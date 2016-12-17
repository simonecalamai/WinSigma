// ArchivioFattureView.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "PrintPreviewFatture.h"
#include "ArchivioFattureView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define DATA_COL          1
#define NUMERO_COL        2
#define TIPO_COL          3
#define INTESTATARIO_COL  4
#define IMPORTO_COL       5
#define SCADENZA_COL      6
#define VERBALI_COL       7

/////////////////////////////////////////////////////////////////////////////
// CArchivioFattureView

IMPLEMENT_DYNCREATE(CArchivioFattureView, CFormView)

CArchivioFattureView::CArchivioFattureView()
	: CFormView(CArchivioFattureView::IDD)
{
	//{{AFX_DATA_INIT(CArchivioFattureView)
	m_csRagione_Sociale = _T("");
	m_csCodice = _T("");
	m_csPartita_IVA = _T("");
	m_csNumero_Verbale = _T("");
	m_strNumFattura = _T("");
	//}}AFX_DATA_INIT
}

CArchivioFattureView::~CArchivioFattureView()
{
	//Chiusura recordSet Testata Fattura
  if(m_pFattureSet)
  {
  	m_pFattureSet->Close();
  	delete m_pFattureSet;
  }

	//Chiusura RecordSet Righe Fattura
  if(m_pVerbaliSet)
  {
  	m_pVerbaliSet->Close();
  	delete m_pVerbaliSet;
  }
}

void CArchivioFattureView::Query()
{
	//Stringa SQL per la Query
	CString sql_Fatture;
  CString sql_Verbali;
	//Stringa di appoggio per la gestione dell'anno all'interno della data 
	CString strApp, str;
  int year = 0;  
	//Si caricano i dati nelle variabili
	UpdateData(TRUE);

  // Anno
  if(m_cmbAnni.GetCurSel() != -1)
	  year = m_cmbAnni.GetItemData(m_cmbAnni.GetCurSel());
	if(year != 0)
    sql_Fatture.Format("Data >= '%s' AND Data <= '%s'", CTime(year, 1, 1, 0, 0, 0).Format("%Y-%m-%d"), CTime(year, 12, 31, 0, 0, 0).Format("%Y-%m-%d"));

  // Numero fattura
  if(!m_strNumFattura.IsEmpty())
  {
    if(sql_Fatture.IsEmpty())
      strApp.Format("Numero = '%s'", m_strNumFattura);
    else
      strApp.Format(" AND Numero = '%s'", m_strNumFattura);
    sql_Fatture += strApp;
  	m_pFattureSet->m_strFilter = sql_Fatture;
    m_pFattureSet->m_strSort = "Data,Numero";
  	m_pFattureSet->Requery();
    return;
  }
  
  // Numero verbale
  if(!m_csNumero_Verbale.IsEmpty())
  {
		sql_Verbali.Format("ProgressivoTotale = '%s'", m_csNumero_Verbale);
    m_pVerbaliSet->m_strFilter = sql_Verbali;
    m_pVerbaliSet->m_strSort = "Fattura";
    m_pVerbaliSet->Requery();

    // Ho il codice della fattura: faccio la requery ed esco
    int g(0);
    for (g = 0; !m_pVerbaliSet->IsEOF(); m_pVerbaliSet->MoveNext(), g++)
    {
      if(sql_Fatture.IsEmpty())
        sql_Fatture.Format("(Codice = %d", m_pVerbaliSet->m_NumeroFattura);
      else if(g == 0)
      {
        strApp.Format(" AND (Codice = %d", m_pVerbaliSet->m_NumeroFattura);
        sql_Fatture += strApp;
      }
      else
      {
        strApp.Format(" OR Codice = %d", m_pVerbaliSet->m_NumeroFattura);
        sql_Fatture += strApp;
      }
    }
    if (g > 0)
    {
        strApp.Format(")");
        sql_Fatture += strApp;
    }

  	m_pFattureSet->m_strFilter = sql_Fatture;
    m_pFattureSet->m_strSort = "Data,Numero";
  	m_pFattureSet->Requery();
    return;
  }

  // Ragione sociale
	if(!m_csRagione_Sociale.IsEmpty())
	{
		m_csRagione_Sociale.Replace("'", "''");
    strApp = "%" + m_csRagione_Sociale + "%";
		if(sql_Fatture.IsEmpty())
			sql_Fatture.Format("RagioneSociale LIKE '%s'", strApp);
		else
    {
      str.Format(" AND RagioneSociale LIKE '%s'", strApp);
			sql_Fatture += str;
    }
	}

  // Partita IVA
  if(!m_csPartita_IVA.IsEmpty())
  {
  	m_csPartita_IVA.Replace("'", "''");
    strApp.Format(" AND P_IVA LIKE '%s%%'", m_csPartita_IVA);
    if(sql_Fatture.IsEmpty())
      sql_Fatture.Format("P_IVA LIKE '%s%%'", m_csPartita_IVA);
    else
      sql_Fatture += strApp;
  }

  // Codice cliente
  if(!m_csCodice.IsEmpty())
  {
    strApp = "%" + m_csCodice + "%";
    if(sql_Fatture.IsEmpty())
      sql_Fatture.Format("IDIntestario LIKE '%s'", strApp);
    else
    {
      str.Format(" AND IDIntestario LIKE '%s'", strApp);
      sql_Fatture += str;
    }
  }
  
  // Faccio la query sulle fatture e sui verbali
	m_pFattureSet->m_strFilter = sql_Fatture;
  m_pFattureSet->m_strSort = "Data,Numero";
	m_pFattureSet->Requery();
}

