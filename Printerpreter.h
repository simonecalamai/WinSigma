#include "FreeImage.h"

#define MAX_GRID_ROWS			32

/********************************************************************
* Classe     : CPrintItem
* Descrizione: Classe base da cui deriveremo le varie classi per
               memorizzare gli oggetti da stampare 
* Note       : 
*********************************************************************/
class CPrintItem : public CObject
{
  /*----- dati -----*/
  public:
		int  m_X;    // coordinata x
		int  m_Y;    // coordinata y
    int  m_W;    // larghezza della griglia
    int  m_H;    // altezza
    int  m_HDrawn;
		int  m_Page; // numero di pagina
    FILE*  m_pPrintFile;
		COLORREF m_Color;

	protected:
		CString		m_Nomefile;
  
	/*----- metodi -----*/
  public:
    CPrintItem(void);
		void SetNomefile(CString nomefile);
    // imposta le variabili in base ai valori letti dal file alla sezione sec 
		virtual BOOL Load(CString sec, CString key, CString layoutFName);
    // stampa l'oggetto in base alle sue caratteristiche
		virtual CGdiObject* Print(CDC* pDC, CGdiObject* pGdiObj);
    // Stampa in modalità testo
    virtual BOOL Print(int& xCurr, int& yCurr, BOOL bPrint);
    // Comandi per la stampante ad aghi
    virtual void SetFont(CString strFont);
};

/********************************************************************
* Classe     : CPrintItemArray
* Descrizione: Derivata dalla CObArray ed usata per memorizzare in
               array gli oggetti di tipo CPrintItem
* Note       : 
*********************************************************************/
class CPrintItemArray : public CObArray
{
  /*----- dati -----*/
  public:
  /*----- metodi -----*/
  public:
    // costruttore
		CPrintItemArray(void);
    // distruttore
		~CPrintItemArray(void);
    // costruzione dell'arry
		int  Load(CString sec, CString layoutFName, CString headerFName = "");
    //
		CPrintItem& operator[](int i);
    // 
		CPrintItem* GetAt(int i);
};

/********************************************************************
* Classe     : CStringItem
* Descrizione: Memorizza 
* Note       : Derivata dalla CPrintItem per memorizzare un'item stringa
               da stampare
*********************************************************************/
class CStringItem : public CPrintItem
{
  /*----- dati -----*/
  protected:
    CString m_Text;
    UINT    m_TextAlign;
    int     m_FontWidth;
    int     m_FontHeight;
    int     m_FontWeight;
    BOOL    m_bFontItalic;
    BOOL    m_bFontUnderline;
		BYTE    m_nEdge;
    CString m_FontName;
  public:
	  static int m_LastX;
	  static int m_LastY;
		BOOL    m_bNull;
  
	/*----- metodi -----*/
  public:
    CStringItem(void);
    // imposta le variabili membro, in base ai dati contenuti nel file
		BOOL Load(CString sec, CString key, CString layoutFName);
    // stampa
		CGdiObject* Print(CDC* pDC, CGdiObject* pFont);
    // Stampa in modalità testo
    BOOL Print(int& xCurr, int& yCurr, BOOL bPrint);
    void SetFont(CString strFont);
};


/********************************************************************
* Classe     : CFieldItem
* Descrizione: Memorizza 
* Note       : Derivata dalla CStringItem per memorizzare le stringhe
               di riferimento da sostituire 
*********************************************************************/
class CFieldItem : public CStringItem
{
  /*----- dati -----*/
  private:
    // oltre alle variabili membro della classe CStringItem, ha anche 
		// la variabli m_Key che rappresenta la chiave 
		CString m_Key;
	/*----- metodi -----*/
  public:
    CFieldItem(void);
    // imposta le variabili membro, in base ai dati contenuti nel file    
		BOOL Load(CString sec, CString key, CString layoutFName);
#if 0
    // stampa
		CGdiObject* Print(CDC* pDC, CGdiObject* pFont);
    // Stampa in modalità testo
    BOOL Print(int& xCurr, int& yCurr, BOOL bPrint);
#endif
    // mappatura
		BOOL Remap(CStringArray* pEntries, CStringArray* pValues);
};

