// OperatoriView.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "winsigmadoc.h"
#include "XFormView.h"
#include "OperatoriView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COperatoriView

IMPLEMENT_DYNCREATE(COperatoriView, CFormView)

COperatoriView::COperatoriView()
	: CXFormView(IDD)
{
	//{{AFX_DATA_INIT(COperatoriView)
	m_bSospeso = FALSE;
	m_TimeInizio = 0;
	m_TimeFine = CTime::GetCurrentTime();
	m_strCognome = _T("");
	m_strNome = _T("");
	m_strPassword = _T("");
	m_strVerifica = _T("");
	m_strCodice = _T("");
	m_strMacchina = _T("");
	m_bSperimentatore = FALSE;
	m_bResponsabile = FALSE;
	m_strTitoli = _T("");
	m_strSigla = _T("");
	//}}AFX_DATA_INIT
}

COperatoriView::~COperatoriView()
{
}

void COperatoriView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COperatoriView)
	DDX_Control(pDX, IDC_CHECK_INVALIDPICKER, m_ctrlChkInvalidatePicker);
	DDX_Control(pDX, IDC_EDIT_TITOLI, m_EdtTitoli);
	DDX_Control(pDX, IDC_EDIT_SIGLA, m_EdtSigla);
	DDX_Control(pDX, IDC_CHECK_RESPONSABILE, m_BtnResponsabile);
	DDX_Control(pDX, IDC_EDIT_MACCHINA, m_EdtMacchina);
	DDX_Control(pDX, IDC_CHECK_SPERIMENTATORE, m_BtnSperimentatore);
	DDX_Control(pDX, IDC_EDIT_VERIFICA, m_EditVerifica);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_EditPassword);
	DDX_Control(pDX, IDC_EDIT_NOME, m_EditNome);
	DDX_Control(pDX, IDC_EDIT_COGNOME, m_EditCognome);
	DDX_Control(pDX, IDC_DATETIMEPICKER_INIZIO, m_DatePickerInizio);
	DDX_Control(pDX, IDC_DATETIMEPICKER_FINE, m_DatePickerFine);
	DDX_Control(pDX, IDC_CHECK_SOPSESO, m_CheckSospeso);
	DDX_Control(pDX, IDC_COMBO_LIVELLO, m_ComboLivello);
	DDX_Check(pDX, IDC_CHECK_SOPSESO, m_bSospeso);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_INIZIO, m_TimeInizio);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_FINE, m_TimeFine);
	DDX_Text(pDX, IDC_EDIT_COGNOME, m_strCognome);
	DDV_MaxChars(pDX, m_strCognome, 32);
	DDX_Text(pDX, IDC_EDIT_NOME, m_strNome);
	DDV_MaxChars(pDX, m_strNome, 32);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_VERIFICA, m_strVerifica);
	DDX_Text(pDX, IDC_EDIT_CODICE, m_strCodice);
	DDX_Text(pDX, IDC_EDIT_MACCHINA, m_strMacchina);
	DDX_Check(pDX, IDC_CHECK_SPERIMENTATORE, m_bSperimentatore);
	DDX_Check(pDX, IDC_CHECK_RESPONSABILE, m_bResponsabile);
	DDX_Text(pDX, IDC_EDIT_TITOLI, m_strTitoli);
	DDV_MaxChars(pDX, m_strTitoli, 16);
	DDX_Text(pDX, IDC_EDIT_SIGLA, m_strSigla);
	DDV_MaxChars(pDX, m_strSigla, 4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COperatoriView, CXFormView)
	//{{AFX_MSG_MAP(COperatoriView)
	ON_BN_CLICKED(IDC_CHECK_SPERIMENTATORE, OnCheckSperimentatore)
	ON_BN_CLICKED(IDC_CHECK_RESPONSABILE, OnCheckResponsabile)
	ON_COMMAND(ID_BUTTON_AGGIORNA, OnButtonAggiorna)
	ON_BN_CLICKED(IDC_CHECK_INVALIDPICKER, OnCheckInvalidpicker)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COperatoriView diagnostics

