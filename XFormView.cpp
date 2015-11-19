// XFormView.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "winsigmadoc.h"
#include "mainfrm.h"
#include "XFormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXFormView


CXFormView::CXFormView(int nID)
	: CFormView(nID)
{
	//{{AFX_DATA_INIT(CXFormView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pSet = NULL;
}

CXFormView::~CXFormView()
{
}

void CXFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXFormView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXFormView, CFormView)
	//{{AFX_MSG_MAP(CXFormView)
	ON_COMMAND(ID_NUOVO, OnNuovo)
	ON_COMMAND(ID_MODIFICA, OnModifica)
	ON_COMMAND(ID_ELIMINA, OnElimina)
	ON_COMMAND(IDOK, OnOK)
	ON_COMMAND(IDCANCEL, OnCancel)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CXFormView diagnostics

#ifdef _DEBUG
void CXFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CXFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXFormView message handlers

void CXFormView::OnInitialUpdate() 
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CRuntimeClass* pRuntimeClass;

	CFormView::OnInitialUpdate();
  for(CWnd* pWnd = GetWindow(GW_CHILD); pWnd; pWnd = pWnd->GetNextWindow())
	{
    pRuntimeClass = pWnd->GetRuntimeClass();
    if(!strcmp(pRuntimeClass->m_lpszClassName, "CEdit"))
      pWnd->SetFont(pApp->GetCtrlFont());
    if(!strcmp(pRuntimeClass->m_lpszClassName, "CComboBox"))
      pWnd->SetFont(pApp->GetCtrlFont());
    if(!strcmp(pRuntimeClass->m_lpszClassName, "CListCtrl"))
      pWnd->SetFont(pApp->GetCtrlFont());
    if(!strcmp(pRuntimeClass->m_lpszClassName, "CButton"))
      pWnd->SetFont(pApp->GetCtrlFont());
  }
	EnableToolTips(TRUE);	
  EnableControls(FALSE);
}

void CXFormView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if(m_pSet)
	{ 
		if(!m_pSet->IsBOF())
		{
			LoadCurRecord(TRUE);
		}
		else
			LoadCurRecord(FALSE);
	}
	UpdateData(FALSE);
}

BOOL CXFormView::OnCommand(WPARAM wParam, LPARAM lParam) 
{
  static CWnd* pFocus;
  UINT notificationCode = (UINT) HIWORD(wParam);

  if((notificationCode == EN_SETFOCUS)  ||
     (notificationCode == LBN_SETFOCUS) ||
     (notificationCode == CBN_SETFOCUS) ||
     (notificationCode == NM_SETFOCUS)  ||
     (notificationCode == WM_SETFOCUS)) 
	{
	  pFocus = GetFocus();

		if(pFocus &&(pFocus->GetParent() == this))
		{
			RedrawWindow();
		}       
	}	
	return CFormView::OnCommand(wParam, lParam);
}



void CXFormView::OnNuovo() 
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
	        pApp->SetViewMode(MODE_VIEW);
 	        EnableControls(FALSE);
					break;
				default:
					break;
			}
      break;
	}
}

void CXFormView::OnModifica() 
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();

  if(!m_pSet->IsBOF())
	{
		switch(pApp->GetViewMode())
		{
			case MODE_VIEW:
				pApp->SetViewMode(MODE_EDIT);
  			EnableControls(TRUE);
				break;
			case MODE_EDIT:
				UpdateData();
				if(!IsDataChanged() || SaveRecord())
				{
					pApp->SetViewMode(MODE_VIEW);
 					EnableControls(FALSE);
				}
				break;
			case MODE_NEW:
				MessageBeep(-1);
				break;
		}
  }
	else
		MessageBeep(-1);
}


void CXFormView::OnElimina() 
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();

  switch(pApp->GetViewMode())
	{
	  case MODE_VIEW:
      if(!DeleteRecord())
        LoadCurRecord(TRUE);
      else
			  LoadCurRecord(FALSE);
			UpdateData(FALSE);
			break;
		case MODE_EDIT:
		  MessageBeep(-1);
			break;
		case MODE_NEW:
		  MessageBeep(-1);
      break;
	}

}

void CXFormView::OnCancel() 
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

  switch(pApp->GetViewMode())
	{
		case MODE_EDIT:
		  OnModifica();
			break;
		case MODE_NEW:
		  OnNuovo();
      break;
	}
}

void CXFormView::OnOK() 
{
  GetNextDlgTabItem(GetFocus())->SetFocus();
}

BOOL CXFormView::OnToolTipNotify(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
{
  UINT    n, nID = pNMHDR->idFrom;
  CString cs;
  CMainFrame* pMainFrame = (CMainFrame*)GetParentFrame();
  TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
  
  if(nID)
	{
 		cs = GetToolTip(nID);
		n = cs.Find('\n');
		pMainFrame->StatusBarMessage(cs.Left(n));
		if(cs.GetLength())
		{
      strcpy(pTTT->lpszText, (LPCSTR)cs.Mid(n + 1));
      pTTT->hinst = NULL;
      return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}

CString CXFormView::GetToolTip(int nID)
{
  return "";
}


HBRUSH CXFormView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
/*	
  if(pWnd == GetFocus())
	{
	  pDC->SetBkColor(RGB(0x80, 0xFF, 0x80));
	  return (HBRUSH)pApp->GetFocusBkBrush()->m_hObject;
	}
*/
	return hbr;
}
