// VerbaliServErogatiSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "VerbaliServErogatiSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVerbaliServErogatiSet

IMPLEMENT_DYNAMIC(CVerbaliServErogatiSet, CRecordset)

CVerbaliServErogatiSet::CVerbaliServErogatiSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CVerbaliServErogatiSet)
	m_CodiceServizioErogato = 0;
	m_CodiceServizio = 0;
	m_Verbale = 0;
	m_Prezzo = 0.0;
	m_Sconto = 0.0;
	m_CodiceVerbale = 0;
	m_IntestatarioFattura = 0;
	m_ListinoGenerale = 0;
	m_ListinoParticolare = 0;
	m_P_IVA = _T("");
	m_ProgressivoTotale = 0;
	m_ProgressivoParziale = 0;
	m_DataAccettazione = 0;
	m_DataPrimaStampa = 0;
	m_DataConsegna = 0;
	m_DataChiusura = 0;
	m_VuoiUrgenza = 0;
	m_VuoiSpedizione = 0;
	m_Descrizione = _T("");
	m_Serie = 0;
	m_TipoVerbale = 0;
	m_LungaScadenza = 0;
	m_IDListino = _T("");
	m_Cantiere = _T("");
	m_NumFatturaServizio = 0;
	m_NumFatturaVerbale = 0;
	m_InFatturazione = 0;
	m_Quantita = 0.0;
	m_Nome = _T("");
	m_nFields = 29;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CVerbaliServErogatiSet::GetDefaultConnect()
{
	return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CVerbaliServErogatiSet::GetDefaultSQL()
{
  CString str;
  str.Format("%s,%s", SERVIZI_EROGATI, VERBALI);
	return _T(str);
}

void CVerbaliServErogatiSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CVerbaliServErogatiSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[SERVIZI_EROGATI].[Codice]"), m_CodiceServizioErogato);
	RFX_Long(pFX, _T("[CodiceServizio]"), m_CodiceServizio);
	RFX_Long(pFX, _T("[Verbale]"), m_Verbale);
	RFX_Double(pFX, _T("[Prezzo]"), m_Prezzo);
	RFX_Double(pFX, _T("[Sconto]"), m_Sconto);
	RFX_Long(pFX, _T("[VERBALI].[Codice]"), m_CodiceVerbale);
	RFX_Long(pFX, _T("[IntestatarioFattura]"), m_IntestatarioFattura);
	RFX_Long(pFX, _T("[ListinoGenerale]"), m_ListinoGenerale);
	RFX_Long(pFX, _T("[ListinoParticolare]"), m_ListinoParticolare);
	RFX_Text(pFX, _T("[P_IVA]"), m_P_IVA);
	RFX_Long(pFX, _T("[ProgressivoTotale]"), m_ProgressivoTotale);
	RFX_Long(pFX, _T("[ProgressivoParziale]"), m_ProgressivoParziale);
	RFX_Date(pFX, _T("[DataAccettazione]"), m_DataAccettazione);
	RFX_Date(pFX, _T("[DataPrimaStampa]"), m_DataPrimaStampa);
	RFX_Date(pFX, _T("[DataConsegna]"), m_DataConsegna);
	RFX_Date(pFX, _T("[DataChiusura]"), m_DataChiusura);
	RFX_Byte(pFX, _T("[VuoiUrgenza]"), m_VuoiUrgenza);
	RFX_Byte(pFX, _T("[VuoiSpedizione]"), m_VuoiSpedizione);
	RFX_Text(pFX, _T("[Descrizione]"), m_Descrizione);
	RFX_Long(pFX, _T("[Serie]"), m_Serie);
	RFX_Long(pFX, _T("[TipoVerbale]"), m_TipoVerbale);
	RFX_Byte(pFX, _T("[LungaScadenza]"), m_LungaScadenza);
	RFX_Text(pFX, _T("[ID_Listino]"), m_IDListino);
	RFX_Text(pFX, _T("[Cantiere]"), m_Cantiere);
	RFX_Long(pFX, _T("[SERVIZI_EROGATI].[Fattura]"), m_NumFatturaServizio);
	RFX_Long(pFX, _T("[VERBALI].[Fattura]"), m_NumFatturaVerbale);
	RFX_Byte(pFX, _T("[InFatturazione]"), m_InFatturazione);
	RFX_Double(pFX, _T("[Quantita]"), m_Quantita);
	RFX_Text(pFX, _T("[Nome]"), m_Nome);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CVerbaliServErogatiSet diagnostics

#ifdef _DEBUG
void CVerbaliServErogatiSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CVerbaliServErogatiSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
