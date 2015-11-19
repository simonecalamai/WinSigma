#if !defined(AFX_CATEGORIEDLG_H__87207AE6_9A34_46C3_8885_C0443EB4ACCF__INCLUDED_)
#define AFX_CATEGORIEDLG_H__87207AE6_9A34_46C3_8885_C0443EB4ACCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CategorieDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCategorieDlg dialog

class CCategorieDlg : public CDialog
{
// Construction
public:
	CCategorieDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCategorieDlg)
	enum { IDD = IDD_DIALOG_CATEGORIE };
	CEdit	m_EditCodice;
	CString	m_strCodice;
	CString	m_strDescrizione;
	CString	m_strNome;
	CString	m_strCodiceListino;
	CString	m_strNomeListino;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCategorieDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCategorieDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CATEGORIEDLG_H__87207AE6_9A34_46C3_8885_C0443EB4ACCF__INCLUDED_)
