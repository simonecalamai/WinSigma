#if !defined(AFX_AZIENDETREECTRL_H__62B43360_BB7A_11D7_B754_0080AD70B2EE__INCLUDED_)
#define AFX_AZIENDETREECTRL_H__62B43360_BB7A_11D7_B754_0080AD70B2EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AziendeTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAziendeTreeCtrl window

class CAziendeTreeCtrl : public CXTreeCtrl
{
// Construction
public:
	CAziendeTreeCtrl();

// Attributes
public:

// Operations
public:
  HTREEITEM m_HTreeImportanti;
  HTREEITEM m_HTreeAlfabetica;
  
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAziendeTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
  void Populate(CString strLabel, long nCode);
	void PopulateTree(void);
	CWinSigmaDoc* m_pDoc;
	void SetDoc(CDocument *pDoc);
	virtual ~CAziendeTreeCtrl();
  void SelectedTree(int nSelected);
  HTREEITEM SelectItemData(HTREEITEM hItemFolder, long nCode);
protected:
	// Generated message map functions
protected:
	//{{AFX_MSG(CAziendeTreeCtrl)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AZIENDETREECTRL_H__62B43360_BB7A_11D7_B754_0080AD70B2EE__INCLUDED_)
