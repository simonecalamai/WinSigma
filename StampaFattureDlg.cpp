// StampaFattureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "winsigmadoc.h"
#include "Configurazione.h"
#include "Printerpreter.h"
#include "StampaFattureDlg.h"
#include "WinSigmaDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_CHAR_DESCRIZIONE 85
#define N_COPIE_FATTURA 2
#define VERIFY_DATA_MSG "Verificare la correttezza della data."

/////////////////////////////////////////////////////////////////////////////
// CStampaFattureDlg dialog
CFattureSet*            CStampaFattureDlg::m_pFattureEmesseSet;
CVerbaliSet*            CStampaFattureDlg::m_pVerbaliInfatturazione;
CServiziErogatiSet*     CStampaFattureDlg::m_pServiziErogati;
CAziendeSet*            CStampaFattureDlg::m_pAziendeSet;
CString                 CStampaFattureDlg::m_strProgressiviVerbali;
CString                 CStampaFattureDlg::m_strImporto;
CString                 CStampaFattureDlg::m_strImportoScontato;
CString                 CStampaFattureDlg::m_strIVA;
CString                 CStampaFattureDlg::m_strTotaleFattura;
CString                 CStampaFattureDlg::m_strTipoPagamento;
CString                 CStampaFattureDlg::m_strTipoDocumento;
CString                 CStampaFattureDlg::m_strCoordinateBancarie;
double                  CStampaFattureDlg::m_dSconto;
double                  CStampaFattureDlg::m_dSpeseSpedizione;
double                  CStampaFattureDlg::m_dAliquota;
BOOL                    CStampaFattureDlg::m_bFatturaEmessa;
BOOL                    CStampaFattureDlg::m_bSpedSelezionata;
BOOL                    CStampaFattureDlg::m_bMaggiorazione;
BOOL                    CStampaFattureDlg::m_bVerbaliPrinted;
BOOL                    CStampaFattureDlg::m_bRiba;
BOOL                    CStampaFattureDlg::m_bFatturaProForma;
long                    CStampaFattureDlg::m_lCodiceVerbale;
long                    CStampaFattureDlg::m_lCodiceServizio;
long                    CStampaFattureDlg::m_lCodiceAzienda;
long                    CStampaFattureDlg::m_lCodiceFatturaEmessa;
int                     CStampaFattureDlg::m_nImportoVerbale;
int                     CStampaFattureDlg::m_nNumPagine;
int                     CStampaFattureDlg::m_nRitAcconto;
int                     CStampaFattureDlg::m_nTotRitAcconto;
int                     CStampaFattureDlg::m_nIVA;
int                     CStampaFattureDlg::m_nImponibile;
int                     CStampaFattureDlg::m_nSpeseSpedizione;
int                     CStampaFattureDlg::m_nImponibileScontato;



CStampaFattureDlg::CStampaFattureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStampaFattureDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStampaFattureDlg)
	m_bSpedizione = FALSE;
	m_bPA = FALSE;
	m_bIVADifferita = FALSE;
	m_strBanca = _T("");
	m_strCAB = _T("");
	m_strCodice = _T("");
	m_strIndirizzo = _T("");
	m_strNumero = _T("");
	m_strPIVA = _T("");
	m_strRagioneSociale = _T("");
	m_strABI = _T("");
	m_strAliquota = _T("");
	m_strImponibile = _T("");
	m_strTotale = _T("");
	m_strImportoIVA = _T("");
	m_bRaggruppaPerServizio = FALSE;
	m_DataFattura = 0;
	m_strPIVA_CF = _T("");
	m_nNumCopie = 0;
	m_strSconto = _T("");
	m_strImponibileScontato = _T("");
	m_strCodFiscale = _T("");
	m_csRitAcconto = _T("");
	m_csTotRitAcconto = _T("");
	m_bHeader = TRUE;
	//}}AFX_DATA_INIT
  m_strImporto.Empty();
  m_strIVA.Empty();
  m_strTotaleFattura.Empty();
  m_csRitAcconto.Empty();
  m_csTotRitAcconto.Empty();
  m_bFatturaProForma = FALSE;

  m_nRitAcconto = 0;
  m_nTotRitAcconto = 0;
}


void CStampaFattureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStampaFattureDlg)
	DDX_Control(pDX, IDC_EDIT_TOT_RIT_ACCONTO, m_edtTotoRitAcconto);
	DDX_Control(pDX, IDC_EDIT_RIT_ACCONTO, m_edtRitAcconto);
	DDX_Control(pDX, IDC_STATIC_DATI, m_StaticDati);
	DDX_Control(pDX, IDC_DATETIMEPICKER_DATA_FATTURA, m_DTCtrlDataFattura);
	DDX_Control(pDX, IDC_COMBO_TIPO_PAGAMENTO, m_ComboTipoPagamento);
	DDX_Control(pDX, IDC_CHECK_SPEDIZIONE, m_BtnSpedizione);
	DDX_Control(pDX, IDC_BUTTON_PRINT_FATTURA, m_BtnStampaFattura);
	DDX_Control(pDX, IDC_BUTTON_FATTURA_XML, m_BtnFatturaXML);
	DDX_Control(pDX, IDOK, m_BtnEmettiFattura);
	DDX_Check(pDX, IDC_CHECK_SPEDIZIONE, m_bSpedizione);
	DDX_Check(pDX, IDC_CHECK_PA, m_bPA);
	DDX_Check(pDX, IDC_CHECK_IVADIFF, m_bIVADifferita);
	DDX_Text(pDX, IDC_EDIT_BANCA, m_strBanca);
	DDV_MaxChars(pDX, m_strBanca, 64);
	DDX_Text(pDX, IDC_EDIT_CAB, m_strCAB);
	DDV_MaxChars(pDX, m_strCAB, 8);
	DDX_Text(pDX, IDC_EDIT_CODICE, m_strCodice);
	DDX_Text(pDX, IDC_EDIT_INDIRIZZO, m_strIndirizzo);
	DDX_Text(pDX, IDC_EDIT_NUMERO, m_strNumero);
	DDX_Text(pDX, IDC_EDIT_PIVA, m_strPIVA);
	DDX_Text(pDX, IDC_EDIT_RAGIONE_SOCIALE, m_strRagioneSociale);
	DDX_Text(pDX, IDC_EDIT_ABI, m_strABI);
	DDV_MaxChars(pDX, m_strABI, 8);
	DDX_Control(pDX, IDC_MASKEDBOX_SPESE_SPEDIZIONE, m_MskSpeseSpedizione);
	DDX_Text(pDX, IDC_EDIT_ALIQUOTA, m_strAliquota);
	DDX_Text(pDX, IDC_EDIT_IMPONIBILE, m_strImponibile);
	DDX_Text(pDX, IDC_EDIT_TOTALE, m_strTotale);
	DDX_Text(pDX, IDC_EDIT_IVA, m_strImportoIVA);
	DDX_Check(pDX, IDC_CHECK_PERSERVIZIO, m_bRaggruppaPerServizio);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATA_FATTURA, m_DataFattura);
	DDX_Text(pDX, IDC_STATIC_PIVA_CF, m_strPIVA_CF);
	DDX_Text(pDX, IDC_EDIT_NUM_COPIE, m_nNumCopie);
	DDV_MinMaxInt(pDX, m_nNumCopie, 0, 100000);
	DDX_Text(pDX, IDC_EDIT_SCONTO, m_strSconto);
	DDX_Text(pDX, IDC_EDIT_IMPORTOSCONTATO, m_strImponibileScontato);
	DDX_Text(pDX, IDC_EDIT_CODFISCALE, m_strCodFiscale);
	DDX_Text(pDX, IDC_EDIT_RIT_ACCONTO, m_csRitAcconto);
	DDX_Text(pDX, IDC_EDIT_TOT_RIT_ACCONTO, m_csTotRitAcconto);
	DDX_Check(pDX, IDC_CHECK_HEADER, m_bHeader);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStampaFattureDlg, CDialog)
	//{{AFX_MSG_MAP(CStampaFattureDlg)
	ON_BN_CLICKED(IDC_BUTTON_PRINT_FATTURA, OnButtonPrintFattura)
	ON_BN_CLICKED(IDOK, OnButtonEmetti)
	ON_BN_CLICKED(IDC_CHECK_SPEDIZIONE, OnCheckSpedizione)
	ON_EN_CHANGE(IDC_EDIT_ALIQUOTA, OnChangeEditAliquota)
	ON_BN_CLICKED(IDC_CHECK_PERSERVIZIO, OnCheckPerservizio)
	ON_BN_CLICKED(IDC_BUTTON_FATTURA_XML, OnButtonFatturaXML)
	ON_CBN_SELCHANGE(IDC_COMBO_TIPO_PAGAMENTO, OnSelchangeComboTipoPagamento)
	ON_EN_CHANGE(IDC_EDIT_SCONTO, OnChangeEditSconto)
	ON_EN_CHANGE(IDC_EDIT_TOTALE, OnChangeEditTotale)
	ON_EN_CHANGE(IDC_EDIT_RIT_ACCONTO, OnChangeEditRitAcconto)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStampaFattureDlg message handlers

void CStampaFattureDlg::OnCancel() 
{
  if(m_pVerbaliInfatturazione)
  {
    if(m_pVerbaliInfatturazione->IsOpen())
      m_pVerbaliInfatturazione->Close();
    delete m_pVerbaliInfatturazione;
  }
  if(m_pServiziErogati)
  {
    if(m_pServiziErogati->IsOpen())
      m_pServiziErogati->Close();
    delete m_pServiziErogati;
  }
	CDialog::OnCancel();
}


