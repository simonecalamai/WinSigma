// WinSigma.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "WinSigma.h"

#include <direct.h>

#include "XFormView.h"
#include "WinSigmaDoc.h"
#include "MainFrm.h"
#include "AziendeView.h"
#include "Configurazione.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

MSG Spacciatore ()
{
	MSG msg;
	while (::PeekMessage(&msg,NULL,0,0,PM_REMOVE))
  {
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
    
    if (((CWinSigmaApp*)AfxGetApp())->m_dlg.m_bOkPressed == true)
    {
      ((CWinSigmaApp*)AfxGetApp())->m_dlg.m_ctrlProgressLoad.SetPos(
                              ((CWinSigmaApp*)AfxGetApp())->m_dlg.m_ctrlProgressLoad.GetPos() + 7);
      
      ((CWinSigmaApp*)AfxGetApp())->m_dlg.m_ctrlProgressLoad.RedrawWindow();
    }
	}

  return msg;
}

////////////////////////////////////////////////////////////////////////////
// CWinSigmaApp

BEGIN_MESSAGE_MAP(CWinSigmaApp, CWinApp)
	//{{AFX_MSG_MAP(CWinSigmaApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_HELP_VERSION, OnHelpVersion)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinSigmaApp construction

CWinSigmaApp::CWinSigmaApp()
{
  m_nMode = FALSE;
  m_bPrimaVolta = true;
	m_byDBRemoto = 1;
	m_headerPrn = "header.prn";
	m_headerFatturePrn = "headerfatture.prn";
}

CWinSigmaApp::~CWinSigmaApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWinSigmaApp object

CWinSigmaApp theApp;

const char* STR_MESI[] = {"Gennaio", "Febbraio", "Marzo", 
                          "Aprile",  "Maggio",   "Giugno",
										   	  "Luglio",  "Agosto",   "Settembre",
											    "Ottobre", "Novembre", "Dicembre"};

