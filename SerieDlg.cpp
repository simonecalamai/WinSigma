// SerieDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "XDialog.h"
#include "WinSigmaDoc.h"
#include "SerieDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define STR_DATAND "- n. d. -"
#define STR_DATAND_12390 "> 28 gg"
/////////////////////////////////////////////////////////////////////////////
// CSerieDlg dialog


CSerieDlg::CSerieDlg(CWnd* pParent /*=NULL*/)
	: CXDialog(CSerieDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSerieDlg)
	m_bNuovoCertificato = FALSE;
	m_strPosizione = _T("");
	m_DataPrelievo = 0;
	m_strSigla = _T("");
	m_strStruttura = _T("");
	m_StaticDim1 = _T("");
	m_StaticDim2 = _T("");
	m_StaticDim3 = _T("");
	m_nProviniRichiesti = 0;
	m_nNumeroServizi = 0;
	m_bListinoGenerale = FALSE;
	m_dDimensione1 = 0.0;
	m_dDimensione2 = 0.0;
	m_dDimensione3 = 0.0;
	m_strMateriale = _T("");
	m_bNonDichiarata = FALSE;
	m_strDataND = _T("");
	m_DataScadenza = 0;
	m_sSiglaFornitore = _T("");
	m_sVerbalePrelievo = _T("");
	m_csOsservazioni = _T("");
	m_strSigla2 = _T("");
	//}}AFX_DATA_INIT
  m_pDoc = NULL;
  m_pTCertificatoSet = NULL;
  m_pCatServSet = NULL;
  m_pSerieSet = NULL;
  m_bEnableTipo = m_bEnableNuovo = TRUE;
  m_bProva = FALSE;
  m_nListinoGenerale = -1;
  m_nListinoParticolare = -1;
	m_nMaxProviniXCertificato = 0;
}

CSerieDlg::~CSerieDlg()
{
  if(m_pSerieSet)
  {
    m_pSerieSet->Close();
    delete m_pSerieSet;
  }
  if(m_pCatServSet)
  {
    m_pCatServSet->Close();
    delete m_pCatServSet;
  }
  if(m_pMaterialiSet)
  {
    m_pMaterialiSet->Close();
    delete m_pMaterialiSet;
  }
}

void CSerieDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSerieDlg)
	DDX_Control(pDX, IDC_EDIT_SIGLA2, m_EditSigla2);
	DDX_Control(pDX, IDC_STATIC_SIGLA2, m_StaticSigla2);
	DDX_Control(pDX, IDC_EDIT_OSSERVAZIONI, m_ctrlOsservazioni);
	DDX_Control(pDX, IDC_EDIT_VERBALE_PRELIEVO, m_ctrlVerbalePrelievo);
	DDX_Control(pDX, IDC_EDIT_SIGLA_FORNITORE, m_ctrlSiglaFornitore);
	DDX_Control(pDX, IDC_DATETIMEPICKER_SCADENZA, m_DTCtrlScadenza);
	DDX_Control(pDX, IDC_EDIT_DATA_ND, m_ctrDataND);
	DDX_Control(pDX, IDC_CHECK_NON_DICHIARATA, m_BtnNonDichiarata);
	DDX_Control(pDX, IDC_COMBO_MATERIALE, m_ComboMateriale);
	DDX_Control(pDX, IDC_CHECK_LISTINO, m_BtnListinoGenerale);
	DDX_Control(pDX, IDC_STATIC_STRUTTURA, m_StaticStruttura);
	DDX_Control(pDX, IDC_STATIC_SIGLA, m_StaticSigla);
	DDX_Control(pDX, IDC_STATIC_MATERIALE, m_StaticMateriale);
	DDX_Control(pDX, IDC_EDIT_STRUTTURA, m_EditStruttura);
	DDX_Control(pDX, IDC_EDIT_SIGLA, m_EditSigla);
	DDX_Control(pDX, IDC_EDIT_DIM1, m_EditDimensione1);
	DDX_Control(pDX, IDC_EDIT_DIM2, m_EditDimensione2);
	DDX_Control(pDX, IDC_EDIT_DIM3, m_EditDimensione3);
	DDX_Control(pDX, IDC_DATETIMEPICKER_PRELIEVO, m_DateCtrlPrelievo);
	DDX_Control(pDX, IDOK, m_BtnOk);
	DDX_Control(pDX, IDCANCEL, m_BtnCancel);
	DDX_Control(pDX, IDC_LIST_SERVIZI, m_ListServizi);
	DDX_Control(pDX, IDC_CHECK_NUOVOCERT, m_BtnNuovoCertificato);
	DDX_Control(pDX, IDC_COMBO_TIPI_CERTIFICATO, m_ComboTipoCertificato);
	DDX_Check(pDX, IDC_CHECK_NUOVOCERT, m_bNuovoCertificato);
	DDX_Text(pDX, IDC_EDIT_POSIZIONE, m_strPosizione);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_PRELIEVO, m_DataPrelievo);
	DDX_Text(pDX, IDC_EDIT_SIGLA, m_strSigla);
	DDV_MaxChars(pDX, m_strSigla, 14);
	DDX_Text(pDX, IDC_EDIT_STRUTTURA, m_strStruttura);
	DDV_MaxChars(pDX, m_strStruttura, 44);
	DDX_Text(pDX, IDC_STATIC_DIM1, m_StaticDim1);
	DDX_Text(pDX, IDC_STATIC_DIM2, m_StaticDim2);
	DDX_Text(pDX, IDC_STATIC_DIM3, m_StaticDim3);
	DDX_Text(pDX, IDC_EDIT_RICHIESTI, m_nProviniRichiesti);
	DDX_Text(pDX, IDC_EDIT_NUMSERVIZI, m_nNumeroServizi);
	DDX_Check(pDX, IDC_CHECK_LISTINO, m_bListinoGenerale);
	DDX_Text(pDX, IDC_EDIT_DIM1, m_dDimensione1);
	DDX_Text(pDX, IDC_EDIT_DIM2, m_dDimensione2);
	DDX_Text(pDX, IDC_EDIT_DIM3, m_dDimensione3);
	DDX_CBString(pDX, IDC_COMBO_MATERIALE, m_strMateriale);
	DDX_Check(pDX, IDC_CHECK_NON_DICHIARATA, m_bNonDichiarata);
	DDX_Text(pDX, IDC_EDIT_DATA_ND, m_strDataND);
	DDV_MaxChars(pDX, m_strDataND, 10);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_SCADENZA, m_DataScadenza);
	DDX_Text(pDX, IDC_EDIT_SIGLA_FORNITORE, m_sSiglaFornitore);
	DDX_Text(pDX, IDC_EDIT_VERBALE_PRELIEVO, m_sVerbalePrelievo);
	DDV_MaxChars(pDX, m_sVerbalePrelievo, 16);
	DDX_Text(pDX, IDC_EDIT_OSSERVAZIONI, m_csOsservazioni);
	DDX_Text(pDX, IDC_EDIT_SIGLA2, m_strSigla2);
	DDV_MaxChars(pDX, m_strSigla2, 14);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSerieDlg, CXDialog)
	//{{AFX_MSG_MAP(CSerieDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_TIPI_CERTIFICATO, OnSelchangeTipiCertificato)
	ON_BN_CLICKED(IDC_CHECK_NUOVOCERT, OnCheckNuovoCertificato)
	ON_BN_CLICKED(IDC_CHECK_LISTINO, OnCheckListino)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SERVIZI, OnItemchangedListServizi)
	ON_BN_CLICKED(IDC_CHECK_NON_DICHIARATA, OnCheckNonDichiarata)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_CBN_SELCHANGE(IDC_COMBO_MATERIALE, OnSelchangeComboMateriale)
	ON_EN_KILLFOCUS(IDC_EDIT_STRUTTURA, OnKillfocusEditStruttura)
	ON_NOTIFY(DTN_CLOSEUP, IDC_DATETIMEPICKER_PRELIEVO, OnCloseupDatetimepickerPrelievo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSerieDlg message handlers
BOOL CSerieDlg::OnInitDialog() 
{  
  if(!m_pDoc)
    return FALSE;
  
  CString str;
	DWORD style;
  int n;
  
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CXDialog::OnInitDialog();
	SetWindowText(m_strTitolo);

	
	// controlli sigla2 non visibili di default
	m_StaticSigla2.ShowWindow(SW_HIDE);
	m_EditSigla2.ShowWindow(SW_HIDE);;

	// Inizializza i controlli
	m_sVerbalePrelievo.Empty();
	m_sSiglaFornitore.Empty();

  // Lista dei servizi
  style = m_ListServizi.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES;
	m_ListServizi.SetExtendedStyle(style);
  m_ListServizi.InsertColumn(0, "Codice", LVCFMT_LEFT, 65, -1);
	m_ListServizi.InsertColumn(1, "Descrizione", LVCFMT_LEFT, 468, -1);
  m_pSerieSet	= new CSerieSet(&pApp->m_db);
  if(m_nNumeroVerbale > 0)
    m_pSerieSet->m_strFilter.Format("Verbale = %d", m_nNumeroVerbale);
  m_pSerieSet->Open();
	m_pMaterialiSet = new CTipiMaterialeSet(&pApp->m_db);
  m_pMaterialiSet->m_strFilter = "Codice = 0";
  m_pMaterialiSet->Open();
  // Carico la lista dei tipi di certificato
  m_pTCertificatoSet = m_pDoc->m_pTipiCertificatoSet;
  n = m_ComboTipoCertificato.AddString("--- Nessuno ---");
	m_ComboTipoCertificato.SetItemData(n, 0);
  m_ComboTipoCertificato.SetCurSel(0);
  for(SET_START(m_pTCertificatoSet); !m_pTCertificatoSet->IsEOF(); m_pTCertificatoSet->MoveNext())
  {
		if(m_pTCertificatoSet->m_Attivo == 1)
		{
			str.Format("%d - %s", m_pTCertificatoSet->m_Codice, m_pTCertificatoSet->m_Nome);
			n = m_ComboTipoCertificato.AddString(str);
			m_ComboTipoCertificato.SetItemData(n, m_pTCertificatoSet->m_Codice);
		}
  }
  // Posizione serie/certificato
  if((n = m_strPosizione.ReverseFind('/')) == -1)
    m_nPosSerie = atoi(m_strPosizione);
  else
  {  
    CString str1, str2;
    m_nCertificato = atoi(m_strPosizione.Mid(n + 1, 1));
    n = m_strPosizione.Find('/');
    m_nPosSerie = atoi(m_strPosizione.Mid(0, n));
  }
  m_BtnNuovoCertificato.EnableWindow(m_bEnableNuovo);
  m_ComboTipoCertificato.EnableWindow(m_bEnableTipo);
  if(m_bNuovoCertificato)
  {
    if(m_nCertificato == 1 && m_nPosSerie == 1)
      m_nCertificato = 1;
    else
      m_nCertificato++;
    m_nPosSerie = 1;
    m_strPosizione.Format("%d/%d", m_nPosSerie, m_nCertificato);
  }
   // Categorie e servizi associati al listino
  m_pCatServSet = new CCategorieServiziSet(&pApp->m_db);
  m_pCatServSet->m_strFilter.Format("Listino = 0");
  m_pCatServSet->Open();
  SET_START(m_pTCertificatoSet);
  m_arySelectedServices.RemoveAll();
	if(!m_nListinoParticolare)
	{
	  m_bListinoGenerale = TRUE;
		m_BtnListinoGenerale.EnableWindow(FALSE);
  }
	InitDialogData();
	if(!m_bNuovaSerie && !m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Certificato)
	   && m_pSerieSet->m_Certificato)
	{
	  // serie di un certificato gia' emesso: disabilito qualcosa
		m_ComboTipoCertificato.EnableWindow(FALSE);
		m_ListServizi.EnableWindow(FALSE);
		m_BtnNuovoCertificato.EnableWindow(FALSE);
		m_BtnListinoGenerale.EnableWindow(FALSE);
		//m_ComboMateriale.EnableWindow(FALSE);
	}
  if(m_nCodiceSerie != -1)
    m_EditSigla.SetFocus();

  UpdateData(FALSE);
	return FALSE;  
}


void CSerieDlg::OnCancel() 
{
	CDialog::OnCancel();
}

