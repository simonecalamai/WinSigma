// TotFatturatoView.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "TotFatturatoView.h"
#include "FattureSerEroVerSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTotFatturatoView dialog
IMPLEMENT_DYNCREATE(CTotFatturatoView, CFormView)

#include "WinSigmaDoc.h"

CTotFatturatoView::CTotFatturatoView()
	: CFormView(CTotFatturatoView::IDD)
{
	//{{AFX_DATA_INIT(CTotFatturatoView)
	m_csAnno = _T("");
	//}}AFX_DATA_INIT
}


void CTotFatturatoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTotFatturatoView)
	DDX_Control(pDX, IDC_COMBO_MESE, m_cmbMese);
	DDX_Control(pDX, IDC_COMBO_ANNO, m_cmbAnno);
	DDX_Control(pDX, IDC_LIST_TOTALI_FATTURATO, m_listTotFatturato);
	DDX_Control(pDX, IDC_BUTTON_CALCOLA, m_btnCalcola);
	DDX_CBString(pDX, IDC_COMBO_ANNO, m_csAnno);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTotFatturatoView, CFormView)
	//{{AFX_MSG_MAP(CTotFatturatoView)
	ON_BN_CLICKED(IDC_BUTTON_CALCOLA, OnButtonCalcola)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTotFatturatoView message handlers

