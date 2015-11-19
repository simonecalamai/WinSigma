// PrintPreviewFatture.cpp: implementation of the CPrintPreviewFatture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "winsigma.h"
#include "Printerpreter.h"
#include "PrintPreviewFatture.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
BOOL                    CPrintPreviewFatture::m_bPrintProForma;
double                  CPrintPreviewFatture::m_dAliquota;
double                  CPrintPreviewFatture::m_dSpeseSpedizione;
CFattureSet*            CPrintPreviewFatture::m_pFattureEmesseSet;
CVerbaliSet*            CPrintPreviewFatture::m_pVerbaliInfatturazione;
CServiziErogatiSet*     CPrintPreviewFatture::m_pServiziErogati;
CAziendeSet*            CPrintPreviewFatture::m_pAziendeSet;
CString                 CPrintPreviewFatture::m_strTipoDocumento;
CString                 CPrintPreviewFatture::m_strImportoScontato;
CString                 CPrintPreviewFatture::m_strProgressiviVerbali;
CString                 CPrintPreviewFatture::m_strImponibile;
CString                 CPrintPreviewFatture::m_strIVA;
CString                 CPrintPreviewFatture::m_strTotaleFattura;
double                  CPrintPreviewFatture::m_dSconto;
BOOL                    CPrintPreviewFatture::m_bSpedSelezionata;
int                     CPrintPreviewFatture::m_nNumPagine;
long                    CPrintPreviewFatture::m_lCodiceServizio;
long                    CPrintPreviewFatture::m_lCodiceVerbale;
long                    CPrintPreviewFatture::m_lCodiceFattura;
BOOL                    CPrintPreviewFatture::m_bMaggiorazione;
BOOL                    CPrintPreviewFatture::m_bVerbaliPrinted;
CString                 CPrintPreviewFatture::m_strTipoPagamento;
int                     CPrintPreviewFatture::m_nImportoVerbale;
BOOL                    CPrintPreviewFatture::m_bRiba;

CPrintPreviewFatture::CPrintPreviewFatture()
{
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  m_pFattureEmesseSet = new CFattureSet(&pApp->m_db);
  m_pVerbaliInfatturazione = new CVerbaliSet(&pApp->m_db);
  m_pServiziErogati = new CServiziErogatiSet(&pApp->m_db);
  m_pAziendeSet = new CAziendeSet(&pApp->m_db);
}

CPrintPreviewFatture::~CPrintPreviewFatture()
{
  if(m_pFattureEmesseSet)
  {
    if(m_pFattureEmesseSet->IsOpen())
      m_pFattureEmesseSet->Close();
    delete m_pFattureEmesseSet;
  }
  if(m_pVerbaliInfatturazione)
  {
    if(m_pVerbaliInfatturazione->IsOpen())
      m_pVerbaliInfatturazione->Close();
    delete m_pVerbaliInfatturazione;
  }
  if(m_pServiziErogati)
  {
    if(m_pServiziErogati->IsOpen())
      m_pServiziErogati->Close();
    delete m_pServiziErogati;
  }
  if(m_pAziendeSet)
  {
    if(m_pAziendeSet->IsOpen())
      m_pAziendeSet->Close();
    delete m_pAziendeSet;
  }
}


void CPrintPreviewFatture::Print(long lCodice, CDC* pDC, CRect* pRect)
{
  CPrintInterpreter prn;

  if(pDC == NULL)
  {
    if(!prn.PrePrinting())
      return;
  }
  else
  {
    if(!prn.PrePrinting(pDC, pRect, 0, 0))
      return;
  }
  SincronizeData();
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CStringArray strNames, strValues;

  // Simulazione
  m_lCodiceVerbale = 0;
  m_lCodiceServizio = 0;
  m_bMaggiorazione = FALSE;
  m_bVerbaliPrinted = FALSE;
  SET_START(m_pVerbaliInfatturazione);
  SET_START(m_pServiziErogati);
  CalcolaTotale();
  prn.SetPage(1);
  prn.StartSimulation();
  SET_START(m_pVerbaliInfatturazione);
  SET_START(m_pServiziErogati);
  if(m_bRaggruppaPerServizio)
    prn.Print(pApp->GetCurrentDirectory() + m_strLayout, &strNames, &strValues, &ScanDatiFattura, &ScanPerServizio);
  else
    prn.Print(pApp->GetCurrentDirectory() + m_strLayout, &strNames, &strValues, &ScanDatiFattura, &ScanServizi);
  m_nNumPagine = prn.GetPage() - 1;
  prn.EndSimulation();
  m_pVerbaliInfatturazione->m_strSort = "Codice";
  m_pServiziErogati->m_strSort = "Verbale,ID_Listino,Codice";
  m_pVerbaliInfatturazione->Requery();
  m_pServiziErogati->Requery();
  for(int n = 0; n < m_nNumeroCopie; n++)
  {
    m_lCodiceVerbale = 0;
    m_bMaggiorazione = FALSE;
    m_bVerbaliPrinted = FALSE;
    m_nImportoVerbale = 0;
    prn.SetPage(1);
    SET_START(m_pVerbaliInfatturazione);
    SET_START(m_pServiziErogati);
    if(m_bRaggruppaPerServizio)
      prn.Print(pApp->GetCurrentDirectory() + m_strLayout, &strNames, &strValues, &ScanDatiFattura, &ScanPerServizio);
    else
      prn.Print(pApp->GetCurrentDirectory() + m_strLayout, &strNames, &strValues, &ScanDatiFattura, &ScanServizi);
  }
  prn.PostPrinting();
}


