// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrazionePiegamentoBarreB450_2010.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog


CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CXDialog(CMainDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainDlg)
	m_strFiCalcolato = _T("");
	m_nIndiceAllungamento = 0;
	m_lfLunghezza = 0.0;
	m_strSezioneEffettiva = _T("");
	m_strSnervamentoRelativo = _T("");
	m_strAllungamentoPercentuale = _T("");
	m_strTensioneRelativa = _T("");
	m_strTolleranzaPercentuale = _T("");
	m_lfAllungamento = 0.0;
	m_nFiNominale = 0;
	m_lfPeso = 0.0;
	m_lfRottura = 0.0;
	m_lfSnervamento = 0.0;
	m_DataProve = 0;
	m_strOsservazioni = _T("");
	m_strMacchina = _T("");
	m_strSperimentatore = _T("");
	m_strSigla = _T("");
	m_strStruttura = _T("");
	m_lfAderenza = 0.0;
	m_nMandrino = 0;
	m_nPOS = -1;
	m_nNEG = -1;
	m_strPosizione = _T("");
	m_strMateriale = _T("");
	m_strDataAccettazione = _T("");
	m_lfFyk = 0.0;
	m_bCalcoliConDecimali = FALSE;
	m_csmmper = _T("");
	m_csAllAgt = _T("");
	m_csAllAgtPer = _T("");
	m_bRotoliCT = FALSE;
	m_iOldIndexMarchio	= 0;
	m_iAnnullaMarchio	= 0;
	m_bPrimaSelezione	= true;
	m_iFirstItem		= 0;
	m_csFornitore = _T("");
	//}}AFX_DATA_INIT
}


void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CXDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDlg)
	DDX_Control(pDX, IDC_EDIT_FORN, m_ctrlFornitore);
	DDX_Control(pDX, IDC_CHECK_ROTOLI, m_ctrlRotoliCT);
	DDX_Control(pDX, IDC_STATIC_PERC, m_lblPerc);
	DDX_Control(pDX, IDC_STATIC_ALL, m_lblAll);
	DDX_Control(pDX, IDC_EDIT_INDICE_ALL, m_editIndiceAllungamento);
	DDX_Control(pDX, IDC_CHECK_CALCOLI, m_BtnCalcoliConDecimali);
	DDX_Control(pDX, IDC_EDIT_FYK, m_EdtFyk);
	DDX_Control(pDX, IDC_COMBO_MARCHI, m_ComboMarchi);
	DDX_Control(pDX, IDC_RADIO_POS, m_BtnPOS);
	DDX_Control(pDX, IDC_RADIO_NEG, m_BtnNEG);
	DDX_Control(pDX, IDC_EDIT_OSSERVAZIONI, m_EdtOsservazioni);
	DDX_Control(pDX, IDC_COMBO_SPERIMENTATORI, m_ComboSperimentatori);
	DDX_Control(pDX, IDC_COMBO_MACCHINE, m_ComboMacchine);
	DDX_Control(pDX, IDC_EDIT_DIAMETR_MANDRINO, m_EdtMandrino);
	DDX_Control(pDX, IDC_DATA_PROVA, m_ctrDataProve);
	DDX_Control(pDX, IDOK, m_BtnOk);
	DDX_Control(pDX, IDCANCEL, m_BtnCancel);
	DDX_Control(pDX, IDC_TREE_PROVINI, m_TreeProvini);
	DDX_Control(pDX, IDC_EDT_ADERENZA, m_EdtAderenza);
	DDX_Control(pDX, IDC_EDT_SNERVAMENTO, m_EdtSnervamento);
	DDX_Control(pDX, IDC_EDT_ROTTURA, m_EdtRottura);
	DDX_Control(pDX, IDC_EDT_PESO, m_EdtPeso);
	DDX_Control(pDX, IDC_EDT_ALLUNGAMENTO, m_EdtAllungamento);
	DDX_Control(pDX, IDC_EDIT_LUNGHEZZA, m_EdtLunghezza);
	DDX_Control(pDX, IDC_BUTTON_CONFERMA, m_BtnConferma);
	DDX_Control(pDX, IDC_BUTTON_ANNULLA, m_BtnAnnulla);
	DDX_Control(pDX, IDC_BTN_MODIFICA, m_BtnModifica);
	DDX_Text(pDX, IDC_EDIT_FI_CALC, m_strFiCalcolato);
	DDX_Text(pDX, IDC_EDIT_INDICE_ALL, m_nIndiceAllungamento);
	DDX_Text(pDX, IDC_EDIT_LUNGHEZZA, m_lfLunghezza);
	DDX_Text(pDX, IDC_EDIT_SEZ_EFFET, m_strSezioneEffettiva);
	DDX_Text(pDX, IDC_EDIT_SNERVAM_PERC, m_strSnervamentoRelativo);
	DDX_Text(pDX, IDC_EDIT_ALLUNG_PERC, m_strAllungamentoPercentuale);
	DDX_Text(pDX, IDC_EDIT_TENS_PERC, m_strTensioneRelativa);
	DDX_Text(pDX, IDC_EDIT_TOLL_PERC, m_strTolleranzaPercentuale);
	DDX_Text(pDX, IDC_EDT_ALLUNGAMENTO, m_lfAllungamento);
	DDX_Text(pDX, IDC_EDT_FI_NOMINALE, m_nFiNominale);
	DDX_Text(pDX, IDC_EDT_PESO, m_lfPeso);
	DDX_Text(pDX, IDC_EDT_ROTTURA, m_lfRottura);
	DDX_Text(pDX, IDC_EDT_SNERVAMENTO, m_lfSnervamento);
	DDX_DateTimeCtrl(pDX, IDC_DATA_PROVA, m_DataProve);
	DDX_Text(pDX, IDC_EDIT_OSSERVAZIONI, m_strOsservazioni);
	DDX_CBString(pDX, IDC_COMBO_MACCHINE, m_strMacchina);
	DDX_CBString(pDX, IDC_COMBO_SPERIMENTATORI, m_strSperimentatore);
	DDX_Text(pDX, IDC_EDIT_SIGLA, m_strSigla);
	DDX_Text(pDX, IDC_EDIT_STRUTTURA, m_strStruttura);
	DDX_Text(pDX, IDC_EDT_ADERENZA, m_lfAderenza);
	DDX_Text(pDX, IDC_EDIT_DIAMETR_MANDRINO, m_nMandrino);
	DDX_Radio(pDX, IDC_RADIO_POS, m_nPOS);
	DDX_Radio(pDX, IDC_RADIO_NEG, m_nNEG);
	DDX_Text(pDX, IDC_EDIT_POSIZIONE, m_strPosizione);
	DDX_Text(pDX, IDC_EDIT_MATERIALE, m_strMateriale);
	DDX_Text(pDX, IDC_EDIT_DATA_VA, m_strDataAccettazione);
	DDX_Text(pDX, IDC_EDIT_FYK, m_lfFyk);
	DDX_Check(pDX, IDC_CHECK_CALCOLI, m_bCalcoliConDecimali);
	DDX_Text(pDX, IDC_STATIC_MM_PER, m_csmmper);
	DDX_Text(pDX, IDC_STATIC_ALL_AGT, m_csAllAgt);
	DDX_Text(pDX, IDC_STATIC_ALL_AGT_PER, m_csAllAgtPer);
	DDX_Check(pDX, IDC_CHECK_ROTOLI, m_bRotoliCT);
	DDX_Text(pDX, IDC_EDIT_FORN, m_csFornitore);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainDlg, CXDialog)
	//{{AFX_MSG_MAP(CMainDlg)
	ON_BN_CLICKED(IDC_BTN_MODIFICA, OnBtnModifica)
	ON_BN_CLICKED(IDC_BUTTON_ANNULLA, OnButtonAnnulla)
	ON_BN_CLICKED(IDC_BUTTON_CONFERMA, OnButtonConferma)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_PROVINI, OnSelchangedTreeProvini)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_PROVINI, OnDblclkTreeProvini)
	ON_CBN_SELCHANGE(IDC_COMBO_SPERIMENTATORI, OnSelchangeComboSperimentatori)
	ON_BN_CLICKED(IDC_RADIO_NEG, OnRadioNeg)
	ON_BN_CLICKED(IDC_RADIO_POS, OnRadioPos)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_NOTIFY(DTN_CLOSEUP, IDC_DATA_PROVA, OnCloseupDataProva)
	ON_EN_KILLFOCUS(IDC_EDT_ALLUNGAMENTO, OnKillfocusEdtAllungamento)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers


////////////////////////////////////////////////////////////////
// Istanzia il blob s lo inizializza il blob con valori di default

CByteArray* CMainDlg::InitBlob()
{
	CByteArray* blob = new CByteArray();		//Creazione del blob contenitore
	dati* pDati = new dati();								//Creazione della struttura specializzata
	pDati->nVersione		= 0;										//Inserimento del numero di versione
	pDati->lunghezza		= 0;
	pDati->peso					= 0;
	pDati->allungamento = 0;
	pDati->esito				= 0;
	pDati->rottura			= 0;
	pDati->snervamento	= 0;
	pDati->aderenza			= 0;
	pDati->mandrino			= SceltaMandrino();
	pDati->esito				= 1;

	char *p_ary = (char*)pDati;
	for(int i=0;i<sizeof(struct dati);i++)	// Riempimento del blob contenitore
		{
		blob->Add(*p_ary);
		p_ary++;
		}
	return blob;										

}


/////////////////////////////////////////////////////////////
// Gestione dei controlli dalla visualizzazione alla modifica

void CMainDlg::DisableModify(boolean disabilita)
{
	if( m_bDatiModificabili )
		{
			if((m_nProveRichieste == 1)||(m_nProveRichieste == 3))
				{
				m_EdtAllungamento.SetReadOnly(disabilita);
				m_EdtLunghezza.SetReadOnly(disabilita);
				m_EdtPeso.SetReadOnly(disabilita);
				m_EdtRottura.SetReadOnly(disabilita);
				m_EdtSnervamento.SetReadOnly(disabilita);
				}
			if(m_nProveRichieste>1)
				{
				m_EdtAderenza.SetReadOnly(disabilita);
				m_EdtMandrino.SetReadOnly(disabilita);
				m_BtnPOS.EnableWindow(!disabilita);
				m_BtnNEG.EnableWindow(!disabilita);
				}	
			m_ComboMarchi.EnableWindow(!disabilita);

			m_EdtFyk.SetReadOnly(disabilita);
			m_TreeProvini.EnableWindow(disabilita);
			m_BtnModifica.EnableWindow(disabilita);
			m_BtnOk.EnableWindow(disabilita);
      m_BtnCalcoliConDecimali.EnableWindow(disabilita);
			
			m_EdtOsservazioni.SetReadOnly(!m_pSerieSet->m_NuovoCertificato);
			m_ctrDataProve.EnableWindow(m_pSerieSet->m_NuovoCertificato);
			m_ComboSperimentatori.EnableWindow(m_pSerieSet->m_NuovoCertificato);
			m_ComboMacchine.EnableWindow(m_pSerieSet->m_NuovoCertificato);

			if(!m_bDatiCambiati)
				m_BtnCancel.EnableWindow(disabilita);
			else
				m_BtnCancel.EnableWindow(FALSE);
				
			m_BtnAnnulla.EnableWindow(!disabilita);
			m_BtnConferma.EnableWindow(!disabilita);

			m_ctrlFornitore.SetReadOnly(!m_pSerieSet->m_NuovoCertificato);
		}
	else
		{
		m_EdtAllungamento.SetReadOnly(TRUE);
		m_EdtLunghezza.SetReadOnly(TRUE);
		m_EdtPeso.SetReadOnly(TRUE);
		m_EdtRottura.SetReadOnly(TRUE);
		m_EdtSnervamento.SetReadOnly(TRUE);
		m_EdtAderenza.SetReadOnly(TRUE);
		
		m_ComboMarchi.EnableWindow(FALSE);
		m_BtnPOS.EnableWindow(FALSE);
		m_BtnNEG.EnableWindow(FALSE);
		m_BtnAnnulla.EnableWindow(FALSE);
		m_BtnConferma.EnableWindow(FALSE);
		m_ctrDataProve.EnableWindow(FALSE);
		m_BtnModifica.EnableWindow(disabilita);
		m_BtnOk.EnableWindow(FALSE);

		m_EdtOsservazioni.SetReadOnly(TRUE);
		m_ComboSperimentatori.EnableWindow(FALSE);
		m_ComboMacchine.EnableWindow(FALSE);
    m_BtnCalcoliConDecimali.EnableWindow(FALSE);

		m_ctrlFornitore.SetReadOnly(TRUE);
		}
}

