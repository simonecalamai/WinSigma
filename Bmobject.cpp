/*****************************************************************************
* FILE       : BMOBJECT.CPP                                                  *
* DESCRIZIONE: oggetto bitmap immagine caricata di un fle .BMP               *
* AUTORE     : Stefano Poli                                                  *
* DATA       : 21/11/96                                                      *
* NOTE       :                                                               *
*****************************************************************************/
#include "stdafx.h"      
#include "bmobject.h"

#define SZ_BLOCK   32              /* minimo blocco di pixel */
#define SZ_BYTE     8              /* ovvio                  */

/*****************************************************************************
* FUNZIONE   : CBMPObject                                                    *
* DESCRIZIONE: costruttore                                                   *
* PARAMETRI  :                                                               *
* NOTE       :                                                               *
*****************************************************************************/
CBMPObject::CBMPObject(void) : CObject()
{
  m_pBits   = NULL;
  m_pHeader = NULL;
  m_pInfo   = NULL;
	m_nHeaderSize = 0;
}


/*****************************************************************************
* FUNZIONE   : ~CBMPObject                                                   *
* DESCRIZIONE: distruttore                                                   *
* PARAMETRI  :                                                               *
* NOTE       : eventualmente disalloca i buffer                              *
*****************************************************************************/
CBMPObject::~CBMPObject(void)
{
  Close();
}

/*****************************************************************************
* FUNZIONE   : Open                                                          *
* DESCRIZIONE: carica un file .BMP nell'oggetto                              *
* PARAMETRI  : il nome del file, restituisce il risultato della funzione     *
* NOTE       :                                                               *
*****************************************************************************/
BOOL CBMPObject::Open(CString fileName)
{
  char  buff[512];
  CFile f;
  
  if(!(f.Open((const char*)fileName, CFile::modeRead, NULL)))
    return FALSE;
  CArchive ar(&f, CArchive::load, sizeof(buff), buff);  
  Serialize(ar);
  m_PathName = fileName;
  ar.Close();
  f.Close();
  return TRUE;
}

BOOL CBMPObject::Open(CFile* pFile)
{
  char  buff[512];

  CArchive ar(pFile, CArchive::load, sizeof(buff), buff);  
  Serialize(ar);
  m_PathName = pFile->GetFilePath();
  ar.Close();
  return TRUE;
}


BOOL CBMPObject::IsOpen()
{
  if(m_pBits)
	  return TRUE;
	return FALSE;
}

/*****************************************************************************
* FUNZIONE   : Save                                                          *
* DESCRIZIONE: salva il contenuto dell'oggetto su un file .BMP               *
* PARAMETRI  : il nome del file, restituisce il risultato della funzione     *
* NOTE       :                                                               *
*****************************************************************************/
BOOL CBMPObject::Save(CString fileName)
{
  char  buff[512];
  CFile f;
  
  if(!(f.Open((LPCSTR)fileName, CFile::modeWrite | CFile::modeCreate, NULL)))
    return FALSE;
  CArchive ar(&f, CArchive::store, sizeof(buff), buff);  
  Serialize(ar);
  ar.Close();
  f.Close();
  return TRUE;
}

BOOL CBMPObject::Save(CFile* pFile)
{
  char  buff[512];

  CArchive ar(pFile, CArchive::store, sizeof(buff), buff);  
  Serialize(ar);
  ar.Close();
  return TRUE;
}

/*****************************************************************************
* FUNZIONE   : Close                                                         *
* DESCRIZIONE: chiude l'oggetto nel senso che libera i buffer                *
* PARAMETRI  :                                                               *
* NOTE       :                                                               *
*****************************************************************************/
void CBMPObject::Close(void)
{
  if(m_pBits)
  {
    GlobalUnlock(m_hBits);
    GlobalFree(m_hBits);
    m_pBits = NULL;
  }
  if(m_pHeader)
  {
    GlobalUnlock(m_hHeader);
    GlobalFree(m_hHeader);
    m_pHeader = NULL;
    m_pInfo = NULL;
  }
}

