// CategorieSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "CategorieSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCategorieSet

IMPLEMENT_DYNAMIC(CCategorieSet, CRecordset)

CCategorieSet::CCategorieSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CCategorieSet)
	m_Codice = 0;
	m_Listino = 0;
	m_ID = _T("");
	m_Descrizione = _T("");
	m_Nome = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CCategorieSet::GetDefaultConnect()
{
  return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CCategorieSet::GetDefaultSQL()
{
	return _T("[CATEGORIE]");
}

void CCategorieSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CCategorieSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Codice]"), m_Codice);
	RFX_Long(pFX, _T("[Listino]"), m_Listino);
	RFX_Text(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Descrizione]"), m_Descrizione);
	RFX_Text(pFX, _T("[Nome]"), m_Nome);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCategorieSet diagnostics

#ifdef _DEBUG
void CCategorieSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCategorieSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
