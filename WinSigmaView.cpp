// WinSigmaView.cpp : implementation of the CWinSigmaView class
//

#include "stdafx.h"
#include "WinSigma.h"

#include "WinSigmaDoc.h"
#include "MainFrm.h"

#include "WinSigmaView.h"

#include "AziendeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinSigmaView

IMPLEMENT_DYNCREATE(CWinSigmaView, CFormView)

BEGIN_MESSAGE_MAP(CWinSigmaView, CFormView)
	//{{AFX_MSG_MAP(CWinSigmaView)
	ON_COMMAND(ID_AZIENDA_MODIFICA, OnAziendaModifica)
	ON_COMMAND(ID_AZIENDA_NUOVA, OnAziendaNuova)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinSigmaView construction/destruction

CWinSigmaView::CWinSigmaView()
	: CFormView(CWinSigmaView::IDD)
{
	//{{AFX_DATA_INIT(CWinSigmaView)
	m_csNome = _T("");
	m_csIndirizzo = _T("");
	m_csFax = _T("");
	m_csEMail = _T("");
	m_csCodiceFiscale = _T("");
	m_csCodiceCliente = _T("");
	m_csCitta = _T("");
	m_csCAP = _T("");
	m_csCAB = _T("");
	m_csABI = _T("");
	m_csBanca = _T("");
	m_csPIVA = _T("");
	m_csProvincia = _T("");
	m_csTelefono = _T("");
	m_IsImportante = FALSE;
	m_csRagioneSociale = _T("");
	m_csNote = _T("");
	m_csCognome = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

	m_pApp = (CWinSigmaApp*)AfxGetApp();
	m_pDB = &m_pApp->m_db;
}

CWinSigmaView::~CWinSigmaView()
{
}

void CWinSigmaView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinSigmaView)
	DDX_Text(pDX, IDC_EDIT_NOME, m_csNome);
	DDX_Text(pDX, IDC_EDIT_INDIRIZZO, m_csIndirizzo);
	DDX_Text(pDX, IDC_EDIT_FAX, m_csFax);
	DDX_Text(pDX, IDC_EDIT_E_MAIL, m_csEMail);
	DDX_Text(pDX, IDC_EDIT_CODICE_FISCALE, m_csCodiceFiscale);
	DDX_Text(pDX, IDC_EDIT_CODICE_CLIENTE, m_csCodiceCliente);
	DDX_Text(pDX, IDC_EDIT_CITTA, m_csCitta);
	DDX_Text(pDX, IDC_EDIT_CAP, m_csCAP);
	DDX_Text(pDX, IDC_EDIT_CAB, m_csCAB);
	DDX_Text(pDX, IDC_EDIT_ABI, m_csABI);
	DDX_Text(pDX, IDC_EDIT_BANCA, m_csBanca);
	DDX_Text(pDX, IDC_EDIT_P_IVA, m_csPIVA);
	DDX_Text(pDX, IDC_EDIT_PROVINCIA, m_csProvincia);
	DDX_Text(pDX, IDC_EDIT_TELEFONO, m_csTelefono);
	DDX_Check(pDX, IDC_CHECK_AZIENDA_IMPORTANTE, m_IsImportante);
	DDX_Text(pDX, IDC_EDIT_RAGIONE_SOCIALE, m_csRagioneSociale);
	DDX_Text(pDX, IDC_EDIT_NOTE, m_csNote);
	DDX_Text(pDX, IDC_EDIT_COGNOME, m_csCognome);
	//}}AFX_DATA_MAP
}

BOOL CWinSigmaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

/********************************************************************
* Funzione   : OnInitialUpdate
* Descrizione: 
* Parametri  :                
* Ritorno    :     
* Note       : 
*********************************************************************/
void CWinSigmaView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();


  GetDlgItem(IDC_CHECK_AZIENDA_IMPORTANTE)->EnableWindow(false);

}

/////////////////////////////////////////////////////////////////////////////
// CWinSigmaView printing

BOOL CWinSigmaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWinSigmaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWinSigmaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CWinSigmaView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CWinSigmaView diagnostics

#ifdef _DEBUG
void CWinSigmaView::AssertValid() const
{
	CFormView::AssertValid();
}

