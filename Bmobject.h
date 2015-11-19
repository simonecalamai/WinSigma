/*****************************************************************************
* FILE       : BMOBJECT.CPP                                                  *
* DESCRIZIONE: oggetto bitmap immagine caricata di un fle .BMP               *
* AUTORE     : Stefano Poli                                                  *
* DATA       : 21/11/96                                                      *
* NOTE       : risistemazione di vecchi file bmpdoc e bmpobject              *
*****************************************************************************/
#define BMP_BLACK        RGB(0x00, 0x00, 0x00)
#define BMP_WHITE        RGB(0xFF, 0xFF, 0xFF)

#define BMP_MONOCHROME   1    /* codifica del tipo di bitmap      */
#define BMP_16COLORS     4
#define BMP_256COLORS    8
#define BMP_24BITS      24

class CBMPObject : public CObject
{
  //***** dati
  protected:
    HGLOBAL            m_hHeader;
    HGLOBAL            m_hBits;
		DWORD              m_nHeaderSize;
  public:
    LPBITMAPINFO       m_pHeader;
    LPBITMAPINFOHEADER m_pInfo;
    BYTE*              m_pBits;
    CString            m_PathName;
    DWORD              m_WidthBytes; /* num. di byte per riga        */
    DWORD              m_NColors;    /* num. di colori nella palette */
  //***** metodi
  public:
    CBMPObject(void);
    ~CBMPObject(void);
    BOOL     Open(CString fileName);
		BOOL     Open(CFile* pFile);
		BOOL     IsOpen();
    void     Close(void);
    BOOL     New(LONG width, LONG height, RGBQUAD* colorTab);
    BOOL     Save(CString fileName = "");
		BOOL     Save(CFile* pFile);
		int      GetFileLenght(void);
    COLORREF GetPixel(CPoint p);
    BOOL     SetPixel(CPoint p, RGBTRIPLE rgb);
    BOOL     GetRect(LPRECT pRect, char* buffer);
    BOOL     SetRect(LPRECT pRect, char* buffer);
  protected:
    void     Serialize(CArchive& ar);
};
