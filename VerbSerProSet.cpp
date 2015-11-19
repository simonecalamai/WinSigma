// VerbSerProSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "VerbSerProSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVerbSerProSet

IMPLEMENT_DYNAMIC(CVerbSerProSet, CRecordset)

CVerbSerProSet::CVerbSerProSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CVerbSerProSet)
	m_Certificato				= 0;
	m_CodProvini				= 0;
	m_CodSerie					= 0;
	m_Serie							= 0;
	m_DataInsertProvini = 0;
	m_CodVerbale				= 0;
	m_Verbale						= 0;
	m_NuovoCertificato = 0;
	m_ProgParziale = 0;
	m_ProgTotale = 0;
	m_TipoCertificato = 0;
	m_Servizio = "";
	m_nFields = 12;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CVerbSerProSet::GetDefaultConnect()
{
	return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;}

CString CVerbSerProSet::GetDefaultSQL()
{
	return _T("[PROVINI],[SERIE],[VERBALI]");
}




void CVerbSerProSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CVerbSerProSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[SERIE].[Certificato]"), m_Certificato);
	RFX_Long(pFX, _T("[PROVINI].[Codice]"), m_CodProvini);
	RFX_Long(pFX, _T("[SERIE].[Codice]"), m_CodSerie);
	RFX_Long(pFX, _T("[PROVINI].[Serie]"), m_Serie);
	RFX_Date(pFX, _T("[PROVINI].[DataInserimento]"), m_DataInsertProvini);
	RFX_Long(pFX, _T("[VERBALI].[Codice]"), m_CodVerbale);
	RFX_Long(pFX, _T("[SERIE].[Verbale]"), m_Verbale);
	RFX_Byte(pFX, _T("[SERIE].[NuovoCertificato]"), m_NuovoCertificato);
	RFX_Long(pFX, _T("[VERBALI].[ProgressivoParziale]"), m_ProgParziale);
	RFX_Long(pFX, _T("[VERBALI].[ProgressivoTotale]"), m_ProgTotale);
	RFX_Long(pFX, _T("[SERIE].[TipoCertificato]"), m_TipoCertificato);
	RFX_Text(pFX, _T("[PROVINI].[Servizio]"), m_Servizio);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CVerbSerProSet diagnostics

#ifdef _DEBUG
void CVerbSerProSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CVerbSerProSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