void CSerieDlg::OnOK() 
{
  int i, n;
  int ServiziSelezionati[MAX_SERVIZI_PER_SERIE];
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

  UpdateData();
  if(!ValidateData())
    return; 
  for(i = 0; i < MAX_SERVIZI_PER_SERIE; i++)
    ServiziSelezionati[i] = -1;
  // Aggiungo la nuova serie
  pApp->LockTable(SERIE);
  if(m_bNuovaSerie)
	{
    m_pSerieSet->AddNew();
		m_pSerieSet->m_Certificato = 0;
  }
	else
  {
    // E' una modifica ad una serie già inserita: seleziono e modifico il record
    for(SET_START(m_pSerieSet); !m_pSerieSet->IsEOF(); m_pSerieSet->MoveNext())
    {
      if(m_pSerieSet->m_Verbale == m_nNumeroVerbale && m_pSerieSet->m_Codice == m_nCodiceSerie)
        break;
    }
    m_pSerieSet->Edit();
  }

  UpdateData();
  m_nNumeroProvini = m_nProviniRichiesti;
  m_pSerieSet->m_Verbale						= m_nNumeroVerbale;
  m_pSerieSet->m_TipoCertificato		= m_nCodiceTipoCertificato = m_pTCertificatoSet->m_Codice;
  m_pSerieSet->m_Ordinamento        = m_pTCertificatoSet->m_Ordinamento;

  if(m_bNonDichiarata)
  {
    m_pSerieSet->SetFieldNull(&m_pSerieSet->m_DataPrelievo);
	  m_pSerieSet->m_strDataND = m_strDataND;
    m_pSerieSet->SetFieldNull(&m_pSerieSet->m_DataProva);
  }
  else
  {
	  m_pSerieSet->m_DataPrelievo	= m_DataPrelievo;
    m_pSerieSet->m_strDataND    = "";
    m_pSerieSet->m_DataProva    = m_DataScadenza;
  }
  
  m_pSerieSet->m_NuovoCertificato		= m_bNuovoCertificato;
  m_pSerieSet->m_NumeroProvini			= m_nProviniRichiesti;
  m_pSerieSet->m_StrutturaPrelievo	= m_strStruttura;
  m_pSerieSet->m_Sigla							= m_strSigla;
  m_pSerieSet->m_Sigla2							= m_strSigla2;
  m_pSerieSet->m_Dimensione1				= m_dDimensione1;
  m_pSerieSet->m_Dimensione2				= m_dDimensione2;
  m_pSerieSet->m_Dimensione3				= m_dDimensione3;
  m_pSerieSet->m_Materiale					= m_strMateriale;
	m_pSerieSet->m_Osservazioni				= m_csOsservazioni;
  if ((m_bNonDichiarata) && ((m_strDataND != STR_DATAND) || (m_strDataND != STR_DATAND_12390)))
    m_pSerieSet->m_strDataND = m_strDataND;
  else
    m_pSerieSet->m_strDataND.Empty();
  //////////////////////////////////////////////////////////////////////////////
  // Per Livorno: definisco il codice certificato barre e imposto a uno il check per
  // fare i calcoli con i decimali
  if(pApp->GetProfileInt(CONFIGURAZIONE, CODICE_CERT_BARRE, 0) == (UINT)m_nCodiceTipoCertificato)
    m_pSerieSet->m_Checked = pApp->GetProfileInt(CONFIGURAZIONE, CALCOLO_CON_DECIMALI, 0);
	if((n = m_ComboMateriale.GetCurSel()) < 0 || !m_ComboMateriale.GetItemData(n))
	{
	  m_pSerieSet->m_Snervamento = 0;
		m_pSerieSet->m_IDMateriale.Empty();
	}
	else
	{
    n = m_ComboMateriale.GetItemData(n);
    SINCRONIZE(m_pMaterialiSet, n);
	  m_pSerieSet->m_Snervamento = m_pMaterialiSet->m_Snervamento;
		m_pSerieSet->m_IDMateriale = m_pMaterialiSet->m_ID;
	}

	m_pSerieSet->SetFieldNull(&m_pSerieSet->m_Servizio1);
	m_pSerieSet->SetFieldNull(&m_pSerieSet->m_Servizio2);
	m_pSerieSet->SetFieldNull(&m_pSerieSet->m_Servizio3);
	m_pSerieSet->SetFieldNull(&m_pSerieSet->m_Servizio4);
	m_pSerieSet->SetFieldNull(&m_pSerieSet->m_Servizio5);
	m_pSerieSet->SetFieldNull(&m_pSerieSet->m_Servizio6);

  // Aggiungo i servizi selezionati
  for(i = 0, n = 0; i < m_ListServizi.GetItemCount() && n < MAX_SERVIZI_PER_SERIE; i++)
  {
    if(m_ListServizi.GetCheck(i))
      ServiziSelezionati[n++] = m_ListServizi.GetItemData(i);
  }
  if(ServiziSelezionati[0] != -1)
    m_pSerieSet->m_Servizio1 = ServiziSelezionati[0];
	if(ServiziSelezionati[1] != -1)
    m_pSerieSet->m_Servizio2 = ServiziSelezionati[1];
  if(ServiziSelezionati[2] != -1)
    m_pSerieSet->m_Servizio3 = ServiziSelezionati[2];
  if(ServiziSelezionati[3] != -1)
    m_pSerieSet->m_Servizio4 = ServiziSelezionati[3];
  if(ServiziSelezionati[4] != -1)
    m_pSerieSet->m_Servizio5 = ServiziSelezionati[4];
  if(ServiziSelezionati[5] != -1)
	  m_pSerieSet->m_Servizio6 = ServiziSelezionati[5];

	// Se presenti salva sul DB i valori del Verbale di Prelievo e della Sigla del Fornitore
	if(!m_sVerbalePrelievo.IsEmpty())
	{
		m_pSerieSet->m_VerbalePrelievo = m_sVerbalePrelievo;
	}
	if(!m_sSiglaFornitore.IsEmpty())
	{
		m_pSerieSet->m_SiglaFornitore = m_sSiglaFornitore;
	}

  // Aggiungo il servizio aggiungibile
	m_pSerieSet->m_ServAggiungibile = GetServAggiungibile();
  m_pSerieSet->Update();
  m_pSerieSet->Requery();

  // Se è una nuova serie, la seleziono per averne il codice
  if(m_bNuovaSerie)
  {
    m_nCodiceSerie = 0;
    for(SET_START(m_pSerieSet); !m_pSerieSet->IsEOF(); m_pSerieSet->MoveNext())
    {
      if(m_nCodiceSerie < m_pSerieSet->m_Codice)
        m_nCodiceSerie = m_pSerieSet->m_Codice;
    }
  }
  // Sblocco le tabelle
  pApp->UnlockTables();
	CDialog::OnOK();
}

// Cambio il tipo di certificato
void CSerieDlg::OnSelchangeTipiCertificato() 
{
	m_nNumeroServizi		= 0;
	m_nProviniRichiesti = 0;
  int i;

  if((i = m_ComboTipoCertificato.GetCurSel()) != -1)
  {
    for(SET_START(m_pTCertificatoSet); !m_pTCertificatoSet->IsEOF(); m_pTCertificatoSet->MoveNext())
    {
      if((DWORD)m_pTCertificatoSet->m_Codice == m_ComboTipoCertificato.GetItemData(i))
        break;
    }
		// Ripristino il valore del numero di provini per certificato
		m_nMaxProviniXCertificato = m_pTCertificatoSet->m_ProvXcertificato;
    // Aggiorno il form secondo il nuovo tipo di certificato
    LoadTCertData();
    // Aggiorno la lista dei servizi associati a questo tipo di certificato
    LoadServizi();
	// Aggiorno la combo dei materiali 
	LoadMateriali();
  }
	
  if(m_pSerieSet->m_TipoCertificato != m_pTCertificatoSet->m_Codice)
	{
    // Se è un tipo di certificato diverso da quello precedente->
    // forzo un nuovo certificato
    SetNuovoCertificato(TRUE);
    m_BtnNuovoCertificato.EnableWindow(FALSE);
		
		// Cancello la lista dei servizi selezionati
		m_arySelectedServices.RemoveAll();
		m_bProva = FALSE;
    if(!m_pTCertificatoSet->IsFieldNull(&m_pTCertificatoSet->m_Maturazione) && m_pTCertificatoSet->m_Maturazione != 0)
    {
      CTimeSpan tsMat(m_pTCertificatoSet->m_Maturazione, 0, 0, 0);
      m_DataScadenza = m_DataPrelievo + tsMat;
    }
    else
      m_DataScadenza = CTime::GetCurrentTime();
		UpdateData(FALSE);
	}
	else if(m_bNuovaSerie)
		LoadLastSerie(FALSE);	

	m_bNonDichiarata = TRUE;
	m_BtnNonDichiarata.SetCheck(1);
	m_DateCtrlPrelievo.EnableWindow(FALSE);
  m_DTCtrlScadenza.EnableWindow(FALSE);
  
  i = m_ComboTipoCertificato.GetCurSel();
// questa e' una vera nefandezza !!!! s.c. 22-2-2010
  if ((m_ComboTipoCertificato.GetItemData(i) == 8) || (m_ComboTipoCertificato.GetItemData(i) == 9) ||
				m_ComboTipoCertificato.GetItemData(i) == 12 || 
				m_ComboTipoCertificato.GetItemData(i) == 16)
	{
	  m_strDataND = STR_DATAND_12390;
	}
  else
	{
    m_strDataND = STR_DATAND;
	}

	// Abilita/Disabilita i controlli per l'inserimento del Verbale di Prelievo e della Sigla del Fornitore
	if ((m_ComboTipoCertificato.GetItemData(i) == 11) ||
			(m_ComboTipoCertificato.GetItemData(i) == 12) ||
			(m_ComboTipoCertificato.GetItemData(i) == 13) ||
			(m_ComboTipoCertificato.GetItemData(i) == 16) || 
			(m_ComboTipoCertificato.GetItemData(i) == 17))		
	{
		m_ctrlVerbalePrelievo.EnableWindow(TRUE);
	}
	else
	{
		m_ctrlVerbalePrelievo.EnableWindow(FALSE);
	}
	if ((m_ComboTipoCertificato.GetItemData(i) == 11) ||
			(m_ComboTipoCertificato.GetItemData(i) == 13) || 
			(m_ComboTipoCertificato.GetItemData(i) == 17))
	{
		m_ctrlSiglaFornitore.EnableWindow(TRUE);
	}
	else
	{
		m_ctrlSiglaFornitore.EnableWindow(FALSE);
	}
	if (m_ComboTipoCertificato.GetItemData(i) == 11 ||
	(m_ComboTipoCertificato.GetItemData(i) == 17))
	{
		m_ctrlOsservazioni.EnableWindow(TRUE);
	}
	else
	{
		m_ctrlOsservazioni.EnableWindow(FALSE);
	}
	
  UpdateData(FALSE);	
}

