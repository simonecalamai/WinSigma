// ArchivioCertificatiView.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "StampaCertificatiDlg.h"
#include "ArchivioCertificatiView.h"
#include "WinsigmaDoc.h"
#include "XFormView.h"
#include "VerbaliView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TUTTI "Tutti"

/////////////////////////////////////////////////////////////////////////////
// CArchivioCertificatiView

IMPLEMENT_DYNCREATE(CArchivioCertificatiView, CFormView)

CArchivioCertificatiView::CArchivioCertificatiView()
	: CFormView(CArchivioCertificatiView::IDD)
{
	//{{AFX_DATA_INIT(CArchivioCertificatiView)
	m_csNumero_Certificato = _T("");
	m_csNumero_Verbale = _T("");
	m_csRagione_Sociale = _T("");
	m_csCodice = _T("");
	m_strNumCertificati = _T("");
	m_strNumeroFattura = _T("");
	//}}AFX_DATA_INIT
}

CArchivioCertificatiView::~CArchivioCertificatiView()
{
	m_pSet->Close();
	delete m_pSet;
}

void CArchivioCertificatiView::Carica_Combo()
{
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CCertificatiSet* pSet = new CCertificatiSet(&pApp->m_db);
	//Serve per caricare la combo con gli anni in cui sono stati emessi dei Certificati
	pSet->m_strFilter = "NumeroCertificato <> 0";
	pSet->m_strSort = "DataEmissione";
	pSet->Open();
  int n = m_cmbAnni.AddString(TUTTI);
  m_cmbAnni.SetItemData(n, 0);
  int year = 0;
  n++;
  for(SET_START(pSet); !pSet->IsEOF(); pSet->MoveNext())
  {
    if(year != pSet->m_DataEmissione.GetYear())
    {
      m_cmbAnni.InsertString(n, pSet->m_DataEmissione.Format("%Y"));
      year = pSet->m_DataEmissione.GetYear();
      m_cmbAnni.SetItemData(n, year);
      n++;
    }
  }
	pSet->Close();
  year = CTime::GetCurrentTime().GetYear();
	//Seleziona come Item corrente quello dell'anno in corso
  for(n = 0; n < m_cmbAnni.GetCount(); n++)
  {
    if(m_cmbAnni.GetItemData(n) == (unsigned int)year)
      break;
  }
	m_cmbAnni.SetCurSel(n);
  // Combo con i tipi di certificato
  CTipiCertificatoSet* pTipiSet = new CTipiCertificatoSet(&pApp->m_db);
  pTipiSet->Open();
  n = m_ComboTipoCertificato.AddString("Tutti");
  m_ComboTipoCertificato.SetItemData(n, 0);
  n++;
  for(SET_START(pTipiSet); !pTipiSet->IsEOF(); pTipiSet->MoveNext())
  {
    m_ComboTipoCertificato.InsertString(n, pTipiSet->m_Nome);
    m_ComboTipoCertificato.SetItemData(n, pTipiSet->m_Codice);
    n++;
  }
  m_ComboTipoCertificato.SetCurSel(0);
  pTipiSet->Close();
}

