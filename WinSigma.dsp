# Microsoft Developer Studio Project File - Name="WinSigma" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=WinSigma - Win32 LIDebug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WinSigma.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WinSigma.mak" CFG="WinSigma - Win32 LIDebug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WinSigma - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WinSigma - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "WinSigma - Win32 W2Release" (based on "Win32 (x86) Application")
!MESSAGE "WinSigma - Win32 W2Debug" (based on "Win32 (x86) Application")
!MESSAGE "WinSigma - Win32 LIDebug" (based on "Win32 (x86) Application")
!MESSAGE "WinSigma - Win32 LIRelease" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WinSigma - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\html\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 C:\Lavori\Sigma\WinSigma\html\lib\htmlhelp.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "WinSigma - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "C:\Lavori\Sigma\WinSigma\html\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 C:\Lavori\Sigma\WinSigma\FreeImage.lib C:\Lavori\Sigma\WinSigma\html\lib\htmlhelp.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"C:\Lavori\Sigma\WinSigma\html\lib"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "WinSigma - Win32 W2Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinSigma___Win32_W2Release"
# PROP BASE Intermediate_Dir "WinSigma___Win32_W2Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinSigma___Win32_W2Release"
# PROP Intermediate_Dir "WinSigma___Win32_W2Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\html\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\html\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "WINSIGMA2" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 C:\Quadrante\WinSigma\html\lib\htmlhelp.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 C:\Lavori\Sigma\WinSigma\html\lib\htmlhelp.lib /nologo /subsystem:windows /machine:I386 /out:"WinSigma___Win32_W2Release/WinSigma2.exe"

!ELSEIF  "$(CFG)" == "WinSigma - Win32 W2Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinSigma___Win32_W2Debug"
# PROP BASE Intermediate_Dir "WinSigma___Win32_W2Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinSigma___Win32_W2Debug"
# PROP Intermediate_Dir "WinSigma___Win32_W2Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "C:\Lavori\Sigma\WinSigma\html\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "WINSIGMA2" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 C:\Quadrante\WinSigma\html\lib\htmlhelp.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"C:\Lavori\Sigma\WinSigma\html\lib"
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 C:\Lavori\Sigma\WinSigma\html\lib\htmlhelp.lib /nologo /subsystem:windows /debug /machine:I386 /out:"WinSigma___Win32_W2Debug/WinSigma2.exe" /pdbtype:sept /libpath:"C:\Lavori\Sigma\WinSigma\html\lib"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "WinSigma - Win32 LIDebug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinSigma___Win32_LIDebug"
# PROP BASE Intermediate_Dir "WinSigma___Win32_LIDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinSigma___Win32_LIDebug"
# PROP Intermediate_Dir "WinSigma___Win32_LIDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "C:\Lavori\Sigma\WinSigma\html\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "WINSIGMA2" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "C:\Lavori\Sigma\WinSigma\html\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "WINSIGMALI" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 C:\Lavori\Sigma\WinSigma\html\lib\htmlhelp.lib /nologo /subsystem:windows /debug /machine:I386 /out:"WinSigma___Win32_W2Debug/WinSigma2.exe" /pdbtype:sept /libpath:"C:\Lavori\Sigma\WinSigma\html\lib"
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 C:\Lavori\Sigma\WinSigma\html\lib\htmlhelp.lib /nologo /subsystem:windows /debug /machine:I386 /out:"WinSigma___Win32_LIDebug/WinSigmaLI.exe" /pdbtype:sept /libpath:"C:\Lavori\Sigma\WinSigma\html\lib"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "WinSigma - Win32 LIRelease"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinSigma___Win32_LIRelease"
# PROP BASE Intermediate_Dir "WinSigma___Win32_LIRelease"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinSigma___Win32_LIRelease"
# PROP Intermediate_Dir "WinSigma___Win32_LIRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\html\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "WINSIGMA2" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\html\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "WINSIGMALI" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x410 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 C:\Lavori\Sigma\WinSigma\html\lib\htmlhelp.lib /nologo /subsystem:windows /machine:I386 /out:"WinSigma___Win32_W2Release/WinSigma2.exe"
# ADD LINK32 C:\Lavori\Sigma\WinSigma\html\lib\htmlhelp.lib /nologo /subsystem:windows /machine:I386 /out:"WinSigma___Win32_LIRelease/WinSigma2.exe"

!ENDIF 

# Begin Target

# Name "WinSigma - Win32 Release"
# Name "WinSigma - Win32 Debug"
# Name "WinSigma - Win32 W2Release"
# Name "WinSigma - Win32 W2Debug"
# Name "WinSigma - Win32 LIDebug"
# Name "WinSigma - Win32 LIRelease"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ArchiviaFattureDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ArchivioAziende.cpp
# End Source File
# Begin Source File

