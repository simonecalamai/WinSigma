// MarchiSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "MarchiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMarchiSet

IMPLEMENT_DYNAMIC(CMarchiSet, CRecordset)

CMarchiSet::CMarchiSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CMarchiSet)
	m_Codice = 0;
	m_Nome = _T("");
	m_Descrizione = _T("");
	m_Produttore = _T("");
	m_Stabilimento = _T("");
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CMarchiSet::GetDefaultConnect()
{
  return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CMarchiSet::GetDefaultSQL()
{
	return _T("[MARCHI]");
}

void CMarchiSet::DoFieldExchange(CFieldExchange* pFX)
{
	if (((CWinSigmaApp*)AfxGetApp())->m_bPrimaVolta)
    Spacciatore();

  //{{AFX_FIELD_MAP(CMarchiSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Codice]"), m_Codice);
	RFX_Text(pFX, _T("[Nome]"), m_Nome);
	RFX_Text(pFX, _T("[Descrizione]"), m_Descrizione);
	RFX_Text(pFX, _T("[Produttore]"), m_Produttore);
	RFX_Text(pFX, _T("[Stabilimento]"), m_Stabilimento);
	RFX_Binary(pFX, _T("[Immagine]"), m_Immagine, 80000);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CMarchiSet diagnostics

#ifdef _DEBUG
void CMarchiSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CMarchiSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
