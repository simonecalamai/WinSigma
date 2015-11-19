#if !defined(AFX_CERTIFICATISET_H__EB949F3D_B1D8_4EDD_96C2_CA54BD3FCD6B__INCLUDED_)
#define AFX_CERTIFICATISET_H__EB949F3D_B1D8_4EDD_96C2_CA54BD3FCD6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CertificatiSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCertificatiSet recordset

class CCertificatiSet : public CRecordset
{
public:
	CCertificatiSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCertificatiSet)

// Field/Param Data
	//{{AFX_FIELD(CCertificatiSet, CRecordset)
	long	m_Codice;
	long	m_Verbale;
	long	m_TipoCertificato;
	long	m_NumeroCertificato;
	long	m_Posizione;
	CString	m_Sperimentatore;
	CString m_Macchina;
	CTime	m_DataEmissione;
	CTime	m_DataStampa;
	CTime	m_DataProve;
	int		m_NumeroPagine;
	long	m_EmendaIl;
	long	m_EmendatoDa;
	BYTE  m_Aderenza;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCertificatiSet)
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

#endif // !defined(AFX_CERTIFICATISET_H__EB949F3D_B1D8_4EDD_96C2_CA54BD3FCD6B__INCLUDED_)