// Inizializza i dati del dialogo
void CSerieDlg::InitDialogData(void)
{
  int n, nServizio;
  
  m_DataPrelievo = CTime::GetCurrentTime();
  m_DataScadenza = CTime::GetCurrentTime();
  
  m_strDataND = STR_DATAND;
  m_nNumeroServizi = 0;
  m_arySelectedServices.RemoveAll();
  if(!m_bNuovaSerie)
  {
    // Devo modificare una serie già inserita: leggo i dati dal db
    if(m_nCodiceSerie != -1 && m_nNumeroVerbale >= 0)
    {
      // Cerco il record della serie da modificare
      for(SET_START(m_pSerieSet); !m_pSerieSet->IsEOF(); m_pSerieSet->MoveNext())
      {
        if(m_pSerieSet->m_Codice == m_nCodiceSerie && m_pSerieSet->m_Verbale == m_nNumeroVerbale)
          break;
      }
      // Tipo di certificato
      for(SET_START(m_pTCertificatoSet); !m_pTCertificatoSet->IsEOF(); m_pTCertificatoSet->MoveNext())
      {
        if(m_pTCertificatoSet->m_Codice == m_pSerieSet->m_TipoCertificato)
          break;
      }
      LoadSeriesData();
      for(n = 0; n < m_ComboTipoCertificato.GetCount(); n++)
      {
        if((int)m_ComboTipoCertificato.GetItemData(n) == m_pTCertificatoSet->m_Codice)
          break;
      }
      if(n < m_ComboTipoCertificato.GetCount())
        m_ComboTipoCertificato.SetCurSel(n);
      else
        m_ComboTipoCertificato.SetCurSel(-1);

      LoadTCertData();
      // Servizi associati a questo tipo di certificato
      LoadServizi();
      // Caricamento dei tipi di materiale x il tipo di certificato

			LoadMateriali();
			// Attivo il check per i servizi selezionati
      m_bServiceLoaded = FALSE;
			int nProvRichiestiTemp = 0;
      for(n = 0, m_nNumeroServizi = 0; n < m_ListServizi.GetItemCount(); n++)
      {
        nServizio = m_ListServizi.GetItemData(n);
        if(nServizio == m_pSerieSet->m_Servizio1 || nServizio == m_pSerieSet->m_Servizio2 ||
           nServizio == m_pSerieSet->m_Servizio3 || nServizio == m_pSerieSet->m_Servizio4 ||
           nServizio == m_pSerieSet->m_Servizio5 || nServizio == m_pSerieSet->m_Servizio6)
        {
          m_ListServizi.SetCheck(n);  
          m_arySelectedServices.Add(nServizio);
					if(m_pTCertificatoSet->m_Codice == 16 && !(m_ListServizi.GetItemText(n, 0).CompareNoCase("CA02")))
					{
						m_StaticSigla.SetWindowText("Sigla1");
						m_StaticSigla2.ShowWindow(SW_SHOW);
						m_EditSigla2.ShowWindow(SW_SHOW);
					}
          // Se è una prova aggiorno il numero di provini richiesti
          for(SET_START(m_pCatServSet); !m_pCatServSet->IsEOF(); m_pCatServSet->MoveNext())
          {
            if(m_pCatServSet->m_Codice == nServizio && m_pCatServSet->m_Prove != 0)
            {
              m_bProva = TRUE;
              if( m_pCatServSet->m_PerSerie == PER_SERIE )
								nProvRichiestiTemp = m_pCatServSet->m_Campioni;
							else
								nProvRichiestiTemp = 1;
             // break;
            }
          }
        }
      }
			m_nNumeroServizi		= m_arySelectedServices.GetSize();
			m_nProviniRichiesti = nProvRichiestiTemp;
      m_bServiceLoaded = TRUE;
    }
  }
  else
	// Se stiamo inserendo una nova serie...
  {
    m_StaticDim1.Empty();
    m_StaticDim2.Empty();
    m_StaticDim3.Empty();
    m_dDimensione1 = m_dDimensione2 = m_dDimensione3 = 0;
    m_strSigla.Empty();
    m_strStruttura.Empty();
    m_strMateriale.Empty();
    m_DataPrelievo = CTime::GetCurrentTime();
    m_EditDimensione1.EnableWindow(FALSE);
    m_EditDimensione2.EnableWindow(FALSE);
    m_EditDimensione3.EnableWindow(FALSE);

	  //Inserisco i dati relativi alla serie precedente se il tipo certificato corrisponde
	  LoadLastSerie(TRUE);
  }	
  m_DateCtrlPrelievo.SetTime(&m_DataPrelievo);
  UpdateData(FALSE);
}

