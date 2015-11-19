#if !defined(AFX_MARCHIVIEW_H__3FFEADDC_07AF_4115_8F38_F0D7738EC37C__INCLUDED_)
#define AFX_MARCHIVIEW_H__3FFEADDC_07AF_4115_8F38_F0D7738EC37C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MarchiView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMarchiView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CMarchiView : public CXFormView
{
protected:
	CMarchiView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMarchiView)

// Form Data
public:
	//{{AFX_DATA(CMarchiView)
	enum { IDD = IDD_FORM_MARCHI };
	CButton	m_ButtonSfoglia;
	CEdit	m_EditStabilimento;
	CEdit	m_EditProduttore;
	CEdit	m_EditNome;
	CEdit	m_EditDescrizione;
	CXBMPControl	m_StaticMarchio;
	CString	m_strCodice;
	CString	m_strDescrizione;
	CString	m_strNome;
	CString	m_strProduttore;
	CString	m_strStabilimento;
	//}}AFX_DATA
  CString m_strFileName;
// Attributes
public:
protected:
  CMarchiSet* m_pSet;
  CBMPObject  m_BmpObject;

// Operations
public:
  void LoadCurRecord(BOOL bData);
	BOOL IsDataChanged();
	BOOL ValidateData();
  BOOL NewRecord();
	BOOL SaveRecord();
	BOOL DeleteRecord();
	void EnableControls(BOOL bEnable);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarchiView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMarchiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMarchiView)
	afx_msg void OnButtonSfoglia();
	afx_msg void OnStampa();
	afx_msg void OnButtonAggiorna();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARCHIVIEW_H__3FFEADDC_07AF_4115_8F38_F0D7738EC37C__INCLUDED_)
