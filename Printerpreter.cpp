#include "stdafx.h"
#include "resource.h"
#include "WinSigma.h"
#include "barcode.h"
#include "Printerpreter.h"

#define BMP_MONOCHROME   1
#define BMP_16COLORS     4
#define BMP_256COLORS    8
#define BMP_24BITS      24

#define SEC_GENERAL      "general"
#define SEC_STRINGS      "strings"
#define SEC_FIELDS       "fields"
#define SEC_TABFIELDS    "tabfields"
#define SEC_TEXTS        "texts"
#define SEC_GRIDS        "grids"
#define SEC_BITMAPS      "bitmaps"
#define SEC_IMAGES	     "images"
#define SEC_BARCODES		 "barcodes"

#define KEY_XZERO         "x zero"
#define KEY_YZERO         "y zero"
#define KEY_TABLINES      "tab lines"
#define KEY_NR_PAGINA     "Nr.Pagina"
#define KEY_PRN_TYPE      "prn_type"
#define KEY_PAGE_DIM      "page_dim"

#define KEY_CURPAGE       "@page"

#define LAST_PAGE        -1

#define NO_FONT          "*"

#define EDGE_SOUTH				0x01
#define EDGE_WEST					0x02
#define EDGE_NORTH				0x04
#define EDGE_EAST					0x08
#define EDGE_NONEIFNULL		0x10	

// Defines per la stampa in modalità testo
#define TEXT_PRINT     'T'  // Stampa in modalità testo
#define NORMAL_FONT    "N"
#define MINI_FONT      "m"
#define MAXI_FONT      "M"
#define DEFAULT_FONT   NORMAL_FONT
#define Y_UNIT         40 //42
#define X_MINI_UNIT   136
#define X_NORMAL_UNIT  82
#define X_MAXI_UNIT    40
#define PAGE_WIDTH    2030 
#define PAGE_HEIGHT   2760 //2960 //2870
#define MAX_Y         PAGE_HEIGHT/Y_UNIT
#define MAX_X         PAGE_WIDTH

#define Y_PAGE_LIMIT  2520
// Comandi per la stampante ad aghi
#define CMD_SET_MINI   "\017"
#define CMD_DESET_MINI "\022"
#define CMD_SET_MAXI   "\033\016"
#define CMD_DESET_MAXI "\024"
#define CMD_A_CAPO     "\n"
#define CMD_RESET_PRN  "\033@"
#define CMD_SET_PG_LEN "\033C\106"
#define CMD_SET_LN_SPC "\0332"
#define CMD_SET_BT_MRG "\033N\1"

int nLines;

// variabili statiche usate per gli incrementi all'interno di una sezione
int CStringItem::m_LastX = 0;
int CStringItem::m_LastY = 0;

int CGridItem::m_LastX = 0;
int CGridItem::m_LastY = 0;

/*----- implementazione di CPrintIterpreter -----*/
/********************************************************************
* Funzione   : CPrintInterpreter
* Descrizione: Funzione costruttore, inizializza solo 2 variabili
               (che non sono membro della classe)
* Parametri  : 
* Note       : 
*********************************************************************/
CPrintInterpreter::CPrintInterpreter(void) : CObject()
{
	m_nPage = 1;
	m_HeaderFName = "";
	m_DocName = "printdoc";
}

CPrintInterpreter::~CPrintInterpreter(void)
{
  if(m_dcPrint.m_hDC)
    m_dcPrint.DeleteDC();
}

BOOL CPrintInterpreter::PrePrinting(CDC* pDC, CRect* pRect, double dScala, int nOrigine)
{
  m_dcPrint.Attach(pDC->m_hDC);
  m_dcPrint.SetMapMode(MM_ISOTROPIC);
  /*----- imposto le dimensioni 'logiche' dell'area di stampa (in decimi di mm) -----*/
  if(dScala)
  {
    m_dcPrint.SetWindowOrg(0, 2970 / 3 * nOrigine);
    m_dcPrint.SetWindowExt((int)((double)2100 / dScala), (int)((double)2970 / dScala));
  }
  else
  {
    m_dcPrint.SetWindowOrg(0, 0);
    m_dcPrint.SetWindowExt(2100, 2970);
  }
  /*----- imposto le dimensioni 'fisiche' dell'area di stampa (in pixel) -----*/
  m_dcPrint.SetViewportOrg(pRect->left, pRect->top);
  m_dcPrint.SetViewportExt(pRect->Width(), pRect->Height());   
  return TRUE;
}


BOOL CPrintInterpreter::PrePrinting(HDC DC)
{
	int hSize;
	int vSize;
  HDC hDC = DC;
	DOCINFO di;

	// Controlla se il PrintDC gli viene passato dall'esterno, se no lo crea
	if (!hDC)
	{
		// visualizza il dialogo per scegliere stampante e altre impostazioni di stampa
		CPrintDialog dialogPrt(TRUE);
		if (dialogPrt.DoModal() == IDCANCEL)
			return FALSE;

		if(!(hDC = dialogPrt.CreatePrinterDC()))
			return FALSE;
	}

	// memorizza informazioni (tra cui i nomi dei file) usate dalla funzione StartDoc
	// della classe CDC
	di.cbSize       =  sizeof(DOCINFO);  
	di.lpszDocName  = m_DocName; 	// nome del documento da stampare 
	di.lpszOutput   = NULL;
	di.lpszDatatype = NULL;
	di.fwType       = 0;
  
	// allega il window device context hDC all'oggetto dcPrint
	m_dcPrint.Attach(hDC);
  m_dcPrint.SetMapMode(MM_ISOTROPIC);
  m_dcPrint.SetWindowOrg(0, 0);
  /*----- imposto le dimensioni 'logiche' dell'area di stampa (in decimi di mm) -----*/
  m_dcPrint.SetWindowExt(2100, 2970);
  m_dcPrint.SetViewportOrg(0, 0);
  /*----- imposto le dimensioni 'fisiche' dell'area di stampa (in pixel) -----*/
  hSize = 210 * m_dcPrint.GetDeviceCaps(HORZRES) / 
                m_dcPrint.GetDeviceCaps(HORZSIZE);
  vSize = 297 * m_dcPrint.GetDeviceCaps(VERTRES) / 
                m_dcPrint.GetDeviceCaps(VERTSIZE);
  m_dcPrint.SetViewportExt(hSize, vSize);

		// inizio il job di stampa informando il driver della stampante che un nuovo
	// lavoro di stampa sta partendo
	if(m_dcPrint.StartDoc(&di) < 0)
	{
		DWORD error = GetLastError();
		return FALSE;
	}

	return TRUE;
}

BOOL CPrintInterpreter::PostPrinting(CDC* pDC)
{
  if(!pDC && m_dcPrint.EndDoc() < 0)
	{
    m_dcPrint.AbortDoc();
		return FALSE;
	}
	m_dcPrint.Detach();
	return TRUE;
}

BOOL CPrintInterpreter::StartSimulation(void)
{
	HDC hDC;

	if (m_dcPrint.m_hDC == NULL)
    return FALSE;
  m_hDC = m_dcPrint.Detach();
	if(!(hDC = CreateCompatibleDC(m_hDC)))
	  return FALSE;
	m_dcPrint.Attach(hDC);
	return TRUE;
}

BOOL CPrintInterpreter::EndSimulation(void)
{
  m_dcPrint.Detach();
	if(m_hDC)
	{
	  m_dcPrint.Attach(m_hDC);
	  return TRUE;
	}
	return FALSE;
}


int  CPrintInterpreter::GetPage(void)
{
  return m_nPage;
}

void CPrintInterpreter::SetPage(int n)
{
  m_nPage = n;
}

