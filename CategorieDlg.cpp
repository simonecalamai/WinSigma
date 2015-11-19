// CategorieDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "CategorieDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCategorieDlg dialog


CCategorieDlg::CCategorieDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCategorieDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCategorieDlg)
	m_strCodice = _T("");
	m_strDescrizione = _T("");
	m_strNome = _T("");
	m_strCodiceListino = _T("");
	m_strNomeListino = _T("");
	//}}AFX_DATA_INIT
}


void CCategorieDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCategorieDlg)
	DDX_Control(pDX, IDC_EDIT_CODICE, m_EditCodice);
	DDX_Text(pDX, IDC_EDIT_CODICE, m_strCodice);
	DDX_Text(pDX, IDC_EDIT_DESCRIZIONE, m_strDescrizione);
	DDV_MaxChars(pDX, m_strDescrizione, 128);
	DDX_Text(pDX, IDC_EDIT_NOME, m_strNome);
	DDV_MaxChars(pDX, m_strNome, 64);
	DDX_Text(pDX, IDC_EDIT_CODICELISTINO, m_strCodiceListino);
	DDX_Text(pDX, IDC_EDIT_NOMELISTINO, m_strNomeListino);
	DDV_MaxChars(pDX, m_strNomeListino, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCategorieDlg, CDialog)
	//{{AFX_MSG_MAP(CCategorieDlg)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnButtonOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCategorieDlg message handlers

BOOL CCategorieDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
  if(m_strCodice.IsEmpty())
	  SetWindowText("Inserimento nuova categoria");
	else
	  SetWindowText("Modifica categoria");
	return TRUE;
}


void CCategorieDlg::OnOK() 
{
  NextDlgCtrl();
}

void CCategorieDlg::OnButtonOk() 
{
  UpdateData();
	if(m_strCodice.IsEmpty())
	{
	  AfxMessageBox("Inserire un codice per la categoria.");
		m_EditCodice.SetFocus(); 
	}
	else
	  CDialog::OnOK();
}