/********************************************************************
* Classe     : CPageItem
* Descrizione: Usata per istanziare l'oggetto contenente il modo con cui
               stampare il numero progressivo di pagina 
* Note       : Derivata dalla CStringItem 
*********************************************************************/
class CPageItem : public CStringItem
{  
	/* ----- metodi -----*/
  public:
    // imposta la variabili membro m_Text    
		BOOL SetText(CString cs);
};

/********************************************************************
* Classe     : CTabfieldItem
* Descrizione: 
* Note       : 
*********************************************************************/
class CTabfieldItem : public CFieldItem
{
  /*----- dati -----*/
  private:
	  // valore di Y di partenza dovuto alle eventuali righe prima stampate
    int m_ZeroY;
  /*----- metodi -----*/
  public:
	  static int m_nRigheScritte;
    CTabfieldItem(void);
    // imposta le variabili membro, in base ai dati contenuti nel file    
    BOOL Load(CString sec, CString key, CString layoutFName);
    // stampa
		CGdiObject* Print(CDC* pDC, CGdiObject* pFont);
    // Stampa in modalità testo
    BOOL Print(int& xCurr, int& yCurr, BOOL bPrint);
    void SetFont(CString strFont);
    // 
		void NewPage(void);
};

/********************************************************************
* Classe     : CTextItem
* Descrizione: 
* Note       : 
*********************************************************************/
class CTextItem : public CStringItem
{
  /*----- dati -----*/
  private:
    CString m_FileName;
  /*----- metodi -----*/
  public:
    CTextItem(void);
    BOOL Load(CString sec, CString key, CString layoutFName);
    CGdiObject* Print(CDC* pDC, CGdiObject* pFont);
};


/********************************************************************
* Classe     : CGridItem
* Descrizione: Memorizza i dati di una griglia da stampare
* Note       : 
*********************************************************************/
class CGridItem : public CPrintItem
{
  /*----- dati -----*/
  protected:
  public:
    int  m_Rows;   // numero di righe contenute nella griglia
    int  m_Cols;   // numero di colonne contenute nella griglia
    static m_LastX;
    static m_LastY;

  /*----- metodi -----*/
  public:
    CGridItem(void);
    CGridItem(CGridItem* pItem);
    BOOL Load(CString sec, CString key, CString layoutFName);
    CGdiObject* Print(CDC* pDC, CGdiObject* pPen);
};

/********************************************************************
* Classe     : CBitmapItem
* Descrizione: 
* Note       : 
*********************************************************************/
class CBitmapItem : public CPrintItem
{
  /*----- dati -----*/
  protected:
	  CString            m_Flags;
    HGLOBAL            m_hHeader;
    HGLOBAL            m_hBits;
    LPBITMAPINFO       m_pHeader;
    LPBITMAPINFOHEADER m_pInfo;
    BYTE*              m_pBits;
    CString            m_PathName;
    DWORD              m_WidthBytes; /* num. di byte per riga        */
    DWORD              m_NColors;    /* num. di colori nella palette */
  /*----- metodi -----*/
  public:
    CBitmapItem(void);
    ~CBitmapItem(void);
    BOOL Load(CString sec, CString key, CString layoutFName);
    CGdiObject* Print(CDC* pDC, CGdiObject* pBitmap);
};

/********************************************************************
* Classe     : CImageItem
* Descrizione: 
* Note       : 
*********************************************************************/
class CImageItem : public CPrintItem
{
  /*----- dati -----*/
  protected:
		FIBITMAP*					 m_dib;	
	  CString            m_Flags;
    HGLOBAL            m_hHeader;
    HGLOBAL            m_hBits;
    LPBITMAPINFO       m_pHeader;
    LPBITMAPINFOHEADER m_pInfo;
    BYTE*              m_pBits;
    CString            m_PathName;
    DWORD              m_WidthBytes; /* num. di byte per riga        */
    DWORD              m_NColors;    /* num. di colori nella palette */
  /*----- metodi -----*/
  public:
    CImageItem(void);
    ~CImageItem(void);
    BOOL Load(CString sec, CString key, CString layoutFName);
    CGdiObject* Print(CDC* pDC, CGdiObject* pBitmap);
};

