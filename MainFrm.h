// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__73C5E068_BB73_11D7_B754_0080AD70B2EE__INCLUDED_)
#define AFX_MAINFRM_H__73C5E068_BB73_11D7_B754_0080AD70B2EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GfxSplitterWnd.h"
#include "GfxOutBarCtrl.h"
#include "XTreeCtrl.h"
#include "AziendeTreeCtrl.h"	// Added by ClassView
#include "FattureTreeCtrl.h"	// Added by ClassView
#include "VerbaliTreeCtrl.h"	// Added by ClassView
#include "ListiniTreeCtrl.h"	// Added by ClassView
#include "StrumentiTreeCtrl.h"	// Added by ClassView

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
		CGfxSplitterWnd	m_wndSplitter;
		CGfxOutBarCtrl	m_wndBar;
		
		CImageList	m_imgAziende,  m_imgVerbali, m_imgFatture, m_imgListini;
		CImageList  m_imgArchivio, m_imgStrumenti;
		bool bFirst;

// Operations
public:
	void EditMode(int nID);
	void StatusBarMessage(CString strMessage);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	void RepopulateTrees();
	void ReloadTree(CString strLabel, long nCodice);
	CStrumentiTreeCtrl m_wndTreeStrumenti;
	CListiniTreeCtrl   m_wndTreeListini;
	CVerbaliTreeCtrl   m_wndTreeVerbali;
	CFattureTreeCtrl   m_wndTreeFatture;
	CAziendeTreeCtrl   m_wndTreeAziende;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	void SwitchToForm(int nForm);
  int m_iForm;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG

	afx_msg long OnOutbarNotify(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__73C5E068_BB73_11D7_B754_0080AD70B2EE__INCLUDED_)
