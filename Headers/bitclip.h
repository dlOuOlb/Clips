/*------------------------------------------------------------------*/
/*	BitClip specifies the size of data types.						*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2018.03.21	*/
/*------------------------------------------------------------------*/
/*	OpenCL Support													*/
/*	http://www.khronos.org/opencl/									*/
/*------------------------------------------------------------------*/

#ifndef _INC_BITCLIP
#define _INC_BITCLIP	//BitClip : Header Declaration

#if((-1)!=((-1)>>1))
#error The bit shift right operation of a signed integer does not preserve the sign bit in this implementation.
#endif

#include <stdint.h>
#ifdef _CL
#include <CL\opencl.h>
#endif
#include <memclip.h>
#ifdef __OPENCL_H
#include <penclip.h>
#endif

#if(MemC_Fold_(Definition:Types))
typedef uint8_t data_08;		//BitClip : 8-bit Natural Variable
typedef uint16_t data_16;		//BitClip : 16-bit Natural Variable
typedef uint32_t data_32;		//BitClip : 32-bit Natural Variable
typedef uint64_t data_64;		//BitClip : 64-bit Natural Variable

typedef const data_08 DATA_08;	//BitClip : 8-bit Natural Constant
typedef const data_16 DATA_16;	//BitClip : 16-bit Natural Constant
typedef const data_32 DATA_32;	//BitClip : 32-bit Natural Constant
typedef const data_64 DATA_64;	//BitClip : 64-bit Natural Constant

typedef int8_t inte_08;			//BitClip : 8-bit Integer Variable
typedef int16_t inte_16;		//BitClip : 16-bit Integer Variable
typedef int32_t inte_32;		//BitClip : 32-bit Integer Variable
typedef int64_t inte_64;		//BitClip : 64-bit Integer Variable

typedef const inte_08 INTE_08;	//BitClip : 8-bit Integer Constant
typedef const inte_16 INTE_16;	//BitClip : 16-bit Integer Constant
typedef const inte_32 INTE_32;	//BitClip : 32-bit Integer Constant
typedef const inte_64 INTE_64;	//BitClip : 64-bit Integer Constant

typedef float real_32;			//BitClip : 32-bit Single Precision Floating Point Variable
typedef double real_64;			//BitClip : 64-bit Double Precision Floating Point Variable

typedef const real_32 REAL_32;	//BitClip : 32-bit Single Precision Floating Point Constant
typedef const real_64 REAL_64;	//BitClip : 64-bit Double Precision Floating Point Constant

typedef void general;			//BitClip : General Variable
typedef signed int integer;		//BitClip : Integer Variable
typedef unsigned int natural;	//BitClip : Natural Variable
typedef size_t address;			//BitClip : Address Variable

typedef const general GENERAL;	//BitClip : General Constant
typedef const integer INTEGER;	//BitClip : Integer Constant
typedef const natural NATURAL;	//BitClip : Natural Constant
typedef const address ADDRESS;	//BitClip : Address Constant

typedef void (*func_p_)(void);	//BitClip : Function Pointer Variable
typedef const func_p_ FUNC_P_;	//BitClip : Function Pointer Constant

enum _boolean	//BitClip : Boolean Enumeration
{
	Null=0,		//BitClip : All Bits Off
	Full=~0		//BitClip : All Bits On
};
typedef enum _boolean boolean;			//BitClip : Boolean Variable
typedef const enum _boolean BOOLEAN;	//BitClip : Boolean Constant

union _point_v		//BitClip : Variable Pointer Union
{
	general *G;		//BitClip : General Container
	address A;		//BitClip : Address Container
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
};
typedef union _point_v point_v;			//BitClip : Variable Pointer Variable
typedef const union _point_v POINT_V;	//BitClip : Variable Pointer Constant

union _point_c		//BitClip : Constant Pointer Union
{
	GENERAL *G;		//BitClip : General Container
	address A;		//BitClip : Address Container
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
};
typedef union _point_c point_c;			//BitClip : Constant Pointer Variable
typedef const union _point_c POINT_C;	//BitClip : Constant Pointer Constant

union _bitclip	//BitClip : Pointer Union
{
	point_v V;	//BitClip : Read or Write Access
	point_c C;	//BitClip : Read Only Access
};
typedef union _bitclip bitclip;			//BitClip : Pointer Variable
typedef const union _bitclip BITCLIP;	//BitClip : Pointer Constant

