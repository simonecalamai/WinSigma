// AziendeTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "WinSigma.h"
#include "WinSigmaDoc.h"

#include "MainFrm.h"

#include "AziendeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Aziende recenti

class CAziendeRecentiTree : public CXRecsetTree
{
  public:
		CAziendeRecentiTree(CRecordset* pSet, int nTag, int nIcon)
		   : CXRecsetTree(pSet, nTag, nIcon)
		{
		};
		long GetCode()
		{
			return ((CAziendeSet*)m_pSet)->m_Codice;
		};
		CString GetLabel()
		{
			CAziendeSet* pSet = (CAziendeSet*)m_pSet;
			return pSet->m_RagioneSociale;
		};
};

/////////////////////////////////////////////////////////////////////////////
// Aziende importanti

class CAziendeImportantiTree : public CXRecsetTree
{
  public:
		CAziendeImportantiTree(CRecordset* pSet, int nTag, int nIcon)
		   : CXRecsetTree(pSet, nTag, nIcon)
		{
		};
		long GetCode()
		{
		  return ((CAziendeSet*)m_pSet)->m_Codice;
		};
		CString GetLabel()
		{
			CAziendeSet* pSet = (CAziendeSet*)m_pSet;
			return pSet->m_RagioneSociale;
		};
};

/////////////////////////////////////////////////////////////////////////////
// Aziende alfabetica

class CAziendeAlfabeticaTree : public CXRecsetTree
{
  public:
		CAziendeAlfabeticaTree(CRecordset* pSet, int nTag, int nIcon)
		   : CXRecsetTree(pSet, nTag, nIcon)
		{
		};
		CAziendeAlfabeticaTree(CRecordset* pSet, CRecordset* pTurboSet, int nTag, int nIcon)
		   : CXRecsetTree(pSet, pTurboSet, nTag, nIcon)
		{
		};
		long GetCode()
		{
			if(m_pTurboSet)
			   return ((CAziendeTurboSet*)m_pTurboSet)->m_Codice;
			else
			 return ((CAziendeSet*)m_pSet)->m_Codice;
		};
		CString GetLabel()
		{
			if(m_pTurboSet)
			   return ((CAziendeTurboSet*)m_pTurboSet)->m_RagioneSociale;
			else
			 return ((CAziendeSet*)m_pSet)->m_RagioneSociale;
		};
};



/////////////////////////////////////////////////////////////////////////////
// CAziendeTreeCtrl

CAziendeTreeCtrl::CAziendeTreeCtrl()
{
}

CAziendeTreeCtrl::~CAziendeTreeCtrl()
{
  m_HTreeImportanti = NULL;
  m_HTreeAlfabetica = NULL;
}


BEGIN_MESSAGE_MAP(CAziendeTreeCtrl, CXTreeCtrl)
	//{{AFX_MSG_MAP(CAziendeTreeCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAziendeTreeCtrl message handlers

void CAziendeTreeCtrl::SetDoc(CDocument *pDoc)
{
  m_pDoc = (CWinSigmaDoc*)pDoc;
}

/**********************************************************************************
* Funzione:    Populate
* Descrizione: Modella un sottoablbero con il relativo recordset
* Parametri:   L'etichetta del sottoalbero e il codice dell'elemento selezionato
* Note:
**********************************************************************************/
void CAziendeTreeCtrl::Populate(CString strLabel, long nCodeSelected)
{
  long         nCodeMax;
	HTREEITEM     hTreeItem, hTreeSelectedItem, hTreeParentItem, hTreeInitialItem;
	CString       strItem;
	CXRecsetTree* pXTree;
	CRecordset*   pSet;
 
  if(strLabel != TREELABEL_AZIENDEALFABETICA)
  {
    CXTreeCtrl::Populate(strLabel, nCodeSelected);
    return;
  }
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
  /*---- cerco il record coinvolto e il codice massimo ----*/
	for(nCodeMax = 0, SET_START(pSet);
      !pSet->IsEOF() && nCodeSelected != pXTree->GetCode();
      pSet->MoveNext())
    if(nCodeMax < pXTree->GetCode())
      nCodeMax = pXTree->GetCode();
  if(pSet->IsEOF())
  {
    /*--- mi sincronizzo con il record nuovo ----*/
    for(SET_START(pSet);
      !pSet->IsEOF() && nCodeMax != pXTree->GetCode();
      pSet->MoveNext());
  }  
  /*---- analizzo i vari casi ----*/
  if(nCodeSelected == -1)
  {
    /*----- e' stata creata una nuova azienda: cerco la sottocartella -----*/
    for(hTreeInitialItem = GetChildItem(hTreeParentItem);
        hTreeInitialItem;
	    	hTreeInitialItem = GetNextSiblingItem(hTreeInitialItem))
      if(GetItemText(hTreeInitialItem) == CString(pXTree->GetLabel()[0]))
        break;
    if(!hTreeInitialItem)
    {
      /*---- la cartella con l'iniziale non c'e': la creo ----*/
      hTreeInitialItem = InsertItem(CString(pXTree->GetLabel()[0]), 
  		                              4, 4, hTreeParentItem);
    }
    /*---- inserisco l'item ----*/
    hTreeSelectedItem = InsertItem(pXTree->GetLabel(), 
		                               pXTree->m_nIcon, pXTree->m_nIcon, hTreeInitialItem);
		SetItemData(hTreeSelectedItem, pXTree->GetCode());
  }
  else
  {
    /*---- e' stata eliminata o modificata un'azienda: cerco il relativo item ----*/
    for(hTreeInitialItem = GetChildItem(hTreeParentItem);
        hTreeInitialItem;
	    	hTreeInitialItem = GetNextSiblingItem(hTreeInitialItem))
    {
      for(hTreeItem = GetChildItem(hTreeInitialItem);
          hTreeItem;
      	  hTreeItem = GetNextSiblingItem(hTreeItem))
      {
         if(GetItemData(hTreeItem) == (DWORD)nCodeSelected)
          break;
      }
      if(hTreeItem)
        break;
    }
    if(hTreeItem)
    {
      /*---- elimino l'item ----*/
      DeleteItem(hTreeItem);
      if(!pSet->IsEOF())
      {
        /*---- e' stata modificata un'azienda: cerco la sottocartella -----*/
        for(hTreeInitialItem = GetChildItem(hTreeParentItem);
            hTreeInitialItem;
    	    	hTreeInitialItem = GetNextSiblingItem(hTreeInitialItem))
          if(GetItemText(hTreeInitialItem) == CString(pXTree->GetLabel()[0]))
            break;
        if(!hTreeInitialItem)
        {
          /*---- la cartella con l'iniziale non c'e': la creo ----*/
          hTreeInitialItem = InsertItem(CString(pXTree->GetLabel()[0]), 
      		                              pXTree->m_nIcon, pXTree->m_nIcon, hTreeParentItem);
        }
        /*---- inserisco l'item ----*/
        hTreeSelectedItem = InsertItem(pXTree->GetLabel(), 
    		                               pXTree->m_nIcon, pXTree->m_nIcon, hTreeInitialItem);
        SetItemData(hTreeSelectedItem, pXTree->GetCode());
        SortChildren(hTreeInitialItem);
      }
    }
  }
  /*---- riordino l'albero degli operatori -----*/
  SortChildren(hTreeParentItem);
  m_bDenySelection = FALSE;
  SelectItem(hTreeSelectedItem);
//  Sincronize(strLabel);
}

