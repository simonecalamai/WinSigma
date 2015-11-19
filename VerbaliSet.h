#if !defined(AFX_VERBALISET_H__DC719E41_E44C_11D7_9A8F_00A0CCCE3AB1__INCLUDED_)
#define AFX_VERBALISET_H__DC719E41_E44C_11D7_9A8F_00A0CCCE3AB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VerbaliSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVerbaliSet recordset

class CVerbaliSet : public CRecordset
{
public:
	CVerbaliSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CVerbaliSet)

// Field/Param Data
	//{{AFX_FIELD(CVerbaliSet, CRecordset)
	CString	m_Cantiere;
	long	m_Codice;
	CTime	m_DataAccettazione;
	CTime	m_DataChiusura;
	CTime	m_DataConsegna;
	CTime	m_DataPrimaStampa;
	CString	m_ProveRichieste;
	CString	m_Direttore;
	long	m_CodiceImpresa;
	long	m_ProgressivoParziale;
	long	m_ProgressivoTotale;
	CString	m_Proprietario;
	CString	m_Richiedente;
	BYTE	m_CertOgniSerie;
	BYTE	m_Spedizione;
	BYTE	m_Urgenza;
	CString	m_DescrizioneMateriale;
	CString	m_IndirizzoRichiedente;
	CString	m_IndirizzoCertificato;
	CString	m_IndirizzoFattura;
	long	m_CodiceAzCertificato;
	long	m_CodiceAzFattura;
	CString	m_NomeImpresa;
	CString	m_NomeAzCertificato;
	CString	m_NomeAzFattura;
	CString	m_IDImpresaRichiedente;
	CString	m_IDAzCertificato;
	CString	m_IDAzFattura;
	long  	m_TipoVerbale;
	CString	m_Destinatario;
	BYTE	m_LetteraIncarico;
	CString	m_NumLetteraIncarico;
	CString	m_NoteSpedizione;
	CString	m_P_IVA;
	CString	m_Pagamento;
	long	m_ListinoGenerale;
	long	m_ListinoParticolare;
	BYTE	m_LungaScadenza;
	CString	m_Operatore;
	BYTE	m_DomandaSottoscritta;
	CString	m_OraConsegna;
	long	m_NumeroFattura;
	BYTE	m_InFatturazione;
	CString	m_InUso;
	BYTE	m_Annullato;
  CString	m_CodFiscale;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVerbaliSet)
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

#endif // !defined(AFX_VERBALISET_H__DC719E41_E44C_11D7_9A8F_00A0CCCE3AB1__INCLUDED_)
