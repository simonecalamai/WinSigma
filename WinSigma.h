// WinSigma.h : main header file for the WINSIGMA application
//

#if !defined(AFX_WINSIGMA_H__73C5E064_BB73_11D7_B754_0080AD70B2EE__INCLUDED_)
#define AFX_WINSIGMA_H__73C5E064_BB73_11D7_B754_0080AD70B2EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif


#include <float.h>
#include <math.h>
#include "resource.h"       // main symbols
#include "msmask.h"

#include "mysqld_error.h"
#include "AziendeSet.h"
#include "AziendeTurboSet.h"
#include "OperatoriSet.h"
#include "TipiMaterialeSet.h"
#include "TipiPagamentoSet.h"
#include "MarchiSet.h"
#include "MarchiTurboSet.h"
#include "TipiCertificatoSet.h"
#include "ListiniSet.h"
#include "CategorieSet.h"
#include "ServiziListinoSet.h"
#include "VerbaliSet.h"
#include "SerieSet.h"
#include "ProviniSet.h"
#include "SerieProviniSet.h"
#include "CertificatiSet.h"
#include "CertificatiVerbaliSet.h"
#include "ServiziErogatiSet.h"
#include "CategorieServiziSet.h"
#include "VerbaliServErogatiSet.h"
#include "FattureSet.h"
#include "AllTables.h"
#include "VerbSerProSet.h"
#include "ConnessioneDlg.h"
#include "LogSet.h"

/////////////////////////////////////////////////////////////////////////////
// CWinSigmaApp:
// See WinSigma.cpp for the implementation of this class
//
//#define WINSIGMA2

#define STR_VERSION							"4.6.1" 
#define STR_BUILDTIME   __TIMESTAMP__  
#define AZIENDE_BUFFER  1024
#define FATTURE_BUFFER  1024

#define MODE_VIEW                   0
#define MODE_NEW                    1
#define MODE_EDIT                   2
#define MODE_NEW_VERB               3
#define MODE_EDIT_PROVINI           4
#define MODE_NEW_GEO                5

#define TREEITEM_OPERATORI          1
#define TREEITEM_PAGAMENTI          2
#define TREEITEM_MATERIALI          3
#define TREEITEM_MARCHI             4

#define TREEITEM_SCADUTI            5
#define TREEITEM_INVIGORE           6
#define TREEITEM_INELABORAZIONE     7

#define TREEITEM_AZIENDERECENTI     8
#define TREEITEM_AZIENDEIMPORTANTI  9
#define TREEITEM_AZIENDEALFABETICA 10

#define TREEITEM_VERBALIPRECEDENTI 11
#define TREEITEM_VERBALIULTIMOMESE 12

#define TREEITEM_FATTUREDAEMETTERE 13
#define TREEITEM_FATTUREEMESSE     14

#define TREEITEM_VERBFATTPROFORMA  15

#define ARCHIVIO_VERBALI					  0
#define ARCHIVIO_CERTIFICATI			  1
#define ARCHIVIO_FATTURE					  2
#define STATISTICHE_PROVE					  3
#define STATISTICHE_FATTURATO			  4
#define TOTALE_FATTURATO						5
#define ESPORTAZIONE_CSV						6


#define TREELABEL_AZIENDERECENTI    "Recenti"
#define TREELABEL_AZIENDEIMPORTANTI "Importanti"
#define TREELABEL_AZIENDEALFABETICA "Alfabetica"

#define TREELABEL_OPERATORI       "Operatori"
#define TREELABEL_PAGAMENTI       "Tipi di pagamento"
#define TREELABEL_MATERIALI       "Tipi di materiale"
#define TREELABEL_MARCHI          "Marchi"

#define TREELABEL_SCADUTI         "Scaduti"
#define TREELABEL_INVIGORE        "In vigore"
#define TREELABEL_INELABORAZIONE  "In elaborazione"


#define TREELABEL_VERBALIPRECEDENTI  "Precedenti"
#define TREELABEL_VERBALIULTIMOMESE  "Ultimo mese"
#define TREELABEL_VERBALIFATTPROFORMA "Fatture proforma"

