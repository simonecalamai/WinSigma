// TrovaAzienda.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "WinSigmaDoc.h"
#include "TrovaAziendaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrovaAzienda dialog


CTrovaAziendaDlg::CTrovaAziendaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrovaAziendaDlg::IDD, pParent)
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

	//{{AFX_DATA_INIT(CTrovaAziendaDlg)
	m_strPartitaIva = _T("");
	m_strNome = _T("");
	m_strID = _T("");
	m_nAziende = 0;
	//}}AFX_DATA_INIT
  m_pSet        = NULL;
	m_lCodice     = 0;
  m_lListino    = 0;
	m_lPagamento  = 0;
	m_strIndirizzo = _T("");
	m_pSet = new CAziendeSet(&pApp->m_db);
}

CTrovaAziendaDlg::~CTrovaAziendaDlg()
{
  if(m_pSet->IsOpen())
	  m_pSet->Close();
  delete m_pSet;
}

void CTrovaAziendaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrovaAziendaDlg)
	DDX_Control(pDX, IDC_LIST_RISULTATI, m_ListRisultati);
	DDX_Text(pDX, IDC_EDIT_PIVA, m_strPartitaIva);
	DDV_MaxChars(pDX, m_strPartitaIva, 16);
	DDX_Text(pDX, IDC_EDIT_NOME, m_strNome);
	DDV_MaxChars(pDX, m_strNome, 64);
	DDX_Text(pDX, IDC_EDIT_CODICE, m_strID);
	DDX_Text(pDX, IDC_EDIT_NAZIENDE, m_nAziende);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTrovaAziendaDlg, CDialog)
	//{{AFX_MSG_MAP(CTrovaAziendaDlg)
	ON_BN_CLICKED(IDC_BUTTON_CERCA, OnButtonCerca)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RISULTATI, OnDblclkListRisultati)
	ON_EN_CHANGE(IDC_EDIT_NOME, OnChangeEditNome)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CTrovaAziendaDlg::Find()
{
  int nCnt;

  ASSERT(!m_pSet->IsOpen());
	m_pSet->m_strFilter = Filter();
	if(m_pSet->m_strFilter.IsEmpty())
	  m_pSet->m_strFilter = "Codice = 0";
	m_pSet->m_strSort = "RagioneSociale";
	for(nCnt = 0, m_pSet->Open(); !m_pSet->IsEOF(); nCnt++, m_pSet->MoveNext());
	if(nCnt == 1)
	{
	  m_pSet->MoveFirst();
	  return TRUE;
	}
	return FALSE;
}

CString CTrovaAziendaDlg::Filter()
{
	CString strQuery, str;

	if(!m_strID.IsEmpty())
	{
		m_strID.Replace("'", "''");
		strQuery.Format("ID like '%s%%'", m_strID);
	}
 
	if(!m_strNome.IsEmpty())
	{
		m_strNome.Replace("'", "''");
	  if(!strQuery.IsEmpty())
			strQuery += " AND ";
			
		int len = m_strNome.GetLength();
		if(len > 2)
		{
			str.Format("RagioneSociale like '%%%s%%'", m_strNome);
		}
		else
		{
			str.Format("RagioneSociale like '%s%%'", m_strNome);
		}
		strQuery += str;
	}
	if(!m_strPartitaIva.IsEmpty())
	{
		m_strPartitaIva.Replace("'", "''");
	  if(!strQuery.IsEmpty())
		  strQuery += " AND ";
		str.Format("P_IVA like '%s%%'", m_strPartitaIva);
		strQuery += str;
	}
	return strQuery;
}

void CTrovaAziendaDlg::LoadList(void)
{
  int n;
	CString str;

  m_ListRisultati.DeleteAllItems();
  for(SET_START(m_pSet), m_nAziende = 0; !m_pSet->IsEOF(); m_pSet->MoveNext(), m_nAziende++)
	{
	  n = m_ListRisultati.InsertItem(m_nAziende, m_pSet->m_ID, 0);
    m_ListRisultati.SetItemText(n, 1, m_pSet->m_P_IVA);
    m_ListRisultati.SetItemText(n, 2, m_pSet->m_RagioneSociale);
		str = m_pSet->m_Indirizzo + " - " + m_pSet->m_CAP + " " + m_pSet->m_Citta;
    m_ListRisultati.SetItemText(n, 3, str);
		m_ListRisultati.SetItemText(n, 4, m_pSet->m_CodiceFiscale);
    m_ListRisultati.SetItemData(n, m_pSet->m_Codice);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTrovaAzienda message handlers


BOOL CTrovaAziendaDlg::OnInitDialog() 
{
	DWORD style;
	CDialog::OnInitDialog();

  style = m_ListRisultati.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT;
	m_ListRisultati.SetExtendedStyle(style);	
  m_ListRisultati.InsertColumn(0, "Codice",						LVCFMT_CENTER,	60,  -1);
  m_ListRisultati.InsertColumn(1, "P. IVA",						LVCFMT_CENTER,	80,  -1);
  m_ListRisultati.InsertColumn(2, "Ragione sociale",	LVCFMT_LEFT,		260, -1); 
  m_ListRisultati.InsertColumn(3, "Indirizzo",				LVCFMT_LEFT,		300, -1); 
	m_ListRisultati.InsertColumn(4, "Cod. Fiscale",			LVCFMT_LEFT,		130, -1); 
  if(!m_pSet->IsOpen())
	  Find();
	LoadList();
	UpdateData(FALSE);
	return TRUE; 
}


void CTrovaAziendaDlg::OnButtonCerca() 
{
  UpdateData();
	m_pSet->m_strFilter = Filter();
	if(m_pSet->m_strFilter.IsEmpty())
	{
	  AfxMessageBox("Definire una chiave di ricerca di almeno un carattere.");
		return;
	}
	m_pSet->Requery();
	LoadList();
  UpdateData(FALSE);
}

void CTrovaAziendaDlg::OnOK() 
{
  int n;
	POSITION pos;
  
  pos = m_ListRisultati.GetFirstSelectedItemPosition();
	if((n = m_ListRisultati.GetNextSelectedItem(pos)) < 0)
  {
	  AfxMessageBox("Selezionare un'azienda dalla lista o premere 'Annulla'");
		return;
  }
  m_lCodice = (long)m_ListRisultati.GetItemData(n);
  SINCRONIZE(m_pSet, m_lCodice);
	CDialog::OnOK();
}

void CTrovaAziendaDlg::OnDblclkListRisultati(NMHDR* pNMHDR, LRESULT* pResult) 
{
  OnOK();	
	*pResult = 0;
}

void CTrovaAziendaDlg::OnChangeEditNome() 
{
	UpdateData();

	if(m_strNome.GetLength() < 3)
		return;
	m_pSet->m_strFilter = Filter();
	m_pSet->Requery();
	LoadList();
  UpdateData(FALSE);
}
