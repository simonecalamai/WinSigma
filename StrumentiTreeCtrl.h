#if !defined(AFX_STRUMENTITREECTRL_H__97B28F00_BC31_11D7_B754_0080AD70B2EE__INCLUDED_)
#define AFX_STRUMENTITREECTRL_H__97B28F00_BC31_11D7_B754_0080AD70B2EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StrumentiTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStrumentiTreeCtrl window

class CStrumentiTreeCtrl : public CXTreeCtrl
{
// Construction
public:
	CStrumentiTreeCtrl();

// Attributes
protected:
  HTREEITEM m_HTreeOperatori;
  HTREEITEM m_HTreePagamenti;
  HTREEITEM m_HTreeMateriali;
  HTREEITEM m_HTreeMarchi;

public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStrumentiTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	CWinSigmaDoc* m_pDoc;
	virtual ~CStrumentiTreeCtrl();
	void SetDoc(CDocument *pDoc);
  void PopulateTree(void);
protected:
  void ReformatTree(HTREEITEM hTreeParentItem);

	// Generated message map functions
protected:
	//{{AFX_MSG(CStrumentiTreeCtrl)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STRUMENTITREECTRL_H__97B28F00_BC31_11D7_B754_0080AD70B2EE__INCLUDED_)
