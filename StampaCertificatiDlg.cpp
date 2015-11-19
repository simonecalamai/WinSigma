// StampaCertificatiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "StampaCertificatiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStampaCertificatiDlg dialog


CStampaCertificatiDlg::CStampaCertificatiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStampaCertificatiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStampaCertificatiDlg)
	m_bDuplicato = FALSE;
	m_DataDuplicato = 0;
	//m_bAderenza = FALSE;
	//}}AFX_DATA_INIT
}


void CStampaCertificatiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStampaCertificatiDlg)
	DDX_Control(pDX, IDC_DATA_DUPLICATO, m_CtrDataDuplicato);
	DDX_Control(pDX, IDC_CHECK_DUPLICATO, m_BtnDuplicato);
	DDX_Control(pDX, IDC_LIST_CERTIFICATI_STAMPABILI, m_ListCertificati);
	DDX_Check(pDX, IDC_CHECK_DUPLICATO, m_bDuplicato);
	DDX_DateTimeCtrl(pDX, IDC_DATA_DUPLICATO, m_DataDuplicato);
	//DDX_Check(pDX, IDC_CHECK_ADERENZA, m_bAderenza);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStampaCertificatiDlg, CDialog)
	//{{AFX_MSG_MAP(CStampaCertificatiDlg)
	ON_BN_CLICKED(IDC_BUTTON_SELEZIONE, OnButtonSelezione)
	ON_BN_CLICKED(IDC_CHECK_DUPLICATO, OnCheckDuplicato)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStampaCertificatiDlg message handlers

BOOL CStampaCertificatiDlg::OnInitDialog() 
{
	m_imgStampaCert.Create(IDB_IMAGELIST_STAMPA_CERT, 16, 0, RGB(0,128,128));
	CDialog::OnInitDialog();
	m_bSelezione = FALSE;
	m_DataDuplicato = CTime::GetCurrentTime();

	if(m_bRistampa)
		m_BtnDuplicato.EnableWindow(TRUE);
	
	DWORD style;
  style = m_ListCertificati.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES;
	m_ListCertificati.SetExtendedStyle(style);
	m_ListCertificati.InsertColumn(0, "Numero", LVCFMT_LEFT, 70, -1);
	m_ListCertificati.InsertColumn(1, "Verbale", LVCFMT_CENTER, 60, -1);
	m_ListCertificati.InsertColumn(2, "Tipo", LVCFMT_LEFT, 210, -1);
	m_ListCertificati.InsertColumn(3, "Aderenza", LVCFMT_LEFT, 0, -1);

	m_ListCertificati.SetImageList(&m_imgStampaCert, LVSIL_SMALL);
	RiempiElenco();

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CStampaCertificatiDlg::OnOK() 
{
	for(int n=0; n<m_ListCertificati.GetItemCount(); n++)
		{
		if ( m_ListCertificati.GetCheck(n) )
		m_pCertificatiScelti->Add( m_ListCertificati.GetItemData(n) );
		}	
	CDialog::OnOK();
}



void CStampaCertificatiDlg::OnButtonSelezione() 
{
	for(int n=0; n<m_ListCertificati.GetItemCount(); n++)
		{
		 m_ListCertificati.SetCheck(n, m_bSelezione);
		}	
	m_bSelezione = !m_bSelezione;
}



///////////////////////////////////////////////////////////////////////////
// Riempie l'elenco con gli elementi contenuti nel recordset m_pCertVerbSet

void CStampaCertificatiDlg::RiempiElenco()
{
	int n = 0, nIcona;
	CString str;
	m_ListCertificati.DeleteAllItems();
	for(SET_START(m_pCertVerbSet); !m_pCertVerbSet->IsEOF(); m_pCertVerbSet->MoveNext() )
	{
		m_pCertVerbSet->IsFieldNull(&m_pCertVerbSet->m_DataStampa) ? nIcona=0 : nIcona=1;

		SINCRONIZE(m_pTipiCertificatoSet, m_pCertVerbSet->m_TipoCertificato);
		n = m_ListCertificati.GetItemCount(); // indice della prima posizione disponibile

		str.Format("%d", m_pCertVerbSet->m_NumeroCertificato);
		n = m_ListCertificati.InsertItem(n, str, nIcona);
		m_ListCertificati.SetItemData(n, m_pCertVerbSet->m_CodiceCertificato ); 
		str.Format("%d/%d",  m_pCertVerbSet->m_ProgressivoParziale, m_pCertVerbSet->m_ProgressivoTotale);
		m_ListCertificati.SetItemText(n, 1, str);
		m_ListCertificati.SetItemText(n, 2, m_pTipiCertificatoSet->m_Nome);
		
		// Se il tipo di certificato sui BA450 è 2010 visualizzo se è con o senza aderenza
		if ((m_pCertVerbSet->m_TipoCertificato == 11) || (m_pCertVerbSet->m_TipoCertificato == 13))
		{
			// controllo se la colonna 'Aderenza' e' gia' stata aggiunta 
			int nWid = m_ListCertificati.GetColumnWidth(3);
			if(nWid == 0)
			{
				m_ListCertificati.SetColumnWidth(2,150);
				m_ListCertificati.SetColumnWidth(3,60);
			}
			if(m_pCertVerbSet->m_Aderenza == 0)
			{
				m_ListCertificati.SetItemText(n, 3, "No");
			}
			else if (m_pCertVerbSet->m_Aderenza == 1)
			{
				m_ListCertificati.SetItemText(n, 3, "Sì");
			}
		}
		m_ListCertificati.SetCheck(n, TRUE);
	}
}

void CStampaCertificatiDlg::OnCheckDuplicato() 
{
	UpdateData();
	m_CtrDataDuplicato.EnableWindow(m_bDuplicato);
	UpdateData(FALSE);
}