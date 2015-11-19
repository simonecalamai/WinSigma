// WinSigmaDoc.cpp : implementation of the CWinSigmaDoc class
//

#include "stdafx.h"
#include "WinSigma.h"

#include "WinSigmaDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinSigmaDoc

IMPLEMENT_DYNCREATE(CWinSigmaDoc, CDocument)

BEGIN_MESSAGE_MAP(CWinSigmaDoc, CDocument)
	//{{AFX_MSG_MAP(CWinSigmaDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinSigmaDoc construction/destruction

CWinSigmaDoc::CWinSigmaDoc()
{
  m_pAziendeSet            = NULL;
  m_pAziendeTurboSet       = NULL;
	m_pAziendeRecentiSet     = NULL;
  m_pAziendeImportantiSet  = NULL;
	m_pOperatoriSet          = NULL;
	m_pMarchiSet             = NULL;
	m_pMarchiTurboSet        = NULL;
	m_pTipiMaterialeSet      = NULL;
	m_pTipiPagamentoSet      = NULL;
	m_pListiniScadutiSet     = NULL;
	m_pListiniInVigoreSet    = NULL;
	m_pListiniInElaborazioneSet = NULL;
  m_pVerbaliAperti         = NULL;
  m_pVerbaliUltimoMeseSet  = NULL;
  m_pVerbaliPrecedentiSet  = NULL;
  m_pVerbaliFattProforma   = NULL;
  m_pTipiCertificatoSet    = NULL;
  m_pSerieSet              = NULL;
  m_pFattureEmesseSet      = NULL;
}

CWinSigmaDoc::~CWinSigmaDoc()
{
}

