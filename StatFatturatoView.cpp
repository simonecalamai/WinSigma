// StatFatturatoView.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "StatFatturatoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatFatturatoView

#include "WinSigmaDoc.h"
#include "Printerpreter.h"

int CStatFatturatoView::m_nIndex;
CStringArray	CStatFatturatoView::m_aryDatiStampa;

IMPLEMENT_DYNCREATE(CStatFatturatoView, CFormView)

CStatFatturatoView::CStatFatturatoView()
	: CFormView(CStatFatturatoView::IDD)
{
	//{{AFX_DATA_INIT(CStatFatturatoView)
	m_csAnno = _T("");
	m_csCliente = _T("");
	m_csMese = _T("");
	m_csCodiceCliente = _T("");
	//}}AFX_DATA_INIT
}

CStatFatturatoView::~CStatFatturatoView()
{
}

void CStatFatturatoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatFatturatoView)
	DDX_Control(pDX, IDC_BUTTON_ORDINA_VERBALI, m_btnOrdinaVerbali);
	DDX_Control(pDX, IDC_BUTTON_ORDINA_IMPONIBILE, m_btnOrdinaImponibile);
	DDX_Control(pDX, IDC_BUTTON_STAMPA_REPORT, m_btnStampaReport);
	DDX_Control(pDX, IDC_LIST_FATTURATO, m_listFatturato);
	DDX_Control(pDX, IDC_COMBO_MESE, m_cmbMese);
	DDX_Control(pDX, IDC_COMBO_CLIENTE, m_cmbCliente);
	DDX_Control(pDX, IDC_COMBO_ANNO, m_cmbAnno);
	DDX_Control(pDX, IDC_BUTTON_RICERCA, m_btnRicerca);
	DDX_CBString(pDX, IDC_COMBO_ANNO, m_csAnno);
	DDX_CBString(pDX, IDC_COMBO_CLIENTE, m_csCliente);
	DDX_CBString(pDX, IDC_COMBO_MESE, m_csMese);
	DDX_Text(pDX, IDC_EDIT_CODICE, m_csCodiceCliente);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatFatturatoView, CFormView)
	//{{AFX_MSG_MAP(CStatFatturatoView)
	ON_BN_CLICKED(IDC_BUTTON_RICERCA, OnButtonRicerca)
	ON_BN_CLICKED(IDC_BUTTON_STAMPA_REPORT, OnButtonStampaReport)
	ON_BN_CLICKED(IDC_BUTTON_TROVA_CLIENTE, OnButtonTrovaCliente)
	ON_CBN_SELCHANGE(IDC_COMBO_ANNO, OnSelchangeComboAnno)
	ON_CBN_SELCHANGE(IDC_COMBO_CLIENTE, OnSelchangeComboCliente)
	ON_CBN_SELCHANGE(IDC_COMBO_MESE, OnSelchangeComboMese)
	ON_BN_CLICKED(IDC_BUTTON_ORDINA_VERBALI, OnButtonOrdinaVerbali)
	ON_BN_CLICKED(IDC_BUTTON_ORDINA_IMPONIBILE, OnButtonOrdinaImponibile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatFatturatoView diagnostics

#ifdef _DEBUG
void CStatFatturatoView::AssertValid() const
{
	CFormView::AssertValid();
}

void CStatFatturatoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStatFatturatoView message handlers

void CStatFatturatoView::OnInitialUpdate() 
{
	int n				= 0;
	int year		= 0;
	int minAnno = 0;
	int maxAnno = 0;
	DWORD Result_style;

	CFormView::OnInitialUpdate();

	if(!(m_pApp = ((CWinSigmaApp*)AfxGetApp())))
		return;
	
	// Inizializza la grid per i risultati
	Result_style = m_listFatturato.GetExtendedStyle();
	Result_style |= LVS_EX_GRIDLINES;
	m_listFatturato.SetExtendedStyle(Result_style);
  m_listFatturato.InsertColumn(0, "Cliente", LVCFMT_LEFT, 468, -1);
	m_listFatturato.InsertColumn(1, "N° Verbali", LVCFMT_LEFT, 85, -1);
	m_listFatturato.InsertColumn(2, "Importo fatture", LVCFMT_LEFT, 85, -1);

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

	m_cmbAnno.InsertString(0, "Tutti");
	m_cmbAnno.SetItemData(0, 0);
	n++;
	maxAnno++;
	for (int i = minAnno; i < maxAnno; i++)
	{
		CString Anno("");
		Anno.Format("%d", i);
		m_cmbAnno.InsertString(n, Anno);
		m_cmbAnno.SetItemData(n, i);
    n++;
	}
	// Seleziona il primo elemento della combobox
	m_cmbAnno.SetCurSel(0);
	
	// Chiusura recordSet Listini
  if(pListiniSet)
  {
  	pListiniSet->Close();
  	delete pListiniSet;
  }

	// Popola la combo dei mesi
	m_cmbMese.InsertString(0, "Tutti");
	m_cmbMese.SetItemData(0, 0);

	m_cmbMese.InsertString(1, "Gennaio");
	m_cmbMese.SetItemData(1, 1);

	m_cmbMese.InsertString(2, "Febbraio");
	m_cmbMese.SetItemData(2, 2);

	m_cmbMese.InsertString(3, "Marzo");
	m_cmbMese.SetItemData(3, 3);

	m_cmbMese.InsertString(4, "Aprile");
	m_cmbMese.SetItemData(4, 4);

	m_cmbMese.InsertString(5, "Maggio");
	m_cmbMese.SetItemData(5, 5);

	m_cmbMese.InsertString(6, "Giugno");
	m_cmbMese.SetItemData(6, 6);

	m_cmbMese.InsertString(7, "Luglio");
	m_cmbMese.SetItemData(7, 7);

	m_cmbMese.InsertString(8, "Agosto");
	m_cmbMese.SetItemData(8, 8);

	m_cmbMese.InsertString(9, "Settembre");
	m_cmbMese.SetItemData(9, 9);

	m_cmbMese.InsertString(10, "Ottobre");
	m_cmbMese.SetItemData(10, 10);

	m_cmbMese.InsertString(11, "Novembre");
	m_cmbMese.SetItemData(11, 11);

	m_cmbMese.InsertString(12, "Dicembre");
	m_cmbMese.SetItemData(12, 12);

	// Seleziona il primo elemento della combobox
	m_cmbMese.SetCurSel(0);
}

void CStatFatturatoView::OnButtonRicerca() 
{
	int			n							= 0;
	int			Codice				= 0;
	int			Intestatario	= 0;
	int			Verbali				= 0;
	double	Imponibile		= 0;
	CString	csVerbali("");
	CString RagSoc("");
	CString str("");
	CWinSigmaDoc* pDoc			= NULL;
	CFattureSet*	pFatture	= NULL;

	if(!(pDoc = ((CWinSigmaDoc*)GetDocument())))
	{
		MessageBox("Impossibile di effettuare la ricerca!", "Attenzione", MB_OK);
		return;
	}
	// Reperisce il puntatore alla tabella delle Fatture
	pFatture = pDoc->m_pFattureEmesseSet;
	pFatture->m_strFilter = "";

	// Costruisce il filtro per la query
	if(m_cmbCliente.GetItemData(m_cmbCliente.GetCurSel()) != 0)
		pFatture->m_strFilter.Format("Intestatario = %d", m_cmbCliente.GetItemData(m_cmbCliente.GetCurSel()));

	if(m_cmbAnno.GetItemData(m_cmbAnno.GetCurSel()) != 0)
	{
		if(pFatture->m_strFilter == "") 
			str.Format("YEAR(Data) = %d", m_cmbAnno.GetItemData(m_cmbAnno.GetCurSel()));
		else
			str.Format(" AND YEAR(Data) = %d", m_cmbAnno.GetItemData(m_cmbAnno.GetCurSel()));

		pFatture->m_strFilter.Insert(pFatture->m_strFilter.GetLength(), str);
	}

	if(m_cmbMese.GetItemData(m_cmbMese.GetCurSel()) != 0)
	{
		if(pFatture->m_strFilter == "") 
			str.Format("MONTH(Data) = %d", m_cmbMese.GetItemData(m_cmbMese.GetCurSel()));
		else
			str.Format(" AND MONTH(Data) = %d", m_cmbMese.GetItemData(m_cmbMese.GetCurSel()));

		pFatture->m_strFilter.Insert(pFatture->m_strFilter.GetLength(), str);
	}

	// Ordina per intestatario
	pFatture->m_strSort = "Intestatario";
	
	// Ricerca i dati
	pFatture->Requery();

	m_listFatturato.DeleteAllItems();

	if (!pFatture->IsEOF())
	{
		Intestatario = pFatture->m_Intestatario;
		RagSoc = pFatture->m_RagioneSociale;
		Codice = pFatture->m_Codice;
	}
	else
	{
		MessageBox("Report vuoto!", "Attenzione", MB_OK);
		
		// Disabilita il pulsante per la stampa del report
		m_btnStampaReport.EnableWindow(FALSE);
		
		// Disabilita i pulsanti per l'ordinamento
		m_btnOrdinaVerbali.EnableWindow(FALSE);
		m_btnOrdinaImponibile.EnableWindow(FALSE);

		return;
	}

	for(SET_START(pFatture); !pFatture->IsEOF(); pFatture->MoveNext())
	{
		if(Intestatario != pFatture->m_Intestatario)
		{
			if(Imponibile > 0)
			{
				n = m_listFatturato.InsertItem(n, RagSoc);
				m_listFatturato.SetItemData(n, Codice);
				
				csVerbali.Format("%d", Verbali);
				m_listFatturato.SetItemText(n, 1, csVerbali);
				
				str.Format("%.2f", Imponibile);
				m_listFatturato.SetItemText(n, 2, str);
			}

			Imponibile	= 0;
			Verbali			= 0;
			Intestatario = pFatture->m_Intestatario;
			RagSoc = pFatture->m_RagioneSociale;
			Codice = pFatture->m_Codice;
		}

		Imponibile += pFatture->m_Imponibile;
		Verbali += NumeroVerbali(Codice);
	}

	n = m_listFatturato.InsertItem(n, pFatture->m_RagioneSociale);
	m_listFatturato.SetItemData(n, pFatture->m_Codice);
	
	csVerbali.Format("%d", Verbali);
	m_listFatturato.SetItemText(n, 1, csVerbali);
	
	str.Format("%.2f", Imponibile);
	m_listFatturato.SetItemText(n, 2, str);

	// Abilita il pulsante per la stampa del report
	m_btnStampaReport.EnableWindow(TRUE);

	// Abilita i pulsanti per l'ordinamento
	m_btnOrdinaVerbali.EnableWindow(TRUE);
	m_btnOrdinaImponibile.EnableWindow(TRUE);
	
}

int CStatFatturatoView::NumeroVerbali(int Fatture_Codice)
{
	// Restituisce il numero di verbali associati ad una fattura

	CWinSigmaDoc* pDoc			= NULL;
	CVerbaliSet*	pVerbali	= NULL;
	int n = 0;
	
	if(Fatture_Codice > 0)
	{
		if(!(pDoc = ((CWinSigmaDoc*)GetDocument())))
		{
			MessageBox("Impossibile di effettuare la ricerca!", "Attenzione", MB_OK);
			return 0;
		}
		
		// Reperisce il puntatore alla tabella dei Verbali
		pVerbali = pDoc->m_pVerbaliAperti;
		pVerbali->m_strFilter.Format("Fattura = %d", Fatture_Codice);
		pVerbali->Requery();
		for(; !pVerbali->IsEOF(); pVerbali->MoveNext())
			n++;
		return n;
	}
	else
		return 0;
}

void CStatFatturatoView::OnButtonStampaReport() 
{
	int i = 0;
	CString str("");
	CPrintInterpreter prn;
	CStringArray fieldNames, fieldValues;

	CWinSigmaApp* pApp	= (CWinSigmaApp*)AfxGetApp();

	m_nIndex = 0;

	if(prn.PrePrinting())
	{
		m_cmbAnno.GetWindowText(str);
		if(str == "Tutti")
			str.Format("da %d a %d", m_cmbAnno.GetItemData(1), m_cmbAnno.GetItemData(m_cmbAnno.GetCount() - 1));
		else
			str.Format("%d", m_cmbAnno.GetItemData(m_cmbAnno.GetCurSel()));
		fieldNames.Add("anno");
		fieldValues.Add(str);

		m_cmbMese.GetWindowText(str);
		if (str == "Tutti")
			str = "Anno";
		fieldNames.Add("mese");
		fieldValues.Add(str);

		for(i = 0; i < m_listFatturato.GetItemCount(); i++)
		{
			m_aryDatiStampa.Add(m_listFatturato.GetItemText(i, 0));
			m_aryDatiStampa.Add(m_listFatturato.GetItemText(i, 1));
			m_aryDatiStampa.Add(m_listFatturato.GetItemText(i, 2));
		}

		prn.Print(pApp->GetCurrentDirectory() + "\\" + "StatisticheFatturato.prn", &fieldNames, &fieldValues, NULL, NULL, &ScanFatture);
	}

	m_aryDatiStampa.RemoveAll();

	prn.PostPrinting();
}


BOOL CStatFatturatoView::ScanFatture(CStringArray* pFieldNames, CStringArray* pFieldValues)
{	
	// CallBack per la stampa del report 
	pFieldNames->RemoveAll();
	pFieldValues->RemoveAll();

	pFieldNames->Add("cliente");
	pFieldValues->Add(m_aryDatiStampa.GetAt(m_nIndex++));

	pFieldNames->Add("numeroverbali");
	pFieldValues->Add(m_aryDatiStampa.GetAt(m_nIndex++));

	pFieldNames->Add("imponibile");
	pFieldValues->Add(m_aryDatiStampa.GetAt(m_nIndex++));
	
	if(m_nIndex >= m_aryDatiStampa.GetSize())
		return FALSE;

	return TRUE;
}

void CStatFatturatoView::OnButtonTrovaCliente() 
{
	// Ricerca il cliente in base al codice (anche parziale)
	int n = 0;

	UpdateData();

	// Disabilita la combo per la scelta dei clienti
	m_cmbCliente.EnableWindow(FALSE);

	// Elimina tutti gli elementi dalla combobox
	n = 0;
	m_cmbCliente.ResetContent();

	// Popola la combo Clienti
	CAziendeSet*	pAziendeSet;
	pAziendeSet = new CAziendeSet(&m_pApp->m_db);

  if(m_csCodiceCliente != "")
		// Seleziona il cliente in base al codice
		pAziendeSet->m_strFilter.Format("ID LIKE '%s%%'", m_csCodiceCliente);
	else
	{
		// Seleziona tutti i clienti
		pAziendeSet->m_strFilter = "Codice > 0";

		// Da la possibilità di effettuare la ricerca su tutti i clienti
		m_cmbCliente.InsertString(n, "Tutti");
		m_cmbCliente.SetItemData(n++, 0);
	}

	// Ordina il risultato in base alla ragione sociale
	pAziendeSet->m_strSort = "RagioneSociale";
	pAziendeSet->Open();

	if(pAziendeSet->IsEOF())
		return;

	for(; !pAziendeSet->IsEOF(); pAziendeSet->MoveNext())
	{
		// Inserisce gli elementi della query all'interno della combobox
		m_cmbCliente.InsertString(n, pAziendeSet->m_RagioneSociale);
		m_cmbCliente.SetItemData(n, pAziendeSet->m_Codice);
		n++;
	}

	// Seleziona il primo elemento della combobox
	m_cmbCliente.SetCurSel(0);

	// Chiusura recordSet Aziende
  if(pAziendeSet)
  {
  	pAziendeSet->Close();
  	delete pAziendeSet;
  }

	// Abilita la combobox dei clienti
	m_cmbCliente.EnableWindow(TRUE);
}

void CStatFatturatoView::OnSelchangeComboAnno() 
{
	// Disabilita il pulsante per la stampa del report
	m_btnStampaReport.EnableWindow(FALSE);

	// Disabilita i pulsanti per l'ordinamento
	m_btnOrdinaVerbali.EnableWindow(FALSE);
	m_btnOrdinaImponibile.EnableWindow(FALSE);
}

void CStatFatturatoView::OnSelchangeComboCliente() 
{
	// Disabilita il pulsante per la stampa del report
	m_btnStampaReport.EnableWindow(FALSE);

	// Disabilita i pulsanti per l'ordinamento
	m_btnOrdinaVerbali.EnableWindow(FALSE);
	m_btnOrdinaImponibile.EnableWindow(FALSE);
}

void CStatFatturatoView::OnSelchangeComboMese() 
{
	// Disabilita il pulsante per la stampa del report
	m_btnStampaReport.EnableWindow(FALSE);

	// Disabilita i pulsanti per l'ordinamento
	m_btnOrdinaVerbali.EnableWindow(FALSE);
	m_btnOrdinaImponibile.EnableWindow(FALSE);
}

void CStatFatturatoView::OnButtonOrdinaVerbali() 
{
	CString str("");
	int index = -1;

	for(int i(0); i < m_listFatturato.GetItemCount(); i++)
	{
		index = i;
		str = m_listFatturato.GetItemText(i, 1);
		for(int j(i+1); j < m_listFatturato.GetItemCount(); j++)
		{
			if(atof(str) < atof(m_listFatturato.GetItemText(j, 1)))
			{
				index = j;
				str = m_listFatturato.GetItemText(j, 1);
			}
		}
		
		if(index != i)
		{
			// Devo scambiare gli elementi
			CString Cliente			= m_listFatturato.GetItemText(index, 0);
			CString Verbali			= m_listFatturato.GetItemText(index, 1);
			CString Imponibile	= m_listFatturato.GetItemText(index, 2);

			
			m_listFatturato.SetItemText(index, 0, m_listFatturato.GetItemText(i, 0));
			m_listFatturato.SetItemText(index, 1, m_listFatturato.GetItemText(i, 1));
			m_listFatturato.SetItemText(index, 2, m_listFatturato.GetItemText(i, 2));


			m_listFatturato.SetItemText(i, 0, Cliente);
			m_listFatturato.SetItemText(i, 1, Verbali);
			m_listFatturato.SetItemText(i, 2, Imponibile);
		}
	}

	UpdateData(FALSE);
}

void CStatFatturatoView::OnButtonOrdinaImponibile() 
{
	CString str("");
	int index = -1;

	for(int i(0); i < m_listFatturato.GetItemCount(); i++)
	{
		index = i;
		str = m_listFatturato.GetItemText(i, 2);
		for(int j(i+1); j < m_listFatturato.GetItemCount(); j++)
		{
			if(atof(str) < atof(m_listFatturato.GetItemText(j, 2)))
			{
				index = j;
				str = m_listFatturato.GetItemText(j, 2);
			}
		}
		
		if(index != i)
		{
			// Devo scambiare gli elementi
			CString Cliente			= m_listFatturato.GetItemText(index, 0);
			CString Verbali			= m_listFatturato.GetItemText(index, 1);
			CString Imponibile	= m_listFatturato.GetItemText(index, 2);

			
			m_listFatturato.SetItemText(index, 0, m_listFatturato.GetItemText(i, 0));
			m_listFatturato.SetItemText(index, 1, m_listFatturato.GetItemText(i, 1));
			m_listFatturato.SetItemText(index, 2, m_listFatturato.GetItemText(i, 2));


			m_listFatturato.SetItemText(i, 0, Cliente);
			m_listFatturato.SetItemText(i, 1, Verbali);
			m_listFatturato.SetItemText(i, 2, Imponibile);
		}
	}

	UpdateData(FALSE);
}
