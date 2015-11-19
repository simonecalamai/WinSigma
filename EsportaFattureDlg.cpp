// EsportaFattureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "EsportaFattureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEsportaFattureDlg dialog


CEsportaFattureDlg::CEsportaFattureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEsportaFattureDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEsportaFattureDlg)
	m_intAFattura = 0;
	m_intDaFattura = 0;
	m_csAnno = _T("");
	m_csPath = _T("C:\\is\\dati\\");
	m_intAElett = 0;
	m_intDaElett = 0;
	//}}AFX_DATA_INIT
}


void CEsportaFattureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEsportaFattureDlg)
	DDX_Control(pDX, IDC_COMBO_ANNI, m_cmbAnni);
	DDX_Text(pDX, IDC_EDIT_A_FATTURA, m_intAFattura);
	DDV_MinMaxInt(pDX, m_intAFattura, 0, 10000000);
	DDX_Text(pDX, IDC_EDIT_DA_FATTURA, m_intDaFattura);
	DDV_MinMaxInt(pDX, m_intDaFattura, 0, 10000000);
	DDX_CBString(pDX, IDC_COMBO_ANNI, m_csAnno);
	DDX_Text(pDX, IDC_EDIT_PATH, m_csPath);
	DDX_Text(pDX, IDC_EDIT_A_ELETT, m_intAElett);
	DDX_Text(pDX, IDC_EDIT_DA_ELETT, m_intDaElett);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEsportaFattureDlg, CDialog)
	//{{AFX_MSG_MAP(CEsportaFattureDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEsportaFattureDlg message handlers

BOOL CEsportaFattureDlg::OnInitDialog() 
{
	int year = 0; 

	CDialog::OnInitDialog();

	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	//Recordset Testata Fattura
	m_pFattureSet = new CFattureSet(&pApp->m_db);
  m_pFattureSet->m_strFilter = "Data is not null";
	m_pFattureSet->m_strSort = "Data";
	m_pFattureSet->Open();
	
  // Caricamento degli anni nella combo
  m_cmbAnni.ResetContent();
	int n = m_cmbAnni.AddString("");
  m_cmbAnni.SetItemData(n, 0);
  n++;
  for(SET_START(m_pFattureSet); !m_pFattureSet->IsEOF(); m_pFattureSet->MoveNext())
  {
    if(year != m_pFattureSet->m_Data.GetYear())
    {
      m_cmbAnni.InsertString(n, m_pFattureSet->m_Data.Format("%Y"));
      year = m_pFattureSet->m_Data.GetYear();
      m_cmbAnni.SetItemData(n, year);
      n++;
    }
  }
	//Seleziona come Item corrente quello vuoto
	//m_cmbAnni.SetCurSel(0);
	// seleziona anno corrente
	CTime t = CTime::GetCurrentTime();
	CString cs("");
	cs.Format("%d", t.GetYear());
	m_cmbAnni.SelectString(-1, cs);

	//Chiusura recordSet Testata Fattura
  if(m_pFattureSet)
  {
  	m_pFattureSet->Close();
  	delete m_pFattureSet;
  }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEsportaFattureDlg::OnOK() 
{
	UpdateData();
	if ((m_intAFattura == 0) || (m_intDaFattura == 0))
	{
		if ((m_intAElett == 0) || (m_intDaElett == 0))
		{
			MessageBox("Errore inserire un numero di fattura valido!", "Attenzione",MB_OK);
			return;
		}
	}
	else if ((m_intAFattura < m_intDaFattura) || m_intAElett < m_intDaElett)
	{
		MessageBox("Errore nell'intervallo delle fatture!", "Attenzione",MB_OK);
		return;
	}
	else if (m_csAnno.IsEmpty())
	{
		MessageBox("Selezionare l'anno!", "Attenzione",MB_OK);
		return;
	}
	else if (m_csPath == "")
	{
		MessageBox("Inserire un path valido dove esportare il file!", "Attenzione",MB_OK);
		return;
	}
	
	CDialog::OnOK();
}

