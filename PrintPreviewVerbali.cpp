// PrintVerbali.cpp: implementation of the CPrintVerbali class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "winsigma.h"
#include "PreviewDlg.h"
#include "PrintPreviewVerbali.h"

#include "Printerpreter.h"
#include "WinSigmaDoc.h"
#include "PrinterThread.h"
#include "XFormView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTipiCertificatoSet*  CPrintPreviewVerbali::m_pTipiCertificatoSet;
CString               CPrintPreviewVerbali::m_strTipoPagamento;
CSerieSet*            CPrintPreviewVerbali::m_pSerieSet;
CVerbaliSet*          CPrintPreviewVerbali::m_pVerbaliSet;
int                   CPrintPreviewVerbali::m_nTotalePagine;
BOOL                  CPrintPreviewVerbali::m_bPrivato;
BOOL                  CPrintPreviewVerbali::m_bSpianatura;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrintPreviewVerbali::CPrintPreviewVerbali()
{
	
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	
	m_pVerbaliSet = new CVerbaliSet(&pApp->m_db);
	m_pSerieSet = new CSerieSet(&pApp->m_db);
	m_pTipiCertificatoSet = new CTipiCertificatoSet(&pApp->m_db);
}

CPrintPreviewVerbali::~CPrintPreviewVerbali()
{
  if(m_pVerbaliSet)
  {
    if(m_pVerbaliSet->IsOpen())
      m_pVerbaliSet->Close();
  	delete m_pVerbaliSet;
  }
	if(m_pSerieSet)
  {
    if(m_pSerieSet->IsOpen())
      m_pSerieSet->Close();
  	delete m_pSerieSet;
  }
  if(m_pTipiCertificatoSet)
  {
    if(m_pTipiCertificatoSet->IsOpen())
      m_pTipiCertificatoSet->Close();
	  delete m_pTipiCertificatoSet;
  }
}

void CPrintPreviewVerbali::Print(long lCodVerbale, CDC* pDC, CRect* pRect)
{
  CPrintInterpreter prnInterpreter;
  CStringArray strNames, strValues;
  BOOL bPrint = FALSE;
  CTime data = CTime::GetCurrentTime();
  CString printFileName, strPrinter;

	m_pVerbaliSet->m_strFilter.Format("Codice = %d",lCodVerbale);
	m_pVerbaliSet->Open();

	m_pTipiCertificatoSet->Open();
	m_strTipoPagamento = m_pVerbaliSet->m_Pagamento;

  m_pSerieSet->m_strFilter.Format("Verbale = %d", m_pVerbaliSet->m_Codice);
  m_pSerieSet->m_strSort = "Codice ASC";
  m_pSerieSet->Open();
  if(m_pVerbaliSet->IsBOF() || m_pVerbaliSet->IsEOF())
	{
	  MessageBeep(-1);
		return;
	}
	// La stampa viene fatta su un file che ha come nome il progressivo totale del verbale
  printFileName.Format("%d_%d.txt", m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale);

	// imposta il nome del file secondo le specifiche della gestione documentale (s.c. 14.09.2017)
	CString docname;
  docname.Format("VA-%d-%d", m_pVerbaliSet->m_ProgressivoTotale, m_pVerbaliSet->m_DataAccettazione.GetYear());
	prnInterpreter.SetDocName(docname);

  if(!prnInterpreter.PrePrinting())
    return;
  m_pSerieSet->m_strFilter.Format("Verbale = %d", m_pVerbaliSet->m_Codice);
  m_pSerieSet->m_strSort = "TipoCertificato, Codice ASC";
  m_pSerieSet->Requery();
  m_bSpianatura = FALSE;
  for(SET_START(m_pSerieSet); !m_pSerieSet->IsEOF(); m_pSerieSet->MoveNext())
  {
	  ASSERT(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_ServAggiungibile));
    if(m_pSerieSet->m_ServAggiungibile)
    {
      if(m_pSerieSet->m_Servizio1 == m_pSerieSet->m_ServAggiungibile
			   || m_pSerieSet->m_Servizio2 == m_pSerieSet->m_ServAggiungibile
			   || m_pSerieSet->m_Servizio3 == m_pSerieSet->m_ServAggiungibile
			   || m_pSerieSet->m_Servizio4 == m_pSerieSet->m_ServAggiungibile
			   || m_pSerieSet->m_Servizio5 == m_pSerieSet->m_ServAggiungibile
			   || m_pSerieSet->m_Servizio6 == m_pSerieSet->m_ServAggiungibile)
        m_bSpianatura = TRUE;  	     
			else
			{
        m_bSpianatura = FALSE;  
			  break;
			}
		}
  }
  SET_START(m_pSerieSet);
  CAziendeSet* pAziende = new CAziendeSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
  pAziende->m_strFilter.Format("Codice = %d", m_pVerbaliSet->m_CodiceAzFattura);
  pAziende->Open();
  m_bPrivato = pAziende->m_Privato;
  pAziende->Close();

  // Simulazione
  m_nTotalePagine = 0;
  prnInterpreter.SetPage(1);
  prnInterpreter.StartSimulation();
