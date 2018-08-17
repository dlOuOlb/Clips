/*------------------------------------------------------------------*/
/*	PenClip is a file I/O header.									*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2018.08.17	*/
/*------------------------------------------------------------------*/
/*	OpenCL Support													*/
/*	http://www.khronos.org/opencl/									*/
/*------------------------------------------------------------------*/

#ifndef _INC_PENCLIP
#define _INC_PENCLIP	//PenClip : Header Declaration

#include <uchar.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#ifdef _CL
#include <CL\opencl.h>
#endif
#include <memclip.h>

#if(MemC_Fold_(Definition:Types))

MemC_Type_Rename_(char,name_08,NAME_08)		//PenClip : 8-bit Character
MemC_Type_Rename_(char16_t,name_16,NAME_16)	//PenClip : 16-bit Character
MemC_Type_Rename_(char32_t,name_32,NAME_32)	//PenClip : 32-bit Character

struct _penc_sc				//PenClip : String Container Structure
{
	ADDRESS Capacity;	//PenClip : Allowed Size in Bytes
	union _penc_up			//PenClip : Union of Pointers
	{
		name_08 _PL_ N08;	//PenClip : 8-bit Access
		name_16 _PL_ N16;	//PenClip : 16-bit Access
		name_32 _PL_ N32;	//PenClip : 32-bit Access
		GENERAL _PL_ X;	//PenClip : No Access
	}
	String;					//PenClip : String Data
};
MemC_Type_Declare_(struct,penc_sc,PENC_SC);	//PenClip : String Container Structure

struct _penc_ss			//PenClip : Sub-Container Set Structure
{
	PENC_SC Root;		//PenClip : Root-Container
	ADDRESS Nums;	//PenClip : Number of Sub-Containers
	PENC_SC _PL_ Part;	//PenClip : Sub-Container Set
};
MemC_Type_Declare_(struct,penc_ss,PENC_SS);	//PenClip : Sub-Container Set Structure

#ifdef __OPENCL_H
struct _penc_cl						//PenC_CL : OpenCL Program Resource Structure
{
	cl_device_id const Device;		//PenC_CL : Device ID
	cl_context const Context;		//PenC_CL : Context
	cl_command_queue const Queue;	//PenC_CL : Command Queue
	cl_program const Program;		//PenC_CL : Internal Program
	cl_kernel _PL_ SetKernel;		//PenC_CL : Internal Kernel Set
	ADDRESS _PL_ SizeWorker;	//PenC_CL : Maximum Number of Work Items that can be specified in each Dimension of the Work Group 
	ADDRESS Workers;			//PenC_CL : Maximum Number of Work Items in a Work Group
	const cl_ulong SizeLocal;		//PenC_CL : Size of Local Memory Arena in Bytes
	const cl_uint Cores;			//PenC_CL : The Number of Parallel Compute Cores
	const cl_uint Dimensions;		//PenC_CL : Maximum Dimensions of Global and Local Work Items
	const cl_uint Kernels;			//PenC_CL : The Number of Kernels
};
MemC_Type_Declare_(struct,penc_cl,PENC_CL);	//PenC_CL : OpenCL Program Resource Structure

union _penc_eu		//PenC_CL : OpenCL Error Union
{
	enum _penc_ee	//PenC_CL : OpenCL Error Enumeration
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
	E;				//PenC_CL : Access as Enumeration
	cl_int I;		//PenC_CL : Access as Integer
};
MemC_Type_Declare_(union,penc_eu,PENC_EU);	//PenC_CL : OpenCL Error Union
static_assert((sizeof(enum _penc_ee)==sizeof(cl_int)),"sizeof(enum) != sizeof(integer)");
#endif
#endif

#if(MemC_Fold_(Definition:Macros))
#define PenC_File_Opener_(FilePointer,FileName,Mode) fopen_s(&(FilePointer),FileName,Mode)												//PenClip : File Open
#define PenC_File_Closer_(FilePointer) do{if(FilePointer){if(!fclose(FilePointer)){(FilePointer)=NULL;}}}while(0)						//PenClip : File Close
#define PenC_File_Remove_(FileName) remove(FileName)																					//PenClip : File Delete
#define PenC_File_Rename_(FileNameOld,FileNameNew) rename(FileNameOld,FileNameNew)														//PenClip : File Rename
#define PenC_File_Writer_(FilePointer,Buffer,Elements,type) fwrite(Buffer,sizeof(type),Elements,FilePointer)							//PenClip : File Write
#define PenC_File_Reader_(FilePointer,Buffer,Elements,type) fread_s(Buffer,(Elements)*sizeof(type),sizeof(type),Elements,FilePointer)	//PenClip : File Read
#define PenC_File_Jumper_(FilePointer,Elements,type) fseek(FilePointer,(Elements)*sizeof(type),SEEK_CUR)								//PenClip : Step Forward from Current Location
#define PenC_File_Backer_(FilePointer,Elements,type) fseek(FilePointer,0-((Elements)*sizeof(type)),SEEK_CUR)							//PenClip : Step Backward from Current Location
#define PenC_File_Rewind_(FilePointer) rewind(FilePointer)	//PenClip : Pointer Restart
#define PenC_File_Teller_(FilePointer) ftell(FilePointer)	//PenClip : Current Location from Start
#define PenC_File_Washer_(FilePointer) fflush(FilePointer)	//PenClip : Stream Flush
#define PenC_File_Finish_(FilePointer) feof(FilePointer)		//PenClip : End of File