SOURCE=.\ArchivioCertificatiView.cpp
# End Source File
# Begin Source File

SOURCE=.\ArchivioFattureView.cpp
# End Source File
# Begin Source File

SOURCE=.\ArchivioVerbaliView.cpp
# End Source File
# Begin Source File

SOURCE=.\AziendeOldSet.cpp
# End Source File
# Begin Source File

SOURCE=.\AziendeSet.cpp
# End Source File
# Begin Source File

SOURCE=.\AziendeTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\AziendeTurboSet.cpp
# End Source File
# Begin Source File

SOURCE=.\AziendeView.cpp
# End Source File
# Begin Source File

SOURCE=.\Bmobject.cpp
# End Source File
# Begin Source File

SOURCE=.\CategorieDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CategorieServiziSet.cpp
# End Source File
# Begin Source File

SOURCE=.\CategorieSet.cpp
# End Source File
# Begin Source File

SOURCE=.\CertificatiSet.cpp
# End Source File
# Begin Source File

SOURCE=.\CertificatiVerbaliSet.cpp
# End Source File
# Begin Source File

SOURCE=.\CondizioniPagamentoSet.cpp
# End Source File
# Begin Source File

SOURCE=.\Configurazione.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigurazioneSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ConnessioneDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DatiAziende.cpp
# End Source File
# Begin Source File

SOURCE=.\DatiFatturaProforma.cpp
# End Source File
# Begin Source File

SOURCE=.\DBRemotoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EmendaDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EmissioneCertificatiDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EsportaFattureDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EsportaXMLDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EsportazioneCSVView.cpp
# End Source File
# Begin Source File

SOURCE=.\EtichetteDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FattureSerEroVerSet.cpp
# End Source File
# Begin Source File

SOURCE=.\FattureSet.cpp
# End Source File
# Begin Source File

SOURCE=.\FattureTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\FattureView.cpp
# End Source File
# Begin Source File

SOURCE=.\FindVerbaliDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GfxGroupEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\GfxOutBarCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GfxPopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\GfxSplitterWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\InsertVerbaliDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\InsertVerbaliInFatturaDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ListiniSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ListiniTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\ListiniView.cpp
# End Source File
# Begin Source File

SOURCE=.\LocalitaSet.cpp
# End Source File
# Begin Source File

SOURCE=.\LogSet.cpp
# End Source File
# Begin Source File

SOURCE=.\CompressioneCubi\maindlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MarchiSet.cpp
# End Source File
# Begin Source File

SOURCE=.\MarchiTurboSet.cpp
# End Source File
# Begin Source File

SOURCE=.\MarchiView.cpp
# End Source File
# Begin Source File

SOURCE=.\MinuteDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ModificaCertificatoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\msmask.cpp
# End Source File
# Begin Source File

SOURCE=.\OperatoriSet.cpp
# End Source File
# Begin Source File

SOURCE=.\OperatoriView.cpp
# End Source File
# Begin Source File

SOURCE=.\PreviewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Printerpreter.cpp
# End Source File
# Begin Source File

SOURCE=.\PrinterThread.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintPreviewCertificati.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintPreviewFatture.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintPreviewVerbali.cpp
# End Source File
# Begin Source File

SOURCE=.\ProviniSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportVerbali.cpp
# End Source File
# Begin Source File

SOURCE=.\RipartizioneImponibileDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SalvaStampaVerbaliDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SerieDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SerieProviniSet.cpp
# End Source File
# Begin Source File

SOURCE=.\SerieSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiziErogatiSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiziFatturaDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiziListinoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ServiziListinoSet.cpp
# End Source File
# Begin Source File

SOURCE=.\StampaCertificatiDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StampaEffetti.cpp
# End Source File
# Begin Source File

SOURCE=.\StampaEffetti.h
# End Source File
# Begin Source File

SOURCE=.\StampaFattureDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StatFatturatoView.cpp
# End Source File
# Begin Source File

SOURCE=.\StatProveView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StrumentiTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\TipiCertificatoSet.cpp
# End Source File
# Begin Source File

SOURCE=.\TipiMaterialeSet.cpp
# End Source File
# Begin Source File

SOURCE=.\TipiMaterialeView.cpp
# End Source File
# Begin Source File

SOURCE=.\TipiPagamentoSet.cpp
# End Source File
# Begin Source File

SOURCE=.\TipiPagamentoView.cpp
# End Source File
# Begin Source File