/********************************************************************
* Funzione   : Print
* Descrizione: Stampa secondo il layout imposto nel file, secondo
               
* Parametri  : layoutFName = nome del file
               pNames =  array con i nomi dei campi
               pValues = array con i valori da sostituire ai campi
               pfnSetFields
               pfnSetTabfields
* Ritorno    : 
* Note       : 
*********************************************************************/
BOOL CPrintInterpreter::Print(
       CString layoutFName,
       CStringArray* pNames,
       CStringArray* pValues,
       BOOL (CALLBACK *pfnSetFields)(CStringArray*, CStringArray*),
       BOOL (CALLBACK *pfnSetTabfields)(CStringArray*, CStringArray*))
{
  BOOL         bAgain = TRUE;
  CRect        rect;
	CString      csPag;
  
	m_LayoutFName  =    layoutFName;
  m_pFieldsName  =    pNames;
  m_pFieldsValue =    pValues;
  m_pfnSetFields =    pfnSetFields;
  m_pfnSetTabfields = pfnSetTabfields;

  // ricava il numero nLines impostato alla sezione general
	nLines = GetPrivateProfileInt(SEC_GENERAL, KEY_TABLINES, 0, layoutFName);

  // dal file di layout vede se deve scrivere il numero a ciascuna pagina e, in caso
	// affermativo, memorizza come nelle le variabili membro dell'oggetto m_PageItem
  BOOL bStampaNumeroPagina = m_PageItem.Load(SEC_GENERAL, KEY_NR_PAGINA, layoutFName);
   
	/*----- creo il device context per la stampante -----*/
	if (m_dcPrint.m_hDC == NULL)
    return FALSE;
  
	// legge il file di layout per costruire i vari array di tipo CPrintItemArray  
	m_StringItems.Load(SEC_STRINGS,                  layoutFName, m_HeaderFName);
	m_FieldItems.Load(SEC_FIELDS,                    layoutFName, m_HeaderFName);
	m_TabfieldItems.Load(SEC_TABFIELDS,              layoutFName, m_HeaderFName);
	m_TextItems.Load(SEC_TEXTS,                      layoutFName, m_HeaderFName);
  m_GridItems.Load(SEC_GRIDS,                      layoutFName, m_HeaderFName);
  m_BitmapItems.Load(SEC_BITMAPS,                  layoutFName, m_HeaderFName);
  m_ImageItems.Load(SEC_IMAGES,										 layoutFName, m_HeaderFName);
  m_BarcodeItems.Load(SEC_BARCODES,                layoutFName, m_HeaderFName);
  	  
	CFont* pFont;

	/*----- ciclo di stampa delle pagine -----*/
  // n conteggia il numero delle pagine 
	for (; bAgain; m_nPage++)
  {
    // prepara il driver della stampante a ricevere dati 
		m_dcPrint.StartPage();

		/*----- stampo -----*/
    bAgain = FALSE;
    // stampo le stringhe fisse
		if (PrintStrings(&m_dcPrint, m_nPage))   bAgain = TRUE;
    // stampa gli elenchi - liste
		if (PrintTabfields(&m_dcPrint, m_nPage)) bAgain = TRUE;
    // stampo i campi
		if (PrintFields(&m_dcPrint, m_nPage))    bAgain = TRUE;
    // 
		if (PrintTexts(&m_dcPrint, m_nPage))     bAgain = TRUE;
    // stampa le lineee dei rettangoli
		if (PrintGrids(&m_dcPrint, m_nPage))     bAgain = TRUE;
    // stampa le bitmap
		if (PrintBitmaps(&m_dcPrint, m_nPage))   bAgain = TRUE;
    // stampa le immagini (png, jpg, ...)
		if (PrintImages(&m_dcPrint, m_nPage))   bAgain = TRUE;
    // stampa i barcode
		if (PrintBarcodes(&m_dcPrint, m_nPage))   bAgain = TRUE;

    // se deve stampare il numero di pagina, lo stampa secondo gli attributi
		// memorizzati nell'oggetto m_PageItem
		if (bStampaNumeroPagina)
		{
		  pFont = NULL;
		  csPag.Format("%d", m_nPage);		
		  m_PageItem.SetText(csPag);
		  m_PageItem.Print(&m_dcPrint, pFont);
		}
    
    // se non deve stampare piu' pagine
		if ( !bAgain)
		{
      // riscandisce gli elementi dell'array con le stringhe e i fields per stampare
			// solo quelli che si voleva stampare nell'ultima pagina 
			PrintStrings(&m_dcPrint, LAST_PAGE);
			PrintFields(&m_dcPrint,  LAST_PAGE);
		  PrintGrids(&m_dcPrint, LAST_PAGE);
    }

		// informa il driver della stampante di aver terminato la scrittura della pagina 
		// e di avanzare alla successiva
    m_dcPrint.EndPage();
  }
   
  return TRUE;
}


 BOOL CPrintInterpreter::PrintPage(CString layoutFName,
								 CStringArray* pFieldsName,
								 CStringArray* pFieldsValue,
								 BOOL (CALLBACK *pfnSetFields)(CStringArray*, CStringArray*),
								 BOOL (CALLBACK *pfnSetTabfields)(CStringArray*, CStringArray*),
                 int nPage)
{
  CRect        rect;
	CString      csPag;
  
	m_LayoutFName  =    layoutFName;
  m_pFieldsName  =    pFieldsName;
  m_pFieldsValue =    pFieldsValue;
  m_pfnSetFields =    pfnSetFields;
  m_pfnSetTabfields = pfnSetTabfields;

  // ricava il numero nLines impostato alla sezione general
	nLines = GetPrivateProfileInt(SEC_GENERAL, KEY_TABLINES, 0, layoutFName);

  // dal file di layout vede se deve scrivere il numero a ciascuna pagina e, in caso
	// affermativo, memorizza come nelle le variabili membro dell'oggetto m_PageItem
  BOOL bStampaNumeroPagina = m_PageItem.Load(SEC_GENERAL, KEY_NR_PAGINA, layoutFName);
   
	/*----- creo il device context per la stampante -----*/
	if (m_dcPrint.m_hDC == NULL)
    return FALSE;
  
	// legge il file di layout per costruire i vari array di tipo CPrintItemArray  
	m_StringItems.Load(SEC_STRINGS,                  layoutFName);
	m_FieldItems.Load(SEC_FIELDS,                    layoutFName);
	m_TabfieldItems.Load(SEC_TABFIELDS,              layoutFName);
	m_TextItems.Load(SEC_TEXTS,                      layoutFName);
  m_GridItems.Load(SEC_GRIDS,                      layoutFName);
  m_BitmapItems.Load(SEC_BITMAPS,                  layoutFName);
  m_ImageItems.Load(SEC_IMAGES,                    layoutFName);
  m_BarcodeItems.Load(SEC_BARCODES,                layoutFName);
  
	  
	CFont* pFont;

  // prepara il driver della stampante a ricevere dati 
	m_dcPrint.StartPage();
  m_nPage = nPage;
	/*----- stampo -----*/
  // stampo le stringhe fisse
	PrintStrings(&m_dcPrint, m_nPage);
  // stampa gli elenchi - liste
	PrintTabfields(&m_dcPrint, m_nPage);
  // stampo i campi
	PrintFields(&m_dcPrint, m_nPage);
  // 
	PrintTexts(&m_dcPrint, m_nPage);
  // stampa le lineee dei rettangoli
	PrintGrids(&m_dcPrint, m_nPage);
  // stampa le bitmap
	PrintBitmaps(&m_dcPrint, m_nPage);
  // stampa le immagini (png, jpg, ...)
	PrintImages(&m_dcPrint, m_nPage);
  // stampa i barcode
	PrintBarcodes(&m_dcPrint, m_nPage);

  // se deve stampare il il numero di pagina, lo stampa secondo gli attributi
	// memorizzati nell'oggetto m_PageItem
	if (bStampaNumeroPagina)
	{
		pFont = NULL;
		csPag.Format("%d", m_nPage);		
		m_PageItem.SetText(csPag);
		m_PageItem.Print(&m_dcPrint, pFont);
	}
  
  // se non deve stampare piu' pagine
	if (m_nPage == m_nTotalePagine)
	{
    // riscandisce gli elementi dell'array con le stringhe e i fields per stampare
		// solo quelli che si voleva stampare nell'ultima pagina 
		PrintStrings(&m_dcPrint, LAST_PAGE);
		PrintFields(&m_dcPrint,  LAST_PAGE);
		PrintGrids(&m_dcPrint, LAST_PAGE);
  }

	// informa il driver della stampante di aver terminato la scrittura della pagina 
	// e di avanzare alla successiva
  m_dcPrint.EndPage();
   
  return TRUE;
}



BOOL CPrintInterpreter::PrintText(CString layoutFName,
       CString printFileName,                           
       CStringArray* pNames,
       CStringArray* pValues,
       BOOL (CALLBACK *pfnSetFields)(CStringArray*, CStringArray*),
			 BOOL (CALLBACK *pfnSetTabfields)(CStringArray*, CStringArray*))
      
