// AziendeTurboSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "AziendeTurboSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAziendeTurboSet

IMPLEMENT_DYNAMIC(CAziendeTurboSet, CRecordset)

CAziendeTurboSet::CAziendeTurboSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CAziendeTurboSet)
	m_Codice = 0;
	m_RagioneSociale = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CAziendeTurboSet::GetDefaultConnect()
{
  return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CAziendeTurboSet::GetDefaultSQL()
{
	return _T("[AZIENDE]");
}

void CAziendeTurboSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAziendeTurboSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Codice]"), m_Codice);
	RFX_Text(pFX, _T("[RagioneSociale]"), m_RagioneSociale);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CAziendeTurboSet diagnostics

#ifdef _DEBUG
void CAziendeTurboSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CAziendeTurboSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
