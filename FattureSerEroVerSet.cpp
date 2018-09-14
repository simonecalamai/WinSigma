// FattureSerEroVerSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "FattureSerEroVerSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFattureSerEroVerSet

IMPLEMENT_DYNAMIC(CFattureSerEroVerSet, CRecordset)

CFattureSerEroVerSet::CFattureSerEroVerSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CFattureSerEroVerSet)
	m_Codice = 0;
	m_Intestatario = 0;
	m_TipoPagamento = 0;
	m_Numero = 0;
	m_P_IVA = _T("");
	m_CodiceFiscale = _T("");
	m_RagioneSociale = _T("");
	m_IDIntestario = _T("");
	m_Indirizzo = _T("");
	m_CAP = _T("");
	m_Citta = _T("");
	m_Provincia = _T("");
	m_Banca = _T("");
	m_ABI = _T("");
	m_CAB = _T("");
	m_Sconto = 0.0;
	m_AliquotaIVA = 0.0;
	m_Spese = 0.0;
	m_Imponibile = 0.0;
	m_Pagamento = _T("");
	m_TipoDocumento = 0;
	m_CINAppoggio = _T("");
	m_ContoAppoggio = _T("");
	m_RitenutaAcconto = 0.0;
	m_CodiceServizio = 0;
	m_Verbale = 0;
	m_Fattura = 0;
	m_Serie = 0;
	m_Quantita = 0.0;
	m_Prezzo = 0.0;
	m_TipoVerbale = 0;
	m_Annullato = 0;
	m_ScontoSevizio = 0;
	m_VuoiUrgenza = 0;
	m_PA = 0;
	m_CodiceDestinatario = _T("");
	m_PEC = _T("");
	m_nFields = 39;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CFattureSerEroVerSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=WinSigma");
}

CString CFattureSerEroVerSet::GetDefaultSQL()
{
	return _T("[FATTURE],[SERVIZI_EROGATI],[VERBALI]");
}

void CFattureSerEroVerSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CFattureSerEroVerSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[FATTURE].[Codice]"), m_Codice);
	RFX_Long(pFX, _T("[Intestatario]"), m_Intestatario);
	RFX_Long(pFX, _T("[TipoPagamento]"), m_TipoPagamento);
	RFX_Long(pFX, _T("[Numero]"), m_Numero);
	RFX_Date(pFX, _T("[Data]"), m_Data);
	RFX_Date(pFX, _T("[Scadenza]"), m_Scadenza);
	RFX_Text(pFX, _T("[FATTURE].[P_IVA]"), m_P_IVA);
	RFX_Text(pFX, _T("[CodiceFiscale]"), m_CodiceFiscale);
	RFX_Text(pFX, _T("[RagioneSociale]"), m_RagioneSociale);
	RFX_Text(pFX, _T("[IDIntestario]"), m_IDIntestario);
	RFX_Text(pFX, _T("[Indirizzo]"), m_Indirizzo);
	RFX_Text(pFX, _T("[CAP]"), m_CAP);
	RFX_Text(pFX, _T("[Citta]"), m_Citta);
	RFX_Text(pFX, _T("[Provincia]"), m_Provincia);
	RFX_Text(pFX, _T("[Banca]"), m_Banca);
	RFX_Text(pFX, _T("[ABI]"), m_ABI);
	RFX_Text(pFX, _T("[CAB]"), m_CAB);
	RFX_Double(pFX, _T("[FATTURE].[Sconto]"), m_Sconto);
	RFX_Double(pFX, _T("[AliquotaIVA]"), m_AliquotaIVA);
	RFX_Double(pFX, _T("[Spese]"), m_Spese);
	RFX_Double(pFX, _T("[Imponibile]"), m_Imponibile);
	RFX_Text(pFX, _T("[FATTURE].[Pagamento]"), m_Pagamento);
	RFX_Byte(pFX, _T("[TipoDocumento]"), m_TipoDocumento);
	RFX_Text(pFX, _T("[CINAppoggio]"), m_CINAppoggio);
	RFX_Text(pFX, _T("[ContoAppoggio]"), m_ContoAppoggio);
	RFX_Double(pFX, _T("[RitenutaAcconto]"), m_RitenutaAcconto);
	RFX_Long(pFX, _T("[CodiceServizio]"), m_CodiceServizio);
	RFX_Long(pFX, _T("[Verbale]"), m_Verbale);
	RFX_Long(pFX, _T("[SERVIZI_EROGATI].[Fattura]"), m_Fattura);
	RFX_Long(pFX, _T("[Serie]"), m_Serie);
	RFX_Double(pFX, _T("[Quantita]"), m_Quantita);
	RFX_Double(pFX, _T("[Prezzo]"), m_Prezzo);
	RFX_Long(pFX, _T("[TipoVerbale]"), m_TipoVerbale);
	RFX_Byte(pFX, _T("[Annullato]"), m_Annullato);
	RFX_Double(pFX, _T("[SERVIZI_EROGATI].[Sconto]"), m_ScontoSevizio);
	RFX_Long(pFX, _T("[VERBALI].[VuoiUrgenza]"), m_VuoiUrgenza);
	RFX_Byte(pFX, _T("[FATTURE].[fPA]"), m_PA);
	RFX_Text(pFX, _T("[CodiceDestinatario]"), m_CodiceDestinatario);
	RFX_Text(pFX, _T("[PEC]"), m_PEC);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CFattureSerEroVerSet diagnostics

#ifdef _DEBUG
void CFattureSerEroVerSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CFattureSerEroVerSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
