// TrazioneProfilati2011.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "TrazioneProfilati2011.h"
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
// CTrazioneProfilati2011App

BEGIN_MESSAGE_MAP(CTrazioneProfilati2011App, CWinApp)
	//{{AFX_MSG_MAP(CTrazioneProfilati2011App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrazioneProfilati2011App construction

CTrazioneProfilati2011App::CTrazioneProfilati2011App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTrazioneProfilati2011App object

CTrazioneProfilati2011App theApp;


//////////////////////////////////////////////
// Implementazione delle funzioni da esportare


//////////////////////////////////////////////////////////////////////
// La funzione richiede che l'oggetto tabelle sia istanziato e che il 
// codSerie corrisponda alla serie in elaborazione

__declspec( dllexport ) int OpenDlg(long codSerie, CAllTables* tabelle, long* ultimoSperimentatore, CTime* pUltimaDataProve)
{
	CSerieSet* pSerieSet = tabelle->m_pSerieSet;
	pSerieSet->m_strFilter.Format("Codice = %d", codSerie);
	SAFETY_OPEN(pSerieSet);
	CVerbaliSet* pVerbaliSet = tabelle->m_pVerbaliSet;
	pVerbaliSet->m_strFilter.Format("Codice = %d", pSerieSet->m_Verbale);
	SAFETY_OPEN(pVerbaliSet);
	
	//------------ Determino la posizione serie e certificato e le info associate ----------//

	// Carico tutte le serie associate allo stesso verbale per aggiornare i dati
	// a quelle relative allo stesso certificato memorizzando le info certificato
	pSerieSet->m_strSort = "TipoCertificato, Codice";
	pSerieSet->m_strFilter.Format("Verbale = %d",pSerieSet->m_Verbale);
	pSerieSet->Requery();

	int posCertificato = 0;
	int posSerie = 0;
	CString osservazioni = "", sperimentatore = "", macchina = "";
	CTime dataProva;
	
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
			if( !pSerieSet->IsFieldNull(&pSerieSet->m_DataProva) )
				dataProva = pSerieSet->m_DataProva;
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
				||	pSerieSet->IsFieldNull(&pSerieSet->m_DataProva)
				||	pSerieSet->m_Osservazioni		!= osservazioni
				||	pSerieSet->m_Sperimentatore	!= sperimentatore
				||	pSerieSet->m_Macchina				!= macchina
				||  pSerieSet->m_DataProva			!= dataProva))
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

	// Il recordset delle serie è sincronizzato con quella in esame ma contiene 
	// tutte le serie associate al verbale di riferimento in ordine di inserimento

	CMainDlg dlg;
	dlg.m_pSerieSet						= pSerieSet;
	dlg.m_pProviniSet					= tabelle->m_pProviniSet;
	dlg.m_pOperatoriSet				= tabelle->m_pOperatoriSet;
	dlg.m_DataAccettazione		= tabelle->m_pVerbaliSet->m_DataAccettazione;
	dlg.m_pUltimoSper					= ultimoSperimentatore;
	dlg.m_pUltimaDataProve		= pUltimaDataProve;
	dlg.m_strPosizione.Format("%d/%d",posSerie,posCertificato);
	return dlg.DoModal();
}


//////////////////////////////////////////////////////////////////////////////////////
// La funzione si aspetta che i recordset usati siano sincronizzati con i valori opportuni.
// Riempie il CStringArray con due stringhe, la prima descrive le prove richieste, 
// la seconda il materiale consegnato.


__declspec( dllexport ) int LoadProveMateriale(CStringArray* stringhe, CAllTables* tabelle, CDWordArray* parySerieEliminate)
{
	CString prove, materiale, strTempMateriale;
	CSerieSet*						pSerieSet		= tabelle->m_pSerieSet;
	CTipiCertificatoSet*	pTCertSet		= tabelle->m_pTipiCertificatoSet;
	CVerbaliSet*					pVerbSet		= tabelle->m_pVerbaliSet;
	
	if( pSerieSet->IsEOF() || pSerieSet->m_TipoCertificato != pTCertSet->m_Codice)
		return IDNO;

	BOOL tutteEliminate = TRUE;
	int nProvini = 0;
	
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
		nProvini += pSerieSet->m_NumeroProvini;
		pSerieSet->MoveNext();
		}

	if(tutteEliminate)
		return IDNO;

	strTempMateriale.Format("%d %s", nProvini, MATERIALE);
	if( stringhe->GetSize() > 0 )
		{
		prove			= stringhe->GetAt(0);
		materiale = stringhe->GetAt(1);
		prove = prove + " - " + pTCertSet->m_ProvaA;
		// Se non è già stato inserito dalla ddl dedicata alla resilienza 
		if( materiale.Find(MATERIALE, 0) == -1)
			materiale = materiale + " - " + strTempMateriale;
		else
			{
			strTempMateriale = "+ " + strTempMateriale;
			materiale.Replace(MATERIALE, strTempMateriale);
			}
		stringhe->SetAt(0,prove);
		stringhe->SetAt(1,materiale);
		}
	else
		{
		stringhe->Add(pTCertSet->m_ProvaA);
		stringhe->Add(MATERIALE);
		}

	return IDYES;
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
	fieldNames->Add("macchina");
	str.Format("Macchina utilizzata: %s", pSerieSet->m_Macchina);
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
	fieldNames->Add("dataProve");
	fieldValues->Add(pSerieSet->m_DataProva.Format("%d/%m/%Y") );



//---------------	
	str = pSerieSet->m_Osservazioni;
	str.TrimLeft();
	str.TrimRight();
	if(str.GetLength() > 1 )
		{
		fieldNames->Add("osservazioniLabel");
		fieldValues->Add("Osservazioni");
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

	CString str;

	pFieldNames->RemoveAll();
  pFieldValues->RemoveAll();

	
	pFieldNames->Add("strutturaPrelievo");

	str = pSerieProviniSet->m_StrutturaPrelievo;
	if(primoCampo)
		pFieldValues->Add(str);
	else
	{
		str.TrimLeft();
		str.TrimRight();
		int lung = str.GetLength();
		int d = lung/4;
		for(int i = 0; i < lung; i++)
			if(i == d || i == lung - d - 1) 
				str.SetAt( i, '"');
			else
				str.SetAt( i, ' ');
		pFieldValues->Add(str);
	}

	

	switch(pDati->nVersione)
	{
		case 0:
		{
			pFieldNames->Add("dimensioni_provetta");
			pFieldNames->Add("sezione");
			pFieldNames->Add("snervamento");
			pFieldNames->Add("rottura");
			pFieldNames->Add("allungamento");

			/* arrotondamento a 1 cifra decimale */
			str.Format("%.1f x %.1f",pDati->larghezza, pDati->spessore);
			pFieldValues->Add(str);
      if(pDati->area < 100)
        str.Format("%.1f", pDati->area);
      else
        str.Format("%.0f", pDati->area);
			pFieldValues->Add(str);
			str.Format("%.0f",pDati->snervamento);
			pFieldValues->Add(str);
			str.Format("%.0f",pDati->rottura);
			pFieldValues->Add(str);
			str.Format("%.0f",pDati->allungamento);
			pFieldValues->Add(str);
		}
		break;
	  case 1:
      break;
	}
  return TRUE;
}
