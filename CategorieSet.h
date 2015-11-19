#if !defined(AFX_CATEGORIESET_H__3604FB73_89D3_4CE4_8AAA_F9E10A31282B__INCLUDED_)
#define AFX_CATEGORIESET_H__3604FB73_89D3_4CE4_8AAA_F9E10A31282B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CategorieSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCategorieSet recordset

class CCategorieSet : public CRecordset
{
public:
	CCategorieSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCategorieSet)

// Field/Param Data
	//{{AFX_FIELD(CCategorieSet, CRecordset)
	long	m_Codice;
	long	m_Listino;
	CString	m_ID;
	CString	m_Descrizione;
	CString	m_Nome;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCategorieSet)
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

#endif // !defined(AFX_CATEGORIESET_H__3604FB73_89D3_4CE4_8AAA_F9E10A31282B__INCLUDED_)
