// LocalitaSet1.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "LocalitaSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLocalitaSet

IMPLEMENT_DYNAMIC(CLocalitaSet, CRecordset)

CLocalitaSet::CLocalitaSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CLocalitaSet)
	m_Codice = 0;
	m_Provincia = _T("");
	m_Localita = _T("");
	m_CAP = 0;
	m_Indirizzo = _T("");
	m_Tipologia = _T("");
	m_Note = _T("");
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CLocalitaSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=WinSigma");
}

CString CLocalitaSet::GetDefaultSQL()
{
	return _T("[LOCALITA]");
}

void CLocalitaSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CLocalitaSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Codice]"), m_Codice);
	RFX_Text(pFX, _T("[Provincia]"), m_Provincia);
	RFX_Text(pFX, _T("[Localita]"), m_Localita);
	RFX_Long(pFX, _T("[CAP]"), m_CAP);
	RFX_Text(pFX, _T("[Indirizzo]"), m_Indirizzo);
	RFX_Text(pFX, _T("[Tipologia]"), m_Tipologia);
	RFX_Text(pFX, _T("[Note]"), m_Note);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CLocalitaSet diagnostics

#ifdef _DEBUG
void CLocalitaSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CLocalitaSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
