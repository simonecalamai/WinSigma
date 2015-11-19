#if !defined(AFX_TIPIMATERIALEVIEW_H__6CEC246F_C702_4307_977B_1AAFFA533AF3__INCLUDED_)
#define AFX_TIPIMATERIALEVIEW_H__6CEC246F_C702_4307_977B_1AAFFA533AF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TipiMaterialeView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTipiMaterialeView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CTipiMaterialeView : public CXFormView
{
protected:
	CTipiMaterialeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTipiMaterialeView)

// Form Data
public:
	//{{AFX_DATA(CTipiMaterialeView)
	enum { IDD = IDD_FORM_MATERIALI };
	CComboBox	m_ComboCertificato4;
	CComboBox	m_ComboCertificato3;
	CComboBox	m_ComboCertificato2;
	CButton	m_BtnQuadro;
	CEdit	m_EdtSnervamento;
	CEdit	m_EdtCodice;
	CButton	m_BtnPredefinito;
	CComboBox	m_ComboCertificato;
	CEdit	m_EditNome;
	CEdit	m_EditDescrizione;
	CString	m_strCodice;
	CString	m_strDescrizione;
	CString	m_strNome;
	BOOL	m_bPredefinito;
	double	m_lfSnervamento;
	//}}AFX_DATA

// Attributes
public:
protected:
  CTipiMaterialeSet* m_pSet;
  CTipiCertificatoSet* m_pTCertificatiSet;

// Operations
public:
	CTipiMaterialeSet* m_pMatPredSet;

// Overrides
  void LoadCurRecord(BOOL bData);
	BOOL IsDataChanged();
	BOOL ValidateData();
  BOOL NewRecord();
	BOOL SaveRecord();
	BOOL DeleteRecord();
	void EnableControls(BOOL bEnable);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTipiMaterialeView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTipiMaterialeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CTipiMaterialeView)
	afx_msg void OnButtonSfoglia();
	afx_msg void OnButtonQuadri();
	afx_msg void OnButtonAggiorna();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIPIMATERIALEVIEW_H__6CEC246F_C702_4307_977B_1AAFFA533AF3__INCLUDED_)
