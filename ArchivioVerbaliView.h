#if !defined(AFX_ARCHIVIOVERBALIVIEW_H__7C640BE0_2A3E_11D8_B754_00C026108782__INCLUDED_)
#define AFX_ARCHIVIOVERBALIVIEW_H__7C640BE0_2A3E_11D8_B754_00C026108782__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ArchivioVerbaliView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArchivioVerbaliView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CArchivioVerbaliView : public CFormView
{
protected:
	CArchivioVerbaliView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CArchivioVerbaliView)
	CVerbaliSet* m_pSetVerbali;

private:
	void Query(BOOL bVA = FALSE);
	void Popola_Lista();
  void ApriDocumento(void);
  // Form Data
public:
	//{{AFX_DATA(CArchivioVerbaliView)
	enum { IDD = IDD_FORM_ARCHIVIO_VERBALI };
	CComboBox	m_cmbAnni;
	CListCtrl	m_Risultati_Ricerca;
	CButton m_rbIntestazione_Certificati;
	CButton m_rbIntestazione_Fatture;
	CButton m_rbImpresa_Costruttrice;
	CButton m_rbDestinatario_Certificati;
	CString	m_csRagione_Sociale;
	CString	m_csCodice;
	BOOL	m_chkVerbaliAperti;
	CString	m_csDaNumero;
	CString	m_csANumero;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArchivioVerbaliView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CArchivioVerbaliView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CArchivioVerbaliView)
	afx_msg void OnButtonRicerca();
	afx_msg void OnDblclkListRisultatoRicerca(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonRicercaAvanzata();
	afx_msg void OnOpenDoc();
	afx_msg void OnPreviewDoc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARCHIVIOVERBALIVIEW_H__7C640BE0_2A3E_11D8_B754_00C026108782__INCLUDED_)
