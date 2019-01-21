// FattureTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "WinSigma.h"
#include "XTreeCtrl.h"
#include "WinSigmaDoc.h"
#include "FattureTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CFattureDaEmettereTree : public CXRecsetTree
{
  public:
		CFattureDaEmettereTree(CRecordset* pSet, int nTag, int nIcon)
		   : CXRecsetTree(pSet, nTag, nIcon)
		{
		};
		long GetCode()
		{
      return ((CVerbaliSet*)m_pSet)->m_CodiceAzFattura;
		};
		CString GetLabel()
		{
      return ((CVerbaliSet*)m_pSet)->m_NomeAzFattura;
		};
};


class CFattureEmesseTree : public CXRecsetTree
{
public:
  CFattureEmesseTree(CRecordset* pSet, int nTag, int nIcon)
    : CXRecsetTree(pSet, nTag, nIcon)
  {
  };
  long GetCode()
  {
    CFattureSet* pFattureSet = (CFattureSet*)m_pSet;
    if(pFattureSet->m_TipoDocumento == FATTURA)
		{
      m_nIcon = 3;
		}
    else
		{
      m_nIcon = 4;
		}
    return pFattureSet->m_Codice;
  }
  CString GetLabel()
  {
    CFattureSet* pFattureSet = (CFattureSet*)m_pSet;
    if(pFattureSet->m_TipoDocumento == FATTURA)
    {  
			m_nIcon = 3;
		}
    else
		{
      m_nIcon = 4;
		}
    return pFattureSet->m_RagioneSociale;
  }
};

/////////////////////////////////////////////////////////////////////////////
// CFattureTreeCtrl

CFattureTreeCtrl::CFattureTreeCtrl()
{
  m_hTreeFattureDaEmettere = NULL;
}

CFattureTreeCtrl::~CFattureTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CFattureTreeCtrl, CXTreeCtrl)
	//{{AFX_MSG_MAP(CFattureTreeCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFattureTreeCtrl message handlers

void CFattureTreeCtrl::SetDoc(CDocument *pDoc)
{
  m_pDoc = (CWinSigmaDoc*)pDoc;
}

