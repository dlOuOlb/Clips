/*------------------------------------------------------------------*/
/*	PenClip is a simple stream I/O library.							*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2018.09.07	*/
/*------------------------------------------------------------------*/
/*	OpenCL Support													*/
/*	http://www.khronos.org/opencl/									*/
/*------------------------------------------------------------------*/

#ifndef _INC_PENCLIP
#define _INC_PENCLIP	//PenClip : Header Declaration

#include <uchar.h>
#include <wchar.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#ifdef _CL
#include <CL\opencl.h>
#endif
#include <memclip.h>

#if(MemC_Fold_(Definition:Types))
MemC_Type_Rename_(char,name_08,NAME_08)		//PenClip : 8-bit Character
static_assert((sizeof(name_08)==1),"sizeof(name_08) != 1");
MemC_Type_Rename_(wchar_t,name_16,NAME_16)	//PenClip : 16-bit Character
static_assert((sizeof(name_16)==2),"sizeof(name_16) != 2");
MemC_Type_Rename_(char32_t,name_32,NAME_32)	//PenClip : 32-bit Character
static_assert((sizeof(name_32)==4),"sizeof(name_32) != 4");

static_assert((sizeof(integer)<=sizeof(address)),"sizeof(integer) > sizeof(address)");
static_assert((sizeof(integer)<=sizeof(rsize_t)),"sizeof(integer) > sizeof(rsize_t)");
static_assert((sizeof(rsize_t)<=sizeof(address)),"sizeof(rsize_t) > sizeof(address)");

struct _penc_sc				//PenClip : String Container Structure
{
	ADDRESS Capacity;		//PenClip : Allowed Size in Bytes
	union _penc_up			//PenClip : Union of Pointers
	{
		name_08 _PL_ N08;	//PenClip : 8-bit Access
		name_16 _PL_ N16;	//PenClip : 16-bit Access
		name_32 _PL_ N32;	//PenClip : 32-bit Access
		GENERAL _PL_ X;		//PenClip : No Access
		ADDRESS A;			//PenClip : Address Value
	}
	String;					//PenClip : String Data
};
MemC_Type_Declare_(struct,penc_sc,PENC_SC);	//PenClip : String Container Structure

