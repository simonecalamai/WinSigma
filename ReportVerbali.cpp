// ReportVerbali.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "ReportVerbali.h"
#include "Printerpreter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Definizione dei membri statici
CStringArray		CReportVerbali::m_aryDatiStampa;
int							CReportVerbali::m_nIndex;


// Definizione di costatnti
#define FILE_STAMPA			".\\ReportVerbali.prn"
#define COL_NUMERO					0 
#define COL_DATA						1
#define COL_CANTIERE				2
#define COL_FATTURE					3
#define COL_MATERIALE				4

#define NUM_RIGHE_X_PAGINA	30


/////////////////////////////////////////////////////////////////////////////
// CReportVerbali dialog


CReportVerbali::CReportVerbali(CWnd* pParent /*=NULL*/)
	: CDialog(CReportVerbali::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportVerbali)
	m_DataAl = 0;
	m_DataDal = 0;
	m_strRagioneSociale = _T("");
	//}}AFX_DATA_INIT
}


void CReportVerbali::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportVerbali)
	DDX_Control(pDX, IDC_BUTTON_CERCA, m_BtnCerca);
	DDX_Control(pDX, IDC_LIST_SERVIZI, m_ListaVerbali);
	DDX_Control(pDX, IDC_BUTTON_STAMPA, m_BtnStampa);
	DDX_Control(pDX, IDC_DATE_AL, m_DataCtrAl);
	DDX_Control(pDX, IDC_DATE_DAL, m_DataCtrDal);
	DDX_DateTimeCtrl(pDX, IDC_DATE_AL, m_DataAl);
	DDX_DateTimeCtrl(pDX, IDC_DATE_DAL, m_DataDal);
	DDX_Text(pDX, IDC_EDIT_RAGIONE_SOCIALE, m_strRagioneSociale);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportVerbali, CDialog)
	//{{AFX_MSG_MAP(CReportVerbali)
	ON_BN_CLICKED(IDC_BUTTON_CERCA, OnButtonCerca)
	ON_BN_CLICKED(IDC_BUTTON_STAMPA, OnButtonStampa)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportVerbali message handlers

BOOL CReportVerbali::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	m_pFattureSet = new CFattureSet(&pApp->m_db);
	m_pVerbaliSet = new CVerbaliSet(&pApp->m_db);
	m_pServiziErogatiSet = new CServiziErogatiSet(&pApp->m_db);

	DWORD style;
  
  // Lista dei verbali
  style = m_ListaVerbali.GetExtendedStyle();
  style |= LVS_EX_GRIDLINES | LVS_EX_ONECLICKACTIVATE | LVS_EX_FULLROWSELECT;
	m_ListaVerbali.SetExtendedStyle(style);
  m_ListaVerbali.InsertColumn(COL_NUMERO, "Numero", LVCFMT_CENTER, 80, -1);
	m_ListaVerbali.InsertColumn(COL_DATA, "Data", LVCFMT_CENTER, 70, -1);
	m_ListaVerbali.InsertColumn(COL_CANTIERE, "Cantiere", LVCFMT_LEFT, 350, -1);
	m_ListaVerbali.InsertColumn(COL_FATTURE, "Fattura", LVCFMT_LEFT, 100, -1);
	m_ListaVerbali.InsertColumn(COL_MATERIALE, "Materiale consegnato", LVCFMT_LEFT, 400, -1);

	m_DataAl = CTime::GetCurrentTime();
	m_DataDal = CTime(m_DataAl.GetYear(), 1, 1, 1, 1, 1);
	m_strRagioneSociale.Format("%s - (ID: %s)", m_pAziendeSet->m_RagioneSociale, m_pAziendeSet->m_ID);
	UpdateData(FALSE);
	
	return TRUE;  
}

