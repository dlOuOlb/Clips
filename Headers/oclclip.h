﻿#ifndef oOCLCLIP_INC_
#define oOCLCLIP_INC_ "OCLC:2020.01.31"
/*------------------------------------------------------------------+
|	OCLClip provides some simple OpenCL wrapping functions.			|
|																	|
|	Written by Ranny Clover											|
|	http://github.com/dlOuOlb/Clips/blob/master/Headers/oclclip.h	|
+-------------------------------------------------------------------+
|	Dependency:														|
|																	|
|	MSVClip -- MemClip -- PenClip -- OCLClip						|
+-------------------------------------------------------------------+
|	Non-Prefixed Macros (Device):									|
|																	|
|	Fold_															|
|	Meta_	NULL	Acs_	_R_		__dlOuOlb__						|
|	Conc_	FULL	Mute_	_PL_	__dl	lb__					|
|																	|
|	_K_		_F_		_C_		_G_		_L_		_P_						|
|																	|
|	Work_Dims_														|
|	Work_Wait_G_					Work_Wait_L_					|
|	Work_Size_G_	Work_Nums_B_	Work_Size_L_					|
|	Work_Here_G_	Work_Here_B_	Work_Here_L_					|
+-------------------------------------------------------------------+
|	Non-Prefixed Types (Device):									|
|																	|
|	general	logical	byte_08	integer	address							|
|	GENERAL	LOGICAL	BYTE_08	INTEGER	ADDRESS							|
+-------------------------------------------------------------------+
|	Note:															|
|																	|
|	If you want to use the Clip libraries with OpenCL extensions,	|
|	please #define uOCLCLIP_USE_ before including any Clip header.	|
+-------------------------------------------------------------------+
|	About OpenCL:													|
|																	|
|	http://www.khronos.org/opencl/									|
|	http://www.khronos.org/registry/OpenCL/							|
|	http://stackoverflow.com/questions/tagged/opencl				|
|	http://www.reddit.com/r/OpenCL/									|
+------------------------------------------------------------------*/

#ifdef __OPENCL_VERSION__

#ifdef Fold_
#error The macro "Fold_" is already defined.
#else
//#define Fold_(...) (1)
#define Fold_(Comment) (1)
#endif

#if(Fold_(Non-Prefixed Basic Macros))
#ifdef NULL
//_Static_assert(((uintptr_t)(NULL))==((uintptr_t)(0)));
#else
#define NULL ((void*)(0))
#endif

#ifdef FULL
//_Static_assert(((uintptr_t)(FULL))==(~((uintptr_t)(0))));
#else
#define FULL ((void*)(~((uintptr_t)(0))))
#endif

#ifdef Acs_
#error The macro "Acs_" is already defined.
#else
#define Acs_(scope,type,Data) (*((_##scope##_ type*)&(Data)))
#endif

#ifdef Mute_
#error The macro "Mute_" is already defined.
#else
#define Mute_(Argument) ((general)(Argument))
#endif

#ifdef Meta_
#error The macro "Meta_" is already defined.
#else
#define Meta_(X) xOCLC_Meta_(X)
#define xOCLC_Meta_(X) #X
#endif

#ifdef Conc_
#error The macro "Conc_" is already defined.
#else
#define Conc_(A,B) xOCLC_Conc_(A,B)
#define xOCLC_Conc_(A,B) A##B
#endif

#if defined(__dl)||defined(lb__)
#error The macro "__dl" or "lb__" is already defined.
#else
#define __dl do
#define lb__ while(0)
#endif

#ifdef __dlOuOlb__
#error The macro __dlOuOlb__ is already defined.
#else
#define __dlOuOlb__ while(1)
#endif
#endif

#if(Fold_(Non-Prefixed Qualifier Macros))
#if defined(_K_)||defined(_F_)
#error The macro "_K_" or "_F_" is already defined.
#else
#define _K_ kernel void
#define _F_ static inline
#endif

#if defined(_C_)||defined(_G_)||defined(_L_)||defined(_P_)
#error The macro "_C_", "_G_", "_L_", or "_P_" is already defined.
#else
#define _C_ constant
#define _G_ global
#define _L_ local
#define _P_ private
#endif

