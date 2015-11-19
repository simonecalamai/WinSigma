// PrintVerbali.cpp: implementation of the CPrintVerbali class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "winsigma.h"
#include "PrintVerbali.h"

#include "Printerpreter.h"
#include "WinSigmaDoc.h"
#include "PrinterThread.h"
#include "XFormView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTipiCertificatoSet* CPrintVerbali::m_pTipiCertificatoSet;
CString CPrintVerbali::m_strTipoPagamento;
CSerieSet*   CPrintVerbali::m_pSerieSet;
CVerbaliSet* CPrintVerbali::m_pVerbaliSet;
int CPrintVerbali::m_nTotalePagine;
CString CPrintVerbali::m_csApp1;
CString CPrintVerbali::m_csApp2;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrintVerbali::CPrintVerbali(CWinSigmaDoc* pDoc, HWND phWnd)
{
	
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	
	m_pVerbaliSet = new CVerbaliSet(&pApp->m_db);
	m_pSerieSet = new CSerieSet(&pApp->m_db);
	m_pTipiCertificatoSet = new CTipiCertificatoSet(&pApp->m_db);
	
	m_pDoc = pDoc;
	m_hWnd = phWnd;

}

CPrintVerbali::~CPrintVerbali()
{

	m_pVerbaliSet->Close();
	delete m_pVerbaliSet;
	
	m_pSerieSet->Close();
	delete m_pSerieSet;

	m_pTipiCertificatoSet->Close();
	delete m_pTipiCertificatoSet;

}

void CPrintVerbali::PrintVerbale(BOOL bCartaIntestata, long lCodVerbale)
{
  CPrintInterpreter prnInterpreter;
  CStringArray strNames, strValues;
  BOOL bPrint = FALSE;
  CTime data = CTime::GetCurrentTime();
  CString printFileName;

	m_print_verbali = new CPrintVerbaliView((CWnd*)this);
	m_print_verbali->DoModal();

	m_pVerbaliSet->m_strFilter.Format("Codice = %d",lCodVerbale);
	m_pVerbaliSet->Open();

	m_pTipiCertificatoSet->Open();

  // La stampa viene fatta su un file che ha come nome il progressivo totale del verbale
  printFileName.Format("%d_%d.txt", m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale);

	CTipiPagamentoSet* pTipoPag = m_pDoc->m_pTipiPagamentoSet;
	if ((!m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_TipoPagamento))&&(m_pVerbaliSet->m_TipoPagamento!=0))
	{
		SINCRONIZE(pTipoPag, m_pVerbaliSet->m_TipoPagamento);
		m_strTipoPagamento = pTipoPag->m_Nome;
	}
	else
		m_strTipoPagamento.Empty();

  if(!bCartaIntestata)
  {
    if(!prnInterpreter.PrePrinting())
      return;
  }
  m_pSerieSet->m_strFilter.Format("Verbale = %d", m_pVerbaliSet->m_Codice);
  m_pSerieSet->m_strSort = "Codice ASC";
  m_pSerieSet->Open();
  SET_START(m_pSerieSet);
  // Simulazione
  m_nTotalePagine = 0;
  prnInterpreter.SetPage(1);
  prnInterpreter.StartSimulation();
  for(SET_START(m_pSerieSet); !m_pSerieSet->IsEOF(); )
#ifdef WINSIGMA2
    prnInterpreter.Print(".\\VerbaliSigma2.prn", &strNames, &strValues, NULL, &ScanCampioni);
#else            
    prnInterpreter.Print(".\\Verbali.prn", &strNames, &strValues, NULL, &ScanCampioni);
