// ListiniView.cpp : implementation file
//

#include "stdafx.h"
#include "WinSigma.h"
#include "Printerpreter.h"
#include "winsigmadoc.h"
#include "XFormView.h"
#include "TrovaAziendaDlg.h"
#include "ListiniView.h"
#include "CategorieDlg.h"
#include "ServiziListinoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define STR_LISTINOGENERALE       "Listino generale"

CCategorieSet*        CListiniView::m_pCategorieSet;
CServiziListinoSet*   CListiniView::m_pServiziSet;
CWordArray            CListiniView::m_aryPagine;

/////////////////////////////////////////////////////////////////////////////
// CListiniView

IMPLEMENT_DYNCREATE(CListiniView, CFormView)

CListiniView::CListiniView()
	: CXFormView(CListiniView::IDD)
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	//{{AFX_DATA_INIT(CListiniView)
	m_strAutore = _T("");
	m_strNome = _T("");
	m_strCodice = _T("");
	m_strCodiceAzienda = _T("");
	m_strNomeAzienda = _T("");
	m_nCategorie = 0;
	m_nServizi = 0;
	m_bCertificatiOgniSerie = FALSE;
	m_strInizio = _T("");
	m_strFine = _T("");
	//}}AFX_DATA_INIT
	m_bDenySinc = FALSE;
	m_pCategorieSet = NULL;
	m_pServiziSet   = NULL;
}

CListiniView::~CListiniView()
{
  /*--- distruggo i recordset ----*/
  if(m_pCategorieSet)
	{
	  m_pCategorieSet->Close();
		delete m_pCategorieSet;
  }
  if(m_pServiziSet)
	{
	  m_pServiziSet->Close();
		delete m_pServiziSet;
  }
}

void CListiniView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListiniView)
	DDX_Control(pDX, IDC_EDIT_FINE, m_EditFine);
	DDX_Control(pDX, IDC_EDIT_INIZIO, m_EditInizio);
	DDX_Control(pDX, IDC_CHECK_CERTIFICATIOGNISERIE, m_CheckCertOgniSerie);
	DDX_Control(pDX, IDC_BUTTON_CERCA, m_ButtonCerca);
	DDX_Control(pDX, IDC_EDIT_NOME, m_EditNome);
	DDX_Control(pDX, IDC_LIST_SERVIZI, m_ListServizi);
	DDX_Control(pDX, IDC_LIST_CATEGORIE, m_ListCategorie);
	DDX_Text(pDX, IDC_EDIT_AUTORE, m_strAutore);
	DDV_MaxChars(pDX, m_strAutore, 16);
	DDX_Text(pDX, IDC_EDIT_NOME, m_strNome);
	DDV_MaxChars(pDX, m_strNome, 32);
	DDX_Text(pDX, IDC_EDIT_CODICE, m_strCodice);
	DDX_Text(pDX, IDC_EDIT_CODICEAZIENDA, m_strCodiceAzienda);
	DDX_Text(pDX, IDC_EDIT_NOMEAZIENDA, m_strNomeAzienda);
	DDX_Text(pDX, IDC_EDIT_NCATEGORIE, m_nCategorie);
	DDX_Text(pDX, IDC_EDIT_NSERVIZI, m_nServizi);
	DDX_Check(pDX, IDC_CHECK_CERTIFICATIOGNISERIE, m_bCertificatiOgniSerie);
	DDX_Text(pDX, IDC_EDIT_INIZIO, m_strInizio);
	DDX_Text(pDX, IDC_EDIT_FINE, m_strFine);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CListiniView, CXFormView)
	//{{AFX_MSG_MAP(CListiniView)
	ON_COMMAND(ID_LISTINI_COPIA, OnListiniCopia)
	ON_COMMAND(ID_LISTINI_ATTIVA, OnListiniAttiva)
	ON_COMMAND(ID_CATEGORIA_NUOVA, OnCategoriaNuova)
	ON_COMMAND(ID_CATEGORIA_MODIFICA, OnCategoriaModifica)
	ON_COMMAND(ID_CATEGORIA_ELIMINA, OnCategoriaElimina)
	ON_COMMAND(ID_SERVIZI_NUOVO, OnServiziNuovo)
	ON_COMMAND(ID_SERVIZI_MODIFICA, OnServiziModifica)
	ON_COMMAND(ID_SERVIZI_ELIMINA, OnServiziElimina)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST_CATEGORIE, OnItemactivateListCategorie)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST_SERVIZI, OnItemactivateListServizi)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CATEGORIE, OnDblclkListCategorie)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SERVIZI, OnDblclkListServizi)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SERVIZI, OnItemchangedListServizi)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CATEGORIE, OnItemchangedListCategorie)
	ON_COMMAND(ID_LISTINI_DISATTIVA, OnListiniDisattiva)
	ON_COMMAND(ID_LISTINI_STAMPA, OnListiniStampa)
	ON_BN_CLICKED(IDC_BUTTON_CERCA, OnButtonCerca)
	ON_COMMAND(ID_SERVIZI_NUOVONOTA, OnServiziNuovonota)
	ON_COMMAND(ID_LISTINI_STAMPA_INCONCESSIONE, OnListiniStampaInConcessione)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CListiniView::LoadCurRecord(BOOL bData)
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CAziendeSet setAziende(&pApp->m_db);

  if(bData)
	{
		m_strCodice.Format("LIST%d", m_pSet->m_Codice);
		m_strNome     = m_pSet->m_Nome;
		if(!m_pSet->IsFieldNull(&m_pSet->m_Azienda)
		   && m_pSet->m_Azienda > 0)
		{
		  setAziende.m_strFilter.Format("Codice = %d", m_pSet->m_Azienda);
		  setAziende.Open();
			if(setAziende.IsEOF())
      {
				m_strCodiceAzienda.Empty();
				m_strNomeAzienda = "Listino generale";
			  m_nCodiceAzienda = 0;
			}
			else
			{
				m_strCodiceAzienda = setAziende.m_ID;
				m_strNomeAzienda   = setAziende.m_RagioneSociale;
				m_nCodiceAzienda   = m_pSet->m_Azienda;
			}
    }
		else
		{
			m_strCodiceAzienda.Empty();
		  m_strNomeAzienda = "Listino generale";
			m_nCodiceAzienda = 0;
		}
		m_strAutore   = m_pSet->m_Autore;
		if(!m_pSet->IsFieldNull(&m_pSet->m_Inizio))
      m_strInizio = m_pSet->m_Inizio.Format("%d/%m/%Y");
		else
      m_strInizio.Empty();
    if(!m_pSet->IsFieldNull(&m_pSet->m_Fine))
		  m_strFine = m_pSet->m_Fine.Format("%d/%m/%Y");
		else
		  m_strFine.Empty();
		m_bCertificatiOgniSerie = m_pSet->m_CertOgniSerie;
		/*-- carico la lista delle categorie e svuoto quella dei servizi ---*/
		LoadCategorie();
	}
	else
	{
		m_strCodice.Empty();
		m_strNome.Empty();
		m_strCodiceAzienda.Empty();
		m_strNomeAzienda.Empty();
		m_strAutore.Empty();
		m_strInizio.Empty();
		m_strFine.Empty();
		m_ListCategorie.DeleteAllItems();
		m_ListServizi.DeleteAllItems();
    m_bCertificatiOgniSerie = FALSE;
		m_nCodiceAzienda = 0;
  }
}

BOOL CListiniView::IsDataChanged()
{
  if(m_strNome != m_pSet->m_Nome
	   || m_nCodiceAzienda != m_pSet->m_Azienda
		 || m_bCertificatiOgniSerie != m_pSet->m_CertOgniSerie
     || m_strInizio != m_pSet->m_Inizio.Format("%d/%m/%Y")
     || m_strFine != m_pSet->m_Fine.Format("%d/%m/%Y"))
		return TRUE;
  return FALSE;
}

