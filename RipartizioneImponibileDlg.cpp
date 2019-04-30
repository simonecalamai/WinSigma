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
	m_strRagioneSociale = _T("");
	m_strCodice = _T("");
	m_strIndirizzo = _T("");
	m_strImponibile = _T("");
	m_strImponibileScontato = _T("");
	m_strTipoVerbale = _T("");
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
	m_dResiduo = 0.0f;
	m_nPercProveCarico = 0;
	m_nPercConglomeratiBituminosi = 0;
	m_nPercInerti = 0;
	m_nPercMonitoraggi = 0;
	m_nPercLineeVita = 0;
	m_nPercIndaginiMurature = 0;
	m_nPercIndaginiCLS = 0;
	m_nPercMaterialiMetallici = 0;
	m_nPercVarie = 0;
	m_nPercGeotecnica = 0;
	m_nPercResiduo = 0;
	//}}AFX_DATA_INIT
	m_nTipoVerbale = -1;
	m_strRipartizioneImponibile = _T("");
	m_dImponibileScontato = 0.0f;

	for(int i = 0; i < NCATEGORIE; i++)
	{
		m_arPerc[i] = 0;
		m_arImpo[i] = 0.0f;
	}
	m_nTotPerc = 0;
	m_dTotImpo = 0.0f;
}


void CRipartizioneImponibileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRipartizioneImponibileDlg)
	DDX_Control(pDX, IDC_EDIT_PERC_PROVEDICARICO, m_editPercProveCarico);
	DDX_Control(pDX, IDC_EDIT_PERC_CONGLOMERATIBITUMINOSI, m_editPercConglomeratiBituminosi);
	DDX_Control(pDX, IDC_EDIT_PERC_INERTI, m_editPercInerti);
	DDX_Control(pDX, IDC_EDIT_PERC_MONITORAGGI, m_editPercMonitoraggi);
	DDX_Control(pDX, IDC_EDIT_PERC_LINEEVITA, m_editPercLineeVita);
	DDX_Control(pDX, IDC_EDIT_PERC_INDAGINIMURATURE, m_editPercIndaginiMurature);
	DDX_Control(pDX, IDC_EDIT_PERC_INDAGINICLS, m_editPercIndaginiCLS);
	DDX_Control(pDX, IDC_EDIT_PERC_MATERIALIMETALLICI, m_editPercMaterialiMetallici);
	DDX_Control(pDX, IDC_EDIT_PERC_VARIE, m_editPercVarie);
	DDX_Control(pDX, IDC_EDIT_PERC_GEOTECNICA, m_editPercGeotecnica);
	DDX_Control(pDX, IDC_EDIT_PERC_RESIDUO, m_editPercResiduo);

	DDX_Text(pDX, IDC_EDIT_RAGIONE_SOCIALE, m_strRagioneSociale);
	DDX_Text(pDX, IDC_EDIT_CODICE, m_strCodice);
	DDX_Text(pDX, IDC_EDIT_INDIRIZZO, m_strIndirizzo);
	DDX_Text(pDX, IDC_EDIT_IMPONIBILE, m_strImponibileScontato);
	DDX_Text(pDX, IDC_EDIT_TIPO_VERBALE, m_strTipoVerbale);
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
	DDX_Text(pDX, IDC_EDIT_IMP_RESIDUO, m_dResiduo);

	DDX_Text(pDX, IDC_EDIT_PERC_PROVEDICARICO, m_nPercProveCarico);
	DDV_MinMaxInt(pDX, m_nPercProveCarico, 0, 100);
	DDX_Text(pDX, IDC_EDIT_PERC_CONGLOMERATIBITUMINOSI, m_nPercConglomeratiBituminosi);
	DDV_MinMaxInt(pDX, m_nPercConglomeratiBituminosi, 0, 100);
	DDX_Text(pDX, IDC_EDIT_PERC_INERTI, m_nPercInerti);
	DDV_MinMaxInt(pDX, m_nPercInerti, 0, 100);
	DDX_Text(pDX, IDC_EDIT_PERC_MONITORAGGI, m_nPercMonitoraggi);
	DDV_MinMaxInt(pDX, m_nPercMonitoraggi, 0, 100);
	DDX_Text(pDX, IDC_EDIT_PERC_LINEEVITA, m_nPercLineeVita);
	DDV_MinMaxInt(pDX, m_nPercLineeVita, 0, 100);
	DDX_Text(pDX, IDC_EDIT_PERC_INDAGINIMURATURE, m_nPercIndaginiMurature);
	DDV_MinMaxInt(pDX, m_nPercIndaginiMurature, 0, 100);
	DDX_Text(pDX, IDC_EDIT_PERC_INDAGINICLS, m_nPercIndaginiCLS);
	DDV_MinMaxInt(pDX, m_nPercIndaginiCLS, 0, 100);
	DDX_Text(pDX, IDC_EDIT_PERC_MATERIALIMETALLICI, m_nPercMaterialiMetallici);
	DDV_MinMaxInt(pDX, m_nPercMaterialiMetallici, 0, 100);
	DDX_Text(pDX, IDC_EDIT_PERC_VARIE, m_nPercVarie);
	DDV_MinMaxInt(pDX, m_nPercVarie, 0, 100);
	DDX_Text(pDX, IDC_EDIT_PERC_GEOTECNICA, m_nPercGeotecnica);
	DDV_MinMaxInt(pDX, m_nPercGeotecnica, 0, 100);
	DDX_Text(pDX, IDC_EDIT_PERC_RESIDUO, m_nPercResiduo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRipartizioneImponibileDlg, CDialog)
	//{{AFX_MSG_MAP(CRipartizioneImponibileDlg)
	ON_EN_KILLFOCUS(IDC_EDIT_PERC_PROVEDICARICO, OnKillfocusEditPercProvedicarico)
	ON_EN_KILLFOCUS(IDC_EDIT_PERC_CONGLOMERATIBITUMINOSI, OnKillfocusEditPercConglomeratibituminosi)
	ON_EN_KILLFOCUS(IDC_EDIT_PERC_GEOTECNICA, OnKillfocusEditPercGeotecnica)
	ON_EN_KILLFOCUS(IDC_EDIT_PERC_INDAGINICLS, OnKillfocusEditPercIndaginicls)
	ON_EN_KILLFOCUS(IDC_EDIT_PERC_INDAGINIMURATURE, OnKillfocusEditPercIndaginimurature)
	ON_EN_KILLFOCUS(IDC_EDIT_PERC_INERTI, OnKillfocusEditPercInerti)
	ON_EN_KILLFOCUS(IDC_EDIT_PERC_LINEEVITA, OnKillfocusEditPercLineevita)
	ON_EN_KILLFOCUS(IDC_EDIT_PERC_MATERIALIMETALLICI, OnKillfocusEditPercMaterialimetallici)
	ON_EN_KILLFOCUS(IDC_EDIT_PERC_MONITORAGGI, OnKillfocusEditPercMonitoraggi)
	ON_EN_KILLFOCUS(IDC_EDIT_PERC_VARIE, OnKillfocusEditPercVarie)
	ON_EN_CHANGE(IDC_EDIT_PERC_CONGLOMERATIBITUMINOSI, OnChangeEditPercConglomeratibituminosi)
	ON_EN_CHANGE(IDC_EDIT_PERC_GEOTECNICA, OnChangeEditPercGeotecnica)
	ON_EN_CHANGE(IDC_EDIT_PERC_INDAGINICLS, OnChangeEditPercIndaginicls)
	ON_EN_CHANGE(IDC_EDIT_PERC_INDAGINIMURATURE, OnChangeEditPercIndaginimurature)
	ON_EN_CHANGE(IDC_EDIT_PERC_INERTI, OnChangeEditPercInerti)
	ON_EN_CHANGE(IDC_EDIT_PERC_LINEEVITA, OnChangeEditPercLineevita)
	ON_EN_CHANGE(IDC_EDIT_PERC_MATERIALIMETALLICI, OnChangeEditPercMaterialimetallici)
	ON_EN_CHANGE(IDC_EDIT_PERC_MONITORAGGI, OnChangeEditPercMonitoraggi)
	ON_EN_CHANGE(IDC_EDIT_PERC_PROVEDICARICO, OnChangeEditPercProvedicarico)
	ON_EN_CHANGE(IDC_EDIT_PERC_VARIE, OnChangeEditPercVarie)
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
			m_strTipoVerbale = "Prove di Carico";
			break;
		case VERB_NC_CONGL_BITUMINOSI:
			m_strTipoVerbale = "Conglomerati Bituminosi";
			break;
		case VERB_NC_INERTI:
			m_strTipoVerbale = "Inerti";
			break;
		case VERB_NC_MONITORAGGI:
			m_strTipoVerbale = "Monitoraggi";
			break;
		case VERB_NC_VARIE:
			m_strTipoVerbale = "Varie";
			break;
		case VERB_NC_GEOTECNICA:
			m_strTipoVerbale = "Geotecnica";
			break;
		case VERB_NC_LINEE_VITA:
			m_strTipoVerbale = "Linee Vita";
			break;
		case VERB_NC_INDAGINI_MURATURE:
			m_strTipoVerbale = "Indagini Murature";
			break;
		case VERB_NC_INDAGINI_CLS:
			m_strTipoVerbale = "Indagini CLS";
			break;
		case VERB_NC_MAT_METALLICI:
			m_strTipoVerbale = "Materiali Metallici";
			break;
	}
	// verifica ripartizione imponibile
	if(m_strRipartizioneImponibile.IsEmpty())
	{
		// ripartizione non definita: tutti i parziali sono vuoti
		m_dResiduo = m_dImponibileScontato;
		m_nPercResiduo = 100;
	}
	else
	{
		// ripart. imponibile definita: analisi della ripartizione
		LoadRipartizione();
	}
  UpdateData(FALSE);
	return FALSE;
}

