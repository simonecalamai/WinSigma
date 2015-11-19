#if !defined(AFX_SERIESET_H__B32F2340_FD79_11D7_9A8F_00A0CCCE3AB1__INCLUDED_)
#define AFX_SERIESET_H__B32F2340_FD79_11D7_9A8F_00A0CCCE3AB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SerieSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSerieSet recordset

class CSerieSet : public CRecordset
{
public:
	CSerieSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSerieSet)

// Field/Param Data
	//{{AFX_FIELD(CSerieSet, CRecordset)
	long	m_Codice;
	long	m_Verbale;
	long	m_TipoCertificato;
	int		m_NumeroProvini;
	CTime	m_DataPrelievo;
	CTime	m_DataProva;
	BYTE	m_NuovoCertificato;
	long	m_Certificato;
	long	m_Servizio1;
	long	m_Servizio2;
	long	m_Servizio3;
	long	m_Servizio4;
	long	m_Servizio5;
	long	m_Servizio6;
	CString	m_Materiale;
	long	m_ServAggiungibile;
	long	m_ServAggiunto;
	CString	m_Sigla;
	CString	m_StrutturaPrelievo;
	double	m_Dimensione1;
	double	m_Dimensione2;
	double	m_Dimensione3;
	CString m_Osservazioni;
	CString m_Sperimentatore;
	CString m_Macchina;
	long	m_Marchio;
	double	m_Snervamento;
	int		m_TipoProva;
	CString	m_strDataND;
	CString m_IDMateriale;
	BYTE	m_Checked;
  long	m_Ordinamento;
	CString m_SiglaFornitore;
	CString m_VerbalePrelievo;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerieSet)
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

#endif // !defined(AFX_SERIESET_H__B32F2340_FD79_11D7_9A8F_00A0CCCE3AB1__INCLUDED_)
