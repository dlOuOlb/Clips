#ifndef oBITCLIP_INC_
#define oBITCLIP_INC_ "BitC:2020.01.31"
/*------------------------------------------------------------------+
|	BitClip provides some simple bit-operation functions.			|
|																	|
|	Written by Ranny Clover											|
|	http://github.com/dlOuOlb/Clips/blob/master/Headers/bitclip.h	|
+-------------------------------------------------------------------+
|	Dependency:														|
|																	|
|	MSVClip -- MemClip -- PenClip -- OCLClip -- BitClip				|
+-------------------------------------------------------------------+
|	Non-Prefixed Types (Host):										|
|																	|
|	uintptr	sintptr													|
|	UINTPTR	SINTPTR													|
|																	|
|	data_08	data_16	data_32	data_64									|
|	DATA_08	DATA_16	DATA_32	DATA_64									|
|																	|
|	inte_08	inte_16	inte_32	inte_64									|
|	INTE_08	INTE_16	INTE_32	INTE_64									|
|																	|
|					real_32	real_64									|
|					REAL_32	REAL_64									|
+-------------------------------------------------------------------+
|	Non-Prefixed Macros (Device):									|
|																	|
|	Vect_															|
|	Vect_Load_		Vect_Save_										|
+-------------------------------------------------------------------+
|	Non-Prefixed Types (Device):									|
|																	|
|	uintptr		sintptr												|
|	UINTPTR		SINTPTR												|
|																	|
|	data_08		data_16		data_32		data_64						|
|	_@@_data_08	_@@_data_16	_@@_data_32	_@@_data_64					|
|	DATA_08		DATA_16		DATA_32		DATA_64						|
|	_@@_DATA_08	_@@_DATA_16	_@@_DATA_32	_@@_DATA_64					|
|																	|
|	inte_08		inte_16		inte_32		inte_64						|
|	_@@_inte_08	_@@_inte_16	_@@_inte_32	_@@_inte_64					|
|	INTE_08		INTE_16		INTE_32		INTE_64						|
|	_@@_INTE_08	_@@_INTE_16	_@@_INTE_32	_@@_INTE_64					|
|																	|
|				real_16		real_32		real_64						|
|				_@@_real_16	_@@_real_32	_@@_real_64					|
|				REAL_16		REAL_32		REAL_64						|
|				_@@_REAL_16	_@@_REAL_32	_@@_REAL_64					|
|																	|
|	@@ = 02, 03, 04, 08, 16.										|
+-------------------------------------------------------------------+
|	Note:															|
|																	|
|	Run "BitC.Okay.Wrap_();" to check whether the casted function	|
|	pointers work normally from data_## types into inte_## types.	|
+------------------------------------------------------------------*/

#include <oclclip.h>

#ifdef __OPENCL_VERSION__

#if(Fold_(Extension Macros))
#ifdef xBitC_Empty_
#error The macro "xBitC_Empty_" is already defined.
#else
#define xBitC_Empty_(X) ((~(~X+0)==0)&&(~(~X+1)==1))
#endif

#ifdef uBitC_R16_
#if(xBitC_Empty_(uBitC_R16_))
#undef uBitC_R16_
#define uBitC_R16_ (1)
#endif
#else
#define uBitC_R16_ (0)
#endif

#ifdef uBitC_R64_
#if(xBitC_Empty_(uBitC_R64_))
#undef uBitC_R64_
#define uBitC_R64_ (1)
#endif
#else
#define uBitC_R64_ (0)
#endif

#if(uBitC_R16_)
#pragma OPENCL EXTENSION cl_khr_fp16 : enable
#else
#pragma OPENCL EXTENSION cl_khr_fp16 : disable
#endif

#if(uBitC_R64_)
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#else
#pragma OPENCL EXTENSION cl_khr_fp64 : disable
#endif

#undef xBitC_Empty_
#endif

#if(Fold_(Vector Macros))
#define Vect_(scope,num,type) _##scope##_ _##num##_##type

#define Vect_Load_(num,Address) xBitC_Vect_Load_##num##_(Address)
#define xBitC_Vect_Load_02_(Address) vload2(0,Address)
#define xBitC_Vect_Load_03_(Address) vload3(0,Address)
#define xBitC_Vect_Load_04_(Address) vload4(0,Address)
#define xBitC_Vect_Load_08_(Address) vload8(0,Address)
#define xBitC_Vect_Load_16_(Address) vload16(0,Address)

#define Vect_Save_(num,Address,Vector) xBitC_Vect_Save_##num##_(Vector,Address)
#define xBitC_Vect_Save_02_(Vector,Address) vstore2(Vector,0,Address)
#define xBitC_Vect_Save_03_(Vector,Address) vstore3(Vector,0,Address)
#define xBitC_Vect_Save_04_(Vector,Address) vstore4(Vector,0,Address)
#define xBitC_Vect_Save_08_(Vector,Address) vstore8(Vector,0,Address)
#define xBitC_Vect_Save_16_(Vector,Address) vstore16(Vector,0,Address)
#endif

#if(Fold_(Scalar and Vector Types))
#define xBitC_Parse_(oldtype,newtype,NEWTYPE) OCLC_Type_Rename_(oldtype,newtype,NEWTYPE);OCLC_Type_Rename_(oldtype##2,_02_##newtype,_02_##NEWTYPE);OCLC_Type_Rename_(oldtype##3,_03_##newtype,_03_##NEWTYPE);OCLC_Type_Rename_(oldtype##4,_04_##newtype,_04_##NEWTYPE);OCLC_Type_Rename_(oldtype##8,_08_##newtype,_08_##NEWTYPE);OCLC_Type_Rename_(oldtype##16,_16_##newtype,_16_##NEWTYPE)

OCLC_Type_Rename_(intptr_t,sintptr,SINTPTR);
OCLC_Type_Rename_(uintptr_t,uintptr,UINTPTR);

xBitC_Parse_(uchar,data_08,DATA_08);
xBitC_Parse_(ushort,data_16,DATA_16);
xBitC_Parse_(uint,data_32,DATA_32);
xBitC_Parse_(ulong,data_64,DATA_64);

xBitC_Parse_(char,inte_08,INTE_08);
xBitC_Parse_(short,inte_16,INTE_16);
xBitC_Parse_(int,inte_32,INTE_32);
xBitC_Parse_(long,inte_64,INTE_64);

#if(uBitC_R16_)
xBitC_Parse_(half,real_16,REAL_16);
#else
xBitC_Parse_(short,real_16,REAL_16);
#endif
xBitC_Parse_(float,real_32,REAL_32);
#if(uBitC_R64_)
xBitC_Parse_(double,real_64,REAL_64);
#else
xBitC_Parse_(long,real_64,REAL_64);
#endif

#undef xBitC_Parse_
#endif

#if(Fold_(Pointer Unions))
#define xBitC_Parse_(scope,acs) union{xBitC_Parse_Scalar_##acs##_(scope);xBitC_Parse_Vector_##acs##_(scope,02);xBitC_Parse_Vector_##acs##_(scope,03);xBitC_Parse_Vector_##acs##_(scope,04);xBitC_Parse_Vector_##acs##_(scope,08);xBitC_Parse_Vector_##acs##_(scope,16);}acs
#define xBitC_Parse_Scalar_V_(scope) _##scope##_ general *G;_##scope##_ general **GG;_##scope##_ address *AA;_##scope##_ data_08 *D08;_##scope##_ data_16 *D16;_##scope##_ data_32 *D32;_##scope##_ data_64 *D64;_##scope##_ inte_08 *I08;_##scope##_ inte_16 *I16;_##scope##_ inte_32 *I32;_##scope##_ inte_64 *I64;_##scope##_ real_16 *R16;_##scope##_ real_32 *R32;_##scope##_ real_64 *R64
#define xBitC_Parse_Scalar_C_(scope) _##scope##_ GENERAL *G;_##scope##_ GENERAL **GG;_##scope##_ ADDRESS *AA;_##scope##_ DATA_08 *D08;_##scope##_ DATA_16 *D16;_##scope##_ DATA_32 *D32;_##scope##_ DATA_64 *D64;_##scope##_ INTE_08 *I08;_##scope##_ INTE_16 *I16;_##scope##_ INTE_32 *I32;_##scope##_ INTE_64 *I64;_##scope##_ REAL_16 *R16;_##scope##_ REAL_32 *R32;_##scope##_ REAL_64 *R64
#define xBitC_Parse_Vector_V_(scope,num) union{_##scope##_ _##num##_data_08 *D08;_##scope##_ _##num##_data_16 *D16;_##scope##_ _##num##_data_32 *D32;_##scope##_ _##num##_data_64 *D64;_##scope##_ _##num##_inte_08 *I08;_##scope##_ _##num##_inte_16 *I16;_##scope##_ _##num##_inte_32 *I32;_##scope##_ _##num##_inte_64 *I64;_##scope##_ _##num##_real_16 *R16;_##scope##_ _##num##_real_32 *R32;_##scope##_ _##num##_real_64 *R64;}_##num
#define xBitC_Parse_Vector_C_(scope,num) union{_##scope##_ _##num##_DATA_08 *D08;_##scope##_ _##num##_DATA_16 *D16;_##scope##_ _##num##_DATA_32 *D32;_##scope##_ _##num##_DATA_64 *D64;_##scope##_ _##num##_INTE_08 *I08;_##scope##_ _##num##_INTE_16 *I16;_##scope##_ _##num##_INTE_32 *I32;_##scope##_ _##num##_INTE_64 *I64;_##scope##_ _##num##_REAL_16 *R16;_##scope##_ _##num##_REAL_32 *R32;_##scope##_ _##num##_REAL_64 *R64;}_##num

union _bitc_cp { xBitC_Parse_(C,V);xBitC_Parse_(C,C); };
OCLC_Type_Declare_(union,bitc_cp,BITC_CP);

union _bitc_gp { xBitC_Parse_(G,V);xBitC_Parse_(G,C); };
OCLC_Type_Declare_(union,bitc_gp,BITC_GP);

union _bitc_lp { xBitC_Parse_(L,V);xBitC_Parse_(L,C); };
OCLC_Type_Declare_(union,bitc_lp,BITC_LP);

union _bitc_pp { xBitC_Parse_(P,V);xBitC_Parse_(P,C); };
OCLC_Type_Declare_(union,bitc_pp,BITC_PP);

#undef xBitC_Parse_Vector_C_
#undef xBitC_Parse_Vector_V_
#undef xBitC_Parse_Scalar_C_
#undef xBitC_Parse_Scalar_V_
#undef xBitC_Parse_
#endif

#else

#include <inttypes.h>

#if(Fold_(Primal Types))
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
#endif

#if(Fold_(Plain Types))
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

#if(Fold_(Check Macros))
#define BitC_Inte_Over_(X)\
__dl{\
	switch(sizeof(X))\
	{\
		case 1:assert((INT8_C(-0x40)<Acs_(inte_08,X))&&(Acs_(inte_08,X)<INT8_C(+0x40)));break;\
		case 2:assert((INT16_C(-0x4000)<Acs_(inte_16,X))&&(Acs_(inte_16,X)<INT16_C(+0x4000)));break;\
		case 4:assert((INT32_C(-0x40000000)<Acs_(inte_32,X))&&(Acs_(inte_32,X)<INT32_C(+0x40000000)));break;\
		case 8:assert((INT64_C(-0x4000000000000000)<Acs_(inte_64,X))&&(Acs_(inte_64,X)<INT64_C(+0x4000000000000000)));break;\
		default:assert((X)&(0));\
	}\
}lb__
#endif

