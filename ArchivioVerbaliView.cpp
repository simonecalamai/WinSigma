// ArchivioVerbaliView.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "PreviewDlg.h"
#include "PrintPreviewVerbali.h"
#include "ArchivioVerbaliView.h"
#include "FindVerbaliDlg.h"
//#include "PrintVerbali.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define STR_VERIFY_LETTERE "AaBbCcDdEeFfGgHhIiLlMmNnOoPpQqRrSsTtUuVvZzXxYyWwJjKk"

/////////////////////////////////////////////////////////////////////////////
// CArchivioVerbaliView

IMPLEMENT_DYNCREATE(CArchivioVerbaliView, CFormView)

CArchivioVerbaliView::CArchivioVerbaliView()
	: CFormView(CArchivioVerbaliView::IDD)
{
	//{{AFX_DATA_INIT(CArchivioVerbaliView)
	m_csRagione_Sociale = _T("");
	m_csCodice = _T("");
	m_chkVerbaliAperti = FALSE;
	m_csDaNumero = _T("");
	m_csANumero = _T("");
	//}}AFX_DATA_INIT
}

CArchivioVerbaliView::~CArchivioVerbaliView()
{
	//Chiusura recordSet Testata Fattura
	m_pSetVerbali->Close();
	delete m_pSetVerbali;
}

void CArchivioVerbaliView::Query(BOOL bVA)
{
	CString sql;
	CString csApp;

	//Avvalora le variabili con il contenuto degli oggetti all'interno della form
	UpdateData(TRUE);

	m_cmbAnni.GetLBText(m_cmbAnni.GetCurSel(),csApp);
	
	if (csApp != "Tutti")
			sql="(DataAccettazione >= '" + csApp + "-1-1' AND DataAccettazione <= '" + csApp + "-12-31')";

	//Compone la stringa sql da utilizzare nella Query
	if (m_csDaNumero!="")
		{
			if (m_csANumero!="")
      {
        if (sql=="")
					  sql="(ProgressivoTotale >= " + m_csDaNumero + " And ProgressivoTotale <= " + m_csANumero + ")";
			  else
					  sql+=" AND (ProgressivoTotale >= " + m_csDaNumero + " And ProgressivoTotale <= " + m_csANumero + ")";
      }
      else
      {
        if (sql=="")
					  sql="(ProgressivoTotale = " + m_csDaNumero + ")";
			  else
					  sql+=" AND (ProgressivoTotale = " + m_csDaNumero + ")";
      }
		}
	
	//Se il campo ragione sociale è avvalorato 
	//a seconda del radio button selezionato sceglie il campo su cui fare la Query
	if (m_csRagione_Sociale!="")
		{
			m_csRagione_Sociale.Replace("'", "''");
			CString CampoApp;

			if (m_rbIntestazione_Certificati)
					CampoApp="NomeIntestatarioCertificato";
			else if (m_rbIntestazione_Fatture)
					CampoApp="NomeIntestatarioFattura";
			else if (m_rbImpresa_Costruttrice)
					CampoApp="NomeImpresaRichiedente";
			else if (m_rbDestinatario_Certificati)
					CampoApp="NomeSpedizioneRitiro";

			if (sql=="")
					sql="(" + CampoApp + " LIKE '%" + m_csRagione_Sociale + "%')";
			else
					sql+=" AND (" + CampoApp + " LIKE '%" + m_csRagione_Sociale + "%')";
		}

	if (m_csCodice!="")
		{
			if (sql=="")
					sql="(IDIntestatarioCertificato = '" + m_csCodice + "')";
			else
					sql+=" AND (IDIntestatarioCertificato = '" + m_csCodice + "')";
		}

	//Esegue la Query su RecordSet
	if ( (sql.IsEmpty() ) && ( bVA == FALSE ) )
		sql = "DataChiusura is not null";
	else if ( (!sql.IsEmpty() ) && ( bVA == FALSE ) )
		sql += "AND DataChiusura is not null";

	CString strApp("");
	if (sql.IsEmpty())
		strApp.Format("TipoVerbale = %d OR TipoVerbale = %d OR TipoVerbale = %d OR TipoVerbale = %d OR TipoVerbale = %d OR \
										TipoVerbale = %d OR TipoVerbale = %d OR TipoVerbale = %d OR TipoVerbale = %d OR TipoVerbale = %d OR \
										TipoVerbale = %d OR TipoVerbale = %d OR TipoVerbale = %d", 
									VERB_NON_IN_CONCESSIONE, VERB_IN_CONCESSIONE, VERB_GEOLOGIA, VERB_NC_PROVE_DI_CARICO, VERB_NC_CONGL_BITUMINOSI, 
									VERB_NC_INERTI, VERB_NC_MONITORAGGI, VERB_NC_VARIE, VERB_NC_GEOTECNICA, VERB_NC_LINEE_VITA,
									VERB_NC_INDAGINI_MURATURE, VERB_NC_INDAGINI_CLS, VERB_NC_MAT_METALLICI);
	else
		strApp.Format(" AND (TipoVerbale = %d OR TipoVerbale = %d OR TipoVerbale = %d OR TipoVerbale = %d OR TipoVerbale = %d OR \
													TipoVerbale = %d OR TipoVerbale = %d OR TipoVerbale = %d OR TipoVerbale = %d OR TipoVerbale = %d OR \
													TipoVerbale = %d OR TipoVerbale = %d OR TipoVerbale = %d)",
									VERB_NON_IN_CONCESSIONE, VERB_IN_CONCESSIONE, VERB_GEOLOGIA, VERB_NC_PROVE_DI_CARICO, VERB_NC_CONGL_BITUMINOSI, 
									VERB_NC_INERTI, VERB_NC_MONITORAGGI, VERB_NC_VARIE, VERB_NC_GEOTECNICA, VERB_NC_LINEE_VITA,
									VERB_NC_INDAGINI_MURATURE, VERB_NC_INDAGINI_CLS, VERB_NC_MAT_METALLICI);
	sql += strApp;

	m_pSetVerbali->m_strFilter = sql;
	m_pSetVerbali->Requery();

}

