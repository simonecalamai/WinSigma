#if !defined(AFX_AZIENDETURBOSET_H__0742A3E2_1C7C_47DF_88C1_EE1F58583780__INCLUDED_)
#define AFX_AZIENDETURBOSET_H__0742A3E2_1C7C_47DF_88C1_EE1F58583780__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AziendeTurboSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAziendeTurboSet recordset

class CAziendeTurboSet : public CRecordset
{
public:
	CAziendeTurboSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAziendeTurboSet)

// Field/Param Data
	//{{AFX_FIELD(CAziendeTurboSet, CRecordset)
	long	m_Codice;
	CString	m_RagioneSociale;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAziendeTurboSet)
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

#endif // !defined(AFX_AZIENDETURBOSET_H__0742A3E2_1C7C_47DF_88C1_EE1F58583780__INCLUDED_)
