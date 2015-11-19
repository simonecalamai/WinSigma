// ClientiTransferDoc.cpp : implementation of the CClientiTransferDoc class
//

#include "stdafx.h"
#include "ClientiTransfer.h"

#include "ClientiTransferSet.h"
#include "ClientiTransferDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientiTransferDoc

IMPLEMENT_DYNCREATE(CClientiTransferDoc, CDocument)

BEGIN_MESSAGE_MAP(CClientiTransferDoc, CDocument)
	//{{AFX_MSG_MAP(CClientiTransferDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientiTransferDoc construction/destruction

CClientiTransferDoc::CClientiTransferDoc()
{
	// TODO: add one-time construction code here

}

CClientiTransferDoc::~CClientiTransferDoc()
{
	m_db.Close();
	m_db_old.Close();
}

BOOL CClientiTransferDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	// Imposta la stinga di connessione
	m_csDefaultConnect.Format("ODBC;UID=dbuser;PWD=49sigma03");

  // prova ad aprire la connessione con i dati
	if(!m_db.Open("WinSigma", FALSE, FALSE, m_csDefaultConnect, TRUE))
	{
	  AfxMessageBox("Connessione alla base dati fallita."); 
	  return FALSE;
	}

	m_csDefaultConnect_old.Format("ODBC;DSN=Clienti");
  // prova ad aprire la connessione con i dati
	if(!m_db_old.Open("Clienti", FALSE, FALSE, m_csDefaultConnect_old, TRUE))
	{
	  AfxMessageBox("Connessione alla base dati fallita."); 
	  return FALSE;
	}

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CClientiTransferDoc diagnostics

#ifdef _DEBUG
void CClientiTransferDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CClientiTransferDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClientiTransferDoc commands
