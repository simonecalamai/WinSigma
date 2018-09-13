// AziendeView.cpp: implementation of the CAziendeView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "winsigma.h"
#include "winsigmadoc.h"
#include "TrovaAziendaDlg.h"
#include "InsertVerbaliDlg.h"
#include "XFormView.h"
#include "MainFrm.h"
#include "AziendeView.h"
#include "AziendeSet.h"
#include "ReportVerbali.h"
#include "PreviewDlg.h"
#include "PrintPreviewVerbali.h"
#include "LocalitaSet.h"
#include "DBRemotoDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define V_APERTO      "Aperto"
#define V_DAFATTURARE "In fatturazione"
#define V_CHIUSO      "Chiuso"
#define V_FATTURATO   "Fatturato"
#define V_ANNULLATO   "Annullato"

#define COLUMN_NUMERO  1
#define COLUMN_DATA    2
#define COLUMN_PROVE   3
#define COLUMN_STATO   4

#define STR_VERIFY_LETTERE "AaBbCcDdEeFfGgHhIiLlMmNnOoPpQqRrSsTtUuVvZzXxYyWwJjKk"

struct CheckCodeItem
{
	char car;
	int oddVal;
	int evenVal; 
};

const CheckCodeItem ccTable[] =
{
	{'0', 1, 0}, {'1', 0, 1}, {'2', 5, 2}, {'3', 7, 3}, {'4', 9, 4}, {'5', 13, 5}, {'6', 15, 6}, {'7', 17, 7}, {'8', 19, 8}, {'9', 21, 9},
	{'A', 1, 0}, {'B', 0, 1}, {'C', 5, 2}, {'D', 7, 3}, {'E', 9, 4}, {'F', 13, 5}, {'G', 15, 6}, {'H', 17, 7}, {'I', 19, 8}, {'J', 21, 9},
	{'K', 2, 10}, {'L', 4, 11}, {'M', 18, 12}, {'N', 20, 13}, {'O', 11, 14}, {'P', 3, 15}, {'Q', 6, 16}, {'R', 8, 17}, {'S', 12, 18}, {'T', 14, 19},
	{'U', 16, 20}, {'V', 10, 21}, {'W', 22, 22}, {'X', 25, 23}, {'Y', 24, 24}, {'Z', 23, 25}
}; 

const int ccSize = sizeof(ccTable)/sizeof(CheckCodeItem);

#define TIPO_NON_DEFINITO									0
#define TIPO_PERSONA_FISICA								1
#define TIPO_SOGG_DIVERSO_DA_PERS_FISICA	2

CCodiceFiscale::CCodiceFiscale()
{
	m_cCarattereDiControllo = ' ';
	m_csCodice = "";
	m_byTipoCodice = TIPO_NON_DEFINITO;
}


CCodiceFiscale::CCodiceFiscale(CString codice)
{
	m_cCarattereDiControllo = ' ';
	m_csCodice = codice;
	SetTipoCodice();
}

void CCodiceFiscale::SetTipoCodice()
{
	if(m_csCodice.GetLength() == 16)
	{
		m_byTipoCodice = TIPO_PERSONA_FISICA;
	}
	else if(m_csCodice.GetLength() == 11)
	{
		m_byTipoCodice = TIPO_SOGG_DIVERSO_DA_PERS_FISICA;
	}
	else
	{
		m_byTipoCodice = TIPO_NON_DEFINITO;
	}
}

BYTE CCodiceFiscale::GetTipoCodice()
{
	return m_byTipoCodice;
}


void CCodiceFiscale::SetCodice(CString codice)
{
	m_csCodice = codice;
	SetTipoCodice();
}

CString& CCodiceFiscale::GetCodice()
{
	return m_csCodice;
}

/*
Algoritmo: 
PERSONA FISICA: cifratura caratteri di posto dispari secondo ccTable, cifratura caratteri di posto pari secondo ccTable
somma delle cifre e calcolo del resto della divisione per 26, quindi cifratura secondo tabella 0 = 'A', 1 = 'B' ....
DIVERSO DA PERSONA FISICA: Si sommano i valori di ciascuna delle cinque cifre di ordine dispari, partendo da sinistra; 
si raddoppia ogni cifra di ordine pari e, se il risultato è un numero di due cifre, esso si riduce ad una sola 
sommando la cifra relativa alle decine e quella relativa alle unità; si sommano quindi tutti i precedenti risultati; 
si determina il totale delle due somme di cui sopra; si sottrae da dieci la cifra relativa alle unità del precedente totale. 
Il carattere di controllo è la cifra relativa alle unità del risultato.
*/
void CCodiceFiscale::CalcolaCarattereDiControllo()
{
	char cc;
	int val = 0, sum = 0, resto = 0;

	if(m_byTipoCodice == TIPO_PERSONA_FISICA)
	{
		for(int i = 0; i < m_csCodice.GetLength() - 1; i++)
		{
			cc = toupper(m_csCodice.GetAt(i));
			for(int j = 0; j < ccSize; j++)
			{
				if(cc == ccTable[j].car)
				{
					val = (i+1)%2 ? ccTable[j].oddVal : ccTable[j].evenVal;
					sum += val;
				}
			}
		}
		resto = sum % 26;
		m_cCarattereDiControllo = 'A' + resto;
	}
	else if (m_byTipoCodice == TIPO_SOGG_DIVERSO_DA_PERS_FISICA)
	{
		for(int i = 0; i < m_csCodice.GetLength() - 1; i++)
		{
			val = m_csCodice.GetAt(i) - '0';
			sum += (i%2 ? (((2*val)%10)+((2*val)/10)): val);
		}
		resto = 10 - (sum%10);
		m_cCarattereDiControllo = '0' + resto;
	}
	else
	{
		m_cCarattereDiControllo = -1;
	}
}

BOOL CCodiceFiscale::ValidaCarattereDiControllo()
{
	BOOL bRet = TRUE;
	char cc = -1;

	switch(m_byTipoCodice)
	{
		case TIPO_PERSONA_FISICA:
			cc = m_csCodice.GetAt(15);
			break;
		case TIPO_SOGG_DIVERSO_DA_PERS_FISICA:
			cc = m_csCodice.GetAt(10);
			break;
		default:
			return FALSE;
	}
	CalcolaCarattereDiControllo();
	if(cc != m_cCarattereDiControllo)
	{
		bRet = FALSE;
	}
	return bRet;
}

BOOL CCodiceFiscale::Valida()
{
	BOOL bRet = TRUE;
	CString str;
	
	if(m_byTipoCodice == TIPO_PERSONA_FISICA)
	{
		if(m_csCodice.GetLength() != 16)
			return FALSE;
		// COGNOME e NOME 6 lettere
		str = m_csCodice.Mid(0, 6);
		if(str.FindOneOf("0123456789") >= 0)
			bRet= FALSE;
		// ANNO DI NASCITA 2 cifre 00-99
		str = m_csCodice.Mid(6, 2);
		if(str.FindOneOf(STR_VERIFY_LETTERE) >= 0)
			bRet= FALSE;
		 // MESE DI NASCITA 1 lettera (A,B,C,D,E,H,L,M,P,R,S,T)
		str = m_csCodice.Mid(8, 1);
		if(str.FindOneOf("ABCDEHLMPRSTabcdehlmprst") == -1)
			bRet= FALSE;
		// GIORNO DI NASCITA 2 cifre (01-31 MASCHIO, 41-71 FEMMINA)
		str = m_csCodice.Mid(9, 2);
		if(str.FindOneOf(STR_VERIFY_LETTERE) >= 0)
			bRet= FALSE;
		int gg = atoi(str);
		if(gg < 1 || gg > 71 || (gg > 31 && gg < 41))
			bRet = FALSE;
		// COMUNE DI NASCITA codice catastale XNNN 1 lettera + 3 cifre
		str = m_csCodice.Mid(11, 1);
		if(str.FindOneOf("0123456789") >= 0)
			bRet= FALSE;
		str = m_csCodice.Mid(12, 3);
		if(str.FindOneOf(STR_VERIFY_LETTERE) >= 0)
			bRet= FALSE;
	}
	else if(m_byTipoCodice == TIPO_SOGG_DIVERSO_DA_PERS_FISICA) 
	{
		if(m_csCodice.GetLength() != 11)
			return FALSE;
		// SOLO CIFRE NUMERICHE
		for(int k = 0; k < m_csCodice.GetLength(); k++)
		{
			char c = m_csCodice.GetAt(k);
			if(c < 0x30 && c > 0x39)
				return FALSE;
		}
	}
	else
	{
		bRet = FALSE;
	}
	// CODICE DI CONTROLLO
	bRet = ValidaCarattereDiControllo();
	return bRet;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CAziendeView, CFormView)

CAziendeView::CAziendeView()
: CXFormView(CAziendeView::IDD)
{
	//{{AFX_DATA_INIT(CAziendeView)
	m_strRagioneSociale = _T("");
	m_strCAP = _T("");
	m_strCitta = _T("");
	m_strCodiceFiscale = _T("");
	m_strEMail = _T("");
	m_strCodiceDestinatario = _T("");
	m_strPEC = _T("");
	m_strFax = _T("");
	m_strIndirizzo = _T("");
	m_strPIVA = _T("");
	m_strProvincia = _T("");
	m_strTelefono = _T("");
	m_bAziendaImportante = FALSE;
	m_strABI = _T("");
	m_strBanca = _T("");
	m_strCAB = _T("");
	m_strNoteAzienda = _T("");
	m_nVerbaliDaFatturare = 0;
	m_nVerbaliAperti = 0;
	m_nTotaleVerbali = 0;
	m_strCodiceAzienda = _T("");
	m_dSconto = 0.0;
	m_bListinoGenerale = FALSE;
	m_bPrivato = FALSE;
	m_strCellulare = _T("");
	m_csCap_Spedizione = _T("");
	m_csIndirizzo_Spedizione = _T("");
	m_csCitta_Spedizione = _T("");
	m_csProvincia_Spedizione = _T("");
	//}}AFX_DATA_INIT

	m_dati_aziende = new CDatiAziende;
	m_pCodice_Aziende_Remoto = NULL;
	m_pAziendeRemoteSet = NULL;
	m_bCodiceFiscaleValido = TRUE;
}

CAziendeView::~CAziendeView()
{
	delete m_dati_aziende;
}


