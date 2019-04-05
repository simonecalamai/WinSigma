#if !defined(AFX_RIPARTIZIONEIMPONIBILEDLG_H__9DDDBD13_07FA_4D2B_9247_D38B88B2AD45__INCLUDED_)
#define AFX_RIPARTIZIONEIMPONIBILEDLG_H__9DDDBD13_07FA_4D2B_9247_D38B88B2AD45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RipartizioneImponibileDlg.h : header file
//

// definizioni
#define PC	0   // Prove di Carico
#define CB	1		// Conglomerati Bituminosi
#define I		2		// Inerti
#define MO	3		// Monitoraggi
#define LV	4		// Linee Vita
#define IM	5		// Indagini Murature
#define IC	6		// Indagini CLS
#define MM	7		// Materiali Metallici
#define V		8		// Varie
#define GEO	9		// Geotecnica
#define NCATEGORIE	10

#define FMT_RIP "PC=%d;CB=%d;I=%d;MO=%d;LV=%d;IM=%d;IC=%d;MM=%d;V=%d;GEO=%d"

/////////////////////////////////////////////////////////////////////////////
// CRipartizioneImponibileDlg dialog

class CRipartizioneImponibileDlg : public CDialog
{
// Construction
public:
	CRipartizioneImponibileDlg(CWnd* pParent = NULL);   // standard constructor
	int m_nTipoVerbale;
	CString m_strRipartizioneImponibile;
	double m_dImponibileScontato;
// Dialog Data
	//{{AFX_DATA(CRipartizioneImponibileDlg)
	enum { IDD = IDD_DIALOG_RIPARTIZIONE_IMPONIBILE };
	CEdit m_editPercProveCarico;
	CEdit	m_editPercConglomeratiBituminosi;
	CEdit m_editPercInerti;
	CEdit m_editPercMonitoraggi;
	CEdit m_editPercLineeVita;
	CEdit m_editPercIndaginiMurature;
	CEdit m_editPercIndaginiCLS;
	CEdit m_editPercMaterialiMetallici;
	CEdit m_editPercVarie;
	CEdit	m_editPercGeotecnica;
	CEdit	m_editPercResiduo;
	CString	m_strRagioneSociale;
	CString	m_strCodice;
	CString	m_strIndirizzo;
	CString	m_strImponibile;
	CString	m_strImponibileScontato;
	CString m_strTipoVerbale;
	double m_dProveCarico;
	double m_dConglomeratiBituminosi;
	double m_dInerti;
	double m_dMonitoraggi;
	double m_dLineeVita;
	double m_dIndaginiMurature;
	double m_dIndaginiCLS;
	double m_dMaterialiMetallici;
	double m_dVarie;
	double m_dGeotecnica;
	double m_dResiduo;
	int m_nPercProveCarico;
	int m_nPercConglomeratiBituminosi;
	int m_nPercInerti;
	int m_nPercMonitoraggi;
	int m_nPercLineeVita;
	int m_nPercIndaginiMurature;
	int m_nPercIndaginiCLS;
	int m_nPercMaterialiMetallici;
	int m_nPercVarie;
	int m_nPercGeotecnica;
	int m_nPercResiduo;
	//}}AFX_DATA

	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRipartizioneImponibileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRipartizioneImponibileDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnKillfocusEditPercProvedicarico();
	afx_msg void OnKillfocusEditPercConglomeratibituminosi();
	afx_msg void OnKillfocusEditPercGeotecnica();
	afx_msg void OnKillfocusEditPercIndaginicls();
	afx_msg void OnKillfocusEditPercIndaginimurature();
	afx_msg void OnKillfocusEditPercInerti();
	afx_msg void OnKillfocusEditPercLineevita();
	afx_msg void OnKillfocusEditPercMaterialimetallici();
	afx_msg void OnKillfocusEditPercMonitoraggi();
	afx_msg void OnKillfocusEditPercVarie();
	afx_msg void OnChangeEditPercConglomeratibituminosi();
	afx_msg void OnChangeEditPercGeotecnica();
	afx_msg void OnChangeEditPercIndaginicls();
	afx_msg void OnChangeEditPercIndaginimurature();
	afx_msg void OnChangeEditPercInerti();
	afx_msg void OnChangeEditPercLineevita();
	afx_msg void OnChangeEditPercMaterialimetallici();
	afx_msg void OnChangeEditPercMonitoraggi();
	afx_msg void OnChangeEditPercProvedicarico();
	afx_msg void OnChangeEditPercVarie();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int m_arPerc[NCATEGORIE];
	int m_nTotPerc;
	double m_arImpo[NCATEGORIE];
	double m_dTotImpo;
	int LoadRipartizione();
	void CalcRipartizione(int id);
	double Percent(double val, int perc);
	void CalcTotali();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIPARTIZIONEIMPONIBILEDLG_H__9DDDBD13_07FA_4D2B_9247_D38B88B2AD45__INCLUDED_)
