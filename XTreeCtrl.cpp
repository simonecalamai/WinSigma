// XTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "WinSigmaDoc.h"
#include "MainFrm.h"
#include "XTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXTreeCtrl

CXTreeCtrl::CXTreeCtrl()
{
  m_bDenySelection = FALSE;
	m_pfnCompare     = NULL;
}

CXTreeCtrl::~CXTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CXTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CXTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpanded)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/**********************************************************************************
* Funzione:    Populate
* Descrizione: Modella un sottoablbero con il relativo recordset
* Parametri:   L'etichetta del sottoalbero e il codice dell'elemento selezionato
* Note:
**********************************************************************************/
void CXTreeCtrl::Populate(CString strLabel, long nCodeSelected)
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	HTREEITEM     hTreeItem, hTreeSelectedItem, hTreeParentItem;
	CString       strItem;
	CXRecsetTree* pXTree;
	CRecordset*   pSet;
	TVSORTCB      tvSortCB;
 
  /*----- cerco l'item folder -----*/
	if(!(hTreeParentItem = GetFolderItem(strLabel)))
	  return;
  m_bDenySelection = TRUE;
 	SelectItem(NULL);
  hTreeSelectedItem = NULL;
	pXTree = (CXRecsetTree*)GetItemData(hTreeParentItem);
	if(pXTree->m_pTurboSet)
	{
	  pSet = pXTree->m_pTurboSet;
  	pXTree->m_pSet->Requery();
	}
	else 
	  pSet = pXTree->m_pSet;
  pSet->Requery();
	/*----- sincronizzo l'albero -----*/
	hTreeItem = GetChildItem(hTreeParentItem);
	hTreeSelectedItem = hTreeParentItem;
	for(SET_START(pSet); !pSet->IsEOF(); pSet->MoveNext())
	{
		
	  if (((CWinSigmaApp*)AfxGetApp())->m_bPrimaVolta)
      Spacciatore();

    if(hTreeItem)
		{
    /*----- se l'ho trovato ricarico il nome -----*/
			SetItemText(hTreeItem, pXTree->GetLabel());
		}
		else
		{
	  /*----- se non l'ho trovato lo inserisco -----*/
			hTreeItem = InsertItem(pXTree->GetLabel(), 
			                       pXTree->m_nIcon, pXTree->m_nIcon, hTreeParentItem);
		  hTreeSelectedItem = hTreeItem;
		}
		SetItemData(hTreeItem, pXTree->GetCode());
    SetItemImage(hTreeItem, pXTree->m_nIcon, pXTree->m_nIcon);
		/*----- eventualmente seleziono -----*/
		if(pXTree->GetCode() == nCodeSelected)
		  hTreeSelectedItem = hTreeItem;
		hTreeItem = GetNextSiblingItem(hTreeItem);
	}
	for(; hTreeItem; hTreeItem = GetNextSiblingItem(hTreeItem))
  {
		
	  if (((CWinSigmaApp*)AfxGetApp())->m_bPrimaVolta)
      Spacciatore();
    
    DeleteItem(hTreeItem);
  }
  /*---- riordino l'albero degli operatori -----*/
  if(m_pfnCompare)
	{
	  tvSortCB.hParent = hTreeParentItem;
		tvSortCB.lParam  = 0;
		tvSortCB.lpfnCompare = m_pfnCompare;
		SortChildrenCB(&tvSortCB);
	}
	else
	  SortChildren(hTreeParentItem);
  m_bDenySelection = FALSE;
  SelectItem(hTreeSelectedItem);
  Sincronize(strLabel);
}

/**********************************************************************************
* Funzione:    Sincronize
* Descrizione: sincronizza il recorset con l'elemento selezionato in un sottoablero
* Parametri:   L'etichetta del sottoalbero
* Note:
**********************************************************************************/
void CXTreeCtrl::Sincronize(CString strLabel)
{
  int n;
	HTREEITEM     hTreeItem = GetSelectedItem(), hTreeParentItem;
	CXRecsetTree* pXTree;
	CRecordset*   pSet;
 
  /*----- cerco l'item folder -----*/
	if(!(hTreeParentItem = GetFolderItem(strLabel)))
	  return;
	pXTree = (CXRecsetTree*)GetItemData(hTreeParentItem);
	if(pXTree->m_pTurboSet)
	  pSet = pXTree->m_pTurboSet;
	else
	  pSet = pXTree->m_pSet;
	/*----- sincronizzo il recordset -----*/
	if(!pSet->IsBOF() || !pSet->IsEOF())
	{
		if(!hTreeItem)
	  {
		  /*--- nessun elemento selezionato -----*/
		  pSet->MoveFirst();
			pSet->MovePrev();
	  }
	  else
		{
			long c = (long)GetItemData(hTreeItem);
			for(pSet->MoveFirst(), n = 0; 
					!pSet->IsEOF(); 
					pSet->MoveNext(), n++)
				if(pXTree->GetCode() == c)
  				break;
			if(pXTree->m_pTurboSet)
			{
				pXTree->m_pSet->MoveFirst();
				pXTree->m_pSet->Move(n);

			}
    }
	}
}

