#if !defined(AFX_SERIEPROVINISET_H__8FA1F10D_74C2_46A3_BF00_E38E96416A19__INCLUDED_)
#define AFX_SERIEPROVINISET_H__8FA1F10D_74C2_46A3_BF00_E38E96416A19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SerieProviniSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSerieProviniSet recordset

class CSerieProviniSet : public CRecordset
{
public:
	CSerieProviniSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSerieProviniSet)

// Field/Param Data
	//{{AFX_FIELD(CSerieProviniSet, CRecordset)
	long	m_CodiceSerie;
	long	m_Verbale;
	long	m_TipoCertificato;
	int		m_NumeroProvini;
	BYTE	m_NuovoCertificato;
	long	m_Certificato;
	CTime	m_DataPrelievo;
	CTime m_DataProva;
	CString	m_StrutturaPrelievo;
	CString	m_Sigla;
	long	m_Servizio1;
	long	m_Servizio2;
	long	m_Servizio3;
	long	m_Servizio4;
	long	m_Servizio5;
	long	m_Servizio6;
	long	m_ServAggiungibile;
	long	m_ServAggiunto;
	long	m_CodiceProvino;
	CTime	m_DataInserimento;
	CString	m_InUso;
	CByteArray	m_Risultati;
	long	m_Serie;
	CString  m_Materiale;
	CString m_Osservazioni;
	CString m_Sperimentatore;
	CString m_Macchina;
	long		m_MarchioSerie;
	long		m_Marchio;
	double	m_Snervamento;
	double	m_Dimensione1;
	double	m_Dimensione2;
	double	m_Dimensione3;
	int			m_TipoProva;
	CString	m_strDataND;
	BYTE	m_Checked;
	CString	m_VerbalePrelievo;
	CString m_SiglaFornitore;
	BYTE m_RotoliCT;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerieProviniSet)
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

#endif // !defined(AFX_SERIEPROVINISET_H__8FA1F10D_74C2_46A3_BF00_E38E96416A19__INCLUDED_)
