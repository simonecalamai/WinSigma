// XBMPControl.cpp : implementation file
//

#include "stdafx.h"
#include "bmobject.h"
#include "winsigma.h"
#include "XBMPControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXBMPControl

CXBMPControl::CXBMPControl()
{
  m_pBMPImage = NULL;
}


CXBMPControl::~CXBMPControl()
{
}


BEGIN_MESSAGE_MAP(CXBMPControl, CStatic)
	//{{AFX_MSG_MAP(CXBMPControl)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CXBMPControl::Set(CBMPObject* pBmpObject)
{
  m_pBMPImage = pBmpObject;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CXBMPControl message handlers

void CXBMPControl::OnPaint() 
{
	CPaintDC dc(this);
  double   xFact, yFact;
  CSize    sizeWnd, sizeDst;
	CRect    rect;
	CPoint   posDst;
  CBitmap* pOldBitMap;
  HBITMAP  hBitMap;
	CDC      MemoryDC;
	CBrush   whiteBrush(RGB(0xFF, 0xFF, 0xFF));

  GetClientRect((LPRECT)rect);
	sizeWnd = rect.Size();
	dc.FillRect(rect, &whiteBrush);
	if(m_pBMPImage && m_pBMPImage->IsOpen())
  {   
	  MemoryDC.CreateCompatibleDC(NULL);
		hBitMap = CreateDIBitmap(dc.m_hDC, m_pBMPImage->m_pInfo, CBM_INIT,
                             m_pBMPImage->m_pBits, m_pBMPImage->m_pHeader,
		              				   DIB_RGB_COLORS);
    pOldBitMap = MemoryDC.SelectObject((CBitmap*)CBitmap::FromHandle(hBitMap));
    if(m_pBMPImage->m_pInfo->biWidth)
	    xFact = (double)sizeWnd.cx / m_pBMPImage->m_pInfo->biWidth;
  	else xFact = 100;
  	if(m_pBMPImage->m_pInfo->biHeight)
	  	yFact = (double)sizeWnd.cy / m_pBMPImage->m_pInfo->biHeight;
  	else yFact = 100;
    if(xFact < yFact)
    {
      sizeDst = CSize(sizeWnd.cx,
                      (int)(m_pBMPImage->m_pInfo->biHeight * xFact));  
      posDst = CPoint(0, (sizeWnd.cy - sizeDst.cy) / 2);  
    }
    else
    {
      sizeDst = CSize((int)(m_pBMPImage->m_pInfo->biWidth * yFact),
                      sizeWnd.cy);  
      posDst = CPoint((sizeWnd.cx - sizeDst.cx) / 2, 0);  
    }
    dc.StretchBlt(posDst.x, posDst.y, sizeDst.cx, sizeDst.cy,
                  &MemoryDC, 0, 0,
                  m_pBMPImage->m_pInfo->biWidth,
                  m_pBMPImage->m_pInfo->biHeight,
                  SRCCOPY);
    MemoryDC.SelectObject(pOldBitMap);
    DeleteObject((HBITMAP)hBitMap);
	}
  MemoryDC.DeleteDC();
}
