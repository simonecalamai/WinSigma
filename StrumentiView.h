#if !defined(AFX_STRUMENTIVIEW_H__D90FD120_BC35_11D7_B754_0080AD70B2EE__INCLUDED_)
#define AFX_STRUMENTIVIEW_H__D90FD120_BC35_11D7_B754_0080AD70B2EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StrumentiView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStrumentiView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CStrumentiView : public CFormView
{
protected:
	CStrumentiView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CStrumentiView)

// Form Data
public:
	//{{AFX_DATA(CStrumentiView)
	enum { IDD = IDD_FORM_STRUMENTI };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStrumentiView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CStrumentiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CStrumentiView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STRUMENTIVIEW_H__D90FD120_BC35_11D7_B754_0080AD70B2EE__INCLUDED_)