#ifdef __OPENCL_H
enum _bitc_ki				//BitC_CL : BitCKernel Indicator Index Enumeration
{
	BitCEndianD16=1,		//BitC_CL : BitCKernel[BitCEndianD16]="BitC_Endian_D16_"
	BitCEndianD32=2,		//BitC_CL : BitCKernel[BitCEndianD32]="BitC_Endian_D32_"
	BitCEndianD64=3,		//BitC_CL : BitCKernel[BitCEndianD64]="BitC_Endian_D64_"
	BitCCasterD08D16=5,		//BitC_CL : BitCKernel[BitCCasterD08D16]="BitC_Caster_D08_D16_"
	BitCCasterD08D32=6,		//BitC_CL : BitCKernel[BitCCasterD08D32]="BitC_Caster_D08_D32_"
	BitCCasterD08D64=7,		//BitC_CL : BitCKernel[BitCCasterD08D64]="BitC_Caster_D08_D64_"
	BitCCasterD08I08=8,		//BitC_CL : BitCKernel[BitCCasterD08I08]="BitC_Caster_D08_I08_"
	BitCCasterD08R16=13,	//BitC_CL : BitCKernel[BitCCasterD08R16]="BitC_Caster_D08_R16_"
	BitCCasterD08R32=14,	//BitC_CL : BitCKernel[BitCCasterD08R32]="BitC_Caster_D08_R32_"
	BitCCasterD08R64=15,	//BitC_CL : BitCKernel[BitCCasterD08R64]="BitC_Caster_D08_R64_"
	BitCCasterD16D08=16,	//BitC_CL : BitCKernel[BitCCasterD16D08]="BitC_Caster_D16_D08_"
	BitCCasterD16D32=18,	//BitC_CL : BitCKernel[BitCCasterD16D32]="BitC_Caster_D16_D32_"
	BitCCasterD16D64=19,	//BitC_CL : BitCKernel[BitCCasterD16D64]="BitC_Caster_D16_D64_"
	BitCCasterD16I08=20,	//BitC_CL : BitCKernel[BitCCasterD16I08]="BitC_Caster_D16_I08_"
	BitCCasterD16I16=21,	//BitC_CL : BitCKernel[BitCCasterD16I16]="BitC_Caster_D16_I16_"
	BitCCasterD16R16=25,	//BitC_CL : BitCKernel[BitCCasterD16R16]="BitC_Caster_D16_R16_"
	BitCCasterD16R32=26,	//BitC_CL : BitCKernel[BitCCasterD16R32]="BitC_Caster_D16_R32_"
	BitCCasterD16R64=27,	//BitC_CL : BitCKernel[BitCCasterD16R64]="BitC_Caster_D16_R64_"
	BitCCasterD32D08=28,	//BitC_CL : BitCKernel[BitCCasterD32D08]="BitC_Caster_D32_D08_"
	BitCCasterD32D16=29,	//BitC_CL : BitCKernel[BitCCasterD32D16]="BitC_Caster_D32_D16_"
	BitCCasterD32D64=31,	//BitC_CL : BitCKernel[BitCCasterD32D64]="BitC_Caster_D32_D64_"
	BitCCasterD32I08=32,	//BitC_CL : BitCKernel[BitCCasterD32I08]="BitC_Caster_D32_I08_"
	BitCCasterD32I16=33,	//BitC_CL : BitCKernel[BitCCasterD32I16]="BitC_Caster_D32_I16_"
	BitCCasterD32I32=34,	//BitC_CL : BitCKernel[BitCCasterD32I32]="BitC_Caster_D32_I32_"
	BitCCasterD32R16=37,	//BitC_CL : BitCKernel[BitCCasterD32R16]="BitC_Caster_D32_R16_"
	BitCCasterD32R32=38,	//BitC_CL : BitCKernel[BitCCasterD32R32]="BitC_Caster_D32_R32_"
	BitCCasterD32R64=39,	//BitC_CL : BitCKernel[BitCCasterD32R64]="BitC_Caster_D32_R64_"
	BitCCasterD64D08=40,	//BitC_CL : BitCKernel[BitCCasterD64D08]="BitC_Caster_D64_D08_"
	BitCCasterD64D16=41,	//BitC_CL : BitCKernel[BitCCasterD64D16]="BitC_Caster_D64_D16_"
	BitCCasterD64D32=42,	//BitC_CL : BitCKernel[BitCCasterD64D32]="BitC_Caster_D64_D32_"
	BitCCasterD64I08=44,	//BitC_CL : BitCKernel[BitCCasterD64I08]="BitC_Caster_D64_I08_"
	BitCCasterD64I16=45,	//BitC_CL : BitCKernel[BitCCasterD64I16]="BitC_Caster_D64_I16_"
	BitCCasterD64I32=46,	//BitC_CL : BitCKernel[BitCCasterD64I32]="BitC_Caster_D64_I32_"
	BitCCasterD64I64=47,	//BitC_CL : BitCKernel[BitCCasterD64I64]="BitC_Caster_D64_I64_"
	BitCCasterD64R16=49,	//BitC_CL : BitCKernel[BitCCasterD64R16]="BitC_Caster_D64_R16_"
	BitCCasterD64R32=50,	//BitC_CL : BitCKernel[BitCCasterD64R32]="BitC_Caster_D64_R32_"
	BitCCasterD64R64=51,	//BitC_CL : BitCKernel[BitCCasterD64R64]="BitC_Caster_D64_R64_"
	BitCCasterI08D08=52,	//BitC_CL : BitCKernel[BitCCasterI08D08]="BitC_Caster_I08_D08_"
	BitCCasterI08D16=53,	//BitC_CL : BitCKernel[BitCCasterI08D16]="BitC_Caster_I08_D16_"
	BitCCasterI08D32=54,	//BitC_CL : BitCKernel[BitCCasterI08D32]="BitC_Caster_I08_D32_"
	BitCCasterI08D64=55,	//BitC_CL : BitCKernel[BitCCasterI08D64]="BitC_Caster_I08_D64_"
	BitCCasterI08I16=57,	//BitC_CL : BitCKernel[BitCCasterI08I16]="BitC_Caster_I08_I16_"
	BitCCasterI08I32=58,	//BitC_CL : BitCKernel[BitCCasterI08I32]="BitC_Caster_I08_I32_"
	BitCCasterI08I64=59,	//BitC_CL : BitCKernel[BitCCasterI08I64]="BitC_Caster_I08_I64_"
	BitCCasterI08R16=61,	//BitC_CL : BitCKernel[BitCCasterI08R16]="BitC_Caster_I08_R16_"
	BitCCasterI08R32=62,	//BitC_CL : BitCKernel[BitCCasterI08R32]="BitC_Caster_I08_R32_"
	BitCCasterI08R64=63,	//BitC_CL : BitCKernel[BitCCasterI08R64]="BitC_Caster_I08_R64_"
	BitCCasterI16D08=64,	//BitC_CL : BitCKernel[BitCCasterI16D08]="BitC_Caster_I16_D08_"
	BitCCasterI16D16=65,	//BitC_CL : BitCKernel[BitCCasterI16D16]="BitC_Caster_I16_D16_"
	BitCCasterI16D32=66,	//BitC_CL : BitCKernel[BitCCasterI16D32]="BitC_Caster_I16_D32_"
	BitCCasterI16D64=67,	//BitC_CL : BitCKernel[BitCCasterI16D64]="BitC_Caster_I16_D64_"
	BitCCasterI16I08=68,	//BitC_CL : BitCKernel[BitCCasterI16I08]="BitC_Caster_I16_I08_"
	BitCCasterI16I32=70,	//BitC_CL : BitCKernel[BitCCasterI16I32]="BitC_Caster_I16_I32_"
	BitCCasterI16I64=71,	//BitC_CL : BitCKernel[BitCCasterI16I64]="BitC_Caster_I16_I64_"
	BitCCasterI16R16=73,	//BitC_CL : BitCKernel[BitCCasterI16R16]="BitC_Caster_I16_R16_"
	BitCCasterI16R32=74,	//BitC_CL : BitCKernel[BitCCasterI16R32]="BitC_Caster_I16_R32_"
	BitCCasterI16R64=75,	//BitC_CL : BitCKernel[BitCCasterI16R64]="BitC_Caster_I16_R64_"
	BitCCasterI32D08=76,	//BitC_CL : BitCKernel[BitCCasterI32D08]="BitC_Caster_I32_D08_"
	BitCCasterI32D16=77,	//BitC_CL : BitCKernel[BitCCasterI32D16]="BitC_Caster_I32_D16_"
	BitCCasterI32D32=78,	//BitC_CL : BitCKernel[BitCCasterI32D32]="BitC_Caster_I32_D32_"
	BitCCasterI32D64=79,	//BitC_CL : BitCKernel[BitCCasterI32D64]="BitC_Caster_I32_D64_"
	BitCCasterI32I08=80,	//BitC_CL : BitCKernel[BitCCasterI32I08]="BitC_Caster_I32_I08_"
	BitCCasterI32I16=81,	//BitC_CL : BitCKernel[BitCCasterI32I16]="BitC_Caster_I32_I16_"
	BitCCasterI32I64=83,	//BitC_CL : BitCKernel[BitCCasterI32I64]="BitC_Caster_I32_I64_"
	BitCCasterI32R16=85,	//BitC_CL : BitCKernel[BitCCasterI32R16]="BitC_Caster_I32_R16_"
	BitCCasterI32R32=86,	//BitC_CL : BitCKernel[BitCCasterI32R32]="BitC_Caster_I32_R32_"
	BitCCasterI32R64=87,	//BitC_CL : BitCKernel[BitCCasterI32R64]="BitC_Caster_I32_R64_"
	BitCCasterI64D08=88,	//BitC_CL : BitCKernel[BitCCasterI64D08]="BitC_Caster_I64_D08_"
	BitCCasterI64D16=89,	//BitC_CL : BitCKernel[BitCCasterI64D16]="BitC_Caster_I64_D16_"
	BitCCasterI64D32=90,	//BitC_CL : BitCKernel[BitCCasterI64D32]="BitC_Caster_I64_D32_"
	BitCCasterI64D64=91,	//BitC_CL : BitCKernel[BitCCasterI64D64]="BitC_Caster_I64_D64_"
	BitCCasterI64I08=92,	//BitC_CL : BitCKernel[BitCCasterI64I08]="BitC_Caster_I64_I08_"
	BitCCasterI64I16=93,	//BitC_CL : BitCKernel[BitCCasterI64I16]="BitC_Caster_I64_I16_"
	BitCCasterI64I32=94,	//BitC_CL : BitCKernel[BitCCasterI64I32]="BitC_Caster_I64_I32_"
	BitCCasterI64R16=97,	//BitC_CL : BitCKernel[BitCCasterI64R16]="BitC_Caster_I64_R16_"
	BitCCasterI64R32=98,	//BitC_CL : BitCKernel[BitCCasterI64R32]="BitC_Caster_I64_R32_"
	BitCCasterI64R64=99,	//BitC_CL : BitCKernel[BitCCasterI64R64]="BitC_Caster_I64_R64_"
	BitCCasterR16D08=112,	//BitC_CL : BitCKernel[BitCCasterR16D08]="BitC_Caster_R16_D08_"
	BitCCasterR16D16=113,	//BitC_CL : BitCKernel[BitCCasterR16D16]="BitC_Caster_R16_D16_"
	BitCCasterR16D32=114,	//BitC_CL : BitCKernel[BitCCasterR16D32]="BitC_Caster_R16_D32_"
	BitCCasterR16D64=115,	//BitC_CL : BitCKernel[BitCCasterR16D64]="BitC_Caster_R16_D64_"
	BitCCasterR16I08=116,	//BitC_CL : BitCKernel[BitCCasterR16I08]="BitC_Caster_R16_I08_"
	BitCCasterR16I16=117,	//BitC_CL : BitCKernel[BitCCasterR16I16]="BitC_Caster_R16_I16_"
	BitCCasterR16I32=118,	//BitC_CL : BitCKernel[BitCCasterR16I32]="BitC_Caster_R16_I32_"
	BitCCasterR16I64=119,	//BitC_CL : BitCKernel[BitCCasterR16I64]="BitC_Caster_R16_I64_"
	BitCCasterR16R32=122,	//BitC_CL : BitCKernel[BitCCasterR16R32]="BitC_Caster_R16_R32_"
	BitCCasterR16R64=123,	//BitC_CL : BitCKernel[BitCCasterR16R64]="BitC_Caster_R16_R64_"
	BitCCasterR32D08=124,	//BitC_CL : BitCKernel[BitCCasterR32D08]="BitC_Caster_R32_D08_"
	BitCCasterR32D16=125,	//BitC_CL : BitCKernel[BitCCasterR32D16]="BitC_Caster_R32_D16_"
	BitCCasterR32D32=126,	//BitC_CL : BitCKernel[BitCCasterR32D32]="BitC_Caster_R32_D32_"
	BitCCasterR32D64=127,	//BitC_CL : BitCKernel[BitCCasterR32D64]="BitC_Caster_R32_D64_"
	BitCCasterR32I08=128,	//BitC_CL : BitCKernel[BitCCasterR32I08]="BitC_Caster_R32_I08_"
	BitCCasterR32I16=129,	//BitC_CL : BitCKernel[BitCCasterR32I16]="BitC_Caster_R32_I16_"
	BitCCasterR32I32=130,	//BitC_CL : BitCKernel[BitCCasterR32I32]="BitC_Caster_R32_I32_"
	BitCCasterR32I64=131,	//BitC_CL : BitCKernel[BitCCasterR32I64]="BitC_Caster_R32_I64_"
	BitCCasterR32R16=133,	//BitC_CL : BitCKernel[BitCCasterR32R16]="BitC_Caster_R32_R16_"
	BitCCasterR32R64=135,	//BitC_CL : BitCKernel[BitCCasterR32R64]="BitC_Caster_R32_R64_"
	BitCCasterR64D08=136,	//BitC_CL : BitCKernel[BitCCasterR64D08]="BitC_Caster_R64_D08_"
	BitCCasterR64D16=137,	//BitC_CL : BitCKernel[BitCCasterR64D16]="BitC_Caster_R64_D16_"
	BitCCasterR64D32=138,	//BitC_CL : BitCKernel[BitCCasterR64D32]="BitC_Caster_R64_D32_"
	BitCCasterR64D64=139,	//BitC_CL : BitCKernel[BitCCasterR64D64]="BitC_Caster_R64_D64_"
	BitCCasterR64I08=140,	//BitC_CL : BitCKernel[BitCCasterR64I08]="BitC_Caster_R64_I08_"
	BitCCasterR64I16=141,	//BitC_CL : BitCKernel[BitCCasterR64I16]="BitC_Caster_R64_I16_"
	BitCCasterR64I32=142,	//BitC_CL : BitCKernel[BitCCasterR64I32]="BitC_Caster_R64_I32_"
	BitCCasterR64I64=143,	//BitC_CL : BitCKernel[BitCCasterR64I64]="BitC_Caster_R64_I64_"
	BitCCasterR64R16=145,	//BitC_CL : BitCKernel[BitCCasterR64R16]="BitC_Caster_R64_R16_"
	BitCCasterR64R32=146,	//BitC_CL : BitCKernel[BitCCasterR64R32]="BitC_Caster_R64_R32_"
	BitCBON1D08=148,		//BitC_CL : BitCKernel[BitCBON1D08]="BitC_BO_N_1_D08_"
	BitCBOA2D08=149,		//BitC_CL : BitCKernel[BitCBOA2D08]="BitC_BO_A_2_D08_"
	BitCBOO2D08=150,		//BitC_CL : BitCKernel[BitCBOO2D08]="BitC_BO_O_2_D08_"
	BitCBOX2D08=151,		//BitC_CL : BitCKernel[BitCBOX2D08]="BitC_BO_X_2_D08_"
	BitCBOA1D08=152,		//BitC_CL : BitCKernel[BitCBOA1D08]="BitC_BO_A_1_D08_"
	BitCBOA1D16=153,		//BitC_CL : BitCKernel[BitCBOA1D16]="BitC_BO_A_1_D16_"
	BitCBOA1D32=154,		//BitC_CL : BitCKernel[BitCBOA1D32]="BitC_BO_A_1_D32_"
	BitCBOA1D64=155,		//BitC_CL : BitCKernel[BitCBOA1D64]="BitC_BO_A_1_D64_"
	BitCBOO1D08=156,		//BitC_CL : BitCKernel[BitCBOO1D08]="BitC_BO_O_1_D08_"
	BitCBOO1D16=157,		//BitC_CL : BitCKernel[BitCBOO1D16]="BitC_BO_O_1_D16_"
	BitCBOO1D32=158,		//BitC_CL : BitCKernel[BitCBOO1D32]="BitC_BO_O_1_D32_"
	BitCBOO1D64=159,		//BitC_CL : BitCKernel[BitCBOO1D64]="BitC_BO_O_1_D64_"
	BitCBOX1D08=160,		//BitC_CL : BitCKernel[BitCBOX1D08]="BitC_BO_X_1_D08_"
	BitCBOX1D16=161,		//BitC_CL : BitCKernel[BitCBOX1D16]="BitC_BO_X_1_D16_"
	BitCBOX1D32=162,		//BitC_CL : BitCKernel[BitCBOX1D32]="BitC_BO_X_1_D32_"
	BitCBOX1D64=163,		//BitC_CL : BitCKernel[BitCBOX1D64]="BitC_BO_X_1_D64_"
	BitCBOS1D08=164,		//BitC_CL : BitCKernel[BitCBOS1D08]="BitC_BO_S_1_D08_"
	BitCBOS1D16=165,		//BitC_CL : BitCKernel[BitCBOS1D16]="BitC_BO_S_1_D16_"
	BitCBOS1D32=166,		//BitC_CL : BitCKernel[BitCBOS1D32]="BitC_BO_S_1_D32_"
	BitCBOS1D64=167,		//BitC_CL : BitCKernel[BitCBOS1D64]="BitC_BO_S_1_D64_"
	BitCBOS1I08=168,		//BitC_CL : BitCKernel[BitCBOS1I08]="BitC_BO_S_1_I08_"
	BitCBOS1I16=169,		//BitC_CL : BitCKernel[BitCBOS1I16]="BitC_BO_S_1_I16_"
	BitCBOS1I32=170,		//BitC_CL : BitCKernel[BitCBOS1I32]="BitC_BO_S_1_I32_"
	BitCBOS1I64=171,		//BitC_CL : BitCKernel[BitCBOS1I64]="BitC_BO_S_1_I64_"
	BitCExpandD08=172,		//BitC_CL : BitCKernel[BitCExpandD08]="BitC_Expand_D08_"
	BitCExpandD16=173,		//BitC_CL : BitCKernel[BitCExpandD16]="BitC_Expand_D16_"
	BitCExpandD32=174,		//BitC_CL : BitCKernel[BitCExpandD32]="BitC_Expand_D32_"
	BitCExpandD64=175,		//BitC_CL : BitCKernel[BitCExpandD64]="BitC_Expand_D64_"
	BitCShrinkD08=176,		//BitC_CL : BitCKernel[BitCShrinkD08]="BitC_Shrink_D08_"
	BitCShrinkD16=177,		//BitC_CL : BitCKernel[BitCShrinkD16]="BitC_Shrink_D16_"
	BitCShrinkD32=178,		//BitC_CL : BitCKernel[BitCShrinkD32]="BitC_Shrink_D32_"
	BitCShrinkD64=179,		//BitC_CL : BitCKernel[BitCShrinkD64]="BitC_Shrink_D64_"
	BitCROE1D08=180,		//BitC_CL : BitCKernel[BitCROE1D08]="BitC_RO_E_1_D08_"
	BitCROE1D16=181,		//BitC_CL : BitCKernel[BitCROE1D16]="BitC_RO_E_1_D16_"
	BitCROE1D32=182,		//BitC_CL : BitCKernel[BitCROE1D32]="BitC_RO_E_1_D32_"
	BitCROE1D64=183,		//BitC_CL : BitCKernel[BitCROE1D64]="BitC_RO_E_1_D64_"
	BitCRON1D08=184,		//BitC_CL : BitCKernel[BitCRON1D08]="BitC_RO_N_1_D08_"
	BitCRON1D16=185,		//BitC_CL : BitCKernel[BitCRON1D16]="BitC_RO_N_1_D16_"
	BitCRON1D32=186,		//BitC_CL : BitCKernel[BitCRON1D32]="BitC_RO_N_1_D32_"
	BitCRON1D64=187,		//BitC_CL : BitCKernel[BitCRON1D64]="BitC_RO_N_1_D64_"
	BitCROG1D08=188,		//BitC_CL : BitCKernel[BitCROG1D08]="BitC_RO_G_1_D08_"
	BitCROG1D16=189,		//BitC_CL : BitCKernel[BitCROG1D16]="BitC_RO_G_1_D16_"
	BitCROG1D32=190,		//BitC_CL : BitCKernel[BitCROG1D32]="BitC_RO_G_1_D32_"
	BitCROG1D64=191,		//BitC_CL : BitCKernel[BitCROG1D64]="BitC_RO_G_1_D64_"
	BitCROG1I08=192,		//BitC_CL : BitCKernel[BitCROG1I08]="BitC_RO_G_1_I08_"
	BitCROG1I16=193,		//BitC_CL : BitCKernel[BitCROG1I16]="BitC_RO_G_1_I16_"
	BitCROG1I32=194,		//BitC_CL : BitCKernel[BitCROG1I32]="BitC_RO_G_1_I32_"
	BitCROG1I64=195,		//BitC_CL : BitCKernel[BitCROG1I64]="BitC_RO_G_1_I64_"
	BitCROG1R16=197,		//BitC_CL : BitCKernel[BitCROG1R16]="BitC_RO_G_1_R16_"
	BitCROG1R32=198,		//BitC_CL : BitCKernel[BitCROG1R32]="BitC_RO_G_1_R32_"
	BitCROG1R64=199,		//BitC_CL : BitCKernel[BitCROG1R64]="BitC_RO_G_1_R64_"
	BitCROL1D08=200,		//BitC_CL : BitCKernel[BitCROL1D08]="BitC_RO_L_1_D08_"
	BitCROL1D16=201,		//BitC_CL : BitCKernel[BitCROL1D16]="BitC_RO_L_1_D16_"
	BitCROL1D32=202,		//BitC_CL : BitCKernel[BitCROL1D32]="BitC_RO_L_1_D32_"
	BitCROL1D64=203,		//BitC_CL : BitCKernel[BitCROL1D64]="BitC_RO_L_1_D64_"
	BitCROL1I08=204,		//BitC_CL : BitCKernel[BitCROL1I08]="BitC_RO_L_1_I08_"
	BitCROL1I16=205,		//BitC_CL : BitCKernel[BitCROL1I16]="BitC_RO_L_1_I16_"
	BitCROL1I32=206,		//BitC_CL : BitCKernel[BitCROL1I32]="BitC_RO_L_1_I32_"
	BitCROL1I64=207,		//BitC_CL : BitCKernel[BitCROL1I64]="BitC_RO_L_1_I64_"
	BitCROL1R16=209,		//BitC_CL : BitCKernel[BitCROL1R16]="BitC_RO_L_1_R16_"
	BitCROL1R32=210,		//BitC_CL : BitCKernel[BitCROL1R32]="BitC_RO_L_1_R32_"
	BitCROL1R64=211,		//BitC_CL : BitCKernel[BitCROL1R64]="BitC_RO_L_1_R64_"
	BitCROE2D08=212,		//BitC_CL : BitCKernel[BitCROE2D08]="BitC_RO_E_2_D08_"
	BitCROE2D16=213,		//BitC_CL : BitCKernel[BitCROE2D16]="BitC_RO_E_2_D16_"
	BitCROE2D32=214,		//BitC_CL : BitCKernel[BitCROE2D32]="BitC_RO_E_2_D32_"
	BitCROE2D64=215,		//BitC_CL : BitCKernel[BitCROE2D64]="BitC_RO_E_2_D64_"
	BitCRON2D08=216,		//BitC_CL : BitCKernel[BitCRON2D08]="BitC_RO_N_2_D08_"
	BitCRON2D16=217,		//BitC_CL : BitCKernel[BitCRON2D16]="BitC_RO_N_2_D16_"
	BitCRON2D32=218,		//BitC_CL : BitCKernel[BitCRON2D32]="BitC_RO_N_2_D32_"
	BitCRON2D64=219,		//BitC_CL : BitCKernel[BitCRON2D64]="BitC_RO_N_2_D64_"
	BitCROG2D08=220,		//BitC_CL : BitCKernel[BitCROG2D08]="BitC_RO_G_2_D08_"
	BitCROG2D16=221,		//BitC_CL : BitCKernel[BitCROG2D16]="BitC_RO_G_2_D16_"
	BitCROG2D32=222,		//BitC_CL : BitCKernel[BitCROG2D32]="BitC_RO_G_2_D32_"
	BitCROG2D64=223,		//BitC_CL : BitCKernel[BitCROG2D64]="BitC_RO_G_2_D64_"
	BitCROG2I08=224,		//BitC_CL : BitCKernel[BitCROG2I08]="BitC_RO_G_2_I08_"
	BitCROG2I16=225,		//BitC_CL : BitCKernel[BitCROG2I16]="BitC_RO_G_2_I16_"
	BitCROG2I32=226,		//BitC_CL : BitCKernel[BitCROG2I32]="BitC_RO_G_2_I32_"
	BitCROG2I64=227,		//BitC_CL : BitCKernel[BitCROG2I64]="BitC_RO_G_2_I64_"
	BitCROG2R16=229,		//BitC_CL : BitCKernel[BitCROG2R16]="BitC_RO_G_2_R16_"
	BitCROG2R32=230,		//BitC_CL : BitCKernel[BitCROG2R32]="BitC_RO_G_2_R32_"
	BitCROG2R64=231,		//BitC_CL : BitCKernel[BitCROG2R64]="BitC_RO_G_2_R64_"
	BitCROL2D08=232,		//BitC_CL : BitCKernel[BitCROL2D08]="BitC_RO_L_2_D08_"
	BitCROL2D16=233,		//BitC_CL : BitCKernel[BitCROL2D16]="BitC_RO_L_2_D16_"
	BitCROL2D32=234,		//BitC_CL : BitCKernel[BitCROL2D32]="BitC_RO_L_2_D32_"
	BitCROL2D64=235,		//BitC_CL : BitCKernel[BitCROL2D64]="BitC_RO_L_2_D64_"
	BitCROL2I08=236,		//BitC_CL : BitCKernel[BitCROL2I08]="BitC_RO_L_2_I08_"
	BitCROL2I16=237,		//BitC_CL : BitCKernel[BitCROL2I16]="BitC_RO_L_2_I16_"
	BitCROL2I32=238,		//BitC_CL : BitCKernel[BitCROL2I32]="BitC_RO_L_2_I32_"
	BitCROL2I64=239,		//BitC_CL : BitCKernel[BitCROL2I64]="BitC_RO_L_2_I64_"
	BitCROL2R16=241,		//BitC_CL : BitCKernel[BitCROL2R16]="BitC_RO_L_2_R16_"
	BitCROL2R32=242,		//BitC_CL : BitCKernel[BitCROL2R32]="BitC_RO_L_2_R32_"
	BitCROL2R64=243			//BitC_CL : BitCKernel[BitCROL2R64]="BitC_RO_L_2_R64_"
};
typedef enum _bitc_ki bitc_ki;			//BitC_CL : BitCKernel Indicator Index Variable
typedef const enum _bitc_ki BITC_KI;	//BitC_CL : BitCKernel Indicator Index Constant
#endif
#endif

