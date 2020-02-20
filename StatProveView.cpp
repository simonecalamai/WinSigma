// StatProveView.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "StatProveView.h"
#include "VerbaliServErogatiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatProveView

#include "Printerpreter.h"

int CStatProveView::m_nIndex;
CStringArray	CStatProveView::m_aryDatiStampa;

IMPLEMENT_DYNCREATE(CStatProveView, CFormView)

CStatProveView::CStatProveView()
	: CFormView(CStatProveView::IDD)
{
	//{{AFX_DATA_INIT(CStatProveView)
	m_csAnno = _T("");
	//}}AFX_DATA_INIT

	m_pDoc								= NULL;
  m_pTCertificatoSet		= NULL;
  m_pCatServSet					= NULL;
	m_pVerbaliServErogati = NULL;
}

CStatProveView::~CStatProveView()
{
	if(m_pCatServSet)
  {
    m_pCatServSet->Close();
    delete m_pCatServSet;
  }

  if(m_pVerbaliServErogati)
  {
  	m_pVerbaliServErogati->Close();
  	delete m_pVerbaliServErogati;
  }
}

void CStatProveView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatProveView)
	DDX_Control(pDX, IDC_BUTTON_REPORT, m_btnPrintReport);
	DDX_Control(pDX, IDC_LIST_RISULTATO, m_ListRisultato);
	DDX_Control(pDX, IDC_BUTTON_RICERCA, m_btnRicerca);
	DDX_Control(pDX, IDC_COMBO_ANNI, m_cmbAnni);
	DDX_Control(pDX, IDC_LIST_SERVIZI, m_ListServizi);
	DDX_Control(pDX, IDC_COMBO_TIPI_CERTIFICATO, m_ComboTipoCertificato);
	DDX_CBString(pDX, IDC_COMBO_ANNI, m_csAnno);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatProveView, CFormView)
	//{{AFX_MSG_MAP(CStatProveView)
	ON_CBN_SELCHANGE(IDC_COMBO_TIPI_CERTIFICATO, OnSelchangeComboTipiCertificato)
	ON_CBN_SELCHANGE(IDC_COMBO_ANNI, OnSelchangeComboAnni)
	ON_BN_CLICKED(IDC_BUTTON_RICERCA, OnButtonRicerca)
	ON_BN_CLICKED(IDC_BUTTON_REPORT, OnButtonReport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatProveView diagnostics

#ifdef _DEBUG
void CStatProveView::AssertValid() const
{
	CFormView::AssertValid();
}

void CStatProveView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStatProveView message handlers

void CStatProveView::OnInitialUpdate() 
{
	int n				= 0;
	int year		= 0;
	int minAnno = 0;
	int maxAnno = 0;
	CString str("");
	DWORD Service_style;
	DWORD Result_style;

	CFormView::OnInitialUpdate();
	
	if(!(m_pApp = ((CWinSigmaApp*)AfxGetApp())))
		return;
	

	if(!(m_pDoc = ((CWinSigmaDoc*)GetDocument())))
		return;

	// Servizi erogati associati ad un verbale
	m_pVerbaliServErogati = new CVerbaliServErogatiSet(&m_pApp->m_db);
  m_pVerbaliServErogati->m_strFilter = "VERBALI.Codice = 0";
	m_pVerbaliServErogati->Open();

	// Recupera gli anni di validità dei listini per le ricerche dei servizi erogati
	CListiniSet*	pListiniSet;
	pListiniSet = new CListiniSet(&m_pApp->m_db);
  pListiniSet->m_strFilter = "Inizio is not null";
	pListiniSet->m_strSort = "Inizio";
	pListiniSet->Open();
	
	// Caricamento degli anni nella combo
	// Prende dalle date di validità dei listini l'anno minimo e quello massimo
	if (!pListiniSet->IsEOF())
	{
		minAnno = pListiniSet->m_Inizio.GetYear();
		for(SET_START(pListiniSet); !pListiniSet->IsEOF(); pListiniSet->MoveNext());
		maxAnno = pListiniSet->m_Fine.GetYear();
	}

	maxAnno++;
	for (int i = minAnno; i < maxAnno; i++)
	{
		CString Anno("");
		Anno.Format("%d", i);
		m_cmbAnni.InsertString(n, Anno);
		m_cmbAnni.SetItemData(n, i);
    n++;
	}
	// Seleziona il primo elemento della combobox
	m_cmbAnni.SetCurSel(0);

	// Chiusura recordSet Listini
  if(pListiniSet)
  {
  	pListiniSet->Close();
  	delete pListiniSet;
  }

  // Inizializza la lista dei servizi e quella del report
  Service_style = m_ListServizi.GetExtendedStyle();
  Service_style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES;
	m_ListServizi.SetExtendedStyle(Service_style);
  m_ListServizi.InsertColumn(0, "Codice", LVCFMT_LEFT, 65, -1);
	m_ListServizi.InsertColumn(1, "Descrizione", LVCFMT_LEFT, 468, -1);

	Result_style = m_ListRisultato.GetExtendedStyle();
	Result_style |= LVS_EX_GRIDLINES;
	m_ListRisultato.SetExtendedStyle(Result_style);
  m_ListRisultato.InsertColumn(0, "Tipo di prova", LVCFMT_LEFT, 85, -1);
	m_ListRisultato.InsertColumn(1, "Quantità", LVCFMT_LEFT, 468, -1);

	// Categorie e servizi associati al listino
  m_pCatServSet = new CCategorieServiziSet(&m_pApp->m_db);
  m_pCatServSet->m_strFilter.Format("Listino = 0");
  m_pCatServSet->Open();
	
	// Carico la lista dei tipi di certificato
  m_pTCertificatoSet = m_pDoc->m_pTipiCertificatoSet;
	m_pTCertificatoSet->m_strSort = "Ordinamento";
	m_pTCertificatoSet->Requery();
  n = m_ComboTipoCertificato.AddString("--- Nessuno ---");
	m_ComboTipoCertificato.SetItemData(n, 0);
  m_ComboTipoCertificato.SetCurSel(0);
  for(SET_START(m_pTCertificatoSet); !m_pTCertificatoSet->IsEOF(); m_pTCertificatoSet->MoveNext())
  {
    str.Format("%d - %s", m_pTCertificatoSet->m_Codice, m_pTCertificatoSet->m_Nome);
		n = m_ComboTipoCertificato.AddString(str);
		m_ComboTipoCertificato.SetItemData(n, m_pTCertificatoSet->m_Codice);
  }
}

void CStatProveView::OnSelchangeComboTipiCertificato() 
{
  int i;

  if((i = m_ComboTipoCertificato.GetCurSel()) != -1)
  {
		if(i != 0)
		{
			for(SET_START(m_pTCertificatoSet); !m_pTCertificatoSet->IsEOF(); m_pTCertificatoSet->MoveNext())
			{
				if((DWORD)m_pTCertificatoSet->m_Codice == m_ComboTipoCertificato.GetItemData(i))
					break;
			}
			// Aggiorno la lista dei servizi associati alla tipologia di certificato
			LoadServizi();

			// Ablita il pulsante per la ricerca
			m_btnRicerca.EnableWindow(TRUE);

			// Disabilita il pulsante per la stampa del report
			m_btnPrintReport.EnableWindow(FALSE);

			m_ListRisultato.DeleteAllItems();
		}
		else
		{
			// Cancella la lista dei servizi
			m_ListServizi.DeleteAllItems();

			// Disabilita il pulsante per la ricerca
			m_btnRicerca.EnableWindow(FALSE);
		}
  }
}

// Carica la lista dei servizi
void CStatProveView::LoadServizi(void)
{
  int n = 0;
  CString str("");
	
	UpdateData();

  m_pVerbaliServErogati->m_strFilter.Format("(VERBALI.Codice = SERVIZI_EROGATI.Verbale) AND YEAR(DataAccettazione) = %s GROUP BY ListinoGenerale, ListinoParticolare", m_csAnno);
	m_pVerbaliServErogati->Requery();

	m_pCatServSet->m_strFilter = "";

	if(!m_pVerbaliServErogati->IsEOF())
		m_pCatServSet->m_strFilter = "(Categoria = CATEGORIE.Codice)";
	else
		m_pCatServSet->m_strFilter = "((Categoria = CATEGORIE.Codice)";

	n = 0;
	for(; !m_pVerbaliServErogati->IsEOF(); m_pVerbaliServErogati->MoveNext())
	{
		if((!m_pVerbaliServErogati->IsFieldNull(&m_pVerbaliServErogati->m_ListinoGenerale)) && (!m_pVerbaliServErogati->IsFieldNull(&m_pVerbaliServErogati->m_ListinoParticolare)))
		{
			if (!n)
				str.Format(" AND ((Listino = %d OR Listino = %d)",m_pVerbaliServErogati->m_ListinoGenerale, m_pVerbaliServErogati->m_ListinoParticolare);
			else
				str.Format(" OR (Listino = %d OR Listino = %d)",m_pVerbaliServErogati->m_ListinoGenerale, m_pVerbaliServErogati->m_ListinoParticolare);

			m_pCatServSet->m_strFilter.Insert(m_pCatServSet->m_strFilter.GetLength(), str);
			n++;
		}
	}
	m_pCatServSet->m_strFilter.Insert(m_pCatServSet->m_strFilter.GetLength(), ")");
	str.Format(" AND ((Certificato = %d) OR (Certificato2 = %d))",  m_pTCertificatoSet->m_Codice, m_pTCertificatoSet->m_Codice);
	m_pCatServSet->m_strFilter.Insert(m_pCatServSet->m_strFilter.GetLength(), str);
	m_pCatServSet->m_strFilter.Insert(m_pCatServSet->m_strFilter.GetLength(), " GROUP BY SERVIZI_LISTINO.ID");
	m_pCatServSet->Requery();

  // Cancello gli items della lista
  m_ListServizi.DeleteAllItems();
  // Servizi associati a questo tipo di certificato appartenenti alle categorie associate al listino selezionato
  for(SET_START(m_pCatServSet); !m_pCatServSet->IsEOF(); m_pCatServSet->MoveNext())
  {
    n = m_ListServizi.InsertItem(n, m_pCatServSet->m_ID);
    m_ListServizi.SetItemData(n, m_pCatServSet->m_Codice);
    m_ListServizi.SetItemText(n, 1, FormatDescrizione());
    m_ListServizi.SetCheck(n, FALSE);
  }
}

CString CStatProveView::FormatDescrizione(void)
{
  CString str, strApp;
  BOOL bSerie = ((BOOL)(m_pCatServSet->m_PerSerie));
  
  if(m_pCatServSet->m_Nome.IsEmpty())
  {
    str = m_pCatServSet->m_Descrizione;
    str = str.Mid(0, 60);
    str.Replace("\r\n", " ");
    if(str.GetLength() < m_pCatServSet->m_Descrizione)
      str += "...";
  }
  else
    str = m_pCatServSet->m_Nome;
  if(bSerie)
    strApp.Format(", per serie di %d provini", m_pCatServSet->m_Campioni);
  else
  {
    if(m_pCatServSet->m_Prove != 0)
      strApp = ", per provino";
    else
      strApp = ", cad.";
  }
  str += strApp;
  return str;
}

void CStatProveView::OnSelchangeComboAnni() 
{
  int i;

  if((i = m_ComboTipoCertificato.GetCurSel()) != -1)
  {
    for(SET_START(m_pTCertificatoSet); !m_pTCertificatoSet->IsEOF(); m_pTCertificatoSet->MoveNext())
    {
      if((DWORD)m_pTCertificatoSet->m_Codice == m_ComboTipoCertificato.GetItemData(i))
        break;
    }
    LoadServizi();

		// Disabilita il pulsante per la stampa del report
		m_btnPrintReport.EnableWindow(FALSE);

		m_ListRisultato.DeleteAllItems();
  }
}

void CStatProveView::OnButtonRicerca() 
{
	int n		= 0;
	int i   = 0;
	int cnt = 0;

	// Apre il recordset per calcolare il numero di prove per i materiali
	CVerbSerProSet* pVerSerPro = new CVerbSerProSet(&m_pApp->m_db);
	pVerSerPro->m_strFilter = "VERBALI.Codice = 0";
	pVerSerPro->Open();

	CVerbaliServErogatiSet* pVerSer = new CVerbaliServErogatiSet(&m_pApp->m_db);
	pVerSer->m_strFilter = "VERBALI.Codice = 0";
	pVerSer->Open();

	UpdateData();

	for(i = 0; i < m_ListServizi.GetItemCount(); i++)
	{
		if(m_ListServizi.GetCheck(i))
		{
			m_btnPrintReport.EnableWindow(TRUE); 
			break;
		}
		else
			m_btnPrintReport.EnableWindow(FALSE); 
	}
	// Cancella la lista del report
	m_ListRisultato.DeleteAllItems();

	for(i = 0; i < m_ListServizi.GetItemCount(); i++)
	{
		if(m_ListServizi.GetCheck(i))
		{
			n = m_ListRisultato.InsertItem(n, m_ListServizi.GetItemText(i,0));
			m_ListRisultato.SetItemData(n, m_pVerbaliServErogati->m_CodiceServizioErogato);
			
			pVerSerPro->m_strFilter.Format("SERIE.Verbale = VERBALI.Codice AND PROVINI.Serie = SERIE.Codice AND PROVINI.Servizio = '%s' AND YEAR(VERBALI.DataAccettazione) = %s", m_ListServizi.GetItemText(i,0), m_csAnno);
			pVerSerPro->Requery();
			
			if(pVerSerPro->IsEOF())
			{
				pVerSer->m_strFilter.Format("SERVIZI_EROGATI.Verbale = VERBALI.Codice AND YEAR(VERBALI.DataAccettazione) = %s AND SERVIZI_EROGATI.ID_Listino = '%s'", m_csAnno, m_ListServizi.GetItemText(i,0));
				pVerSer->Requery();

				for(cnt = 0; !pVerSer->IsEOF(); pVerSer->MoveNext())
					cnt += (int)pVerSer->m_Quantita;
			}
			else
				for(cnt = 0; !pVerSerPro->IsEOF(); pVerSerPro->MoveNext(),cnt++);
			
			CString app("");
			app.Format("%d", cnt);
			m_ListRisultato.SetItemText(n, 1, app);
		}
	}

	if(pVerSerPro)
	{
		if(pVerSerPro->IsOpen())
			pVerSerPro->Close();
		delete pVerSerPro;
	}
	if(pVerSer)
	{
		if(pVerSer->IsOpen())
			pVerSer->Close();
		delete pVerSer;
	}
}

void CStatProveView::OnButtonReport() 
{
	int i = 0;
	CPrintInterpreter prn;
	CStringArray fieldNames, fieldValues;
	CString str("");

	CWinSigmaApp* pApp	= (CWinSigmaApp*)AfxGetApp();

	m_nIndex = 0;
	
	if(prn.PrePrinting())
	{
		str.Format("%d", m_cmbAnni.GetItemData(m_cmbAnni.GetCurSel()));
		fieldNames.Add("anno");
		fieldValues.Add(str);

		for(i = 0; i < m_ListRisultato.GetItemCount(); i++)
		{
			m_aryDatiStampa.Add(m_ListRisultato.GetItemText(i, 0));
			m_aryDatiStampa.Add(m_ListRisultato.GetItemText(i, 1));
		}

		prn.Print(pApp->GetCurrentDirectory() + "\\" + "StatisticheProve.prn", &fieldNames, &fieldValues, NULL, NULL, &ScanProve);
	}

	m_aryDatiStampa.RemoveAll();

	prn.PostPrinting();	
}

BOOL CStatProveView::ScanProve(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
	if(m_nIndex >= m_aryDatiStampa.GetSize())
		return FALSE;

	pFieldNames->RemoveAll();
	pFieldValues->RemoveAll();

	pFieldNames->Add("prova");
	pFieldValues->Add(m_aryDatiStampa.GetAt(m_nIndex++));

	pFieldNames->Add("numeroprove");
	pFieldValues->Add(m_aryDatiStampa.GetAt(m_nIndex++));
	
	if(m_nIndex >= m_aryDatiStampa.GetSize())
		return FALSE;

	return TRUE;
}