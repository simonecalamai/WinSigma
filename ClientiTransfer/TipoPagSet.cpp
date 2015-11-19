// TipoPagSet.cpp : implementation file
//

#include "stdafx.h"
#include "ClientiTransfer.h"
#include "TipoPagSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTipoPagSet

IMPLEMENT_DYNAMIC(CTipoPagSet, CRecordset)

CTipoPagSet::CTipoPagSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CTipoPagSet)
	m_Codice = 0;
	m_VecchioCod = 0;
	m_Nome = _T("");
	m_Descrizione = _T("");
	m_Allineamento = 0;
	m_NumRate = 0;
	m_GiorniPrimaScad = 0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CTipoPagSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=WinSigma");
}

CString CTipoPagSet::GetDefaultSQL()
{
	return _T("[tipi_pagamento]");
}

void CTipoPagSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CTipoPagSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Codice]"), m_Codice);
	RFX_Int(pFX, _T("[VecchioCod]"), m_VecchioCod);
	RFX_Text(pFX, _T("[Nome]"), m_Nome);
	RFX_Text(pFX, _T("[Descrizione]"), m_Descrizione);
	RFX_Int(pFX, _T("[Allineamento]"), m_Allineamento);
	RFX_Int(pFX, _T("[NumRate]"), m_NumRate);
	RFX_Int(pFX, _T("[GiorniPrimaScad]"), m_GiorniPrimaScad);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CTipoPagSet diagnostics

#ifdef _DEBUG
void CTipoPagSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CTipoPagSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
