#if !defined(AFX_DATIFATTURAPROFORMA_H__2BE70404_A196_4278_9EAB_D9462CD77950__INCLUDED_)
#define AFX_DATIFATTURAPROFORMA_H__2BE70404_A196_4278_9EAB_D9462CD77950__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DatiFatturaProforma.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDatiFatturaProforma dialog

class CDatiFatturaProforma : public CDialog
{
// Construction
public:
	CDatiFatturaProforma(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDatiFatturaProforma)
	enum { IDD = IDD_DIALOG_FATTURA_PROFORMA };
	CButton	m_BtnSpedizione;
	CEdit	m_EditSpese;
	BOOL	m_bSpedizione;
	CString	m_strAliquota;
	CString	m_strSconto;
	CString	m_strSpese;
	int		m_nNumCopie;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatiFatturaProforma)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDatiFatturaProforma)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATIFATTURAPROFORMA_H__2BE70404_A196_4278_9EAB_D9462CD77950__INCLUDED_)
