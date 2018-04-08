// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CompressioneCubiDM2018.h"
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
	m_lfAltezza = 0.0;
	m_lfCaricoSp = 0.0;
	m_lfLarghezza = 0.0;
	m_lfLunghezza = 0.0;
	m_lfMassa = 0.0;
	m_strCbTipoRottura = _T("");
	m_strArea = _T("");
	m_strCompressione = _T("");
	m_strRottura = _T("");
	m_strDataPrelievo = _T("");
	m_DataProva = 0;
	m_strSigla = _T("");
	m_strMacchina = _T("");
	m_strSperimentatore = _T("");
	m_strOsservazioni = _T("");
	m_strStruttura = _T("");
	m_strPosizione = _T("");
	m_strDataAccettazione = _T("");
	m_strLunghezza = _T("Lunghezza (cm)");
	m_strLarghezza = _T("Larghezza (cm)");
	m_strAltezza = _T("Altezza (cm)");
	m_strUMArea = _T("(cm²)");
	//}}AFX_DATA_INIT
}


void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CXDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDlg)
	DDX_Control(pDX, IDC_EDIT_OSSERVAZIONI, m_EdtOsservazioni);
	DDX_Control(pDX, IDC_COMBO_SPERIMENTATORI, m_ComboSperimentatori);
	DDX_Control(pDX, IDC_COMBO_MACCHINE, m_ComboMacchine);
	DDX_Control(pDX, IDCANCEL, m_BtnCancel);
	DDX_Control(pDX, IDOK, m_BtnOk);
	DDX_Control(pDX, IDC_CHECK_SPIANATURA, m_BtnSpianatura);
	DDX_Control(pDX, IDC_TREE_PROVINI, m_TreeProvini);
	DDX_Control(pDX, IDC_DATA_PROVA, m_ctrDataTest);
	DDX_Control(pDX, IDC_EDIT_MASSA, m_EdtMassa);
	DDX_Control(pDX, IDC_EDIT_LUNGHEZZA, m_EdtLunghezza);
	DDX_Control(pDX, IDC_EDIT_LARGHEZZA, m_EdtLarghezza);
	DDX_Control(pDX, IDC_EDIT_CARICO_SP, m_EdtCaricoSp);
	DDX_Control(pDX, IDC_EDIT_ALTEZZA, m_EdtAltezza);
	DDX_Control(pDX, IDC_COMBO_TIPO_ROTTURA, m_ComboTipoRottura);
	DDX_Control(pDX, IDC_BTN_MODIFICA, m_BtnModifica);
	DDX_Control(pDX, IDC_BTN_CONFERMA, m_BtnConferma);
	DDX_Control(pDX, IDC_BTN_ANNULLA, m_BtnAnnulla);
	DDX_Text(pDX, IDC_EDIT_ALTEZZA, m_lfAltezza);
	DDX_Text(pDX, IDC_EDIT_CARICO_SP, m_lfCaricoSp);
	DDX_Text(pDX, IDC_EDIT_LARGHEZZA, m_lfLarghezza);
	DDX_Text(pDX, IDC_EDIT_LUNGHEZZA, m_lfLunghezza);
	DDX_Text(pDX, IDC_EDIT_MASSA, m_lfMassa);
	DDX_CBString(pDX, IDC_COMBO_TIPO_ROTTURA, m_strCbTipoRottura);
	DDX_Text(pDX, IDC_EDIT_AREA, m_strArea);
	DDX_Text(pDX, IDC_EDIT_COMPRESSIONE, m_strCompressione);
	DDX_Text(pDX, IDC_EDIT_ROTTURA, m_strRottura);
	DDX_Text(pDX, IDC_EDIT_DATA_PRELIEVO, m_strDataPrelievo);
	DDX_DateTimeCtrl(pDX, IDC_DATA_PROVA, m_DataProva);
	DDX_Text(pDX, IDC_EDIT_SIGLA, m_strSigla);
	DDX_CBString(pDX, IDC_COMBO_MACCHINE, m_strMacchina);
	DDX_CBString(pDX, IDC_COMBO_SPERIMENTATORI, m_strSperimentatore);
	DDX_Text(pDX, IDC_EDIT_OSSERVAZIONI, m_strOsservazioni);
	DDX_Text(pDX, IDC_EDIT_STRUTTURA, m_strStruttura);
	DDX_Text(pDX, IDC_EDIT_POSIZIONE, m_strPosizione);
	DDX_Text(pDX, IDC_EDID_DATA_VA, m_strDataAccettazione);
	DDX_Text(pDX, IDC_STC_DIM1, m_strLunghezza);
	DDX_Text(pDX, IDC_STC_DIM2, m_strLarghezza);
	DDX_Text(pDX, IDC_STC_3, m_strAltezza);
	DDX_Text(pDX, IDC_STATIC_AREA, m_strUMArea);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainDlg, CXDialog)
	//{{AFX_MSG_MAP(CMainDlg)
	ON_BN_CLICKED(IDC_BTN_CONFERMA, OnBtnConferma)
	ON_BN_CLICKED(IDC_BTN_MODIFICA, OnBtnModifica)
	ON_BN_CLICKED(IDC_BTN_ANNULLA, OnBtnAnnulla)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_PROVINI, OnSelchangedTreeProvini)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_PROVINI, OnDblclkTreeProvini)
	ON_NOTIFY(DTN_CLOSEUP, IDC_DATA_PROVA, OnCloseupDataProva)
	ON_CBN_SELCHANGE(IDC_COMBO_SPERIMENTATORI, OnSelchangeComboSperimentatori)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_EN_KILLFOCUS(IDC_EDIT_CARICO_SP, OnKillfocusEditCaricoSp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog() 
{
	CXDialog::OnInitDialog();
	m_bDatiCambiati = FALSE;
	
	// Apertura dei recordset utilizzati
	m_pServiziListinoSet->m_strSort = "Codice";
	m_pServiziListinoSet->m_strFilter.Format("Certificato = %d",m_pSerieSet->m_TipoCertificato);
	SAFETY_OPEN(m_pServiziListinoSet);
	m_pProviniSet->m_strSort = "Serie";
	m_pProviniSet->m_strFilter.Format("Serie = %d",m_pSerieSet->m_Codice);
  m_pProviniSet->m_strSort = "Codice";
	SAFETY_OPEN(m_pProviniSet);
	SAFETY_OPEN(m_pOperatoriSet);

	//--- Verifico se la serie fa parte di un certificato già emesso ---//
	m_bDatiModificabili = m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Certificato) 
		|| m_pSerieSet->m_Certificato == 0;

	
	//--- Lettura e preparazione dei dati relativi al certificato ---//
	DatiCertificato();


	// Ricerca delle date di prelievo e di prova e di accettazione
	m_strDataAccettazione = m_DataAccettazione.Format("%d/%m/%Y");
	if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_DataPrelievo))
		{
		m_DataPrelievo = m_pSerieSet->m_DataPrelievo;
		m_strDataPrelievo = m_pSerieSet->m_DataPrelievo.Format("%d/%m/%Y");
		if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_DataProva))
			m_DataProva = m_pSerieSet->m_DataProva;
		else
			{
			  m_DataProva = *m_pUltimaDataProva;
			}
			/*{
			CTimeSpan maturazione(m_nGiorniMaturazione,0,0,0);
			m_DataProva = max((m_DataPrelievo + maturazione), m_DataAccettazione);
			}*/
		}
	else
		{
		m_DataPrelievo = 0;
		m_strDataPrelievo = m_pSerieSet->m_strDataND;
		if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_DataProva))
			m_DataProva = m_pSerieSet->m_DataProva;
		else
      m_DataProva = *m_pUltimaDataProva;
			//m_DataProva = max(CTime::GetCurrentTime(), m_DataAccettazione);
		}

	UpdateData(FALSE);//scrivo nel dialogo

	// determino se il servizio di spianatura è stato richiesto 
	m_bSpianaturaRichiesta = RichiestaSpianatura();
	if(m_bSpianaturaRichiesta)
		{
		m_BtnSpianatura.SetCheck(1);
		m_BtnSpianatura.EnableWindow(FALSE);
		}
	// se non è stato richiesto verifico se è stato aggiunto
	else if (! m_pSerieSet->IsFieldNull(&m_pSerieSet->m_ServAggiunto) && 
											m_pSerieSet->m_ServAggiunto == 	m_pSerieSet->m_ServAggiungibile)
		{
		m_BtnSpianatura.SetCheck(1);
		}

	// ----- Inserisco i dai statici della serie nel dialogo ---- //
	if (! m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Sigla) )
		{
		m_strSigla = m_pSerieSet->m_Sigla;
		}
	if (! m_pSerieSet->IsFieldNull(&m_pSerieSet->m_StrutturaPrelievo) )
		{
		m_strStruttura = m_pSerieSet->m_StrutturaPrelievo;
		}
	UpdateData(FALSE);//scrivo nel dialogo

	
	// Inizializzazione della lista delle icone dei provini
	HICON icon[4];
	icon[0]	= AfxGetApp()->LoadIcon(IDI_ICON_INTERA);
	icon[1]	= AfxGetApp()->LoadIcon(IDI_ICON_INTERA_SELECT);
	icon[2]	= AfxGetApp()->LoadIcon(IDI_ICON_NOSELECT);
	icon[3]	= AfxGetApp()->LoadIcon(IDI_ICON_SELECT);
	m_imageList.Create(16, 16, 0, 8, 8);
	for(int n=0; n<4;n++)
		m_imageList.Add(icon[n]);
	m_TreeProvini.SetImageList(&m_imageList, TVSIL_NORMAL);


	//Inserimento dei dati nella combo dei tipi di rottura
	int index = 0;
	CString str;

  str.Format("%d - Soddisfacente",SODDISFACENTE);
  index = m_ComboTipoRottura.AddString(str);
  m_ComboTipoRottura.SetItemData( index, SODDISFACENTE);
  str.Format("%d - Non Soddisfacente",NON_SODDISFACENTE);
  index = m_ComboTipoRottura.AddString(str);	
  m_ComboTipoRottura.SetItemData( index, NON_SODDISFACENTE);
	// riempimento dell'albero selezionando il primo elemento
	RiempiAlbero(FALSE);

	// Preparazione delle abilitazioni dei controlli
	DisableModify(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/////////////////////////////////////////////////////////////
// Gestione dei controlli dalla visualizzazione alla modifica

void CMainDlg::DisableModify(boolean disabilita)
{
	if( m_bDatiModificabili)
		{
		m_EdtLarghezza.SetReadOnly(disabilita);
		m_EdtLunghezza.SetReadOnly(disabilita);
		m_EdtAltezza.SetReadOnly(disabilita);
		m_EdtCaricoSp.SetReadOnly(disabilita);
		m_EdtMassa.SetReadOnly(disabilita);
		m_ComboTipoRottura.EnableWindow(!disabilita);
		
		m_TreeProvini.EnableWindow(disabilita);
		m_BtnModifica.EnableWindow(disabilita);
		m_BtnAnnulla.EnableWindow(!disabilita);
		m_BtnConferma.EnableWindow(!disabilita);
		m_BtnOk.EnableWindow(disabilita);
		m_EdtOsservazioni.SetReadOnly(!m_pSerieSet->m_NuovoCertificato);
		m_ComboSperimentatori.EnableWindow(m_pSerieSet->m_NuovoCertificato);
		m_ComboMacchine.EnableWindow(m_pSerieSet->m_NuovoCertificato);
		
		if(!m_bDatiCambiati)
			m_BtnCancel.EnableWindow(disabilita);
		else
			m_BtnCancel.EnableWindow(FALSE);
		}
	else
		{
		m_EdtLarghezza.SetReadOnly(TRUE);
		m_EdtLunghezza.SetReadOnly(TRUE);
		m_EdtAltezza.SetReadOnly(TRUE);
		m_EdtCaricoSp.SetReadOnly(TRUE);
		m_EdtMassa.SetReadOnly(TRUE);

		m_BtnAnnulla.EnableWindow(FALSE);
		m_BtnConferma.EnableWindow(FALSE);
		m_ComboTipoRottura.EnableWindow(FALSE);
		m_ctrDataTest.EnableWindow(FALSE);
		m_BtnModifica.EnableWindow(disabilita);
		m_BtnSpianatura.EnableWindow(FALSE);
		m_BtnOk.EnableWindow(FALSE);
		m_EdtOsservazioni.SetReadOnly(TRUE);
		m_ComboSperimentatori.EnableWindow(FALSE);
		m_ComboMacchine.EnableWindow(FALSE);
		
		}
}


//////////////////////////////////////////////////////////
// Istanzia il blob e lo inizializza con valori di default

CByteArray* CMainDlg::InitBlob()
{
	CByteArray* blob	= new CByteArray();		//Creazione del blob contenitore
	dati* pDati				= new dati();					//Creazione della struttura specializzata
	pDati->nVersione	= 0;									//Inserimento del numero di versione
	pDati->alt				= m_pSerieSet->m_Dimensione1;
	pDati->larg				= m_pSerieSet->m_Dimensione2;
	pDati->lung				= m_pSerieSet->m_Dimensione3;
	pDati->massa			= 0;
	pDati->caricoSp		= 0;
	pDati->tipoRott		= 1;

	
	// Riempimento del blob contenitore
	char *p_ary = (char*)pDati;
	for(int i=0;i<sizeof(struct dati);i++)	
		{
		blob->Add(*p_ary);
		p_ary++;
		}
	return blob;	// Restituzione del puntatore al nuovo blob											
}


///////////////////////////////////////////////////////////////////
// Trascrive i dati dal dialogo al blob e lo memorizza sul database

///////////////////////////////////////////////////////////////////
// Trascrive i dati dal dialogo al blob e lo memorizza sul database

void CMainDlg::OnBtnConferma() 
{
	if(UpdateData(TRUE))//Solo se i dati sono stati validati
	{
		m_bDatiCambiati = TRUE;
		DisableModify(TRUE);
		switch(m_pDatiCorrenti->nVersione)
			{
			case 0://elaborazione dei dati per la versione 0
				{
					m_pDatiCorrenti->lung				= m_lfLunghezza;
					m_pDatiCorrenti->larg				= m_lfLarghezza;
					m_pDatiCorrenti->alt				= m_lfAltezza;
					m_pDatiCorrenti->massa			= m_lfMassa;
					m_pDatiCorrenti->caricoSp		= m_lfCaricoSp;

					int index = m_ComboTipoRottura.GetCurSel();
					m_pDatiCorrenti->tipoRott	= (byte)m_ComboTipoRottura.GetItemData(index);
				};
			case 1 :; // predisposizione per l'introduzione di nuovi campi alla struttura dati
			}
		
		UpdateData(FALSE);
		try
		{
			m_pProviniSet->m_pDatabase->BeginTrans();	
			m_pProviniSet->Edit();
			m_pProviniSet->m_DataInserimento = CTime::GetCurrentTime();
			m_pProviniSet->SetFieldDirty(&m_pProviniSet->m_Risultati,TRUE);
			m_pProviniSet->Update();
			m_pProviniSet->m_pDatabase->CommitTrans();
		}
		catch(CDBException* e)
		{
			if(e->m_nRetCode == 1008) // AFX_SQL_ERROR_NO_ROWS_AFFECTED
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



void CMainDlg::OnBtnModifica() 
{
	if( m_bDatiModificabili )
		{
		DisableModify(FALSE);
		HTREEITEM hItem = m_TreeProvini.GetSelectedItem();
		m_nCodProvinoCorrente = m_TreeProvini.GetItemData(hItem);	
		m_EdtLunghezza.SetFocus();
		m_EdtLunghezza.SetSel(0, -1);
	}
	else 
		{
			byte test = AfxMessageBox("Attenzione: La serie fa parte di un certificato già emesso.\nContinuare con le modifiche?", MB_YESNO);
			if(IDYES == test)
			{
			m_bDatiModificabili = TRUE;
			m_EdtOsservazioni.SetReadOnly(FALSE);
			m_ComboSperimentatori.EnableWindow(TRUE);
			m_ComboMacchine.EnableWindow(TRUE);		
			m_ctrDataTest.EnableWindow(TRUE);
			m_BtnSpianatura.EnableWindow(TRUE);
			DisableModify(FALSE);
			HTREEITEM hItem = m_TreeProvini.GetSelectedItem();
			m_nCodProvinoCorrente = m_TreeProvini.GetItemData(hItem);	
			m_EdtLunghezza.SetFocus();
			m_EdtLunghezza.SetSel(0, -1);
			}
		}

}


///////////////////////////////////////////////////////////////
// Ripristina i valori del dialogo con quelli presenti nel blob

void CMainDlg::OnBtnAnnulla() 
{
	switch(m_pDatiCorrenti->nVersione)
		{
		case 0:
			{
				m_lfLunghezza				= m_pDatiCorrenti->lung;
				m_lfLarghezza				= m_pDatiCorrenti->larg;
				m_lfAltezza					= m_pDatiCorrenti->alt;
				m_lfMassa						= m_pDatiCorrenti->massa;
				m_strCbTipoRottura	= m_pDatiCorrenti->tipoRott;
				m_lfCaricoSp				= m_pDatiCorrenti->caricoSp;
			
			};
		case 1 :; // predisposizione per l'introduzione di nuovi campi alla struttura dati
		}

	// Cancello i dati eventualmente presenti nei campi relativi ai dati calcolati
	m_strArea = "";
	m_strCompressione = "";
	m_strRottura = "";
				
	UpdateData(FALSE);
	CalcolaDati();
	UpdateData(FALSE);
				
	DisableModify(TRUE);
	m_TreeProvini.SetFocus();
}


//////////////////////////////////////////////////////////////
// restituisce TRUE se è richiesto il servizio aggiungibile;

BOOL CMainDlg::RichiestaSpianatura()
{

	BOOL spianaturaRichiesta = FALSE;
	long codServAgg = 0;
	if( !m_pSerieSet->IsFieldNull(&m_pSerieSet->m_ServAggiungibile) )
		codServAgg = m_pSerieSet->m_ServAggiungibile;
	else
		return FALSE;

	if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Servizio1))
		spianaturaRichiesta |= (m_pSerieSet->m_Servizio1 == codServAgg);
		
	if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Servizio2))
		spianaturaRichiesta |= (m_pSerieSet->m_Servizio2 == codServAgg);
	
	if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Servizio3))
			spianaturaRichiesta |= (m_pSerieSet->m_Servizio3 == codServAgg);

	if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Servizio4))
		spianaturaRichiesta |= (m_pSerieSet->m_Servizio4 == codServAgg);
	
	if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Servizio5))
		spianaturaRichiesta |= (m_pSerieSet->m_Servizio5 == codServAgg);
	
	if(!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Servizio6))
		spianaturaRichiesta |= (m_pSerieSet->m_Servizio6 == codServAgg);
	
	return spianaturaRichiesta;
}


