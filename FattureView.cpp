// FattureView.cpp : implementation file
//

#include "stdafx.h"
#include "WinSigma.h"
#include "WinSigmaDoc.h"
#include "XFormView.h"
#include "StampaEffetti.h"
#include "VerbaliServErogatiSet.h"
#include "VerbaliView.h"
#include "FattureView.h"
#include "MainFrm.h"
#include "Configurazione.h"
#include "InsertVerbaliInFatturaDlg.h"
#include "ServiziFatturaDlg.h"
#include "StampaFattureDlg.h"
#include "TrovaAziendaDlg.h"
#include "ArchiviaFattureDlg.h"
#include "EsportaFattureDlg.h"
#include "FattureSerEroVerSet.h"
#include "Printerpreter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFattureView

// Stati: serve per quando si fanno fatture senza verbale o note di credito
#define IDLE               0
#define FATT_SVERBALE      1
#define NOTA_DI_CREDITO    2

// Risposte della VerficaSelezione
#define VERIFICA_OK         1
#define VERIFICA_ERR_DATA  -1
#define VERIFICA_ERR_DOC   -2

#define CREATE_INVOICE_FIRST_MSG "Prima emettere la fattura"

IMPLEMENT_DYNCREATE(CFattureView, CFormView)

CFattureView::CFattureView()
	: CXFormView(CFattureView::IDD)
{
	//{{AFX_DATA_INIT(CFattureView)
	m_strBanca = _T("");
	m_strCodiceCliente = _T("");
	m_strImporto = _T("");
	m_strP_IVA = _T("");
	m_strRagioneSociale = _T("");
	m_strIndirizzo = _T("");
	m_strSconto = _T("");
	m_strABI = _T("");
	m_strCAB = _T("");
	m_strCodiceFiscale = _T("");
	m_strTipoPagamento = _T("");
	m_strAliquota = _T("");
	m_strImportoScontato = _T("");
	m_strIVA = _T("");
	m_strScontoFattura = _T("");
	m_strTotale = _T("");
	m_strSpeseSpedizione = _T("");
	m_strTipoDocumento = _T("");
	m_DataEmissione = 0;
	m_csRitAcconto = _T("");
	m_csTotRitAcconto = _T("");
	m_strCodiceDestinatario = _T("");
	m_strPEC = _T("");
	m_strCUP = _T("");
	m_strCIG = _T("");
	m_strOrdineAcquisto = _T("");
	m_DataOrdineAcquisto = 0;
	m_strContratto = _T("");
	m_DataContratto = 0;
	m_strNumeroDDT = _T("");
	m_DataDDT = 0;
	m_strCodiceXML = _T("");
	m_strIBAN = _T("");
	//}}AFX_DATA_INIT
  m_bEnableServiziCheck = FALSE;
  m_lListinoGenerale = m_lListinoParticolare = 0;
}

CFattureView::~CFattureView()
{
  if(m_pFattureEmesseSet)
  {
    m_pFattureEmesseSet->m_strFilter.Empty();
    m_pFattureEmesseSet->Requery();
  }
  if(m_pServiziErogati)
  {
    m_pServiziErogati->Close();
    delete m_pServiziErogati;
  }
  if(m_pVerbaliInFatturazione)
  {
    m_pVerbaliInFatturazione->Close();
    delete m_pVerbaliInFatturazione;
  }
}

void CFattureView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFattureView)
	DDX_Control(pDX, IDC_DATETIMEPICKER_DATA_EMISSIONE, m_DTCtrlDataEmissione);
	DDX_Control(pDX, IDC_EDIT_TIPO_DOC, m_EditTipoDoc);
	DDX_Control(pDX, IDC_EDIT_SCONTO, m_EditSconto);
	DDX_Control(pDX, IDC_EDIT_P_IVA, m_EditP_IVA);
	DDX_Control(pDX, IDC_EDIT_INDIRIZZO, m_EditIndirizzo);
	DDX_Control(pDX, IDC_EDIT_COD_FISCALE, m_EditCodFiscale);
	DDX_Control(pDX, IDC_EDIT_CAB, m_EditCAB);
	DDX_Control(pDX, IDC_EDIT_BANCA, m_EditBanca);
	DDX_Control(pDX, IDC_EDIT_ABI, m_EditABI);
	DDX_Control(pDX, IDC_COMBO_TIPO_PAGAMENTO, m_ComboTipoPagamento);
	DDX_Control(pDX, IDC_EDIT_RAGIONE_SOCIALE, m_EditRagioneSociale);
	DDX_Control(pDX, IDC_EDIT_COD_CLIENTE, m_EditCodiceCliente);
	DDX_Control(pDX, IDC_EDIT_CODICE_XML, m_EditCodiceXML);
	DDX_Control(pDX, IDC_LIST_VERBALI, m_ListVerbali);
	DDX_Control(pDX, IDC_LIST_SERVIZI, m_ListServizi);
	DDX_Control(pDX, IDC_BUTTON_MODIFY_SERVIZIO, m_BtnModifyServizio);
	DDX_Control(pDX, IDC_BUTTON_DEL_SERVIZIO, m_BtnDeleteServizio);
	DDX_Control(pDX, IDC_BUTTON_ADD_SERVIZIO, m_BtnAddServizio);
	DDX_Control(pDX, IDC_EDIT_CODDEST, m_EditCodiceDestinatario);
	DDX_Control(pDX, IDC_EDIT_PEC, m_EditPEC);
	DDX_Text(pDX, IDC_EDIT_BANCA, m_strBanca);
	DDV_MaxChars(pDX, m_strBanca, 64);
	DDX_Text(pDX, IDC_EDIT_COD_CLIENTE, m_strCodiceCliente);
	DDX_Text(pDX, IDC_EDIT_IMPORTO, m_strImporto);
	DDX_Text(pDX, IDC_EDIT_P_IVA, m_strP_IVA);
	DDX_Text(pDX, IDC_EDIT_RAGIONE_SOCIALE, m_strRagioneSociale);
	DDV_MaxChars(pDX, m_strRagioneSociale, 64);
	DDX_Text(pDX, IDC_EDIT_INDIRIZZO, m_strIndirizzo);
	DDX_Text(pDX, IDC_EDIT_SCONTO, m_strSconto);
	DDX_Text(pDX, IDC_EDIT_ABI, m_strABI);
	DDV_MaxChars(pDX, m_strABI, 8);
	DDX_Text(pDX, IDC_EDIT_CAB, m_strCAB);
	DDV_MaxChars(pDX, m_strCAB, 8);
	DDX_Text(pDX, IDC_EDIT_COD_FISCALE, m_strCodiceFiscale);
	DDV_MaxChars(pDX, m_strCodiceFiscale, 16);
	DDX_CBString(pDX, IDC_COMBO_TIPO_PAGAMENTO, m_strTipoPagamento);
	DDX_Text(pDX, IDC_EDIT_ALIQUOTA, m_strAliquota);
	DDX_Text(pDX, IDC_EDIT_IMPORTO_SCONTATO, m_strImportoScontato);
	DDX_Text(pDX, IDC_EDIT_IVA, m_strIVA);
	DDX_Text(pDX, IDC_EDIT_SCONTO_FATTURA, m_strScontoFattura);
	DDX_Text(pDX, IDC_EDIT_TOTALE, m_strTotale);
	DDX_Text(pDX, IDC_EDIT_SPESE_SPED, m_strSpeseSpedizione);
	DDX_Text(pDX, IDC_EDIT_TIPO_DOC, m_strTipoDocumento);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATA_EMISSIONE, m_DataEmissione);
	DDX_Text(pDX, IDC_EDIT_RIT_ACCONTO, m_csRitAcconto);
	DDX_Text(pDX, IDC_EDIT_TOT_RIT_ACCONTO, m_csTotRitAcconto);
	DDX_Text(pDX, IDC_EDIT_CODDEST, m_strCodiceDestinatario);
	DDV_MaxChars(pDX, m_strCodiceDestinatario, 7);
	DDX_Text(pDX, IDC_EDIT_PEC, m_strPEC);
	DDV_MaxChars(pDX, m_strPEC, 200);
	DDX_Text(pDX, IDC_EDIT_CODICE_XML, m_strCodiceXML);
	DDX_Control(pDX, IDC_EDIT_IBAN, m_EditIBAN);
	DDX_Text(pDX, IDC_EDIT_IBAN, m_strIBAN);
	DDV_MaxChars(pDX, m_strIBAN, 27);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFattureView, CXFormView)
	//{{AFX_MSG_MAP(CFattureView)
	ON_COMMAND(ID_FATTURA_EMETTI, OnFatturaEmetti)
	ON_COMMAND(ID_FATTURA_ELETT_EMETTI, OnFatturaElettEmetti)
	ON_COMMAND(ID_ESPORTA_FATTURE, OnEsportaFatture)
  ON_COMMAND(ID_FATTURA_ESPORTAFATTURE, OnEsportaFatture)
	ON_BN_CLICKED(IDC_BUTTON_ADD_SERVIZIO, OnButtonAddServizio)
	ON_BN_CLICKED(IDC_BUTTON_DEL_SERVIZIO, OnButtonDelServizio)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_SERVIZIO, OnButtonModifyServizio)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST_VERBALI, OnItemchangingListVerbali)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SERVIZI, OnDblclkListServizi)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_VERBALI, OnItemchangedListVerbali)
	ON_COMMAND(ID_VISUALIZZA_FATTURA, OnVisualizzaFattura)
	ON_COMMAND(ID_TROVA, OnTrovaAzienda)
	ON_COMMAND(ID_NUOVA_SENZAVERBALE, OnNuovaSenzaVerbale)
	ON_EN_KILLFOCUS(IDC_EDIT_COD_CLIENTE, OnKillfocusEditCodCliente)
	ON_EN_KILLFOCUS(IDC_EDIT_RAGIONE_SOCIALE, OnKillfocusEditRagioneSociale)
	ON_EN_KILLFOCUS(IDC_EDIT_P_IVA, OnKillfocusEditPIva)
  ON_COMMAND(ID_PRINTPROFORMA, OnPrintProforma)
	ON_COMMAND(ID_STAMPAEFFETTI, OnStampaeffetti)
	ON_COMMAND(ID_BUTTON_AGGIORNA, OnButtonAggiorna)
	ON_COMMAND(ID_NOTACREDITO_NUOVA, OnNotacreditoNuova)
	ON_COMMAND(ID_SBLOCCAFATTURA, OnSbloccaFattura)
	ON_COMMAND(ID_SBLOCCAFATTURAZIONE, OnSbloccaFatturazione)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_VERBALI, OnDblclkListVerbali)
	ON_COMMAND(ID_DEL_INFATTURAZIONE, OnDelInfatturazione)
	ON_COMMAND(ID_INSERTVERBALE, OnInsertVerbale)
	ON_COMMAND(ID_FATTURA_ARCHIVIA_SINGOLAFATTURA, OnFatturaArchiviaSingolafattura)
	ON_COMMAND(ID_FATTURA_ARCHIVIA_GRUPPOFATTURE, OnFatturaArchiviaGruppofatture)
	ON_COMMAND(ID_FATTURA_XML, OnFatturaXML)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_DATA_EMISSIONE, OnDatetimechangeDatetimepickerDataEmissione)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFattureView diagnostics

#ifdef _DEBUG
void CFattureView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFattureView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFattureView message handlers


