#if !defined(AFX_REPORTVERBALI_H__880F5A2C_BEAD_43A5_8F08_EA1AB9C9C304__INCLUDED_)
#define AFX_REPORTVERBALI_H__880F5A2C_BEAD_43A5_8F08_EA1AB9C9C304__INCLUDED_

#include "FattureSet.h"	// Added by ClassView
#include "VerbaliSet.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReportVerbali.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReportVerbali dialog

class CReportVerbali : public CDialog
{
// Construction
public:
	void StampaReport();
	static int m_nIndex;
	static BOOL CALLBACK ScanVerbali(CStringArray* pFieldNames, CStringArray* pFieldValues);
	static CStringArray m_aryDatiStampa;
	CVerbaliSet* m_pVerbaliSet;
	CServiziErogatiSet* m_pServiziErogatiSet;
	CFattureSet* m_pFattureSet;
	CAziendeSet* m_pAziendeSet;
	CReportVerbali(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReportVerbali)
	enum { IDD = IDD_DIALOG_REPORT_VERBALI };
	CButton	m_BtnCerca;
	CListCtrl	m_ListaVerbali;
	CButton	m_BtnStampa;
	CDateTimeCtrl	m_DataCtrAl;
	CDateTimeCtrl	m_DataCtrDal;
	CTime	m_DataAl;
	CTime	m_DataDal;
	CString	m_strRagioneSociale;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportVerbali)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void RiempiCampi(CStringArray* pFieldNames, CStringArray* pFieldValues);

	// Generated message map functions
	//{{AFX_MSG(CReportVerbali)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCerca();
	afx_msg void OnButtonStampa();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTVERBALI_H__880F5A2C_BEAD_43A5_8F08_EA1AB9C9C304__INCLUDED_)
