// PrintPreviewFatture.h: interface for the CPrintPreviewFatture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTPREVIEWFATTURE_H__464CEEAA_A24E_4565_832D_8868895C4CCB__INCLUDED_)
#define AFX_PRINTPREVIEWFATTURE_H__464CEEAA_A24E_4565_832D_8868895C4CCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XFormView.h"
#include "PreviewDlg.h"

class CWinSigmaDoc;

class CPrintPreviewFatture : public CPrintPreviewDoc  
{
public:
	CPrintPreviewFatture();
	virtual ~CPrintPreviewFatture();
	virtual void Print(long lCodice, CDC* pDC, CRect* pRect);
  virtual int PrintPage(long lCodice, CDC* pDc, CRect* pRect, int nPage, double dScala, int nOrigine);
  static BOOL CALLBACK ScanDatiFattura(CStringArray* pFieldNames, CStringArray* pFieldValues);
	static BOOL CALLBACK ScanServizi(CStringArray* pFieldNames, CStringArray* pFieldValues);
  static BOOL CALLBACK ScanPerServizio(CStringArray* pFieldNames, CStringArray* pFieldValues);

  long m_lCodiceAzienda;
  double m_dImportoFattura;
  static long m_lCodiceVerbale;
  static long m_lCodiceServizio;
  static long m_lCodiceFattura;
  static BOOL m_bPrintProForma;
  static CAziendeSet* m_pAziendeSet;
  static CFattureSet* m_pFattureEmesseSet;
  static CVerbaliSet* m_pVerbaliInfatturazione;
  static CServiziErogatiSet* m_pServiziErogati;
  static int  m_nNumPagine;
  static BOOL m_bVerbaliPrinted;
  static int m_nImportoVerbale;
  int  m_nNumeroCopie;
  // dati fattura
  BOOL m_bRaggruppaPerServizio;  
  static CString m_strTipoDocumento;
  static CString m_strTotaleFattura;
  static CString m_strImportoScontato;
  static CString m_strImponibile;
  static CString m_strIVA;
  static double m_dSconto;
  static double m_dAliquota;
  static double m_dSpeseSpedizione;
  static BOOL m_bSpedSelezionata;
  static BOOL m_bMaggiorazione;
  static CString m_strTipoPagamento;
  static BOOL m_bRiba;
  static CString m_strProgressiviVerbali;
  CString m_strLayout;

protected:
  void CalcolaTotale(void);
  void SincronizeData(void);
};

#endif // !defined(AFX_PRINTPREVIEWFATTURE_H__464CEEAA_A24E_4565_832D_8868895C4CCB__INCLUDED_)
