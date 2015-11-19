#if !defined(AFX_MINUTEDLG_H__199EB9CC_167C_4159_8B66_42F42FA2F9F0__INCLUDED_)
#define AFX_MINUTEDLG_H__199EB9CC_167C_4159_8B66_42F42FA2F9F0__INCLUDED_

#include "TipiCertificatoSet.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MinuteDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMinuteDlg dialog

class CMinuteDlg : public CDialog
{
// Construction
public:
	CDWordArray m_aryTCertificato;
	CTipiCertificatoSet* m_pTCertSet;
	CMinuteDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMinuteDlg)
	enum { IDD = IDD_DIALOG_STAMPAMINUTE };
	CListCtrl	m_ListMinute;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMinuteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMinuteDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonTutte();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MINUTEDLG_H__199EB9CC_167C_4159_8B66_42F42FA2F9F0__INCLUDED_)
