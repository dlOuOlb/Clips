/*------------------------------------------------------------------*/
/*	OCLClip provides some simple OpenCL wrapping functions.			*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2019.06.21	*/
/*------------------------------------------------------------------*/
/*	OpenCL Support													*/
/*	http://www.khronos.org/opencl/									*/
/*	http://www.khronos.org/registry/OpenCL/							*/
/*	http://stackoverflow.com/questions/tagged/opencl				*/
/*	http://www.reddit.com/r/OpenCL/									*/
/*------------------------------------------------------------------*/

#ifndef _INC_OCLCLIP
#define _INC_OCLCLIP

#ifdef __OPENCL_VERSION__

#if(1)
#ifdef Fold_
#error The macro "Fold_" is already defined.
#else
#define Fold_(Comment) (1)
#endif
#endif

#if(Fold_(Primal Macros))
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

#if defined(_Conc_)||defined(Conc_)
#error The macro "_Conc_" or "Conc_" is already defined.
#else
#define _Conc_(A,B) A##B
#define Conc_(A,B) _Conc_(A,B)
#endif
#endif

#if(Fold_(Qualifier Macros))
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

#if(Fold_(Worker Macros))
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
#define OCLC_Type_Rename_(oldtype,newtype,NEWTYPE) typedef oldtype newtype;typedef const oldtype NEWTYPE;
#define OCLC_Type_Declare_(spec,type,TYPE) typedef spec _##type type;typedef const spec _##type TYPE;
#endif

#if(Fold_(Primal Types))
OCLC_Type_Rename_(void,general,GENERAL);
OCLC_Type_Rename_(char,byte_08,BYTE_08);
OCLC_Type_Rename_(int,integer,INTEGER);
OCLC_Type_Rename_(size_t,address,ADDRESS);
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

#if(1)
#include <CL\opencl.h>
#include <penclip.h>
#ifdef _
#error The macro "_" is already defined.
#endif
#endif

#if(Fold_(Redefinition:OpenCL Types))
MemC_Type_Rename_(struct _cl_platform_id,oclc_pi,OCLC_PI);		//OCLClip : OpenCL Platform ID
MemC_Type_Rename_(struct _cl_device_id,oclc_di,OCLC_DI);		//OCLClip : OpenCL Device ID
MemC_Type_Rename_(struct _cl_context,oclc_co,OCLC_CO);			//OCLClip : OpenCL Context Object
MemC_Type_Rename_(struct _cl_program,oclc_po,OCLC_PO);			//OCLClip : OpenCL Program Object
MemC_Type_Rename_(struct _cl_kernel,oclc_ko,OCLC_KO);			//OCLClip : OpenCL Kernel Object
MemC_Type_Rename_(struct _cl_command_queue,oclc_qo,OCLC_QO);	//OCLClip : OpenCL Command Queue Object
MemC_Type_Rename_(struct _cl_mem,oclc_mo,OCLC_MO);				//OCLClip : OpenCL Memory Object
#endif

#if(Fold_(Definition:Primal Types))
//OCLClip : Meta-Data Structure
struct _oclc_md
{
	address Size;	//OCLClip : Byte Size
	BYTE_08 *Data;	//OCLClip : Meta-Data
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
static_assert(OCLCPinAxes==4,"The pin must be 4D.");

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
		CLLinkerNotAvailable=CL_LINKER_NOT_AVAILABLE,
		CLLinkProgramFailure=CL_LINK_PROGRAM_FAILURE,
		CLDevicePartitionFailed=CL_DEVICE_PARTITION_FAILED,
		CLKernelArgInfoNotAvailable=CL_KERNEL_ARG_INFO_NOT_AVAILABLE,
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
		CLInvalidImageDescriptor=CL_INVALID_IMAGE_DESCRIPTOR,
		CLInvalidCompilerOptions=CL_INVALID_COMPILER_OPTIONS,
		CLInvalidLinkerOptions=CL_INVALID_LINKER_OPTIONS,
		CLInvalidDevicePartitionCount=CL_INVALID_DEVICE_PARTITION_COUNT,
		CLInvalidPipeSize=CL_INVALID_PIPE_SIZE,
		CLInvalidDeviceQueue=CL_INVALID_DEVICE_QUEUE
	}
	E;
};
MemC_Type_Declare_(union,oclc_ef,OCLC_EF);	//OCLClip : Error Flag Union
static_assert((sizeof(oclc_ef)==sizeof(cl_int)),"sizeof(enum) != sizeof(integer)");
static_assert(CLSuccess==0,"CLSuccess != 0");
#endif

