// VerbaliSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "VerbaliSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVerbaliSet

IMPLEMENT_DYNAMIC(CVerbaliSet, CRecordset)

CVerbaliSet::CVerbaliSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CVerbaliSet)
	m_Cantiere = _T("");
	m_Codice = 0;
	m_DataAccettazione = 0;
	m_DataChiusura = 0;
	m_DataConsegna = 0;
	m_DataPrimaStampa = 0;
	m_ProveRichieste = _T("");
	m_Direttore = _T("");
	m_CodiceImpresa = 0;
	m_ProgressivoParziale = 0;
	m_ProgressivoTotale = 0;
	m_Proprietario = _T("");
	m_Richiedente = _T("");
	m_CertOgniSerie = 0;
	m_Spedizione = 0;
	m_Urgenza = 0;
	m_DescrizioneMateriale = _T("");
	m_IndirizzoRichiedente = _T("");
	m_IndirizzoCertificato = _T("");
	m_IndirizzoFattura = _T("");
	m_CodiceAzCertificato = 0;
	m_CodiceAzFattura = 0;
	m_NomeImpresa = _T("");
	m_NomeAzCertificato = _T("");
	m_NomeAzFattura = _T("");
	m_IDImpresaRichiedente = _T("");
	m_IDAzCertificato = _T("");
	m_IDAzFattura = _T("");
	m_TipoVerbale = 0;
	m_Destinatario = _T("");
	m_LetteraIncarico = 0;
	m_NumLetteraIncarico = _T("");
	m_NoteSpedizione = _T("");
	m_P_IVA = _T("");
  m_Pagamento = _T("");
	m_ListinoGenerale = 0;
	m_ListinoParticolare = 0;
	m_LungaScadenza = 0;
	m_Operatore = _T("");
	m_DomandaSottoscritta = 0;
	m_OraConsegna = _T("");
	m_NumeroFattura = 0;
	m_InFatturazione = 0;
	m_InUso = _T("");
	m_Annullato = 0;
  m_CodFiscale = _T("");
	m_nFields = 46;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CVerbaliSet::GetDefaultConnect()
{
  return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CVerbaliSet::GetDefaultSQL()
{
	return _T(VERBALI);
}

void CVerbaliSet::DoFieldExchange(CFieldExchange* pFX)
{
	if (((CWinSigmaApp*)AfxGetApp())->m_bPrimaVolta)
    Spacciatore();
  
  //{{AFX_FIELD_MAP(CVerbaliSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Cantiere]"), m_Cantiere);
	RFX_Long(pFX, _T("[Codice]"), m_Codice);
	RFX_Date(pFX, _T("[DataAccettazione]"), m_DataAccettazione);
	RFX_Date(pFX, _T("[DataChiusura]"), m_DataChiusura);
	RFX_Date(pFX, _T("[DataConsegna]"), m_DataConsegna);
	RFX_Date(pFX, _T("[DataPrimaStampa]"), m_DataPrimaStampa);
	RFX_Text(pFX, _T("[DescrizioneProveRichieste]"), m_ProveRichieste);
	RFX_Text(pFX, _T("[DirettoreLavori]"), m_Direttore);
	RFX_Long(pFX, _T("[ImpresaRichiedente]"), m_CodiceImpresa);
	RFX_Long(pFX, _T("[ProgressivoParziale]"), m_ProgressivoParziale);
	RFX_Long(pFX, _T("[ProgressivoTotale]"), m_ProgressivoTotale);
	RFX_Text(pFX, _T("[Proprietario]"), m_Proprietario);
	RFX_Text(pFX, _T("[Richiedente]"), m_Richiedente);
	RFX_Byte(pFX, _T("[CertOgniSerie]"), m_CertOgniSerie);
	RFX_Byte(pFX, _T("[VuoiSpedizione]"), m_Spedizione);
	RFX_Byte(pFX, _T("[VuoiUrgenza]"), m_Urgenza);
	RFX_Text(pFX, _T("[DescrizioneMateriale]"), m_DescrizioneMateriale);
	RFX_Text(pFX, _T("[IndirizzoImpresaRichiedente]"), m_IndirizzoRichiedente);
	RFX_Text(pFX, _T("[IndirizzoIntCertificato]"), m_IndirizzoCertificato);
	RFX_Text(pFX, _T("[IndirizzoIntFattura]"), m_IndirizzoFattura);
	RFX_Long(pFX, _T("[IntestatarioCertificato]"), m_CodiceAzCertificato);
	RFX_Long(pFX, _T("[IntestatarioFattura]"), m_CodiceAzFattura);
	RFX_Text(pFX, _T("[NomeImpresaRichiedente]"), m_NomeImpresa);
	RFX_Text(pFX, _T("[NomeIntestatarioCertificato]"), m_NomeAzCertificato);
	RFX_Text(pFX, _T("[NomeIntestatarioFattura]"), m_NomeAzFattura);
	RFX_Text(pFX, _T("[IDImpresaRichiedente]"), m_IDImpresaRichiedente);
	RFX_Text(pFX, _T("[IDIntestatarioCertificato]"), m_IDAzCertificato);
	RFX_Text(pFX, _T("[IDIntestatarioFattura]"), m_IDAzFattura);
	RFX_Long(pFX, _T("[TipoVerbale]"), m_TipoVerbale);
	RFX_Text(pFX, _T("[Destinatario]"), m_Destinatario);
	RFX_Byte(pFX, _T("[LetteraIncarico]"), m_LetteraIncarico);
	RFX_Text(pFX, _T("[NumLetteraIncarico]"), m_NumLetteraIncarico);
	RFX_Text(pFX, _T("[NoteSpedizione]"), m_NoteSpedizione);
	RFX_Text(pFX, _T("[P_IVA]"), m_P_IVA);
	RFX_Text(pFX, _T("[Pagamento]"), m_Pagamento);
	RFX_Long(pFX, _T("[ListinoGenerale]"), m_ListinoGenerale);
	RFX_Long(pFX, _T("[ListinoParticolare]"), m_ListinoParticolare);
	RFX_Byte(pFX, _T("[LungaScadenza]"), m_LungaScadenza);
	RFX_Text(pFX, _T("[Operatore]"), m_Operatore);
	RFX_Byte(pFX, _T("[DomandaSottoscritta]"), m_DomandaSottoscritta);
	RFX_Text(pFX, _T("[OraConsegna]"), m_OraConsegna);
	RFX_Long(pFX, _T("[Fattura]"), m_NumeroFattura);
	RFX_Byte(pFX, _T("[InFatturazione]"), m_InFatturazione);
	RFX_Text(pFX, _T("[InUso]"), m_InUso);
	RFX_Byte(pFX, _T("[Annullato]"), m_Annullato);
  RFX_Text(pFX, _T("[CodFiscale]"), m_CodFiscale);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CVerbaliSet diagnostics

#ifdef _DEBUG
void CVerbaliSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CVerbaliSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
