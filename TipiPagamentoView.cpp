// TipiPagamentoView.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "winsigmadoc.h"
#include "XFormView.h"
#include "TipiPagamentoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTipiPagamentoView

IMPLEMENT_DYNCREATE(CTipiPagamentoView, CFormView)

CTipiPagamentoView::CTipiPagamentoView()
	: CXFormView(CTipiPagamentoView::IDD)
{
	//{{AFX_DATA_INIT(CTipiPagamentoView)
	m_strDescrizione = _T("");
	m_strNome = _T("");
	m_strCodice = _T("");
	m_nNumero_Rate = 1;
	m_nPrima_Scadenza = 0;
	m_strABI = _T("");
	m_strBanca = _T("");
	m_strCAB = _T("");
	m_strContoCorrente = _T("");
	m_strCIN = _T("");
	m_iCodiceGest = 0;
	m_bBonifico = FALSE;
	m_bRIBA = FALSE;
	//}}AFX_DATA_INIT
}

CTipiPagamentoView::~CTipiPagamentoView()
{
}

void CTipiPagamentoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTipiPagamentoView)
	DDX_Control(pDX, IDC_EDIT_CODICE_GEST, m_EditCodiceGest);
	DDX_Control(pDX, IDC_EDIT_CIN, m_EditCIN);
	DDX_Control(pDX, IDC_EDIT_CC, m_EditCC);
	DDX_Control(pDX, IDC_EDIT_CAB, m_EditCAB);
	DDX_Control(pDX, IDC_EDIT_BANCA, m_EditBanca);
	DDX_Control(pDX, IDC_EDIT_ABI, m_EditABI);
	DDX_Control(pDX, IDC_COMBO_ALLINEAMENTO, m_ComboAllineamento);
	DDX_Control(pDX, IDC_EDIT_PRIMA_SCADENZA, m_Prima_Scadenza);
	DDX_Control(pDX, IDC_EDIT_NUMERO_RATE, m_Numero_Rate);
	DDX_Control(pDX, IDC_EDIT_NOME, m_EditNome);
	DDX_Control(pDX, IDC_EDIT_DESCRIZIONE, m_EditDescrizione);
	DDX_Control(pDX, IDC_EDIT_CODICE, m_EditCodice);
	DDX_Text(pDX, IDC_EDIT_DESCRIZIONE, m_strDescrizione);
	DDV_MaxChars(pDX, m_strDescrizione, 250);
	DDX_Text(pDX, IDC_EDIT_NOME, m_strNome);
	DDV_MaxChars(pDX, m_strNome, 32);
	DDX_Text(pDX, IDC_EDIT_CODICE, m_strCodice);
	DDX_Text(pDX, IDC_EDIT_NUMERO_RATE, m_nNumero_Rate);
	DDX_Text(pDX, IDC_EDIT_PRIMA_SCADENZA, m_nPrima_Scadenza);
	DDX_Text(pDX, IDC_EDIT_ABI, m_strABI);
	DDV_MaxChars(pDX, m_strABI, 8);
	DDX_Text(pDX, IDC_EDIT_BANCA, m_strBanca);
	DDV_MaxChars(pDX, m_strBanca, 64);
	DDX_Text(pDX, IDC_EDIT_CAB, m_strCAB);
	DDV_MaxChars(pDX, m_strCAB, 8);
	DDX_Text(pDX, IDC_EDIT_CC, m_strContoCorrente);
	DDV_MaxChars(pDX, m_strContoCorrente, 32);
	DDX_Text(pDX, IDC_EDIT_CIN, m_strCIN);
	DDV_MaxChars(pDX, m_strCIN, 8);
	DDX_Text(pDX, IDC_EDIT_CODICE_GEST, m_iCodiceGest);
	DDV_MinMaxInt(pDX, m_iCodiceGest, 0, 1000);
	DDX_Check(pDX, IDC_CHECK_BONIFICO, m_bBonifico);
	DDX_Check(pDX, IDC_CHECK_RIBA, m_bRIBA);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTipiPagamentoView, CXFormView)
	//{{AFX_MSG_MAP(CTipiPagamentoView)
	ON_COMMAND(ID_BUTTON_AGGIORNA, OnButtonAggiorna)
	ON_BN_CLICKED(IDC_CHECK_RIBA, OnCheckRiba)
	ON_BN_CLICKED(IDC_CHECK_BONIFICO, OnCheckBonifico)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CTipiPagamentoView::LoadCurRecord(BOOL bData)
{
  int i;

  m_ComboAllineamento.Clear();

	i = m_ComboAllineamento.AddString("Fine mese");
	m_ComboAllineamento.SetItemData(i, eScadFineMese);
	i = m_ComboAllineamento.AddString("Fine mese + 5 gg");
	m_ComboAllineamento.SetItemData(i, eScad5Giorni);
	i = m_ComboAllineamento.AddString("Fine mese + 10 gg");
	m_ComboAllineamento.SetItemData(i, eScad10Giorni);
	i = m_ComboAllineamento.AddString("Fine mese + 15 gg");
	m_ComboAllineamento.SetItemData(i, eScad15Giorni);
	i = m_ComboAllineamento.AddString("Fine mese + 20 gg");
	m_ComboAllineamento.SetItemData(i, eScad20Giorni);
  i = m_ComboAllineamento.AddString("Data fattura");
	m_ComboAllineamento.SetItemData(i, eScadDataFattura);

  if(bData)
	{
		m_strCodice.Format("PAG%d", m_pSet->m_Codice);
		m_strNome     = m_pSet->m_Nome;
		m_strDescrizione = m_pSet->m_Descrizione;

		if(m_pSet->IsFieldNull(&m_pSet->m_VecchioCod))
			m_iCodiceGest = 0;
		else
			m_iCodiceGest = m_pSet->m_VecchioCod;

    m_strBanca = m_pSet->m_Banca;
    m_strCAB = m_pSet->m_CAB;
    m_strABI = m_pSet->m_ABI;
    m_strCIN = m_pSet->m_CIN;
    m_strContoCorrente = m_pSet->m_NumeroConto;
		// determinazione RiBa/Bonifico e allineamento
		int nAllineamento = m_pSet->m_Allineamento;
		if(nAllineamento >= eScadRIBAFineMese)
		{
			nAllineamento -= eScadRIBAFineMese;
			m_bRIBA = TRUE;
		}
		else if(nAllineamento >= eScadBonFineMese)
		{
			nAllineamento -= eScadBonFineMese;
			m_bBonifico = TRUE;
		}
		else
		{
			m_bBonifico = FALSE;
			m_bRIBA = FALSE;
		}
		for(i = 0; i < m_ComboAllineamento.GetCount(); i++)
		{
		  if(m_ComboAllineamento.GetItemData(i) == (DWORD)nAllineamento)
			{
        m_ComboAllineamento.SetCurSel(i);
				break;
      }
		}
		m_nNumero_Rate=m_pSet->m_NumRate;
		m_nPrima_Scadenza=m_pSet->m_GiorniPrimaScad;
		UpdateData(FALSE);
  }
	else
	{
		m_strCodice.Empty();
		m_strNome.Empty();
		m_strDescrizione.Empty();
    m_strBanca.Empty();
    m_strABI.Empty();
    m_strCAB.Empty();
    m_strCIN.Empty();
    m_strContoCorrente.Empty();
		m_ComboAllineamento.SetCurSel(0);
		m_nPrima_Scadenza = 0;
		m_nNumero_Rate = 1;
		m_bBonifico = FALSE;
		m_bRIBA = FALSE;
  }
}

