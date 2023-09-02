// Windows Link File Management



#pragma once


class WinLink {

IShellLink*   psl;
IPersistFile* ppf;

public:

  WinLink() : psl(0), ppf(0) { }
 ~WinLink() {clear();}

  void clear() {if (psl) {psl->Release(); psl = 0;}  if (ppf) {ppf->Release();  ppf = 0;}}

  bool update(TCchar* linkPath, TCchar* oldRoot, TCchar* newRoot);

  bool toDesktop(TCchar* path);
  };