BOOL CStampaFattureDlg::OnInitDialog() 
{
  if(m_pDoc == NULL)
    return FALSE;
	CDialog::OnInitDialog();
  CString strMask, str, strFilter;
  long codice;

  str = m_strTipoDocumento;
  str.MakeLower();
  if(m_lCodiceFatturaEmessa > 0)
  {
    m_BtnEmettiFattura.SetWindowText("Salva");
    SetWindowText("Modifica " + str);
  }
  else
  {
    m_BtnEmettiFattura.SetWindowText("Emetti");
    SetWindowText("Emissione " + str);
  }
  m_StaticDati.SetWindowText("Dati " + str);
  m_nNumCopie = 2;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	if(m_bElett == TRUE)
		((CStatic*)GetDlgItem(IDC_STATIC_ELETT))->ShowWindow(SW_SHOW);
	else
		((CStatic*)GetDlgItem(IDC_STATIC_ELETT))->ShowWindow(SW_HIDE);
  // Inizializzo il recordset prendendo solo le fatture dell'anno impostato nella data di emissione
  m_pFattureEmesseSet = m_pDoc->m_pFattureEmesseSet;
  CTime dateFrom(m_DataFattura.GetYear(), 1, 1, 0, 0, 0);
  CTime dateTo(m_DataFattura.GetYear(), 12, 31, 23, 59, 59);
  m_pFattureEmesseSet->m_strFilter.Format("Data >= '%s' and Data <= '%s'", dateFrom.Format("%Y-%m-%d"), dateTo.Format("%Y-%m-%d"));
  m_pFattureEmesseSet->Requery();

  m_pVerbaliInfatturazione = new CVerbaliSet(&pApp->m_db);
  if(m_bFatturaProForma || !m_lCodiceFatturaEmessa)
  {
    m_pVerbaliInfatturazione->m_strFilter.Format("Fattura = 0 AND InFatturazione = 1 AND IntestatarioFattura = %d", m_lCodiceAzienda);
    if(m_bFatturaProForma)
      m_nNumCopie = 1;
  }
  else
    m_pVerbaliInfatturazione->m_strFilter.Format("Fattura = %d", m_lCodiceFatturaEmessa);
  m_pVerbaliInfatturazione->Open();
  // Servizi erogati
  codice = 0;
  for(SET_START(m_pVerbaliInfatturazione); !m_pVerbaliInfatturazione->IsEOF(); m_pVerbaliInfatturazione->MoveNext())
  {
    if(codice != m_pVerbaliInfatturazione->m_Codice)
    {
      str.Format("Verbale = %d OR ", m_pVerbaliInfatturazione->m_Codice);
      strFilter += str;
      codice = m_pVerbaliInfatturazione->m_Codice;
    }
  }
  strFilter.TrimRight(" OR ");
  m_pServiziErogati = new CServiziErogatiSet(&pApp->m_db);
  if(strFilter.IsEmpty())
    str.Format("Fattura = %ld", m_lCodiceFatturaEmessa);
  else
    str.Format("Fattura = %d AND (%s)", m_lCodiceFatturaEmessa, strFilter);
  m_pServiziErogati->m_strFilter = str;
  m_pServiziErogati->Open();
  m_pAziendeSet = m_pDoc->m_pAziendeSet;
  SINCRONIZE(m_pAziendeSet, m_lCodiceAzienda);
  if(m_lCodiceFatturaEmessa > 0)
  {
    m_BtnStampaFattura.EnableWindow();
		m_BtnFatturaXML.EnableWindow();
    SINCRONIZE(m_pFattureEmesseSet, m_lCodiceFatturaEmessa);
    m_strNumero.Format("%d", m_pFattureEmesseSet->m_Numero);
    m_lMaxNumFattura = m_pFattureEmesseSet->m_Numero;
    m_DTCtrlDataFattura.SetTime(&m_DataFattura);

    m_nRitAcconto = (int)m_pFattureEmesseSet->m_RitAcconto;

    m_strAliquota.Format("%.0f", m_pFattureEmesseSet->m_Aliquota);
    m_lTipoPagamento = m_pFattureEmesseSet->m_TipoPagamento;
		// fattura per Pubblica Amministrazione
		if(m_pFattureEmesseSet->m_PA > 0)
			m_bPA = TRUE;
		else
			m_bPA = FALSE;
		// fattura con IVA Differita
		if(m_pFattureEmesseSet->m_IVADifferita > 0)
			m_bIVADifferita = TRUE;
		else
			m_bIVADifferita = FALSE;

    if(!m_pFattureEmesseSet->IsFieldNull(&m_pFattureEmesseSet->m_Spese) && m_pFattureEmesseSet->m_Spese != 0)
    {
      m_bSpedizione = TRUE;
      strMask = m_MskSpeseSpedizione.GetMask();
      str.Format("%.2f", m_pFattureEmesseSet->m_Spese);
      strMask = strMask.Left(strMask.GetLength() - str.GetLength());
      strMask.Replace("#", m_MskSpeseSpedizione.GetPromptChar());
      strMask = strMask + str;
      strMask.Replace('.', ',');
      m_MskSpeseSpedizione.SetText(strMask);
    }
    else
    {
      m_bSpedizione = FALSE;
      strMask = m_MskSpeseSpedizione.GetMask();
      strMask.Replace("#", m_MskSpeseSpedizione.GetPromptChar());
      m_MskSpeseSpedizione.SetText(strMask);
      m_MskSpeseSpedizione.EnableWindow(FALSE);
    }
    m_bSpedSelezionata = m_bSpedizione;
    m_nNumCopie = 1;
  }
  else
  {
    m_BtnEmettiFattura.EnableWindow(!m_bFatturaProForma);
    m_BtnStampaFattura.EnableWindow(m_bFatturaProForma);
		m_BtnFatturaXML.EnableWindow(m_bFatturaProForma);
    FindMaxNumeroFattura();
    if(m_bFatturaProForma)
      m_strNumero = "0";
    else
      m_strNumero.Format("%d", m_lMaxNumFattura);
    m_DTCtrlDataFattura.SetTime(&m_DataFattura);
    strMask = m_MskSpeseSpedizione.GetMask();
    strMask.Replace("#", m_MskSpeseSpedizione.GetPromptChar());
    m_MskSpeseSpedizione.SetText(strMask);
    m_MskSpeseSpedizione.EnableWindow(FALSE);
  }
  m_BtnEmettiFattura.SetFocus();
  m_bFatturaEmessa = FALSE;
  // Inizalizzo la combo dei tipi di pagamento
  InitTipiPagamento();
  // Calcolo il valore dell'iva e il totale
  str = m_strImponibileScontato;
  str.Replace(".", "");
  str.Replace(",", ".");
  double dImporto = atof(str);
  m_nImponibileScontato = (int)(dImporto * 100 + 0.5);
  double dIVA = (dImporto * atof(m_strAliquota) / 100);
  m_nIVA = (int)(dIVA * 100 + 0.5);
  m_strImporto = m_strImponibile;
  m_strImportoScontato = m_strImponibileScontato;
  Valuta iva(m_nIVA);
  m_strIVA = m_strImportoIVA = iva.Format(-1, TRUE);

  CalcolaTotale();

  UpdateData(FALSE);
	return FALSE;  
}


void CStampaFattureDlg::OnButtonEmetti() 
{
  int n;
  CString str1, str2;
  UpdateData();
  m_DTCtrlDataFattura.GetTime(m_DataFattura);
  if(!CheckData())
  {
    AfxMessageBox(VERIFY_DATA_MSG);
    return;
  }
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CalcolaTotale();
  // Modifica ad una fattura già emessa
  if(m_lCodiceFatturaEmessa > 0)
  {
    SalvaFattura();
    return;
  }
  // Ho emesso una nuova fattura
  // Sincronizzo i recodset delle aziende e dei tipi di pagamento
  CTipiPagamentoSet* pTipiPagamentoSet = m_pDoc->m_pTipiPagamentoSet;
  if((n = m_ComboTipoPagamento.GetCurSel()) != -1)
  {
    // Se ho selezionato un nuovo tipo di pagamento, aggiorno il record
    if(m_ComboTipoPagamento.GetItemData(n) != 0)
      m_lTipoPagamento= m_ComboTipoPagamento.GetItemData(n);
  }
  else
  {
    if(!m_pAziendeSet->IsFieldNull(&m_pAziendeSet->m_TipoPagamento) && m_pAziendeSet->m_TipoPagamento != 0)
      m_lTipoPagamento = m_pAziendeSet->m_TipoPagamento;
  }
  SINCRONIZE(pTipiPagamentoSet, m_lTipoPagamento);
  m_strTipoPagamento = pTipiPagamentoSet->m_Nome;
  try
  {
    pApp->LockTable(FATTURE);
    // Numero fattura
    FindMaxNumeroFattura();
    // Creo il nuovo record per la fattura emessa
    m_pFattureEmesseSet->AddNew();
    // Tipo di documento
    m_pFattureEmesseSet->m_TipoDocumento = m_nTipoDocumento;
    // Dati fattura
    m_pFattureEmesseSet->m_Numero     = m_lMaxNumFattura;
    m_pFattureEmesseSet->m_Data       = m_DataFattura;
    m_pFattureEmesseSet->m_Aliquota   = atof(m_strAliquota);
    m_pFattureEmesseSet->m_Spese      = m_dSpeseSpedizione;
    m_pFattureEmesseSet->m_Archiviata = FALSE;
    m_pFattureEmesseSet->m_Imponibile = (double)m_nTotaleFattura / 100;
    m_pFattureEmesseSet->m_RitAcconto = (double)m_nRitAcconto ;
    // Tipo di pagamento
    m_pFattureEmesseSet->m_TipoPagamento = m_lTipoPagamento;
    m_pFattureEmesseSet->m_Pagamento     = m_strTipoPagamento;
    m_pFattureEmesseSet->m_BancaAppoggio = pTipiPagamentoSet->m_Banca;
    m_pFattureEmesseSet->m_ABIAppoggio   = pTipiPagamentoSet->m_ABI;
    m_pFattureEmesseSet->m_CABAppoggio   = pTipiPagamentoSet->m_CAB;
    m_pFattureEmesseSet->m_CINAppoggio   = pTipiPagamentoSet->m_CIN;
    m_pFattureEmesseSet->m_ContoAppoggio = pTipiPagamentoSet->m_NumeroConto;
    // Scadenza
    m_pFattureEmesseSet->m_Scadenza = pApp->GetScadenza(m_DataFattura, pTipiPagamentoSet->m_GiorniPrimaScad, pTipiPagamentoSet->m_Allineamento);
		// Dati intestatario
    m_pFattureEmesseSet->m_Intestatario = m_lCodiceAzienda;
    m_pFattureEmesseSet->m_RagioneSociale = m_strRagioneSociale;
    m_pFattureEmesseSet->m_IDIntestatario = m_strCodice;
    m_pFattureEmesseSet->m_P_IVA = m_strPIVA;
    m_pFattureEmesseSet->m_CodiceFiscale = m_strCodFiscale;
    m_pFattureEmesseSet->m_Indirizzo = m_pAziendeSet->m_Indirizzo;
    m_pFattureEmesseSet->m_CAP = m_pAziendeSet->m_CAP;
    m_pFattureEmesseSet->m_Citta = m_pAziendeSet->m_Citta;
    m_pFattureEmesseSet->m_Provincia = m_pAziendeSet->m_Provincia;
    m_pFattureEmesseSet->m_Note = m_pAziendeSet->m_Note;
    m_pFattureEmesseSet->m_Sconto = m_dSconto;
    m_pFattureEmesseSet->m_Banca = m_strBanca;
    m_pFattureEmesseSet->m_ABI = m_strABI;
    m_pFattureEmesseSet->m_CAB = m_strCAB;
		if(m_bPA == TRUE)
			m_pFattureEmesseSet->m_PA				= 1;
		else
			m_pFattureEmesseSet->m_PA				= 0;
		if(m_bIVADifferita == TRUE)
			m_pFattureEmesseSet->m_IVADifferita	= 1;
		else
			m_pFattureEmesseSet->m_IVADifferita	= 0;
    // fattura elettronica
		if(m_bElett == TRUE)
			m_pFattureEmesseSet->m_Elett				= 1;
		else
			m_pFattureEmesseSet->m_Elett				= 0;

    m_pFattureEmesseSet->Update();
    // Aggiorno
    m_pFattureEmesseSet->Requery();
    // Prendo il codice della fattura per scriverlo nei servizi compresi nella fattura
    m_lCodiceFatturaEmessa = 0;
    for(SET_START(m_pFattureEmesseSet); !m_pFattureEmesseSet->IsEOF(); m_pFattureEmesseSet->MoveNext())
    {
      if(m_lCodiceFatturaEmessa < m_pFattureEmesseSet->m_Codice)
        m_lCodiceFatturaEmessa = m_pFattureEmesseSet->m_Codice;
    }
    pApp->UnlockTables();
  }
  catch(CDBException* e)
  {
    pApp->UnlockTables();
    AfxMessageBox(e->m_strError);
    return;
  }  
  // Sincronizzo il recordset delle fatture
  SINCRONIZE(m_pFattureEmesseSet, m_lCodiceFatturaEmessa);
  CSerieSet* pSerieSet = new CSerieSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
  pSerieSet->m_strFilter = "Codice = 0";
  pSerieSet->Open();
  BOOL bCertificato = TRUE;
  // Aggiorno i record dei servizi erogati e del verbale
  for(SET_START(m_pVerbaliInfatturazione); !m_pVerbaliInfatturazione->IsEOF(); m_pVerbaliInfatturazione->MoveNext())
  {
    bCertificato = TRUE;
    m_pVerbaliInfatturazione->Edit();
    m_pVerbaliInfatturazione->m_NumeroFattura = m_lCodiceFatturaEmessa;
    // Se i certificati di questo verbale sono tutti stati emessi, chiudoil verbale
    pSerieSet->m_strFilter.Format("Verbale = %ld", m_pVerbaliInfatturazione->m_Codice);
    pSerieSet->Requery();
    for(SET_START(pSerieSet); !pSerieSet->IsEOF(); pSerieSet->MoveNext())
    {
      if(pSerieSet->IsFieldNull(&pSerieSet->m_Certificato) || pSerieSet->m_Certificato == 0)
      {
        bCertificato = FALSE;
        break;
      }
    }
    if(!m_pVerbaliInfatturazione->m_LungaScadenza && bCertificato)
      m_pVerbaliInfatturazione->m_DataChiusura = m_DataFattura;
    m_pVerbaliInfatturazione->Update();
  }
  pSerieSet->Close();
  // Scrivo il codice nella fattura nel recordset dei servizi erogati
  for(n = 0; n < m_aryCodiciServizi.GetSize(); n++)
  {
    for(SET_START(m_pServiziErogati); !m_pServiziErogati->IsEOF(); m_pServiziErogati->MoveNext())
    {
      if((long)m_aryCodiciServizi.GetAt(n) == m_pServiziErogati->m_Codice)
      {
        m_pServiziErogati->Edit();
        m_pServiziErogati->m_Fattura = m_lCodiceFatturaEmessa;
        m_pServiziErogati->Update();
      }
    }
  }
  m_BtnEmettiFattura.EnableWindow(FALSE);
  m_BtnSpedizione.EnableWindow(FALSE);
  m_MskSpeseSpedizione.EnableWindow(FALSE);  
  // Abilito il pulsante di stampa e setto il flag di fattura emessa
  m_BtnStampaFattura.EnableWindow();
	m_BtnFatturaXML.EnableWindow();
  m_bFatturaEmessa = TRUE;
}