{
  FILE* pPrintFile;
  CStringArray   aryTabFieldNames, aryTabFieldValues;
	m_LayoutFName  =    layoutFName;
  m_pFieldsName  =    pNames;
  m_pFieldsValue =    pValues;
  m_pfnSetFields =    pfnSetFields;
  m_pfnSetTabfields = pfnSetTabfields;

  // ricava il numero nLines impostato alla sezione general
	nLines = GetPrivateProfileInt(SEC_GENERAL, KEY_TABLINES, 0, layoutFName);

  // dal file di layout vede se deve scrivere il numero a ciascuna pagina e, in caso
	// affermativo, memorizza come nelle le variabili membro dell'oggetto m_PageItem
  BOOL bStampaNumeroPagina = m_PageItem.Load(SEC_GENERAL, KEY_NR_PAGINA, layoutFName);
  
  if((pPrintFile = fopen(printFileName, "wt")) == NULL)
    return FALSE;
  // Lunghezza della pagina
  fwrite(CMD_RESET_PRN, sizeof(CMD_RESET_PRN) - 1, 1, pPrintFile);
  fwrite(CMD_SET_LN_SPC, sizeof(CMD_SET_LN_SPC) - 1, 1, pPrintFile);
  fwrite(CMD_SET_PG_LEN, sizeof(CMD_SET_PG_LEN) - 1, 1, pPrintFile);
  fwrite(CMD_SET_BT_MRG, sizeof(CMD_SET_BT_MRG) - 1, 1, pPrintFile);

	
	
	int nString, nField, nTabField;
  int xCurr, yCurr;
  int xRef, i;
  CString str;
  CStringItem*   pStringItem = NULL;
  CFieldItem*    pFieldItem = NULL;
  CTabfieldItem* pTabFieldItem = NULL;
  BOOL bMorePages, bTabFieldAgain;
  CPrintItem* pPrintItem;
  
  // Costruisco gli array di PrintItem
	m_StringItems.Load(SEC_STRINGS, m_LayoutFName);
	m_FieldItems.Load(SEC_FIELDS, m_LayoutFName);
	m_TabfieldItems.Load(SEC_TABFIELDS, m_LayoutFName);
  // Divido le coordinate y per Y_UNIT per trovare il numero di linea
  // e inizializzo il file per la stampa
  for(nString = 0; nString < m_StringItems.GetSize(); nString++)
  {
    m_StringItems.GetAt(nString)->m_Y /= Y_UNIT;
    m_StringItems.GetAt(nString)->m_pPrintFile = pPrintFile;
  }
  for(nField = 0; nField < m_FieldItems.GetSize(); nField++)
  {
    m_FieldItems.GetAt(nField)->m_Y /= Y_UNIT;
    m_FieldItems.GetAt(nField)->m_pPrintFile = pPrintFile;
  }
  for(nTabField = 0; nTabField < m_TabfieldItems.GetSize(); nTabField++)
  {
    m_TabfieldItems.GetAt(nTabField)->m_Y /= Y_UNIT;
    m_TabfieldItems.GetAt(nTabField)->m_pPrintFile = pPrintFile;
  }

  // Imposto il numero di pagina
	str.Format("%ld", m_nPage);
  for (i = 0; i < m_pFieldsName->GetSize(); i ++)
    if(m_pFieldsName->GetAt(i) == KEY_CURPAGE)
		  break;
	if(i < m_pFieldsValue->GetSize())
		m_pFieldsValue->SetAt(i, str);
	else
	{
		m_pFieldsName->Add(KEY_CURPAGE);
		m_pFieldsValue->Add(str);
	}

	/***************************** andrea **************************/
	/************** Sostituzione dei caratteri speciali ************/
	/************** nella stampa in modalità testo *****************/

	for(int x=0; x<m_pFieldsValue->GetSize(); x++)
	{
		CString str;
		str = m_pFieldsValue->GetAt(x);
		str.Replace("°", "ø");
		m_pFieldsValue->SetAt(x,str);
		str = m_pFieldsValue->GetAt(x);
		str.Replace("Ø", "í");
		m_pFieldsValue->SetAt(x,str); //1
	}
	/****************************************************************/
	
  // Carico le liste dei field items e dei tabfield items e rimappo
  if(m_pfnSetFields)
    m_pfnSetFields(m_pFieldsName, m_pFieldsValue);
  for(nField = 0; nField < m_FieldItems.GetSize(); nField++)
    ((CFieldItem*)m_FieldItems.GetAt(nField))->Remap(m_pFieldsName, m_pFieldsValue);

  yCurr = 0;
  xCurr = 0;
  bMorePages = FALSE;
  if(m_pfnSetTabfields)
	{
	  bTabFieldAgain = m_pfnSetTabfields(&aryTabFieldNames, &aryTabFieldValues);
    // rimappo i campi
    for(nTabField = 0; nTabField < m_TabfieldItems.GetSize(); nTabField++) 
      ((CTabfieldItem*)m_TabfieldItems.GetAt(nTabField))->Remap(&aryTabFieldNames, &aryTabFieldValues);
  }
  for (nString = 0, nField = 0, nTabField = 0;;)
  {
    xRef = PAGE_WIDTH;
    pStringItem = pFieldItem = pTabFieldItem = NULL;
    pPrintItem = NULL;

    if(nString < m_StringItems.GetSize())
      pStringItem = (CStringItem*)m_StringItems.GetAt(nString);
    if(nField < m_FieldItems.GetSize())
      pFieldItem  = (CFieldItem*)m_FieldItems.GetAt(nField);
    if(nTabField < m_TabfieldItems.GetSize())
      pTabFieldItem = (CTabfieldItem*)m_TabfieldItems.GetAt(nTabField);
    // Scelgo l'item da stampare
    if(pStringItem && pStringItem->m_Y == yCurr && pStringItem->m_X < xRef)
    {
      pPrintItem = pStringItem;
      xRef = pStringItem->m_X;
    }
    if(pFieldItem && pFieldItem->m_Y == yCurr && pFieldItem->m_X < xRef)
    {
      pPrintItem = pFieldItem;
      xRef = pFieldItem->m_X;
    }
    if(pTabFieldItem && pTabFieldItem->m_Y == yCurr && pTabFieldItem->m_X < xRef)
    {
      pPrintItem = pTabFieldItem;
      xRef = pTabFieldItem->m_X;
    }
    // stampo l'item
    if(!pPrintItem)
    {
      // Vado a capo
      fprintf(pPrintFile, CMD_A_CAPO);
      yCurr++;
      xCurr = 0;
    }
    else
    {
      pPrintItem->Print(xCurr, yCurr, pPrintItem->m_Page != LAST_PAGE || !bMorePages);
      if(pPrintItem == pStringItem)
        nString++;
      else if(pPrintItem == pFieldItem)
        nField++;
      else if(pPrintItem == pTabFieldItem)
        nTabField++;
    }
    
    if(nString == m_StringItems.GetSize()
       && nField == m_FieldItems.GetSize()
       && nTabField == m_TabfieldItems.GetSize())
    {
      while(yCurr < MAX_Y)
      {
        fprintf(pPrintFile, CMD_A_CAPO);
        yCurr++;
      }
//      fprintf(pPrintFile, "\f");
      // cambio pagina
      m_nPage++;
    	str.Format("%ld", m_nPage);
      for (i = 0; i < m_pFieldsName->GetSize(); i ++)
        if(m_pFieldsName->GetAt(i) == KEY_CURPAGE)
    		  break;
    	if(i < m_pFieldsValue->GetSize())
    		m_pFieldsValue->SetAt(i, str);
    	else
    	{
    		m_pFieldsName->Add(KEY_CURPAGE);
    		m_pFieldsValue->Add(str);
    	}

			/***************************** andrea **************************/
			/************** Sostituzione dei caratteri speciali ************/
			/************** nella stampa in modalità testo *****************/
			
			for(int x=0; x<m_pFieldsValue->GetSize(); x++)
			{
				CString str;
				str = m_pFieldsValue->GetAt(x);
				str.Replace("°", "ø");
				m_pFieldsValue->SetAt(x,str);
				str = m_pFieldsValue->GetAt(x);
				str.Replace("Ø", "í");
				m_pFieldsValue->SetAt(x,str);//2
			}
			
			/****************************************************************/

      // Carico la lista dei field items e rimappo
      if(m_pfnSetFields)
        m_pfnSetFields(m_pFieldsName, m_pFieldsValue);
      for(nField = 0; nField < m_FieldItems.GetSize(); nField++)
        ((CFieldItem*)m_FieldItems.GetAt(nField))->Remap(m_pFieldsName, m_pFieldsValue);



      if(nLines)
        break;

      yCurr = xCurr = 0;
      nLines = GetPrivateProfileInt(SEC_GENERAL, KEY_TABLINES, 0, layoutFName);
      nString   = 0;
      nField    = 0;
		  bMorePages = FALSE;
      for(nTabField = 0; nTabField < m_TabfieldItems.GetSize(); nTabField++)
      {
        ((CTabfieldItem*)m_TabfieldItems.GetAt(nTabField))->NewPage();
        m_TabfieldItems.GetAt(nTabField)->m_Y /= Y_UNIT;
      }
      nTabField = 0;
      continue;
    }
	  if(nTabField == m_TabfieldItems.GetSize() && m_pfnSetTabfields)
    {
			if(nLines)
			{
			  if(bTabFieldAgain)
				{
					bTabFieldAgain = m_pfnSetTabfields(&aryTabFieldNames, &aryTabFieldValues);
					// rimappo i campi
					for(nTabField = 0; nTabField < m_TabfieldItems.GetSize(); nTabField++) 
						((CTabfieldItem*)m_TabfieldItems.GetAt(nTabField))->Remap(&aryTabFieldNames, &aryTabFieldValues);
					if(--nLines)
						nTabField = 0;
					bMorePages = TRUE;
				}
				else
				  bMorePages = FALSE;
			}
    }
  }
  fclose(pPrintFile);
  return TRUE;
}
/********************************************************************
* Funzione   : PrintStrings
* Descrizione: Stampa le stringhe fisse esaminando l'array m_StringItem
               (ogni elemento dell'array e' un oggetto che indica come
							 stampare una certa stringa) 
* Parametri  : pDC =  puntatore al contesto di dispositivo usato per stampare
               page = numero di pagina che attualmente si sta stampando
							 (a meno che nPage sia uguale a LAST_PAGE, in tal caso significa
							 che vogliamo stampare solo gli elementi che si volevano stampare nell'
							 ultima pagina)
* Ritorno    : TRUE  se deve stampare ancora una pagina
               FALSE altrimenti
* Note       : 
*********************************************************************/
BOOL CPrintInterpreter::PrintStrings(CDC* pDC, int page)
{ 
	BOOL   bAgain = FALSE;
	CFont* pOldFont = pDC->GetCurrentFont();
	CFont* pFont = NULL;
  
	// esamina tutto l'array m_StringItems prima costruito
	for (int i = 0; i < m_StringItems.GetSize(); i ++)
  {
    if (page >= 0)
		{
			// se la variabile m_Page dell'elemento i-esimo della'array e' zero o e' uguale
			// alla pagina che si sta attualmente stampando, stampa l'elemento
			if (!m_StringItems[i].m_Page || m_StringItems[i].m_Page == page)
			{
				// stampa l'elemento (stringa) i-esimo e memorizza l'indirizzo del font
				pFont = (CFont*)m_StringItems[i].Print(pDC, pFont);
			}
    
			if (m_StringItems[i].m_Page > page)
				bAgain = TRUE;
		}
		else if (m_StringItems[i].m_Page == LAST_PAGE)
		{
			// stampa l'elemento (stringa) i-esimo e memorizza l'indirizzo del font
			pFont = (CFont*)m_StringItems[i].Print(pDC, pFont);
		}
  }
  
	// se ha il puntatore al font usato per stampare l'ultimo elemento
  pDC->SelectObject(pOldFont);
	if(pFont)
  {
    pFont->DeleteObject();
    delete pFont;
  }
	// restituisce un flag indicante se c'e ancora stringhe da stampare in una
	// pagina successiva
	return bAgain;
}

/********************************************************************
* Funzione   : PrintFields
* Descrizione: 
* Parametri  : 
* Ritorno    : 
* Note       : 
*********************************************************************/
BOOL CPrintInterpreter::PrintFields(CDC* pDC, int page)
{
  int     i;
  BOOL    bAgain = FALSE;
  CString str; 
	CFont* pOldFont = pDC->GetCurrentFont();
	CFont* pFont = NULL;
	
	if (m_pfnSetFields)
    bAgain = (*m_pfnSetFields)(m_pFieldsName, m_pFieldsValue);
	/*---- sostituisco il numero di pagina ----*/
	str.Format("%ld", page);
	for (i = 0; i < m_pFieldsName->GetSize(); i ++)
    if(m_pFieldsName->GetAt(i) == KEY_CURPAGE)
		  break;
	if(i < m_pFieldsValue->GetSize())
		m_pFieldsValue->SetAt(i, str);
	else
	{
		m_pFieldsName->Add(KEY_CURPAGE);
		m_pFieldsValue->Add(str);
	}

	for (i = 0; i < m_FieldItems.GetSize(); i ++)
    ((CFieldItem*)(m_FieldItems.GetAt(i)))->Remap(m_pFieldsName,
                                                  m_pFieldsValue);  
	// esamina tutto l'array m_FieldItems prima costruito	
	for (i = 0; i < m_FieldItems.GetSize(); i ++)
  {
    if (page >= 0)
		{
		  if ( !m_FieldItems[i].m_Page || m_FieldItems[i].m_Page == page)
        pFont = (CFont*)m_FieldItems[i].Print(pDC, pFont);
		}
		else if (m_FieldItems[i].m_Page == LAST_PAGE)
		{
      pFont = (CFont*)m_FieldItems[i].Print(pDC, pFont);		
		}
  }
  pDC->SelectObject(pOldFont);
	if(pFont)
  {
    pFont->DeleteObject();
    delete pFont;
  }
	return bAgain;
}

