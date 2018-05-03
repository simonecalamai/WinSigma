// TipiMaterialeSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "TipiMaterialeSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTipiMaterialeSet

IMPLEMENT_DYNAMIC(CTipiMaterialeSet, CRecordset)

CTipiMaterialeSet::CTipiMaterialeSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CTipiMaterialeSet)
	m_Codice = 0;
	m_Nome = _T("");
	m_Descrizione = _T("");
	m_TipoCertificato = 0;
	m_TipoCertificato2 = 0;
	m_TipoCertificato3 = 0;
	m_TipoCertificato4 = 0;
	m_TipoCertificato5 = 0;
	m_Snervamento = 0.0;
	m_ID = _T("");
	m_DiDefault = 0;
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CTipiMaterialeSet::GetDefaultConnect()
{
	return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CTipiMaterialeSet::GetDefaultSQL()
{
	return _T("[TIPI_MATERIALE]");
}

void CTipiMaterialeSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CTipiMaterialeSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Codice]"), m_Codice);
	RFX_Text(pFX, _T("[Nome]"), m_Nome);
	RFX_Text(pFX, _T("[Descrizione]"), m_Descrizione);
	RFX_Long(pFX, _T("[TipoCertificato]"), m_TipoCertificato);
	RFX_Long(pFX, _T("[TipoCertificato2]"), m_TipoCertificato2);
	RFX_Long(pFX, _T("[TipoCertificato3]"), m_TipoCertificato3);
	RFX_Long(pFX, _T("[TipoCertificato4]"), m_TipoCertificato4);
	RFX_Long(pFX, _T("[TipoCertificato5]"), m_TipoCertificato5);
	RFX_Double(pFX, _T("[Snervamento]"), m_Snervamento);
	RFX_Text(pFX, _T("[ID]"), m_ID);
	RFX_Byte(pFX, _T("[DiDefault]"), m_DiDefault);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTipiMaterialeSet diagnostics

#ifdef _DEBUG
void CTipiMaterialeSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CTipiMaterialeSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