void CStampaFattureDlg::SalvaFattura(void)
{
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  int n;
  CTipiPagamentoSet* pTipiPagamentoSet = m_pDoc->m_pTipiPagamentoSet;

  // Sincronizzo il recordset delle fatture
  SINCRONIZE(m_pFattureEmesseSet, m_lCodiceFatturaEmessa);
  // Ho fatto modifiche ad una fattura già emessa
  pApp->LockTable(FATTURE);
  m_pFattureEmesseSet->Edit();
  m_pFattureEmesseSet->m_Data = m_DataFattura;
  if((n = m_ComboTipoPagamento.GetCurSel()) != -1)
  {
    // Se ho selezionato un nuovo tipo di pagamento, aggiorno il record
    if(m_ComboTipoPagamento.GetItemData(n) != 0)
    {
      m_lTipoPagamento = m_pFattureEmesseSet->m_TipoPagamento = m_ComboTipoPagamento.GetItemData(n);
      SINCRONIZE(pTipiPagamentoSet, m_lTipoPagamento);
      m_pFattureEmesseSet->m_Scadenza = pApp->GetScadenza(m_DataFattura, pTipiPagamentoSet->m_GiorniPrimaScad, pTipiPagamentoSet->m_Allineamento);
      m_pFattureEmesseSet->m_Pagamento = pTipiPagamentoSet->m_Nome;
      m_pFattureEmesseSet->m_BancaAppoggio = pTipiPagamentoSet->m_Banca;
      m_pFattureEmesseSet->m_ABIAppoggio   = pTipiPagamentoSet->m_ABI;
      m_pFattureEmesseSet->m_CABAppoggio   = pTipiPagamentoSet->m_CAB;
      m_pFattureEmesseSet->m_CINAppoggio   = pTipiPagamentoSet->m_CIN;
      m_pFattureEmesseSet->m_ContoAppoggio = pTipiPagamentoSet->m_NumeroConto;
    }
  }
  m_pFattureEmesseSet->m_Aliquota = atof(m_strAliquota);
  if(m_bSpedizione)
    m_pFattureEmesseSet->m_Spese = m_dSpeseSpedizione;
  else
    m_pFattureEmesseSet->m_Spese    = 0;
  m_pFattureEmesseSet->m_Archiviata = FALSE;
  m_pFattureEmesseSet->m_Sconto     = m_dSconto;
  m_pFattureEmesseSet->m_Banca      = m_strBanca;
  m_pFattureEmesseSet->m_ABI        = m_strABI;
  m_pFattureEmesseSet->m_CAB        = m_strCAB;
  m_pFattureEmesseSet->m_Imponibile = (double)m_nTotaleFattura / 100;
  m_pFattureEmesseSet->m_RitAcconto = (double)m_nRitAcconto;
	if(m_bPA == TRUE)
		m_pFattureEmesseSet->m_PA				= 1;
	else
		m_pFattureEmesseSet->m_PA				= 0;
	if(m_bIVADifferita == TRUE)
		m_pFattureEmesseSet->m_IVADifferita	= 1;
	else
		m_pFattureEmesseSet->m_IVADifferita	= 0;

  m_pFattureEmesseSet->Update();
  pApp->UnlockTables();
}

void CStampaFattureDlg::PrnFromFattToFatt(int DaNumFatt, int ANumFatt, CString Anno, CWinSigmaDoc* pDoc)
{
	CString strMask;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	
	CPrintInterpreter prn;
  CString str, strFilter, strLayout;
	CStringArray strNames, strValues;
	CVerbaliServErogatiSet* pVerSerErog;
  BOOL bSconto = FALSE;
	HDC hDC = NULL;

	//Controllo la validità dei parametri
	if (!DaNumFatt || !ANumFatt || Anno.IsEmpty() || (ANumFatt < DaNumFatt))
		return;

	m_pDoc = pDoc;
	m_nNumCopie = 1;
	
	//Apro la tabella per reperire i Verbali messi in fatturazione
	m_pVerbaliInfatturazione	= new CVerbaliSet(&pApp->m_db);
	m_pVerbaliInfatturazione->Open();
	
	//Apro la tabella dei Verbali e dei Servizi Erogati
	pVerSerErog = new CVerbaliServErogatiSet(&pApp->m_db);
	pVerSerErog->m_strFilter = "VERBALI.Codice = 0";
	pVerSerErog->Open();
	
	//Apro la tabella per reperire i Servizi Erogati
	m_pServiziErogati					= new CServiziErogatiSet(&pApp->m_db);
	m_pServiziErogati->Open();

	//Reperisco la tabella Aziende dal Documento Attivo
	m_pAziendeSet = m_pDoc->m_pAziendeSet;

	//Reperisco la tabella Fatture dal Documento Attivo
	m_pFattureEmesseSet = m_pDoc->m_pFattureEmesseSet;
	

	CPrintDialog dialogPrt(TRUE);

	if (dialogPrt.DoModal() == IDCANCEL)
		return;

	if(!(hDC = dialogPrt.CreatePrinterDC()))
		return;

	if(!prn.PrePrinting(hDC))
		return;

	m_pFattureEmesseSet->m_strFilter.Format("(Data > '%s-01-01') AND (Numero >= %d) AND (Numero <= %d)", Anno ,DaNumFatt, ANumFatt);
	m_pFattureEmesseSet->m_strSort = "Numero";
	m_pFattureEmesseSet->Requery();

	for(SET_START(m_pFattureEmesseSet); !m_pFattureEmesseSet->IsEOF(); m_pFattureEmesseSet->MoveNext())
	{
		m_lCodiceFatturaEmessa = m_pFattureEmesseSet->m_Codice;
		m_lCodiceAzienda = m_pFattureEmesseSet->m_Intestatario;

		pVerSerErog->m_strFilter.Format("(SERVIZI_EROGATI.Verbale = VERBALI.Codice)  AND VERBALI.Fattura = %d", m_lCodiceFatturaEmessa);
		pVerSerErog->m_strSort = "SERVIZI_EROGATI.Verbale,SERVIZI_EROGATI.ID_Listino,SERVIZI_EROGATI.Codice";
		pVerSerErog->Requery();

		m_pVerbaliInfatturazione->m_strFilter.Format("Fattura = %d", m_lCodiceFatturaEmessa);
		m_pVerbaliInfatturazione->m_strSort = "Codice";
		m_pVerbaliInfatturazione->Requery();

		m_pServiziErogati->m_strFilter.Format("Fattura = %d", m_lCodiceFatturaEmessa);
		m_pServiziErogati->m_strSort = "Verbale,ID_Listino,Codice";
		m_pServiziErogati->Requery();

		double Imponibile = 0;

		for (SET_START(pVerSerErog); !pVerSerErog->IsEOF(); pVerSerErog->MoveNext())
		{
			double Val = (pVerSerErog->m_Prezzo * pVerSerErog->m_Quantita) -
										(
										((pVerSerErog->m_Prezzo * pVerSerErog->m_Quantita) * pVerSerErog->m_Sconto)/100
										);

			Imponibile += Val;

			if(pVerSerErog->m_VuoiUrgenza == 1)
				Imponibile += (Val/2);
		}

		m_strImporto.Format("%.2f", Imponibile);

		m_nImponibileScontato	= (int)(((Imponibile - ((Imponibile * m_pFattureEmesseSet->m_Sconto) / 100)) * 100) + 0.5);

		double dIVA = ((Imponibile - ((Imponibile * m_pFattureEmesseSet->m_Sconto) / 100)) *  m_pFattureEmesseSet->m_Aliquota / 100);
		m_nIVA = (int)(dIVA * 100 + 0.5);

		m_nTotaleFattura = (int)((m_pFattureEmesseSet->m_Imponibile + 
													   ((m_pFattureEmesseSet->m_Imponibile * m_pFattureEmesseSet->m_Aliquota) / 100) - 
													   ((m_pFattureEmesseSet->m_Imponibile * m_pFattureEmesseSet->m_RitAcconto) / 100) * 100) + 0.5);
	
		m_nRitAcconto = (int) (m_pFattureEmesseSet->m_RitAcconto);

		m_strSconto.Format("%.2f", m_pFattureEmesseSet->m_Sconto);

		if(m_pFattureEmesseSet->m_Spese > 0)
		{
			m_bSpedizione = TRUE;
			m_bSpedSelezionata = TRUE;
			m_nSpeseSpedizione = (int)((m_pFattureEmesseSet->m_Spese * 100) + 0.5);
			m_dSpeseSpedizione = m_pFattureEmesseSet->m_Spese;
		}
		else
		{
			m_bSpedizione = FALSE;
			m_bSpedSelezionata = FALSE;
			m_nSpeseSpedizione = 0;
			m_dSpeseSpedizione = 0;
		}

		CalcolaTotale();

		// Individua il prn da caricare
		for(SET_START(m_pServiziErogati); !m_pServiziErogati->IsEOF(); m_pServiziErogati->MoveNext())
		{
			if(!m_pServiziErogati->IsFieldNull(&m_pServiziErogati->m_Sconto) && m_pServiziErogati->m_Sconto)
			{ 
				bSconto = TRUE;
				break;
			}
		}

		SET_START(m_pServiziErogati);

		if(bSconto)
			strLayout = "\\FattureSconto.prn";
		else
			strLayout = "\\Fatture.prn";

		// Costruisco la stringa dei verbali fatturati
		m_strProgressiviVerbali.Empty();
		m_lCodiceVerbale = 0;
		for(SET_START(m_pVerbaliInfatturazione); !m_pVerbaliInfatturazione->IsEOF(); m_pVerbaliInfatturazione->MoveNext())
		{
			if(m_lCodiceVerbale != m_pVerbaliInfatturazione->m_Codice)
			{
				str.Format("%d", m_pVerbaliInfatturazione->m_ProgressivoTotale);
				m_strProgressiviVerbali += str + " - ";
				m_lCodiceVerbale = m_pVerbaliInfatturazione->m_Codice;

				if ((m_pVerbaliInfatturazione->m_TipoVerbale == VERB_GEOLOGIA)
						&& (m_strProgressiviVerbali.GetAt(m_strProgressiviVerbali.GetLength() - 1) != 'G'))
					m_strProgressiviVerbali += "G";
				else if ((m_pVerbaliInfatturazione->m_TipoVerbale == VERB_IN_CONCESSIONE)
						&& (m_strProgressiviVerbali.GetAt(m_strProgressiviVerbali.GetLength() - 1) != 'C'))
					m_strProgressiviVerbali += "C";
				else if (((m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NON_IN_CONCESSIONE)		||
									(m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NC_PROVE_DI_CARICO)		||
									(m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NC_CONGL_BITUMINOSI)		||
									(m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NC_INERTI)							||
									(m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NC_MONITORAGGI)				||
									(m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NC_VARIE)							||
									(m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NC_GEOTECNICA))
									&& (m_strProgressiviVerbali.GetAt(m_strProgressiviVerbali.GetLength() - 1) != 'C'))
					m_strProgressiviVerbali += "NC";

				m_strProgressiviVerbali += " - ";
			}
		}
		m_strProgressiviVerbali.TrimRight(" - ");

		// Azienda
		if(!m_pAziendeSet)
			m_pAziendeSet = m_pDoc->m_pAziendeSet;
		SINCRONIZE(m_pAziendeSet, m_lCodiceAzienda);
  
		// TipoPagamento
		CTipiPagamentoSet* pPagamentiSet = m_pDoc->m_pTipiPagamentoSet;
  
		SINCRONIZE(pPagamentiSet, m_pFattureEmesseSet->m_TipoPagamento);
		
		m_strCoordinateBancarie.Empty();
		
		// Se è una fattura vecchia, verifico se è una riba dal recordset fatture
		if(!m_pFattureEmesseSet->IsFieldNull(&m_pFattureEmesseSet->m_Scadenza))
			m_bRiba = TRUE;
		else
			m_bRiba = FALSE;

		// Simulazione
		m_lCodiceVerbale = 0;
		m_lCodiceServizio = 0;
		m_bMaggiorazione = FALSE;
		m_bVerbaliPrinted = FALSE;
		m_dAliquota = atof(m_strAliquota);
		str = m_strSconto;
		str.Replace(",", ".");
		m_dSconto = atof(m_strSconto);
		prn.SetPage(1);
		prn.StartSimulation();
		SET_START(m_pVerbaliInfatturazione);
		SET_START(m_pServiziErogati);
		// imposta la stampa con l'header
		if(m_bHeader == TRUE)
		{
			prn.SetHeaderFile(pApp->GetCurrentDirectory() + "\\" + pApp->m_headerFatturePrn);
		}
		if(m_bRaggruppaPerServizio)
			prn.Print(pApp->GetCurrentDirectory() + strLayout, &strNames, &strValues, &ScanDatiFattura, &ScanPerServizio);
		else
			prn.Print(pApp->GetCurrentDirectory() + strLayout, &strNames, &strValues, &ScanDatiFattura, &ScanServizi);
		m_nNumPagine = prn.GetPage() - 1;
		prn.EndSimulation();
		m_pVerbaliInfatturazione->m_strSort = "Codice";
		m_pServiziErogati->m_strSort = "Verbale,ID_Listino,Codice";
		m_pVerbaliInfatturazione->Requery();
		m_pServiziErogati->Requery();

		for(int n = 0; n < m_nNumCopie; n++)
		{
			m_lCodiceVerbale = 0;
			m_bMaggiorazione = FALSE;
			m_bVerbaliPrinted = FALSE;
			m_nImportoVerbale = 0;
			prn.SetPage(1);
			SET_START(m_pVerbaliInfatturazione);
			SET_START(m_pServiziErogati);

			// imposta la stampa con l'header
			if(m_bHeader == TRUE)
			{
				prn.SetHeaderFile(pApp->GetCurrentDirectory() + "\\" + pApp->m_headerFatturePrn);
			}
			if(m_bRaggruppaPerServizio)
				prn.Print(pApp->GetCurrentDirectory() + strLayout, &strNames, &strValues, &ScanDatiFattura, &ScanPerServizio);
			else
				prn.Print(pApp->GetCurrentDirectory() + strLayout, &strNames, &strValues, &ScanDatiFattura, &ScanServizi);
		}
	}

	prn.PostPrinting();
	if(m_pVerbaliInfatturazione)
	{
		if(m_pVerbaliInfatturazione->IsOpen())
			m_pVerbaliInfatturazione->Close();
		delete m_pVerbaliInfatturazione;
	}
	if(m_pServiziErogati)
	{
		if(m_pServiziErogati->IsOpen())
			m_pServiziErogati->Close();
		delete m_pServiziErogati;
	}
	if(pVerSerErog)
	{
		if(pVerSerErog->IsOpen())
			pVerSerErog->Close();
		delete pVerSerErog;
	}
}

