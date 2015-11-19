#if !defined(AFX_SERVIZIEROGATISET_H__9F4A3679_BAF8_48D2_9D3D_CEE0DCF1440F__INCLUDED_)
#define AFX_SERVIZIEROGATISET_H__9F4A3679_BAF8_48D2_9D3D_CEE0DCF1440F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServiziErogatiSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CServiziErogatiSet recordset

class CServiziErogatiSet : public CRecordset
{
public:
	CServiziErogatiSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CServiziErogatiSet)

// Field/Param Data
	//{{AFX_FIELD(CServiziErogatiSet, CRecordset)
	long		m_Codice;
	long		m_CodiceServizio;
	long		m_Verbale;
	long		m_Fattura;
	long		m_Serie;
	CString	m_Descrizione;
	CString	m_ID_Listino;
	double	m_Prezzo;
	double	m_Sconto;
	double	m_Quantita;
	CString	m_Nome;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServiziErogatiSet)
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

#endif // !defined(AFX_SERVIZIEROGATISET_H__9F4A3679_BAF8_48D2_9D3D_CEE0DCF1440F__INCLUDED_)
