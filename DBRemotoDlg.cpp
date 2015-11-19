// DBRemotoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "DBRemotoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBRemotoDlg dialog


CDBRemotoDlg::CDBRemotoDlg(CDatiAziende* dati_aziende, CWnd* pParent /*=NULL*/)
	: CDialog(CDBRemotoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDBRemotoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pDatiAziende = dati_aziende;
	m_pAziendeRemoteSet = NULL;
}


void CDBRemotoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDBRemotoDlg)
	DDX_Control(pDX, IDC_LIST_DB_REMOTO, m_lstAziendeRemote);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDBRemotoDlg, CDialog)
	//{{AFX_MSG_MAP(CDBRemotoDlg)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_ID_MISSING, OnButtonIdMissing)
	ON_BN_CLICKED(IDC_BUTTON_ID_PRESENT, OnButtonIdPresent)
	ON_BN_CLICKED(IDC_BUTTON_TUTTI, OnButtonTutti)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBRemotoDlg message handlers

BOOL CDBRemotoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//Defisce lo stile della ListView
	unsigned long style = m_lstAziendeRemote.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT;
	m_lstAziendeRemote.SetExtendedStyle(style);

	//Inserisce le colonne con le relative intestazioni nella lista
	m_lstAziendeRemote.InsertColumn(0,"Ragione sociale",LVCFMT_LEFT, 260, -1);
	m_lstAziendeRemote.InsertColumn(1,"No.",LVCFMT_LEFT, 60, -1);
	m_lstAziendeRemote.InsertColumn(2,"Codice",LVCFMT_LEFT, 60, -1);
	m_lstAziendeRemote.InsertColumn(3,"Partita IVA",LVCFMT_LEFT, 80, -1);
	m_lstAziendeRemote.InsertColumn(4,"Indirizzo",LVCFMT_LEFT, 340, -1);
	m_lstAziendeRemote.DeleteAllItems();

	m_pAziendeRemoteSet = new CAziendeSet(&((CWinSigmaApp*)AfxGetApp())->m_dbr);
	m_pAziendeRemoteSet->m_strFilter.Format("Codice > 11186");
	m_pAziendeRemoteSet->Open();
	
//	PopolaLista();
	OnButtonIdMissing();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDBRemotoDlg::PopolaLista()
{
	m_lstAziendeRemote.DeleteAllItems();

	m_pAziendeRemoteSet->m_strFilter.Format("Codice > 11186");
	m_pAziendeRemoteSet->Requery();
	while (!m_pAziendeRemoteSet->IsEOF())
	{
		AddToListAziende();
		m_pAziendeRemoteSet->MoveNext();
	}
}

void CDBRemotoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	m_lstAziendeRemote.DeleteAllItems();

	m_pAziendeRemoteSet->Close();
	delete m_pAziendeRemoteSet;
	m_pAziendeRemoteSet = NULL;
}

void CDBRemotoDlg::OnButtonIdMissing() 
{
	CString csText, csSQL;
	CAziendeSet* pSet = new CAziendeSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
	m_lstAziendeRemote.DeleteAllItems();

	m_pAziendeRemoteSet->m_strFilter.Format("Codice > 11186");
	m_pAziendeRemoteSet->Requery();
	while (!m_pAziendeRemoteSet->IsEOF())
	{
		pSet->m_strFilter.Format("ID LIKE '%s'", m_pAziendeRemoteSet->m_ID);
		pSet->Open();
		if(pSet->IsBOF())
		{		
			AddToListAziende();
		}
		pSet->Close();
		m_pAziendeRemoteSet->MoveNext();
	}
	delete pSet;
}

void CDBRemotoDlg::OnButtonIdPresent() 
{
	CString csSQL;
	CAziendeSet* pSet = new CAziendeSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
	m_lstAziendeRemote.DeleteAllItems();

	m_pAziendeRemoteSet->m_strFilter.Format("Codice > 11186");
	m_pAziendeRemoteSet->Requery();
	while (!m_pAziendeRemoteSet->IsEOF())
	{
		pSet->m_strFilter.Format("ID LIKE '%s'", m_pAziendeRemoteSet->m_ID);
		pSet->Open();
		if(!pSet->IsBOF())
		{		
			AddToListAziende();
		}
		pSet->Close();
		m_pAziendeRemoteSet->MoveNext();
	}
	delete pSet;
}

void CDBRemotoDlg::OnButtonTutti() 
{
	PopolaLista();
}