void CStampaFattureDlg::OnButtonPrintFattura() 
{
	CPrintInterpreter prn;
  CString str, strFilter, strLayout;
  BOOL bSconto = FALSE;

	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CStringArray strNames, strValues;
	HDC hDC = NULL;

	UpdateData(TRUE);

//	if(!prn.PrePrinting())
//		return;

	CString fname;
  // Recordset delle fatture e dei verbali - servizi erogati
  if(!m_bFatturaProForma)
  {
    SINCRONIZE(m_pFattureEmesseSet, m_lCodiceFatturaEmessa);
    m_pVerbaliInfatturazione->m_strFilter.Format("Fattura = %d", m_lCodiceFatturaEmessa);
    m_pServiziErogati->m_strFilter.Format("Fattura = %d", m_lCodiceFatturaEmessa);
    m_lCodiceAzienda = m_pFattureEmesseSet->m_Intestatario;
		int gg = m_pFattureEmesseSet->m_Data.GetDay();
		int mm = m_pFattureEmesseSet->m_Data.GetMonth();
		int aa = m_pFattureEmesseSet->m_Data.GetYear();
		int numero = m_pFattureEmesseSet->m_Numero;
//		fname.Format("FA-%02d-%02d-%d-%d-%d", gg, mm, aa, numero, m_lCodiceAzienda);
		fname.Format("FA-%02d-%02d-%d-%d-%s", gg, mm, aa, numero, m_pAziendeSet->m_ID);
  }
  else
  {
    m_pVerbaliInfatturazione->m_strFilter.Format("Fattura = 0 AND IntestatarioFattura = %d AND InFatturazione = 1", m_lCodiceAzienda);
    m_pVerbaliInfatturazione->Requery();
    long codice = 0;
    for(SET_START(m_pVerbaliInfatturazione); !m_pVerbaliInfatturazione->IsEOF(); m_pVerbaliInfatturazione->MoveNext())
    {
      if(codice != m_pVerbaliInfatturazione->m_Codice)
      {
        str.Format("Verbale = %d OR ", m_pVerbaliInfatturazione->m_Codice);
        strFilter += str;
        codice = m_pVerbaliInfatturazione->m_Codice;
      }
    }
    strFilter.TrimRight(" OR ");
    str.Format("Fattura = 0 AND (%s)", strFilter);
    m_pServiziErogati->m_strFilter = str;
		CTime curdate = CTime::GetCurrentTime();
		int gg = curdate.GetDay();
		int mm = curdate.GetMonth();
		int aa = curdate.GetYear();
//		fname.Format("FA-PROFORMA-%02d-%02d-%d-%d", gg, mm, aa, m_lCodiceAzienda);
		fname.Format("FA-PROFORMA-%02d-%02d-%d-%s", gg, mm, aa, m_pAziendeSet->m_ID);
  }
	prn.SetDocName(fname);
	if(!prn.PrePrinting())
		return;
  m_pVerbaliInfatturazione->m_strSort = "Codice";
  m_pServiziErogati->m_strSort = "Verbale,ID_Listino,Codice";
  m_pVerbaliInfatturazione->Requery();
  m_pServiziErogati->Requery();
  for(SET_START(m_pServiziErogati); !m_pServiziErogati->IsEOF(); m_pServiziErogati->MoveNext())
  {
    if(!m_pServiziErogati->IsFieldNull(&m_pServiziErogati->m_Sconto) && m_pServiziErogati->m_Sconto)
    { 
      bSconto = TRUE;
      break;
    }
  }
  SET_START(m_pServiziErogati);
  if(bSconto)
    strLayout = "\\FattureSconto.prn";
  else
    strLayout = "\\Fatture.prn";
  // Costruisco la stringa dei verbali fatturati
  m_strProgressiviVerbali.Empty();
  m_lCodiceVerbale = 0;
  for(SET_START(m_pVerbaliInfatturazione); !m_pVerbaliInfatturazione->IsEOF(); m_pVerbaliInfatturazione->MoveNext())
  {
    if(m_lCodiceVerbale != m_pVerbaliInfatturazione->m_Codice)
    {
#ifdef WINSIGMA2
      str.Format("A%d", m_pVerbaliInfatturazione->m_ProgressivoTotale);
#else
      str.Format("%d", m_pVerbaliInfatturazione->m_ProgressivoTotale);
#endif
      m_strProgressiviVerbali += str + " - ";
      m_lCodiceVerbale = m_pVerbaliInfatturazione->m_Codice;

      if ((m_pVerbaliInfatturazione->m_TipoVerbale == VERB_GEOLOGIA)
          && (m_strProgressiviVerbali.GetAt(m_strProgressiviVerbali.GetLength() - 1) != 'G'))
			{
        m_strProgressiviVerbali += "G";
			}
      else if ((m_pVerbaliInfatturazione->m_TipoVerbale == VERB_IN_CONCESSIONE)
          && (m_strProgressiviVerbali.GetAt(m_strProgressiviVerbali.GetLength() - 1) != 'C'))
			{
        m_strProgressiviVerbali += "C";
			}
      else if (	((m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NON_IN_CONCESSIONE)		|| 
								(m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NC_PROVE_DI_CARICO)		||
								(m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NC_CONGL_BITUMINOSI)		||
								(m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NC_INERTI)							||
								(m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NC_MONITORAGGI)				||
								(m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NC_VARIE)							||
								(m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NC_GEOTECNICA))
								 && (m_strProgressiviVerbali.GetAt(m_strProgressiviVerbali.GetLength() - 1) != 'C'))
			{
#ifdef WINSIGMA2
#else
        m_strProgressiviVerbali += "NC";
#endif
			}
      m_strProgressiviVerbali += " - ";
    }
  }
  m_strProgressiviVerbali.TrimRight(" - ");
  // Azienda
  if(!m_pAziendeSet)
    m_pAziendeSet = m_pDoc->m_pAziendeSet;
  SINCRONIZE(m_pAziendeSet, m_lCodiceAzienda);
  
	// TipoPagamento
	CTipiPagamentoSet* pPagamentiSet = m_pDoc->m_pTipiPagamentoSet;
  
	if(m_bFatturaProForma)
  {
    SINCRONIZE(pPagamentiSet, (long)m_ComboTipoPagamento.GetItemData(m_ComboTipoPagamento.GetCurSel()));
  }
  else
  {
    SINCRONIZE(pPagamentiSet, m_pFattureEmesseSet->m_TipoPagamento);
  }
  m_strCoordinateBancarie.Empty();
  // Se è una fattura emessa adesso o una fattuta proforma, verifico se il pagamento è una riba dal recordset dei pagamenti
  if(m_bFatturaEmessa || m_bFatturaProForma)
  {
    if(!pPagamentiSet->IsFieldNull(&pPagamentiSet->m_Allineamento) && pPagamentiSet->m_Allineamento != 0)
      m_bRiba = TRUE;
    else
    {
      m_bRiba = FALSE;
      if(!pPagamentiSet->m_Banca.IsEmpty())
        m_strCoordinateBancarie.Format(" BANCA %s", pPagamentiSet->m_Banca);
      if(!pPagamentiSet->m_ABI.IsEmpty())
      {
        str.Format(" - ABI %s CAB %s", pPagamentiSet->m_ABI, pPagamentiSet->m_CAB);
        m_strCoordinateBancarie += str;
      }
      if(!pPagamentiSet->m_CIN.IsEmpty())
      {
        str.Format(" - CIN %s C/C %s", pPagamentiSet->m_CIN, pPagamentiSet->m_NumeroConto);
        m_strCoordinateBancarie += str;
      }
    }
  }
  else
  {
    // Se è una fattura vecchia, verifico se è una riba dal recordset fatture
    if(!m_pFattureEmesseSet->IsFieldNull(&m_pFattureEmesseSet->m_Scadenza))
      m_bRiba = TRUE;
    else
      m_bRiba = FALSE;
  }
  // Simulazione
  m_bSpedSelezionata = m_bSpedizione;
  m_lCodiceVerbale = 0;
  m_lCodiceServizio = 0;
  m_bMaggiorazione = FALSE;
  m_bVerbaliPrinted = FALSE;
  m_dAliquota = atof(m_strAliquota);
  str = m_strSconto;
  str.Replace(",", ".");
  m_dSconto = atof(m_strSconto);
  prn.SetPage(1);
  prn.StartSimulation();
  SET_START(m_pVerbaliInfatturazione);
  SET_START(m_pServiziErogati);

	// imposta la stampa con l'header
	if(m_bHeader == TRUE)
	{
		prn.SetHeaderFile(pApp->GetCurrentDirectory() + "\\" + pApp->m_headerFatturePrn);
	}

  if(m_bRaggruppaPerServizio)
    prn.Print(pApp->GetCurrentDirectory() + strLayout, &strNames, &strValues, &ScanDatiFattura, &ScanPerServizio);
  else
    prn.Print(pApp->GetCurrentDirectory() + strLayout, &strNames, &strValues, &ScanDatiFattura, &ScanServizi);
  m_nNumPagine = prn.GetPage() - 1;
  prn.EndSimulation();
  m_pVerbaliInfatturazione->m_strSort = "Codice";
  m_pServiziErogati->m_strSort = "Verbale,ID_Listino,Codice";
  m_pVerbaliInfatturazione->Requery();
  m_pServiziErogati->Requery();
  for(int n = 0; n < m_nNumCopie; n++)
  {
    m_lCodiceVerbale = 0;
    m_bMaggiorazione = FALSE;
    m_bVerbaliPrinted = FALSE;
    m_nImportoVerbale = 0;
    prn.SetPage(1);
    SET_START(m_pVerbaliInfatturazione);
    SET_START(m_pServiziErogati);
		// imposta la stampa con l'header
		if(m_bHeader == TRUE)
		{
			prn.SetHeaderFile(pApp->GetCurrentDirectory() + "\\" + pApp->m_headerFatturePrn);
		}
    if(m_bRaggruppaPerServizio)
      prn.Print(pApp->GetCurrentDirectory() + strLayout, &strNames, &strValues, &ScanDatiFattura, &ScanPerServizio);
    else
      prn.Print(pApp->GetCurrentDirectory() + strLayout, &strNames, &strValues, &ScanDatiFattura, &ScanServizi);
  }
  prn.PostPrinting();
  if(m_pVerbaliInfatturazione)
  {
    if(m_pVerbaliInfatturazione->IsOpen())
      m_pVerbaliInfatturazione->Close();
    delete m_pVerbaliInfatturazione;
  }
  if(m_pServiziErogati)
  {
    if(m_pServiziErogati->IsOpen())
      m_pServiziErogati->Close();
    delete m_pServiziErogati;
  }
  
	CDialog::OnOK();
}