void CAziendeView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAziendeView)
	DDX_Control(pDX, IDC_COMBO_CAP, m_cbxCAP);
	DDX_Control(pDX, IDC_BUTTON_MODIFICA_VFARLOCCO, m_BtnModificaVerbale);
	DDX_Control(pDX, IDC_STATIC_VERBALI_FARLOCCHI, m_StaticVerbaliFarlocchi);
	DDX_Control(pDX, IDC_BUTTON_ELIMINA_VFARLOCCO, m_BtnEliminaVerbale);
	DDX_Control(pDX, IDC_BUTTON_GENERA_CODICE, m_btGenera_Codice);
	DDX_Control(pDX, IDC_BUTTON_INSERT, m_BtnInserisciVerbali);
	DDX_Control(pDX, IDC_EDIT_CAP_SPEDIZIONE, m_EditCap_Spedizione);
	DDX_Control(pDX, IDC_EDIT_CITTA_SPEDIZIONE, m_EditCitta_Spedizione);
	DDX_Control(pDX, IDC_EDIT_PROVINCIA_SPEDIZIONE, m_EditProvincia_Spedizione);
	DDX_Control(pDX, IDC_EDIT_INDIRIZZO_SPEDIZIONE, m_EditIndirizzo_Spedizione);
	DDX_Control(pDX, IDC_BUTTON_ARCHIVIO_AZIENDE, m_btArchivio_Aziende);
	DDX_Control(pDX, IDC_BUTTON_DB_REMOTO, m_btDBRemoto);
	DDX_Control(pDX, IDC_EDIT_CELL, m_EditCellulare);
	DDX_Control(pDX, IDC_CHECK_PRIVATO, m_BtnPrivato);
	DDX_Control(pDX, IDC_EDIT_TOTALEVERBALI, m_EditTotaleVerbali);
	DDX_Control(pDX, IDC_CHECK_LISTINOGENERALE, m_BtnListinoGenerale);
	DDX_Control(pDX, IDC_EDIT_SCONTO, m_EditSconto);
	DDX_Control(pDX, IDC_EDIT_DAFATTURARE, m_EditVerbaliDaFatturare);
	DDX_Control(pDX, IDC_EDIT_CAB, m_EditCAB);
	DDX_Control(pDX, IDC_EDIT_BANCA, m_EditBanca);
	DDX_Control(pDX, IDC_EDIT_APERTI, m_EditVerbaliAperti);
	DDX_Control(pDX, IDC_EDIT_ABI, m_EditABI);
	DDX_Control(pDX, IDC_COMBO_TIPOPAGAMENTO, m_ComboTipoPagamento);
	DDX_Control(pDX, IDC_EDIT_TELEFONO, m_EditTelefono);
	DDX_Control(pDX, IDC_EDIT_RAG_SOC, m_EditRagioneSociale);
	DDX_Control(pDX, IDC_EDIT_PROVINCIA, m_EditProvincia);
	DDX_Control(pDX, IDC_EDIT_PIVA, m_EditPIVA);
	DDX_Control(pDX, IDC_EDIT_NOTE, m_EditNote);
	DDX_Control(pDX, IDC_EDIT_INDIRIZZO, m_EditIndirizzo);
	DDX_Control(pDX, IDC_EDIT_FAX, m_EditFax);
	DDX_Control(pDX, IDC_EDIT_EMAIL, m_EditEMail);
	DDX_Control(pDX, IDC_EDIT_CODFISC, m_EditCodiceFiscale);
	DDX_Control(pDX, IDC_EDIT_CODE, m_EditCodiceAzienda);
	DDX_Control(pDX, IDC_EDIT_PEC, m_EditPEC);
	DDX_Control(pDX, IDC_EDIT_CODDEST, m_EditCodiceDestinatario);
	DDX_Control(pDX, IDC_EDIT_CITTA, m_EditCitta);
	DDX_Control(pDX, IDC_EDIT_CAP, m_EditCAP);
	DDX_Control(pDX, IDC_CHECK_IMPORTANTE, m_BtnAziendaImportante);
	DDX_Text(pDX, IDC_EDIT_RAG_SOC, m_strRagioneSociale);
	DDV_MaxChars(pDX, m_strRagioneSociale, 64);
	DDX_Text(pDX, IDC_EDIT_CAP, m_strCAP);
	DDV_MaxChars(pDX, m_strCAP, 8);
	DDX_Text(pDX, IDC_EDIT_CITTA, m_strCitta);
	DDV_MaxChars(pDX, m_strCitta, 32);
	DDX_Text(pDX, IDC_EDIT_CODFISC, m_strCodiceFiscale);
	DDV_MaxChars(pDX, m_strCodiceFiscale, 16);
	DDX_Text(pDX, IDC_EDIT_EMAIL, m_strEMail);
	DDV_MaxChars(pDX, m_strEMail, 200);
	DDX_Text(pDX, IDC_EDIT_CODDEST, m_strCodiceDestinatario);
	DDV_MaxChars(pDX, m_strCodiceDestinatario, 7);
	DDX_Text(pDX, IDC_EDIT_PEC, m_strPEC);
	DDV_MaxChars(pDX, m_strPEC, 200);
	DDX_Text(pDX, IDC_EDIT_FAX, m_strFax);
	DDV_MaxChars(pDX, m_strFax, 32);
	DDX_Text(pDX, IDC_EDIT_INDIRIZZO, m_strIndirizzo);
	DDV_MaxChars(pDX, m_strIndirizzo, 32);
	DDX_Text(pDX, IDC_EDIT_PIVA, m_strPIVA);
	DDV_MaxChars(pDX, m_strPIVA, 16);
	DDX_Text(pDX, IDC_EDIT_PROVINCIA, m_strProvincia);
	DDV_MaxChars(pDX, m_strProvincia, 4);
	DDX_Text(pDX, IDC_EDIT_TELEFONO, m_strTelefono);
	DDV_MaxChars(pDX, m_strTelefono, 32);
	DDX_Check(pDX, IDC_CHECK_IMPORTANTE, m_bAziendaImportante);
	DDX_Text(pDX, IDC_EDIT_ABI, m_strABI);
	DDV_MaxChars(pDX, m_strABI, 8);
	DDX_Text(pDX, IDC_EDIT_BANCA, m_strBanca);
	DDV_MaxChars(pDX, m_strBanca, 64);
	DDX_Text(pDX, IDC_EDIT_CAB, m_strCAB);
	DDV_MaxChars(pDX, m_strCAB, 8);
	DDX_Text(pDX, IDC_EDIT_NOTE, m_strNoteAzienda);
	DDV_MaxChars(pDX, m_strNoteAzienda, 512);
	DDX_Text(pDX, IDC_EDIT_DAFATTURARE, m_nVerbaliDaFatturare);
	DDX_Text(pDX, IDC_EDIT_APERTI, m_nVerbaliAperti);
	DDX_Text(pDX, IDC_EDIT_TOTALEVERBALI, m_nTotaleVerbali);
	DDX_Control(pDX, IDC_LIST_VERBALI, m_ListCtrlVerbali);
	DDX_Text(pDX, IDC_EDIT_CODE, m_strCodiceAzienda);
	DDX_Text(pDX, IDC_EDIT_SCONTO, m_dSconto);
	DDV_MinMaxDouble(pDX, m_dSconto, 0., 100.);
	DDX_Check(pDX, IDC_CHECK_LISTINOGENERALE, m_bListinoGenerale);
	DDX_Check(pDX, IDC_CHECK_PRIVATO, m_bPrivato);
	DDX_Text(pDX, IDC_EDIT_CELL, m_strCellulare);
	DDV_MaxChars(pDX, m_strCellulare, 32);
	DDX_Text(pDX, IDC_EDIT_CAP_SPEDIZIONE, m_csCap_Spedizione);
	DDV_MaxChars(pDX, m_csCap_Spedizione, 8);
	DDX_Text(pDX, IDC_EDIT_INDIRIZZO_SPEDIZIONE, m_csIndirizzo_Spedizione);
	DDV_MaxChars(pDX, m_csIndirizzo_Spedizione, 64);
	DDX_Text(pDX, IDC_EDIT_CITTA_SPEDIZIONE, m_csCitta_Spedizione);
	DDV_MaxChars(pDX, m_csCitta_Spedizione, 32);
	DDX_Text(pDX, IDC_EDIT_PROVINCIA_SPEDIZIONE, m_csProvincia_Spedizione);
	DDV_MaxChars(pDX, m_csProvincia_Spedizione, 4);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAziendeView, CXFormView)
	//{{AFX_MSG_MAP(CAziendeView)
	ON_COMMAND(ID_TROVA, OnTrova)
	ON_BN_CLICKED(IDC_CHECK_PRIVATO, OnCheckPrivato)
	ON_EN_SETFOCUS(IDC_EDIT_CODE, OnSetfocusEditCode)
	ON_BN_CLICKED(IDC_BUTTON_ARCHIVIO_AZIENDE, OnButtonArchivioAziende)
	ON_BN_CLICKED(IDC_BUTTON_DB_REMOTO, OnButtonDBRemoto)
	ON_BN_CLICKED(IDC_BUTTON_GENERA_CODICE, OnButtonGeneraCodice)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, OnButtonInsert)
	ON_BN_CLICKED(IDC_BUTTON_ELIMINA_VFARLOCCO, OnButtonEliminaVfarlocco)
	ON_BN_CLICKED(IDC_BUTTON_MODIFICA_VFARLOCCO, OnButtonModificaVfarlocco)
	ON_COMMAND(ID_BUTTON_AGGIORNA, OnButtonAggiorna)
	ON_COMMAND(ID_REPORT_VERBALI, OnReportVerbali)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_VERBALI, OnDblclkListVerbali)
	ON_COMMAND(ID_NUOVO, OnNuovo)
	ON_EN_KILLFOCUS(IDC_EDIT_PROVINCIA, OnKillfocusEditProvincia)
	ON_EN_KILLFOCUS(IDC_EDIT_CITTA, OnKillfocusEditCitta)
	ON_CBN_SELCHANGE(IDC_COMBO_CAP, OnSelchangeComboCap)
	ON_EN_KILLFOCUS(IDC_EDIT_INDIRIZZO, OnKillfocusEditIndirizzo)
	ON_BN_CLICKED(IDC_BUTTON_AGGIORNA, OnButtonUpdateFromDBR)
	ON_EN_KILLFOCUS(IDC_EDIT_CODFISC, OnKillfocusEditCodFisc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



void CAziendeView::OnInitialUpdate()
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  int nFontWidth = pApp->GetFontWidth();

  switch(pDoc->m_nSelectedTreeAziende)
  {
  case TREEITEM_AZIENDEIMPORTANTI:
    m_pSet = pDoc->m_pAziendeImportantiSet;
    break;
  case TREEITEM_AZIENDERECENTI:
    m_pSet = pDoc->m_pAziendeRecentiSet;
    break;
  default:
    m_pSet = pDoc->m_pAziendeSet;
    break;
  }
  CXFormView::m_pSet = m_pSet;
	CXFormView::OnInitialUpdate();

  int i, n;
	DWORD style;
  m_pTipiPagamentoSet = pDoc->m_pTipiPagamentoSet;
  for(SET_START(m_pTipiPagamentoSet); !m_pTipiPagamentoSet->IsEOF(); m_pTipiPagamentoSet->MoveNext())
  {
  	i = m_ComboTipoPagamento.AddString(m_pTipiPagamentoSet->m_Nome);
  	m_ComboTipoPagamento.SetItemData(i, m_pTipiPagamentoSet->m_Codice);
  }
  n = pApp->GetProfileInt(CONFIGURAZIONE, TIPO_PAGAMENTO_DEFAULT, 1);
  for(i = 0; i < m_ComboTipoPagamento.GetCount(); i++)
  {
    if(m_ComboTipoPagamento.GetItemData(i) == (DWORD)n)
      break;
  }
  if(i < m_ComboTipoPagamento.GetCount())
    m_ComboTipoPagamento.SetCurSel(i);
  else
    m_ComboTipoPagamento.SetCurSel(-1);
  style = m_ListCtrlVerbali.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT;
	m_ListCtrlVerbali.SetExtendedStyle(style);
  m_ListCtrlVerbali.InsertColumn(0,"", LVCFMT_LEFT, 0);
  m_ListCtrlVerbali.InsertColumn(1, "Numero", LVCFMT_CENTER, 14 * nFontWidth, -1);
	m_ListCtrlVerbali.InsertColumn(2, "Data", LVCFMT_LEFT, 16 * nFontWidth, -1);
	m_ListCtrlVerbali.InsertColumn(3, "Tipo", LVCFMT_LEFT, 40 * nFontWidth, -1);
	m_ListCtrlVerbali.InsertColumn(4, "Stato", LVCFMT_LEFT, 16 * nFontWidth, -1);
  CString str;
  str.Format("Verbali precedenti al %s", (CTime(CTime::GetCurrentTime().GetYear(), 1, 1,0, 0, 0)).Format("%d/%m/%y"));
  m_StaticVerbaliFarlocchi.SetWindowText(str);
  OnUpdate(this, 0, NULL);
}

void CAziendeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	 CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  
  switch(pDoc->m_nSelectedTreeAziende)
  {
  case TREEITEM_AZIENDEIMPORTANTI:
    if(!pDoc->m_pAziendeImportantiSet->IsBOF())
	    CXFormView::m_pSet = m_pSet = pDoc->m_pAziendeImportantiSet;
    break;
  case TREEITEM_AZIENDERECENTI:
    if(!pDoc->m_pAziendeRecentiSet->IsBOF())
	    CXFormView::m_pSet = m_pSet = pDoc->m_pAziendeRecentiSet;
    break;
  default:
    if(!pDoc->m_pAziendeSet->IsBOF())
      CXFormView::m_pSet = m_pSet = pDoc->m_pAziendeSet;
    break;
  }
	CXFormView::OnUpdate(pSender, lHint, pHint);
  
}


void CAziendeView::LoadCurRecord(BOOL bData)
{
  int i, n;
  if(bData)
  {
    // Carico i dati nella form
    m_strRagioneSociale				= m_pSet->m_RagioneSociale;
    m_strCodiceAzienda				= m_pSet->m_ID;
    m_strIndirizzo						= m_pSet->m_Indirizzo;
    m_strCAP									= m_pSet->m_CAP;
    m_strCitta								= m_pSet->m_Citta;
    m_strProvincia						= m_pSet->m_Provincia;
    m_strTelefono							= m_pSet->m_Telefono;
    m_strCellulare						= m_pSet->m_Cellulare;
    m_strEMail								= m_pSet->m_E_Mail;
    m_strFax									= m_pSet->m_Fax;
    m_strCodiceFiscale				= m_pSet->m_CodiceFiscale;
    m_strPIVA									= m_pSet->m_P_IVA;
    m_bAziendaImportante			= m_pSet->m_IsImportante;
    m_bPrivato								= m_pSet->m_Privato;
		m_csIndirizzo_Spedizione	= m_pSet->m_Indirizzo_Sped;
		m_csCap_Spedizione				= m_pSet->m_CAP_Sped;
		m_csCitta_Spedizione			= m_pSet->m_Citta_Sped;
		m_csProvincia_Spedizione	= m_pSet->m_Provincia_Sped;
    m_strCodiceDestinatario		= m_pSet->m_CodiceDestinatario;
    m_strPEC									= m_pSet->m_PEC;
    // Dati pagamento
    m_strBanca					= m_pSet->m_Banca;
    m_strABI						= m_pSet->m_ABI;
    m_strCAB						= m_pSet->m_CAB;
    m_dSconto						= m_pSet->m_Sconto;
    m_bListinoGenerale	= m_pSet->m_UsaTuttiListini;
    for(i = 0; i < m_ComboTipoPagamento.GetCount(); i++)
    {
      if(m_ComboTipoPagamento.GetItemData(i) == (DWORD)m_pSet->m_TipoPagamento)
        break;
    }
    // Note
    m_strNoteAzienda = m_pSet->m_Note;
    // Verbali aperti
    LoadVerbali(m_pSet->m_ID);
  }
  else
  {
	Clear(&i);
  }
	if(i < m_ComboTipoPagamento.GetCount())
	  m_ComboTipoPagamento.SetCurSel(i);
	else
  {
    n = ((CWinSigmaApp*)AfxGetApp())->GetProfileInt(CONFIGURAZIONE, TIPO_PAGAMENTO_DEFAULT, 1);
    for(i = 0; i < m_ComboTipoPagamento.GetCount(); i++)
    {
      if(m_ComboTipoPagamento.GetItemData(i) == (DWORD)n)
        break;
    }
    if(i < m_ComboTipoPagamento.GetCount())
      m_ComboTipoPagamento.SetCurSel(i);
    else
      m_ComboTipoPagamento.SetCurSel(-1);
  }
}

void CAziendeView::OnNuovo()
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();

  switch(pApp->GetViewMode())
	{
	  case MODE_VIEW:
      LoadCurRecord(FALSE);
		  pApp->SetViewMode(MODE_NEW);
  	  EnableControls(TRUE);
			UpdateData(FALSE);
			break;
		case MODE_EDIT:
		  MessageBeep(-1);
			break;
		case MODE_NEW:
			UpdateData();
			switch(AfxMessageBox("Salvare le modifiche ai dati?", MB_YESNOCANCEL))
			{
				case IDYES:
				  if(NewRecord())
					{
		        EnableControls(FALSE);
		        pApp->SetViewMode(MODE_VIEW);
					}
  				break;

				case IDNO:
					Clear();
					UpdateData(FALSE);
	        pApp->SetViewMode(MODE_VIEW);
 	        EnableControls(FALSE);
					break;

				default:
					break;
			}
      break;
	}
}

void CAziendeView::Clear(int* i)
{
	// Anagrafica
	m_strRagioneSociale.Empty();
	m_strCodiceAzienda.Empty();
	m_strIndirizzo.Empty();
	m_strCAP.Empty();
	m_strCitta.Empty();
	m_strProvincia.Empty();
	m_strTelefono.Empty();
	m_strCellulare.Empty();
	m_strEMail.Empty();
	m_strFax.Empty();	
	m_strCodiceFiscale.Empty();
	m_strPIVA.Empty();
	m_bAziendaImportante = FALSE;
	m_bPrivato = FALSE;
	m_csIndirizzo_Spedizione.Empty();
	m_csCap_Spedizione.Empty();
	m_csCitta_Spedizione.Empty();
	m_csProvincia_Spedizione.Empty();
	m_strCodiceDestinatario.Empty();
	m_strPEC.Empty();
	// Pagamenti
	m_strBanca.Empty();
	m_strABI.Empty();
	m_strCAB.Empty();
	m_dSconto = 0.0;
	if (i)
		*i = m_ComboTipoPagamento.GetCount();

	// Note
	m_strNoteAzienda.Empty();
	m_ListCtrlVerbali.DeleteAllItems();
}

BOOL CAziendeView::IsDataChanged()
{
  int nTipoPagamento;
  nTipoPagamento = m_ComboTipoPagamento.GetItemData(m_ComboTipoPagamento.GetCurSel());
  if(m_strRagioneSociale			!= m_pSet->m_RagioneSociale		||
     m_strCodiceAzienda				!= m_pSet->m_ID					||
     m_strIndirizzo					!= m_pSet->m_Indirizzo			||
     m_strCAP						!= m_pSet->m_CAP				||
     m_strCitta						!= m_pSet->m_Citta				||
     m_strProvincia					!= m_pSet->m_Provincia			||
     m_strTelefono					!= m_pSet->m_Telefono			||
     m_strCellulare					!= m_pSet->m_Cellulare			||        
     m_strEMail						!= m_pSet->m_E_Mail				||
     m_strFax						!= m_pSet->m_Fax				||
     m_strCodiceFiscale				!= m_pSet->m_CodiceFiscale		||
     m_strPIVA						!= m_pSet->m_P_IVA				||
     m_bAziendaImportante			!= m_pSet->m_IsImportante		||
     m_bPrivato						!= m_pSet->m_Privato			||
		 m_strCodiceDestinatario != m_pSet->m_CodiceDestinatario ||
		 m_strPEC != m_pSet->m_PEC ||
	 // Pagamento
     nTipoPagamento					!= m_pSet->m_TipoPagamento		||
     m_strBanca						!= m_pSet->m_Banca				||
     m_strABI						!= m_pSet->m_ABI				||
     m_strCAB						!= m_pSet->m_CAB				||
     m_dSconto						!= m_pSet->m_Sconto				||
     m_bListinoGenerale				!= m_pSet->m_UsaTuttiListini	||
	 // Spedizione
	 m_csIndirizzo_Spedizione		!= m_pSet->m_Indirizzo_Sped		||
	 m_csCap_Spedizione				!= m_pSet->m_CAP_Sped			||
	 m_csCitta_Spedizione			!= m_pSet->m_Citta_Sped			||
	 m_csProvincia_Spedizione		!= m_pSet->m_Provincia_Sped		||
	 // Note
	 m_strNoteAzienda				!= m_pSet->m_Note)
     return TRUE;
  return FALSE;
}

BOOL CAziendeView::ValidateData()
{
  CString str;
  
  if ( ControllaCodice( m_strCodiceAzienda.Mid(0,3) ) != -1 )
  {
		AfxMessageBox("Attenzione: il 'Codice' dell'azienda può contenere solamente lettere e numeri.");
		return FALSE;
  }
  if(m_strRagioneSociale.GetLength() < 2)
  {
	  AfxMessageBox("Attenzione: il nome dell'azienda deve essere di almeno due lettere");
	  return FALSE;
  }
  if(m_strCodiceAzienda.GetLength() < 2)
  {
	  AfxMessageBox("Digitare un codice azienda valido");
	  return FALSE;
  }
  if(!m_strCAP.IsEmpty() && m_strCAP.FindOneOf(STR_VERIFY_LETTERE) >= 0)
  {
    AfxMessageBox("Verificare il campo CAP");
    return FALSE;
  }
  if(!m_strTelefono.IsEmpty() && m_strTelefono.FindOneOf(STR_VERIFY_LETTERE) >= 0)
  {
    AfxMessageBox("Verificare il campo telefono");
    return FALSE;
  }
  if(!m_strCellulare.IsEmpty() && m_strCellulare.FindOneOf(STR_VERIFY_LETTERE) >= 0)
  {
    AfxMessageBox("Verificare il campo cellulare");
    return FALSE;
  }
  if(!m_strFax.IsEmpty() && m_strFax.FindOneOf(STR_VERIFY_LETTERE) >= 0)
  {
    AfxMessageBox("Verificare il campo fax");
    return FALSE;
  }
	str = m_strPIVA;
	str.TrimLeft("0123456789");
  if(!m_strPIVA.IsEmpty() && !str.IsEmpty())
  {
    AfxMessageBox("La partita IVA non contiene solo cifre.");
    return FALSE;
  }
  if((!m_strPIVA.IsEmpty() && (m_strPIVA.GetLength() != 11) && (m_strPIVA.GetLength() > 0))|| (VerificaPI() == FALSE))
  {
    AfxMessageBox("La partita IVA non è corretta.");
    return FALSE;
  }
  if(!m_strABI.IsEmpty() && m_strABI.FindOneOf(STR_VERIFY_LETTERE) >= 0)
  {
    AfxMessageBox("Verificare il campo ABI");
    return FALSE;
  }
  if(!m_strCAB.IsEmpty() && m_strCAB.FindOneOf(STR_VERIFY_LETTERE) >= 0)
  {
    AfxMessageBox("Verificare il campo CAB");
    return FALSE;
  }
  return TRUE;
}

BOOL CAziendeView::ValidateCodiceFiscale(void)
{
  CString str;
	BOOL bRet = TRUE;

	// non valida il codice fiscale se è vuoto
	if(m_strCodiceFiscale.IsEmpty())
	{
		return TRUE;
	}

	CCodiceFiscale cf(m_strCodiceFiscale);
	bRet = cf.Valida();

	if(bRet == FALSE)
	{
		CString msg = "CODICE FISCALE non valido";
		if(AfxMessageBox(msg) == IDOK)
		{
			m_EditCodiceFiscale.SetFocus();
			m_EditCodiceFiscale.SetSel(0, -1);
		}
	}

  return bRet;
}


BOOL CAziendeView::VerificaPI(void)
{
  int i, c, s;

  if (  m_strPIVA.GetLength() == 0 )
    return TRUE;

  if( m_strPIVA.GetLength() != 11 )
      return FALSE;

  for( i=0; i<11; i++ )
  {
    if( ! isdigit(m_strPIVA.GetBuffer(100)[i]) )
        return FALSE;
  }

  s = 0;
  for( i=0; i<=9; i+=2 )
      s += m_strPIVA.GetBuffer(100)[i] - '0';
  for( i=1; i<=9; i+=2 ){
      c = 2*( m_strPIVA.GetBuffer(100)[i] - '0' );
      if( c > 9 )  c = c - 9;
      s += c;
  }
  if( ( 10 - s%10 )%10 != m_strPIVA.GetBuffer(100)[10] - '0' )
      return FALSE;
  
  return TRUE;
}

