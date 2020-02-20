// TrazionePiegamentoBarreB450_2010.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "afx.h"
#include "TrazionePiegamentoBarreB450_2010.h"
#include "MainDlg.h"

int m_nVariante;

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
//		For example:aderenza
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
// TrazionePiegamentoBarreB450_2010App

BEGIN_MESSAGE_MAP(CTrazionePiegamentoBarreB450_2010App, CWinApp)
	//{{AFX_MSG_MAP(CTrazionePiegamentoBarreB450_2010App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrazionePiegamentoBarreB450_2010App construction

CTrazionePiegamentoBarreB450_2010App::CTrazionePiegamentoBarreB450_2010App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTrazionePiegamentoBarreB450_2010App object

CTrazionePiegamentoBarreB450_2010App theApp;


//////////////////////////////////////////////
// Implementazione delle funzioni da esportare


//////////////////////////////////////////////////////////////////////
// La funzione richiede che l'oggetto tabelle sia istanziato e che il 
// codSerie corrisponda alla serie in elaborazione

__declspec( dllexport ) int OpenDlg(long codSerie, CAllTables* tabelle, long* ultimoSperimentatore, CTime* pUltimaDataProve)
{
	CSerieSet* pSerieSet = tabelle->m_pSerieSet;
	CTipiCertificatoSet*	pTCertSet		= tabelle->m_pTipiCertificatoSet;
	pSerieSet->m_strFilter.Format("Codice = %d", codSerie);
	SAFETY_OPEN(pSerieSet);
	CVerbaliSet* pVerbaliSet = tabelle->m_pVerbaliSet;
	pVerbaliSet->m_strFilter.Format("Codice = %d", pSerieSet->m_Verbale);
	SAFETY_OPEN(pVerbaliSet);
	
	//------------ Determino la posizione serie e certificato e le info associate ----------//

	CString osservazioni = pSerieSet->m_Osservazioni;

	// Carico tutte le serie associate allo stesso verbale per aggiornare i dati
	// a quelle relative allo stesso certificato memorizzando le info certificato

	pSerieSet->m_strSort = "TipoCertificato, Codice";
	pSerieSet->m_strFilter.Format("Verbale = %d",pSerieSet->m_Verbale);
	pSerieSet->Requery();

	int posCertificato = 0;
	int posSerie = 0;
	CString sperimentatore = "", macchina = "";
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
	dlg.m_pSerieSet	= pSerieSet;

	if(!pSerieSet->IsEOF())
	{
		pTCertSet->m_strFilter.Format("Codice = %d", pSerieSet->m_TipoCertificato);
		if(!pTCertSet->IsOpen())
			pTCertSet->Open();
		else
			pTCertSet->Requery();
		dlg.m_pTipoCertSet = pTCertSet;
	}

	dlg.m_pProviniSet					= tabelle->m_pProviniSet;
	dlg.m_pServiziListinoSet	= tabelle->m_pServiziListinoSet;
	dlg.m_pOperatoriSet				= tabelle->m_pOperatoriSet;
	dlg.m_pMarchiSet					= tabelle->m_pMarchiSet;
	dlg.m_DataAccettazione		= tabelle->m_pVerbaliSet->m_DataAccettazione;
	dlg.m_pUltimoSper					= ultimoSperimentatore;
	dlg.m_pUltimaDataProve		= pUltimaDataProve;
	dlg.m_strPosizione.Format("%d/%d",posSerie,posCertificato);
	return dlg.DoModal();
}


////////////////////////////////////////////////////////////
// Operazione di riempimento dei campi fields per la stampa