#if defined(_R_)||defined(_PL_)
#error The macro "_R_" or "_PL_" is already defined.
#else
#define _R_ restrict
#define _PL_ *const
#endif
#endif

#if(Fold_(Non-Prefixed Worker Macros))
#define Work_Wait_G_() barrier(CLK_GLOBAL_MEM_FENCE)
#define Work_Wait_L_() barrier(CLK_LOCAL_MEM_FENCE)

#define Work_Dims_ get_work_dim

#define Work_Size_G_ get_global_size
#define Work_Here_G_ get_global_id

#define Work_Nums_B_ get_num_groups
#define Work_Here_B_ get_group_id

#define Work_Size_L_ get_local_size
#define Work_Here_L_ get_local_id
#endif

#if(Fold_(Type Macros))
#define OCLC_Type_Rename_(oldtype,newtype,NEWTYPE) typedef oldtype newtype;typedef const oldtype NEWTYPE
#define OCLC_Type_Declare_(spec,type,TYPE) typedef spec _##type type;typedef const spec _##type TYPE
#endif

#if(Fold_(Primal Types))
OCLC_Type_Rename_(void,general,GENERAL);
OCLC_Type_Rename_(bool,logical,LOGICAL);
OCLC_Type_Rename_(unsigned char,byte_08,BYTE_08);
OCLC_Type_Rename_(signed int,integer,INTEGER);
OCLC_Type_Rename_(uintptr_t,address,ADDRESS);
#endif

#if(Fold_(Memory Pin Structure))
enum _oclc_pa
{
	OCLCPinAxisN,
	OCLCPinAxisZ,
	OCLCPinAxisY,
	OCLCPinAxisX,
	OCLCPinAxes
};
OCLC_Type_Declare_(enum,oclc_pa,OCLC_PA);

struct _oclclip
{
	union
	{
		struct
		{
			address N;
			address Z;
			address Y;
			address X;
		};
		address S[OCLCPinAxes];
	};
};
OCLC_Type_Declare_(struct,oclclip,OCLCLIP);

_F_ oclclip Work_From_(_P_ OCLCLIP Amount)
{
	_P_ oclclip Where;

	Where.X=Work_Here_G_(0);
	Where.Y=Where.X/Amount.X;
	Where.Z=Where.Y/Amount.Y;
	Where.N=Where.Z/Amount.Z;
	Where.Z%=Amount.Z;
	Where.Y%=Amount.Y;
	Where.X%=Amount.X;

	return Where;
}
_F_ address Work_Into_(_P_ OCLCLIP Where,_P_ OCLCLIP Start,_P_ OCLCLIP Shape)
{
	_P_ address Index=Where.N+Start.N;

	Index*=Shape.Z;
	Index+=Where.Z;
	Index+=Start.Z;

	Index*=Shape.Y;
	Index+=Where.Y;
	Index+=Start.Y;

	Index*=Shape.X;
	Index+=Where.X;
	Index+=Start.X;

	return Index;
}
#endif

#else

#include <penclip.h>
#ifdef uOCLCLIP_USE_
#include <CL/opencl.h>
#ifndef __OPENCL_H
#error Cannot find the OpenCL header.
#endif
#endif

#if(Fold_(Plain Types)&&defined(__OPENCL_H))
//OCLClip : Meta-Data Structure
struct _oclc_md
{
	address Size;	//OCLClip : Byte Size
	TEXT_08 *Data;	//OCLClip : Meta-Data
};
MemC_Type_Declare_(struct,oclc_md,OCLC_MD);	//OCLClip : Meta-Data Structure

//OCLClip : 4D Pin Axis Enumeration
enum _oclc_pa
{
	OCLCPinAxisN,	//OCLClip : N-Axis
	OCLCPinAxisZ,	//OCLClip : Z-Axis
	OCLCPinAxisY,	//OCLClip : Y-Axis
	OCLCPinAxisX,	//OCLClip : X-Axis
	OCLCPinAxes		//OCLClip : The Number of Axes
};
MemC_Type_Declare_(enum,oclc_pa,OCLC_PA);	//OCLClip : 4D Pin Axis Enumeration

