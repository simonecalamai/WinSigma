#include "AziendeSet.h"
#include "OperatoriSet.h"
#include "TipiMaterialeSet.h"
#include "TipiPagamentoSet.h"
#include "CondizioniPagamentoSet.h"
#include "MarchiSet.h"
#include "TipiCertificatoSet.h"
#include "ListiniSet.h"
#include "CategorieSet.h"
#include "ServiziListinoSet.h"
#include "VerbaliSet.h"
#include "SerieSet.h"
#include "ProviniSet.h"
#include "SerieProviniSet.h"
#include "CertificatiSet.h"
#include "CertificatiVerbaliSet.h"
#include "ServiziErogatiSet.h"
#include "CategorieServiziSet.h"
#include "VerbaliServErogatiSet.h"
#include "FattureSet.h"

#define CLOSE_DELETE(pSet) if( pSet->IsOpen() ) pSet->Close(); delete pSet

class CAllTables
{
public:
	CAziendeSet* m_pAziendeSet;
	COperatoriSet* m_pOperatoriSet;
	CTipiMaterialeSet* m_pTipiMaterialeSet;
	CTipiPagamentoSet* m_pTipiPagamentoSet;
	CCondizioniPagamentoSet* m_pCondizioniPagamentoSet;
	CMarchiSet* m_pMarchiSet;
	CTipiCertificatoSet* m_pTipiCertificatoSet;
	CListiniSet* m_pListiniSet;
	CCategorieSet* m_pCategorieSet;
	CServiziListinoSet* m_pServiziListinoSet;
	CVerbaliSet* m_pVerbaliSet;
	CSerieSet* m_pSerieSet;
	CProviniSet* m_pProviniSet;
	CSerieProviniSet* m_pSerieProviniSet;
	CCertificatiSet* m_pCertificatiSet;
	CCertificatiVerbaliSet* m_pCertificatiVerbaliSet;
	CServiziErogatiSet* m_pServiziErogatiSet;
	CCategorieServiziSet* m_pCategorieServiziSet;
	CVerbaliServErogatiSet* m_pVerbaliServErogatiSet;
	CFattureSet* m_pFattureSet;

	CAllTables::CAllTables(CDatabase* pDatabase = NULL)
		{
		m_pAziendeSet							= new CAziendeSet(pDatabase);
		m_pOperatoriSet						= new COperatoriSet(pDatabase);
		m_pTipiMaterialeSet				= new CTipiMaterialeSet(pDatabase);
		m_pTipiPagamentoSet				= new CTipiPagamentoSet(pDatabase);
		m_pCondizioniPagamentoSet				= new CCondizioniPagamentoSet(pDatabase);
		m_pMarchiSet							= new CMarchiSet(pDatabase);
		m_pTipiCertificatoSet			= new CTipiCertificatoSet(pDatabase);
		m_pListiniSet							= new CListiniSet(pDatabase);
		m_pCategorieSet						= new CCategorieSet(pDatabase);
		m_pServiziListinoSet			= new CServiziListinoSet(pDatabase);
		m_pVerbaliSet							= new CVerbaliSet(pDatabase);
		m_pSerieSet								= new CSerieSet(pDatabase);
		m_pProviniSet							= new CProviniSet(pDatabase);
		m_pSerieProviniSet				= new CSerieProviniSet(pDatabase);
		m_pCertificatiSet					= new CCertificatiSet(pDatabase);
		m_pCertificatiVerbaliSet	= new CCertificatiVerbaliSet(pDatabase);
		m_pServiziErogatiSet			= new CServiziErogatiSet(pDatabase);
		m_pCategorieServiziSet		= new CCategorieServiziSet(pDatabase);
		m_pVerbaliServErogatiSet	= new CVerbaliServErogatiSet(pDatabase);
		m_pFattureSet							= new CFattureSet(pDatabase);
		}

	CAllTables::~CAllTables()
		{
		CLOSE_DELETE(m_pAziendeSet);
		CLOSE_DELETE(m_pOperatoriSet);
		CLOSE_DELETE(m_pTipiMaterialeSet);
		CLOSE_DELETE(m_pTipiPagamentoSet);
		CLOSE_DELETE(m_pCondizioniPagamentoSet);
		CLOSE_DELETE(m_pMarchiSet);
		CLOSE_DELETE(m_pTipiCertificatoSet);
		CLOSE_DELETE(m_pListiniSet);
		CLOSE_DELETE(m_pCategorieSet);
		CLOSE_DELETE(m_pServiziListinoSet);
		CLOSE_DELETE(m_pVerbaliSet);
		CLOSE_DELETE(m_pSerieSet);
		CLOSE_DELETE(m_pProviniSet);
		CLOSE_DELETE(m_pSerieProviniSet);
		CLOSE_DELETE(m_pCertificatiSet);
		CLOSE_DELETE(m_pCertificatiVerbaliSet);
		CLOSE_DELETE(m_pServiziErogatiSet);
		CLOSE_DELETE(m_pCategorieServiziSet);
		CLOSE_DELETE(m_pVerbaliServErogatiSet);
		CLOSE_DELETE(m_pFattureSet);
		}
};