BOOL CAziendeView::NewRecord()
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	int n;
	
	if(!m_bCodiceFiscaleValido || !ValidateData())
		return FALSE;
	m_ListCtrlVerbali.DeleteAllItems();

	if(CheckIDExist(m_strCodiceAzienda) == TRUE)        
	{
		CString str("Codice azienda già presente.");
		AfxMessageBox(str, MB_OK);
		return FALSE;
	}

  try
  {
    m_pSet->AddNew();
    // Anagrafica
    m_pSet->m_RagioneSociale	= m_strRagioneSociale;
    m_pSet->m_ID				= m_strCodiceAzienda;
    m_pSet->m_Indirizzo			= m_strIndirizzo;
    m_pSet->m_CAP				= m_strCAP;
    m_pSet->m_Citta				= m_strCitta;
    m_pSet->m_Provincia			= m_strProvincia;
    m_pSet->m_Telefono			= m_strTelefono;
    m_pSet->m_Cellulare			= m_strCellulare;
    m_pSet->m_E_Mail			= m_strEMail;
    m_pSet->m_Fax				= m_strFax;
    m_pSet->m_CodiceFiscale		= m_strCodiceFiscale;
    m_pSet->m_CodiceDestinatario		= m_strCodiceDestinatario;
    m_pSet->m_PEC		= m_strPEC;

		if(CheckPIVAExist(m_strPIVA) == TRUE)        
		{
			CString str("Partita IVA già presente. Vuoi ugualmente procedere all'inserimento?");
			if (AfxMessageBox(str, MB_YESNO) == IDNO)
				return FALSE;
		}

		m_pSet->m_P_IVA	= m_strPIVA;

    m_pSet->m_IsImportante		= (BYTE)m_bAziendaImportante;
    m_pSet->m_UsaTuttiListini	= m_bListinoGenerale;
    m_pSet->m_Privato			= (BYTE)m_bPrivato;
		m_pSet->m_Indirizzo_Sped	= m_csIndirizzo_Spedizione;
		m_pSet->m_CAP_Sped			= m_csCap_Spedizione;
		m_pSet->m_Citta_Sped		= m_csCitta_Spedizione;
		m_pSet->m_Provincia_Sped	= m_csProvincia_Spedizione;
    // Note
    m_pSet->m_Note				= m_strNoteAzienda;
    // Pagamento
    if((n = m_ComboTipoPagamento.GetCurSel()) != -1)
      m_pSet->m_TipoPagamento		= m_ComboTipoPagamento.GetItemData(n);
    else
      m_pSet->m_TipoPagamento = pApp->GetProfileInt(CONFIGURAZIONE, TIPO_PAGAMENTO_DEFAULT, 1);
    m_pSet->m_ABI				= m_strABI;
    m_pSet->m_CAB				= m_strCAB;
    m_pSet->m_Banca				= m_strBanca;
    m_pSet->m_Sconto			= m_dSconto;
    m_pSet->Update();
  }
	catch(CDBException* e)
	{
		CString strError;  

    if(pApp->DecodeDBError(e->m_strStateNativeOrigin) == ER_DUP_ENTRY)
			strError.Format("Codice o Partita IVA già presenti.");
    else
			strError = e->m_strError;
		AfxMessageBox(strError);
		return FALSE;
	}

	// aggiorno l'eventuale DB remoto
	NewRecordRemoto(m_strCodiceAzienda, TRUE);

  LoadVerbali(m_pSet->m_ID);
  // Ricarico gli alberi
  pApp->ReloadTree(TREELABEL_AZIENDEALFABETICA, -1);
  pApp->ReloadTree(TREELABEL_AZIENDEIMPORTANTI, -1);
  pApp->ReloadTree(TREELABEL_AZIENDERECENTI, -1);
  return TRUE;
}

BOOL CAziendeView::NewRecordRemoto(CString& strID, BOOL bCheckPresent)
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	int n;

	if(pApp->IsDBRemoto() == 0)
		return FALSE;

	m_pAziendeRemoteSet = new CAziendeSet(&pApp->m_dbr);  
	m_pAziendeRemoteSet->m_strSort = "RagioneSociale ASC";
	if(bCheckPresent)
	{
		m_pAziendeRemoteSet->m_strFilter.Format("ID LIKE '%s'", strID);
		m_pAziendeRemoteSet->Open();
	
		if(!m_pAziendeRemoteSet->IsBOF())
		{
			CString str("Codice gia' presente nell'archivio remoto.");
			AfxMessageBox(str, MB_OK);
			m_pAziendeRemoteSet->Close();
			delete m_pAziendeRemoteSet;
			return FALSE;
		}
		m_pAziendeRemoteSet->Close();
	}

	// riapro il recordset remoto
	m_pAziendeRemoteSet->m_strFilter.Format("Codice > 0");
	m_pAziendeRemoteSet->Open();

  try
  {
    m_pAziendeRemoteSet->AddNew();
    // Anagrafica
    m_pAziendeRemoteSet->m_RagioneSociale		= m_strRagioneSociale;
    m_pAziendeRemoteSet->m_ID								= m_strCodiceAzienda;
    m_pAziendeRemoteSet->m_Indirizzo				= m_strIndirizzo;
    m_pAziendeRemoteSet->m_CAP							= m_strCAP;
    m_pAziendeRemoteSet->m_Citta						= m_strCitta;
    m_pAziendeRemoteSet->m_Provincia				= m_strProvincia;
    m_pAziendeRemoteSet->m_Telefono					= m_strTelefono;
    m_pAziendeRemoteSet->m_Cellulare				= m_strCellulare;
    m_pAziendeRemoteSet->m_E_Mail						= m_strEMail;
    m_pAziendeRemoteSet->m_Fax							= m_strFax;
    m_pAziendeRemoteSet->m_CodiceFiscale		= m_strCodiceFiscale;
		m_pAziendeRemoteSet->m_P_IVA						=	m_strPIVA;
    m_pAziendeRemoteSet->m_IsImportante			= (BYTE)m_bAziendaImportante;
    m_pAziendeRemoteSet->m_UsaTuttiListini	= m_bListinoGenerale;
    m_pAziendeRemoteSet->m_Privato					= (BYTE)m_bPrivato;
		m_pAziendeRemoteSet->m_Indirizzo_Sped		= m_csIndirizzo_Spedizione;
		m_pAziendeRemoteSet->m_CAP_Sped					= m_csCap_Spedizione;
		m_pAziendeRemoteSet->m_Citta_Sped				= m_csCitta_Spedizione;
		m_pAziendeRemoteSet->m_Provincia_Sped		= m_csProvincia_Spedizione;
    // Note
    m_pAziendeRemoteSet->m_Note							= m_strNoteAzienda;
    // Pagamento
    if((n = m_ComboTipoPagamento.GetCurSel()) != -1)
      m_pAziendeRemoteSet->m_TipoPagamento	= m_ComboTipoPagamento.GetItemData(n);
    else
      m_pAziendeRemoteSet->m_TipoPagamento	= pApp->GetProfileInt(CONFIGURAZIONE, TIPO_PAGAMENTO_DEFAULT, 1);
    m_pAziendeRemoteSet->m_ABI							= m_strABI;
    m_pAziendeRemoteSet->m_CAB							= m_strCAB;
    m_pAziendeRemoteSet->m_Banca						= m_strBanca;
    m_pAziendeRemoteSet->m_Sconto						= m_dSconto;
    m_pAziendeRemoteSet->Update();
  }
	catch(CDBException* e)
	{
		CString strError;
		strError = e->m_strError;
		AfxMessageBox(strError);
		m_pAziendeRemoteSet->Close();
		delete m_pAziendeRemoteSet;
		return FALSE;
	}
	m_pAziendeRemoteSet->Close();
	delete m_pAziendeRemoteSet;
  return TRUE;
}

BOOL CAziendeView::SaveRecord()
{
  UpdateData();
  long nCode;
  int n;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

 	switch(AfxMessageBox("Salvare le modifiche ai dati?", MB_YESNOCANCEL))
	{
	  case IDYES:
    	if(!m_bCodiceFiscaleValido || !ValidateData())
    	  return FALSE;
      nCode = m_pSet->m_Codice;
      try
      {
        m_pSet->Edit();
        m_pSet->m_RagioneSociale	= m_strRagioneSociale;
        m_pSet->m_ID							= m_strCodiceAzienda;
        m_pSet->m_Indirizzo				= m_strIndirizzo;
        m_pSet->m_CAP							= m_strCAP;
        m_pSet->m_Citta						= m_strCitta;
        m_pSet->m_Provincia				= m_strProvincia;
        m_pSet->m_Telefono				= m_strTelefono;
        m_pSet->m_Cellulare				= m_strCellulare;
        m_pSet->m_E_Mail					= m_strEMail;
        m_pSet->m_Fax							= m_strFax;
        m_pSet->m_CodiceFiscale		= m_strCodiceFiscale;
        m_pSet->m_CodiceDestinatario		= m_strCodiceDestinatario;
        m_pSet->m_PEC							= m_strPEC;

				// controllo la P.IVA solo se e' stata modificata
				if(m_strPIVA.CompareNoCase(m_pSet->m_P_IVA))
				{
					if (CheckPIVAExist(m_strPIVA) == TRUE)        
					{
						CString str("Partita IVA già presente. Vuoi ugualmente procedere all'inserimento?");
						if (AfxMessageBox(str, MB_YESNO) == IDNO)
						{
							LoadCurRecord(TRUE);
							UpdateData(FALSE);
							return TRUE;
						}
					}
				}
				m_pSet->m_P_IVA	= m_strPIVA;

        m_pSet->m_IsImportante		= (BYTE)m_bAziendaImportante;
        m_pSet->m_UsaTuttiListini = m_bListinoGenerale;
        m_pSet->m_Privato					= (BYTE)m_bPrivato;
				m_pSet->m_Indirizzo_Sped	= m_csIndirizzo_Spedizione;
				m_pSet->m_CAP_Sped				= m_csCap_Spedizione;
				m_pSet->m_Citta_Sped			= m_csCitta_Spedizione;
				m_pSet->m_Provincia_Sped	= m_csProvincia_Spedizione;
        // Note
        m_pSet->m_Note            = m_strNoteAzienda;
        // Pagamento
        if((n = m_ComboTipoPagamento.GetCurSel()) != -1)
          m_pSet->m_TipoPagamento		= m_ComboTipoPagamento.GetItemData(n);
        else
          m_pSet->m_TipoPagamento = pApp->GetProfileInt(CONFIGURAZIONE, TIPO_PAGAMENTO_DEFAULT, 1);
        m_pSet->m_ABI							= m_strABI;
        m_pSet->m_CAB							= m_strCAB;
        m_pSet->m_Banca						= m_strBanca;
        m_pSet->m_Sconto					= m_dSconto;
        m_pSet->Update();
      }
    	catch(CDBException* e)
    	{
    		CString strError;

        if(pApp->DecodeDBError(e->m_strStateNativeOrigin) == ER_DUP_ENTRY)
    			strError.Format("La partita IVA %s corriponde\nad un altro cliente. Verificare i dati inseriti.",
    			                m_strPIVA);
        else
    			strError = e->m_strError;
    		AfxMessageBox(strError);
    		return FALSE;
    	}
      pApp->ReloadTree(TREELABEL_AZIENDERECENTI, nCode);
      pApp->ReloadTree(TREELABEL_AZIENDEIMPORTANTI, nCode);
      pApp->ReloadTree(TREELABEL_AZIENDEALFABETICA, nCode);
		  break;
	case IDNO:
      LoadCurRecord(TRUE);
      UpdateData(FALSE);
		  break;
		default:
		  return FALSE;
	}

	// aggiorno l'eventuale DB remoto
	SaveRecordRemoto(m_strCodiceAzienda);

	return TRUE;
}

