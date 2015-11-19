#if !defined(AFX_MARCHISET_H__24A81CD7_CA5F_42A4_9E2F_4514DD0F175F__INCLUDED_)
#define AFX_MARCHISET_H__24A81CD7_CA5F_42A4_9E2F_4514DD0F175F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MarchiSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMarchiSet recordset

class CMarchiSet : public CRecordset
{
public:
	CMarchiSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CMarchiSet)

// Field/Param Data
	//{{AFX_FIELD(CMarchiSet, CRecordset)
	long	m_Codice;
	CString	m_Nome;
	CString	m_Descrizione;
	CString	m_Produttore;
	CString	m_Stabilimento;
	CByteArray	m_Immagine;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarchiSet)
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

#endif // !defined(AFX_MARCHISET_H__24A81CD7_CA5F_42A4_9E2F_4514DD0F175F__INCLUDED_)