/********************************************************************
* Funzione   : PrintTabfields
* Descrizione: 
* Parametri  : 
* Ritorno    : TRUE se deve ancora stampare pagine
* Note       : 
*********************************************************************/
BOOL CPrintInterpreter::PrintTabfields(CDC* pDC, int page)
{
  int          i, n, hMax;
  BOOL         bAgain = FALSE;
	CFont* pOldFont = pDC->GetCurrentFont();
	CFont* pFont = NULL;
  CStringArray names, values;

  // da eseguire per il numero n di volte (linee) impostate alla sezione general
	// quindi si stampano, al massimo, n righe della lista per pagina
	for (n = 0; n < nLines; n ++)
  {
    if (m_pfnSetTabfields)
      bAgain = (*m_pfnSetTabfields)(&names, &values);
    else 
		  return FALSE;
    // Altezza dei tabfield
    hMax = m_TabfieldItems.GetAt(0)->m_H;
    if(hMax < 0)
      hMax *= -1;
		for(i = 0; i < m_TabfieldItems.GetSize(); i ++)
			((CFieldItem*)(m_TabfieldItems.GetAt(i)))->Remap(&names, &values);  
		for (i = 0; i < m_TabfieldItems.GetSize(); i ++)
    {
			pFont = (CFont*)m_TabfieldItems[i].Print(pDC, pFont);
      if(m_TabfieldItems.GetAt(i)->m_H < 0)
      {
        if((m_TabfieldItems.GetAt(i)->m_Y + hMax) > Y_PAGE_LIMIT)
          n = nLines;
        else
          n = 0;
      }
    }
	  if (!bAgain)
		  break;
    // Calcolo la y
    hMax = 0;
    for(i = 0; i < m_TabfieldItems.GetSize(); i++)
    {
      if(hMax < (m_TabfieldItems.GetAt(i))->m_HDrawn)
        hMax = (m_TabfieldItems.GetAt(i))->m_HDrawn;
    }
    for(i = 0; i < m_TabfieldItems.GetSize(); i++)
    {
      if(m_TabfieldItems.GetAt(i)->m_H < 0)
        (m_TabfieldItems.GetAt(i))->m_Y += (hMax + 40);
      else
        (m_TabfieldItems.GetAt(i))->m_Y += m_TabfieldItems.GetAt(i)->m_H;
    }
  }
	pDC->SelectObject(pOldFont);
	if(pFont)
	{
		pFont->DeleteObject();
		delete pFont;
		pFont = NULL;
	}

	for (i = 0; i < m_TabfieldItems.GetSize(); i ++)
  {
/*
    hMax = m_TabfieldItems.GetAt(i)->m_H;
    if(hMax < 0)
    {
      hMax *= -1;
      if((m_TabfieldItems.GetAt(i)->m_Y + hMax) > Y_PAGE_LIMIT)
        ((CTabfieldItem*)(m_TabfieldItems.GetAt(i)))->NewPage();
    }
    else
*/
    ((CTabfieldItem*)(m_TabfieldItems.GetAt(i)))->NewPage();
  }
  
  return bAgain;
}

/********************************************************************
* Funzione   : PrintTexts
* Descrizione: 
* Parametri  : 
* Ritorno    : 
* Note       : 
*********************************************************************/
BOOL CPrintInterpreter::PrintTexts(CDC* pDC, int page)
{
  int    i;
  BOOL   bAgain = FALSE;
  CFont* pOldFont;
  
  pOldFont = NULL;
  
	for (i = 0; i < m_TextItems.GetSize(); i++)
  {
    if(!m_TextItems[i].m_Page || m_TextItems[i].m_Page == page)
      pOldFont = (CFont*)m_TextItems[i].Print(pDC, pOldFont);
    if(m_TextItems[i].m_Page > page)
      bAgain = TRUE;
  }
  if(pOldFont)
  {
    pOldFont = pDC->SelectObject(pOldFont);
    pOldFont->DeleteObject();
    delete pOldFont;
  }
  return bAgain;
}

/********************************************************************
* Funzione   : PrintGrids
* Descrizione: 
* Parametri  : 
* Ritorno    : 
* Note       : 
*********************************************************************/
BOOL CPrintInterpreter::PrintGrids(CDC* pDC, int page)
{
  int   i;
  BOOL  bAgain = FALSE;

  for(i = 0; i < m_GridItems.GetSize(); i++)
  {
    if(!m_GridItems[i].m_Page || m_GridItems[i].m_Page == page)
      m_GridItems[i].Print(pDC, NULL);
    if(m_GridItems[i].m_Page > page)
      bAgain = TRUE;
  }
  return bAgain;
}

/********************************************************************
* Funzione   : PrintBitmaps
* Descrizione: 
* Parametri  : 
* Ritorno    : 
* Note       : 
*********************************************************************/
BOOL CPrintInterpreter::PrintBitmaps(CDC* pDC, int page)
{
  int   i;
  BOOL  bAgain = FALSE;

  for(i = 0; i < m_BitmapItems.GetSize(); i++)
  {
    if(!m_BitmapItems[i].m_Page || m_BitmapItems[i].m_Page == page)
      m_BitmapItems[i].Print(pDC, NULL);
    if(m_BitmapItems[i].m_Page > page)
      bAgain = TRUE;
  }
  return bAgain;
}

/********************************************************************
* Funzione   : PrintImages
* Descrizione: 
* Parametri  : 
* Ritorno    : 
* Note       : 
*********************************************************************/
BOOL CPrintInterpreter::PrintImages(CDC* pDC, int page)
{
  int   i;
  BOOL  bAgain = FALSE;

  for(i = 0; i < m_ImageItems.GetSize(); i++)
  {
    if(!m_ImageItems[i].m_Page || m_ImageItems[i].m_Page == page)
      m_ImageItems[i].Print(pDC, NULL);
    if(m_ImageItems[i].m_Page > page)
      bAgain = TRUE;
  }
  return bAgain;
}

/********************************************************************
* Funzione   : PrintBarcodes
* Descrizione: 
* Parametri  : 
* Ritorno    : 
* Note       : 
*********************************************************************/
BOOL CPrintInterpreter::PrintBarcodes(CDC* pDC, int page)
{
  int   i;
  BOOL  bAgain = FALSE;

  for(i = 0; i < m_BarcodeItems.GetSize(); i++)
  {
		m_BarcodeItems[i].SetNomefile(m_DocName);
    if(!m_BarcodeItems[i].m_Page || m_BarcodeItems[i].m_Page == page)
      m_BarcodeItems[i].Print(pDC, NULL);
    if(m_BarcodeItems[i].m_Page > page)
      bAgain = TRUE;
  }
  return bAgain;
}

void CPrintInterpreter::SetHeaderFile(CString	headerFName)
{
	m_HeaderFName = headerFName;
}

void CPrintInterpreter::SetDocName(CString	docName)
{
	m_DocName = docName;
}


/*----- implementazione di CPrintItem -----*/
CPrintItem::CPrintItem(void) : CObject()
{
  m_X      = 0;
  m_Y      = 0;
  m_W      = 0;
  m_H      = 0;
  m_Page   = 0;
	m_Color	 = 0x00000000;    // nero
	m_Nomefile = "";
}

BOOL CPrintItem::Load(CString sec, CString key, CString layoutFName)
{
  return TRUE;
}

void CPrintItem::SetNomefile(CString nomefile)
{
	m_Nomefile = nomefile;
}

CGdiObject* CPrintItem::Print(CDC* pDC, CGdiObject* pGdiObject)
{
  return NULL;
}

int CPrintItem::Print(int& xCurr, int& yCurr, BOOL bPrint)
{
  return 0;
}

void CPrintItem::SetFont(CString strFont)
{
}

/*----- implementazione di CPrintItemArray -----*/
CPrintItemArray::CPrintItemArray(void)
{
}

CPrintItemArray::~CPrintItemArray(void)
{
  int i;

  for (i = 0; i < GetSize(); i++)
    delete GetAt(i);
  RemoveAll();
}

/********************************************************************
* Funzione   : CPrintItemArray::Load
* Descrizione: Costruisce gli elementi dell'array di oggetti di classe
               CPrintItem, in base alla sezione letta dal file di layout
* Parametri  : sec =         nome della sezione
               layoutFName = nome del file
* Ritorno    :     
* Note       : 
*********************************************************************/
int CPrintItemArray::Load(CString sec, CString layoutFName, CString headerFName)
{
  int         i, p;
  char        buffer[1536];
	char				bufheader[512];
  CPrintItem* pPrintItem;

  for (i = 0; i < GetSize(); i++)
    delete GetAt(i);
  RemoveAll();

  // copia in buffer l'elenco di tutte le chiavi presenti alla sezione sec 
	GetPrivateProfileString(sec, NULL, "", buffer, sizeof(buffer) - 1, layoutFName);
  
	// esamina tutto il buffer, cioe' tutte le chiavi della sezione
	for (p = 0; buffer[p]; p += (strlen(buffer + p) + 1))
  {
    // alloca un nuovo oggetto derivato da CPrintItem, in base alla sezione sec
		if (sec == SEC_STRINGS)        
		  pPrintItem = new CStringItem();
    else if(sec == SEC_FIELDS)
		  pPrintItem = new CFieldItem();
    else if (sec == SEC_TABFIELDS)
		  pPrintItem = new CTabfieldItem();
    else if(sec == SEC_TEXTS)
		  pPrintItem = new CTextItem();
    else if(sec == SEC_GRIDS)
		  pPrintItem = new CGridItem();
    else if(sec == SEC_BITMAPS)
		  pPrintItem = new CBitmapItem();
    else if(sec == SEC_IMAGES)
		  pPrintItem = new CImageItem();
    else if(sec == SEC_BARCODES)
		  pPrintItem = new CBarcodeItem();
    else
		  continue;
    
		// imposta le variabili membro dell'oggetto appena allocato in base al valore
		// presente a destra della chiave corrente
		if (pPrintItem->Load(sec, buffer + p, layoutFName))
    {
      // calcola la variabile m_Page che viene :
			// LAST_PAGE (valore negativo, controlla nel define) se la chiave e' minore di zero
			// 0 se la chiave e' compresa tra 0 e 999
			// 1 se la chiave e' compresa tra 1000 e 1999, e cosi' via.
			
			// per gli oggetti di classe CStringItem e CFieldsItem:
			// se m_Page e' = LAST_PAGE l'item verra' stampato solo nell'ultima pagina,
			// se m_Page e' 0,          l'item verra' stampato in tutte le pagine,
			// se m_Page e' > 0         l'item verra' stampato solo nella pagina indicata
			int nChiave = atoi((LPCSTR)(buffer + p));
			
			if (nChiave < 0)
			  pPrintItem->m_Page = LAST_PAGE;			
			else
			  pPrintItem->m_Page = nChiave / 1000;
      // inserisce il nuovo oggetto nell'array 
      if(!GetSize())
        Add(pPrintItem);
      else
      {
        for(i = 0; i < GetSize(); i++)
        {
          if(GetAt(i)->m_Y > pPrintItem->m_Y)
          {
            InsertAt(i, pPrintItem);
            break;
          }
        }
        if(i == GetSize())
          Add(pPrintItem);
      }
    }
  }

	// Inserimento header (se definito) s.c. luglio 2016
	if(headerFName.IsEmpty() == false)
	{
		GetPrivateProfileString(sec, NULL, "", bufheader, sizeof(bufheader) - 1, headerFName);
		// esamina tutto il buffer, cioe' tutte le chiavi della sezione
		for (p = 0; bufheader[p]; p += (strlen(bufheader + p) + 1))
		{
			// alloca un nuovo oggetto derivato da CPrintItem, in base alla sezione sec
			if (sec == SEC_STRINGS)        
				pPrintItem = new CStringItem();
			else if(sec == SEC_FIELDS)
				pPrintItem = new CFieldItem();
			else if (sec == SEC_TABFIELDS)
				pPrintItem = new CTabfieldItem();
			else if(sec == SEC_TEXTS)
				pPrintItem = new CTextItem();
			else if(sec == SEC_GRIDS)
				pPrintItem = new CGridItem();
			else if(sec == SEC_BITMAPS)
				pPrintItem = new CBitmapItem();
			else if(sec == SEC_IMAGES)
				pPrintItem = new CImageItem();
			else if(sec == SEC_BARCODES)
				pPrintItem = new CBarcodeItem();
			else
				continue;
    
			// imposta le variabili membro dell'oggetto appena allocato in base al valore
			// presente a destra della chiave corrente
			if (pPrintItem->Load(sec, bufheader + p, headerFName))
			{
				int nChiave = atoi((LPCSTR)(bufheader + p));
				
				// stampa in tutte le pagine
				pPrintItem->m_Page = 0;			
				// inserisce il nuovo oggetto nell'array 
				if(!GetSize())
					Add(pPrintItem);
				else
				{
					for(i = 0; i < GetSize(); i++)
					{
						if(GetAt(i)->m_Y > pPrintItem->m_Y)
						{
							InsertAt(i, pPrintItem);
							break;
						}
					}
					if(i == GetSize())
						Add(pPrintItem);
				}
			}
		}
	}

  // restituisce il numero di oggetti allocati dell'array
	return GetSize();
}


