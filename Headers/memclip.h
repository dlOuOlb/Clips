/*------------------------------------------------------------------*/
/*	MemClip provides some memory allocating functions.				*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2018.07.31	*/
/*------------------------------------------------------------------*/
/*	OpenCL Support													*/
/*	http://www.khronos.org/opencl/									*/
/*------------------------------------------------------------------*/

#ifndef _INC_MEMCLIP
#define _INC_MEMCLIP	//MemClip : Header Declaration

#include <malloc.h>
#include <memory.h>
#ifdef _CL
#include <CL\opencl.h>
#endif

#define MemC_Fold_(Comment) (1)	//MemClip : Code Folding with #if and #endif Pre-processor.
#if(MemC_Fold_(Preprocessing))
#ifdef _WIN64
#define MemC_64_	//MemClip : 64-bit Memory Address
#endif

#ifdef NULL
static_assert(((size_t)(NULL))==((size_t)(0)),"NULL != 0");
#else
#define NULL ((void*)(0))	//MemClip : Null Pointer Definition
#endif

#ifdef FULL
static_assert(((size_t)(FULL))==(~((size_t)(0))),"FULL != ~0");
#else
#define FULL ((void*)(~((size_t)(0))))	//MemClip : Full Pointer Definition
#endif

static_assert((sizeof(char)==1),"sizeof(char) != 1");
static_assert((sizeof(void*)==sizeof(size_t)),"sizeof(void*) != sizeof(size_t)");
#ifdef __OPENCL_H
static_assert((sizeof(cl_int)<=sizeof(size_t)),"sizeof(cl_int) > sizeof(size_t)");
#endif

#ifdef _PL_
#error The macro "_PL_" is already defined.
#else
#define _PL_ *const	//MemClip : Pointer Lock Definition
#endif

#ifdef _R_
#error The macro "_R_" is already defined.
#else
#define _R_ __restrict	//MemClip : Exclusive memory Access
#endif

#ifdef Acs_
#error The macro "Acs_" is already defined.
#else
#define Acs_(type,Data) (*((type*)(&(Data))))	//MemClip : Indirect Memory Access
#endif

#define MemC_Type_Rename_(oldtype,newtype,NEWTYPE) typedef oldtype newtype;typedef const oldtype NEWTYPE;	//MemClip : Macro for Type Renaming
#define MemC_Type_Declare_(spec,type,TYPE) typedef spec _##type type;typedef const spec _##type TYPE;		//MemClip : Macro for Type Declaration
#endif

#if(MemC_Fold_(Definition:Types))
struct _memc_dt					//MemClip : Data Type Structure
{
	const void _PL_ Scope;		//MemClip : Type Scope
	const size_t Index;			//MemClip : Index in Scope
	const size_t Flag;			//MemClip : Property Flag
	const size_t SizeType;		//MemClip : Type's Byte Size
	const size_t SizeName;		//MemClip : Name's Byte Size
	const char _PL_ Name;		//MemClip : Type Name
	const void _PL_ Link;		//MemClip : External Link
	const void _PL_ Meta;		//MemClip : Meta Data
};
MemC_Type_Declare_(struct,memc_dt,MEMC_DT);	//MemClip : Data Type Structure

struct _memc_ms			//MemClip : Memory Slot Structure
{
	const void _PL_ ID;	//MemClip : Identification
	MEMC_DT _PL_ Type;	//MemClip : Data Type
	const size_t Nums;	//MemClip : Number of Slots
	union _memc_vp		//MemClip : Variable Pointer Union
	{
		void *_PL_ P;	//MemClip : Access as Pointer Array
		size_t _PL_ V;	//MemClip : Access as Numeric Array
	}
	Slot;				//MemClip : Slot Access
};
MemC_Type_Declare_(struct,memc_ms,MEMC_MS);	//MemClip : Memory Slot Structure

struct _memc_mc					//MemClip : Memory Container Structure
{
	const void _PL_ ID;			//MemClip : Identification
	MEMC_DT _PL_ Type;			//MemClip : Data Type
	const size_t Unit;			//MemClip : Type Size
	const size_t Dims;			//MemClip : Dimension (N)
	const size_t Lng1D;			//MemClip : Total Number of Elements
	const size_t _PL_ LngND;	//MemClip : Data Shape
	void _PL_ Acs1D;			//MemClip : 1-Dimensional Data Access
	const void _PL_ AcsND;		//MemClip : N-Dimensional Data Access
};
MemC_Type_Declare_(struct,memc_mc,MEMC_MC);	//MemClip : Memory Container Structure