BOOL CAziendeView::SaveRecordRemoto(CString& strID)
{
  int n;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

	if(pApp->IsDBRemoto() == 0)
		return FALSE;

  m_pAziendeRemoteSet = new CAziendeSet(&pApp->m_dbr);  
  m_pAziendeRemoteSet->m_strSort = "RagioneSociale ASC";
  m_pAziendeRemoteSet->m_strFilter.Format("ID LIKE '%s'", strID);
  m_pAziendeRemoteSet->Open();

	if(m_pAziendeRemoteSet->IsBOF())
	{
		// record non presente nel DB remoto
		m_pAziendeRemoteSet->Close();
		delete m_pAziendeRemoteSet;
		CString str("Azienda non presente nell'archivio remoto. Procedere all'inserimento?");
		if (AfxMessageBox(str, MB_YESNO) == IDNO)
			return FALSE;
		// aggiungo il record nel DB remoto
		NewRecordRemoto(strID, FALSE);
		return TRUE;
	}

	try
	{
		m_pAziendeRemoteSet->Edit();
		m_pAziendeRemoteSet->m_RagioneSociale		= m_strRagioneSociale;
		m_pAziendeRemoteSet->m_ID								= m_strCodiceAzienda;
		m_pAziendeRemoteSet->m_Indirizzo				= m_strIndirizzo;
		m_pAziendeRemoteSet->m_CAP							= m_strCAP;
		m_pAziendeRemoteSet->m_Citta						= m_strCitta;
		m_pAziendeRemoteSet->m_Provincia				= m_strProvincia;
		m_pAziendeRemoteSet->m_Telefono					= m_strTelefono;
		m_pAziendeRemoteSet->m_Cellulare				= m_strCellulare;
		m_pAziendeRemoteSet->m_E_Mail						= m_strEMail;
		m_pAziendeRemoteSet->m_Fax							= m_strFax;
		m_pAziendeRemoteSet->m_CodiceFiscale		= m_strCodiceFiscale;
		m_pAziendeRemoteSet->m_P_IVA						= m_strPIVA;
		m_pAziendeRemoteSet->m_IsImportante			= (BYTE)m_bAziendaImportante;
		m_pAziendeRemoteSet->m_UsaTuttiListini	= m_bListinoGenerale;
		m_pAziendeRemoteSet->m_Privato					= (BYTE)m_bPrivato;
		m_pAziendeRemoteSet->m_Indirizzo_Sped		= m_csIndirizzo_Spedizione;
		m_pAziendeRemoteSet->m_CAP_Sped					= m_csCap_Spedizione;
		m_pAziendeRemoteSet->m_Citta_Sped				= m_csCitta_Spedizione;
		m_pAziendeRemoteSet->m_Provincia_Sped		= m_csProvincia_Spedizione;
		// Note
		m_pAziendeRemoteSet->m_Note							= m_strNoteAzienda;
		// Pagamento
		if((n = m_ComboTipoPagamento.GetCurSel()) != -1)
			m_pAziendeRemoteSet->m_TipoPagamento	= m_ComboTipoPagamento.GetItemData(n);
		else
			m_pAziendeRemoteSet->m_TipoPagamento	= pApp->GetProfileInt(CONFIGURAZIONE, TIPO_PAGAMENTO_DEFAULT, 1);
		m_pAziendeRemoteSet->m_ABI							= m_strABI;
		m_pAziendeRemoteSet->m_CAB							= m_strCAB;
		m_pAziendeRemoteSet->m_Banca						= m_strBanca;
		m_pAziendeRemoteSet->m_Sconto						= m_dSconto;
		m_pAziendeRemoteSet->Update();
	}
	catch(CDBException* e)
	{
		CString strError;
		strError = e->m_strError;
		AfxMessageBox(strError);
		m_pAziendeRemoteSet->Close();
		delete m_pAziendeRemoteSet;
 		return FALSE;
 	}
	m_pAziendeRemoteSet->Close();
	delete m_pAziendeRemoteSet;
	return TRUE;
}

BOOL CAziendeView::CheckIDExist(CString &strID)
{
	BOOL ret = FALSE;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CAziendeSet* aziende = NULL;

	aziende = new CAziendeSet(&pApp->m_db);
	aziende->m_strFilter.Format("ID LIKE '%s'", strID);
	aziende->Open();

	if(!aziende->IsBOF())
	{
		ret = TRUE;
	}
	aziende->Close();
	delete aziende;	
	return ret;
}

BOOL CAziendeView::CheckPIVAExist(CString strPIVA)
{
	BOOL ret = FALSE;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CAziendeSet* aziende = NULL;

	if(strPIVA.IsEmpty())
		return FALSE;
	aziende = new CAziendeSet(&pApp->m_db);
	aziende->m_strFilter.Format("P_IVA LIKE '%s%%'", strPIVA);
	aziende->Open();

	if(!aziende->IsBOF())
	{
		ret = TRUE;
	}
	aziende->Close();
	delete aziende;	
	return ret;
}

BOOL CAziendeView::DeleteRecord()
{
  if(!m_pSet->IsBOF())
	{
    long nCode;
    CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  	CString str;
    if(!m_pSet->m_Privato)
    {
      nCode = m_pSet->m_Codice;
      AfxMessageBox("Attenzione: è possibile eliminare solo soggetti privati.");
      return FALSE;
    }
		str.Format("Eliminare %s (Codice %s)?", m_strRagioneSociale, m_strCodiceAzienda);

		if(AfxMessageBox(str, MB_YESNO) == IDYES)
		{
      nCode = m_pSet->m_Codice;
      m_pSet->Delete();
			// cancello il record dal DB remoto
			DeleteRecordRemoto(m_strCodiceAzienda);
      pApp->ReloadTree(TREELABEL_AZIENDERECENTI, nCode);
      pApp->ReloadTree(TREELABEL_AZIENDEIMPORTANTI, nCode);
      pApp->ReloadTree(TREELABEL_AZIENDEALFABETICA, nCode);
    	return TRUE;
		}
    return FALSE;
	}
	return FALSE;
}

BOOL CAziendeView::DeleteRecordRemoto(CString& strID)
{
	BOOL ret = FALSE;
  int nCode;
 	CString str;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

	if(pApp->IsDBRemoto() == 0)
		return FALSE;

  m_pAziendeRemoteSet = new CAziendeSet(&pApp->m_dbr);  
  m_pAziendeRemoteSet->m_strSort = "RagioneSociale ASC";
  m_pAziendeRemoteSet->m_strFilter.Format("ID LIKE '%s'", strID);
  m_pAziendeRemoteSet->Open();
 
	if(!m_pAziendeRemoteSet->IsBOF())
	{
    if(!m_pAziendeRemoteSet->m_Privato)
    {
      AfxMessageBox("Attenzione: è possibile eliminare solo soggetti privati.");
    }
		else
		{
			nCode = m_pAziendeRemoteSet->m_Codice;
			m_pAziendeRemoteSet->Delete();
   		ret = TRUE;
		}
	}
  m_pAziendeRemoteSet->Close();
	delete m_pAziendeRemoteSet;
	return ret;
}

void CAziendeView::EnableControls(BOOL bEnable)
{
  // Anagrafica cliente
  m_EditRagioneSociale.EnableWindow(bEnable);
  m_EditCodiceAzienda.EnableWindow(bEnable);
  m_EditIndirizzo.EnableWindow(bEnable);
  m_EditCAP.EnableWindow(bEnable);
  m_cbxCAP.EnableWindow(bEnable);
  m_EditCitta.EnableWindow(bEnable);
  m_EditProvincia.EnableWindow(bEnable);
  m_EditTelefono.EnableWindow(bEnable);
  m_EditCellulare.EnableWindow(bEnable);
  m_EditEMail.EnableWindow(bEnable);
  m_EditFax.EnableWindow(bEnable);
  m_EditCodiceFiscale.EnableWindow(bEnable);
  m_EditPIVA.EnableWindow(bEnable);
  m_EditCodiceDestinatario.EnableWindow(bEnable);
  m_EditPEC.EnableWindow(bEnable);
  m_BtnAziendaImportante.EnableWindow(bEnable);  
  m_BtnListinoGenerale.EnableWindow(bEnable);
  m_BtnPrivato.EnableWindow(bEnable);
	m_EditIndirizzo_Spedizione.EnableWindow(bEnable);
	m_EditCap_Spedizione.EnableWindow(bEnable);
	m_EditCitta_Spedizione.EnableWindow(bEnable);
	m_EditProvincia_Spedizione.EnableWindow(bEnable);
	if (bEnable == TRUE)
	{
		if (((CWinSigmaApp*)AfxGetApp())->GetViewMode() == 1)
		{
			m_btArchivio_Aziende.EnableWindow(bEnable);
			if(((CWinSigmaApp*)AfxGetApp())->GetProfileInt("Configurazione", "EnableDBRSincro", 0) == 1)
			{
				m_btDBRemoto.EnableWindow(bEnable);
				((CButton*)GetDlgItem(IDC_BUTTON_AGGIORNA))->ShowWindow(SW_SHOWNORMAL);
				
			}
			else
			{
				m_btDBRemoto.EnableWindow(FALSE);
				((CButton*)GetDlgItem(IDC_BUTTON_AGGIORNA))->ShowWindow(SW_HIDE);
			}
			m_btGenera_Codice.EnableWindow(bEnable);
		}
	}
	else
	{
		m_btArchivio_Aziende.EnableWindow(FALSE);
		m_btDBRemoto.EnableWindow(FALSE);
		m_btGenera_Codice.EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_AGGIORNA))->ShowWindow(SW_HIDE);
	}

  // Pagamenti
  m_EditBanca.EnableWindow(bEnable);
  m_EditSconto.EnableWindow(bEnable);
  m_EditCAB.EnableWindow(bEnable);
  m_EditABI.EnableWindow(bEnable);
  m_ComboTipoPagamento.EnableWindow(bEnable);
  // Note
  m_EditNote.EnableWindow(bEnable);
  // Verbali in corso
//  m_ListCtrlVerbali.EnableWindow(bEnable);
  m_EditVerbaliAperti.EnableWindow(bEnable);
  m_EditVerbaliDaFatturare.EnableWindow(bEnable);
  m_EditTotaleVerbali.EnableWindow(bEnable);
  m_EditRagioneSociale.SetFocus();
  if(((CWinSigmaApp*)AfxGetApp())->GetViewMode() != MODE_NEW)
  {
    m_BtnInserisciVerbali.EnableWindow(bEnable);
    m_BtnModificaVerbale.EnableWindow(bEnable);
    m_BtnEliminaVerbale.EnableWindow(bEnable);
  }
  else
  {
    m_BtnInserisciVerbali.EnableWindow(FALSE);
    m_BtnModificaVerbale.EnableWindow(FALSE);
    m_BtnEliminaVerbale.EnableWindow(FALSE);
  }
}

CString  CAziendeView::GetToolTip(int nID)
{
  switch(nID)
	{
	  case ID_NUOVO:
    	return "Crea una nuova azienda\nNuova azienda";
		case ID_MODIFICA:
		  return "Consente la modifica dei dati di una azienda\nModifica azienda";
		case ID_ELIMINA:
		  return "Elimina l'azienda dall'archivio\nElimina azienda";
    default:
      return "";
	}
}

void CAziendeView::OnTrova() 
{
  CTrovaAziendaDlg dlg;
  CAziendeTreeCtrl* pTreeCtrl = &((CMainFrame*)GetParentFrame())->m_wndTreeAziende;
	
  dlg.m_strTipoRicerca = "Ricerca anagrafica";
  if(dlg.DoModal() == IDOK)
	{
    CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
    m_pSet = pDoc->m_pAziendeSet;
		pTreeCtrl->SelectItemData(NULL, dlg.m_pSet->m_Codice);
		SINCRONIZE(m_pSet, dlg.m_pSet->m_Codice);
	}
}

