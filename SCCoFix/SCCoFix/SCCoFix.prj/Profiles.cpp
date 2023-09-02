// Find all Profile Files


#include "pch.h"
#include "Profiles.h"
#include "FileSrch.h"


void Profiles::find(TCchar* path) {
FileSrch srch;
String   sub;
String   name;

  srch.findFiles(path, _T("*.profile"));
  while (srch.getName(name)) {data += name;}

  srch.findAllSubDirs(path)  ;
  while (srch.getName(sub)) {find(sub);}
  }