CPrintItem& CPrintItemArray::operator[](int i)
{
  return (*GetAt(i));
}

CPrintItem* CPrintItemArray::GetAt(int i)
{
  return (CPrintItem*)CObArray::GetAt(i);
}

/*-----------------------implementazione di CStringItem -------------------------*/
CStringItem::CStringItem(void) : CPrintItem()
{
  m_Text       = "";
  m_TextAlign  = TA_LEFT;
  m_FontWidth  = 50;
  m_FontHeight = 100;
  m_FontWeight = FW_NORMAL;
  m_bFontItalic    = FALSE;
  m_bFontUnderline = FALSE;
	m_nEdge = 0;
  m_FontName   = "System";
	m_bNull = TRUE;
}

/********************************************************************
* Funzione   : CStringItem::Load 
* Descrizione: Imposta le variabili membro in base ai dati contenuti 
               nel file ad una certa sezione e ad una certa chiave
* Parametri  : sec = sezione
               key = chiave
							 layoutFName = nome del file               
* Ritorno    :     
* Note       : 
*********************************************************************/
BOOL CStringItem::Load(CString sec, CString key, CString layoutFName)
{
  int     p;
  char    buffer[256];
	static  int nFontWidth, nFontHeight;
	static  CString strFontName, strFlags;

  // ricava le coordinate generali di traslazione
  int zerox = GetPrivateProfileInt(SEC_GENERAL, KEY_XZERO, 0, layoutFName);
  int zeroy = GetPrivateProfileInt(SEC_GENERAL, KEY_YZERO, 0, layoutFName);
  
  // copia in buffer la stringa presente alla sezione sec e alla chiave key 	
	GetPrivateProfileString(sec, key, "", buffer, sizeof(buffer) - 1, layoutFName);
  
	/*----- sostituisco le virgole con 0 e termino con 00 -----*/
  for (p = 0; buffer[p]; p ++)
	{
    if (buffer[p] == ',') buffer[p] = 0;
	}
	buffer[p + 1] = 0;
  	/*----- calcola la coordinata m_X -----*/
  if ( !buffer[p = 0])
	  return FALSE;
	sscanf(buffer + p, "%d", &m_X);

	if ((buffer[p] == '+') || (buffer[p] == '-'))
		m_X += CStringItem::m_LastX;
	else
		m_X += zerox;
	
	p += (strlen(buffer + p) + 1);
	m_LastX = m_X;
	/*----- calcola la coordinata m_Y -----*/
  if(!buffer[p])  return FALSE;
	sscanf(buffer + p, "%d", &m_Y);
	if ((buffer[p] == '+') || (buffer[p] == '-'))
		m_Y += CStringItem::m_LastY;				
	else
		m_Y += zeroy;
  p += (strlen(buffer + p) + 1);
	m_LastY = m_Y;
  	/*----- m_W -----*/
  if(!buffer[p]) return FALSE;
  sscanf(buffer + p, "%d", &m_W);
  p += (strlen(buffer + p) + 1);
  /*----- m_H -----*/
  if(!buffer[p]) return FALSE;
  sscanf(buffer + p, "%d", &m_H);
  p += (strlen(buffer + p) + 1);
	/*----- m_FontName -----*/
  if(!buffer[p]) return FALSE;
  m_FontName = buffer + p;
  p += (strlen(buffer + p) + 1);
  
	if (m_FontName != NO_FONT)
  {
    /*----- m_FontWidth -----*/
    if(!buffer[p]) return FALSE;
    sscanf(buffer + p, "%d", &m_FontWidth);
    nFontWidth = m_FontWidth = (m_FontWidth * 2 / 3);
    p += (strlen(buffer + p) + 1);
    /*----- m_FontHeight -----*/
    if(!buffer[p]) return FALSE;
    sscanf(buffer + p, "%d", &m_FontHeight);
    nFontHeight = m_FontHeight = (m_FontHeight);
    p += (strlen(buffer + p) + 1);
    /*----- i flag -----*/
    strFlags = buffer + p;
    p += (strlen(buffer + p) + 1);
  }
  else
  {
    m_FontWidth  = nFontWidth;
    m_FontHeight = nFontHeight;
		m_FontName   = strFontName;
  }
  if(strFlags.FindOneOf("Rr") != -1)      m_TextAlign = DT_RIGHT;
  else if(strFlags.FindOneOf("Cc") != -1) m_TextAlign = DT_CENTER;
  else                                    m_TextAlign = DT_LEFT;
  if(strFlags.FindOneOf("Vv") != -1)      m_TextAlign |= DT_VCENTER;
  m_bFontItalic    = (strFlags.FindOneOf("Ii") != -1);
  m_bFontUnderline = (strFlags.FindOneOf("Uu") != -1);
  m_FontWeight     = (strFlags.FindOneOf("Bb") != -1 ? FW_BOLD : FW_NORMAL);
	m_nEdge = 0;
	if(strFlags.FindOneOf("Nn") != -1)
		m_nEdge |= EDGE_NORTH; 
	if(strFlags.FindOneOf("Ww") != -1)
		m_nEdge |= EDGE_WEST; 
	if(strFlags.FindOneOf("Ss") != -1)
		m_nEdge |= EDGE_SOUTH; 
	if(strFlags.FindOneOf("Ee") != -1)
		m_nEdge |= EDGE_EAST; 
	if(strFlags.FindOneOf("Xx") != -1)
		m_nEdge |= EDGE_NONEIFNULL; 
  /*----- la stringa -----*/
  m_Text = buffer + p;
  p += (strlen(buffer + p) + 1);
	/*----- colore -----*/
  sscanf(buffer + p, "%x", &m_Color);
  return TRUE;
}

/********************************************************************
* Funzione   : CStringItem::Print
* Descrizione: 
* Parametri  : pDC = puntatore al contesto di dispositivo da usare per stampare
               pOldFont = puntatore all'oggetto GDI da usare per disegnare                
* Ritorno    :     
* Note       : 
*********************************************************************/
CGdiObject* CStringItem::Print(CDC* pDC, CGdiObject* pOldFont)
{
	static  int  nFontWidth, nFontHeight, nFontWeight, nHRect;
	static  BOOL bFontItalic, bFontUnderline;
	static  CString strFontName;

  CFont* pFont;
  CPen   penBlack(PS_SOLID, 2, RGB(0x00, 0x00, 0x00));

	if(!pOldFont
		 || nFontWidth != m_FontWidth || nFontHeight != m_FontHeight 
	   || bFontItalic != m_bFontItalic || bFontUnderline != m_bFontUnderline
	   || strFontName != m_FontName || nFontWeight != m_FontWeight)
	{
	  /*--- il font e' cambiato: lo cambio ----*/
		pFont = new CFont();
		CSize sz(m_FontWidth, m_FontHeight);
    pDC->DPtoLP(&sz);
/*
    pFont->CreateFont(sz.cy, sz.cx, 0, 0, m_FontWeight,
                      m_bFontItalic, m_bFontUnderline, 0, DEFAULT_CHARSET,
                      OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                      DEFAULT_QUALITY, DEFAULT_PITCH,
                      m_FontName);
*/
    pFont->CreateFont(m_FontHeight, m_FontWidth, 0, 0, m_FontWeight,
                      m_bFontItalic, m_bFontUnderline, 0, DEFAULT_CHARSET,
                      OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                      DEFAULT_QUALITY, DEFAULT_PITCH,
                      m_FontName);
		pDC->SelectObject(pFont);
		if(pOldFont)
		{
      pOldFont->DeleteObject();
			delete pOldFont;
		}
	}
	else
	  pFont = (CFont*)pOldFont;
	/* impostazione colore */
//	COLORREF col = RGB(0, 32, 96);
	pDC->SetTextColor(m_Color);
	/*---- memorizzo i dati del font -----*/
	nFontWidth     = m_FontWidth;
	nFontHeight    = m_FontHeight;
	bFontItalic    = m_bFontItalic;
	bFontUnderline = m_bFontUnderline;
	strFontName    = m_FontName;
	nFontWeight    = m_FontWeight;
  /*---- imposto gli allineamenti ----*/
  pDC->SetTextAlign(TA_NOUPDATECP);
 	UINT nTextAlign = m_TextAlign;
	if(nTextAlign & DT_VCENTER)
    nTextAlign |= DT_SINGLELINE;
	else
	  nTextAlign |= DT_WORDBREAK;
	/*--- stampo il testo -----*/
  nHRect = m_H;
  if(m_H < 0)
    nHRect *= -1;
	if(nTextAlign & DT_RIGHT)
		m_Text += " ";
  m_HDrawn = pDC->DrawText(m_Text, CRect(m_X, m_Y, m_X + m_W, m_Y + nHRect), nTextAlign);
  /*--- stampo il bordo ----*/
	//CPen* pOldPen;
	//pOldPen = pDC->SelectObject(&penBlack);
	if(m_nEdge & EDGE_NORTH)
	{
		pDC->MoveTo(m_X, m_Y);
		pDC->LineTo(m_X + m_W, m_Y);
	}
	if(m_nEdge & EDGE_EAST && !(m_bNull && (m_nEdge & EDGE_NONEIFNULL)))
	{
		pDC->MoveTo(m_X + m_W, m_Y);
		pDC->LineTo(m_X + m_W, m_Y + m_H);
	}
	if(m_nEdge & EDGE_SOUTH)
	{
		pDC->MoveTo(m_X, m_Y + m_H);
		pDC->LineTo(m_X + m_W, m_Y + m_H);
	}
	if(m_nEdge & EDGE_WEST && !(m_bNull && (m_nEdge & EDGE_NONEIFNULL)))
	{
		pDC->MoveTo(m_X, m_Y);
		pDC->LineTo(m_X, m_Y + m_H);
	}
	//pDC->SelectObject(pOldPen);
	// restituisce il font 
	return pFont;
}

