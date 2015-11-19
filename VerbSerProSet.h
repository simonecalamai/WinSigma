#if !defined(AFX_VERBSERPROSET_H__E9BF8A5B_8039_48DF_994E_C3941B4568D2__INCLUDED_)
#define AFX_VERBSERPROSET_H__E9BF8A5B_8039_48DF_994E_C3941B4568D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VerbSerProSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVerbSerProSet recordset

class CVerbSerProSet : public CRecordset
{
public:
	CVerbSerProSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CVerbSerProSet)

// Field/Param Data
	//{{AFX_FIELD(CVerbSerProSet, CRecordset)
	long	m_Certificato;
	long	m_CodProvini;
	long	m_CodSerie;
	long	m_Serie;
	CTime	m_DataInsertProvini;
	long	m_CodVerbale;
	long	m_Verbale;
	BYTE	m_NuovoCertificato;
	long	m_ProgParziale;
	long	m_ProgTotale;
	long	m_TipoCertificato;
	CString m_Servizio;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVerbSerProSet)
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

#endif // !defined(AFX_VERBSERPROSET_H__E9BF8A5B_8039_48DF_994E_C3941B4568D2__INCLUDED_)
