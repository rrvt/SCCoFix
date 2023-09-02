// Utilities


#include "pch.h"
#include "NotePad.h"
#include "Utilities.h"


static bool firstLtrUC(String& s);


void replaceTgt(String& s, TCchar* tgt, TCchar* rplc) {
String tgtUC = tgt;   tgtUC.upperCase();
String sUC   = s;     sUC.upperCase();
String r     = rplc;
int    lng   = tgtUC.length();
int    pos;
Tchar  ch;

  pos = sUC.find(tgtUC);

  if (pos < 0) {
    lng--;   tgtUC = tgtUC.substr(0, lng);   pos = sUC.find(tgtUC);   if (pos < 0) return;

    ch = sUC[pos+lng];   if (ch != _T('\n') && ch != _T(' ')) return;

    r = r.substr(0, r.length()-1);
    }

//  logLine(_T("Before"), s);

  String prefix    = s.substr(0,   pos);
  String before    = s.substr(pos, lng);
  String suffix    = s.substr(pos+lng);

  if (!firstLtrUC(before)) r.lowerCase();

  s = prefix + r + suffix;

//  logLine(_T("After"), s);
  }


bool firstLtrUC(String& s) {
int   i;
int   lng;
Tchar ch;

  for (i = 0, lng = s.length(); i < lng; i++) {
    ch = s[i];
    if (_T('A') <= ch && ch <= _T('Z')) return true;
    if (_T('a') <= ch && ch <= _T('z')) return false;
    }

  return false;
  }


static TCchar* DeskTopPfx = _T("C:\\Users\\");
static TCchar* DeskTopSfx = _T("\\Desktop\\");


String getDeskTopPath() {
Tchar buf[UNLEN+1];
DWORD lng = UNLEN+1;
String dtPath = DeskTopPfx;

  GetUserName(buf, &lng);

  dtPath += buf;  dtPath += DeskTopSfx;  return dtPath;
  }


void logLine(TCchar* prefix, TCchar* line) {
String s = line;   s = s.trim();

  notePad << nSetTab(18);   notePad << prefix << _T(":") << nTab << s << nCrlf;
  }