/********************************************************************
* Funzione   : CStringItem::Print
* Descrizione: Stampa in modalità testo
* Parametri  : xCurr = coordinata x corrente                
*              yCurr = coordinata y corrente
* Ritorno    :     
* Note       : 
*********************************************************************/
BOOL CStringItem::Print(int& xCurr, int& yCurr, BOOL bPrint)
{
  int n = 0;
  if(m_Y != yCurr)
    return FALSE;
  if(m_X < xCurr)
    return FALSE;
/*
  if(n = ((m_X - xCurr) * X_MINI_UNIT) / PAGE_WIDTH)
  {  
    // Metto tanti spazi quanti ne servono per arrivare a m_X 
    SetFont(MINI_FONT);
    for(; n; n--)
      fprintf(m_pPrintFile, " ");
  }
*/
  // Imposto il font e stampo
  if(m_FontWidth <= (PAGE_WIDTH / X_MINI_UNIT))
  {
    SetFont(MINI_FONT);
  for(n = ((m_X - xCurr) * X_MINI_UNIT) / PAGE_WIDTH; n; n--)
      fprintf(m_pPrintFile, " ");
    n = X_MINI_UNIT;
  }
  else if(m_FontWidth <= (PAGE_WIDTH / X_NORMAL_UNIT))
  {
    SetFont(NORMAL_FONT);
  for(n = ((m_X - xCurr) * X_NORMAL_UNIT) / PAGE_WIDTH; n; n--)
      fprintf(m_pPrintFile, " ");
    n = X_NORMAL_UNIT;
  }
  else
  {
    SetFont(MAXI_FONT);
    for(n = ((m_X - xCurr) * X_MAXI_UNIT) / PAGE_WIDTH; n; n--)
      fprintf(m_pPrintFile, " ");
    n = X_MAXI_UNIT;
  }
  //fwrite(m_Text, m_Text.GetLength(), m_Text.GetLength(), m_pPrintFile);
  CString str = m_Text;
	str.Replace("%", "%%");
	if(bPrint)
    fprintf(m_pPrintFile, str);
  if(str.IsEmpty())
    xCurr = m_X;
  else  
  {
    xCurr = str.GetLength() * (PAGE_WIDTH / n);
    xCurr += m_X;
  }
  return TRUE;
}


/********************************************************************
* Funzione   : CStringItem::SetFont
* Descrizione: Invia alla stampante il comando per l'impostazione del font
* Parametri  : Stringa del font selezionato
* Ritorno    :     
* Note       : 
*********************************************************************/
void CStringItem::SetFont(CString strFont)
{
  static CString strOldFont;

	if(strOldFont == strFont)
	  return;
  if(strFont == (MINI_FONT))
    fprintf(m_pPrintFile, CMD_SET_MINI);
  else if(strFont== MAXI_FONT)
    fprintf(m_pPrintFile, "\033\016");
  else
  {
    fprintf(m_pPrintFile, CMD_DESET_MINI);
    fprintf(m_pPrintFile, CMD_DESET_MAXI);
  }
	strOldFont = strFont;
}


/*----------------------- implementazione di CFieldItem ---------------------*/
CFieldItem::CFieldItem(void) : CStringItem()
{
  m_Key = "";
}

/********************************************************************
* Funzione   : CFieldItem::Load
* Descrizione: Imposta le variabili membro in base ai dati contenuti 
               nel file ad una certa sezione e ad una certa chiave
* Parametri  : sec = sezione
               key = chiave
							 layoutFName = nome del file               
* Ritorno    :     
* Note       : 
*********************************************************************/
BOOL CFieldItem::Load(CString sec, CString key, CString layoutFName)
{
  // ricava i dati del campo in base a cosa e' scritto alla chiave key
	// in particolare ricava la variabile m_Text
	BOOL r = CStringItem::Load(sec, key, layoutFName);

  // eguaglia m_Key a m_Text in quuanto la chiave e' l'ultima parte dellla riga 
	// nel file di layout alla sezione fields 
	m_Key = m_Text;
  // resetta m_Text
	m_Text = "";
  
	return r;
}

#if 0
// stampa
CGdiObject* CFieldItem::Print(CDC* pDC, CGdiObject* pFont)
{
	if(!m_bNull)
		return CStringItem::Print(pDC, pFont);
  return pFont;
}

// Stampa in modalità testo
BOOL CFieldItem::Print(int& xCurr, int& yCurr, BOOL bPrint)
{
	if(!m_bNull)
		return CStringItem::Print(xCurr, yCurr, bPrint);
  return bPrint;
}
#endif

/********************************************************************
* Funzione   : Remap
* Descrizione: Sostituisce 
* Parametri  : pEntries = array con le stringhe di riferimento
                          (costruito run -time)
               pValues = array con le stringhe con i valori da stampare
							            (costruito run -time)
* Ritorno    :     
* Note       : 
*********************************************************************/
BOOL CFieldItem::Remap(CStringArray* pEntries, CStringArray* pValues)
{
  int i;
  // se e' vuoto uno dei due array, esce subito
  if ( !pEntries || !pValues)
	  return TRUE;

  // esamina l'array con le stringhe di riferimento costruite run-time
	for (i = 0; i < pEntries->GetSize(); i ++)
	{
    // se la chiave corrente letta dal file di layout coincide con quella
		// nella stringa di riferimento, esce
		if ( !m_Key.CompareNoCase(pEntries->GetAt(i)))
      break;
  }
	// se ha trovato la chiave corrente, nell'array di stringhe
	if (i < pEntries->GetSize() && i < pValues->GetSize())
  {
    // vede quale stringa mettere al posto della stringa chiave corrente 
		m_Text = pValues->GetAt(i);
		m_bNull = FALSE;
    return TRUE;
  }
  
	// chiave non trovata, restituisce la stringa nulla
	m_Text = "";
  return FALSE;
}

/*----- implementazione di CTabfiledItem -----*/
CTabfieldItem::CTabfieldItem(void) : CFieldItem()
{
}
/********************************************************************
* Funzione   : CTabfieldItem::Print
* Descrizione: Stampa in modalità testo
* Parametri  : xCurr = coordinata x corrente                
*              yCurr = coordinata y corrente
* Ritorno    :     
* Note       : 
*********************************************************************/
BOOL CTabfieldItem::Print(int& xCurr, int& yCurr, BOOL bPrint)
{
  CFieldItem::Print(xCurr, yCurr, bPrint);
  m_Y++;
  return TRUE;
}

/********************************************************************
* Funzione   : CTabfieldItem::SetFont
* Descrizione: Invia alla stampante il comando per l'impostazione del font
* Parametri  : Stringa del font selezionato
* Ritorno    :     
* Note       : 
*********************************************************************/
void CTabfieldItem::SetFont(CString strFont)
{
  CStringItem::SetFont(strFont);
}

/********************************************************************
* Funzione   : CTabfieldItem::Load
* Descrizione: 
* Parametri  : sec = sezione
               key = chiave
							 layoutFName = nome del file               
* Ritorno    :     
* Note       : 
*********************************************************************/
BOOL CTabfieldItem::Load(CString sec, CString key, CString layoutFName)
{
  BOOL bRet;
  
	// chiama la Load della classe CFieldItem per impostare
  bRet = CFieldItem::Load(sec, key, layoutFName);
  m_ZeroY = m_Y;
  return bRet;
}

/********************************************************************
* Funzione   : CTabfieldItem::Print
* Descrizione: Stampa un item di una lista
* Parametri  :                
* Ritorno    :     
* Note       : 
*********************************************************************/
CGdiObject* CTabfieldItem::Print(CDC* pDC, CGdiObject* pOldFont)
{
  CGdiObject* pGdiObj;

  pGdiObj = CFieldItem::Print(pDC, pOldFont);
//	m_Y += (m_FontHeight * 11 / 10);  
//	m_Y += m_H;  
	return pGdiObj;
}

/********************************************************************
* Funzione   : NewPage
* Descrizione: inizializza il valore della variabile membro m_Y
               ponendolo uguale a quello della variabile m_ZeroY 
* Parametri  :                
* Ritorno    :     
* Note       : 
*********************************************************************/
void CTabfieldItem::NewPage(void)
{
	m_Y = m_ZeroY;
}

/*----- implementazione di CPageItem -----*/

/********************************************************************
* Funzione   : CPageItem::SetText
* Descrizione: Imposta la variabile m_Text dell'oggetto di classe CPageItem 
* Parametri  : 
* Ritorno    : 
* Note       : 
*********************************************************************/
BOOL CPageItem::SetText(CString cs)
{
  m_Text = cs;
  return true;
}


/*----- implementazione di CTextItem -----*/
CTextItem::CTextItem(void) : CStringItem()
{
  m_FileName = "";
}

BOOL CTextItem::Load(CString sec, CString key, CString layoutFName)
{
  BOOL r = CStringItem::Load(sec, key, layoutFName);

  m_FileName = m_Text;
  m_Text = "";
  return r;
}

CGdiObject* CTextItem::Print(CDC* pDC, CGdiObject* pOldFont)
{
  int        y;
  CFont*     pFont;
  CStdioFile f;

  pFont = (CFont*)pOldFont;
  if (m_FontName != NO_FONT)
  {
    if(pFont)
    {
      pFont = pDC->SelectObject(pFont);
      pFont->DeleteObject();
      delete pFont;
    }
    pFont = new CFont();
    pFont->CreateFont(m_FontHeight, m_FontWidth, 0, 0, m_FontWeight,
                      m_bFontItalic, m_bFontUnderline, 0, DEFAULT_CHARSET,
                      OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                      DEFAULT_QUALITY, DEFAULT_PITCH,
                      m_FontName);
    pFont = pDC->SelectObject(pFont);
    pDC->SetTextAlign(m_TextAlign);
  }
  if(f.Open(m_FileName, CFile::modeRead))
  {
    for(y = m_Y;; y += (m_FontHeight * 11 / 10))
    {
      if(f.ReadString(m_Text))
        pDC->TextOut(m_X, y, m_Text);
      else break;
    }
    f.Close();
  }
  return pFont;
}

/*----- implementazione di CGridItem -----*/
CGridItem::CGridItem(void) : CPrintItem()
{
  m_Rows   = 0;
  m_Cols   = 0;
}