void CTotFatturatoView::OnButtonCalcola() 
{

	double	FattConcessione			= 0;
	double	FattNonConcessione	= 0;
	double	FattGeotecnica			= 0;
	double	ImpPA								= 0;
	double	TotImpPA		  			= 0;

	double TotProveCarico			= 0;
	double TotCongBituminosi	= 0;
	double TotInerti					= 0;
	double TotMonitoraggi		  = 0;
	double TotVarie						= 0;
	double TotGeotNC					= 0;
	double TotLineeVita				= 0;
	double TotIndMurature			= 0;
	double TotIndCLS					= 0;
	double TotMatMetallici		= 0;

	double	AppFC		= 0;
	double	AppFNC 	= 0;
	double	AppFG		= 0;

	int			n = 0;

	CFattureSerEroVerSet* pFattVerSerErog = NULL;
	CFattureSet* pFatturePA = NULL;

	UpdateData();

	// Apertura Recordset Fatture
	pFatturePA	= new CFattureSet(&m_pApp->m_db);

	// Apertura Recordset Fatture/Verbali/ServiziErogati
	pFattVerSerErog	= new CFattureSerEroVerSet(&m_pApp->m_db);
	if(m_cmbMese.GetItemData(m_cmbMese.GetCurSel()) == 0)
	{
		pFatturePA->m_strFilter.Format("(FATTURE.fPA > 0) And (FATTURE.Data >= '%s-01-01') And (FATTURE.Data <= '%s-31-12')", m_csAnno, m_csAnno);
		pFattVerSerErog->m_strFilter.Format("(VERBALI.Fattura = FATTURE.Codice) And (SERVIZI_EROGATI.Verbale = VERBALI.Codice) And (FATTURE.Data >= '%s-01-01') And (FATTURE.Data <= '%s-31-12')", m_csAnno, m_csAnno);
	}
	else
	{
		pFatturePA->m_strFilter.Format("(FATTURE.fPA > 0) And (FATTURE.Data >= '%s-%02d-01') And (FATTURE.Data <= '%s-%02d-31')", m_csAnno, m_cmbMese.GetItemData(m_cmbMese.GetCurSel()) ,m_csAnno, m_cmbMese.GetItemData(m_cmbMese.GetCurSel()));
		pFattVerSerErog->m_strFilter.Format("(VERBALI.Fattura = FATTURE.Codice) And (SERVIZI_EROGATI.Verbale = VERBALI.Codice) And (FATTURE.Data >= '%s-%02d-01') And (FATTURE.Data <= '%s-%02d-31')", m_csAnno, m_cmbMese.GetItemData(m_cmbMese.GetCurSel()) ,m_csAnno, m_cmbMese.GetItemData(m_cmbMese.GetCurSel()));
	}

	pFatturePA->m_strSort = "FATTURE.Data";
	pFatturePA->Open();

	pFattVerSerErog->m_strSort = "VERBALI.Codice";
	pFattVerSerErog->Open();

	AppFC		= 0;
	AppFNC 	= 0;
	AppFG		= 0;

	for(SET_START(pFattVerSerErog); !pFattVerSerErog->IsEOF(); pFattVerSerErog->MoveNext())
	{
			AppFC		= 0;
			AppFNC 	= 0;
			AppFG		= 0;

			// Controlla la tipologia del Verbale
			if(pFattVerSerErog->m_TipoVerbale == VERB_IN_CONCESSIONE)
			{
				double Val = (pFattVerSerErog->m_Prezzo * pFattVerSerErog->m_Quantita) -
										 (((pFattVerSerErog->m_Prezzo * pFattVerSerErog->m_Quantita) * pFattVerSerErog->m_ScontoSevizio) / 100);
				
				if(pFattVerSerErog->m_TipoDocumento == 1) 
				{
					AppFC -= Val;
				}
				else
				{
					AppFC += Val;
				}

				// Se il verbale ha l'urgenza deve essere aggiunta la quota pari al 50% del costo del servizio
				if(pFattVerSerErog->m_VuoiUrgenza == 1)
					AppFC += Val/2;
			}
			else if (
							(pFattVerSerErog->m_TipoVerbale == VERB_NON_IN_CONCESSIONE)		|| 
							(pFattVerSerErog->m_TipoVerbale == VERB_NC_PROVE_DI_CARICO)		||
							(pFattVerSerErog->m_TipoVerbale == VERB_NC_CONGL_BITUMINOSI)	||
							(pFattVerSerErog->m_TipoVerbale == VERB_NC_INERTI)						||
							(pFattVerSerErog->m_TipoVerbale == VERB_NC_MONITORAGGI)				||
							(pFattVerSerErog->m_TipoVerbale == VERB_NC_VARIE)							||
							(pFattVerSerErog->m_TipoVerbale == VERB_NC_GEOTECNICA)				||
							(pFattVerSerErog->m_TipoVerbale == VERB_NC_LINEE_VITA)				||
							(pFattVerSerErog->m_TipoVerbale == VERB_NC_INDAGINI_MURATURE)	||
							(pFattVerSerErog->m_TipoVerbale == VERB_NC_INDAGINI_CLS)			||
							(pFattVerSerErog->m_TipoVerbale == VERB_NC_MAT_METALLICI)
							)
			{
				double Val = (pFattVerSerErog->m_Prezzo * pFattVerSerErog->m_Quantita) -
										 (((pFattVerSerErog->m_Prezzo * pFattVerSerErog->m_Quantita) * pFattVerSerErog->m_ScontoSevizio) / 100);
				
				if(pFattVerSerErog->m_TipoDocumento == 1) 
				{
					AppFNC -= Val;
				}
				else
				{
					AppFNC += Val;
				}

				// Se il verbale ha l'urgenza deve essere aggiunta la quota pari al 50% del costo del servizio
				if(pFattVerSerErog->m_VuoiUrgenza == 1)
						AppFNC += Val/2;
			}
			else if (pFattVerSerErog->m_TipoVerbale == VERB_GEOLOGIA)
			{
				double Val = (pFattVerSerErog->m_Prezzo * pFattVerSerErog->m_Quantita) -
										 (((pFattVerSerErog->m_Prezzo * pFattVerSerErog->m_Quantita) * pFattVerSerErog->m_ScontoSevizio) / 100); 
				if(pFattVerSerErog->m_TipoDocumento == 1) 
				{
					AppFG -= Val;
				}
				else
				{
					AppFG += Val;
				}
				
				// Se il verbale ha l'urgenza deve essere aggiunta la quota pari al 50% del costo del servizio
				if(pFattVerSerErog->m_VuoiUrgenza == 1)
					AppFG += Val/2;
			}
			else
			{
				double Val = (pFattVerSerErog->m_Prezzo * pFattVerSerErog->m_Quantita) -
										 (((pFattVerSerErog->m_Prezzo * pFattVerSerErog->m_Quantita) * pFattVerSerErog->m_ScontoSevizio) / 100);
				if(pFattVerSerErog->m_TipoDocumento == 1) 
				{
					AppFNC -= Val;
				}
				else
				{
					AppFNC += Val;
				}

				// Se il verbale ha l'urgenza deve essere aggiunta la quota pari al 50% del costo del servizio
				if(pFattVerSerErog->m_VuoiUrgenza == 1)
					AppFNC += Val/2;
			}

			// Spese per le spedizioni
/*			if(pFattVerSerErog->m_Spese > 0)
			{
				if(AppFC)
					AppFC		+= pFattVerSerErog->m_Spese;
				else if(AppFNC) 
					AppFNC	+= pFattVerSerErog->m_Spese;
				else if(AppFG)
					AppFG		+= pFattVerSerErog->m_Spese;
			}
*/
			// Applica lo sconto alla fattura
			if(pFattVerSerErog->m_Sconto > 0)
			{
				AppFC		-= ((AppFC  * pFattVerSerErog->m_Sconto) / 100);
				AppFNC	-= ((AppFNC * pFattVerSerErog->m_Sconto) / 100);
				AppFG		-= ((AppFG  * pFattVerSerErog->m_Sconto) / 100);
			}

#if 0
			// Toglie l'eventuale ritenuta d'acconto
			if(pFattVerSerErog->m_RitenutaAcconto > 0)
			{		
				if(AppFC)
					AppFC		-= ((AppFC  * pFattVerSerErog->m_RitenutaAcconto) / 100);
				else if(AppFNC) 
					AppFNC	-= ((AppFNC * pFattVerSerErog->m_RitenutaAcconto) / 100);
				else if(AppFG)
					AppFG		-= ((AppFG  * pFattVerSerErog->m_RitenutaAcconto) / 100);
			}
#endif

			FattConcessione			+= AppFC;
			FattNonConcessione	+= AppFNC;
			FattGeotecnica			+= AppFG;

			if(AppFNC > 0)
			{
				// Totali per sottocategoria di verbale non in concessione
				if(pFattVerSerErog->m_TipoVerbale == VERB_NC_PROVE_DI_CARICO)
					TotProveCarico += AppFNC;
				else if(pFattVerSerErog->m_TipoVerbale == VERB_NC_CONGL_BITUMINOSI)
					TotCongBituminosi += AppFNC;
				else if(pFattVerSerErog->m_TipoVerbale == VERB_NC_INERTI)
					TotInerti += AppFNC;
				else if(pFattVerSerErog->m_TipoVerbale == VERB_NC_MONITORAGGI)
					TotMonitoraggi += AppFNC;
				else if(pFattVerSerErog->m_TipoVerbale == VERB_NC_VARIE)
					TotVarie += AppFNC;
				else if(pFattVerSerErog->m_TipoVerbale == VERB_NC_GEOTECNICA)
					TotGeotNC += AppFNC;
				else if(pFattVerSerErog->m_TipoVerbale == VERB_NC_LINEE_VITA)
					TotLineeVita += AppFNC;
				else if(pFattVerSerErog->m_TipoVerbale == VERB_NC_INDAGINI_MURATURE)
					TotIndMurature += AppFNC;
				else if(pFattVerSerErog->m_TipoVerbale == VERB_NC_INDAGINI_CLS)
					TotIndCLS += AppFNC;
				else if(pFattVerSerErog->m_TipoVerbale == VERB_NC_MAT_METALLICI)
					TotMatMetallici += AppFNC;
			}
	}

	// imponibile per Pubblica Amministrazione (PA)
	for(SET_START(pFatturePA); !pFatturePA->IsEOF(); pFatturePA->MoveNext())
	{
		if(pFatturePA->m_PA > 0)
		{
//			ImpPA += pFatturePA->m_Imponibile;
			ImpPA = (100 * pFatturePA->m_Imponibile) / (100 + pFatturePA->m_Aliquota);
			TotImpPA += ImpPA;
		}
	}

	if(pFatturePA)
	{
		pFatturePA->Close();
		delete pFatturePA;
	}

	if(pFattVerSerErog)
	{
		pFattVerSerErog->Close();
		delete pFattVerSerErog;
	}

	// Cancella tutti gli elementi presenti nella lista
	m_listTotFatturato.DeleteAllItems();

	// Inserisce gli elementi nella lista
	CString app("");

	n = m_listTotFatturato.InsertItem(n, "");
	app.Format("PC = %.2f", TotProveCarico);
  m_listTotFatturato.SetItemText(n, 2, app);
	
	n = m_listTotFatturato.InsertItem(n, "");
	app.Format("CB = %.2f", TotCongBituminosi);
  m_listTotFatturato.SetItemText(n, 2, app);
	
	n = m_listTotFatturato.InsertItem(n, "");
	app.Format("I  = %.2f", TotInerti);
  m_listTotFatturato.SetItemText(n, 2, app);
	
	n = m_listTotFatturato.InsertItem(n, "");
	app.Format("MO = %.2f", TotMonitoraggi);
  m_listTotFatturato.SetItemText(n, 2, app);

	// add s.c. 14.01.2019
	n = m_listTotFatturato.InsertItem(n, "");
	app.Format("LV = %.2f", TotLineeVita);
  m_listTotFatturato.SetItemText(n, 2, app);

	n = m_listTotFatturato.InsertItem(n, "");
	app.Format("IM = %.2f", TotIndMurature);
  m_listTotFatturato.SetItemText(n, 2, app);

	n = m_listTotFatturato.InsertItem(n, "");
	app.Format("IC = %.2f", TotIndCLS);
  m_listTotFatturato.SetItemText(n, 2, app);

	n = m_listTotFatturato.InsertItem(n, "");
	app.Format("MM = %.2f", TotMatMetallici);
  m_listTotFatturato.SetItemText(n, 2, app);
	// fine add s.c. 14.01.2019

	n = m_listTotFatturato.InsertItem(n, "");
	app.Format("V  = %.2f", TotVarie);
  m_listTotFatturato.SetItemText(n, 2, app);

	n = m_listTotFatturato.InsertItem(n, "");
	app.Format("Geo NC  = %.2f", TotGeotNC);
  m_listTotFatturato.SetItemText(n, 2, app);

	app.Format("%.2f", FattConcessione + FattNonConcessione + FattGeotecnica);
	n = m_listTotFatturato.InsertItem(n, app);

	app.Format("%.2f", FattConcessione);
  m_listTotFatturato.SetItemText(n, 1, app);

	app.Format("%.2f", FattNonConcessione);
  m_listTotFatturato.SetItemText(n, 2, app);

	app.Format("%.2f", FattGeotecnica);
	m_listTotFatturato.SetItemText(n, 3, app);

	app.Format("%.2f", TotImpPA);
	m_listTotFatturato.SetItemText(n, 4, app);
}