BOOL CListiniView::ValidateData()
{
  if(m_strNome.GetLength() < 2)
	{
	  AfxMessageBox("La lunghezza del nome deve essere di almeno due lettere");
	  return FALSE;
	}
  CTime inizio, fine;
  inizio = GetData(m_strInizio);
  fine = GetData(m_strFine);
  if(inizio > fine)
  {
    AfxMessageBox("Verificare la coerenza delle date impostate per il periodo di validità del listino.");
    return FALSE;
  }
	return TRUE;
}

BOOL CListiniView::NewRecord()
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

	if(!ValidateData())
	  return FALSE;
	m_pSet->AddNew();
	m_pSet->m_Nome    = m_strNome;
	m_pSet->m_Azienda = m_nCodiceAzienda;
	m_pSet->m_Autore  = pApp->GetUserName();
	m_pSet->m_CertOgniSerie = m_bCertificatiOgniSerie;
  if(!m_strInizio.IsEmpty())
    m_pSet->m_Inizio = GetData(m_strInizio);
  if(!m_strFine.IsEmpty())
    m_pSet->m_Fine = GetData(m_strFine);
	m_pSet->Update();
	pApp->ReloadTree(TREELABEL_INELABORAZIONE, -1);
	return TRUE;
}

BOOL CListiniView::SaveRecord()
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

	if(!ValidateData())
	  return FALSE;
  switch(AfxMessageBox("Salvare le modifiche ai dati?", MB_YESNOCANCEL))
	{
	  case IDYES:
  	  m_pSet->Edit();
    	m_pSet->m_Nome    = m_strNome;
	    m_pSet->m_Azienda = m_nCodiceAzienda;
    	m_pSet->m_CertOgniSerie = m_bCertificatiOgniSerie;
      if(!m_strInizio.IsEmpty())
        m_pSet->m_Inizio = GetData(m_strInizio);
      if(!m_strFine.IsEmpty())
        m_pSet->m_Fine = GetData(m_strFine);
	    m_pSet->Update();
	    pApp->ReloadTree(TREELABEL_INELABORAZIONE, -1);
		  break;
		case IDNO:
		  break;
		default:
		  return FALSE;
	}
	return TRUE;
}

BOOL CListiniView::DeleteRecord()
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
	CString str;

  /*--- non si possono eliminare listini in vigore nè scaduti ---*/
	if(!pDoc->m_pListiniInVigoreSet->IsBOF() || !pDoc->m_pListiniScadutiSet->IsBOF())
	{
	  MessageBeep(-1);
    AfxMessageBox("Non si possono eliminare listini in vigore o scaduti.");
		return FALSE;
	}
  if(!m_pSet->IsBOF())
	{
		str.Format("Eliminare il listino %s (Codice %s)?",
							 m_strNome, m_strCodice);
		if(AfxMessageBox(str, MB_YESNO) == IDYES)
		{
			try
			{
				/*----- avvio la transazione -----*/
				pApp->BeginTrans();
				/*---- elimino il listino ----*/
				m_pSet->Delete();
        /*---- elimino le categorie con i relativi servizi -----*/
        for(m_pCategorieSet->IsBOF() ? 
				      m_pCategorieSet->IsEOF() ? 0 : m_pCategorieSet->MoveNext() :
							m_pCategorieSet->MoveFirst();
				    !m_pCategorieSet->IsEOF();
						m_pCategorieSet->MoveNext())
				{
				  m_pServiziSet->m_strFilter.Format("Categoria = %d", m_pCategorieSet->m_Codice);
					for(m_pServiziSet->Requery(); !m_pServiziSet->IsEOF(); m_pServiziSet->MoveNext())
					  m_pServiziSet->Delete();
				}
				pApp->ReloadTree(TREELABEL_INELABORAZIONE, -1);
				/*---- committo la transazione ----*/
				pApp->CommitTrans();
				/*---- svuoto le liste ----*/
				m_ListCategorie.DeleteAllItems();
				m_ListServizi.DeleteAllItems();
		  }
			catch(CDBException* e)
			{
				/*----- transazione fallita ----*/
				pApp->Rollback();
				AfxMessageBox(e->m_strError);
			}
			/*---- deseleziono categorie e servizi -----*/
			m_ListCategorie.SetSelectionMark(-1);
			m_ListServizi.SetSelectionMark(-1);
			if(!m_pCategorieSet->IsBOF())
			{
				m_pCategorieSet->MoveFirst();
				m_pCategorieSet->MovePrev();
			}
			if(!m_pServiziSet->IsBOF())
			{
				m_pServiziSet->MoveFirst();
				m_pServiziSet->MovePrev();
			}
    	return TRUE;
		}
	}
	return FALSE;
}

void CListiniView::EnableControls(BOOL bEditMode)
{
	m_EditNome.EnableWindow(bEditMode);
	m_ButtonCerca.EnableWindow(bEditMode);
	m_CheckCertOgniSerie.EnableWindow(bEditMode);
  m_EditInizio.EnableWindow(bEditMode);
  m_EditFine.EnableWindow(bEditMode);
	m_EditNome.SetFocus();
}

CString CListiniView::GetToolTip(int nID)
{
  switch(nID)
	{
	  case ID_NUOVO:
    	return "Crea un nuovo listino\nNuovo listino";
		case ID_MODIFICA:
		  return "Consente la modifica dei dati del listino\nModifica listino";
		case ID_ELIMINA:
		  return "Elimina il listino dall'archivio\nElimina listino";
    default:
      return "";
	}
}


void CListiniView::LoadCategorie()
{
	int n;

	/*-- carico la lista delle categorie ---*/
	m_bDenySinc = TRUE;
	m_ListCategorie.DeleteAllItems();
	m_pCategorieSet->m_strFilter.Format("Listino = %d", m_pSet->m_Codice);
	for(m_nCategorie = 0, m_pCategorieSet->Requery();
		  !m_pCategorieSet->IsEOF();
			m_nCategorie++, m_pCategorieSet->MoveNext())
	{
		n = m_ListCategorie.InsertItem(m_nCategorie, m_pCategorieSet->m_ID);
    m_ListCategorie.SetItemData(n, m_pCategorieSet->m_Codice);
		m_ListCategorie.SetItemText(n, 1, m_pCategorieSet->m_Nome);
		m_ListCategorie.SetItemText(n, 2, m_pCategorieSet->m_Descrizione);
	}
	/*---- non e' selezionata alcuna categoria -----*/
	if(!m_pCategorieSet->IsBOF())
	{
    m_pCategorieSet->MoveFirst();
	  m_pCategorieSet->MovePrev();
  }
	/*--- elimino gli elementi dalla lista dei servizi ----*/
	m_nServizi = 0;
	m_ListServizi.DeleteAllItems();
	/*--- non e' selezionato alcun servizio ---*/
	if(!m_pServiziSet->IsBOF())
	{
		m_pServiziSet->MoveFirst();
		m_pServiziSet->MovePrev();
  }
	m_bDenySinc = FALSE;
}

