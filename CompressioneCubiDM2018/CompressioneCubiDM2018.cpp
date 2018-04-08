// CompressioneCubiDM2018.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "CompressioneCubiDM2018.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW  
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CCompressioneCubiDM2018App

BEGIN_MESSAGE_MAP(CCompressioneCubiDM2018App, CWinApp)
	//{{AFX_MSG_MAP(CCompressioneCubiDM2018App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompressioneCubiDM2018App construction

CCompressioneCubiDM2018App::CCompressioneCubiDM2018App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCompressioneCubiDM2018App object

CCompressioneCubiDM2018App theApp;


//////////////////////////////////////////////
// Implementazione delle funzioni da esportare


//////////////////////////////////////////////////////////////////////
// La funzione richiede che l'oggetto tabelle sia istanziato e che il 
// codSerie corrisponda alla serie in elaborazione

__declspec( dllexport ) int OpenDlg(long codSerie, CAllTables* tabelle, long* ultimoSperimentatore, CTime* pUltimaDataProva)
{
  CString str;

	CSerieSet* pSerieSet = tabelle->m_pSerieSet;
	pSerieSet->m_strFilter.Format("Codice = %d", codSerie);
	SAFETY_OPEN(pSerieSet);
	CVerbaliSet* pVerbaliSet = tabelle->m_pVerbaliSet;
	pVerbaliSet->m_strFilter.Format("Codice = %d", pSerieSet->m_Verbale);
	SAFETY_OPEN(pVerbaliSet);

	//------------------ Sistemo il servizio aggiuntivo per le serie ----------//

	
	if( pSerieSet->IsFieldNull(&pSerieSet->m_ServAggiungibile) 
		|| pSerieSet->m_ServAggiungibile == 0 )
		{
		byte spianaturaTrovata = FALSE;

		CCategorieServiziSet* pCatServSet = tabelle->m_pCategorieServiziSet;
		CVerbaliSet*					pVerbSet = tabelle->m_pVerbaliSet;

		pVerbSet->m_strFilter.Format("Codice = %d",pSerieSet->m_Verbale);
		SAFETY_OPEN(pVerbSet);

		//Se compare un listino particolare verifico la presenza di un servizio aggiungibile
		long codListino = 0;
		if( !pVerbSet->IsFieldNull(&pVerbSet->m_ListinoParticolare) )
			codListino = pVerbSet->m_ListinoParticolare;

		CString queryJoin, query;
		queryJoin = "CATEGORIE.Codice = SERVIZI_LISTINO.Categoria AND ";

		query.Format("(Aggiuntivo = 1 AND Listino = %d AND Certificato = %d)", codListino, pSerieSet->m_TipoCertificato);
		pCatServSet->m_strFilter = queryJoin + query;
		SAFETY_OPEN(pCatServSet);

		// Se non ho trovato il servizio nel listino particolare lo cerco in quello generale
		if( pCatServSet->IsEOF() )
			{
			query.Format("(Aggiuntivo = 1 AND Listino = %d AND Certificato = %d)", pVerbSet->m_ListinoGenerale, pSerieSet->m_TipoCertificato);
			pCatServSet->m_strFilter = queryJoin + query;
			pCatServSet->Requery();
			}
		// Se l'ho trovato lo inserisco nella serie
		if( !pCatServSet->IsEOF() )
			{
			pSerieSet->Edit();
			pSerieSet->m_ServAggiungibile = pCatServSet->m_Codice;
			pSerieSet->Update();
			spianaturaTrovata = TRUE;
			}

			if(!spianaturaTrovata)
			{
			AfxMessageBox("Attenzione!!! \nIl servizio di spianatura non è stato correttamente configurato.");
			pSerieSet->Edit();
			pSerieSet->m_ServAggiungibile = 0;
			pSerieSet->Update();
			}
		}

	//------------ Determino la posizione serie e certificato e le info associate ----------//

	// Carico tutte le serie associate allo stesso verbale per aggiornare i dati
	// a quelle relative allo stesso certificato memorizzando le info certificato
	pSerieSet->m_strSort = "TipoCertificato, Codice";
	pSerieSet->m_strFilter.Format("Verbale = %d",pSerieSet->m_Verbale);
	pSerieSet->Requery();

	int posCertificato = 0;
	int posSerie = 0;
	CString osservazioni = "", sperimentatore = "", macchina = "";
	
	for(SET_START(pSerieSet); !pSerieSet->IsEOF(); pSerieSet->MoveNext() )
		{
		if( pSerieSet->m_NuovoCertificato )
			{
			posCertificato++;
			posSerie = 1;
			if( !pSerieSet->IsFieldNull(&pSerieSet->m_Osservazioni) )
				osservazioni = pSerieSet->m_Osservazioni;
			if( !pSerieSet->IsFieldNull(&pSerieSet->m_Sperimentatore) )
				sperimentatore = pSerieSet->m_Sperimentatore;
			if( !pSerieSet->IsFieldNull(&pSerieSet->m_Macchina) )
				macchina = pSerieSet->m_Macchina;
			}
		else
			posSerie++;

		if( pSerieSet->m_Codice == codSerie )
			{
			if(	 !pSerieSet->m_NuovoCertificato &&
				(		
					pSerieSet->IsFieldNull(&pSerieSet->m_Osservazioni)
				||	pSerieSet->IsFieldNull(&pSerieSet->m_Sperimentatore)
				||	pSerieSet->IsFieldNull(&pSerieSet->m_Macchina)
				||	pSerieSet->m_Osservazioni		!= osservazioni
				||	pSerieSet->m_Sperimentatore	!= sperimentatore
				||	pSerieSet->m_Macchina				!= macchina))
				{
				pSerieSet->Edit();
				pSerieSet->m_Osservazioni		= osservazioni;
				pSerieSet->m_Sperimentatore = sperimentatore;
				pSerieSet->m_Macchina				= macchina;
				pSerieSet->Update();
				}
			break;
			}
			
	}
	ASSERT( !pSerieSet->IsEOF() );
	//------------------------------------------------------------------//

	//--- Determino il numero di giorni previsti per la maturazione ---//
	tabelle->m_pTipiCertificatoSet->m_strFilter.Format("Codice = %d", pSerieSet->m_TipoCertificato);
	SAFETY_OPEN(tabelle->m_pTipiCertificatoSet);
	

	// Il recordset delle serie è sincronizzato con quella in esame ma contiene 
	// tutte le serie associate al verbale di riferimento in ordine di inserimento

	CMainDlg dlg;
	dlg.m_pSerieSet						= pSerieSet; 
	dlg.m_pProviniSet					= tabelle->m_pProviniSet;
	dlg.m_pServiziListinoSet	= tabelle->m_pServiziListinoSet;
	dlg.m_pOperatoriSet				= tabelle->m_pOperatoriSet;
	dlg.m_DataAccettazione		= pVerbaliSet->m_DataAccettazione;
	dlg.m_nGiorniMaturazione	= tabelle->m_pTipiCertificatoSet->m_Maturazione;
	dlg.m_pUltimoSper					= ultimoSperimentatore;
	dlg.m_pUltimaDataProva		= pUltimaDataProva;
	dlg.m_strPosizione.Format("%d/%d",posSerie,posCertificato);

  tabelle->m_pTipiCertificatoSet->m_strFilter = "Codice = 16";
  if (!tabelle->m_pTipiCertificatoSet->IsOpen())
    tabelle->m_pTipiCertificatoSet->Open();
  else
    tabelle->m_pTipiCertificatoSet->Requery();

  dlg.m_strLunghezza = tabelle->m_pTipiCertificatoSet->m_Dimensione1;
  dlg.m_strLarghezza = tabelle->m_pTipiCertificatoSet->m_Dimensione2;
  dlg.m_strAltezza   = tabelle->m_pTipiCertificatoSet->m_Dimensione3;

  dlg.m_strUMArea    = "(mm²)";

  
	return dlg.DoModal();
}