/********************************************************************
* Funzione   : Load
* Descrizione: Imposta le variabili membro della griglia in base ai
               dati contenuti nel file ad una certa sezione e ad una
							 certa chiave
* Parametri  : sec = sezione
               key = chiave
							 layoutFName = nome del file               
* Ritorno    :     
* Note       : 
*********************************************************************/
BOOL CGridItem::Load(CString sec, CString key, CString layoutFName)
{
  int     p;
  char    buffer[128];
  CString flags;

  // ricava le coordinate generali di traslazione
  int zerox = GetPrivateProfileInt(SEC_GENERAL, KEY_XZERO, 0, layoutFName);
  int zeroy = GetPrivateProfileInt(SEC_GENERAL, KEY_YZERO, 0, layoutFName);
  
  // copia in buffer il valore presente alla sezione sec e alla chiave key 	
	GetPrivateProfileString(sec, key, "", buffer, sizeof(buffer) - 1, layoutFName);
  
	/*----- sostituisco le virgole con 0 e termino con 00 -----*/
  for (p = 0; buffer[p]; p ++)
	{
    if(buffer[p] == ',') buffer[p] = 0;
  }
	buffer[p + 1] = 0;

  /*----- m_X -----*/
  if (!buffer[p = 0])
	  return FALSE;
  
	// ricava l'intero presente nel buffer a partire dalla posione p
	sscanf(buffer + p, "%d", &m_X);

	// se si tratta di un incremento o di un decremento rispetto alla coordinata X
	// della riga precedente
	if ((buffer[p] == '+') || (buffer[p] == '-'))
		m_X += m_LastX;				
	// altrimenti e' un valore assoluto e va solo incrementato con lo shift X globale 
	else
		m_X += zerox;
	
	// incrementa p per spostarsi verso destra nel buffer per la lettura seguente
	p += (strlen(buffer + p) + 1);
	// memorizza la coordinata assoluta X per l'eventuale uso nella chiamata successiva
	m_LastX = m_X;	

	/*----- m_Y -----*/
  if ( !buffer[p]) 
	  return FALSE;

	// ricava l'intero presente nel buffer a partire dalla posione p
	sscanf(buffer + p, "%d", &m_Y);

	// se si tratta di un incremento o di un decremento rispetto alla coordinata Y 
	// della riga precedente
	if   ((buffer[p] == '+') || (buffer[p] == '-'))
		m_Y += m_LastY;	
	// altrimenti e' un valore assoluto e va solo incrementato con lo shift Y globale 
	else
		m_Y += zeroy;
  
	// incrementa p per spostarsi verso destra nel buffer per la lettura seguente
  p += (strlen(buffer + p) + 1);
	// memorizza la coordinata assoluta Y per l'eventuale uso nella chiamata successiva
	m_LastY = m_Y;
	  
	/*----- m_Width -----*/
  if(!buffer[p]) return FALSE;
  sscanf(buffer + p, "%d", &m_W);
  p += (strlen(buffer + p) + 1);
  /*----- m_Height -----*/
  if(!buffer[p]) return FALSE;
  sscanf(buffer + p, "%d", &m_H);
  p += (strlen(buffer + p) + 1);
  /*----- m_Rows -----*/
  if(!buffer[p]) return FALSE;
  sscanf(buffer + p, "%d", &m_Rows);
  if(m_Rows > 100) m_Rows = 100;
  p += (strlen(buffer + p) + 1);
  /*----- m_Cols -----*/
  if(!buffer[p]) return FALSE;
  sscanf(buffer + p, "%d", &m_Cols);
  if(m_Cols > 100) m_Cols = 100;
  p += (strlen(buffer + p) + 1);
	/*----- colore -----*/
  sscanf(buffer + p, "%x", &m_Color);
  return TRUE;
}

/********************************************************************
* Funzione   : Print
* Descrizione: 
* Parametri  :                
* Ritorno    :     
* Note       : 
*********************************************************************/
CGdiObject* CGridItem::Print(CDC* pDC, CGdiObject* pOldPen)
{
  int i;
  int dx = (m_W + m_Cols * 2);
  int dy = (m_H + m_Rows * 2);
  int y = m_Y;
//  CPen   penBlack(PS_SOLID, 2, RGB(0x00, 0x00, 0x00));
  CPen   penBlack(PS_SOLID, 2, m_Color);

  pOldPen = pDC->SelectObject(&penBlack);
  /*----- stampo il frame esterno -----*/
  pDC->MoveTo(m_X, y);
  pDC->LineTo(m_X + m_W, y);
  pDC->LineTo(m_X + m_W, y + m_H);
  pDC->LineTo(m_X, y + m_H);
  pDC->LineTo(m_X, y);
  /*----- stampo le righe verticali -----*/
  for (i = 1; i < m_Cols; i ++)
  {
    pDC->MoveTo(m_X + i * m_W / m_Cols, y);
    pDC->LineTo(m_X + i * m_W / m_Cols, y + m_H - 1);
  }
  /*----- stampo le righe orizzontali -----*/
  for(i = 1; i < m_Rows; i++)
  {
    pDC->MoveTo(m_X, y + i * m_H / m_Rows);
    pDC->LineTo(m_X + m_W - 1, y + i * m_H / m_Rows);
  }
  pDC->SelectObject(pOldPen);
  penBlack.DeleteObject();
  return pOldPen;
}

/*----- implementazione di CBitmapItem -----*/

CBitmapItem::CBitmapItem(void) : CPrintItem()
{
  m_hHeader = NULL;
  m_hBits = NULL;
  m_pHeader = NULL;
  m_pInfo = NULL;
  m_pBits = NULL;
  m_PathName = "";
  m_WidthBytes = 0;
  m_NColors = 0;
}

CBitmapItem::~CBitmapItem(void)
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

BOOL CBitmapItem::Load(CString sec, CString key, CString layoutFName)
{
  int     p, r, zerox, zeroy;
  char    buffer[128];
  CString flags;
  DWORD   headerSize;
  BITMAPFILEHEADER fileHeader;
  CFile   f;

  zerox = GetPrivateProfileInt(SEC_GENERAL, KEY_XZERO, 0, layoutFName);
  zeroy = GetPrivateProfileInt(SEC_GENERAL, KEY_YZERO, 0, layoutFName);
  GetPrivateProfileString(sec, key, "",
                          buffer, sizeof(buffer) - 1, layoutFName);
  /*----- sostituisco le virgole con 0 e termino con 00 -----*/
  for(p = 0; buffer[p]; p++)
    if(buffer[p] == ',') buffer[p] = 0;
  buffer[p + 1] = 0;
  /*----- m_X -----*/
  if(!buffer[p = 0]) return FALSE;
  sscanf(buffer + p, "%d", &m_X);
  m_X += zerox;
  p += (strlen(buffer + p) + 1);
  /*----- m_Y -----*/
  if(!buffer[p]) return FALSE;
  sscanf(buffer + p, "%d", &m_Y);
  m_Y += zeroy;
  //m_Y = (m_Y * vRes / vSize);
  p += (strlen(buffer + p) + 1);
  /*----- m_Width -----*/
  if(!buffer[p]) return FALSE;
  sscanf(buffer + p, "%d", &m_W);
  p += (strlen(buffer + p) + 1);
  /*----- m_Height -----*/
  if(!buffer[p]) return FALSE;
  sscanf(buffer + p, "%d", &m_H);
  //m_Height = (m_Height * vRes / vSize);
  p += (strlen(buffer + p) + 1);
  /*----- m_Flags -----*/
  m_Flags = buffer + p;
  p += (strlen(buffer + p) + 1);
  /*----- m_PathName -----*/
  if(!buffer[p]) return FALSE;
  m_PathName = buffer + p;
  p += (strlen(buffer + p) + 1);
  if(!f.Open(m_PathName, CFile::modeRead)) return FALSE;
  /*----- carico la bitmap -----*/  
  f.Read((char*)&fileHeader, sizeof(BITMAPFILEHEADER));
  headerSize = fileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);
  if((m_hHeader = GlobalAlloc(GHND, headerSize)) == NULL) return FALSE;
  if((m_pHeader = (LPBITMAPINFO)GlobalLock(m_hHeader)) == NULL)
  {
    GlobalFree(m_hHeader);
    return FALSE;
  }
  m_pInfo = &(m_pHeader->bmiHeader);
  f.Read((char*)m_pHeader, (UINT)headerSize);
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
    GlobalUnlock(m_hHeader);
    GlobalFree(m_hHeader);
    return FALSE;
  }
  if((m_pBits = (BYTE*)GlobalLock(m_hBits)) == NULL)
  {
    GlobalUnlock(m_hHeader);
    GlobalFree(m_hHeader);
    GlobalFree(m_hBits);
    return FALSE;
  }
  for(r = 0; r < m_pInfo->biHeight; r++)
    f.Read((char*)m_pBits + m_WidthBytes * r, (UINT)m_WidthBytes);
  f.Close();
  return TRUE;
}

CGdiObject* CBitmapItem::Print(CDC* pDC, CGdiObject* pBitmap)
{
  HBITMAP  hBM;
  CBitmap* pOldBM;
  CDC      memDC;
  double   w, h, x, y;


  if(!m_W || !m_H)
	  return NULL;
  memDC.CreateCompatibleDC(pDC);
	int n = memDC.GetDeviceCaps(BITSPIXEL);
  hBM = CreateDIBitmap(pDC->m_hDC, m_pInfo, CBM_INIT,
                       m_pBits, m_pHeader, DIB_RGB_COLORS);

  w = m_pInfo->biWidth;
	h = m_pInfo->biHeight;
	if(m_pInfo->biWidth / m_pInfo->biHeight > m_W / m_H)
		h = m_pInfo->biWidth * m_H / m_W;
	else
		w = m_pInfo->biHeight * m_W / m_H;

  memDC.SetMapMode(MM_ISOTROPIC);
	
	memDC.SetWindowOrg(0, 0);
	memDC.SetWindowExt(m_W, m_H);
  
	x = (m_pInfo->biWidth - (int)w) / 2;
	y = (m_pInfo->biHeight - (int)h) / 2;
	memDC.SetViewportOrg((int)x, (int)y);
	memDC.SetViewportExt((int)w, (int)h);

  pOldBM = memDC.SelectObject((CBitmap*)CBitmap::FromHandle(hBM));

  CRect  r(0, 0, (int)m_pInfo->biWidth, (int)m_pInfo->biHeight);
  CPen   whitePen(PS_SOLID, 2, RGB(0xFF, 0xFF, 0xFF));
//  CPen   whitePen(PS_SOLID, 2, RGB(0x00, 0x00, 0x00));
  memDC.DPtoLP(&r);
	r += CPoint(m_X, m_Y);
	pDC->BitBlt(m_X, m_Y, m_W, m_H, &memDC, 0, 0, SRCCOPY);

	CPen*  pOldPen = pDC->SelectObject(&whitePen);
	pDC->MoveTo(r.left, r.top);
	pDC->LineTo(r.right, r.top);
	pDC->LineTo(r.right, r.bottom);
	pDC->LineTo(r.left, r.bottom);
	pDC->LineTo(r.left, r.top);

  pDC->SelectObject(pOldPen);
  memDC.SelectObject(pOldBM);
  DeleteObject((HBITMAP)hBM);

	return NULL;
}