/*****************************************************************************
* FUNZIONE   : New                                                           *
* DESCRIZIONE: crea una nuova bitmap                                         *
* PARAMETRI  : larghezza, altezza e palette da utilizzare                    *
* NOTE       : crea una bitmap a 16 colori - la bitmap e' inizializzata col  *
*              colore zero della palette - se fallisce chiamare Close        *
*              perche' l'oggetto può essere inconsistente                    *
*****************************************************************************/
BOOL CBMPObject::New(LONG width, LONG height, RGBQUAD* colorTab)
{
  WORD  i;
	RGBQUAD defTab[] = {{0xFF, 0xFF, 0xFF, 0x00}, {0x80, 0x80, 0xFF, 0x00},
	                    {0x00, 0x80, 0xFF, 0x00}, {0xFF, 0x80, 0x80, 0x00},
											{0xFF, 0x80, 0x00, 0x00}, {0xFF, 0x00, 0x00, 0x00},
											{0xFF, 0xFF, 0x80, 0x00}, {0xFF, 0xFF, 0x00, 0x00},
											{0x00, 0xFF, 0x00, 0x00}, {0x00, 0x80, 0xFF, 0x00},
											{0x00, 0x00, 0x80, 0x00}, {0x80, 0x00, 0x80, 0x00},
											{0x80, 0xFF, 0x00, 0x00}, {0xFF, 0x00, 0xFF, 0x00},
											{0x80, 0x80, 0xFF, 0x00}, {0x80, 0x80, 0x80, 0x00}}; 

  /*----- libero i buffer precedenti -----*/
  Close();
  /*----- alloco il buffere per l'header -----*/
  if(!(m_hHeader = GlobalAlloc(GHND, 104)))              return FALSE;
  if(!(m_pHeader = (LPBITMAPINFO)GlobalLock(m_hHeader)))
  {
    GlobalFree(m_hHeader);
    return FALSE;
  }
  /*----- imposto i campi dell'header -----*/
  m_pInfo = &(m_pHeader->bmiHeader);
  m_pInfo->biSize     = 40;
  m_pInfo->biWidth    = width;
  m_pInfo->biHeight   = height;
  m_pInfo->biPlanes   = 1;
  m_pInfo->biBitCount = BMP_16COLORS;
  m_WidthBytes = (m_pInfo->biWidth * m_pInfo->biBitCount + 31) / 32;
  m_WidthBytes *= 4;
  m_pInfo->biSizeImage = m_pInfo->biHeight * m_WidthBytes;
  m_pInfo->biXPelsPerMeter = 2250;
  m_pInfo->biYPelsPerMeter = 2250;
  m_NColors = 16;
  /*----- imposto la tabella dei colori -----*/
	if(!colorTab)
	  colorTab = defTab;
  for(i = 0; i < m_NColors; i++)
    m_pHeader->bmiColors[i] = colorTab[i];
  /*----- alloco il buffer per i bit -----*/
  if(!(m_hBits = GlobalAlloc(GHND, m_pInfo->biSizeImage))) return FALSE;
  if(!(m_pBits = (BYTE*)GlobalLock(m_hBits)))
  {
    GlobalFree(m_hBits);
    return FALSE;
  }
  return TRUE;
}

int CBMPObject::GetFileLenght(void)
{
  if(!IsOpen())
	  return -1;
	return  m_nHeaderSize + sizeof(BITMAPFILEHEADER) + m_pInfo->biHeight * m_WidthBytes;
}