#if(MemC_Fold_(Definition:Macros))
#define Inte_Max_08_(Output,InputA,InputB) {(Output)=(InputB)-(InputA);(Output)&=(((inte_08)(Output))>>7);(Output)=(InputB)-(Output);}													//BitClip : Maximum of 8-bit Integer - Only valid for Data Range under 0x40
#define Inte_Max_16_(Output,InputA,InputB) {(Output)=(InputB)-(InputA);(Output)&=(((inte_16)(Output))>>15);(Output)=(InputB)-(Output);}													//BitClip : Maximum of 16-bit Integer - Only valid for Data Range under 0x4000
#define Inte_Max_32_(Output,InputA,InputB) {(Output)=(InputB)-(InputA);(Output)&=(((inte_32)(Output))>>31);(Output)=(InputB)-(Output);}													//BitClip : Maximum of 32-bit Integer - Only valid for Data Range under 0x40000000
#define Inte_Max_64_(Output,InputA,InputB) {(Output)=(InputB)-(InputA);(Output)&=(((inte_64)(Output))>>63);(Output)=(InputB)-(Output);}													//BitClip : Maximum of 64-bit Integer - Only valid for Data Range under 0x4000000000000000

#define Inte_Min_08_(Output,InputA,InputB) {(Output)=(InputA)-(InputB);(Output)&=(((inte_08)(Output))>>7);(Output)+=(InputB);}															//BitClip : Minimum of 8-bit Integer - Only valid for Data Range under 0x40
#define Inte_Min_16_(Output,InputA,InputB) {(Output)=(InputA)-(InputB);(Output)&=(((inte_16)(Output))>>15);(Output)+=(InputB);}															//BitClip : Minimum of 16-bit Integer - Only valid for Data Range under 0x4000
#define Inte_Min_32_(Output,InputA,InputB) {(Output)=(InputA)-(InputB);(Output)&=(((inte_32)(Output))>>31);(Output)+=(InputB);}															//BitClip : Minimum of 32-bit Integer - Only valid for Data Range under 0x40000000
#define Inte_Min_64_(Output,InputA,InputB) {(Output)=(InputA)-(InputB);(Output)&=(((inte_64)(Output))>>63);(Output)+=(InputB);}															//BitClip : Minimum of 64-bit Integer - Only valid for Data Range under 0x4000000000000000