//OCLClip : 4D Memory Pin Structure
struct _oclc_mp
{
	union
	{
		struct
		{
			address N;	//OCLClip : Number Pin
			address Z;	//OCLClip : Depth Pin
			address Y;	//OCLClip : Height Pin
			address X;	//OCLClip : Width Pin
		};
		address S[OCLCPinAxes];	//OCLClip : Access as Array
	};
};
MemC_Type_Declare_(struct,oclc_mp,OCLC_MP);	//OCLClip : 4D Memory Pin Structure

//OCLClip : Memory Holder Structure
struct _oclc_mh
{
	general *Memory;	//OCLClip : Host Memory Address or Device Memory Object
	OCLC_MP *Start;		//OCLClip : Start Pin
	OCLC_MP *Shape;		//OCLClip : Shape Pin
	MEMC_DT *Type;		//OCLClip : Data Type
};
MemC_Type_Declare_(struct,oclc_mh,OCLC_MH);	//OCLClip : Memory Holder Structure

//OCLClip : Copy Flag Enumeration
enum _oclc_cf
{
	OCLCopyHtoH=0x48746F48,	//OCLClip : Host to Host Copy
	OCLCopyHtoD=0x48746F44,	//OCLClip : Host to Device Copy
	OCLCopyDtoH=0x44746F48,	//OCLClip : Device to Host Copy
	OCLCopyDtoD=0x44746F44	//OCLClip : Device to Device Copy
};
MemC_Type_Declare_(enum,oclc_cf,OCLC_CF);	//OCLClip : Copy Flag Enumeration

//OCLClip : Error Flag Union
union _oclc_ef
{
	cl_int I;	//OCLClip : Access as Integer