////////////////////////////////////////////////////
// Abilitazione dei pulsanti di modifica e
// memorizzazione del codice del provino selezionato


void CMainDlg::OnBtnModifica() 
{
	if( m_bDatiModificabili )
	{
		m_iAnnullaMarchio = m_ComboMarchi.GetCurSel();
		
		if ((m_iOldIndexMarchio != 0) || (m_ComboMarchi.GetCurSel() == 0))
			m_ComboMarchi.SetCurSel(m_iOldIndexMarchio);

		DisableModify(FALSE);

		m_EdtOsservazioni.SetReadOnly(FALSE);

		m_ctrlRotoliCT.EnableWindow(FALSE);

		HTREEITEM hItem = m_TreeProvini.GetSelectedItem();
		m_nCodProvinoCorrente = m_TreeProvini.GetItemData(hItem);	
		m_EdtPeso.SetFocus();
		m_EdtPeso.SetSel(0, -1);
	}
	else 
		{
			byte test = AfxMessageBox("Attenzione: La serie fa parte di un certificato gi‡ emesso.\nContinuare con le modifiche?", MB_YESNO);
			if(IDYES == test)
			{
			m_bDatiModificabili = TRUE;
			m_EdtOsservazioni.SetReadOnly(FALSE);
			m_ctrlFornitore.SetReadOnly(FALSE);
			m_ComboSperimentatori.EnableWindow(TRUE);
			m_ComboMacchine.EnableWindow(TRUE);	
			m_ctrDataProve.EnableWindow(TRUE);
			m_ComboMarchi.EnableWindow(TRUE);
			DisableModify(FALSE);
			HTREEITEM hItem = m_TreeProvini.GetSelectedItem();
			m_nCodProvinoCorrente = m_TreeProvini.GetItemData(hItem);	
			m_EdtPeso.SetFocus();
			m_EdtPeso.SetSel(0, -1);
			}
		}
}

void CMainDlg::OnButtonAnnulla() 
{
	switch(m_pDatiCorrenti->nVersione)
		{
		case 0:
			{
				m_lfLunghezza			= m_pDatiCorrenti->lunghezza;
				m_lfPeso					= m_pDatiCorrenti->peso;
				m_lfAllungamento	= m_pDatiCorrenti->allungamento;
				m_lfRottura				= m_pDatiCorrenti->rottura;
				m_lfSnervamento		= m_pDatiCorrenti->snervamento;
				// Cancello i dati eventualmente presenti nei campi relativi ai dati calcolati
				m_strAllungamentoPercentuale = "";
				m_strFiCalcolato= "";
				m_strSezioneEffettiva = "";
				m_strSnervamentoRelativo = "";
				m_strTensioneRelativa = "";
				m_strTolleranzaPercentuale = "";
			};
		case 1 :; // predisposizione per l'introduzione di nuovi campi alla struttura dati
		}

	m_ComboMarchi.SetCurSel(m_iAnnullaMarchio);

	UpdateData(FALSE);
	CalcolaDati(m_bCalcoliConDecimali);
	UpdateData(FALSE);
	
	DisableModify(TRUE);
	m_TreeProvini.SetFocus();
}


///////////////////////////////////////////////////////////////////
// Trascrive i dati dal dialogo al blob e lo memorizza sul database

void CMainDlg::OnButtonConferma() 
{
	if (m_iFirstItem == m_TreeProvini.GetItemData(m_TreeProvini.GetSelectedItem()))
		m_iOldIndexMarchio = m_ComboMarchi.GetCurSel();
	
	if(UpdateData(TRUE))
	{
		if( sqrt(m_lfFyk*m_lfFyk) < 0.001)
		{
			CString msg;
			msg.Format("Attenzione il valore del parametro:\n\n fbk =%.4f\n\nnon Ë un dato accettabile!",m_lfFyk);
			AfxMessageBox(msg);
			return;
		}
			
		m_bDatiCambiati = TRUE;
		DisableModify(TRUE);
		m_ctrlRotoliCT.EnableWindow(FALSE);
		m_EdtOsservazioni.SetReadOnly(TRUE);
		m_ctrlFornitore.SetReadOnly(TRUE);
		switch(m_pDatiCorrenti->nVersione)
		{
			case 0://elaborazione dei dati per la versione 0
			{
					m_pDatiCorrenti->allungamento = m_lfAllungamento;
					m_pDatiCorrenti->lunghezza		= m_lfLunghezza;
					m_pDatiCorrenti->peso					= m_lfPeso;
					m_pDatiCorrenti->rottura			= m_lfRottura;
					m_pDatiCorrenti->snervamento	= m_lfSnervamento;
					m_pDatiCorrenti->aderenza			= m_lfAderenza;
					m_pDatiCorrenti->mandrino			= m_nMandrino;
					m_pDatiCorrenti->esito				= m_BtnPOS.GetCheck();
			};
			case 1 :; // predisposizione per l'introduzione di nuovi campi alla struttura dati
		}
		UpdateData(FALSE);
		UpdateData(TRUE);
		try
		{
			m_pProviniSet->m_pDatabase->BeginTrans();
			m_pProviniSet->Edit();
			m_pProviniSet->m_DataInserimento	= CTime::GetCurrentTime();
			m_pProviniSet->m_Marchio					= (long)m_ComboMarchi.GetItemData(m_ComboMarchi.GetCurSel());
			m_pProviniSet->SetFieldDirty(&m_pProviniSet->m_Risultati,TRUE);
			m_pProviniSet->m_RotoliCT = m_bRotoliCT;
			m_pProviniSet->Update();
			m_pProviniSet->m_pDatabase->CommitTrans();		
		}
		catch(CDBException* e)
		{
			if (e->m_nRetCode == 1008) // AFX_SQL_ERROR_NO_ROWS_AFFECTED
			{
				m_pProviniSet->m_pDatabase->CommitTrans();
			}
			else
			{
				m_pProviniSet->m_pDatabase->Rollback();
			}
		}
		RiempiAlbero(TRUE);
		m_TreeProvini.SetFocus();
	}
}




