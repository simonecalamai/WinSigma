// VerbaliTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "WinSigma.h"
#include "WinSigmaDoc.h"
#include "XTreeCtrl.h"
#include "VerbaliTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


class CUltimoMeseTree : public CXRecsetTree
{
  public:
		CUltimoMeseTree(CRecordset* pSet, int nTag, int nIcon)
		   : CXRecsetTree(pSet, nTag, nIcon)
		{
		};
		long GetCode()
		{
			CVerbaliSet* pSet = (CVerbaliSet*)m_pSet;
			if(pSet->m_InUso == INSERIMENTO_NUOVO_VERBALE)
				m_nIcon = 5;
			else
  		{
        switch(pSet->m_TipoVerbale)
        {
        case VERB_IN_CONCESSIONE:
					m_nIcon = 1;
          break;
        case VERB_NON_IN_CONCESSIONE:
				case VERB_NC_PROVE_DI_CARICO:
				case VERB_NC_CONGL_BITUMINOSI:
				case VERB_NC_INERTI:
				case VERB_NC_MONITORAGGI:
				case VERB_NC_VARIE:
				case VERB_NC_GEOTECNICA :
				case VERB_NC_LINEE_VITA:
				case VERB_NC_INDAGINI_MURATURE:
				case VERB_NC_INDAGINI_CLS:
				case VERB_NC_MAT_METALLICI:
					m_nIcon = 2;
          break;
        case VERB_GEOLOGIA:
          m_nIcon = 5;
          break;
        }
	  	}
      
			return ((CVerbaliSet*)m_pSet)->m_Codice;
		};
		CString GetLabel()
		{
      CString str;
			CVerbaliSet* pSet = (CVerbaliSet*)m_pSet;
      if(pSet->m_InUso == INSERIMENTO_NUOVO_VERBALE)
				m_nIcon = 5;
			else
			{
        switch(pSet->m_TipoVerbale)
        {
        case VERB_IN_CONCESSIONE:
					m_nIcon = 1;
          break;
        case VERB_NON_IN_CONCESSIONE:
				case VERB_NC_PROVE_DI_CARICO:
				case VERB_NC_CONGL_BITUMINOSI:
				case VERB_NC_INERTI:
				case VERB_NC_MONITORAGGI:
				case VERB_NC_VARIE:
				case VERB_NC_GEOTECNICA :
				case VERB_NC_LINEE_VITA:
				case VERB_NC_INDAGINI_MURATURE:
				case VERB_NC_INDAGINI_CLS:
				case VERB_NC_MAT_METALLICI:
					m_nIcon = 2;
          break;
        case VERB_GEOLOGIA:
          m_nIcon = 5;
          break;
        }
			}
#ifdef WINSIGMA2
      str.Format("V. A%d del %s", pSet->m_ProgressivoTotale, (pSet->m_DataAccettazione).Format("%d/%m/%y"));
#else
      str.Format("V. %d/%d del %s", pSet->m_ProgressivoParziale, pSet->m_ProgressivoTotale, (pSet->m_DataAccettazione).Format("%d/%m/%y"));
#endif
			return str;
		};
};


class CPrecedentiTree : public CXRecsetTree
{
  public:
		CPrecedentiTree(CRecordset* pSet, int nTag, int nIcon)
		   : CXRecsetTree(pSet, nTag, nIcon)
		{
		};
		long GetCode()
		{
			CVerbaliSet* pSet = (CVerbaliSet*)m_pSet;
      switch(pSet->m_TipoVerbale)
      {
      case VERB_IN_CONCESSIONE:
				m_nIcon = 1;
        break;
      case VERB_NON_IN_CONCESSIONE:
			case VERB_NC_PROVE_DI_CARICO:
			case VERB_NC_CONGL_BITUMINOSI:
			case VERB_NC_INERTI:
			case VERB_NC_MONITORAGGI:
			case VERB_NC_VARIE:
			case VERB_NC_GEOTECNICA :
			case VERB_NC_LINEE_VITA:
			case VERB_NC_INDAGINI_MURATURE:
			case VERB_NC_INDAGINI_CLS:
			case VERB_NC_MAT_METALLICI:
				m_nIcon = 2;
        break;
      case VERB_GEOLOGIA:
          m_nIcon = 5;
        break;
      }
     
			return ((CVerbaliSet*)m_pSet)->m_Codice;
		};
		CString GetLabel()
		{
			CVerbaliSet* pSet = (CVerbaliSet*)m_pSet;
      CString str;
      str.Format("V. %d/%d del %s", pSet->m_ProgressivoParziale, pSet->m_ProgressivoTotale, (pSet->m_DataAccettazione).Format("%d/%m/%y"));
			return str;
		};
};

