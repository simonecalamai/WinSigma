// PrintPreviewCertificati.h: interface for the CPrintPreviewCertificati class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTPREVIEWCERTIFICATI_H__5113BF5C_D9D8_419E_9728_DA177D8AAA62__INCLUDED_)
#define AFX_PRINTPREVIEWCERTIFICATI_H__5113BF5C_D9D8_419E_9728_DA177D8AAA62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XFormView.h"
#include "PreviewDlg.h"

class CWinSigmaDoc;

class CPrintPreviewCertificati : public CPrintPreviewDoc  
{
public:
	CPrintPreviewCertificati();
	virtual ~CPrintPreviewCertificati();
	virtual void Print(long lCodice, CDC* pDC, CRect* pRect);
  virtual int PrintPage(long lCodice, CDC* pDc, CRect* pRect, int nPage, double dScala, int nOrigine);
};

#endif // !defined(AFX_PRINTPREVIEWCERTIFICATI_H__5113BF5C_D9D8_419E_9728_DA177D8AAA62__INCLUDED_)
