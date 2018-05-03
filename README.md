# A Python wrapper for DAISY Dense Image Descriptor

## DAISY : A Fast Local Descriptor for Dense Matching

[DAISY descriptor](http://cvlab.epfl.ch/software/daisy) was introduced by CVLAB of EPFL. They also provide their code base in C++. Which is fairly nicely written, is reusable and quite flexible. However no python interface.

OpenCV provides an interface for Daisy. However, it does not provide a way to call it on entire image through python. Documentation is also sparse. See [here](http://docs.opencv.org/trunk/d9/d37/classcv_1_1xfeatures2d_1_1DAISY.html) for example.

Yet another interface to daisy is by scikit. See [here](http://scikit-image.org/docs/dev/auto_examples/features_detection/plot_daisy.html) and [here](http://scikit-image.org/docs/dev/api/skimage.feature.html#skimage.feature.daisy). I believe this one is buggy. I noticed my 240x320 image's whole image descriptors come out to be 224x304x20 in (8,1,4,4) config at step size of 1. 20 is fine but I wonder how 224 and 304 come up. I think there might be an issue with corner case handling or something. Need someone else to verify this!

Feeling frustrated with the python interfaces, I took it upon myself to have a python interface.
Issue with version-1 of this wrapper was that it used to do memory copy and hence used to be much slower. In the current version (ie. version-2), I return the pointer as view with
numpy. Memory is owned by C++ code. Be careful around this.


## Reference Papers
Tola, Engin, Vincent Lepetit, and Pascal Fua. "A fast local descriptor for dense matching." Computer Vision and Pattern Recognition, 2008. CVPR 2008. IEEE Conference on. IEEE, 2008.

Tola, Engin, Vincent Lepetit, and Pascal Fua. "Daisy: An efficient dense descriptor applied to wide-baseline stereo." IEEE transactions on pattern analysis and machine intelligence 32.5 (2010): 815-830.

Winder, Simon, Gang Hua, and Matthew Brown. "Picking the best daisy." Computer Vision and Pattern Recognition, 2009. CVPR 2009. IEEE Conference on. IEEE, 2009.

## Other Papers that Use Daisy-descriptor 
Yang, Hongsheng, Wen-Yan Lin, and Jiangbo Lu. "Daisy filter flow: A generalized discrete approach to dense correspondences." Proceedings of the IEEE Conference on Computer Vision and Pattern Recognition. 2014.



## Credits
I have used the [original code](http://cvlab.epfl.ch/software/daisy) from CVLAB by E. Tola.


## How to Use?
### Step-1 : Compile the Daisy Code and the Wrapper.
```
$ compile.sh
```
This should create *libtoto.so* and *_daisymeld.so*. libtoto needs to be in LD_LIBRARY_PATH. Easy way is to append the current directory to the LD_LIBRARY_PATH.

```
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:.
```

### Step-2 : If everything works well. You are all set.
Run the python script which demos the usage of this
```
python -i daisy_with_py3.py
```

### Step : Clean up
To delete all the dirty files
```
$ sh cleanup.sh
```

## How it all works
The original daisy code is in the folder daisy-1.8.1. One can compile all the cpp files into a shared object and following the usage help in that folder can get a cpp program working quite easy.

I wrote up a c++ class DaisyMeld in daisymeld.h and daisymeld.cpp to call the original daisy. This class need to be linked with the shared object libtoto.so.

This DaisyMeld class has an hook() function which can accept a numpy array. This is still a hacky way but it works! I have written up a [SWIG](http://www.swig.org/) wrapper for the class DaisyMeld. I used swig2.

Go through compile.sh for each step of compiling. It is not that hard to write up a makefile. Any contributions on this are welcome.

Finally, just follow the script daisy_with_py.py to get it hitting with python. This is still a work in progress. I am using this for my current project.  


In version-2,
I use a bit of a trickery to force not copying the data. The way to do it is
using numpy.i with SWIG.
See [here](https://docs.scipy.org/doc/numpy-1.13.0/reference/swig.interface-file.html)
for how to do it.

## Common Pitfalls
Make sure you have swig installed.
``` sudo apt-get install swig-2.0```

## Author
Manohar Kuse <mpkuse (at) connect . ust . hk>
Hope this help!
