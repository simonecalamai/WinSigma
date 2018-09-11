#if !defined(AFX_ESPORTAXMLDLG_H__F105CACF_20AD_4584_93B7_592FEEF7C9A5__INCLUDED_)
#define AFX_ESPORTAXMLDLG_H__F105CACF_20AD_4584_93B7_592FEEF7C9A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EsportaXMLDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEsportaXMLDlg dialog

class CEsportaXMLDlg : public CDialog
{
// Construction
public:
	CEsportaXMLDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEsportaXMLDlg)
	enum { IDD = IDD_DIALOG_ESPORTA_XML };
	int		m_intAnno;
	int		m_intAFattura;
	int		m_intDaFattura;
	int		m_intProgressivo;
	CString	m_csAnno;
	CString	m_csPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEsportaXMLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CFattureSet* m_pFattureSet;

	// Generated message map functions
	//{{AFX_MSG(CEsportaXMLDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ESPORTAXMLDLG_H__F105CACF_20AD_4584_93B7_592FEEF7C9A5__INCLUDED_)
