#if !defined(AFX_ETICHETTEDLG_H__C082101D_3F96_4C44_ADC9_E9AEAC9B1EEA__INCLUDED_)
#define AFX_ETICHETTEDLG_H__C082101D_3F96_4C44_ADC9_E9AEAC9B1EEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EtichetteDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEtichetteDlg dialog

class CEtichetteDlg : public CDialog
{
// Construction
public:
	CString m_strQueryRange;
	int m_nInizioStampa;
	CStringArray* m_paryIndirizziReport;
	CStringArray* m_paryIndirizzi;
	
	CEtichetteDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEtichetteDlg)
	enum { IDD = IDD_DIALOG_ETICHETTE };
	CComboBox	m_cmbAnno;
	CButton	m_BtnOK;
	CComboBox	m_ComboPartenza;
	BOOL	m_bStEtichette;
	BOOL	m_bStReport;
	CString	m_strScelti;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEtichetteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL CreaQuery();
	CString CreaIndirizzo(CAziendeSet* pSet);

	// Generated message map functions
	//{{AFX_MSG(CEtichetteDlg)
	virtual void OnOK();
	afx_msg void OnCheckEtichette();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckReport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ETICHETTEDLG_H__C082101D_3F96_4C44_ADC9_E9AEAC9B1EEA__INCLUDED_)
