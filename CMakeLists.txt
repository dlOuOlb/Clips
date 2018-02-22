cmake_minimum_required(VERSION 3.0)
project(Clips)

# Settings
if(DEFINED ENV{INTELOCLSDKROOT})
set(DIR_INC ./Headers $ENV{INTELOCLSDKROOT}/include)
add_definitions(-D_CL)
elseif(DEFINED ENV{CUDA_PATH})
set(DIR_INC ./Headers $ENV{CUDA_PATH}/include)
add_definitions(-D_CL)
else()
set(DIR_INC ./Headers)
endif()

set(DIR_SRC ./Sources)
set(CONFIG Release)
set(OPT_COMPILE /TC /WX /W4 /wd4201 /O2 /Ob2 /Oi /Ot /GL)
set(OPT_LINK /LTCG)

set(CMAKE_CONFIGURATION_TYPES ${CONFIG})
set(CMAKE_BUILD_TYPE ${CONFIG})
set(CMAKE_STATIC_LINKER_FLAGS ${OPT_LINK})
set(CMAKE_SUPPRESS_REGENERATION true)

# MemClip
set(NAME memclip)
add_library(${NAME} STATIC ${DIR_SRC}/${NAME}.c)
target_include_directories(${NAME} PUBLIC ${DIR_INC})
target_compile_options(${NAME} PUBLIC ${OPT_COMPILE})

# PenClip
set(NAME penclip)
add_library(${NAME} STATIC ${DIR_SRC}/${NAME}.c)
target_include_directories(${NAME} PUBLIC ${DIR_INC})
target_compile_options(${NAME} PUBLIC ${OPT_COMPILE})

# BitClip
set(NAME bitclip)
add_library(${NAME} STATIC ${DIR_SRC}/${NAME}.c)
target_include_directories(${NAME} PUBLIC ${DIR_INC})
target_compile_options(${NAME} PUBLIC ${OPT_COMPILE})
