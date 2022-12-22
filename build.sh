mkdir "build"
cd build || exit

source geant4.sh
cmake ..
make -j

cd ..