// Ricarica i dati dell'ultima serie inserita
void CSerieDlg::LoadLastSerie(byte CambiaTipiCertificato)
{
	if (m_nCodiceSerie != -1)
	{
		SINCRONIZE(m_pSerieSet, m_nCodiceSerie);
	}
	else
	{
		m_bNonDichiarata = TRUE;
		m_BtnNonDichiarata.SetCheck(1);
		m_DateCtrlPrelievo.EnableWindow(FALSE);
    m_DTCtrlScadenza.EnableWindow(FALSE);
		m_strDataND = STR_DATAND;
		m_ctrDataND.EnableWindow(TRUE);
		UpdateData(FALSE);
		return;
	}
	if(!m_bNuovaSerie)
		return;
	
	//Sistemo la combo dei tipi certificato solo se richiesto
	if( CambiaTipiCertificato 
		&& !m_pSerieSet->IsFieldNull(&m_pSerieSet->m_TipoCertificato) )
	{
		SINCRONIZE(m_pTCertificatoSet, m_pSerieSet->m_TipoCertificato );
		m_nMaxProviniXCertificato = m_pTCertificatoSet->m_ProvXcertificato;
		LoadTCertData();
		LoadServizi();
	}
	// Altrimenti verifico se si è tornati a selezionare il tipo di certificato relativo
	// alla serie precedente
	else if( !m_pSerieSet->m_TipoCertificato == m_pTCertificatoSet->m_Codice )
		return;
	
	int n, nProva = 0;
	BOOL bSerie = FALSE;
	
	m_nNumeroServizi = 0;
	m_bServiceLoaded = FALSE;
	for(n = 0; n < m_ListServizi.GetItemCount(); n++)
	{
		if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Servizio1) && 
			m_pSerieSet->m_Servizio1 == (int)m_ListServizi.GetItemData(n))
			m_ListServizi.SetCheck(n);
		if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Servizio2) && 
			m_pSerieSet->m_Servizio2 == (int)m_ListServizi.GetItemData(n))
			m_ListServizi.SetCheck(n);
		if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Servizio3) && 
			m_pSerieSet->m_Servizio3 == (int)m_ListServizi.GetItemData(n))
			m_ListServizi.SetCheck(n);
		if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Servizio4) && 
			m_pSerieSet->m_Servizio4 == (int)m_ListServizi.GetItemData(n))
			m_ListServizi.SetCheck(n);
		if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Servizio5) && 
			m_pSerieSet->m_Servizio5 == (int)m_ListServizi.GetItemData(n))
			m_ListServizi.SetCheck(n);
		if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Servizio6) && 
			m_pSerieSet->m_Servizio6 == (int)m_ListServizi.GetItemData(n))
			m_ListServizi.SetCheck(n);
		if(m_ListServizi.GetCheck(n))
		{
			if(m_pTCertificatoSet->m_Codice == 16 && !(m_ListServizi.GetItemText(n, 0).CompareNoCase("CA02")))
			{
				m_StaticSigla.SetWindowText("Sigla1");
				m_StaticSigla2.ShowWindow(SW_SHOW);
				m_EditSigla2.ShowWindow(SW_SHOW);
			}
			for(SET_START(m_pCatServSet); !m_pCatServSet->IsEOF(); m_pCatServSet->MoveNext())
			{
				if((long)m_ListServizi.GetItemData(n) == m_pCatServSet->m_Codice)
				{
					if(m_pCatServSet->m_Prove != 0)
						m_bProva = TRUE;
					break;
				}
			}
		}
	}
	m_nProviniRichiesti = m_pSerieSet->m_NumeroProvini;
	if( !m_pSerieSet->IsFieldNull(&m_pSerieSet->m_StrutturaPrelievo) )
		m_strStruttura = m_pSerieSet->m_StrutturaPrelievo;
	else
		m_strStruttura.Empty();
	m_strSigla.Empty();
	
	if( !m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Dimensione1) )
		m_dDimensione1 = m_pSerieSet->m_Dimensione1;
	if( !m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Dimensione2) )
		m_dDimensione2 = m_pSerieSet->m_Dimensione2;
	if( !m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Dimensione3) )
		m_dDimensione3 = m_pSerieSet->m_Dimensione3;
	
	if(m_nNumeroProvini + m_nProviniRichiesti > m_nMaxProviniXCertificato)
	{
		// Ho superato il numero massimo di provini per certificato
		// -> impongo un nuovo certificato
		SetNuovoCertificato(TRUE);
		m_BtnNuovoCertificato.EnableWindow(FALSE);
	}
	else
	{
		SetNuovoCertificato(FALSE);
		m_BtnNuovoCertificato.EnableWindow(TRUE);
	}
	
	// Carico la lista dei servizi selezionati
	m_arySelectedServices.RemoveAll();
	m_nNumeroServizi = 0;
	for(n = 0; n < m_ListServizi.GetItemCount(); n++)
	{
		if(m_ListServizi.GetCheck(n))
		{
			m_arySelectedServices.Add((WORD)m_ListServizi.GetItemData(n));
			m_nNumeroServizi++;
		}
	}
	
	//Gestione della data prelievo
	if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_DataPrelievo) && m_DataPrelievo != 0)
	{
		m_DataPrelievo = m_pSerieSet->m_DataPrelievo;
		if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_DataProva) && m_pSerieSet->m_DataProva != 0)
			m_DataScadenza = m_pSerieSet->m_DataProva;
		else
			m_DataScadenza = CTime::GetCurrentTime();
    m_bNonDichiarata = FALSE;
    m_BtnNonDichiarata.SetCheck(0);
    m_ctrDataND.EnableWindow(FALSE);
	}
	else
	{
		m_DataScadenza = CTime::GetCurrentTime();
  	m_strDataND = STR_DATAND;
		if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_strDataND))
			m_strDataND = m_pSerieSet->m_strDataND;
  	m_bNonDichiarata = TRUE;
  	m_BtnNonDichiarata.SetCheck(1);
  	m_DateCtrlPrelievo.EnableWindow(FALSE);
    m_DTCtrlScadenza.EnableWindow(FALSE);
	}
	UpdateData(FALSE);
	
	// Carico i tipi di materiale opportuni preselezionando quello della serie prec
	LoadMateriali();
	
	m_EditStruttura.SetFocus();
	m_bServiceLoaded = TRUE;
}

// Carica la lista dei servizi
void CSerieDlg::LoadServizi(void)
{
  int n, nListinoGenerale;
  CString str;
  
  UpdateData();
  if(m_bListinoGenerale)
	  nListinoGenerale = m_nListinoGenerale;
	else
	  nListinoGenerale = 0;
	// Seleziono categorie e servizi associati al listino selezionato
  m_pCatServSet->m_strFilter.Format("(Categoria = CATEGORIE.Codice) AND (Listino = %d OR Listino = %d) AND ((Certificato = %d) OR (Certificato2 = %d) OR (Certificato3 = %d) OR (Certificato4 = %d))",
	                                  nListinoGenerale, m_nListinoParticolare, m_pTCertificatoSet->m_Codice, m_pTCertificatoSet->m_Codice, m_pTCertificatoSet->m_Codice, m_pTCertificatoSet->m_Codice);
	m_pCatServSet->Requery();
  m_bServiceLoaded = FALSE;
  // Cancello gli items della lista
  m_ListServizi.DeleteAllItems();
  m_nProviniRichiesti = 0;
  n = 0;
  // Servizi associati a questo tipo di certificato appartenenti 
  // alle categorie associate al listino selezionato
  for(SET_START(m_pCatServSet); !m_pCatServSet->IsEOF(); m_pCatServSet->MoveNext())
  {
    n = m_ListServizi.InsertItem(n, m_pCatServSet->m_ID);
    m_ListServizi.SetItemData(n, m_pCatServSet->m_Codice);
    m_ListServizi.SetItemText(n, 1, FormatDescrizione());
    m_ListServizi.SetCheck(n, FALSE);
  }
  m_bServiceLoaded = TRUE;
}