enum _memc_df				//MemClip : Memory Domain Flag Enumeration
{
	MemCDomainHost=0x48,	//MemClip : Memory in Host Domain
	MemCDomainDevice=0x44	//MemClip : Memory in Device Domain
};
MemC_Type_Declare_(enum,memc_df,MEMC_DF);	//MemClip : Memory Domain Flag Enumeration
static_assert(sizeof(memc_df)<=sizeof(size_t),"sizeof(enum) > sizeof(size_t)");

struct _memc_vc					//MemClip : Virtual Container Structure
{
	const void _PL_ ID;			//MemClip : Identification
	MEMC_DT _PL_ Type;			//MemClip : Data Type
	const size_t Unit;			//MemClip : Type Size
	const size_t Dims;			//MemClip : Dimensions (N)
	const size_t Lng1D;			//MemClip : Total Number of Elements
	const size_t _PL_ LngND;	//MemClip : Data Shape
	const union _memc_ue		//MemClip : Union of Enumeration
	{
		MEMC_DF E;				//MemClip : Access as Enum Type
		const size_t N;			//MemClip : Access as Non-Enum Type
	}
	Domain;						//MemClip : Memory Domain Flag
	const void _PL_ Hidden;		//MemClip : Hidden Linkage
};
MemC_Type_Declare_(struct,memc_vc,MEMC_VC);	//MemClip : Virtual Container Structure

#ifdef __OPENCL_H
struct _devi_qc						//MemC_CL : Queue Container Structure
{
	const cl_platform_id Platform;	//MemC_CL : Platform ID
	const cl_device_id Device;		//MemC_CL : Device ID
	const cl_context Context;		//MemC_CL : Context
	const cl_command_queue Queue;	//MemC_CL : Command Queue
};
MemC_Type_Declare_(struct,devi_qc,DEVI_QC);	//MemC_CL : Queue Container Structure

struct _devi_bc				//MemC_CL : Buffer Container Structure
{
	const void _PL_ ID;		//MemC_CL : Identification
	MEMC_DT _PL_ Type;		//MemC_CL : Data Type
	const size_t Unit;		//MemC_CL : Type Size
	const size_t LngT;		//MemC_CL : Total Length
	const cl_mem BufT;		//MemC_CL : Main Buffer
	const size_t Nums;		//MemC_CL : Number of Sub-Buffers
	const size_t _PL_ LngS;	//MemC_CL : Lengths of Sub-Buffers
	const cl_mem _PL_ BufS;	//MemC_CL : Sub-Buffer Address Array
};
MemC_Type_Declare_(struct,devi_bc,DEVI_BC);	//MemC_CL : Buffer Container Structure

enum _devi_df					//MemC_CL : Device Memory Domain Flag Enumeration
{
	DeviDomainConstant=0x43,	//MemC_CL : Constant Memory
	DeviDomainGlobal=0x47,		//MemC_CL : Global Memory
	DeviDomainLocal=0x4C,		//MemC_CL : Local Memory
	DeviDomainPrivate=0x50		//MemC_CL : Private Memory
};
MemC_Type_Declare_(enum,devi_df,DEVI_DF);	//MemC_CL : Device Memory Domain Flag Enumeration
static_assert(sizeof(devi_df)<=sizeof(size_t),"sizeof(enum) > sizeof(size_t)");

struct _devi_km					//MemC_CL : Kernel Manager Structure
{
	const void _PL_ ID;			//MemC_CL : Identification
	const size_t KArgs;			//MemC_CL : The Number of Kernel Arguments
	const size_t WDims;			//MemC_CL : Work Dimensions
	const cl_kernel Kernel;		//MemC_CL : Linked Kernel
	DEVI_DF _PL_ ArgFlag;		//MemC_CL : Argument Type Indicator
	const size_t _PL_ ArgSize;	//MemC_CL : Argument Byte Size Set
	union _memc_cp				//MemC_CL : Constant Pointer Union
	{
		const void _PL_ _PL_ P;	//MemC_CL : Access as Pointer Array
		const size_t _PL_ V;	//MemC_CL : Access as Numeric Array
	}
	ArgAccess;					//MemC_CL : Argument Access
	const void _PL_ ArgMemory;	//MemC_CL : Argument Data Storage
	size_t _PL_ WLocals;		//MemC_CL : The Number of Local Workers
	size_t _PL_ WGroups;		//MemC_CL : The Number of Work Groups
	size_t _PL_ WOffset;		//MemC_CL : Global Worker Offset
	size_t _PL_ WLength;		//MemC_CL : Work Length
};
MemC_Type_Declare_(struct,devi_km,DEVI_KM);	//MemC_CL : Kernel Manager Structure

enum _devi_cf		//MemC_CL : Device Memory Copy Function Flag Enumeration
{
	DeviCopyHtoH=0,	//MemC_CL : Host to Host Copy (Not Used)
	DeviCopyHtoD=1,	//MemC_CL : Host to Device Copy
	DeviCopyDtoH=2, //MemC_CL : Device to Host Copy
	DeviCopyDtoD=3	//MemC_CL : Device to Device Copy
};
MemC_Type_Declare_(enum,devi_cf,DEVI_CF);	//MemC_CL : Device Memory Copy Function Flag Enumeration
#endif
#endif