// carica la lista dei verbali che riguardano questa azienda
void CAziendeView::LoadVerbali(CString strID)
{
  int n;
  CString str;
  CTime date = CTime::GetCurrentTime();
  CVerbaliSet* pVerbaliSet = new CVerbaliSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
  str.Format("%d-1-1 00:00:00", date.GetYear());
  pVerbaliSet->m_strFilter.Format("(IDIntestatarioCertificato = '%s' OR IDIntestatarioFattura = '%s' OR IDImpresaRichiedente = '%s')", strID, strID, strID, str);  
  pVerbaliSet->m_strSort = "DataAccettazione,ProgressivoTotale DESC";
  pVerbaliSet->Open();
  m_nTotaleVerbali = 0;
  m_nVerbaliDaFatturare = 0;
  m_nVerbaliAperti = 0;
  n = 0;
  m_ListCtrlVerbali.DeleteAllItems();
  for(SET_START(pVerbaliSet); !pVerbaliSet->IsEOF(); pVerbaliSet->MoveNext())
  {
    if(pVerbaliSet->m_TipoVerbale == VERB_PER_FATTURA || pVerbaliSet->m_TipoVerbale == VERB_PER_NOTACREDITO)
      continue;
    // Aggiorno la lista dei verbali relativi all'azienda
    m_nTotaleVerbali++;
    n = m_ListCtrlVerbali.InsertItem(n, "");
    str.Format("%d/%d", pVerbaliSet->m_ProgressivoParziale, pVerbaliSet->m_ProgressivoTotale);
    m_ListCtrlVerbali.SetItemData(n, (DWORD)pVerbaliSet->m_Codice);
    m_ListCtrlVerbali.SetItemText(n, COLUMN_NUMERO, str);
    m_ListCtrlVerbali.SetItemText(n, COLUMN_DATA, pVerbaliSet->m_DataAccettazione.Format("%d/%m/%Y"));
    str.Empty();
    switch(pVerbaliSet->m_TipoVerbale)
    {
    case VERB_NON_IN_CONCESSIONE:
		case VERB_NC_PROVE_DI_CARICO :
		case VERB_NC_CONGL_BITUMINOSI	:
		case VERB_NC_INERTI	:
		case VERB_NC_MONITORAGGI :
		case VERB_NC_VARIE	:
		case VERB_NC_GEOTECNICA:
      str = "Verbale senza prove in concessione";
      break;
    case VERB_IN_CONCESSIONE:
      str = "Verbale con prove in concessione";
      break;
    case VERB_GEOLOGIA:
      str = "Verbale per prove geotecniche";
      break;
    case VERB_VECCHIO_PROG:
      str = "Verbale precedente al 1/1/2004";
      break;
    }
    m_ListCtrlVerbali.SetItemText(n, COLUMN_PROVE, str);
    if(pVerbaliSet->IsFieldNull(&pVerbaliSet->m_DataChiusura))
    {
      m_nVerbaliAperti++;
      m_ListCtrlVerbali.SetItemText(n, COLUMN_STATO, V_APERTO);
    }
    else
      m_ListCtrlVerbali.SetItemText(n, COLUMN_STATO, V_CHIUSO);
    if(!pVerbaliSet->IsFieldNull(&pVerbaliSet->m_NumeroFattura) && pVerbaliSet->m_NumeroFattura != 0)
      m_ListCtrlVerbali.SetItemText(n, COLUMN_STATO, V_FATTURATO);       
    else if(!pVerbaliSet->IsFieldNull(&pVerbaliSet->m_InFatturazione) && pVerbaliSet->m_InFatturazione == VERB_INFATT)
    {
      m_nVerbaliDaFatturare++;
      m_ListCtrlVerbali.SetItemText(n, COLUMN_STATO, V_DAFATTURARE);
    }
    if(pVerbaliSet->m_Annullato)
      m_ListCtrlVerbali.SetItemText(n, COLUMN_STATO, V_ANNULLATO);
  }
  pVerbaliSet->Close();
  delete pVerbaliSet;
}


void CAziendeView::OnCheckPrivato() 
{
  UpdateData();
}


void CAziendeView::OnSetfocusEditCode() 
{
  //UpdateData();
/*
  if(!m_strCodiceAzienda.IsEmpty())
    return;
  CAziendeSet* pAziendeSet = ((CWinSigmaDoc*)GetDocument())->m_pAziendeSet;
  // Genero il codice azienda
  CString str;
  CTime data;
  data = CTime::GetCurrentTime();
  str = m_strRagioneSociale.Left(3);
  str.MakeUpper();
  m_strCodiceAzienda.Format("%s%s", data.Format("%y"), str);
  for(SET_START(pAziendeSet); !pAziendeSet->IsEOF(); pAziendeSet->MoveNext())
  {
    if(pAziendeSet->m_ID == m_strCodiceAzienda)
      break;
  }
  if(!pAziendeSet->IsEOF())
  {
    str.Format("%s", data.Format("%M"));
    m_strCodiceAzienda += str;
  }
*/
  // Aggiorno la vista
  UpdateData(FALSE);
}

void CAziendeView::OnButtonArchivioAziende() 
{
	UpdateData();
	m_archivio_aziende = new CArchivioAziendeDlg(m_dati_aziende,this);
	if(m_archivio_aziende->DoModal() == IDOK)
	{
		m_strRagioneSociale				= m_dati_aziende->m_RagioneSociale;
		m_strIndirizzo						= m_dati_aziende->m_Indirizzo;
		m_csIndirizzo_Spedizione	= m_dati_aziende->m_Indirizzo_Sped;
		m_strCAP									=	m_dati_aziende->m_CAP;
		m_csCap_Spedizione				=	m_dati_aziende->m_CAP_Sped;
		m_strCitta								= m_dati_aziende->m_Citta;
		m_csCitta_Spedizione			= m_dati_aziende->m_Citta_Sped;
		m_strProvincia						= m_dati_aziende->m_Provincia;
		m_csProvincia_Spedizione	= m_dati_aziende->m_Provincia_Sped;
		m_strABI									= m_dati_aziende->m_ABI;
		m_strCAB									= m_dati_aziende->m_CAB;
		m_strBanca								= m_dati_aziende->m_Banca;
		m_strCellulare						= m_dati_aziende->m_Cellulare;
		m_strCodiceAzienda				=	m_dati_aziende->m_ID;
		m_strCodiceFiscale				= m_dati_aziende->m_CodiceFiscale;
		m_strEMail								=	m_dati_aziende->m_E_Mail;
		m_strCodiceDestinatario		= m_dati_aziende->m_CodiceDestinatario;
		m_strPEC									=	m_dati_aziende->m_PEC;
		m_strFax									= m_dati_aziende->m_Fax;	
		m_strNoteAzienda					= m_dati_aziende->m_Note;
		m_strPIVA									= m_dati_aziende->m_P_IVA;
		m_strTelefono							= m_dati_aziende->m_Telefono;
    m_dSconto                 = m_dati_aziende->m_Sconto;

		int count(0);
		int index(0);
		for (int i(0); i < m_ComboTipoPagamento.GetCount(); i++)
		{
			index = m_ComboTipoPagamento.GetItemData(i);
			if (index == m_dati_aziende->m_TipoPagamento)	
			{
				m_ComboTipoPagamento.SetCurSel(count);
				m_ComboTipoPagamento.UpdateData(FALSE);
				break;
			}
			count++;
		}
  }
	delete m_archivio_aziende;
	UpdateData(FALSE);
}

void CAziendeView::OnButtonDBRemoto() 
{
	UpdateData();
	CDBRemotoDlg dlg(m_dati_aziende, this);
	if(dlg.DoModal() == IDOK)
	{
		m_strRagioneSociale				= m_dati_aziende->m_RagioneSociale;
		m_strIndirizzo						= m_dati_aziende->m_Indirizzo;
		m_csIndirizzo_Spedizione	= m_dati_aziende->m_Indirizzo_Sped;
		m_strCAP									=	m_dati_aziende->m_CAP;
		m_csCap_Spedizione				=	m_dati_aziende->m_CAP_Sped;
		m_strCitta								= m_dati_aziende->m_Citta;
		m_csCitta_Spedizione			= m_dati_aziende->m_Citta_Sped;
		m_strProvincia						= m_dati_aziende->m_Provincia;
		m_csProvincia_Spedizione	= m_dati_aziende->m_Provincia_Sped;
		m_strABI									= m_dati_aziende->m_ABI;
		m_strCAB									= m_dati_aziende->m_CAB;
		m_strBanca								= m_dati_aziende->m_Banca;
		m_strCellulare						= m_dati_aziende->m_Cellulare;
		m_strCodiceAzienda				=	m_dati_aziende->m_ID;
		m_strCodiceFiscale				= m_dati_aziende->m_CodiceFiscale;
		m_strEMail								=	m_dati_aziende->m_E_Mail;
		m_strFax									= m_dati_aziende->m_Fax;	
		m_strNoteAzienda					= m_dati_aziende->m_Note;
		m_strPIVA									= m_dati_aziende->m_P_IVA;
		m_strTelefono							= m_dati_aziende->m_Telefono;
    m_dSconto                 = m_dati_aziende->m_Sconto;

		int count(0);
		int index(0);
		for (int i(0); i < m_ComboTipoPagamento.GetCount(); i++)
		{
			index = m_ComboTipoPagamento.GetItemData(i);
			if (index == m_dati_aziende->m_TipoPagamento)	
			{
				m_ComboTipoPagamento.SetCurSel(count);
				m_ComboTipoPagamento.UpdateData(FALSE);
				break;
			}
			count++;
		}
  }
	UpdateData(FALSE);
}

void CAziendeView::OnButtonGeneraCodice() 
{
	GeneraCodice();
}

