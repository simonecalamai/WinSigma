#if !defined(AFX_FATTURESET_H__30017FA0_1C22_11D8_9A8F_00A0CCCE3AB1__INCLUDED_)
#define AFX_FATTURESET_H__30017FA0_1C22_11D8_9A8F_00A0CCCE3AB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FattureSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFattureSet recordset

class CFattureSet : public CRecordset
{
public:
	CFattureSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CFattureSet)

// Field/Param Data
	//{{AFX_FIELD(CFattureSet, CRecordset)
	long	m_Codice;
	long	m_Intestatario;
	long	m_TipoPagamento;
	long	m_Numero;
	CTime	m_Data;
	CTime	m_Scadenza;
	CString	m_P_IVA;
	CString	m_CodiceFiscale;
	CString	m_RagioneSociale;
	CString	m_Indirizzo;
	CString	m_CAP;
	CString	m_Citta;
	CString	m_Provincia;
	CString	m_Banca;
	CString	m_ABI;
	CString	m_CAB;
	double	m_Sconto;
	CString	m_Note;
	CString	m_IDIntestatario;
	double	m_Aliquota;
	BYTE	m_Archiviata;
	double	m_Imponibile;
	double	m_Spese;
	CString	m_Pagamento;
	BYTE	m_TipoDocumento;
	CString	m_InUso;
	CString	m_ABIAppoggio;
	CString	m_BancaAppoggio;
	CString	m_CABAppoggio;
	CString	m_CINAppoggio;
	CString	m_ContoAppoggio;
  double	m_RitAcconto;
	BYTE m_PA;
	BYTE m_IVADifferita;
	BYTE m_Elett;
	CString	m_CodiceDestinatario;
	CString	m_PEC;
	CString m_CUP;
	CString m_CIG;
	CString m_OrdineAcquisto;
	CTime		m_DataOrdineAcquisto;
	CString m_Contratto;
	CTime		m_DataContratto;
	CString m_NumeroDDT;
	CTime		m_DataDDT;
	long m_CodiceXML;
	CString m_IBAN;
	CString m_IBANAppoggio;
	long m_CondizioniPagamento;
	CString m_RipartizioneImponibile;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFattureSet)
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

#endif // !defined(AFX_FATTURESET_H__30017FA0_1C22_11D8_9A8F_00A0CCCE3AB1__INCLUDED_)