void CArchivioFattureView::Popola_Lista()
{
  int n;
  CString str, strApp;
	//Ripulisce la Lista
	m_Risultati_Ricerca.DeleteAllItems();
  CString strIndirizzo;
  CPrintPreviewFatture prnPreview;
			
  SetCursor(LoadCursor(NULL, IDC_WAIT));
  // Riempio la lista coi risultati trovati
  for(SET_START(m_pFattureSet); !m_pFattureSet->IsEOF(); m_pFattureSet->MoveNext())
  {
    n = m_Risultati_Ricerca.GetItemCount();
    m_Risultati_Ricerca.InsertItem(n, "");
    m_Risultati_Ricerca.SetItemData(n, (DWORD)m_pFattureSet->m_Codice);
    m_Risultati_Ricerca.SetItemText(n, DATA_COL, m_pFattureSet->m_Data.Format("%d/%m/%y"));
    str.Format("%d", m_pFattureSet->m_Numero);
    m_Risultati_Ricerca.SetItemText(n, NUMERO_COL, str);
    if(m_pFattureSet->m_TipoDocumento == FATTURA)
      m_Risultati_Ricerca.SetItemText(n, TIPO_COL, "Fattura");
    else
      m_Risultati_Ricerca.SetItemText(n, TIPO_COL, "Nota di credito");
    strIndirizzo = m_pFattureSet->m_Indirizzo;
  	strIndirizzo = m_pFattureSet->m_Indirizzo;
  	strIndirizzo += " - ";
  	if(!m_pFattureSet->m_CAP.IsEmpty())
  	{
  	  strIndirizzo += m_pFattureSet->m_CAP + " ";
  	}
  	strIndirizzo += m_pFattureSet->m_Citta;
  	if(!m_pFattureSet->m_Provincia.IsEmpty())
  	{
  	  str.Format(" (%s)", m_pFattureSet->m_Provincia);
  		strIndirizzo += str;
    }
    m_Risultati_Ricerca.SetItemText(n, INTESTATARIO_COL, m_pFattureSet->m_RagioneSociale /*+ strIndirizzo*/);
    Valuta importo(m_pFattureSet->m_Imponibile);
    m_Risultati_Ricerca.SetItemText(n, IMPORTO_COL, importo.Format());
    if(!m_pFattureSet->IsFieldNull(&m_pFattureSet->m_Scadenza))
      str = m_pFattureSet->m_Scadenza.Format("%d/%m/%y");
    else
      str.Empty();
    m_Risultati_Ricerca.SetItemText(n, SCADENZA_COL, str);
    str.Empty();
    // Verbali fatturati con questa fattura
    m_pVerbaliSet->m_strFilter.Format("Fattura = %ld", m_pFattureSet->m_Codice);
    m_pVerbaliSet->Requery();
    for(SET_START(m_pVerbaliSet); !m_pVerbaliSet->IsEOF(); m_pVerbaliSet->MoveNext())
    {
      if(m_pVerbaliSet->m_TipoVerbale != VERB_PER_FATTURA && m_pVerbaliSet->m_TipoVerbale != VERB_PER_NOTACREDITO)// && m_pVerbaliSet->m_NumeroFattura == m_pFattureSet->m_Codice)
      {
        strApp.Format("%d - ", m_pVerbaliSet->m_ProgressivoTotale);
        str += strApp;
      }
    }
    str.TrimRight(" - ");
    m_Risultati_Ricerca.SetItemText(n, VERBALI_COL, str);
  }
}

