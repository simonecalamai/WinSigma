// EmissioneCertificatiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "EmissioneCertificatiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEmissioneCertificatiDlg dialog


CEmissioneCertificatiDlg::CEmissioneCertificatiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEmissioneCertificatiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmissioneCertificatiDlg)
	m_nNuovoNumero = 0;
	m_lfNumProposto = 0;
	m_strNumScelto = _T("");
//	m_bAderenza = FALSE;
	//}}AFX_DATA_INIT
}


void CEmissioneCertificatiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmissioneCertificatiDlg)
	DDX_Control(pDX, IDC_CHECK_ADERENZA, m_CtrlAderenza);
	DDX_Control(pDX, IDOK, m_BtnOk);
	DDX_Control(pDX, IDC_LIST_CERTIFICATI, m_ListProposti);
	DDX_Text(pDX, IDC_EDIT_NUM_MOD, m_nNuovoNumero);
	DDX_Text(pDX, IDC_EDIT_PROPOSTO, m_lfNumProposto);
	DDX_Text(pDX, IDC_EDIT_CODICE_PRIMO, m_strNumScelto);
//	DDX_Check(pDX, IDC_CHECK_ADERENZA, m_bAderenza);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEmissioneCertificatiDlg, CDialog)
	//{{AFX_MSG_MAP(CEmissioneCertificatiDlg)
	ON_BN_CLICKED(IDC_BUTTON_MOD_NUM, OnButtonModNum)
	ON_BN_CLICKED(IDC_BUTTON_CONFERMA, OnButtonConferma)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CERTIFICATI, OnItemchangedListCertificati)
	ON_BN_CLICKED(IDC_CHECK_ADERENZA, OnCheckAderenza)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmissioneCertificatiDlg message handlers

BOOL CEmissioneCertificatiDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_nNuovoNumero = m_nCodiceProposto;
	
	m_paryAderenza.RemoveAll();
	m_CtrlAderenza.EnableWindow(FALSE);

	// Inizializzazione della lista dei certificati papabili
	DWORD style;
  style = m_ListProposti.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES;
	m_ListProposti.SetExtendedStyle(style);
	m_ListProposti.InsertColumn(0, "Rif V.A.", LVCFMT_LEFT, 80, -1);
	m_ListProposti.InsertColumn(1, "Pos.", LVCFMT_CENTER, 35, -1);
  m_ListProposti.InsertColumn(2, "Tipo certificato", LVCFMT_LEFT, 212, -1);
	m_ListProposti.InsertColumn(3, "Serie", LVCFMT_CENTER, 45, -1);
	m_ListProposti.InsertColumn(4, "Provini", LVCFMT_CENTER, 45, -1);

	// Inserimento dei certificati nella lista
	int n, ind1, ind2, ind3, ind4;
	CString str, descrizione, verbale, posizione, serie, provini;
	for(int i=0; i<m_paryProposti->GetSize(); i++)
	{
		// Inizializza l' UINTARRAY contenente lo stato del check Aderenza
		m_paryAderenza.Add(0);
		n = m_ListProposti.GetItemCount();

		//----- Ricavo le informazioni dalle stringhe ricevute ----//
		str			= m_paryInfoCertificato->GetAt(i).GetBuffer(0);
		ind1		= str.Find('@');
		ind2		= str.Find('@',ind1+1);
		ind3		= str.Find('@',ind2+1);
		ind4		= str.Find('@',ind3+1);
		descrizione		= str.Left(ind1);
		posizione			= str.Mid(ind1 + 1, ind2 - ind1 - 1);
		serie					=	str.Mid(ind2 + 1, ind3 - ind2 - 1);
		provini				= str.Mid(ind3 + 1, ind4 - ind3 - 1);
		verbale				= str.Mid(ind4 + 1);

		//-- Inserisco gli elementi nella lista --//
		n = m_ListProposti.InsertItem(n,verbale);
		m_ListProposti.SetItemData(n, m_paryProposti->GetAt(i)); 
		m_ListProposti.SetItemText(n, 1, posizione);
		m_ListProposti.SetItemText(n, 2, descrizione);
		m_ListProposti.SetItemText(n, 3, serie);
		m_ListProposti.SetItemText(n, 4, provini);
		m_ListProposti.SetCheck(n, FALSE);
	}

	//Inizializzo il valore del codice per il primo certificato con il dato ricevuto
	m_lfNumProposto = m_nCodiceProposto;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEmissioneCertificatiDlg::OnOK() 
{
	m_parySceltiAderenza->RemoveAll();
	for(int n=0; n<m_ListProposti.GetItemCount(); n++)
	{
		if (m_ListProposti.GetCheck(n) )
		{
			m_paryScelti->Add( m_ListProposti.GetItemData(n) );
			m_parySceltiAderenza->Add( m_paryAderenza[n] );
		}
	}
	CDialog::OnOK();
}

void CEmissioneCertificatiDlg::OnButtonModNum() 
{
	UpdateData(TRUE);
	if(m_nNuovoNumero < m_nCodiceProposto)
	{
		AfxMessageBox("Attenzione: il numero proposto non può essere sostituito da un valore inferiore!");
	}
	else
	{
		m_nCodicePrimo = m_nNuovoNumero;
		m_strNumScelto.Format("%d", m_nCodicePrimo);
		m_BtnOk.EnableWindow(TRUE);
		UpdateData(FALSE);
	}
	UpdateData(FALSE);
}

void CEmissioneCertificatiDlg::OnButtonConferma() 
{
	m_nCodicePrimo = m_lfNumProposto;
	m_strNumScelto.Format("%d", m_nCodicePrimo);
	m_BtnOk.EnableWindow(TRUE);
	UpdateData(FALSE);
}

void CEmissioneCertificatiDlg::OnItemchangedListCertificati(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// Gestisce l'abilitazione e la disabilitazione del checkbox Aderenza
	
	// Ricava l'indice dell'item selezionato
	POSITION pos = m_ListProposti.GetFirstSelectedItemPosition();
	if(pos != NULL)
	{
		int i = ((int)(pos)) - 1;
		// Abilita disabilita il checkbox Aderenza a seconda del tipo di certificato
		if ((m_paryTipiCertificato->GetAt(i) == 11) || (m_paryTipiCertificato->GetAt(i) == 13) || 
				(m_paryTipiCertificato->GetAt(i) == 17) || (m_paryTipiCertificato->GetAt(i) == 20))
		{
			m_CtrlAderenza.SetCheck(m_paryAderenza[i]);
			m_CtrlAderenza.EnableWindow(TRUE);
		}
		else
		{
			m_CtrlAderenza.SetCheck(0);
			m_CtrlAderenza.EnableWindow(FALSE);
		}
	}

	*pResult = 0;
}


void CEmissioneCertificatiDlg::OnCheckAderenza() 
{
	// Ricava l'indice dell'item selezionato
	POSITION idx = m_ListProposti.GetFirstSelectedItemPosition();
	int i = ((int)(idx)) - 1;

	if(m_CtrlAderenza.GetCheck() == 1)
	{
		m_paryAderenza[i] = 1;
	}
	else
	{
		m_paryAderenza[i] = 0;
	}
}
