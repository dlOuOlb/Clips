/*------------------------------------------------------------------*/
/*	MemClip provides some memory allocating functions.				*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2018.10.16	*/
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

#define MemC_Fold_(Comment,...) (1)	//MemClip : Code Folding with #if and #endif Pre-processor.
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

#ifdef __dl
#error The macro "__dl" is already defined.
#else
#define __dl do			//MemClip : Macro Block Opening
#endif
#ifdef lb__
#error The macro "lb__" is already defined.
#else
#define lb__ while(0)	//MemClip : Macro Block Closing
#endif

#define MemC_Type_Rename_(oldtype,newtype,NEWTYPE) typedef oldtype newtype;typedef const oldtype NEWTYPE;	//MemClip : Macro for Type Renaming
#define MemC_Type_Declare_(spec,type,TYPE) typedef spec _##type type;typedef const spec _##type TYPE;		//MemClip : Macro for Type Declaration

#define MemC_Func_Declare_V_(Return,Func_,...) Return (*Func_)(__VA_ARGS__)		//MemClip : Function Pointer Variable Declaration
#define MemC_Func_Declare_C_(Return,Func_,...) Return (_PL_ Func_)(__VA_ARGS__)	//MemClip : Function Pointer Constant Declaration
#define MemC_Func_Casting_(Return,Func_,...) (Return(*)(__VA_ARGS__))(Func_)	//MemClip : Function Pointer Casting

#define MemC_Type_Func_Declare_(Return,func_type_,FUNC_TYPE_,...) typedef MemC_Func_Declare_V_(Return,func_type_,__VA_ARGS__);typedef MemC_Func_Declare_C_(Return,FUNC_TYPE_,__VA_ARGS__);	//MemClip : Macro for Function Type Declaration

#define MemC_DT_Define_(IScope,IIndex,IName,IFlag,ILink,IMeta,type) {.Scope=(IScope),.Index=(IIndex),.Flag=(IFlag),.SizeType=sizeof(type),.SizeName=sizeof(IName),.Name=(IName),.Link=(ILink),.Meta=(IMeta)}	//MemClip : Macro for MemC_DT Definition

#define MemC_Using_(type,Object,Creation,Deleter_) for(type *(_Temp)=FULL,_PL_ (Object)=(Creation);_Temp;(_Temp)=NULL,(Deleter_)((type**)&(Object)))if(Object)	//MemClip : Object Pointer Variable Use in Local Scope
#define MemC_Catch_ else																																		//MemClip : Failure Case for "MemC_Using_"
#endif

#if(MemC_Fold_(Definition:Types))
MemC_Type_Rename_(void,general,GENERAL);					//MemClip : Void Type
MemC_Type_Rename_(char,byte_08,BYTE_08);					//MemClip : Byte Type
MemC_Type_Rename_(int,integer,INTEGER);						//MemClip : Integer Type
MemC_Type_Rename_(size_t,address,ADDRESS);					//MemClip : Address Type
MemC_Type_Func_Declare_(general,func_p_,FUNC_P_,general);	//MemClip : Function Pointer Type

struct _memc_dt				//MemClip : Data Type Structure
{
	GENERAL _PL_ Scope;		//MemClip : Type Scope
	ADDRESS Index;			//MemClip : Index in Scope
	ADDRESS Flag;			//MemClip : Property Flag
	ADDRESS SizeType;		//MemClip : Type's Byte Size
	ADDRESS SizeName;		//MemClip : Name's Byte Size
	BYTE_08 _PL_ Name;		//MemClip : Type Name
	GENERAL _PL_ Link;		//MemClip : External Link
	GENERAL _PL_ Meta;		//MemClip : Meta Data
};
MemC_Type_Declare_(struct,memc_dt,MEMC_DT);	//MemClip : Data Type Structure

struct _memc_ms				//MemClip : Memory Slot Structure
{
	GENERAL _PL_ ID;		//MemClip : Identification
	MEMC_DT _PL_ Type;		//MemClip : Data Type
	ADDRESS Nums;			//MemClip : Number of Slots
	union _memc_vp			//MemClip : Variable Pointer Union
	{
		general *_PL_ P;	//MemClip : Access as Pointer Array
		address _PL_ V;		//MemClip : Access as Numeric Array
	}
	Slot;					//MemClip : Slot Access
};
MemC_Type_Declare_(struct,memc_ms,MEMC_MS);	//MemClip : Memory Slot Structure

struct _memc_mc			//MemClip : Host Memory Container Structure
{
	GENERAL _PL_ ID;	//MemClip : Identification
	MEMC_DT _PL_ Type;	//MemClip : Data Type
	ADDRESS Unit;		//MemClip : Type Size
	ADDRESS Dims;		//MemClip : Dimension (N)
	ADDRESS Lng1D;		//MemClip : Total Number of Elements
	ADDRESS _PL_ LngND;	//MemClip : Data Shape
	general _PL_ Acs1D;	//MemClip : 1-Dimensional Data Access
	GENERAL _PL_ AcsND;	//MemClip : N-Dimensional Data Access
};
MemC_Type_Declare_(struct,memc_mc,MEMC_MC);	//MemClip : Host Memory Container Structure

enum _memc_df				//MemClip : Memory Domain Flag Enumeration
{
	MemCDomainHost=0x48,	//MemClip : Memory in Host Domain
	MemCDomainDevice=0x44	//MemClip : Memory in Device Domain
};
MemC_Type_Declare_(enum,memc_df,MEMC_DF);	//MemClip : Memory Domain Flag Enumeration
static_assert(sizeof(memc_df)<=sizeof(address),"sizeof(enum) > sizeof(size_t)");