#if(MemC_Fold_(Definition:Macros))
#if(MemC_Fold_(Part:Memory))
#define MemC_Deloc_(Memory) do{if(Memory){free(Memory);(Memory)=NULL;}}while(0)	//MemClip : Memory Deallocation
#define Unit_Alloc_(type) (type*)Byte_Alloc_(sizeof(type))						//MemClip : Unit Memory Allocation
#define Line_Alloc_(Z,type) (type*)_Line_Alloc_(Z,sizeof(type))					//MemClip : 1D Array Memory Allocation
#define Rect_Alloc_(Y,Z,type) (type**)_Rect_Alloc_(Y,Z,sizeof(type))			//MemClip : 2D Array Memory Allocation
#define Cube_Alloc_(X,Y,Z,type) (type***)_Cube_Alloc_(X,Y,Z,sizeof(type))		//MemClip : 3D Array Memory Allocation
#define Tess_Alloc_(W,X,Y,Z,type) (type****)_Tess_Alloc_(W,X,Y,Z,sizeof(type))	//MemClip : 4D Array Memory Allocation

#define MemC_Mute_(Argument) ((void)(Argument))				//MemClip : Unused Argument Warning Mute
#define MemC_Size_(type,Elements) ((Elements)*sizeof(type))	//MemClip : Byte Size of Elements

#define Byte_Clear_(Memory,ByteSize) memset(Memory,0,ByteSize)							//MemClip : Data Reset in Byte Size
#define Byte_Copy_(Source,Target,ByteSize) memcpy_s(Target,ByteSize,Source,ByteSize)	//MemClip : Data Copy in Byte Size
#define Byte_Compare_(MemoryA,MemoryB,ByteSize) memcmp(MemoryA,MemoryB,ByteSize)		//MemClip : Data Compare in Byte Size

#define Unit_Clear_(Unit,type) (type*)memset(Unit,0,sizeof(type))			//MemClip : Unit Data Reset
#define Unit_Compare_(UnitA,UnitB,type) memcmp(UnitA,UnitB,sizeof(type))	//MemClip : Unit Data Compare

#define Line_Clear_(Line,Elements,type) (type*)memset(Line,0,(Elements)*sizeof(type))									//MemClip : 1D Array Data Reset
#define Line_Copy_(Source,Target,Elements,type) memcpy_s(Target,(Elements)*sizeof(type),Source,(Elements)*sizeof(type))	//MemClip : 1D Array Data Copy
#define Line_Compare_(LineA,LineB,Elements,type) memcmp(LineA,LineB,(Elements)*sizeof(type))							//MemClip : 1D Array Data Compare

#define Line_Init_(Memory,Tile,Elements,type) _Line_Init_(Memory,Tile,Elements,sizeof(type))						//MemClip : 1D Array Data Preset
#define Line_Pick_(Source,Target,Channels,Elements,type) _Line_Pick_(Source,Target,Channels,Elements,sizeof(type))	//MemClip : 1D Array Channel Pick
#define Line_Fill_(Source,Target,Channels,Elements,type) _Line_Fill_(Source,Target,Channels,Elements,sizeof(type))	//MemClip : 1D Array Channel Fill

#define Line_Assign_U_(Address,Line,Jump,Number,type) _Line_Assign_(Address,Line,Jump,Number,sizeof(type),0)			//MemClip : 1D Array Uniform Interval Addressing
#define Line_Assign_N_(Address,Line,Jump,Number,type) _Line_Assign_(Address,Line,(size_t)(Jump),Number,sizeof(type),1)	//MemClip : 1D Array Non-Uniform Interval Addressing

#define MemC_Switch_(Key,RefBook,RefLng,KeyLng,Refs,type) _MemC_Switch_(Key,RefBook,RefLng,KeyLng,Refs,sizeof(type))	//MemClip : Key Finding for Switch Operation
#define MemC_Copy_(S,T,SOfs,TOfs,Lng,SShp,TShp,Dims,type) _MemC_Copy_(S,T,SOfs,TOfs,Lng,SShp,TShp,Dims,sizeof(type))	//MemClip : Array Data Copy

