// ClientiTransfer.h : main header file for the CLIENTITRANSFER application
//

#if !defined(AFX_CLIENTITRANSFER_H__86068F06_2FC1_11D8_B754_00C026108782__INCLUDED_)
#define AFX_CLIENTITRANSFER_H__86068F06_2FC1_11D8_B754_00C026108782__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CClientiTransferApp:
// See ClientiTransfer.cpp for the implementation of this class
//

class CClientiTransferApp : public CWinApp
{
public:
	CClientiTransferApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientiTransferApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CClientiTransferApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTITRANSFER_H__86068F06_2FC1_11D8_B754_00C026108782__INCLUDED_)
