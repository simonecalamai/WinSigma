// AziendeView.h: interface for the CAziendeView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AZIENDEVIEW_H__150DFC40_DD71_11D7_9A8F_00A0CCCE3AB1__INCLUDED_)
#define AFX_AZIENDEVIEW_H__150DFC40_DD71_11D7_9A8F_00A0CCCE3AB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "ArchivioAziende.h"
#include "DatiAziende.h"

class CCodiceFiscale 
{
public:
	BYTE GetTipoCodice();
	BYTE m_byTipoCodice;
	CCodiceFiscale(void);
	CCodiceFiscale(CString codice);
	void SetCodice(CString ccodice);
	CString& GetCodice(void);
	BOOL Valida(void);
	
protected:
	void SetTipoCodice();
	CString m_csCodice;
	char m_cCarattereDiControllo;
	void CalcolaCarattereDiControllo(void); 
	BOOL ValidaCarattereDiControllo(void);
};

class CAziendeView : public CXFormView  
{
protected:
	CAziendeView();
	int ControllaCodice(CString str);
  DECLARE_DYNCREATE(CAziendeView)

// Data    
public:
	//{{AFX_DATA(CAziendeView)
	enum { IDD = IDD_FORM_AZIENDE };
	CComboBox	m_cbxCAP;
	CButton	m_BtnModificaVerbale;
	CButton	m_StaticVerbaliFarlocchi;
	CButton	m_BtnEliminaVerbale;
	CButton	m_btGenera_Codice;
	CButton	m_BtnInserisciVerbali;
	CEdit	m_EditCap_Spedizione;
	CEdit	m_EditCitta_Spedizione;
	CEdit	m_EditProvincia_Spedizione;
	CEdit	m_EditIndirizzo_Spedizione;
	CButton	m_btArchivio_Aziende;
	CButton	m_btDBRemoto;
	CEdit	m_EditCellulare;
	CButton	m_BtnPrivato;
	CEdit	m_EditTotaleVerbali;
	CButton	m_BtnListinoGenerale;
	CEdit	m_EditSconto;
	CEdit	m_EditVerbaliDaFatturare;
	CEdit	m_EditCAB;
	CEdit	m_EditBanca;
	CEdit	m_EditVerbaliAperti;
	CEdit	m_EditABI;
	CComboBox	m_ComboTipoPagamento;
	CEdit	m_EditTelefono;
	CEdit	m_EditRagioneSociale;
	CEdit	m_EditProvincia;
	CEdit	m_EditPIVA;
	CEdit	m_EditNote;
	CEdit	m_EditIndirizzo;
	CEdit	m_EditFax;
	CEdit	m_EditEMail;
	CEdit	m_EditCodiceFiscale;
	CEdit	m_EditCodiceAzienda;
	CEdit	m_EditPEC;
	CEdit	m_EditCodiceDestinatario;
	CEdit	m_EditCitta;
	CEdit	m_EditCAP;
	CButton	m_BtnAziendaImportante;
	CString	m_strRagioneSociale;
	CString	m_strCAP;
	CString	m_strCitta;
	CString	m_strCodiceFiscale;
	CString	m_strCodiceDestinatario;
	CString	m_strEMail;
	CString	m_strPEC;
	CString	m_strFax;
	CString	m_strIndirizzo;
	CString	m_strPIVA;
	CString	m_strProvincia;
	CString	m_strTelefono;
	BOOL	  m_bAziendaImportante;
	CString	m_strABI;
	CString	m_strBanca;
	CString	m_strCAB;
	CString	m_strNoteAzienda;
	int		m_nVerbaliDaFatturare;
	int		m_nVerbaliAperti;
	int		m_nTotaleVerbali;
	CListCtrl	m_ListCtrlVerbali;
	CString	m_strCodiceAzienda;
	double	m_dSconto;
	BOOL	m_bListinoGenerale;
	BOOL	m_bPrivato;
	CString	m_strCellulare;
	CString	m_csCap_Spedizione;
	CString	m_csIndirizzo_Spedizione;
	CString	m_csCitta_Spedizione;
	CString	m_csProvincia_Spedizione;
	CEdit		m_EditIBAN;
	CString	m_strIBAN;
	//}}AFX_DATA

protected:
	CAziendeSet* m_pSet;
	CAziendeSet* m_pAziendeRemoteSet;
	CAziendeSet* m_pCodice_Aziende;
	CAziendeSet* m_pCodice_Aziende_Remoto;
	CAziendeOldSet* m_pCodice_Aziende_Vecchie;
	CTipiPagamentoSet* m_pTipiPagamentoSet;
	CArchivioAziendeDlg* m_archivio_aziende;
	CDatiAziende* m_dati_aziende;
// Operations
protected:
  void CAP();
	void LoadCurRecord(BOOL bData);
	BOOL IsDataChanged();
	BOOL ValidateData();
	BOOL NewRecord();
	BOOL NewRecordRemoto(CString& strID, BOOL bCheckPresent);
	BOOL SaveRecord();
	BOOL SaveRecordRemoto(CString& strID);
	BOOL DeleteRecord();
	BOOL DeleteRecordRemoto(CString& strID);
	void EnableControls(BOOL bEnable);
	void LoadVerbali(CString strID);
	CString GetToolTip(int nID);
	void GeneraCodice();
  BOOL VerificaPI(void);
	void Clear(int* i = NULL);
	BOOL CheckIDExist(CString& strID);
	BOOL CheckPIVAExist(CString strPIVA = "");
	BOOL ValidateCodiceFiscale(void);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAziendeView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL
protected:
	BOOL m_bCodiceFiscaleValido;
	virtual ~CAziendeView();

	// Generated message map functions
	//{{AFX_MSG(CAziendeView)
	afx_msg void OnTrova();
	afx_msg void OnCheckPrivato();
	afx_msg void OnSetfocusEditCode();
	afx_msg void OnButtonArchivioAziende();
	afx_msg void OnButtonDBRemoto();
	afx_msg void OnButtonGeneraCodice();
	afx_msg void OnButtonInsert();
	afx_msg void OnButtonEliminaVfarlocco();
	afx_msg void OnButtonModificaVfarlocco();
	afx_msg void OnButtonAggiorna();
	afx_msg void OnReportVerbali();
	afx_msg void OnDblclkListVerbali(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNuovo();
	afx_msg void OnKillfocusEditProvincia();
	afx_msg void OnKillfocusEditCitta();
	afx_msg void OnSelchangeComboCap();
	afx_msg void OnKillfocusEditIndirizzo();
	afx_msg void OnKillfocusEditCodFisc();
	afx_msg void OnButtonUpdateFromDBR();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_AZIENDEVIEW_H__150DFC40_DD71_11D7_9A8F_00A0CCCE3AB1__INCLUDED_)