void CArchivioCertificatiView::Query()
{
	CString sql, str;
	CString csApp;
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  int year = -1;
	//Aggiorna le variabili con il valore contenuto nei campi della form
	UpdateData(TRUE);

	m_cmbAnni.GetLBText(m_cmbAnni.GetCurSel(),csApp);
	//Crea la stringa sql da utilizzare nella Query
	if(csApp != TUTTI)
  {
	  sql = "(DataEmissione >= '" + csApp + "-1-1' AND DataEmissione <= '" + csApp + "-12-31')";
    year = m_cmbAnni.GetItemData(m_cmbAnni.GetCurSel());
  }
	if(!m_strNumeroFattura.IsEmpty())
  {
    CFattureSet* pFatture = new CFattureSet(&pApp->m_db);
    if(year != -1)
      pFatture->m_strFilter.Format("Numero = '%s' AND Data >= '%s' AND Data <= '%s'", m_strNumeroFattura, CTime(year, 1, 1, 0, 0, 0).Format("%Y-%m-%d"), CTime(year, 12, 31, 0, 0, 0).Format("%Y-%m-%d"));
    else
      pFatture->m_strFilter.Format("Numero = '%s' AND Data is not NULL", m_strNumeroFattura);
    pFatture->Open();
    str.Empty();
    while(!pFatture->IsEOF())
    {
      csApp.Format("Fattura = %d OR ", pFatture->m_Codice);
      str += csApp;
      pFatture->MoveNext();
    }
    str.TrimRight(" OR ");
    if(!str.IsEmpty())
    {
      if(sql.IsEmpty())
        sql = "(" + str + ")";
      else
        sql += " AND (" + str + ")";
    }
    pFatture->Close();
  }
  m_ComboTipoCertificato.GetLBText(m_ComboTipoCertificato.GetCurSel(), csApp);
  if(csApp != TUTTI)
  {
    str.Format("TipoCertificato = %ld", m_ComboTipoCertificato.GetItemData(m_ComboTipoCertificato.GetCurSel()));
    if(sql.IsEmpty())
      sql = str;
    else
      sql += " AND " + str;
  }

	if (m_csNumero_Certificato!="")
		{
			if (sql=="")
					sql="(NumeroCertificato = " + m_csNumero_Certificato + ")";
			else
					sql+=" AND (NumeroCertificato = " + m_csNumero_Certificato + ")";
		}

	 if (m_csNumero_Verbale!="")
		{
			if (sql=="")
					sql= "(ProgressivoTotale = " + m_csNumero_Verbale + ")";
			else
					sql+= " AND (ProgressivoTotale = " + m_csNumero_Verbale + ")";
		}
	//Se questo campo contiene dei valori 
	//si seleziona il campo corretto a seconda del radiobutton delezionato
	if (m_csRagione_Sociale!="")
		{
			m_csRagione_Sociale.Replace("'", "''");

			CString CampoApp;

			if (m_rbIntestazione_Certificati)
					CampoApp="NomeIntestatarioCertificato";
			else if (m_rbIntestazione_Fatture)
					CampoApp="NomeIntestatarioFattura";
			else if (m_rbImpresa_Costruttrice)
					CampoApp="NomeImpresaRichiedente";
			else if (m_rbDestinatario_Certificati)
					CampoApp="NomeSpedizioneRitiro";

			if (sql=="")
					sql="(" + CampoApp + " LIKE '%" + m_csRagione_Sociale + "%')";
			else
					sql+=" AND (" + CampoApp + " LIKE '%" + m_csRagione_Sociale + "%')";
		}

	if (m_csCodice!="")
		{
			if (sql=="")
					sql="(IDIntestatarioCertificato = '" + m_csCodice + "')";
			else
					sql+=" AND (IDIntestatarioCertificato = '" + m_csCodice + "')";
		}

	if( sql.IsEmpty() )
		{
		CString msg;
		msg =		"Attenzione, si è scelto di eseguire una ricerca senza nessun filtro.\n";
		msg +=	"Tale operazione mostrerà tutti i documenti presenti nel database e avrà una durata proporzionale al loro numero.\n";
		msg +=	"Procedere comunque con l'operazione?";
		if (IDYES == AfxMessageBox( msg ,MB_YESNO))
			sql = "CERTIFICATI.Verbale = VERBALI.Codice";
		else 
			return;
		}
	else
		sql += " AND CERTIFICATI.Verbale = VERBALI.Codice";
		
	m_pSet->m_strSort = "Verbale, NumeroCertificato";
	m_pSet->m_strFilter = sql;
	m_pSet->Requery();
}

