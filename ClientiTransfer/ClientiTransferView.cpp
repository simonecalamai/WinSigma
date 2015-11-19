// ClientiTransferView.cpp : implementation of the CClientiTransferView class
//

#include "stdafx.h"
#include "ClientiTransfer.h"

#include "ClientiTransferSet.h"
#include "ClientiTransferDoc.h"
#include "ClientiTransferView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientiTransferView

IMPLEMENT_DYNCREATE(CClientiTransferView, COleDBRecordView)

BEGIN_MESSAGE_MAP(CClientiTransferView, COleDBRecordView)
	//{{AFX_MSG_MAP(CClientiTransferView)
	ON_BN_CLICKED(IDC_BUTTON_TRASFERIMENTO, OnButtonTrasferimento)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientiTransferView construction/destruction

CClientiTransferView::CClientiTransferView()
	: COleDBRecordView(CClientiTransferView::IDD)
{
	//{{AFX_DATA_INIT(CClientiTransferView)
	m_pSet = NULL;
	m_csReport = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CClientiTransferView::~CClientiTransferView()
{
	m_pAziendeSet->Close();
	delete m_pAziendeSet;

	m_pSet_Old->Close();
	delete m_pSet_Old;

	m_pTipoPagSet->Close();
	delete m_pTipoPagSet;
}

void CClientiTransferView::DoDataExchange(CDataExchange* pDX)
{
	COleDBRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientiTransferView));
	DDX_Text(pDX, IDC_EDIT_REPORT, m_csReport);
	//}}AFX_DATA_MAP
}

BOOL CClientiTransferView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return COleDBRecordView::PreCreateWindow(cs);
}

void CClientiTransferView::OnInitialUpdate()
{
	m_pAziendeSet = new CAzSet(&GetDocument()->m_db);
	m_pSet_Old		= new CClienti_Old(&GetDocument()->m_db_old);
	m_pTipoPagSet	= new CTipoPagSet(&GetDocument()->m_db);

	HRESULT hr(0);

	m_pAziendeSet->m_strFilter.Empty();
	hr = m_pAziendeSet->Open();
	
	m_pSet_Old->m_strFilter.Empty();
	hr = m_pSet_Old->Open();
	
	m_pTipoPagSet->m_strFilter.Empty();
	hr = m_pTipoPagSet->Open();			

	COleDBRecordView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CClientiTransferView diagnostics

#ifdef _DEBUG
void CClientiTransferView::AssertValid() const
{
	COleDBRecordView::AssertValid();
}

void CClientiTransferView::Dump(CDumpContext& dc) const
{
	COleDBRecordView::Dump(dc);
}

CClientiTransferDoc* CClientiTransferView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClientiTransferDoc)));
	return (CClientiTransferDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClientiTransferView database support
CRowset* CClientiTransferView::OnGetRowset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// CClientiTransferView message handlers

void CClientiTransferView::OnButtonTrasferimento() 
{
	// TODO: Add your control notification handler code here
	m_pSet_Old->MoveFirst();
	
	GetDocument()->m_db.BeginTrans();

	int count(0);
	while (!m_pSet_Old->IsEOF())
	{
		if(	(strcmp(m_pSet_Old->m_iva,"00000000000")!=0)&&
				(strcmp(m_pSet_Old->m_iva,"NON PERVEN0")!=0)&&
				(strcmp(m_pSet_Old->m_iva,"NON PERVEN.")!=0)&&
				(strcmp(m_pSet_Old->m_iva,"NON PER000")!=0)&&
				(strcmp(m_pSet_Old->m_iva,"NON PERVE00")!=0)&&
				(strcmp(m_pSet_Old->m_iva,"NON PERVEN9")!=0)&&
				(strcmp(m_pSet_Old->m_iva,"NON PERVN00")!=0)&&
				(strcmp(m_pSet_Old->m_iva,"non perven0")!=0)&&
				(strcmp(m_pSet_Old->m_iva,"NON TIENE")!=0)&&
				(strcmp(m_pSet_Old->m_iva,"")!=0)
				)
		{
			try
			{
				m_pAziendeSet->AddNew();

				m_pAziendeSet->m_ID							=	m_pSet_Old->m_codice;
				m_pAziendeSet->m_RagioneSociale = m_pSet_Old->m_ragsociale + m_pSet_Old->m_estensione;
				m_pAziendeSet->m_Note						= m_pSet_Old->m_genspe;

				m_pAziendeSet->m_CAP_Sped							= m_pSet_Old->m_caps;
				m_pAziendeSet->m_Citta_Sped						= m_pSet_Old->m_descits;
				m_pAziendeSet->m_Indirizzo_Sped				= m_pSet_Old->m_indspe;
				m_pAziendeSet->m_Provincia_Sped				= m_pSet_Old->m_provs;

				m_pAziendeSet->m_Indirizzo			=	m_pSet_Old->m_indirizzo;
				m_pAziendeSet->m_Citta					=	m_pSet_Old->m_descitta;
				m_pAziendeSet->m_Provincia			=	m_pSet_Old->m_prov;
				m_pAziendeSet->m_CAP						=	m_pSet_Old->m_cap;
				m_pAziendeSet->m_P_IVA					=	m_pSet_Old->m_iva;
				m_pAziendeSet->m_Banca					=	m_pSet_Old->m_bancaapp;
				m_pAziendeSet->m_Sconto					=	atof(m_pSet_Old->m_sconto);
				m_pAziendeSet->m_Telefono				=	m_pSet_Old->m_ntelef;
				m_pAziendeSet->m_CodiceFiscale	=	m_pSet_Old->m_codfis;

				m_pAziendeSet->m_DataInserimento = m_pSet_Old->m_data_ins;

				m_pAziendeSet->m_ABI						=	m_pSet_Old->m_abi;
				m_pAziendeSet->m_CAB						=	m_pSet_Old->m_cab;

				Inserisci_Codice_Pagamento(atoi(m_pSet_Old->m_codpaga));

				m_pAziendeSet->Update();

				count++;
		} 
		catch (CDBException* e) 
		{};
		}
		m_pSet_Old->MoveNext();
	}

	char buf[25];
	sprintf(buf,"%d",count);
	m_csReport.Insert(m_csReport.GetLength(),buf);
	m_csReport += " Aggiunti con Successo!\r\n";
	UpdateData(FALSE);

	GetDocument()->m_db.CommitTrans();
}

void CClientiTransferView::Inserisci_Codice_Pagamento(int codpaga)
{
	char buf[25];
	int hr(0);
	sprintf(buf,"%d",codpaga);
	CString sql(buf);

	m_pTipoPagSet->m_strFilter = "VecchioCod = " + sql;
	hr = m_pTipoPagSet->Requery();
	
	if ((hr==1)&&(!m_pTipoPagSet->IsEOF()))	
		m_pAziendeSet->m_TipoPagamento	= m_pTipoPagSet->m_Codice;
}