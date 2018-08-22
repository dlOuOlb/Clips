/*------------------------------------------------------------------*/
/*	BitClip specifies the size of data types.						*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2018.08.22	*/
/*------------------------------------------------------------------*/
/*	OpenCL Support													*/
/*	http://www.khronos.org/opencl/									*/
/*------------------------------------------------------------------*/

#ifndef _INC_BITCLIP
#define _INC_BITCLIP	//BitClip : Header Declaration

#include <stdint.h>
#ifdef _CL
#include <CL\opencl.h>
#endif
#include <memclip.h>
#ifdef __OPENCL_H
#include <penclip.h>
#endif

#if(MemC_Fold_(Definition:Types))
MemC_Type_Rename_(uint8_t,data_08,DATA_08)	//BitClip : 8-bit Natural
MemC_Type_Rename_(uint16_t,data_16,DATA_16)	//BitClip : 16-bit Natural
MemC_Type_Rename_(uint32_t,data_32,DATA_32)	//BitClip : 32-bit Natural
MemC_Type_Rename_(uint64_t,data_64,DATA_64)	//BitClip : 64-bit Natural

MemC_Type_Rename_(int8_t,inte_08,INTE_08)	//BitClip : 8-bit Integer
MemC_Type_Rename_(int16_t,inte_16,INTE_16)	//BitClip : 16-bit Integer
MemC_Type_Rename_(int32_t,inte_32,INTE_32)	//BitClip : 32-bit Integer
MemC_Type_Rename_(int64_t,inte_64,INTE_64)	//BitClip : 64-bit Integer

MemC_Type_Rename_(float,real_32,REAL_32)	//BitClip : 32-bit Single Precision Floating Point
MemC_Type_Rename_(double,real_64,REAL_64)	//BitClip : 64-bit Double Precision Floating Point

enum _boolean	//BitClip : Boolean Enumeration
{
	BitCNull=0,	//BitClip : All Bits Off
	BitCFull=~0	//BitClip : All Bits On
};
MemC_Type_Declare_(enum,boolean,BOOLEAN);	//BitClip : Boolean Enumeration

union _bitclip			//BitClip : Pointer Union
{
	address A;			//BitClip : Address Container
	union _point_v		//BitClip : Variable Pointer Union
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
	V;					//BitClip : Access as Variable
	union _point_c		//BitClip : Constant Pointer Union
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
	C;					//BitClip : Access as Constant
};
MemC_Type_Declare_(union,bitclip,BITCLIP);	//BitClip : Pointer Union

enum _bitc_dt		//BitClip : Data Type Enumeration
{
	BitCTypeD08=0,	//BitClip : 8-bit Natural
	BitCTypeD16=1,	//BitClip : 16-bit Natural
	BitCTypeD32=2,	//BitClip : 32-bit Natural
	BitCTypeD64=3,	//BitClip : 64-bit Natural
	BitCTypeI08=4,	//BitClip : 8-bit Integer
	BitCTypeI16=5,	//BitClip : 16-bit Integer
	BitCTypeI32=6,	//BitClip : 32-bit Integer
	BitCTypeI64=7,	//BitClip : 64-bit Integer
	BitCTypeR08=8,	//BitClip : 8-bit Real (Not Available)
	BitCTypeR16=9,	//BitClip : 16-bit Real (Special Device Only)
	BitCTypeR32=10,	//BitClip : 32-bit Real
	BitCTypeR64=11,	//BitClip : 64-bit Real
	BitCTypes=12	//BitClip : The Number of Types
};
MemC_Type_Declare_(enum,bitc_dt,BITC_DT);	//BitClip : Data Type Enumeration

