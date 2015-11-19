#if !defined(AFX_CERTIFICATIVERBALISET_H__33B90C50_D13B_43FA_9BFA_59FB37B3F2F2__INCLUDED_)
#define AFX_CERTIFICATIVERBALISET_H__33B90C50_D13B_43FA_9BFA_59FB37B3F2F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CertificatiVerbaliSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCertificatiVerbaliSet recordset

class CCertificatiVerbaliSet : public CRecordset
{
public:
	CCertificatiVerbaliSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CCertificatiVerbaliSet)

// Field/Param Data
	//{{AFX_FIELD(CCertificatiVerbaliSet, CRecordset)
	long	m_CodiceCertificato;
	long  m_CodiceVerbale;
	long	m_Verbale;
	long	m_TipoCertificato;
	long	m_NumeroCertificato;
	long	m_Posizione;
	CTime	m_DataEmissione;
	CTime	m_DataStampa;
	CString	m_Cantiere;
	CTime	m_DataAccettazione;
	CTime	m_DataChiusura;
	CTime	m_DataConsegna;
	CTime	m_DataPrimaStampa;
	CTime m_DataProve;
	CString	m_DescrizioneMateriale;
	CString	m_DescrizioneProveRichieste;
	CString	m_DirettoreLavori;
	CString	m_IDImpresaRichiedente;
	CString	m_IDIntestatarioCertificato;
	CString	m_IDIntestatarioFattura;
	long	m_ImpresaRichiedente;
	CString	m_IndirizzoImpresaRichiedente;
	CString	m_IndirizzoIntCertificato;
	CString	m_IndirizzoIntFattura;
	CString	m_Destinatario;
	long	m_IntestatarioCertificato;
	long	m_IntestatarioFattura;
	BYTE	m_LetteraIncarico;
	CString	m_NomeImpresaRichiedente;
	CString	m_NomeIntestatarioCertificato;
	CString	m_NomeIntestatarioFattura;
	CString	m_NumLetteraIncarico;
	long	m_ProgressivoParziale;
	long	m_ProgressivoTotale;
	CString	m_Proprietario;
	long	m_TipoVerbale;
	BYTE	m_VuoiSpedizione;
	BYTE	m_VuoiUrgenza;
	BYTE	m_Sottoscritta;
	BYTE	m_InFatturazione;
	long	m_ListinoGenerale;
	long	m_ListinoParticolare;
	BYTE	m_LungaScadenza;
	CString	m_NoteSpedizione;
	CString	m_Operatore;
	CString	m_OraConsegna;
	CString	m_P_IVA;
	CString	m_Richiedente;
	int		m_NumeroPagine;
	long	m_EmendatoDa;
	long	m_EmendaIl;
	long	m_Fattura;
	BYTE  m_Aderenza;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCertificatiVerbaliSet)
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

#endif // !defined(AFX_CERTIFICATIVERBALISET_H__33B90C50_D13B_43FA_9BFA_59FB37B3F2F2__INCLUDED_)
