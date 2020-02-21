// TrazionePiegamentoBarreCTDM2018.h : main header file for the TRAZIONEPIEGAMENTOBARRECTDM2018 DLL
//

#if !defined(AFX_TRAZIONEPIEGAMENTOBARRECTDM2018_H__E374F35B_FC43_46A1_BE9C_3F2C7063328A__INCLUDED_)
#define AFX_TRAZIONEPIEGAMENTOBARRECTDM2018_H__E374F35B_FC43_46A1_BE9C_3F2C7063328A__INCLUDED_

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

#define PESO_SPECIFICO 7.85
#define PI_GRECO 3.141592654
#define INDICE_ALLUNGAMENTO 5
#define MARCHI_FOLDER			"marchi"

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
	double	aderenza;
	int			mandrino;
	byte		esito;
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
																				 CStringArray* pFieldValues, byte primoCampo, int numeroInterno, long CodiceCertificato);

__declspec( dllexport ) BOOL StampaAllegato(CString* fileLayout, CAllTables* tabelle, 
																						CStringArray* fieldNames, CStringArray* fieldValues, CStringArray* marchiFiles,  
																						int* pContaProvini, BOOL* Duplicato,  CTime* DataDuplicato);
}

/////////////////////////////////////////////////////////////////////////////
// CTrazionePiegamentoBarreCTDM2018
// See TrazionePiegamentoBarreCTDM2018.cpp for the implementation of this class
//

class CTrazionePiegamentoBarreCTDM2018App : public CWinApp
{
public:
	CTrazionePiegamentoBarreCTDM2018App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrazionePiegamentoBarreCTDM2018)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CTrazionePiegamentoBarreCTDM2018)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TrazionePiegamentoBarreCTDM2018_H__E374F35B_FC43_46A1_BE9C_3F2C7063328A__INCLUDED_)