#ifdef __OPENCL_H
enum _bitc_ki				//BitC_CL : BitCKernel Indicator Enumeration
{
	BitCEndianD16=1,		//BitC_CL : BitC_Endian_D16_(_G_ data_16 *_R_ Data,_P_ DATA_32 Length)
	BitCEndianD32=2,		//BitC_CL : BitC_Endian_D32_(_G_ data_32 *_R_ Data,_P_ DATA_32 Length)
	BitCEndianD64=3,		//BitC_CL : BitC_Endian_D64_(_G_ data_64 *_R_ Data,_P_ DATA_32 Length)
	BitCCasterD08D16=5,		//BitC_CL : BitC_Caster_D08_D16_(_G_ DATA_08 *_R_ DataI,_G_ data_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD08D32=6,		//BitC_CL : BitC_Caster_D08_D32_(_G_ DATA_08 *_R_ DataI,_G_ data_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD08D64=7,		//BitC_CL : BitC_Caster_D08_D64_(_G_ DATA_08 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD08I08=8,		//BitC_CL : BitC_Caster_D08_I08_(_G_ DATA_08 *_R_ DataI,_G_ inte_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD08R16=13,	//BitC_CL : BitC_Caster_D08_R16_(_G_ DATA_08 *_R_ DataI,_G_ real_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD08R32=14,	//BitC_CL : BitC_Caster_D08_R32_(_G_ DATA_08 *_R_ DataI,_G_ real_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD08R64=15,	//BitC_CL : BitC_Caster_D08_R64_(_G_ DATA_08 *_R_ DataI,_G_ real_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD16D08=16,	//BitC_CL : BitC_Caster_D16_D08_(_G_ DATA_16 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD16D32=18,	//BitC_CL : BitC_Caster_D16_D32_(_G_ DATA_16 *_R_ DataI,_G_ data_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD16D64=19,	//BitC_CL : BitC_Caster_D16_D64_(_G_ DATA_16 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD16I08=20,	//BitC_CL : BitC_Caster_D16_I08_(_G_ DATA_16 *_R_ DataI,_G_ inte_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD16I16=21,	//BitC_CL : BitC_Caster_D16_I16_(_G_ DATA_16 *_R_ DataI,_G_ inte_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD16R16=25,	//BitC_CL : BitC_Caster_D16_R16_(_G_ DATA_16 *_R_ DataI,_G_ real_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD16R32=26,	//BitC_CL : BitC_Caster_D16_R32_(_G_ DATA_16 *_R_ DataI,_G_ real_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD16R64=27,	//BitC_CL : BitC_Caster_D16_R64_(_G_ DATA_16 *_R_ DataI,_G_ real_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD32D08=28,	//BitC_CL : BitC_Caster_D32_D08_(_G_ DATA_32 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD32D16=29,	//BitC_CL : BitC_Caster_D32_D16_(_G_ DATA_32 *_R_ DataI,_G_ data_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD32D64=31,	//BitC_CL : BitC_Caster_D32_D64_(_G_ DATA_32 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD32I08=32,	//BitC_CL : BitC_Caster_D32_I08_(_G_ DATA_32 *_R_ DataI,_G_ inte_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD32I16=33,	//BitC_CL : BitC_Caster_D32_I16_(_G_ DATA_32 *_R_ DataI,_G_ inte_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD32I32=34,	//BitC_CL : BitC_Caster_D32_I32_(_G_ DATA_32 *_R_ DataI,_G_ inte_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD32R16=37,	//BitC_CL : BitC_Caster_D32_R16_(_G_ DATA_32 *_R_ DataI,_G_ real_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD32R32=38,	//BitC_CL : BitC_Caster_D32_R32_(_G_ DATA_32 *_R_ DataI,_G_ real_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD32R64=39,	//BitC_CL : BitC_Caster_D32_R64_(_G_ DATA_32 *_R_ DataI,_G_ real_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD64D08=40,	//BitC_CL : BitC_Caster_D64_D08_(_G_ DATA_64 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD64D16=41,	//BitC_CL : BitC_Caster_D64_D16_(_G_ DATA_64 *_R_ DataI,_G_ data_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD64D32=42,	//BitC_CL : BitC_Caster_D64_D32_(_G_ DATA_64 *_R_ DataI,_G_ data_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD64I08=44,	//BitC_CL : BitC_Caster_D64_I08_(_G_ DATA_64 *_R_ DataI,_G_ inte_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD64I16=45,	//BitC_CL : BitC_Caster_D64_I16_(_G_ DATA_64 *_R_ DataI,_G_ inte_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD64I32=46,	//BitC_CL : BitC_Caster_D64_I32_(_G_ DATA_64 *_R_ DataI,_G_ inte_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD64I64=47,	//BitC_CL : BitC_Caster_D64_I64_(_G_ DATA_64 *_R_ DataI,_G_ inte_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD64R16=49,	//BitC_CL : BitC_Caster_D64_R16_(_G_ DATA_64 *_R_ DataI,_G_ real_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD64R32=50,	//BitC_CL : BitC_Caster_D64_R32_(_G_ DATA_64 *_R_ DataI,_G_ real_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterD64R64=51,	//BitC_CL : BitC_Caster_D64_R64_(_G_ DATA_64 *_R_ DataI,_G_ real_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI08D08=52,	//BitC_CL : BitC_Caster_I08_D08_(_G_ INTE_08 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI08D16=53,	//BitC_CL : BitC_Caster_I08_D16_(_G_ INTE_08 *_R_ DataI,_G_ data_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI08D32=54,	//BitC_CL : BitC_Caster_I08_D32_(_G_ INTE_08 *_R_ DataI,_G_ data_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI08D64=55,	//BitC_CL : BitC_Caster_I08_D64_(_G_ INTE_08 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI08I16=57,	//BitC_CL : BitC_Caster_I08_I16_(_G_ INTE_08 *_R_ DataI,_G_ inte_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI08I32=58,	//BitC_CL : BitC_Caster_I08_I32_(_G_ INTE_08 *_R_ DataI,_G_ inte_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI08I64=59,	//BitC_CL : BitC_Caster_I08_I64_(_G_ INTE_08 *_R_ DataI,_G_ inte_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI08R16=61,	//BitC_CL : BitC_Caster_I08_R16_(_G_ INTE_08 *_R_ DataI,_G_ real_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI08R32=62,	//BitC_CL : BitC_Caster_I08_R32_(_G_ INTE_08 *_R_ DataI,_G_ real_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI08R64=63,	//BitC_CL : BitC_Caster_I08_R64_(_G_ INTE_08 *_R_ DataI,_G_ real_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI16D08=64,	//BitC_CL : BitC_Caster_I16_D08_(_G_ INTE_16 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI16D16=65,	//BitC_CL : BitC_Caster_I16_D16_(_G_ INTE_16 *_R_ DataI,_G_ data_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI16D32=66,	//BitC_CL : BitC_Caster_I16_D32_(_G_ INTE_16 *_R_ DataI,_G_ data_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI16D64=67,	//BitC_CL : BitC_Caster_I16_D64_(_G_ INTE_16 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI16I08=68,	//BitC_CL : BitC_Caster_I16_I08_(_G_ INTE_16 *_R_ DataI,_G_ inte_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI16I32=70,	//BitC_CL : BitC_Caster_I16_I32_(_G_ INTE_16 *_R_ DataI,_G_ inte_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI16I64=71,	//BitC_CL : BitC_Caster_I16_I64_(_G_ INTE_16 *_R_ DataI,_G_ inte_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI16R16=73,	//BitC_CL : BitC_Caster_I16_R16_(_G_ INTE_16 *_R_ DataI,_G_ real_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI16R32=74,	//BitC_CL : BitC_Caster_I16_R32_(_G_ INTE_16 *_R_ DataI,_G_ real_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI16R64=75,	//BitC_CL : BitC_Caster_I16_R64_(_G_ INTE_16 *_R_ DataI,_G_ real_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI32D08=76,	//BitC_CL : BitC_Caster_I32_D08_(_G_ INTE_32 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI32D16=77,	//BitC_CL : BitC_Caster_I32_D16_(_G_ INTE_32 *_R_ DataI,_G_ data_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI32D32=78,	//BitC_CL : BitC_Caster_I32_D32_(_G_ INTE_32 *_R_ DataI,_G_ data_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI32D64=79,	//BitC_CL : BitC_Caster_I32_D64_(_G_ INTE_32 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI32I08=80,	//BitC_CL : BitC_Caster_I32_I08_(_G_ INTE_32 *_R_ DataI,_G_ inte_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI32I16=81,	//BitC_CL : BitC_Caster_I32_I16_(_G_ INTE_32 *_R_ DataI,_G_ inte_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI32I64=83,	//BitC_CL : BitC_Caster_I32_I64_(_G_ INTE_32 *_R_ DataI,_G_ inte_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI32R16=85,	//BitC_CL : BitC_Caster_I32_R16_(_G_ INTE_32 *_R_ DataI,_G_ real_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI32R32=86,	//BitC_CL : BitC_Caster_I32_R32_(_G_ INTE_32 *_R_ DataI,_G_ real_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI32R64=87,	//BitC_CL : BitC_Caster_I32_R64_(_G_ INTE_32 *_R_ DataI,_G_ real_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI64D08=88,	//BitC_CL : BitC_Caster_I64_D08_(_G_ INTE_64 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI64D16=89,	//BitC_CL : BitC_Caster_I64_D16_(_G_ INTE_64 *_R_ DataI,_G_ data_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI64D32=90,	//BitC_CL : BitC_Caster_I64_D32_(_G_ INTE_64 *_R_ DataI,_G_ data_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI64D64=91,	//BitC_CL : BitC_Caster_I64_D64_(_G_ INTE_64 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI64I08=92,	//BitC_CL : BitC_Caster_I64_I08_(_G_ INTE_64 *_R_ DataI,_G_ inte_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI64I16=93,	//BitC_CL : BitC_Caster_I64_I16_(_G_ INTE_64 *_R_ DataI,_G_ inte_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI64I32=94,	//BitC_CL : BitC_Caster_I64_I32_(_G_ INTE_64 *_R_ DataI,_G_ inte_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI64R16=97,	//BitC_CL : BitC_Caster_I64_R16_(_G_ INTE_64 *_R_ DataI,_G_ real_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI64R32=98,	//BitC_CL : BitC_Caster_I64_R32_(_G_ INTE_64 *_R_ DataI,_G_ real_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterI64R64=99,	//BitC_CL : BitC_Caster_I64_R64_(_G_ INTE_64 *_R_ DataI,_G_ real_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR16D08=112,	//BitC_CL : BitC_Caster_R16_D08_(_G_ REAL_16 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR16D16=113,	//BitC_CL : BitC_Caster_R16_D16_(_G_ REAL_16 *_R_ DataI,_G_ data_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR16D32=114,	//BitC_CL : BitC_Caster_R16_D32_(_G_ REAL_16 *_R_ DataI,_G_ data_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR16D64=115,	//BitC_CL : BitC_Caster_R16_D64_(_G_ REAL_16 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR16I08=116,	//BitC_CL : BitC_Caster_R16_I08_(_G_ REAL_16 *_R_ DataI,_G_ inte_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR16I16=117,	//BitC_CL : BitC_Caster_R16_I16_(_G_ REAL_16 *_R_ DataI,_G_ inte_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR16I32=118,	//BitC_CL : BitC_Caster_R16_I32_(_G_ REAL_16 *_R_ DataI,_G_ inte_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR16I64=119,	//BitC_CL : BitC_Caster_R16_I64_(_G_ REAL_16 *_R_ DataI,_G_ inte_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR16R32=122,	//BitC_CL : BitC_Caster_R16_R32_(_G_ REAL_16 *_R_ DataI,_G_ real_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR16R64=123,	//BitC_CL : BitC_Caster_R16_R64_(_G_ REAL_16 *_R_ DataI,_G_ real_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR32D08=124,	//BitC_CL : BitC_Caster_R32_D08_(_G_ REAL_32 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR32D16=125,	//BitC_CL : BitC_Caster_R32_D16_(_G_ REAL_32 *_R_ DataI,_G_ data_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR32D32=126,	//BitC_CL : BitC_Caster_R32_D32_(_G_ REAL_32 *_R_ DataI,_G_ data_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR32D64=127,	//BitC_CL : BitC_Caster_R32_D64_(_G_ REAL_32 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR32I08=128,	//BitC_CL : BitC_Caster_R32_I08_(_G_ REAL_32 *_R_ DataI,_G_ inte_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR32I16=129,	//BitC_CL : BitC_Caster_R32_I16_(_G_ REAL_32 *_R_ DataI,_G_ inte_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR32I32=130,	//BitC_CL : BitC_Caster_R32_I32_(_G_ REAL_32 *_R_ DataI,_G_ inte_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR32I64=131,	//BitC_CL : BitC_Caster_R32_I64_(_G_ REAL_32 *_R_ DataI,_G_ inte_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR32R16=133,	//BitC_CL : BitC_Caster_R32_R16_(_G_ REAL_32 *_R_ DataI,_G_ real_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR32R64=135,	//BitC_CL : BitC_Caster_R32_R64_(_G_ REAL_32 *_R_ DataI,_G_ real_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR64D08=136,	//BitC_CL : BitC_Caster_R64_D08_(_G_ REAL_64 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR64D16=137,	//BitC_CL : BitC_Caster_R64_D16_(_G_ REAL_64 *_R_ DataI,_G_ data_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR64D32=138,	//BitC_CL : BitC_Caster_R64_D32_(_G_ REAL_64 *_R_ DataI,_G_ data_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR64D64=139,	//BitC_CL : BitC_Caster_R64_D64_(_G_ REAL_64 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR64I08=140,	//BitC_CL : BitC_Caster_R64_I08_(_G_ REAL_64 *_R_ DataI,_G_ inte_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR64I16=141,	//BitC_CL : BitC_Caster_R64_I16_(_G_ REAL_64 *_R_ DataI,_G_ inte_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR64I32=142,	//BitC_CL : BitC_Caster_R64_I32_(_G_ REAL_64 *_R_ DataI,_G_ inte_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR64I64=143,	//BitC_CL : BitC_Caster_R64_I64_(_G_ REAL_64 *_R_ DataI,_G_ inte_64 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR64R16=145,	//BitC_CL : BitC_Caster_R64_R16_(_G_ REAL_64 *_R_ DataI,_G_ real_16 *_R_ DataO,_P_ DATA_32 Length)
	BitCCasterR64R32=146,	//BitC_CL : BitC_Caster_R64_R32_(_G_ REAL_64 *_R_ DataI,_G_ real_32 *_R_ DataO,_P_ DATA_32 Length)
	BitCBON1D08=148,		//BitC_CL : BitC_BO_N_1_D08_(_G_ data_08 _PL_ DataC,_G_ DATA_08 _PL_ DataA,_P_ DATA_32 Length)
	BitCBOA2D08=149,		//BitC_CL : BitC_BO_S_1_D08_(_G_ data_08 *DataC,_G_ DATA_08 *DataA,_P_ inte_32 Shift,_P_ DATA_32 Length)
	BitCBOO2D08=150,		//BitC_CL : BitC_BO_S_1_D16_(_G_ data_16 *DataC,_G_ DATA_16 *DataA,_P_ inte_32 Shift,_P_ DATA_32 Length)
	BitCBOX2D08=151,		//BitC_CL : BitC_BO_S_1_D32_(_G_ data_32 *DataC,_G_ DATA_32 *DataA,_P_ inte_32 Shift,_P_ DATA_32 Length)
	BitCBOA1D08=152,		//BitC_CL : BitC_BO_S_1_D64_(_G_ data_64 *DataC,_G_ DATA_64 *DataA,_P_ inte_32 Shift,_P_ DATA_32 Length)
	BitCBOA1D16=153,		//BitC_CL : BitC_BO_S_1_I08_(_G_ inte_08 *DataC,_G_ INTE_08 *DataA,_P_ inte_32 Shift,_P_ DATA_32 Length)
	BitCBOA1D32=154,		//BitC_CL : BitC_BO_S_1_I16_(_G_ inte_16 *DataC,_G_ INTE_16 *DataA,_P_ inte_32 Shift,_P_ DATA_32 Length)
	BitCBOA1D64=155,		//BitC_CL : BitC_BO_S_1_I32_(_G_ inte_32 *DataC,_G_ INTE_32 *DataA,_P_ inte_32 Shift,_P_ DATA_32 Length)
	BitCBOO1D08=156,		//BitC_CL : BitC_BO_S_1_I64_(_G_ inte_64 *DataC,_G_ INTE_64 *DataA,_P_ inte_32 Shift,_P_ DATA_32 Length)
	BitCBOO1D16=157,		//BitC_CL : BitC_BO_A_1_D08_(_G_ data_08* DataC,_G_ DATA_08* DataA,_P_ DATA_08 Mask,_P_ DATA_32 Length)
	BitCBOO1D32=158,		//BitC_CL : BitC_BO_A_1_D16_(_G_ data_16* DataC,_G_ DATA_16* DataA,_P_ DATA_16 Mask,_P_ DATA_32 Length)
	BitCBOO1D64=159,		//BitC_CL : BitC_BO_A_1_D32_(_G_ data_32* DataC,_G_ DATA_32* DataA,_P_ DATA_32 Mask,_P_ DATA_32 Length)
	BitCBOX1D08=160,		//BitC_CL : BitC_BO_A_1_D64_(_G_ data_64* DataC,_G_ DATA_64* DataA,_P_ DATA_64 Mask,_P_ DATA_32 Length)
	BitCBOX1D16=161,		//BitC_CL : BitC_BO_A_2_D08_(_G_ data_08 _PL_ DataC,_G_ DATA_08 _PL_ DataA,_G_ DATA_08 _PL_ DataB,_P_ DATA_32 Length)
	BitCBOX1D32=162,		//BitC_CL : BitC_BO_O_1_D08_(_G_ data_08* DataC,_G_ DATA_08* DataA,_P_ DATA_08 Mask,_P_ DATA_32 Length)
	BitCBOX1D64=163,		//BitC_CL : BitC_BO_O_1_D16_(_G_ data_16* DataC,_G_ DATA_16* DataA,_P_ DATA_16 Mask,_P_ DATA_32 Length)
	BitCBOS1D08=164,		//BitC_CL : BitC_BO_O_1_D32_(_G_ data_32* DataC,_G_ DATA_32* DataA,_P_ DATA_32 Mask,_P_ DATA_32 Length)
	BitCBOS1D16=165,		//BitC_CL : BitC_BO_O_1_D64_(_G_ data_64* DataC,_G_ DATA_64* DataA,_P_ DATA_64 Mask,_P_ DATA_32 Length)
	BitCBOS1D32=166,		//BitC_CL : BitC_BO_O_2_D08_(_G_ data_08 _PL_ DataC,_G_ DATA_08 _PL_ DataA,_G_ DATA_08 _PL_ DataB,_P_ DATA_32 Length)
	BitCBOS1D64=167,		//BitC_CL : BitC_BO_X_1_D08_(_G_ data_08* DataC,_G_ DATA_08* DataA,_P_ DATA_08 Mask,_P_ DATA_32 Length)
	BitCBOS1I08=168,		//BitC_CL : BitC_BO_X_1_D16_(_G_ data_16* DataC,_G_ DATA_16* DataA,_P_ DATA_16 Mask,_P_ DATA_32 Length)
	BitCBOS1I16=169,		//BitC_CL : BitC_BO_X_1_D32_(_G_ data_32* DataC,_G_ DATA_32* DataA,_P_ DATA_32 Mask,_P_ DATA_32 Length)
	BitCBOS1I32=170,		//BitC_CL : BitC_BO_X_1_D64_(_G_ data_64* DataC,_G_ DATA_64* DataA,_P_ DATA_64 Mask,_P_ DATA_32 Length)
	BitCBOS1I64=171,		//BitC_CL : BitC_BO_X_2_D08_(_G_ data_08 _PL_ DataC,_G_ DATA_08 _PL_ DataA,_G_ DATA_08 _PL_ DataB,_P_ DATA_32 Length)
	BitCExpandD08=172,		//BitC_CL : BitC_Expand_D08_(_G_ DATA_08 _PL_ _R_ DataI,_G_ data_08 _PL_ _R_ DataO,_P_ DATA_32 Length)
	BitCExpandD16=173,		//BitC_CL : BitC_Expand_D16_(_G_ DATA_08 _PL_ _R_ DataI,_G_ data_16 _PL_ _R_ DataO,_P_ DATA_32 Length)
	BitCExpandD32=174,		//BitC_CL : BitC_Expand_D32_(_G_ DATA_08 _PL_ _R_ DataI,_G_ data_32 _PL_ _R_ DataO,_P_ DATA_32 Length)
	BitCExpandD64=175,		//BitC_CL : BitC_Expand_D64_(_G_ DATA_08 _PL_ _R_ DataI,_G_ data_64 _PL_ _R_ DataO,_P_ DATA_32 Length)
	BitCShrinkD08=176,		//BitC_CL : BitC_Shrink_D08_(_G_ DATA_08 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCShrinkD16=177,		//BitC_CL : BitC_Shrink_D16_(_G_ DATA_16 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCShrinkD32=178,		//BitC_CL : BitC_Shrink_D32_(_G_ DATA_32 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCShrinkD64=179,		//BitC_CL : BitC_Shrink_D64_(_G_ DATA_64 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
	BitCROE1D08=180,		//BitC_CL : BitC_RO_E_1_D08_(_G_ data_08 *_R_ DataC,_G_ DATA_08 *_R_ DataA,_P_ DATA_08 Value,_P_ DATA_32 Length)
	BitCROE1D16=181,		//BitC_CL : BitC_RO_E_1_D16_(_G_ data_08 *_R_ DataC,_G_ DATA_16 *_R_ DataA,_P_ DATA_16 Value,_P_ DATA_32 Length)
	BitCROE1D32=182,		//BitC_CL : BitC_RO_E_1_D32_(_G_ data_08 *_R_ DataC,_G_ DATA_32 *_R_ DataA,_P_ DATA_32 Value,_P_ DATA_32 Length)
	BitCROE1D64=183,		//BitC_CL : BitC_RO_E_1_D64_(_G_ data_08 *_R_ DataC,_G_ DATA_64 *_R_ DataA,_P_ DATA_64 Value,_P_ DATA_32 Length)
	BitCRON1D08=184,		//BitC_CL : BitC_RO_E_2_D08_(_G_ data_08 *_R_ DataC,_G_ DATA_08 *_R_ DataA,_G_ DATA_08 *_R_ DataB,_P_ DATA_32 Length)
	BitCRON1D16=185,		//BitC_CL : BitC_RO_E_2_D16_(_G_ data_08 *_R_ DataC,_G_ DATA_16 *_R_ DataA,_G_ DATA_16 *_R_ DataB,_P_ DATA_32 Length)
	BitCRON1D32=186,		//BitC_CL : BitC_RO_E_2_D32_(_G_ data_08 *_R_ DataC,_G_ DATA_32 *_R_ DataA,_G_ DATA_32 *_R_ DataB,_P_ DATA_32 Length)
	BitCRON1D64=187,		//BitC_CL : BitC_RO_E_2_D64_(_G_ data_08 *_R_ DataC,_G_ DATA_64 *_R_ DataA,_G_ DATA_64 *_R_ DataB,_P_ DATA_32 Length)
	BitCROG1D08=188,		//BitC_CL : BitC_RO_N_1_D08_(_G_ data_08 *_R_ DataC,_G_ DATA_08 *_R_ DataA,_P_ DATA_08 Value,_P_ DATA_32 Length)
	BitCROG1D16=189,		//BitC_CL : BitC_RO_N_1_D16_(_G_ data_08 *_R_ DataC,_G_ DATA_16 *_R_ DataA,_P_ DATA_16 Value,_P_ DATA_32 Length)
	BitCROG1D32=190,		//BitC_CL : BitC_RO_N_1_D32_(_G_ data_08 *_R_ DataC,_G_ DATA_32 *_R_ DataA,_P_ DATA_32 Value,_P_ DATA_32 Length)
	BitCROG1D64=191,		//BitC_CL : BitC_RO_N_1_D64_(_G_ data_08 *_R_ DataC,_G_ DATA_64 *_R_ DataA,_P_ DATA_64 Value,_P_ DATA_32 Length)
	BitCROG1I08=192,		//BitC_CL : BitC_RO_N_2_D08_(_G_ data_08 *_R_ DataC,_G_ DATA_08 *_R_ DataA,_G_ DATA_08 *_R_ DataB,_P_ DATA_32 Length)
	BitCROG1I16=193,		//BitC_CL : BitC_RO_N_2_D16_(_G_ data_08 *_R_ DataC,_G_ DATA_16 *_R_ DataA,_G_ DATA_16 *_R_ DataB,_P_ DATA_32 Length)
	BitCROG1I32=194,		//BitC_CL : BitC_RO_N_2_D32_(_G_ data_08 *_R_ DataC,_G_ DATA_32 *_R_ DataA,_G_ DATA_32 *_R_ DataB,_P_ DATA_32 Length)
	BitCROG1I64=195,		//BitC_CL : BitC_RO_N_2_D64_(_G_ data_08 *_R_ DataC,_G_ DATA_64 *_R_ DataA,_G_ DATA_64 *_R_ DataB,_P_ DATA_32 Length)
	BitCROG1R16=197,		//BitC_CL : BitC_RO_G_1_D08_(_G_ data_08 *_R_ DataC,_G_ DATA_08 *_R_ DataA,_P_ DATA_08 Value,_P_ DATA_32 Length)
	BitCROG1R32=198,		//BitC_CL : BitC_RO_G_1_D16_(_G_ data_08 *_R_ DataC,_G_ DATA_16 *_R_ DataA,_P_ DATA_16 Value,_P_ DATA_32 Length)
	BitCROG1R64=199,		//BitC_CL : BitC_RO_G_1_D32_(_G_ data_08 *_R_ DataC,_G_ DATA_32 *_R_ DataA,_P_ DATA_32 Value,_P_ DATA_32 Length)
	BitCROL1D08=200,		//BitC_CL : BitC_RO_G_1_D64_(_G_ data_08 *_R_ DataC,_G_ DATA_64 *_R_ DataA,_P_ DATA_64 Value,_P_ DATA_32 Length)
	BitCROL1D16=201,		//BitC_CL : BitC_RO_G_1_I08_(_G_ data_08 *_R_ DataC,_G_ INTE_08 *_R_ DataA,_P_ INTE_08 Value,_P_ DATA_32 Length)
	BitCROL1D32=202,		//BitC_CL : BitC_RO_G_1_I16_(_G_ data_08 *_R_ DataC,_G_ INTE_16 *_R_ DataA,_P_ INTE_16 Value,_P_ DATA_32 Length)
	BitCROL1D64=203,		//BitC_CL : BitC_RO_G_1_I32_(_G_ data_08 *_R_ DataC,_G_ INTE_32 *_R_ DataA,_P_ INTE_32 Value,_P_ DATA_32 Length)
	BitCROL1I08=204,		//BitC_CL : BitC_RO_G_1_I64_(_G_ data_08 *_R_ DataC,_G_ INTE_64 *_R_ DataA,_P_ INTE_64 Value,_P_ DATA_32 Length)
	BitCROL1I16=205,		//BitC_CL : BitC_RO_G_1_R16_(_G_ data_08 *_R_ DataC,_G_ REAL_16 *_R_ DataA,_P_ DATA_16 Value,_P_ DATA_32 Length)
	BitCROL1I32=206,		//BitC_CL : BitC_RO_G_1_R32_(_G_ data_08 *_R_ DataC,_G_ REAL_32 *_R_ DataA,_P_ REAL_32 Value,_P_ DATA_32 Length)
	BitCROL1I64=207,		//BitC_CL : BitC_RO_G_1_R64_(_G_ data_08 *_R_ DataC,_G_ REAL_64 *_R_ DataA,_P_ REAL_64 Value,_P_ DATA_32 Length)
	BitCROL1R16=209,		//BitC_CL : BitC_RO_G_2_D08_(_G_ data_08 *_R_ DataC,_G_ DATA_08 *_R_ DataA,_G_ DATA_08 *_R_ DataB,_P_ DATA_32 Length)
	BitCROL1R32=210,		//BitC_CL : BitC_RO_G_2_D16_(_G_ data_08 *_R_ DataC,_G_ DATA_16 *_R_ DataA,_G_ DATA_16 *_R_ DataB,_P_ DATA_32 Length)
	BitCROL1R64=211,		//BitC_CL : BitC_RO_G_2_D32_(_G_ data_08 *_R_ DataC,_G_ DATA_32 *_R_ DataA,_G_ DATA_32 *_R_ DataB,_P_ DATA_32 Length)
	BitCROE2D08=212,		//BitC_CL : BitC_RO_G_2_D64_(_G_ data_08 *_R_ DataC,_G_ DATA_64 *_R_ DataA,_G_ DATA_64 *_R_ DataB,_P_ DATA_32 Length)
	BitCROE2D16=213,		//BitC_CL : BitC_RO_G_2_I08_(_G_ data_08 *_R_ DataC,_G_ INTE_08 *_R_ DataA,_G_ INTE_08 *_R_ DataB,_P_ DATA_32 Length)
	BitCROE2D32=214,		//BitC_CL : BitC_RO_G_2_I16_(_G_ data_08 *_R_ DataC,_G_ INTE_16 *_R_ DataA,_G_ INTE_16 *_R_ DataB,_P_ DATA_32 Length)
	BitCROE2D64=215,		//BitC_CL : BitC_RO_G_2_I32_(_G_ data_08 *_R_ DataC,_G_ INTE_32 *_R_ DataA,_G_ INTE_32 *_R_ DataB,_P_ DATA_32 Length)
	BitCRON2D08=216,		//BitC_CL : BitC_RO_G_2_I64_(_G_ data_08 *_R_ DataC,_G_ INTE_64 *_R_ DataA,_G_ INTE_64 *_R_ DataB,_P_ DATA_32 Length)
	BitCRON2D16=217,		//BitC_CL : BitC_RO_G_2_R16_(_G_ data_08 *_R_ DataC,_G_ REAL_16 *_R_ DataA,_G_ REAL_16 *_R_ DataB,_P_ DATA_32 Length)
	BitCRON2D32=218,		//BitC_CL : BitC_RO_G_2_R32_(_G_ data_08 *_R_ DataC,_G_ REAL_32 *_R_ DataA,_G_ REAL_32 *_R_ DataB,_P_ DATA_32 Length)
	BitCRON2D64=219,		//BitC_CL : BitC_RO_G_2_R64_(_G_ data_08 *_R_ DataC,_G_ REAL_64 *_R_ DataA,_G_ REAL_64 *_R_ DataB,_P_ DATA_32 Length)
	BitCROG2D08=220,		//BitC_CL : BitC_RO_L_1_D08_(_G_ data_08 *_R_ DataC,_G_ DATA_08 *_R_ DataA,_P_ DATA_08 Value,_P_ DATA_32 Length)
	BitCROG2D16=221,		//BitC_CL : BitC_RO_L_1_D16_(_G_ data_08 *_R_ DataC,_G_ DATA_16 *_R_ DataA,_P_ DATA_16 Value,_P_ DATA_32 Length)
	BitCROG2D32=222,		//BitC_CL : BitC_RO_L_1_D32_(_G_ data_08 *_R_ DataC,_G_ DATA_32 *_R_ DataA,_P_ DATA_32 Value,_P_ DATA_32 Length)
	BitCROG2D64=223,		//BitC_CL : BitC_RO_L_1_D64_(_G_ data_08 *_R_ DataC,_G_ DATA_64 *_R_ DataA,_P_ DATA_64 Value,_P_ DATA_32 Length)
	BitCROG2I08=224,		//BitC_CL : BitC_RO_L_1_I08_(_G_ data_08 *_R_ DataC,_G_ INTE_08 *_R_ DataA,_P_ INTE_08 Value,_P_ DATA_32 Length)
	BitCROG2I16=225,		//BitC_CL : BitC_RO_L_1_I16_(_G_ data_08 *_R_ DataC,_G_ INTE_16 *_R_ DataA,_P_ INTE_16 Value,_P_ DATA_32 Length)
	BitCROG2I32=226,		//BitC_CL : BitC_RO_L_1_I32_(_G_ data_08 *_R_ DataC,_G_ INTE_32 *_R_ DataA,_P_ INTE_32 Value,_P_ DATA_32 Length)
	BitCROG2I64=227,		//BitC_CL : BitC_RO_L_1_I64_(_G_ data_08 *_R_ DataC,_G_ INTE_64 *_R_ DataA,_P_ INTE_64 Value,_P_ DATA_32 Length)
	BitCROG2R16=229,		//BitC_CL : BitC_RO_L_1_R16_(_G_ data_08 *_R_ DataC,_G_ REAL_16 *_R_ DataA,_P_ DATA_16 Value,_P_ DATA_32 Length)
	BitCROG2R32=230,		//BitC_CL : BitC_RO_L_1_R32_(_G_ data_08 *_R_ DataC,_G_ REAL_32 *_R_ DataA,_P_ REAL_32 Value,_P_ DATA_32 Length)
	BitCROG2R64=231,		//BitC_CL : BitC_RO_L_1_R64_(_G_ data_08 *_R_ DataC,_G_ REAL_64 *_R_ DataA,_P_ REAL_64 Value,_P_ DATA_32 Length)
	BitCROL2D08=232,		//BitC_CL : BitC_RO_L_2_D08_(_G_ data_08 *_R_ DataC,_G_ DATA_08 *_R_ DataA,_G_ DATA_08 *_R_ DataB,_P_ DATA_32 Length)
	BitCROL2D16=233,		//BitC_CL : BitC_RO_L_2_D16_(_G_ data_08 *_R_ DataC,_G_ DATA_16 *_R_ DataA,_G_ DATA_16 *_R_ DataB,_P_ DATA_32 Length)
	BitCROL2D32=234,		//BitC_CL : BitC_RO_L_2_D32_(_G_ data_08 *_R_ DataC,_G_ DATA_32 *_R_ DataA,_G_ DATA_32 *_R_ DataB,_P_ DATA_32 Length)
	BitCROL2D64=235,		//BitC_CL : BitC_RO_L_2_D64_(_G_ data_08 *_R_ DataC,_G_ DATA_64 *_R_ DataA,_G_ DATA_64 *_R_ DataB,_P_ DATA_32 Length)
	BitCROL2I08=236,		//BitC_CL : BitC_RO_L_2_I08_(_G_ data_08 *_R_ DataC,_G_ INTE_08 *_R_ DataA,_G_ INTE_08 *_R_ DataB,_P_ DATA_32 Length)
	BitCROL2I16=237,		//BitC_CL : BitC_RO_L_2_I16_(_G_ data_08 *_R_ DataC,_G_ INTE_16 *_R_ DataA,_G_ INTE_16 *_R_ DataB,_P_ DATA_32 Length)
	BitCROL2I32=238,		//BitC_CL : BitC_RO_L_2_I32_(_G_ data_08 *_R_ DataC,_G_ INTE_32 *_R_ DataA,_G_ INTE_32 *_R_ DataB,_P_ DATA_32 Length)
	BitCROL2I64=239,		//BitC_CL : BitC_RO_L_2_I64_(_G_ data_08 *_R_ DataC,_G_ INTE_64 *_R_ DataA,_G_ INTE_64 *_R_ DataB,_P_ DATA_32 Length)
	BitCROL2R16=241,		//BitC_CL : BitC_RO_L_2_R16_(_G_ data_08 *_R_ DataC,_G_ REAL_16 *_R_ DataA,_G_ REAL_16 *_R_ DataB,_P_ DATA_32 Length)
	BitCROL2R32=242,		//BitC_CL : BitC_RO_L_2_R32_(_G_ data_08 *_R_ DataC,_G_ REAL_32 *_R_ DataA,_G_ REAL_32 *_R_ DataB,_P_ DATA_32 Length)
	BitCROL2R64=243,		//BitC_CL : BitC_RO_L_2_R64_(_G_ data_08 *_R_ DataC,_G_ REAL_64 *_R_ DataA,_G_ REAL_64 *_R_ DataB,_P_ DATA_32 Length)