int nCntFatture = 0;
int nCntServizi = 0;
BOOL CStampaFattureDlg::ScanDatiFattura(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
  CString str;

  nCntFatture++;
  pFieldNames->RemoveAll();
  pFieldValues->RemoveAll();
  // Intestazione fattura
  pFieldNames->Add("codice");
  pFieldNames->Add("ragioneSociale");
  pFieldNames->Add("indirizzo");
  pFieldNames->Add("datiLocalita");
  pFieldNames->Add("pIVA");
  pFieldNames->Add("codFiscale");
  pFieldNames->Add("tipoPagamento");
  pFieldNames->Add("tipo_documento");
  pFieldNames->Add("numero");
  pFieldNames->Add("data");
  // Per le fatture proforma, prendo i dati dal recordset delle aziende
  if(m_bFatturaProForma)
  {
    // Dati anagrafici dell'intestatario
    pFieldValues->Add(m_pAziendeSet->m_ID);
    str = m_pAziendeSet->m_RagioneSociale;
    str.Replace("&", "&&");
    pFieldValues->Add(str);
    pFieldValues->Add(m_pAziendeSet->m_Indirizzo);
    str.Empty();
    if(!m_pAziendeSet->m_CAP.IsEmpty())
      str = m_pAziendeSet->m_CAP;
    if(!m_pAziendeSet->m_Citta.IsEmpty())
    {
      str += " ";
      str += m_pAziendeSet->m_Citta;
    }
    if(!m_pAziendeSet->m_Provincia.IsEmpty())
    {
      str += " (";
      str += m_pAziendeSet->m_Provincia; 
      str += ")";
    }
    pFieldValues->Add(str);

    // Partita IVA E codice fiscale
    if(!m_pAziendeSet->m_P_IVA.IsEmpty())
      str.Format("P.IVA    %s", m_pAziendeSet->m_P_IVA);
     else
       str = "";

    pFieldValues->Add(str);

    if(!m_pAziendeSet->m_CodiceFiscale.IsEmpty())
      str.Format("Cod.Fiscale    %s", m_pAziendeSet->m_CodiceFiscale);
    else
      str = "";

    pFieldValues->Add(str);

    // Tipo pagamento
    if(!m_bRiba || (m_bRiba && m_pAziendeSet->m_Banca.IsEmpty()))
      str = m_strTipoPagamento + m_strCoordinateBancarie;
    else
    {
      if(m_pAziendeSet->m_ABI.IsEmpty() || m_pAziendeSet->m_CAB.IsEmpty())
        str.Format("%s - BANCA %s", m_strTipoPagamento, m_pAziendeSet->m_Banca);
      else
        str.Format("%s - BANCA %s - ABI %s CAB %s", m_strTipoPagamento, m_pAziendeSet->m_Banca, m_pAziendeSet->m_ABI, m_pAziendeSet->m_CAB);
    }
    pFieldValues->Add(str);
    // Numero e data fattura
    pFieldValues->Add("Fattura proforma");  // Tipo documento
    pFieldValues->Add("");                  // Numero
    str.Format("del %s", CTime::GetCurrentTime().Format("%d/%m/%y"));
    pFieldValues->Add(str);
  }
  else
  {
    // Per le fatture emesse prendo i dati dal recordset delle fatture
    pFieldValues->Add(m_pFattureEmesseSet->m_IDIntestatario);
    str = m_pFattureEmesseSet->m_RagioneSociale;
    str.Replace("&", "&&");
    pFieldValues->Add(str);
    pFieldValues->Add(m_pFattureEmesseSet->m_Indirizzo);
    str.Empty();
    if(!m_pFattureEmesseSet->m_CAP.IsEmpty())
      str = m_pFattureEmesseSet->m_CAP;
    if(!m_pFattureEmesseSet->m_Citta.IsEmpty())
    {
      str += " ";
      str += m_pFattureEmesseSet->m_Citta;
    }
    if(!m_pFattureEmesseSet->m_Provincia.IsEmpty())
    {
      str += " (";
      str += m_pFattureEmesseSet->m_Provincia; 
      str += ")";
    }
    pFieldValues->Add(str);

    // Partita IVA E codice fiscale
    if(!m_pAziendeSet->m_P_IVA.IsEmpty())
      str.Format("P.IVA    %s", m_pAziendeSet->m_P_IVA);
     else
       str = "";

    pFieldValues->Add(str);

    if(!m_pAziendeSet->m_CodiceFiscale.IsEmpty())
      str.Format("Cod.Fiscale    %s", m_pAziendeSet->m_CodiceFiscale);
    else
      str = "";

    pFieldValues->Add(str);

    // Tipo pagamento
    if(!m_bRiba || (m_bRiba && m_pFattureEmesseSet->m_Banca.IsEmpty()))
    {
      str = m_strTipoPagamento;
      if(!m_pFattureEmesseSet->m_BancaAppoggio.IsEmpty())
      {
        if(m_pFattureEmesseSet->m_ABIAppoggio.IsEmpty() || m_pFattureEmesseSet->m_CABAppoggio.IsEmpty())
          str.Format("%s - Banca d'appoggio %s", m_strTipoPagamento, m_pFattureEmesseSet->m_BancaAppoggio);
        else
        {
          CString str2;
          if(!m_pFattureEmesseSet->m_CINAppoggio.IsEmpty())
            str2.Format("- CIN %s C/C %s", m_pFattureEmesseSet->m_CINAppoggio, m_pFattureEmesseSet->m_ContoAppoggio);
          str.Format("%s - Banca d'appoggio %s - ABI %s CAB %s %s", m_strTipoPagamento, m_pFattureEmesseSet->m_BancaAppoggio, m_pFattureEmesseSet->m_ABIAppoggio, m_pFattureEmesseSet->m_CABAppoggio, str2);
        }
      }
    }
    else
    {
      if(m_pFattureEmesseSet->m_ABI.IsEmpty() || m_pFattureEmesseSet->m_CAB.IsEmpty())
        str.Format("%s - BANCA %s", m_strTipoPagamento, m_pFattureEmesseSet->m_Banca);
      else
        str.Format("%s - BANCA %s - ABI %s CAB %s", m_strTipoPagamento, m_pFattureEmesseSet->m_Banca, m_pFattureEmesseSet->m_ABI, m_pFattureEmesseSet->m_CAB);
    }
    pFieldValues->Add(str);
    // Numero e data fattura  
    pFieldValues->Add(m_strTipoDocumento + " n.");
    str.Format("%d", m_pFattureEmesseSet->m_Numero);
    pFieldValues->Add(str);
    str.Format("del %s", m_pFattureEmesseSet->m_Data.Format("%d/%m/%y"));
    pFieldValues->Add(str);
  }
  // Numero pagina
  pFieldNames->Add("pagina");
  str.Format(" / %d", m_nNumPagine);
  pFieldValues->Add(str);
  // Verbali fatturati
  if(m_pVerbaliInfatturazione->m_TipoVerbale != VERB_PER_FATTURA && m_pVerbaliInfatturazione->m_TipoVerbale != VERB_PER_NOTACREDITO)
  {
    pFieldNames->Add("verbali");
    pFieldValues->Add(m_strProgressiviVerbali);
  }
  // Scadenza e importo
  if(!m_bFatturaProForma && !m_pFattureEmesseSet->IsFieldNull(&m_pFattureEmesseSet->m_Scadenza))
  {
    pFieldNames->Add("scadenza");
    pFieldValues->Add(m_pFattureEmesseSet->m_Scadenza.Format("%d/%m/%y"));
  }
  pFieldNames->Add("totImporto");
  pFieldValues->Add(m_strTotaleFattura);
  // Totale imponibile
  pFieldNames->Add("importo");
  pFieldValues->Add(m_strImportoScontato);
  pFieldNames->Add("imponibile");
  pFieldValues->Add(m_strImporto);
  // IVA
  pFieldNames->Add("aliquota");
  pFieldNames->Add("iva");
  if(!m_bFatturaProForma)
    m_dAliquota = m_pFattureEmesseSet->m_Aliquota;
  if(m_dAliquota != 0)
  {
    str.Format("I.V.A.  %0.f %%", m_dAliquota);
    pFieldValues->Add(str);
  }
  else
    pFieldValues->Add("Esente I.V.A.");
  pFieldValues->Add(m_strIVA);

  // Ritenuta Acconto se la fattura è proforna la ritenuta non viene stampata
  pFieldNames->Add("ritacconto");
  if (m_pFattureEmesseSet->m_RitAcconto > 0)
    str.Format("Rit. Acconto %2.0f%%", m_pFattureEmesseSet->m_RitAcconto);
  else if (m_nRitAcconto != 0)
  {
    str.Format("Rit. Acconto %2.0d%%", m_nRitAcconto);
  }
  else
    str = "";
  pFieldValues->Add(str);

  // Totale Ritenuta Acconto
  pFieldNames->Add("totritacconto");
  if (m_nTotRitAcconto > 0)
  {
    double RA = m_nTotRitAcconto / 100.0;
    str.Format("%.2f", RA);
  }
  else
    str = "";
  pFieldValues->Add(str);

  // Spese di spedizione
  if(m_bSpedSelezionata)
  {
    pFieldNames->Add("spedizione");
    pFieldValues->Add("Esente Art.15*");
    pFieldNames->Add("spesespedizione");
    Valuta spese(m_dSpeseSpedizione);
    pFieldValues->Add(spese.Format());
    pFieldNames->Add("notaSpedizione");
    pFieldValues->Add("*Trattasi di spese postali");
  }
  // Totale fattura
  pFieldNames->Add("totale");
  pFieldValues->Add(m_strTotaleFattura);
  // Sconto
  if(m_dSconto)
  {
    pFieldNames->Add("sconto");
    str.Format("Sconto fattura  %.2f%%", m_dSconto);
    pFieldValues->Add(str);
  }
  return FALSE;
}

