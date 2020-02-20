// MarchiView.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "bmobject.h"
#include "printerpreter.h"
#include "xbmpcontrol.h"
#include "winsigmadoc.h"
#include "XFormView.h"
#include "MarchiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMarchiView

IMPLEMENT_DYNCREATE(CMarchiView, CFormView)

CMarchiView::CMarchiView()
	: CXFormView(CMarchiView::IDD)
{
	//{{AFX_DATA_INIT(CMarchiView)
	m_strCodice = _T("");
	m_strDescrizione = _T("");
	m_strNome = _T("");
	m_strProduttore = _T("");
	m_strStabilimento = _T("");
	//}}AFX_DATA_INIT
}

CMarchiView::~CMarchiView()
{
}

void CMarchiView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMarchiView)
	DDX_Control(pDX, IDC_BUTTON_SFOGLIA, m_ButtonSfoglia);
	DDX_Control(pDX, IDC_EDIT_STABILIMENTO, m_EditStabilimento);
	DDX_Control(pDX, IDC_EDIT_PRODUTTORE, m_EditProduttore);
	DDX_Control(pDX, IDC_EDIT_NOME, m_EditNome);
	DDX_Control(pDX, IDC_EDIT_DESCRIZIONE, m_EditDescrizione);
	DDX_Control(pDX, IDC_STATIC_MARCHIO, m_StaticMarchio);
	DDX_Text(pDX, IDC_EDIT_CODICE, m_strCodice);
	DDX_Text(pDX, IDC_EDIT_DESCRIZIONE, m_strDescrizione);
	DDV_MaxChars(pDX, m_strDescrizione, 250);
	DDX_Text(pDX, IDC_EDIT_NOME, m_strNome);
	DDV_MaxChars(pDX, m_strNome, 32);
	DDX_Text(pDX, IDC_EDIT_PRODUTTORE, m_strProduttore);
	DDV_MaxChars(pDX, m_strProduttore, 64);
	DDX_Text(pDX, IDC_EDIT_STABILIMENTO, m_strStabilimento);
	DDV_MaxChars(pDX, m_strStabilimento, 64);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMarchiView, CXFormView)
	//{{AFX_MSG_MAP(CMarchiView)
	ON_BN_CLICKED(IDC_BUTTON_SFOGLIA, OnButtonSfoglia)
	ON_COMMAND(ID_STAMPA, OnStampa)
	ON_COMMAND(ID_BUTTON_AGGIORNA, OnButtonAggiorna)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMarchiView diagnostics

#ifdef _DEBUG
void CMarchiView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMarchiView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMarchiView message handlers

void CMarchiView::OnInitialUpdate() 
{
	CWinSigmaDoc* pDoc = (CWinSigmaDoc*)GetDocument();
	m_pSet = pDoc->m_pMarchiSet;
	CXFormView::m_pSet = m_pSet;

	CXFormView::OnInitialUpdate();
		m_StaticMarchio.Set(&m_BmpObject);
}

void CMarchiView::LoadCurRecord(BOOL bData)
{
	CMemFile  mFile;

	if(m_BmpObject.IsOpen())
    m_BmpObject.Close();
  if(bData)
	{
		m_strCodice.Format("MA%d", m_pSet->m_Codice);
		m_strNome         = m_pSet->m_Nome;
		m_strDescrizione  = m_pSet->m_Descrizione;
    m_strProduttore   = m_pSet->m_Produttore;
		m_strStabilimento = m_pSet->m_Stabilimento;
		if(!m_pSet->IsFieldNull(&m_pSet->m_Immagine))
		{
			mFile.Attach(m_pSet->m_Immagine.GetData(), m_pSet->m_Immagine.GetSize());
			m_BmpObject.Open(&mFile);
		}
  }
	else
	{
		m_strCodice.Empty();
		m_strNome.Empty();
		m_strDescrizione.Empty();
		m_strProduttore.Empty();
		m_strStabilimento.Empty();
  }
	m_strFileName.Empty();
  m_StaticMarchio.RedrawWindow();
}

BOOL CMarchiView::IsDataChanged()
{
  if(m_strNome     != m_pSet->m_Nome
		 ||	m_strDescrizione  != m_pSet->m_Descrizione
		 || m_strProduttore   != m_pSet->m_Produttore
		 || m_strStabilimento != m_pSet->m_Stabilimento
		 || !m_strFileName.IsEmpty())
		return TRUE;
  return FALSE;
}

