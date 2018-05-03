#if !defined(AFX_SERVIZILISTINOSET_H__13889D7B_D031_41BA_B39D_2E7B6F138DE8__INCLUDED_)
#define AFX_SERVIZILISTINOSET_H__13889D7B_D031_41BA_B39D_2E7B6F138DE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServiziListinoSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CServiziListinoSet recordset
class CServiziListinoSet : public CRecordset
{
public:
	CServiziListinoSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CServiziListinoSet)

// Field/Param Data
	//{{AFX_FIELD(CServiziListinoSet, CRecordset)
	long	m_Codice;
	long	m_Categoria;
	CString	m_ID;
	CString	m_Descrizione;
	CString m_Nome;
	CString m_Norma;
	CString m_Riferimenti;
	double	m_Prezzo;
	double	m_Sconto;
	int		m_Campioni;
	long	m_Certificato;
	long	m_Certificato2;
	long	m_Certificato3;
	long	m_Certificato4;
	long	m_Certificato5;
	BYTE	m_PerSerie;
	int		m_Prove;
	int		m_Prove2;
	int		m_Prove3;
	int		m_Prove4;
	int		m_Prove5;
	BYTE	m_Emissione;
	BYTE  m_Aggiuntivo;
	BYTE	m_Concessione;
	int		m_ProviniPerSerie;
	CString	m_Commento;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServiziListinoSet)
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

#endif // !defined(AFX_SERVIZILISTINOSET_H__13889D7B_D031_41BA_B39D_2E7B6F138DE8__INCLUDED_)