BOOL CStampaFattureDlg::ScanServizi(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
  CString str, str2;
  double dImporto = 0.;
  double dPrezzo = 0.;

  nCntServizi++;
  pFieldNames->RemoveAll();
  pFieldValues->RemoveAll();
  if(m_lCodiceVerbale != m_pVerbaliInfatturazione->m_Codice || m_pVerbaliInfatturazione->IsEOF())
  {
    // Maggiorazione
    if(m_bMaggiorazione)
    {
      pFieldNames->Add("descrizione");
      pFieldValues->Add("Maggiorazione del 50% per diritto procedura d'urgenza");
      Valuta maggiorazione(((double)m_nImportoVerbale / 2));
      pFieldNames->Add("importo");
      pFieldValues->Add(maggiorazione.Format(-1, TRUE));
      m_bMaggiorazione = FALSE;
      m_nImportoVerbale = 0;
      if(m_pVerbaliInfatturazione->IsEOF() && m_pServiziErogati->IsEOF())
        return FALSE;
      return TRUE;
    }
  }
  if(m_pVerbaliInfatturazione->IsEOF() && m_pServiziErogati->IsEOF())
  {
    m_lCodiceVerbale = 0;
    m_nImportoVerbale = 0;
    m_bMaggiorazione = FALSE;
    return FALSE;
  }
  if(m_lCodiceVerbale != m_pVerbaliInfatturazione->m_Codice)
  {
    m_lCodiceVerbale = m_pVerbaliInfatturazione->m_Codice;
    m_nImportoVerbale = 0;
    m_pServiziErogati->m_strFilter.Format("Verbale = %d", m_lCodiceVerbale);
    m_pServiziErogati->Requery();
    // Quando cambio verbale, prima dei servizi metto il verbale di riferimento
    // Verbale di riferimento
    if(m_pVerbaliInfatturazione->m_TipoVerbale != VERB_PER_FATTURA && m_pVerbaliInfatturazione->m_TipoVerbale != VERB_PER_NOTACREDITO)
    {
      pFieldNames->Add("descrizione");
#ifdef WINSIGMA2
      str.Format("VA A%d del %s - Cant.: %s", m_pVerbaliInfatturazione->m_ProgressivoTotale, m_pVerbaliInfatturazione->m_DataAccettazione.Format("%d/%m/%y"), m_pVerbaliInfatturazione->m_Cantiere);
#else
      str.Format("VA %d/%d del %s - Cant.: %s", m_pVerbaliInfatturazione->m_ProgressivoParziale, m_pVerbaliInfatturazione->m_ProgressivoTotale, m_pVerbaliInfatturazione->m_DataAccettazione.Format("%d/%m/%y"), m_pVerbaliInfatturazione->m_Cantiere);
#endif
      str.Replace("\r\n", " ");
      pFieldValues->Add(str);
      // Maggiorazione
      if((m_pVerbaliInfatturazione->m_Urgenza) && (m_pVerbaliInfatturazione->m_Urgenza != 2))
        m_bMaggiorazione = TRUE;
      else
        m_bMaggiorazione = FALSE;
      if(m_pServiziErogati->IsEOF())
        m_pVerbaliInfatturazione->MoveNext();
      return TRUE;
    }
    if(m_pServiziErogati->IsEOF())
    {
      m_pVerbaliInfatturazione->MoveNext();
      if(m_pVerbaliInfatturazione->IsEOF() && !m_bMaggiorazione)
        return FALSE;
    }
    return TRUE;
  }
  if(m_lCodiceVerbale == m_pVerbaliInfatturazione->m_Codice)
  {
    // Codici
    pFieldNames->Add("codici");
    if(m_pServiziErogati->m_ID_Listino != ID_SERVIZI_NO_LISTINO)
      pFieldValues->Add(m_pServiziErogati->m_ID_Listino);
    else
      pFieldValues->Add("");
    // Descrizione
    pFieldNames->Add("descrizione");
    if(!m_pServiziErogati->m_Nome.IsEmpty())
      pFieldValues->Add(m_pServiziErogati->m_Nome);
    else
      pFieldValues->Add(m_pServiziErogati->m_Descrizione);
    // Per i servizi a prezzo zero non metto gli altri campi
    if(m_pServiziErogati->m_Prezzo != 0.)
    {
      // Quantità
      pFieldNames->Add("quantità");
      str.Format("%.2f", m_pServiziErogati->m_Quantita);
      pFieldValues->Add(str);
      // Prezzo
      pFieldNames->Add("prezzo");
      dPrezzo = m_pServiziErogati->m_Prezzo;
      Valuta prezzo(dPrezzo);
      pFieldValues->Add(prezzo.Format());
      // Sconto
      pFieldNames->Add("sconto");
      if(!m_pServiziErogati->IsFieldNull(&m_pServiziErogati->m_Sconto) && m_pServiziErogati->m_Sconto != 0)
      {
        str.Format("%.2f", m_pServiziErogati->m_Sconto);
        pFieldValues->Add(str);
      }
      else
        pFieldValues->Add("---");
      // Importo
      pFieldNames->Add("importo");
      dImporto = m_pServiziErogati->m_Prezzo * m_pServiziErogati->m_Quantita;
      if(!m_pServiziErogati->IsFieldNull(&m_pServiziErogati->m_Sconto))
        dImporto = dImporto - (dImporto * m_pServiziErogati->m_Sconto / 100);
      Valuta importo(dImporto);
      if(dImporto < 0)
        m_nImportoVerbale += (int)(dImporto * 100 - 0.5);
      else
        m_nImportoVerbale += (int)(dImporto * 100 + 0.5);
      pFieldValues->Add(importo.Format());  
    }
    m_pServiziErogati->MoveNext();
  }
  if(m_pServiziErogati->IsEOF())
  {
    m_pVerbaliInfatturazione->MoveNext();
    if(m_pVerbaliInfatturazione->IsEOF() && !m_bMaggiorazione)
      return FALSE;
  }
  return TRUE;
}

