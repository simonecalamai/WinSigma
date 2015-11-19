// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "WinSigma.h"
#include "bmobject.h"
#include "xbmpcontrol.h"

#include "WinSigmaDoc.h"
#include "MainFrm.h"
#include "XFormView.h"
#include "VerbaliView.h"
#include "FattureView.h"
#include "ListiniView.h"
#include "OperatoriView.h"
#include "AziendeView.h"
#include "TipiPagamentoView.h"
#include "TipiMaterialeView.h"
#include "MarchiView.h"

#include "ArchivioVerbaliView.h"
#include "ArchivioCertificatiView.h"
#include "ArchivioFattureView.h"
#include "StatProveView.h"
#include "StatFatturatoView.h"
#include "TotFatturatoView.h"
#include "EsportazioneCSVView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SPLIT_RATIO   24

static bool bFirst = true;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_OUTBAR_NOTIFY, OnOutbarNotify)
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	bFirst = true;
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::EditMode(int nId)
{
  WORD i;
  CMenu* pMenu;
	TBBUTTON tbButton;

  /*---- abilito/disabilito la barra di navigazione -----*/
	m_wndBar.EnableWindow(nId < 0);
  /*---- abilito/disabilito il menù di sistema -----*/
	pMenu = GetSystemMenu(FALSE);
	if(nId < 0)
	{
		for(i = 0; i < pMenu->GetMenuItemCount(); i++)
		  pMenu->EnableMenuItem(i, MF_BYPOSITION | MF_ENABLED);
	}
	else
	{
		for(i = 0; i < pMenu->GetMenuItemCount(); i++)
		  pMenu->EnableMenuItem(i, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);
  }
  /*---- abilito/disabilito il menù della vista -----*/
	pMenu = GetMenu();
  if(nId < 0)
	{
		for(i = 0; i < pMenu->GetMenuItemCount(); i++)
  		pMenu->EnableMenuItem(i, MF_BYPOSITION | MF_ENABLED);
    pMenu->DeleteMenu(i - 1, MF_BYPOSITION);
	}
	else
	{
		for(i = 0; i < pMenu->GetMenuItemCount(); i++)
		{
		  pMenu->EnableMenuItem(i, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);
		}
    pMenu->InsertMenu(i, MF_BYPOSITION, nId, "Chiudi");
	}
	DrawMenuBar();
	/*----- abilito/disbilito i bottoni della toolbar -----*/
  if(nId < 0)
	{
		for(i = 0; i < m_wndToolBar.GetToolBarCtrl().GetButtonCount(); i++)
		{
		  m_wndToolBar.GetToolBarCtrl().GetButton(i, &tbButton);
		  m_wndToolBar.GetToolBarCtrl().EnableButton(tbButton.idCommand, TRUE);
			m_wndToolBar.GetToolBarCtrl().Indeterminate(tbButton.idCommand, FALSE);
//		  m_wndToolBar.GetToolBarCtrl().SetState(tbButton.idCommand, TBSTATE_ENABLED);
		}
	}
	else
	{
		for(i = 0; i < m_wndToolBar.GetToolBarCtrl().GetButtonCount(); i++)
		{
		  m_wndToolBar.GetToolBarCtrl().GetButton(i, &tbButton);
		  m_wndToolBar.GetToolBarCtrl().EnableButton(tbButton.idCommand, FALSE);
  		m_wndToolBar.GetToolBarCtrl().Indeterminate(tbButton.idCommand, TRUE);
//		  m_wndToolBar.GetToolBarCtrl().SetState(tbButton.idCommand, 0);
		}
		m_wndToolBar.GetToolBarCtrl().EnableButton(nId, TRUE);
		m_wndToolBar.GetToolBarCtrl().Indeterminate(nId, FALSE);
//	  m_wndToolBar.GetToolBarCtrl().SetState(nId, TBSTATE_ENABLED);
	}
}

void CMainFrame::StatusBarMessage(CString strMessage)
{
	m_wndStatusBar.SetPaneText(0, strMessage);
}

/********************************************************************
* Funzione   : OnCreate
* Descrizione: 
* Parametri  : 
* Ritorno    : 
* Note       : 
*********************************************************************/
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR_AZIENDE) )
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
  //	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
  //	EnableDocking(CBRS_ALIGN_ANY);
  //	DockControlBar(&m_wndToolBar);
 
  return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

  cs.style = WS_OVERLAPPEDWINDOW; 

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