	//BitC_CL : BitC_Reform_D08_(_G_ DATA_08 _PL_ Source,_G_ data_08 _PL_ Target,_C_ DATA_32 _PL_ Parameter)
	//＊Pass arguments as
	//　{ &(cl_mem)(SourceArray), &(cl_mem)(TargetArray), &(cl_mem)(Buffer), &(data_32*)(SourceShape), &(data_32*)(ReformingAxis), &(data_32)(Dimensions) }
	//＊Required (Buffer) size is (((Devi_Copy_Max_Dimension)×2)＋2)×4 bytes.
	BitCReformD08=244,
	//BitC_CL : BitC_Reform_D08_(_G_ DATA_08 _PL_ Source,_G_ data_08 _PL_ Target,_C_ DATA_32 _PL_ Parameter)
	//＊Pass arguments as
	//　{ &(cl_mem)(SourceArray), &(cl_mem)(TargetArray), &(cl_mem)(Buffer), &(data_32*)(SourceShape), &(data_32*)(ReformingAxis), &(data_32)(Dimensions) }
	//＊Required (Buffer) size is (((Devi_Copy_Max_Dimension)×2)＋2)×4 bytes.
	BitCReformD16=245,
	//BitC_CL : BitC_Reform_D08_(_G_ DATA_08 _PL_ Source,_G_ data_08 _PL_ Target,_C_ DATA_32 _PL_ Parameter)
	//＊Pass arguments as
	//　{ &(cl_mem)(SourceArray), &(cl_mem)(TargetArray), &(cl_mem)(Buffer), &(data_32*)(SourceShape), &(data_32*)(ReformingAxis), &(data_32)(Dimensions) }
	//＊Required (Buffer) size is (((Devi_Copy_Max_Dimension)×2)＋2)×4 bytes.
	BitCReformD32=246,
	//BitC_CL : BitC_Reform_D08_(_G_ DATA_08 _PL_ Source,_G_ data_08 _PL_ Target,_C_ DATA_32 _PL_ Parameter)
	//＊Pass arguments as
	//　{ &(cl_mem)(SourceArray), &(cl_mem)(TargetArray), &(cl_mem)(Buffer), &(data_32*)(SourceShape), &(data_32*)(ReformingAxis), &(data_32)(Dimensions) }
	//＊Required (Buffer) size is (((Devi_Copy_Max_Dimension)×2)＋2)×4 bytes.
	BitCReformD64=247,

