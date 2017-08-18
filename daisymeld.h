#ifndef __DAISY_MELD__H___
#define __DAISY_MELD__H___


#include <iostream>
#include <vector>
#include <boost/timer.hpp>
#include "daisy/daisy.h"

class DaisyMeld
{
public:
  DaisyMeld();

  void hook( std::vector<float> image_data, std::vector<int> dim  );

private:
  daisy * desc;
};

#endif