#if(Fold_(Bit Operation Macros))
#if(Fold_(BitC_Max_T##_))
//BitClip : Maximum of 8-bit Integer - This could be invalid for data range over 0x40.
#define BitC_Max_I08_(Output,InputA,InputB)\
__dl{\
	static_assert((sizeof(inte_08)&sizeof(Output)&sizeof(InputA)&sizeof(InputB))==(sizeof(inte_08)|sizeof(Output)|sizeof(InputA)|sizeof(InputB)),"Not 8-bit!");\
	Acs_(inte_08,Output)=Acs_(inte_08,InputB)-Acs_(inte_08,InputA);\
	Acs_(inte_08,Output)&=(Acs_(inte_08,Output)>>7);\
	Acs_(inte_08,Output)=Acs_(inte_08,InputB)-Acs_(inte_08,Output);\
}lb__
//BitClip : Maximum of 16-bit Integer - This could be invalid for data range over 0x4000.
#define BitC_Max_I16_(Output,InputA,InputB)\
__dl{\
	static_assert((sizeof(inte_16)&sizeof(Output)&sizeof(InputA)&sizeof(InputB))==(sizeof(inte_16)|sizeof(Output)|sizeof(InputA)|sizeof(InputB)),"Not 16-bit!");\
	Acs_(inte_16,Output)=Acs_(inte_16,InputB)-Acs_(inte_16,InputA);\
	Acs_(inte_16,Output)&=(Acs_(inte_16,Output)>>15);\
	Acs_(inte_16,Output)=Acs_(inte_16,InputB)-Acs_(inte_16,Output);\
}lb__
//BitClip : Maximum of 32-bit Integer - This could be invalid for data range over 0x40000000.
#define BitC_Max_I32_(Output,InputA,InputB)\
__dl{\
	static_assert((sizeof(inte_32)&sizeof(Output)&sizeof(InputA)&sizeof(InputB))==(sizeof(inte_32)|sizeof(Output)|sizeof(InputA)|sizeof(InputB)),"Not 32-bit!");\
	Acs_(inte_32,Output)=Acs_(inte_32,InputB)-Acs_(inte_32,InputA);\
	Acs_(inte_32,Output)&=(Acs_(inte_32,Output)>>31);\
	Acs_(inte_32,Output)=Acs_(inte_32,InputB)-Acs_(inte_32,Output);\
}lb__
//BitClip : Maximum of 64-bit Integer - This could be invalid for data range over 0x4000000000000000.
#define BitC_Max_I64_(Output,InputA,InputB)\
__dl{\
	static_assert((sizeof(inte_64)&sizeof(Output)&sizeof(InputA)&sizeof(InputB))==(sizeof(inte_64)|sizeof(Output)|sizeof(InputA)|sizeof(InputB)),"Not 64-bit!");\
	Acs_(inte_64,Output)=Acs_(inte_64,InputB)-Acs_(inte_64,InputA);\
	Acs_(inte_64,Output)&=(Acs_(inte_64,Output)>>63);\
	Acs_(inte_64,Output)=Acs_(inte_64,InputB)-Acs_(inte_64,Output);\
}lb__
//BitClip : Maximum of 32-bit Real - This could be imprecise.
#define BitC_Max_R32_(Output,InputA,InputB)\
__dl{\
	static_assert((sizeof(real_32)&sizeof(Output)&sizeof(InputA)&sizeof(InputB))==(sizeof(real_32)|sizeof(Output)|sizeof(InputA)|sizeof(InputB)),"Not 32-bit!");\
	Acs_(real_32,Output)=Acs_(real_32,InputB)-Acs_(real_32,InputA);\
	Acs_(inte_32,Output)&=(Acs_(inte_32,Output)>>31);\
	Acs_(real_32,Output)=Acs_(real_32,InputB)-Acs_(real_32,Output);\
}lb__
//BitClip : Maximum of 64-bit Real - This could be imprecise.
#define BitC_Max_R64_(Output,InputA,InputB)\
__dl{\
	static_assert((sizeof(real_64)&sizeof(Output)&sizeof(InputA)&sizeof(InputB))==(sizeof(real_64)|sizeof(Output)|sizeof(InputA)|sizeof(InputB)),"Not 64-bit!");\
	Acs_(real_64,Output)=Acs_(real_64,InputB)-Acs_(real_64,InputA);\
	Acs_(inte_64,Output)&=(Acs_(inte_64,Output)>>63);\
	Acs_(real_64,Output)=Acs_(real_64,InputB)-Acs_(real_64,Output);\
}lb__
#endif

#if(Fold_(BitC_Min_T##_))
//BitClip : Minimum of 8-bit Integer - This could be invalid for data range over 0x40.
#define BitC_Min_I08_(Output,InputA,InputB)\
__dl{\
	static_assert((sizeof(inte_08)&sizeof(Output)&sizeof(InputA)&sizeof(InputB))==(sizeof(inte_08)|sizeof(Output)|sizeof(InputA)|sizeof(InputB)),"Not 8-bit!");\
	Acs_(inte_08,Output)=Acs_(inte_08,InputA)-Acs_(inte_08,InputB);\
	Acs_(inte_08,Output)&=(Acs_(inte_08,Output)>>7);\
	Acs_(inte_08,Output)+=Acs_(inte_08,InputB);\
}lb__
//BitClip : Minimum of 16-bit Integer - This could be invalid for data range over 0x4000.
#define BitC_Min_I16_(Output,InputA,InputB)\
__dl{\
	static_assert((sizeof(inte_16)&sizeof(Output)&sizeof(InputA)&sizeof(InputB))==(sizeof(inte_16)|sizeof(Output)|sizeof(InputA)|sizeof(InputB)),"Not 16-bit!");\
	Acs_(inte_16,Output)=Acs_(inte_16,InputA)-Acs_(inte_16,InputB);\
	Acs_(inte_16,Output)&=(Acs_(inte_16,Output)>>15);\
	Acs_(inte_16,Output)+=Acs_(inte_16,InputB);\
}lb__
//BitClip : Minimum of 32-bit Integer - This could be invalid for data range over 0x40000000.
#define BitC_Min_I32_(Output,InputA,InputB)\
__dl{\
	static_assert((sizeof(inte_32)&sizeof(Output)&sizeof(InputA)&sizeof(InputB))==(sizeof(inte_32)|sizeof(Output)|sizeof(InputA)|sizeof(InputB)),"Not 32-bit!");\
	Acs_(inte_32,Output)=Acs_(inte_32,InputA)-Acs_(inte_32,InputB);\
	Acs_(inte_32,Output)&=(Acs_(inte_32,Output)>>31);\
	Acs_(inte_32,Output)+=Acs_(inte_32,InputB);\
}lb__
//BitClip : Minimum of 64-bit Integer - This could be invalid for data range over 0x4000000000000000.
#define BitC_Min_I64_(Output,InputA,InputB)\
__dl{\
	static_assert((sizeof(inte_64)&sizeof(Output)&sizeof(InputA)&sizeof(InputB))==(sizeof(inte_64)|sizeof(Output)|sizeof(InputA)|sizeof(InputB)),"Not 64-bit!");\
	Acs_(inte_64,Output)=Acs_(inte_64,InputA)-Acs_(inte_64,InputB);\
	Acs_(inte_64,Output)&=(Acs_(inte_64,Output)>>63);\
	Acs_(inte_64,Output)+=Acs_(inte_64,InputB);\
}lb__
//BitClip : Minimum of 32-bit Real - This could be imprecise.
#define BitC_Min_R32_(Output,InputA,InputB)\
__dl{\
	static_assert((sizeof(real_32)&sizeof(Output)&sizeof(InputA)&sizeof(InputB))==(sizeof(real_32)|sizeof(Output)|sizeof(InputA)|sizeof(InputB)),"Not 32-bit!");\
	Acs_(real_32,Output)=Acs_(real_32,InputA)-Acs_(real_32,InputB);\
	Acs_(inte_32,Output)&=(Acs_(inte_32,Output)>>31);\
	Acs_(real_32,Output)+=Acs_(real_32,InputB);\
}lb__
//BitClip : Minimum of 64-bit Real - This could be imprecise.
#define BitC_Min_R64_(Output,InputA,InputB)\
__dl{\
	static_assert((sizeof(real_64)&sizeof(Output)&sizeof(InputA)&sizeof(InputB))==(sizeof(real_64)|sizeof(Output)|sizeof(InputA)|sizeof(InputB)),"Not 64-bit!");\
	Acs_(real_64,Output)=Acs_(real_64,InputA)-Acs_(real_64,InputB);\
	Acs_(inte_64,Output)&=(Acs_(inte_64,Output)>>63);\
	Acs_(real_64,Output)+=Acs_(real_64,InputB);\
}lb__
#endif

#if(Fold_(BitC_Abs_P_T##_))
//BitClip : Positive Absolute of 8-bit Integer
#define BitC_Abs_P_I08_(Output,Input)\
__dl{\
	static_assert((sizeof(inte_08)&sizeof(Output)&sizeof(Input))==(sizeof(inte_08)|sizeof(Output)|sizeof(Input)),"Not 8-bit!");\
	Acs_(inte_08,Output)=Acs_(inte_08,Input)>>7;\
	Acs_(inte_08,Output)^=Acs_(inte_08,Input)+Acs_(inte_08,Output);\
}lb__
//BitClip : Positive Absolute of 16-bit Integer
#define BitC_Abs_P_I16_(Output,Input)\
__dl{\
	static_assert((sizeof(inte_16)&sizeof(Output)&sizeof(Input))==(sizeof(inte_16)|sizeof(Output)|sizeof(Input)),"Not 16-bit!");\
	Acs_(inte_16,Output)=Acs_(inte_16,Input)>>15;\
	Acs_(inte_16,Output)^=Acs_(inte_16,Input)+Acs_(inte_16,Output);\
}lb__
//BitClip : Positive Absolute of 32-bit Integer
#define BitC_Abs_P_I32_(Output,Input)\
__dl{\
	static_assert((sizeof(inte_32)&sizeof(Output)&sizeof(Input))==(sizeof(inte_32)|sizeof(Output)|sizeof(Input)),"Not 32-bit!");\
	Acs_(inte_32,Output)=Acs_(inte_32,Input)>>31;\
	Acs_(inte_32,Output)^=Acs_(inte_32,Input)+Acs_(inte_32,Output);\
}lb__
//BitClip : Positive Absolute of 64-bit Integer
#define BitC_Abs_P_I64_(Output,Input)\
__dl{\
	static_assert((sizeof(inte_64)&sizeof(Output)&sizeof(Input))==(sizeof(inte_64)|sizeof(Output)|sizeof(Input)),"Not 64-bit!");\
	Acs_(inte_64,Output)=Acs_(inte_64,Input)>>63;\
	Acs_(inte_64,Output)^=Acs_(inte_64,Input)+Acs_(inte_64,Output);\
}lb__
//BitClip : Positive Absolute of 32-bit Real
#define BitC_Abs_P_R32_(Output,Input)\
__dl{\
	static_assert((sizeof(real_32)&sizeof(Output)&sizeof(Input))==(sizeof(real_32)|sizeof(Output)|sizeof(Input)),"Not 32-bit!");\
	Acs_(inte_32,Output)=Acs_(inte_32,Input)&INT32_C(0x7FFFFFFF);\
}lb__
//BitClip : Positive Absolute of 64-bit Real
#define BitC_Abs_P_R64_(Output,Input)\
__dl{\
	static_assert((sizeof(real_64)&sizeof(Output)&sizeof(Input))==(sizeof(real_64)|sizeof(Output)|sizeof(Input)),"Not 64-bit!");\
	Acs_(inte_64,Output)=Acs_(inte_64,Input)&INT64_C(0x7FFFFFFFFFFFFFFF);\
}lb__
#endif