#define Inte_Abs_08_Positive_(Output,Input) {(Output)=((inte_08)(Input))>>7;(Output)^=((Input)+(Output));}																				//BitClip : Positive Absolute of 8-bit Integer
#define Inte_Abs_16_Positive_(Output,Input) {(Output)=((inte_16)(Input))>>15;(Output)^=((Input)+(Output));}																				//BitClip : Positive Absolute of 16-bit Integer
#define Inte_Abs_32_Positive_(Output,Input) {(Output)=((inte_32)(Input))>>31;(Output)^=((Input)+(Output));}																				//BitClip : Positive Absolute of 32-bit Integer
#define Inte_Abs_64_Positive_(Output,Input) {(Output)=((inte_64)(Input))>>63;(Output)^=((Input)+(Output));}																				//BitClip : Positive Absolute of 64-bit Integer

#define Inte_Abs_08_Negative_(Output,Input) {(Output)=((inte_08)(Input))>>7;(Output)=~(Output);(Output)^=((Input)+(Output));}															//BitClip : Negative Absolute of 8-bit Integer
#define Inte_Abs_16_Negative_(Output,Input) {(Output)=((inte_16)(Input))>>15;(Output)=~(Output);(Output)^=((Input)+(Output));}															//BitClip : Negative Absolute of 16-bit Integer
#define Inte_Abs_32_Negative_(Output,Input) {(Output)=((inte_32)(Input))>>31;(Output)=~(Output);(Output)^=((Input)+(Output));}															//BitClip : Negative Absolute of 32-bit Integer
#define Inte_Abs_64_Negative_(Output,Input) {(Output)=((inte_64)(Input))>>63;(Output)=~(Output);(Output)^=((Input)+(Output));}															//BitClip : Negative Absolute of 64-bit Integer

#define Inte_Lim_08_Positive_(Output,Input) {(Output)=((inte_08)(Input))>>7;(Output)=~(Output);(Output)&=(Input);}																		//BitClip : Positive Clipping of 8-bit Integer
#define Inte_Lim_16_Positive_(Output,Input) {(Output)=((inte_16)(Input))>>15;(Output)=~(Output);(Output)&=(Input);}																		//BitClip : Positive Clipping of 16-bit Integer
#define Inte_Lim_32_Positive_(Output,Input) {(Output)=((inte_32)(Input))>>31;(Output)=~(Output);(Output)&=(Input);}																		//BitClip : Positive Clipping of 32-bit Integer
#define Inte_Lim_64_Positive_(Output,Input) {(Output)=((inte_64)(Input))>>63;(Output)=~(Output);(Output)&=(Input);}																		//BitClip : Positive Clipping of 64-bit Integer

#define Inte_Lim_08_Negative_(Output,Input) {(Output)=((inte_08)(Input))>>7;(Output)&=(Input);}																							//BitClip : Negative Clipping of 8-bit Integer
#define Inte_Lim_16_Negative_(Output,Input) {(Output)=((inte_16)(Input))>>15;(Output)&=(Input);}																						//BitClip : Negative Clipping of 16-bit Integer
#define Inte_Lim_32_Negative_(Output,Input) {(Output)=((inte_32)(Input))>>31;(Output)&=(Input);}																						//BitClip : Negative Clipping of 32-bit Integer
#define Inte_Lim_64_Negative_(Output,Input) {(Output)=((inte_64)(Input))>>63;(Output)&=(Input);}																						//BitClip : Negative Clipping of 64-bit Integer

