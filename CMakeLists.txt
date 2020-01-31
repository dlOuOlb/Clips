cmake_minimum_required(VERSION 3.0)
project(Clips)

# OpenCL Directory
if(DEFINED CL_ENV)
	if(NOT DEFINED CL_INC)
		message(FATAL_ERROR "Specify the include path via -DCL_INC:STRING=(include).")
	endif()

	if(NOT DEFINED CL_LIB)
		message(FATAL_ERROR "Specify the library path via -DCL_LIB:STRING=(library).")
	endif()

	if(DEFINED ENV{${CL_ENV}})
		set(FLAG_CL 1)
		set(DIR_INC $ENV{${CL_ENV}}/${CL_INC})
		set(DIR_OCL $ENV{${CL_ENV}}/${CL_LIB})

		string(REPLACE "\\" "/" DIR_INC "${DIR_INC}")
		string(REPLACE "\\" "/" DIR_OCL "${DIR_OCL}")

		string(REPLACE "//" "/" DIR_INC "${DIR_INC}")
		string(REPLACE "//" "/" DIR_OCL "${DIR_OCL}")

		message("OpenCL Include Path:")
		message(${DIR_INC})
		message("OpenCL Library Path:")
		message(${DIR_OCL})
	else()
		message(FATAL_ERROR "OpenCL path is not found.")
	endif()
else()
	set(FLAG_CL 0)

	message("OpenCL path is not specified via -DCL_ENV:STRING=(directory).")
endif()
unset(CL_ENV CACHE)
unset(CL_INC CACHE)
unset(CL_LIB CACHE)

if(FLAG_CL)
	add_definitions(-DuOCLCLIP_USE_)
endif()

# Settings
set(DIR_INC ./Headers ${DIR_INC})
set(CONFIG Release)
set(DIR_SRC ./Sources)
set(DIR_USE ./Mains)
set(OPT_COMPILE /TC /WX /Wall /O2 /Ob2 /Oi /Ot /GL /fp:fast /fp:except-)
set(OPT_LINK /LTCG)

set(CMAKE_CONFIGURATION_TYPES ${CONFIG})
set(CMAKE_BUILD_TYPE ${CONFIG})
set(CMAKE_STATIC_LINKER_FLAGS ${OPT_LINK})
set(CMAKE_EXE_LINKER_FLAGS ${OPT_LINK})
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

# OCLClip
set(NAME oclclip)
add_library(${NAME} STATIC ${DIR_SRC}/${NAME}.c)
target_include_directories(${NAME} PUBLIC ${DIR_INC})
target_compile_options(${NAME} PUBLIC ${OPT_COMPILE})

# BitClip
set(NAME bitclip)
add_library(${NAME} STATIC ${DIR_SRC}/${NAME}.c)
target_include_directories(${NAME} PUBLIC ${DIR_INC})
target_compile_options(${NAME} PUBLIC ${OPT_COMPILE})

# LinClip
set(NAME linclip)
add_library(${NAME} STATIC ${DIR_SRC}/${NAME}.c)
target_include_directories(${NAME} PUBLIC ${DIR_INC})
target_compile_options(${NAME} PUBLIC ${OPT_COMPILE})

# BoxClip
set(NAME boxclip)
add_library(${NAME} STATIC ${DIR_SRC}/${NAME}.c)
target_include_directories(${NAME} PUBLIC ${DIR_INC})
target_compile_options(${NAME} PUBLIC ${OPT_COMPILE})

# TimClip
set(NAME timclip)
add_library(${NAME} STATIC ${DIR_SRC}/${NAME}.c)
target_include_directories(${NAME} PUBLIC ${DIR_INC})
target_compile_options(${NAME} PUBLIC ${OPT_COMPILE})

# PriClip
set(NAME priclip)
add_library(${NAME} STATIC ${DIR_SRC}/${NAME}.c)
target_include_directories(${NAME} PUBLIC ${DIR_INC})
target_compile_options(${NAME} PUBLIC ${OPT_COMPILE})

# OpenCL Kernel Builder
if(FLAG_CL)
	set(NAME builder)
	add_executable(${NAME} ${DIR_USE}/${NAME}.c)
	target_include_directories(${NAME} PRIVATE ${DIR_INC})
	target_compile_options(${NAME} PRIVATE ${OPT_COMPILE})
	target_link_libraries(${NAME} PRIVATE memclip penclip oclclip bitclip linclip ${DIR_OCL}/OpenCL.lib)
endif()

# Sorting Tester
set(NAME sorting)
add_executable(${NAME} ${DIR_USE}/${NAME}.c)
target_include_directories(${NAME} PRIVATE ${DIR_INC})
target_compile_options(${NAME} PRIVATE ${OPT_COMPILE})
if(FLAG_CL)
	target_link_libraries(${NAME} PRIVATE memclip penclip oclclip bitclip linclip timclip ${DIR_OCL}/OpenCL.lib)
else()
	target_link_libraries(${NAME} PRIVATE memclip penclip oclclip bitclip linclip timclip)
endif()

# Prime Factorizer
set(NAME prime)
add_executable(${NAME} ${DIR_USE}/${NAME}.c)
target_include_directories(${NAME} PRIVATE ${DIR_INC})
target_compile_options(${NAME} PRIVATE ${OPT_COMPILE})
if(FLAG_CL)
	target_link_libraries(${NAME} PRIVATE memclip penclip oclclip bitclip priclip timclip ${DIR_OCL}/OpenCL.lib)
else()
	target_link_libraries(${NAME} PRIVATE memclip penclip oclclip bitclip priclip timclip)
endif()
