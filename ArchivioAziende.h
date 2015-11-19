#if !defined(AFX_ARCHIVIOAZIENDE_H__4626D860_30BE_11D8_B754_00C026108782__INCLUDED_)
#define AFX_ARCHIVIOAZIENDE_H__4626D860_30BE_11D8_B754_00C026108782__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ArchivioAziende.h : header file
//

#include "AziendeOldSet.h"
#include "DatiAziende.h"

/////////////////////////////////////////////////////////////////////////////
// CArchivioAziende dialog

class CArchivioAziendeDlg : public CDialog
{
// Construction
public:
	CArchivioAziendeDlg(CDatiAziende* dati_aziende, CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CArchivioAziendeDlg)
	enum { IDD = IDD_DIALOG_ARCHIVIO_AZIENDE };
	CListCtrl	m_Lista_Aziende;
	CString	m_csIndirizzo;
	CString	m_csPartita_IVA;
	CString	m_csRagione_Sociale;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArchivioAziendeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CAziendeOldSet* aziende_old;

	// Generated message map functions
	//{{AFX_MSG(CArchivioAziendeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnDblclkListAziendeVecchie(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonRicerca();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Popola_Lista();
	void Query();
	bool Congruenza_Dati_Ricerca(CString* msg);
	CDatiAziende* m_pDati_Aziende;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARCHIVIOAZIENDE_H__4626D860_30BE_11D8_B754_00C026108782__INCLUDED_)
