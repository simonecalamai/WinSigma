// ResilienzaProfilati.h : main header file for the RESILIENZAPROFILATI DLL
//

#if !defined(AFX_RESILIENZAPROFILATI_H__C32542B1_2C49_47AB_81F5_EAD0684E6EE7__INCLUDED_)
#define AFX_RESILIENZAPROFILATI_H__C32542B1_2C49_47AB_81F5_EAD0684E6EE7__INCLUDED_

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
#define MARCHI_FOLDER			"marchi"

#define PI_GRECO 3.141592654

#define SAFETY_OPEN(pSet) pSet->IsOpen() ? pSet->Requery() : pSet->Open();

#define SET_START(pSet)   (pSet->IsBOF() ? \
				                   pSet->IsEOF() ? 0 : pSet->MoveNext() : \
							             pSet->MoveFirst())

#define SINCRONIZE(pSet, cod) for(SET_START(pSet); !pSet->IsEOF(); pSet->MoveNext()) \
	if(pSet->m_Codice==cod) break; \
	ASSERT(!pSet->IsEOF())

#define NORMALE 0
#define	SOSTITUTIVA 1
#define STR_NORMALE "Normale"
#define STR_SOSTITUTIVA "Sostitutiva"
#define DIM_STR_TEMP 10
#define DIM_STR_SEZ 10



/////////////////////////////////////////////////////////////////////////////
// Struttura dati dedicata

struct dati 
	{
	int			nVersione;
	int			provetta;
	double	kv;
	char		temperatura[DIM_STR_TEMP];
	char		sezione[DIM_STR_SEZ];
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
// CResilienzaProfilatiApp
// See ResilienzaProfilati.cpp for the implementation of this class
//

class CResilienzaProfilatiApp : public CWinApp
{
public:
	CResilienzaProfilatiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResilienzaProfilatiApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CResilienzaProfilatiApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESILIENZAPROFILATI_H__C32542B1_2C49_47AB_81F5_EAD0684E6EE7__INCLUDED_)
