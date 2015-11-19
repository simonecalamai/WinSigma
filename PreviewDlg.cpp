// PreviewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winsigma.h"
#include "PreviewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreviewDlg dialog
#define TOP_POS   0
#define MED_POS   1
#define BOT_POS   2

CPreviewDlg::CPreviewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPreviewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPreviewDlg)
	m_bZoom = FALSE;
	//}}AFX_DATA_INIT
  m_pPrintPreviewDoc = NULL;
}


void CPreviewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreviewDlg)
	DDX_Control(pDX, IDC_SCROLLBAR, m_ScrollBar);
	DDX_Control(pDX, IDC_STATIC_PREVIEW, m_StaticPreview);
	DDX_Check(pDX, IDC_CHECK_ZOOM, m_bZoom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreviewDlg, CDialog)
	//{{AFX_MSG_MAP(CPreviewDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK_ZOOM, OnCheckZoom)
	ON_WM_VSCROLL()
	ON_BN_CLICKED(IDC_STAMPA, OnStampa)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreviewDlg message handlers

BOOL CPreviewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_nPage = 1;
  m_nPosZoom = TOP_POS;
	m_ScrollBar.ShowWindow(SW_SHOW);	   
	return TRUE;
}

void CPreviewDlg::OnPaint() 
{
  int n;
	CPaintDC dc(this); // device context for painting
	CRect    rect;
	CRgn     rgn;
	CBrush   brushWhite(RGB(0xFF, 0xFF, 0xFF));
	CBrush   brushBlack(RGB(0x00, 0x00, 0x00));
  double dScala = 0;

	m_StaticPreview.GetWindowRect(&rect);
	ScreenToClient(&rect);
  n = rect.Width() / 5;
	if(!m_bZoom)
	{
	  rect.left  += n;
		rect.right -= n;
	}
	dc.Rectangle(&rect);
  rgn.CreateRectRgnIndirect(&rect);
	dc.SelectClipRgn(&rgn);
  rect += CSize(14, 0);
  n = 0;
	if(m_bZoom)
    dScala = 1.8;
	dc.SetBkColor(RGB(0xFF, 0xFF, 0xFF));
	m_nTotalePagine = m_pPrintPreviewDoc->PrintPage(m_nCodice, &dc, &rect, m_nPage, dScala, m_nPosZoom);
  if(!m_bZoom)
    m_ScrollBar.SetScrollRange(1, m_nTotalePagine);
}


void CPreviewDlg::OnCheckZoom() 
{
  UpdateData();
  if(!m_bZoom)
  {
    m_ScrollBar.SetScrollRange(1, m_nTotalePagine);
    m_ScrollBar.SetScrollPos(m_nPage);
  }
  else
  {
    m_ScrollBar.SetScrollRange(TOP_POS, BOT_POS);
    m_ScrollBar.SetScrollPos(TOP_POS);
  }
  m_nPosZoom = TOP_POS;
  m_nScrollDir = -1;
  RedrawWindow();
}

void CPreviewDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
  if(!m_bZoom)
  {
    if(nSBCode == SB_LINEDOWN || nSBCode == SB_PAGEDOWN)
    {
      if(m_nPage < m_nTotalePagine)
        m_nPage++;
      m_ScrollBar.SetScrollPos(m_nPage);
      RedrawWindow();
    }
    else if(nSBCode == SB_LINEUP || nSBCode == SB_PAGEUP)
    {
      if(m_nPage > 1)
        m_nPage--;
      m_ScrollBar.SetScrollPos(m_nPage);
      RedrawWindow();
    }
  }
  else
  {
    m_nScrollDir = nSBCode;
    if(m_nScrollDir == SB_LINEDOWN || m_nScrollDir == SB_PAGEDOWN)
    {
      if(m_nPosZoom == TOP_POS || m_nPosZoom == MED_POS)
      {
        m_nPosZoom++;
        m_ScrollBar.SetScrollPos(m_nPosZoom);
        RedrawWindow();
      }
    }
    else if(m_nScrollDir == SB_LINEUP || m_nScrollDir == SB_PAGEUP)
    {
      if(m_nPosZoom > TOP_POS)
      {
        m_nPosZoom--;
        m_ScrollBar.SetScrollPos(m_nPosZoom);
        RedrawWindow();
      }
    }
  }
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CPreviewDlg::OnStampa() 
{
  m_pPrintPreviewDoc->Print(m_nCodice, NULL, NULL);	
  CDialog::OnCancel();
}