/********************************************************************
* Funzione   : OnCreateClient
* Descrizione: 
* Parametri  : 
* Ritorno    : 
* Note       : Chiamata dal framework durante l'esecuzione della 
               OnCreate
*********************************************************************/
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
  int n, nFolder;

	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  
	// creo la splitter windows principale
	if (!m_wndSplitter.CreateStatic(this, 1, 2)) 
		return false;
	
	// creo la view associata al pannello di destra della splitter
	if (!m_wndSplitter.CreateView(0, 1, pContext->m_pNewViewClass, CSize(0,0), pContext)) 
		return false;

	// impostazione dei flags
	DWORD dwf = CGfxOutBarCtrl::fDragItems|CGfxOutBarCtrl::fEditGroups|CGfxOutBarCtrl::fEditItems|CGfxOutBarCtrl::fRemoveGroups|
				CGfxOutBarCtrl::fRemoveItems|CGfxOutBarCtrl::fAddGroups|CGfxOutBarCtrl::fAnimation;
//				|CGfxOutBarCtrl::fSelHighlight;

	// creo la Outlook-style bar del pannello di sinistra della splitter
	m_wndBar.Create(WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), &m_wndSplitter, m_wndSplitter.IdFromRowCol(0, 0), dwf);
	m_wndBar.SetOwner(this);

	// inizializza gli oggetti di classe CImageList (per ciascun oggetto viene indicata
	// l'ID della risorsa (bitmap) contenente la lista di immagini)
	m_imgAziende.Create(IDB_IMAGELIST_AZIENDE,     24, 0, RGB(0,128,128));
  m_imgVerbali.Create(IDB_IMAGELIST_VERBALI,     24, 0, RGB(0,128,128));
  m_imgFatture.Create(IDB_IMAGELIST_FATTURE,     24, 0, RGB(0,128,128));
  m_imgListini.Create(IDB_IMAGELIST_LISTINI,     24, 0, RGB(0,128,128));	
  m_imgStrumenti.Create(IDB_IMAGELIST_STRUMENTI, 24, 0, RGB(0,128,128));	
	m_imgArchivio.Create(IDB_IMAGELIST_ARCHIVIO,   32, 0, RGB(128,128,128));
	// la funzione SetImageList della classe CGfxOutBarCtrl imposta le icone
	m_wndBar.SetImageList(&m_imgArchivio, CGfxOutBarCtrl::fLargeIcon);

  DWORD dwStyle;
	dwStyle = WS_CHILD | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS|TVS_SHOWSELALWAYS;
	
	// creo l'albero delle aziende
	m_wndTreeAziende.Create(dwStyle, CRect(0,0,0,0), &m_wndBar, 1010);
	m_wndTreeAziende.SetImageList(&m_imgAziende, TVSIL_NORMAL);
	m_wndTreeAziende.SetDoc(pContext->m_pCurrentDoc);
	nFolder = m_wndBar.AddFolderBar("Aziende", &m_wndTreeAziende);

	// albero dei verbali
	m_wndTreeVerbali.Create(dwStyle, CRect(0,0,0,0), &m_wndBar, 1010);
	m_wndTreeVerbali.SetImageList(&m_imgVerbali, TVSIL_NORMAL);
	m_wndTreeVerbali.SetDoc(pContext->m_pCurrentDoc);
	m_wndBar.AddFolderBar("Verbali aperti", &m_wndTreeVerbali);

	if(pApp->GetUserPrivileges() <= PRIV_FATTURAZIONE)
	{
		// albero delle fatture
		m_wndTreeFatture.Create(dwStyle, CRect(0,0,0,0), &m_wndBar, 1010);
		m_wndTreeFatture.SetImageList(&m_imgFatture, TVSIL_NORMAL);
		m_wndTreeFatture.SetDoc(pContext->m_pCurrentDoc);

  	m_wndBar.AddFolderBar("Fatture",  &m_wndTreeFatture);
  }

	if(pApp->GetUserPrivileges() <= PRIV_AMMINISTRAZIONE)
	{
		/*--- albero dei listini ---*/
		m_wndTreeListini.Create(dwStyle, CRect(0,0,0,0), &m_wndBar, 1010);
		m_wndTreeListini.SetImageList(&m_imgListini, TVSIL_NORMAL);
		m_wndTreeListini.SetDoc(pContext->m_pCurrentDoc);

  	m_wndBar.AddFolderBar("Listini",              &m_wndTreeListini);
	
		// albero delle tabelle ausiliarie
		m_wndTreeStrumenti.Create(dwStyle, CRect(0,0,0,0), &m_wndBar, 1010);
		m_wndTreeStrumenti.SetImageList(&m_imgStrumenti, TVSIL_NORMAL);
		m_wndTreeStrumenti.SetDoc(pContext->m_pCurrentDoc);

  	n = m_wndBar.AddFolderBar("Tabelle",              &m_wndTreeStrumenti);
  }
	
	n = m_wndBar.AddFolder("Archivio",5);
	m_wndBar.InsertItem(n, ARCHIVIO_VERBALI,		"Archivio Verbali", 7, 0);
	m_wndBar.InsertItem(n, ARCHIVIO_CERTIFICATI,"Archivio Certificati", 8, 0);
	m_wndBar.InsertItem(n, ARCHIVIO_FATTURE,		"Archivio Fatture", 9, 0);
	m_wndBar.InsertItem(n, STATISTICHE_PROVE,		"Statistiche prove", 3, 0);
	m_wndBar.InsertItem(n, STATISTICHE_FATTURATO,"Statistiche fatturato", 3, 0);
	m_wndBar.InsertItem(n, TOTALE_FATTURATO,"Totali fatturato", 3, 0);
	m_wndBar.InsertItem(n, ESPORTAZIONE_CSV,"Esportazione CSV", 3, 0);

	// imposta gli effetti di animazione
	m_wndBar.SetAnimationTickCount(20);
	m_wndBar.SetAnimSelHighlight(200);
			
	// seleziono il folder con l'albero Aziende come default all'avvio del programma
	m_wndBar.SetSelFolder(nFolder);

	// imposto la larghezza dei due pannelli
	CRect r;
	GetClientRect(&r);

	int w1 = (r.Width() * SPLIT_RATIO) / 100;
	int w2 = (r.Width() * (100 - SPLIT_RATIO)) / 100;
	
