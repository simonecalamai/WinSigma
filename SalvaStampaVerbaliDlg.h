#if !defined(AFX_SALVASTAMPAVERBALIDLG_H__FA1F09A0_1A7A_11D8_9A8F_00A0CCCE3AB1__INCLUDED_)
#define AFX_SALVASTAMPAVERBALIDLG_H__FA1F09A0_1A7A_11D8_9A8F_00A0CCCE3AB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CSalvaStampaVerbaliDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSalvaStampaVerbaliDlg dialog

class CSalvaStampaVerbaliDlg : public CDialog
{
// Construction
public:
	CSalvaStampaVerbaliDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSalvaStampaVerbaliDlg)
	enum { IDD = IDD_DIALOG_SAVEPRN_VERBALI };
	CButton	m_BtnPrnVerbale;
	BOOL	m_bPrintMinuta;
	BOOL	m_bPrintVerbaleCartaLibera;
	BOOL	m_bPrintVerbale;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSalvaStampaVerbaliDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSalvaStampaVerbaliDlg)
	afx_msg void OnCheckPrnMinuta();
	afx_msg void OnCheckPrnVcartalibera();
	afx_msg void OnCheckPrnVerbale();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnButtonNo();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SALVASTAMPAVERBALIDLG_H__FA1F09A0_1A7A_11D8_9A8F_00A0CCCE3AB1__INCLUDED_)
