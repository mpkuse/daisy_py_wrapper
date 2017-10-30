# Create all .o files
DAISY_BASE='./daisy-1.8.1/'
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

echo -e "${RED}Compiling ${NC}"
g++ -O3 -fPIC -c -I ${DAISY_BASE}include ${DAISY_BASE}src/corecv.cpp
g++ -O3 -fPIC -c -I ${DAISY_BASE}include ${DAISY_BASE}src/daisy.cpp
g++ -O3 -fPIC -c -I ${DAISY_BASE}include ${DAISY_BASE}src/general.cpp
g++ -O3 -fPIC -c -I ${DAISY_BASE}include ${DAISY_BASE}src/image_io_bmp.cpp
g++ -O3 -fPIC -c -I ${DAISY_BASE}include ${DAISY_BASE}src/image_io_jpeg.cpp
g++ -O3 -fPIC -c -I ${DAISY_BASE}include ${DAISY_BASE}src/image_io_png.cpp
g++ -O3 -fPIC -c -I ${DAISY_BASE}include ${DAISY_BASE}src/image_io_pnm.cpp
g++ -O3 -fPIC -c -I ${DAISY_BASE}include ${DAISY_BASE}src/image_manipulation.cpp
g++ -O3 -fPIC -c -I ${DAISY_BASE}include ${DAISY_BASE}src/interaction.cpp
g++ -O3 -fPIC -c -I ${DAISY_BASE}include ${DAISY_BASE}src/main.cpp
g++ -O3 -fPIC -c -I ${DAISY_BASE}include ${DAISY_BASE}src/progress_bar.cpp

# mkdir lib
echo "${RED}Linking to create libtoto.so ${NC}"
g++ -fPIC -shared -I include/ *.o  -o ./libtoto.so

echo "${RED}Remove object files (.o)${NC}"
rm *.o #remove the .o files

echo "${RED}Copy include${NC}"
cp -r ${DAISY_BASE}include ./

echo "compile your program as : g++ main.cpp -I include/ -L . -ltoto"
echo "compile your program as : g++ main.cpp daisymeld.cpp -I include/ -L . -ltoto"


echo "---"
echo "${RED}Compile Swig Interface class${NC}"
echo "---"

echo "${RED}generate swig wrapper${NC}"
swig -c++ -python daisymeld.i

echo "${RED}compile DaisyMeld${NC}"
g++ -fPIC -c daisymeld.cpp  -I include

echo "${RED}compile wrapper${NC}"
g++ -fPIC -c daisymeld_wrap.cxx -I include -I /usr/include/python2.7

echo "${RED}Link Daisy, DaisyMeld, wrapper to create _daisymeld.so${NC}"
g++ -shared daisymeld.o daisymeld_wrap.o -L . -ltoto -o _daisymeld.so


echo "${GREEN}Wrapper is ready...!${NC}"

DIST_DIR="DaisyMeld"
mkdir $DIST_DIR
cp _daisymeld.so daisymeld.py libtoto.so $DIST_DIR
touch ${DIST_DIR}/__init__.py
echo "see https://github.com/mpkuse/daisy_py_wrapper" >> ${DIST_DIR}/README.md

echo "Copy files for distrubution in directory : daisy_py_distribute"

echo "${GREEN}Now you can use daisymeld with python (see daisy_with_py.py). ${NC}"
echo "Sample Python Program : "
echo "from daisymeld import DaisyMeld"
echo "import numpy as np"
echo "dai = DaisyMeld(0,0,0) #doesnot matter if using hook() based call"
echo "X = np.random.random( (60,40) )"
echo "dai.hook( X.flatten(), X.shape )"


echo ""
echo "Sample Usage with Direct Memory View (no copy of data, hence lot faster)"
echo "from daisymeld import DaisyMeld"
echo "import numpy as np"
echo "dai = DaisyMeld(240,320,0) #doesnot matter if using hook() based call"
echo "X = np.random.random( (240,320), dtype='float32' )"
echo "dai.do_daisy_computation( X )"
echo "vii = dai.get_daisy_view()"