void CFattureView::LoadCurRecord(BOOL bData)
{
  int n, m;
  CString str, strTipo, strTipoDoc;
  CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  int nCodiceVerbale = -1, nCodiceServizio = -1;
	strTipoDoc = "";
  long lDefPagamento = pApp->GetProfileInt(CONFIGURAZIONE, TIPO_PAGAMENTO_DEFAULT, 9);
  if(!bData)
  {
    m_strRagioneSociale.Empty();
    m_strCodiceCliente.Empty();
    m_strIndirizzo.Empty();
    m_strCodiceFiscale.Empty();
    m_strSconto.Empty();
    m_strP_IVA.Empty();
    m_strBanca.Empty();
    m_strTipoPagamento.Empty();
    m_strImporto.Empty();
    m_strPEC.Empty();
    m_strCodiceDestinatario.Empty();
		m_strCIG.Empty();
		m_strCUP.Empty();
		m_strOrdineAcquisto.Empty();
		m_DataOrdineAcquisto = 0;
		m_strContratto.Empty();
		m_DataContratto = 0;
		m_strNumeroDDT.Empty();
		m_DataDDT = 0;
    m_strCodiceXML.Empty();
    m_ListVerbali.DeleteAllItems();
    m_ListServizi.DeleteAllItems();
    m_DataEmissione = CTime::GetCurrentTime();
    m_csRitAcconto.Empty();
    m_csTotRitAcconto.Empty();
    EnableServicesBtns(FALSE);
    EnableControls(FALSE);
    return;
  }
  if((m_pVerbaliInFatturazione->IsBOF() || m_pVerbaliInFatturazione->IsEOF()) && (m_pFattureEmesseSet->IsBOF() || m_pFattureEmesseSet->IsEOF()))
    return;
  if(!m_ComboTipoPagamento.GetCount())
    return;
  // Disabilito il controllo itemchanging-itemchanged sulla lista dei verbali
  m_bEnableServiziCheck = FALSE;
  // Codice azienda selezionata
  CFattureTreeCtrl* pTreeCtrl = &((CMainFrame*)GetParentFrame())->m_wndTreeFatture;
  CXRecsetTree* pXTree;
  m_lCodiceAzienda = 0;
  m_lCodiceFattura = 0;
  m_lListinoParticolare = m_lListinoGenerale = 0;
  if(pDoc->m_nSelectedTreeFatture == TREEITEM_FATTUREDAEMETTERE)
  {
    pXTree = (CXRecsetTree*)pTreeCtrl->GetItemData(pTreeCtrl->m_hTreeFattureDaEmettere);
    m_lCodiceAzienda = pXTree->GetCode();
  }
  else
  {
    if((m_lCodiceFattura = pTreeCtrl->GetItemData(pTreeCtrl->GetSelectedItem())) > 0)
    {
      for(SET_START(m_pFattureEmesseSet); !m_pFattureEmesseSet->IsEOF(); m_pFattureEmesseSet->MoveNext())
      {
        if(m_pFattureEmesseSet->m_Codice == m_lCodiceFattura)
        {
          m_lCodiceAzienda = m_pFattureEmesseSet->m_Intestatario;
          break;
        }
      }
      if(m_pFattureEmesseSet->IsEOF())
        return;
    }
  }
  if(bData && m_lCodiceAzienda > 0)
  {
    if(m_lCodiceFattura > 0)
      m_pVerbaliInFatturazione->m_strFilter.Format("Fattura = %d", m_lCodiceFattura);
    else
      m_pVerbaliInFatturazione->m_strFilter.Format("Fattura = %d AND IntestatarioFattura = %d", m_lCodiceFattura, m_lCodiceAzienda);
    m_pVerbaliInFatturazione->Requery();
    if((m_pVerbaliInFatturazione->IsBOF() || m_pVerbaliInFatturazione->IsEOF()) && !m_lCodiceFattura)
      return;
    for(SET_START(m_pVerbaliInFatturazione); !m_pVerbaliInFatturazione->IsEOF(); m_pVerbaliInFatturazione->MoveNext())
    {
      if(!m_pVerbaliInFatturazione->IsFieldNull(&m_pVerbaliInFatturazione->m_ListinoParticolare))
        m_lListinoParticolare = m_pVerbaliInFatturazione->m_ListinoParticolare;
      if(!m_pVerbaliInFatturazione->IsFieldNull(&m_pVerbaliInFatturazione->m_ListinoGenerale))
        m_lListinoGenerale = m_pVerbaliInFatturazione->m_ListinoGenerale;
    }
    SET_START(m_pVerbaliInFatturazione);
    CAziendeSet* pAziendeSet = new CAziendeSet(&pApp->m_db);//pDoc->m_pAziendeSet;
    pAziendeSet->m_strFilter.Format("Codice = %d", m_lCodiceAzienda);
    pAziendeSet->Open();
//    SINCRONIZE(pAziendeSet, m_lCodiceAzienda);
    // Dati cliente e pagamento
    if(!m_lCodiceFattura)
    {
      m_DTCtrlDataEmissione.EnableWindow(TRUE);
      // Fattura da emettere: prendo i dati dal recordset dell'azienda
      m_strCodiceCliente = pAziendeSet->m_ID;
      m_strRagioneSociale = pAziendeSet->m_RagioneSociale;
      if(!pAziendeSet->m_Indirizzo.IsEmpty())
      {
        m_strIndirizzo.Format("%s, %s %s", pAziendeSet->m_Indirizzo, pAziendeSet->m_CAP, pAziendeSet->m_Citta);
        if(!pAziendeSet->m_Provincia.IsEmpty())
        {
          str.Format(" (%s)", pAziendeSet->m_Provincia);
          m_strIndirizzo += str;
        }
      }
      m_strP_IVA = pAziendeSet->m_P_IVA;
      m_strCodiceFiscale = pAziendeSet->m_CodiceFiscale;
      m_strCodiceDestinatario = pAziendeSet->m_CodiceDestinatario;
      m_strPEC = pAziendeSet->m_PEC;
      m_strBanca = pAziendeSet->m_Banca;
      m_strABI = pAziendeSet->m_ABI;
      m_strCAB = pAziendeSet->m_CAB;
      m_strIBAN = pAziendeSet->m_IBAN;
      // Tipo di pagamento
      if(!pAziendeSet->IsFieldNull(&pAziendeSet->m_TipoPagamento) &&
          pAziendeSet->m_TipoPagamento > 0)
        m_lTipoPagamento = pAziendeSet->m_TipoPagamento;
      else
        m_lTipoPagamento = lDefPagamento;
      if(!pAziendeSet->IsFieldNull(&pAziendeSet->m_Sconto))
        m_dSconto = pAziendeSet->m_Sconto;
      else
        m_dSconto = 0.;
      m_strAliquota = STR_DEFAULT_ALIQUOTA_IVA;
      m_DataEmissione = CTime::GetCurrentTime();
    }
    else
    {
      m_DTCtrlDataEmissione.EnableWindow(FALSE);
      // Fattura emessa: prendo i dati dal recordset della fattura
      SINCRONIZE(m_pFattureEmesseSet, m_lCodiceFattura);
      m_strCodiceCliente = m_pFattureEmesseSet->m_IDIntestatario;
      m_strRagioneSociale = m_pFattureEmesseSet->m_RagioneSociale;
      if(!m_pFattureEmesseSet->m_Indirizzo.IsEmpty())
      {
        m_strIndirizzo.Format("%s, %s %s", m_pFattureEmesseSet->m_Indirizzo, m_pFattureEmesseSet->m_CAP, m_pFattureEmesseSet->m_Citta);
        if(!m_pFattureEmesseSet->m_Provincia.IsEmpty())
        {
          str.Format(" (%s)", m_pFattureEmesseSet->m_Provincia);
          m_strIndirizzo += str;
        }
      }
      m_strP_IVA = m_pFattureEmesseSet->m_P_IVA;
      m_strCodiceFiscale = m_pFattureEmesseSet->m_CodiceFiscale;
      m_strCodiceDestinatario = m_pFattureEmesseSet->m_CodiceDestinatario;
      m_strPEC = m_pFattureEmesseSet->m_PEC;
      if(!m_pFattureEmesseSet->IsFieldNull(&m_pFattureEmesseSet->m_CUP))
				m_strCUP = m_pFattureEmesseSet->m_CUP;
      if(!m_pFattureEmesseSet->IsFieldNull(&m_pFattureEmesseSet->m_CIG))
				m_strCIG = m_pFattureEmesseSet->m_CIG;
      if(!m_pFattureEmesseSet->IsFieldNull(&m_pFattureEmesseSet->m_OrdineAcquisto))
			{
				m_strOrdineAcquisto = m_pFattureEmesseSet->m_OrdineAcquisto;
	      if(!m_pFattureEmesseSet->IsFieldNull(&m_pFattureEmesseSet->m_DataOrdineAcquisto))
				{
					m_DataOrdineAcquisto = m_pFattureEmesseSet->m_DataOrdineAcquisto;
				}
			}
      if(!m_pFattureEmesseSet->IsFieldNull(&m_pFattureEmesseSet->m_Contratto))
			{
				m_strContratto = m_pFattureEmesseSet->m_Contratto;
	      if(!m_pFattureEmesseSet->IsFieldNull(&m_pFattureEmesseSet->m_DataContratto))
				{
					m_DataContratto = m_pFattureEmesseSet->m_DataContratto;
				}
			}
      if(!m_pFattureEmesseSet->IsFieldNull(&m_pFattureEmesseSet->m_NumeroDDT))
			{
				m_strNumeroDDT = m_pFattureEmesseSet->m_NumeroDDT;
	      if(!m_pFattureEmesseSet->IsFieldNull(&m_pFattureEmesseSet->m_DataDDT))
				{
					m_DataDDT = m_pFattureEmesseSet->m_DataDDT;
				}
			}
      if(!m_pFattureEmesseSet->IsFieldNull(&m_pFattureEmesseSet->m_CodiceXML))
			{
				m_strCodiceXML.Format("%05d", m_pFattureEmesseSet->m_CodiceXML);
			}

      if(m_pFattureEmesseSet->m_BancaAppoggio.IsEmpty())
      {
        m_strBanca = m_pFattureEmesseSet->m_Banca;
        m_strIBAN = m_pFattureEmesseSet->m_IBAN;
        m_strABI = m_pFattureEmesseSet->m_ABI;
        m_strCAB = m_pFattureEmesseSet->m_CAB;
      }
      else
      {
        m_strBanca = m_pFattureEmesseSet->m_BancaAppoggio;
        m_strIBAN = m_pFattureEmesseSet->m_IBANAppoggio;
        m_strABI = m_pFattureEmesseSet->m_ABIAppoggio;
        m_strCAB = m_pFattureEmesseSet->m_CABAppoggio;
      }
      // Tipo di pagamento
      if(!m_pFattureEmesseSet->IsFieldNull(&m_pFattureEmesseSet->m_TipoPagamento) &&
          m_pFattureEmesseSet->m_TipoPagamento > 0)
        m_lTipoPagamento = m_pFattureEmesseSet->m_TipoPagamento;
      else
        m_lTipoPagamento = lDefPagamento;
      if(!m_pFattureEmesseSet->IsFieldNull(&m_pFattureEmesseSet->m_Sconto))
        m_dSconto = m_pFattureEmesseSet->m_Sconto;
      else
        m_dSconto = 0.;
      m_strAliquota.Format("%.0f", m_pFattureEmesseSet->m_Aliquota);
      Valuta sped(m_pFattureEmesseSet->m_Spese);
      m_strSpeseSpedizione = sped.Format();
      m_DataEmissione = m_pFattureEmesseSet->m_Data;
      if(m_pFattureEmesseSet->m_TipoDocumento == FATTURA)
	      m_strTipoDocumento = "Fattura";
	      if(m_pFattureEmesseSet->m_Elett == 1)
					strTipoDoc = " elettronica";
      else
        m_strTipoDocumento = "Nota di credito";
    }
    for(n = 0; n < m_ComboTipoPagamento.GetCount(); n++)
    {
      if(m_lTipoPagamento == (long)m_ComboTipoPagamento.GetItemData(n))
      {
        m_ComboTipoPagamento.GetLBText(n, m_strTipoPagamento);
        break;
      }
    }
    if(n < m_ComboTipoPagamento.GetCount())
      m_ComboTipoPagamento.SetCurSel(n);
    else
    {
      m_ComboTipoPagamento.SetCurSel(0);
      m_ComboTipoPagamento.GetLBText(0, m_strTipoPagamento);
    }
    if(m_dSconto)
      m_strSconto.Format("%.2f", m_dSconto);
    else
      m_strSconto.Format("%.0f", m_dSconto);
    m_strScontoFattura = m_strSconto;
    
    m_ListVerbali.DeleteAllItems();
    m_ListServizi.DeleteAllItems();
    n = m = 0;
    for(SET_START(m_pVerbaliInFatturazione); !m_pVerbaliInFatturazione->IsEOF(); m_pVerbaliInFatturazione->MoveNext())
    {
      if(nCodiceVerbale != m_pVerbaliInFatturazione->m_Codice)
      {
        nCodiceVerbale = m_pVerbaliInFatturazione->m_Codice;
        n = m_ListVerbali.GetItemCount();
#ifdef WINSIGMA2
        str.Format("A%d", m_pVerbaliInFatturazione->m_ProgressivoTotale);
#else
        str.Format("%d/%d", m_pVerbaliInFatturazione->m_ProgressivoParziale, m_pVerbaliInFatturazione->m_ProgressivoTotale);
#endif
        switch(m_pVerbaliInFatturazione->m_TipoVerbale)
        {
        case VERB_NON_IN_CONCESSIONE:
				case VERB_NC_PROVE_DI_CARICO:
				case VERB_NC_CONGL_BITUMINOSI:
				case VERB_NC_INERTI:
				case VERB_NC_MONITORAGGI:
				case VERB_NC_VARIE:
				case VERB_NC_GEOTECNICA: 
          strTipo = "Prove non in concessione";
          break;
        case VERB_IN_CONCESSIONE:
          strTipo = "Prove in concessione";
          break;
        case VERB_GEOLOGIA:
          strTipo = "Prove geotecniche";
          break;
        case VERB_VECCHIO_PROG:
          strTipo.Format("Precedente al 1/1/%s", (CTime::GetCurrentTime()).Format("%Y"));
          break;
        case VERB_PER_FATTURA:
          str.Empty();
          strTipo = "Fattura senza verbale";
          break;
        case VERB_PER_NOTACREDITO:
          str.Empty();
          strTipo = "Nota di credito";
          break;
        }
        n = m_ListVerbali.InsertItem(n, str);
        m_ListVerbali.SetItemData(n, (DWORD)m_pVerbaliInFatturazione->m_Codice);
        m_ListVerbali.SetItemText(n, 1, strTipo);
        if(m_pVerbaliInFatturazione->m_TipoVerbale != VERB_PER_FATTURA && m_pVerbaliInFatturazione->m_TipoVerbale != VERB_PER_NOTACREDITO)
        {
          m_ListVerbali.SetItemText(n, 2, m_pVerbaliInFatturazione->m_DataAccettazione.Format("%d/%m/%Y"));
          if(m_pVerbaliInFatturazione->IsFieldNull(&m_pVerbaliInFatturazione->m_DataChiusura))
            m_ListVerbali.SetItemText(n, 3, "Aperto");
          else
            m_ListVerbali.SetItemText(n, 3, "Chiuso");
        }
        else
        {
          m_ListVerbali.SetItemText(n, 2, "");
          m_ListVerbali.SetItemText(n, 3, "");
        }
        if(m_pVerbaliInFatturazione->m_InFatturazione == 1)
        {
          if(m_pVerbaliInFatturazione->m_TipoVerbale == VERB_PER_NOTACREDITO)
					{
            m_strTipoDocumento = "Nota di credito";
					}
          else
					{
            m_strTipoDocumento = "Fattura";
						m_strTipoDocumento += strTipoDoc;
					}
          m_ListVerbali.SetCheck(n);
        }
      }
    }
    pAziendeSet->Close();
    delete pAziendeSet;
    LoadServizi();
    // Abilito il controllo itemchanging-itemchanged sulla lista dei verbali
    m_bEnableServiziCheck = TRUE;
    EnableServicesBtns(TRUE);
  }
}

BOOL CFattureView::ValidateData(void)
{
  return FALSE;
}

BOOL CFattureView::IsDataChanged(void)
{
  return FALSE;
}

