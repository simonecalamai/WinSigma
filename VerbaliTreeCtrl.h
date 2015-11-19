#if !defined(AFX_VERBALITREECTRL_H__4DD6DDC1_BB94_11D7_B754_0080AD70B2EE__INCLUDED_)
#define AFX_VERBALITREECTRL_H__4DD6DDC1_BB94_11D7_B754_0080AD70B2EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VerbaliTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVerbaliTreeCtrl window

class CVerbaliTreeCtrl : public CXTreeCtrl
{
// Construction
public:
	CVerbaliTreeCtrl();

// Attributes
public:
  HTREEITEM m_HTreeUltimoMese;
  HTREEITEM m_HTreePrecedenti;
  HTREEITEM m_hTreeFattureProforma;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVerbaliTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	CWinSigmaDoc* m_pDoc;
  void SelectedTree(int nSelected);
	void SetDoc(CDocument *pDoc);
  void PopulateTree(void);
	virtual ~CVerbaliTreeCtrl();

	// Generated message map functions
protected:
  static int CALLBACK Sort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

  void ReformatTree(HTREEITEM hTreeParentItem);
	//{{AFX_MSG(CVerbaliTreeCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VERBALITREECTRL_H__4DD6DDC1_BB94_11D7_B754_0080AD70B2EE__INCLUDED_)