#define PenC_Setter_Byte_(Buffer,Value,Length) (name_08*)memset(Buffer,Value,Length)	//PenClip : Buffer Byte Set
#define PenC_Finder_Byte_(Buffer,Value,Length) (name_08*)memchr(Buffer,Value,Length)	//PenClip : Buffer Byte Find

#define PenC_String_Length_(String,Capacity) strnlen_s(String,Capacity)					//PenClip : String Length
#define PenC_String_Finder_(Sentence,Word) (name_08*)strstr(Sentence,Word)				//PenClip : Sentence Word Find
#define PenC_String_Concat_(Buffer,Source,Capacity) strcat_s(Buffer,Capacity,Source)	//PenClip : String Concatenation
#define PenC_String_Copier_(Buffer,Source,Capacity) strcpy_s(Buffer,Capacity,Source)	//PenClip : String Copy

#define PenC_Reader_1D_(Line,FileName,Elements,type) _PenC_Reader_1D_(Line,FileName,sizeof(type),Elements)	//PenClip : 1D Array Data Read
#define PenC_Writer_1D_(Line,FileName,Elements,type) _PenC_Writer_1D_(Line,FileName,sizeof(type),Elements)	//PenClip : 1D Array Data Write

#define PenC_Pipe_Opener_(ProgramPointer,Command,Mode) do{(ProgramPointer)=_popen(Command,Mode);}while(0)									//PenClip : Program Open
#define PenC_Pipe_Closer_(ProgramPointer,Return) do{if(ProgramPointer){(Return)=_pclose(ProgramPointer);(ProgramPointer)=NULL;}}while(0)	//PenClip : Program Close

#define PenC_Time_Clocks_ clock()						//PenClip : Current Clocks
#define PenC_Time_Elapse_(Start) (PenC_Time_Clocks_-(Start))	//PenClip : Clock Measure from Start

#define PenC_Prefix_N08_(String) u8##String	//PenClip : 8-bit String Literal Prefix
#define PenC_Prefix_N16_(String) u##String	//PenClip : 16-bit String Literal Prefix
#define PenC_Prefix_N32_(String) U##String	//PenClip : 32-bit String Literal Prefix

#define PenC_String_Writer_ printf_s			//PenClip : Standard Stream Print
#define PenC_String_Reader_ scanf_s				//PenClip : Standard Stream Scan
#define PenC_String_Writer_File_ fprintf_s		//PenClip : File Stream Print
#define PenC_String_Reader_File_ fscanf_s		//PenClip : File Stream Scan
#define PenC_String_Writer_Stream_ fputs		//PenClip : Stream Print
#define PenC_String_Reader_Stream_ fgets		//PenClip : Stream Scan
#define PenC_String_Writer_Buffer_ sprintf_s	//PenClip : Buffer Stream Print
#define PenC_String_Reader_Buffer_ sscanf_s		//PenClip : Buffer Stream Scan

#define PenC_SC_Define_(IString) {.Capacity=sizeof(IString),.String.X=(IString)}	//PenClip : String Container Static Definition
#endif

#if(MemC_Fold_(Declaration:Global Constants))
//PenClip : Library Version
extern NAME_08 _PL_ PenClip;

//PenClip : File I/O Option
//＊[0] : "rb" (Read Binary)
//　[1] : "wb" (Write Binary)
//　[2] : "rt" (Read Text)
//　[3] : "wt" (Write Text)
extern NAME_08 _PL_ _PL_ PenCOpen;
#endif

#if(MemC_Fold_(Declaration:I/O Functions))
//PenClip : File Byte Size
address PenC_File_Length_(NAME_08 _PL_ FileName);

//PenClip : Execute a command.
integer PenC_Pipe_Action_(NAME_08 _PL_ Command);

