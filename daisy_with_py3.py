from daisymeld import DaisyMeld
import numpy as np
import cv2
import time

im = cv2.imread( 'images/kf_75.png', 0 )
cv2.imshow( 'im', im )
cv2.waitKey(0)


# h, w
dai = DaisyMeld(240, 320, 1)
# startT = time.time()
# for u in range(10):
#     output = dai.hook( np.float64(im.flatten()), im.shape )
#     # dai.hook_noreturn( np.float64(im.flatten()), im.shape )
# print 'Time taken (py in ms) : ', 1000. * (time.time() - startT)
# output = np.array( output ).reshape( im.shape[0], im.shape[1], -1 )
# # the_ascii = np.loadtxt( 'out.ascii' ).reshape(  im.shape[0], im.shape[1], -1 )


startT = time.time()
print dai.rms( np.random.rand( 1000000 ) )
print 'Time taken (py in ms) : ', 1000. * (time.time() - startT)


startT = time.time()
im_rand = np.random.random( (1000,1000 ) )
print dai.sum2d( im_rand )
print 'Time taken (py in ms) : ', 1000. * (time.time() - startT)



# startT = time.time()
# im_rand = np.random.random( (1000,1000 ) )
# im64 = im.copy().astype( 'float64' )
# print im64
# print dai.im_neg( im64 )
# print im64
# print 'Time taken (py in ms) : ', 1000. * (time.time() - startT)
# cv2.imshow( 'im', im64.astype('uint8') )
# cv2.waitKey(0)



# im_rand = np.random.random( (100,200) )
# im_rand2 = np.random.random( (240,320) )
# dai.add_im( im_rand, im_rand2 )


# v_rand = np.random.random( 100 )
# v_rand2 = np.random.random( 100 )
# dai.dot( v_rand, v_rand2 )


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