#define MemC_DT_Define_(IScope,IIndex,IName,IFlag,ILink,IMeta,type) {.Scope=(IScope),.Index=(IIndex),.Flag=(IFlag),.SizeType=sizeof(type),.SizeName=sizeof(IName),.Name=(IName),.Link=(ILink),.Meta=(IMeta)}	//MemClip : Macro for MemC_DT Definition
#endif
#if(MemC_Fold_(Part:OpenCL))
#ifdef __OPENCL_H
#define Devi_Numb_Platforms_(Num) clGetPlatformIDs(0,NULL,Num)													//MemC_CL : Platform Number Get
#define Devi_List_Platforms_(List,Listed,Entries) clGetPlatformIDs(Entries,List,Listed)							//MemC_CL : Platform List Get
#define Devi_Info_Platform_(Pltf,List,Num,type,Flag) clGetPlatformInfo(Pltf,Flag,(Num)*sizeof(type),List,NULL)	//MemC_CL : Platform Information Get
#define Devi_Size_Info_Platform_(Pltf,Size,Flag) clGetPlatformInfo(Pltf,Flag,0,NULL,Size)						//MemC_CL : Platform Information Size Get

#define Devi_Numb_Devices_(Pltf,Num) clGetDeviceIDs(Pltf,CL_DEVICE_TYPE_ALL,0,NULL,Num)								//MemC_CL : Device Number Get
#define Devi_List_Devices_(Pltf,List,Listed,Entries) clGetDeviceIDs(Pltf,CL_DEVICE_TYPE_ALL,Entries,List,Listed)	//MemC_CL : Device List Get
#define Devi_Info_Device_(Devi,List,Num,type,Flag) clGetDeviceInfo(Devi,Flag,(Num)*sizeof(type),List,NULL)			//MemC_CL : Device Information Get
#define Devi_Size_Info_Device_(Devi,Size,Flag) clGetDeviceInfo(Devi,Flag,0,NULL,Size)								//MemC_CL : Device Information Size Get

#define Devi_Create_Context_(DeviceList,Number,Error) clCreateContext(NULL,Number,DeviceList,NULL,NULL,Error)	//MemC_CL : Context Memory Allocation - Deallocate with "Devi_Delete_Context_"
#define Devi_Delete_Context_(Context) do{if(Context){clReleaseContext(Context);(Context)=NULL;}}while(0)		//MemC_CL : Context Memory Deallocation
#define Devi_Info_Context_(Cntx,List,Num,type,Flag) clGetContextInfo(Cntx,Flag,(Num)*sizeof(type),List,NULL)	//MemC_CL : Context Information Get
#define Devi_Size_Info_Context_(Cntx,Size,Flag) clGetContextInfo(Cntx,Flag,0,NULL,Size)							//MemC_CL : Context Information Size Get

#define Devi_Create_Program_Source_(Cntx,SrcList,SrcLng,SrcNum,Error) clCreateProgramWithSource(Cntx,SrcNum,SrcList,SrcLng,Error)							//MemC_CL : Program Memory Allocation - Deallocate with "Devi_Delete_Program_"
#define Devi_Create_Program_Binary_(DeviList,Cntx,BinList,BinLng,BinNum,Error) clCreateProgramWithBinary(Cntx,BinNum,DeviList,BinLng,BinList,NULL,Error)	//MemC_CL : Program Memory Allocation - Deallocate with "Devi_Delete_Program_"
#define Devi_Delete_Program_(Program) do{if(Program){clReleaseProgram(Program);(Program)=NULL;}}while(0)													//MemC_CL : Program Memory Deallocation
#define Devi_Info_Program_(Prgm,List,Num,type,Flag) clGetProgramInfo(Prgm,Flag,(Num)*sizeof(type),List,NULL)												//MemC_CL : Program Information Get
#define Devi_Size_Info_Program_(Prgm,Size,Flag) clGetProgramInfo(Prgm,Flag,0,NULL,Size)																		//MemC_CL : Program Information Size Get

#define Devi_Build_(Program,Option) clBuildProgram(Program,0,NULL,Option,NULL,NULL)											//MemC_CL : Program Build
#define Devi_Info_Build_(Devi,Prgm,List,Num,type,Flag) clGetProgramBuildInfo(Prgm,Devi,Flag,(Num)*sizeof(type),List,NULL)	//MemC_CL : Program Build Information Get
#define Devi_Size_Info_Build_(Devi,Prgm,Size,Flag) clGetProgramBuildInfo(Prgm,Devi,Flag,0,NULL,Size)						//MemC_CL : Program Build Information Size Get