void CListiniView::SincronizeCategorie()
{
	int n;
  CString str;
	POSITION pos;

  /*----- se non è selezionata alcuna categoria esco ---*/
  pos = m_ListCategorie.GetFirstSelectedItemPosition();
	if((n = m_ListCategorie.GetNextSelectedItem(pos)) < 0)
	  return;
  /*----- se si tratta della categoria già selezionata esco ---*/
	if(!m_pCategorieSet->IsBOF()
       && (DWORD)m_pCategorieSet->m_Codice == m_ListCategorie.GetItemData(n))
	  return;
	/*---- cerco la categoria nel recorset -----*/
	for(m_pCategorieSet->MoveFirst();
		  !m_pCategorieSet->IsEOF();
			m_pCategorieSet->MoveNext())
	{
		if((long)m_ListCategorie.GetItemData(n) == m_pCategorieSet->m_Codice)
			break;
	}
  /*--- preparo il recodset dei servizi -----*/
	if(!m_pCategorieSet->IsEOF())
	  m_pServiziSet->m_strFilter.Format("Categoria = %d", m_pCategorieSet->m_Codice);
	else 
	  m_pServiziSet->m_strFilter.Format("Categoria = 0");
  /*--- elimino gli elementi dalla lista dei servizi ----*/
	m_ListServizi.DeleteAllItems();
 	m_bDenySinc = TRUE;
 /*---- inserisco i servizi nella lista -----*/
	for(m_nServizi = 0, m_pServiziSet->Requery();
		  !m_pServiziSet->IsEOF();
			m_nServizi++, m_pServiziSet->MoveNext())
	{
		n = m_ListServizi.InsertItem(m_nServizi, m_pServiziSet->m_ID);
    m_ListServizi.SetItemData(n, m_pServiziSet->m_Codice);
		/*--- ----*/
		str = m_pServiziSet->m_Descrizione;
		str.Replace("\r\n", " ");
		m_ListServizi.SetItemText(n, 1, str);
		/*--- ----*/
		if(!m_pServiziSet->IsFieldNull(&m_pServiziSet->m_Prezzo))
    {
			str = Valuta(m_pServiziSet->m_Prezzo).Format();
			m_ListServizi.SetItemText(n, 2, str);
    }
	}
	m_bDenySinc = FALSE;
	/*--- non e' selezionato alcun servizio ---*/
	if(!m_pServiziSet->IsBOF())
	{
		m_pServiziSet->MoveFirst();
		m_pServiziSet->MovePrev();
  }
  UpdateData(FALSE);
}

void CListiniView::SincronizeServizi()
{
	int n;
	POSITION pos;
		
  /*----- se non è selezionata alcun servizio esco ---*/
  pos = m_ListServizi.GetFirstSelectedItemPosition();
	if((n = m_ListServizi.GetNextSelectedItem(pos)) < 0)
	  return;
  /*----- se si tratta del servizio già selezionato esco ---*/
	if(!m_pServiziSet->IsBOF()
       && (DWORD)m_pServiziSet->m_Codice == m_ListServizi.GetItemData(n))
	  return;
	/*---- cerco il servizio nel recorset -----*/
	for(m_pServiziSet->MoveFirst();
		  !m_pServiziSet->IsEOF();
			m_pServiziSet->MoveNext())
	{
		if((long)m_ListServizi.GetItemData(n) == m_pServiziSet->m_Codice)
			break;
	}
  
}

/////////////////////////////////////////////////////////////////////////////
// CListiniView diagnostics

#ifdef _DEBUG
void CListiniView::AssertValid() const
{
	CFormView::AssertValid();
}

void CListiniView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CListiniView message handlers

void CListiniView::OnInitialUpdate() 
{
	DWORD style;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();

	m_pSet = pDoc->m_pListiniInElaborazioneSet;
	CXFormView::m_pSet = m_pSet;

  // creo i recordset
	m_pCategorieSet = new CCategorieSet(&pApp->m_db);
  m_pCategorieSet->m_strSort = "ID";
	m_pCategorieSet->Open();

	m_pServiziSet = new CServiziListinoSet(&pApp->m_db);
  m_pServiziSet->m_strSort = "ID";
	m_pServiziSet->Open();

	CXFormView::OnInitialUpdate();

  // lista delle categorie	
	style = m_ListCategorie.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT;
	m_ListCategorie.SetExtendedStyle(style);
	m_ListCategorie.InsertColumn(0, "Codice", LVCFMT_LEFT, 50, -1);
	m_ListCategorie.InsertColumn(1, "Nome", LVCFMT_LEFT, 240, -1);
	m_ListCategorie.InsertColumn(2, "Descrizione", LVCFMT_LEFT, 240, -1);
	m_ListCategorie.InsertColumn(3, "Autore", LVCFMT_LEFT, 90, -1);

  // lista dei servizi
	style = m_ListServizi.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT;
	m_ListServizi.SetExtendedStyle(style);
	m_ListServizi.InsertColumn(0, "Codice", LVCFMT_LEFT, 50, -1);
	m_ListServizi.InsertColumn(1, "Nome", LVCFMT_LEFT, 480, -1);
	m_ListServizi.InsertColumn(2, "Prezzo €", LVCFMT_RIGHT, 90, -1);

	OnUpdate(NULL, 0, NULL);
}

void CListiniView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();

  switch(pDoc->m_nSelectedTreeListini)
  {
  case TREEITEM_INVIGORE:
	if(!pDoc->m_pListiniInVigoreSet->IsBOF())
	  CXFormView::m_pSet = m_pSet = pDoc->m_pListiniInVigoreSet;
    break;
  case TREEITEM_SCADUTI:
	if(!pDoc->m_pListiniScadutiSet->IsBOF())
	  CXFormView::m_pSet = m_pSet = pDoc->m_pListiniScadutiSet;
    break;
  case TREEITEM_INELABORAZIONE:
  default:
	if(!pDoc->m_pListiniInElaborazioneSet->IsBOF())
	  CXFormView::m_pSet = m_pSet = pDoc->m_pListiniInElaborazioneSet;
    break;
  }
	CXFormView::OnUpdate(pSender, lHint, pHint);
}

