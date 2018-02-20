/*------------------------------------------------------------------*/
/*	MemClip provides some memory allocating functions.				*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2018.02.12	*/
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

#ifndef NULL
#define NULL 0		//MemClip : Null Pointer Definition
#endif

#ifndef _PL_
#define _PL_ *const	//MemClip : Pointer Lock Definition
#endif

#ifdef __OPENCL_H
enum _devi_cp		//MemC_CL : Device Memory Copy Function Flag
{
	DeviCopyHtoD=1,	//MemC_CL : Host to Device Copy
	DeviCopyDtoH=2, //MemC_CL : Device to Host Copy
	DeviCopyDtoD=3	//MemC_CL : Device to Device Copy
};
typedef enum _devi_cp devi_cp;			//MemC_CL : Copy Flag Variable
typedef const enum _devi_cp DEVI_CP;	//MemC_CL : Copy Flag Constant

struct _devi_qc						//MemC_CL : Queue Container
{
	cl_platform_id const Platform;	//MemC_CL : Platform ID
	cl_device_id const Device;		//MemC_CL : Device ID
	cl_context const Context;		//MemC_CL : Context
	cl_command_queue const Queue;	//MemC_CL : Command Queue
};
typedef struct _devi_qc devi_qc;		//MemC_CL : Queue Container Variable
typedef const struct _devi_qc DEVI_QC;	//MemC_CL : Queue Container Constant

