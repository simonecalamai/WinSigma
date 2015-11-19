#if !defined(AFX_AZSET_H__CE2A1180_3075_11D8_B754_00C026108782__INCLUDED_)
#define AFX_AZSET_H__CE2A1180_3075_11D8_B754_00C026108782__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AzSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAzSet recordset

class CAzSet : public CRecordset
{
public:
	CAzSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAzSet)

// Field/Param Data
	//{{AFX_FIELD(CAzSet, CRecordset)
	long	m_Codice;
	long	m_TipoPagamento;
	BYTE	m_Privato;
	CString	m_ID;
	CString	m_P_IVA;
	CString	m_CodiceFiscale;
	CString	m_RagioneSociale;
	CString	m_RagioneSociale_Sped;
	CString	m_Nome;
	CString	m_Cognome;
	CString	m_Indirizzo;
	CString	m_CAP;
	CString	m_Citta;
	CString	m_Provincia;
	CString	m_Indirizzo_Sped;
	CString	m_CAP_Sped;
	CString	m_Citta_Sped;
	CString	m_Provincia_Sped;
	CString	m_E_Mail;
	CString	m_Telefono;
	CString	m_Cellulare;
	CString	m_Fax;
	CString	m_Banca;
	CString	m_ABI;
	CString	m_CAB;
	CString	m_Note;
	double	m_Sconto;
	CTime	m_DataInserimento;
	CTime	m_DataUltimoRapporto;
	BYTE	m_IsImportante;
	BYTE	m_UsaTuttiListini;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAzSet)
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

#endif // !defined(AFX_AZSET_H__CE2A1180_3075_11D8_B754_00C026108782__INCLUDED_)