	BitCKernels=248			//BitC_CL : The Number of Kernels
};
MemC_Type_Declare_(enum,bitc_ki,BITC_KI);	//BitC_CL : BitCKernel Indicator Enumeration

struct _bitc_cl					//BitC_CL : Kernel Manager Set Structure
{
	PENC_CL _PL_ Helper;		//BitC_CL : Program Resource
	DEVI_KM _PL_ _PL_ KMSet;	//BitC_CL : Kernel Manager Set
};
MemC_Type_Declare_(struct,bitc_cl,BITC_CL);	//BitC_CL : Kernel Manager Set Structure
#endif
#endif

#if(MemC_Fold_(Preprocessing))
static_assert((-1)==(((inte_08)(-1))>>1),"The bit-shift-right operation of a signed integer must preserve the sign.");
static_assert((-1)!=(((data_08)(-1))>>1),"The bit-shift-right operation of an unsigned integer must not preserve the sign.");
static_assert((~((address)(0)))==((address)((inte_08)(~0))),"Casting from a signed integer to an address value must preserve the sign.");
static_assert((~((address)(1)))==((address)((inte_08)(~1))),"Casting from a signed integer to an address value must preserve the sign.");
static_assert(sizeof(data_32)<=sizeof(address),"The size of an address value must be equal to or larger than 32 bits.");
#endif