void CFattureView::OnInitialUpdate() 
{
  DWORD style;
  CString str;
  int n;

  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  int nFontWidth = pApp->GetFontWidth();
  m_bServiziChecked = FALSE;
  // Prendo i verbali messi in fatturazione
  m_pVerbaliInFatturazione = new CVerbaliSet(&pApp->m_db);
  // Cancello gli eventuali verbali cerati per emettere una fattura senza verbale
  // che non contengono i dati dell'azienda
  m_pVerbaliInFatturazione->m_strFilter.Format("(TipoVerbale = %d OR TipoVerbale = %d) AND IntestatarioFattura = 0", VERB_PER_FATTURA, VERB_PER_NOTACREDITO);
  m_pVerbaliInFatturazione->Open();
  for(SET_START(m_pVerbaliInFatturazione); !m_pVerbaliInFatturazione->IsEOF(); m_pVerbaliInFatturazione->MoveNext())
    m_pVerbaliInFatturazione->Delete();
  m_pVerbaliInFatturazione->m_strFilter = "Fattura = 0";
  m_pVerbaliInFatturazione->m_strSort = "Codice ASC";
  m_pVerbaliInFatturazione->Requery();
  // Servizi erogati
  m_pServiziErogati = new CServiziErogatiSet(&pApp->m_db);
  m_pServiziErogati->m_strFilter = "Codice = 0";
  m_pServiziErogati->Open();
  // Prendo le fatture non archiviate
  m_pFattureEmesseSet = pDoc->m_pFattureEmesseSet;
  m_pFattureEmesseSet->m_strFilter = "Archiviata = 0";
  m_pFattureEmesseSet->Requery();
  if(pDoc->m_nSelectedTreeFatture == TREEITEM_FATTUREDAEMETTERE)
    CXFormView::m_pSet = m_pVerbaliInFatturazione;
  else
    CXFormView::m_pSet = m_pFattureEmesseSet;
	CXFormView::OnInitialUpdate();

  // Lista dei servizi
  style = m_ListServizi.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT;
	m_ListServizi.SetExtendedStyle(style);
  m_ListServizi.InsertColumn(0, "", LVCFMT_LEFT,0);
  m_ListServizi.InsertColumn(1, "Verbale", LVCFMT_CENTER, 15 * nFontWidth, -1);
  m_ListServizi.InsertColumn(2, "Cod.", LVCFMT_LEFT, 8 * nFontWidth, -1);
  m_ListServizi.InsertColumn(3, "Descrizione", LVCFMT_LEFT, 55 * nFontWidth, -1);
  m_ListServizi.InsertColumn(4, "N.", LVCFMT_CENTER, 8 * nFontWidth, -1);
  m_ListServizi.InsertColumn(5, "Prezzo", LVCFMT_RIGHT, 10 * nFontWidth, -1);
  m_ListServizi.InsertColumn(6, "Sc. %", LVCFMT_CENTER, 9 * nFontWidth, -1);
  m_ListServizi.InsertColumn(7, "Importo", LVCFMT_RIGHT, 12 * nFontWidth, -1);
  // Lista dei verbali
  style = m_ListVerbali.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES;
  m_ListVerbali.SetExtendedStyle(style);
  m_ListVerbali.InsertColumn(0, "Numero", LVCFMT_LEFT, 16 * nFontWidth, -1);
  m_ListVerbali.InsertColumn(1, "Tipo", LVCFMT_LEFT, 31 * nFontWidth, -1);
  m_ListVerbali.InsertColumn(2, "Accettazione", LVCFMT_CENTER, 15 * nFontWidth, -1);
  m_ListVerbali.InsertColumn(3, "Stato", LVCFMT_LEFT, 14 * nFontWidth, -1);
  m_DataEmissione = CTime::GetCurrentTime();
  // Tipi di pagamento
  CTipiPagamentoSet* pTipiPagamento = pDoc->m_pTipiPagamentoSet;
  for(SET_START(pTipiPagamento); !pTipiPagamento->IsEOF(); pTipiPagamento->MoveNext())
  {
  	n = m_ComboTipoPagamento.AddString(pTipiPagamento->m_Nome);
  	m_ComboTipoPagamento.SetItemData(n, pTipiPagamento->m_Codice);
  }
  m_ComboTipoPagamento.SetCurSel(-1);
  m_nState = IDLE;
  CFont m_FontLarge;
	m_FontLarge.CreateFont(16, 10, 0, 0, FW_NORMAL,
                         0, 0, 0, DEFAULT_CHARSET,
                         OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                         DEFAULT_QUALITY, DEFAULT_PITCH,
                         "Arial");
  m_EditTipoDoc.SetFont(&m_FontLarge);

	/**************************************************************/
	/************ Modifica provvisoria (Andrea) *******************/
	/**************************************************************/
	if(!m_pFattureEmesseSet->IsEOF())
		m_pFattureEmesseSet->MoveLast();
	/**************************************************************/
	/**************************************************************/
	
  m_lLastFattura = m_pFattureEmesseSet->m_Codice;
  SET_START(m_pFattureEmesseSet);
  OnUpdate(NULL, 0, NULL);
}

void CFattureView::OnEsportaFatture() 
{
	CWinSigmaApp * pApp = (CWinSigmaApp *) AfxGetApp();

	CFattureSet					*	pFattureSet;
	CAziendeSet					*	pAziendeSet;
	CTipiPagamentoSet		*	pTipiPag;
	CFattureSerEroVerSet* pFattSerEroVer;

	CString sql		("");
	CString csApp	("");

	//Totali
	double ImpConcessione			= 0;
	double ImpNonConcessione	= 0;
	double ImpGeotecnica	   	= 0;
	double ImpAltro				   	= 0;
	double Imponibile					= 0;
	double IVA						   	= 0;
	double Spese							= 0;
	double RitenutaAcc				= 0;

	//Richiama il dialogo per l'esportazione
	CEsportaFattureDlg esporta;
	if (esporta.DoModal() == IDOK)
	{
		//Apertura dei recordset

		//Recordset Fatture
		pFattureSet = new CFattureSet(&pApp->m_db);
		pFattureSet->m_strFilter = "Codice = 0";
		if (!pFattureSet->Open())
		{
			MessageBox("Errore nel reperimento dei dati da esportare. Esportazione fallita!", "Errore", MB_OK);
			pFattureSet->Close();
			delete pFattureSet;
			return;
		}

		//Recordset Aziende
		pAziendeSet = new CAziendeSet(&pApp->m_db);
		pAziendeSet->m_strFilter = "Codice = 0";
		if (!pAziendeSet->Open())
		{
			MessageBox("Errore nel reperimento dei dati da esportare. Esportazione fallita!", "Errore", MB_OK);
			pAziendeSet->Close();
			delete pAziendeSet;	
			return;
		}

		//Recordset Fatture-ServiziErogati-Verbali
		pFattSerEroVer = new CFattureSerEroVerSet(&pApp->m_db);
		pFattSerEroVer->m_strFilter = "[FATTURE].Codice = 0";
		if (!pFattSerEroVer->Open())
		{
			MessageBox("Errore nel reperimento dei dati da esportare. Esportazione fallita!", "Errore", MB_OK);
			pFattSerEroVer->Close();
			delete pFattSerEroVer;
			return;
		}

		//Recordset TipiPagamento
		pTipiPag = new CTipiPagamentoSet(&pApp->m_db);
		pTipiPag->m_strFilter = "Codice = 0";
		if (!pTipiPag->Open())
		{
			MessageBox("Errore nel reperimento dei dati da esportare. Esportazione fallita!", "Errore", MB_OK);
			pTipiPag->Close();
			delete pTipiPag;
			return;
		}

		pFattureSet->m_strFilter.Format("(Data > '%s-01-01') AND ((fElett = 0 AND Numero >= %d AND Numero <= %d) OR (fElett = 1 AND Numero >= %d AND Numero <= %d))", esporta.m_csAnno,esporta.m_intDaFattura, esporta.m_intAFattura, esporta.m_intDaElett, esporta.m_intAElett);
		pFattureSet->m_strSort = "fElett, Numero";
		pFattureSet->Requery();

		CString str("");
		int nDa = esporta.m_intDaFattura;
		int nA = esporta.m_intAFattura;
		int nDaElett = esporta.m_intDaElett;
		int nAElett = esporta.m_intAElett;
		if(nDaElett == 0 && nAElett == 0)
		{
			// solo cartacee
			str.Format("%s\\fatture_%d_%d_%s.txt", esporta.m_csPath ,esporta.m_intDaFattura, esporta.m_intAFattura, esporta.m_csAnno);
		}
		else if(nDa == 0 && nA == 0)
		{
			// solo elettroniche
			str.Format("%s\\fatture_E%d_E%d_%s.txt", esporta.m_csPath ,esporta.m_intDaElett, esporta.m_intAElett, esporta.m_csAnno);
		}
		else
		{
			// cartacee + elettroniche
			str.Format("%s\\fatture_%d_%d_E%d_E%d_%s.txt", esporta.m_csPath, esporta.m_intDaFattura, esporta.m_intAFattura ,esporta.m_intDaElett, esporta.m_intAElett, esporta.m_csAnno);
		}


		FILE* f = fopen((const char*)str.GetBuffer(str.GetLength()), "w");
    if (f == NULL)
		{
			MessageBox("Errore nell'apertura del file di esportazione. Esportazione fallita!", "Errore", MB_OK);
			pAziendeSet->Close();
			delete pAziendeSet;
			pFattureSet->Close();
			delete pFattureSet;
			pFattSerEroVer->Close();
			delete pFattSerEroVer;
			pTipiPag->Close();
			delete pTipiPag;
			return;
		}

		while(!pFattureSet->IsEOF())
		{
			ImpConcessione		= 0;
		  ImpNonConcessione	= 0;
		  ImpGeotecnica	   	= 0;
		  ImpAltro				  = 0;
		  IVA						   	= 0;
		  RitenutaAcc				= 0;

			//Codice Cliente
			//csApp.Format("Codice Cliente = %s;\n", pFattureSet->m_IDIntestatario);
			csApp.Format("%s;", pFattureSet->m_IDIntestatario);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Partita IVA
			//csApp.Format("Partita Iva = %s;\n", pFattureSet->m_P_IVA);
			csApp.Format("%s;", pFattureSet->m_P_IVA);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Codice Fiscale
			//csApp.Format("Codice Fiscale = %s;\n", pFattureSet->m_CodiceFiscale);
			csApp.Format("%s;", pFattureSet->m_CodiceFiscale);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Ragione Sociale
			//csApp.Format("Ragione Sociale = %s;\n", pFattureSet->m_RagioneSociale);
			csApp.Format("%s;", pFattureSet->m_RagioneSociale);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Privato = 1 - Azienda = 0
			pAziendeSet->m_strFilter.Format("Codice = %d", pFattureSet->m_Intestatario);
			pAziendeSet->Requery();
			//csApp.Format("Privato = %d;\n" ,pAziendeSet->m_Privato);
			csApp.Format("%d;" ,pAziendeSet->m_Privato);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Indirizzo
			//csApp.Format("Indirizzo = %s;\n", pFattureSet->m_Indirizzo);
			csApp.Format("%s;", pFattureSet->m_Indirizzo);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//CAP
			//csApp.Format("CAP = %s;\n", pFattureSet->m_CAP);
			csApp.Format("%s;", pFattureSet->m_CAP);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Città
			//csApp.Format("Città = %s;\n", pFattureSet->m_Citta);
			csApp.Format("%s;", pFattureSet->m_Citta);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Provincia
			//csApp.Format("Provincia = %s;\n", pFattureSet->m_Provincia);
			csApp.Format("%s;", pFattureSet->m_Provincia);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//EMail
			//csApp.Format("EMail = %s;\n", pAziendeSet->m_E_Mail);
			csApp.Format("%s;", pAziendeSet->m_E_Mail);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Banca
			//csApp.Format("Banca = %s;\n", pFattureSet->m_Banca);
			pFattureSet->m_Banca.Remove(0x0D);
			pFattureSet->m_Banca.Remove(0x0A);
			csApp.Format("%s;", pFattureSet->m_Banca);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//ABI
			//csApp.Format("ABI = %s;\n", pFattureSet->m_ABI);
			csApp.Format("%s;", pFattureSet->m_ABI);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//CAB
			//csApp.Format("CAB = %s;\n", pFattureSet->m_CAB);
			csApp.Format("%s;", pFattureSet->m_CAB);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Tipo di pagamento
			pTipiPag->m_strFilter.Format("Codice = %d", pFattureSet->m_TipoPagamento);
			if (!pTipiPag->Requery())
			{
				MessageBox("Errore nell'apertura del file di esportazione. Esportazione fallita!", "Errore", MB_OK);
				pAziendeSet->Close();
				delete pAziendeSet;
				pFattureSet->Close();
				delete pFattureSet;
				pFattSerEroVer->Close();
				delete pFattSerEroVer;
				pTipiPag->Close();
				delete pTipiPag;
				return;
			}
			if (!pTipiPag->IsEOF() && (!pTipiPag->IsFieldNull(&pTipiPag->m_VecchioCod)))
			{
				//csApp.Format("Codice Pagamento = %d;\n", pTipiPag->m_VecchioCod);
				csApp.Format("%0.2d;", pTipiPag->m_VecchioCod);
			}
			else
				csApp = ";";
				//csApp = "Codice Pagamento = ;\n";
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);





			///DA VERIFICARE CON SABRINA E MARCO
			//csApp.Format("CIN = ;\n");
			csApp.Format(";");
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);
			///Da verificare con la Sabrina e Marco
			//csApp.Format("Conto Corrente = %s;\n", pFattureSet->m_ContoAppoggio);
			csApp.Format("%s;", pFattureSet->m_ContoAppoggio);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);
			///DA VERIFICARE CON SABRINA E MARCO




			
			//Tipo documento (0 = Fattura ; 1 = nota di credito)
			//csApp.Format("Tipo Documento = %d;\n", pFattureSet->m_TipoDocumento);
			csApp.Format("%d;", pFattureSet->m_TipoDocumento);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Numero fattura
			//csApp.Format("Numero Fattura = %d;\n", pFattureSet->m_Numero);
			csApp.Format("%d;", pFattureSet->m_Numero);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Data
			//csApp.Format("Data = %s;\n", pFattureSet->m_Data.Format("%m/%d/%Y"));
			csApp.Format("%s;", pFattureSet->m_Data.Format("%d/%m/%Y"));
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Data di scadenza
			if (!pFattureSet->IsFieldNull(&pFattureSet->m_Scadenza))
				csApp.Format("%s;", pFattureSet->m_Scadenza.Format("%d/%m/%Y"));
				//csApp.Format("Scadenza = %s;\n", pFattureSet->m_Scadenza.Format("%m/%d/%Y"));
			else
				csApp.Format(";");
				//csApp.Format("Scadenza = ;\n");
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Aliquota IVA
			//csApp.Format("Aliquota IVA = %.2f;\n", pFattureSet->m_Aliquota);
			csApp.Format("%.2f;", pFattureSet->m_Aliquota);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Spese
			//csApp.Format("Spese = %.2f;\n", pFattureSet->m_Spese);
			Spese = pFattureSet->m_Spese; 
			csApp.Format("%.2f;", Spese);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Gestione righe di fattura afferenti a verbali in concessione a quelli non in concessione ed a quelli geotecnici
			pFattSerEroVer->m_strFilter.Format("([FATTURE].Codice = %d) AND ([SERVIZI_EROGATI].Fattura = [FATTURE].Codice) AND ([VERBALI].Codice = [SERVIZI_EROGATI].Verbale)", pFattureSet->m_Codice);
			if(!pFattSerEroVer->Requery())
			{
				MessageBox("Errore nell'apertura del file di esportazione. Esportazione fallita!", "Errore", MB_OK);
				pAziendeSet->Close();
				delete pAziendeSet;
				pFattureSet->Close();
				delete pFattureSet;
				pFattSerEroVer->Close();
				delete pFattSerEroVer;
				pTipiPag->Close();
				delete pTipiPag;
				return;
			}

			BOOL Urgenza = FALSE;				
			double Totale = 0;
			int Verbale = 0;
			int TipoVer = -1;
			if(!pFattSerEroVer->IsEOF())
				Verbale = pFattSerEroVer->m_Verbale;

			for (; !pFattSerEroVer->IsEOF(); pFattSerEroVer->MoveNext())
			{
				TipoVer = pFattSerEroVer->m_TipoVerbale;

				if(Verbale != pFattSerEroVer->m_Verbale)
				{
					if(Urgenza)
					{
						if (TipoVer == VERB_IN_CONCESSIONE)
								ImpConcessione		+= Totale + (Totale/2);
						else if ((TipoVer == VERB_NON_IN_CONCESSIONE) ||
										(TipoVer == VERB_NC_PROVE_DI_CARICO)	||
										(TipoVer == VERB_NC_CONGL_BITUMINOSI) ||
										(TipoVer == VERB_NC_INERTI)						||
										(TipoVer == VERB_NC_MONITORAGGI)			||
										(TipoVer == VERB_NC_VARIE)						||
										(TipoVer == VERB_NC_GEOTECNICA))
								ImpNonConcessione += Totale + (Totale/2);
						else if (TipoVer == VERB_GEOLOGIA)
								ImpGeotecnica += Totale + (Totale/2);
						else
							ImpAltro += Totale + (Totale/2);
					}
					else
					{
						if (TipoVer == VERB_IN_CONCESSIONE)
								ImpConcessione		+= Totale;
						else if ((TipoVer == VERB_NON_IN_CONCESSIONE) ||
										(TipoVer == VERB_NC_PROVE_DI_CARICO)	||
										(TipoVer == VERB_NC_CONGL_BITUMINOSI) ||
										(TipoVer == VERB_NC_INERTI)						||
										(TipoVer == VERB_NC_MONITORAGGI)			||
										(TipoVer == VERB_NC_VARIE)						||
										(TipoVer == VERB_NC_GEOTECNICA))
								ImpNonConcessione += Totale;
						else if (TipoVer == VERB_GEOLOGIA)
								ImpGeotecnica += Totale;
						else
							ImpAltro += Totale;
					}

					Verbale = pFattSerEroVer->m_Verbale;
					Urgenza = FALSE;
					Totale = 0;
				}

				if(pFattSerEroVer->m_VuoiUrgenza == 1)
					Urgenza = TRUE;

				Totale += ((pFattSerEroVer->m_Prezzo * pFattSerEroVer->m_Quantita) -
														((pFattSerEroVer->m_Prezzo * pFattSerEroVer->m_Quantita) * pFattSerEroVer->m_ScontoSevizio) / 100);

			}

			if(Urgenza)
			{
				if (TipoVer == VERB_IN_CONCESSIONE)
						ImpConcessione		+= Totale + (Totale/2);
				else if ((TipoVer == VERB_NON_IN_CONCESSIONE)			||
										(TipoVer == VERB_NC_PROVE_DI_CARICO)	||
										(TipoVer == VERB_NC_CONGL_BITUMINOSI) ||
										(TipoVer == VERB_NC_INERTI)						||
										(TipoVer == VERB_NC_MONITORAGGI)			||
										(TipoVer == VERB_NC_VARIE)						||
										(TipoVer == VERB_NC_GEOTECNICA))
						ImpNonConcessione += Totale + (Totale/2);
				else if (TipoVer == VERB_GEOLOGIA)
						ImpGeotecnica += Totale + (Totale/2);
				else
					ImpAltro += Totale + (Totale/2);
			}
			else if (TipoVer != -1)
			{
				if (TipoVer == VERB_IN_CONCESSIONE)
						ImpConcessione		+= Totale;
				else if ((TipoVer == VERB_NON_IN_CONCESSIONE)			||
										(TipoVer == VERB_NC_PROVE_DI_CARICO)	||
										(TipoVer == VERB_NC_CONGL_BITUMINOSI) ||
										(TipoVer == VERB_NC_INERTI)						||
										(TipoVer == VERB_NC_MONITORAGGI)			||
										(TipoVer == VERB_NC_VARIE)						||
										(TipoVer == VERB_NC_GEOTECNICA))
						ImpNonConcessione += Totale;
				else if (TipoVer == VERB_GEOLOGIA)
						ImpGeotecnica += Totale;
				else
					ImpAltro += Totale;
			}

			//Toglie l'eventuale sconto
			ImpConcessione		-= ((ImpConcessione			* pFattSerEroVer->m_Sconto)		/ 100);
			ImpNonConcessione -= ((ImpNonConcessione	* pFattSerEroVer->m_Sconto)		/ 100);
			ImpGeotecnica			-= ((ImpGeotecnica			* pFattSerEroVer->m_Sconto)		/ 100);
			ImpAltro					-= ((ImpAltro						* pFattSerEroVer->m_Sconto)		/ 100);

			Imponibile = ImpConcessione + ImpNonConcessione + ImpGeotecnica + ImpAltro;

			//Calcolo l'IVA
			IVA = (Imponibile * pFattureSet->m_Aliquota) / 100;

			//Imponibile Concessione
			//csApp.Format("Imponibile Concessione = %.2f;\n", ImpConcessione);
			csApp.Format("%.2f;", ImpConcessione);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Imponibile Non Concessione
			//csApp.Format("Imponibile Non Concessione = %.2f;\n", ImpNonConcessione);
			csApp.Format("%.2f;", ImpNonConcessione);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Imponibile Geotecnica
			//csApp.Format("Imponibile Geotecnica = %.2f;\n", ImpGeotecnica);
			csApp.Format("%.2f;", ImpGeotecnica);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Imponibile Altro
			//csApp.Format("Imponibile Altro = %.2f;\n", ImpAltro);
			csApp.Format("%.2f;", ImpAltro);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Ritenuta d'acconto
			RitenutaAcc = (Imponibile * pFattureSet->m_RitAcconto) / 100;
			//csApp.Format("Ritenuta D'Acconto = %.2f;\n", RitenutaAcc);
			csApp.Format("%.2f;", RitenutaAcc);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//IVA
			//csApp.Format("Importo IVA = %.2f;\n", IVA);
			csApp.Format("%.2f;", IVA);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Imponibile
			//csApp.Format("Imponibile = %.2f;\n", ImpConcessione + ImpNonConcessione + ImpGeotecnica + ImpAltro);
			csApp.Format("%.2f;", Imponibile);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			//Totale Fattura (c'è un errore il campo si chiama imponibile ma contiene il totale fattura)
			//Si eseguono le seguenti conversioni per approssimare al centesimo
			CString csImpConcessione("");
			csImpConcessione.Format("%.2f", ImpConcessione);
			ImpConcessione = atof(csImpConcessione.GetBuffer(csImpConcessione.GetLength()));

			CString csImpNonConcessione("");
			csImpNonConcessione.Format("%.2f", ImpNonConcessione);
			ImpNonConcessione = atof(csImpNonConcessione.GetBuffer(csImpNonConcessione.GetLength()));

			CString csImpGeotecnica("");
			csImpGeotecnica.Format("%.2f", ImpGeotecnica);
			ImpGeotecnica = atof(csImpGeotecnica.GetBuffer(csImpGeotecnica.GetLength()));

			CString csImpAltro("");
			csImpAltro.Format("%.2f", ImpAltro);
			ImpAltro = atof(csImpAltro.GetBuffer(csImpAltro.GetLength()));

			CString csIVA("");
			csIVA.Format("%.2f", IVA);
			IVA = atof(csIVA.GetBuffer(csIVA.GetLength()));

			CString csImponibile("");
			csImponibile.Format("%.2f", Imponibile);
			Imponibile = atof(csImponibile.GetBuffer(csImponibile.GetLength()));

			CString csRitenutaAcc("");
			csRitenutaAcc.Format("%.2f", RitenutaAcc);
			RitenutaAcc = atof(csRitenutaAcc.GetBuffer(csRitenutaAcc.GetLength()));

			CString csSpese("");
			csSpese.Format("%.2f", Spese);
			Spese = atof(csSpese.GetBuffer(csSpese.GetLength()));

			//csApp.Format("Totale Fattura = %.2f;\n", ImpConcessione + ImpNonConcessione + ImpGeotecnica + ImpAltro + IVA - RitenutaAcc);
			double TotaleFattura = Imponibile + IVA - RitenutaAcc + Spese;
			csApp.Format("%.2f;", TotaleFattura);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);
			TotaleFattura = atof(csApp.GetBuffer(csApp.GetLength()));

			// tabella scadenza-importo rata (max 5 rate) per pagamento RiBa/Bonifico
			for(int i = 0; i < 5; i++)
			{
				if(!(pTipiPag->IsEOF()) && i < pTipiPag->m_NumRate)
				{
					double dImportoRata = TotaleFattura / pTipiPag->m_NumRate;
					CString csImpRata("");
					csImpRata.Format("%.2f;", dImportoRata);
					dImportoRata = atof(csImpRata.GetBuffer(csImpRata.GetLength()));
					double dTotRate = dImportoRata*pTipiPag->m_NumRate;
					while(dTotRate > TotaleFattura)
					{
						dImportoRata -= 0.01;
						dTotRate = dImportoRata*pTipiPag->m_NumRate;
					}
					if(i == pTipiPag->m_NumRate-1)
					{
						// eventuale correzione arrotondamento al centesimo sull'ultima rata
						if(dTotRate < TotaleFattura)
						{
							dImportoRata += (TotaleFattura - dTotRate);
						}
					}
					CTime data = pApp->GetScadenza(pFattureSet->m_Data, pTipiPag->m_GiorniPrimaScad + 30*i, pTipiPag->m_Allineamento); 
					csApp.Format("%s;%.2f;", data.Format("%d/%m/%Y"), dImportoRata);
				}
				else
				{
					csApp.Format(";;");
				}
				fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);
			}

			// Flag IVA DIfferita (sc 31.03.2015)
			// modifica (sc 30.10.2018) il flag è posto a 1 sia per Differita (1) che Split (2)
			if(pFattureSet->m_IVADifferita == 1 || pFattureSet->m_IVADifferita == 2)
				csApp.Format("1;");
			else
				csApp.Format("0;");
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			// Flag Fattura Elettronica (sc 17.10.2015)
			csApp.Format("%d;", pFattureSet->m_Elett);
			fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);

			pFattureSet->MoveNext();
			if(!pFattureSet->IsEOF())
			{
				csApp = "\n";
				fwrite(csApp.GetBuffer(csApp.GetLength()), csApp.GetLength(),1,f);
			}
		}

		fclose(f);

		pAziendeSet->Close();
		delete pAziendeSet;

		pFattureSet->Close();
		delete pFattureSet;

		pFattSerEroVer->Close();
		delete pFattSerEroVer;

		pTipiPag->Close();
		delete pTipiPag;
	}

	//Generazione del File PDF
	CStampaFattureDlg* StampaFatture = new CStampaFattureDlg;
	StampaFatture->PrnFromFattToFatt(esporta.m_intDaFattura, esporta.m_intAFattura, esporta.m_csAnno, ((CWinSigmaDoc*)GetDocument()));
	delete StampaFatture;
}


