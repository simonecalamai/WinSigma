// EsportazioneCSVView.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "EsportazioneCSVView.h"
#include "SerieProviniset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEsportazioneCSVView

IMPLEMENT_DYNCREATE(CEsportazioneCSVView, CFormView)

CEsportazioneCSVView::CEsportazioneCSVView()
	: CFormView(CEsportazioneCSVView::IDD)
{
	//{{AFX_DATA_INIT(CEsportazioneCSVView)
	m_tDa = 0;
	m_tA = 0;
	//}}AFX_DATA_INIT
	m_CSVLine.Empty();
	m_pDati = NULL;
}

CEsportazioneCSVView::~CEsportazioneCSVView()
{
}

void CEsportazioneCSVView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEsportazioneCSVView)
	DDX_Control(pDX, IDC_DATETIMEPICKER_A, m_ctrlA);
	DDX_Control(pDX, IDC_DATETIMEPICKER_DA, m_ctrlDa);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DA, m_tDa);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_A, m_tA);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEsportazioneCSVView, CFormView)
	//{{AFX_MSG_MAP(CEsportazioneCSVView)
	ON_BN_CLICKED(IDOK, OnEsporta)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEsportazioneCSVView diagnostics

#ifdef _DEBUG
void CEsportazioneCSVView::AssertValid() const
{
	CFormView::AssertValid();
}

void CEsportazioneCSVView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEsportazioneCSVView message handlers

void CEsportazioneCSVView::OnEsporta() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgFile(FALSE,NULL,"export.csv",OFN_ENABLESIZING|OFN_EXPLORER|OFN_FILEMUSTEXIST,"CSV (*.csv)|*.csv|All Files (*.*)|*.*||",this);
	if (dlgFile.DoModal() == IDOK)
	{

		Query();

		CFile cvsFile;
		cvsFile.Open(dlgFile.GetFileName(),CFile::modeCreate|CFile::modeWrite);

		cvsFile.Write(m_CSVLine, m_CSVLine.GetLength());

		cvsFile.Close();
	}
}

void CEsportazioneCSVView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CTime t;
	m_ctrlDa.SetTime(&t.GetCurrentTime());
	m_ctrlA.SetTime(&t.GetCurrentTime());
}

#define CSV_HEADER "Data;Sigla;Diametro;Diam. Eff.;Snervamento;Rottura;Allungamento;Esito;Aderenza;Fornitore;B/R\r\n"
#define PROVIDER	"Fornitore"
void CEsportazioneCSVView::Query()
{
	CString appStr;
	UpdateData(TRUE);

	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CSerieProviniSet* pSerieProvini = new CSerieProviniSet(&pApp->m_db);
	pSerieProvini->m_strFilter.Format("(PROVINI.Serie = SERIE.Codice) AND (SERIE.Certificato > 0) AND (DataPrelievo >= '%d-%d-%d') AND (DataPrelievo <= '%d-%d-%d')", 
											m_tDa.GetYear(), m_tDa.GetMonth(), m_tDa.GetDay(),
											m_tA.GetYear(), m_tA.GetMonth(), m_tA.GetDay()
											);
	pSerieProvini->Open();

	m_CSVLine.Format(CSV_HEADER);
	// Cicla il risultato della query	
	for(SET_START(pSerieProvini); !pSerieProvini->IsEOF(); pSerieProvini->MoveNext())
	{
		if(pSerieProvini->m_TipoCertificato == 13)
		{
			appStr.Empty();
			m_pDati = (dati*)pSerieProvini->m_Risultati.GetData();
			// Data
			m_CSVLine.Insert(m_CSVLine.GetLength(), pSerieProvini->m_DataPrelievo.Format("%d/%m/%y;"));
			// Provino (Sigla Fornitore)
			appStr  = pSerieProvini->m_SiglaFornitore;
			int pos =  appStr.Find(PROVIDER);
			if(pos != -1)
			{
				appStr.Delete(pos, appStr.GetLength() - pos);
			}
			appStr.Insert(appStr.GetLength(), ";");
			m_CSVLine.Insert(m_CSVLine.GetLength(), appStr);

			// Diametro
			appStr.Format("%.0f;", pSerieProvini->m_Dimensione1);
			m_CSVLine.Insert(m_CSVLine.GetLength(), appStr);

			// Diametro Effettivo
			appStr.Format("XXXX;");
			m_CSVLine.Insert(m_CSVLine.GetLength(), appStr);

			// Tensione di Snervamento 
			double PI_GRECO			= 3.141592654;
			double fiNominale		= pSerieProvini->m_Dimensione1;
			double sezNominale	= 0;
			double snervamento	= 0;
			if ( fiNominale > 0 )
			{
				sezNominale	= (fiNominale/2) * (fiNominale/2) * PI_GRECO;

				// Si prendono solamente 3 cifre
				CString stringa("");		
				stringa.Format("%f", sezNominale);
				int idx = stringa.Find(".", 0);	
				if (idx < 2)
				{
					stringa.Delete(5, stringa.GetLength() - 5);
					sezNominale = atof(stringa);
					stringa.Format("%1.2f", sezNominale);
				}
				else if (idx < 3)
				{
					stringa.Delete(6, stringa.GetLength() - 6);
					sezNominale = atof(stringa);
					stringa.Format("%2.1f", sezNominale);
				}
				else
					stringa.Format("%3.0f", sezNominale);

				sezNominale = atof(stringa);

				snervamento	= m_pDati->snervamento/sezNominale * 1000;
			}
			appStr.Format("%.0lf;", snervamento);
			m_CSVLine.Insert(m_CSVLine.GetLength(), appStr);


			// Tensione di Rottura
			double rotturaRelativa	= m_pDati->rottura/sezNominale * 1000;
			appStr.Format("%.0lf;",rotturaRelativa);
			m_CSVLine.Insert(m_CSVLine.GetLength(), appStr);

			// Allungamento
			double allungamentoPerc = m_pDati->allungamento + (rotturaRelativa / 2000);
			appStr.Format("%.1lf;",allungamentoPerc);
			m_CSVLine.Insert(m_CSVLine.GetLength(), appStr);

			// Esito
			m_pDati->esito ? appStr="P;" : appStr="N;";
			m_CSVLine.Insert(m_CSVLine.GetLength(), appStr);

			// Aderenza
			appStr.Format("%.3f;",m_pDati->aderenza);
			m_CSVLine.Insert(m_CSVLine.GetLength(), appStr);

			// Fornitore
			appStr  = pSerieProvini->m_SiglaFornitore;
			pos =  appStr.Find(PROVIDER);
			if(pos != -1)
			{
				appStr.Delete(0, pos + sizeof(PROVIDER));
				appStr.Insert(appStr.GetLength(), ";");
			}
			else
			{
				appStr.Format(";");
			}
			m_CSVLine.Insert(m_CSVLine.GetLength(), appStr);

			// Barra o Rotolo
			appStr.Format("%d",pSerieProvini->m_RotoliCT);
			m_CSVLine.Insert(m_CSVLine.GetLength(), appStr);
			m_CSVLine.Insert(m_CSVLine.GetLength(), "\r\n");
		}
	}

	if(pSerieProvini)
	{
		if (pSerieProvini->IsOpen())
		{
			pSerieProvini->Close();
		}
		delete pSerieProvini;
	}
}