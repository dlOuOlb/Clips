/*------------------------------------------------------------------*/
/*	MemClip provides some simple memory handling functions.			*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2019.04.26	*/
/*------------------------------------------------------------------*/

#ifndef _INC_MEMCLIP
#define _INC_MEMCLIP

#if(1)
#include <malloc.h>
#include <memory.h>
#include <stdarg.h>
#include <assert.h>
#include <errno.h>
#endif

#if(1)
#ifdef Fold_
#error The macro "Fold_" is already defined.
#else
#define Fold_(Comment,...) (1)	//MemClip : Code Folding with #if and #endif Pre-processor.
#endif
#endif

#if(Fold_(Definition:Primal Macros))
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

#ifdef Mute_
#error The macro "Mute_" is already defined.
#else
#define Mute_(Argument) ((general)(Argument))	//MemClip : Unused Argument Warning Mute
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
#endif

#if(Fold_(Definition:Advanced Macros))
#define MemC_Type_Rename_(oldtype,newtype,NEWTYPE) typedef oldtype newtype;typedef const oldtype NEWTYPE;	//MemClip : Macro for Type Renaming
#define MemC_Type_Declare_(spec,type,TYPE) typedef spec _##type type;typedef const spec _##type TYPE;		//MemClip : Macro for Type Declaration

#define MemC_Func_Declare_V_(Return,Func_,...) Return (*Func_)(__VA_ARGS__)		//MemClip : Function Pointer Variable Declaration
#define MemC_Func_Declare_C_(Return,Func_,...) Return (_PL_ Func_)(__VA_ARGS__)	//MemClip : Function Pointer Constant Declaration
#define MemC_Func_Casting_(Return,Func_,...) (Return(*)(__VA_ARGS__))(Func_)	//MemClip : Function Pointer Casting
#define MemC_Type_Func_Declare_(Return,func_type_,FUNC_TYPE_,...) typedef MemC_Func_Declare_V_(Return,func_type_,__VA_ARGS__);typedef MemC_Func_Declare_C_(Return,FUNC_TYPE_,__VA_ARGS__);	//MemClip : Macro for Function Type Declaration

#define MemC_DT_Define_(IScope,IIndex,IName,IFlag,ILink,IMeta,type) {.Scope=(IScope),.Index=(IIndex),.Flag=(IFlag),.SizeType=sizeof(type),.SizeName=sizeof(IName),.Name=(IName),.Link=(ILink),.Meta=(IMeta)}	//MemClip : Macro for MemC_DT Definition

#define MemC_Size_(type,Elements) ((Elements)*sizeof(type))	//MemClip : Byte Size of Elements

#define MemC_Max_Dimension 8	//MemClip : Maximum Array Dimension
#endif

#if(Fold_(Definition:Primal Types))
MemC_Type_Rename_(void,general,GENERAL);					//MemClip : Void Type
MemC_Type_Rename_(char,byte_08,BYTE_08);					//MemClip : Byte Type
MemC_Type_Rename_(int,integer,INTEGER);						//MemClip : Integer Type
MemC_Type_Rename_(size_t,address,ADDRESS);					//MemClip : Address Type
MemC_Type_Func_Declare_(general,func_p_,FUNC_P_,general);	//MemClip : Function Pointer Type

static_assert((sizeof(char)==1),"sizeof(char) != 1");
static_assert((sizeof(void*)==sizeof(size_t)),"sizeof(void*) != sizeof(size_t)");
#endif

#if(Fold_(Definition:Advanced Types))
//MemClip : Address Union
union _memclip
{
	general *P;	//MemClip : Access as Pointer Value
	address V;	//MemClip : Access as Numeric Value
};
MemC_Type_Declare_(union,memclip,MEMCLIP);	//MemClip : Address Union

//MemClip : Error Note Union
union _memc_en
{
	errno_t I;	//MemClip : Access as Raw Value