// Emissione di una fattura
void CFattureView::OnFatturaEmetti() 
{
  if(m_lCodiceFattura > 0 || m_pVerbaliInFatturazione->IsBOF() || m_pVerbaliInFatturazione->IsEOF())
  {
    MessageBeep(-1);
    return;
  }

	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CString msg,strDatiOccupante;
	// Blocco della certificazione
	if( !pApp->DisabilitaFatturazione(&strDatiOccupante) )
	{
		msg = STR_BLOCCO_FATTURAZIONE(strDatiOccupante);
		msg = msg + STR_ISTRUZIONI_RIMOZIONE;
		AfxMessageBox(msg);
		return;
	}
  EmettiSalvaFattura(FALSE);

	pApp->DisabilitaFatturazione(&strDatiOccupante, FALSE);
}

// Emissione di una fattura
void CFattureView::OnFatturaElettEmetti() 
{
  if(m_lCodiceFattura > 0 || m_pVerbaliInFatturazione->IsBOF() || m_pVerbaliInFatturazione->IsEOF())
  {
    MessageBeep(-1);
    return;
  }

	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CString msg,strDatiOccupante;
	// Blocco della certificazione
	if( !pApp->DisabilitaFatturazione(&strDatiOccupante) )
	{
		msg = STR_BLOCCO_FATTURAZIONE(strDatiOccupante);
		msg = msg + STR_ISTRUZIONI_RIMOZIONE;
		AfxMessageBox(msg);
		return;
	}
  EmettiSalvaFattura(TRUE);

	pApp->DisabilitaFatturazione(&strDatiOccupante, FALSE);
}

// Salva le modifiche effettuate a fatture emesse
void CFattureView::OnVisualizzaFattura() 
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  if(m_lCodiceFattura <= 0 || m_pFattureEmesseSet->IsBOF() || m_pFattureEmesseSet->IsEOF())
  {
    MessageBeep(-1);
    return;
  }

	if( !pApp->SetFatturaInUso(m_pFattureEmesseSet))
		return;
  EmettiSalvaFattura(m_pFattureEmesseSet->m_Elett);
	
	pApp->SetFatturaInUso(m_pFattureEmesseSet, TRUE);

}

// Emissione/Esportazione XML di una fattura
void CFattureView::OnFatturaXML() 
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	// Fattura da emettere
  if(m_lCodiceFattura <= 0 || m_pFattureEmesseSet->IsBOF() || m_pFattureEmesseSet->IsEOF())
  {
    AfxMessageBox(CREATE_INVOICE_FIRST_MSG);
    return;
/*
		CString msg,strDatiOccupante;
		// Blocco della certificazione
		if( !pApp->DisabilitaFatturazione(&strDatiOccupante) )
		{
			msg = STR_BLOCCO_FATTURAZIONE(strDatiOccupante);
			msg = msg + STR_ISTRUZIONI_RIMOZIONE;
			AfxMessageBox(msg);
			return;
		}
		EmettiSalvaFattura(TRUE);

		pApp->DisabilitaFatturazione(&strDatiOccupante, FALSE);
*/
  }
	// Fattura emessa
  else if(m_lCodiceFattura > 0 || m_pVerbaliInFatturazione->IsBOF() || m_pVerbaliInFatturazione->IsEOF())
  {
		if( !pApp->SetFatturaInUso(m_pFattureEmesseSet))
			return;
		EmettiSalvaFattura(m_pFattureEmesseSet->m_Elett);
		
		pApp->SetFatturaInUso(m_pFattureEmesseSet, TRUE);
  }


}

