// SCCoFixView.cpp : implementation of the SCCoFixView class


#include "pch.h"
#include "SCCoFixView.h"
#include "SCCoFix.h"
#include "SCCoFixDoc.h"
#include "ClipLine.h"
#include "IniFile.h"
#include "OptionsDlg.h"
#include "Resource.h"
#include "Resources.h"
#include "RptOrientDlgTwo.h"


static TCchar* StrOrietnKey = _T("Store");


IMPLEMENT_DYNCREATE(SCCoFixView, CScrView)

BEGIN_MESSAGE_MAP(SCCoFixView, CScrView)
  ON_COMMAND(ID_Options,     &onOptions)
  ON_COMMAND(ID_Orientation, &onRptOrietn)

  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONDBLCLK()

  ON_WM_CONTEXTMENU()                     // Right Mouse Popup Menu
  ON_COMMAND(ID_Pup0, &onCopy)
  ON_COMMAND(ID_Pup1, &onPup1)
  ON_COMMAND(ID_Pup2, &onPup2)

END_MESSAGE_MAP()


SCCoFixView::SCCoFixView() noexcept {
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);

  sub.LoadMenu(ID_PopupMenu);
  menu.CreatePopupMenu();
  menu.AppendMenu(MF_POPUP, (UINT_PTR) sub.GetSafeHmenu(), _T(""));        //

  sub.Detach();
  }


BOOL SCCoFixView::PreCreateWindow(CREATESTRUCT& cs) {return CScrView::PreCreateWindow(cs);}


void SCCoFixView::OnInitialUpdate() {CScrView::OnInitialUpdate();}


void SCCoFixView::onOptions() {
OptionsDlg dlg;

  if (printer.name.isEmpty()) printer.load(0);

  if (dlg.DoModal() == IDOK) pMgr.setFontScale(printer.scale);
  }


void SCCoFixView::onRptOrietn() {
RptOrietnDlg dlg;

  dlg.lbl01 = _T("Store:");
  dlg.ntpd = printer.toStg(prtNote.prtrOrietn);
//  dlg.rpt1 = printer.toStg(prtStore.prtrOrietn);

  if (dlg.DoModal() == IDOK) {
    prtNote.prtrOrietn  = printer.toOrient(dlg.ntpd);
//    prtStore.prtrOrietn = printer.toOrient(dlg.rpt1);
    saveRptOrietn();
    }
  }


void SCCoFixView::initRptOrietn()
        {/*prtStore.prtrOrietn = (PrtrOrient) iniFile.readInt(RptOrietnSect, StrOrietnKey, PortOrient);*/}


void SCCoFixView::saveRptOrietn()
         {saveNoteOrietn();   /*iniFile.write(RptOrietnSect, StrOrietnKey,  (int) prtStore.prtrOrietn);*/}



void SCCoFixView::onPreparePrinting(CPrintInfo* info) {

  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.onPreparePrinting(info);     break;
    }
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void SCCoFixView::onBeginPrinting() {

  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.onBeginPrinting(*this);  break;
    }
  }


void SCCoFixView::onDisplayOutput() {

  switch(doc()->dataSrc()) {
    case NotePadSrc : dspNote.display(*this); break;
    }
  }


void SCCoFixView::displayHeader(DevBase& dev) {
  switch(doc()->dataSrc()) {
    case NotePadSrc   : dspNote.dspHeader(dev);   break;
//    case StoreSrc     : dspStore.dspHeader(dev); break;
    }
  }


void SCCoFixView::displayFooter(DevBase& dev) {
  switch(doc()->dataSrc()) {
    case NotePadSrc   : dspNote.dspFooter(dev);   break;
//    case StoreSrc     : dspStore.dspFooter(dev); break;
    }
  }


void SCCoFixView::printHeader(DevBase& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc: prtNote.prtHeader(dev, pageNo);   break;
//    case StoreSrc  : dspStore.prtHeader(dev, pageNo); break;
    }
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void SCCoFixView::printFooter(DevBase& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.prtFooter(dev, pageNo);  break;
    }
  }



void SCCoFixView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
//    case StoreSrc   : break;
    }
  }


void SCCoFixView::OnSetFocus(CWnd* pOldWnd) {

  CScrView::OnSetFocus(pOldWnd);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
//    case StoreSrc   : break;
    }
  }


void SCCoFixView::OnLButtonDown(UINT nFlags, CPoint point)
                        {clipLine.set(point);   invalidate();   CScrView::OnLButtonDown(nFlags, point);}


void SCCoFixView::OnLButtonDblClk(UINT nFlags, CPoint point)
  {clipLine.set(point);   RedrawWindow();   clipLine.load();   CScrView::OnLButtonDblClk(nFlags, point);}


void SCCoFixView::OnContextMenu(CWnd* /*pWnd*/, CPoint point) {
CRect  rect;
CMenu* popup;
CWnd*  pWndPopupOwner = this;

  if (point.x == -1 && point.y == -1)
            {GetClientRect(rect);  ClientToScreen(rect);  point = rect.TopLeft();  point.Offset(5, 5);}

  popup = menu.GetSubMenu(0);   if (!popup) return;

  while (pWndPopupOwner->GetStyle() & WS_CHILD) pWndPopupOwner = pWndPopupOwner->GetParent();

  popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
  }


void SCCoFixView::onCopy() {clipLine.load();  invalidate();}


void SCCoFixView::onPup1() {  }


void SCCoFixView::onPup2() {  }


// SCCoFixView diagnostics

#ifdef _DEBUG

void SCCoFixView::AssertValid() const {CScrollView::AssertValid();}

void SCCoFixView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}     // non-debug version is inline
                                             // non-debug version is inline
SCCoFixDoc* SCCoFixView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(SCCoFixDoc))); return (SCCoFixDoc*)m_pDocument;}

#endif //_DEBUG


#ifdef Examples
                                            dspStore(dMgr.getNotePad()), prtStore(pMgr.getNotePad()) {
#endif
#ifdef Examples
    case StoreSrc   : prtStore.onPreparePrinting(info);    break;
#endif
#ifdef Examples
    case StoreSrc   : prtStore.onBeginPrinting(*this); break;
#endif
#ifdef Examples
    case StoreSrc   : dspStore.display(*this); break;
#endif
#ifdef Examples
    case StoreSrc   : prtStore.prtFooter(dev, pageNo); break;
#endif

