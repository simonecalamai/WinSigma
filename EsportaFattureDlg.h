#if !defined(AFX_ESPORTAFATTUREDLG_H__167FC993_25AC_484C_B843_1E7880601999__INCLUDED_)
#define AFX_ESPORTAFATTUREDLG_H__167FC993_25AC_484C_B843_1E7880601999__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EsportaFattureDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEsportaFattureDlg dialog

class CEsportaFattureDlg : public CDialog
{
// Construction
public:
	CEsportaFattureDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEsportaFattureDlg)
	enum { IDD = IDD_DIALOG_ESPORTA_FATTURE };
	CComboBox	m_cmbAnni;
	int		m_intAFattura;
	int		m_intDaFattura;
	CString	m_csAnno;
	CString	m_csPath;
	int		m_intAElett;
	int		m_intDaElett;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEsportaFattureDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CFattureSet* m_pFattureSet;

	// Generated message map functions
	//{{AFX_MSG(CEsportaFattureDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ESPORTAFATTUREDLG_H__167FC993_25AC_484C_B843_1E7880601999__INCLUDED_)