void CAziendeView::GeneraCodice() 
{
	CString Codice("");
	CString sql("");
	int Numero(0);

	// Serve per caricare la Ragione Sociale e il Codice Azienda
	UpdateData(TRUE);
	m_strCodiceAzienda = "";
	UpdateData(FALSE);

	// Crea un nuovo RecordSet e lo apre per controllare se il codice esiste
	m_pCodice_Aziende = new CAziendeSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
	m_pCodice_Aziende->m_strFilter.Empty();
	m_pCodice_Aziende->Open();

	// Apro l'eventuale anagrafica nel DB remoto
	if(((CWinSigmaApp*)AfxGetApp())->IsDBRemoto() == 1)
	{
		m_pCodice_Aziende_Remoto = new CAziendeSet(&((CWinSigmaApp*)AfxGetApp())->m_dbr);
		m_pCodice_Aziende_Remoto->m_strFilter.Empty();
		m_pCodice_Aziende_Remoto->Open();
	}

	m_pCodice_Aziende_Vecchie = new CAziendeOldSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
	m_pCodice_Aziende_Vecchie->m_strFilter.Empty();
	m_pCodice_Aziende_Vecchie->Open();


	//Estrae le prime tre lettere dalla Ragione Sociale
	int Lunghezza_Codice(m_strCodiceAzienda.GetLength());
	if (Lunghezza_Codice >= 3)
	{
			if ( ControllaCodice( m_strCodiceAzienda.Mid(0,3) ) != -1 )
				{
					AfxMessageBox("Attenzione: il 'Codice' dell'azienda può contenere solamente lettere e numeri.");
					return;
				}
		
			Codice = m_strCodiceAzienda.Mid(0,3);
			Codice.MakeUpper();
	}
	else
	{
		if (Lunghezza_Codice == 2)
		{
			if (m_strRagioneSociale.GetLength() < 1)
			{
				AfxMessageBox("Attenzione: la 'Ragione sociale' dell'azienda deve essere di almeno una lettera.");
				return;
			}
			else
			{
				Codice = m_strCodiceAzienda.Mid(0,2);
				Codice += m_strRagioneSociale.Mid(0,1);
				Codice.MakeUpper();
			}
		}
		else if (Lunghezza_Codice == 1)
		{
			if (m_strRagioneSociale.GetLength() < 2)
			{
				AfxMessageBox("Attenzione: la 'Ragione sociale' dell'azienda deve essere di almeno due lettere.");
				return;
			}
			else
			{
				Codice = m_strCodiceAzienda.Mid(0,1);
				Codice += m_strRagioneSociale.Mid(0,2);
				Codice.MakeUpper();
			}
		}
		else if (Lunghezza_Codice == 0)
		{
			if (m_strRagioneSociale.GetLength() < 3)
			{
				AfxMessageBox("Attenzione: la 'Ragione sociale' dell'azienda deve essere di almeno tre lettere.");
				return;
			}
			else
			{
				//Genera i primi tre caratteri del codice a partire dai primi tre caratteri utili della ragione sociale
				Codice = m_strRagioneSociale.Mid(0,3);
				Codice.MakeUpper();

				int b(0);
				int cc(ControllaCodice( Codice ));
				while (( cc != -1 ) && ( b <= m_strRagioneSociale.GetLength() ) )
				{
					Codice.Delete( 3 - cc );
					Codice.Insert(Codice.GetLength(), m_strRagioneSociale.Mid( 3 - cc + b, 1 ));
					Codice.MakeUpper();
					cc = ControllaCodice ( Codice );
					b ++;
				}

				if ( ( ControllaCodice(Codice ) != -1 ) || ( Codice.GetLength() < 3 ) )
				{
					AfxMessageBox("Attenzione: la 'Ragione sociale' dell'azienda contiene dei caratteri speciali, inserire il codice a mano.");
					return;
				}
			}
		}
	}

	//Ricerca sul RecordSet se esiste un codice che inizia per quelle tre lettere
	Codice.Replace("'", "''");
	sql = "ID LIKE '" + Codice + "%'";
	m_pCodice_Aziende->m_strFilter = sql;
	m_pCodice_Aziende_Vecchie->m_strFilter = sql;

	m_pCodice_Aziende->Requery();
	SET_START(m_pCodice_Aziende);
	m_pCodice_Aziende_Vecchie->Requery();
	SET_START(m_pCodice_Aziende_Vecchie);

	while (!m_pCodice_Aziende->IsEOF())
	{
		int App(atoi(m_pCodice_Aziende->m_ID.Mid(3,m_pCodice_Aziende->m_ID.GetLength())));
		if (Numero < App)
				Numero = App;
		m_pCodice_Aziende->MoveNext();
	}

	while (!m_pCodice_Aziende_Vecchie->IsEOF())
	{
		int App(atoi(m_pCodice_Aziende_Vecchie->m_ID.Mid(3,m_pCodice_Aziende_Vecchie->m_ID.GetLength())));
		if (Numero < App)
				Numero = App;
		m_pCodice_Aziende_Vecchie->MoveNext();
	}

	if(((CWinSigmaApp*)AfxGetApp())->IsDBRemoto() == 1)
	{
		m_pCodice_Aziende_Remoto->m_strFilter = sql;
		m_pCodice_Aziende_Remoto->Requery();
		SET_START(m_pCodice_Aziende_Remoto);
		while (!m_pCodice_Aziende_Remoto->IsEOF())
		{
			int App(atoi(m_pCodice_Aziende_Remoto->m_ID.Mid(3,m_pCodice_Aziende_Remoto->m_ID.GetLength())));
			if (Numero < App)
				Numero = App;
			m_pCodice_Aziende_Remoto->MoveNext();
		}
	}

	if (Numero == 0)
	{
		Codice += "0001";
	}
	else 
	{
		char buf[20];
		sprintf(buf,"%04d",Numero + 1);
		CString App(buf);
		Codice += App;
	}

	//Chiude e distrugge il RecordSet
	m_pCodice_Aziende->Close();
	delete m_pCodice_Aziende;

	m_pCodice_Aziende_Vecchie->Close();
	delete m_pCodice_Aziende_Vecchie;

	if(((CWinSigmaApp*)AfxGetApp())->IsDBRemoto() == 1)
	{
		m_pCodice_Aziende_Remoto->Close();
		delete m_pCodice_Aziende_Remoto;
	}

	m_strCodiceAzienda = Codice;
	
	UpdateData(FALSE);
}

int CAziendeView::ControllaCodice(CString str)
{
	//Controlla che non ci siano apici od altri segni all'interno del codice appena estratto
	CString strApp = str;

	if (str == "")
		return -1;

	char* cApp = NULL;
	
	CString strA("");
	strA.Format("%.1s",strApp);

	cApp = strpbrk( strA, "QWERTYUIOPLKJHGFDSAZXCVBNMqwertyuioplkjhgfdsazxcvbnm1234567890" );

	if ( !cApp )
		return strApp.GetLength();	

	strApp.Delete(0,1);

	return ControllaCodice(strApp);
}

// Apre il dialogo per l'inserimento di un verbale fittizio per la fatturazione
// dei verbali del 2003
void CAziendeView::OnButtonInsert() 
{
  CInsertVerbaliDlg dlg;
  CString str;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  if(dlg.DoModal() == IDOK)
  {
  	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
    CVerbaliSet verbaliSet(&pApp->m_db);
    verbaliSet.m_strFilter = "Codice = 0";
    verbaliSet.Open();
    CListiniSet* pListinoSet;
    pApp->LockTable(VERBALI);
    verbaliSet.AddNew();
    verbaliSet.m_TipoVerbale = VERB_VECCHIO_PROG;
    verbaliSet.m_ProgressivoParziale = atol(dlg.m_strProgressivoParziale);
    verbaliSet.m_ProgressivoTotale = atol(dlg.m_strProgressivoTotale);
    verbaliSet.m_Cantiere = dlg.m_strCantiere;
    // Operatore
    verbaliSet.m_Operatore = pApp->GetUserName();
    verbaliSet.m_DataAccettazione = dlg.m_DataAccettazione;
    // Listino
    pListinoSet = pDoc->m_pListiniInVigoreSet;
		for(SET_START(pListinoSet); !pListinoSet->IsEOF(); pListinoSet->MoveNext())
		{
			if(pListinoSet->IsFieldNull(&pListinoSet->m_Azienda)
				 || pListinoSet->m_Azienda == 0)
				break;
		}
		if(!pListinoSet->IsEOF())
			verbaliSet.m_ListinoGenerale = pListinoSet->m_Codice;
		else
      verbaliSet.m_ListinoGenerale = 0;
		for(SET_START(pListinoSet); !pListinoSet->IsEOF(); pListinoSet->MoveNext())
    {
      if(pListinoSet->m_Azienda == m_pSet->m_Codice)
      {
        verbaliSet.m_ListinoParticolare = pListinoSet->m_Codice;
        break;
      }
    }
		if(pListinoSet->IsEOF())
			verbaliSet.m_ListinoParticolare = 0;
		verbaliSet.m_CertOgniSerie   = 0;
		verbaliSet.m_CodiceAzFattura = m_pSet->m_Codice;
  	verbaliSet.m_IDAzFattura = m_pSet->m_ID;
    verbaliSet.m_P_IVA = m_pSet->m_P_IVA;
  	verbaliSet.m_NomeAzFattura = m_pSet->m_RagioneSociale;
    str.Format("%s %s %s %s", m_pSet->m_Indirizzo, m_pSet->m_CAP, m_pSet->m_Citta, m_pSet->m_Provincia);
    verbaliSet.m_IndirizzoFattura = m_pSet->m_Indirizzo;
    verbaliSet.m_DataConsegna = 0;
    verbaliSet.m_Urgenza = 0;
    verbaliSet.m_Spedizione = 0;
    verbaliSet.m_LungaScadenza = dlg.m_bLungaScadenza;
    // Metto il verbale in fatturazione
    verbaliSet.m_NumeroFattura = 0;
    verbaliSet.m_InFatturazione = 0;
    // Aggiorno il recordset
    verbaliSet.Update();
    // Sblocco la tabella
    pApp->UnlockTables();
    verbaliSet.m_strFilter.Empty();
    verbaliSet.Close();
    pDoc->m_pVerbaliAperti->Requery();
  }
  LoadVerbali(m_pSet->m_ID);
  pApp->ReloadTree(TREELABEL_FATTUREDAEMETTERE, m_pSet->m_Codice);
  UpdateData(FALSE);
}

void CAziendeView::OnButtonEliminaVfarlocco() 
{
  CString str;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  int n;
  POSITION pos;
  if((pos = m_ListCtrlVerbali.GetFirstSelectedItemPosition()) == NULL)
  {
    AfxMessageBox("Selezionare un dato valido.");
    return;
  }
  n = m_ListCtrlVerbali.GetNextSelectedItem(pos);
  CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  CVerbaliSet verbaliSet(&pApp->m_db);
  verbaliSet.m_strFilter.Format("Codice = %d", m_ListCtrlVerbali.GetItemData(n));
  verbaliSet.Open();  
  if(verbaliSet.m_TipoVerbale != VERB_VECCHIO_PROG)
  {
    str.Format("Selezionare un verbale antecedente al %s", (CTime(CTime::GetCurrentTime().GetYear(), 1, 1,0, 0, 0)).Format("%d/%m/%Y"));
    AfxMessageBox(str);
    return;
  }
  str.Format("Eliminare il verbale %d/%d del %s?", verbaliSet.m_ProgressivoParziale, verbaliSet.m_ProgressivoTotale, verbaliSet.m_DataAccettazione.Format("%d/%m/%Y"));
  if(AfxMessageBox(str, MB_YESNO) == IDYES)
    verbaliSet.Delete();
  verbaliSet.Close();
  LoadVerbali(m_pSet->m_ID);
  pApp->ReloadTree(TREELABEL_FATTUREDAEMETTERE, m_pSet->m_Codice);
  UpdateData(FALSE);
}

void CAziendeView::OnButtonModificaVfarlocco() 
{
	CInsertVerbaliDlg dlg;
  CString str;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  int n;
  POSITION pos;
  if((pos = m_ListCtrlVerbali.GetFirstSelectedItemPosition()) == NULL)
  {
    AfxMessageBox("Selezionare un dato valido.");
    return;
  }
  n = m_ListCtrlVerbali.GetNextSelectedItem(pos);
  CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  CVerbaliSet verbaliSet(&pApp->m_db);
  verbaliSet.m_strFilter.Format("Codice = %d", m_ListCtrlVerbali.GetItemData(n));
  verbaliSet.Open();  
  if(verbaliSet.m_TipoVerbale != VERB_VECCHIO_PROG)
  {
    str.Format("Selezionare un verbale antecedente al %s", (CTime(CTime::GetCurrentTime().GetYear(), 1, 1,0, 0, 0)).Format("%d/%m/%Y"));
    AfxMessageBox(str);
    return;
  }
  dlg.m_bLungaScadenza = verbaliSet.m_LungaScadenza;
  dlg.m_strProgressivoParziale.Format("%d", verbaliSet.m_ProgressivoParziale);
  dlg.m_strProgressivoTotale.Format("%d", verbaliSet.m_ProgressivoTotale);
  dlg.m_strCantiere = verbaliSet.m_Cantiere;
  dlg.m_DataAccettazione = verbaliSet.m_DataAccettazione;
  if(dlg.DoModal() == IDOK)
  {
    pApp->LockTable(VERBALI);
    verbaliSet.Edit();
    verbaliSet.m_TipoVerbale = VERB_VECCHIO_PROG;
    verbaliSet.m_ProgressivoParziale = atol(dlg.m_strProgressivoParziale);
    verbaliSet.m_ProgressivoTotale = atol(dlg.m_strProgressivoTotale);
    verbaliSet.m_Cantiere = dlg.m_strCantiere;
    // Operatore
    verbaliSet.m_Operatore = pApp->GetUserName();
    verbaliSet.m_DataAccettazione = dlg.m_DataAccettazione;
    // Aggiorno il recordset
    verbaliSet.Update();
    // Sblocco la tabella
    pApp->UnlockTables();
    verbaliSet.m_strFilter.Empty();
    pDoc->m_pVerbaliAperti->Requery();
  }
  verbaliSet.Close();
  LoadVerbali(m_pSet->m_ID);
  pApp->ReloadTree(TREELABEL_FATTUREDAEMETTERE, m_pSet->m_Codice);
  UpdateData(FALSE);
}


