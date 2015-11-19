// FindVerbali.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "winsigmadoc.h"
#include "FindVerbaliDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindVerbali dialog


CFindVerbaliDlg::CFindVerbaliDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindVerbaliDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindVerbaliDlg)
	m_nChiaveRicerca = -1;
	m_strChiaveRicerca = _T("");
	//}}AFX_DATA_INIT
  m_pDoc = NULL;
}

CFindVerbaliDlg::~CFindVerbaliDlg()
{
}


void CFindVerbaliDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindVerbaliDlg)
	DDX_Control(pDX, IDC_EDIT_CHIAVE, m_EditChiave);
	DDX_Control(pDX, IDC_LIST_VERBALI, m_ListVerbali);
	DDX_Radio(pDX, IDC_RADIO_CANTIERE, m_nChiaveRicerca);
	DDX_Text(pDX, IDC_EDIT_CHIAVE, m_strChiaveRicerca);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindVerbaliDlg, CDialog)
	//{{AFX_MSG_MAP(CFindVerbaliDlg)
	ON_BN_CLICKED(IDC_BUTTON_CERCA, OnButtonCerca)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_VERBALI, OnDblclkListVerbali)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindVerbali message handlers

BOOL CFindVerbaliDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

  DWORD style;
  style = m_ListVerbali.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT;
	m_ListVerbali.SetExtendedStyle(style);
  m_ListVerbali.DeleteAllItems();
  m_ListVerbali.InsertColumn(0, "", LVCFMT_LEFT, 0);
  m_ListVerbali.InsertColumn(1, "Numero", LVCFMT_CENTER, 70, -1);
  m_ListVerbali.InsertColumn(2, "Data", LVCFMT_CENTER, 80, -1);
  m_ListVerbali.InsertColumn(3, "Tipo", LVCFMT_LEFT, 100, -1);
  m_ListVerbali.InsertColumn(4, "Certificati", LVCFMT_LEFT, 135, -1);
  m_ListVerbali.InsertColumn(5, "Impresa", LVCFMT_LEFT, 135, -1);
  m_ListVerbali.InsertColumn(6, "Fattura", LVCFMT_LEFT, 135, -1);
  m_ListVerbali.InsertColumn(7, "Cantiere", LVCFMT_LEFT, 190, -1);
  m_nCodiceVerbale = -1;
  m_strChiaveRicerca.Empty();
  SetWindowText(m_strTitolo);
  m_EditChiave.SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CFindVerbaliDlg::FindVerbali()
{
  UpdateData(TRUE);

  int n = 0, codice;
  CString str1, str2, strFilter;
  if(m_strChiaveRicerca.IsEmpty())
  {
    AfxMessageBox("Specificare una chiave di ricerca");
    return FALSE;
  }
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CVerbaliSet* pVerbaliSet = new CVerbaliSet(&pApp->m_db);
  pVerbaliSet->m_strFilter.Format("TipoVerbale <> %d AND TipoVerbale <> %d", VERB_PER_FATTURA, VERB_PER_NOTACREDITO);
  if(m_nAnnoAccettazione > 0)
  {
    // Filtro sulla data di accettazione
    str1.Format("%d-1-1 00:00:00", m_nAnnoAccettazione);
    str2.Format("%d-12-31 23:59:59", m_nAnnoAccettazione);
    strFilter.Format(" AND (DataAccettazione >= '%s' AND DataAccettazione <= '%s')", str1, str2);
    pVerbaliSet->m_strFilter += strFilter;
  }
  // Filtro su verbali aperti o chiusi
  if(m_bChiusi)
    pVerbaliSet->m_strFilter += " AND DataChiusura is not NULL";
  else
    pVerbaliSet->m_strFilter += " AND DataChiusura is NULL";
  pVerbaliSet->m_strSort = "Codice ASC";
  pVerbaliSet->Open();
  m_ListVerbali.DeleteAllItems();
 	CSerieSet* pSerieSet = new CSerieSet(&pApp->m_db);
  switch(m_nChiaveRicerca)
  {
  case SEARCH_NUMERO:
    pVerbaliSet->m_strFilter += " AND ProgressivoTotale = " + m_strChiaveRicerca;
    pVerbaliSet->Requery();
    for(SET_START(pVerbaliSet); !pVerbaliSet->IsEOF(); pVerbaliSet->MoveNext())
    {
      CString s("");
      s.Format("%d", pVerbaliSet->m_ProgressivoTotale);
      CheckAndAdd(s, pVerbaliSet);
    }
    break;
  case SEARCH_CANTIERE:
    pVerbaliSet->m_strFilter += " AND Cantiere like '%" + m_strChiaveRicerca + "%'";
    pVerbaliSet->Requery();
    for(SET_START(pVerbaliSet); !pVerbaliSet->IsEOF(); pVerbaliSet->MoveNext())
      CheckAndAdd(pVerbaliSet->m_Cantiere, pVerbaliSet);
    break;
  case SEARCH_DIRLAVORI:
    pVerbaliSet->m_strFilter += " AND DirettoreLavori like '%" + m_strChiaveRicerca + "%'";
    pVerbaliSet->Requery();
    for(SET_START(pVerbaliSet); !pVerbaliSet->IsEOF(); pVerbaliSet->MoveNext())
      CheckAndAdd(pVerbaliSet->m_Direttore, pVerbaliSet);
    break;
  case SEARCH_CERTIFICATO:
    pVerbaliSet->m_strFilter += " AND NomeIntestatarioCertificato like '%" + m_strChiaveRicerca + "%'";
    pVerbaliSet->Requery();
    for(SET_START(pVerbaliSet); !pVerbaliSet->IsEOF(); pVerbaliSet->MoveNext())
      CheckAndAdd(pVerbaliSet->m_NomeAzCertificato, pVerbaliSet);
    break;
  case SEARCH_FATTURA:
    pVerbaliSet->m_strFilter += " AND NomeIntestatarioFattura like '%" + m_strChiaveRicerca + "%'";
    pVerbaliSet->Requery();
    for(SET_START(pVerbaliSet); !pVerbaliSet->IsEOF(); pVerbaliSet->MoveNext())
      CheckAndAdd(pVerbaliSet->m_NomeAzFattura, pVerbaliSet);
    break;
  case SEARCH_IMPRESA:
    pVerbaliSet->m_strFilter += " AND NomeImpresaRichiedente like '%" + m_strChiaveRicerca + "%'";
    pVerbaliSet->Requery();
    for(SET_START(pVerbaliSet); !pVerbaliSet->IsEOF(); pVerbaliSet->MoveNext())
      CheckAndAdd(pVerbaliSet->m_NomeImpresa, pVerbaliSet);
    break;
	case SEARCH_STRUTTURA:
    str1 = m_strChiaveRicerca;
    str1.MakeUpper();
    pSerieSet->m_strFilter = "StrutturaPrelievo like '%" + str1 + "%'";
    pSerieSet->m_strSort = "Verbale";
	  pSerieSet->Open();
    if(pSerieSet->IsEOF())
      break;
    codice = 0;
    for(SET_START(pSerieSet); !pSerieSet->IsEOF(); pSerieSet->MoveNext())
    {
      if(codice != pSerieSet->m_Verbale)
      {
        codice = pSerieSet->m_Verbale;
        pVerbaliSet->m_strFilter.Format("Codice = %d", codice);
        pVerbaliSet->Requery();
        if(pVerbaliSet->m_TipoVerbale == VERB_PER_FATTURA || pVerbaliSet->m_TipoVerbale == VERB_PER_NOTACREDITO)
          continue;
        AddItem(pVerbaliSet);
      }
    }
    pSerieSet->Close();
    delete pSerieSet;
    break;

    break;
  case SEARCH_SIGLA:
    str1 = m_strChiaveRicerca;
    str1.MakeUpper();
    pSerieSet->m_strFilter = "Sigla like '%" + str1 + "%'";
    pSerieSet->m_strSort = "Verbale";
	  pSerieSet->Open();
    if(pSerieSet->IsEOF())
      break;
    codice = 0;
    for(SET_START(pSerieSet); !pSerieSet->IsEOF(); pSerieSet->MoveNext())
    {
      if(codice != pSerieSet->m_Verbale)
      {
        codice = pSerieSet->m_Verbale;
        pVerbaliSet->m_strFilter.Format("Codice = %d", codice);
        pVerbaliSet->Requery();
        if(pVerbaliSet->m_TipoVerbale == VERB_PER_FATTURA || pVerbaliSet->m_TipoVerbale == VERB_PER_NOTACREDITO)
          continue;
        AddItem(pVerbaliSet);
      }
    }
    pSerieSet->Close();
    delete pSerieSet;
    break;
  }
  if(pVerbaliSet->IsEOF() && !m_ListVerbali.GetItemCount())
  {
    pVerbaliSet->Close();
    AfxMessageBox("Impossibile trovare verbali per la chiave di ricerca selezionata");
    return FALSE;
  }
  m_nCodiceVerbale = pVerbaliSet->m_Codice;
  UpdateData(FALSE);
  pVerbaliSet->Close();
  return TRUE;
}

