# TEASER-plusplus_cpp-test
TEASER-plusplus with visualization in cpp

## To run
```bash
sudo apt install cmake libeigen3-dev libboost-all-dev
git clone https://github.com/MIT-SPARK/TEASER-plusplus.git
cd TEASER-plusplus && mkdir build && cd build
cmake .. && make
sudo make install
cd ../..
git clone https://github.com/rFalque/TEASER-plusplus_cpp-test.git
cd TEASER-plusplus_cpp-test && mkdir build && cd build
cmake .. && make
./teaser_plusplus_test_bin
```
