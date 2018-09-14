// FattureSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "FattureSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFattureSet

IMPLEMENT_DYNAMIC(CFattureSet, CRecordset)

CFattureSet::CFattureSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CFattureSet)
	m_Codice = 0;
	m_Intestatario = 0;
	m_TipoPagamento = 0;
	m_Numero = 0;
  m_Data = 0;
  m_Scadenza = 0;
	m_P_IVA = _T("");
	m_CodiceFiscale = _T("");
	m_RagioneSociale = _T("");
	m_Indirizzo = _T("");
	m_CAP = _T("");
	m_Citta = _T("");
	m_Provincia = _T("");
	m_Banca = _T("");
	m_ABI = _T("");
	m_CAB = _T("");
	m_Sconto = 0.0;
	m_Note = _T("");
	m_IDIntestatario = _T("");
	m_Aliquota = 0.0;
	m_Archiviata = 0;
	m_Imponibile = 0.0;
	m_Spese = 0.0;
	m_Pagamento = _T("");
	m_TipoDocumento = 0;
	m_InUso = _T("");
	m_ABIAppoggio = _T("");
	m_BancaAppoggio = _T("");
	m_CABAppoggio = _T("");
	m_CINAppoggio = _T("");
	m_ContoAppoggio = _T("");
  m_RitAcconto = 0.0;
	m_PA = 0;
	m_IVADifferita = 0;
	m_Elett = 0;
	m_CodiceDestinatario = _T("");
	m_PEC = _T("");
	m_nFields = 37;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CFattureSet::GetDefaultConnect()
{
  return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CFattureSet::GetDefaultSQL()
{
	return _T(FATTURE);
}

void CFattureSet::DoFieldExchange(CFieldExchange* pFX)
{
	if (((CWinSigmaApp*)AfxGetApp())->m_bPrimaVolta)
    Spacciatore();

  //{{AFX_FIELD_MAP(CFattureSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Codice]"), m_Codice);
	RFX_Long(pFX, _T("[Intestatario]"), m_Intestatario);
	RFX_Long(pFX, _T("[TipoPagamento]"), m_TipoPagamento);
	RFX_Long(pFX, _T("[Numero]"), m_Numero);
	RFX_Date(pFX, _T("[Data]"), m_Data);
	RFX_Date(pFX, _T("[Scadenza]"), m_Scadenza);
	RFX_Text(pFX, _T("[P_IVA]"), m_P_IVA);
	RFX_Text(pFX, _T("[CodiceFiscale]"), m_CodiceFiscale);
	RFX_Text(pFX, _T("[RagioneSociale]"), m_RagioneSociale);
	RFX_Text(pFX, _T("[Indirizzo]"), m_Indirizzo);
	RFX_Text(pFX, _T("[CAP]"), m_CAP);
	RFX_Text(pFX, _T("[Citta]"), m_Citta);
	RFX_Text(pFX, _T("[Provincia]"), m_Provincia);
	RFX_Text(pFX, _T("[Banca]"), m_Banca);
	RFX_Text(pFX, _T("[ABI]"), m_ABI);
	RFX_Text(pFX, _T("[CAB]"), m_CAB);
	RFX_Double(pFX, _T("[Sconto]"), m_Sconto);
	RFX_Text(pFX, _T("[Note]"), m_Note, FATTURE_BUFFER);
	RFX_Text(pFX, _T("[IDIntestario]"), m_IDIntestatario);
	RFX_Double(pFX, _T("[AliquotaIVA]"), m_Aliquota);
	RFX_Byte(pFX, _T("[Archiviata]"), m_Archiviata);
	RFX_Double(pFX, _T("[Imponibile]"), m_Imponibile);
	RFX_Double(pFX, _T("[Spese]"), m_Spese);
	RFX_Text(pFX, _T("[Pagamento]"), m_Pagamento);
	RFX_Byte(pFX, _T("[TipoDocumento]"), m_TipoDocumento);
	RFX_Text(pFX, _T("[InUso]"), m_InUso);
	RFX_Text(pFX, _T("[ABIAppoggio]"), m_ABIAppoggio);
	RFX_Text(pFX, _T("[BancaAppoggio]"), m_BancaAppoggio);
	RFX_Text(pFX, _T("[CABAppoggio]"), m_CABAppoggio);
	RFX_Text(pFX, _T("[CINAppoggio]"), m_CINAppoggio);
	RFX_Text(pFX, _T("[ContoAppoggio]"), m_ContoAppoggio);
  RFX_Double(pFX, _T("[RitenutaAcconto]"), m_RitAcconto);
	RFX_Byte(pFX, _T("[fPA]"), m_PA);
	RFX_Byte(pFX, _T("[fIVADiff]"), m_IVADifferita);
	RFX_Byte(pFX, _T("[fElett]"), m_Elett);
	RFX_Text(pFX, _T("[CodiceDestinatario]"), m_CodiceDestinatario);
	RFX_Text(pFX, _T("[PEC]"), m_PEC);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CFattureSet diagnostics

#ifdef _DEBUG
void CFattureSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CFattureSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