void CRipartizioneImponibileDlg::OnChangeEditPercProvedicarico() 
{
	CalcParte(PC);
}

void CRipartizioneImponibileDlg::OnKillfocusEditPercProvedicarico() 
{
	CalcParte(PC);
}

void CRipartizioneImponibileDlg::OnChangeEditPercConglomeratibituminosi() 
{
	CalcParte(CB);
}

void CRipartizioneImponibileDlg::OnKillfocusEditPercConglomeratibituminosi() 
{
	CalcParte(CB);
}

void CRipartizioneImponibileDlg::OnChangeEditPercGeotecnica() 
{
	CalcParte(GEO);
}

void CRipartizioneImponibileDlg::OnKillfocusEditPercGeotecnica() 
{
	CalcParte(GEO);
}

void CRipartizioneImponibileDlg::OnChangeEditPercIndaginicls() 
{
	CalcParte(IC);
}

void CRipartizioneImponibileDlg::OnKillfocusEditPercIndaginicls() 
{
	CalcParte(IC);
}

void CRipartizioneImponibileDlg::OnChangeEditPercIndaginimurature() 
{
	CalcParte(IM);
}

void CRipartizioneImponibileDlg::OnKillfocusEditPercIndaginimurature() 
{
	CalcParte(IM);
}

void CRipartizioneImponibileDlg::OnChangeEditPercInerti() 
{
	CalcParte(I);
}

void CRipartizioneImponibileDlg::OnKillfocusEditPercInerti() 
{
	CalcParte(I);
}

void CRipartizioneImponibileDlg::OnChangeEditPercLineevita() 
{
	CalcParte(LV);
}

void CRipartizioneImponibileDlg::OnKillfocusEditPercLineevita() 
{
	CalcParte(LV);
}

void CRipartizioneImponibileDlg::OnChangeEditPercMaterialimetallici() 
{
	CalcParte(MM);
}

void CRipartizioneImponibileDlg::OnKillfocusEditPercMaterialimetallici() 
{
	CalcParte(MM);
}

void CRipartizioneImponibileDlg::OnChangeEditPercMonitoraggi() 
{
	CalcParte(MO);
}

void CRipartizioneImponibileDlg::OnKillfocusEditPercMonitoraggi() 
{
	CalcParte(MO);
}

void CRipartizioneImponibileDlg::OnChangeEditPercVarie() 
{
	CalcParte(V);
}

void CRipartizioneImponibileDlg::OnKillfocusEditPercVarie() 
{
	CalcParte(V);
}


