# crystal-lattice
C++ library that manages the underlying periodic structure of a crystal

## Installation
```
cmake -B build -S . -L -DCMAKE_INSTALL_PREFIX=install
cmake --build build --target install --config Release
```

## Usage
Set the cell parameters (`length of a`, `length of b`, `length of c`, `alpha`, `beta`, `gamma`)
```
Lattice lattice;
int extension = 3;
lattice.setCellParameters({10, 10, 10, 90, 90, 90});
```
The unit cell can be `Niggli reduced` with
```
lattice.updateParametersToReducedMode();
```
otherwise call the following
```
lattice.updateParametersToOrginalMode();
```
Then, extend the lattice points and get the entire point cloud in the following way
```
lattice.spanTheLattice(extension);
std::vector<Eigen::Vector3d> pointcloud = lattice.getPointCloud();
```

## Tests
```
cmake -B build -S . -L -DCMAKE_INSTALL_PREFIX=install
cmake --build build --target install --config Debug
cd build
ctest --build-config Debug --build-target install
```
