/*------------------------------------------------------------------*/
/*	BitClip specifies the size of data types.						*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2018.02.14	*/
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

#ifdef _WIN64
#define BitC_64_		//BitClip : 64-bit Memory Address
#endif

#if(MemC_Fold_(Definition:Types))
typedef uint8_t data_08;				//BitClip : 8-bit Natural Variable
typedef uint16_t data_16;				//BitClip : 16-bit Natural Variable
typedef uint32_t data_32;				//BitClip : 32-bit Natural Variable
typedef uint64_t data_64;				//BitClip : 64-bit Natural Variable

typedef const data_08 DATA_08;			//BitClip : 8-bit Natural Constant
typedef const data_16 DATA_16;			//BitClip : 16-bit Natural Constant
typedef const data_32 DATA_32;			//BitClip : 32-bit Natural Constant
typedef const data_64 DATA_64;			//BitClip : 64-bit Natural Constant

typedef int8_t inte_08;					//BitClip : 8-bit Integer Variable
typedef int16_t inte_16;				//BitClip : 16-bit Integer Variable
typedef int32_t inte_32;				//BitClip : 32-bit Integer Variable
typedef int64_t inte_64;				//BitClip : 64-bit Integer Variable

typedef const inte_08 INTE_08;			//BitClip : 8-bit Integer Constant
typedef const inte_16 INTE_16;			//BitClip : 16-bit Integer Constant
typedef const inte_32 INTE_32;			//BitClip : 32-bit Integer Constant
typedef const inte_64 INTE_64;			//BitClip : 64-bit Integer Constant

typedef float real_32;					//BitClip : 32-bit Single Precision Floating Point Variable
typedef double real_64;					//BitClip : 64-bit Double Precision Floating Point Variable

typedef const real_32 REAL_32;			//BitClip : 32-bit Single Precision Floating Point Constant
typedef const real_64 REAL_64;			//BitClip : 64-bit Double Precision Floating Point Constant

typedef void general;					//BitClip : General Variable
typedef signed int integer;				//BitClip : Integer Variable
typedef unsigned int natural;			//BitClip : Natural Variable
typedef size_t address;					//BitClip : Address Variable

typedef const general GENERAL;			//BitClip : General Constant
typedef const integer INTEGER;			//BitClip : Integer Constant
typedef const natural NATURAL;			//BitClip : Natural Constant
typedef const address ADDRESS;			//BitClip : Address Constant

typedef void (*func_p_)(void);			//BitClip : Function Pointer

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
#endif

#if(MemC_Fold_(Declaration:Constants and Variables))
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
//BitC_CL : Kernel Indicator Set
extern DATA_08 _PL_ _PL_ BitCKernel;
#endif

//BitClip : 256 byte Buffer
extern inte_32 _PL_ BitCBuffer;
#endif

#if(MemC_Fold_(Declaration:KM Functions))
#ifdef __OPENCL_H
//BitC_CL : Kernel Manager Memory Allocation - Deallocate with "Devi_KM_Delete_"
devi_km *BitC_Create_KM_(cl_kernel const);

//BitC_CL : Setting Kernel Manager's Local Workers and Work Groups
//＊BitC_Endian_T##_
general BitC_Worker_KM_Endian_(PENC_CL _PL_,devi_km _PL_,cl_mem const Data,DATA_32 Length);
//BitC_CL : Setting Kernel Manager's Local Workers and Work Groups
//＊BitC_Caster_T##_T##_
general BitC_Worker_KM_Caster_(PENC_CL _PL_,devi_km _PL_,cl_mem const Input,cl_mem const Output,DATA_32 Length);

