#if !defined(AFX_ARCHIVIOCERTIFICATIVIEW_H__7C640BE1_2A3E_11D8_B754_00C026108782__INCLUDED_)
#define AFX_ARCHIVIOCERTIFICATIVIEW_H__7C640BE1_2A3E_11D8_B754_00C026108782__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ArchivioCertificatiView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArchivioCertificatiView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CArchivioCertificatiView : public CFormView
{
protected:
	CArchivioCertificatiView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CArchivioCertificatiView)
	CCertificatiVerbaliSet* m_pSet;

private:
	void Carica_Combo();
	void Query();
	void Popola_Lista();
	bool Congruenza_Dati_Ricerca(CString* msg = NULL);
  void StampaCertificato(void);
// Form Data
public:
	//{{AFX_DATA(CArchivioCertificatiView)
	enum { IDD = IDD_FORM_ARCHIVIO_CERTIFICATI };
	CComboBox	m_ComboTipoCertificato;
	CEdit	m_EditNumeroCertificato;
	CComboBox	m_cmbAnni;
	CListCtrl	m_Risultati_Ricerca;
	CButton m_rbIntestazione_Certificati;
	CButton m_rbIntestazione_Fatture;
	CButton m_rbImpresa_Costruttrice;
	CButton m_rbDestinatario_Certificati;
	CString	m_csNumero_Certificato;
	CString	m_csNumero_Verbale;
	CString	m_csRagione_Sociale;
	CString	m_csCodice;
	CString	m_strNumCertificati;
	CString	m_strNumeroFattura;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	CImageList m_imgCertificati;
	BOOL IsEditCtrl(CWnd* pWnd);
	afx_msg void OnUpdateEditCopyCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnEditUndo();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArchivioCertificatiView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CTipiCertificatoSet* m_pTipiCertSet;
	virtual ~CArchivioCertificatiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CArchivioCertificatiView)
	afx_msg void OnButtonRicerca();
	afx_msg void OnDblclkListRisultatoRicerca(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnEliminacertificato();
	afx_msg void OnPreviewDoc();
	afx_msg void OnStampa();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARCHIVIOCERTIFICATIVIEW_H__7C640BE1_2A3E_11D8_B754_00C026108782__INCLUDED_)