#define TREELABEL_FATTUREDAEMETTERE  "Fatture da emettere"
#define TREELABEL_FATTUREEMESSE      "Fatture emesse"

#define PRIV_AMMINISTRAZIONE      1
#define PRIV_FATTURAZIONE         2
#define PRIV_CERTIFICAZIONE       3
#define PRIV_ACCETTAZIONE         4

// definizioni per scadenze fatture
enum
{
	// diretto
	eScadFineMese					=			0,    // fine mese data fattura (default)
	eScad5Giorni					=			5,		// fine mese + 5 giorni	
	eScad10Giorni					=			10,		// fine mese + 10 giorni
	eScad15Giorni					=			15,		// fine mese + 15 giorni
	eScad20Giorni					=			20,		// fine mese + 20 giorni
	eScadDataFattura			=			50,		// data fattura
	// bonifico
	eScadBonFineMese			=			100,
	eScadBon5Giorni				=			105,
	eScadBon10Giorni			=			110,
	eScadBon15Giorni			=			115,
	eScadBon20Giorni			=			120,
	eScadBonDataFattura		=			150,
	// RI.BA.
	eScadRIBAFineMese			=		  200,
	eScadRIBA5Giorni			=			205,
	eScadRIBA10Giorni			=			210,
	eScadRIBA15Giorni			=			215,
	eScadRIBA20Giorni			=			220,
	eScadRIBADataFattura	=			250,
};

#if 0
#define RIBA_SCAD_STESSADATA      1
#define RIBA_SCAD_DECADE          2
#define RIBA_SCAD_FINEMESE        3
#define BON_SCAD_STESSADATA       4
#define BON_SCAD_DECADE           5
#define BON_SCAD_FINEMESE         6
#endif 

#define SERV_OGNI_SERIE           1
#define SERV_URGENZA              2
#define SPEDIZIONE                3
#define RITIRA                    4

#define PAG_RIBA                  1
#define PAG_CONTRASSEGNO          2
#define PAG_BONIFICO              3
#define PAG_RIM_DIRETTA           4

#define MAX_SERVIZI_PER_SERIE     6
#define MAX_SERIE_PER_CERT        6

// Tipi di verbale
#define VERB_NON_IN_CONCESSIONE   0     // Verbale senza prove in concessione
#define VERB_IN_CONCESSIONE       1     // Verbale con prove in concessione
#define VERB_VECCHIO_PROG         2     // Verbale creato col vecchio sistema, ma ancora da fatturare
#define VERB_PER_FATTURA          3     // Verbale nascosto per fatture che non fanno rif. a nessun verbale (tipo vendita di materiale)
#define VERB_PER_NOTACREDITO      4     // Verbale nascosto per nota di credito
#define VERB_GEOLOGIA             5     // Verbale per prove geologiche
#define VERB_NC_PROVE_DI_CARICO		6
#define VERB_NC_CONGL_BITUMINOSI	7
#define VERB_NC_INERTI						8
#define VERB_NC_MONITORAGGI				9
#define VERB_NC_VARIE							10
#define VERB_NC_GEOTECNICA				11

// Verbali in fatturazione
#define VERB_INFATT      1
#define VERB_FATT_SVERB  2
#define VERB_PROFORMA    3

// Tipi di documento in fatturazione
#define FATTURA       0
#define NOTA_CREDITO  1

// Verbale in inserimento
#define INSERIMENTO_NUOVO_VERBALE		"@@@Inserimento@@@nuovo@@@"

// ID per i servizi non di listino (per l'ordinamento)
#define ID_SERVIZI_NO_LISTINO    "ZZZ"

// Codice tipo servizio 
#define SERVIZIO_NON_CONC     0
#define SERVIZIO_CONCESSIONE  1
#define SERVIZIO_GEOLOGIA     2

// sezioni file .ini
#define GENERALE				"Generale"
#define INSTALLAZIONE		"Installazione"


