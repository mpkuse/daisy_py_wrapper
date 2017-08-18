from daisymeld import DaisyMeld
import numpy as np
dai = DaisyMeld()
X = np.random.random( (60,40) )
dai.hook( X.flatten(), X.shape )