/////////////////////////////////////////////////////////////////
//  Calcola i dati e mostra i risultati nella finestra di dialogo

byte CMainDlg::CalcolaDati(BOOL bConDecimali)
{
	int temp = 0;
	boolean esito = TRUE;
	if(m_lfLunghezza!=0)
	{
		// massa lineare
		double massa				= m_lfPeso/m_lfLunghezza;
		// sezione efettiva
		double sezRilevata	= massa/PESO_SPECIFICO * 1000;

		//Gestione dei decimali in base alla sezione rilevata
    if(!bConDecimali)
    {
 			if(sezRilevata>100)
 				sezRilevata = floor(sezRilevata + 0.5);
 			else if(sezRilevata<100 && sezRilevata>10)
 				sezRilevata = floor((sezRilevata * 10) + 0.5)/10;
 			else if(sezRilevata<10)
 				sezRilevata = (floor( (sezRilevata*100) + 0.5 ))/100 ;	
    }
				
		// sezione nominale
		double sezNominale	= (m_nFiNominale/2) * (m_nFiNominale/2) * PI_GRECO;
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

		// snervamento relativo percentuale
		double snervamentoRelativo = 0;
		snervamentoRelativo	= m_lfSnervamento/sezNominale * 1000;

		// Richiesto da Enzo 11/06/2007 per l'approssimazione non corretta di 0,01
    CString s;
    s.Format("%.0f", snervamentoRelativo);
    snervamentoRelativo = atof(s);
      
		// tensione relativa percentuale
		double tensioneRelativa	= 0;
		tensioneRelativa	= m_lfRottura/sezNominale * 1000;

    s.Format("%.0f", tensioneRelativa);
    tensioneRelativa = atof(s);
		// alungamento relativo percentuale
		double allungamentoPercentuale = 0;
		// precedente certificato
		// allungamentoPercentuale	= m_lfAllungamento/(m_nFiNominale*m_nIndiceAllungamento) * 100;
		allungamentoPercentuale = m_lfAllungamento + ( tensioneRelativa / 2000);
		// fi effettivo
		double fiEffettivo							= sqrt(sezRilevata/PI_GRECO)*2;
		// scarto percentuale sezione nominale e rilevata
		double tollSullaSez							= (sezRilevata - sezNominale)/sezNominale * 100;
	
		/////////////////////////////////////////////////
		// Visulaizzazione dei dati calcolati nel dialogo
    if(bConDecimali)
    {
   		if(sezRilevata>100)
   			sezRilevata = floor(sezRilevata + 0.5);
   		else if(sezRilevata<100 && sezRilevata>10)
   			sezRilevata = floor((sezRilevata * 10) + 0.5)/10;
   		else if(sezRilevata<10)
   			sezRilevata = (floor( (sezRilevata*100) + 0.5 ))/100 ;	
    }

		//CString str;
		str.Format("%.2lf",sezRilevata);
		m_strSezioneEffettiva = str;
		str.Format("%.0lf",snervamentoRelativo);
		m_strSnervamentoRelativo = str;
		str.Format("%.0lf",tensioneRelativa);
		m_strTensioneRelativa = str;
		str.Format("%.1lf",allungamentoPercentuale);
		m_strAllungamentoPercentuale = str;
		str.Format("%.2lf",fiEffettivo);
		m_strFiCalcolato = str;
		str.Format("%.2lf",tollSullaSez);
		m_strTolleranzaPercentuale = str;

		UpdateData(FALSE);

		esito = (tollSullaSez<=6 && tollSullaSez>=-6);
				//Controllo che non ci sia eccessiva differenza fra la sezione
				// nominale e quella 
	}
	return esito; 			
}



//////////////////////////////////////////////////////////////////////
// Apre i recordset, preleva i dati generali dal recordset delle serie
// rileva il tipo di emissione (A, B, AB), Inizializza e riempie l'albero
// dei provini,