void CListiniView::OnListiniCopia() 
{
  int nCodListino, nCodCategoria, nCodAzienda;
	CString str;
	CWinSigmaApp*  pApp = (CWinSigmaApp*)AfxGetApp();
	CWinSigmaDoc*  pDoc = (CWinSigmaDoc*)GetDocument();
	CListiniSet*   pListSet;
	CCategorieSet* pCatSet;
	CServiziListinoSet*   pServSet;

  if(!m_pSet->IsBOF())
	{
		str.Format("Creare una copia del listino %s (Codice %s)?",
							 m_strNome, m_strCodice);
		if(AfxMessageBox(str, MB_YESNO) == IDYES)
		{
      /*--- creo e apro i recordset per la copia di categorie e servizi ---*/
			pCatSet  = new CCategorieSet(&pApp->m_db);
			pServSet = new CServiziListinoSet(&pApp->m_db);
     	pListSet = new CListiniSet(&pApp->m_db);
			pCatSet->Open();
			pServSet->Open();
			pListSet->Open();
			try
			{
				/*----- avvio la transazione -----*/
				pApp->LockTable("LISTINI WRITE, CATEGORIE WRITE, SERVIZI_LISTINO WRITE");
				pApp->BeginTrans();
				nCodAzienda = m_pSet->m_Azienda;
				/*---- creo il listino ----*/
				pListSet->AddNew();
				pListSet->m_Nome    = "Copia di " + m_strNome;
				pListSet->m_Azienda = nCodAzienda;
				pListSet->m_Autore  = pApp->GetUserName();
				pListSet->Update();
        /*---- cerco il codice del nuovo listino ----*/
				for(nCodListino = 0, pListSet->Requery(); !pListSet->IsEOF(); pListSet->MoveNext())
				  if(nCodListino < pListSet->m_Codice)
					  nCodListino = pListSet->m_Codice;
        /*---- copio le categorie con i relativi servizi -----*/
        for(SET_START(m_pCategorieSet);
				    !m_pCategorieSet->IsEOF();
						m_pCategorieSet->MoveNext())
				{
				  /*----- crea la categoria -----*/
					pCatSet->AddNew();
					pCatSet->m_Nome        = m_pCategorieSet->m_Nome;
					pCatSet->m_ID          = m_pCategorieSet->m_ID;
					pCatSet->m_Descrizione = m_pCategorieSet->m_Descrizione;
					pCatSet->m_Listino     = nCodListino;
          pCatSet->Update();
					/*----- cerco la categoria aggiunta -----*/
					for(nCodCategoria = 0, pCatSet->Requery(); !pCatSet->IsEOF(); pCatSet->MoveNext())
            if(nCodCategoria < pCatSet->m_Codice)
						  nCodCategoria = pCatSet->m_Codice;
				  /*----- seleziono i servizi dal listino sorgente ----*/
				  m_pServiziSet->m_strFilter.Format("Categoria = %d", m_pCategorieSet->m_Codice);
					for(m_pServiziSet->Requery(); !m_pServiziSet->IsEOF(); m_pServiziSet->MoveNext())
					{
					  pServSet->AddNew();
						pServSet->m_Categoria					= nCodCategoria;
						pServSet->m_Descrizione				= m_pServiziSet->m_Descrizione;
						pServSet->m_ID								= m_pServiziSet->m_ID;
						pServSet->m_Prezzo						= m_pServiziSet->m_Prezzo;
						pServSet->m_Sconto						= m_pServiziSet->m_Sconto;
						pServSet->m_Certificato				= m_pServiziSet->m_Certificato;
						pServSet->m_Campioni					= m_pServiziSet->m_Campioni;
            pServSet->m_PerSerie					= m_pServiziSet->m_PerSerie;
            pServSet->m_Prove							= m_pServiziSet->m_Prove;
						pServSet->m_Concessione				= m_pServiziSet->m_Concessione;
						pServSet->m_Commento	        = m_pServiziSet->m_Commento;
            pServSet->m_Norma             = m_pServiziSet->m_Norma;
            pServSet->m_Aggiuntivo        = m_pServiziSet->m_Aggiuntivo;
            pServSet->m_Emissione         = m_pServiziSet->m_Emissione;
            pServSet->m_Nome              = m_pServiziSet->m_Nome;
            pServSet->m_Riferimenti       = m_pServiziSet->m_Riferimenti;
            pServSet->m_ProviniPerSerie   = m_pServiziSet->m_ProviniPerSerie;
            pServSet->m_Certificato2      = m_pServiziSet->m_Certificato2;
            pServSet->m_Certificato3      = m_pServiziSet->m_Certificato3;
            pServSet->m_Certificato4      = m_pServiziSet->m_Certificato4;
            pServSet->m_Certificato5      = m_pServiziSet->m_Certificato5;
						pServSet->Update();
					}
				}
				pApp->ReloadTree(TREELABEL_INELABORAZIONE, -1);
				/*---- committo la transazione ----*/
				pApp->CommitTrans();
 				pApp->UnlockTables();
				/*-- carico la lista delle categorie e svuoto quella dei servizi ---*/
				LoadCategorie();
		  }
			catch(CDBException* e)
			{
				/*----- transazione fallita ----*/
				pApp->Rollback();
  			pApp->UnlockTables();
				AfxMessageBox(e->m_strError);
			}
			/*---- deseleziono categorie e servizi -----*/
			m_ListCategorie.SetSelectionMark(-1);
			m_ListServizi.SetSelectionMark(-1);
			if(!m_pCategorieSet->IsBOF())
			{
				m_pCategorieSet->MoveFirst();
				m_pCategorieSet->MovePrev();
			}
			if(!m_pServiziSet->IsBOF())
			{
				m_pServiziSet->MoveFirst();
				m_pServiziSet->MovePrev();
			}
			pListSet->Close();
			pCatSet->Close();
			pServSet->Close();
			delete pListSet;
			delete pCatSet;
			delete pServSet;
      pApp->ReloadTree(TREELABEL_INELABORAZIONE, -1);
		}
	}
}

void CListiniView::OnListiniAttiva() 
{
  CString str;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
	CListiniSet*  pSet;

	if(pDoc->m_pListiniInElaborazioneSet->IsBOF() && pDoc->m_pListiniScadutiSet->IsBOF())
	{
	  MessageBeep(-1);
		return;
	}
  /*----- cerco un eventuale listino attivo corrispondente -----*/
 	pSet = pDoc->m_pListiniInVigoreSet;
 	for(; !pSet->IsEOF(); pSet->MoveNext())
	{
	  if(!pSet->IsBOF() && pSet->m_Azienda == m_pSet->m_Azienda)
		  break;
	}
	/*--- verifico se c'e' un listino da disattivare ----*/
	if(!pSet->IsEOF())
		str.Format("Sostituire il listino %s (Codice LIST%d) con il listino %s (Codice LIST%d)?",
	              pSet->m_Nome, pSet->m_Codice, m_pSet->m_Nome, m_pSet->m_Codice);	  
  else
		str.Format("Attivare il listino %s (Codice LIST%d)?",
	             m_pSet->m_Nome, m_pSet->m_Codice);

	/*--- attivo il listino ---*/
  if(AfxMessageBox(str, MB_YESNO) == IDYES)
  {
 	  m_pSet->Edit();
 	  m_pSet->m_Inizio = CTime::GetCurrentTime();
		m_pSet->SetFieldNull(&(m_pSet->m_Fine));
    m_pSet->Update();
		if(!pSet->IsEOF())
		{
		  pSet->Edit();
			pSet->m_Fine = CTime::GetCurrentTime();
			pSet->Update();
		}
    pApp->ReloadTree(TREELABEL_SCADUTI, -1);
    pApp->ReloadTree(TREELABEL_INVIGORE, -1);
    pApp->ReloadTree(TREELABEL_INELABORAZIONE, -1);
	}
}

void CListiniView::OnListiniDisattiva() 
{
	CString str;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();

	if(pDoc->m_pListiniInVigoreSet->IsBOF())
	{
	  MessageBeep(-1);
		return;
	}
	/*--- attivo il listino ---*/
	str.Format("Disattivare il listino %s (Codice LIST%d)?",
	             m_pSet->m_Nome, m_pSet->m_Codice);
  if(AfxMessageBox(str, MB_YESNO) == IDYES)
  {
 	  m_pSet->Edit();
 	  m_pSet->m_Fine = CTime::GetCurrentTime();
    m_pSet->Update();
    pApp->ReloadTree(TREELABEL_INVIGORE, -1);
    pApp->ReloadTree(TREELABEL_SCADUTI, -1);
	}
	
}

void CListiniView::OnListiniStampa() 
{
  StampaListino(FALSE);
}

void CListiniView::OnListiniStampaInConcessione() 
{
  if(m_pSet->IsBOF() || m_pSet->IsEOF())
  {
    AfxMessageBox("Selezionare un listino.");
    return;
  }
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CString str, strFilter;
  // Filtro le categorie
  CCategorieServiziSet* pCatServ = new CCategorieServiziSet(&pApp->m_db);
  pCatServ->m_strFilter.Format("Listino = %ld and CATEGORIE.Codice = SERVIZI_LISTINO.Categoria and SERVIZI_LISTINO.Concessione = 1 GROUP BY CATEGORIE.Codice", m_pSet->m_Codice);
  pCatServ->Open();
  for(SET_START(pCatServ); !pCatServ->IsEOF(); pCatServ->MoveNext())
  {
    str.Format("Codice = %ld", pCatServ->m_Categoria);
    strFilter += str + " OR ";
  }
  strFilter.TrimRight(" OR ");
  pCatServ->Close();
  m_pCategorieSet->m_strFilter.Format("Listino = %ld AND (%s)", m_pSet->m_Codice, strFilter);
  m_pCategorieSet->Requery();
  StampaListino(TRUE);
}