#define Devi_Create_Kernel_(Program,KernelName,Error) clCreateKernel(Program,KernelName,Error)								//MemC_CL : Kernel Memory Allocation - Deallocate with "Devi_Delete_Kernel_"
#define Devi_Create_Kernel_Set_(Program,Set,Created,Entries) clCreateKernelsInProgram(Program,Entries,Set,Created)			//MemC_CL : Multiple Kernels Memory Allocation
#define Devi_Delete_Kernel_(Kernel) do{if(Kernel){clReleaseKernel(Kernel);(Kernel)=NULL;}}while(0)							//MemC_CL : Kernel Memory Deallocation
#define Devi_Info_Kernel_(Krnl,List,Num,type,Flag) clGetKernelInfo(Krnl,Flag,(Num)*sizeof(type),List,NULL)					//MemC_CL : Kernel Information Get
#define Devi_Size_Info_Kernel_(Krnl,Size,Flag) clGetKernelInfo(Krnl,Flag,0,NULL,Size)										//MemC_CL : Kernel Information Size Get
#define Devi_Info_Work_(Devi,Krnl,List,Num,type,Flag) clGetKernelWorkGroupInfo(Krnl,Devi,Flag,(Num)*sizeof(type),List,NULL)	//MemC_CL : Kernel Work Group Information Get
#define Devi_Size_Info_Work_(Devi,Krnl,Size,Flag) clGetKernelWorkGroupInfo(Krnl,Devi,Flag,0,NULL,Size)						//MemC_CL : Kernel Work Group Information Size Get

#define Devi_Create_Queue_(Context,Device,Error) clCreateCommandQueueWithProperties(Context,Device,NULL,Error)		//MemC_CL : Command Queue Memory Allocation - Deallocate with "Devi_Delete_Queue_"
#define Devi_Delete_Queue_(Queue) do{if(Queue){clReleaseCommandQueue(Queue);(Queue)=NULL;}}while(0)					//MemC_CL : Command Queue Memory Deallocation
#define Devi_Info_Queue_(Queue,List,Num,type,Flag) clGetCommandQueueInfo(Queue,Flag,(Num)*sizeof(type),List,NULL)	//MemC_CL : Command Queue Information Get
#define Devi_Size_Info_Queue_(Queue,Size,Flag) clGetCommandQueueInfo(Queue,Flag,0,NULL,Size)						//MemC_CL : Command Queue Information Size Get

#define Devi_Create_Buffer_(Context,Elements,type) _Devi_Create_Buffer_(Context,Elements,sizeof(type))					//MemC_CL : Buffer Object Memory Allocation - Deallocate with "Devi_Delete_Buffer_"
#define Devi_Create_Buffer_Sub_(Root,Offset,Elements,type) _Devi_Create_Buffer_Sub_(Root,Offset,Elements,sizeof(type))	//MemC_CL : Sub-Buffer Object Memory Allocation - Deallocate with "Devi_Delete_Buffer_"
#define Devi_Delete_Buffer_(Memory) do{if(Memory){clReleaseMemObject(Memory);(Memory)=NULL;}}while(0)					//MemC_CL : Buffer or Sub-Buffer Object Memory Deallocation
#define Devi_Info_Buffer_(Bf,List,Num,type,Flag) clGetMemObjectInfo(Bf,Flag,(Num)*sizeof(type),List,NULL)				//MemC_CL : Buffer or Sub-Buffer Object Information Get
#define Devi_Size_Info_Buffer_(Bf,Size,Flag) clGetMemObjectInfo(Bf,Flag,0,NULL,Size)									//MemC_CL : Buffer or Sub-Buffer Object Information Size Get

#define Devi_Create_Event_(Context,Error) clCreateUserEvent(Context,Error)														//MemC_CL : Event Object Memory Allocation - Deallocate with "Devi_Delete_Event_"
#define Devi_Delete_Event_(Event,Error) do{(Error)=_Devi_Delete_Event_(Event);if((Error)==CL_SUCCESS){(Event)=NULL;}}while(0)	//MemC_CL : Event Object Memory Deallocation
#define Devi_Event_Inc_(Event) clRetainEvent(Event)																				//MemC_CL : Event Count Increase
#define Devi_Event_Dec_(Event) clReleaseEvent(Event)																			//MemC_CL : Event Count Decrease
#define Devi_Info_Event_(Event,List,Num,type,Flag) clGetEventInfo(Event,Flag,(Num)*sizeof(type),List,NULL)						//MemC_CL : Event Object Information Get
#define Devi_Size_Info_Event_(Event,Size,Flag) clGetEventInfo(Event,Flag,0,NULL,Size)											//MemC_CL : Event Object Information Size Get
#define Devi_Wait_Event_(EventList,Number) clWaitForEvents(Number,EventList)													//MemC_CL : Waiting for Events to Complete

#define Devi_Init_(Q,Bf,Val,Ofs,Lng,type) clEnqueueFillBuffer(Q,Bf,Val,sizeof(type),(Ofs)*sizeof(type),(Lng)*sizeof(type),0,NULL,NULL)	//MemC_CL : Buffer Object Memory Initialization
#define Devi_Copy_(Q,S,T,SOfs,TOfs,Lng,SShp,TShp,Dims,type,Flag) _Devi_Copy_(Q,S,T,SOfs,TOfs,Lng,SShp,TShp,Dims,sizeof(type),Flag)		//MemC_CL : Buffer Object Memory Copy
#define Devi_Copy_1D_(Q,S,T,SOfs,TOfs,Lng,type,Flag) _Devi_Copy_1D_(Q,S,T,SOfs,TOfs,Lng,sizeof(type),Flag)								//MemC_CL : Buffer Object Memory 1D Copy

