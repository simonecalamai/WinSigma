#if !defined(AFX_FATTURETREECTRL_H__6197C5E0_BB85_11D7_B754_0080AD70B2EE__INCLUDED_)
#define AFX_FATTURETREECTRL_H__6197C5E0_BB85_11D7_B754_0080AD70B2EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FattureTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFattureTreeCtrl window

class CFattureTreeCtrl : public CXTreeCtrl
{
// Construction
public:
	CFattureTreeCtrl();

// Attributes
public:
  HTREEITEM m_hTreeFattureDaEmettere;
// Operations
public:
  void PopulateTree(void);
  void Populate(CString strLabel, long nCodeSelected);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFattureTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	CWinSigmaDoc* m_pDoc;
	void SetDoc(CDocument *pDoc);
  void SelectedTree(int nSelected);
  void DeleteItemAzienda(long codice);
	virtual ~CFattureTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFattureTreeCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FATTURETREECTRL_H__6197C5E0_BB85_11D7_B754_0080AD70B2EE__INCLUDED_)
