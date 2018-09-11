#if !defined(AFX_CONFIGURAZIONESET_H__5C9FB75A_9B4C_4C71_B953_586B8897A92E__INCLUDED_)
#define AFX_CONFIGURAZIONESET_H__5C9FB75A_9B4C_4C71_B953_586B8897A92E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigurazioneSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfigurazioneSet recordset

class CConfigurazioneSet : public CRecordset
{
public:
	CConfigurazioneSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CConfigurazioneSet)

// Field/Param Data
	//{{AFX_FIELD(CConfigurazioneSet, CRecordset)
	CString	m_Nome;
	CString	m_Valore;
	CString	m_Descrizione;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigurazioneSet)
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

#endif // !defined(AFX_CONFIGURAZIONESET_H__5C9FB75A_9B4C_4C71_B953_586B8897A92E__INCLUDED_)