/*****************************************************************************
* FUNZIONE   : Serialize                                                     *
* DESCRIZIONE: carica e salva da e su file                                   *
* PARAMETRI  : l'oggetto archivio                                            *
* NOTE       : vedi omonima in CObject                                       *
*****************************************************************************/
void CBMPObject::Serialize(CArchive& ar)
{
  long   r;
  BITMAPFILEHEADER fileHeader;
  char  buffer[64];

  if(ar.IsStoring())
  {
    fileHeader.bfType = 0x4D42;
    fileHeader.bfSize = m_nHeaderSize + m_pInfo->biSize;
    fileHeader.bfReserved1 = 0;
    fileHeader.bfReserved2 = 0;
    fileHeader.bfOffBits   = m_nHeaderSize + sizeof(BITMAPFILEHEADER);
    ar.Write((char*)&fileHeader, sizeof(BITMAPFILEHEADER));
    ar.Write((char*)m_pHeader, (UINT)fileHeader.bfOffBits - sizeof(BITMAPFILEHEADER));
    for(r = 0; r < m_pInfo->biHeight; r++)
      ar.Write((char*)m_pBits + m_WidthBytes * r, (UINT)m_WidthBytes);
  }
  else
  {
    ar.Read((char*)&fileHeader, sizeof(BITMAPFILEHEADER));
    m_nHeaderSize = fileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);
    if((m_hHeader = GlobalAlloc(GHND, m_nHeaderSize)) == NULL)
    {
      wsprintf(buffer, "Errore nell'allocazione di %ld byte.", m_nHeaderSize);
      MessageBox(NULL, buffer, "", MB_OK);
      return;
    }
    if((m_pHeader = (LPBITMAPINFO)GlobalLock(m_hHeader)) == NULL)
    {
      MessageBox(NULL, "Errore di lock dell'header.", "", MB_OK);
      return;
    }
    m_pInfo = &(m_pHeader->bmiHeader);
    ar.Read((char*)m_pHeader, (UINT)m_nHeaderSize);
    m_WidthBytes = (m_pInfo->biWidth * m_pInfo->biBitCount + 31) / 32;
    m_WidthBytes *= 4;
    m_pInfo->biSizeImage = m_pInfo->biHeight * m_WidthBytes;
    m_pInfo->biXPelsPerMeter = 2250;
    m_pInfo->biYPelsPerMeter = 2250;
    if(m_pInfo->biBitCount == BMP_24BITS) m_NColors = 0;
    else if(m_pInfo->biClrUsed) m_NColors = m_pInfo->biClrUsed;
    else m_NColors = (0x1 << m_pInfo->biBitCount);
    if((m_hBits = GlobalAlloc(GHND, m_pInfo->biSizeImage)) == NULL)
    {
      wsprintf(buffer, "Errore nell'allocazione di %ld byte.", m_pInfo->biSizeImage);
      MessageBox(NULL, buffer, "", MB_OK);
      return;
    }
    if((m_pBits = (BYTE*)GlobalLock(m_hBits)) == NULL)
    {
      MessageBox(NULL, "Errore di lock dei bit.", "", MB_OK);
      return;
    }
    for(r = 0; r < m_pInfo->biHeight; r++)
      ar.Read((char*)m_pBits + m_WidthBytes * r, (UINT)m_WidthBytes);
  }
}

/*****************************************************************************
* FUNZIONE   : GetPixel                                                      *
* DESCRIZIONE: restituisce il colore di un pixel della bitmap                *
* PARAMETRI  : il punto che interessa - restituisce il colore                *
* NOTE       :                                                               *
*****************************************************************************/
COLORREF CBMPObject::GetPixel(CPoint p)
{
  COLORREF rgbVal;
  BYTE     color, mask;
  DWORD    ptr;
  
  /*----- se c'e' qualche inconsistenza restituisco nero -----*/
  if(!m_pInfo || !m_pBits) return BMP_BLACK;
  if((long)p.x >= m_pInfo->biWidth || (long)p.y >= m_pInfo->biHeight)
    return BMP_BLACK;
  /*----- determino il DWORD dove risiede l'informazione del pixel -----*/
  ptr = (m_pInfo->biHeight - 1 - (DWORD)p.y) * m_WidthBytes;
  ptr += ((DWORD)p.x * m_pInfo->biBitCount) / 8;
  /*----- determino il colore -----*/
  switch(m_pInfo->biBitCount)
  {
  case BMP_MONOCHROME : mask = 0x80 >> (p.x % 8);
                        color = m_pBits[ptr] & mask;
                        color >>= (7 - (p.x % 8));
                        rgbVal = RGB(m_pHeader->bmiColors[color].rgbRed,
                                     m_pHeader->bmiColors[color].rgbGreen,
                                     m_pHeader->bmiColors[color].rgbBlue);
                        break;
  case BMP_16COLORS   : if(p.x % 2) mask = 0xF0;
                        else        mask = 0x0F;
                        color = m_pBits[ptr] & mask;
                        if(p.x % 2) color >>= 4;
                        rgbVal = RGB(m_pHeader->bmiColors[color].rgbRed,
                                     m_pHeader->bmiColors[color].rgbGreen,
                                     m_pHeader->bmiColors[color].rgbBlue);
                        break;
  case BMP_256COLORS  : color = m_pBits[ptr];
                        rgbVal = RGB(m_pHeader->bmiColors[color].rgbRed,
                                     m_pHeader->bmiColors[color].rgbGreen,
                                     m_pHeader->bmiColors[color].rgbBlue);
                        break;
  case BMP_24BITS     : rgbVal = RGB(m_pBits[ptr + 2], 
                                     m_pBits[ptr + 1],
                                     m_pBits[ptr]);
                        break;
  default             : rgbVal = RGB(0x00, 0x00, 0x00);
  }
  return rgbVal;
}