BOOL CMarchiView::ValidateData()
{
  if(m_strNome.GetLength() < 2)
	{
	  AfxMessageBox("La lunghezza del nome deve essere di almeno due lettere");
	  return FALSE;
	}
	if(!m_BmpObject.IsOpen())
	{
	  AfxMessageBox("Selezionare un'immagine");
	  return FALSE;
	}
	return TRUE;
}

BOOL CMarchiView::NewRecord()
{
	CMemFile   mFile;
	CByteArray data;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

	if(!ValidateData())
	  return FALSE;
	/*---- costruisco il memory file e ci salvo l'immagine ----*/
	data.SetSize(m_BmpObject.GetFileLenght());
	mFile.Attach(data.GetData(), data.GetSize());
	m_BmpObject.Save(&mFile);
	m_pSet->m_Immagine.Copy(data);
	/*---- aggiungo il record -----*/
	m_pSet->AddNew();
	m_pSet->m_Nome         = m_strNome;
	m_pSet->m_Descrizione  = m_strDescrizione;
	m_pSet->m_Produttore   = m_strProduttore;
	m_pSet->m_Stabilimento = m_strStabilimento;
 	m_pSet->m_Immagine.Copy(data);
	m_pSet->Update();
	pApp->ReloadTree(TREELABEL_MARCHI, -1);
	return TRUE;
}

BOOL CMarchiView::SaveRecord()
{
	CMemFile   mFile;
	CByteArray data;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

	if(!ValidateData())
	  return FALSE;
  switch(AfxMessageBox("Salvare le modifiche ai dati?", MB_YESNOCANCEL))
	{
	  case IDYES:
			/*---- costruisco il memory file e ci salvo l'immagine ----*/
			data.SetSize(m_BmpObject.GetFileLenght());
			mFile.Attach(data.GetData(), data.GetSize());
			m_BmpObject.Save(&mFile);
			m_pSet->m_Immagine.Copy(data);
			/*---- aggiorno il recodset -----*/
  	  m_pSet->Edit();
			m_pSet->m_Nome         = m_strNome;
			m_pSet->m_Descrizione  = m_strDescrizione;
			m_pSet->m_Produttore   = m_strProduttore;
			m_pSet->m_Stabilimento = m_strStabilimento;
		  m_pSet->m_Immagine.Copy(data);
	    m_pSet->Update();
			/*---- ----*/
	    pApp->ReloadTree(TREELABEL_MARCHI, m_pSet->m_Codice);
		  break;
		case IDNO:
		  break;
		default:
		  return FALSE;
	}
	return TRUE;
}

BOOL CMarchiView::DeleteRecord()
{
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();
	CString str;

  if(!m_pSet->IsBOF())
	{
		str.Format("Eliminare il marchio %s (Codice %s)?",
							 m_strNome, m_strCodice);

		if(AfxMessageBox(str, MB_YESNO) == IDYES)
		{
			m_pSet->Delete();
	    pApp->ReloadTree(TREELABEL_MARCHI, -1);
  	return TRUE;
		}
    return FALSE;
	}
	return FALSE;
}

void CMarchiView::EnableControls(BOOL bEditMode)
{
	m_EditNome.EnableWindow(bEditMode);
	m_EditDescrizione.EnableWindow(bEditMode);
	m_EditProduttore.EnableWindow(bEditMode);
	m_EditStabilimento.EnableWindow(bEditMode);
	m_ButtonSfoglia.EnableWindow(bEditMode);
	m_EditNome.SetFocus();
}


void CMarchiView::OnButtonSfoglia() 
{
  CFileDialog  fileDlg(TRUE, "bmp", "*.bmp");
	
	if(fileDlg.DoModal() == IDOK)
	{
	  if(m_BmpObject.IsOpen())
		  m_BmpObject.Close();
	  m_BmpObject.Open(m_strFileName = fileDlg.GetPathName());
		m_StaticMarchio.RedrawWindow();
	}	
}

void CMarchiView::OnStampa() 
{
  CStringArray fieldNames, fieldValues;
	CPrintInterpreter  prn;
	CWinSigmaApp* pApp = (CWinSigmaApp*)AfxGetApp();

  m_BmpObject.Save("marchio.bmp");
	prn.PrePrinting();
	prn.Print(pApp->GetCurrentDirectory() + "\\marchio.prn", &fieldNames, &fieldValues, NULL, NULL, NULL);
	prn.PostPrinting();
}


void CMarchiView::OnButtonAggiorna() 
{
	CWinSigmaApp* pApp	= (CWinSigmaApp*)AfxGetApp();
	if( MODE_VIEW != pApp->GetViewMode())
		return;
	long nCurSel = m_pSet->m_Codice;
	pApp->ReloadTree(TREELABEL_MARCHI, nCurSel);
}
