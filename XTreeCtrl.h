#if !defined(AFX_XTREECTRL_H__903D6010_F148_4B70_A6F3_6D36985EADA3__INCLUDED_)
#define AFX_XTREECTRL_H__903D6010_F148_4B70_A6F3_6D36985EADA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XTreeCtrl.h : header file
//

class CXRecsetTree : public CObject
{
  public:
	  CRecordset* m_pSet;
		CRecordset* m_pTurboSet;
		int         m_nTag;
    int         m_nIcon;
	  CXRecsetTree(CRecordset* pSet, int nTag, int nIcon)
		{ 
		  m_pSet  = pSet;
			m_pTurboSet = NULL;
			m_nTag  = nTag;
			m_nIcon = nIcon;
		};
	  CXRecsetTree(CRecordset* pSet, CRecordset* pTurboSet, int nTag, int nIcon)
		{ 
		  m_pSet  = pSet;
			m_pTurboSet = pTurboSet;
			m_nTag  = nTag;
			m_nIcon = nIcon;
		};
		virtual long    GetCode() = 0;
		virtual CString GetLabel() = 0;
};

/////////////////////////////////////////////////////////////////////////////
// CXTreeCtrl window

class CXTreeCtrl : public CTreeCtrl
{
// Construction
public:
	CXTreeCtrl();

// Attributes
public:
    int (CALLBACK *m_pfnCompare)(LPARAM, LPARAM, LPARAM);
// Operations
public:
  virtual void PopulateTree(void) = 0;
  void Populate(CString strLabel, long nCode);
	void Sincronize(CString strLabel);
  void Activate();
	virtual HTREEITEM SelectItemData(HTREEITEM hTreeItem, long nCode);
	virtual HTREEITEM GetFolderItem(CString strLabel);
protected:
  BOOL      m_bDenySelection;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CXTreeCtrl)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XTREECTRL_H__903D6010_F148_4B70_A6F3_6D36985EADA3__INCLUDED_)