/*****************************************************************************
* FUNZIONE   : SetPixel                                                      *
* DESCRIZIONE: imposta il colore di un pixel della bitmap                    *
* PARAMETRI  : il punto che interessa e il colore - restituisce l'esito      *
* NOTE       :                                                               *
*****************************************************************************/
BOOL CBMPObject::SetPixel(CPoint p, RGBTRIPLE rgb)
{
  BYTE    color, mask;
  DWORD   ptr, i;
  
  /*----- verifico la consistenza -----*/
  if((long)p.x >= m_pInfo->biWidth || (long)p.y >= m_pInfo->biHeight)
    return FALSE;
  /*----- determino il DWORD dove risiede l'informazione del pixel -----*/
  ptr = (m_pInfo->biHeight - 1 - (DWORD)p.y) * m_WidthBytes;
  ptr += ((DWORD)p.x * m_pInfo->biBitCount) / 8;
  /*----- determino la posizione del colore nella palette -----*/
  for(color = 0, i = 1; i < m_NColors; i++)
    if(labs(m_pHeader->bmiColors[i].rgbBlue - rgb.rgbtBlue)
       + labs(m_pHeader->bmiColors[i].rgbGreen - rgb.rgbtGreen)
       + labs(m_pHeader->bmiColors[i].rgbRed - rgb.rgbtRed) 
       < labs(m_pHeader->bmiColors[color].rgbBlue - rgb.rgbtBlue)
         + labs(m_pHeader->bmiColors[color].rgbGreen - rgb.rgbtGreen)
         + labs(m_pHeader->bmiColors[color].rgbRed - rgb.rgbtRed))
       color = (BYTE)i;
  /*----- imposto il pixel -----*/
  switch(m_pInfo->biBitCount)
  {
  case BMP_MONOCHROME : mask = 0x80 >> (p.x % 8);
                        color <<= (7 - (p.x % 8));
                        m_pBits[ptr] &= ~mask;
                        m_pBits[ptr] |= color;
                        break;
  case BMP_16COLORS   : if(p.x % 2) mask = 0xF0;
                        else        mask = 0x0F;
                        if(p.x % 2) color <<= 4;
                        m_pBits[ptr] &= ~mask;
                        m_pBits[ptr] |= color;
                        break;
  case BMP_256COLORS  : m_pBits[ptr] = color;
                        break;
  case BMP_24BITS     : m_pBits[ptr] = (BYTE)rgb.rgbtBlue;
                        m_pBits[ptr + 1] = (BYTE)rgb.rgbtGreen;
                        m_pBits[ptr + 2] = (BYTE)rgb.rgbtRed;
                        break;
  }
  return TRUE;
}