// bElett: FALSE=fattura tradizionale, TRUE=fattura elettronica
void CFattureView::EmettiSalvaFattura(BOOL bElett)
{
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CStampaFattureDlg dlg;
  int n;  
  CString str;

  UpdateData();
  m_DTCtrlDataEmissione.GetTime(m_DataEmissione);
  switch(VerificaSelezione())
  {
  case VERIFICA_ERR_DATA:
    AfxMessageBox("La data di emissione della fattura non è coerente con la data di accettazione dei verbali selezionati!\n Correggere le impostazioni e ripetere l'operazione.");
    return;
  case VERIFICA_ERR_DOC:
    AfxMessageBox("Attenzione: sono stati selezionati documenti di tipo diverso.\nCorreggere e ripetere l'operazione");
    return;
  default:
    break;
  }
  
  // Inizializzo i dai del dialogo per l'emissione e la stampa delle fatture
  dlg.m_pDoc = (CWinSigmaDoc*)GetDocument();
  dlg.m_nTipoDocumento = m_nTipoDocumento;
  dlg.m_lCodiceFatturaEmessa = m_lCodiceFattura;
  dlg.m_lCodiceAzienda = m_lCodiceAzienda;
	if(bElett == TRUE)
	{
		m_strTipoDocumento += " elettronica";
	}
  dlg.m_strTipoDocumento = m_strTipoDocumento;
	dlg.m_bElett = bElett;


  dlg.m_strPIVA_CF = "P. IVA";
  if(!m_strP_IVA.IsEmpty())
    dlg.m_strPIVA = m_strP_IVA;
  
  if (!m_strCodiceFiscale.IsEmpty())
		dlg.m_strCodFiscale = m_strCodiceFiscale;

  if (!m_strCodiceDestinatario.IsEmpty())
		dlg.m_strCodiceDestinatario = m_strCodiceDestinatario;

  if (!m_strPEC.IsEmpty())
		dlg.m_strPEC = m_strPEC;

  if (!m_strCUP.IsEmpty())
		dlg.m_strCUP = m_strCUP;

  if (!m_strCIG.IsEmpty())
		dlg.m_strCIG = m_strCIG;

  if (!m_strOrdineAcquisto.IsEmpty())
	{
		dlg.m_strOrdineAcquisto = m_strOrdineAcquisto;
		if(m_DataOrdineAcquisto > 0)
			dlg.m_DataOrdineAcquisto = m_DataOrdineAcquisto;
	}

  if (!m_strContratto.IsEmpty())
	{
		dlg.m_strContratto = m_strContratto;
		if(m_DataContratto > 0)
			dlg.m_DataContratto = m_DataContratto;
	}

  if (!m_strNumeroDDT.IsEmpty())
	{
		dlg.m_strNumeroDDT = m_strNumeroDDT;
		if(m_DataDDT > 0)
			dlg.m_DataDDT = m_DataDDT;
	}

  if (!m_strCodiceXML.IsEmpty())
		dlg.m_strCodiceXML = m_strCodiceXML;

  dlg.m_strRagioneSociale = m_strRagioneSociale;
  dlg.m_strCodice = m_strCodiceCliente;
  dlg.m_strIndirizzo = m_strIndirizzo;
  dlg.m_strTipoPagamento = m_strTipoPagamento;
  dlg.m_lTipoPagamento = m_lTipoPagamento;
  dlg.m_strBanca = m_strBanca;
  dlg.m_strBanca.Replace("\r\n", " ");
  dlg.m_strIBAN = m_strIBAN;
  dlg.m_strABI = m_strABI;
  dlg.m_strCAB = m_strCAB;
  dlg.m_strImponibile = m_strImporto;
  dlg.m_strSconto = m_strSconto;
  dlg.m_strAliquota = m_strAliquota;
  dlg.m_dSconto = m_dSconto;
  dlg.m_strImponibileScontato = m_strImportoScontato;
  dlg.m_nImponibileScontato = m_nImponibileScontato;
  dlg.m_DataFattura = m_DataEmissione;
  dlg.m_bFatturaProForma = FALSE;
  for(n = 0; n < m_aryCodServiziSelezionati.GetSize(); n++)
    dlg.m_aryCodiciServizi.Add(m_aryCodServiziSelezionati.GetAt(n));
  dlg.DoModal();
  m_pVerbaliInFatturazione->Requery();
  m_pServiziErogati->Requery();
  if(dlg.m_bFatturaEmessa)
  {
    pApp->ReloadTree(TREELABEL_FATTUREDAEMETTERE, m_lCodiceAzienda);
    m_lLastFattura = dlg.m_lCodiceFatturaEmessa;
  }
  if(dlg.m_lCodiceFatturaEmessa > 0)
  {
  // E' stata emessa una fattura: aggiorno gli alberini
    SINCRONIZE(m_pFattureEmesseSet, dlg.m_lCodiceFatturaEmessa);
    str.Format("%d", m_pFattureEmesseSet->m_Data.GetYear());
    if(dlg.m_bFatturaEmessa)
      pApp->ReloadTree(str, -1);
    m_lCodiceFattura = dlg.m_lCodiceFatturaEmessa;
    m_pVerbaliInFatturazione->Requery();
    ((CWinSigmaDoc*)GetDocument())->m_nSelectedTreeFatture = TREEITEM_FATTUREEMESSE; 
    if(dlg.m_bFatturaEmessa)
      LoadCurRecord(TRUE);
//    else    // s.c. 14.9.2018 provo a commentare qui cosi non cancella la visualizzazione dei dati fattura... vediamo
//      LoadCurRecord(FALSE);

		// ricarica le eventuali variazioni 
		m_strCUP = dlg.m_strCUP;
		m_strCIG = dlg.m_strCIG;
		m_strOrdineAcquisto = dlg.m_strOrdineAcquisto;
		m_DataOrdineAcquisto = dlg.m_DataOrdineAcquisto;
  	m_strContratto = dlg.m_strContratto;
		m_DataContratto = dlg.m_DataContratto;
		m_strNumeroDDT = dlg.m_strNumeroDDT;
		m_DataDDT = dlg.m_DataDDT;
		m_strCodiceXML = dlg.m_strCodiceXML;

    EnableServicesBtns(TRUE);
    EnableControls(FALSE);
    UpdateData(FALSE);
  }
}

// Aggiunge un servizio nel documento
void CFattureView::OnButtonAddServizio() 
{
  if(m_lCodiceAzienda <= 0)
    return;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CServiziFatturaDlg dlg;
  // Inizializzo i dati del dialogo
  dlg.m_lCodiceAzienda = m_lCodiceAzienda;
  dlg.m_lCodiceServizioErogato = -1;
  if(m_lCodiceUltimoVerbale > 0)
    dlg.m_lCodiceVerbale = m_lCodiceUltimoVerbale;
  else
    dlg.m_lCodiceVerbale = -1;
  dlg.m_pDoc = (CWinSigmaDoc*)GetDocument();
  dlg.m_nOperazione = AGGIUNGI_SERVIZIO;
  dlg.m_lCodiceFattura = m_lCodiceFattura;
  dlg.m_lListinoGenerale = m_lListinoGenerale;
  dlg.m_lListinoParticolare = m_lListinoParticolare;
  if(dlg.DoModal()== IDOK)
  {
    m_lCodiceUltimoVerbale = dlg.m_lCodiceVerbale;
    m_pServiziErogati->Requery();
    LoadServizi();
    if(dlg.m_lCodiceFattura > 0)
    {
      m_lCodiceFattura = dlg.m_lCodiceFattura;
      SINCRONIZE(m_pFattureEmesseSet, m_lCodiceFattura);
      // Aggiorno il record della fattura
      m_pFattureEmesseSet->Edit();
      m_pFattureEmesseSet->m_Imponibile = (double)m_nTotaleFattura / 100;
      m_pFattureEmesseSet->Update();
      SINCRONIZE(m_pFattureEmesseSet, m_lCodiceFattura);
      pApp->ReloadTree(m_pFattureEmesseSet->m_Data.Format("%Y"), m_lCodiceFattura);
    }
    else
      pApp->ReloadTree(TREELABEL_FATTUREDAEMETTERE, m_lCodiceAzienda);
  }
  UpdateData(FALSE);
}

// Elimina un servizio dal documento
void CFattureView::OnButtonDelServizio() 
{
  int n;
  POSITION pos;
  CString str;
  if((pos = m_ListServizi.GetFirstSelectedItemPosition()) == NULL)
  {
    AfxMessageBox("Selezionare un servizio");
    return;
  }
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  n = m_ListServizi.GetNextSelectedItem(pos);
  if(m_ListServizi.GetItemData(n) == 0)
    return;
  // Sincronizzo il recordset
  m_pServiziErogati->m_strFilter.Empty();
  m_pServiziErogati->Requery();
  SINCRONIZE(m_pServiziErogati, (long)m_ListServizi.GetItemData(n));
  SINCRONIZE(m_pVerbaliInFatturazione, m_pServiziErogati->m_Verbale);
  if(!m_pServiziErogati->m_ID_Listino.IsEmpty() && m_pServiziErogati->m_ID_Listino != ID_SERVIZI_NO_LISTINO)
    str.Format("Eliminare il servizio %s?", m_pServiziErogati->m_ID_Listino);
  else
    str = "Eliminare il servizio selezionato?";
  if(AfxMessageBox(str, MB_YESNO) == IDYES)
    m_pServiziErogati->Delete();
  m_pServiziErogati->Requery();
  if(m_lCodiceFattura > 0)
    pApp->ReloadTree(m_pFattureEmesseSet->m_Data.Format("%Y"), m_lCodiceFattura);
  else
    pApp->ReloadTree(TREELABEL_FATTUREDAEMETTERE, m_lCodiceAzienda);
  LoadServizi();
  if(m_lCodiceFattura > 0)
  {
    SINCRONIZE(m_pFattureEmesseSet, m_lCodiceFattura);
    // Aggiorno il records della fattura
    m_pFattureEmesseSet->Edit();
    m_pFattureEmesseSet->m_Imponibile = (double)m_nTotaleFattura / 100;
    m_pFattureEmesseSet->Update();
    SINCRONIZE(m_pFattureEmesseSet, m_lCodiceFattura);
  }
  UpdateData(FALSE);
}

// Modifica i dati del servizio selezionato
void CFattureView::OnButtonModifyServizio() 
{
  int n;
  POSITION pos;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  if((pos = m_ListServizi.GetFirstSelectedItemPosition()) == NULL)
  {
    AfxMessageBox("Selezionare un servizio");
    return;
  }
  n = m_ListServizi.GetNextSelectedItem(pos);
  if(m_ListServizi.GetItemData(n) == 0)
    return;
  // Sincronizzo i recordset
  SINCRONIZE(m_pServiziErogati, (long)m_ListServizi.GetItemData(n));
  SINCRONIZE(m_pVerbaliInFatturazione, m_pServiziErogati->m_Verbale);
  CServiziFatturaDlg dlg;
  dlg.m_pDoc = (CWinSigmaDoc*)GetDocument();
  dlg.m_nOperazione = MODIFICA_SERVIZIO;
  dlg.m_lListinoGenerale = m_lListinoGenerale;
  if(IsDaListinoParticolare(m_pServiziErogati->m_CodiceServizio))
    dlg.m_lListinoParticolare = m_lListinoParticolare;
  else
    dlg.m_lListinoParticolare = 0;
  dlg.m_lCodiceAzienda = m_pVerbaliInFatturazione->m_CodiceAzFattura; // m_lCodiceAzienda
  dlg.m_lCodiceServizioErogato = m_pServiziErogati->m_Codice;
  m_lCodiceUltimoVerbale = m_pVerbaliInFatturazione->m_Codice;
  dlg.m_lCodiceFattura = m_lCodiceFattura;
  dlg.m_lCodiceVerbale = m_pVerbaliInFatturazione->m_Codice; //m_lCodiceUltimoVerbale;
  if(dlg.DoModal() == IDOK)
  {
    m_lCodiceUltimoVerbale = dlg.m_lCodiceVerbale;
    m_pServiziErogati->Requery();
    if(dlg.m_lCodiceFattura > 0)
      pApp->ReloadTree(m_pFattureEmesseSet->m_Data.Format("%Y"), m_lCodiceFattura);
    else
      pApp->ReloadTree(TREELABEL_FATTUREDAEMETTERE, m_lCodiceAzienda);
    LoadServizi();
    if(m_lCodiceFattura > 0)
    {
      SINCRONIZE(m_pFattureEmesseSet, m_lCodiceFattura);
      // Aggiorno il records della fattura
      m_pFattureEmesseSet->Edit();
      m_pFattureEmesseSet->m_Imponibile = (double)m_nTotaleFattura / 100;
      m_pFattureEmesseSet->Update();
      SINCRONIZE(m_pFattureEmesseSet, m_lCodiceFattura);
    }
  }
  UpdateData(FALSE);
}

BOOL CFattureView::IsDaListinoParticolare(long codiceServizio)
{
  if(!m_lListinoParticolare)
    return FALSE;
  BOOL bRes;
  CCategorieServiziSet* pCatServSet = new CCategorieServiziSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
  pCatServSet->m_strFilter.Format("Listino = %d AND Categoria = CATEGORIE.Codice AND SERVIZI_LISTINO.Codice = %d", m_lListinoParticolare, codiceServizio);
  pCatServSet->Open();
  bRes = !pCatServSet->IsEOF();
  pCatServSet->Close();
  return bRes;
}

// Abilita/Disabilita le edit dell'anagrafica cliente
void CFattureView::EnableControls(BOOL bEnable)
{
  m_EditRagioneSociale.EnableWindow(bEnable);
  m_EditCodiceCliente.EnableWindow(bEnable);
  m_EditIndirizzo.EnableWindow(bEnable);
  m_EditCodFiscale.EnableWindow(bEnable);
  m_EditCodiceDestinatario.EnableWindow(bEnable);
  m_EditPEC.EnableWindow(bEnable);
  m_EditSconto.EnableWindow(bEnable);
  m_EditP_IVA.EnableWindow(bEnable);
  m_ComboTipoPagamento.EnableWindow(bEnable);
  m_EditBanca.EnableWindow(bEnable);
  m_EditCAB.EnableWindow(bEnable);
  m_EditABI.EnableWindow(bEnable);
  m_EditIBAN.EnableWindow(bEnable);
}

// Abilita/Disabilita i pulsanti per aggiungere, modificare o eliminare un servizio
void CFattureView::EnableServicesBtns(BOOL bEnable)
{
  m_BtnModifyServizio.EnableWindow(bEnable);
  m_BtnAddServizio.EnableWindow(bEnable);
  m_BtnDeleteServizio.EnableWindow(bEnable);
}


int CFattureView::DeleteRecord(void)
{
  return 0;
}

int CFattureView::SaveRecord(void)
{
  return 0;
}

int CFattureView::NewRecord(void)
{
  return 0;
}

void CFattureView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
  CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  
  if(pDoc->m_nSelectedTreeFatture == TREEITEM_FATTUREDAEMETTERE && !m_pVerbaliInFatturazione->IsEOF())
	  CXFormView::m_pSet = m_pVerbaliInFatturazione;
  else
    if(!m_pFattureEmesseSet->IsEOF())
      CXFormView::m_pSet = m_pFattureEmesseSet;
  CXFormView::OnUpdate(pSender, lHint, pHint);
}


void CFattureView::OnItemchangingListVerbali(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(!m_bEnableServiziCheck)
    return;
  if(m_lCodiceFattura)
    return;
  m_bVerbaliChecked = m_ListVerbali.GetCheck(pNMListView->iItem);
	*pResult = 0;
}

void CFattureView::OnItemchangedListVerbali(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(!m_bEnableServiziCheck)
    return;
  if(m_lCodiceFattura)
    return;
  int nItem;
  nItem = pNMListView->iItem;
  if(VerificaSelezione() == VERIFICA_ERR_DOC)
  {
    AfxMessageBox("Attenzione: sono stati selezionati documenti di tipo diverso.\nCorreggere e ripetere l'operazione");
    m_bEnableServiziCheck = FALSE;
    m_ListVerbali.SetCheck(nItem, FALSE);
    UpdateData(FALSE);
    m_bEnableServiziCheck = TRUE;
    return;
  }
  CString str;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  SINCRONIZE(m_pVerbaliInFatturazione, (long)m_ListVerbali.GetItemData(nItem));
  pApp->LockTable(VERBALI);
  m_pVerbaliInFatturazione->Edit();
  m_pVerbaliInFatturazione->m_InFatturazione = m_ListVerbali.GetCheck(nItem);
  m_pVerbaliInFatturazione->Update();
  pApp->UnlockTables();
  SINCRONIZE(m_pVerbaliInFatturazione, (long)m_ListVerbali.GetItemData(nItem));
  
  if (m_ListVerbali.GetCheck(nItem))
  {
    m_lListinoGenerale    = m_pVerbaliInFatturazione->m_ListinoGenerale; 
    m_lListinoParticolare = m_pVerbaliInFatturazione->m_ListinoParticolare;
  }
  
  LoadServizi();
  
	*pResult = 0;
  UpdateData(FALSE);
}