void CRipartizioneImponibileDlg::CalcParte(int id = -1) 
{
	CString strPerc = "";
	int nPerc = 0;

	switch(id)
	{
		case -1:
		default:
			break;

		case PC:
			m_editPercProveCarico.GetWindowText(strPerc);
			if(strPerc.IsEmpty())
				return;
			nPerc = atoi(strPerc);
			m_nPercProveCarico = nPerc;
			m_arPerc[PC] = m_nPercProveCarico; 
			m_dProveCarico = Percent(m_dImponibileScontato, m_nPercProveCarico);
			m_arImpo[PC] = m_dProveCarico;
			break;

		case CB:
			m_editPercConglomeratiBituminosi.GetWindowText(strPerc);
			if(strPerc.IsEmpty())
				return;
			nPerc = atoi(strPerc);
			m_nPercConglomeratiBituminosi = nPerc;
			m_arPerc[CB] = m_nPercConglomeratiBituminosi; 
			m_dConglomeratiBituminosi = Percent(m_dImponibileScontato, m_nPercConglomeratiBituminosi);
			m_arImpo[CB] = m_dConglomeratiBituminosi; 
			break;

		case I:
			m_editPercInerti.GetWindowText(strPerc);
			if(strPerc.IsEmpty())
				return;
			nPerc = atoi(strPerc);
			m_nPercInerti = nPerc;
			m_arPerc[I] = m_nPercInerti; 
			m_dInerti = Percent(m_dImponibileScontato, m_nPercInerti);
			m_arImpo[I] = m_dInerti; 
			break;

		case MO:
			m_editPercMonitoraggi.GetWindowText(strPerc);
			if(strPerc.IsEmpty())
				return;
			nPerc = atoi(strPerc);
			m_nPercMonitoraggi = nPerc;
			m_arPerc[MO] = m_nPercMonitoraggi; 
			m_dMonitoraggi = Percent(m_dImponibileScontato, m_nPercMonitoraggi);
			m_arImpo[MO] = m_dMonitoraggi; 
			break;

		case LV:
			m_editPercLineeVita.GetWindowText(strPerc);
			if(strPerc.IsEmpty())
				return;
			nPerc = atoi(strPerc);
			m_nPercLineeVita = nPerc;
			m_arPerc[LV] = m_nPercLineeVita; 
			m_dLineeVita = Percent(m_dImponibileScontato, m_nPercLineeVita);
			m_arImpo[LV] = m_dLineeVita; 
			break;

		case IM:
			m_editPercIndaginiMurature.GetWindowText(strPerc);
			if(strPerc.IsEmpty())
				return;
			nPerc = atoi(strPerc);
			m_nPercIndaginiMurature = nPerc;
			m_arPerc[IM] = m_nPercIndaginiMurature; 
			m_dIndaginiMurature = Percent(m_dImponibileScontato, m_nPercIndaginiMurature);
			m_arImpo[IM] = m_dIndaginiMurature; 
			break;

		case IC:
			m_editPercIndaginiCLS.GetWindowText(strPerc);
			if(strPerc.IsEmpty())
				return;
			nPerc = atoi(strPerc);
			m_nPercIndaginiCLS = nPerc;
			m_arPerc[IC] = m_nPercIndaginiCLS; 
			m_dIndaginiCLS = Percent(m_dImponibileScontato, m_nPercIndaginiCLS);
			m_arImpo[IC] = m_dIndaginiCLS; 
			break;

		case MM:
			m_editPercMaterialiMetallici.GetWindowText(strPerc);
			if(strPerc.IsEmpty())
				return;
			nPerc = atoi(strPerc);
			m_nPercMaterialiMetallici = nPerc;
			m_arPerc[MM] = m_nPercMaterialiMetallici; 
			m_dMaterialiMetallici = Percent(m_dImponibileScontato, m_nPercMaterialiMetallici);
			m_arImpo[MM] = m_dMaterialiMetallici; 
			break;

		case V:
			m_editPercVarie.GetWindowText(strPerc);
			if(strPerc.IsEmpty())
				return;
			nPerc = atoi(strPerc);
			m_nPercVarie = nPerc;
			m_arPerc[V] = m_nPercVarie; 
			m_dVarie = Percent(m_dImponibileScontato, m_nPercVarie);
			m_arImpo[V] = m_dVarie; 
			break;

		case GEO:
			m_editPercGeotecnica.GetWindowText(strPerc);
			if(strPerc.IsEmpty())
				return;
			nPerc = atoi(strPerc);
			m_nPercGeotecnica = nPerc;
			m_arPerc[GEO] = m_nPercGeotecnica; 
			m_dGeotecnica = Percent(m_dImponibileScontato, m_nPercGeotecnica);
			m_arImpo[GEO] = m_dGeotecnica; 
			break;
	}

	CalcTotali();

	UpdateData(FALSE);
}

double CRipartizioneImponibileDlg::Percent(double val, int perc)
{
	double dp = 0.0f;

	int n = (int)(100*val);
	dp = ((double)(n*perc))/100.0f;
	dp /= 100;

	return dp;
}

void CRipartizioneImponibileDlg::CalcTotali()
{
	// somma le percentuali e gli importi
	m_nTotPerc = 0;
	m_dTotImpo = 0.0f;
	for(int i = 0; i < NCATEGORIE; i++)
	{
		m_nTotPerc += m_arPerc[i];
		m_dTotImpo += m_arImpo[i];
	}

	m_nPercResiduo = 100 - m_nTotPerc;
	m_dResiduo = Percent(m_dImponibileScontato, m_nPercResiduo);
}

