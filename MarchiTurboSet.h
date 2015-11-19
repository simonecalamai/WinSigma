#if !defined(AFX_MARCHITURBOSET_H__24FEF56C_D78B_4AA6_A09D_9DA3109AB46A__INCLUDED_)
#define AFX_MARCHITURBOSET_H__24FEF56C_D78B_4AA6_A09D_9DA3109AB46A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MarchiTurboSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMarchiTurboSet recordset

class CMarchiTurboSet : public CRecordset
{
public:
	CMarchiTurboSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CMarchiTurboSet)

// Field/Param Data
	//{{AFX_FIELD(CMarchiTurboSet, CRecordset)
	long	m_Codice;
	CString	m_Nome;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarchiTurboSet)
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

#endif // !defined(AFX_MARCHITURBOSET_H__24FEF56C_D78B_4AA6_A09D_9DA3109AB46A__INCLUDED_)