void CFattureView::LoadServizi(void)
{
  int m;
  CString str, strFilter;
  double dImporto, dSconto, dImportoTotale;
  CString strDescrizione;
  int nImportoVerbale, nMaggiorazione;
  BOOL bUrgenza;
  m_strImporto.Empty();
  m_aryCodServiziSelezionati.RemoveAll();
  nImportoVerbale = m_nImponibile = 0;
  dImportoTotale = 0;
  bUrgenza = FALSE;

  m_nImponibile = 0;
  m_ListServizi.DeleteAllItems();
  str.Empty();
  strFilter.Empty();
  for(SET_START(m_pVerbaliInFatturazione); !m_pVerbaliInFatturazione->IsEOF(); m_pVerbaliInFatturazione->MoveNext())
  {
    if(m_pVerbaliInFatturazione->m_InFatturazione == 1)
    {
      str.Format("Verbale = %ld", m_pVerbaliInFatturazione->m_Codice);
      str += " OR ";
      strFilter += str;
    }
  }
  strFilter.TrimRight(" OR ");
  if(strFilter.IsEmpty())
    str.Format("Fattura = %ld", m_lCodiceFattura);
  else
    str.Format(" AND Fattura = %d", m_lCodiceFattura);
  strFilter += str;
  m_pServiziErogati->m_strFilter = strFilter;
  m_pServiziErogati->m_strSort = "ID_Listino,Codice ASC";
  m_pServiziErogati->Requery();
  for(SET_START(m_pVerbaliInFatturazione); !m_pVerbaliInFatturazione->IsEOF(); m_pVerbaliInFatturazione->MoveNext())
  {
		bUrgenza = FALSE;
    if(m_pVerbaliInFatturazione->m_InFatturazione == 1)
    {
      if (m_pVerbaliInFatturazione->m_Urgenza != 2)
        bUrgenza = m_pVerbaliInFatturazione->m_Urgenza;
      for(SET_START(m_pServiziErogati); !m_pServiziErogati->IsEOF(); m_pServiziErogati->MoveNext())
      {
        if(m_pServiziErogati->m_Verbale != m_pVerbaliInFatturazione->m_Codice)
          continue;
        dImporto = 0.;
        m = m_ListServizi.GetItemCount();
        m = m_ListServizi.InsertItem(m, "");
        m_ListServizi.SetItemData(m, (DWORD)m_pServiziErogati->m_Codice);
        m_aryCodServiziSelezionati.Add((DWORD)m_pServiziErogati->m_Codice);
        if(m_pVerbaliInFatturazione->m_TipoVerbale != VERB_PER_FATTURA && m_pVerbaliInFatturazione->m_TipoVerbale != VERB_PER_NOTACREDITO)
				{
#ifdef WINSIGMA2
          str.Format("A%d", m_pVerbaliInFatturazione->m_ProgressivoTotale);
#else
          str.Format("%d/%d", m_pVerbaliInFatturazione->m_ProgressivoParziale, m_pVerbaliInFatturazione->m_ProgressivoTotale);
#endif
				}
        else
				{
          str.Empty();
				}
        m_ListServizi.SetItemText(m, 1, str);
        if(m_pServiziErogati->m_ID_Listino != ID_SERVIZI_NO_LISTINO)
        {
          m_ListServizi.SetItemText(m, 2, m_pServiziErogati->m_ID_Listino);
          // Formatto la stringa per le quantità: sono sempre interi
          str.Format("%.0f", m_pServiziErogati->m_Quantita);
        }
        else
        {
          m_ListServizi.SetItemText(m, 2, "");
          // Formatto la stringa per le quantità: possono essere frazionari
          if(m_pServiziErogati->m_Prezzo)
            str.Format("%.1f", m_pServiziErogati->m_Quantita);
          else
            str.Empty();
        }
        strDescrizione = m_pServiziErogati->m_Descrizione;
        strDescrizione.Replace("\r\n", " ");
        m_ListServizi.SetItemText(m, 3, strDescrizione);
        m_ListServizi.SetItemText(m, 4, str);
        Valuta prezzo(m_pServiziErogati->m_Prezzo);
        if(m_pServiziErogati->m_Prezzo != 0.)
          m_ListServizi.SetItemText(m, 5, prezzo.Format());
        else
          m_ListServizi.SetItemText(m, 5, "");
        dImporto = m_pServiziErogati->m_Prezzo * m_pServiziErogati->m_Quantita;
        // Sconto
        if(!m_pServiziErogati->IsFieldNull(&m_pServiziErogati->m_Sconto))
          dSconto = m_pServiziErogati->m_Sconto;
        else
          dSconto = 0;
        if(dSconto)
          str.Format("%.2f", dSconto);  
        else
          str = "0";
        if(m_pServiziErogati->m_Prezzo)
          m_ListServizi.SetItemText(m, 6, str);
        else
          m_ListServizi.SetItemText(m, 6, "");
        dImporto = dImporto - (dImporto * dSconto / 100);
        if(dImporto > 0)
          nImportoVerbale += (int)(dImporto * 100 + 0.5); 
        else
          nImportoVerbale += (int)(dImporto * 100 - 0.5);
        dImportoTotale += dImporto;
        Valuta importo(dImporto);
        if(dImporto != 0.)
          m_ListServizi.SetItemText(m, 7, importo.Format());
        else
          m_ListServizi.SetItemText(m, 7, "");
      }
      if(bUrgenza)
      {
        nMaggiorazione = (int)((double)nImportoVerbale / 2 + 0.5);
        nImportoVerbale += nMaggiorazione;
        m = m_ListServizi.GetItemCount();
        m = m_ListServizi.InsertItem(m, "");
        m_ListServizi.SetItemData(m, 0);
        str.Format("%d/%d", m_pVerbaliInFatturazione->m_ProgressivoParziale, m_pVerbaliInFatturazione->m_ProgressivoTotale);
        m_ListServizi.SetItemText(m, 1, str);
        m_ListServizi.SetItemText(m, 2, "");
        strDescrizione = "Maggiorazione del 50% per diritto procedura d'urgenza";
        m_ListServizi.SetItemText(m, 3, strDescrizione);
        m_ListServizi.SetItemText(m, 4, "");
        m_ListServizi.SetItemText(m, 5, "");
        m_ListServizi.SetItemText(m, 6, "");
        Valuta maggiorazione((double)nMaggiorazione);
        m_ListServizi.SetItemText(m, 7, maggiorazione.Format(-1, TRUE));
      }    
    }  
    m_nImponibile += nImportoVerbale;
    nImportoVerbale = 0;
  }
  Valuta importo((double)m_nImponibile);
  m_strImporto = importo.Format(-1, TRUE);
  // Applico lo sconto fattura sul totale
  dImportoTotale = (double)m_nImponibile / 100;
  dImportoTotale -= dImportoTotale * m_dSconto / 100;
  m_nImponibileScontato = (int)(dImportoTotale * 100 + 0.5);
  double dIVA = (dImportoTotale * atof(m_strAliquota) / 100);
  m_nIVA = (int)(dIVA * 100 + 0.5);
  CalcolaTotale();
  m_pVerbaliInFatturazione->Requery();
}

void CFattureView::CalcolaTotale(void)
{
  Valuta impScontato((double)m_nImponibileScontato);
  m_strImportoScontato = impScontato.Format(-1, TRUE);
  int spese = 0;
  CString str;
  if(!m_strSpeseSpedizione.IsEmpty())
  {
    str = m_strSpeseSpedizione;
    str.Replace(",", ".");
    spese = (int)(atof(str) * 100 + 0.5);
  }
  Valuta iva(m_nIVA);
  m_strIVA = iva.Format(-1, TRUE);
  m_nTotaleFattura = m_nImponibileScontato + m_nIVA + spese;

  // Ritenuta Acconto
  double Imp = ((
                (m_pFattureEmesseSet->m_Imponibile - m_pFattureEmesseSet->m_Spese) / 
                (100 + m_pFattureEmesseSet->m_Aliquota - m_pFattureEmesseSet->m_RitAcconto)
                ) 
                * 100);
  double RA = (Imp * m_pFattureEmesseSet->m_RitAcconto) / 100;
  m_nTotaleFattura -= (int)(RA * 100 + 0.5);
  m_csRitAcconto.Format("%2.0f", m_pFattureEmesseSet->m_RitAcconto);
  m_csTotRitAcconto.Format("%.2f", RA);

  Valuta totale(m_nTotaleFattura);
  m_strTotale = totale.Format(-1, TRUE);
}


void CFattureView::OnDblclkListServizi(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnButtonModifyServizio();
	*pResult = 0;
}

// Stampa una fattura proforma, cioè senza emetterla e con numero 0
void CFattureView::OnPrintProforma() 
{
	PrintProforma(TRUE);
}

void CFattureView::PrintProforma(BOOL bheader)
{
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CStampaFattureDlg dlg;
	dlg.SetHeader(bheader);
  int n;  
  CString str;
  if(m_pVerbaliInFatturazione->IsBOF() || m_pVerbaliInFatturazione->IsEOF() || m_lCodiceFattura > 0)
  {
    MessageBeep(-1);
    return;
  }
  // Inizializzo i dai del dialogo per l'emissione e la stampa delle fatture
  dlg.m_pDoc = (CWinSigmaDoc*)GetDocument();
  dlg.m_lCodiceFatturaEmessa = 0;
  dlg.m_lCodiceAzienda = m_pVerbaliInFatturazione->m_CodiceAzFattura;
  dlg.m_strPIVA = m_strP_IVA;
  dlg.m_strCodFiscale =  m_strCodiceFiscale;
  dlg.m_strCodiceDestinatario =  m_strCodiceDestinatario;
  dlg.m_strPEC =  m_strPEC;
  if (!m_strCUP.IsEmpty())
		dlg.m_strCUP = m_strCUP;

  if (!m_strCIG.IsEmpty())
		dlg.m_strCIG = m_strCIG;

  if (!m_strOrdineAcquisto.IsEmpty())
	{
		dlg.m_strOrdineAcquisto = m_strOrdineAcquisto;
		if(m_DataOrdineAcquisto > 0)
			dlg.m_DataOrdineAcquisto = m_DataOrdineAcquisto;
	}

  if (!m_strContratto.IsEmpty())
	{
		dlg.m_strContratto = m_strContratto;
		if(m_DataContratto > 0)
			dlg.m_DataContratto = m_DataContratto;
	}

  if (!m_strNumeroDDT.IsEmpty())
	{
		dlg.m_strNumeroDDT = m_strNumeroDDT;
		if(m_DataDDT > 0)
			dlg.m_DataDDT = m_DataDDT;
	}

  if (!m_strCodiceXML.IsEmpty())
		dlg.m_strCodiceXML = m_strCodiceXML;

  dlg.m_strRagioneSociale = m_strRagioneSociale;
  dlg.m_strCodice = m_strCodiceCliente;
  dlg.m_strIndirizzo = m_strIndirizzo;
  dlg.m_strTipoPagamento = m_strTipoPagamento;
  dlg.m_lTipoPagamento = m_lTipoPagamento;
  dlg.m_strBanca = m_strBanca;
  dlg.m_strBanca.Replace("\r\n", " ");
  dlg.m_strIBAN = m_strIBAN;
  dlg.m_strABI = m_strABI;
  dlg.m_strCAB = m_strCAB;
  dlg.m_strImponibile = m_strImporto;
  dlg.m_strSconto = m_strSconto;
  dlg.m_strAliquota = m_strAliquota;
  dlg.m_dSconto = m_dSconto;
  dlg.m_strImponibileScontato = m_strImportoScontato;
  dlg.m_nImponibileScontato = m_nImponibileScontato;
  dlg.m_strAliquota = STR_DEFAULT_ALIQUOTA_IVA;
  dlg.m_DataFattura = m_DataEmissione;
  dlg.m_bFatturaProForma = TRUE;
  for(n = 0; n < m_aryCodServiziSelezionati.GetSize(); n++)
    dlg.m_aryCodiciServizi.Add(m_aryCodServiziSelezionati.GetAt(n));
  dlg.DoModal();
}