BOOL CMainDlg::OnInitDialog() 
{
	CXDialog::OnInitDialog();
	m_bDatiCambiati = FALSE;
	m_pProviniSet->m_strFilter.Format("Serie = %d",m_pSerieSet->m_Codice);
  m_pProviniSet->m_strSort = "Codice";
	SAFETY_OPEN(m_pProviniSet);
	SAFETY_OPEN(m_pOperatoriSet);
	m_pMarchiSet->m_strSort = "Nome";
	SAFETY_OPEN(m_pMarchiSet);

	m_nVariante = 0;

	m_csmmper			=  "%";
	m_csAllAgt		= "Ag";
	m_csAllAgtPer = "AGT";

	m_editIndiceAllungamento.ShowWindow(SW_HIDE);
	m_lblAll.ShowWindow(SW_HIDE);
	m_lblPerc.ShowWindow(SW_HIDE);

	//-- Verifico se la serie appartiene ad un certificato gi‡ emesso
	m_bDatiModificabili = m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Certificato) 
		|| m_pSerieSet->m_Certificato == 0;

	m_nFiNominale = (int)m_pSerieSet->m_Dimensione1;
	m_nIndiceAllungamento = INDICE_ALLUNGAMENTO;

	// ----- Inserisco i dai statici della serie nel dialogo ---- //

	// Gestione data prova e data accettazione 
	m_strDataAccettazione = m_DataAccettazione.Format("%d/%m/%Y");
	if( !m_pSerieSet->IsFieldNull(&m_pSerieSet->m_DataProva) )
		m_DataProve = m_pSerieSet->m_DataProva;
	else
		m_DataProve = *m_pUltimaDataProve;
	if (! m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Sigla) )
		m_strSigla = m_pSerieSet->m_Sigla;
	if (! m_pSerieSet->IsFieldNull(&m_pSerieSet->m_StrutturaPrelievo) )
		m_strStruttura = m_pSerieSet->m_StrutturaPrelievo;
	if (! m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Materiale) )
		m_strMateriale = m_pSerieSet->m_Materiale;
	else
		m_strMateriale = "n.d.";
	if (! m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Snervamento) )
		m_lfFyk =  m_pSerieSet->m_Snervamento;
  if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Checked))
    m_bCalcoliConDecimali = m_pSerieSet->m_Checked;

	m_csFornitore = m_pSerieSet->m_SiglaFornitore;

	UpdateData(FALSE);//scrivo nel dialogo


	// -------- Inserimento dei dati nella combo dei marchi -------------//
	
	CString str;

	int index = 0;
	int indexNR = m_ComboMarchi.AddString("Non rilevato");
	m_ComboMarchi.SetItemData( indexNR, 0);
	byte datoPresente = !m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Marchio);
	for(SET_START(m_pMarchiSet); !m_pMarchiSet->IsEOF(); m_pMarchiSet->MoveNext())
	{
		index = m_ComboMarchi.AddString(m_pMarchiSet->m_Nome);
		m_ComboMarchi.SetItemData( index, m_pMarchiSet->m_Codice);
	}
	m_ComboMarchi.SetCurSel(indexNR);
	UpdateData(TRUE);
 //------------------------------------------------------------------------//


	//Rilevamento del tipo di emissione corrente (A, B, AB)
	m_nProveRichieste = ProveRichieste(m_pServiziListinoSet, m_pSerieSet);
	
	// Inizializzazione della lista delle icone dei provini
	HICON icon[4];
	icon[0]	= AfxGetApp()->LoadIcon(IDI_ICON_INTERA);
	icon[1]	= AfxGetApp()->LoadIcon(IDI_ICON_INTERA_SELECT);
	icon[2]	= AfxGetApp()->LoadIcon(IDI_ICON_NOSELECT);
	icon[3]	= AfxGetApp()->LoadIcon(IDI_ICON_SELECT);
	m_imageList.Create(16, 16, 0, 8, 8);
	for(int n=0; n<4;n++)
		m_imageList.Add(icon[n]);
	// Assegno la lista di icona alla struttura ad albero
	m_TreeProvini.SetImageList(&m_imageList, TVSIL_NORMAL);

	// Riempio l'albero dei provini selezionando il primo elemento
	RiempiAlbero(FALSE);
	AbilitaControlli();
	DisableModify(TRUE);

	DatiCertificato();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//////////////////////////////////////////////////////////////////////
// Stabilisce il tipo di certificato associabile ai servizi richiesti,

byte CMainDlg::ProveRichieste(CServiziListinoSet* pServiziSet, CSerieSet* pSerieSet)
{
	byte temp = 0, prove = 0;
	CString str, query = "";

	if(!pSerieSet->IsFieldNull(&pSerieSet->m_Servizio1))
		{
		str.Format("Codice = %d", pSerieSet->m_Servizio1);
		(query.GetLength()==0) ? query = str : query = query + " OR " + str;
		}
	if(!pSerieSet->IsFieldNull(&pSerieSet->m_Servizio2))
		{
		str.Format("Codice = %d", pSerieSet->m_Servizio2);
		(query.GetLength()==0) ? query = str : query = query + " OR " + str; 
		}
	if(!pSerieSet->IsFieldNull(&pSerieSet->m_Servizio3))
		{
		str.Format("Codice = %d", pSerieSet->m_Servizio3);
		(query.GetLength()==0) ? query = str : query = query + " OR " + str; 
		}
	if(!pSerieSet->IsFieldNull(&pSerieSet->m_Servizio4))
		{
		str.Format("Codice = %d", pSerieSet->m_Servizio4);
		(query.GetLength()==0) ? query = str : query = query + " OR " + str; 
		}
	if(!pSerieSet->IsFieldNull(&pSerieSet->m_Servizio5))
	{
		str.Format("Codice = %d", pSerieSet->m_Servizio5);
		(query.GetLength()==0) ? query = str : query = query + " OR " + str;
		}
	if(!pSerieSet->IsFieldNull(&pSerieSet->m_Servizio6))
		{
		str.Format("Codice = %d", pSerieSet->m_Servizio6);
		(query.GetLength()==0) ? query = str : query = query + " OR " + str; 
		}
	if(!pSerieSet->IsFieldNull(&pSerieSet->m_ServAggiunto))
		{
		str.Format("Codice = %d", pSerieSet->m_ServAggiunto);
		(query.GetLength()==0) ? query = str : query = query + " OR " + str; 
		}

	//Seleziono solo i servizi che comportano prove
	pServiziSet->m_strFilter.Format("Prove!=0 AND (%s)", query);
	SAFETY_OPEN(pServiziSet);
	while( !pServiziSet->IsEOF() )
		{
		if ((temp = max(temp, pServiziSet->m_Prove)) != prove && prove == 0)
			prove = temp;
		else
			prove = 3;
		pServiziSet->MoveNext();
		}
	return prove;
}