//	m_wndSplitter.SetColumnInfo( 0, w1, w1);
//	m_wndSplitter.SetColumnInfo( 1, w2, w2);

  int nCur, nMin;

  m_wndSplitter.GetColumnInfo(0, nCur, nMin);
  nCur = pApp->GetProfileInt("Impostazioni", "CurW", w1);
  nMin = pApp->GetProfileInt("Impostazioni", "MinW", w1);
	m_wndSplitter.SetColumnInfo( 0, nCur, nMin);

  // riadatta il layout alle nuove impostazioni
	m_wndSplitter.RecalcLayout();
	return true;
}

/********************************************************************
* Funzione   : RepopulateTrees
* Descrizione: 
* Parametri  : 
* Ritorno    : 
* Note       :  
*********************************************************************/
void CMainFrame::RepopulateTrees()
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

  pApp->HideApplication();
  
  m_wndTreeVerbali.PopulateTree();
  if(pApp->GetUserPrivileges() <= PRIV_AMMINISTRAZIONE)
	{
  	m_wndTreeListini.PopulateTree();
	  m_wndTreeStrumenti.PopulateTree();
  }
  if(pApp->GetUserPrivileges() <= PRIV_FATTURAZIONE)
	{
    m_wndTreeFatture.PopulateTree();
	}
	m_wndTreeAziende.PopulateTree();

  for (int i(((CWinSigmaApp*)AfxGetApp())->m_dlg.m_ctrlProgressLoad.GetPos()); i <= 1000; i++)
    ((CWinSigmaApp*)AfxGetApp())->m_dlg.m_ctrlProgressLoad.SetPos(i);
  ((CWinSigmaApp*)AfxGetApp())->m_dlg.m_bOkPressed = false;
  ((CWinSigmaApp*)AfxGetApp())->m_dlg.DestroyWindow();
  ((CWinSigmaApp*)AfxGetApp())->m_bPrimaVolta = false;
}