struct _devi_km							//MemC_CL : Kernel Manager
{
	cl_kernel const Kernel;				//MemC_CL : Linked Kernel
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
typedef struct _devi_km devi_km;		//MemC_CL : Kernel Manager Variable
typedef const struct _devi_km DEVI_KM;	//MemC_CL : Kernel Manager Constant
#endif

#define MemC_Deloc_(Memory) if(Memory){free(Memory);(Memory)=NULL;}														//MemClip : Memory Deallocation

#define Unit_Alloc_(type) (type*)Byte_Alloc_(sizeof(type))																//MemClip : Unit Memory Allocation
#define Line_Alloc_(Z,type) (type*)_Line_Alloc_(Z,sizeof(type))															//MemClip : 1D Array Memory Allocation
#define Rect_Alloc_(Y,Z,type) (type**)_Rect_Alloc_(Y,Z,sizeof(type))													//MemClip : 2D Array Memory Allocation
#define Cube_Alloc_(X,Y,Z,type) (type***)_Cube_Alloc_(X,Y,Z,sizeof(type))												//MemClip : 3D Array Memory Allocation
#define Tess_Alloc_(W,X,Y,Z,type) (type****)_Tess_Alloc_(W,X,Y,Z,sizeof(type))											//MemClip : 4D Array Memory Allocation

#define MemC_Mute_(Argument) ((void)(Argument))																			//MemClip : Unused Argument Warning Mute
#define MemC_Fold_(Comment) (1)																							//MemClip : Code Folding with #if Pre-processor.

#define MemC_Size_(type,Elements) ((Elements)*sizeof(type))																//MemClip : Byte Size of Elements
#define MemC_Acs_(type,Data) (*((type*)(&(Data))))																		//MemClip : Indirect Memory Access
#define MemC_Rst_ __restrict																							//MemClip : Exclusive memory Access

#define Unit_Clear_(Unit,type) (type*)memset(Unit,0,sizeof(type))														//MemClip : Unit Data Reset
#define Unit_Compare_(UnitA,UnitB,type) memcmp(UnitA,UnitB,sizeof(type))												//MemClip : Unit Data Compare

#define Line_Clear_(Line,Elements,type) (type*)memset(Line,0,(Elements)*sizeof(type))									//MemClip : 1D Array Data Reset
#define Line_Copy_(Source,Target,Elements,type) memcpy_s(Target,(Elements)*sizeof(type),Source,(Elements)*sizeof(type))	//MemClip : 1D Array Data Copy
#define Line_Compare_(LineA,LineB,Elements,type) memcmp(LineA,LineB,(Elements)*sizeof(type))							//MemClip : 1D Array Data Compare

#define Line_Pick_(Source,Target,Channels,Elements,type) _Line_Pick_(Source,Target,Channels,Elements,sizeof(type))		//MemClip : 1D Array Channel Pick
#define Line_Fill_(Source,Target,Channels,Elements,type) _Line_Fill_(Source,Target,Channels,Elements,sizeof(type))		//MemClip : 1D Array Channel Fill

#define Line_Assign_U_(Address,Line,Jump,Number,type) _Line_Assign_(Address,Line,Jump,Number,sizeof(type),0)			//MemClip : 1D Array Uniform Interval Addressing
#define Line_Assign_N_(Address,Line,Jump,Number,type) _Line_Assign_(Address,Line,(size_t)(Jump),Number,sizeof(type),1)	//MemClip : 1D Array Non-Uniform Interval Addressing

#define MemC_Switch_(Key,RefBook,RefLng,KeyLng,Refs,type) _MemC_Switch_(Key,RefBook,RefLng,KeyLng,Refs,sizeof(type))	//MemClip : Key Finding for Switch Operation
#define MemC_Copy_(S,T,SOfs,TOfs,Lng,SShp,TShp,Dims,type) _MemC_Copy_(S,T,SOfs,TOfs,Lng,SShp,TShp,Dims,sizeof(type))	//MemClip : Array Data Copy

#ifdef __OPENCL_H
#define Devi_Numb_Platforms_(Num) clGetPlatformIDs(0,NULL,Num)															//MemC_CL : Platform Number Get
#define Devi_List_Platforms_(List,Listed,Entries) clGetPlatformIDs(Entries,List,Listed)									//MemC_CL : Platform List Get
#define Devi_Info_Platform_(Pltf,List,Num,type,Flag) clGetPlatformInfo(Pltf,Flag,(Num)*sizeof(type),List,NULL)			//MemC_CL : Platform Information Get
#define Devi_Size_Info_Platform_(Pltf,Size,Flag) clGetPlatformInfo(Pltf,Flag,0,NULL,Size)								//MemC_CL : Platform Information Size Get

#define Devi_Numb_Devices_(Pltf,Num) clGetDeviceIDs(Pltf,CL_DEVICE_TYPE_ALL,0,NULL,Num)									//MemC_CL : Device Number Get
#define Devi_List_Devices_(Pltf,List,Listed,Entries) clGetDeviceIDs(Pltf,CL_DEVICE_TYPE_ALL,Entries,List,Listed)		//MemC_CL : Device List Get
#define Devi_Info_Device_(Devi,List,Num,type,Flag) clGetDeviceInfo(Devi,Flag,(Num)*sizeof(type),List,NULL)				//MemC_CL : Device Information Get
#define Devi_Size_Info_Device_(Devi,Size,Flag) clGetDeviceInfo(Devi,Flag,0,NULL,Size)									//MemC_CL : Device Information Size Get

#define Devi_Create_Context_(DeviceList,Number,Error) clCreateContext(NULL,Number,DeviceList,NULL,NULL,Error)			//MemC_CL : Context Memory Allocation
#define Devi_Delete_Context_(Context) if(Context){clReleaseContext(Context);(Context)=NULL;}							//MemC_CL : Context Memory Deallocation
#define Devi_Info_Context_(Cntx,List,Num,type,Flag) clGetContextInfo(Cntx,Flag,(Num)*sizeof(type),List,NULL)			//MemC_CL : Context Information Get
#define Devi_Size_Info_Context_(Cntx,Size,Flag) clGetContextInfo(Cntx,Flag,0,NULL,Size)									//MemC_CL : Context Information Size Get

#define Devi_Create_Program_(Cntx,List,Lng,Num,Error) clCreateProgramWithSource(Cntx,Num,List,Lng,Error)				//MemC_CL : Program Memory Allocation
#define Devi_Delete_Program_(Program) if(Program){clReleaseProgram(Program);(Program)=NULL;}							//MemC_CL : Program Memory Deallocation
#define Devi_Info_Program_(Prgm,List,Num,type,Flag) clGetProgramInfo(Prgm,Flag,(Num)*sizeof(type),List,NULL)			//MemC_CL : Program Information Get
#define Devi_Size_Info_Program_(Prgm,Size,Flag) clGetProgramInfo(Prgm,Flag,0,NULL,Size)									//MemC_CL : Program Information Size Get

#define Devi_Build_(Program,Option) clBuildProgram(Program,0,NULL,Option,NULL,NULL)											//MemC_CL : Program Build
#define Devi_Info_Build_(Devi,Prgm,List,Num,type,Flag) clGetProgramBuildInfo(Prgm,Devi,Flag,(Num)*sizeof(type),List,NULL)	//MemC_CL : Program Build Information Get
#define Devi_Size_Info_Build_(Devi,Prgm,Size,Flag) clGetProgramBuildInfo(Prgm,Devi,Flag,0,NULL,Size)						//MemC_CL : Program Build Information Size Get

#define Devi_Create_Kernel_(Program,KernelName,Error) clCreateKernel(Program,KernelName,Error)								//MemC_CL : Kernel Memory Allocation
#define Devi_Create_Kernel_Set_(Program,Set,Created,Entries) clCreateKernelsInProgram(Program,Entries,Set,Created)			//MemC_CL : Multiple Kernels Memory Allocation
#define Devi_Delete_Kernel_(Kernel) if(Kernel){clReleaseKernel(Kernel);(Kernel)=NULL;}										//MemC_CL : Kernel Memory Deallocation
#define Devi_Info_Kernel_(Krnl,List,Num,type,Flag) clGetKernelInfo(Krnl,Flag,(Num)*sizeof(type),List,NULL)					//MemC_CL : Kernel Information Get
#define Devi_Size_Info_Kernel_(Krnl,Size,Flag) clGetKernelInfo(Krnl,Flag,0,NULL,Size)										//MemC_CL : Kernel Information Size Get
#define Devi_Info_Work_(Devi,Krnl,List,Num,type,Flag) clGetKernelWorkGroupInfo(Krnl,Devi,Flag,(Num)*sizeof(type),List,NULL)	//MemC_CL : Kernel Work Group Information Get
#define Devi_Size_Info_Work_(Devi,Krnl,Size,Flag) clGetKernelWorkGroupInfo(Krnl,Devi,Flag,0,NULL,Size)						//MemC_CL : Kernel Work Group Information Size Get

#define Devi_Create_Queue_(Context,Device,Error) clCreateCommandQueue(Context,Device,0,Error)							//MemC_CL : Command Queue Memory Allocation
#define Devi_Delete_Queue_(Queue) if(Queue){clReleaseCommandQueue(Queue);(Queue)=NULL;}									//MemC_CL : Command Queue Memory Deallocation
#define Devi_Info_Queue_(Queue,List,Num,type,Flag) clGetCommandQueueInfo(Queue,Flag,(Num)*sizeof(type),List,NULL)		//MemC_CL : Command Queue Information Get
#define Devi_Size_Info_Queue_(Queue,Size,Flag) clGetCommandQueueInfo(Queue,Flag,0,NULL,Size)							//MemC_CL : Command Queue Information Size Get

#define Devi_Create_Buffer_(Context,Elements,type) _Devi_Create_Buffer_(Context,Elements,sizeof(type))					//MemC_CL : Buffer Object Memory Allocation
#define Devi_Create_Buffer_Sub_(Root,Offset,Elements,type) _Devi_Create_Buffer_Sub_(Root,Offset,Elements,sizeof(type))	//MemC_CL : Sub-Buffer Object Memory Allocation
#define Devi_Delete_Buffer_(Memory) if(Memory){clReleaseMemObject(Memory);(Memory)=NULL;}								//MemC_CL : Buffer or Sub-Buffer Object Memory Deallocation
#define Devi_Info_Buffer_(Bf,List,Num,type,Flag) clGetMemObjectInfo(Bf,Flag,(Num)*sizeof(type),List,NULL)				//MemC_CL : Buffer or Sub-Buffer Object Information Get
#define Devi_Size_Info_Buffer_(Bf,Size,Flag) clGetMemObjectInfo(Bf,Flag,0,NULL,Size)									//MemC_CL : Buffer or Sub-Buffer Object Information Size Get

#define Devi_Create_Event_(Context,Error) clCreateUserEvent(Context,Error)												//MemC_CL : Event Object Memory Allocation
#define Devi_Delete_Event_(Event,Error) {(Error)=_Devi_Delete_Event_(Event);if((Error)==CL_SUCCESS){(Event)=NULL;}}		//MemC_CL : Event Object Memory Deallocation
#define Devi_Event_Inc_(Event) clRetainEvent(Event)																		//MemC_CL : Event Count Increase
#define Devi_Event_Dec_(Event) clReleaseEvent(Event)																	//MemC_CL : Event Count Decrease
#define Devi_Info_Event_(Event,List,Num,type,Flag) clGetEventInfo(Event,Flag,(Num)*sizeof(type),List,NULL)				//MemC_CL : Event Object Information Get
#define Devi_Size_Info_Event_(Event,Size,Flag) clGetEventInfo(Event,Flag,0,NULL,Size)									//MemC_CL : Event Object Information Size Get
#define Devi_Wait_Event_(EventList,Number) clWaitForEvents(Number,EventList)											//MemC_CL : Waiting for Events to Complete

#define Devi_Init_(Q,Bf,Val,Ofs,Lng,type) clEnqueueFillBuffer(Q,Bf,Val,sizeof(type),(Ofs)*sizeof(type),(Lng)*sizeof(type),0,NULL,NULL)	//MemC_CL : Buffer Object Memory Initialization
#define Devi_Copy_(Q,S,T,SOfs,TOfs,Lng,SShp,TShp,Dims,type,Flag) _Devi_Copy_(Q,S,T,SOfs,TOfs,Lng,SShp,TShp,Dims,sizeof(type),Flag)		//MemC_CL : Buffer Object Memory Copy
#define Devi_Copy_1D_(Q,S,T,SOfs,TOfs,Lng,type,Flag) _Devi_Copy_1D_(Q,S,T,SOfs,TOfs,Lng,sizeof(type),Flag)								//MemC_CL : Buffer Object Memory 1D Copy

#define Devi_Flush_(Queue) clFlush(Queue)																				//MemC_CL : Command Queue Flush
#define Devi_Finish_(Queue) clFinish(Queue)																				//MemC_CL : Command Queue Finish

#define Devi_Karg_(Kernel,Order,Address,ByteSize) clSetKernelArg(Kernel,Order,ByteSize,Address)							//MemC_CL : Kernel Argument Set
#define Devi_Karg_Global_(Kernel,Order,BufferAddress) clSetKernelArg(Kernel,Order,sizeof(cl_mem),BufferAddress)			//MemC_CL : Kernel Argument Set (Buffer Object)
#define Devi_Karg_Local_(Kernel,Order,Elements,type) clSetKernelArg(Kernel,Order,(Elements)*sizeof(type),NULL)			//MemC_CL : Kernel Argument Set (Local Memory)
#define Devi_Karg_Value_(Kernel,Order,ValueAddress,type) clSetKernelArg(Kernel,Order,sizeof(type),ValueAddress)			//MemC_CL : Kernel Argument Set (Parameter Value)

#define Devi_KM_Type_G_(Karg,Order,type) _Devi_KM_Type_(Karg,Order,sizeof(type),0)										//MemC_CL : Kernel Manager Argument Type Set (Global Parameter)
#define Devi_KM_Type_L_(Karg,Order,type) _Devi_KM_Type_(Karg,Order,sizeof(type),1)										//MemC_CL : Kernel Manager Argument Type Set (Local Parameter)
#endif

#define MemC_Buffer_Elements 64		//MemClip : Maximum Number of Elements in "MemCBuffer"
#define MemC_Copy_Max_Dimension 8	//MemClip : Maximum Copy Dimension of "MemC_Copy_"
#ifdef __OPENCL_H
#define Devi_Copy_Max_Dimension 3	//MemC_CL : Maximum Copy Dimension of "Devi_Copy_"
#endif

//MemClip : Library Version
extern const char _PL_ MemClip;
//MemClip : Address Buffer [64]
extern void *_PL_ MemCBuffer;

//MemClip : Memory Allocation Check
//＊Return value is 0 for failure, 1 for success.
int MemC_Check_(const void _PL_*MemorySet,const size_t Count);
//MemClip : Memory Allocation
void *Byte_Alloc_(const size_t ByteSize);
//MemClip : Array Memory Allocation
//＊Return value is the allocated memory address.
void *MemC_Alloc_(const size_t _PL_ ArraySize,const size_t DimensionsNumber,const size_t ElementSize);
//MemClip : Batch Memory Deallocation
void MemC_Deloc_Set_(void **MemorySet,const size_t Count);

#ifdef __OPENCL_H
//MemC_CL : Default Number of Local Workers
//＊(local workers)[n]≤(maximum workers)[n]
//　∏(local workers)[n]≤(total workers)
void Devi_Work_Local_Default_(size_t _PL_ LocalWorkers,const size_t _PL_ WorkLength,const size_t _PL_ MaximumWorkers,const size_t TotalWorkers,const cl_uint Dimensions);
//MemC_CL : The Number of Work Groups Calculation
//＊(work groups)[n]＝ceil((work length)[n]÷(local workers)[n])
void Devi_Work_Groups_(size_t *MemC_Rst_ WorkGroups,const size_t *MemC_Rst_ WorkLength,const size_t *MemC_Rst_ LocalWorkers,const cl_uint Dimensions);
//MemC_CL : The Number of Global Workers Calculation
//＊(global workers)[n]＝(work groups)[n]×(local workers)[n]
void Devi_Work_Global_(size_t *MemC_Rst_ GlobalWorkers,const size_t *MemC_Rst_ WorkGroups,const size_t *MemC_Rst_ LocalWorkers,const cl_uint Dimensions);
//MemC_CL : Two's Power Calculation
//＊(bounded local workers)[n]＝exp₂(floor(log₂((local workers)[n])))
void Devi_Work_Safe_2_(size_t *MemC_Rst_ BoundedLocalWorkers,const size_t *MemC_Rst_ LocalWorkers,const cl_uint Dimensions);

//MemC_CL : Kernel Enqueue
//＊Maximum dimension is 3.
cl_int Devi_Kenq_(cl_command_queue const,cl_kernel const,const size_t _PL_ WorkGroups,const size_t _PL_ LocalWorkers,const size_t _PL_ GlobalOffset,const cl_uint Dimensions);

//MemC_CL : Queue Container Memory Allocation
devi_qc *Devi_QC_Create_(const cl_uint PlatformSelect,const cl_uint DeviceSelect);
//MemC_CL : Queue Container Memory Deallocation
void Devi_QC_Delete_(devi_qc*_PL_);

//MemC_CL : Kernel Manager Memory Allocation
devi_km *Devi_KM_Create_(cl_kernel const,const cl_uint KernelArguments,const cl_uint WorkDimension);
//MemC_CL : Kernel Manager Initialization
//＊Execute only one time for one karg manager.
cl_int Devi_KM_Init_(devi_km _PL_);
//MemC_CL : Kernel Manager Memory Deallocation
void Devi_KM_Delete_(devi_km*_PL_);

//MemC_CL : Kernel Manager Argument Save (Global)
void Devi_KM_Save_G_(DEVI_KM _PL_,const cl_uint Index,const void _PL_ Value);
//MemC_CL : Kernel Manager Argument Save (Local)
void Devi_KM_Save_L_(DEVI_KM _PL_,const cl_uint Index,const size_t Elements);
//MemC_CL : Kernel Manager Group Size Set
//＊WGroups[n]＝ceil(WLength[n]÷WLocals[n])
void Devi_KM_Work_Groups_(DEVI_KM _PL_);

//MemC_CL : Kernel Enqueue with Kernel Manager
cl_int Devi_KM_Enqueue_(cl_command_queue const,DEVI_KM _PL_);
#endif

void *_Line_Alloc_(const size_t,const size_t);
void *_Rect_Alloc_(const size_t,const size_t,const size_t);
void *_Cube_Alloc_(const size_t,const size_t,const size_t,const size_t);
void *_Tess_Alloc_(const size_t,const size_t,const size_t,const size_t,const size_t);

errno_t _Line_Pick_(const void _PL_,void _PL_,const size_t,const size_t,const size_t);
errno_t _Line_Fill_(const void _PL_,void _PL_,const size_t,const size_t,const size_t);

errno_t _MemC_Copy_(const void _PL_,void _PL_,const size_t _PL_,const size_t _PL_,const size_t _PL_,const size_t _PL_,const size_t _PL_,const size_t,const size_t);

size_t _Line_Assign_(void _PL_,const void _PL_,const size_t,const size_t,const size_t,const int);
size_t _MemC_Switch_(const void _PL_,const void _PL_ _PL_,const size_t*,const size_t,const size_t,const size_t);

#ifdef __OPENCL_H
cl_mem _Devi_Create_Buffer_(cl_context const,const size_t,const size_t);
cl_mem _Devi_Create_Buffer_Sub_(cl_mem const,const size_t,const size_t,const size_t);
cl_int _Devi_Delete_Event_(cl_event const);

cl_int _Devi_Copy_(cl_command_queue const,void _PL_,void _PL_,const size_t _PL_,const size_t _PL_,const size_t _PL_,const size_t _PL_,const size_t _PL_,const cl_uint,const size_t,DEVI_CP);
cl_int _Devi_Copy_1D_(cl_command_queue const,void _PL_,void _PL_,const size_t,const size_t,const size_t,const size_t,DEVI_CP);

cl_int _Devi_KM_Type_(DEVI_KM _PL_,const cl_uint,const size_t,const int);
#endif
#endif