void CReportVerbali::OnButtonCerca() 
{
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	UpdateData();
	m_ListaVerbali.DeleteAllItems();
	CString str, strTemp, queryFatture, queryIntestatario, queryVerbali, queryData;

	queryData.Format("DataAccettazione >= '%s' AND DataAccettazione <= '%s'", m_DataDal.Format("%Y%m%d"), m_DataAl.Format("%Y%m%d") );
	queryIntestatario.Format("IntestatarioFattura = %d or IntestatarioCertificato = %d or ImpresaRichiedente = %d", m_pAziendeSet->m_Codice, m_pAziendeSet->m_Codice, m_pAziendeSet->m_Codice);
	queryVerbali.Format("%s AND (%s)", queryData, queryIntestatario);
	m_pVerbaliSet->m_strFilter = queryVerbali;
	
	if(m_pVerbaliSet->IsOpen())
		m_pVerbaliSet->Requery();
	else
		m_pVerbaliSet->Open();
	int n = 0;

	m_BtnStampa.EnableWindow(!m_pVerbaliSet->IsBOF());
	
	for(; !m_pVerbaliSet->IsEOF(); m_pVerbaliSet->MoveNext())
		{
		str.Format("%d/%d",m_pVerbaliSet->m_ProgressivoParziale, m_pVerbaliSet->m_ProgressivoTotale);
		n = m_ListaVerbali.InsertItem(n, str);
		str = m_pVerbaliSet->m_DataAccettazione.Format("%d/%m/%Y");
		m_ListaVerbali.SetItemText(n, COL_DATA, str);

		str = m_pVerbaliSet->m_Cantiere;
		str.Replace("\r\n","  ");
		m_ListaVerbali.SetItemText(n, COL_CANTIERE, str);


    // Cerca le fatture
    if (m_pVerbaliSet->m_NumeroFattura !=  0)
    {
      str.Empty();
		  m_pFattureSet->m_strFilter.Format("Codice = %d", m_pVerbaliSet->m_NumeroFattura);
		  if(m_pFattureSet->IsOpen())
			  m_pFattureSet->Requery();
		  else
			  m_pFattureSet->Open();

      
      for(; !m_pFattureSet->IsEOF(); m_pFattureSet->MoveNext())
			{
			  strTemp.Format("%d", m_pFattureSet->m_Numero);
			  if(str.IsEmpty())
				  str = strTemp;
			  else
				  str = str + ", " + strTemp;
			}
    }
    else
			str = "non fatturato";



/*		
		// ---------------- Ricerca dei servizi erogati ------------------ //

		queryFatture = "Codice = -1";
		m_pServiziErogatiSet->m_strFilter.Format("Verbale = %d",m_pVerbaliSet->m_Codice);
    m_pServiziErogatiSet->m_strSort = "Fattura";
		if(m_pServiziErogatiSet->IsOpen())
			m_pServiziErogatiSet->Requery();
		else
			m_pServiziErogatiSet->Open();
		for(long nFattura = -1; !m_pServiziErogatiSet->IsEOF(); m_pServiziErogatiSet->MoveNext())
		{
      if(nFattura != m_pServiziErogatiSet->m_Fattura)
      {  
			  strTemp.Format("Codice = %d", m_pServiziErogatiSet->m_Fattura);
			  queryFatture = queryFatture + " OR " + strTemp;
      }
      nFattura = m_pServiziErogatiSet->m_Fattura;
		}

			// ------ Ricerca delle fatture legate ai servizi erogati ------ //
		str.Empty();
		m_pFattureSet->m_strFilter = queryFatture;
		if(m_pFattureSet->IsOpen())
			m_pFattureSet->Requery();
		else
			m_pFattureSet->Open();
		
		if(m_pFattureSet->IsEOF())
			str = "non fatturato";
			
		for(; !m_pFattureSet->IsEOF(); m_pFattureSet->MoveNext())
			{
			strTemp.Format("%d", m_pFattureSet->m_Numero);
			if(str.IsEmpty())
				str = strTemp;
			else
				str = str + ", " + strTemp;
			}
		
		// --------------------------------------------------------------- //
*/

		
		m_ListaVerbali.SetItemText(n, COL_FATTURE, str);
		str = m_pVerbaliSet->m_DescrizioneMateriale;
		m_ListaVerbali.SetItemText(n, COL_MATERIALE, str);
		n++;

		}
}

void CReportVerbali::OnButtonStampa() 
{
	StampaReport();
}


void CReportVerbali::StampaReport()
{
	CPrintInterpreter prnInterpreter;
	int righe = 0;
	if((righe = m_ListaVerbali.GetItemCount()) <1 )
	{
		AfxMessageBox("Non sono presenti dati da stampare.");
		return;
	}
	if(prnInterpreter.PrePrinting())
	{
		SetCursor(LoadCursor(NULL, IDC_WAIT));
		CString str;
		CStringArray fieldNames, fieldValues;

		// Riempimento dei campi relativi all'azienda
		RiempiCampi( &fieldNames, &fieldValues );

		// Calcolo del numero delle pagine previste in base al numero delle righe da stampare
		fieldNames.Add("pagine");
		int numPag = ( righe / NUM_RIGHE_X_PAGINA ) + 1;
		str.Format("%d",numPag);
		fieldValues.Add(str);

		// Riempimento dell'array contenitore dei tabFields
		m_nIndex = 0;
		m_aryDatiStampa.RemoveAll();
		for(int i = 0; i < righe; i++)
		{
			str = m_ListaVerbali.GetItemText(i, COL_NUMERO);
			m_aryDatiStampa.Add(str);
			str = m_ListaVerbali.GetItemText(i, COL_DATA);
			m_aryDatiStampa.Add(str);
			str = m_ListaVerbali.GetItemText(i, COL_CANTIERE);
			m_aryDatiStampa.Add(str);
			str = m_ListaVerbali.GetItemText(i, COL_FATTURE);
			m_aryDatiStampa.Add(str);
			str = m_ListaVerbali.GetItemText(i, COL_MATERIALE);
			m_aryDatiStampa.Add(str);
		}
		// - - - - - - - - - - - - - - - - - - - - - - - - //
		
		prnInterpreter.Print(FILE_STAMPA, &fieldNames, &fieldValues, NULL, NULL, &ScanVerbali );
		prnInterpreter.PostPrinting();
	}

}