void CListiniView::StampaListino(BOOL bInConcessione)
{
	CString str;
	CStringArray fieldNames, fieldValues;
  CPrintInterpreter prn;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

  if(!prn.PrePrinting())
		return;
  /*---- simulazione ----*/
  prn.SetPage(1);
	prn.StartSimulation();
  SET_START(m_pCategorieSet);
	m_aryPagine.RemoveAll();
#ifdef WINSIGMA2	
	prn.Print(pApp->GetCurrentDirectory() + "\\ListinoIndexSigma2.prn", &fieldNames, &fieldValues, NULL, NULL, &ScanCategorie);
#else
	prn.Print(pApp->GetCurrentDirectory() + "\\ListinoIndex.prn", &fieldNames, &fieldValues, NULL, NULL, &ScanCategorie);
#endif
	for(SET_START(m_pCategorieSet);
	    !m_pCategorieSet->IsEOF();
			m_pCategorieSet->MoveNext())
	{
    m_aryPagine.Add(prn.GetPage());
    if(bInConcessione)
      m_pServiziSet->m_strFilter.Format("Concessione = 1 AND Categoria = %d", m_pCategorieSet->m_Codice);
    else
		  m_pServiziSet->m_strFilter.Format("Categoria = %d", m_pCategorieSet->m_Codice);
		m_pServiziSet->Requery();
		SET_START(m_pServiziSet);
#ifdef WINSIGMA2	
		prn.Print(pApp->GetCurrentDirectory() + "\\ListinoSigma2.prn", &fieldNames, &fieldValues, NULL, NULL, &ScanServizi);
#else
		prn.Print(pApp->GetCurrentDirectory() + "\\Listino.prn", &fieldNames, &fieldValues, NULL, NULL, &ScanServizi);
#endif
	}
  prn.EndSimulation();
	/*---- copertina ----*/
	fieldNames.Add("validità");
	if(m_pSet->m_Inizio != 0)
	{
		str.Format("IN VIGORE DAL %d %s %d",
							 m_pSet->m_Inizio.GetDay(), 
							 STR_MESI[m_pSet->m_Inizio.GetMonth() - 1],
							 m_pSet->m_Inizio.GetYear());
	}
	else str = "Listino in elaborazione";
 	str.MakeUpper();
  fieldValues.Add(str);
#ifdef WINSIGMA2
	prn.Print(pApp->GetCurrentDirectory() + "\\ListinoCoverSigma2.prn", &fieldNames, &fieldValues, NULL, NULL, NULL);
#else
	prn.Print(pApp->GetCurrentDirectory() + "\\ListinoCover.prn", &fieldNames, &fieldValues, NULL, NULL, NULL);
#endif
	fieldNames.RemoveAll();
	fieldValues.RemoveAll();
	/*---- indice delle categorie -----*/
  SET_START(m_pCategorieSet);
  prn.SetPage(1);
#ifdef WINSIGMA2
	prn.Print(pApp->GetCurrentDirectory() + "\\ListinoIndexSigma2.prn", &fieldNames, &fieldValues, NULL, NULL, &ScanCategorie);
#else
	prn.Print(pApp->GetCurrentDirectory() + "\\ListinoIndex.prn", &fieldNames, &fieldValues, NULL, NULL, &ScanCategorie);
#endif
	fieldNames.RemoveAll();
	fieldValues.RemoveAll();
  /*---- stampa dei servizi ----*/
  fieldNames.Add("data");
	fieldNames.Add("idCategoria");
	fieldNames.Add("nomeCategoria");
  fieldNames.Add("descrizione");
	for(SET_START(m_pCategorieSet);
	    !m_pCategorieSet->IsEOF();
			m_pCategorieSet->MoveNext())
	{
    if(bInConcessione)
      m_pServiziSet->m_strFilter.Format("Concessione = 1 AND Categoria = %d", m_pCategorieSet->m_Codice);
    else
		  m_pServiziSet->m_strFilter.Format("Categoria = %d", m_pCategorieSet->m_Codice);
		m_pServiziSet->Requery();
		SET_START(m_pServiziSet);
    fieldValues.RemoveAll();
    fieldValues.Add(m_pSet->m_Inizio.Format("%d/%m/%Y"));
		fieldValues.Add(m_pCategorieSet->m_ID);
		fieldValues.Add(m_pCategorieSet->m_Nome);
    fieldValues.Add(m_pCategorieSet->m_Descrizione);
#ifdef WINSIGMA2
		prn.Print(pApp->GetCurrentDirectory() + "\\ListinoSigma2.prn", &fieldNames, &fieldValues, NULL, NULL, &ScanServizi);
#else
		prn.Print(pApp->GetCurrentDirectory() + "\\Listino.prn", &fieldNames, &fieldValues, NULL, NULL, &ScanServizi);
#endif
	}

	prn.PostPrinting();
  m_pCategorieSet->m_strFilter.Format("Listino = %ld", m_pSet->m_Codice);
  m_pCategorieSet->Requery();
  LoadCategorie();
}



BOOL CListiniView::ScanCategorie(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
  if(CListiniView::m_pCategorieSet->IsEOF())
	  return FALSE;
  pFieldNames->RemoveAll();
	pFieldNames->Add("idCategoria");
	pFieldNames->Add("nomeCategoria");
	pFieldNames->Add("paginaCategoria");
  pFieldValues->RemoveAll();
	pFieldValues->Add(m_pCategorieSet->m_ID);
	pFieldValues->Add(m_pCategorieSet->m_Nome);
	if(m_aryPagine.GetSize())
	{
	  CString str;

		str.Format("%d", m_aryPagine[0]);
		pFieldValues->Add(str);
    m_aryPagine.RemoveAt(0);
	}
	m_pCategorieSet->MoveNext();
  if(CListiniView::m_pCategorieSet->IsEOF())
	  return FALSE;
  return TRUE;
}


BOOL CListiniView::ScanServizi(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
  CString str;

  if(CListiniView::m_pServiziSet->IsEOF())
	  return FALSE;
  pFieldNames->RemoveAll();
	pFieldNames->Add("idServizio");
	pFieldNames->Add("concessione");
	pFieldNames->Add("nomeServizio");
	pFieldNames->Add("prezzoServizio");
  pFieldNames->Add("proviniPerSerie");
  pFieldValues->RemoveAll();
	
		// ID del servizio
	pFieldValues->Add(m_pServiziSet->m_ID);

	str="";
	// Campo relativo alla concessione
	if(m_pServiziSet->m_Concessione == SERVIZIO_CONCESSIONE)
		str = "C";
  else if(m_pServiziSet->m_Concessione == SERVIZIO_GEOLOGIA)
    str = "G";
	pFieldValues->Add(str);

	// Costruzione della stringa completa della descrizione

	CString norma="", note="", composta="";
	if(!m_pServiziSet->IsFieldNull(&m_pServiziSet->m_Norma)
			&& !m_pServiziSet->m_Norma.IsEmpty())
		{
			norma.Format("\r\n%s", m_pServiziSet->m_Norma);
		if(m_pServiziSet->m_PerSerie == PER_SERIE)
			norma = ", per serie" + norma;
		if(m_pServiziSet->m_PerSerie == PER_PROVINO)
				norma = ", cad." + norma;
		}
	else
		{
		if(m_pServiziSet->m_PerSerie == PER_SERIE)
			norma = ", per serie" + norma;				
		if(m_pServiziSet->m_PerSerie == PER_PROVINO)
			norma = ", cad." + norma;				
		}				

	if(!m_pServiziSet->IsFieldNull(&m_pServiziSet->m_Riferimenti)
		&& !m_pServiziSet->m_Riferimenti.IsEmpty())
			note.Format(" %s ", m_pServiziSet->m_Riferimenti);

	composta.Format("%s%s%s",m_pServiziSet->m_Descrizione, note, norma );
	pFieldValues->Add(composta);

	/*str = m_pServiziSet->m_Descrizione;
	if(!m_pServiziSet->m_Norma.IsEmpty())
	{
	  str += "\r\n";
		str += m_pServiziSet->m_Norma;
	}*/
	
	if(!m_pServiziSet->IsFieldNull(&m_pServiziSet->m_Prezzo) && m_pServiziSet->m_Prezzo > 0.0001 )
	{
		Valuta v(m_pServiziSet->m_Prezzo);
		pFieldValues->Add(v.Format(6));
  }
	else
		pFieldValues->Add("");
  // Provini per serie
  if(!m_pServiziSet->IsFieldNull(&m_pServiziSet->m_ProviniPerSerie) && m_pServiziSet->m_ProviniPerSerie != 0)
    str.Format("%d", m_pServiziSet->m_ProviniPerSerie);
  else
    str.Empty();
  pFieldValues->Add(str);
	m_pServiziSet->MoveNext();
  if(CListiniView::m_pServiziSet->IsEOF())
	  return FALSE;
  return TRUE;
}

