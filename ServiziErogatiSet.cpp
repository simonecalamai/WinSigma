// ServiziErogatiSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "ServiziErogatiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServiziErogatiSet

IMPLEMENT_DYNAMIC(CServiziErogatiSet, CRecordset)

CServiziErogatiSet::CServiziErogatiSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CServiziErogatiSet)
	m_Codice = 0;
	m_CodiceServizio = 0;
	m_Verbale = 0;
	m_Fattura = 0;
	m_Serie = 0;
	m_Descrizione = _T("");
	m_ID_Listino = _T("");
	m_Prezzo = 0.0;
	m_Sconto = 0.0;
	m_Quantita = 0.0;
	m_Nome = _T("");
	m_nFields = 11;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CServiziErogatiSet::GetDefaultConnect()
{
	return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CServiziErogatiSet::GetDefaultSQL()
{
	return _T("[SERVIZI_EROGATI]");
}

void CServiziErogatiSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CServiziErogatiSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Codice]"), m_Codice);
	RFX_Long(pFX, _T("[CodiceServizio]"), m_CodiceServizio);
	RFX_Long(pFX, _T("[Verbale]"), m_Verbale);
	RFX_Long(pFX, _T("[Fattura]"), m_Fattura);
	RFX_Long(pFX, _T("[Serie]"), m_Serie);
	RFX_Text(pFX, _T("[Descrizione]"), m_Descrizione);
	RFX_Text(pFX, _T("[ID_Listino]"), m_ID_Listino);
	RFX_Double(pFX, _T("[Prezzo]"), m_Prezzo);
	RFX_Double(pFX, _T("[Sconto]"), m_Sconto);
	RFX_Double(pFX, _T("[Quantita]"), m_Quantita);
	RFX_Text(pFX, _T("[Nome]"), m_Nome);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CServiziErogatiSet diagnostics

#ifdef _DEBUG
void CServiziErogatiSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CServiziErogatiSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
