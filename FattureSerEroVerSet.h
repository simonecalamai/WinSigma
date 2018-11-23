#if !defined(AFX_FATTURESEREROVERSET_H__D0DFC336_108C_4EB4_93CE_B0E37FE3B06F__INCLUDED_)
#define AFX_FATTURESEREROVERSET_H__D0DFC336_108C_4EB4_93CE_B0E37FE3B06F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FattureSerEroVerSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFattureSerEroVerSet recordset

class CFattureSerEroVerSet : public CRecordset
{
public:
	CFattureSerEroVerSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CFattureSerEroVerSet)

// Field/Param Data
	//{{AFX_FIELD(CFattureSerEroVerSet, CRecordset)
	long	m_Codice;
	long	m_Intestatario;
	long	m_TipoPagamento;
	long	m_Numero;
	CTime	m_Data;
	CTime	m_Scadenza;
	CString	m_P_IVA;
	CString	m_CodiceFiscale;
	CString	m_RagioneSociale;
	CString	m_IDIntestario;
	CString	m_Indirizzo;
	CString	m_CAP;
	CString	m_Citta;
	CString	m_Provincia;
	CString	m_Banca;
	CString	m_ABI;
	CString	m_CAB;
	double	m_Sconto;
	double	m_AliquotaIVA;
	double	m_Spese;
	double	m_Imponibile;
	CString	m_Pagamento;
	BYTE	m_TipoDocumento;
	CString	m_CINAppoggio;
	CString	m_ContoAppoggio;
	double	m_RitenutaAcconto;
	long	m_CodiceServizio;
	long	m_Verbale;
	long	m_Fattura;
	long	m_Serie;
	double	m_Quantita;
	double	m_Prezzo;
	long	m_TipoVerbale;
	BYTE	m_Annullato;
	double	m_ScontoSevizio;
	long m_VuoiUrgenza;
	BYTE m_PA;
	CString	m_CodiceDestinatario;
	CString m_PEC;
	CString m_IBAN;
	CString m_IBANAppoggio;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFattureSerEroVerSet)
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

#endif // !defined(AFX_FATTURESEREROVERSET_H__D0DFC336_108C_4EB4_93CE_B0E37FE3B06F__INCLUDED_)