	//OCLClip : Access as Enumeration
	enum
	{
		CLSuccess=CL_SUCCESS,
		CLDeviceNotFound=CL_DEVICE_NOT_FOUND,
		CLDeviceNotAvailable=CL_DEVICE_NOT_AVAILABLE,
		CLCompilerNotAvailable=CL_COMPILER_NOT_AVAILABLE,
		CLMemObjectAllocationFailure=CL_MEM_OBJECT_ALLOCATION_FAILURE,
		CLOutOfResources=CL_OUT_OF_RESOURCES,
		CLOutOfHostMemory=CL_OUT_OF_HOST_MEMORY,
		CLProfilingInfoNotAvailable=CL_PROFILING_INFO_NOT_AVAILABLE,
		CLMemCopyOverlap=CL_MEM_COPY_OVERLAP,
		CLImageFormatMismatch=CL_IMAGE_FORMAT_MISMATCH,
		CLImageFormatNotSupported=CL_IMAGE_FORMAT_NOT_SUPPORTED,
		CLBuildProgramFailure=CL_BUILD_PROGRAM_FAILURE,
		CLMapFailure=CL_MAP_FAILURE,
		CLMisalignedSubBufferOffset=CL_MISALIGNED_SUB_BUFFER_OFFSET,
		CLExecStatusErrorForEventsInWaitList=CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST,
		CLCompileProgramFailure=CL_COMPILE_PROGRAM_FAILURE,
#ifdef CL_VERSION_1_2
		CLLinkerNotAvailable=CL_LINKER_NOT_AVAILABLE,
		CLLinkProgramFailure=CL_LINK_PROGRAM_FAILURE,
		CLDevicePartitionFailed=CL_DEVICE_PARTITION_FAILED,
		CLKernelArgInfoNotAvailable=CL_KERNEL_ARG_INFO_NOT_AVAILABLE,
#endif
		CLInvalidValue=CL_INVALID_VALUE,
		CLInvalidDeviceType=CL_INVALID_DEVICE_TYPE,
		CLInvalidPlatform=CL_INVALID_PLATFORM,
		CLInvalidDevice=CL_INVALID_DEVICE,
		CLInvalidContext=CL_INVALID_CONTEXT,
		CLInvalidQueueProperties=CL_INVALID_QUEUE_PROPERTIES,
		CLInvalidCommandQueue=CL_INVALID_COMMAND_QUEUE,
		CLInvalidHostPtr=CL_INVALID_HOST_PTR,
		CLInvalidMemObject=CL_INVALID_MEM_OBJECT,
		CLInvalidImageFormatDescriptor=CL_INVALID_IMAGE_FORMAT_DESCRIPTOR,
		CLInvalidImageSize=CL_INVALID_IMAGE_SIZE,
		CLInvalidSampler=CL_INVALID_SAMPLER,
		CLInvalidBinary=CL_INVALID_BINARY,
		CLInvalidBuildOptions=CL_INVALID_BUILD_OPTIONS,
		CLInvalidProgram=CL_INVALID_PROGRAM,
		CLInvalidProgramExecutable=CL_INVALID_PROGRAM_EXECUTABLE,
		CLInvalidKernelName=CL_INVALID_KERNEL_NAME,
		CLInvalidKernelDefinition=CL_INVALID_KERNEL_DEFINITION,
		CLInvalidKernel=CL_INVALID_KERNEL,
		CLInvalidArgIndex=CL_INVALID_ARG_INDEX,
		CLInvalidArgValue=CL_INVALID_ARG_VALUE,
		CLInvalidArgSize=CL_INVALID_ARG_SIZE,
		CLInvalidKernelArgs=CL_INVALID_KERNEL_ARGS,
		CLInvalidWorkDimension=CL_INVALID_WORK_DIMENSION,
		CLInvalidWorkGroupSize=CL_INVALID_WORK_GROUP_SIZE,
		CLInvalidWorkItemSize=CL_INVALID_WORK_ITEM_SIZE,
		CLInvalidGlobalOffset=CL_INVALID_GLOBAL_OFFSET,
		CLInvalidEventWaitList=CL_INVALID_EVENT_WAIT_LIST,
		CLInvalidEvent=CL_INVALID_EVENT,
		CLInvalidOperation=CL_INVALID_OPERATION,
		CLInvalidGlObject=CL_INVALID_GL_OBJECT,
		CLInvalidBufferSize=CL_INVALID_BUFFER_SIZE,
		CLInvalidMipLevel=CL_INVALID_MIP_LEVEL,
		CLInvalidGlobalWorkSize=CL_INVALID_GLOBAL_WORK_SIZE,
		CLInvalidProperty=CL_INVALID_PROPERTY,
#ifdef CL_VERSION_1_2
		CLInvalidImageDescriptor=CL_INVALID_IMAGE_DESCRIPTOR,
		CLInvalidCompilerOptions=CL_INVALID_COMPILER_OPTIONS,
		CLInvalidLinkerOptions=CL_INVALID_LINKER_OPTIONS,
		CLInvalidDevicePartitionCount=CL_INVALID_DEVICE_PARTITION_COUNT,
#endif
#ifdef CL_VERSION_2_0
		CLInvalidPipeSize=CL_INVALID_PIPE_SIZE,
		CLInvalidDeviceQueue=CL_INVALID_DEVICE_QUEUE
#endif
	}
	E;
};
MemC_Type_Declare_(union,oclc_ef,OCLC_EF);	//OCLClip : Error Flag Union
#endif

