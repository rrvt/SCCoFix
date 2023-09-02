// SCCoFix.h : main header file for the SCCoFix application

#pragma once
#include "CApp.h"
#include "MainFrame.h"


class SCCoFixDoc;
class SCCoFixView;


class SCCoFix : public CApp {

public:

               SCCoFix() noexcept : CApp(this) { }

  virtual BOOL InitInstance();
  virtual int  ExitInstance();

//virtual bool ProcessShellCommand(CCommandLineInfo& cmdInfo) {return true;}

  SCCoFixDoc*  doc()  {return (SCCoFixDoc*)  CApp::getDoc();}
  SCCoFixView* view() {return (SCCoFixView*) CApp::getView();}
  MainFrame*   mainFrm() {return (MainFrame*) m_pMainWnd;}

  DECLARE_MESSAGE_MAP()

  afx_msg void onAppAbout();
  afx_msg void onHelp();
  };


extern SCCoFix theApp;

inline void         invalidate() {theApp.invalidate();}
inline SCCoFixDoc*  doc()        {return theApp.doc();}
inline SCCoFixView* view()       {return theApp.view();}
inline MainFrame*   mainFrm()    {return theApp.mainFrm();}
inline ToolBar&     getToolBar() {return mainFrm()->getToolBar();}