BOOL CStampaFattureDlg::ScanPerServizio(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
  CString str;
  double dPrezzo, dImporto, dServizi;
  int    nImporto;
  
  pFieldNames->RemoveAll();
  pFieldValues->RemoveAll();

  if(!m_bVerbaliPrinted)
  {
    if(m_bMaggiorazione)
    {
      // Scrivo la maggiorazione
      pFieldNames->Add("descrizione");
      pFieldValues->Add("Maggiorazione del 50% per diritto procedura d'urgenza");
      Valuta maggiorazione(((double)m_nImportoVerbale / 2));
      pFieldNames->Add("importo");
      pFieldValues->Add(maggiorazione.Format(-1, TRUE));
      m_bMaggiorazione = FALSE;
      m_nImportoVerbale = 0;
      return TRUE;
    }
    // Stampo i verbali
    if(m_lCodiceVerbale != m_pVerbaliInfatturazione->m_Codice)
    {
      m_lCodiceVerbale = m_pVerbaliInfatturazione->m_Codice;
      m_nImportoVerbale = 0;
      if(m_pVerbaliInfatturazione->m_TipoVerbale != VERB_PER_FATTURA && m_pVerbaliInfatturazione->m_TipoVerbale != VERB_PER_NOTACREDITO)
      {
        pFieldNames->Add("descrizione");
        str.Format("VA %d/%d del %s - Cant.: %s", m_pVerbaliInfatturazione->m_ProgressivoParziale, m_pVerbaliInfatturazione->m_ProgressivoTotale, m_pVerbaliInfatturazione->m_DataAccettazione.Format("%d/%m/%y"), m_pVerbaliInfatturazione->m_Cantiere);
        str.Replace("\r\n", " ");
        pFieldValues->Add(str);
        
        if (m_pVerbaliInfatturazione->m_Urgenza != 2)
          m_bMaggiorazione = m_pVerbaliInfatturazione->m_Urgenza;
        
        if(!m_bMaggiorazione)
        {
          // Scorro il recordset fino al prossimo verbale
          while(!m_pVerbaliInfatturazione->IsEOF())
          {
            m_pVerbaliInfatturazione->MoveNext();
            if(m_lCodiceVerbale != m_pVerbaliInfatturazione->m_Codice)
              break;
          }
          return TRUE;
        }
        m_pServiziErogati->m_strFilter.Format("Verbale = %d", m_lCodiceVerbale);
        m_pServiziErogati->Requery();
      }
    }
    while(!m_pServiziErogati->IsEOF())
    {
      // Calcolo l'importo verbale per l'eventuale maggiorazione
      dImporto = m_pServiziErogati->m_Prezzo * m_pServiziErogati->m_Quantita;
      if(!m_pServiziErogati->IsFieldNull(&m_pServiziErogati->m_Sconto))
        dImporto = dImporto - (dImporto * m_pServiziErogati->m_Sconto / 100);
      Valuta importo(dImporto);
      if(dImporto < 0)
        m_nImportoVerbale += (int)(dImporto * 100 - 0.5);
      else
        m_nImportoVerbale += (int)(dImporto * 100 + 0.5);
      m_pServiziErogati->MoveNext();
    }
    while(!m_pVerbaliInfatturazione->IsEOF())
    {
      m_pVerbaliInfatturazione->MoveNext();
      if(m_lCodiceVerbale != m_pVerbaliInfatturazione->m_Codice)
        break;
    }
    // Passo alla stampa dei servizi
    if(m_pVerbaliInfatturazione->IsEOF() && !m_bMaggiorazione)
    {
      long codice(0);
      CString strFilter;
      for(SET_START(m_pVerbaliInfatturazione); !m_pVerbaliInfatturazione->IsEOF(); m_pVerbaliInfatturazione->MoveNext())
      {
        if(codice != m_pVerbaliInfatturazione->m_Codice)
        {
          str.Format("Verbale = %d OR ", m_pVerbaliInfatturazione->m_Codice);
          strFilter += str;
          codice = m_pVerbaliInfatturazione->m_Codice;
        }
      }
      strFilter.TrimRight(" OR ");
      m_pServiziErogati->m_strFilter = strFilter;
      m_pServiziErogati->m_strSort = "ID_Listino,Sconto";
      m_pServiziErogati->Requery();
      SET_START(m_pServiziErogati);
      m_bVerbaliPrinted = TRUE;
      dServizi = 0;
      m_lCodiceServizio = -1;
      m_lCodiceVerbale = 0;
    }
  }
  if(m_bVerbaliPrinted)
  {
    // Stampo i servizi
    if(m_lCodiceServizio != m_pServiziErogati->m_CodiceServizio)
    {
      // Cambio servizio
      CVerbaliServErogatiSet* pSet = new CVerbaliServErogatiSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
      dServizi = 0;
      m_lCodiceServizio = m_pServiziErogati->m_CodiceServizio;
      pSet->m_strFilter.Format("Verbale = VERBALI.Codice AND SERVIZI_EROGATI.Fattura = %d AND VERBALI.Fattura = %d AND SERVIZI_EROGATI.CodiceServizio = %d", m_lCodiceFatturaEmessa, m_lCodiceFatturaEmessa, m_lCodiceServizio);
      pSet->m_strSort = "ID_Listino,Sconto";
      pSet->Open();
      // Conto i servizi
      for(SET_START(pSet); !pSet->IsEOF(); pSet->MoveNext())
        dServizi += pSet->m_Quantita;
      // Descrizione
      pFieldNames->Add("descrizione");
      pFieldValues->Add(pSet->m_Descrizione);
      if(pSet->m_Prezzo != 0)
      {
        // Codici
        if(pSet->m_IDListino != ID_SERVIZI_NO_LISTINO)
        {
          pFieldNames->Add("codici");
          pFieldValues->Add(pSet->m_IDListino);
          str.Format("%.0f", dServizi);
        }
        else
          str.Format("%.1f", dServizi);
        // Quantità
        pFieldNames->Add("quantità");
        pFieldValues->Add(str);
        // Prezzo
        pFieldNames->Add("prezzo");
        dPrezzo = pSet->m_Prezzo;
        Valuta prezzo(dPrezzo);
        pFieldValues->Add(prezzo.Format());
        // Sconto
        pFieldNames->Add("sconto");
        if(!pSet->IsFieldNull(&pSet->m_Sconto) && pSet->m_Sconto)
        {
          str.Format("%.2f", pSet->m_Sconto);
          pFieldValues->Add(str);
        }
        else
          pFieldValues->Add("---");
        // Importo
        pFieldNames->Add("importo");
        dImporto = pSet->m_Prezzo * dServizi;
        if(!pSet->IsFieldNull(&pSet->m_Sconto))
          dImporto = dImporto - (dImporto * pSet->m_Sconto / 100);
        if(dImporto < 0)
          nImporto = (int)(dImporto * 100 - 0.5);
        else
          nImporto = (int)(dImporto * 100 + 0.5);
        Valuta importo((double)nImporto);
        pFieldValues->Add(importo.Format(-1, TRUE));  
      }
      pSet->Close();
      delete pSet;
    }
    while(!m_pServiziErogati->IsEOF())
    {
      m_pServiziErogati->MoveNext();
      if(m_lCodiceServizio != m_pServiziErogati->m_CodiceServizio)
        break;
    }
    if(m_pServiziErogati->IsEOF())
      return FALSE;
  }
  if(m_pVerbaliInfatturazione->IsEOF() && m_pServiziErogati->IsEOF())
    return FALSE;
  return TRUE;
}

void CStampaFattureDlg::FindMaxNumeroFattura(void)
{
  m_lMaxNumFattura = 0;
	CString csOldFilter = m_pFattureEmesseSet->m_strFilter;
	CString csOldSort = m_pFattureEmesseSet->m_strSort;
	if(m_bElett == TRUE)
	{
		m_pFattureEmesseSet->m_strFilter += " and fElett = 1";
	}
	else
	{
		m_pFattureEmesseSet->m_strFilter += " and fElett = 0";
	}
	m_pFattureEmesseSet->m_strSort = "numero ASC";
	m_pFattureEmesseSet->Requery();
	if(m_pFattureEmesseSet->IsEOF() != TRUE)
	{
		m_pFattureEmesseSet->MoveLast();
		m_lMaxNumFattura = m_pFattureEmesseSet->m_Numero;
	}
/*
  for(SET_START(m_pFattureEmesseSet); !m_pFattureEmesseSet->IsEOF(); m_pFattureEmesseSet->MoveNext())
  {
		if(m_bElett == TRUE)
		{
	    if(m_pFattureEmesseSet->m_Elett == 1 && m_lMaxNumFattura < m_pFattureEmesseSet->m_Numero)
		    m_lMaxNumFattura = m_pFattureEmesseSet->m_Numero;
		}
		else
		{
	    if(m_pFattureEmesseSet->m_Elett == 0 && m_lMaxNumFattura < m_pFattureEmesseSet->m_Numero)
		    m_lMaxNumFattura = m_pFattureEmesseSet->m_Numero;
		}
  }
*/
  // Prima fattura
  if(!m_lMaxNumFattura)
    m_lMaxNumFattura = 1;
  else
    m_lMaxNumFattura += 1; // Per le altre incremento il massimo di 1

	m_pFattureEmesseSet->m_strFilter = csOldFilter;
	m_pFattureEmesseSet->m_strSort = csOldSort;
	m_pFattureEmesseSet->Requery();
}

void CStampaFattureDlg::OnCheckSpedizione() 
{
  UpdateData();
  m_bSpedSelezionata = m_bSpedizione;	
  m_MskSpeseSpedizione.EnableWindow(m_bSpedizione);
  CalcolaTotale();
  UpdateData(FALSE);
}

