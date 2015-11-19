#if !defined(AFX_MODIFICACERTIFICATODLG_H__75628430_09B6_46B4_9899_C1B8E31F2E4D__INCLUDED_)
#define AFX_MODIFICACERTIFICATODLG_H__75628430_09B6_46B4_9899_C1B8E31F2E4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModificaCertificatoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModificaCertificatoDlg dialog

class CModificaCertificatoDlg : public CDialog
{
// Construction
public:
	long m_nCodCertificato;
	CCertificatiVerbaliSet* m_pCertVerbSet;
	CModificaCertificatoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModificaCertificatoDlg)
	enum { IDD = IDD_DIALOG_MODIFICA_CERTIFICATO };
	CButton	m_BtnCalcolo;
	CButton	m_BtnInserimento;
	CEdit	m_EdtNumero;
	CDateTimeCtrl	m_DataCtrl;
	CButton	m_BtnEmenda;
	CEdit	m_EdtPagine;
	CTime	m_DataEmissione;
	int		m_nNumDocumento;
	int		m_nNumPagine;
	CString	m_strVerbale;
	BOOL	m_bAbilitaCalcolo;
	BOOL	m_bInserimento;
	BOOL	m_bEmenda;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModificaCertificatoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL ValidateDate();

	// Generated message map functions
	//{{AFX_MSG(CModificaCertificatoDlg)
	virtual void OnOK();
	afx_msg void OnCheckCalcoloPagine();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckNoCalcolo();
	afx_msg void OnCheckEmendamento();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFICACERTIFICATODLG_H__75628430_09B6_46B4_9899_C1B8E31F2E4D__INCLUDED_)
