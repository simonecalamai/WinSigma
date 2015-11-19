#if !defined(AFX_TIPIMATERIALESET_H__982C1F82_001B_4DF1_8795_93CA509B6B7D__INCLUDED_)
#define AFX_TIPIMATERIALESET_H__982C1F82_001B_4DF1_8795_93CA509B6B7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TipiMaterialeSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTipiMaterialeSet recordset

class CTipiMaterialeSet : public CRecordset
{
public:
	CTipiMaterialeSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTipiMaterialeSet)

// Field/Param Data
	//{{AFX_FIELD(CTipiMaterialeSet, CRecordset)
	long	m_Codice;
	CString	m_Nome;
	CString	m_Descrizione;
	long    m_TipoCertificato;
	long    m_TipoCertificato2;
	long    m_TipoCertificato3;
	long    m_TipoCertificato4;
	double	m_Snervamento;
	CString	m_ID;
	BYTE	m_DiDefault;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTipiMaterialeSet)
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

#endif // !defined(AFX_TIPIMATERIALESET_H__982C1F82_001B_4DF1_8795_93CA509B6B7D__INCLUDED_)
