#if !defined(AFX_FINDVERBALI_H__A097B501_2A40_11D8_9A8F_00A0CCCE3AB1__INCLUDED_)
#define AFX_FINDVERBALI_H__A097B501_2A40_11D8_9A8F_00A0CCCE3AB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindVerbaliDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindVerbali dialog

// Chiavi di ricerca dei verbali
#define SEARCH_CANTIERE     0
#define SEARCH_DIRLAVORI    1
#define SEARCH_CERTIFICATO  2
#define SEARCH_FATTURA      3
#define SEARCH_IMPRESA      4
#define SEARCH_STRUTTURA    5
#define SEARCH_SIGLA        6
#define SEARCH_NUMERO       7


class CFindVerbaliDlg : public CDialog
{
// Construction
public:
	CFindVerbaliDlg(CWnd* pParent = NULL);   // standard constructor
  ~CFindVerbaliDlg();

// Dialog Data
	//{{AFX_DATA(CFindVerbaliDlg)
	enum { IDD = IDD_DIALOG_FIND_VERBALI };
	CEdit	m_EditChiave;
	CListCtrl	m_ListVerbali;
	int		m_nChiaveRicerca;
	CString	m_strChiaveRicerca;
	//}}AFX_DATA
  CString m_strTitolo;
  int m_nCodiceVerbale;
  CWinSigmaDoc* m_pDoc;
  int m_nAnnoAccettazione;
  BOOL m_bChiusi;
  // Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindVerbaliDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  BOOL FindVerbali(void);
  void CheckAndAdd(CString strChiave, CVerbaliSet* pSet);
  void AddItem(CVerbaliSet* pSet);
  void SelectVerbale(void);
	// Generated message map functions
	//{{AFX_MSG(CFindVerbaliDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCerca();
	virtual void OnOK();
	afx_msg void OnDblclkListVerbali(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDVERBALI_H__A097B501_2A40_11D8_9A8F_00A0CCCE3AB1__INCLUDED_)