#endif
  
	m_nTotalePagine = prnInterpreter.GetPage() - 1;
  prnInterpreter.EndSimulation();
	prnInterpreter.SetPage(1);
  SET_START(m_pSerieSet);
  if(bCartaIntestata)
  {
#ifdef WINSIGMA2
    if(prnInterpreter.PrintText(".\\VerbaliSigma2.prn", printFileName, &strNames, &strValues, &ScanFields, &ScanCampioni))
#else
    if(prnInterpreter.PrintText(".\\Verbali.prn", printFileName, &strNames, &strValues, &ScanFields, &ScanCampioni))
#endif    
		{
      CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
      SetTimer(m_hWnd,TIME_OUT_MSG_ID, 10000, NULL);
      // Il file è pronto, posso lanciare il thread di stampa
      CPrinterThread prnThread;
      if(m_pVerbaliSet->m_TipoVerbale == VERB_IN_CONCESSIONE)
        prnThread.BeginPrinterThread(printFileName, pApp->GetProfileString(CONFIGURAZIONE, STAMPA_CONCESSIONE), m_hWnd);
      else if(m_pVerbaliSet->m_TipoVerbale == VERB_GEOLOGIA)
        prnThread.BeginPrinterThread(printFileName, pApp->GetProfileString(CONFIGURAZIONE, STAMPA_GEOLOGIA), m_hWnd);
      else
        prnThread.BeginPrinterThread(printFileName, pApp->GetProfileString(CONFIGURAZIONE, STAMPA_NONCONCESSIONE), m_hWnd);
			try
			{
				pApp->LockTable(VERBALI);
				// Scrivo la data nel record
				pApp->BeginTrans();
				m_pVerbaliSet->Edit();
				m_pVerbaliSet->m_DataPrimaStampa = data;
				m_pVerbaliSet->Update();
				pApp->CommitTrans();
				pApp->UnlockTables(); 
			}
			catch(CDBException* e)
			{
				/*----- transazione fallita ----*/
				pApp->Rollback();
  			pApp->UnlockTables();
				AfxMessageBox(e->m_strError);
			}
    }
  }
  else
  {
#ifdef WINSIGMA2
		prnInterpreter.Print(".\\VerbaliSigma2.prn", &strNames, &strValues, &ScanFields, &ScanCampioni);
#else
    prnInterpreter.Print(".\\Verbali.prn", &strNames, &strValues, &ScanFields, &ScanCampioni);
#endif  	
		prnInterpreter.PostPrinting();
  }
}

BOOL CPrintVerbali::ScanFields(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
  CString str;
  CTime data = CTime::GetCurrentTime();

  if(m_pVerbaliSet->IsEOF())
    return FALSE;
  pFieldNames->RemoveAll();
  pFieldValues->RemoveAll();
  // Numero verbale
  pFieldNames->Add("numeroVerbale");
  str.Format("%d/%d", m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale);
  pFieldValues->Add(str);
  // Tipo di verbale
  pFieldNames->Add("tipoVerbale");
  if(m_pVerbaliSet->m_TipoVerbale == VERB_IN_CONCESSIONE)
    pFieldValues->Add("Prove in concessione");
  else if(!m_pVerbaliSet->m_TipoVerbale)
    pFieldValues->Add("Prove non in concessione");
  else
    pFieldValues->Add("");
  // Data
  pFieldNames->Add("data");
  str.Format("FI, %s", data.Format("%d/%m/%Y"));
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
	m_csApp1 = "";
	m_csApp2 = "";
	int a(m_pVerbaliSet->m_Cantiere.Find("/r"));
	m_csApp1.Insert(0,m_pVerbaliSet->m_Cantiere.Mid(0,a));
	m_csApp2.Insert(0,m_pVerbaliSet->m_Cantiere.Mid(a,m_pVerbaliSet->m_Cantiere.GetLength()));

	pFieldNames->Add("cantiere1");
	pFieldNames->Add("cantiere2");
	//if(!m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_Cantiere))
	if(m_csApp1 != "")
			pFieldValues->Add(m_csApp1);
			//pFieldValues->Add(m_pVerbaliSet->m_Cantiere);
	else
			pFieldValues->Add("");

  //if(!m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_Cantiere2))
	if(m_csApp2 != "")
    pFieldValues->Add(m_csApp2);
		//pFieldValues->Add(m_pVerbaliSet->m_Cantiere2);
  else
    pFieldValues->Add("");
  // Direttore dei lavori
  pFieldNames->Add("direttoreLavori");
  pFieldValues->Add(m_pVerbaliSet->m_Direttore);
  if(!m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_LetteraIncarico) && m_pVerbaliSet->m_LetteraIncarico)
  {
    pFieldNames->Add("lettera");
    pFieldValues->Add(m_pVerbaliSet->m_NumLetteraIncarico);
  }
  pFieldNames->Add("domanda");
  if(!m_pVerbaliSet->m_DomandaSottoscritta)
    pFieldValues->Add("Domanda di prove NON sottoscritta dal D.L.");
  else
    pFieldValues->Add("Domanda di prove sottoscritta dal D.L.");
  // Proprietario
  pFieldNames->Add("proprietario");
  pFieldValues->Add(m_pVerbaliSet->m_Proprietario);
  // Campioni consegnati
  pFieldNames->Add("materialeConsegnato");
  pFieldValues->Add(m_pVerbaliSet->m_DescrizioneMateriale);
  // Prove richieste
  pFieldNames->Add("proveRichiesteNote");
  pFieldValues->Add(m_pVerbaliSet->m_ProveRichieste);
  // Tabella campioni
  pFieldNames->Add("linea");
  pFieldValues->Add("------------------------------------------------------------------------------");
  if(!m_pSerieSet->IsBOF())
  {
    pFieldNames->Add("campioni");
    pFieldValues->Add("CAMPIONI");
    pFieldNames->Add("sigle");
    pFieldValues->Add("SIGLE");
    pFieldNames->Add("prelievo");
    pFieldValues->Add("PRELIEVO");
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
  }
  // Spianatura
  pFieldNames->Add("spianatura");
  pFieldValues->Add("(se necessaria)");
  // Azienda fatturazione
  pFieldNames->Add("codAzFattura");
  pFieldValues->Add(m_pVerbaliSet->m_IDAzFattura);
  pFieldNames->Add("nomeAzFattura");
  pFieldValues->Add(m_pVerbaliSet->m_NomeAzFattura);
  pFieldNames->Add("indirizzoAzFattura");
  pFieldValues->Add(m_pVerbaliSet->m_IndirizzoFattura);
  pFieldNames->Add("partitaIVA");
  pFieldValues->Add(m_pVerbaliSet->m_P_IVA);
  pFieldNames->Add("condPagamento");
  pFieldValues->Add(m_strTipoPagamento);
  // Richiedente
  pFieldNames->Add("richiedente");
  pFieldValues->Add(m_pVerbaliSet->m_Richiedente);
  // Consegna
  pFieldNames->Add("consegna");
  if(m_pVerbaliSet->m_Spedizione)
  {
    if(!m_pVerbaliSet->m_NoteSpedizione.IsEmpty())
      str.Format("Spedire a %s", m_pVerbaliSet->m_NoteSpedizione);
    else
      str.Format("Spedire");
  }
  else
    str.Format("%s", m_pVerbaliSet->m_NoteSpedizione);
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
  pFieldValues->Add(m_pVerbaliSet->m_Operatore);

  pFieldNames->Add("pagina");
  str.Format("/ %d", m_nTotalePagine);
  pFieldValues->Add(str);

  return FALSE;
}

