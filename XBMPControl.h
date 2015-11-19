#if !defined(AFX_XBMPCONTROL_H__27FBA8B6_B971_4A92_83C3_DF5F6A141FB1__INCLUDED_)
#define AFX_XBMPCONTROL_H__27FBA8B6_B971_4A92_83C3_DF5F6A141FB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XBMPControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXBMPControl window

class CXBMPControl : public CStatic
{
// Construction
public:
	CXBMPControl();

// Attributes
public:
	CBMPObject* m_pBMPImage;
// Operations
public:
	 BOOL Set(CBMPObject* pBMPImage);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXBMPControl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXBMPControl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CXBMPControl)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XBMPCONTROL_H__27FBA8B6_B971_4A92_83C3_DF5F6A141FB1__INCLUDED_)
