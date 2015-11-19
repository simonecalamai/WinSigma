// TipiMaterialeView.cpp : implementation file
//

#include "stdafx.h"
#include "bmobject.h"
#include "xbmpcontrol.h"
#include "winsigma.h"
#include "winsigmadoc.h"
#include "XFormView.h"
#include "TipiMaterialeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTipiMaterialeView

IMPLEMENT_DYNCREATE(CTipiMaterialeView, CFormView)

CTipiMaterialeView::CTipiMaterialeView()
	: CXFormView(CTipiMaterialeView::IDD)
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

	//{{AFX_DATA_INIT(CTipiMaterialeView)
	m_strCodice = _T("");
	m_strDescrizione = _T("");
	m_strNome = _T("");
	m_bPredefinito = FALSE;
	m_lfSnervamento = 0.0;
	//}}AFX_DATA_INIT
	m_pTCertificatiSet = new CTipiCertificatoSet(&pApp->m_db);
	m_pTCertificatiSet->Open();
	//Carico i materiali che sono stati settati per comparire di default
	// per poterli velocemente sostituire nel caso di un nuovo inserimento di default
	m_pMatPredSet = new CTipiMaterialeSet(&pApp->m_db);
	m_pMatPredSet->m_strFilter = "DiDefault = 1";
	m_pMatPredSet->Open();
}

CTipiMaterialeView::~CTipiMaterialeView()
{
  if(m_pTCertificatiSet)
	{
	  m_pTCertificatiSet->Close();
		delete m_pTCertificatiSet;
	}
	if(m_pMatPredSet)
	{
	  m_pMatPredSet->Close();
		delete m_pMatPredSet;
	}
}

void CTipiMaterialeView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTipiMaterialeView)
	DDX_Control(pDX, IDC_COMBO_TIPOCERTIFICATO4, m_ComboCertificato4);
	DDX_Control(pDX, IDC_COMBO_TIPOCERTIFICATO3, m_ComboCertificato3);
	DDX_Control(pDX, IDC_COMBO_TIPOCERTIFICATO2, m_ComboCertificato2);
	DDX_Control(pDX, IDC_BUTTON_QUADRI, m_BtnQuadro);
	DDX_Control(pDX, IDC_EDIT_SNERVAMENTO, m_EdtSnervamento);
	DDX_Control(pDX, IDC_EDIT_CODICE, m_EdtCodice);
	DDX_Control(pDX, IDC_CHECK_PREDEFINITO, m_BtnPredefinito);
	DDX_Control(pDX, IDC_COMBO_TIPOCERTIFICATO, m_ComboCertificato);
	DDX_Control(pDX, IDC_EDIT_NOME, m_EditNome);
	DDX_Control(pDX, IDC_EDIT_DESCRIZIONE, m_EditDescrizione);
	DDX_Text(pDX, IDC_EDIT_CODICE, m_strCodice);
	DDX_Text(pDX, IDC_EDIT_DESCRIZIONE, m_strDescrizione);
	DDV_MaxChars(pDX, m_strDescrizione, 250);
	DDX_Text(pDX, IDC_EDIT_NOME, m_strNome);
	DDV_MaxChars(pDX, m_strNome, 32);
	DDX_Check(pDX, IDC_CHECK_PREDEFINITO, m_bPredefinito);
	DDX_Text(pDX, IDC_EDIT_SNERVAMENTO, m_lfSnervamento);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTipiMaterialeView, CXFormView)
	//{{AFX_MSG_MAP(CTipiMaterialeView)
	ON_BN_CLICKED(IDC_BUTTON_SFOGLIA, OnButtonSfoglia)
	ON_BN_CLICKED(IDC_BUTTON_QUADRI, OnButtonQuadri)
	ON_COMMAND(ID_BUTTON_AGGIORNA, OnButtonAggiorna)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CTipiMaterialeView::LoadCurRecord(BOOL bData)
{
  int i;
  CBMPObject bmp;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  char bfr[200];

  if(bData)
	{
		m_bPredefinito		= m_pSet->m_DiDefault;
		m_strCodice			= m_pSet->m_ID;
		m_strNome			= m_pSet->m_Nome;
		m_strDescrizione	= m_pSet->m_Descrizione;
		strcpy(bfr, m_strDescrizione);
		m_lfSnervamento		= m_pSet->m_Snervamento;
		
    for(i = 0; i < m_ComboCertificato.GetCount(); i++)
		if(m_ComboCertificato.GetItemData(i) == (DWORD)m_pSet->m_TipoCertificato)
			  break;
		if(i < m_ComboCertificato.GetCount())
		  m_ComboCertificato.SetCurSel(i);


	for(i = 0; i < m_ComboCertificato2.GetCount(); i++)
		if(m_ComboCertificato2.GetItemData(i) == (DWORD)m_pSet->m_TipoCertificato2)
			  break;
		if(i < m_ComboCertificato2.GetCount())
		  m_ComboCertificato2.SetCurSel(i);

	for(i = 0; i < m_ComboCertificato3.GetCount(); i++)
		if(m_ComboCertificato3.GetItemData(i) == (DWORD)m_pSet->m_TipoCertificato3)
			  break;
		if(i < m_ComboCertificato3.GetCount())
		  m_ComboCertificato3.SetCurSel(i);

	for(i = 0; i < m_ComboCertificato4.GetCount(); i++)
		if(m_ComboCertificato4.GetItemData(i) == (DWORD)m_pSet->m_TipoCertificato4)
			  break;
		if(i < m_ComboCertificato4.GetCount())
		  m_ComboCertificato4.SetCurSel(i);
  }
	else
	{
		m_bPredefinito = FALSE;
		m_strCodice.Empty();
		m_strNome.Empty();
		m_strDescrizione.Empty();
		m_ComboCertificato.SetCurSel(-1);
		m_ComboCertificato2.SetCurSel(-1);
		m_ComboCertificato3.SetCurSel(-1);
		m_ComboCertificato4.SetCurSel(-1);
  }
}

