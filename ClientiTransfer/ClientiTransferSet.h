// ClientiTransferSet.h : interface of the CClientiTransferSet class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTITRANSFERSET_H__86068F10_2FC1_11D8_B754_00C026108782__INCLUDED_)
#define AFX_CLIENTITRANSFERSET_H__86068F10_2FC1_11D8_B754_00C026108782__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CClienti
{
public:
	CClienti()
	{
		memset( (void*)this, 0, sizeof(*this) );
	};

	char m_CODICE[6];
	char m_RAGSOCIALE[36];
	char m_ESTENSIONE[21];
	char m_INDIRIZZO[36];
	char m_DESCITTA[26];
	char m_PROV[3];
	char m_CAP[6];
	char m_IVA[12];
	double m_IMPORPAGA;
	double m_TOTIMPON;
	double m_TOTIVA;
	double m_TOTBOLLI;
	char m_RICHIED[2];
	char m_FATTURATO[2];
	char m_IMPRESA[2];
	char m_CODPAGA[3];
	char m_BANCAAPP[37];
	double m_SCONTO;
	char m_GENSPE[36];
	char m_INDSPE[31];
	char m_DESCITS[26];
	char m_PROVS[3];
	char m_CAPS[6];
	char m_NTELEF[16];
	char m_TIPOCLI[3];
	char m_RIBA[4];
	char m_CODFIS[17];
	char m_CENTRO[3];
	char m_CATEG[3];
	char m_SETTORE[6];
	double m_NFATTURE;
	char m_RAGGR_VERB[2];
	double m_NINSOLUTI;
	double m_SCOPERTO;
	DBDATE m_DATA_INS;
	char m_ABI[6];
	char m_CAB[6];


BEGIN_COLUMN_MAP(CClienti)
		COLUMN_ENTRY_TYPE(1, DBTYPE_STR, m_CODICE)
		COLUMN_ENTRY_TYPE(2, DBTYPE_STR, m_RAGSOCIALE)
		COLUMN_ENTRY_TYPE(3, DBTYPE_STR, m_ESTENSIONE)
		COLUMN_ENTRY_TYPE(4, DBTYPE_STR, m_INDIRIZZO)
		COLUMN_ENTRY_TYPE(5, DBTYPE_STR, m_DESCITTA)
		COLUMN_ENTRY_TYPE(6, DBTYPE_STR, m_PROV)
		COLUMN_ENTRY_TYPE(7, DBTYPE_STR, m_CAP)
		COLUMN_ENTRY_TYPE(8, DBTYPE_STR, m_IVA)
		COLUMN_ENTRY_TYPE(9, DBTYPE_R8, m_IMPORPAGA)
		COLUMN_ENTRY_TYPE(10, DBTYPE_R8, m_TOTIMPON)
		COLUMN_ENTRY_TYPE(11, DBTYPE_R8, m_TOTIVA)
		COLUMN_ENTRY_TYPE(12, DBTYPE_R8, m_TOTBOLLI)
		COLUMN_ENTRY_TYPE(13, DBTYPE_STR, m_RICHIED)
		COLUMN_ENTRY_TYPE(14, DBTYPE_STR, m_FATTURATO)
		COLUMN_ENTRY_TYPE(15, DBTYPE_STR, m_IMPRESA)
		COLUMN_ENTRY_TYPE(16, DBTYPE_STR, m_CODPAGA)
		COLUMN_ENTRY_TYPE(17, DBTYPE_STR, m_BANCAAPP)
		COLUMN_ENTRY_TYPE(18, DBTYPE_R8, m_SCONTO)
		COLUMN_ENTRY_TYPE(19, DBTYPE_STR, m_GENSPE)
		COLUMN_ENTRY_TYPE(20, DBTYPE_STR, m_INDSPE)
		COLUMN_ENTRY_TYPE(21, DBTYPE_STR, m_DESCITS)
		COLUMN_ENTRY_TYPE(22, DBTYPE_STR, m_PROVS)
		COLUMN_ENTRY_TYPE(23, DBTYPE_STR, m_CAPS)
		COLUMN_ENTRY_TYPE(24, DBTYPE_STR, m_NTELEF)
		COLUMN_ENTRY_TYPE(25, DBTYPE_STR, m_TIPOCLI)
		COLUMN_ENTRY_TYPE(26, DBTYPE_STR, m_RIBA)
		COLUMN_ENTRY_TYPE(27, DBTYPE_STR, m_CODFIS)
		COLUMN_ENTRY_TYPE(28, DBTYPE_STR, m_CENTRO)
		COLUMN_ENTRY_TYPE(29, DBTYPE_STR, m_CATEG)
		COLUMN_ENTRY_TYPE(30, DBTYPE_STR, m_SETTORE)
		COLUMN_ENTRY_TYPE(31, DBTYPE_R8, m_NFATTURE)
		COLUMN_ENTRY_TYPE(32, DBTYPE_STR, m_RAGGR_VERB)
		COLUMN_ENTRY_TYPE(33, DBTYPE_R8, m_NINSOLUTI)
		COLUMN_ENTRY_TYPE(34, DBTYPE_R8, m_SCOPERTO)
		COLUMN_ENTRY_TYPE(35, DBTYPE_DBDATE, m_DATA_INS)
		COLUMN_ENTRY_TYPE(36, DBTYPE_STR, m_ABI)
		COLUMN_ENTRY_TYPE(37, DBTYPE_STR, m_CAB)
END_COLUMN_MAP()

};

class CClientiTransferSet : public CCommand<CAccessor<CClienti> >
{
public:

	HRESULT Open()
	{
		CDataSource db;
		CSession	session;
		HRESULT		hr;

		CDBPropSet	dbinit(DBPROPSET_DBINIT);
		dbinit.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
		dbinit.AddProperty(DBPROP_INIT_PROMPT, (short)4);
		dbinit.AddProperty(DBPROP_INIT_PROVIDERSTRING, "DSN=File di dBASE;DBQ=c:\\LAVORO\\SIGMA\\CLIENTI;DefaultDir=c:\\LAVORO\\SIGMA\\CLIENTI;DriverId=533;FILEDSN=C:\\Programmi\\File comuni\\ODBC\\Data Sources\\File di dBASE (not sharable).dsn;MaxBufferSize=2048;PageTimeout=5;");
		dbinit.AddProperty(DBPROP_INIT_LCID, (long)1040);

		hr = db.OpenWithServiceComponents("MSDASQL.1", &dbinit);
		if (FAILED(hr))
			return hr;

		hr = session.Open(db);
		if (FAILED(hr))
			return hr;

		CDBPropSet	propset(DBPROPSET_ROWSET);
		propset.AddProperty(DBPROP_CANFETCHBACKWARDS, true);
		propset.AddProperty(DBPROP_IRowsetScroll, true);
		propset.AddProperty(DBPROP_IRowsetChange, true);
		propset.AddProperty(DBPROP_UPDATABILITY, DBPROPVAL_UP_CHANGE | DBPROPVAL_UP_INSERT | DBPROPVAL_UP_DELETE );

		hr = CCommand<CAccessor<CClienti> >::Open(session, "SELECT * FROM clienti", &propset);
		if (FAILED(hr))
			return hr;

		return MoveNext();
	}

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTITRANSFERSET_H__86068F10_2FC1_11D8_B754_00C026108782__INCLUDED_)

