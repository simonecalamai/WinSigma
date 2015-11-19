#if !defined(AFX_XFORMVIEW_H__CAA72C78_4A92_40AD_B034_A39AC8896820__INCLUDED_)
#define AFX_XFORMVIEW_H__CAA72C78_4A92_40AD_B034_A39AC8896820__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XFormView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CXFormView : public CFormView
{
protected:
	CXFormView(int nId);           // protected constructor used by dynamic creation

// Form Data
public:
	//{{AFX_DATA(CXFormView)
	//}}AFX_DATA

// Attributes
public:
  CRecordset* m_pSet;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXFormView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CXFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
  virtual void LoadCurRecord(BOOL bData) = 0;
	virtual BOOL IsDataChanged() = 0;
	virtual BOOL ValidateData() = 0;
  virtual BOOL NewRecord() = 0;
	virtual BOOL SaveRecord() = 0;
	virtual BOOL DeleteRecord() = 0;
	virtual void EnableControls(BOOL bEnable) = 0;
	virtual CString GetToolTip(int nID);

	// Generated message map functions
	//{{AFX_MSG(CXFormView)
	afx_msg void OnNuovo();
	afx_msg void OnModifica();
	afx_msg void OnElimina();
	afx_msg void OnCancel();
	afx_msg void OnOK();
  afx_msg BOOL OnToolTipNotify(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XFORMVIEW_H__CAA72C78_4A92_40AD_B034_A39AC8896820__INCLUDED_)