#if(MemC_Fold_(Definition:Macros))
#if(MemC_Fold_(Part:BitC_Max_T##_))
#define BitC_Max_I08_(Output,InputA,InputB) {(Output)=(InputB)-(InputA);(Output)&=(Acs_(inte_08,Output)>>7);(Output)=(InputB)-(Output);}				//BitClip : Maximum of 8-bit Integer - Only valid for Data Range under 0x40
#define BitC_Max_I16_(Output,InputA,InputB) {(Output)=(InputB)-(InputA);(Output)&=(Acs_(inte_16,Output)>>15);(Output)=(InputB)-(Output);}				//BitClip : Maximum of 16-bit Integer - Only valid for Data Range under 0x4000
#define BitC_Max_I32_(Output,InputA,InputB) {(Output)=(InputB)-(InputA);(Output)&=(Acs_(inte_32,Output)>>31);(Output)=(InputB)-(Output);}				//BitClip : Maximum of 32-bit Integer - Only valid for Data Range under 0x40000000
#define BitC_Max_I64_(Output,InputA,InputB) {(Output)=(InputB)-(InputA);(Output)&=(Acs_(inte_64,Output)>>63);(Output)=(InputB)-(Output);}				//BitClip : Maximum of 64-bit Integer - Only valid for Data Range under 0x4000000000000000
#define BitC_Max_R32_(Output,InputA,InputB) {(Output)=(InputB)-(InputA);Acs_(inte_32,Output)&=(Acs_(inte_32,Output)>>31);(Output)=(InputB)-(Output);}	//BitClip : Maximum of 32-bit Real
#define BitC_Max_R64_(Output,InputA,InputB) {(Output)=(InputB)-(InputA);Acs_(inte_64,Output)&=(Acs_(inte_64,Output)>>63);(Output)=(InputB)-(Output);}	//BitClip : Maximum of 64-bit Real
#endif
#if(MemC_Fold_(Part:BitC_Min_T##_))
#define BitC_Min_I08_(Output,InputA,InputB) {(Output)=(InputA)-(InputB);(Output)&=(Acs_(inte_08,Output)>>7);(Output)+=(InputB);}				//BitClip : Minimum of 8-bit Integer - Only valid for Data Range under 0x40
#define BitC_Min_I16_(Output,InputA,InputB) {(Output)=(InputA)-(InputB);(Output)&=(Acs_(inte_16,Output)>>15);(Output)+=(InputB);}				//BitClip : Minimum of 16-bit Integer - Only valid for Data Range under 0x4000
#define BitC_Min_I32_(Output,InputA,InputB) {(Output)=(InputA)-(InputB);(Output)&=(Acs_(inte_32,Output)>>31);(Output)+=(InputB);}				//BitClip : Minimum of 32-bit Integer - Only valid for Data Range under 0x40000000
#define BitC_Min_I64_(Output,InputA,InputB) {(Output)=(InputA)-(InputB);(Output)&=(Acs_(inte_64,Output)>>63);(Output)+=(InputB);}				//BitClip : Minimum of 64-bit Integer - Only valid for Data Range under 0x4000000000000000
#define BitC_Min_R32_(Output,InputA,InputB) {(Output)=(InputA)-(InputB);Acs_(inte_32,Output)&=(Acs_(inte_32,Output)>>31);(Output)+=(InputB);}	//BitClip : Minimum of 32-bit Real
#define BitC_Min_R64_(Output,InputA,InputB) {(Output)=(InputA)-(InputB);Acs_(inte_64,Output)&=(Acs_(inte_64,Output)>>63);(Output)+=(InputB);}	//BitClip : Minimum of 64-bit Real
#endif
#if(MemC_Fold_(Part:BitC_Abs_P_T##_))
#define BitC_Abs_P_I08_(Output,Input) {(Output)=Acs_(inte_08,Input)>>7;(Output)^=((Input)+(Output));}	//BitClip : Positive Absolute of 8-bit Integer
#define BitC_Abs_P_I16_(Output,Input) {(Output)=Acs_(inte_16,Input)>>15;(Output)^=((Input)+(Output));}	//BitClip : Positive Absolute of 16-bit Integer
#define BitC_Abs_P_I32_(Output,Input) {(Output)=Acs_(inte_32,Input)>>31;(Output)^=((Input)+(Output));}	//BitClip : Positive Absolute of 32-bit Integer
#define BitC_Abs_P_I64_(Output,Input) {(Output)=Acs_(inte_64,Input)>>63;(Output)^=((Input)+(Output));}	//BitClip : Positive Absolute of 64-bit Integer
#define BitC_Abs_P_R32_(Output,Input) {Acs_(inte_32,Output)=Acs_(inte_32,Input)&0x7FFFFFFF;}			//BitClip : Positive Absolute of 32-bit Real
#define BitC_Abs_P_R64_(Output,Input) {Acs_(inte_64,Output)=Acs_(inte_64,Input)&0x7FFFFFFFFFFFFFFF;}	//BitClip : Positive Absolute of 64-bit Real
#endif
#if(MemC_Fold_(Part:BitC_Abs_N_T##_))
#define BitC_Abs_N_I08_(Output,Input) {(Output)=Acs_(inte_08,Input)>>7;(Output)=~(Output);(Output)^=((Input)+(Output));}	//BitClip : Negative Absolute of 8-bit Integer
#define BitC_Abs_N_I16_(Output,Input) {(Output)=Acs_(inte_16,Input)>>15;(Output)=~(Output);(Output)^=((Input)+(Output));}	//BitClip : Negative Absolute of 16-bit Integer
#define BitC_Abs_N_I32_(Output,Input) {(Output)=Acs_(inte_32,Input)>>31;(Output)=~(Output);(Output)^=((Input)+(Output));}	//BitClip : Negative Absolute of 32-bit Integer
#define BitC_Abs_N_I64_(Output,Input) {(Output)=Acs_(inte_64,Input)>>63;(Output)=~(Output);(Output)^=((Input)+(Output));}	//BitClip : Negative Absolute of 64-bit Integer
#define BitC_Abs_N_R32_(Output,Input) {Acs_(inte_32,Output)=Acs_(inte_32,Input)|0x80000000;}								//BitClip : Negative Absolute of 32-bit Real
#define BitC_Abs_N_R64_(Output,Input) {Acs_(inte_64,Output)=Acs_(inte_64,Input)|0x8000000000000000;}						//BitClip : Negative Absolute of 64-bit Real
#endif
#if(MemC_Fold_(Part:BitC_Lim_P_T##_))
#define BitC_Lim_P_I08_(Output,Input) {(Output)=Acs_(inte_08,Input)>>7;(Output)=~(Output);(Output)&=(Input);}																//BitClip : Positive Clipping of 8-bit Integer
#define BitC_Lim_P_I16_(Output,Input) {(Output)=Acs_(inte_16,Input)>>15;(Output)=~(Output);(Output)&=(Input);}																//BitClip : Positive Clipping of 16-bit Integer
#define BitC_Lim_P_I32_(Output,Input) {(Output)=Acs_(inte_32,Input)>>31;(Output)=~(Output);(Output)&=(Input);}																//BitClip : Positive Clipping of 32-bit Integer
#define BitC_Lim_P_I64_(Output,Input) {(Output)=Acs_(inte_64,Input)>>63;(Output)=~(Output);(Output)&=(Input);}																//BitClip : Positive Clipping of 64-bit Integer
#define BitC_Lim_P_R32_(Output,Input) {Acs_(inte_32,Output)=Acs_(inte_32,Input)>>31;Acs_(inte_32,Output)=~Acs_(inte_32,Output);Acs_(inte_32,Output)&=Acs_(inte_32,Input);}	//BitClip : Positive Clipping of 32-bit Real
#define BitC_Lim_P_R64_(Output,Input) {Acs_(inte_64,Output)=Acs_(inte_64,Input)>>63;Acs_(inte_64,Output)=~Acs_(inte_64,Output);Acs_(inte_64,Output)&=Acs_(inte_64,Input);}	//BitClip : Positive Clipping of 64-bit Real
#endif
#if(MemC_Fold_(Part:BitC_Lim_N_T##_))
#define BitC_Lim_N_I08_(Output,Input) {(Output)=Acs_(inte_08,Input)>>7;(Output)&=(Input);}										//BitClip : Negative Clipping of 8-bit Integer
#define BitC_Lim_N_I16_(Output,Input) {(Output)=Acs_(inte_16,Input)>>15;(Output)&=(Input);}										//BitClip : Negative Clipping of 16-bit Integer
#define BitC_Lim_N_I32_(Output,Input) {(Output)=Acs_(inte_32,Input)>>31;(Output)&=(Input);}										//BitClip : Negative Clipping of 32-bit Integer
#define BitC_Lim_N_I64_(Output,Input) {(Output)=Acs_(inte_64,Input)>>63;(Output)&=(Input);}										//BitClip : Negative Clipping of 64-bit Integer
#define BitC_Lim_N_R32_(Output,Input) {Acs_(inte_32,Output)=Acs_(inte_32,Input)>>31;Acs_(inte_32,Output)&=Acs_(inte_32,Input);}	//BitClip : Negative Clipping of 32-bit Real
#define BitC_Lim_N_R64_(Output,Input) {Acs_(inte_64,Output)=Acs_(inte_64,Input)>>63;Acs_(inte_64,Output)&=Acs_(inte_64,Input);}	//BitClip : Negative Clipping of 64-bit Real
#endif
#endif

#if(MemC_Fold_(Declaration:Global Constants))
//BitClip : Library Version
extern DATA_08 _PL_ BitClip;
//BitClip : Endianness
//＊Pointed value is 0x00 for big-endian, 0x01 for little-endian.
extern DATA_08 _PL_ BitCEndian;
//BitClip : 32-bit Non-Real
//＊[0] : ＋∞
//　[1] : －∞
//　[2] : ＋NaN
//　[3] : －NaN
extern REAL_32 _PL_ BitCInvalid32;
//BitClip : 64-bit Non-Real
//＊[0] : ＋∞
//　[1] : －∞
//　[2] : ＋NaN
//　[3] : －NaN
extern REAL_64 _PL_ BitCInvalid64;
//BitClip : 32-bit Pi and Euler Number
//＊[0] : π
//　[1] : 1／π
//　[2] : ｅ
//　[3] : 1／ｅ
extern REAL_32 _PL_ BitCPi32;
//BitClip : 64-bit Pi and Euler Number
//＊[0] : π
//　[1] : 1／π
//　[2] : ｅ
//　[3] : 1／ｅ
extern REAL_64 _PL_ BitCPi64;
//BitClip : Boolean Table
//＊[~1] : !1
//　[~0] : !0
//　[0] : 0
//　[1] : ~0
extern BOOLEAN _PL_ BitCBool;
//BitClip : Type Descriptor Set
//＊Access with BitCTypeT##
extern MEMC_DT _PL_ _PL_ BitCType;

#ifdef __OPENCL_H
//BitC_CL : OpenCL Source File Name Set
//＊[0] : "ouoclip.cl"
//　[1] : "bitclip.cl"
//　[2] : "bitclip.obj"
extern NAME_08 _PL_ _PL_ BitCFile;
//BitC_CL : OpenCL Kernel Indicator Set
extern NAME_08 _PL_ _PL_ BitCKernel;
#endif
#endif

#if(MemC_Fold_(Declaration:Endian Functions))
//BitClip : 16-bit Natural Endian Flipping
general BitC_Endian_D16_(data_16 _PL_ Data,DATA_32 Length);
//BitClip : 32-bit Natural Endian Flipping
general BitC_Endian_D32_(data_32 _PL_ Data,DATA_32 Length);
//BitClip : 64-bit Natural Endian Flipping
general BitC_Endian_D64_(data_64 _PL_ Data,DATA_32 Length);
#endif

#if(MemC_Fold_(Declaration:Caster Functions))
//BitClip : 8-bit Natural to 16-bit Natural Type Casting
general BitC_Caster_D08_D16_(DATA_08 *_R_ I,data_16 *_R_ O,DATA_32 N);
//BitClip : 8-bit Natural to 32-bit Natural Type Casting
general BitC_Caster_D08_D32_(DATA_08 *_R_ I,data_32 *_R_ O,DATA_32 N);
//BitClip : 8-bit Natural to 64-bit Natural Type Casting
general BitC_Caster_D08_D64_(DATA_08 *_R_ I,data_64 *_R_ O,DATA_32 N);
//BitClip : 8-bit Natural to 8-bit Integer Type Casting
general BitC_Caster_D08_I08_(DATA_08 *_R_ I,inte_08 *_R_ O,DATA_32 N);
//BitClip : 8-bit Natural to 32-bit Real Type Casting
general BitC_Caster_D08_R32_(DATA_08 *_R_ I,real_32 *_R_ O,DATA_32 N);
//BitClip : 8-bit Natural to 64-bit Real Type Casting
general BitC_Caster_D08_R64_(DATA_08 *_R_ I,real_64 *_R_ O,DATA_32 N);

//BitClip : 16-bit Natural to 8-bit Natural Type Casting
general BitC_Caster_D16_D08_(DATA_16 *_R_ I,data_08 *_R_ O,DATA_32 N);
//BitClip : 16-bit Natural to 32-bit Natural Type Casting
general BitC_Caster_D16_D32_(DATA_16 *_R_ I,data_32 *_R_ O,DATA_32 N);
//BitClip : 16-bit Natural to 64-bit Natural Type Casting
general BitC_Caster_D16_D64_(DATA_16 *_R_ I,data_64 *_R_ O,DATA_32 N);
//BitClip : 16-bit Natural to 8-bit Integer Type Casting
general BitC_Caster_D16_I08_(DATA_16 *_R_ I,inte_08 *_R_ O,DATA_32 N);
//BitClip : 16-bit Natural to 16-bit Integer Type Casting
general BitC_Caster_D16_I16_(DATA_16 *_R_ I,inte_16 *_R_ O,DATA_32 N);
//BitClip : 16-bit Natural to 32-bit Real Type Casting
general BitC_Caster_D16_R32_(DATA_16 *_R_ I,real_32 *_R_ O,DATA_32 N);
//BitClip : 16-bit Natural to 64-bit Real Type Casting
general BitC_Caster_D16_R64_(DATA_16 *_R_ I,real_64 *_R_ O,DATA_32 N);

