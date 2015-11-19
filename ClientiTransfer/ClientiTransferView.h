// ClientiTransferView.h : interface of the CClientiTransferView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTITRANSFERVIEW_H__86068F0E_2FC1_11D8_B754_00C026108782__INCLUDED_)
#define AFX_CLIENTITRANSFERVIEW_H__86068F0E_2FC1_11D8_B754_00C026108782__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AzSet.h"
#include "Clienti_Old.h"
#include "TipoPagSet.h"

class CClientiTransferSet;

class CClientiTransferView : public COleDBRecordView
{
protected: // create from serialization only
	CClientiTransferView();
	DECLARE_DYNCREATE(CClientiTransferView);
	void Inserisci_Codice_Pagamento(int codpaga);

public:
	//{{AFX_DATA(CClientiTransferView)
	enum { IDD = IDD_CLIENTITRANSFER_FORM };
	CClientiTransferSet* m_pSet;
	CAzSet* m_pAziendeSet;
	CTipoPagSet* m_pTipoPagSet;
	CClienti_Old* m_pSet_Old;
	CString	m_csReport;
	//}}AFX_DATA

// Attributes
public:
	CClientiTransferDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientiTransferView)
	public:
	virtual CRowset* OnGetRowset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClientiTransferView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CClientiTransferView)
	afx_msg void OnButtonTrasferimento();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ClientiTransferView.cpp
inline CClientiTransferDoc* CClientiTransferView::GetDocument()
   { return (CClientiTransferDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTITRANSFERVIEW_H__86068F0E_2FC1_11D8_B754_00C026108782__INCLUDED_)