#define Real_Max_32_(Output,InputA,InputB) {(Output)=(InputB)-(InputA);(*(inte_32*)&(Output))&=((*(inte_32*)&(Output))>>31);(Output)=(InputB)-(Output);}								//BitClip : Maximum of 32-bit Real
#define Real_Max_64_(Output,InputA,InputB) {(Output)=(InputB)-(InputA);(*(inte_64*)&(Output))&=((*(inte_64*)&(Output))>>63);(Output)=(InputB)-(Output);}								//BitClip : Maximum of 64-bit Real

#define Real_Min_32_(Output,InputA,InputB) {(Output)=(InputA)-(InputB);(*(inte_32*)&(Output))&=((*(inte_32*)&(Output))>>31);(Output)+=(InputB);}										//BitClip : Minimum of 32-bit Real
#define Real_Min_64_(Output,InputA,InputB) {(Output)=(InputA)-(InputB);(*(inte_64*)&(Output))&=((*(inte_64*)&(Output))>>63);(Output)+=(InputB);}										//BitClip : Minimum of 64-bit Real

#define Real_Abs_32_Positive_(Output,Input) {*(inte_32*)&(Output)=(*(inte_32*)&(Input))&0x7FFFFFFF;}																					//BitClip : Positive Absolute of 32-bit Real
#define Real_Abs_64_Positive_(Output,Input) {*(inte_64*)&(Output)=(*(inte_64*)&(Input))&0x7FFFFFFFFFFFFFFF;}																			//BitClip : Positive Absolute of 64-bit Real

#define Real_Abs_32_Negative_(Output,Input) {*(inte_32*)&(Output)=(*(inte_32*)&(Input))|0x80000000;}																					//BitClip : Negative Absolute of 32-bit Real
#define Real_Abs_64_Negative_(Output,Input) {*(inte_64*)&(Output)=(*(inte_64*)&(Input))|0x8000000000000000;}																			//BitClip : Negative Absolute of 64-bit Real

#define Real_Lim_32_Positive_(Output,Input) {*(inte_32*)&(Output)=(*(inte_32*)&(Input))>>31;*(inte_32*)&(Output)=~(*(inte_32*)&(Output));*(inte_32*)&(Output)&=(*(inte_32*)&(Input));}	//BitClip : Positive Clipping of 32-bit Real
#define Real_Lim_64_Positive_(Output,Input) {*(inte_64*)&(Output)=(*(inte_64*)&(Input))>>63;*(inte_64*)&(Output)=~(*(inte_64*)&(Output));*(inte_64*)&(Output)&=(*(inte_64*)&(Input));}	//BitClip : Positive Clipping of 64-bit Real

#define Real_Lim_32_Negative_(Output,Input) {*(inte_32*)&(Output)=(*(inte_32*)&(Input))>>31;*(inte_32*)&(Output)&=(*(inte_32*)&(Input));}												//BitClip : Negative Clipping of 32-bit Real
#define Real_Lim_64_Negative_(Output,Input) {*(inte_64*)&(Output)=(*(inte_64*)&(Input))>>63;*(inte_64*)&(Output)&=(*(inte_64*)&(Input));}												//BitClip : Negative Clipping of 64-bit Real

#define Func_Declare_V_(Return,Func_,...) Return (*Func_)(__VA_ARGS__)																													//BitClip : Function Pointer Variable Declaration
#define Func_Declare_C_(Return,Func_,...) Return (_PL_ Func_)(__VA_ARGS__)																												//BitClip : Function Pointer Constant Declaration
#define Func_Casting_(Return,Func_,...) (Return(*)(__VA_ARGS__))(Func_)																													//BitClip : Function Pointer Casting

#ifdef __OPENCL_H
#define BitC_Worker_KM_Expand_ BitC_Worker_KM_Caster_	//BitC_CL : Renamed Function
#define BitC_Worker_KM_Shrink_ BitC_Worker_KM_Caster_	//BitC_CL : Renamed Function

#define BitC_Worker_KM_BO_A_1_ BitC_Worker_KM_Op_M_1_	//BitC_CL : Renamed Function
#define BitC_Worker_KM_BO_O_1_ BitC_Worker_KM_Op_M_1_	//BitC_CL : Renamed Function
#define BitC_Worker_KM_BO_X_1_ BitC_Worker_KM_Op_M_1_	//BitC_CL : Renamed Function
#define BitC_Worker_KM_RO_E_1_ BitC_Worker_KM_Op_M_1_	//BitC_CL : Renamed Function
#define BitC_Worker_KM_RO_N_1_ BitC_Worker_KM_Op_M_1_	//BitC_CL : Renamed Function
#define BitC_Worker_KM_RO_G_1_ BitC_Worker_KM_Op_M_1_	//BitC_CL : Renamed Function
#define BitC_Worker_KM_RO_L_1_ BitC_Worker_KM_Op_M_1_	//BitC_CL : Renamed Function

#define BitC_Worker_KM_BO_A_2_ BitC_Worker_KM_Op_M_2_	//BitC_CL : Renamed Function
#define BitC_Worker_KM_BO_O_2_ BitC_Worker_KM_Op_M_2_	//BitC_CL : Renamed Function
#define BitC_Worker_KM_BO_X_2_ BitC_Worker_KM_Op_M_2_	//BitC_CL : Renamed Function
#define BitC_Worker_KM_RO_E_2_ BitC_Worker_KM_Op_M_2_	//BitC_CL : Renamed Function
#define BitC_Worker_KM_RO_N_2_ BitC_Worker_KM_Op_M_2_	//BitC_CL : Renamed Function
#define BitC_Worker_KM_RO_G_2_ BitC_Worker_KM_Op_M_2_	//BitC_CL : Renamed Function
#define BitC_Worker_KM_RO_L_2_ BitC_Worker_KM_Op_M_2_	//BitC_CL : Renamed Function
#endif
#endif

#if(MemC_Fold_(Declaration:Global Constants))
//BitClip : Library Version
extern DATA_08 _PL_ BitClip;

//BitClip : Endianness
//＊Pointed value is 0x00 for big-endian, 0x01 for little-endian.
extern volatile DATA_08 _PL_ BitCEndian;

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

#ifdef __OPENCL_H
//BitC_CL : OpenCL Source File Name Set
//＊[0] : "bitclip_h.cl"
//　[1] : "bitclip_c.cl"
extern NAME_08 _PL_ _PL_ BitCFile;
//BitC_CL : OpenCL Kernel Indicator Set
extern NAME_08 _PL_ _PL_ BitCKernel;
#endif
#endif

#if(MemC_Fold_(Declaration:KM Functions))
#ifdef __OPENCL_H
//BitC_CL : Kernel Manager Memory Allocation - Deallocate with "Devi_KM_Delete_"
devi_km *BitC_Create_KM_(cl_kernel const);

//BitC_CL : Setting Kernel Manager's Local Workers and Work Groups
//＊BitC_Endian_T##_
general BitC_Worker_KM_Endian_(PENC_CL _PL_ OpenCLHelper,devi_km _PL_ KernelManager,cl_mem const Data,DATA_32 Length);
//BitC_CL : Setting Kernel Manager's Local Workers and Work Groups
//＊BitC_Caster_T##_T##_, BitC_Expand_T##_, BitC_Shrink_T##_
general BitC_Worker_KM_Caster_(PENC_CL _PL_ OpenCLHelper,devi_km _PL_ KernelManager,cl_mem const Input,cl_mem const Output,DATA_32 Length);