BOOL CTipiMaterialeView::IsDataChanged()
{
  int n  = m_ComboCertificato.GetCurSel();

  int n2 = m_ComboCertificato2.GetCurSel();

  int n3 = m_ComboCertificato3.GetCurSel();

	int n4 = m_ComboCertificato4.GetCurSel();

  if(m_strNome          != m_pSet->m_Nome
		|| m_strCodice			!= m_pSet->m_ID
		|| m_lfSnervamento	!= m_pSet->m_Snervamento
		|| m_bPredefinito   != m_pSet->m_DiDefault
		|| m_strDescrizione != m_pSet->m_Descrizione
		|| (n >= 0 && m_ComboCertificato.GetItemData(n) != (DWORD)m_pSet->m_TipoCertificato))
		return TRUE;

    if(m_strNome        != m_pSet->m_Nome
		|| m_strCodice			!= m_pSet->m_ID
		|| m_lfSnervamento	!= m_pSet->m_Snervamento
		|| m_bPredefinito   != m_pSet->m_DiDefault
		|| m_strDescrizione != m_pSet->m_Descrizione
		|| (n2 >= 0 && m_ComboCertificato2.GetItemData(n2) != (DWORD)m_pSet->m_TipoCertificato2))
		return TRUE;

	if(m_strNome        != m_pSet->m_Nome
		|| m_strCodice			!= m_pSet->m_ID
		|| m_lfSnervamento	!= m_pSet->m_Snervamento
		|| m_bPredefinito   != m_pSet->m_DiDefault
		|| m_strDescrizione != m_pSet->m_Descrizione
		|| (n3 >= 0 && m_ComboCertificato3.GetItemData(n3) != (DWORD)m_pSet->m_TipoCertificato3))
		return TRUE;
  
	if(m_strNome        != m_pSet->m_Nome
		|| m_strCodice			!= m_pSet->m_ID
		|| m_lfSnervamento	!= m_pSet->m_Snervamento
		|| m_bPredefinito   != m_pSet->m_DiDefault
		|| m_strDescrizione != m_pSet->m_Descrizione
		|| (n4 >= 0 && m_ComboCertificato4.GetItemData(n4) != (DWORD)m_pSet->m_TipoCertificato4))
		return TRUE;

  return FALSE;
}

BOOL CTipiMaterialeView::ValidateData()
{
  if(m_strNome.GetLength() < 2)
	{
	  AfxMessageBox("La lunghezza del nome deve essere di almeno due lettere");
	  return FALSE;
	}
	return TRUE;
}

