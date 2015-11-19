// EmendaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "EmendaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEmendaDlg dialog


CEmendaDlg::CEmendaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEmendaDlg::IDD, pParent)
{
  m_cntEmendamenti  = 0;
  m_nIDCertificato  = 0;
  //{{AFX_DATA_INIT(CEmendaDlg)
	//}}AFX_DATA_INIT
}

void CEmendaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmendaDlg)
	DDX_Control(pDX, IDC_BUTTON_ELIMINA, m_bcElimina);
	DDX_Control(pDX, IDC_TREE_EMENDAMENTI, m_tcEmendamenti);
	DDX_Control(pDX, IDC_CERTIFICATO, m_tcCertificato);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEmendaDlg, CDialog)
	//{{AFX_MSG_MAP(CEmendaDlg)
	ON_BN_CLICKED(IDC_BUTTON_CREA, OnButtonCrea)
	ON_BN_CLICKED(IDC_BUTTON_ELIMINA, OnButtonElimina)
	ON_BN_CLICKED(IDC_BUTTON_CTOE, OnButtonCtoe)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmendaDlg message handlers

BOOL CEmendaDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
  // Caricamento delle Serie nel Certificato
  m_oaSerieEmend.RemoveAll();
  GetSerie();

  // Disabilita il pulsante "Elimina"
  m_bcElimina.EnableWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEmendaDlg::GetSerie()
{
  // Cancella il Certificato
  m_tcCertificato.DeleteAllItems();

  if (m_nIDCertificato != 0)
  {
    // Inserisce il numero di Certificato
    HTREEITEM hWA =  m_tcCertificato.InsertItem(m_strDescCertificato ,TVI_ROOT, TVI_LAST);
    m_tcCertificato.SetItemData(hWA,m_nIDCertificato);
    
    CString str("");

    // Aggiunge le Serie al Certificato
    for (int i(0); i < m_waIDSerie.GetSize(); i++)
    {
      str.Format("Serie n° %d",i + 1);

      HTREEITEM hWB = m_tcCertificato.InsertItem(str ,hWA, TVI_LAST);
      // Aggiunge l'ID della Serie nell'ItemData
      m_tcCertificato.SetItemData(hWB,m_waIDSerie[i]);
    }
    
    // Seleziona il Certificato appena creato
    m_tcCertificato.SelectItem(m_tcCertificato.GetRootItem());
  }
}

void CEmendaDlg::OnButtonCrea() 
{
  // Incrementa il contatore degli Emendamenti
  m_cntEmendamenti++;
  
  // Crea una voce negli Emendamenti
  CString str("");
  str.Format("Emendamento n° %d", m_cntEmendamenti);
  HTREEITEM hWA = m_tcEmendamenti.InsertItem(str ,TVI_ROOT, TVI_LAST);
  
  // Seleziona l'Emedamento appena creato
  m_tcEmendamenti.Select(hWA,TVGN_CARET);

  // Se esiste almeno un Emendamento abilita il pulsante "Elimina"
  if (m_tcEmendamenti.GetCount() != 0)
    m_bcElimina.EnableWindow(TRUE);
	
}

void CEmendaDlg::OnButtonElimina() 
{
  HTREEITEM hWA = m_tcEmendamenti.GetSelectedItem();
  HTREEITEM hWB = NULL;
  CString txt("");

  // Controlla se eliminare l'intero Emendamento o solo un Item
  if ((m_tcEmendamenti.GetParentItem(hWA) == NULL) && (m_tcEmendamenti.ItemHasChildren(hWA)))
  {
    while ((hWA = m_tcEmendamenti.GetNextItem(hWA,TVGN_CHILD)) != NULL)
    {
      txt = m_tcEmendamenti.GetItemText(hWA);

      hWB = m_tcCertificato.GetRootItem();
      hWB = m_tcCertificato.InsertItem(txt, hWB, TVI_LAST);
      m_tcCertificato.SetItemData(hWB, m_tcEmendamenti.GetItemData(hWA));
      
      // Si posiziona sul padre
      hWB = hWA;
      hWA = m_tcEmendamenti.GetParentItem(hWA);

      // Elimina l'Item dall'Emendamento
      m_tcEmendamenti.DeleteItem(hWB);

      if (!m_tcEmendamenti.ItemHasChildren(hWA))
        break;
    }
  }
  else if (m_tcEmendamenti.GetParentItem(hWA) != NULL)
  { 
    txt = m_tcEmendamenti.GetItemText(hWA);

    hWB = m_tcCertificato.GetRootItem();
    hWB = m_tcCertificato.InsertItem(txt, hWB, TVI_LAST);
    m_tcCertificato.SetItemData(hWB, m_tcEmendamenti.GetItemData(hWA));
  }
  
  // Elimina l'Item dal Certificato perchè è stao inserito tra gli Emendamenti
  bool rigenera = false;
  if (!m_tcEmendamenti.ItemHasChildren(hWA))
    rigenera = true;

  m_tcEmendamenti.DeleteItem(hWA);

  if (rigenera)
  {
    m_cntEmendamenti--;

    hWA = m_tcEmendamenti.GetRootItem();

    for (int i(1); i <= m_cntEmendamenti; i++)
    {
      CString app("");
      app.Format("Emendamento n° %d",i);

      m_tcEmendamenti.SetItemText(hWA,app);

      hWA = m_tcEmendamenti.GetNextItem(hWA, TVGN_NEXT);
    }
  }

  hWA = m_tcCertificato.GetRootItem();
  m_tcCertificato.Expand(hWA,TVE_EXPAND);

  // Disabilita il pulsante Elimina se non esistono Emendamenti
  if (m_tcEmendamenti.GetCount() == 0)
    m_bcElimina.EnableWindow(FALSE);
}