int CPrintPreviewFatture::PrintPage(long lCodice, CDC* pDC, CRect* pRect, int nPage, double dScala, int nOrigine)
{
  CPrintInterpreter prn;

  if(pDC == NULL)
  {
    if(!prn.PrePrinting())
      return 0;
  }
  else
  {
    if(!prn.PrePrinting(pDC, pRect, dScala, nOrigine))
      return 0;
  }
  SincronizeData();
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CStringArray strNames, strValues;

  // Simulazione
  m_lCodiceVerbale = 0;
  m_lCodiceServizio = 0;
  m_bMaggiorazione = FALSE;
  m_bVerbaliPrinted = FALSE;
  SET_START(m_pVerbaliInfatturazione);
  SET_START(m_pServiziErogati);
  CalcolaTotale();
  prn.SetPage(1);
  prn.StartSimulation();
  SET_START(m_pVerbaliInfatturazione);
  SET_START(m_pServiziErogati);
  if(m_bRaggruppaPerServizio)
    prn.Print(pApp->GetCurrentDirectory() + m_strLayout, &strNames, &strValues, &ScanDatiFattura, &ScanPerServizio);
  else
    prn.Print(pApp->GetCurrentDirectory() + m_strLayout, &strNames, &strValues, &ScanDatiFattura, &ScanServizi);
  m_nNumPagine = prn.GetPage() - 1;
  prn.EndSimulation();
  prn.m_nTotalePagine = m_nNumPagine;
  m_pVerbaliInfatturazione->m_strSort = "Codice";
  m_pServiziErogati->m_strSort = "Verbale,ID_Listino,Codice";
  m_pVerbaliInfatturazione->Requery();
  m_pServiziErogati->Requery();
  m_lCodiceVerbale = 0;
  m_bMaggiorazione = FALSE;
  m_bVerbaliPrinted = FALSE;
  m_nImportoVerbale = 0;
  SET_START(m_pVerbaliInfatturazione);
  SET_START(m_pServiziErogati);
  if(m_bRaggruppaPerServizio)
    prn.PrintPage(pApp->GetCurrentDirectory() + m_strLayout, &strNames, &strValues, &ScanDatiFattura, &ScanPerServizio, nPage);
  else
    prn.PrintPage(pApp->GetCurrentDirectory() + m_strLayout, &strNames, &strValues, &ScanDatiFattura, &ScanServizi, nPage);
  prn.PostPrinting();
  return m_nNumPagine;
}