	//MemClip : Access as Enumerated Value
	enum
	{
		MemCErrZero=0,
		MemCErrCustom=0x4D656D43,
#ifdef EDOM
		MemCErrDomain=EDOM,
#endif
#ifdef ERANGE
		MemCErrRange=ERANGE,
#endif
#ifdef EILSEQ
		MemCErrIllegalSequence=EILSEQ,
#endif
#ifdef ECHILD
		MemCErrChild=ECHILD,
#endif
#ifdef EAGAIN
		MemCErrAgain=EAGAIN,
#endif
#ifdef E2BIG
		MemCErrTooBig=E2BIG,
#endif
#ifdef EACCES
		MemCErrAccess=EACCES,
#endif
#ifdef EBADF
		MemCErrBadFile=EBADF,
#endif
#ifdef EDEADLOCK
		MemCErrDeadLock=EDEADLOCK,
#endif
#ifdef EEXIST
		MemCErrExist=EEXIST,
#endif
#ifdef EINVAL
		MemCErrInvalid=EINVAL,
#endif
#ifdef EMFILE
		MemCErrManyFiles=EMFILE,
#endif
#ifdef ENOENT
		MemCErrNoEntry=ENOENT,
#endif
#ifdef ENOEXEC
		MemCErrNoExecution=ENOEXEC,
#endif
#ifdef ENOMEM
		MemCErrNoMemory=ENOMEM,
#endif
#ifdef ENOSPC
		MemCErrNoSpace=ENOSPC,
#endif
#ifdef EXDEV
		MemCErrNoExternalDevice=EXDEV,
#endif
#ifdef STRUNCATE
		MemCErrStringTruncate=STRUNCATE
#endif
	}
	E;
};
MemC_Type_Declare_(union,memc_en,MEMC_EN);	//MemClip : Error Note Union
static_assert(sizeof(memc_en)==sizeof(errno_t),"sizeof(memc_en)!=sizeof(errno_t)");

//MemClip : Data Type Structure
struct _memc_dt
{
	GENERAL _PL_ Scope;	//MemClip : Type Scope
	ADDRESS Index;		//MemClip : Index in Scope
	ADDRESS Flag;		//MemClip : Property Flag
	ADDRESS SizeType;	//MemClip : Type's Byte Size
	ADDRESS SizeName;	//MemClip : Name's Byte Size
	BYTE_08 _PL_ Name;	//MemClip : Type Name
	GENERAL _PL_ Link;	//MemClip : External Link
	GENERAL _PL_ Meta;	//MemClip : Meta Data
};
MemC_Type_Declare_(struct,memc_dt,MEMC_DT);	//MemClip : Data Type Structure

//MemClip : Type Enumeration
enum _memc_te
{
	MemCTypeUnknown=-1,	//MemClip : Unknown
	MemCTypeNone_00=0,	//MemClip : None
	MemCTypeByte_08=1,	//MemClip : 8-bit Byte
	MemCTypeInteger=2,	//MemClip : Integer
	MemCTypeAddress=3,	//MemClip : Address
	MemCTypes=4			//MemClip : The Number of Types
};
MemC_Type_Declare_(enum,memc_te,MEMC_TE);	//MemClip : Type Enumeration

//MemClip : Memory Slot Structure
struct _memc_ms
{
	GENERAL _PL_ ID;	//MemClip : Identification
	MEMC_DT _PL_ Type;	//MemClip : Data Type
	ADDRESS Nums;		//MemClip : Number of Slots

	const union
	{
		//MemClip : Cell Access
		memclip _PL_ Cell;

		//MemClip : Slot Access
		const union
		{
			general *_PL_ P;	//MemClip : Access as Pointer Array
			address _PL_ V;		//MemClip : Access as Numeric Array
		}
		Slot;
	};
};
MemC_Type_Declare_(struct,memc_ms,MEMC_MS);	//MemClip : Memory Slot Structure

//MemClip : Host Memory Container Structure
struct _memc_mc
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

MemC_Type_Declare_(struct,memc_ml,MEMC_ML);	//MemClip : Memory Lender Structure
//MemClip : Memory Lender Structure
struct _memc_ml
{
	memc_ml _PL_ LinkSelf;	//MemClip : Self Reference
	memc_ml _PL_ LinkPrev;	//MemClip : Previous Linked Lender
	memc_ml _PL_ LinkNext;	//MemClip : Next Linked Lender
	ADDRESS SizeAble;		//MemClip : Current Lendable Memory Size in Bytes
	ADDRESS SizeIdle;		//MemClip : Current Idle Memory Size
	ADDRESS SizeUsed;		//MemClip : Current Used Memory Size
	ADDRESS NumsIdle;		//MemClip : Current Number of Idle Nodes
	ADDRESS NumsUsed;		//MemClip : Current Number of Used Nodes
};
#endif