/**********************************************************************************
* Funzione:    ActivateTree
* Descrizione: sincronizza il recorset con l'elemento selezionato in tutto l'albero
* Parametri: 
* Note:
**********************************************************************************/
void CXTreeCtrl::Activate()
{
  HTREEITEM hTreeItem, hTreeRootItem;
	CXRecsetTree* pXTree;
	CRecordset*   pSet;
 
  /*--- metto in BOF tutti recordset -----*/
  for(hTreeItem = GetChildItem(NULL);
	    hTreeItem; 
			hTreeItem = GetNextSiblingItem(hTreeItem))
	{
		pXTree = (CXRecsetTree*)GetItemData(hTreeItem);
    pSet = pXTree->m_pSet;
  	if(!pSet->IsBOF())
 	  {
 		  pSet->MoveFirst();
			if(!pSet->IsEOF())
 			  pSet->MovePrev();
 		}
  }
	/*----- determino l'item selezionato e l'eventuale radice -----*/
  for(hTreeItem = GetSelectedItem();
      hTreeItem && !GetItemData(hTreeItem);
      hTreeItem = GetParentItem(hTreeItem));
  for(hTreeRootItem = GetParentItem(hTreeItem);
      hTreeRootItem && GetParentItem(hTreeRootItem);
      hTreeRootItem = GetParentItem(hTreeRootItem));
	/*----- sincronizzo il recordset -----*/
	if(hTreeRootItem)
  {
    /*---- se c'e' un padre sincronizzo il relativo recordset -----*/
		pXTree = (CXRecsetTree*)GetItemData(hTreeRootItem);
    pSet = pXTree->m_pSet;
  	Sincronize(GetItemText(hTreeRootItem));
		hTreeItem = hTreeRootItem;
	}
	else if(hTreeItem)
	{
	  /*----- se non c'e' il padre metto in BOF -----*/
		pXTree = (CXRecsetTree*)GetItemData(hTreeItem);
    pSet = pXTree->m_pSet;
 		if(!pSet->IsBOF() || !pSet->IsEOF())
  	{
	  	pSet->MoveFirst();
			pSet->MovePrev();
    }
	}
	/*----- comunico alla main frame che è cambiata la vista -----*/
	if ((hTreeItem && this->IsWindowVisible()))
	  GetParentFrame()->PostMessage(WM_OUTBAR_NOTIFY, NM_OB_ITEMCLICK, pXTree->m_nTag);
}

HTREEITEM CXTreeCtrl::GetFolderItem(CString strLabel)
{
	HTREEITEM hTreeItem;
	CXRecsetTree* pXTree;

  for(hTreeItem = GetChildItem(NULL);
	    hTreeItem; 
			hTreeItem = GetNextSiblingItem(hTreeItem))
	{
		
	  if (((CWinSigmaApp*)AfxGetApp())->m_bPrimaVolta)
      Spacciatore();

    pXTree = (CXRecsetTree*)GetItemData(hTreeItem);
    if(GetItemText(hTreeItem) == strLabel)
 		  return hTreeItem;
	}
	return NULL;
}


/**********************************************************************************
* Funzione:    SelectItemData
* Descrizione: seleziona l'item con codice specificato nel folder specificato
* Parametri: 
* Note:
**********************************************************************************/
HTREEITEM CXTreeCtrl::SelectItemData(HTREEITEM hItemFolder, long nCode)

{
	HTREEITEM hTreeItem;

  for(hTreeItem = GetChildItem(hItemFolder);
	    hTreeItem; 
			hTreeItem = GetNextSiblingItem(hTreeItem))
	{
		CString str = GetItemText(hTreeItem);
    if(GetItemData(hTreeItem) == (unsigned long)nCode)
		{
      EnsureVisible(hTreeItem);
			SelectItem(hTreeItem);
 		  return hTreeItem;
		}
	}
	return NULL;
}


/////////////////////////////////////////////////////////////////////////////
// CXTreeCtrl message handlers

void CXTreeCtrl::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

  if(!m_bDenySelection)
    Activate();
	*pResult = 0;
}

void CXTreeCtrl::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	if(!m_bDenySelection)
  {
        SelectItem( GetFirstVisibleItem( ) );
  }
	*pResult = 0;
}
