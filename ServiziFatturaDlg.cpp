// ServiziFatturaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "WinSigmaDoc.h"
#include "ServiziFatturaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServiziFatturaDlg dialog


CServiziFatturaDlg::CServiziFatturaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServiziFatturaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServiziFatturaDlg)
	m_strDescrizione = _T("");
	m_strImporto = _T("");
	m_strQuantita = _T("");
	m_strNote = _T("");
	m_strSconto = _T("");
	m_bListinoGenerale = FALSE;
	//}}AFX_DATA_INIT
  m_lCodiceAzienda = -1;
  m_lCodiceVerbale = -1;
  m_lCodiceServizioErogato = -1;
  m_bChangeSconto = TRUE;
}


void CServiziFatturaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServiziFatturaDlg)
	DDX_Control(pDX, IDC_CHECK_LISTINOGENERALE, m_BtnListinoGenerale);
	DDX_Control(pDX, IDC_EDIT_SCONTO, m_EditSconto);
	DDX_Control(pDX, IDC_EDIT_QUANTITA, m_EditQuantita);
	DDX_Control(pDX, IDC_EDIT_NOTE, m_EditNote);
	DDX_Control(pDX, IDC_EDIT_DESCRIZIONE, m_EditDescrizione);
	DDX_Control(pDX, IDC_COMBO_VERBALE, m_ComboVerbali);
	DDX_Control(pDX, IDC_COMBO_SERVIZIO, m_ComboServizi);
	DDX_Control(pDX, IDC_COMBO_CATEGORIA, m_ComboCategorie);
	DDX_Text(pDX, IDC_EDIT_DESCRIZIONE, m_strDescrizione);
	DDV_MaxChars(pDX, m_strDescrizione, 255);
	DDX_Text(pDX, IDC_EDIT_QUANTITA, m_strQuantita);
	DDX_Text(pDX, IDC_EDIT_NOTE, m_strNote);
	DDV_MaxChars(pDX, m_strNote, 64);
	DDX_Text(pDX, IDC_EDIT_SCONTO, m_strSconto);
	DDX_Control(pDX, IDC_MASKEDBOX_IMPORTO, m_MskImporto);
	DDX_Control(pDX, IDC_MASKEDBOX_PREZZO, m_MskPrezzo);
	DDX_Check(pDX, IDC_CHECK_LISTINOGENERALE, m_bListinoGenerale);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServiziFatturaDlg, CDialog)
	//{{AFX_MSG_MAP(CServiziFatturaDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_VERBALE, OnSelchangeComboVerbale)
	ON_CBN_SELCHANGE(IDC_COMBO_CATEGORIA, OnSelchangeComboCategoria)
	ON_CBN_SELCHANGE(IDC_COMBO_SERVIZIO, OnSelchangeComboServizio)
	ON_EN_CHANGE(IDC_EDIT_SCONTO, OnChangeEditSconto)
	ON_EN_CHANGE(IDC_EDIT_QUANTITA, OnChangeEditQuantita)
	ON_EN_CHANGE(IDC_EDIT_DESCRIZIONE, OnChangeEditDescrizione)
	ON_BN_CLICKED(IDC_CHECK_LISTINOGENERALE, OnCheckListinogenerale)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServiziFatturaDlg message handlers

