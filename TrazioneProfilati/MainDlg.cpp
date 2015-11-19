// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrazioneProfilati.h"
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
	m_DataProve = 0;
	m_strMateriale = _T("");
	m_strOsservazioni = _T("");
	m_strSigla = _T("");
	m_strStruttura = _T("");
	m_strPosizione = _T("");
	m_lfArea = 0.0;
	m_lfAllungamento = 0.0;
	m_lfRottura = 0.0;
	m_lfSnervamento = 0.0;
	m_strDataAccettazione = _T("");
	//}}AFX_DATA_INIT
}


void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CXDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDlg)
	DDX_Control(pDX, IDC_DATA_PROVA, m_ctrDataProve);
	DDX_Control(pDX, IDC_EDT_SNERVAMENTO, m_EdtSnervamento);
	DDX_Control(pDX, IDC_EDT_ROTTURA, m_EdtRottura);
	DDX_Control(pDX, IDC_EDT_AREA, m_EdtArea);
	DDX_Control(pDX, IDC_EDT_ALLUNGAMENTO, m_EdtAllungamento);
	DDX_Control(pDX, IDC_TREE_PROVINI, m_TreeProvini);
	DDX_Control(pDX, IDOK, m_BtnOk);
	DDX_Control(pDX, IDCANCEL, m_BtnCancel);
	DDX_Control(pDX, IDC_EDIT_OSSERVAZIONI, m_EdtOsservazioni);
	DDX_Control(pDX, IDC_COMBO_SPERIMENTATORI, m_ComboSperimentatori);
	DDX_Control(pDX, IDC_COMBO_MACCHINE, m_ComboMacchine);
	DDX_Control(pDX, IDC_BUTTON_CONFERMA, m_BtnConferma);
	DDX_Control(pDX, IDC_BUTTON_ANNULLA, m_BtnAnnulla);
	DDX_Control(pDX, IDC_BTN_MODIFICA, m_BtnModifica);
	DDX_DateTimeCtrl(pDX, IDC_DATA_PROVA, m_DataProve);
	DDX_Text(pDX, IDC_EDIT_MATERIALE, m_strMateriale);
	DDX_Text(pDX, IDC_EDIT_OSSERVAZIONI, m_strOsservazioni);
	DDX_Text(pDX, IDC_EDIT_SIGLA, m_strSigla);
	DDX_Text(pDX, IDC_EDIT_STRUTTURA, m_strStruttura);
	DDX_Text(pDX, IDC_EDIT_POSIZIONE, m_strPosizione);
	DDX_Text(pDX, IDC_EDT_AREA, m_lfArea);
	DDX_Text(pDX, IDC_EDT_ALLUNGAMENTO, m_lfAllungamento);
	DDX_Text(pDX, IDC_EDT_ROTTURA, m_lfRottura);
	DDX_Text(pDX, IDC_EDT_SNERVAMENTO, m_lfSnervamento);
	DDX_CBString(pDX, IDC_COMBO_MACCHINE, m_strMacchina);
	DDX_CBString(pDX, IDC_COMBO_SPERIMENTATORI, m_strSperimentatore);
	DDX_Text(pDX, IDC_EDIT_DATA_VA, m_strDataAccettazione);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainDlg, CXDialog)
	//{{AFX_MSG_MAP(CMainDlg)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_PROVINI, OnSelchangedTreeProvini)
	ON_BN_CLICKED(IDC_BUTTON_CONFERMA, OnButtonConferma)
	ON_BN_CLICKED(IDC_BUTTON_ANNULLA, OnButtonAnnulla)
	ON_BN_CLICKED(IDC_BTN_MODIFICA, OnBtnModifica)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_PROVINI, OnDblclkTreeProvini)
	ON_CBN_SELCHANGE(IDC_COMBO_SPERIMENTATORI, OnSelchangeComboSperimentatori)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, OnButtonNext)
	ON_NOTIFY(DTN_CLOSEUP, IDC_DATA_PROVA, OnCloseupDataProva)
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
	pDati->area					= 0;
	pDati->snervamento	= 0;
	pDati->rottura			= 0;
	pDati->allungamento = 0;

	char *p_ary = (char*)pDati;
	for(int i=0;i<sizeof(struct dati);i++)	// Riempimento del blob contenitore
		{
		blob->Add(*p_ary);
		p_ary++;
		}
	return blob;										

}


