// StampaEffetti.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "StampaEffetti.h"
#include "Printerpreter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStampaEffetti dialog

CListCtrl   	CStampaEffetti::m_lstEffetti;
int           CStampaEffetti::m_ItemCount;
CStringArray  CStampaEffetti::m_aryIndirizzi;
int           CStampaEffetti::m_nTotaleEffetti;

CStampaEffetti::CStampaEffetti(CWnd* pParent /*=NULL*/)
	: CDialog(CStampaEffetti::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStampaEffetti)
	m_strDa_Fattura = _T("");
	m_strA_Fattura = _T("");
	//}}AFX_DATA_INIT
}


void CStampaEffetti::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStampaEffetti)
	DDX_Control(pDX, IDC_LIST_EFFETTI, m_lstEffetti);
	DDX_Text(pDX, IDC_EDIT_DA_FATTURA, m_strDa_Fattura);
	DDX_Text(pDX, IDC_EDIT_A_FATTURA, m_strA_Fattura);
  DDX_Control(pDX, IDC_COMBO_ANNO, m_cmbAnno);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStampaEffetti, CDialog)
	//{{AFX_MSG_MAP(CStampaEffetti)
	ON_BN_CLICKED(IDC_BUTTON_RICERCA, OnButtonRicerca)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStampaEffetti message handlers

BOOL CStampaEffetti::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	//Definizione delle Style della Lista e delle intestazioni delle colonne
	unsigned long style = m_lstEffetti.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES;
	m_lstEffetti.SetExtendedStyle(style);

	m_lstEffetti.InsertColumn(0,"R.B.",LVCFMT_CENTER, 40, -1);
	m_lstEffetti.InsertColumn(1,"Fatt.",LVCFMT_CENTER, 40, -1);
	m_lstEffetti.InsertColumn(2,"Data fatt.",LVCFMT_CENTER, 70, -1);
	m_lstEffetti.InsertColumn(3,"Partita IVA",LVCFMT_LEFT, 180, -1);
	m_lstEffetti.InsertColumn(4,"Cliente",LVCFMT_LEFT, 180, -1);
	m_lstEffetti.InsertColumn(5,"Importo",LVCFMT_RIGHT, 80, -1);
	m_lstEffetti.InsertColumn(6,"Scadenza",LVCFMT_CENTER, 70 -1);
	m_lstEffetti.InsertColumn(7,"CAB",LVCFMT_LEFT, 50, -1);
	m_lstEffetti.InsertColumn(8,"ABI",LVCFMT_LEFT, 50, -1);
	m_lstEffetti.InsertColumn(9,"Banca d'appoggio",LVCFMT_LEFT, 140, -1);
	m_lstEffetti.DeleteAllItems();

  int startYear = ((CWinSigmaApp*)AfxGetApp())->GetProfileInt(FATTURAZIONE, START_YEAR, CTime::GetCurrentTime().GetYear());
  int endYear = ((CWinSigmaApp*)AfxGetApp())->GetProfileInt(FATTURAZIONE, END_YEAR, CTime::GetCurrentTime().GetYear());
  CString AppYear("");
  for (int y(startYear); y<= endYear; y++)
  {
    AppYear = "";
    AppYear.Format("%d",y);

    m_cmbAnno.AddString(AppYear);
  }
  AppYear = "";
  AppYear.Format("%d",endYear);
  m_cmbAnno.SetWindowText(AppYear);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStampaEffetti::OnButtonRicerca() 
{
	CString msg("");

	m_lstEffetti.DeleteAllItems();
	
	UpdateData(TRUE);
	//Si tolgono in automatico eventuali spazi in cima o in coda
	m_strDa_Fattura.TrimLeft();
	m_strDa_Fattura.TrimRight();
	m_strA_Fattura.TrimLeft();
	m_strA_Fattura.TrimRight();

	UpdateData(FALSE);
	
	if (Congruenza_Dati_Ricerca(&msg) == true)
		Query();
	else
		AfxMessageBox(msg);

	for(int i(0);i<m_lstEffetti.GetItemCount();i++)
		m_lstEffetti.SetCheck(i,TRUE);

}

