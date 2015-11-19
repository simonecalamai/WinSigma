#if !defined(AFX_ESPORTAZIONECSVVIEW_H__997E6AB0_1379_42E8_BE02_D597A3C2D0CF__INCLUDED_)
#define AFX_ESPORTAZIONECSVVIEW_H__997E6AB0_1379_42E8_BE02_D597A3C2D0CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EsportazioneCSVView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEsportazioneCSVView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

struct dati 
{
	int nVersione;
	double	peso;
	double	lunghezza;
	double	snervamento;
	double	rottura;
	double	allungamento;
	double	aderenza;
	int			mandrino;
	byte		esito;
};


class CEsportazioneCSVView : public CFormView
{
protected:
	CEsportazioneCSVView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CEsportazioneCSVView)

// Form Data
private:
	void Query();
	CString m_CSVLine;
	dati * m_pDati;
public:
	//{{AFX_DATA(CEsportazioneCSVView)
	enum { IDD = IDD_FORM_ESPORTAZIONE_CSV };
	CDateTimeCtrl	m_ctrlA;
	CDateTimeCtrl	m_ctrlDa;
	CTime	m_tDa;
	CTime	m_tA;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEsportazioneCSVView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CEsportazioneCSVView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CEsportazioneCSVView)
	afx_msg void OnEsporta();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ESPORTAZIONECSVVIEW_H__997E6AB0_1379_42E8_BE02_D597A3C2D0CF__INCLUDED_)
