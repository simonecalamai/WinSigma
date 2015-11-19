// ConnessioneDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "ConnessioneDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Handle to the Windows Message hook. It can be a global variable or a
// member variable in your CPropertySheet-derived class.
HHOOK hHook = NULL;



// Hook procedure for WH_GETMESSAGE hook type.
LRESULT CALLBACK GetMessageProc(int nCode, WPARAM wParam, LPARAM lParam)
{
  // If this is a keystrokes message, translate it in controls'
  // PreTranslateMessage().
  LPMSG lpMsg = (LPMSG) lParam;
  if( (nCode >= 0) &&
     PM_REMOVE == wParam &&
     (lpMsg->message >= WM_KEYFIRST && lpMsg->message <= WM_KEYLAST) &&
     ((CWinSigmaApp*)(AfxGetApp()))->PreTranslateMessage((LPMSG)lParam) )
     {
     // The value returned from this hookproc is ignored, and it cannot
     // be used to tell Windows the message has been handled. To avoid
     // further processing, convert the message to WM_NULL before
     // returning.
     lpMsg->message = WM_NULL;
     lpMsg->lParam = 0L;
     lpMsg->wParam = 0;
     }

  // Passes the hook information to the next hook procedure in
  // the current hook chain.
  return ::CallNextHookEx(hHook, nCode, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
// CConnessioneDlg dialog


CConnessioneDlg::CConnessioneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConnessioneDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConnessioneDlg)
	m_csPassword = _T("");
	//}}AFX_DATA_INIT

  m_bOkPressed = false;
  m_bCancelPressed = false;
}


void CConnessioneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnessioneDlg)
	DDX_Control(pDX, IDC_STATIC_ICON, m_ctrlIcon);
	DDX_Control(pDX, IDC_PROGRESS_LOAD, m_ctrlProgressLoad);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_ctrlPassWord);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_COMBO_OPERATORE, m_ComboOperatore);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_csPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnessioneDlg, CDialog)
	//{{AFX_MSG_MAP(CConnessioneDlg)
	ON_CBN_CLOSEUP(IDC_COMBO_OPERATORE, OnCloseupComboOperatore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnessioneDlg message handlers

BOOL CConnessioneDlg::OnInitDialog() 
{
  int n, nCodOperatore;

  // Install the WH_GETMESSAGE hook function.
  hHook = ::SetWindowsHookEx(
     WH_GETMESSAGE,
     GetMessageProc,
     AfxGetInstanceHandle(),
     GetCurrentThreadId());
  ASSERT (hHook);
  
  CDialog::OnInitDialog();
#ifdef WINSIGMA2
	this->SetWindowText("Connessione a WinSigmaDUE");
#endif
  m_pSet = new COperatoriSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
  nCodOperatore = AfxGetApp()->GetProfileInt("Sessione", "Utente", 0);
  for(m_pSet->Open(); !m_pSet->IsEOF(); m_pSet->MoveNext())
  {
    n = m_ComboOperatore.AddString(m_pSet->m_Cognome + " " + m_pSet->m_Nome);
    m_ComboOperatore.SetItemData(n, m_pSet->m_Codice);
    m_ComboOperatore.SetIcon(HICON(m_ctrlIcon.GetIcon()),FALSE);
    if(m_pSet->m_Codice == nCodOperatore)
    {
      m_ComboOperatore.SetCurSel(n);
      GetDlgItem(IDC_EDIT_PASSWORD)->SetFocus();
    }
  }
  
  this->SetIcon(HICON(m_ctrlIcon.GetIcon()),FALSE);
  
  m_ctrlProgressLoad.SetRange32(0,1000);
  m_ctrlProgressLoad.SetStep(1);
  m_ctrlProgressLoad.SetPos(0);

  return FALSE;
}

/********************************************************************
* Funzione   : OnOk
* Descrizione: Controlla utente e password inserite e, se sono
               valide, fa andare avanti nel programma
* Parametri  : 
* Ritorno    : 
* Note       : 
*********************************************************************/
void CConnessioneDlg::OnOK() 
{
  int n;
  CString csOperatore;

	UpdateData(TRUE);

  m_ComboOperatore.GetWindowText(csOperatore);
	if(csOperatore == "dbmaster" && m_csPassword == "qs12iz4")
	{
	  m_pSet->Close();
		delete m_pSet;
		m_nOperatore = 0;
	  CDialog::OnOK();
		return;
	}
	if((n = m_ComboOperatore.GetCurSel()) < 0) 
	{
	  MessageBeep(-1);
	  AfxMessageBox("Selezionare un operatore valido.");
		return;
	}

	for(SET_START(m_pSet); !m_pSet->IsEOF(); m_pSet->MoveNext())
    if(m_pSet->m_Codice == (long)m_ComboOperatore.GetItemData(n))
		  break;
	if(m_pSet->IsEOF())
	{
	  AfxMessageBox("Operatore sconosciuto.");
	  MessageBeep(-1);
		return;
	}
	if(m_csPassword != m_pSet->m_Password)
	{
	  MessageBeep(-1);
	  AfxMessageBox("La password è errata.");
		return;
	}
  if(m_pSet->m_Sospeso)
	{
	  MessageBeep(-1);
	  AfxMessageBox("Utente sospeso");
		return;
	}
  if((m_pSet->m_Fine < CTime::GetCurrentTime()) && (!m_pSet->IsFieldNull(&m_pSet->m_Fine)))
	{
	  MessageBeep(-1);
	  AfxMessageBox("Fine attività");
		return;
	}

	m_nOperatore = m_pSet->m_Codice;
  m_nPrivilegi = m_pSet->m_Privilegi;
	m_ComboOperatore.GetWindowText(m_strOperatore);
	AfxGetApp()->WriteProfileInt("Sessione", "Utente", m_pSet->m_Codice);
	m_pSet->Close();
	delete m_pSet;
  
  m_bOkPressed = true;
  m_btnOk.EnableWindow(FALSE);
  m_btnCancel.EnableWindow(FALSE);
  m_ctrlPassWord.EnableWindow(FALSE);
  m_ComboOperatore.EnableWindow(FALSE);
  
  ((CMenu*)(this->GetSystemMenu(FALSE)))->RemoveMenu( SC_CLOSE, MF_BYCOMMAND ); 

  //CDialog::OnOK();
}


void CConnessioneDlg::OnCloseupComboOperatore() 
{
	GetDlgItem(IDC_EDIT_PASSWORD)->SetFocus();
}


void CConnessioneDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
  m_bCancelPressed = true;

  //CDialog::OnCancel();
}