void CArchivioFattureView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArchivioFattureView)
	DDX_Control(pDX, IDC_COMBO_ANNO, m_cmbAnni);
	DDX_Control(pDX, IDC_LIST_RISULTATO_RICERCA, m_Risultati_Ricerca);
	DDX_Text(pDX, IDC_EDIT_RAGIONE_SOCIALE, m_csRagione_Sociale);
	DDV_MaxChars(pDX, m_csRagione_Sociale, 64);
	DDX_Text(pDX, IDC_EDIT_CODICE, m_csCodice);
	DDX_Text(pDX, IDC_EDIT_PARTITA_IVA, m_csPartita_IVA);
	DDV_MaxChars(pDX, m_csPartita_IVA, 16);
	DDX_Text(pDX, IDC_EDIT_NUMERO_VERBALE, m_csNumero_Verbale);
	DDX_Text(pDX, IDC_EDIT_NUM_FATTURA, m_strNumFattura);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArchivioFattureView, CFormView)
	//{{AFX_MSG_MAP(CArchivioFattureView)
	ON_BN_CLICKED(IDC_BUTTON_RICERCA, OnButtonRicerca)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RISULTATO_RICERCA, OnDblclkListRisultatoRicerca)
	ON_COMMAND(ID_FATTURA_STAMPA_MULTIPLA, OnFatturaStampaMultipla)
	ON_COMMAND(ID_FATTURA_STAMPA_SINGOLA, OnFatturaStampaSingola)
	ON_COMMAND(ID_ARCHIVIOFATTURE_STAMPA_DOPPIACOPIASENZAHEADER, OnFatturaStampaMultiplaNoHeader)
	ON_COMMAND(ID_ARCHIVIOFATTURE_STAMPA_SINGOLACOPIASENZAHEADER, OnFatturaStampaSingolaNoHeader)
	ON_COMMAND(ID_RIPRISTINA_FATTURA, OnRipristinaFattura)
	ON_COMMAND(IDD_PREVIEW_DOC, OnPreviewDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArchivioFattureView diagnostics

#ifdef _DEBUG
void CArchivioFattureView::AssertValid() const
{
	CFormView::AssertValid();
}

void CArchivioFattureView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CArchivioFattureView message handlers

void CArchivioFattureView::OnInitialUpdate() 
{
  int year = 0;
	CFormView::OnInitialUpdate();

  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	//Recordset Testata Fattura
	m_pFattureSet = new CFattureSet(&pApp->m_db);
  m_pFattureSet->m_strFilter = "Data is not null";
	m_pFattureSet->m_strSort = "Data";
	m_pFattureSet->Open();
	//RecordSet Verbali fatturati
  m_pVerbaliSet = new CVerbaliSet(&pApp->m_db);
  m_pVerbaliSet->m_strFilter = "Fattura <> 0";
  m_pVerbaliSet->Open();
  //Definizione delle Style della Lista e delle intestazioni delle colonne
	unsigned long style = m_Risultati_Ricerca.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT;
	m_Risultati_Ricerca.SetExtendedStyle(style);

  m_Risultati_Ricerca.InsertColumn(0, "", LVCFMT_LEFT, 0);
	m_Risultati_Ricerca.InsertColumn(DATA_COL, "Data", LVCFMT_CENTER, 80, -1);
	m_Risultati_Ricerca.InsertColumn(NUMERO_COL, "Numero", LVCFMT_CENTER, 54, -1);
  m_Risultati_Ricerca.InsertColumn(TIPO_COL, "Documento", LVCFMT_LEFT, 86, -1);
	m_Risultati_Ricerca.InsertColumn(INTESTATARIO_COL, "Intestatario", LVCFMT_LEFT, 250, -1);
	m_Risultati_Ricerca.InsertColumn(IMPORTO_COL, "Importo", LVCFMT_RIGHT, 80, -1);
  m_Risultati_Ricerca.InsertColumn(SCADENZA_COL, "Scadenza", LVCFMT_CENTER, 80, -1);
  m_Risultati_Ricerca.InsertColumn(VERBALI_COL, "Verbali", LVCFMT_CENTER, 110, -1);

  // Caricamento degli anni nella combo
  m_cmbAnni.ResetContent();
  int n = m_cmbAnni.AddString("Tutti");
  m_cmbAnni.SetItemData(n, 0);
  n++;
  year = 0;
  for(SET_START(m_pFattureSet); !m_pFattureSet->IsEOF(); m_pFattureSet->MoveNext())
  {
    if(year != m_pFattureSet->m_Data.GetYear())
    {
      m_cmbAnni.InsertString(n, m_pFattureSet->m_Data.Format("%Y"));
      year = m_pFattureSet->m_Data.GetYear();
      m_cmbAnni.SetItemData(n, year);
      n++;
    }
  }
	//Seleziona come Item corrente quello vuoto
	m_cmbAnni.SetCurSel(0);
}

void CArchivioFattureView::OnButtonRicerca() 
{
	//Controlla la congruenza dei dati presenti nei campi di selezione della Query
	CString msg("");
  if(m_csNumero_Verbale.FindOneOf("AaBbCcDdEeFfGgHhIiLlMmNnOoPpQqRrSsTtUuVvZzXxYyWwJjKk") >= 0)
  {
    AfxMessageBox("Il valore del campo 'Numero verbale' deve essere numerico.");
    return;
  }
	//Esecuzione della query
	Query();

	//Popolamento della lista con il risultato della Query
	Popola_Lista();
  UpdateData(FALSE);
}

void CArchivioFattureView::OnDblclkListRisultatoRicerca(NMHDR* pNMHDR, LRESULT* pResult) 
{
  OnRipristinaFattura();
	*pResult = 0;
}



void CArchivioFattureView::OnFatturaStampaMultipla() 
{
  PrintFattura(FALSE, TRUE);
}

void CArchivioFattureView::OnFatturaStampaSingola() 
{
  PrintFattura(FALSE, FALSE);
}

void CArchivioFattureView::OnFatturaStampaMultiplaNoHeader() 
{
  PrintFattura(FALSE, TRUE, FALSE);
}

void CArchivioFattureView::OnFatturaStampaSingolaNoHeader() 
{
  PrintFattura(FALSE, FALSE, FALSE);
}

void CArchivioFattureView::PrintFattura(BOOL bAnteprima, BOOL bDoppiaCopia, BOOL bHeader)
{
  int n;
  POSITION pos;
  CString str;
  if((pos = m_Risultati_Ricerca.GetFirstSelectedItemPosition()) == NULL)
  {
    AfxMessageBox("Selezionare un dato valido");
    return;
  }
  CPrintPreviewFatture prnPreview;
	CPreviewDlg dlg;
			
	dlg.m_pPrintPreviewDoc = &prnPreview;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  n = m_Risultati_Ricerca.GetNextSelectedItem(pos);
  long codice = (long)m_Risultati_Ricerca.GetItemData(n);
  SINCRONIZE(m_pFattureSet, codice);
  // Inizializzo i dati per la stampa
  prnPreview.m_lCodiceFattura = m_pFattureSet->m_Codice;
  prnPreview.m_lCodiceAzienda = m_pFattureSet->m_Intestatario;
  prnPreview.m_bPrintProForma = FALSE;
  if(m_pFattureSet->m_Spese)
    prnPreview.m_bSpedSelezionata = TRUE;
  else
    prnPreview.m_bSpedSelezionata = FALSE;
  if(bDoppiaCopia)
    prnPreview.m_nNumeroCopie = 2;
  else
    prnPreview.m_nNumeroCopie = 1;
  prnPreview.m_dAliquota = m_pFattureSet->m_Aliquota;
  prnPreview.m_dSconto = m_pFattureSet->m_Sconto;
  prnPreview.m_dSpeseSpedizione = m_pFattureSet->m_Spese;
  prnPreview.m_dImportoFattura = m_pFattureSet->m_Imponibile;
  prnPreview.m_bRaggruppaPerServizio = FALSE;
	if(m_pFattureSet->m_Elett == TRUE)
	  prnPreview.m_strTipoDocumento = m_Risultati_Ricerca.GetItemText(n, TIPO_COL) + " elettronica ";
	else
	  prnPreview.m_strTipoDocumento = m_Risultati_Ricerca.GetItemText(n, TIPO_COL);
	prnPreview.SetHeader(bHeader);
  if(bAnteprima)
    if(dlg.DoModal() != IDOK)
      return;
  prnPreview.Print(0, NULL, NULL);
}

void CArchivioFattureView::OnRipristinaFattura() 
{
  int n;
  POSITION pos;
  CString str;
  if((pos = m_Risultati_Ricerca.GetFirstSelectedItemPosition()) == NULL)
  {
    AfxMessageBox("Selezionare un dato valido");
    return;
  }
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  n = m_Risultati_Ricerca.GetNextSelectedItem(pos);
  long codice = (long)m_Risultati_Ricerca.GetItemData(n);
  SINCRONIZE(m_pFattureSet, codice);
  if(!m_pFattureSet->m_Archiviata)
  {
    AfxMessageBox("La fattura non risulta archiviata.");
//    MessageBeep(-1);
    return;
  }
  if(m_pFattureSet->m_TipoDocumento == FATTURA)
    str.Format("Ripristinare la fattura n %d del %s?", m_pFattureSet->m_Numero, m_pFattureSet->m_Data.Format("%d/%m/%Y"));
  else
    str.Format("Ripristinare la nota di credito n %d del %s?", m_pFattureSet->m_Numero, m_pFattureSet->m_Data.Format("%d/%m/%Y"));
  if(AfxMessageBox(str, MB_YESNO) == IDYES)
  {
    pApp->LockTable(FATTURE);
    m_pFattureSet->Edit();
    m_pFattureSet->m_Archiviata = 0;
    m_pFattureSet->Update();
    m_pFattureSet->Requery();
    pApp->UnlockTables();
    SINCRONIZE(m_pFattureSet, codice);
    pApp->ReloadTree(m_pFattureSet->m_Data.Format("%Y"), m_pFattureSet->m_Codice);
  }
}

void CArchivioFattureView::OnPreviewDoc() 
{
  PrintFattura(TRUE, FALSE);
}