__declspec( dllexport ) int RiempiCampi(long numCertificato, CAllTables* pTabelle,
																				CStringArray* fieldNames, CStringArray* fieldValues)
{
	CString queryJoin, query,str,strTemp;

	//------------- Apertura dei recordset utilizzati -----------//
	CCertificatiVerbaliSet* pCertVerbSet	= pTabelle->m_pCertificatiVerbaliSet;
	CSerieProviniSet* pSerieProvSet				= pTabelle->m_pSerieProviniSet;
	CProviniSet* pProvSet									= pTabelle->m_pProviniSet;
	
	query.Format("VERBALI.Codice = CERTIFICATI.Verbale AND CERTIFICATI.Codice = %d",numCertificato);
	pCertVerbSet->m_strFilter = query;
	SAFETY_OPEN(pCertVerbSet);

	queryJoin = "SERIE.Codice = PROVINI.Serie";
	pSerieProvSet->m_strFilter.Format("%s AND NuovoCertificato = 1 AND Certificato = %d", queryJoin, numCertificato);
	SAFETY_OPEN(pSerieProvSet);

	COperatoriSet* pOperatSet = pTabelle->m_pOperatoriSet;
	pOperatSet->m_strFilter = " Responsabile = 1 ";
	SAFETY_OPEN(pOperatSet);

	//-----------------------------------------------------------//
	
	fieldNames->RemoveAll();
	fieldValues->RemoveAll();

	
	//--------------------- Intestazione sotto il titolo -------------------------//
	
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
	
//---------------	
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

#if 0
//---------------
	fieldNames->Add("dataprelievo");
	fieldValues->Add(pSerieProvSet->m_DataPrelievo.Format("%d/%m/%Y"));

	fieldNames->Add("verbaleprelievo");
	fieldValues->Add(pSerieProvSet->m_VerbalePrelievo);

	int i		= 1;
	int pos = -1;
	queryJoin = "SERIE.Codice = PROVINI.Serie";
	pSerieProvSet->m_strFilter.Format("%s And Certificato = %d" ,queryJoin, numCertificato);
	pSerieProvSet->Requery();
	CString csSiglaFornitore = pSerieProvSet->m_SiglaFornitore;
	str.Format("Campioni %s", csSiglaFornitore);
	for(; !pSerieProvSet->IsEOF(); pSerieProvSet->MoveNext())
	{
		if(pSerieProvSet->m_SiglaFornitore == csSiglaFornitore)
		{
			pos = str.Find(csSiglaFornitore);
			CString s;
			s.Format("%d - ",i);
			str.Insert(pos, s); 
		}
		else
		{
			csSiglaFornitore = pSerieProvSet->m_SiglaFornitore;
			CString app;
			app.Format("\r\nCampioni %s", csSiglaFornitore);
			str.Insert(str.GetLength(), app);
			pos = str.Find(csSiglaFornitore);
			CString s;
			s.Format("%d - ",i);
			str.Insert(pos, s); 
		}
		i++;
	}

	fieldNames->Add("siglafornitore");
	fieldValues->Add(str);
#endif

	queryJoin = "SERIE.Codice = PROVINI.Serie";
	pSerieProvSet->m_strFilter.Format("%s AND NuovoCertificato = 1 AND Certificato = %d", queryJoin, numCertificato);
	pSerieProvSet->Requery();

//---------------

	str = "";
	fieldNames->Add("caratteristiche");
	if( !pSerieProvSet->IsFieldNull(&pSerieProvSet->m_Materiale) )
		str = pSerieProvSet->m_Materiale;
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
	fieldValues->Add( pSerieProvSet->m_DataProva.Format("%d/%m/%Y") );

//---------------	
	if(pSerieProvSet->m_TipoProva < 2)
		{
		fieldNames->Add("richiestaPiegatura");
		fieldValues->Add("Prova di piegamento di Normativa non richiesta dalla D.L.");
		}
	
//--------------
	fieldNames->Add("macchina");
	str.Format("Macchina utilizzata: %s", pSerieProvSet->m_Macchina);
	str.Replace("&", "&&");
	fieldValues->Add(str);
	
//---------------	

	str = pSerieProvSet->m_Osservazioni;
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
	str.Replace("&", "&&");
	fieldValues->Add(str);


//--------------	

	fieldNames->Add("sperimentatore");
	fieldValues->Add(pSerieProvSet->m_Sperimentatore);

	
	int pagine = 0;
	if(pCertVerbSet->IsFieldNull(&pCertVerbSet->m_NumeroPagine))
		{
		//--- Se le pagine devono essere calcolate (debug andrea)---//	
		pSerieProvSet->m_strSort = "SERIE.Codice, SERIE.Marchio, PROVINI.Marchio";
		pSerieProvSet->m_strFilter.Format("%s AND Certificato = %d", queryJoin, numCertificato);	
		pSerieProvSet->Requery();
		
// -- Trasporto delle info sui marchi dalle serie ai provini -- //
// -- serve solo per le serie inserite precedentemente -- //
		BOOL cambiate = FALSE;
		for (; !pSerieProvSet->IsEOF(); pSerieProvSet->MoveNext() )	
		{
			if(pSerieProvSet->IsFieldNull(&pSerieProvSet->m_Marchio)
				&& !pSerieProvSet->IsFieldNull(&pSerieProvSet->m_MarchioSerie))
			{
				cambiate = TRUE;
				long debug = pSerieProvSet->m_CodiceSerie;
				long debug2 = pSerieProvSet->m_CodiceProvino;
				pProvSet->m_strFilter.Format("Codice = %d",pSerieProvSet->m_CodiceProvino);
				SAFETY_OPEN(pProvSet);
				pProvSet->Edit();
				pProvSet->m_Marchio = pSerieProvSet->m_MarchioSerie;
				pProvSet->Update();
			}
		}
		// Se ho cambiato dei dati riallineo il recordset al contenuto del database
		if(cambiate)
			pSerieProvSet->Requery();
// ------------------------------------------------------------ //

		int marchi = 0;
		long marchioInserito = 0;
		pSerieProvSet->m_strSort = "PROVINI.Marchio";
		pSerieProvSet->Requery();
		for (SET_START(pSerieProvSet); !pSerieProvSet->IsEOF(); pSerieProvSet->MoveNext() )
		{
			if(pSerieProvSet->m_Marchio !=0 && pSerieProvSet->m_Marchio!= marchioInserito)
			{
				marchioInserito = pSerieProvSet->m_Marchio;
				marchi++;
			}
		}
		// 2 marchi per pagina + la prima pagina:
    pagine = (marchi + 1) / 2 + 1;
	}
	else
		pagine = pCertVerbSet->m_NumeroPagine;

	str.Format("%d", pagine);

//--------------	
	fieldNames->Add("pagine");
	fieldValues->Add(str);
	
//--------------		
	fieldNames->Add("diPagine");
	fieldValues->Add(str);

//--------------

	/* norme e note */
	fieldNames->Add("norma_etichetta");
	fieldValues->Add("Norme");

  if (pCertVerbSet->m_Aderenza == 0)
	{
		fieldNames->Add("piegamento_noaderenza");
		fieldValues->Add("Piegamento");

		fieldNames->Add("mandrino_noaderenza");
		fieldValues->Add("Mandrino mm");

		fieldNames->Add("esito_noaderenza");
		fieldValues->Add("Esito");

		/* norme e note */
		fieldNames->Add("norma_valore");
		fieldValues->Add("Trazione e Piegamento UNI EN ISO 15630-1 / D.M. 14/01/08");
	}
	else
	{
		fieldNames->Add("aderenza");
		fieldValues->Add("Aderenza");

		fieldNames->Add("indice_aderenza");
		fieldValues->Add("Indice fr.");

		fieldNames->Add("piegamento");
		fieldValues->Add("Piegamento");

		fieldNames->Add("mandrino");
		fieldValues->Add("Mandrino mm");

		fieldNames->Add("esito");
		fieldValues->Add("Esito");

		/* norme e note */
		fieldNames->Add("norma_valore");
		fieldValues->Add("Trazione e Piegamento UNI EN ISO 15630-1 / D.M. 14/01/08 - ADERENZA UNI EN ISO 15630-1 / D.M. 14/01/08");
	}

	return pagine;
}



