// MarchiTurboSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "MarchiTurboSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMarchiTurboSet

IMPLEMENT_DYNAMIC(CMarchiTurboSet, CRecordset)

CMarchiTurboSet::CMarchiTurboSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CMarchiTurboSet)
	m_Codice = 0;
	m_Nome = _T("");
	m_nFields =2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CMarchiTurboSet::GetDefaultConnect()
{
  return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CMarchiTurboSet::GetDefaultSQL()
{
	return _T("[MARCHI]");
}

void CMarchiTurboSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CMarchiTurboSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Codice]"), m_Codice);
	RFX_Text(pFX, _T("[Nome]"), m_Nome);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CMarchiTurboSet diagnostics

#ifdef _DEBUG
void CMarchiTurboSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CMarchiTurboSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
