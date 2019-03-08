//{{AFX_INCLUDES()
//}}AFX_INCLUDES
#if !defined(AFX_STAMPAFATTUREDLG_H__BCE8FE45_2B25_11D8_9A8F_00A0CCCE3AB1__INCLUDED_)
#define AFX_STAMPAFATTUREDLG_H__BCE8FE45_2B25_11D8_9A8F_00A0CCCE3AB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StampaFattureDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStampaFattureDlg dialog
#include "bmobject.h"
#include "xbmpcontrol.h"

class CStampaFattureDlg : public CDialog
{
// Construction
public:
	CStampaFattureDlg(CWnd* pParent = NULL);   // standard constructor
  static BOOL CALLBACK ScanDatiFattura(CStringArray* pFieldNames, CStringArray* pFieldValues);
	static BOOL CALLBACK ScanServizi(CStringArray* pFieldNames, CStringArray* pFieldValues);
  static BOOL CALLBACK ScanPerServizio(CStringArray* pFieldNames, CStringArray* pFieldValues);
  // Dialog Data
	//{{AFX_DATA(CStampaFattureDlg)
	enum { IDD = IDD_DIALOG_STAMPA_FATTURE };
	CEdit	m_edtTotoRitAcconto;
	CEdit	m_edtRitAcconto;
	CButton	m_StaticDati;
	CDateTimeCtrl	m_DTCtrlDataFattura;
	CComboBox	m_ComboTipoPagamento;
	CComboBox	m_ComboCondizioniPagamento;
	CButton	m_BtnSpedizione;
	CButton	m_BtnStampaFattura;
	CButton	m_BtnEmettiFattura;
	CButton	m_BtnFatturaXML;
	CEdit	m_edtOrdineAcquisto;
	CDateTimeCtrl	m_DTCtrlDataOrdineAcquisto;
	CEdit	m_edtContratto;
	CDateTimeCtrl	m_DTCtrlDataContratto;
	CEdit	m_edtNumeroDDT;
	CDateTimeCtrl	m_DTCtrlDataDDT;
	BOOL	m_bSpedizione;
	BOOL	m_bPA;
	CString	m_strBanca;
	CString	m_strCAB;
	CString	m_strCodice;
	CString	m_strIndirizzo;
	CString	m_strNumero;
	CString	m_strPIVA;
	CString	m_strRagioneSociale;
	CString	m_strABI;
	CMSMask	m_MskSpeseSpedizione;
	CString	m_strAliquota;
	CString	m_strImponibile;
	CString	m_strTotale;
	CString	m_strImportoIVA;
	BOOL	m_bRaggruppaPerServizio;
	CTime	m_DataFattura;
	CString	m_strPIVA_CF;
	int		m_nNumCopie;
	CString	m_strSconto;
	CString	m_strImponibileScontato;
	CString	m_strCodFiscale;
	CString	m_csRitAcconto;
	CString	m_csTotRitAcconto;
	CString m_strCodiceDestinatario;
	CString m_strPEC;
	CString m_strCIG;
	CString m_strCUP;
	CString m_strOrdineAcquisto;
	CTime	m_DataOrdineAcquisto;
	CString m_strContratto;
	CTime	m_DataContratto;
	CString m_strNumeroDDT;
	CTime	m_DataDDT;
	CString m_strCodiceXML;
	BOOL m_bHeader;
	int		m_nEsigIVA;
	CString	m_strIBAN;
	CButton	m_BtnRipartizioneImponibile;
	//}}AFX_DATA