#if(Fold_(BitC_Abs_N_T##_))
//BitClip : Negative Absolute of 8-bit Integer
#define BitC_Abs_N_I08_(Output,Input)\
__dl{\
	static_assert((sizeof(inte_08)&sizeof(Output)&sizeof(Input))==(sizeof(inte_08)|sizeof(Output)|sizeof(Input)),"Not 8-bit!");\
	Acs_(inte_08,Output)=Acs_(inte_08,Input)>>7;\
	Acs_(inte_08,Output)=~Acs_(inte_08,Output);\
	Acs_(inte_08,Output)^=Acs_(inte_08,Input)+Acs_(inte_08,Output);\
}lb__
//BitClip : Negative Absolute of 16-bit Integer
#define BitC_Abs_N_I16_(Output,Input)\
__dl{\
	static_assert((sizeof(inte_16)&sizeof(Output)&sizeof(Input))==(sizeof(inte_16)|sizeof(Output)|sizeof(Input)),"Not 16-bit!");\
	Acs_(inte_16,Output)=Acs_(inte_16,Input)>>15;\
	Acs_(inte_16,Output)=~Acs_(inte_16,Output);\
	Acs_(inte_16,Output)^=Acs_(inte_16,Input)+Acs_(inte_16,Output);\
}lb__
//BitClip : Negative Absolute of 32-bit Integer
#define BitC_Abs_N_I32_(Output,Input)\
__dl{\
	static_assert((sizeof(inte_32)&sizeof(Output)&sizeof(Input))==(sizeof(inte_32)|sizeof(Output)|sizeof(Input)),"Not 32-bit!");\
	Acs_(inte_32,Output)=Acs_(inte_32,Input)>>31;\
	Acs_(inte_32,Output)=~Acs_(inte_32,Output);\
	Acs_(inte_32,Output)^=Acs_(inte_32,Input)+Acs_(inte_32,Output);\
}lb__
//BitClip : Negative Absolute of 64-bit Integer
#define BitC_Abs_N_I64_(Output,Input)\
__dl{\
	static_assert((sizeof(inte_64)&sizeof(Output)&sizeof(Input))==(sizeof(inte_64)|sizeof(Output)|sizeof(Input)),"Not 64-bit!");\
	Acs_(inte_64,Output)=Acs_(inte_64,Input)>>63;\
	Acs_(inte_64,Output)=~Acs_(inte_64,Output);\
	Acs_(inte_64,Output)^=Acs_(inte_64,Input)+Acs_(inte_64,Output);\
}lb__
//BitClip : Negative Absolute of 32-bit Real
#define BitC_Abs_N_R32_(Output,Input)\
__dl{\
	static_assert((sizeof(real_32)&sizeof(Output)&sizeof(Input))==(sizeof(real_32)|sizeof(Output)|sizeof(Input)),"Not 32-bit!");\
	Acs_(inte_32,Output)=Acs_(inte_32,Input)|INT32_C(0x80000000);\
}lb__
//BitClip : Negative Absolute of 64-bit Real
#define BitC_Abs_N_R64_(Output,Input)\
__dl{\
	static_assert((sizeof(real_64)&sizeof(Output)&sizeof(Input))==(sizeof(real_64)|sizeof(Output)|sizeof(Input)),"Not 64-bit!");\
	Acs_(inte_64,Output)=Acs_(inte_64,Input)|INT64_C(0x8000000000000000);\
}lb__
#endif

#if(Fold_(BitC_Lim_P_T##_))
//BitClip : Positive Clipping of 8-bit Integer
#define BitC_Lim_P_I08_(Output,Input)\
__dl{\
	static_assert((sizeof(inte_08)&sizeof(Output)&sizeof(Input))==(sizeof(inte_08)|sizeof(Output)|sizeof(Input)),"Not 8-bit!");\
	Acs_(inte_08,Output)=Acs_(inte_08,Input)>>7;\
	Acs_(inte_08,Output)=~Acs_(inte_08,Output);\
	Acs_(inte_08,Output)&=Acs_(inte_08,Input);\
}lb__
//BitClip : Positive Clipping of 16-bit Integer
#define BitC_Lim_P_I16_(Output,Input)\
__dl{\
	static_assert((sizeof(inte_16)&sizeof(Output)&sizeof(Input))==(sizeof(inte_16)|sizeof(Output)|sizeof(Input)),"Not 16-bit!");\
	Acs_(inte_16,Output)=Acs_(inte_16,Input)>>15;\
	Acs_(inte_16,Output)=~Acs_(inte_16,Output);\
	Acs_(inte_16,Output)&=Acs_(inte_16,Input);\
}lb__
//BitClip : Positive Clipping of 32-bit Integer
#define BitC_Lim_P_I32_(Output,Input)\
__dl{\
	static_assert((sizeof(inte_32)&sizeof(Output)&sizeof(Input))==(sizeof(inte_32)|sizeof(Output)|sizeof(Input)),"Not 32-bit!");\
	Acs_(inte_32,Output)=Acs_(inte_32,Input)>>31;\
	Acs_(inte_32,Output)=~Acs_(inte_32,Output);\
	Acs_(inte_32,Output)&=Acs_(inte_32,Input);\
}lb__
//BitClip : Positive Clipping of 64-bit Integer
#define BitC_Lim_P_I64_(Output,Input)\
__dl{\
	static_assert((sizeof(inte_64)&sizeof(Output)&sizeof(Input))==(sizeof(inte_64)|sizeof(Output)|sizeof(Input)),"Not 64-bit!");\
	Acs_(inte_64,Output)=Acs_(inte_64,Input)>>63;\
	Acs_(inte_64,Output)=~Acs_(inte_64,Output);\
	Acs_(inte_64,Output)&=Acs_(inte_64,Input);\
}lb__
//BitClip : Positive Clipping of 32-bit Real
#define BitC_Lim_P_R32_(Output,Input)\
__dl{\
	static_assert((sizeof(real_32)&sizeof(Output)&sizeof(Input))==(sizeof(real_32)|sizeof(Output)|sizeof(Input)),"Not 32-bit!");\
	Acs_(inte_32,Output)=Acs_(inte_32,Input)>>31;\
	Acs_(inte_32,Output)=~Acs_(inte_32,Output);\
	Acs_(inte_32,Output)&=Acs_(inte_32,Input);\
}lb__
//BitClip : Positive Clipping of 64-bit Real
#define BitC_Lim_P_R64_(Output,Input)\
__dl{\
	static_assert((sizeof(real_64)&sizeof(Output)&sizeof(Input))==(sizeof(real_64)|sizeof(Output)|sizeof(Input)),"Not 64-bit!");\
	Acs_(inte_64,Output)=Acs_(inte_64,Input)>>63;\
	Acs_(inte_64,Output)=~Acs_(inte_64,Output);\
	Acs_(inte_64,Output)&=Acs_(inte_64,Input);\
}lb__
#endif

#if(Fold_(BitC_Lim_N_T##_))
//BitClip : Negative Clipping of 8-bit Integer
#define BitC_Lim_N_I08_(Output,Input)\
__dl{\
	static_assert((sizeof(inte_08)&sizeof(Output)&sizeof(Input))==(sizeof(inte_08)|sizeof(Output)|sizeof(Input)),"Not 8-bit!");\
	Acs_(inte_08,Output)=Acs_(inte_08,Input)>>7;\
	Acs_(inte_08,Output)&=Acs_(inte_08,Input);\
}lb__
//BitClip : Negative Clipping of 16-bit Integer
#define BitC_Lim_N_I16_(Output,Input)\
__dl{\
	static_assert((sizeof(inte_16)&sizeof(Output)&sizeof(Input))==(sizeof(inte_16)|sizeof(Output)|sizeof(Input)),"Not 16-bit!");\
	Acs_(inte_16,Output)=Acs_(inte_16,Input)>>15;\
	Acs_(inte_16,Output)&=Acs_(inte_16,Input);\
}lb__
//BitClip : Negative Clipping of 32-bit Integer
#define BitC_Lim_N_I32_(Output,Input)\
__dl{\
	static_assert((sizeof(inte_32)&sizeof(Output)&sizeof(Input))==(sizeof(inte_32)|sizeof(Output)|sizeof(Input)),"Not 32-bit!");\
	Acs_(inte_32,Output)=Acs_(inte_32,Input)>>31;\
	Acs_(inte_32,Output)&=Acs_(inte_32,Input);\
}lb__
//BitClip : Negative Clipping of 64-bit Integer
#define BitC_Lim_N_I64_(Output,Input)\
__dl{\
	static_assert((sizeof(inte_64)&sizeof(Output)&sizeof(Input))==(sizeof(inte_64)|sizeof(Output)|sizeof(Input)),"Not 64-bit!");\
	Acs_(inte_64,Output)=Acs_(inte_64,Input)>>63;\
	Acs_(inte_64,Output)&=Acs_(inte_64,Input);\
}lb__
//BitClip : Negative Clipping of 32-bit Real
#define BitC_Lim_N_R32_(Output,Input)\
__dl{\
	static_assert((sizeof(real_32)&sizeof(Output)&sizeof(Input))==(sizeof(real_32)|sizeof(Output)|sizeof(Input)),"Not 32-bit!");\
	Acs_(inte_32,Output)=Acs_(inte_32,Input)>>31;\
	Acs_(inte_32,Output)&=Acs_(inte_32,Input);\
}lb__
//BitClip : Negative Clipping of 64-bit Real
#define BitC_Lim_N_R64_(Output,Input)\
__dl{\
static_assert((sizeof(real_64)&sizeof(Output)&sizeof(Input))==(sizeof(real_64)|sizeof(Output)|sizeof(Input)),"Not 64-bit!");\
Acs_(inte_64,Output)=Acs_(inte_64,Input)>>63;\
Acs_(inte_64,Output)&=Acs_(inte_64,Input);\
}lb__
#endif
#endif

#if(Fold_(String Formatting Macros))
#if(Fold_(BitC_Put_Dec_T##_))
#define BitC_Put_Dec_D08_(width) "%" Meta_(width) PRIu8
#define BitC_Put_Dec_D16_(width) "%" Meta_(width) PRIu16
#define BitC_Put_Dec_D32_(width) "%" Meta_(width) PRIu32
#define BitC_Put_Dec_D64_(width) "%" Meta_(width) PRIu64

#define BitC_Put_Dec_I08_(width) "%+" Meta_(width) PRIi8
#define BitC_Put_Dec_I16_(width) "%+" Meta_(width) PRIi16
#define BitC_Put_Dec_I32_(width) "%+" Meta_(width) PRIi32
#define BitC_Put_Dec_I64_(width) "%+" Meta_(width) PRIi64

#define BitC_Put_Dec_R32_(width,precision) "%+" Meta_(width) "." Meta_(precision) "F"
#define BitC_Put_Dec_R64_(width,precision) "%+" Meta_(width) "." Meta_(precision) "lF"
#endif

#if(Fold_(BitC_Put_Exp_R##_))
#define BitC_Put_Exp_R32_(width,precision) "%+" Meta_(width) "." Meta_(precision) "E"
#define BitC_Put_Exp_R64_(width,precision) "%+" Meta_(width) "." Meta_(precision) "lE"
#endif

#if(Fold_(BitC_Put_Hex_T##_))
#define BitC_Put_Hex_D08_() "%#02" PRIX8
#define BitC_Put_Hex_D16_() "%#04" PRIX16
#define BitC_Put_Hex_D32_() "%#08" PRIX32
#define BitC_Put_Hex_D64_() "%#016" PRIX64

#define BitC_Put_Hex_I08_() BitC_Put_Hex_D08_()
#define BitC_Put_Hex_I16_() BitC_Put_Hex_D16_()
#define BitC_Put_Hex_I32_() BitC_Put_Hex_D32_()
#define BitC_Put_Hex_I64_() BitC_Put_Hex_D64_()

#define BitC_Put_Hex_R32_() "%+.6" "A"
#define BitC_Put_Hex_R64_() "%+.13" "lA"
#endif

#if(Fold_(BitC_Get_Dec_T##_))
#define BitC_Get_D08_(width) BitC_Get_I08_(width)
#define BitC_Get_D16_(width) BitC_Get_I16_(width)
#define BitC_Get_D32_(width) BitC_Get_I32_(width)
#define BitC_Get_D64_(width) BitC_Get_I64_(width)

#define BitC_Get_I08_(width) "%" Meta_(width) SCNi8
#define BitC_Get_I16_(width) "%" Meta_(width) SCNi16
#define BitC_Get_I32_(width) "%" Meta_(width) SCNi32
#define BitC_Get_I64_(width) "%" Meta_(width) SCNi64

#define BitC_Get_R32_(width) "%" Meta_(width) "F"
#define BitC_Get_R64_(width) "%" Meta_(width) "lF"
#endif
#endif

