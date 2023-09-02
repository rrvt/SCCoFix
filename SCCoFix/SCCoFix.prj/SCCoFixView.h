// SCCoFixView.h : interface of the SCCoFixView class


#pragma once
#include "CScrView.h"
#include "NotePadRpt.h"


class SCCoFixDoc;


class SCCoFixView : public CScrView {


CMenu      menu;
CMenu      sub;

protected: // create from serialization only

  SCCoFixView() noexcept;

  DECLARE_DYNCREATE(SCCoFixView)

public:

  virtual        ~SCCoFixView() { }

  void            initRptOrietn();
  void            saveRptOrietn();

  virtual BOOL    PreCreateWindow(CREATESTRUCT& cs);
  virtual void    OnInitialUpdate();

  virtual void    displayHeader(DevBase& dev);
  virtual void    displayFooter(DevBase& dev);

  virtual void    onPreparePrinting(CPrintInfo* info);
  virtual void    onBeginPrinting();
  virtual void    onDisplayOutput();

  virtual void    printHeader(DevBase& dev, int pageNo);
  virtual void    printFooter(DevBase& dev, int pageNo);
  virtual void    OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  SCCoFixDoc* GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:

  DECLARE_MESSAGE_MAP()

  afx_msg void onOptions();
  afx_msg void onRptOrietn();

  afx_msg void OnSetFocus(CWnd* pOldWnd);

  afx_msg void OnLButtonDown(  UINT nFlags, CPoint point);
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

  afx_msg void OnContextMenu(  CWnd* ,      CPoint point);
  afx_msg void onCopy();
  afx_msg void onPup1();
  afx_msg void onPup2();
  };



#ifndef _DEBUG  // debug version in SCCoFixView.cpp
inline SCCoFixDoc* SCCoFixView::GetDocument() const {return reinterpret_cast<SCCoFixDoc*>(m_pDocument);}
#endif



#ifdef Examples
#include "StoreRpt.h"
#endif
#ifdef Examples
StoreRpt   dspStore;
StoreRpt   prtStore;
#endif

//  StoreRpt&       storeRpt()  {return dspStore;}

