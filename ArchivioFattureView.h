#if !defined(AFX_ARCHIVIOFATTUREVIEW_H__7C640BE2_2A3E_11D8_B754_00C026108782__INCLUDED_)
#define AFX_ARCHIVIOFATTUREVIEW_H__7C640BE2_2A3E_11D8_B754_00C026108782__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ArchivioFattureView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArchivioFattureView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CArchivioFattureView : public CFormView
{
protected:
	CArchivioFattureView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CArchivioFattureView)
	CFattureSet* m_pFattureSet;
  CVerbaliSet* m_pVerbaliSet;
  
private:
	void Query();
	void Popola_Lista();
  CString CalcolaTotale(void);
  void PrintFattura(BOOL bAnteprima, BOOL bDoppiaCopia, BOOL bHeader = TRUE);
// Form Data
public:
	//{{AFX_DATA(CArchivioFattureView)
	enum { IDD = IDD_FORM_ARCHIVIO_FATTURE };
	CComboBox	m_cmbAnni;
	CListCtrl	m_Risultati_Ricerca;
	CString	m_csRagione_Sociale;
	CString	m_csCodice;
	CString	m_csPartita_IVA;
	CString	m_csNumero_Verbale;
	CString	m_strNumFattura;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArchivioFattureView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CArchivioFattureView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CArchivioFattureView)
	afx_msg void OnButtonRicerca();
	afx_msg void OnDblclkListRisultatoRicerca(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFatturaStampaMultipla();
	afx_msg void OnFatturaStampaSingola();
	afx_msg void OnFatturaStampaMultiplaNoHeader();
	afx_msg void OnFatturaStampaSingolaNoHeader();
	afx_msg void OnRipristinaFattura();
	afx_msg void OnPreviewDoc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARCHIVIOFATTUREVIEW_H__7C640BE2_2A3E_11D8_B754_00C026108782__INCLUDED_)