void CStampaEffetti::Query() 
{
  int    n, count;
	double prezzo;
	CString sql(""), str;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CTime tScadenza;

	//Controllo sulle EditBox per la creazione della stringa SQL
	if (((m_strDa_Fattura == "")||(m_strDa_Fattura.IsEmpty())))
	{
		AfxMessageBox("Il valore del campo 'Da fattura n.' non può essere vuoto.");
		return;
	}

	if (((m_strA_Fattura == "")||(m_strA_Fattura.IsEmpty())) && ((!m_strDa_Fattura.IsEmpty())||(m_strDa_Fattura!="")))
			sql = "Numero >= " + m_strDa_Fattura;

	if ((m_strDa_Fattura != "") && (!m_strDa_Fattura.IsEmpty()) && (m_strA_Fattura != "") && (!m_strA_Fattura.IsEmpty()))
				sql = "(	Numero >= " + m_strDa_Fattura + ") AND (Numero <= " + m_strA_Fattura + ")";

  CString csApp("");
  m_cmbAnno.GetWindowText(csApp);
	CTime inizioAnno(atoi(csApp), 1,1,1,1,1,1);
  CTime fineAnno(atoi(csApp), 12,31,1,1,1,1);

  CString sqlApp("");
  sqlApp.Format(" AND (Data >= '%s') AND (Data <= '%s')", inizioAnno.Format("%Y-%m-%d"), fineAnno.Format("%Y-%m-%d"));
  sql += sqlApp;

  CString msg("");
	if (Congruenza_Dati_Ricerca(&msg) == true)
	{
		fatture					= new CFattureSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
		tipi_pagamento	= new CTipiPagamentoSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
		servizi_erogati = new CServiziErogatiSet(&((CWinSigmaApp*)AfxGetApp())->m_db);
					
		servizi_erogati->m_strFilter.Empty();
		servizi_erogati->Open();
		
		fatture->m_strFilter = sql;
		fatture->Open();
		
		tipi_pagamento->Open();
			
		int indice_riba(0);
		m_aryIndirizzi.RemoveAll();
		while(!fatture->IsEOF())
		{					
			//Calcolo degli effetti in base al TipoPagamento della singola Fattura
			tipi_pagamento->m_strFilter.Format("Codice = %d", fatture->m_TipoPagamento);
			tipi_pagamento->Requery();

			if ((!tipi_pagamento->IsEOF()) && (tipi_pagamento->m_Allineamento >= eScadBonFineMese))
			{
				for(count = 0; count < tipi_pagamento->m_NumRate; count++)
				{
					//Singole parti dell'effetto
					n = m_lstEffetti.GetItemCount();
					
					indice_riba++;
					str.Format("%d",indice_riba);
					m_lstEffetti.InsertItem(n, str);

          tScadenza = pApp->GetScadenza(fatture->m_Data,
					                              tipi_pagamento->m_GiorniPrimaScad + 30 * count,
                                        tipi_pagamento->m_Allineamento);
          m_lstEffetti.SetItemText(n, 6, tScadenza.Format("%d/%m/%y"));

					prezzo = fatture->m_Imponibile;
					Valuta v(count + 1 < tipi_pagamento->m_NumRate ?
					         prezzo / tipi_pagamento->m_NumRate :
                   prezzo - ((prezzo/tipi_pagamento->m_NumRate)*(tipi_pagamento->m_NumRate - 1)));
					m_lstEffetti.SetItemText(n, 5, v.Format());

					
					//Inserimento del Numero Fattura
					str.Format("%d",fatture->m_Numero);
					m_lstEffetti.SetItemText(n, 1, str);

					//Data Fattura
					m_lstEffetti.SetItemText(n, 2, fatture->m_Data.Format("%d/%m/%y"));

					//Banca d'appoggio
					m_lstEffetti.SetItemText(n, 7, fatture->m_CAB);
					m_lstEffetti.SetItemText(n, 8, fatture->m_ABI);
					m_lstEffetti.SetItemText(n, 9, fatture->m_Banca);
									
					//Intestatario
					m_lstEffetti.SetItemText(n, 3, fatture->m_P_IVA);
					m_lstEffetti.SetItemText(n, 4,
																	fatture->m_IDIntestatario + " - " +
																	fatture->m_RagioneSociale + " ");
					str.Format("%s - %s %s (%s)",
					           fatture->m_Indirizzo, fatture->m_CAP, fatture->m_Citta,  fatture->m_Provincia);
					m_aryIndirizzi.Add(str);
				}
			}
			fatture->MoveNext();
		}
		
		servizi_erogati->Close();
		delete servizi_erogati;
		servizi_erogati=NULL;

		tipi_pagamento->Close();
		delete tipi_pagamento;
		tipi_pagamento=NULL;
		
		fatture->Close();
		delete fatture;
		fatture=NULL;
	}
	else
	{
		AfxMessageBox(msg);
	}
}

