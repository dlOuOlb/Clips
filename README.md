# Clips Documentation

## Build Guide

### Make Build Directory

```
mkdir build
cd build
```

### CMake Command Examples

* 32-bit Platform without OpenCL
  ```
  cmake .. -A "Win32"
  ```

* 64-bit Platform without OpenCL
  ```
  cmake .. -A "x64"
  ```

* 32-bit Platform with Intel OpenCL
  ```
  cmake .. -A "Win32" -DCL_ENV:STRING=INTELOCLSDKROOT -DCL_INC:STRING=include -DCL_LIB:STRING=lib/x86
  ```

* 64-bit Platform with NVIDIA OpenCL
  ```
  cmake .. -A "x64" -DCL_ENV:STRING=CUDA_PATH -DCL_INC:STRING=include -DCL_LIB:STRING=lib/x64
  ```

### Build Process

1. Build the "ALL_BUILD" project in the "Clips" solution.
2. Execute "builder.exe" in the "Release" folder if you want the OpenCL extension.
3. Take the output object files.

## Library Usage

### malloc/free Function Linkage Example

```
#define I_USE_STATIC_CHUNKS 1024

#if(I_USE_STATIC_CHUNKS)
MemC_ML_Define_(MyMemoryLender,I_USE_STATIC_CHUNKS)
static general *_MemC_Alloc_(ADDRESS Size) { return MemC.ML.Borrow_(MyMemoryLender,Size); }
static general _MemC_Free_(general _PL_ Memory) { MemC.ML.Return_(Memory); }
#else
_MemC_Default_
#endif
```

### Mean/StdDev Calculation Example

```
#include <penclip.h>
#include <linclip.h>
#include <timclip.h>

integer main(general)
{
    ADDRESS Length=1024;
    REAL_32 Averager=1.0F/((real_32)Length);
    real_32 Mean,StdDev;

    timc_rg *RandGen=TimC.RG.Create_(1);
    real_32 *Array=MemC_Alloc_ND_(real_32,1,Length);

    PenC_Stream_Format_T08_(0,NULL,"Ideal Mean : ");
    PenC_Stream_Format_T08_(1,NULL,"%f",&Mean);
    PenC_Stream_Format_T08_(0,NULL,"Ideal Standard Deviation : ");
    PenC_Stream_Format_T08_(1,NULL,"%f",&StdDev);

    TimC.RG.Gau.R32_(RandGen,0,Array,Length,Mean,StdDev);
    Mean=Averager*LinC.Sum_1.R32_(Array,Length);
    StdDev=Averager*LinC.Dot_2.R32_(Array,Array,Length)-Mean*Mean;

    PenC_Stream_Format_T08_(0,NULL,"Actual Mean : %f \n",Mean);
    PenC_Stream_Format_T08_(0,NULL,"Actual Standard Deviation : %f \n",StdDev);

    MemC_Deloc_(Array);
    TimC.RG.Delete_(&RandGen);

    return 0;
}
```