//////////////////////////////////////////////////////////////////
// Riempie l'albero selezionando il primo elemento se il parametro 
// booleano Ë falso, altrimenti ribadisce la selezione rilevata

void CMainDlg::RiempiAlbero(boolean selezionato)
{
	BOOL trovato = FALSE;
	HTREEITEM primo,select;
	m_TreeProvini.DeleteAllItems( );
	TV_INSERTSTRUCT tvinsert;
	tvinsert.hParent = NULL;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	tvinsert.item.hItem = NULL;
	tvinsert.item.iSelectedImage = 3;
	tvinsert.item.iImage = 2;
	CString str;
	int i = 0;
	for(SET_START(m_pProviniSet); !m_pProviniSet->IsEOF(); m_pProviniSet->MoveNext())
		{
		if(m_pProviniSet->IsFieldNull(&m_pProviniSet->m_Risultati))
			{
				m_pProviniSet->Edit();
				m_pProviniSet->m_Risultati.Copy(*InitBlob());//Se il campo Ë null viene inizializzato con valori di default
				m_pProviniSet->Update();
			}
		str.Format("Provino %d",i+1);				// Nome del provino
		
		tvinsert.item.pszText = str.GetBuffer(0);
		dati* tempDati = (dati*)m_pProviniSet->m_Risultati.GetData();
		if (m_pProviniSet->IsFieldNull(&m_pProviniSet->m_DataInserimento))
			{
				tvinsert.item.iImage = 0;
				tvinsert.item.iSelectedImage = 1;
			}
		else
			{
				tvinsert.item.iImage = 2;
				tvinsert.item.iSelectedImage = 3;
			}
		HTREEITEM nItem = m_TreeProvini.InsertItem(&tvinsert);
		if(i==0)
			select = primo = nItem;

		// Identifica l'item successivo a quello corrente
		if(trovato)
			{
			trovato = FALSE;
			select = nItem;
			}

		// Item Corrente
		if(selezionato && m_pProviniSet->m_Codice == m_nCodProvinoCorrente)
			trovato = TRUE;
		
		m_TreeProvini.SetItemData(nItem, m_pProviniSet->m_Codice);
		m_TreeProvini.SetItemText(nItem, str);
		i++;
		}

	if(selezionato)
		m_TreeProvini.SelectItem(select);
	else
		m_TreeProvini.SelectItem(primo);
}



/////////////////////////////////////////////////////////////////////
// Chiamata quando Ë cambiata la selezione da un provino ad un altro,
// seleziona il blob dal recordset e mostra il contenuto nei campi del dialogo.
// Se il dato Ë gi‡ stato confermato tenta di riempire anche i campi contenenti 
// i dati calcolati

void CMainDlg::OnSelchangedTreeProvini(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	HTREEITEM hItem = m_TreeProvini.GetSelectedItem();
	long codProvino = m_TreeProvini.GetItemData(hItem);

	//Sincronizzo il provino del recordset con quello selezionato
	SAFETY_OPEN(m_pProviniSet);
	SINCRONIZE(m_pProviniSet, codProvino);
	
	m_bRotoliCT = m_pProviniSet->m_RotoliCT;

	// Converto il blob nella struttura dati adatta
	m_pDatiCorrenti = (dati*)m_pProviniSet->m_Risultati.GetData();


	// Allineo la combo al tipo di marchio relativo al provino selezionato
	int indexSel = 0;
	for(int i=0; i<m_ComboMarchi.GetCount(); i++)
		{
		if(m_pProviniSet->m_Marchio == (long)m_ComboMarchi.GetItemData(i))
			indexSel = i;
		}

	if (m_bPrimaSelezione == true)
	{
		m_iFirstItem = m_TreeProvini.GetItemData(m_TreeProvini.GetSelectedItem());
		m_iOldIndexMarchio = indexSel;
		m_bPrimaSelezione = false;
	}
	if (m_iFirstItem == m_TreeProvini.GetItemData(m_TreeProvini.GetSelectedItem()))
		m_iOldIndexMarchio = indexSel;


	m_ComboMarchi.SetCurSel(indexSel);

	// Eseguo le operazioni di riempimento del dialogo con i valori presenti nel blob
	switch(m_pDatiCorrenti->nVersione)
		{
		case 0:
			{
				m_lfLunghezza			= m_pDatiCorrenti->lunghezza;
				m_lfPeso					= m_pDatiCorrenti->peso;
				m_lfAllungamento	= m_pDatiCorrenti->allungamento;
				m_lfRottura				= m_pDatiCorrenti->rottura;
				m_lfSnervamento		= m_pDatiCorrenti->snervamento;
				m_lfAderenza			= m_pDatiCorrenti->aderenza;
				m_nMandrino				= m_pDatiCorrenti->mandrino;
				// Cancello i dati eventualmente presenti nei campi relativi ai dati calcolati
				m_strAllungamentoPercentuale = "";
				m_strFiCalcolato= "";
				m_strSezioneEffettiva = "";
				m_strSnervamentoRelativo = "";
				m_strTensioneRelativa = "";
				m_strTolleranzaPercentuale = "";
				UpdateData(FALSE);

				int set;
				m_pDatiCorrenti->esito ? set=1 : set = 0;
				m_BtnPOS.SetCheck(set);
				m_BtnNEG.SetCheck(1-set);
				UpdateData(TRUE);
				
				CalcolaDati(m_bCalcoliConDecimali);
			};
		case 1 :; // predisposizione per l'introduzione di nuovi campi alla struttura dati
		}

	*pResult = 0;
}


