// WinSigmaDoc.h : interface of the CWinSigmaDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINSIGMADOC_H__73C5E06A_BB73_11D7_B754_0080AD70B2EE__INCLUDED_)
#define AFX_WINSIGMADOC_H__73C5E06A_BB73_11D7_B754_0080AD70B2EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWinSigmaDoc : public CDocument
{
protected: // create from serialization only
	CWinSigmaDoc();
	DECLARE_DYNCREATE(CWinSigmaDoc)

// Attributes
public:
  CAziendeSet*         m_pAziendeSet;
  CAziendeTurboSet*    m_pAziendeTurboSet;
  CAziendeSet*         m_pAziendeImportantiSet;
  CAziendeSet*         m_pAziendeRecentiSet;
  COperatoriSet*			 m_pOperatoriSet;
  CTipiMaterialeSet*	 m_pTipiMaterialeSet;
  CTipiPagamentoSet*	 m_pTipiPagamentoSet;
  CMarchiSet*	         m_pMarchiSet;
  CMarchiTurboSet*     m_pMarchiTurboSet;
  CListiniSet*	       m_pListiniScadutiSet;
  CListiniSet*	       m_pListiniInVigoreSet;
  CListiniSet*	       m_pListiniInElaborazioneSet;
  CVerbaliSet*         m_pVerbaliAperti;
  CVerbaliSet*         m_pVerbaliUltimoMeseSet;
  CVerbaliSet*         m_pVerbaliPrecedentiSet;
  CVerbaliSet*         m_pVerbaliFattProforma;
  CTipiCertificatoSet* m_pTipiCertificatoSet;
  CSerieSet*           m_pSerieSet;
  CFattureSet*         m_pFattureEmesseSet;

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinSigmaDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_nSelectedTreeAziende;
  int m_nSelectedTreeVerbali;
  int m_nSelectedTreeFatture;
  int m_nSelectedTreeListini;
	virtual ~CWinSigmaDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWinSigmaDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINSIGMADOC_H__73C5E06A_BB73_11D7_B754_0080AD70B2EE__INCLUDED_)
