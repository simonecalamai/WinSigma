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

class CPrintPreviewVerbali : public CPrintPreviewDoc
{
public:
	CPrintPreviewVerbali();
	virtual ~CPrintPreviewVerbali();
	virtual void Print(long lCodice, CDC* pDC, CRect* pRect);
  virtual int PrintPage(long lCodice, CDC* pDc, CRect* pRect, int nPage, double dScala, int nOrigine);
//	virtual void PrintText(long lCodice, CString strLpt = "");
	static	BOOL CALLBACK ScanFields(CStringArray* pFieldNames, CStringArray* pFieldValues);
  static	BOOL CALLBACK ScanCampioni(CStringArray* pFieldNames, CStringArray* pFieldValues);

private:
	CPrintVerbaliView* m_print_verbali;

protected:
  static BOOL    m_bPrivato;
  static BOOL    m_bSpianatura;
	static CString m_strTipoPagamento;
  static CVerbaliSet* m_pVerbaliSet;
  static CSerieSet*   m_pSerieSet;
	static CTipiCertificatoSet* m_pTipiCertificatoSet;

	static int m_nTotalePagine;
};

#endif // !defined(AFX_PRINTVERBALI_H__4DA8A720_2CB9_11D8_B754_00C026108782__INCLUDED_)