// Carica i dati della serie
void CSerieDlg::LoadSeriesData(void)
{

  if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_DataPrelievo) && m_pSerieSet->m_DataPrelievo != 0)
  {
    m_DataPrelievo = m_pSerieSet->m_DataPrelievo;
    if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_DataProva) && m_pSerieSet->m_DataProva != 0)
      m_DataScadenza = m_pSerieSet->m_DataProva;
    else
      m_DataScadenza = CTime::GetCurrentTime();
    m_bNonDichiarata = FALSE;
    m_ctrDataND.EnableWindow(FALSE);
  }
  else
	{
    m_DataPrelievo = CTime::GetCurrentTime();
    m_DataScadenza = CTime::GetCurrentTime();

  	if(m_pSerieSet->IsFieldNull(&m_pSerieSet->m_DataPrelievo))
  	{
  	  m_DateCtrlPrelievo.EnableWindow(FALSE);
      m_DTCtrlScadenza.EnableWindow(FALSE);
  		m_ctrDataND.EnableWindow(TRUE);
  		m_bNonDichiarata = TRUE;
      m_strDataND = STR_DATAND;
      if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_strDataND))
    	  m_strDataND = m_pSerieSet->m_strDataND;
      
  	}
	}

  if(m_pSerieSet->m_NuovoCertificato)
		SetNuovoCertificato(TRUE);
  m_strStruttura				= m_pSerieSet->m_StrutturaPrelievo;
  m_strSigla						= m_pSerieSet->m_Sigla;
  m_strSigla2						= m_pSerieSet->m_Sigla2;

	if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Dimensione1) )
		m_dDimensione1 = m_pSerieSet->m_Dimensione1;
	if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Dimensione2) )
		m_dDimensione2 = m_pSerieSet->m_Dimensione2;
	if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Dimensione3) )
		m_dDimensione3 = m_pSerieSet->m_Dimensione3;

	UpdateData(FALSE);
  m_StaticSigla.EnableWindow();
  m_StaticMateriale.EnableWindow();

  if (!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_strDataND))
	{
		m_bNonDichiarata = TRUE;
		m_BtnNonDichiarata.SetCheck(1);
		m_DateCtrlPrelievo.EnableWindow(FALSE);
    m_DTCtrlScadenza.EnableWindow(FALSE);
    m_strDataND = m_pSerieSet->m_strDataND;
		UpdateData(FALSE);
	}
  else
    m_strDataND = STR_DATAND;

	// Carica i valori del Verbale di Prelievo e della Sigla del Fornitore caricati in fase di accettazione
	if (!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_VerbalePrelievo))
	{
		m_sVerbalePrelievo = m_pSerieSet->m_VerbalePrelievo;
	}

	if (!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_SiglaFornitore))
	{
		m_sSiglaFornitore = m_pSerieSet->m_SiglaFornitore;
	}
}

// Carica i dati del tipo di certificato selezionato
void CSerieDlg::LoadTCertData(void)
{
  int n;
  
  m_StaticDim1.Empty();
  m_StaticDim2.Empty();
  m_StaticDim3.Empty();
  m_EditDimensione1.EnableWindow(FALSE);
  m_EditDimensione2.EnableWindow(FALSE);
  m_EditDimensione3.EnableWindow(FALSE);
  m_dDimensione1 = m_dDimensione2 = m_dDimensione3 = 0;

  for(n = 0; n < m_ComboTipoCertificato.GetCount(); n++)
  {
    if((int)m_ComboTipoCertificato.GetItemData(n) == m_pTCertificatoSet->m_Codice)
    {
      break;
    }
  }
  if(n < m_ComboTipoCertificato.GetCount())
    m_ComboTipoCertificato.SetCurSel(n);
  else
    m_ComboTipoCertificato.SetCurSel(-1);

	int codCert = m_ComboTipoCertificato.GetItemData(n);
	if(m_pSerieSet->IsFieldNull(&m_pSerieSet->m_strDataND))
	{
		if(codCert == 8 || codCert == 9 || codCert == 12 || codCert == 16)
		{	
			m_strDataND = STR_DATAND_12390;
		}
	}

	// Abilita/Disabilita i controlli per l'inserimento del Verbale di Prelievo e della Sigla del Fornitore
	if (codCert == 11 || codCert == 12 || codCert == 13 || codCert == 16)
	{
		m_ctrlVerbalePrelievo.EnableWindow(TRUE);
		if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_VerbalePrelievo))
		{
			m_sVerbalePrelievo = m_pSerieSet->m_VerbalePrelievo;
		}
	}
	else
	{
		m_ctrlVerbalePrelievo.EnableWindow(FALSE);
	}
	if (codCert == 11 || codCert == 13)
	{
		m_ctrlSiglaFornitore.EnableWindow(TRUE);
		if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_SiglaFornitore))
		{
			m_sSiglaFornitore = m_pSerieSet->m_SiglaFornitore;
		}
	}
	else
	{
		m_ctrlSiglaFornitore.EnableWindow(FALSE);
	}

	if(codCert == 11)
	{
		m_ctrlOsservazioni.EnableWindow(TRUE);
		if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Osservazioni))
		{
			m_csOsservazioni = m_pSerieSet->m_Osservazioni;
		}
	}
	else
	{
		m_ctrlOsservazioni.EnableWindow(FALSE);
	}

  // Dimensioni dei provini
  if(!m_pTCertificatoSet->IsFieldNull(&m_pTCertificatoSet->m_Dimensione1))
  {
    m_StaticDim1 = m_pTCertificatoSet->m_Dimensione1;
    if(!m_pTCertificatoSet->IsFieldNull(&m_pTCertificatoSet->m_ValoreDim1))
      m_dDimensione1 = m_pTCertificatoSet->m_ValoreDim1;
    if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Dimensione1) && !m_bNuovaSerie)
      m_dDimensione1 = m_pSerieSet->m_Dimensione1;
    m_EditDimensione1.EnableWindow();
  }
  if(!m_pTCertificatoSet->IsFieldNull(&m_pTCertificatoSet->m_Dimensione2))
  {
    m_StaticDim2 = m_pTCertificatoSet->m_Dimensione2;
    if(!m_pTCertificatoSet->IsFieldNull(&m_pTCertificatoSet->m_ValoreDim2))
      m_dDimensione2 = m_pTCertificatoSet->m_ValoreDim2;
    if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Dimensione2) && !m_bNuovaSerie)
      m_dDimensione2 = m_pSerieSet->m_Dimensione2;
    m_EditDimensione2.EnableWindow();
  }
  if(!m_pTCertificatoSet->IsFieldNull(&m_pTCertificatoSet->m_Dimensione3))
  {
    m_StaticDim3 = m_pTCertificatoSet->m_Dimensione3;
    if(!m_pTCertificatoSet->IsFieldNull(&m_pTCertificatoSet->m_ValoreDim3))
      m_dDimensione3 = m_pTCertificatoSet->m_ValoreDim3;
    if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Dimensione3) && !m_bNuovaSerie)
      m_dDimensione3 = m_pSerieSet->m_Dimensione3;
    m_EditDimensione3.EnableWindow();
  }
	
	UpdateData(FALSE);
}


