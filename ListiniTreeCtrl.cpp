// ListiniTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "WinSigma.h"

#include "WinSigmaDoc.h"
#include "MainFrm.h"
#include "XTreeCtrl.h"
#include "ListiniTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CScadutiTree : public CXRecsetTree
{
  public:
		CScadutiTree(CRecordset* pSet, int nTag, int nIcon) 
		  : CXRecsetTree(pSet, nTag, nIcon)
		{
		};
		long GetCode()
		{
			return ((CListiniSet*)m_pSet)->m_Codice;
		};
		CString GetLabel()
		{
			return ((CListiniSet*)m_pSet)->m_Nome;
		};
};

class CInVigoreTree : public CXRecsetTree
{
  public:
		CInVigoreTree(CRecordset* pSet, int nTag, int nIcon) 
		  : CXRecsetTree(pSet, nTag, nIcon)
		{
		};
		long GetCode()
		{
			return ((CListiniSet*)m_pSet)->m_Codice;
		};
		CString GetLabel()
		{
			return ((CListiniSet*)m_pSet)->m_Nome;
		};
};

class CInElaborazioneTree : public CXRecsetTree
{
  public:
		CInElaborazioneTree(CRecordset* pSet, int nTag, int nIcon) 
		  : CXRecsetTree(pSet, nTag, nIcon)
		{
		};
		long GetCode()
		{
			return ((CListiniSet*)m_pSet)->m_Codice;
		};
		CString GetLabel()
		{
			return ((CListiniSet*)m_pSet)->m_Nome;
		};
};

/////////////////////////////////////////////////////////////////////////////
// CListiniTreeCtrl

CListiniTreeCtrl::CListiniTreeCtrl()
{
}

CListiniTreeCtrl::~CListiniTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CListiniTreeCtrl, CXTreeCtrl)
	//{{AFX_MSG_MAP(CListiniTreeCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CListiniTreeCtrl::PopulateTree(void)
{
  HTREEITEM hTreeItem;
	CXRecsetTree* pXTree;

 	SelectItem(NULL);
	/*----- listini scaduti -----*/
	hTreeItem = InsertItem(TREELABEL_SCADUTI, 0, 0);
	pXTree = new CScadutiTree(m_pDoc->m_pListiniScadutiSet, TREEITEM_SCADUTI, 1);
	SetItemData(hTreeItem, (DWORD)pXTree);
	Populate(TREELABEL_SCADUTI, -1);
	/*----- listini in vigore -----*/
	hTreeItem = InsertItem(TREELABEL_INVIGORE, 2, 2);
	pXTree = new CInVigoreTree(m_pDoc->m_pListiniInVigoreSet, TREEITEM_INVIGORE, 3);
	SetItemData(hTreeItem, (DWORD)pXTree);
	Populate(TREELABEL_INVIGORE, -1);
	/*----- listini in elaborazione -----*/
	hTreeItem = InsertItem(TREELABEL_INELABORAZIONE, 4, 4);
	pXTree = new CInElaborazioneTree(m_pDoc->m_pListiniInElaborazioneSet, TREEITEM_INELABORAZIONE, 5);
	SetItemData(hTreeItem, (DWORD)pXTree);
	Populate(TREELABEL_INELABORAZIONE, -1);
}

/////////////////////////////////////////////////////////////////////////////
// CListiniTreeCtrl message handlers

void CListiniTreeCtrl::SetDoc(CDocument *pDoc)
{
  m_pDoc = (CWinSigmaDoc*)pDoc;
}


void CListiniTreeCtrl::SelectedTree(int nSelected)
{
  if(m_pDoc == NULL)
    return;
  m_pDoc->m_nSelectedTreeListini = nSelected;
}