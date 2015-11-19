// ArchivioAziende.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "ArchivioAziende.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArchivioAziende dialog


CArchivioAziendeDlg::CArchivioAziendeDlg(CDatiAziende* dati_aziende, CWnd* pParent /*=NULL*/)
	: CDialog(CArchivioAziendeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CArchivioAziendeDlg)
	m_csIndirizzo = _T("");
	m_csPartita_IVA = _T("");
	m_csRagione_Sociale = _T("");
	//}}AFX_DATA_INIT
	
	m_pDati_Aziende = dati_aziende;
}

void CArchivioAziendeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArchivioAziendeDlg)
	DDX_Control(pDX, IDC_LIST_AZIENDE_VECCHIE, m_Lista_Aziende);
	DDX_Text(pDX, IDC_EDIT_INDIRIZZO, m_csIndirizzo);
	DDV_MaxChars(pDX, m_csIndirizzo, 32);
	DDX_Text(pDX, IDC_EDIT_PARTITA_IVA, m_csPartita_IVA);
	DDV_MaxChars(pDX, m_csPartita_IVA, 16);
	DDX_Text(pDX, IDC_EDIT_RAGIONE_SOCIALE, m_csRagione_Sociale);
	DDV_MaxChars(pDX, m_csRagione_Sociale, 64);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArchivioAziendeDlg, CDialog)
	//{{AFX_MSG_MAP(CArchivioAziendeDlg)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_AZIENDE_VECCHIE, OnDblclkListAziendeVecchie)
	ON_BN_CLICKED(ID_BUTTON_RICERCA, OnButtonRicerca)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArchivioAziendeDlg message handlers

BOOL CArchivioAziendeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	//Defisce lo stile della ListView
	unsigned long style = m_Lista_Aziende.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT;
	m_Lista_Aziende.SetExtendedStyle(style);

	//Inserisce le colonne con le relative intestazioni nella lista
	m_Lista_Aziende.InsertColumn(0,"Ragione sociale",LVCFMT_LEFT, 250, -1);
	m_Lista_Aziende.InsertColumn(1,"Partita IVA",LVCFMT_LEFT, 90, -1);
	m_Lista_Aziende.InsertColumn(2,"Indirizzo",LVCFMT_LEFT, 250, -1);
	m_Lista_Aziende.DeleteAllItems();

	aziende_old	=	NULL;
	aziende_old = new CAziendeOldSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
	aziende_old->m_strFilter.Empty();
//  aziende_old->
	aziende_old->Open();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CArchivioAziendeDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	m_Lista_Aziende.DeleteAllItems();

	aziende_old->Close();
	delete aziende_old;

}

void CArchivioAziendeDlg::Query()
{
	CString sql("");

	//Aggiorna le variabili con il valore contenuto nei campi della form
	UpdateData(TRUE);

	//Crea la stringa sql da utilizzare nella Query
	if (m_csRagione_Sociale!="")
		{
		m_csRagione_Sociale.Replace("'", "''");
		m_csRagione_Sociale.Replace("%", "%%");
		sql="(RagioneSociale LIKE '" + m_csRagione_Sociale + "%')";
		}

	if (m_csIndirizzo!="")
		{
		 m_csIndirizzo.Replace("'", "''");
			if (sql=="")
					sql="(Indirizzo LIKE '%" + m_csIndirizzo + "%')";
			else
					sql+=" AND (Indirizzo LIKE '%" + m_csIndirizzo + "%')";
		}

	if (m_csPartita_IVA!="")
		{
			if (sql=="")
					sql="(P_IVA = '" + m_csPartita_IVA + "')";
			else
					sql+=" AND (P_IVA = '" + m_csPartita_IVA + "')";
		}



	if (sql!="")
		{
			aziende_old->m_strFilter=sql;
			aziende_old->Requery();
		}
	else
		{
			aziende_old->m_strFilter.Empty();
			aziende_old->Requery();
		}
}

void CArchivioAziendeDlg::Popola_Lista()
{
	m_Lista_Aziende.DeleteAllItems();

	while (!aziende_old->IsEOF())
	{
		int n;

		n = m_Lista_Aziende.InsertItem(0,aziende_old->m_RagioneSociale);
		m_Lista_Aziende.SetItemData(n,(DWORD)aziende_old->m_Codice);

		m_Lista_Aziende.SetItemText(n,1,aziende_old->m_P_IVA);
		m_Lista_Aziende.SetItemText(n,2,aziende_old->m_Indirizzo +
																		" " +
																		aziende_old->m_Citta +
																		" " +
																		aziende_old->m_CAP +
																		" " +
																		aziende_old->m_Provincia);
		aziende_old->MoveNext();
	}
}