//BitClip : 32-bit Natural to 8-bit Natural Type Casting
general BitC_Caster_D32_D08_(DATA_32 *_R_ I,data_08 *_R_ O,DATA_32 N);
//BitClip : 32-bit Natural to 16-bit Natural Type Casting
general BitC_Caster_D32_D16_(DATA_32 *_R_ I,data_16 *_R_ O,DATA_32 N);
//BitClip : 32-bit Natural to 64-bit Natural Type Casting
general BitC_Caster_D32_D64_(DATA_32 *_R_ I,data_64 *_R_ O,DATA_32 N);
//BitClip : 32-bit Natural to 8-bit Integer Type Casting
general BitC_Caster_D32_I08_(DATA_32 *_R_ I,inte_08 *_R_ O,DATA_32 N);
//BitClip : 32-bit Natural to 16-bit Integer Type Casting
general BitC_Caster_D32_I16_(DATA_32 *_R_ I,inte_16 *_R_ O,DATA_32 N);
//BitClip : 32-bit Natural to 32-bit Integer Type Casting
general BitC_Caster_D32_I32_(DATA_32 *_R_ I,inte_32 *_R_ O,DATA_32 N);
//BitClip : 32-bit Natural to 32-bit Real Type Casting
general BitC_Caster_D32_R32_(DATA_32 *_R_ I,real_32 *_R_ O,DATA_32 N);
//BitClip : 32-bit Natural to 64-bit Real Type Casting
general BitC_Caster_D32_R64_(DATA_32 *_R_ I,real_64 *_R_ O,DATA_32 N);

//BitClip : 64-bit Natural to 8-bit Natural Type Casting
general BitC_Caster_D64_D08_(DATA_64 *_R_ I,data_08 *_R_ O,DATA_32 N);
//BitClip : 64-bit Natural to 16-bit Natural Type Casting
general BitC_Caster_D64_D16_(DATA_64 *_R_ I,data_16 *_R_ O,DATA_32 N);
//BitClip : 64-bit Natural to 32-bit Natural Type Casting
general BitC_Caster_D64_D32_(DATA_64 *_R_ I,data_32 *_R_ O,DATA_32 N);
//BitClip : 64-bit Natural to 8-bit Integer Type Casting
general BitC_Caster_D64_I08_(DATA_64 *_R_ I,inte_08 *_R_ O,DATA_32 N);
//BitClip : 64-bit Natural to 16-bit Integer Type Casting
general BitC_Caster_D64_I16_(DATA_64 *_R_ I,inte_16 *_R_ O,DATA_32 N);
//BitClip : 64-bit Natural to 32-bit Integer Type Casting
general BitC_Caster_D64_I32_(DATA_64 *_R_ I,inte_32 *_R_ O,DATA_32 N);
//BitClip : 64-bit Natural to 64-bit Integer Type Casting
general BitC_Caster_D64_I64_(DATA_64 *_R_ I,inte_64 *_R_ O,DATA_32 N);
//BitClip : 64-bit Natural to 32-bit Real Type Casting
general BitC_Caster_D64_R32_(DATA_64 *_R_ I,real_32 *_R_ O,DATA_32 N);
//BitClip : 64-bit Natural to 64-bit Real Type Casting
general BitC_Caster_D64_R64_(DATA_64 *_R_ I,real_64 *_R_ O,DATA_32 N);

//BitClip : 8-bit Integer to 8-bit Natural Type Casting
general BitC_Caster_I08_D08_(INTE_08 *_R_ I,data_08 *_R_ O,DATA_32 N);
//BitClip : 8-bit Integer to 16-bit Natural Type Casting
general BitC_Caster_I08_D16_(INTE_08 *_R_ I,data_16 *_R_ O,DATA_32 N);
//BitClip : 8-bit Integer to 32-bit Natural Type Casting
general BitC_Caster_I08_D32_(INTE_08 *_R_ I,data_32 *_R_ O,DATA_32 N);
//BitClip : 8-bit Integer to 64-bit Natural Type Casting
general BitC_Caster_I08_D64_(INTE_08 *_R_ I,data_64 *_R_ O,DATA_32 N);
//BitClip : 8-bit Integer to 16-bit Integer Type Casting
general BitC_Caster_I08_I16_(INTE_08 *_R_ I,inte_16 *_R_ O,DATA_32 N);
//BitClip : 8-bit Integer to 32-bit Integer Type Casting
general BitC_Caster_I08_I32_(INTE_08 *_R_ I,inte_32 *_R_ O,DATA_32 N);
//BitClip : 8-bit Integer to 64-bit Integer Type Casting
general BitC_Caster_I08_I64_(INTE_08 *_R_ I,inte_64 *_R_ O,DATA_32 N);
//BitClip : 8-bit Integer to 32-bit Real Type Casting
general BitC_Caster_I08_R32_(INTE_08 *_R_ I,real_32 *_R_ O,DATA_32 N);
//BitClip : 8-bit Integer to 64-bit Real Type Casting
general BitC_Caster_I08_R64_(INTE_08 *_R_ I,real_64 *_R_ O,DATA_32 N);

//BitClip : 16-bit Integer to 8-bit Natural Type Casting
general BitC_Caster_I16_D08_(INTE_16 *_R_ I,data_08 *_R_ O,DATA_32 N);
//BitClip : 16-bit Integer to 16-bit Natural Type Casting
general BitC_Caster_I16_D16_(INTE_16 *_R_ I,data_16 *_R_ O,DATA_32 N);
//BitClip : 16-bit Integer to 32-bit Natural Type Casting
general BitC_Caster_I16_D32_(INTE_16 *_R_ I,data_32 *_R_ O,DATA_32 N);
//BitClip : 16-bit Integer to 64-bit Natural Type Casting
general BitC_Caster_I16_D64_(INTE_16 *_R_ I,data_64 *_R_ O,DATA_32 N);
//BitClip : 16-bit Integer to 8-bit Integer Type Casting
general BitC_Caster_I16_I08_(INTE_16 *_R_ I,inte_08 *_R_ O,DATA_32 N);
//BitClip : 16-bit Integer to 32-bit Integer Type Casting
general BitC_Caster_I16_I32_(INTE_16 *_R_ I,inte_32 *_R_ O,DATA_32 N);
//BitClip : 16-bit Integer to 64-bit Integer Type Casting
general BitC_Caster_I16_I64_(INTE_16 *_R_ I,inte_64 *_R_ O,DATA_32 N);
//BitClip : 16-bit Integer to 32-bit Real Type Casting
general BitC_Caster_I16_R32_(INTE_16 *_R_ I,real_32 *_R_ O,DATA_32 N);
//BitClip : 16-bit Integer to 64-bit Real Type Casting
general BitC_Caster_I16_R64_(INTE_16 *_R_ I,real_64 *_R_ O,DATA_32 N);

//BitClip : 32-bit Integer to 8-bit Natural Type Casting
general BitC_Caster_I32_D08_(INTE_32 *_R_ I,data_08 *_R_ O,DATA_32 N);
//BitClip : 32-bit Integer to 16-bit Natural Type Casting
general BitC_Caster_I32_D16_(INTE_32 *_R_ I,data_16 *_R_ O,DATA_32 N);
//BitClip : 32-bit Integer to 32-bit Natural Type Casting
general BitC_Caster_I32_D32_(INTE_32 *_R_ I,data_32 *_R_ O,DATA_32 N);
//BitClip : 32-bit Integer to 64-bit Natural Type Casting
general BitC_Caster_I32_D64_(INTE_32 *_R_ I,data_64 *_R_ O,DATA_32 N);
//BitClip : 32-bit Integer to 8-bit Integer Type Casting
general BitC_Caster_I32_I08_(INTE_32 *_R_ I,inte_08 *_R_ O,DATA_32 N);
//BitClip : 32-bit Integer to 16-bit Integer Type Casting
general BitC_Caster_I32_I16_(INTE_32 *_R_ I,inte_16 *_R_ O,DATA_32 N);
//BitClip : 32-bit Integer to 64-bit Integer Type Casting
general BitC_Caster_I32_I64_(INTE_32 *_R_ I,inte_64 *_R_ O,DATA_32 N);
//BitClip : 32-bit Integer to 32-bit Real Type Casting
general BitC_Caster_I32_R32_(INTE_32 *_R_ I,real_32 *_R_ O,DATA_32 N);
//BitClip : 32-bit Integer to 64-bit Real Type Casting
general BitC_Caster_I32_R64_(INTE_32 *_R_ I,real_64 *_R_ O,DATA_32 N);

//BitClip : 64-bit Integer to 8-bit Natural Type Casting
general BitC_Caster_I64_D08_(INTE_64 *_R_ I,data_08 *_R_ O,DATA_32 N);
//BitClip : 64-bit Integer to 16-bit Natural Type Casting
general BitC_Caster_I64_D16_(INTE_64 *_R_ I,data_16 *_R_ O,DATA_32 N);
//BitClip : 64-bit Integer to 32-bit Natural Type Casting
general BitC_Caster_I64_D32_(INTE_64 *_R_ I,data_32 *_R_ O,DATA_32 N);
//BitClip : 64-bit Integer to 64-bit Natural Type Casting
general BitC_Caster_I64_D64_(INTE_64 *_R_ I,data_64 *_R_ O,DATA_32 N);
//BitClip : 64-bit Integer to 8-bit Integer Type Casting
general BitC_Caster_I64_I08_(INTE_64 *_R_ I,inte_08 *_R_ O,DATA_32 N);
//BitClip : 64-bit Integer to 16-bit Integer Type Casting
general BitC_Caster_I64_I16_(INTE_64 *_R_ I,inte_16 *_R_ O,DATA_32 N);
//BitClip : 64-bit Integer to 32-bit Integer Type Casting
general BitC_Caster_I64_I32_(INTE_64 *_R_ I,inte_32 *_R_ O,DATA_32 N);
//BitClip : 64-bit Integer to 32-bit Real Type Casting
general BitC_Caster_I64_R32_(INTE_64 *_R_ I,real_32 *_R_ O,DATA_32 N);
//BitClip : 64-bit Integer to 64-bit Real Type Casting
general BitC_Caster_I64_R64_(INTE_64 *_R_ I,real_64 *_R_ O,DATA_32 N);

//BitClip : 32-bit Real to 8-bit Natural Type Casting
general BitC_Caster_R32_D08_(REAL_32 *_R_ I,data_08 *_R_ O,DATA_32 N);
//BitClip : 32-bit Real to 16-bit Natural Type Casting
general BitC_Caster_R32_D16_(REAL_32 *_R_ I,data_16 *_R_ O,DATA_32 N);
//BitClip : 32-bit Real to 32-bit Natural Type Casting
general BitC_Caster_R32_D32_(REAL_32 *_R_ I,data_32 *_R_ O,DATA_32 N);
//BitClip : 32-bit Real to 64-bit Natural Type Casting
general BitC_Caster_R32_D64_(REAL_32 *_R_ I,data_64 *_R_ O,DATA_32 N);
//BitClip : 32-bit Real to 8-bit Integer Type Casting
general BitC_Caster_R32_I08_(REAL_32 *_R_ I,inte_08 *_R_ O,DATA_32 N);
//BitClip : 32-bit Real to 16-bit Integer Type Casting
general BitC_Caster_R32_I16_(REAL_32 *_R_ I,inte_16 *_R_ O,DATA_32 N);
//BitClip : 32-bit Real to 32-bit Integer Type Casting
general BitC_Caster_R32_I32_(REAL_32 *_R_ I,inte_32 *_R_ O,DATA_32 N);
//BitClip : 32-bit Real to 64-bit Integer Type Casting
general BitC_Caster_R32_I64_(REAL_32 *_R_ I,inte_64 *_R_ O,DATA_32 N);
//BitClip : 32-bit Real to 64-bit Real Type Casting
general BitC_Caster_R32_R64_(REAL_32 *_R_ I,real_64 *_R_ O,DATA_32 N);