#ifdef WINSIGMA2
	prnInterpreter.Print(".\\VerbaliSigma2.prn", &strNames, &strValues, NULL, NULL, &ScanCampioni);
#else
  prnInterpreter.Print(".\\Verbali.prn", &strNames, &strValues, NULL, NULL, &ScanCampioni);
#endif  
	m_nTotalePagine = prnInterpreter.GetPage() - 1;
  prnInterpreter.EndSimulation();
  prnInterpreter.SetPage(1);
  SET_START(m_pSerieSet);
  ScanFields(&strNames, &strValues);
#ifdef WINSIGMA2
	prnInterpreter.Print(".\\VerbaliSigma2.prn", &strNames, &strValues, NULL, NULL, &ScanCampioni);
#else
  prnInterpreter.Print(".\\Verbali.prn", &strNames, &strValues, NULL, NULL, &ScanCampioni);
#endif	
	prnInterpreter.PostPrinting();
  m_pSerieSet->m_strFilter.Empty();
  m_pSerieSet->Requery();
	m_pVerbaliSet->Close();
	m_pTipiCertificatoSet->Close();
	m_pSerieSet->Close();
}

int CPrintPreviewVerbali::PrintPage(long lCodVerbale, CDC* pDC, CRect* pRect, int nPage, double dScala, int nOrigine)
{
  CPrintInterpreter prnInterpreter;
  CStringArray strNames, strValues;
  BOOL bPrint = FALSE;
  CTime data = CTime::GetCurrentTime();
  CString printFileName;

  if(!prnInterpreter.PrePrinting(pDC, pRect, dScala, nOrigine))
    return 0;
	m_pVerbaliSet->m_strFilter.Format("Codice = %d",lCodVerbale);
	m_pVerbaliSet->Open();

	m_pTipiCertificatoSet->Open();
	m_strTipoPagamento = m_pVerbaliSet->m_Pagamento;

  m_pSerieSet->m_strFilter.Format("Verbale = %d", m_pVerbaliSet->m_Codice);
  m_pSerieSet->m_strSort = "Codice ASC";
  m_pSerieSet->Open();
  m_bSpianatura = FALSE;
  for(SET_START(m_pSerieSet); !m_pSerieSet->IsEOF(); m_pSerieSet->MoveNext())
  {
	  ASSERT(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_ServAggiungibile));
    if(m_pSerieSet->m_ServAggiungibile)
    {
      if(m_pSerieSet->m_Servizio1 == m_pSerieSet->m_ServAggiungibile
			   || m_pSerieSet->m_Servizio2 == m_pSerieSet->m_ServAggiungibile
			   || m_pSerieSet->m_Servizio3 == m_pSerieSet->m_ServAggiungibile
			   || m_pSerieSet->m_Servizio4 == m_pSerieSet->m_ServAggiungibile
			   || m_pSerieSet->m_Servizio5 == m_pSerieSet->m_ServAggiungibile
			   || m_pSerieSet->m_Servizio6 == m_pSerieSet->m_ServAggiungibile)
        m_bSpianatura = TRUE;  	     
			else
			{
        m_bSpianatura = FALSE;  
			  break;
			}
		}
  }
  SET_START(m_pSerieSet);
  CAziendeSet* pAziende = new CAziendeSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
  pAziende->m_strFilter.Format("Codice = %d", m_pVerbaliSet->m_CodiceAzFattura);
  pAziende->Open();
  m_bPrivato = pAziende->m_Privato;
  pAziende->Close();
  SET_START(m_pSerieSet);

	// imposta il nome del file secondo le specifiche della gestione documentale (s.c. 14.09.2017)
	CString docname;
  docname.Format("VA-%d-%d", m_pVerbaliSet->m_ProgressivoTotale, m_pVerbaliSet->m_DataAccettazione.GetYear());
	prnInterpreter.SetDocName(docname);

  // Simulazione
  m_nTotalePagine = 0;
  prnInterpreter.SetPage(1);
  prnInterpreter.StartSimulation();
