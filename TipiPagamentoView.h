#if !defined(AFX_TIPIPAGAMENTOVIEW_H__1A0142E8_9061_4212_AAF5_5D9DF4724231__INCLUDED_)
#define AFX_TIPIPAGAMENTOVIEW_H__1A0142E8_9061_4212_AAF5_5D9DF4724231__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TipiPagamentoView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTipiPagamentoView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CTipiPagamentoView : public CXFormView
{
protected:
	CTipiPagamentoView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTipiPagamentoView)

// Form Data
public:
	//{{AFX_DATA(CTipiPagamentoView)
	enum { IDD = IDD_FORM_PAGAMENTI };
	CEdit	m_EditCodiceGest;
	CEdit	m_EditCIN;
	CEdit	m_EditCC;
	CEdit	m_EditCAB;
	CEdit	m_EditBanca;
	CEdit	m_EditABI;
	CComboBox	m_ComboAllineamento;
	CEdit	m_Prima_Scadenza;
	CEdit	m_Numero_Rate;
	CEdit	m_EditNome;
	CEdit	m_EditDescrizione;
	CEdit	m_EditCodice;
	CString	m_strDescrizione;
	CString	m_strNome;
	CString	m_strCodice;
	int	m_nNumero_Rate;
	int	m_nPrima_Scadenza;
	CString	m_strABI;
	CString	m_strBanca;
	CString	m_strCAB;
	CString	m_strContoCorrente;
	CString	m_strCIN;
	int		m_iCodiceGest;
	BOOL	m_bBonifico;
	BOOL	m_bRIBA;
	CEdit	m_EditCodiceXML;
	CString	m_strCodiceXML;
	//}}AFX_DATA

// Attributes
public:
protected:
  CTipiPagamentoSet* m_pSet;

// Operations
public:

// Overrides
  void LoadCurRecord(BOOL bData);
	BOOL IsDataChanged();
	BOOL ValidateData();
  BOOL NewRecord();
	BOOL SaveRecord();
	BOOL DeleteRecord();
	void EnableControls(BOOL bEnable);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTipiPagamentoView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTipiPagamentoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CTipiPagamentoView)
	afx_msg void OnButtonAggiorna();
	afx_msg void OnCheckRiba();
	afx_msg void OnCheckBonifico();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIPIPAGAMENTOVIEW_H__1A0142E8_9061_4212_AAF5_5D9DF4724231__INCLUDED_)
