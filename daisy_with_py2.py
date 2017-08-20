from daisymeld import DaisyMeld
import numpy as np
import cv2

im = cv2.imread( 'images/a.png', 0 )
cv2.imshow( 'im', im )
cv2.waitKey(0)

X = np.random.random( (60,40) )


dai = DaisyMeld()
output = dai.hook( np.float64(im.flatten()), im.shape )
output = np.array( output ).reshape( im.shape[0], im.shape[1], -1 )
the_ascii = np.loadtxt( 'out.ascii' ).reshape(  im.shape[0], im.shape[1], -1 )

for i in range( output.shape[2] ):
    cv2.imshow( 'live', output[:,:,i] )
    cv2.imshow( 'frm file', the_ascii[:,:,i] )
    cv2.waitKey(0)
