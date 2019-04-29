/*------------------------------------------------------------------*/
/*	LinClip provides some elementary arithmetic operations.			*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2019.04.26	*/
/*------------------------------------------------------------------*/
/*	OpenCL Support													*/
/*	http://www.khronos.org/opencl/									*/
/*------------------------------------------------------------------*/

#ifndef _INC_LINCLIP
#define _INC_LINCLIP

#ifdef __OPENCL_VERSION__

#if(1)
#include <bitclip.h>
#endif

#else

#if(1)
#ifdef _CL
#include <CL\opencl.h>
#endif
#include <bitclip.h>
#endif

#if(Fold_(Library Casing))
//LinClip : Library Case
extern const struct _lincase
{
	//LinClip : Library Version
	BYTE_08 _PL_ Version;

#if(Fold_(Domain:Host))
	const struct
	{
		//LinClip : Arithmetic Progression Functions
		const struct
		{
			//LinClip : 8-bit Integer Line Arithmetic Progression
			//ㄙC[n]ˊSㄚ(n▼K)
			general(_PL_ I08_)(inte_08 *_R_ C,INTE_08 S,INTE_08 K,ADDRESS N);
			//LinClip : 16-bit Integer Line Arithmetic Progression
			//ㄙC[n]ˊSㄚ(n▼K)
			general(_PL_ I16_)(inte_16 *_R_ C,INTE_16 S,INTE_16 K,ADDRESS N);
			//LinClip : 32-bit Integer Line Arithmetic Progression
			//ㄙC[n]ˊSㄚ(n▼K)
			general(_PL_ I32_)(inte_32 *_R_ C,INTE_32 S,INTE_32 K,ADDRESS N);
			//LinClip : 64-bit Integer Line Arithmetic Progression
			//ㄙC[n]ˊSㄚ(n▼K)
			general(_PL_ I64_)(inte_64 *_R_ C,INTE_64 S,INTE_64 K,ADDRESS N);
			//LinClip : 8-bit Natural Line Arithmetic Progression
			//ㄙC[n]ˊSㄚ(n▼K)
			general(_PL_ D08_)(data_08 *_R_ C,DATA_08 S,DATA_08 K,ADDRESS N);
			//LinClip : 16-bit Natural Line Arithmetic Progression
			//ㄙC[n]ˊSㄚ(n▼K)
			general(_PL_ D16_)(data_16 *_R_ C,DATA_16 S,DATA_16 K,ADDRESS N);
			//LinClip : 32-bit Natural Line Arithmetic Progression
			//ㄙC[n]ˊSㄚ(n▼K)
			general(_PL_ D32_)(data_32 *_R_ C,DATA_32 S,DATA_32 K,ADDRESS N);
			//LinClip : 64-bit Natural Line Arithmetic Progression
			//ㄙC[n]ˊSㄚ(n▼K)
			general(_PL_ D64_)(data_64 *_R_ C,DATA_64 S,DATA_64 K,ADDRESS N);
			//LinClip : 32-bit Real Line Arithmetic Progression
			//ㄙC[n]ˊSㄚ(n▼K)
			general(_PL_ R32_)(real_32 *_R_ C,REAL_32 S,REAL_32 K,ADDRESS N);
			//LinClip : 64-bit Real Line Arithmetic Progression
			//ㄙC[n]ˊSㄚ(n▼K)
			general(_PL_ R64_)(real_64 *_R_ C,REAL_64 S,REAL_64 K,ADDRESS N);
		}
		Ari_0;

		//LinClip : Geometric Progression Functions
		const struct
		{
			//LinClip : 8-bit Integer Line Geometric Progression
			//ㄙC[n]ˊS▼K明
			general(_PL_ I08_)(inte_08 *_R_ C,INTE_08 S,INTE_08 K,ADDRESS N);
			//LinClip : 16-bit Integer Line Geometric Progression
			//ㄙC[n]ˊS▼K明
			general(_PL_ I16_)(inte_16 *_R_ C,INTE_16 S,INTE_16 K,ADDRESS N);
			//LinClip : 32-bit Integer Line Geometric Progression
			//ㄙC[n]ˊS▼K明
			general(_PL_ I32_)(inte_32 *_R_ C,INTE_32 S,INTE_32 K,ADDRESS N);
			//LinClip : 64-bit Integer Line Geometric Progression
			//ㄙC[n]ˊS▼K明
			general(_PL_ I64_)(inte_64 *_R_ C,INTE_64 S,INTE_64 K,ADDRESS N);
			//LinClip : 8-bit Natural Line Geometric Progression
			//ㄙC[n]ˊS▼K明
			general(_PL_ D08_)(data_08 *_R_ C,DATA_08 S,DATA_08 K,ADDRESS N);
			//LinClip : 16-bit Natural Line Geometric Progression
			//ㄙC[n]ˊS▼K明
			general(_PL_ D16_)(data_16 *_R_ C,DATA_16 S,DATA_16 K,ADDRESS N);
			//LinClip : 32-bit Natural Line Geometric Progression
			//ㄙC[n]ˊS▼K明
			general(_PL_ D32_)(data_32 *_R_ C,DATA_32 S,DATA_32 K,ADDRESS N);
			//LinClip : 64-bit Natural Line Geometric Progression
			//ㄙC[n]ˊS▼K明
			general(_PL_ D64_)(data_64 *_R_ C,DATA_64 S,DATA_64 K,ADDRESS N);
			//LinClip : 32-bit Real Line Geometric Progression
			//ㄙC[n]ˊS▼K明
			general(_PL_ R32_)(real_32 *_R_ C,REAL_32 S,REAL_32 K,ADDRESS N);
			//LinClip : 64-bit Real Line Geometric Progression
			//ㄙC[n]ˊS▼K明
			general(_PL_ R64_)(real_64 *_R_ C,REAL_64 S,REAL_64 K,ADDRESS N);
		}
		Geo_0;

		//LinClip : Increment Functions
		const struct
		{
			//LinClip : 8-bit Integer Line Increment
			//ㄙC[n]ˊA[n]ㄚK
			general(_PL_ I08_)(inte_08 *C,INTE_08 *A,INTE_08 K,ADDRESS N);
			//LinClip : 16-bit Integer Line Increment
			//ㄙC[n]ˊA[n]ㄚK
			general(_PL_ I16_)(inte_16 *C,INTE_16 *A,INTE_16 K,ADDRESS N);
			//LinClip : 32-bit Integer Line Increment
			//ㄙC[n]ˊA[n]ㄚK
			general(_PL_ I32_)(inte_32 *C,INTE_32 *A,INTE_32 K,ADDRESS N);
			//LinClip : 64-bit Integer Line Increment
			//ㄙC[n]ˊA[n]ㄚK
			general(_PL_ I64_)(inte_64 *C,INTE_64 *A,INTE_64 K,ADDRESS N);
			//LinClip : 8-bit Natural Line Increment
			//ㄙC[n]ˊA[n]ㄚK
			general(_PL_ D08_)(data_08 *C,DATA_08 *A,DATA_08 K,ADDRESS N);
			//LinClip : 16-bit Natural Line Increment
			//ㄙC[n]ˊA[n]ㄚK
			general(_PL_ D16_)(data_16 *C,DATA_16 *A,DATA_16 K,ADDRESS N);
			//LinClip : 32-bit Natural Line Increment
			//ㄙC[n]ˊA[n]ㄚK
			general(_PL_ D32_)(data_32 *C,DATA_32 *A,DATA_32 K,ADDRESS N);
			//LinClip : 64-bit Natural Line Increment
			//ㄙC[n]ˊA[n]ㄚK
			general(_PL_ D64_)(data_64 *C,DATA_64 *A,DATA_64 K,ADDRESS N);
			//LinClip : 32-bit Real Line Increment
			//ㄙC[n]ˊA[n]ㄚK
			general(_PL_ R32_)(real_32 *C,REAL_32 *A,REAL_32 K,ADDRESS N);
			//LinClip : 64-bit Real Line Increment
			//ㄙC[n]ˊA[n]ㄚK
			general(_PL_ R64_)(real_64 *C,REAL_64 *A,REAL_64 K,ADDRESS N);
		}
		Inc_1;

		//LinClip : Amplification Functions
		const struct
		{
			//LinClip : 8-bit Integer Line Amplification
			//ㄙC[n]ˊK▼A[n]
			general(_PL_ I08_)(inte_08 *C,INTE_08 *A,INTE_08 K,ADDRESS N);
			//LinClip : 16-bit Integer Line Amplification
			//ㄙC[n]ˊK▼A[n]
			general(_PL_ I16_)(inte_16 *C,INTE_16 *A,INTE_16 K,ADDRESS N);
			//LinClip : 32-bit Integer Line Amplification
			//ㄙC[n]ˊK▼A[n]
			general(_PL_ I32_)(inte_32 *C,INTE_32 *A,INTE_32 K,ADDRESS N);
			//LinClip : 64-bit Integer Line Amplification
			//ㄙC[n]ˊK▼A[n]
			general(_PL_ I64_)(inte_64 *C,INTE_64 *A,INTE_64 K,ADDRESS N);
			//LinClip : 8-bit Natural Line Amplification
			//ㄙC[n]ˊK▼A[n]
			general(_PL_ D08_)(data_08 *C,DATA_08 *A,DATA_08 K,ADDRESS N);
			//LinClip : 16-bit Natural Line Amplification
			//ㄙC[n]ˊK▼A[n]
			general(_PL_ D16_)(data_16 *C,DATA_16 *A,DATA_16 K,ADDRESS N);
			//LinClip : 32-bit Natural Line Amplification
			//ㄙC[n]ˊK▼A[n]
			general(_PL_ D32_)(data_32 *C,DATA_32 *A,DATA_32 K,ADDRESS N);
			//LinClip : 64-bit Natural Line Amplification
			//ㄙC[n]ˊK▼A[n]
			general(_PL_ D64_)(data_64 *C,DATA_64 *A,DATA_64 K,ADDRESS N);
			//LinClip : 32-bit Real Line Amplification
			//ㄙC[n]ˊK▼A[n]
			general(_PL_ R32_)(real_32 *C,REAL_32 *A,REAL_32 K,ADDRESS N);
			//LinClip : 64-bit Real Line Amplification
			//ㄙC[n]ˊK▼A[n]
			general(_PL_ R64_)(real_64 *C,REAL_64 *A,REAL_64 K,ADDRESS N);
		}
		Amp_1;

		//LinClip : Addition Functions
		const struct
		{
			//LinClip : 8-bit Integer Line Addition
			//ㄙC[n]ˊA[n]ㄚB[n]
			general(_PL_ I08_)(inte_08 *C,INTE_08 *A,INTE_08 *B,ADDRESS N);
			//LinClip : 16-bit Integer Line Addition
			//ㄙC[n]ˊA[n]ㄚB[n]
			general(_PL_ I16_)(inte_16 *C,INTE_16 *A,INTE_16 *B,ADDRESS N);
			//LinClip : 32-bit Integer Line Addition
			//ㄙC[n]ˊA[n]ㄚB[n]
			general(_PL_ I32_)(inte_32 *C,INTE_32 *A,INTE_32 *B,ADDRESS N);
			//LinClip : 64-bit Integer Line Addition
			//ㄙC[n]ˊA[n]ㄚB[n]
			general(_PL_ I64_)(inte_64 *C,INTE_64 *A,INTE_64 *B,ADDRESS N);
			//LinClip : 8-bit Natural Line Addition
			//ㄙC[n]ˊA[n]ㄚB[n]
			general(_PL_ D08_)(data_08 *C,DATA_08 *A,DATA_08 *B,ADDRESS N);
			//LinClip : 16-bit Natural Line Addition
			//ㄙC[n]ˊA[n]ㄚB[n]
			general(_PL_ D16_)(data_16 *C,DATA_16 *A,DATA_16 *B,ADDRESS N);
			//LinClip : 32-bit Natural Line Addition
			//ㄙC[n]ˊA[n]ㄚB[n]
			general(_PL_ D32_)(data_32 *C,DATA_32 *A,DATA_32 *B,ADDRESS N);
			//LinClip : 64-bit Natural Line Addition
			//ㄙC[n]ˊA[n]ㄚB[n]
			general(_PL_ D64_)(data_64 *C,DATA_64 *A,DATA_64 *B,ADDRESS N);
			//LinClip : 32-bit Real Line Addition
			//ㄙC[n]ˊA[n]ㄚB[n]
			general(_PL_ R32_)(real_32 *C,REAL_32 *A,REAL_32 *B,ADDRESS N);
			//LinClip : 64-bit Real Line Addition
			//ㄙC[n]ˊA[n]ㄚB[n]
			general(_PL_ R64_)(real_64 *C,REAL_64 *A,REAL_64 *B,ADDRESS N);
		}
		Add_2;

		//LinClip : Subtraction Functions
		const struct
		{
			//LinClip : 8-bit Integer Line Subtraction
			//ㄙC[n]ˊA[n]ㄜB[n]
			general(_PL_ I08_)(inte_08 *C,INTE_08 *A,INTE_08 *B,ADDRESS N);
			//LinClip : 16-bit Integer Line Subtraction
			//ㄙC[n]ˊA[n]ㄜB[n]
			general(_PL_ I16_)(inte_16 *C,INTE_16 *A,INTE_16 *B,ADDRESS N);
			//LinClip : 32-bit Integer Line Subtraction
			//ㄙC[n]ˊA[n]ㄜB[n]
			general(_PL_ I32_)(inte_32 *C,INTE_32 *A,INTE_32 *B,ADDRESS N);
			//LinClip : 64-bit Integer Line Subtraction
			//ㄙC[n]ˊA[n]ㄜB[n]
			general(_PL_ I64_)(inte_64 *C,INTE_64 *A,INTE_64 *B,ADDRESS N);
			//LinClip : 8-bit Natural Line Subtraction
			//ㄙC[n]ˊA[n]ㄜB[n]
			general(_PL_ D08_)(data_08 *C,DATA_08 *A,DATA_08 *B,ADDRESS N);
			//LinClip : 16-bit Natural Line Subtraction
			//ㄙC[n]ˊA[n]ㄜB[n]
			general(_PL_ D16_)(data_16 *C,DATA_16 *A,DATA_16 *B,ADDRESS N);
			//LinClip : 32-bit Natural Line Subtraction
			//ㄙC[n]ˊA[n]ㄜB[n]
			general(_PL_ D32_)(data_32 *C,DATA_32 *A,DATA_32 *B,ADDRESS N);
			//LinClip : 64-bit Natural Line Subtraction
			//ㄙC[n]ˊA[n]ㄜB[n]
			general(_PL_ D64_)(data_64 *C,DATA_64 *A,DATA_64 *B,ADDRESS N);
			//LinClip : 32-bit Real Line Subtraction
			//ㄙC[n]ˊA[n]ㄜB[n]
			general(_PL_ R32_)(real_32 *C,REAL_32 *A,REAL_32 *B,ADDRESS N);
			//LinClip : 64-bit Real Line Subtraction
			//ㄙC[n]ˊA[n]ㄜB[n]
			general(_PL_ R64_)(real_64 *C,REAL_64 *A,REAL_64 *B,ADDRESS N);
		}
		Sub_2;

		//LinClip : Multiplication Functions
		const struct
		{
			//LinClip : 8-bit Integer Line Multiplication
			//ㄙC[n]ˊA[n]▼B[n]
			general(_PL_ I08_)(inte_08 *C,INTE_08 *A,INTE_08 *B,ADDRESS N);
			//LinClip : 16-bit Integer Line Multiplication
			//ㄙC[n]ˊA[n]▼B[n]
			general(_PL_ I16_)(inte_16 *C,INTE_16 *A,INTE_16 *B,ADDRESS N);
			//LinClip : 32-bit Integer Line Multiplication
			//ㄙC[n]ˊA[n]▼B[n]
			general(_PL_ I32_)(inte_32 *C,INTE_32 *A,INTE_32 *B,ADDRESS N);
			//LinClip : 64-bit Integer Line Multiplication
			//ㄙC[n]ˊA[n]▼B[n]
			general(_PL_ I64_)(inte_64 *C,INTE_64 *A,INTE_64 *B,ADDRESS N);
			//LinClip : 8-bit Natural Line Multiplication
			//ㄙC[n]ˊA[n]▼B[n]
			general(_PL_ D08_)(data_08 *C,DATA_08 *A,DATA_08 *B,ADDRESS N);
			//LinClip : 16-bit Natural Line Multiplication
			//ㄙC[n]ˊA[n]▼B[n]
			general(_PL_ D16_)(data_16 *C,DATA_16 *A,DATA_16 *B,ADDRESS N);
			//LinClip : 32-bit Natural Line Multiplication
			//ㄙC[n]ˊA[n]▼B[n]
			general(_PL_ D32_)(data_32 *C,DATA_32 *A,DATA_32 *B,ADDRESS N);
			//LinClip : 64-bit Natural Line Multiplication
			//ㄙC[n]ˊA[n]▼B[n]
			general(_PL_ D64_)(data_64 *C,DATA_64 *A,DATA_64 *B,ADDRESS N);
			//LinClip : 32-bit Real Line Multiplication
			//ㄙC[n]ˊA[n]▼B[n]
			general(_PL_ R32_)(real_32 *C,REAL_32 *A,REAL_32 *B,ADDRESS N);
			//LinClip : 64-bit Real Line Multiplication
			//ㄙC[n]ˊA[n]▼B[n]
			general(_PL_ R64_)(real_64 *C,REAL_64 *A,REAL_64 *B,ADDRESS N);
		}
		Mul_2;

		//LinClip : Division Functions
		const struct
		{
			//LinClip : 8-bit Integer Line Division
			//ㄙC[n]ˊA[n]㊣K
			general(_PL_ I08_)(inte_08 *C,INTE_08 *A,INTE_08 K,ADDRESS N);
			//LinClip : 16-bit Integer Line Division
			//ㄙC[n]ˊA[n]㊣K
			general(_PL_ I16_)(inte_16 *C,INTE_16 *A,INTE_16 K,ADDRESS N);
			//LinClip : 32-bit Integer Line Division
			//ㄙC[n]ˊA[n]㊣K
			general(_PL_ I32_)(inte_32 *C,INTE_32 *A,INTE_32 K,ADDRESS N);
			//LinClip : 64-bit Integer Line Division
			//ㄙC[n]ˊA[n]㊣K
			general(_PL_ I64_)(inte_64 *C,INTE_64 *A,INTE_64 K,ADDRESS N);
			//LinClip : 8-bit Natural Line Division
			//ㄙC[n]ˊA[n]㊣K
			general(_PL_ D08_)(data_08 *C,DATA_08 *A,DATA_08 K,ADDRESS N);
			//LinClip : 16-bit Natural Line Division
			//ㄙC[n]ˊA[n]㊣K
			general(_PL_ D16_)(data_16 *C,DATA_16 *A,DATA_16 K,ADDRESS N);
			//LinClip : 32-bit Natural Line Division
			//ㄙC[n]ˊA[n]㊣K
			general(_PL_ D32_)(data_32 *C,DATA_32 *A,DATA_32 K,ADDRESS N);
			//LinClip : 64-bit Natural Line Division
			//ㄙC[n]ˊA[n]㊣K
			general(_PL_ D64_)(data_64 *C,DATA_64 *A,DATA_64 K,ADDRESS N);
		}
		Div_1;

		//LinClip : Inverse Functions
		const struct
		{
			//LinClip : 8-bit Integer Line Inverse
			//ㄙC[n]ˊK㊣A[n]
			general(_PL_ I08_)(inte_08 *C,INTE_08 *A,INTE_08 K,ADDRESS N);
			//LinClip : 16-bit Integer Line Inverse
			//ㄙC[n]ˊK㊣A[n]
			general(_PL_ I16_)(inte_16 *C,INTE_16 *A,INTE_16 K,ADDRESS N);
			//LinClip : 32-bit Integer Line Inverse
			//ㄙC[n]ˊK㊣A[n]
			general(_PL_ I32_)(inte_32 *C,INTE_32 *A,INTE_32 K,ADDRESS N);
			//LinClip : 64-bit Integer Line Inverse
			//ㄙC[n]ˊK㊣A[n]
			general(_PL_ I64_)(inte_64 *C,INTE_64 *A,INTE_64 K,ADDRESS N);
			//LinClip : 8-bit Natural Line Inverse
			//ㄙC[n]ˊK㊣A[n]
			general(_PL_ D08_)(data_08 *C,DATA_08 *A,DATA_08 K,ADDRESS N);
			//LinClip : 16-bit Natural Line Inverse
			//ㄙC[n]ˊK㊣A[n]
			general(_PL_ D16_)(data_16 *C,DATA_16 *A,DATA_16 K,ADDRESS N);
			//LinClip : 32-bit Natural Line Inverse
			//ㄙC[n]ˊK㊣A[n]
			general(_PL_ D32_)(data_32 *C,DATA_32 *A,DATA_32 K,ADDRESS N);
			//LinClip : 64-bit Natural Line Inverse
			//ㄙC[n]ˊK㊣A[n]
			general(_PL_ D64_)(data_64 *C,DATA_64 *A,DATA_64 K,ADDRESS N);
			//LinClip : 32-bit Real Line Inverse
			//ㄙC[n]ˊK㊣A[n]
			general(_PL_ R32_)(real_32 *C,REAL_32 *A,REAL_32 K,ADDRESS N);
			//LinClip : 64-bit Real Line Inverse
			//ㄙC[n]ˊK㊣A[n]
			general(_PL_ R64_)(real_64 *C,REAL_64 *A,REAL_64 K,ADDRESS N);
		}
		Inv_1;

		//LinClip : Division Functions
		const struct
		{
			//LinClip : 8-bit Integer Line Division
			//ㄙC[n]ˊA[n]㊣B[n]
			general(_PL_ I08_)(inte_08 *C,INTE_08 *A,INTE_08 *B,ADDRESS N);
			//LinClip : 16-bit Integer Line Division
			//ㄙC[n]ˊA[n]㊣B[n]
			general(_PL_ I16_)(inte_16 *C,INTE_16 *A,INTE_16 *B,ADDRESS N);
			//LinClip : 32-bit Integer Line Division
			//ㄙC[n]ˊA[n]㊣B[n]
			general(_PL_ I32_)(inte_32 *C,INTE_32 *A,INTE_32 *B,ADDRESS N);
			//LinClip : 64-bit Integer Line Division
			//ㄙC[n]ˊA[n]㊣B[n]
			general(_PL_ I64_)(inte_64 *C,INTE_64 *A,INTE_64 *B,ADDRESS N);
			//LinClip : 8-bit Natural Line Division
			//ㄙC[n]ˊA[n]㊣B[n]
			general(_PL_ D08_)(data_08 *C,DATA_08 *A,DATA_08 *B,ADDRESS N);
			//LinClip : 16-bit Natural Line Division
			//ㄙC[n]ˊA[n]㊣B[n]
			general(_PL_ D16_)(data_16 *C,DATA_16 *A,DATA_16 *B,ADDRESS N);
			//LinClip : 32-bit Natural Line Division
			//ㄙC[n]ˊA[n]㊣B[n]
			general(_PL_ D32_)(data_32 *C,DATA_32 *A,DATA_32 *B,ADDRESS N);
			//LinClip : 64-bit Natural Line Division
			//ㄙC[n]ˊA[n]㊣B[n]
			general(_PL_ D64_)(data_64 *C,DATA_64 *A,DATA_64 *B,ADDRESS N);
			//LinClip : 32-bit Real Line Division
			//ㄙC[n]ˊA[n]㊣B[n]
			general(_PL_ R32_)(real_32 *C,REAL_32 *A,REAL_32 *B,ADDRESS N);
			//LinClip : 64-bit Real Line Division
			//ㄙC[n]ˊA[n]㊣B[n]
			general(_PL_ R64_)(real_64 *C,REAL_64 *A,REAL_64 *B,ADDRESS N);
		}
		Div_2;

		//LinClip : Modulo Functions
		const struct
		{
			//LinClip : 8-bit Natural Line Modulo
			//ㄙC[n]ˊA[n]ㄔK
			general(_PL_ D08_)(data_08 *C,DATA_08 *A,DATA_08 K,ADDRESS N);
			//LinClip : 16-bit Natural Line Modulo
			//ㄙC[n]ˊA[n]ㄔK
			general(_PL_ D16_)(data_16 *C,DATA_16 *A,DATA_16 K,ADDRESS N);
			//LinClip : 32-bit Natural Line Modulo
			//ㄙC[n]ˊA[n]ㄔK
			general(_PL_ D32_)(data_32 *C,DATA_32 *A,DATA_32 K,ADDRESS N);
			//LinClip : 64-bit Natural Line Modulo
			//ㄙC[n]ˊA[n]ㄔK
			general(_PL_ D64_)(data_64 *C,DATA_64 *A,DATA_64 K,ADDRESS N);
			//LinClip : 8-bit Integer Line Modulo
			//ㄙC[n]ˊA[n]ㄔK
			general(_PL_ I08_)(inte_08 *C,INTE_08 *A,INTE_08 K,ADDRESS N);
			//LinClip : 16-bit Integer Line Modulo
			//ㄙC[n]ˊA[n]ㄔK
			general(_PL_ I16_)(inte_16 *C,INTE_16 *A,INTE_16 K,ADDRESS N);
			//LinClip : 32-bit Integer Line Modulo
			//ㄙC[n]ˊA[n]ㄔK
			general(_PL_ I32_)(inte_32 *C,INTE_32 *A,INTE_32 K,ADDRESS N);
			//LinClip : 64-bit Integer Line Modulo
			//ㄙC[n]ˊA[n]ㄔK
			general(_PL_ I64_)(inte_64 *C,INTE_64 *A,INTE_64 K,ADDRESS N);
		}
		Mod_1;

		//LinClip : Summation Functions
		const struct
		{
			//LinClip : 8-bit Integer Line Summation
			//ㄙSˊ３A[n]
			inte_08(_PL_ I08_)(INTE_08 *_R_ A,ADDRESS N);
			//LinClip : 16-bit Integer Line Summation
			//ㄙSˊ３A[n]
			inte_16(_PL_ I16_)(INTE_16 *_R_ A,ADDRESS N);
			//LinClip : 32-bit Integer Line Summation
			//ㄙSˊ３A[n]
			inte_32(_PL_ I32_)(INTE_32 *_R_ A,ADDRESS N);
			//LinClip : 64-bit Integer Line Summation
			//ㄙSˊ３A[n]
			inte_64(_PL_ I64_)(INTE_64 *_R_ A,ADDRESS N);
			//LinClip : 8-bit Natural Line Summation
			//ㄙSˊ３A[n]
			data_08(_PL_ D08_)(DATA_08 *_R_ A,ADDRESS N);
			//LinClip : 16-bit Natural Line Summation
			//ㄙSˊ３A[n]
			data_16(_PL_ D16_)(DATA_16 *_R_ A,ADDRESS N);
			//LinClip : 32-bit Natural Line Summation
			//ㄙSˊ３A[n]
			data_32(_PL_ D32_)(DATA_32 *_R_ A,ADDRESS N);
			//LinClip : 64-bit Natural Line Summation
			//ㄙSˊ３A[n]
			data_64(_PL_ D64_)(DATA_64 *_R_ A,ADDRESS N);
			//LinClip : 32-bit Real Line Summation
			//ㄙSˊ３A[n]
			real_32(_PL_ R32_)(REAL_32 *_R_ A,ADDRESS N);
			//LinClip : 64-bit Real Line Summation
			//ㄙSˊ３A[n]
			real_64(_PL_ R64_)(REAL_64 *_R_ A,ADDRESS N);
		}
		Sum_1;

		//LinClip : Dot Product Functions
		const struct
		{
			//LinClip : 8-bit Integer Line Dot Product
			//ㄙSˊ３A[n]▼B[n]
			inte_08(_PL_ I08_)(INTE_08 *A,INTE_08 *B,ADDRESS N);
			//LinClip : 16-bit Integer Line Dot Product
			//ㄙSˊ３A[n]▼B[n]
			inte_16(_PL_ I16_)(INTE_16 *A,INTE_16 *B,ADDRESS N);
			//LinClip : 32-bit Integer Line Dot Product
			//ㄙSˊ３A[n]▼B[n]
			inte_32(_PL_ I32_)(INTE_32 *A,INTE_32 *B,ADDRESS N);
			//LinClip : 64-bit Integer Line Dot Product
			//ㄙSˊ３A[n]▼B[n]
			inte_64(_PL_ I64_)(INTE_64 *A,INTE_64 *B,ADDRESS N);
			//LinClip : 8-bit Natural Line Dot Product
			//ㄙSˊ３A[n]▼B[n]
			data_08(_PL_ D08_)(DATA_08 *A,DATA_08 *B,ADDRESS N);
			//LinClip : 16-bit Natural Line Dot Product
			//ㄙSˊ３A[n]▼B[n]
			data_16(_PL_ D16_)(DATA_16 *A,DATA_16 *B,ADDRESS N);
			//LinClip : 32-bit Natural Line Dot Product
			//ㄙSˊ３A[n]▼B[n]
			data_32(_PL_ D32_)(DATA_32 *A,DATA_32 *B,ADDRESS N);
			//LinClip : 64-bit Natural Line Dot Product
			//ㄙSˊ３A[n]▼B[n]
			data_64(_PL_ D64_)(DATA_64 *A,DATA_64 *B,ADDRESS N);
			//LinClip : 32-bit Real Line Dot Product
			//ㄙSˊ３A[n]▼B[n]
			real_32(_PL_ R32_)(REAL_32 *A,REAL_32 *B,ADDRESS N);
			//LinClip : 64-bit Real Line Dot Product
			//ㄙSˊ３A[n]▼B[n]
			real_64(_PL_ R64_)(REAL_64 *A,REAL_64 *B,ADDRESS N);
		}
		Dot_2;

		//LinClip : Maximum Functions
		const struct
		{
			//LinClip : 8-Bit Integer Line Maximum
			//ㄙnˊargmax{A}
			address(_PL_ I08_)(INTE_08 _PL_ A,ADDRESS N);
			//LinClip : 16-Bit Integer Line Maximum
			//ㄙnˊargmax{A}
			address(_PL_ I16_)(INTE_16 _PL_ A,ADDRESS N);
			//LinClip : 32-Bit Integer Line Maximum
			//ㄙnˊargmax{A}
			address(_PL_ I32_)(INTE_32 _PL_ A,ADDRESS N);
			//LinClip : 64-Bit Integer Line Maximum
			//ㄙnˊargmax{A}
			address(_PL_ I64_)(INTE_64 _PL_ A,ADDRESS N);
			//LinClip : 8-Bit Natural Line Maximum
			//ㄙnˊargmax{A}
			address(_PL_ D08_)(DATA_08 _PL_ A,ADDRESS N);
			//LinClip : 16-Bit Natural Line Maximum
			//ㄙnˊargmax{A}
			address(_PL_ D16_)(DATA_16 _PL_ A,ADDRESS N);
			//LinClip : 32-Bit Natural Line Maximum
			//ㄙnˊargmax{A}
			address(_PL_ D32_)(DATA_32 _PL_ A,ADDRESS N);
			//LinClip : 64-Bit Natural Line Maximum
			//ㄙnˊargmax{A}
			address(_PL_ D64_)(DATA_64 _PL_ A,ADDRESS N);
			//LinClip : 32-Bit Real Line Maximum
			//ㄙnˊargmax{A}
			address(_PL_ R32_)(REAL_32 _PL_ A,ADDRESS N);
			//LinClip : 64-Bit Real Line Maximum
			//ㄙnˊargmax{A}
			address(_PL_ R64_)(REAL_64 _PL_ A,ADDRESS N);
		}
		Max_1;

		//LinClip : Minimum Functions
		const struct
		{
			//LinClip : 8-Bit Integer Line Minimum
			//ㄙnˊargmin{A}
			address(_PL_ I08_)(INTE_08 _PL_ A,ADDRESS N);
			//LinClip : 16-Bit Integer Line Minimum
			//ㄙnˊargmin{A}
			address(_PL_ I16_)(INTE_16 _PL_ A,ADDRESS N);
			//LinClip : 32-Bit Integer Line Minimum
			//ㄙnˊargmin{A}
			address(_PL_ I32_)(INTE_32 _PL_ A,ADDRESS N);
			//LinClip : 64-Bit Integer Line Minimum
			//ㄙnˊargmin{A}
			address(_PL_ I64_)(INTE_64 _PL_ A,ADDRESS N);
			//LinClip : 8-Bit Natural Line Minimum
			//ㄙnˊargmin{A}
			address(_PL_ D08_)(DATA_08 _PL_ A,ADDRESS N);
			//LinClip : 16-Bit Natural Line Minimum
			//ㄙnˊargmin{A}
			address(_PL_ D16_)(DATA_16 _PL_ A,ADDRESS N);
			//LinClip : 32-Bit Natural Line Minimum
			//ㄙnˊargmin{A}
			address(_PL_ D32_)(DATA_32 _PL_ A,ADDRESS N);
			//LinClip : 64-Bit Natural Line Minimum
			//ㄙnˊargmin{A}
			address(_PL_ D64_)(DATA_64 _PL_ A,ADDRESS N);
			//LinClip : 32-Bit Real Line Minimum
			//ㄙnˊargmin{A}
			address(_PL_ R32_)(REAL_32 _PL_ A,ADDRESS N);
			//LinClip : 64-Bit Real Line Minimum
			//ㄙnˊargmin{A}
			address(_PL_ R64_)(REAL_64 _PL_ A,ADDRESS N);
		}
		Min_1;

		//LinClip : Recursive Radix Sorting Functions
		const struct
		{
			//LinClip : 8-Bit Integer Recursive Radix Sorting
			//ㄙRequired (ValueLine) size is (Length)▼1 bytes.
			//﹛Required (IndexLine) size is (Length)▼sizeof(address) bytes.
			//﹛Required (Buffer) size is (Length)▼(sizeof(address)ㄚ1) bytes.
			//ㄙMode Null : Ascending Order
			//﹛Mode Full : Descending Order
			//ㄙ(ValueLine) and (IndexLine) should be initialized before processing.
			general(_PL_ I08_)(inte_08 _PL_ ValueLine,address _PL_ IndexLine,general _PL_ Buffer,ADDRESS Length,BOOLEAN Mode);
			//LinClip : 16-Bit Integer Recursive Radix Sorting
			//ㄙRequired (ValueLine) size is (Length)▼2 bytes.
			//﹛Required (IndexLine) size is (Length)▼sizeof(address) bytes.
			//﹛Required (Buffer) size is (Length)▼(sizeof(address)ㄚ2) bytes.
			//ㄙMode Null : Ascending Order
			//﹛Mode Full : Descending Order
			//ㄙ(ValueLine) and (IndexLine) should be initialized before processing.
			general(_PL_ I16_)(inte_16 _PL_ ValueLine,address _PL_ IndexLine,general _PL_ Buffer,ADDRESS Length,BOOLEAN Mode);
			//LinClip : 32-Bit Integer Recursive Radix Sorting
			//ㄙRequired (ValueLine) size is (Length)▼4 bytes.
			//﹛Required (IndexLine) size is (Length)▼sizeof(address) bytes.
			//﹛Required (Buffer) size is (Length)▼(sizeof(address)ㄚ4) bytes.
			//ㄙMode Null : Ascending Order
			//﹛Mode Full : Descending Order
			//ㄙ(ValueLine) and (IndexLine) should be initialized before processing.
			general(_PL_ I32_)(inte_32 _PL_ ValueLine,address _PL_ IndexLine,general _PL_ Buffer,ADDRESS Length,BOOLEAN Mode);
			//LinClip : 64-Bit Integer Recursive Radix Sorting
			//ㄙRequired (ValueLine) size is (Length)▼8 bytes.
			//﹛Required (IndexLine) size is (Length)▼sizeof(address) bytes.
			//﹛Required (Buffer) size is (Length)▼(sizeof(address)ㄚ8) bytes.
			//ㄙMode Null : Ascending Order
			//﹛Mode Full : Descending Order
			//ㄙ(ValueLine) and (IndexLine) should be initialized before processing.
			general(_PL_ I64_)(inte_64 _PL_ ValueLine,address _PL_ IndexLine,general _PL_ Buffer,ADDRESS Length,BOOLEAN Mode);
			//LinClip : 8-Bit Natural Recursive Radix Sorting
			//ㄙRequired (ValueLine) size is (Length)▼1 bytes.
			//﹛Required (IndexLine) size is (Length)▼sizeof(address) bytes.
			//﹛Required (Buffer) size is (Length)▼(sizeof(address)ㄚ1) bytes.
			//ㄙMode Null : Ascending Order
			//﹛Mode Full : Descending Order
			//ㄙ(ValueLine) and (IndexLine) should be initialized before processing.
			general(_PL_ D08_)(data_08 _PL_ ValueLine,address _PL_ IndexLine,general _PL_ Buffer,ADDRESS Length,BOOLEAN Mode);
			//LinClip : 16-Bit Natural Recursive Radix Sorting
			//ㄙRequired (ValueLine) size is (Length)▼2 bytes.
			//﹛Required (IndexLine) size is (Length)▼sizeof(address) bytes.
			//﹛Required (Buffer) size is (Length)▼(sizeof(address)ㄚ2) bytes.
			//ㄙMode Null : Ascending Order
			//﹛Mode Full : Descending Order
			//ㄙ(ValueLine) and (IndexLine) should be initialized before processing.
			general(_PL_ D16_)(data_16 _PL_ ValueLine,address _PL_ IndexLine,general _PL_ Buffer,ADDRESS Length,BOOLEAN Mode);
			//LinClip : 32-Bit Natural Recursive Radix Sorting
			//ㄙRequired (ValueLine) size is (Length)▼4 bytes.
			//﹛Required (IndexLine) size is (Length)▼sizeof(address) bytes.
			//﹛Required (Buffer) size is (Length)▼(sizeof(address)ㄚ4) bytes.
			//ㄙMode Null : Ascending Order
			//﹛Mode Full : Descending Order
			//ㄙ(ValueLine) and (IndexLine) should be initialized before processing.
			general(_PL_ D32_)(data_32 _PL_ ValueLine,address _PL_ IndexLine,general _PL_ Buffer,ADDRESS Length,BOOLEAN Mode);
			//LinClip : 64-Bit Natural Recursive Radix Sorting
			//ㄙRequired (ValueLine) size is (Length)▼8 bytes.
			//﹛Required (IndexLine) size is (Length)▼sizeof(address) bytes.
			//﹛Required (Buffer) size is (Length)▼(sizeof(address)ㄚ8) bytes.
			//ㄙMode Null : Ascending Order
			//﹛Mode Full : Descending Order
			//ㄙ(ValueLine) and (IndexLine) should be initialized before processing.
			general(_PL_ D64_)(data_64 _PL_ ValueLine,address _PL_ IndexLine,general _PL_ Buffer,ADDRESS Length,BOOLEAN Mode);
			//LinClip : 32-Bit Real Recursive Radix Sorting
			//ㄙRequired (ValueLine) size is (Length)▼4 bytes.
			//﹛Required (IndexLine) size is (Length)▼sizeof(address) bytes.
			//﹛Required (Buffer) size is (Length)▼(sizeof(address)ㄚ4) bytes.
			//ㄙMode Null : Ascending Order
			//﹛Mode Full : Descending Order
			//ㄙ(ValueLine) and (IndexLine) should be initialized before processing.
			general(_PL_ R32_)(real_32 _PL_ ValueLine,address _PL_ IndexLine,general _PL_ Buffer,ADDRESS Length,BOOLEAN Mode);
			//LinClip : 64-Bit Real Recursive Radix Sorting
			//ㄙRequired (ValueLine) size is (Length)▼8 bytes.
			//﹛Required (IndexLine) size is (Length)▼sizeof(address) bytes.
			//﹛Required (Buffer) size is (Length)▼(sizeof(address)ㄚ8) bytes.
			//ㄙMode Null : Ascending Order
			//﹛Mode Full : Descending Order
			//ㄙ(ValueLine) and (IndexLine) should be initialized before processing.
			general(_PL_ R64_)(real_64 _PL_ ValueLine,address _PL_ IndexLine,general _PL_ Buffer,ADDRESS Length,BOOLEAN Mode);
		}
		Order;

		//LinClip : Mapping Functions
		const struct
		{
			//LinClip : 8-Bit Integer Line Mapping
			//ㄙC[n]ˊT[I[n]]
			general(_PL_ I08_)(inte_08 *_R_ C,ADDRESS *_R_ I,INTE_08 _PL_ T,ADDRESS N);
			//LinClip : 16-Bit Integer Line Mapping
			//ㄙC[n]ˊT[I[n]]
			general(_PL_ I16_)(inte_16 *_R_ C,ADDRESS *_R_ I,INTE_16 _PL_ T,ADDRESS N);
			//LinClip : 32-Bit Integer Line Mapping
			//ㄙC[n]ˊT[I[n]]
			general(_PL_ I32_)(inte_32 *_R_ C,ADDRESS *_R_ I,INTE_32 _PL_ T,ADDRESS N);
			//LinClip : 64-Bit Integer Line Mapping
			//ㄙC[n]ˊT[I[n]]
			general(_PL_ I64_)(inte_64 *_R_ C,ADDRESS *_R_ I,INTE_64 _PL_ T,ADDRESS N);
			//LinClip : 8-Bit Natural Line Mapping
			//ㄙC[n]ˊT[I[n]]
			general(_PL_ D08_)(data_08 *_R_ C,ADDRESS *_R_ I,DATA_08 _PL_ T,ADDRESS N);
			//LinClip : 16-Bit Natural Line Mapping
			//ㄙC[n]ˊT[I[n]]
			general(_PL_ D16_)(data_16 *_R_ C,ADDRESS *_R_ I,DATA_16 _PL_ T,ADDRESS N);
			//LinClip : 32-Bit Natural Line Mapping
			//ㄙC[n]ˊT[I[n]]
			general(_PL_ D32_)(data_32 *_R_ C,ADDRESS *_R_ I,DATA_32 _PL_ T,ADDRESS N);
			//LinClip : 64-Bit Natural Line Mapping
			//ㄙC[n]ˊT[I[n]]
			general(_PL_ D64_)(data_64 *_R_ C,ADDRESS *_R_ I,DATA_64 _PL_ T,ADDRESS N);
			//LinClip : 32-Bit Real Line Mapping
			//ㄙC[n]ˊT[I[n]]
			general(_PL_ R32_)(real_32 *_R_ C,ADDRESS *_R_ I,REAL_32 _PL_ T,ADDRESS N);
			//LinClip : 64-Bit Real Line Mapping
			//ㄙC[n]ˊT[I[n]]
			general(_PL_ R64_)(real_64 *_R_ C,ADDRESS *_R_ I,REAL_64 _PL_ T,ADDRESS N);
		}
		Map_1;
	};
#endif

#if(Fold_(Domain:Device)&&defined(__OPENCL_H))
	//LinClip : OpenCL Function Set
	const struct
	{
		//LinClip : Program Build Functions
		const struct
		{
			//LinClip : Program Build into Binary Files with 8-bit String Path
			//ㄙThe number of binary paths must be same as the number of devices associated with the context.
			//ㄙ(BuildOption) Example : "-I ../../Headers -I ../../Sources -D _BitC_R16_=0 -D _BitC_R64_=1"
			//﹛(SourcePath) Example : "../../Kernels/linclip.cl"
			//﹛(BinaryPath) Example : { "../../Device 1/linclip.obj", "../../Device 2/linclip.obj", ... }
			general(_PL_ T08_)(oclc_co _PL_ Context,BYTE_08 _PL_ BuildOption,TEXT_08 _PL_ SourcePath,TEXT_08 _PL_ _PL_ BinaryPath,FILE _PL_ LogStream,oclc_ef _PL_ Error);
			//LinClip : Program Build into Binary Files with 16-bit String Path
			//ㄙThe number of binary paths must be same as the number of devices associated with the context.
			//ㄙ(BuildOption) Example : "-I ../../Headers -I ../../Sources -D _BitC_R16_=0 -D _BitC_R64_=1"
			//﹛(SourcePath) Example : "../../Kernels/linclip.cl"
			//﹛(BinaryPath) Example : { "../../Device 1/linclip.obj", "../../Device 2/linclip.obj", ... }
			general(_PL_ T16_)(oclc_co _PL_ Context,BYTE_08 _PL_ BuildOption,TEXT_16 _PL_ SourcePath,TEXT_16 _PL_ _PL_ BinaryPath,FILE _PL_ LogStream,oclc_ef _PL_ Error);
		}
		Ready;

		//LinClip : Program Creation Functions
		const struct
		{
			//LinClip : Program Manager Creation with 8-bit String Path - Delete with "OCLC.PM.Delete_"
			//ㄙThe number of binary paths must be same as the number of devices associated with the context.
			//ㄙ(BinaryPath) Example : { "../../Device 1/linclip.obj", "../../Device 2/linclip.obj", ... }
			oclc_pm*(_PL_ T08_)(oclc_co _PL_ Context,BYTE_08 _PL_ BuildOption,TEXT_08 _PL_ _PL_ BinaryPath,FILE _PL_ LogStream,oclc_ef _PL_ Error);
			//LinClip : Program Manager Creation with 16-bit String Path - Delete with "OCLC.PM.Delete_"
			//ㄙThe number of binary paths must be same as the number of devices associated with the context.
			//ㄙ(BinaryPath) Example : { "../../Device 1/linclip.obj", "../../Device 2/linclip.obj", ... }
			oclc_pm*(_PL_ T16_)(oclc_co _PL_ Context,BYTE_08 _PL_ BuildOption,TEXT_16 _PL_ _PL_ BinaryPath,FILE _PL_ LogStream,oclc_ef _PL_ Error);
		}
		Create;

		const struct
		{
			//LinClip : Increment
			//ㄙC and A's types should be same and one of BitC.Type.
			//ㄙRequired (Value) size is the type size of those to be calculated.
			general(_PL_ Inc_1_)(OCLC_PM _PL_,oclc_qo _PL_ Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Value,oclc_ef _PL_ Error);

			//LinClip : Amplification
			//ㄙC and A's types should be same and one of BitC.Type.
			//ㄙRequired (Value) size is the type size of those to be calculated.
			general(_PL_ Amp_1_)(OCLC_PM _PL_,oclc_qo _PL_ Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Value,oclc_ef _PL_ Error);

			//LinClip : Addition
			//ㄙC, A, and B's types should be same and one of BitC.Type.
			general(_PL_ Add_2_)(OCLC_PM _PL_,oclc_qo _PL_ Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ Error);

			//LinClip : Subtraction
			//ㄙC, A, and B's types should be same and one of BitC.Type.
			general(_PL_ Sub_2_)(OCLC_PM _PL_,oclc_qo _PL_ Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ Error);

			//LinClip : Multiplication
			//ㄙC, A, and B's types should be same and one of BitC.Type.
			general(_PL_ Mul_2_)(OCLC_PM _PL_,oclc_qo _PL_ Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ Error);

			//LinClip : Division
			//ㄙC and A's types should be same and one of BitC.Type.D## or BitC.Type.I##.
			//ㄙRequired (Value) size is the type size of those to be calculated.
			general(_PL_ Div_1_)(OCLC_PM _PL_,oclc_qo _PL_ Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Value,oclc_ef _PL_ Error);

			//LinClip : Inverse
			//ㄙC and A's types should be same and one of BitC.Type.
			//ㄙRequired (Value) size is the type size of those to be calculated.
			general(_PL_ Inv_1_)(OCLC_PM _PL_,oclc_qo _PL_ Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Value,oclc_ef _PL_ Error);

			//LinClip : Division
			//ㄙC, A, and B's types should be same and one of BitC.Type.
			general(_PL_ Div_2_)(OCLC_PM _PL_,oclc_qo _PL_ Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ Error);

			//LinClip : Modulo
			//ㄙC and A's types should be same and one of BitC.Type.D## or BitC.Type.I##.
			//ㄙRequired (Value) size is the type size of those to be calculated.
			general(_PL_ Mod_1_)(OCLC_PM _PL_,oclc_qo _PL_ Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Value,oclc_ef _PL_ Error);

			//LinClip : Summation
			//ㄙC and A's types should be same and one of BitC.Type.
			general(_PL_ Sum_1_)(OCLC_PM _PL_,oclc_qo _PL_ Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,OCLC_PA Axis,oclc_ef _PL_ Error);

			//LinClip : Dot Product
			//ㄙC, A, and B's types should be same and one of BitC.Type.
			general(_PL_ Dot_2_)(OCLC_PM _PL_,oclc_qo _PL_ Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,OCLC_PA Axis,oclc_ef _PL_ Error);

			//LinClip : Maximum
			//ㄙI's type size▼8 should be same as the device's address bits.
			//ㄙA's type should be one of BitC.Type.
			general(_PL_ Max_1_)(OCLC_PM _PL_,oclc_qo _PL_ Queue,OCLC_MH _PL_ AboutI,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,OCLC_PA Axis,oclc_ef _PL_ Error);

			//LinClip : Minimum
			//ㄙI's type size▼8 should be same as the device's address bits.
			//﹛A's type should be one of BitC.Type.
			general(_PL_ Min_1_)(OCLC_PM _PL_,oclc_qo _PL_ Queue,OCLC_MH _PL_ AboutI,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,OCLC_PA Axis,oclc_ef _PL_ Error);

			//LinClip : Mapping
			//ㄙI's type size▼8 should be same as the device's address bits.
			//﹛C and A's type sizes should be same.
			general(_PL_ Map_1_)(OCLC_PM _PL_,oclc_qo _PL_ Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutI,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,OCLC_PA Axis,oclc_ef _PL_ Error);
		};
	}
	CL;
#endif
}
LinC;
#endif
#endif
#endif
