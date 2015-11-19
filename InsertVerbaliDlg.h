#if !defined(AFX_INSERTVERBALIDLG_H__56314720_33EF_11D8_9A8F_00A0CCCE3AB1__INCLUDED_)
#define AFX_INSERTVERBALIDLG_H__56314720_33EF_11D8_9A8F_00A0CCCE3AB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsertVerbaliDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInsertVerbaliDlg dialog

class CInsertVerbaliDlg : public CDialog
{
// Construction
public:
	CInsertVerbaliDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInsertVerbaliDlg)
	enum { IDD = IDD_DIALOG_INSERT_VERBALI };
	CDateTimeCtrl	m_DTCtrlDataAccettazione;
	CEdit	m_EditParziale;
	CString	m_strProgressivoParziale;
	CString	m_strProgressivoTotale;
	CString	m_strCantiere;
	CTime	m_DataAccettazione;
	BOOL	m_bLungaScadenza;
	//}}AFX_DATA

// Data
public:
  long m_lProgressivoParziale;
  long m_lProgressivoTotale;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsertVerbaliDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInsertVerbaliDlg)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckLungaScadenza();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSERTVERBALIDLG_H__56314720_33EF_11D8_9A8F_00A0CCCE3AB1__INCLUDED_)
