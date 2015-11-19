// MinuteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "MinuteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMinuteDlg dialog


CMinuteDlg::CMinuteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMinuteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMinuteDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMinuteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMinuteDlg)
	DDX_Control(pDX, IDC_LIST_MINUTE, m_ListMinute);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMinuteDlg, CDialog)
	//{{AFX_MSG_MAP(CMinuteDlg)
	ON_BN_CLICKED(IDC_BUTTON_TUTTE, OnButtonTutte)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMinuteDlg message handlers

BOOL CMinuteDlg::OnInitDialog() 
{
	DWORD style;
	CDialog::OnInitDialog();
	style = m_ListMinute.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES;
	m_ListMinute.SetExtendedStyle(style);
  m_ListMinute.InsertColumn(0, "Tipo certificato", LVCFMT_LEFT, 360, -1);

	int n =0;
	for(SET_START(m_pTCertSet); !m_pTCertSet->IsEOF(); m_pTCertSet->MoveNext() )
		{
		m_ListMinute.InsertItem(n,m_pTCertSet->m_Nome);
		m_ListMinute.SetItemData(n,m_pTCertSet->m_Codice);
		n++;
		}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMinuteDlg::OnButtonTutte() 
{
	m_aryTCertificato.RemoveAll();
	for(SET_START(m_pTCertSet); !m_pTCertSet->IsEOF(); m_pTCertSet->MoveNext() )
		m_aryTCertificato.Add(m_pTCertSet->m_Codice);
	CDialog::OnOK();
}

void CMinuteDlg::OnOK() 
{
	m_aryTCertificato.RemoveAll();
	for(int n = 0; n < m_ListMinute.GetItemCount(); n++ )
		if( m_ListMinute.GetCheck(n) )
			m_aryTCertificato.Add(m_ListMinute.GetItemData(n));
	CDialog::OnOK();
}

