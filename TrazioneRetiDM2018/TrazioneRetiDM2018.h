// TrazioneRetiDM2018.h : main header file for the TrazioneRetiDM2018 DLL
//

#if !defined(AFX_TrazioneRetiDM2018_H__E0882B23_FEDF_4F0D_8084_1A3DCFB9E31C__INCLUDED_)
#define AFX_TrazioneRetiDM2018_H__E0882B23_FEDF_4F0D_8084_1A3DCFB9E31C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "..\AllTables.h"
#include "..\bmobject.h"
#include "Math.h"



////////////////////////////////////////////////////////////// 
// Definizione delle macro generiche

#define DENOMINATORE_SEZIONE 7.85
#define PI_GRECO 3.141592654
#define INDICE_ALLUNGAMENTO 10

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
	int nVersione;
	double	peso;
	double	lunghezza;
	double	snervamento;
	double	rottura;
	double	allungamento;
	double	distacco;
	byte		tipoDistacco;
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

__declspec( dllexport ) BOOL StampaAllegato(CString* fileLayout, CAllTables* tabelle, 
																						CStringArray* fieldNames, CStringArray* fieldValues, 
																						int* pContaProvini, BOOL* Duplicato, CTime* DataDuplicato);
}

/////////////////////////////////////////////////////////////////////////////
// CTrazioneRetiDM2018App
// See TrazioneRetiDM2018.cpp for the implementation of this class
//

class CTrazioneRetiDM2018App : public CWinApp
{
public:
	CTrazioneRetiDM2018App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrazioneRetiDM2018App)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CTrazioneRetiDM2018App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TrazioneRetiDM2018_H__E0882B23_FEDF_4F0D_8084_1A3DCFB9E31C__INCLUDED_)