void CArchivioVerbaliView::Popola_Lista()
{
  SetCursor(LoadCursor(NULL, IDC_WAIT));
	//Cancella gli eventuali Item presenti nella lista
	//per poi inserire il risultato della Query
	m_Risultati_Ricerca.DeleteAllItems();
	CString str;
  int n;
  CFattureSet* pFatture = new CFattureSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
  pFatture->m_strFilter = "Codice = 0";
  pFatture->Open();
	//Scorre il risultato della Query
	for(SET_START(m_pSetVerbali); !m_pSetVerbali->IsEOF(); m_pSetVerbali->MoveNext())
	{
		n = m_Risultati_Ricerca.GetItemCount();
		m_Risultati_Ricerca.InsertItem(n, m_pSetVerbali->m_DataAccettazione.Format("%d/%m/%y"));
		m_Risultati_Ricerca.SetItemData(n,(DWORD)m_pSetVerbali->m_Codice);
    str.Format("%d/%d", m_pSetVerbali->m_ProgressivoParziale, m_pSetVerbali->m_ProgressivoTotale);
		m_Risultati_Ricerca.SetItemText(n, 1, str);
		m_Risultati_Ricerca.SetItemText(n, 2, m_pSetVerbali->m_NomeAzCertificato);
		m_Risultati_Ricerca.SetItemText(n, 3, m_pSetVerbali->m_NomeAzFattura);
		m_Risultati_Ricerca.SetItemText(n, 4, m_pSetVerbali->m_NomeImpresa);
    if(m_pSetVerbali->m_Annullato)
      m_Risultati_Ricerca.SetItemText(n, 5, "Annullato");
    else if ( m_pSetVerbali->IsFieldNull(&m_pSetVerbali->m_DataChiusura) )
	  	m_Risultati_Ricerca.SetItemText(n, 5, "Aperto");
	  else
      m_Risultati_Ricerca.SetItemText(n, 5, "");
    pFatture->m_strFilter.Format("Codice = %ld AND Data is not NULL", m_pSetVerbali->m_NumeroFattura);
    pFatture->Requery();
    if(!pFatture->IsEOF())
    {
      str.Format("%ld", pFatture->m_Numero);
      m_Risultati_Ricerca.SetItemText(n, 6, str);
    }

    m_Risultati_Ricerca.SetItemText(n, 7, m_pSetVerbali->m_DescrizioneMateriale);
	}
  pFatture->Close();
}