#define Devi_Flush_(Queue) clFlush(Queue)	//MemC_CL : Command Queue Flush
#define Devi_Finish_(Queue) clFinish(Queue)	//MemC_CL : Command Queue Finish

#define Devi_Karg_(Kernel,Order,Address,ByteSize) clSetKernelArg(Kernel,Order,ByteSize,Address)	//MemC_CL : Kernel Argument Set

#define Devi_KM_Type_C_(KM,Index) _Devi_KM_Type_(KM,Index,0,DeviDomainConstant)					//MemC_CL : Kernel Manager Argument Type Setting (Constant Domain)
#define Devi_KM_Type_G_(KM,Index) _Devi_KM_Type_(KM,Index,0,DeviDomainGlobal)					//MemC_CL : Kernel Manager Argument Type Setting (Global Domain)
#define Devi_KM_Type_L_(KM,Index,type) _Devi_KM_Type_(KM,Index,sizeof(type),DeviDomainLocal)	//MemC_CL : Kernel Manager Argument Type Setting (Local Domain)
#define Devi_KM_Type_P_(KM,Index,type) _Devi_KM_Type_(KM,Index,sizeof(type),DeviDomainPrivate)	//MemC_CL : Kernel Manager Argument Type Setting (Private Domain)
#endif
#endif
#if(MemC_Fold_(Part:Literals))
#define MemC_Copy_Max_Dimension 8	//MemClip : Maximum Copy Dimension of "MemC_Copy_"
#ifdef __OPENCL_H
#define Devi_Copy_Max_Dimension 3	//MemC_CL : Maximum Copy Dimension of "Devi_Copy_"
#endif
#endif
#endif

#if(MemC_Fold_(Declaration:Global Constants))
//MemClip : Library Version
extern const char _PL_ MemClip;
//MemClip : Self Reference
extern const void _PL_ MemCrux;
//MemClip : Address Type Descriptor
extern MEMC_DT _PL_ MemCTypeAddress;
#endif

#if(MemC_Fold_(Declaration:Memory Functions))
//MemClip : Nothing
void MemC_Void_(void);
//MemClip : Memory Allocation Check
//＊Return value is 0 for failure, 1 for success.
int MemC_Check_(const void _PL_ *MemorySet,const size_t Count);
//MemClip : Memory Allocation - Deallocate with "MemC_Deloc_"
void *Byte_Alloc_(const size_t ByteSize);
//MemClip : Array Memory Allocation - Deallocate with "MemC_Deloc_"
//＊Return value is the allocated memory address.
void *MemC_Alloc_(const size_t _PL_ ArraySize,const size_t DimensionsNumber,const size_t ElementSize);
//MemClip : Batch Memory Deallocation
void MemC_Deloc_Set_(void **MemorySet,const size_t Count);
#endif

#if(MemC_Fold_(Declaration:MemClip Structure Functions))
//MemClip : Memory Slot Memory Allocation - Deallocate with "MemC_MS_Delete_"
//＊Nums = SlotsNumber
memc_ms *MemC_MS_Create_(const void _PL_ Identification,const size_t SlotsNumber);
//MemClip : Memory Slot Memory Deallocation
void MemC_MS_Delete_(memc_ms *_PL_ MemorySlot);
//MemClip : Memory Slot Memory Type Change
int MemC_MS_Change_(MEMC_MS _PL_ MemorySlot,MEMC_DT _PL_ MemoryType);

//MemClip : Memory Slot Data Reset
int MemC_MS_Init_(MEMC_MS _PL_ MemorySlot);
//MemClip : Memory Slot NULL Check
//＊Count = MemorySlot -> Slot.V[0]
//　MemorySet = { P[1], P[2], ..., P[Count] | P = MemorySlot -> Slot.P }
//＊Mode 0 : Return value is 1 for all NULLs, otherwise 0.
//＊Mode 1 : Return value is 0 for any NULLs, otherwise 1.
int MemC_MS_Null_(MEMC_MS _PL_ MemorySlot,const int CheckMode);

//MemClip : Just kidding!
int MemC_MS_Joke_(MEMC_MS _PL_ MemorySlot);
//MemClip : Oops!
int MemC_MS_Oops_(MEMC_MS _PL_ MemorySlot);