struct _memc_vc				//MemClip : Virtual Container Structure
{
	GENERAL _PL_ ID;		//MemClip : Identification
	MEMC_DT _PL_ Type;		//MemClip : Data Type
	ADDRESS Unit;			//MemClip : Type Size
	ADDRESS Dims;			//MemClip : Dimensions (N)
	ADDRESS Lng1D;			//MemClip : Total Number of Elements
	ADDRESS _PL_ LngND;		//MemClip : Data Shape
	const union _memc_ue	//MemClip : Union of Enumeration
	{
		MEMC_DF E;			//MemClip : Access as Enum Type
		ADDRESS N;			//MemClip : Access as Non-Enum Type
	}
	Domain;					//MemClip : Memory Domain Flag
	GENERAL _PL_ Hidden;	//MemClip : Hidden Linkage
};
MemC_Type_Declare_(struct,memc_vc,MEMC_VC);	//MemClip : Virtual Container Structure

enum _memc_te			//MemClip : Data Type Enumeration
{
	MemCTypeNone_00=0,	//MemClip : none_00
	MemCTypeByte_08=1,	//MemClip : byte_08 (char)
	MemCTypeInteger=2,	//MemClip : integer (int)
	MemCTypeAddress=3,	//MemClip : address (size_t)
	MemCTypes=4			//MemClip : The Number of Types
};
MemC_Type_Declare_(enum,memc_te,MEMC_TE);	//MemClip : Data Type Enumeration

#ifdef __OPENCL_H
struct _devi_qc						//MemC_CL : Queue Container Structure
{
	const cl_platform_id Platform;	//MemC_CL : Platform ID
	const cl_device_id Device;		//MemC_CL : Device ID
	const cl_context Context;		//MemC_CL : Context
	const cl_command_queue Queue;	//MemC_CL : Command Queue
};
MemC_Type_Declare_(struct,devi_qc,DEVI_QC);	//MemC_CL : Queue Container Structure

struct _devi_mc				//MemC_Cl : Device Memory Container Structure
{
	GENERAL _PL_ ID;		//MemC_Cl : Identification
	MEMC_DT _PL_ Type;		//MemC_CL : Data Type
	ADDRESS Unit;			//MemC_CL : Type Size
	ADDRESS Nums;			//MemC_CL : Number of Sub-Buffers
	ADDRESS LngS;			//MemC_CL : Length of a Sub-Buffer
	ADDRESS AlignS;			//MemC_CL : Byte Size of a Sub-Buffer
	const cl_mem BufT;		//MemC_CL : Main Buffer
	const cl_mem _PL_ BufS;	//MemC_CL : Sub-Buffer Address Array
};
MemC_Type_Declare_(struct,devi_mc,DEVI_MC);	//MemC_CL : Device Memory Container Structure

enum _devi_df					//MemC_CL : Device Memory Domain Flag Enumeration
{
	DeviDomainConstant=0x43,	//MemC_CL : Constant Memory
	DeviDomainGlobal=0x47,		//MemC_CL : Global Memory
	DeviDomainLocal=0x4C,		//MemC_CL : Local Memory
	DeviDomainPrivate=0x50		//MemC_CL : Private Memory
};
MemC_Type_Declare_(enum,devi_df,DEVI_DF);	//MemC_CL : Device Memory Domain Flag Enumeration
static_assert(sizeof(devi_df)<=sizeof(address),"sizeof(enum) > sizeof(size_t)");

