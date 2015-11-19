#if !defined(AFX_MAINDLG_H__6E934932_D4D1_4AF7_81BE_E26F2CF07966__INCLUDED_)
#define AFX_MAINDLG_H__6E934932_D4D1_4AF7_81BE_E26F2CF07966__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainDlg.h : header file
//

#include "..\XDialog.h"
#include "math.h"

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog

class CMainDlg : public CXDialog
{
// Construction
public:
	int m_nVariante;
	int m_iAnnullaMarchio;
	int m_iOldIndexMarchio;
	DWORD m_iFirstItem;
	bool m_bPrimaSelezione;
	CTime* m_pUltimaDataProve;
	long* m_pUltimoSper;
	CTime m_DataAccettazione;
	CMarchiSet* m_pMarchiSet;
	COperatoriSet* m_pOperatoriSet;
	long m_nCodProvinoCorrente;
	byte ProveRichieste(CServiziListinoSet* pServiziSet, CSerieSet* pSerieSet);
	CServiziListinoSet* m_pServiziListinoSet;
	CProviniSet* m_pProviniSet;
	CSerieSet* m_pSerieSet;
	CTipiCertificatoSet* m_pTipoCertSet;
	CMainDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMainDlg)
	enum { IDD = IDD_DIALOG_TPBARE_B450_2010 };
	CEdit	m_ctrlFornitore;
	CButton	m_ctrlRotoliCT;
	CStatic	m_lblPerc;
	CStatic	m_lblAll;
	CEdit	m_editIndiceAllungamento;
	CButton	m_BtnCalcoliConDecimali;
	CEdit	m_EdtFyk;
	CComboBox	m_ComboMarchi;
	CButton	m_BtnPOS;
	CButton	m_BtnNEG;
	CEdit	m_EdtOsservazioni;
	CComboBox	m_ComboSperimentatori;
	CComboBox	m_ComboMacchine;
	CEdit	m_EdtMandrino;
	CDateTimeCtrl	m_ctrDataProve;
	CButton	m_BtnOk;
	CButton	m_BtnCancel;
	CTreeCtrl	m_TreeProvini;
	CEdit		m_EdtAderenza;
	CEdit		m_EdtSnervamento;
	CEdit		m_EdtRottura;
	CEdit		m_EdtPeso;
	CEdit		m_EdtAllungamento;
	CEdit		m_EdtLunghezza;
	CButton	m_BtnConferma;
	CButton	m_BtnAnnulla;
	CButton	m_BtnModifica;
	CString	m_strFiCalcolato;
	int			m_nIndiceAllungamento;
	double	m_lfLunghezza;
	CString	m_strSezioneEffettiva;
	CString	m_strSnervamentoRelativo;
	CString	m_strAllungamentoPercentuale;
	CString	m_strTensioneRelativa;
	CString	m_strTolleranzaPercentuale;
	double	m_lfAllungamento;
	int			m_nFiNominale;
	double	m_lfPeso;
	double	m_lfRottura;
	double	m_lfSnervamento;
	CString	m_strTestData;
	CTime	m_DataProve;
	CString	m_strOsservazioni;
	CString	m_strMacchina;
	CString	m_strSperimentatore;
	CString	m_strSigla;
	CString	m_strStruttura;
	double	m_lfAderenza;
	int			m_nMandrino;
	int			m_nPOS;
	int			m_nNEG;
	CString	m_strPosizione;
	CString	m_strMateriale;
	CString	m_strDataAccettazione;
	double	m_lfFyk;
	BOOL	m_bCalcoliConDecimali;
	CString	m_csmmper;
	CString	m_csAllAgt;
	CString	m_csAllAgtPer;
	BOOL	m_bRotoliCT;
	CString	m_csFornitore;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	byte m_bDatiModificabili;
	int SceltaMandrino();
	void DatiCertificato();
	byte m_bDatiCambiati;
	void AbilitaControlli();
	void RiempiAlbero(boolean selezionato);
	byte m_nProveRichieste;
	CImageList m_imageList;
	byte CalcolaDati(BOOL bConDecimali);
	dati* m_pDatiCorrenti;
	void DisableModify(boolean disabilita);
	CByteArray* InitBlob();

	// Generated message map functions
	//{{AFX_MSG(CMainDlg)
	afx_msg void OnBtnModifica();
	afx_msg void OnButtonAnnulla();
	afx_msg void OnButtonConferma();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedTreeProvini(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkTreeProvini(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnSelchangeComboSperimentatori();
	afx_msg void OnRadioNeg();
	afx_msg void OnRadioPos();
	afx_msg void OnButtonNext();
	afx_msg void OnCloseupDataProva(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEdtAllungamento();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINDLG_H__6E934932_D4D1_4AF7_81BE_E26F2CF07966__INCLUDED_)
