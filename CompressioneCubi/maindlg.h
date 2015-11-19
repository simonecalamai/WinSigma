#if !defined(AFX_MAINDLG_H__319CD17F_A91C_4199_83FD_0114DA5DFBF6__INCLUDED_)
#define AFX_MAINDLG_H__319CD17F_A91C_4199_83FD_0114DA5DFBF6__INCLUDED_

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
	CTime* m_pUltimaDataProva;
	long* m_pUltimoSper;
	int m_nGiorniMaturazione;
	CTime m_DataAccettazione;
	CTime m_DataMaturazione;
	COperatoriSet* m_pOperatoriSet;
	CServiziListinoSet* m_pServiziSet;
	BOOL RichiestaSpianatura();
	CServiziListinoSet* m_pServiziListinoSet;
	CProviniSet* m_pProviniSet;
	CSerieSet* m_pSerieSet;
	CMainDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMainDlg)
	enum { IDD = IDD_DIALOG_MAIN };
	CEdit	m_EdtOsservazioni;
	CComboBox	m_ComboSperimentatori;
	CComboBox	m_ComboMacchine;
	CButton	m_BtnCancel;
	CButton	m_BtnOk;
	CButton	m_BtnSpianatura;
	CTreeCtrl	m_TreeProvini;
	CDateTimeCtrl	m_ctrDataTest;
	CEdit	m_EdtMassa;
	CEdit	m_EdtLunghezza;
	CEdit	m_EdtLarghezza;
	CEdit	m_EdtCaricoSp;
	CEdit	m_EdtAltezza;
	CComboBox	m_ComboTipoRottura;
	CButton	m_BtnModifica;
	CButton	m_BtnConferma;
	CButton	m_BtnAnnulla;
	double	m_lfAltezza;
	double	m_lfCaricoSp;
	double	m_lfLarghezza;
	double	m_lfLunghezza;
	double	m_lfMassa;
	CString	m_strCbTipoRottura;
	CString	m_strArea;
	CString	m_strCompressione;
	CString	m_strRottura;
	CString	m_strDataPrelievo;
	CTime	m_DataProva;
	CString m_strSigla;
	CString	m_strMacchina;
	CString	m_strSperimentatore;
	CString	m_strOsservazioni;
	CString	m_strStruttura;
	CString	m_strPosizione;
	CString	m_strDataAccettazione;
	CString	m_strLunghezza;
	CString	m_strLarghezza;
	CString	m_strAltezza;
	CString	m_strUMArea;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL CalcolaDati();
	byte m_bDatiModificabili;
	void DatiCertificato();
	byte m_bDatiCambiati;
	CTime m_DataPrelievo;
	byte m_bSpianaturaRichiesta;
	void AggiornaDatiSerie();
	long m_nCodProvinoCorrente;
	void RiempiAlbero(boolean selezionato);
	CByteArray* m_pBlobCorrente;
	dati* m_pDatiCorrenti;
	CByteArray* InitBlob();
	void DisableModify(boolean disabilita);
	CImageList m_imageList;

	// Generated message map functions
	//{{AFX_MSG(CMainDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnConferma();
	afx_msg void OnBtnModifica();
	afx_msg void OnBtnAnnulla();
	afx_msg void OnSelchangedTreeProvini(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkTreeProvini(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnCloseupDataProva(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboSperimentatori();
	afx_msg void OnButtonNext();
	afx_msg void OnKillfocusEditCaricoSp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__319CD17F_A91C_4199_83FD_0114DA5DFBF6__INCLUDED_)
