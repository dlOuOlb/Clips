/*------------------------------------------------------------------*/
/*	BitClip provides some simple bit-operation functions.			*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2019.07.12	*/
/*------------------------------------------------------------------*/

#ifndef _INC_BITCLIP
#define _INC_BITCLIP

#ifdef __OPENCL_VERSION__

#if(1)
#include <oclclip.h>
#endif

#if(Fold_(Definition:Extension Macros))
#ifdef _EMPTY_
#error The macro "_EMPTY_" is already defined.
#else
#define _EMPTY_(X) ((~(~X+0)==0)&&(~(~X+1)==1))
#endif

#ifdef _BitC_R16_
#if(_EMPTY_(_BitC_R16_))
#undef _BitC_R16_
#define _BitC_R16_ (1)
#endif
#else
#define _BitC_R16_ (0)
#endif

#ifdef _BitC_R64_
#if(_EMPTY_(_BitC_R64_))
#undef _BitC_R64_
#define _BitC_R64_ (1)
#endif
#else
#define _BitC_R64_ (0)
#endif

#if(_BitC_R16_)
#pragma OPENCL EXTENSION cl_khr_fp16 : enable
#else
#pragma OPENCL EXTENSION cl_khr_fp16 : disable
#endif

#if(_BitC_R64_)
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#else
#pragma OPENCL EXTENSION cl_khr_fp64 : disable
#endif

#undef _EMPTY_
#endif

#if(Fold_(Definition:Vector Macros))
#define Vect_(scope,num,type) _##scope##_ _##num##_##type

#define _Vect_Load_02_(Address) vload2(0,Address)
#define _Vect_Load_03_(Address) vload3(0,Address)
#define _Vect_Load_04_(Address) vload4(0,Address)
#define _Vect_Load_08_(Address) vload8(0,Address)
#define _Vect_Load_16_(Address) vload16(0,Address)
#define Vect_Load_(num,Address) _Vect_Load_##num##_(Address)

#define _Vect_Save_02_(Vector,Address) vstore2(Vector,0,Address)
#define _Vect_Save_03_(Vector,Address) vstore3(Vector,0,Address)
#define _Vect_Save_04_(Vector,Address) vstore4(Vector,0,Address)
#define _Vect_Save_08_(Vector,Address) vstore8(Vector,0,Address)
#define _Vect_Save_16_(Vector,Address) vstore16(Vector,0,Address)
#define Vect_Save_(num,Address,Vector) _Vect_Save_##num##_(Vector,Address)
#endif

#if(Fold_(Definition:Scalar and Vector Types))
#define _Parse_(oldtype,newtype,NEWTYPE) OCLC_Type_Rename_(oldtype,newtype,NEWTYPE);OCLC_Type_Rename_(oldtype##2,_02_##newtype,_02_##NEWTYPE);OCLC_Type_Rename_(oldtype##3,_03_##newtype,_03_##NEWTYPE);OCLC_Type_Rename_(oldtype##4,_04_##newtype,_04_##NEWTYPE);OCLC_Type_Rename_(oldtype##8,_08_##newtype,_08_##NEWTYPE);OCLC_Type_Rename_(oldtype##16,_16_##newtype,_16_##NEWTYPE);

OCLC_Type_Rename_(intptr_t,sintptr,SINTPTR);
OCLC_Type_Rename_(uintptr_t,uintptr,UINTPTR);

_Parse_(uchar,data_08,DATA_08);
_Parse_(ushort,data_16,DATA_16);
_Parse_(uint,data_32,DATA_32);
_Parse_(ulong,data_64,DATA_64);

_Parse_(char,inte_08,INTE_08);
_Parse_(short,inte_16,INTE_16);
_Parse_(int,inte_32,INTE_32);
_Parse_(long,inte_64,INTE_64);

#if(_BitC_R16_)
_Parse_(half,real_16,REAL_16);
#else
_Parse_(short,real_16,REAL_16);
#endif
_Parse_(float,real_32,REAL_32);
#if(_BitC_R64_)
_Parse_(double,real_64,REAL_64);
#else
_Parse_(long,real_64,REAL_64);
#endif

#undef _Parse_
#endif

#if(Fold_(Definition:Pointer Unions))
#define _Parse_Scalar_V_(scope) _##scope##_ general *G;_##scope##_ general **GG;_##scope##_ address *AA;_##scope##_ data_08 *D08;_##scope##_ data_16 *D16;_##scope##_ data_32 *D32;_##scope##_ data_64 *D64;_##scope##_ inte_08 *I08;_##scope##_ inte_16 *I16;_##scope##_ inte_32 *I32;_##scope##_ inte_64 *I64;_##scope##_ real_16 *R16;_##scope##_ real_32 *R32;_##scope##_ real_64 *R64;
#define _Parse_Scalar_C_(scope) _##scope##_ GENERAL *G;_##scope##_ GENERAL **GG;_##scope##_ ADDRESS *AA;_##scope##_ DATA_08 *D08;_##scope##_ DATA_16 *D16;_##scope##_ DATA_32 *D32;_##scope##_ DATA_64 *D64;_##scope##_ INTE_08 *I08;_##scope##_ INTE_16 *I16;_##scope##_ INTE_32 *I32;_##scope##_ INTE_64 *I64;_##scope##_ REAL_16 *R16;_##scope##_ REAL_32 *R32;_##scope##_ REAL_64 *R64;
#define _Parse_Vector_V_(scope,num) union{_##scope##_ _##num##_data_08 *D08;_##scope##_ _##num##_data_16 *D16;_##scope##_ _##num##_data_32 *D32;_##scope##_ _##num##_data_64 *D64;_##scope##_ _##num##_inte_08 *I08;_##scope##_ _##num##_inte_16 *I16;_##scope##_ _##num##_inte_32 *I32;_##scope##_ _##num##_inte_64 *I64;_##scope##_ _##num##_real_16 *R16;_##scope##_ _##num##_real_32 *R32;_##scope##_ _##num##_real_64 *R64;}_##num;
#define _Parse_Vector_C_(scope,num) union{_##scope##_ _##num##_DATA_08 *D08;_##scope##_ _##num##_DATA_16 *D16;_##scope##_ _##num##_DATA_32 *D32;_##scope##_ _##num##_DATA_64 *D64;_##scope##_ _##num##_INTE_08 *I08;_##scope##_ _##num##_INTE_16 *I16;_##scope##_ _##num##_INTE_32 *I32;_##scope##_ _##num##_INTE_64 *I64;_##scope##_ _##num##_REAL_16 *R16;_##scope##_ _##num##_REAL_32 *R32;_##scope##_ _##num##_REAL_64 *R64;}_##num;
#define _Parse_(scope,acs) union{_Parse_Scalar_##acs##_(scope);_Parse_Vector_##acs##_(scope,02);_Parse_Vector_##acs##_(scope,03);_Parse_Vector_##acs##_(scope,04);_Parse_Vector_##acs##_(scope,08);_Parse_Vector_##acs##_(scope,16);}acs;

union _bitc_cp
{
	_Parse_(C,V);
	_Parse_(C,C);
};
OCLC_Type_Declare_(union,bitc_cp,BITC_CP);

union _bitc_gp
{
	_Parse_(G,V);
	_Parse_(G,C);
};
OCLC_Type_Declare_(union,bitc_gp,BITC_GP);

union _bitc_lp
{
	_Parse_(L,V);
	_Parse_(L,C);
};
OCLC_Type_Declare_(union,bitc_lp,BITC_LP);

union _bitc_pp
{
	_Parse_(P,V);
	_Parse_(P,C);
};
OCLC_Type_Declare_(union,bitc_pp,BITC_PP);

#undef _Parse_
#undef _Parse_Vector_C_
#undef _Parse_Vector_V_
#undef _Parse_Scalar_C_
#undef _Parse_Scalar_V_
#endif

#else

#if(1)
#include <stdint.h>
#ifdef _CL
#include <CL/opencl.h>
#endif
#ifdef __OPENCL_H
#include <oclclip.h>
#else
#include <memclip.h>
#endif
#endif

#if(Fold_(Definition:Primal Types))
MemC_Type_Rename_(uint8_t,data_08,DATA_08);		//BitClip : 8-bit Natural
MemC_Type_Rename_(uint16_t,data_16,DATA_16);	//BitClip : 16-bit Natural
MemC_Type_Rename_(uint32_t,data_32,DATA_32);	//BitClip : 32-bit Natural
MemC_Type_Rename_(uint64_t,data_64,DATA_64);	//BitClip : 64-bit Natural

MemC_Type_Rename_(int8_t,inte_08,INTE_08);		//BitClip : 8-bit Integer
MemC_Type_Rename_(int16_t,inte_16,INTE_16);		//BitClip : 16-bit Integer
MemC_Type_Rename_(int32_t,inte_32,INTE_32);		//BitClip : 32-bit Integer
MemC_Type_Rename_(int64_t,inte_64,INTE_64);		//BitClip : 64-bit Integer

MemC_Type_Rename_(float,real_32,REAL_32);		//BitClip : 32-bit Single Precision Floating Point
MemC_Type_Rename_(double,real_64,REAL_64);		//BitClip : 64-bit Double Precision Floating Point

MemC_Type_Rename_(intptr_t,sintptr,SINTPTR);	//BitClip : Signed Address
MemC_Type_Rename_(uintptr_t,uintptr,UINTPTR);	//BitClip : Unsigned Address

static_assert((-1)==(((inte_08)(-1))>>1),"The bit-shift-right operation of a signed integer must preserve the sign.");
static_assert((-1)!=(((data_08)(-1))>>1),"The bit-shift-right operation of an unsigned integer must not preserve the sign.");
static_assert((~((address)(0)))==((address)((inte_08)(~0))),"Casting from a signed integer to an address value must preserve the sign.");
#endif

#if(Fold_(Definition:Derived Types))
//BitClip : Pointer Union
union _bitclip
{
	address A;	//BitClip : Address Container

	//BitClip : Access as Variable
	union
	{
		general *G;		//BitClip : General Container
		general **GG;	//BitClip : General Access
		address *AA;	//BitClip : Address Access
		data_08 *D08;	//BitClip : 8-Bit Natural Access
		data_16 *D16;	//BitClip : 16-Bit Natural Access
		data_32 *D32;	//BitClip : 32-Bit Natural Access
		data_64 *D64;	//BitClip : 64-Bit Natural Access
		inte_08 *I08;	//BitClip : 8-Bit Integer Access
		inte_16 *I16;	//BitClip : 16-Bit Integer Access
		inte_32 *I32;	//BitClip : 32-Bit Integer Access
		inte_64 *I64;	//BitClip : 64-Bit Integer Access
		real_32 *R32;	//BitClip : 32-Bit Floating Point Access
		real_64 *R64;	//BitClip : 64-Bit Floating Point Access
	}
	V;

	//BitClip : Access as Constant
	union
	{
		GENERAL *G;		//BitClip : General Container
		GENERAL **GG;	//BitClip : General Access
		ADDRESS *AA;	//BitClip : Address Access
		DATA_08 *D08;	//BitClip : 8-Bit Natural Access
		DATA_16 *D16;	//BitClip : 16-Bit Natural Access
		DATA_32 *D32;	//BitClip : 32-Bit Natural Access
		DATA_64 *D64;	//BitClip : 64-Bit Natural Access
		INTE_08 *I08;	//BitClip : 8-Bit Integer Access
		INTE_16 *I16;	//BitClip : 16-Bit Integer Access
		INTE_32 *I32;	//BitClip : 32-Bit Integer Access
		INTE_64 *I64;	//BitClip : 64-Bit Integer Access
		REAL_32 *R32;	//BitClip : 32-Bit Floating Point Access
		REAL_64 *R64;	//BitClip : 64-Bit Floating Point Access
	}
	C;
};
MemC_Type_Declare_(union,bitclip,BITCLIP);	//BitClip : Pointer Union

