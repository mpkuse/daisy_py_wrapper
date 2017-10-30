#ifndef __DAISY_MELD__H___
#define __DAISY_MELD__H___


#include <iostream>
#include <vector>
#include <boost/timer.hpp>
#include "daisy/daisy.h"

// #define _PRINTING_ 

//TODO : Another way to go about this might be to use inheritance. Basically inherit the class `daisy`. This way you will have access to all the internal functions with python
class DaisyMeld
{
public:
  DaisyMeld(int h, int w, int verbosity);
  ~DaisyMeld();

  const std::vector<float> hook( const std::vector<float>& image_data, const std::vector<int>& dim  );




  void do_daisy_computation( float * seq, int d1, int d2 );
  void get_daisy_view( float** vec, int* d1, int* d2, int* d3 );



  // Example Usage of array passing with SWIG.
  // See : https://docs.scipy.org/doc/numpy-1.13.0/reference/swig.interface-file.html

  // Read only array
  double rms( double * seq, int n);
  double sum2d( double * seq, int d1, int d2 );

  // In-place array operation
  void im_neg( double *im, int d1, int d2 );


  // Dot product
  double  dot( int len, double * vec1, double * vec2 );
  double  my_dot( int len1, double* vec1, int len2, double * vec2 );

  // END Example Usage of SWIG Array passing with numpy.i



private:
  daisy * desc;
  void print_info();

  float * workspace;
  float * descriptors;
  float * tmp_img;
  int m_h, m_w;


};

#endif