void CMainFrame::ReloadTree(CString strLabel, long nCodice)
{
  if(strLabel == TREELABEL_OPERATORI
	   || strLabel == TREELABEL_PAGAMENTI
		 || strLabel == TREELABEL_MATERIALI
		 || strLabel == TREELABEL_MARCHI)
    m_wndTreeStrumenti.Populate(strLabel, nCodice);
	if(strLabel == TREELABEL_SCADUTI
	   || strLabel == TREELABEL_INVIGORE
		 || strLabel == TREELABEL_INELABORAZIONE)
		m_wndTreeListini.Populate(strLabel, nCodice);
  if(strLabel == TREELABEL_AZIENDERECENTI
     || strLabel == TREELABEL_AZIENDEIMPORTANTI
     || strLabel == TREELABEL_AZIENDEALFABETICA)
     m_wndTreeAziende.Populate(strLabel, nCodice);
  if(strLabel == TREELABEL_VERBALIULTIMOMESE
     || strLabel == TREELABEL_VERBALIPRECEDENTI
     || strLabel == TREELABEL_VERBALIFATTPROFORMA)
     m_wndTreeVerbali.Populate(strLabel, nCodice);
  if(strLabel == TREELABEL_FATTUREDAEMETTERE || strLabel.FindOneOf("0123456789") >= 0)
    m_wndTreeFatture.Populate(strLabel, nCodice);
}