BOOL CServiziFatturaDlg::OnInitDialog() 
{
  // Se non è stato impostato il codice azienda esco subito
  if(m_lCodiceAzienda <= 0 || m_pDoc == NULL)
    return FALSE;
	CDialog::OnInitDialog();
  
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  CString str, str2;
  switch(m_nOperazione)
  {
  case MODIFICA_SERVIZIO:
    str = "Modifica servizio";
    break;
  case AGGIUNGI_SERVIZIO:
  default:
    str = "Aggiungi servizio";
    m_nOperazione = AGGIUNGI_SERVIZIO;
    break;
  }
  str += " in fatturazione";
  SetWindowText(str);

  m_pVerbaliInFatturazione = new CVerbaliSet(&pApp->m_db);
  m_pServiziErogati = new CServiziErogatiSet(&pApp->m_db);
  m_pFattureSet = new CFattureSet(&pApp->m_db);
  m_pFattureSet->Open();  
  if(m_lCodiceVerbale != -1)
  {
    m_pVerbaliInFatturazione->m_strFilter.Format("Codice = %d", m_lCodiceVerbale);
    if(m_lCodiceServizioErogato != -1)
      m_pServiziErogati->m_strFilter.Format("Verbale = %d AND Codice = %d", m_lCodiceVerbale, m_lCodiceServizioErogato);
    else
      m_pServiziErogati->m_strFilter.Format("Verbale = %d", m_lCodiceVerbale);
    str.Format(" AND Fattura = %d", m_lCodiceFattura);
    m_pVerbaliInFatturazione->m_strFilter += str;
    m_pServiziErogati->m_strFilter += str;
  }
  else 
  {
    if(m_lCodiceFattura > 0)
      m_pVerbaliInFatturazione->m_strFilter.Format("Fattura = %d", m_lCodiceFattura);
    else
      m_pVerbaliInFatturazione->m_strFilter.Format("IntestatarioFattura = %d AND Fattura = 0 AND (InFatturazione = 1 OR InFatturazione = 2)", m_lCodiceAzienda);
    m_pServiziErogati->m_strFilter.Format("Fattura = %d", m_lCodiceFattura); 
  }
  // C'è un codice valido per la fattura
  if(m_lCodiceFattura > 0)
  {
    SINCRONIZE(m_pFattureSet, m_lCodiceFattura);
  }
  m_pVerbaliInFatturazione->Open();
  m_pServiziErogati->Open();
  m_pCategorieServiziSet = new CCategorieServiziSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
  InitListino();
  m_BtnListinoGenerale.EnableWindow(!m_bListinoGenerale);
  m_pCategorieServiziSet->m_strFilter.Format("(CATEGORIE.Listino = %d OR CATEGORIE.Listino = %d) AND CATEGORIE.Codice = SERVIZI_LISTINO.Categoria", m_lListinoGenerale, m_lListinoParticolare);
  m_pCategorieServiziSet->Open();
  m_dImporto = 0.;
  str = m_MskPrezzo.GetMask();
  str.Replace("#", "_");
  m_MskPrezzo.SetText(str);
  str = m_MskImporto.GetMask();
  str.Replace("#", "_");
  m_MskImporto.SetText(str);
  // Inizalizzo le combo dei verbali, delle categorie e dei servizi
  InitVerbali();
  InitCategorie();
  InitServizi();
  UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CServiziFatturaDlg::InitVerbali(void)
{
  CString str;
  int n;
  long codice = -1;
  
  // Carico la lista dei verbali
  for(SET_START(m_pVerbaliInFatturazione); !m_pVerbaliInFatturazione->IsEOF(); m_pVerbaliInFatturazione->MoveNext())
  {
    if(codice != m_pVerbaliInFatturazione->m_Codice)
    {
      codice = m_pVerbaliInFatturazione->m_Codice;  
      switch(m_pVerbaliInFatturazione->m_TipoVerbale)
      {
      case VERB_NON_IN_CONCESSIONE:
			case VERB_NC_PROVE_DI_CARICO :
			case VERB_NC_CONGL_BITUMINOSI	:
			case VERB_NC_INERTI	:
			case VERB_NC_MONITORAGGI :
			case VERB_NC_VARIE	:
			case VERB_NC_GEOTECNICA :
#ifdef WINSIGMA2
        str.Format("Verbale senza prove in concessione n. A%d del %s", m_pVerbaliInFatturazione->m_ProgressivoTotale, m_pVerbaliInFatturazione->m_DataAccettazione.Format("%d/%m/%Y"));
#else
        str.Format("Verbale senza prove in concessione n. %d/%d del %s", m_pVerbaliInFatturazione->m_ProgressivoParziale, m_pVerbaliInFatturazione->m_ProgressivoTotale, m_pVerbaliInFatturazione->m_DataAccettazione.Format("%d/%m/%Y"));
#endif
        break;
      case VERB_IN_CONCESSIONE:
        str.Format("Verbale con prove in concessione n. %d/%d del %s", m_pVerbaliInFatturazione->m_ProgressivoParziale, m_pVerbaliInFatturazione->m_ProgressivoTotale, m_pVerbaliInFatturazione->m_DataAccettazione.Format("%d/%m/%Y"));
        break;
      case VERB_GEOLOGIA:
        str.Format("Verbale con prove geotecniche n. %d/%d del %s", m_pVerbaliInFatturazione->m_ProgressivoParziale, m_pVerbaliInFatturazione->m_ProgressivoTotale, m_pVerbaliInFatturazione->m_DataAccettazione.Format("%d/%m/%Y"));
        break;
      case VERB_VECCHIO_PROG:
        str.Format("Verbale n. %d/%d del %s", m_pVerbaliInFatturazione->m_ProgressivoParziale, m_pVerbaliInFatturazione->m_ProgressivoTotale, m_pVerbaliInFatturazione->m_DataAccettazione.Format("%d/%m/%Y"));
        break;
      case VERB_PER_FATTURA:
        str = "Fattura senza verbale";
        break;
      case VERB_PER_NOTACREDITO:
        str = "Nota di credito";
        break;
      }
      n = m_ComboVerbali.AddString(str);
      m_ComboVerbali.SetItemData(n, (DWORD)m_pVerbaliInFatturazione->m_Codice);
    }
  }
  m_ComboVerbali.SetCurSel(0);
  // Disabilito la combo delle categorie
  m_ComboCategorie.EnableWindow(FALSE);
  if(m_lCodiceVerbale != -1)
  {
    // E' stato selezionato un verbale (modifica o cancellazione di un servizio)
    for(n = 0; n < m_ComboVerbali.GetCount(); n++)
    {
      if(m_pVerbaliInFatturazione->m_Codice == (long)m_ComboVerbali.GetItemData(n))
        break;
    }
    if(n < m_ComboVerbali.GetCount())
    {
      m_ComboVerbali.SetCurSel(n);
      if(m_nOperazione == MODIFICA_SERVIZIO)
        m_ComboVerbali.EnableWindow(FALSE);
    }
  }
}


void CServiziFatturaDlg::InitCategorie(void)
{
  long lCodiceCat, lCodiceServ;
  int  m;

  if(m_ComboVerbali.GetCurSel() == -1)
  {
    // Non è selezionato nessun verbale, cancello le edit e svuoto la combo
    m_strDescrizione.Empty();
    m_strNote.Empty();
    m_strSconto.Empty();
    m_strQuantita.Empty();
    m_ComboCategorie.ResetContent();
    return;
  }
  // Riempio le combo delle categorie e dei servizi
  m_pCategorieServiziSet->m_strFilter.Format("Listino = %d AND CATEGORIE.Codice = SERVIZI_LISTINO.Categoria", m_pListinoSet->m_Codice);
  m_pCategorieServiziSet->m_strSort = "CATEGORIE.Codice,SERVIZI_LISTINO.Codice";
  m_pCategorieServiziSet->Requery();
  lCodiceCat = 0;
  m_ComboCategorie.ResetContent();
  m = m_ComboCategorie.AddString("--- Nessuna ---");
  m_ComboCategorie.SetItemData(m, 0);
  for(SET_START(m_pCategorieServiziSet); !m_pCategorieServiziSet->IsEOF(); m_pCategorieServiziSet->MoveNext())
  {
    if(lCodiceCat != m_pCategorieServiziSet->m_CodiceCategoria)
    {
      lCodiceCat = m_pCategorieServiziSet->m_CodiceCategoria;
      m = m_ComboCategorie.AddString(m_pCategorieServiziSet->m_IDCategorie);
      m_ComboCategorie.SetItemData(m, (DWORD)lCodiceCat);
    }
  }
  m_ComboCategorie.SetCurSel(0);
  m_ComboCategorie.EnableWindow();
  // Disabilto la combo dei servizi
  m_ComboServizi.EnableWindow(FALSE);  
  // Abilito le edit
  m_EditDescrizione.EnableWindow();
  m_EditQuantita.EnableWindow();
  m_EditSconto.EnableWindow();
  // Se è stato indicato un servizio, seleziono la categoria e disabilito la combo
  if(m_nOperazione == MODIFICA_SERVIZIO)
  {
    if(m_lCodiceServizioErogato > 0)
    {
      SINCRONIZE(m_pServiziErogati, m_lCodiceServizioErogato);
      lCodiceServ = m_pServiziErogati->m_CodiceServizio;
      if(lCodiceServ > 0)
      {
  			SINCRONIZE(m_pCategorieServiziSet, lCodiceServ);
        for(m = 0; m < m_ComboCategorie.GetCount(); m++)
        {
          if(m_pCategorieServiziSet->m_CodiceCategoria == (long)m_ComboCategorie.GetItemData(m))
            break;
        }
        if(m < m_ComboCategorie.GetCount())
        {
          m_ComboCategorie.SetCurSel(m);
          m_ComboCategorie.EnableWindow(FALSE);
          // Disabilito anche le edit della descrizione e delle note
          m_EditDescrizione.EnableWindow(FALSE);
          m_EditNote.EnableWindow(FALSE);
        }
      }
    }
    else
    {
      m_ComboCategorie.EnableWindow(FALSE);
      // Disabilito anche le edit della descrizione e delle note
      m_EditDescrizione.EnableWindow(FALSE);
      m_EditNote.EnableWindow(FALSE);
    }
  }
}

void CServiziFatturaDlg::InitServizi(void)
{
  int n, m;
  long codiceServizio;
  CString str, strMask;
  double dImporto, dSconto, quantita;
  
  m_strSconto = "0";
  m_strQuantita = "1";
  m_ComboServizi.ResetContent();
  if((n = m_ComboCategorie.GetCurSel()) > 0)
  {
    m_pCategorieServiziSet->m_strFilter.Format("Listino = %d AND CATEGORIE.Codice = %d AND CATEGORIE.Codice = SERVIZI_LISTINO.Categoria", m_pListinoSet->m_Codice, m_ComboCategorie.GetItemData(n));
    m_pCategorieServiziSet->Requery();
    // Riempio la combo dei servizi
    for(SET_START(m_pCategorieServiziSet); !m_pCategorieServiziSet->IsEOF(); m_pCategorieServiziSet->MoveNext())
    {
      m = m_ComboServizi.AddString(m_pCategorieServiziSet->m_ID);
      m_ComboServizi.SetItemData(m, (DWORD)m_pCategorieServiziSet->m_Codice);
    }
    m_ComboServizi.SetCurSel(-1);
    // Abilito la combodei servizi
    m_ComboServizi.EnableWindow();
  }
  else
  {
    m_ComboServizi.EnableWindow(FALSE);
    m_EditDescrizione.EnableWindow();
    m_EditNote.EnableWindow();
  }
  if(m_nOperazione == MODIFICA_SERVIZIO)
  {
    if(m_lCodiceServizioErogato > 0)
    {
      // Sincronizzo il recordset dei servizi erogati
      SINCRONIZE(m_pServiziErogati, m_lCodiceServizioErogato);
      codiceServizio = m_pServiziErogati->m_CodiceServizio;
      if(codiceServizio > 0)
      {
        // Sto modificando un servizio di listino: inizializzo i dati prendendoli dal recordset
        SINCRONIZE(m_pCategorieServiziSet, codiceServizio);
        for(m = 0; m < m_ComboServizi.GetCount(); m++)
        {
          if(m_pCategorieServiziSet->m_Codice == (long)m_ComboServizi.GetItemData(m))
            break;
        }
        m_ComboServizi.SetCurSel(m);
        m_ComboServizi.EnableWindow(FALSE);
        m_strNote = m_pCategorieServiziSet->m_Nome;
      }
      // Sto modificando un servizio non di listino
      m_strDescrizione = m_pServiziErogati->m_Descrizione;
      quantita = m_pServiziErogati->m_Quantita;
      str.Format("%.2f", quantita);
      str.Replace(".", ",");
      m_strQuantita = str;
      if(!m_pServiziErogati->IsFieldNull(&m_pServiziErogati->m_Sconto))
        dSconto = m_pServiziErogati->m_Sconto;
      else
        dSconto = 0;       
      str.Format("%.2f", dSconto);
      str.Replace(".", ",");
      m_strSconto = str;
      m_ComboCategorie.EnableWindow(FALSE);
      m_ComboServizi.EnableWindow(FALSE);
      // Prezzo
      if(!m_pServiziErogati->IsFieldNull(&m_pServiziErogati->m_Prezzo))
      {
        Valuta prezzo(m_pServiziErogati->m_Prezzo);
        str = prezzo.Format();
        // Importo
        if(quantita < 0)
          quantita *= -1;
        dImporto = m_pServiziErogati->m_Prezzo * quantita;
        dImporto = dImporto - (dImporto * dSconto / 100);
      }
      else
      {
        str = "0";
        dImporto = 0;
      }
    }
    // Prezzo
    strMask = m_MskPrezzo.GetMask();
    strMask = strMask.Left(strMask.GetLength() - str.GetLength());
    strMask.Replace("#", m_MskPrezzo.GetPromptChar());
    strMask.Replace(',', '.');
    strMask = strMask + str;
    m_MskPrezzo.SetText(strMask);
    // Importo
    Valuta importo(dImporto);
    str = importo.Format();
    strMask = m_MskImporto.GetMask();
    strMask = strMask.Left(strMask.GetLength() - str.GetLength());
    strMask.Replace("#", m_MskImporto.GetPromptChar());
    strMask.Replace(',', '.');
    strMask = strMask + str;
    m_MskImporto.SetText(strMask);
    m_EditQuantita.EnableWindow();
    m_EditSconto.EnableWindow();
    m_MskImporto.EnableWindow();
  }
  UpdateData(FALSE);
}

void CServiziFatturaDlg::OnCancel() 
{
	if(m_pVerbaliInFatturazione)
  {
    m_pVerbaliInFatturazione->Close();
    delete m_pVerbaliInFatturazione;
  }
  if(m_pServiziErogati)
  {
    m_pServiziErogati->Close();
    delete m_pServiziErogati;
  }
  if(m_pCategorieServiziSet)
  {
    m_pCategorieServiziSet->Close();
    delete m_pCategorieServiziSet;
  }
  if(m_pListinoSet)
  {
    m_pListinoSet->Close();
    delete m_pListinoSet;
  }
	CDialog::OnCancel();
}

void CServiziFatturaDlg::OnOK() 
{
  int n;
  CString str ;

  UpdateData(TRUE);
  CAziendeSet* pAziendeSet = m_pDoc->m_pAziendeSet;
  switch(m_nOperazione)
  {
  case AGGIUNGI_SERVIZIO:
    if((n = m_ComboVerbali.GetCurSel()) == -1)
    {
      AfxMessageBox("Selezionare un verbale in cui inserire il servizio.");
      return;
    }
    if(m_strQuantita.IsEmpty())
    {
      AfxMessageBox("Indicare la quantità.");
      return;
    }
    SINCRONIZE(m_pVerbaliInFatturazione, (long)m_ComboVerbali.GetItemData(n));
    SINCRONIZE(pAziendeSet, m_pVerbaliInFatturazione->m_CodiceAzFattura);
    // Aggiungo il nuovo servizio
    m_pServiziErogati->AddNew();
    m_pServiziErogati->m_Verbale = m_pVerbaliInFatturazione->m_Codice;
    // Prezzo
    str = m_MskPrezzo.GetText();
    str.Remove('.');
    str.TrimLeft(" _");
    str.Replace(',', '.');
    if(str.FindOneOf("0123456789") < 0)
    	m_pServiziErogati->m_Prezzo = 0;
    else
    	m_pServiziErogati->m_Prezzo = atof(str);
    str = m_strSconto;
    str.Replace(",", ".");
    m_pServiziErogati->m_Sconto	= atof(str);
    str = m_strQuantita;
    str.Replace(",", ".");
    m_pServiziErogati->m_Quantita	= atof(str);
    if((n = m_ComboServizi.GetCurSel()) != -1)
    {
      // Ho selezionato un servizio di listino: sincronizzo il recordset
      SINCRONIZE(m_pCategorieServiziSet, (long)m_ComboServizi.GetItemData(n));
      // Prendo codice, descrizione e ID dal listino
    	m_pServiziErogati->m_CodiceServizio	= m_pCategorieServiziSet->m_Codice;
    	m_pServiziErogati->m_Descrizione = m_pCategorieServiziSet->m_Descrizione;
      m_pServiziErogati->m_Nome = m_pCategorieServiziSet->m_Nome;
    	m_pServiziErogati->m_ID_Listino	= m_pCategorieServiziSet->m_ID;
      if(m_lCodiceFattura >= 0)
        m_pServiziErogati->m_Fattura = m_lCodiceFattura;
    }
    else
    {
      // Aggiungo un servizio non di listino
    	m_pServiziErogati->m_CodiceServizio	= 0;
    	m_pServiziErogati->m_Descrizione = m_strDescrizione;
    	m_pServiziErogati->m_ID_Listino	= ID_SERVIZI_NO_LISTINO;
      if(m_lCodiceFattura >= 0)
        m_pServiziErogati->m_Fattura = m_lCodiceFattura;
    }
    // Aggiorno
    m_pServiziErogati->Update();
    m_lCodiceVerbale = m_pVerbaliInFatturazione->m_Codice;
    break;
  case MODIFICA_SERVIZIO:
    SINCRONIZE(pAziendeSet, m_lCodiceAzienda);
    m_pServiziErogati->Edit();
    CString str = m_MskPrezzo.GetText();
  	str.Remove('.');
  	str.TrimLeft(" _");
  	str.Replace(',', '.');
  	if(str.FindOneOf("0123456789") < 0)
  	  m_pServiziErogati->m_Prezzo = 0;
  	else
  	  m_pServiziErogati->m_Prezzo = atof(str);
    str = m_strSconto;
    str.Replace(",", ".");
    m_pServiziErogati->m_Sconto	= atof(str);
    str = m_strQuantita;
    str.Replace(",", ".");
    m_pServiziErogati->m_Quantita	= atof(str);
    m_pServiziErogati->m_Descrizione = m_strDescrizione;
    m_pServiziErogati->Update();
    break;
  }
  m_pServiziErogati->Requery();
	if(m_pVerbaliInFatturazione)
  {
    m_pVerbaliInFatturazione->Close();
    delete m_pVerbaliInFatturazione;
  }
  if(m_pServiziErogati)
  {
    m_pServiziErogati->Close();
    delete m_pServiziErogati;
  }
  if(m_pCategorieServiziSet)
  {
    m_pCategorieServiziSet->Close();
    delete m_pCategorieServiziSet;
  }
  if(m_pListinoSet)
  {
    m_pListinoSet->Close();
    delete m_pListinoSet;
  }
	CDialog::OnOK();
}


void CServiziFatturaDlg::OnSelchangeComboVerbale() 
{
  int n;

  if((n = m_ComboVerbali.GetCurSel()) != -1)
  {
    // Sincronizzo il recordset
    for(SET_START(m_pVerbaliInFatturazione); !m_pVerbaliInFatturazione->IsEOF(); m_pVerbaliInFatturazione->MoveNext())
    {
      if(m_pVerbaliInFatturazione->m_Codice == (long)m_ComboVerbali.GetItemData(n))
        break;
    }

    SINCRONIZE(m_pVerbaliInFatturazione, (long)m_ComboVerbali.GetItemData(n));

    if (m_bListinoGenerale == TRUE)
    {
      SINCRONIZE(m_pListinoSet, (long)m_pVerbaliInFatturazione->m_ListinoGenerale);
    }
    else
    {
      SINCRONIZE(m_pListinoSet, (long)m_pVerbaliInFatturazione->m_ListinoParticolare);
    }

    // Carico le categorie
    InitCategorie();
  }
}

void CServiziFatturaDlg::OnSelchangeComboCategoria() 
{
  InitServizi();
}

void CServiziFatturaDlg::OnSelchangeComboServizio() 
{
  int n;
  CString str, strMask;
  double dPrezzo, dImporto, dSconto, quantita;

  UpdateData();
  m_strDescrizione.Empty();
  m_strNote.Empty();
  if((n = m_ComboServizi.GetCurSel()) != -1)
  {
    // Quando è selezionato un servizio disabilito le edit della descrizione e delle note
    SINCRONIZE(m_pCategorieServiziSet, (long)m_ComboServizi.GetItemData(n));
    m_strDescrizione = m_pCategorieServiziSet->m_Descrizione;
    m_EditDescrizione.EnableWindow(FALSE);
    m_EditNote.EnableWindow(FALSE);
    // Prezzo
    if(!m_pCategorieServiziSet->IsFieldNull(&m_pCategorieServiziSet->m_Prezzo))
      dPrezzo = m_pCategorieServiziSet->m_Prezzo;
    else
      dPrezzo = 0;
    Valuta prezzo(dPrezzo);
    str = prezzo.Format(6);
    strMask = m_MskPrezzo.GetMask();
    strMask = strMask.Left(strMask.GetLength() - str.GetLength());
    strMask.Replace("#", m_MskPrezzo.GetPromptChar());
    strMask.Replace(',', '.');
    strMask = strMask + str;
    m_MskPrezzo.SetText(strMask);
    dSconto = atof(m_strSconto);
    // Importo
    str = m_strQuantita;
    str.Replace(",", ".");
    quantita = atof(str);
    if(quantita < 0)
      quantita *= -1;
    dImporto = dPrezzo * quantita;
    dImporto = dImporto - (dImporto * dSconto / 100);
    Valuta importo(dImporto);
    str = importo.Format(6);
    strMask = m_MskImporto.GetMask();
    strMask = strMask.Left(strMask.GetLength() - str.GetLength());
    strMask.Replace("#", m_MskImporto.GetPromptChar());
    strMask.Replace(',', '.');
    strMask = strMask + str;
    m_MskImporto.SetText(strMask);
  }
  UpdateData(FALSE);
}

BEGIN_EVENTSINK_MAP(CServiziFatturaDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CServiziFatturaDlg)
	ON_EVENT(CServiziFatturaDlg, IDC_MASKEDBOX_IMPORTO, 1 /* Change */, OnChangeMaskedboxImporto, VTS_NONE)
	ON_EVENT(CServiziFatturaDlg, IDC_MASKEDBOX_PREZZO, 1 /* Change */, OnChangeMaskedboxPrezzo, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CServiziFatturaDlg::OnChangeMaskedboxImporto() 
{
  double dSconto, dImporto, dPrezzo, dImportoNonScontato, quantita;
  CString str, strMask;

  if(!m_dImporto)
  {
    str = m_MskImporto.GetText();
  	str.Remove('.');
  	str.TrimLeft(" _");
  	str.Replace(',', '.');
    dImporto = atof(str);
  }
  else
    dImporto = m_dImporto;
  str = m_MskPrezzo.GetText();
	str.Remove('.');
	str.TrimLeft(" _");
	str.Replace(',', '.');
  dPrezzo = atof(str);
  if(dPrezzo && dImporto)
  {
    str = m_strQuantita;
    str.Replace(",", ".");
    quantita = atof(str);
    if(quantita < 0)
      quantita *= -1;
    dImportoNonScontato = dPrezzo * quantita;
    if(m_bChangeSconto)
    {
      dSconto = ((dImportoNonScontato - dImporto) * 100) / dImportoNonScontato; 
      str.Format("%.2f", dSconto);
      str.Replace(".", ",");
      m_strSconto = str;
    }
  }
  UpdateData(FALSE);
}

void CServiziFatturaDlg::OnChangeMaskedboxPrezzo() 
{
  double dSconto, dImporto, dPrezzo, quantita;
  CString str, strMask;
  
  m_bChangeSconto = FALSE;    
  str = m_MskPrezzo.GetText();
	str.Remove('.');
	str.TrimLeft(" _");
	str.Replace(',', '.');
  dPrezzo = atof(str);
  str = m_strSconto;
  str.Replace(",", ".");
  dSconto = atof(str);
  str = m_strQuantita;
  str.Replace(",", ".");    
  quantita = atof(str);
  if(quantita < 0)
    quantita *= -1;
  dImporto = dPrezzo * quantita;
  dImporto = dImporto - (dImporto * dSconto / 100);
  Valuta importo(dImporto);
  str = importo.Format();
  strMask = m_MskImporto.GetMask();
  strMask = strMask.Left(strMask.GetLength() - str.GetLength());
  strMask.Replace("#", m_MskImporto.GetPromptChar());
  strMask.Replace(',', '.');
  strMask = strMask + str;
  m_MskImporto.SetText(strMask);
  m_bChangeSconto = TRUE;    
  UpdateData(FALSE);
}

void CServiziFatturaDlg::OnChangeEditSconto() 
{
  double dSconto, dImporto, dPrezzo;
  CString str, strMask;
  double quantita;
  
	UpdateData(TRUE);
  str = m_strSconto;
  str.Replace(",", ".");
  dSconto = atof(str);
  str = m_MskPrezzo.GetText();
	str.Remove('.');
	str.TrimLeft(" _");
	str.Replace(',', '.');
  dPrezzo = atof(str);
  if(dPrezzo)
  {
    m_bChangeSconto = FALSE;
    str = m_strQuantita;
    str.Replace(",", ".");
    quantita = atof(str);
    if(quantita < 0)
      quantita *= -1;
    dImporto = dPrezzo * quantita;
    dImporto = dImporto - (dImporto * dSconto / 100);
  	Valuta importo(dImporto);
  	str = importo.Format();
    strMask = m_MskImporto.GetMask();
    strMask = strMask.Left(strMask.GetLength() - str.GetLength());
    strMask.Replace("#", m_MskImporto.GetPromptChar());
    strMask.Replace(',', '.');
    strMask = strMask + str;
    m_MskImporto.SetText(strMask);
    m_bChangeSconto = TRUE;
  }
  UpdateData(FALSE);
}

void CServiziFatturaDlg::OnChangeEditQuantita() 
{
	UpdateData();
  double dSconto, dImporto, dPrezzo;
  CString str, strMask;
  double quantita;

  str = m_strQuantita;
  str.Replace(",", ".");
  quantita = atof(str);
  str = m_strSconto;
  str.Replace(",", ".");
  dSconto = atof(str);
  str = m_MskPrezzo.GetText();
	str.Remove('.');
	str.TrimLeft(" _");
	str.Replace(',', '.');
  dPrezzo = atof(str);
  if(dPrezzo)
  {
    m_bChangeSconto = FALSE;    
    if(quantita < 0)
      quantita *= -1;
    dImporto = quantita * dPrezzo;
    dImporto = dImporto - (dImporto * dSconto / 100);
    m_dImporto = dImporto;
  	Valuta importo(dImporto);
  	str = importo.Format();
    strMask = m_MskImporto.GetMask();
    strMask = strMask.Left(strMask.GetLength() - str.GetLength());
    strMask.Replace("#", m_MskImporto.GetPromptChar());
    strMask.Replace(',', '.');
    strMask = strMask + str;
    m_MskImporto.SetText(strMask);
    m_dImporto = 0.;
    m_bChangeSconto = TRUE;    
  }
  UpdateData(FALSE);
}

void CServiziFatturaDlg::OnChangeEditDescrizione() 
{
  UpdateData();
}

void CServiziFatturaDlg::OnCheckListinogenerale() 
{
  UpdateData();
  if(m_bListinoGenerale)
  {
    SINCRONIZE(m_pListinoSet, m_lListinoGenerale);
  }
  else
  {
    SINCRONIZE(m_pListinoSet, m_lListinoParticolare);
  }
  // Cancello le edit e svuoto la combo
  m_strDescrizione.Empty();
  m_strNote.Empty();
  m_strSconto.Empty();
  m_strQuantita.Empty();
  m_ComboCategorie.ResetContent();
  InitVerbali();
  InitCategorie();
  InitServizi();
  UpdateData(FALSE);
}

void CServiziFatturaDlg::InitListino(void)
{
  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
  m_pListinoSet = new CListiniSet(&pApp->m_db);   
  m_pListinoSet->Open();
  if(m_lListinoParticolare != 0)
  {
    m_bListinoGenerale = FALSE;
    // Cerco il listino col codice m_lListinoParticolare
    for(SET_START(m_pListinoSet); !m_pListinoSet->IsEOF(); m_pListinoSet->MoveNext())
    {
      if(m_pListinoSet->m_Codice == m_lListinoParticolare)
        break;
    }
  }
  if(!m_lListinoParticolare || m_pListinoSet->IsEOF())
  {
    // Azzero il codice del listino particolare
    m_lListinoParticolare = 0;
    for(SET_START(m_pListinoSet); !m_pListinoSet->IsEOF(); m_pListinoSet->MoveNext())
    {
      if(m_pListinoSet->m_Codice == m_lListinoGenerale)
        break;
    }
    // Se non l'ho trovato, sincronizzo il listino sul listino generale attualmente attivo
    if(m_pListinoSet->IsEOF())
    {
      m_pListinoSet->Close();
      m_pListinoSet = m_pDoc->m_pListiniInVigoreSet;
      for(SET_START(m_pListinoSet); !m_pListinoSet->IsEOF(); m_pListinoSet->MoveNext())
      {
        if(m_pListinoSet->IsFieldNull(&m_pListinoSet->m_Azienda) || m_pListinoSet->m_Azienda == 0)
        {
          m_lListinoGenerale = m_pListinoSet->m_Codice;
          break;
        }
      }
    }
    m_bListinoGenerale = TRUE;
    SINCRONIZE(m_pListinoSet, m_lListinoGenerale);
  }
}
