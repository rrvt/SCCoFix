 // SCCoFixDoc.cpp : implementation of the SCCoFixDoc class


#include "pch.h"
#include "SCCoFixDoc.h"
#include "ClipLine.h"
#include "Config.h"
#include "FileName.h"
#include "GetPathDlg.h"
#include "IniFile.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Printer.h"
#include "Profiles.h"
#include "Resource.h"
#include "SCCoFix.h"
#include "SCCoFixView.h"
#include "Utilities.h"
#include "WinLink.h"

// configuration file

static TCchar* ConfigFiles[] = {_T("bin\\Outpost.conf"),
                                _T("data\\Launch.ini"),
                                _T("PackItForms\\Outpost\\SCCo\\addons\\SCCoPIFO.launch"),
                                _T("PackItForms\\Outpost\\SCCo\\addons\\SCCoPIFO.ini")
                                };


// Link File

static TCchar* LinkFiles[]   = {_T("Outpost SCC.lnk"),
                                _T("Ipagwpe SCC.lnk"),
                                _T("Ipserial SCC.lnk"),
                                _T("Iptelnet SCC.lnk")
                                };


IMPLEMENT_DYNCREATE(SCCoFixDoc, CDoc)

BEGIN_MESSAGE_MAP(SCCoFixDoc, CDoc)

END_MESSAGE_MAP()


// SCCoFixDoc construction/destruction

SCCoFixDoc::SCCoFixDoc() noexcept : dataSource(NotePadSrc) {
  pathDlgDsc(_T("Ugly Example"), _T(""), _T("txt"), _T("*.txt"));
  }

SCCoFixDoc::~SCCoFixDoc() { }


void SCCoFixDoc::setRootPath(TCchar* helpPath) {
String s;

  rootPath = ::getPath(helpPath);
  appName  = ::getMainName(helpPath);

  s = rootPath + appName + _T(".ini");   iniFile.setPath(s);
  }


static TCchar* Section   = _T("Global");
static TCchar* PreZipKey = _T("PreZipPath");

// Determine the root path before zipping the files

void SCCoFixDoc::setPreZipRoot() {iniFile.write(Section, PreZipKey, rootPath);}
bool SCCoFixDoc::getPreZipRoot() {return iniFile.read(Section, PreZipKey, preZipRoot);}


// Look through four files for PreZip Root paths and replace them with the current root.

void SCCoFixDoc::procConfigFiles() {
String path;
int    i;
int    n;

  for (i = 0, n = noElements(ConfigFiles); i < n; i++)
                                     {path = rootPath + ConfigFiles[i];   procConfFile(preZipRoot, path);}
  procProfileFiles();

  for (i = 0, n = noElements(LinkFiles); i < n; i++)
                                                    {path = rootPath + LinkFiles[i];   updateLinks(path);}

  display();
  }


void SCCoFixDoc::procProfileFiles() {
Profiles profiles;
PrfIter  iter(profiles);
String*   path;

  profiles.find(rootPath);

  for (path = iter(); path; path = iter++) {
    procConfFile(preZipRoot, *path);
    }
  }



bool SCCoFixDoc::procConfFile(TCchar* beforePath, TCchar* path) {

  logLine(_T("proccess file"), path);

  config.clear();

  dataSource = ConfigSrc;

  if (OnOpenDocument(path) && config.isLoaded()) {
    backupFile(5);   config.fix(beforePath, rootPath);   OnSaveDocument(path);   display();   return true;
    }

  display();   return false;
  }



// HRESULT resolveIt(HWND hwnd, LPCSTR lpszLinkFile, LPWSTR lpszPath, int iPathBufferSize);

void SCCoFixDoc::updateLinks(TCchar* path) {
WinLink wlnk;

  wlnk.update(path, preZipRoot, rootPath);   wlnk.toDesktop(path);
  }

#if 0
static TCchar* BinFiles[] = {_T("Ics213mm.exe"),
                             _T("Ics309clb.exe"),
                             _T("Ipagwpe.exe"),
                             _T("Ipserial.exe"),
                             _T("Iptelnet.exe"),
                             _T("Ntsmm.exe"),
                             _T("Opdirect.exe"),
                             _T("Opnote.exe"),
                             _T("Opscripts.exe"),
                             _T("Opsessn.exe"),
                             _T("Outpost.exe"),
                             _T("PdfToPrinter.exe"),
                             _T("TimeCheck.exe")
                             };

void SCCoFixDoc::testExeData() {
String  path;
ExeData exeData;
int     i;
int     n;

  for (i = 0, n = noElements(BinFiles); i < n; i++) {

    notePad << BinFiles[i] << nCrlf;

    path = rootPath + _T("bin\\");   path += BinFiles[i];

    exeData.enumerate(path);
    }
  }
#endif


void SCCoFixDoc::onEditCopy() {clipLine.load();}


void SCCoFixDoc::onSpecifyRoot() {

  notePad.clear();

  if (getDirPathDlg(_T("Root Directory"), path)) {logLine(_T("Root Directory"), path);}

  display();
  }


void SCCoFixDoc::display(DataSource ds) {dataSource = ds; invalidate();}


void SCCoFixDoc::OnFileSave() {
  switch (dataSource) {
    case NotePadSrc : if (setSaveAsPath(pathDlgDsc)) OnSaveDocument(path);   break;
    }

  invalidate();
  }


// UglyDoc serialization

void SCCoFixDoc::serialize(Archive& ar) {

  if (ar.isStoring()) {
    switch(dataSource) {
      case NotePadSrc : notePad.archive(ar); return;
      case ConfigSrc  : config.store(ar);
      default         : return;
      }
    }

  switch(dataSource) {
    case ConfigSrc: config.load(ar);
    default       : return;
    }
  }


// SCCoFixDoc diagnostics

#ifdef _DEBUG
void SCCoFixDoc::AssertValid() const {         CDocument::AssertValid();}
void SCCoFixDoc::Dump(CDumpContext& dc) const {CDocument::Dump(dc);}
#endif //_DEBUG





#if 0
void SCCoFixDoc::saveFile(TCchar* title, TCchar* suffix, TCchar* fileType) {
String fileName = path;
int    pos      = fileName.find_last_of(_T('\\'));
String ext      = _T("*."); ext += fileType;
String ttl      = title;    ttl += _T(" Output");

  fileName = fileName.substr(pos+1);   pos = fileName.find_first_of(_T('.'));
  fileName = fileName.substr(0, pos);  fileName += suffix;

  pathDlgDsc(ttl, fileName, fileType, ext);

  if (setSaveAsPath(pathDlgDsc)) OnSaveDocument(path);
  }
#endif
// data dir configuration file

//static TCchar* DataConfigFile = _T("data\\Launch.ini");

// PackItForms dir configuration file

//static TCchar* PacConfigFile  = _T("PackItForms\\Outpost\\SCCo\\addons\\SCCoPIFO.launch");
//static TCchar* PIFOConfigFile = _T("PackItForms\\Outpost\\SCCo\\addons\\SCCoPIFO.ini");
#if 0
void SCCoFixDoc::updateOneLink() {
int     i;
int     n = noElements(LinkFiles);
String  path;
WinLink wLnk;

  for (i = 0, n = noElements(LinkFiles); i < n; i++)
                          {path = rootPath + LinkFiles[i];   wLnk.testUpdate(path, preZipRoot, rootPath);}
  }
#endif

