// EsportaXMLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "EsportaXMLDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEsportaXMLDlg dialog


CEsportaXMLDlg::CEsportaXMLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEsportaXMLDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEsportaXMLDlg)
	m_intAnno = 2018;
	m_intAFattura = 0;
	m_intDaFattura = 0;
	m_intProgressivo = 0;
	m_csPath = _T("C:\\is\\dati\\");
	//}}AFX_DATA_INIT
}


void CEsportaXMLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEsportaXMLDlg)
	DDX_Text(pDX, IDC_EDIT_ANNO, m_intAnno);
	DDV_MinMaxInt(pDX, m_intAnno, 2003, 2999);
	DDX_Text(pDX, IDC_EDIT_A_FATTURA, m_intAFattura);
	DDV_MinMaxInt(pDX, m_intAFattura, 0, 99999);
	DDX_Text(pDX, IDC_EDIT_DA_FATTURA, m_intDaFattura);
	DDV_MinMaxInt(pDX, m_intDaFattura, 0, 99999);
	DDX_Text(pDX, IDC_EDIT_PROGRESSIVO, m_intProgressivo);
	DDV_MinMaxInt(pDX, m_intProgressivo, 0, 99999);
	DDX_Text(pDX, IDC_EDIT_PATH, m_csPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEsportaXMLDlg, CDialog)
	//{{AFX_MSG_MAP(CEsportaXMLDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEsportaXMLDlg message handlers

BOOL CEsportaXMLDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	
	// imposta l'anno corrente
	CTime t = CTime::GetCurrentTime();
	m_intAnno = t.GetYear();
	m_intDaFattura = 1;
	m_intAFattura = 2;

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEsportaXMLDlg::OnOK() 
{
	UpdateData();
	if ((m_intAFattura == 0) || (m_intDaFattura == 0))
	{
		MessageBox("Errore inserire un numero di fattura valido!", "Attenzione",MB_OK);
		return;
	}
	else if (m_intAFattura < m_intDaFattura)
	{
		MessageBox("Errore nell'intervallo delle fatture!", "Attenzione",MB_OK);
		return;
	}
/*	else if (m_csAnno.IsEmpty())
	{
		MessageBox("Selezionare l'anno!", "Attenzione",MB_OK);
		return;
	}*/
	else if (m_csPath == "")
	{
		MessageBox("Inserire un path valido dove esportare il file!", "Attenzione",MB_OK);
		return;
	}
	
	CDialog::OnOK();
}
