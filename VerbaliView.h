#if !defined(AFX_VERBALIVIEW_H__4DD6DDC0_BB94_11D7_B754_0080AD70B2EE__INCLUDED_)
#define AFX_VERBALIVIEW_H__4DD6DDC0_BB94_11D7_B754_0080AD70B2EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VerbaliView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVerbaliView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#define TIME_OUT_MSG_ID   WM_USER + 3

class CVerbaliView : public CXFormView
{
protected:
	CVerbaliView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CVerbaliView)
	static BOOL CALLBACK ScanFields(CStringArray* pFieldNames, CStringArray* pFieldValues);
  static BOOL CALLBACK ScanCampioni(CStringArray* pFieldNames, CStringArray* pFieldValues);
  static BOOL CALLBACK ScanProviniMinuta(CStringArray* pFieldNames, CStringArray* pFieldValues);
	static BOOL CALLBACK ScanEtichette(CStringArray* pFieldNames, CStringArray* pFieldValues);
// Form Data
public:
	//{{AFX_DATA(CVerbaliView)
	enum { IDD = IDD_FORM_VERBALI };
	CComboBox	m_ComboTipoProva;
	CEdit	m_EditCodFiscale;
	CButton	m_chkRitiro;
	CButton	m_BtnEmenda;
	CEdit	m_EditPartitaIva;
	CEdit	m_EditDestinatario;
	CComboBox	m_ComboConsegna;
	CEdit	m_EditCantiere;
	CEdit	m_EditOraConsegna;
	CEdit	m_EditRichiedente;
	CButton	m_BtnDomandaSottoscritta;
	CButton	m_BtnCopia;
	CButton	m_BtnDatiProvini;
	CButton	m_BtnLungaScadenza;
	CButton	m_BtnSpedIntestatario;
	CButton	m_BtnConsegna;
	CEdit	m_EditNote;
	CButton	m_BtnAutoProve;
	CButton	m_BtnAutoMateriale;
	CButton	m_BtnLettera;
	CEdit	m_EditCosto;
	CEdit	m_EditTipoVerbale;
	CEdit	m_EditNumSerie;
	CButton	m_BtnModificaSerie;
	CButton	m_BtnEliminaSerie;
	CButton	m_BtnAggiungiSerie;
	CDateTimeCtrl	m_CtrlDataConsegna;
	CDateTimeCtrl	m_CtrlDataAccettazione;
	CEdit	m_EditMaterialeConsegnato;
	CEdit	m_EditProveRichieste;
	CEdit	m_EditProprietario;
	CEdit	m_EditNomeAzImpresa;
	CEdit	m_EditNomeAzFattura;
	CEdit	m_EditNomeAzCertificato;
	CEdit	m_EditLetteraIncarico;
	CEdit	m_EditDirettore;
	CEdit	m_EditCodiceAzImpresa;
	CEdit	m_EditCodiceAzFattura;
	CEdit	m_EditCodiceAzCertificato;
	CComboBox	m_ComboDataConsegna;
	CComboBox	m_ComboDataAccettazione;
	CButton	m_BtnUrgenza;
	CButton	m_BtnOgniSerie;
	CButton	m_BtnCerca;
	CListCtrl	m_ListSerie;
	BOOL	m_bCertificatoOgniSerie;
	BOOL	m_bUrgenza;
	CString	m_strCodiceAzFattura;
	CString	m_strCodiceImpresa;
	CString	m_strDirettore;
	CString	m_strLetteraIncarico;
	CString	m_strNomeAzCertificato;
	CString	m_strCodiceAzCertificato;
	CString	m_strNomeAzFattura;
	CString	m_strNomeImpresa;
	int		m_nNumSerie;
	CString	m_strProprietario;
	CString	m_strProveRichieste;
	CString	m_strTipoVerbale;
	CString	m_strMaterialeConsegnato;
	CTime	m_DataAccettazione;
	CTime	m_DataConsegna;
	CString	m_strCosto;
	BOOL	m_bLetteraIncarico;
	CString	m_strNote;
	int		m_nConsegna;
	BOOL	m_bLungaScadenza;
	BOOL	m_bDomandaSottoscritta;
	CString	m_strRichiedente;
	CString	m_strOraConsegna;
	CString	m_strCantiere;
	CString	m_strDestinatario;
	CString	m_strPartitaIva;
	CString	m_strTipoPagamento;
	BOOL	m_bRitiro;
	CString	m_strCodFiscale;
	//}}AFX_DATA
  
