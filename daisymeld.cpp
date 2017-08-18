#include "daisymeld.h"

DaisyMeld::DaisyMeld()
{
  std::cout << "constructor called\n";
  desc = new daisy();
  desc->verbose( 1 );
  desc->set_parameters( 8,1,4,4 );


}

void DaisyMeld::hook(std::vector<float> image_data, std::vector<int> dim)
{
  std::cout << "hook called\n";
  std::cout << "len(image_data) = " << image_data.size() << std::endl;
  std::cout << "len(dim) = " << dim.size() << std::endl;

  boost::timer t;
  t.restart();
  desc->set_image( image_data.data(), dim[0], dim[1] );
  desc->initialize_single_descriptor_mode();
  desc->compute_descriptors();
  desc->normalize_descriptors();
  float * daisy_dense = desc->get_dense_descriptors(); // this will be NxMx (desc->descriptor_size() )
  cout << "descriptor size : " << desc->descriptor_size() << endl;
  cout << "Time taken : " << t.elapsed() << endl;

}
