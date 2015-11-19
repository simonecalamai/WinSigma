#if !defined(AFX_LISTINITREECTRL_H__6C27DEC0_BBA1_11D7_B754_0080AD70B2EE__INCLUDED_)
#define AFX_LISTINITREECTRL_H__6C27DEC0_BBA1_11D7_B754_0080AD70B2EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListiniTreeCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListiniTreeCtrl window

class CListiniTreeCtrl : public CXTreeCtrl
{
// Construction
public:
	CListiniTreeCtrl();

// Attributes
public:
  HTREEITEM m_hTreeScaduti;
  HTREEITEM m_hTreeInVigore;
  HTREEITEM m_hTreeInElaborazione;

// Operations
public:
	void PopulateTree(void);
  void PopulateScaduti(long nCodeSelected);
  void PopulateInVigore(long nCodeSelected);
  void PopulateInElaborazione(long nCodeSelected);
  void ActivateTree();
	void SincronizeScaduti();
	void SincronizeInVigore();
	void SincronizeInElaborazione();
  void SelectedTree(int nSelected);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListiniTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetDoc(CDocument *pDoc);
	CWinSigmaDoc* m_pDoc;
	virtual ~CListiniTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListiniTreeCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTINITREECTRL_H__6C27DEC0_BBA1_11D7_B754_0080AD70B2EE__INCLUDED_)