#ifdef _DEBUG
void COperatoriView::AssertValid() const
{
	CFormView::AssertValid();
}

void COperatoriView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COperatoriView message handlers

void COperatoriView::OnInitialUpdate() 
{
	int i;
	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
	m_pSet = pDoc->m_pOperatoriSet;
	CXFormView::m_pSet = m_pSet;

	CXFormView::OnInitialUpdate();
	i = m_ComboLivello.AddString("Accettazione");
	m_ComboLivello.SetItemData(i, PRIV_ACCETTAZIONE);
	i = m_ComboLivello.AddString("Certificazione");
	m_ComboLivello.SetItemData(i, PRIV_CERTIFICAZIONE);
	i = m_ComboLivello.AddString("Fatturazione");
	m_ComboLivello.SetItemData(i, PRIV_FATTURAZIONE);
	i = m_ComboLivello.AddString("Amministrazione");
	m_ComboLivello.SetItemData(i, PRIV_AMMINISTRAZIONE);

	m_strMacchina		= "";
  OnUpdate(NULL, 0, NULL);
}

void COperatoriView::LoadCurRecord(BOOL bData)
{
  int i;

  if(bData)
	{
		m_strCodice.Format("OP%d", m_pSet->m_Codice);
		m_strCognome		= m_pSet->m_Cognome;
		m_strNome				= m_pSet->m_Nome;
		m_strPassword		= m_pSet->m_Password;
		m_strVerifica		= m_pSet->m_Password;
		m_strTitoli			= m_pSet->m_Titolo;
		m_strSigla			= m_pSet->m_Sigla;
		m_bResponsabile	= m_pSet->m_Responsabile;

		for(i = 0; i < m_ComboLivello.GetCount(); i++)
		  if(m_ComboLivello.GetItemData(i) == (DWORD)m_pSet->m_Privilegi)
			  break;
		m_TimeInizio				= m_pSet->m_Inizio;
		
    m_bSospeso					= m_pSet->m_Sospeso;
		m_bSperimentatore		= m_pSet->m_Sperimentatore;
		if( m_bSperimentatore )
			m_strMacchina = m_pSet->m_Macchina;
    if (m_pSet->IsFieldNull(&m_pSet->m_Fine))
    {
      m_ctrlChkInvalidatePicker.SetCheck(0);
      m_iEndActChecked = 0;
    }
    else
    {
      m_ctrlChkInvalidatePicker.SetCheck(1);
      m_TimeFine	= m_pSet->m_Fine;
      m_iEndActChecked = 1;
    }
  }
	else
	{
		m_strCodice.Empty();
		m_strCognome.Empty();
		m_strNome.Empty();
		m_strPassword.Empty();
    m_strVerifica.Empty();
		m_strMacchina.Empty();
		m_strTitoli.Empty();
		m_strSigla.Empty();
		m_bResponsabile = FALSE;
		m_bSperimentatore = FALSE;
		m_bSospeso = FALSE;
		m_EdtMacchina.EnableWindow(FALSE);
		for(i = 0; i < m_ComboLivello.GetCount(); i++)
		  if(m_ComboLivello.GetItemData(i) == PRIV_ACCETTAZIONE)
			  break;
		m_TimeInizio = CTime::GetCurrentTime();
		m_TimeFine   = CTime::GetCurrentTime();
    m_ctrlChkInvalidatePicker.SetCheck(0);
  }
  
  if(i < m_ComboLivello.GetCount())
	  m_ComboLivello.SetCurSel(i);
	else
	  m_ComboLivello.SetCurSel(-1);
}