///////////////////////////////////////////////////////////////////////////////
// Funzione che riempie i campi degli array con i valori presenti nell'elemento
// nel quale è sincronizzato il recordset pSerieProvini ricevuto

__declspec( dllexport ) BOOL DatiProvino(CAllTables* pTabelle, CStringArray* pFieldNames, 
																				 CStringArray* pFieldValues, byte primoCampo, int numeroInterno, long CodiceCertificato)
{
	CSerieProviniSet* pSerieProviniSet = pTabelle->m_pSerieProviniSet;
	CProviniSet* pProvSet = pTabelle->m_pProviniSet;
	CTipiCertificatoSet*	pTCertSet		= pTabelle->m_pTipiCertificatoSet;
	CCertificatiSet * pCertificatiSet = pTabelle->m_pCertificatiSet;

	if( pSerieProviniSet->IsEOF() )
	  return FALSE;

	pTCertSet->m_strFilter.Format("Codice = %d", pSerieProviniSet->m_TipoCertificato);
	if(!pTCertSet->IsOpen())
		pTCertSet->Open();
	else
		pTCertSet->Requery();
	m_nVariante = pTCertSet->m_Variante;

	// -- Variabili d'appoggio --//
	CString str;
	double ftfy = 0;
	double fyfyk = 0;
	double massaLineare = 0;
	double sezEffettiva	= 0;
	double sezNominale	= 0;
	double snervamento	= 0;
	double rotturaRelativa = 0;
	double allungamentoPerc = 0;

	pFieldNames->RemoveAll();
	pFieldValues->RemoveAll();

	// -- conversione del blob nella struttura dati apposita --//
	dati* pDati;
	pDati = (dati*)pSerieProviniSet->m_Risultati.GetData();


	// --------  dati Generici serie  --------//
	double fiNominale = pSerieProviniSet->m_Dimensione1;
//------------------
	pFieldNames->Add("numeroInterno");
	pFieldNames->Add("fiNominale");

	str.Format("%d",numeroInterno);
	pFieldValues->Add(str);

	str.Format("%.0f", fiNominale);
	pFieldValues->Add(str);
	//------------------ Dati provini -------------------//
			
	switch(pDati->nVersione)
	{
		case 0:
		{
//-----------------------------	
			// Calcoli per la Snervamento effettiva
			sezNominale = (fiNominale/2) * (fiNominale/2) * PI_GRECO;

			// Si prendono solamente 3 cifre
			CString str("");		
			str.Format("%f", sezNominale);
			int idx = str.Find(".", 0);	
			if (idx < 2)
			{
				str.Delete(5, str.GetLength() - 5);
				sezNominale = atof(str);
				str.Format("%1.2f", sezNominale);
			}
			else if (idx < 3)
			{
				str.Delete(6, str.GetLength() - 6);
				sezNominale = atof(str);
				str.Format("%2.1f", sezNominale);
			}
			else
				str.Format("%3.0f", sezNominale);
			sezNominale = atof(str);
			pFieldNames->Add("sezioneNominale");
			pFieldValues->Add(str);

			pFieldNames->Add("sezioneEffettiva");
			pFieldNames->Add("massa");
			pFieldNames->Add("snervamento");
			pFieldNames->Add("rottura");
			pFieldNames->Add("fynom");
			pFieldNames->Add("ftfy");
			pFieldNames->Add("allungamento");

			if(pSerieProviniSet->m_TipoProva==1 || pSerieProviniSet->m_TipoProva==3)
			{
				massaLineare			= pDati->peso / pDati->lunghezza;
				sezEffettiva			= massaLineare/PESO_SPECIFICO * 1000;

//        if(!pSerieProviniSet->m_Checked)
        {
            // Se non vanno fatti i calcoli con i decimali, ricalcolo la sezione effettiva
    			if(sezEffettiva>100)
    			{
            if(!pSerieProviniSet->m_Checked)
    				  sezEffettiva = floor(sezEffettiva + 0.5);
    				str.Format("%.0lf",sezEffettiva);
    			}
    			else if(sezEffettiva>10)
    			{
            if(!pSerieProviniSet->m_Checked)
      				sezEffettiva = floor((sezEffettiva * 10) + 0.5)/10;
    				str.Format("%.1lf",sezEffettiva);
    			}
    			else
    			{
            if(!pSerieProviniSet->m_Checked)
      				sezEffettiva = (floor( (sezEffettiva*100) + 0.5 ))/100 ;
    				str.Format("%.2lf",sezEffettiva);
    			}
        }
				snervamento				= pDati->snervamento/sezNominale * 1000;						
				rotturaRelativa		= pDati->rottura/sezNominale * 1000;

				allungamentoPerc = 0;
				allungamentoPerc = pDati->allungamento + (rotturaRelativa / 2000);

				fyfyk							= snervamento / pSerieProviniSet->m_Snervamento;
				ftfy 							= rotturaRelativa / snervamento;

				pFieldValues->Add(str);
				str.Format("%.3lf",massaLineare);
				pFieldValues->Add(str);
				str.Format("%.0lf",snervamento);
				pFieldValues->Add(str);
				str.Format("%.0lf",rotturaRelativa);
				pFieldValues->Add(str);

				str.Format("%.2lf",fyfyk);
				pFieldValues->Add(str);

				str.Format("%.2lf",ftfy);
				pFieldValues->Add(str);
				str.Format("%.1lf",allungamentoPerc);
				pFieldValues->Add(str);
			}
			else
			{
				str = "n.r.";
				for(int i=0; i<7; i++)
					pFieldValues->Add(str);
			}
//-----------------------------	
			// Controlla se deve essere o meno visualizzata il campo Aderenza
			pCertificatiSet->m_strFilter.Format("Codice = %d", CodiceCertificato);
			if(!pCertificatiSet->IsOpen())
			{
				pCertificatiSet->Open();
			}
			else
			{
				pCertificatiSet->Requery();
			}

			if(pCertificatiSet->m_Aderenza == 1) 
			{
				pFieldNames->Add("aderenza");
				pFieldNames->Add("mandrino");
				pFieldNames->Add("esito");

				if(pSerieProviniSet->m_TipoProva < 2)
				{
					str = "n.r.";
					pFieldValues->Add(str);
					pFieldValues->Add(" ");
					pFieldValues->Add(str);
				}
				else
				{	
					str.Format("%.3f",pDati->aderenza);
					pFieldValues->Add(str);
					str.Format("%d",pDati->mandrino);
					pFieldValues->Add(str);
					pDati->esito ? str="POS" : str="NEG";
					pFieldValues->Add(str);
				}
			}
			else if(pCertificatiSet->m_Aderenza == 0)
			{
				pFieldNames->Add("mandrino_noaderenza");
				pFieldNames->Add("esito_noaderenza");
				if(pSerieProviniSet->m_TipoProva < 2)
				{
					str = "n.r.";
					pFieldValues->Add(" ");
					pFieldValues->Add(str);
				}
				else
				{	
					str.Format("%d",pDati->mandrino);
					pFieldValues->Add(str);
					pDati->esito ? str="POS" : str="NEG";
					pFieldValues->Add(str);
				}
			}
		}
		break;
	};

  return TRUE;
}




