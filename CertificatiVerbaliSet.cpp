// CertificatiVerbaliSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "CertificatiVerbaliSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCertificatiVerbaliSet

IMPLEMENT_DYNAMIC(CCertificatiVerbaliSet, CRecordset)

CCertificatiVerbaliSet::CCertificatiVerbaliSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CCertificatiVerbaliSet)
	m_CodiceCertificato = 0;
	m_CodiceVerbale = 0;
	m_Verbale = 0;
	m_TipoCertificato = 0;
	m_NumeroCertificato = 0;
	m_Posizione = 0;
	m_Cantiere = _T("");
	m_DataProve = 0;
	m_DescrizioneMateriale = _T("");
	m_DescrizioneProveRichieste = _T("");
	m_DirettoreLavori = _T("");
	m_IDImpresaRichiedente = _T("");
	m_IDIntestatarioCertificato = _T("");
	m_IDIntestatarioFattura = _T("");
	m_ImpresaRichiedente = 0;
	m_IndirizzoImpresaRichiedente = _T("");
	m_IndirizzoIntCertificato = _T("");
	m_IndirizzoIntFattura = _T("");
	m_Destinatario = _T("");
	m_IntestatarioCertificato = 0;
	m_IntestatarioFattura = 0;
	m_LetteraIncarico = 0;
	m_NomeImpresaRichiedente = _T("");
	m_NomeIntestatarioCertificato = _T("");
	m_NomeIntestatarioFattura = _T("");
	m_NumLetteraIncarico = _T("");
	m_ProgressivoParziale = 0;
	m_ProgressivoTotale = 0;
	m_Proprietario = _T("");
	m_TipoVerbale = 0;
	m_VuoiSpedizione = 0;
	m_VuoiUrgenza = 0;
	m_Sottoscritta = 0;
	m_InFatturazione = 0;
	m_ListinoGenerale = 0;
	m_ListinoParticolare = 0;
	m_LungaScadenza = 0;
	m_NoteSpedizione = _T("");
	m_Operatore = _T("");
	m_OraConsegna = _T("");
	m_P_IVA = _T("");
	m_Richiedente = _T("");
	m_NumeroPagine = 0;
	m_EmendatoDa = 0;
	m_EmendaIl = 0;
	m_Fattura = 0;
	m_Aderenza = 0;
	m_nFields = 53;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CCertificatiVerbaliSet::GetDefaultConnect()
{
	return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CCertificatiVerbaliSet::GetDefaultSQL()
{
	return _T("[CERTIFICATI],[VERBALI]");
}

void CCertificatiVerbaliSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CCertificatiVerbaliSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[CERTIFICATI].[Codice]"), m_CodiceCertificato);
	RFX_Long(pFX, _T("[VERBALI].[Codice]"), m_CodiceVerbale);
	RFX_Long(pFX, _T("[CERTIFICATI].[Verbale]"), m_Verbale);
	RFX_Byte(pFX, _T("[Aderenza]"), m_Aderenza);
	RFX_Long(pFX, _T("[TipoCertificato]"), m_TipoCertificato);
	RFX_Long(pFX, _T("[NumeroCertificato]"), m_NumeroCertificato);
	RFX_Long(pFX, _T("[Posizione]"), m_Posizione);
	RFX_Date(pFX, _T("[DataEmissione]"), m_DataEmissione);
	RFX_Date(pFX, _T("[DataStampa]"), m_DataStampa);
	RFX_Text(pFX, _T("[Cantiere]"), m_Cantiere);
	RFX_Date(pFX, _T("[DataAccettazione]"), m_DataAccettazione);
	RFX_Date(pFX, _T("[DataChiusura]"), m_DataChiusura);
	RFX_Date(pFX, _T("[DataConsegna]"), m_DataConsegna);
	RFX_Date(pFX, _T("[DataPrimaStampa]"), m_DataPrimaStampa);
	RFX_Date(pFX, _T("[DataProve]"), m_DataProve);
	RFX_Text(pFX, _T("[DescrizioneMateriale]"), m_DescrizioneMateriale);
	RFX_Text(pFX, _T("[DescrizioneProveRichieste]"), m_DescrizioneProveRichieste);
	RFX_Text(pFX, _T("[DirettoreLavori]"), m_DirettoreLavori);
	RFX_Text(pFX, _T("[IDImpresaRichiedente]"), m_IDImpresaRichiedente);
	RFX_Text(pFX, _T("[IDIntestatarioCertificato]"), m_IDIntestatarioCertificato);
	RFX_Text(pFX, _T("[IDIntestatarioFattura]"), m_IDIntestatarioFattura);
	RFX_Long(pFX, _T("[ImpresaRichiedente]"), m_ImpresaRichiedente);
	RFX_Text(pFX, _T("[IndirizzoImpresaRichiedente]"), m_IndirizzoImpresaRichiedente);
	RFX_Text(pFX, _T("[IndirizzoIntCertificato]"), m_IndirizzoIntCertificato);
	RFX_Text(pFX, _T("[IndirizzoIntFattura]"), m_IndirizzoIntFattura);
	RFX_Text(pFX, _T("[Destinatario]"), m_Destinatario);
	RFX_Long(pFX, _T("[IntestatarioCertificato]"), m_IntestatarioCertificato);
	RFX_Long(pFX, _T("[IntestatarioFattura]"), m_IntestatarioFattura);
	RFX_Byte(pFX, _T("[LetteraIncarico]"), m_LetteraIncarico);
	RFX_Text(pFX, _T("[NomeImpresaRichiedente]"), m_NomeImpresaRichiedente);
	RFX_Text(pFX, _T("[NomeIntestatarioCertificato]"), m_NomeIntestatarioCertificato);
	RFX_Text(pFX, _T("[NomeIntestatarioFattura]"), m_NomeIntestatarioFattura);
	RFX_Text(pFX, _T("[NumLetteraIncarico]"), m_NumLetteraIncarico);
	RFX_Long(pFX, _T("[ProgressivoParziale]"), m_ProgressivoParziale);
	RFX_Long(pFX, _T("[ProgressivoTotale]"), m_ProgressivoTotale);
	RFX_Text(pFX, _T("[Proprietario]"), m_Proprietario);
	RFX_Long(pFX, _T("[TipoVerbale]"), m_TipoVerbale);
	RFX_Byte(pFX, _T("[VuoiSpedizione]"), m_VuoiSpedizione);
	RFX_Byte(pFX, _T("[VuoiUrgenza]"), m_VuoiUrgenza);
	RFX_Byte(pFX, _T("[DomandaSottoscritta]"), m_Sottoscritta);
	RFX_Byte(pFX, _T("[InFatturazione]"), m_InFatturazione);
	RFX_Long(pFX, _T("[ListinoGenerale]"), m_ListinoGenerale);
	RFX_Long(pFX, _T("[ListinoParticolare]"), m_ListinoParticolare);
	RFX_Byte(pFX, _T("[LungaScadenza]"), m_LungaScadenza);
	RFX_Text(pFX, _T("[NoteSpedizione]"), m_NoteSpedizione);
	RFX_Text(pFX, _T("[Operatore]"), m_Operatore);
	RFX_Text(pFX, _T("[OraConsegna]"), m_OraConsegna);
	RFX_Text(pFX, _T("[P_IVA]"), m_P_IVA);
	RFX_Text(pFX, _T("[Richiedente]"), m_Richiedente);
	RFX_Int(pFX, _T("[NumeroPagine]"), m_NumeroPagine);
	RFX_Long(pFX, _T("[EmendatoDa]"), m_EmendatoDa);
	RFX_Long(pFX, _T("[EmendaIl]"), m_EmendaIl);
	RFX_Long(pFX, _T("[VERBALI].[Fattura]"), m_Fattura);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CCertificatiVerbaliSet diagnostics

#ifdef _DEBUG
void CCertificatiVerbaliSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCertificatiVerbaliSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
