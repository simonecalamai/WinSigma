#if !defined(AFX_CATEGORIESERVIZISET_H__B5CFFFA1_1E64_11D8_9A8F_00A0CCCE3AB1__INCLUDED_)
#define AFX_CATEGORIESERVIZISET_H__B5CFFFA1_1E64_11D8_9A8F_00A0CCCE3AB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CategorieServiziSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCategorieServiziSet recordset

class CCategorieServiziSet : public CRecordset
{
public:
	CCategorieServiziSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCategorieServiziSet)

// Field/Param Data
	//{{AFX_FIELD(CCategorieServiziSet, CRecordset)
	long  	m_CodiceCategoria;
	long	  m_Listino;
	long	  m_Codice;
	long	  m_Certificato;
  long	  m_Certificato2;
  long	  m_Certificato3;
  long	  m_Certificato4;
	long	  m_Categoria;
	CString	m_ID;
	CString	m_Descrizione;
	BYTE  	m_Emissione;
	int	  	m_Campioni;
	int	  	m_Prove;
  int	  	m_Prove2;
	BYTE  	m_PerSerie;
	double	m_Prezzo;
	double	m_Sconto;
	CString	m_Nome;
	BYTE	m_Aggiuntivo;
	CString	m_IDCategorie;
	BYTE	m_Concessione;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCategorieServiziSet)
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

#endif // !defined(AFX_CATEGORIESERVIZISET_H__B5CFFFA1_1E64_11D8_9A8F_00A0CCCE3AB1__INCLUDED_)