BOOL CPrintPreviewFatture::ScanDatiFattura(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
  CString str;

  pFieldNames->RemoveAll();
  pFieldValues->RemoveAll();
  // Intestazione fattura
  pFieldNames->Add("codice");
  pFieldNames->Add("ragioneSociale");
  pFieldNames->Add("indirizzo");
  pFieldNames->Add("datiLocalita");
  pFieldNames->Add("pIVA");
  pFieldNames->Add("tipoPagamento");
  pFieldNames->Add("tipo_documento");
  pFieldNames->Add("numero");
  pFieldNames->Add("data");
  // Per le fatture proforma, prendo i dati dal recordset delle aziende
  if(m_bPrintProForma)
  {
    // Dati anagrafici dell'intestatario
    pFieldValues->Add(m_pAziendeSet->m_ID);
    str = m_pAziendeSet->m_RagioneSociale;
    str.Replace("&", "&&");
    pFieldValues->Add(str);
    pFieldValues->Add(m_pAziendeSet->m_Indirizzo);
    str.Empty();
    if(!m_pAziendeSet->m_CAP.IsEmpty())
      str = m_pAziendeSet->m_CAP;
    if(!m_pAziendeSet->m_Citta.IsEmpty())
    {
      str += " ";
      str += m_pAziendeSet->m_Citta;
    }
    if(!m_pAziendeSet->m_Provincia.IsEmpty())
    {
      str += " (";
      str += m_pAziendeSet->m_Provincia; 
      str += ")";
    }
    pFieldValues->Add(str);
    // Partita IVA o codice fiscale
    if(!m_pAziendeSet->m_P_IVA.IsEmpty())
    {
      str.Format("P.IVA    %s", m_pAziendeSet->m_P_IVA);
      pFieldValues->Add(str);
    }
    else if(!m_pAziendeSet->m_CodiceFiscale.IsEmpty())
    {
      str.Format("Cod.Fiscale    %s", m_pAziendeSet->m_CodiceFiscale);
      pFieldValues->Add(str);
    }
    else
      pFieldValues->Add("");
    // Tipo pagamento
    if(!m_bRiba || (m_bRiba && m_pAziendeSet->m_Banca.IsEmpty()))
      str = m_strTipoPagamento;
    else
    {
      if(m_pAziendeSet->m_ABI.IsEmpty() || m_pAziendeSet->m_CAB.IsEmpty())
        str.Format("%s - BANCA %s", m_strTipoPagamento, m_pAziendeSet->m_Banca);
      else
        str.Format("%s - BANCA %s - ABI %s CAB %s", m_strTipoPagamento, m_pAziendeSet->m_Banca, m_pAziendeSet->m_ABI, m_pAziendeSet->m_CAB);
    }
    pFieldValues->Add(str);
    // Numero e data fattura
    pFieldValues->Add("Fattura proforma");  // Tipo documento
    pFieldValues->Add("");                  // Numero
    str.Format("del %s", CTime::GetCurrentTime().Format("%d/%m/%y"));
    pFieldValues->Add(str);
  }
  else
  {
    // Per le fatture emesse prendo i dati dal recordset delle fatture
    pFieldValues->Add(m_pFattureEmesseSet->m_IDIntestatario);
    str = m_pFattureEmesseSet->m_RagioneSociale;
    str.Replace("&", "&&");
    pFieldValues->Add(str);
    pFieldValues->Add(m_pFattureEmesseSet->m_Indirizzo);
    str.Empty();
    if(!m_pFattureEmesseSet->m_CAP.IsEmpty())
      str = m_pFattureEmesseSet->m_CAP;
    if(!m_pFattureEmesseSet->m_Citta.IsEmpty())
    {
      str += " ";
      str += m_pFattureEmesseSet->m_Citta;
    }
    if(!m_pFattureEmesseSet->m_Provincia.IsEmpty())
    {
      str += " (";
      str += m_pFattureEmesseSet->m_Provincia; 
      str += ")";
    }
    pFieldValues->Add(str);
    // Partita IVA o codice fiscale
    if(!m_pFattureEmesseSet->m_P_IVA.IsEmpty())
    {
      str.Format("P.IVA    %s", m_pFattureEmesseSet->m_P_IVA);
      pFieldValues->Add(str);
    }
    else if(!m_pFattureEmesseSet->m_CodiceFiscale.IsEmpty())
    {
      str.Format("Cod.Fiscale    %s", m_pFattureEmesseSet->m_CodiceFiscale);
      pFieldValues->Add(str);
    }
    else
      pFieldValues->Add("");
    // Tipo pagamento
    if(!m_bRiba || (m_bRiba && m_pFattureEmesseSet->m_Banca.IsEmpty()))
    {
      str = m_strTipoPagamento;
      if(!m_pFattureEmesseSet->m_BancaAppoggio.IsEmpty())
      {
        if(m_pFattureEmesseSet->m_ABIAppoggio.IsEmpty() || m_pFattureEmesseSet->m_CABAppoggio.IsEmpty())
          str.Format("%s - Banca d'appoggio %s", m_strTipoPagamento, m_pFattureEmesseSet->m_BancaAppoggio);
        else
          str.Format("%s - Banca d'appoggio %s - ABI %s CAB %s", m_strTipoPagamento, m_pFattureEmesseSet->m_BancaAppoggio, m_pFattureEmesseSet->m_ABIAppoggio, m_pFattureEmesseSet->m_CABAppoggio);
      }
    }
    else
    {
      if(m_pFattureEmesseSet->m_ABI.IsEmpty() || m_pFattureEmesseSet->m_CAB.IsEmpty())
        str.Format("%s - BANCA %s", m_strTipoPagamento, m_pFattureEmesseSet->m_Banca);
      else
        str.Format("%s - BANCA %s - ABI %s CAB %s", m_strTipoPagamento, m_pFattureEmesseSet->m_Banca, m_pFattureEmesseSet->m_ABI, m_pFattureEmesseSet->m_CAB);
    }
    pFieldValues->Add(str);
    // Numero e data fattura  
    pFieldValues->Add(m_strTipoDocumento + " n.");
    str.Format("%d", m_pFattureEmesseSet->m_Numero);
    pFieldValues->Add(str);
    str.Format("del %s", m_pFattureEmesseSet->m_Data.Format("%d/%m/%y"));
    pFieldValues->Add(str);
  }
  // Numero pagina
  pFieldNames->Add("pagina");
  str.Format(" / %d", m_nNumPagine);
  pFieldValues->Add(str);
  // Verbali fatturati
  if(m_pVerbaliInfatturazione->m_TipoVerbale != VERB_PER_FATTURA && m_pVerbaliInfatturazione->m_TipoVerbale != VERB_PER_NOTACREDITO)
  {
    pFieldNames->Add("verbali");
    pFieldValues->Add(m_strProgressiviVerbali);
  }
  // Scadenza e importo
  if(!m_bPrintProForma && !m_pFattureEmesseSet->IsFieldNull(&m_pFattureEmesseSet->m_Scadenza))
  {
    pFieldNames->Add("scadenza");
    pFieldValues->Add(m_pFattureEmesseSet->m_Scadenza.Format("%d/%m/%y"));
  }
  pFieldNames->Add("totImporto");
  pFieldValues->Add(m_strTotaleFattura);
  // Totale imponibile
  pFieldNames->Add("importo");
  pFieldValues->Add(m_strImportoScontato);
  pFieldNames->Add("imponibile");
  pFieldValues->Add(m_strImponibile);
  // IVA
  pFieldNames->Add("aliquota");
  pFieldNames->Add("iva");
  if(!m_bPrintProForma)
    m_dAliquota = m_pFattureEmesseSet->m_Aliquota;
  if(m_dAliquota != 0)
  {
    str.Format("I.V.A.  %0.f %%", m_dAliquota);
    pFieldValues->Add(str);
  }
  else
    pFieldValues->Add("Esente I.V.A.");
  pFieldValues->Add(m_strIVA);
  // Spese di spedizione
  if(m_bSpedSelezionata)
  {
    pFieldNames->Add("spedizione");
    pFieldValues->Add("Esente Art.15*");
    pFieldNames->Add("spesespedizione");
    if(!m_bPrintProForma)
      m_dSpeseSpedizione = m_pFattureEmesseSet->m_Spese;
    Valuta spese(m_dSpeseSpedizione);
    pFieldValues->Add(spese.Format());
    pFieldNames->Add("notaSpedizione");
    pFieldValues->Add("*Trattasi di spese postali");
  }
  // Totale fattura
  pFieldNames->Add("totale");
  pFieldValues->Add(m_strTotaleFattura);
  // Sconto
  if(m_dSconto)
  {
    pFieldNames->Add("sconto");
    str.Format("Sconto fattura  %.2f%%", m_dSconto);
    pFieldValues->Add(str);
  }
  return FALSE;
}