#ifdef WINSIGMA2
	prnInterpreter.Print(".\\VerbaliSigma2.prn", &strNames, &strValues, NULL, NULL, &ScanCampioni);
#else
  prnInterpreter.Print(".\\Verbali.prn", &strNames, &strValues, NULL, NULL, &ScanCampioni);
#endif 	
	m_nTotalePagine = prnInterpreter.GetPage() - 1;
  prnInterpreter.EndSimulation();
  prnInterpreter.m_nTotalePagine = m_nTotalePagine;
	// Stampa
  SET_START(m_pSerieSet);
#ifdef WINSIGMA2
  prnInterpreter.PrintPage(".\\VerbaliSigma2.prn", &strNames, &strValues, &ScanFields, &ScanCampioni, nPage);
#else
  prnInterpreter.PrintPage(".\\Verbali.prn", &strNames, &strValues, &ScanFields, &ScanCampioni, nPage);
#endif 	
	prnInterpreter.PostPrinting(pDC);
	m_pVerbaliSet->Close();
	m_pTipiCertificatoSet->Close();
	m_pSerieSet->Close();
  return m_nTotalePagine;
}

BOOL CPrintPreviewVerbali::ScanFields(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
  int n;
	CString str, strApp;
  if(m_pVerbaliSet->IsEOF())
    return FALSE;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  pFieldNames->RemoveAll();
  pFieldValues->RemoveAll();

  // Numero verbale
  pFieldNames->Add("numeroVerbale");
  str.Format("%d/%d", m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale);
  pFieldValues->Add(str);
  // Tipo di verbale
  pFieldNames->Add("tipoVerbale");
  switch(m_pVerbaliSet->m_TipoVerbale)
  {
  case VERB_IN_CONCESSIONE:
    pFieldValues->Add("Prove in concessione");
    break;
  case VERB_NON_IN_CONCESSIONE:
	case VERB_NC_PROVE_DI_CARICO :
	case VERB_NC_CONGL_BITUMINOSI	:
	case VERB_NC_INERTI	:
	case VERB_NC_MONITORAGGI :
	case VERB_NC_VARIE	:
	case VERB_NC_GEOTECNICA :
	case VERB_NC_LINEE_VITA:
	case VERB_NC_INDAGINI_MURATURE:
	case VERB_NC_INDAGINI_CLS:
	case VERB_NC_MAT_METALLICI:    pFieldValues->Add("Prove non in concessione");
    break;
  case VERB_GEOLOGIA:
    pFieldValues->Add("Prove geotecniche");
    break;
  default:
    pFieldValues->Add("");
    break;
  }
  // Data
  pFieldNames->Add("data");
  str.Format("%s, %s",pApp->GetProfileString(CONFIGURAZIONE, LABORATORIO), m_pVerbaliSet->m_DataAccettazione.Format("%d/%m/%Y") );
  pFieldValues->Add(str);
  // Intestatario certificati
  pFieldNames->Add("codAzCertificati");
  str = m_pVerbaliSet->m_IDAzCertificato;
  str.MakeUpper();
  pFieldValues->Add(str);
  pFieldNames->Add("nomeAzCertificati");
  pFieldValues->Add(m_pVerbaliSet->m_NomeAzCertificato);
  pFieldNames->Add("indirizzoCertificati");
  pFieldValues->Add(m_pVerbaliSet->m_IndirizzoCertificato);
  // Impresa
  pFieldNames->Add("codImpresa");
  pFieldValues->Add(m_pVerbaliSet->m_IDImpresaRichiedente);
  pFieldNames->Add("nomeImpresa");
  pFieldValues->Add(m_pVerbaliSet->m_NomeImpresa);
  pFieldNames->Add("indirizzoImpresa");
  pFieldValues->Add(m_pVerbaliSet->m_IndirizzoRichiedente);
  // Cantiere
  pFieldNames->Add("cantiere1");
  pFieldNames->Add("cantiere2");
	str = m_pVerbaliSet->m_Cantiere;
	n = 0;
  str.Replace("\r\n", " ");
  str.TrimLeft();
  int nAcapo = DIM_STR_CANTIERE / 2;
  if(str.GetLength() > DIM_STR_CANTIERE / 2)
  {
    strApp = str.Left(nAcapo);
    if((n = strApp.ReverseFind(' ')) > 0)
      pFieldValues->Add(str.Left(n));
    else
    {
      pFieldValues->Add(str.Left(nAcapo));
      n = nAcapo;
    }
    strApp = str.Mid(n, DIM_STR_CANTIERE / 2); 
    strApp.TrimLeft();
		strApp.TrimLeft("-");
    strApp.TrimLeft();
    pFieldValues->Add(strApp);
  }
  else
  {
    pFieldValues->Add(str);
    pFieldValues->Add("");
  }
  // Direttore dei lavori
  pFieldNames->Add("direttoreLavori");
  pFieldValues->Add(m_pVerbaliSet->m_Direttore);
  if(!m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_LetteraIncarico) && m_pVerbaliSet->m_LetteraIncarico)
  {
		pFieldNames->Add("letteraLabel");
    pFieldValues->Add("Lettera di incarico......:");
    pFieldNames->Add("lettera");
    pFieldValues->Add(m_pVerbaliSet->m_NumLetteraIncarico);
  }
  pFieldNames->Add("domanda");
  if(!m_pVerbaliSet->m_DomandaSottoscritta)
    pFieldValues->Add("Domanda di prove NON sottoscritta dal D.L.");
  else
    pFieldValues->Add("Domanda di prove sottoscritta dal D.L.");
  // Proprietario
  pFieldNames->Add("proprietario1");
  pFieldNames->Add("proprietario2");
	str = m_pVerbaliSet->m_Proprietario;
	n = 0;
  str.Replace("\r\n", " ");
  str.TrimLeft();
  nAcapo = DIM_STR_CANTIERE / 2;
  if(str.GetLength() > DIM_STR_CANTIERE / 2)
  {
    strApp = str.Left(nAcapo);
    if((n = strApp.ReverseFind(' ')) > 0)
      pFieldValues->Add(str.Left(n));
    else
    {
      pFieldValues->Add(str.Left(nAcapo));
      n = nAcapo;
    }
    strApp = str.Mid(n, DIM_STR_CANTIERE / 2); 
    strApp.TrimLeft();
		strApp.TrimLeft("-");
    strApp.TrimLeft();
    pFieldValues->Add(strApp);
  }
  else
  {
    pFieldValues->Add(str);
    pFieldValues->Add("");
  }
  // Campioni consegnati
  pFieldNames->Add("materialeConsegnato");
	str = m_pVerbaliSet->m_DescrizioneMateriale;
  pFieldValues->Add(str);
  // Prove richieste
  pFieldNames->Add("proveRichiesteNote");
  pFieldValues->Add(m_pVerbaliSet->m_ProveRichieste);
  // Tabella campioni
  pFieldNames->Add("linea");
  pFieldValues->Add("------------------------------------------------------------------------------");
  if(!m_pSerieSet->IsBOF())
  {
    pFieldNames->Add("campioni");
    pFieldValues->Add("C A M P I O N I");
    pFieldNames->Add("sigle");
    pFieldValues->Add("SIGLE");
    pFieldNames->Add("prelievo");
    pFieldValues->Add("P R E L I E V O");
    pFieldNames->Add("posizione");
    pFieldValues->Add("POS");
    pFieldNames->Add("numero");
    pFieldValues->Add("N.");
    pFieldNames->Add("contrassegni");
    pFieldValues->Add("CONTRASSEGNI");
    pFieldNames->Add("tipo");
    pFieldValues->Add("TIPO E CARATTERISTICHE");
    pFieldNames->Add("struttura");
    pFieldValues->Add("STRUTTURA");
    pFieldNames->Add("dataPrelievo");
    pFieldValues->Add("DATA");
    pFieldNames->Add("certificato");
    pFieldValues->Add("CER");
    pFieldNames->Add("barra");
    pFieldValues->Add("|");
  }
  // Spianatura
  pFieldNames->Add("spianatura");
  if(m_bSpianatura)
    pFieldValues->Add("Si");
  else
    pFieldValues->Add("(se necessaria)");
  // Azienda fatturazione
  pFieldNames->Add("codAzFattura");
  pFieldValues->Add(m_pVerbaliSet->m_IDAzFattura);
  pFieldNames->Add("nomeAzFattura");
  pFieldValues->Add(m_pVerbaliSet->m_NomeAzFattura);
  pFieldNames->Add("indirizzoAzFattura");
  pFieldValues->Add(m_pVerbaliSet->m_IndirizzoFattura);
  pFieldNames->Add("partitaIVA");
  if(!m_bPrivato)
    str.Format("Partita I.V.A.:   %s", m_pVerbaliSet->m_P_IVA);
  else
    str = "Prestazione a privato";
  pFieldValues->Add(str);
  pFieldNames->Add("condPagamento");
  pFieldValues->Add(m_pVerbaliSet->m_Pagamento);
  // Richiedente
  pFieldNames->Add("richiedente");
  pFieldValues->Add(m_pVerbaliSet->m_Richiedente);
  // Consegna
  pFieldNames->Add("consegna");
  if(m_pVerbaliSet->m_Spedizione)
  {
    if(!m_pVerbaliSet->m_NoteSpedizione.IsEmpty())
      str = m_pVerbaliSet->m_NoteSpedizione;
    else
      str = "Spedire";
  }
  else
	{
		if(m_pVerbaliSet->m_NoteSpedizione.IsEmpty())
			str = "RITIRO";
		else
			str.Format("RITIRA %s", m_pVerbaliSet->m_NoteSpedizione);
	}
  if(!m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_Urgenza) && m_pVerbaliSet->m_Urgenza)
  {
    if (m_pVerbaliSet->m_Urgenza != 2)
      strApp.Format("  %s - %s", m_pVerbaliSet->m_DataConsegna.Format("%d/%m/%Y"), m_pVerbaliSet->m_OraConsegna);
    else
      strApp.Format("  %s", m_pVerbaliSet->m_DataConsegna.Format("%d/%m/%Y"));
    
    str += strApp;
  }
  pFieldValues->Add(str);
  // Urgenza
  if(!m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_Urgenza) && m_pVerbaliSet->m_Urgenza)
  {
    if (m_pVerbaliSet->m_Urgenza != 2)
    {
      pFieldNames->Add("urgenza");
		  pFieldValues->Add("Procedura d'urgenza (maggiorazione 50%).............firma:...................");
    }
  }
  // Operatore
  pFieldNames->Add("operatore");
  strApp.Empty();
  if(!m_pVerbaliSet->m_Operatore.IsEmpty())
  {
    if((n = m_pVerbaliSet->m_Operatore.Find(" ")) != -1)
    {
      strApp = m_pVerbaliSet->m_Operatore.GetAt(n + 1);
      strApp += ".";
      strApp += m_pVerbaliSet->m_Operatore.GetAt(0);
      strApp += ".";
    }
    else
      strApp = m_pVerbaliSet->m_Operatore.GetAt(0) + ".";
  }
  pFieldValues->Add(strApp);
  pFieldNames->Add("pagina");
  str.Format("/ %d", m_nTotalePagine);
  pFieldValues->Add(str);
  return TRUE;
}

