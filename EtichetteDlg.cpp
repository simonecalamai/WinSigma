// EtichetteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "EtichetteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define ETICHETTE_X_PAGINA 8

/////////////////////////////////////////////////////////////////////////////
// CEtichetteDlg dialog


CEtichetteDlg::CEtichetteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEtichetteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEtichetteDlg)
	m_bStEtichette = FALSE;
	m_bStReport = FALSE;
	m_strScelti = _T("");
	//}}AFX_DATA_INIT
}


void CEtichetteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEtichetteDlg)
	DDX_Control(pDX, IDC_COMBO_ANNO, m_cmbAnno);
	DDX_Control(pDX, IDOK, m_BtnOK);
	DDX_Control(pDX, IDC_COMBO_PARTENZA, m_ComboPartenza);
	DDX_Check(pDX, IDC_CHECK_ETICHETTE, m_bStEtichette);
	DDX_Check(pDX, IDC_CHECK_REPORT, m_bStReport);
	DDX_Text(pDX, IDC_EDIT_DAL, m_strScelti);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEtichetteDlg, CDialog)
	//{{AFX_MSG_MAP(CEtichetteDlg)
	ON_BN_CLICKED(IDC_CHECK_ETICHETTE, OnCheckEtichette)
	ON_BN_CLICKED(IDC_CHECK_REPORT, OnCheckReport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEtichetteDlg message handlers

void CEtichetteDlg::OnOK() 
{
	UpdateData();
	CWinSigmaApp* pApp				= (CWinSigmaApp*)AfxGetApp();
	CVerbaliSet* pVerbSet			= new CVerbaliSet(&pApp->m_db);
	CAziendeSet* pAziendeSet	= new CAziendeSet(&pApp->m_db);

	// Set del valore di righe da saltare per la stampa delle etichette
	m_nInizioStampa = m_ComboPartenza.GetItemData(m_ComboPartenza.GetCurSel());

	CString str, queryAziende = "Codice = 0 ";

	// reperisco l'anno in corso
  CString csApp("");
  m_cmbAnno.GetWindowText(csApp);
	CTime inizioAnno(atoi(csApp), 1,1,1,1,1,1);
  CTime fineAnno(atoi(csApp), 12,31,1,1,1,1);
	CString queryData;
	CString strIntest, strInd, strNote, strIndReport;
	queryData.Format("DataAccettazione >= '%s' AND DataAccettazione <= '%s'", inizioAnno.Format("%Y-%m-%d"), fineAnno.Format("%Y-%m-%d"));

	if( !CreaQuery() )
	{
		AfxMessageBox("Verificare la conformità dei dati inseriti.");
		return;
	}
		
	//Repeisco i verbali interessati
	pVerbSet->m_strSort = "ProgressivoTotale ASC";
	pVerbSet->m_strFilter.Format("(%s) AND (%s)", queryData, m_strQueryRange);
	pVerbSet->Open();

	// Creo la query per reperire le aziende coinvolte
	while(!pVerbSet->IsEOF())
	{
		str.Format(" OR Codice = %d",pVerbSet->m_CodiceAzFattura);
		queryAziende += str;
		pVerbSet->MoveNext();
	}
	
	// Reperisco le aziende coinvolte
	pAziendeSet->m_strFilter = queryAziende;
	pAziendeSet->Open();


	// In questo modo inserisco i dati in ordine di progressivo del verbale crescente
	for(SET_START(pVerbSet); !pVerbSet->IsEOF(); pVerbSet->MoveNext())
	{
		SINCRONIZE(pAziendeSet, pVerbSet->m_CodiceAzFattura);
		strIndReport = CreaIndirizzo(pAziendeSet);
		
		if( pVerbSet->IsFieldNull(&pVerbSet->m_Destinatario) 
			|| pVerbSet->m_Destinatario.IsEmpty() )
			strInd = strIndReport;
		else
			strInd = pVerbSet->m_Destinatario;

		str = "";
		if(!pVerbSet->IsFieldNull(&pVerbSet->m_NoteSpedizione) )
			str = pVerbSet->m_NoteSpedizione;
		
		strIntest.Format("N.Verb. %d  %s", pVerbSet->m_ProgressivoTotale, str);
		if(pAziendeSet->IsFieldNull(&pAziendeSet->m_Note)
			|| pAziendeSet->m_Note.IsEmpty() )
			strNote = "Non ci sono dati aggiuntivi";
		else
			strNote = pAziendeSet->m_Note;

		if (pVerbSet->m_Spedizione != 0)
			m_paryIndirizzi->Add(strInd);
		
  	str.Format("%s\n%s\n%s", strIntest, strIndReport, strNote);
  	str = "----------------------------------------------------------------------\n" + str;
  	m_paryIndirizziReport->Add(str);
  }
	CDialog::OnOK();
}

CString CEtichetteDlg::CreaIndirizzo(CAziendeSet* pSet)
{
	CString str;
	if(pSet->IsFieldNull(&pSet->m_Indirizzo_Sped) || pSet->m_Indirizzo_Sped.IsEmpty())
		str.Format("%s\n%s\n%s %s %s",pSet->m_RagioneSociale, pSet->m_Indirizzo, pSet->m_CAP, pSet->m_Citta, pSet->m_Provincia);
	else
		str.Format("%s\n%s\n%s %s %s",pSet->m_RagioneSociale, pSet->m_Indirizzo_Sped, pSet->m_CAP_Sped, pSet->m_Citta_Sped, pSet->m_Provincia_Sped);
	return str;
}

void CEtichetteDlg::OnCheckEtichette() 
{
	UpdateData();
	m_ComboPartenza.EnableWindow(m_bStEtichette);
	m_BtnOK.EnableWindow(TRUE);
}



BOOL CEtichetteDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CString str;
	int ind = 0;
	for(int i=0; i<ETICHETTE_X_PAGINA; i++)	
		{
		str.Format("%d",i);
		ind = m_ComboPartenza.AddString(str);
		m_ComboPartenza.SetItemData(ind,i);
		}
	m_ComboPartenza.SetCurSel(0);

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



// La funzione processa la stringa rappresentatne la scelta fatta:
// e costruisce la query che risponde alla scelta, se nel procedimento
// risulta che la stringa non risponde alla formattazione stabilita,
// la funzione si interrompe restituendo false

BOOL CEtichetteDlg::CreaQuery()
{
	int idp, index;
	CStringArray aryScelti;
	char* pChar;
	CString verifica, str, strTemp = m_strScelti;
	pChar = strTemp.GetBuffer(0);
	
	idp = m_strScelti.Find(":",0);


	// Scelto un intervallo di valori.
	if(idp!=-1)
		{
		for(index = 0; index<strTemp.GetLength(); index++)
			{
			if(pChar[index]==':')
				{
				if(str.GetLength()<=0)
					return FALSE;
				aryScelti.Add(str);
				str="";
				}
			else
				{
				verifica = pChar[index];
				if(!(verifica=="0" || verifica=="1" || verifica=="2" || verifica=="3" || verifica=="4" 
					|| verifica=="5" || verifica=="6" || verifica=="7" || verifica=="8" || verifica=="9" ) )
					return FALSE;				
				str += pChar[index]; 
				}
			}

		// Aggiunge il secondo numero
		if(str.GetLength()<=0)
			return FALSE;
		aryScelti.Add(str);

		if(aryScelti.GetSize()!=2)
			return FALSE;

		m_strQueryRange.Format("(ProgressivoTotale >= %s AND ProgressivoTotale <= %s)",aryScelti.GetAt(0) ,aryScelti.GetAt(1) );
		
		}
	else
		{
		// Scelti un insieme di valori.
			str = "";
			for(index = 0; index<strTemp.GetLength(); index++)
				{
				if(pChar[index]==',')
					{
					if(str.GetLength()<=0)
						return FALSE;
					
					aryScelti.Add(str);
					str="";
					}
				else
					{
					verifica = pChar[index];
					if(!(verifica=="0" || verifica=="1" || verifica=="2" || verifica=="3" || verifica=="4" 
						|| verifica=="5" || verifica=="6" || verifica=="7" || verifica=="8" || verifica=="9" ) )
						return FALSE;
					str += pChar[index]; 
					}
				}

			// Aggiunge l'ultimo numero
			if(str.GetLength()<=0)
				return FALSE;
			aryScelti.Add(str);
			
			for(index=0; index<aryScelti.GetSize(); index++)
				{
				if(index==0)
					m_strQueryRange.Format("ProgressivoTotale = %s", aryScelti.GetAt(index));
				else
					{
					str.Format(" OR ProgressivoTotale = %s ",aryScelti.GetAt(index));
					m_strQueryRange += str;
					}
				}
		}

	return TRUE;
}

void CEtichetteDlg::OnCheckReport() 
{
	m_BtnOK.EnableWindow(TRUE);
}
