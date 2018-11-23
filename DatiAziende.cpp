// DatiAziende.cpp: implementation of the CDatiAziende class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "winsigma.h"
#include "DatiAziende.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDatiAziende::CDatiAziende()
{
	m_Codice = 0;
	m_TipoPagamento = 0;
	m_Privato = 0;
	m_ID = _T("");
	m_P_IVA = _T("");
	m_CodiceFiscale = _T("");
	m_RagioneSociale = _T("");
	m_RagioneSociale_Sped = _T("");
	m_Nome = _T("");
	m_Cognome = _T("");
	m_Indirizzo = _T("");
	m_CAP = _T("");
	m_Citta = _T("");
	m_Provincia = _T("");
	m_Indirizzo_Sped = _T("");
	m_CAP_Sped = _T("");
	m_Citta_Sped = _T("");
	m_Provincia_Sped = _T("");
	m_E_Mail = _T("");
	m_Telefono = _T("");
	m_Cellulare = _T("");
	m_Fax = _T("");
	m_Banca = _T("");
	m_ABI = _T("");
	m_CAB = _T("");
	m_Note = _T("");
	m_Sconto = 0.0;
	m_IsImportante = 0;
	m_UsaTuttiListini = 0;
	m_CodiceDestinatario = _T("");
	m_PEC = _T("");
	m_IBAN = _T("");
}

CDatiAziende::~CDatiAziende()
{

}