//BitClip : Type Enumeration
enum _bitc_te
{
	BitCTypeUnknown=-1,	//BitClip : Unknown
	BitCTypeData_08=0,	//BitClip : 8-bit Natural
	BitCTypeData_16=1,	//BitClip : 16-bit Natural
	BitCTypeData_32=2,	//BitClip : 32-bit Natural
	BitCTypeData_64=3,	//BitClip : 64-bit Natural
	BitCTypeInte_08=4,	//BitClip : 8-bit Integer
	BitCTypeInte_16=5,	//BitClip : 16-bit Integer
	BitCTypeInte_32=6,	//BitClip : 32-bit Integer
	BitCTypeInte_64=7,	//BitClip : 64-bit Integer
	BitCTypeReal_08=8,	//BitClip : 8-bit Real (Not Available)
	BitCTypeReal_16=9,	//BitClip : 16-bit Real (Special Device Only)
	BitCTypeReal_32=10,	//BitClip : 32-bit Real
	BitCTypeReal_64=11,	//BitClip : 64-bit Real
	BitCTypes=12		//BitClip : The Number of Types
};
MemC_Type_Declare_(enum,bitc_te,BITC_TE);	//BitClip : Type Enumeration

//BitClip : Bit Pointer Structure
struct _bitc_bp
{
	data_08 *Base;	//BitClip : Base Address
	sintptr Offset;	//BitClip : Bit Offset (0~7)
};
MemC_Type_Declare_(struct,bitc_bp,BITC_BP);	//BitClip : Bit Pointer Structure
#endif

#if(Fold_(Definition:Macros))
#if(Fold_(Part:BitC_Max_T##_))
#define BitC_Max_I08_(Output,InputA,InputB) {(Output)=(InputB)-(InputA);(Output)&=(Acs_(inte_08,Output)>>7);(Output)=(InputB)-(Output);}				//BitClip : Maximum of 8-bit Integer - Only valid for Data Range under 0x40
#define BitC_Max_I16_(Output,InputA,InputB) {(Output)=(InputB)-(InputA);(Output)&=(Acs_(inte_16,Output)>>15);(Output)=(InputB)-(Output);}				//BitClip : Maximum of 16-bit Integer - Only valid for Data Range under 0x4000
#define BitC_Max_I32_(Output,InputA,InputB) {(Output)=(InputB)-(InputA);(Output)&=(Acs_(inte_32,Output)>>31);(Output)=(InputB)-(Output);}				//BitClip : Maximum of 32-bit Integer - Only valid for Data Range under 0x40000000
#define BitC_Max_I64_(Output,InputA,InputB) {(Output)=(InputB)-(InputA);(Output)&=(Acs_(inte_64,Output)>>63);(Output)=(InputB)-(Output);}				//BitClip : Maximum of 64-bit Integer - Only valid for Data Range under 0x4000000000000000
#define BitC_Max_R32_(Output,InputA,InputB) {(Output)=(InputB)-(InputA);Acs_(inte_32,Output)&=(Acs_(inte_32,Output)>>31);(Output)=(InputB)-(Output);}	//BitClip : Maximum of 32-bit Real
#define BitC_Max_R64_(Output,InputA,InputB) {(Output)=(InputB)-(InputA);Acs_(inte_64,Output)&=(Acs_(inte_64,Output)>>63);(Output)=(InputB)-(Output);}	//BitClip : Maximum of 64-bit Real
#endif

#if(Fold_(Part:BitC_Min_T##_))
#define BitC_Min_I08_(Output,InputA,InputB) {(Output)=(InputA)-(InputB);(Output)&=(Acs_(inte_08,Output)>>7);(Output)+=(InputB);}				//BitClip : Minimum of 8-bit Integer - Only valid for Data Range under 0x40
#define BitC_Min_I16_(Output,InputA,InputB) {(Output)=(InputA)-(InputB);(Output)&=(Acs_(inte_16,Output)>>15);(Output)+=(InputB);}				//BitClip : Minimum of 16-bit Integer - Only valid for Data Range under 0x4000
#define BitC_Min_I32_(Output,InputA,InputB) {(Output)=(InputA)-(InputB);(Output)&=(Acs_(inte_32,Output)>>31);(Output)+=(InputB);}				//BitClip : Minimum of 32-bit Integer - Only valid for Data Range under 0x40000000
#define BitC_Min_I64_(Output,InputA,InputB) {(Output)=(InputA)-(InputB);(Output)&=(Acs_(inte_64,Output)>>63);(Output)+=(InputB);}				//BitClip : Minimum of 64-bit Integer - Only valid for Data Range under 0x4000000000000000
#define BitC_Min_R32_(Output,InputA,InputB) {(Output)=(InputA)-(InputB);Acs_(inte_32,Output)&=(Acs_(inte_32,Output)>>31);(Output)+=(InputB);}	//BitClip : Minimum of 32-bit Real
#define BitC_Min_R64_(Output,InputA,InputB) {(Output)=(InputA)-(InputB);Acs_(inte_64,Output)&=(Acs_(inte_64,Output)>>63);(Output)+=(InputB);}	//BitClip : Minimum of 64-bit Real
#endif

#if(Fold_(Part:BitC_Abs_P_T##_))
#define BitC_Abs_P_I08_(Output,Input) {(Output)=Acs_(inte_08,Input)>>7;(Output)^=((Input)+(Output));}	//BitClip : Positive Absolute of 8-bit Integer
#define BitC_Abs_P_I16_(Output,Input) {(Output)=Acs_(inte_16,Input)>>15;(Output)^=((Input)+(Output));}	//BitClip : Positive Absolute of 16-bit Integer
#define BitC_Abs_P_I32_(Output,Input) {(Output)=Acs_(inte_32,Input)>>31;(Output)^=((Input)+(Output));}	//BitClip : Positive Absolute of 32-bit Integer
#define BitC_Abs_P_I64_(Output,Input) {(Output)=Acs_(inte_64,Input)>>63;(Output)^=((Input)+(Output));}	//BitClip : Positive Absolute of 64-bit Integer
#define BitC_Abs_P_R32_(Output,Input) {Acs_(inte_32,Output)=Acs_(inte_32,Input)&0x7FFFFFFF;}			//BitClip : Positive Absolute of 32-bit Real
#define BitC_Abs_P_R64_(Output,Input) {Acs_(inte_64,Output)=Acs_(inte_64,Input)&0x7FFFFFFFFFFFFFFF;}	//BitClip : Positive Absolute of 64-bit Real
#endif

#if(Fold_(Part:BitC_Abs_N_T##_))
#define BitC_Abs_N_I08_(Output,Input) {(Output)=Acs_(inte_08,Input)>>7;(Output)=~(Output);(Output)^=((Input)+(Output));}	//BitClip : Negative Absolute of 8-bit Integer
#define BitC_Abs_N_I16_(Output,Input) {(Output)=Acs_(inte_16,Input)>>15;(Output)=~(Output);(Output)^=((Input)+(Output));}	//BitClip : Negative Absolute of 16-bit Integer
#define BitC_Abs_N_I32_(Output,Input) {(Output)=Acs_(inte_32,Input)>>31;(Output)=~(Output);(Output)^=((Input)+(Output));}	//BitClip : Negative Absolute of 32-bit Integer
#define BitC_Abs_N_I64_(Output,Input) {(Output)=Acs_(inte_64,Input)>>63;(Output)=~(Output);(Output)^=((Input)+(Output));}	//BitClip : Negative Absolute of 64-bit Integer
#define BitC_Abs_N_R32_(Output,Input) {Acs_(inte_32,Output)=Acs_(inte_32,Input)|0x80000000;}								//BitClip : Negative Absolute of 32-bit Real
#define BitC_Abs_N_R64_(Output,Input) {Acs_(inte_64,Output)=Acs_(inte_64,Input)|0x8000000000000000;}						//BitClip : Negative Absolute of 64-bit Real
#endif

#if(Fold_(Part:BitC_Lim_P_T##_))
#define BitC_Lim_P_I08_(Output,Input) {(Output)=Acs_(inte_08,Input)>>7;(Output)=~(Output);(Output)&=(Input);}																//BitClip : Positive Clipping of 8-bit Integer
#define BitC_Lim_P_I16_(Output,Input) {(Output)=Acs_(inte_16,Input)>>15;(Output)=~(Output);(Output)&=(Input);}																//BitClip : Positive Clipping of 16-bit Integer
#define BitC_Lim_P_I32_(Output,Input) {(Output)=Acs_(inte_32,Input)>>31;(Output)=~(Output);(Output)&=(Input);}																//BitClip : Positive Clipping of 32-bit Integer
#define BitC_Lim_P_I64_(Output,Input) {(Output)=Acs_(inte_64,Input)>>63;(Output)=~(Output);(Output)&=(Input);}																//BitClip : Positive Clipping of 64-bit Integer
#define BitC_Lim_P_R32_(Output,Input) {Acs_(inte_32,Output)=Acs_(inte_32,Input)>>31;Acs_(inte_32,Output)=~Acs_(inte_32,Output);Acs_(inte_32,Output)&=Acs_(inte_32,Input);}	//BitClip : Positive Clipping of 32-bit Real
#define BitC_Lim_P_R64_(Output,Input) {Acs_(inte_64,Output)=Acs_(inte_64,Input)>>63;Acs_(inte_64,Output)=~Acs_(inte_64,Output);Acs_(inte_64,Output)&=Acs_(inte_64,Input);}	//BitClip : Positive Clipping of 64-bit Real
#endif

#if(Fold_(Part:BitC_Lim_N_T##_))
#define BitC_Lim_N_I08_(Output,Input) {(Output)=Acs_(inte_08,Input)>>7;(Output)&=(Input);}										//BitClip : Negative Clipping of 8-bit Integer
#define BitC_Lim_N_I16_(Output,Input) {(Output)=Acs_(inte_16,Input)>>15;(Output)&=(Input);}										//BitClip : Negative Clipping of 16-bit Integer
#define BitC_Lim_N_I32_(Output,Input) {(Output)=Acs_(inte_32,Input)>>31;(Output)&=(Input);}										//BitClip : Negative Clipping of 32-bit Integer
#define BitC_Lim_N_I64_(Output,Input) {(Output)=Acs_(inte_64,Input)>>63;(Output)&=(Input);}										//BitClip : Negative Clipping of 64-bit Integer
#define BitC_Lim_N_R32_(Output,Input) {Acs_(inte_32,Output)=Acs_(inte_32,Input)>>31;Acs_(inte_32,Output)&=Acs_(inte_32,Input);}	//BitClip : Negative Clipping of 32-bit Real
#define BitC_Lim_N_R64_(Output,Input) {Acs_(inte_64,Output)=Acs_(inte_64,Input)>>63;Acs_(inte_64,Output)&=Acs_(inte_64,Input);}	//BitClip : Negative Clipping of 64-bit Real
#endif
#endif