// Attributes
public:
protected:
  static CVerbaliSet* m_pVerbaliSet;
  static CSerieSet*   m_pSerieSet;
	static CTipiCertificatoSet* m_pTipiCertificatoSet;
  BOOL m_bNuovoVerbale;
	BOOL m_bListinoGenerale;
	int m_nListinoGenerale;
	int m_nListinoParticolare;
  int m_nConCertProvv, m_nConCert;   
  int m_nSenzaCertProvv, m_nSenzaCert;  
  int m_nGeologiaProvv, m_nGeologia;
  int m_nTotVerbaliProvv, m_nTotVerbali;
  int m_nCertificati, m_nSeriePos;
  int m_nCodiceAzFattura, m_nCodiceAzCertificato, m_nCodiceImpresa;
  int m_nCodiceUltimaSerie;
  int m_nTipoVerbale;
  BOOL m_bSerieDataChanged;
  CStringArray m_aryPosSerie;
  CDWordArray   m_arySerieEliminate, m_arySerieAggiunte;
  BOOL m_bSpedizione;
  int m_nNumeroProvini;
  CVerbaliSet* m_pGlobalVerbaliSet;
  CSerieSet* m_pGlobalSerieSet;
  // 
  CString m_strIndAzCertificati, m_strIndImpresa, m_strIndAzFattura;

  static BOOL m_bPrivato;
  static BOOL m_bNote;
  static int m_nTotalePagine;
  static BOOL m_bSpianatura;
	static CAllTables* m_pTabelle;
	static CString m_strDllCorrente;
	static long m_nCodSerieStampata;
	static int m_nContaProvini;
  static m_nPosCertificato;
	CImageList  m_imgSerie;
	CFont m_FontLarge;
// Operations
public:
//	static BOOL m_bStampaCaratteri;
	static int m_nPrintMode;
	static void StampaCertificato(CTipiCertificatoSet* pSet, long codRif, BOOL isCodSerie = TRUE, BOOL bHeader = FALSE );
	static void StampaCertificato(long codRif, BOOL isCodSerie = TRUE, BOOL bHeader = FALSE );
	void CreaEmendamento(long codDoc);
	static CStringArray m_aryCampiEtichette;
	static int m_nContaEtichette;
	static int m_nSaltaEtichette;
	void ModificaCertificato(long codSerie);
	static BOOL CALLBACK ScanProvini(CStringArray* pFieldNames, CStringArray* pFieldValues);
  void EnableAddedServices(int service, BOOL bEnable, BOOL bSet);
  void SetFieldsMinuta(CStringArray* pFieldNames, CStringArray* pFieldValues);
  void FindVerbali(int searchParam);
  BOOL IsDaListinoParticolare(long codSerie);
  static  CString FormatIndirizzo(CAziendeSet* m_pSet);
  static 	void ErogaServiziSerie(CSerieSet* pSerieSet);
	static  void ErogaServizio(CSerieSet* pSerieSet, CCategorieServiziSet* pServListSet, CServiziErogatiSet* pServErogSet);


  // Operations