#if(Fold_(Advanced Types)&&defined(__OPENCL_H))
//OCLClip : Environment Manager Structure
struct _oclc_em
{
	//OCLClip : Platform Manager
	const struct
	{
		//OCLClip : OpenCL Platform Number
		ADDRESS Nums;
		//OCLClip : Platform List
		const struct _oclc_em_platform
		{
			//OCLClip : Platform ID
			const cl_platform_id ID;
			//OCLClip : Platform Name
			OCLC_MD Name;
			//OCLClip : Context Object
			const cl_context Context;
			//OCLClip : Device Manager
			const struct
			{
				//OCLClip : Device Number
				ADDRESS Nums;
				//OCLClip : Device List
				const struct _oclc_em_device
				{
					//OCLClip : Device ID
					const cl_device_id ID;
					//OCLClip : Command Queue
					const cl_command_queue Queue;
					//OCLClip : Device Name
					OCLC_MD Name;
					//OCLClip : Device Information
					const struct _oclc_em_device_info
					{
						const struct
						{
							const cl_uint AddressBits;				//OCLClip : The default compute device address space size of the global address space specified as an unsigned integer value in bits.
							const cl_uint MaxClockFrequency;		//OCLClip : Maximum configured clock frequency of the device in MHz.
							const cl_uint MaxComputeUnits;			//OCLClip : The number of parallel compute units on the OpenCL device. A work-group executes on a single compute unit.
							const cl_uint MaxWorkItemDimensions;	//OCLClip : Maximum dimensions that specify the global and local work-item IDs used by the data parallel execution model.
						};
						const struct
						{
							const cl_ulong GlobalMemSize;			//OCLClip : Size of global device memory in bytes.
							const cl_ulong LocalMemSize;			//OCLClip : Size of local memory region in bytes.
							const cl_ulong MaxConstantBufferSize;	//OCLClip : Max size in bytes of a constant buffer allocation.
							const cl_ulong MaxMemAllocSize;			//OCLClip : Max size of memory object allocation in bytes.
						};
						const struct
						{
							ADDRESS MaxWorkGroupSize;		//OCLClip : Maximum number of work-items in a work-group executing a kernel on a single compute unit, using the data parallel execution model.
							ADDRESS _PL_ MaxWorkItemSizes;	//OCLClip : Maximum number of work-items that can be specified in each dimension of the work-group to clEnqueueNDRangeKernel.
						};
					}
					Info;
				}
				_PL_ List;
			}
			Device;
		}
		_PL_ List;
	}
	Platform;
};
MemC_Type_Declare_(struct,oclc_em,OCLC_EM);	//OCLClip : Environment Manager Structure

//OCLClip : Program Manager Structure
struct _oclc_pm
{
	GENERAL _PL_ Origin;	//OCLClip : Responsible Library

	//OCLClip : Program Manager
	const struct
	{
		const cl_program ID;	//OCLClip : Program Object

		//OCLClip : Kernel Manager
		const struct
		{
			//OCLClip : Kernel Number
			const struct
			{
				ADDRESS Total;	//OCLClip : The Total Number of Kernels
				ADDRESS Valid;	//OCLClip : The Number of Valid Kernels
			}
			Nums;

			//OCLClip : Kernel List
			const struct _oclc_pm_kernel
			{
				const cl_kernel ID;	//OCLClip : Kernel Object
				ADDRESS xPreserved;	//OCLClip : Preserved for Future Usage
				OCLC_MD Name;		//OCLClip : Kernel Name
			}
			_PL_ List;
		}
		Kernel;
	}
	Program;
};
MemC_Type_Declare_(struct,oclc_pm,OCLC_PM);	//OCLClip : Program Manager Structure
#endif

#if(Fold_(Library Casing))
//OCLClip : Library Case Structure
typedef const struct
{
	//OCLClip : Library Version - "OCLC:yyyy.mm.dd"
	BYTE_08 _PL_ _R_ Version;
}
OCLCASE;

//OCLClip : Library Case Object
extern OCLCASE OCLC,*OCLC_(general);

