//{{AFX_INCLUDES()
//}}AFX_INCLUDES
#if !defined(AFX_SERVIZIFATTURADLG_H__BCE8FE40_2B25_11D8_9A8F_00A0CCCE3AB1__INCLUDED_)
#define AFX_SERVIZIFATTURADLG_H__BCE8FE40_2B25_11D8_9A8F_00A0CCCE3AB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServiziFatturaDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CServiziFatturaDlg dialog
#define AGGIUNGI_SERVIZIO   0
#define MODIFICA_SERVIZIO   1
#define ELIMINA_SERVIZIO    2

class CServiziFatturaDlg : public CDialog
{
// Construction
public:
	CServiziFatturaDlg(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CServiziFatturaDlg)
	enum { IDD = IDD_DIALOG_SERVIZI_FATTURA };
	CButton	m_BtnListinoGenerale;
	CEdit	m_EditSconto;
	CEdit	m_EditQuantita;
	CEdit	m_EditNote;
	CEdit	m_EditDescrizione;
	CComboBox	m_ComboVerbali;
	CComboBox	m_ComboServizi;
	CComboBox	m_ComboCategorie;
	CString	m_strDescrizione;
	CString	m_strImporto;
	CString	m_strQuantita;
	CString	m_strNote;
	CString	m_strSconto;
	CMSMask	m_MskImporto;
	CMSMask	m_MskPrezzo;
	BOOL	m_bListinoGenerale;
	//}}AFX_DATA
  CWinSigmaDoc* m_pDoc;
  CFattureSet* m_pFattureSet;
  CVerbaliSet* m_pVerbaliInFatturazione;
  CServiziErogatiSet* m_pServiziErogati;
  CListiniSet* m_pListinoSet;
  CCategorieServiziSet* m_pCategorieServiziSet;
  int m_nOperazione;
  long m_lCodiceAzienda;
  long m_lCodiceServizioErogato;
  long m_lCodiceVerbale;
  long m_lCodiceFattura;
  long m_lListinoGenerale;
  long m_lListinoParticolare;
  CString m_strEmettiSalvaBtn;
  double m_dImporto;
  double m_dSconto;
  BOOL   m_bChangeSconto;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServiziFatturaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  void InitListino(void);
  void InitVerbali(void);
  void InitCategorie(void);
  void InitServizi(void);
	// Generated message map functions
	//{{AFX_MSG(CServiziFatturaDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSelchangeComboVerbale();
	afx_msg void OnSelchangeComboCategoria();
	afx_msg void OnSelchangeComboServizio();
	afx_msg void OnChangeMaskedboxImporto();
	afx_msg void OnChangeMaskedboxPrezzo();
	afx_msg void OnChangeEditSconto();
	afx_msg void OnChangeEditQuantita();
	afx_msg void OnChangeEditDescrizione();
	afx_msg void OnCheckListinogenerale();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVIZIFATTURADLG_H__BCE8FE40_2B25_11D8_9A8F_00A0CCCE3AB1__INCLUDED_)
