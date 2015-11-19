// SalvaStampaVerbaliDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "SalvaStampaVerbaliDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SalvaStampaVerbaliDlg dialog


CSalvaStampaVerbaliDlg::CSalvaStampaVerbaliDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSalvaStampaVerbaliDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSalvaStampaVerbaliDlg)
	m_bPrintMinuta = FALSE;
	m_bPrintVerbaleCartaLibera = FALSE;
	m_bPrintVerbale = FALSE;
	//}}AFX_DATA_INIT
}


void CSalvaStampaVerbaliDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSalvaStampaVerbaliDlg)
	DDX_Control(pDX, IDC_CHECK_PRN_VERBALE, m_BtnPrnVerbale);
	DDX_Check(pDX, IDC_CHECK_PRN_MINUTA, m_bPrintMinuta);
	DDX_Check(pDX, IDC_CHECK_PRN_VCARTALIBERA, m_bPrintVerbaleCartaLibera);
	DDX_Check(pDX, IDC_CHECK_PRN_VERBALE, m_bPrintVerbale);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSalvaStampaVerbaliDlg, CDialog)
	//{{AFX_MSG_MAP(CSalvaStampaVerbaliDlg)
	ON_BN_CLICKED(IDC_CHECK_PRN_MINUTA, OnCheckPrnMinuta)
	ON_BN_CLICKED(IDC_CHECK_PRN_VCARTALIBERA, OnCheckPrnVcartalibera)
	ON_BN_CLICKED(IDC_CHECK_PRN_VERBALE, OnCheckPrnVerbale)
	ON_BN_CLICKED(IDC_BUTTON_NO, OnButtonNo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SalvaStampaVerbaliDlg message handlers

void CSalvaStampaVerbaliDlg::OnCheckPrnMinuta() 
{
	UpdateData();
}

void CSalvaStampaVerbaliDlg::OnCheckPrnVcartalibera() 
{
	UpdateData();
  if(m_bPrintVerbaleCartaLibera)
    m_bPrintVerbale = !m_bPrintVerbaleCartaLibera;
  UpdateData(FALSE);
}

void CSalvaStampaVerbaliDlg::OnCheckPrnVerbale() 
{
	UpdateData();
  if(m_bPrintVerbale)
  m_bPrintVerbaleCartaLibera = !m_bPrintVerbale;
  UpdateData(FALSE);
}

void CSalvaStampaVerbaliDlg::OnCancel() 
{
	
	CDialog::OnCancel();
}

void CSalvaStampaVerbaliDlg::OnOK() 
{
	
	CDialog::OnOK();
}

void CSalvaStampaVerbaliDlg::OnButtonNo() 
{
  CDialog::EndDialog(IDC_BUTTON_NO);
}

BOOL CSalvaStampaVerbaliDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	m_BtnPrnVerbale.EnableWindow(m_bPrintVerbale);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