void CFindVerbaliDlg::CheckAndAdd(CString strChiave, CVerbaliSet* pSet)
{
  CString str;
  int n = 0;

  if(pSet->m_TipoVerbale == VERB_PER_FATTURA || pSet->m_TipoVerbale == VERB_PER_NOTACREDITO)
    return;
  strChiave.MakeUpper();
  str = m_strChiaveRicerca;
  str.MakeUpper();
  if(strChiave.Find(str) >= 0)
    AddItem(pSet);
}

void CFindVerbaliDlg::OnButtonCerca() 
{
	SetCursor(LoadCursor(NULL, IDC_WAIT));
  FindVerbali();
}

void CFindVerbaliDlg::OnOK() 
{
  SelectVerbale();
  CDialog::OnOK();
}

void CFindVerbaliDlg::OnDblclkListVerbali(NMHDR* pNMHDR, LRESULT* pResult) 
{
  SelectVerbale();
  *pResult = 0;
  CDialog::OnOK();
}

void CFindVerbaliDlg::SelectVerbale()
{
	int n;
  POSITION pos;
  CTime date;
  CString strDate;

  date = CTime::GetCurrentTime() - CTimeSpan(30, 0, 0, 0);
  strDate = date.Format("%Y-%m-%d");
  
  if((pos = m_ListVerbali.GetFirstSelectedItemPosition()) == NULL)
  {
    AfxMessageBox("Selezionare un dato valido");
    return;
  }
  n = m_ListVerbali.GetNextSelectedItem(pos);
  m_nCodiceVerbale = m_ListVerbali.GetItemData(n);
  if(m_pDoc != NULL)
  {
    CVerbaliSet* pVerbaliSet = new CVerbaliSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
    pVerbaliSet->m_strFilter.Format("Codice = %ld and DataAccettazione >= '%s'", m_nCodiceVerbale, strDate);
    pVerbaliSet->Open();
    if(pVerbaliSet->IsEOF())
      m_pDoc->m_nSelectedTreeVerbali = TREEITEM_VERBALIPRECEDENTI;
    else
      m_pDoc->m_nSelectedTreeVerbali = TREEITEM_VERBALIULTIMOMESE;
    pVerbaliSet->Close();
    delete pVerbaliSet;
  }
}