#if(Fold_(Library Casing))
//BitClip : Library Case Structure
typedef const struct
{
	//BitClip : Some Constants
	const struct
	{
		//BitClip : Library Version - "BitC:yyyy.mm.dd"
		BYTE_08 _PL_ _R_ Version;
		//BitClip : Environment Endianness
		//＊0x00 for big-endian, 0x01 for little-endian.
		DATA_08 _PL_ _R_ Endianness;

		//BitClip : Okay Function Set
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//BitClip : Check whether the casted functions work correctly for this library.
			logical(_PL_ Wrap_)(general);
			//BitClip : Check whether the casted function works correctly.
			logical(_PL_ Cast_)(BITC_TE Source,BITC_TE Target);
		}
		Okay;
	};

	//BitClip : Type Descriptor Set
	const struct
	{
		MEMC_DT _PL_ _R_ D08;	//BitClip : data_08
		MEMC_DT _PL_ _R_ D16;	//BitClip : data_16
		MEMC_DT _PL_ _R_ D32;	//BitClip : data_32
		MEMC_DT _PL_ _R_ D64;	//BitClip : data_64
		MEMC_DT _PL_ _R_ I08;	//BitClip : inte_08
		MEMC_DT _PL_ _R_ I16;	//BitClip : inte_16
		MEMC_DT _PL_ _R_ I32;	//BitClip : inte_32
		MEMC_DT _PL_ _R_ I64;	//BitClip : inte_64
		MEMC_DT _PL_ _R_ R08;	//BitClip : real_08
		MEMC_DT _PL_ _R_ R16;	//BitClip : real_16
		MEMC_DT _PL_ _R_ R32;	//BitClip : real_32
		MEMC_DT _PL_ _R_ R64;	//BitClip : real_64

		//BitClip : Descriptor to Enumeration Conversion
		bitc_te(_PL_ Enum_)(MEMC_DT _PL_ _R_ Descriptor);
		//BitClip : Enumeration to Descriptor Conversion
		MEMC_DT*(_PL_ Desc_)(BITC_TE Enumeration);
	}
	Type;

	//BitClip : Reformation
	const struct
	{
		//BitClip : Maximum Dimension
		ADDRESS MaxDims;

		//BitClip : Array Reformation
		//＊(Dimensions) should not be greater than "BitC.MaxDims".
		//　SourceShape[dim] == TargetShape[ReformingAxis[dim]] where dim＜(Dimensions).
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Reform_)(GENERAL _PL_ SourceArray,general _PL_ TargetArray,ADDRESS _PL_ SourceShape,ADDRESS _PL_ ReformingAxis,ADDRESS Dimensions,ADDRESS TypeSize);
#define BitC_Reform_(S,T,SShp,StoTAxis,Dims) (MemC_Assert_(sizeof(*(S))==sizeof(*(T))),BitC.Reform_(S,T,SShp,StoTAxis,Dims,sizeof(*(S))))
	};

	//BitClip : Global Constant Number Set
	const struct
	{
		//BitClip : Mask Set
		const struct
		{
			ADDRESS _PL_ _R_ Safe;	//BitClip : Safe[n]＝0-(1<<n) where n＝0, 1, ..., 7.
			ADDRESS _PL_ _R_ Rest;	//BitClip : Rest[n]＝(1<<n)-1 where n＝0, 1, ..., 7.
		}
		Mask;

		//BitClip : Preserved for Future Usage
		ADDRESS xPreserved[2];

		//BitClip : Pi Number Set
		const struct
		{
			//BitClip : 32-bit Pi Number
			//＊[0] : π
			//　[1] : 1／π
			REAL_32 _PL_ _R_ R32;
			//BitClip : 64-bit Pi Number
			//＊[0] : π
			//　[1] : 1／π
			REAL_64 _PL_ _R_ R64;
		}
		Pi;

		//BitClip : Euler Number Set
		const struct
		{
			//BitClip : 32-bit Euler Number
			//＊[0] : ｅ
			//　[1] : 1／ｅ
			REAL_32 _PL_ _R_ R32;
			//BitClip : 64-bit Euler Number
			//＊[0] : ｅ
			//　[1] : 1／ｅ
			REAL_64 _PL_ _R_ R64;
		}
		Euler;

		//BitClip : Infinite Number Set
		const struct
		{
			//BitClip : 32-bit Infinite Number
			//＊[0] : ＋∞
			//　[1] : －∞
			REAL_32 _PL_ _R_ R32;
			//BitClip : 64-bit Infinite Number
			//＊[0] : ＋∞
			//　[1] : －∞
			REAL_64 _PL_ _R_ R64;
		}
		Inf;

		//BitClip : Not-a-Number Set
		const struct
		{
			//BitClip : 32-bit Not-a-Number
			//＊[0] : ＋NaN
			//　[1] : －NaN
			REAL_32 _PL_ _R_ R32;
			//BitClip : 64-bit Not-a-Number
			//＊[0] : ＋NaN
			//　[1] : －NaN
			REAL_64 _PL_ _R_ R64;
		}
		NaN;
	}
	Const;

	//BitClip : Some Operations
	const struct
	{
		//BitClip : Bit Pointer Function Set
		const struct
		{
			//BitClip : Bit Pointer Assign
			const struct
			{
				//BitClip : Assign with signed offset.
				bitc_bp(_PL_ S_)(general _PL_ BaseAddress,SINTPTR BitOffset);
				//BitClip : Assign with unsigned offset.
				bitc_bp(_PL_ U_)(general _PL_ BaseAddress,UINTPTR BitOffset);
			}
			Assign;

			//BitClip : Bit Pointer Move
			//＊Return value is the moved pointer.
			const struct
			{
				//BitClip : Move with signed offset.
				bitc_bp(_PL_ S_)(BITC_BP BitPointer,SINTPTR Move);
				//BitClip : Move with unsigned offset.
				bitc_bp(_PL_ U_)(BITC_BP BitPointer,UINTPTR Move);
			}
			Jumper;

			//BitClip : Read and Write
			const struct
			{
				//BitClip : Bit Pointer Read
				//＊Return value is 0 or 1.
				logical(_PL_ Reader_)(BITC_BP BitPointer);
				//BitClip : Bit Pointer Write
				//＊Bool value should be 0 or 1.
				general(_PL_ Writer_)(BITC_BP BitPointer,LOGICAL Boolean);
			};

			//BitClip : Comparison and Difference
			const struct
			{
				//BitClip : Bit Pointer Comparison
				//＊Return value is -1 for A<B, 0 for A==B, or +1 for A>B.
				integer(_PL_ Comp_)(BITC_BP A,BITC_BP B);
				//BitClip : Bit Pointer Difference
				//＊Return value is (A.Base－B.Base)×8＋(A.Offset－B.Offset).
				sintptr(_PL_ Diff_)(BITC_BP A,BITC_BP B);
			};
		}
		BP;

		//BitClip : Endian Flipping Function Set
		const union
		{
			const struct
			{
				//BitClip : 8-bit Natural Endian Flipping
				general(_PL_ D08_)(data_08 _PL_ Data,ADDRESS Length);
				//BitClip : 16-bit Natural Endian Flipping
				general(_PL_ D16_)(data_16 _PL_ Data,ADDRESS Length);
				//BitClip : 32-bit Natural Endian Flipping
				general(_PL_ D32_)(data_32 _PL_ Data,ADDRESS Length);
				//BitClip : 64-bit Natural Endian Flipping
				general(_PL_ D64_)(data_64 _PL_ Data,ADDRESS Length);
			};
			const struct
			{
				//BitClip : 8-bit Integer Endian Flipping
				general(_PL_ I08_)(inte_08 _PL_ Data,ADDRESS Length);
				//BitClip : 16-bit Integer Endian Flipping
				general(_PL_ I16_)(inte_16 _PL_ Data,ADDRESS Length);

				const union
				{
					const struct
					{
						//BitClip : 32-bit Integer Endian Flipping
						general(_PL_ I32_)(inte_32 _PL_ Data,ADDRESS Length);
						//BitClip : 64-bit Integer Endian Flipping
						general(_PL_ I64_)(inte_64 _PL_ Data,ADDRESS Length);
					};
					const struct
					{
						//BitClip : 32-bit Real Endian Flipping
						general(_PL_ R32_)(real_32 _PL_ Data,ADDRESS Length);
						//BitClip : 64-bit Real Endian Flipping
						general(_PL_ R64_)(real_64 _PL_ Data,ADDRESS Length);
					};
				};
			};
		}
		Endian;

		//BitClip : Bit Operation Function Set
		const struct
		{
			//BitClip : NOT Operation
			const union
			{
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
				};
				const struct
				{
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
				};
			}
			N_1;

			//BitClip : Shift Operation
			const struct
			{
				//BitClip : 8-Bit Natural Shift Operation
				//＊C[n]＝(S>0)?(A[n]<<S):(A[n]>>(-S))
				general(_PL_ D08_)(data_08 _PL_ C,DATA_08 _PL_ A,INTEGER S,ADDRESS N);
				//BitClip : 16-Bit Natural Shift Operation
				//＊C[n]＝(S>0)?(A[n]<<S):(A[n]>>(-S))
				general(_PL_ D16_)(data_16 _PL_ C,DATA_16 _PL_ A,INTEGER S,ADDRESS N);
				//BitClip : 32-Bit Natural Shift Operation
				//＊C[n]＝(S>0)?(A[n]<<S):(A[n]>>(-S))
				general(_PL_ D32_)(data_32 _PL_ C,DATA_32 _PL_ A,INTEGER S,ADDRESS N);
				//BitClip : 64-Bit Natural Shift Operation
				//＊C[n]＝(S>0)?(A[n]<<S):(A[n]>>(-S))
				general(_PL_ D64_)(data_64 _PL_ C,DATA_64 _PL_ A,INTEGER S,ADDRESS N);
				//BitClip : 8-Bit Integer Shift Operation
				//＊C[n]＝(S>0)?(A[n]<<S):(A[n]>>(-S))
				general(_PL_ I08_)(inte_08 _PL_ C,INTE_08 _PL_ A,INTEGER S,ADDRESS N);
				//BitClip : 16-Bit Integer Shift Operation
				//＊C[n]＝(S>0)?(A[n]<<S):(A[n]>>(-S))
				general(_PL_ I16_)(inte_16 _PL_ C,INTE_16 _PL_ A,INTEGER S,ADDRESS N);
				//BitClip : 32-Bit Integer Shift Operation
				//＊C[n]＝(S>0)?(A[n]<<S):(A[n]>>(-S))
				general(_PL_ I32_)(inte_32 _PL_ C,INTE_32 _PL_ A,INTEGER S,ADDRESS N);
				//BitClip : 64-Bit Integer Shift Operation
				//＊C[n]＝(S>0)?(A[n]<<S):(A[n]>>(-S))
				general(_PL_ I64_)(inte_64 _PL_ C,INTE_64 _PL_ A,INTEGER S,ADDRESS N);
			}
			S_1;

			//BitClip : AND Operation
			const union
			{
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
				};
				const struct
				{
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
				};
			}
			A_1;

			//BitClip : AND Operation
			const union
			{
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
				};
				const struct
				{
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
				};
			}
			A_2;

			//BitClip : OR Operation
			const union
			{
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
				};
				const struct
				{
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
				};
			}
			O_1;

			//BitClip : OR Operation
			const union
			{
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
				};
				const struct
				{
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
				};
			}
			O_2;

			//BitClip : XOR Operation
			const union
			{
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
				};
				const struct
				{
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
				};
			}
			X_1;

			//BitClip : XOR Operation
			const union
			{
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
				};
				const struct
				{
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
				};
			}
			X_2;
		}
		BO;

		//BitClip : Relational Operation Function Set
		const struct
		{
			//BitClip : Bit Expansion
			const union
			{
				const struct
				{
					//BitClip : Bit Expansion to 8-bit Natural
					//＊O[n]＝(I[n/8].bit[n%8])?(0xFF):(0x00)
					general(_PL_ D08_)(DATA_08 _PL_ _R_ I,data_08 _PL_ _R_ O,ADDRESS N);
					//BitClip : Bit Expansion to 16-bit Natural
					//＊O[n]＝(I[n/8].bit[n%8])?(0xFFFF):(0x0000)
					general(_PL_ D16_)(DATA_08 _PL_ _R_ I,data_16 _PL_ _R_ O,ADDRESS N);
					//BitClip : Bit Expansion to 32-bit Natural
					//＊O[n]＝(I[n/8].bit[n%8])?(0xFFFFFFFF):(0x00000000)
					general(_PL_ D32_)(DATA_08 _PL_ _R_ I,data_32 _PL_ _R_ O,ADDRESS N);
					//BitClip : Bit Expansion to 64-bit Natural
					//＊O[n]＝(I[n/8].bit[n%8])?(0xFFFFFFFFFFFFFFFF):(0x0000000000000000)
					general(_PL_ D64_)(DATA_08 _PL_ _R_ I,data_64 _PL_ _R_ O,ADDRESS N);
				};
				const struct
				{
					//BitClip : Bit Expansion to 8-bit Integer
					//＊O[n]＝(I[n/8].bit[n%8])?(0xFF):(0x00)
					general(_PL_ I08_)(DATA_08 _PL_ _R_ I,inte_08 _PL_ _R_ O,ADDRESS N);
					//BitClip : Bit Expansion to 16-bit Integer
					//＊O[n]＝(I[n/8].bit[n%8])?(0xFFFF):(0x0000)
					general(_PL_ I16_)(DATA_08 _PL_ _R_ I,inte_16 _PL_ _R_ O,ADDRESS N);
					//BitClip : Bit Expansion to 32-bit Integer
					//＊O[n]＝(I[n/8].bit[n%8])?(0xFFFFFFFF):(0x00000000)
					general(_PL_ I32_)(DATA_08 _PL_ _R_ I,inte_32 _PL_ _R_ O,ADDRESS N);
					//BitClip : Bit Expansion to 64-bit Integer
					//＊O[n]＝(I[n/8].bit[n%8])?(0xFFFFFFFFFFFFFFFF):(0x0000000000000000)
					general(_PL_ I64_)(DATA_08 _PL_ _R_ I,inte_64 _PL_ _R_ O,ADDRESS N);
				};
			}
			Expand;

			//BitClip : Bit Shrink
			const union
			{
				const struct
				{
					//BitClip : Bit Shrinkage from 8-bit Natural
					//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
					general(_PL_ D08_)(DATA_08 _PL_ _R_ I,data_08 _PL_ _R_ O,ADDRESS N);
					//BitClip : Bit Shrinkage from 16-bit Natural
					//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
					general(_PL_ D16_)(DATA_16 _PL_ _R_ I,data_08 _PL_ _R_ O,ADDRESS N);
					//BitClip : Bit Shrinkage from 32-bit Natural
					//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
					general(_PL_ D32_)(DATA_32 _PL_ _R_ I,data_08 _PL_ _R_ O,ADDRESS N);
					//BitClip : Bit Shrinkage from 64-bit Natural
					//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
					general(_PL_ D64_)(DATA_64 _PL_ _R_ I,data_08 _PL_ _R_ O,ADDRESS N);
				};
				const struct
				{
					//BitClip : Bit Shrinkage from 8-bit Integer
					//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
					general(_PL_ I08_)(INTE_08 _PL_ _R_ I,data_08 _PL_ _R_ O,ADDRESS N);
					//BitClip : Bit Shrinkage from 16-bit Integer
					//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
					general(_PL_ I16_)(INTE_16 _PL_ _R_ I,data_08 _PL_ _R_ O,ADDRESS N);
					//BitClip : Bit Shrinkage from 32-bit Integer
					//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
					general(_PL_ I32_)(INTE_32 _PL_ _R_ I,data_08 _PL_ _R_ O,ADDRESS N);
					//BitClip : Bit Shrinkage from 64-bit Integer
					//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
					general(_PL_ I64_)(INTE_64 _PL_ _R_ I,data_08 _PL_ _R_ O,ADDRESS N);
				};
			}
			Shrink;

			//BitClip : EQ Operation
			const union
			{
				const struct
				{
					//BitClip : 8-bit Natural EQ Operation
					//＊C[n/8].bit[n%8]＝(A[n]==V)
					general(_PL_ D08_)(data_08 _PL_ _R_ C,DATA_08 _PL_ _R_ A,DATA_08 V,ADDRESS N);
					//BitClip : 16-bit Natural EQ Operation
					//＊C[n/8].bit[n%8]＝(A[n]==V)
					general(_PL_ D16_)(data_08 _PL_ _R_ C,DATA_16 _PL_ _R_ A,DATA_16 V,ADDRESS N);
					//BitClip : 32-bit Natural EQ Operation
					//＊C[n/8].bit[n%8]＝(A[n]==V)
					general(_PL_ D32_)(data_08 _PL_ _R_ C,DATA_32 _PL_ _R_ A,DATA_32 V,ADDRESS N);
					//BitClip : 64-bit Natural EQ Operation
					//＊C[n/8].bit[n%8]＝(A[n]==V)
					general(_PL_ D64_)(data_08 _PL_ _R_ C,DATA_64 _PL_ _R_ A,DATA_64 V,ADDRESS N);
				};
				const struct
				{
					//BitClip : 8-bit Integer EQ Operation
					//＊C[n/8].bit[n%8]＝(A[n]==V)
					general(_PL_ I08_)(data_08 _PL_ _R_ C,INTE_08 _PL_ _R_ A,INTE_08 V,ADDRESS N);
					//BitClip : 16-bit Integer EQ Operation
					//＊C[n/8].bit[n%8]＝(A[n]==V)
					general(_PL_ I16_)(data_08 _PL_ _R_ C,INTE_16 _PL_ _R_ A,INTE_16 V,ADDRESS N);

					const union
					{
						const struct
						{
							//BitClip : 32-bit Integer EQ Operation
							//＊C[n/8].bit[n%8]＝(A[n]==V)
							general(_PL_ I32_)(data_08 _PL_ _R_ C,INTE_32 _PL_ _R_ A,INTE_32 V,ADDRESS N);
							//BitClip : 64-bit Integer EQ Operation
							//＊C[n/8].bit[n%8]＝(A[n]==V)
							general(_PL_ I64_)(data_08 _PL_ _R_ C,INTE_64 _PL_ _R_ A,INTE_64 V,ADDRESS N);
						};
						const struct
						{
							//BitClip : 32-bit Real EQ Operation
							//＊C[n/8].bit[n%8]＝(A[n]==V)
							general(_PL_ R32_)(data_08 _PL_ _R_ C,REAL_32 _PL_ _R_ A,REAL_32 V,ADDRESS N);
							//BitClip : 64-bit Real EQ Operation
							//＊C[n/8].bit[n%8]＝(A[n]==V)
							general(_PL_ R64_)(data_08 _PL_ _R_ C,REAL_64 _PL_ _R_ A,REAL_64 V,ADDRESS N);
						};
					};
				};
			}
			E_1;

			//BitClip : EQ Operation
			const union
			{
				const struct
				{
					//BitClip : 8-bit Natural EQ Operation
					//＊C[n/8].bit[n%8]＝(A[n]==B[n])
					general(_PL_ D08_)(data_08 _PL_ _R_ C,DATA_08 _PL_ _R_ A,DATA_08 _PL_ _R_ B,ADDRESS N);
					//BitClip : 16-bit Natural EQ Operation
					//＊C[n/8].bit[n%8]＝(A[n]==B[n])
					general(_PL_ D16_)(data_08 _PL_ _R_ C,DATA_16 _PL_ _R_ A,DATA_16 _PL_ _R_ B,ADDRESS N);
					//BitClip : 32-bit Natural EQ Operation
					//＊C[n/8].bit[n%8]＝(A[n]==B[n])
					general(_PL_ D32_)(data_08 _PL_ _R_ C,DATA_32 _PL_ _R_ A,DATA_32 _PL_ _R_ B,ADDRESS N);
					//BitClip : 64-bit Natural EQ Operation
					//＊C[n/8].bit[n%8]＝(A[n]==B[n])
					general(_PL_ D64_)(data_08 _PL_ _R_ C,DATA_64 _PL_ _R_ A,DATA_64 _PL_ _R_ B,ADDRESS N);
				};
				const struct
				{
					//BitClip : 8-bit Integer EQ Operation
					//＊C[n/8].bit[n%8]＝(A[n]==B[n])
					general(_PL_ I08_)(data_08 _PL_ _R_ C,INTE_08 _PL_ _R_ A,INTE_08 _PL_ _R_ B,ADDRESS N);
					//BitClip : 16-bit Integer EQ Operation
					//＊C[n/8].bit[n%8]＝(A[n]==B[n])
					general(_PL_ I16_)(data_08 _PL_ _R_ C,INTE_16 _PL_ _R_ A,INTE_16 _PL_ _R_ B,ADDRESS N);

					const union
					{
						const struct
						{
							//BitClip : 32-bit Integer EQ Operation
							//＊C[n/8].bit[n%8]＝(A[n]==B[n])
							general(_PL_ I32_)(data_08 _PL_ _R_ C,INTE_32 _PL_ _R_ A,INTE_32 _PL_ _R_ B,ADDRESS N);
							//BitClip : 64-bit Integer EQ Operation
							//＊C[n/8].bit[n%8]＝(A[n]==B[n])
							general(_PL_ I64_)(data_08 _PL_ _R_ C,INTE_64 _PL_ _R_ A,INTE_64 _PL_ _R_ B,ADDRESS N);
						};
						const struct
						{
							//BitClip : 32-bit Real EQ Operation
							//＊C[n/8].bit[n%8]＝(A[n]==B[n])
							general(_PL_ R32_)(data_08 _PL_ _R_ C,REAL_32 _PL_ _R_ A,REAL_32 _PL_ _R_ B,ADDRESS N);
							//BitClip : 64-bit Real EQ Operation
							//＊C[n/8].bit[n%8]＝(A[n]==B[n])
							general(_PL_ R64_)(data_08 _PL_ _R_ C,REAL_64 _PL_ _R_ A,REAL_64 _PL_ _R_ B,ADDRESS N);
						};
					};
				};
			}
			E_2;

			//BitClip : NE Operation
			const union
			{
				const struct
				{
					//BitClip : 8-bit Natural NE Operation
					//＊C[n/8].bit[n%8]＝(A[n]!=V)
					general(_PL_ D08_)(data_08 _PL_ _R_ C,DATA_08 _PL_ _R_ A,DATA_08 V,ADDRESS N);
					//BitClip : 16-bit Natural NE Operation
					//＊C[n/8].bit[n%8]＝(A[n]!=V)
					general(_PL_ D16_)(data_08 _PL_ _R_ C,DATA_16 _PL_ _R_ A,DATA_16 V,ADDRESS N);
					//BitClip : 32-bit Natural NE Operation
					//＊C[n/8].bit[n%8]＝(A[n]!=V)
					general(_PL_ D32_)(data_08 _PL_ _R_ C,DATA_32 _PL_ _R_ A,DATA_32 V,ADDRESS N);
					//BitClip : 64-bit Natural NE Operation
					//＊C[n/8].bit[n%8]＝(A[n]!=V)
					general(_PL_ D64_)(data_08 _PL_ _R_ C,DATA_64 _PL_ _R_ A,DATA_64 V,ADDRESS N);
				};
				const struct
				{
					//BitClip : 8-bit Integer NE Operation
					//＊C[n/8].bit[n%8]＝(A[n]!=V)
					general(_PL_ I08_)(data_08 _PL_ _R_ C,INTE_08 _PL_ _R_ A,INTE_08 V,ADDRESS N);
					//BitClip : 16-bit Integer NE Operation
					//＊C[n/8].bit[n%8]＝(A[n]!=V)
					general(_PL_ I16_)(data_08 _PL_ _R_ C,INTE_16 _PL_ _R_ A,INTE_16 V,ADDRESS N);

					const union
					{
						const struct
						{
							//BitClip : 32-bit Integer NE Operation
							//＊C[n/8].bit[n%8]＝(A[n]!=V)
							general(_PL_ I32_)(data_08 _PL_ _R_ C,INTE_32 _PL_ _R_ A,INTE_32 V,ADDRESS N);
							//BitClip : 64-bit Integer NE Operation
							//＊C[n/8].bit[n%8]＝(A[n]!=V)
							general(_PL_ I64_)(data_08 _PL_ _R_ C,INTE_64 _PL_ _R_ A,INTE_64 V,ADDRESS N);
						};
						const struct
						{
							//BitClip : 32-bit Real NE Operation
							//＊C[n/8].bit[n%8]＝(A[n]!=V)
							general(_PL_ R32_)(data_08 _PL_ _R_ C,REAL_32 _PL_ _R_ A,REAL_32 V,ADDRESS N);
							//BitClip : 64-bit Real NE Operation
							//＊C[n/8].bit[n%8]＝(A[n]!=V)
							general(_PL_ R64_)(data_08 _PL_ _R_ C,REAL_64 _PL_ _R_ A,REAL_64 V,ADDRESS N);
						};
					};
				};
			}
			N_1;

			//BitClip : NE Operation
			const union
			{
				const struct
				{
					//BitClip : 8-bit Natural NE Operation
					//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
					general(_PL_ D08_)(data_08 _PL_ _R_ C,DATA_08 _PL_ _R_ A,DATA_08 _PL_ _R_ B,ADDRESS N);
					//BitClip : 16-bit Natural NE Operation
					//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
					general(_PL_ D16_)(data_08 _PL_ _R_ C,DATA_16 _PL_ _R_ A,DATA_16 _PL_ _R_ B,ADDRESS N);
					//BitClip : 32-bit Natural NE Operation
					//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
					general(_PL_ D32_)(data_08 _PL_ _R_ C,DATA_32 _PL_ _R_ A,DATA_32 _PL_ _R_ B,ADDRESS N);
					//BitClip : 64-bit Natural NE Operation
					//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
					general(_PL_ D64_)(data_08 _PL_ _R_ C,DATA_64 _PL_ _R_ A,DATA_64 _PL_ _R_ B,ADDRESS N);
				};
				const struct
				{
					//BitClip : 8-bit Integer NE Operation
					//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
					general(_PL_ I08_)(data_08 _PL_ _R_ C,INTE_08 _PL_ _R_ A,INTE_08 _PL_ _R_ B,ADDRESS N);
					//BitClip : 16-bit Integer NE Operation
					//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
					general(_PL_ I16_)(data_08 _PL_ _R_ C,INTE_16 _PL_ _R_ A,INTE_16 _PL_ _R_ B,ADDRESS N);

					const union
					{
						const struct
						{
							//BitClip : 32-bit Integer NE Operation
							//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
							general(_PL_ I32_)(data_08 _PL_ _R_ C,INTE_32 _PL_ _R_ A,INTE_32 _PL_ _R_ B,ADDRESS N);
							//BitClip : 64-bit Integer NE Operation
							//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
							general(_PL_ I64_)(data_08 _PL_ _R_ C,INTE_64 _PL_ _R_ A,INTE_64 _PL_ _R_ B,ADDRESS N);
						};
						const struct
						{
							//BitClip : 32-bit Real NE Operation
							//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
							general(_PL_ R32_)(data_08 _PL_ _R_ C,REAL_32 _PL_ _R_ A,REAL_32 _PL_ _R_ B,ADDRESS N);
							//BitClip : 64-bit Real NE Operation
							//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
							general(_PL_ R64_)(data_08 _PL_ _R_ C,REAL_64 _PL_ _R_ A,REAL_64 _PL_ _R_ B,ADDRESS N);
						};
					};
				};
			}
			N_2;

			//BitClip : GE Operation
			const struct
			{
				//BitClip : 8-bit Natural GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥V)
				general(_PL_ D08_)(data_08 _PL_ _R_ C,DATA_08 _PL_ _R_ A,DATA_08 V,ADDRESS N);
				//BitClip : 16-bit Natural GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥V)
				general(_PL_ D16_)(data_08 _PL_ _R_ C,DATA_16 _PL_ _R_ A,DATA_16 V,ADDRESS N);
				//BitClip : 32-bit Natural GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥V)
				general(_PL_ D32_)(data_08 _PL_ _R_ C,DATA_32 _PL_ _R_ A,DATA_32 V,ADDRESS N);
				//BitClip : 64-bit Natural GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥V)
				general(_PL_ D64_)(data_08 _PL_ _R_ C,DATA_64 _PL_ _R_ A,DATA_64 V,ADDRESS N);
				//BitClip : 8-bit Integer GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥V)
				general(_PL_ I08_)(data_08 _PL_ _R_ C,INTE_08 _PL_ _R_ A,INTE_08 V,ADDRESS N);
				//BitClip : 16-bit Integer GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥V)
				general(_PL_ I16_)(data_08 _PL_ _R_ C,INTE_16 _PL_ _R_ A,INTE_16 V,ADDRESS N);
				//BitClip : 32-bit Integer GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥V)
				general(_PL_ I32_)(data_08 _PL_ _R_ C,INTE_32 _PL_ _R_ A,INTE_32 V,ADDRESS N);
				//BitClip : 64-bit Integer GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥V)
				general(_PL_ I64_)(data_08 _PL_ _R_ C,INTE_64 _PL_ _R_ A,INTE_64 V,ADDRESS N);
				//BitClip : 32-bit Real GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥V)
				general(_PL_ R32_)(data_08 _PL_ _R_ C,REAL_32 _PL_ _R_ A,REAL_32 V,ADDRESS N);
				//BitClip : 64-bit Real GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥V)
				general(_PL_ R64_)(data_08 _PL_ _R_ C,REAL_64 _PL_ _R_ A,REAL_64 V,ADDRESS N);
			}
			G_1;

			//BitClip : GE Operation
			const struct
			{
				//BitClip : 8-bit Natural GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
				general(_PL_ D08_)(data_08 _PL_ _R_ C,DATA_08 _PL_ _R_ A,DATA_08 _PL_ _R_ B,ADDRESS N);
				//BitClip : 16-bit Natural GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
				general(_PL_ D16_)(data_08 _PL_ _R_ C,DATA_16 _PL_ _R_ A,DATA_16 _PL_ _R_ B,ADDRESS N);
				//BitClip : 32-bit Natural GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
				general(_PL_ D32_)(data_08 _PL_ _R_ C,DATA_32 _PL_ _R_ A,DATA_32 _PL_ _R_ B,ADDRESS N);
				//BitClip : 64-bit Natural GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
				general(_PL_ D64_)(data_08 _PL_ _R_ C,DATA_64 _PL_ _R_ A,DATA_64 _PL_ _R_ B,ADDRESS N);
				//BitClip : 8-bit Integer GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
				general(_PL_ I08_)(data_08 _PL_ _R_ C,INTE_08 _PL_ _R_ A,INTE_08 _PL_ _R_ B,ADDRESS N);
				//BitClip : 16-bit Integer GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
				general(_PL_ I16_)(data_08 _PL_ _R_ C,INTE_16 _PL_ _R_ A,INTE_16 _PL_ _R_ B,ADDRESS N);
				//BitClip : 32-bit Integer GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
				general(_PL_ I32_)(data_08 _PL_ _R_ C,INTE_32 _PL_ _R_ A,INTE_32 _PL_ _R_ B,ADDRESS N);
				//BitClip : 64-bit Integer GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
				general(_PL_ I64_)(data_08 _PL_ _R_ C,INTE_64 _PL_ _R_ A,INTE_64 _PL_ _R_ B,ADDRESS N);
				//BitClip : 32-bit Real GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
				general(_PL_ R32_)(data_08 _PL_ _R_ C,REAL_32 _PL_ _R_ A,REAL_32 _PL_ _R_ B,ADDRESS N);
				//BitClip : 64-bit Real GE Operation
				//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
				general(_PL_ R64_)(data_08 _PL_ _R_ C,REAL_64 _PL_ _R_ A,REAL_64 _PL_ _R_ B,ADDRESS N);
			}
			G_2;

			//BitClip : LT Operation
			const struct
			{
				//BitClip : 8-bit Natural LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜V)
				general(_PL_ D08_)(data_08 _PL_ _R_ C,DATA_08 _PL_ _R_ A,DATA_08 V,ADDRESS N);
				//BitClip : 16-bit Natural LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜V)
				general(_PL_ D16_)(data_08 _PL_ _R_ C,DATA_16 _PL_ _R_ A,DATA_16 V,ADDRESS N);
				//BitClip : 32-bit Natural LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜V)
				general(_PL_ D32_)(data_08 _PL_ _R_ C,DATA_32 _PL_ _R_ A,DATA_32 V,ADDRESS N);
				//BitClip : 64-bit Natural LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜V)
				general(_PL_ D64_)(data_08 _PL_ _R_ C,DATA_64 _PL_ _R_ A,DATA_64 V,ADDRESS N);
				//BitClip : 8-bit Integer LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜V)
				general(_PL_ I08_)(data_08 _PL_ _R_ C,INTE_08 _PL_ _R_ A,INTE_08 V,ADDRESS N);
				//BitClip : 16-bit Integer LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜V)
				general(_PL_ I16_)(data_08 _PL_ _R_ C,INTE_16 _PL_ _R_ A,INTE_16 V,ADDRESS N);
				//BitClip : 32-bit Integer LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜V)
				general(_PL_ I32_)(data_08 _PL_ _R_ C,INTE_32 _PL_ _R_ A,INTE_32 V,ADDRESS N);
				//BitClip : 64-bit Integer LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜V)
				general(_PL_ I64_)(data_08 _PL_ _R_ C,INTE_64 _PL_ _R_ A,INTE_64 V,ADDRESS N);
				//BitClip : 32-bit Real LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜V)
				general(_PL_ R32_)(data_08 _PL_ _R_ C,REAL_32 _PL_ _R_ A,REAL_32 V,ADDRESS N);
				//BitClip : 64-bit Real LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜V)
				general(_PL_ R64_)(data_08 _PL_ _R_ C,REAL_64 _PL_ _R_ A,REAL_64 V,ADDRESS N);
			}
			L_1;

			//BitClip : LT Operation
			const struct
			{
				//BitClip : 8-bit Natural LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
				general(_PL_ D08_)(data_08 _PL_ _R_ C,DATA_08 _PL_ _R_ A,DATA_08 _PL_ _R_ B,ADDRESS N);
				//BitClip : 16-bit Natural LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
				general(_PL_ D16_)(data_08 _PL_ _R_ C,DATA_16 _PL_ _R_ A,DATA_16 _PL_ _R_ B,ADDRESS N);
				//BitClip : 32-bit Natural LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
				general(_PL_ D32_)(data_08 _PL_ _R_ C,DATA_32 _PL_ _R_ A,DATA_32 _PL_ _R_ B,ADDRESS N);
				//BitClip : 64-bit Natural LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
				general(_PL_ D64_)(data_08 _PL_ _R_ C,DATA_64 _PL_ _R_ A,DATA_64 _PL_ _R_ B,ADDRESS N);
				//BitClip : 8-bit Integer LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
				general(_PL_ I08_)(data_08 _PL_ _R_ C,INTE_08 _PL_ _R_ A,INTE_08 _PL_ _R_ B,ADDRESS N);
				//BitClip : 16-bit Integer LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
				general(_PL_ I16_)(data_08 _PL_ _R_ C,INTE_16 _PL_ _R_ A,INTE_16 _PL_ _R_ B,ADDRESS N);
				//BitClip : 32-bit Integer LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
				general(_PL_ I32_)(data_08 _PL_ _R_ C,INTE_32 _PL_ _R_ A,INTE_32 _PL_ _R_ B,ADDRESS N);
				//BitClip : 64-bit Integer LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
				general(_PL_ I64_)(data_08 _PL_ _R_ C,INTE_64 _PL_ _R_ A,INTE_64 _PL_ _R_ B,ADDRESS N);
				//BitClip : 32-bit Real LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
				general(_PL_ R32_)(data_08 _PL_ _R_ C,REAL_32 _PL_ _R_ A,REAL_32 _PL_ _R_ B,ADDRESS N);
				//BitClip : 64-bit Real LT Operation
				//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
				general(_PL_ R64_)(data_08 _PL_ _R_ C,REAL_64 _PL_ _R_ A,REAL_64 _PL_ _R_ B,ADDRESS N);
			}
			L_2;
		}
		RO;

		//BitClip : Type Casting Function Set
		const struct
		{
			//BitClip : Casting from 8-bit Natural
			const struct
			{
				//BitClip : 8-bit Natural to 8-bit Natural Type Casting
				general(_PL_ D08_)(DATA_08 _PL_ _R_ I,data_08 _PL_ _R_ O,ADDRESS N);
				//BitClip : 8-bit Natural to 16-bit Natural Type Casting
				general(_PL_ D16_)(DATA_08 _PL_ _R_ I,data_16 _PL_ _R_ O,ADDRESS N);
				//BitClip : 8-bit Natural to 32-bit Natural Type Casting
				general(_PL_ D32_)(DATA_08 _PL_ _R_ I,data_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 8-bit Natural to 64-bit Natural Type Casting
				general(_PL_ D64_)(DATA_08 _PL_ _R_ I,data_64 _PL_ _R_ O,ADDRESS N);
				//BitClip : 8-bit Natural to 8-bit Integer Type Casting
				general(_PL_ I08_)(DATA_08 _PL_ _R_ I,inte_08 _PL_ _R_ O,ADDRESS N);
				//BitClip : 8-bit Natural to 16-bit Integer Type Casting
				general(_PL_ I16_)(DATA_08 _PL_ _R_ I,inte_16 _PL_ _R_ O,ADDRESS N);
				//BitClip : 8-bit Natural to 32-bit Integer Type Casting
				general(_PL_ I32_)(DATA_08 _PL_ _R_ I,inte_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 8-bit Natural to 64-bit Integer Type Casting
				general(_PL_ I64_)(DATA_08 _PL_ _R_ I,inte_64 _PL_ _R_ O,ADDRESS N);
				//BitClip : 8-bit Natural to 32-bit Real Type Casting
				general(_PL_ R32_)(DATA_08 _PL_ _R_ I,real_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 8-bit Natural to 64-bit Real Type Casting
				general(_PL_ R64_)(DATA_08 _PL_ _R_ I,real_64 _PL_ _R_ O,ADDRESS N);
			}
			D08;

			//BitClip : Casting from 16-bit Natural
			const struct
			{
				//BitClip : 16-bit Natural to 8-bit Natural Type Casting
				general(_PL_ D08_)(DATA_16 _PL_ _R_ I,data_08 _PL_ _R_ O,ADDRESS N);
				//BitClip : 16-bit Natural to 16-bit Natural Type Casting
				general(_PL_ D16_)(DATA_16 _PL_ _R_ I,data_16 _PL_ _R_ O,ADDRESS N);
				//BitClip : 16-bit Natural to 32-bit Natural Type Casting
				general(_PL_ D32_)(DATA_16 _PL_ _R_ I,data_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 16-bit Natural to 64-bit Natural Type Casting
				general(_PL_ D64_)(DATA_16 _PL_ _R_ I,data_64 _PL_ _R_ O,ADDRESS N);
				//BitClip : 16-bit Natural to 8-bit Integer Type Casting
				general(_PL_ I08_)(DATA_16 _PL_ _R_ I,inte_08 _PL_ _R_ O,ADDRESS N);
				//BitClip : 16-bit Natural to 16-bit Integer Type Casting
				general(_PL_ I16_)(DATA_16 _PL_ _R_ I,inte_16 _PL_ _R_ O,ADDRESS N);
				//BitClip : 16-bit Natural to 32-bit Integer Type Casting
				general(_PL_ I32_)(DATA_16 _PL_ _R_ I,inte_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 16-bit Natural to 64-bit Integer Type Casting
				general(_PL_ I64_)(DATA_16 _PL_ _R_ I,inte_64 _PL_ _R_ O,ADDRESS N);
				//BitClip : 16-bit Natural to 32-bit Real Type Casting
				general(_PL_ R32_)(DATA_16 _PL_ _R_ I,real_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 16-bit Natural to 64-bit Real Type Casting
				general(_PL_ R64_)(DATA_16 _PL_ _R_ I,real_64 _PL_ _R_ O,ADDRESS N);
			}
			D16;

			//BitClip : Casting from 32-bit Natural
			const struct
			{
				//BitClip : 32-bit Natural to 8-bit Natural Type Casting
				general(_PL_ D08_)(DATA_32 _PL_ _R_ I,data_08 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Natural to 16-bit Natural Type Casting
				general(_PL_ D16_)(DATA_32 _PL_ _R_ I,data_16 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Natural to 32-bit Natural Type Casting
				general(_PL_ D32_)(DATA_32 _PL_ _R_ I,data_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Natural to 64-bit Natural Type Casting
				general(_PL_ D64_)(DATA_32 _PL_ _R_ I,data_64 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Natural to 8-bit Integer Type Casting
				general(_PL_ I08_)(DATA_32 _PL_ _R_ I,inte_08 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Natural to 16-bit Integer Type Casting
				general(_PL_ I16_)(DATA_32 _PL_ _R_ I,inte_16 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Natural to 32-bit Integer Type Casting
				general(_PL_ I32_)(DATA_32 _PL_ _R_ I,inte_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Natural to 64-bit Integer Type Casting
				general(_PL_ I64_)(DATA_32 _PL_ _R_ I,inte_64 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Natural to 32-bit Real Type Casting
				general(_PL_ R32_)(DATA_32 _PL_ _R_ I,real_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Natural to 64-bit Real Type Casting
				general(_PL_ R64_)(DATA_32 _PL_ _R_ I,real_64 _PL_ _R_ O,ADDRESS N);
			}
			D32;

			//BitClip : Casting from 64-bit Natural
			const struct
			{
				//BitClip : 64-bit Natural to 8-bit Natural Type Casting
				general(_PL_ D08_)(DATA_64 _PL_ _R_ I,data_08 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Natural to 16-bit Natural Type Casting
				general(_PL_ D16_)(DATA_64 _PL_ _R_ I,data_16 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Natural to 32-bit Natural Type Casting
				general(_PL_ D32_)(DATA_64 _PL_ _R_ I,data_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Natural to 64-bit Natural Type Casting
				general(_PL_ D64_)(DATA_64 _PL_ _R_ I,data_64 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Natural to 8-bit Integer Type Casting
				general(_PL_ I08_)(DATA_64 _PL_ _R_ I,inte_08 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Natural to 16-bit Integer Type Casting
				general(_PL_ I16_)(DATA_64 _PL_ _R_ I,inte_16 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Natural to 32-bit Integer Type Casting
				general(_PL_ I32_)(DATA_64 _PL_ _R_ I,inte_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Natural to 64-bit Integer Type Casting
				general(_PL_ I64_)(DATA_64 _PL_ _R_ I,inte_64 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Natural to 32-bit Real Type Casting
				general(_PL_ R32_)(DATA_64 _PL_ _R_ I,real_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Natural to 64-bit Real Type Casting
				general(_PL_ R64_)(DATA_64 _PL_ _R_ I,real_64 _PL_ _R_ O,ADDRESS N);
			}
			D64;

			//BitClip : Casting from 8-bit Integer
			const struct
			{
				//BitClip : 8-bit Integer to 8-bit Natural Type Casting
				general(_PL_ D08_)(INTE_08 _PL_ _R_ I,data_08 _PL_ _R_ O,ADDRESS N);
				//BitClip : 8-bit Integer to 16-bit Natural Type Casting
				general(_PL_ D16_)(INTE_08 _PL_ _R_ I,data_16 _PL_ _R_ O,ADDRESS N);
				//BitClip : 8-bit Integer to 32-bit Natural Type Casting
				general(_PL_ D32_)(INTE_08 _PL_ _R_ I,data_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 8-bit Integer to 64-bit Natural Type Casting
				general(_PL_ D64_)(INTE_08 _PL_ _R_ I,data_64 _PL_ _R_ O,ADDRESS N);
				//BitClip : 8-bit Integer to 8-bit Integer Type Casting
				general(_PL_ I08_)(INTE_08 _PL_ _R_ I,inte_08 _PL_ _R_ O,ADDRESS N);
				//BitClip : 8-bit Integer to 16-bit Integer Type Casting
				general(_PL_ I16_)(INTE_08 _PL_ _R_ I,inte_16 _PL_ _R_ O,ADDRESS N);
				//BitClip : 8-bit Integer to 32-bit Integer Type Casting
				general(_PL_ I32_)(INTE_08 _PL_ _R_ I,inte_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 8-bit Integer to 64-bit Integer Type Casting
				general(_PL_ I64_)(INTE_08 _PL_ _R_ I,inte_64 _PL_ _R_ O,ADDRESS N);
				//BitClip : 8-bit Integer to 32-bit Real Type Casting
				general(_PL_ R32_)(INTE_08 _PL_ _R_ I,real_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 8-bit Integer to 64-bit Real Type Casting
				general(_PL_ R64_)(INTE_08 _PL_ _R_ I,real_64 _PL_ _R_ O,ADDRESS N);
			}
			I08;

			//BitClip : Casting from 16-bit Integer
			const struct
			{
				//BitClip : 16-bit Integer to 8-bit Natural Type Casting
				general(_PL_ D08_)(INTE_16 _PL_ _R_ I,data_08 _PL_ _R_ O,ADDRESS N);
				//BitClip : 16-bit Integer to 16-bit Natural Type Casting
				general(_PL_ D16_)(INTE_16 _PL_ _R_ I,data_16 _PL_ _R_ O,ADDRESS N);
				//BitClip : 16-bit Integer to 32-bit Natural Type Casting
				general(_PL_ D32_)(INTE_16 _PL_ _R_ I,data_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 16-bit Integer to 64-bit Natural Type Casting
				general(_PL_ D64_)(INTE_16 _PL_ _R_ I,data_64 _PL_ _R_ O,ADDRESS N);
				//BitClip : 16-bit Integer to 8-bit Integer Type Casting
				general(_PL_ I08_)(INTE_16 _PL_ _R_ I,inte_08 _PL_ _R_ O,ADDRESS N);
				//BitClip : 16-bit Integer to 16-bit Integer Type Casting
				general(_PL_ I16_)(INTE_16 _PL_ _R_ I,inte_16 _PL_ _R_ O,ADDRESS N);
				//BitClip : 16-bit Integer to 32-bit Integer Type Casting
				general(_PL_ I32_)(INTE_16 _PL_ _R_ I,inte_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 16-bit Integer to 64-bit Integer Type Casting
				general(_PL_ I64_)(INTE_16 _PL_ _R_ I,inte_64 _PL_ _R_ O,ADDRESS N);
				//BitClip : 16-bit Integer to 32-bit Real Type Casting
				general(_PL_ R32_)(INTE_16 _PL_ _R_ I,real_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 16-bit Integer to 64-bit Real Type Casting
				general(_PL_ R64_)(INTE_16 _PL_ _R_ I,real_64 _PL_ _R_ O,ADDRESS N);
			}
			I16;

			//BitClip : Casting from 32-bit Integer
			const struct
			{
				//BitClip : 32-bit Integer to 8-bit Natural Type Casting
				general(_PL_ D08_)(INTE_32 _PL_ _R_ I,data_08 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Integer to 16-bit Natural Type Casting
				general(_PL_ D16_)(INTE_32 _PL_ _R_ I,data_16 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Integer to 32-bit Natural Type Casting
				general(_PL_ D32_)(INTE_32 _PL_ _R_ I,data_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Integer to 64-bit Natural Type Casting
				general(_PL_ D64_)(INTE_32 _PL_ _R_ I,data_64 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Integer to 8-bit Integer Type Casting
				general(_PL_ I08_)(INTE_32 _PL_ _R_ I,inte_08 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Integer to 16-bit Integer Type Casting
				general(_PL_ I16_)(INTE_32 _PL_ _R_ I,inte_16 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Integer to 32-bit Integer Type Casting
				general(_PL_ I32_)(INTE_32 _PL_ _R_ I,inte_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Integer to 64-bit Integer Type Casting
				general(_PL_ I64_)(INTE_32 _PL_ _R_ I,inte_64 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Integer to 32-bit Real Type Casting
				general(_PL_ R32_)(INTE_32 _PL_ _R_ I,real_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Integer to 64-bit Real Type Casting
				general(_PL_ R64_)(INTE_32 _PL_ _R_ I,real_64 _PL_ _R_ O,ADDRESS N);
			}
			I32;

			//BitClip : Casting from 64-bit Integer
			const struct
			{
				//BitClip : 64-bit Integer to 8-bit Natural Type Casting
				general(_PL_ D08_)(INTE_64 _PL_ _R_ I,data_08 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Integer to 16-bit Natural Type Casting
				general(_PL_ D16_)(INTE_64 _PL_ _R_ I,data_16 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Integer to 32-bit Natural Type Casting
				general(_PL_ D32_)(INTE_64 _PL_ _R_ I,data_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Integer to 64-bit Natural Type Casting
				general(_PL_ D64_)(INTE_64 _PL_ _R_ I,data_64 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Integer to 8-bit Integer Type Casting
				general(_PL_ I08_)(INTE_64 _PL_ _R_ I,inte_08 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Integer to 16-bit Integer Type Casting
				general(_PL_ I16_)(INTE_64 _PL_ _R_ I,inte_16 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Integer to 32-bit Integer Type Casting
				general(_PL_ I32_)(INTE_64 _PL_ _R_ I,inte_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Integer to 64-bit Integer Type Casting
				general(_PL_ I64_)(INTE_64 _PL_ _R_ I,inte_64 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Integer to 32-bit Real Type Casting
				general(_PL_ R32_)(INTE_64 _PL_ _R_ I,real_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Integer to 64-bit Real Type Casting
				general(_PL_ R64_)(INTE_64 _PL_ _R_ I,real_64 _PL_ _R_ O,ADDRESS N);
			}
			I64;

			//BitClip : Casting from 32-bit Real
			const struct
			{
				//BitClip : 32-bit Real to 8-bit Natural Type Casting
				general(_PL_ D08_)(REAL_32 _PL_ _R_ I,data_08 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Real to 16-bit Natural Type Casting
				general(_PL_ D16_)(REAL_32 _PL_ _R_ I,data_16 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Real to 32-bit Natural Type Casting
				general(_PL_ D32_)(REAL_32 _PL_ _R_ I,data_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Real to 64-bit Natural Type Casting
				general(_PL_ D64_)(REAL_32 _PL_ _R_ I,data_64 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Real to 8-bit Integer Type Casting
				general(_PL_ I08_)(REAL_32 _PL_ _R_ I,inte_08 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Real to 16-bit Integer Type Casting
				general(_PL_ I16_)(REAL_32 _PL_ _R_ I,inte_16 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Real to 32-bit Integer Type Casting
				general(_PL_ I32_)(REAL_32 _PL_ _R_ I,inte_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Real to 64-bit Integer Type Casting
				general(_PL_ I64_)(REAL_32 _PL_ _R_ I,inte_64 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Real to 32-bit Real Type Casting
				general(_PL_ R32_)(REAL_32 _PL_ _R_ I,real_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 32-bit Real to 64-bit Real Type Casting
				general(_PL_ R64_)(REAL_32 _PL_ _R_ I,real_64 _PL_ _R_ O,ADDRESS N);
			}
			R32;

			//BitClip : Casting from 64-bit Real
			const struct
			{
				//BitClip : 64-bit Real to 8-bit Natural Type Casting
				general(_PL_ D08_)(REAL_64 _PL_ _R_ I,data_08 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Real to 16-bit Natural Type Casting
				general(_PL_ D16_)(REAL_64 _PL_ _R_ I,data_16 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Real to 32-bit Natural Type Casting
				general(_PL_ D32_)(REAL_64 _PL_ _R_ I,data_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Real to 64-bit Natural Type Casting
				general(_PL_ D64_)(REAL_64 _PL_ _R_ I,data_64 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Real to 8-bit Integer Type Casting
				general(_PL_ I08_)(REAL_64 _PL_ _R_ I,inte_08 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Real to 16-bit Integer Type Casting
				general(_PL_ I16_)(REAL_64 _PL_ _R_ I,inte_16 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Real to 32-bit Integer Type Casting
				general(_PL_ I32_)(REAL_64 _PL_ _R_ I,inte_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Real to 64-bit Integer Type Casting
				general(_PL_ I64_)(REAL_64 _PL_ _R_ I,inte_64 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Real to 32-bit Real Type Casting
				general(_PL_ R32_)(REAL_64 _PL_ _R_ I,real_32 _PL_ _R_ O,ADDRESS N);
				//BitClip : 64-bit Real to 64-bit Real Type Casting
				general(_PL_ R64_)(REAL_64 _PL_ _R_ I,real_64 _PL_ _R_ O,ADDRESS N);
			}
			R64;
		}
		Caster;
	};
}
BITCASE;

//BitClip : Library Case Object
extern BITCASE BitC,*BitC_(general);

#ifdef __OPENCL_H
//BitClip : OpenCL Extension Structure
typedef const struct
{
	//BitClip : Program Build Functions
	//＊The number of binary paths must be same as the number of devices associated with the context.
	//＊(BuildOption) Example : "-I ../../Headers -I ../../Sources -D uBitC_R16_=0 -D uBitC_R64_=1"
	const struct
	{
		//BitClip : Build a program as binary files with narrow string paths.
		//＊(SourcePath) Example : "../../Kernels/bitclip.cl"
		//　(BinaryPath) Example : { "../../Device 1/bitclip.obj", "../../Device 2/bitclip.obj", ... }
		general(_PL_ T08_)(const cl_context Context,TEXT_08 _PL_ _R_ BuildOption,TEXT_08 _PL_ _R_ SourcePath,TEXT_08 _PL_ _PL_ _R_ BinaryPath,FILE _PL_ _R_ Stream,oclc_ef _PL_ _R_ Error);
		//BitClip : Build a program as binary files with wide string paths.
		//＊(SourcePath) Example : L"../../Kernels/bitclip.cl"
		//　(BinaryPath) Example : { L"../../Device 1/bitclip.obj", L"../../Device 2/bitclip.obj", ... }
		general(_PL_ T16_)(const cl_context Context,TEXT_08 _PL_ _R_ BuildOption,TEXT_16 _PL_ _R_ SourcePath,TEXT_16 _PL_ _PL_ _R_ BinaryPath,FILE _PL_ _R_ Stream,oclc_ef _PL_ _R_ Error);
	}
	Build;

	//BitClip : Program Creation Functions - See also "OCLCL.PM.Delete_"
	//＊The number of binary paths must be same as the number of devices associated with the context.
	//＊(BuildOption) Example : "-I ../../Headers -I ../../Sources -D uBitC_R16_=0 -D uBitC_R64_=1"
	const struct
	{
		//BitClip : Load a program from binary files with narrow string paths. - Delete with "OCLCL.PM.Delete_"
		//＊(BinaryPath) Example : { "../../Device 1/bitclip.obj", "../../Device 2/bitclip.obj", ... }
		oclc_pm*(_PL_ T08_)(const cl_context Context,TEXT_08 _PL_ _R_ BuildOption,TEXT_08 _PL_ _PL_ _R_ BinaryPath,FILE _PL_ _R_ LogStream,oclc_ef _PL_ _R_ Error);
		//BitClip : Load a program from binary files with wide string paths. - Delete with "OCLCL.PM.Delete_"
		//＊(BinaryPath) Example : { L"../../Device 1/bitclip.obj", L"../../Device 2/bitclip.obj", ... }
		oclc_pm*(_PL_ T16_)(const cl_context Context,TEXT_08 _PL_ _R_ BuildOption,TEXT_16 _PL_ _PL_ _R_ BinaryPath,FILE _PL_ _R_ LogStream,oclc_ef _PL_ _R_ Error);
	}
	Create;

	//BitClip : Some Operations
	const struct
	{
		//BitClip : Pin Value Casting
		//＊Required (Buffer) size is 4×((DeviceAddressBits)÷8) bytes.
		//＊Return address is (Pin) for the same address bits between the host and the device, or (Buffer) otherwise.
		GENERAL*(_PL_ Pin_)(OCLC_MP _PL_ _R_ Pin,general _PL_ Buffer,ADDRESS DeviceAddressBits);

		//BitClip : Endian Flipping
		general(_PL_ Endian_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ Data,OCLC_MP _PL_ Amount,oclc_ef _PL_ _R_ Error);

		//BitClip : Array Reformation
		//＊SourceAmount->S[dim] == TargetAmount->S[ReformingAxis->S[dim]] where dim＝0, 1, 2, 3.
		//＊Source and Target's type sizes should be same.
		general(_PL_ Reform_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ Source,OCLC_MH _PL_ Target,OCLC_MP _PL_ SourceAmount,OCLC_MP _PL_ ReformingAxis,oclc_ef _PL_ _R_ Error);

		//BitClip : Type Casting Function
		general(_PL_ Caster_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutI,OCLC_MH _PL_ AboutO,OCLC_MP _PL_ AboutN,oclc_ef _PL_ _R_ Error);

		//BitClip : Bit Operation Function Set
		const struct
		{
			//BitClip : NOT Operation
			//＊C and A's type sizes should be same.
			general(_PL_ N_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,oclc_ef _PL_ _R_ Error);
			//BitClip : Shift Operation
			//＊C and A's types should be same.
			general(_PL_ S_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,INTEGER Shift,oclc_ef _PL_ _R_ Error);
			//BitClip : AND Operation
			//＊C and A's type sizes should be same.
			//＊Required (Mask) size is the type size of those to be calculated.
			general(_PL_ A_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Mask,oclc_ef _PL_ _R_ Error);
			//BitClip : AND Operation
			//＊C, A, and B's type sizes should be same.
			general(_PL_ A_2_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ _R_ Error);
			//BitClip : OR Operation
			//＊C and A's type sizes should be same.
			//＊Required (Mask) size is the type size of those to be calculated.
			general(_PL_ O_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Mask,oclc_ef _PL_ _R_ Error);
			//BitClip : OR Operation
			//＊C, A, and B's type sizes should be same.
			general(_PL_ O_2_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ _R_ Error);
			//BitClip : XOR Operation
			//＊C and A's type sizes should be same.
			//＊Required (Mask) size is the type size of those to be calculated.
			general(_PL_ X_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Mask,oclc_ef _PL_ _R_ Error);
			//BitClip : XOR Operation
			//＊C, A, and B's type sizes should be same.
			general(_PL_ X_2_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ _R_ Error);
		}
		BO;

		//BitClip : Relational Operation Function Set
		const struct
		{
			//BitClip : EQ Operation
			//＊C and A's type sizes should be same.
			//　C's type should be inte_xx.
			//＊Required (Value) size is the type size of those to be calculated.
			general(_PL_ E_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Value,oclc_ef _PL_ _R_ Error);
			//BitClip : EQ Operation
			//＊C, A, and B's type sizes should be same.
			//　C's type should be inte_xx.
			//　A and B's types should be same.
			general(_PL_ E_2_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ _R_ Error);
			//BitClip : NE Operation
			//＊C and A's type sizes should be same.
			//　C's type should be inte_xx.
			//＊Required (Value) size is the type size of those to be calculated.
			general(_PL_ N_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Value,oclc_ef _PL_ _R_ Error);
			//BitClip : NE Operation
			//＊C, A, and B's type sizes should be same.
			//　C's type should be inte_xx.
			//　A and B's types should be same.
			general(_PL_ N_2_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ _R_ Error);
			//BitClip : GE Operation
			//＊C and A's type sizes should be same.
			//　C's type should be inte_xx.
			//＊Required (Value) size is the type size of those to be calculated.
			general(_PL_ G_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Value,oclc_ef _PL_ _R_ Error);
			//BitClip : GE Operation
			//＊C, A, and B's type sizes should be same.
			//　C's type should be inte_xx.
			//　A and B's types should be same.
			general(_PL_ G_2_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ _R_ Error);
			//BitClip : LT Operation
			//＊C and A's type sizes should be same.
			//　C's type should be inte_xx.
			//＊Required (Value) size is the type size of those to be calculated.
			general(_PL_ L_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Value,oclc_ef _PL_ _R_ Error);
			//BitClip : LT Operation
			//＊C, A, and B's type sizes should be same.
			//　C's type should be inte_xx.
			//　A and B's types should be same.
			general(_PL_ L_2_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ _R_ Error);
		}
		RO;
	};
}
BITC_CL;

//BitClip : OpenCL Extension Object
extern BITC_CL BitCL,*BitCL_(general);
#else
//BitClip : Indirect access to the OpenCL extension object.
//＊If the library is not built with OpenCL settings,
//　then the return address will be just NULL.
extern GENERAL *BitCL_(general);
#endif
#endif
#endif
#endif