struct _penc_ss			//PenClip : Sub-Container Set Structure
{
	PENC_SC Root;		//PenClip : Root-Container
	ADDRESS Nums;		//PenClip : Number of Sub-Containers
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
	ADDRESS _PL_ SizeWorker;		//PenC_CL : Maximum Number of Work Items that can be specified in each Dimension of the Work Group 
	ADDRESS Workers;				//PenC_CL : Maximum Number of Work Items in a Work Group
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
#define PenC_Prefix_N08_N_(String) String		//PenClip : Narrow Multi-byte String Literal Prefix
#define PenC_Prefix_N16_W_(String) L##String	//PenClip : Wide String Literal Prefix
#define PenC_Prefix_N08_U_(String) u8##String	//PenClip : UTF-8 Encoded String Literal Prefix
#define PenC_Prefix_N16_U_(String) u##String	//PenClip : UTF-16 Encoded String Literal Prefix
#define PenC_Prefix_N32_U_(String) U##String	//PenClip : UTF-32 Encoded String Literal Prefix

#define PenC_Setter_N08_(Buffer,Value,Count) (name_08*)memset(Buffer,Value,Count)	//PenClip : 8-bit Character Setting
#define PenC_Setter_N16_(Buffer,Value,Count) (name_16*)wmemset(Buffer,Value,Count)	//PenClip : 16-bit Character Setting

#define PenC_Finder_N08_(Buffer,Value,Count) (name_08*)memchr(Buffer,Value,Count)	//PenClip : 8-bit Character Finding
#define PenC_Finder_N16_(Buffer,Value,Count) (name_16*)wmemchr(Buffer,Value,Count)	//PenClip : 16-bit Character Finding

#define PenC_Buffer_Format_N08_(Mode,Buffer,Capacity,...) ((Mode)?(sscanf_s(Buffer,__VA_ARGS__)):(sprintf_s(Buffer,Capacity,__VA_ARGS__)))		//PenClip : 8-bit Buffer Print (Mode 0) or Scan (Mode 1)
#define PenC_Buffer_Format_N16_(Mode,Buffer,Capacity,...) ((Mode)?(swscanf_s(Buffer,__VA_ARGS__)):(swprintf_s(Buffer,Capacity,__VA_ARGS__)))	//PenClip : 16-bit Buffer Print (Mode 0) or Scan (Mode 1)

#define PenC_Stream_Format_N08_(Mode,Stream,...) ((Mode)?((Stream)?(fscanf_s(Stream,__VA_ARGS__)):(scanf_s(__VA_ARGS__))):((Stream)?(fprintf_s(Stream,__VA_ARGS__)):(printf_s(__VA_ARGS__))))		//PenClip : 8-bit Stream Print (Mode 0) or Scan (Mode 1)
#define PenC_Stream_Format_N16_(Mode,Stream,...) ((Mode)?((Stream)?(fwscanf_s(Stream,__VA_ARGS__)):(wscanf_s(__VA_ARGS__))):((Stream)?(fwprintf_s(Stream,__VA_ARGS__)):(wprintf_s(__VA_ARGS__))))	//PenClip : 16-bit Stream Print (Mode 0) or Scan (Mode 1)

#define PenC_Stream_Buffer_N08_(Mode,Stream,Buffer,Capacity) ((Mode)?((Stream)?((address)fgets(Buffer,(integer)(Capacity),Stream)):((address)gets_s(Buffer,(rsize_t)(Capacity)))):((Stream)?((address)fputs(Buffer,Stream)):((address)puts(Buffer))))	//PenClip : 8-bit Buffer to Stream Print (Mode 0) or Stream to Buffer Scan (Mode 1)
#define PenC_Stream_Buffer_N16_(Mode,Stream,Buffer,Capacity) ((Mode)?((Stream)?((address)fgetws(Buffer,(integer)(Capacity),Stream)):((address)_getws_s(Buffer,Capacity))):((Stream)?((address)fputws(Buffer,Stream)):((address)_putws(Buffer))))		//PenClip : 16-bit Buffer to Stream Print (Mode 0) or Stream to Buffer Scan (Mode 1)
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
#if(MemC_Fold_(Part:File))
//PenClip : File Open
FILE *PenC_File_Opener_(NAME_08 _PL_ FileName,NAME_08 _PL_ OpeningMode);
//PenClip : File Close
//＊Return value is 0 for success, an error code for failure.
integer PenC_File_Closer_(FILE *_PL_ FilePointer);
//PenClip : File Pointer Usage in Local Scope - Handle with "MemC_Failed_"
#define PenC_File_Region_(File,Name,Mode,Error) for(FILE *(_Temp)=FULL,_PL_ (File)=PenC_File_Opener_(Name,Mode);_Temp;(_Temp)=NULL,(Error)=PenC_File_Closer_((FILE**)&(File)))if(File)
//PenClip : File Write
#define PenC_File_Writer_(FilePointer,Buffer,Elements,type) fwrite(Buffer,sizeof(type),Elements,FilePointer)
//PenClip : File Read
#define PenC_File_Reader_(FilePointer,Buffer,Elements,type) fread_s(Buffer,(Elements)*sizeof(type),sizeof(type),Elements,FilePointer)
//PenClip : Step Forward from Current Location
#define PenC_File_Jumper_(FilePointer,Elements,type) fseek(FilePointer,(Elements)*sizeof(type),SEEK_CUR)
//PenClip : Step Backward from Current Location
#define PenC_File_Backer_(FilePointer,Elements,type) fseek(FilePointer,0-((Elements)*sizeof(type)),SEEK_CUR)
//PenClip : Pointer Restart
#define PenC_File_Rewind_(FilePointer) rewind(FilePointer)
//PenClip : Current Location from Start
#define PenC_File_Teller_(FilePointer) ftell(FilePointer)
//PenClip : Stream Flush
#define PenC_File_Washer_(FilePointer) fflush(FilePointer)
//PenClip : End of File
#define PenC_File_Finish_(FilePointer) feof(FilePointer)
//PenClip : File Remove
#define PenC_File_Remove_(FileName) remove(FileName)
//PenClip : File Rename
#define PenC_File_Rename_(FileNameOld,FileNameNew) rename(FileNameOld,FileNameNew)
//PenClip : File's Byte Size
address PenC_File_Length_(NAME_08 _PL_ FileName);

//PenClip : 1D Array Data Read
//＊Return value is 1 for success, 0 for failure.
integer _PenC_Reader_1D_(general _PL_ Line,NAME_08 _PL_ FileName,ADDRESS TypeSize,ADDRESS Count);
#define PenC_Reader_1D_(Line,FileName,Elements,type) _PenC_Reader_1D_(Line,FileName,sizeof(type),Elements)
//PenClip : 1D Array Data Write
//＊Return value is 1 for success, 0 for failure.
integer _PenC_Writer_1D_(GENERAL _PL_ Line,NAME_08 _PL_ FileName,ADDRESS TypeSize,ADDRESS Count);
#define PenC_Writer_1D_(Line,FileName,Elements,type) _PenC_Writer_1D_(Line,FileName,sizeof(type),Elements)
#endif
#if(MemC_Fold_(Part:Pipe))
//PenClip : Pipe Open
#define PenC_Pipe_Opener_(Command,Mode) _popen(Command,Mode)
//PenClip : Pipe Close
integer PenC_Pipe_Closer_(FILE *_PL_ Pipe);
//PenClip : Pipe Pointer Usage in Local Scope - Handle with "MemC_Failed_"
#define PenC_Pipe_Region_(Pipe,Command,Mode,Return) for(FILE *(_Temp)=FULL,_PL_ (Pipe)=PenC_Pipe_Opener_(Command,Mode);_Temp;(_Temp)=NULL,(Return)=PenC_Pipe_Closer_((FILE**)&(Pipe)))if(Pipe)
//PenClip : Execute a command.
integer PenC_Pipe_Action_(NAME_08 _PL_ Command,FILE _PL_ MsgStream);
#endif
#if(MemC_Fold_(Part:String))
//PenClip : Narrow Multi-byte to Wide String Conversion
errno_t PenC_String_Caster_N08_N16_(NAME_08 *SourceString,name_16 _PL_ TargetString,ADDRESS SourceCapacity,ADDRESS TargetCapacity);
//PenClip : Wide to Narrow Multi-byte String Conversion
errno_t PenC_String_Caster_N16_N08_(NAME_16 *SourceString,name_08 _PL_ TargetString,ADDRESS SourceCapacity,ADDRESS TargetCapacity);

//PenClip : 8-bit String Length
#define PenC_String_Length_N08_(String,Capacity) strnlen_s(String,Capacity)
//PenClip : 16-bit String Length
#define PenC_String_Length_N16_(String,Capacity) wcsnlen_s(String,Capacity)

//PenClip : 8-bit Sub-String Finding
#define PenC_String_Finder_N08_(String,SubString) (name_08*)strstr(String,SubString)
//PenClip : 16-bit Sub-String Finding
#define PenC_String_Finder_N16_(String,SubString) (name_16*)wcsstr(String,SubString)

//PenClip : 8-bit String Concatenation
#define PenC_String_Concat_N08_(Buffer,Source,Capacity) strcat_s(Buffer,Capacity,Source)
//PenClip : 16-bit String Concatenation
#define PenC_String_Concat_N16_(Buffer,Source,Capacity) wcscat_s(Buffer,Capacity,Source)

//PenClip : 8-bit String Copy
#define PenC_String_Copier_N08_(Buffer,Source,Capacity) strcpy_s(Buffer,Capacity,Source)
//PenClip : 16-bit String Copy
#define PenC_String_Copier_N16_(Buffer,Source,Capacity) wcscpy_s(Buffer,Capacity,Source)
#endif
#if(MemC_Fold_(Part:Name))
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
#endif

#if(MemC_Fold_(Declaration:PenClip Managed Functions))
#if(MemC_Fold_(Part:PenC_SC))
//PenClip : String Container Static Definition
#define PenC_SC_Define_(IString) {.Capacity=sizeof(IString),.String.X=(IString)}
//PenClip : String Container Local Variable Assignment without Heap Allocation
penc_sc _PenC_SC_Assign_(GENERAL _PL_ String,ADDRESS Capacity);
#define PenC_SC_Assign_(Buffer) _PenC_SC_Assign_(Buffer,sizeof(Buffer))

//PenClip : String Container Memory Allocation - Deallocate with "PenC_SC_Delete_"
penc_sc *PenC_SC_Create_(ADDRESS CapacityBytes);
//PenClip : Sub-Container Memory Allocation from a Root-Container - Deallocate with "PenC_SC_Delete_"
penc_sc *PenC_SC_Create_Sub_(PENC_SC _PL_ RootContainer,ADDRESS OffsetBytes,ADDRESS LengthBytes);
//PenClip : String Container Memory Deallocation
general PenC_SC_Delete_(penc_sc *_PL_ StringContainer);

//PenClip : String Container Data Reset
#define PenC_SC_Init_(SC) MemC_Clear_1D_((SC).String.N08,(SC).Capacity,name_08)

//PenClip : String Container multi-byte to 2-byte Conversion
#define PenC_SC_Caster_N08_N16_(Source,Target) PenC_String_Caster_N08_N16_((Source).String.N08,(Target).String.N16,(Source).Capacity,(Target).Capacity>>1)
//PenClip : String Container 2-byte to multi-byte Conversion
#define PenC_SC_Caster_N16_N08_(Source,Target) PenC_String_Caster_N16_N08_((Source).String.N16,(Target).String.N08,(Source).Capacity>>1,(Target).Capacity)

//PenClip : String Container 8-bit Length
#define PenC_SC_Length_N08_(SC) PenC_String_Length_N08_((SC).String.N08,(SC).Capacity)
//PenClip : String Container 16-bit Length
#define PenC_SC_Length_N16_(SC) PenC_String_Length_N16_((SC).String.N16,(SC).Capacity>>1)

//PenClip : String Container 8-bit Copy
#define PenC_SC_Copier_N08_(Target,Source) PenC_String_Copier_N08_((Target).String.N08,(Source).String.N08,(Target).Capacity)
//PenClip : String Container 16-bit Copy
#define PenC_SC_Copier_N16_(Target,Source) PenC_String_Copier_N16_((Target).String.N16,(Source).String.N16,(Target).Capacity>>1)

//PenClip : String Container 8-bit Concatenation
#define PenC_SC_Concat_N08_(Target,Source) PenC_String_Concat_N08_((Target).String.N08,(Source).String.N08,(Target).Capacity)
//PenClip : String Container 16-bit Concatenation
#define PenC_SC_Concat_N16_(Target,Source) PenC_String_Concat_N16_((Target).String.N16,(Source).String.N16,(Target).Capacity>>1)

//PenClip : 8-bit String Container Print (Mode 0) or Scan (Mode 1)
#define PenC_SC_Format_N08_(Mode,SC,...) PenC_Buffer_Format_N08_(Mode,(SC).String.N08,(SC).Capacity,__VA_ARGS__)
//PenClip : 16-bit String Container Print (Mode 0) or Scan (Mode 1)
#define PenC_SC_Format_N16_(Mode,SC,...) PenC_Buffer_Format_N16_(Mode,(SC).String.N16,(SC).Capacity>>1,__VA_ARGS__)

//PenClip : 8-bit String Container to Stream Print (Mode 0) or Stream to String Container Scan (Mode 1)
#define PenC_SC_Stream_N08_(Mode,SC,Stream) PenC_Stream_Buffer_N08_(Mode,Stream,(SC).String.N08,(SC).Capacity)
//PenClip : 16-bit String Container to Stream Print (Mode 0) or Stream to String Container Scan (Mode 1)
#define PenC_SC_Stream_N16_(Mode,SC,Stream) PenC_Stream_Buffer_N16_(Mode,Stream,(SC).String.N16,(SC).Capacity>>1)
#endif
#if(MemC_Fold_(Part:PenC_SS))
//PenClip : Sub-Container Set Memory Allocation - Deallocate with "PenC_SS_Delete_"
penc_ss *PenC_SS_Create_(ADDRESS SubBufferNumbers,ADDRESS TotalCapacityBytes);
//PenClip : Sub-Container Set Memory Deallocation
general PenC_SS_Delete_(penc_ss *_PL_ StringContainerSet);
//PenClip : Sub-Container Assign from the Root-Container
//＊Return value is 1 for success, 0 for failure.
integer PenC_SS_Assign_(PENC_SS _PL_ SS,ADDRESS Index,ADDRESS Offset,ADDRESS Length);
#endif
#endif

#if(MemC_Fold_(Declaration:OpenCL Functions))
#ifdef __OPENCL_H
//PenC_CL : Select Platform and Device with Console Interface
penc_eu PenC_CL_Identify_(cl_uint _PL_ PlatformSelect,cl_uint _PL_ DeviceSelect,FILE _PL_ InputMessageStream,FILE _PL_ OutputMessageStream);
//PenC_CL : Program Build from Source Files to an Object File
penc_eu PenC_CL_Binary_(cl_command_queue const Queue,NAME_08 _PL_ ObjectFileName,NAME_08 _PL_ _PL_ SourceFileNameSet,NAME_08 _PL_ BuildOption,ADDRESS SourceFilesNumber,FILE _PL_ MsgStream);

//PenC_CL : Program Resource Memory Allocation - Deallocate with "PenC_Delete_CL_"
penc_cl *PenC_CL_Create_(cl_command_queue const Queue,NAME_08 _PL_ ObjectFileName,NAME_08 _PL_ _PL_ IndicatorSet,NAME_08 _PL_ BuildOption,const cl_uint KernelsNumber,penc_eu _PL_ Error,FILE _PL_ MsgStream);
//PenC_CL : Program Resource Memory Deallocation
general PenC_CL_Delete_(penc_cl *_PL_ PenCL);
#endif
#endif
#endif