BOOL CPrintPreviewVerbali::ScanCampioni(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
	CString str, strTemp;
  static int numCert;
	int i = 0, l = 0;

  pFieldNames->RemoveAll();
  pFieldValues->RemoveAll();
  if(m_pSerieSet->IsEOF())
  {
    numCert = 0;
    return FALSE;
  }
  for(SET_START(m_pTipiCertificatoSet); !m_pTipiCertificatoSet->IsEOF(); m_pTipiCertificatoSet->MoveNext())
  {
    if(m_pTipiCertificatoSet->m_Codice == m_pSerieSet->m_TipoCertificato)
      break;
  }
  if(m_pTipiCertificatoSet->IsEOF())
    return FALSE;
  pFieldNames->Add("numeroCampioni");
  if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_NumeroProvini))
    str.Format("%d", m_pSerieSet->m_NumeroProvini);
  else
    str.Empty();
  pFieldValues->Add(str);

  pFieldNames->Add("tipoCaratteristiche");
	str = m_pSerieSet->m_Materiale;
		
  pFieldValues->Add(str);
	
  pFieldNames->Add("dimensione1");
  if(!m_pTipiCertificatoSet->m_Dimensione1.IsEmpty())
    str.Format("%.0f", m_pSerieSet->m_Dimensione1);
  else
    str.Empty();
  pFieldValues->Add(str);
  pFieldNames->Add("dimensione2");
  if(!m_pTipiCertificatoSet->m_Dimensione2.IsEmpty())
    str.Format("%.0f", m_pSerieSet->m_Dimensione2);
  else
    str.Empty();
  pFieldValues->Add(str);
  pFieldNames->Add("dimensione3");
  if(!m_pTipiCertificatoSet->m_Dimensione3.IsEmpty())
    str.Format("%.0f", m_pSerieSet->m_Dimensione3);
  else
    str.Empty();
  pFieldValues->Add(str);
  pFieldNames->Add("sigla");
	str = "";
  if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Sigla))
	{
		str = m_pSerieSet->m_Sigla;
	}
    
  pFieldValues->Add(str);
  if(!m_pSerieSet->m_StrutturaPrelievo.IsEmpty())
  {
    pFieldNames->Add("struttura");
		str = m_pSerieSet->m_StrutturaPrelievo;
    pFieldValues->Add(str);
  }
  pFieldNames->Add("data");
  if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_DataPrelievo))
    pFieldValues->Add(m_pSerieSet->m_DataPrelievo.Format("%d/%m/%Y"));
  else
    pFieldValues->Add(m_pSerieSet->m_strDataND);  
  // Posizione del certificato nel verbale
  pFieldNames->Add("posizioneCert");
  if(m_pSerieSet->m_NuovoCertificato)
    numCert++;
  str.Format("%d", numCert);
  pFieldValues->Add(str);
  m_pSerieSet->MoveNext();
  if(m_pSerieSet->IsEOF())
  {
    numCert = 0;
    return FALSE;
  }
  return TRUE;
}