/////////////////////////////////////////////////////////////////////
// Chiamata quando è cambiata la selezione da un provino ad un altro,
// seleziona il blob dal recordset e mostr il contenuto nei campi del dialogo.
// Se il dato è già stato confermato tenta di riempire anche i campi contenenti 
// i dati calcolati

void CMainDlg::OnSelchangedTreeProvini(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	HTREEITEM hItem = m_TreeProvini.GetSelectedItem();

	long codProvino = m_TreeProvini.GetItemData(hItem);

	//Sincronizzo il provino del recordset con quello selezionato
	SAFETY_OPEN(m_pProviniSet);
	SINCRONIZE(m_pProviniSet, codProvino);	
	// Converto il blob nella struttura dati adatta
	m_pDatiCorrenti = (dati*)m_pProviniSet->m_Risultati.GetData();
	switch(m_pDatiCorrenti->nVersione)
		{
		case 0:
			{
				m_lfLunghezza				= m_pDatiCorrenti->lung;
				m_lfLarghezza				= m_pDatiCorrenti->larg;
				m_lfAltezza					= m_pDatiCorrenti->alt;
				m_lfMassa						= m_pDatiCorrenti->massa;
				m_lfCaricoSp				= m_pDatiCorrenti->caricoSp;
				UpdateData(FALSE);
				for(int pos = 0; pos < m_ComboTipoRottura.GetCount(); pos++)
					if((byte)m_ComboTipoRottura.GetItemData(pos) == m_pDatiCorrenti->tipoRott)
						{
						m_ComboTipoRottura.SetCurSel(pos);
						UpdateData(TRUE);
						}
				// Cancello i dati eventualmente presenti nei campi relativi ai dati calcolati
				m_strArea = "";
				m_strCompressione = "";
				m_strRottura = "";
				CalcolaDati();
			};
		case 1 :; // predisposizione per l'introduzione di nuovi campi alla struttura dati
		}
	UpdateData(FALSE);
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
		HTREEITEM hItem = m_TreeProvini.GetSelectedItem();
		m_nCodProvinoCorrente = m_TreeProvini.GetItemData(hItem);	
		m_EdtLunghezza.SetFocus();
		m_EdtLunghezza.SetSel(0, -1);
		}
	else 
		{
			byte test = AfxMessageBox("Attenzione: La serie fa parte di un certificato già emesso.\nContinuare con le modifiche?", MB_YESNO);
			if(IDYES == test)
			{
			m_bDatiModificabili = TRUE;
			m_EdtOsservazioni.SetReadOnly(FALSE);
			m_ComboSperimentatori.EnableWindow(TRUE);
			m_ComboMacchine.EnableWindow(TRUE);	
			m_ctrDataTest.EnableWindow(TRUE);
			m_BtnSpianatura.EnableWindow(TRUE);
			DisableModify(FALSE);
			HTREEITEM hItem = m_TreeProvini.GetSelectedItem();
			m_nCodProvinoCorrente = m_TreeProvini.GetItemData(hItem);	
			m_EdtLunghezza.SetFocus();
			m_EdtLunghezza.SetSel(0, -1);
			}
		}
	*pResult = 0;

}



