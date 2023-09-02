// SCCoFixDoc.h : interface of the SCCoFixDoc class


#pragma once
#include "CDoc.h"
#include "MainFrame.h"


enum DataSource {NotePadSrc, ConfigSrc};


class SCCoFixDoc : public CDoc {

String      preZipRoot;

String      rootPath;
String      appName;
PathDlgDsc  pathDlgDsc;
DataSource  dataSource;

protected:                                                          // create from serialization only

  DECLARE_DYNCREATE(SCCoFixDoc)

               SCCoFixDoc() noexcept;
public:

  virtual     ~SCCoFixDoc();

  void         setRootPath(TCchar* helpPath);
  void         setPreZipPath(TCchar* path) {preZipRoot = path;}
  String&      getRootPath() {return rootPath;}

  void         setPreZipRoot();                       // Determine the root path before zipping the files
  bool         getPreZipRoot();                       // Load the pre zip path from the ini file
  void         procConfigFiles();                     // Replace the path found by setPreZipRoot with
                                                      // current root path in all the configuration files
  void         procProfileFiles();

  void         updateLinks(TCchar* path);

//  void         testExeData();

  DataSource   dataSrc() {return dataSource;}
  void         display(DataSource ds = NotePadSrc);

  virtual void serialize(Archive& ar);

public:                                                              // Implementation
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

private:

  bool procConfFile(TCchar* beforePath, TCchar* path);

protected:

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void onSpecifyRoot();
  afx_msg void OnFileSave();
  afx_msg void onEditCopy();
  };



//  void         updateOneLink();