void CArchivioCertificatiView::Popola_Lista()
{
	m_Risultati_Ricerca.DeleteAllItems();
	int nIcon=0, indexProve = 0;
	CString str, strEmenda, strTemp;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CCertificatiSet pCertSet(&pApp->m_db);
	pCertSet.m_strFilter = "Codice = -1";
	pCertSet.Open();
	
	while(!m_pSet->IsEOF())
	{
		if(!m_pSet->IsFieldNull(&m_pSet->m_EmendatoDa))
		{
			pCertSet.m_strFilter.Format("Codice = %d", m_pSet->m_EmendatoDa);
			pCertSet.Requery();
			strEmenda.Format("Em. dal N° %d",pCertSet.m_NumeroCertificato);
			nIcon = 4;
		}
		else if(!m_pSet->IsFieldNull(&m_pSet->m_EmendaIl))
		{
			pCertSet.m_strFilter.Format("Codice = %d", m_pSet->m_EmendaIl);
			pCertSet.Requery();
			strEmenda.Format("Em. il N° %d",pCertSet.m_NumeroCertificato);
			nIcon = 5;
		}
		else
		{
			strEmenda="";
			nIcon = 3;
		}
			

		int n = m_Risultati_Ricerca.GetItemCount();

		str.Format("%d",m_pSet->m_NumeroCertificato);
		str;
		m_Risultati_Ricerca.InsertItem(n,str, nIcon);
		m_Risultati_Ricerca.SetItemData(n,(DWORD)m_pSet->m_CodiceCertificato);

		str = m_pSet->m_DataEmissione.Format("%d/%m/%Y");		
		m_Risultati_Ricerca.SetItemText(n,1,str);

		strTemp = "Chiuso";
		if(m_pSet->IsFieldNull(&m_pSet->m_DataChiusura))
			strTemp = "Aperto";

		str.Format("%d / %d", m_pSet->m_ProgressivoParziale, m_pSet->m_ProgressivoTotale);
		m_Risultati_Ricerca.SetItemText(n,2,str);

		str.Format("%s (%s)", m_pSet->m_DataAccettazione.Format("%d/%m/%Y"), strTemp);
		m_Risultati_Ricerca.SetItemText(n,3,str);

		SINCRONIZE(m_pTipiCertSet, m_pSet->m_TipoCertificato);
		str = strTemp = m_pTipiCertSet->m_Nome;
		str.MakeUpper();
		if((indexProve = str.Find("PROVA")) == 0)
			str = strTemp.Right(strTemp.GetLength() - 6);
		m_Risultati_Ricerca.SetItemText(n,4,str);

		m_Risultati_Ricerca.SetItemText(n,5,m_pSet->m_NomeIntestatarioCertificato);
		m_Risultati_Ricerca.SetItemText(n,6,strEmenda);

		m_pSet->MoveNext();
	}
	pCertSet.Close();
  m_strNumCertificati.Format("%d", m_Risultati_Ricerca.GetItemCount());
  UpdateData(FALSE);
}

bool CArchivioCertificatiView::Congruenza_Dati_Ricerca(CString* msg)
{
	int congruenza(1);

	UpdateData(TRUE);

	for(int i(0);i<m_csNumero_Certificato.GetLength();i++)
		{
			char buf=m_csNumero_Certificato.GetAt(i);
			congruenza = strspn(&buf,"0123456789");
			if (congruenza == 0)
			{
					msg->Insert(0,"Il valore del campo 'Numero certificato' deve essere numerico.");
					return false;
			}
		}

	for(int j(0);j<m_csNumero_Verbale.GetLength();j++)
		{
			char buf=m_csNumero_Verbale.GetAt(j);
			congruenza = strspn(&buf,"0123456789");
			if (congruenza == 0)
			{
					msg->Insert(0,"Il valore del campo 'Numero verbale' deve essere numerico.");
					return false;
			}
		}

	return true;
}

void CArchivioCertificatiView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArchivioCertificatiView)
	DDX_Control(pDX, IDC_COMBO_TIPO, m_ComboTipoCertificato);
	DDX_Control(pDX, IDC_EDIT_NUMERO_CERTIFICATO, m_EditNumeroCertificato);
	DDX_Control(pDX, IDC_COMBO_ANNO, m_cmbAnni);
	DDX_Control(pDX, IDC_LIST_RISULTATO_RICERCA, m_Risultati_Ricerca);
	DDX_Control(pDX, IDC_RADIO_INTESTAZIONE_CERTIFICATI, m_rbIntestazione_Certificati);
	DDX_Control(pDX, IDC_RADIO_INTESTAZIONE_FATTURE, m_rbIntestazione_Fatture);
	DDX_Control(pDX, IDC_RADIO_IMPRESA_COSTRUTTRICE, m_rbImpresa_Costruttrice);
	DDX_Control(pDX, IDC_RADIO_DESTINATARIO_CERTIFICATI, m_rbDestinatario_Certificati);
	DDX_Text(pDX, IDC_EDIT_NUMERO_CERTIFICATO, m_csNumero_Certificato);
	DDX_Text(pDX, IDC_EDIT_NUMEROVERBALE, m_csNumero_Verbale);
	DDX_Text(pDX, IDC_EDIT_RAGIONE_SOCIALE, m_csRagione_Sociale);
	DDV_MaxChars(pDX, m_csRagione_Sociale, 64);
	DDX_Text(pDX, IDC_EDIT_CODICE, m_csCodice);
	DDX_Text(pDX, IDC_EDIT_NUM_CERTIFICATI, m_strNumCertificati);
	DDX_Text(pDX, IDC_EDIT_FATTURA, m_strNumeroFattura);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArchivioCertificatiView, CFormView)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopyCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCopyCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	//{{AFX_MSG_MAP(CArchivioCertificatiView)
	ON_BN_CLICKED(IDC_BUTTON_RICERCA, OnButtonRicerca)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RISULTATO_RICERCA, OnDblclkListRisultatoRicerca)
	ON_COMMAND(ID_BTN_EILIMINACERTIFICATO, OnBtnEliminacertificato)
	ON_COMMAND(IDD_PREVIEW_DOC, OnPreviewDoc)
	ON_COMMAND(ID_STAMPA, OnStampa)
	ON_COMMAND(ID_STAMPA_CON_HEADER, OnStampaConHeader)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArchivioCertificatiView diagnostics

