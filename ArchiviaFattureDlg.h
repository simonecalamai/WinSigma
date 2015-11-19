#if !defined(AFX_ARCHIVIAFATTUREDLG_H__1BB9DEB1_75C8_4236_AB6A_C58202F473E7__INCLUDED_)
#define AFX_ARCHIVIAFATTUREDLG_H__1BB9DEB1_75C8_4236_AB6A_C58202F473E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ArchiviaFattureDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArchiviaFattureDlg dialog

class CArchiviaFattureDlg : public CDialog
{
// Construction
public:
	CArchiviaFattureDlg(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CArchiviaFattureDlg)
	enum { IDD = IDD_DIALOG_ARCHIVIA_FATTURE };
	int		m_iA;
	int		m_iDa;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArchiviaFattureDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CArchiviaFattureDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARCHIVIAFATTUREDLG_H__1BB9DEB1_75C8_4236_AB6A_C58202F473E7__INCLUDED_)
