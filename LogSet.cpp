// LogSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "LogSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogSet

IMPLEMENT_DYNAMIC(CLogSet, CRecordset)

CLogSet::CLogSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CLogSet)
	m_LOG_ID = 0;
	m_LOG_EVENT_DESCRIPTION = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CLogSet::GetDefaultConnect()
{
#ifdef WINSIGMA2
	return _T("ODBC;DSN=WinSigma2");
#else
	return _T("ODBC;DSN=WinSigma");
#endif
}

CString CLogSet::GetDefaultSQL()
{
	return _T("[LOG]");
}

void CLogSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CLogSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[LOG_ID]"), m_LOG_ID);
	RFX_Text(pFX, _T("[LOG_EVENT_DESCRIPTION]"), m_LOG_EVENT_DESCRIPTION);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CLogSet diagnostics

#ifdef _DEBUG
void CLogSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CLogSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
