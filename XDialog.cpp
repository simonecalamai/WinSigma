// XDialog.cpp : implementation file
//

#include "stdafx.h"
#include "XDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXDialog dialog


CXDialog::CXDialog(UINT nIDTemplate, CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent)
{
	//{{AFX_DATA_INIT(CXDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CXDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXDialog, CDialog)
	//{{AFX_MSG_MAP(CXDialog)
	ON_WM_CTLCOLOR()
//	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXDialog message handlers

BOOL CXDialog::OnCommand(WPARAM wParam, LPARAM lParam) 
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
	return CDialog::OnCommand(wParam, lParam);
}

HBRUSH CXDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
  if(pWnd == GetFocus())
	{
	  pDC->SetBkColor(RGB(0x80, 0xFF, 0x80));
	  return (HBRUSH)GetFocusBkBrush()->m_hObject;
	}
	return hbr;
}


void CXDialog::OnButtonNext() 
{
  CWnd* pWnd = GetFocus();

  NextDlgCtrl();
	pWnd->RedrawWindow();
  pWnd = GetFocus();
	pWnd->RedrawWindow();
}


BOOL CXDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_BrushFocusBk.CreateSolidBrush(RGB(0x80, 0xFF, 0x80));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CBrush* CXDialog::GetFocusBkBrush()
{
	return &m_BrushFocusBk;
}