//BitClip : 64-bit Real to 8-bit Natural Type Casting
general BitC_Caster_R64_D08_(REAL_64 *_R_ I,data_08 *_R_ O,DATA_32 N);
//BitClip : 64-bit Real to 16-bit Natural Type Casting
general BitC_Caster_R64_D16_(REAL_64 *_R_ I,data_16 *_R_ O,DATA_32 N);
//BitClip : 64-bit Real to 32-bit Natural Type Casting
general BitC_Caster_R64_D32_(REAL_64 *_R_ I,data_32 *_R_ O,DATA_32 N);
//BitClip : 64-bit Real to 64-bit Natural Type Casting
general BitC_Caster_R64_D64_(REAL_64 *_R_ I,data_64 *_R_ O,DATA_32 N);
//BitClip : 64-bit Real to 8-bit Integer Type Casting
general BitC_Caster_R64_I08_(REAL_64 *_R_ I,inte_08 *_R_ O,DATA_32 N);
//BitClip : 64-bit Real to 16-bit Integer Type Casting
general BitC_Caster_R64_I16_(REAL_64 *_R_ I,inte_16 *_R_ O,DATA_32 N);
//BitClip : 64-bit Real to 32-bit Integer Type Casting
general BitC_Caster_R64_I32_(REAL_64 *_R_ I,inte_32 *_R_ O,DATA_32 N);
//BitClip : 64-bit Real to 64-bit Integer Type Casting
general BitC_Caster_R64_I64_(REAL_64 *_R_ I,inte_64 *_R_ O,DATA_32 N);
//BitClip : 64-bit Real to 32-bit Real Type Casting
general BitC_Caster_R64_R32_(REAL_64 *_R_ I,real_32 *_R_ O,DATA_32 N);
#endif

#if(MemC_Fold_(Declaration:Bit Operation Functions))
//BitClip : 8-bit Natural NOT Operation
//＊C[n]＝~A[n]
general BitC_BO_N_1_D08_(data_08 _PL_ C,DATA_08 _PL_ A,DATA_32 N);

//BitClip : 8-Bit Natural Bit Shift Operation
//＊C[n]＝A[n]<<S
general BitC_BO_S_1_D08_(data_08 *C,DATA_08 *A,inte_32 S,DATA_32 N);
//BitClip : 16-Bit Natural Bit Shift Operation
//＊C[n]＝A[n]<<S
general BitC_BO_S_1_D16_(data_16 *C,DATA_16 *A,inte_32 S,DATA_32 N);
//BitClip : 32-Bit Natural Bit Shift Operation
//＊C[n]＝A[n]<<S
general BitC_BO_S_1_D32_(data_32 *C,DATA_32 *A,inte_32 S,DATA_32 N);
//BitClip : 64-Bit Natural Bit Shift Operation
//＊C[n]＝A[n]<<S
general BitC_BO_S_1_D64_(data_64 *C,DATA_64 *A,inte_32 S,DATA_32 N);
//BitClip : 8-Bit Integer Bit Shift Operation
//＊C[n]＝A[n]<<S
general BitC_BO_S_1_I08_(inte_08 *C,INTE_08 *A,inte_32 S,DATA_32 N);
//BitClip : 16-Bit Integer Bit Shift Operation
//＊C[n]＝A[n]<<S
general BitC_BO_S_1_I16_(inte_16 *C,INTE_16 *A,inte_32 S,DATA_32 N);
//BitClip : 32-Bit Integer Bit Shift Operation
//＊C[n]＝A[n]<<S
general BitC_BO_S_1_I32_(inte_32 *C,INTE_32 *A,inte_32 S,DATA_32 N);
//BitClip : 64-Bit Integer Bit Shift Operation
//＊C[n]＝A[n]<<S
general BitC_BO_S_1_I64_(inte_64 *C,INTE_64 *A,inte_32 S,DATA_32 N);

//BitClip : 8-bit Natural AND Operation
//＊C[n]＝A[n]&M
general BitC_BO_A_1_D08_(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 M,DATA_32 N);
//BitClip : 16-bit Natural AND Operation
//＊C[n]＝A[n]&M
general BitC_BO_A_1_D16_(data_16 _PL_ C,DATA_16 _PL_ A,DATA_16 M,DATA_32 N);
//BitClip : 32-bit Natural AND Operation
//＊C[n]＝A[n]&M
general BitC_BO_A_1_D32_(data_32 _PL_ C,DATA_32 _PL_ A,DATA_32 M,DATA_32 N);
//BitClip : 64-bit Natural AND Operation
//＊C[n]＝A[n]&M
general BitC_BO_A_1_D64_(data_32 _PL_ C,DATA_32 _PL_ A,DATA_64 M,DATA_32 N);
//BitClip : 8-bit Natural AND Operation
//＊C[n]＝A[n]&B[n]
general BitC_BO_A_2_D08_(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 _PL_ B,DATA_32 N);

//BitClip : 8-bit Natural OR Operation
//＊C[n]＝A[n]|M
general BitC_BO_O_1_D08_(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 M,DATA_32 N);
//BitClip : 16-bit Natural OR Operation
//＊C[n]＝A[n]|M
general BitC_BO_O_1_D16_(data_16 _PL_ C,DATA_16 _PL_ A,DATA_16 M,DATA_32 N);
//BitClip : 32-bit Natural OR Operation
//＊C[n]＝A[n]|M
general BitC_BO_O_1_D32_(data_32 _PL_ C,DATA_32 _PL_ A,DATA_32 M,DATA_32 N);
//BitClip : 64-bit Natural OR Operation
//＊C[n]＝A[n]|M
general BitC_BO_O_1_D64_(data_32 _PL_ C,DATA_32 _PL_ A,DATA_64 M,DATA_32 N);
//BitClip : 8-bit Natural OR Operation
//＊C[n]＝A[n]|B[n]
general BitC_BO_O_2_D08_(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 _PL_ B,DATA_32 N);

//BitClip : 8-bit Natural XOR Operation
//＊C[n]＝A[n]^M
general BitC_BO_X_1_D08_(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 M,DATA_32 N);
//BitClip : 16-bit Natural XOR Operation
//＊C[n]＝A[n]^M
general BitC_BO_X_1_D16_(data_16 _PL_ C,DATA_16 _PL_ A,DATA_16 M,DATA_32 N);
//BitClip : 32-bit Natural XOR Operation
//＊C[n]＝A[n]^M
general BitC_BO_X_1_D32_(data_32 _PL_ C,DATA_32 _PL_ A,DATA_32 M,DATA_32 N);
//BitClip : 64-bit Natural XOR Operation
//＊C[n]＝A[n]^M
general BitC_BO_X_1_D64_(data_32 _PL_ C,DATA_32 _PL_ A,DATA_64 M,DATA_32 N);
//BitClip : 8-bit Natural XOR Operation
//＊C[n]＝A[n]^B[n]
general BitC_BO_X_2_D08_(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 _PL_ B,DATA_32 N);
#endif

#if(MemC_Fold_(Declaration:Relational Operation Functions))
//BitClip : Bit Expansion to 8-bit Natural
//＊O[n]＝(I[n/8].bit[n%8])?(0xFF):(0x00)
general BitC_Expand_D08_(DATA_08 *_R_ I,data_08 *_R_ O,DATA_32 N);
//BitClip : Bit Expansion to 16-bit Natural
//＊O[n]＝(I[n/8].bit[n%8])?(0xFFFF):(0x0000)
general BitC_Expand_D16_(DATA_08 *_R_ I,data_16 *_R_ O,DATA_32 N);
//BitClip : Bit Expansion to 32-bit Natural
//＊O[n]＝(I[n/8].bit[n%8])?(0xFFFFFFFF):(0x00000000)
general BitC_Expand_D32_(DATA_08 *_R_ I,data_32 *_R_ O,DATA_32 N);
//BitClip : Bit Expansion to 64-bit Natural
//＊O[n]＝(I[n/8].bit[n%8])?(0xFFFFFFFFFFFFFFFF):(0x0000000000000000)
general BitC_Expand_D64_(DATA_08 *_R_ I,data_64 *_R_ O,DATA_32 N);

//BitClip : Bit Shrinkage from 8-bit Natural
//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
general BitC_Shrink_D08_(DATA_08 *_R_ I,data_08 *_R_ O,DATA_32 N);
//BitClip : Bit Shrinkage from 16-bit Natural
//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
general BitC_Shrink_D16_(DATA_16 *_R_ I,data_08 *_R_ O,DATA_32 N);
//BitClip : Bit Shrinkage from 32-bit Natural
//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
general BitC_Shrink_D32_(DATA_32 *_R_ I,data_08 *_R_ O,DATA_32 N);
//BitClip : Bit Shrinkage from 64-bit Natural
//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
general BitC_Shrink_D64_(DATA_64 *_R_ I,data_08 *_R_ O,DATA_32 N);

//BitClip : 8-bit Natural EQ Operation
//＊C[n/8].bit[n%8]＝(A[n]==V)
general BitC_RO_E_1_D08_(data_08 *_R_ C,DATA_08 *_R_ A,DATA_08 V,DATA_32 N);
//BitClip : 16-bit Natural EQ Operation
//＊C[n/8].bit[n%8]＝(A[n]==V)
general BitC_RO_E_1_D16_(data_08 *_R_ C,DATA_16 *_R_ A,DATA_16 V,DATA_32 N);
//BitClip : 32-bit Natural EQ Operation
//＊C[n/8].bit[n%8]＝(A[n]==V)
general BitC_RO_E_1_D32_(data_08 *_R_ C,DATA_32 *_R_ A,DATA_32 V,DATA_32 N);
//BitClip : 64-bit Natural EQ Operation
//＊C[n/8].bit[n%8]＝(A[n]==V)
general BitC_RO_E_1_D64_(data_08 *_R_ C,DATA_64 *_R_ A,DATA_64 V,DATA_32 N);
//BitClip : 8-bit Natural EQ Operation
//＊C[n/8].bit[n%8]＝(A[n]==B[n])
general BitC_RO_E_2_D08_(data_08 *_R_ C,DATA_08 *_R_ A,DATA_08 *_R_ B,DATA_32 N);
//BitClip : 16-bit Natural EQ Operation
//＊C[n/8].bit[n%8]＝(A[n]==B[n])
general BitC_RO_E_2_D16_(data_08 *_R_ C,DATA_16 *_R_ A,DATA_16 *_R_ B,DATA_32 N);
//BitClip : 32-bit Natural EQ Operation
//＊C[n/8].bit[n%8]＝(A[n]==B[n])
general BitC_RO_E_2_D32_(data_08 *_R_ C,DATA_32 *_R_ A,DATA_32 *_R_ B,DATA_32 N);
//BitClip : 64-bit Natural EQ Operation
//＊C[n/8].bit[n%8]＝(A[n]==B[n])
general BitC_RO_E_2_D64_(data_08 *_R_ C,DATA_64 *_R_ A,DATA_64 *_R_ B,DATA_32 N);

//BitClip : 8-bit Natural NE Operation
//＊C[n/8].bit[n%8]＝(A[n]!=V)
general BitC_RO_N_1_D08_(data_08 *_R_ C,DATA_08 *_R_ A,DATA_08 V,DATA_32 N);
//BitClip : 16-bit Natural NE Operation
//＊C[n/8].bit[n%8]＝(A[n]!=V)
general BitC_RO_N_1_D16_(data_08 *_R_ C,DATA_16 *_R_ A,DATA_16 V,DATA_32 N);
//BitClip : 32-bit Natural NE Operation
//＊C[n/8].bit[n%8]＝(A[n]!=V)
general BitC_RO_N_1_D32_(data_08 *_R_ C,DATA_32 *_R_ A,DATA_32 V,DATA_32 N);
//BitClip : 64-bit Natural NE Operation
//＊C[n/8].bit[n%8]＝(A[n]!=V)
general BitC_RO_N_1_D64_(data_08 *_R_ C,DATA_64 *_R_ A,DATA_64 V,DATA_32 N);
//BitClip : 8-bit Natural NE Operation
//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
general BitC_RO_N_2_D08_(data_08 *_R_ C,DATA_08 *_R_ A,DATA_08 *_R_ B,DATA_32 N);
//BitClip : 16-bit Natural NE Operation
//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
general BitC_RO_N_2_D16_(data_08 *_R_ C,DATA_16 *_R_ A,DATA_16 *_R_ B,DATA_32 N);
//BitClip : 32-bit Natural NE Operation
//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
general BitC_RO_N_2_D32_(data_08 *_R_ C,DATA_32 *_R_ A,DATA_32 *_R_ B,DATA_32 N);
//BitClip : 64-bit Natural NE Operation
//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
general BitC_RO_N_2_D64_(data_08 *_R_ C,DATA_64 *_R_ A,DATA_64 *_R_ B,DATA_32 N);

