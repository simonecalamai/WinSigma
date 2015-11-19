// CertificatiSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "CertificatiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCertificatiSet

IMPLEMENT_DYNAMIC(CCertificatiSet, CRecordset)

CCertificatiSet::CCertificatiSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CCertificatiSet)
	m_Codice = 0;
	m_Verbale = 0;
	m_TipoCertificato = 0;
	m_NumeroCertificato = 0;
	m_Posizione = 0;
	m_Sperimentatore =  _T("");
	m_Macchina =  _T("");
	m_DataEmissione = 0;
	m_DataStampa = 0;
	m_DataProve = 0;
	m_NumeroPagine = 0;
	m_EmendaIl = 0;
	m_EmendatoDa = 0;
	m_Aderenza = 0;
	m_nFields = 14;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CCertificatiSet::GetDefaultConnect()
{
	return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CCertificatiSet::GetDefaultSQL()
{
	return _T("[CERTIFICATI]");
}

void CCertificatiSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CCertificatiSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Codice]"), m_Codice);
	RFX_Long(pFX, _T("[Verbale]"), m_Verbale);
	RFX_Long(pFX, _T("[TipoCertificato]"), m_TipoCertificato);
	RFX_Long(pFX, _T("[NumeroCertificato]"), m_NumeroCertificato);
	RFX_Long(pFX, _T("[Posizione]"), m_Posizione);
	RFX_Text(pFX, _T("[Sperimentatore]"), m_Sperimentatore);
	RFX_Text(pFX, _T("[Macchina]"), m_Macchina);
	RFX_Date(pFX, _T("[DataEmissione]"), m_DataEmissione);
	RFX_Date(pFX, _T("[DataStampa]"), m_DataStampa);
	RFX_Date(pFX, _T("[DataProve]"), m_DataProve);
	RFX_Int(pFX, _T("[NumeroPagine]"), m_NumeroPagine);
	RFX_Long(pFX, _T("[EmendaIl]"), m_EmendaIl);
	RFX_Long(pFX, _T("[EmendatoDa]"), m_EmendatoDa);
	RFX_Byte(pFX, _T("[Aderenza]"), m_Aderenza);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCertificatiSet diagnostics

#ifdef _DEBUG
void CCertificatiSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCertificatiSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