BOOL CTipiPagamentoView::IsDataChanged()
{
  int nAllineamento = eScadFineMese, nsel = m_ComboAllineamento.GetCurSel();

	if(nsel >= 0)
	  nAllineamento = m_ComboAllineamento.GetItemData(nsel);

	UpdateData(TRUE);
	if(m_bBonifico) nAllineamento += eScadBonFineMese;
	if(m_bRIBA)	nAllineamento += eScadRIBAFineMese;

  if(m_strNome						!= m_pSet->m_Nome             ||
		 m_strDescrizione   	!= m_pSet->m_Descrizione      ||
		 nAllineamento				!= m_pSet->m_Allineamento			||
     m_nNumero_Rate		    != m_pSet->m_NumRate          ||
		 m_nPrima_Scadenza  	!= m_pSet->m_GiorniPrimaScad  ||
     m_strBanca           != m_pSet->m_Banca            ||
     m_strABI             != m_pSet->m_ABI              ||
     m_strCIN             != m_pSet->m_CIN              ||
		 m_iCodiceGest        != m_pSet->m_VecchioCod       ||
     m_strCAB             != m_pSet->m_CAB)
	{
		return TRUE;
	}
  return FALSE;
}

BOOL CTipiPagamentoView::ValidateData()
{
	UpdateData(TRUE);
  if(m_strNome.GetLength() < 2)
	{
	  AfxMessageBox("La lunghezza del nome deve essere di almeno due lettere");
	  return FALSE;
	}
#if 0
	if(m_bRiBa && m_nPrima_Scadenza < 5)
	{
	  AfxMessageBox("La presentazione delle ricevute bancarie richiede almeno 5 giorni");
	  return FALSE;
	}
	if(((m_ComboAllineamento.GetCurSel() < 0)&&(m_CheckRiBa.GetCheck() != 0)) 
    || (((m_ComboAllineamento.GetCurSel() < 0)&&(m_CheckBonifico.GetCheck() != 0))))
	{
	  AfxMessageBox("Deve essere selezionato un 'Arrotondamento scadenza'");
	  return FALSE;
	}
	if(((m_nNumero_Rate == 0)&&(m_CheckRiBa.GetCheck() != 0)) 
    || ((m_nNumero_Rate == 0)&&(m_CheckBonifico.GetCheck() != 0)))
	{
	  AfxMessageBox("Deve essere inserito un numero di rate valido");
	  return FALSE;
	}
#endif
	return TRUE;
}

