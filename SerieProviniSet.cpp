// SerieProviniSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "SerieProviniSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSerieProviniSet

IMPLEMENT_DYNAMIC(CSerieProviniSet, CRecordset)

CSerieProviniSet::CSerieProviniSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSerieProviniSet)
	m_CodiceSerie = 0;
	m_Verbale = 0;
	m_TipoCertificato = 0;
	m_NumeroProvini = 0;
	m_NuovoCertificato = 0;
	m_Certificato = 0;
	m_DataPrelievo = CTime::GetCurrentTime();
	m_DataProva = CTime::GetCurrentTime();
	m_StrutturaPrelievo = _T("");
	m_Sigla = _T("");
	m_Servizio1 = 0;
	m_Servizio2 = 0;
	m_Servizio3 = 0;
	m_Servizio4 = 0;
	m_Servizio5 = 0;
	m_Servizio6 = 0;
	m_ServAggiungibile = 0;
	m_ServAggiunto = 0;
	m_CodiceProvino = 0;
	m_DataInserimento = 0;
	m_InUso = _T("");
	m_Serie = 0;
	m_Materiale = _T("");
	m_Osservazioni = _T("");
	m_Sperimentatore = _T("");
	m_Macchina = _T("");
	m_MarchioSerie = 0;
	m_Marchio = 0;
	m_Snervamento = 0;
	m_Dimensione1 = 0.0;
	m_Dimensione2 = 0.0;
	m_Dimensione3 = 0.0;
	m_TipoProva	= 0;
	m_strDataND = _T("");
	m_Checked = 0;
	m_VerbalePrelievo = _T("");
	m_SiglaFornitore = _T("");
	m_RotoliCT = 0;
	m_nFields = 39;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSerieProviniSet::GetDefaultConnect()
{
	return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CSerieProviniSet::GetDefaultSQL()
{
  return _T("[SERIE], [PROVINI]");
}

void CSerieProviniSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSerieProviniSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[SERIE].[Codice]"),		m_CodiceSerie);
	RFX_Long(pFX, _T("[Verbale]"),					m_Verbale);
	RFX_Long(pFX, _T("[TipoCertificato]"),	m_TipoCertificato);
	RFX_Int(pFX, _T("[NumeroProvini]"),			m_NumeroProvini);
	RFX_Byte(pFX, _T("[NuovoCertificato]"), m_NuovoCertificato);
	RFX_Long(pFX, _T("[Certificato]"),			m_Certificato);
	RFX_Date(pFX, _T("[DataPrelievo]"),			m_DataPrelievo);
	RFX_Date(pFX, _T("[DataProva]"),				m_DataProva);
	RFX_Text(pFX, _T("[StrutturaPrelievo]"),m_StrutturaPrelievo);
	RFX_Text(pFX, _T("[Sigla]"),						m_Sigla); 
	RFX_Long(pFX, _T("[Servizio1]"),				m_Servizio1);
	RFX_Long(pFX, _T("[Servizio2]"),				m_Servizio2);
	RFX_Long(pFX, _T("[Servizio3]"),				m_Servizio3);
	RFX_Long(pFX, _T("[Servizio4]"),				m_Servizio4);
	RFX_Long(pFX, _T("[Servizio5]"),				m_Servizio5);
	RFX_Long(pFX, _T("[Servizio6]"),				m_Servizio6);
	RFX_Long(pFX, _T("[ServAggiungibile]"),	m_ServAggiungibile);
	RFX_Long(pFX, _T("[ServAggiunto]"),			m_ServAggiunto);
	RFX_Long(pFX, _T("[PROVINI].[Codice]"),	m_CodiceProvino);
	RFX_Date(pFX, _T("[DataInserimento]"),	m_DataInserimento);
	RFX_Text(pFX, _T("[InUso]"),						m_InUso);
	RFX_Binary(pFX, _T("[Risultati]"),			m_Risultati);
	RFX_Long(pFX, _T("[PROVINI].[Serie]"),	m_Serie);
	RFX_Text(pFX, _T("[Materiale]"),				m_Materiale);
	RFX_Text(pFX, _T("[Osservazioni]"),			m_Osservazioni);
	RFX_Text(pFX, _T("[Sperimentatore]"),		m_Sperimentatore);
	RFX_Text(pFX, _T("[Macchina]"),					m_Macchina);
	RFX_Long(pFX, _T("[SERIE].[Marchio]"),	m_MarchioSerie);
	RFX_Long(pFX, _T("[PROVINI].[Marchio]"),	m_Marchio);
	RFX_Double(pFX, _T("[Snervamento]"), m_Snervamento);
	RFX_Double(pFX, _T("[SERIE].[Dimensione1]"), m_Dimensione1);
	RFX_Double(pFX, _T("[SERIE].[Dimensione2]"), m_Dimensione2);
	RFX_Double(pFX, _T("[SERIE].[Dimensione3]"), m_Dimensione3);
	RFX_Int(pFX, _T("[TipoProva]"), m_TipoProva);
	RFX_Text(pFX, _T("[DataND]"),						m_strDataND);
	RFX_Byte(pFX, _T("[Checked]"),					m_Checked);
	RFX_Text(pFX, _T("[VerbalePrelievo]"),	m_VerbalePrelievo);
	RFX_Text(pFX, _T("[SiglaFornitore]"),	m_SiglaFornitore);
	RFX_Byte(pFX, _T("[RotoliCT]"), m_RotoliCT);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSerieProviniSet diagnostics

#ifdef _DEBUG
void CSerieProviniSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSerieProviniSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
