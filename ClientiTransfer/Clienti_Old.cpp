// Clienti_Old.cpp : implementation file
//

#include "stdafx.h"
#include "ClientiTransfer.h"
#include "Clienti_Old.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClienti_Old

IMPLEMENT_DYNAMIC(CClienti_Old, CRecordset)

CClienti_Old::CClienti_Old(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CClienti_Old)
	m_codice = _T("");
	m_ragsociale = _T("");
	m_estensione = _T("");
	m_indirizzo = _T("");
	m_descitta = _T("");
	m_prov = _T("");
	m_cap = _T("");
	m_iva = _T("");
	m_imporpaga = _T("");
	m_totimpon = _T("");
	m_totiva = _T("");
	m_totbolli = _T("");
	m_richied = _T("");
	m_fatturato = _T("");
	m_impresa = _T("");
	m_codpaga = _T("");
	m_bancaapp = _T("");
	m_sconto = _T("");
	m_genspe = _T("");
	m_indspe = _T("");
	m_descits = _T("");
	m_provs = _T("");
	m_caps = _T("");
	m_ntelef = _T("");
	m_tipocli = _T("");
	m_riba = _T("");
	m_codfis = _T("");
	m_centro = _T("");
	m_categ = _T("");
	m_settore = _T("");
	m_nfatture = _T("");
	m_raggr_verb = _T("");
	m_ninsoluti = _T("");
	m_scoperto = _T("");
	m_abi = _T("");
	m_cab = _T("");
	m_nFields = 37;
	m_data_ins = 0;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CClienti_Old::GetDefaultConnect()
{
	return _T("ODBC;DSN=Clienti");
}

CString CClienti_Old::GetDefaultSQL()
{
	return _T("[clienti]");
}

void CClienti_Old::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CClienti_Old)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[codice]"), m_codice);
	RFX_Text(pFX, _T("[ragsociale]"), m_ragsociale);
	RFX_Text(pFX, _T("[estensione]"), m_estensione);
	RFX_Text(pFX, _T("[indirizzo]"), m_indirizzo);
	RFX_Text(pFX, _T("[descitta]"), m_descitta);
	RFX_Text(pFX, _T("[prov]"), m_prov);
	RFX_Text(pFX, _T("[cap]"), m_cap);
	RFX_Text(pFX, _T("[iva]"), m_iva);
	RFX_Text(pFX, _T("[imporpaga]"), m_imporpaga);
	RFX_Text(pFX, _T("[totimpon]"), m_totimpon);
	RFX_Text(pFX, _T("[totiva]"), m_totiva);
	RFX_Text(pFX, _T("[totbolli]"), m_totbolli);
	RFX_Text(pFX, _T("[richied]"), m_richied);
	RFX_Text(pFX, _T("[fatturato]"), m_fatturato);
	RFX_Text(pFX, _T("[impresa]"), m_impresa);
	RFX_Text(pFX, _T("[codpaga]"), m_codpaga);
	RFX_Text(pFX, _T("[bancaapp]"), m_bancaapp);
	RFX_Text(pFX, _T("[sconto]"), m_sconto);
	RFX_Text(pFX, _T("[genspe]"), m_genspe);
	RFX_Text(pFX, _T("[indspe]"), m_indspe);
	RFX_Text(pFX, _T("[descits]"), m_descits);
	RFX_Text(pFX, _T("[provs]"), m_provs);
	RFX_Text(pFX, _T("[caps]"), m_caps);
	RFX_Text(pFX, _T("[ntelef]"), m_ntelef);
	RFX_Text(pFX, _T("[tipocli]"), m_tipocli);
	RFX_Text(pFX, _T("[riba]"), m_riba);
	RFX_Text(pFX, _T("[codfis]"), m_codfis);
	RFX_Text(pFX, _T("[centro]"), m_centro);
	RFX_Text(pFX, _T("[categ]"), m_categ);
	RFX_Text(pFX, _T("[settore]"), m_settore);
	RFX_Text(pFX, _T("[nfatture]"), m_nfatture);
	RFX_Text(pFX, _T("[raggr_verb]"), m_raggr_verb);
	RFX_Text(pFX, _T("[ninsoluti]"), m_ninsoluti);
	RFX_Text(pFX, _T("[scoperto]"), m_scoperto);
	RFX_Date(pFX, _T("[data_ins]"), m_data_ins);
	RFX_Text(pFX, _T("[abi]"), m_abi);
	RFX_Text(pFX, _T("[cab]"), m_cab);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CClienti_Old diagnostics

#ifdef _DEBUG
void CClienti_Old::AssertValid() const
{
	CRecordset::AssertValid();
}

void CClienti_Old::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