////////////////////////////////////////////////////////////////////
// Operazione di riempimento dei campi fields per la corretta stampa

__declspec( dllexport ) int RiempiCampi(long numCertificato, CAllTables* pTabelle,
																				CStringArray* fieldNames, CStringArray* fieldValues)
{

	//------------------ Apertura dei recordset utilizzati -----------------//

	CCertificatiVerbaliSet* pCertVerbSet = pTabelle->m_pCertificatiVerbaliSet;
	CString query;
	query.Format("VERBALI.Codice = CERTIFICATI.Verbale AND CERTIFICATI.Codice = %d",numCertificato);
	pCertVerbSet->m_strFilter = query;
	SAFETY_OPEN(pCertVerbSet);

	CSerieSet* pSerieSet = pTabelle->m_pSerieSet;
	pSerieSet->m_strFilter.Format("NuovoCertificato = 1 AND Certificato = %d", numCertificato);
	SAFETY_OPEN(pSerieSet);

	COperatoriSet* pOperatSet = pTabelle->m_pOperatoriSet;
	pOperatSet->m_strFilter = " Responsabile = 1 ";
	SAFETY_OPEN(pOperatSet);
	
	CString str, strTemp;
	
	//--- Gestione dei numeri di pagine ---//
	int pagine = 1;
	if(!pCertVerbSet->IsFieldNull(&pCertVerbSet->m_NumeroPagine))
		pagine = pCertVerbSet->m_NumeroPagine;

//---------------			
	fieldNames->Add("numeroCertificato");
	fieldNames->Add("dataCertificato");
	fieldNames->Add("numeroVerbale");
	fieldNames->Add("dataVerbale");

//---------------	
	str.Format("%d",pCertVerbSet->m_NumeroCertificato);
	fieldValues->Add(str);
	fieldValues->Add(pCertVerbSet->m_DataEmissione.Format("%d/%m/%Y"));
	str.Format("%d/%d", pCertVerbSet->m_ProgressivoParziale, pCertVerbSet->m_ProgressivoTotale);
	fieldValues->Add(str);
	fieldValues->Add(pCertVerbSet->m_DataAccettazione.Format("%d/%m/%Y"));


	//------------------ Dati forniti dal committente ----------------------------//
	if(pCertVerbSet->m_LetteraIncarico)
		{
		fieldNames->Add("etichettaIncarico");
		fieldValues->Add("Lettera di incarico");
		fieldNames->Add("letteraIncarico");
		fieldValues->Add(pCertVerbSet->m_NumLetteraIncarico);
		}

//---------------
	fieldNames->Add("richiedente");
	if( pCertVerbSet->IsFieldNull(&pCertVerbSet->m_NomeIntestatarioCertificato) )
		str = "";
	else
		str = pCertVerbSet->m_NomeIntestatarioCertificato;
  str.Replace("&", "&&");
	fieldValues->Add(str);

//---------------
	fieldNames->Add("indirizzoRichiedente");
	if( pCertVerbSet->IsFieldNull(&pCertVerbSet->m_IndirizzoIntCertificato) )
		str = "";
	else
		str = pCertVerbSet->m_IndirizzoIntCertificato;
	str.Replace("&", "&&");
	fieldValues->Add(str);

//---------------	
	fieldNames->Add("direttoreLavori");
	if( pCertVerbSet->IsFieldNull(&pCertVerbSet->m_DirettoreLavori) )
		str = "";
	else
		str = pCertVerbSet->m_DirettoreLavori;	
  str.Replace("&", "&&");
	fieldValues->Add(str);

//---------------	
	fieldNames->Add("impresaEsecutrice");
	if( pCertVerbSet->IsFieldNull(&pCertVerbSet->m_NomeImpresaRichiedente) )
		str = "";
	else
		str = pCertVerbSet->m_NomeImpresaRichiedente;	
  str.Replace("&", "&&");
	fieldValues->Add(str);
	
//---------------	
	fieldNames->Add("indirizzoImpresaEsecutrice");
	if( pCertVerbSet->IsFieldNull(&pCertVerbSet->m_IndirizzoImpresaRichiedente) )
		str = "";
	else
		str = pCertVerbSet->m_IndirizzoImpresaRichiedente;
	str.Replace("&", "&&");
	fieldValues->Add(str);

//---------------	
	fieldNames->Add("cantiere");
		if( pCertVerbSet->IsFieldNull(&pCertVerbSet->m_Cantiere) )
		str = "";
	else
		str = pCertVerbSet->m_Cantiere;	
  str.Replace("&", "&&");
	fieldValues->Add(str);

	
//------------------
	if(!pCertVerbSet->IsFieldNull(&pCertVerbSet->m_Proprietario) )
		{
		fieldNames->Add("etichettaProprietario");
		fieldValues->Add("Proprietario");
		fieldNames->Add("proprietario");
    str = pCertVerbSet->m_Proprietario;
    str.Replace("&", "&&");
		fieldValues->Add(str);
		}
	
	
//---------------
	str = "";
	fieldNames->Add("caratteristiche");
	if( !pSerieSet->IsFieldNull(&pSerieSet->m_Materiale) )
		str = pSerieSet->m_Materiale;
	str.Replace("&", "&&");
	fieldValues->Add(str);

			
//---------------	
	fieldNames->Add("domandaProve");

	if(pCertVerbSet->m_Sottoscritta)
		str = "sottoscritta dal D.L.";
	else 
		str = "non sottoscritta dal D.L.";

	fieldValues->Add(str);


//---------------	
	fieldNames->Add("macchina");
	
	str.Format("Macchina utilizzata: %s", pSerieSet->m_Macchina);
	str.Replace("&", "&&");
	fieldValues->Add(str);

//---------------	
	str = pSerieSet->m_Osservazioni;
	str.TrimLeft();
	str.TrimRight();
	if(str.GetLength() > 1 )
		{
		fieldNames->Add("osservazioniLabel");
		fieldValues->Add("Osservazioni:");
		fieldNames->Add("osservazioni");
		str.Replace("&", "&&");
		fieldValues->Add(str);
		}

	
//---------------	
	fieldNames->Add("responsabile");
	str = "";
	if(!pOperatSet->IsEOF())
		str.Format("%s %s %s", pOperatSet->m_Titolo, pOperatSet->m_Nome, pOperatSet->m_Cognome);
	fieldValues->Add(str);

	
//---------------	
	fieldNames->Add("sperimentatore");
	fieldValues->Add(pSerieSet->m_Sperimentatore);

	return pagine;
}