//MemClip : Memory Container Memory Allocation - Deallocate with "MemC_MC_Delete_"
//＊Unit = TypeInfo -> SizeType
//　Dims = ShapeInfo -> Slot.V[0]
//　LngND = { V[1], V[2], ..., V[Dims] | V = ShapeInfo -> Slot.V }
memc_mc *MemC_MC_Create_(const void _PL_ Identification,MEMC_MS _PL_ ShapeInfo,MEMC_DT _PL_ TypeInfo);
//MemClip : Memory Container Memory Deallocation
void MemC_MC_Delete_(memc_mc *_PL_ MemoryContainer);
//MemClip : Memory Container Data Type Change
int MemC_MC_Change_(MEMC_MC _PL_ MemoryContainer,MEMC_DT _PL_ DataType);
#endif

#if(MemC_Fold_(Declaration:OpenCL Functions))
#ifdef __OPENCL_H
//MemC_CL : Kernel Enqueue
//＊Maximum dimension is 3.
cl_int Devi_Kenq_(cl_command_queue const,cl_kernel const,const size_t _PL_ WorkGroups,const size_t _PL_ LocalWorkers,const size_t _PL_ GlobalOffset,const cl_uint Dimensions);

//MemC_CL : Queue Container Memory Allocation - Deallocate with "Devi_QC_Delete_"
devi_qc *Devi_QC_Create_(const cl_uint PlatformSelect,const cl_uint DeviceSelect);
//MemC_CL : Queue Container Memory Deallocation
void Devi_QC_Delete_(devi_qc *_PL_ QueueContainer);

//MemC_CL : Buffer Container Memory Allocation - Deallocate with "Devi_BC_Delete_"
//＊Nums = ShapeInfo -> Slot.V[0]
//＊Mode 0 : Uniform Length
//　LngS = { V[1], V[1], ..., V[1] | V = ShapeInfo -> Slot.V }
//＊Mode 1 : Ununiform Length
//　LngS = { V[1], V[2], ..., V[Nums] | V = ShapeInfo -> Slot.V }
devi_bc *Devi_BC_Create_(const void _PL_ Identification,cl_context const Context,MEMC_MS _PL_ ShapeInfo,MEMC_DT _PL_ TypeInfo,const int Mode);
//MemC_CL : Buffer Container Memory Deallocation
void Devi_BC_Delete_(devi_bc *_PL_ BufferContainer);

//MemC_CL : Kernel Manager Memory Allocation - Deallocate with "Devi_KM_Delete_"
devi_km *Devi_KM_Create_(const void _PL_ Identification,const size_t KernelArguments,const size_t WorkDimension);
//MemC_CL : Kernel Manager Initialization
//＊Execute only one time for one kernel manager, after type setting with "Devi_KM_Type_*_".
cl_int Devi_KM_Init_(devi_km _PL_ KernelManager,cl_kernel const Kernel);
//MemC_CL : Kernel Manager Memory Deallocation
void Devi_KM_Delete_(devi_km *_PL_ KernelManager);

//MemC_CL : Kernel Manager Argument Save
//＊If KM -> Flag[Order] == DeviDomainLocal,
//　then pass the number of local buffer elements as the token,
//　otherwise pass the address of the argument as the token.
cl_int Devi_KM_Save_(DEVI_KM _PL_ KM,const size_t Order,const size_t Token);

//MemC_CL : Kernel Enqueue with Kernel Manager
cl_int Devi_KM_Enqueue_(cl_command_queue const Queue,DEVI_KM _PL_ KernelManager);
#endif
#endif

#if(MemC_Fold_(Declaration:MemClip Fused Functions))
//MemClip : Virtual Container Memory Allocation - Deallocate with "MemC_VC_Delete_"
//＊V = EntryInfo -> Slot.V
//　Dims = ( MC -> Dims ) - V[0]
//　LngND = ( MC -> LngND ) + V[0]
//　Hidden = MC -> AcsND[V[1]][V[2]][...][V[V[0]]]
memc_vc *MemC_VC_Create_(const void _PL_ Identification,MEMC_MC _PL_ MemoryContainer,MEMC_MS _PL_ EntryInfo);
#ifdef __OPENCL_H
//MemC_CL : Virtual Container Memory Allocation - Deallocate with "MemC_VC_Delete_"
//＊Dims = EntryInfo -> Slot.V[1]
//　LngND = { V[2], V[3], ..., V[Dims+1] | V = EntryInfo -> Slot.V }
//　Hidden = BC -> BufS[V[0]]
memc_vc *Devi_VC_Create_(const void _PL_ Identification,DEVI_BC _PL_ BufferContainer,MEMC_MS _PL_ ShapeInfo);
#endif
//MemClip : Virtual Container Memory Deallocation
void MemC_VC_Delete_(memc_vc *_PL_ VirtualContainer);
//MemClip : Virtual Container Data Type Change
int MemC_VC_Change_(MEMC_VC _PL_ VirtualContainer,MEMC_DT _PL_ DataType);