#if(Fold_(Declaration:Memory Allocator and Deallocator))
//MemClip : Memory Allocator Declaration - Pair with "_MemC_Free_"
general *_MemC_Malloc_(ADDRESS Size);
//MemClip : Memory Deallocator Declaration - Pair with "_MemC_Malloc_"
general _MemC_Free_(general _PL_ Memory);
//MemClip : Default Memory Allocator and Deallocator Definition - Put it once somewhere unless you have a custom one.
#define _MemC_Default_ general *_MemC_Malloc_(ADDRESS Size) { return malloc(Size); } general _MemC_Free_(general _PL_ Memory) { free(Memory); }
#endif

#if(Fold_(Library Casing))
//MemClip : Library Case
extern const struct _memcase
{
	BYTE_08 _PL_ Version;	//MemClip : Library Version

	//MemClip : Type Descriptors
	const struct
	{
		MEMC_DT _PL_ N00;	//MemClip : none_00
		MEMC_DT _PL_ B08;	//MemClip : byte_08
		MEMC_DT _PL_ Int;	//MemClip : integer
		MEMC_DT _PL_ Add;	//MemClip : address

		//MemClip : Type Descriptor to Enumeration Conversion
		memc_te(_PL_ Enum_)(MEMC_DT _PL_);
		//MemClip : Type Enumeration to Descriptor Conversion
		MEMC_DT*(_PL_ Desc_)(MEMC_TE);
	}
	Type;

#if(Fold_(Part:Plain Memory Allocation and Deallocation))
	//MemClip : Allocation Functions
	const struct
	{
		//MemClip : Memory Allocation - Deallocate with "MemC_Deloc_"
		general*(_PL_ Byte_)(ADDRESS ByteSize);
		//MemClip : Unit Memory Allocation - Deallocate with "MemC_Deloc_"
#define MemC_Alloc_Unit_(type) MemC.Alloc.Byte_(sizeof(type))
		//MemClip : ND Array Memory Allocation - Deallocate with "MemC_Deloc_"
		//£ªDims and the number of variadic arguments must be equal!
		general*(_PL_ DN_)(ADDRESS,ADDRESS,...);
#define MemC_Alloc_ND_(type,Dims,...) MemC.Alloc.DN_(sizeof(type),Dims,__VA_ARGS__)
	}
	Alloc;
	//MemClip : Memory Deallocation
#define MemC_Deloc_(Memory) __dl{if(Memory){_MemC_Free_(Memory);(Memory)=NULL;}}lb__

	//MemClip : Temporary Memory Allocation and Deallocation
#define MemC_Temp_Byte_(Temp,Size,EXIT) for(general _PL_(Temp)=MemC.Alloc.Byte_(Size),*(_##Temp)=FULL;_##Temp;_MemC_Free_(Temp),_##Temp=NULL)if(!(Temp))goto EXIT;else
#define MemC_Temp_Unit_(type,Temp,EXIT) for(type _PL_(Temp)=MemC_Alloc_Unit_(type),*(_##Temp)=FULL;_##Temp;_MemC_Free_(Temp),_##Temp=NULL)if(!(Temp))goto EXIT;else
#define MemC_Temp_ND_(type,Temp,EXIT,Dims,...) for(general _PL_(Temp)=MemC_Alloc_ND_(type,Dims,__VA_ARGS__),*(_##Temp)=FULL;_##Temp;_MemC_Free_(Temp),_##Temp=NULL)if(!(Temp))goto EXIT;else

	//MemClip : Set Functions
	const struct
	{
		//MemClip : Batch Memory Allocation Check
		//£ªReturn value is 0 for failure, 1 for success.
		integer(_PL_ Check_)(GENERAL _PL_ _PL_ MemorySet,ADDRESS Count);
		//MemClip : Batch Memory Deallocation
		general(_PL_ Deloc_)(general *_PL_ MemorySet,ADDRESS Count);
	}
	Set;
#endif

#if(Fold_(Part:Plain Memory Clear))
	//MemClip : Data Reset in Byte Size
#define MemC_Clear_Byte_(Memory,ByteSize) memset(Memory,0,ByteSize)
	//MemClip : Unit Data Reset
#define MemC_Clear_Unit_(Unit) memset(Unit,0,sizeof(*(Unit)))
	//MemClip : 1D Array Data Reset
#define MemC_Clear_1D_(Line,Elements) memset(Line,0,(Elements)*sizeof(*(Line)))
#endif

#if(Fold_(Part:Plain Memory Copy))
	//MemClip : Data Copy in Byte Size
#define MemC_Copy_Byte_(Source,Target,ByteSize) memcpy_s(Target,ByteSize,Source,ByteSize)
	//MemClip : Unit Data Copy
#define MemC_Copy_Unit_(Source,Target) ((sizeof(*(Source))==sizeof(*(Target)))?(memcpy_s(Target,sizeof(*(Target)),Source,sizeof(*(Source)))):(MemCErrCustom))
	//MemClip : 1D Array Data Copy
#define MemC_Copy_1D_(Source,Target,Elements) ((sizeof(*(Source))==sizeof(*(Target)))?(memcpy_s(Target,(Elements)*sizeof(*(Target)),Source,(Elements)*sizeof(*(Source)))):(MemCErrCustom))
#endif

#if(Fold_(Part:Plain Memory Compare))
	//MemClip : Data Compare in Byte Size
#define MemC_Compare_Byte_(MemoryA,MemoryB,ByteSize) memcmp(MemoryA,MemoryB,ByteSize)
	//MemClip : Unit Data Compare
#define MemC_Compare_Unit_(UnitA,UnitB) memcmp(UnitA,UnitB,sizeof(*(UnitA)))
	//MemClip : 1D Array Data Compare
#define MemC_Compare_1D_(LineA,LineB,Elements) memcmp(LineA,LineB,(Elements)*sizeof(*(LineA)))
#endif

	//MemClip : Complex Memory Copy Functions
	const struct
	{
		//MemClip : Array Data Copy
		errno_t(_PL_ DN_)(GENERAL _PL_ Source1DAccess,general _PL_ Target1DAccess,ADDRESS _PL_ SourceOffset,ADDRESS _PL_ TargetOffset,ADDRESS _PL_ CopyLength,ADDRESS _PL_ SourceShape,ADDRESS _PL_ TargetShape,ADDRESS Dimensions,ADDRESS TypeSize);
#define MemC_Copy_ND_(S,T,SOfs,TOfs,Lng,SShp,TShp,Dims) ((sizeof(*(S))==sizeof(*(T)))?(MemC.Copy.DN_(S,T,SOfs,TOfs,Lng,SShp,TShp,Dims,sizeof(*(S)))):(MemCErrCustom))
		//MemClip : Array Data Copy with Step
		errno_t(_PL_ Step_)(GENERAL _PL_ Source1DAccess,general _PL_ Target1DAccess,ADDRESS CopyNums,ADDRESS SourceStepBytes,ADDRESS TargetStepBytes,ADDRESS EachCopyBytes);
	}
	Copy;

	//MemClip : Data Preset Functions
	const struct
	{
		//MemClip : 1D Array Data Preset
		errno_t(_PL_ D1_)(general _PL_ Memory,GENERAL _PL_ Tile,ADDRESS Number,ADDRESS TypeSize);
#define MemC_Preset_1D_(Memory,Tile,Elements) ((sizeof(*(Memory))==sizeof(*(Tile)))?(MemC.Preset.D1_(Memory,Tile,Elements,sizeof(*(Tile)))):(MemCErrCustom))
	}
	Preset;

	//MemClip : Data Reformation Functions
	const struct
	{
		//MemClip : Reformed Target Shape Calculation
		//£ªTargetShape[ReformingAxis[dim]] = SourceShape[dim]
		integer(_PL_ Shape_)(ADDRESS _PL_ SourceShape,ADDRESS _PL_ ReformingAxis,address _PL_ TargetShape,ADDRESS Dimensions);

		//MemClip : Array Data Reformation - See also "MemC_Reform_Shape_"
		errno_t(_PL_ DN_)(GENERAL _PL_ Source1DAccess,general _PL_ Target1DAccess,ADDRESS _PL_ SourceShape,ADDRESS _PL_ ReformingAxis,address Dimensions,address TypeSize);
#define MemC_Reform_ND_(S,T,SShp,Axis,Dims) ((sizeof(*(S))==sizeof(*(T)))?(MemC.Reform.DN_(S,T,SShp,Axis,Dims,sizeof(*(S)))):(MemCErrCustom))
	}
	Reform;

	//MemClip : Interval Addressing Functions
	const struct
	{
		//MemClip :  1D Array Uniform or Non-Uniform Interval Addressing
		address(_PL_ D1_)(general _PL_ Indexer,GENERAL _PL_ Indexed,ADDRESS Interval,ADDRESS Indices,ADDRESS TypeSize,INTEGER Mode);
#define MemC_Assign_1D_U_(Address,Line,Jump,Number) MemC.Assign.D1_(Address,Line,Jump,Number,sizeof(*(Line)),0)
#define MemC_Assign_1D_N_(Address,Line,Jump,Number) MemC.Assign.D1_(Address,Line,(address)(Jump),Number,sizeof(*(Line)),1)
	}
	Assign;

	//MemClip : Sorting Functions
	const struct
	{
		//MemClip : Table Indexing
		//£ªTable[idx]£½Mode£¿£¦(Table[idx])£ºidx
		general(_PL_ Index_)(address *_R_ Table,ADDRESS Count,INTEGER Mode);

		//MemClip : Object Sorting
		//£ªRequired ReferTable size is Count¡¿sizeof(general*) bytes.
		//£ªIf IndexTable is not NULL, then its required size is Count¡¿sizeof(address) bytes.
		//£ªRequired BufferSpace size is 2¡¿Count¡¿sizeof(address) bytes.
		//£ªIf Comp_(ReferTable[m],ReferTable[n]) is not 0, then those two will be swapped during the process.
		errno_t(_PL_ Do_)(MemC_Func_Declare_C_(integer,Comp_,GENERAL _PL_,GENERAL _PL_),GENERAL *_PL_ ReferTable,address _PL_ IndexTable,address _PL_ BufferSpace,ADDRESS Count);
	}
	Sort;

	//MemClip : Size Functions
	const struct
	{
		//MemClip : Two Number Addition
		//£ªReturn value is A£«B for no overflow, 0 for overflow.
		address(_PL_ Add_)(ADDRESS A,ADDRESS B);
		//MemClip : Two Number Multiplication
		//£ªReturn value is A¡¿B for no overflow, 0 for overflow.
		//£ªB must not be zero.
		address(_PL_ Mul_)(ADDRESS A,ADDRESS B);
	}
	Size;

#if(Fold_(Part:Others))
	//MemClip : Do nothing.
	general(_PL_ Void_)(general);

	//MemClip : Key Finding for Switch Operation
	address(_PL_ Switch_)(GENERAL _PL_ Key,GENERAL _PL_ _PL_ TblRf,ADDRESS _PL_ LngRf,ADDRESS LngKey,ADDRESS NumRf,ADDRESS TypeSize);
#define MemC_Switch_(Key,RefBook,RefLng,KeyLng,Refs) MemC.Switch_(Key,RefBook,RefLng,KeyLng,Refs,sizeof(**(RefBoook)))
#endif

	//MemClip : Memory Slot Functions
	const struct
	{
		//MemClip : Memory Slot Memory Allocation - Deallocate with "MemC.MS.Delete_"
		//£ªNums = SlotsNumber
		memc_ms*(_PL_ Create_)(GENERAL _PL_ Identification,ADDRESS SlotsNumber);
		//MemClip : Memory Slot Memory Deallocation
		general(_PL_ Delete_)(memc_ms *_PL_ MemorySlot);
		//MemClip : Temporarily allocate and deallocate a memory slot.
#define MemC_MS_Temp_(Temp,Nums,EXIT) for(memc_ms _PL_(Temp)=MemC.MS.Create_(NULL,Nums),*(_##Temp)=FULL;_##Temp;MemC.MS.Delete_((memc_ms**)&(Temp)),(_##Temp)=NULL)if(!(Temp))goto EXIT;else

		//MemClip : Memory Slot Memory Occupation
		address(_PL_ Size_)(MEMC_MS _PL_ MemorySlot);
		//MemClip : Memory Slot Memory Type Change
		integer(_PL_ Change_)(MEMC_MS _PL_ MemorySlot,MEMC_DT _PL_ MemoryType);

		//MemClip : Memory Slot Data Reset
		integer(_PL_ Init_)(MEMC_MS _PL_ MemorySlot);
		//MemClip : Memory Slot NULL Check
		//£ªCount = MemorySlot -> Slot.V[0]
		//¡¡MemorySet = { P[1], P[2], ..., P[Count] | P = MemorySlot -> Slot.P }
		//£ªMode 0 : Return value is 1 for all NULLs, otherwise 0.
		//£ªMode 1 : Return value is 0 for any NULLs, otherwise 1.
		integer(_PL_ Null_)(MEMC_MS _PL_ MemorySlot,INTEGER CheckMode);

		//MemClip : Shape Information Setting
		//£ªShapeInfo -> Slot.V[0] = Dims
		//¡¡{ V[1], V[2], ..., V[Dims] | V = ShapeInfo -> Slot.V } = { Arg1, Arg2, ..., ArgN }
		//£ªDims and N must be equal!
		integer(_PL_ Dims_)(MEMC_MS _PL_ ShapeInfo,ADDRESS Dims,...);

		//MemClip : Just kidding!
		integer(_PL_ Joke_)(MEMC_MS _PL_ MemorySlot);
		//MemClip : Oops!
		integer(_PL_ Oops_)(MEMC_MS _PL_ MemorySlot);

#define MemC_MS_Foreach_(MemorySlot,type,Each) for(type (Each)=(type)0,*(_Ptr##Each)=(general*)((MemorySlot)->Slot.P),_PL_(_End##Each)=(general*)(((MemorySlot)->Slot.P)+((MemorySlot)->Nums)),_PL_(_Check##Each)[sizeof(type)==sizeof(address)]={NULL};(((address)(_Ptr##Each))<((address)(_End##Each)))?(Acs_(address,Each)=*(address*)(_Ptr##Each),1):(MemC_Mute_(_Check##Each),0);Acs_(address*,(_Ptr##Each))++)
	}
	MS;

	//MemClip : Memory Container Functions
	const struct
	{
		//MemClip : Memory Container Memory Allocation - Deallocate with "MemC.MC.Delete_"
		//£ªUnit = TypeInfo -> SizeType
		//¡¡Dims = ShapeInfo -> Slot.V[0]
		//¡¡LngND = { V[1], V[2], ..., V[Dims] | V = ShapeInfo -> Slot.V }
		memc_mc*(_PL_ Create_)(GENERAL _PL_ Identification,MEMC_MS _PL_ ShapeInfo,MEMC_DT _PL_ TypeInfo);
		//MemClip : Memory Container Memory Deallocation
		general(_PL_ Delete_)(memc_mc *_PL_ MemoryContainer);
		//MemClip : Temporarily allocate and deallocate a memory container.
#define MemC_MC_Temp_(Temp,Shape,Type,EXIT) for(memc_mc _PL_(Temp)=MemC.MC.Create_(NULL,Shape,Type),*(_##Temp)=FULL;_##Temp;MemC.MC.Delete_((memc_mc**)&(Temp)),(_##Temp)=NULL)if(!(Temp))goto EXIT;else

		//MemClip : Memory Container Memory Occupation
		address(_PL_ Size_)(MEMC_MC _PL_ MemoryContainer);
		//MemClip : Memory Container Shape Information Copy
		//£ªShapeInfo -> Slot.V[0] = MemoryContainer -> Dims
		//¡¡{ V[1], V[2], ..., V[Dims] | V = ShapeInfo -> Slot.V } = MemoryContainer -> LngND
		integer(_PL_ Form_)(MEMC_MC _PL_ MemoryContainer,MEMC_MS _PL_ ShapeInfo);
		//MemClip : Memory Container Data Type Change
		integer(_PL_ Change_)(MEMC_MC _PL_ MemoryContainer,MEMC_DT _PL_ DataType);
	}
	MC;

	//MemClip : Memory Lender Functions
	const struct
	{
		//MemClip : Memory Lender Static Definition
		//£ª1 chunk is equal to 4¡¿sizeof(size_t) bytes.
		//¡¡The memory lender's head occupies 2 chunks.
		//¡¡Each memory slice's head occupies 1 chunk.
#define MemC_ML_Define_(LenderName,ChunksNumber) static address _##LenderName[(ChunksNumber)<<2]={(address)_##LenderName,(address)_##LenderName,(address)_##LenderName,((ChunksNumber)-3)<<4,((ChunksNumber)-3)<<4,0,1,0,(address)NULL,(address)NULL,(address)NULL,((ChunksNumber)-3)<<4};memc_ml _PL_ LenderName=(memc_ml*)_##LenderName;

		//MemClip : Memory Lender Memory Allocation - Deallocate with "MemC.ML.Delete_"
		//£ª1 chunk is equal to 4¡¿sizeof(size_t) bytes.
		//¡¡The memory lender's head occupies 2 chunks.
		//¡¡Each memory slice's head occupies 1 chunk.
		//£ªThe previous lender can be NULL, if linking is not wanted.
		memc_ml*(_PL_ Create_)(memc_ml _PL_ PreviousLender,ADDRESS ChunksNumber);
		//MemClip : Memory Lender Memory Deallocation
		//£ªReturn value is the memory lender's previous lender.
		memc_ml*(_PL_ Delete_)(memc_ml *_PL_ MemoryLender);

		//MemClip : Memory Lender Memory Occupation
		address(_PL_ Size_)(MEMC_ML _PL_ MemoryLender);
		//MemClip : Kill all memory slices in the linked memory lenders.
		//£ªReturn value is 0 for failure, 1 for success.
		integer(_PL_ Kill_)(memc_ml _PL_ MemoryLender);
		//MemClip : Move all memory slices from the source lenders to the target lenders.
		//£ªBufferSlot->Nums should not be less than the total number of the linked source and target lenders,
		//¡¡and also should not be less than the 3¡¿total number of the used slices in the linked source lenders.
		//£ªUsed slices in the source lenders will be overwritten with their corresponding new addresses.
		//¡¡After you finish address mapping, reset the source lenders with "MemC_ML_Kill_"
		//£ªReturn value is 0 for failure, 1 for success.
		integer(_PL_ Move_)(memc_ml _PL_ SourceLender,memc_ml _PL_ TargetLender,memc_ms _PL_ BufferSlot);

		//MemClip : Borrow a memory slice from the memory lender - Return with "MemC_ML_Return_"
		general*(_PL_ Borrow_)(memc_ml _PL_ MemoryLender,ADDRESS SliceBytes);
		//MemClip : Return the memory slice to its master.
		//£ªReturn value is 0 for failure, 1 for success.
		integer(_PL_ Return_)(general _PL_ MemorySlice);
#define MemC_ML_Return_(MemorySlice) __dl{if(MemC.ML.Return_(MemorySlice)){(MemorySlice)=NULL;}}lb__
		//MemClip : Temporarily borrow and return a memory slice from the memory lender.
#define MemC_ML_Moment_(Lender,Temp,Size,EXIT) for(general _PL_(Temp)=MemC.ML.Borrow_(Lender,Size),*(_##Temp)=FULL;_##Temp;MemC.ML.Return_(Temp),(_##Temp)=NULL)if(!(Temp))goto EXIT;else

		//MemClip : Get the master of the memory slice.
		memc_ml*(_PL_ Master_)(GENERAL _PL_ MemorySlice);
		//MemClip : Get the usable bytes of the memory slice.
		address(_PL_ Usable_)(GENERAL _PL_ MemorySlice);
	}
	ML;
}
MemC;
#endif
#endif