void CFattureView::OnTrovaAzienda() 
{
  UpdateData(TRUE);
  if(m_pFattureEmesseSet->IsBOF() || m_pFattureEmesseSet->IsEOF() || m_lCodiceFattura <= 0)
  {
    MessageBeep(-1);
    return;
  }
  CTrovaAziendaDlg dlg;
  dlg.m_strTipoRicerca = "Ricerca anagrafica";
  if(dlg.DoModal() == IDOK)
  {
    CString str;
    CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
    CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
    CAziendeSet* pAziendeSet = pDoc->m_pAziendeSet;
    CTipiPagamentoSet* pTipiPagamento = pDoc->m_pTipiPagamentoSet;
    SINCRONIZE(pAziendeSet, dlg.m_lCodice);
    m_lCodiceAzienda = dlg.m_lCodice;
    m_strRagioneSociale = pAziendeSet->m_RagioneSociale;
    m_strCodiceCliente = pAziendeSet->m_ID;
    if(!pAziendeSet->IsFieldNull(&pAziendeSet->m_TipoPagamento) && pAziendeSet->m_TipoPagamento > 0)
    {
      SINCRONIZE(pTipiPagamento, pAziendeSet->m_TipoPagamento);
      m_strTipoPagamento = pTipiPagamento->m_Nome;
      if(!pTipiPagamento->IsFieldNull(&pTipiPagamento->m_Allineamento) && pTipiPagamento->m_Allineamento)
      {
        m_strBanca = pAziendeSet->m_Banca;
        m_strIBAN   = pAziendeSet->m_IBAN;
        m_strABI   = pAziendeSet->m_ABI;
        m_strCAB   = pAziendeSet->m_CAB;
      }
      else
      {
        m_strBanca = pTipiPagamento->m_Banca;
        m_strIBAN   = pTipiPagamento->m_IBAN;
        m_strABI   = pTipiPagamento->m_ABI;
        m_strCAB   = pTipiPagamento->m_CAB;
      }
    }
    else
    {
      m_strBanca.Empty();
      m_strIBAN.Empty();
      m_strABI.Empty();
      m_strCAB.Empty();
      m_strTipoPagamento = "Contrassegno";
    }
    if(!pAziendeSet->m_Indirizzo.IsEmpty())
    {
      m_strIndirizzo.Format("%s, %s %s", pAziendeSet->m_Indirizzo, pAziendeSet->m_CAP, pAziendeSet->m_Citta);
      if(!pAziendeSet->m_Provincia.IsEmpty())
      {
        str.Format(" (%s)", pAziendeSet->m_Provincia);
        m_strIndirizzo += str;
      }
    }
    m_strP_IVA = pAziendeSet->m_P_IVA;
    m_strCodiceFiscale = pAziendeSet->m_CodiceFiscale;
    if(!pAziendeSet->IsFieldNull(&pAziendeSet->m_CodiceDestinatario))
	    m_strCodiceDestinatario = pAziendeSet->m_CodiceDestinatario;
		
    if(!pAziendeSet->IsFieldNull(&pAziendeSet->m_PEC))
		  m_strPEC = pAziendeSet->m_PEC;

    if(!pAziendeSet->IsFieldNull(&pAziendeSet->m_Sconto))
      m_dSconto = pAziendeSet->m_Sconto;
    else
      m_dSconto = 0.;
    m_strSconto.Format("%.0f", m_dSconto);
    // Salvo i dati nei recordset
    SINCRONIZE(m_pFattureEmesseSet, m_lCodiceFattura);
    pApp->LockTable(FATTURE);
    m_pFattureEmesseSet->Edit();
    m_pFattureEmesseSet->m_Intestatario = m_lCodiceAzienda;
    m_pFattureEmesseSet->m_P_IVA = pAziendeSet->m_P_IVA;
    m_pFattureEmesseSet->m_TipoPagamento = pAziendeSet->m_TipoPagamento;
    m_pFattureEmesseSet->m_RagioneSociale = pAziendeSet->m_RagioneSociale;
    m_pFattureEmesseSet->m_IDIntestatario = pAziendeSet->m_ID;
    m_pFattureEmesseSet->m_Indirizzo = pAziendeSet->m_Indirizzo;
    m_pFattureEmesseSet->m_CAP = pAziendeSet->m_CAP;
    m_pFattureEmesseSet->m_Citta = pAziendeSet->m_Citta;
    m_pFattureEmesseSet->m_Provincia = pAziendeSet->m_Provincia;
    m_pFattureEmesseSet->m_Note = pAziendeSet->m_Note;
    if(!pAziendeSet->IsFieldNull(&pAziendeSet->m_Sconto))
      m_pFattureEmesseSet->m_Sconto = pAziendeSet->m_Sconto;
    m_pFattureEmesseSet->m_Banca = pAziendeSet->m_Banca;
    m_pFattureEmesseSet->m_IBAN = pAziendeSet->m_IBAN;
    m_pFattureEmesseSet->m_ABI = pAziendeSet->m_ABI;
    m_pFattureEmesseSet->m_CAB = pAziendeSet->m_CAB;
    if(!pTipiPagamento->m_Banca.IsEmpty())
    {
      m_pFattureEmesseSet->m_BancaAppoggio = pTipiPagamento->m_Banca;
      m_pFattureEmesseSet->m_IBANAppoggio = pTipiPagamento->m_IBAN;
      m_pFattureEmesseSet->m_ABIAppoggio = pTipiPagamento->m_ABI;
      m_pFattureEmesseSet->m_CABAppoggio = pTipiPagamento->m_CAB;
    }
    else
    {
      m_pFattureEmesseSet->m_BancaAppoggio.Empty();
      m_pFattureEmesseSet->m_IBANAppoggio.Empty();
      m_pFattureEmesseSet->m_ABIAppoggio.Empty();
      m_pFattureEmesseSet->m_CABAppoggio.Empty();
    }
    m_pFattureEmesseSet->Update();
    pApp->UnlockTables();
    SINCRONIZE(m_pFattureEmesseSet, m_lCodiceFattura);
    pApp->ReloadTree(m_pFattureEmesseSet->m_Data.Format("%Y"), m_lCodiceFattura);
    UpdateData(FALSE);
  }
}

// Aggiorna i dati presenti nello spazio di navigazione delle fatture
void CFattureView::AggiornaAlbero() 
{
	CWinSigmaApp* pApp	= (CWinSigmaApp*)AfxGetApp();
	if(pApp->GetViewMode() == MODE_EDIT)
		return;
  m_pFattureEmesseSet->m_strFilter.Format("Archiviata = 0 AND Codice >= %d AND Data is not NULL", m_lLastFattura);
  m_pFattureEmesseSet->Requery();
  for(SET_START(m_pFattureEmesseSet); !m_pFattureEmesseSet->IsEOF(); m_pFattureEmesseSet->MoveNext())
  {
    pApp->ReloadTree(m_pFattureEmesseSet->m_Data.Format("%Y"), m_pFattureEmesseSet->m_Codice);
  }
  m_pServiziErogati->Requery();
  m_pVerbaliInFatturazione->m_strFilter = "Fattura = 0";
  m_pVerbaliInFatturazione->Requery();
  CString str;
  long code;
  for(SET_START(m_pVerbaliInFatturazione); !m_pVerbaliInFatturazione->IsEOF(); m_pVerbaliInFatturazione->MoveNext())
  {
    str = m_pVerbaliInFatturazione->m_NomeAzFattura;
    code = m_pVerbaliInFatturazione->m_CodiceAzFattura;
  	pApp->ReloadTree(TREELABEL_FATTUREDAEMETTERE, m_pVerbaliInFatturazione->m_CodiceAzFattura);
  }
  LoadCurRecord(FALSE);
  UpdateData(FALSE);
}

// Creazione di una fattura senza verbale
void CFattureView::OnNuovaSenzaVerbale() 
{
  CTime data(CTime::GetCurrentTime().GetYear(), 1, 1, 0, 0, 0);
  m_pVerbaliInFatturazione->m_strFilter.Format("Fattura = 0 and DataAccettazione >= '%s'", data.Format("%Y-%m-%d"));
  m_pVerbaliInFatturazione->Requery();
  m_DataEmissione = CTime::GetCurrentTime();
	// Creo un verbale finto di tipo VERB_PER_FATTURA a cui riferire i servizi
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  CVerbaliSet verbaliSet(&pApp->m_db);
  verbaliSet.m_strFilter = "Codice = 0";
  verbaliSet.Open();
  CListiniSet* pListinoSet;
  pApp->LockTable(VERBALI);
  verbaliSet.AddNew();
  verbaliSet.m_TipoVerbale = VERB_PER_FATTURA;
  verbaliSet.m_ProgressivoParziale = 0;
  verbaliSet.m_ProgressivoTotale = 0;
	verbaliSet.m_CodiceAzFattura = 0;
  verbaliSet.m_Cantiere.Empty();
  // Operatore
  verbaliSet.m_Operatore = pApp->GetUserName();
  verbaliSet.m_DataAccettazione = CTime::GetCurrentTime();
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
	verbaliSet.m_ListinoParticolare = 0;
	verbaliSet.m_CertOgniSerie   = 0;
  verbaliSet.m_DataConsegna = 0;
  verbaliSet.m_Urgenza = 0;
  verbaliSet.m_Spedizione = 0;
  verbaliSet.m_LungaScadenza = 0;
  // Metto il verbale in fatturazione
  verbaliSet.m_NumeroFattura = 0;
  verbaliSet.m_InFatturazione = 2;
  // Aggiorno il recordset
  verbaliSet.Update();
  // Sblocco la tabella
  pApp->UnlockTables();
  verbaliSet.m_strFilter.Empty();
  verbaliSet.Close();
  m_pVerbaliInFatturazione->Requery();
  // Carico il record corrente
  LoadCurRecord(FALSE);
  UpdateData(FALSE);
  // Abilito le edit per l'inserimento dei dati dell'azienda
  EnableControls(TRUE);
  m_EditCodiceCliente.SetFocus();
  m_nState = FATT_SVERBALE;
  m_strTipoDocumento = "Fattura";
  pDoc->m_nSelectedTreeFatture = TREEITEM_FATTUREDAEMETTERE;
  UpdateData(FALSE);
}



void CFattureView::OnNotacreditoNuova() 
{
  CTime data(CTime::GetCurrentTime().GetYear(), 1, 1, 0, 0, 0);
  m_pVerbaliInFatturazione->m_strFilter.Format("Fattura = 0 and DataAccettazione >= '%s'", data.Format("%Y-%m-%d"));
  m_pVerbaliInFatturazione->Requery();
  m_DataEmissione = CTime::GetCurrentTime();
	// Creo un verbale finto di tipo VERB_PER_FATTURA a cui riferire i servizi
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  CVerbaliSet verbaliSet(&pApp->m_db);
  verbaliSet.m_strFilter = "Codice = 0";
  verbaliSet.Open();
  CListiniSet* pListinoSet;
  pApp->LockTable(VERBALI);
  verbaliSet.AddNew();
  verbaliSet.m_TipoVerbale = VERB_PER_NOTACREDITO;
  verbaliSet.m_ProgressivoParziale = 0;
  verbaliSet.m_ProgressivoTotale = 0;
	verbaliSet.m_CodiceAzFattura = 0;
  verbaliSet.m_Cantiere.Empty();
  // Operatore
  verbaliSet.m_Operatore = pApp->GetUserName();
  verbaliSet.m_DataAccettazione = CTime::GetCurrentTime();
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
	verbaliSet.m_ListinoParticolare = 0;
	verbaliSet.m_CertOgniSerie   = 0;
  verbaliSet.m_DataConsegna = 0;
  verbaliSet.m_Urgenza = 0;
  verbaliSet.m_Spedizione = 0;
  verbaliSet.m_LungaScadenza = 0;
  // Metto il verbale in fatturazione
  verbaliSet.m_NumeroFattura = 0;
  verbaliSet.m_InFatturazione = 2;
  // Aggiorno il recordset
  verbaliSet.Update();
  // Sblocco la tabella
  pApp->UnlockTables();
  verbaliSet.m_strFilter.Empty();
  verbaliSet.Close();
  m_pVerbaliInFatturazione->Requery();
  // Carico il record corrente
  LoadCurRecord(FALSE);
  UpdateData(FALSE);
  // Abilito le edit per l'inserimento dei dati dell'azienda
  EnableControls(TRUE);
  m_EditCodiceCliente.SetFocus();
  m_nState = NOTA_DI_CREDITO;
  m_strTipoDocumento = "Nota di credito";
  pDoc->m_nSelectedTreeFatture = TREEITEM_FATTUREDAEMETTERE;
  UpdateData(FALSE);
}


void CFattureView::OnKillfocusEditCodCliente() 
{
  CTrovaAziendaDlg dlg;
  UpdateData();

  if(m_strCodiceCliente.IsEmpty())
  {
	  m_strRagioneSociale.Empty();
    m_strP_IVA.Empty();
  }
	else
  {
		dlg.m_strID = m_strCodiceCliente;
    if((dlg.Find() || dlg.DoModal() == IDOK) && m_pSet->IsOpen())
      GetDatiAzienda(dlg.m_pSet);
    if(dlg.m_pSet->IsOpen())
      dlg.m_pSet->Close();
  }
  UpdateData(FALSE);
}

void CFattureView::OnKillfocusEditRagioneSociale() 
{
  CTrovaAziendaDlg dlg;
  UpdateData();
  if(m_strRagioneSociale.IsEmpty())
  {
	  m_strCodiceCliente.Empty();
    m_strP_IVA.Empty();
  }
	else
  {
		dlg.m_strNome = m_strRagioneSociale;
    if((dlg.Find() || dlg.DoModal() == IDOK) && m_pSet->IsOpen())
      GetDatiAzienda(dlg.m_pSet);
    if(dlg.m_pSet->IsOpen())
      dlg.m_pSet->Close();
  }
  UpdateData(FALSE);
}

void CFattureView::OnKillfocusEditPIva() 
{
  CTrovaAziendaDlg dlg;
  UpdateData();
  if(!m_strP_IVA.IsEmpty())	
  {
    dlg.m_strPartitaIva = m_strP_IVA;
    if((dlg.Find() || dlg.DoModal() == IDOK) && m_pSet->IsOpen())
      GetDatiAzienda(dlg.m_pSet);
    if(dlg.m_pSet->IsOpen())
      dlg.m_pSet->Close();
  }
  UpdateData(FALSE);
}

void CFattureView::GetDatiAzienda(CAziendeSet* pSet)
{
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CVerbaliSet verbaliSet(&pApp->m_db);
  CListiniSet* pListiniSet = ((CWinSigmaDoc*)GetDocument())->m_pListiniInVigoreSet;
  long codice;
  if(m_nState == FATT_SVERBALE)
    verbaliSet.m_strFilter.Format("TipoVerbale = %d AND Fattura = 0 AND IntestatarioFattura = 0 AND InFatturazione = 2", VERB_PER_FATTURA);
  else if(m_nState == NOTA_DI_CREDITO)
    verbaliSet.m_strFilter.Format("TipoVerbale = %d AND Fattura = 0 AND IntestatarioFattura = 0 AND InFatturazione = 2", VERB_PER_NOTACREDITO);
  else
    return;
  m_nState = IDLE;
  verbaliSet.Open();
  codice = verbaliSet.m_Codice;
  verbaliSet.Edit();
	verbaliSet.m_CodiceAzFattura = pSet->m_Codice;
	verbaliSet.m_IDAzFattura = pSet->m_ID;
	verbaliSet.m_NomeAzFattura = pSet->m_RagioneSociale;
  // Verifico se l'azienda ha un listino particolare
  for(SET_START(pListiniSet); !pListiniSet->IsEOF(); pListiniSet->MoveNext())
  {
    if(!pListiniSet->IsFieldNull(&pListiniSet->m_Azienda) && pListiniSet->m_Azienda == pSet->m_Codice)
    {
      verbaliSet.m_ListinoParticolare = pListiniSet->m_Codice;
      break;
    }
  }
  verbaliSet.m_InFatturazione = 0;
	verbaliSet.m_IndirizzoFattura = CVerbaliView::FormatIndirizzo(pSet);
  verbaliSet.Update();
  verbaliSet.Close();
  m_pVerbaliInFatturazione->Requery();
  SINCRONIZE(m_pVerbaliInFatturazione, codice);
  pApp->ReloadTree(TREELABEL_FATTUREDAEMETTERE, m_pVerbaliInFatturazione->m_CodiceAzFattura);
  SINCRONIZE(m_pVerbaliInFatturazione, codice);
  LoadCurRecord(TRUE);
  UpdateData(FALSE);
  // Disabilito le edit
  EnableControls(FALSE);
}


