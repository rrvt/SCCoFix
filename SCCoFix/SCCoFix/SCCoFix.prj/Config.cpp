// Config files are processed here


#include "pch.h"
#include "Config.h"
#include "CopyFile.h"
#include "NotePad.h"
#include "Utilities.h"

#if 0
// Data Root Dir

static TCchar* DataRootDir     = _T("C:\\SCCoPacket\\");

// PacForms Root Dir


static TCchar* OldBinRoot      = _T("C:\\SCCoPacket\\");
#endif

static TCchar* PackItFormsDir = _T("C:\\PackItForms\\");

Config config;


void Config::load(Archive& ar) {
int i;

  notePad << _T("Loading") << nCrlf;

  for (i = 0; ar.read(data[i]); i++) continue;
  }


void Config::fix(TCchar* beforePath, TCchar* newRt) {
CfgIter iter(*this);
String* s;
String  newRoot = newRt;
String  PackItRoot = newRoot + _T("PackItForms\\");
String  PacRoot    = newRoot + _T("PacFORMS\\");

  for (s = iter(); s; s = iter++) {

    replaceTgt(*s, beforePath,              newRoot);
    replaceTgt(*s, _T("C:\\PackItForms\\"), PackItRoot);
    replaceTgt(*s, _T("C:\\PacFORMS\\"),    PacRoot);
    }
  }



void Config::store(Archive& ar) {
int i;
int n = nData();

  notePad << _T("Storing") << nCrlf;

  for (i = 0; i < n; i++) ar.write(data[i]);
  }

#if 0

// ResolveIt - Uses the Shell's IShellLink and IPersistFile interfaces
//             to retrieve the path and description from an existing shortcut.
//
// Returns the result of calling the member functions of the interfaces.
//
// Parameters:
// hwnd         - A handle to the parent window. The Shell uses this window to
//                display a dialog box if it needs to prompt the user for more
//                information while resolving the link.
// lpszLinkFile - Address of a buffer that contains the path of the link,
//                including the file name.
// lpszPath     - Address of a buffer that receives the path of the link
//                target, including the file name.
// lpszDesc     - Address of a buffer that receives the description of the
//                Shell link, stored in the Comment field of the link
//                properties.

#include "windows.h"
#include "shobjidl.h"
#include "shlguid.h"
#include "strsafe.h"

HRESULT resolveIt(HWND hwnd, TCchar* linkFilePath, LPWSTR lpszPath, int iPathBufferSize) {
HRESULT         hres = 0;
IShellLink*     psl  = 0;
IPersistFile*   ppf  = 0;
WCHAR           szGotPath[MAX_PATH];
WCHAR           szDescription[MAX_PATH];
WIN32_FIND_DATA wfd;

  *lpszPath = 0;                                  // Assume failure

  // Get a pointer to the IShellLink interface. It is assumed that CoInitialize has already been called.

  hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl);

  if (SUCCEEDED(hres)) {

    // Get a pointer to the IPersistFile interface.

    hres = psl->QueryInterface(IID_IPersistFile, (void**)&ppf);

    if (SUCCEEDED(hres)) {

      // Add code here to check return value from MultiByteWideChar for success.

      // Load the shortcut.

      hres = ppf->Load(linkFilePath, STGM_READ);

      if (SUCCEEDED(hres)) {

        // Resolve the link.
        hres = psl->Resolve(hwnd, 0);

        if (SUCCEEDED(hres)) {

          // Get the path to the link target.
          hres = psl->GetPath(szGotPath, MAX_PATH, (WIN32_FIND_DATA*) &wfd, SLGP_SHORTPATH);

          if (SUCCEEDED(hres)) {

            // Get the description of the target.
            hres = psl->GetDescription(szDescription, MAX_PATH);

            if (SUCCEEDED(hres)) {
              hres = StringCbCopy(lpszPath, iPathBufferSize, szGotPath);
              if (SUCCEEDED(hres)) {

                String pth = szGotPath;   config.replaceRoot(pth, OldBinRoot);
                String deskTop = getDeskTopPath() + _T("ugly.lnk");

                  hres = psl->SetPath(pth);
                  hres = ppf->Save(linkFilePath, true);

                  copyFile(linkFilePath, deskTop);      // moveFile(linkFilePath, deskTop);

                // Handle success
                }
              else {
                  // Handle the error
                }
              }
            }
          }
        }

      // Release the pointer to the IPersistFile interface.
      ppf->Release();
      }

    // Release the pointer to the IShellLink interface.
    psl->Release();
    }
  return hres;
  }


/* BOOL GetUserNameA(LPSTR   lpBuffer, LPDWORD pcbBuffer); */
#endif
#if 0
void Config::replaceRoot(String& s, TCchar* oldRoot) {
int lng = _tcsclen(oldRoot);
int pos;

  pos = s.find(oldRoot);

  if (pos >= 0) {
    String prefix = s.substr(0, pos);
    String suffix = s.substr(pos+lng);

    s = prefix + newRoot + suffix;
    }
  }
#endif

