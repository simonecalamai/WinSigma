#if !defined(AFX_EMISSIONECERTIFICATIDLG_H__24DEBD45_EC7C_46A0_933F_0A6FF5543E3C__INCLUDED_)
#define AFX_EMISSIONECERTIFICATIDLG_H__24DEBD45_EC7C_46A0_933F_0A6FF5543E3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EmissioneCertificatiDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEmissioneCertificatiDlg dialog

class CEmissioneCertificatiDlg : public CDialog
{
// Construction
public:
	long m_nCodicePrimo;
	long m_nCodiceProposto;
	CStringArray* m_paryInfoCertificato;
	CDWordArray*	m_paryScelti;
	CUIntArray*		m_parySceltiAderenza;
	CDWordArray*	m_paryProposti;
	CUIntArray*		m_paryTipiCertificato;
	CUIntArray		m_paryAderenza;
	CEmissioneCertificatiDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEmissioneCertificatiDlg)
	enum { IDD = IDD_DIALOG_EMISSIONE_CERTIFICATI };
	CButton	m_CtrlAderenza;
	CButton	m_BtnOk;
	CListCtrl	m_ListProposti;
	long	m_nNuovoNumero;
	long	m_lfNumProposto;
	CString	m_strNumScelto;
//	BOOL	m_bAderenza;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmissioneCertificatiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEmissioneCertificatiDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonModNum();
	afx_msg void OnButtonConferma();
	afx_msg void OnItemchangedListCertificati(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckAderenza();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMISSIONECERTIFICATIDLG_H__24DEBD45_EC7C_46A0_933F_0A6FF5543E3C__INCLUDED_)
