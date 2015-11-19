// ModificaCertificatoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "ModificaCertificatoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModificaCertificatoDlg dialog


CModificaCertificatoDlg::CModificaCertificatoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModificaCertificatoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModificaCertificatoDlg)
	m_DataEmissione = 0;
	m_nNumDocumento = 0;
	m_nNumPagine = 0;
	m_strVerbale = _T("");
	m_bAbilitaCalcolo = FALSE;
	m_bInserimento = FALSE;
	m_bEmenda = FALSE;
	//}}AFX_DATA_INIT
}


void CModificaCertificatoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModificaCertificatoDlg)
	DDX_Control(pDX, IDC_CHECK_CALCOLO_PAGINE, m_BtnCalcolo);
	DDX_Control(pDX, IDC_CHECK_NO_CALCOLO, m_BtnInserimento);
	DDX_Control(pDX, IDC_EDIT_NUMERO, m_EdtNumero);
	DDX_Control(pDX, IDC_DATE_EMISSIONE, m_DataCtrl);
	DDX_Control(pDX, IDC_CHECK_EMENDAMENTO, m_BtnEmenda);
	DDX_Control(pDX, IDC_EDIT_PAGINE, m_EdtPagine);
	DDX_DateTimeCtrl(pDX, IDC_DATE_EMISSIONE, m_DataEmissione);
	DDX_Text(pDX, IDC_EDIT_NUMERO, m_nNumDocumento);
	DDX_Text(pDX, IDC_EDIT_PAGINE, m_nNumPagine);
	DDX_Text(pDX, IDC_EDIT_VERBALE, m_strVerbale);
	DDX_Check(pDX, IDC_CHECK_CALCOLO_PAGINE, m_bAbilitaCalcolo);
	DDX_Check(pDX, IDC_CHECK_NO_CALCOLO, m_bInserimento);
	DDX_Check(pDX, IDC_CHECK_EMENDAMENTO, m_bEmenda);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModificaCertificatoDlg, CDialog)
	//{{AFX_MSG_MAP(CModificaCertificatoDlg)
	ON_BN_CLICKED(IDC_CHECK_CALCOLO_PAGINE, OnCheckCalcoloPagine)
	ON_BN_CLICKED(IDC_CHECK_NO_CALCOLO, OnCheckNoCalcolo)
	ON_BN_CLICKED(IDC_CHECK_EMENDAMENTO, OnCheckEmendamento)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModificaCertificatoDlg message handlers

BOOL CModificaCertificatoDlg::ValidateDate()
{
	CString str;
	if ( !UpdateData() )
		return FALSE;
	
	CTime inizioAnno(m_DataEmissione.GetYear(), 1,1,1,1,1,1);
	CTime inizioAnnoSuccessivo(m_DataEmissione.GetYear()+1, 1,1,1,1,1,1);
	CString query, rangeData, queryJoin, dataScelta, dataMinima, dataMassima;
	CString queryNum, queryCod, queryCoerenza1, queryCoerenza2, strErrorMessage;
	
	dataScelta = m_DataEmissione.Format("%Y-%m-%d");
	dataMinima = inizioAnno.Format("%Y-%m-%d");
	dataMassima = inizioAnnoSuccessivo.Format("%Y-%m-%d");

	queryJoin = "VERBALI.Codice = CERTIFICATI.Verbale";
	rangeData.Format("CERTIFICATI.DataEmissione >= '%s' AND CERTIFICATI.DataEmissione < '%s'", dataMinima, dataMassima);
	queryCod.Format("CERTIFICATI.Codice != %d", m_nCodCertificato);
	queryNum.Format("CERTIFICATI.NumeroCertificato = %d", m_nNumDocumento);
	
	//Verifica dell'unicità del codice scelto///
	query.Format("%s AND %s AND %s AND %s",queryJoin, rangeData, queryCod, queryNum);
	m_pCertVerbSet->m_strFilter = query;
	m_pCertVerbSet->Requery();
	if(!m_pCertVerbSet->IsEOF())
		{
		strErrorMessage.Format("Il 'Numero certificato' scelto è già assegnato al seguente documento:\n\nCertificato N° %d del %s",m_pCertVerbSet->m_NumeroCertificato, m_pCertVerbSet->m_DataEmissione.Format("%d/%m/%Y"));
		str.Format("\n\nRif. V.A. N° %d/%d del %s",m_pCertVerbSet->m_ProgressivoParziale, m_pCertVerbSet->m_ProgressivoTotale, m_pCertVerbSet->m_DataAccettazione.Format("%d/%m/%Y"));
		strErrorMessage = "OPERAZIONE NON COSENTITA!\n\n" + strErrorMessage + str;
		AfxMessageBox(strErrorMessage);
		return FALSE;
		}

	//Verifica della coerenza fra le date ed il numero impostato
	queryCoerenza1.Format("CERTIFICATI.NumeroCertificato > %d AND CERTIFICATI.DataEmissione < '%s'", m_nNumDocumento, dataScelta);
	queryCoerenza2.Format("CERTIFICATI.NumeroCertificato < %d AND CERTIFICATI.DataEmissione > '%s'", m_nNumDocumento, dataScelta);
	query.Format("%s AND %s AND (%s OR %s)",queryJoin, rangeData, queryCoerenza1, queryCoerenza2);
	m_pCertVerbSet->m_strFilter = query;
	m_pCertVerbSet->Requery();
	if(!m_pCertVerbSet->IsEOF())
		{
		strErrorMessage.Format("Il 'Numero certificato' e la 'Data emissione' scelti sono in conflitto con il seguente documento:\n\nCertificato N° %d del %s",m_pCertVerbSet->m_NumeroCertificato, m_pCertVerbSet->m_DataEmissione.Format("%d/%m/%Y"));
		str.Format("\n\nRif. V.A. N° %d/%d del %s",m_pCertVerbSet->m_ProgressivoParziale, m_pCertVerbSet->m_ProgressivoTotale, m_pCertVerbSet->m_DataAccettazione.Format("%d/%m/%Y"));
		strErrorMessage = "OPERAZIONE NON COSENTITA!\n\n" + strErrorMessage + str;
		AfxMessageBox(strErrorMessage);
		return FALSE;
		}
	
	return TRUE;
}