BOOL CPrintVerbali::ScanCampioni(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
  CString str;
  static int numCert;

  pFieldNames->RemoveAll();
  pFieldValues->RemoveAll();
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
/*
  pFieldNames->Add("tipoCaratteristiche");
  if(!m_pTipiCertificatoSet->IsFieldNull(&m_pTipiCertificatoSet->m_Descrizione))
    pFieldValues->Add(m_pTipiCertificatoSet->m_Descrizione);
  else
    pFieldValues->Add("");
*/
  pFieldNames->Add("dimensione1");
  if(!m_pTipiCertificatoSet->IsFieldNull(&m_pTipiCertificatoSet->m_ValoreDim1))
    str.Format("%d", m_pTipiCertificatoSet->m_ValoreDim1);
  else
    str.Empty();
  pFieldValues->Add(str);
  pFieldNames->Add("dimensione2");
  if(!m_pTipiCertificatoSet->IsFieldNull(&m_pTipiCertificatoSet->m_ValoreDim2))
    str.Format("%d", m_pTipiCertificatoSet->m_ValoreDim2);
  else
    str.Empty();
  pFieldValues->Add(str);
  pFieldNames->Add("dimensione3");
  if(!m_pTipiCertificatoSet->IsFieldNull(&m_pTipiCertificatoSet->m_ValoreDim3))
    str.Format("%d", m_pTipiCertificatoSet->m_ValoreDim3);
  else
    str.Empty();
  pFieldValues->Add(str);
  pFieldNames->Add("sigla");
  if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Sigla))
    pFieldValues->Add(m_pSerieSet->m_Sigla);
  else
    pFieldValues->Add("");
  if(!m_pSerieSet->m_StrutturaPrelievo.IsEmpty())
  {
    pFieldNames->Add("struttura");
    pFieldValues->Add(m_pSerieSet->m_StrutturaPrelievo);
  }
  pFieldNames->Add("data");
  if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_DataPrelievo))
    pFieldValues->Add(m_pSerieSet->m_DataPrelievo.Format("%d/%m/%Y"));
  else
    pFieldValues->Add("N.D.");  
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