SOURCE=.\TotFatturatoView.cpp
# End Source File
# Begin Source File

SOURCE=.\TrovaAziendaDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VerbaliServErogatiSet.cpp
# End Source File
# Begin Source File

SOURCE=.\VerbaliSet.cpp
# End Source File
# Begin Source File

SOURCE=.\VerbaliTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\VerbaliView.cpp
# End Source File
# Begin Source File

SOURCE=.\VerbSerProSet.cpp
# End Source File
# Begin Source File

SOURCE=.\WinSigma.cpp
# End Source File
# Begin Source File

SOURCE=.\WinSigma.rc
# End Source File
# Begin Source File

SOURCE=.\WinSigmaDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\XBMPControl.cpp
# End Source File
# Begin Source File

SOURCE=.\XDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\XFormView.cpp
# End Source File
# Begin Source File

SOURCE=.\XTreeCtrl.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AllTables.h
# End Source File
# Begin Source File

SOURCE=.\ArchiviaFattureDlg.h
# End Source File
# Begin Source File

SOURCE=.\ArchivioAziende.h
# End Source File
# Begin Source File

SOURCE=.\ArchivioCertificatiView.h
# End Source File
# Begin Source File

SOURCE=.\ArchivioFattureView.h
# End Source File
# Begin Source File

SOURCE=.\ArchivioVerbaliView.h
# End Source File
# Begin Source File

SOURCE=.\AziendeOldSet.h
# End Source File
# Begin Source File

SOURCE=.\AziendeSet.h
# End Source File
# Begin Source File

SOURCE=.\AziendeTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\AziendeTurboSet.h
# End Source File
# Begin Source File

SOURCE=.\AziendeView.h
# End Source File
# Begin Source File

SOURCE=.\Barcode.h
# End Source File
# Begin Source File

SOURCE=.\Bmobject.h
# End Source File
# Begin Source File

SOURCE=.\CategorieDlg.h
# End Source File
# Begin Source File

SOURCE=.\CategorieServiziSet.h
# End Source File
# Begin Source File

SOURCE=.\CategorieSet.h
# End Source File
# Begin Source File

SOURCE=.\CertificatiSet.h
# End Source File
# Begin Source File

SOURCE=.\CertificatiVerbaliSet.h
# End Source File
# Begin Source File

SOURCE=.\CondizioniPagamentoSet.h
# End Source File
# Begin Source File

SOURCE=.\Configurazione.h
# End Source File
# Begin Source File

SOURCE=.\ConfigurazioneSet.h
# End Source File
# Begin Source File

SOURCE=.\ConnessioneDlg.h
# End Source File
# Begin Source File

SOURCE=.\DatiAziende.h
# End Source File
# Begin Source File

SOURCE=.\DatiFatturaProforma.h
# End Source File
# Begin Source File

SOURCE=.\DBRemotoDlg.h
# End Source File
# Begin Source File

SOURCE=.\EmendaDlg.h
# End Source File
# Begin Source File

SOURCE=.\EmissioneCertificatiDlg.h
# End Source File
# Begin Source File

SOURCE=.\EsportaFattureDlg.h
# End Source File
# Begin Source File

SOURCE=.\EsportaXMLDlg.h
# End Source File
# Begin Source File

SOURCE=.\EsportazioneCSVView.h
# End Source File
# Begin Source File

SOURCE=.\EtichetteDlg.h
# End Source File
# Begin Source File

SOURCE=.\FattureSerEroVerSet.h
# End Source File
# Begin Source File

SOURCE=.\FattureSet.h
# End Source File
# Begin Source File

SOURCE=.\FattureTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\FattureView.h
# End Source File
# Begin Source File

SOURCE=.\FindVerbaliDlg.h
# End Source File
# Begin Source File

SOURCE=.\GfxGroupEdit.h
# End Source File
# Begin Source File

SOURCE=.\GfxOutBarCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GfxPopupMenu.h
# End Source File
# Begin Source File

SOURCE=.\GfxSplitterWnd.h
# End Source File
# Begin Source File

SOURCE=.\InsertVerbaliDlg.h
# End Source File
# Begin Source File

SOURCE=.\InsertVerbaliInFatturaDlg.h
# End Source File
# Begin Source File

SOURCE=.\ListiniSet.h
# End Source File
# Begin Source File

SOURCE=.\ListiniTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\ListiniView.h
# End Source File
# Begin Source File

SOURCE=.\LocalitaSet.h
# End Source File
# Begin Source File

SOURCE=.\LogSet.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MarchiSet.h
# End Source File
# Begin Source File