#ifdef _DEBUG
void CArchivioCertificatiView::AssertValid() const
{
	CFormView::AssertValid();
}

void CArchivioCertificatiView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CArchivioCertificatiView message handlers

void CArchivioCertificatiView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	m_pSet = NULL;
	m_pSet = new CCertificatiVerbaliSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
  m_pSet->m_strFilter = "VERBALI.Codice = CERTIFICATI.Verbale";
	m_pSet->Open();

	Carica_Combo();

	m_rbIntestazione_Certificati.SetCheck(1);

	unsigned long style = m_Risultati_Ricerca.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT;
	m_Risultati_Ricerca.SetExtendedStyle(style);

	m_imgCertificati.Create(IDB_IMAGELIST_SERIE, 16, 0, RGB(0,128,128));
  m_Risultati_Ricerca.SetImageList(&m_imgCertificati, LVSIL_SMALL);

	m_Risultati_Ricerca.InsertColumn(0,"N° doc.",LVCFMT_CENTER, 60, -1);
	m_Risultati_Ricerca.InsertColumn(1,"Emesso il",LVCFMT_CENTER, 70, -1);
	m_Risultati_Ricerca.InsertColumn(2,"Verbale",LVCFMT_CENTER, 80, -1);
	m_Risultati_Ricerca.InsertColumn(3,"Data V.A.",LVCFMT_CENTER, 113, -1);
	m_Risultati_Ricerca.InsertColumn(4,"Tipo prove",LVCFMT_LEFT, 135, -1);
	m_Risultati_Ricerca.InsertColumn(5,"Intestatario",LVCFMT_LEFT, 190, -1);
	m_Risultati_Ricerca.InsertColumn(6,"Emendamenti",LVCFMT_LEFT, 80, -1);
	
	m_Risultati_Ricerca.DeleteAllItems();	

	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
	m_pTipiCertSet = pDoc->m_pTipiCertificatoSet;
  m_EditNumeroCertificato.SetFocus();
}

void CArchivioCertificatiView::OnButtonRicerca() 
{
	//Controlla la congruenza dei dati presenti nei campi di selezione della Query
	CString msg("");
	if (Congruenza_Dati_Ricerca(&msg) == true)
	{
    m_strNumCertificati.Empty();
    UpdateData(FALSE);
		//Esecuzione della query
		Query();

		//Popolamento della lista con il risultato della Query
		Popola_Lista();
	}
	else
	{
		AfxMessageBox(msg);
	}
}

BOOL CArchivioCertificatiView::IsEditCtrl(CWnd* pWnd)
{
	// CG: This function was added by the Clipboard Assistant component
	ASSERT_VALID(pWnd);

	TCHAR lpClassName[32];
	::GetClassName(pWnd->GetSafeHwnd(), lpClassName, 32);

	if (!_tcscmp(lpClassName, _T("Edit")))
		return TRUE;

	return FALSE;
}

void CArchivioCertificatiView::OnUpdateEditCopyCut(CCmdUI* pCmdUI)
{
	// CG: This block was added by the Clipboard Assistant component
	{
		CWnd* pWnd = CWnd::GetFocus();

		if (pWnd != NULL)
		{
			if (IsEditCtrl(pWnd))
			{
				int nStart, nEnd;
				((CEdit*)pWnd)->GetSel(nStart, nEnd);
				pCmdUI->Enable(nStart != nEnd);
				return;
			}
		}
	}

	pCmdUI->Enable(FALSE);
}