void CArchivioVerbaliView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArchivioVerbaliView)
	DDX_Control(pDX, IDC_COMBO_ANNO, m_cmbAnni);
	DDX_Control(pDX, IDC_LIST_RISULTATO_RICERCA, m_Risultati_Ricerca);
	DDX_Control(pDX, IDC_RADIO_INTESTAZIONE_CERTIFICATI, m_rbIntestazione_Certificati);
	DDX_Control(pDX, IDC_RADIO_INTESTAZIONE_FATTURE, m_rbIntestazione_Fatture);
	DDX_Control(pDX, IDC_RADIO_IMPRESA_COSTRUTTRICE, m_rbImpresa_Costruttrice);
	DDX_Control(pDX, IDC_RADIO_DESTINATARIO_CERTIFICATI, m_rbDestinatario_Certificati);
	DDX_Text(pDX, IDC_EDIT_RAGIONE_SOCIALE, m_csRagione_Sociale);
	DDV_MaxChars(pDX, m_csRagione_Sociale, 64);
	DDX_Text(pDX, IDC_EDIT_CODICE, m_csCodice);
	DDX_Check(pDX, IDC_CHK_VERBALI_APERTI, m_chkVerbaliAperti);
	DDX_Text(pDX, IDC_EDIT_DANUMERO, m_csDaNumero);
	DDX_Text(pDX, IDC_EDIT_ANUMERO, m_csANumero);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArchivioVerbaliView, CFormView)
	//{{AFX_MSG_MAP(CArchivioVerbaliView)
	ON_BN_CLICKED(IDC_BUTTON_RICERCA, OnButtonRicerca)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RISULTATO_RICERCA, OnDblclkListRisultatoRicerca)
	ON_BN_CLICKED(IDC_BUTTON_RICERCA_AVANZATA, OnButtonRicercaAvanzata)
	ON_COMMAND(IDD_OPEN_DOC, OnOpenDoc)
	ON_COMMAND(IDD_PREVIEW_DOC, OnPreviewDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArchivioVerbaliView diagnostics

#ifdef _DEBUG
void CArchivioVerbaliView::AssertValid() const
{
	CFormView::AssertValid();
}

void CArchivioVerbaliView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CArchivioVerbaliView message handlers

void CArchivioVerbaliView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	m_pSetVerbali = NULL;
	m_pSetVerbali = new CVerbaliSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
  m_pSetVerbali->m_strFilter.Format("ProgressivoParziale = 1");
	m_pSetVerbali->m_strSort = "DataAccettazione DESC";
	m_pSetVerbali->Open();

  int n = 0, anno = 0;
  CString str;
	//Carica gli anni nella combo
  m_cmbAnni.ResetContent();
  n = m_cmbAnni.AddString("Tutti");
  anno = 0;
  m_cmbAnni.SetItemData(n, anno);
  n++;
  for(SET_START(m_pSetVerbali); !m_pSetVerbali->IsEOF(); m_pSetVerbali->MoveNext())
  {
    if(anno != m_pSetVerbali->m_DataAccettazione.GetYear())
    {
      str = m_pSetVerbali->m_DataAccettazione.Format("%Y");
      if(m_cmbAnni.FindStringExact(-1, str))
      {
        m_cmbAnni.InsertString(n, str);
        anno = m_pSetVerbali->m_DataAccettazione.GetYear();
        m_cmbAnni.SetItemData(n, anno);
        n++;
      }
    }
  }
  m_cmbAnni.SetCurSel(0);

  //m_pSetVerbali->m_strFilter.Format("DataChiusura is not null AND TipoVerbale <> %d AND TipoVerbale <> %d", VERB_PER_FATTURA, VERB_PER_NOTACREDITO);
	//m_pSetVerbali->m_strSort = "Codice";
  //m_pSetVerbali->Requery();

  //Seleziona il primo radio button come default
	m_rbIntestazione_Certificati.SetCheck(1);

	//Definisce lo stile della ListView
	unsigned long style = m_Risultati_Ricerca.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT;
	m_Risultati_Ricerca.SetExtendedStyle(style);
	
	//Inserisce le colonne con le relative intestazioni nella lista
	m_Risultati_Ricerca.InsertColumn(0,"Data",LVCFMT_CENTER, 60, -1);
	m_Risultati_Ricerca.InsertColumn(1,"Numero",LVCFMT_CENTER, 70, -1);
	m_Risultati_Ricerca.InsertColumn(2,"Int.certificati",LVCFMT_CENTER, 165, -1);
	m_Risultati_Ricerca.InsertColumn(3,"Int.fatture",LVCFMT_CENTER, 165, -1);
	m_Risultati_Ricerca.InsertColumn(4,"Impresa esecutrice",LVCFMT_CENTER, 165, -1);
  m_Risultati_Ricerca.InsertColumn(5, "Stato", LVCFMT_CENTER, 60, -1);
  m_Risultati_Ricerca.InsertColumn(6, "Fattura", LVCFMT_CENTER, 55, -1);
  m_Risultati_Ricerca.InsertColumn(7, "Materiale", LVCFMT_CENTER, 185, -1);
  m_Risultati_Ricerca.DeleteAllItems();
}