void CDBRemotoDlg::AddToListAziende()
{
	int n;
	CString csText;

	n = m_lstAziendeRemote.InsertItem(0,m_pAziendeRemoteSet->m_RagioneSociale);
	m_lstAziendeRemote.SetItemData(n,(DWORD)m_pAziendeRemoteSet->m_Codice);

	csText.Format("%d", m_pAziendeRemoteSet->m_Codice);
	m_lstAziendeRemote.SetItemText(n,1,csText);
	m_lstAziendeRemote.SetItemText(n,2,m_pAziendeRemoteSet->m_ID);
	m_lstAziendeRemote.SetItemText(n,3,m_pAziendeRemoteSet->m_P_IVA);
	csText.Format(m_pAziendeRemoteSet->m_Indirizzo + " " + m_pAziendeRemoteSet->m_Citta + " " + m_pAziendeRemoteSet->m_CAP + " " + m_pAziendeRemoteSet->m_Provincia);
	m_lstAziendeRemote.SetItemText(n,4, csText);
}

void CDBRemotoDlg::OnOK() 
{
	if(m_lstAziendeRemote.GetItemCount()>0)
	{
		int index = m_lstAziendeRemote.GetSelectionMark();
		if(index > -1)
		{
			m_pAziendeRemoteSet->m_strFilter.Format("Codice = %d", m_lstAziendeRemote.GetItemData(index));
			m_pAziendeRemoteSet->Requery();
					
			if(!m_pAziendeRemoteSet->IsEOF())
			{				
			  m_pDatiAziende->m_ABI								= m_pAziendeRemoteSet->m_ABI;
				m_pDatiAziende->m_Banca							=	m_pAziendeRemoteSet->m_Banca;
				m_pDatiAziende->m_CAB								=	m_pAziendeRemoteSet->m_CAB;
				m_pDatiAziende->m_CAP								=	m_pAziendeRemoteSet->m_CAP;
				m_pDatiAziende->m_CAP_Sped						=	m_pAziendeRemoteSet->m_CAP_Sped;
				m_pDatiAziende->m_Cellulare					=	m_pAziendeRemoteSet->m_Cellulare;
				m_pDatiAziende->m_Citta							=	m_pAziendeRemoteSet->m_Citta;
				m_pDatiAziende->m_Citta_Sped					=	m_pAziendeRemoteSet->m_Citta_Sped;
				m_pDatiAziende->m_CodiceFiscale			=	m_pAziendeRemoteSet->m_CodiceFiscale;
				m_pDatiAziende->m_Cognome						=	m_pAziendeRemoteSet->m_Cognome;
				m_pDatiAziende->m_DataInserimento		=	m_pAziendeRemoteSet->m_DataInserimento;
				m_pDatiAziende->m_DataUltimoRapporto	=	m_pAziendeRemoteSet->m_DataUltimoRapporto;
				m_pDatiAziende->m_E_Mail							=	m_pAziendeRemoteSet->m_E_Mail;
				m_pDatiAziende->m_Fax								=	m_pAziendeRemoteSet->m_Fax;
				m_pDatiAziende->m_ID									=	m_pAziendeRemoteSet->m_ID;
				m_pDatiAziende->m_Indirizzo					=	m_pAziendeRemoteSet->m_Indirizzo;
				m_pDatiAziende->m_Indirizzo_Sped			=	m_pAziendeRemoteSet->m_Indirizzo_Sped;
				m_pDatiAziende->m_IsImportante				=	m_pAziendeRemoteSet->m_IsImportante;
				m_pDatiAziende->m_Nome								=	m_pAziendeRemoteSet->m_Nome;
				m_pDatiAziende->m_Note								=	m_pAziendeRemoteSet->m_Note;
				m_pDatiAziende->m_P_IVA							=	m_pAziendeRemoteSet->m_P_IVA;
				m_pDatiAziende->m_Privato						=	m_pAziendeRemoteSet->m_Privato;
				m_pDatiAziende->m_Provincia					=	m_pAziendeRemoteSet->m_Provincia;
				m_pDatiAziende->m_Provincia_Sped			=	m_pAziendeRemoteSet->m_Provincia_Sped;
				m_pDatiAziende->m_RagioneSociale			=	m_pAziendeRemoteSet->m_RagioneSociale;
				m_pDatiAziende->m_RagioneSociale_Sped=	m_pAziendeRemoteSet->m_RagioneSociale_Sped;
				m_pDatiAziende->m_Sconto							=	m_pAziendeRemoteSet->m_Sconto;
				m_pDatiAziende->m_Telefono						=	m_pAziendeRemoteSet->m_Telefono;
				m_pDatiAziende->m_TipoPagamento			=	m_pAziendeRemoteSet->m_TipoPagamento;
				m_pDatiAziende->m_UsaTuttiListini		=	m_pAziendeRemoteSet->m_UsaTuttiListini;
			}
		}
	}
	CDialog::OnOK();
}

