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

```C++
/* OpenCL 1.0 */
clGetPlatformIDs,
clGetPlatformInfo,
clGetDeviceIDs,
nullptr,//   cl_api_clGetDeviceInfo clGetDeviceInfo;
clCreateContext,
nullptr,//   cl_api_clCreateContextFromType clCreateContextFromType;
clRetainContext,
clReleaseContext,
nullptr,//   cl_api_clGetContextInfo clGetContextInfo;
clCreateCommandQueue,
clRetainCommandQueue,
clReleaseCommandQueue,
nullptr,//   cl_api_clGetCommandQueueInfo clGetCommandQueueInfo;
nullptr,//   cl_api_clSetCommandQueueProperty clSetCommandQueueProperty;
nullptr,//   cl_api_clCreateBuffer clCreateBuffer;
nullptr,//   cl_api_clCreateImage2D clCreateImage2D;
nullptr,//   cl_api_clCreateImage3D clCreateImage3D;
nullptr,//   cl_api_clRetainMemObject clRetainMemObject;
nullptr,//   cl_api_clReleaseMemObject clReleaseMemObject;
nullptr,//   cl_api_clGetSupportedImageFormats clGetSupportedImageFormats;
nullptr,//   cl_api_clGetMemObjectInfo clGetMemObjectInfo;
nullptr,//   cl_api_clGetImageInfo clGetImageInfo;
nullptr,//   cl_api_clCreateSampler clCreateSampler;
nullptr,//   cl_api_clRetainSampler clRetainSampler;
nullptr,//   cl_api_clReleaseSampler clReleaseSampler;
nullptr,//   cl_api_clGetSamplerInfo clGetSamplerInfo;
clCreateProgramWithSource,
nullptr,//   cl_api_clCreateProgramWithBinary clCreateProgramWithBinary;
nullptr,//   cl_api_clRetainProgram clRetainProgram;
nullptr,//   cl_api_clReleaseProgram clReleaseProgram;
nullptr,//   cl_api_clBuildProgram clBuildProgram;
nullptr,//   cl_api_clUnloadCompiler clUnloadCompiler;
nullptr,//   cl_api_clGetProgramInfo clGetProgramInfo;
nullptr,//   cl_api_clGetProgramBuildInfo clGetProgramBuildInfo;
nullptr,//   cl_api_clCreateKernel clCreateKernel;
nullptr,//   cl_api_clCreateKernelsInProgram clCreateKernelsInProgram;
nullptr,//   cl_api_clRetainKernel clRetainKernel;
nullptr,//   cl_api_clReleaseKernel clReleaseKernel;
nullptr,//   cl_api_clSetKernelArg clSetKernelArg;
nullptr,//   cl_api_clGetKernelInfo clGetKernelInfo;
nullptr,//   cl_api_clGetKernelWorkGroupInfo clGetKernelWorkGroupInfo;
nullptr,//   cl_api_clWaitForEvents clWaitForEvents;
nullptr,//   cl_api_clGetEventInfo clGetEventInfo;
nullptr,//   cl_api_clRetainEvent clRetainEvent;
nullptr,//   cl_api_clReleaseEvent clReleaseEvent;
nullptr,//   cl_api_clGetEventProfilingInfo clGetEventProfilingInfo;
nullptr,//   cl_api_clFlush clFlush;
nullptr,//   cl_api_clFinish clFinish;
nullptr,//   cl_api_clEnqueueReadBuffer clEnqueueReadBuffer;
nullptr,//   cl_api_clEnqueueWriteBuffer clEnqueueWriteBuffer;
nullptr,//   cl_api_clEnqueueCopyBuffer clEnqueueCopyBuffer;
nullptr,//   cl_api_clEnqueueReadImage clEnqueueReadImage;
nullptr,//   cl_api_clEnqueueWriteImage clEnqueueWriteImage;
nullptr,//   cl_api_clEnqueueCopyImage clEnqueueCopyImage;
nullptr,//   cl_api_clEnqueueCopyImageToBuffer clEnqueueCopyImageToBuffer;
nullptr,//   cl_api_clEnqueueCopyBufferToImage clEnqueueCopyBufferToImage;
nullptr,//   cl_api_clEnqueueMapBuffer clEnqueueMapBuffer;
nullptr,//   cl_api_clEnqueueMapImage clEnqueueMapImage;
nullptr,//   cl_api_clEnqueueUnmapMemObject clEnqueueUnmapMemObject;
nullptr,//   cl_api_clEnqueueNDRangeKernel clEnqueueNDRangeKernel;
nullptr,//   cl_api_clEnqueueTask clEnqueueTask;
nullptr,//   cl_api_clEnqueueNativeKernel clEnqueueNativeKernel;
nullptr,//   cl_api_clEnqueueMarker clEnqueueMarker;
nullptr,//   cl_api_clEnqueueWaitForEvents clEnqueueWaitForEvents;
nullptr,//   cl_api_clEnqueueBarrier clEnqueueBarrier;
nullptr,//   cl_api_clGetExtensionFunctionAddress clGetExtensionFunctionAddress;
nullptr,//   cl_api_clCreateFromGLBuffer clCreateFromGLBuffer;
nullptr,//   cl_api_clCreateFromGLTexture2D clCreateFromGLTexture2D;
nullptr,//   cl_api_clCreateFromGLTexture3D clCreateFromGLTexture3D;
nullptr,//   cl_api_clCreateFromGLRenderbuffer clCreateFromGLRenderbuffer;
nullptr,//   cl_api_clGetGLObjectInfo clGetGLObjectInfo;
nullptr,//   cl_api_clGetGLTextureInfo clGetGLTextureInfo;
nullptr,//   cl_api_clEnqueueAcquireGLObjects clEnqueueAcquireGLObjects;
nullptr,//   cl_api_clEnqueueReleaseGLObjects clEnqueueReleaseGLObjects;
nullptr,//   cl_api_clGetGLContextInfoKHR clGetGLContextInfoKHR;

//   /* cl_khr_d3d10_sharing */
nullptr,//   cl_api_clGetDeviceIDsFromD3D10KHR clGetDeviceIDsFromD3D10KHR;
nullptr,//   cl_api_clCreateFromD3D10BufferKHR clCreateFromD3D10BufferKHR;
nullptr,//   cl_api_clCreateFromD3D10Texture2DKHR clCreateFromD3D10Texture2DKHR;
nullptr,//   cl_api_clCreateFromD3D10Texture3DKHR clCreateFromD3D10Texture3DKHR;
nullptr,//   cl_api_clEnqueueAcquireD3D10ObjectsKHR clEnqueueAcquireD3D10ObjectsKHR;
nullptr,//   cl_api_clEnqueueReleaseD3D10ObjectsKHR clEnqueueReleaseD3D10ObjectsKHR;

//   /* OpenCL 1.1 */
nullptr,//   cl_api_clSetEventCallback clSetEventCallback;
nullptr,//   cl_api_clCreateSubBuffer clCreateSubBuffer;
nullptr,//   cl_api_clSetMemObjectDestructorCallback clSetMemObjectDestructorCallback;
nullptr,//   cl_api_clCreateUserEvent clCreateUserEvent;
nullptr,//   cl_api_clSetUserEventStatus clSetUserEventStatus;
nullptr,//   cl_api_clEnqueueReadBufferRect clEnqueueReadBufferRect;
nullptr,//   cl_api_clEnqueueWriteBufferRect clEnqueueWriteBufferRect;
nullptr,//   cl_api_clEnqueueCopyBufferRect clEnqueueCopyBufferRect;

//   /* cl_ext_device_fission */
nullptr,//   cl_api_clCreateSubDevicesEXT clCreateSubDevicesEXT;
nullptr,//   cl_api_clRetainDeviceEXT clRetainDeviceEXT;
nullptr,//   cl_api_clReleaseDeviceEXT clReleaseDeviceEXT;

//   /* cl_khr_gl_event */
nullptr,//   cl_api_clCreateEventFromGLsyncKHR clCreateEventFromGLsyncKHR;

//   /* OpenCL 1.2 */
nullptr,//   cl_api_clCreateSubDevices clCreateSubDevices;
nullptr,//   cl_api_clRetainDevice clRetainDevice;
nullptr,//   cl_api_clReleaseDevice clReleaseDevice;
nullptr,//   cl_api_clCreateImage clCreateImage;
nullptr,//   cl_api_clCreateProgramWithBuiltInKernels clCreateProgramWithBuiltInKernels;
nullptr,//   cl_api_clCompileProgram clCompileProgram;
nullptr,//   cl_api_clLinkProgram clLinkProgram;
nullptr,//   cl_api_clUnloadPlatformCompiler clUnloadPlatformCompiler;
nullptr,//   cl_api_clGetKernelArgInfo clGetKernelArgInfo;
nullptr,//   cl_api_clEnqueueFillBuffer clEnqueueFillBuffer;
nullptr,//   cl_api_clEnqueueFillImage clEnqueueFillImage;
nullptr,//   cl_api_clEnqueueMigrateMemObjects clEnqueueMigrateMemObjects;
nullptr,//   cl_api_clEnqueueMarkerWithWaitList clEnqueueMarkerWithWaitList;
nullptr,//   cl_api_clEnqueueBarrierWithWaitList clEnqueueBarrierWithWaitList;
nullptr,//   cl_api_clGetExtensionFunctionAddressForPlatform
//       clGetExtensionFunctionAddressForPlatform;
nullptr,//   cl_api_clCreateFromGLTexture clCreateFromGLTexture;

//   /* cl_khr_d3d11_sharing */
nullptr,//   cl_api_clGetDeviceIDsFromD3D11KHR clGetDeviceIDsFromD3D11KHR;
nullptr,//   cl_api_clCreateFromD3D11BufferKHR clCreateFromD3D11BufferKHR;
nullptr,//   cl_api_clCreateFromD3D11Texture2DKHR clCreateFromD3D11Texture2DKHR;
nullptr,//   cl_api_clCreateFromD3D11Texture3DKHR clCreateFromD3D11Texture3DKHR;
nullptr,//   cl_api_clCreateFromDX9MediaSurfaceKHR clCreateFromDX9MediaSurfaceKHR;
nullptr,//   cl_api_clEnqueueAcquireD3D11ObjectsKHR clEnqueueAcquireD3D11ObjectsKHR;
nullptr,//   cl_api_clEnqueueReleaseD3D11ObjectsKHR clEnqueueReleaseD3D11ObjectsKHR;

//   /* cl_khr_dx9_media_sharing */
nullptr,//   cl_api_clGetDeviceIDsFromDX9MediaAdapterKHR
//       clGetDeviceIDsFromDX9MediaAdapterKHR;
nullptr,//   cl_api_clEnqueueAcquireDX9MediaSurfacesKHR
//       clEnqueueAcquireDX9MediaSurfacesKHR;
nullptr,//   cl_api_clEnqueueReleaseDX9MediaSurfacesKHR
//       clEnqueueReleaseDX9MediaSurfacesKHR;

//   /* cl_khr_egl_image */
nullptr,//   cl_api_clCreateFromEGLImageKHR clCreateFromEGLImageKHR;
nullptr,//   cl_api_clEnqueueAcquireEGLObjectsKHR clEnqueueAcquireEGLObjectsKHR;
nullptr,//   cl_api_clEnqueueReleaseEGLObjectsKHR clEnqueueReleaseEGLObjectsKHR;

//   /* cl_khr_egl_event */
nullptr,//   cl_api_clCreateEventFromEGLSyncKHR clCreateEventFromEGLSyncKHR;

//   /* OpenCL 2.0 */
nullptr,//   cl_api_clCreateCommandQueueWithProperties clCreateCommandQueueWithProperties;
nullptr,//   cl_api_clCreatePipe clCreatePipe;
nullptr,//   cl_api_clGetPipeInfo clGetPipeInfo;
nullptr,//   cl_api_clSVMAlloc clSVMAlloc;
nullptr,//   cl_api_clSVMFree clSVMFree;
nullptr,//   cl_api_clEnqueueSVMFree clEnqueueSVMFree;
nullptr,//   cl_api_clEnqueueSVMMemcpy clEnqueueSVMMemcpy;
nullptr,//   cl_api_clEnqueueSVMMemFill clEnqueueSVMMemFill;
nullptr,//   cl_api_clEnqueueSVMMap clEnqueueSVMMap;
nullptr,//   cl_api_clEnqueueSVMUnmap clEnqueueSVMUnmap;
nullptr,//   cl_api_clCreateSamplerWithProperties clCreateSamplerWithProperties;
nullptr,//   cl_api_clSetKernelArgSVMPointer clSetKernelArgSVMPointer;
nullptr,//   cl_api_clSetKernelExecInfo clSetKernelExecInfo;

//   /* cl_khr_sub_groups */
nullptr,//   cl_api_clGetKernelSubGroupInfoKHR clGetKernelSubGroupInfoKHR;

//   /* OpenCL 2.1 */
nullptr,//   cl_api_clCloneKernel clCloneKernel;
nullptr,//   cl_api_clCreateProgramWithIL clCreateProgramWithIL;
nullptr,//   cl_api_clEnqueueSVMMigrateMem clEnqueueSVMMigrateMem;
nullptr,//   cl_api_clGetDeviceAndHostTimer clGetDeviceAndHostTimer;
nullptr,//   cl_api_clGetHostTimer clGetHostTimer;
nullptr,//   cl_api_clGetKernelSubGroupInfo clGetKernelSubGroupInfo;
nullptr,//   cl_api_clSetDefaultDeviceCommandQueue clSetDefaultDeviceCommandQueue;

//   /* OpenCL 2.2 */
nullptr,//   cl_api_clSetProgramReleaseCallback clSetProgramReleaseCallback;
nullptr,//   cl_api_clSetProgramSpecializationConstant clSetProgramSpecializationConstant;

//   /* OpenCL 3.0 */
nullptr,//   cl_api_clCreateBufferWithProperties clCreateBufferWithProperties;
nullptr,//   cl_api_clCreateImageWithProperties clCreateImageWithProperties;
nullptr,//   cl_api_clSetContextDestructorCallback clSetContextDestructorCallback;
```
