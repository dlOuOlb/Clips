/*------------------------------------------------------------------*/
/*	MemClip provides some memory allocating functions.				*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2018.06.06	*/
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
#define NULL (0)	//MemClip : Null Pointer Definition
#endif

static_assert((sizeof(void*)==sizeof(size_t)),"sizeof(void*) != sizeof(size_t)");
static_assert((sizeof(char)==1),"sizeof(char) != 1");

#ifdef _PL_
#error The macro "_PL_" is already defined.
#else
#define _PL_ *const	//MemClip : Pointer Lock Definition
#endif

#define MemC_Declare_(spec,type,TYPE) typedef spec _##type type;typedef const spec _##type TYPE;	//MemClip : Macro for Type Declaration
#endif

#if(MemC_Fold_(Definition:Types))
struct _memc_dt					//MemClip : Data Type Structure
{
	const void _PL_ Scope;		//MemClip : ID Scope
	const size_t ID;			//MemClip : Identification
	const size_t Flag;			//MemClip : Property Flag
	const size_t SizeType;		//MemClip : Type's Byte Size
	const size_t SizeName;		//MemClip : Name's Byte Size
	const char _PL_ Name;		//MemClip : Type Name
	const void _PL_ Link;		//MemClip : External Link
	const void _PL_ Meta;		//MemClip : Meta Data
};
MemC_Declare_(struct,memc_dt,MEMC_DT);	//MemClip : Data Type Structure

struct _memc_ms				//MemClip : Memory Slot Structure
{
	void *ID;				//MemClip : Identification
	MEMC_DT _PL_ Type;		//MemClip : Data Type
	const size_t Nums;		//MemClip : Number of Slots
	const union _memc_pv	//MemClip : Pointer and Value Union
	{
		void *_PL_ P;		//MemClip : Access as Pointer Array
		size_t _PL_ V;		//MemClip : Access as Numeric Array
	}
	Slot;					//MemClip : Slot Access
};
MemC_Declare_(struct,memc_ms,MEMC_MS);	//MemClip : Memory Slot Structure

struct _memc_mc					//MemClip : Memory Container Structure
{
	void *ID;					//MemClip : Identification
	MEMC_DT _PL_ Type;			//MemClip : Data Type
	const size_t Unit;			//MemClip : Type Size
	const size_t Dims;			//MemClip : Dimension (N)
	const size_t Lng1D;			//MemClip : Total Number of Elements
	const size_t _PL_ LngND;	//MemClip : Data Shape
	void _PL_ Acs1D;			//MemClip : 1-Dimensional Data Access
	void _PL_ AcsND;			//MemClip : N-Dimensional Data Access
};
MemC_Declare_(struct,memc_mc,MEMC_MC);	//MemClip : Memory Container Structure

enum _memc_df				//MemClip : Memory Domain Flag Enumeration
{
	MemCDomainHost=0x48,	//MemClip : Memory in Host Domain
	MemCDomainDevice=0x44	//MemClip : Memory in Device Domain
};
MemC_Declare_(enum,memc_df,MEMC_DF);	//MemClip : Memory Domain Flag Enumeration
static_assert(sizeof(memc_df)<=sizeof(size_t),"sizeof(enum) > sizeof(size_t)");

