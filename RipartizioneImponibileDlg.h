#if !defined(AFX_RIPARTIZIONEIMPONIBILEDLG_H__9DDDBD13_07FA_4D2B_9247_D38B88B2AD45__INCLUDED_)
#define AFX_RIPARTIZIONEIMPONIBILEDLG_H__9DDDBD13_07FA_4D2B_9247_D38B88B2AD45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RipartizioneImponibileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRipartizioneImponibileDlg dialog

class CRipartizioneImponibileDlg : public CDialog
{
// Construction
public:
	CRipartizioneImponibileDlg(CWnd* pParent = NULL);   // standard constructor
	int m_nTipoVerbale;
	CString m_strRipartizioneImponibile;
// Dialog Data
	//{{AFX_DATA(CRipartizioneImponibileDlg)
	enum { IDD = IDD_DIALOG_RIPARTIZIONE_IMPONIBILE };
	CString	m_strRagioneSociale;
	CString	m_strCodice;
	CString	m_strIndirizzo;
	CString	m_strImponibile;
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
	double m_dPercProveCarico;
	double m_dPercConglomeratiBituminosi;
	double m_dPercInerti;
	double m_dPercMonitoraggi;
	double m_dPercLineeVita;
	double m_dPercIndaginiMurature;
	double m_dPercIndaginiCLS;
	double m_dPercMaterialiMetallici;
	double m_dPercVarie;
	double m_dPercGeotecnica;
		// NOTE: the ClassWizard will add data members here
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIPARTIZIONEIMPONIBILEDLG_H__9DDDBD13_07FA_4D2B_9247_D38B88B2AD45__INCLUDED_)
