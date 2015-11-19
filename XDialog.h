#if !defined(AFX_XDIALOG_H__868237C9_0C14_4FE2_A474_B0144DD5B2E4__INCLUDED_)
#define AFX_XDIALOG_H__868237C9_0C14_4FE2_A474_B0144DD5B2E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXDialog dialog

class CXDialog : public CDialog
{
// Construction
public:
	virtual CBrush* GetFocusBkBrush();
	CXDialog(UINT nIDTemplate, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXDialog)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButtonNext();
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBrush m_BrushFocusBk;

	// Generated message map functions
	//{{AFX_MSG(CXDialog)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XDIALOG_H__868237C9_0C14_4FE2_A474_B0144DD5B2E4__INCLUDED_)
