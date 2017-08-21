#include "daisymeld.h"

DaisyMeld::DaisyMeld()
{
  // std::cout << "constructor called\n";
  desc = new daisy();
  desc->verbose( 0 );
  desc->set_parameters( 8,1,4,4 );


}

void DaisyMeld::print_info()
{
  std::cout << "descriptor_size:" << desc->descriptor_size()<< std::endl;
  std::cout << "compute_workspace_memory:" << desc->compute_workspace_memory()<< std::endl;
  std::cout << "get_hq:" << desc->get_hq()<< std::endl;
  std::cout << "get_thq:" << desc->get_thq()<< std::endl;
  std::cout << "get_rq:" << desc->get_rq()<< std::endl;
  std::cout << "get_rad:" << desc->get_rad()<< std::endl;
}

const std::vector<float> DaisyMeld::hook(const std::vector<float>& image_data, const std::vector<int>& dim)
{
  // std::cout << "hook called\n";
  // std::cout << "len(image_data) = " << image_data.size() << std::endl;
  // std::cout << "len(dim) = " << dim.size() << std::endl;
  // for( int i=0 ; i<dim.size() ; i++ )
  // {
    // std::cout << dim[i] << " x " ;
  // }
  // std::cout << endl;


  boost::timer t;
  t.restart();
  desc->set_image( image_data.data(), dim[0], dim[1] );
  // Print Info
  // print_info();

  desc->initialize_single_descriptor_mode();
  desc->compute_descriptors();
  desc->normalize_descriptors();
  float * daisy_dense = desc->get_dense_descriptors(); // this will be NxMx (desc->descriptor_size() )
  // cout << "descriptor size : " << desc->descriptor_size() << endl;
  cout << "Time taken : " << t.elapsed() << endl;

  // desc->save_descriptors_ascii( "out.ascii" );


  std::vector<float> vec; //may be move this to private instead of on stack?

  vec.assign( desc->get_dense_descriptors(), desc->get_dense_descriptors() + desc->compute_descriptor_memory() );
  // vec.push_back( 2.4 );
  // vec.push_back( 1.0 );
  // vec.push_back( 19.90 );
  return vec;
}