SOURCE=.\MarchiTurboSet.h
# End Source File
# Begin Source File

SOURCE=.\MarchiView.h
# End Source File
# Begin Source File

SOURCE=.\MinuteDlg.h
# End Source File
# Begin Source File

SOURCE=.\ModificaCertificatoDlg.h
# End Source File
# Begin Source File

SOURCE=.\msmask.h
# End Source File
# Begin Source File

SOURCE=.\OperatoriSet.h
# End Source File
# Begin Source File

SOURCE=.\OperatoriView.h
# End Source File
# Begin Source File

SOURCE=.\PreviewDlg.h
# End Source File
# Begin Source File

SOURCE=.\Printerpreter.h
# End Source File
# Begin Source File

SOURCE=.\PrinterThread.h
# End Source File
# Begin Source File

SOURCE=.\PrintPreviewCertificati.h
# End Source File
# Begin Source File

SOURCE=.\PrintPreviewFatture.h
# End Source File
# Begin Source File

SOURCE=.\PrintPreviewVerbali.h
# End Source File
# Begin Source File

SOURCE=.\ProviniSet.h
# End Source File
# Begin Source File

SOURCE=.\ReportVerbali.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "WinSigma - Win32 Release"

!ELSEIF  "$(CFG)" == "WinSigma - Win32 Debug"

# Begin Custom Build - Making HTML Help Include File...
TargetName=WinSigma
InputPath=.\Resource.h

"html\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	makehm ID_,IDH_,0x10000 IDM_,IDH_,0x10000 resource.h >>"\html\$(TargetName).hm" 
	makehm IDP_,IDH_,0x30000 resource.h >>"html\$(TargetName).hm" 
	makehm IDR_,IDH_,0x20000 resource.h >>"html\$(TargetName).hm" 
	makehm IDD_,IDH_,0x00000 resource.h >>"html\$(TargetName).hm" 
	makehm IDC_,IDH_,0x00000 resource.h >>"html\$(TargetName).hm" 
	makehm IDW_,IDH_,0x50000 resource.h >>"html\$(TargetName).hm" 
	echo. >>"html\$(TargetName).hm" 
	c:\Quadrante\WinSigma\html\MakeIDH\MakeIDH "C:\Quadrante\WinSigma\html\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "WinSigma - Win32 W2Release"

!ELSEIF  "$(CFG)" == "WinSigma - Win32 W2Debug"

# Begin Custom Build - Making HTML Help Include File...
TargetName=WinSigma2
InputPath=.\Resource.h

"html\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	makehm ID_,IDH_,0x10000 IDM_,IDH_,0x10000 resource.h >>"\html\$(TargetName).hm" 
	makehm IDP_,IDH_,0x30000 resource.h >>"html\$(TargetName).hm" 
	makehm IDR_,IDH_,0x20000 resource.h >>"html\$(TargetName).hm" 
	makehm IDD_,IDH_,0x00000 resource.h >>"html\$(TargetName).hm" 
	makehm IDC_,IDH_,0x00000 resource.h >>"html\$(TargetName).hm" 
	makehm IDW_,IDH_,0x50000 resource.h >>"html\$(TargetName).hm" 
	echo. >>"html\$(TargetName).hm" 
	c:\Quadrante\WinSigma\html\MakeIDH\MakeIDH "C:\Quadrante\WinSigma\html\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "WinSigma - Win32 LIDebug"

# Begin Custom Build - Making HTML Help Include File...
TargetName=WinSigmaLI
InputPath=.\Resource.h

"html\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	makehm ID_,IDH_,0x10000 IDM_,IDH_,0x10000 resource.h >>"\html\$(TargetName).hm" 
	makehm IDP_,IDH_,0x30000 resource.h >>"html\$(TargetName).hm" 
	makehm IDR_,IDH_,0x20000 resource.h >>"html\$(TargetName).hm" 
	makehm IDD_,IDH_,0x00000 resource.h >>"html\$(TargetName).hm" 
	makehm IDC_,IDH_,0x00000 resource.h >>"html\$(TargetName).hm" 
	makehm IDW_,IDH_,0x50000 resource.h >>"html\$(TargetName).hm" 
	echo. >>"html\$(TargetName).hm" 
	c:\Quadrante\WinSigma\html\MakeIDH\MakeIDH "C:\Quadrante\WinSigma\html\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "WinSigma - Win32 LIRelease"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RipartizioneImponibileDlg.h
# End Source File
# Begin Source File

SOURCE=.\SalvaStampaVerbaliDlg.h
# End Source File
# Begin Source File

SOURCE=.\SerieDlg.h
# End Source File
# Begin Source File