void CModificaCertificatoDlg::OnOK() 
{
	if( ValidateDate() )
		CDialog::OnOK();
}

void CModificaCertificatoDlg::OnCheckCalcoloPagine() 
{
	UpdateData();
	m_EdtPagine.EnableWindow(!m_bAbilitaCalcolo);
	m_bInserimento = !m_bAbilitaCalcolo;
	UpdateData(FALSE);

}


BOOL CModificaCertificatoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	m_bAbilitaCalcolo = m_pCertVerbSet->IsFieldNull(&m_pCertVerbSet->m_NumeroPagine);
	if(m_pCertVerbSet->IsFieldNull(&m_pCertVerbSet->m_EmendatoDa))
		m_BtnEmenda.EnableWindow(TRUE);

	CString str;
	str.Format("%d/%d", m_pCertVerbSet->m_ProgressivoParziale, m_pCertVerbSet->m_ProgressivoTotale);
	m_strVerbale			= str;
	m_DataEmissione		= m_pCertVerbSet->m_DataEmissione;
	m_nNumDocumento		= m_pCertVerbSet->m_NumeroCertificato;
	m_nCodCertificato = m_pCertVerbSet->m_CodiceCertificato;

	if( !m_bAbilitaCalcolo )
		m_nNumPagine = m_pCertVerbSet->m_NumeroPagine;

	m_EdtPagine.EnableWindow(!m_bAbilitaCalcolo);
	m_bInserimento = !m_bAbilitaCalcolo;


	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CModificaCertificatoDlg::OnCheckNoCalcolo() 
{
	UpdateData();
	m_EdtPagine.EnableWindow(m_bInserimento);
	m_bAbilitaCalcolo = !m_bInserimento;
	UpdateData(FALSE);
}

void CModificaCertificatoDlg::OnCheckEmendamento() 
{
	m_bEmenda = m_BtnEmenda.GetCheck();
	UpdateData(!m_bEmenda);
	if(m_bEmenda)
		{
		m_BtnInserimento.SetCheck(FALSE);
		m_BtnCalcolo.SetCheck(TRUE);
		}
	m_BtnCalcolo.EnableWindow(!m_bEmenda);
	m_bAbilitaCalcolo = !m_bEmenda;
	m_EdtPagine.EnableWindow(!m_bEmenda && m_bInserimento);
	m_DataCtrl.EnableWindow(!m_bEmenda);
	m_EdtNumero.EnableWindow(!m_bEmenda);
	m_BtnInserimento.EnableWindow(!m_bEmenda);
	
}
