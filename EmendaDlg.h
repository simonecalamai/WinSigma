#if !defined(AFX_EMENDADLG_H__881D2FE8_B1E5_4A79_86A1_21FBCB3115E4__INCLUDED_)
#define AFX_EMENDADLG_H__881D2FE8_B1E5_4A79_86A1_21FBCB3115E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EmendaDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEmendaDlg dialog

class CEmendaDlg : public CDialog
{
// Construction
public:
	CEmendaDlg(CWnd* pParent = NULL);   // standard constructor

  void SetIDCertificato(int ID)            {m_nIDCertificato = ID;};
  void SetDescrCertificato(CString Descr)  {m_strDescCertificato = Descr;};

  // ObbArray che contiene gli Emendamenti con i relativi ID delle Serie
  CObArray m_oaSerieEmend;
  
  // ID del Certificato
  int m_nIDCertificato;
  // Descrizione del certificacato
  CString m_strDescCertificato;
  // Contiene gli ID delle Serie da visualizzare nel Certificato
  CDWordArray m_waIDSerie;

// Dialog Data
	//{{AFX_DATA(CEmendaDlg)
	enum { IDD = IDD_DIALOG_EMENDAMENTI };
	CButton	m_bcElimina;
	CTreeCtrl	m_tcEmendamenti;
	CTreeCtrl	m_tcCertificato;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmendaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  // Contatore per gli Emendamenti
  int m_cntEmendamenti;

  // Inserisce le Serie nel certificato durate l'inizializzazione
  void GetSerie();
	// Generated message map functions
	//{{AFX_MSG(CEmendaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCrea();
	afx_msg void OnButtonElimina();
	afx_msg void OnButtonCtoe();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMENDADLG_H__881D2FE8_B1E5_4A79_86A1_21FBCB3115E4__INCLUDED_)
