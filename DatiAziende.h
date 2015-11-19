// DatiAziende.h: interface for the CDatiAziende class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATIAZIENDE_H__316488C1_3170_11D8_B754_00C026108782__INCLUDED_)
#define AFX_DATIAZIENDE_H__316488C1_3170_11D8_B754_00C026108782__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDatiAziende  
{
public:
	CDatiAziende();
	virtual ~CDatiAziende();
	long	m_Codice;
	long	m_TipoPagamento;
	BYTE	m_Privato;
	CString	m_ID;
	CString	m_P_IVA;
	CString	m_CodiceFiscale;
	CString	m_RagioneSociale;
	CString	m_RagioneSociale_Sped;
	CString	m_Nome;
	CString	m_Cognome;
	CString	m_Indirizzo;
	CString	m_CAP;
	CString	m_Citta;
	CString	m_Provincia;
	CString	m_Indirizzo_Sped;
	CString	m_CAP_Sped;
	CString	m_Citta_Sped;
	CString	m_Provincia_Sped;
	CString	m_E_Mail;
	CString	m_Telefono;
	CString	m_Cellulare;
	CString	m_Fax;
	CString	m_Banca;
	CString	m_ABI;
	CString	m_CAB;
	CString	m_Note;
	double	m_Sconto;
	CTime	m_DataInserimento;
	CTime	m_DataUltimoRapporto;
	BYTE	m_IsImportante;
	BYTE	m_UsaTuttiListini;
};

#endif // !defined(AFX_DATIAZIENDE_H__316488C1_3170_11D8_B754_00C026108782__INCLUDED_)