struct _memc_vc					//MemClip : Virtual Container Structure
{
	void *ID;					//MemClip : Identification
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
MemC_Declare_(struct,memc_vc,MEMC_VC);	//MemClip : Virtual Container Structure

#ifdef __OPENCL_H
struct _devi_qc						//MemC_CL : Queue Container Structure
{
	const cl_platform_id Platform;	//MemC_CL : Platform ID
	const cl_device_id Device;		//MemC_CL : Device ID
	const cl_context Context;		//MemC_CL : Context
	const cl_command_queue Queue;	//MemC_CL : Command Queue
};
MemC_Declare_(struct,devi_qc,DEVI_QC);	//MemC_CL : Queue Container Structure

struct _devi_bc				//MemC_CL : Buffer Container Structure
{
	void *ID;				//MemC_CL : Identification
	MEMC_DT _PL_ Type;		//MemC_CL : Data Type
	const size_t Unit;		//MemC_CL : Type Size
	const size_t LngT;		//MemC_CL : Total Length
	const cl_mem BufT;		//MemC_CL : Main Buffer
	const size_t Nums;		//MemC_CL : Number of Sub-Buffers
	const size_t _PL_ LngS;	//MemC_CL : Lengths of Sub-Buffers
	const cl_mem _PL_ BufS;	//MemC_CL : Sub-Buffer Address Array
};
MemC_Declare_(struct,devi_bc,DEVI_BC);	//MemC_CL : Buffer Container Structure

struct _devi_km							//MemC_CL : Kernel Manager Structure
{
	const cl_kernel Kernel;				//MemC_CL : Linked Kernel
	const char _PL_ Flag;				//MemC_CL : Argument Type Indicator
	const void _PL_ Memory;				//MemC_CL : Argument Data Storage
	const void _PL_ _PL_ ArgAddress;	//MemC_CL : Argument Address Set
	const size_t _PL_ ArgSize;			//MemC_CL : Argument Byte Size Set
	const size_t _PL_ Elements;			//MemC_CL : The Number of Elements for Local Memory
	const size_t _PL_ TypeSize;			//MemC_CL : Argument Type Byte Size
	size_t _PL_ WLocals;				//MemC_CL : The Number of Local Workers
	size_t _PL_ WGroups;				//MemC_CL : The Number of Work Groups
	size_t _PL_ WOffset;				//MemC_CL : Global Worker Offset
	size_t _PL_ WLength;				//MemC_CL : Work Length
	const cl_uint KArgs;				//MemC_CL : The Number of Kernel Arguments
	const cl_uint WDims;				//MemC_CL : Work Dimensions
};
MemC_Declare_(struct,devi_km,DEVI_KM);	//MemC_CL : Kernel Manager Structure

enum _devi_cf		//MemC_CL : Device Memory Copy Function Flag Enumeration
{
	DeviCopyHtoD=1,	//MemC_CL : Host to Device Copy
	DeviCopyDtoH=2, //MemC_CL : Device to Host Copy
	DeviCopyDtoD=3	//MemC_CL : Device to Device Copy
};
MemC_Declare_(enum,devi_cf,DEVI_CF);	//MemC_CL : Device Memory Copy Function Flag Enumeration
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
#define MemC_Acs_(type,Data) (*((type*)(&(Data))))			//MemClip : Indirect Memory Access
#define MemC_Rst_ __restrict								//MemClip : Exclusive memory Access

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

#define Devi_Create_Program_(Cntx,List,Lng,Num,Error) clCreateProgramWithSource(Cntx,Num,List,Lng,Error)		//MemC_CL : Program Memory Allocation - Deallocate with "Devi_Delete_Program_"
#define Devi_Delete_Program_(Program) do{if(Program){clReleaseProgram(Program);(Program)=NULL;}}while(0)		//MemC_CL : Program Memory Deallocation
#define Devi_Info_Program_(Prgm,List,Num,type,Flag) clGetProgramInfo(Prgm,Flag,(Num)*sizeof(type),List,NULL)	//MemC_CL : Program Information Get
#define Devi_Size_Info_Program_(Prgm,Size,Flag) clGetProgramInfo(Prgm,Flag,0,NULL,Size)							//MemC_CL : Program Information Size Get

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

#define Devi_Karg_(Kernel,Order,Address,ByteSize) clSetKernelArg(Kernel,Order,ByteSize,Address)					//MemC_CL : Kernel Argument Set
#define Devi_Karg_Global_(Kernel,Order,BufferAddress) clSetKernelArg(Kernel,Order,sizeof(cl_mem),BufferAddress)	//MemC_CL : Kernel Argument Set (Buffer Object)
#define Devi_Karg_Local_(Kernel,Order,Elements,type) clSetKernelArg(Kernel,Order,(Elements)*sizeof(type),NULL)	//MemC_CL : Kernel Argument Set (Local Memory)
#define Devi_Karg_Value_(Kernel,Order,ValueAddress,type) clSetKernelArg(Kernel,Order,sizeof(type),ValueAddress)	//MemC_CL : Kernel Argument Set (Parameter Value)

#define Devi_KM_Type_G_(Karg,Order,type) _Devi_KM_Type_(Karg,Order,sizeof(type),0)	//MemC_CL : Kernel Manager Argument Type Set (Global Parameter)
#define Devi_KM_Type_L_(Karg,Order,type) _Devi_KM_Type_(Karg,Order,sizeof(type),1)	//MemC_CL : Kernel Manager Argument Type Set (Local Parameter)
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
memc_ms *MemC_MS_Create_(const size_t SlotsNumber);
//MemClip : Memory Slot Memory Deallocation
void MemC_MS_Delete_(memc_ms *_PL_ MemorySlot);

//MemClip : Memory Container Memory Allocation - Deallocate with "MemC_MC_Delete_"
//＊Unit = TypeInfo -> SizeType
//　Dims = ShapeInfo -> Slot.V[0]
//　LngND = { V[1], V[2], ..., V[Dims] }
memc_mc *MemC_MC_Create_(MEMC_MS _PL_ ShapeInfo,MEMC_DT _PL_ TypeInfo);
//MemClip : Memory Container Memory Deallocation
void MemC_MC_Delete_(memc_mc *_PL_ MemoryContainer);

//MemClip : Memory Container Array Access
//＊Return = &(MemoryContainer -> AcsND[V[0]][V[1]][...][V[Dims-1]])
void *MemC_MC_Access_(MEMC_MC _PL_ MemoryContainer,MEMC_MS _PL_ OffsetInfo);
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
//　LngS[n] = { V[1], V[1], ..., V[1] }
//＊Mode 1 : Ununiform Length
//　LngS[n] = { V[1], V[2], ..., V[Nums] }
devi_bc *Devi_BC_Create_(const cl_context Context,MEMC_MS _PL_ ShapeInfo,MEMC_DT _PL_ TypeInfo,const int Mode);
//MemC_CL : Buffer Container Memory Deallocation
void Devi_BC_Delete_(devi_bc *_PL_ BufferContainer);

//MemC_CL : Kernel Manager Memory Allocation - Deallocate with "Devi_KM_Delete_"
devi_km *Devi_KM_Create_(cl_kernel const,const cl_uint KernelArguments,const cl_uint WorkDimension);
//MemC_CL : Kernel Manager Initialization
//＊Execute only one time for one karg manager.
cl_int Devi_KM_Init_(devi_km _PL_ KernelManager);
//MemC_CL : Kernel Manager Memory Deallocation
void Devi_KM_Delete_(devi_km *_PL_ KernelManager);

//MemC_CL : Kernel Manager Argument Save (Global)
cl_int Devi_KM_Save_G_(DEVI_KM _PL_ KernelManager,const cl_uint Index,const void _PL_ Value);
//MemC_CL : Kernel Manager Argument Save (Local)
cl_int Devi_KM_Save_L_(DEVI_KM _PL_ KernelManager,const cl_uint Index,const size_t Elements);

//MemC_CL : Kernel Enqueue with Kernel Manager
cl_int Devi_KM_Enqueue_(cl_command_queue const Queue,DEVI_KM _PL_ KernelManager);
#endif
#endif

#if(MemC_Fold_(Declaration:Fused Functions))
//MemClip : Virtual Container Memory Allocation - Deallocate with "MemC_VC_Delete_"
//＊Dims = ( MC -> Dims ) - ( EntryInfo -> Slot.V[0] )
//　LngND = ( MC -> LngND ) + ( EntryInfo -> Slot.V[0] )
//　Hidden = MC -> AcsND[V[1]][V[2]][...][V[V[0]]]
memc_vc *MemC_VC_Create_(MEMC_MC _PL_ MemoryContainer,MEMC_MS _PL_ EntryInfo);
#ifdef __OPENCL_H
//MemC_CL : Virtual Container Memory Allocation - Deallocate with "MemC_VC_Delete_"
//＊Dims = EntryInfo -> Slot.V[1]
//　LngND = { V[2], V[3], ..., V[Dims+1] }
//　Hidden = BC -> BufS[V[0]]
memc_vc *Devi_VC_Create_(DEVI_BC _PL_ BufferContainer,MEMC_MS _PL_ ShapeInfo);
#endif
//MemClip : Virtual Container Memory Deallocation
void MemC_VC_Delete_(memc_vc *_PL_ VirtualContainer);

//MemClip : Virtual Container Member Get :: VC->AcsND
void *MemC_VC_Member_AcsND_(MEMC_VC _PL_ VirtualContainer);
//MemClip : Virtual Container Member Get :: VC->Acs1D
void *MemC_VC_Member_Acs1D_(MEMC_VC _PL_ VirtualContainer);
#ifdef __OPENCL_H
//MemC_CL : Virtual Container Member Get :: VC->Buf
cl_mem Devi_VC_Member_Buf_(MEMC_VC _PL_ VirtualContainer);
#endif

//MemClip : Virtual Container Data Reset
//＊Return value is 1 for success, 0 for failure.
int MemC_VC_Init_(void _PL_ Queue,MEMC_VC _PL_ VirtualContainer);
//MemClip : Virtual Container Data Copy
//＊CopyDims = CopyInfo -> Slot.V[0] ≤ min { SourceDims, TargetDims }
//　CopyLngND = { V[1], V[2], ..., V[CopyDims] }
//　SourceOffset = { E[1], E[2], ..., E[SourceDims] | E = V + CopyDims }
//　TargetOffset = { F[1], F[2], ..., F[TargetDims] | F = E + SourceDims }
//＊Type checker should return 1 for compatible types, 0 for incompatible types.
//＊Return value is 1 for success, 0 for failure.
int MemC_VC_Copy_(const void _PL_ Queue,MEMC_VC _PL_ SourceContainer,MEMC_VC _PL_ TargetContainer,MEMC_MS _PL_ CopyInfo,int(_PL_ Type_Checker_)(MEMC_DT _PL_ SourceType,MEMC_DT _PL_ TargetType));
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

cl_int _Devi_KM_Type_(DEVI_KM _PL_ KM,const cl_uint,const size_t,const int);
#endif
#endif
#endif
