// StrumentiTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "WinSigma.h"
#include "WinSigmaDoc.h"
#include "MainFrm.h"
#include "XTreeCtrl.h"
#include "StrumentiTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class COperatoriTree : public CXRecsetTree
{
  public:
		COperatoriTree(CRecordset* pSet, int nTag, int nIcon)
		   : CXRecsetTree(pSet, nTag, nIcon)
		{
		};
		long GetCode()
		{
			return ((COperatoriSet*)m_pSet)->m_Codice;
		};
		CString GetLabel()
		{
			COperatoriSet* pSet = (COperatoriSet*)m_pSet;
			return pSet->m_Cognome + " " + pSet->m_Nome;
		};
};

class CPagamentiTree : public CXRecsetTree
{
  public:
		CPagamentiTree(CRecordset* pSet, int nTag, int nIcon)
		   : CXRecsetTree(pSet, nTag, nIcon)
		{
		};
		long GetCode()
		{
			return ((CTipiPagamentoSet*)m_pSet)->m_Codice;
		};
		CString GetLabel()
		{
			return ((CTipiPagamentoSet*)m_pSet)->m_Nome;
		};
};

class CMaterialiTree : public CXRecsetTree
{
  public:
		CMaterialiTree(CRecordset* pSet, int nTag, int nIcon)
		   : CXRecsetTree(pSet, nTag, nIcon)
		{
		};
		long GetCode()
		{
			return ((CTipiMaterialeSet*)m_pSet)->m_Codice;
		};
		CString GetLabel()
		{
			CString str; // Modificata la label
			str.Format("%s - %s", ((CTipiMaterialeSet*)m_pSet)->m_ID, ((CTipiMaterialeSet*)m_pSet)->m_Nome);
			return str;
		};
};

class CMarchiTree : public CXRecsetTree
{
  public:
		CMarchiTree(CRecordset* pSet, int nTag, int nIcon)
		   : CXRecsetTree(pSet, nTag, nIcon)
		{
		};
		CMarchiTree(CRecordset* pSet, CRecordset* pTurboSet, int nTag, int nIcon)
		   : CXRecsetTree(pSet, pTurboSet, nTag, nIcon)
		{
		};
		long GetCode()
		{
			if(m_pTurboSet)
			  return ((CMarchiTurboSet*)m_pTurboSet)->m_Codice;
			else
        return ((CMarchiSet*)m_pSet)->m_Codice;
		};
		CString GetLabel()
		{
			if(m_pTurboSet)
			  return ((CMarchiTurboSet*)m_pTurboSet)->m_Nome;
			else
  			return ((CMarchiSet*)m_pSet)->m_Nome;
		};
};

/////////////////////////////////////////////////////////////////////////////
// CStrumentiTreeCtrl

CStrumentiTreeCtrl::CStrumentiTreeCtrl()
{
}

CStrumentiTreeCtrl::~CStrumentiTreeCtrl()
{
  m_HTreeOperatori = NULL;
  m_HTreePagamenti = NULL;
  m_HTreeMateriali = NULL;
  m_HTreeMarchi    = NULL;
}


BEGIN_MESSAGE_MAP(CStrumentiTreeCtrl, CXTreeCtrl)
	//{{AFX_MSG_MAP(CStrumentiTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CStrumentiTreeCtrl::SetDoc(CDocument *pDoc)
{
  m_pDoc = (CWinSigmaDoc*)pDoc;
}

void CStrumentiTreeCtrl::PopulateTree(void)
{
	CXRecsetTree* pXTree;

 	SelectItem(NULL);
	/*----- lista operatori -----*/
	m_HTreeOperatori = InsertItem(TREELABEL_OPERATORI, 0, 0);
	pXTree = new COperatoriTree(m_pDoc->m_pOperatoriSet, TREEITEM_OPERATORI, 1);
	SetItemData(m_HTreeOperatori, (DWORD)pXTree);
	Populate(TREELABEL_OPERATORI, -1);
	Expand(m_HTreeOperatori, TVE_COLLAPSE);
	/*----- lista pagamenti -----*/
  m_HTreePagamenti = InsertItem(TREELABEL_PAGAMENTI, 2, 2);
	pXTree = new CPagamentiTree(m_pDoc->m_pTipiPagamentoSet, TREEITEM_PAGAMENTI, 3);
	SetItemData(m_HTreePagamenti, (DWORD)pXTree);
	Populate(TREELABEL_PAGAMENTI, -1);
	Expand(m_HTreePagamenti, TVE_COLLAPSE);
	/*----- lista materiali -----*/
  m_HTreeMateriali = InsertItem(TREELABEL_MATERIALI, 4, 4);
	pXTree = new CMaterialiTree(m_pDoc->m_pTipiMaterialeSet, TREEITEM_MATERIALI, 5);
	SetItemData(m_HTreeMateriali, (DWORD)pXTree);
	Populate(TREELABEL_MATERIALI, -1);
	Expand(m_HTreeMateriali, TVE_COLLAPSE);
	/*----- lista marchi -----*/
  m_HTreeMarchi = InsertItem(TREELABEL_MARCHI, 6, 6);
	pXTree = new CMarchiTree(m_pDoc->m_pMarchiSet, TREEITEM_MARCHI, 7);
//	pXTree = new CMarchiTree(m_pDoc->m_pMarchiSet, m_pDoc->m_pMarchiTurboSet, TREEITEM_MARCHI, 7);
	SetItemData(m_HTreeMarchi, (DWORD)pXTree);
	Populate(TREELABEL_MARCHI, -1);
	Expand(m_HTreeMarchi, TVE_COLLAPSE);

	SelectItem(m_HTreeOperatori);
}


/////////////////////////////////////////////////////////////////////////////
// CStrumentiTreeCtrl message handlers

