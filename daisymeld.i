%module daisymeld
%include "std_vector.i"
%include "cpointer.i"

%pointer_class( float, floatp )
%pointer_class( int, intp )

namespace std
{
%template(IntVector) vector<int>;
%template(FloatVector) vector<float>;
}

%{
#define SWIG_FILE_WITH_INIT
#include "daisymeld.h"
%}
%include "typemaps.i"


%include "numpy.i"
%init %{
  import_array();
%}

%apply (double* IN_ARRAY1, int DIM1) {(double* seq, int n) };
%apply (double* IN_ARRAY2, int DIM1, int DIM2) {(double* seq, int d1, int d2) };


%apply (float* IN_ARRAY2, int DIM1, int DIM2) {(float* seq, int d1, int d2) };
%apply( float** ARGOUTVIEW_ARRAY3, int*DIM1, int*DIM2, int* DIM3) { (float** vec, int* d1, int* d2, int* d3) }



%apply( int DIM1, double * IN_ARRAY1) { (int len1, double* vec1),
                                        (int len2, double* vec2)
                                      }

%rename (dot) my_dot;
%exception my_dot {
  $action
  if ( PyErr_Occurred() ) SWIG_fail;
}
%inline %{
  double DaisyMeld::my_dot( int len1, double* vec1, int len2, double * vec2 ) {
    if( len1 != len2 ) {
      PyErr_Format( PyExc_ValueError,
                    "Arrays of lengths (%d,%d) given", len1, len2 );
      return 0.0;
    }
    return dot( len1, vec1, vec2 );
  }
%}
%ignore dot;

%include <std_string.i>
%include <stl.i>
%include "daisymeld.h"
