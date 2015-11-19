#if !defined(AFX_LOGSET_H__F6988F4C_9275_493A_B77A_4C8FADBC8708__INCLUDED_)
#define AFX_LOGSET_H__F6988F4C_9275_493A_B77A_4C8FADBC8708__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogSet recordset

class CLogSet : public CRecordset
{
public:
	CLogSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CLogSet)

// Field/Param Data
	//{{AFX_FIELD(CLogSet, CRecordset)
	long	m_LOG_ID;
	CString	m_LOG_EVENT_DESCRIPTION;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogSet)
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

#endif // !defined(AFX_LOGSET_H__F6988F4C_9275_493A_B77A_4C8FADBC8708__INCLUDED_)
