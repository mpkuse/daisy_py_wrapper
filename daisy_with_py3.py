#from daisymeld import DaisyMeld
try:
    from DaisyMeld.daisymeld import DaisyMeld
except:
    print 'If you get this error, your DaisyMeld wrapper is not properly setup. You need to set DaisyMeld in LD_LIBRARY_PATH. and PYTHONPATH contains parent of DaisyMeld'
    print 'See also : https://github.com/mpkuse/daisy_py_wrapper'
    print 'Do: export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/Downloads/daisy_py_wrapper/DaisyMeld'
    print 'do: export PYTHONPATH=$PYTHONPATH:$HOME/Downloads/daisy_py_wrapper/'
    quit()
    
import numpy as np
import cv2
import time

im = cv2.imread( 'images/kf_75.png', 0 ) #240x320x1 (needed 1 channel image)
cv2.imshow( 'im', im )
cv2.waitKey(0)


# h, w
dai = DaisyMeld(240, 320, 1) #this 1 is for verbosity, 0 will mute all the messages


im32 = im.copy().astype( 'float32' )
startT = time.time()
dai.do_daisy_computation( im32 )
vi = dai.get_daisy_view()
print 'py time: %4.2f' %( time.time() - startT )



# vi.flags
#  C_CONTIGUOUS : True
#  F_CONTIGUOUS : False
#  OWNDATA : False
#  WRITEABLE : True
#  ALIGNED : True
#  UPDATEIFCOPY : False

cv2.imshow( 'vi0', (255*vi[:,:,0]).astype('uint8') )
cv2.imshow( 'vi1', (255*vi[:,:,1]).astype('uint8') )
cv2.imshow( 'vi2', (255*vi[:,:,2]).astype('uint8') )
cv2.imshow( 'vi3', (255*vi[:,:,3]).astype('uint8') )
cv2.imshow( 'vi4', (255*vi[:,:,4]).astype('uint8') )
cv2.imshow( 'vi5', (255*vi[:,:,5]).astype('uint8') )
cv2.waitKey(0)
