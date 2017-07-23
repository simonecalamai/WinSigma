#if !defined(AFX_OPERATORIVIEW_H__83E83215_740C_4A4D_B0A9_EDCBBAEB44CF__INCLUDED_)
#define AFX_OPERATORIVIEW_H__83E83215_740C_4A4D_B0A9_EDCBBAEB44CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OperatoriView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COperatoriView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class COperatoriView : public CXFormView
{
protected:
	COperatoriView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(COperatoriView)

// Form Data
public:
	//{{AFX_DATA(COperatoriView)
	enum { IDD = IDD_FORM_OPERATORI };
	CButton	m_ctrlChkInvalidatePicker;
	CEdit	m_EdtTitoli;
	CEdit	m_EdtSigla;
	CButton	m_BtnResponsabile;
	CEdit	m_EdtMacchina;
	CButton	m_BtnSperimentatore;
	CEdit	m_EditVerifica;
	CEdit	m_EditPassword;
	CEdit	m_EditNome;
	CEdit	m_EditCognome;
	CDateTimeCtrl	m_DatePickerInizio;
	CDateTimeCtrl	m_DatePickerFine;
	CButton	m_CheckSospeso;
	CComboBox	m_ComboLivello;
	BOOL	m_bSospeso;
	CTime	m_TimeInizio;
	CTime	m_TimeFine;
	CString	m_strCognome;
	CString	m_strNome;
	CString	m_strPassword;
	CString	m_strVerifica;
	CString	m_strCodice;
	CString	m_strMacchina;
	BOOL	m_bSperimentatore;
	BOOL	m_bResponsabile;
	CString	m_strTitoli;
	CString m_strSigla;
	//}}AFX_DATA

// Attributes
public:
protected:
  COperatoriSet* m_pSet;
  int m_iEndActChecked;

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
	//{{AFX_VIRTUAL(COperatoriView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void RimuoviResponsabile();
	virtual ~COperatoriView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(COperatoriView)
	afx_msg void OnCheckSperimentatore();
	afx_msg void OnCheckResponsabile();
	afx_msg void OnButtonAggiorna();
	afx_msg void OnCheckInvalidpicker();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPERATORIVIEW_H__83E83215_740C_4A4D_B0A9_EDCBBAEB44CF__INCLUDED_)
