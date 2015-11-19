#if !defined(AFX_DBREMOTODLG_H__C0A42638_532C_4BED_85C7_B7DCF1E1AF3F__INCLUDED_)
#define AFX_DBREMOTODLG_H__C0A42638_532C_4BED_85C7_B7DCF1E1AF3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBRemotoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBRemotoDlg dialog

#include "DatiAziende.h"

class CDBRemotoDlg : public CDialog
{
// Construction
public:
	void AddToListAziende();
	CDBRemotoDlg(CDatiAziende* dati_aziende, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDBRemotoDlg)
	enum { IDD = IDD_DIALOG_DB_REMOTO };
	CListCtrl	m_lstAziendeRemote;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBRemotoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CAziendeSet* m_pAziendeRemoteSet;

private:
	CDatiAziende* m_pDatiAziende;
	void PopolaLista();
	// Generated message map functions
	//{{AFX_MSG(CDBRemotoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnButtonIdMissing();
	afx_msg void OnButtonIdPresent();
	afx_msg void OnButtonTutti();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBREMOTODLG_H__C0A42638_532C_4BED_85C7_B7DCF1E1AF3F__INCLUDED_)