void CTotFatturatoView::OnInitialUpdate() 
{
	int n				= 0;
	int year		= 0;
	int minAnno = 0;
	int maxAnno = 0;

	DWORD style;

	CFormView::OnInitialUpdate();

	if(!(m_pApp = ((CWinSigmaApp*)AfxGetApp())))
		return;
	
  // Inizializza la lista dei servizi e quella del report
  style = m_listTotFatturato.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE;
	m_listTotFatturato.SetExtendedStyle(style);
  m_listTotFatturato.InsertColumn(0, "Imponibile Totale", LVCFMT_LEFT, 130, -1);
	m_listTotFatturato.InsertColumn(1, "Imp. prove in concessione", LVCFMT_LEFT, 140, -1);
	m_listTotFatturato.InsertColumn(2, "Imp. prove non in concessione", LVCFMT_LEFT, 160, -1);
	m_listTotFatturato.InsertColumn(3, "Imp. prove geotecnica", LVCFMT_LEFT, 140, -1);
	m_listTotFatturato.InsertColumn(4, "Imponibile PA", LVCFMT_LEFT, 140, -1);

	// Recupera gli anni di validità dei listini per le ricerche dei servizi erogati
	CListiniSet*	pListiniSet;
	pListiniSet = new CListiniSet(&m_pApp->m_db);
  pListiniSet->m_strFilter = "Inizio is not null";
	pListiniSet->m_strSort = "Inizio";
	pListiniSet->Open();
	
	// Caricamento degli anni nella combo
	// Prende dalle date di validità dei listini l'anno minimo e quello massimo
	if (!pListiniSet->IsEOF())
	{
		minAnno = pListiniSet->m_Inizio.GetYear();
		for(SET_START(pListiniSet); !pListiniSet->IsEOF(); pListiniSet->MoveNext());
		maxAnno = pListiniSet->m_Fine.GetYear();
	}

/*
	maxAnno++;
	for (int i = minAnno; i < maxAnno; i++)
	{
		CString Anno("");
		Anno.Format("%d", i);
		m_cmbAnno.InsertString(n, Anno);
		m_cmbAnno.SetItemData(n, i);
    n++;
	}
	// Seleziona il primo elemento della combobox
	m_cmbAnno.SetCurSel(0);
*/
	for (int i = maxAnno; i >= minAnno; i--)
	{
		CString Anno("");
		Anno.Format("%d", i);
		m_cmbAnno.InsertString(n, Anno);
		m_cmbAnno.SetItemData(n, i);
    n++;
	}
	CTime t = CTime::GetCurrentTime();
	CString curYear =  "";
	curYear.Format("%d", t.GetYear());
	m_cmbAnno.SelectString(0, curYear);
	
	// Chiusura recordSet Listini
  if(pListiniSet)
  {
  	pListiniSet->Close();
  	delete pListiniSet;
  }

	// Popola la combo dei mesi
	m_cmbMese.InsertString(0, "Tutti");
	m_cmbMese.SetItemData(0, 0);

	m_cmbMese.InsertString(1, "Gennaio");
	m_cmbMese.SetItemData(1, 1);

	m_cmbMese.InsertString(2, "Febbraio");
	m_cmbMese.SetItemData(2, 2);

	m_cmbMese.InsertString(3, "Marzo");
	m_cmbMese.SetItemData(3, 3);

	m_cmbMese.InsertString(4, "Aprile");
	m_cmbMese.SetItemData(4, 4);

	m_cmbMese.InsertString(5, "Maggio");
	m_cmbMese.SetItemData(5, 5);

	m_cmbMese.InsertString(6, "Giugno");
	m_cmbMese.SetItemData(6, 6);

	m_cmbMese.InsertString(7, "Luglio");
	m_cmbMese.SetItemData(7, 7);

	m_cmbMese.InsertString(8, "Agosto");
	m_cmbMese.SetItemData(8, 8);

	m_cmbMese.InsertString(9, "Settembre");
	m_cmbMese.SetItemData(9, 9);

	m_cmbMese.InsertString(10, "Ottobre");
	m_cmbMese.SetItemData(10, 10);

	m_cmbMese.InsertString(11, "Novembre");
	m_cmbMese.SetItemData(11, 11);

	m_cmbMese.InsertString(12, "Dicembre");
	m_cmbMese.SetItemData(12, 12);

	// Seleziona il primo elemento della combobox
	m_cmbMese.SetCurSel(0);
}