void CFindVerbaliDlg::AddItem(CVerbaliSet* pSet)
{
  CString str;
  int n = 0;
  
  str.Format("%d", pSet->m_ProgressivoTotale);
  n = m_ListVerbali.InsertItem(n, "");
  m_ListVerbali.SetItemText(n, 1, str);
  m_ListVerbali.SetItemData(n, pSet->m_Codice);
  m_ListVerbali.SetItemText(n, 2, pSet->m_DataAccettazione.Format("%d/%m/%y"));
  switch(pSet->m_TipoVerbale)
  {
  case VERB_IN_CONCESSIONE:
    str = "In concessione";
    break;
  case VERB_NON_IN_CONCESSIONE:
	case VERB_NC_PROVE_DI_CARICO :
	case VERB_NC_CONGL_BITUMINOSI	:
	case VERB_NC_INERTI	:
	case VERB_NC_MONITORAGGI :
	case VERB_NC_VARIE:	
  case VERB_NC_GEOTECNICA :
    str = "Non in concessione";
    break;
  case VERB_GEOLOGIA:
    str = "Prove geotecniche";
    break;
  case VERB_VECCHIO_PROG:
    str.Format("Precedente al 1/1/2004");
    break;
  }
  m_ListVerbali.SetItemText(n, 3, str);
  m_ListVerbali.SetItemText(n, 4, pSet->m_NomeAzCertificato);
  m_ListVerbali.SetItemText(n, 5, pSet->m_NomeImpresa);
  m_ListVerbali.SetItemText(n, 6, pSet->m_NomeAzFattura);
  m_ListVerbali.SetItemText(n, 7, pSet->m_Cantiere);
}