int CRipartizioneImponibileDlg::CalcolaRipartizione() 
{
	CString ar[NCATEGORIE];
	CString strRip = m_strRipartizioneImponibile;
	CString cs = "";
	int perc = 0;
	int pos = 0, i = 0;
	// scompone la stringa di ripartizione nei suoi elementi 
	// e li salva in un array
	while(pos >= 0)
	{
		pos = strRip.Find(';');
		if(pos > 0)
		{
			ar[i++] = strRip.Left(pos);
			strRip = strRip.Mid(pos+1);
		}
	}
	ar[i] = strRip;
	// determina le percentuali 
	for(i = 0; i < NCATEGORIE; i++)
	{
		perc = 0;
		pos = ar[i].Find('=');
		if(pos > 0)
		{
			cs = ar[i].Mid(pos+1);
			perc = atoi(cs);
		}
		switch(i)
		{
			case PC:
				m_nPercProveCarico = perc;
				m_dProveCarico = Percent(m_dImponibileScontato, perc);
				m_arPerc[PC] = perc;
				m_arImpo[PC] = m_dProveCarico;
				break;
			case CB:
				m_nPercConglomeratiBituminosi = perc;
				m_dConglomeratiBituminosi = Percent(m_dImponibileScontato, perc);
				m_arPerc[CB] = perc;
				m_arImpo[CB] = m_dConglomeratiBituminosi;
				break;
			case I:
				m_nPercInerti = perc;
				m_dInerti = Percent(m_dImponibileScontato, perc);
				m_arPerc[I] = perc;
				m_arImpo[I] = m_dInerti;
				break;	
			case MO:
				m_nPercMonitoraggi = perc;
				m_dMonitoraggi = Percent(m_dImponibileScontato, perc);
				m_arPerc[MO] = perc;
				m_arImpo[MO] = m_dMonitoraggi;
				break;
			case LV:
				m_nPercLineeVita = perc;
				m_dLineeVita = Percent(m_dImponibileScontato, perc);
				m_arPerc[LV] = perc;
				m_arImpo[LV] = m_dLineeVita;
				break;
			case IM:
				m_nPercIndaginiMurature = perc;
				m_dIndaginiMurature = Percent(m_dImponibileScontato, perc);
				m_arPerc[IM] = perc;
				m_arImpo[IM] = m_dIndaginiMurature;
				break;
			case IC:
				m_nPercIndaginiCLS = perc;
				m_dIndaginiCLS = Percent(m_dImponibileScontato, perc);
				m_arPerc[IC] = perc;
				m_arImpo[IC] = m_dIndaginiCLS;
				break;
			case MM:
				m_nPercMaterialiMetallici = perc;
				m_dMaterialiMetallici = Percent(m_dImponibileScontato, perc);
				m_arPerc[MM] = perc;
				m_arImpo[MM] = m_dMaterialiMetallici;
				break;
			case V:
				m_nPercVarie = perc;
				m_dVarie = Percent(m_dImponibileScontato, perc);
				m_arPerc[V] = perc;
				m_arImpo[V] = m_dVarie;
				break;		
			case GEO:
				m_nPercGeotecnica = perc;
				m_dGeotecnica = Percent(m_dImponibileScontato, perc);
				m_arPerc[GEO] = perc;
				m_arImpo[GEO] = m_dGeotecnica;
				break;
		}
	}
	CalcTotali();
	return 0;
}

int CRipartizioneImponibileDlg::LoadRipartizione() 
{
	CalcolaRipartizione();
	UpdateData(FALSE);
	return 0;
}

void CRipartizioneImponibileDlg::OnOK() 
{
	if(m_nTotPerc != 100)
	{
		CString msg;
		msg.Format("Verificare le percentuali!"); 
		MessageBox(msg, "Attenzione!", MB_OK);	
		return;
	}
	CString strRip = "";
	strRip.Format(FMT_RIP, m_nPercProveCarico, m_nPercConglomeratiBituminosi, 
												m_nPercInerti, m_nPercMonitoraggi, m_nPercLineeVita, 
												m_nPercIndaginiMurature, m_nPercIndaginiCLS, 
												m_nPercMaterialiMetallici, m_nPercVarie, 
												m_nPercGeotecnica);
	m_strRipartizioneImponibile = strRip;
	CDialog::OnOK();
}