  CWinSigmaDoc* m_pDoc;
  static CFattureSet* m_pFattureEmesseSet;
  static CVerbaliSet* m_pVerbaliInfatturazione;
  static CServiziErogatiSet* m_pServiziErogati;
  static CAziendeSet* m_pAziendeSet;
  static long m_lCodiceAzienda;
  static long m_lCodiceFatturaEmessa;
  static CString m_strProgressiviVerbali;
  long m_lMaxNumFattura;
  static BOOL m_bFatturaEmessa;
  static BOOL m_bFatturaProForma;
  static int  m_nImponibile;
  static int  m_nImponibileScontato;
  static int  m_nIVA;
  int  m_nTotaleFattura;
  static int  m_nRitAcconto;
  static int  m_nTotRitAcconto;
  static int  m_nSpeseSpedizione;
  long m_lTipoPagamento;
  long m_lCondizioniPagamento;
  CDWordArray m_aryCodiciServizi;
  static CString m_strImporto;
  static CString m_strIVA;
  static CString m_strTotaleFattura;
  static CString m_strSpedizione;
  static double m_dSconto;
  static BOOL m_bSpedSelezionata;
  static int  m_nNumPagine;
  static long m_lCodiceServizio;
  static long m_lCodiceVerbale;
  static BOOL m_bMaggiorazione;
  static BOOL m_bVerbaliPrinted;
  static double m_dSpeseSpedizione;
  static CString m_strTipoPagamento;
  static CString m_strCondizioniPagamento;
  static int  m_nImportoVerbale;
  static BOOL m_bRiba;
  static double m_dAliquota;
  static CString m_strImportoScontato;
  static CString m_strTipoDocumento;
  static CString m_strCoordinateBancarie;
	BOOL m_bElett;
	double m_dImponibileXML;
	double m_dImpostaXML;
	double m_dImportoPagamentoXML;
  int m_nTipoDocumento;
	int m_nTipoVerbale;
	void SetHeader(BOOL bon);
	void PrnFromFattToFatt(int DaNumFatt = 0, int ANumFatt = 0, CString Anno = "", CWinSigmaDoc* m_pDoc = NULL);
	CString m_strRipartizioneImponibile;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStampaFattureDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
  void FindMaxNumeroFattura(void);
  void EmettiFattura(void);
  void CalcolaTotale(void);
  void CalcolaRitAcconto(void);
  void InitTipiPagamento(void);
  void InitCondizioniPagamento(void);
  BOOL CheckData(void);
  void SalvaFattura(void);
	void XMLHeaderDatiTrasmissione(FILE* f, int progressivo, CString versione);
	void XMLHeaderCedentePrestatore(FILE* f);
	BOOL XMLHeaderCessionarioCommittente(FILE* f);
	void XMLHeaderTerzoIntermediarioSoggettoEmittente(FILE* f);
	void XMLBodyDatiGenerali(FILE* f);
	void XMLBodyDatiBeniServizi(FILE* f);
	void XMLBodyDatiPagamento(FILE* f);
	void XMLAddMaggiorazioneUrgenza(FILE* f, int* pnum, double* pimpverb, double* pimptot);
	CString XMLValidate(CString& cs);
	CString m_csSum;
	BOOL ChangeChecker();
	int FilterANSI(CString& cs);
	CString GetPaymentMode();
	CString GetPaymentCondition();
	// Generated message map functions
	//{{AFX_MSG(CStampaFattureDlg)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonPrintFattura();
	afx_msg void OnButtonEmetti();
	afx_msg void OnButtonFatturaXML();
	afx_msg void OnCheckSpedizione();
	afx_msg void OnChangeMaskedboxSpeseSpedizione();
	afx_msg void OnChangeEditAliquota();
	afx_msg void OnCheckPerservizio();
	afx_msg void OnSelchangeComboTipoPagamento();
	afx_msg void OnSelchangeComboCondizioniPagamento();
	afx_msg void OnChangeEditSconto();
	afx_msg void OnChangeEditTotale();
	afx_msg void OnChangeEditRitAcconto();
	afx_msg void OnKillfocusEditOrdineAcquisto();
	afx_msg void OnKillfocusEditContratto();
	afx_msg void OnKillfocusEditNumeroDDT();
	afx_msg void OnButtonRipartizioneImponibile();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAMPAFATTUREDLG_H__BCE8FE45_2B25_11D8_9A8F_00A0CCCE3AB1__INCLUDED_)
