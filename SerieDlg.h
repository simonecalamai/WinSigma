#if !defined(AFX_SERIEDLG_H__EB52B201_FA72_11D7_9A8F_00A0CCCE3AB1__INCLUDED_)
#define AFX_SERIEDLG_H__EB52B201_FA72_11D7_9A8F_00A0CCCE3AB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SerieDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSerieDlg dialog
#define TIPO_CERT   0
#define NUOVO_CERT  1

class CSerieDlg : public CXDialog
{
// Construction
public:
	CSerieDlg(CWnd* pParent = NULL);   // standard constructor
  ~CSerieDlg();

// Dialog Data
	//{{AFX_DATA(CSerieDlg)
	enum { IDD = IDD_DIALOG_SERIE };
	CEdit	m_EditSigla2;
	CStatic	m_StaticSigla2;
	CEdit	m_ctrlOsservazioni;
	CEdit	m_ctrlVerbalePrelievo;
	CEdit	m_ctrlSiglaFornitore;
	CDateTimeCtrl	m_DTCtrlScadenza;
	CEdit	m_ctrDataND;
	CButton	m_BtnNonDichiarata;
	CComboBox	m_ComboMateriale;
	CButton	m_BtnListinoGenerale;
	CStatic	m_StaticStruttura;
	CStatic	m_StaticSigla;
	CStatic	m_StaticMateriale;
	CEdit	m_EditStruttura;
	CEdit	m_EditSigla;
	CEdit	m_EditDimensione1;
	CEdit	m_EditDimensione2;
	CEdit	m_EditDimensione3;
	CDateTimeCtrl	m_DateCtrlPrelievo;
	CButton	m_BtnOk;
	CButton	m_BtnCancel;
	CListCtrl	m_ListServizi;
	CButton	m_BtnNuovoCertificato;
	CComboBox	m_ComboTipoCertificato;
	BOOL	m_bNuovoCertificato;
	CString	m_strPosizione;
	CTime	m_DataPrelievo;
	CString	m_strSigla;
	CString	m_strStruttura;
	CString	m_StaticDim1;
	CString	m_StaticDim2;
	CString	m_StaticDim3;
	int		m_nProviniRichiesti;
	int		m_nNumeroServizi;
	BOOL	m_bListinoGenerale;
	double	m_dDimensione1;
	double	m_dDimensione2;
	double	m_dDimensione3;
	CString	m_strMateriale;
	BOOL	m_bNonDichiarata;
	CString	m_strDataND;
	CTime	m_DataScadenza;
	CString	m_sSiglaFornitore;
	CString	m_sVerbalePrelievo;
	CString	m_csOsservazioni;
	CString	m_strSigla2;
	//}}AFX_DATA

  int m_nCodiceTipoCertificato;
  int m_nNumeroVerbale;
  int m_nCodiceSerie;
  int m_nPosSerie, m_nCertificato, m_nOldPos;
  int m_nCodiceAzienda;
  int m_nListinoGenerale, m_nListinoParticolare;
  int m_nNumeroProvini;
  BOOL m_bAccListGen;
  BOOL m_bNuovaSerie, m_bProva;
  BOOL m_bEnableTipo, m_bEnableNuovo;
  BOOL m_bServiceChecked, m_bServiceLoaded;
  CString m_strTitolo;
  CWinSigmaDoc* m_pDoc;
  CCategorieServiziSet* m_pCatServSet;
  CSerieSet*						m_pSerieSet;
  CTipiCertificatoSet*	m_pTCertificatoSet;
	CTipiMaterialeSet*		m_pMaterialiSet;
  CDWordArray						m_arySelectedServices;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerieDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
// Implementation
protected:
	BOOL VerificaCoerenza( long codServizio, BOOL inserimento );
	BOOL ProveRichieste();
	int m_nMaxProviniXCertificato;
	void LoadMateriali(void);
  void InitDialogData(void);
  void LoadServizi(void);
  void LoadSeriesData(void);
  void LoadTCertData(void);
  BOOL ValidateData(void);
  CString FormatDescrizione(void);
  void SetNuovoCertificato(BOOL bNuovo);
  void LoadLastSerie(byte CambiaTipiCertificato);
	long GetServAggiungibile();
	// Generated message map functions
	//{{AFX_MSG(CSerieDlg)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTipiCertificato();
	afx_msg void OnCheckNuovoCertificato();
	afx_msg void OnCheckListino();
	afx_msg void OnItemchangedListServizi(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckNonDichiarata();
	afx_msg void OnButtonNext();
	afx_msg void OnSelchangeComboMateriale();
	afx_msg void OnKillfocusEditStruttura();
	afx_msg void OnCloseupDatetimepickerPrelievo(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERIEDLG_H__EB52B201_FA72_11D7_9A8F_00A0CCCE3AB1__INCLUDED_)
