// RipartizioneImponibileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "RipartizioneImponibileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRipartizioneImponibileDlg dialog


CRipartizioneImponibileDlg::CRipartizioneImponibileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRipartizioneImponibileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRipartizioneImponibileDlg)
	m_strCodice = _T("");
	m_strIndirizzo = _T("");
	m_strRagioneSociale = _T("");
	m_strImponibile = _T("");
	m_dProveCarico = 0.0f;
	m_dConglomeratiBituminosi = 0.0f;
	m_dInerti = 0.0f;
	m_dMonitoraggi = 0.0f;
	m_dLineeVita = 0.0f;
	m_dIndaginiMurature = 0.0f;
	m_dIndaginiCLS = 0.0f;
	m_dMaterialiMetallici = 0.0f;
	m_dVarie = 0.0f;
	m_dGeotecnica = 0.0f;
	m_dPercProveCarico = 0.0f;
	m_dPercConglomeratiBituminosi = 0.0f;
	m_dPercInerti = 0.0f;
	m_dPercMonitoraggi = 0.0f;
	m_dPercLineeVita = 0.0f;
	m_dPercIndaginiMurature = 0.0f;
	m_dPercIndaginiCLS = 0.0f;
	m_dPercMaterialiMetallici = 0.0f;
	m_dPercVarie = 0.0f;
	m_dPercGeotecnica = 0.0f;
	//}}AFX_DATA_INIT
	m_nTipoVerbale = -1;
	m_strRipartizioneImponibile = _T("");
}


void CRipartizioneImponibileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRipartizioneImponibileDlg)
	DDX_Text(pDX, IDC_EDIT_CODICE, m_strCodice);
	DDX_Text(pDX, IDC_EDIT_INDIRIZZO, m_strIndirizzo);
	DDX_Text(pDX, IDC_EDIT_RAGIONE_SOCIALE, m_strRagioneSociale);
	DDX_Text(pDX, IDC_EDIT_IMPONIBILE, m_strImponibile);
	DDX_Text(pDX, IDC_EDIT_IMP_PROVEDICARICO, m_dProveCarico);
	DDX_Text(pDX, IDC_EDIT_IMP_CONGLOMERATIBITUMINOSI, m_dConglomeratiBituminosi);
	DDX_Text(pDX, IDC_EDIT_IMP_INERTI, m_dInerti);
	DDX_Text(pDX, IDC_EDIT_IMP_MONITORAGGI, m_dMonitoraggi);
	DDX_Text(pDX, IDC_EDIT_IMP_LINEEVITA, m_dLineeVita);
	DDX_Text(pDX, IDC_EDIT_IMP_INDAGINIMURATURE, m_dIndaginiMurature);
	DDX_Text(pDX, IDC_EDIT_IMP_INDAGINICLS, m_dIndaginiCLS);
	DDX_Text(pDX, IDC_EDIT_IMP_MATERIALIMETALLICI, m_dMaterialiMetallici);
	DDX_Text(pDX, IDC_EDIT_IMP_VARIE, m_dVarie);
	DDX_Text(pDX, IDC_EDIT_IMP_GEOTECNICA, m_dGeotecnica);
	DDX_Text(pDX, IDC_EDIT_PERC_PROVEDICARICO, m_dPercProveCarico);
	DDX_Text(pDX, IDC_EDIT_PERC_CONGLOMERATIBITUMINOSI, m_dPercConglomeratiBituminosi);
	DDX_Text(pDX, IDC_EDIT_PERC_INERTI, m_dPercInerti);
	DDX_Text(pDX, IDC_EDIT_PERC_MONITORAGGI, m_dPercMonitoraggi);
	DDX_Text(pDX, IDC_EDIT_PERC_LINEEVITA, m_dPercLineeVita);
	DDX_Text(pDX, IDC_EDIT_PERC_INDAGINIMURATURE, m_dPercIndaginiMurature);
	DDX_Text(pDX, IDC_EDIT_PERC_INDAGINICLS, m_dPercIndaginiCLS);
	DDX_Text(pDX, IDC_EDIT_PERC_MATERIALIMETALLICI, m_dPercMaterialiMetallici);
	DDX_Text(pDX, IDC_EDIT_PERC_VARIE, m_dPercVarie);
	DDX_Text(pDX, IDC_EDIT_PERC_GEOTECNICA, m_dPercGeotecnica);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRipartizioneImponibileDlg, CDialog)
	//{{AFX_MSG_MAP(CRipartizioneImponibileDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRipartizioneImponibileDlg message handlers

BOOL CRipartizioneImponibileDlg::OnInitDialog() 
{
	switch(m_nTipoVerbale)
	{
		case -1:
		default:
			break;

		case VERB_NC_PROVE_DI_CARICO:
			break;

		case VERB_NC_CONGL_BITUMINOSI:
			break;

		case VERB_NC_INERTI:
			break;

		case VERB_NC_MONITORAGGI:
			break;

		case VERB_NC_VARIE:
			break;

		case VERB_NC_GEOTECNICA:
			break;

		case VERB_NC_LINEE_VITA:
			break;

		case VERB_NC_INDAGINI_MURATURE:
			break;

		case VERB_NC_INDAGINI_CLS:
			break;

		case VERB_NC_MAT_METALLICI:
			break;

	}
  UpdateData(FALSE);
	return FALSE;
}

void CRipartizioneImponibileDlg::OnOK() 
{
	m_strRipartizioneImponibile = "prova";
	CDialog::OnOK();
}
