// Config files are processed here


#pragma once
#include "Expandable.h"
#include "IterT.h"

class Archive;


class Config;
typedef IterT<Config, String> CfgIter;


class Config {

Expandable<String, 1024> data;

//String preZipRoot;

public:

         Config() { }
        ~Config() { }

  void   clear() {data.clear();}

//  void   setPreZipRoot(TCchar* path) {preZipRoot = path;}

  void   load(Archive& ar);
  bool   isLoaded() {return nData() > 0;}

  void   fix(TCchar* beforePath, TCchar* newRt);

  void   store(Archive& ar);

private:

  // returns either a pointer to datum at index i in array or zero

  String* datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}

  int     nData()      {return data.end();}                     // returns number of data items in array

  void    removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename CfgIter;
  };


//HRESULT resolveIt(HWND hwnd, TCchar* linkFilePath, LPWSTR lpszPath, int iPathBufferSize);
//String  getDeskTopPath();


extern Config config;




//  void   replaceRoot(String& s, TCchar* oldRoot);

