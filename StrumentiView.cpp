// StrumentiView.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "StrumentiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStrumentiView

IMPLEMENT_DYNCREATE(CStrumentiView, CFormView)

CStrumentiView::CStrumentiView()
	: CFormView(CStrumentiView::IDD)
{
	//{{AFX_DATA_INIT(CStrumentiView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CStrumentiView::~CStrumentiView()
{
}

void CStrumentiView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStrumentiView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStrumentiView, CFormView)
	//{{AFX_MSG_MAP(CStrumentiView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStrumentiView diagnostics

#ifdef _DEBUG
void CStrumentiView::AssertValid() const
{
	CFormView::AssertValid();
}

void CStrumentiView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStrumentiView message handlers
