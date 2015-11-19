// DatiFatturaProforma.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "DatiFatturaProforma.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDatiFatturaProforma dialog


CDatiFatturaProforma::CDatiFatturaProforma(CWnd* pParent /*=NULL*/)
	: CDialog(CDatiFatturaProforma::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDatiFatturaProforma)
	m_bSpedizione = FALSE;
	m_strAliquota = _T("");
	m_strSconto = _T("");
	m_strSpese = _T("");
	m_nNumCopie = 0;
	//}}AFX_DATA_INIT
}


void CDatiFatturaProforma::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatiFatturaProforma)
	DDX_Control(pDX, IDC_CHECK_SPEDIZIONE, m_BtnSpedizione);
	DDX_Control(pDX, IDC_EDIT_SPESE, m_EditSpese);
	DDX_Check(pDX, IDC_CHECK_SPEDIZIONE, m_bSpedizione);
	DDX_Text(pDX, IDC_EDIT_ALIQUOTA, m_strAliquota);
	DDX_Text(pDX, IDC_EDIT_SCONTO, m_strSconto);
	DDX_Text(pDX, IDC_EDIT_SPESE, m_strSpese);
	DDX_Text(pDX, IDC_EDIT_NUMCOPIE, m_nNumCopie);
	DDV_MinMaxInt(pDX, m_nNumCopie, 1, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDatiFatturaProforma, CDialog)
	//{{AFX_MSG_MAP(CDatiFatturaProforma)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatiFatturaProforma message handlers

BOOL CDatiFatturaProforma::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
  m_EditSpese.EnableWindow(m_bSpedizione);
  m_BtnSpedizione.EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

