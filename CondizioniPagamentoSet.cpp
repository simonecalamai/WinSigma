// CondizioniPagamentoSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "CondizioniPagamentoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCondizioniPagamentoSet

IMPLEMENT_DYNAMIC(CCondizioniPagamentoSet, CRecordset)

CCondizioniPagamentoSet::CCondizioniPagamentoSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CCondizioniPagamentoSet)
	m_Codice = 0;
	m_Descrizione = _T("");
	m_CodiceXML = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CCondizioniPagamentoSet::GetDefaultConnect()
{
  return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CCondizioniPagamentoSet::GetDefaultSQL()
{
	return _T("[CONDIZIONI_PAGAMENTO]");
}

void CCondizioniPagamentoSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CCondizioniPagamentoSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Codice]"), m_Codice);
	RFX_Text(pFX, _T("[Descrizione]"), m_Descrizione);
	RFX_Text(pFX, _T("[CodiceXML]"), m_CodiceXML);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCondizioniPagamentoSet diagnostics

#ifdef _DEBUG
void CCondizioniPagamentoSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCondizioniPagamentoSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