////////////////////////////////////////////////////
// Prepara il dialogo per la lettura/modifica dei dati 
// relativi al certificato 

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
// Gestione dell'abilitazione dei controlli

void CMainDlg::DisableModify(byte disabilita)
{
	if( m_bDatiModificabili )
		{
		m_EdtAllungamento.SetReadOnly(disabilita);
		m_EdtArea.SetReadOnly(disabilita);
		m_EdtRottura.SetReadOnly(disabilita);
		m_EdtSnervamento.SetReadOnly(disabilita);
		m_EdtAllungamento.SetReadOnly(disabilita);
		
		m_TreeProvini.EnableWindow(disabilita);
		m_BtnModifica.EnableWindow(disabilita);
		m_BtnOk.EnableWindow(disabilita);

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
		}
	else
		{
		m_EdtAllungamento.SetReadOnly(TRUE);
		m_EdtArea.SetReadOnly(TRUE);
		m_EdtRottura.SetReadOnly(TRUE);
		m_EdtSnervamento.SetReadOnly(TRUE);
		m_EdtAllungamento.SetReadOnly(TRUE);
		
		m_BtnAnnulla.EnableWindow(FALSE);
		m_BtnConferma.EnableWindow(FALSE);
		m_BtnModifica.EnableWindow(disabilita);
		m_BtnOk.EnableWindow(FALSE);

		m_EdtOsservazioni.SetReadOnly(TRUE);
		m_ComboSperimentatori.EnableWindow(FALSE);
		m_ComboMacchine.EnableWindow(FALSE);
		}

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
// seleziona il blob dal recordset e mostr il contenuto nei campi del dialogo.
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

	// Converto il blob nella struttura dati adatta
	m_pDatiCorrenti = (dati*)m_pProviniSet->m_Risultati.GetData();

	// Eseguo le operazioni di riempimento del dialogo con i valori presenti nel blob
	switch(m_pDatiCorrenti->nVersione)
		{
		case 0:
			{
				m_lfArea					= m_pDatiCorrenti->area;
				m_lfAllungamento	= m_pDatiCorrenti->allungamento;
				m_lfRottura				= m_pDatiCorrenti->rottura;
				m_lfSnervamento		= m_pDatiCorrenti->snervamento;
				UpdateData(FALSE);

			};
		case 1 :; // predisposizione per l'introduzione di nuovi campi alla struttura dati
		}

	*pResult = 0;
}

///////////////////////////////////////////////////////////////////
// Trascrive i dati dal dialogo al blob e lo memorizza sul database

