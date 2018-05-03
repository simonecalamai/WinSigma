// CategorieServiziSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "CategorieServiziSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCategorieServiziSet

IMPLEMENT_DYNAMIC(CCategorieServiziSet, CRecordset)

CCategorieServiziSet::CCategorieServiziSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CCategorieServiziSet)
	m_CodiceCategoria = 0;
	m_Listino = 0;
	m_Codice = 0;
	m_Certificato = 0;
  m_Certificato2 = 0;
  m_Certificato3 = 0;
  m_Certificato4 = 0;
  m_Certificato5 = 0;
	m_Categoria = 0;
	m_ID = _T("");
	m_Descrizione = _T("");
	m_Emissione = 0;
	m_Campioni = 0;
	m_Prove = 0;
  m_Prove2 = 0;
  m_Prove3 = 0;
  m_Prove4 = 0;
  m_Prove5 = 0;
	m_PerSerie = 0;
	m_Prezzo = 0.0;
	m_Sconto = 0.0;
	m_Nome = _T("");
	m_Aggiuntivo = 0;
	m_IDCategorie = _T("");
	m_Concessione = 0;
	m_nFields = 25;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CCategorieServiziSet::GetDefaultConnect()
{
  return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CCategorieServiziSet::GetDefaultSQL()
{
  CString str;
  str.Format("%s,%s", CATEGORIE, SERVIZI_LISTINO);
	return _T(str);
}

void CCategorieServiziSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CCategorieServiziSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[CATEGORIE].[Codice]"), m_CodiceCategoria);
	RFX_Long(pFX, _T("[Listino]"), m_Listino);
	RFX_Long(pFX, _T("[SERVIZI_LISTINO].[Codice]"), m_Codice);
	RFX_Long(pFX, _T("[Certificato]"), m_Certificato);
  RFX_Long(pFX, _T("[Certificato2]"), m_Certificato2);
	RFX_Long(pFX, _T("[Certificato3]"), m_Certificato3);
  RFX_Long(pFX, _T("[Certificato4]"), m_Certificato4);
  RFX_Long(pFX, _T("[Certificato5]"), m_Certificato5);
	RFX_Long(pFX, _T("[Categoria]"), m_Categoria);
	RFX_Text(pFX, _T("[SERVIZI_LISTINO].[ID]"), m_ID);
	RFX_Text(pFX, _T("[SERVIZI_LISTINO].[Descrizione]"), m_Descrizione);
	RFX_Byte(pFX, _T("[Emissione]"), m_Emissione);
	RFX_Int(pFX, _T("[Campioni]"), m_Campioni);
	RFX_Int(pFX, _T("[Prove]"), m_Prove);
  RFX_Int(pFX, _T("[Prove2]"), m_Prove2);
  RFX_Int(pFX, _T("[Prove3]"), m_Prove3);
  RFX_Int(pFX, _T("[Prove4]"), m_Prove4);
  RFX_Int(pFX, _T("[Prove5]"), m_Prove5);
	RFX_Byte(pFX, _T("[PerSerie]"), m_PerSerie);
	RFX_Double(pFX, _T("[Prezzo]"), m_Prezzo);
	RFX_Double(pFX, _T("[Sconto]"), m_Sconto);
	RFX_Text(pFX, _T("[SERVIZI_LISTINO].[Nome]"), m_Nome);
	RFX_Byte(pFX, _T("[Aggiuntivo]"), m_Aggiuntivo);
	RFX_Text(pFX, _T("[CATEGORIE].[ID]"), m_IDCategorie);
	RFX_Byte(pFX, _T("[Concessione]"), m_Concessione);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCategorieServiziSet diagnostics

#ifdef _DEBUG
void CCategorieServiziSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCategorieServiziSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
