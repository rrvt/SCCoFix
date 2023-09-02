// Find all Profile Files


#pragma once
#include "Expandable.h"
#include "IterT.h"


class Profiles;
typedef IterT<Profiles, String> PrfIter;



class Profiles {

Expandable<String, 4> data;

public:

  Profiles() { }
 ~Profiles() { }

  void find(TCchar* rootPath);

private:

  // returns either a pointer to data (or datum) at index i in array or zero

  String* datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}       // or data[i].p

  int     nData()      {return data.end();}                       // returns number of data items in array

  void    removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename PrfIter;
  };

