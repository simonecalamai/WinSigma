// ServiziListinoSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "ServiziListinoSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServiziListinoSet

IMPLEMENT_DYNAMIC(CServiziListinoSet, CRecordset)

CServiziListinoSet::CServiziListinoSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CServiziListinoSet)
	m_Codice			= 0;
	m_Categoria			= 0;
	m_ID				= _T("");
	m_Descrizione		= _T("");
	m_Nome				= _T("");
	m_Norma				= _T("");
	m_Riferimenti		= _T("");
	m_Prezzo			= 0.0;
	m_Sconto			= 0.0;
	m_Campioni			= 0;
	m_Certificato		= 0;
	m_Certificato2		= 0;
	m_Certificato3		= 0;
	m_Certificato4		= 0;
	m_Certificato5		= 0;
	m_PerSerie			= 0;
	m_Prove				= 0;
	m_Prove2			= 0;
	m_Prove3			= 0;
	m_Prove4			= 0;
	m_Prove5			= 0;
	m_Emissione			= 0;
	m_Concessione		= 0;
	m_ProviniPerSerie	= 0;
	m_Commento			= _T("");
	m_nFields = 26;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CServiziListinoSet::GetDefaultConnect()
{
  return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CServiziListinoSet::GetDefaultSQL()
{
	return _T("[SERVIZI_LISTINO]");
}

void CServiziListinoSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CServiziListinoSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Codice]"), m_Codice);
	RFX_Long(pFX, _T("[Categoria]"), m_Categoria);
	RFX_Text(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Descrizione]"), m_Descrizione);
	RFX_Text(pFX, _T("[Nome]"), m_Nome);
	RFX_Text(pFX, _T("[Norma]"), m_Norma);
	RFX_Text(pFX, _T("[Riferimenti]"), m_Riferimenti);
	RFX_Double(pFX, _T("[Prezzo]"), m_Prezzo);
	RFX_Double(pFX, _T("[Sconto]"), m_Sconto);
	RFX_Int(pFX, _T("[Campioni]"), m_Campioni);
	RFX_Long(pFX, _T("[Certificato]"), m_Certificato);
	RFX_Long(pFX, _T("[Certificato2]"), m_Certificato2);
	RFX_Long(pFX, _T("[Certificato3]"), m_Certificato3);
	RFX_Long(pFX, _T("[Certificato4]"), m_Certificato4);
	RFX_Long(pFX, _T("[Certificato5]"), m_Certificato5);
	RFX_Byte(pFX, _T("[PerSerie]"), m_PerSerie);
	RFX_Int(pFX, _T("[Prove]"), m_Prove);
	RFX_Int(pFX, _T("[Prove2]"), m_Prove2);
	RFX_Int(pFX, _T("[Prove3]"), m_Prove3);
	RFX_Int(pFX, _T("[Prove4]"), m_Prove4);
	RFX_Int(pFX, _T("[Prove5]"), m_Prove5);
	RFX_Byte(pFX, _T("[Emissione]"), m_Emissione);
	RFX_Byte(pFX, _T("[Aggiuntivo]"), m_Aggiuntivo);
	RFX_Byte(pFX, _T("[Concessione]"), m_Concessione);
	RFX_Int(pFX, _T("[ProviniPerSerie]"), m_ProviniPerSerie);
	RFX_Text(pFX, _T("[Commento]"), m_Commento);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CServiziListinoSet diagnostics

#ifdef _DEBUG
void CServiziListinoSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CServiziListinoSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
