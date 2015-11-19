#if !defined(AFX_MAINDLG_H__2503246C_AF03_4386_B387_68CEFF1D9580__INCLUDED_)
#define AFX_MAINDLG_H__2503246C_AF03_4386_B387_68CEFF1D9580__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainDlg.h : header file
//

#include "..\XDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog

class CMainDlg : public CXDialog
{
// Construction
public:
	CTime* m_pUltimaDataProve;
	long* m_pUltimoSper;
	CTime m_DataAccettazione;
	CProviniSet* m_pProviniSet;
	CSerieSet* m_pSerieSet;
	COperatoriSet* m_pOperatoriSet;
	CMainDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMainDlg)
	enum { IDD = IDD_DIALOG_MAIN };
	CComboBox	m_ComboSperimentatori;
	CComboBox	m_ComboMacchine;
	CDateTimeCtrl	m_ctrDataProve;
	CEdit	m_EdtTemperatura;
	CEdit	m_EdtKV;
	CEdit	m_EdtSezione;
	CEdit	m_EdtOsservazioni;
	CEdit	m_EdtPosizione;
	CEdit	m_EdtSigla;
	CButton	m_BtnOk;
	CButton	m_BtnCancel;
	CTreeCtrl	m_TreeProvini;
	CComboBox	m_ComboProvette;
	CButton	m_BtnConferma;
	CButton	m_BtnAnnulla;
	CButton	m_BtnModifica;
	CTime	m_DataProve;
	CString	m_strTemperatura;
	CString	m_strSigla;
	CString	m_strPosizione;
	CString	m_strMateriale;
	CString	m_strOsservazioni;
	CString	m_strSezione;
	CString	m_strStruttura;
	double	m_lfKV;
	CString	m_strMacchina;
	CString	m_strSperimentatore;
	CString	m_strDataAccettazione;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImageList m_imageList;
	dati* m_pDatiCorrenti;
	long m_nCodProvinoCorrente;
	void RiempiAlbero(boolean selezionato);
	void DatiCertificato();
	byte m_bDatiCambiati;
	byte m_bDatiModificabili;
	void DisableModify(byte disabilita);
	CByteArray* InitBlob();

	// Generated message map functions
	//{{AFX_MSG(CMainDlg)
	afx_msg void OnSelchangedTreeProvini(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnModifica();
	afx_msg void OnButtonAnnulla();
	afx_msg void OnButtonConferma();
	afx_msg void OnDblclkTreeProvini(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboSperimentatori();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonNext();
	afx_msg void OnCloseupDataProva(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__2503246C_AF03_4386_B387_68CEFF1D9580__INCLUDED_)
