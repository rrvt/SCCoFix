// SCCoFix.cpp : Defines the class behaviors for the application.


#include "pch.h"
#include "SCCoFix.h"
#include "AboutDlg.h"
#include "CommandLineInfo.h"
#include "IniFile.h"
#include "NotePad.h"
#include "Resource.h"
#include "SCCoFixDoc.h"
#include "SCCoFixView.h"
#include "Utilities.h"

SCCoFix theApp;                       // The one and only SCCoFix object
IniFile iniFile;


// SCCoFix

BEGIN_MESSAGE_MAP(SCCoFix, CWinAppEx)
  ON_COMMAND(ID_Help,      &onHelp)
  ON_COMMAND(ID_App_About, &onAppAbout)
END_MESSAGE_MAP()


// SCCoFix initialization

BOOL SCCoFix::InitInstance() {

  CWinAppEx::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

  notePad.clear();

  SetRegistryKey(appID);

  LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

  // Register the application's document templates.  Document templates
  // serve as the connection between documents, frame windows and views

  CSingleDocTemplate* pDocTemplate;

  pDocTemplate = new CSingleDocTemplate(
    IDR_MAINFRAME,
    RUNTIME_CLASS(SCCoFixDoc),
    RUNTIME_CLASS(MainFrame),       // main SDI frame window
    RUNTIME_CLASS(SCCoFixView));

  if (!pDocTemplate) return FALSE;

  AddDocTemplate(pDocTemplate);

//  EnableShellOpen(); RegisterShellFileTypes(TRUE);       // Enable DDE Execute open
  // Parse command line for standard shell commands, DDE, file open

  CommandLineInfo cmdInfo;   ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

  if (!ProcessShellCommand(cmdInfo)) return FALSE;

  setAppName(_T("SCCo Packet Fix")); setTitle(_T("Updated Lines"));

  view()->setFont(_T("Arial"), 12.0);

  doc()->setRootPath(m_pszHelpFilePath);
  logLine(_T("Help File Path"), m_pszHelpFilePath);

  if (!doc()->getPreZipRoot()) {
    logLine(_T("Establish PreZip Root Path: "), doc()->getRootPath());
    doc()->setPreZipRoot();
    }

  else doc()->procConfigFiles();

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }



int SCCoFix::ExitInstance() {

#ifdef DebugMemoryLeaks
  _CrtDumpMemoryLeaks();
#endif

  return CApp::ExitInstance();
  }


void SCCoFix::onHelp() {
String topic = m_pszHelpFilePath; topic += _T(">Introduction");

  ::HtmlHelp(m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 0);
  }


void SCCoFix::onAppAbout() {AboutDlg aboutDlg; aboutDlg.DoModal();}