struct _devi_km					//MemC_CL : Kernel Manager Structure
{
	GENERAL _PL_ ID;			//MemC_CL : Identification
	ADDRESS KArgs;				//MemC_CL : The Number of Kernel Arguments
	ADDRESS WDims;				//MemC_CL : Work Dimensions
	const cl_kernel Kernel;		//MemC_CL : Linked Kernel
	DEVI_DF _PL_ ArgFlag;		//MemC_CL : Argument Type Indicator
	ADDRESS _PL_ ArgSize;		//MemC_CL : Argument Byte Size Set
	union _memc_cp				//MemC_CL : Constant Pointer Union
	{
		GENERAL _PL_ _PL_ P;	//MemC_CL : Access as Pointer Array
		ADDRESS _PL_ V;			//MemC_CL : Access as Numeric Array
	}
	ArgAccess;					//MemC_CL : Argument Access
	GENERAL _PL_ ArgMemory;		//MemC_CL : Argument Data Storage
	address _PL_ WLocals;		//MemC_CL : The Number of Local Workers
	address _PL_ WGroups;		//MemC_CL : The Number of Work Groups
	address _PL_ WOffset;		//MemC_CL : Global Worker Offset
	address _PL_ WLength;		//MemC_CL : Work Length
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
#define MemC_Mute_(Argument) ((general)(Argument))			//MemClip : Unused Argument Warning Mute
#define MemC_Size_(type,Elements) ((Elements)*sizeof(type))	//MemClip : Byte Size of Elements

#define MemC_Errno_0 0				//MemClip : <No Error> Flag for "errno_t"
#define MemC_Copy_Max_Dimension 8	//MemClip : Maximum Copy Dimension of "MemC_Copy_"
#ifdef __OPENCL_H
#define Devi_Copy_Max_Dimension 3	//MemC_CL : Maximum Copy Dimension of "Devi_Copy_"
#endif
#endif

#if(MemC_Fold_(Declaration:Global Constants))
//MemClip : Library Version
extern BYTE_08 _PL_ MemClip;
//MemClip : Self Reference
extern GENERAL _PL_ MemCrux;
//MemClip : Type Descriptor Set
//＊Access with MemCTypeByte … MemCTypeAddress
extern MEMC_DT _PL_ _PL_ MemCType;
#endif

#if(MemC_Fold_(Declaration:Memory Functions))
//MemClip : Memory Allocation Check
//＊Return value is 0 for failure, 1 for success.
integer MemC_Check_(GENERAL _PL_ *MemorySet,ADDRESS Count);

//MemClip : Memory Deallocation
#define MemC_Deloc_(Memory) __dl{if(Memory){free(Memory);(Memory)=NULL;}}lb__
//MemClip : Batch Memory Deallocation
general MemC_Deloc_Set_(general **MemorySet,ADDRESS Count);

//MemClip : Array Memory Allocation - Deallocate with "MemC_Deloc_"
//＊Return value is the allocated memory address.
general *MemC_Alloc_(ADDRESS _PL_ ArraySize,ADDRESS DimensionsNumber,ADDRESS ElementSize);
//MemClip : Memory Allocation - Deallocate with "MemC_Deloc_"
general *MemC_Alloc_Byte_(ADDRESS ByteSize);
//MemClip : Unit Memory Allocation - Deallocate with "MemC_Deloc_"
#define MemC_Alloc_Unit_(type) (type*)MemC_Alloc_Byte_(sizeof(type))
//MemClip : 1D Array Memory Allocation - Deallocate with "MemC_Deloc_
general *_MemC_Alloc_1D_(ADDRESS,ADDRESS);
#define MemC_Alloc_1D_(Z,type) (type*)_MemC_Alloc_1D_(Z,sizeof(type))
//MemClip : 2D Array Memory Allocation - Deallocate with "MemC_Deloc_
general *_MemC_Alloc_2D_(ADDRESS,ADDRESS,ADDRESS);
#define MemC_Alloc_2D_(Y,Z,type) (type**)_MemC_Alloc_2D_(Y,Z,sizeof(type))
//MemClip : 3D Array Memory Allocation - Deallocate with "MemC_Deloc_
general *_MemC_Alloc_3D_(ADDRESS,ADDRESS,ADDRESS,ADDRESS);
#define MemC_Alloc_3D_(X,Y,Z,type) (type***)_MemC_Alloc_3D_(X,Y,Z,sizeof(type))
//MemClip : 4D Array Memory Allocation - Deallocate with "MemC_Deloc_
general *_MemC_Alloc_4D_(ADDRESS,ADDRESS,ADDRESS,ADDRESS,ADDRESS);
#define MemC_Alloc_4D_(W,X,Y,Z,type) (type****)_MemC_Alloc_4D_(W,X,Y,Z,sizeof(type))

//MemClip : Data Reset in Byte Size
#define MemC_Clear_Byte_(Memory,ByteSize) memset(Memory,0,ByteSize)
//MemClip : Unit Data Reset
#define MemC_Clear_Unit_(Unit) memset(Unit,0,sizeof(*(Unit)))
//MemClip : 1D Array Data Reset
#define MemC_Clear_1D_(Line,Elements) memset(Line,0,(Elements)*sizeof(*(Line)))

//MemClip : Data Copy in Byte Size
#define MemC_Copy_Byte_(Source,Target,ByteSize) memcpy_s(Target,ByteSize,Source,ByteSize)
//MemClip : Unit Data Copy
#define MemC_Copy_Unit_(Source,Target) ((sizeof(*(Source))==sizeof(*(Target)))?(memcpy_s(Target,sizeof(*(Target)),Source,sizeof(*(Source)))):(EINVAL))
//MemClip : 1D Array Data Copy
#define MemC_Copy_1D_(Source,Target,Elements) ((sizeof(*(Source))==sizeof(*(Target)))?(memcpy_s(Target,(Elements)*sizeof(*(Target)),Source,(Elements)*sizeof(*(Source)))):(EINVAL))

//MemClip : Data Compare in Byte Size
#define MemC_Compare_Byte_(MemoryA,MemoryB,ByteSize) memcmp(MemoryA,MemoryB,ByteSize)
//MemClip : Unit Data Compare
#define MemC_Compare_Unit_(UnitA,UnitB) memcmp(UnitA,UnitB,sizeof(*(UnitA)))
//MemClip : 1D Array Data Compare
#define MemC_Compare_1D_(LineA,LineB,Elements) memcmp(LineA,LineB,(Elements)*sizeof(*(LineA)))

//MemClip : Array Data Copy
errno_t _MemC_Copy_(GENERAL _PL_ SourceArray,general _PL_ TargetArray,ADDRESS _PL_ SourceOffset,ADDRESS _PL_ TargetOffset,ADDRESS _PL_ CopyLength,ADDRESS _PL_ SourceShape,ADDRESS _PL_ TargetShape,ADDRESS Dimensions,ADDRESS TypeSize);
#define MemC_Copy_(S,T,SOfs,TOfs,Lng,SShp,TShp,Dims) ((sizeof(*(S))==sizeof(*(T)))?(_MemC_Copy_(S,T,SOfs,TOfs,Lng,SShp,TShp,Dims,sizeof(*(S)))):(EINVAL))
//MemClip : Array Data Copy with Step
errno_t MemC_Copy_Step_(GENERAL _PL_ SourceArray,general _PL_ TargetArray,ADDRESS CopyNums,ADDRESS SourceStepBytes,ADDRESS TargetStepBytes,ADDRESS EachCopyBytes);

//MemClip : Array Data Reformation - See also "MemC_Reform_Shape_"
errno_t _MemC_Reform_(GENERAL _PL_ SourceArray,general _PL_ TargetArray,ADDRESS _PL_ SourceShape,ADDRESS _PL_ ReformingAxis,address Dimensions,address TypeSize);
#define MemC_Reform_(S,T,SShp,Axis,Dims) ((sizeof(*(S))==sizeof(*(T)))?(_MemC_Reform_(S,T,SShp,Axis,Dims,sizeof(*(S)))):(EINVAL))
//MemClip : Reformed Target Shape Calculation
//＊TargetShape[ReformingAxis[dim]] = SourceShape[dim]
integer MemC_Reform_Shape_(ADDRESS _PL_ SourceShape,ADDRESS _PL_ ReformingAxis,address _PL_ TargetShape,ADDRESS Dimensions);

//MemClip : Object Sorting
//＊Required ReferTable size is Count×sizeof(general*) bytes.
//＊If IndexTable is not NULL, then its required size is Count×sizeof(address) bytes.
//＊Required BufferSpace size is 2×Count×sizeof(address) bytes.
//＊If Comp_(ReferTable[m],ReferTable[n]) is not 0, then those two will be swapped during the process.
errno_t MemC_Sort_(MemC_Func_Declare_C_(integer,Comp_,GENERAL _PL_,GENERAL _PL_),GENERAL *_PL_ ReferTable,address _PL_ IndexTable,address _PL_ BufferSpace,ADDRESS Count);

//MemClip : 1D Array Data Preset
errno_t _MemC_Init_1D_(general _PL_ Memory,GENERAL _PL_ Tile,ADDRESS Number,ADDRESS TypeSize);
#define MemC_Init_1D_(Memory,Tile,Elements) ((sizeof(*(Memory))==sizeof(*(Tile)))?(_MemC_Init_1D_(Memory,Tile,Elements,sizeof(*(Tile)))):(EINVAL))

//MemClip :  1D Array Uniform or Non-Uniform Interval Addressing
address _MemC_Assign_1D_(general _PL_ Indexer,GENERAL _PL_ Indexed,ADDRESS Interval,ADDRESS Indices,ADDRESS TypeSize,INTEGER Mode);
#define MemC_Assign_1D_U_(Address,Line,Jump,Number) _MemC_Assign_1D_(Address,Line,Jump,Number,sizeof(*(Line)),0)
#define MemC_Assign_1D_N_(Address,Line,Jump,Number) _MemC_Assign_1D_(Address,Line,(address)(Jump),Number,sizeof(*(Line)),1)
#endif

#if(MemC_Fold_(Declaration:MemClip Structure Functions))
#if(MemC_Fold_(Part:MemC_MS))
//MemClip : Memory Slot Memory Allocation - Deallocate with "MemC_MS_Delete_"
//＊Nums = SlotsNumber
memc_ms *MemC_MS_Create_(GENERAL _PL_ Identification,ADDRESS SlotsNumber);
//MemClip : Memory Slot Memory Deallocation
general MemC_MS_Delete_(memc_ms *_PL_ MemorySlot);

//MemClip : Memory Slot Memory Occupation
address MemC_MS_Size_(MEMC_MS _PL_ MemorySlot);
//MemClip : Memory Slot Memory Type Change
integer MemC_MS_Change_(MEMC_MS _PL_ MemorySlot,MEMC_DT _PL_ MemoryType);

//MemClip : Memory Slot Data Reset
integer MemC_MS_Init_(MEMC_MS _PL_ MemorySlot);
//MemClip : Memory Slot NULL Check
//＊Count = MemorySlot -> Slot.V[0]
//　MemorySet = { P[1], P[2], ..., P[Count] | P = MemorySlot -> Slot.P }
//＊Mode 0 : Return value is 1 for all NULLs, otherwise 0.
//＊Mode 1 : Return value is 0 for any NULLs, otherwise 1.
integer MemC_MS_Null_(MEMC_MS _PL_ MemorySlot,INTEGER CheckMode);

//MemClip : Just kidding!
integer MemC_MS_Joke_(MEMC_MS _PL_ MemorySlot);
//MemClip : Oops!
integer MemC_MS_Oops_(MEMC_MS _PL_ MemorySlot);

#define MemC_MS_Dims_0_(MS) __dl{address _PL_ _V=(MS)->Slot.V;_V[0]=0;}lb__
#define MemC_MS_Dims_1_(MS,D0) __dl{address _PL_ _V=(MS)->Slot.V;_V[0]=1;_V[1]=(D0);}lb__
#define MemC_MS_Dims_2_(MS,D0,D1) __dl{address _PL_ _V=(MS)->Slot.V;_V[0]=2;_V[1]=(D0);_V[2]=(D1);}lb__
#define MemC_MS_Dims_3_(MS,D0,D1,D2) __dl{address _PL_ _V=(MS)->Slot.V;_V[0]=3;_V[1]=(D0);_V[2]=(D1);_V[3]=(D2);}lb__
#define MemC_MS_Dims_4_(MS,D0,D1,D2,D3) __dl{address _PL_ _V=(MS)->Slot.V;_V[0]=4;_V[1]=(D0);_V[2]=(D1);_V[3]=(D2);_V[4]=(D3);}lb__
#define MemC_MS_Dims_5_(MS,D0,D1,D2,D3,D4) __dl{address _PL_ _V=(MS)->Slot.V;_V[0]=5;_V[1]=(D0);_V[2]=(D1);_V[3]=(D2);_V[4]=(D3);_V[5]=(D4);}lb__
#define MemC_MS_Dims_6_(MS,D0,D1,D2,D3,D4,D5) __dl{address _PL_ _V=(MS)->Slot.V;_V[0]=6;_V[1]=(D0);_V[2]=(D1);_V[3]=(D2);_V[4]=(D3);_V[5]=(D4);_V[6]=(D5);}lb__
#define MemC_MS_Dims_7_(MS,D0,D1,D2,D3,D4,D5,D6) __dl{address _PL_ _V=(MS)->Slot.V;_V[0]=7;_V[1]=(D0);_V[2]=(D1);_V[3]=(D2);_V[4]=(D3);_V[5]=(D4);_V[6]=(D5);_V[7]=(D6);}lb__
#endif
#if(MemC_Fold_(Part:MemC_MC))
//MemClip : Memory Container Memory Allocation - Deallocate with "MemC_MC_Delete_"
//＊Unit = TypeInfo -> SizeType
//　Dims = ShapeInfo -> Slot.V[0]
//　LngND = { V[1], V[2], ..., V[Dims] | V = ShapeInfo -> Slot.V }
memc_mc *MemC_MC_Create_(GENERAL _PL_ Identification,MEMC_MS _PL_ ShapeInfo,MEMC_DT _PL_ TypeInfo);
//MemClip : Memory Container Memory Deallocation
general MemC_MC_Delete_(memc_mc *_PL_ MemoryContainer);

//MemClip : Memory Container Memory Occupation
address MemC_MC_Size_(MEMC_MC _PL_ MemoryContainer);
//MemClip : Memory Container Shape Information Copy
//＊ShapeInfo -> Slot.V[0] = MemoryContainer -> Dims
//　{ V[1], V[2], ..., V[Dims] | V = ShapeInfo -> Slot.V } = MemoryContainer -> LngND
integer MemC_MC_Form_(MEMC_MC _PL_ MemoryContainer,MEMC_MS _PL_ ShapeInfo);
//MemClip : Memory Container Data Type Change
integer MemC_MC_Change_(MEMC_MC _PL_ MemoryContainer,MEMC_DT _PL_ DataType);
#endif
#endif

#if(MemC_Fold_(Declaration:OpenCL Functions))
#ifdef __OPENCL_H
#if(MemC_Fold_(Part:Platform))
//MemC_CL : Platform Number Get
#define Devi_Numb_Platforms_(Num) clGetPlatformIDs(0,NULL,Num)
//MemC_CL : Platform List Get
#define Devi_List_Platforms_(List,Listed,Entries) clGetPlatformIDs(Entries,List,Listed)
//MemC_CL : Platform Information Get
#define Devi_Info_Platform_(Pltf,List,Num,Flag) clGetPlatformInfo(Pltf,Flag,(Num)*sizeof(*(List)),List,NULL)
//MemC_CL : Platform Information Size Get
#define Devi_Size_Info_Platform_(Pltf,Size,Flag) clGetPlatformInfo(Pltf,Flag,0,NULL,Size)
#endif
#if(MemC_Fold_(Part:Device))
//MemC_CL : Device Number Get
#define Devi_Numb_Devices_(Pltf,Num) clGetDeviceIDs(Pltf,CL_DEVICE_TYPE_ALL,0,NULL,Num)
//MemC_CL : Device List Get
#define Devi_List_Devices_(Pltf,List,Listed,Entries) clGetDeviceIDs(Pltf,CL_DEVICE_TYPE_ALL,Entries,List,Listed)
//MemC_CL : Device Information Get
#define Devi_Info_Device_(Devi,List,Num,Flag) clGetDeviceInfo(Devi,Flag,(Num)*sizeof(*(List)),List,NULL)
//MemC_CL : Device Information Size Get
#define Devi_Size_Info_Device_(Devi,Size,Flag) clGetDeviceInfo(Devi,Flag,0,NULL,Size)
#endif
#if(MemC_Fold_(Part:Context))
//MemC_CL : Context Memory Allocation - Deallocate with "Devi_Delete_Context_"
#define Devi_Create_Context_(DeviceList,Number,Error) clCreateContext(NULL,Number,DeviceList,NULL,NULL,Error)
//MemC_CL : Context Memory Deallocation
#define Devi_Delete_Context_(Context) __dl{if(Context){clReleaseContext(Context);(Context)=NULL;}}lb__
//MemC_CL : Context Information Get
#define Devi_Info_Context_(Cntx,List,Num,Flag) clGetContextInfo(Cntx,Flag,(Num)*sizeof(*(List)),List,NULL)
//MemC_CL : Context Information Size Get
#define Devi_Size_Info_Context_(Cntx,Size,Flag) clGetContextInfo(Cntx,Flag,0,NULL,Size)
#endif
#if(MemC_Fold_(Part:Program))
//MemC_CL : Program Memory Allocation - Deallocate with "Devi_Delete_Program_"
#define Devi_Create_Program_Source_(Cntx,SrcList,SrcLng,SrcNum,Error) clCreateProgramWithSource(Cntx,SrcNum,SrcList,SrcLng,Error)
//MemC_CL : Program Memory Allocation - Deallocate with "Devi_Delete_Program_"
#define Devi_Create_Program_Binary_(DeviList,Cntx,BinList,BinLng,BinNum,Error) clCreateProgramWithBinary(Cntx,BinNum,DeviList,BinLng,BinList,NULL,Error)
//MemC_CL : Program Memory Deallocation
#define Devi_Delete_Program_(Program) __dl{if(Program){clReleaseProgram(Program);(Program)=NULL;}}lb__
//MemC_CL : Program Information Get
#define Devi_Info_Program_(Prgm,List,Num,Flag) clGetProgramInfo(Prgm,Flag,(Num)*sizeof(*(List)),List,NULL)
//MemC_CL : Program Information Size Get
#define Devi_Size_Info_Program_(Prgm,Size,Flag) clGetProgramInfo(Prgm,Flag,0,NULL,Size)

//MemC_CL : Program Build
#define Devi_Build_(Program,Option) clBuildProgram(Program,0,NULL,Option,NULL,NULL)
//MemC_CL : Program Build Information Get
#define Devi_Info_Build_(Devi,Prgm,List,Num,Flag) clGetProgramBuildInfo(Prgm,Devi,Flag,(Num)*sizeof(*(List)),List,NULL)
//MemC_CL : Program Build Information Size Get
#define Devi_Size_Info_Build_(Devi,Prgm,Size,Flag) clGetProgramBuildInfo(Prgm,Devi,Flag,0,NULL,Size)
#endif
#if(MemC_Fold_(Part:Command Queue))
//MemC_CL : Command Queue Memory Allocation - Deallocate with "Devi_Delete_Queue_"
#define Devi_Create_Queue_(Context,Device,Error) clCreateCommandQueueWithProperties(Context,Device,NULL,Error)
//MemC_CL : Command Queue Memory Deallocation
#define Devi_Delete_Queue_(Queue) __dl{if(Queue){clReleaseCommandQueue(Queue);(Queue)=NULL;}}lb__
//MemC_CL : Command Queue Information Get
#define Devi_Info_Queue_(Queue,List,Num,Flag) clGetCommandQueueInfo(Queue,Flag,(Num)*sizeof(*(List)),List,NULL)
//MemC_CL : Command Queue Information Size Get
#define Devi_Size_Info_Queue_(Queue,Size,Flag) clGetCommandQueueInfo(Queue,Flag,0,NULL,Size)

//MemC_CL : Command Queue Flush
#define Devi_Flush_(Queue) clFlush(Queue)
//MemC_CL : Command Queue Finish - Use for Synchronization
#define Devi_Finish_(Queue) clFinish(Queue)
#endif
#if(MemC_Fold_(Part:Kernel))
//MemC_CL : Kernel Memory Allocation - Deallocate with "Devi_Delete_Kernel_"
#define Devi_Create_Kernel_(Program,KernelName,Error) clCreateKernel(Program,KernelName,Error)
//MemC_CL : Multiple Kernels Memory Allocation
#define Devi_Create_Kernel_Set_(Program,Set,Created,Entries) clCreateKernelsInProgram(Program,Entries,Set,Created)
//MemC_CL : Kernel Memory Deallocation
#define Devi_Delete_Kernel_(Kernel) __dl{if(Kernel){clReleaseKernel(Kernel);(Kernel)=NULL;}}lb__
//MemC_CL : Kernel Information Get
#define Devi_Info_Kernel_(Krnl,List,Num,Flag) clGetKernelInfo(Krnl,Flag,(Num)*sizeof(*(List)),List,NULL)
//MemC_CL : Kernel Information Size Get
#define Devi_Size_Info_Kernel_(Krnl,Size,Flag) clGetKernelInfo(Krnl,Flag,0,NULL,Size)
//MemC_CL : Kernel Work Group Information Get
#define Devi_Info_Work_(Devi,Krnl,List,Num,Flag) clGetKernelWorkGroupInfo(Krnl,Devi,Flag,(Num)*sizeof(*(List)),List,NULL)
//MemC_CL : Kernel Work Group Information Size Get
#define Devi_Size_Info_Work_(Devi,Krnl,Size,Flag) clGetKernelWorkGroupInfo(Krnl,Devi,Flag,0,NULL,Size)

//MemC_CL : Kernel Argument Set
#define Devi_Karg_(Kernel,Order,Address,ByteSize) clSetKernelArg(Kernel,Order,ByteSize,Address)

//MemC_CL : Kernel Enqueue
//＊Maximum dimension is 3.
cl_int Devi_Kenq_(cl_command_queue const,cl_kernel const,ADDRESS _PL_ WorkGroups,ADDRESS _PL_ LocalWorkers,ADDRESS _PL_ GlobalOffset,const cl_uint Dimensions);
#endif
#if(MemC_Fold_(Part:Buffer))
//MemC_CL : Buffer Object Memory Allocation - Deallocate with "Devi_Delete_Buffer_"
cl_mem _Devi_Create_Buffer_(cl_context const,ADDRESS,ADDRESS,cl_int _PL_ Err);
#define Devi_Create_Buffer_(Context,Elements,type,Error) _Devi_Create_Buffer_(Context,Elements,sizeof(type),Error)
//MemC_CL : OpenGL Shared Buffer Object Memory Allocation - Deallocate with "Devi_Delete_Buffer_"
cl_mem _Devi_Create_Buffer_GL_(cl_context const,const cl_GLuint,cl_int _PL_ Err);
#define Devi_Create_Buffer_GL_(Context,GLBuffer,Error) _Devi_Create_Buffer_GL_(Context,GLBuffer,Error)
//MemC_CL : Sub-Buffer Object Memory Allocation - Deallocate with "Devi_Delete_Buffer_"
cl_mem _Devi_Create_Buffer_Sub_(cl_mem const,ADDRESS,ADDRESS,ADDRESS,cl_int _PL_ Err);
#define Devi_Create_Buffer_Sub_(Root,Offset,Elements,type,Error) _Devi_Create_Buffer_Sub_(Root,Offset,Elements,sizeof(type),Error)
//MemC_CL : Buffer or Sub-Buffer Object Memory Deallocation
#define Devi_Delete_Buffer_(Memory) __dl{if(Memory){clReleaseMemObject(Memory);(Memory)=NULL;}}lb__
//MemC_CL : Buffer or Sub-Buffer Object Information Get
#define Devi_Info_Buffer_(Bf,List,Num,type,Flag) clGetMemObjectInfo(Bf,Flag,(Num)*sizeof(type),List,NULL)
//MemC_CL : Buffer or Sub-Buffer Object Information Size Get
#define Devi_Size_Info_Buffer_(Bf,Size,Flag) clGetMemObjectInfo(Bf,Flag,0,NULL,Size)

//MemC_CL : Buffer Object Asynchronous Memory Initialization - Synchronize with "Devi_Finish_"
#define Devi_Init_(Q,Bf,Val,Ofs,Lng,type) clEnqueueFillBuffer(Q,Bf,Val,sizeof(type),(Ofs)*sizeof(type),(Lng)*sizeof(type),0,NULL,NULL)
//MemC_CL : Buffer Object Asynchronous Memory Copy - Synchronize with "Devi_Finish_"
cl_int _Devi_Copy_(cl_command_queue const Queue,general _PL_ SourceBuffer,general _PL_ TargetBuffer,ADDRESS _PL_ SourceOffset,ADDRESS _PL_ TargetOffset,ADDRESS _PL_ CopyLength,ADDRESS _PL_ SourceShape,ADDRESS _PL_ TargetShape,const cl_uint Dimensions,ADDRESS TypeSize,DEVI_CF Mode);
#define Devi_Copy_(Q,S,T,SOfs,TOfs,Lng,SShp,TShp,Dims,type,Flag) _Devi_Copy_(Q,S,T,SOfs,TOfs,Lng,SShp,TShp,Dims,sizeof(type),Flag)
//MemC_CL : Buffer Object Asynchronous Memory 1D Copy - Synchronize with "Devi_Finish_"
cl_int _Devi_Copy_1D_(cl_command_queue const Queue,general _PL_ SourceBuffer,general _PL_ TargetBuffer,ADDRESS SourceOffset,ADDRESS TargetOffset,ADDRESS CopyLength,ADDRESS TypeSize,DEVI_CF Mode);
#define Devi_Copy_1D_(Q,S,T,SOfs,TOfs,Lng,type,Flag) _Devi_Copy_1D_(Q,S,T,SOfs,TOfs,Lng,sizeof(type),Flag)
#endif
#if(MemC_Fold_(Part:Event))
//MemC_CL : Event Object Memory Allocation - Deallocate with "Devi_Delete_Event_"
#define Devi_Create_Event_(Context,Error) clCreateUserEvent(Context,Error)
//MemC_CL : Event Object Memory Deallocation
cl_int _Devi_Delete_Event_(cl_event const);
#define Devi_Delete_Event_(Event,Error) __dl{(Error)=_Devi_Delete_Event_(Event);if((Error)==CL_SUCCESS){(Event)=NULL;}}lb__
//MemC_CL : Event Count Increase
#define Devi_Event_Inc_(Event) clRetainEvent(Event)
//MemC_CL : Event Count Decrease
#define Devi_Event_Dec_(Event) clReleaseEvent(Event)
//MemC_CL : Event Object Information Get
#define Devi_Info_Event_(Event,List,Num,Flag) clGetEventInfo(Event,Flag,(Num)*sizeof(*(List)),List,NULL)
//MemC_CL : Event Object Information Size Get
#define Devi_Size_Info_Event_(Event,Size,Flag) clGetEventInfo(Event,Flag,0,NULL,Size)
//MemC_CL : Waiting for Events to Complete
#define Devi_Wait_Event_(EventList,Number) clWaitForEvents(Number,EventList)
#endif

#if(MemC_Fold_(Part:Devi_QC))
//MemC_CL : Queue Container Memory Allocation - Deallocate with "Devi_QC_Delete_"
devi_qc *Devi_QC_Create_(const cl_uint PlatformSelect,const cl_uint DeviceSelect);
//MemC_CL : Queue Container Memory Deallocation
general Devi_QC_Delete_(devi_qc *_PL_ QueueContainer);
#endif
#if(MemC_Fold_(Part:Devi_MC))
//MemC_CL : Memory Container Memory Allocation - Deallocate with "Devi_MC_Delete_"
devi_mc *Devi_MC_Create_(GENERAL _PL_ Identification,cl_context const Context,ADDRESS BuffersNumber,ADDRESS EachLength,MEMC_DT _PL_ TypeInfo,cl_int *Error);
//MemC_CL : Memory Container Memory Deallocation
general Devi_MC_Delete_(devi_mc *_PL_ MemoryContainer);
//MemClip : Memory Container Data Type Change
integer Devi_MC_Change_(DEVI_MC _PL_ MemoryContainer,MEMC_DT _PL_ DataType);
#endif
#if(MemC_Fold_(Part:Devi_KM))
//MemC_CL : Kernel Manager Memory Allocation - Deallocate with "Devi_KM_Delete_"
devi_km *Devi_KM_Create_(GENERAL _PL_ Identification,ADDRESS KernelArguments,ADDRESS WorkDimension);
//MemC_CL : Kernel Manager Argument Type Setting for Constant, Global, Local, or Private Domain
cl_int _Devi_KM_Type_(DEVI_KM _PL_ KernelManager,ADDRESS Index,ADDRESS TypeSize,DEVI_DF Mode);
#define Devi_KM_Type_C_(KM,Index) _Devi_KM_Type_(KM,Index,0,DeviDomainConstant)
#define Devi_KM_Type_G_(KM,Index) _Devi_KM_Type_(KM,Index,0,DeviDomainGlobal)
#define Devi_KM_Type_L_(KM,Index,type) _Devi_KM_Type_(KM,Index,sizeof(type),DeviDomainLocal)
#define Devi_KM_Type_P_(KM,Index,type) _Devi_KM_Type_(KM,Index,sizeof(type),DeviDomainPrivate)
//MemC_CL : Kernel Manager Initialization
//＊Execute only one time for one kernel manager, after type setting with "Devi_KM_Type_*_".
cl_int Devi_KM_Init_(devi_km _PL_ KernelManager,cl_kernel const Kernel);
//MemC_CL : Kernel Manager Memory Deallocation
general Devi_KM_Delete_(devi_km *_PL_ KernelManager);

//MemC_CL : Kernel Manager Argument Save
//＊If KM -> Flag[Order] == DeviDomainLocal,
//　then pass the number of local buffer elements as the token,
//　otherwise pass the address of the argument as the token.
cl_int Devi_KM_Save_(DEVI_KM _PL_ KM,ADDRESS Order,ADDRESS Token);
//MemC_CL : Kernel Enqueue with Kernel Manager
cl_int Devi_KM_Enqueue_(cl_command_queue const Queue,DEVI_KM _PL_ KernelManager);
#endif
#endif
#endif

#if(MemC_Fold_(Declaration:MemClip Fused Functions))
//MemClip : Virtual Container Memory Allocation - Deallocate with "MemC_VC_Delete_"
//＊V = EntryInfo -> Slot.V
//　Dims = ( MC -> Dims ) - V[0]
//　LngND = ( MC -> LngND ) + V[0]
//　Hidden = MC -> AcsND[V[1]][V[2]][...][V[V[0]]]
memc_vc *MemC_VC_Create_(GENERAL _PL_ Identification,MEMC_MC _PL_ MemoryContainer,MEMC_MS _PL_ EntryInfo);
#ifdef __OPENCL_H
//MemC_CL : Virtual Container Memory Allocation - Deallocate with "MemC_VC_Delete_"
//＊Dims = ShapeInfo -> Slot.V[0]
//　LngND = { V[1], V[2], ..., V[Dims] | V = ShapeInfo -> Slot.V }
//　Hidden = MC -> BufS[ SubBufferSelect ]
memc_vc *Devi_VC_Create_(GENERAL _PL_ Identification,DEVI_MC _PL_ MemoryContainer,ADDRESS SubBufferSelect,MEMC_MS _PL_ ShapeInfo);
#endif
//MemClip : Virtual Container Memory Deallocation
general MemC_VC_Delete_(memc_vc *_PL_ VirtualContainer);

//MemClip : Virtual Container Memory Occupation
address MemC_VC_Size_(MEMC_VC _PL_ VC);
//MemClip : Virtual Container Data Type Change
integer MemC_VC_Change_(MEMC_VC _PL_ VirtualContainer,MEMC_DT _PL_ DataType);

//MemClip : Virtual Container's Virtual Member :: VC->AcsND
//＊Host Domain Only
general *MemC_VC_Member_AcsND_(MEMC_VC _PL_ VirtualContainer);
//MemClip : Virtual Container's Virtual Member :: VC->Acs1D
//＊Host Domain Only
general *MemC_VC_Member_Acs1D_(MEMC_VC _PL_ VirtualContainer);
#ifdef __OPENCL_H
//MemC_CL : Virtual Container's Virtual Member :: VC->BufS
//＊Device Domain Only
cl_mem Devi_VC_Member_BufS_(MEMC_VC _PL_ VirtualContainer);
#endif
//MemClip : Virtual Container Memory Access
//＊V = AccessInfo -> Slot.V
//＊Host Domain :
//　V[0] = &( VC -> AcsND[V[1]][V[2]]...[V[Dims]] )
//＊Device Domain :
//　V[0] = &( VC -> AcsND[V[1]][V[2]]...[V[Dims]] ) - &( VC -> Acs1D[0] )
//　Note that the returned offset V[0] is not in byte unit.
//＊Return value is 1 for success, 0 for failure.
integer MemC_VC_Access_(MEMC_VC _PL_ VirtualContainer,MEMC_MS _PL_ AccessInfo);

//MemClip : Virtual Container Data Reset
//＊Return value is 1 for success, 0 for failure.
integer MemC_VC_Init_(general _PL_ Queue,MEMC_VC _PL_ VirtualContainer);
//MemClip : Virtual Container Data Copy
//＊CopyDims = CopyInfo -> Slot.V[0] ≤ min { SourceDims, TargetDims }
//　CopyLngND = { V[1], V[2], ..., V[CopyDims] | V = CopyInfo -> Slot.V }
//　SourceOffset = { E[1], E[2], ..., E[SourceDims] | E = V + CopyDims }
//　TargetOffset = { F[1], F[2], ..., F[TargetDims] | F = E + SourceDims }
//＊Type checker should return 1 for compatible types, 0 for incompatible types.
//＊Return value is 1 for success, 0 for failure.
integer MemC_VC_Copy_(general _PL_ Queue,MEMC_VC _PL_ SourceContainer,MEMC_VC _PL_ TargetContainer,MEMC_MS _PL_ CopyInfo);
#endif

#if(MemC_Fold_(Declaration:Other Functions))
//MemClip : Nothing
general MemC_Void_(general);

//MemClip : Table Indexing
//＊Table[idx]＝Mode？＆(Table[idx])：idx
general MemC_Self_(address *_R_ Table,ADDRESS Count,INTEGER Mode);

//MemClip : Key Finding for Switch Operation
address _MemC_Switch_(GENERAL _PL_ Key,GENERAL _PL_ _PL_ TblRf,ADDRESS* LngRf,ADDRESS LngKey,ADDRESS NumRf,ADDRESS TypeSize);
#define MemC_Switch_(Key,RefBook,RefLng,KeyLng,Refs) _MemC_Switch_(Key,RefBook,RefLng,KeyLng,Refs,sizeof(**(RefBoook)))

//MemClip : Two Number Addition
//＊Return value is A＋B for no overflow, 0 for overflow.
address _MemC_Size_Add_(ADDRESS A,ADDRESS B);
//MemClip : Two Number Multiplication
//＊Return value is A×B for no overflow, 0 for overflow.
//＊B must not be zero.
address _MemC_Size_Mul_(ADDRESS A,ADDRESS B);
#endif
#endif
