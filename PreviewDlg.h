#if !defined(AFX_PREVIEWDLG_H__E13AF8C8_0B61_486F_A8A2_242FEE2CA911__INCLUDED_)
#define AFX_PREVIEWDLG_H__E13AF8C8_0B61_486F_A8A2_242FEE2CA911__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PreviewDlg.h : header file
//

class CPrintPreviewDoc : public CObject
{
public:
	CPrintPreviewDoc() {};
	virtual ~CPrintPreviewDoc() {};
	virtual void Print(long lCodice, CDC* pDC, CRect* pRect)  = 0;
  virtual int PrintPage(long lCodice, CDC* pDc, CRect* pRect, int nPage, double dScala, int nOrigine) = 0;
//	virtual void PrintText(long lCodice, CString strLpt = "");
};


/////////////////////////////////////////////////////////////////////////////
// CPreviewDlg dialog

class CPreviewDlg : public CDialog
{
// Construction
public:
	CPreviewDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPreviewDlg)
	enum { IDD = IDD_DIALOG_PREVIEW };
	CScrollBar	m_ScrollBar;
	CStatic	m_StaticPreview;
	BOOL	m_bZoom;
	//}}AFX_DATA

  long m_nCodice;
  int m_nPage;
  int m_nTotalePagine;
  int m_nPosZoom;
  int m_nScrollDir;
	CPrintPreviewDoc* m_pPrintPreviewDoc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreviewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPreviewDlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckZoom();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnStampa();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PREVIEWDLG_H__E13AF8C8_0B61_486F_A8A2_242FEE2CA911__INCLUDED_)