void CStampaEffetti::OnOK() 
{
	CStringArray strNames, strValues;
	CPrintInterpreter prn;

	if(!prn.PrePrinting())
    return;

  CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

	//Inserisce la data
	strNames.Add("Data");
  strValues.Add(CTime::GetCurrentTime().Format("%d/%m/%Y"));

	prn.SetPage(1);
	m_ItemCount=0;
  m_nTotaleEffetti = 0;
	prn.Print(pApp->GetCurrentDirectory() + "\\Effetti.prn", &strNames, &strValues, NULL, &ScanPerEffetto);	
 
	prn.PostPrinting();

	CDialog::OnOK();
}

BOOL CStampaEffetti::ScanPerEffetto(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
  pFieldNames->RemoveAll();
  pFieldValues->RemoveAll();
  
  // Stampo gli effetti
	CString str;
  double  dimporto;
  
	if(m_ItemCount < m_lstEffetti.GetItemCount())
	{
		while(!m_lstEffetti.GetCheck(m_ItemCount))
			m_ItemCount++;
    
		if(m_lstEffetti.GetCheck(m_ItemCount))
		{
			pFieldNames->Add("Effetto N.");
			str = m_lstEffetti.GetItemText(m_ItemCount, 0);
			pFieldValues->Add(str);

			pFieldNames->Add("Importo");
			str = "€ ";
			str += m_lstEffetti.GetItemText(m_ItemCount, 5);
			pFieldValues->Add(str);
      str = m_lstEffetti.GetItemText(m_ItemCount, 5);
      str.Remove('.');
      str.Replace(",", ".");
      dimporto = atof(str);
      m_nTotaleEffetti += (int)(dimporto * 100 + 0.5);

			pFieldNames->Add("Scadenza");
			str = m_lstEffetti.GetItemText(m_ItemCount, 6);
			pFieldValues->Add(str);

			pFieldNames->Add("CAB");
			str = m_lstEffetti.GetItemText(m_ItemCount, 7);
			pFieldValues->Add(str);

			pFieldNames->Add("ABI");
			str = m_lstEffetti.GetItemText(m_ItemCount, 8);
			pFieldValues->Add(str);

			pFieldNames->Add("Banca");
			str = m_lstEffetti.GetItemText(m_ItemCount, 9);
			pFieldValues->Add(str);

			pFieldNames->Add("PartitaIva");
			str = "P.IVA ";
			str += m_lstEffetti.GetItemText(m_ItemCount, 3);
			pFieldValues->Add(str);

			pFieldNames->Add("Cliente");
			str = m_lstEffetti.GetItemText(m_ItemCount, 4);
			pFieldValues->Add(str);

			pFieldNames->Add("Indirizzo");
			pFieldValues->Add(m_aryIndirizzi[m_ItemCount]);

			pFieldNames->Add("NFattura");
			str = "Fattura n° ";
			str += m_lstEffetti.GetItemText(m_ItemCount, 1);
			pFieldValues->Add(str);

			pFieldNames->Add("DataFattura");
			str = "del ";
			str += m_lstEffetti.GetItemText(m_ItemCount, 2);
			pFieldValues->Add(str);

			pFieldNames->Add("Borda");
			str = "";
			pFieldValues->Add(str);
		}

		m_ItemCount++;
    for(; m_ItemCount < m_lstEffetti.GetItemCount(); m_ItemCount++)
    {
      if(m_lstEffetti.GetCheck(m_ItemCount))
        break;
    }
	}
  else
  {
    // Come ultima voce metto il totale
	  pFieldNames->Add("Importo");
    pFieldValues->Add("Totale");
    pFieldNames->Add("Scadenza");
    Valuta totale((double)m_nTotaleEffetti);
    pFieldValues->Add("€ " + totale.Format(-1, TRUE));
    return FALSE;
  }
  return TRUE;
}

bool CStampaEffetti::Congruenza_Dati_Ricerca(CString* msg)
{
	int congruenza(1);

	UpdateData(TRUE);

	for(int i(0);i<m_strDa_Fattura.GetLength();i++)
		{
			char buf=m_strDa_Fattura.GetAt(i);
			congruenza = strspn(&buf,"0123456789");
			if (congruenza == 0)
			{
					msg->Insert(0,"Il valore del campo 'Da fattura n.' deve essere numerico.");
					return false;
			}
		}

		for(int j(0);j<m_strA_Fattura.GetLength();j++)
		{
			char buf=m_strA_Fattura.GetAt(j);
			congruenza = strspn(&buf,"0123456789");
			if (congruenza == 0)
			{
					msg->Insert(0,"Il valore del campo 'A fattura n.' deve essere numerico.");
					return false;
			}
		}

	return true;
}