#if(Fold_(Definition:Manager Types))
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
			oclc_pi _PL_ ID;
			//OCLClip : Platform Name
			OCLC_MD Name;
			//OCLClip : Context Object
			oclc_co _PL_ Context;
			//OCLClip : Device Manager
			const struct
			{
				//OCLClip : Device Number
				ADDRESS Nums;
				//OCLClip : Device List
				const struct _oclc_em_device
				{
					//OCLClip : Device ID
					oclc_di _PL_ ID;
					//OCLClip : Device Name
					OCLC_MD Name;
					//OCLClip : Command Queue
					oclc_qo _PL_ Queue;
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
static_assert((sizeof(struct _oclc_em_device_info)%sizeof(address))==0,"Structure Misalign");

//OCLClip : Program Manager Structure
struct _oclc_pm
{
	GENERAL _PL_ Origin;	//OCLClip : Responsible Library

	//OCLClip : Program Manager
	const struct
	{
		oclc_po _PL_ ID;	//OCLClip : Program Object

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
				oclc_ko _PL_ ID;	//OCLClip : Kernel Object
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
struct _oclcase
{
	//OCLClip : Library Version
	BYTE_08 _PL_ Version;

	//OCLClip : Environment Manager Functions
	const struct
	{
		//OCLClip : Environment Manager Creation - Delete with "OCLC.CM.Delete_"
		oclc_em*(_PL_ Create_)(oclc_ef _PL_ Error);
		//OCLClip : Environment Manager Deletion
		general(_PL_ Delete_)(oclc_em *_PL_);

		//OCLClip : Select Functions
		const struct
		{
			//OCLClip : Get a Context Object
			oclc_co*(_PL_ Context_)(OCLC_EM _PL_,ADDRESS PlatformSelect);
			//OCLClip : Get a Command Queue Object
			oclc_qo*(_PL_ Queue_)(OCLC_EM _PL_,ADDRESS PlatformSelect,ADDRESS DeviceSelect);
		}
		Select;
	}
	EM;

	//OCLClip : Program Manager Functions
	const struct
	{
		//OCLClip : Program Manager Creation - Delete with "OCLC.PM.Delete_"
		oclc_pm*(_PL_ Create_)(GENERAL _PL_ LibraryID,OCLC_MD _PL_ KernelList,ADDRESS KernelNums);
		//OCLClip : Program Build Functions
		const struct
		{
			//OCLClip : Build from Source Files
			const struct
			{
				//OCLClip : Program Build from Source Files with 8-bit String Path - Only Once per Program Manager
				//£ªNot found kernels will be just ignored.
				general(_PL_ T08_)(oclc_pm _PL_,oclc_co _PL_ Context,BYTE_08 _PL_ BuildOption,TEXT_08 _PL_ _PL_ SourcePath,const cl_uint SourceNumber,oclc_ef _PL_ Error);
				//OCLClip : Program Build from Source Files with 16-bit String Path - Only Once per Program Manager
				//£ªNot found kernels will be just ignored.
				general(_PL_ T16_)(oclc_pm _PL_,oclc_co _PL_ Context,BYTE_08 _PL_ BuildOption,TEXT_16 _PL_ _PL_ SourcePath,const cl_uint SourceNumber,oclc_ef _PL_ Error);
			}
			Source;
			//OCLClip : Build from Binary Files
			const struct
			{
				//OCLClip : Program Build from Binary Files with 8-bit String Path - Only Once per Program Manager
				//£ªThe number of paths must be same as the number of devices associated with the context.
				//£ªNot found kernels will be just ignored.
				general(_PL_ T08_)(oclc_pm _PL_,oclc_co _PL_ Context,BYTE_08 _PL_ BuildOption,TEXT_08 _PL_ _PL_ BinaryPath,oclc_ef _PL_ Error);
				//OCLClip : Program Build from Binary Files with 16-bit String Path - Only Once per Program Manager
				//£ªThe number of paths must be same as the number of devices associated with the context.
				//£ªNot found kernels will be just ignored.
				general(_PL_ T16_)(oclc_pm _PL_,oclc_co _PL_ Context,BYTE_08 _PL_ BuildOption,TEXT_16 _PL_ _PL_ BinaryPath,oclc_ef _PL_ Error);
			}
			Binary;
			//OCLClip : Save Binary Files after Building
			const struct
			{
				//OCLClip : Save the Binary Files with 8-bit String Path - Only after Program Building
				//£ªThe number of paths must be same as the number of devices associated with the context.
				general(_PL_ T08_)(OCLC_PM _PL_,TEXT_08 _PL_ _PL_ BinaryPath,oclc_ef _PL_ Error);
				//OCLClip : Save the Binary Files with 16-bit String Path - Only after Program Building
				//£ªThe number of paths must be same as the number of devices associated with the context.
				general(_PL_ T16_)(OCLC_PM _PL_,TEXT_16 _PL_ _PL_ BinaryPath,oclc_ef _PL_ Error);
			}
			Save;
			//OCLClip : Get Build Log - Only after Program Building
			general(_PL_ Log_)(OCLC_PM _PL_ Program,FILE _PL_ Stream,oclc_ef _PL_ Error);
		}
		Build;
		//OCLClip : Program Manager Deletion
		general(_PL_ Delete_)(oclc_pm *_PL_);

		//OCLClip : Select Functions
		const struct
		{
			//OCLClip : Get a Kernel Object
			oclc_ko*(_PL_ Kernel_)(OCLC_PM _PL_,ADDRESS KernelSelect);
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
			address(_PL_ Size_)(OCLC_PI _PL_ Platform,const cl_platform_info Flag,oclc_ef _PL_ Error);
			//OCLClip : Get Information
			general(_PL_ What_)(OCLC_PI _PL_ Platform,const cl_platform_info Flag,general _PL_ Info,ADDRESS Size,oclc_ef _PL_ Error);
		}
		Info;
	}
	PI;

	//OCLClip : Device ID Functions
	const struct
	{
		//OCLClip : Information Functions
		const struct
		{
			//OCLClip : Get the Size of Information
			address(_PL_ Size_)(OCLC_DI _PL_ Device,const cl_device_info Flag,oclc_ef _PL_ Error);
			//OCLClip : Get Information
			general(_PL_ What_)(OCLC_DI _PL_ Device,const cl_device_info Flag,general _PL_ Info,ADDRESS Size,oclc_ef _PL_ Error);
		}
		Info;
	}
	DI;

	//OCLClip : Context Object Functions
	const struct
	{
		//OCLClip : Information Functions
		const struct
		{
			//OCLClip : Get the Size of Information
			address(_PL_ Size_)(OCLC_CO _PL_ Context,const cl_context_info Flag,oclc_ef _PL_ Error);
			//OCLClip : Get Information
			general(_PL_ What_)(OCLC_CO _PL_ Context,const cl_context_info Flag,general _PL_ Info,ADDRESS Size,oclc_ef _PL_ Error);
		}
		Info;
	}
	CO;

	//OCLClip : Queue Object Functions
	const struct
	{
		//OCLClip : Information Functions
		const struct
		{
			//OCLClip : Get the Size of Information
			address(_PL_ Size_)(OCLC_QO _PL_ Queue,const cl_command_queue_info Flag,oclc_ef _PL_ Error);
			//OCLClip : Get Information
			general(_PL_ What_)(OCLC_QO _PL_ Queue,const cl_command_queue_info Flag,general _PL_ Info,ADDRESS Size,oclc_ef _PL_ Error);
		}
		Info;

		//OCLClip : Asynchronous Memory Fill
		//£ªRequired (Value) size is (MemoryHolder)->Type->SizeType bytes.
		general(_PL_ Fill_)(oclc_qo _PL_ Queue,GENERAL _PL_ Value,OCLC_MH _PL_ MemoryHolder,OCLC_MP _PL_ FillLength,oclc_ef _PL_ Error);
		//OCLClip : Asynchronous Memory Copy
		general(_PL_ Copy_)(oclc_qo _PL_ Queue,OCLC_CF CopyMode,OCLC_MH _PL_ SourceHolder,OCLC_MH _PL_ TargetHolder,OCLC_MP _PL_ CopyLength,oclc_ef _PL_ Error);
		//OCLClip : Synchronization
		general(_PL_ Wait_)(oclc_qo _PL_ Queue,oclc_ef _PL_ Error);
	}
	QO;

	//OCLClip : Kernel Object Functions
	const struct
	{
		//OCLClip : Information Functions
		const struct
		{
			//OCLClip : Get the Size of Information
			address(_PL_ Size_)(OCLC_KO _PL_ Kernel,const cl_kernel_info Flag,oclc_ef _PL_ Error);
			//OCLClip : Get Information
			general(_PL_ What_)(OCLC_KO _PL_ Kernel,const cl_kernel_info Flag,general _PL_ Info,ADDRESS Size,oclc_ef _PL_ Error);
		}
		Info;

		//OCLClip : Argument Set Functions
		const struct
		{
			//OCLClip : Pass a Memory Object
			general(_PL_ G_)(oclc_ko _PL_,const cl_uint ArgIndex,OCLC_MO _PL_ MemoryObject,oclc_ef _PL_ Error);
			//OCLClip : Pass a Local Memory Size
			general(_PL_ L_)(oclc_ko _PL_,const cl_uint ArgIndex,ADDRESS LocalMemorySize,oclc_ef _PL_ Error);
			//OCLClip : Pass a Value
			general(_PL_ P_)(oclc_ko _PL_,const cl_uint ArgIndex,GENERAL _PL_ ValueAddress,ADDRESS ValueSize,oclc_ef _PL_ Error);
		}
		Arg;
	}
	KO;

	//OCLClip : Memory Object Functions
	const struct
	{
		//OCLClip : Information Functions
		const struct
		{
			//OCLClip : Get the Size of Information
			address(_PL_ Size_)(OCLC_MO _PL_ Memory,const cl_mem_info Flag,oclc_ef _PL_ Error);
			//OCLClip : Get Information
			general(_PL_ What_)(OCLC_MO _PL_ Memory,const cl_mem_info Flag,general _PL_ Info,ADDRESS Size,oclc_ef _PL_ Error);
		}
		Info;

		//OCLClip : Memory Object Creation Functions
		const struct
		{
			//OCLClip : Buffer Creation - Delete with "OCLC.MO.Delete_"
			oclc_mo*(_PL_ Buffer_)(oclc_co _PL_ Context,ADDRESS Size,oclc_ef _PL_ Error);
			//OCLClip : Sub-Buffer Creation - Delete with "OCLC.MO.Delete_"
			oclc_mo*(_PL_ Sub_)(oclc_mo _PL_ RootBuffer,ADDRESS Offset,ADDRESS Size,oclc_ef _PL_ Error);
		}
		Create;
		//OCLClip : Memory Object Deletion
		general(_PL_ Delete_)(oclc_mo *_PL_);
	}
	MO;

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
#define OCLC_MP_Length_(Pin,...) __dl{oclc_mp(_)={1,1,1,1};__VA_ARGS__;*(Pin)=(_);}lb__

			//OCLClip : Validity Check
			//£ªReturn value is 1 for any excess, otherwise 0.
			//¡¡i.e. for any Start+Amount>Shape or Amount==0
			_Bool(_PL_ Invalid_)(OCLC_MP _PL_ Start,OCLC_MP _PL_ Amount,OCLC_MP _PL_ Shape);
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
#define OCLC_MP_Offset_(Pin,...) __dl{oclc_mp(_)={0,0,0,0};__VA_ARGS__;*(Pin)=(_);}lb__

			//OCLClip : Validity Check
			//£ªReturn value is 1 for any excess, otherwise 0.
			//¡¡i.e. for any Start>Shape
			_Bool(_PL_ Invalid_)(OCLC_MP _PL_ Start,OCLC_MP _PL_ Shape);
		}
		Offset;

		//OCLClip : Total Number of Elements
		//¡¡i.e. N¡¿Z¡¿Y¡¿X
		address(_PL_ Total_)(OCLC_MP _PL_);

		//OCLClip : Empty Pin
		OCLC_MP _PL_ Zero;
	}
	MP;

	//OCLClip : Memory Holder Functions
	const struct
	{
		//OCLClip : Memory Holder Pin Assign
		oclc_mh(_PL_ Assign_)(general _PL_ Memory,OCLC_MP _PL_ Start,OCLC_MP _PL_ Shape,MEMC_DT _PL_ Type);
#define OCLC_MH_Assign_(Holder,Memory,Type,...) __dl{struct{OCLC_MP*Start;OCLC_MP*Shape;}(_)={NULL,NULL};__VA_ARGS__;*(Holder)=OCLC.MH.Assign_(Memory,_.Start,_.Shape,Type);}lb__
	}
	MH;
};
MemC_Type_Declare_(struct,oclcase,OCLCASE);
#define OCLC_Info_(Kind,Whose,It,Flag,Error) OCLC.Kind.Info.What_(Whose,Flag,It,sizeof(*(It)),Error)

//OCLClip : Library Case Object
extern OCLCASE OCLC;
//OCLClip : Indirect access to the library case object.
extern OCLCASE *OCLC_(general);
#endif
#endif
#endif
