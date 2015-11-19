#if !defined(AFX_STAMPACERTIFICATIDLG_H__A803711A_C218_4287_A6B2_4B0BC8ECA6EC__INCLUDED_)
#define AFX_STAMPACERTIFICATIDLG_H__A803711A_C218_4287_A6B2_4B0BC8ECA6EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StampaCertificatiDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStampaCertificatiDlg dialog

class CStampaCertificatiDlg : public CDialog
{
// Construction
public:
	BOOL m_bRistampa;
	CCertificatiVerbaliSet* m_pCertVerbSet;
	CDWordArray* m_pCertificatiScelti;
	CTipiCertificatoSet* m_pTipiCertificatoSet;
	
	CStampaCertificatiDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStampaCertificatiDlg)
	enum { IDD = IDD_DIALOG_STAMPA_CERTIFICATI };
	CDateTimeCtrl	m_CtrDataDuplicato;
	CButton	m_BtnDuplicato;
	CListCtrl	m_ListCertificati;
	BOOL	m_bDuplicato;
	CTime	m_DataDuplicato;
	//BOOL	m_bAderenza;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStampaCertificatiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImageList m_imgStampaCert;
	void RiempiElenco();
	byte m_bSelezione;

	// Generated message map functions
	//{{AFX_MSG(CStampaCertificatiDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonSelezione();
	afx_msg void OnCheckDuplicato();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAMPACERTIFICATIDLG_H__A803711A_C218_4287_A6B2_4B0BC8ECA6EC__INCLUDED_)
