// ProviniSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "ProviniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProviniSet

IMPLEMENT_DYNAMIC(CProviniSet, CRecordset)

CProviniSet::CProviniSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CProviniSet)
	m_Codice = 0;
	m_Serie = 0;
  m_DataInserimento = 0; 
	m_Servizio = _T("");
	m_InUso = _T("");
	m_Marchio = 0;
	m_RotoliCT = 0;
	m_Collaudatore = 0;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CProviniSet::GetDefaultConnect()
{
	return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CProviniSet::GetDefaultSQL()
{
	return _T(PROVINI);
}

void CProviniSet::DoFieldExchange(CFieldExchange* pFX)
{
	if (((CWinSigmaApp*)AfxGetApp())->m_bPrimaVolta)
    Spacciatore();

  //{{AFX_FIELD_MAP(CProviniSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Codice]"), m_Codice);
	RFX_Long(pFX, _T("[Serie]"), m_Serie);
	RFX_Date(pFX, _T("[DataInserimento]"), m_DataInserimento);
	RFX_Binary(pFX, _T("[Risultati]"), m_Risultati);
	RFX_Text(pFX, _T("[Servizio]"), m_Servizio);
	RFX_Text(pFX, _T("[InUso]"), m_InUso);
	RFX_Long(pFX, _T("[Marchio]"), m_Marchio);
	RFX_Byte(pFX, _T("[RotoliCT]"), m_RotoliCT);
	RFX_Long(pFX, _T("[Collaudatore]"), m_Collaudatore);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CProviniSet diagnostics

#ifdef _DEBUG
void CProviniSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CProviniSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