/*****************************************************************************
* FUNZIONE   : GetRect                                                       *
* DESCRIZIONE: estrae i colori di un rettangolo della bitma                  *
* PARAMETRI  : il rettangolo e un buffer da impostare: ogni byte del buffer  *
*              rappresenta un pixel nella disposizione ordinaria e contiene  *
*              l'indice del colore nella palette dell bitmap - non funziona  *
*              per bitmap a 24 bit per pixel                                 *
* NOTE       : l'area del rettangolo fuori dalla bitmap e' colorata con il   *
*              colore 0 della palette                                        *
*****************************************************************************/
BOOL CBMPObject::GetRect(LPRECT pRect, char* buffer)
{
  long  p = 0, r, c;
  DWORD ptr;
  BYTE  color, mask;
  
  /*----- compilo il buffer -----*/
  for(r = pRect->top; r <= pRect->bottom; r++)
    for(c = pRect->left; c <= pRect->right; c++)
    {
      if(c >= 0 && c < m_pInfo->biWidth && r >= 0 && r < m_pInfo->biHeight)
      {                    
        /*--- se il punto e' interno alla bitmap determino la posizione ---*/
        ptr = (m_pInfo->biHeight - 1 - (DWORD)r) * m_WidthBytes;
        ptr += ((DWORD)c * m_pInfo->biBitCount) / 8;
        /*----- determino il colore -----*/
        switch(m_pInfo->biBitCount)
        {
        case BMP_MONOCHROME : mask = 0x80 >> (c % 8);
                              color = m_pBits[ptr] & mask;
                              color >>= (7 - (c % 8));
                              break;
        case BMP_16COLORS   : if(c % 2) mask = 0x0F;
                              else      mask = 0xF0;
                              color = m_pBits[ptr] & mask;
                              if(!(c % 2)) color >>= 4;
                              break;
        case BMP_256COLORS  : color = m_pBits[ptr];
                              break;
        case BMP_24BITS     : return FALSE;
        }
      }
      else color = 0;
      buffer[p++] = color;
    }
  return TRUE;
}

/****************************************************************************
* FUNZIONE   : SetRect                                                      *
* DESCRIZIONE: imposta i colori in un rettangolo della bitmap               *
* PARAMETRI  : il rettangolo e un buffer in cui ogni byte rappresenta un    *
*              pixel nella disposizione ordinaria e contiene l'indice del   *
*              colore nella palette della bitmap - non funziona per bitmap  *
*              a 24 bit per pixel                                           *
* NOTE       : l'area del rettangolo fuori dalla bitmap non e' impostata    *
****************************************************************************/
BOOL CBMPObject::SetRect(LPRECT pRect, char* buffer)
{
  long  p = 0, r, c;
  DWORD ptr;
  BYTE  color, mask;
  
  /*----- compilo il buffer -----*/
  for(r = pRect->top; r < pRect->bottom; r++)
    for(c = pRect->left; c < pRect->right; c++)
    {
      color = buffer[p++];
      if(c >= 0 && c < m_pInfo->biWidth && r >= 0 && r < m_pInfo->biHeight)
      {                    
        /*--- se il punto e' interno alla bitmap determino la posizione ---*/
        ptr = (m_pInfo->biHeight - 1 - (DWORD)r) * m_WidthBytes;
        ptr += ((DWORD)c * m_pInfo->biBitCount) / 8;
        /*----- imposto il colore -----*/
        switch(m_pInfo->biBitCount)
        {
        case BMP_MONOCHROME : mask = 0x80 >> (c % 8);
                              if(color) m_pBits[ptr] |= mask;
                              else      m_pBits[ptr] &= ~mask;
                              break;
        case BMP_16COLORS   : if(c % 2)
                              {
                                m_pBits[ptr] &= 0xF0;
                                m_pBits[ptr] |= (color &0x0F);
                              }
                              else
                              {
                                m_pBits[ptr] &= 0x0F;
                                m_pBits[ptr] |= (color << 4);
                              }
                              break;
        case BMP_256COLORS  : m_pBits[ptr] = color;
                              break;
        case BMP_24BITS     : return FALSE;
        }
      }
    }
  return TRUE;
}