BOOL CPrintPreviewFatture::ScanServizi(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
  CString str, str2;
  double dImporto = 0.;
  double dPrezzo = 0.;

  pFieldNames->RemoveAll();
  pFieldValues->RemoveAll();
  if(m_lCodiceVerbale != m_pVerbaliInfatturazione->m_Codice || m_pVerbaliInfatturazione->IsEOF())
  {
    // Maggiorazione
    if(m_bMaggiorazione)
    {
      pFieldNames->Add("descrizione");
      pFieldValues->Add("Maggiorazione del 50% per diritto procedura d'urgenza");
      Valuta maggiorazione(((double)m_nImportoVerbale / 2));
      pFieldNames->Add("importo");
      pFieldValues->Add(maggiorazione.Format(-1, TRUE));
      m_bMaggiorazione = FALSE;
      m_nImportoVerbale = 0;
      if(m_pVerbaliInfatturazione->IsEOF() && m_pServiziErogati->IsEOF())
        return FALSE;
      return TRUE;
    }
  }
  if(m_pVerbaliInfatturazione->IsEOF() && m_pServiziErogati->IsEOF())
  {
    m_lCodiceVerbale = 0;
    m_nImportoVerbale = 0;
    m_bMaggiorazione = FALSE;
    return FALSE;
  }
  if(m_lCodiceVerbale != m_pVerbaliInfatturazione->m_Codice)
  {
    m_lCodiceVerbale = m_pVerbaliInfatturazione->m_Codice;
    m_nImportoVerbale = 0;
    m_pServiziErogati->m_strFilter.Format("Verbale = %d", m_lCodiceVerbale);
    m_pServiziErogati->Requery();
    // Quando cambio verbale, prima dei servizi metto il verbale di riferimento
    // Verbale di riferimento
    if(m_pVerbaliInfatturazione->m_TipoVerbale != VERB_PER_FATTURA && m_pVerbaliInfatturazione->m_TipoVerbale != VERB_PER_NOTACREDITO)
    {
      pFieldNames->Add("descrizione");
      str.Format("VA %d/%d del %s - Cant.: %s", m_pVerbaliInfatturazione->m_ProgressivoParziale, m_pVerbaliInfatturazione->m_ProgressivoTotale, m_pVerbaliInfatturazione->m_DataAccettazione.Format("%d/%m/%y"), m_pVerbaliInfatturazione->m_Cantiere);
      str.Replace("\r\n", " ");
      pFieldValues->Add(str);
      // Maggiorazione
      if((m_pVerbaliInfatturazione->m_Urgenza) && (m_pVerbaliInfatturazione->m_Urgenza != 2))
        m_bMaggiorazione = TRUE;
      else
        m_bMaggiorazione = FALSE;
      if(m_pServiziErogati->IsEOF())
        m_pVerbaliInfatturazione->MoveNext();
      return TRUE;
    }
    if(m_pServiziErogati->IsEOF())
    {
      m_pVerbaliInfatturazione->MoveNext();
      if(m_pVerbaliInfatturazione->IsEOF() && !m_bMaggiorazione)
        return FALSE;
    }
    return TRUE;
  }
  if(m_lCodiceVerbale == m_pVerbaliInfatturazione->m_Codice)
  {
    // Codici
    pFieldNames->Add("codici");
    if(m_pServiziErogati->m_ID_Listino != ID_SERVIZI_NO_LISTINO)
      pFieldValues->Add(m_pServiziErogati->m_ID_Listino);
    else
      pFieldValues->Add("");
    // Descrizione
    pFieldNames->Add("descrizione");
    if(!m_pServiziErogati->m_Nome.IsEmpty())
      pFieldValues->Add(m_pServiziErogati->m_Nome);
    else
      pFieldValues->Add(m_pServiziErogati->m_Descrizione);
    // Per i servizi a prezzo zero non metto gli altri campi
    if(m_pServiziErogati->m_Prezzo != 0.)
    {
      // Quantità
      pFieldNames->Add("quantità");
      str.Format("%.2f", m_pServiziErogati->m_Quantita);
      pFieldValues->Add(str);
      // Prezzo
      pFieldNames->Add("prezzo");
      dPrezzo = m_pServiziErogati->m_Prezzo;
      Valuta prezzo(dPrezzo);
      pFieldValues->Add(prezzo.Format());
      // Sconto
      pFieldNames->Add("sconto");
      if(!m_pServiziErogati->IsFieldNull(&m_pServiziErogati->m_Sconto) && m_pServiziErogati->m_Sconto != 0)
      {
        str.Format("%.2f", m_pServiziErogati->m_Sconto);
        pFieldValues->Add(str);
      }
      else
        pFieldValues->Add("---");
      // Importo
      pFieldNames->Add("importo");
      dImporto = m_pServiziErogati->m_Prezzo * m_pServiziErogati->m_Quantita;
      if(!m_pServiziErogati->IsFieldNull(&m_pServiziErogati->m_Sconto))
        dImporto = dImporto - (dImporto * m_pServiziErogati->m_Sconto / 100);
      Valuta importo(dImporto);
      if(dImporto < 0)
        m_nImportoVerbale += (int)(dImporto * 100 - 0.5);
      else
        m_nImportoVerbale += (int)(dImporto * 100 + 0.5);
      pFieldValues->Add(importo.Format());  
    }
    m_pServiziErogati->MoveNext();
  }
  if(m_pServiziErogati->IsEOF())
  {
    m_pVerbaliInfatturazione->MoveNext();
    if(m_pVerbaliInfatturazione->IsEOF() && !m_bMaggiorazione)
      return FALSE;
  }
  return TRUE;
}