void CMainDlg::OnButtonConferma() 
{
	if(UpdateData(TRUE))
		{
		m_bDatiCambiati = TRUE;
		DisableModify(TRUE);
		switch(m_pDatiCorrenti->nVersione)
			{
			case 0://elaborazione dei dati per la versione 0
				{
					m_pDatiCorrenti->allungamento = m_lfAllungamento;
					m_pDatiCorrenti->area					= m_lfArea;
					m_pDatiCorrenti->rottura			= m_lfRottura;
					m_pDatiCorrenti->snervamento	= m_lfSnervamento;
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



void CMainDlg::OnButtonAnnulla() 
{
	switch(m_pDatiCorrenti->nVersione)
		{
		case 0:
			{
				m_lfArea					= m_pDatiCorrenti->area;
				m_lfAllungamento	= m_pDatiCorrenti->allungamento;
				m_lfRottura				= m_pDatiCorrenti->rottura;
				m_lfSnervamento		= m_pDatiCorrenti->snervamento;
				
			};
		case 1 :; // predisposizione per l'introduzione di nuovi campi alla struttura dati
		}

	UpdateData(FALSE);
	DisableModify(TRUE);
	m_TreeProvini.SetFocus();
}




////////////////////////////////////////////////////
// Abilitazione dei pulsanti di modifica e
// memorizzazione del codice del provino selezionato

void CMainDlg::OnBtnModifica() 
{
	if( m_bDatiModificabili )
	{
		DisableModify(FALSE);
		HTREEITEM hItem = m_TreeProvini.GetSelectedItem();
		m_nCodProvinoCorrente = m_TreeProvini.GetItemData(hItem);	
		m_EdtArea.SetFocus();
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
			DisableModify(FALSE);
			HTREEITEM hItem = m_TreeProvini.GetSelectedItem();
			m_nCodProvinoCorrente = m_TreeProvini.GetItemData(hItem);	
			m_EdtArea.SetFocus();
			}
		}
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
		m_EdtArea.SetFocus();
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
			DisableModify(FALSE);
			HTREEITEM hItem = m_TreeProvini.GetSelectedItem();
			m_nCodProvinoCorrente = m_TreeProvini.GetItemData(hItem);	
			m_EdtArea.SetFocus();
			}
		}
	*pResult = 0;
}


/////////////////////////////////////////////
// Associa la macchina allo sperimentatore

void CMainDlg::OnSelchangeComboSperimentatori() 
{
 int index = m_ComboSperimentatori.GetCurSel();
 m_ComboMacchine.SetCurSel(index);
}




//////////////////////////////////////////////////////////////////////
// Apre i recordset, preleva i dati generali dal recordset delle serie
// rileva il tipo di emissione (A, B, AB), Inizializza e riempie l'albero
// dei provini,

BOOL CMainDlg::OnInitDialog() 
{
	CXDialog::OnInitDialog();
	m_bDatiCambiati = FALSE;
	// Apertura dei recordset utilizzati
	m_pProviniSet->m_strFilter.Format("Serie = %d",m_pSerieSet->m_Codice);
  m_pProviniSet->m_strSort = "Codice";
	SAFETY_OPEN(m_pProviniSet);
	SAFETY_OPEN(m_pOperatoriSet);

	//-- Verifico se la serie appartiene ad un certificato gi‡ emesso
	m_bDatiModificabili = m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Certificato) 
		|| m_pSerieSet->m_Certificato == 0;


	// ----- Inserisco i dai statici della serie nel dialogo ---- //

	// Gestione data prova e data accettazione 
	m_strDataAccettazione = m_DataAccettazione.Format("%d/%m/%Y");
	if( !m_pSerieSet->IsFieldNull(&m_pSerieSet->m_DataProva) )
		m_DataProve = m_pSerieSet->m_DataProva;
	else
		{
		m_DataProve = *m_pUltimaDataProve;
		}

	if (! m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Sigla) )
		{
		m_strSigla = m_pSerieSet->m_Sigla;
		}
	if (! m_pSerieSet->IsFieldNull(&m_pSerieSet->m_StrutturaPrelievo) )
		{
		m_strStruttura = m_pSerieSet->m_StrutturaPrelievo;
		}
	if (! m_pSerieSet->IsFieldNull(&m_pSerieSet->m_Materiale) )
		{
		m_strMateriale = m_pSerieSet->m_Materiale;
		}
	else
		{
		m_strMateriale = "n.d.";
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
	// Assegno la lista di icona alla struttura ad albero
	m_TreeProvini.SetImageList(&m_imageList, TVSIL_NORMAL);

	// Riempio l'albero dei provini selezionando il primo elemento
	RiempiAlbero(FALSE);

	DisableModify(TRUE);

	//Gestione dei dati relativi al certificato
	DatiCertificato();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
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
			m_pSerieSet->Update();
			m_pSerieSet->MoveNext();

			while( !m_pSerieSet->IsEOF() && !m_pSerieSet->m_NuovoCertificato)
			{
				m_pSerieSet->Edit();
				m_pSerieSet->m_DataProva = m_DataProve;
				m_pSerieSet->m_Osservazioni = m_strOsservazioni;
				m_pSerieSet->m_Sperimentatore = m_strSperimentatore;
				m_pSerieSet->m_Macchina = m_strMacchina;
				m_pSerieSet->Update();
				m_pSerieSet->MoveNext();
			}
		}
		else
		{
			UpdateData(TRUE);
			m_pSerieSet->Edit();
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
