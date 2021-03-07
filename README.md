# cov(opencl on vulkan)

opencl on vulkan<br>
**just for fun!**

# how to build

## linux

clone this project and build it:

```shell
cd ${PROJECT_ROOT}
mkdir build && cd build
cmake ..
make -j
```

Then you will get:<br>
libvulkan.so: a stub vulkan dynamic library, which used to link OpenCL, and would be replaced by your device's vulkan driver.<br>
libOpenCL.so: main library supports OpenCL API and lies on vulkan.<br>
budCovTest: an executeble test program.<br>

Here are test suites:

```shell
./budCovTest platform
```

## windows

clone this project and build it:

```shell
cd ${PROJECT_ROOT}
mkdir build && cd build
cmake ..
cmake --build .
```

# supported API list

clGetPlatformIDs<br>
clGetPlatformInfo<br>
clGetDeviceIDs<br>
clCreateContext<br>
clRetainContext<br>
clReleaseContext<br>
clCreateCommandQueue<br>
clRetainCommandQueue<br>
clReleaseCommandQueue<br>
