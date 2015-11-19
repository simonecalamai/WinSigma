#if !defined(AFX_PROVINISET_H__07BEB0C0_009E_11D8_9A8F_00A0CCCE3AB1__INCLUDED_)
#define AFX_PROVINISET_H__07BEB0C0_009E_11D8_9A8F_00A0CCCE3AB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProviniSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProviniSet recordset

class CProviniSet : public CRecordset
{
public:
	CProviniSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CProviniSet)

// Field/Param Data
	//{{AFX_FIELD(CProviniSet, CRecordset)
	long	m_Codice;
	long	m_Serie;
	CTime	m_DataInserimento;
	CByteArray	m_Risultati;
	CString	m_Servizio;
	CString m_InUso;
	long	m_Marchio;
	long	m_Collaudatore;
	BYTE m_RotoliCT;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProviniSet)
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

#endif // !defined(AFX_PROVINISET_H__07BEB0C0_009E_11D8_9A8F_00A0CCCE3AB1__INCLUDED_)
