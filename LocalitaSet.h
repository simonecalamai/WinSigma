#if !defined(AFX_LOCALITASET1_H__682D4BCA_F727_4D07_BD55_1316C802CC9F__INCLUDED_)
#define AFX_LOCALITASET1_H__682D4BCA_F727_4D07_BD55_1316C802CC9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LocalitaSet1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLocalitaSet recordset

class CLocalitaSet : public CRecordset
{
public:
	CLocalitaSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CLocalitaSet)

// Field/Param Data
	//{{AFX_FIELD(CLocalitaSet, CRecordset)
	long	m_Codice;
	CString	m_Provincia;
	CString	m_Localita;
	long	m_CAP;
	CString	m_Indirizzo;
	CString	m_Tipologia;
	CString	m_Note;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocalitaSet)
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

#endif // !defined(AFX_LOCALITASET1_H__682D4BCA_F727_4D07_BD55_1316C802CC9F__INCLUDED_)
