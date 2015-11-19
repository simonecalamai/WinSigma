// TipiCertificatoSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "TipiCertificatoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTipiCertificatoSet

IMPLEMENT_DYNAMIC(CTipiCertificatoSet, CRecordset)

CTipiCertificatoSet::CTipiCertificatoSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CTipiCertificatoSet)
	m_Codice = 0;
	m_Nome = _T("");
	m_Descrizione = _T("");
	m_LayoutStampa = _T("");
	m_ProvaA = _T("");
	m_ProvaB = _T("");
	m_ProvaC = _T("");
	m_Dimensione1 = _T("");
	m_Dimensione2 = _T("");
	m_Dimensione3 = _T("");
	m_ValoreDim1 = 0;
	m_ValoreDim2 = 0;
	m_ValoreDim3 = 0;
	m_LayoutStampaMinuta  = _T("");
	m_LayoutStampaVerbali = _T("");
	m_ProvXcertificato = 0;
	m_Maturazione = 0;
  m_Ordinamento = 0;
	m_Variante = 0;
	m_nFields = 20;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CTipiCertificatoSet::GetDefaultConnect()
{
	return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CTipiCertificatoSet::GetDefaultSQL()
{
	return _T("[TIPI_CERTIFICATO]");
}

void CTipiCertificatoSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CTipiCertificatoSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Codice]"), m_Codice);
	RFX_Text(pFX, _T("[Nome]"), m_Nome);
	RFX_Text(pFX, _T("[Descrizione]"), m_Descrizione);
	RFX_Text(pFX, _T("[LayoutStampa]"), m_LayoutStampa);
	RFX_Text(pFX, _T("[FinestraDialogo]"), m_FinestraDialogo);
	RFX_Text(pFX, _T("[ProvaA]"), m_ProvaA);
	RFX_Text(pFX, _T("[ProvaB]"), m_ProvaB);
	RFX_Text(pFX, _T("[ProvaC]"), m_ProvaC);
	RFX_Text(pFX, _T("[Dimensione1]"), m_Dimensione1);
	RFX_Text(pFX, _T("[Dimensione2]"), m_Dimensione2);
	RFX_Text(pFX, _T("[Dimensione3]"), m_Dimensione3);
	RFX_Long(pFX, _T("[ValoreDim1]"), m_ValoreDim1);
	RFX_Long(pFX, _T("[ValoreDim2]"), m_ValoreDim2);
	RFX_Long(pFX, _T("[ValoreDim3]"), m_ValoreDim3);
	RFX_Text(pFX, _T("[LayoutStampaMinuta]"), m_LayoutStampaMinuta);
	RFX_Text(pFX, _T("[LayoutStampaVerbali]"), m_LayoutStampaVerbali);
	RFX_Long(pFX, _T("[ProvXcertificato]"), m_ProvXcertificato);
	RFX_Long(pFX, _T("[Maturazione]"), m_Maturazione);
  RFX_Long(pFX, _T("[Ordinamento]"), m_Ordinamento);
	RFX_Int(pFX, _T("[Variante]"), m_Variante);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTipiCertificatoSet diagnostics

#ifdef _DEBUG
void CTipiCertificatoSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CTipiCertificatoSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