void CArchivioCertificatiView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
	// CG: This block was added by the Clipboard Assistant component
	{
		CWnd* pWnd = CWnd::GetFocus();

		if (pWnd != NULL)
		{
			if (IsEditCtrl(pWnd))
			{
				pCmdUI->Enable(::IsClipboardFormatAvailable(CF_TEXT));
				return;
			}
		}
	}

	pCmdUI->Enable(FALSE);
}

void CArchivioCertificatiView::OnUpdateEditUndo(CCmdUI* pCmdUI)
{
	// CG: This block was added by the Clipboard Assistant component
	{
		CWnd* pWnd = CWnd::GetFocus();

		if (pWnd != NULL)
		{
			if (IsEditCtrl(pWnd))
			{
				pCmdUI->Enable(((CEdit*)pWnd)->CanUndo());
				return;
			}
		}
	}

	pCmdUI->Enable(FALSE);
}

void CArchivioCertificatiView::OnEditCopy()
{
	// CG: This block was added by the Clipboard Assistant component
	{
		CEdit* pEdit = (CEdit*)CWnd::GetFocus();
		pEdit->Copy();
	}
}

void CArchivioCertificatiView::OnEditCut()
{
	// CG: This block was added by the Clipboard Assistant component
	{
		CEdit* pEdit = (CEdit*)CWnd::GetFocus();
		pEdit->Cut();
	}
}

void CArchivioCertificatiView::OnEditPaste()
{
	// CG: This block was added by the Clipboard Assistant component
	{
		CEdit* pEdit = (CEdit*)CWnd::GetFocus();
		pEdit->Paste();
	}
}

void CArchivioCertificatiView::OnEditUndo()
{
	// CG: This block was added by the Clipboard Assistant component
	{
		CEdit* pEdit = (CEdit*)CWnd::GetFocus();
		pEdit->Undo();
	}
}



///////////////////////////////////////////////////////////////////////////////////////////
// Funzione disponibile esclusivamente per gli operatori con permessi di amministrazione
// Dopo avere chiesto la conferma procede con l'eliminazione del record relativo al 
// certificato scelto e azzera il campo relativo nei record relativi alle serie interessate

