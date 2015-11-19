#if !defined(AFX_TIPICERTIFICATOSET_H__EA4D5910_416A_4094_A7B2_6F76F700A4CF__INCLUDED_)
#define AFX_TIPICERTIFICATOSET_H__EA4D5910_416A_4094_A7B2_6F76F700A4CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TipiCertificatoSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTipiCertificatoSet recordset

class CTipiCertificatoSet : public CRecordset
{
public:
	CTipiCertificatoSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTipiCertificatoSet)

// Field/Param Data
	//{{AFX_FIELD(CTipiCertificatoSet, CRecordset)
	long	m_Codice;
	CString	m_Nome;
	CString	m_Descrizione;
	CString	m_LayoutStampa;
	CString	m_FinestraDialogo;
	CString	m_ProvaA;
	CString	m_ProvaB;
	CString	m_ProvaC;
	CString	m_Dimensione1;
	CString	m_Dimensione2;
	CString	m_Dimensione3;
	long	m_ValoreDim1;
	long	m_ValoreDim2;
	long	m_ValoreDim3;
	CString	m_LayoutStampaMinuta;
	CString	m_LayoutStampaVerbali;
	long	m_ProvXcertificato;
	long  m_Maturazione;
  long  m_Ordinamento;
	int   m_Variante;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTipiCertificatoSet)
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

#endif // !defined(AFX_TIPICERTIFICATOSET_H__EA4D5910_416A_4094_A7B2_6F76F700A4CF__INCLUDED_)
