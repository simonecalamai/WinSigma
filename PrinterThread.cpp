/********************************************************************
* Classe     : CPrinterThread
* Descrizione: Classe per la gestione del thread di stampa su
*              stampante ad aghi (LPT1)
* Note       : 
*********************************************************************/
#include "stdafx.h"
#include "PrinterThread.h"


#define PRINT_OK         0
#define NO_FILE_TOPRINT  1
#define NO_COMM          2

CString CPrinterThread::m_strFileName;
CString CPrinterThread::m_strPrinter;
HWND    CPrinterThread::m_hWnd;

CPrinterThread::CPrinterThread() : CObject()
{
}


CPrinterThread::~CPrinterThread()
{
}

void CPrinterThread::BeginPrinterThread(CString strFile, CString strPrinter, HWND hWnd)
{
  m_strFileName = strFile;
  m_strPrinter = strPrinter;
  m_hWnd = hWnd;
  AfxBeginThread(PrinterProcess, NULL);
}


UINT CPrinterThread::PrinterProcess(LPVOID pParam)
{
  CStdioFile fileToPrint;
  FILE* pPrinterFile;
  CString str;
  int nParziale, nTotale, n;

  str = m_strFileName;
  str.TrimRight(".txt");
  str.Replace("_", "/");
  if(m_strFileName.IsEmpty() || m_strPrinter.IsEmpty())
  {
    CString strMsg;
    strMsg.Format("Impossibile stampare il verbale %s", str);
    MessageBox(AfxGetMainWnd()->m_hWnd, strMsg, "WinSigma", MB_OK);
    return NO_FILE_TOPRINT;
  }
  n = str.Find('/');
  nTotale = atoi(str.Mid(n + 1));
  str.Left(str.GetLength() - n);
  nParziale = atoi(str);
  // Apro la stampante 
  if((pPrinterFile = fopen(m_strPrinter, "w")) == NULL)
  {
    PostMessage(m_hWnd, WM_PRINT_NO_COMM, nParziale, nTotale);
    return NO_COMM;
  }
  
  if(!fileToPrint.Open(m_strFileName, CFile::modeRead))
  {
    fclose(pPrinterFile);
    return NO_FILE_TOPRINT;
  }
  while(fileToPrint.ReadString(str))
  {
    fprintf(pPrinterFile, str);
    fprintf(pPrinterFile, "\r\n");
  }
  fileToPrint.Close();
  CFile::Remove(m_strFileName);
  if(fclose(pPrinterFile))
    return NO_COMM;
  PostMessage(m_hWnd, WM_PRINT_OK, nParziale, nTotale);
  return PRINT_OK;
}