// Nomi delle tabelle
#define AZIENDE             "AZIENDE"
#define VERBALI             "VERBALI"
#define TIPI_CERTIFICATO    "TIPI_CERTIFICATO"
#define LISTINI             "LISTINI"
#define CATEGORIE           "CATEGORIE"
#define SERVIZI_LISTINO     "SERVIZI_LISTINO"
#define SERVIZI_STANDARD    "SERVIZI_STANDARD"
#define SERIE               "SERIE"
#define FATTURE             "FATTURE"
#define CERTIFICATI         "CERTIFICATI"
#define SERVIZI_EROGATI     "SERVIZI_EROGATI"
#define PROVINI             "PROVINI"
#define OPERATORI           "OPERATORI"
#define OPERAZIONI          "OPERAZIONI"
#define TIPI_PAGAMENTO      "TIPI_PAGAMENTO"
#define TIPI_MATERIALE      "TIPI_MATERIALE"
#define PRODUTTORI          "PRODUTTORI"
#define TIPI_SCONTO         "TIPI_SCONTO"

// Stringhe per la stampa verbali
#define CONFIGURAZIONE          "Configurazione"
#define LABORATORIO							"Laboratorio"
#define RESPONSABILE						"Responsabile"
#define STAMPA_CONCESSIONE      "PrnConcessione"
#define STAMPA_NONCONCESSIONE   "PrnNonConcessione"
#define STAMPA_GEOLOGIA         "PrnGeologia"
#define TIPO_PAGAMENTO_DEFAULT  "TipoPagamentoDefault"
#define CODICE_CERT_BARRE       "CodiceCertBarre"
#define CALCOLO_CON_DECIMALI    "CalcoloConDecimali"

// Stringhe per l'inizializzazione dell'albero delle fatture emesse (file .ini)
#define FATTURAZIONE      "Fatturazione"
#define START_YEAR        "Start"
#define END_YEAR          "End"

// Strinhe per la notifica del blocco del documento
#define STR_BLOCCO_CERTIFICAZIONE(str) "Operazione non consentita!\n\nSono in corso operazioni sui certificati da parte dell'operatore: " + str
#define STR_BLOCCO_FATTURAZIONE(str) "Operazione non consentita!\n\nSono in corso operazioni di fatturazione da parte dell'operatore: " + str
#define STR_ISTRUZIONI_RIMOZIONE "\n\n(Per rimuovere un eventuale blocco errato utilizzare l'apposita funzione di menù)"
#define STR_BLOCCO_DOCUMENTO_INUSO(str) "Operazione non consentita!\n\nIl documento risulta in elaborazione da parte dell'operatore: " + str
#define STR_BLOCCO_DOCUMENTO_NUOVO(str) "Operazione non consentita!\n\nIl documento risulta in elaborazione da parte dell'operatore: " + str

// Gestione delle dimensioni della struttura e del cantiere
#define DIM_STR_CANTIERE				150//104 //128
#define DIM_MAX_STRUTTURA				60

// Definizioni relative ai servizi di listino
#define PER_PROVINO							0
#define PER_SERIE								1
#define NON_DEFINITO						2

#define NON_EMISSIONE						0
#define EMISSIONE								1
#define INCLUDE_EMISSIONE				2

#define NON_AGGIUNTIVO					0
#define AGGIUNTIVO							1
#define COMPRENSIVO							2

//#define STR_DEFAULT_ALIQUOTA_IVA	"21"  // da settembre 2011  
#define STR_DEFAULT_ALIQUOTA_IVA	"22"  // dal 1 ottobre 2013


// Costanti certificati
// Cubetti
#define DATA_SCADENZA_CUBETTI		45    // Cubetti DM2018 scadenza 45 giorni


#define SET_START(pSet)   (pSet->IsBOF() ? \
				                   pSet->IsEOF() ? 0 : pSet->MoveNext() : \
							             pSet->MoveFirst())

#define SINCRONIZE(pSet, cod) for(SET_START(pSet); !pSet->IsEOF(); pSet->MoveNext()) \
	if(pSet->m_Codice==cod) break; \
	ASSERT(!pSet->IsEOF())

typedef void (*EntryPointfuncPtr)(int argc, const char * argv);