//BitClip : 8-bit Natural GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥V)
general BitC_RO_G_1_D08_(data_08 *_R_ C,DATA_08 *_R_ A,DATA_08 V,DATA_32 N);
//BitClip : 16-bit Natural GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥V)
general BitC_RO_G_1_D16_(data_08 *_R_ C,DATA_16 *_R_ A,DATA_16 V,DATA_32 N);
//BitClip : 32-bit Natural GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥V)
general BitC_RO_G_1_D32_(data_08 *_R_ C,DATA_32 *_R_ A,DATA_32 V,DATA_32 N);
//BitClip : 64-bit Natural GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥V)
general BitC_RO_G_1_D64_(data_08 *_R_ C,DATA_64 *_R_ A,DATA_64 V,DATA_32 N);
//BitClip : 8-bit Integer GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥V)
general BitC_RO_G_1_I08_(data_08 *_R_ C,INTE_08 *_R_ A,INTE_08 V,DATA_32 N);
//BitClip : 16-bit Integer GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥V)
general BitC_RO_G_1_I16_(data_08 *_R_ C,INTE_16 *_R_ A,INTE_16 V,DATA_32 N);
//BitClip : 32-bit Integer GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥V)
general BitC_RO_G_1_I32_(data_08 *_R_ C,INTE_32 *_R_ A,INTE_32 V,DATA_32 N);
//BitClip : 64-bit Integer GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥V)
general BitC_RO_G_1_I64_(data_08 *_R_ C,INTE_64 *_R_ A,INTE_64 V,DATA_32 N);
//BitClip : 32-bit Real GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥V)
general BitC_RO_G_1_R32_(data_08 *_R_ C,REAL_32 *_R_ A,REAL_32 V,DATA_32 N);
//BitClip : 64-bit Real GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥V)
general BitC_RO_G_1_R64_(data_08 *_R_ C,REAL_64 *_R_ A,REAL_64 V,DATA_32 N);
//BitClip : 8-bit Natural GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
general BitC_RO_G_2_D08_(data_08 *_R_ C,DATA_08 *_R_ A,DATA_08 *_R_ B,DATA_32 N);
//BitClip : 16-bit Natural GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
general BitC_RO_G_2_D16_(data_08 *_R_ C,DATA_16 *_R_ A,DATA_16 *_R_ B,DATA_32 N);
//BitClip : 32-bit Natural GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
general BitC_RO_G_2_D32_(data_08 *_R_ C,DATA_32 *_R_ A,DATA_32 *_R_ B,DATA_32 N);
//BitClip : 64-bit Natural GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
general BitC_RO_G_2_D64_(data_08 *_R_ C,DATA_64 *_R_ A,DATA_64 *_R_ B,DATA_32 N);
//BitClip : 8-bit Integer GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
general BitC_RO_G_2_I08_(data_08 *_R_ C,INTE_08 *_R_ A,INTE_08 *_R_ B,DATA_32 N);
//BitClip : 16-bit Integer GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
general BitC_RO_G_2_I16_(data_08 *_R_ C,INTE_16 *_R_ A,INTE_16 *_R_ B,DATA_32 N);
//BitClip : 32-bit Integer GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
general BitC_RO_G_2_I32_(data_08 *_R_ C,INTE_32 *_R_ A,INTE_32 *_R_ B,DATA_32 N);
//BitClip : 64-bit Integer GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
general BitC_RO_G_2_I64_(data_08 *_R_ C,INTE_64 *_R_ A,INTE_64 *_R_ B,DATA_32 N);
//BitClip : 32-bit Real GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
general BitC_RO_G_2_R32_(data_08 *_R_ C,REAL_32 *_R_ A,REAL_32 *_R_ B,DATA_32 N);
//BitClip : 64-bit Real GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
general BitC_RO_G_2_R64_(data_08 *_R_ C,REAL_64 *_R_ A,REAL_64 *_R_ B,DATA_32 N);

//BitClip : 8-bit Natural LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜V)
general BitC_RO_L_1_D08_(data_08 *_R_ C,DATA_08 *_R_ A,DATA_08 V,DATA_32 N);
//BitClip : 16-bit Natural LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜V)
general BitC_RO_L_1_D16_(data_08 *_R_ C,DATA_16 *_R_ A,DATA_16 V,DATA_32 N);
//BitClip : 32-bit Natural LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜V)
general BitC_RO_L_1_D32_(data_08 *_R_ C,DATA_32 *_R_ A,DATA_32 V,DATA_32 N);
//BitClip : 64-bit Natural LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜V)
general BitC_RO_L_1_D64_(data_08 *_R_ C,DATA_64 *_R_ A,DATA_64 V,DATA_32 N);
//BitClip : 8-bit Integer LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜V)
general BitC_RO_L_1_I08_(data_08 *_R_ C,INTE_08 *_R_ A,INTE_08 V,DATA_32 N);
//BitClip : 16-bit Integer LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜V)
general BitC_RO_L_1_I16_(data_08 *_R_ C,INTE_16 *_R_ A,INTE_16 V,DATA_32 N);
//BitClip : 32-bit Integer LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜V)
general BitC_RO_L_1_I32_(data_08 *_R_ C,INTE_32 *_R_ A,INTE_32 V,DATA_32 N);
//BitClip : 64-bit Integer LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜V)
general BitC_RO_L_1_I64_(data_08 *_R_ C,INTE_64 *_R_ A,INTE_64 V,DATA_32 N);
//BitClip : 32-bit Real LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜V)
general BitC_RO_L_1_R32_(data_08 *_R_ C,REAL_32 *_R_ A,REAL_32 V,DATA_32 N);
//BitClip : 64-bit Real LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜V)
general BitC_RO_L_1_R64_(data_08 *_R_ C,REAL_64 *_R_ A,REAL_64 V,DATA_32 N);

//BitClip : 8-bit Natural LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
general BitC_RO_L_2_D08_(data_08 *_R_ C,DATA_08 *_R_ A,DATA_08 *_R_ B,DATA_32 N);
//BitClip : 16-bit Natural LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
general BitC_RO_L_2_D16_(data_08 *_R_ C,DATA_16 *_R_ A,DATA_16 *_R_ B,DATA_32 N);
//BitClip : 32-bit Natural LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
general BitC_RO_L_2_D32_(data_08 *_R_ C,DATA_32 *_R_ A,DATA_32 *_R_ B,DATA_32 N);
//BitClip : 64-bit Natural LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
general BitC_RO_L_2_D64_(data_08 *_R_ C,DATA_64 *_R_ A,DATA_64 *_R_ B,DATA_32 N);
//BitClip : 8-bit Integer LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
general BitC_RO_L_2_I08_(data_08 *_R_ C,INTE_08 *_R_ A,INTE_08 *_R_ B,DATA_32 N);
//BitClip : 16-bit Integer LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
general BitC_RO_L_2_I16_(data_08 *_R_ C,INTE_16 *_R_ A,INTE_16 *_R_ B,DATA_32 N);
//BitClip : 32-bit Integer LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
general BitC_RO_L_2_I32_(data_08 *_R_ C,INTE_32 *_R_ A,INTE_32 *_R_ B,DATA_32 N);
//BitClip : 64-bit Integer LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
general BitC_RO_L_2_I64_(data_08 *_R_ C,INTE_64 *_R_ A,INTE_64 *_R_ B,DATA_32 N);
//BitClip : 32-bit Real LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
general BitC_RO_L_2_R32_(data_08 *_R_ C,REAL_32 *_R_ A,REAL_32 *_R_ B,DATA_32 N);
//BitClip : 64-bit Real LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
general BitC_RO_L_2_R64_(data_08 *_R_ C,REAL_64 *_R_ A,REAL_64 *_R_ B,DATA_32 N);
#endif

#if(MemC_Fold_(Declaration:BitClip Kernel Manager Functions))
#ifdef __OPENCL_H
//BitC_CL : Program Build
//＊Return value is an error code.
penc_eu BitC_CL_Binary_(cl_command_queue const Queue,NAME_08 _PL_ SourceDirectory,NAME_08 _PL_ ObjectDirectory,NAME_08 _PL_ BuildOption);

//BitC_CL : Kernel Manager Set Memory Allocation - Deallocate with "BitC_CL_Delete_"
bitc_cl *BitC_CL_Create_(general);
//BitC_CL : Kernel Activation Check Table
//＊Example of checking the kernel "BitC_Endian_D16_" :
//　BitC_CL_Choice_( KernelManager ) [ BitCEndianD16 ] = 1;
//＊Do not access the returned table after "BitC_CL_Launch_"
address *BitC_CL_Choice_(BITC_CL _PL_ KernelManager);
//BitC_CL : OpenCL Program Build with Specified Kernels
//＊Execute only one time.
//＊Return value is an error code.
penc_eu BitC_CL_Launch_(cl_command_queue const Queue,BITC_CL _PL_ KernelManager,NAME_08 _PL_ ObjectDirectory,NAME_08 _PL_ BuildOption);
//BitC_CL : Kernel Manager Set Memory Deallocation
general BitC_CL_Delete_(bitc_cl *_PL_ KernelManager);

//BitC_CL : Kernel Manager Task Enqueueing
//＊Example for KernelIndicator : BitCEndianD16
//　KernelArgument -> Slot.P[0] : &(cl_mem)(Data)
//　KernelArgument -> Slot.P[1] : &(data_32)(Length)
//＊Return value is an error code.
penc_eu BitC_CL_Action_(BITC_CL _PL_ KernelManager,MEMC_MS _PL_ KernelArgument,BITC_KI KernelIndicator);
#endif
#endif

#if(MemC_Fold_(Declaration:Array Reformation Functions))
//BitClip : Array Reformation for SourceShape[dim] == TargetShape[ReformingAxis[dim]]
boolean _BitC_Reform_(GENERAL _PL_ SourceArray,general _PL_ TargetArray,DATA_32 _PL_ SourceShape,DATA_32 _PL_ ReformingAxis,data_32 Dimensions,data_32 TypeSize);
#define BitC_Reform_(S,T,SShp,StoTAxis,Dims,type) _BitC_Reform_(S,T,SShp,StoTAxis,Dims,sizeof(type))
#define BitC_Reform_D08_(S,T,SShp,StoTAxis,Dims) BitC_Reform_(S,T,SShp,StoTAxis,Dims,data_08)
#define BitC_Reform_D16_(S,T,SShp,StoTAxis,Dims) BitC_Reform_(S,T,SShp,StoTAxis,Dims,data_16)
#define BitC_Reform_D32_(S,T,SShp,StoTAxis,Dims) BitC_Reform_(S,T,SShp,StoTAxis,Dims,data_32)
#define BitC_Reform_D64_(S,T,SShp,StoTAxis,Dims) BitC_Reform_(S,T,SShp,StoTAxis,Dims,data_64)
#endif
#endif