#ifdef __OPENCL_H
//OCLClip : OpenCL Extension Structure
typedef const struct
{
	//OCLClip : Environment Manager Functions
	const struct
	{
		//OCLClip : Environment Manager Creation - Delete with "OCLCL.CM.Delete_"
		oclc_em*(_PL_ Create_)(oclc_ef _PL_ _R_ Error);
		//OCLClip : Environment Manager Deletion
		general(_PL_ Delete_)(oclc_em *_PL_ _R_);

		//OCLClip : Select Functions
		const struct
		{
			//OCLClip : Get a Context Object
			cl_context(_PL_ Context_)(OCLC_EM _PL_ _R_,ADDRESS PlatformSelect);
			//OCLClip : Get a Command Queue Object
			cl_command_queue(_PL_ Queue_)(OCLC_EM _PL_ _R_,ADDRESS PlatformSelect,ADDRESS DeviceSelect);
		}
		Select;
	}
	EM;

	//OCLClip : Program Manager Functions
	const struct
	{
		//OCLClip : Program Manager Creation - Delete with "OCLCL.PM.Delete_"
		oclc_pm*(_PL_ Create_)(GENERAL _PL_ LibraryID,OCLC_MD _PL_ _R_ KernelList,ADDRESS KernelNums);
		//OCLClip : Program Manager Deletion
		general(_PL_ Delete_)(oclc_pm *_PL_ _R_);

		//OCLClip : Program Build Functions
		const struct
		{
			//OCLClip : Build from Source Files
			//＊Do only once per program manager.
			//　Not found kernels will be just ignored.
			const struct
			{
				//OCLClip : Build a program from source files with a narrow string path.
				general(_PL_ T08_)(oclc_pm _PL_ _R_,const cl_context Context,TEXT_08 _PL_ _R_ BuildOption,TEXT_08 _PL_ _PL_ _R_ SourcePath,const cl_uint SourceNumber,oclc_ef _PL_ _R_ Error);
				//OCLClip : Build a program from source files with a wide string path.
				general(_PL_ T16_)(oclc_pm _PL_ _R_,const cl_context Context,TEXT_08 _PL_ _R_ BuildOption,TEXT_16 _PL_ _PL_ _R_ SourcePath,const cl_uint SourceNumber,oclc_ef _PL_ _R_ Error);
			}
			Source;

			//OCLClip : Build from Binary Files
			//＊Do only once per program manager.
			//　Not found kernels will be just ignored.
			//＊The number of paths must be same as the number of devices associated with the context.
			const struct
			{
				//OCLClip : Build a program from binary files with a narrow string path.
				general(_PL_ T08_)(oclc_pm _PL_ _R_,const cl_context Context,TEXT_08 _PL_ _R_ BuildOption,TEXT_08 _PL_ _PL_ _R_ BinaryPath,oclc_ef _PL_ _R_ Error);
				//OCLClip : Build a program from binary files with a wide string path.
				general(_PL_ T16_)(oclc_pm _PL_ _R_,const cl_context Context,TEXT_08 _PL_ _R_ BuildOption,TEXT_16 _PL_ _PL_ _R_ BinaryPath,oclc_ef _PL_ _R_ Error);
			}
			Binary;

			//OCLClip : Save Binary Files after Building
			//＊Do only after the program has been built.
			//＊The number of paths must be same as the number of devices associated with the context.
			const struct
			{
				//OCLClip : Save a program as binary files with a narrow string path.
				general(_PL_ T08_)(OCLC_PM _PL_ _R_,TEXT_08 _PL_ _PL_ _R_ BinaryPath,oclc_ef _PL_ _R_ Error);
				//OCLClip : Save a program as binary files with a wide string path.
				general(_PL_ T16_)(OCLC_PM _PL_ _R_,TEXT_16 _PL_ _PL_ _R_ BinaryPath,oclc_ef _PL_ _R_ Error);
			}
			Save;

			//OCLClip : Get Build Log - Only after Program Building
			general(_PL_ Log_)(OCLC_PM _PL_ _R_ Program,FILE _PL_ _R_ Stream,oclc_ef _PL_ _R_ Error);
		}
		Build;

		//OCLClip : Select Functions
		const struct
		{
			//OCLClip : Get a Kernel Object
			cl_kernel(_PL_ Kernel_)(OCLC_PM _PL_ _R_,ADDRESS KernelSelect);
		}
		Select;
	}
	PM;

	//OCLClip : Platform ID Functions
	const struct
	{
		//OCLClip : Information Functions
		const struct
		{
			//OCLClip : Get the Size of Information
			address(_PL_ Size_)(const cl_platform_id Platform,const cl_platform_info Flag,oclc_ef _PL_ _R_ Error);
			//OCLClip : Get Information
			general(_PL_ What_)(const cl_platform_id Platform,const cl_platform_info Flag,general _PL_ Info,ADDRESS Size,oclc_ef _PL_ _R_ Error);
		}
		Info;
	}
	Platform;

	//OCLClip : Device ID Functions
	const struct
	{
		//OCLClip : Information Functions
		const struct
		{
			//OCLClip : Get the Size of Information
			address(_PL_ Size_)(const cl_device_id Device,const cl_device_info Flag,oclc_ef _PL_ _R_ Error);
			//OCLClip : Get Information
			general(_PL_ What_)(const cl_device_id Device,const cl_device_info Flag,general _PL_ Info,ADDRESS Size,oclc_ef _PL_ _R_ Error);
		}
		Info;
	}
	Device;

	//OCLClip : Context Object Functions
	const struct
	{
		//OCLClip : Information Functions
		const struct
		{
			//OCLClip : Get the Size of Information
			address(_PL_ Size_)(const cl_context Context,const cl_context_info Flag,oclc_ef _PL_ _R_ Error);
			//OCLClip : Get Information
			general(_PL_ What_)(const cl_context Context,const cl_context_info Flag,general _PL_ Info,ADDRESS Size,oclc_ef _PL_ _R_ Error);
		}
		Info;
	}
	Context;

	//OCLClip : Queue Object Functions
	const struct
	{
		//OCLClip : Information Functions
		const struct
		{
			//OCLClip : Get the Size of Information
			address(_PL_ Size_)(const cl_command_queue Queue,const cl_command_queue_info Flag,oclc_ef _PL_ _R_ Error);
			//OCLClip : Get Information
			general(_PL_ What_)(const cl_command_queue Queue,const cl_command_queue_info Flag,general _PL_ Info,ADDRESS Size,oclc_ef _PL_ _R_ Error);
		}
		Info;

		//OCLClip : Asynchronous Memory Fill
		//＊Required (Value) size is (MemoryHolder)->Type->SizeType bytes.
		general(_PL_ Fill_)(const cl_command_queue Queue,GENERAL _PL_ Value,OCLC_MH _PL_ _R_ MemoryHolder,OCLC_MP _PL_ _R_ FillLength,oclc_ef _PL_ _R_ Error);
		//OCLClip : Asynchronous Memory Copy
		general(_PL_ Copy_)(const cl_command_queue Queue,OCLC_CF CopyMode,OCLC_MH _PL_ _R_ SourceHolder,OCLC_MH _PL_ _R_ TargetHolder,OCLC_MP _PL_ _R_ CopyLength,oclc_ef _PL_ _R_ Error);
		//OCLClip : Synchronization
		general(_PL_ Wait_)(const cl_command_queue Queue,oclc_ef _PL_ _R_ Error);
		//OCLClip : Preserved for Future Usage
		ADDRESS xPreserved;
	}
	Queue;

	//OCLClip : Kernel Object Functions
	const struct
	{
		//OCLClip : Information Functions
		const struct
		{
			//OCLClip : Get the Size of Information
			address(_PL_ Size_)(const cl_kernel Kernel,const cl_kernel_info Flag,oclc_ef _PL_ _R_ Error);
			//OCLClip : Get Information
			general(_PL_ What_)(const cl_kernel Kernel,const cl_kernel_info Flag,general _PL_ Info,ADDRESS Size,oclc_ef _PL_ _R_ Error);
		}
		Info;

		//OCLClip : Argument Set Functions
		const struct
		{
			//OCLClip : Pass a Memory Object
			general(_PL_ G_)(const cl_kernel,const cl_uint ArgIndex,const cl_mem MemoryObject,oclc_ef _PL_ _R_ Error);
			//OCLClip : Pass a Local Memory Size
			general(_PL_ L_)(const cl_kernel,const cl_uint ArgIndex,ADDRESS LocalMemorySize,oclc_ef _PL_ _R_ Error);
			//OCLClip : Pass a Value
			general(_PL_ P_)(const cl_kernel,const cl_uint ArgIndex,GENERAL _PL_ ValueAddress,ADDRESS ValueSize,oclc_ef _PL_ _R_ Error);
		}
		Arg;

		//OCLClip : Preserved for Future Usage.
		ADDRESS xPreserved;
	}
	Kernel;

	//OCLClip : Memory Object Functions
	const struct
	{
		//OCLClip : Information Functions
		const struct
		{
			//OCLClip : Get the Size of Information
			address(_PL_ Size_)(const cl_mem Memory,const cl_mem_info Flag,oclc_ef _PL_ _R_ Error);
			//OCLClip : Get Information
			general(_PL_ What_)(const cl_mem Memory,const cl_mem_info Flag,general _PL_ Info,ADDRESS Size,oclc_ef _PL_ _R_ Error);
		}
		Info;

		//OCLClip : Memory Object Creation Functions
		const struct
		{
			//OCLClip : Buffer Creation - Delete with "OCLCL.MO.Delete_"
			cl_mem(_PL_ Buffer_)(const cl_context Context,ADDRESS Size,oclc_ef _PL_ _R_ Error);
			//OCLClip : Sub-Buffer Creation - Delete with "OCLCL.MO.Delete_"
			cl_mem(_PL_ Sub_)(const cl_mem RootBuffer,ADDRESS Offset,ADDRESS Size,oclc_ef _PL_ _R_ Error);
		}
		Create;

		//OCLClip : Memory Object Deletion
		general(_PL_ Delete_)(cl_mem _PL_ _R_);
		
		//OCLClip : Preserved for Future Usage
		ADDRESS xPreserved;
	}
	Memory;

	//OCLClip : Memory Pin Functions
	const struct
	{
		//OCLClip : Length Setting Functions
		const struct
		{
			//OCLClip : Set 1D Length
			oclc_mp(_PL_ D1_)(ADDRESS X);
			//OCLClip : Set 2D Length
			oclc_mp(_PL_ D2_)(ADDRESS Y,ADDRESS X);
			//OCLClip : Set 3D Length
			oclc_mp(_PL_ D3_)(ADDRESS Z,ADDRESS Y,ADDRESS X);
			//OCLClip : Set 4D Length
			oclc_mp(_PL_ D4_)(ADDRESS N,ADDRESS Z,ADDRESS Y,ADDRESS X);
		}
		Length;

		//OCLClip : Offset Setting Functions
		const struct
		{
			//OCLClip : Set 1D Offset
			oclc_mp(_PL_ D1_)(ADDRESS X);
			//OCLClip : Set 2D Offset
			oclc_mp(_PL_ D2_)(ADDRESS Y,ADDRESS X);
			//OCLClip : Set 3D Offset
			oclc_mp(_PL_ D3_)(ADDRESS Z,ADDRESS Y,ADDRESS X);
			//OCLClip : Set 4D Offset
			oclc_mp(_PL_ D4_)(ADDRESS N,ADDRESS Z,ADDRESS Y,ADDRESS X);
		}
		Offset;

		//OCLClip : Memory Pin Information
		const struct
		{
			//OCLClip : Validity Check
			//＊Return value is 1 for any excess, otherwise 0.
			const struct
			{
				//OCLClip : Validity Check for Length
				//　Excess means any Start+Amount>Shape or Amount==0
				logical(_PL_ Length_)(OCLC_MP _PL_ Start,OCLC_MP _PL_ Amount,OCLC_MP _PL_ Shape);

				//OCLClip : Validity Check for Offset
				//　Excess means any Start>Shape
				logical(_PL_ Offset_)(OCLC_MP _PL_ Start,OCLC_MP _PL_ Shape);
			}
			Invalid;

			//OCLClip : Total Number of Elements
			//　i.e. N×Z×Y×X
			address(_PL_ Total_)(OCLC_MP _PL_ _R_);

			//OCLClip : Empty Pin
			OCLC_MP _PL_ _R_ Zero;
		};
	}
	MP;
}
OCLC_CL;

//OCLClip : OpenCL Extension Object
extern OCLC_CL OCLCL,*OCLCL_(general);

//OCLClip : Get the information about the object.
#define OCLCL_Info_(Kind,Whose,It,Flag,Error) OCLCL.Kind.Info.What_(Whose,Flag,It,sizeof(*(It)),Error)
#else
//OCLClip : Indirect access to the OpenCL extension object.
//＊If the library is not built with OpenCL settings,
//　then the return address will be just NULL.
extern GENERAL *OCLCL_(general);

//OCLClip : Get the information about the object.
#define OCLCL_Info_(...) static_assert(0,"#define uOCLCLIP_USE_ before #include <oclclip.h>")
#endif
#endif
#endif
#endif
