// PrintVerbaliView.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "PrintVerbaliView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrintVerbaliView dialog


CPrintVerbaliView::CPrintVerbaliView(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintVerbaliView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrintVerbaliView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPrintVerbaliView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrintVerbaliView)
	DDX_Control(pDX, IDC_STATIC_PREVIEW, m_Static_Preview);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrintVerbaliView, CDialog)
	//{{AFX_MSG_MAP(CPrintVerbaliView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintVerbaliView message handlers

BOOL CPrintVerbaliView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	sss.CreateEx(WS_EX_CLIENTEDGE, // Make a client edge label.
      _T("STATIC"), 
			"Ciao Ciao",
      WS_CHILD | WS_TABSTOP | WS_VISIBLE,
      40, 40, 300, 425, 
			this->m_hWnd, 
			(HMENU)59392);

  //ShowWindow(SW_MAXIMIZE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CPrintVerbaliView::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	bool bIsMax(false);
	//CRect* rect= new CRect(NULL);
	
	if (nType == 2)
	{
		GetWindowRect(m_rect_static_preview);
		bIsMax = true;
	}
	else
	{
		
		GetClientRect(m_rect_static_preview);
		bIsMax = false;
	}

	/*LPRECT lpRectApp;
	lpRectApp = rect;
	if (bIsMax == true)
	{
		lpRectApp->left		+= 15;
		lpRectApp->top		+= 15;
		lpRectApp->right	-= 15;
		lpRectApp->bottom	-= 30;
		m_Static_Preview.MoveWindow(lpRectApp);

		lpRectApp = rect;
		lpRectApp->left		+= 25;
		lpRectApp->top		+= 25;
		lpRectApp->right	-= 25;
		lpRectApp->bottom	-= 40;
		sss.MoveWindow(lpRectApp);
	}
	else
	{
		lpRectApp->left		+= 7;
		lpRectApp->top		+= 7;
		lpRectApp->right	-= 7;
		lpRectApp->bottom	-= 7;
		m_Static_Preview.MoveWindow(lpRectApp);

		
		lpRectApp = rect;
		lpRectApp->left		+= 10;
		lpRectApp->top		+= 10;
		lpRectApp->right	-= 196;
		lpRectApp->bottom	-= 28;
		sss.MoveWindow(lpRectApp);
	}*/
	
	//delete rect;
	
	// TODO: Add your message handler code here
	
}