/********************************************************************
* Funzione   : PopulateTree
* Descrizione: Cancella e ricostruisce l'albero delle aziende selezionando
               alla fine l'azienda di cui si passa il codice 
* Parametri  : 
* Ritorno    : 
* Note       : Se il parametro passato e' SEARCH_FIRST_AZIENDA, significa
               che non conosciamo il codice della prima azienda,
							 ma che vogliamo selezionare la prima azienda che legge
							 dal recordset
*********************************************************************/
void CAziendeTreeCtrl::PopulateTree(void)
{
  char ch;
  CString str;
	CXRecsetTree* pXTree;
  CAziendeSet*  pSet;
  HTREEITEM     hTreeLettera, hTreeItem;

 	SelectItem(NULL);
  /*----- lista aziende importanti -----*/
  m_HTreeImportanti = InsertItem(TREELABEL_AZIENDEIMPORTANTI, 2, 2);
	pXTree = new CAziendeImportantiTree(m_pDoc->m_pAziendeImportantiSet, TREEITEM_AZIENDEIMPORTANTI, 3);
	SetItemData(m_HTreeImportanti, (DWORD)pXTree);
	CXTreeCtrl::Populate(TREELABEL_AZIENDEIMPORTANTI, -1);
	/*----- lista aziende afabetica -----*/
  m_HTreeAlfabetica = InsertItem(TREELABEL_AZIENDEALFABETICA, 4, 4);
	pXTree = new CAziendeAlfabeticaTree(m_pDoc->m_pAziendeSet, m_pDoc->m_pAziendeTurboSet, TREEITEM_AZIENDEALFABETICA, 5);
	SetItemData(m_HTreeAlfabetica, (DWORD)pXTree);
  pSet = m_pDoc->m_pAziendeSet;
  ch = 0;

  CString csRS;
  CString csCH(ch);
  
  for(SET_START(pSet); !pSet->IsEOF(); pSet->MoveNext())
  {
	  if (((CWinSigmaApp*)AfxGetApp())->m_bPrimaVolta)
      Spacciatore();

    csRS = pSet->m_RagioneSociale[0];
    csRS.MakeUpper();
    
    if( csCH !=  csRS )
    {
      ch = pSet->m_RagioneSociale[0];
      csCH = ch;
      csCH.MakeUpper();

      str.Format("%c", ch);
      hTreeLettera = InsertItem(str, 4, 4, m_HTreeAlfabetica);
      SetItemData(hTreeLettera, (DWORD)NULL);
    }
    hTreeItem = InsertItem(pSet->m_RagioneSociale, 5, 5, hTreeLettera);
    SetItemData(hTreeItem, (DWORD)pSet->m_Codice);
  }
  /*----- -----*/
	SelectItem(m_HTreeAlfabetica);
}

void CAziendeTreeCtrl::SelectedTree(int nSelected)
{
    m_pDoc->m_nSelectedTreeAziende = nSelected;
}

/**********************************************************************************
* Funzione:    SelectItemData
* Descrizione: seleziona l'item con codice specificato nel folder specificato
* Parametri: 
* Note:
**********************************************************************************/
HTREEITEM CAziendeTreeCtrl::SelectItemData(HTREEITEM hItemFolder, long nCode)

{
	HTREEITEM h, hTreeItem = GetFolderItem(TREELABEL_AZIENDEALFABETICA);

	for(hTreeItem = GetChildItem(hTreeItem);
			hTreeItem; 
			hTreeItem = GetNextSiblingItem(hTreeItem))
	{
    
		if(h = CXTreeCtrl::SelectItemData(hTreeItem, nCode))
			return h;
	}
	return NULL;
}

