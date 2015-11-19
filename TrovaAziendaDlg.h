#if !defined(AFX_TROVAAZIENDA_H__79B2B340_E38C_11D7_9A8F_00A0CCCE3AB1__INCLUDED_)
#define AFX_TROVAAZIENDA_H__79B2B340_E38C_11D7_9A8F_00A0CCCE3AB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CTrovaAziendaDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTrovaAziendaDlg dialog

class CTrovaAziendaDlg : public CDialog
{
// Construction
public:
	CTrovaAziendaDlg(CWnd* pParent = NULL);   // standard constructor
	~CTrovaAziendaDlg();
  BOOL Find();
  
// Dialog Data
	//{{AFX_DATA(CTrovaAziendaDlg)
	enum { IDD = IDD_DIALOG_TROVA_AZIENDA };
	CListCtrl	m_ListRisultati;
	CString	m_strPartitaIva;
	CString	m_strNome;
	CString	m_strID;
	int		m_nAziende;
	//}}AFX_DATA
  CAziendeSet* m_pSet;
	long    m_lCodice;
	long    m_lListino;
	long    m_lPagamento;
	CString m_strIndirizzo;

	CString m_strTipoRicerca;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrovaAziendaDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
  
// Implementation
protected:
  CString Filter();
	void    LoadList();

	// Generated message map functions
	//{{AFX_MSG(CTrovaAziendaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCerca();
	virtual void OnOK();
	afx_msg void OnDblclkListRisultati(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditNome();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TROVAAZIENDA_H__79B2B340_E38C_11D7_9A8F_00A0CCCE3AB1__INCLUDED_)
