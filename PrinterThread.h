/********************************************************************
* Classe     : CPrinterThread
* Descrizione: Classe per la gestione del thread di stampa su
*              stampante ad aghi (LPT1)
* Note       : 
*********************************************************************/

#define WM_PRINT_NO_COMM     WM_USER + 10
#define WM_PRINT_OK          WM_USER + 20

class CPrinterThread : public CObject
{
public:
  CPrinterThread(void);
  ~CPrinterThread(void);  
  void BeginPrinterThread(CString strfile, CString strPrinter, HWND hWnd);
  static CString m_strFileName;
  static CString m_strPrinter;
  static HWND m_hWnd;
protected:
  static UINT PrinterProcess(LPVOID pParam);
};