extern const char* STR_MESI[];

MSG Spacciatore ();

class Valuta
{
  protected:
	  double m_fValue;
	public:
	  Valuta(double fValue) { m_fValue = fValue; };
		CString Format(int len = -1, BOOL bCentesimi = FALSE) 
		{ 
		  int  i, n; 
			char str[17];
      BOOL bNeg = FALSE;
      double fValAbs = m_fValue;
      
      if(m_fValue < 0)
      {
        fValAbs *= -1;
        bNeg = TRUE;
      }
      if(!bCentesimi)
        n = (int)(fValAbs * 100. + 0.5);
      else
        n = (int)fValAbs;
      for(i = 17; i && len;)
			{
			  switch(--i)
				{
				  case 16: str[i] = 0;
					  break;
				  case 13: str[i] = ',';
					  break;
					case  9:
					case  5: str[i] = '.';
					  break;
					default: 
					  if(i > 11 || n)
						{
						  str[i] = '0' + (n % 10);
							n /= 10;
						}
						else
						  str[i] = ' ';
						len--;
				}
			}
			while(str[i] == '.' || str[i] == ' ')
			  i++;
      CString strFormatted;
      if(!bNeg)
        strFormatted = CString(str + i);
      else
        strFormatted.Format("-%s", CString(str + i));
			return strFormatted;
		};
};

class CWinSigmaApp : public CWinApp
{
  /*---- attributi -----*/
	protected:
		BOOL    m_nMode;
		long    m_nUserCode;
		long    m_nUserPrivileges;
    CString m_strUserName;
		int     m_nFontWidth;
		CFont   m_FontCtrl;
		CBrush  m_BrushFocusBk;
	public:
		CDatabase m_db;
		CDatabase m_dbr;
		CString m_csDefaultConnect;   
		CString m_csUtente;
    bool m_bPrimaVolta;
		BYTE m_byDBRemoto;
		CString m_headerPrn;
		CString m_headerFatturePrn;
		CString m_headerVerbaliPrn;
  /*---- metodi -----*/
  public:
		~CWinSigmaApp();
	  BYTE IsDBRemoto();
    CConnessioneDlg m_dlg;
	  BOOL SetFatturaInUso(CFattureSet* pFattSet, BOOL libera = FALSE);
	  BOOL DisabilitaFatturazione(CString* strDaChi, BOOL disabilita = TRUE);
	  BOOL DisabilitaCertificazione(CString* strDaChi, BOOL disabilita = TRUE);
	  BOOL SetVerbaleInUso(long nCodice, BOOL libera = FALSE);
		CWinSigmaApp();
    /*---- Calcolo della scadenza dei pagamenti ----*/
    CTime GetScadenza(CTime data, int giorni, int allineamento);
		/*---- GDI da usare nei controlli -----*/
		CFont*  GetCtrlFont();
		int     GetFontWidth();
		CBrush* GetFocusBkBrush();
		/*---- directory corrente -----*/
		CString GetCurrentDirectory();
		/*---- utente corrente -----*/
		CString GetUserName();
		long    GetUserCode();
		long    GetUserPrivileges();
		/*---- gestione della modalità di editing -----*/
		WORD GetViewMode(void);
		void SetViewMode(WORD nMode);
		/*---- gestione delle transazioni -----*/
		BOOL BeginTrans(void);
		BOOL CommitTrans(void);
		BOOL Rollback(void);
		/*---- decodifica degli errori del db -----*/
		int  DecodeDBError(CString str);
		/*---- locking delle tabelle -----*/
		BOOL LockTable(CString strTable);
		BOOL UnlockTables();
		/*--- aggiornamento data ultimo rapporto ----*/
		BOOL UpdateRecent(long nCodAzienda);
		BOOL ReopenVerbale(long nCodVerbale);

		void ReloadTree(CString strLabel, long nCodice);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinSigmaApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CWinSigmaApp)
	afx_msg void OnAppAbout();
	afx_msg void OnHelpVersion();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINSIGMA_H__73C5E064_BB73_11D7_B754_0080AD70B2EE__INCLUDED_)
