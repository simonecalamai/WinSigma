// SerieSet.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "SerieSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSerieSet

IMPLEMENT_DYNAMIC(CSerieSet, CRecordset)

CSerieSet::CSerieSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSerieSet)
	m_Codice = 0;
	m_Verbale = 0;
	m_TipoCertificato = 0;
	m_NumeroProvini = 0;
  m_DataPrelievo = 0;
	m_DataProva = 0;
	m_NuovoCertificato = 0;
	m_Certificato = 0;
	m_Servizio1 = 0;
	m_Servizio2 = 0;
	m_Servizio3 = 0;
	m_Servizio4 = 0;
	m_Servizio5 = 0;
	m_Servizio6 = 0;
	m_Materiale =  _T("");
	m_ServAggiungibile = 0;
	m_ServAggiunto = 0;
	m_Sigla = _T("");
	m_Sigla2 = _T("");
	m_StrutturaPrelievo = _T("");
	m_Dimensione1 = 0.0;
	m_Dimensione2 = 0.0;
	m_Dimensione3 = 0.0;
	m_Osservazioni = _T("");
	m_Sperimentatore = _T("");
	m_Macchina	= _T("");
	m_Marchio		= 0;
	m_Snervamento = 0.0;
	m_TipoProva = 0;
	m_strDataND	= _T("");
	m_IDMateriale =  _T("");
	m_Checked = 0;
  m_Ordinamento = 0;
	m_SiglaFornitore =  _T("");
	m_VerbalePrelievo =  _T("");
	m_nFields = 35;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSerieSet::GetDefaultConnect()
{
	return ((CWinSigmaApp*)AfxGetApp())->m_csDefaultConnect;
}

CString CSerieSet::GetDefaultSQL()
{
	return _T(SERIE);
}

void CSerieSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSerieSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Codice]"), m_Codice);
	RFX_Long(pFX, _T("[Verbale]"), m_Verbale);
	RFX_Long(pFX, _T("[TipoCertificato]"), m_TipoCertificato);
	RFX_Int(pFX, _T("[NumeroProvini]"), m_NumeroProvini);
	RFX_Date(pFX, _T("[DataPrelievo]"), m_DataPrelievo);
	RFX_Date(pFX, _T("[DataProva]"), m_DataProva);
	RFX_Byte(pFX, _T("[NuovoCertificato]"), m_NuovoCertificato);
	RFX_Long(pFX, _T("[Certificato]"), m_Certificato);
	RFX_Long(pFX, _T("[Servizio1]"), m_Servizio1);
	RFX_Long(pFX, _T("[Servizio2]"), m_Servizio2);
	RFX_Long(pFX, _T("[Servizio3]"), m_Servizio3);
	RFX_Long(pFX, _T("[Servizio4]"), m_Servizio4);
	RFX_Long(pFX, _T("[Servizio5]"), m_Servizio5);
	RFX_Long(pFX, _T("[Servizio6]"), m_Servizio6);
	RFX_Text(pFX, _T("[Materiale]"), m_Materiale);
	RFX_Long(pFX, _T("[ServAggiungibile]"), m_ServAggiungibile);
	RFX_Long(pFX, _T("[ServAggiunto]"), m_ServAggiunto);
	RFX_Text(pFX, _T("[Sigla]"), m_Sigla);
	RFX_Text(pFX, _T("[Sigla2]"), m_Sigla2);
	RFX_Text(pFX, _T("[StrutturaPrelievo]"), m_StrutturaPrelievo);
	RFX_Double(pFX, _T("[Dimensione1]"), m_Dimensione1);
	RFX_Double(pFX, _T("[Dimensione2]"), m_Dimensione2);
	RFX_Double(pFX, _T("[Dimensione3]"), m_Dimensione3);
	RFX_Text(pFX, _T("[Osservazioni]"),			m_Osservazioni);
	RFX_Text(pFX, _T("[Sperimentatore]"),		m_Sperimentatore);
	RFX_Text(pFX, _T("[Macchina]"),					m_Macchina);
	RFX_Long(pFX, _T("[Marchio]"),	m_Marchio);
	RFX_Double(pFX, _T("[Snervamento]"), m_Snervamento);
	RFX_Int(pFX, _T("[TipoProva]"), m_TipoProva);
	RFX_Text(pFX, _T("[DataND]"), m_strDataND);
	RFX_Text(pFX, _T("[IDMateriale]"), m_IDMateriale);
	RFX_Byte(pFX, _T("[Checked]"), m_Checked);
  RFX_Long(pFX, _T("[Ordinamento]"),	m_Ordinamento);
	RFX_Text(pFX, _T("[SiglaFornitore]"), m_SiglaFornitore);
	RFX_Text(pFX, _T("[VerbalePrelievo]"), m_VerbalePrelievo);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSerieSet diagnostics

#ifdef _DEBUG
void CSerieSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSerieSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