/********************************************************************
* Funzione   : OnOutbarNotify
* Descrizione: 
* Parametri  : 
* Ritorno    : 
* Note       : Viene chiamata quando l'applicazione riceve il messaggio
               WM_OUTBAR_NOTIFY 
*********************************************************************/
	long CMainFrame::OnOutbarNotify(WPARAM wParam, LPARAM lParam)
{
  CString str;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  int folderArchivio = 5;
  long privilege;
  if((privilege = pApp->GetUserPrivileges()) > PRIV_FATTURAZIONE)
    folderArchivio = 2;
  else if(privilege == PRIV_FATTURAZIONE)
    folderArchivio = 3;
	switch (wParam)
	{
		case NM_OB_ITEMCLICK:
		{
		  // cast the lParam to an integer to get the clicked item
  	  int ClickedItem = (int)lParam;
			if (m_wndBar.GetSelFolder() == folderArchivio)
			{
				switch(ClickedItem)
				{
					case ARCHIVIO_VERBALI :
						SwitchToForm(IDD_FORM_ARCHIVIO_VERBALI);
						break;
					case ARCHIVIO_CERTIFICATI :
						SwitchToForm(IDD_FORM_ARCHIVIO_CERTIFICATI);
						break;
					case ARCHIVIO_FATTURE :
						SwitchToForm(IDD_FORM_ARCHIVIO_FATTURE);
						break;
					case STATISTICHE_PROVE :
						SwitchToForm(IDD_FORM_STATISTICHE_PROVE);
						break;		
					case STATISTICHE_FATTURATO :
						SwitchToForm(IDD_FORM_STATISTICHE_FATTURATO);
						break;
					case TOTALE_FATTURATO :
						SwitchToForm(IDD_FORM_TOTALI_FATTURATO);
						break;
					case ESPORTAZIONE_CSV :
						SwitchToForm(IDD_FORM_ESPORTAZIONE_CSV);
						break;
				}
			} 
			else
			{
				switch(ClickedItem)
				{
					case TREEITEM_OPERATORI :  
							SwitchToForm(IDD_FORM_OPERATORI);
						break;
					// icona
					case TREEITEM_PAGAMENTI :  
							SwitchToForm(IDD_FORM_PAGAMENTI);
						break;
					// icona
					case TREEITEM_MATERIALI :
							SwitchToForm(IDD_FORM_MATERIALI);
						break;
					case TREEITEM_MARCHI :
							SwitchToForm(IDD_FORM_MARCHI);
						break;
					case TREEITEM_AZIENDEIMPORTANTI:
					case TREEITEM_AZIENDERECENTI:
					case TREEITEM_AZIENDEALFABETICA:
							m_wndTreeAziende.SelectedTree(ClickedItem);
							SwitchToForm(IDD_FORM_AZIENDE);
						break;
					case TREEITEM_VERBALIPRECEDENTI:
					case TREEITEM_VERBALIULTIMOMESE:
          case TREEITEM_VERBFATTPROFORMA:
						m_wndTreeVerbali.SelectedTree(ClickedItem);
						SwitchToForm(IDD_FORM_VERBALI);
						break;
					case TREEITEM_FATTUREDAEMETTERE:
          case TREEITEM_FATTUREEMESSE:
            m_wndTreeFatture.SelectedTree(ClickedItem);
						SwitchToForm(IDD_FORM_FATTURE);
						break;
          case TREEITEM_INVIGORE:
          case TREEITEM_INELABORAZIONE:
          case TREEITEM_SCADUTI:
            m_wndTreeListini.SelectedTree(ClickedItem);
            SwitchToForm(IDD_FORM_LISTINI);
            break;
				}
			}
		}
//		GetActiveDocument()->UpdateAllViews(NULL);
		return 0;

		case NM_OB_ONLABELENDEDIT:
		// cast the lParam to an OUTBAR_INFO * struct; it will contain info about the edited item
		// return 1 to do the change and 0 to cancel it
			{
				OUTBAR_INFO * pOI = (OUTBAR_INFO *) lParam;
				TRACE2("Editing item %d, new text:%s\n", pOI->index, pOI->cText);
			}
		return 1;

		case NM_OB_ONGROUPENDEDIT:
		// cast the lParam to an OUTBAR_INFO * struct; it will contain info about the edited folder
		// return 1 to do the change and 0 to cancel it
			{
				OUTBAR_INFO * pOI = (OUTBAR_INFO *) lParam;
				TRACE2("Editing folder %d, new text:%s\n", pOI->index, pOI->cText);
			}
		return 1;

		case NM_OB_DRAGITEM:
		// cast the lParam to an OUTBAR_INFO * struct; it will contain info about the dragged items
		// return 1 to do the change and 0 to cancel it
			{
				OUTBAR_INFO * pOI = (OUTBAR_INFO *) lParam;
				TRACE2("Drag item %d at position %d\n", pOI->iDragFrom, pOI->iDragTo);
			}
		return 1;

		case NM_FOLDERCHANGE:
		// cast the lParam to an integer to get the clicked folder
			{
				int index = (int) lParam;
				switch(lParam)
				{
					case 0:
						SwitchToForm(IDD_FORM_AZIENDE);
						break;
					case 1:
						SwitchToForm(IDD_FORM_VERBALI);
						break;
					case 2:
            if(privilege > PRIV_FATTURAZIONE)
              SwitchToForm(IDD_FORM_ARCHIVIO_VERBALI);
            else
						  SwitchToForm(IDD_FORM_FATTURE);
						break;
					case 3:
            if(privilege >= PRIV_FATTURAZIONE)
              SwitchToForm(IDD_FORM_ARCHIVIO_VERBALI);
            else
						  SwitchToForm(IDD_FORM_LISTINI);
						break;
					case 4:
					  m_wndTreeStrumenti.Activate();
						break;
					case 5:
					  SwitchToForm(IDD_FORM_ARCHIVIO_VERBALI);
						break;
				}	
			}
		return 1;
	}
	return 0;
}


