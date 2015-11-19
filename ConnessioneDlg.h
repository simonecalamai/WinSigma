#if !defined(AFX_CONNESSIONEDLG_H__20C6D8A0_BC5A_11D7_B754_0080AD70B2EE__INCLUDED_)
#define AFX_CONNESSIONEDLG_H__20C6D8A0_BC5A_11D7_B754_0080AD70B2EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConnessioneDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConnessioneDlg dialog

class CConnessioneDlg : public CDialog
{
// Construction
public:
	CConnessioneDlg(CWnd* pParent = NULL);   // standard constructor
  bool m_bOkPressed;
  bool m_bCancelPressed;
// Dialog Data
	//{{AFX_DATA(CConnessioneDlg)
	enum { IDD = IDD_DIALOG_CONNESSIONE };
	CStatic	m_ctrlIcon;
	CProgressCtrl	m_ctrlProgressLoad;
	CEdit	m_ctrlPassWord;
	CButton	m_btnOk;
	CButton	m_btnCancel;
	CComboBox	m_ComboOperatore;
	CString	m_csPassword;
	//}}AFX_DATA
	COperatoriSet* m_pSet;
	long m_nOperatore;
	long m_nPrivilegi;
	CString m_strOperatore;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnessioneDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CConnessioneDlg)
  virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCloseupComboOperatore();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNESSIONEDLG_H__20C6D8A0_BC5A_11D7_B754_0080AD70B2EE__INCLUDED_)
