#ifndef oMEMCLIP_INC_
#define oMEMCLIP_INC_ "MemC:2020.01.31"
/*------------------------------------------------------------------+
|	MemClip provides some simple memory handling functions.			|
|																	|
|	Written by Ranny Clover											|
|	http://github.com/dlOuOlb/Clips/blob/master/Headers/memclip.h	|
+-------------------------------------------------------------------+
|	Dependency:														|
|																	|
|	MSVClip -- MemClip												|
+-------------------------------------------------------------------+
|	Non-Prefixed Macros:											|
|																	|
|	Fold_															|
|	Meta_	NULL	Acs_	_R_		__dlOuOlb__						|
|	Conc_	FULL	Mute_	_PL_	__dl	lb__					|
+-------------------------------------------------------------------+
|	Non-Prefixed Types:												|
|																	|
|	general	logical	byte_08	integer	address	func_p_					|
|	GENERAL	LOGICAL	BYTE_08	INTEGER	ADDRESS	FUNC_P_					|
+-------------------------------------------------------------------+
|	Note:															|
|																	|
|	Unmanaged objects from these Clip libraries are allocated and	|
|	deallocated by the "uMemC_Malloc_" and "uMemC_Free_" function	|
|	pair, and someone must define them. Their default definitions	|
|	are defined in the "MemC_Default_" macro, and... that's all.	|
+------------------------------------------------------------------*/

#include <msvclip.h>

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef Fold_
#error The macro "Fold_" is already defined.
#else
#define Fold_(...) (1)
#ifdef $
#endif
#endif

#if(Fold_(Non-Prefixed Macros))
#ifndef NULL
#define NULL ((general*)(0))
#endif

#ifndef FULL
#define FULL ((general*)(~((address)(0))))
#endif

#ifdef _PL_
#error The macro "_PL_" is already defined.
#else
#define _PL_ *const
#endif

#ifdef _R_
#error The macro "_R_" is already defined.
#else
#define _R_ restrict
#endif

#ifdef Acs_
#error The macro "Acs_" is already defined.
#else
#define Acs_(type,Data) (*((type*)(&(Data))))
#endif

#ifdef Mute_
#error The macro "Mute_" is already defined.
#else
#define Mute_(Argument) ((general)(Argument))
#endif

#ifdef Meta_
#error The macro "Meta_" is already defined.
#else
#define Meta_(X) xMemC_Meta_(X)
#define xMemC_Meta_(X) #X
#endif

#ifdef Conc_
#error The macro "Conc_" is already defined.
#else
#define Conc_(A,B) xMemC_Conc_(A,B)
#define xMemC_Conc_(A,B) A##B
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

#if(Fold_(Prefixed Macros))
#define MemC_Type_Rename_(oldname,newname,NEWNAME) typedef oldname newname;typedef const oldname NEWNAME
#define MemC_Type_Declare_(spec,type,TYPE) typedef spec _##type type;typedef const spec _##type TYPE

#define MemC_Func_Casting_(Return,Func_,...) ((Return(*)(__VA_ARGS__))(Func_))
#define MemC_Func_Declare_(Return,func_,FUNC_,...) typedef Return(*func_)(__VA_ARGS__);typedef Return(_PL_ FUNC_)(__VA_ARGS__)

#define MemC_Assert_(Cond) ((general)((ADDRESS[(Cond)?(+1):(-1)]){0}))
#define MemC_Size_(type,Elements) ((Elements)*sizeof(type))
#define MemC_Unit_(type,Unit,...) type _PL_(Unit)=&(type){__VA_ARGS__}
#define MemC_Temp_(type,...) for(type __VA_ARGS__,*Conc_(xMemCTemp,__LINE__)=FULL;Conc_(xMemCTemp,__LINE__);Conc_(xMemCTemp,__LINE__)=NULL)
#endif

#if(Fold_(Primal Types))
MemC_Type_Rename_(void,general,GENERAL);				//MemClip : Void Type
MemC_Type_Rename_(_Bool,logical,LOGICAL);				//MemClip : Bool Type
MemC_Type_Rename_(unsigned char,byte_08,BYTE_08);		//MemClip : Byte Type
MemC_Type_Rename_(signed int,integer,INTEGER);			//MemClip : Integer Type
MemC_Type_Rename_(uintptr_t,address,ADDRESS);			//MemClip : Address Type
MemC_Func_Declare_(general,func_p_,FUNC_P_,general);	//MemClip : Function Pointer Type
#endif

