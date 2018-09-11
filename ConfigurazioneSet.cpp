// ConfigurazioneSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "ConfigurazioneSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigurazioneSet

IMPLEMENT_DYNAMIC(CConfigurazioneSet, CRecordset)

CConfigurazioneSet::CConfigurazioneSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CConfigurazioneSet)
	m_Nome = _T("");
	m_Valore = _T("");
	m_Descrizione = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CConfigurazioneSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=WinSigma");
}

CString CConfigurazioneSet::GetDefaultSQL()
{
	return _T("[configurazione]");
}

void CConfigurazioneSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CConfigurazioneSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Nome]"), m_Nome, 50);
	RFX_Text(pFX, _T("[Valore]"), m_Valore, 500);
	RFX_Text(pFX, _T("[Descrizione]"), m_Descrizione, 200);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CConfigurazioneSet diagnostics

#ifdef _DEBUG
void CConfigurazioneSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CConfigurazioneSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