BOOL CWinSigmaDoc::OnNewDocument()
{
  CTime date = CTime::GetCurrentTime() - CTimeSpan(100, 0, 0, 0);
  CString strDate;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

	if (!CDocument::OnNewDocument())
		return FALSE;
  strDate = date.Format("%Y-%m-%d");
  // apro i recordset permanenti : aziende
  m_pAziendeSet = new CAziendeSet(&pApp->m_db);  
  m_pAziendeSet->m_strSort = "RagioneSociale ASC";
  m_pAziendeSet->Open();
  m_pAziendeTurboSet = new CAziendeTurboSet(&pApp->m_db);  
  m_pAziendeTurboSet->m_strSort = "RagioneSociale ASC";
  m_pAziendeTurboSet->Open(CRecordset::snapshot, NULL, CRecordset::readOnly | CRecordset::noDirtyFieldCheck);
  m_pAziendeImportantiSet = new CAziendeSet(&pApp->m_db);
  m_pAziendeImportantiSet->m_strFilter = "IsImportante <> 0";
  m_pAziendeImportantiSet->Open();
  m_pAziendeRecentiSet = new CAziendeSet(&pApp->m_db);
  m_pAziendeRecentiSet->m_strFilter.Format("DataUltimoRapporto > '%s'", strDate); 
  m_pAziendeRecentiSet->m_strSort = "DataUltimoRapporto ASC";
  m_pAziendeRecentiSet->Open();

  // tabelle ausiliarie
  m_pOperatoriSet = new COperatoriSet(&pApp->m_db);
	m_pOperatoriSet->Open();
  m_pTipiMaterialeSet = new CTipiMaterialeSet(&pApp->m_db);
	m_pTipiMaterialeSet->m_strSort = "TipoCertificato, ID ASC";
	m_pTipiMaterialeSet->Open();
  m_pTipiPagamentoSet = new CTipiPagamentoSet(&pApp->m_db);
	m_pTipiPagamentoSet->Open();
	m_pMarchiSet = new CMarchiSet(&pApp->m_db);
	m_pMarchiSet->m_strSort = "Nome";
	m_pMarchiSet->Open();
  m_pMarchiTurboSet = new CMarchiTurboSet(&pApp->m_db);
	m_pMarchiTurboSet->m_strSort = "Nome";
	m_pMarchiTurboSet->Open();

	// listini
  date = CTime::GetCurrentTime();
  strDate = date.Format("%Y-%m-%d");
  m_pListiniScadutiSet = new CListiniSet(&pApp->m_db);
	m_pListiniScadutiSet->m_strFilter.Format("Inizio < '%s' AND Fine < '%s'", strDate, strDate);
	m_pListiniScadutiSet->Open();
  m_pListiniInVigoreSet = new CListiniSet(&pApp->m_db);
	m_pListiniInVigoreSet->m_strFilter.Format("Inizio <= '%s' AND (Fine >= '%s' OR Fine is NULL)", strDate, strDate);
	m_pListiniInVigoreSet->Open();
  m_pListiniInElaborazioneSet = new CListiniSet(&pApp->m_db);
	m_pListiniInElaborazioneSet->m_strFilter.Format("Inizio > '%s' or Inizio is null", strDate);
	m_pListiniInElaborazioneSet->Open();


  // Verbali
  date = CTime::GetCurrentTime() - CTimeSpan(30, 0, 0, 0);
  strDate = date.Format("%Y-%m-%d");
  m_pVerbaliAperti = new CVerbaliSet(&pApp->m_db);
  m_pVerbaliAperti->m_strFilter = "DataChiusura is NULL";
  m_pVerbaliAperti->Open();
  m_pVerbaliUltimoMeseSet = new CVerbaliSet(&pApp->m_db);
  m_pVerbaliUltimoMeseSet->m_strFilter.Format("DataChiusura is NULL AND DataAccettazione >= '%s' AND TipoVerbale <> %d AND TipoVerbale <> %d AND TipoVerbale <> %d and TipoVerbale <> %d", strDate, VERB_VECCHIO_PROG, VERB_PER_FATTURA, VERB_PER_NOTACREDITO);
  m_pVerbaliUltimoMeseSet->Open();
  m_pVerbaliPrecedentiSet = new CVerbaliSet(&pApp->m_db);
  m_pVerbaliPrecedentiSet->m_strFilter.Format("DataChiusura is NULL AND DataAccettazione < '%s' AND TipoVerbale <> %d AND TipoVerbale <> %d OR (TipoVerbale = %d AND LungaScadenza = 1)", strDate, VERB_VECCHIO_PROG, VERB_PER_FATTURA, VERB_PER_NOTACREDITO, VERB_VECCHIO_PROG);
  m_pVerbaliPrecedentiSet->Open();
  m_pVerbaliFattProforma = new CVerbaliSet(&pApp->m_db);
  m_pVerbaliFattProforma->m_strFilter.Format("DataChiusura is NULL and InFatturazione = %ld", VERB_PROFORMA);
  m_pVerbaliFattProforma->Open();
  
  // Tipi certificato
  m_pTipiCertificatoSet = new CTipiCertificatoSet(&pApp->m_db);
	m_pTipiCertificatoSet->m_strSort = "Codice ASC";
  m_pTipiCertificatoSet->Open();

  // Serie
  m_pSerieSet = new CSerieSet(&pApp->m_db);
  m_pSerieSet->m_strSort = "TipoCertificato, Codice ASC";
  m_pSerieSet->Open();

  // Fatture emesse
  m_pFattureEmesseSet = new CFattureSet(&pApp->m_db);
  m_pFattureEmesseSet->Open();

  return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWinSigmaDoc serialization

void CWinSigmaDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWinSigmaDoc diagnostics

#ifdef _DEBUG
void CWinSigmaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWinSigmaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWinSigmaDoc commands

void CWinSigmaDoc::DeleteContents() 
{
  if(m_pAziendeSet)
  {
    m_pAziendeSet->Close();
    delete m_pAziendeSet;
  }
  if(m_pAziendeTurboSet)
  {
    m_pAziendeTurboSet->Close();
    delete m_pAziendeTurboSet;
  }
  if(m_pAziendeRecentiSet)
  {
    m_pAziendeRecentiSet->Close();
    delete m_pAziendeRecentiSet;
  }
  if(m_pAziendeImportantiSet)
  {
    m_pAziendeImportantiSet->Close();
    delete m_pAziendeImportantiSet;
  }
  if(m_pOperatoriSet)
	{
		m_pOperatoriSet->Close();
		delete m_pOperatoriSet;
	}
  if(m_pTipiMaterialeSet)
	{
		m_pTipiMaterialeSet->Close();
		delete m_pTipiMaterialeSet;
	}
  if(m_pTipiPagamentoSet)
	{
		m_pTipiPagamentoSet->Close();
		delete m_pTipiPagamentoSet;
	}
  if(m_pMarchiSet)
	{
		m_pMarchiSet->Close();
		delete m_pMarchiSet;
	}
  if(m_pMarchiTurboSet)
	{
		m_pMarchiTurboSet->Close();
		delete m_pMarchiTurboSet;
	}
  if(m_pListiniScadutiSet)
	{
		m_pListiniScadutiSet->Close();
		delete m_pListiniScadutiSet;
	}
  if(m_pListiniInVigoreSet)
	{
		m_pListiniInVigoreSet->Close();
		delete m_pListiniInVigoreSet;
	}
  if(m_pListiniInElaborazioneSet)
	{
		m_pListiniInElaborazioneSet->Close();
		delete m_pListiniInElaborazioneSet;
	}
  if(m_pVerbaliAperti)
  {
    m_pVerbaliAperti->Close();
    delete m_pVerbaliAperti;
  }
  if(m_pVerbaliUltimoMeseSet)
  {
    m_pVerbaliUltimoMeseSet->Close();
    delete m_pVerbaliUltimoMeseSet;
  }
  if(m_pVerbaliPrecedentiSet)
  {
    m_pVerbaliPrecedentiSet->Close();
    delete m_pVerbaliPrecedentiSet;
  }
  if(m_pVerbaliFattProforma)
  {
    m_pVerbaliFattProforma->Close();
    delete m_pVerbaliFattProforma;
  }
  if(m_pTipiCertificatoSet)
  {
    m_pTipiCertificatoSet->Close();
    delete m_pTipiCertificatoSet;
  }
  if(m_pSerieSet)
  {
    m_pSerieSet->Close();
    delete m_pSerieSet;
  }
  if(m_pFattureEmesseSet)
  {
    m_pFattureEmesseSet->Close();
    delete m_pFattureEmesseSet;
  }
	CDocument::DeleteContents();
}