//////////////////////////////////////////////////////////////
// Stampa dell'allegato con le immagini dei produttori
// riceve il codice relativo al marchi della serie precedente
// ed il recordset sincronizzato con la serie in elaborazione


__declspec( dllexport ) BOOL StampaAllegato(CString* fileLayout, CAllTables* tabelle, 
																						CStringArray* fieldNames, CStringArray* fieldValues, CStringArray* marchiFiles, 
																						int* pContaProvini, BOOL* Duplicato, CTime* DataDuplicato)
{	
	CSerieProviniSet* pSerieProvSet = tabelle->m_pSerieProviniSet;
	COperatoriSet * pOperatSet = tabelle->m_pOperatoriSet;

	//int contaProvini = *pContaProvini;
	int numeropagina = *pContaProvini;
	CMemFile		mFile;
	CBMPObject  bmpObject;
	long				codMarchio = pSerieProvSet->m_Marchio;

	*fileLayout = "allegatoFerriSingolo.prn";

	//---------- Apertura dei recordset utilizzati ------------------//
	CCertificatiVerbaliSet* pCertVerbSet	= tabelle->m_pCertificatiVerbaliSet;
	CMarchiSet*							pMarchiSet		= tabelle->m_pMarchiSet;

	CString queryJoin, query, str;
	queryJoin = "VERBALI.Codice = CERTIFICATI.Verbale";

	query.Format("CERTIFICATI.Codice = %d", pSerieProvSet->m_Certificato);
	pCertVerbSet->m_strFilter.Format("%s AND %s",queryJoin, query);
	SAFETY_OPEN(pCertVerbSet);

	codMarchio = 0;
	if(!pSerieProvSet->IsFieldNull(&pSerieProvSet->m_Marchio) )
		codMarchio = pSerieProvSet->m_Marchio;

	pMarchiSet->m_strFilter.Format("Codice = %d", codMarchio);
	SAFETY_OPEN(pMarchiSet);
	//-----------------------------------------------------------------//


	//-----------------------------------------------------------------//

//-----------------
	fieldNames->Add("responsabile");
	str = "";
	if(!pOperatSet->IsEOF())
		str.Format("%s %s %s", pOperatSet->m_Titolo, pOperatSet->m_Nome, pOperatSet->m_Cognome);
	str.Replace("&", "&&");
	fieldValues->Add(str);

//-----------------
	fieldNames->Add("numeroCertificato");
	str.Format("%d", pCertVerbSet->m_NumeroCertificato);
	fieldValues->Add(str);

//-----------------
	fieldNames->Add("dataCertificato");
	str = pCertVerbSet->m_DataEmissione.Format("%d/%m/%Y");
	fieldValues->Add(str);

//-----------------
	fieldNames->Add("numeroVerbale");
	str.Format("%d/%d",pCertVerbSet->m_ProgressivoParziale, pCertVerbSet->m_ProgressivoTotale);
	fieldValues->Add(str);

//-----------------
	fieldNames->Add("dataVerbale");
	str = pCertVerbSet->m_DataAccettazione.Format("%d/%m/%Y");
	fieldValues->Add(str);

//-----------------
	fieldNames->Add("sperimentatore");
	fieldValues->Add(pSerieProvSet->m_Sperimentatore);

  if (*Duplicato == TRUE)
  {
    //-----------------
	    fieldNames->Add("duplicato");
      str.Format("DUPLICATO del %s",DataDuplicato->Format("%d/%m/%Y"));
	    fieldValues->Add(str);
  }

	// Conta i provini rileva le dimensioni e verifica se il processo è finito
	CString strProvini = "", temp, strFi;
	CString strProvini2 = "", strFi2="";
	CDWordArray aryMarchi, aryFi, aryFi2;

	int  iMarchio, iFi, iProvino;
	
	for(iProvino = 1; !pSerieProvSet->IsEOF(); iProvino++)
	{
    // controllo se il marchio l'ho gia' incontrato
    for(iMarchio = 0; iMarchio < aryMarchi.GetSize(); iMarchio++)
		   if(aryMarchi[iMarchio] == (DWORD)pSerieProvSet->m_Marchio)
			   break;

		if(iMarchio == aryMarchi.GetSize())
		{
			// non l'ho trovato: lo aggiungo
			aryMarchi.Add(pSerieProvSet->m_Marchio);

			pMarchiSet->m_strFilter.Format("Codice = %d", pSerieProvSet->m_Marchio);
			pMarchiSet->Requery();
		}

    if(iMarchio == numeropagina * 2)
		{
			if(strProvini.IsEmpty())
			{

        //inserisco i dati del marchio
				strProvini.Format("%d", iProvino);
				
				fieldNames->Add("lblprovino");
				fieldValues->Add("Provini");
				// inserisco i campi del primo marchio
				fieldNames->Add("primaEtichetta");
				fieldValues->Add("Campioni");

				if(pMarchiSet->IsEOF())
				{
					fieldNames->Add("nonRilevabile");
					fieldValues->Add("NON RILEVABILE");
				}
				else
        {
					fieldNames->Add("etichettaProduttore");
					fieldValues->Add("Produttore");

					fieldNames->Add("produttore");
					fieldValues->Add(pMarchiSet->m_Produttore);

					fieldNames->Add("etichettaStabilimento");
					fieldValues->Add("Stabilimento");

					fieldNames->Add("stabilimento");
					fieldValues->Add(pMarchiSet->m_Stabilimento);

					fieldNames->Add("etichettaDescrizione");
					fieldValues->Add("Tipo di acciaio");

					fieldNames->Add("descrizione");
					fieldValues->Add(pMarchiSet->m_Descrizione);
        }
				//----------- Salvataggio della immagine sul file -----------//
				if(pMarchiSet->IsEOF() || pMarchiSet->IsFieldNull(&pMarchiSet->m_Immagine))
					bmpObject.New(0, 0, NULL);
				else
				{
    			mFile.Attach(pMarchiSet->m_Immagine.GetData(), pMarchiSet->m_Immagine.GetSize());
					bmpObject.Open(&mFile);
					mFile.Close();
				}
	   		bmpObject.Save("marchio1.bmp");
				bmpObject.Close();
			}
		  else
			{
				temp.Format(", %d", iProvino);
				strProvini += temp;
			}

			// cerco il diametro
			for(iFi = 0; iFi < aryFi.GetSize(); iFi++)
				if(aryFi[iFi] == (DWORD)pSerieProvSet->m_Dimensione1)
					break;
				
				if(iFi == aryFi.GetSize())
				{
					// non l'ho trovato: lo aggiungo
					aryFi.Add((DWORD)pSerieProvSet->m_Dimensione1);
					
					if(strFi.IsEmpty())
						strFi.Format("Ø %d mm", (DWORD)pSerieProvSet->m_Dimensione1);
					else
					{
						strFi.TrimRight(" mm");						
						temp.Format(", %d mm", (DWORD)pSerieProvSet->m_Dimensione1);
						strFi += temp;
					}
				}
		}


		if(iMarchio == numeropagina * 2 + 1)
		{
		  if(strProvini2.IsEmpty())
			{
				strProvini2.Format("%d", iProvino);
				
				fieldNames->Add("lblprovino");
				fieldValues->Add("Provini");

				// inserisco le etichette del secondo marchio
				fieldNames->Add("primaEtichetta2");
				fieldValues->Add("Campioni");

				if(pMarchiSet->IsEOF())
				{
					fieldNames->Add("nonRilevabile2");
					fieldValues->Add("NON RILEVABILE");
				}
				else
        {
					fieldNames->Add("etichettaProduttore2");
					fieldValues->Add("Produttore");

				  fieldNames->Add("produttore2");
    			fieldValues->Add(pMarchiSet->m_Produttore);

					fieldNames->Add("etichettaStabilimento2");
					fieldValues->Add("Stabilimento");

					fieldNames->Add("stabilimento2");
					fieldValues->Add(pMarchiSet->m_Stabilimento);

					fieldNames->Add("etichettaDescrizione2");
					fieldValues->Add("Tipo di acciaio");

					fieldNames->Add("descrizione2");
				  fieldValues->Add(pMarchiSet->m_Descrizione);

        }
				//----------- Salvataggio della immagine sul file -----------//
				if(pMarchiSet->IsEOF() || pMarchiSet->IsFieldNull(&pMarchiSet->m_Immagine))
					bmpObject.New(0, 0, NULL);
				else
				{
    			mFile.Attach(pMarchiSet->m_Immagine.GetData(), pMarchiSet->m_Immagine.GetSize());
					bmpObject.Open(&mFile);
					mFile.Close();
				}
	   		bmpObject.Save("marchio2.bmp");
				bmpObject.Close();
			}
			else
			{
				temp.Format(", %d", iProvino);
				strProvini2 += temp;
			}

			// cerco il diametro
			for(iFi = 0; iFi < aryFi2.GetSize(); iFi++)
				if(aryFi2[iFi] == (DWORD)pSerieProvSet->m_Dimensione1)
					break;
				
				if(iFi == aryFi2.GetSize())
				{
					// non l'ho trovato: lo aggiungo
					aryFi2.Add((DWORD)pSerieProvSet->m_Dimensione1);
					
					if(strFi2.IsEmpty())
						strFi2.Format("Ø %d mm", (DWORD)pSerieProvSet->m_Dimensione1);
					else
					{
						strFi.TrimRight(" mm");	
						temp.Format(", %d mm", (DWORD)pSerieProvSet->m_Dimensione1);
						strFi2 += temp;
					}
				}
		}

		pSerieProvSet->MoveNext();
	}

//-----------------
	fieldNames->Add("primoCampo");
	fieldValues->Add(strFi);

	fieldNames->Add("secondoCampo");
	fieldValues->Add(strProvini);

	fieldNames->Add("primoCampo2");
	fieldValues->Add(strFi2);

	fieldNames->Add("secondoCampo2");
	fieldValues->Add(strProvini2);
	
    // controllo se c'e' anche il secondo marchio
	if(numeropagina * 2 + 1 < aryMarchi.GetSize())
   	*fileLayout = "allegatoFerriDoppio.prn";
	else
		*fileLayout = "allegatoFerriSingolo.prn";

	if((numeropagina + 1) * 2 < aryMarchi.GetSize())
		return TRUE;

	return FALSE;
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
	CServiziListinoSet*		pServSet		= tabelle->m_pServiziListinoSet;

	if( pSerieSet->IsEOF() || pSerieSet->m_TipoCertificato != pTCertSet->m_Codice)
		return IDNO;

	
	//------------ Materiale e prove richieste ------------------//

	CMainDlg dlg;
	CString strProve = "";
	byte proveRichieste = 0;
	
	CString strMateriale = "" , strFi = "", strNum = "";
	int nProvini = 0;
	strMateriale = "";
	double fi = -1;

	BOOL tutteEliminate = TRUE;
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
		
		if( pSerieSet->m_NuovoCertificato )
			proveRichieste = max( proveRichieste, dlg.ProveRichieste(pServSet, pSerieSet) );

		nProvini += pSerieSet->m_NumeroProvini;
		if( fi != pSerieSet->m_Dimensione1 )
			{
			fi = pSerieSet->m_Dimensione1;
			if(strFi.IsEmpty())
				strFi.Format("Ø %.0f", fi);
			else
				strFi.Format(", %.0f", fi);
			strMateriale = strMateriale + strFi;
			}
		pSerieSet->MoveNext();
		}

	if(tutteEliminate)
		return IDNO;

	strNum.Format("%d", nProvini);
	if(nProvini==1)
		strMateriale = strNum + " ferro " + strMateriale;
	else
		strMateriale = strNum + " ferri " + strMateriale;

	//----------------Prove richieste ------------------//
	switch(proveRichieste)
		{
		case(1): strProve = pTCertSet->m_ProvaA;
			break;
		case(2): strProve = pTCertSet->m_ProvaB;
			break;
		case(3): strProve.Format("%s - %s", pTCertSet->m_ProvaA, pTCertSet->m_ProvaB);
			break;
		}
	
	//Aggiungo alle stringhe se sono presenti o le inserisco 
	if( stringhe->GetSize() > 0 )
		{
		prove			= stringhe->GetAt(0);
		materiale = stringhe->GetAt(1);
		prove = prove + " - " + strProve;
		materiale = materiale + " - " + strMateriale;
		stringhe->SetAt(0,prove);
		stringhe->SetAt(1,materiale);
		}
	else
		{
		stringhe->Add(strProve);
		stringhe->Add(strMateriale);
		}
	
	return IDYES;
}