void CListiniView::OnCategoriaNuova() 
{
	int n;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  CCategorieDlg dlg;

  if(m_pSet->IsBOF())
	{
	  MessageBeep(-1);
		return;
	}
	dlg.m_strCodiceListino.Format("LIST%d", m_pSet->m_Codice);
	dlg.m_strNomeListino = m_pSet->m_Nome;

	if(dlg.DoModal() == IDOK)
	{
	  try
		{
			m_pCategorieSet->AddNew();
			m_pCategorieSet->m_ID          = dlg.m_strCodice;
			m_pCategorieSet->m_Nome        = dlg.m_strNome;
			m_pCategorieSet->m_Descrizione = dlg.m_strDescrizione;
			m_pCategorieSet->m_Listino     = m_pSet->m_Codice;
			m_pCategorieSet->Update();
		}
		catch(CDBException* e)
		{
		  CString strError;

      if(pApp->DecodeDBError(e->m_strStateNativeOrigin) == ER_DUP_ENTRY)
			  strError.Format("Nel listino è già presente una categoria con codice %s:"
			                  " impossibile aggiungere la categoria",
			                  dlg.m_strCodice);
      else
			  strError = e->m_strError;
			AfxMessageBox(strError);
			return;
		}
    /*--- aggiorno il recordset e cerco la posizione nella lista -----*/
		for(n = 0, m_pCategorieSet->Requery();
		    !m_pCategorieSet->IsEOF();
				n++, m_pCategorieSet->MoveNext())
		{
		  if(m_ListCategorie.GetItemText(n, 0) != m_pCategorieSet->m_ID)
			  break;
		}
		/*--- inserisco la categoria nella lista -----*/
		m_bDenySinc = TRUE;
		n = m_ListCategorie.InsertItem(n, m_pCategorieSet->m_ID);
    m_ListCategorie.SetItemData(n, m_pCategorieSet->m_Codice);
		m_ListCategorie.SetItemText(n, 1, m_pCategorieSet->m_Nome);
		m_ListCategorie.SetItemText(n, 2, m_pCategorieSet->m_Descrizione);
	  m_bDenySinc = FALSE;
	}
}

void CListiniView::OnCategoriaModifica() 
{
	int n;
	POSITION pos;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
  CCategorieDlg dlg;

  if(m_pSet->IsBOF() || m_pCategorieSet->IsBOF())
	{
	  MessageBeep(-1);
		return;
	}
	dlg.m_strCodice      = m_pCategorieSet->m_ID; 
	dlg.m_strNome        = m_pCategorieSet->m_Nome; 
	dlg.m_strDescrizione = m_pCategorieSet->m_Descrizione;
	dlg.m_strCodiceListino.Format("LIST%d", m_pSet->m_Codice);
	dlg.m_strNomeListino = m_pSet->m_Nome;
	/*--- preparo la lista con gli ID di categoria ---*/
	if(dlg.DoModal() == IDOK)
	{
    /*---- inizio la transazione ----*/
	  try
		{
      pApp->BeginTrans();
			if(dlg.m_strCodice != m_pCategorieSet->m_ID)
			{
			  /*--- aggiorno i relativi servizi ----*/
				for(m_pServiziSet->IsBOF() ? 0: m_pServiziSet->MoveFirst();
						!m_pServiziSet->IsEOF(); m_pServiziSet->MoveNext())
				{
					m_pServiziSet->Edit();
					m_pServiziSet->m_ID.Replace(m_pCategorieSet->m_ID, dlg.m_strCodice);
					m_pServiziSet->Update();
				}
			}
		  /*--- aggiorno la categoria ---*/
			m_pCategorieSet->Edit();
			m_pCategorieSet->m_ID          = dlg.m_strCodice;
			m_pCategorieSet->m_Nome        = dlg.m_strNome;
			m_pCategorieSet->m_Descrizione = dlg.m_strDescrizione;
			m_pCategorieSet->Update();
			/*---- committo la transazione ----*/
			pApp->CommitTrans();
		}
		catch(CDBException* e)
		{
		  CString strError;
			pApp->Rollback();

      if(pApp->DecodeDBError(e->m_strStateNativeOrigin) == ER_DUP_ENTRY)
			  strError.Format("Nel listino è già presente una categoria con codice %s:"
			                  " impossibile aggiungere la categoria",
			                  dlg.m_strCodice);
      else
			  strError = e->m_strError;
			AfxMessageBox(strError);
			return;
		}
		/*--- aggiorno la categoria nella lista -----*/
		pos = m_ListCategorie.GetFirstSelectedItemPosition();
		n = m_ListCategorie.GetNextSelectedItem(pos);
		m_ListCategorie.SetItemText(n, 0, m_pCategorieSet->m_ID);
		m_ListCategorie.SetItemText(n, 1, m_pCategorieSet->m_Nome);
		m_ListCategorie.SetItemText(n, 2, m_pCategorieSet->m_Descrizione);
		/*--- elimino gli elementi dalla lista dei servizi ----*/
		m_ListServizi.DeleteAllItems();
	  m_bDenySinc = TRUE;
		/*---- inserisco i servizi nella lista -----*/
		for(m_nServizi = 0, m_pServiziSet->Requery();
				!m_pServiziSet->IsEOF();
				m_nServizi++, m_pServiziSet->MoveNext())
		{
			n = m_ListServizi.InsertItem(m_nServizi, m_pServiziSet->m_ID);
			m_ListServizi.SetItemData(n, m_pServiziSet->m_Codice);
			m_ListServizi.SetItemText(n, 1, m_pServiziSet->m_Descrizione);
		}
		m_bDenySinc = FALSE;
		/*--- non e' selezionato alcun servizio ---*/
		if(!m_pServiziSet->IsBOF())
		{
			m_pServiziSet->MoveFirst();
			m_pServiziSet->MovePrev();
		}
		UpdateData(FALSE);
	}
}

void CListiniView::OnCategoriaElimina() 
{
  int n, nCodice;
	CString strDescr, str;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

  if(m_pSet->IsBOF() || m_pCategorieSet->IsBOF())
	{
	  MessageBeep(-1);
		return;
	}
	/*---- chiedo conferma ----*/
	if(m_pCategorieSet->m_Nome.GetLength() < 12)
	  strDescr = m_pCategorieSet->m_Nome;
	else
	  strDescr = m_pCategorieSet->m_Nome.Left(10) + " ...";
  str.Format("Eliminare la categoria %s (codice %s) e i relativi servizi?",
	            strDescr, m_pCategorieSet->m_ID);
  if(AfxMessageBox(str, MB_YESNO) == IDNO)
	  return;
  /*---- inizio la transazione ----*/
	try
	{
		nCodice = m_pCategorieSet->m_Codice;
    pApp->BeginTrans();
		/*---- elimino i servizi -----*/
		for(m_pServiziSet->IsBOF() ? 0 : m_pServiziSet->MoveFirst();
				!m_pServiziSet->IsEOF();
				m_pServiziSet->MoveNext())
		{
			if(!m_pServiziSet->IsBOF())
			  m_pServiziSet->Delete();
		}
		/*---- elimino la categoria -----*/
		m_pCategorieSet->Delete();
		/*---- committo la transazione ----*/
		pApp->CommitTrans();
		/*---- svuoto la lista dei servizi ----*/
		m_ListServizi.DeleteAllItems();
		/*---- elimino la categoria dalla lista ----*/
		for(n = 0; n < m_ListCategorie.GetItemCount(); n++)
			if((long)m_ListCategorie.GetItemData(n) == nCodice)
			{
				m_ListCategorie.DeleteItem(n);
				break;
			}
  }
	catch(CDBException* e)
	{
		/*----- transazione fallita ----*/
		pApp->Rollback();

		AfxMessageBox(e->m_strError);
	}
	/*---- deseleziono categorie e servizi -----*/
	m_ListCategorie.SetSelectionMark(-1);
	m_ListServizi.SetSelectionMark(-1);
	if(!m_pCategorieSet->IsBOF())
	{
	  m_pCategorieSet->MoveFirst();
    m_pCategorieSet->MovePrev();
	}
	if(!m_pServiziSet->IsBOF())
	{
	  m_pServiziSet->MoveFirst();
    m_pServiziSet->MovePrev();
	}
}	

