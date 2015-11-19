#if !defined(AFX_STAMPAETICHETTE_H__01124220_4688_11D8_B754_0080AD70B2EE__INCLUDED_)
#define AFX_STAMPAETICHETTE_H__01124220_4688_11D8_B754_0080AD70B2EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StampaEtichette.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStampaEtichette dialog

class CStampaEtichette : public CDialog
{
// Construction
public:
	CStampaEtichette(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStampaEtichette)
	enum { IDD = IDD_DIALOG_ETICHETTE };
	CListCtrl	m_lstEtichette;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStampaEtichette)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStampaEtichette)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAMPAETICHETTE_H__01124220_4688_11D8_B754_0080AD70B2EE__INCLUDED_)
