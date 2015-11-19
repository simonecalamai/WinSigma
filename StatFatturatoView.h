#if !defined(AFX_STATFATTURATOVIEW_H__3C97E553_64C9_4A97_AA84_C494FDA7D1DB__INCLUDED_)
#define AFX_STATFATTURATOVIEW_H__3C97E553_64C9_4A97_AA84_C494FDA7D1DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatFatturatoView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatFatturatoView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CStatFatturatoView : public CFormView
{
protected:
	CStatFatturatoView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CStatFatturatoView)

// Form Data
public:
	//{{AFX_DATA(CStatFatturatoView)
	enum { IDD = IDD_FORM_STATISTICHE_FATTURATO };
	CButton	m_btnOrdinaVerbali;
	CButton	m_btnOrdinaImponibile;
	CButton	m_btnStampaReport;
	CListCtrl	m_listFatturato;
	CComboBox	m_cmbMese;
	CComboBox	m_cmbCliente;
	CComboBox	m_cmbAnno;
	CButton	m_btnRicerca;
	CString	m_csAnno;
	CString	m_csCliente;
	CString	m_csMese;
	CString	m_csCodiceCliente;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatFatturatoView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CStatFatturatoView();
	static int m_nIndex;
	static CStringArray m_aryDatiStampa;
	static BOOL CALLBACK ScanFatture(CStringArray* pFieldNames, CStringArray* pFieldValues);
	int NumeroVerbali(int Fatture_Codice = 0);
	CWinSigmaApp* m_pApp;
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CStatFatturatoView)
	afx_msg void OnButtonRicerca();
	afx_msg void OnButtonStampaReport();
	afx_msg void OnButtonTrovaCliente();
	afx_msg void OnSelchangeComboAnno();
	afx_msg void OnSelchangeComboCliente();
	afx_msg void OnSelchangeComboMese();
	afx_msg void OnButtonOrdinaVerbali();
	afx_msg void OnButtonOrdinaImponibile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATFATTURATOVIEW_H__3C97E553_64C9_4A97_AA84_C494FDA7D1DB__INCLUDED_)
