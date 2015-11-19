#if !defined(AFX_CLIENTI_OLD_H__6AD157A3_309E_11D8_B754_00C026108782__INCLUDED_)
#define AFX_CLIENTI_OLD_H__6AD157A3_309E_11D8_B754_00C026108782__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Clienti_Old.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClienti_Old recordset

class CClienti_Old : public CRecordset
{
public:
	CClienti_Old(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CClienti_Old)

// Field/Param Data
	//{{AFX_FIELD(CClienti_Old, CRecordset)
	CString	m_codice;
	CString	m_ragsociale;
	CString	m_estensione;
	CString	m_indirizzo;
	CString	m_descitta;
	CString	m_prov;
	CString	m_cap;
	CString	m_iva;
	CString	m_imporpaga;
	CString	m_totimpon;
	CString	m_totiva;
	CString	m_totbolli;
	CString	m_richied;
	CString	m_fatturato;
	CString	m_impresa;
	CString	m_codpaga;
	CString	m_bancaapp;
	CString	m_sconto;
	CString	m_genspe;
	CString	m_indspe;
	CString	m_descits;
	CString	m_provs;
	CString	m_caps;
	CString	m_ntelef;
	CString	m_tipocli;
	CString	m_riba;
	CString	m_codfis;
	CString	m_centro;
	CString	m_categ;
	CString	m_settore;
	CString	m_nfatture;
	CString	m_raggr_verb;
	CString	m_ninsoluti;
	CString	m_scoperto;
	CTime	m_data_ins;
	CString	m_abi;
	CString	m_cab;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClienti_Old)
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

#endif // !defined(AFX_CLIENTI_OLD_H__6AD157A3_309E_11D8_B754_00C026108782__INCLUDED_)