void CArchivioCertificatiView::OnBtnEliminacertificato() 
{
	UpdateData();
	int n;
  POSITION pos;
	long codCert;
	CString msg,strDatiOccupante;
	CWinSigmaApp*		pApp = (CWinSigmaApp*)AfxGetApp();

	if(pApp->GetUserPrivileges() != PRIV_AMMINISTRAZIONE)
	{
		AfxMessageBox("Utente non autorizzato a questa operazione!");
		return;
	}  
	CVerbaliSet			verbSet(&pApp->m_db);
	CCertificatiSet certSet(&pApp->m_db);
	CCertificatiSet certSetEmnda(&pApp->m_db);
	CSerieSet				serieSet(&pApp->m_db);
	CProviniSet			provSet(&pApp->m_db);
	
	certSetEmnda.m_strFilter="Codice=-1";
	certSetEmnda.Open()	;
	
  pos = m_Risultati_Ricerca.GetFirstSelectedItemPosition();
	if((n = m_Risultati_Ricerca.GetNextSelectedItem(pos)) < 0)
	{
    AfxMessageBox("Selezionare un dato valido!");
	  return;
	}

	codCert = m_Risultati_Ricerca.GetItemData(n);
	certSet.m_strFilter.Format("Codice = %d", codCert);
	certSet.Open();
	if(certSet.IsEOF())
  {
		AfxMessageBox("Selezionare un dato valido!");
	  return;
	}
	
	msg.Format("Confermi l'eliminazione del certificato N°%d emesso in data %s", certSet.m_NumeroCertificato, certSet.m_DataEmissione.Format("%d/%m/%Y"));
	if(IDYES == AfxMessageBox(msg, MB_YESNO))	
	{
		certSetEmnda.m_strFilter.Format("EmendaIl = %d", certSet.m_Codice);
		certSetEmnda.Requery();
		if(!certSetEmnda.IsEOF())
		{
			msg.Format("Operazione non consentita!\nIl certificato risulta emendato dal documento N° %d.",certSetEmnda.m_NumeroCertificato);
			AfxMessageBox(msg);
			return;
		}

		certSetEmnda.m_strFilter.Format("EmendatoDa = %d", certSet.m_Codice);
		certSetEmnda.Requery();
		if(!certSetEmnda.IsEOF())
		{
			msg.Format("Il certificato risulta essere l'emendamento del documento N° %d.\nProcedere con l'operazione di eliminazione?",certSetEmnda.m_NumeroCertificato);
			if(!(IDYES==AfxMessageBox(msg, MB_YESNO)) )
				return;
		}

		// Verifico che il verbale interessato non sia in uso
		verbSet.m_strFilter.Format("Codice = %d", certSet.m_Verbale);
		verbSet.Open();
		if(!pApp->SetVerbaleInUso(verbSet.m_Codice))
			return;
		serieSet.m_strFilter.Format("Certificato = %d", codCert);
		serieSet.Open();
		
		// Verificato che non ci siano in atto operazioni di certificazione
		if(!pApp->DisabilitaCertificazione(&strDatiOccupante))
		{
  		msg = STR_BLOCCO_CERTIFICAZIONE(strDatiOccupante);
			msg = msg + STR_ISTRUZIONI_RIMOZIONE;
			AfxMessageBox(msg);
			pApp->SetVerbaleInUso(verbSet.m_Codice, TRUE);
			return;
		}
		/*----- avvio la transazione -----*/
		try
		{
			pApp->BeginTrans();
			certSet.Delete();

			// Se sto rimuovendo un emendamento rimuovo il riferimento all'emendato
			// E le serie ed i provini legati al documento da eliminare
			if(!certSetEmnda.IsEOF())
			{
				CString str, queryProvini="Codice = -1";
				certSetEmnda.Edit();
				certSetEmnda.SetFieldNull(&certSetEmnda.m_EmendatoDa);
				certSetEmnda.Update();
				while(!serieSet.IsEOF())
				{
					str.Format(" OR Serie = %d", serieSet.m_Codice);
					serieSet.Delete();
					serieSet.MoveNext();
				}
				provSet.m_strFilter = queryProvini;
				provSet.Open();
				while(!provSet.IsEOF())
				{
					provSet.Delete();
					serieSet.MoveNext();
				}
			}
			else
			{
        // Se elimino un certificato normale, dalle serie tolgo solo il riferimento 
				while(!serieSet.IsEOF())
				{
					serieSet.Edit();
					serieSet.m_Certificato = 0;
					serieSet.Update();
					serieSet.MoveNext();
				}
			}
			pApp->CommitTrans();
		}	
		
		/*--------------------------------*/
		catch(CDBException* e)
		{
      pApp->Rollback();
      pApp->UnlockTables();
      AfxMessageBox("Attenzione operazione non riuscita!\n" + e->m_strError);
			pApp->DisabilitaCertificazione(&strDatiOccupante, FALSE);
			pApp->SetVerbaleInUso(verbSet.m_Codice, TRUE);
      return;
    }
		pApp->DisabilitaCertificazione(&strDatiOccupante, FALSE);
		pApp->SetVerbaleInUso(verbSet.m_Codice, TRUE);
  	m_pSet->Requery();
  	Popola_Lista();
	}
}


void CArchivioCertificatiView::OnPreviewDoc() 
{
	
}

void CArchivioCertificatiView::OnDblclkListRisultatoRicerca(NMHDR* pNMHDR, LRESULT* pResult) 
{
  StampaCertificato();
  *pResult = 0;
}


void CArchivioCertificatiView::OnStampa() 
{
	StampaCertificato();
}


void CArchivioCertificatiView::StampaCertificato(BOOL bHeader)
{
  POSITION pos;
  int n;
  long codCert;
	if((pos = m_Risultati_Ricerca.GetFirstSelectedItemPosition()) == NULL)
  {
    AfxMessageBox("Selezionare un documento.");
    return;
  }
	if((n = m_Risultati_Ricerca.GetNextSelectedItem(pos)) < 0)
	{
    AfxMessageBox("Selezionare un dato valido!");
	  return;
	}
	codCert = m_Risultati_Ricerca.GetItemData(n);
	

	CVerbaliView::StampaCertificato(m_pTipiCertSet, codCert, FALSE, bHeader);
//	CVerbaliView::StampaCertificato(codCert, FALSE);
}

void CArchivioCertificatiView::OnStampaConHeader() 
{
	StampaCertificato(TRUE);
}