void CEmendaDlg::OnButtonCtoe() 
{
	/*---- Copia ItemCertificato in ItemEmendamenti ----*/

  // Controlla che sia stato creato almeno un emendamento
  if ((m_tcEmendamenti.GetCount() != 0) && (m_tcEmendamenti.GetParentItem(m_tcEmendamenti.GetSelectedItem()) == NULL))
  {
	  HTREEITEM hWA = NULL;
    HTREEITEM hWB = NULL;
    CString txt("");

    hWA = m_tcCertificato.GetSelectedItem();

    // Se è selezionato l'intero Certificato lo copia nell'Emendamento selezionato
    if (m_tcCertificato.GetRootItem() == hWA)
    {
      // Scorre ed inserisce gli altri figli del Certificato
      while(hWA  = m_tcCertificato.GetChildItem(hWA))

      {
        txt = m_tcCertificato.GetItemText(hWA);

        hWB = m_tcEmendamenti.GetSelectedItem();
        hWB = m_tcEmendamenti.InsertItem(txt, hWB, TVI_LAST);
        m_tcEmendamenti.SetItemData(hWB, m_tcCertificato.GetItemData(hWA));

        // Elimina l'Item dal Certificato
        m_tcCertificato.DeleteItem(hWA);

        // Si posiziona sulla radice del Certificato
        hWA = m_tcCertificato.GetRootItem();
      }
      
      hWB = m_tcEmendamenti.GetParentItem(hWB);
      m_tcEmendamenti.Expand(hWB,TVE_EXPAND);
    }
    else
    {
      // Preleva il testo dall'Item selezionato nel Certificato
      hWA = m_tcCertificato.GetSelectedItem();
      txt = m_tcCertificato.GetItemText(hWA);

      // Inserisce l'Item del Certificato nell'Emendamento selezionato
      hWB = m_tcEmendamenti.GetSelectedItem();
      hWB = m_tcEmendamenti.InsertItem(txt, hWB, TVI_LAST);
      m_tcEmendamenti.SetItemData(hWB, m_tcCertificato.GetItemData(hWA));

      // Elimina l'Item dal Certificato
      m_tcCertificato.DeleteItem(hWA);

      // Seleziona l'ultimo Item inserito
      m_tcEmendamenti.Select(hWB, TVGN_CARET);
      m_tcEmendamenti.Expand(hWB, TVE_EXPAND);
      m_tcCertificato.Expand(m_tcCertificato.GetRootItem(), TVE_EXPAND);
    }
  }
  else
    AfxMessageBox("Deve essere creato e/o selezionato almeno un emendamento.", MB_OK|MB_ICONEXCLAMATION);
}

void CEmendaDlg::OnOK() 
{
  /*---- Salva i dati gli Emendamenti nel CObbArray per effettuare il salvataggio sul Database----*/
  HTREEITEM hWA = m_tcEmendamenti.GetRootItem();
  HTREEITEM hWB = NULL;
  int count(-1);
  while (hWA)
  {
    if (m_tcEmendamenti.ItemHasChildren(hWA))
    {
      m_oaSerieEmend.Add(new CDWordArray);
      count++;
    }
    
    hWB = m_tcEmendamenti.GetNextItem(hWA,TVGN_CHILD);

    while (hWB)
    {
      ((CDWordArray*)(((CWordArray*)(m_oaSerieEmend.GetAt(count)))))->Add((DWORD)m_tcEmendamenti.GetItemData(hWB));
      hWB = m_tcEmendamenti.GetNextItem(hWB,TVGN_NEXT);
    }

    m_tcEmendamenti.SelectItem(hWA);
    hWA = m_tcEmendamenti.GetNextItem(hWA,TVGN_NEXT);
  }

	CDialog::OnOK();
}
