#if !defined(AFX_TIPIPAGAMENTOSET_H__5EE13A21_3D26_11D8_B754_0080AD70B2EE__INCLUDED_)
#define AFX_TIPIPAGAMENTOSET_H__5EE13A21_3D26_11D8_B754_0080AD70B2EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TipiPagamentoSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTipiPagamentoSet recordset

class CTipiPagamentoSet : public CRecordset
{
public:
	CTipiPagamentoSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTipiPagamentoSet)

// Field/Param Data
	//{{AFX_FIELD(CTipiPagamentoSet, CRecordset)
	long	m_Codice;
	int		m_VecchioCod;
	CString	m_Nome;
	CString	m_Descrizione;
	int		m_Allineamento;
	int		m_NumRate;
	int		m_GiorniPrimaScad;
	CString	m_ABI;
	CString	m_Banca;
	CString	m_CAB;
	CString	m_CIN;
	CString	m_NumeroConto;
	CString	m_CodiceXML;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTipiPagamentoSet)
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

#endif // !defined(AFX_TIPIPAGAMENTOSET_H__5EE13A21_3D26_11D8_B754_0080AD70B2EE__INCLUDED_)
