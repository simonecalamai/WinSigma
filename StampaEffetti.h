#if !defined(AFX_STAMPAEFFETTI_H__0B739520_3F99_11D8_B754_0080AD70B2EE__INCLUDED_)
#define AFX_STAMPAEFFETTI_H__0B739520_3F99_11D8_B754_0080AD70B2EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StampaEffetti.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStampaEffetti dialog

class CStampaEffetti : public CDialog
{
// Construction
public:
	CStampaEffetti(CWnd* pParent = NULL);   // standard constructor
	static BOOL CALLBACK ScanPerEffetto(CStringArray* pFieldNames, CStringArray* pFieldValues);
	static int m_ItemCount;
// Dialog Data
	//{{AFX_DATA(CStampaEffetti)
	enum { IDD = IDD_DIALOG_EFFETTI };
	static CListCtrl	m_lstEffetti;
	CString	m_strDa_Fattura;
	CString	m_strA_Fattura;
  CComboBox	m_cmbAnno;
	//}}AFX_DATA
  static CStringArray m_aryIndirizzi;
  static int m_nTotaleEffetti;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStampaEffetti)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStampaEffetti)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonRicerca();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Query();
	CFattureSet* fatture;
	CTipiPagamentoSet* tipi_pagamento;
	CServiziErogatiSet* servizi_erogati;
	bool Congruenza_Dati_Ricerca(CString* msg);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAMPAEFFETTI_H__0B739520_3F99_11D8_B754_0080AD70B2EE__INCLUDED_)