SOURCE=.\SerieProviniSet.h
# End Source File
# Begin Source File

SOURCE=.\SerieSet.h
# End Source File
# Begin Source File

SOURCE=.\ServiziErogatiSet.h
# End Source File
# Begin Source File

SOURCE=.\ServiziFatturaDlg.h
# End Source File
# Begin Source File

SOURCE=.\ServiziListinoDlg.h
# End Source File
# Begin Source File

SOURCE=.\ServiziListinoSet.h
# End Source File
# Begin Source File

SOURCE=.\StampaCertificatiDlg.h
# End Source File
# Begin Source File

SOURCE=.\StampaFattureDlg.h
# End Source File
# Begin Source File

SOURCE=.\StatFatturatoView.h
# End Source File
# Begin Source File

SOURCE=.\StatProveView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StrumentiTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\TipiCertificatoSet.h
# End Source File
# Begin Source File

SOURCE=.\TipiMaterialeSet.h
# End Source File
# Begin Source File

SOURCE=.\TipiMaterialeView.h
# End Source File
# Begin Source File

SOURCE=.\TipiPagamentoSet.h
# End Source File
# Begin Source File

SOURCE=.\TipiPagamentoView.h
# End Source File
# Begin Source File

SOURCE=.\TotFatturatoView.h
# End Source File
# Begin Source File

SOURCE=.\TrovaAziendaDlg.h
# End Source File
# Begin Source File

SOURCE=.\VerbaliServErogatiSet.h
# End Source File
# Begin Source File

SOURCE=.\VerbaliSet.h
# End Source File
# Begin Source File

SOURCE=.\VerbaliTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\VerbaliView.h
# End Source File
# Begin Source File

SOURCE=.\VerbSerProSet.h
# End Source File
# Begin Source File

SOURCE=.\WinSigma.h
# End Source File
# Begin Source File

SOURCE=.\WinSigmaDoc.h
# End Source File
# Begin Source File

SOURCE=.\XBMPControl.h
# End Source File
# Begin Source File

SOURCE=.\XDialog.h
# End Source File
# Begin Source File

SOURCE=.\XFormView.h
# End Source File
# Begin Source File

SOURCE=.\XTreeCtrl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\archivio.bmp
# End Source File
# Begin Source File

SOURCE=.\res\aziende.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmpSaveVerbali.bmp
# End Source File
# Begin Source File

SOURCE=".\res\clock-2-icon-32x32.ico"
# End Source File
# Begin Source File

SOURCE=".\res\disk-4-icon-32x32.ico"
# End Source File
# Begin Source File

SOURCE=.\res\elett16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\fatture.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\iconMsg.ico
# End Source File
# Begin Source File

SOURCE=.\res\icr_hand.cur
# End Source File
# Begin Source File

SOURCE=.\res\imagelis.bmp
# End Source File
# Begin Source File

SOURCE=.\html\Images\lgq.bmp
# End Source File
# Begin Source File

SOURCE=.\res\listini.bmp
# End Source File
# Begin Source File

SOURCE=.\html\Images\LogoQUADRANTE.bmp
# End Source File
# Begin Source File

SOURCE=".\res\quarkxpress-passport-icon-32x32.ico"
# End Source File
# Begin Source File

SOURCE=.\res\serie.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stampaCertificati.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Strumenti.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_arccert.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_arcfatt.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_arcverb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_aziende.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_fatture.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_listini.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_marchi.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_materiali.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_operatori.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_pagamenti.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_verbali.bmp
# End Source File
# Begin Source File

SOURCE=.\res\verbali.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WinSigma.ico
# End Source File
# Begin Source File

SOURCE=.\res\WinSigma.rc2
# End Source File
# Begin Source File

SOURCE=.\res\WinSigma2.ico
# End Source File
# Begin Source File

SOURCE=.\res\WinSigmaDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\html\WinSigma.hhp
# End Source File
# End Target
# End Project
# Section WinSigma : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont1
# 	2:10:HeaderFile:font1.h
# 	2:8:ImplFile:font1.cpp
# End Section
# Section WinSigma : {4D6CC9A0-DF77-11CF-8E74-00A0C90F26F8}
# 	2:5:Class:CMSMask
# 	2:10:HeaderFile:msmask.h
# 	2:8:ImplFile:msmask.cpp
# End Section
# Section WinSigma : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section WinSigma : {C932BA85-4374-101B-A56C-00AA003668DC}
# 	2:21:DefaultSinkHeaderFile:msmask.h
# 	2:16:DefaultSinkClass:CMSMask
# End Section
