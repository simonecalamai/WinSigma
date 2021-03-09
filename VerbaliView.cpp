// VerbaliView.cpp : implementation file
//

#include "stdafx.h"
#include "WinSigma.h"
#include "XDialog.h"
#include "WinSigmaDoc.h"
#include "TrovaAziendaDlg.h"
#include "SerieDlg.h"
#include "XFormView.h"
#include "Printerpreter.h"
#include "VerbaliView.h"
#include "FattureSet.h"
#include "EmissioneCertificatiDlg.h"
#include "StampaCertificatiDlg.h"
#include "SalvaStampaVerbaliDlg.h"
#include "PrinterThread.h"
#include "FindVerbaliDlg.h"
#include "ModificaCertificatoDlg.h"
#include "MinuteDlg.h"
#include "EtichetteDlg.h"
#include "PrintPreviewFatture.h"
#include "DatiFatturaProforma.h"
#include "afxcmn.h"

#include "EmendaDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define AZIENDA_CERTIFICATO  1
#define AZIENDA_FATTURA      2
#define AZIENDA_IMPRESA      3

// Possibili esiti della ricerca del codice azienda per la fatturazione
#define AZ_NOTFOUND    -1  // Azienda non trovata
#define AZ_NOLISTGEN    0  // Azienda trovata: non accede al listino generale
#define AZ_LISTGEN      1  // Azienda trovata: accede al listino generale

#define STR_CONCERTIFICATO      "Verbale con certificazione"
#define STR_SENZACERTIFICATO    "Verbale senza certificazione"
#define STR_GEOLOGIA            "Verbale per prove geotecniche"

#define STR_SPIANATURA					"SPIANATURA"

// nome del file di stampa della scheda intestatario fattura del verbale
#define FILE_STAMPA_SCHEDA ".\\SchedaIntestatarioFattura.prn"


// Definizione dei membri statici
CAllTables*						CVerbaliView::m_pTabelle;
CString								CVerbaliView::m_strDllCorrente;
long									CVerbaliView::m_nCodSerieStampata;
int										CVerbaliView::m_nContaProvini;
int                   CVerbaliView::m_nPosCertificato;
CVerbaliSet*          CVerbaliView::m_pVerbaliSet;
CSerieSet*            CVerbaliView::m_pSerieSet;
CTipiCertificatoSet*  CVerbaliView::m_pTipiCertificatoSet;
int                   CVerbaliView::m_nTotalePagine;
BOOL                  CVerbaliView::m_bSpianatura;
long                  CVerbaliView::m_nSerieInStampa;
BOOL                  CVerbaliView::m_bPrivato;
BOOL                  CVerbaliView::m_bNote;
CString               CVerbaliView::FormatIndirizzo(CAziendeSet* m_pSet);
int										CVerbaliView::m_nContaEtichette;
int										CVerbaliView::m_nSaltaEtichette;
CStringArray					CVerbaliView::m_aryCampiEtichette;
//BOOL                  CVerbaliView::m_bStampaCaratteri;
int                  CVerbaliView::m_nPrintMode;
/////////////////////////////////////////////////////////////////////////////
// CVerbaliView

IMPLEMENT_DYNCREATE(CVerbaliView, CFormView)

CVerbaliView::CVerbaliView()
: CXFormView(CVerbaliView::IDD)
{
	//{{AFX_DATA_INIT(CVerbaliView)
	m_bCertificatoOgniSerie = FALSE;
	m_bUrgenza = FALSE;
	m_strCodiceAzFattura = _T("");
	m_strCodiceImpresa = _T("");
	m_strDirettore = _T("");
	m_strLetteraIncarico = _T("");
	m_strNomeAzCertificato = _T("");
	m_strCodiceAzCertificato = _T("");
	m_strNomeAzFattura = _T("");
	m_strNomeImpresa = _T("");
	m_nNumSerie = 0;
	m_strProprietario = _T("");
	m_strProveRichieste = _T("");
	m_strTipoVerbale = _T("");
	m_strMaterialeConsegnato = _T("");
  m_DataAccettazione = CTime::GetCurrentTime();
	m_DataConsegna = CTime::GetCurrentTime();
	m_strCosto = _T("");
	m_bLetteraIncarico = FALSE;
	m_strNote = _T("");
	m_bLungaScadenza = FALSE;
	m_bDomandaSottoscritta = FALSE;
	m_strRichiedente = _T("");
	m_strOraConsegna = _T("");
	m_strCantiere = _T("");
	m_strDestinatario = _T("");
	m_strPartitaIva = _T("");
	m_strTipoPagamento = _T("");
	m_bRitiro = FALSE;
	m_strCodFiscale = _T("");
	m_strEMail = _T("");
	//}}AFX_DATA_INIT
  m_bSerieDataChanged = FALSE;
  m_nCertificati = 0;
  m_nSeriePos = 0;
  m_bNuovoVerbale = FALSE;
	m_bListinoGenerale = FALSE;
  m_nCodiceAzFattura = -1;
  m_nCodiceAzCertificato = -1;
  m_nCodiceImpresa = -1;
  m_bSpedizione = FALSE;
  m_nNumeroProvini = 0;

  m_pGlobalVerbaliSet = NULL;
  m_pGlobalVerbaliSet = new CVerbaliSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
  m_pGlobalVerbaliSet->m_strFilter = "Codice = -1";
  m_pGlobalVerbaliSet->Open();

  m_pGlobalSerieSet = NULL;
  m_pGlobalSerieSet = new CSerieSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
  m_pGlobalSerieSet->m_strFilter = "Codice = -1";
  m_pGlobalSerieSet->Open();
}

CVerbaliView::~CVerbaliView()
{
  if (m_pGlobalVerbaliSet)
  {
    m_pGlobalVerbaliSet->Close();
    delete m_pGlobalVerbaliSet;
  }

  if (m_pGlobalSerieSet)
  {
    m_pGlobalSerieSet->Close();
    delete m_pGlobalSerieSet;
  }
}

void CVerbaliView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVerbaliView)
	DDX_Control(pDX, IDC_EDIT_CODFISCALE, m_EditCodFiscale);
	DDX_Control(pDX, IDC_CHECK_RITIRO, m_chkRitiro);
	DDX_Control(pDX, IDC_BUTTON_EMENDA, m_BtnEmenda);
	DDX_Control(pDX, IDC_EDIT_PIVA, m_EditPartitaIva);
	DDX_Control(pDX, IDC_EDIT_DESTINATARIO, m_EditDestinatario);
	DDX_Control(pDX, IDC_COMBO_CONSEGNA, m_ComboConsegna);
	DDX_Control(pDX, IDC_COMBO_TIPO_PROVA, m_ComboTipoProva);
	DDX_Control(pDX, IDC_EDIT_CANTIERE, m_EditCantiere);
	DDX_Control(pDX, IDC_EDIT_ORA_CONSEGNA, m_EditOraConsegna);
	DDX_Control(pDX, IDC_EDIT_RICHIEDENTE, m_EditRichiedente);
	DDX_Control(pDX, IDC_CHECK_DOMANDA_SOTTOSCRITTA, m_BtnDomandaSottoscritta);
	DDX_Control(pDX, IDC_BUTTON_COPY, m_BtnCopia);
	DDX_Control(pDX, IDC_BUTTON_DATI_PROVINI, m_BtnDatiProvini);
	DDX_Control(pDX, IDC_CHECK_LUNGA_SCADENZA, m_BtnLungaScadenza);
	DDX_Control(pDX, IDC_EDIT_NOTE, m_EditNote);
	DDX_Control(pDX, IDC_BUTTON_AUTO_PROVE, m_BtnAutoProve);
	DDX_Control(pDX, IDC_BUTTON_AUTO_MAT, m_BtnAutoMateriale);
	DDX_Control(pDX, IDC_CHECK_LETTERA, m_BtnLettera);
	DDX_Control(pDX, IDC_EDIT_COSTO, m_EditCosto);
	DDX_Control(pDX, IDC_EDIT_TIPOVERBALE, m_EditTipoVerbale);
	DDX_Control(pDX, IDC_EDIT_NUMSERIE, m_EditNumSerie);
	DDX_Control(pDX, IDC_BUTTON_MODIFICA, m_BtnModificaSerie);
	DDX_Control(pDX, IDC_BUTTON_ELIMINA, m_BtnEliminaSerie);
	DDX_Control(pDX, IDC_BUTTON_AGGIUNGI, m_BtnAggiungiSerie);
	DDX_Control(pDX, IDC_DATE_CONSEGNA, m_CtrlDataConsegna);
	DDX_Control(pDX, IDC_DATE_ACCETTAZIONE, m_CtrlDataAccettazione);
	DDX_Control(pDX, IDC_EDITMATERIALE, m_EditMaterialeConsegnato);
	DDX_Control(pDX, IDC_EDIT_PROVE, m_EditProveRichieste);
	DDX_Control(pDX, IDC_EDIT_PROPRIETARIO, m_EditProprietario);
	DDX_Control(pDX, IDC_EDIT_NOME_AZ_IMPRESA, m_EditNomeAzImpresa);
	DDX_Control(pDX, IDC_EDIT_NOME_AZ_FATTURA, m_EditNomeAzFattura);
	DDX_Control(pDX, IDC_EDIT_NOME_AZ_CERTIFICATO, m_EditNomeAzCertificato);
	DDX_Control(pDX, IDC_EDIT_LETTERA, m_EditLetteraIncarico);
	DDX_Control(pDX, IDC_EDIT_DIRETTORE, m_EditDirettore);
	DDX_Control(pDX, IDC_EDIT_COD_AZ_IMPRESA, m_EditCodiceAzImpresa);
	DDX_Control(pDX, IDC_EDIT_COD_AZ_FATTURA, m_EditCodiceAzFattura);
	DDX_Control(pDX, IDC_EDIT_COD_AZ_CERTIFICATO, m_EditCodiceAzCertificato);
	DDX_Control(pDX, IDC_CHECK_URGENZA, m_BtnUrgenza);
	DDX_Control(pDX, IDC_CHECK_OGNISERIE, m_BtnOgniSerie);
	DDX_Control(pDX, IDC_LIST_SERIE, m_ListSerie);
	DDX_Check(pDX, IDC_CHECK_OGNISERIE, m_bCertificatoOgniSerie);
	DDX_Check(pDX, IDC_CHECK_URGENZA, m_bUrgenza);
	DDX_Text(pDX, IDC_EDIT_COD_AZ_FATTURA, m_strCodiceAzFattura);
	DDX_Text(pDX, IDC_EDIT_COD_AZ_IMPRESA, m_strCodiceImpresa);
	DDX_Text(pDX, IDC_EDIT_DIRETTORE, m_strDirettore);
	DDV_MaxChars(pDX, m_strDirettore, 64);
	DDX_Text(pDX, IDC_EDIT_LETTERA, m_strLetteraIncarico);
	DDX_Text(pDX, IDC_EDIT_NOME_AZ_CERTIFICATO, m_strNomeAzCertificato);
	DDX_Text(pDX, IDC_EDIT_COD_AZ_CERTIFICATO, m_strCodiceAzCertificato);
	DDX_Text(pDX, IDC_EDIT_NOME_AZ_FATTURA, m_strNomeAzFattura);
	DDX_Text(pDX, IDC_EDIT_NOME_AZ_IMPRESA, m_strNomeImpresa);
	DDX_Text(pDX, IDC_EDIT_NUMSERIE, m_nNumSerie);
	DDX_Text(pDX, IDC_EDIT_PROPRIETARIO, m_strProprietario);
	DDV_MaxChars(pDX, m_strProprietario, 104);
	DDX_Text(pDX, IDC_EDIT_PROVE, m_strProveRichieste);
	DDX_Text(pDX, IDC_EDIT_TIPOVERBALE, m_strTipoVerbale);
	DDX_Text(pDX, IDC_EDITMATERIALE, m_strMaterialeConsegnato);
	DDV_MaxChars(pDX, m_strMaterialeConsegnato, 255);
	DDX_DateTimeCtrl(pDX, IDC_DATE_ACCETTAZIONE, m_DataAccettazione);
  DDX_DateTimeCtrl(pDX, IDC_DATE_CONSEGNA, m_DataConsegna);
	DDX_Text(pDX, IDC_EDIT_COSTO, m_strCosto);
	DDX_Check(pDX, IDC_CHECK_LETTERA, m_bLetteraIncarico);
	DDX_Text(pDX, IDC_EDIT_NOTE, m_strNote);
	DDX_Check(pDX, IDC_CHECK_LUNGA_SCADENZA, m_bLungaScadenza);
	DDX_Check(pDX, IDC_CHECK_DOMANDA_SOTTOSCRITTA, m_bDomandaSottoscritta);
	DDX_Text(pDX, IDC_EDIT_RICHIEDENTE, m_strRichiedente);
	DDX_Text(pDX, IDC_EDIT_ORA_CONSEGNA, m_strOraConsegna);
	DDX_Text(pDX, IDC_EDIT_CANTIERE, m_strCantiere);
	DDV_MaxChars(pDX, m_strCantiere, 125);
	DDX_Text(pDX, IDC_EDIT_DESTINATARIO, m_strDestinatario);
	DDX_Text(pDX, IDC_EDIT_PIVA, m_strPartitaIva);
	DDX_Text(pDX, IDC_EDIT_PAGAMENTO, m_strTipoPagamento);
	DDX_Check(pDX, IDC_CHECK_RITIRO, m_bRitiro);
	DDX_Text(pDX, IDC_EDIT_CODFISCALE, m_strCodFiscale);
	DDX_Text(pDX, IDC_EDIT_EMAIL, m_strEMail);
	DDX_Control(pDX, IDC_STATIC_ALARM_NOTE, m_StaticAlarmNote);
//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVerbaliView, CXFormView)
	//{{AFX_MSG_MAP(CVerbaliView)
	ON_COMMAND(ID_NUOVO, OnNuovo)
	ON_COMMAND(ID_NUOVO_VERBALE, OnNuovoVerbale)
	ON_BN_CLICKED(IDC_BUTTON_MODIFICA, OnButtonModifica)
	ON_BN_CLICKED(IDC_BUTTON_AGGIUNGI, OnButtonAggiungi)
	ON_BN_CLICKED(IDC_BUTTON_ELIMINA, OnButtonElimina)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SERIE, OnDblclkListSerie)
	ON_BN_CLICKED(IDC_CHECK_OGNISERIE, OnCheckOgniserie)
	ON_BN_CLICKED(IDC_CHECK_LETTERA, OnCheckLettera)
	ON_BN_CLICKED(IDC_CHECK_URGENZA, OnCheckUrgenza)
	ON_COMMAND(ID_BUTTON_AVVIA_EMISSIONE, OnButtonEmissioneCertificati)
	ON_COMMAND(ID_MODIFICA, OnModifica)
	ON_EN_CHANGE(IDC_EDIT_COD_AZ_FATTURA, OnChangeEditCodAzFattura)
	ON_EN_CHANGE(IDC_EDIT_NOME_AZ_FATTURA, OnChangeEditNomeAzFattura)
	ON_COMMAND(ID_PRINT_MINUTA, OnPrintMinuta)
	ON_EN_KILLFOCUS(IDC_EDIT_COD_AZ_CERTIFICATO, OnKillfocusEditCodAzCertificato)
	ON_EN_KILLFOCUS(IDC_EDIT_COD_AZ_FATTURA, OnKillfocusEditCodAzFattura)
	ON_EN_KILLFOCUS(IDC_EDIT_COD_AZ_IMPRESA, OnKillfocusEditCodAzImpresa)
	ON_EN_KILLFOCUS(IDC_EDIT_NOME_AZ_CERTIFICATO, OnKillfocusEditNomeAzCertificato)
	ON_EN_KILLFOCUS(IDC_EDIT_NOME_AZ_FATTURA, OnKillfocusEditNomeAzFattura)
	ON_EN_KILLFOCUS(IDC_EDIT_NOME_AZ_IMPRESA, OnKillfocusEditNomeAzImpresa)
	ON_COMMAND(ID_BUTTON_STAMPA_CERTIFICATI_SENZA_HEADER, OnButtonStampaCertificati)
	ON_COMMAND(ID_BUTTON_STAMPA_CERTIFICATI, OnButtonStampaCertificatiConHeader)
	ON_COMMAND(ID_PRN_CARTA_INTESTATA, OnPrnCartaIntestata)
	ON_COMMAND(ID_PRN_CARTA_LIBERA, OnPrnCartaLibera)
	ON_COMMAND(ID_VERBALI_STAMPA_VERBALECONINTESTAZIONE, OnPrnVerbaleConIntestazione)
	ON_BN_CLICKED(IDC_CHECK_LUNGA_SCADENZA, OnCheckLungaScadenza)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_MAT, OnButtonAutoMateriale)
	ON_BN_CLICKED(IDC_BUTTON_AUTO_PROVE, OnButtonAutoProve)
	ON_COMMAND(ID_DATI_PROVINI, OnDatiProvini)
	ON_BN_CLICKED(IDC_BUTTON_DATI_PROVINI, OnButtonDatiProvini)
	ON_COMMAND(ID_CHIUDI_VERBALE, OnChiudiVerbale)
	ON_COMMAND(ID_METTI_IN_FATTURAZIONE, OnMettiInFatturazione)
	ON_COMMAND(ID_ANNULLA, OnAnnullaVerbale)
	ON_BN_CLICKED(IDC_BUTTON_COPY, OnButtonCopy)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_CONSEGNA, OnSelchangeComboConsegna)
	ON_COMMAND(ID_FIND_VERB_CANTIERE, OnFindVerbCantiere)
	ON_COMMAND(ID_FIND_VERB_CERTIFICATO, OnFindVerbCertificato)
	ON_COMMAND(ID_FIND_VERB_DIR_LAVORI, OnFindVerbDirLavori)
	ON_COMMAND(ID_FIND_VERB_FATTURA, OnFindVerbFattura)
	ON_COMMAND(ID_FIND_VERB_IMPRESA, OnFindVerbImpresa)
	ON_COMMAND(ID_BUTTON_MODIFICA_CERTIFICATO, OnButtonModificaCertificato)
	ON_COMMAND(ID_AGGIORNA_ALBERO, OnAggiornaAlbero)
	ON_COMMAND(ID_SBLOCCO_VERBALE, OnSbloccoVerbale)
	ON_COMMAND(ID_SBLOCCACERTIFICAZIONE, OnSbloccacertificazione)
	ON_COMMAND(ID_STAMPA_ETICHETTE, OnStampaEtichette)
	ON_COMMAND(ID_BUTTON_AGGIORNA, OnButtonAggiorna)
	ON_COMMAND(ID_FIND_VERB_STRUTTURA, OnFindVerbStruttura)
	ON_COMMAND(ID_PRINT_SCHEDA_INT_FATTURA, OnPrintSchedaIntFattura)
	ON_COMMAND(ID_PRN_FATTURA_PROFORMA, OnPrnFatturaProforma)
	ON_COMMAND(ID_FIND_VERB_SIGLA, OnFindVerbSigla)
	ON_COMMAND(ID_NUOVO_GEOLOGIA, OnNuovoGeologia)
	ON_BN_CLICKED(IDC_BUTTON_EMENDA, OnButtonEmenda)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SERIE, OnClickListSerie)
	ON_BN_CLICKED(IDC_CHECK_RITIRO, OnCheckRitiro)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_FIND_VERB_NUMERO, OnFindVerbNumero)
	//}}AFX_MSG_MAP
  ON_MESSAGE(WM_PRINT_NO_COMM, OnPrintNoComm)
  ON_MESSAGE(WM_PRINT_OK, OnPrintThreadOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVerbaliView diagnostics

#ifdef _DEBUG
void CVerbaliView::AssertValid() const
{
	CFormView::AssertValid();
}

void CVerbaliView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVerbaliView message handlers

void CVerbaliView::OnInitialUpdate() 
{
	int n = 0;
	DWORD style;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  int nFontWidth = pApp->GetFontWidth();

  switch(pDoc->m_nSelectedTreeVerbali)
  {
  case TREEITEM_VERBALIPRECEDENTI:
    m_pVerbaliSet = pDoc->m_pVerbaliPrecedentiSet;
    break;
  case TREEITEM_VERBFATTPROFORMA:
    m_pVerbaliSet = pDoc->m_pVerbaliFattProforma;
    break;
  case TREEITEM_VERBALIULTIMOMESE:
  default:
    m_pVerbaliSet = pDoc->m_pVerbaliUltimoMeseSet;
    break;
  }
  CXFormView::m_pSet = m_pVerbaliSet;
	CXFormView::OnInitialUpdate();
  /*----- imposto il font per il numero di verbale ------*/
	m_FontLarge.CreateFont(16, 10, 0, 0, FW_NORMAL,
                         0, 0, 0, DEFAULT_CHARSET,
                         OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                         DEFAULT_QUALITY, DEFAULT_PITCH,
                         "Arial");
  m_EditTipoVerbale.SetFont(&m_FontLarge);
  /*----- configuro la lista delle serie -----*/
  style = m_ListSerie.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT;
	m_ListSerie.SetExtendedStyle(style);
  m_ListSerie.InsertColumn(0, "Pos.", LVCFMT_CENTER, 12 * nFontWidth, -1);
  m_ListSerie.InsertColumn(1, "Certificato", LVCFMT_LEFT, 21 * nFontWidth, -1);
	m_ListSerie.InsertColumn(2, "Tipo", LVCFMT_LEFT, 32 * nFontWidth, -1);
  m_ListSerie.InsertColumn(3, "Struttura", LVCFMT_LEFT, 19 * nFontWidth, -1);
	m_ListSerie.InsertColumn(4, "Servizi", LVCFMT_LEFT, 19 * nFontWidth, -1);
	m_ListSerie.InsertColumn(5, "C.", LVCFMT_CENTER, 5 * nFontWidth, -1);
  m_ListSerie.InsertColumn(6, "Prezzo", LVCFMT_RIGHT, 10 * nFontWidth, -1);
  m_imgSerie.Create(IDB_IMAGELIST_SERIE, 16, 0, RGB(0,128,128));
  m_ListSerie.SetImageList(&m_imgSerie, LVSIL_SMALL);
  /*---- inizializzo i campi -----*/
  m_DataAccettazione = CTime::GetCurrentTime();
	m_DataConsegna = CTime::GetCurrentTime();
	m_DataProva = CTime::GetCurrentTime();
  m_CtrlDataAccettazione.SetTime(&m_DataAccettazione);
  m_CtrlDataConsegna.SetTime(&m_DataConsegna);
  m_strOraConsegna.Empty();
  m_pSerieSet = pDoc->m_pSerieSet;
	m_pTipiCertificatoSet = pDoc->m_pTipiCertificatoSet;
  m_bSerieDataChanged = FALSE;
  m_nCodiceAzFattura = -1;
  m_nCodiceAzCertificato = -1;
  m_nCodiceImpresa = -1;
  m_nCodiceUltimaSerie = -1;
  m_aryPosSerie.RemoveAll();
	m_strTempEtichette = "";
  /*----- inizializzo la combo della spedizione -----*/
	m_ComboConsegna.AddString("Invio");
	m_ComboConsegna.AddString("Sped. int. certificati");
	m_ComboConsegna.AddString("Sped. int. fattura");
	m_ComboConsegna.AddString("Sped. impresa");
	m_ComboConsegna.AddString("Spedire a ...");
	m_ComboConsegna.AddString("Ritiro");
	m_ComboConsegna.SetCurSel(0);
  m_arySerieEliminate.RemoveAll();
	m_nCodSperiment = 0;

	/*----- inizializzo la combo del tipo di prova -----*/
	m_ComboTipoProva.ResetContent();
	n = m_ComboTipoProva.AddString("Prove di carico - PC");
	m_ComboTipoProva.SetItemData(n, VERB_NC_PROVE_DI_CARICO);	
	n = m_ComboTipoProva.AddString("Conglomerati bituminosi - CB");
	m_ComboTipoProva.SetItemData(n, VERB_NC_CONGL_BITUMINOSI);	
	n = m_ComboTipoProva.AddString("Inerti e rocce - I");
	m_ComboTipoProva.SetItemData(n, VERB_NC_INERTI);	
	n = m_ComboTipoProva.AddString("Monitoraggi - MO");
	m_ComboTipoProva.SetItemData(n, VERB_NC_MONITORAGGI);	
	n = m_ComboTipoProva.AddString("Varie - V");
	m_ComboTipoProva.SetItemData(n, VERB_NC_VARIE);	
	n = m_ComboTipoProva.AddString("Geotecnica - NC");
	m_ComboTipoProva.SetItemData(n, VERB_NC_GEOTECNICA);	
	n = m_ComboTipoProva.AddString("Linee Vita - LV");
	m_ComboTipoProva.SetItemData(n, VERB_NC_LINEE_VITA);	
	n = m_ComboTipoProva.AddString("Indagini su murature - IM");
	m_ComboTipoProva.SetItemData(n, VERB_NC_INDAGINI_MURATURE);	
	n = m_ComboTipoProva.AddString("Indagini su CLS - IC");
	m_ComboTipoProva.SetItemData(n, VERB_NC_INDAGINI_CLS);	
	n = m_ComboTipoProva.AddString("Materiali metallici - MM");
	m_ComboTipoProva.SetItemData(n, VERB_NC_MAT_METALLICI);	

	/* notifica note non visibile */
	m_StaticAlarmNote.ShowWindow(SW_HIDE);

	OnUpdate(NULL, 0, NULL);

  // Disabilito il pulsante "Emenda"
  m_BtnEmenda.EnableWindow(FALSE);

  m_chkRitiro.EnableWindow(FALSE);
  m_bRitiro = false;

}


void CVerbaliView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  int nVerbale;
  
  switch(pDoc->m_nSelectedTreeVerbali)
  {
  case TREEITEM_VERBALIPRECEDENTI:
//    if(!pDoc->m_pVerbaliPrecedentiSet->IsBOF())
    {
	    CXFormView::m_pSet = m_pSet = pDoc->m_pVerbaliPrecedentiSet;
      nVerbale = pDoc->m_pVerbaliPrecedentiSet->m_Codice;
    }
    break;
  case TREEITEM_VERBFATTPROFORMA:
//    if(!pDoc->m_pVerbaliFattProforma->IsBOF())
    {
      CXFormView::m_pSet = m_pSet = pDoc->m_pVerbaliFattProforma;
      nVerbale = pDoc->m_pVerbaliFattProforma->m_Codice;
    }
    break;
  case TREEITEM_VERBALIULTIMOMESE:
  default:
//    if(!pDoc->m_pVerbaliUltimoMeseSet->IsBOF())
    {
	    CXFormView::m_pSet = m_pSet = pDoc->m_pVerbaliUltimoMeseSet;
      nVerbale = pDoc->m_pVerbaliUltimoMeseSet->m_Codice;
    }
    break;
  }
  if(!pDoc->m_pSerieSet->IsBOF())
    m_pSerieSet = pDoc->m_pSerieSet;    
	CXFormView::OnUpdate(pSender, lHint, pHint);
}

// Copia nome e codice di un'azienda nelle altre edit
void CVerbaliView::OnButtonCopy() 
{
  UpdateData();
  m_strCodiceAzFattura = m_strCodiceImpresa = m_strCodiceAzCertificato;
  m_strNomeAzFattura   = m_strNomeImpresa   = m_strNomeAzCertificato;
  m_strIndAzFattura    = m_strIndImpresa    = m_strIndAzCertificati;
  m_nCodiceAzFattura   = m_nCodiceImpresa   = m_nCodiceAzCertificato; 
  GetDatiFatturazione();
  UpdateData(FALSE);
}


// Carica nella form i dati del verbale selezionato
void CVerbaliView::LoadCurRecord(BOOL bData)
{
  m_arySerieEliminate.RemoveAll();
  m_aryPosSerie.RemoveAll();
  m_bSerieDataChanged = FALSE;
  if(bData)
  { 
    if(m_pVerbaliSet->IsBOF() || m_pVerbaliSet->IsEOF())
      return;  
    m_nTipoVerbale = m_pVerbaliSet->m_TipoVerbale;
    // Accettazione
    switch(m_nTipoVerbale)
    {
    case VERB_IN_CONCESSIONE:
      m_strTipoVerbale.Format("Verbale n° %d / %d\r\n Prove in concessione", m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale);
      break;
    case VERB_NON_IN_CONCESSIONE:
		case VERB_NC_PROVE_DI_CARICO :
		case VERB_NC_CONGL_BITUMINOSI	:
		case VERB_NC_INERTI	:
		case VERB_NC_MONITORAGGI :
		case VERB_NC_VARIE	:
		case VERB_NC_GEOTECNICA :
		case VERB_NC_LINEE_VITA:
		case VERB_NC_INDAGINI_MURATURE:
		case VERB_NC_INDAGINI_CLS:
		case VERB_NC_MAT_METALLICI:
#ifdef WINSIGMA2
			m_strTipoVerbale.Format("Verbale n° A%d", m_pVerbaliSet->m_ProgressivoTotale);	
#else
      m_strTipoVerbale.Format("Verbale n° %d / %d", m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale);
#endif
      break;
    case VERB_GEOLOGIA:
      m_strTipoVerbale.Format("Verbale n° %d / %d\r\n Prove geotecniche", m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale);
      break;
    }
    m_DataAccettazione = m_pVerbaliSet->m_DataAccettazione;
    m_CtrlDataAccettazione.SetTime(&m_DataAccettazione);
    // Intestazioni
		for(int u(0); u < m_ComboTipoProva.GetCount(); u++)
		{
			if(m_ComboTipoProva.GetItemData(u) == (unsigned long)m_pVerbaliSet->m_TipoVerbale)
			{
				m_ComboTipoProva.SetCurSel(u);
				break;
			}
		}

    m_strCodiceAzCertificato = m_pVerbaliSet->m_IDAzCertificato;
    m_strNomeAzCertificato   = m_pVerbaliSet->m_NomeAzCertificato;
    m_strIndAzCertificati    = m_pVerbaliSet->m_IndirizzoCertificato;
    m_strCodiceAzFattura     = m_pVerbaliSet->m_IDAzFattura;
    m_strNomeAzFattura       = m_pVerbaliSet->m_NomeAzFattura;
    m_strIndAzFattura        = m_pVerbaliSet->m_IndirizzoFattura;
    m_strPartitaIva          = m_pVerbaliSet->m_P_IVA;
    m_strCodFiscale          = m_pVerbaliSet->m_CodFiscale;
    m_strTipoPagamento       = m_pVerbaliSet->m_Pagamento;
    m_strCodiceImpresa       = m_pVerbaliSet->m_IDImpresaRichiedente;
    m_strNomeImpresa         = m_pVerbaliSet->m_NomeImpresa;
    m_strIndImpresa          = m_pVerbaliSet->m_IndirizzoRichiedente;
    // Chiavi esterne su tabelle collegate 
    m_nCodiceAzFattura     = m_pVerbaliSet->m_CodiceAzFattura;
    m_nCodiceAzCertificato = m_pVerbaliSet->m_CodiceAzCertificato;
    m_nCodiceImpresa       = m_pVerbaliSet->m_CodiceImpresa;
  	m_nListinoGenerale     = m_pVerbaliSet->m_ListinoGenerale;
  	m_nListinoParticolare  = m_pVerbaliSet->m_ListinoParticolare;
    // Altri dati
		GetDatiFatturazione();
    m_bLetteraIncarico   = (BOOL)m_pVerbaliSet->m_LetteraIncarico;
    m_strLetteraIncarico = m_pVerbaliSet->m_NumLetteraIncarico;
    m_strDirettore       = m_pVerbaliSet->m_Direttore;
  	m_strCantiere        = m_pVerbaliSet->m_Cantiere;
    m_strProprietario    = m_pVerbaliSet->m_Proprietario;
    m_strRichiedente     = m_pVerbaliSet->m_Richiedente;
    if(!m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_DomandaSottoscritta))
      m_bDomandaSottoscritta = (BOOL)m_pVerbaliSet->m_DomandaSottoscritta;
    else
      m_bDomandaSottoscritta = FALSE;
    // Prove richieste e materiale consegnato
    m_strProveRichieste      = m_pVerbaliSet->m_ProveRichieste;
    m_strMaterialeConsegnato = m_pVerbaliSet->m_DescrizioneMateriale;
    // Servizi aggiuntivi
    m_bCertificatoOgniSerie = (BOOL)m_pVerbaliSet->m_CertOgniSerie;
    
    if (m_pVerbaliSet->m_Urgenza != 2)
      m_bUrgenza = (BOOL)m_pVerbaliSet->m_Urgenza;
    else
    {
      m_bUrgenza = false;
      m_bRitiro  = true;
    }
    
    m_DataConsegna = m_pVerbaliSet->m_DataConsegna;
    m_CtrlDataConsegna.SetTime(&m_DataConsegna);
    m_strOraConsegna = m_pVerbaliSet->m_OraConsegna;

    m_bLungaScadenza = (BOOL)m_pVerbaliSet->m_LungaScadenza;
    // Spedizione
    m_strDestinatario = m_pVerbaliSet->m_Destinatario;
    m_strNote = m_pVerbaliSet->m_NoteSpedizione;
    if(!m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_Spedizione))
      m_bSpedizione = (BOOL)m_pVerbaliSet->m_Spedizione;
    else
      m_bSpedizione = false;
    if(m_bSpedizione)
		{
		  m_ComboConsegna.SetCurSel(4);
		}
    else
		{
			if(m_bRitiro == TRUE)
				m_ComboConsegna.SetCurSel(5);
			else
				m_ComboConsegna.SetCurSel(0);
		}
    // Serie
    LoadSeries(m_pVerbaliSet->m_Codice);
  }
  else
  {
    // Pulisco i dati della form
    m_DataAccettazione = CTime::GetCurrentTime();
    m_DataConsegna = CTime::GetCurrentTime() + CTimeSpan(2, 0, 0, 0);
    m_CtrlDataAccettazione.SetTime(&m_DataAccettazione);
    m_CtrlDataConsegna.SetTime(&m_DataConsegna);
    m_strOraConsegna.Empty();
    // Codici - nomi aziende
    m_strCodiceAzCertificato.Empty();
    m_strNomeAzCertificato.Empty();
    m_strIndAzCertificati.Empty();
    m_strCodiceAzFattura.Empty();
    m_strNomeAzFattura.Empty();
    m_strIndAzFattura.Empty	();
	  m_strPartitaIva.Empty();
    m_strCodFiscale.Empty();
    m_strEMail.Empty();
    m_strCodiceImpresa.Empty();
    m_strNomeImpresa.Empty();
    m_strIndImpresa.Empty();
    m_strTipoPagamento.Empty();
	  m_nListinoGenerale    = 0;
	  m_nListinoParticolare = 0;
    // Altri dati
    m_strLetteraIncarico.Empty();
    m_strDirettore.Empty();
    m_strCantiere.Empty();
    m_strProprietario.Empty();
    m_strRichiedente.Empty();
    m_strProveRichieste.Empty();
    m_strMaterialeConsegnato.Empty();
	  m_strCosto.Empty();
    m_bCertificatoOgniSerie = FALSE;
    m_bUrgenza = FALSE;
    m_bLetteraIncarico = FALSE;
   // m_bDomandaSottoscritta = FALSE;
    // Consegna
		m_ComboConsegna.SetCurSel(0);
    m_bSpedizione = FALSE;
    m_strDestinatario.Empty();
    m_nNumSerie = 0;
    m_ListSerie.DeleteAllItems();
    m_bSerieDataChanged = FALSE;
	  m_strNote.Empty();
    // Chiavi esterne su tabelle collegate 
    m_nCodiceAzFattura     = -1;
    m_nCodiceAzCertificato = -1;
    m_nCodiceImpresa       = -1;
    m_bLungaScadenza = FALSE;
		m_StaticAlarmNote.ShowWindow(SW_HIDE);
  }
}

// Verifica se qualche dato è cambiato
BOOL CVerbaliView::IsDataChanged()
{
  CString str, str1;
  int n;
  str = m_strCantiere;
  str.Replace("\r\n", "$");
  if((n = str.Find("$")) != -1)
  {
    str1 = str.Mid(n + 1);
    str.TrimRight("$");
  }
  if( m_DataAccettazione         != m_pVerbaliSet->m_DataAccettazione
     || m_strCodiceAzCertificato != m_pVerbaliSet->m_IDAzCertificato
     || m_strNomeAzCertificato   != m_pVerbaliSet->m_NomeAzCertificato
     || m_strCodiceAzFattura     != m_pVerbaliSet->m_IDAzFattura
     || m_strNomeAzFattura       != m_pVerbaliSet->m_NomeAzFattura
     || m_strCodiceImpresa       != m_pVerbaliSet->m_IDImpresaRichiedente
     || m_strNomeImpresa         != m_pVerbaliSet->m_NomeImpresa
     || m_strLetteraIncarico     != m_pVerbaliSet->m_NumLetteraIncarico
     || m_bLetteraIncarico       != m_pVerbaliSet->m_LetteraIncarico
     || m_strDirettore           != m_pVerbaliSet->m_Direttore
     || m_bDomandaSottoscritta   != m_pVerbaliSet->m_DomandaSottoscritta
     || str                      != m_pVerbaliSet->m_Cantiere
     || m_bLungaScadenza         != m_pVerbaliSet->m_LungaScadenza
     || m_strProprietario        != m_pVerbaliSet->m_Proprietario
     || m_strRichiedente         != m_pVerbaliSet->m_Richiedente
     || m_strProveRichieste      != m_pVerbaliSet->m_ProveRichieste
     || m_strMaterialeConsegnato != m_pVerbaliSet->m_DescrizioneMateriale
     || m_bCertificatoOgniSerie  != m_pVerbaliSet->m_CertOgniSerie
     || m_bUrgenza               != m_pVerbaliSet->m_Urgenza
     || m_DataConsegna           != m_pVerbaliSet->m_DataConsegna
     || m_strOraConsegna         != m_pVerbaliSet->m_OraConsegna    
     || m_bSpedizione            != m_pVerbaliSet->m_Spedizione
     || m_strDestinatario        != m_pVerbaliSet->m_Destinatario
     || m_strNote                != m_pVerbaliSet->m_NoteSpedizione
     || m_bSerieDataChanged)
     return TRUE;
  return TRUE;
}


// Verifica la correttezza dei dati inseriti
BOOL CVerbaliView::ValidateData()
{
	
	// Controllo della coerenza fra la data del verbale candidato con il contenuto del database
	CString query, msg;
	if(m_DataAccettazione > CTime::GetCurrentTime() )
	{
		AfxMessageBox("Attenzione: data di accettazione successiva alla data odierna");
		return FALSE;
	}
	else
	{
		// Query che verifica, fra tutti i verbali dell'anno in corso, un eventuale conflitto
		// corretto bug 5-10-2010 s.c.
    query.Format("(TipoVerbale = %d or TipoVerbale = %d or TipoVerbale = %d or TipoVerbale = %d or TipoVerbale = %d or TipoVerbale = %d or TipoVerbale = %d or TipoVerbale = %d or TipoVerbale = %d or TipoVerbale = %d or TipoVerbale = %d or TipoVerbale = %d or TipoVerbale = %d)"
                 "AND (DataAccettazione > %s AND DataAccettazione <= %s)"
                 "AND ((DataAccettazione > %s AND ProgressivoTotale < %d)"
                 "OR (DataAccettazione < %s AND ProgressivoTotale > %d))",
                 VERB_IN_CONCESSIONE, 
								 VERB_NON_IN_CONCESSIONE, 
								 VERB_NC_PROVE_DI_CARICO, 
								 VERB_NC_CONGL_BITUMINOSI,
								 VERB_NC_INERTI,
								 VERB_NC_MONITORAGGI,
								 VERB_NC_VARIE,
								 VERB_NC_GEOTECNICA,
								 VERB_GEOLOGIA,
								 VERB_NC_LINEE_VITA,
									VERB_NC_INDAGINI_MURATURE,
									VERB_NC_INDAGINI_CLS,
									VERB_NC_MAT_METALLICI,
                 m_DataAccettazione.Format("%Y0000"),
                 m_DataAccettazione.Format("%Y1231"),
                 m_DataAccettazione.Format("%Y%m%d"), 
                 m_pVerbaliSet->m_ProgressivoTotale,
                 m_DataAccettazione.Format("%Y%m%d"), 
                 m_pVerbaliSet->m_ProgressivoTotale);
		m_pGlobalVerbaliSet->m_strFilter = query;
    m_pGlobalVerbaliSet->Requery();
		if(!m_pGlobalVerbaliSet->IsEOF())
		{
			msg.Format("La data %s scelta per il verbale corrente N° %d / %d\nnon è coerente con\nla data %s del verbale N° %d / %d",m_DataAccettazione.Format("%d/%m/%Y"), m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale, m_pGlobalVerbaliSet->m_DataAccettazione.Format("%d/%m/%Y"), m_pGlobalVerbaliSet->m_ProgressivoParziale,m_pGlobalVerbaliSet->m_ProgressivoTotale);
			AfxMessageBox(msg);
			return FALSE;
		}
	}
//--------------------------------------------------------------------------------//

	
  if(m_bUrgenza && m_DataConsegna < m_DataAccettazione)
  {
    AfxMessageBox("Attenzione: la data di consegna è precedente a quella di accettazione");
    return FALSE;
  }
  if(m_strNomeAzCertificato.GetLength() < 2 || m_strNomeAzCertificato.GetLength() < 2)
  {
    AfxMessageBox("Attenzione: il nome dell'azienda deve essere almeno due caratteri.");
    return FALSE;
  }
  if(m_strCodiceAzCertificato.IsEmpty() || m_strCodiceAzFattura.IsEmpty())
  {
    AfxMessageBox("Attenzione: inserire i codici delle aziende.");
    return FALSE;
  }
  if(m_bSpedizione && m_strDestinatario.IsEmpty())
  {
    if(AfxMessageBox("I dati per la spedizione del verbale non sono completi.\nVuoi continuare?", MB_YESNO) == IDYES)
      return TRUE;
    return FALSE;
  }
	if(m_nTipoVerbale == VERB_IN_CONCESSIONE && !m_nNumSerie)
	{
    if(AfxMessageBox("Il verbale con prove in concessione non contiene serie.\nSalvare ugualmente?", MB_YESNO) == IDYES)
      return TRUE;
    return FALSE;
	}
	if(
		(m_nTipoVerbale == VERB_NON_IN_CONCESSIONE && m_nNumSerie)	||
		(m_nTipoVerbale == VERB_NC_PROVE_DI_CARICO && m_nNumSerie)	||
		(m_nTipoVerbale == VERB_NC_CONGL_BITUMINOSI && m_nNumSerie) ||
		(m_nTipoVerbale == VERB_NC_INERTI && m_nNumSerie)						||
		(m_nTipoVerbale == VERB_NC_MONITORAGGI && m_nNumSerie)			||
		(m_nTipoVerbale == VERB_NC_VARIE && m_nNumSerie)						||
		(m_nTipoVerbale == VERB_NC_GEOTECNICA && m_nNumSerie)				||
		(m_nTipoVerbale == VERB_NC_LINEE_VITA && m_nNumSerie)				||
		(m_nTipoVerbale == VERB_NC_INDAGINI_MURATURE && m_nNumSerie)				||
		(m_nTipoVerbale == VERB_NC_INDAGINI_CLS && m_nNumSerie)				||
		(m_nTipoVerbale == VERB_NC_MAT_METALLICI && m_nNumSerie)
		)
	{
    if(AfxMessageBox("Il verbale senze prove in concessione contiene serie.\nSalvare ugualmente?", MB_YESNO) == IDYES)
      return TRUE;
    return FALSE;
	}
  return TRUE;
}

// Nuovo record
BOOL CVerbaliView::NewRecord()
{
	SetProveMateriale(FALSE, FALSE);
	
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  UpdateData(TRUE);
  m_CtrlDataAccettazione.GetTime(m_DataAccettazione);
  m_CtrlDataConsegna.GetTime(m_DataConsegna);

  if(!ValidateData())
    return FALSE;
  int nVerbale, n;
  // Inizio la transazione
  try
  {
    pApp->BeginTrans();
    // Blocco la tabella
    // Cerco i massimi per i progressivi parziali e totale
    FindNumVerbali(FALSE);
    m_pVerbaliSet->Edit();
    // Scrivo i dati nel record
    nVerbale = m_pVerbaliSet->m_Codice;
    m_pVerbaliSet->m_TipoVerbale = (long)m_nTipoVerbale;
    switch(m_nTipoVerbale)
    {
    case VERB_IN_CONCESSIONE:
      m_pVerbaliSet->m_ProgressivoParziale = m_nConCert;
      break;
    case VERB_NON_IN_CONCESSIONE:
		case VERB_NC_PROVE_DI_CARICO :
		case VERB_NC_CONGL_BITUMINOSI	:
		case VERB_NC_INERTI	:
		case VERB_NC_MONITORAGGI :
		case VERB_NC_VARIE	:
		case VERB_NC_GEOTECNICA :
		case VERB_NC_LINEE_VITA:
		case VERB_NC_INDAGINI_MURATURE:
		case VERB_NC_INDAGINI_CLS:
		case VERB_NC_MAT_METALLICI:
      m_pVerbaliSet->m_ProgressivoParziale = m_nSenzaCert;
      break;
    case VERB_GEOLOGIA:
      m_pVerbaliSet->m_ProgressivoParziale = m_nGeologia;
      break;
    }
    m_pVerbaliSet->m_ProgressivoTotale = m_nTotVerbali;
    // Operatore
    m_pVerbaliSet->m_Operatore = pApp->GetUserName();
    // Aggiorno il numero verbale nella form
    switch(m_nTipoVerbale)
    {
    case VERB_IN_CONCESSIONE:
      m_strTipoVerbale.Format("Verbale n° %d / %d\r\n Prove in concessione", m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale);
      break;
    case VERB_NON_IN_CONCESSIONE:
		case VERB_NC_PROVE_DI_CARICO :
		case VERB_NC_CONGL_BITUMINOSI	:
		case VERB_NC_INERTI	:
		case VERB_NC_MONITORAGGI :
		case VERB_NC_VARIE	:
		case VERB_NC_GEOTECNICA :
		case VERB_NC_LINEE_VITA:
		case VERB_NC_INDAGINI_MURATURE:
		case VERB_NC_INDAGINI_CLS:
		case VERB_NC_MAT_METALLICI:
#ifdef WINSIGMA2
			m_strTipoVerbale.Format("Verbale n° A%d", m_pVerbaliSet->m_ProgressivoTotale);	
#else
      m_strTipoVerbale.Format("Verbale n° %d / %d", m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale);
#endif
      break;
    case VERB_GEOLOGIA:
      m_strTipoVerbale.Format("Verbale n° %d / %d\r\n Prove geotecniche", m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale);
      break;
    }
    m_pVerbaliSet->m_DataAccettazione = m_DataAccettazione;
    m_pVerbaliSet->m_CodiceAzCertificato = m_nCodiceAzCertificato;
		m_pVerbaliSet->m_CodiceAzFattura     = m_nCodiceAzFattura;
		m_pVerbaliSet->m_CodiceImpresa       = m_nCodiceImpresa;
		m_pVerbaliSet->m_ListinoParticolare  = m_nListinoParticolare;
    m_pVerbaliSet->m_IDAzCertificato     = m_strCodiceAzCertificato;
  	m_pVerbaliSet->m_IDAzFattura         = m_strCodiceAzFattura;
    m_pVerbaliSet->m_P_IVA               = m_strPartitaIva;
    m_pVerbaliSet->m_CodFiscale          = m_strCodFiscale;
		m_pVerbaliSet->m_Pagamento           = m_strTipoPagamento;
  	m_pVerbaliSet->m_IDImpresaRichiedente = m_strCodiceImpresa;
  	m_pVerbaliSet->m_NomeAzCertificato = m_strNomeAzCertificato;
  	m_pVerbaliSet->m_NomeAzFattura = m_strNomeAzFattura;
  	m_pVerbaliSet->m_NomeImpresa = m_strNomeImpresa;
    m_pVerbaliSet->m_IndirizzoCertificato = m_strIndAzCertificati;
    m_pVerbaliSet->m_IndirizzoFattura = m_strIndAzFattura;
    m_pVerbaliSet->m_IndirizzoRichiedente = m_strIndImpresa;
    m_pVerbaliSet->m_ProveRichieste = m_strProveRichieste;
    m_pVerbaliSet->m_DescrizioneMateriale = m_strMaterialeConsegnato;
    m_pVerbaliSet->m_CertOgniSerie = m_bCertificatoOgniSerie;

    if (m_bRitiro)
      m_pVerbaliSet->m_Urgenza					  = 2;
    else
      m_pVerbaliSet->m_Urgenza					  = m_bUrgenza;
       
    //m_pVerbaliSet->m_Urgenza = m_bUrgenza;
    m_pVerbaliSet->m_DataConsegna = m_DataConsegna;
    m_pVerbaliSet->m_OraConsegna  = m_strOraConsegna;
    // Spedizione
    m_pVerbaliSet->m_Spedizione = m_bSpedizione;
    m_pVerbaliSet->m_LungaScadenza = m_bLungaScadenza;
    m_pVerbaliSet->m_Destinatario = m_strDestinatario;
    m_pVerbaliSet->m_NoteSpedizione = m_strNote;
    m_pVerbaliSet->m_LetteraIncarico = m_bLetteraIncarico;
    m_pVerbaliSet->m_NumLetteraIncarico = m_strLetteraIncarico;
    m_pVerbaliSet->m_Cantiere = m_strCantiere;
    m_pVerbaliSet->m_Direttore = m_strDirettore;
    m_pVerbaliSet->m_Proprietario = m_strProprietario;
    m_pVerbaliSet->m_DomandaSottoscritta = m_bDomandaSottoscritta;
    m_pVerbaliSet->m_Richiedente = m_strRichiedente;

		if(m_ComboTipoProva.GetItemData(m_ComboTipoProva.GetCurSel()) != -1)
					m_nTipoVerbale = m_pVerbaliSet->m_TipoVerbale = m_ComboTipoProva.GetItemData(m_ComboTipoProva.GetCurSel());
    
		// Definisco materiale e prove
		if(m_strMaterialeConsegnato.IsEmpty())
		  OnButtonAutoMateriale();
		if(m_strProveRichieste.IsEmpty())
		  OnButtonAutoProve();
    // Aggiorno il recordset
    m_pVerbaliSet->Update();
    // Sblocco la tabella
 
    // Cancello le serie che eventualmente sono state eliminate e i provini associati
    if(m_arySerieEliminate.GetSize())
    {
      m_pGlobalSerieSet->m_strFilter.Format("Verbale = %ld", nVerbale);
      m_pGlobalSerieSet->Requery();
      for(SET_START(m_pGlobalSerieSet); !m_pGlobalSerieSet->IsEOF(); m_pGlobalSerieSet->MoveNext())
      {
        for(n = 0; n < m_arySerieEliminate.GetSize(); n++)
          if(m_pGlobalSerieSet->m_Codice == (long)m_arySerieEliminate.GetAt(n))
            DeleteProvini(m_pGlobalSerieSet->m_Codice, FALSE);
      }
    }
		pApp->UpdateRecent(m_nCodiceAzFattura);
		pApp->UpdateRecent(m_nCodiceAzCertificato);
		pApp->UpdateRecent(m_nCodiceImpresa);
    // Committo la transazione
    pApp->CommitTrans();
  }
	catch(CDBException* e)
	{
		CString strError;
		pApp->Rollback();
    pApp->UnlockTables();
		strError = e->m_strError;
		AfxMessageBox(strError);
		return TRUE;
	}

	pApp->SetVerbaleInUso(m_pVerbaliSet->m_Codice, TRUE);
  m_pVerbaliSet->Requery();
  SINCRONIZE(m_pVerbaliSet, nVerbale);
  // Ho salvato -> cancello la lista delle serie aggiunte
  m_arySerieAggiunte.RemoveAll();
  pApp->ReloadTree(TREELABEL_VERBALIPRECEDENTI, -1);
  pApp->ReloadTree(TREELABEL_VERBALIULTIMOMESE, -1);
  SINCRONIZE(m_pVerbaliSet, nVerbale);
  UpdateData(FALSE);
  LoadCurRecord(TRUE);
  return TRUE;
}

// Salva le modifiche al record corrente
BOOL CVerbaliView::SaveRecord()
{
  UpdateData(TRUE);
	SetProveMateriale(FALSE, FALSE);

  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  
  m_CtrlDataAccettazione.GetTime(m_DataAccettazione);
  m_CtrlDataConsegna.GetTime(m_DataConsegna);

	if(!ValidateData())
		return FALSE;
	
  int nVerbale, n;
  long lCodiceFattura = m_pVerbaliSet->m_CodiceAzFattura;
  m_bSerieDataChanged = FALSE;
  nVerbale = m_pVerbaliSet->m_Codice;
  CSalvaStampaVerbaliDlg dlg;
  // Inizializzo i flag
  if(m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_DataPrimaStampa))
  {
    // E' la prima stampa
    // Controllo che ci sia il nome della stampante
    if((m_nTipoVerbale == VERB_IN_CONCESSIONE && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_CONCESSIONE).IsEmpty())
      || (m_nTipoVerbale == VERB_NON_IN_CONCESSIONE && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty())
			|| (m_nTipoVerbale == VERB_NC_PROVE_DI_CARICO && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty())
			|| (m_nTipoVerbale == VERB_NC_CONGL_BITUMINOSI && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty())
			|| (m_nTipoVerbale == VERB_NC_INERTI && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty())
			|| (m_nTipoVerbale == VERB_NC_MONITORAGGI && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty())
			|| (m_nTipoVerbale == VERB_NC_VARIE && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty())
			|| (m_nTipoVerbale == VERB_NC_GEOTECNICA && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty())
			|| (m_nTipoVerbale == VERB_GEOLOGIA && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_GEOLOGIA).IsEmpty())
			|| (m_nTipoVerbale == VERB_NC_LINEE_VITA && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty())
			|| (m_nTipoVerbale == VERB_NC_INDAGINI_MURATURE && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty())
			|| (m_nTipoVerbale == VERB_NC_INDAGINI_CLS && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty())
			|| (m_nTipoVerbale == VERB_NC_MAT_METALLICI && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty()))
      dlg.m_bPrintVerbale = FALSE;
    else
      dlg.m_bPrintVerbale = TRUE;
    dlg.m_bPrintMinuta = TRUE;
  }
  else
  {
    // ho già stampato
    dlg.m_bPrintVerbale = FALSE;
    dlg.m_bPrintMinuta = FALSE;
  }
  dlg.m_bPrintVerbaleCartaLibera = !dlg.m_bPrintVerbale;
	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  switch(dlg.DoModal())
	{
	  case IDOK:
      try
      {
				//assegno il valore automatico al materiale richiesto
        if(m_strMaterialeConsegnato.IsEmpty())
					OnButtonAutoMateriale();
				if(m_strProveRichieste.IsEmpty())
					OnButtonAutoProve();
        // Salvo i dati

				// Operazione misteriosa che risolve l'errore:
				// <<Nessuna riga è ststa influenzata dalle operazioni di aggiornamento o cancellazione!! Cod_err = 1008>>
				m_pGlobalVerbaliSet->m_strFilter.Format("Codice = %d", m_pVerbaliSet->m_Codice);
        m_pGlobalVerbaliSet->Requery();
				//-----------------------------------------------------------------------------------------------------//
				
        pApp->BeginTrans();	
		    m_pGlobalVerbaliSet->Edit();
        if(pApp->GetViewMode() != MODE_EDIT)
          m_pGlobalVerbaliSet->m_Operatore				  = pApp->GetUserName();
        m_pGlobalVerbaliSet->m_DataAccettazione		  = m_DataAccettazione;
    		m_pGlobalVerbaliSet->m_CodiceAzCertificato	= m_nCodiceAzCertificato;
    		m_pGlobalVerbaliSet->m_CodiceAzFattura			= m_nCodiceAzFattura;
    		m_pGlobalVerbaliSet->m_CodiceImpresa			  = m_nCodiceImpresa;
    		m_pGlobalVerbaliSet->m_ListinoParticolare		= m_nListinoParticolare;
        m_pGlobalVerbaliSet->m_IDAzCertificato			= m_strCodiceAzCertificato;
      	m_pGlobalVerbaliSet->m_IDAzFattura				  = m_strCodiceAzFattura;
      	m_pGlobalVerbaliSet->m_IDImpresaRichiedente	= m_strCodiceImpresa;
      	m_pGlobalVerbaliSet->m_NomeAzCertificato		= m_strNomeAzCertificato;
      	m_pGlobalVerbaliSet->m_NomeAzFattura			  = m_strNomeAzFattura;
        m_pGlobalVerbaliSet->m_P_IVA					      = m_strPartitaIva;
        m_pGlobalVerbaliSet->m_CodFiscale           = m_strCodFiscale;
        m_pGlobalVerbaliSet->m_Pagamento				    = m_strTipoPagamento;
      	m_pGlobalVerbaliSet->m_NomeImpresa				  = m_strNomeImpresa;
        m_pGlobalVerbaliSet->m_IndirizzoCertificato	= m_strIndAzCertificati;
        m_pGlobalVerbaliSet->m_IndirizzoFattura		  = m_strIndAzFattura;
        m_pGlobalVerbaliSet->m_IndirizzoRichiedente	= m_strIndImpresa;
        m_pGlobalVerbaliSet->m_ProveRichieste			  = m_strProveRichieste;
        m_pGlobalVerbaliSet->m_Spedizione				    = m_bSpedizione;
        m_pGlobalVerbaliSet->m_CertOgniSerie			  = m_bCertificatoOgniSerie;
        m_pGlobalVerbaliSet->m_DescrizioneMateriale	= m_strMaterialeConsegnato;
        
        if (m_bRitiro)
        {
          m_pGlobalVerbaliSet->m_Urgenza					  = 2;
          m_pGlobalVerbaliSet->SetFieldNull(&m_pGlobalVerbaliSet->m_OraConsegna);
        }
        else
        {
          m_pGlobalVerbaliSet->m_Urgenza					  = m_bUrgenza;
          m_pGlobalVerbaliSet->m_OraConsegna				= m_strOraConsegna;
        }
        
        m_pGlobalVerbaliSet->m_DataConsegna			    = m_DataConsegna;
        m_pGlobalVerbaliSet->m_Destinatario			    = m_strDestinatario;
        m_pGlobalVerbaliSet->m_NoteSpedizione			  = m_strNote;
        m_pGlobalVerbaliSet->m_LetteraIncarico			= m_bLetteraIncarico;
        m_pGlobalVerbaliSet->m_NumLetteraIncarico		= m_strLetteraIncarico;
        m_pGlobalVerbaliSet->m_Cantiere				      = m_strCantiere;
        m_pGlobalVerbaliSet->m_Direttore				    = m_strDirettore;
        m_pGlobalVerbaliSet->m_Proprietario			    = m_strProprietario;
        m_pGlobalVerbaliSet->m_Richiedente				  = m_strRichiedente;
        m_pGlobalVerbaliSet->m_DomandaSottoscritta  = m_bDomandaSottoscritta;
	    	m_pGlobalVerbaliSet->m_LungaScadenza			  = m_bLungaScadenza;

				if(m_ComboTipoProva.GetItemData(m_ComboTipoProva.GetCurSel()) != -1)
					m_nTipoVerbale = m_pGlobalVerbaliSet->m_TipoVerbale = m_ComboTipoProva.GetItemData(m_ComboTipoProva.GetCurSel());

        m_pGlobalVerbaliSet->Update();

        m_pGlobalSerieSet->m_strFilter.Format("Verbale = %ld", nVerbale);
        m_pGlobalSerieSet->Requery();
        // Cancello le serie che erano state eliminate e i provini associati
        for(SET_START(m_pGlobalSerieSet); !m_pGlobalSerieSet->IsEOF(); m_pGlobalSerieSet->MoveNext())
        {
          for(n = 0; n < m_arySerieEliminate.GetSize(); n++)
          {
            if(m_pGlobalSerieSet->m_Codice == (long)m_arySerieEliminate.GetAt(n))
              DeleteProvini(m_pGlobalSerieSet->m_Codice, FALSE);
          }
        }
				// Committo la transazione
        pApp->CommitTrans();  

        m_pVerbaliSet->Requery();
        
        // Ho salvato -> cancello la lista delle serie aggiunte
        m_arySerieAggiunte.RemoveAll();
        SINCRONIZE(m_pVerbaliSet, nVerbale);
        if(!m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_NumeroFattura))
        {
          if(m_pVerbaliSet->m_NumeroFattura == 0)
          {
            pApp->ReloadTree(TREELABEL_FATTUREDAEMETTERE, lCodiceFattura);
            pApp->ReloadTree(TREELABEL_FATTUREDAEMETTERE, m_pVerbaliSet->m_CodiceAzFattura);
          }
        }
        if(pDoc->m_nSelectedTreeVerbali == TREEITEM_VERBFATTPROFORMA)
          pApp->ReloadTree(TREELABEL_VERBALIFATTPROFORMA, nVerbale);
        if(pDoc->m_nSelectedTreeVerbali == TREEITEM_VERBALIPRECEDENTI)
          pApp->ReloadTree(TREELABEL_VERBALIPRECEDENTI, nVerbale);
        if(pDoc->m_nSelectedTreeVerbali == TREEITEM_VERBALIULTIMOMESE)
          pApp->ReloadTree(TREELABEL_VERBALIULTIMOMESE, nVerbale);
      }
    	catch(CDBException* e)
    	{
    		CString strError;
    		pApp->Rollback();
    		strError.Format("%s CODICE ECC: %d", e->m_strError, e->m_nRetCode);
    		AfxMessageBox(strError);
        return FALSE;
    	}

			pApp->SetVerbaleInUso(m_pVerbaliSet->m_Codice, TRUE );
		  break;
    case IDC_BUTTON_NO:
      m_pGlobalSerieSet->m_strFilter.Format("Verbale = %d", nVerbale);
      m_pGlobalSerieSet->Requery();
      // Cancello i record delle serie che eventualmente avevo aggiunto
      for(SET_START(m_pGlobalSerieSet); !m_pGlobalSerieSet->IsEOF(); m_pGlobalSerieSet->MoveNext())
      {
        for(n = 0; n < m_arySerieAggiunte.GetSize(); n++)
        {
          if(m_pGlobalSerieSet->m_Codice == (long)m_arySerieAggiunte.GetAt(n))
            DeleteProvini(m_pGlobalSerieSet->m_Codice, !m_bSerieDataChanged);
        }
      }
      // Cancello le liste
      m_arySerieAggiunte.RemoveAll();
      m_arySerieEliminate.RemoveAll();
      // Ricarico il record corrente
      LoadCurRecord(TRUE);
      UpdateData(FALSE);
			pApp->SetVerbaleInUso( m_pVerbaliSet->m_Codice, TRUE );
		  break;
		case IDCANCEL:
      return FALSE;
	}
	return TRUE;
}

BOOL CVerbaliView::DeleteRecord()
{
	return FALSE;
}

void CVerbaliView::EnableControls(BOOL bEnable)
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

  if(pApp->GetViewMode() != MODE_EDIT_PROVINI)
  {
    m_BtnDatiProvini.EnableWindow(FALSE);
    // Accettazione
    m_CtrlDataAccettazione.EnableWindow(bEnable);

    if ((m_bUrgenza) || (m_bRitiro))
    {
      m_CtrlDataConsegna.EnableWindow(bEnable);
      m_EditOraConsegna.EnableWindow(bEnable);
    }
    else
    {
      m_CtrlDataConsegna.EnableWindow(FALSE);
      m_EditOraConsegna.EnableWindow(FALSE);
    }

    if(!m_bNuovoVerbale)
      m_CtrlDataAccettazione.EnableWindow(FALSE);
    // Intestazioni
		m_CtrlDataAccettazione.EnableWindow(bEnable);
    m_EditCodiceAzCertificato.EnableWindow(bEnable);
    m_EditNomeAzCertificato.EnableWindow(bEnable);
    m_EditCodiceAzFattura.EnableWindow(bEnable);
    m_EditNomeAzFattura.EnableWindow(bEnable);
    m_EditCodiceAzImpresa.EnableWindow(bEnable);
    m_EditNomeAzImpresa.EnableWindow(bEnable);
    m_BtnCopia.EnableWindow(bEnable);
    // Altri dati
    m_BtnLettera.EnableWindow(bEnable);
    if(m_bLetteraIncarico && bEnable)
      m_EditLetteraIncarico.EnableWindow();
    else
      m_EditLetteraIncarico.EnableWindow(FALSE);
    m_EditDirettore.EnableWindow(bEnable);
    m_EditProprietario.EnableWindow(bEnable);
    m_BtnDomandaSottoscritta.EnableWindow(bEnable);
    m_EditRichiedente.EnableWindow(bEnable);
    m_EditCantiere.EnableWindow(bEnable);
    // Prove richieste
    m_EditProveRichieste.EnableWindow(bEnable);
    m_BtnAutoProve.EnableWindow(bEnable);
    // Materiale consegnato
    m_EditMaterialeConsegnato.EnableWindow(bEnable);
    m_BtnAutoMateriale.EnableWindow(bEnable);
    // Altri servizi
    m_BtnUrgenza.EnableWindow(bEnable);
    m_BtnLungaScadenza.EnableWindow(bEnable);
    // Dati spedizione
		m_EditDestinatario.EnableWindow(bEnable & m_bSpedizione);
    m_EditNote.EnableWindow(bEnable);
  	m_ComboConsegna.EnableWindow(bEnable);
    // Serie
    m_BtnModificaSerie.EnableWindow(bEnable);
    if(CheckEditableSeries(FALSE))
    {
      m_BtnAggiungiSerie.EnableWindow(bEnable);
      m_BtnEliminaSerie.EnableWindow(bEnable);
      m_BtnOgniSerie.EnableWindow(bEnable);
    }
    else
    {
      m_BtnAggiungiSerie.EnableWindow(FALSE);
      m_BtnEliminaSerie.EnableWindow(FALSE);
      m_BtnOgniSerie.EnableWindow(FALSE);
    }
    m_EditNumSerie.EnableWindow(bEnable);
    m_EditCosto.EnableWindow(bEnable);

    m_chkRitiro.EnableWindow(bEnable);
		
		if((m_nTipoVerbale == VERB_NON_IN_CONCESSIONE)		||
				(m_nTipoVerbale == VERB_NC_PROVE_DI_CARICO)		||
				(m_nTipoVerbale == VERB_NC_CONGL_BITUMINOSI)	||
				(m_nTipoVerbale == VERB_NC_INERTI)						||
				(m_nTipoVerbale == VERB_NC_MONITORAGGI)				||
				(m_nTipoVerbale == VERB_NC_VARIE)							||
				(m_nTipoVerbale == VERB_NC_GEOTECNICA)				||
				(m_nTipoVerbale == VERB_NC_LINEE_VITA)				||
				(m_nTipoVerbale == VERB_NC_INDAGINI_MURATURE)				||
				(m_nTipoVerbale == VERB_NC_INDAGINI_CLS)				||
				(m_nTipoVerbale == VERB_NC_MAT_METALLICI)
			)
			m_ComboTipoProva.EnableWindow(bEnable);
  }
  else
  {
    m_BtnDatiProvini.EnableWindow(bEnable);
    m_ListSerie.EnableWindow(bEnable);
    m_EditCosto.EnableWindow(bEnable);
  }

}

CString CVerbaliView::GetToolTip(int nID)
{
  switch(nID)
	{
	  case ID_NUOVO:
    	return "Crea un nuovo verbale per Certificati in concessione ministeriale\nNuovo in concessione";
		case ID_MODIFICA:
		  return "Consente la modifica dei dati di accetazione del verbale\nModifica verbale";
		case ID_ELIMINA:
		  return "Elimina verbale";
    default:
      return "";
	}
}


// Abilita/disabilita le check box dei servizi aggiuntivi e il servizio
void CVerbaliView::EnableAddedServices(int service, BOOL bEnable, BOOL bSet)
{
  switch(service)
  {
  case SERV_OGNI_SERIE:
    m_bCertificatoOgniSerie = bSet;
    m_BtnOgniSerie.EnableWindow(bEnable);
    break;
  case SERV_URGENZA:
    m_bUrgenza = bSet;
    m_BtnUrgenza.EnableWindow(bEnable);
    break;
  }
}

// Crea un nuovo verbale che contiene certificati in concessione
void CVerbaliView::OnNuovo()
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	if( MODE_EDIT == pApp->GetViewMode())
		return;
  m_pVerbaliSet = ((CWinSigmaDoc*)GetDocument())->m_pVerbaliUltimoMeseSet;
  if(pApp->GetViewMode() != MODE_NEW)
    LoadCurRecord(FALSE);
  m_strTipoVerbale = STR_CONCERTIFICATO;
	m_bDomandaSottoscritta = TRUE;
  m_nTipoVerbale = VERB_IN_CONCESSIONE;
  NuovoVerbale(MODE_NEW);

	m_ComboTipoProva.ResetContent();
}

// Crea un nuovo verbale che non contiene certificati in concessione
void CVerbaliView::OnNuovoVerbale() 
{
	int n = 0;

	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	if( MODE_EDIT == pApp->GetViewMode())
		return;
  m_pVerbaliSet = ((CWinSigmaDoc*)GetDocument())->m_pVerbaliUltimoMeseSet;
  if(pApp->GetViewMode() != MODE_NEW_VERB)
    LoadCurRecord(FALSE);
  m_strTipoVerbale = STR_SENZACERTIFICATO;
  m_bDomandaSottoscritta = FALSE;
  m_nTipoVerbale = VERB_NON_IN_CONCESSIONE;
	m_EditNomeAzCertificato.SetFocus();
  NuovoVerbale(MODE_NEW_VERB);

	m_ComboTipoProva.ResetContent();
	n = m_ComboTipoProva.AddString("Prove di carico - PC");
	m_ComboTipoProva.SetItemData(n, VERB_NC_PROVE_DI_CARICO);	
	n = m_ComboTipoProva.AddString("Conglomerati bituminosi - CB");
	m_ComboTipoProva.SetItemData(n, VERB_NC_CONGL_BITUMINOSI);	
	n = m_ComboTipoProva.AddString("Inerti e rocce - I");
	m_ComboTipoProva.SetItemData(n, VERB_NC_INERTI);	
	n = m_ComboTipoProva.AddString("Monitoraggi - MO");
	m_ComboTipoProva.SetItemData(n, VERB_NC_MONITORAGGI);	
	n = m_ComboTipoProva.AddString("Varie - V");
	m_ComboTipoProva.SetItemData(n, VERB_NC_VARIE);
	n = m_ComboTipoProva.AddString("Geotecnica - NC");
	m_ComboTipoProva.SetItemData(n, VERB_NC_GEOTECNICA);
	n = m_ComboTipoProva.AddString("Linee Vita - LV");
	m_ComboTipoProva.SetItemData(n, VERB_NC_LINEE_VITA);
	n = m_ComboTipoProva.AddString("Indagini su murature - IM");
	m_ComboTipoProva.SetItemData(n, VERB_NC_INDAGINI_MURATURE);
	n = m_ComboTipoProva.AddString("Indagini su CLS - IC");
	m_ComboTipoProva.SetItemData(n, VERB_NC_INDAGINI_CLS);
	n = m_ComboTipoProva.AddString("Materiali metallici - MM");
	m_ComboTipoProva.SetItemData(n, VERB_NC_MAT_METALLICI);
}


// Crea un nuovo verbale per prove geologiche
void CVerbaliView::OnNuovoGeologia() 
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	if( MODE_EDIT == pApp->GetViewMode())
		return;
  m_pVerbaliSet = ((CWinSigmaDoc*)GetDocument())->m_pVerbaliUltimoMeseSet;
  if(pApp->GetViewMode() != MODE_NEW_GEO)
    LoadCurRecord(FALSE);
  m_strTipoVerbale = STR_GEOLOGIA;
  m_bDomandaSottoscritta = FALSE;
  m_nTipoVerbale = VERB_GEOLOGIA;
	m_EditNomeAzCertificato.SetFocus();
  NuovoVerbale(MODE_NEW_GEO);
	
	m_ComboTipoProva.ResetContent();
}


void CVerbaliView::NuovoVerbale(WORD ViewMode)
{
	int n = 0;
	int maxCodice;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  int nVerbale;
  CListiniSet* pListinoSet;
  CSalvaStampaVerbaliDlg dlg;

  switch(pApp->GetViewMode())
	{
	  case MODE_VIEW:
			//Verifico la presenza di un verbale in fase di presunto inserimento
			m_pGlobalVerbaliSet->m_strFilter.Format("InUso = '%s'", INSERIMENTO_NUOVO_VERBALE);
      m_pGlobalVerbaliSet->Requery();
			if(!m_pGlobalVerbaliSet->IsEOF())
			{
				AfxMessageBox("L'operazione di inserimento non è al momento disponibile.");
				return;
			}
			//-----------------------------------------------------------------//

      m_arySerieEliminate.RemoveAll();
      m_aryPosSerie.RemoveAll();
      LoadCurRecord(FALSE);
      m_bNuovoVerbale = TRUE;
      m_nCodiceAzFattura = -1;     
      m_nCodiceUltimaSerie = -1;
			// Cerco il listino generale
      pListinoSet = pDoc->m_pListiniInVigoreSet;
			for(SET_START(pListinoSet); !pListinoSet->IsEOF(); pListinoSet->MoveNext())
			{
				if(pListinoSet->IsFieldNull(&pListinoSet->m_Azienda)
					 || pListinoSet->m_Azienda == 0)
					break;
			}
			if(!pListinoSet->IsEOF())
			  m_nListinoGenerale = pListinoSet->m_Codice;
			else
			  m_nListinoGenerale = 0;
      // Blocco la tabella
      pApp->LockTable(VERBALI);      
      FindNumVerbali(TRUE);
      m_nTotVerbaliProvv++;
      switch(m_nTipoVerbale)
      {
      case VERB_IN_CONCESSIONE:
				m_strTipoVerbale.Format("Verbale n° %d / %d\r\n Prove in concessione", ++m_nConCertProvv, m_nTotVerbaliProvv);
				break;
      case VERB_NON_IN_CONCESSIONE:
			case VERB_NC_PROVE_DI_CARICO :
			case VERB_NC_CONGL_BITUMINOSI	:
			case VERB_NC_INERTI	:
			case VERB_NC_MONITORAGGI :
			case VERB_NC_VARIE	:
			case VERB_NC_GEOTECNICA	:
			case VERB_NC_LINEE_VITA:
			case VERB_NC_INDAGINI_MURATURE:
			case VERB_NC_INDAGINI_CLS:
			case VERB_NC_MAT_METALLICI:
#ifdef WINSIGMA2
				m_strTipoVerbale.Format("Verbale n° A%d", m_nTotVerbaliProvv);	
#else
				m_strTipoVerbale.Format("Verbale n° %d / %d", ++m_nSenzaCertProvv, m_nTotVerbaliProvv);	
#endif
				break;
      case VERB_GEOLOGIA:
				m_strTipoVerbale.Format("Verbale n° %d / %d\r\n Prove geotecniche", ++m_nGeologiaProvv, m_nTotVerbaliProvv);
				break;
      }
      m_nSeriePos = 1;
      m_nCertificati = 1;
      m_nNumeroProvini = 0;
			if(pListinoSet->IsEOF())
			  m_bCertificatoOgniSerie = 0;
			else
				m_bCertificatoOgniSerie = pListinoSet->m_CertOgniSerie;
      // Aggiungo il nuovo record
			ASSERT(m_nListinoGenerale);
      m_pVerbaliSet->AddNew();
			m_pVerbaliSet->m_InUso = INSERIMENTO_NUOVO_VERBALE;
      m_pVerbaliSet->m_DataAccettazione = CTime::GetCurrentTime();
      switch(m_nTipoVerbale)
      {
      case VERB_IN_CONCESSIONE:
        m_pVerbaliSet->m_ProgressivoParziale = m_nConCertProvv;
        break;
      case VERB_NON_IN_CONCESSIONE:
			case VERB_NC_PROVE_DI_CARICO :
			case VERB_NC_CONGL_BITUMINOSI	:
			case VERB_NC_INERTI	:
			case VERB_NC_MONITORAGGI :
			case VERB_NC_VARIE	:
			case VERB_NC_GEOTECNICA	:
			case VERB_NC_LINEE_VITA:
			case VERB_NC_INDAGINI_MURATURE:
			case VERB_NC_INDAGINI_CLS:
			case VERB_NC_MAT_METALLICI:
        m_pVerbaliSet->m_ProgressivoParziale = m_nSenzaCertProvv;
        break;
      case VERB_GEOLOGIA:
        m_pVerbaliSet->m_ProgressivoParziale = m_nGeologiaProvv;
        break;
      }
      m_pVerbaliSet->m_ProgressivoTotale = m_nTotVerbaliProvv;
      m_pVerbaliSet->m_TipoVerbale = m_nTipoVerbale;
      // Listino
      m_pVerbaliSet->m_ListinoGenerale = m_nListinoGenerale;
			m_pVerbaliSet->m_CertOgniSerie   = pListinoSet->m_CertOgniSerie;
      m_pVerbaliSet->Update();
      if(m_pVerbaliSet->Requery())
      {
        maxCodice = 0;
        // Cerco il codice più grande
        for(SET_START(m_pVerbaliSet); !m_pVerbaliSet->IsEOF(); m_pVerbaliSet->MoveNext())
        {
          if(maxCodice < m_pVerbaliSet->m_Codice)
            maxCodice = m_pVerbaliSet->m_Codice;
        }
        // seleziono il recordset col codice più grande
        for(SET_START(m_pVerbaliSet); !m_pVerbaliSet->IsEOF(); m_pVerbaliSet->MoveNext())
        {
          if(maxCodice == m_pVerbaliSet->m_Codice)
            break;
        }
      }
      pApp->UnlockTables();
			UpdateData(FALSE);
		  pApp->SetViewMode(ViewMode);
  	  EnableControls(TRUE);
			break;
    case MODE_NEW_VERB:
    case MODE_NEW:
    case MODE_NEW_GEO:
			UpdateData();

      // Inizializzo i flag
      if((m_nTipoVerbale == VERB_IN_CONCESSIONE && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_CONCESSIONE).IsEmpty())
        || (m_nTipoVerbale == VERB_NON_IN_CONCESSIONE && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty())
 				|| (m_nTipoVerbale == VERB_NC_PROVE_DI_CARICO && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty())
				|| (m_nTipoVerbale == VERB_NC_CONGL_BITUMINOSI && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty())
				|| (m_nTipoVerbale == VERB_NC_INERTI && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty())
				|| (m_nTipoVerbale == VERB_NC_MONITORAGGI && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty())
				|| (m_nTipoVerbale == VERB_NC_VARIE && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty())	
				|| (m_nTipoVerbale == VERB_GEOLOGIA && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_GEOLOGIA).IsEmpty())
				|| (m_nTipoVerbale == VERB_NC_LINEE_VITA && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty())
				|| (m_nTipoVerbale == VERB_NC_INDAGINI_MURATURE && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty())
				|| (m_nTipoVerbale == VERB_NC_INDAGINI_CLS && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty())
				|| (m_nTipoVerbale == VERB_NC_MAT_METALLICI && pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE).IsEmpty()))
        dlg.m_bPrintVerbale = FALSE;
      else
        dlg.m_bPrintVerbale = TRUE;
      dlg.m_bPrintMinuta = TRUE;
      dlg.m_bPrintVerbaleCartaLibera = !dlg.m_bPrintVerbale;
			switch(dlg.DoModal())
			{
				case IDOK:
				  if(NewRecord())
					{
            m_bNuovoVerbale = FALSE;
            m_bSerieDataChanged = FALSE;
		        pApp->SetViewMode(MODE_VIEW);
		        EnableControls(FALSE);
          }
  				break;
				case IDCANCEL:
          break;
        case IDC_BUTTON_NO:
          m_strTipoVerbale.Empty();
          nVerbale = m_pVerbaliSet->m_Codice;
          try
          {
            pApp->BeginTrans();
            // Blocco la tabella
            pApp->LockTable(VERBALI);
            // Cancello il record del verbale
            m_pVerbaliSet->Delete(); 
            pApp->UnlockTables();
            pApp->CommitTrans();
          }
        	catch(CDBException* e)
        	{
        		pApp->Rollback();
            pApp->UnlockTables();
        		AfxMessageBox(e->m_strError);
            return;
        	}
          m_pGlobalSerieSet->m_strFilter.Format("Verbale = %ld", nVerbale);
          m_pGlobalSerieSet->Requery();
          // Cancello le serie associate al verbale
          for(SET_START(m_pGlobalSerieSet); !m_pGlobalSerieSet->IsEOF(); m_pGlobalSerieSet->MoveNext())
          {
              // cancello i provini
              DeleteProvini(m_pGlobalSerieSet->m_Codice, FALSE);
          }

          LoadCurRecord(FALSE);
          m_arySerieAggiunte.RemoveAll();
          m_arySerieEliminate.RemoveAll();
		    	UpdateData(FALSE);
	        pApp->SetViewMode(MODE_VIEW);
 	        EnableControls(FALSE);
          while(!m_pVerbaliSet->IsBOF())
            m_pVerbaliSet->MovePrev();
					break;
			}
      break;
		default:
		  MessageBeep(-1);
			break;
	}
}


// Cerca nel db i valori massimi per i progressivi parziali e totale
void CVerbaliView::FindNumVerbali(BOOL bProvvisori)
{
  int nConCert, nSenzaCert, nGeologia, nTot;

  CTime date(CTime::GetCurrentTime().GetYear(), 1, 1, 0, 0, 0);
		m_pGlobalVerbaliSet->m_strFilter.Format("(TipoVerbale = %d or TipoVerbale = %d or TipoVerbale = %d or TipoVerbale = %d or TipoVerbale = %d or TipoVerbale = %d or TipoVerbale = %d or Tipoverbale = %d or Tipoverbale = %d or Tipoverbale = %d or Tipoverbale = %d or Tipoverbale = %d or Tipoverbale = %d) and DataAccettazione >= '%s'", 
																							VERB_IN_CONCESSIONE, 
																							VERB_NON_IN_CONCESSIONE,
																							VERB_NC_PROVE_DI_CARICO,
																							VERB_NC_CONGL_BITUMINOSI,
																							VERB_NC_INERTI,
																							VERB_NC_MONITORAGGI,
																							VERB_NC_VARIE,
																							VERB_NC_GEOTECNICA,
																							VERB_GEOLOGIA, 
																							VERB_NC_LINEE_VITA,
																							VERB_NC_INDAGINI_MURATURE,
																							VERB_NC_INDAGINI_CLS,
																							VERB_NC_MAT_METALLICI,
																							date.Format("%Y-%m-%d %H:%M:%S"));
  m_pGlobalVerbaliSet->Requery();
  nConCert = nSenzaCert = nGeologia = nTot = 0;
  for(SET_START(m_pGlobalVerbaliSet); !m_pGlobalVerbaliSet->IsEOF(); m_pGlobalVerbaliSet->MoveNext())
  {
    if(m_pGlobalVerbaliSet->m_TipoVerbale == VERB_IN_CONCESSIONE)
    {
      if(m_pGlobalVerbaliSet->m_ProgressivoParziale > nConCert)
        nConCert = m_pGlobalVerbaliSet->m_ProgressivoParziale;
    }
    else if	(
						(m_pGlobalVerbaliSet->m_TipoVerbale == VERB_NON_IN_CONCESSIONE)		||
						(m_pGlobalVerbaliSet->m_TipoVerbale == VERB_NC_PROVE_DI_CARICO)		||
						(m_pGlobalVerbaliSet->m_TipoVerbale == VERB_NC_CONGL_BITUMINOSI)	||
						(m_pGlobalVerbaliSet->m_TipoVerbale == VERB_NC_INERTI)						||
						(m_pGlobalVerbaliSet->m_TipoVerbale == VERB_NC_MONITORAGGI)				||
						(m_pGlobalVerbaliSet->m_TipoVerbale == VERB_NC_VARIE)							||
						(m_pGlobalVerbaliSet->m_TipoVerbale == VERB_NC_GEOTECNICA)				||
						(m_pGlobalVerbaliSet->m_TipoVerbale == VERB_NC_LINEE_VITA)				||
						(m_pGlobalVerbaliSet->m_TipoVerbale == VERB_NC_INDAGINI_MURATURE)	||
						(m_pGlobalVerbaliSet->m_TipoVerbale == VERB_NC_INDAGINI_CLS)			||
						(m_pGlobalVerbaliSet->m_TipoVerbale == VERB_NC_MAT_METALLICI)
						)
    {
      if(m_pGlobalVerbaliSet->m_ProgressivoParziale > nSenzaCert)
        nSenzaCert = m_pGlobalVerbaliSet->m_ProgressivoParziale;
    }
    else if(m_pGlobalVerbaliSet->m_TipoVerbale == VERB_GEOLOGIA)
    {
      if(m_pGlobalVerbaliSet->m_ProgressivoParziale > nGeologia)
        nGeologia = m_pGlobalVerbaliSet->m_ProgressivoParziale;
    }
    if(m_pGlobalVerbaliSet->m_ProgressivoTotale > nTot)
      nTot = m_pGlobalVerbaliSet->m_ProgressivoTotale;
  }
  if(bProvvisori)
  {
    m_nConCertProvv    = nConCert;
    m_nSenzaCertProvv  = nSenzaCert;
    m_nGeologiaProvv   = nGeologia;
    m_nTotVerbaliProvv = nTot;
  }
  else
  {
    m_nConCert    = nConCert;
    m_nSenzaCert  = nSenzaCert;
    m_nGeologia   = nGeologia;
    m_nTotVerbali = nTot;
  }
}


// Aggiunge una serie
void CVerbaliView::OnButtonAggiungi() 
{
	CSerieDlg dlg;
  CString str;

	UpdateData();
  // Inizializzo i dati del dialogo
  dlg.m_pDoc = (CWinSigmaDoc*)GetDocument();
  dlg.m_nNumeroVerbale = m_pVerbaliSet->m_Codice;
  dlg.m_strTitolo = "Inserisci serie";
  dlg.m_bNuovaSerie = TRUE;
  dlg.m_nCodiceAzienda = m_nCodiceAzFattura;
  // Se il certificato è pieno o è settato il flag "per ogni serie", 
  // imposto il flag di nuovo certificato e disabilito il controllo
  m_pGlobalSerieSet->m_strFilter.Format("Verbale = %d", m_pVerbaliSet->m_Codice);
  m_pGlobalSerieSet->Requery();
  if(m_pGlobalSerieSet->IsEOF())
	{
    dlg.m_bNuovoCertificato = TRUE;
    dlg.m_bEnableNuovo = FALSE;
  }
	else
	{
    if (m_nCodiceUltimaSerie != -1)
      SINCRONIZE(m_pGlobalSerieSet, m_nCodiceUltimaSerie);
    SINCRONIZE(m_pTipiCertificatoSet, m_pGlobalSerieSet->m_TipoCertificato);
	  if(m_bCertificatoOgniSerie 
			|| m_nNumeroProvini == m_pTipiCertificatoSet->m_ProvXcertificato 
			|| !m_nNumeroProvini)
	  {
	    dlg.m_bNuovoCertificato = TRUE;
	    dlg.m_bEnableNuovo = FALSE;
	  }
	  else
	    dlg.m_bEnableNuovo = TRUE;
	}
		
  dlg.m_nNumeroProvini = m_nNumeroProvini;
  dlg.m_bEnableTipo = TRUE;
  dlg.m_strPosizione.Format("%d/%d", m_nSeriePos, m_nCertificati);
  dlg.m_nOldPos = m_nSeriePos;
  dlg.m_bAccListGen = m_bListinoGenerale;
  // Listini
  dlg.m_nListinoParticolare = m_nListinoParticolare;
  dlg.m_nListinoGenerale    = m_nListinoGenerale;
  if(m_nNumSerie && m_nCodiceUltimaSerie > 0)
    dlg.m_nCodiceSerie = m_nCodiceUltimaSerie;
  else
    dlg.m_nCodiceSerie = -1;
  
  // Salva la posizione attuale all'interno della lista
  POSITION pos = m_ListSerie.GetFirstSelectedItemPosition();
  int n = m_ListSerie.GetNextSelectedItem(pos);

  if(dlg.DoModal() == IDOK)
  {
    m_arySerieAggiunte.Add((DWORD)dlg.m_nCodiceSerie);
    m_nNumSerie++;
    m_nNumeroProvini += dlg.m_nProviniRichiesti;
    m_bSerieDataChanged = TRUE;
    m_nCodiceUltimaSerie = dlg.m_nCodiceSerie;
    m_pGlobalSerieSet->m_strFilter.Format("Codice = %d", m_nCodiceUltimaSerie);
    m_pGlobalSerieSet->Requery();
    AddProvini(m_pGlobalSerieSet);
    LoadSeries(m_pVerbaliSet->m_Codice);
    // Il verbale è in fatturazione, erogo i servizi associati alla serie che ho appena aggiunto
    if(!m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_NumeroFattura) && m_pVerbaliSet->m_NumeroFattura == 0)
      ErogaServiziSerie(m_pGlobalSerieSet);
  }

  if (n != -1)
  {
    m_ListSerie.SetItemState(n, LVIS_SELECTED, LVIS_SELECTED);
    
    // Scrolla la lista fino al punto del record selezionato
    CSize size;
    CRect rect;
    m_ListSerie.GetItemRect(n,rect,LVIR_LABEL);
    size.cy =  (rect.bottom - rect.top) * n;
    m_ListSerie.Scroll(size);
  }

  UpdateData(FALSE);
}

void CVerbaliView::OnDblclkListSerie(NMHDR* pNMHDR, LRESULT* pResult) 
{
  int n;
  POSITION pos;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

  UpdateData();
  if(m_pVerbaliSet->IsBOF() || m_pVerbaliSet->IsEOF())
  {
    MessageBeep(-1);
    return;
  }
  pos = m_ListSerie.GetFirstSelectedItemPosition();
	if((n = m_ListSerie.GetNextSelectedItem(pos)) < 0)
  {
    AfxMessageBox("Selezionare un dato valido!");
	  return;
  }
  switch(pApp->GetViewMode())
	{
	  case MODE_EDIT_PROVINI:
		  ModificaRisultati( n );
			break;
		case MODE_EDIT:
		  ModificaSerie(n);
			break;
		default:
		  break;
	}
	*pResult = 0;
  UpdateData(FALSE);
}

void CVerbaliView::OnDatiProvini() 
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

  if(m_pVerbaliSet->IsBOF() || m_pVerbaliSet->IsEOF())
  {
    MessageBeep(-1);
    return;
  }
  /*if(!CheckEditableSeries(TRUE))
  {
    AfxMessageBox("Il verbale è in certificazione: non è possibile modificarne i dati");
    return;
  }*/

	

  if(pApp->GetViewMode() == MODE_EDIT_PROVINI)
	{
	  pApp->SetViewMode(MODE_VIEW);
  	EnableControls(FALSE);
		pApp->SetVerbaleInUso(m_pVerbaliSet->m_Codice, TRUE);

    int pos = m_ListSerie.GetSelectionMark();
    CString str = m_ListSerie.GetItemText(pos,1);
    if ((!str.IsEmpty()) && (str!="-----"))
      m_BtnEmenda.EnableWindow(TRUE);
	}
	else if(pApp->GetViewMode() == MODE_VIEW)
	{
		if(!pApp->SetVerbaleInUso(m_pVerbaliSet->m_Codice))
			return;
	  pApp->SetViewMode(MODE_EDIT_PROVINI);
  	EnableControls(TRUE);

    m_BtnEmenda.EnableWindow(FALSE);
	}
	else
	  MessageBeep(-1);
}

void CVerbaliView::OnButtonDatiProvini() 
{
  int n;
  POSITION pos;
  pos = m_ListSerie.GetFirstSelectedItemPosition();
	if((n = m_ListSerie.GetNextSelectedItem(pos)) < 0)
  {
    AfxMessageBox("Selezionare un dato valido!");
	  return;
  }
	ModificaRisultati(n);
}

// Modifica i dati di una serie
void CVerbaliView::OnButtonModifica() 
{
  int n;
  POSITION pos;
  
	UpdateData();
  pos = m_ListSerie.GetFirstSelectedItemPosition();
	if((n = m_ListSerie.GetNextSelectedItem(pos)) < 0)
  {
    AfxMessageBox("Selezionare un dato valido!");
	  return;
  }
  ModificaSerie(n);

  int itm = m_ListSerie.GetItemCount();;

  UpdateData(FALSE);

  m_ListSerie.SetItemState(n, LVIS_SELECTED, LVIS_SELECTED);
  
  // Scrolla la lista fino al punto del record selezionato
  CSize size;
  CRect rect;
  m_ListSerie.GetItemRect(n,rect,LVIR_LABEL);
  size.cy =  (rect.bottom - rect.top) * n;
  m_ListSerie.Scroll(size);

} 

void CVerbaliView::ModificaSerie(int n)
{
  CSerieDlg dlg;
  int i;
  CString str;

  // Inizializzo i dati del dialogo
  dlg.m_pDoc = (CWinSigmaDoc*)GetDocument();
  dlg.m_strTitolo = "Modifica serie";
  dlg.m_nNumeroVerbale = m_pVerbaliSet->m_Codice;
  dlg.m_nCodiceSerie = m_ListSerie.GetItemData(n);
  dlg.m_bNuovaSerie = FALSE;
  // Disabilito la combo per la selezione del tipo di certificato
  dlg.m_bEnableNuovo = TRUE;
  dlg.m_bEnableTipo = FALSE;
  dlg.m_strPosizione = str = m_aryPosSerie.GetAt(n);
  if((i = str.Find('/')) != -1)
    dlg.m_nOldPos = atoi(str.Mid(0, i)) + 1;
  else
    dlg.m_nOldPos = atoi(str);
  // Listini
  dlg.m_nListinoParticolare = m_nListinoParticolare;
  dlg.m_nListinoGenerale    = m_nListinoGenerale;
  dlg.m_bListinoGenerale    = IsDaListinoParticolare((long)m_ListSerie.GetItemData(n));
  if(dlg.DoModal() == IDOK)
  {
    m_bSerieDataChanged = TRUE;
    AddProvini(NULL, dlg.m_nCodiceSerie);
    // Verifico che il numero di provini per certificato sia corretto
    if(!VerificaProviniPerCertificato(m_pVerbaliSet->m_Codice))
      AfxMessageBox("Verificare il numero di provini per certificato ed\neventualmente correggerlo manualmente.");

		// Ricarico la lista delle serie
		LoadSeries(m_pVerbaliSet->m_Codice);
  }
}

BOOL CVerbaliView::VerificaProviniPerCertificato(int nVerbale)
{
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  int nTipoCertificato = 0;
  int nProvini = 0;
  int nMaxProvini = 0;

  m_pGlobalSerieSet->m_strFilter.Format("Verbale = %d", nVerbale);
  m_pGlobalSerieSet->m_strSort = "TipoCertificato, Codice ASC";
  m_pGlobalSerieSet->Requery();
  CTipiCertificatoSet* pTipiCert = new CTipiCertificatoSet(&pApp->m_db);
  pTipiCert->m_strFilter = "Codice = 0";
  pTipiCert->Open();
  for(SET_START(m_pGlobalSerieSet); !m_pGlobalSerieSet->IsEOF(); m_pGlobalSerieSet->MoveNext())
  {
    if(nTipoCertificato != m_pGlobalSerieSet->m_TipoCertificato)
    {
      nTipoCertificato = m_pGlobalSerieSet->m_TipoCertificato;
      pTipiCert->m_strFilter.Format("Codice = %d", nTipoCertificato);
      pTipiCert->Requery();
      nMaxProvini = pTipiCert->m_ProvXcertificato;
      nProvini = 0;
    }
    if(m_pGlobalSerieSet->m_NuovoCertificato)
      nProvini = 0;
    nProvini += m_pGlobalSerieSet->m_NumeroProvini;
    if(nProvini > nMaxProvini)
      return FALSE;
  }
  pTipiCert->Close();
  delete pTipiCert;
  return TRUE;
}

// Verifica se i servizi dellla serie selezionata sono da listino particolare o generale
BOOL CVerbaliView::IsDaListinoParticolare(long codSerie)
{
  if(!m_nListinoParticolare)
    return FALSE;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  // Sincronizzo il recordset
  m_pGlobalSerieSet->m_strFilter.Format("Codice = %ld", codSerie);
  m_pGlobalSerieSet->Requery();
  CString str, strFilter;
  if(!m_pGlobalSerieSet->IsFieldNull(&m_pGlobalSerieSet->m_Servizio1))
  {
    str.Format("SERVIZI_LISTINO.Codice = %d", m_pGlobalSerieSet->m_Servizio1);
    strFilter += str;
  }
  if(!m_pGlobalSerieSet->IsFieldNull(&m_pGlobalSerieSet->m_Servizio2))
  {
    if(strFilter.IsEmpty())
      str.Format("SERVIZI_LISTINO.Codice = %d", m_pGlobalSerieSet->m_Servizio2);
    else
      str.Format(" OR SERVIZI_LISTINO.Codice = %d", m_pGlobalSerieSet->m_Servizio2);
    strFilter += str;
  }
  if(!m_pGlobalSerieSet->IsFieldNull(&m_pGlobalSerieSet->m_Servizio3))
  {
    if(strFilter.IsEmpty())
      str.Format("SERVIZI_LISTINO.Codice = %d", m_pGlobalSerieSet->m_Servizio3);
    else
      str.Format(" OR SERVIZI_LISTINO.Codice = %d", m_pGlobalSerieSet->m_Servizio3);
    strFilter += str;
  }
  if(!m_pGlobalSerieSet->IsFieldNull(&m_pGlobalSerieSet->m_Servizio4))
  {
    if(strFilter.IsEmpty())
      str.Format("SERVIZI_LISTINO.Codice = %d", m_pGlobalSerieSet->m_Servizio4);
    else
      str.Format(" OR SERVIZI_LISTINO.Codice = %d", m_pGlobalSerieSet->m_Servizio4);
    strFilter += str;
  }
  if(!m_pGlobalSerieSet->IsFieldNull(&m_pGlobalSerieSet->m_Servizio5))
  {
    if(strFilter.IsEmpty())
      str.Format("SERVIZI_LISTINO.Codice = %d", m_pGlobalSerieSet->m_Servizio5);
    else
      str.Format(" OR SERVIZI_LISTINO.Codice = %d", m_pGlobalSerieSet->m_Servizio5);
    strFilter += str;
  }
  if(!m_pGlobalSerieSet->IsFieldNull(&m_pGlobalSerieSet->m_Servizio6))
  {
    if(strFilter.IsEmpty())
      str.Format("SERVIZI_LISTINO.Codice = %d", m_pGlobalSerieSet->m_Servizio6);
    else
      str.Format(" OR SERVIZI_LISTINO.Codice = %d", m_pGlobalSerieSet->m_Servizio6);
    strFilter += str;
  }
  
  CCategorieServiziSet* pCatServSet = new CCategorieServiziSet(&pApp->m_db);
  pCatServSet->m_strFilter.Format("Listino = %d AND Categoria = CATEGORIE.Codice AND (%s)", m_nListinoParticolare, strFilter);
  pCatServSet->Open();
  BOOL bEof = pCatServSet->IsEOF();
  pCatServSet->Close();
  return bEof;
}

// Elimina una serie
void CVerbaliView::OnButtonElimina() 
{
  int n;
  POSITION pos;

	UpdateData();  
  pos = m_ListSerie.GetFirstSelectedItemPosition();
	if((n = m_ListSerie.GetNextSelectedItem(pos)) < 0)
  {
    AfxMessageBox("Selezionare un dato valido!");
	  return;
  }
  CString str;
	switch(AfxMessageBox("Eliminare la serie selezionata?", MB_YESNOCANCEL))
	{
		case IDYES:
      m_arySerieEliminate.Add((DWORD)m_ListSerie.GetItemData(n));
      // Ricarico la lista delle serie
      LoadSeries(m_pVerbaliSet->m_Codice);
      m_bSerieDataChanged = TRUE;
  		break;
		case IDNO:
      break;
  }
	UpdateData(FALSE);
}

// Carica la lista delle serie non visualizzando quelle eliminate
// (verranno cancellate definitivamente al salvataggio del verbale)
void CVerbaliView::LoadSeries(int nVerbale)
{
  CString str;
  int    i, n = 0, nIcona;
  double dPrezzo, dTotale;
  long    nCodiceSerie, nProviniInseriti;
  CString strPosizione, strCertificato, strTipo, strStruttura, strServizi, strCampioni, strPrezzo;
	m_nCodiceUltimaSerie = -1;
	int	nNumeroProviniTemp = 0;
	int servComprEm = 0;

  SetCursor(LoadCursor(NULL, IDC_WAIT));
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  // Serie - provini
  CSerieProviniSet* pSerieProviniSet = new CSerieProviniSet(&pApp->m_db);
  pSerieProviniSet->m_strFilter.Format("Verbale = %d AND Serie = SERIE.Codice ", m_pVerbaliSet->m_Codice);
  pSerieProviniSet->m_strSort = "SERIE.Ordinamento, SERIE.TipoCertificato, SERIE.Codice ASC";
  pSerieProviniSet->Open();
	// Serie singole per prelevare quelle anomale
	m_pGlobalSerieSet->m_strFilter.Format("Verbale = %d", m_pVerbaliSet->m_Codice);
  m_pGlobalSerieSet->m_strSort = "SERIE.Ordinamento, SERIE.TipoCertificato, SERIE.Codice ASC";
  m_pGlobalSerieSet->Requery();
  // Categorie - servizi
  CCategorieServiziSet* pCatServSet = new CCategorieServiziSet(&pApp->m_db);
  if(m_nListinoParticolare != 0)
    pCatServSet->m_strFilter.Format("(Listino = %d OR Listino = %d) AND Categoria = CATEGORIE.Codice AND Certificato <> 0", m_pVerbaliSet->m_ListinoGenerale, m_pVerbaliSet->m_ListinoParticolare);
  else
    pCatServSet->m_strFilter.Format("Listino = %d AND Categoria = CATEGORIE.Codice AND Certificato <> 0", m_pVerbaliSet->m_ListinoGenerale);
  pCatServSet->Open();
  // Certificati emessi
  CCertificatiSet* pCertificatiSet = new CCertificatiSet(&pApp->m_db);
  pCertificatiSet->m_strFilter.Format("Verbale = %d", m_pVerbaliSet->m_Codice);
  pCertificatiSet->Open();
  // Tipo di certificato
  CTipiCertificatoSet* pTCertificato = ((CWinSigmaDoc*)GetDocument())->m_pTipiCertificatoSet;
  // Inizializzo gli indici
  m_ListSerie.DeleteAllItems();
  m_strCosto.Empty();
  m_nNumSerie = 0;
  m_nCertificati = 0;
  m_nSeriePos = 1;
  m_nCertificati = 1;
  m_aryPosSerie.RemoveAll();
  BOOL bFirst = TRUE;
  dTotale = 0.;
  nCodiceSerie = 0;
  nProviniInseriti = 0;
  n = 0;
	CString strContaSerie;
	int nContaSerie = 0;

	
	// Risalgo al tipo di certificato relativo all'ultima serie inserita per memorizzare 
	// il numero di provini già inseriti per il certificato che la comprende
	int tempNumeroProvini = 0;
	long codSerie = 0;
	long certUltimaSerie = 0;
	if(!pSerieProviniSet->IsEOF())
  {
		for(SET_START(pSerieProviniSet); !pSerieProviniSet->IsEOF(); pSerieProviniSet->MoveNext())
    {
			if(codSerie < pSerieProviniSet->m_CodiceSerie)
			{
				codSerie = pSerieProviniSet->m_CodiceSerie;
				certUltimaSerie = pSerieProviniSet->m_TipoCertificato;
				if(!pSerieProviniSet->IsFieldNull(&pSerieProviniSet->m_DataProva) 
					&& pSerieProviniSet->m_DataProva!=0)
					m_DataProva = pSerieProviniSet->m_DataProva;
			}
    }
  }
			
	codSerie = 0;
	BOOL eliminata = FALSE;
	// ---------------------------------------------------------------------------------//

	int IDCert(0);
  // Carico la lista delle serie
  for(SET_START(pSerieProviniSet); ; pSerieProviniSet->MoveNext())
  {

		//Rilevo il numero di provini inseriti per l'ultimo tipo di certificato
		// valutando solamente le serie non eliminate ed associate al giusto tipo
		// di certificato 
		if(pSerieProviniSet->m_CodiceSerie != codSerie && pSerieProviniSet->m_TipoCertificato == certUltimaSerie)
		{
			for(i = 0; i < m_arySerieEliminate.GetSize(); i++)
      {
				// Se la serie è tra quelle eliminate non viene processata
				eliminata = FALSE;
        if(pSerieProviniSet->m_CodiceSerie == (long)m_arySerieEliminate.GetAt(i))
          eliminata = TRUE;
      }
			codSerie = pSerieProviniSet->m_CodiceSerie;
			if(!eliminata)
			{
				if(pSerieProviniSet->m_NuovoCertificato)
					tempNumeroProvini  = pSerieProviniSet->m_NumeroProvini;
				else
					tempNumeroProvini  += pSerieProviniSet->m_NumeroProvini;
			}
		}
		//------------------------------------------------------------------------------//
		
    if(pSerieProviniSet->IsEOF() || nCodiceSerie != pSerieProviniSet->m_CodiceSerie)
    {
      if(nCodiceSerie)
      {
				nContaSerie++;
				if(nContaSerie<10)
					strContaSerie.Format(" %d [%s]", nContaSerie,strPosizione);
				else
					strContaSerie.Format("%d[%s]", nContaSerie,strPosizione);

        n = m_ListSerie.GetItemCount();
        n = m_ListSerie.InsertItem(n, strContaSerie, nIcona);
        m_ListSerie.SetItemData(n, nCodiceSerie);
        m_ListSerie.SetItemText(n, 1, strCertificato);
        m_ListSerie.SetItemText(n, 2, strTipo);
        m_ListSerie.SetItemText(n, 3, strStruttura);
        m_ListSerie.SetItemText(n, 4, strServizi);
        m_ListSerie.SetItemText(n, 5, strCampioni);
        m_ListSerie.SetItemText(n, 6, strPrezzo);
      }
			// se ho finito esco
			if(pSerieProviniSet->IsEOF())
				break;

      dPrezzo = 0.;
      nProviniInseriti = 0;
      // Verifico che la serie che sto considerando adesso non sia stata eliminata
      for(i = 0; i < m_arySerieEliminate.GetSize(); i++)
      {
        if(pSerieProviniSet->m_CodiceSerie == (long)m_arySerieEliminate.GetAt(i))
          break;
      }
      // Se questa serie è nella lista di quelle eliminate vado avanti
      if(i != m_arySerieEliminate.GetSize())
			{
			  nCodiceSerie = 0;  
        continue;
			}
      // reinizializzo le stringhe
      strPosizione.Empty();
      strCertificato.Empty();
      strTipo.Empty();
      strServizi.Empty();
      strCampioni.Empty();
      strPrezzo.Empty();
      m_nNumSerie++;
      // Posizione
      if(pSerieProviniSet->m_NuovoCertificato)
      {
        m_nNumeroProvini = 0;
				nNumeroProviniTemp = 0;
        m_nSeriePos = 1;
        if(!bFirst)
          m_nCertificati++;
      }


      /*----Gestione Emendamento ----*/
      pCertificatiSet->m_strFilter.Format("Codice = %d",pSerieProviniSet->m_Certificato);
      pCertificatiSet->Requery();
      if (!pCertificatiSet->IsEOF() && (!pCertificatiSet->IsFieldNull(&pCertificatiSet->m_EmendaIl)) && (IDCert != pSerieProviniSet->m_Certificato))
      {
        m_nSeriePos = 1;
        IDCert = pSerieProviniSet->m_Certificato;
      }


      strPosizione.Format("%d/%d", m_nSeriePos, m_nCertificati);
      bFirst = FALSE;
      m_aryPosSerie.Add(strPosizione);
      strStruttura = pSerieProviniSet->m_StrutturaPrelievo;
      // Carico la lista dei servizi selezionati
      for(SET_START(pCatServSet); !pCatServSet->IsEOF(); pCatServSet->MoveNext())
      {
        if(
          (pCatServSet->m_Certificato != pSerieProviniSet->m_TipoCertificato)  &&
          (pCatServSet->m_Certificato2 != pSerieProviniSet->m_TipoCertificato) &&
          (pCatServSet->m_Certificato3 != pSerieProviniSet->m_TipoCertificato) &&
          (pCatServSet->m_Certificato4 != pSerieProviniSet->m_TipoCertificato) &&
					(pCatServSet->m_Certificato5 != pSerieProviniSet->m_TipoCertificato)
          )
          continue;
        if(pCatServSet->m_Codice == pSerieProviniSet->m_Servizio1)
        {
          strServizi += pCatServSet->m_ID;
          strServizi += ", ";
          if(!pCatServSet->IsFieldNull(&pCatServSet->m_Prezzo))
					{
						if(pCatServSet->m_PerSerie == PER_SERIE )
							dPrezzo += pCatServSet->m_Prezzo;
						else
							dPrezzo += (pCatServSet->m_Prezzo * pSerieProviniSet->m_NumeroProvini);
						if(pCatServSet->m_Emissione == INCLUDE_EMISSIONE)
							servComprEm++;
					}
          continue;
        }
        if(pCatServSet->m_Codice == pSerieProviniSet->m_Servizio2)
        {
          strServizi += pCatServSet->m_ID;
          strServizi += ", ";
          if(!pCatServSet->IsFieldNull(&pCatServSet->m_Prezzo))
          {
						if(pCatServSet->m_PerSerie == PER_SERIE )
							dPrezzo += pCatServSet->m_Prezzo;
						else
							dPrezzo += (pCatServSet->m_Prezzo * pSerieProviniSet->m_NumeroProvini);
						if(pCatServSet->m_Emissione == INCLUDE_EMISSIONE)
							servComprEm++;
					}
          continue;
        }
        if(pCatServSet->m_Codice == pSerieProviniSet->m_Servizio3)
        {
          strServizi += pCatServSet->m_ID;
          strServizi += ", ";
          if(!pCatServSet->IsFieldNull(&pCatServSet->m_Prezzo))
          {
						if(pCatServSet->m_PerSerie == PER_SERIE )
							dPrezzo += pCatServSet->m_Prezzo;
						else
							dPrezzo += (pCatServSet->m_Prezzo * pSerieProviniSet->m_NumeroProvini);
						if(pCatServSet->m_Emissione == INCLUDE_EMISSIONE)
							servComprEm++;
					}
          continue;
        }
        if(pCatServSet->m_Codice == pSerieProviniSet->m_Servizio4)
        {
          strServizi += pCatServSet->m_ID;
          strServizi += ", ";
          if(!pCatServSet->IsFieldNull(&pCatServSet->m_Prezzo))
          {
						if(pCatServSet->m_PerSerie == PER_SERIE )
							dPrezzo += pCatServSet->m_Prezzo;
						else
							dPrezzo += (pCatServSet->m_Prezzo * pSerieProviniSet->m_NumeroProvini);
						if(pCatServSet->m_Emissione == INCLUDE_EMISSIONE)
							servComprEm++;
					}
          continue;
        }
        if(pCatServSet->m_Codice == pSerieProviniSet->m_Servizio5)
        {
          strServizi += pCatServSet->m_ID;
          strServizi += ", ";
          if(!pCatServSet->IsFieldNull(&pCatServSet->m_Prezzo))
          {
						if(pCatServSet->m_PerSerie == PER_SERIE )
							dPrezzo += pCatServSet->m_Prezzo;
						else
							dPrezzo += (pCatServSet->m_Prezzo * pSerieProviniSet->m_NumeroProvini);
						if(pCatServSet->m_Emissione == INCLUDE_EMISSIONE)
							servComprEm++;
					}
          continue;
        }
        if(pCatServSet->m_Codice == pSerieProviniSet->m_Servizio6)
        {
          strServizi += pCatServSet->m_ID;
          strServizi += ", ";
          if(!pCatServSet->IsFieldNull(&pCatServSet->m_Prezzo))
          {
						if(pCatServSet->m_PerSerie == PER_SERIE )
							dPrezzo += pCatServSet->m_Prezzo;
						else
							dPrezzo += (pCatServSet->m_Prezzo * pSerieProviniSet->m_NumeroProvini);
						if(pCatServSet->m_Emissione == INCLUDE_EMISSIONE)
							servComprEm++;
					}
          continue;
        }
      }
      // Tipo di certificato
      for(SET_START(pTCertificato); !pTCertificato->IsEOF(); pTCertificato->MoveNext())
      {
        if(pTCertificato->m_Codice == pSerieProviniSet->m_TipoCertificato)
        {
          strTipo = pTCertificato->m_Nome;
          break;
        }
      }
      strServizi.TrimRight(", ");
      // Numero campioni
      strCampioni.Format("%d", pSerieProviniSet->m_NumeroProvini);
      nNumeroProviniTemp += pSerieProviniSet->m_NumeroProvini;
      // Stato del certificato
      if(pSerieProviniSet->m_Certificato != 0)
      {
			  if(m_nSeriePos == 1)
				{
					SINCRONIZE(pCertificatiSet, pSerieProviniSet->m_Certificato);
					strCertificato.Format("%4d del %s", pCertificatiSet->m_NumeroCertificato,
  																 pCertificatiSet->m_DataEmissione.Format("%d/%m/%Y"));
					if( !pCertificatiSet->IsFieldNull(&pCertificatiSet->m_EmendatoDa) )
  				{
						long codTemp = pCertificatiSet->m_EmendatoDa;
						for(SET_START(pCertificatiSet); !pCertificatiSet->IsEOF(); pCertificatiSet->MoveNext() )
							if(pCertificatiSet->m_Codice == codTemp)
								break;
						if(!pCertificatiSet->IsEOF())
						{
							str.Format("(%d)",pCertificatiSet->m_NumeroCertificato);
							strCertificato+=str;
						}
						nIcona = 4;
					}
					else if( !pCertificatiSet->IsFieldNull(&pCertificatiSet->m_EmendaIl) )
					{
						long codTemp = pCertificatiSet->m_EmendaIl;
						for(SET_START(pCertificatiSet); !pCertificatiSet->IsEOF(); pCertificatiSet->MoveNext() )
							if(pCertificatiSet->m_Codice == codTemp)
								break;	
						if(!pCertificatiSet->IsEOF())
						{
							str.Format("(%d)",pCertificatiSet->m_NumeroCertificato);
							strCertificato+=str;
						}
						nIcona = 5;
					}
					else
						nIcona = 3;
        }
				else
				  nIcona = -1;
      }
      else
        strCertificato = "-----";

      Valuta prezzo(dPrezzo);
      strPrezzo = prezzo.Format();
      dTotale += dPrezzo;

	    if( m_nCodiceUltimaSerie < pSerieProviniSet->m_CodiceSerie )
			{
				m_nCodiceUltimaSerie = pSerieProviniSet->m_CodiceSerie;
				m_nNumeroProvini = nNumeroProviniTemp;
			}
			
      m_nSeriePos++;
    }
    // conto i provini inseriti
    if(!pSerieProviniSet->IsFieldNull(&pSerieProviniSet->m_DataInserimento))
      nProviniInseriti++;
    // seleziono l'icona
    if(pSerieProviniSet->m_Certificato == 0)
		{
			if(!nProviniInseriti)
				nIcona = 0;
			else if(nProviniInseriti == pSerieProviniSet->m_NumeroProvini)
				nIcona = 2;
			else
				nIcona = 1;
    }
    nCodiceSerie = pSerieProviniSet->m_CodiceSerie;
  }

	// Aggiungo al totale il prezzo dei certificati
  if(!m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_ListinoParticolare) && m_pVerbaliSet->m_ListinoParticolare != 0)
    pCatServSet->m_strFilter.Format("(Listino = %d OR Listino = %d) AND Categoria = CATEGORIE.Codice AND Emissione = 1", m_pVerbaliSet->m_ListinoGenerale, m_pVerbaliSet->m_ListinoParticolare);
  else
    pCatServSet->m_strFilter.Format("Listino = %d AND Categoria = CATEGORIE.Codice AND Emissione = 1", m_pVerbaliSet->m_ListinoGenerale);
  pCatServSet->Requery();
	dTotale += (pCatServSet->m_Prezzo * (m_nCertificati - servComprEm));
		
	m_lfCostoTotale = dTotale;
	if(m_bUrgenza)
		dTotale = m_lfCostoTotale * 1.5;
	else
		dTotale = m_lfCostoTotale;
  m_ListSerie.EnsureVisible(n, FALSE);
  Valuta totale(dTotale);
  m_strCosto = totale.Format();
  
	// Assegno all'apposita variabile il numero di provini inseriti nel 
	// del certificato che comprende l'ultima serie inserita.
	m_nNumeroProvini = tempNumeroProvini;

	// Ricerca di serie anomale
	BOOL trovata;
	while( !m_pGlobalSerieSet->IsEOF() )
	{
		nIcona = 0;
		trovata = FALSE;
		for(SET_START(pSerieProviniSet); !pSerieProviniSet->IsEOF(); pSerieProviniSet->MoveNext() )
			if(m_pGlobalSerieSet->m_Codice == pSerieProviniSet->m_CodiceSerie)
			{
				trovata = TRUE;
				break;
			}
		if(!trovata)
			m_pGlobalSerieSet->Delete();
		m_pGlobalSerieSet->MoveNext();
	}
  if(m_bNuovoVerbale)
    m_ListSerie.EnsureVisible(m_ListSerie.GetItemCount() - 1, FALSE);
  else
    m_ListSerie.EnsureVisible(0, FALSE);
	pSerieProviniSet->Close();
  delete pSerieProviniSet;
  pCertificatiSet->Close();
  delete pCertificatiSet;
  pCatServSet->Close();
  delete pCatServSet;
}

// Aggiunge i record dei provini per una serie
BOOL CVerbaliView::AddProvini(CSerieSet* pSerieSet, int nCodice)
{
  int i , n, m;
  int Servizi[MAX_SERVIZI_PER_SERIE];
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

  CString str, strFilter;
  for(i = 0; i < MAX_SERVIZI_PER_SERIE; i++)
    Servizi[i] = -1;
  // Servizi selezionati

  if(pSerieSet == NULL)
  {
    m_pGlobalSerieSet->m_strFilter.Format("Codice = %d", nCodice);
    m_pGlobalSerieSet->Requery();
    pSerieSet = m_pGlobalSerieSet;
  }
  if(!m_pGlobalSerieSet->IsFieldNull(&m_pGlobalSerieSet->m_Servizio1))
  {
    Servizi[0] = pSerieSet->m_Servizio1;   
    str.Format("Codice = %d", Servizi[0]);
    strFilter = str + " OR ";
  }    
  if(!m_pGlobalSerieSet->IsFieldNull(&m_pGlobalSerieSet->m_Servizio2))
  {
    Servizi[1] = pSerieSet->m_Servizio2;
    str.Format("Codice = %d", Servizi[1]);
    strFilter += str + " OR ";
  }
  if(!m_pGlobalSerieSet->IsFieldNull(&m_pGlobalSerieSet->m_Servizio3))
  {
    Servizi[2] = m_pGlobalSerieSet->m_Servizio3;
    str.Format("Codice = %d", Servizi[2]);
    strFilter += str + " OR ";
  }
  if(!m_pGlobalSerieSet->IsFieldNull(&m_pGlobalSerieSet->m_Servizio4))
  {
    Servizi[3] = pSerieSet->m_Servizio4;
    str.Format("Codice = %d", Servizi[3]);
    strFilter += str + " OR ";
  }
  if(!m_pGlobalSerieSet->IsFieldNull(&m_pGlobalSerieSet->m_Servizio5))
  {
    Servizi[4] = pSerieSet->m_Servizio5;
    str.Format("Codice = %d", Servizi[4]);
    strFilter += str + " OR ";
  }
  if(!m_pGlobalSerieSet->IsFieldNull(&m_pGlobalSerieSet->m_Servizio6))
  {
    Servizi[5] = pSerieSet->m_Servizio6;
    str.Format("Codice = %d", Servizi[5]);
    strFilter += str + " OR ";
  }
  strFilter.TrimRight(" OR ");
  CProviniSet* pProviniSet = new CProviniSet(&pApp->m_db);
  pProviniSet->m_strFilter.Format("Serie = %d", m_pGlobalSerieSet->m_Codice);
  pProviniSet->Open();
  CServiziListinoSet* pServiziSet = new CServiziListinoSet(&pApp->m_db);
  pServiziSet->m_strFilter = strFilter;
  pServiziSet->Open();
  // Aggiungo i record dei provini
  for(i = 0; i < MAX_SERVIZI_PER_SERIE; i++)
  {
    if(Servizi[i] == -1)
      continue;
    for(SET_START(pServiziSet); !pServiziSet->IsEOF(); pServiziSet->MoveNext())
    {
      if(Servizi[i] == pServiziSet->m_Codice && pServiziSet->m_Prove != 0)
      {
        m = 0;
        // Verifico che non ci siano già i provini
        for(SET_START(pProviniSet); !pProviniSet->IsEOF(); pProviniSet->MoveNext())
        {
          if(pProviniSet->m_Serie == pSerieSet->m_Codice)// && !pProviniSet->m_Servizio.Compare(pServiziSet->m_ID))
            m++;
        }
        // Ho già inserito i provini che servono per questo servizio
        if(m == pSerieSet->m_NumeroProvini)
          continue;
        // Troppi provini!!! Ne elimino qualcuno
        if(m > pSerieSet->m_NumeroProvini)
        {
          pProviniSet->m_strFilter.Format("Serie = %d", pSerieSet->m_Codice);
          pProviniSet->Requery();
          for(SET_START(pProviniSet); !pProviniSet->IsEOF(); pProviniSet->MoveNext())
          {
            if(m > pSerieSet->m_NumeroProvini)
            {
              pProviniSet->Delete();
              m--;
            }
          }
        }
        // Mancano dei provini
        for(n = m; n < pSerieSet->m_NumeroProvini; n++)
        {
          pProviniSet->AddNew();
          pProviniSet->m_Serie = pSerieSet->m_Codice;
          pProviniSet->m_Servizio = pServiziSet->m_ID;
          pProviniSet->Update();
        }
        pProviniSet->Requery();
      }
    }
  }

  pServiziSet->Close();
  pProviniSet->Close();
  delete pServiziSet;
  delete pProviniSet;
  return TRUE;
}

// Cancella tutti i record dei provini per la serie selezionata
// Parametri: bVerify = se TRUE devo verificare che il provino 
// non sia in uso prima di cancellarlo
void CVerbaliView::DeleteProvini(long codiceSerie, BOOL bVerify)
{
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  
  CProviniSet* pProviniSet = new CProviniSet(&pApp->m_db);
  pProviniSet->m_strFilter.Format("Serie = %d", codiceSerie);
  pProviniSet->Open();
  for(SET_START(pProviniSet); !pProviniSet->IsEOF(); pProviniSet->MoveNext())
  {
    if(!bVerify)
      pProviniSet->Delete();
    else
    {
      // Se il provino è in uso non lo cancello
      if(!pProviniSet->IsFieldNull(&pProviniSet->m_DataInserimento))
        continue;
      else
        pProviniSet->Delete();
    }
  }
  pProviniSet->Close();
  delete pProviniSet;
}

void CVerbaliView::OnKillfocusEditCodAzCertificato() 
{
  CTrovaAziendaDlg dlg;
  UpdateData();

  if(m_strCodiceAzCertificato.IsEmpty())
	  m_strNomeAzCertificato.Empty();
	else
	{
		dlg.m_strID = m_strCodiceAzCertificato;
		if(dlg.Find() || dlg.DoModal() == IDOK)
		{
			m_nCodiceAzCertificato   = dlg.m_pSet->m_Codice;
			m_strCodiceAzCertificato = dlg.m_pSet->m_ID;
			m_strNomeAzCertificato   = dlg.m_pSet->m_RagioneSociale;
			m_strIndAzCertificati    = FormatIndirizzo(dlg.m_pSet);
		}
  }
  UpdateData(FALSE);
}

void CVerbaliView::OnKillfocusEditCodAzFattura() 
{
  CTrovaAziendaDlg dlg;
  UpdateData();

//	m_strNomeAzFattura.Empty();
  if(m_strCodiceAzFattura.IsEmpty())
	{
	  m_strNomeAzFattura.Empty();
		m_strPartitaIva.Empty();
	}
	else
	{
		dlg.m_strID = m_strCodiceAzFattura;
		if(dlg.Find() || dlg.DoModal() == IDOK)
		{
			m_nCodiceAzFattura   = dlg.m_pSet->m_Codice;
			m_strCodiceAzFattura = dlg.m_pSet->m_ID;
			m_strNomeAzFattura   = dlg.m_pSet->m_RagioneSociale;
			m_strIndAzFattura    = FormatIndirizzo(dlg.m_pSet);
			GetDatiFatturazione();
		}
  }
  UpdateData(FALSE);
}

void CVerbaliView::OnKillfocusEditCodAzImpresa() 
{
  CTrovaAziendaDlg dlg;
  UpdateData();

  if(m_strCodiceImpresa.IsEmpty())
	  m_strNomeImpresa.Empty();
	else
  {
		dlg.m_strID = m_strCodiceImpresa;
		if(dlg.Find() || dlg.DoModal() == IDOK)
		{
			m_nCodiceImpresa   = dlg.m_pSet->m_Codice;
			m_strCodiceImpresa = dlg.m_pSet->m_ID;
			m_strNomeImpresa   = dlg.m_pSet->m_RagioneSociale;
			m_strIndImpresa    = FormatIndirizzo(dlg.m_pSet);
		}
  }
  UpdateData(FALSE);
}

void CVerbaliView::OnKillfocusEditNomeAzCertificato() 
{
  CTrovaAziendaDlg dlg;


  UpdateData();
	if(m_strNomeAzCertificato.IsEmpty())
	  m_strCodiceAzCertificato.Empty();
	else
	{
		dlg.m_strNome = m_strNomeAzCertificato;
		if(dlg.Find() || dlg.DoModal() == IDOK)
		{
			m_nCodiceAzCertificato   = dlg.m_pSet->m_Codice;
			m_strCodiceAzCertificato = dlg.m_pSet->m_ID;
			m_strNomeAzCertificato   = dlg.m_pSet->m_RagioneSociale;
			m_strIndAzCertificati    = FormatIndirizzo(dlg.m_pSet);
		}
  }
  UpdateData(FALSE);
}

void CVerbaliView::OnKillfocusEditNomeAzFattura() 
{
  CTrovaAziendaDlg dlg;

  UpdateData();
	if(m_strNomeAzFattura.IsEmpty())
	{
	  m_strCodiceAzFattura.Empty();
		m_strPartitaIva.Empty();
  }
  else
	{
		dlg.m_strNome = m_strNomeAzFattura;
		if(dlg.Find() || dlg.DoModal() == IDOK)
		{
			m_nCodiceAzFattura   = dlg.m_pSet->m_Codice;
			m_strCodiceAzFattura = dlg.m_pSet->m_ID;
			m_strNomeAzFattura   = dlg.m_pSet->m_RagioneSociale;
			m_strIndAzFattura    = FormatIndirizzo(dlg.m_pSet);
			GetDatiFatturazione();
		}
  }
  UpdateData(FALSE);
}

void CVerbaliView::OnKillfocusEditNomeAzImpresa() 
{
  CTrovaAziendaDlg dlg;

  UpdateData();
	if(m_strNomeImpresa.IsEmpty())
	  m_strCodiceImpresa.Empty();
	else
	{
		dlg.m_strNome = m_strNomeImpresa;
		if(dlg.Find() || dlg.DoModal() == IDOK)
		{
			m_nCodiceImpresa   = dlg.m_pSet->m_Codice;
			m_strCodiceImpresa = dlg.m_pSet->m_ID;
			m_strNomeImpresa   = dlg.m_pSet->m_RagioneSociale;
			m_strIndImpresa    = FormatIndirizzo(dlg.m_pSet);
		}
  }
  UpdateData(FALSE);
}


/////////////////////////////////////////////////////////////////////////
//
// La funzione riceve l'indice della lista serie e preleva dal database
// i dati relativi ai provini corrispondenti alla stessa serie.
// Chiama in seguito la funzione asssociata al tipo di certificato 
// specifico.

void CVerbaliView::ModificaRisultati(int indexSerie)
{
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	long codSerie = (long)m_ListSerie.GetItemData(indexSerie);

	CString msg, utente;  // stringhe di appoggio per segnalare la presenza di un utente

	// Istanza del recordset dei provini relativo al codice serie rilevato
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	
  pApp->LockTable("PROVINI");
  CProviniSet* pProviniSet = new CProviniSet(&pApp->m_db);
  pProviniSet->m_strFilter.Format("Serie = %d", codSerie);
  pProviniSet->Open();
	
	///////// Operazioni necessarie per la gestione di accessi concorrenti //////////
	boolean inElaborazione = FALSE; // Variabili d'appoggio per la gestione della 
	int eseguiOperazione = TRUE;		// sincronizzazione degli accessi al database
	for(SET_START(pProviniSet); !pProviniSet->IsEOF(); pProviniSet->MoveNext())
	{
		if(!pProviniSet->IsFieldNull(&pProviniSet->m_InUso))
		{
				utente = pProviniSet->m_InUso; // Determino l'utente presente nel campo
				inElaborazione = TRUE;
				break;
		}
	}
	if(inElaborazione)	// Se la tabella risulta in uso richiedo conferma prima di proseguire
	{
		msg = "Attenzione\nI risultati dei test risultano attualmente in fase di elaborazione\n";
		msg += "da parte dell'utente: " +  utente + "\n\nProcedere comunque con l'operazione?";

		eseguiOperazione = AfxMessageBox(msg, MB_YESNO);// Visulizzazione del messaggio di avvertimento
	}	
	if(eseguiOperazione == IDNO)// Se l'utente decide di abbandonare l'operazione chiudo le operazioni
	{
		pApp->UnlockTables();				// Libero la tabella
		pProviniSet->Close();				// Chiudo il recordset
		delete pProviniSet;					// Cancello il puntatore
		return;
	}
	else 
	{
		// Notifico che la tabella dei provini è attualmente in uso dell'operatore corrente
			for(SET_START(pProviniSet); !pProviniSet->IsEOF(); pProviniSet->MoveNext())
			{
				if (pProviniSet->m_InUso != pApp->GetUserName())
				{
					pProviniSet->Edit();											  // Assegno il valore dell'operatore corrente per
					pProviniSet->m_InUso = pApp->GetUserName(); // indicare che attualmente egli sta operando  
					pProviniSet->Update();										  // sui dati della tabella
				}
			}
			pApp->UnlockTables();												// Libero la tabella 
			pProviniSet->Close();												// Chiudo il recordset
			
			// Chiamata alla funzione del modulo dll 
			//-----------------------------------------------------------------------------------//
			// La funzione richiede:
			// - Il recordset delle serie aperto e sincronizzato con la serie da elaborare
			// - Gli altri due recordset istanziati e chiusi
      m_pSerieSet->m_strFilter.Format("Codice = %ld", codSerie);
      m_pSerieSet->Requery();
//			SINCRONIZE(m_pSerieSet, codSerie);

			CString moduloDll = GetNameModuloDll(m_pSerieSet->m_TipoCertificato);
			
			CAllTables* pTabelle = new CAllTables(&pApp->m_db);
			
			// Definizione del tipo di puntatore alla funzione da chiamare
			typedef int (PROCESTERNA)(long, CAllTables*, long*, CTime*);	
	
			// Operazioni necessarie per la chiamata alla procedura del modulo esterno
			HINSTANCE hist, hexe;
			PROCESTERNA* pFunc;										// Creo una variabile function del tipo precedentemente definito
			int esito = 0;
			if (hist = ::LoadLibrary(moduloDll))	// Reperimento dell'istanza del modulo cercato
			{
				if(pFunc = (PROCESTERNA*)::GetProcAddress(hist,"OpenDlg"))// Reperimento della funzione esterna
				{
					hexe = AfxGetResourceHandle();	// Memorizzazione temporanea delle risorse attuali
					AfxSetResourceHandle(hist);			// Forzo l'uso delle risorse della dll
					
					// Chiamata alla funzione esterna 
					esito = (pFunc)(codSerie, pTabelle, &m_nCodSperiment, &m_DataProva);

					AfxSetResourceHandle(hexe);			// Ripristino dell'uso delle risorse
				}
			}	

			delete pTabelle;
			// Riscrittura dei dati nella lista delle serie
			if(esito == IDOK)
				RiscriviDatiSerie(indexSerie);
			
			// Ripristino della tabella provini consentendo l'elaborazione da parte di altri utenti
			LiberaTabellaProvini(codSerie);
      UpdateData(FALSE);
		}
}

////////////////////////////////////////////////////////////////////////////
// Funzione che ripristina a null il campo che autorizza la modifica degli 
// elementi della tabella provini

void CVerbaliView::LiberaTabellaProvini(int codSerie)
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	pApp->LockTable("PROVINI");
	CProviniSet* pProviniSet = new CProviniSet(&pApp->m_db);
	pProviniSet->m_strFilter.Format("Serie = %d", codSerie);
	pProviniSet->Open();
	
	for(SET_START(pProviniSet); !pProviniSet->IsEOF(); pProviniSet->MoveNext())
	{
		pProviniSet->Edit();				
		pProviniSet->SetFieldNull(&pProviniSet->m_InUso, TRUE);// Rimetto a NULL il valore del campo
		pProviniSet->Update();
	}
	pApp->UnlockTables();	
	pProviniSet->Close();
	delete pProviniSet;
}


void CVerbaliView::OnCheckOgniserie() 
{
	int nProv, nCert;

  UpdateData();
  m_pSerieSet->m_strFilter.Format("Verbale = %ld", m_pVerbaliSet->m_Codice);
	m_pSerieSet->m_strSort = "TipoCertificato, Codice ASC";
  m_pSerieSet->Requery();
	nProv = nCert = 0;
  
  CString materiale("");
  if (!m_pSerieSet->IsEOF())
      materiale = m_pSerieSet->m_Materiale;

  for(SET_START(m_pSerieSet); !m_pSerieSet->IsEOF(); m_pSerieSet->MoveNext())
  {
    if(m_pSerieSet->m_Verbale == m_pVerbaliSet->m_Codice)
    {
      m_pSerieSet->Edit();
      if(
        (nCert != m_pSerieSet->m_TipoCertificato)
				 || 
         ((nProv += m_pSerieSet->m_NumeroProvini) > 6)
         ||
         (materiale != m_pSerieSet->m_Materiale)
         )
			{
			  m_pSerieSet->m_NuovoCertificato = TRUE;
				nProv = m_pSerieSet->m_NumeroProvini;
  			nCert = m_pSerieSet->m_TipoCertificato;
			}
		  else
			  m_pSerieSet->m_NuovoCertificato = m_bCertificatoOgniSerie;

      materiale = m_pSerieSet->m_Materiale;

      m_pSerieSet->Update();
    }
  }
	LoadSeries(m_pVerbaliSet->m_Codice);
  UpdateData(FALSE);
}

void CVerbaliView::OnCheckUrgenza() 
{
  UpdateData();
	double lfCosto = m_lfCostoTotale;
	if(m_bUrgenza)
  {
		lfCosto = lfCosto*1.5;

    m_CtrlDataConsegna.EnableWindow(TRUE);
    m_EditOraConsegna.EnableWindow(TRUE);

    m_chkRitiro.SetCheck(BST_UNCHECKED);
    m_bRitiro = false;
  }
  else
  {
    m_CtrlDataConsegna.EnableWindow(FALSE);
    m_EditOraConsegna.EnableWindow(FALSE);
  }

	Valuta vCosto(lfCosto);
	m_strCosto = vCosto.Format();
  UpdateData(FALSE);
}


void CVerbaliView::OnCheckLettera() 
{
  UpdateData();
  m_strLetteraIncarico.Empty();
  m_EditLetteraIncarico.EnableWindow(m_bLetteraIncarico);
  UpdateData(FALSE);
}


void CVerbaliView::OnModifica() 
{
	
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

	// Verifica che sia selezionato un dato valido
#ifdef WINSIGMA2
  if(m_pVerbaliSet->IsBOF() || m_pVerbaliSet->IsEOF() || 
			 ( m_pVerbaliSet->m_TipoVerbale != VERB_NON_IN_CONCESSIONE
			&& m_pVerbaliSet->m_TipoVerbale != VERB_NC_PROVE_DI_CARICO
			&& m_pVerbaliSet->m_TipoVerbale != VERB_NC_CONGL_BITUMINOSI
			&& m_pVerbaliSet->m_TipoVerbale != VERB_NC_INERTI
			&& m_pVerbaliSet->m_TipoVerbale != VERB_NC_MONITORAGGI
			&& m_pVerbaliSet->m_TipoVerbale != VERB_NC_VARIE
			&& m_pVerbaliSet->m_TipoVerbale != VERB_NC_GEOTECNICA
			&& m_pVerbaliSet->m_TipoVerbale != VERB_NC_LINEE_VITA
			&& m_pVerbaliSet->m_TipoVerbale != VERB_NC_INDAGINI_MURATURE
			&& m_pVerbaliSet->m_TipoVerbale != VERB_NC_INDAGINI_CLS
			&& m_pVerbaliSet->m_TipoVerbale != VERB_NC_MAT_METALLICI)
			)	
#else
  if(m_pVerbaliSet->IsBOF() || m_pVerbaliSet->IsEOF())
#endif
  {
	  MessageBeep(-1);
		return;
  }

// verifica che non siamo in modalità di modifica provini
  if(pApp->GetViewMode() == MODE_EDIT_PROVINI)
	{
	  MessageBeep(-1);
		return;
	}

	///////////////////////////////////////////////////////////////////////////
	// Notifico che il verbale è in uso se passo dalla MODE_VIEW alla MODE_EDIT
	// Se l'operazione fallisce non proseguo.
	if( pApp->GetViewMode() == MODE_VIEW && !pApp->SetVerbaleInUso(m_pVerbaliSet->m_Codice) )
		return;
  
  if(pApp->GetViewMode() == MODE_VIEW)
  {
    if(m_pVerbaliSet->m_NumeroFattura == 0)
    {
      if(AfxMessageBox("Attenzione: il verbale selezionato è in fatturazione, eventuali modifiche ai servizi \ndovranno essere riportate manualmente in fatturazione.\nSi vuole proseguire?", MB_YESNO) == IDNO)
      {
        pApp->SetVerbaleInUso(m_pVerbaliSet->m_Codice, TRUE);
        return ;
      }
    }
    else  if(!m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_NumeroFattura) && m_pVerbaliSet->m_NumeroFattura != 0)
    {
      if(AfxMessageBox("Attenzione: il verbale selezionato è già stato fatturato, eventuali modifiche ai servizi \ndovranno essere riportate manualmente nella fattura.\nSi vuole proseguire?", MB_YESNO) == IDNO)
      {
        pApp->SetVerbaleInUso(m_pVerbaliSet->m_Codice, TRUE);
        return ;
      }
    }
  }
			
	m_bNuovoVerbale = FALSE;
	CXFormView::OnModifica();

  m_BtnEmenda.EnableWindow(FALSE);
}

int CVerbaliView::TrovaCodiceAzienda(int azSelezionata)
{
  
  if(m_strCodiceAzFattura.IsEmpty())
  {
    AfxMessageBox("Indicare il codice di un'azienda per la fatturazione");
    return AZ_NOTFOUND;
  }
  int res;
  CAziendeSet* pSet = new CAziendeSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
  pSet->Open();
  switch(azSelezionata)
  {
  case AZIENDA_FATTURA:
    for(SET_START(pSet); !pSet->IsEOF(); pSet->MoveNext())
    {
      if(pSet->m_ID == m_strCodiceAzFattura)
      {
        m_nCodiceAzFattura = pSet->m_Codice;
        m_strNomeAzFattura = pSet->m_RagioneSociale;
        if(pSet->m_UsaTuttiListini)
          res = AZ_LISTGEN;
        else
          res = AZ_NOLISTGEN;
        break;
      }
    }
    if(pSet->IsEOF())
    {
      AfxMessageBox("Impossibile trovare l'azienda per la fatturazione!");
      return AZ_NOTFOUND;
    }
    break;
  case AZIENDA_CERTIFICATO:
    for(SET_START(pSet); !pSet->IsEOF(); pSet->MoveNext())
    {
      if(pSet->m_ID == m_strCodiceAzCertificato)
      {
        m_nCodiceAzCertificato = pSet->m_Codice;
        break;
      }
    }
    if(pSet->IsEOF())
    {
      AfxMessageBox("Impossibile trovare l'azienda per la fatturazione!");
      return AZ_NOTFOUND;
    }
    break;
  case AZIENDA_IMPRESA:
    for(SET_START(pSet); !pSet->IsEOF(); pSet->MoveNext())
    {
      if(pSet->m_ID == m_strCodiceImpresa)
      {
        m_nCodiceImpresa = pSet->m_Codice;
        break;
      }
    }
    if(pSet->IsEOF())
    {
      AfxMessageBox("Impossibile trovare l'azienda per la fatturazione!");
      return AZ_NOTFOUND;
    }
    break;
  }
  pSet->Close();
  return res;
}

void CVerbaliView::OnChangeEditCodAzFattura() 
{
  UpdateData();
	if(m_strCodiceAzFattura.IsEmpty())
  {
    m_strNomeAzFattura.Empty();
    m_nCodiceAzFattura = -1;
  }
}


void CVerbaliView::OnChangeEditNomeAzFattura() 
{
  UpdateData();
	if(m_strNomeAzFattura.IsEmpty())
  {
    m_strCodiceAzFattura.Empty();
    m_nCodiceAzFattura = -1;
  }
}


void CVerbaliView::PrintMinuta()
{
  CPrintInterpreter prnInterpreter;
  CString strLayout, strNumCampioni, docname;
  int nCodiceCertificato;
  
  if(m_pVerbaliSet->IsBOF() || m_pVerbaliSet->IsEOF())
	{
	  MessageBeep(-1);
		return;
	}

	// imposta il nome del file secondo le specifiche della gestione documentale (s.c. 14.09.2017)
  docname.Format("minuta-%d-%d", m_pVerbaliSet->m_ProgressivoTotale, m_pVerbaliSet->m_DataAccettazione.GetYear());
	prnInterpreter.SetDocName(docname);

  CStringArray strNames, strValues;
  if(!prnInterpreter.PrePrinting())
    return;
  m_pSerieSet->m_strFilter.Format("Verbale = %d", m_pVerbaliSet->m_Codice);
  m_pSerieSet->Requery();

	// prima effettua una simulazione di stampa per determinare il numero delle pagine (s.c. 23.10.2019)
	// non è molto elegante fatto così --> da rivedere
  nCodiceCertificato = -1;
  // Numero totale dei campioni
  int n = 0;
  for(SET_START(m_pSerieSet); !m_pSerieSet->IsEOF(); m_pSerieSet->MoveNext())
    n += m_pSerieSet->m_NumeroProvini;
  strNumCampioni.Format("%d", n);
  m_nPosCertificato = 0;
	BOOL inclusione;
  for(SET_START(m_pSerieSet); !m_pSerieSet->IsEOF();)
	{
    SINCRONIZE(m_pTipiCertificatoSet, m_pSerieSet->m_TipoCertificato);
		
		// Verifico se il tipo di certificato è incluso fra quelli selezionati
		inclusione = FALSE;
		for(int n=0; n < m_paryTCerMinute.GetSize(); n++)
			if( m_pTipiCertificatoSet->m_Codice == (long)m_paryTCerMinute.GetAt(n))
				inclusione = TRUE;
			
		// Se non è incluso passo alle serie successive senza fare altro che incrementare 
		// l'intero che rappresenta la posizione del certificato
    if(m_pTipiCertificatoSet->m_LayoutStampaMinuta.IsEmpty() || !inclusione)
		{
			if(m_pSerieSet->m_NuovoCertificato)
			  m_nPosCertificato++;
      m_pSerieSet->MoveNext();
      continue;
		}
		
    if(m_pTipiCertificatoSet->m_Codice != nCodiceCertificato)
		{
			m_nSerieInStampa = 0;
      nCodiceCertificato = m_pTipiCertificatoSet->m_Codice;
      SetFieldsMinuta(&strNames, &strValues);
      strNames.Add("numeroCampioni");
      strValues.Add(strNumCampioni);
      strLayout.Format(".\\%s", m_pTipiCertificatoSet->m_LayoutStampaMinuta);

			m_nTotalePagine = 0;
			prnInterpreter.SetPage(1);
			prnInterpreter.StartSimulation();
			prnInterpreter.Print(strLayout, &strNames, &strValues, NULL, NULL, ScanProviniMinuta);
			m_nTotalePagine = prnInterpreter.GetPage() - 1;
			prnInterpreter.EndSimulation();
		}
	}

	// esecuzione della stampa effettiva (s.c. 23.10.2019)
  nCodiceCertificato = -1;
  m_nPosCertificato = 0;

  for(SET_START(m_pSerieSet); !m_pSerieSet->IsEOF();)
	{
    SINCRONIZE(m_pTipiCertificatoSet, m_pSerieSet->m_TipoCertificato);
		
		// Verifico se il tipo di certificato è incluso fra quelli selezionati
		inclusione = FALSE;
		for(int n=0; n < m_paryTCerMinute.GetSize(); n++)
			if( m_pTipiCertificatoSet->m_Codice == (long)m_paryTCerMinute.GetAt(n))
				inclusione = TRUE;
			
		// Se non è incluso passo alle serie successive senza fare altro che incrementare 
		// l'intero che rappresenta la posizione del certificato
    if(m_pTipiCertificatoSet->m_LayoutStampaMinuta.IsEmpty() || !inclusione)
		{
			if(m_pSerieSet->m_NuovoCertificato)
			  m_nPosCertificato++;
      m_pSerieSet->MoveNext();
      continue;
		}
		
    if(m_pTipiCertificatoSet->m_Codice != nCodiceCertificato)
		{
			m_nSerieInStampa = 0;
      nCodiceCertificato = m_pTipiCertificatoSet->m_Codice;
      SetFieldsMinuta(&strNames, &strValues);
      strNames.Add("numeroCampioni");
      strValues.Add(strNumCampioni);
      strLayout.Format(".\\%s", m_pTipiCertificatoSet->m_LayoutStampaMinuta);
			prnInterpreter.SetPage(1);
			prnInterpreter.SetTotPages(m_nTotalePagine);
      prnInterpreter.Print(strLayout, &strNames, &strValues, NULL, NULL, ScanProviniMinuta);
		}
	}
  prnInterpreter.PostPrinting();
  m_nPosCertificato = 0;
  m_pSerieSet->m_strFilter.Empty();
  m_pSerieSet->Requery();
}


// Riempie le stringhe per i campi della minuta
void CVerbaliView::SetFieldsMinuta(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
  CString str;

  pFieldNames->RemoveAll();
  pFieldValues->RemoveAll();
  // Data della minuta
  pFieldNames->Add("dataMinuta");
  pFieldValues->Add((CTime::GetCurrentTime()).Format("%d/%m/%Y"));
  // Totale verbali
  pFieldNames->Add("totaleVerbali");
  str.Format("%d", m_pVerbaliSet->m_ProgressivoTotale);
  pFieldValues->Add(str);
  // Data accettazione del verbale
  pFieldNames->Add("dataAccettazione");
  pFieldValues->Add(m_pVerbaliSet->m_DataAccettazione.Format("%d/%m/%Y"));
  // Data di consegna
  if(m_pVerbaliSet->m_Urgenza)
  {
    if (m_pVerbaliSet->m_Urgenza != 2)
    {
      pFieldNames->Add("urgenza");
		  if(m_pVerbaliSet->m_Spedizione)
        str.Format("URGENTE: %s - %s", m_pVerbaliSet->m_DataConsegna.Format("%d/%m/%Y"), m_pVerbaliSet->m_OraConsegna);
      else
        str.Format("URGENTE: %s - %s", m_pVerbaliSet->m_DataConsegna.Format("%d/%m/%Y"), m_pVerbaliSet->m_OraConsegna);
		  pFieldValues->Add(str);
    }
    else
    {
      pFieldNames->Add("urgenza");
      str.Format("%s", m_pVerbaliSet->m_DataConsegna.Format("%d/%m/%Y"));
		  pFieldValues->Add(str);
    }
  }
  // Progressivo del verbale
  pFieldNames->Add("progressivoVerbale");
  str.Format("%d/%d", m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale);
  pFieldValues->Add(str);
  // Spianatura
  //pFieldNames->Add("spianpieg");
  //pFieldValues->Add("");
  // Materiale consegnato
  pFieldNames->Add("materialeConsegnato");
  pFieldValues->Add(m_pVerbaliSet->m_DescrizioneMateriale);
  // Prove richieste
  pFieldNames->Add("proveRichieste");  
  pFieldValues->Add(m_pVerbaliSet->m_ProveRichieste);
	
	//--- Gestione del titolo e della spianatura in relazione alle prove richieste ---//

	// Per ogni servizio associato alla prima serie di ogni tipo di certificazione:
	// esamino i servizi richiesti per valutare sia la composizione del titolo che
	// l'eventuale inserimento della stringa relativa alla spianatura
	//
	// Funzionamento
	// Per ogni servizio not null:
	// verificato se corrisponde al servizio aggiuntivo;
	// compongo il filtro per eseguire la query mirata ai soli servizi selezionati
	// in maniera da poter valutare quali tipi di prove sono implicate dai 
	// servizi richiesti
	
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CServiziListinoSet pServSet(&pApp->m_db);
	CString query, strProve, strSpianatura ="";
	
	if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Servizio1))
  {
		if(m_pSerieSet->m_Servizio1 == m_pSerieSet->m_ServAggiungibile)
			strSpianatura = STR_SPIANATURA;
		if(query.GetLength()==0)
			query.Format("Codice = %d", m_pSerieSet->m_Servizio1);
		else
		{
			str.Format(" OR Codice = %d", m_pSerieSet->m_Servizio1);
			query += str;
		}
	}
	if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Servizio2))
	{
		if(m_pSerieSet->m_Servizio2 == m_pSerieSet->m_ServAggiungibile)
			strSpianatura = STR_SPIANATURA;
		if(query.GetLength()==0)
			query.Format("Codice = %d", m_pSerieSet->m_Servizio2);
		else
		{
			str.Format(" OR Codice = %d", m_pSerieSet->m_Servizio2);
			query += str;
		}
	}
	if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Servizio3))
	{
		if(m_pSerieSet->m_Servizio3 == m_pSerieSet->m_ServAggiungibile)
			strSpianatura = STR_SPIANATURA;
		if(query.GetLength()==0)
			query.Format("Codice = %d", m_pSerieSet->m_Servizio3);
		else
		{
			str.Format(" OR Codice = %d", m_pSerieSet->m_Servizio3);
			query += str;
		}
	}
	if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Servizio4))
  {
		if(m_pSerieSet->m_Servizio4 == m_pSerieSet->m_ServAggiungibile)
			strSpianatura = STR_SPIANATURA;
		if(query.GetLength()==0)
			query.Format("Codice = %d", m_pSerieSet->m_Servizio4);
		else
		{
			str.Format(" OR Codice = %d", m_pSerieSet->m_Servizio4);
			query += str;
		}
	}
	if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Servizio5))
	{
		if(m_pSerieSet->m_Servizio5 == m_pSerieSet->m_ServAggiungibile)
			strSpianatura = STR_SPIANATURA;
		if(query.GetLength()==0)
			query.Format("Codice = %d", m_pSerieSet->m_Servizio5);
		else
		{
			str.Format(" OR Codice = %d", m_pSerieSet->m_Servizio5);
			query += str;
		}
	}
	if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Servizio6))
	{
		if(m_pSerieSet->m_Servizio6 == m_pSerieSet->m_ServAggiungibile)
			strSpianatura = STR_SPIANATURA;		
		if(query.GetLength()==0)
			query.Format("Codice = %d", m_pSerieSet->m_Servizio6);
		else
		{
			str.Format(" OR Codice = %d", m_pSerieSet->m_Servizio6);
			query += str;
		}
	}
	if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_ServAggiunto))
	{
		if(m_pSerieSet->m_ServAggiunto == m_pSerieSet->m_ServAggiungibile)
			strSpianatura = STR_SPIANATURA;
		if(query.GetLength()==0)
			query.Format("Codice = %d", m_pSerieSet->m_ServAggiunto);
		else
		{
			str.Format(" OR Codice = %d", m_pSerieSet->m_ServAggiunto);
			query += str;
		}
	}

	pServSet.m_strFilter = query;
	pServSet.Open();
	int prove = 0;
	while(!pServSet.IsEOF())
	{
		if(prove != pServSet.m_Prove)
			prove += pServSet.m_Prove;
		pServSet.MoveNext();
	}
	//SINCRONIZE();
	switch(prove)
	{
  	case(1): strProve = m_pTipiCertificatoSet->m_ProvaA;
			break;
		case(2): strProve = m_pTipiCertificatoSet->m_ProvaB;
			break;
		case(3): strProve = m_pTipiCertificatoSet->m_ProvaA + " - " + m_pTipiCertificatoSet->m_ProvaB;
			break;
	}
	pServSet.Close();
	
	// Titolo minuta
	pFieldNames->Add("titolo");  
	strProve.MakeUpper();
	str = "Risultati di PROVA " + strProve;
  pFieldValues->Add(str);

	// Spianatura
  pFieldNames->Add("spianpieg");
  pFieldValues->Add(strSpianatura);
	
	//----------------------------------------------------------//

}


BOOL CVerbaliView::ScanProviniMinuta(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
  static int nCodiceSerie, nTipoCertificato, nProvini, numProvino;
  CString str, strTemp;
	int i = 0, l = 0;
  
  if(m_pSerieSet->IsEOF())
  {
	  m_nPosCertificato = 0;
    return FALSE;
  }
  pFieldNames->RemoveAll();
  pFieldValues->RemoveAll();

	// Stampa di una riga vuota per separare ogni serie e una riga per separare i certificati
	if(m_nSerieInStampa != m_pSerieSet->m_Codice)
	{
		m_nSerieInStampa = m_pSerieSet->m_Codice;
		pFieldNames->Add("separatore");
		str = "";
		if(m_pSerieSet->m_NuovoCertificato)
			for(int x=0; x<20; x++)
				str += "¯ ¯ ¯ ¯ ¯ ¯ ¯ ¯ ¯ ¯ ¯ ";
		pFieldValues->Add(str);
		return TRUE;
	}
		
  if(nCodiceSerie != m_pSerieSet->m_Codice)
  {
    nProvini = 0;
    if(!numProvino)
      numProvino = 1;

    pFieldNames->Add("materiale");
    pFieldValues->Add(m_pSerieSet->m_IDMateriale);

//    pFieldNames->Add("sigla");
//    pFieldValues->Add(m_pSerieSet->m_Sigla);
    if(!m_pSerieSet->m_StrutturaPrelievo.IsEmpty())
    {
      pFieldNames->Add("posizione");
      pFieldValues->Add(m_pSerieSet->m_StrutturaPrelievo);
    }
		if(m_pSerieSet->m_NuovoCertificato)
		  m_nPosCertificato++;
  }

  if(nCodiceSerie != m_pSerieSet->m_Codice)
  {
    pFieldNames->Add("sigla");
    pFieldValues->Add(m_pSerieSet->m_Sigla);
	}
	else
	{
    pFieldNames->Add("sigla");
    pFieldValues->Add(m_pSerieSet->m_Sigla2);
	}

  // Dati minuta cubetti
  pFieldNames->Add("verbale_prelievo");
  pFieldNames->Add("prelievo");
  pFieldNames->Add("scad45gg");
  pFieldNames->Add("matur_prova");
	pFieldValues->Add(m_pSerieSet->m_VerbalePrelievo);  // verbale prelievo
	if(m_pSerieSet->IsFieldNull(&m_pSerieSet->m_DataPrelievo) || m_pSerieSet->m_DataPrelievo == 0)
	{
		pFieldValues->Add(m_pSerieSet->m_strDataND);  // data prelievo
    pFieldValues->Add("../../..");								// scadenza 45 gg 
    pFieldValues->Add("../../..");								// maturazione 
	}
	else
	{
    TIME_ZONE_INFORMATION timeZone;
//		CTimeSpan ts1 = CTimeSpan(1, 1, 0, 0);    // elemento per correzione passaggio ora solare s.c. 9.11.2018
    CTimeSpan  tsMat28(m_pTipiCertificatoSet->m_Maturazione, 0, 0, 0);			// 28 gg
    CTimeSpan  tsMat29(m_pTipiCertificatoSet->m_Maturazione+1, 0, 0, 0);		// 29 gg
    CTimeSpan  tsMat30(m_pTipiCertificatoSet->m_Maturazione+2, 0, 0, 0);		// 30 gg
    CTimeSpan  tsScad(DATA_SCADENZA_CUBETTI, 0, 0, 0);
    GetTimeZoneInformation(&timeZone);
		tsMat28 -= timeZone.Bias * 60; 
		tsMat29 -= timeZone.Bias * 60; 
		tsMat30 -= timeZone.Bias * 60; 
		tsScad -= timeZone.Bias * 60;
		CTime ctMat28 = m_pSerieSet->m_DataPrelievo + tsMat28;
		CTime ctMat29 = m_pSerieSet->m_DataPrelievo + tsMat29;
		CTime ctMat30 = m_pSerieSet->m_DataPrelievo + tsMat30;
		CTime scad45 = m_pSerieSet->m_DataPrelievo + tsScad;
#if 0 // più pratico usare la correzione con la timezone s.c. 16.11.2018
		CTime ctMat28n = CTime(ctMat28.GetYear(), ctMat28.GetMonth(), ctMat28.GetDay(), 0, 0, 0);
		CTime ctMat29n = CTime(ctMat29.GetYear(), ctMat29.GetMonth(), ctMat29.GetDay(), 0, 0, 0);
		CTime ctMat30n = CTime(ctMat30.GetYear(), ctMat30.GetMonth(), ctMat30.GetDay(), 0, 0, 0);
		if(ctMat28n - m_pSerieSet->m_DataPrelievo < tsMat28)
		{
			// correzione ora solare
			ctMat28n += ts1;
			ctMat28 = CTime(ctMat28n.GetYear(), ctMat28n.GetMonth(), ctMat28n.GetDay(), 0, 0, 0);
		}
		if(ctMat29n - m_pSerieSet->m_DataPrelievo < tsMat29)
		{
			// correzione ora solare
			ctMat29n += ts1;
			ctMat29 = CTime(ctMat29n.GetYear(), ctMat29n.GetMonth(), ctMat29n.GetDay(), 0, 0, 0);
		}
		if(ctMat30n - m_pSerieSet->m_DataPrelievo < tsMat30)
		{
			// correzione ora solare
			ctMat30n += ts1;
			ctMat30 = CTime(ctMat30n.GetYear(), ctMat30n.GetMonth(), ctMat30n.GetDay(), 0, 0, 0);
		}
#endif
		CTime realnow = CTime::GetCurrentTime();
		// normalizza la data corrente alle ore 00:00:00
		CTime now(realnow.GetYear(), realnow.GetMonth(), realnow.GetDay(), 0, 0, 0);
		CTime accett(m_pVerbaliSet->m_DataAccettazione.GetYear(), m_pVerbaliSet->m_DataAccettazione.GetMonth(), m_pVerbaliSet->m_DataAccettazione.GetDay(), 0, 0, 0);
		CString csNow = now.Format("%d/%m/%y");
		CString cs45 = scad45.Format("%d/%m/%y");
		pFieldValues->Add(m_pSerieSet->m_DataPrelievo.Format("%d/%m/%y"));							// data prelievo
		if(scad45 >= accett)
		{
			pFieldValues->Add((m_pSerieSet->m_DataPrelievo + tsScad).Format("%d/%m/%y"));		// scadenza 45 gg
		}
		else
		{
	    pFieldValues->Add("");								// scadenza 45 gg 
		}

		CString csDataAccett = accett.Format("%d/%m/%y");
		CString csDataPrel = m_pSerieSet->m_DataPrelievo.Format("%d/%m/%y");
		CString csData28 = (ctMat28).Format("%d/%m/%y");
		CString csData29 = (ctMat29).Format("%d/%m/%y");
		CString csData30 = (ctMat30).Format("%d/%m/%y");

//		if(accett == ctMat28 || accett == ctMat29 || accett == ctMat30)
		if(csDataAccett.CompareNoCase(csData28) == 0 || 
				csDataAccett.CompareNoCase(csData29) == 0 || 
				csDataAccett.CompareNoCase(csData30) == 0)
		{
			pFieldValues->Add(csDataAccett);
		}
		else if(accett < ctMat28)
		{
		  pFieldValues->Add(ctMat28.Format("%d/%m/%y"));
		}
		else  // accett > m_pSerieSet->m_DataPrelievo + tsMat30
		{
		  pFieldValues->Add("../../..");
		}
  }
//	pFieldNames->Add("UB");
//  pFieldValues->Add("...");
  pFieldNames->Add("nProvino");
  str.Format("%d", numProvino);
  pFieldValues->Add(str);
  pFieldNames->Add("dim1");
  pFieldValues->Add("......");
  pFieldNames->Add("dim2");
  pFieldValues->Add("......");
  pFieldNames->Add("dim3");
  pFieldValues->Add("......");
  pFieldNames->Add("area");
  pFieldValues->Add(".......");
  pFieldNames->Add("massa");
  pFieldValues->Add(".......");
  pFieldNames->Add("carico");
  pFieldValues->Add(".......");
  pFieldNames->Add("resistenza");
  pFieldValues->Add(".......");
  pFieldNames->Add("posCertificato");
	str.Format("%d", m_nPosCertificato);
  pFieldValues->Add(str);
  // Spianatura: se è richiesta, metto la A
  pFieldNames->Add("tr_s");
  if(m_pSerieSet->m_Servizio1 == m_pSerieSet->m_ServAggiungibile
		 || m_pSerieSet->m_Servizio2 == m_pSerieSet->m_ServAggiungibile
		 || m_pSerieSet->m_Servizio3 == m_pSerieSet->m_ServAggiungibile
		 || m_pSerieSet->m_Servizio4 == m_pSerieSet->m_ServAggiungibile
		 || m_pSerieSet->m_Servizio5 == m_pSerieSet->m_ServAggiungibile
		 || m_pSerieSet->m_Servizio6 == m_pSerieSet->m_ServAggiungibile)
     pFieldValues->Add("... A");
  else
    pFieldValues->Add("... ..");
  pFieldNames->Add("op"); 
  pFieldValues->Add("|_|");
  pFieldNames->Add("cassone");
  pFieldValues->Add("....");
  
  // Dati minuta ferri
  pFieldNames->Add("diametro");
  str.Format("%.1f",m_pSerieSet->m_Dimensione1);
  pFieldValues->Add(str);
  pFieldNames->Add("peso");
  pFieldValues->Add("......");
  pFieldNames->Add("lunghezza");
  pFieldValues->Add("......");
  pFieldNames->Add("carSne");
  pFieldValues->Add("........");
  pFieldNames->Add("carRot");
  pFieldValues->Add("........");
  pFieldNames->Add("tensSne");
  pFieldValues->Add("........");
  pFieldNames->Add("tensRot");
  pFieldValues->Add("........");
  pFieldNames->Add("allungamento");
  pFieldValues->Add("........");

  pFieldNames->Add("piegEsito");
  pFieldValues->Add("......");
  pFieldNames->Add("piegMandr");
  pFieldValues->Add("......");
  pFieldNames->Add("ripianoTrazione");
  pFieldValues->Add("......");
  pFieldNames->Add("pancalePiegamento");
  pFieldValues->Add("......");
  pFieldNames->Add("numProvino");
  pFieldValues->Add("1");
	
  // Dati minuta laminati
  pFieldNames->Add("tipo");
  pFieldValues->Add("");
  pFieldNames->Add("larghezza");
  pFieldValues->Add("......");

	// Dati minuta resilienza
	pFieldNames->Add("indiceResilienza");
	str.Format("%d", numProvino);
	pFieldValues->Add(str);
	pFieldNames->Add("siglaResilienza");
	pFieldValues->Add(".................");
	pFieldNames->Add("temperaturaResilienza");
	pFieldValues->Add(".........");
	pFieldNames->Add("provettaResilienza");
	pFieldValues->Add("...................");
	pFieldNames->Add("sezioneResilienza");
	pFieldValues->Add("........ X ........");
	pFieldNames->Add("indebolitaResilienza");
	pFieldValues->Add("........ X ........");
	pFieldNames->Add("resilienzaResilienza");
	pFieldValues->Add("................");
	pFieldNames->Add("noteResilienza");
	pFieldValues->Add("......");

	// Dati minuta reti
	pFieldNames->Add("indiceReti");
	str.Format("%d", numProvino);
	pFieldValues->Add(str);
	pFieldNames->Add("fiReti");
	str.Format("%.1lf", m_pSerieSet->m_Dimensione1);
	pFieldValues->Add(str);
	pFieldNames->Add("pesoReti");
	pFieldValues->Add("........");
	pFieldNames->Add("lunghezzaReti");
	pFieldValues->Add("........");
	pFieldNames->Add("sezioneReti");
	pFieldValues->Add("........");
	pFieldNames->Add("snervamentoReti");
	pFieldValues->Add("........");
	pFieldNames->Add("rotturaReti");
	pFieldValues->Add("........");
	pFieldNames->Add("tensSnerAReti");
	pFieldValues->Add("........");
	pFieldNames->Add("tensSnerBReti");
	pFieldValues->Add("........");
	pFieldNames->Add("tensRottAReti");
	pFieldValues->Add("........");
	pFieldNames->Add("tensRottBReti");
	pFieldValues->Add("........");
	pFieldNames->Add("allungAReti");
	pFieldValues->Add("....");
	pFieldNames->Add("allungBReti");
	pFieldValues->Add("....");
	pFieldNames->Add("agReti");							// Minuta Reti 2011
	pFieldValues->Add("....");
	pFieldNames->Add("agtReti");						// Minuta Reti 2011
	pFieldValues->Add("....");
	pFieldNames->Add("ratioRotSnervReti");	// Minuta Reti 2011
	pFieldValues->Add("....");
	pFieldNames->Add("distaccoReti");
	pFieldValues->Add("........");
	pFieldNames->Add("noteReti");
	pFieldValues->Add("....");
	
  numProvino++;
  nTipoCertificato	= m_pSerieSet->m_TipoCertificato;
  nCodiceSerie			= m_pSerieSet->m_Codice;

  if(++nProvini == m_pSerieSet->m_NumeroProvini)
    m_pSerieSet->MoveNext();
  if(m_pSerieSet->IsEOF() || nTipoCertificato != m_pSerieSet->m_TipoCertificato)
  {
		if(m_pSerieSet->IsEOF())
		  m_nPosCertificato = 0;
    nCodiceSerie = 0;
    numProvino = 0;
    return FALSE;
  }
  return TRUE;
}



/////////////////////////////////////////////////////////
// Sceglie tutte le serie che soddisfano i seguenti requisiti:
//    1) Check nuovo certificato;
//    2) Campo certificato NULL
//    3) Tutti i dati dei provini delle serie associate allo
//		stesso certificato risultano inseriti.
// Sucessivamente richiama il dialogo relativo all'emissione che riempie un secondo 
// array con i codici delle serie associate ai certificati selezionati
// Se viene confermata l'emissione vengono creati i nuovi record nella tabella certificati 
// e vengono riempiti i relativi campi della tabella delle serie coinvolte

void CVerbaliView::OnButtonEmissioneCertificati() 
{
	CString msg,strDatiOccupante;
	
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	if( MODE_VIEW != pApp->GetViewMode())
		return;
	long lCodVerbale = m_pVerbaliSet->m_Codice;
	//-- Array temporanei per lo scambio informazioni con il dialogo --//
	CDWordArray	paryProposti,paryScelti;
	CStringArray paryInfoCert;
	CCertificatiSet*	pCertificatiSet	= new CCertificatiSet(&pApp->m_db);

	// Blocco della certificazione
	if(!pApp->DisabilitaCertificazione(&strDatiOccupante))
	{
		delete pCertificatiSet;
		msg = STR_BLOCCO_CERTIFICAZIONE(strDatiOccupante);
		msg = msg + STR_ISTRUZIONI_RIMOZIONE;
		AfxMessageBox(msg);
		return;
	}

	//-- Creazione dei recordset necessari per le operazioni di emissione --//
	CVerbSerProSet*		pVSPSet					= new CVerbSerProSet(&pApp->m_db);						
	
  if(m_pVerbaliSet->IsBOF() || m_pVerbaliSet->IsEOF() || pApp->GetViewMode() != MODE_VIEW)
	{
	  MessageBeep(-1);
		return;
	}
	//----------------- Inizio del reperimento info certificati -----------------//

	//--variabili d'appoggio --//
	CString infoCert, numVerb;
	CUIntArray paryTipoCert, parySceltiAderenza;
	int numSerie = 0, numProvini = 0, posizioneCertificato = 0;
	boolean datiInseriti = TRUE;
	long tempSerie, codSerieInEsame = 0;
	long codVerbaleInEsame = 0;

	//-- Prelevo tutte le serie che risultano non ancora emesse --//
	m_pGlobalSerieSet->m_strSort = "Verbale,TipoCertificato, Codice ASC";
	m_pGlobalSerieSet->m_strFilter.Format("Certificato = 0");
	m_pGlobalSerieSet->Requery();
	CString queryJoin = "VERBALI.Codice=SERIE.Verbale AND SERIE.Codice=PROVINI.Serie ";
	pVSPSet->m_strSort = "VERBALI.Codice, SERIE.Ordinamento, SERIE.TipoCertificato, SERIE.Codice ASC";
	pVSPSet->m_strFilter.Format("%s AND SERIE.Certificato = 0", queryJoin);
	pVSPSet->Open();


	// Se esistono delle serie da esaminare predispongo alcune variabili
	if(!pVSPSet->IsEOF())
	{
		codVerbaleInEsame = pVSPSet->m_CodVerbale;
		numVerb.Format("%d/%d",pVSPSet->m_ProgParziale, pVSPSet->m_ProgTotale);
	}

	// Ciclo di esame delle informazioni necessarie a rilevare i certificati da erogare
	/*Durante il ciclo esamina le caratteristiche della serie */
	while( !pVSPSet->IsEOF() )
	{
		//La serie non è la prima serie di un nuovo certificato,
		if(pVSPSet->m_NuovoCertificato!=1)
		{
			if( codVerbaleInEsame == pVSPSet->m_CodVerbale )
				numSerie++;				
			// Controllo di sicurezza nel caso in cui la prima serie di un verbale successivo 
			// non abbia checcato il flag NuovoCertificato
		}
		else
		{
      if( (codSerieInEsame!=0) && (datiInseriti) )
			{
				// La serie è la prima di un certificato candidato successivo al primo
				// abbiamo a disposizione le info relative al documento precedente
				infoCert.Format("@%d@%d@%d@%s", posizioneCertificato, numSerie, numProvini, numVerb);
				infoCert = m_pTipiCertificatoSet->m_Nome + infoCert;
				paryProposti.Add(codSerieInEsame);
				paryInfoCert.Add(infoCert);

				paryTipoCert.Add(m_pTipiCertificatoSet->m_Codice);
			}

			
			// Si predispongono le variabili per l'esame della serie corrente
			codSerieInEsame = pVSPSet->m_CodSerie;
			datiInseriti = TRUE;
			SINCRONIZE(m_pTipiCertificatoSet, pVSPSet->m_TipoCertificato);
			numSerie = 1;
			numProvini = 0;
				
			// Riparte dal primo certificato ogni volta che si cambia verbale
			if(pVSPSet->m_CodVerbale != codVerbaleInEsame)
			{
        numVerb.Format("%d/%d",pVSPSet->m_ProgParziale, pVSPSet->m_ProgTotale);
				posizioneCertificato = 1;
				codVerbaleInEsame = pVSPSet->m_CodVerbale;
			}	
			else
				posizioneCertificato++;			
			
		}  //end if(pSerieSet->m_NuovoCertificato==1)

		// Verifico che i dati siano stati inseriti per tutti i provini
		// scandendo tutti i record relativi alla serie in esame
		
		tempSerie = pVSPSet->m_CodSerie;
		while(tempSerie==pVSPSet->m_CodSerie && !pVSPSet->IsEOF() )
		{
      numProvini ++;
			if( pVSPSet->IsFieldNull(&pVSPSet->m_DataInsertProvini) && datiInseriti)
				datiInseriti = FALSE;
			pVSPSet->MoveNext();
		}

	}//Fine del ciclo di esame delle serie

	// Questo ultimo passo è necessario perchè il ciclo può terminare 
	// senza aver valutato i dati relativi all'ultima serie 
	if( (codSerieInEsame!=0) && (datiInseriti) )
	{
		infoCert.Format("@%d@%d@%d@%s", posizioneCertificato, numSerie, numProvini, numVerb);
		infoCert = m_pTipiCertificatoSet->m_Nome + infoCert;
		paryProposti.Add(codSerieInEsame);
		paryInfoCert.Add(infoCert);

		paryTipoCert.Add(m_pTipiCertificatoSet->m_Codice);
	}
	
	//-- Reperimento del più alto codice certificato fra quelli presenti nel database per l'anno in corso --//

	// reperisco l'anno in corso
	CTime inizioAnno(CTime::GetCurrentTime().GetYear(), 1,1,1,1,1,1);
	CString queryData;
	queryData.Format("CERTIFICATI.DataEmissione >= '%s'", inizioAnno.Format("%Y-%m-%d"));
	long codiceMax = 0;

	pCertificatiSet->m_strSort = "NumeroCertificato ASC";
	pCertificatiSet->m_strFilter = queryData;
	pCertificatiSet->Open();
	


	if( !pCertificatiSet->IsEOF() )
	{
		pCertificatiSet->MoveLast();
		codiceMax = pCertificatiSet->m_NumeroCertificato;
	}
		
	//----------------------- Fine del reperimento info certificati -----------------------//

	//t = clock() - t;
	//pApp->WriteProfileInt("tempi","Erogazione certificati",t);

	//--------------- Inizializzazione ed apertura del dialogo di emissione ----------------//

	if( paryProposti.GetSize()>0 )
	{
		
		CEmissioneCertificatiDlg dlg;
		dlg.m_paryProposti				= &paryProposti;
		dlg.m_paryInfoCertificato = &paryInfoCert;
		dlg.m_paryScelti					= &paryScelti;
		dlg.m_nCodiceProposto			= codiceMax + 1;
		dlg.m_paryTipiCertificato	= &paryTipoCert;
		dlg.m_parySceltiAderenza	= &parySceltiAderenza;
	
//--- Operazioni di scrittura sul database per l'emissione dei certificati scelti ---//
		if( dlg.DoModal()==IDOK )
		{	
      CUIntArray aryCodiciVerbaliCertificati;
			try
			{
				pApp->BeginTrans();
				int numeroCertificato = dlg.m_nCodicePrimo;
				long codPrimaSerie;
				long tipoCertificato = 0;
				long numVerbaleInCorso;

				for(int i=0; i<paryScelti.GetSize(); i++)
				{				
					// il certificato è identificato dal codice della prima serie inclusa
					codPrimaSerie = paryScelti.GetAt(i);
          m_pGlobalSerieSet->Requery();
					while(m_pGlobalSerieSet->m_Codice != codPrimaSerie && !m_pGlobalSerieSet->IsEOF())
						m_pGlobalSerieSet->MoveNext();
					if(m_pGlobalSerieSet->IsEOF())
						break;

					// --- Verifica della completezza dei dati per le serie dello stesso verbale
					CString msg = "";
					BOOL datiCompleti = TRUE;
					for(SET_START(pVSPSet); !pVSPSet->IsEOF(); pVSPSet->MoveNext() )
						if(pVSPSet->m_Verbale == m_pGlobalSerieSet->m_Verbale 
							&& pVSPSet->IsFieldNull(&pVSPSet->m_DataInsertProvini) )
						{
							msg.Format("Per il verbale %d/%d, ",pVSPSet->m_ProgParziale, pVSPSet->m_ProgTotale);
							msg += "di cui si sta erogando un certificato, risultano delle serie i cui dati sono incompleti.\nProseguire comunque con l'operazione?";
							datiCompleti = FALSE;
						}

					if(!datiCompleti && IDNO == AfxMessageBox(msg, MB_YESNO) )
						continue;
					//__________________________________________________________________________//

					
					numVerbaleInCorso = m_pGlobalSerieSet->m_Verbale;
					tipoCertificato = m_pGlobalSerieSet->m_TipoCertificato; // identifico il tipo certificato
          aryCodiciVerbaliCertificati.Add(numVerbaleInCorso);
					//--- operazioni di aggiornamento della tabella dei certificati ---/
					
					pCertificatiSet->AddNew();
					pCertificatiSet->m_NumeroCertificato	= numeroCertificato;
					pCertificatiSet->m_DataEmissione			= CTime::GetCurrentTime();
					pCertificatiSet->m_TipoCertificato		= tipoCertificato;
					pCertificatiSet->m_Verbale						= m_pGlobalSerieSet->m_Verbale;
					pCertificatiSet->m_Aderenza						= parySceltiAderenza[i];

					pCertificatiSet->Update();
					
					//-- reperisco il valore del codice assegnato al certificato
					long codAssegnato;
					pCertificatiSet->m_strSort = "Codice ASC";
					CString query;
					query.Format("CERTIFICATI.NumeroCertificato = %d", numeroCertificato);
					pCertificatiSet->m_strFilter = queryData + " AND " + query;
					pCertificatiSet->Requery();
					pCertificatiSet->MoveLast();
					codAssegnato = pCertificatiSet->m_Codice;
						
					
					// Per la prima serie inserisco il codice del certificato
					m_pGlobalSerieSet->Edit();
					m_pGlobalSerieSet->m_Certificato = codAssegnato;
					m_pGlobalSerieSet->Update();
					m_pGlobalSerieSet->MoveNext();

					//--- operazioni per le serie fino alla prima di un nuovo certificato ---/
					// Il controllo rispetto al verbale è solo per sicurezza nel caso in cui 
					// la prima serie del successivo verbale non abbia il check nuovoCertificato
					// correttamente impostato
					while( !m_pGlobalSerieSet->IsEOF() && m_pGlobalSerieSet->m_NuovoCertificato == 0 
						&& numVerbaleInCorso == m_pGlobalSerieSet->m_Verbale)
					{
						m_pGlobalSerieSet->Edit();
						m_pGlobalSerieSet->m_Certificato = codAssegnato;
						m_pGlobalSerieSet->Update();
						m_pGlobalSerieSet->MoveNext();
					}
					numeroCertificato++;
						
				} // end for(int i=0; i<paryScelti->GetSize(); i++)
				pApp->CommitTrans();
  		}
			catch(CDBException* e)
			{
				/*----- transazione fallita ----*/
				pApp->Rollback();
				AfxMessageBox( e->m_strError );
			}
      m_pGlobalSerieSet->Requery();
      if(aryCodiciVerbaliCertificati.GetSize() > 0)
      {
        CString str, strFilter;
        // Se il verbale è stato fatturato e sono stati emessi tutti i certificati, lo chiudo
        for(int n = 0; n < aryCodiciVerbaliCertificati.GetSize(); n++)
        {
          str.Format("Codice = %ld", aryCodiciVerbaliCertificati.GetAt(n));
          strFilter += str + " OR ";
        }
        strFilter.TrimRight(" OR ");
        m_pGlobalVerbaliSet->m_strFilter = strFilter;
        m_pGlobalVerbaliSet->Requery();
        BOOL bCertificato = TRUE;
        for(SET_START(m_pGlobalVerbaliSet); !m_pGlobalVerbaliSet->IsEOF(); m_pGlobalVerbaliSet->MoveNext())
        {
          if(m_pGlobalVerbaliSet->IsFieldNull(&m_pGlobalVerbaliSet->m_NumeroFattura) || m_pGlobalVerbaliSet->m_NumeroFattura == 0)
            continue;
          // Se il verbale è stato fatturato, controllo le serie
          bCertificato = TRUE;
          m_pGlobalSerieSet->m_strFilter.Format("Verbale = %ld", m_pGlobalVerbaliSet->m_Codice);
          m_pGlobalSerieSet->Requery();
          for(SET_START(m_pGlobalSerieSet); !m_pGlobalSerieSet->IsEOF(); m_pGlobalSerieSet->MoveNext())
          {
            if(m_pGlobalSerieSet->IsFieldNull(&m_pGlobalSerieSet->m_Certificato) || m_pGlobalSerieSet->m_Certificato == 0)
            {
              // C'è una serie non certificata
              bCertificato = FALSE;
              break;
            }
          }
          if(bCertificato)
          {
            m_pGlobalVerbaliSet->Edit();
            m_pGlobalVerbaliSet->m_DataChiusura = CTime::GetCurrentTime();
            m_pGlobalVerbaliSet->Update();
          }
        }
      }
			StampaCertificati(true);
      m_pVerbaliSet->Requery();
      pApp->ReloadTree(TREELABEL_VERBALIFATTPROFORMA, -1);
      pApp->ReloadTree(TREELABEL_VERBALIPRECEDENTI, -1);
      pApp->ReloadTree(TREELABEL_VERBALIULTIMOMESE, -1);
      LoadCurRecord(TRUE);
			UpdateData(FALSE);
		}//end if DoModal==IDOK
	}
	else
		AfxMessageBox("Operazione non disponibile!\nNon sono stati rilevati documenti in fase di emissione.");

	pApp->DisabilitaCertificazione(&strDatiOccupante, FALSE);
	pVSPSet->Close();
	delete pVSPSet;
	pCertificatiSet->Close();
	delete pCertificatiSet;
}

void CVerbaliView::OnPrintMinuta() 
{
	CMinuteDlg dlg;
	dlg.m_pTCertSet = m_pTipiCertificatoSet;
	if( IDOK == dlg.DoModal() )
	{
		m_paryTCerMinute.Copy(dlg.m_aryTCertificato);
		if(m_paryTCerMinute.GetSize()>0)
			PrintMinuta();
	}
}

#define STAMPA_VERBALE_AD_AGHI					0
#define STAMPA_VERBALE_CARTA_LIBERA			1
#define STAMPA_VERBALE_CON_INTESTAZIONE	2

void CVerbaliView::OnPrnCartaIntestata() 
{
	m_nPrintMode = STAMPA_VERBALE_AD_AGHI;
  PrintVerbale();	
}

void CVerbaliView::OnPrnCartaLibera() 
{
	m_nPrintMode = STAMPA_VERBALE_CARTA_LIBERA;
  PrintVerbale();	
}

void CVerbaliView::OnPrnVerbaleConIntestazione()
{
	m_nPrintMode = STAMPA_VERBALE_CON_INTESTAZIONE;
  PrintVerbale();	
}

void CVerbaliView::PrintVerbale()
{
  CPrintInterpreter prnInterpreter;
  CStringArray strNames, strValues;
  BOOL bPrint = FALSE;
  CTime data = CTime::GetCurrentTime();
  CString printFileName, strPrinter, strPrnFile, docname;
	int TipoCertificato = 0;
  int VerID;
	CWinSigmaApp* pApp	= (CWinSigmaApp*)AfxGetApp();

  if(m_pVerbaliSet->IsBOF() || m_pVerbaliSet->IsEOF())
	{
	  MessageBeep(-1);
		return;
	}
	// La stampa viene fatta su un file che ha come nome il progressivo totale del verbale
  printFileName.Format("%d_%d.txt", m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale);
  VerID = m_pVerbaliSet->m_Codice;

	// imposta il nome del file secondo le specifiche della gestione documentale (s.c. 14.09.2017)
  docname.Format("VA-%d-%d", m_pVerbaliSet->m_ProgressivoTotale, m_pVerbaliSet->m_DataAccettazione.GetYear());
	prnInterpreter.SetDocName(docname);

#ifdef WINSIGMA2
  if(!prnInterpreter.PrePrinting())
    return;
#else
  if(m_nPrintMode != STAMPA_VERBALE_AD_AGHI)
  {
    if(!prnInterpreter.PrePrinting())
      return;
  }
#endif
  m_pSerieSet->m_strFilter.Format("Verbale = %d", m_pVerbaliSet->m_Codice);
  m_pSerieSet->m_strSort = "TipoCertificato, Codice ASC";
  m_pSerieSet->Requery();
  m_bSpianatura = FALSE;
  for(SET_START(m_pSerieSet); !m_pSerieSet->IsEOF(); m_pSerieSet->MoveNext())
  {
		TipoCertificato = m_pSerieSet->m_TipoCertificato;
	  ASSERT(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_ServAggiungibile));
    if(m_pSerieSet->m_ServAggiungibile)
    {
      if(m_pSerieSet->m_Servizio1 == m_pSerieSet->m_ServAggiungibile
			   || m_pSerieSet->m_Servizio2 == m_pSerieSet->m_ServAggiungibile
			   || m_pSerieSet->m_Servizio3 == m_pSerieSet->m_ServAggiungibile
			   || m_pSerieSet->m_Servizio4 == m_pSerieSet->m_ServAggiungibile
			   || m_pSerieSet->m_Servizio5 == m_pSerieSet->m_ServAggiungibile
			   || m_pSerieSet->m_Servizio6 == m_pSerieSet->m_ServAggiungibile)
        m_bSpianatura = TRUE;  	     
			else
			{
        m_bSpianatura = FALSE;  
			  break;
			}
		}
  }
  SET_START(m_pSerieSet);

  CAziendeSet* pAziende = new CAziendeSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
  pAziende->m_strFilter.Format("Codice = %d", m_pVerbaliSet->m_CodiceAzFattura);
  pAziende->Open();
  m_bPrivato = pAziende->m_Privato;
  if (!pAziende->m_Note.IsEmpty())
    m_bNote = TRUE;
  else
    m_bNote = FALSE;
  pAziende->Close();

  if(m_pVerbaliSet->m_TipoVerbale == VERB_GEOLOGIA)
	{
    strPrnFile = ".\\VerbaliGeo.prn";
	}
  else
	{
#ifdef WINSIGMA2
		CTipiCertificatoSet* pTipiCertificato = new CTipiCertificatoSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
		pTipiCertificato->m_strFilter.Format("Codice = %d", TipoCertificato);
		pTipiCertificato->Open();
		if (!pTipiCertificato->IsEOF())
		{
			strPrnFile.Format(".\\%s", pTipiCertificato->m_LayoutStampaVerbali);
		}
		else
		{
			strPrnFile = ".\\VerbaliSigma2.prn";
		}
		
		pTipiCertificato->Close();
		delete pTipiCertificato;
	}
	// Simulazione
  m_nTotalePagine = 0;
  prnInterpreter.SetPage(1);
  prnInterpreter.StartSimulation();
  prnInterpreter.Print(strPrnFile, &strNames, &strValues, NULL, &ScanCampioni);
  m_nTotalePagine = prnInterpreter.GetPage() - 1;
  prnInterpreter.EndSimulation();
  prnInterpreter.SetPage(1);
  SET_START(m_pSerieSet);
  ScanFields(&strNames, &strValues);
  prnInterpreter.Print(strPrnFile, &strNames, &strValues, NULL, &ScanCampioni);
	prnInterpreter.PostPrinting();
	if(m_nPrintMode == STAMPA_VERBALE_AD_AGHI)
	{
		// Scrivo la data nel record
		CString strSql("");
		strSql.Format("UPDATE VERBALI SET DataPrimaStampa = '%s' Where Codice = %d", data.Format("%Y-%m-%d"), VerID);
		((CWinSigmaApp*)AfxGetApp())->m_db.ExecuteSQL(strSql);
	}
#else
		CTipiCertificatoSet* pTipiCertificato = new CTipiCertificatoSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
		pTipiCertificato->m_strFilter.Format("Codice = %d", TipoCertificato);
		pTipiCertificato->Open();
		if (!pTipiCertificato->IsEOF())
		{
			strPrnFile.Format(".\\%s", pTipiCertificato->m_LayoutStampaVerbali);
		}
		else
		{
			strPrnFile = ".\\Verbali.prn";
		}
		
		pTipiCertificato->Close();
		delete pTipiCertificato;
	}

	// imposta la stampa con l'header
	if(m_nPrintMode == STAMPA_VERBALE_CON_INTESTAZIONE)
	{
		int pos = strPrnFile.Find(".prn");
		strPrnFile.Insert(pos, "_H");
		prnInterpreter.SetHeaderFile(pApp->GetCurrentDirectory() + "\\" + pApp->m_headerVerbaliPrn);
	}
	else if(m_nPrintMode == STAMPA_VERBALE_CARTA_LIBERA)
	{
		int pos = strPrnFile.Find(".prn");
		strPrnFile.Insert(pos, "_H");
	}

	// Simulazione
  m_nTotalePagine = 0;
  prnInterpreter.SetPage(1);
  prnInterpreter.StartSimulation();
  if(m_nPrintMode == STAMPA_VERBALE_AD_AGHI)
    prnInterpreter.PrintText(strPrnFile, printFileName, &strNames, &strValues, NULL, &ScanCampioni);
  else
    prnInterpreter.Print(strPrnFile, &strNames, &strValues, NULL, NULL, &ScanCampioni);
  m_nTotalePagine = prnInterpreter.GetPage() - 1;
  prnInterpreter.EndSimulation();
  prnInterpreter.SetPage(1);
  SET_START(m_pSerieSet);
  ScanFields(&strNames, &strValues);
  if(m_nPrintMode == STAMPA_VERBALE_AD_AGHI)
  {
    if(prnInterpreter.PrintText(strPrnFile, printFileName, &strNames, &strValues, NULL, &ScanCampioni))
    {
      CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
      SetTimer(TIME_OUT_MSG_ID, 10000, NULL);
      // Il file è pronto, posso lanciare il thread di stampa
      CPrinterThread prnThread;
      switch(m_pVerbaliSet->m_TipoVerbale)
      {
      case VERB_IN_CONCESSIONE:
        strPrinter = pApp->GetProfileString(CONFIGURAZIONE, STAMPA_CONCESSIONE);
        break;
      case VERB_NON_IN_CONCESSIONE:
			case VERB_NC_PROVE_DI_CARICO :
			case VERB_NC_CONGL_BITUMINOSI	:
			case VERB_NC_INERTI	:
			case VERB_NC_MONITORAGGI :
			case VERB_NC_VARIE	:
			case VERB_NC_GEOTECNICA :
			case VERB_NC_LINEE_VITA:
			case VERB_NC_INDAGINI_MURATURE:
			case VERB_NC_INDAGINI_CLS:
			case VERB_NC_MAT_METALLICI:
        strPrinter = pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE);
        break;
      case VERB_GEOLOGIA:
        strPrinter = pApp->GetProfileString(CONFIGURAZIONE, STAMPA_GEOLOGIA);
        break;
      }
      prnThread.BeginPrinterThread(printFileName, strPrinter, this->m_hWnd);
      
			// Scrivo la data nel record
			CString strSql("");
			strSql.Format("UPDATE VERBALI SET DataPrimaStampa = '%s' Where Codice = %d", data.Format("%Y-%m-%d"), VerID);
			((CWinSigmaApp*)AfxGetApp())->m_db.ExecuteSQL(strSql);
    }
  }
  else
  {
    prnInterpreter.Print(strPrnFile, &strNames, &strValues, NULL, NULL, &ScanCampioni);
  	prnInterpreter.PostPrinting();
  }
#endif 
  m_pSerieSet->m_strFilter.Empty();
  m_pSerieSet->Requery();
}



BOOL CVerbaliView::ScanFields(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
  int n;
	CString str, strApp;
  if(m_pVerbaliSet->IsEOF())
    return FALSE;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  pFieldNames->RemoveAll();
  pFieldValues->RemoveAll();

  // Numero verbale
  pFieldNames->Add("numeroVerbale");
#ifdef WINSIGMA2
  str.Format("A%d", m_pVerbaliSet->m_ProgressivoTotale);
#else
  str.Format("%d/%d", m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale);
#endif
  pFieldValues->Add(str);
  // Tipo di verbale
  pFieldNames->Add("tipoVerbale");
  switch(m_pVerbaliSet->m_TipoVerbale)
  {
  case VERB_IN_CONCESSIONE:
    pFieldValues->Add("Prove in concessione");
    break;
  case VERB_NON_IN_CONCESSIONE:
	case VERB_NC_PROVE_DI_CARICO :
	case VERB_NC_CONGL_BITUMINOSI	:
	case VERB_NC_INERTI	:
	case VERB_NC_MONITORAGGI :
	case VERB_NC_VARIE	:
	case VERB_NC_GEOTECNICA :
	case VERB_NC_LINEE_VITA:
	case VERB_NC_INDAGINI_MURATURE:
	case VERB_NC_INDAGINI_CLS:
	case VERB_NC_MAT_METALLICI:
    pFieldValues->Add("Prove non in concessione");
    break;
  case VERB_GEOLOGIA:
    pFieldValues->Add("Prove geotecniche");
    break;
  default:
    pFieldValues->Add("");
    break;
  }
  // Data
  pFieldNames->Add("data");
  str.Format("%s, %s",pApp->GetProfileString(CONFIGURAZIONE, LABORATORIO), m_pVerbaliSet->m_DataAccettazione.Format("%d/%m/%Y") );
  pFieldValues->Add(str);
  // Intestatario certificati
  pFieldNames->Add("codAzCertificati");
  str = m_pVerbaliSet->m_IDAzCertificato;
  str.MakeUpper();
  pFieldValues->Add(str);
  pFieldNames->Add("nomeAzCertificati");
  pFieldValues->Add(m_pVerbaliSet->m_NomeAzCertificato);
  pFieldNames->Add("indirizzoCertificati");
  pFieldValues->Add(m_pVerbaliSet->m_IndirizzoCertificato);
  // Impresa
  pFieldNames->Add("codImpresa");
  pFieldValues->Add(m_pVerbaliSet->m_IDImpresaRichiedente);
  pFieldNames->Add("nomeImpresa");
  pFieldValues->Add(m_pVerbaliSet->m_NomeImpresa);
  pFieldNames->Add("indirizzoImpresa");
  if (!m_pVerbaliSet->m_NomeImpresa.IsEmpty())
    pFieldValues->Add(m_pVerbaliSet->m_IndirizzoRichiedente);
  else
    pFieldValues->Add("");
  // Cantiere
  pFieldNames->Add("cantiere1");
  pFieldNames->Add("cantiere2");
  pFieldNames->Add("cantiere3");
	str = m_pVerbaliSet->m_Cantiere;
	n = 0;
  str.Replace("\r\n", " ");
  str.TrimLeft();
  int nAcapo = DIM_STR_CANTIERE / 3;
  if(str.GetLength() > DIM_STR_CANTIERE / 3)
  {
    strApp = str.Left(nAcapo);
    if((n = strApp.ReverseFind(' ')) > 0)
      pFieldValues->Add(str.Left(n));
    else
    {
      pFieldValues->Add(str.Left(nAcapo));
      n = nAcapo;
    }
    strApp = str.Mid(n); 
    strApp.TrimLeft();
		strApp.TrimLeft("-");
    strApp.TrimLeft();
    str = strApp;
    nAcapo = DIM_STR_CANTIERE / 3;
    if(str.GetLength() > DIM_STR_CANTIERE / 3)
    {
      strApp = str.Left(nAcapo);
      if((n = strApp.ReverseFind(' ')) > 0)
        pFieldValues->Add(str.Left(n));
      else
      {
        pFieldValues->Add(str.Left(nAcapo));
        n = nAcapo;
      }
      strApp = str.Mid(n, DIM_STR_CANTIERE / 3); 
      strApp.TrimLeft();
  		strApp.TrimLeft("-");
      strApp.TrimLeft();
      pFieldValues->Add(strApp);
    }
    else
    {
      pFieldValues->Add(strApp);
      pFieldValues->Add("");
    }
  }
  else
  {
    pFieldValues->Add(str);
    pFieldValues->Add("");
    pFieldValues->Add("");
  }
  // Direttore dei lavori
  pFieldNames->Add("direttoreLavori");
  pFieldValues->Add(m_pVerbaliSet->m_Direttore);
  if(!m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_LetteraIncarico) && m_pVerbaliSet->m_LetteraIncarico)
  {
		pFieldNames->Add("letteraLabel");
    pFieldValues->Add("Lettera di incarico......:");
    pFieldNames->Add("lettera");
    pFieldValues->Add(m_pVerbaliSet->m_NumLetteraIncarico);
  }
  pFieldNames->Add("domanda");
  if(!m_pVerbaliSet->m_DomandaSottoscritta)
    pFieldValues->Add("Domanda di prove NON sottoscritta dal D.L.");
  else
    pFieldValues->Add("Domanda di prove sottoscritta dal D.L.");
  // Proprietario
  pFieldNames->Add("proprietario1");
  pFieldNames->Add("proprietario2");
	str = m_pVerbaliSet->m_Proprietario;
	n = 0;
  str.Replace("\r\n", " ");
  str.TrimLeft();
  nAcapo = DIM_STR_CANTIERE / 2;
  if(str.GetLength() > DIM_STR_CANTIERE / 2)
  {
    strApp = str.Left(nAcapo);
    if((n = strApp.ReverseFind(' ')) > 0)
      pFieldValues->Add(str.Left(n));
    else
    {
      pFieldValues->Add(str.Left(nAcapo));
      n = nAcapo;
    }
    strApp = str.Mid(n, DIM_STR_CANTIERE / 2); 
    strApp.TrimLeft();
		strApp.TrimLeft("-");
    strApp.TrimLeft();
    pFieldValues->Add(strApp);
  }
  else
  {
    pFieldValues->Add(str);
    pFieldValues->Add("");
  }
  // Campioni consegnati
  pFieldNames->Add("materialeConsegnato");
	str = m_pVerbaliSet->m_DescrizioneMateriale;
  pFieldValues->Add(str);
  // Prove richieste
  pFieldNames->Add("proveRichiesteNote");
  pFieldValues->Add(m_pVerbaliSet->m_ProveRichieste);
  // Tabella campioni
  pFieldNames->Add("linea");
  pFieldValues->Add("------------------------------------------------------------------------------");
  if(!m_pSerieSet->IsBOF())
  {
    pFieldNames->Add("campioni");
    pFieldValues->Add("C A M P I O N I");
    pFieldNames->Add("sigle");
    pFieldValues->Add("SIGLE");
    pFieldNames->Add("prelievo");
    pFieldValues->Add("P R E L I E V O");
    pFieldNames->Add("posizione");
    pFieldValues->Add("POS");
    pFieldNames->Add("numero");
    pFieldValues->Add("N.");
    pFieldNames->Add("contrassegni");
    pFieldValues->Add("CONTRASSEGNI");
    pFieldNames->Add("tipo");
    pFieldValues->Add("TIPO E CARATTERISTICHE");
    pFieldNames->Add("struttura");
    pFieldValues->Add("STRUTTURA");
		pFieldNames->Add("vpfornitore");
    pFieldValues->Add("VP/Fornitore");
    pFieldNames->Add("dataPrelievo");
    pFieldValues->Add("DATA");
    pFieldNames->Add("certificato");
    pFieldValues->Add("CER");
    pFieldNames->Add("barra");
    pFieldValues->Add("|");
  }
  // Spianatura
  pFieldNames->Add("spianatura");
  if(m_bSpianatura)
    pFieldValues->Add("Si");
  else
    pFieldValues->Add("(se necessaria)");
  // Azienda fatturazione
  pFieldNames->Add("codAzFattura");
  pFieldValues->Add(m_pVerbaliSet->m_IDAzFattura);
  
  pFieldNames->Add("nomeAzFattura");
  CString csAzFat(m_pVerbaliSet->m_NomeAzFattura);
  if (m_bNote == TRUE)
    csAzFat.Insert(csAzFat.GetLength(), "*");
  pFieldValues->Add(csAzFat);
  
  pFieldNames->Add("indirizzoAzFattura");
  pFieldValues->Add(m_pVerbaliSet->m_IndirizzoFattura);
  pFieldNames->Add("partitaIVA");
  if(!m_bPrivato)
    str.Format("Partita I.V.A.:   %s", m_pVerbaliSet->m_P_IVA);
  else
    str = "Prestazione a privato";
  pFieldValues->Add(str);
  pFieldNames->Add("condPagamento");
  pFieldValues->Add(m_pVerbaliSet->m_Pagamento);

  pFieldNames->Add("codFiscale");
 if(!m_pVerbaliSet->m_CodFiscale.IsEmpty())
    str.Format("Codice Fiscale:   %s", m_pVerbaliSet->m_CodFiscale);
  else
    str = "";
  pFieldValues->Add(str);

  // Richiedente
  pFieldNames->Add("richiedente");
  pFieldValues->Add(m_pVerbaliSet->m_Richiedente);
  // Consegna
  pFieldNames->Add("consegna");
  if(m_pVerbaliSet->m_Spedizione)
  {
    if(!m_pVerbaliSet->m_NoteSpedizione.IsEmpty())
      str = m_pVerbaliSet->m_NoteSpedizione;
    else
      str = "Spedire";
  }
  else
	{
		if(m_pVerbaliSet->m_NoteSpedizione.IsEmpty())
			str = "INVIO";
		else
			str.Format("%s", m_pVerbaliSet->m_NoteSpedizione);
	}
  if(!m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_Urgenza) && m_pVerbaliSet->m_Urgenza)
  {
    if (m_pVerbaliSet->m_Urgenza != 2)
      strApp.Format("  %s - %s", m_pVerbaliSet->m_DataConsegna.Format("%d/%m/%Y"), m_pVerbaliSet->m_OraConsegna);
    else
      strApp.Format("  %s", m_pVerbaliSet->m_DataConsegna.Format("%d/%m/%Y"));
    
    str += strApp;
  }
  pFieldValues->Add(str);
  // Urgenza
  if(!m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_Urgenza) && m_pVerbaliSet->m_Urgenza)
  {
    if (m_pVerbaliSet->m_Urgenza != 2)
    {
      pFieldNames->Add("urgenza");
		  pFieldValues->Add("Procedura d'urgenza (maggiorazione 50%).............firma:...................");
    }
  }
  // Operatore
  pFieldNames->Add("operatore");
  strApp.Empty();
  if(!m_pVerbaliSet->m_Operatore.IsEmpty())
  {
    if((n = m_pVerbaliSet->m_Operatore.Find(" ")) != -1)
    {
      strApp = m_pVerbaliSet->m_Operatore.GetAt(n + 1);
      strApp += ".";
      strApp += m_pVerbaliSet->m_Operatore.GetAt(0);
      strApp += ".";
    }
    else
      strApp = m_pVerbaliSet->m_Operatore.GetAt(0) + ".";
  }
  pFieldValues->Add(strApp);
  pFieldNames->Add("pagina");
  str.Format("/ %d", m_nTotalePagine);
  pFieldValues->Add(str);
  return TRUE;
}

BOOL CVerbaliView::ScanCampioni(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
	CString str, strTemp;
  static int numCert;
	int i = 0, l = 0;

  pFieldNames->RemoveAll();
  pFieldValues->RemoveAll();
  if(m_pSerieSet->IsEOF())
  {
    numCert = 0;
    return FALSE;
  }
  for(SET_START(m_pTipiCertificatoSet); !m_pTipiCertificatoSet->IsEOF(); m_pTipiCertificatoSet->MoveNext())
  {
    if(m_pTipiCertificatoSet->m_Codice == m_pSerieSet->m_TipoCertificato)
      break;
  }
  if(m_pTipiCertificatoSet->IsEOF())
    return FALSE;
  pFieldNames->Add("numeroCampioni");
  if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_NumeroProvini))
    str.Format("%d", m_pSerieSet->m_NumeroProvini);
  else
    str.Empty();
  pFieldValues->Add(str);

  pFieldNames->Add("tipoCaratteristiche");
	str = m_pSerieSet->m_Materiale;
	if(m_nPrintMode == STAMPA_VERBALE_AD_AGHI)
	{
		str.Replace("²", "ý");
		str.Replace("°", "ø");
	}
		
  pFieldValues->Add(str);
	
  pFieldNames->Add("dimensione1");
  if(!m_pTipiCertificatoSet->m_Dimensione1.IsEmpty())
    str.Format("%.0f", m_pSerieSet->m_Dimensione1);
  else
    str.Empty();
  pFieldValues->Add(str);
  pFieldNames->Add("dimensione2");
  if(!m_pTipiCertificatoSet->m_Dimensione2.IsEmpty())
    str.Format("%.0f", m_pSerieSet->m_Dimensione2);
  else
    str.Empty();
  pFieldValues->Add(str);
  pFieldNames->Add("dimensione3");
  if(!m_pTipiCertificatoSet->m_Dimensione3.IsEmpty())
    str.Format("%.0f", m_pSerieSet->m_Dimensione3);
  else
    str.Empty();
  pFieldValues->Add(str);

	// sigla o sigla1 - sigla2 per cubi 2018
  pFieldNames->Add("sigla");
	str = "";
  if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Sigla))
	{
		str = m_pSerieSet->m_Sigla;
		if(m_nPrintMode == STAMPA_VERBALE_AD_AGHI)
		{
			str.Replace("°", "ø");
  		str.Replace("²", "ý");
		}
	}  
  pFieldValues->Add(str);

	str = "";
  if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Sigla2))
	{
		str = m_pSerieSet->m_Sigla2;
		if(!str.IsEmpty())
		{
		  pFieldNames->Add("sigla_sep");
		  pFieldNames->Add("sigla2");
			if(m_nPrintMode == STAMPA_VERBALE_AD_AGHI)
			{
				str.Replace("°", "ø");
  			str.Replace("²", "ý");
			}
		  pFieldValues->Add(" - ");
		  pFieldValues->Add(str);
		}
	}  

	// struttura e verbale di prelievo
	if(m_pSerieSet->m_TipoCertificato == 18)
	{
		// certificato cubi DM 2018
    pFieldNames->Add("struttura");
		if(!m_pSerieSet->m_StrutturaPrelievo.IsEmpty())
		{
			str.Format("%s - %s", m_pSerieSet->m_StrutturaPrelievo, m_pSerieSet->m_VerbalePrelievo);
		}
		else
		{
			str.Format("%s", m_pSerieSet->m_VerbalePrelievo);
		}
		if(m_nPrintMode == STAMPA_VERBALE_AD_AGHI)
		{
			str.Replace("°", "ø");
			str.Replace("²", "ý");
		}
    pFieldValues->Add(str);
	} 
	else if(m_pSerieSet->m_TipoCertificato == 17)   
	{
		// certificato ferri B450 DM 2018
    pFieldNames->Add("struttura");
		if(!m_pSerieSet->m_StrutturaPrelievo.IsEmpty())
		{
			str.Format("%s - %s", m_pSerieSet->m_StrutturaPrelievo, m_pSerieSet->m_VerbalePrelievo);
		}
		else
		{
			str.Format("%s", m_pSerieSet->m_VerbalePrelievo);
		}
		if(m_nPrintMode == STAMPA_VERBALE_AD_AGHI)
		{
			str.Replace("°", "ø");
			str.Replace("²", "ý");
		}
    pFieldValues->Add(str);
	} 
  else if((!m_pSerieSet->m_StrutturaPrelievo.IsEmpty()) || (m_pSerieSet->m_TipoCertificato == 13))
  {
    pFieldNames->Add("struttura");
		if (m_pSerieSet->m_TipoCertificato == 13)
		{
			str.Format("%s - %s", m_pSerieSet->m_VerbalePrelievo, m_pSerieSet->m_SiglaFornitore);
		}
		else
		{
			str = m_pSerieSet->m_StrutturaPrelievo;
		}
		if(m_nPrintMode == STAMPA_VERBALE_AD_AGHI)
		{
			str.Replace("°", "ø");
			str.Replace("²", "ý");
		}
    pFieldValues->Add(str);
  }

  pFieldNames->Add("data");
  if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_DataPrelievo))
    pFieldValues->Add(m_pSerieSet->m_DataPrelievo.Format("%d/%m/%Y"));
  else
    pFieldValues->Add(m_pSerieSet->m_strDataND);  
  // Posizione del certificato nel verbale
  pFieldNames->Add("posizioneCert");
  if(m_pSerieSet->m_NuovoCertificato)
    numCert++;
  str.Format("%d", numCert);
  pFieldValues->Add(str);
  m_pSerieSet->MoveNext();
  if(m_pSerieSet->IsEOF())
  {
    numCert = 0;
    return FALSE;
  }
  return TRUE;
}

void CVerbaliView::GetDatiFatturazione(void)
{
	CWinSigmaApp*	pApp = (CWinSigmaApp*)AfxGetApp();
  CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  CAziendeSet* pSet = new CAziendeSet(&pApp->m_db);
  CTipiPagamentoSet* pPagamentoSet = pDoc->m_pTipiPagamentoSet;
  CListiniSet*       pListiniSet   = pDoc->m_pListiniInVigoreSet;

  // Cerco il record dell'azienda a cui devo fatturare
  if(m_nCodiceAzFattura && m_nCodiceAzFattura != -1)
  {
    pSet->m_strFilter.Format("Codice = %ld", m_nCodiceAzFattura);
    pSet->Open();
  }
  else
  {
    pSet->Open();
    for(SET_START(pSet); !pSet->IsEOF(); pSet->MoveNext())
    {
      if(pSet->m_ID == m_strCodiceAzFattura)
      {
        m_nCodiceAzFattura = pSet->m_Codice;
        break;
      }
    }
  }
  if(pSet->IsEOF())  
  {
    AfxMessageBox("Impossibile trovare l'azienda per la fatturazione");
    pSet->Close();
    return;
  }
  // Prendo i dati che mi servono per la fatturazione    
  m_strPartitaIva = "";
  m_strCodFiscale = "";
  if(!pSet->IsFieldNull(&pSet->m_P_IVA))
    m_strPartitaIva = pSet->m_P_IVA;
  if(!pSet->IsFieldNull(&pSet->m_CodiceFiscale))
    m_strCodFiscale = pSet->m_CodiceFiscale;

	// verifica presenza email in anagrafica
  if(!pSet->IsFieldNull(&pSet->m_E_Mail))
    m_strEMail = pSet->m_E_Mail;
	else
		m_strEMail.Empty();

	// verifica presenza di note in anagrafica
  if(!pSet->IsFieldNull(&pSet->m_Note))
    m_StaticAlarmNote.ShowWindow(SW_SHOW);
	else
    m_StaticAlarmNote.ShowWindow(SW_HIDE);

  if(!pSet->IsFieldNull(&pSet->m_TipoPagamento) && pSet->m_TipoPagamento != 0)
  {
    SINCRONIZE(pPagamentoSet, pSet->m_TipoPagamento);
    m_strTipoPagamento = pPagamentoSet->m_Nome;
  }
  else
  {
    m_strTipoPagamento.Empty();
    AfxMessageBox("Attenzione: per l'azienda selezionata non è stato definito il tipo di pagamento");
  }
  /*-----listino particolare -----*/
	m_nListinoParticolare = 0;
  for(SET_START(pListiniSet); !pListiniSet->IsEOF(); pListiniSet->MoveNext())
  {
    if(pListiniSet->m_Azienda == m_nCodiceAzFattura)
    {
      m_nListinoParticolare = pListiniSet->m_Codice;
      break;
    }
  }
  pSet->Close();
}

CString CVerbaliView::FormatIndirizzo(CAziendeSet* pSet)
{
  CString strIndirizzo, str;
  ASSERT(!pSet->IsBOF() && !pSet->IsEOF());
  
	strIndirizzo = pSet->m_Indirizzo;
	strIndirizzo += " - ";
	if(!pSet->m_CAP.IsEmpty())
	{
	  strIndirizzo += pSet->m_CAP + " ";
	}
	strIndirizzo += pSet->m_Citta;
	if(!pSet->m_Provincia.IsEmpty())
	{
	  str.Format(" (%s)", pSet->m_Provincia);
		strIndirizzo += str;
  }
  return strIndirizzo;
}

void CVerbaliView::OnSelchangeComboConsegna() 
{
  int m, n = m_ComboConsegna.GetCurSel();
	int nCodAzienda = -1;

  UpdateData();
	m_bRitiro = false;
  m_bSpedizione = true;
  m_strDestinatario.Empty();
	m_strNote.Empty();
	switch(n)
	{
	  case 0:
		  /*---- invio -----*/
      m_bSpedizione = FALSE;
			m_EditDestinatario.EnableWindow(FALSE);
		  UpdateData(FALSE);
		  return;
		case 1:
		  /*--- spedire intestatario certificati ----*/
			m_EditDestinatario.EnableWindow(TRUE);
		  m = AZIENDA_CERTIFICATO;
			nCodAzienda = m_nCodiceAzCertificato;
			break;
		case 2:
		  /*--- spedire intestatario fattura ----*/
			m_EditDestinatario.EnableWindow(TRUE);
		  m = AZIENDA_FATTURA;
			nCodAzienda = m_nCodiceAzFattura;
		  break;
		case 3:
		  /*--- spedire intestatario fattura ----*/
			m_EditDestinatario.EnableWindow(TRUE);
		  m = AZIENDA_IMPRESA;
			nCodAzienda = m_nCodiceImpresa;
		  break;
		case 4:
		  /*--- spedire ad altro ----*/
			m_EditDestinatario.EnableWindow(TRUE);
			nCodAzienda = -1;
		  break;
	  case 5:
		  /*---- ritiro -----*/
      m_bSpedizione = false;
			m_bRitiro = true;
			m_strNote = "RITIRO";
			m_EditDestinatario.EnableWindow(FALSE);
		  UpdateData(FALSE);
		  return;
	}
	if(nCodAzienda != -1)
		FindDatiAziendaSpedizione(nCodAzienda);
	m_EditNote.EnableWindow();
	m_ComboConsegna.GetLBText( m_ComboConsegna.GetCurSel(), m_strNote );
  UpdateData(FALSE);
}


void CVerbaliView::FindDatiAziendaSpedizione(int nCodice)
{
  CString str;

  CAziendeSet* pAziendeSet = new CAziendeSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
  pAziendeSet->m_strFilter.Format("Codice = %ld",nCodice);
  pAziendeSet->Open();
  m_strDestinatario = pAziendeSet->m_RagioneSociale;
  m_strDestinatario += "\r\n";
	m_strDestinatario += pAziendeSet->m_Indirizzo;
  m_strDestinatario += "\r\n";
	if(!pAziendeSet->m_CAP.IsEmpty())
	{
    m_strDestinatario += pAziendeSet->m_CAP;
    m_strDestinatario += " - ";
	}
	m_strDestinatario += pAziendeSet->m_Citta;
	if(!pAziendeSet->m_Provincia.IsEmpty())
	{
    m_strDestinatario += " (";
	  m_strDestinatario += pAziendeSet->m_Provincia;
    m_strDestinatario += ")";
	}
  if(!m_pVerbaliSet->m_NoteSpedizione.IsEmpty())
    m_strNote = m_pVerbaliSet->m_NoteSpedizione;
  pAziendeSet->Close();
}


/////////////////////////////////////////////////////////////
// Restituisce il nome della dll associata al tipoCertificato

CString  CVerbaliView::GetNameModuloDll(long codTipoCertificato)
{
  SINCRONIZE(m_pTipiCertificatoSet, codTipoCertificato);
	return m_pTipiCertificatoSet->m_FinestraDialogo;
}


//////////////////////////////////////////////////////////////////////////
// Verifica se il focus è sulla lista delle serie, nel qual caso propone la
// stampa del certificato relativo alla serie selezionata;
// altrimenti mostra nell'apposito dialogo i certificati emessi e non ancora stampati;
// procede alla stampa dei certificati selezionati nel dialogo.

void CVerbaliView::OnButtonStampaCertificati() 
{
	CWnd* pWind = m_ListSerie.GetFocus();
	if( pWind!=NULL && *pWind == m_ListSerie)
	{
		int n;
		POSITION pos;
		pos = m_ListSerie.GetFirstSelectedItemPosition();
		if( (n = m_ListSerie.GetNextSelectedItem(pos)) >= 0)
			StampaCertificato(m_ListSerie.GetItemData(n));
		else
			StampaCertificati();
	}
	else
		StampaCertificati();
}

void CVerbaliView::OnButtonStampaCertificatiConHeader() 
{
	CWnd* pWind = m_ListSerie.GetFocus();
	if( pWind!=NULL && *pWind == m_ListSerie)
	{
		int n;
		POSITION pos;
		pos = m_ListSerie.GetFirstSelectedItemPosition();
		if( (n = m_ListSerie.GetNextSelectedItem(pos)) >= 0)
			StampaCertificato(m_ListSerie.GetItemData(n), true, true);
		else
			StampaCertificati(true);
	}
	else
		StampaCertificati(true);
}

//////////////////////////////////////////////////////////////////////////////////
//  La funzione riceve il recordset sincronizzato con il certificato da stampare e:
// - riempie gli array con i dati relativi ai campi field del file di layout
// - assegna alla stringa puntata da pFileLayout il nome del file di layout

int CVerbaliView::LoadDatiStampa(long codCertificato, CStringArray* pFieldNames, CStringArray* pFieldValues)
{
	byte pagine = 0;
	typedef int (PROCESTERNA)(long, CAllTables*, CStringArray*, CStringArray* );	
	HINSTANCE hist;
	PROCESTERNA* pFunc;										// Creo una variabile function del tipo precedentemente definito
	if (hist = ::LoadLibrary(m_strDllCorrente))	// Reperimento dell'istanza del modulo cercato
	{
		if(pFunc = (PROCESTERNA*)::GetProcAddress(hist,"RiempiCampi"))
			 pagine = ( pFunc )( codCertificato, m_pTabelle, pFieldNames, pFieldValues );
	}
	SET_START(m_pTabelle->m_pSerieProviniSet);
	return pagine;
}


//////////////////////////////////////////////////
// Scandisce i provini relativi alla serie puntata 
// dal recordset globale m_pSerieProviniSet

BOOL CVerbaliView::ScanProvini(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
	if( m_pTabelle->m_pSerieProviniSet->IsEOF() )
	  return FALSE;
	
	//-- Operazioni per differenziare la stampa del primo elemento della serie --//
	byte bPrimoProvino = TRUE;
	if(m_nCodSerieStampata == m_pTabelle->m_pSerieProviniSet->m_CodiceSerie)
		bPrimoProvino = FALSE;
	m_nCodSerieStampata = m_pTabelle->m_pSerieProviniSet->m_CodiceSerie;
	m_nContaProvini++;
	//---------------------------------------------------------------------------//

	typedef BOOL (PROCESTERNA)(CAllTables*, CStringArray*, CStringArray*, byte, int, long);	
	HINSTANCE hist;
	PROCESTERNA* pFunc;		
	BOOL esito = 0;
	if (hist = ::LoadLibrary(m_strDllCorrente))	
	{
		if(pFunc = (PROCESTERNA*)::GetProcAddress(hist,"DatiProvino"))
			esito = (pFunc)(m_pTabelle, pFieldNames, pFieldValues, bPrimoProvino, m_nContaProvini, m_pTabelle->m_pSerieProviniSet->m_Certificato);
	}	
	
	m_pTabelle->m_pSerieProviniSet->MoveNext();
  if( m_pTabelle->m_pSerieProviniSet->IsEOF())
	  return FALSE;

  return TRUE;
}




////////////////////////////////////////////////////////////////////////////
// Eroga tutti i servizi associati alla serie puntata dal recordset ricevuto
// utilizzando le info sul certificato puntato dal relativo recordset
 
void CVerbaliView::ErogaServiziSerie(CSerieSet* pSerieSet)
{
	//--------------- Apertura dei recordset complementari -----------------//
	CWinSigmaApp*					pApp					= (CWinSigmaApp*)AfxGetApp();
	CCategorieServiziSet* pCatServSet		= new CCategorieServiziSet(&pApp->m_db);
	CServiziErogatiSet*		pServErogSet	= new CServiziErogatiSet(&pApp->m_db);
	CVerbaliSet*					pVerbSet			= new CVerbaliSet(&pApp->m_db);

	// Reperimento di tutti i servizi relativi ai listini associati al verbale
	pVerbSet->m_strFilter.Format("Codice = %d", pSerieSet->m_Verbale);
	pVerbSet->Open();
	CString strProve = "" , queyJoin, query, queryTot, query2 = "";
	
	queyJoin = "SERVIZI_LISTINO.Categoria = CATEGORIE.Codice";
	query.Format("CATEGORIE.Listino = %d", pVerbSet->m_ListinoGenerale);
	if( !pVerbSet->IsFieldNull(&pVerbSet->m_ListinoParticolare) && pVerbSet->m_ListinoParticolare != 0)
	{
		query2.Format("CATEGORIE.Listino = %d", pVerbSet->m_ListinoParticolare);
		strProve.Format(" AND ( %s OR %s )", query, query2) ;
	}
  else
    strProve.Format(" AND %s", query);
	queryTot = queyJoin + strProve;
	pCatServSet->m_strFilter = queryTot;
	pCatServSet->Open();
	

	//Carico esclusivamente l'elenco dei servizi associati al verbale 
	pServErogSet->m_strFilter.Format("Verbale = %d", pSerieSet->m_Verbale);
	pServErogSet->Open();

	byte aggiuntivoIncluso	= FALSE;
	byte emissioneInclusa		= FALSE;

	
	// Per ogni servizio associato alla serie eseguo le operazioni di emissione
	if( !pSerieSet->IsFieldNull(&pSerieSet->m_Servizio1) )
	{
		SINCRONIZE(pCatServSet, pSerieSet->m_Servizio1); 
		ErogaServizio(pSerieSet, pCatServSet, pServErogSet);
		if( !pCatServSet->IsFieldNull(&pCatServSet->m_Aggiuntivo) 
			&& ((pCatServSet->m_Aggiuntivo == 2) || (pCatServSet->m_Aggiuntivo == 1) ) )
			aggiuntivoIncluso = TRUE;
		if(!pCatServSet->IsFieldNull(&pCatServSet->m_Emissione) && pCatServSet->m_Emissione == INCLUDE_EMISSIONE)
			emissioneInclusa = TRUE;
	}
	if( !pSerieSet->IsFieldNull(&pSerieSet->m_Servizio2) )
	{
		SINCRONIZE(pCatServSet, pSerieSet->m_Servizio2); 
		ErogaServizio(pSerieSet, pCatServSet, pServErogSet);
		if(!pCatServSet->IsFieldNull(&pCatServSet->m_Aggiuntivo) 
			&& ((pCatServSet->m_Aggiuntivo == 2) || (pCatServSet->m_Aggiuntivo == 1) ) )
			aggiuntivoIncluso = TRUE;
		if(!pCatServSet->IsFieldNull(&pCatServSet->m_Emissione) && pCatServSet->m_Emissione == INCLUDE_EMISSIONE)
			emissioneInclusa = TRUE;
	}
	if( !pSerieSet->IsFieldNull(&pSerieSet->m_Servizio3) )
	{
		SINCRONIZE(pCatServSet, pSerieSet->m_Servizio3); 
		ErogaServizio(pSerieSet, pCatServSet, pServErogSet);
		if(!pCatServSet->IsFieldNull(&pCatServSet->m_Aggiuntivo) 
			&& ((pCatServSet->m_Aggiuntivo == 2) || (pCatServSet->m_Aggiuntivo == 1) ) )
			aggiuntivoIncluso = TRUE;
		if(!pCatServSet->IsFieldNull(&pCatServSet->m_Emissione) && pCatServSet->m_Emissione == INCLUDE_EMISSIONE)
			emissioneInclusa = TRUE;
	}
	if( !pSerieSet->IsFieldNull(&pSerieSet->m_Servizio4) )
	{
		SINCRONIZE(pCatServSet, pSerieSet->m_Servizio4); 
		ErogaServizio(pSerieSet, pCatServSet, pServErogSet);
		if(!pCatServSet->IsFieldNull(&pCatServSet->m_Aggiuntivo) 
			&& ((pCatServSet->m_Aggiuntivo == 2) || (pCatServSet->m_Aggiuntivo == 1) ) )
			aggiuntivoIncluso = TRUE;
		if(!pCatServSet->IsFieldNull(&pCatServSet->m_Emissione) && pCatServSet->m_Emissione == INCLUDE_EMISSIONE)
			emissioneInclusa = TRUE;
	}
	if( !pSerieSet->IsFieldNull(&pSerieSet->m_Servizio5) )
	{
		SINCRONIZE(pCatServSet, pSerieSet->m_Servizio5); 
		ErogaServizio(pSerieSet, pCatServSet, pServErogSet);
		if(!pCatServSet->IsFieldNull(&pCatServSet->m_Aggiuntivo) 
			&& ((pCatServSet->m_Aggiuntivo == 2) || (pCatServSet->m_Aggiuntivo == 1) ) )
			aggiuntivoIncluso = TRUE;
		if(!pCatServSet->IsFieldNull(&pCatServSet->m_Emissione) && pCatServSet->m_Emissione == INCLUDE_EMISSIONE)
			emissioneInclusa = TRUE;
	}
	if( !pSerieSet->IsFieldNull(&pSerieSet->m_Servizio6) )
	{
		SINCRONIZE(pCatServSet, pSerieSet->m_Servizio6); 
		ErogaServizio(pSerieSet, pCatServSet, pServErogSet);
		if(!pCatServSet->IsFieldNull(&pCatServSet->m_Aggiuntivo) 
			&& ((pCatServSet->m_Aggiuntivo == 2) || (pCatServSet->m_Aggiuntivo == 1) ) )
			aggiuntivoIncluso = TRUE;
		if(!pCatServSet->IsFieldNull(&pCatServSet->m_Emissione) && pCatServSet->m_Emissione == INCLUDE_EMISSIONE)
			emissioneInclusa = TRUE;
	}
	if( !aggiuntivoIncluso
		&& !pSerieSet->IsFieldNull(&pSerieSet->m_ServAggiunto) 
		&& pSerieSet->m_ServAggiunto!= 0 )
	{
		SINCRONIZE(pCatServSet, pSerieSet->m_ServAggiunto); 
		ErogaServizio( pSerieSet, pCatServSet, pServErogSet);
		if(!pCatServSet->IsFieldNull(&pCatServSet->m_Emissione) && pCatServSet->m_Emissione == INCLUDE_EMISSIONE)
			emissioneInclusa = TRUE;
	}

	// Se la serie è la prima di un certificato e non è stato incluso in alcun servizio
	// erogo il servizio di emissione certificato
	if( !emissioneInclusa && pSerieSet->m_NuovoCertificato  )
	{
		for(SET_START(pCatServSet); !pCatServSet->IsEOF(); pCatServSet->MoveNext() )
			if ( pCatServSet->m_Emissione == EMISSIONE )
				break;
		if( pCatServSet->IsEOF() )
			AfxMessageBox("Attenzione! \n Servizio di emissione non correttamente configurato.");
		else
			ErogaServizio( pSerieSet, pCatServSet, pServErogSet);
	}

	pVerbSet->Close();
	pCatServSet->Close();
	pServErogSet->Close();
	delete pVerbSet;
	delete pCatServSet;
	delete pServErogSet;
}


////////////////////////////////////////////////////////////////////////////////
// Riceve un codice di un servizio di listino e 3 recordset dei quali:
// pSerieSet:			è sincronizzato con la serie di cui si stanno erogando i servizi
// pServListSet:	è sincronizzato con il servizio di listino da erogare
// CServErogSet:	è stato caricato con i servizi già erogati per il verbale a cui 
//								afferisce il certificato
// La funzione aggiorna la situazione dei servizi erogati e restituisce corrispondente 
// recordset allineato con il database.

void CVerbaliView::ErogaServizio(CSerieSet* pSerieSet, CCategorieServiziSet* pServListSet, 
																 CServiziErogatiSet* pServErogSet)
{
	long cod = pServListSet->m_Codice;

  //-- verifico la presenza di un servizio analogo a quello da erogare non fatturato --//
	for( SET_START(pServErogSet); !pServErogSet->IsEOF(); pServErogSet->MoveNext() )
	{
		if(pServErogSet->m_CodiceServizio == cod && 
			(pServErogSet->IsFieldNull(&pServErogSet->m_Fattura) 
			 ||	pServErogSet->m_Fattura==0 ) )
			break;
	}
			
	if(!pServErogSet->IsEOF() )//Se l'ho trovato, devo incrementarne la quantità, ...
	{
		CString temp = pServListSet->m_ID;
		long temp2 = pSerieSet->m_Codice;
		pServErogSet->Edit();
		if( pServListSet->m_PerSerie == PER_SERIE || pServListSet->m_Emissione)
			pServErogSet->m_Quantita ++;
		else
			pServErogSet->m_Quantita += pSerieSet->m_NumeroProvini;
	}
	else //... altrimenti devo aggiungere un nuovo record
	{
		pServErogSet->AddNew();
		pServErogSet->m_CodiceServizio	= pServListSet->m_Codice;
		pServErogSet->m_Descrizione			= pServListSet->m_Descrizione;
    pServErogSet->m_Nome            = pServListSet->m_Nome;
		pServErogSet->m_ID_Listino			= pServListSet->m_ID;
		pServErogSet->m_Prezzo					= pServListSet->m_Prezzo;
		pServErogSet->m_Sconto					= 0;
		pServErogSet->m_Verbale					= pSerieSet->m_Verbale;
		pServErogSet->m_Serie						= pSerieSet->m_Codice;
    pServErogSet->m_Fattura         = 0;

		CString temp = pServListSet->m_ID;
		long temp2 = pSerieSet->m_Codice;
		if( pServListSet->m_PerSerie  == 1 || pServListSet->m_Emissione)
			pServErogSet->m_Quantita	= 1;
		else 
			pServErogSet->m_Quantita	= pSerieSet->m_NumeroProvini;
	}

	pServErogSet->Update();
	pServErogSet->Requery();
}


void CVerbaliView::OnCheckLungaScadenza() 
{
  UpdateData();	
}

void CVerbaliView::OnButtonAutoMateriale() 
{
  UpdateData();
	SetProveMateriale(FALSE, TRUE);
  UpdateData(FALSE);
}

void CVerbaliView::OnButtonAutoProve() 
{
  UpdateData();
  SetProveMateriale(TRUE, FALSE);
  UpdateData(FALSE);
}


void CVerbaliView::OnChiudiVerbale() 
{
  CString str;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CTime data = CTime::GetCurrentTime();
  
  if(m_pVerbaliSet->IsBOF() || m_pVerbaliSet->IsEOF())
	{
	  MessageBeep(-1);
    return;
	}
  str.Format("Chiudere il verbale %d/%d del %s?", m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale, m_pVerbaliSet->m_DataAccettazione.Format("%d/%m/%Y"));
	switch(AfxMessageBox(str, MB_YESNO))
  {
  case IDYES:
    if(m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_NumeroFattura) || !m_pVerbaliSet->m_NumeroFattura)
    {
      str.Format("Il verbale %d/%d non è ancora stato fatturato. Proseguire con la chiusura?", m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale);
    	if(AfxMessageBox(str, MB_YESNO) == IDNO)
        return;
    }
    try
    {
      SetCursor(LoadCursor(NULL, IDC_WAIT));
      // Salvo i dati
      pApp->BeginTrans();
      pApp->LockTable(VERBALI);
    	m_pVerbaliSet->Edit();
      // Scrivo la data di chiusura
      m_pVerbaliSet->m_DataChiusura = data;
      m_pVerbaliSet->Update();
      // Sblocco la tabella
      pApp->UnlockTables(); 
      // Committo la transazione
      pApp->CommitTrans();        
      m_pVerbaliSet->Requery();
      pApp->ReloadTree(TREELABEL_VERBALIPRECEDENTI, -1);
      pApp->ReloadTree(TREELABEL_VERBALIULTIMOMESE, -1);
    }
    catch(CDBException* e)
    {
    	pApp->Rollback();
      pApp->UnlockTables();
    	AfxMessageBox(e->m_strError);
      return;
    }
    break;
  case IDNO:
    break;
  }
}

void CVerbaliView::OnMettiInFatturazione() 
{
  CString str;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  long lCodiceVerb, lCodiceAzienda;
  BOOL bServErogati = FALSE;
  CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  
	if( MODE_VIEW != pApp->GetViewMode())
		return;

	// Verifica che il pulsante sia abilitato
	if( MODE_EDIT == pApp->GetViewMode())
		return;
  
  if(m_pVerbaliSet->IsBOF() || m_pVerbaliSet->IsEOF())
	{
	  MessageBeep(-1);
    return;
	}
  if(!m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_NumeroFattura))
  {
    if(m_pVerbaliSet->m_NumeroFattura > 0)
      AfxMessageBox("Il verbale selezionato è già stato fatturato.");
    else if(m_pVerbaliSet->m_NumeroFattura == 0 || !m_pVerbaliSet->m_LungaScadenza)
      AfxMessageBox("Il verbale selezionato è già in fatturazione.");
    return;
  }
  if(m_pVerbaliSet->m_InFatturazione == VERB_PROFORMA)
    bServErogati = TRUE;

	// Verifico che il verbale non sia in elaborazione da parte di altri utenti,
	// in tal caso lo blocco
	if(!pApp->SetVerbaleInUso(m_pVerbaliSet->m_Codice))
		return;
	
  lCodiceVerb = m_pVerbaliSet->m_Codice;
  lCodiceAzienda = m_pVerbaliSet->m_CodiceAzFattura;
#ifdef WINSIGMA2
  str.Format("Mettere in fatturazione il verbale A%d del %s?", m_pVerbaliSet->m_ProgressivoTotale, m_pVerbaliSet->m_DataAccettazione.Format("%d/%m/%Y"));
#else
  str.Format("Mettere in fatturazione il verbale %d/%d del %s?", m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale, m_pVerbaliSet->m_DataAccettazione.Format("%d/%m/%Y"));
#endif
	switch(AfxMessageBox(str, MB_YESNO))
  {
  case IDYES:
    SetCursor(LoadCursor(NULL, IDC_WAIT));
      try
      {
        // Salvo i dati
        pApp->BeginTrans();
        pApp->LockTable(VERBALI);
				
				/********************************************************************/
				/**********************Modifica provvisoria (Andrea)*****************/
				/********************************************************************/
				long codSel = m_pVerbaliSet->m_Codice;
				m_pVerbaliSet->Requery();
				SINCRONIZE(m_pVerbaliSet, codSel);
				/********************************************************************/
				/********************************************************************/
				
    	  m_pVerbaliSet->Edit();
        // Scrivo la data di chiusura
        m_pVerbaliSet->m_NumeroFattura = 0;
        m_pVerbaliSet->m_InFatturazione = 0;
        m_pVerbaliSet->Update();
        // Sblocco la tabella
        pApp->UnlockTables(); 
        // Committo la transazione
        pApp->CommitTrans();        
        m_pVerbaliSet->Requery();
      }
    	catch(CDBException* e)
    	{
    		pApp->Rollback();
        pApp->UnlockTables();
    		AfxMessageBox(e->m_strError);
				// Libero il blocco del verbale
				pApp->SetVerbaleInUso(m_pVerbaliSet->m_Codice, TRUE);
        return;
    	}
      pApp->SetVerbaleInUso(lCodiceVerb, TRUE);
      // Erogo i servizi se non sono stati erogati
      m_pSerieSet->m_strFilter.Format("Verbale = %d", lCodiceVerb);
      m_pSerieSet->Requery();
      if(!bServErogati)
      {
        for(SET_START(m_pSerieSet); !m_pSerieSet->IsEOF(); m_pSerieSet->MoveNext())
          ErogaServiziSerie(m_pSerieSet);
      }
      pApp->ReloadTree(TREELABEL_FATTUREDAEMETTERE, lCodiceAzienda);
      if(pDoc->m_nSelectedTreeVerbali == TREEITEM_VERBFATTPROFORMA)
        pApp->ReloadTree(TREELABEL_VERBALIFATTPROFORMA, lCodiceVerb);
      if(pDoc->m_nSelectedTreeVerbali == TREEITEM_VERBALIPRECEDENTI)
        pApp->ReloadTree(TREELABEL_VERBALIPRECEDENTI, lCodiceVerb);
      if(pDoc->m_nSelectedTreeVerbali == TREEITEM_VERBALIULTIMOMESE)
        pApp->ReloadTree(TREELABEL_VERBALIULTIMOMESE, lCodiceVerb);
      SINCRONIZE(m_pVerbaliSet, lCodiceVerb);
      LoadCurRecord(TRUE);
      break;
  case IDNO:
    break;
  }
	
	// Libero il blocco del verbale
	pApp->SetVerbaleInUso(lCodiceVerb, TRUE);
	
}

BOOL CVerbaliView::CheckEditableSeries(BOOL bVerifyAll)
{
  BOOL bEdit = TRUE;

  if(m_pVerbaliSet->IsBOF() || m_pVerbaliSet->IsEOF())
    return FALSE;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  m_pGlobalSerieSet->m_strFilter.Format("Verbale = %d", m_pVerbaliSet->m_Codice);
  m_pGlobalSerieSet->Requery();
  for(SET_START(m_pGlobalSerieSet); !m_pGlobalSerieSet->IsEOF(); m_pGlobalSerieSet->MoveNext())
  {
    bEdit = TRUE;
    if(!m_pGlobalSerieSet->IsFieldNull(&m_pGlobalSerieSet->m_Certificato) && m_pGlobalSerieSet->m_Certificato != 0)
    {
      bEdit = FALSE;
      if(!bVerifyAll)
        break;
    }
  }
  return bEdit;
}

void CVerbaliView::OnAnnullaVerbale() 
{
  CString str;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  
  if(m_pVerbaliSet->IsBOF() || m_pVerbaliSet->IsEOF())
	{
	  MessageBeep(-1);
    return;
	}
  if(!m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_NumeroFattura))
  {
    if(m_pVerbaliSet->m_NumeroFattura)
    {
      AfxMessageBox("Il verbale è già stato fatturato e non è possibile annullarlo");
      return;
    }
    else
    {
      if(AfxMessageBox("Il verbale risulta in fatturazione. Proseguire?", MB_YESNO) == IDNO)
        return;      
    }      
  }
  long lCodice = m_pVerbaliSet->m_Codice;
  long lCodAzienda = m_pVerbaliSet->m_CodiceAzFattura;
  CServiziErogatiSet* pServiziErogati = new CServiziErogatiSet(&pApp->m_db);
  str.Format("Annullare il verbale %d/%d del %s?", m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale, m_pVerbaliSet->m_DataAccettazione.Format("%d/%m/%Y"));
	switch(AfxMessageBox(str, MB_YESNO))
  {
  case IDYES:
    // Blocco il verbale
    if(!pApp->SetVerbaleInUso(lCodice))
      return;
    m_pVerbaliSet->Requery();
    SetCursor(LoadCursor(NULL, IDC_WAIT));
    SINCRONIZE(m_pVerbaliSet, lCodice);
    m_pVerbaliSet->Edit();
    m_pVerbaliSet->m_Annullato = 1;
    m_pVerbaliSet->m_DataChiusura = CTime::GetCurrentTime();
    // Lo tolgo dalla fatturazione
    m_pVerbaliSet->SetFieldNull(&m_pVerbaliSet->m_NumeroFattura);
    m_pVerbaliSet->SetFieldNull(&m_pVerbaliSet->m_InFatturazione);
    m_pVerbaliSet->Update();
    m_pVerbaliSet->Requery();
    // Cancello i servizi erogati per questo verbale
    pServiziErogati->m_strFilter.Format("Verbale = %ld", lCodice);
    pServiziErogati->Open();
    for(SET_START(pServiziErogati); !pServiziErogati->IsEOF(); pServiziErogati->MoveNext())
      pServiziErogati->Delete();
    pServiziErogati->Close();
    // Ricarico gli alberi
    pApp->ReloadTree(TREELABEL_FATTUREDAEMETTERE, lCodAzienda);
    pApp->ReloadTree(TREELABEL_VERBALIPRECEDENTI, -1);
    pApp->ReloadTree(TREELABEL_VERBALIULTIMOMESE, -1);
    pApp->ReloadTree(TREELABEL_VERBALIFATTPROFORMA, -1);
    // Sblocco il verbale
    pApp->SetVerbaleInUso(lCodice, TRUE);
    break;
  case IDNO:
    break;
  }
  
}


void CVerbaliView::StampaCertificati(BOOL bHeader)
{
		//--------------- Istanze dei recordset utilizzati-----------------//

	CWinSigmaApp* pApp	= (CWinSigmaApp*)AfxGetApp();
	m_pTabelle					= new CAllTables(&pApp->m_db);
	CCertificatiVerbaliSet* pCertVerbSet		= new CCertificatiVerbaliSet(&pApp->m_db);
	CCertificatiSet*				pCertificatiSet	= new CCertificatiSet(&pApp->m_db);

		//------- Caricamento dei certificati non ancora stampati --//
	pCertificatiSet->m_strFilter.Format("DataStampa IS NULL");
	pCertificatiSet->Open();
	pCertVerbSet->m_strSort = "CERTIFICATI.NumeroCertificato ASC";
	pCertVerbSet->m_strFilter.Format("VERBALI.Codice = CERTIFICATI.Verbale AND DataStampa IS NULL ");
	pCertVerbSet->Open();

	// Apertura del recordset per poter eseguire le requery nel ciclo for della stampa
	//m_pTabelle->m_pSerieProviniSet->m_strSort = "SERIE.TipoCertificato, SERIE.Codice, PROVINI.Codice ASC";
	m_pTabelle->m_pSerieProviniSet->m_strFilter.Format("SERIE.Codice = PROVINI.Serie AND SERIE.Certificato = 0 ");
  m_pTabelle->m_pSerieProviniSet->m_strSort = "SERIE.TipoCertificato, SERIE.Codice, PROVINI.Codice ASC";
  m_pTabelle->m_pSerieProviniSet->Open();

  if(pApp->GetViewMode() != MODE_VIEW)
	{
	  MessageBeep(-1);
		return;
	}

	if( pCertificatiSet->IsEOF() )
	{
		pCertVerbSet->Close();
		pCertificatiSet->Close();
		
		delete m_pTabelle;
		delete pCertVerbSet;
		delete pCertificatiSet;
		AfxMessageBox("Non sono stati rilevati certificati in fase di stampa!\nSelezionare un certificato per eseguirne la ristampa.");
		return;
	}


	//----------- Apertura del dialogo di selezione --------//

	CDWordArray CertScelti;
	CStampaCertificatiDlg dlg;

	dlg.m_pCertVerbSet				= pCertVerbSet;
	dlg.m_pTipiCertificatoSet = m_pTipiCertificatoSet;
	dlg.m_pCertificatiScelti	= &CertScelti;
	dlg.m_bRistampa						= FALSE;

	if( dlg.DoModal()==IDOK && CertScelti.GetSize()>0)
	{
		CString temp, fileLayout = "";	// contenitore del nome del file di layout
		int numeroPagine = 0;
		CStringArray fieldNames, fieldValues, marchiFiles;

		SetCursor(LoadCursor(NULL, IDC_WAIT));
		for(int i=0; i<CertScelti.GetSize(); i++)
		{
			//sincronizzo il recordset con il certificato scelto
			for( SET_START(pCertVerbSet); !pCertVerbSet->IsEOF(); pCertVerbSet->MoveNext() )
				if( pCertVerbSet->m_CodiceCertificato == (long)CertScelti.GetAt(i) )
					break;

			SINCRONIZE(m_pTipiCertificatoSet, pCertVerbSet->m_TipoCertificato);
			// Individuo la dll associata per richiamare opportunamente le funzioni
			m_strDllCorrente = GetNameModuloDll(m_pTipiCertificatoSet->m_Codice);
			fileLayout = m_pTipiCertificatoSet->m_LayoutStampa;

			CPrintInterpreter prn;
			CString docname = BuildCertificateName(pCertVerbSet);
			prn.SetDocName(docname);
			if(prn.PrePrinting())
			{
				numeroPagine = LoadDatiStampa(pCertVerbSet->m_CodiceCertificato, &fieldNames, &fieldValues);	

				//Preparazione del recordset dei provini per la scanProvini
				
				//m_pTabelle->m_pSerieProviniSet->m_strSort = "SERIE.TipoCertificato, SERIE.Codice, PROVINI.Codice ASC";
				m_pTabelle->m_pSerieProviniSet->m_strFilter.Format("SERIE.Codice = PROVINI.Serie AND SERIE.Certificato = %d ", pCertVerbSet->m_CodiceCertificato);
				m_pTabelle->m_pSerieProviniSet->m_strSort = "SERIE.TipoCertificato, SERIE.Codice, PROVINI.Codice ASC";
        m_pTabelle->m_pSerieProviniSet->Requery();	
					
				m_nCodSerieStampata = 0;// serve per stampare in maniera diversa la prima riga di una serie 															
				m_nContaProvini = 0;		// serve per indicare il numero del provino alla dll
				if(numeroPagine == 1)
				{
					//--------- gestione numeri di pagina --------------------//
					fieldNames.Add("pagineTotali");
					fieldValues.Add("1");
					fieldNames.Add("paginaCorrente");
					fieldValues.Add("1");
					//--------------------------------------------------------//
				}				

				// imposta la stampa con l'header
				if(bHeader == TRUE)
				{
					prn.SetHeaderFile(pApp->GetCurrentDirectory() + "\\" + pApp->m_headerPrn);
				}
				
				prn.Print(pApp->GetCurrentDirectory() + "\\" + fileLayout, 
							&fieldNames, &fieldValues, NULL, NULL, &ScanProvini );

				// (andrea) Modifica provvisoria per saltare la stampa degli allegati
				// numeroPagine = 1;
				// --------------------------------------------------------------- //
				if(numeroPagine > 1)
				{
					int contaProvini = 1;
					byte stampaAllegati = TRUE;
					SET_START(m_pTabelle->m_pSerieProviniSet);
					typedef BOOL (PROCESTERNA)(CString*,CAllTables*,CStringArray*,CStringArray*, CStringArray*, int* );	
					HINSTANCE hist = NULL;
					PROCESTERNA* pFunc;		
					BOOL esito = 0;
					ASSERT( hist = ::LoadLibrary(m_strDllCorrente) );
					if( pFunc = (PROCESTERNA*)::GetProcAddress(hist,"StampaAllegato") )
					{
						int pagCorrente = 0;
						CString str;
						while(stampaAllegati)
						{
							fieldNames.RemoveAll();
							fieldValues.RemoveAll();
							marchiFiles.RemoveAll();
							//stampaAllegati = (pFunc)(&fileLayout,m_pTabelle,&fieldNames,&fieldValues,&contaProvini);
							SET_START(m_pTabelle->m_pSerieProviniSet);
							stampaAllegati = (pFunc)(&fileLayout,m_pTabelle,&fieldNames,&fieldValues,&marchiFiles,&pagCorrente);
							//--------- gestione numeri di pagina --------------------//
							fieldNames.Add("pagineTotali");
							str.Format("%d",numeroPagine);
							fieldValues.Add(str);
							fieldNames.Add("paginaCorrente");
							str.Format("%d",pagCorrente + 2 );
							fieldValues.Add(str);
							//--------------------------------------------------------//

							pagCorrente++;
							prn.Print(pApp->GetCurrentDirectory() + "\\" + fileLayout, 
								&fieldNames, &fieldValues, &marchiFiles, NULL, NULL);
						}
					}
				}
				fieldNames.RemoveAll();
				fieldValues.RemoveAll();

				prn.PostPrinting();

				//--- inserimento della data di stampa nella tabella certificati ---//
				SINCRONIZE(pCertificatiSet, pCertVerbSet->m_CodiceCertificato);
				pCertificatiSet->Edit();
				pCertificatiSet->m_DataStampa		= CTime::GetCurrentTime();
				pCertificatiSet->Update();
			} // if preprinting()
		} // for sui certificati scelti  
	}

	pCertVerbSet->Close();
	pCertificatiSet->Close();

	delete m_pTabelle;
	delete pCertVerbSet;
	delete pCertificatiSet;
}



void CVerbaliView::OnPrintNoComm(WPARAM wParam, LPARAM lParam)
{
  CString str;
  str.Format("Errore nella comunicazione con la stampante.\nImpossibile stampare il verbale %d/%d", wParam, lParam);
  AfxMessageBox(str);
  KillTimer(TIME_OUT_MSG_ID);
}

void CVerbaliView::OnPrintThreadOk(WPARAM wParam, LPARAM lParam)
{
  KillTimer(TIME_OUT_MSG_ID);
}

void CVerbaliView::OnTimer(UINT nIDEvent) 
{
  if(nIDEvent == TIME_OUT_MSG_ID)
  {
    AfxMessageBox("Errore nella comunicazione con la stampante");
    KillTimer(TIME_OUT_MSG_ID);
  }
	CXFormView::OnTimer(nIDEvent);
}


//////////////////////////////////////////////////////
// 
void CVerbaliView::SetProveMateriale(byte forzaProve, byte forzaMateriale)
{
	UpdateData();
	m_strMaterialeConsegnato.TrimLeft();
	m_strMaterialeConsegnato.TrimRight();
	m_strProveRichieste.TrimLeft();
	m_strProveRichieste.TrimRight();
	if( m_strProveRichieste.GetLength() > 1 && m_strMaterialeConsegnato.GetLength() > 1 
		&& !forzaProve && !forzaMateriale)
		return;
	
	CStringArray stringhe;
	CString moduloDll,materiale, prove, str;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	m_pTabelle = new CAllTables(&pApp->m_db);
	m_pTabelle->m_pTipiCertificatoSet->m_strSort = "Codice ASC";
	m_pTabelle->m_pTipiCertificatoSet->Open();
	m_pTabelle->m_pVerbaliSet->m_strFilter.Format("Codice = %d", m_pVerbaliSet->m_Codice);
	m_pTabelle->m_pVerbaliSet->Open();
	m_pTabelle->m_pSerieSet->m_strSort = "TipoCertificato, Dimensione1";
	m_pTabelle->m_pSerieSet->m_strFilter.Format("Verbale = %d", m_pVerbaliSet->m_Codice);
	m_pTabelle->m_pSerieSet->Open();
	
	int contaProve = 0, contaMat = 0;
	while( !m_pTabelle->m_pTipiCertificatoSet->IsEOF() ) 
	{
		// Chiamo la funzione solo se la serie sincronizzata appartiene al tipo di certificato 
		// associato altrimenti passo oltre, la dll scandisce il recordset serie restituendolo
		// sincronizzato con la prima serie di tipo certificato diverso, eventualmente EOF.
		if(m_pTabelle->m_pTipiCertificatoSet->m_Codice == m_pTabelle->m_pSerieSet->m_TipoCertificato)
		{
			CString str = "";
			moduloDll = GetNameModuloDll(m_pTabelle->m_pTipiCertificatoSet->m_Codice);
			typedef int (PROCESTERNA)(CStringArray*, CAllTables*, CDWordArray*);	
			HINSTANCE hist;
			PROCESTERNA* pFunc;										// Creo una variabile function del tipo precedentemente definito
			int addStringa = IDNO;
			if (hist = ::LoadLibrary(moduloDll))	// Reperimento dell'istanza del modulo cercato
					if(pFunc = (PROCESTERNA*)::GetProcAddress(hist,"LoadProveMateriale"))// Reperimento della funzione esterna
						addStringa = (pFunc)(&stringhe, m_pTabelle, &m_arySerieEliminate);
		}
		m_pTabelle->m_pTipiCertificatoSet->MoveNext();
	}
	
	
	//Sovrascrivo le stringhe solo se richesto
	UpdateData();
	
	if( stringhe.GetSize() > 0 
		&& (forzaProve || m_strProveRichieste.GetLength() < 2 ) )
		m_strProveRichieste = stringhe.GetAt(0);

	if( stringhe.GetSize() > 0 
		&& (forzaMateriale || m_strMaterialeConsegnato.GetLength() < 2) )
		m_strMaterialeConsegnato = stringhe.GetAt(1);

	UpdateData(FALSE);
	m_pTabelle->m_pSerieSet->Close();
	m_pTabelle->m_pVerbaliSet->Close();
	m_pTabelle->m_pTipiCertificatoSet->Close();
	delete m_pTabelle;
}


/////////////////////////////////////////////////////////
//Stampa di un certificato 
void CVerbaliView::StampaCertificato(CTipiCertificatoSet* pTipiCertSet, long codRif, BOOL isCodSerie, BOOL bHeader)
{
	m_pTipiCertificatoSet = pTipiCertSet;
	StampaCertificato(codRif, isCodSerie, bHeader);
}

void CVerbaliView::StampaCertificato(long codRif, BOOL isCodSerie, BOOL bHeader)
{
		//--------------- Istanze dei recordset utilizzati-----------------//
  BOOL bIsEmendamento = FALSE; 
	CWinSigmaApp* pApp	= (CWinSigmaApp*)AfxGetApp();
	m_pTabelle					= new CAllTables(&pApp->m_db);
	CCertificatiVerbaliSet* pCertVerbSet	= new CCertificatiVerbaliSet(&pApp->m_db);
	long codCertificato;

	m_pTabelle->m_pSerieProviniSet->m_strFilter.Format("SERIE.Codice = PROVINI.Serie AND SERIE.Codice = %d ", codRif);
	m_pTabelle->m_pSerieProviniSet->m_strSort = "SERIE.Codice , PROVINI.Codice";
  m_pTabelle->m_pSerieProviniSet->Open();

	if(isCodSerie)
		codCertificato = m_pTabelle->m_pSerieProviniSet->m_Certificato;
	else
		codCertificato = codRif;
		
	pCertVerbSet->m_strFilter.Format("VERBALI.Codice = CERTIFICATI.Verbale AND CERTIFICATI.Codice = %d", codCertificato);
	pCertVerbSet->Open();

  if(pApp->GetViewMode() != MODE_VIEW)
	{
	  MessageBeep(-1);
		return;
	}

	if( pCertVerbSet->IsEOF() )
	{
		pCertVerbSet->Close();
		delete pCertVerbSet;
		delete m_pTabelle;
		AfxMessageBox("Operazione non disponibile!\nNon è stato trovato il documento richiesto.");
		return;
	}


	//----------- Apertura del dialogo di selezione --------//

	CDWordArray CertScelti;
	CStampaCertificatiDlg dlg;

	dlg.m_pCertVerbSet				= pCertVerbSet;
	dlg.m_pTipiCertificatoSet = m_pTipiCertificatoSet;
	dlg.m_pCertificatiScelti	= &CertScelti;
	dlg.m_bRistampa						= TRUE;

	if(dlg.DoModal() == IDOK && CertScelti.GetSize() > 0)
	{
		BOOL stampaDuplicato = dlg.m_bDuplicato;
		CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

		CString fileLayout = "";	// contenitore del nome del file di layout
		int numeroPagine = 0;
		CStringArray fieldNames, fieldValues, marchiFiles;

		for(int i = 0; i < CertScelti.GetSize(); i++)
		{
			//sincronizzo il recordset con il certificato scelto
			for(SET_START(pCertVerbSet); !pCertVerbSet->IsEOF(); pCertVerbSet->MoveNext())
				if(pCertVerbSet->m_CodiceCertificato == (long)CertScelti.GetAt(i))
					break;

			// Settaggio della dll associata per richiamare opportunamente le funzioni
			SINCRONIZE(m_pTipiCertificatoSet, pCertVerbSet->m_TipoCertificato);
			
			fileLayout = m_pTipiCertificatoSet->m_LayoutStampa;
					
			m_strDllCorrente = GetNameModuloDll(m_pTipiCertificatoSet->m_Codice);
        
			CPrintInterpreter prn;
			CString docname = BuildCertificateName(pCertVerbSet);
			prn.SetDocName(docname);
			if(prn.PrePrinting())
			{
				numeroPagine = LoadDatiStampa(pCertVerbSet->m_CodiceCertificato, &fieldNames, &fieldValues);

				//--- Gestione del duplicato e dell'emendamento ---//
				CString str = "";
				CString strAmend = "";
				fieldNames.Add("duplicato");
				if(stampaDuplicato)					
					str.Format("DUPLICATO del %s", dlg.m_DataDuplicato.Format("%d/%m/%Y"));
 				fieldValues.Add(str);
				str.Empty();
				fieldNames.Add("emendamento");
				if(!pCertVerbSet->IsFieldNull(&pCertVerbSet->m_EmendaIl) && pCertVerbSet->m_EmendaIl != 0)
				{
					bIsEmendamento = TRUE;
					CCertificatiSet set(&pApp->m_db);
					set.m_strFilter.Format("Codice = %d", pCertVerbSet->m_EmendaIl);
					set.Open();
				// variazione dicitura emendamento 29.05.2016 s.c. 
					strAmend.Format("Emendamento che annulla e sostituisce il certificato N° %d del %s", set.m_NumeroCertificato, set.m_DataEmissione.Format("%d/%m/%Y"));
					set.Close();
				}
				if(!pCertVerbSet->IsFieldNull(&pCertVerbSet->m_EmendatoDa) && pCertVerbSet->m_EmendatoDa != 0)
				{
					bIsEmendamento = TRUE;
					CCertificatiSet set(&pApp->m_db);
					set.m_strFilter.Format("Codice = %d", pCertVerbSet->m_EmendatoDa);
					set.Open();
					strAmend.Format("Emendato dal certificato N° %d del %s", set.m_NumeroCertificato, set.m_DataEmissione.Format("%d/%m/%Y"));
					set.Close();
				}
 				fieldValues.Add(strAmend);
        
				CString debug = pCertVerbSet->m_Cantiere;

				//Preparazione del recordset dei provini 
				//m_pTabelle->m_pSerieProviniSet->m_strSort = "SERIE.Codice, PROVINI.Codice ASC";
				m_pTabelle->m_pSerieProviniSet->m_strFilter.Format("SERIE.Codice = PROVINI.Serie AND SERIE.Certificato = %d ", pCertVerbSet->m_CodiceCertificato);
				m_pTabelle->m_pSerieProviniSet->m_strSort = "SERIE.Codice, PROVINI.Codice ASC";
				m_pTabelle->m_pSerieProviniSet->Requery();
				m_nCodSerieStampata = 0;//serve per stampare la prima riga di una serie in maniera diversa 
				m_nContaProvini = 0;		// serve per indicare il numero del provino alla dll
				if(numeroPagine == 1)
				{
					//--------- gestione numeri di pagina --------------------//
					fieldNames.Add("pagineTotali");
					fieldValues.Add("1");
					fieldNames.Add("paginaCorrente");
					fieldValues.Add("1");
					//--------------------------------------------------------//
				}
				
				// imposta la stampa con l'header
				if(bHeader == TRUE)
				{
					prn.SetHeaderFile(pApp->GetCurrentDirectory() + "\\" + pApp->m_headerPrn);
				}

				prn.Print(pApp->GetCurrentDirectory() + "\\" + fileLayout, 
							&fieldNames, &fieldValues, NULL, NULL, &ScanProvini);
					// (andrea) Modifica provvisoria per saltare la stampa degli allegati
				// numeroPagine = 1;
				// --------------------------------------------------------------- //
				if(numeroPagine > 1)
				{
					int contaProvini = 1;
					byte stampaAllegati = TRUE;
					SET_START(m_pTabelle->m_pSerieProviniSet);
					typedef BOOL (PROCESTERNA)(CString*,CAllTables*,CStringArray*,CStringArray*,CStringArray*, int*, BOOL*, CTime* );	
					HINSTANCE hist = NULL;
					PROCESTERNA* pFunc;		
					BOOL esito = 0;
					ASSERT(hist = ::LoadLibrary(m_strDllCorrente));
					if(pFunc = (PROCESTERNA*)::GetProcAddress(hist,"StampaAllegato"))
					{
						int pagCorrente = 0;
						CString str;
						while(stampaAllegati)
						{
							fieldNames.RemoveAll();
							fieldValues.RemoveAll();
							marchiFiles.RemoveAll();
							//stampaAllegati = (pFunc)(&fileLayout,m_pTabelle,&fieldNames,&fieldValues,&contaProvini);
							SET_START(m_pTabelle->m_pSerieProviniSet);
							stampaAllegati = (pFunc)(&fileLayout, m_pTabelle, &fieldNames, &fieldValues, &marchiFiles, &pagCorrente,&stampaDuplicato, &dlg.m_DataDuplicato);
							//--------- gestione numeri di pagina --------------------//
							fieldNames.Add("pagineTotali");
							str.Format("%d",numeroPagine);
							fieldValues.Add(str);
							fieldNames.Add("paginaCorrente");
							str.Format("%d",pagCorrente + 2 );
							fieldValues.Add(str);

							if(bIsEmendamento == TRUE) // 4.12.2017 s.c.
							{
								fieldNames.Add("emendamento");
								fieldValues.Add(strAmend);
							}
							//--------------------------------------------------------//	
							pagCorrente++;
							prn.Print(pApp->GetCurrentDirectory() + "\\" + fileLayout, 
								&fieldNames, &fieldValues, &marchiFiles, NULL, NULL);
						}
					}					
				}
				fieldNames.RemoveAll();
				fieldValues.RemoveAll();
				prn.PostPrinting();
			} // endif preprinting()
		} // for sui certificati scelti
	}

	pCertVerbSet->Close();

	delete m_pTabelle;
  delete pCertVerbSet;
}

// Effettua la ricerca dei verbali secondo la chiave impostata
void CVerbaliView::FindVerbali(int searchParam)
{
  CFindVerbaliDlg dlg;
  CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  
  switch(searchParam)
  {
  case SEARCH_CANTIERE:
    dlg.m_strTitolo = "Ricerca per cantiere";
    break;
  case SEARCH_DIRLAVORI:
    dlg.m_strTitolo = "Ricerca per direttore lavori";
    break;
  case SEARCH_CERTIFICATO:
    dlg.m_strTitolo = "Ricerca per intestatario certificati";
    break;
  case SEARCH_FATTURA:
    dlg.m_strTitolo = "Ricerca per intestatario fattura";
    break;
  case SEARCH_IMPRESA:
    dlg.m_strTitolo = "Ricerca per impresa";
    break;
	case SEARCH_STRUTTURA:
    dlg.m_strTitolo = "Ricerca per struttura di prelievo";
    break;
  case SEARCH_SIGLA:
    dlg.m_strTitolo = "Ricerca per sigla serie inserite";
    break;
  }
  dlg.m_nChiaveRicerca = searchParam;
  dlg.m_pDoc = pDoc;
  dlg.m_nAnnoAccettazione = 0;
  dlg.m_bChiusi = FALSE;
  if(dlg.DoModal() == IDOK)
  {
    if(dlg.m_nCodiceVerbale > 0)
    {
      OnUpdate(NULL, 0, NULL);
      switch(pDoc->m_nSelectedTreeVerbali)
      {
      case TREEITEM_VERBALIPRECEDENTI:
        m_pVerbaliSet = pDoc->m_pVerbaliPrecedentiSet;
        break;
      case TREEITEM_VERBALIULTIMOMESE:
      default:
        m_pVerbaliSet = pDoc->m_pVerbaliUltimoMeseSet;
        break;
      }
/*
      for(SET_START(m_pVerbaliSet); !m_pVerbaliSet->IsEOF(); m_pVerbaliSet->MoveNext())
      {
        if(m_pVerbaliSet->m_Codice == dlg.m_nCodiceVerbale)
          break;
      }
      if(m_pVerbaliSet->IsEOF())
      {
        LoadCurRecord(FALSE);
        return;
      }
*/
      SINCRONIZE(m_pVerbaliSet, dlg.m_nCodiceVerbale);
      LoadSeries(m_pVerbaliSet->m_Codice);
      CWinSigmaApp* pApp = ((CWinSigmaApp*)AfxGetApp());
      if(pDoc->m_nSelectedTreeVerbali == TREEITEM_VERBALIPRECEDENTI)
        pApp->ReloadTree(TREELABEL_VERBALIPRECEDENTI, dlg.m_nCodiceVerbale);
      else
        pApp->ReloadTree(TREELABEL_VERBALIULTIMOMESE, dlg.m_nCodiceVerbale);
      LoadCurRecord(TRUE);
    }
  }
  UpdateData(FALSE);
}

void CVerbaliView::OnFindVerbCantiere() 
{
	FindVerbali(SEARCH_CANTIERE);	
}

void CVerbaliView::OnFindVerbCertificato() 
{
	FindVerbali(SEARCH_CERTIFICATO);	
}

void CVerbaliView::OnFindVerbDirLavori() 
{
	FindVerbali(SEARCH_DIRLAVORI);	
}

void CVerbaliView::OnFindVerbFattura() 
{
	FindVerbali(SEARCH_FATTURA);	
}

void CVerbaliView::OnFindVerbImpresa() 
{
	FindVerbali(SEARCH_IMPRESA);	
}

void CVerbaliView::OnFindVerbStruttura() 
{
	FindVerbali(SEARCH_STRUTTURA);	
}

void CVerbaliView::OnFindVerbSigla() 
{
	FindVerbali(SEARCH_SIGLA);	
}

void CVerbaliView::ModificaCertificato(long codSerie)
{
	CString msg,strDatiOccupante;
	
		//--------------- Istanze dei recordset utilizzati-----------------//

	CWinSigmaApp* pApp	= (CWinSigmaApp*)AfxGetApp();

	
	if( MODE_VIEW != pApp->GetViewMode())
		return;

	CCertificatiSet CertSet(&pApp->m_db);
	CSerieSet SerieSet(&pApp->m_db);
	CCertificatiVerbaliSet CertVerbSet(&pApp->m_db);
	CString str;

	SerieSet.m_strFilter.Format("Codice = %d", codSerie);
	SerieSet.Open();
	CertVerbSet.m_strFilter.Format("VERBALI.Codice = CERTIFICATI.Verbale AND CERTIFICATI.Codice = %d", SerieSet.m_Certificato);
	CertVerbSet.Open();
	CertSet.m_strFilter.Format("Codice = %d", SerieSet.m_Certificato);
	CertSet.Open();

	// Blocco della certificazione
	if(!pApp->DisabilitaCertificazione(&strDatiOccupante))
	{
		CertSet.Close();
		msg = STR_BLOCCO_CERTIFICAZIONE(strDatiOccupante);
		msg = msg + STR_ISTRUZIONI_RIMOZIONE;
		AfxMessageBox(msg);
		return;
	}

  if(pApp->GetViewMode() != MODE_VIEW)
	{
	  MessageBeep(-1);
		return;
	}

	if( CertVerbSet.IsEOF() )
	{
		CertVerbSet.Close();
		AfxMessageBox("Operazione non disponibile!\nNon è stato trovato il documento richiesto.");
		return;
	}
	else
	{
		CModificaCertificatoDlg dlg;
		dlg.m_pCertVerbSet	= &CertVerbSet;
		if( IDOK == dlg.DoModal() )
		{
			if(dlg.m_bEmenda)
			{
				CreaEmendamento(CertSet.m_Codice);
				// Riallineamento del rercordset con il contenuto del database.
				long tempSel = m_pSerieSet->m_Codice;
				m_pSerieSet->Requery();
				SINCRONIZE(m_pSerieSet, tempSel);
			}
			else
			{
				CertSet.Edit();
				CertSet.m_DataEmissione			= dlg.m_DataEmissione;
				CertSet.m_NumeroCertificato = dlg.m_nNumDocumento;
				if(dlg.m_bAbilitaCalcolo)
					CertSet.SetFieldNull(&CertSet.m_NumeroPagine, TRUE);
				else
					CertSet.m_NumeroPagine = dlg.m_nNumPagine;
				CertSet.Update();
			}
			LoadSeries(m_pVerbaliSet->m_Codice);
		}
	}
	pApp->DisabilitaCertificazione(&strDatiOccupante, FALSE);
}

void CVerbaliView::OnButtonModificaCertificato() 
{
	int n;
  POSITION pos;
  
	UpdateData();
  pos = m_ListSerie.GetFirstSelectedItemPosition();
	if((n = m_ListSerie.GetNextSelectedItem(pos)) < 0)
  {
    AfxMessageBox("Selezionare un dato valido!");
	  return;
  }
  ModificaCertificato(m_ListSerie.GetItemData(n));
	UpdateData(FALSE);
}




// Aggiorna i dati presenti nello spazio di navigazione dei verbali
void CVerbaliView::AggiornaAlbero() 
{
	CWinSigmaApp* pApp	= (CWinSigmaApp*)AfxGetApp();
	if( MODE_VIEW != pApp->GetViewMode())
		return;
	long nVerbale = m_pVerbaliSet->m_Codice;
  pApp->ReloadTree(TREELABEL_VERBALIFATTPROFORMA, nVerbale);
	pApp->ReloadTree(TREELABEL_VERBALIPRECEDENTI, nVerbale);
	pApp->ReloadTree(TREELABEL_VERBALIULTIMOMESE, nVerbale);
	LoadSeries(nVerbale);
}

// risponde alla pressione della voce presente nella barra dei menù
void CVerbaliView::OnAggiornaAlbero() 
{
	AggiornaAlbero();
}

// risponde alla pressione del pulsante presente nella barra dei pulsanti
void CVerbaliView::OnButtonAggiorna() 
{
	AggiornaAlbero();	
}

// Ripristina l'icona corrispondente allo stato dei dati della serie
void CVerbaliView::RiscriviDatiSerie( int indexSerie)
{	
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	long codSerie = m_ListSerie.GetItemData(indexSerie);
  m_pGlobalSerieSet->m_strFilter.Format("Codice = %ld", codSerie);
  m_pGlobalSerieSet->Requery();
  CProviniSet proviniSet(&pApp->m_db);
	proviniSet.m_strFilter.Format("Serie = %d", m_pGlobalSerieSet->m_Codice);
	proviniSet.Open();
	BOOL datiInseriti = TRUE;
	int numDati = 0;
	while(!proviniSet.IsEOF())
	{
		if(proviniSet.IsFieldNull(&proviniSet.m_DataInserimento) )
			datiInseriti = FALSE;
		else
			numDati++;
		proviniSet.MoveNext();
	}
	proviniSet.Close();
	
	int nIcon;
	if(m_pGlobalSerieSet->m_Certificato != 0)
		return;
  else if(datiInseriti)
		nIcon = 2;
	else if(numDati>0)
		nIcon = 1;
	else
		nIcon = 0;

	CString strContaSerie, strCertificato, strTipo, strStruttura, strServizi, strCampioni, strPrezzo;
	char pTemp[100];

	m_ListSerie.GetItemText(indexSerie, 0, pTemp, 100);
	strContaSerie = pTemp;
	m_ListSerie.GetItemText(indexSerie, 1, pTemp, 100);
	strCertificato = pTemp;
	m_ListSerie.GetItemText(indexSerie, 2, pTemp, 100);
	strTipo = pTemp;
	m_ListSerie.GetItemText(indexSerie, 3, pTemp, 100);
	strStruttura = pTemp;
	m_ListSerie.GetItemText(indexSerie, 4, pTemp, 100);
	strServizi = pTemp;
	m_ListSerie.GetItemText(indexSerie, 5, pTemp, 100);
	strCampioni = pTemp;
	m_ListSerie.GetItemText(indexSerie, 6, pTemp, 100);
	strPrezzo = pTemp;
	
	m_ListSerie.DeleteItem(indexSerie);

	m_ListSerie.InsertItem(indexSerie, strContaSerie, nIcon);
	m_ListSerie.SetItemData(indexSerie, codSerie);
	m_ListSerie.SetItemText(indexSerie, 1, strCertificato);
  m_ListSerie.SetItemText(indexSerie, 2, strTipo);
  m_ListSerie.SetItemText(indexSerie, 3, strStruttura);
  m_ListSerie.SetItemText(indexSerie, 4, strServizi);
  m_ListSerie.SetItemText(indexSerie, 5, strCampioni);
  m_ListSerie.SetItemText(indexSerie, 6, strPrezzo);
}

void CVerbaliView::OnSbloccoVerbale() 
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	if(m_pVerbaliSet->IsBOF() || m_pVerbaliSet->IsEOF())
	{
	  MessageBeep(-1);
		return;
	}

  if( pApp->GetViewMode() == MODE_EDIT_PROVINI )
	{
	  MessageBeep(-1);
		return;
	}

	if(m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_InUso) )
	{
		AfxMessageBox("Il verbale non risulta bloccato.");
		return;
	}
	
	CString msg = m_pVerbaliSet->m_InUso;
	msg.Format("Operazione di rimozione forzata del blocco sul verbale: %d/%d.\n\n",m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale);
	msg += "Attenzione, lavorare contemporaneamente sullo stesso documento può essere causa di inconsistenze nella memorizzazione dei dati;";
	msg += " il blocco di un documento serve a scongiurare questa eventualità.\n\n";
	msg += "PROCEDERE CON LO SBLOCCO SOLO DOPO AVERE VERIFICATO CHE NESSUN ALTRO UTENTE STIA LAVORANDO SU QUESTO DOCUMENTO\n";
	msg += "\nConfermi l'operazione di sblocco del verbale?";
	if(IDYES == AfxMessageBox(msg, MB_YESNO) )
		pApp->SetVerbaleInUso(m_pVerbaliSet->m_Codice, TRUE);
}


void CVerbaliView::OnSbloccacertificazione() 
{
	CString msg, str;
	msg = "Attenzione, prima di proseguire verificare che nessun operatore stia eseguendo l'operazione di emissione.";
	msg += "Si vuole procedere con l'operazione?";
	if(!IDYES == AfxMessageBox(msg, MB_YESNO) )
		return;
	
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CCertificatiSet Set(&pApp->m_db);
	if( !pApp->DisabilitaCertificazione(&str, FALSE) )
		AfxMessageBox("La certificazione non risulta bloccata.");
}

void CVerbaliView::OnStampaEtichette() 
{
	CStringArray* paryIndRep	= new CStringArray();
	CStringArray*	paryInd	= new CStringArray(); 

	CStringArray aryField, aryValue;
	CString str;
	CPrintInterpreter prn;
	CEtichetteDlg dlg;	
	dlg.m_strScelti = m_strTempEtichette;
	dlg.m_paryIndirizzi				= paryInd;
	dlg.m_paryIndirizziReport	= paryIndRep;
	if(dlg.DoModal() == IDOK)
	{
		if(dlg.m_bStReport || dlg.m_bStEtichette)
		{
			m_aryCampiEtichette.RemoveAll();
			m_nContaEtichette = 0;
			m_nSaltaEtichette = 0;

			if(dlg.m_bStReport)
			{
				if(prn.PrePrinting())
				{
					SetCursor(LoadCursor(NULL, IDC_WAIT));
					m_aryCampiEtichette.Copy(*dlg.m_paryIndirizziReport);
					aryField.RemoveAll();
					aryValue.RemoveAll();
					str.Format("Stampa del report delle etichette dei Verbali (%s)", dlg.m_strScelti);
					aryField.Add("intestazione");
					aryValue.Add(str);
					prn.Print(".\\ReportEtichette.prn", &aryField, &aryValue, NULL, NULL, &ScanEtichette);
					prn.PostPrinting();
				}
			}
				
			if(dlg.m_bStEtichette && paryInd->GetSize())
			{
				if(prn.PrePrinting())
				{
					m_nSaltaEtichette = dlg.m_nInizioStampa;
					m_nContaEtichette = 0;
					m_aryCampiEtichette.Copy(*paryInd);
					aryField.RemoveAll();
					aryValue.RemoveAll();
					prn.Print(".\\Etichette.prn", &aryField, &aryValue, NULL, NULL, &ScanEtichette);
					prn.PostPrinting();
				}
			}
		}
		m_strTempEtichette	= dlg.m_strScelti;
	}
	delete paryIndRep;
	delete paryInd;
}

BOOL CVerbaliView::ScanEtichette(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
	int index = m_nContaEtichette - m_nSaltaEtichette;
	pFieldNames->RemoveAll();
	pFieldValues->RemoveAll();
	if( index >= m_aryCampiEtichette.GetSize())
		return FALSE;

	CString str="";;
	if(index>=0)
		str = m_aryCampiEtichette.GetAt(index);

	pFieldNames->Add("indirizzo");
	str.Replace("&","&&");
	pFieldValues->Add(str);

	m_nContaEtichette++;
	index = m_nContaEtichette - m_nSaltaEtichette;
	if( index >= m_aryCampiEtichette.GetSize())
		return FALSE;
	
	return TRUE;
}


void CVerbaliView::CreaEmendamento(long codDoc)
{
	CWinSigmaApp*			pApp				= (CWinSigmaApp*)AfxGetApp();

	CCertificatiSet*	pOldCertSet	=		new CCertificatiSet(&pApp->m_db);
	CSerieSet*				pOldSerieSet=		new CSerieSet(&pApp->m_db);
	CProviniSet*			pOldProvSet	=		new CProviniSet(&pApp->m_db);

	CSerieSet					newSerieSet(&pApp->m_db);
	CProviniSet				newProvSet(&pApp->m_db);
	CCertificatiSet		newCertSet(&pApp->m_db);

	newSerieSet.m_strFilter = "Codice = -1";
	newProvSet.m_strFilter	= "Codice = -1"; 
	newSerieSet.Open();
	newProvSet.Open();
	
	try
	{
		pApp->BeginTrans();

// Inserimento del nuovo certificato
		
		// Cerco il numero da assegnare al nuovo certificato
		CString queryData;
		CTime inizioAnno(CTime::GetCurrentTime().GetYear(), 1,1,1,1,1,1);
		queryData.Format("CERTIFICATI.DataEmissione >= '%s'", inizioAnno.Format("%Y-%m-%d"));
		long numeroMax = 0;
		newCertSet.m_strSort = "NumeroCertificato ASC";
		newCertSet.m_strFilter = queryData;
		newCertSet.Open();
		if( !newCertSet.IsEOF() )
		{
			newCertSet.MoveLast();
			numeroMax = newCertSet.m_NumeroCertificato;
		}
		long numeroNuovoDoc = numeroMax + 1;

		pOldCertSet->m_strFilter.Format("Codice = %d", codDoc);
		pOldCertSet->Open();
		
		newCertSet.AddNew();
		newCertSet.m_NumeroCertificato	= numeroNuovoDoc;
		newCertSet.m_DataEmissione			= CTime::GetCurrentTime();
		newCertSet.m_DataProve					= pOldCertSet->m_DataProve;
		newCertSet.m_Macchina						= pOldCertSet->m_Macchina;
		newCertSet.m_NumeroPagine				= pOldCertSet->m_NumeroPagine;
		newCertSet.m_Sperimentatore			= pOldCertSet->m_Sperimentatore;
		newCertSet.m_TipoCertificato		= pOldCertSet->m_TipoCertificato;
		newCertSet.m_Verbale						= m_pVerbaliSet->m_Codice;
		newCertSet.m_EmendaIl						= pOldCertSet->m_Codice;
		newCertSet.Update();

		// Reperimento del codice del nuovo certificato appena inserito
		CString queryNumero;
		queryNumero.Format("NumeroCertificato = %d", numeroNuovoDoc);
		newCertSet.m_strFilter.Format("%s AND %s", queryData, queryNumero);
		newCertSet.Requery();
		long codNuovoDoc = newCertSet.m_Codice;

		// Notifica che il vecchio certificato è stato emendato
		pOldCertSet->Edit();
		pOldCertSet->m_EmendatoDa = codNuovoDoc;
		pOldCertSet->Update();
		
// Iserimento delle nuove serie

		// Reperisco tutte le serie da duplicare
		pOldSerieSet->m_strFilter.Format("Certificato = %d", codDoc);
		pOldSerieSet->Open();

		// Operazione di duplicazione dei record delle serie e dei provini
		for(SET_START(pOldSerieSet); !pOldSerieSet->IsEOF(); pOldSerieSet->MoveNext() )	
		{
			newSerieSet.AddNew();
			newSerieSet.m_Certificato				= codNuovoDoc;
			newSerieSet.m_DataPrelievo			= pOldSerieSet->m_DataPrelievo;
			newSerieSet.m_DataProva					= pOldSerieSet->m_DataProva;
			newSerieSet.m_Dimensione1				= pOldSerieSet->m_Dimensione1;
			newSerieSet.m_Dimensione2				= pOldSerieSet->m_Dimensione2;
			newSerieSet.m_Dimensione3				= pOldSerieSet->m_Dimensione3;
			newSerieSet.m_IDMateriale				= pOldSerieSet->m_IDMateriale;
			newSerieSet.m_Marchio						= pOldSerieSet->m_Marchio;
			newSerieSet.m_Macchina					= pOldSerieSet->m_Macchina;
			newSerieSet.m_Materiale					= pOldSerieSet->m_Materiale;
			newSerieSet.m_NumeroProvini			= pOldSerieSet->m_NumeroProvini;
			newSerieSet.m_NuovoCertificato	= pOldSerieSet->m_NuovoCertificato;
			newSerieSet.m_Osservazioni			= pOldSerieSet->m_Osservazioni;
			newSerieSet.m_ServAggiungibile	= pOldSerieSet->m_ServAggiungibile;
			newSerieSet.m_ServAggiunto			= pOldSerieSet->m_ServAggiunto;
			newSerieSet.m_Servizio1					= pOldSerieSet->m_Servizio1;
			newSerieSet.m_Servizio2					= pOldSerieSet->m_Servizio2;
			newSerieSet.m_Servizio3					= pOldSerieSet->m_Servizio3;
			newSerieSet.m_Servizio4					= pOldSerieSet->m_Servizio4;
			newSerieSet.m_Servizio5					= pOldSerieSet->m_Servizio5;
			newSerieSet.m_Servizio6					= pOldSerieSet->m_Servizio6;
			newSerieSet.m_Sigla							= pOldSerieSet->m_Sigla;
			newSerieSet.m_StrutturaPrelievo = pOldSerieSet->m_StrutturaPrelievo;
			newSerieSet.m_Snervamento				= pOldSerieSet->m_Snervamento;
			newSerieSet.m_Sperimentatore		= pOldSerieSet->m_Sperimentatore;
			newSerieSet.m_TipoCertificato		= pOldSerieSet->m_TipoCertificato;
			newSerieSet.m_TipoProva					= pOldSerieSet->m_TipoProva;
			newSerieSet.m_Verbale						= pOldSerieSet->m_Verbale;
			newSerieSet.Update();
			

      //Inserimento dei nuovi provini
			// Reperimento del codice della serie appena inserita
			newSerieSet.m_strFilter.Format("Certificato = %d", codNuovoDoc);
      newSerieSet.m_strSort = "Codice ASC";
			newSerieSet.Requery();
      newSerieSet.MoveLast();
			long codNuovaSerie = newSerieSet.m_Codice;

			// Carico i provini associati alla serie in fase di duplicazione
			pOldProvSet->m_strFilter.Format("Serie = %d", pOldSerieSet->m_Codice);
			if(pOldProvSet->IsOpen())
				pOldProvSet->Requery();
			else
				pOldProvSet->Open();
			
			// Eseguo la duplicazione dei provini.
			for(; !pOldProvSet->IsEOF(); pOldProvSet->MoveNext())
			{
				newProvSet.AddNew();
				newProvSet.m_Risultati.Copy(pOldProvSet->m_Risultati);
				newProvSet.m_DataInserimento	= pOldProvSet->m_DataInserimento;
				newProvSet.m_Servizio					= pOldProvSet->m_Servizio;
				newProvSet.m_Serie						= codNuovaSerie;
				newProvSet.Update();
			}
		}	
		pApp->CommitTrans();
	}
	catch(CDBException* e)
	{
		CString err = e->m_strError;
		AfxMessageBox(err);
		pOldSerieSet->Close();
		pOldCertSet->Close();
		pOldProvSet->Close();
		newSerieSet.Close();
		newCertSet.Close();
		newProvSet.Close();
		delete pOldSerieSet;
		delete pOldCertSet;
		delete pOldProvSet;
		pApp->Rollback();
	}
	if(pOldSerieSet->IsOpen())
		pOldSerieSet->Close();
	if(pOldCertSet->IsOpen())
		pOldCertSet->Close();
	if(pOldProvSet->IsOpen())
		pOldProvSet->Close();
	newSerieSet.Close();
	newCertSet.Close();
	newProvSet.Close();
	delete pOldSerieSet;
	delete pOldCertSet;
	delete pOldProvSet;
}

void CVerbaliView::OnPrintSchedaIntFattura() 
{
	CPrintInterpreter prn;
	if(prn.PrePrinting())
	{
		SetCursor(LoadCursor(NULL, IDC_WAIT));
		CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
		CAziendeSet aziendeSet(&pApp->m_db);
		aziendeSet.m_strFilter.Format("Codice = %d", m_pVerbaliSet->m_CodiceAzFattura);
		aziendeSet.Open();
		if(aziendeSet.IsEOF())
		{
      aziendeSet.Close();
			AfxMessageBox("Attenzione, intestatario non trovato");
			return;
		}
		CString str;
		CStringArray fName, fValue;
		str.Format("VERBALE: %d/%d del %s", m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale, m_pVerbaliSet->m_DataAccettazione.Format("%d/%m/%Y"));
		fName.Add("datiVerbale");
		fValue.Add(str);

		fName.Add("id");
		str.Format("(Cod: %s)", aziendeSet.m_ID);
		fValue.Add(str);
		
		fName.Add("ragSociale");
		fValue.Add(aziendeSet.m_RagioneSociale);

		fName.Add("piva");
		if(aziendeSet.m_Privato)
			str.Format("C. fiscale: %s", aziendeSet.m_CodiceFiscale);
		else
			str.Format("P. IVA: %s", aziendeSet.m_P_IVA);
		fValue.Add(str);
		
		fName.Add("indirizzo");
		fValue.Add(aziendeSet.m_Indirizzo);

		fName.Add("cap");
		fValue.Add(aziendeSet.m_CAP);

		fName.Add("citta");
		str.Format("%s (%s)", aziendeSet.m_Citta, aziendeSet.m_Provincia);
		fValue.Add(str);

		if(!aziendeSet.IsFieldNull(&aziendeSet.m_Indirizzo_Sped))
		{
			fName.Add("indirizzoSped");
			fValue.Add(aziendeSet.m_Indirizzo_Sped);

			fName.Add("capSped");
			fValue.Add(aziendeSet.m_CAP_Sped);

			fName.Add("cittaSped");
			str.Format("%s (%s)", aziendeSet.m_Citta_Sped, aziendeSet.m_Provincia_Sped);
			fValue.Add(str);
		}		
		
		fName.Add("datiAggiuntivi");
		if(!aziendeSet.IsFieldNull(&aziendeSet.m_Note))
			str = aziendeSet.m_Note;
		else
			str = "Non ci sono dati aggiuntivi.";
		fValue.Add(str);
		
		prn.Print(FILE_STAMPA_SCHEDA, &fName, &fValue, NULL, NULL, NULL);
		prn.PostPrinting();
    aziendeSet.Close();
	}
  
}

// Stampa una fattura proforma del verbale selezionato
// Vengono erogati i servizi
void CVerbaliView::OnPrnFatturaProforma() 
{

  if (!m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_NumeroFattura))
  {
    AfxMessageBox("Il verbale è già stato fatturato o messo in fatturazione.", MB_OK);
    return;
  }
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

  CDatiFatturaProforma dlg;
  if(m_pVerbaliSet->m_Spedizione)
    dlg.m_bSpedizione = TRUE;
  else
    dlg.m_bSpedizione = FALSE;
//  dlg.m_strAliquota = STR_DEFAULT_ALIQUOTA_IVA;
  dlg.m_strAliquota = pApp->m_csAliquotaIVA;
  dlg.m_nNumCopie = 1;
  if(dlg.DoModal() == IDCANCEL)
    return;
  double dAliquota = 0, dSpese = 0, dSconto = 0;
  dlg.m_strAliquota.Replace(",", ".");
  dAliquota = atof(dlg.m_strAliquota);
  if(!dlg.m_strSconto.IsEmpty())
  {
    dlg.m_strSconto.Replace(",", ".");
    dSconto = atof(dlg.m_strSconto);
  }
  if(!dlg.m_strSpese.IsEmpty())
  {
    dlg.m_strSpese.Replace(",", ".");
    dSpese = atof(dlg.m_strSpese);
  }
  long lCodVerbale = m_pVerbaliSet->m_Codice;
  BOOL bServiziErogati = (m_pVerbaliSet->m_InFatturazione == VERB_PROFORMA);
  // Metto il verbale in fatturazione
  m_pVerbaliSet->Edit();
  m_pVerbaliSet->m_NumeroFattura = 0;
  m_pVerbaliSet->m_InFatturazione = VERB_PROFORMA;
  m_pVerbaliSet->Update();
  SINCRONIZE(m_pVerbaliSet, lCodVerbale);
  // Erogo i servizi se non sono ancora stati erogati
  m_pSerieSet->m_strFilter.Format("Verbale = %ld", lCodVerbale);
  m_pSerieSet->Requery();
  if(!bServiziErogati)
  {
    for(SET_START(m_pSerieSet); !m_pSerieSet->IsEOF(); m_pSerieSet->MoveNext())
      ErogaServiziSerie(m_pSerieSet);
  }
  // Stampo la fattura proforma
  CPrintPreviewFatture prnPreview;
  prnPreview.m_lCodiceFattura = 0;
  prnPreview.m_lCodiceVerbale = lCodVerbale;
  prnPreview.m_lCodiceAzienda = m_pVerbaliSet->m_CodiceAzFattura;
  prnPreview.m_bPrintProForma = TRUE;
  prnPreview.m_bRaggruppaPerServizio = FALSE;
  if(m_pVerbaliSet->m_Spedizione && dSpese)
    prnPreview.m_bSpedSelezionata = TRUE;
  else
    prnPreview.m_bSpedSelezionata = FALSE;
  prnPreview.m_nNumeroCopie = 1;
  prnPreview.m_dAliquota = dAliquota;
  prnPreview.m_dSconto = dSconto;
  prnPreview.m_dSpeseSpedizione = dSpese;
  prnPreview.m_dImportoFattura = 0;
  prnPreview.m_nNumeroCopie = dlg.m_nNumCopie;
  prnPreview.Print(0, NULL, NULL);
  // Tolgo il verbale dalla fatturazione
  m_pVerbaliSet->Edit();
  m_pVerbaliSet->SetFieldNull(&m_pVerbaliSet->m_NumeroFattura);
  m_pVerbaliSet->Update();
  m_pVerbaliSet->Requery();
  // Sincronizzo il recordset ed aggiorno gli alberi
  SINCRONIZE(m_pVerbaliSet, lCodVerbale);
  pApp->ReloadTree(TREELABEL_VERBALIFATTPROFORMA, -1);
  pApp->ReloadTree(TREELABEL_VERBALIPRECEDENTI, -1);
  pApp->ReloadTree(TREELABEL_VERBALIULTIMOMESE, -1);
  LoadCurRecord(TRUE);
}

void CVerbaliView::OnButtonEmenda() 
{
  // Puntatore all'applicazione
  CWinSigmaApp*	pApp = (CWinSigmaApp*)AfxGetApp();

  // Dialog Emendamenti
  CEmendaDlg* emenda = new CEmendaDlg;
 
  // Reperimento dei parametri da passare al dialogo degli emnedamenti
  CString str("");
  m_ListSerie.GetItemText(m_ListSerie.GetSelectionMark(), 1, str.GetBuffer(100), 100);
  
  // Reperimento dell'ID del Certificato
  int IDSerie = m_ListSerie.GetItemData(m_ListSerie.GetSelectionMark());
  m_pSerieSet->m_strFilter.Format("Codice = %d", IDSerie);
  m_pSerieSet->Requery();

  // Crea il Certificato nel Dialogo
  if (!m_pSerieSet->IsEOF())
  {
    emenda->SetIDCertificato(m_pSerieSet->m_Certificato);
    emenda->SetDescrCertificato(str);
  }

  m_pSerieSet->m_strFilter.Format("Certificato = %d", m_pSerieSet->m_Certificato);
  m_pSerieSet->Requery();
  while (!m_pSerieSet->IsEOF())
  {
    // Inserisce gli ID delle Serie nel CWordArray del Dialogo
    emenda->m_waIDSerie.Add((DWORD)m_pSerieSet->m_Codice);
    m_pSerieSet->MoveNext();
  }

  // Creazione degli Emendamenti
  if (emenda->DoModal() == IDOK)
  {
    SetCursor(LoadCursor(NULL, IDC_WAIT));

    // Reperimento dati vecchio certificato, serie, provini
    CCertificatiSet*  pOldCertificato = new CCertificatiSet(&pApp->m_db);
    pOldCertificato->m_strFilter.Format("Codice = %d", emenda->m_nIDCertificato);
    pOldCertificato->Open();
    
    CSerieSet*        pOldSerie       = new CSerieSet(&pApp->m_db);
    pOldSerie->Open();
    
    long codNuovoEmen(0);

    // Puntatore al recorset per l'aggiunta del nuovo emendamento
    CCertificatiSet* pNewCertificato = new CCertificatiSet(&pApp->m_db);
    pNewCertificato->Open();
    
    CSerieSet*  pNewSerie  = new CSerieSet(&pApp->m_db);
    pNewSerie->Open();

    /*---- Inizio Gestione Emendamenti ----*/
    for (int i(0); i < emenda->m_oaSerieEmend.GetSize(); i++)
    {
        // Cerco il numero da assegnare al nuovo Emendamento
		    CString queryData;
		    CTime inizioAnno(CTime::GetCurrentTime().GetYear(), 1,1,1,1,1,1);
		    queryData.Format("CERTIFICATI.DataEmissione >= '%s'", inizioAnno.Format("%Y-%m-%d"));
		    long numeroMax = 0;
		    pNewCertificato->m_strSort = "NumeroCertificato ASC";
		    pNewCertificato->m_strFilter = queryData;
		    pNewCertificato->Requery();
		    if( !pNewCertificato->IsEOF() )
		    {
			    pNewCertificato->MoveLast();
			    numeroMax = pNewCertificato->m_NumeroCertificato;
		    }
		    long numeroNuovoCert = numeroMax + 1;
    
        // Aggiungo l'Emendamento
        pNewCertificato->AddNew();
        pNewCertificato->m_NumeroCertificato	= numeroNuovoCert;
		    pNewCertificato->m_DataEmissione			= CTime::GetCurrentTime();
		    pNewCertificato->m_DataProve					= pOldCertificato->m_DataProve;
		    pNewCertificato->m_Macchina					  = pOldCertificato->m_Macchina;
		    pNewCertificato->m_NumeroPagine			  = pOldCertificato->m_NumeroPagine;
		    pNewCertificato->m_Sperimentatore		  = pOldCertificato->m_Sperimentatore;
		    pNewCertificato->m_TipoCertificato		= pOldCertificato->m_TipoCertificato;
		    pNewCertificato->m_Verbale						= pOldCertificato->m_Verbale;
		    pNewCertificato->m_EmendaIl					  = pOldCertificato->m_Codice;
        pNewCertificato->Update();


        // Reperimento del codice dell'Emendamento appena inserito
		    CString queryNumero("");
		    queryNumero.Format("NumeroCertificato = %d", numeroNuovoCert);
		    pNewCertificato->m_strFilter.Format("%s AND %s", queryData, queryNumero);
		    pNewCertificato->Requery();
        // Salvo l'ID dell'Emendamento
        codNuovoEmen = pNewCertificato->m_Codice;

        pOldCertificato->Edit();
        pOldCertificato->m_EmendatoDa = codNuovoEmen;
        pOldCertificato->Update();

        for (int h(0); h < ((CWordArray*)(emenda->m_oaSerieEmend.GetAt(i)))->GetSize(); h++)
        {
        /*---- Inizio Gestione Serie ----*/
          pOldSerie->m_strFilter.Format("Codice = %d", ((CDWordArray*)(emenda->m_oaSerieEmend.GetAt(i)))->GetAt(h));
          pOldSerie->Requery();
          if (!pOldSerie->IsEOF())
          {
            // Inserisce le nuove serie
            pNewSerie->AddNew();
			      pNewSerie->m_Certificato				= codNuovoEmen;
			      pNewSerie->m_DataPrelievo			  = pOldSerie->m_DataPrelievo;
			      pNewSerie->m_DataProva					= pOldSerie->m_DataProva;
			      pNewSerie->m_Dimensione1				= pOldSerie->m_Dimensione1;
			      pNewSerie->m_Dimensione2				= pOldSerie->m_Dimensione2;
			      pNewSerie->m_Dimensione3				= pOldSerie->m_Dimensione3;
			      pNewSerie->m_IDMateriale				= pOldSerie->m_IDMateriale;
			      pNewSerie->m_Marchio						= pOldSerie->m_Marchio;
			      pNewSerie->m_Macchina					  = pOldSerie->m_Macchina;
			      pNewSerie->m_Materiale					= pOldSerie->m_Materiale;
			      pNewSerie->m_NumeroProvini			= pOldSerie->m_NumeroProvini;
            
            if (h == 0)
              pNewSerie->m_NuovoCertificato	  = 1;
            else
  			      pNewSerie->m_NuovoCertificato	  = pOldSerie->m_NuovoCertificato;

			      pNewSerie->m_Osservazioni			  = pOldSerie->m_Osservazioni;
			      pNewSerie->m_ServAggiungibile	  = pOldSerie->m_ServAggiungibile;
			      pNewSerie->m_ServAggiunto			  = pOldSerie->m_ServAggiunto;
			      pNewSerie->m_Servizio1					= pOldSerie->m_Servizio1;
			      pNewSerie->m_Servizio2					= pOldSerie->m_Servizio2;
			      pNewSerie->m_Servizio3					= pOldSerie->m_Servizio3;
			      pNewSerie->m_Servizio4					= pOldSerie->m_Servizio4;
			      pNewSerie->m_Servizio5					= pOldSerie->m_Servizio5;
			      pNewSerie->m_Servizio6					= pOldSerie->m_Servizio6;
			      pNewSerie->m_Sigla							= pOldSerie->m_Sigla;
			      pNewSerie->m_Sigla2							= pOldSerie->m_Sigla2;
			      pNewSerie->m_StrutturaPrelievo  = pOldSerie->m_StrutturaPrelievo;
			      pNewSerie->m_Snervamento				= pOldSerie->m_Snervamento;
			      pNewSerie->m_Sperimentatore		  = pOldSerie->m_Sperimentatore;
			      pNewSerie->m_TipoCertificato		= pOldSerie->m_TipoCertificato;
			      pNewSerie->m_TipoProva					= pOldSerie->m_TipoProva;
			      pNewSerie->m_Verbale						= pOldSerie->m_Verbale;
			      pNewSerie->m_strDataND					= pOldSerie->m_strDataND;
			      pNewSerie->m_Checked					  = pOldSerie->m_Checked;
			      pNewSerie->m_Ordinamento				= pOldSerie->m_Ordinamento;
			      pNewSerie->m_SiglaFornitore			= pOldSerie->m_SiglaFornitore;
			      pNewSerie->m_VerbalePrelievo		= pOldSerie->m_VerbalePrelievo;
			      pNewSerie->Update();


            // Ricerca del Codice della Serie appena aggiunta
			      pNewSerie->m_strFilter.Format("Certificato = %d", codNuovoEmen);
            pNewSerie->m_strSort = "Codice ASC";
			      pNewSerie->Requery ();
            pNewSerie->MoveLast();
			      long codNuovaSerie = pNewSerie->m_Codice;

            /*---- Inizio Gestione Provini ----*/
            CProviniSet* pOldProvini = new CProviniSet(&pApp->m_db);
            pOldProvini->m_strFilter.Format("Serie = %d", pOldSerie->m_Codice);
						pOldProvini->m_strSort = "Codice";
            pOldProvini->Open();

            CProviniSet* pNewProvini = new CProviniSet(&pApp->m_db);
            pNewProvini->Open();
            while (!pOldProvini->IsEOF())
            {
//              CProviniSet* pNewProvini = new CProviniSet(&pApp->m_db);
//              pNewProvini->Open();

              pNewProvini->AddNew();

				      pNewProvini->m_Risultati.Copy(pOldProvini->m_Risultati);
				      pNewProvini->m_DataInserimento = pOldProvini->m_DataInserimento;
				      pNewProvini->m_Servizio				= pOldProvini->m_Servizio;
				      pNewProvini->m_Serie						= codNuovaSerie;
							// [Fix] 7.12.2017 aggiunti Marchio e RotoliCT s.c.
							pNewProvini->m_Marchio = pOldProvini->m_Marchio;
							pNewProvini->m_RotoliCT = pOldProvini->m_RotoliCT;
              pNewProvini->Update();
        
//              pNewProvini->Close();
//              delete pNewProvini;
        
              pOldProvini->MoveNext();
            }

            pNewProvini->Close();
            delete pNewProvini;
      
            pOldProvini->Close();
            delete pOldProvini;
            /*---- Fine Gestione Provini ----*/
          }
        }
      /*---- Fine Gestione Serie ----*/
    }

    pNewCertificato->Close();
    delete pNewCertificato;

    pOldCertificato->Close();
    delete pOldCertificato;

    pOldSerie->Close();
    delete pOldSerie; 

    pNewSerie->Close();
    delete pNewSerie;
    /*---- Fine Gestione Emendamenti ----*/
  }

  delete emenda;

  // Riallineamento del rercordset con il contenuto del database.
	long tempSel = m_pSerieSet->m_Codice;
	m_pSerieSet->Requery();
	SINCRONIZE(m_pSerieSet, tempSel);

  LoadSeries(m_pVerbaliSet->m_Codice);
}

void CVerbaliView::OnClickListSerie(NMHDR* pNMHDR, LRESULT* pResult) 
{
  int pos = m_ListSerie.GetSelectionMark();
  CString str = m_ListSerie.GetItemText(pos,1);
  if ((!str.IsEmpty())                                  && 
      (str!="-----")                                    && 
      (m_BtnDatiProvini.IsWindowEnabled()   == FALSE)   && 
      (m_BtnEliminaSerie.IsWindowEnabled()  == FALSE)   && 
      (m_BtnModificaSerie.IsWindowEnabled() == FALSE)   && 
      (m_BtnAggiungiSerie.IsWindowEnabled() == FALSE))
    m_BtnEmenda.EnableWindow();
  else
    m_BtnEmenda.EnableWindow(FALSE);
	
	*pResult = 0;
}

void CVerbaliView::OnCheckRitiro() 
{
	UpdateData();
  if (m_bRitiro)
  {
    m_CtrlDataConsegna.EnableWindow(TRUE);
    m_BtnUrgenza.SetCheck(BST_UNCHECKED);
  }
	else if (m_bUrgenza == false)
    m_CtrlDataConsegna.EnableWindow(FALSE);

  m_EditOraConsegna.EnableWindow(FALSE);
}

void CVerbaliView::OnFindVerbNumero() 
{
	FindVerbali(SEARCH_NUMERO);	
}

#define SAFETY_OPEN(pSet) pSet->IsOpen() ? pSet->Requery() : pSet->Open();
// compone il nome del file certificato pdf secondo la specifica fornita (27.06.2017) 
CString CVerbaliView::BuildCertificateName(CCertificatiVerbaliSet* pCertVerbSet)
{
	CString docname;
	CString siglasp = "XX";

	int numverb = pCertVerbSet->m_ProgressivoTotale;
	int annoverb = pCertVerbSet->m_DataAccettazione.GetYear();
	int numcert = pCertVerbSet->m_NumeroCertificato;
	int annocert = pCertVerbSet->m_DataEmissione.GetYear();

	// trova la serie corrispondente al certificato per determinare lo sperimentatore
	CSerieSet* pSerieSet = m_pTabelle->m_pSerieSet;
	pSerieSet->m_strFilter.Format(" NuovoCertificato = 1 AND Certificato = %d ", pCertVerbSet->m_CodiceCertificato);
	SAFETY_OPEN(pSerieSet);

	if(!pSerieSet->IsEOF())
	{
		// trovata la serie determina la sigla dello sperimentatore
		CString exper = pSerieSet->m_Sperimentatore;
		COperatoriSet* pOperatSet = m_pTabelle->m_pOperatoriSet;
		pOperatSet->m_strFilter.Format(" REPLACE(CONCAT(IFNULL(Titolo, ''), Nome, Cognome), ' ', '') = REPLACE('%s', ' ', '') ", exper);
		SAFETY_OPEN(pOperatSet);
		if(!pOperatSet->IsEOF())
		{
			siglasp.Format("%s", pOperatSet->m_Sigla);
		}
	}
	docname.Format("CE-1-%d-%d-%s-C-%d-%d-0", numverb, annoverb, siglasp, numcert, annocert);
	return docname;
}

void CVerbaliView::StampaCertificatoDiretto(CTipiCertificatoSet* pTipiCertSet, long codRif, CPrintInterpreter* pprn, BOOL isCodSerie, BOOL bHeader)
{
	m_pTipiCertificatoSet = pTipiCertSet;
	StampaCertificatoDiretto(codRif, pprn, isCodSerie, bHeader);
}

void CVerbaliView::StampaCertificatoDiretto(long codRif, CPrintInterpreter* pprn, BOOL isCodSerie, BOOL bHeader)
{
		//--------------- Istanze dei recordset utilizzati-----------------//
  BOOL bIsEmendamento = FALSE; 
	CWinSigmaApp* pApp	= (CWinSigmaApp*)AfxGetApp();
	m_pTabelle					= new CAllTables(&pApp->m_db);
	CCertificatiVerbaliSet* pCertVerbSet	= new CCertificatiVerbaliSet(&pApp->m_db);
	long codCertificato;

	m_pTabelle->m_pSerieProviniSet->m_strFilter.Format("SERIE.Codice = PROVINI.Serie AND SERIE.Codice = %d ", codRif);
	m_pTabelle->m_pSerieProviniSet->m_strSort = "SERIE.Codice , PROVINI.Codice";
  m_pTabelle->m_pSerieProviniSet->Open();

	if(isCodSerie)
		codCertificato = m_pTabelle->m_pSerieProviniSet->m_Certificato;
	else
		codCertificato = codRif;
		
	pCertVerbSet->m_strFilter.Format("VERBALI.Codice = CERTIFICATI.Verbale AND CERTIFICATI.Codice = %d", codCertificato);
	pCertVerbSet->Open();

  if(pApp->GetViewMode() != MODE_VIEW)
	{
	  MessageBeep(-1);
		return;
	}

	if( pCertVerbSet->IsEOF() )
	{
		pCertVerbSet->Close();
		delete pCertVerbSet;
		delete m_pTabelle;
		AfxMessageBox("Operazione non disponibile!\nNon è stato trovato il documento richiesto.");
		return;
	}

	CDWordArray CertScelti;
	try
	{
		pCertVerbSet->MoveFirst();
	}
	catch(CDBException* e)
  {
		pCertVerbSet->Close();
		delete m_pTabelle;
		delete pCertVerbSet;
    return;
  }  

	for(;!pCertVerbSet->IsEOF(); pCertVerbSet->MoveNext())
	{
		CertScelti.Add(pCertVerbSet->m_CodiceCertificato);
	}

	BOOL stampaDuplicato = TRUE;
	CTime dataDuplicato = CTime::GetCurrentTime();

	CString fileLayout = "";	// contenitore del nome del file di layout
	int numeroPagine = 0;
	CStringArray fieldNames, fieldValues, marchiFiles;

	for(int i = 0; i < CertScelti.GetSize(); i++)
	{
		//sincronizzo il recordset con il certificato scelto
		for(SET_START(pCertVerbSet); !pCertVerbSet->IsEOF(); pCertVerbSet->MoveNext())
		if(pCertVerbSet->m_CodiceCertificato == (long)CertScelti.GetAt(i))
			break;

		// Settaggio della dll associata per richiamare opportunamente le funzioni
		SINCRONIZE(m_pTipiCertificatoSet, pCertVerbSet->m_TipoCertificato);
			
		fileLayout = m_pTipiCertificatoSet->m_LayoutStampa;
					
		m_strDllCorrente = GetNameModuloDll(m_pTipiCertificatoSet->m_Codice);
        
//		CPrintInterpreter prn;
		CString docname = BuildCertificateName(pCertVerbSet);
		pprn->SetDocName(docname);
//		if(prn.PrePrinting())
//		{
			numeroPagine = LoadDatiStampa(pCertVerbSet->m_CodiceCertificato, &fieldNames, &fieldValues);

			//--- Gestione del duplicato e dell'emendamento ---//
			CString str = "";
			CString strAmend = "";
			fieldNames.Add("duplicato");
			if(stampaDuplicato)					
				str.Format("DUPLICATO del %s", dataDuplicato.Format("%d/%m/%Y"));
 			fieldValues.Add(str);
			str.Empty();
			fieldNames.Add("emendamento");
			if(!pCertVerbSet->IsFieldNull(&pCertVerbSet->m_EmendaIl) && pCertVerbSet->m_EmendaIl != 0)
			{
				bIsEmendamento = TRUE;
				CCertificatiSet set(&pApp->m_db);
				set.m_strFilter.Format("Codice = %d", pCertVerbSet->m_EmendaIl);
				set.Open();
				// variazione dicitura emendamento 29.05.2016 s.c. 
				strAmend.Format("Emendamento che annulla e sostituisce il certificato N° %d del %s", set.m_NumeroCertificato, set.m_DataEmissione.Format("%d/%m/%Y"));
				set.Close();
			}
			if(!pCertVerbSet->IsFieldNull(&pCertVerbSet->m_EmendatoDa) && pCertVerbSet->m_EmendatoDa != 0)
			{
				bIsEmendamento = TRUE;
				CCertificatiSet set(&pApp->m_db);
				set.m_strFilter.Format("Codice = %d", pCertVerbSet->m_EmendatoDa);
				set.Open();
				strAmend.Format("Emendato dal certificato N° %d del %s", set.m_NumeroCertificato, set.m_DataEmissione.Format("%d/%m/%Y"));
				set.Close();
			}
 			fieldValues.Add(strAmend);
        
			CString debug = pCertVerbSet->m_Cantiere;

			//Preparazione del recordset dei provini 
			//m_pTabelle->m_pSerieProviniSet->m_strSort = "SERIE.Codice, PROVINI.Codice ASC";
			m_pTabelle->m_pSerieProviniSet->m_strFilter.Format("SERIE.Codice = PROVINI.Serie AND SERIE.Certificato = %d ", pCertVerbSet->m_CodiceCertificato);
			m_pTabelle->m_pSerieProviniSet->m_strSort = "SERIE.Codice, PROVINI.Codice ASC";
			m_pTabelle->m_pSerieProviniSet->Requery();
			m_nCodSerieStampata = 0;//serve per stampare la prima riga di una serie in maniera diversa 
			m_nContaProvini = 0;		// serve per indicare il numero del provino alla dll
			if(numeroPagine == 1)
			{
				//--------- gestione numeri di pagina --------------------//
				fieldNames.Add("pagineTotali");
				fieldValues.Add("1");
				fieldNames.Add("paginaCorrente");
				fieldValues.Add("1");
				//--------------------------------------------------------//
			}
				
			// imposta la stampa con l'header
			if(bHeader == TRUE)
			{
				pprn->SetHeaderFile(pApp->GetCurrentDirectory() + "\\" + pApp->m_headerPrn);
			}

			pprn->Print(pApp->GetCurrentDirectory() + "\\" + fileLayout, 
							&fieldNames, &fieldValues, NULL, NULL, &ScanProvini);
			// (andrea) Modifica provvisoria per saltare la stampa degli allegati
			// numeroPagine = 1;
			// --------------------------------------------------------------- //
			if(numeroPagine > 1)
			{
				int contaProvini = 1;
				byte stampaAllegati = TRUE;
				SET_START(m_pTabelle->m_pSerieProviniSet);
				typedef BOOL (PROCESTERNA)(CString*,CAllTables*,CStringArray*,CStringArray*,CStringArray*, int*, BOOL*, CTime* );	
				HINSTANCE hist = NULL;
				PROCESTERNA* pFunc;		
				BOOL esito = 0;
				ASSERT(hist = ::LoadLibrary(m_strDllCorrente));
				if(pFunc = (PROCESTERNA*)::GetProcAddress(hist,"StampaAllegato"))
				{
					int pagCorrente = 0;
					CString str;
					while(stampaAllegati)
					{
						fieldNames.RemoveAll();
						fieldValues.RemoveAll();
						marchiFiles.RemoveAll();
						//stampaAllegati = (pFunc)(&fileLayout,m_pTabelle,&fieldNames,&fieldValues,&contaProvini);
						SET_START(m_pTabelle->m_pSerieProviniSet);
						stampaAllegati = (pFunc)(&fileLayout, m_pTabelle, &fieldNames, &fieldValues, &marchiFiles, &pagCorrente,&stampaDuplicato, &dataDuplicato);
						//--------- gestione numeri di pagina --------------------//
						fieldNames.Add("pagineTotali");
						str.Format("%d",numeroPagine);
						fieldValues.Add(str);
						fieldNames.Add("paginaCorrente");
						str.Format("%d",pagCorrente + 2 );
						fieldValues.Add(str);
						
						if(bIsEmendamento == TRUE) // 4.12.2017 s.c.
						{
							fieldNames.Add("emendamento");
							fieldValues.Add(strAmend);
						}
						//--------------------------------------------------------//	
						pagCorrente++;
						pprn->Print(pApp->GetCurrentDirectory() + "\\" + fileLayout, 
							&fieldNames, &fieldValues, &marchiFiles, NULL, NULL);
					}
				}					
			}
			fieldNames.RemoveAll();
			fieldValues.RemoveAll();
		//	prn.PostPrinting();
//		} // endif preprinting()
	} // for sui certificati scelti

	pCertVerbSet->Close();

	delete m_pTabelle;
  delete pCertVerbSet;
}




#if 0    // da cancellare
void CVerbaliView::PrintVerbale(int mode)
{
  CPrintInterpreter prnInterpreter;
  CStringArray strNames, strValues;
  BOOL bPrint = FALSE;
  CTime data = CTime::GetCurrentTime();
  CString printFileName, strPrinter, strPrnFile, docname;
	int TipoCertificato = 0;
  int VerID;

  if(m_pVerbaliSet->IsBOF() || m_pVerbaliSet->IsEOF())
	{
	  MessageBeep(-1);
		return;
	}
	// La stampa viene fatta su un file che ha come nome il progressivo totale del verbale
  printFileName.Format("%d_%d.txt", m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale);
  VerID = m_pVerbaliSet->m_Codice;

	// imposta il nome del file secondo le specifiche della gestione documentale (s.c. 14.09.2017)
  docname.Format("VA-%d-%d", m_pVerbaliSet->m_ProgressivoTotale, m_pVerbaliSet->m_DataAccettazione.GetYear());
	prnInterpreter.SetDocName(docname);

#ifdef WINSIGMA2
  if(!prnInterpreter.PrePrinting())
    return;
#else
  if(!m_bStampaCaratteri)
  {
    if(!prnInterpreter.PrePrinting())
      return;
  }
#endif
  m_pSerieSet->m_strFilter.Format("Verbale = %d", m_pVerbaliSet->m_Codice);
  m_pSerieSet->m_strSort = "TipoCertificato, Codice ASC";
  m_pSerieSet->Requery();
  m_bSpianatura = FALSE;
  for(SET_START(m_pSerieSet); !m_pSerieSet->IsEOF(); m_pSerieSet->MoveNext())
  {
		TipoCertificato = m_pSerieSet->m_TipoCertificato;
	  ASSERT(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_ServAggiungibile));
    if(m_pSerieSet->m_ServAggiungibile)
    {
      if(m_pSerieSet->m_Servizio1 == m_pSerieSet->m_ServAggiungibile
			   || m_pSerieSet->m_Servizio2 == m_pSerieSet->m_ServAggiungibile
			   || m_pSerieSet->m_Servizio3 == m_pSerieSet->m_ServAggiungibile
			   || m_pSerieSet->m_Servizio4 == m_pSerieSet->m_ServAggiungibile
			   || m_pSerieSet->m_Servizio5 == m_pSerieSet->m_ServAggiungibile
			   || m_pSerieSet->m_Servizio6 == m_pSerieSet->m_ServAggiungibile)
        m_bSpianatura = TRUE;  	     
			else
			{
        m_bSpianatura = FALSE;  
			  break;
			}
		}
  }
  SET_START(m_pSerieSet);

  CAziendeSet* pAziende = new CAziendeSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
  pAziende->m_strFilter.Format("Codice = %d", m_pVerbaliSet->m_CodiceAzFattura);
  pAziende->Open();
  m_bPrivato = pAziende->m_Privato;
  if (!pAziende->m_Note.IsEmpty())
    m_bNote = TRUE;
  else
    m_bNote = FALSE;
  pAziende->Close();

  if(m_pVerbaliSet->m_TipoVerbale == VERB_GEOLOGIA)
	{
    strPrnFile = ".\\VerbaliGeo.prn";
	}
  else
	{
#ifdef WINSIGMA2
		CTipiCertificatoSet* pTipiCertificato = new CTipiCertificatoSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
		pTipiCertificato->m_strFilter.Format("Codice = %d", TipoCertificato);
		pTipiCertificato->Open();
		if (!pTipiCertificato->IsEOF())
		{
			strPrnFile.Format(".\\%s", pTipiCertificato->m_LayoutStampaVerbali);
		}
		else
		{
			strPrnFile = ".\\VerbaliSigma2.prn";
		}
		
		pTipiCertificato->Close();
		delete pTipiCertificato;
	}
	// Simulazione
  m_nTotalePagine = 0;
  prnInterpreter.SetPage(1);
  prnInterpreter.StartSimulation();
  prnInterpreter.Print(strPrnFile, &strNames, &strValues, NULL, &ScanCampioni);
  m_nTotalePagine = prnInterpreter.GetPage() - 1;
  prnInterpreter.EndSimulation();
  prnInterpreter.SetPage(1);
  SET_START(m_pSerieSet);
  ScanFields(&strNames, &strValues);
  prnInterpreter.Print(strPrnFile, &strNames, &strValues, NULL, &ScanCampioni);
	prnInterpreter.PostPrinting();
	if(m_bStampaCaratteri)
	{
		// Scrivo la data nel record
		CString strSql("");
		strSql.Format("UPDATE VERBALI SET DataPrimaStampa = '%s' Where Codice = %d", data.Format("%Y-%m-%d"), VerID);
		((CWinSigmaApp*)AfxGetApp())->m_db.ExecuteSQL(strSql);
	}
#else
		CTipiCertificatoSet* pTipiCertificato = new CTipiCertificatoSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
		pTipiCertificato->m_strFilter.Format("Codice = %d", TipoCertificato);
		pTipiCertificato->Open();
		if (!pTipiCertificato->IsEOF())
		{
			strPrnFile.Format(".\\%s", pTipiCertificato->m_LayoutStampaVerbali);
		}
		else
		{
			strPrnFile = ".\\Verbali.prn";
		}
		
		pTipiCertificato->Close();
		delete pTipiCertificato;
	}
	// Simulazione
  m_nTotalePagine = 0;
  prnInterpreter.SetPage(1);
  prnInterpreter.StartSimulation();
  if(m_bStampaCaratteri)
    prnInterpreter.PrintText(strPrnFile, printFileName, &strNames, &strValues, NULL, &ScanCampioni);
  else
    prnInterpreter.Print(strPrnFile, &strNames, &strValues, NULL, &ScanCampioni);
  m_nTotalePagine = prnInterpreter.GetPage() - 1;
  prnInterpreter.EndSimulation();
  prnInterpreter.SetPage(1);
  SET_START(m_pSerieSet);
  ScanFields(&strNames, &strValues);
  if(m_bStampaCaratteri)
  {
    if(prnInterpreter.PrintText(strPrnFile, printFileName, &strNames, &strValues, NULL, &ScanCampioni))
    {
      CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
      SetTimer(TIME_OUT_MSG_ID, 10000, NULL);
      // Il file è pronto, posso lanciare il thread di stampa
      CPrinterThread prnThread;
      switch(m_pVerbaliSet->m_TipoVerbale)
      {
      case VERB_IN_CONCESSIONE:
        strPrinter = pApp->GetProfileString(CONFIGURAZIONE, STAMPA_CONCESSIONE);
        break;
      case VERB_NON_IN_CONCESSIONE:
			case VERB_NC_PROVE_DI_CARICO :
			case VERB_NC_CONGL_BITUMINOSI	:
			case VERB_NC_INERTI	:
			case VERB_NC_MONITORAGGI :
			case VERB_NC_VARIE	:
			case VERB_NC_GEOTECNICA :
			case VERB_NC_LINEE_VITA:
			case VERB_NC_INDAGINI_MURATURE:
			case VERB_NC_INDAGINI_CLS:
			case VERB_NC_MAT_METALLICI:
        strPrinter = pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE);
        break;
      case VERB_GEOLOGIA:
        strPrinter = pApp->GetProfileString(CONFIGURAZIONE, STAMPA_GEOLOGIA);
        break;
      }
      prnThread.BeginPrinterThread(printFileName, strPrinter, this->m_hWnd);
      
			// Scrivo la data nel record
			CString strSql("");
			strSql.Format("UPDATE VERBALI SET DataPrimaStampa = '%s' Where Codice = %d", data.Format("%Y-%m-%d"), VerID);
			((CWinSigmaApp*)AfxGetApp())->m_db.ExecuteSQL(strSql);
    }
  }
  else
  {
    prnInterpreter.Print(strPrnFile, &strNames, &strValues, NULL, &ScanCampioni);
  	prnInterpreter.PostPrinting();
  }
#endif 
  m_pSerieSet->m_strFilter.Empty();
  m_pSerieSet->Requery();
}
#endif