class CGeologiaTree : public CXRecsetTree
{
  public:
		CGeologiaTree(CRecordset* pSet, int nTag, int nIcon)
		   : CXRecsetTree(pSet, nTag, nIcon)
		{
		};
		long GetCode()
		{
			CVerbaliSet* pSet = (CVerbaliSet*)m_pSet;
      m_nIcon = 5;
			return ((CVerbaliSet*)m_pSet)->m_Codice;
		};
		CString GetLabel()
		{
			CVerbaliSet* pSet = (CVerbaliSet*)m_pSet;
      CString str;
      str.Format("V. %d/%d del %s", pSet->m_ProgressivoParziale, pSet->m_ProgressivoTotale, (pSet->m_DataAccettazione).Format("%d/%m/%y"));
			return str;
		};
};


class CFattProformaTree : public CXRecsetTree
{
  public:
		CFattProformaTree(CRecordset* pSet, int nTag, int nIcon)
		   : CXRecsetTree(pSet, nTag, nIcon)
		{
		};
		long GetCode()
		{
			CVerbaliSet* pSet = (CVerbaliSet*)m_pSet;
      switch(pSet->m_TipoVerbale)
      {
      case VERB_IN_CONCESSIONE:
				m_nIcon = 1;
        break;
      case VERB_NON_IN_CONCESSIONE:
			case VERB_NC_PROVE_DI_CARICO:
			case VERB_NC_CONGL_BITUMINOSI:
			case VERB_NC_INERTI:
			case VERB_NC_MONITORAGGI:
			case VERB_NC_VARIE:
			case VERB_NC_GEOTECNICA :
			case VERB_NC_LINEE_VITA:
			case VERB_NC_INDAGINI_MURATURE:
			case VERB_NC_INDAGINI_CLS:
			case VERB_NC_MAT_METALLICI:
				m_nIcon = 2;
        break;
      case VERB_GEOLOGIA:
          m_nIcon = 5;
        break;
      }
     
			return ((CVerbaliSet*)m_pSet)->m_Codice;
		};
		CString GetLabel()
		{
			CVerbaliSet* pSet = (CVerbaliSet*)m_pSet;
      CString str;
      str.Format("V. %d/%d del %s", pSet->m_ProgressivoParziale, pSet->m_ProgressivoTotale, (pSet->m_DataAccettazione).Format("%d/%m/%y"));
			return str;
		};
};
/////////////////////////////////////////////////////////////////////////////
// CVerbaliTreeCtrl

CVerbaliTreeCtrl::CVerbaliTreeCtrl()
{
}

CVerbaliTreeCtrl::~CVerbaliTreeCtrl()
{
  m_HTreeUltimoMese = NULL;
  m_HTreePrecedenti = NULL;
}


BEGIN_MESSAGE_MAP(CVerbaliTreeCtrl, CXTreeCtrl)
	//{{AFX_MSG_MAP(CVerbaliTreeCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVerbaliTreeCtrl message handlers

void CVerbaliTreeCtrl::SetDoc(CDocument *pDoc)
{
  m_pDoc = (CWinSigmaDoc*)pDoc;
	m_pfnCompare = Sort;
}

void CVerbaliTreeCtrl::PopulateTree(void)
{
	CXRecsetTree* pXTree;

 	SelectItem(NULL);
  /*----- Verbali per cui sono state fatte fatture proforma ----*/
  m_hTreeFattureProforma = InsertItem(TREELABEL_VERBALIFATTPROFORMA, 4, 4);
  pXTree = new CFattProformaTree(m_pDoc->m_pVerbaliFattProforma, TREEITEM_VERBFATTPROFORMA, 1);
  SetItemData(m_hTreeFattureProforma, (DWORD)pXTree);
  Populate(TREELABEL_VERBALIFATTPROFORMA, -1);
	/*----- Precedenti all'ultimo mese -----*/
  m_HTreePrecedenti = InsertItem(TREELABEL_VERBALIPRECEDENTI, 3, 3);
	pXTree = new CPrecedentiTree(m_pDoc->m_pVerbaliPrecedentiSet, TREEITEM_VERBALIPRECEDENTI, 1);
	SetItemData(m_HTreePrecedenti, (DWORD)pXTree);
	Populate(TREELABEL_VERBALIPRECEDENTI, -1);
	/*----- Ultimo mese -----*/
	m_HTreeUltimoMese = InsertItem(TREELABEL_VERBALIULTIMOMESE, 0, 0);
  pXTree = new CUltimoMeseTree(m_pDoc->m_pVerbaliUltimoMeseSet, TREEITEM_VERBALIULTIMOMESE, 1);
	SetItemData(m_HTreeUltimoMese, (DWORD)pXTree);
	Populate(TREELABEL_VERBALIULTIMOMESE, -1);
//  SelectItem(m_HTreeUltimoMese);
}

void CVerbaliTreeCtrl::SelectedTree(int nSelected)
{
  m_pDoc->m_nSelectedTreeVerbali = nSelected;
}


int CVerbaliTreeCtrl::Sort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
  if(lParam1 < lParam2)
	  return -1;
	else if(lParam1 > lParam2)
	  return 1;
	else return 0;
}

