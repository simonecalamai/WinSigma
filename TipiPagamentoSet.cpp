// TipiPagamentoSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "TipiPagamentoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTipiPagamentoSet

IMPLEMENT_DYNAMIC(CTipiPagamentoSet, CRecordset)

CTipiPagamentoSet::CTipiPagamentoSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CTipiPagamentoSet)
	m_Codice = 0;
	m_VecchioCod = 0;
	m_Nome = _T("");
	m_Descrizione = _T("");
	m_Allineamento = 0;
	m_NumRate = 0;
	m_GiorniPrimaScad = 0;
	m_ABI = _T("");
	m_Banca = _T("");
	m_CAB = _T("");
	m_CIN = _T("");
	m_NumeroConto = _T("");
	m_CodiceXML = _T("");
	m_nFields = 13;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CTipiPagamentoSet::GetDefaultConnect()
{
  return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CTipiPagamentoSet::GetDefaultSQL()
{
	return _T("[TIPI_PAGAMENTO]");
}

void CTipiPagamentoSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CTipiPagamentoSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Codice]"), m_Codice);
	RFX_Int(pFX, _T("[VecchioCod]"), m_VecchioCod);
	RFX_Text(pFX, _T("[Nome]"), m_Nome);
	RFX_Text(pFX, _T("[Descrizione]"), m_Descrizione);
	RFX_Int(pFX, _T("[Allineamento]"), m_Allineamento);
	RFX_Int(pFX, _T("[NumRate]"), m_NumRate);
	RFX_Int(pFX, _T("[GiorniPrimaScad]"), m_GiorniPrimaScad);
	RFX_Text(pFX, _T("[ABI]"), m_ABI);
	RFX_Text(pFX, _T("[Banca]"), m_Banca);
	RFX_Text(pFX, _T("[CAB]"), m_CAB);
	RFX_Text(pFX, _T("[CIN]"), m_CIN);
	RFX_Text(pFX, _T("[NumeroConto]"), m_NumeroConto);
	RFX_Text(pFX, _T("[CodiceXML]"), m_CodiceXML);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTipiPagamentoSet diagnostics

#ifdef _DEBUG
void CTipiPagamentoSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CTipiPagamentoSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
