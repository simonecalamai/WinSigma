#if !defined(AFX_TIPOPAGSET_H__5DD05D00_3D3F_11D8_B754_0080AD70B2EE__INCLUDED_)
#define AFX_TIPOPAGSET_H__5DD05D00_3D3F_11D8_B754_0080AD70B2EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TipoPagSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTipoPagSet recordset

class CTipoPagSet : public CRecordset
{
public:
	CTipoPagSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTipoPagSet)

// Field/Param Data
	//{{AFX_FIELD(CTipoPagSet, CRecordset)
	long	m_Codice;
	int		m_VecchioCod;
	CString	m_Nome;
	CString	m_Descrizione;
	int		m_Allineamento;
	int		m_NumRate;
	int		m_GiorniPrimaScad;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTipoPagSet)
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

#endif // !defined(AFX_TIPOPAGSET_H__5DD05D00_3D3F_11D8_B754_0080AD70B2EE__INCLUDED_)