//BitC_CL : Setting Kernel Manager's Local Workers and Work Groups
//＊BitC_BO_N_1_T##_
general BitC_Worker_KM_BO_N_1_(PENC_CL _PL_ OpenCLHelper,devi_km _PL_ KernelManager,cl_mem const C,cl_mem const A,DATA_32 N);
//BitC_CL : Setting Kernel Manager's Local Workers and Work Groups
//＊BitC_BO_S_1_T##_
general BitC_Worker_KM_BO_S_1_(PENC_CL _PL_ OpenCLHelper,devi_km _PL_ KernelManager,cl_mem const C,cl_mem const A,INTE_32 S,DATA_32 N);
//BitC_CL : Setting Kernel Manager's Local Workers and Work Groups
//＊BitC_BO_A_1_T##_, BitC_BO_O_1_T##_, BitC_BO_X_1_T##_,
//　BitC_RO_E_1_T##_, BitC_RO_N_1_T##_, BitC_RO_G_1_T##_, BitC_RO_L_1_T##_
general BitC_Worker_KM_Op_M_1_(PENC_CL _PL_ OpenCLHelper,devi_km _PL_ KernelManager,cl_mem const C,cl_mem const A,GENERAL *M,DATA_32 N);
//BitC_CL : Setting Kernel Manager's Local Workers and Work Groups
//＊BitC_BO_A_2_T##_, BitC_BO_O_2_T##_, BitC_BO_X_2_T##_
//　BitC_RO_E_2_T##_, BitC_RO_N_2_T##_, BitC_RO_G_2_T##_, BitC_RO_L_2_T##_
general BitC_Worker_KM_Op_M_2_(PENC_CL _PL_ OpenCLHelper,devi_km _PL_ KernelManager,cl_mem const C,cl_mem const A,cl_mem const B,DATA_32 N);
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
general BitC_Caster_D08_D16_(DATA_08 *MemC_Rst_ I,data_16 *MemC_Rst_ O,DATA_32 N);
//BitClip : 8-bit Natural to 32-bit Natural Type Casting
general BitC_Caster_D08_D32_(DATA_08 *MemC_Rst_ I,data_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 8-bit Natural to 64-bit Natural Type Casting
general BitC_Caster_D08_D64_(DATA_08 *MemC_Rst_ I,data_64 *MemC_Rst_ O,DATA_32 N);
//BitClip : 8-bit Natural to 8-bit Integer Type Casting
general BitC_Caster_D08_I08_(DATA_08 *MemC_Rst_ I,inte_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : 8-bit Natural to 32-bit Real Type Casting
general BitC_Caster_D08_R32_(DATA_08 *MemC_Rst_ I,real_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 8-bit Natural to 64-bit Real Type Casting
general BitC_Caster_D08_R64_(DATA_08 *MemC_Rst_ I,real_64 *MemC_Rst_ O,DATA_32 N);

//BitClip : 16-bit Natural to 8-bit Natural Type Casting
general BitC_Caster_D16_D08_(DATA_16 *MemC_Rst_ I,data_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : 16-bit Natural to 32-bit Natural Type Casting
general BitC_Caster_D16_D32_(DATA_16 *MemC_Rst_ I,data_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 16-bit Natural to 64-bit Natural Type Casting
general BitC_Caster_D16_D64_(DATA_16 *MemC_Rst_ I,data_64 *MemC_Rst_ O,DATA_32 N);
//BitClip : 16-bit Natural to 8-bit Integer Type Casting
general BitC_Caster_D16_I08_(DATA_16 *MemC_Rst_ I,inte_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : 16-bit Natural to 16-bit Integer Type Casting
general BitC_Caster_D16_I16_(DATA_16 *MemC_Rst_ I,inte_16 *MemC_Rst_ O,DATA_32 N);
//BitClip : 16-bit Natural to 32-bit Real Type Casting
general BitC_Caster_D16_R32_(DATA_16 *MemC_Rst_ I,real_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 16-bit Natural to 64-bit Real Type Casting
general BitC_Caster_D16_R64_(DATA_16 *MemC_Rst_ I,real_64 *MemC_Rst_ O,DATA_32 N);

//BitClip : 32-bit Natural to 8-bit Natural Type Casting
general BitC_Caster_D32_D08_(DATA_32 *MemC_Rst_ I,data_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Natural to 16-bit Natural Type Casting
general BitC_Caster_D32_D16_(DATA_32 *MemC_Rst_ I,data_16 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Natural to 64-bit Natural Type Casting
general BitC_Caster_D32_D64_(DATA_32 *MemC_Rst_ I,data_64 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Natural to 8-bit Integer Type Casting
general BitC_Caster_D32_I08_(DATA_32 *MemC_Rst_ I,inte_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Natural to 16-bit Integer Type Casting
general BitC_Caster_D32_I16_(DATA_32 *MemC_Rst_ I,inte_16 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Natural to 32-bit Integer Type Casting
general BitC_Caster_D32_I32_(DATA_32 *MemC_Rst_ I,inte_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Natural to 32-bit Real Type Casting
general BitC_Caster_D32_R32_(DATA_32 *MemC_Rst_ I,real_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Natural to 64-bit Real Type Casting
general BitC_Caster_D32_R64_(DATA_32 *MemC_Rst_ I,real_64 *MemC_Rst_ O,DATA_32 N);

//BitClip : 64-bit Natural to 8-bit Natural Type Casting
general BitC_Caster_D64_D08_(DATA_64 *MemC_Rst_ I,data_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Natural to 16-bit Natural Type Casting
general BitC_Caster_D64_D16_(DATA_64 *MemC_Rst_ I,data_16 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Natural to 32-bit Natural Type Casting
general BitC_Caster_D64_D32_(DATA_64 *MemC_Rst_ I,data_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Natural to 8-bit Integer Type Casting
general BitC_Caster_D64_I08_(DATA_64 *MemC_Rst_ I,inte_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Natural to 16-bit Integer Type Casting
general BitC_Caster_D64_I16_(DATA_64 *MemC_Rst_ I,inte_16 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Natural to 32-bit Integer Type Casting
general BitC_Caster_D64_I32_(DATA_64 *MemC_Rst_ I,inte_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Natural to 64-bit Integer Type Casting
general BitC_Caster_D64_I64_(DATA_64 *MemC_Rst_ I,inte_64 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Natural to 32-bit Real Type Casting
general BitC_Caster_D64_R32_(DATA_64 *MemC_Rst_ I,real_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Natural to 64-bit Real Type Casting
general BitC_Caster_D64_R64_(DATA_64 *MemC_Rst_ I,real_64 *MemC_Rst_ O,DATA_32 N);

//BitClip : 8-bit Integer to 8-bit Natural Type Casting
general BitC_Caster_I08_D08_(INTE_08 *MemC_Rst_ I,data_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : 8-bit Integer to 16-bit Natural Type Casting
general BitC_Caster_I08_D16_(INTE_08 *MemC_Rst_ I,data_16 *MemC_Rst_ O,DATA_32 N);
//BitClip : 8-bit Integer to 32-bit Natural Type Casting
general BitC_Caster_I08_D32_(INTE_08 *MemC_Rst_ I,data_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 8-bit Integer to 64-bit Natural Type Casting
general BitC_Caster_I08_D64_(INTE_08 *MemC_Rst_ I,data_64 *MemC_Rst_ O,DATA_32 N);
//BitClip : 8-bit Integer to 16-bit Integer Type Casting
general BitC_Caster_I08_I16_(INTE_08 *MemC_Rst_ I,inte_16 *MemC_Rst_ O,DATA_32 N);
//BitClip : 8-bit Integer to 32-bit Integer Type Casting
general BitC_Caster_I08_I32_(INTE_08 *MemC_Rst_ I,inte_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 8-bit Integer to 64-bit Integer Type Casting
general BitC_Caster_I08_I64_(INTE_08 *MemC_Rst_ I,inte_64 *MemC_Rst_ O,DATA_32 N);
//BitClip : 8-bit Integer to 32-bit Real Type Casting
general BitC_Caster_I08_R32_(INTE_08 *MemC_Rst_ I,real_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 8-bit Integer to 64-bit Real Type Casting
general BitC_Caster_I08_R64_(INTE_08 *MemC_Rst_ I,real_64 *MemC_Rst_ O,DATA_32 N);

//BitClip : 16-bit Integer to 8-bit Natural Type Casting
general BitC_Caster_I16_D08_(INTE_16 *MemC_Rst_ I,data_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : 16-bit Integer to 16-bit Natural Type Casting
general BitC_Caster_I16_D16_(INTE_16 *MemC_Rst_ I,data_16 *MemC_Rst_ O,DATA_32 N);
//BitClip : 16-bit Integer to 32-bit Natural Type Casting
general BitC_Caster_I16_D32_(INTE_16 *MemC_Rst_ I,data_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 16-bit Integer to 64-bit Natural Type Casting
general BitC_Caster_I16_D64_(INTE_16 *MemC_Rst_ I,data_64 *MemC_Rst_ O,DATA_32 N);
//BitClip : 16-bit Integer to 8-bit Integer Type Casting
general BitC_Caster_I16_I08_(INTE_16 *MemC_Rst_ I,inte_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : 16-bit Integer to 32-bit Integer Type Casting
general BitC_Caster_I16_I32_(INTE_16 *MemC_Rst_ I,inte_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 16-bit Integer to 64-bit Integer Type Casting
general BitC_Caster_I16_I64_(INTE_16 *MemC_Rst_ I,inte_64 *MemC_Rst_ O,DATA_32 N);
//BitClip : 16-bit Integer to 32-bit Real Type Casting
general BitC_Caster_I16_R32_(INTE_16 *MemC_Rst_ I,real_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 16-bit Integer to 64-bit Real Type Casting
general BitC_Caster_I16_R64_(INTE_16 *MemC_Rst_ I,real_64 *MemC_Rst_ O,DATA_32 N);

//BitClip : 32-bit Integer to 8-bit Natural Type Casting
general BitC_Caster_I32_D08_(INTE_32 *MemC_Rst_ I,data_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Integer to 16-bit Natural Type Casting
general BitC_Caster_I32_D16_(INTE_32 *MemC_Rst_ I,data_16 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Integer to 32-bit Natural Type Casting
general BitC_Caster_I32_D32_(INTE_32 *MemC_Rst_ I,data_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Integer to 64-bit Natural Type Casting
general BitC_Caster_I32_D64_(INTE_32 *MemC_Rst_ I,data_64 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Integer to 8-bit Integer Type Casting
general BitC_Caster_I32_I08_(INTE_32 *MemC_Rst_ I,inte_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Integer to 16-bit Integer Type Casting
general BitC_Caster_I32_I16_(INTE_32 *MemC_Rst_ I,inte_16 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Integer to 64-bit Integer Type Casting
general BitC_Caster_I32_I64_(INTE_32 *MemC_Rst_ I,inte_64 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Integer to 32-bit Real Type Casting
general BitC_Caster_I32_R32_(INTE_32 *MemC_Rst_ I,real_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Integer to 64-bit Real Type Casting
general BitC_Caster_I32_R64_(INTE_32 *MemC_Rst_ I,real_64 *MemC_Rst_ O,DATA_32 N);

//BitClip : 64-bit Integer to 8-bit Natural Type Casting
general BitC_Caster_I64_D08_(INTE_64 *MemC_Rst_ I,data_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Integer to 16-bit Natural Type Casting
general BitC_Caster_I64_D16_(INTE_64 *MemC_Rst_ I,data_16 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Integer to 32-bit Natural Type Casting
general BitC_Caster_I64_D32_(INTE_64 *MemC_Rst_ I,data_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Integer to 64-bit Natural Type Casting
general BitC_Caster_I64_D64_(INTE_64 *MemC_Rst_ I,data_64 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Integer to 8-bit Integer Type Casting
general BitC_Caster_I64_I08_(INTE_64 *MemC_Rst_ I,inte_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Integer to 16-bit Integer Type Casting
general BitC_Caster_I64_I16_(INTE_64 *MemC_Rst_ I,inte_16 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Integer to 32-bit Integer Type Casting
general BitC_Caster_I64_I32_(INTE_64 *MemC_Rst_ I,inte_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Integer to 32-bit Real Type Casting
general BitC_Caster_I64_R32_(INTE_64 *MemC_Rst_ I,real_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Integer to 64-bit Real Type Casting
general BitC_Caster_I64_R64_(INTE_64 *MemC_Rst_ I,real_64 *MemC_Rst_ O,DATA_32 N);

//BitClip : 32-bit Real to 8-bit Natural Type Casting
general BitC_Caster_R32_D08_(REAL_32 *MemC_Rst_ I,data_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Real to 16-bit Natural Type Casting
general BitC_Caster_R32_D16_(REAL_32 *MemC_Rst_ I,data_16 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Real to 32-bit Natural Type Casting
general BitC_Caster_R32_D32_(REAL_32 *MemC_Rst_ I,data_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Real to 64-bit Natural Type Casting
general BitC_Caster_R32_D64_(REAL_32 *MemC_Rst_ I,data_64 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Real to 8-bit Integer Type Casting
general BitC_Caster_R32_I08_(REAL_32 *MemC_Rst_ I,inte_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Real to 16-bit Integer Type Casting
general BitC_Caster_R32_I16_(REAL_32 *MemC_Rst_ I,inte_16 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Real to 32-bit Integer Type Casting
general BitC_Caster_R32_I32_(REAL_32 *MemC_Rst_ I,inte_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Real to 64-bit Integer Type Casting
general BitC_Caster_R32_I64_(REAL_32 *MemC_Rst_ I,inte_64 *MemC_Rst_ O,DATA_32 N);
//BitClip : 32-bit Real to 64-bit Real Type Casting
general BitC_Caster_R32_R64_(REAL_32 *MemC_Rst_ I,real_64 *MemC_Rst_ O,DATA_32 N);

//BitClip : 64-bit Real to 8-bit Natural Type Casting
general BitC_Caster_R64_D08_(REAL_64 *MemC_Rst_ I,data_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Real to 16-bit Natural Type Casting
general BitC_Caster_R64_D16_(REAL_64 *MemC_Rst_ I,data_16 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Real to 32-bit Natural Type Casting
general BitC_Caster_R64_D32_(REAL_64 *MemC_Rst_ I,data_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Real to 64-bit Natural Type Casting
general BitC_Caster_R64_D64_(REAL_64 *MemC_Rst_ I,data_64 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Real to 8-bit Integer Type Casting
general BitC_Caster_R64_I08_(REAL_64 *MemC_Rst_ I,inte_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Real to 16-bit Integer Type Casting
general BitC_Caster_R64_I16_(REAL_64 *MemC_Rst_ I,inte_16 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Real to 32-bit Integer Type Casting
general BitC_Caster_R64_I32_(REAL_64 *MemC_Rst_ I,inte_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Real to 64-bit Integer Type Casting
general BitC_Caster_R64_I64_(REAL_64 *MemC_Rst_ I,inte_64 *MemC_Rst_ O,DATA_32 N);
//BitClip : 64-bit Real to 32-bit Real Type Casting
general BitC_Caster_R64_R32_(REAL_64 *MemC_Rst_ I,real_32 *MemC_Rst_ O,DATA_32 N);
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
general BitC_Expand_D08_(DATA_08 *MemC_Rst_ I,data_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : Bit Expansion to 16-bit Natural
//＊O[n]＝(I[n/8].bit[n%8])?(0xFFFF):(0x0000)
general BitC_Expand_D16_(DATA_08 *MemC_Rst_ I,data_16 *MemC_Rst_ O,DATA_32 N);
//BitClip : Bit Expansion to 32-bit Natural
//＊O[n]＝(I[n/8].bit[n%8])?(0xFFFFFFFF):(0x00000000)
general BitC_Expand_D32_(DATA_08 *MemC_Rst_ I,data_32 *MemC_Rst_ O,DATA_32 N);
//BitClip : Bit Expansion to 64-bit Natural
//＊O[n]＝(I[n/8].bit[n%8])?(0xFFFFFFFFFFFFFFFF):(0x0000000000000000)
general BitC_Expand_D64_(DATA_08 *MemC_Rst_ I,data_64 *MemC_Rst_ O,DATA_32 N);

//BitClip : Bit Shrinkage from 8-bit Natural
//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
general BitC_Shrink_D08_(DATA_08 *MemC_Rst_ I,data_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : Bit Shrinkage from 16-bit Natural
//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
general BitC_Shrink_D16_(DATA_16 *MemC_Rst_ I,data_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : Bit Shrinkage from 32-bit Natural
//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
general BitC_Shrink_D32_(DATA_32 *MemC_Rst_ I,data_08 *MemC_Rst_ O,DATA_32 N);
//BitClip : Bit Shrinkage from 64-bit Natural
//＊O[n/8].bit[n%8]＝I[n].bit[n%8]
general BitC_Shrink_D64_(DATA_64 *MemC_Rst_ I,data_08 *MemC_Rst_ O,DATA_32 N);

//BitClip : 8-bit Natural EQ Operation
//＊C[n/8].bit[n%8]＝(A[n]==V)
general BitC_RO_E_1_D08_(data_08 *MemC_Rst_ C,DATA_08 *MemC_Rst_ A,DATA_08 V,DATA_32 N);
//BitClip : 16-bit Natural EQ Operation
//＊C[n/8].bit[n%8]＝(A[n]==V)
general BitC_RO_E_1_D16_(data_08 *MemC_Rst_ C,DATA_16 *MemC_Rst_ A,DATA_16 V,DATA_32 N);
//BitClip : 32-bit Natural EQ Operation
//＊C[n/8].bit[n%8]＝(A[n]==V)
general BitC_RO_E_1_D32_(data_08 *MemC_Rst_ C,DATA_32 *MemC_Rst_ A,DATA_32 V,DATA_32 N);
//BitClip : 64-bit Natural EQ Operation
//＊C[n/8].bit[n%8]＝(A[n]==V)
general BitC_RO_E_1_D64_(data_08 *MemC_Rst_ C,DATA_64 *MemC_Rst_ A,DATA_64 V,DATA_32 N);
//BitClip : 8-bit Natural EQ Operation
//＊C[n/8].bit[n%8]＝(A[n]==B[n])
general BitC_RO_E_2_D08_(data_08 *MemC_Rst_ C,DATA_08 *MemC_Rst_ A,DATA_08 *MemC_Rst_ B,DATA_32 N);
//BitClip : 16-bit Natural EQ Operation
//＊C[n/8].bit[n%8]＝(A[n]==B[n])
general BitC_RO_E_2_D16_(data_08 *MemC_Rst_ C,DATA_16 *MemC_Rst_ A,DATA_16 *MemC_Rst_ B,DATA_32 N);
//BitClip : 32-bit Natural EQ Operation
//＊C[n/8].bit[n%8]＝(A[n]==B[n])
general BitC_RO_E_2_D32_(data_08 *MemC_Rst_ C,DATA_32 *MemC_Rst_ A,DATA_32 *MemC_Rst_ B,DATA_32 N);
//BitClip : 64-bit Natural EQ Operation
//＊C[n/8].bit[n%8]＝(A[n]==B[n])
general BitC_RO_E_2_D64_(data_08 *MemC_Rst_ C,DATA_64 *MemC_Rst_ A,DATA_64 *MemC_Rst_ B,DATA_32 N);

//BitClip : 8-bit Natural NE Operation
//＊C[n/8].bit[n%8]＝(A[n]!=V)
general BitC_RO_N_1_D08_(data_08 *MemC_Rst_ C,DATA_08 *MemC_Rst_ A,DATA_08 V,DATA_32 N);
//BitClip : 16-bit Natural NE Operation
//＊C[n/8].bit[n%8]＝(A[n]!=V)
general BitC_RO_N_1_D16_(data_08 *MemC_Rst_ C,DATA_16 *MemC_Rst_ A,DATA_16 V,DATA_32 N);
//BitClip : 32-bit Natural NE Operation
//＊C[n/8].bit[n%8]＝(A[n]!=V)
general BitC_RO_N_1_D32_(data_08 *MemC_Rst_ C,DATA_32 *MemC_Rst_ A,DATA_32 V,DATA_32 N);
//BitClip : 64-bit Natural NE Operation
//＊C[n/8].bit[n%8]＝(A[n]!=V)
general BitC_RO_N_1_D64_(data_08 *MemC_Rst_ C,DATA_64 *MemC_Rst_ A,DATA_64 V,DATA_32 N);
//BitClip : 8-bit Natural NE Operation
//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
general BitC_RO_N_2_D08_(data_08 *MemC_Rst_ C,DATA_08 *MemC_Rst_ A,DATA_08 *MemC_Rst_ B,DATA_32 N);
//BitClip : 16-bit Natural NE Operation
//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
general BitC_RO_N_2_D16_(data_08 *MemC_Rst_ C,DATA_16 *MemC_Rst_ A,DATA_16 *MemC_Rst_ B,DATA_32 N);
//BitClip : 32-bit Natural NE Operation
//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
general BitC_RO_N_2_D32_(data_08 *MemC_Rst_ C,DATA_32 *MemC_Rst_ A,DATA_32 *MemC_Rst_ B,DATA_32 N);
//BitClip : 64-bit Natural NE Operation
//＊C[n/8].bit[n%8]＝(A[n]!=B[n])
general BitC_RO_N_2_D64_(data_08 *MemC_Rst_ C,DATA_64 *MemC_Rst_ A,DATA_64 *MemC_Rst_ B,DATA_32 N);

//BitClip : 8-bit Natural GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥V)
general BitC_RO_G_1_D08_(data_08 *MemC_Rst_ C,DATA_08 *MemC_Rst_ A,DATA_08 V,DATA_32 N);
//BitClip : 16-bit Natural GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥V)
general BitC_RO_G_1_D16_(data_08 *MemC_Rst_ C,DATA_16 *MemC_Rst_ A,DATA_16 V,DATA_32 N);
//BitClip : 32-bit Natural GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥V)
general BitC_RO_G_1_D32_(data_08 *MemC_Rst_ C,DATA_32 *MemC_Rst_ A,DATA_32 V,DATA_32 N);
//BitClip : 64-bit Natural GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥V)
general BitC_RO_G_1_D64_(data_08 *MemC_Rst_ C,DATA_64 *MemC_Rst_ A,DATA_64 V,DATA_32 N);
//BitClip : 8-bit Integer GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥V)
general BitC_RO_G_1_I08_(data_08 *MemC_Rst_ C,INTE_08 *MemC_Rst_ A,INTE_08 V,DATA_32 N);
//BitClip : 16-bit Integer GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥V)
general BitC_RO_G_1_I16_(data_08 *MemC_Rst_ C,INTE_16 *MemC_Rst_ A,INTE_16 V,DATA_32 N);
//BitClip : 32-bit Integer GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥V)
general BitC_RO_G_1_I32_(data_08 *MemC_Rst_ C,INTE_32 *MemC_Rst_ A,INTE_32 V,DATA_32 N);
//BitClip : 64-bit Integer GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥V)
general BitC_RO_G_1_I64_(data_08 *MemC_Rst_ C,INTE_64 *MemC_Rst_ A,INTE_64 V,DATA_32 N);
//BitClip : 32-bit Real GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥V)
general BitC_RO_G_1_R32_(data_08 *MemC_Rst_ C,REAL_32 *MemC_Rst_ A,REAL_32 V,DATA_32 N);
//BitClip : 64-bit Real GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥V)
general BitC_RO_G_1_R64_(data_08 *MemC_Rst_ C,REAL_64 *MemC_Rst_ A,REAL_64 V,DATA_32 N);
//BitClip : 8-bit Natural GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
general BitC_RO_G_2_D08_(data_08 *MemC_Rst_ C,DATA_08 *MemC_Rst_ A,DATA_08 *MemC_Rst_ B,DATA_32 N);
//BitClip : 16-bit Natural GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
general BitC_RO_G_2_D16_(data_08 *MemC_Rst_ C,DATA_16 *MemC_Rst_ A,DATA_16 *MemC_Rst_ B,DATA_32 N);
//BitClip : 32-bit Natural GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
general BitC_RO_G_2_D32_(data_08 *MemC_Rst_ C,DATA_32 *MemC_Rst_ A,DATA_32 *MemC_Rst_ B,DATA_32 N);
//BitClip : 64-bit Natural GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
general BitC_RO_G_2_D64_(data_08 *MemC_Rst_ C,DATA_64 *MemC_Rst_ A,DATA_64 *MemC_Rst_ B,DATA_32 N);
//BitClip : 8-bit Integer GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
general BitC_RO_G_2_I08_(data_08 *MemC_Rst_ C,INTE_08 *MemC_Rst_ A,INTE_08 *MemC_Rst_ B,DATA_32 N);
//BitClip : 16-bit Integer GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
general BitC_RO_G_2_I16_(data_08 *MemC_Rst_ C,INTE_16 *MemC_Rst_ A,INTE_16 *MemC_Rst_ B,DATA_32 N);
//BitClip : 32-bit Integer GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
general BitC_RO_G_2_I32_(data_08 *MemC_Rst_ C,INTE_32 *MemC_Rst_ A,INTE_32 *MemC_Rst_ B,DATA_32 N);
//BitClip : 64-bit Integer GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
general BitC_RO_G_2_I64_(data_08 *MemC_Rst_ C,INTE_64 *MemC_Rst_ A,INTE_64 *MemC_Rst_ B,DATA_32 N);
//BitClip : 32-bit Real GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
general BitC_RO_G_2_R32_(data_08 *MemC_Rst_ C,REAL_32 *MemC_Rst_ A,REAL_32 *MemC_Rst_ B,DATA_32 N);
//BitClip : 64-bit Real GE Operation
//＊C[n/8].bit[n%8]＝(A[n]≥B[n])
general BitC_RO_G_2_R64_(data_08 *MemC_Rst_ C,REAL_64 *MemC_Rst_ A,REAL_64 *MemC_Rst_ B,DATA_32 N);

//BitClip : 8-bit Natural LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜V)
general BitC_RO_L_1_D08_(data_08 *MemC_Rst_ C,DATA_08 *MemC_Rst_ A,DATA_08 V,DATA_32 N);
//BitClip : 16-bit Natural LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜V)
general BitC_RO_L_1_D16_(data_08 *MemC_Rst_ C,DATA_16 *MemC_Rst_ A,DATA_16 V,DATA_32 N);
//BitClip : 32-bit Natural LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜V)
general BitC_RO_L_1_D32_(data_08 *MemC_Rst_ C,DATA_32 *MemC_Rst_ A,DATA_32 V,DATA_32 N);
//BitClip : 64-bit Natural LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜V)
general BitC_RO_L_1_D64_(data_08 *MemC_Rst_ C,DATA_64 *MemC_Rst_ A,DATA_64 V,DATA_32 N);
//BitClip : 8-bit Integer LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜V)
general BitC_RO_L_1_I08_(data_08 *MemC_Rst_ C,INTE_08 *MemC_Rst_ A,INTE_08 V,DATA_32 N);
//BitClip : 16-bit Integer LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜V)
general BitC_RO_L_1_I16_(data_08 *MemC_Rst_ C,INTE_16 *MemC_Rst_ A,INTE_16 V,DATA_32 N);
//BitClip : 32-bit Integer LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜V)
general BitC_RO_L_1_I32_(data_08 *MemC_Rst_ C,INTE_32 *MemC_Rst_ A,INTE_32 V,DATA_32 N);
//BitClip : 64-bit Integer LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜V)
general BitC_RO_L_1_I64_(data_08 *MemC_Rst_ C,INTE_64 *MemC_Rst_ A,INTE_64 V,DATA_32 N);
//BitClip : 32-bit Real LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜V)
general BitC_RO_L_1_R32_(data_08 *MemC_Rst_ C,REAL_32 *MemC_Rst_ A,REAL_32 V,DATA_32 N);
//BitClip : 64-bit Real LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜V)
general BitC_RO_L_1_R64_(data_08 *MemC_Rst_ C,REAL_64 *MemC_Rst_ A,REAL_64 V,DATA_32 N);

//BitClip : 8-bit Natural LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
general BitC_RO_L_2_D08_(data_08 *MemC_Rst_ C,DATA_08 *MemC_Rst_ A,DATA_08 *MemC_Rst_ B,DATA_32 N);
//BitClip : 16-bit Natural LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
general BitC_RO_L_2_D16_(data_08 *MemC_Rst_ C,DATA_16 *MemC_Rst_ A,DATA_16 *MemC_Rst_ B,DATA_32 N);
//BitClip : 32-bit Natural LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
general BitC_RO_L_2_D32_(data_08 *MemC_Rst_ C,DATA_32 *MemC_Rst_ A,DATA_32 *MemC_Rst_ B,DATA_32 N);
//BitClip : 64-bit Natural LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
general BitC_RO_L_2_D64_(data_08 *MemC_Rst_ C,DATA_64 *MemC_Rst_ A,DATA_64 *MemC_Rst_ B,DATA_32 N);
//BitClip : 8-bit Integer LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
general BitC_RO_L_2_I08_(data_08 *MemC_Rst_ C,INTE_08 *MemC_Rst_ A,INTE_08 *MemC_Rst_ B,DATA_32 N);
//BitClip : 16-bit Integer LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
general BitC_RO_L_2_I16_(data_08 *MemC_Rst_ C,INTE_16 *MemC_Rst_ A,INTE_16 *MemC_Rst_ B,DATA_32 N);
//BitClip : 32-bit Integer LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
general BitC_RO_L_2_I32_(data_08 *MemC_Rst_ C,INTE_32 *MemC_Rst_ A,INTE_32 *MemC_Rst_ B,DATA_32 N);
//BitClip : 64-bit Integer LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
general BitC_RO_L_2_I64_(data_08 *MemC_Rst_ C,INTE_64 *MemC_Rst_ A,INTE_64 *MemC_Rst_ B,DATA_32 N);
//BitClip : 32-bit Real LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
general BitC_RO_L_2_R32_(data_08 *MemC_Rst_ C,REAL_32 *MemC_Rst_ A,REAL_32 *MemC_Rst_ B,DATA_32 N);
//BitClip : 64-bit Real LT Operation
//＊C[n/8].bit[n%8]＝(A[n]＜B[n])
general BitC_RO_L_2_R64_(data_08 *MemC_Rst_ C,REAL_64 *MemC_Rst_ A,REAL_64 *MemC_Rst_ B,DATA_32 N);
#endif
#endif
