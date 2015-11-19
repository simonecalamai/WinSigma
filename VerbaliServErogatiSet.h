#if !defined(AFX_VERBALISERVEROGATISET_H__B5CFFFA2_1E64_11D8_9A8F_00A0CCCE3AB1__INCLUDED_)
#define AFX_VERBALISERVEROGATISET_H__B5CFFFA2_1E64_11D8_9A8F_00A0CCCE3AB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VerbaliServErogatiSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVerbaliServErogatiSet recordset

class CVerbaliServErogatiSet : public CRecordset
{
public:
	CVerbaliServErogatiSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CVerbaliServErogatiSet)

// Field/Param Data
	//{{AFX_FIELD(CVerbaliServErogatiSet, CRecordset)
	long	m_CodiceServizioErogato;
	long	m_CodiceServizio;
	long	m_Verbale;
	double	m_Prezzo;
	double	m_Sconto;
	long	m_CodiceVerbale;
	long	m_IntestatarioFattura;
	long	m_ListinoGenerale;
	long	m_ListinoParticolare;
	CString	m_P_IVA;
	long	m_ProgressivoTotale;
	long	m_ProgressivoParziale;
	CTime	m_DataAccettazione;
	CTime	m_DataPrimaStampa;
	CTime	m_DataConsegna;
	CTime	m_DataChiusura;
	BYTE	m_VuoiUrgenza;
	BYTE	m_VuoiSpedizione;
	CString	m_Descrizione;
	long	m_Serie;
	long	m_TipoVerbale;
	BYTE	m_LungaScadenza;
	CString	m_IDListino;
	CString	m_Cantiere;
	long	m_NumFatturaServizio;
	long	m_NumFatturaVerbale;
	BYTE	m_InFatturazione;
	double	m_Quantita;
	CString	m_Nome;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVerbaliServErogatiSet)
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

#endif // !defined(AFX_VERBALISERVEROGATISET_H__B5CFFFA2_1E64_11D8_9A8F_00A0CCCE3AB1__INCLUDED_)
