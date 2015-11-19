// OperatoriSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "OperatoriSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COperatoriSet

IMPLEMENT_DYNAMIC(COperatoriSet, CRecordset)

COperatoriSet::COperatoriSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(COperatoriSet)
	m_Codice = 0;
	m_Nome = _T("");
	m_Cognome = _T("");
	m_Password = _T("");
	m_Privilegi = 0;
	m_Sperimentatore = 0;
	m_Macchina = _T("");
	m_Fine    = 0;
	m_Inizio  = 0;
	m_Sospeso = 0;
	m_Responsabile = 0;
	m_Titolo = _T("");
	m_nFields = 12;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString COperatoriSet::GetDefaultConnect()
{
  return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString COperatoriSet::GetDefaultSQL()
{
	return _T("[OPERATORI]");
}

void COperatoriSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(COperatoriSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Codice]"), m_Codice);
	RFX_Text(pFX, _T("[Nome]"), m_Nome);
	RFX_Text(pFX, _T("[Cognome]"), m_Cognome);
	RFX_Text(pFX, _T("[Password]"), m_Password);
	RFX_Long(pFX, _T("[Privilegi]"), m_Privilegi);
	RFX_Int(pFX, _T("[Sperimentatore]"), m_Sperimentatore);
	RFX_Text(pFX, _T("[Macchina]"), m_Macchina);
	RFX_Date(pFX, _T("[Fine]"), m_Fine);
	RFX_Date(pFX, _T("[Inizio]"), m_Inizio);
	RFX_Int(pFX, _T("[Sospeso]"), m_Sospeso);
	RFX_Byte(pFX, _T("[Responsabile]"), m_Responsabile);
	RFX_Text(pFX, _T("[Titolo]"), m_Titolo);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// COperatoriSet diagnostics

#ifdef _DEBUG
void COperatoriSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void COperatoriSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
