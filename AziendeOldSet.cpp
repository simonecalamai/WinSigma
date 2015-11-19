// AziendeOldSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "AziendeOldSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAziendeOldSet

IMPLEMENT_DYNAMIC(CAziendeOldSet, CRecordset)

CAziendeOldSet::CAziendeOldSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CAziendeOldSet)
	m_Codice = 0;
	m_TipoPagamento = 0;
	m_Privato = 0;
	m_ID = _T("");
	m_P_IVA = _T("");
	m_CodiceFiscale = _T("");
	m_RagioneSociale = _T("");
	m_RagioneSociale_Sped = _T("");
	m_Nome = _T("");
	m_Cognome = _T("");
	m_Indirizzo = _T("");
	m_CAP = _T("");
	m_Citta = _T("");
	m_Provincia = _T("");
	m_Indirizzo_Sped = _T("");
	m_CAP_Sped = _T("");
	m_Citta_Sped = _T("");
	m_Provincia_Sped = _T("");
	m_E_Mail = _T("");
	m_Telefono = _T("");
	m_Cellulare = _T("");
	m_Fax = _T("");
	m_Banca = _T("");
	m_ABI = _T("");
	m_CAB = _T("");
	m_Note = _T("");
	m_Sconto = 0.0;
	m_IsImportante = 0;
	m_UsaTuttiListini = 0;
	m_nFields = 31;
	m_DataInserimento = 0;
	m_DataUltimoRapporto = 0;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CAziendeOldSet::GetDefaultConnect()
{
  return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CAziendeOldSet::GetDefaultSQL()
{
	return _T("[AZIENDE_VECCHIE]");
}

void CAziendeOldSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAziendeOldSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Codice]"), m_Codice);
	RFX_Long(pFX, _T("[TipoPagamento]"), m_TipoPagamento);
	RFX_Byte(pFX, _T("[Privato]"), m_Privato);
	RFX_Text(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[P_IVA]"), m_P_IVA);
	RFX_Text(pFX, _T("[CodiceFiscale]"), m_CodiceFiscale);
	RFX_Text(pFX, _T("[RagioneSociale]"), m_RagioneSociale);
	RFX_Text(pFX, _T("[RagioneSociale_Sped]"), m_RagioneSociale_Sped);
	RFX_Text(pFX, _T("[Nome]"), m_Nome);
	RFX_Text(pFX, _T("[Cognome]"), m_Cognome);
	RFX_Text(pFX, _T("[Indirizzo]"), m_Indirizzo);
	RFX_Text(pFX, _T("[CAP]"), m_CAP);
	RFX_Text(pFX, _T("[Citta]"), m_Citta);
	RFX_Text(pFX, _T("[Provincia]"), m_Provincia);
	RFX_Text(pFX, _T("[Indirizzo_Sped]"), m_Indirizzo_Sped);
	RFX_Text(pFX, _T("[CAP_Sped]"), m_CAP_Sped);
	RFX_Text(pFX, _T("[Citta_Sped]"), m_Citta_Sped);
	RFX_Text(pFX, _T("[Provincia_Sped]"), m_Provincia_Sped);
	RFX_Text(pFX, _T("[E_Mail]"), m_E_Mail);
	RFX_Text(pFX, _T("[Telefono]"), m_Telefono);
	RFX_Text(pFX, _T("[Cellulare]"), m_Cellulare);
	RFX_Text(pFX, _T("[Fax]"), m_Fax);
	RFX_Text(pFX, _T("[Banca]"), m_Banca);
	RFX_Text(pFX, _T("[ABI]"), m_ABI);
	RFX_Text(pFX, _T("[CAB]"), m_CAB);
	RFX_Text(pFX, _T("[Note]"), m_Note, AZIENDE_BUFFER);
	RFX_Double(pFX, _T("[Sconto]"), m_Sconto);
	RFX_Date(pFX, _T("[DataInserimento]"), m_DataInserimento);
	RFX_Date(pFX, _T("[DataUltimoRapporto]"), m_DataUltimoRapporto);
	RFX_Byte(pFX, _T("[IsImportante]"), m_IsImportante);
	RFX_Byte(pFX, _T("[UsaTuttiListini]"), m_UsaTuttiListini);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CAziendeOldSet diagnostics

#ifdef _DEBUG
void CAziendeOldSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CAziendeOldSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