///////////////////////////////////////////////////////////////////////
// Memorizza il codice associato al provino selezionato per consentirne 
// la corretta selezione al ternmine delle operazioni di modifica

void CMainDlg::OnDblclkTreeProvini(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if( m_bDatiModificabili )
		{
		DisableModify(FALSE);

		m_EdtOsservazioni.SetReadOnly(FALSE);

		m_ctrlRotoliCT.EnableWindow(FALSE);

		HTREEITEM hItem = m_TreeProvini.GetSelectedItem();
		m_nCodProvinoCorrente = m_TreeProvini.GetItemData(hItem);	
		m_EdtPeso.SetFocus();
		m_EdtPeso.SetSel(0, -1);
		}
	else 
		{
			byte test = AfxMessageBox("Attenzione: La serie fa parte di un certificato gi‡ emesso.\nContinuare con le modifiche?", MB_YESNO);
			if(IDYES == test)
			{
			m_bDatiModificabili = TRUE;

			m_EdtOsservazioni.SetReadOnly(FALSE);
			m_ComboSperimentatori.EnableWindow(TRUE);
			m_ComboMacchine.EnableWindow(TRUE);	
			m_ctrDataProve.EnableWindow(TRUE);
			m_ComboMarchi.EnableWindow(TRUE);
			m_ctrlFornitore.SetReadOnly(FALSE);
			DisableModify(FALSE);
			HTREEITEM hItem = m_TreeProvini.GetSelectedItem();
			m_nCodProvinoCorrente = m_TreeProvini.GetItemData(hItem);	
			m_EdtPeso.SetFocus();
			m_EdtPeso.SetSel(0, -1);
			}
		}
	*pResult = 0;
}

void CMainDlg::OnOK() 
{
	// Memorizzo lo sperimentatore e la data prova selezionati per riproporli in seguito
	*m_pUltimoSper = m_ComboSperimentatori.GetItemData(m_ComboSperimentatori.GetCurSel());
	*m_pUltimaDataProve = m_DataProve;

	try
	{
		m_pSerieSet->m_pDatabase->BeginTrans();
		if( m_pSerieSet->m_NuovoCertificato )
		{
			UpdateData(TRUE);
			
			if(m_ComboMacchine.GetCurSel() != CB_ERR)
				m_ComboMacchine.GetLBText(m_ComboMacchine.GetCurSel(), m_strMacchina);
			if(m_ComboSperimentatori.GetCurSel() != CB_ERR)
				m_ComboSperimentatori.GetLBText(m_ComboSperimentatori.GetCurSel(), m_strSperimentatore);

			m_pSerieSet->Edit();
			m_pSerieSet->m_DataProva			= m_DataProve;
			m_pSerieSet->m_Osservazioni		= m_strOsservazioni;
			m_pSerieSet->m_Sperimentatore = m_strSperimentatore;
			m_pSerieSet->m_Macchina				= m_strMacchina;
			m_pSerieSet->m_TipoProva			= m_nProveRichieste;
			m_pSerieSet->m_Snervamento		= m_lfFyk;
      m_pSerieSet->m_Checked    = m_bCalcoliConDecimali;
			m_pSerieSet->m_SiglaFornitore = m_csFornitore;
			m_pSerieSet->Update();
			
			m_pSerieSet->MoveNext();
			while( !m_pSerieSet->IsEOF() && !m_pSerieSet->m_NuovoCertificato)
			{
				m_pSerieSet->Edit();
				m_pSerieSet->m_DataProva			= m_DataProve;
				m_pSerieSet->m_Osservazioni		= m_strOsservazioni;
				m_pSerieSet->m_Sperimentatore = m_strSperimentatore;
				m_pSerieSet->m_Macchina				= m_strMacchina;
				m_pSerieSet->m_TipoProva			= m_nProveRichieste;
        m_pSerieSet->m_Checked        = m_bCalcoliConDecimali;
				m_pSerieSet->Update();
				m_pSerieSet->MoveNext();
			}
		}
		else
		{
			UpdateData(TRUE);
			m_pSerieSet->Edit();
			m_pSerieSet->m_Snervamento	= m_lfFyk;
			m_pSerieSet->m_TipoProva		= m_nProveRichieste;
			m_pSerieSet->m_Osservazioni		= m_strOsservazioni;
			m_pSerieSet->Update();
		}
		m_pSerieSet->m_pDatabase->CommitTrans();
	}
	catch(CDBException* e)
	{
		m_pSerieSet->m_pDatabase->Rollback();
		CString strError;
		strError.Format("Attenzione, le informazioni sulle serie non sono state salvate!\n%s",e->m_strError);
		AfxMessageBox(strError);
	}
		
	CDialog::OnOK();
}

void CMainDlg::AbilitaControlli()
{
	if(m_nProveRichieste == 1)
		{
		m_EdtAllungamento.EnableWindow(TRUE);
		m_EdtLunghezza.EnableWindow(TRUE);
		m_EdtPeso.EnableWindow(TRUE);
		m_EdtRottura.EnableWindow(TRUE);
		m_EdtSnervamento.EnableWindow(TRUE);

		m_EdtAderenza.EnableWindow(FALSE);
		m_EdtMandrino.EnableWindow(FALSE);
		m_BtnPOS.EnableWindow(FALSE);
		m_BtnNEG.EnableWindow(FALSE);
		}
	else if(m_nProveRichieste==2)
		{
		m_EdtAllungamento.EnableWindow(FALSE);
		m_EdtLunghezza.EnableWindow(FALSE);
		m_EdtPeso.EnableWindow(FALSE);
		m_EdtRottura.EnableWindow(FALSE);
		m_EdtSnervamento.EnableWindow(FALSE);

		m_EdtAderenza.EnableWindow(TRUE);
		m_EdtMandrino.EnableWindow(TRUE);
		m_BtnPOS.EnableWindow(TRUE);
		m_BtnNEG.EnableWindow(TRUE);
		}	
	else 
		{
		m_EdtAllungamento.EnableWindow(TRUE);
		m_EdtLunghezza.EnableWindow(TRUE);
		m_EdtPeso.EnableWindow(TRUE);
		m_EdtRottura.EnableWindow(TRUE);
		m_EdtSnervamento.EnableWindow(TRUE);
		m_EdtAderenza.EnableWindow(TRUE);
		m_EdtMandrino.EnableWindow(TRUE);
		m_BtnPOS.EnableWindow(TRUE);
		m_BtnNEG.EnableWindow(TRUE);
		}
}