#if(Fold_(Library Casing))
//BitClip : Library Case Structure
struct _bitcase
{
	//BitClip : Library Version
	BYTE_08 _PL_ Version;

	//BitClip : Type Descriptor Set
	const struct
	{
		MEMC_DT _PL_ D08;	//BitClip : data_08
		MEMC_DT _PL_ D16;	//BitClip : data_16
		MEMC_DT _PL_ D32;	//BitClip : data_32
		MEMC_DT _PL_ D64;	//BitClip : data_64
		MEMC_DT _PL_ I08;	//BitClip : inte_08
		MEMC_DT _PL_ I16;	//BitClip : inte_16
		MEMC_DT _PL_ I32;	//BitClip : inte_32
		MEMC_DT _PL_ I64;	//BitClip : inte_64
		MEMC_DT _PL_ R08;	//BitClip : real_08
		MEMC_DT _PL_ R16;	//BitClip : real_16
		MEMC_DT _PL_ R32;	//BitClip : real_32
		MEMC_DT _PL_ R64;	//BitClip : real_64

		//BitClip : Descriptor to Enumeration Conversion
		bitc_te(_PL_ Enum_)(MEMC_DT _PL_ Descriptor);
		//BitClip : Enumeration to Descriptor Conversion
		MEMC_DT*(_PL_ Desc_)(BITC_TE Enumeration);
	}
	Type;

	//BitClip : Global Constant Number Set
	const struct
	{
		//BitClip : Mask Set
		const struct
		{
			ADDRESS _PL_ Safe;	//BitClip : Safe[n]＝0-(1<<n) where n＝0, 1, ..., 7.
			ADDRESS _PL_ Rest;	//BitClip : Rest[n]＝(1<<n)-1 where n＝0, 1, ..., 7.
		}
		Mask;

		//BitClip : Pi Number Set
		const struct
		{
			//BitClip : 32-bit Pi Number
			//＊[0] : π
			//　[1] : 1／π
			REAL_32 _PL_ R32;
			//BitClip : 64-bit Pi Number
			//＊[0] : π
			//　[1] : 1／π
			REAL_64 _PL_ R64;
		}
		Pi;

		//BitClip : Euler Number Set
		const struct
		{
			//BitClip : 32-bit Euler Number
			//＊[0] : ｅ
			//　[1] : 1／ｅ
			REAL_32 _PL_ R32;
			//BitClip : 64-bit Euler Number
			//＊[0] : ｅ
			//　[1] : 1／ｅ
			REAL_64 _PL_ R64;
		}
		Euler;

		//BitClip : Infinite Number Set
		const struct
		{
			//BitClip : 32-bit Infinite Number
			//＊[0] : ＋∞
			//　[1] : －∞
			REAL_32 _PL_ R32;
			//BitClip : 64-bit Infinite Number
			//＊[0] : ＋∞
			//　[1] : －∞
			REAL_64 _PL_ R64;
		}
		Inf;

		//BitClip : Not-a-Number Set
		const struct
		{
			//BitClip : 32-bit Not-a-Number
			//＊[0] : ＋NaN
			//　[1] : －NaN
			REAL_32 _PL_ R32;
			//BitClip : 64-bit Not-a-Number
			//＊[0] : ＋NaN
			//　[1] : －NaN
			REAL_64 _PL_ R64;
		}
		NaN;
	}
	Const;