/*----- implementazione di CImageItem -----*/
CImageItem::CImageItem(void) : CPrintItem()
{
	m_dib = NULL;
  m_hHeader = NULL;
  m_hBits = NULL;
  m_pHeader = NULL;
  m_pInfo = NULL;
  m_pBits = NULL;
  m_PathName = "";
  m_WidthBytes = 0;
  m_NColors = 0;
}

CImageItem::~CImageItem(void)
{
	if(m_dib != NULL)
	{
		FreeImage_Unload(m_dib);
	}	
#if 0
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
#endif
}

BOOL CImageItem::Load(CString sec, CString key, CString layoutFName)
{
  int     p, zerox, zeroy;
  char    buffer[128];
  CString flags;

  zerox = GetPrivateProfileInt(SEC_GENERAL, KEY_XZERO, 0, layoutFName);
  zeroy = GetPrivateProfileInt(SEC_GENERAL, KEY_YZERO, 0, layoutFName);
  GetPrivateProfileString(sec, key, "",
                          buffer, sizeof(buffer) - 1, layoutFName);
  /*----- sostituisco le virgole con 0 e termino con 00 -----*/
  for(p = 0; buffer[p]; p++)
    if(buffer[p] == ',') buffer[p] = 0;
  buffer[p + 1] = 0;
  /*----- m_X -----*/
  if(!buffer[p = 0]) return FALSE;
  sscanf(buffer + p, "%d", &m_X);
  m_X += zerox;
  p += (strlen(buffer + p) + 1);
  /*----- m_Y -----*/
  if(!buffer[p]) return FALSE;
  sscanf(buffer + p, "%d", &m_Y);
  m_Y += zeroy;
  //m_Y = (m_Y * vRes / vSize);
  p += (strlen(buffer + p) + 1);
  /*----- m_Width -----*/
  if(!buffer[p]) return FALSE;
  sscanf(buffer + p, "%d", &m_W);
  p += (strlen(buffer + p) + 1);
  /*----- m_Height -----*/
  if(!buffer[p]) return FALSE;
  sscanf(buffer + p, "%d", &m_H);
  //m_Height = (m_Height * vRes / vSize);
  p += (strlen(buffer + p) + 1);
  /*----- m_Flags -----*/
  m_Flags = buffer + p;
  p += (strlen(buffer + p) + 1);
  /*----- m_PathName -----*/
  if(!buffer[p]) return FALSE;
  m_PathName = buffer + p;
  p += (strlen(buffer + p) + 1);
//  if(!f.Open(m_PathName, CFile::modeRead)) return FALSE;
  /*----- carico l'immagine -----*/  
	m_dib = FreeImage_Load(FIF_PNG, m_PathName, PNG_DEFAULT);

#if 0
//  f.Read((char*)&fileHeader, sizeof(BITMAPFILEHEADER));
//  headerSize = fileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);
//  if((m_hHeader = GlobalAlloc(GHND, headerSize)) == NULL) return FALSE;
//  if((m_pHeader = (LPBITMAPINFO)GlobalLock(m_hHeader)) == NULL)
//  {
//    GlobalFree(m_hHeader);
//    return FALSE;
//  }
#endif

//  m_pInfo = &(m_pHeader->bmiHeader);
	m_pInfo = FreeImage_GetInfoHeader(m_dib);
//  f.Read((char*)m_pHeader, (UINT)headerSize);
	m_pHeader = FreeImage_GetInfo(m_dib);
  m_WidthBytes = (m_pInfo->biWidth * m_pInfo->biBitCount + 31) / 32;
  m_WidthBytes *= 4;
  m_pInfo->biSizeImage = m_pInfo->biHeight * m_WidthBytes;
  m_pInfo->biXPelsPerMeter = 2250;
  m_pInfo->biYPelsPerMeter = 2250;
  if(m_pInfo->biBitCount == BMP_24BITS) m_NColors = 0;
  else if(m_pInfo->biClrUsed) m_NColors = m_pInfo->biClrUsed;
  else m_NColors = (0x1 << m_pInfo->biBitCount);

	m_pBits = FreeImage_GetBits(m_dib);
#if 0
  if((m_hBits = GlobalAlloc(GHND, m_pInfo->biSizeImage)) == NULL)
  {
    GlobalUnlock(m_hHeader);
    GlobalFree(m_hHeader);
    return FALSE;
  }
  if((m_pBits = (BYTE*)GlobalLock(m_hBits)) == NULL)
  {
    GlobalUnlock(m_hHeader);
    GlobalFree(m_hHeader);
    GlobalFree(m_hBits);
    return FALSE;
  }
  for(r = 0; r < m_pInfo->biHeight; r++)
    f.Read((char*)m_pBits + m_WidthBytes * r, (UINT)m_WidthBytes);
  f.Close();
#endif

  return TRUE;
}

CGdiObject* CImageItem::Print(CDC* pDC, CGdiObject* pBitmap)
{
  HBITMAP  hBM;
  CBitmap* pOldBM;
  CDC      memDC;
  double   w, h, x, y;


  if(!m_W || !m_H)
	  return NULL;
  memDC.CreateCompatibleDC(pDC);
	int n = memDC.GetDeviceCaps(BITSPIXEL);
  hBM = CreateDIBitmap(pDC->m_hDC, m_pInfo, CBM_INIT,
                       m_pBits, m_pHeader, DIB_RGB_COLORS);

  w = m_pInfo->biWidth;
	h = m_pInfo->biHeight;
	if(m_pInfo->biWidth / m_pInfo->biHeight > m_W / m_H)
		h = m_pInfo->biWidth * m_H / m_W;
	else
		w = m_pInfo->biHeight * m_W / m_H;

  memDC.SetMapMode(MM_ISOTROPIC);
	
	memDC.SetWindowOrg(0, 0);
	memDC.SetWindowExt(m_W, m_H);
  
	x = (m_pInfo->biWidth - (int)w) / 2;
	y = (m_pInfo->biHeight - (int)h) / 2;
	memDC.SetViewportOrg((int)x, (int)y);
	memDC.SetViewportExt((int)w, (int)h);

  pOldBM = memDC.SelectObject((CBitmap*)CBitmap::FromHandle(hBM));

  CRect  r(0, 0, (int)m_pInfo->biWidth, (int)m_pInfo->biHeight);
  CPen   whitePen(PS_SOLID, 2, RGB(0xFF, 0xFF, 0xFF));
//  CPen   whitePen(PS_SOLID, 2, RGB(0x00, 0x00, 0x00));
  memDC.DPtoLP(&r);
	r += CPoint(m_X, m_Y);
	pDC->BitBlt(m_X, m_Y, m_W, m_H, &memDC, 0, 0, SRCCOPY);

	CPen*  pOldPen = pDC->SelectObject(&whitePen);
	pDC->MoveTo(r.left, r.top);
	pDC->LineTo(r.right, r.top);
	pDC->LineTo(r.right, r.bottom);
	pDC->LineTo(r.left, r.bottom);
	pDC->LineTo(r.left, r.top);

  pDC->SelectObject(pOldPen);
  memDC.SelectObject(pOldBM);
  DeleteObject((HBITMAP)hBM);

 return NULL;
}


/*----- implementazione di CBarcodeItem -----*/

CBarcodeItem::CBarcodeItem(void) : CPrintItem()
{
	m_Type = 0;   // default type: BARCODE128
	m_PenWidth = 4;
	m_Code = "";
}

CBarcodeItem::~CBarcodeItem(void)
{
}

BOOL CBarcodeItem::Load(CString sec, CString key, CString layoutFName)
{
  int     p, zerox, zeroy;
  char    buffer[128];
  CString flags;

  zerox = GetPrivateProfileInt(SEC_GENERAL, KEY_XZERO, 0, layoutFName);
  zeroy = GetPrivateProfileInt(SEC_GENERAL, KEY_YZERO, 0, layoutFName);
  GetPrivateProfileString(sec, key, "",
                          buffer, sizeof(buffer) - 1, layoutFName);
  /*----- sostituisco le virgole con 0 e termino con 00 -----*/
  for(p = 0; buffer[p]; p++)
    if(buffer[p] == ',') buffer[p] = 0;
  buffer[p + 1] = 0;
  /*----- m_X -----*/
  if(!buffer[p = 0]) return FALSE;
  sscanf(buffer + p, "%d", &m_X);
  m_X += zerox;
  p += (strlen(buffer + p) + 1);
  /*----- m_Y -----*/
  if(!buffer[p]) return FALSE;
  sscanf(buffer + p, "%d", &m_Y);
  m_Y += zeroy;
  //m_Y = (m_Y * vRes / vSize);
  p += (strlen(buffer + p) + 1);
  /*----- m_Width -----*/
  if(!buffer[p]) return FALSE;
  sscanf(buffer + p, "%d", &m_W);
  p += (strlen(buffer + p) + 1);
  /*----- m_Height -----*/
  if(!buffer[p]) return FALSE;
  sscanf(buffer + p, "%d", &m_H);
  //m_Height = (m_Height * vRes / vSize);
  p += (strlen(buffer + p) + 1);
  /*----- m_Type -----*/ 
	/* barcode type, per ora 0: BARCODE128 */
  if(!buffer[p]) return FALSE;
  sscanf(buffer + p, "%d", &m_Type);
  p += (strlen(buffer + p) + 1);
  /*----- m_PenWidth -----*/ 
  if(!buffer[p]) return FALSE;
  sscanf(buffer + p, "%d", &m_PenWidth);
  p += (strlen(buffer + p) + 1);
  /*----- m_Code -----*/
  m_Code = buffer + p;
  p += (strlen(buffer + p) + 1);
  return TRUE;
}

CGdiObject* CBarcodeItem::Print(CDC* pDC, CGdiObject* pBitmap)
{
	COLORREF clrBar		= RGB(0,0,0);
	COLORREF clrSpace	= RGB(255,255,255);
	CString text2code;

	if(!m_Code.CompareNoCase("@nomefile"))
	{
		text2code = m_Nomefile;
	}
	else
	{
		text2code = m_Code;
	}

	if(m_Type == 0)
	{
		Barcode128 code;
		code.Encode128A(text2code);
		code.DrawBarcode(pDC->m_hDC, m_X, m_Y, m_Y + m_H - 10, m_Y + m_H, clrBar, clrSpace, m_PenWidth);
	}
	else
	{
		Barcode39 code;
		code.Encode39(text2code);
		code.DrawBarcode(pDC->m_hDC, m_X, m_Y, m_Y + m_H - 10, m_Y + m_H, clrBar, clrSpace, m_PenWidth);
	}
	return NULL;
}