///////////////////////////////////////////////////////
// Prepara il dialogo in relazione ai dati presenti nel
// recordset delle serie sulle informazioni legate al
// certificato

void CMainDlg::DatiCertificato()
{
	CString str;
	int index = 0;
	int no = 0, nm = 0, OpPredef = 0, MaPredef=0;
	for( SET_START(m_pOperatoriSet); !m_pOperatoriSet->IsEOF(); m_pOperatoriSet->MoveNext() )
			{
			if( !m_pOperatoriSet->IsFieldNull(&m_pOperatoriSet->m_Sperimentatore) 
					&& m_pOperatoriSet->m_Sperimentatore ) 
				{
				str = m_pOperatoriSet->m_Titolo + " " + m_pOperatoriSet->m_Nome + " " + m_pOperatoriSet->m_Cognome;
				no = m_ComboSperimentatori.AddString(str);
				m_ComboSperimentatori.SetItemData(no, m_pOperatoriSet->m_Codice);
				nm = m_ComboMacchine.AddString(m_pOperatoriSet->m_Macchina);
				if(m_pOperatoriSet->m_Codice == *m_pUltimoSper)
					{
					OpPredef = no;
					MaPredef = nm;
					}
				}
			}

	if( !m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Osservazioni) )
		{
		m_strOsservazioni = m_pSerieSet->m_Osservazioni;
		UpdateData(FALSE); //scrivo nel dialogo
		}
	if( !m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Sperimentatore) )
		{
		index =	m_ComboMacchine.FindString(0,m_pSerieSet->m_Macchina);
		if(index==-1)	index = 0;
		m_ComboMacchine.SetCurSel(index);
		index =	m_ComboSperimentatori.FindString(0,m_pSerieSet->m_Sperimentatore);
		if(index==-1)	index = 0;
		m_ComboSperimentatori.SetCurSel(index);
		UpdateData(TRUE); //leggo dal dialogo
		}
	else
		{
		m_ComboMacchine.SetCurSel(MaPredef);
		m_ComboSperimentatori.SetCurSel(OpPredef);
		UpdateData(TRUE); //leggo dal dialogo
		}
}

/////////////////////////////////////////////
// Associa la macchina allo sperimentatore

void CMainDlg::OnSelchangeComboSperimentatori() 
{
 int index = m_ComboSperimentatori.GetCurSel();
 m_ComboMacchine.SetCurSel(index);
}

void CMainDlg::OnRadioNeg() 
{
	m_BtnPOS.SetCheck(0);
}

void CMainDlg::OnRadioPos() 
{
	m_BtnNEG.SetCheck(0);	
}

int CMainDlg::SceltaMandrino()
{
	int FiNom = (int)m_pSerieSet->m_Dimensione1;

	if(m_pSerieSet->m_Snervamento == 430 )
		{
		switch(FiNom)
			{
			case 6 : return 24;
			case 8 : return 32;
			case 10: return 40;
			case 12: return 48;
			case 14: return 112;
			case 16: return 128;
			case 18: return 144;
			case 20: return 200;
			case 22: return 220;
			case 24: return 240;
			case 26: return 312;
			case 28: return 336;
			case 30: return 360;
			};
		}
	else if (m_pSerieSet->m_Snervamento == 375)
		{
		switch(FiNom)
			{
			case 6 : return 18;
			case 8 : return 24;
			case 10: return 30;
			case 12: return 36;
			case 14: return 84;
			case 16: return 96;
			case 18: return 108;
			case 20: return 160;
			case 22: return 176;
			case 24: return 192;
			case 26: return 260;
			case 28: return 280;
			case 30: return 300;
			};
		}
	else if (m_pSerieSet->m_Snervamento == 450)
		{
		switch(FiNom)
			{
			case 6 : return 24;
			case 8 : return 32;
			case 10: return 40;
			case 12: return 60;
			case 14: return 70;
			case 16: return 80;
			case 18: return 144;
			case 20: return 160;
			case 22: return 176;
			case 24: return 192;
			case 26: return 260;
			case 28: return 280;
			case 30: return 300;
			};
		}
	return 0;
}

void CMainDlg::OnButtonNext() 
{
	CXDialog::OnButtonNext();
}


void CMainDlg::OnCloseupDataProva(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CString str1, str2;
	str1 = "ATTENZIONE!\nOperazione non consentita!\nLa data scelta precede la data di accettazione!";
	str2 = "ATTENZIONE!\n» stata scelta una data successiva a quella corrente!";
	CTime dataTemp;
	m_ctrDataProve.GetTime(dataTemp);
	if( dataTemp < m_DataAccettazione)
		{
		m_ctrDataProve.SetTime(&m_DataProve);
		AfxMessageBox(str1);
		}
	if (dataTemp > CTime::GetCurrentTime() )
		AfxMessageBox(str2);
	*pResult = 0;
}


void CMainDlg::OnKillfocusEdtAllungamento() 
{
	UpdateData();
	if(!CalcolaDati(m_bCalcoliConDecimali))
		AfxMessageBox("ATTENZIONE!\nVerificare che il diametro nominale sia coerente con i risultati.");
	UpdateData(FALSE);
}
