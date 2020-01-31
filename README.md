# Clips Documentation

## Build Guide

### Make Build Directory

```cmd
mkdir build
cd build
```

### CMake Command Examples

* 32-bit Platform without OpenCL
  ```cmd
  cmake .. -A "Win32"
  ```

* 64-bit Platform without OpenCL
  ```cmd
  cmake .. -A "x64"
  ```

* 32-bit Platform with Intel OpenCL
  ```cmd
  cmake .. -A "Win32" -DCL_ENV:STRING=INTELOCLSDKROOT -DCL_INC:STRING=include -DCL_LIB:STRING=lib/x86
  ```

* 64-bit Platform with NVIDIA OpenCL
  ```cmd
  cmake .. -A "x64" -DCL_ENV:STRING=CUDA_PATH -DCL_INC:STRING=include -DCL_LIB:STRING=lib/x64
  ```

### Build Process

1. Build the "ALL_BUILD" project in the "Clips" solution.
2. Execute "builder.exe" in the "Release" folder if you want the OpenCL extension.
3. Take the output object files.

## Library Usage

### malloc/free Function Linkage Example

```c
#define I_USE_STATIC_CHUNKS 1024

#if(I_USE_STATIC_CHUNKS)
extern general *uMemC_Malloc_(ADDRESS Size)
{
	MemC_ML_Static_(MyMemoryLender,I_USE_STATIC_CHUNKS);
	return MemC.ML.Borrow_(MyMemoryLender,Size);
}
extern general uMemC_Free_(general _PL_ Memory)
{
	MemC.ML.Return_(Memory);
	return;
}
#else
MemC_Default_;
#endif
```

### Mean/StdDev Calculation Example

```c
#define __STDC_WANT_LIB_EXT1__ (1)
#include <timclip.h>
#include <linclip.h>

#include <math.h>

MemC_Default_;

extern integer main(general)
{
	TimC_RG_Auto_(RandGen,1,(data_64)time(NULL));
	real_32 Array[1024];
	ADDRESS Length=sizeof(Array)/sizeof(*Array);
	REAL_32 Averager=1.0F/((real_32)(Length));
	real_32 Mean,StdDev;

	PenC_Stream_Format_T08_(O,stdout,"Ideal Mean : ");
	PenC_Stream_Format_T08_(I,stdin,"%f",&Mean);
	PenC_Stream_Format_T08_(O,stdout,"Ideal Standard Deviation : ");
	PenC_Stream_Format_T08_(I,stdin,"%f",&StdDev);

	TimC.RG.Gau.R32_(RandGen,0,Array,Length,Mean,StdDev);
	Mean=Averager*LinC.Sum_1.R32_(Array,Length);
	StdDev=Averager*LinC.Dot_2.R32_(Array,Array,Length)-Mean*Mean;
	StdDev=sqrtf(StdDev);

	PenC_Stream_Format_T08_(O,stdout,"Actual Mean : %f \n",Mean);
	PenC_Stream_Format_T08_(O,stdout,"Actual Standard Deviation : %f \n",StdDev);

	return 0;
}
```