void CListiniView::OnServiziNuovo() 
{
  int n;
	CString str;
	CServiziListinoDlg dlg;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

  if(m_pSet->IsBOF() || m_pCategorieSet->IsBOF())
	{
	  MessageBeep(-1);
		return;
	}
	/*----- cerco gli ID disponibili per i servizi ----*/
	for(n = 1, SET_START(m_pServiziSet);
	    n < 100 && !m_pServiziSet->IsEOF(); 
			n++)
	{
    str.Format("%s%02d", m_pCategorieSet->m_ID, n);
		if(str != m_pServiziSet->m_ID)
		  dlg.m_aryStrId.Add(str);
		else
		  m_pServiziSet->MoveNext();
  }
  /*---- aggiungo un nuovo codice per i servizi ----*/
	if(n < 100)
	{
  	str.Format("%s%02d", m_pCategorieSet->m_ID, n);
	  dlg.m_aryStrId.Add(str);
	}
	/*--- apro il dialogo ----*/
	dlg.m_strCategoria = m_pCategorieSet->m_ID;
	while(dlg.DoModal() == IDOK)
	{
  	try
		{
			m_pServiziSet->AddNew();
			m_pServiziSet->m_Categoria					= m_pCategorieSet->m_Codice;
			m_pServiziSet->m_ID									= dlg.m_strID;
			m_pServiziSet->m_Descrizione				= dlg.m_strDescrizione;
			m_pServiziSet->m_Nome								= dlg.m_strNome;
			m_pServiziSet->m_Norma							= dlg.m_strNorma;
			m_pServiziSet->m_Riferimenti				= dlg.m_strRiferimenti;
			m_pServiziSet->m_Campioni						= dlg.m_nProvini;
			if(dlg.m_fPrezzo == DBL_MAX)
				m_pServiziSet->SetFieldNull(&m_pServiziSet->m_Prezzo);
			else
				m_pServiziSet->m_Prezzo						= dlg.m_fPrezzo;
			m_pServiziSet->m_PerSerie						= dlg.m_nPerSerie;
			m_pServiziSet->m_Emissione					= dlg.m_nEmissione;
			m_pServiziSet->m_Certificato				= dlg.m_nCertificato;
      m_pServiziSet->m_Certificato2       = dlg.m_nCertificato2;
			m_pServiziSet->m_Certificato3       = dlg.m_nCertificato3;
			m_pServiziSet->m_Certificato4       = dlg.m_nCertificato4;
			m_pServiziSet->m_Certificato5       = dlg.m_nCertificato5;
			m_pServiziSet->m_Prove							= dlg.m_byProve;
      m_pServiziSet->m_Prove2             = dlg.m_byProve2;
      m_pServiziSet->m_Prove3             = dlg.m_byProve3;
      m_pServiziSet->m_Prove4             = dlg.m_byProve4;
      m_pServiziSet->m_Prove5             = dlg.m_byProve5;
			m_pServiziSet->m_Aggiuntivo					= dlg.m_nAggiuntivo;
      if(dlg.m_bConcessione)
			  m_pServiziSet->m_Concessione			= SERVIZIO_CONCESSIONE;
      else if(dlg.m_bGeologia)
        m_pServiziSet->m_Concessione      = SERVIZIO_GEOLOGIA;
      else
        m_pServiziSet->m_Concessione      = SERVIZIO_NON_CONC;
      m_pServiziSet->m_Commento         	= dlg.m_strCommentoMateriale;
      m_pServiziSet->Update();
    }
		catch(CDBException* e)
		{
		  CString strError;

      if(pApp->DecodeDBError(e->m_strStateNativeOrigin) == ER_DUP_ENTRY)
			{
			  strError.Format("Nel listino è già presente un servizio con codice %s.",
			                  dlg.m_strID);
			  AfxMessageBox(strError);
				continue;
			}
			else
			{
			  strError = e->m_strError;
			  AfxMessageBox(strError);
			}
			return;
		}
		/*--- cerco il servizio ---*/
		for(n = 0, m_pServiziSet->Requery(); !m_pServiziSet->IsEOF(); n++, m_pServiziSet->MoveNext())
		  if(m_pServiziSet->m_ID == dlg.m_strID)
			  break;  
		/*--- inserisco il servizio  nella lista -----*/
		m_bDenySinc = TRUE;
		n = m_ListServizi.InsertItem(n, m_pServiziSet->m_ID);
    m_ListServizi.SetItemData(n, m_pServiziSet->m_Codice);
		str = m_pServiziSet->m_Descrizione;
		str.Replace("\r\n", "  ");
		m_ListServizi.SetItemText(n, 1, str);
    str = Valuta(m_pServiziSet->m_Prezzo).Format();
		str.TrimLeft(" .");
		m_ListServizi.SetItemText(n, 2, str);
		m_nServizi++;
		m_bDenySinc = FALSE;
		/*--- deselezione qualunque servizio ---*/
		m_pServiziSet->MoveFirst();
		m_pServiziSet->MovePrev();
		break;
	}
	UpdateData(FALSE);
}

void CListiniView::OnServiziNuovonota() 
{
	// TODO: Add your command handler code here
	
}