///////////////////////////////////////////////////////////////////////////////
// Funzione che riempie i campi degli array con i valori presenti nell'elemento
// nel quale è sincronizzato il recordset pSerieProvini ricevuto

__declspec( dllexport ) BOOL DatiProvino(CAllTables* pTabelle, CStringArray* pFieldNames, 
																				 CStringArray* pFieldValues, byte primoCampo, int numeroInterno)

{
	CSerieProviniSet* pSerieProviniSet = pTabelle->m_pSerieProviniSet;
	
	if( pSerieProviniSet->IsEOF() )
	  return FALSE;

	dati* pDati;
	pDati = (dati*)pSerieProviniSet->m_Risultati.GetData();

	CString str, struttura, nomeStruttura;
	double area			= (pDati->larg * pDati->lung);
	double rottura	= 0;

  rottura	= (pDati->caricoSp / area)*10 * 100;

	pFieldNames->RemoveAll();
  pFieldValues->RemoveAll();

//--- Gestione del campo struttura differenziata in base al numero di caratteri ---//
//--- Gestione dei campi da scrivere unicamente per il primo provino ---//
	struttura = pSerieProviniSet->m_StrutturaPrelievo;
//	struttura.Insert(0, " ");
	if(struttura.GetLength() > LIMITE_RIGA)
		nomeStruttura = "strutturaPrelievoLunga";
	else
		nomeStruttura = "strutturaPrelievoBreve";

	if( primoCampo )
		{
		  pFieldNames->Add(nomeStruttura);
			pFieldNames->Add("verbale_prelievo");
		  pFieldNames->Add("sigla");
		  pFieldNames->Add("dataPrelievo");
		  pFieldValues->Add(struttura);
//		  pFieldValues->Add(pSerieProviniSet->m_StrutturaPrelievo);
			pFieldValues->Add(pSerieProviniSet->m_VerbalePrelievo);
		  pFieldValues->Add(pSerieProviniSet->m_Sigla);
		  if( 
        !pSerieProviniSet->IsFieldNull(&pSerieProviniSet->m_DataPrelievo) 
			  && (pSerieProviniSet->m_DataPrelievo != 0) 
        )
			  pFieldValues->Add(pSerieProviniSet->m_DataPrelievo.Format("%d/%m/%Y"));	
		  else 
      {
			  if (pSerieProviniSet->m_strDataND.IsEmpty())
        {
          CString s("");
          s = "> 28 gg";
          pFieldValues->Add(s);
        }
        else
          pFieldValues->Add(pSerieProviniSet->m_strDataND);
      }
		}
	else
		{
		  pFieldNames->Add("strutturaPrelievoBreve");
			pFieldNames->Add("verbale_prelievo");
		  pFieldNames->Add("sigla");
		  pFieldNames->Add("dataPrelievo");

		  pFieldValues->Add("");
			pFieldValues->Add("");
		  pFieldValues->Add(pSerieProviniSet->m_Sigla2);
		  pFieldValues->Add(" \"  \" ");
		}
			

	switch(pDati->nVersione)
		{
		case 0:
			{
			pFieldNames->Add("lunghezza");
			pFieldNames->Add("larghezza");
			pFieldNames->Add("altezza");
			pFieldNames->Add("massa");
			pFieldNames->Add("tipoRottura");
			pFieldNames->Add("rottura");
			pFieldNames->Add("spianatura");
			
      str.Format("%.0f",pDati->lung);
			pFieldValues->Add(str);
      str.Format("%.0f",pDati->larg);
			pFieldValues->Add(str);
      str.Format("%.0f",pDati->alt);
      pFieldValues->Add(str);

      CString App("");

      App.Format("0.%03.0f",pDati->lung);
      double lung = atof(App);

			App.Format("0.%03.0f",pDati->larg);
      double larg = atof(App);

      App.Format("0.%03.0f",pDati->alt);
      double alt = atof(App);

      double Calc = pDati->massa / (lung * larg * alt);
      str.Format("%4.0f",Calc);


      pFieldValues->Add(str);

			str.Format("%d",pDati->tipoRott);
			pFieldValues->Add(str);
			str.Format("%.1f",rottura);
			pFieldValues->Add(str);

			if( !pSerieProviniSet->IsFieldNull(&pSerieProviniSet->m_ServAggiunto) 
				&& (pSerieProviniSet->m_ServAggiunto == pSerieProviniSet->m_ServAggiungibile) )
				pFieldValues->Add("A");
			else
				pFieldValues->Add("B");

			pFieldNames->Add("fc");
			str.Format("%.1f",pDati->caricoSp);
			pFieldValues->Add(str);
			
			}
			break;
		case 1:;
		};
	pFieldNames->Add("dataProva");
	if( primoCampo )
  {
		if(!pSerieProviniSet->IsFieldNull(&pSerieProviniSet->m_DataProva))
      pFieldValues->Add(pSerieProviniSet->m_DataProva.Format("%d/%m/%Y") );
    else
      pFieldValues->Add("- n. d. -" );
  }
  else
		pFieldValues->Add(" \"  \" ");
	
  return TRUE;
}


