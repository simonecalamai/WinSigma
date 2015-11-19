// PrintVerbali.h: interface for the CPrintVerbali class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTVERBALI_H__4DA8A720_2CB9_11D8_B754_00C026108782__INCLUDED_)
#define AFX_PRINTVERBALI_H__4DA8A720_2CB9_11D8_B754_00C026108782__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <afxext.h>
#endif // _MSC_VER > 1000

#include "XFormView.h"
#include "PrintVerbaliView.h"

#define TIME_OUT_MSG_ID   WM_USER + 3

class CWinSigmaDoc;

class CPrintVerbali : public CObject
{
public:
	CPrintVerbali(CWinSigmaDoc* pDoc = NULL, HWND m_hWnd = NULL);
	virtual ~CPrintVerbali();

	void		PrintVerbale(BOOL bCartaNumerata, long lCodVerbale);
	static	BOOL CALLBACK ScanFields(CStringArray* pFieldNames, CStringArray* pFieldValues);
  static	BOOL CALLBACK ScanCampioni(CStringArray* pFieldNames, CStringArray* pFieldValues);

private:
	CWinSigmaDoc* m_pDoc;
	static CString m_csApp1;
	static CString m_csApp2;	
	CPrintVerbaliView* m_print_verbali;

protected:
	static CString m_strTipoPagamento;
  static CVerbaliSet* m_pVerbaliSet;
  static CSerieSet*   m_pSerieSet;
	static CTipiCertificatoSet* m_pTipiCertificatoSet;

	static int m_nTotalePagine;
	
	HWND m_hWnd;	
};

#endif // !defined(AFX_PRINTVERBALI_H__4DA8A720_2CB9_11D8_B754_00C026108782__INCLUDED_)
