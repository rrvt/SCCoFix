

SCCoFix.chm : *.htm SCCoFix.hhp SCCoFix.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" SCCoFix


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  del /F SCCoFix.chm


Release/SCCoFix.chm : SCCoFix.chm
  copy $(MAKEDIR)\SCCoFix.chm  $(MAKEDIR)\..\Release\SCCoFix.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  del SCCoFix.chm
  cd $(MAKEDIR)


Debug/SCCoFix.chm : SCCoFix.chm
  copy $(MAKEDIR)\SCCoFix.chm  $(MAKEDIR)\..\Debug\SCCoFix.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  del SCCoFix.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/SCCoFix.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/SCCoFix.chm


