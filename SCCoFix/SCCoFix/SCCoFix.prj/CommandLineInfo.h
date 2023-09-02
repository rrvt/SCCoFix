// Command Line Info


#pragma once


class CommandLineInfo : public CCommandLineInfo {
public:

int    n;
String arg;
bool   flag;

  CommandLineInfo() : CCommandLineInfo(), n(0) { }
 ~CommandLineInfo() { }

  virtual void ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast);
  };