/**********************************************************************************
* Funzione:    Populate
* Descrizione: Modella un sottoablbero con il relativo recordset
* Parametri:   L'etichetta del sottoalbero e il codice dell'elemento selezionato
* Note:
**********************************************************************************/
void CFattureTreeCtrl::Populate(CString strLabel, long nCodeSelected)
{
  long          nCodeMax;
	HTREEITEM     hTreeSelectedItem, hTreeParentItem;
	CString       strItem;
	CXRecsetTree* pXTree;
	CRecordset*   pSet;
 
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
  pSet->m_strSort = "Codice ASC";
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
  if(strLabel != TREELABEL_FATTUREDAEMETTERE)
  {
    if(nCodeSelected == -1)
    {
      // Devo aggiornare l'albero delle fatture emesse: inserisco il nuovo item
      strItem.Format("N°. %d - %s", ((CFattureSet*)pSet)->m_Numero, ((CFattureSet*)pSet)->m_RagioneSociale);
      hTreeSelectedItem = InsertItem(strItem, pXTree->m_nIcon, pXTree->m_nIcon, hTreeParentItem);
    	SetItemData(hTreeSelectedItem, pXTree->GetCode());
			if(((CFattureSet*)pSet)->m_Elett == 1) pXTree->m_nIcon = 5;
      SetItemImage(hTreeSelectedItem, pXTree->m_nIcon, pXTree->m_nIcon);
    }
    else
    {
      for(hTreeSelectedItem = GetChildItem(hTreeParentItem);
          hTreeSelectedItem; hTreeSelectedItem = GetNextSiblingItem(hTreeSelectedItem))
          {
            if(GetItemData(hTreeSelectedItem) == (DWORD)nCodeSelected)
              break;
          }
      if(hTreeSelectedItem)
      {
        for(SET_START(pSet); !pSet->IsEOF(); pSet->MoveNext())
        {
          if(nCodeSelected == pXTree->GetCode())
            break;
        }
        if(pSet->IsEOF())
          DeleteItem(hTreeSelectedItem);
        else
        {
          strItem.Format("N°. %d - %s", ((CFattureSet*)pSet)->m_Numero, pXTree->GetLabel());
          SetItemText(hTreeSelectedItem, strItem);
          SetItemData(hTreeSelectedItem, pXTree->GetCode());
					if(((CFattureSet*)pSet)->m_Elett == 1) pXTree->m_nIcon = 5;
          SetItemImage(hTreeSelectedItem, pXTree->m_nIcon, pXTree->m_nIcon);
        }
      }
      else
      {
        // E' stata ripristinata una fattura: la rimetto nell'albero
        strItem.Format("N°. %d - %s", ((CFattureSet*)pSet)->m_Numero, ((CFattureSet*)pSet)->m_RagioneSociale);
        hTreeSelectedItem = InsertItem(strItem, pXTree->m_nIcon, pXTree->m_nIcon, hTreeParentItem);
    		SetItemData(hTreeSelectedItem, pXTree->GetCode());
				if(((CFattureSet*)pSet)->m_Elett == 1) pXTree->m_nIcon = 5;
        SetItemImage(hTreeSelectedItem, pXTree->m_nIcon, pXTree->m_nIcon);
      }
    }
  }
  if(strLabel == TREELABEL_FATTUREDAEMETTERE)
  {
    // Verifico che non ci sia già un item che faccia riferimento a quella azienda
    for(hTreeSelectedItem = GetChildItem(hTreeParentItem);
        hTreeSelectedItem; hTreeSelectedItem = GetNextSiblingItem(hTreeSelectedItem))
        {
          if(GetItemData(hTreeSelectedItem) == (DWORD)nCodeSelected)
            break;
        }
    // L'item non c'è, lo aggiungo
    if(!hTreeSelectedItem)
    {
      hTreeSelectedItem = InsertItem(pXTree->GetLabel(), 1, 1, hTreeParentItem);
      SetItemData(hTreeSelectedItem, pXTree->GetCode());
    }
    else
    {
      // Se non ci sono altre fatture a questo intesatatario, elimino l'item
      if(hTreeSelectedItem)
      {
        for(SET_START(pSet); !pSet->IsEOF(); pSet->MoveNext())
        {
          if(nCodeSelected == pXTree->GetCode())
            break;
        }
        if(pSet->IsEOF())
          DeleteItem(hTreeSelectedItem);
        else
        {
          SetItemText(hTreeSelectedItem, pXTree->GetLabel());
          SetItemData(hTreeSelectedItem, pXTree->GetCode());
        }
      }
    }
    SortChildren(hTreeParentItem);
  }
  SelectItem(hTreeSelectedItem);
  m_bDenySelection = FALSE;
  Sincronize(strLabel);
}