	const struct
	{
		//BitClip : Array Reformation
		//＊SourceShape[dim] == TargetShape[ReformingAxis[dim]] where dim＜Dimensions.
		//＊Return value is ~0 for success, 0 for failure.
		logical(_PL_ Reform_)(GENERAL _PL_ SourceArray,general _PL_ TargetArray,ADDRESS _PL_ SourceShape,ADDRESS _PL_ ReformingAxis,ADDRESS Dimensions,ADDRESS TypeSize);
#define BitC_Reform_(S,T,SShp,StoTAxis,Dims) ((sizeof(*(S))==sizeof(*(T)))?(BitC.Reform_(S,T,SShp,StoTAxis,Dims,sizeof(*(S)))):(BitCNull))

		//BitClip : Endian Flipping Function Set
		const struct
		{
			//BitClip : Endianness
			//＊Pointed value is 0x00 for big-endian, 0x01 for little-endian.
			DATA_08 _PL_ Endianness;

			//BitClip : 8-bit Natural Endian Flipping
			general(_PL_ D08_)(data_08 _PL_ Data,ADDRESS Length);
			//BitClip : 16-bit Natural Endian Flipping
			general(_PL_ D16_)(data_16 _PL_ Data,ADDRESS Length);
			//BitClip : 32-bit Natural Endian Flipping
			general(_PL_ D32_)(data_32 _PL_ Data,ADDRESS Length);
			//BitClip : 64-bit Natural Endian Flipping
			general(_PL_ D64_)(data_64 _PL_ Data,ADDRESS Length);
			//BitClip : 8-bit Integer Endian Flipping
			general(_PL_ I08_)(inte_08 _PL_ Data,ADDRESS Length);
			//BitClip : 16-bit Integer Endian Flipping
			general(_PL_ I16_)(inte_16 _PL_ Data,ADDRESS Length);
			//BitClip : 32-bit Integer Endian Flipping
			general(_PL_ I32_)(inte_32 _PL_ Data,ADDRESS Length);
			//BitClip : 64-bit Integer Endian Flipping
			general(_PL_ I64_)(inte_64 _PL_ Data,ADDRESS Length);
			//BitClip : 32-bit Real Endian Flipping
			general(_PL_ R32_)(real_32 _PL_ Data,ADDRESS Length);
			//BitClip : 64-bit Real Endian Flipping
			general(_PL_ R64_)(real_64 _PL_ Data,ADDRESS Length);
		}
		Endian;

		//BitClip : Type Casting Function Set
		const struct
		{
			//BitClip : Casting from 8-bit Natural
			const struct
			{
				//BitClip : 8-bit Natural to 8-bit Natural Type Casting
				general(_PL_ D08_)(DATA_08 *_R_ I,data_08 *_R_ O,ADDRESS N);
				//BitClip : 8-bit Natural to 16-bit Natural Type Casting
				general(_PL_ D16_)(DATA_08 *_R_ I,data_16 *_R_ O,ADDRESS N);
				//BitClip : 8-bit Natural to 32-bit Natural Type Casting
				general(_PL_ D32_)(DATA_08 *_R_ I,data_32 *_R_ O,ADDRESS N);
				//BitClip : 8-bit Natural to 64-bit Natural Type Casting
				general(_PL_ D64_)(DATA_08 *_R_ I,data_64 *_R_ O,ADDRESS N);
				//BitClip : 8-bit Natural to 8-bit Integer Type Casting
				general(_PL_ I08_)(DATA_08 *_R_ I,inte_08 *_R_ O,ADDRESS N);
				//BitClip : 8-bit Natural to 16-bit Integer Type Casting
				general(_PL_ I16_)(DATA_08 *_R_ I,inte_16 *_R_ O,ADDRESS N);
				//BitClip : 8-bit Natural to 32-bit Integer Type Casting
				general(_PL_ I32_)(DATA_08 *_R_ I,inte_32 *_R_ O,ADDRESS N);
				//BitClip : 8-bit Natural to 64-bit Integer Type Casting
				general(_PL_ I64_)(DATA_08 *_R_ I,inte_64 *_R_ O,ADDRESS N);
				//BitClip : 8-bit Natural to 32-bit Real Type Casting
				general(_PL_ R32_)(DATA_08 *_R_ I,real_32 *_R_ O,ADDRESS N);
				//BitClip : 8-bit Natural to 64-bit Real Type Casting
				general(_PL_ R64_)(DATA_08 *_R_ I,real_64 *_R_ O,ADDRESS N);
			}
			D08;

			//BitClip : Casting from 16-bit Natural
			const struct
			{
				//BitClip : 16-bit Natural to 8-bit Natural Type Casting
				general(_PL_ D08_)(DATA_16 *_R_ I,data_08 *_R_ O,ADDRESS N);
				//BitClip : 16-bit Natural to 16-bit Natural Type Casting
				general(_PL_ D16_)(DATA_16 *_R_ I,data_16 *_R_ O,ADDRESS N);
				//BitClip : 16-bit Natural to 32-bit Natural Type Casting
				general(_PL_ D32_)(DATA_16 *_R_ I,data_32 *_R_ O,ADDRESS N);
				//BitClip : 16-bit Natural to 64-bit Natural Type Casting
				general(_PL_ D64_)(DATA_16 *_R_ I,data_64 *_R_ O,ADDRESS N);
				//BitClip : 16-bit Natural to 8-bit Integer Type Casting
				general(_PL_ I08_)(DATA_16 *_R_ I,inte_08 *_R_ O,ADDRESS N);
				//BitClip : 16-bit Natural to 16-bit Integer Type Casting
				general(_PL_ I16_)(DATA_16 *_R_ I,inte_16 *_R_ O,ADDRESS N);
				//BitClip : 16-bit Natural to 32-bit Integer Type Casting
				general(_PL_ I32_)(DATA_16 *_R_ I,inte_32 *_R_ O,ADDRESS N);
				//BitClip : 16-bit Natural to 64-bit Integer Type Casting
				general(_PL_ I64_)(DATA_16 *_R_ I,inte_64 *_R_ O,ADDRESS N);
				//BitClip : 16-bit Natural to 32-bit Real Type Casting
				general(_PL_ R32_)(DATA_16 *_R_ I,real_32 *_R_ O,ADDRESS N);
				//BitClip : 16-bit Natural to 64-bit Real Type Casting
				general(_PL_ R64_)(DATA_16 *_R_ I,real_64 *_R_ O,ADDRESS N);
			}
			D16;

			//BitClip : Casting from 32-bit Natural
			const struct
			{
				//BitClip : 32-bit Natural to 8-bit Natural Type Casting
				general(_PL_ D08_)(DATA_32 *_R_ I,data_08 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Natural to 16-bit Natural Type Casting
				general(_PL_ D16_)(DATA_32 *_R_ I,data_16 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Natural to 32-bit Natural Type Casting
				general(_PL_ D32_)(DATA_32 *_R_ I,data_32 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Natural to 64-bit Natural Type Casting
				general(_PL_ D64_)(DATA_32 *_R_ I,data_64 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Natural to 8-bit Integer Type Casting
				general(_PL_ I08_)(DATA_32 *_R_ I,inte_08 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Natural to 16-bit Integer Type Casting
				general(_PL_ I16_)(DATA_32 *_R_ I,inte_16 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Natural to 32-bit Integer Type Casting
				general(_PL_ I32_)(DATA_32 *_R_ I,inte_32 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Natural to 64-bit Integer Type Casting
				general(_PL_ I64_)(DATA_32 *_R_ I,inte_64 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Natural to 32-bit Real Type Casting
				general(_PL_ R32_)(DATA_32 *_R_ I,real_32 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Natural to 64-bit Real Type Casting
				general(_PL_ R64_)(DATA_32 *_R_ I,real_64 *_R_ O,ADDRESS N);
			}
			D32;

			//BitClip : Casting from 64-bit Natural
			const struct
			{
				//BitClip : 64-bit Natural to 8-bit Natural Type Casting
				general(_PL_ D08_)(DATA_64 *_R_ I,data_08 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Natural to 16-bit Natural Type Casting
				general(_PL_ D16_)(DATA_64 *_R_ I,data_16 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Natural to 32-bit Natural Type Casting
				general(_PL_ D32_)(DATA_64 *_R_ I,data_32 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Natural to 64-bit Natural Type Casting
				general(_PL_ D64_)(DATA_64 *_R_ I,data_64 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Natural to 8-bit Integer Type Casting
				general(_PL_ I08_)(DATA_64 *_R_ I,inte_08 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Natural to 16-bit Integer Type Casting
				general(_PL_ I16_)(DATA_64 *_R_ I,inte_16 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Natural to 32-bit Integer Type Casting
				general(_PL_ I32_)(DATA_64 *_R_ I,inte_32 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Natural to 64-bit Integer Type Casting
				general(_PL_ I64_)(DATA_64 *_R_ I,inte_64 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Natural to 32-bit Real Type Casting
				general(_PL_ R32_)(DATA_64 *_R_ I,real_32 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Natural to 64-bit Real Type Casting
				general(_PL_ R64_)(DATA_64 *_R_ I,real_64 *_R_ O,ADDRESS N);
			}
			D64;

			//BitClip : Casting from 8-bit Integer
			const struct
			{
				//BitClip : 8-bit Integer to 8-bit Natural Type Casting
				general(_PL_ D08_)(INTE_08 *_R_ I,data_08 *_R_ O,ADDRESS N);
				//BitClip : 8-bit Integer to 16-bit Natural Type Casting
				general(_PL_ D16_)(INTE_08 *_R_ I,data_16 *_R_ O,ADDRESS N);
				//BitClip : 8-bit Integer to 32-bit Natural Type Casting
				general(_PL_ D32_)(INTE_08 *_R_ I,data_32 *_R_ O,ADDRESS N);
				//BitClip : 8-bit Integer to 64-bit Natural Type Casting
				general(_PL_ D64_)(INTE_08 *_R_ I,data_64 *_R_ O,ADDRESS N);
				//BitClip : 8-bit Integer to 8-bit Integer Type Casting
				general(_PL_ I08_)(INTE_08 *_R_ I,inte_08 *_R_ O,ADDRESS N);
				//BitClip : 8-bit Integer to 16-bit Integer Type Casting
				general(_PL_ I16_)(INTE_08 *_R_ I,inte_16 *_R_ O,ADDRESS N);
				//BitClip : 8-bit Integer to 32-bit Integer Type Casting
				general(_PL_ I32_)(INTE_08 *_R_ I,inte_32 *_R_ O,ADDRESS N);
				//BitClip : 8-bit Integer to 64-bit Integer Type Casting
				general(_PL_ I64_)(INTE_08 *_R_ I,inte_64 *_R_ O,ADDRESS N);
				//BitClip : 8-bit Integer to 32-bit Real Type Casting
				general(_PL_ R32_)(INTE_08 *_R_ I,real_32 *_R_ O,ADDRESS N);
				//BitClip : 8-bit Integer to 64-bit Real Type Casting
				general(_PL_ R64_)(INTE_08 *_R_ I,real_64 *_R_ O,ADDRESS N);
			}
			I08;

			//BitClip : Casting from 16-bit Integer
			const struct
			{
				//BitClip : 16-bit Integer to 8-bit Natural Type Casting
				general(_PL_ D08_)(INTE_16 *_R_ I,data_08 *_R_ O,ADDRESS N);
				//BitClip : 16-bit Integer to 16-bit Natural Type Casting
				general(_PL_ D16_)(INTE_16 *_R_ I,data_16 *_R_ O,ADDRESS N);
				//BitClip : 16-bit Integer to 32-bit Natural Type Casting
				general(_PL_ D32_)(INTE_16 *_R_ I,data_32 *_R_ O,ADDRESS N);
				//BitClip : 16-bit Integer to 64-bit Natural Type Casting
				general(_PL_ D64_)(INTE_16 *_R_ I,data_64 *_R_ O,ADDRESS N);
				//BitClip : 16-bit Integer to 8-bit Integer Type Casting
				general(_PL_ I08_)(INTE_16 *_R_ I,inte_08 *_R_ O,ADDRESS N);
				//BitClip : 16-bit Integer to 16-bit Integer Type Casting
				general(_PL_ I16_)(INTE_16 *_R_ I,inte_16 *_R_ O,ADDRESS N);
				//BitClip : 16-bit Integer to 32-bit Integer Type Casting
				general(_PL_ I32_)(INTE_16 *_R_ I,inte_32 *_R_ O,ADDRESS N);
				//BitClip : 16-bit Integer to 64-bit Integer Type Casting
				general(_PL_ I64_)(INTE_16 *_R_ I,inte_64 *_R_ O,ADDRESS N);
				//BitClip : 16-bit Integer to 32-bit Real Type Casting
				general(_PL_ R32_)(INTE_16 *_R_ I,real_32 *_R_ O,ADDRESS N);
				//BitClip : 16-bit Integer to 64-bit Real Type Casting
				general(_PL_ R64_)(INTE_16 *_R_ I,real_64 *_R_ O,ADDRESS N);
			}
			I16;

			//BitClip : Casting from 32-bit Integer
			const struct
			{
				//BitClip : 32-bit Integer to 8-bit Natural Type Casting
				general(_PL_ D08_)(INTE_32 *_R_ I,data_08 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Integer to 16-bit Natural Type Casting
				general(_PL_ D16_)(INTE_32 *_R_ I,data_16 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Integer to 32-bit Natural Type Casting
				general(_PL_ D32_)(INTE_32 *_R_ I,data_32 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Integer to 64-bit Natural Type Casting
				general(_PL_ D64_)(INTE_32 *_R_ I,data_64 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Integer to 8-bit Integer Type Casting
				general(_PL_ I08_)(INTE_32 *_R_ I,inte_08 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Integer to 16-bit Integer Type Casting
				general(_PL_ I16_)(INTE_32 *_R_ I,inte_16 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Integer to 32-bit Integer Type Casting
				general(_PL_ I32_)(INTE_32 *_R_ I,inte_32 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Integer to 64-bit Integer Type Casting
				general(_PL_ I64_)(INTE_32 *_R_ I,inte_64 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Integer to 32-bit Real Type Casting
				general(_PL_ R32_)(INTE_32 *_R_ I,real_32 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Integer to 64-bit Real Type Casting
				general(_PL_ R64_)(INTE_32 *_R_ I,real_64 *_R_ O,ADDRESS N);
			}
			I32;

			//BitClip : Casting from 64-bit Integer
			const struct
			{
				//BitClip : 64-bit Integer to 8-bit Natural Type Casting
				general(_PL_ D08_)(INTE_64 *_R_ I,data_08 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Integer to 16-bit Natural Type Casting
				general(_PL_ D16_)(INTE_64 *_R_ I,data_16 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Integer to 32-bit Natural Type Casting
				general(_PL_ D32_)(INTE_64 *_R_ I,data_32 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Integer to 64-bit Natural Type Casting
				general(_PL_ D64_)(INTE_64 *_R_ I,data_64 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Integer to 8-bit Integer Type Casting
				general(_PL_ I08_)(INTE_64 *_R_ I,inte_08 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Integer to 16-bit Integer Type Casting
				general(_PL_ I16_)(INTE_64 *_R_ I,inte_16 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Integer to 32-bit Integer Type Casting
				general(_PL_ I32_)(INTE_64 *_R_ I,inte_32 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Integer to 64-bit Integer Type Casting
				general(_PL_ I64_)(INTE_64 *_R_ I,inte_64 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Integer to 32-bit Real Type Casting
				general(_PL_ R32_)(INTE_64 *_R_ I,real_32 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Integer to 64-bit Real Type Casting
				general(_PL_ R64_)(INTE_64 *_R_ I,real_64 *_R_ O,ADDRESS N);
			}
			I64;

			//BitClip : Casting from 32-bit Real
			const struct
			{
				//BitClip : 32-bit Real to 8-bit Natural Type Casting
				general(_PL_ D08_)(REAL_32 *_R_ I,data_08 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Real to 16-bit Natural Type Casting
				general(_PL_ D16_)(REAL_32 *_R_ I,data_16 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Real to 32-bit Natural Type Casting
				general(_PL_ D32_)(REAL_32 *_R_ I,data_32 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Real to 64-bit Natural Type Casting
				general(_PL_ D64_)(REAL_32 *_R_ I,data_64 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Real to 8-bit Integer Type Casting
				general(_PL_ I08_)(REAL_32 *_R_ I,inte_08 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Real to 16-bit Integer Type Casting
				general(_PL_ I16_)(REAL_32 *_R_ I,inte_16 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Real to 32-bit Integer Type Casting
				general(_PL_ I32_)(REAL_32 *_R_ I,inte_32 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Real to 64-bit Integer Type Casting
				general(_PL_ I64_)(REAL_32 *_R_ I,inte_64 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Real to 32-bit Real Type Casting
				general(_PL_ R32_)(REAL_32 *_R_ I,real_32 *_R_ O,ADDRESS N);
				//BitClip : 32-bit Real to 64-bit Real Type Casting
				general(_PL_ R64_)(REAL_32 *_R_ I,real_64 *_R_ O,ADDRESS N);
			}
			R32;

			//BitClip : Casting from 64-bit Real
			const struct
			{
				//BitClip : 64-bit Real to 8-bit Natural Type Casting
				general(_PL_ D08_)(REAL_64 *_R_ I,data_08 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Real to 16-bit Natural Type Casting
				general(_PL_ D16_)(REAL_64 *_R_ I,data_16 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Real to 32-bit Natural Type Casting
				general(_PL_ D32_)(REAL_64 *_R_ I,data_32 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Real to 64-bit Natural Type Casting
				general(_PL_ D64_)(REAL_64 *_R_ I,data_64 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Real to 8-bit Integer Type Casting
				general(_PL_ I08_)(REAL_64 *_R_ I,inte_08 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Real to 16-bit Integer Type Casting
				general(_PL_ I16_)(REAL_64 *_R_ I,inte_16 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Real to 32-bit Integer Type Casting
				general(_PL_ I32_)(REAL_64 *_R_ I,inte_32 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Real to 64-bit Integer Type Casting
				general(_PL_ I64_)(REAL_64 *_R_ I,inte_64 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Real to 32-bit Real Type Casting
				general(_PL_ R32_)(REAL_64 *_R_ I,real_32 *_R_ O,ADDRESS N);
				//BitClip : 64-bit Real to 64-bit Real Type Casting
				general(_PL_ R64_)(REAL_64 *_R_ I,real_64 *_R_ O,ADDRESS N);
			}
			R64;
		}
		Caster;

		//BitClip : Bit Operation Function Set
		const struct
		{
			//BitClip : NOT Operation
			const struct
			{
				//BitClip : 8-bit Natural NOT Operation
				//＊C[n]＝~A[n]
				general(_PL_ D08_)(data_08 _PL_ C,DATA_08 _PL_ A,ADDRESS N);
				//BitClip : 16-bit Natural NOT Operation
				//＊C[n]＝~A[n]
				general(_PL_ D16_)(data_16 _PL_ C,DATA_16 _PL_ A,ADDRESS N);
				//BitClip : 32-bit Natural NOT Operation
				//＊C[n]＝~A[n]
				general(_PL_ D32_)(data_32 _PL_ C,DATA_32 _PL_ A,ADDRESS N);
				//BitClip : 64-bit Natural NOT Operation
				//＊C[n]＝~A[n]
				general(_PL_ D64_)(data_64 _PL_ C,DATA_64 _PL_ A,ADDRESS N);
				//BitClip : 8-bit Integer NOT Operation
				//＊C[n]＝~A[n]
				general(_PL_ I08_)(inte_08 _PL_ C,INTE_08 _PL_ A,ADDRESS N);
				//BitClip : 16-bit Integer NOT Operation
				//＊C[n]＝~A[n]
				general(_PL_ I16_)(inte_16 _PL_ C,INTE_16 _PL_ A,ADDRESS N);
				//BitClip : 32-bit Integer NOT Operation
				//＊C[n]＝~A[n]
				general(_PL_ I32_)(inte_32 _PL_ C,INTE_32 _PL_ A,ADDRESS N);
				//BitClip : 64-bit Integer NOT Operation
				//＊C[n]＝~A[n]
				general(_PL_ I64_)(inte_64 _PL_ C,INTE_64 _PL_ A,ADDRESS N);
			}
			N_1;

			//BitClip : Shift Operation
			const struct
			{
				//BitClip : 8-Bit Natural Shift Operation
				//＊C[n]＝(S>0)?(A[n]<<S):(A[n]>>(-S))
				general(_PL_ D08_)(data_08 *C,DATA_08 *A,INTEGER S,ADDRESS N);
				//BitClip : 16-Bit Natural Shift Operation
				//＊C[n]＝(S>0)?(A[n]<<S):(A[n]>>(-S))
				general(_PL_ D16_)(data_16 *C,DATA_16 *A,INTEGER S,ADDRESS N);
				//BitClip : 32-Bit Natural Shift Operation
				//＊C[n]＝(S>0)?(A[n]<<S):(A[n]>>(-S))
				general(_PL_ D32_)(data_32 *C,DATA_32 *A,INTEGER S,ADDRESS N);
				//BitClip : 64-Bit Natural Shift Operation
				//＊C[n]＝(S>0)?(A[n]<<S):(A[n]>>(-S))
				general(_PL_ D64_)(data_64 *C,DATA_64 *A,INTEGER S,ADDRESS N);
				//BitClip : 8-Bit Integer Shift Operation
				//＊C[n]＝(S>0)?(A[n]<<S):(A[n]>>(-S))
				general(_PL_ I08_)(inte_08 *C,INTE_08 *A,INTEGER S,ADDRESS N);
				//BitClip : 16-Bit Integer Shift Operation
				//＊C[n]＝(S>0)?(A[n]<<S):(A[n]>>(-S))
				general(_PL_ I16_)(inte_16 *C,INTE_16 *A,INTEGER S,ADDRESS N);
				//BitClip : 32-Bit Integer Shift Operation
				//＊C[n]＝(S>0)?(A[n]<<S):(A[n]>>(-S))
				general(_PL_ I32_)(inte_32 *C,INTE_32 *A,INTEGER S,ADDRESS N);
				//BitClip : 64-Bit Integer Shift Operation
				//＊C[n]＝(S>0)?(A[n]<<S):(A[n]>>(-S))
				general(_PL_ I64_)(inte_64 *C,INTE_64 *A,INTEGER S,ADDRESS N);
			}
			S_1;

			//BitClip : AND Operation
			const struct
			{
				//BitClip : 8-bit Natural AND Operation
				//＊C[n]＝A[n]&M
				general(_PL_ D08_)(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 M,ADDRESS N);
				//BitClip : 16-bit Natural AND Operation
				//＊C[n]＝A[n]&M
				general(_PL_ D16_)(data_16 _PL_ C,DATA_16 _PL_ A,DATA_16 M,ADDRESS N);
				//BitClip : 32-bit Natural AND Operation
				//＊C[n]＝A[n]&M
				general(_PL_ D32_)(data_32 _PL_ C,DATA_32 _PL_ A,DATA_32 M,ADDRESS N);
				//BitClip : 64-bit Natural AND Operation
				//＊C[n]＝A[n]&M
				general(_PL_ D64_)(data_64 _PL_ C,DATA_64 _PL_ A,DATA_64 M,ADDRESS N);
				//BitClip : 8-bit Integer AND Operation
				//＊C[n]＝A[n]&M
				general(_PL_ I08_)(inte_08 _PL_ C,INTE_08 _PL_ A,INTE_08 M,ADDRESS N);
				//BitClip : 16-bit Integer AND Operation
				//＊C[n]＝A[n]&M
				general(_PL_ I16_)(inte_16 _PL_ C,INTE_16 _PL_ A,INTE_16 M,ADDRESS N);
				//BitClip : 32-bit Integer AND Operation
				//＊C[n]＝A[n]&M
				general(_PL_ I32_)(inte_32 _PL_ C,INTE_32 _PL_ A,INTE_32 M,ADDRESS N);
				//BitClip : 64-bit Integer AND Operation
				//＊C[n]＝A[n]&M
				general(_PL_ I64_)(inte_64 _PL_ C,INTE_64 _PL_ A,INTE_64 M,ADDRESS N);
			}
			A_1;

			//BitClip : AND Operation
			const struct
			{
				//BitClip : 8-bit Natural AND Operation
				//＊C[n]＝A[n]&B[n]
				general(_PL_ D08_)(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 _PL_ B,ADDRESS N);
				//BitClip : 16-bit Natural AND Operation
				//＊C[n]＝A[n]&B[n]
				general(_PL_ D16_)(data_16 _PL_ C,DATA_16 _PL_ A,DATA_16 _PL_ B,ADDRESS N);
				//BitClip : 32-bit Natural AND Operation
				//＊C[n]＝A[n]&B[n]
				general(_PL_ D32_)(data_32 _PL_ C,DATA_32 _PL_ A,DATA_32 _PL_ B,ADDRESS N);
				//BitClip : 64-bit Natural AND Operation
				//＊C[n]＝A[n]&B[n]
				general(_PL_ D64_)(data_64 _PL_ C,DATA_64 _PL_ A,DATA_64 _PL_ B,ADDRESS N);
				//BitClip : 8-bit Integer AND Operation
				//＊C[n]＝A[n]&B[n]
				general(_PL_ I08_)(inte_08 _PL_ C,INTE_08 _PL_ A,INTE_08 _PL_ B,ADDRESS N);
				//BitClip : 16-bit Integer AND Operation
				//＊C[n]＝A[n]&B[n]
				general(_PL_ I16_)(inte_16 _PL_ C,INTE_16 _PL_ A,INTE_16 _PL_ B,ADDRESS N);
				//BitClip : 32-bit Integer AND Operation
				//＊C[n]＝A[n]&B[n]
				general(_PL_ I32_)(inte_32 _PL_ C,INTE_32 _PL_ A,INTE_32 _PL_ B,ADDRESS N);
				//BitClip : 64-bit Integer AND Operation
				//＊C[n]＝A[n]&B[n]
				general(_PL_ I64_)(inte_64 _PL_ C,INTE_64 _PL_ A,INTE_64 _PL_ B,ADDRESS N);
			}
			A_2;

			//BitClip : OR Operation
			const struct
			{
				//BitClip : 8-bit Natural OR Operation
				//＊C[n]＝A[n]|M
				general(_PL_ D08_)(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 M,ADDRESS N);
				//BitClip : 16-bit Natural OR Operation
				//＊C[n]＝A[n]|M
				general(_PL_ D16_)(data_16 _PL_ C,DATA_16 _PL_ A,DATA_16 M,ADDRESS N);
				//BitClip : 32-bit Natural OR Operation
				//＊C[n]＝A[n]|M
				general(_PL_ D32_)(data_32 _PL_ C,DATA_32 _PL_ A,DATA_32 M,ADDRESS N);
				//BitClip : 64-bit Natural OR Operation
				//＊C[n]＝A[n]|M
				general(_PL_ D64_)(data_64 _PL_ C,DATA_64 _PL_ A,DATA_64 M,ADDRESS N);
				//BitClip : 8-bit Integer OR Operation
				//＊C[n]＝A[n]|M
				general(_PL_ I08_)(inte_08 _PL_ C,INTE_08 _PL_ A,INTE_08 M,ADDRESS N);
				//BitClip : 16-bit Integer OR Operation
				//＊C[n]＝A[n]|M
				general(_PL_ I16_)(inte_16 _PL_ C,INTE_16 _PL_ A,INTE_16 M,ADDRESS N);
				//BitClip : 32-bit Integer OR Operation
				//＊C[n]＝A[n]|M
				general(_PL_ I32_)(inte_32 _PL_ C,INTE_32 _PL_ A,INTE_32 M,ADDRESS N);
				//BitClip : 64-bit Integer OR Operation
				//＊C[n]＝A[n]|M
				general(_PL_ I64_)(inte_64 _PL_ C,INTE_64 _PL_ A,INTE_64 M,ADDRESS N);
			}
			O_1;

			//BitClip : OR Operation
			const struct
			{
				//BitClip : 8-bit Natural OR Operation
				//＊C[n]＝A[n]|B[n]
				general(_PL_ D08_)(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 _PL_ B,ADDRESS N);
				//BitClip : 16-bit Natural OR Operation
				//＊C[n]＝A[n]|B[n]
				general(_PL_ D16_)(data_16 _PL_ C,DATA_16 _PL_ A,DATA_16 _PL_ B,ADDRESS N);
				//BitClip : 32-bit Natural OR Operation
				//＊C[n]＝A[n]|B[n]
				general(_PL_ D32_)(data_32 _PL_ C,DATA_32 _PL_ A,DATA_32 _PL_ B,ADDRESS N);
				//BitClip : 64-bit Natural OR Operation
				//＊C[n]＝A[n]|B[n]
				general(_PL_ D64_)(data_64 _PL_ C,DATA_64 _PL_ A,DATA_64 _PL_ B,ADDRESS N);
				//BitClip : 8-bit Integer OR Operation
				//＊C[n]＝A[n]|B[n]
				general(_PL_ I08_)(inte_08 _PL_ C,INTE_08 _PL_ A,INTE_08 _PL_ B,ADDRESS N);
				//BitClip : 16-bit Integer OR Operation
				//＊C[n]＝A[n]|B[n]
				general(_PL_ I16_)(inte_16 _PL_ C,INTE_16 _PL_ A,INTE_16 _PL_ B,ADDRESS N);
				//BitClip : 32-bit Integer OR Operation
				//＊C[n]＝A[n]|B[n]
				general(_PL_ I32_)(inte_32 _PL_ C,INTE_32 _PL_ A,INTE_32 _PL_ B,ADDRESS N);
				//BitClip : 64-bit Integer OR Operation
				//＊C[n]＝A[n]|B[n]
				general(_PL_ I64_)(inte_64 _PL_ C,INTE_64 _PL_ A,INTE_64 _PL_ B,ADDRESS N);
			}
			O_2;

			//BitClip : XOR Operation
			const struct
			{
				//BitClip : 8-bit Natural XOR Operation
				//＊C[n]＝A[n]^M
				general(_PL_ D08_)(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 M,ADDRESS N);
				//BitClip : 16-bit Natural XOR Operation
				//＊C[n]＝A[n]^M
				general(_PL_ D16_)(data_16 _PL_ C,DATA_16 _PL_ A,DATA_16 M,ADDRESS N);
				//BitClip : 32-bit Natural XOR Operation
				//＊C[n]＝A[n]^M
				general(_PL_ D32_)(data_32 _PL_ C,DATA_32 _PL_ A,DATA_32 M,ADDRESS N);
				//BitClip : 64-bit Natural XOR Operation
				//＊C[n]＝A[n]^M
				general(_PL_ D64_)(data_64 _PL_ C,DATA_64 _PL_ A,DATA_64 M,ADDRESS N);
				//BitClip : 8-bit Integer XOR Operation
				//＊C[n]＝A[n]^M
				general(_PL_ I08_)(inte_08 _PL_ C,INTE_08 _PL_ A,INTE_08 M,ADDRESS N);
				//BitClip : 16-bit Integer XOR Operation
				//＊C[n]＝A[n]^M
				general(_PL_ I16_)(inte_16 _PL_ C,INTE_16 _PL_ A,INTE_16 M,ADDRESS N);
				//BitClip : 32-bit Integer XOR Operation
				//＊C[n]＝A[n]^M
				general(_PL_ I32_)(inte_32 _PL_ C,INTE_32 _PL_ A,INTE_32 M,ADDRESS N);
				//BitClip : 64-bit Integer XOR Operation
				//＊C[n]＝A[n]^M
				general(_PL_ I64_)(inte_64 _PL_ C,INTE_64 _PL_ A,INTE_64 M,ADDRESS N);
			}
			X_1;

			//BitClip : XOR Operation
			const struct
			{
				//BitClip : 8-bit Natural XOR Operation
				//＊C[n]＝A[n]^B[n]
				general(_PL_ D08_)(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 _PL_ B,ADDRESS N);
				//BitClip : 16-bit Natural XOR Operation
				//＊C[n]＝A[n]^B[n]
				general(_PL_ D16_)(data_16 _PL_ C,DATA_16 _PL_ A,DATA_16 _PL_ B,ADDRESS N);
				//BitClip : 32-bit Natural XOR Operation
				//＊C[n]＝A[n]^B[n]
				general(_PL_ D32_)(data_32 _PL_ C,DATA_32 _PL_ A,DATA_32 _PL_ B,ADDRESS N);
				//BitClip : 64-bit Natural XOR Operation
				//＊C[n]＝A[n]^B[n]
				general(_PL_ D64_)(data_64 _PL_ C,DATA_64 _PL_ A,DATA_64 _PL_ B,ADDRESS N);
				//BitClip : 8-bit Integer XOR Operation
				//＊C[n]＝A[n]^B[n]
				general(_PL_ I08_)(inte_08 _PL_ C,INTE_08 _PL_ A,INTE_08 _PL_ B,ADDRESS N);
				//BitClip : 16-bit Integer XOR Operation
				//＊C[n]＝A[n]^B[n]
				general(_PL_ I16_)(inte_16 _PL_ C,INTE_16 _PL_ A,INTE_16 _PL_ B,ADDRESS N);
				//BitClip : 32-bit Integer XOR Operation
				//＊C[n]＝A[n]^B[n]
				general(_PL_ I32_)(inte_32 _PL_ C,INTE_32 _PL_ A,INTE_32 _PL_ B,ADDRESS N);
				//BitClip : 64-bit Integer XOR Operation
				//＊C[n]＝A[n]^B[n]
				general(_PL_ I64_)(inte_64 _PL_ C,INTE_64 _PL_ A,INTE_64 _PL_ B,ADDRESS N);
			}
			X_2;
		}
		BO;

		//BitClip : Relational Operation Function Set
		const struct
		{
			//BitClip : Bit Expansion
			const struct
			{
				//BitClip : Bit Expansion to 8-bit Natural
				//＊O[n]＝(I[n/8].bit[n%8])?(0xFF):(0x00)
				general(_PL_ D08_)(DATA_08 *_R_ I,data_08 *_R_ O,ADDRESS N);
				//BitClip : Bit Expansion to 16-bit Natural
				//＊O[n]＝(I[n/8].bit[n%8])?(0xFFFF):(0x0000)
				general(_PL_ D16_)(DATA_08 *_R_ I,data_16 *_R_ O,ADDRESS N);
				//BitClip : Bit Expansion to 32-bit Natural
				//＊O[n]＝(I[n/8].bit[n%8])?(0xFFFFFFFF):(0x00000000)
				general(_PL_ D32_)(DATA_08 *_R_ I,data_32 *_R_ O,ADDRESS N);
				//BitClip : Bit Expansion to 64-bit Natural
				//＊O[n]＝(I[n/8].bit[n%8])?(0xFFFFFFFFFFFFFFFF):(0x0000000000000000)
				general(_PL_ D64_)(DATA_08 *_R_ I,data_64 *_R_ O,ADDRESS N);
				//BitClip : Bit Expansion to 8-bit Integer
				//＊O[n]＝(I[n/8].bit[n%8])?(0xFF):(0x00)
				general(_PL_ I08_)(DATA_08 *_R_ I,inte_08 *_R_ O,ADDRESS N);
				//BitClip : Bit Expansion to 16-bit Integer
				//＊O[n]＝(I[n/8].bit[n%8])?(0xFFFF):(0x0000)
				general(_PL_ I16_)(DATA_08 *_R_ I,inte_16 *_R_ O,ADDRESS N);
				//BitClip : Bit Expansion to 32-bit Integer
				//＊O[n]＝(I[n/8].bit[n%8])?(0xFFFFFFFF):(0x00000000)
				general(_PL_ I32_)(DATA_08 *_R_ I,inte_32 *_R_ O,ADDRESS N);
				//BitClip : Bit Expansion to 64-bit Integer
				//＊O[n]＝(I[n/8].bit[n%8])?(0xFFFFFFFFFFFFFFFF):(0x0000000000000000)
				general(_PL_ I64_)(DATA_08 *_R_ I,inte_64 *_R_ O,ADDRESS N);
			}
			Expand;

			//BitClip : Bit Shrink
			const struct
			{
				//BitClip : Bit Shrinkage from 8-bit Natural
				//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
				general(_PL_ D08_)(DATA_08 *_R_ I,data_08 *_R_ O,ADDRESS N);
				//BitClip : Bit Shrinkage from 16-bit Natural
				//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
				general(_PL_ D16_)(DATA_16 *_R_ I,data_08 *_R_ O,ADDRESS N);
				//BitClip : Bit Shrinkage from 32-bit Natural
				//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
				general(_PL_ D32_)(DATA_32 *_R_ I,data_08 *_R_ O,ADDRESS N);
				//BitClip : Bit Shrinkage from 64-bit Natural
				//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
				general(_PL_ D64_)(DATA_64 *_R_ I,data_08 *_R_ O,ADDRESS N);
				//BitClip : Bit Shrinkage from 8-bit Integer
				//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
				general(_PL_ I08_)(INTE_08 *_R_ I,data_08 *_R_ O,ADDRESS N);
				//BitClip : Bit Shrinkage from 16-bit Integer
				//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
				general(_PL_ I16_)(INTE_16 *_R_ I,data_08 *_R_ O,ADDRESS N);
				//BitClip : Bit Shrinkage from 32-bit Integer
				//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
				general(_PL_ I32_)(INTE_32 *_R_ I,data_08 *_R_ O,ADDRESS N);
				//BitClip : Bit Shrinkage from 64-bit Integer
				//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
				general(_PL_ I64_)(INTE_64 *_R_ I,data_08 *_R_ O,ADDRESS N);
			}
			Shrink;

			//BitClip : EQ Operation
			const struct
			{
				//BitClip : 8-bit Natural EQ Operation
				//＊C[n/8].bit[n%8]＝(A[n]==V)
				general(_PL_ D08_)(data_08 *_R_ C,DATA_08 *_R_ A,DATA_08 V,ADDRESS N);
				//BitClip : 16-bit Natural EQ Operation
				//＊C[n/8].bit[n%8]＝(A[n]==V)
				general(_PL_ D16_)(data_08 *_R_ C,DATA_16 *_R_ A,DATA_16 V,ADDRESS N);
				//BitClip : 32-bit Natural EQ Operation
				//＊C[n/8].bit[n%8]＝(A[n]==V)
				general(_PL_ D32_)(data_08 *_R_ C,DATA_32 *_R_ A,DATA_32 V,ADDRESS N);
				//BitClip : 64-bit Natural EQ Operation
				//＊C[n/8].bit[n%8]＝(A[n]==V)
				general(_PL_ D64_)(data_08 *_R_ C,DATA_64 *_R_ A,DATA_64 V,ADDRESS N);
				//BitClip : 8-bit Integer EQ Operation
				//＊C[n/8].bit[n%8]＝(A[n]==V)
				general(_PL_ I08_)(data_08 *_R_ C,INTE_08 *_R_ A,INTE_08 V,ADDRESS N);
				//BitClip : 16-bit Integer EQ Operation
				//＊C[n/8].bit[n%8]＝(A[n]==V)
				general(_PL_ I16_)(data_08 *_R_ C,INTE_16 *_R_ A,INTE_16 V,ADDRESS N);
				//BitClip : 32-bit Integer EQ Operation
				//＊C[n/8].bit[n%8]＝(A[n]==V)
				general(_PL_ I32_)(data_08 *_R_ C,INTE_32 *_R_ A,INTE_32 V,ADDRESS N);
				//BitClip : 64-bit Integer EQ Operation
				//＊C[n/8].bit[n%8]＝(A[n]==V)
				general(_PL_ I64_)(data_08 *_R_ C,INTE_64 *_R_ A,INTE_64 V,ADDRESS N);
				//BitClip : 32-bit Real EQ Operation
				//＊C[n/8].bit[n%8]＝(A[n]==V)
				general(_PL_ R32_)(data_08 *_R_ C,REAL_32 *_R_ A,REAL_32 V,ADDRESS N);
				//BitClip : 64-bit Real EQ Operation
				//＊C[n/8].bit[n%8]＝(A[n]==V)
				general(_PL_ R64_)(data_08 *_R_ C,REAL_64 *_R_ A,REAL_64 V,ADDRESS N);
			}
			E_1;

			//BitClip : EQ Operation
			const struct
			{
				//BitClip : 8-bit Natural EQ Operation
				//＊C[n/8].bit[n%8]＝(A[n]==B[n])
				general(_PL_ D08_)(data_08 *_R_ C,DATA_08 *_R_ A,DATA_08 *_R_ B,ADDRESS N);
				//BitClip : 16-bit Natural EQ Operation
				//＊C[n/8].bit[n%8]＝(A[n]==B[n])
				general(_PL_ D16_)(data_08 *_R_ C,DATA_16 *_R_ A,DATA_16 *_R_ B,ADDRESS N);
				//BitClip : 32-bit Natural EQ Operation
				//＊C[n/8].bit[n%8]＝(A[n]==B[n])
				general(_PL_ D32_)(data_08 *_R_ C,DATA_32 *_R_ A,DATA_32 *_R_ B,ADDRESS N);
				//BitClip : 64-bit Natural EQ Operation
				//＊C[n/8].bit[n%8]＝(A[n]==B[n])
				general(_PL_ D64_)(data_08 *_R_ C,DATA_64 *_R_ A,DATA_64 *_R_ B,ADDRESS N);
				//BitClip : 8-bit Integer EQ Operation
				//＊C[n/8].bit[n%8]＝(A[n]==B[n])
				general(_PL_ I08_)(data_08 *_R_ C,INTE_08 *_R_ A,INTE_08 *_R_ B,ADDRESS N);
				//BitClip : 16-bit Integer EQ Operation
				//＊C[n/8].bit[n%8]＝(A[n]==B[n])
				general(_PL_ I16_)(data_08 *_R_ C,INTE_16 *_R_ A,INTE_16 *_R_ B,ADDRESS N);
				//BitClip : 32-bit Integer EQ Operation
				//＊C[n/8].bit[n%8]＝(A[n]==B[n])
				general(_PL_ I32_)(data_08 *_R_ C,INTE_32 *_R_ A,INTE_32 *_R_ B,ADDRESS N);
				//BitClip : 64-bit Integer EQ Operation
				//＊C[n/8].bit[n%8]＝(A[n]==B[n])
				general(_PL_ I64_)(data_08 *_R_ C,INTE_64 *_R_ A,INTE_64 *_R_ B,ADDRESS N);
				//BitClip : 32-bit Real EQ Operation
				//＊C[n/8].bit[n%8]＝(A[n]==B[n])
				general(_PL_ R32_)(data_08 *_R_ C,REAL_32 *_R_ A,REAL_32 *_R_ B,ADDRESS N);
				//BitClip : 64-bit Real EQ Operation
				//＊C[n/8].bit[n%8]＝(A[n]==B[n])
				general(_PL_ R64_)(data_08 *_R_ C,REAL_64 *_R_ A,REAL_64 *_R_ B,ADDRESS N);
			}
			E_2;

			//BitClip : NE Operation
			const struct
			{
				//BitClip : 8-bit Natural NE Operation
				//＊C[n/8].bit[n%8]＝(A[n]!=V)
				general(_PL_ D08_)(data_08 *_R_ C,DATA_08 *_R_ A,DATA_08 V,ADDRESS N);
				//BitClip : 16-bit Natural NE Operation
				//＊C[n/8].bit[n%8]＝(A[n]!=V)
				general(_PL_ D16_)(data_08 *_R_ C,DATA_16 *_R_ A,DATA_16 V,ADDRESS N);
				//BitClip : 32-bit Natural NE Operation
				//＊C[n/8].bit[n%8]＝(A[n]!=V)
				general(_PL_ D32_)(data_08 *_R_ C,DATA_32 *_R_ A,DATA_32 V,ADDRESS N);
				//BitClip : 64-bit Natural NE Operation
				//＊C[n/8].bit[n%8]＝(A[n]!=V)
				general(_PL_ D64_)(data_08 *_R_ C,DATA_64 *_R_ A,DATA_64 V,ADDRESS N);
				//BitClip : 8-bit Integer NE Operation
				//＊C[n/8].bit[n%8]＝(A[n]!=V)
				general(_PL_ I08_)(data_08 *_R_ C,INTE_08 *_R_ A,INTE_08 V,ADDRESS N);
				//BitClip : 16-bit Integer NE Operation
				//＊C[n/8].bit[n%8]＝(A[n]!=V)
				general(_PL_ I16_)(data_08 *_R_ C,INTE_16 *_R_ A,INTE_16 V,ADDRESS N);
				//BitClip : 32-bit Integer NE Operation
				//＊C[n/8].bit[n%8]＝(A[n]!=V)
				general(_PL_ I32_)(data_08 *_R_ C,INTE_32 *_R_ A,INTE_32 V,ADDRESS N);
				//BitClip : 64-bit Integer NE Operation
				//＊C[n/8].bit[n%8]＝(A[n]!=V)
				general(_PL_ I64_)(data_08 *_R_ C,INTE_64 *_R_ A,INTE_64 V,ADDRESS N);
				//BitClip : 32-bit Real NE Operation
				//＊C[n/8].bit[n%8]＝(A[n]!=V)
				general(_PL_ R32_)(data_08 *_R_ C,REAL_32 *_R_ A,REAL_32 V,ADDRESS N);
				//BitClip : 64-bit Real NE Operation
				//＊C[n/8].bit[n%8]＝(A[n]!=V)
				general(_PL_ R64_)(data_08 *_R_ C,REAL_64 *_R_ A,REAL_64 V,ADDRESS N);
			}
			N_1;

			//BitClip : NE Operation
			const struct
			{
				//BitClip : 8-bit Natural NE Operation
				//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
				general(_PL_ D08_)(data_08 *_R_ C,DATA_08 *_R_ A,DATA_08 *_R_ B,ADDRESS N);
				//BitClip : 16-bit Natural NE Operation
				//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
				general(_PL_ D16_)(data_08 *_R_ C,DATA_16 *_R_ A,DATA_16 *_R_ B,ADDRESS N);
				//BitClip : 32-bit Natural NE Operation
				//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
				general(_PL_ D32_)(data_08 *_R_ C,DATA_32 *_R_ A,DATA_32 *_R_ B,ADDRESS N);
				//BitClip : 64-bit Natural NE Operation
				//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
				general(_PL_ D64_)(data_08 *_R_ C,DATA_64 *_R_ A,DATA_64 *_R_ B,ADDRESS N);
				//BitClip : 8-bit Integer NE Operation
				//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
				general(_PL_ I08_)(data_08 *_R_ C,INTE_08 *_R_ A,INTE_08 *_R_ B,ADDRESS N);
				//BitClip : 16-bit Integer NE Operation
				//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
				general(_PL_ I16_)(data_08 *_R_ C,INTE_16 *_R_ A,INTE_16 *_R_ B,ADDRESS N);
				//BitClip : 32-bit Integer NE Operation
				//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
				general(_PL_ I32_)(data_08 *_R_ C,INTE_32 *_R_ A,INTE_32 *_R_ B,ADDRESS N);
				//BitClip : 64-bit Integer NE Operation
				//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
				general(_PL_ I64_)(data_08 *_R_ C,INTE_64 *_R_ A,INTE_64 *_R_ B,ADDRESS N);
				//BitClip : 32-bit Real NE Operation
				//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
				general(_PL_ R32_)(data_08 *_R_ C,REAL_32 *_R_ A,REAL_32 *_R_ B,ADDRESS N);
				//BitClip : 64-bit Real NE Operation
				//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
				general(_PL_ R64_)(data_08 *_R_ C,REAL_64 *_R_ A,REAL_64 *_R_ B,ADDRESS N);
			}
			N_2;

			//BitClip : GE Operation
			const struct
			{
				//BitClip : 8-bit Natural GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥V)
				general(_PL_ D08_)(data_08 *_R_ C,DATA_08 *_R_ A,DATA_08 V,ADDRESS N);
				//BitClip : 16-bit Natural GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥V)
				general(_PL_ D16_)(data_08 *_R_ C,DATA_16 *_R_ A,DATA_16 V,ADDRESS N);
				//BitClip : 32-bit Natural GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥V)
				general(_PL_ D32_)(data_08 *_R_ C,DATA_32 *_R_ A,DATA_32 V,ADDRESS N);
				//BitClip : 64-bit Natural GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥V)
				general(_PL_ D64_)(data_08 *_R_ C,DATA_64 *_R_ A,DATA_64 V,ADDRESS N);
				//BitClip : 8-bit Integer GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥V)
				general(_PL_ I08_)(data_08 *_R_ C,INTE_08 *_R_ A,INTE_08 V,ADDRESS N);
				//BitClip : 16-bit Integer GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥V)
				general(_PL_ I16_)(data_08 *_R_ C,INTE_16 *_R_ A,INTE_16 V,ADDRESS N);
				//BitClip : 32-bit Integer GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥V)
				general(_PL_ I32_)(data_08 *_R_ C,INTE_32 *_R_ A,INTE_32 V,ADDRESS N);
				//BitClip : 64-bit Integer GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥V)
				general(_PL_ I64_)(data_08 *_R_ C,INTE_64 *_R_ A,INTE_64 V,ADDRESS N);
				//BitClip : 32-bit Real GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥V)
				general(_PL_ R32_)(data_08 *_R_ C,REAL_32 *_R_ A,REAL_32 V,ADDRESS N);
				//BitClip : 64-bit Real GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥V)
				general(_PL_ R64_)(data_08 *_R_ C,REAL_64 *_R_ A,REAL_64 V,ADDRESS N);
			}
			G_1;

			//BitClip : GE Operation
			const struct
			{
				//BitClip : 8-bit Natural GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
				general(_PL_ D08_)(data_08 *_R_ C,DATA_08 *_R_ A,DATA_08 *_R_ B,ADDRESS N);
				//BitClip : 16-bit Natural GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
				general(_PL_ D16_)(data_08 *_R_ C,DATA_16 *_R_ A,DATA_16 *_R_ B,ADDRESS N);
				//BitClip : 32-bit Natural GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
				general(_PL_ D32_)(data_08 *_R_ C,DATA_32 *_R_ A,DATA_32 *_R_ B,ADDRESS N);
				//BitClip : 64-bit Natural GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
				general(_PL_ D64_)(data_08 *_R_ C,DATA_64 *_R_ A,DATA_64 *_R_ B,ADDRESS N);
				//BitClip : 8-bit Integer GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
				general(_PL_ I08_)(data_08 *_R_ C,INTE_08 *_R_ A,INTE_08 *_R_ B,ADDRESS N);
				//BitClip : 16-bit Integer GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
				general(_PL_ I16_)(data_08 *_R_ C,INTE_16 *_R_ A,INTE_16 *_R_ B,ADDRESS N);
				//BitClip : 32-bit Integer GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
				general(_PL_ I32_)(data_08 *_R_ C,INTE_32 *_R_ A,INTE_32 *_R_ B,ADDRESS N);
				//BitClip : 64-bit Integer GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
				general(_PL_ I64_)(data_08 *_R_ C,INTE_64 *_R_ A,INTE_64 *_R_ B,ADDRESS N);
				//BitClip : 32-bit Real GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
				general(_PL_ R32_)(data_08 *_R_ C,REAL_32 *_R_ A,REAL_32 *_R_ B,ADDRESS N);
				//BitClip : 64-bit Real GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
				general(_PL_ R64_)(data_08 *_R_ C,REAL_64 *_R_ A,REAL_64 *_R_ B,ADDRESS N);
			}
			G_2;

			//BitClip : LT Operation
			const struct
			{
				//BitClip : 8-bit Natural LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜V)
				general(_PL_ D08_)(data_08 *_R_ C,DATA_08 *_R_ A,DATA_08 V,ADDRESS N);
				//BitClip : 16-bit Natural LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜V)
				general(_PL_ D16_)(data_08 *_R_ C,DATA_16 *_R_ A,DATA_16 V,ADDRESS N);
				//BitClip : 32-bit Natural LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜V)
				general(_PL_ D32_)(data_08 *_R_ C,DATA_32 *_R_ A,DATA_32 V,ADDRESS N);
				//BitClip : 64-bit Natural LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜V)
				general(_PL_ D64_)(data_08 *_R_ C,DATA_64 *_R_ A,DATA_64 V,ADDRESS N);
				//BitClip : 8-bit Integer LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜V)
				general(_PL_ I08_)(data_08 *_R_ C,INTE_08 *_R_ A,INTE_08 V,ADDRESS N);
				//BitClip : 16-bit Integer LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜V)
				general(_PL_ I16_)(data_08 *_R_ C,INTE_16 *_R_ A,INTE_16 V,ADDRESS N);
				//BitClip : 32-bit Integer LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜V)
				general(_PL_ I32_)(data_08 *_R_ C,INTE_32 *_R_ A,INTE_32 V,ADDRESS N);
				//BitClip : 64-bit Integer LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜V)
				general(_PL_ I64_)(data_08 *_R_ C,INTE_64 *_R_ A,INTE_64 V,ADDRESS N);
				//BitClip : 32-bit Real LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜V)
				general(_PL_ R32_)(data_08 *_R_ C,REAL_32 *_R_ A,REAL_32 V,ADDRESS N);
				//BitClip : 64-bit Real LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜V)
				general(_PL_ R64_)(data_08 *_R_ C,REAL_64 *_R_ A,REAL_64 V,ADDRESS N);
			}
			L_1;

			//BitClip : LT Operation
			const struct
			{
				//BitClip : 8-bit Natural LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
				general(_PL_ D08_)(data_08 *_R_ C,DATA_08 *_R_ A,DATA_08 *_R_ B,ADDRESS N);
				//BitClip : 16-bit Natural LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
				general(_PL_ D16_)(data_08 *_R_ C,DATA_16 *_R_ A,DATA_16 *_R_ B,ADDRESS N);
				//BitClip : 32-bit Natural LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
				general(_PL_ D32_)(data_08 *_R_ C,DATA_32 *_R_ A,DATA_32 *_R_ B,ADDRESS N);
				//BitClip : 64-bit Natural LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
				general(_PL_ D64_)(data_08 *_R_ C,DATA_64 *_R_ A,DATA_64 *_R_ B,ADDRESS N);
				//BitClip : 8-bit Integer LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
				general(_PL_ I08_)(data_08 *_R_ C,INTE_08 *_R_ A,INTE_08 *_R_ B,ADDRESS N);
				//BitClip : 16-bit Integer LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
				general(_PL_ I16_)(data_08 *_R_ C,INTE_16 *_R_ A,INTE_16 *_R_ B,ADDRESS N);
				//BitClip : 32-bit Integer LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
				general(_PL_ I32_)(data_08 *_R_ C,INTE_32 *_R_ A,INTE_32 *_R_ B,ADDRESS N);
				//BitClip : 64-bit Integer LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
				general(_PL_ I64_)(data_08 *_R_ C,INTE_64 *_R_ A,INTE_64 *_R_ B,ADDRESS N);
				//BitClip : 32-bit Real LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
				general(_PL_ R32_)(data_08 *_R_ C,REAL_32 *_R_ A,REAL_32 *_R_ B,ADDRESS N);
				//BitClip : 64-bit Real LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
				general(_PL_ R64_)(data_08 *_R_ C,REAL_64 *_R_ A,REAL_64 *_R_ B,ADDRESS N);
			}
			L_2;
		}
		RO;

		//BitClip : Bit Pointer Function Set
		const struct
		{
			//BitClip : Bit Pointer Assign
			bitc_bp(_PL_ Assign_)(general _PL_ BaseAddress,SINTPTR BitOffset);
			//BitClip : Bit Pointer Move
			//＊Return value is the moved pointer.
			bitc_bp(_PL_ Jumper_)(BITC_BP BitPointer,SINTPTR Move);
			//BitClip : Bit Pointer Read
			//＊Return value is 0 or ~0.
			logical(_PL_ Reader_)(BITC_BP BitPointer);
			//BitClip : Bit Pointer Write
			//＊Bool value should be 0 or ~0.
			general(_PL_ Writer_)(BITC_BP BitPointer,LOGICAL Boolean);
		}
		BP;
	};
};
MemC_Type_Declare_(struct,bitcase,BITCASE);	//BitClip : Library Case Structure

//BitClip : Library Case Object
extern BITCASE BitC;
//BitClip : Indirect access to the library case object.
extern BITCASE *BitC_(general);

#ifdef __OPENCL_H
//BitClip : OpenCL Extension Structure
struct _bitc_cl
{
	//BitClip : Program Build Functions
	const struct
	{
		//BitClip : Program Build into Binary Files with 8-bit String Path
		//＊The number of binary paths must be same as the number of devices associated with the context.
		//＊(BuildOption) Example : "-I ../../Headers -I ../../Sources -D _BitC_R16_=0 -D _BitC_R64_=1"
		//　(SourcePath) Example : "../../Kernels/bitclip.cl"
		//　(BinaryPath) Example : { "../../Device 1/bitclip.obj", "../../Device 2/bitclip.obj", ... }
		general(_PL_ T08_)(const cl_context Context,BYTE_08 _PL_ BuildOption,TEXT_08 _PL_ SourcePath,TEXT_08 _PL_ _PL_ BinaryPath,FILE _PL_ Stream,oclc_ef _PL_ Error);
		//BitClip : Program Build into Binary Files with 16-bit String Path
		//＊The number of binary paths must be same as the number of devices associated with the context.
		//＊(BuildOption) Example : "-I ../../Headers -I ../../Sources -D _BitC_R16_=0 -D _BitC_R64_=1"
		//　(SourcePath) Example : "../../Kernels/bitclip.cl"
		//　(BinaryPath) Example : { "../../Device 1/bitclip.obj", "../../Device 2/bitclip.obj", ... }
		general(_PL_ T16_)(const cl_context Context,BYTE_08 _PL_ BuildOption,TEXT_16 _PL_ SourcePath,TEXT_16 _PL_ _PL_ BinaryPath,FILE _PL_ Stream,oclc_ef _PL_ Error);
	}
	Ready;

	//BitClip : Program Creation Functions
	const struct
	{
		//BitClip : Program Manager Creation with 8-bit String Path - Delete with "OCLC.PM.Delete_"
		//＊The number of binary paths must be same as the number of devices associated with the context.
		//＊(BinaryPath) Example : { "../../Device 1/bitclip.obj", "../../Device 2/bitclip.obj", ... }
		oclc_pm*(_PL_ T08_)(const cl_context Context,BYTE_08 _PL_ BuildOption,TEXT_08 _PL_ _PL_ BinaryPath,FILE _PL_ LogStream,oclc_ef _PL_ Error);
		//BitClip : Program Manager Creation with 16-bit String Path - Delete with "OCLC.PM.Delete_"
		//＊The number of binary paths must be same as the number of devices associated with the context.
		//＊(BinaryPath) Example : { "../../Device 1/bitclip.obj", "../../Device 2/bitclip.obj", ... }
		oclc_pm*(_PL_ T16_)(const cl_context Context,BYTE_08 _PL_ BuildOption,TEXT_16 _PL_ _PL_ BinaryPath,FILE _PL_ LogStream,oclc_ef _PL_ Error);
	}
	Create;

	//BitClip : Pin Value Casting
	//＊Required (Buffer) size is 4×((DeviceAddressBits)÷8) bytes.
	//＊Return address is (Pin) for the same address bits between the host and the device, or (Buffer) otherwise.
	GENERAL*(_PL_ Pin_)(OCLC_MP _PL_ Pin,general _PL_ Buffer,ADDRESS DeviceAddressBits);

	const struct
	{
		//BitClip : Endian Flipping
		general(_PL_ Endian_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ Data,OCLC_MP _PL_ Amount,oclc_ef _PL_ Error);

		//BitClip : Array Reformation
		//＊SourceAmount->S[dim] == TargetAmount->S[ReformingAxis->S[dim]] where dim＝0, 1, 2, 3.
		//＊Source and Target's type sizes should be same.
		general(_PL_ Reform_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ Source,OCLC_MH _PL_ Target,OCLC_MP _PL_ SourceAmount,OCLC_MP _PL_ ReformingAxis,oclc_ef _PL_ Error);

		//BitClip : Type Casting Function
		general(_PL_ Caster_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutI,OCLC_MH _PL_ AboutO,OCLC_MP _PL_ AboutN,oclc_ef _PL_ Error);

		//BitClip : Bit Operation Function Set
		const struct
		{
			//BitClip : NOT Operation
			//＊C and A's type sizes should be same.
			general(_PL_ N_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,oclc_ef _PL_ Error);
			//BitClip : Shift Operation
			//＊C and A's types should be same.
			general(_PL_ S_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,INTEGER Shift,oclc_ef _PL_ Error);
			//BitClip : AND Operation
			//＊C and A's type sizes should be same.
			//＊Required (Mask) size is the type size of those to be calculated.
			general(_PL_ A_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Mask,oclc_ef _PL_ Error);
			//BitClip : AND Operation
			//＊C, A, and B's type sizes should be same.
			general(_PL_ A_2_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ Error);
			//BitClip : OR Operation
			//＊C and A's type sizes should be same.
			//＊Required (Mask) size is the type size of those to be calculated.
			general(_PL_ O_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Mask,oclc_ef _PL_ Error);
			//BitClip : OR Operation
			//＊C, A, and B's type sizes should be same.
			general(_PL_ O_2_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ Error);
			//BitClip : XOR Operation
			//＊C and A's type sizes should be same.
			//＊Required (Mask) size is the type size of those to be calculated.
			general(_PL_ X_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Mask,oclc_ef _PL_ Error);
			//BitClip : XOR Operation
			//＊C, A, and B's type sizes should be same.
			general(_PL_ X_2_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ Error);
		}
		BO;

		//BitClip : Relational Operation Function Set
		const struct
		{
			//BitClip : EQ Operation
			//＊C and A's type sizes should be same.
			//　C's type should be inte_xx.
			//＊Required (Value) size is the type size of those to be calculated.
			general(_PL_ E_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Value,oclc_ef _PL_ Error);
			//BitClip : EQ Operation
			//＊C, A, and B's type sizes should be same.
			//　C's type should be inte_xx.
			//　A and B's types should be same.
			general(_PL_ E_2_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ Error);
			//BitClip : NE Operation
			//＊C and A's type sizes should be same.
			//　C's type should be inte_xx.
			//＊Required (Value) size is the type size of those to be calculated.
			general(_PL_ N_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Value,oclc_ef _PL_ Error);
			//BitClip : NE Operation
			//＊C, A, and B's type sizes should be same.
			//　C's type should be inte_xx.
			//　A and B's types should be same.
			general(_PL_ N_2_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ Error);
			//BitClip : GE Operation
			//＊C and A's type sizes should be same.
			//　C's type should be inte_xx.
			//＊Required (Value) size is the type size of those to be calculated.
			general(_PL_ G_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Value,oclc_ef _PL_ Error);
			//BitClip : GE Operation
			//＊C, A, and B's type sizes should be same.
			//　C's type should be inte_xx.
			//　A and B's types should be same.
			general(_PL_ G_2_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ Error);
			//BitClip : LT Operation
			//＊C and A's type sizes should be same.
			//　C's type should be inte_xx.
			//＊Required (Value) size is the type size of those to be calculated.
			general(_PL_ L_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Value,oclc_ef _PL_ Error);
			//BitClip : LT Operation
			//＊C, A, and B's type sizes should be same.
			//　C's type should be inte_xx.
			//　A and B's types should be same.
			general(_PL_ L_2_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ Error);
		}
		RO;
	};
};
MemC_Type_Declare_(struct,bitc_cl,BITC_CL);	//BitClip : OpenCL Extension Structure

//BitClip : OpenCL Extension Object
extern BITC_CL BitCL;
//BitClip : Indirect access to the OpenCL extension object.
extern BITC_CL *BitCL_(general);
#endif
#endif
#endif
#endif