void CArchivioVerbaliView::OnButtonRicerca() 
{
  UpdateData();

  if(m_csDaNumero.FindOneOf(STR_VERIFY_LETTERE) >= 0)
  {
    AfxMessageBox("Il valore del campo 'Numero' deve essere numerico.");
    return;
  }
	//Esecuzione della query
	Query(m_chkVerbaliAperti);

	//Popolamento della lista con il risultato della Query
	Popola_Lista();
}

void CArchivioVerbaliView::OnDblclkListRisultatoRicerca(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos;
	if((pos = m_Risultati_Ricerca.GetFirstSelectedItemPosition()) == NULL)
	{
		AfxMessageBox("Selezionare un documento.");
		return;
	}
	int n = m_Risultati_Ricerca.GetNextSelectedItem(pos);
	
	if ( m_Risultati_Ricerca.GetItemText(n,5) != "Aperto" )
		ApriDocumento();
	else
		AfxMessageBox("Il verbale è già aperto.");
}

void CArchivioVerbaliView::OnOpenDoc() 
{
  ApriDocumento();
}


void CArchivioVerbaliView::OnButtonRicercaAvanzata() 
{
	CWinSigmaApp*	pApp	= (CWinSigmaApp*)AfxGetApp();
	CFindVerbaliDlg dlg;
  
  dlg.m_bChiusi = TRUE;
  dlg.m_nAnnoAccettazione = 0;
  dlg.m_nChiaveRicerca = 0;
  if(dlg.DoModal() == IDOK)
  {
    CString str;
    long lCodice = dlg.m_nCodiceVerbale;
    m_pSetVerbali->m_strFilter.Format("Codice = %ld", lCodice);
    m_pSetVerbali->Requery();
    Popola_Lista();
  }
}



void CArchivioVerbaliView::OnPreviewDoc() 
{
  POSITION pos;
  if((pos = m_Risultati_Ricerca.GetFirstSelectedItemPosition()) == NULL)
  {
    AfxMessageBox("Selezionare un documento.");
    return;
  }
  CPrintPreviewVerbali prnVerbali;
	CPreviewDlg dlg;
	int n = m_Risultati_Ricerca.GetNextSelectedItem(pos);		
	if (n > -1)
	{
		dlg.m_pPrintPreviewDoc = &prnVerbali;
		dlg.m_nCodice = (long)m_Risultati_Ricerca.GetItemData(n);
		dlg.DoModal();
	}
}


void CArchivioVerbaliView::ApriDocumento()
{	
  POSITION pos;
  if((pos = m_Risultati_Ricerca.GetFirstSelectedItemPosition()) == NULL)
  {
    AfxMessageBox("Selezionare un documento.");
    return;
  }
  int n = m_Risultati_Ricerca.GetNextSelectedItem(pos);
  if(n < 0)
    return;
	CWinSigmaApp*	pApp	= (CWinSigmaApp*)AfxGetApp();
  CString str;
  long lCodice;

  str.Format("Riaprire il verbale %s del %s?",
  					 m_Risultati_Ricerca.GetItemText(n, 1),
  					 m_Risultati_Ricerca.GetItemText(n, 0));

  lCodice = (long)m_Risultati_Ricerca.GetItemData(n);
  if(AfxMessageBox(str, MB_YESNO) == IDYES)
  {
    SetCursor(LoadCursor(NULL, IDC_WAIT));
  	pApp->ReopenVerbale(lCodice);
    m_pSetVerbali->m_strFilter.Format("Codice = %ld", lCodice);
    m_pSetVerbali->Requery();
    if(m_pSetVerbali->m_DataAccettazione.GetMonth() == CTime::GetCurrentTime().GetMonth())
  	  pApp->ReloadTree(TREELABEL_VERBALIULTIMOMESE, lCodice);
    else
      pApp->ReloadTree(TREELABEL_VERBALIPRECEDENTI, lCodice);
    m_Risultati_Ricerca.DeleteItem(n);
  }
}