protected:
  void		LoadCurRecord(BOOL bData);
	BOOL		IsDataChanged();
	BOOL		ValidateData();
  void		NuovoVerbale(WORD ViewMode); 
  BOOL		NewRecord();
	BOOL		SaveRecord();
	BOOL		DeleteRecord();
	void		EnableControls(BOOL bEnable);
	CString GetToolTip(int nID);
  void		LoadSeries(int nVerbale);
  void		FindNumVerbali(BOOL bProvvisori);
  BOOL		AddProvini(CSerieSet* pSerieSet, int nCodice = 0);
  void		DeleteProvini(long codiceSerie, BOOL bVerify);
  void		ModificaSerie(int n);
  BOOL    CheckEditableSeries(BOOL bVerifyAll);
	void		LiberaTabellaProvini(int codSerie);
	void		ElaboraProvini(int codSerie, boolean salva, CPtrArray* blobs);
  int			TrovaCodiceAzienda(int azSelezionata);
  void		PrintMinuta(void);
  void		GetDatiFatturazione(void);
  void    FindDatiAziendaSpedizione(int nCodice);
  void		PrintVerbale();
  BOOL    VerificaProviniPerCertificato(int nVerbale);
	static  CString BuildCertificateName(CCertificatiVerbaliSet* pCertVerbSet);
  // Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVerbaliView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CTime m_DataProva;
	CString m_strTempEtichette;
	CDWordArray m_paryTCerMinute;
	void RiscriviDatiSerie(int indexSerie);
	void AggiornaAlbero();
	double m_lfCostoTotale;
	long m_nCodSperiment;
	static long m_nSerieInStampa;
	void SetProveMateriale(byte forzaProve, byte forzaMateriale);
	void StampaCertificati(BOOL bHeader = false);
	static int LoadDatiStampa(long codCertificato, CStringArray* pFieldNames, CStringArray* pFieldValues);

	void SetServiziAggiuntivi(CDWordArray* paryServiziAggiuntivi);
  static CString GetNameModuloDll(long codTipoCertificato);
	void ModificaRisultati(int indexSerie);
	virtual ~CVerbaliView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CVerbaliView)
	afx_msg void OnNuovo();
	afx_msg void OnNuovoVerbale();
	afx_msg void OnButtonModifica();
	afx_msg void OnButtonAggiungi();
	afx_msg void OnButtonElimina();
	afx_msg void OnDblclkListSerie(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckOgniserie();
	afx_msg void OnCheckLettera();
	afx_msg void OnCheckUrgenza();
	afx_msg void OnButtonEmissioneCertificati();
	afx_msg void OnModifica();
	afx_msg void OnChangeEditCodAzFattura();
	afx_msg void OnChangeEditNomeAzFattura();
	afx_msg void OnPrintMinuta();
	afx_msg void OnKillfocusEditCodAzCertificato();
	afx_msg void OnKillfocusEditCodAzFattura();
	afx_msg void OnKillfocusEditCodAzImpresa();
	afx_msg void OnKillfocusEditNomeAzCertificato();
	afx_msg void OnKillfocusEditNomeAzFattura();
	afx_msg void OnKillfocusEditNomeAzImpresa();
	afx_msg void OnButtonStampaCertificati();
	afx_msg void OnButtonStampaCertificatiConHeader();
	afx_msg void OnPrnCartaIntestata();
	afx_msg void OnPrnCartaLibera();
	afx_msg void OnPrnVerbaleConIntestazione();
	afx_msg void OnCheckLungaScadenza();
	afx_msg void OnButtonAutoMateriale();
	afx_msg void OnButtonAutoProve();
	afx_msg void OnDatiProvini();
	afx_msg void OnButtonDatiProvini();
	afx_msg void OnChiudiVerbale();
	afx_msg void OnMettiInFatturazione();
	afx_msg void OnAnnullaVerbale();
	afx_msg void OnButtonCopy();
	afx_msg void OnTimer(UINT nIDEvent);
  afx_msg void OnPrintNoComm(WPARAM wParam, LPARAM lParam);
  afx_msg void OnPrintThreadOk(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSelchangeComboConsegna();
	afx_msg void OnFindVerbCantiere();
	afx_msg void OnFindVerbCertificato();
	afx_msg void OnFindVerbDirLavori();
	afx_msg void OnFindVerbFattura();
	afx_msg void OnFindVerbImpresa();
	afx_msg void OnButtonModificaCertificato();
	afx_msg void OnAggiornaAlbero();
	afx_msg void OnSbloccoVerbale();
	afx_msg void OnSbloccacertificazione();
	afx_msg void OnStampaEtichette();
	afx_msg void OnButtonAggiorna();
	afx_msg void OnFindVerbStruttura();
	afx_msg void OnPrintSchedaIntFattura();
	afx_msg void OnPrnFatturaProforma();
	afx_msg void OnFindVerbSigla();
	afx_msg void OnNuovoGeologia();
	afx_msg void OnButtonEmenda();
	afx_msg void OnClickListSerie(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckRitiro();
	afx_msg void OnFindVerbNumero();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VERBALIVIEW_H__4DD6DDC0_BB94_11D7_B754_0080AD70B2EE__INCLUDED_)