bool CArchivioAziendeDlg::Congruenza_Dati_Ricerca(CString* msg)
{
	int congruenza(1);

	UpdateData(TRUE);

	for(int i(0);i<m_csPartita_IVA.GetLength();i++)
		{
			char buf=m_csPartita_IVA.GetAt(i);
			congruenza = strspn(&buf,"0123456789");
			if (congruenza == 0)
			{
					msg->Insert(0,"Il valore del campo 'Partita IVA' deve essere numerico.");
					return false;
			}
		}

	if	(
				(strcmp(m_csRagione_Sociale,"")==0)&&
				(strcmp(m_csIndirizzo,"")==0)&&
				(strcmp(m_csPartita_IVA,"")==0)
			)
		{
					msg->Insert(0,"Deve essere inserita almeno una chiave di ricerca.");
					return false;
		}

	if	(
				(strcmp(m_csIndirizzo,"")==0)&&
				(strcmp(m_csPartita_IVA,"")==0)&&
				(m_csRagione_Sociale.GetLength() < 3)
			)
	{
					msg->Insert(0,"La lunghezza della chiave 'Ragione sociale' deve essere di almeno tre caratteri.");
					return false;	
	}

	return true;
}

void CArchivioAziendeDlg::OnDblclkListAziendeVecchie(NMHDR* pNMHDR, LRESULT* pResult) 
{
  OnOK();
}


void CArchivioAziendeDlg::OnButtonRicerca() 
{
	//Controlla la congruenza dei dati presenti nei campi di selezione della Query
	CString msg("");
	if (Congruenza_Dati_Ricerca(&msg) == true)
	{
		//Esecuzione della query
		Query();

		//Popolamento della lista con il risultato della Query
		Popola_Lista();
	}
	else
	{
		AfxMessageBox(msg);
	}
}

void CArchivioAziendeDlg::OnOK() 
{

	if(m_Lista_Aziende.GetItemCount()>0)
	{
		int index =m_Lista_Aziende.GetSelectionMark();
		if (index > -1)
		{
			aziende_old->m_strFilter.Format("Codice = %d", m_Lista_Aziende.GetItemData(index));
			aziende_old->Requery();
					
			if (!aziende_old->IsEOF())
			{				
			  m_pDati_Aziende->m_ABI								= aziende_old->m_ABI;
				m_pDati_Aziende->m_Banca							=	aziende_old->m_Banca;
				m_pDati_Aziende->m_CAB								=	aziende_old->m_CAB;
				m_pDati_Aziende->m_CAP								=	aziende_old->m_CAP;
				m_pDati_Aziende->m_CAP_Sped						=	aziende_old->m_CAP_Sped;
				m_pDati_Aziende->m_Cellulare					=	aziende_old->m_Cellulare;
				m_pDati_Aziende->m_Citta							=	aziende_old->m_Citta;
				m_pDati_Aziende->m_Citta_Sped					=	aziende_old->m_Citta_Sped;
				m_pDati_Aziende->m_CodiceFiscale			=	aziende_old->m_CodiceFiscale;
				m_pDati_Aziende->m_Cognome						=	aziende_old->m_Cognome;
				m_pDati_Aziende->m_DataInserimento		=	aziende_old->m_DataInserimento;
				m_pDati_Aziende->m_DataUltimoRapporto	=	aziende_old->m_DataUltimoRapporto;
				m_pDati_Aziende->m_E_Mail							=	aziende_old->m_E_Mail;
				m_pDati_Aziende->m_Fax								=	aziende_old->m_Fax;
				m_pDati_Aziende->m_ID									=	aziende_old->m_ID;
				m_pDati_Aziende->m_Indirizzo					=	aziende_old->m_Indirizzo;
				m_pDati_Aziende->m_Indirizzo_Sped			=	aziende_old->m_Indirizzo_Sped;
				m_pDati_Aziende->m_IsImportante				=	aziende_old->m_IsImportante;
				m_pDati_Aziende->m_Nome								=	aziende_old->m_Nome;
				m_pDati_Aziende->m_Note								=	aziende_old->m_Note;
				m_pDati_Aziende->m_P_IVA							=	aziende_old->m_P_IVA;
				m_pDati_Aziende->m_Privato						=	aziende_old->m_Privato;
				m_pDati_Aziende->m_Provincia					=	aziende_old->m_Provincia;
				m_pDati_Aziende->m_Provincia_Sped			=	aziende_old->m_Provincia_Sped;
				m_pDati_Aziende->m_RagioneSociale			=	aziende_old->m_RagioneSociale;
				m_pDati_Aziende->m_RagioneSociale_Sped=	aziende_old->m_RagioneSociale_Sped;
				m_pDati_Aziende->m_Sconto							=	aziende_old->m_Sconto;
				m_pDati_Aziende->m_Telefono						=	aziende_old->m_Telefono;
				m_pDati_Aziende->m_TipoPagamento			=	aziende_old->m_TipoPagamento;
				m_pDati_Aziende->m_UsaTuttiListini		=	aziende_old->m_UsaTuttiListini;
			}
		}
	}
	CDialog::OnOK();
}
