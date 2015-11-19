// ServiziListinoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "ServiziListinoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CServiziListinoDlg dialog


CServiziListinoDlg::CServiziListinoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServiziListinoDlg::IDD, pParent)
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

	//{{AFX_DATA_INIT(CServiziListinoDlg)
	m_strCategoria = _T("");
	m_strDescrizione = _T("");
	m_strNProvini = _T("");
	m_bProvaA = FALSE;
	m_bProvaB = FALSE;
	m_strNome = _T("");
	m_strNorma = _T("");
	m_strRiferimenti = _T("");
	m_strID = _T("");
	m_bPerSerie = FALSE;
	m_bPerProvino = FALSE;
	m_bConcessione = FALSE;
	m_strProviniPerSerie = _T("");
	m_bGeologia = FALSE;
	m_strCommentoMateriale = _T("");
	m_bProvaA2 = FALSE;
	m_bProvaB2 = FALSE;
	m_bProvaA3 = FALSE;
	m_bProvaB3 = FALSE;
	m_bProvaA4 = FALSE;
	m_bProvaB4 = FALSE;
	//}}AFX_DATA_INIT
	m_fPrezzo      = 0;
	m_byProve      = 0;
	m_byProve2     = 0;
	m_byProve3     = 0;
	m_byProve4     = 0;
	m_nCertificato = 0;
	m_nCertificato2= 0;
	m_nCertificato3= 0;
	m_nCertificato4= 0;
	m_nProvini     = 0;
	m_nProviniPerSerie = 0;
	m_nEmissione   = 0;
	m_nAggiuntivo  = 0;
	m_pTCertificatiSet = new CTipiCertificatoSet(&pApp->m_db);
	m_pTCertificatiSet->Open();
}

CServiziListinoDlg::~CServiziListinoDlg()
{
  if(m_pTCertificatiSet)
	{
	  m_pTCertificatiSet->Close();
		delete m_pTCertificatiSet;
	}
}

void CServiziListinoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServiziListinoDlg)
	DDX_Control(pDX, IDC_COMBO_CERTIFICATO4, m_ComboCertificato4);
	DDX_Control(pDX, IDC_COMBO_CERTIFICATO3, m_ComboCertificato3);
	DDX_Control(pDX, IDC_COMBO_CERTIFICATO2, m_ComboCertificato2);
	DDX_Control(pDX, IDC_EDIT_COMMENTO, m_EdtCommento);
	DDX_Control(pDX, IDC_CHECK_GEOLOGIA, m_BtnGeologia);
	DDX_Control(pDX, IDC_CHECK_CONCESSIONE, m_EdtConcessione);
	DDX_Control(pDX, IDC_CHECK_PERPROVINO, m_BtnPerProvino);
	DDX_Control(pDX, IDC_CHECK_PERSERIE, m_BtnPerSerie);
	DDX_Control(pDX, IDC_COMBO_AGGIUNTIVO, m_ComboAggiuntivo);
	DDX_Control(pDX, IDC_COMBO_EMISSIONE, m_ComboEmissione);
	DDX_Control(pDX, IDC_COMBO_ID, m_ComboID);
	DDX_Control(pDX, IDC_EDIT_NPROVINI, m_EditNProvini);
	DDX_Control(pDX, IDC_COMBO_CERTIFICATO, m_ComboCertificato);
	DDX_Control(pDX, IDC_CHECK_PROVAA, m_CheckProvaA);
	DDX_Control(pDX, IDC_CHECK_PROVAB, m_CheckProvaB);
	DDX_Control(pDX, IDC_CHECK_PROVAA2, m_CheckProvaA2);
	DDX_Control(pDX, IDC_CHECK_PROVAB2, m_CheckProvaB2);
	DDX_Control(pDX, IDC_CHECK_PROVAA3, m_CheckProvaA3);
	DDX_Control(pDX, IDC_CHECK_PROVAB3, m_CheckProvaB3);
	DDX_Control(pDX, IDC_CHECK_PROVAA4, m_CheckProvaA4);
	DDX_Control(pDX, IDC_CHECK_PROVAB4, m_CheckProvaB4);
	DDX_Text(pDX, IDC_EDIT_CATEGORIA, m_strCategoria);
	DDX_Text(pDX, IDC_EDIT_DESCRIZIONE, m_strDescrizione);
	DDV_MaxChars(pDX, m_strDescrizione, 255);
	DDX_Text(pDX, IDC_EDIT_NPROVINI, m_strNProvini);
	DDX_Control(pDX, IDC_MASKEDBOX_PREZZO, m_MskEditPrezzo);
	DDX_Text(pDX, IDC_EDIT_NOME, m_strNome);
	DDV_MaxChars(pDX, m_strNome, 64);
	DDX_Text(pDX, IDC_EDIT_NORMA, m_strNorma);
	DDV_MaxChars(pDX, m_strNorma, 62);
	DDX_Text(pDX, IDC_EDIT_RIFERIMENTI, m_strRiferimenti);
	DDV_MaxChars(pDX, m_strRiferimenti, 32);
	DDX_CBString(pDX, IDC_COMBO_ID, m_strID);
	DDX_Check(pDX, IDC_CHECK_PERPROVINO, m_bPerSerie);
	DDX_Check(pDX, IDC_CHECK_PERSERIE, m_bPerProvino);
	DDX_Check(pDX, IDC_CHECK_CONCESSIONE, m_bConcessione);
	DDX_Text(pDX, IDC_EDIT_PROVINI_PER_SERIE, m_strProviniPerSerie);
	DDX_Check(pDX, IDC_CHECK_GEOLOGIA, m_bGeologia);
	DDX_Text(pDX, IDC_EDIT_COMMENTO, m_strCommentoMateriale);
	DDX_Check(pDX, IDC_CHECK_PROVAA, m_bProvaA);
	DDX_Check(pDX, IDC_CHECK_PROVAB, m_bProvaB);
	DDX_Check(pDX, IDC_CHECK_PROVAA2, m_bProvaA2);
	DDX_Check(pDX, IDC_CHECK_PROVAB2, m_bProvaB2);
	DDX_Check(pDX, IDC_CHECK_PROVAA3, m_bProvaA3);
	DDX_Check(pDX, IDC_CHECK_PROVAB3, m_bProvaB3);
	DDX_Check(pDX, IDC_CHECK_PROVAA4, m_bProvaA4);
	DDX_Check(pDX, IDC_CHECK_PROVAB4, m_bProvaB4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServiziListinoDlg, CDialog)
	//{{AFX_MSG_MAP(CServiziListinoDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_CERTIFICATO, OnSelchangeComboCertificato)
	ON_CBN_SELCHANGE(IDC_COMBO_EMISSIONE, OnSelchangeComboEmissione)
	ON_BN_CLICKED(IDC_CHECK_PERSERIE, OnCheckPerserie)
	ON_BN_CLICKED(IDC_CHECK_PERPROVINO, OnCheckPerprovino)
	ON_BN_CLICKED(IDC_CHECK_CONCESSIONE, OnCheckConcessione)
	ON_BN_CLICKED(IDC_CHECK_GEOLOGIA, OnCheckGeologia)
	ON_CBN_SELCHANGE(IDC_COMBO_CERTIFICATO2, OnSelchangeComboCertificato2)
	ON_CBN_SELCHANGE(IDC_COMBO_CERTIFICATO3, OnSelchangeComboCertificato3)
	ON_CBN_SELCHANGE(IDC_COMBO_CERTIFICATO4, OnSelchangeComboCertificato4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServiziListinoDlg message handlers

BOOL CServiziListinoDlg::OnInitDialog() 
{
	int n,n2,n3,n4;
	CString str, strMask;

	CDialog::OnInitDialog();


  if(m_strID.IsEmpty())
	  SetWindowText("Inserimento nuovo servizio");
	else
	  SetWindowText("Modifica servizio");
	/*--- riempio la lista degli ID ----*/
	for(n = 0; n < m_aryStrId.GetSize(); n++)
	  m_ComboID.AddString(m_aryStrId[n]);
	if(m_strID.IsEmpty())
		m_ComboID.SetCurSel(0);
  else
	  m_ComboID.SelectString(-1, m_strID);
	/*---- riempio la combo della modalita' di emissione ----*/
	n = m_ComboEmissione.AddString("Nessuna");
	m_ComboEmissione.SetItemData(n, NON_EMISSIONE);
	n = m_ComboEmissione.AddString("Solo emissione");
	m_ComboEmissione.SetItemData(n, EMISSIONE);
	n = m_ComboEmissione.AddString("Compresa");
	m_ComboEmissione.SetItemData(n, INCLUDE_EMISSIONE);

	for(int e = 0; e < m_ComboEmissione.GetCount(); e++)
		if(m_nEmissione == (int)m_ComboEmissione.GetItemData(e))
			m_ComboEmissione.SetCurSel(e);
		
  /*--- riempio la lista dei tipi di certificato (carico gli elementi nelle 2 combo)---*/
	n = m_ComboCertificato.AddString("--- Nessuno ----");
	m_ComboCertificato.SetItemData(n, 0);
	m_ComboCertificato.SetCurSel(n);

	n2 = m_ComboCertificato2.AddString("--- Nessuno ----");
	m_ComboCertificato2.SetItemData(n2, 0);
	m_ComboCertificato2.SetCurSel(n2);

	n3 = m_ComboCertificato3.AddString("--- Nessuno ----");
	m_ComboCertificato3.SetItemData(n3, 0);
	m_ComboCertificato3.SetCurSel(n3);

	n4 = m_ComboCertificato4.AddString("--- Nessuno ----");
	m_ComboCertificato4.SetItemData(n4, 0);
	m_ComboCertificato4.SetCurSel(n4);

	for(;
	    !m_pTCertificatiSet->IsBOF() && !m_pTCertificatiSet->IsEOF();
		  m_pTCertificatiSet->MoveNext())
	{
    n = m_ComboCertificato.AddString	(m_pTCertificatiSet->m_Nome);
    n2= m_ComboCertificato2.AddString	(m_pTCertificatiSet->m_Nome);
		n3= m_ComboCertificato3.AddString	(m_pTCertificatiSet->m_Nome);
		n4= m_ComboCertificato4.AddString	(m_pTCertificatiSet->m_Nome);
		
    m_ComboCertificato.SetItemData	(n,		m_pTCertificatiSet->m_Codice);
    m_ComboCertificato2.SetItemData	(n2,	m_pTCertificatiSet->m_Codice);
		m_ComboCertificato3.SetItemData	(n3,	m_pTCertificatiSet->m_Codice);
		m_ComboCertificato4.SetItemData	(n4,	m_pTCertificatiSet->m_Codice);
		
    if(m_nCertificato == m_pTCertificatiSet->m_Codice)
		  m_ComboCertificato.SetCurSel(n);

    if(m_nCertificato2 == m_pTCertificatiSet->m_Codice)
		  m_ComboCertificato2.SetCurSel(n2);

		if(m_nCertificato3 == m_pTCertificatiSet->m_Codice)
		  m_ComboCertificato3.SetCurSel(n3);

		if(m_nCertificato4 == m_pTCertificatiSet->m_Codice)
		  m_ComboCertificato4.SetCurSel(n4);
	}

	if(m_nCertificato)
	{
    OnSelchangeComboCertificato();
  	if(m_byProve & 0x01)
      m_bProvaA = TRUE;
  	if(m_byProve & 0x02)
      m_bProvaB = TRUE;
	}
	else
	{
  	m_CheckProvaA.EnableWindow(FALSE);
    m_CheckProvaB.EnableWindow(FALSE);
	}

	if(m_nCertificato2)
	{
    OnSelchangeComboCertificato2();
  	if(m_byProve2 & 0x01)
      m_bProvaA2 = TRUE;
  	if(m_byProve2 & 0x02)
      m_bProvaB2 = TRUE;
	}
	else
	{
  	m_CheckProvaA2.EnableWindow(FALSE);
    m_CheckProvaB2.EnableWindow(FALSE);
	}

	if(m_nCertificato3)
	{
    OnSelchangeComboCertificato3();
  	if(m_byProve3 & 0x01)
      m_bProvaA3 = TRUE;
  	if(m_byProve3 & 0x02)
      m_bProvaB3 = TRUE;
	}
	else
	{
  	m_CheckProvaA3.EnableWindow(FALSE);
    m_CheckProvaB3.EnableWindow(FALSE);
	}

	if(m_nCertificato4)
	{
    OnSelchangeComboCertificato4();
  	if(m_byProve4 & 0x01)
      m_bProvaA4= TRUE;
  	if(m_byProve4 & 0x02)
      m_bProvaB4 = TRUE;
	}
	else
	{
  	m_CheckProvaA4.EnableWindow(FALSE);
    m_CheckProvaB4.EnableWindow(FALSE);
	}

	n = m_ComboCertificato.GetCurSel();
	if(m_ComboCertificato.GetItemData(n) == 0)
	{
		m_ComboCertificato2.EnableWindow(FALSE);
		m_ComboCertificato3.EnableWindow(FALSE);
		m_ComboCertificato4.EnableWindow(FALSE);
	}
	/*---- riempio la combo della modalità di gestione del servizio aggiuntivo ----*/
	n = m_ComboAggiuntivo.AddString("Non aggiungibile");
	m_ComboAggiuntivo.SetItemData(n, NON_AGGIUNTIVO);
	n = m_ComboAggiuntivo.AddString("Aggiungibile");
	m_ComboAggiuntivo.SetItemData(n, AGGIUNTIVO);
	n = m_ComboAggiuntivo.AddString("Comprensivo");
	m_ComboAggiuntivo.SetItemData(n, COMPRENSIVO);

	for(n=0; n < m_ComboAggiuntivo.GetCount(); n++)
		if(m_nAggiuntivo== (int)m_ComboAggiuntivo.GetItemData(n) )
			m_ComboAggiuntivo.SetCurSel(n);


	m_ComboAggiuntivo.SetCurSel(m_nAggiuntivo);
	/*---- inizializzo gli altri campi ----*/
	if(m_fPrezzo != DBL_MAX)
	{
		Valuta prezzo(m_fPrezzo);
		str = prezzo.Format(6);
    strMask = m_MskEditPrezzo.GetMask();
    strMask = strMask.Left(strMask.GetLength() - str.GetLength());
    strMask.Replace("#", m_MskEditPrezzo.GetPromptChar());
    strMask.Replace(',', '.');
    strMask = strMask + str;
    m_MskEditPrezzo.SetText(strMask);
  }

	m_strNProvini.Format("%d", m_nProvini);
  m_strProviniPerSerie.Format("%d", m_nProviniPerSerie);
	UpdateData(FALSE);

	// Gestione dei campi per serie e per provino in base al valore di m_nPerSerie
	// e del numero provini

	if(m_nPerSerie == 0)
	{
		m_BtnPerProvino.SetCheck(TRUE);
		m_BtnPerSerie.SetCheck(FALSE);
		m_bPerProvino = TRUE;
		m_bPerSerie = FALSE;
	}
	else if(m_nPerSerie == 1)
	{
		m_BtnPerProvino.SetCheck(FALSE);
		m_BtnPerSerie.SetCheck(TRUE);
		m_bPerSerie = TRUE;
		m_bPerProvino = FALSE;
	}
	m_EditNProvini.EnableWindow(m_bPerSerie);
	
//-------------------------------------------------------------//

	return TRUE;
}

void CServiziListinoDlg::OnSelchangeComboCertificato() 
{
	int n = m_ComboCertificato.GetCurSel();

	m_CheckProvaA.SetWindowText("");
	m_CheckProvaA.SetCheck(0);
  m_CheckProvaA.EnableWindow(FALSE);
	m_CheckProvaB.SetWindowText("");
	m_CheckProvaB.SetCheck(0);
  m_CheckProvaB.EnableWindow(FALSE);
  m_ComboAggiuntivo.EnableWindow(FALSE);
	m_ComboAggiuntivo.SetCurSel(-1);
	if(n = m_ComboCertificato.GetItemData(n))
	{
	  /*---- cerco il tipo selezionato ----*/
		for(!m_pTCertificatiSet->IsBOF() ? m_pTCertificatiSet->MoveFirst(): 0;
				!m_pTCertificatiSet->IsEOF();
				m_pTCertificatiSet->MoveNext())
			if(m_pTCertificatiSet->m_Codice == n)
			  break;
		/*---- imposto i check delle prove ----*/
		if(!m_pTCertificatiSet->m_ProvaA.IsEmpty())
		{
		  m_CheckProvaA.SetWindowText(m_pTCertificatiSet->m_ProvaA);
      m_CheckProvaA.EnableWindow();
		}
		if(!m_pTCertificatiSet->m_ProvaB.IsEmpty())
		{
		  m_CheckProvaB.SetWindowText(m_pTCertificatiSet->m_ProvaB);
      m_CheckProvaB.EnableWindow();
		}
    m_ComboAggiuntivo.EnableWindow();
	  m_ComboAggiuntivo.SetCurSel(0);
	}

  
  /*---- Gestione delle tre Combo per l'assegnazione del tipo di certificato ----*/
  int n2 = m_ComboCertificato2.GetCurSel();
  n = m_ComboCertificato.GetCurSel();
  if(m_ComboCertificato.GetItemData(n) != 0)
    m_ComboCertificato2.EnableWindow(TRUE);
  else if ((m_ComboCertificato.GetItemData(n) == 0) && (m_ComboCertificato2.GetItemData(n2) == 0))
    m_ComboCertificato2.EnableWindow(FALSE);
}



void CServiziListinoDlg::OnSelchangeComboCertificato2() 
{
	int n2 = m_ComboCertificato2.GetCurSel();

	m_CheckProvaA2.SetWindowText("");
	m_CheckProvaA2.SetCheck(0);
    m_CheckProvaA2.EnableWindow(FALSE);
 	m_CheckProvaB2.SetWindowText("");
	m_CheckProvaB2.SetCheck(0);
    m_CheckProvaB2.EnableWindow(FALSE);

	if(n2 = m_ComboCertificato2.GetItemData(n2))
	{
	  /*---- cerco il tipo selezionato ----*/
		for(!m_pTCertificatiSet->IsBOF() ? m_pTCertificatiSet->MoveFirst(): 0;
				!m_pTCertificatiSet->IsEOF();
				m_pTCertificatiSet->MoveNext())
			if(m_pTCertificatiSet->m_Codice == n2)
			  break;
		/*---- imposto i check delle prove ----*/
		if(!m_pTCertificatiSet->m_ProvaA.IsEmpty())
		{
		  m_CheckProvaA2.SetWindowText(m_pTCertificatiSet->m_ProvaA);
      m_CheckProvaA2.EnableWindow();
		}
		if(!m_pTCertificatiSet->m_ProvaB.IsEmpty())
		{
		  m_CheckProvaB2.SetWindowText(m_pTCertificatiSet->m_ProvaB);
      m_CheckProvaB2.EnableWindow();
		}
	}

  /*---- Gestione delle tre Combo per l'assegnazione del tipo di certificato ----*/
  int n3 = m_ComboCertificato3.GetCurSel();
  n2 = m_ComboCertificato2.GetCurSel();
  if(m_ComboCertificato2.GetItemData(n2) != 0)
    m_ComboCertificato3.EnableWindow(TRUE);
  if ((m_ComboCertificato.GetItemData(n2) == 0) && (m_ComboCertificato3.GetItemData(n3) == 0))
    m_ComboCertificato3.EnableWindow(FALSE);
}

void CServiziListinoDlg::OnSelchangeComboCertificato3() 
{
	int n3 = m_ComboCertificato3.GetCurSel();

	m_CheckProvaA3.SetWindowText("");
	m_CheckProvaA3.SetCheck(0);
    m_CheckProvaA3.EnableWindow(FALSE);
	m_CheckProvaB3.SetWindowText("");
	m_CheckProvaB3.SetCheck(0);
    m_CheckProvaB3.EnableWindow(FALSE);

	if(n3 = m_ComboCertificato3.GetItemData(n3))
	{
	  /*---- cerco il tipo selezionato ----*/
		for(!m_pTCertificatiSet->IsBOF() ? m_pTCertificatiSet->MoveFirst(): 0;
				!m_pTCertificatiSet->IsEOF();
				m_pTCertificatiSet->MoveNext())
			if(m_pTCertificatiSet->m_Codice == n3)
			  break;
		/*---- imposto i check delle prove ----*/
		if(!m_pTCertificatiSet->m_ProvaA.IsEmpty())
		{
		  m_CheckProvaA3.SetWindowText(m_pTCertificatiSet->m_ProvaA);
		  m_CheckProvaA3.EnableWindow();
		}
		if(!m_pTCertificatiSet->m_ProvaB.IsEmpty())
		{
		  m_CheckProvaB3.SetWindowText(m_pTCertificatiSet->m_ProvaB);
          m_CheckProvaB3.EnableWindow();
		}
	}

	/*---- Gestione delle tre Combo per l'assegnazione del tipo di certificato ----*/
  int n4 = m_ComboCertificato4.GetCurSel();
  n3 = m_ComboCertificato3.GetCurSel();
  if(m_ComboCertificato3.GetItemData(n3) != 0)
    m_ComboCertificato4.EnableWindow(TRUE);
  if ((m_ComboCertificato.GetItemData(n3) == 0) && (m_ComboCertificato4.GetItemData(n4) == 0))
    m_ComboCertificato4.EnableWindow(FALSE);
}

void CServiziListinoDlg::OnSelchangeComboCertificato4() 
{
	int n4 = m_ComboCertificato4.GetCurSel();

	m_CheckProvaA4.SetWindowText("");
	m_CheckProvaA4.SetCheck(0);
  m_CheckProvaA4.EnableWindow(FALSE);
	m_CheckProvaB4.SetWindowText("");
	m_CheckProvaB4.SetCheck(0);
  m_CheckProvaB4.EnableWindow(FALSE);

	if(n4 = m_ComboCertificato4.GetItemData(n4))
	{
	  /*---- cerco il tipo selezionato ----*/
		for(!m_pTCertificatiSet->IsBOF() ? m_pTCertificatiSet->MoveFirst(): 0;
				!m_pTCertificatiSet->IsEOF();
				m_pTCertificatiSet->MoveNext())
			if(m_pTCertificatiSet->m_Codice == n4)
			  break;
		/*---- imposto i check delle prove ----*/
		if(!m_pTCertificatiSet->m_ProvaA.IsEmpty())
		{
		  m_CheckProvaA4.SetWindowText(m_pTCertificatiSet->m_ProvaA);
		  m_CheckProvaA4.EnableWindow();
		}
		if(!m_pTCertificatiSet->m_ProvaB.IsEmpty())
		{
		  m_CheckProvaB4.SetWindowText(m_pTCertificatiSet->m_ProvaB);
          m_CheckProvaB4.EnableWindow();
		}
	}	
}

void CServiziListinoDlg::OnOK() 
{
  int n,n2,n3,n4;
 
  if(!ValidateData())
	return;

  /*---- emissione, aggiungibile ----*/
  m_nEmissione = m_ComboEmissione.GetItemData( m_ComboEmissione.GetCurSel() );
  m_nAggiuntivo = m_ComboAggiuntivo.GetItemData( m_ComboAggiuntivo.GetCurSel() );
  /*--- certificato e prove ---*/
  m_byProve  = 0;
  m_byProve2 = 0;
  m_byProve3 = 0;
  n  = m_ComboCertificato.GetCurSel();
  n2 = m_ComboCertificato2.GetCurSel();
  n3 = m_ComboCertificato3.GetCurSel();
	n4 = m_ComboCertificato4.GetCurSel();
  if(n >= 0)
	{
	  m_nCertificato = m_ComboCertificato.GetItemData(n);
		if(m_bProvaA)
			m_byProve |= 0x01;
		if(m_bProvaB)
			m_byProve |= 0x02;
	}
  if(n2 >= 0)
	{
	  m_nCertificato2 = m_ComboCertificato2.GetItemData(n2);
		if(m_bProvaA2)
			m_byProve2 |= 0x01;
		if(m_bProvaB2)
			m_byProve2 |= 0x02;
	}
  if(n3 >= 0)
	{
	  m_nCertificato3 = m_ComboCertificato3.GetItemData(n3);
		if(m_bProvaA3)
			m_byProve3 |= 0x01;
		if(m_bProvaB3)
			m_byProve3 |= 0x02;
	}
	if(n4 >= 0)
	{
	  m_nCertificato4 = m_ComboCertificato4.GetItemData(n4);
		if(m_bProvaA4)
			m_byProve4 |= 0x01;
		if(m_bProvaB4)
			m_byProve4 |= 0x02;
	}
	/*---- prezzo ----*/
  CString str = m_MskEditPrezzo.GetText();
  str.Remove('.');
  str.TrimLeft(" _");
  str.Replace(',', '.');
  if(str.FindOneOf("0123456789") < 0)
	  m_fPrezzo = DBL_MAX;
  else
	  m_fPrezzo = atof(str);
  /*----- campioni ----*/
  m_nProvini = atoi(m_strNProvini);
  m_nProviniPerSerie = atoi(m_strProviniPerSerie);
  CDialog::OnOK();
}

/*
void CServiziListinoDlg::OnRadioPerprovino() 
{
  UpdateData();
	m_nProvini = 1;
	m_strNProvini = "1";
	UpdateData(FALSE);
	m_EditNProvini.EnableWindow(FALSE);
}

void CServiziListinoDlg::OnRadioPerserie() 
{
	m_EditNProvini.EnableWindow();
}
*/

void CServiziListinoDlg::OnSelchangeComboEmissione() 
{
  int n = m_ComboEmissione.GetItemData(m_ComboEmissione.GetCurSel());

	UpdateData();
	switch(n)
	{
	  case 1:
			/*--- servizio di sola emissione ----*/
			m_CheckProvaA.SetWindowText("");
			m_CheckProvaA.EnableWindow(FALSE);
			m_CheckProvaB.SetWindowText("");
			m_CheckProvaB.EnableWindow(FALSE);
			m_bProvaA = FALSE;
			m_bProvaB = FALSE;
			m_ComboCertificato.SetCurSel(-1);
			m_ComboCertificato.EnableWindow(FALSE);
			m_strNProvini.Empty();
			m_EditNProvini.EnableWindow(FALSE);
			m_BtnPerProvino.EnableWindow(FALSE);
			m_BtnPerSerie.EnableWindow(FALSE);
			m_bPerSerie			= FALSE;
			m_bPerProvino		= FALSE;
			m_strCommentoMateriale.Empty();
			m_bConcessione	= FALSE;
			m_EdtCommento.EnableWindow(FALSE);
			m_EdtConcessione.EnableWindow(FALSE);
			m_BtnGeologia.EnableWindow(FALSE);
		  break;
		case 0:
		    /*---- nessuna emissione ----*/
			m_CheckProvaA.EnableWindow(TRUE);
			m_CheckProvaB.EnableWindow(TRUE);
			m_ComboCertificato.SetCurSel(0);
			m_ComboCertificato.EnableWindow(TRUE);
			m_CheckProvaA.EnableWindow(FALSE);
			m_CheckProvaB.EnableWindow(FALSE);
			m_BtnPerProvino.EnableWindow(TRUE);
			m_BtnPerSerie.EnableWindow(TRUE);
			m_EdtCommento.EnableWindow(TRUE);
			m_EdtConcessione.EnableWindow(TRUE);
			m_BtnGeologia.EnableWindow(TRUE);
      break;
		case 2:
		  /*---- servizio comprensivo di emissione -----*/
			m_CheckProvaA.EnableWindow(TRUE);
			m_CheckProvaB.EnableWindow(TRUE);
			m_ComboCertificato.SetCurSel(0);
			m_CheckProvaA.EnableWindow(FALSE);
			m_CheckProvaB.EnableWindow(FALSE);
			m_ComboCertificato.EnableWindow(TRUE);
			m_BtnPerProvino.EnableWindow(TRUE);
			m_BtnPerSerie.EnableWindow(TRUE);
			m_EdtCommento.EnableWindow(TRUE);
			m_EdtConcessione.EnableWindow(TRUE);
			m_BtnGeologia.EnableWindow(TRUE);
		default:
		  break;
	}
	UpdateData(FALSE);
}

void CServiziListinoDlg::OnCheckPerserie() 
{
	m_bPerSerie = m_BtnPerSerie.GetCheck();
	m_EditNProvini.EnableWindow(m_bPerSerie);
	if(m_bPerSerie)
	{
		m_BtnPerProvino.SetCheck(FALSE);
		m_nPerSerie	= 1; 
	}
	else
	{
		m_nPerSerie	= 2; 
	}
}

void CServiziListinoDlg::OnCheckPerprovino() 
{
	m_bPerProvino = m_BtnPerProvino.GetCheck();
	if(m_bPerProvino)
	{
		m_EditNProvini.EnableWindow(FALSE);
		m_BtnPerSerie.SetCheck(FALSE);
		m_nPerSerie	= 0; 
	}
	else
	{
		m_nPerSerie	= 2; 
	}
}

BOOL CServiziListinoDlg::ValidateData()
{
	UpdateData();
	m_nProvini = atoi(m_strNProvini);
	if(m_nPerSerie == 1 && m_nProvini < 1)
	{
		AfxMessageBox("Il numero di provini inseriti non è coerente");
		return FALSE;
	}

	int n4 = m_ComboCertificato4.GetCurSel();
  int n3 = m_ComboCertificato3.GetCurSel();
  int n2 = m_ComboCertificato2.GetCurSel();
  int n  = m_ComboCertificato.GetCurSel();
  if ((m_ComboCertificato.GetItemData(n) == 0)		&& 
			(m_ComboCertificato2.GetItemData(n2) != 0)	&& 
			(m_ComboCertificato3.GetItemData(n3) != 0)	&&
			(m_ComboCertificato4.GetItemData(n4) != 0))
  {
    AfxMessageBox("Non si può assegnare un secondo tipo di certificato se il primo non è stato assegnato!", MB_OK | MB_ICONEXCLAMATION);
    return FALSE;
  }
	return TRUE;
}

void CServiziListinoDlg::OnCheckConcessione() 
{
  UpdateData();
  m_bConcessione = m_EdtConcessione.GetCheck();
  if(m_bConcessione)
  {
    m_bGeologia = 0;
    m_BtnGeologia.SetCheck(0);
  }
  UpdateData(FALSE);
}

void CServiziListinoDlg::OnCheckGeologia() 
{
  UpdateData();
  m_bGeologia= m_BtnGeologia.GetCheck();
  if(m_bGeologia)
  {
    m_bConcessione = 0;
    m_EdtConcessione.SetCheck(0);
  }
  UpdateData(FALSE);
}