BEGIN_EVENTSINK_MAP(CStampaFattureDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CStampaFattureDlg)
	ON_EVENT(CStampaFattureDlg, IDC_MASKEDBOX_SPESE_SPEDIZIONE, 1 /* Change */, OnChangeMaskedboxSpeseSpedizione, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CStampaFattureDlg::OnChangeMaskedboxSpeseSpedizione() 
{
  CString str;
  
  str = m_MskSpeseSpedizione.GetText();
	str.Remove('.');
	str.TrimLeft(" _");
	str.Replace(',', '.');
  m_dSpeseSpedizione = atof(str);
  m_nSpeseSpedizione = (int)(m_dSpeseSpedizione * 100 + 0.5);
  CalcolaTotale();
  UpdateData(FALSE);
}

void CStampaFattureDlg::OnChangeEditAliquota() 
{
  UpdateData();
  CString str = m_strImponibileScontato;
  str.Replace(".","");
  str.Replace(",", ".");
  double dImporto = atof(str);
  double dIVA = (dImporto * atof(m_strAliquota) / 100);
  m_nIVA = (int)(dIVA * 100 + 0.5);
  Valuta iva(m_nIVA);
  m_strIVA = m_strImportoIVA = iva.Format(-1, TRUE);
  CalcolaTotale();
  UpdateData(FALSE);
}


void CStampaFattureDlg::OnChangeEditRitAcconto() 
{
  UpdateData();

  CString str = m_csRitAcconto;
  str.Replace(",", ".");
  m_nRitAcconto = atoi(str);
  
  CalcolaTotale();

	UpdateData(FALSE);
}

void CStampaFattureDlg::CalcolaRitAcconto(void)
{
  m_csRitAcconto.Format("%2d", m_nRitAcconto);

  m_nTotRitAcconto = (m_nRitAcconto * m_nImponibileScontato) / 100;
  Valuta TotRitAcc((double)m_nTotRitAcconto);
  m_csTotRitAcconto = TotRitAcc.Format(-1, TRUE);
}

void CStampaFattureDlg::CalcolaTotale(void)
{
  Valuta iva(m_nIVA);
  m_strIVA = m_strImportoIVA = iva.Format(-1, TRUE);
  Valuta impScontato((double)m_nImponibileScontato);
  m_strImportoScontato = m_strImponibileScontato = impScontato.Format(-1, TRUE);
  m_nTotaleFattura = m_nImponibileScontato + m_nIVA + ((m_bSpedizione) ? m_nSpeseSpedizione : 0);

  CalcolaRitAcconto();
  m_nTotaleFattura -= m_nTotRitAcconto;

  Valuta totale(m_nTotaleFattura);
  m_strTotaleFattura = m_strTotale = totale.Format(-1, TRUE);
}

void CStampaFattureDlg::OnCheckPerservizio() 
{
  UpdateData();	
}

void CStampaFattureDlg::InitTipiPagamento(void)
{
  int i;
  CTipiPagamentoSet* pTipiPagamentoSet = m_pDoc->m_pTipiPagamentoSet;
  for(SET_START(pTipiPagamentoSet); !pTipiPagamentoSet->IsEOF(); pTipiPagamentoSet->MoveNext())
  {
  	i = m_ComboTipoPagamento.AddString(pTipiPagamentoSet->m_Nome);
  	m_ComboTipoPagamento.SetItemData(i, pTipiPagamentoSet->m_Codice);
  }
  m_ComboTipoPagamento.SetCurSel(-1);
  for(i = 0; i < m_ComboTipoPagamento.GetCount(); i++)
  {
    if(m_lTipoPagamento == (long)m_ComboTipoPagamento.GetItemData(i))
    {
      SINCRONIZE(pTipiPagamentoSet, m_lTipoPagamento);
      m_strBanca = pTipiPagamentoSet->m_Banca;
      m_strABI   = pTipiPagamentoSet->m_ABI;
      m_strCAB   = pTipiPagamentoSet->m_CAB;
      // Se è un pagamento di tipo riba metto le coordinate bancarie del cliente
      if(!pTipiPagamentoSet->IsFieldNull(&pTipiPagamentoSet->m_Allineamento) && pTipiPagamentoSet->m_Allineamento)
      {
        m_strBanca = m_pAziendeSet->m_Banca;
        m_strABI   = m_pAziendeSet->m_ABI;
        m_strCAB   = m_pAziendeSet->m_CAB;
      }
      break;
    }
  }
  if(i < m_ComboTipoPagamento.GetCount())
  {
    // Nel caso di fattura emessa, il codice potrebbe corrispondere ad un altro pagamento:
    // se è così aggiungo un altro item alla lista
    if(m_lCodiceFatturaEmessa > 0)
    {
      if(m_strTipoPagamento != pTipiPagamentoSet->m_Nome)
      {
      	i = m_ComboTipoPagamento.AddString(m_strTipoPagamento);
      	m_ComboTipoPagamento.SetItemData(i, 0);
      }
    }
    // Seleziono l'item
    m_ComboTipoPagamento.SetCurSel(i);
    m_ComboTipoPagamento.GetLBText(i, m_strTipoPagamento);
  }
}

void CStampaFattureDlg::OnSelchangeComboTipoPagamento() 
{
  int n;
  UpdateData();
	if((n = m_ComboTipoPagamento.GetCurSel()) != -1)
  {
    m_ComboTipoPagamento.GetLBText(n, m_strTipoPagamento);
    CTipiPagamentoSet* pTipiPagamento = new CTipiPagamentoSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
    pTipiPagamento->m_strFilter.Format("Codice = %d", m_ComboTipoPagamento.GetItemData(n));
    pTipiPagamento->Open();
    // Se è un pagamento di tipo bonifico o rimessa diretta metto le coordinate bancarie Sigma
    m_strBanca = pTipiPagamento->m_Banca;
    m_strABI   = pTipiPagamento->m_ABI;
    m_strCAB   = pTipiPagamento->m_CAB;
    // Se è un pagamento di tipo riba, metto le coordinate bancarie del cliente
    if(!pTipiPagamento->IsFieldNull(&pTipiPagamento->m_Allineamento) && pTipiPagamento->m_Allineamento)
    {
      m_strBanca = m_pAziendeSet->m_Banca;
      m_strABI   = m_pAziendeSet->m_ABI;
      m_strCAB   = m_pAziendeSet->m_CAB;      
    }
    pTipiPagamento->Close();
  }
  UpdateData(FALSE);
}


BOOL CStampaFattureDlg::CheckData(void)
{
  // Verifico la coerenza con la fattura precedente e la successiva
  // Se è la prima fattura, posso uscire senza verficare
  CTime date(m_DataFattura.GetYear(), 1, 1, 0, 0, 0);
  if(m_lMaxNumFattura <= 1 && m_DataFattura >= date)
    return TRUE;
  CFattureSet* pSet = new CFattureSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
  int numFatturaPrec = 0, numFatturaSucc = 0;
  // Numero fatture precedente e successiva
  numFatturaPrec = m_lMaxNumFattura - 1;
  numFatturaSucc = m_lMaxNumFattura + 1;
  // Prendo le fatture precedente e successiva
  pSet->m_strFilter.Format("Data > '%s' AND (Numero = %d OR Numero = %d)", date.Format("%Y-%m-%d"), numFatturaSucc, numFatturaPrec);
//
	if(m_bElett == TRUE)
		pSet->m_strFilter += " and fElett = 1";
	else
		pSet->m_strFilter += " and fElett = 0";
	pSet->m_strSort = "numero ASC";
	//
  pSet->Open();
  for(SET_START(pSet); !pSet->IsEOF(); pSet->MoveNext())
  {
    if((pSet->m_Numero < m_lMaxNumFattura && pSet->m_Data > m_DataFattura)
      || (pSet->m_Numero > m_lMaxNumFattura && pSet->m_Data < m_DataFattura))
    {
      pSet->Close();
      return FALSE;
    }
  }
  pSet->Close();
  return TRUE;
}

void CStampaFattureDlg::OnChangeEditSconto() 
{
  CString str;
  UpdateData(TRUE);
  // Calcolo l'importo scontato
  str = m_strImporto;
  str.Replace(".", "");
  str.Replace(",", ".");
  double imponibile = atof(str);
  double dImportoScontato = imponibile - (imponibile * atof(m_strSconto) / 100);
  m_dSconto = atof(m_strSconto);
  m_nImponibileScontato = (int)(dImportoScontato * 100 + 0.5);
  // Ricalcolo l'importo dell'iva
  double dIVA = (dImportoScontato * atof(m_strAliquota) / 100);
  m_nIVA = (int)(dIVA * 100 + 0.5);
  CalcolaTotale();
  UpdateData(FALSE);	
}

void CStampaFattureDlg::OnChangeEditTotale() 
{
  CString str;
  UpdateData();
  str = m_strTotale;
  str.Replace(".", "");
  str.Replace(",", ".");
  double totale = atof(str);
  str = m_strImponibile;
  str.Replace(".", "");
  str.Replace(",", ".");
  double imponibile = atof(str); 
  m_dSconto = 1 - (totale / ((1 + atof(m_strAliquota) / 100) * imponibile));
  m_dSconto *= 100;
  if(m_dSconto)
    m_strSconto.Format("%.2f", m_dSconto);
  else
    m_strSconto.Format("%.0f", m_dSconto);
  imponibile -= imponibile * m_dSconto / 100;
  m_nImponibileScontato = (int)(imponibile * 100 + 0.5);
  Valuta impScontato((double)m_nImponibileScontato);
  m_strImponibileScontato = m_strImportoScontato = impScontato.Format(-1, TRUE);
  double dIVA = (imponibile * atof(m_strAliquota) / 100);
  m_nIVA = (int)(dIVA * 100 + 0.5);
  Valuta iva((double)m_nIVA);
  m_strImportoIVA = m_strIVA = iva.Format(-1, TRUE);
  UpdateData(FALSE);
}

void CStampaFattureDlg::SetHeader(BOOL bon)
{
	m_bHeader = bon;
}

void CStampaFattureDlg::OnButtonFatturaXML() 
{
	CWinSigmaApp * pApp = (CWinSigmaApp *) AfxGetApp();

	CConfigurazione	config;

	// Lettura variabili
	CString csProg = config.Read("ProgressivoXML");
	int nProgressivo = atoi(csProg);
	CString csFolder = config.Read("XMLFolder");
	CString csPath("");
	CString csFilename("");

	// Compone il nome del file di esportazione e lo apre
	CString idPaese = config.Read("IdPaese");
	CString idCodiceTrasmittente = config.Read("IdCodiceTrasmittente");
	CString tipoFileXML = config.Read("TipologiaFileXML");
	CString extXML = config.Read("EstensioneXML");
	CString versione = config.Read("VersionePA");
	// if privato:
	// versione = config.Read("VersionePR");
	csFilename.Format("%s%s_%s_%d.%s", idPaese, idCodiceTrasmittente, tipoFileXML, nProgressivo, extXML);
	csPath.Format("%s\\%s", csFolder, csFilename);
	FILE* f = fopen((const char*)csPath.GetBuffer(csPath.GetLength()), "w");
  if (f == NULL)
  {
		MessageBox("Errore nell'apertura del file di esportazione. Esportazione fallita!", "Errore", MB_OK);
		return;
	}
	
	// Legge l'header XML
	CString csHdrTemplate = config.Read("XMLHeader");
	CString csLine("");
	csLine.Format(csHdrTemplate, versione);
	csLine += "\n";
	fwrite(csLine.GetBuffer(csLine.GetLength()), csLine.GetLength(),1,f);

	//////// FatturaElettronicaHeader: inizio
	csLine.Format("<FatturaElettronicaHeader>\n"); 
	fwrite(csLine.GetBuffer(csLine.GetLength()), csLine.GetLength(),1,f);

	// Sezione DatiTrasmissione - inizio
	csLine.Format("<DatiTrasmissione>\n"); 
	fwrite(csLine.GetBuffer(csLine.GetLength()), csLine.GetLength(),1,f);

	// IdTrasmittente - inizio
	csLine.Format("<IdTrasmittente>\n"); 
	fwrite(csLine.GetBuffer(csLine.GetLength()), csLine.GetLength(),1,f);

	csLine.Format("<IdPaese>%s</IdPaese>\n", idPaese); 
	fwrite(csLine.GetBuffer(csLine.GetLength()), csLine.GetLength(),1,f);

	csLine.Format("<IdCodice>%s</IdCodice>\n", idCodiceTrasmittente); 
	fwrite(csLine.GetBuffer(csLine.GetLength()), csLine.GetLength(),1,f);

	csLine.Format("</IdTrasmittente>\n"); 
	fwrite(csLine.GetBuffer(csLine.GetLength()), csLine.GetLength(),1,f);
	// IdTrasmittente - fine

	csLine.Format("<ProgressivoInvio>%d</ProgressivoInvio>\n", nProgressivo); 
	fwrite(csLine.GetBuffer(csLine.GetLength()), csLine.GetLength(),1,f);
	csLine.Format("<FormatoTrasmissione>%s</FormatoTrasmissione>\n", versione); 
	fwrite(csLine.GetBuffer(csLine.GetLength()), csLine.GetLength(),1,f);

	// Cedente/Prestatore - inizio
	csLine.Format("<CedentePrestatore>\n"); 
	fwrite(csLine.GetBuffer(csLine.GetLength()), csLine.GetLength(),1,f);

	csLine.Format("</CedentePrestatore>\n"); 
	fwrite(csLine.GetBuffer(csLine.GetLength()), csLine.GetLength(),1,f);
	// Cedente/Prestatore - fine

	// Cessionario/Committente - inizio
	csLine.Format("<CessionarioCommittente>\n"); 
	fwrite(csLine.GetBuffer(csLine.GetLength()), csLine.GetLength(),1,f);

	csLine.Format("</CessionarioCommittente>\n"); 
	fwrite(csLine.GetBuffer(csLine.GetLength()), csLine.GetLength(),1,f);
	// Cessionario/Committente - fine

	// chiudo sezione DatiTrasmissione
	csLine.Format("</DatiTrasmissione>\n"); 
	fwrite(csLine.GetBuffer(csLine.GetLength()), csLine.GetLength(),1,f);
	// Sezione DatiTrasmissione - fine
	// chiudo FatturaElettronicaHeader
	csLine.Format("</FatturaElettronicaHeader>\n"); 
	fwrite(csLine.GetBuffer(csLine.GetLength()), csLine.GetLength(),1,f);
	//////// FatturaElettronicaHeader: fine 

	//////// FatturaElettronicaBody: inizio 
	csLine.Format("<FatturaElettronicaBody>\n"); 
	fwrite(csLine.GetBuffer(csLine.GetLength()), csLine.GetLength(),1,f);

	// chiudo FatturaElettronicaBody
	csLine.Format("</FatturaElettronicaBody>\n"); 
	fwrite(csLine.GetBuffer(csLine.GetLength()), csLine.GetLength(),1,f);
	//////// FatturaElettronicaBody: fine 

	// Esportazione conclusa: chiudo il file
	fclose(f);

	CString msg = "";
	msg.Format("File %s generato in %s", csFilename, csFolder);
	MessageBox(msg, "Esportazione XML", MB_OK);

}