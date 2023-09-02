


#include "pch.h"
#include "WinLink.h"
#include "CopyFile.h"
#include "FileName.h"
#include "NotePad.h"
#include "Utilities.h"


#if 0
HRESULT GetIconLocation(
  LPSTR pszIconPath,
  int   cch,
  int   *piIcon
);
HRESULT SetIconLocation(
  LPCSTR pszIconPath,
  int    iIcon
);
#endif


bool WinLink::update(TCchar* linkPath, TCchar* oldRoot, TCchar* newRoot) {
Tchar  curPath[MAX_PATH];
String exePath;

  // Get a pointer to the IShellLink interface. It is assumed that CoInitialize has already been called.

  if (CoCreateInstance(CLSID_ShellLink, 0, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**) &psl) != S_OK)
                                                                                             return false;
  if (psl->QueryInterface(IID_IPersistFile, (void**) &ppf) != S_OK) {clear(); return false;}

  if (ppf->Load(linkPath, STGM_READ) != S_OK) {clear(); return false;}

    if (psl->GetPath(curPath, MAX_PATH, 0, 0) != S_OK) {clear(); return false;}

    exePath = curPath;   replaceTgt(exePath, oldRoot, newRoot);

    if (psl->SetPath(exePath) != S_OK) {clear(); return false;}

    psl->SetIconLocation(exePath, 0);

  ppf->Save(linkPath, true);  clear(); return true;
  }


bool WinLink::toDesktop(TCchar* path) {
String tgt = getDeskTopPath() + getMainName(path) + _T(".lnk");


  return copyFile(path, tgt);                    // moveFile(linkFilePath, deskTop);
  }




#if 0
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
#endif