/********************************************************************
* Classe     : CBarcodeItem
* Descrizione: 
* Note       : 
*********************************************************************/
class CBarcodeItem : public CPrintItem
{
  /*----- dati -----*/
  protected:
		int				m_Type;					// 0: BARCODE128  !=0: BARCODE39
		int				m_PenWidth;			// default = 4
	  CString		m_Code;
  /*----- metodi -----*/
  public:
    CBarcodeItem(void);
    ~CBarcodeItem(void);
    BOOL Load(CString sec, CString key, CString layoutFName);
    CGdiObject* Print(CDC* pDC, CGdiObject* pBitmap);
};


/********************************************************************
* Classe     : CPrintInterpreter
* Descrizione: Classe usata per stampare che incapsula array di oggetti
               istanziati dalle classi precedentemente definite
* Note       : 
*********************************************************************/
class CPrintInterpreter : public CObject
{
  /*----- dati -----*/
  public:
  protected:
		CString					m_DocName;
    CString         m_LayoutFName;
		CString					m_HeaderFName;
    CStringArray*   m_pFieldsName;
    CStringArray*   m_pFieldsValue;
    BOOL (CALLBACK * m_pfnSetFields)(CStringArray*, CStringArray*);
    BOOL (CALLBACK * m_pfnSetTabfields)(CStringArray*, CStringArray*);
    
  	CDC m_dcPrint;
		HDC m_hDC;
		int m_nPage;
		// array di oggetti che verranno riempiti e inizializzati in base al file di layout
		CPrintItemArray m_StringItems;
    CPrintItemArray m_FieldItems;
    CPrintItemArray m_TabfieldItems;
    CPrintItemArray m_TextItems;
    CPrintItemArray m_GridItems;
    CPrintItemArray m_BitmapItems;
    CPrintItemArray m_ImageItems;
		CPrintItemArray m_BarcodeItems;
    // oggetto per stampare il numero di pagina
    CPageItem m_PageItem;

		int m_nRowSeries;
//		int m_nGroup;
		int m_aryRowAttrs[MAX_GRID_ROWS];

  /*----- metodi -----*/
  public:
    CPrintInterpreter();
    ~CPrintInterpreter(void);
		BOOL PrePrinting(HDC DC = NULL);
		BOOL PrePrinting(CDC* pDC, CRect* pRect, double dScala, int nOrigine);
		BOOL PostPrinting(CDC* pDC = NULL);
		BOOL StartSimulation(void);
		BOOL EndSimulation(void);
		int  GetPage(void);
		void SetPage(int n);
    int m_nTotalePagine;
	
		// stampa secondo il file layoutFName, secondo gli array .....
		BOOL Print(CString layoutFName,
								 CStringArray* pFiledsName,
								 CStringArray* pFieldsValue,
								 BOOL (CALLBACK *pfnSetFields)(CStringArray*, CStringArray*),
								 BOOL (CALLBACK *pfnSetTabfields)(CStringArray*, CStringArray*));
		BOOL PrintPage(CString layoutFName,
								 CStringArray* pFiledsName,
								 CStringArray* pFieldsValue,
								 BOOL (CALLBACK *pfnSetFields)(CStringArray*, CStringArray*),
								 BOOL (CALLBACK *pfnSetTabfields)(CStringArray*, CStringArray*),
                 int nPage);
    BOOL PrintText(CString layoutFName,
                   CString printFileName,
								   CStringArray* pFiledsName,
								   CStringArray* pFieldsValue,
                   BOOL (CALLBACK *pfnSetFields)(CStringArray*, CStringArray*),
								   BOOL (CALLBACK *pfnSetTabfields)(CStringArray*, CStringArray*));
		void SetHeaderFile(CString headerFName);
		void SetDocName(CString docName);

  protected:
    BOOL PrintStrings  (CDC* pDC, int page);
    BOOL PrintFields   (CDC* pDC, int page);
    BOOL PrintTabfields(CDC* pDC, int page);
    BOOL PrintTexts    (CDC* pDC, int page);
    BOOL PrintGrids    (CDC* pDC, int page);
    BOOL PrintBitmaps  (CDC* pDC, int page);
    BOOL PrintImages   (CDC* pDC, int page);
    BOOL PrintBarcodes (CDC* pDC, int page);
};