void CWinSigmaView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CWinSigmaDoc* CWinSigmaView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinSigmaDoc)));
	return (CWinSigmaDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWinSigmaView message handlers

/********************************************************************
* Funzione   : OnAziendaModifica
* Descrizione: 
* Parametri  :                
* Ritorno    :     
* Note       : 
*********************************************************************/
void CWinSigmaView::OnAziendaModifica() 
{
	CMainFrame* pFrame =      (CMainFrame*)GetParentFrame();
  CAziendeTreeCtrl* pTree = (CAziendeTreeCtrl*)&pFrame->m_wndTreeAziende;

	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();

//	CAziendaDlg dlg;
	long nCodAzienda;

  HTREEITEM hSelected = pTree->GetSelectedItem();

	if (hSelected)
	{
	  nCodAzienda = pTree->GetItemData(hSelected);
		
		if (nCodAzienda == 0)
    {
			AfxMessageBox("Selezionare un'azienda");
			return;			
		}
	}
	else
	{
	  AfxMessageBox("Selezionare un'azienda");
    return;	
	}


/*
CAziendeSet set(m_pDB);
  set.m_strFilter.Format("CODICE = %ld", nCodAzienda);
	set.Open();

	CString csOldNome = set.m_Nome;

	dlg.m_IsImportante =  set.m_IsImportante;
  BYTE bOldImportante = set.m_IsImportante;

	// inizializza i controlli del dialogo
	dlg.m_csABI =               set.m_ABI;
	dlg.m_csBanca =             set.m_Banca;
	dlg.m_csCAB =               set.m_CAB;
	dlg.m_csCAP =               set.m_CAP;
	dlg.m_csCitta =             set.m_Citta;
	dlg.m_csCodiceFiscale =     set.m_CodiceFiscale;
	dlg.m_csFax =               set.m_Fax;
	dlg.m_csIndirizzo =         set.m_Indirizzo;
	dlg.m_csNome =              set.m_Nome;
	dlg.m_csNote =              set.m_Note;
	dlg.m_csPIVA =              set.m_P_IVA;
	//dlg.m_csPagamento =         pSet->m_PAGAMENTO;	
	dlg.m_csProvincia =         set.m_Provincia;
	dlg.m_csRagioneSociale =    set.m_RagioneSociale;
	dlg.m_csCognome =           set.m_Cognome;
	dlg.m_csTelefono =          set.m_Telefono;

	set.Close();

	dlg.m_nMode = MODE_EDIT;
	
	if (dlg.DoModal() == IDOK)
	{				
    set.m_strFilter.Format("CODICE = %ld", nCodAzienda);
		set.Open();
		
		set.Edit();
		set.m_ABI =                    dlg.m_csABI;
		set.m_Banca =                  dlg.m_csBanca;
		set.m_CAB =                    dlg.m_csCAB;             
		set.m_CAP =                    dlg.m_csCAP;
		set.m_Citta =                  dlg.m_csCitta;
		
		if (dlg.m_IsImportante)
		  set.m_IsImportante = 1;
		else
		  set.m_IsImportante = 0;
		
		set.m_CodiceFiscale =         dlg.m_csCodiceFiscale;
		set.m_Cognome =               dlg.m_csCognome;
		set.m_Fax =                   dlg.m_csFax;   
		set.m_RagioneSociale =        dlg.m_csRagioneSociale;
		set.m_Indirizzo =             dlg.m_csIndirizzo;
		set.m_Nome =                  dlg.m_csNome; 
		set.m_Note =                  dlg.m_csNote;
		set.m_P_IVA =                 dlg.m_csPIVA;
		//set.m_PAGAMENTO =              dlg.m_csPagamento;
		set.m_Provincia =             dlg.m_csProvincia;
	  set.m_Telefono =              dlg.m_csTelefono;

		set.Update();
		set.Close();
		
		// se e' cambiato l'attributo importante
		if ((dlg.m_IsImportante != bOldImportante) || (dlg.m_csNome != csOldNome))
		{
	 	  // ricostruisce l'albero Aziende, selezionando dopo la ricostruzione,
			// l'azienda appena modificata e aggiorna le viste
//		  pTree->RebuildTree(nCodAzienda);
		}
		else
		{				  
			// aggiorna le viste
		  pDoc->UpdateAllViews(NULL);
		}
	}
*/
}

/********************************************************************
* Funzione   : OnAziendaNuova
* Descrizione: 
* Parametri  :                
* Ritorno    :     
* Note       : 
*********************************************************************/
void CWinSigmaView::OnAziendaNuova() 
{
	CMainFrame* pFrame =      (CMainFrame*)GetParentFrame();
  CAziendeTreeCtrl* pTree = (CAziendeTreeCtrl*)&pFrame->m_wndTreeAziende;

	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();

  CAziendeSet set(m_pDB);

/*
  CAziendaDlg dlg;
	
	dlg.m_nMode = MODE_ADD;

	if (dlg.DoModal() == IDOK)
	{ 
		// aggiunge un record 
		set.Open();
		set.AddNew();

		set.m_RagioneSociale =     dlg.m_csRagioneSociale;
		set.m_Cognome =            dlg.m_csCognome;
		set.m_Nome =               dlg.m_csNome;

    set.m_ABI =                dlg.m_csABI;
    set.m_Banca =              dlg.m_csBanca;
    set.m_CAB =                dlg.m_csCAB;
    set.m_CAP =                dlg.m_csCAP;
    set.m_Citta =              dlg.m_csCitta;
		set.m_CodiceFiscale =      "WWWWWWWWWWWWWWW";
    set.m_Fax =                dlg.m_csFax;
    set.m_Indirizzo =          dlg.m_csIndirizzo;
    set.m_P_IVA =              dlg.m_csPIVA;		
		set.m_Provincia =          dlg.m_csProvincia;
		set.m_Telefono =           dlg.m_csTelefono;
    //set.m_TipoPagamento =      dlg.m_csTipoPagamento;
		
		if (dlg.m_IsImportante)
		  set.m_IsImportante = 1;
		else
		  set.m_IsImportante = 0;

		set.Update();
		set.Close();

    // ricava il codice dell'azienda aggiunta e ne aggiorna il campo CODICE FISCALE
		set.m_strFilter.Format("CodiceFiscale = 'WWWWWWWWWWWWWWW'");
		set.Open();
		
		long nCodAggiunto = set.m_Codice;
		set.Edit();
		set.m_CodiceFiscale = dlg.m_csCodiceFiscale;		
		
		set.Update();
		set.Close();

		// ricostruisce l'albero aziende, selezionando dopo la ricostruzione,
		// l'azienda appena aggiunta
//		pTree->RebuildTree(nCodAggiunto);			
	}		
*/
}

/********************************************************************
* Funzione   : OnUpdate
* Descrizione: 
* Parametri  :                
* Ritorno    :     
* Note       : 
*********************************************************************/
void CWinSigmaView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CMainFrame* pFrame =      (CMainFrame*)GetParentFrame();
  CAziendeTreeCtrl* pTree = (CAziendeTreeCtrl*)&pFrame->m_wndTreeAziende;

	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();

	// ricava l'item selezionato
	HTREEITEM hItem = pTree->GetSelectedItem();
	
	// se e' selezionato un item	
	if (hItem != NULL)
	{
		// ricava il codice associato all'item
		long code = pTree->GetItemData(hItem);

		// se e' stata selezionata una azienda
		if (code)
		{
			CAziendeSet set(m_pDB);
			set.m_strFilter.Format("Codice = %ld", code);
			set.Open();
	  			
			// aggiorno le variabili membro in base ai valori del recordset
			m_csCodiceCliente.Format("%ld", set.m_Codice);

			m_csABI =               set.m_ABI;
			m_csBanca =             set.m_Banca;
			m_csCAB =               set.m_CAB;
			m_csCAP =               set.m_CAP;
			m_csCitta =             set.m_Citta;
			m_csCodiceFiscale =     set.m_CodiceFiscale;
	    m_csCognome =           set.m_Cognome;
			m_csFax =               set.m_Fax;
			m_csIndirizzo =         set.m_Indirizzo;
			m_csNome =              set.m_Nome;
	    m_csNote =              set.m_Note;
			m_csPIVA =              set.m_P_IVA;
			//m_csPagamento =         set.m_Pagamento;
			m_csProvincia =         set.m_Provincia;
	    m_csRagioneSociale =    set.m_RagioneSociale;
			m_csTelefono =          set.m_Telefono;

			if (set.m_IsImportante == 1)
				m_IsImportante = 1;
			else
			  m_IsImportante = 0;

			set.Close();

			// trasferisce i valori prima impostati sulle variabili, ai controlli della vista
			UpdateData(false);
		}
		// altrimenti resetta i controlli della vista
		else
			ResetControls();
	}
}


/********************************************************************
* Funzione   : ResetControls
* Descrizione: Resetta i controlli della vista
* Parametri  :                
* Ritorno    :     
* Note       : 
*********************************************************************/
void CWinSigmaView::ResetControls()
{
	m_csNome = _T("");
	m_csIndirizzo = _T("");
	m_csFax = _T("");
	m_csEMail = _T("");
	m_csCodiceFiscale = _T("");
	m_csCodiceCliente = _T("");
	m_csCitta = _T("");
	m_csCAP = _T("");
	m_csCAB = _T("");
	m_csABI = _T("");
	m_csBanca = _T("");
	m_csPIVA = _T("");
	m_csProvincia = _T("");
	m_csTelefono = _T("");
	m_IsImportante = FALSE;
	m_csRagioneSociale = _T("");
	m_csNote = _T("");
	m_csCognome = _T("");

  UpdateData(false);
}

