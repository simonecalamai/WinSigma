// Configurazione.cpp: implementation of the CConfigurazione class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "winsigma.h"
#include "Configurazione.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConfigurazione::CConfigurazione()
{
  m_app = (CWinSigmaApp*)AfxGetApp();
	m_pDatabase = &(m_app->m_db);
}

CConfigurazione::~CConfigurazione()
{

}

CString CConfigurazione::Read(CString nome)
{
	CString valore = "";

	m_strFilter.Format("Nome = '%s'", nome);
  Open(CRecordset::snapshot, NULL, CRecordset::readOnly | CRecordset::noDirtyFieldCheck);
	
	if(!IsEOF())
	{
		valore = m_Valore;
	}

	Close();

	return valore;
}
