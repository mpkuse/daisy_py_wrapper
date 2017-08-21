#ifndef __DAISY_MELD__H___
#define __DAISY_MELD__H___


#include <iostream>
#include <vector>
#include <boost/timer.hpp>
#include "daisy/daisy.h"


//TODO : Another way to go about this might be to use inheritance. Basically inherit the class `daisy`. This way you will have access to all the internal functions with python
class DaisyMeld
{
public:
  DaisyMeld();

  const std::vector<float> hook( const std::vector<float>& image_data, const std::vector<int>& dim  );

private:
  daisy * desc;
  void print_info();
};

#endif