BOOL CPrintPreviewFatture::ScanPerServizio(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
  CString str;
  double dPrezzo, dImporto, dServizi;
  int    nImporto;
  
  pFieldNames->RemoveAll();
  pFieldValues->RemoveAll();

  if(!m_bVerbaliPrinted)
  {
    if(m_bMaggiorazione)
    {
      // Scrivo la maggiorazione
      pFieldNames->Add("descrizione");
      pFieldValues->Add("Maggiorazione del 50% per diritto procedura d'urgenza");
      Valuta maggiorazione(((double)m_nImportoVerbale / 2));
      pFieldNames->Add("importo");
      pFieldValues->Add(maggiorazione.Format(-1, TRUE));
      m_bMaggiorazione = FALSE;
      m_nImportoVerbale = 0;
      return TRUE;
    }
    // Stampo i verbali
    if(m_lCodiceVerbale != m_pVerbaliInfatturazione->m_Codice)
    {
      m_lCodiceVerbale = m_pVerbaliInfatturazione->m_Codice;
      m_nImportoVerbale = 0;
      if(m_pVerbaliInfatturazione->m_TipoVerbale != VERB_PER_FATTURA && m_pVerbaliInfatturazione->m_TipoVerbale != VERB_PER_NOTACREDITO)
      {
        pFieldNames->Add("descrizione");
        str.Format("VA %d/%d del %s - Cant.: %s", m_pVerbaliInfatturazione->m_ProgressivoParziale, m_pVerbaliInfatturazione->m_ProgressivoTotale, m_pVerbaliInfatturazione->m_DataAccettazione.Format("%d/%m/%y"), m_pVerbaliInfatturazione->m_Cantiere);
        str.Replace("\r\n", " ");
        pFieldValues->Add(str);
        m_bMaggiorazione = m_pVerbaliInfatturazione->m_Urgenza;
        if(!m_bMaggiorazione)
        {
          // Scorro il recordset fino al prossimo verbale
          while(!m_pVerbaliInfatturazione->IsEOF())
          {
            m_pVerbaliInfatturazione->MoveNext();
            if(m_lCodiceVerbale != m_pVerbaliInfatturazione->m_Codice)
              break;
          }
          return TRUE;
        }
        m_pServiziErogati->m_strFilter.Format("Verbale = %d", m_lCodiceVerbale);
        m_pServiziErogati->Requery();
      }
    }
    while(!m_pServiziErogati->IsEOF())
    {
      // Calcolo l'importo verbale per l'eventuale maggiorazione
      dImporto = m_pServiziErogati->m_Prezzo * m_pServiziErogati->m_Quantita;
      if(!m_pServiziErogati->IsFieldNull(&m_pServiziErogati->m_Sconto))
        dImporto = dImporto - (dImporto * m_pServiziErogati->m_Sconto / 100);
      Valuta importo(dImporto);
      if(dImporto < 0)
        m_nImportoVerbale += (int)(dImporto * 100 - 0.5);
      else
        m_nImportoVerbale += (int)(dImporto * 100 + 0.5);
      m_pServiziErogati->MoveNext();
    }
    while(!m_pVerbaliInfatturazione->IsEOF())
    {
      m_pVerbaliInfatturazione->MoveNext();
      if(m_lCodiceVerbale != m_pVerbaliInfatturazione->m_Codice)
        break;
    }
    // Passo alla stampa dei servizi
    if(m_pVerbaliInfatturazione->IsEOF() && !m_bMaggiorazione)
    {
      long codice(0);
      CString strFilter;
      for(SET_START(m_pVerbaliInfatturazione); !m_pVerbaliInfatturazione->IsEOF(); m_pVerbaliInfatturazione->MoveNext())
      {
        if(codice != m_pVerbaliInfatturazione->m_Codice)
        {
          str.Format("Verbale = %d OR ", m_pVerbaliInfatturazione->m_Codice);
          strFilter += str;
          codice = m_pVerbaliInfatturazione->m_Codice;
        }
      }
      strFilter.TrimRight(" OR ");
      m_pServiziErogati->m_strFilter = strFilter;
      m_pServiziErogati->m_strSort = "ID_Listino,Sconto";
      m_pServiziErogati->Requery();
      SET_START(m_pServiziErogati);
      m_bVerbaliPrinted = TRUE;
      dServizi = 0;
      m_lCodiceServizio = -1;
      m_lCodiceVerbale = 0;
    }
  }
  if(m_bVerbaliPrinted)
  {
    // Stampo i servizi
    if(m_lCodiceServizio != m_pServiziErogati->m_CodiceServizio)
    {
      // Cambio servizio
      CVerbaliServErogatiSet* pSet = new CVerbaliServErogatiSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
      dServizi = 0;
      m_lCodiceServizio = m_pServiziErogati->m_CodiceServizio;
      pSet->m_strFilter.Format("Verbale = VERBALI.Codice AND SERVIZI_EROGATI.Fattura = %d AND VERBALI.Fattura = %d AND SERVIZI_EROGATI.CodiceServizio = %d", m_lCodiceFattura, m_lCodiceFattura, m_lCodiceServizio);
      pSet->m_strSort = "ID_Listino,Sconto";
      pSet->Open();
      // Conto i servizi
      for(SET_START(pSet); !pSet->IsEOF(); pSet->MoveNext())
        dServizi += pSet->m_Quantita;
      // Descrizione
      pFieldNames->Add("descrizione");
      pFieldValues->Add(pSet->m_Descrizione);
      if(pSet->m_Prezzo != 0)
      {
        // Codici
        if(pSet->m_IDListino != ID_SERVIZI_NO_LISTINO)
        {
          pFieldNames->Add("codici");
          pFieldValues->Add(pSet->m_IDListino);
          str.Format("%.0f", dServizi);
        }
        else
          str.Format("%.1f", dServizi);
        // Quantità
        pFieldNames->Add("quantità");
        pFieldValues->Add(str);
        // Prezzo
        pFieldNames->Add("prezzo");
        dPrezzo = pSet->m_Prezzo;
        Valuta prezzo(dPrezzo);
        pFieldValues->Add(prezzo.Format());
        // Sconto
        pFieldNames->Add("sconto");
        if(!pSet->IsFieldNull(&pSet->m_Sconto) && pSet->m_Sconto)
        {
          str.Format("%.2f", pSet->m_Sconto);
          pFieldValues->Add(str);
        }
        else
          pFieldValues->Add("---");
        // Importo
        pFieldNames->Add("importo");
        dImporto = pSet->m_Prezzo * dServizi;
        if(!pSet->IsFieldNull(&pSet->m_Sconto))
          dImporto = dImporto - (dImporto * pSet->m_Sconto / 100);
        if(dImporto < 0)
          nImporto = (int)(dImporto * 100 - 0.5);
        else
          nImporto = (int)(dImporto * 100 + 0.5);
        Valuta importo((double)nImporto);
        pFieldValues->Add(importo.Format(-1, TRUE));  
      }
      pSet->Close();
      delete pSet;
    }
    while(!m_pServiziErogati->IsEOF())
    {
      m_pServiziErogati->MoveNext();
      if(m_lCodiceServizio != m_pServiziErogati->m_CodiceServizio)
        break;
    }
    if(m_pServiziErogati->IsEOF())
      return FALSE;
  }
  if(m_pVerbaliInfatturazione->IsEOF() && m_pServiziErogati->IsEOF())
    return FALSE;
  return TRUE;
}


