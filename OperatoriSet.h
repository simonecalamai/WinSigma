#if !defined(AFX_OPERATORISET_H__31A6C09F_B4C3_44CA_AF24_EC4F12DD081B__INCLUDED_)
#define AFX_OPERATORISET_H__31A6C09F_B4C3_44CA_AF24_EC4F12DD081B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OperatoriSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COperatoriSet recordset

class COperatoriSet : public CRecordset
{
public:
	COperatoriSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(COperatoriSet)

// Field/Param Data
	//{{AFX_FIELD(COperatoriSet, CRecordset)
	long	m_Codice;
	CString	m_Nome;
	CString	m_Cognome;
	CString	m_Password;
	long	m_Privilegi;
	int   m_Sperimentatore;
	CString	m_Macchina;
	CTime	m_Fine;
	CTime	m_Inizio;
	int		m_Sospeso;
	BYTE	m_Responsabile;
	CString	m_Titolo;
	CString m_Sigla;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COperatoriSet)
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

#endif // !defined(AFX_OPERATORISET_H__31A6C09F_B4C3_44CA_AF24_EC4F12DD081B__INCLUDED_)
