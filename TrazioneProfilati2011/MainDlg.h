#if !defined(AFX_MAINDLG_H__2A65DB24_539C_4614_9D88_B37AE9ADD440__INCLUDED_)
#define AFX_MAINDLG_H__2A65DB24_539C_4614_9D88_B37AE9ADD440__INCLUDED_

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
	COperatoriSet* m_pOperatoriSet;
	CSerieSet* m_pSerieSet;
	CMainDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMainDlg)
	enum { IDD = IDD_DIALOG_MAIN };
	CEdit	m_EdtLarghezza;
	CEdit	m_EdtSpessore;
	CDateTimeCtrl	m_ctrDataProve;
	CEdit	m_EdtSnervamento;
	CEdit	m_EdtRottura;
	CEdit	m_EdtArea;
	CEdit	m_EdtAllungamento;
	CTreeCtrl	m_TreeProvini;
	CButton	m_BtnOk;
	CButton	m_BtnCancel;
	CEdit	m_EdtOsservazioni;
	CComboBox	m_ComboSperimentatori;
	CComboBox	m_ComboMacchine;
	CButton	m_BtnConferma;
	CButton	m_BtnAnnulla;
	CButton	m_BtnModifica;
	CTime	m_DataProve;
	CString	m_strMateriale;
	CString	m_strOsservazioni;
	CString	m_strSigla;
	CString	m_strStruttura;
	CString	m_strPosizione;
	double	m_lfArea;
	double	m_lfAllungamento;
	double	m_lfRottura;
	double	m_lfSnervamento;
	CString	m_strDataAccettazione;
	double	m_lfLarghezza;
	double	m_lfSpessore;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void CalcolaSezione();
	CString m_strMacchina;
	CString m_strSperimentatore;
	CImageList m_imageList;
	dati* m_pDatiCorrenti;
	long m_nCodProvinoCorrente;
	void RiempiAlbero(boolean selezionato);
	byte m_bDatiCambiati;
	void DisableModify(byte disabilita);
	byte m_bDatiModificabili;
	void DatiCertificato();
	CByteArray* InitBlob();

	// Generated message map functions
	//{{AFX_MSG(CMainDlg)
	afx_msg void OnSelchangedTreeProvini(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonConferma();
	afx_msg void OnButtonAnnulla();
	afx_msg void OnBtnModifica();
	afx_msg void OnDblclkTreeProvini(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboSperimentatori();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonNext();
	afx_msg void OnCloseupDataProva(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEdtSpessore();
	afx_msg void OnKillfocusEdtLarghezza();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__2A65DB24_539C_4614_9D88_B37AE9ADD440__INCLUDED_)