void CAziendeView::OnButtonAggiorna() 
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	long aziendaSel = m_pSet->m_Codice;
	pApp->ReloadTree(TREELABEL_AZIENDEIMPORTANTI, aziendaSel);
	pApp->ReloadTree(TREELABEL_AZIENDERECENTI, aziendaSel);
	pApp->ReloadTree(TREELABEL_AZIENDEALFABETICA, aziendaSel);
}

void CAziendeView::OnReportVerbali() 
{
	CReportVerbali dlg;
	dlg.m_pAziendeSet = m_pSet;
	dlg.DoModal();
}

void CAziendeView::OnDblclkListVerbali(NMHDR* pNMHDR, LRESULT* pResult) 
{
  POSITION pos;
  if((pos = m_ListCtrlVerbali.GetFirstSelectedItemPosition()) == NULL)
  {
    AfxMessageBox("Selezionare un documento.");
    return;
  }
  CPrintPreviewVerbali prnVerbali;
	CPreviewDlg dlg;
	int n = m_ListCtrlVerbali.GetNextSelectedItem(pos);		
	if (n > -1)
	{
		dlg.m_pPrintPreviewDoc = &prnVerbali;
		dlg.m_nCodice = (long)m_ListCtrlVerbali.GetItemData(n);
		dlg.DoModal();
	}
	
	*pResult = 0;
}

// controllo CODICE FISCALE  s.c. 30/03/2014
void CAziendeView::OnKillfocusEditCodFisc()
{
	UpdateData(TRUE);
	m_bCodiceFiscaleValido = ValidateCodiceFiscale();
	return;
}

/*----- GESTIONE DEI CAP -----*/
void CAziendeView::OnKillfocusEditProvincia() 
{
	CAP();
}

void CAziendeView::OnKillfocusEditCitta() 
{
	CAP();
}

void CAziendeView::OnKillfocusEditIndirizzo() 
{
	CAP();
}

void CAziendeView::CAP()
{
  this->UpdateData();
  
  m_cbxCAP.Clear();
  while (!(m_cbxCAP.GetCount() == 0))
  {
    m_cbxCAP.DeleteString(m_cbxCAP.GetCount() - 1);
  }

  m_cbxCAP.InsertString(0,"");
  m_cbxCAP.SetItemData(0,0);

  CLocalitaSet* loc = new CLocalitaSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
  
  CString Provincia (m_strProvincia);
  CString Indirizzo (m_strIndirizzo);
  CString Citta     (m_strCitta);
  Provincia.Replace("'","''");
  Indirizzo.Replace("'","''");
  Citta.Replace("'","''");
  Provincia.MakeUpper();
  Indirizzo.MakeUpper();
  Citta.MakeUpper();
  // Primo livello di Query
  if (
      (!Indirizzo.IsEmpty() || (Indirizzo  != "")) &&
      (Provincia == "FI")  &&
      (Citta == "FIRENZE")
    )
  {
    // Estrae le parole dall'indirizzo e crea la Query SQL
    CString str = m_strIndirizzo;
    str.Replace("'","''");
    str.Replace("%","%%");
    str.Insert(str.GetLength()," ");
    int pos = str.Find(" ");

    while ((pos != -1) || (str.GetLength() != 0))
    {
      int newpos = str.Find(" ", pos + 1);

      if ((newpos == -1) && (str.GetLength() != 0))
      {
        loc->m_strFilter += "(Indirizzo Like '" + str.Mid(0,pos) + "%')";
        str.Delete(0, str.GetLength());
        pos = str.Find(" ");
      }
      else if (newpos != -1)
      {
        loc->m_strFilter += "(Indirizzo Like '" + str.Mid(0,pos) + "%') OR ";
        str.Delete(0,pos + 1);
        pos = str.Find(" ");
      }
    }
    
    // Esegue la Query
    if (!loc->m_strFilter.IsEmpty())
    {
      loc->m_strFilter.Insert(0,"(");
      loc->m_strFilter.Insert(loc->m_strFilter.GetLength(),")");
    }

    loc->Open();

    // Secondo livello di Query
    if (
        !loc->IsEOF() &&
        (!Provincia.IsEmpty()  || (Provincia != "")) &&
        (!Indirizzo.IsEmpty()  || (Indirizzo != "")) 
       )
          loc->m_strFilter += " AND (Provincia = '" + Provincia + "')";
    else if (
              (!Provincia.IsEmpty()  || (Provincia != "")) && 
              (!Indirizzo.IsEmpty()  || (Indirizzo != "")) 
            ) 
          loc->m_strFilter.Format("Provincia = '%s'", Provincia);
   else if (
            !loc->IsEOF() &&
            (!Indirizzo.IsEmpty() || (Indirizzo != "")) &&
            (!Citta.IsEmpty()     || (Citta     != "")) 
           )
          loc->m_strFilter += " AND (Localita Like '" + Citta + "%')";
    else if (
              (!Indirizzo.IsEmpty() || (Indirizzo != "")) &&
              (!Citta.IsEmpty()     || (Citta     != "")) 
            )
           loc->m_strFilter.Format("Localita Like '%s%%'", Citta);

    loc->Requery();
  }
  else if (!Provincia.IsEmpty() || (Provincia != ""))
  {    
    //  Crea la Query SQL
    loc->m_strFilter.Format("Provincia = '%s'", Provincia);
    
    // Esegue la Query
    if (!loc->m_strFilter.IsEmpty())
    {
      loc->m_strFilter.Insert(0,"(");
      loc->m_strFilter.Insert(loc->m_strFilter.GetLength(),")");
    }
    
    loc->Open();

    if (
        !loc->IsEOF() &&
        (!Provincia.IsEmpty()  || (Provincia != "")) &&
        (!Citta.IsEmpty()      || (Citta != "")) 
       )
          loc->m_strFilter += " AND (Localita Like '" + Citta + "%')";

    loc->Requery();
  }
  else if (
          (!Citta.IsEmpty()    || (Citta     != "")) && 
          (Citta != "FIRENZE")
          )
  {
    //  Crea la Query SQL
    loc->m_strFilter.Format("Localita Like '%s%%'", Citta);

    loc->Open();
  }
  else if (
          (!Citta.IsEmpty()    || (Citta     != ""))
          )
  {
    //  Crea la Query SQL
    loc->m_strFilter.Format("Localita Like '%s%%'", Citta);

    loc->Open();
  }

  if (loc->IsOpen())
  {
    for(int i(1); !loc->IsEOF(); loc->MoveNext())
    {
      CString str("");
  
      if (loc->m_Indirizzo == "")
        str.Format("%s", loc->m_Localita);
      else if (loc->m_Note.IsEmpty() || (loc->m_Note == ""))
        str.Format("%s - %s %s", loc->m_Localita, loc->m_Tipologia, loc->m_Indirizzo);
      else if (!loc->m_Note.IsEmpty() || (loc->m_Note != ""))
        str.Format("%s - %s %s - %s", loc->m_Localita, loc->m_Tipologia, loc->m_Indirizzo, loc->m_Note);

  
      m_cbxCAP.InsertString(i,str);
      m_cbxCAP.SetItemData(i, loc->m_CAP);
      i++;
    }
    loc->Close();
  }

  delete loc;

  if(m_cbxCAP.GetCount() > 1)
  {
    m_cbxCAP.SetCurSel(1);

    m_strCAP.Format("%05d",m_cbxCAP.GetItemData(m_cbxCAP.GetCurSel()));
    this->UpdateData(FALSE);
  }
}

void CAziendeView::OnSelchangeComboCap() 
{
  int cap = m_cbxCAP.GetItemData(m_cbxCAP.GetCurSel());
  if (cap != 0)
    m_strCAP.Format("%05d",cap);
  else
    m_strCAP = "";

  this->UpdateData(FALSE);
}


void CAziendeView::OnButtonUpdateFromDBR() 
{
	CString csText, csSQL;
	CAziendeSet* pSet = new CAziendeSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
	CAziendeSet* pRemoteSet = new CAziendeSet(&((CWinSigmaApp*)AfxGetApp())->m_dbr);

	pRemoteSet->m_strFilter.Format("Codice > 11186");
	pRemoteSet->Open();
	while (!pRemoteSet->IsEOF())
	{
		pSet->m_strFilter.Format("ID LIKE '%s'", pRemoteSet->m_ID);
		pSet->Open();
		if(pSet->IsBOF())
		{
			try
			{
				pSet->AddNew();
				// Anagrafica
				pSet->m_RagioneSociale	= pRemoteSet->m_RagioneSociale;
				pSet->m_ID							=	pRemoteSet->m_ID;
				pSet->m_Indirizzo				= pRemoteSet->m_Indirizzo;
				pSet->m_CAP							= pRemoteSet->m_CAP;
				pSet->m_Citta						= pRemoteSet->m_Citta;
				pSet->m_Provincia				= pRemoteSet->m_Provincia;
				pSet->m_Telefono				= pRemoteSet->m_Telefono;
				pSet->m_Cellulare				= pRemoteSet->m_Cellulare;
				pSet->m_E_Mail					= pRemoteSet->m_E_Mail;
				pSet->m_Fax							= pRemoteSet->m_Fax;
				pSet->m_CodiceFiscale		= pRemoteSet->m_CodiceFiscale;

				if(CheckPIVAExist(m_strPIVA) == TRUE)        
				{
					CString str("Partita IVA già presente. Vuoi ugualmente procedere all'inserimento?");
					if (AfxMessageBox(str, MB_YESNO) == IDNO)
						return;
				}

				pSet->m_P_IVA						= pRemoteSet->m_P_IVA;

				pSet->m_IsImportante		= pRemoteSet->m_IsImportante;
				pSet->m_UsaTuttiListini	= pRemoteSet->m_UsaTuttiListini;
				pSet->m_Privato					=	pRemoteSet->m_Privato;
				pSet->m_Indirizzo_Sped	= pRemoteSet->m_Indirizzo_Sped;
				pSet->m_CAP_Sped				= pRemoteSet->m_CAP_Sped;
				pSet->m_Citta_Sped			= pRemoteSet->m_Citta_Sped;
				pSet->m_Provincia_Sped	= pRemoteSet->m_Provincia_Sped;
				// Note
				pSet->m_Note						= pRemoteSet->m_Note;
				// Pagamento
				pSet->m_TipoPagamento		= pRemoteSet->m_TipoPagamento;
				pSet->m_ABI							= pRemoteSet->m_ABI;
				pSet->m_CAB							= pRemoteSet->m_CAB;
				pSet->m_Banca						= pRemoteSet->m_Banca;
				pSet->m_Sconto					= pRemoteSet->m_Sconto;
				pSet->Update();
			}
			catch(CDBException* e)
			{
				CString strError;  

				strError = e->m_strError;
				AfxMessageBox(strError);
				return;
			}
		}
		pSet->Close();
		pRemoteSet->MoveNext();
	}
	pRemoteSet->Close();
	delete pRemoteSet;
	delete pSet;
}