void CPrintPreviewFatture::CalcolaTotale(void)
{
  double dImporto, dSconto, dImportoTotale;
  CString strDescrizione;
  int nImportoVerbale, nMaggiorazione, nImponibile;
  BOOL bUrgenza;
  nImportoVerbale = 0;
  dImportoTotale = 0;
  bUrgenza = FALSE;

  nImponibile = 0;
  for(SET_START(m_pVerbaliInfatturazione); !m_pVerbaliInfatturazione->IsEOF(); m_pVerbaliInfatturazione->MoveNext())
  {
    if((m_lCodiceFattura <= 0 && m_pVerbaliInfatturazione->m_InFatturazione == VERB_PROFORMA) || (m_lCodiceFattura && (!m_pVerbaliInfatturazione->IsFieldNull(&m_pVerbaliInfatturazione->m_NumeroFattura) && m_pVerbaliInfatturazione->m_NumeroFattura > 0)))
    {
      bUrgenza = m_pVerbaliInfatturazione->m_Urgenza;
      for(SET_START(m_pServiziErogati); !m_pServiziErogati->IsEOF(); m_pServiziErogati->MoveNext())
      {
        if(m_pServiziErogati->m_Verbale != m_pVerbaliInfatturazione->m_Codice)
          continue;
        dImporto = 0.;
       Valuta prezzo(m_pServiziErogati->m_Prezzo);
        dImporto = m_pServiziErogati->m_Prezzo * m_pServiziErogati->m_Quantita;
        // Sconto
        if(!m_pServiziErogati->IsFieldNull(&m_pServiziErogati->m_Sconto))
          dSconto = m_pServiziErogati->m_Sconto;
        else
          dSconto = 0;
        dImporto = dImporto - (dImporto * dSconto / 100);
        if(dImporto > 0)
          nImportoVerbale += (int)(dImporto * 100 + 0.5); 
        else
          nImportoVerbale += (int)(dImporto * 100 - 0.5);
        dImportoTotale += dImporto;
        Valuta importo(dImporto);
      }
      if(bUrgenza)
      {
        nMaggiorazione = (int)((double)nImportoVerbale / 2 + 0.5);
        nImportoVerbale += nMaggiorazione;
        Valuta maggiorazione((double)nMaggiorazione);
      }    
    }  
    nImponibile += nImportoVerbale;
    nImportoVerbale = 0;
  }
  Valuta imponibile((double)nImponibile);
  m_strImponibile = imponibile.Format(-1, TRUE);
  // Applico lo sconto fattura sul totale
  dImportoTotale = (double)nImponibile / 100;
  dImportoTotale -= dImportoTotale * m_dSconto / 100;
  int nImponibileScontato = (int)(dImportoTotale * 100 + 0.5);
  Valuta imponibileScontato((double)nImponibileScontato);
  m_strImportoScontato = imponibileScontato.Format(-1, TRUE);
  double dIVA = (dImportoTotale * m_dAliquota / 100);
  int nIVA = (int)(dIVA * 100 + 0.5);
  Valuta iva(nIVA);
  m_strIVA = iva.Format(-1, TRUE);
  int nTotaleFattura = nImponibileScontato + nIVA + (int)(m_dSpeseSpedizione * 100 + 0.5);
  Valuta totale(nTotaleFattura);
  m_strTotaleFattura = totale.Format(-1, TRUE);
}


