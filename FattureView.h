#if !defined(AFX_FATTUREVIEW_H__09895980_BB90_11D7_B754_0080AD70B2EE__INCLUDED_)
#define AFX_FATTUREVIEW_H__09895980_BB90_11D7_B754_0080AD70B2EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FattureView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFattureView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CFattureView : public CXFormView
{
protected:
	CFattureView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CFattureView)

// Form Data
public:
	//{{AFX_DATA(CFattureView)
	enum { IDD = IDD_FORM_FATTURE };
	CDateTimeCtrl	m_DTCtrlDataEmissione;
	CEdit	m_EditTipoDoc;
	CEdit	m_EditSconto;
	CEdit	m_EditP_IVA;
	CEdit	m_EditIndirizzo;
	CEdit	m_EditCodFiscale;
	CEdit	m_EditCAB;
	CEdit	m_EditBanca;
	CEdit	m_EditABI;
	CComboBox	m_ComboTipoPagamento;
	CEdit	m_EditRagioneSociale;
	CEdit	m_EditCodiceCliente;
	CEdit	m_EditCodiceDestinatario;
	CEdit	m_EditPEC;
	CEdit	m_EditCodiceXML;
	CListCtrl	m_ListVerbali;
	CListCtrl	m_ListServizi;
	CButton	m_BtnModifyServizio;
	CButton	m_BtnDeleteServizio;
	CButton	m_BtnAddServizio;
	CString	m_strBanca;
	CString	m_strCodiceCliente;
	CString	m_strImporto;
	CString	m_strP_IVA;
	CString	m_strRagioneSociale;
	CString	m_strIndirizzo;
	CString	m_strSconto;
	CString	m_strABI;
	CString	m_strCAB;
	CString	m_strCodiceFiscale;
	CString	m_strTipoPagamento;
	CString	m_strAliquota;
	CString	m_strImportoScontato;
	CString	m_strIVA;
	CString	m_strScontoFattura;
	CString	m_strTotale;
	CString	m_strSpeseSpedizione;
	CString	m_strTipoDocumento;
	CTime	m_DataEmissione;
	CString	m_csRitAcconto;
	CString	m_csTotRitAcconto;
	CString	m_strCodiceDestinatario;
	CString	m_strPEC;
	CString m_strCIG;
	CString m_strCUP;
	CString m_strOrdineAcquisto;
	CTime	m_DataOrdineAcquisto;
	CString m_strContratto;
	CTime	m_DataContratto;
	CString m_strNumeroDDT;
	CTime	m_DataDDT;
	CString	m_strCodiceXML;
	CEdit	m_EditIBAN;
	CString	m_strIBAN;
	//}}AFX_DATA

// Attributes
public:
  CVerbaliSet* m_pVerbaliInFatturazione;
  CServiziErogatiSet* m_pServiziErogati;
  CStringArray m_aryScadenzePagamento;
  CDWordArray   m_aryCodServiziSelezionati;
  CFattureSet* m_pFattureEmesseSet;
  long  m_lMaxNumFattura;
  BOOL m_bVerbaliChecked;
  BOOL m_bServiziChecked;
  BOOL m_bEnableServiziCheck;
  double m_dSconto;
  long m_lCodiceAzienda;
  long m_lCodiceFattura;
  long m_lCodiceUltimoVerbale;
  long m_lTipoPagamento;
  long m_lCondizioniPagamento;
  int m_nTotaleFattura;
  int m_nImponibile;
  int m_nImponibileScontato;
  int m_nIVA;
  long m_lListinoGenerale;
  long m_lListinoParticolare;
  int  m_nState;
  int  m_nTipoDocumento;
  long m_lLastFattura;
  
// Operations
public:
protected:
  void LoadCurRecord(BOOL bData);
	BOOL IsDataChanged();
	BOOL ValidateData();
  BOOL NewRecord();
	BOOL SaveRecord();
	BOOL DeleteRecord();
	void EnableControls(BOOL bEnable);
  void EnableServicesBtns(BOOL bEnable);
  void LoadServizi(void);
  void CalcolaTotale(void);
  void EmettiSalvaFattura(BOOL bElett = FALSE);
  void GetDatiAzienda(CAziendeSet* pSet);
  BOOL IsDaListinoParticolare(long codiceServizio);
  int VerificaSelezione(void);
  void EliminaDocInFatturazione(void);
  void RicalcolaDatiFattura(void);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFattureView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void PrintProforma(BOOL bheader = TRUE);
	void AggiornaAlbero();
	virtual ~CFattureView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CFattureView)
	afx_msg void OnEsportaFatture();
	afx_msg void OnFatturaEmetti();
	afx_msg void OnFatturaXML();
	afx_msg void OnFatturaElettEmetti();
	afx_msg void OnButtonAddServizio();
	afx_msg void OnButtonDelServizio();
	afx_msg void OnButtonModifyServizio();
	afx_msg void OnCheckSpedizione();
	afx_msg void OnItemchangingListVerbali(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListServizi(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListVerbali(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnVisualizzaFattura();
	afx_msg void OnTrovaAzienda();
	afx_msg void OnNuovaSenzaVerbale();
	afx_msg void OnKillfocusEditCodCliente();
	afx_msg void OnKillfocusEditRagioneSociale();
	afx_msg void OnKillfocusEditPIva();
  afx_msg void OnPrintProforma(void);
  afx_msg void OnStampaeffetti();
	afx_msg void OnButtonAggiorna();
	afx_msg void OnNotacreditoArchivia();
	afx_msg void OnNotacreditoNuova();
	afx_msg void OnSbloccaFattura();
	afx_msg void OnSbloccaFatturazione();
	afx_msg void OnDblclkListVerbali(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDelInfatturazione();
	afx_msg void OnInsertVerbale();
	afx_msg void OnFatturaArchiviaSingolafattura();
	afx_msg void OnFatturaArchiviaGruppofatture();
	afx_msg void OnDatetimechangeDatetimepickerDataEmissione(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FATTUREVIEW_H__09895980_BB90_11D7_B754_0080AD70B2EE__INCLUDED_)
