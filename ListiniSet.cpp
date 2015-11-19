// ListiniSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "ListiniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListiniSet

IMPLEMENT_DYNAMIC(CListiniSet, CRecordset)

CListiniSet::CListiniSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CListiniSet)
	m_Codice = 0;
	m_Azienda = 0;
	m_Autore = _T("");
	m_Nome = _T("");
	m_nFields = 7;
	m_Inizio = 0;
	m_Fine = 0;
	m_CertOgniSerie = TRUE;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CListiniSet::GetDefaultConnect()
{
  return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CListiniSet::GetDefaultSQL()
{
	return _T("[LISTINI]");
}

void CListiniSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CListiniSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Codice]"), m_Codice);
	RFX_Long(pFX, _T("[Azienda]"), m_Azienda);
	RFX_Text(pFX, _T("[Autore]"), m_Autore);
	RFX_Date(pFX, _T("[Fine]"), m_Fine);
	RFX_Date(pFX, _T("[Inizio]"), m_Inizio);
	RFX_Text(pFX, _T("[Nome]"), m_Nome);
	RFX_Byte(pFX, _T("[CertOgniSerie]"), m_CertOgniSerie);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CListiniSet diagnostics

#ifdef _DEBUG
void CListiniSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CListiniSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
