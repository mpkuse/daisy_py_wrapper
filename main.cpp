#include <iostream>
#include <boost/timer.hpp>
#include "daisy/daisy.h"

#include "daisymeld.h"

int main()
{
  /*
  boost::timer t;
  t.restart();

  float * m = new float[100*100];
  for( int i=0 ; i<10 ; i++)
    m[i] = i*i;

    daisy * desc = new daisy();
    desc->set_image( m, 100, 100 ); //h,w
    desc->verbose( 1 );
    desc->set_parameters( 8,1,4,4); //also suggested 8,2,4,4 and 8,1,4,4


    desc->initialize_single_descriptor_mode();
    float * daisy_dense = desc->get_dense_descriptors(); // this will be NxMx (desc->descriptor_size() )
    cout << "descriptor size : " << desc->descriptor_size() << endl;
    cout << "Time taken : " << t.elapsed() << endl;
    */

    DaisyMeld meld = DaisyMeld();
    double f[4] = {1.,1.,2.,2.};
    cout << "RMS : "<< meld.rms(f, 4) << endl;


}