//PenClip : Print current date.
//＊Required buffer size is 10 bytes for ( yyyy.mm.dd ).
general PenC_Time_Record_Date_(name_08 _PL_ Buffer);
//PenClip : Print current time.
//＊Requried buffer size is 8 bytes for ( hh:mm:ss ).
general PenC_Time_Record_Hour_(name_08 _PL_ Buffer);

//PenClip : Print an integer in decimal form.
//＊Required buffer size is count bytes.
general PenC_Name_Deci_(name_08 _PL_ Buffer,ADDRESS Number,ADDRESS Count);
//PenClip : Print an integer in hexadecimal form.
//＊Required buffer size is count bytes.
general PenC_Name_Hexa_(name_08 _PL_ Buffer,ADDRESS Number,ADDRESS Count);

//PenClip : Find the last dot character.
//＊Return value is offset.
address PenC_Name_Extend_(NAME_08 _PL_ Buffer,ADDRESS Length);
#endif

#if(MemC_Fold_(Declaration:PenClip Managed Functions))
//PenClip : String Container Memory Allocation - Deallocate with "PenC_SC_Delete_"
penc_sc *PenC_SC_Create_(ADDRESS CapacityBytes);
//PenClip : Sub-Container Memory Allocation from a Root-Container - Deallocate with "PenC_SC_Delete_"
penc_sc *PenC_SC_Create_Sub_(PENC_SC _PL_ RootContainer,ADDRESS OffsetBytes,ADDRESS LengthBytes);
//PenClip : String Container Memory Deallocation
general PenC_SC_Delete_(penc_sc *_PL_ StringContainer);

//PenClip : String Container Data Reset
//＊Return value is 1 for success, 0 for failure.
integer PenC_SC_Init_(PENC_SC _PL_ StringContainer);

//PenClip : String Container Null Character Finding
//＊Return value is the first found null character's location for success, or the capacity for failure.
address PenC_SC_Length_N08_(PENC_SC _PL_ StringContainer);
//PenClip : String Container Data Copy
//＊Return value is 1 for success, 0 for failure.
integer PenC_SC_Copy_N08_(PENC_SC _PL_ TargetContainer,PENC_SC _PL_ SourceContainer);
//PenClip : String Container Data Concatenation
//＊Return value is 1 for success, 0 for failure.
integer PenC_SC_Concat_N08_(PENC_SC _PL_ TargetContainer,PENC_SC _PL_ SourceContainer);

//PenClip : Sub-Container Set Memory Allocation - Deallocate with "PenC_SS_Delete_"
penc_ss *PenC_SS_Create_(ADDRESS SubBufferNumbers,ADDRESS TotalCapacityBytes);
//PenClip : Sub-Container Set Memory Deallocation
general PenC_SS_Delete_(penc_ss *_PL_ StringContainerSet);
//PenClip : Sub-Container Assign from the Root-Container
//＊Return value is 1 for success, 0 for failure.
integer PenC_SS_Assign_(PENC_SS _PL_ SS,ADDRESS Index,ADDRESS Offset,ADDRESS Length);
#endif

#if(MemC_Fold_(Declaration:OpenCL Functions))
#ifdef __OPENCL_H
//PenC_CL : Select Platform and Device with Console Interface
penc_eu PenC_CL_Identify_(cl_uint _PL_ PlatformSelect,cl_uint _PL_ DeviceSelect);
//PenC_CL : Program Build from Source Files to an Object File
penc_eu PenC_CL_Binary_(cl_command_queue const Queue,NAME_08 _PL_ ObjectFileName,NAME_08 _PL_ _PL_ SourceFileNameSet,NAME_08 _PL_ BuildOption,ADDRESS SourceFilesNumber);

//PenC_CL : Program Resource Memory Allocation - Deallocate with "PenC_Delete_CL_"
penc_cl *PenC_CL_Create_(cl_command_queue const Queue,NAME_08 _PL_ ObjectFileName,NAME_08 _PL_ _PL_ IndicatorSet,NAME_08 _PL_ BuildOption,const cl_uint KernelsNumber,penc_eu _PL_ Error);
//PenC_CL : Program Resource Memory Deallocation
general PenC_CL_Delete_(penc_cl *_PL_ PenCL);
#endif
#endif

#if(MemC_Fold_(Declaration:Renamed Functions))
//PenClip : See "PenC_Reader_1D_"
integer _PenC_Reader_1D_(general _PL_ Line,NAME_08 _PL_ FileName,ADDRESS TypeSize,ADDRESS Count);
//PenClip : See "PenC_Writer_1D_"
integer _PenC_Writer_1D_(GENERAL _PL_ Line,NAME_08 _PL_ FileName,ADDRESS TypeSize,ADDRESS Count);
#endif
#endif