/********************************************************************
* Funzione   : SwitchToForm
* Descrizione: Passa a visualizzare una diversa view nel pannello di destra
               della splitter window, e un nuovo menu e una nuova toolbar
							 nella frame window
* Parametri  : nForm = intero che e' l'ID (identificatore) della nuova vista
                       da visualizzare nel pannello di destra
* Ritorno    : 
* Note       : 
*********************************************************************/
void CMainFrame::SwitchToForm(int nForm)
{
	CMenu menu;
	//static bool bFirst = true;

	// ricava un puntatore alla vista (child window) attualmente presente nel pannello
	// di destra della splitter window
	CView* pOldActiveView = (CView*)m_wndSplitter.GetPane(0, 1);

  // ricava un puntatore alla child window avente identificatore nForm	
	CView* pNewActiveView = (CView*)GetDlgItem(nForm);

	// se non esite una child window con identificatore nForm (il puntatore e' nullo),
	// la crea
	if (pNewActiveView == NULL)     
	{                               
		CCreateContext context; 
		context.m_pCurrentDoc = pOldActiveView->GetDocument();
		// nascondo la view atualmente visualizzata e passa l'attivazione ad un altra
		pOldActiveView->ShowWindow(SW_HIDE);
		// disattivo l'autodistruzione del doc
		context.m_pCurrentDoc->m_bAutoDelete = FALSE;
		// cancello la vecchia view
    m_wndSplitter.DeleteView(0, 1);
		// riattivo l'autodistruzione del doc					  							  
		context.m_pCurrentDoc->m_bAutoDelete = TRUE;
		switch(m_iForm = nForm) 
		{
			case IDD_FORM_AZIENDE:
				m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CAziendeView), CSize(0,0), &context); 
				menu.LoadMenu(IDR_MENU_AZIENDE);
				m_wndToolBar.LoadToolBar(IDR_TOOLBAR_AZIENDE);
		 		break;
			case IDD_FORM_VERBALI:
				m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CVerbaliView), CSize(0,0), &context);
#ifdef WINSIGMA2
				menu.LoadMenu(IDR_MENU_VERBALI_WS2);
#else
				menu.LoadMenu(IDR_MENU_VERBALI);
#endif
				m_wndToolBar.LoadToolBar(IDR_TOOLBAR_VERBALI);
#ifdef WINSIGMA2
				m_wndToolBar.SetButtonInfo(0,ID_SEPARATOR,TBBS_SEPARATOR,0);
				m_wndToolBar.SetButtonInfo(2,ID_SEPARATOR,TBBS_SEPARATOR,0);
#endif
		 		break;
			case IDD_FORM_FATTURE:
				m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CFattureView), CSize(0,0), &context);
				menu.LoadMenu(IDR_MENU_FATTURE);
				m_wndToolBar.LoadToolBar(IDR_TOOLBAR_FATTURE);
		 		break;				
			case IDD_FORM_LISTINI:
				m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CListiniView), CSize(0,0), &context);
				menu.LoadMenu(IDR_MENU_LISTINI);
				m_wndToolBar.LoadToolBar(IDR_TOOLBAR_LISTINI);
		 		break;				
			case IDD_FORM_OPERATORI:
				m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(COperatoriView), CSize(0,0), &context);
				menu.LoadMenu(IDR_MENU_OPERATORI);
				m_wndToolBar.LoadToolBar(IDR_TOOLBAR_OPERATORI);
		 		break;				
			case IDD_FORM_PAGAMENTI:
				m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CTipiPagamentoView), CSize(0,0), &context);
				menu.LoadMenu(IDR_MENU_PAGAMENTI);
				m_wndToolBar.LoadToolBar(IDR_TOOLBAR_PAGAMENTI);
		 		break;				
			case IDD_FORM_MATERIALI:
				m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CTipiMaterialeView), CSize(0,0), &context);
				menu.LoadMenu(IDR_MENU_MATERIALI);
				m_wndToolBar.LoadToolBar(IDR_TOOLBAR_MATERIALI);
		 		break;				
			case IDD_FORM_MARCHI:
				m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CMarchiView), CSize(0,0), &context);
				menu.LoadMenu(IDR_MENU_MARCHI);
				m_wndToolBar.LoadToolBar(IDR_TOOLBAR_MARCHI);
		 		break;	
			case IDD_FORM_ARCHIVIO_VERBALI:
				m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CArchivioVerbaliView), CSize(0,0), &context);
				menu.LoadMenu(IDR_MENU_ARCHIVIO_VERBALI);
				m_wndToolBar.LoadToolBar(IDR_TOOLBAR_ARCHIVIO_VERBALI);
		 		break;
			case IDD_FORM_ARCHIVIO_CERTIFICATI:
				m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CArchivioCertificatiView), CSize(0,0), &context);
				menu.LoadMenu(IDR_MENU_ARCHIVIO_CERTIFICATI);
				m_wndToolBar.LoadToolBar(IDR_TOOLBAR_ARCHIVIO_CERTIFICATI);
		 		break;	
			case IDD_FORM_ARCHIVIO_FATTURE:
				m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CArchivioFattureView), CSize(0,0), &context);
				menu.LoadMenu(IDR_MENU_ARCHIVIO_FATTURE);
				m_wndToolBar.LoadToolBar(IDR_TOOLBAR_ARCHIVIO_FATTURE);
		 		break;
			case IDD_FORM_STATISTICHE_PROVE:
				m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CStatProveView), CSize(0,0), &context);
				menu.Detach();
		 		break;
			case IDD_FORM_STATISTICHE_FATTURATO:
				m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CStatFatturatoView), CSize(0,0), &context);
				menu.Detach();
		 		break;
			case IDD_FORM_TOTALI_FATTURATO:
				m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CTotFatturatoView), CSize(0,0), &context);
				menu.Detach();
		 		break;

			case IDD_FORM_ESPORTAZIONE_CSV:
				m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CEsportazioneCSVView), CSize(0,0), &context);
				menu.Detach();
		 		break;

		}
		// imposta il nuovo menu come menu corrente
		SetMenu(&menu);
		// discollega il windows menu handle dall'oggetto, cosicche' uscendo tra poco dalla
		/// funzione, il distruttore dell'oggetto CMenu non distruggera' il nuovo menu
		menu.Detach();

		CView* pView = (CView*)m_wndSplitter.GetPane(0, 1);
    if (pView)
		{
      SetActiveView(pView);

      if ( !bFirst)
		    pView->OnInitialUpdate();
			
			bFirst = false;
    }
	}

	// imposto la larghezza dei due pannelli in base alla vista selezionata
	CRect r;
	GetClientRect(&r);
	
	int w1 = (r.Width() * SPLIT_RATIO) / 100;
	int w2 = (r.Width() * (100 - SPLIT_RATIO)) / 100;
	