#if(Fold_(Plain Types))
//MemClip : Address Union
union _memclip
{
	general *P;	//MemClip : Access as Pointer Value
	address V;	//MemClip : Access as Numeric Value
};
MemC_Type_Declare_(union,memclip,MEMCLIP);	//MemClip : Address Union

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
#endif

#if(Fold_(Advanced Types))
//MemClip : Memory Slot Structure
struct _memc_ms
{
	ADDRESS Nums;	//MemClip : Number of Slots

	//MemClip : Pointer Union
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

//MemClip : Memory Lender Structure
struct _memc_ml
{
	//MemClip : Link to the other Memory Lenders
	const struct
	{
		struct _memc_ml _PL_ Self;	//MemClip : Self Reference
		struct _memc_ml _PL_ Prev;	//MemClip : Previous Linked Lender
		struct _memc_ml _PL_ Next;	//MemClip : Next Linked Lender
	}
	Link;

	//MemClip : Memory Size Information in Bytes
	const struct
	{
		ADDRESS Able;	//MemClip : Current Lendable Memory Size
		ADDRESS Idle;	//MemClip : Current Idle Memory Size
		ADDRESS Used;	//MemClip : Current Used Memory Size
	}
	Size;

	//MemClip : Node Number Information
	const struct
	{
		ADDRESS Idle;	//MemClip : Current Number of Idle Nodes
		ADDRESS Used;	//MemClip : Current Number of Used Nodes
	}
	Nums;
};
MemC_Type_Declare_(struct,memc_ml,MEMC_ML);	//MemClip : Memory Lender Structure
#endif

#if(Fold_(User-Side Memory Handler))
//MemClip : Memory Allocator Declaration - Pair with "uMemC_Free_"
extern general *uMemC_Malloc_(ADDRESS Size);
//MemClip : Memory Deallocator Declaration - Pair with "uMemC_Malloc_"
extern general uMemC_Free_(general _PL_ Memory);
//MemClip : Default Memory Allocator and Deallocator Definitions - Put it once somewhere unless you have a custom one.
#define MemC_Default_ extern general *uMemC_Malloc_(ADDRESS Size) { return malloc(Size); } extern general uMemC_Free_(general _PL_ Memory) { free(Memory);return; }
#endif

#if(Fold_(Library Casing))
//MemClip : Library Case Structure
typedef const struct
{
	//MemClip : Some Constants
	const struct
	{
		//MemClip : Library Version - "MemC:yyyy.mm.dd"
		BYTE_08 _PL_ _R_ Version;
		//MemClip : Maximum Dimension
		ADDRESS MaxDims;

		MEMCLIP Null;	//MemClip : 0
		MEMCLIP Full;	//MemClip : ~0
	};

	//MemClip : Some Trivials
	const struct
	{
		//MemClip : Do nothing.
		general(_PL_ Void_)(general);
		//BoxClip : Just return the input.
		address(_PL_ Just_)(ADDRESS);

		//PenClip : Preserved for Future Usage
		ADDRESS xPreserved[2];

#if(Fold_(Okay))
#define MemC_Okay_Size_(type) static_assert(sizeof(type)==sizeof(address),"sizeof(" Meta_(type) ") != sizeof(address)")
#define MemC_Okay_Wrap_(type) (MemC_Assert_(sizeof(type)==sizeof(address)),MemC_Func_Casting_(type,MemC.Just_,type const)(Acs_(type,MemC.Full.V))==Acs_(type,MemC.Full.V))
#endif
	};

	//MemClip : Type Descriptors
	const struct
	{
#if(Fold_(Body Definition))
#define MemC_DT_Define_(IScope,IIndex,IName,IFlag,ILink,IMeta,type)\
		{\
			.Scope=(IScope),\
			.Index=(IIndex),\
			.Flag=(IFlag),\
			.SizeType=sizeof(type),\
			.SizeName=sizeof(IName),\
			.Name=(IName),\
			.Link=(ILink),\
			.Meta=(IMeta)\
		}
#endif

		//MemClip : Objects
		const struct
		{
			MEMC_DT _PL_ _R_ N00;	//MemClip : none_00
			MEMC_DT _PL_ _R_ B08;	//MemClip : byte_08
			MEMC_DT _PL_ _R_ Int;	//MemClip : integer
			MEMC_DT _PL_ _R_ Add;	//MemClip : address
		};

		//MemClip : Functions
		const struct
		{
			//MemClip : Type Descriptor to Enumeration Conversion
			memc_te(_PL_ Enum_)(MEMC_DT _PL_ _R_);
			//MemClip : Type Enumeration to Descriptor Conversion
			MEMC_DT*(_PL_ Desc_)(MEMC_TE);

		};

		//PenClip : Preserved for Future Usage
		ADDRESS xPreserved[2];
	}
	Type;

	//MemClip : Size Functions
	const struct
	{
		//MemClip : Add two numbers.
		//＊Return value is A＋B for no overflow, 0 for overflow.
		address(_PL_ Add_)(ADDRESS A,ADDRESS B);
		//MemClip : Subtract two numbers.
		//＊Return value is A－B for no underflow, 0 for underflow.
		address(_PL_ Sub_)(ADDRESS A,ADDRESS B);
		//MemClip : Multiply two numbers.
		//＊Return value is A×B for no overflow, 0 for overflow.
		//＊B must not be zero.
		address(_PL_ Mul_)(ADDRESS A,ADDRESS B);
		//MemClip : Divide two numbers.
		//＊Return value is A÷B for no remainder, 0 for remainder.
		//＊B must not be zero.
		address(_PL_ Div_)(ADDRESS A,ADDRESS B);
	}
	Size;

	//MemClip : Memory Management Functions
	const struct
	{
		//MemClip : Memory Deallocation
#define MemC_Deloc_(Memory) __dl{if(Memory){uMemC_Free_(Memory);(Memory)=NULL;}else;}lb__

		//MemClip : Allocation Functions - See also "MemC_Deloc_"
		const struct
		{
			//MemClip : Memory Allocation - Deallocate with "MemC_Deloc_"
			general*(_PL_ Byte_)(ADDRESS ByteSize);
			//MemClip : Unit Memory Allocation - Deallocate with "MemC_Deloc_"
#define MemC_Alloc_Unit_(type) MemC.Alloc.Byte_(sizeof(type))
			//MemClip : ND Array Memory Allocation - Deallocate with "MemC_Deloc_"
			//＊(Dims) should not be greater than "MemC.MaxDims".
			//　(Dims) and the number of variadic arguments must be equal!
			general*(_PL_ DN_)(ADDRESS TypeSize,ADDRESS Dims,...);
#define MemC_Alloc_ND_(type,Dims,...) MemC.Alloc.DN_(sizeof(type),Dims,__VA_ARGS__)
		}
		Alloc;

#if(Fold_(Temp))
#if(Fold_(Byte))
#define MemC_Temp_Byte_(Temp,Size,FAIL)\
		for\
		(\
			general\
				_PL_(Temp)=MemC.Alloc.Byte_(Size),\
				*Conc_(xMemCTemp,__LINE__)=FULL;\
			Conc_(xMemCTemp,__LINE__);\
			uMemC_Free_(Temp),Conc_(xMemCTemp,__LINE__)=NULL\
		)\
		if(!(Temp)){FAIL}else
#endif

#if(Fold_(Unit))
#define MemC_Temp_Unit_(type,Temp,FAIL)\
		for\
		(\
			type\
				_PL_(Temp)=MemC_Alloc_Unit_(type),\
				*Conc_(xMemCTemp,__LINE__)=FULL;\
			Conc_(xMemCTemp,__LINE__);\
			uMemC_Free_(Temp),Conc_(xMemCTemp,__LINE__)=NULL\
		)\
		if(!(Temp)){FAIL}else
#endif

#if(Fold_(ND))
#define MemC_Temp_ND_(type,Temp,FAIL,Dims,...)\
		for\
		(\
			general\
				_PL_(Temp)=MemC_Alloc_ND_(type,Dims,__VA_ARGS__),\
				*Conc_(xMemCTemp,__LINE__)=FULL;\
			Conc_(xMemCTemp,__LINE__);\
			uMemC_Free_(Temp),Conc_(xMemCTemp,__LINE__)=NULL\
		)\
		if(!(Temp)){FAIL}else
#endif
#endif

		//MemClip : Set Functions
		const struct
		{
			//MemClip : Batch Memory Allocation Check
			//＊Return value is 0 for failure, 1 for success.
			logical(_PL_ Check_)(GENERAL _PL_ _PL_ _R_ MemorySet,ADDRESS Count);
			//MemClip : Batch Memory Deallocation
			general(_PL_ Deloc_)(general *_PL_ _R_ MemorySet,ADDRESS Count);
		}
		Set;
	};

	//MemClip : Memory Operation Functions
	const struct
	{
#if(Fold_(Clear))
		//MemClip : Data Reset in Byte Size
#define MemC_Clear_Byte_(Memory,ByteSize) memset(Memory,0,ByteSize)
		//MemClip : Unit Data Reset
#define MemC_Clear_Unit_(Unit) memset(Unit,0,sizeof(*(Unit)))
		//MemClip : 1D Array Data Reset
#define MemC_Clear_1D_(Line,Elements) memset(Line,0,(Elements)*sizeof(*(Line)))
#endif

#if(Fold_(Copy)&&defined(__STDC_WANT_LIB_EXT1__)&&(__STDC_WANT_LIB_EXT1__))
		//MemClip : Data Copy in Byte Size
		//＊Return value is 0 for failure, 1 for success.
#define MemC_Copy_Byte_(Source,Target,ByteSize) (memcpy_s(Target,ByteSize,Source,ByteSize)==0)
		//MemClip : Unit Data Copy
		//＊Return value is 0 for failure, 1 for success.
#define MemC_Copy_Unit_(Source,Target) (MemC_Assert_(sizeof(*(Source))==sizeof(*(Target))),(memcpy_s(Target,sizeof(*(Target)),Source,sizeof(*(Source)))==0))
		//MemClip : 1D Array Data Copy
		//＊Return value is 0 for failure, 1 for success.
#define MemC_Copy_1D_(Source,Target,Elements) (MemC_Assert_(sizeof(*(Source))==sizeof(*(Target))),(memcpy_s(Target,(Elements)*sizeof(*(Target)),Source,(Elements)*sizeof(*(Source)))==0))
#else
#define MemC_Copy_Byte_(...) xMemC_Copy_Error_
#define MemC_Copy_Unit_(...) xMemC_Copy_Error_
#define MemC_Copy_1D_(...) xMemC_Copy_Error_
#define xMemC_Copy_Error_ static_assert(0,"#define __STDC_WANT_LIB_EXT1__ (1) before #include <memclip.h>")
#endif

#if(Fold_(Compare))
		//MemClip : Data Compare in Byte Size
#define MemC_Compare_Byte_(MemoryA,MemoryB,ByteSize) memcmp(MemoryA,MemoryB,ByteSize)
		//MemClip : Unit Data Compare
#define MemC_Compare_Unit_(UnitA,UnitB) (MemC_Assert_(sizeof(*(UnitA))==sizeof(*(UnitB))),memcmp(UnitA,UnitB,sizeof(*(UnitA))))
		//MemClip : 1D Array Data Compare
#define MemC_Compare_1D_(LineA,LineB,Elements) (MemC_Assert_(sizeof(*(LineA))==sizeof(*(LineB))),memcmp(LineA,LineB,(Elements)*sizeof(*(LineA))))
#endif

		//MemClip : Complex Memory Copy Functions
		//＊Return value is 0 for failure, 1 for success.
		const struct
		{
			//MemClip : Array Data Copy
			//＊(Dimensions) should not be greater than "MemC.MaxDims".
			logical(_PL_ DN_)(GENERAL _PL_ Source1DAccess,general _PL_ Target1DAccess,ADDRESS _PL_ SourceOffset,ADDRESS _PL_ TargetOffset,ADDRESS _PL_ CopyLength,ADDRESS _PL_ SourceShape,ADDRESS _PL_ TargetShape,ADDRESS Dimensions,ADDRESS TypeSize);
#define MemC_Copy_ND_(S,T,SOfs,TOfs,Lng,SShp,TShp,Dims) (MemC_Assert_(sizeof(*(S))==sizeof(*(T))),MemC.Copy.DN_(S,T,SOfs,TOfs,Lng,SShp,TShp,Dims,sizeof(*(S))))
			//MemClip : Array Data Copy with Step
			logical(_PL_ Step_)(GENERAL _PL_ _R_ Source1DAccess,general _PL_ _R_ Target1DAccess,ADDRESS CopyNums,ADDRESS SourceStepBytes,ADDRESS TargetStepBytes,ADDRESS EachCopyBytes);
		}
		Copy;

		//MemClip : Data Reformation Functions
		//＊(Dimensions) should not be greater than "MemC.MaxDims".
		//＊Return value is 0 for failure, 1 for success.
		const struct
		{
			//MemClip : Array Data Reformation - See also "MemC.Reform.Shape_"
			logical(_PL_ DN_)(GENERAL _PL_ _R_ Source1DAccess,general _PL_ _R_ Target1DAccess,ADDRESS _PL_ _R_ SourceShape,ADDRESS _PL_ _R_ ReformingAxis,ADDRESS Dimensions,ADDRESS TypeSize);
#define MemC_Reform_ND_(S,T,SShp,Axis,Dims) (MemC_Assert_(sizeof(*(S))==sizeof(*(T))),MemC.Reform.DN_(S,T,SShp,Axis,Dims,sizeof(*(S))))
			//MemClip : Reformed Target Shape Calculation
			//＊TargetShape[ReformingAxis[dim]] = SourceShape[dim]
			logical(_PL_ Shape_)(ADDRESS _PL_ _R_ SourceShape,ADDRESS _PL_ _R_ ReformingAxis,address _PL_ _R_ TargetShape,ADDRESS Dimensions);
		}
		Reform;

		//MemClip : Sorting Functions
		const struct
		{
			//MemClip : Table Indexing
			//＊Table[idx]＝Mode？＆(Table[idx])：idx
			general(_PL_ Index_)(address _PL_ _R_ Table,ADDRESS Count,LOGICAL Mode);

			//MemClip : Object Sorting
			//＊Required (ReferTable) size is Count×sizeof(general*) bytes.
			//　Required (IndexTable) size is Count×sizeof(address) bytes, unless it is NULL.
			//　Required (BufferSpace) size is 2×Count×sizeof(address) bytes.
			//＊If Comp_(ReferTable[m],ReferTable[n]) returns 1, then those two will be swapped during the process.
			//＊Return value is 0 for failure, 1 for success.
			logical(_PL_ Do_)(logical(_PL_ Comp_)(GENERAL _PL_,GENERAL _PL_),GENERAL *_PL_ _R_ ReferTable,address _PL_ _R_ IndexTable,address _PL_ _R_ BufferSpace,ADDRESS Count);
		}
		Sort;

		//MemClip : Data Preset Functions
		const struct
		{
			//MemClip : 1D Array Data Preset
			//＊Return value is 0 for failure, 1 for success.
			logical(_PL_ D1_)(general _PL_ _R_ Memory,GENERAL _PL_ _R_ Tile,ADDRESS Number,ADDRESS TypeSize);
#define MemC_Preset_1D_(Memory,Tile,Elements) (MemC_Assert_(sizeof(*(Memory))==sizeof(*(Tile))),MemC.Preset.D1_(Memory,Tile,Elements,sizeof(*(Tile))))
		}
		Preset;

		//MemClip : Interval Addressing Functions
		const struct
		{
			//MemClip :  1D Array Uniform or Non-Uniform Interval Addressing
			//＊Mode 0 : Uniform Interval
			//　Mode 1 : Non-Uniform Interval
			address(_PL_ D1_)(general _PL_ _R_ Indexer,GENERAL _PL_ _R_ Indexed,ADDRESS Interval,ADDRESS Indices,ADDRESS TypeSize,LOGICAL Mode);
#define MemC_Assign_1D_U_(Address,Line,Jump,Number) MemC.Assign.D1_(Address,Line,Jump,Number,sizeof(*(Line)),0)
#define MemC_Assign_1D_N_(Address,Line,Jump,Number) MemC.Assign.D1_(Address,Line,(address)(Jump),Number,sizeof(*(Line)),1)
		}
		Assign;
	};

	//MemClip : Memory Slot Functions
	const struct
	{
		//MemClip : Creation and Deletion
		const struct
		{
			//MemClip : Memory Slot Memory Allocation - Deallocate with "MemC.MS.Delete_"
			//＊Nums = SlotsNumber
			memc_ms*(_PL_ Create_)(ADDRESS SlotsNumber);
			//MemClip : Memory Slot Memory Deallocation
			general(_PL_ Delete_)(memc_ms *_PL_ _R_);

			//MemClip : Memory Slot Memory Occupation
			address(_PL_ Size_)(MEMC_MS _PL_ _R_ MemorySlot);
			//MemClip : Memory Slot Data Reset
			//＊Return value is 0 for failure, 1 for success.
			logical(_PL_ Init_)(MEMC_MS _PL_ _R_ MemorySlot);

#if(Fold_(Auto))
#define MemC_MS_Auto_(Auto,SlotsNumber)\
			auto MemC_Unit_(memc_ms,Auto,.Nums=(SlotsNumber),.Cell=(memclip[SlotsNumber]){0})
#endif
		};

		//MemClip : Some Functions
		const struct
		{
			//MemClip : Memory Slot NULL Check
			//＊Count = MemorySlot -> Slot.V[0]
			//　MemorySet = { P[1], P[2], ..., P[Count] | P = MemorySlot -> Slot.P }
			//＊Mode 0 : Return value is 1 for all NULLs, otherwise 0.
			//　Mode 1 : Return value is 0 for any NULLs, otherwise 1.
			logical(_PL_ Null_)(MEMC_MS _PL_ _R_ MemorySlot,LOGICAL CheckMode);
			//MemClip : Shape Information Setting
			//＊ShapeInfo -> Slot.V[0] = Dims
			//　{ V[1], V[2], ..., V[Dims] | V = ShapeInfo -> Slot.V } = { Arg1, Arg2, ..., ArgN }
			//＊Dims and N must be equal!
			//＊Return value is 0 for failure, 1 for success.
			logical(_PL_ Dims_)(MEMC_MS _PL_ _R_ ShapeInfo,ADDRESS Dims,...);

			//MemClip : Preserved for future usage.
			ADDRESS xPreserved[2];
		};

#if(Fold_(Generic))
#define MemC_MS_Generic_($tag,type)\
		MemC_Okay_Size_(type);\
		typedef union{memc_ms*Core;struct{ADDRESS Nums;type _PL_ Item;}_PL_ Wrap;}memc_ms$##$tag;\
		typedef const memc_ms$##$tag MEMC_MS$##$tag;\
		GENERAL _PL_ _R_ MS$##$tag=&(MS$##$tag)
#endif

#if(Fold_(Foreach))
#define MemC_MS_Foreach_(MemorySlot,type,Each)\
		for\
		(\
			address\
				*Conc_(xMemCPtr,__LINE__)=\
				(\
					MemC_Assert_(sizeof(type)==sizeof(address)),\
					((MemorySlot)->Slot.V)\
				),\
				_PL_(Conc_(xMemCEnd,__LINE__))=Conc_(xMemCPtr,__LINE__)+((MemorySlot)->Nums);\
			Conc_(xMemCPtr,__LINE__)<Conc_(xMemCEnd,__LINE__);\
			Conc_(xMemCPtr,__LINE__)++\
		)\
		MemC_Temp_(type,const(Each)=*(type*)(Conc_(xMemCPtr,__LINE__)))
#endif
	}
	MS;

	//MemClip : Memory Container Functions
	const struct
	{
		//MemClip : Creation and Deletion
		const struct
		{
			//MemClip : Memory Container Memory Allocation - Deallocate with "MemC.MC.Delete_"
			//＊Unit = TypeInfo -> SizeType
			//　Dims = ShapeInfo -> Slot.V[0]
			//　LngND = { V[1], V[2], ..., V[Dims] | V = ShapeInfo -> Slot.V }
			memc_mc*(_PL_ Create_)(GENERAL _PL_ Identification,MEMC_MS _PL_ ShapeInfo,MEMC_DT _PL_ TypeInfo);
			//MemClip : Memory Container Memory Deallocation
			general(_PL_ Delete_)(memc_mc *_PL_ _R_);

			//MemClip : Memory Container Memory Occupation
			address(_PL_ Size_)(MEMC_MC _PL_ _R_ MemoryContainer);
			//MemClip : Fill the memory container with the pointed value.
			logical(_PL_ Fill_)(MEMC_MC _PL_ _R_ MemoryContainer,GENERAL _PL_ _R_ ValuePointer);
		};

		//MemClip : Some Functions
		const struct
		{
			//MemClip : Change the type descriptor of the memory container.
			//＊Return value is 0 for failure, 1 for success.
			logical(_PL_ Change_)(memc_mc _PL_ _R_ MemoryContainer,MEMC_DT _PL_ DataType);
			//MemClip : Get the shape information of the memory container.
			//＊ShapeInfo -> Slot.V[0] = MemoryContainer -> Dims
			//　{ V[1], V[2], ..., V[Dims] | V = ShapeInfo -> Slot.V } = MemoryContainer -> LngND
			//＊Return value is 0 for failure, 1 for success.
			logical(_PL_ Form_)(MEMC_MC _PL_ _R_ MemoryContainer,MEMC_MS _PL_ _R_ ShapeInfo);

			//MemClip : Preserved for future usage.
			ADDRESS xPreserved[2];
		};
	}
	MC;

	//MemClip : Memory Lender Functions
	const struct
	{
		//MemClip : Creation and Deletion
		const struct
		{
			//MemClip : Memory Lender Memory Allocation - Deallocate with "MemC.ML.Delete_"
			//＊1 chunk is equal to 4×sizeof(address) bytes.
			//　The memory lender's head occupies 2 chunks.
			//　Each memory slice's head occupies 1 chunk.
			//＊The previous lender can be NULL, if linking is not wanted.
			memc_ml*(_PL_ Create_)(memc_ml _PL_ PreviousLender,ADDRESS ChunksNumber);
			//MemClip : Memory Lender Memory Deallocation
			//＊Return value is the memory lender's previous lender.
			memc_ml*(_PL_ Delete_)(memc_ml *_PL_ _R_);

			//MemClip : Memory Lender Memory Occupation
			address(_PL_ Size_)(MEMC_ML _PL_ _R_ MemoryLender);
			//MemClip : Kill all memory slices in all memory lenders.
			//＊Return value is 0 for failure, 1 for success.
			logical(_PL_ Kill_)(memc_ml _PL_ MemoryLender);

#if(Fold_(Static))
			//MemClip : Memory Lender Static Definition
			//＊1 chunk is equal to 4×sizeof(address) bytes.
			//　The memory lender's head occupies 2 chunks.
			//　Each memory slice's head occupies 1 chunk.
			//＊Be aware that it is not thread-safe.
#define MemC_ML_Static_(Static,Chunks)\
			static address Conc_(xMemCBank,__LINE__)[((Chunks)>3)?((Chunks)<<2):(-1)]=\
			{\
				[0]=(address)(Conc_(xMemCBank,__LINE__)),\
				[1]=(address)(Conc_(xMemCBank,__LINE__)),\
				[2]=(address)(Conc_(xMemCBank,__LINE__)),\
				[3]=xMemC_ML_Static_Caps_(Chunks),\
				[4]=xMemC_ML_Static_Caps_(Chunks),\
				[6]=1,\
				[11]=xMemC_ML_Static_Caps_(Chunks)\
			};\
			static memc_ml _PL_(Static)=(memc_ml*)(Conc_(xMemCBank,__LINE__))
#define xMemC_ML_Static_Caps_(Chunks) MemC_Size_(address,((Chunks)-3)<<2)
#endif
		};

		//MemClip : Borrow and Return
		const struct
		{
			//MemClip : Borrow a memory slice from one of memory lenders. - Return with "MemC_ML_Return_"
			general*(_PL_ Borrow_)(memc_ml _PL_ _R_ MemoryLender,ADDRESS SliceBytes);
			//MemClip : Return the memory slice to its master.
			//＊Return value is 0 for failure, 1 for success.
			logical(_PL_ Return_)(general _PL_ MemorySlice);
#define MemC_ML_Return_(MemorySlice) __dl{if(MemC.ML.Return_(MemorySlice)){(MemorySlice)=NULL;}else;}lb__

#if(Fold_(Moment))
			//MemClip : Temporarily borrow and return a memory slice from the memory lender.
#define MemC_ML_Moment_(Lender,Temp,Size,FAIL)\
			for\
			(\
				general\
					_PL_(Temp)=MemC.ML.Borrow_(Lender,Size),\
					*Conc_(xMemCTemp,__LINE__)=FULL;\
				Conc_(xMemCTemp,__LINE__);\
				Conc_(xMemCTemp,__LINE__)=NULL,MemC.ML.Return_(Temp)\
			)\
			if(!(Temp)){FAIL}else
#endif
		};

		//MemClip : Memory Slice Information
		const struct
		{
			//MemClip : Get the master of the memory slice.
			memc_ml*(_PL_ Master_)(GENERAL _PL_ _R_ MemorySlice);
			//MemClip : Get the usable bytes of the memory slice.
			address(_PL_ Usable_)(GENERAL _PL_ _R_ MemorySlice);
		};

		//MemClip : Preserved for Future Usage
		ADDRESS xPreserved[8];
	}
	ML;
}
MEMCASE;

//MemClip : Library Case Object
extern MEMCASE MemC,*MemC_(general);
#endif
#endif
