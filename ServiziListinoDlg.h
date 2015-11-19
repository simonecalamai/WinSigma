//{{AFX_INCLUDES()
//}}AFX_INCLUDES
#if !defined(AFX_SERVIZILISTINODLG_H__328E8E8E_7479_4135_AE79_1E6CADFABF4C__INCLUDED_)
#define AFX_SERVIZILISTINODLG_H__328E8E8E_7479_4135_AE79_1E6CADFABF4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServiziListinoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CServiziListinoDlg dialog

class CServiziListinoDlg : public CDialog
{
// Construction
public:
	int m_nPerSerie;
	CServiziListinoDlg(CWnd* pParent = NULL);   // standard constructor
	~CServiziListinoDlg();

// Dialog Data
	//{{AFX_DATA(CServiziListinoDlg)
	enum { IDD = IDD_DIALOG_SERVIZILISTINO };
	CButton	m_CheckProvaA4;
	CButton	m_CheckProvaB4;
	CComboBox	m_ComboCertificato4;
	CComboBox	m_ComboCertificato3;
	CButton	m_CheckProvaB3;
	CButton	m_CheckProvaA3;
	CButton	m_CheckProvaA2;
	CButton	m_CheckProvaB2;
	CComboBox	m_ComboCertificato2;
	CEdit	m_EdtCommento;
	CButton	m_BtnGeologia;
	CButton	m_EdtConcessione;
	CButton	m_BtnPerProvino;
	CButton	m_BtnPerSerie;
	CComboBox	m_ComboAggiuntivo;
	CComboBox	m_ComboEmissione;
	CComboBox	m_ComboID;
	CEdit	m_EditNProvini;
	CComboBox	m_ComboCertificato;
	CButton	m_CheckProvaB;
	CButton	m_CheckProvaA;
	CString	m_strCategoria;
	CString	m_strDescrizione;
	CString	m_strNProvini;
	BOOL	m_bProvaA;
	BOOL	m_bProvaB;
	CMSMask	m_MskEditPrezzo;
	CString	m_strNome;
	CString	m_strNorma;
	CString	m_strRiferimenti;
	CString	m_strID;
	BOOL	m_bPerSerie;
	BOOL	m_bPerProvino;
	BOOL	m_bConcessione;
	CString	m_strProviniPerSerie;
	BOOL	m_bGeologia;
	CString	m_strCommentoMateriale;
	BOOL	m_bProvaA2;
	BOOL	m_bProvaB2;
	BOOL	m_bProvaA3;
	BOOL	m_bProvaB3;
	BOOL	m_bProvaA4;
	BOOL	m_bProvaB4;
	//}}AFX_DATA
	CTipiCertificatoSet* m_pTCertificatiSet;
	CStringArray m_aryStrId;
	BYTE     m_byProve;
  BYTE     m_byProve2;
	BYTE     m_byProve3;
	BYTE     m_byProve4;
	int      m_nEmissione;
	int      m_nAggiuntivo;
	int      m_nCertificato;
  int      m_nCertificato2;
	int      m_nCertificato3;
	int      m_nCertificato4;
	int      m_nProvini;
  int      m_nProviniPerSerie;
	double   m_fPrezzo;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServiziListinoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL ValidateData();

	// Generated message map functions
	//{{AFX_MSG(CServiziListinoDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeComboCertificato();
	afx_msg void OnSelchangeComboEmissione();
	afx_msg void OnCheckPerserie();
	afx_msg void OnCheckPerprovino();
	afx_msg void OnCheckConcessione();
	afx_msg void OnCheckGeologia();
	afx_msg void OnSelchangeComboCertificato2();
	afx_msg void OnSelchangeComboCertificato3();
	afx_msg void OnSelchangeComboCertificato4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVIZILISTINODLG_H__328E8E8E_7479_4135_AE79_1E6CADFABF4C__INCLUDED_)
