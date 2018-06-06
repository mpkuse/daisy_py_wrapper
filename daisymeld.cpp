#include "daisymeld.h"

DaisyMeld::DaisyMeld(int h, int w, int verbosity=0)
{
  #ifdef _PRINTING_
  std::cout << "constructor called\n";
  #endif
  desc = new daisy();

  m_h = h; //height
  m_w = w; //width
  tmp_img = new float[h*w];
  desc->set_image( tmp_img, h, w );

  desc->verbose( verbosity );
  desc->set_parameters( 8,1,4,4 );


  int ws = desc->compute_workspace_memory();
  workspace = new float[ws]; //I Manage my own memory
  #ifdef _PRINTING_
  cout << "Allocated "<< ws << " floats array for workspace memory\n";
  #endif
  desc->set_workspace_memory( workspace, ws );


  int dc_mem = desc->compute_descriptor_memory();
  descriptors = new float[dc_mem]; //I Manage my own memory
  #ifdef _PRINTING_
  cout << "Allocated "<< dc_mem << " floats array for descriptor memory\n";
  #endif
  desc->set_descriptor_memory( descriptors, dc_mem );

  // desc->initialize_single_descriptor_mode();
  // desc->detach_dense_descriptor_array();

}

//////////////////////////////////////////////////////////////////////////////////////
///////////////////////// Direct Access to Data from Raw Pointer /////////////////////
//////////////////////////////////////////////////////////////////////////////////////
void DaisyMeld::do_daisy_computation( float * seq, int d1, int d2 )
{
  #ifdef _PRINTING_
  cout << "do_computation()\n";
  #endif
  // for( int r=0 ; r<d1 ; r++ )
  // {
  //   for( int c=0 ; c<d2 ; c++ )
  //   {
  //     descriptors[ d1*d2*4 + r*d2 + c ] = seq[ r*d2 + c ]; //set 1st channel out of 20
  //     descriptors[ d1*d2*2 + r*d2 + c ] = 255. - seq[ r*d2 + c ];
  //   }
  // }

  assert( (d1 == m_h)  &&  (d2 == m_w) ); // the input should same as specified

  boost::timer t;
  t.restart();
  // Daisy
  desc->set_image( seq, d1, d2 );
  desc->initialize_single_descriptor_mode();
  desc->compute_descriptors();
  desc->normalize_descriptors();

  #ifdef _PRINTING_
  cout << "c++: Time taken(1) : " << t.elapsed() << endl;
  #endif



}


void DaisyMeld::get_daisy_view( float** vec, int* d1, int* d2, int* d3 )
{
  #ifdef _PRINTING_
  cout << "get_view()\n";
  #endif
  *vec = descriptors;
  *d3 = desc->descriptor_size(); //20;
  *d1 = m_h; //240;
  *d2 = m_w; //320;
}


//////////////////////////////// END //////////////////////////////////////////////


DaisyMeld::~DaisyMeld()
{
  #ifdef _PRINTING_
  cout << "DISTRUCTOR CALLED\nDeallocate workspace, descriptors, tmp_img\n";
  #endif

  delete [] workspace; //you probably don't need to this as this is deallocated by Daisy i think. Let leaks to happen for now
  delete [] descriptors;
  delete [] tmp_img;
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


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// HOOK //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
const std::vector<float> DaisyMeld::hook(const std::vector<float>& image_data, const std::vector<int>& dim)
{
  std::cout << "hook called\n";
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
  #ifdef _PRINTING_
  print_info();
  #endif


  desc->compute_descriptors();
  desc->normalize_descriptors();

  #ifdef _PRINTING_
  float * daisy_dense = desc->get_dense_descriptors(); // this will be NxMx (desc->descriptor_size() )
  // cout << "descriptor size : " << desc->descriptor_size() << endl;
  if( daisy_dense == descriptors )
    cout << "c++: True\n";
  else
    cout << "c++: False\n";
  cout << "c++: Time taken(1) : " << t.elapsed() << endl;
  #endif

  // desc->save_descriptors_ascii( "out.ascii" );



  // Instead of returning vector<float> consider constructing a numpy array to return
  // PyArray_SimpleNewFromData
  std::vector<float> vec; //may be move this to private instead of on stack?

  vec.assign( desc->get_dense_descriptors(), desc->get_dense_descriptors() + desc->compute_descriptor_memory() );
  // vec.push_back( 2.4 );
  // vec.push_back( 1.0 );
  // vec.push_back( 19.90 );
  #ifdef _PRINTING_
  cout << "c++: Time taken(2) : " << t.elapsed() << endl;
  #endif

  return vec;
}




////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
/////////////////////// EXAMPLE USAGE OF SWIG //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
double DaisyMeld::rms( double * seq, int n)
{
  double sum = 0;
  boost::timer t;
  t.restart();

  for( int i=0 ; i<n ; i++ )
    sum += seq[i]*seq[i];

  cout << "c++: Time taken(rms, sec) : " << t.elapsed() << endl;

  return sum;
}

double DaisyMeld::sum2d( double * seq, int d1, int d2 )
{
  double sum=0.0;
  boost::timer t;
  t.restart();
  for( int i=0 ; i<d1 ; i++ )
  {
    for( int j=0 ; j<d2 ; j++ )
    {
      sum += seq[ i*d2 + j ];
    }
  }
  cout << "c++: Time taken(neg, sec) : " << t.elapsed() << endl;

  return sum;
}


void DaisyMeld::im_neg( double *im, int d1, int d2 )
{
  boost::timer t;
  t.restart();
  for( int i=0 ; i<d1 ; i++ )
  {
    for( int j=0 ; j<d2 ; j++ )
    {
      im[ i*d2 + j ] = 255.0 - im[ i*d2 + j ];
    }
  }
  cout << "c++: Time taken(im_neg, sec) : " << t.elapsed() << endl;
  return ;

}



double DaisyMeld::dot( int len, double * vec1, double * vec2 )
{
  cout << "c++: len: " << len << endl;
  cout << "c++: vec1: "<< vec1[0] << "..." << vec1[len-1] << endl;
  cout << "c++: vec2: "<< vec2[0] << "..." << vec2[len-1] << endl;
  return 1.1;
}
