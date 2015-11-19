#if !defined(AFX_STATPROVEVIEW_H__AD1BDC43_2C9F_4F41_A0B3_5475D51416B5__INCLUDED_)
#define AFX_STATPROVEVIEW_H__AD1BDC43_2C9F_4F41_A0B3_5475D51416B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatProveView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatProveView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "ServiziListinoSet.h"
#include "WinSigmaDoc.h"

class CStatProveView : public CFormView
{
protected:
	CStatProveView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CStatProveView)

// Form Data
public:
	//{{AFX_DATA(CStatProveView)
	enum { IDD = IDD_FORM_STATISTICHE_PROVE };
	CButton	m_btnPrintReport;
	CListCtrl	m_ListRisultato;
	CButton	m_btnRicerca;
	CComboBox	m_cmbAnni;
	CListCtrl	m_ListServizi;
	CComboBox	m_ComboTipoCertificato;
	CString	m_csAnno;
	//}}AFX_DATA

// Attributes
public:
	CWinSigmaDoc*						m_pDoc;
	CWinSigmaApp*						m_pApp;
	CTipiCertificatoSet*		m_pTCertificatoSet;
	CCategorieServiziSet*		m_pCatServSet;
	CVerbaliServErogatiSet* m_pVerbaliServErogati;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatProveView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CStatProveView();
	static int m_nIndex;
	static CStringArray m_aryDatiStampa;
	static BOOL CALLBACK ScanProve(CStringArray* pFieldNames, CStringArray* pFieldValues);
	void LoadServizi(void);
	CString FormatDescrizione(void);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CStatProveView)
	afx_msg void OnSelchangeComboTipiCertificato();
	afx_msg void OnSelchangeComboAnni();
	afx_msg void OnStatisticheproveRicerca();
	afx_msg void OnStatisticheproveStampareport();
	afx_msg void OnButtonRicerca();
	afx_msg void OnButtonReport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATPROVEVIEW_H__AD1BDC43_2C9F_4F41_A0B3_5475D51416B5__INCLUDED_)
