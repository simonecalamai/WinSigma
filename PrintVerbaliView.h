#if !defined(AFX_PRINTVERBALIVIEW_H__A765C600_2F00_11D8_B754_00C026108782__INCLUDED_)
#define AFX_PRINTVERBALIVIEW_H__A765C600_2F00_11D8_B754_00C026108782__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrintVerbaliView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrintVerbaliView dialog

class CPrintVerbaliView : public CDialog
{
// Construction
private:
	LPRECT m_rect_static_preview;
	LPRECT m_rect_window_preview;
	LPRECT m_rect_button_cancel;
	LPRECT m_rect_button_print;
	LPRECT m_rect_zoon_print;
public:
	CPrintVerbaliView(CWnd* pParent = NULL);   // standard constructor
	CWnd sss;
// Dialog Data
	//{{AFX_DATA(CPrintVerbaliView)
	enum { IDD = IDD_DIALOG_PRINT_VERBALI };
	CButton	m_Static_Preview;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintVerbaliView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPrintVerbaliView)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTVERBALIVIEW_H__A765C600_2F00_11D8_B754_00C026108782__INCLUDED_)