BOOL CTipiPagamentoView::NewRecord()
{
	UpdateData(TRUE);
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	int nAllineamento = eScadFineMese;
  int nsel = m_ComboAllineamento.GetCurSel();
	if(nsel >= 0)
	  nAllineamento = m_ComboAllineamento.GetItemData(nsel);

	if(m_bBonifico) nAllineamento += eScadBonFineMese;
	if(m_bRIBA) nAllineamento += eScadRIBAFineMese;
  if(!ValidateData())
	  return FALSE;

	m_pSet->AddNew();
	m_pSet->m_Nome						= m_strNome;
	m_pSet->m_Descrizione			= m_strDescrizione;
	m_pSet->m_VecchioCod			= m_iCodiceGest;
  m_pSet->m_Banca           = m_strBanca;
  m_pSet->m_ABI             = m_strABI;
  m_pSet->m_CAB             = m_strCAB;
  m_pSet->m_CIN             = m_strCIN;
  m_pSet->m_NumeroConto     = m_strContoCorrente;	
	m_pSet->m_Allineamento		= nAllineamento;
  m_pSet->m_GiorniPrimaScad	= m_nPrima_Scadenza;
	m_pSet->m_NumRate					= m_nNumero_Rate;
  TRY
  {
	  m_pSet->Update();
  }
  CATCH(CDBException, e)
  {
		AfxMessageBox(e->m_strError);
	}
  END_CATCH
	pApp->ReloadTree(TREELABEL_PAGAMENTI, -1);
	return TRUE;
}