//MemClip : Virtual Container's Virtual Member :: VC->AcsND
//＊Host Domain Only
void *MemC_VC_Member_AcsND_(MEMC_VC _PL_ VirtualContainer);
//MemClip : Virtual Container's Virtual Member :: VC->Acs1D
//＊Host Domain Only
void *MemC_VC_Member_Acs1D_(MEMC_VC _PL_ VirtualContainer);
#ifdef __OPENCL_H
//MemC_CL : Virtual Container's Virtual Member :: VC->Buf
//＊Device Domain Only
cl_mem Devi_VC_Member_Buf_(MEMC_VC _PL_ VirtualContainer);
#endif
//MemClip : Virtual Container Memory Access
//＊V = AccessInfo -> Slot.V
//＊Host Domain :
//　V[0] = &( VC -> AcsND[V[1]][V[2]]...[V[Dims]] )
//＊Device Domain :
//　V[0] = &( VC -> AcsND[V[1]][V[2]]...[V[Dims]] ) - &( VC -> Acs1D[0] )
//　Note that the returned offset V[0] is not in byte unit.
//＊Return value is 1 for success, 0 for failure.
int MemC_VC_Access_(MEMC_VC _PL_ VirtualContainer,MEMC_MS _PL_ AccessInfo);

//MemClip : Virtual Container Data Reset
//＊Return value is 1 for success, 0 for failure.
int MemC_VC_Init_(void _PL_ Queue,MEMC_VC _PL_ VirtualContainer);
//MemClip : Virtual Container Data Copy
//＊CopyDims = CopyInfo -> Slot.V[0] ≤ min { SourceDims, TargetDims }
//　CopyLngND = { V[1], V[2], ..., V[CopyDims] | V = CopyInfo -> Slot.V }
//　SourceOffset = { E[1], E[2], ..., E[SourceDims] | E = V + CopyDims }
//　TargetOffset = { F[1], F[2], ..., F[TargetDims] | F = E + SourceDims }
//＊Type checker should return 1 for compatible types, 0 for incompatible types.
//＊Return value is 1 for success, 0 for failure.
int MemC_VC_Copy_(const void _PL_ Queue,MEMC_VC _PL_ SourceContainer,MEMC_VC _PL_ TargetContainer,MEMC_MS _PL_ CopyInfo);
#endif

#if(MemC_Fold_(Declaration:Redefined Functions))
void *_Line_Alloc_(const size_t,const size_t);
void *_Rect_Alloc_(const size_t,const size_t,const size_t);
void *_Cube_Alloc_(const size_t,const size_t,const size_t,const size_t);
void *_Tess_Alloc_(const size_t,const size_t,const size_t,const size_t,const size_t);

errno_t _Line_Init_(void _PL_ Memory,const void _PL_ Tile,const size_t Number,const size_t TypeSize);
errno_t _Line_Pick_(const void _PL_ Input,void _PL_ Output,const size_t Channels,const size_t Number,const size_t TypeSize);
errno_t _Line_Fill_(const void _PL_ Input,void _PL_ Output,const size_t Channels,const size_t Number,const size_t TypeSize);

errno_t _MemC_Copy_(const void _PL_ S,void _PL_ T,const size_t _PL_ OfsS,const size_t _PL_ OfsT,const size_t _PL_ Lng,const size_t _PL_ ShpS,const size_t _PL_ ShpT,const size_t Dims,const size_t TypeSize);

size_t _Line_Assign_(void _PL_ Indexer,const void _PL_ Indexed,const size_t Interval,const size_t Indices,const size_t TypeSize,const int Mode);
size_t _MemC_Switch_(const void _PL_ Key,const void _PL_ _PL_ TblRf,const size_t* LngRf,const size_t LngKey,const size_t NumRf,const size_t TypeSize);

#ifdef __OPENCL_H
cl_mem _Devi_Create_Buffer_(cl_context const,const size_t,const size_t);
cl_mem _Devi_Create_Buffer_Sub_(cl_mem const,const size_t,const size_t,const size_t);
cl_int _Devi_Delete_Event_(cl_event const);

cl_int _Devi_Copy_(cl_command_queue const Q,void _PL_ S,void _PL_ T,const size_t _PL_ OfsS,const size_t _PL_ OfsT,const size_t _PL_ Lng,const size_t _PL_ ShpS,const size_t _PL_ ShpT,const cl_uint Dims,const size_t TypeSize,DEVI_CF Mode);
cl_int _Devi_Copy_1D_(cl_command_queue const Q,void _PL_ S,void _PL_ T,const size_t OfsS,const size_t OfsT,const size_t Lng,const size_t TypeSize,DEVI_CF Mode);

cl_int _Devi_KM_Type_(DEVI_KM _PL_ KM,const size_t Idx,const size_t TypeSize,DEVI_DF Mode);
#endif
#endif
#endif
