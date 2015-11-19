//{{AFX_INCLUDES()
#include "msmask.h"
//}}AFX_INCLUDES
#if !defined(AFX_LISTINIVIEW_H__6C27DEC1_BBA1_11D7_B754_0080AD70B2EE__INCLUDED_)
#define AFX_LISTINIVIEW_H__6C27DEC1_BBA1_11D7_B754_0080AD70B2EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListiniView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListiniView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CListiniView : public CXFormView
{
protected:
	CListiniView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CListiniView)
	static BOOL CALLBACK ScanCategorie(CStringArray* pFieldNames, CStringArray* pFieldValues);
	static BOOL CALLBACK ScanServizi(CStringArray* pFieldNames, CStringArray* pFieldValues);

// Form Data
public:
	//{{AFX_DATA(CListiniView)
	enum { IDD = IDD_FORM_LISTINI };
	CEdit	m_EditFine;
	CEdit	m_EditInizio;
	CButton	m_CheckCertOgniSerie;
	CButton	m_ButtonCerca;
	CEdit	m_EditNome;
	CListCtrl	m_ListServizi;
	CListCtrl	m_ListCategorie;
	CString	m_strAutore;
	CString	m_strNome;
	CString	m_strCodice;
	CString	m_strCodiceAzienda;
	CString	m_strNomeAzienda;
	int		m_nCategorie;
	int		m_nServizi;
	BOOL	m_bCertificatiOgniSerie;
	CString	m_strInizio;
	CString	m_strFine;
	//}}AFX_DATA

// Attributes
public:
protected:
  int  m_nCodiceAzienda;
	BOOL m_bDenySinc;
  CListiniSet*   m_pSet;
	static CCategorieSet* m_pCategorieSet;
	static CServiziListinoSet* m_pServiziSet;
	static CWordArray m_aryPagine;

// Operations
public:
protected:
  void LoadCategorie();
	void SincronizeCategorie();
	void SincronizeServizi();
	CString GetToolTip(int nID);
  void StampaListino(BOOL bInConcessione);
  CTime GetData(CString strData);

// Overrides
  void LoadCurRecord(BOOL bData);
	BOOL IsDataChanged();
	BOOL ValidateData();
  BOOL NewRecord();
	BOOL SaveRecord();
	BOOL DeleteRecord();
	void EnableControls(BOOL bEnable);

  // ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListiniView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CListiniView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CListiniView)
	afx_msg void OnListiniCopia();
	afx_msg void OnListiniAttiva();
	afx_msg void OnCategoriaNuova();
	afx_msg void OnCategoriaModifica();
	afx_msg void OnCategoriaElimina();
	afx_msg void OnServiziNuovo();
	afx_msg void OnServiziModifica();
	afx_msg void OnServiziElimina();
	afx_msg void OnItemactivateListCategorie(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemactivateListServizi(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListCategorie(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListServizi(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListServizi(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListCategorie(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnListiniDisattiva();
	afx_msg void OnListiniStampa();
	afx_msg void OnButtonCerca();
	afx_msg void OnServiziNuovonota();
	afx_msg void OnListiniStampaInConcessione();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTINIVIEW_H__6C27DEC1_BBA1_11D7_B754_0080AD70B2EE__INCLUDED_)
