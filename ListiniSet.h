#if !defined(AFX_LISTINISET_H__E1AD4750_0B48_44EF_8EE5_B87ABB5A33AF__INCLUDED_)
#define AFX_LISTINISET_H__E1AD4750_0B48_44EF_8EE5_B87ABB5A33AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListiniSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListiniSet recordset

class CListiniSet : public CRecordset
{
public:
	CListiniSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CListiniSet)

// Field/Param Data
	//{{AFX_FIELD(CListiniSet, CRecordset)
	long	m_Codice;
	long	m_Azienda;
	CString	m_Autore;
	CTime	m_Fine;
	CTime	m_Inizio;
	CString	m_Nome;
	BYTE  m_CertOgniSerie;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListiniSet)
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

#endif // !defined(AFX_LISTINISET_H__E1AD4750_0B48_44EF_8EE5_B87ABB5A33AF__INCLUDED_)