void CFattureTreeCtrl::PopulateTree(void)
{
	CXRecsetTree* pXEmesseTree;
  HTREEITEM     hTreeAnno, hTreeItem;  
  CFattureSet* pEmesseSet = m_pDoc->m_pFattureEmesseSet;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  int startYear = pApp->GetProfileInt(FATTURAZIONE, START_YEAR, CTime::GetCurrentTime().GetYear());
  int endYear = pApp->GetProfileInt(FATTURAZIONE, END_YEAR, CTime::GetCurrentTime().GetYear());
  int year;
  CString strAnno, str;
  SelectItem(NULL);
  // Fatture emesse: faccio una cartellina per ogni anno
  for(year = startYear; year <= endYear; year++)
  {
	  if (((CWinSigmaApp*)AfxGetApp())->m_bPrimaVolta)
      Spacciatore();
    
    CTime Start(year, 1, 1, 0, 0, 0);
    CTime End(year, 12, 31, 23, 59, 59);
    // Prendo le fatture dell'anno selezionato
    pEmesseSet->m_strFilter.Format("Data >= '%s' AND Data <= '%s' AND Archiviata = 0", Start.Format("%Y-%m-%d"), End.Format("%Y-%m-%d"));
    pEmesseSet->m_strSort = "Codice ASC";
    pEmesseSet->Requery();
    strAnno .Format("%d", year);
    hTreeAnno = InsertItem(strAnno, 2, 2);
    pXEmesseTree = new CFattureEmesseTree(pEmesseSet, TREEITEM_FATTUREEMESSE, 3);
    SetItemData(hTreeAnno, (DWORD)pXEmesseTree);
    for(SET_START(pEmesseSet); !pEmesseSet->IsEOF(); pEmesseSet->MoveNext())
    {
	    if (((CWinSigmaApp*)AfxGetApp())->m_bPrimaVolta)
        Spacciatore();
      
      str.Format("N°. %d - %s", pEmesseSet->m_Numero, pEmesseSet->m_RagioneSociale);
      if(pEmesseSet->m_TipoDocumento == FATTURA)
				if(pEmesseSet->m_Elett == 1)
	        hTreeItem = InsertItem(str, 5, 5, hTreeAnno);
				else
	        hTreeItem = InsertItem(str, 3, 3, hTreeAnno);
      else
        hTreeItem = InsertItem(str, 4, 4, hTreeAnno);
      SetItemData(hTreeItem, (DWORD)pEmesseSet->m_Codice);
    }
  }
  pEmesseSet->m_strFilter= "";
  pEmesseSet->Requery();
  
  // Fatture da emettere
  CXRecsetTree* pXTree;
  CVerbaliSet* pDaEmettereSet = m_pDoc->m_pVerbaliAperti;
  CVerbaliSet* pVerbaliInFatturazione = new CVerbaliSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
  // Raggruppo i verbali in fatturazione per cliente
  pDaEmettereSet->m_strFilter.Format("Fattura = 0 AND IntestatarioFattura <> 0 GROUP BY IDIntestatarioFattura");
  pDaEmettereSet->Requery();
  // Creo l'alberino
  m_hTreeFattureDaEmettere = InsertItem(TREELABEL_FATTUREDAEMETTERE, 0, 0);
  pXTree = new CFattureDaEmettereTree(pDaEmettereSet, TREEITEM_FATTUREDAEMETTERE, 1);
  SetItemData(m_hTreeFattureDaEmettere, (DWORD)pXTree);
  //  Riempio l'albero
  for(SET_START(pDaEmettereSet); !pDaEmettereSet->IsEOF(); pDaEmettereSet->MoveNext())
  {
	  if (((CWinSigmaApp*)AfxGetApp())->m_bPrimaVolta)
      Spacciatore();
    
    hTreeItem = InsertItem(pDaEmettereSet->m_NomeAzFattura, 1, 1, m_hTreeFattureDaEmettere);
    SetItemData(hTreeItem, pDaEmettereSet->m_CodiceAzFattura);
  }
  SortChildren(m_hTreeFattureDaEmettere);
  SelectItem(m_hTreeFattureDaEmettere);
}

void CFattureTreeCtrl::SelectedTree(int nSelected)
{
  m_pDoc->m_nSelectedTreeFatture = nSelected;
}


void CFattureTreeCtrl::DeleteItemAzienda(long codice)
{
	HTREEITEM hTreeSelectedItem, hTreeParentItem;
  hTreeParentItem = GetFolderItem(TREELABEL_FATTUREDAEMETTERE);
  // Cerco l'item da cancellare
  for(hTreeSelectedItem = GetChildItem(hTreeParentItem); hTreeSelectedItem; hTreeSelectedItem = GetNextSiblingItem(hTreeSelectedItem))
  {
    if(GetItemData(hTreeSelectedItem) == (DWORD)codice)
      break;
  }
  if(hTreeSelectedItem)
    DeleteItem(hTreeSelectedItem);
}