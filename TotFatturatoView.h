#if !defined(AFX_TOTFATTURATOVIEW_H__63AF103F_0A28_4699_AA56_5979B5D2E0D0__INCLUDED_)
#define AFX_TOTFATTURATOVIEW_H__63AF103F_0A28_4699_AA56_5979B5D2E0D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TotFatturatoView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTotFatturatoView dialog

class CTotFatturatoView : public CFormView
{
// Construction
protected:
	CTotFatturatoView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTotFatturatoView)

// Dialog Data
	//{{AFX_DATA(CTotFatturatoView)
	enum { IDD = IDD_FORM_TOTALI_FATTURATO };
	CComboBox	m_cmbMese;
	CComboBox	m_cmbAnno;
	CListCtrl	m_listTotFatturato;
	CButton	m_btnCalcola;
	CString	m_csAnno;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTotFatturatoView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWinSigmaApp* m_pApp;
	// Generated message map functions
	//{{AFX_MSG(CTotFatturatoView)
	afx_msg void OnButtonCalcola();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOTFATTURATOVIEW_H__63AF103F_0A28_4699_AA56_5979B5D2E0D0__INCLUDED_)
