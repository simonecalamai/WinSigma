#if !defined(AFX_MAINDLG_H__9F618918_0040_48BD_B53A_AEAA49E66D29__INCLUDED_)
#define AFX_MAINDLG_H__9F618918_0040_48BD_B53A_AEAA49E66D29__INCLUDED_

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
	CDateTimeCtrl	m_ctrDataProve;
	CButton	m_BtnOk;
	CButton	m_BtnCancel;
	CButton	m_BtnConferma;
	CButton	m_BtnAnnulla;
	CButton	m_BtnModifica;
	CTreeCtrl	m_TreeProvini;
	CEdit	m_EdtTensione;
	CEdit	m_EdtRottura;
	CEdit	m_edtModulo;
	CEdit	m_EdtLimite2;
	CEdit	m_EdtLimite1;
	CEdit	m_EdtArea;
	CEdit	m_EdtAllungamento;
	CEdit	m_EdtOsservazioni;
	CComboBox	m_ComboSperimentatori;
	CComboBox	m_ComboMacchine;
	CTime	m_DataProve;
	CString	m_strMateriale;
	CString	m_strOsservazioni;
	CString	m_strPosizione;
	CString	m_strSigla;
	CString	m_strStruttura;
	double	m_lfArea;
	double	m_lfLimite1;
	double	m_lfLimite2;
	double	m_lfModulo;
	double	m_lfRottura;
	double	m_lfTensione;
	CString	m_strDataAccettazione;
	CString	m_strAllungamento;
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
	CString m_strMacchina;
	CString m_strSperimentatore;
	dati* m_pDatiCorrenti;
	byte m_bDatiCambiati;
	byte m_bDatiModificabili;
	void DisableModify(byte disabilita);
	long m_nCodProvinoCorrente;
	void RiempiAlbero(boolean selezionato);
	void DatiCertificato();
	CByteArray* InitBlob();

	// Generated message map functions
	//{{AFX_MSG(CMainDlg)
	afx_msg void OnButtonNext();
	afx_msg void OnDblclkTreeProvini(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCloseupDataProva(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTreeProvini(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonAnnulla();
	afx_msg void OnButtonConferma();
	afx_msg void OnBtnModifica();
	virtual void OnOK();
	afx_msg void OnSelchangeComboSperimentatori();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__9F618918_0040_48BD_B53A_AEAA49E66D29__INCLUDED_)
