// InsertVerbaliDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "InsertVerbaliDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsertVerbaliDlg dialog


CInsertVerbaliDlg::CInsertVerbaliDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInsertVerbaliDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInsertVerbaliDlg)
	m_strProgressivoParziale = _T("");
	m_strProgressivoTotale = _T("");
	m_strCantiere = _T("");
	m_DataAccettazione = 0;
	m_bLungaScadenza = FALSE;
	//}}AFX_DATA_INIT
  m_DataAccettazione = CTime::GetCurrentTime();
}


void CInsertVerbaliDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsertVerbaliDlg)
	DDX_Control(pDX, IDC_DATETIMEPICKER_ACCETTAZIONE, m_DTCtrlDataAccettazione);
	DDX_Control(pDX, IDC_EDIT_PARZIALE, m_EditParziale);
	DDX_Text(pDX, IDC_EDIT_PARZIALE, m_strProgressivoParziale);
	DDX_Text(pDX, IDC_EDIT_TOTALE, m_strProgressivoTotale);
	DDX_Text(pDX, IDC_EDIT_CANTIERE, m_strCantiere);
	DDV_MaxChars(pDX, m_strCantiere, 255);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ACCETTAZIONE, m_DataAccettazione);
	DDX_Check(pDX, IDC_CHECK_LUNGA_SCADENZA, m_bLungaScadenza);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsertVerbaliDlg, CDialog)
	//{{AFX_MSG_MAP(CInsertVerbaliDlg)
	ON_BN_CLICKED(IDC_CHECK_LUNGA_SCADENZA, OnCheckLungaScadenza)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsertVerbaliDlg message handlers

void CInsertVerbaliDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CInsertVerbaliDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
  m_DTCtrlDataAccettazione.SetTime(&m_DataAccettazione);
  m_EditParziale.SetFocus();
  UpdateData(FALSE);
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInsertVerbaliDlg::OnCheckLungaScadenza() 
{
  UpdateData();
}

void CInsertVerbaliDlg::OnOK() 
{
  UpdateData(TRUE);	
  m_DTCtrlDataAccettazione.GetTime(m_DataAccettazione);
  m_lProgressivoParziale = atoi(m_strProgressivoParziale);
  m_lProgressivoTotale = atoi(m_strProgressivoTotale);
  if(m_lProgressivoParziale > m_lProgressivoTotale || m_strProgressivoParziale.IsEmpty() || m_strProgressivoTotale.IsEmpty())
  {
    AfxMessageBox("Verificare i dati inseriti: i progressivi non sono corretti");
    return;
  }
	CDialog::OnOK();
}