BOOL COperatoriView::IsDataChanged()
{
  int nPriv;

  if((nPriv = m_ComboLivello.GetCurSel()) >= 0)
	  nPriv = m_ComboLivello.GetItemData(nPriv);
  if(m_strCognome					!= m_pSet->m_Cognome
	   ||	m_strNome					!= m_pSet->m_Nome
		 ||	m_strPassword			!= m_pSet->m_Password
		 || nPriv							!= m_pSet->m_Privilegi
		 || m_TimeInizio			!= m_pSet->m_Inizio
		 || ((m_TimeFine			!= m_pSet->m_Fine) && (!m_pSet->IsFieldNull(&m_pSet->m_Fine)))
		 || m_bSospeso				!= m_pSet->m_Sospeso
		 || m_bSperimentatore	!= m_pSet->m_Sperimentatore
		 || m_strMacchina			!= m_pSet->m_Macchina
		 || m_bResponsabile		!= m_pSet->m_Responsabile
		 || m_strTitoli				!= m_pSet->m_Titolo
		 || m_strSigla				!= m_pSet->m_Sigla
     || m_iEndActChecked  != m_ctrlChkInvalidatePicker.GetCheck())
		return TRUE;

  return FALSE;
}

BOOL COperatoriView::ValidateData()
{
  if(m_strCognome.GetLength() < 2)
	{
	  AfxMessageBox("La lunghezza del cognome deve essere di almeno due lettere");
	  return FALSE;
	}
  if(m_strPassword != m_strVerifica)
	{
	  AfxMessageBox("Errore nella digitazione della password");
	  return FALSE;
	}
	if(m_bSperimentatore && m_strMacchina.GetLength() < 1 )
		{
		AfxMessageBox("Per gli sperimentatori è necessario specificare il nome della macchina");
	  return FALSE;
		}
	return TRUE;
}

BOOL COperatoriView::NewRecord()
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  int nPriv;

	if((nPriv = m_ComboLivello.GetCurSel()) >= 0)
	  nPriv = m_ComboLivello.GetItemData(nPriv);
	if(!ValidateData())
	  return FALSE;

	if(m_bResponsabile)
		RimuoviResponsabile();

  if (m_ctrlChkInvalidatePicker.GetCheck() == 0)
  {
    m_TimeFine = CTime::GetCurrentTime();
  }

	m_pSet->AddNew();
	m_pSet->m_Cognome					= m_strCognome;
	m_pSet->m_Nome						= m_strNome;
	m_pSet->m_Password				= m_strPassword;
	m_pSet->m_Privilegi				= nPriv;
	m_pSet->m_Inizio					= m_TimeInizio;
	m_pSet->m_Fine						= m_TimeFine;
	m_pSet->m_Sospeso					= m_bSospeso;
	m_pSet->m_Sperimentatore	= m_BtnSperimentatore.GetCheck();
	m_pSet->m_Macchina				= m_strMacchina;
	m_pSet->m_Titolo					= m_strTitoli;
	m_pSet->m_Sigla						= m_strSigla;
	m_pSet->m_Responsabile		= m_bResponsabile;

	m_pSet->Update();
	pApp->ReloadTree(TREELABEL_OPERATORI, -1);
	return TRUE;
}

BOOL COperatoriView::SaveRecord()
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  int nPriv;

	if((nPriv = m_ComboLivello.GetCurSel()) >= 0)
	  nPriv = m_ComboLivello.GetItemData(nPriv);
	if(!ValidateData())
	  return FALSE;
	
  switch(AfxMessageBox("Salvare le modifiche ai dati?", MB_YESNOCANCEL))
	{
	  case IDYES:

			if(m_bResponsabile)
				RimuoviResponsabile();

  	  m_pSet->Edit();
    	m_pSet->m_Cognome					= m_strCognome;
    	m_pSet->m_Nome						= m_strNome;
    	m_pSet->m_Password				= m_strPassword;
	    m_pSet->m_Privilegi				= nPriv;
			m_pSet->m_Inizio					= m_TimeInizio;

      if (m_ctrlChkInvalidatePicker.GetCheck() == 0)
          m_pSet->SetFieldNull(&m_pSet->m_Fine);
      else
          m_pSet->m_Fine						= m_TimeFine;

			m_pSet->m_Sospeso					= m_bSospeso;
			m_pSet->m_Sperimentatore	= m_BtnSperimentatore.GetCheck();
			m_pSet->m_Macchina				= m_strMacchina;
			m_pSet->m_Titolo					= m_strTitoli;
			m_pSet->m_Sigla				 	  = m_strSigla;
			m_pSet->m_Responsabile		= m_bResponsabile;
	    m_pSet->Update();
	    pApp->ReloadTree(TREELABEL_OPERATORI, m_pSet->m_Codice);
		  break;
		case IDNO:
		  break;
		default:
		  return FALSE;
	}
	return TRUE;
}

