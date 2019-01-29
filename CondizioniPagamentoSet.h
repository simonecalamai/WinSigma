#if !defined(AFX_CONDIZIONIPAGAMENTOSET_H__608C8098_8F49_4067_8D48_D618AD6F3272__INCLUDED_)
#define AFX_CONDIZIONIPAGAMENTOSET_H__608C8098_8F49_4067_8D48_D618AD6F3272__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CondizioniPagamentoSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCondizioniPagamentoSet recordset

class CCondizioniPagamentoSet : public CRecordset
{
public:
	CCondizioniPagamentoSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCondizioniPagamentoSet)

// Field/Param Data
	//{{AFX_FIELD(CCondizioniPagamentoSet, CRecordset)
	long	m_Codice;
	CString	m_Descrizione;
	CString	m_CodiceXML;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCondizioniPagamentoSet)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONDIZIONIPAGAMENTOSET_H__608C8098_8F49_4067_8D48_D618AD6F3272__INCLUDED_)