BOOL CTipiMaterialeView::NewRecord()
{
  int n;
  int n2;
  int n3;
	int n4;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

	if(!ValidateData())
	  return FALSE;

	m_strCodice.TrimLeft();
	m_strCodice.TrimRight();
	m_strCodice.MakeUpper();
	byte codValido = TRUE;
	long corrente = m_pSet->m_Codice;
	for(SET_START(m_pSet); !m_pSet->IsEOF(); m_pSet->MoveNext() )
		if(m_pSet->m_ID == m_strCodice)
			codValido = FALSE;
	if(!codValido)
	{
	  AfxMessageBox("Il codice scelto non è utilizzabile in quanto già presente nel database");
	  return FALSE;
	}

	m_pSet->AddNew();
	m_pSet->m_DiDefault		= m_bPredefinito;
	m_pSet->m_Nome			= m_strNome;
	m_pSet->m_Descrizione	= m_strDescrizione;
	m_pSet->m_ID			= m_strCodice;
	m_pSet->m_Snervamento	= m_lfSnervamento;
  if((n = m_ComboCertificato.GetCurSel()) < 0)
		m_pSet->m_TipoCertificato = 0;
	else
		m_pSet->m_TipoCertificato  = m_ComboCertificato.GetItemData(n);

  if((n2 = m_ComboCertificato2.GetCurSel()) < 0)
		m_pSet->m_TipoCertificato2 = 0;
	else
		m_pSet->m_TipoCertificato2  = m_ComboCertificato2.GetItemData(n2);
	
  if((n3 = m_ComboCertificato3.GetCurSel()) < 0)
		m_pSet->m_TipoCertificato3 = 0;
	else
		m_pSet->m_TipoCertificato3  = m_ComboCertificato3.GetItemData(n3);

	if((n4 = m_ComboCertificato4.GetCurSel()) < 0)
		m_pSet->m_TipoCertificato4 = 0;
	else
		m_pSet->m_TipoCertificato4  = m_ComboCertificato4.GetItemData(n4);

  m_pSet->Update();
  m_pSet->Requery();	
  pApp->ReloadTree(TREELABEL_MATERIALI, -1);
	
  return TRUE;
}

BOOL CTipiMaterialeView::SaveRecord()
{
  int n;
  int n2;
  int n3;
	int n4;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

	if(!ValidateData())
	  return FALSE;
  switch(AfxMessageBox("Salvare le modifiche ai dati?", MB_YESNOCANCEL))
	{
	  case IDYES:
			//Forzo a zero l'eventuale materiale settato precedentemente
			if(m_pSet->m_DiDefault == 0 && m_bPredefinito)
				for(SET_START(m_pMatPredSet); !m_pMatPredSet->IsEOF(); m_pMatPredSet->MoveNext() )
					if(m_pMatPredSet->m_TipoCertificato == m_pSet->m_TipoCertificato )
					{
						m_pMatPredSet->Edit();
						m_pMatPredSet->m_DiDefault = 0;
						m_pMatPredSet->Update();
					}
			m_pMatPredSet->Requery();

  	  m_pSet->Edit();
			m_pSet->m_DiDefault		= m_bPredefinito;
			m_pSet->m_Nome			= m_strNome;
			m_pSet->m_Descrizione	= m_strDescrizione;
			m_pSet->m_ID			= m_strCodice;
			m_pSet->m_Snervamento	= m_lfSnervamento;
      
      if((n = m_ComboCertificato.GetCurSel()) < 0)
			  m_pSet->m_TipoCertificato = 0;
			else
			  m_pSet->m_TipoCertificato  = m_ComboCertificato.GetItemData(n);
	    
      if((n2 = m_ComboCertificato2.GetCurSel()) < 0)
			  m_pSet->m_TipoCertificato2 = 0;
			else
			  m_pSet->m_TipoCertificato2  = m_ComboCertificato2.GetItemData(n2);

	  if((n3 = m_ComboCertificato3.GetCurSel()) < 0)
		  m_pSet->m_TipoCertificato3 = 0;
		else
		  m_pSet->m_TipoCertificato3  = m_ComboCertificato3.GetItemData(n3);

		if((n4 = m_ComboCertificato4.GetCurSel()) < 0)
		  m_pSet->m_TipoCertificato4 = 0;
		else
		  m_pSet->m_TipoCertificato4  = m_ComboCertificato4.GetItemData(n4);
      
      m_pSet->Update();
      m_pSet->Requery();
	  pApp->ReloadTree(TREELABEL_MATERIALI, m_pSet->m_Codice);
		  break;
	case IDNO:
		  break;
	default:
		  return FALSE;
	}
	return TRUE;
}

