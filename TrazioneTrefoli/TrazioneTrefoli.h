// TrazioneTrefoli.h : main header file for the TRAZIONETREFOLI DLL
//

#if !defined(AFX_TRAZIONETREFOLI_H__DC747D5D_C12B_4A1F_82A9_356BFDE6D7D0__INCLUDED_)
#define AFX_TRAZIONETREFOLI_H__DC747D5D_C12B_4A1F_82A9_356BFDE6D7D0__INCLUDED_

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

#define TITOLO "PROVA DI TRAZIONE SU TREFOLI DA C.A.P."
#define MATERIALE "Trefoli"
#define STR_ALLUNGAMENTO 5

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
	double	limite1;
	double	limite2;
	double	tensione;
	double	rottura;
	double	moduloElastico;
	char	allungamento[STR_ALLUNGAMENTO];
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
// CTrazioneTrefoliApp
// See TrazioneTrefoli.cpp for the implementation of this class
//

class CTrazioneTrefoliApp : public CWinApp
{
public:
	CTrazioneTrefoliApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrazioneTrefoliApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CTrazioneTrefoliApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAZIONETREFOLI_H__DC747D5D_C12B_4A1F_82A9_356BFDE6D7D0__INCLUDED_)
