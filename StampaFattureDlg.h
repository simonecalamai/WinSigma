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
	CButton	m_BtnSpedizione;
	CButton	m_BtnStampaFattura;
	CButton	m_BtnEmettiFattura;
	BOOL	m_bSpedizione;
	BOOL	m_bPA;
	BOOL	m_bIVADifferita;
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
  static int  m_nImportoVerbale;
  static BOOL m_bRiba;
  static double m_dAliquota;
  static CString m_strImportoScontato;
  static CString m_strTipoDocumento;
  static CString m_strCoordinateBancarie;
	BOOL m_bElett;
  int m_nTipoDocumento;
	void PrnFromFattToFatt(int DaNumFatt = 0, int ANumFatt = 0, CString Anno = "", CWinSigmaDoc* m_pDoc = NULL);

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
  BOOL CheckData(void);
  void SalvaFattura(void);
	// Generated message map functions
	//{{AFX_MSG(CStampaFattureDlg)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonPrintFattura();
	afx_msg void OnButtonEmetti();
	afx_msg void OnCheckSpedizione();
	afx_msg void OnChangeMaskedboxSpeseSpedizione();
	afx_msg void OnChangeEditAliquota();
	afx_msg void OnCheckPerservizio();
	afx_msg void OnSelchangeComboTipoPagamento();
	afx_msg void OnChangeEditSconto();
	afx_msg void OnChangeEditTotale();
	afx_msg void OnChangeEditRitAcconto();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAMPAFATTUREDLG_H__BCE8FE45_2B25_11D8_9A8F_00A0CCCE3AB1__INCLUDED_)