const int FINE_MESE[]						= {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int FINE_MESE_BISESTILE[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

#define DURATA_MESE 30

////////////////////////////////////////////////////////////////////////////
// CWinSigmaApp initialization

BOOL CWinSigmaApp::InitInstance()
{ 
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

  free((void*)m_pszProfileName);
  char* pChar = (char*)malloc(256);
#ifdef WINSIGMA2
  strcpy(pChar, (LPCSTR)(GetCurrentDirectory() + "\\WinSigma2.ini"));
#else
  strcpy(pChar, (LPCSTR)(GetCurrentDirectory() + "\\WinSigma.ini"));
#endif
  m_pszProfileName = pChar;


  LoadStdProfileSettings();  // Load standard INI file options (including MRU)

  m_nFontWidth = GetProfileInt("Impostazioni", "Font", 6);
  m_FontCtrl.CreateFont(15, m_nFontWidth, 0, 0, FW_NORMAL,
                         0, 0, 0, DEFAULT_CHARSET,
                         OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                         DEFAULT_QUALITY, DEFAULT_PITCH,
                         "Arial");
  m_BrushFocusBk.CreateSolidBrush(RGB(0x80, 0xFF, 0x80));
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CWinSigmaDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CAziendeView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	CString dbName;
	int instCode = GetProfileInt(GENERALE, INSTALLAZIONE, 0);   // default WinSigma FI
	int dbgLI = GetProfileInt(GENERALE, "DebugLI", 0);   // debug sigma etruria
	// Imposta la stringa di connessione
	switch(instCode)
	{
		case 0:  // WinSigma FI
			dbName.Format("WinSigma");
			m_csDefaultConnect.Format("ODBC;UID=dbuser;PWD=49sigma03");
			m_headerPrn = GetProfileString("Impostazioni", "HdrSigma", "header.prn");
			m_headerFatturePrn = GetProfileString("Impostazioni", "HdrFattureSigma", "headerfatture.prn");
			m_headerVerbaliPrn = GetProfileString("Impostazioni", "HdrVerbaliSigma", "headerverbali.prn");
			break;

		case 1:	// WinSigma LI
			if(dbgLI > 0)
			{
				dbName.Format("winsigmali");
				m_csDefaultConnect.Format("ODBC;UID=dbuser;PWD=49sigma03");
			}
			else
			{
				dbName.Format("WinSigma");
				m_csDefaultConnect.Format("ODBC;UID=dbuser;PWD=59sigma03");
			}
			m_headerPrn = GetProfileString("Impostazioni", "HdrSigmaE", "headerSE.prn");
			m_headerFatturePrn = GetProfileString("Impostazioni", "HdrFattureSigmaE", "headerfattureSE.prn");
			m_headerVerbaliPrn = GetProfileString("Impostazioni", "HdrVerbaliSigmaE", "headerverbaliSE.prn");
			break;

		case 2:	// WinSigmaDue FI
			dbName.Format("WinSigma2");
			m_csDefaultConnect.Format("ODBC;UID=dbuser;PWD=49sigma03");
			m_headerPrn = GetProfileString("Impostazioni", "HdrSigma2", "headerS2.prn");
			m_headerFatturePrn = GetProfileString("Impostazioni", "HdrFattureSigma2", "headerFattureS2.prn");
			m_headerVerbaliPrn = GetProfileString("Impostazioni", "HdrVerbaliSigma", "headerverbali.prn");
			break;
	}

  // prova ad aprire la connessione con i dati
#ifdef WINSIGMA2
//	if(!m_db.Open("WinSigma2", FALSE, FALSE, m_csDefaultConnect, TRUE))
	if(!m_db.Open(dbName, FALSE, FALSE, m_csDefaultConnect, TRUE))
#else
//	if(!m_db.Open("WinSigma", FALSE, FALSE, m_csDefaultConnect, TRUE))
	if(!m_db.Open(dbName, FALSE, FALSE, m_csDefaultConnect, TRUE))
#endif	
	{
	  AfxMessageBox("Connessione alla base dati fallita."); 
	  return FALSE;
	}

	m_byDBRemoto = GetProfileInt("Configurazione", "DBRemoto", 1);
	if(m_byDBRemoto == 1)
	{
		// apre la connessione dati al db remoto
	#ifdef WINSIGMA2
		if(!m_dbr.Open("WinSigma", FALSE, FALSE, m_csDefaultConnect, TRUE))
	#else
		if(!m_dbr.Open("WinSigma2", FALSE, FALSE, m_csDefaultConnect, TRUE))
	#endif	
		{
			AfxMessageBox("Connessione alla base dati remota fallita."); 
			return FALSE;
		}
	}

  //Controlla se ci sono malfunzionamenti hardware nel server
  CString str;

  CLogSet log;
  log.Open();
  if (!log.IsEOF())
  {
    str = log.m_LOG_EVENT_DESCRIPTION;
    //str.Insert(str.GetLength(), " ");
    //str.Insert(str.GetLength(), log.m_LOG_EVENT_DESCRIPTION);
    str.Insert(str.GetLength(), "\nContattare il fornitore del software");
    AfxMessageBox(str,MB_OK|MB_ICONSTOP); 
  }
  log.Close();
  //CConnessioneDlg dlg;
  //mostra il dialogo per connettersi al database nell'host
	//if(m_dlg.DoModal() == IDCANCEL)
	//  return FALSE;

  m_dlg.Create(IDD_DIALOG_CONNESSIONE);
  ShowWindow(m_dlg.m_hWnd,SW_SHOW);

  while (m_dlg.m_bOkPressed == false)
  {
    if (((CWinSigmaApp*)AfxGetApp())->m_bPrimaVolta)
      Spacciatore();
    if (m_dlg.m_bCancelPressed == true)
      return FALSE;
  }
	
	m_nUserCode       = m_dlg.m_nOperatore;
	m_nUserPrivileges = m_dlg.m_nPrivilegi;
  m_strUserName     = m_dlg.m_strOperatore;

  // Dispatch commands specified on the command line
  if (!ProcessShellCommand(cmdInfo))
		return FALSE;

  // Change extension for help file
  CString strHelpFile = m_pszHelpFilePath;
  strHelpFile.Replace("Debug","html");
  strHelpFile.Replace(".HLP", ".chm");
  free((void*)m_pszHelpFilePath);
  m_pszHelpFilePath = _tcsdup(strHelpFile);

#ifdef WINSIGMA2	
  if(m_nUserCode)
	  str.Format("WinSigmaDUE v. %s - %s", STR_VERSION, m_dlg.m_strOperatore);
	else
	  str.Format("WinSigmaDUE v. %s - %s", STR_VERSION, STR_BUILDTIME);
#else
  if(m_nUserCode)
	  str.Format("WinSigma v. %s - %s", STR_VERSION, m_dlg.m_strOperatore);
	else
	  str.Format("WinSigma v. %s - %s", STR_VERSION, STR_BUILDTIME);
#endif
	((CMainFrame*)m_pMainWnd)->RepopulateTrees();
	((CMainFrame*)m_pMainWnd)->SetWindowText(str);

	// Lettura dati azienda
	CConfigurazione config;
	m_csIdPaese = config.Read("IdPaese");
	m_csDenominazione = config.Read("Denominazione");
	m_csPartitaIVA = config.Read("PartitaIVA");
	m_csRegimeFiscale = config.Read("RegimeFiscale");
	m_csIndirizzo = config.Read("Indirizzo");
	m_csNumeroCivico = config.Read("NumeroCivico");
	m_csCAP = config.Read("CAP");
	m_csComune = config.Read("Comune");
	m_csProvincia = config.Read("Provincia");
	m_csNazione = config.Read("Nazione");

		// Iscrizione REA
	m_csUfficioREA = config.Read("UfficioREA");
	m_csNumeroREA = config.Read("NumeroREA");
	m_csCapitaleSociale = config.Read("CapitaleSociale");
	m_csSocioUnico = config.Read("SocioUnico");
	m_csStatoLiquidazione = config.Read("StatoLiquidazione");

	// Dati trasmissione fattura XML
	m_csIdCodiceTrasmittente = config.Read("IdCodiceTrasmittente");
	m_csTipologiaFileXML = config.Read("TipologiaFileXML");
	m_csEstensioneXML = config.Read("EstensioneXML");
	m_csXMLFolder = config.Read("XMLFolder");
	m_csXMLHeader = config.Read("XMLHeader");

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


CTime CWinSigmaApp::GetScadenza(CTime data_fattura, int giorni_prima_scad, int allineamento)
{
  int giornoScadenza, meseScadenza, annoScadenza;
  int mesi_prima_scad = giorni_prima_scad / DURATA_MESE;
  int giorno = data_fattura.GetDay();
  int mese = data_fattura.GetMonth();
  int anno = data_fattura.GetYear();

	// calcolo mese/anno scadenza
	meseScadenza = mese + mesi_prima_scad;
  annoScadenza = anno + (meseScadenza-1)/12;
	if(meseScadenza > 12) meseScadenza %= 12;

	// controllo bisestile
	BOOL bBisestile = ((annoScadenza%4 == 0) && ((annoScadenza%100 != 0) || (annoScadenza%400 == 0))); 

	// calcolo allineamento
	if(allineamento >= eScadRIBAFineMese) allineamento -= eScadRIBAFineMese;
	else if(allineamento >= eScadBonFineMese) allineamento -= eScadBonFineMese;
  // calcolo giorno scadenza con eventuale correzione bisestile e di allineamento
  switch(allineamento)
  {
		case eScadFineMese:
		default:
			giornoScadenza = FINE_MESE[meseScadenza];
			if(meseScadenza == 2 && bBisestile) giornoScadenza++;
			break;

		case eScad5Giorni:
		case eScad10Giorni:
		case eScad15Giorni:
		case eScad20Giorni:
			meseScadenza++; 
		  annoScadenza += (meseScadenza-1)/12;
			if(meseScadenza > 12) meseScadenza %= 12;
			giornoScadenza = allineamento;
			break;

		case eScadDataFattura:
			giornoScadenza = giorno;
			switch(meseScadenza)
			{
				case 4:
				case 6:
				case 9:
				case 11:
					if(giorno == 31)
						giornoScadenza = 30;
					break;

				case 2:
					if(giorno > 28)
						giornoScadenza = 28 + (bBisestile ? 1 : 0);
					break;

			}
			break;
  }
  return CTime(annoScadenza, meseScadenza, giornoScadenza, 0, 0, 0);
}



CFont* CWinSigmaApp::GetCtrlFont()
{
  return &m_FontCtrl;
}

int CWinSigmaApp::GetFontWidth()
{
  return m_nFontWidth;
}


CBrush* CWinSigmaApp::GetFocusBkBrush()
{
  return &m_BrushFocusBk;
}

CString CWinSigmaApp::GetCurrentDirectory()
{
  char buffer[128];

	return _getcwd(buffer, sizeof(buffer) - 1);
}

CString CWinSigmaApp::GetUserName()
{
  return m_strUserName;
}

long CWinSigmaApp::GetUserCode()
{
  return m_nUserCode;
}

long CWinSigmaApp::GetUserPrivileges()
{
  return m_nUserPrivileges;
}

WORD CWinSigmaApp::GetViewMode(void)
{
  return m_nMode;
}

void CWinSigmaApp::SetViewMode(WORD nMode)
{
  switch(m_nMode = nMode)
	{
	  case MODE_NEW:
	    ((CMainFrame*)m_pMainWnd)->EditMode(ID_NUOVO);
			break;
		case MODE_EDIT:
    	((CMainFrame*)m_pMainWnd)->EditMode(ID_MODIFICA);
			break;
		case MODE_EDIT_PROVINI:
    	((CMainFrame*)m_pMainWnd)->EditMode(ID_DATI_PROVINI);
			break;
    case MODE_NEW_VERB:
    	((CMainFrame*)m_pMainWnd)->EditMode(ID_NUOVO_VERBALE);
			break;
    case MODE_NEW_GEO:
    	((CMainFrame*)m_pMainWnd)->EditMode(ID_NUOVO_GEOLOGIA);
      break;
		default:
			((CMainFrame*)m_pMainWnd)->EditMode(-1);
			break;
  }
}

void CWinSigmaApp::ReloadTree(CString strLabel, long nCodice)
{
	((CMainFrame*)m_pMainWnd)->ReloadTree(strLabel, nCodice);
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_csVersion;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_csVersion = _T("");
#ifdef WINSIGMA2
	m_csVersion.Format("WinSigmaDUE %s %s Copyright (C) 2003-2016 by Quadrante s.n.c.", STR_VERSION, STR_BUILDTIME);
#else
	m_csVersion.Format("WinSigma %s %s Copyright (C) 2003-2016 by Quadrante s.n.c.", STR_VERSION, STR_BUILDTIME);
#endif
	//}}AFX_DATA_INIT
} 
 
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_STATIC_VERSION, m_csVersion);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
#ifdef WINSIGMA2
	SetWindowText("Informazioni su WinSigmaDUE");	
#endif
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// App command to run the dialog
void CWinSigmaApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CWinSigmaApp message handlers

BOOL CWinSigmaApp::BeginTrans(void)
{
  if(m_db.IsOpen())
	  return m_db.BeginTrans();
	return FALSE;
}

BOOL CWinSigmaApp::CommitTrans(void)
{
  if(m_db.IsOpen())
	  return m_db.CommitTrans();
	return FALSE;
}

BOOL CWinSigmaApp::Rollback(void)
{
  if(m_db.IsOpen())
	  return m_db.Rollback();
	return FALSE;
}

int CWinSigmaApp::DecodeDBError(CString str)
{
  int n = str.Find("Native:");

	n += strlen("Native:");
	if (str.GetLength() >= n)
		return atoi(str.Mid(n));
	else
		return 0;
}

BOOL CWinSigmaApp::LockTable(CString strTable)
{
/*
  CString strSql;

	strSql.Format("LOCK TABLES %s write;", strTable);
	try
	{
	  m_db.ExecuteSQL(strSql);
	}
	catch(CDBException* e)
	{
		CString str = e->m_strError;
		//AfxMessageBox(str);
		return FALSE;
	}
*/
	return TRUE;
} 

BOOL CWinSigmaApp::UnlockTables(void)
{
//	m_db.ExecuteSQL("UNLOCK TABLES");
  return TRUE;
}

BOOL CWinSigmaApp::UpdateRecent(long nCodAzienda)
{
  CString strSql;

	strSql.Format("UPDATE AZIENDE SET DataUltimoRapporto = '%s' WHERE Codice = %d;",
	              CTime::GetCurrentTime().Format("%Y-%m-%d"), nCodAzienda);
  m_db.ExecuteSQL(strSql);
	return TRUE;
}

BOOL CWinSigmaApp::ReopenVerbale(long nCodVerbale)
{
  CString strSql;

	strSql.Format("UPDATE VERBALI SET DataChiusura = NULL WHERE Codice = %d;", nCodVerbale);
  m_db.ExecuteSQL(strSql);
	strSql.Format("UPDATE VERBALI SET Annullato = 0 WHERE Codice = %d;", nCodVerbale);
  m_db.ExecuteSQL(strSql);
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////////////
// La funzione abilita e disabilita a possibiltà di modifica da parte di altri utenti.
// Se si sceglie di disabilitare la possibiltà di modifica:
//		se il verbale non è già in uso inserisce nel rispettivo record della tabella la stringa
//		con il nome dell'operatore;
//		se il verbale risulta in uso avverte l'operatore e consente di proseguire nelle operazioni.
//
// Se si sceglie di abilitare la possibilità di modifica:
//		la funzione setta a null il campo preposto.
//
// La funzione restituisce l'esito dell'operazione.
//
// Nel caso non si riesca nella fase di lock della tabella viene visualizzato un 
// messaggio di errore, in tal caso l'operazione ha esito negativo.

BOOL CWinSigmaApp::SetVerbaleInUso(long nCodice, BOOL libera)
{
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CVerbaliSet set(&pApp->m_db);

  set.m_strFilter.Format("Codice = %d", nCodice);
	set.Open();
	if(set.IsEOF())
  {
    set.Close();
	  return FALSE;
  }

	if(!LockTable("VERBALI"))
	{
  	AfxMessageBox("Attenzione si è verificato un problema durante la sincronizzazione.\nSi prega di ripetere l'operazione");
    set.Close();
		return FALSE;
	}
	else
	{
	  if(libera)// Si è scelto di liberare la tabella 
		{
			set.Edit();
			set.SetFieldNull(&set.m_InUso, TRUE);
			set.Update();
			UnlockTables();
      set.Close();
			return TRUE;
		}
		else
		{
			BOOL mettiInUso = TRUE;
			if(!set.IsFieldNull(&set.m_InUso)) //Se è in uso
			{
				CString msg, utente;
				utente = set.m_InUso;
				utente.MakeUpper();
				msg = STR_BLOCCO_DOCUMENTO_INUSO(utente);
				if(set.m_InUso == INSERIMENTO_NUOVO_VERBALE)
					msg = STR_BLOCCO_DOCUMENTO_NUOVO(utente);
				msg += STR_ISTRUZIONI_RIMOZIONE;
				AfxMessageBox(msg);
				mettiInUso = FALSE;												
			}
			if(mettiInUso) 
			{
				CString strOrario;
				strOrario = CTime::GetCurrentTime().Format("ore %H:%M del %d/%m/%Y");
				set.Edit();
				set.m_InUso.Format("%s (%s)",m_strUserName, strOrario);
				set.m_nFields;
        set.Update();
			}
			UnlockTables();
      set.Close();
			return mettiInUso;
		}
	}
	return TRUE;
}


BOOL CWinSigmaApp::DisabilitaCertificazione(CString* strDaChi, BOOL disabilita)
{
	BOOL giaPresente = FALSE;
	CCertificatiSet pSet(&m_db);

	// Verifico che sia presente il certificato d'appoggio altrimenti lo inserisco
	pSet.m_strFilter = "NumeroCertificato = 0";
	pSet.Open();
	if( pSet.IsEOF() )
	{
		pSet.AddNew();
		pSet.m_NumeroCertificato = 0;
		pSet.Update();
		pSet.Requery();
	}
	else if( !pSet.IsFieldNull(&pSet.m_Macchina) )
	{
		*strDaChi = pSet.m_Macchina;
		giaPresente = TRUE;
	}

	if( (giaPresente && disabilita) || (!giaPresente && !disabilita) )
		return FALSE;
		
	if( disabilita )
	{
		CString strInUso, strOrario;
		strOrario = CTime::GetCurrentTime().Format("ore %H:%M del %d/%m/%Y");
		strInUso.Format("%s (%s)",m_strUserName, strOrario);
		pSet.Edit();
		pSet.m_Macchina = strInUso;
		pSet.Update();
	}
	else
	{
		pSet.Edit();
		pSet.SetFieldNull(&pSet.m_Macchina, TRUE);
		pSet.Update();
	}
	return TRUE;
}



BOOL CWinSigmaApp::DisabilitaFatturazione(CString* strDaChi, BOOL disabilita)
{
	BOOL giaPresente = FALSE;
	CFattureSet pSet(&m_db);

	// Verifico che sia presente la fattura d'appoggio altrimenti la inserisco
	pSet.m_strFilter = "Numero = 0 AND Intestatario = 0";
	pSet.Open();
	if( pSet.IsEOF() )
		{
		pSet.AddNew();
		pSet.m_Numero = 0;
		pSet.m_Intestatario = 0;
		pSet.Update();
		pSet.Requery();
		}
	else if( !pSet.IsFieldNull(&pSet.m_RagioneSociale) )
		{
		*strDaChi = pSet.m_RagioneSociale;
		giaPresente = TRUE;
		}

	if( (giaPresente && disabilita) || (!giaPresente && !disabilita) )
		return FALSE;
		
	if( disabilita )
		{
		CString strInUso, strOrario;
		strOrario = CTime::GetCurrentTime().Format("ore %H:%M del %d/%m/%Y");
		strInUso.Format("%s (%s)",m_strUserName, strOrario);
		pSet.Edit();
		pSet.m_RagioneSociale = strInUso;
		pSet.Update();
		}
	else
		{
		pSet.Edit();
		pSet.SetFieldNull(&pSet.m_RagioneSociale, TRUE);
		pSet.Update();
		}
	return TRUE;
}

BOOL CWinSigmaApp::SetFatturaInUso(CFattureSet* pFattSet, BOOL libera)
{
	// Riallineamento del recordset con i dati del database
	long tempCod = pFattSet->m_Codice;
	pFattSet->Requery();
	while(!pFattSet->IsEOF())
		{
		long TEST = pFattSet->m_Codice;
		CString prove = pFattSet->m_InUso;
		if(pFattSet->m_Codice == tempCod)
			break;
		pFattSet->MoveNext();
		}
	//-----------------------------------------------------//
	
	if( !LockTable("VERBALI") )
		{
		AfxMessageBox("Attenzione si è verificato un problema durante la sincronizzazione.\nSi prega di ripetere l'operazione");
		return FALSE;
		}
	else
		{
		if( libera )// Si è scelto di liberare la tabella 
			{
			pFattSet->Edit();
			pFattSet->SetFieldNull(&pFattSet->m_InUso, TRUE);
			pFattSet->Update();
			UnlockTables();
			return TRUE;
			}
		else
			{
			BOOL mettiInUso = TRUE;
			if( !pFattSet->IsFieldNull(&pFattSet->m_InUso) ) //Se è in uso
				{
				CString msg, utente;
				utente = pFattSet->m_InUso;
				utente.MakeUpper();
				msg = STR_BLOCCO_DOCUMENTO_INUSO(utente);
				if(pFattSet->m_InUso == INSERIMENTO_NUOVO_VERBALE)
					msg = STR_BLOCCO_DOCUMENTO_NUOVO(utente);
				msg += STR_ISTRUZIONI_RIMOZIONE;
				AfxMessageBox(msg);
				mettiInUso = FALSE;												
				}
			if( mettiInUso ) 
				{
				CString strInUso, strOrario;
				strOrario = CTime::GetCurrentTime().Format("ore %H:%M del %d/%m/%Y");
				strInUso.Format("%s (%s)",m_strUserName, strOrario);
				pFattSet->Edit();
				pFattSet->m_InUso = strInUso;
				pFattSet->Update();
				}
			UnlockTables();
			return mettiInUso;
			}
		}
	return TRUE;
}


void CWinSigmaApp::OnHelpVersion() 
{
	// TODO: Add your command handler code here
	
  CAboutDlg about;
  about.DoModal();
}

BYTE CWinSigmaApp::IsDBRemoto()
{
	return m_byDBRemoto;
}