//BitC_CL : Setting Kernel Manager's Local Workers and Work Groups
//＊BitC_BO_N_1_T##_
general BitC_Worker_KM_Op_N_1_(PENC_CL _PL_,devi_km _PL_,cl_mem const C,cl_mem const A,DATA_32 N);
//BitC_CL : Setting Kernel Manager's Local Workers and Work Groups
//＊BitC_BO_S_1_T##_
general BitC_Worker_KM_Op_S_1_(PENC_CL _PL_,devi_km _PL_,cl_mem const C,cl_mem const A,INTE_32 S,DATA_32 N);
//BitC_CL : Setting Kernel Manager's Local Workers and Work Groups
//＊BitC_BO_A_1_T##_, BitC_BO_O_1_T##_, BitC_BO_X_1_T##_
general BitC_Worker_KM_Op_M_1_(PENC_CL _PL_,devi_km _PL_,cl_mem const C,cl_mem const A,GENERAL *M,DATA_32 N);
//BitC_CL : Setting Kernel Manager's Local Workers and Work Groups
//＊BitC_BO_A_2_T##_, BitC_BO_O_2_T##_, BitC_BO_X_2_T##_
general BitC_Worker_KM_Op_M_2_(PENC_CL _PL_,devi_km _PL_,cl_mem const C,cl_mem const A,cl_mem const B,DATA_32 N);
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
general BitC_Caster_D08_D16_(DATA_08 *MemC_Rst_ Input,data_16 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 8-bit Natural to 32-bit Natural Type Casting
general BitC_Caster_D08_D32_(DATA_08 *MemC_Rst_ Input,data_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 8-bit Natural to 64-bit Natural Type Casting
general BitC_Caster_D08_D64_(DATA_08 *MemC_Rst_ Input,data_64 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 8-bit Natural to 8-bit Integer Type Casting
general BitC_Caster_D08_I08_(DATA_08 *MemC_Rst_ Input,inte_08 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 8-bit Natural to 32-bit Real Type Casting
general BitC_Caster_D08_R32_(DATA_08 *MemC_Rst_ Input,real_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 8-bit Natural to 64-bit Real Type Casting
general BitC_Caster_D08_R64_(DATA_08 *MemC_Rst_ Input,real_64 *MemC_Rst_ Output,DATA_32 Length);

//BitClip : 16-bit Natural to 8-bit Natural Type Casting
general BitC_Caster_D16_D08_(DATA_16 *MemC_Rst_ Input,data_08 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 16-bit Natural to 32-bit Natural Type Casting
general BitC_Caster_D16_D32_(DATA_16 *MemC_Rst_ Input,data_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 16-bit Natural to 64-bit Natural Type Casting
general BitC_Caster_D16_D64_(DATA_16 *MemC_Rst_ Input,data_64 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 16-bit Natural to 8-bit Integer Type Casting
general BitC_Caster_D16_I08_(DATA_16 *MemC_Rst_ Input,inte_08 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 16-bit Natural to 16-bit Integer Type Casting
general BitC_Caster_D16_I16_(DATA_16 *MemC_Rst_ Input,inte_16 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 16-bit Natural to 32-bit Real Type Casting
general BitC_Caster_D16_R32_(DATA_16 *MemC_Rst_ Input,real_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 16-bit Natural to 64-bit Real Type Casting
general BitC_Caster_D16_R64_(DATA_16 *MemC_Rst_ Input,real_64 *MemC_Rst_ Output,DATA_32 Length);

//BitClip : 32-bit Natural to 8-bit Natural Type Casting
general BitC_Caster_D32_D08_(DATA_32 *MemC_Rst_ Input,data_08 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Natural to 16-bit Natural Type Casting
general BitC_Caster_D32_D16_(DATA_32 *MemC_Rst_ Input,data_16 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Natural to 64-bit Natural Type Casting
general BitC_Caster_D32_D64_(DATA_32 *MemC_Rst_ Input,data_64 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Natural to 8-bit Integer Type Casting
general BitC_Caster_D32_I08_(DATA_32 *MemC_Rst_ Input,inte_08 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Natural to 16-bit Integer Type Casting
general BitC_Caster_D32_I16_(DATA_32 *MemC_Rst_ Input,inte_16 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Natural to 32-bit Integer Type Casting
general BitC_Caster_D32_I32_(DATA_32 *MemC_Rst_ Input,inte_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Natural to 32-bit Real Type Casting
general BitC_Caster_D32_R32_(DATA_32 *MemC_Rst_ Input,real_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Natural to 64-bit Real Type Casting
general BitC_Caster_D32_R64_(DATA_32 *MemC_Rst_ Input,real_64 *MemC_Rst_ Output,DATA_32 Length);

//BitClip : 64-bit Natural to 8-bit Natural Type Casting
general BitC_Caster_D64_D08_(DATA_64 *MemC_Rst_ Input,data_08 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Natural to 16-bit Natural Type Casting
general BitC_Caster_D64_D16_(DATA_64 *MemC_Rst_ Input,data_16 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Natural to 32-bit Natural Type Casting
general BitC_Caster_D64_D32_(DATA_64 *MemC_Rst_ Input,data_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Natural to 8-bit Integer Type Casting
general BitC_Caster_D64_I08_(DATA_64 *MemC_Rst_ Input,inte_08 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Natural to 16-bit Integer Type Casting
general BitC_Caster_D64_I16_(DATA_64 *MemC_Rst_ Input,inte_16 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Natural to 32-bit Integer Type Casting
general BitC_Caster_D64_I32_(DATA_64 *MemC_Rst_ Input,inte_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Natural to 64-bit Integer Type Casting
general BitC_Caster_D64_I64_(DATA_64 *MemC_Rst_ Input,inte_64 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Natural to 32-bit Real Type Casting
general BitC_Caster_D64_R32_(DATA_64 *MemC_Rst_ Input,real_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Natural to 64-bit Real Type Casting
general BitC_Caster_D64_R64_(DATA_64 *MemC_Rst_ Input,real_64 *MemC_Rst_ Output,DATA_32 Length);

//BitClip : 8-bit Integer to 8-bit Natural Type Casting
general BitC_Caster_I08_D08_(INTE_08 *MemC_Rst_ Input,data_08 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 8-bit Integer to 16-bit Natural Type Casting
general BitC_Caster_I08_D16_(INTE_08 *MemC_Rst_ Input,data_16 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 8-bit Integer to 32-bit Natural Type Casting
general BitC_Caster_I08_D32_(INTE_08 *MemC_Rst_ Input,data_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 8-bit Integer to 64-bit Natural Type Casting
general BitC_Caster_I08_D64_(INTE_08 *MemC_Rst_ Input,data_64 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 8-bit Integer to 16-bit Integer Type Casting
general BitC_Caster_I08_I16_(INTE_08 *MemC_Rst_ Input,inte_16 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 8-bit Integer to 32-bit Integer Type Casting
general BitC_Caster_I08_I32_(INTE_08 *MemC_Rst_ Input,inte_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 8-bit Integer to 64-bit Integer Type Casting
general BitC_Caster_I08_I64_(INTE_08 *MemC_Rst_ Input,inte_64 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 8-bit Integer to 32-bit Real Type Casting
general BitC_Caster_I08_R32_(INTE_08 *MemC_Rst_ Input,real_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 8-bit Integer to 64-bit Real Type Casting
general BitC_Caster_I08_R64_(INTE_08 *MemC_Rst_ Input,real_64 *MemC_Rst_ Output,DATA_32 Length);

//BitClip : 16-bit Integer to 8-bit Natural Type Casting
general BitC_Caster_I16_D08_(INTE_16 *MemC_Rst_ Input,data_08 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 16-bit Integer to 16-bit Natural Type Casting
general BitC_Caster_I16_D16_(INTE_16 *MemC_Rst_ Input,data_16 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 16-bit Integer to 32-bit Natural Type Casting
general BitC_Caster_I16_D32_(INTE_16 *MemC_Rst_ Input,data_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 16-bit Integer to 64-bit Natural Type Casting
general BitC_Caster_I16_D64_(INTE_16 *MemC_Rst_ Input,data_64 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 16-bit Integer to 8-bit Integer Type Casting
general BitC_Caster_I16_I08_(INTE_16 *MemC_Rst_ Input,inte_08 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 16-bit Integer to 32-bit Integer Type Casting
general BitC_Caster_I16_I32_(INTE_16 *MemC_Rst_ Input,inte_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 16-bit Integer to 64-bit Integer Type Casting
general BitC_Caster_I16_I64_(INTE_16 *MemC_Rst_ Input,inte_64 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 16-bit Integer to 32-bit Real Type Casting
general BitC_Caster_I16_R32_(INTE_16 *MemC_Rst_ Input,real_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 16-bit Integer to 64-bit Real Type Casting
general BitC_Caster_I16_R64_(INTE_16 *MemC_Rst_ Input,real_64 *MemC_Rst_ Output,DATA_32 Length);

//BitClip : 32-bit Integer to 8-bit Natural Type Casting
general BitC_Caster_I32_D08_(INTE_32 *MemC_Rst_ Input,data_08 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Integer to 16-bit Natural Type Casting
general BitC_Caster_I32_D16_(INTE_32 *MemC_Rst_ Input,data_16 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Integer to 32-bit Natural Type Casting
general BitC_Caster_I32_D32_(INTE_32 *MemC_Rst_ Input,data_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Integer to 64-bit Natural Type Casting
general BitC_Caster_I32_D64_(INTE_32 *MemC_Rst_ Input,data_64 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Integer to 8-bit Integer Type Casting
general BitC_Caster_I32_I08_(INTE_32 *MemC_Rst_ Input,inte_08 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Integer to 16-bit Integer Type Casting
general BitC_Caster_I32_I16_(INTE_32 *MemC_Rst_ Input,inte_16 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Integer to 64-bit Integer Type Casting
general BitC_Caster_I32_I64_(INTE_32 *MemC_Rst_ Input,inte_64 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Integer to 32-bit Real Type Casting
general BitC_Caster_I32_R32_(INTE_32 *MemC_Rst_ Input,real_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Integer to 64-bit Real Type Casting
general BitC_Caster_I32_R64_(INTE_32 *MemC_Rst_ Input,real_64 *MemC_Rst_ Output,DATA_32 Length);

//BitClip : 64-bit Integer to 8-bit Natural Type Casting
general BitC_Caster_I64_D08_(INTE_64 *MemC_Rst_ Input,data_08 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Integer to 16-bit Natural Type Casting
general BitC_Caster_I64_D16_(INTE_64 *MemC_Rst_ Input,data_16 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Integer to 32-bit Natural Type Casting
general BitC_Caster_I64_D32_(INTE_64 *MemC_Rst_ Input,data_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Integer to 64-bit Natural Type Casting
general BitC_Caster_I64_D64_(INTE_64 *MemC_Rst_ Input,data_64 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Integer to 8-bit Integer Type Casting
general BitC_Caster_I64_I08_(INTE_64 *MemC_Rst_ Input,inte_08 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Integer to 16-bit Integer Type Casting
general BitC_Caster_I64_I16_(INTE_64 *MemC_Rst_ Input,inte_16 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Integer to 32-bit Integer Type Casting
general BitC_Caster_I64_I32_(INTE_64 *MemC_Rst_ Input,inte_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Integer to 32-bit Real Type Casting
general BitC_Caster_I64_R32_(INTE_64 *MemC_Rst_ Input,real_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Integer to 64-bit Real Type Casting
general BitC_Caster_I64_R64_(INTE_64 *MemC_Rst_ Input,real_64 *MemC_Rst_ Output,DATA_32 Length);

//BitClip : 32-bit Real to 8-bit Natural Type Casting
general BitC_Caster_R32_D08_(REAL_32 *MemC_Rst_ Input,data_08 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Real to 16-bit Natural Type Casting
general BitC_Caster_R32_D16_(REAL_32 *MemC_Rst_ Input,data_16 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Real to 32-bit Natural Type Casting
general BitC_Caster_R32_D32_(REAL_32 *MemC_Rst_ Input,data_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Real to 64-bit Natural Type Casting
general BitC_Caster_R32_D64_(REAL_32 *MemC_Rst_ Input,data_64 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Real to 8-bit Integer Type Casting
general BitC_Caster_R32_I08_(REAL_32 *MemC_Rst_ Input,inte_08 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Real to 16-bit Integer Type Casting
general BitC_Caster_R32_I16_(REAL_32 *MemC_Rst_ Input,inte_16 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Real to 32-bit Integer Type Casting
general BitC_Caster_R32_I32_(REAL_32 *MemC_Rst_ Input,inte_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Real to 64-bit Integer Type Casting
general BitC_Caster_R32_I64_(REAL_32 *MemC_Rst_ Input,inte_64 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 32-bit Real to 64-bit Real Type Casting
general BitC_Caster_R32_R64_(REAL_32 *MemC_Rst_ Input,real_64 *MemC_Rst_ Output,DATA_32 Length);

//BitClip : 64-bit Real to 8-bit Natural Type Casting
general BitC_Caster_R64_D08_(REAL_64 *MemC_Rst_ Input,data_08 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Real to 16-bit Natural Type Casting
general BitC_Caster_R64_D16_(REAL_64 *MemC_Rst_ Input,data_16 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Real to 32-bit Natural Type Casting
general BitC_Caster_R64_D32_(REAL_64 *MemC_Rst_ Input,data_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Real to 64-bit Natural Type Casting
general BitC_Caster_R64_D64_(REAL_64 *MemC_Rst_ Input,data_64 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Real to 8-bit Integer Type Casting
general BitC_Caster_R64_I08_(REAL_64 *MemC_Rst_ Input,inte_08 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Real to 16-bit Integer Type Casting
general BitC_Caster_R64_I16_(REAL_64 *MemC_Rst_ Input,inte_16 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Real to 32-bit Integer Type Casting
general BitC_Caster_R64_I32_(REAL_64 *MemC_Rst_ Input,inte_32 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Real to 64-bit Integer Type Casting
general BitC_Caster_R64_I64_(REAL_64 *MemC_Rst_ Input,inte_64 *MemC_Rst_ Output,DATA_32 Length);
//BitClip : 64-bit Real to 32-bit Real Type Casting
general BitC_Caster_R64_R32_(REAL_64 *MemC_Rst_ Input,real_32 *MemC_Rst_ Output,DATA_32 Length);
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
#endif