BOOL CTipiMaterialeView::DeleteRecord()
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CString str;

  if(!m_pSet->IsBOF())
	{
		str.Format("Eliminare il tipo di materiale %s (Codice %s)?",
							 m_strNome, m_strCodice);

		if(AfxMessageBox(str, MB_YESNO) == IDYES)
		{
			m_pSet->Delete();
	    pApp->ReloadTree(TREELABEL_MATERIALI, -1);
    	return TRUE;
		}
    return FALSE;
	}
	return FALSE;
}

void CTipiMaterialeView::EnableControls(BOOL bEditMode)
{
	m_BtnQuadro.EnableWindow(bEditMode);
	m_EditNome.EnableWindow(bEditMode);
	m_EditDescrizione.EnableWindow(bEditMode);
	m_ComboCertificato.EnableWindow(bEditMode);
	m_ComboCertificato2.EnableWindow(bEditMode);
	m_ComboCertificato3.EnableWindow(bEditMode);
	m_ComboCertificato4.EnableWindow(bEditMode);
	m_EdtCodice.EnableWindow(bEditMode);
	m_BtnPredefinito.EnableWindow(bEditMode);
	m_EdtSnervamento.EnableWindow(bEditMode);
	m_EditNome.SetFocus();
}

/////////////////////////////////////////////////////////////////////////////
// CTipiMaterialeView diagnostics

#ifdef _DEBUG
void CTipiMaterialeView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTipiMaterialeView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTipiMaterialeView message handlers

void CTipiMaterialeView::OnInitialUpdate() 
{
	int n;
	int n2;
	int n3;
	int n4;
	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
	m_pSet = pDoc->m_pTipiMaterialeSet;
	
	CXFormView::m_pSet = m_pSet;

	CXFormView::OnInitialUpdate();
	/*--- riempio la combo dei tipi di certificato ---*/
	n = m_ComboCertificato.AddString("--- Nessuno ----");
	n2 = m_ComboCertificato2.AddString("--- Nessuno ----");
	n3 = m_ComboCertificato3.AddString("--- Nessuno ----");
	n4 = m_ComboCertificato4.AddString("--- Nessuno ----");
	
	m_ComboCertificato.SetItemData(n, 0);
	m_ComboCertificato.SetCurSel(n);

  m_ComboCertificato2.SetItemData(n2, 0);
	m_ComboCertificato2.SetCurSel(n2);

	m_ComboCertificato3.SetItemData(n3, 0);
	m_ComboCertificato3.SetCurSel(n3);
		
	m_ComboCertificato4.SetItemData(n4, 0);
	m_ComboCertificato4.SetCurSel(n4);

	for(;
	    !m_pTCertificatiSet->IsBOF() && !m_pTCertificatiSet->IsEOF();
		  m_pTCertificatiSet->MoveNext())
	{
    n = m_ComboCertificato.AddString(m_pTCertificatiSet->m_Nome);
		m_ComboCertificato.SetItemData(n, m_pTCertificatiSet->m_Codice);

    n2 = m_ComboCertificato2.AddString(m_pTCertificatiSet->m_Nome);
		m_ComboCertificato2.SetItemData(n2, m_pTCertificatiSet->m_Codice);

		n3 = m_ComboCertificato3.AddString(m_pTCertificatiSet->m_Nome);
		m_ComboCertificato3.SetItemData(n3, m_pTCertificatiSet->m_Codice);

		n4 = m_ComboCertificato4.AddString(m_pTCertificatiSet->m_Nome);
		m_ComboCertificato4.SetItemData(n4, m_pTCertificatiSet->m_Codice);
	}
  
  OnUpdate(NULL, 0, NULL);
}

void CTipiMaterialeView::OnButtonSfoglia() 
{
	
}

void CTipiMaterialeView::OnButtonQuadri() 
{
	UpdateData();
	m_strDescrizione += "²";
	m_EditDescrizione.SetFocus();
	UpdateData(FALSE);	
}

void CTipiMaterialeView::OnButtonAggiorna() 
{
	CWinSigmaApp* pApp	= (CWinSigmaApp*)AfxGetApp();
	if( MODE_VIEW != pApp->GetViewMode())
		return;
	long nCurSel = m_pSet->m_Codice;
	pApp->ReloadTree(TREELABEL_MATERIALI, nCurSel);	
}

void CTipiMaterialeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
  CXFormView::OnUpdate(pSender, lHint, pHint);
}