BOOL COperatoriView::DeleteRecord()
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CString str;

  if(!m_pSet->IsBOF())
	{
		str.Format("Eliminare l'operatore %s %s (Codice %s)?",
							 m_strNome, m_strCognome, m_strCodice);

		if(AfxMessageBox(str, MB_YESNO) == IDYES)
		{
			m_pSet->Delete();
	    pApp->ReloadTree(TREELABEL_OPERATORI, -1);
  	return TRUE;
		}
    return FALSE;
	}
	return FALSE;
}

void COperatoriView::EnableControls(BOOL bEditMode)
{
	m_EditVerifica.EnableWindow(bEditMode);
	m_EditPassword.EnableWindow(bEditMode);
	m_EditNome.EnableWindow(bEditMode);
	m_EditCognome.EnableWindow(bEditMode);
	m_DatePickerInizio.EnableWindow(bEditMode);
  if ((bEditMode == TRUE) && (m_ctrlChkInvalidatePicker.GetCheck() == 1))
    m_DatePickerFine.EnableWindow(TRUE);
  else
    m_DatePickerFine.EnableWindow(FALSE);

	m_CheckSospeso.EnableWindow(bEditMode);
	m_ComboLivello.EnableWindow(bEditMode);
	m_BtnSperimentatore.EnableWindow(bEditMode);
	m_EdtTitoli.EnableWindow(bEditMode);
	m_EdtSigla.EnableWindow(bEditMode);
	m_BtnResponsabile.EnableWindow(bEditMode);
  m_ctrlChkInvalidatePicker.EnableWindow(bEditMode);
	if( m_bSperimentatore )
		m_EdtMacchina.EnableWindow(bEditMode);
	m_EditNome.SetFocus();
}


void COperatoriView::OnCheckSperimentatore() 
{
	m_EdtMacchina.EnableWindow( m_BtnSperimentatore.GetCheck() );
}


/////////////////////////////
// Messaggio di avvertimento

void COperatoriView::OnCheckResponsabile() 
{
	UpdateData();
	if( m_bResponsabile && 
		AfxMessageBox("L'inserimento di un responsabile del laboratorio sostituisce l'eventuale responsabile precedentemente selezionato.\n\nCONFERMI L'OPERAZIONE?", MB_YESNO) != IDYES )
		m_bResponsabile = FALSE;
	UpdateData(FALSE);
}



void COperatoriView::RimuoviResponsabile()
{
	long attuale = 0;
	if( !m_pSet->IsFieldNull(&m_pSet->m_Codice) )
		attuale = m_pSet->m_Codice;
	
	for( SET_START(m_pSet); !m_pSet->IsEOF(); m_pSet->MoveNext() )
		{
		
		if( m_pSet->m_Responsabile )
			{
			m_pSet->Edit();
			m_pSet->m_Nome;
			m_pSet->m_Responsabile = 0;
			m_pSet->Update();
			break;
			}
		}

	// Eventuale risincronizzazione dell'operatore con quello di partenza della funzione
	for(SET_START(m_pSet); !m_pSet->IsEOF(); m_pSet->MoveNext() )
		if( attuale == m_pSet->m_Codice)
			break;
}


void COperatoriView::OnButtonAggiorna() 
{
	CWinSigmaApp* pApp	= (CWinSigmaApp*)AfxGetApp();
	
  if( MODE_VIEW != pApp->GetViewMode())
		return;
	long nOperatore = m_pSet->m_Codice;
	
  pApp->ReloadTree(TREELABEL_OPERATORI, nOperatore);
}

void COperatoriView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CXFormView::OnUpdate(pSender, lHint, pHint);
}

void COperatoriView::OnCheckInvalidpicker() 
{
  if (m_DatePickerFine.IsWindowEnabled())
    m_DatePickerFine.EnableWindow(FALSE);
  else
    m_DatePickerFine.EnableWindow(TRUE);
	
}
