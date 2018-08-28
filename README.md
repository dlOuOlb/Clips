Build Guide
===========

* Make Build Directory
  ```
  mkdir build
  cd build
  ```

* CMake Build
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

  * 64-bit Platform with Intel OpenCL
    ```
    cmake .. -A "x64" -DCL_ENV:STRING=INTELOCLSDKROOT -DCL_INC:STRING=include -DCL_LIB:STRING=lib/x64
    ```

  * 32-bit Platform with NVIDIA OpenCL
    ```
    cmake .. -A "Win32" -DCL_ENV:STRING=CUDA_PATH -DCL_INC:STRING=include -DCL_LIB:STRING=lib/Win32
    ```

  * 64-bit Platform with NVIDIA OpenCL
    ```
    cmake .. -A "x64" -DCL_ENV:STRING=CUDA_PATH -DCL_INC:STRING=include -DCL_LIB:STRING=lib/x64
    ```