//////////////////////////////////////////////////////////////////////////////////////
// La funzione si aspetta che i recordset usati siano sincronizzati con i valori opportuni.
// Riempie il CStringArray con due stringhe, la prima descrive le prove richieste, 
// la seconda il materiale consegnato.

__declspec( dllexport ) int LoadProveMateriale(CStringArray* stringhe, CAllTables* tabelle, CDWordArray* parySerieEliminate)
{
	CString prove, materiale;
	CSerieSet*						pSerieSet		= tabelle->m_pSerieSet;
	CTipiCertificatoSet*	pTCertSet		= tabelle->m_pTipiCertificatoSet;
	CVerbaliSet*					pVerbSet		= tabelle->m_pVerbaliSet;
	CServiziListinoSet*   pServSet		= tabelle->m_pServiziListinoSet;
	CString strCommento;
  
	if( pSerieSet->IsEOF() || pSerieSet->m_TipoCertificato != pTCertSet->m_Codice)
		return IDNO;

	CString strMateriale = "", strMatNoCub, strMatConCub;
	strMatNoCub = "1 cubetto cls";
	strMatConCub = "1 cubetto cls con cubiera";
	int nProvConCub = 0, nProvNoCub = 0;

	BOOL tutteEliminate = TRUE;

  strCommento.Empty();
	while( !pSerieSet->IsEOF() && pSerieSet->m_TipoCertificato == pTCertSet->m_Codice)
	{
		for(int i=0; i<parySerieEliminate->GetSize(); i++)
			if(pSerieSet->m_Codice == (long)parySerieEliminate->GetAt(i))
				break;
		if(i!=parySerieEliminate->GetSize())
			{
			pSerieSet->MoveNext();
			continue;
			}

		tutteEliminate = FALSE;
    
		if(ConCubiera(pSerieSet, pServSet, strCommento) )
			nProvConCub += pSerieSet->m_NumeroProvini;
		else
			nProvNoCub += pSerieSet->m_NumeroProvini;
		pSerieSet->MoveNext();
	}

	if(tutteEliminate)
		return IDNO;
	
	if(nProvConCub > 1)
		strMatConCub.Format("%d cubetti cls %s", nProvConCub, strCommento);
	if(nProvNoCub > 1)
		strMatNoCub.Format("%d cubetti cls", nProvNoCub);

	if( (nProvNoCub > 0) && (nProvConCub>0) )
		strMateriale.Format("%d cubetti cls, %d %s", nProvNoCub + nProvConCub, nProvConCub, strCommento);
	else if ((nProvNoCub > 0))
		strMateriale = strMatNoCub;
	else if ((nProvConCub > 0))
		strMateriale = strMatConCub;

	// Verifico la presenza di stringhe nella descrizione
	if( stringhe->GetSize() > 0 )
		{
		prove			= stringhe->GetAt(0);
		materiale = stringhe->GetAt(1);
		prove = prove + " - " + pTCertSet->m_ProvaA;
		materiale = materiale + " - " + strMateriale;
		stringhe->SetAt(0,prove);
		stringhe->SetAt(1,materiale);
		}
	else
		{
		stringhe->Add(pTCertSet->m_ProvaA);
		stringhe->Add(strMateriale);		
		}
	
	return IDYES;
}