// Verifica che non siano stati selezionati documenti di tipo diverso per l'emissione (una fattura e una nota di credito) e che le date siano coerenti
int CFattureView::VerificaSelezione()
{
  int n, nChecked = 0;
  BOOL bNotaCredito = FALSE;
  
  // Controllo la coerenza delle date
  for(n = 0; n < m_ListVerbali.GetItemCount(); n++)
  {
    // Per prima cosa controllo che non sia stata selezionata una nota di credito
    if(m_ListVerbali.GetCheck(n))
    {
      SINCRONIZE(m_pVerbaliInFatturazione, (long)m_ListVerbali.GetItemData(n));
      if(m_pVerbaliInFatturazione->m_DataAccettazione > m_DataEmissione)
        return VERIFICA_ERR_DATA;
    }
  }
  m_nTipoDocumento = FATTURA;
  for(n = 0; n < m_ListVerbali.GetItemCount(); n++)
  {
    // Per prima cosa controllo che non sia stata selezionata una nota di credito
    if(m_ListVerbali.GetCheck(n))
    {
      nChecked++;
      SINCRONIZE(m_pVerbaliInFatturazione, (long)m_ListVerbali.GetItemData(n));
      if(m_pVerbaliInFatturazione->m_TipoVerbale == VERB_PER_NOTACREDITO)
        bNotaCredito = TRUE;
    }
  }
  // Se non è stata selezionata nessuna nota di credito, restituisco TRUE
  if(!bNotaCredito)
  {
    if(nChecked)
    {
      m_nTipoDocumento = FATTURA;
      m_strTipoDocumento = "Fattura";
    }
    return VERIFICA_OK;
  }
  else
  {
    for(n = 0; n < m_ListVerbali.GetItemCount(); n++)
    {
      // Verifico che non ci siano altri tipi di documento selezionati
      if(m_ListVerbali.GetCheck(n))
      {
        SINCRONIZE(m_pVerbaliInFatturazione, (long)m_ListVerbali.GetItemData(n));
        if(m_pVerbaliInFatturazione->m_TipoVerbale != VERB_PER_NOTACREDITO && bNotaCredito)
          return VERIFICA_ERR_DOC;
      }
    }
    if(nChecked)
    {
      m_nTipoDocumento = NOTA_CREDITO;
      m_strTipoDocumento = "Nota di credito";
    }
  }
  return VERIFICA_OK;
}


void CFattureView::OnStampaeffetti() 
{
	CStampaEffetti stampa_effetti;
	stampa_effetti.DoModal();	
}


void CFattureView::OnButtonAggiorna() 
{
	AggiornaAlbero();
}


void CFattureView::OnSbloccaFattura() 
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	pApp->SetFatturaInUso(m_pFattureEmesseSet, TRUE);
}

void CFattureView::OnSbloccaFatturazione() 
{
	CString str,msg = "ATTENZIONE; le operazioni di emissione fattura possono creare inconsistenza dei dati se eseguite contemporaneamente da più utenti!";
	msg +="\n\nACCERTARSI CHE NON CI SIANO ALTRI OPERATORI CHE EMETTONO FATTURE!";
	msg +="\n\nProcedere con lo sblocco della fatturazione?";
	if( !(IDYES == AfxMessageBox(msg, MB_YESNO)) )
		return;
	CWinSigmaApp*	pApp = (CWinSigmaApp*)AfxGetApp();
	if(!pApp->DisabilitaFatturazione(&str, FALSE))
		AfxMessageBox("La fatturazione non risulta bloccata");	
}

// Toglie un documento dalla fatturazione
void CFattureView::OnDblclkListVerbali(NMHDR* pNMHDR, LRESULT* pResult) 
{
  EliminaDocInFatturazione();
  *pResult = 0;
}

void CFattureView::OnDelInfatturazione() 
{
  EliminaDocInFatturazione();	
}

void CFattureView::EliminaDocInFatturazione(void)
{
  POSITION pos;

  if((pos = m_ListVerbali.GetFirstSelectedItemPosition()) == NULL)
  {
    AfxMessageBox("Selezionare un documento valido.");
    return;
  }
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	int n = m_ListVerbali.GetNextSelectedItem(pos);
  long lCodiceAzienda;

  // Eliminazione di un documento da una fattura emessa
  if(m_lCodiceFattura)
  {
    // Chiedo conferma
    if(AfxMessageBox("Togliere dalla fattura il documento selezionato?", MB_YESNO) == IDNO)
      return;        
    SetCursor(LoadCursor(NULL, IDC_WAIT));
    m_pVerbaliInFatturazione->m_strFilter.Format("Codice = %ld", m_ListVerbali.GetItemData(n));
    m_pVerbaliInFatturazione->Requery();
    // Seleziono i servizi di questo verbale
    m_pServiziErogati->m_strFilter.Format("Verbale = %ld", m_pVerbaliInFatturazione->m_Codice);
    m_pServiziErogati->Requery();
    // Resetto il campo fattura
    for(SET_START(m_pServiziErogati); !m_pServiziErogati->IsEOF(); m_pServiziErogati->MoveNext())
    {
      m_pServiziErogati->Edit();
      m_pServiziErogati->m_Fattura = 0;
      m_pServiziErogati->Update();
    }
    m_pServiziErogati->Requery();
    m_pVerbaliInFatturazione->Edit();
    m_pVerbaliInFatturazione->m_NumeroFattura = 0;
    m_pVerbaliInFatturazione->m_InFatturazione = 0;
    m_pVerbaliInFatturazione->SetFieldNull(&m_pVerbaliInFatturazione->m_DataChiusura);
    m_pVerbaliInFatturazione->Update();
    SINCRONIZE(m_pFattureEmesseSet, m_lCodiceFattura);
    m_pVerbaliInFatturazione->m_strFilter.Format("Fattura = %ld", m_lCodiceFattura);
    m_pVerbaliInFatturazione->Requery();
    LoadServizi();
    pApp->ReloadTree(m_pFattureEmesseSet->m_Data.Format("%Y"), m_lCodiceFattura);
    LoadCurRecord(TRUE);
  }
  else
  {
    // chiedo conferma
    if(AfxMessageBox("Togliere dalla fatturazione il documento selezionato?", MB_YESNO) == IDNO)
      return;
    SetCursor(LoadCursor(NULL, IDC_WAIT));
    // verbale ancora da fatturare
    SINCRONIZE(m_pVerbaliInFatturazione, (long)m_ListVerbali.GetItemData(n));
    lCodiceAzienda = m_pVerbaliInFatturazione->m_CodiceAzFattura;
    // Seleziono i servizi di questo verbale e li elimino
    m_pServiziErogati->m_strFilter.Format("Verbale = %d", m_pVerbaliInFatturazione->m_Codice);
    m_pServiziErogati->Requery();
    for(SET_START(m_pServiziErogati); !m_pServiziErogati->IsEOF(); m_pServiziErogati->MoveNext())
      m_pServiziErogati->Delete();
    if( m_pVerbaliInFatturazione->m_TipoVerbale == VERB_NON_IN_CONCESSIONE	|| 
				m_pVerbaliInFatturazione->m_TipoVerbale == VERB_NC_PROVE_DI_CARICO	||
				m_pVerbaliInFatturazione->m_TipoVerbale == VERB_NC_CONGL_BITUMINOSI	||
				m_pVerbaliInFatturazione->m_TipoVerbale == VERB_NC_INERTI						||
				m_pVerbaliInFatturazione->m_TipoVerbale == VERB_NC_MONITORAGGI			||
				m_pVerbaliInFatturazione->m_TipoVerbale == VERB_NC_VARIE						||
				m_pVerbaliInFatturazione->m_TipoVerbale == VERB_NC_GEOTECNICA				||
				m_pVerbaliInFatturazione->m_TipoVerbale == VERB_IN_CONCESSIONE			|| 
				m_pVerbaliInFatturazione->m_TipoVerbale == VERB_GEOLOGIA)
		{
      m_pVerbaliInFatturazione->Edit();
      m_pVerbaliInFatturazione->SetFieldNull(&m_pVerbaliInFatturazione->m_NumeroFattura);
      m_pVerbaliInFatturazione->SetFieldNull(&m_pVerbaliInFatturazione->m_InFatturazione);
      m_pVerbaliInFatturazione->Update();
    }
    else
      m_pVerbaliInFatturazione->Delete();
    m_pServiziErogati->Requery();
    m_pVerbaliInFatturazione->Requery();
    m_pVerbaliInFatturazione->m_strFilter.Format("Fattura = 0 AND IntestatarioFattura = %d", lCodiceAzienda);
    m_pVerbaliInFatturazione->Requery();
    if(m_pVerbaliInFatturazione->IsEOF())
    {
      // Non ci sono altri documenti da fatturare per questo cliente, lo cancello dall'albero
      CFattureTreeCtrl* pTreeCtrl = &((CMainFrame*)GetParentFrame())->m_wndTreeFatture;
      pTreeCtrl->DeleteItemAzienda(lCodiceAzienda);
    }
    else
    {
      m_pVerbaliInFatturazione->m_strFilter = "Fattura = 0";
      m_pVerbaliInFatturazione->Requery();
      pApp->ReloadTree(TREELABEL_FATTUREDAEMETTERE, lCodiceAzienda);
    }
    CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
    pDoc->m_pVerbaliUltimoMeseSet->Requery();
    pDoc->m_pVerbaliFattProforma->Requery();
    pDoc->m_pVerbaliPrecedentiSet->Requery();
    LoadCurRecord(TRUE);
  }
  UpdateData(FALSE);
}


// Consente l'inserimento di un verbale non ancora fatturato in una fattura già emessa
void CFattureView::OnInsertVerbale() 
{
  CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  if(pDoc->m_nSelectedTreeFatture == TREEITEM_FATTUREDAEMETTERE)
  {
    MessageBeep(-1);
    return;
  }
  long lCodice = m_lCodiceFattura;
	CInsertVerbaliInFatturaDlg dlg;
  dlg.m_lCodiceAzienda = m_pFattureEmesseSet->m_Intestatario;
  dlg.m_lCodiceFattura = m_pFattureEmesseSet->m_Codice;
  if(dlg.DoModal() == IDCANCEL)
    return;
  SetCursor(LoadCursor(NULL, IDC_WAIT));
  m_pFattureEmesseSet->Requery();
  m_lCodiceFattura = lCodice;
  // Aggiorno il record della fattura
  SINCRONIZE(m_pFattureEmesseSet, m_lCodiceFattura);
  m_pVerbaliInFatturazione->m_strFilter.Format("Fattura = 0 AND IntestatarioFattura = %ld", m_pFattureEmesseSet->m_Intestatario);
  m_pVerbaliInFatturazione->Requery();
  if(m_pVerbaliInFatturazione->IsEOF())
  {
    CFattureTreeCtrl* pTreeCtrl = &((CMainFrame*)GetParentFrame())->m_wndTreeFatture;
    pTreeCtrl->DeleteItemAzienda(m_pFattureEmesseSet->m_Intestatario);
  }
  m_pVerbaliInFatturazione->m_strFilter.Format("Fattura = %ld", m_lCodiceFattura);
  m_pVerbaliInFatturazione->Requery();
  LoadServizi();
  ((CWinSigmaApp*)AfxGetApp())->ReloadTree(m_pFattureEmesseSet->m_Data.Format("%Y"), m_lCodiceFattura);  
  LoadCurRecord(TRUE);
  UpdateData(FALSE);
}


void CFattureView::RicalcolaDatiFattura(void)
{
  m_bEnableServiziCheck = FALSE;
  m_pVerbaliInFatturazione->m_strFilter.Format("NumeroFattura = %ld", m_pFattureEmesseSet->m_Codice);
  m_pVerbaliInFatturazione->Requery();
  LoadServizi();
  // Abilito il controllo itemchanging-itemchanged sulla lista dei verbali
  m_bEnableServiziCheck = TRUE;
}

void CFattureView::OnFatturaArchiviaSingolafattura() 
{
  CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  if(pDoc->m_nSelectedTreeFatture == TREEITEM_FATTUREDAEMETTERE || (m_pFattureEmesseSet->IsEOF() || m_pFattureEmesseSet->IsBOF()))	
  {
    MessageBeep(-1);
    return;
  }
  CString str, strApp;
  long codice = m_pFattureEmesseSet->m_Codice;
  strApp = m_strTipoDocumento;
  strApp.MakeLower();
  str.Format("Archiviare la %s n. %d?", strApp, m_pFattureEmesseSet->m_Numero);
  if(AfxMessageBox(str, MB_YESNO) == IDYES)
  {
    str.Format("%s", m_pFattureEmesseSet->m_Data.Format("%Y"));
    CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
    pApp->LockTable(FATTURE);
    m_pFattureEmesseSet->Edit();
    m_pFattureEmesseSet->m_Archiviata = 1;
    m_pFattureEmesseSet->Update();
    pApp->UnlockTables();
    // Ricarico l'albero
    pApp->ReloadTree(str, codice);
    m_pFattureEmesseSet->m_strFilter = "Archiviata = 0";
    m_pFattureEmesseSet->Requery();
    LoadCurRecord(FALSE);
  }
  UpdateData(FALSE);	
}

void CFattureView::OnFatturaArchiviaGruppofatture() 
{
	CArchiviaFattureDlg archivia_fatture;
	if (archivia_fatture.DoModal() == IDOK)
	{
		if (archivia_fatture.m_iDa > archivia_fatture.m_iA) 
		{
			MessageBeep(-1);
			AfxMessageBox("Il numero 'A fattura' deve essere maggiore di 'Da fattura'");
			return;
		}

		UpdateData(FALSE);
		
		CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
		CString str;
		str.Format("Archiviare le fatture dalla n. %d alla n. %d?", archivia_fatture.m_iDa, archivia_fatture.m_iA);
		
		if(AfxMessageBox(str, MB_YESNO) == IDYES)
		{
			CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
				
			CString csFilter("");
			csFilter.Format("(Numero >= %d) AND (Numero <= %d) AND (Archiviata = 0)",archivia_fatture.m_iDa,archivia_fatture.m_iA);
			m_pFattureEmesseSet->m_strFilter = csFilter;
			m_pFattureEmesseSet->Requery();
				
			long codice= 0;
      SetCursor(LoadCursor(NULL, IDC_WAIT));
			while(!m_pFattureEmesseSet->IsEOF())	
			{
				codice = m_pFattureEmesseSet->m_Codice;
				
				m_pFattureEmesseSet->Edit();
				m_pFattureEmesseSet->m_Archiviata = 1;
				m_pFattureEmesseSet->Update();
        str.Format("%s", m_pFattureEmesseSet->m_Data.Format("%Y"));
				pApp->ReloadTree(str, codice);
        if(!m_pFattureEmesseSet->IsEOF())
          m_pFattureEmesseSet->MoveNext();
      }
      
			m_pFattureEmesseSet->m_strFilter = "Archiviata = 0";
			m_pFattureEmesseSet->Requery();   
			LoadCurRecord(FALSE);
			UpdateData(FALSE);
		}
	}	
}

void CFattureView::OnDatetimechangeDatetimepickerDataEmissione(NMHDR* pNMHDR, LRESULT* pResult) 
{
  int n;
  
  UpdateData();
  m_DTCtrlDataEmissione.GetTime(m_DataEmissione);
  for(n = 0; n < m_ListVerbali.GetItemCount(); n++)
  {
    if(m_ListVerbali.GetCheck(n))
    {
      SINCRONIZE(m_pVerbaliInFatturazione, (long)m_ListVerbali.GetItemData(n));
      if(m_pVerbaliInFatturazione->m_TipoVerbale == VERB_PER_NOTACREDITO ||
         m_pVerbaliInFatturazione->m_TipoVerbale == VERB_PER_FATTURA)
      {
        m_pVerbaliInFatturazione->Edit();
        m_pVerbaliInFatturazione->m_DataAccettazione = m_DataEmissione;
        m_pVerbaliInFatturazione->Update();
      }
    }
  }
  m_pVerbaliInFatturazione->Requery();
	*pResult = 0;
}