BOOL CReportVerbali::ScanVerbali(CStringArray* pFieldNames, CStringArray* pFieldValues)
{	
	if(m_nIndex >= m_aryDatiStampa.GetSize())
		return FALSE;

	CString str, strNome;
	pFieldNames->RemoveAll();
	pFieldValues->RemoveAll();
	
	pFieldNames->Add("numero");
	str = m_aryDatiStampa.GetAt(m_nIndex);
	pFieldValues->Add(str);
	m_nIndex++;

	pFieldNames->Add("data");
	str = m_aryDatiStampa.GetAt(m_nIndex);
	pFieldValues->Add(str);
	m_nIndex++;

	strNome = "cantiere";
	str = m_aryDatiStampa.GetAt(m_nIndex);
	if(str.GetLength()>75)
		strNome = "cantiereLungo";

	pFieldNames->Add(strNome);
	pFieldValues->Add(str);
	m_nIndex++;

	pFieldNames->Add("fatture");
	str = m_aryDatiStampa.GetAt(m_nIndex);
	pFieldValues->Add(str);
	m_nIndex++;

	strNome = "materiale";
	str = m_aryDatiStampa.GetAt(m_nIndex);
	if(str.GetLength() > 90)
		strNome = "materialeLungo";
	pFieldNames->Add(strNome);
	pFieldValues->Add(str);

	
	m_nIndex++;
	
	if(m_nIndex >= m_aryDatiStampa.GetSize())
		return FALSE;

	return TRUE;
}


void CReportVerbali::OnOK() 
{
	delete m_pFattureSet;
	delete m_pVerbaliSet;

	delete m_pServiziErogatiSet;
	
	CDialog::OnOK();
}




void CReportVerbali::RiempiCampi(CStringArray* pFieldNames, CStringArray* pFieldValues)
{
	CString str;
	
	pFieldNames->Add("periodo");
	str.Format("dal %s al %s", m_DataDal.Format("%d/%m/%Y"), m_DataAl.Format("%d/%m/%Y"));
	pFieldValues->Add(str);
	
	pFieldNames->Add("ragSociale");
	str.Format("(%s) %s", m_pAziendeSet->m_ID ,m_pAziendeSet->m_RagioneSociale);
	pFieldValues->Add(str);
	
	pFieldNames->Add("piva");
	if(m_pAziendeSet->m_Privato)
			str.Format("C. fiscale: %s", m_pAziendeSet->m_CodiceFiscale);
		else
			str.Format("P. IVA: %s", m_pAziendeSet->m_P_IVA);
	pFieldValues->Add(str);
	
	pFieldNames->Add("indirizzo");
	str.Format("%s",m_pAziendeSet->m_Indirizzo);
	pFieldValues->Add(str);

	pFieldNames->Add("citta");
	str.Format("%s (%s)", m_pAziendeSet->m_Citta, m_pAziendeSet->m_Provincia);
	pFieldValues->Add(str);

	pFieldNames->Add("cap");
	str.Format("%s",m_pAziendeSet->m_CAP);
	pFieldValues->Add(str);
	if(!m_pAziendeSet->IsFieldNull(&m_pAziendeSet->m_Indirizzo_Sped))
		{
		pFieldNames->Add("indirizzoSped");
		str.Format("%s",m_pAziendeSet->m_Indirizzo_Sped);
		pFieldValues->Add(str);

		pFieldNames->Add("cittaSped");
		str.Format("%s (%s)", m_pAziendeSet->m_Citta_Sped, m_pAziendeSet->m_Provincia_Sped);
		pFieldValues->Add(str);

		pFieldNames->Add("capSped");
		str.Format("%s",m_pAziendeSet->m_CAP_Sped);
		pFieldValues->Add(str);
		}
}