BOOL CTipiPagamentoView::SaveRecord()
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	int nAllineamento = eScadFineMese;
  int nsel = m_ComboAllineamento.GetCurSel();
	if(nsel >= 0)
	  nAllineamento = m_ComboAllineamento.GetItemData(nsel);

  if(!ValidateData())
	  return FALSE;
  
  switch(AfxMessageBox("Salvare le modifiche ai dati?", MB_YESNOCANCEL))
	{
	  case IDYES:
  	  m_pSet->Edit();
			m_pSet->m_Nome						= m_strNome;
			m_pSet->m_Descrizione			= m_strDescrizione;
			m_pSet->m_VecchioCod			= m_iCodiceGest;
      m_pSet->m_Banca						= m_strBanca;
      m_pSet->m_ABI							= m_strABI;
      m_pSet->m_CAB							= m_strCAB;
      m_pSet->m_CIN             = m_strCIN;
      m_pSet->m_NumeroConto     = m_strContoCorrente;			
			if(m_bBonifico) nAllineamento += eScadBonFineMese;
			else if(m_bRIBA) nAllineamento += eScadRIBAFineMese;
			m_pSet->m_Allineamento		= nAllineamento;
			m_pSet->m_GiorniPrimaScad = m_nPrima_Scadenza;
			m_pSet->m_NumRate					= m_nNumero_Rate;
	    m_pSet->Update();
	    pApp->ReloadTree(TREELABEL_PAGAMENTI, m_pSet->m_Codice);
		  break;
		case IDNO:
		  break;
		default:
		  return FALSE;
	}

  UpdateData(FALSE);

	return TRUE;
}

BOOL CTipiPagamentoView::DeleteRecord()
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CString str;

  if(!m_pSet->IsBOF())
	{
		str.Format("Eliminare il tipo di pagamento %s (Codice %s)?",
							 m_strNome, m_strCodice);

		if(AfxMessageBox(str, MB_YESNO) == IDYES)
		{
			m_pSet->Delete();
	    pApp->ReloadTree(TREELABEL_PAGAMENTI, -1);
    	return TRUE;
		}
    return FALSE;
	}
	return FALSE;
}

void CTipiPagamentoView::EnableControls(BOOL bEditMode)
{
	m_EditNome.EnableWindow(bEditMode);
	m_EditDescrizione.EnableWindow(bEditMode);
  m_EditBanca.EnableWindow(bEditMode);
  m_EditABI.EnableWindow(bEditMode);
  m_EditCAB.EnableWindow(bEditMode);
  m_EditCIN.EnableWindow(bEditMode);
  m_EditCC.EnableWindow(bEditMode);
	m_EditCodiceGest.EnableWindow(bEditMode);
	m_ComboAllineamento.EnableWindow(bEditMode);
	m_Prima_Scadenza.EnableWindow(bEditMode);
	m_Numero_Rate.EnableWindow(bEditMode);
	((CButton*)GetDlgItem(IDC_CHECK_BONIFICO))->EnableWindow(bEditMode);
	((CButton*)GetDlgItem(IDC_CHECK_RIBA))->EnableWindow(bEditMode);
	m_EditNome.SetFocus();
}

/////////////////////////////////////////////////////////////////////////////
// CTipiPagamentoView diagnostics

#ifdef _DEBUG
void CTipiPagamentoView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTipiPagamentoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTipiPagamentoView message handlers


void CTipiPagamentoView::OnInitialUpdate() 
{
	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
	m_pSet = pDoc->m_pTipiPagamentoSet;
	CXFormView::m_pSet = m_pSet;

	CXFormView::OnInitialUpdate();
}


void CTipiPagamentoView::OnButtonAggiorna() 
{
	CWinSigmaApp* pApp	= (CWinSigmaApp*)AfxGetApp();
	if( MODE_VIEW != pApp->GetViewMode())
		return;
	long nCurSel = m_pSet->m_Codice;
	pApp->ReloadTree(TREELABEL_PAGAMENTI, nCurSel);
}


void CTipiPagamentoView::OnCheckRiba() 
{
	UpdateData(TRUE);
	if(m_bRIBA == TRUE && m_bBonifico == TRUE)
	{
		m_bBonifico = FALSE;
		UpdateData(FALSE);
	}	
}

void CTipiPagamentoView::OnCheckBonifico() 
{
	UpdateData(TRUE);
	if(m_bRIBA == TRUE && m_bBonifico == TRUE)
	{
		m_bRIBA = FALSE;
		UpdateData(FALSE);
	}	
}