//////////////////////////////////////////////////////////////////
// Riempie l'albero selezionando il primo elemento se il parametro 
// booleano è falso, altrimenti ribadisce la selezione rilevata

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
			m_pProviniSet->m_Risultati.Copy(*InitBlob());//Se il campo è null viene inizializzato con valori di default
			m_pProviniSet->Update();
		}
		if(i == 0 && !m_pSerieSet->m_Sigla.IsEmpty())
		{
			str.Format("Provino %d - %s", i+1, m_pSerieSet->m_Sigla);		// sigla del provino 1
 		}
		else if(i == 1 && !m_pSerieSet->m_Sigla2.IsEmpty())
		{
			str.Format("Provino %d - %s", i+1, m_pSerieSet->m_Sigla2);	// sigla del provino 2
		}
		else
		{ 
			str.Format("Provino %d",i+1);				// sigla progressiva del provino
		}
		
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


///////////////////////////////////////////////////////////////
// Esecuzione delle modifiche relative alla tabella delle serie

void CMainDlg::AggiornaDatiSerie()
{
  UpdateData(TRUE);
	BOOL spianate = m_BtnSpianatura.GetCheck();

	try
	{
		m_pSerieSet->m_pDatabase->BeginTrans();
		if( !m_pSerieSet->m_NuovoCertificato )
		{
			m_pSerieSet->Edit();
			if(!spianate)
				m_pSerieSet->SetFieldNull(&m_pSerieSet->m_ServAggiunto);
			else
				m_pSerieSet->m_ServAggiunto = m_pSerieSet->m_ServAggiungibile;
			
      //if (!m_pSerieSet->IsFieldNull(&m_pSerieSet->m_DataProva))
      m_pSerieSet->m_DataProva = m_DataProva;
      //else
      //  m_pSerieSet->m_DataProva = CTime::GetCurrentTime();

      int u=m_pSerieSet->m_DataProva.GetDay();
			
      m_pSerieSet->Update();
		}
		// -- aggiornamento dati relativi al certificato -- //
	// -- aggiornamento dati relativi al certificato per tutte le serie incluse -- //
		else
		{			
			if(m_ComboMacchine.GetCurSel() != CB_ERR)
				m_ComboMacchine.GetLBText(m_ComboMacchine.GetCurSel(), m_strMacchina);
			if(m_ComboSperimentatori.GetCurSel() != CB_ERR)
				m_ComboSperimentatori.GetLBText(m_ComboSperimentatori.GetCurSel(), m_strSperimentatore);
			m_pSerieSet->Edit();
			m_pSerieSet->m_DataProva = m_DataProva;
			m_pSerieSet->m_Osservazioni = m_strOsservazioni;
			m_pSerieSet->m_Sperimentatore = m_strSperimentatore;
			m_pSerieSet->m_Macchina = m_strMacchina;

			if(!spianate)
				m_pSerieSet->SetFieldNull(&m_pSerieSet->m_ServAggiunto);
			else
				m_pSerieSet->m_ServAggiunto = m_pSerieSet->m_ServAggiungibile;
			m_pSerieSet->Update();
			m_pSerieSet->MoveNext();
			while( !m_pSerieSet->IsEOF() && !m_pSerieSet->m_NuovoCertificato)
			{
				m_pSerieSet->Edit();
				m_pSerieSet->m_Osservazioni = m_strOsservazioni;
				m_pSerieSet->m_Sperimentatore = m_strSperimentatore;
				m_pSerieSet->m_Macchina = m_strMacchina;
				m_pSerieSet->Update();
				m_pSerieSet->MoveNext();
			}
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
}


////////////////////////////////////////////////////////////
// Richiama le operazioni di memorizzazione dati della serie

void CMainDlg::OnOK() 
{
	// Memorizzo lo sperimentatore e la data prova selezionati per riproporli in seguito
	*m_pUltimoSper = m_ComboSperimentatori.GetItemData(m_ComboSperimentatori.GetCurSel());
	*m_pUltimaDataProva = m_DataProva;

	CTime dataMaturazione;
	CTimeSpan maturazione(m_nGiorniMaturazione,0,0,0);
	dataMaturazione = m_DataPrelievo + maturazione;

	if(m_DataProva < dataMaturazione && 
		!(IDOK == AfxMessageBox("ATTENZIONE!!!\nLa data prova inserita non risulta coerente!\nProcedere comunque con il salvataggio dati",MB_OKCANCEL) ) )
				return;
			
	if( m_bDatiModificabili )
		AggiornaDatiSerie( );
	CDialog::OnOK();
}

//////////////////////////////////////////////////////////////////////
// Controllo che la data di prelievo sia posteriore alla data di prova
// in caso di errore avverte e ripristina la situazione precedente

void CMainDlg::OnCloseupDataProva(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CString str1, str2, str3;
	str2 = "ATTENZIONE!\nOperazione non consentita!\nLa data scelta precede la data di prelievo o la data di accettazione!";
	str3 = "ATTENZIONE!\nÈ stata scelta una data successiva a quella corrente!";
	CTime dataMaturazione, dataTemp;
	CTimeSpan maturazione(m_nGiorniMaturazione,0,0,0);
	dataMaturazione = m_DataPrelievo + maturazione;
	str1.Format("ATTENZIONE!!!\nLa data scelta non è coerente con la data di maturazione prevista (%s).", dataMaturazione.Format("%d/%m/%Y") );
	str1 = str1 + "\nConfermi la data scelta?";
	
	m_ctrDataTest.GetTime(dataTemp);

	if( (dataTemp < m_DataPrelievo)	|| (dataTemp < m_DataAccettazione) )
		{
		m_ctrDataTest.SetTime(&m_DataProva);
		AfxMessageBox(str2);
		}
	else
		{
		if( (dataTemp < dataMaturazione))
			{
			if ( IDYES == AfxMessageBox( str1, MB_YESNO ) ) 
				m_ctrDataTest.GetTime(m_DataProva);
			else
				m_ctrDataTest.SetTime(&m_DataProva);
			}
		else
			m_ctrDataTest.GetTime(m_DataProva);
		}

	if (dataTemp > CTime::GetCurrentTime() )
		AfxMessageBox(str3);
	
	UpdateData();
	
	pResult = 0;
}



///////////////////////////////////////////////////////
// Prepara il dialogo in relazione ai dati presenti nel
// recordset delle serie

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


void CMainDlg::OnButtonNext() 
{
	CXDialog::OnButtonNext();	
}

BOOL CMainDlg::CalcolaDati()
{
	UpdateData();
	//Esecuzione e visualizzazione dei dati calcolati solo se l'area risulta diversa da zero
	if((m_lfLunghezza>0.001) && (m_lfLarghezza>0.001))
	{
		double area					= m_lfLunghezza * m_lfLarghezza;
		double compressione(0);
    compressione = (m_lfCaricoSp / (area/100))*100;
		double rottura			= compressione / 10;
		CString str;
		str.Format("%.0f",area);
		m_strArea = str;
		str.Format("%.3f",compressione);
		m_strCompressione = str;
		str.Format("%.3f",rottura);
		m_strRottura = str;
		return TRUE;
	}
	return FALSE;
}


void CMainDlg::OnKillfocusEditCaricoSp() 
{
	UpdateData();
	CalcolaDati();
	UpdateData(FALSE);
}