void CPrintPreviewFatture::SincronizeData(void)
{
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CString str, strFilter;
  BOOL bSconto = FALSE;
  // Recordset delle fatture e dei verbali - servizi erogati
  if(!m_bPrintProForma)
  {
    m_pFattureEmesseSet->m_strFilter.Format("Codice = %d", m_lCodiceFattura);
    if(!m_pFattureEmesseSet->IsOpen())
      m_pFattureEmesseSet->Open();
    else
      m_pFattureEmesseSet->Requery();
    m_pVerbaliInfatturazione->m_strFilter.Format("Fattura = %ld", m_lCodiceFattura);
    m_pServiziErogati->m_strFilter.Format("Fattura = %ld", m_lCodiceFattura);
    m_lCodiceAzienda = m_pFattureEmesseSet->m_Intestatario;
  }
  else
  {
    if(m_lCodiceVerbale)
    {
      m_pVerbaliInfatturazione->m_strFilter.Format("Codice = %ld", m_lCodiceVerbale);
      m_pServiziErogati->m_strFilter.Format("Verbale = %ld", m_lCodiceVerbale);
    }
    else
    {
      m_pVerbaliInfatturazione->m_strFilter.Format("Fattura = 0 AND IntestatarioFattura = %ld", m_lCodiceAzienda);
      m_pVerbaliInfatturazione->m_strSort = "Codice";
      m_pServiziErogati->m_strFilter= "Fattura = 0";
    }
  }
  if(!m_pVerbaliInfatturazione->IsOpen())
    m_pVerbaliInfatturazione->Open();
  else
    m_pVerbaliInfatturazione->Requery();
  if(m_lCodiceVerbale <= 0)
  {
    long codice = 0;
    for(SET_START(m_pVerbaliInfatturazione); !m_pVerbaliInfatturazione->IsEOF(); m_pVerbaliInfatturazione->MoveNext())
    {
      if(codice != m_pVerbaliInfatturazione->m_Codice)
      {
        str.Format("Verbale = %d OR ", m_pVerbaliInfatturazione->m_Codice);
        strFilter += str;
        codice = m_pVerbaliInfatturazione->m_Codice;
      }
    }
    strFilter.TrimRight(" OR ");
    str.Format(" AND (%s)", strFilter);
    m_pServiziErogati->m_strFilter += str;
  }
  m_pServiziErogati->m_strSort = "Verbale,ID_Listino,Codice";
  m_pVerbaliInfatturazione->Requery();
  if(!m_pServiziErogati->IsOpen())
    m_pServiziErogati->Open();
  else
    m_pServiziErogati->Requery();
  for(SET_START(m_pServiziErogati); !m_pServiziErogati->IsEOF(); m_pServiziErogati->MoveNext())
  {
    if(!m_pServiziErogati->IsFieldNull(&m_pServiziErogati->m_Sconto) && m_pServiziErogati->m_Sconto)
    { 
      bSconto = TRUE;
      break;
    }
  }
  SET_START(m_pServiziErogati);
  if(bSconto)
    m_strLayout = "\\FattureSconto.prn";
  else
    m_strLayout = "\\Fatture.prn";
  // Costruisco la stringa dei verbali fatturati
  m_strProgressiviVerbali.Empty();
  m_lCodiceVerbale = 0;
  for(SET_START(m_pVerbaliInfatturazione); !m_pVerbaliInfatturazione->IsEOF(); m_pVerbaliInfatturazione->MoveNext())
  {
    if(m_lCodiceVerbale != m_pVerbaliInfatturazione->m_Codice)
    {
      str.Format("%d", m_pVerbaliInfatturazione->m_ProgressivoTotale);
      m_strProgressiviVerbali += str + " - ";
      m_lCodiceVerbale = m_pVerbaliInfatturazione->m_Codice;

      if ((m_pVerbaliInfatturazione->m_TipoVerbale == VERB_GEOLOGIA)
          && (m_strProgressiviVerbali.GetAt(m_strProgressiviVerbali.GetLength() - 1) != 'G'))
        m_strProgressiviVerbali += "G";
      else if ((m_pVerbaliInfatturazione->m_TipoVerbale == VERB_IN_CONCESSIONE)
          && (m_strProgressiviVerbali.GetAt(m_strProgressiviVerbali.GetLength() - 1) != 'C'))
        m_strProgressiviVerbali += "C";
      else if (((m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NON_IN_CONCESSIONE)  ||
								(m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NC_PROVE_DI_CARICO)	||
								(m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NC_CONGL_BITUMINOSI)	||
								(m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NC_INERTI)						||
								(m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NC_MONITORAGGI)			||
								(m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NC_VARIE)						||
								(m_pVerbaliInfatturazione->m_TipoVerbale == VERB_NC_GEOTECNICA))
								&& (m_strProgressiviVerbali.GetAt(m_strProgressiviVerbali.GetLength() - 1) != 'C'))
        m_strProgressiviVerbali += "NC";

      m_strProgressiviVerbali += " - ";
    }
  }
  m_strProgressiviVerbali.TrimRight(" - ");
  // Azienda
  m_pAziendeSet->m_strFilter.Format("Codice = %ld", m_lCodiceAzienda);
  if(!m_pAziendeSet->IsOpen())
    m_pAziendeSet->Open();
  else
    m_pAziendeSet->Requery();
  // TipoPagamento
  CTipiPagamentoSet* pPagamentiSet = new CTipiPagamentoSet(&pApp->m_db);
  if(m_bPrintProForma)
    pPagamentiSet->m_strFilter.Format("Codice = %ld", m_pAziendeSet->m_TipoPagamento);
  else
    pPagamentiSet->m_strFilter.Format("Codice = %ld", m_pFattureEmesseSet->m_TipoPagamento);
  pPagamentiSet->Open();
  m_strTipoPagamento = pPagamentiSet->m_Nome;
  // Se è una fattura emessa adesso o una fattuta proforma, verifico se il pagamento è una riba dal recordset dei pagamenti
  if(m_lCodiceFattura > 0 || m_bPrintProForma)
  {
    if(!pPagamentiSet->IsFieldNull(&pPagamentiSet->m_Allineamento) && pPagamentiSet->m_Allineamento != 0)
      m_bRiba = TRUE;
    else
      m_bRiba = FALSE;
  }
  else
  {
    // Se è una fattura vecchia, verifico se è una riba dal recordset fatture
    if(!m_pFattureEmesseSet->IsFieldNull(&m_pFattureEmesseSet->m_Scadenza))
      m_bRiba = TRUE;
    else
      m_bRiba = FALSE;
  }
  pPagamentiSet->Close();
}