#if !defined(AFX_INSERTVERBALIINFATTURADLG_H__EA09EFB1_3F84_402A_B5F4_2A3BDE27B24A__INCLUDED_)
#define AFX_INSERTVERBALIINFATTURADLG_H__EA09EFB1_3F84_402A_B5F4_2A3BDE27B24A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsertVerbaliInFatturaDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInsertVerbaliInFatturaDlg dialog

class CInsertVerbaliInFatturaDlg : public CDialog
{
// Construction
public:
	CInsertVerbaliInFatturaDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInsertVerbaliInFatturaDlg)
	enum { IDD = IDD_DIALOG_INSERT_VERBALE };
	CListCtrl	m_ListVerbali;
	//}}AFX_DATA
  CVerbaliSet* m_pVerbaliSet;
  long m_lCodiceAzienda;
  long m_lCodiceFattura;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsertVerbaliInFatturaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  void InsertVerbale(void);
	// Generated message map functions
	//{{AFX_MSG(CInsertVerbaliInFatturaDlg)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListVerbalidafatturare(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSERTVERBALIINFATTURADLG_H__EA09EFB1_3F84_402A_B5F4_2A3BDE27B24A__INCLUDED_)