BOOL CSerieDlg::ValidateData(void)
{
  int i;

  if((i = m_ComboTipoCertificato.GetCurSel()) == 0)
  {
    AfxMessageBox("Selezionare un tipo valido.");
    return FALSE;
  }
  for(i = 0; i < m_ListServizi.GetItemCount(); i++)
  {
    if(m_ListServizi.GetCheck(i))
      break;
  }
  if(i == m_ListServizi.GetItemCount())
  {
    AfxMessageBox("Selezionare almeno un servizio.");
    return FALSE;
  }
  else if( !ProveRichieste() )
  {
    AfxMessageBox("Selezionare almeno una prova.");
    return FALSE;
  }
	if(m_DataPrelievo > CTime::GetCurrentTime())
	{
    AfxMessageBox("Data prelievo successiva a oggi.");
    return FALSE;
	}

  if (m_DataScadenza < m_DataPrelievo)
  {
    AfxMessageBox("Attenzione la data di scadenza non può essere antecedente a quella di prelievo.");
    return FALSE;
  }
  return TRUE;
}

CString CSerieDlg::FormatDescrizione(void)
{
  CString str, strApp;
  BOOL bSerie = (BOOL)m_pCatServSet->m_PerSerie;
  
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

void CSerieDlg::OnCheckNuovoCertificato() 
{
  UpdateData();
  SetNuovoCertificato(m_bNuovoCertificato);
  UpdateData(FALSE);
}




void CSerieDlg::OnCheckListino() 
{
  UpdateData();
  LoadServizi();
}



void CSerieDlg::SetNuovoCertificato(BOOL bNuovo)
{
  // Cambio il numero di posizione
	if(bNuovo)
  {
    if(m_nCertificato == 1 && m_nPosSerie == 1)
      m_nCertificato = 1;
    else
     m_nCertificato += 1;
    m_nOldPos = m_nPosSerie;
    m_nPosSerie = 1;
  }
  else
  {
    m_nPosSerie = m_nOldPos;
    if(m_nCertificato > 1)
      m_nCertificato -= 1;
    else
      m_nCertificato = 1;
  }
  m_bNuovoCertificato = bNuovo;
  // Aggiorno
  m_strPosizione.Format("%d/%d", m_nPosSerie, m_nCertificato);
}




///////////////////////////////////////////////////////////////////////////////
// Riempie l'array dei servizi con gli elementi checkati nella rispettiva lista

void CSerieDlg::OnItemchangedListServizi(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	UpdateData();

  if(!m_bServiceLoaded)
    return;
  UpdateData();
	int nItem = pNMListView->iItem;
  int nCodiceServizio;

	BOOL inserimento = m_ListServizi.GetCheck(nItem);
  nCodiceServizio = (int)m_ListServizi.GetItemData(nItem);

	// Se il servizio non supera il cotrollo lo deseleziono e non faccio nulla
  if( !VerificaCoerenza(nCodiceServizio, inserimento) )
		{
		m_ListServizi.SetCheck(nItem, FALSE);
		return;
		}
	UpdateData(FALSE);

	//--- Ripristino il contenuto dell'array dei servizi richiesti ---//
	m_arySelectedServices.RemoveAll();
  m_StaticSigla.SetWindowText("Sigla");
	m_StaticSigla2.ShowWindow(SW_HIDE);
	m_EditSigla2.ShowWindow(SW_HIDE);
  for(int x =0; x < m_ListServizi.GetItemCount(); x++)
		if(m_ListServizi.GetCheck(x))
			{
			CString serviceID = m_ListServizi.GetItemText(x, 0);
			if(m_pTCertificatoSet->m_Codice == 16 && !serviceID.CompareNoCase("CA02"))
			{
				m_StaticSigla.SetWindowText("Sigla1");
				m_StaticSigla2.ShowWindow(SW_SHOW);
				m_EditSigla2.ShowWindow(SW_SHOW);
			}
			m_arySelectedServices.Add(m_ListServizi.GetItemData(x));
			}
	m_nNumeroServizi = m_arySelectedServices.GetSize();

	
	// Verifico la necessità di iniziare un nuovo certificato.
	if(m_nNumeroProvini + m_nProviniRichiesti > m_nMaxProviniXCertificato
		|| m_pSerieSet->m_TipoCertificato != m_pTCertificatoSet->m_Codice)
		{
		// Ho superato il numero massimo di provini per certificato
		// -> impongo un nuovo certificato, se sto inserendo un nuovo servizio lo aggiungo
		SetNuovoCertificato(TRUE);
		m_BtnNuovoCertificato.EnableWindow(FALSE);
		}


	UpdateData(FALSE);
	*pResult = 0;
}

/////////////////////////////////////////////////////////////////////
// Riempie la combo dei materiali in relazione al tipo di certificato

void CSerieDlg::LoadMateriali(void)
{
  CString str;

	m_pMaterialiSet->m_strFilter.Format("(TipoCertificato = %d) OR (TipoCertificato2 = %d) OR (TipoCertificato3 = %d) OR (TipoCertificato4 = %d)", m_pTCertificatoSet->m_Codice, m_pTCertificatoSet->m_Codice, m_pTCertificatoSet->m_Codice, m_pTCertificatoSet->m_Codice);
	m_pMaterialiSet->m_strSort = "Descrizione ASC";
	m_pMaterialiSet->Requery();
	m_pMaterialiSet->m_strSort = "TipoCertificato, ID ASC";
	
	m_ComboMateriale.ResetContent( );
	int ind = 0;
	int predef = 1;
	for( SET_START(m_pMaterialiSet); !m_pMaterialiSet->IsEOF(); m_pMaterialiSet->MoveNext() )
	{
		ind = m_ComboMateriale.AddString(m_pMaterialiSet->m_Descrizione);
		m_ComboMateriale.SetItemData(ind, m_pMaterialiSet->m_Codice);
		if( m_pMaterialiSet->m_DiDefault == 1)
			predef = ind;
	}

	// Eventuale caricamento del tipo di materiale relativo all'ultima serie 
	// o alla serie da modificare
	if( m_nCodiceSerie!= -1 && m_pSerieSet->m_TipoCertificato == m_pTCertificatoSet->m_Codice)
		{
		if(CB_ERR == m_ComboMateriale.SelectString(0, m_pSerieSet->m_Materiale))
			{
			ind = m_ComboMateriale.AddString(m_pSerieSet->m_Materiale);
			m_ComboMateriale.SetItemData(ind, 0);
			m_ComboMateriale.SetCurSel(ind);
			}
		}
		else
		m_ComboMateriale.SetCurSel(predef);
	UpdateData(TRUE);
}


////////////////////////////////////
//Gestione della data non dichiarata

void CSerieDlg::OnCheckNonDichiarata() 
{
	UpdateData();
	byte dichiarata = !m_BtnNonDichiarata.GetCheck();
	m_DateCtrlPrelievo.EnableWindow(dichiarata);
  m_DTCtrlScadenza.EnableWindow(dichiarata);
	m_ctrDataND.EnableWindow(!dichiarata);
	
  if(!dichiarata && m_strDataND.GetLength() < 1)
  {
    int i = m_ComboTipoCertificato.GetCurSel();
// questa e' una vera nefandezza !!!! s.c. 22-2-2010
    if (m_ComboTipoCertificato.GetItemData(i) == 8 || m_ComboTipoCertificato.GetItemData(i) == 12)
		  m_strDataND = STR_DATAND_12390;
    else
      m_strDataND = STR_DATAND;
  }
/*
  if(dichiarata)
		m_strDataND.Empty();
  */
  if(!dichiarata)
    m_DataScadenza = CTime::GetCurrentTime();
  else
  {
    if(m_pTCertificatoSet->m_Maturazione != 0)
    {
      CTimeSpan tsMat(m_pTCertificatoSet->m_Maturazione, 0, 0, 0);
      m_DataScadenza = m_DataPrelievo + tsMat;
    }
  }
	UpdateData(FALSE);		
}



void CSerieDlg::OnButtonNext() 
{
	CXDialog::OnButtonNext();
}



long CSerieDlg::GetServAggiungibile()
{
  long nCode = 0;

  for(SET_START(m_pCatServSet); !m_pCatServSet->IsEOF(); m_pCatServSet->MoveNext())
	{
	  if(m_pCatServSet->m_Aggiuntivo == 1)
		{
		  if(m_pCatServSet->m_Listino == m_nListinoParticolare)
		    return m_pCatServSet->m_Codice;
      nCode =  m_pCatServSet->m_Codice;
    }
	}
  return nCode;  
}



///////////////////////////////////////////////////////////////////////
// Forza il check nuovo certificato in relazione al cambio di materiale
// non opera se viene digitata una stringa 

void CSerieDlg::OnSelchangeComboMateriale() 
{
	CString strMaterialeScelto;
	m_ComboMateriale.GetLBText( m_ComboMateriale.GetCurSel(), strMaterialeScelto );

	// Se il recordset è sincronizzato con una serie di un verbale diverso, 
	// non esistono altre serie per questo verbale ed è il primo inserimento, 
	// non devo fare nulla.
	if(m_pSerieSet->m_Verbale!=m_nNumeroVerbale)
		return;

	// Se è un tipo di certificato diverso da quello della serie precedentemente inserita,
	// forzo un nuovo certificato
  if(m_pSerieSet->m_Materiale != strMaterialeScelto )
		{
    SetNuovoCertificato(TRUE);
		m_BtnNuovoCertificato.SetCheck(TRUE);
		m_BtnNuovoCertificato.EnableWindow(FALSE);
		}

	// Se ho risettato il tipo di materiale della serie precedente,
	// ricarico i dati della serie precedente a meno che non siamo in operazioni di modifica
	else if(m_bNuovaSerie)
		{
		for(int i=0; i<m_ListServizi.GetItemCount(); i++)
			m_ListServizi.SetCheck(i, FALSE);
		LoadLastSerie(FALSE);	
		}
}



//////////////////////////////////////////////////////////////////////
// Determina se fra i servizi selezionati è presente almeno una prova

BOOL CSerieDlg::ProveRichieste()
{
	int i = 0;
	for(SET_START(m_pCatServSet); !m_pCatServSet->IsEOF(); m_pCatServSet->MoveNext() )
		{
		for(i = 0; i < m_arySelectedServices.GetSize(); i++)
			{
			long temp = m_arySelectedServices.GetAt(i);
			if(m_pCatServSet->m_Codice == temp && m_pCatServSet->m_Prove != 0)
				return TRUE;
			}
		}
	return FALSE;
}


// Funzione che verifica la coerenza nel caso di un inserimento e determina il numero 
// di provini richiesti.

BOOL CSerieDlg::VerificaCoerenza( long codServizio, BOOL inserimento )
{
	if( m_arySelectedServices.GetSize()==6 && inserimento )
		{
		AfxMessageBox("Attenzione si è gia raggiunto il numero massimo di servizi associabili ad una serie!");
		return FALSE;
		}
	
	//Setto i dati relativi al servizio candidato per verificarne la coerenza
	SINCRONIZE(m_pCatServSet, codServizio);
	BOOL	perSerieCandidato		= m_pCatServSet->m_PerSerie;
	int		proveCandidato			= m_pCatServSet->m_Prove;

	int		campioniCandidato = 1;
	if(perSerieCandidato)
		campioniCandidato = m_pCatServSet->m_Campioni;

	//Inizializzo le varibili d'appoggio per la verifica	
	int		proveCorrente				= 0;
	BOOL	perSerieCorrente		= perSerieCandidato;
	m_nProviniRichiesti				= 0;

	// Prelevo i dati relativi alla prima prova fra quelle selezionate
	for(int i=0; i<m_arySelectedServices.GetSize(); i++)
		{
		SINCRONIZE(m_pCatServSet, (long)m_arySelectedServices.GetAt(i));
		CString temp = m_pCatServSet->m_ID;
		if(m_pCatServSet->m_Codice != codServizio &&  m_pCatServSet->m_Prove > 0)
			{
			proveCorrente				= m_pCatServSet->m_Prove;
			perSerieCorrente		= m_pCatServSet->m_PerSerie;
			if(perSerieCorrente == PER_SERIE)
				m_nProviniRichiesti = m_pCatServSet->m_Campioni;
			else
				m_nProviniRichiesti = 1;
			break;
			} 		}

	// Verifico la coerenza
	if(inserimento && (proveCandidato > 0) )
		{
		if( proveCorrente>0 && 
			(proveCorrente == proveCandidato || perSerieCandidato != perSerieCorrente) )
			{
			AfxMessageBox("Attenzione, il servizio selezionato non è coerente con quelli precedentemente selezionati!");
			return FALSE;
			}
		// Se la coerenza è rispettata il numero dei provini è uguale a quello del candidato
		else 
			m_nProviniRichiesti = campioniCandidato;
		}
		
	return TRUE;
}

void CSerieDlg::OnKillfocusEditStruttura() 
{
	CString str;
	UpdateData();
	if(m_strStruttura.GetLength()>DIM_MAX_STRUTTURA)
		{
		AfxMessageBox("Attenzione la descrizione del campo struttura è troppo lunga e verra accorciata.");
		str = m_strStruttura.Left(DIM_MAX_STRUTTURA);
		m_strStruttura = str;
		}
	UpdateData(FALSE);
}

void CSerieDlg::OnCloseupDatetimepickerPrelievo(NMHDR* pNMHDR, LRESULT* pResult) 
{
  UpdateData(TRUE);

  CTimeSpan tsMat(m_pTCertificatoSet->m_Maturazione, 0, 0, 0);
  m_DataScadenza = m_DataPrelievo + tsMat;
  
  if ( m_DataScadenza < CTime::GetCurrentTime() )
    m_DataScadenza = CTime::GetCurrentTime();
  
  UpdateData(FALSE);

	*pResult = 0;
}