// Verifica se fra i servizi richiesti compare il servizio di sformatura
__declspec( dllexport ) BOOL ConCubiera(CSerieSet* pSerieSet, CServiziListinoSet* pServSet, CString& strCommento)
{	
	CString query = "", temp;
	if( !pSerieSet->IsFieldNull(&pSerieSet->m_Servizio1) )
	{
		temp.Format("Codice=%d", pSerieSet->m_Servizio1);
		if( query.IsEmpty() )
			query = temp;
		else
			query = query + " OR " + temp;
	}
	if( !pSerieSet->IsFieldNull(&pSerieSet->m_Servizio2) )
	{
		temp.Format("Codice=%d", pSerieSet->m_Servizio2);
		if( query.IsEmpty() )
			query = temp;
		else
			query = query + " OR " + temp;
	}
	if( !pSerieSet->IsFieldNull(&pSerieSet->m_Servizio3) )
	{
		temp.Format("Codice=%d", pSerieSet->m_Servizio3);
		if( query.IsEmpty() )
			query = temp;
		else
			query = query + " OR " + temp;
	}
	if( !pSerieSet->IsFieldNull(&pSerieSet->m_Servizio4) )
	{
		temp.Format("Codice=%d", pSerieSet->m_Servizio4);
		if( query.IsEmpty() )
			query = temp;
		else
			query = query + " OR " + temp;
	}
	if( !pSerieSet->IsFieldNull(&pSerieSet->m_Servizio5) )
	{
		temp.Format("Codice=%d", pSerieSet->m_Servizio5);
		if( query.IsEmpty() )
			query = temp;
		else
			query = query + " OR " + temp;
	}
	if( !pSerieSet->IsFieldNull(&pSerieSet->m_Servizio6) )
 	{
		temp.Format("Codice=%d", pSerieSet->m_Servizio6);
		if( query.IsEmpty() )
			query = temp;
		else
			query = query + " OR " + temp;
	}
	temp = query;
	query.Format("Commento is not null AND ( %s )", temp);
	pServSet->m_strFilter = query;
	SAFETY_OPEN(pServSet);
	if(!pServSet->IsEOF())
  {
    strCommento = pServSet->m_Commento;
		return TRUE;
  }
	
	return FALSE;
}

