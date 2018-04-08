// CompressioneCubiDM2018.h : main header file for the COMPRESSIONECUBIDM2018 DLL
//

#if !defined(AFX_COMPRESSIONECUBI_H__89A178BC_24A2_4769_9CBB_7A47EE1B0806__INCLUDED_)
#define AFX_COMPRESSIONECUBI_H__89A178BC_24A2_4769_9CBB_7A47EE1B0806__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "..\AllTables.h"

////////////////////////////////////////////////////////////// 
// Definizione delle macro generiche

#define BIPIRAMIDALE	1
#define SFALDAMENTO		2
#define SGRETOLAMENTO	3
#define ALTRO					4
#define LIMITE_RIGA		30

#define SODDISFACENTE	      1
#define NON_SODDISFACENTE		2

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
	double	lung;
	double	larg;
	double	alt;
	double	massa;
	double	caricoSp;
	byte		tipoRott;
	};


/////////////////////////////////////////////////////////////////////////////
// Dichiarazione delle funzione esportate dal modulo dll
//

extern "C"
{
__declspec( dllexport ) int OpenDlg(long codSerie, CAllTables* tabelle, long* ultimoSperimentatore, CTime* pUltimaDataProva);

__declspec( dllexport ) int LoadProveMateriale(CStringArray* stringhe, CAllTables* tabelle, CDWordArray* parySerieEliminate);

__declspec( dllexport ) int RiempiCampi(long numCertificato, CAllTables* pTabelle,
																				CStringArray* fieldNames, CStringArray* fieldValues);

__declspec( dllexport ) BOOL DatiProvino(CAllTables* pTabelle, CStringArray* pFieldNames, 
																				 CStringArray* pFieldValues, byte primoCampo, int numeroInterno);

__declspec( dllexport ) BOOL ConCubiera(CSerieSet* pSerieSet, CServiziListinoSet* pServSet, CString& strCommento);

}


/////////////////////////////////////////////////////////////////////////////
// CCompressioneCubiDM2018App
// See CompressioneCubiDM2018.cpp for the implementation of this class
//


class CCompressioneCubiDM2018App : public CWinApp
{
public:
	CCompressioneCubiDM2018App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompressioneCubiDM2018App)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCompressioneCubiDM2018App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPRESSIONECUBI_H__89A178BC_24A2_4769_9CBB_7A47EE1B0806__INCLUDED_)
