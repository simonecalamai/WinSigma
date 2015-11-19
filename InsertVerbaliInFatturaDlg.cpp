// InsertVerbaliInFatturaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "XFormView.h"
#include "VerbaliView.h"
#include "InsertVerbaliInFatturaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsertVerbaliInFatturaDlg dialog


CInsertVerbaliInFatturaDlg::CInsertVerbaliInFatturaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInsertVerbaliInFatturaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInsertVerbaliInFatturaDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInsertVerbaliInFatturaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsertVerbaliInFatturaDlg)
	DDX_Control(pDX, IDC_LIST_VERBALIDAFATTURARE, m_ListVerbali);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsertVerbaliInFatturaDlg, CDialog)
	//{{AFX_MSG_MAP(CInsertVerbaliInFatturaDlg)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_VERBALIDAFATTURARE, OnDblclkListVerbalidafatturare)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsertVerbaliInFatturaDlg message handlers

void CInsertVerbaliInFatturaDlg::OnCancel() 
{
	if(m_pVerbaliSet)
  {
    m_pVerbaliSet->Close();
    delete m_pVerbaliSet;
  }
	CDialog::OnCancel();
}

void CInsertVerbaliInFatturaDlg::OnDblclkListVerbalidafatturare(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	InsertVerbale();
	*pResult = 0;
  CDialog::OnOK();
}


void CInsertVerbaliInFatturaDlg::OnOK() 
{
  InsertVerbale();
	CDialog::OnOK();
}

void CInsertVerbaliInFatturaDlg::InsertVerbale(void)
{
  POSITION pos;
  if((pos = m_ListVerbali.GetFirstSelectedItemPosition()) == NULL)
  {
    AfxMessageBox("Selezionare un verbale da aggiungere alla fattura.");
    return;
  }
  int n = m_ListVerbali.GetNextSelectedItem(pos);
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

  SINCRONIZE(m_pVerbaliSet, (long)m_ListVerbali.GetItemData(n));
  // Controllo la coerenza della data
  CFattureSet* pFattureSet = new CFattureSet(&pApp->m_db);
  pFattureSet->m_strFilter.Format("Codice = %ld", m_lCodiceFattura);
  pFattureSet->Open();
  if(CTime(pFattureSet->m_Data.GetYear(), pFattureSet->m_Data.GetMonth(), pFattureSet->m_Data.GetDay(), 0, 0, 0) 
    < CTime(m_pVerbaliSet->m_DataAccettazione.GetYear(), m_pVerbaliSet->m_DataAccettazione.GetMonth(), m_pVerbaliSet->m_DataAccettazione.GetDay(), 0, 0 ,0))
  {
    AfxMessageBox("Attenzione: la data di emissione della fattura è precedente alla data\ndi accettazione del verbale. Impossibile inserire il verbale nella fattura.");
    pFattureSet->Close();
    return;
  }
  pFattureSet->Close();
  if(m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_NumeroFattura))
  {
    // Se il verbale non è stato messo in fatturazione, devo erogare i servizi
    CSerieSet* pSerieSet = new CSerieSet(&pApp->m_db);
    pSerieSet->m_strFilter.Format("Verbale = %ld", m_pVerbaliSet->m_Codice);
    pSerieSet->m_strSort = "Codice";
    pSerieSet->Open();
    for(SET_START(pSerieSet); !pSerieSet->IsEOF(); pSerieSet->MoveNext())
      CVerbaliView::ErogaServiziSerie(pSerieSet);
    pSerieSet->Close();    
  }
  CServiziErogatiSet* pServiziErogati = new CServiziErogatiSet(&pApp->m_db);
  pServiziErogati->m_strFilter.Format("Verbale = %ld", m_pVerbaliSet->m_Codice);
  pServiziErogati->m_strSort = "Codice";
  pServiziErogati->Open();
  for(SET_START(pServiziErogati); !pServiziErogati->IsEOF(); pServiziErogati->MoveNext())
  {
    pServiziErogati->Edit();
    pServiziErogati->m_Fattura = m_lCodiceFattura;
    pServiziErogati->Update();
  }
  pServiziErogati->Close();
  m_pVerbaliSet->Edit();
  m_pVerbaliSet->m_NumeroFattura = m_lCodiceFattura;
  m_pVerbaliSet->m_InFatturazione = 1;
  m_pVerbaliSet->m_DataChiusura = CTime::GetCurrentTime();
  m_pVerbaliSet->Update();
  if(m_pVerbaliSet)
  {
    m_pVerbaliSet->Close();
    delete m_pVerbaliSet;
  }
}


BOOL CInsertVerbaliInFatturaDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	DWORD style = m_ListVerbali.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT;
	m_ListVerbali.SetExtendedStyle(style);
  m_ListVerbali.InsertColumn(0, "Numero", LVCFMT_LEFT, 80);
  m_ListVerbali.InsertColumn(1, "Data", LVCFMT_LEFT, 80);
  m_ListVerbali.InsertColumn(2, "Tipo", LVCFMT_LEFT, 120);
  m_ListVerbali.InsertColumn(3, "Stato", LVCFMT_LEFT, 80);

  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  // Carico la lista dei verbali
  m_pVerbaliSet = new CVerbaliSet(&pApp->m_db);
  m_pVerbaliSet->m_strFilter.Format("DataChiusura is null and IntestatarioFattura = %ld AND (Fattura is NULL or Fattura = 0)", m_lCodiceAzienda);
  m_pVerbaliSet->Open();
  if(m_pVerbaliSet->IsEOF())
  {
    AfxMessageBox("Non ci sono verbali da fatturare per questo cliente.");
    OnCancel();
    return TRUE;
  }
  int n = 0;
  CString str;
  for(SET_START(m_pVerbaliSet); !m_pVerbaliSet->IsEOF(); m_pVerbaliSet->MoveNext())
  {
    if(!m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_ProgressivoTotale) && m_pVerbaliSet->m_ProgressivoTotale != 0)
      str.Format("%d/%d", m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale);
    else
      str.Empty();
    m_ListVerbali.InsertItem(n, str);
    m_ListVerbali.SetItemData(n, m_pVerbaliSet->m_Codice);
    m_ListVerbali.SetItemText(n, 1, m_pVerbaliSet->m_DataAccettazione.Format("%d/%m/%y"));
    switch(m_pVerbaliSet->m_TipoVerbale)
    {
      case VERB_NON_IN_CONCESSIONE:
			case VERB_NC_PROVE_DI_CARICO :
			case VERB_NC_CONGL_BITUMINOSI	:
			case VERB_NC_INERTI	:
			case VERB_NC_MONITORAGGI :
			case VERB_NC_VARIE	:
			case VERB_NC_GEOTECNICA :
        str = "Prove non in concessione";
        break;
      case VERB_IN_CONCESSIONE:
        str = "Prove in concessione";
        break;
      case VERB_GEOLOGIA:
        str = "Prove geotecniche";
        break;
      case VERB_VECCHIO_PROG:
        str = "Precedente al 1/1/2004";
        break;
      case VERB_PER_FATTURA:
        str.Empty();
        str = "Fattura senza verbale";
        break;
      case VERB_PER_NOTACREDITO:
        str.Empty();
        str = "Nota di credito";
        break;
    }
    m_ListVerbali.SetItemText(n, 2, str);
    if(m_pVerbaliSet->IsFieldNull(&m_pVerbaliSet->m_NumeroFattura))
      str = "Aperto";
    else
      str = "In fatturazione";
    m_ListVerbali.SetItemText(n, 3, str);
  }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

