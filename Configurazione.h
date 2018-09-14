// Configurazione.h: interface for the CConfigurazione class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIGURAZIONE_H__7B816258_4846_434A_9E91_0202BEF0CB57__INCLUDED_)
#define AFX_CONFIGURAZIONE_H__7B816258_4846_434A_9E91_0202BEF0CB57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ConfigurazioneSet.h"

class CConfigurazione : public CConfigurazioneSet  
{
public:
	CString Read(CString nome);
	int Write(CString nome, CString valore);
	CConfigurazione();
	virtual ~CConfigurazione();

private:
	CWinSigmaApp * m_app;

};

#endif // !defined(AFX_CONFIGURAZIONE_H__7B816258_4846_434A_9E91_0202BEF0CB57__INCLUDED_)