//	m_wndSplitter.SetColumnInfo( 0, w1, 0);
//	m_wndSplitter.SetColumnInfo( 1, w2, 0);


	// adatto il frame
	m_wndSplitter.RecalcLayout();
}




void CMainFrame::OnClose() 
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  int nCur, nMin;

  m_wndSplitter.GetColumnInfo(0, nCur, nMin);
  pApp->WriteProfileInt("Impostazioni", "CurW", nCur);
  pApp->WriteProfileInt("Impostazioni", "MinW", nMin);
	CFrameWnd::OnClose();
}

BOOL CMainFrame::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
  if ( (m_iForm == 102) )
    HtmlHelp (m_hWnd, AfxGetApp()->m_pszHelpFilePath, HH_HELP_CONTEXT, HELP_CONTEXT ? 102 : 0);
  else if ( (m_iForm == 134) )
    HtmlHelp (m_hWnd, AfxGetApp()->m_pszHelpFilePath, HH_HELP_CONTEXT, HELP_CONTEXT ? 134 : 0);
  else if ( (m_iForm == 133) )
    HtmlHelp (m_hWnd, AfxGetApp()->m_pszHelpFilePath, HH_HELP_CONTEXT, HELP_CONTEXT ? 133 : 0);
  else if ( (m_iForm == 145) )
    HtmlHelp (m_hWnd, AfxGetApp()->m_pszHelpFilePath, HH_HELP_CONTEXT, HELP_CONTEXT ? 145 : 0);
  else if ( (m_iForm == 150) )
    HtmlHelp (m_hWnd, AfxGetApp()->m_pszHelpFilePath, HH_HELP_CONTEXT, HELP_CONTEXT ? 150 : 0);
  else if ( (m_iForm == 184) )
    HtmlHelp (m_hWnd, AfxGetApp()->m_pszHelpFilePath, HH_HELP_CONTEXT, HELP_CONTEXT ? 184 : 0);

  HtmlHelp (m_hWnd, AfxGetApp()->m_pszHelpFilePath, HH_HELP_CONTEXT, HELP_CONTEXT ? pHelpInfo->iCtrlId : 0);
	
  return 0;
	//return CFrameWnd::OnHelpInfo(pHelpInfo);
}

void CMainFrame::WinHelp(DWORD dwData, UINT nCmd) 
{
	// TODO: Add your specialized code here and/or call the base class
	HtmlHelp(m_hWnd, AfxGetApp()->m_pszHelpFilePath, HH_HELP_CONTEXT, nCmd == HELP_CONTEXT ? dwData : 0);
}
