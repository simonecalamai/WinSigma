// TrazioneProfilati.h : main header file for the TRAZIONEPROFILATI DLL
//

#if !defined(AFX_TRAZIONEPROFILATI_H__E9520F62_F6E3_4C95_98F3_3916E405F89E__INCLUDED_)
#define AFX_TRAZIONEPROFILATI_H__E9520F62_F6E3_4C95_98F3_3916E405F89E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "..\AllTables.h"
#include "..\bmobject.h"



////////////////////////////////////////////////////////////// 
// Definizione delle macro generiche

#define MATERIALE "Profilati in acciaio"

#define PI_GRECO 3.141592654

#define SAFETY_OPEN(pSet) pSet->IsOpen() ? pSet->Requery() : pSet->Open();

#define SET_START(pSet)   (pSet->IsBOF() ? \
				                   pSet->IsEOF() ? 0 : pSet->MoveNext() : \
							             pSet->MoveFirst())

#define SINCRONIZE(pSet, cod) for(SET_START(pSet); !pSet->IsEOF(); pSet->MoveNext()) \
	if(pSet->m_Codice==cod) break; \
	ASSERT(!pSet->IsEOF())



/////////////////////////////////////////////////////////////////////////////
// Struttura dati dedicata

struct dati 
	{
	int			nVersione;
	double	area;
	double	snervamento;
	double	rottura;
	double	allungamento;
	};

/////////////////////////////////////////////////////////////////////////////
// Dichiarazione delle funzione esportate dal modulo dll
//

extern "C"
{
__declspec( dllexport ) int OpenDlg(long codSerie, CAllTables* tabelle, long* ultimoSperimentatore, CTime* pUltimaDataProve);

__declspec( dllexport ) int LoadProveMateriale(CStringArray* stringhe, CAllTables* tabelle, CDWordArray* parySerieEliminate);

__declspec( dllexport ) int RiempiCampi(long numCertificato, CAllTables* pTabelle,
																				CStringArray* fieldNames, CStringArray* fieldValues);

__declspec( dllexport ) BOOL DatiProvino(CAllTables* pTabelle, CStringArray* pFieldNames, 
																				 CStringArray* pFieldValues, byte primoCampo, int numeroInterno);

__declspec( dllexport ) BOOL StampaAllegato(CString* fileLayout,CSerieProviniSet* pSerieSet, 
																						CAllTables* tabelle, CStringArray* fieldNames, CStringArray* marchiFiles,  
																						CStringArray* fieldValues, int* contaProvini);
}


/////////////////////////////////////////////////////////////////////////////
// CTrazioneProfilatiApp
// See TrazioneProfilati.cpp for the implementation of this class
//

class CTrazioneProfilatiApp : public CWinApp
{
public:
	CTrazioneProfilatiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrazioneProfilatiApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CTrazioneProfilatiApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAZIONEPROFILATI_H__E9520F62_F6E3_4C95_98F3_3916E405F89E__INCLUDED_)
