// ArchiviaFattureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "ArchiviaFattureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArchiviaFattureDlg dialog


CArchiviaFattureDlg::CArchiviaFattureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CArchiviaFattureDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CArchiviaFattureDlg)
	m_iA = 0;
	m_iDa = 0;
	//}}AFX_DATA_INIT
}


void CArchiviaFattureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArchiviaFattureDlg)
	DDX_Text(pDX, IDC_EDIT_A_FATTURA, m_iA);
	DDX_Text(pDX, IDC_EDIT_DA_FATTURA, m_iDa);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArchiviaFattureDlg, CDialog)
	//{{AFX_MSG_MAP(CArchiviaFattureDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArchiviaFattureDlg message handlers