void CListiniView::OnServiziModifica() 
{
  int n, nCodice;
	CString str;
	CServiziListinoDlg dlg;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

  if(m_pSet->IsBOF() || m_pCategorieSet->IsBOF())
	{
	  MessageBeep(-1);
		return;
	}
  /*---- annoto il codice del servizio selezionato ----*/
	nCodice = m_pServiziSet->m_Codice;
	/*----- cerco gli ID disponibili ----*/
	for(n = 1, m_pServiziSet->MoveFirst();
	    n < 100 && !m_pServiziSet->IsEOF(); 
			n++)
	{
    str.Format("%s%02d", m_pCategorieSet->m_ID, n);
		if(nCodice == m_pServiziSet->m_Codice)
		  dlg.m_aryStrId.Add(str);
		if(str != m_pServiziSet->m_ID)
		  dlg.m_aryStrId.Add(str);
		else
	    m_pServiziSet->MoveNext();
  }
  /*---- aggiungo un nuovo codice ----*/
	if(n < 100)
	{
  	str.Format("%s%02d", m_pCategorieSet->m_ID, n);
    dlg.m_aryStrId.Add(str);
	}
	/*--- cerco il servizio selezionato nel recordset ---*/
	for(m_pServiziSet->MoveFirst(); !m_pServiziSet->IsEOF(); m_pServiziSet->MoveNext())
		if(m_pServiziSet->m_Codice == nCodice)
			break;  
  /*--- apro il dialogo ----*/
	dlg.m_strCategoria   = m_pCategorieSet->m_ID;
	dlg.m_strID          = m_pServiziSet->m_ID;
	dlg.m_strDescrizione = m_pServiziSet->m_Descrizione;
	dlg.m_strNome        = m_pServiziSet->m_Nome;
	dlg.m_strNorma       = m_pServiziSet->m_Norma;
	dlg.m_strRiferimenti = m_pServiziSet->m_Riferimenti;
	dlg.m_nProvini       = m_pServiziSet->m_Campioni;
	dlg.m_nProviniPerSerie = m_pServiziSet->m_ProviniPerSerie;
	if(m_pServiziSet->IsFieldNull(&m_pServiziSet->m_Prezzo))
	  dlg.m_fPrezzo = DBL_MAX;
	else
  	dlg.m_fPrezzo		 = m_pServiziSet->m_Prezzo;
	dlg.m_nPerSerie      = m_pServiziSet->m_PerSerie;
	dlg.m_nEmissione     = m_pServiziSet->m_Emissione;
	dlg.m_nCertificato   = m_pServiziSet->m_Certificato;
	dlg.m_nCertificato2  = m_pServiziSet->m_Certificato2;
	dlg.m_nCertificato3  = m_pServiziSet->m_Certificato3;
	dlg.m_nCertificato4  = m_pServiziSet->m_Certificato4;
	dlg.m_nCertificato5  = m_pServiziSet->m_Certificato5;
	dlg.m_byProve        = m_pServiziSet->m_Prove;
	dlg.m_byProve2       = m_pServiziSet->m_Prove2;
	dlg.m_byProve3       = m_pServiziSet->m_Prove3;
	dlg.m_byProve4       = m_pServiziSet->m_Prove4;
	dlg.m_byProve5       = m_pServiziSet->m_Prove5;
	dlg.m_nAggiuntivo    = m_pServiziSet->m_Aggiuntivo;
  switch(m_pServiziSet->m_Concessione)
  {
  case SERVIZIO_NON_CONC:
    dlg.m_bConcessione = 0;
    dlg.m_bGeologia = 0;
    break;
  case SERVIZIO_CONCESSIONE:
    dlg.m_bConcessione = 1;
    dlg.m_bGeologia = 0;
    break;
  case SERVIZIO_GEOLOGIA:
    dlg.m_bConcessione = 0;
    dlg.m_bGeologia = 1;
    break;
  }
	dlg.m_strCommentoMateriale = m_pServiziSet->m_Commento;
	while(dlg.DoModal() == IDOK)
	{
	  try
		{
			m_pServiziSet->Edit();
			m_pServiziSet->m_ID          = dlg.m_strID;
			m_pServiziSet->m_Descrizione = dlg.m_strDescrizione;
			m_pServiziSet->m_Nome        = dlg.m_strNome;
			m_pServiziSet->m_Norma       = dlg.m_strNorma;
			m_pServiziSet->m_Riferimenti = dlg.m_strRiferimenti;
			m_pServiziSet->m_Campioni    = dlg.m_nProvini;
			m_pServiziSet->m_ProviniPerSerie = dlg.m_nProviniPerSerie;
			if(dlg.m_fPrezzo == DBL_MAX)
				m_pServiziSet->SetFieldNull(&m_pServiziSet->m_Prezzo);
			else
				m_pServiziSet->m_Prezzo    = dlg.m_fPrezzo;
			m_pServiziSet->m_PerSerie    = dlg.m_nPerSerie;
			m_pServiziSet->m_Emissione   = dlg.m_nEmissione;
			m_pServiziSet->m_Certificato = dlg.m_nCertificato;
			m_pServiziSet->m_Certificato2= dlg.m_nCertificato2;
			m_pServiziSet->m_Certificato3= dlg.m_nCertificato3;
			m_pServiziSet->m_Certificato4= dlg.m_nCertificato4;
			m_pServiziSet->m_Certificato5= dlg.m_nCertificato5;
			m_pServiziSet->m_Prove       = dlg.m_byProve;
			m_pServiziSet->m_Prove2      = dlg.m_byProve2;
			m_pServiziSet->m_Prove3      = dlg.m_byProve3;
			m_pServiziSet->m_Prove4      = dlg.m_byProve4;
			m_pServiziSet->m_Prove5      = dlg.m_byProve5;
			m_pServiziSet->m_Aggiuntivo  = dlg.m_nAggiuntivo;
      if(dlg.m_bConcessione)
			  m_pServiziSet->m_Concessione = SERVIZIO_CONCESSIONE;
      else if(dlg.m_bGeologia)
        m_pServiziSet->m_Concessione = SERVIZIO_GEOLOGIA;
      else
        m_pServiziSet->m_Concessione = SERVIZIO_NON_CONC;
			m_pServiziSet->m_Commento      = dlg.m_strCommentoMateriale;
			m_pServiziSet->Update();
		}
		catch(CDBException* e)
		{
		  CString strError;

      if(pApp->DecodeDBError(e->m_strStateNativeOrigin) == ER_DUP_ENTRY)
			{
			  strError.Format("Nel listino è già presente un servizio con codice %s.",
			                  dlg.m_strID);
			  AfxMessageBox(strError);
        continue;
			}
			else
			{
			  strError = e->m_strError;
			  AfxMessageBox(strError);
			}
			return;
		}
		/*--- cerco il servizio nella lista ----*/
		for(n = 0; n < m_ListServizi.GetItemCount(); n++)
		  if(m_pServiziSet->m_Codice == (long)m_ListServizi.GetItemData(n))
			  break;
		/*--- modifico il servizio  nella lista -----*/
		m_ListServizi.SetItemText(n, 0, m_pServiziSet->m_ID);
		str = m_pServiziSet->m_Descrizione;
		str.Replace("\r\n", "  ");
		m_ListServizi.SetItemText(n, 1, str);
    str = Valuta(m_pServiziSet->m_Prezzo).Format();
		str.TrimLeft(" .");
		m_ListServizi.SetItemText(n, 2, str);
		break;
	}
	UpdateData(FALSE);
}

void CListiniView::OnServiziElimina() 
{
	CString str, strDescr;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

  if(m_pSet->IsBOF() || m_pCategorieSet->IsBOF())
	{
	  MessageBeep(-1);
		return;
	}
	/*---- chiedo conferma ----*/
	if( m_pServiziSet->m_Descrizione.GetLength() < 12)
	  strDescr = m_pServiziSet->m_Descrizione;
	else
	  strDescr = m_pServiziSet->m_Descrizione.Left(10) + " ...";
  str.Format("Eliminare il servizio %s (codice %s)?", strDescr, m_pServiziSet->m_ID);
  if(AfxMessageBox(str, MB_YESNO) == IDNO)
	  return;
	/*---- elimino il servizio dalla lista ----*/
	for(m_nServizi = 0; m_nServizi < m_ListServizi.GetItemCount(); m_nServizi++)
	{
		if((long)m_ListServizi.GetItemData(m_nServizi) == m_pServiziSet->m_Codice)
			m_ListServizi.DeleteItem(m_nServizi);
	}
	/*--- elimino il servizio dal recordset ----*/
	m_pServiziSet->Delete();
  m_pServiziSet->Requery();
	/*--- deselezione qualunque servizio ---*/
	m_pServiziSet->MoveFirst();
	m_pServiziSet->MovePrev();

  UpdateData(FALSE);
}

void CListiniView::OnItemactivateListCategorie(NMHDR* pNMHDR, LRESULT* pResult) 
{
  SincronizeCategorie();
	*pResult = 0;
}

void CListiniView::OnItemactivateListServizi(NMHDR* pNMHDR, LRESULT* pResult) 
{
	SincronizeServizi();
	*pResult = 0;
}

void CListiniView::OnItemchangedListCategorie(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!m_bDenySinc)
    SincronizeCategorie();
	*pResult = 0;
}

void CListiniView::OnItemchangedListServizi(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!m_bDenySinc)
    SincronizeServizi();
	*pResult = 0;
}

void CListiniView::OnDblclkListCategorie(NMHDR* pNMHDR, LRESULT* pResult) 
{
  OnCategoriaModifica();
	*pResult = 0;
}

void CListiniView::OnDblclkListServizi(NMHDR* pNMHDR, LRESULT* pResult) 
{
  OnServiziModifica();
	*pResult = 0;
}

void CListiniView::OnButtonCerca() 
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CTrovaAziendaDlg dlg;

  UpdateData(TRUE);
	if(dlg.DoModal() == IDOK)
	{
	  m_strCodiceAzienda = dlg.m_pSet->m_ID;
		m_strNomeAzienda   = dlg.m_pSet->m_RagioneSociale;
		m_nCodiceAzienda   = dlg.m_pSet->m_Codice;
		UpdateData(FALSE);
	}
}


CTime CListiniView::GetData(CString strData)
{
  // Converte la stringa strData in un CTime
  return CTime(atoi(strData.Mid(6)), atoi(strData.Mid(3, 2)), atoi(strData.Left(2)), 0, 0, 0);
}