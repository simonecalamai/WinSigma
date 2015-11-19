// StampaEtichette.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "StampaEtichette.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStampaEtichette dialog


CStampaEtichette::CStampaEtichette(CWnd* pParent /*=NULL*/)
	: CDialog(CStampaEtichette::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStampaEtichette)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStampaEtichette::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStampaEtichette)
	DDX_Control(pDX, IDC_LIST_ETICHETTE, m_lstEtichette);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStampaEtichette, CDialog)
	//{{AFX_MSG_MAP(CStampaEtichette)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStampaEtichette message handlers

BOOL CStampaEtichette::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	unsigned long style = m_lstEtichette.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES;
	m_lstEtichette.SetExtendedStyle(style);

	m_lstEtichette.InsertColumn(0,"R.B.",LVCFMT_CENTER, 50, -1);
	m_lstEtichette.InsertColumn(1,"Importo",LVCFMT_CENTER, 100, -1);
	m_lstEtichette.InsertColumn(2,"Scadenza",LVCFMT_CENTER, 100, -1);

	m_lstEtichette.DeleteAllItems();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
