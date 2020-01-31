#ifndef oLINCLIP_INC_
#define oLINCLIP_INC_ "LinC:2020.01.31"
/*------------------------------------------------------------------+
|	LinClip provides some elementary arithmetic operations.			|
|																	|
|	Written by Ranny Clover											|
|	http://github.com/dlOuOlb/Clips/blob/master/Headers/linclip.h	|
+-------------------------------------------------------------------+
|	Dependency:														|
|																	|
|	MSVClip -- MemClip -- PenClip -- OCLClip -- BitClip -- LinClip	|
+-------------------------------------------------------------------+
|	Note:															|
|																	|
|	Run "LinC.Okay.Wrap_();" to check whether the casted function	|
|	pointers work normally from inte_## types into data_## types.	|
+------------------------------------------------------------------*/

#include <bitclip.h>

#ifdef __OPENCL_VERSION__
#else

#if(Fold_(Library Casing))
//LinClip : Library Case Structure
typedef const struct
{
	const struct
	{
		//LinClip : Library Version - "LinC:yyyy.mm.dd"
		BYTE_08 _PL_ _R_ Version;

		//LinClip : Okay Function Set
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//LinClip : Check whether the casted functions work correctly for this library.
			logical(_PL_ Wrap_)(general);
		}
		Okay;

		//LinClip : Preserved for Future Usage
		ADDRESS xPreserved[2];
	};

	const struct
	{
		//LinClip : Arithmetic Progression Functions
		const struct
		{
			const union
			{
				const struct
				{
					//LinClip : 8-bit Integer Line Arithmetic Progression
					//＊C[n]＝S＋(n×K)
					general(_PL_ I08_)(inte_08 _PL_ _R_ C,INTE_08 S,INTE_08 K,ADDRESS N);
					//LinClip : 16-bit Integer Line Arithmetic Progression
					//＊C[n]＝S＋(n×K)
					general(_PL_ I16_)(inte_16 _PL_ _R_ C,INTE_16 S,INTE_16 K,ADDRESS N);
					//LinClip : 32-bit Integer Line Arithmetic Progression
					//＊C[n]＝S＋(n×K)
					general(_PL_ I32_)(inte_32 _PL_ _R_ C,INTE_32 S,INTE_32 K,ADDRESS N);
					//LinClip : 64-bit Integer Line Arithmetic Progression
					//＊C[n]＝S＋(n×K)
					general(_PL_ I64_)(inte_64 _PL_ _R_ C,INTE_64 S,INTE_64 K,ADDRESS N);
				};
				const struct
				{
					//LinClip : 8-bit Natural Line Arithmetic Progression
					//＊C[n]＝S＋(n×K)
					general(_PL_ D08_)(data_08 _PL_ _R_ C,DATA_08 S,DATA_08 K,ADDRESS N);
					//LinClip : 16-bit Natural Line Arithmetic Progression
					//＊C[n]＝S＋(n×K)
					general(_PL_ D16_)(data_16 _PL_ _R_ C,DATA_16 S,DATA_16 K,ADDRESS N);
					//LinClip : 32-bit Natural Line Arithmetic Progression
					//＊C[n]＝S＋(n×K)
					general(_PL_ D32_)(data_32 _PL_ _R_ C,DATA_32 S,DATA_32 K,ADDRESS N);
					//LinClip : 64-bit Natural Line Arithmetic Progression
					//＊C[n]＝S＋(n×K)
					general(_PL_ D64_)(data_64 _PL_ _R_ C,DATA_64 S,DATA_64 K,ADDRESS N);
				};
			};

			//LinClip : 32-bit Real Line Arithmetic Progression
			//＊C[n]＝S＋(n×K)
			general(_PL_ R32_)(real_32 _PL_ _R_ C,REAL_32 S,REAL_32 K,ADDRESS N);
			//LinClip : 64-bit Real Line Arithmetic Progression
			//＊C[n]＝S＋(n×K)
			general(_PL_ R64_)(real_64 _PL_ _R_ C,REAL_64 S,REAL_64 K,ADDRESS N);
		}
		Ari_0;

		//LinClip : Geometric Progression Functions
		const struct
		{
			const union
			{
				const struct
				{
					//LinClip : 8-bit Integer Line Geometric Progression
					//＊C[n]＝S×Kⁿ
					general(_PL_ I08_)(inte_08 _PL_ _R_ C,INTE_08 S,INTE_08 K,ADDRESS N);
					//LinClip : 16-bit Integer Line Geometric Progression
					//＊C[n]＝S×Kⁿ
					general(_PL_ I16_)(inte_16 _PL_ _R_ C,INTE_16 S,INTE_16 K,ADDRESS N);
					//LinClip : 32-bit Integer Line Geometric Progression
					//＊C[n]＝S×Kⁿ
					general(_PL_ I32_)(inte_32 _PL_ _R_ C,INTE_32 S,INTE_32 K,ADDRESS N);
					//LinClip : 64-bit Integer Line Geometric Progression
					//＊C[n]＝S×Kⁿ
					general(_PL_ I64_)(inte_64 _PL_ _R_ C,INTE_64 S,INTE_64 K,ADDRESS N);
				};
				const struct
				{
					//LinClip : 8-bit Natural Line Geometric Progression
					//＊C[n]＝S×Kⁿ
					general(_PL_ D08_)(data_08 _PL_ _R_ C,DATA_08 S,DATA_08 K,ADDRESS N);
					//LinClip : 16-bit Natural Line Geometric Progression
					//＊C[n]＝S×Kⁿ
					general(_PL_ D16_)(data_16 _PL_ _R_ C,DATA_16 S,DATA_16 K,ADDRESS N);
					//LinClip : 32-bit Natural Line Geometric Progression
					//＊C[n]＝S×Kⁿ
					general(_PL_ D32_)(data_32 _PL_ _R_ C,DATA_32 S,DATA_32 K,ADDRESS N);
					//LinClip : 64-bit Natural Line Geometric Progression
					//＊C[n]＝S×Kⁿ
					general(_PL_ D64_)(data_64 _PL_ _R_ C,DATA_64 S,DATA_64 K,ADDRESS N);
				};
			};

			//LinClip : 32-bit Real Line Geometric Progression
			//＊C[n]＝S×Kⁿ
			general(_PL_ R32_)(real_32 _PL_ _R_ C,REAL_32 S,REAL_32 K,ADDRESS N);
			//LinClip : 64-bit Real Line Geometric Progression
			//＊C[n]＝S×Kⁿ
			general(_PL_ R64_)(real_64 _PL_ _R_ C,REAL_64 S,REAL_64 K,ADDRESS N);
		}
		Geo_0;

		//LinClip : Increment Functions
		const struct
		{
			const union
			{
				const struct
				{
					//LinClip : 8-bit Integer Line Increment
					//＊C[n]＝A[n]＋K
					general(_PL_ I08_)(inte_08 _PL_ C,INTE_08 _PL_ A,INTE_08 K,ADDRESS N);
					//LinClip : 16-bit Integer Line Increment
					//＊C[n]＝A[n]＋K
					general(_PL_ I16_)(inte_16 _PL_ C,INTE_16 _PL_ A,INTE_16 K,ADDRESS N);
					//LinClip : 32-bit Integer Line Increment
					//＊C[n]＝A[n]＋K
					general(_PL_ I32_)(inte_32 _PL_ C,INTE_32 _PL_ A,INTE_32 K,ADDRESS N);
					//LinClip : 64-bit Integer Line Increment
					//＊C[n]＝A[n]＋K
					general(_PL_ I64_)(inte_64 _PL_ C,INTE_64 _PL_ A,INTE_64 K,ADDRESS N);
				};
				const struct
				{
					//LinClip : 8-bit Natural Line Increment
					//＊C[n]＝A[n]＋K
					general(_PL_ D08_)(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 K,ADDRESS N);
					//LinClip : 16-bit Natural Line Increment
					//＊C[n]＝A[n]＋K
					general(_PL_ D16_)(data_16 _PL_ C,DATA_16 _PL_ A,DATA_16 K,ADDRESS N);
					//LinClip : 32-bit Natural Line Increment
					//＊C[n]＝A[n]＋K
					general(_PL_ D32_)(data_32 _PL_ C,DATA_32 _PL_ A,DATA_32 K,ADDRESS N);
					//LinClip : 64-bit Natural Line Increment
					//＊C[n]＝A[n]＋K
					general(_PL_ D64_)(data_64 _PL_ C,DATA_64 _PL_ A,DATA_64 K,ADDRESS N);
				};
			};

			//LinClip : 32-bit Real Line Increment
			//＊C[n]＝A[n]＋K
			general(_PL_ R32_)(real_32 _PL_ C,REAL_32 _PL_ A,REAL_32 K,ADDRESS N);
			//LinClip : 64-bit Real Line Increment
			//＊C[n]＝A[n]＋K
			general(_PL_ R64_)(real_64 _PL_ C,REAL_64 _PL_ A,REAL_64 K,ADDRESS N);
		}
		Inc_1;

		//LinClip : Amplification Functions
		const struct
		{
			const union
			{
				const struct
				{
					//LinClip : 8-bit Integer Line Amplification
					//＊C[n]＝K×A[n]
					general(_PL_ I08_)(inte_08 _PL_ C,INTE_08 _PL_ A,INTE_08 K,ADDRESS N);
					//LinClip : 16-bit Integer Line Amplification
					//＊C[n]＝K×A[n]
					general(_PL_ I16_)(inte_16 _PL_ C,INTE_16 _PL_ A,INTE_16 K,ADDRESS N);
					//LinClip : 32-bit Integer Line Amplification
					//＊C[n]＝K×A[n]
					general(_PL_ I32_)(inte_32 _PL_ C,INTE_32 _PL_ A,INTE_32 K,ADDRESS N);
					//LinClip : 64-bit Integer Line Amplification
					//＊C[n]＝K×A[n]
					general(_PL_ I64_)(inte_64 _PL_ C,INTE_64 _PL_ A,INTE_64 K,ADDRESS N);
				};
				const struct
				{
					//LinClip : 8-bit Natural Line Amplification
					//＊C[n]＝K×A[n]
					general(_PL_ D08_)(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 K,ADDRESS N);
					//LinClip : 16-bit Natural Line Amplification
					//＊C[n]＝K×A[n]
					general(_PL_ D16_)(data_16 _PL_ C,DATA_16 _PL_ A,DATA_16 K,ADDRESS N);
					//LinClip : 32-bit Natural Line Amplification
					//＊C[n]＝K×A[n]
					general(_PL_ D32_)(data_32 _PL_ C,DATA_32 _PL_ A,DATA_32 K,ADDRESS N);
					//LinClip : 64-bit Natural Line Amplification
					//＊C[n]＝K×A[n]
					general(_PL_ D64_)(data_64 _PL_ C,DATA_64 _PL_ A,DATA_64 K,ADDRESS N);
				};
			};

			//LinClip : 32-bit Real Line Amplification
			//＊C[n]＝K×A[n]
			general(_PL_ R32_)(real_32 _PL_ C,REAL_32 _PL_ A,REAL_32 K,ADDRESS N);
			//LinClip : 64-bit Real Line Amplification
			//＊C[n]＝K×A[n]
			general(_PL_ R64_)(real_64 _PL_ C,REAL_64 _PL_ A,REAL_64 K,ADDRESS N);
		}
		Amp_1;

		//LinClip : Addition Functions
		const struct
		{
			const union
			{
				const struct
				{
					//LinClip : 8-bit Integer Line Addition
					//＊C[n]＝A[n]＋B[n]
					general(_PL_ I08_)(inte_08 _PL_ C,INTE_08 _PL_ A,INTE_08 _PL_ B,ADDRESS N);
					//LinClip : 16-bit Integer Line Addition
					//＊C[n]＝A[n]＋B[n]
					general(_PL_ I16_)(inte_16 _PL_ C,INTE_16 _PL_ A,INTE_16 _PL_ B,ADDRESS N);
					//LinClip : 32-bit Integer Line Addition
					//＊C[n]＝A[n]＋B[n]
					general(_PL_ I32_)(inte_32 _PL_ C,INTE_32 _PL_ A,INTE_32 _PL_ B,ADDRESS N);
					//LinClip : 64-bit Integer Line Addition
					//＊C[n]＝A[n]＋B[n]
					general(_PL_ I64_)(inte_64 _PL_ C,INTE_64 _PL_ A,INTE_64 _PL_ B,ADDRESS N);
				};
				const struct
				{
					//LinClip : 8-bit Natural Line Addition
					//＊C[n]＝A[n]＋B[n]
					general(_PL_ D08_)(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 _PL_ B,ADDRESS N);
					//LinClip : 16-bit Natural Line Addition
					//＊C[n]＝A[n]＋B[n]
					general(_PL_ D16_)(data_16 _PL_ C,DATA_16 _PL_ A,DATA_16 _PL_ B,ADDRESS N);
					//LinClip : 32-bit Natural Line Addition
					//＊C[n]＝A[n]＋B[n]
					general(_PL_ D32_)(data_32 _PL_ C,DATA_32 _PL_ A,DATA_32 _PL_ B,ADDRESS N);
					//LinClip : 64-bit Natural Line Addition
					//＊C[n]＝A[n]＋B[n]
					general(_PL_ D64_)(data_64 _PL_ C,DATA_64 _PL_ A,DATA_64 _PL_ B,ADDRESS N);
				};
			};

			//LinClip : 32-bit Real Line Addition
			//＊C[n]＝A[n]＋B[n]
			general(_PL_ R32_)(real_32 _PL_ C,REAL_32 _PL_ A,REAL_32 _PL_ B,ADDRESS N);
			//LinClip : 64-bit Real Line Addition
			//＊C[n]＝A[n]＋B[n]
			general(_PL_ R64_)(real_64 _PL_ C,REAL_64 _PL_ A,REAL_64 _PL_ B,ADDRESS N);
		}
		Add_2;

		//LinClip : Subtraction Functions
		const struct
		{
			const union
			{
				const struct
				{
					//LinClip : 8-bit Integer Line Subtraction
					//＊C[n]＝A[n]－B[n]
					general(_PL_ I08_)(inte_08 _PL_ C,INTE_08 _PL_ A,INTE_08 _PL_ B,ADDRESS N);
					//LinClip : 16-bit Integer Line Subtraction
					//＊C[n]＝A[n]－B[n]
					general(_PL_ I16_)(inte_16 _PL_ C,INTE_16 _PL_ A,INTE_16 _PL_ B,ADDRESS N);
					//LinClip : 32-bit Integer Line Subtraction
					//＊C[n]＝A[n]－B[n]
					general(_PL_ I32_)(inte_32 _PL_ C,INTE_32 _PL_ A,INTE_32 _PL_ B,ADDRESS N);
					//LinClip : 64-bit Integer Line Subtraction
					//＊C[n]＝A[n]－B[n]
					general(_PL_ I64_)(inte_64 _PL_ C,INTE_64 _PL_ A,INTE_64 _PL_ B,ADDRESS N);
				};
				const struct
				{
					//LinClip : 8-bit Natural Line Subtraction
					//＊C[n]＝A[n]－B[n]
					general(_PL_ D08_)(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 _PL_ B,ADDRESS N);
					//LinClip : 16-bit Natural Line Subtraction
					//＊C[n]＝A[n]－B[n]
					general(_PL_ D16_)(data_16 _PL_ C,DATA_16 _PL_ A,DATA_16 _PL_ B,ADDRESS N);
					//LinClip : 32-bit Natural Line Subtraction
					//＊C[n]＝A[n]－B[n]
					general(_PL_ D32_)(data_32 _PL_ C,DATA_32 _PL_ A,DATA_32 _PL_ B,ADDRESS N);
					//LinClip : 64-bit Natural Line Subtraction
					//＊C[n]＝A[n]－B[n]
					general(_PL_ D64_)(data_64 _PL_ C,DATA_64 _PL_ A,DATA_64 _PL_ B,ADDRESS N);
				};
			};

			//LinClip : 32-bit Real Line Subtraction
			//＊C[n]＝A[n]－B[n]
			general(_PL_ R32_)(real_32 _PL_ C,REAL_32 _PL_ A,REAL_32 _PL_ B,ADDRESS N);
			//LinClip : 64-bit Real Line Subtraction
			//＊C[n]＝A[n]－B[n]
			general(_PL_ R64_)(real_64 _PL_ C,REAL_64 _PL_ A,REAL_64 _PL_ B,ADDRESS N);
		}
		Sub_2;

		//LinClip : Multiplication Functions
		const struct
		{
			const union
			{
				const struct
				{
					//LinClip : 8-bit Integer Line Multiplication
					//＊C[n]＝A[n]×B[n]
					general(_PL_ I08_)(inte_08 _PL_ C,INTE_08 _PL_ A,INTE_08 _PL_ B,ADDRESS N);
					//LinClip : 16-bit Integer Line Multiplication
					//＊C[n]＝A[n]×B[n]
					general(_PL_ I16_)(inte_16 _PL_ C,INTE_16 _PL_ A,INTE_16 _PL_ B,ADDRESS N);
					//LinClip : 32-bit Integer Line Multiplication
					//＊C[n]＝A[n]×B[n]
					general(_PL_ I32_)(inte_32 _PL_ C,INTE_32 _PL_ A,INTE_32 _PL_ B,ADDRESS N);
					//LinClip : 64-bit Integer Line Multiplication
					//＊C[n]＝A[n]×B[n]
					general(_PL_ I64_)(inte_64 _PL_ C,INTE_64 _PL_ A,INTE_64 _PL_ B,ADDRESS N);
				};
				const struct
				{
					//LinClip : 8-bit Natural Line Multiplication
					//＊C[n]＝A[n]×B[n]
					general(_PL_ D08_)(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 _PL_ B,ADDRESS N);
					//LinClip : 16-bit Natural Line Multiplication
					//＊C[n]＝A[n]×B[n]
					general(_PL_ D16_)(data_16 _PL_ C,DATA_16 _PL_ A,DATA_16 _PL_ B,ADDRESS N);
					//LinClip : 32-bit Natural Line Multiplication
					//＊C[n]＝A[n]×B[n]
					general(_PL_ D32_)(data_32 _PL_ C,DATA_32 _PL_ A,DATA_32 _PL_ B,ADDRESS N);
					//LinClip : 64-bit Natural Line Multiplication
					//＊C[n]＝A[n]×B[n]
					general(_PL_ D64_)(data_64 _PL_ C,DATA_64 _PL_ A,DATA_64 _PL_ B,ADDRESS N);
				};
			};
			
			//LinClip : 32-bit Real Line Multiplication
			//＊C[n]＝A[n]×B[n]
			general(_PL_ R32_)(real_32 _PL_ C,REAL_32 _PL_ A,REAL_32 _PL_ B,ADDRESS N);
			//LinClip : 64-bit Real Line Multiplication
			//＊C[n]＝A[n]×B[n]
			general(_PL_ R64_)(real_64 _PL_ C,REAL_64 _PL_ A,REAL_64 _PL_ B,ADDRESS N);
		}
		Mul_2;

		//LinClip : Division Functions
		const struct
		{
			//LinClip : 8-bit Integer Line Division
			//＊C[n]＝A[n]÷K
			general(_PL_ I08_)(inte_08 _PL_ C,INTE_08 _PL_ A,INTE_08 K,ADDRESS N);
			//LinClip : 16-bit Integer Line Division
			//＊C[n]＝A[n]÷K
			general(_PL_ I16_)(inte_16 _PL_ C,INTE_16 _PL_ A,INTE_16 K,ADDRESS N);
			//LinClip : 32-bit Integer Line Division
			//＊C[n]＝A[n]÷K
			general(_PL_ I32_)(inte_32 _PL_ C,INTE_32 _PL_ A,INTE_32 K,ADDRESS N);
			//LinClip : 64-bit Integer Line Division
			//＊C[n]＝A[n]÷K
			general(_PL_ I64_)(inte_64 _PL_ C,INTE_64 _PL_ A,INTE_64 K,ADDRESS N);
			//LinClip : 8-bit Natural Line Division
			//＊C[n]＝A[n]÷K
			general(_PL_ D08_)(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 K,ADDRESS N);
			//LinClip : 16-bit Natural Line Division
			//＊C[n]＝A[n]÷K
			general(_PL_ D16_)(data_16 _PL_ C,DATA_16 _PL_ A,DATA_16 K,ADDRESS N);
			//LinClip : 32-bit Natural Line Division
			//＊C[n]＝A[n]÷K
			general(_PL_ D32_)(data_32 _PL_ C,DATA_32 _PL_ A,DATA_32 K,ADDRESS N);
			//LinClip : 64-bit Natural Line Division
			//＊C[n]＝A[n]÷K
			general(_PL_ D64_)(data_64 _PL_ C,DATA_64 _PL_ A,DATA_64 K,ADDRESS N);
		}
		Div_1;

		//LinClip : Inverse Functions
		const struct
		{
			//LinClip : 8-bit Integer Line Inverse
			//＊C[n]＝K÷A[n]
			general(_PL_ I08_)(inte_08 _PL_ C,INTE_08 _PL_ A,INTE_08 K,ADDRESS N);
			//LinClip : 16-bit Integer Line Inverse
			//＊C[n]＝K÷A[n]
			general(_PL_ I16_)(inte_16 _PL_ C,INTE_16 _PL_ A,INTE_16 K,ADDRESS N);
			//LinClip : 32-bit Integer Line Inverse
			//＊C[n]＝K÷A[n]
			general(_PL_ I32_)(inte_32 _PL_ C,INTE_32 _PL_ A,INTE_32 K,ADDRESS N);
			//LinClip : 64-bit Integer Line Inverse
			//＊C[n]＝K÷A[n]
			general(_PL_ I64_)(inte_64 _PL_ C,INTE_64 _PL_ A,INTE_64 K,ADDRESS N);
			//LinClip : 8-bit Natural Line Inverse
			//＊C[n]＝K÷A[n]
			general(_PL_ D08_)(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 K,ADDRESS N);
			//LinClip : 16-bit Natural Line Inverse
			//＊C[n]＝K÷A[n]
			general(_PL_ D16_)(data_16 _PL_ C,DATA_16 _PL_ A,DATA_16 K,ADDRESS N);
			//LinClip : 32-bit Natural Line Inverse
			//＊C[n]＝K÷A[n]
			general(_PL_ D32_)(data_32 _PL_ C,DATA_32 _PL_ A,DATA_32 K,ADDRESS N);
			//LinClip : 64-bit Natural Line Inverse
			//＊C[n]＝K÷A[n]
			general(_PL_ D64_)(data_64 _PL_ C,DATA_64 _PL_ A,DATA_64 K,ADDRESS N);
			//LinClip : 32-bit Real Line Inverse
			//＊C[n]＝K÷A[n]
			general(_PL_ R32_)(real_32 _PL_ C,REAL_32 _PL_ A,REAL_32 K,ADDRESS N);
			//LinClip : 64-bit Real Line Inverse
			//＊C[n]＝K÷A[n]
			general(_PL_ R64_)(real_64 _PL_ C,REAL_64 _PL_ A,REAL_64 K,ADDRESS N);
		}
		Inv_1;

		//LinClip : Division Functions
		const struct
		{
			//LinClip : 8-bit Integer Line Division
			//＊C[n]＝A[n]÷B[n]
			general(_PL_ I08_)(inte_08 _PL_ C,INTE_08 _PL_ A,INTE_08 _PL_ B,ADDRESS N);
			//LinClip : 16-bit Integer Line Division
			//＊C[n]＝A[n]÷B[n]
			general(_PL_ I16_)(inte_16 _PL_ C,INTE_16 _PL_ A,INTE_16 _PL_ B,ADDRESS N);
			//LinClip : 32-bit Integer Line Division
			//＊C[n]＝A[n]÷B[n]
			general(_PL_ I32_)(inte_32 _PL_ C,INTE_32 _PL_ A,INTE_32 _PL_ B,ADDRESS N);
			//LinClip : 64-bit Integer Line Division
			//＊C[n]＝A[n]÷B[n]
			general(_PL_ I64_)(inte_64 _PL_ C,INTE_64 _PL_ A,INTE_64 _PL_ B,ADDRESS N);
			//LinClip : 8-bit Natural Line Division
			//＊C[n]＝A[n]÷B[n]
			general(_PL_ D08_)(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 _PL_ B,ADDRESS N);
			//LinClip : 16-bit Natural Line Division
			//＊C[n]＝A[n]÷B[n]
			general(_PL_ D16_)(data_16 _PL_ C,DATA_16 _PL_ A,DATA_16 _PL_ B,ADDRESS N);
			//LinClip : 32-bit Natural Line Division
			//＊C[n]＝A[n]÷B[n]
			general(_PL_ D32_)(data_32 _PL_ C,DATA_32 _PL_ A,DATA_32 _PL_ B,ADDRESS N);
			//LinClip : 64-bit Natural Line Division
			//＊C[n]＝A[n]÷B[n]
			general(_PL_ D64_)(data_64 _PL_ C,DATA_64 _PL_ A,DATA_64 _PL_ B,ADDRESS N);
			//LinClip : 32-bit Real Line Division
			//＊C[n]＝A[n]÷B[n]
			general(_PL_ R32_)(real_32 _PL_ C,REAL_32 _PL_ A,REAL_32 _PL_ B,ADDRESS N);
			//LinClip : 64-bit Real Line Division
			//＊C[n]＝A[n]÷B[n]
			general(_PL_ R64_)(real_64 _PL_ C,REAL_64 _PL_ A,REAL_64 _PL_ B,ADDRESS N);
		}
		Div_2;

		//LinClip : Modulo Functions
		const struct
		{
			//LinClip : 8-bit Natural Line Modulo
			//＊C[n]＝A[n]％K
			general(_PL_ D08_)(data_08 _PL_ C,DATA_08 _PL_ A,DATA_08 K,ADDRESS N);
			//LinClip : 16-bit Natural Line Modulo
			//＊C[n]＝A[n]％K
			general(_PL_ D16_)(data_16 _PL_ C,DATA_16 _PL_ A,DATA_16 K,ADDRESS N);
			//LinClip : 32-bit Natural Line Modulo
			//＊C[n]＝A[n]％K
			general(_PL_ D32_)(data_32 _PL_ C,DATA_32 _PL_ A,DATA_32 K,ADDRESS N);
			//LinClip : 64-bit Natural Line Modulo
			//＊C[n]＝A[n]％K
			general(_PL_ D64_)(data_64 _PL_ C,DATA_64 _PL_ A,DATA_64 K,ADDRESS N);
			//LinClip : 8-bit Integer Line Modulo
			//＊C[n]＝A[n]％K
			general(_PL_ I08_)(inte_08 _PL_ C,INTE_08 _PL_ A,INTE_08 K,ADDRESS N);
			//LinClip : 16-bit Integer Line Modulo
			//＊C[n]＝A[n]％K
			general(_PL_ I16_)(inte_16 _PL_ C,INTE_16 _PL_ A,INTE_16 K,ADDRESS N);
			//LinClip : 32-bit Integer Line Modulo
			//＊C[n]＝A[n]％K
			general(_PL_ I32_)(inte_32 _PL_ C,INTE_32 _PL_ A,INTE_32 K,ADDRESS N);
			//LinClip : 64-bit Integer Line Modulo
			//＊C[n]＝A[n]％K
			general(_PL_ I64_)(inte_64 _PL_ C,INTE_64 _PL_ A,INTE_64 K,ADDRESS N);
		}
		Mod_1;

		//LinClip : Summation Functions
		const struct
		{
			const union
			{
				const struct
				{
					//LinClip : 8-bit Integer Line Summation
					//＊S＝∑A[n]
					inte_08(_PL_ I08_)(INTE_08 _PL_ _R_ A,ADDRESS N);
					//LinClip : 16-bit Integer Line Summation
					//＊S＝∑A[n]
					inte_16(_PL_ I16_)(INTE_16 _PL_ _R_ A,ADDRESS N);
					//LinClip : 32-bit Integer Line Summation
					//＊S＝∑A[n]
					inte_32(_PL_ I32_)(INTE_32 _PL_ _R_ A,ADDRESS N);
					//LinClip : 64-bit Integer Line Summation
					//＊S＝∑A[n]
					inte_64(_PL_ I64_)(INTE_64 _PL_ _R_ A,ADDRESS N);
				};
				const struct
				{
					//LinClip : 8-bit Natural Line Summation
					//＊S＝∑A[n]
					data_08(_PL_ D08_)(DATA_08 _PL_ _R_ A,ADDRESS N);
					//LinClip : 16-bit Natural Line Summation
					//＊S＝∑A[n]
					data_16(_PL_ D16_)(DATA_16 _PL_ _R_ A,ADDRESS N);
					//LinClip : 32-bit Natural Line Summation
					//＊S＝∑A[n]
					data_32(_PL_ D32_)(DATA_32 _PL_ _R_ A,ADDRESS N);
					//LinClip : 64-bit Natural Line Summation
					//＊S＝∑A[n]
					data_64(_PL_ D64_)(DATA_64 _PL_ _R_ A,ADDRESS N);
				};
			};

			//LinClip : 32-bit Real Line Summation
			//＊S＝∑A[n]
			real_32(_PL_ R32_)(REAL_32 _PL_ _R_ A,ADDRESS N);
			//LinClip : 64-bit Real Line Summation
			//＊S＝∑A[n]
			real_64(_PL_ R64_)(REAL_64 _PL_ _R_ A,ADDRESS N);
		}
		Sum_1;

		//LinClip : Dot Product Functions
		const struct
		{
			const union
			{
				const struct
				{
					//LinClip : 8-bit Integer Line Dot Product
					//＊S＝∑A[n]×B[n]
					inte_08(_PL_ I08_)(INTE_08 _PL_ A,INTE_08 _PL_ B,ADDRESS N);
					//LinClip : 16-bit Integer Line Dot Product
					//＊S＝∑A[n]×B[n]
					inte_16(_PL_ I16_)(INTE_16 _PL_ A,INTE_16 _PL_ B,ADDRESS N);
					//LinClip : 32-bit Integer Line Dot Product
					//＊S＝∑A[n]×B[n]
					inte_32(_PL_ I32_)(INTE_32 _PL_ A,INTE_32 _PL_ B,ADDRESS N);
					//LinClip : 64-bit Integer Line Dot Product
					//＊S＝∑A[n]×B[n]
					inte_64(_PL_ I64_)(INTE_64 _PL_ A,INTE_64 _PL_ B,ADDRESS N);
				};
				const struct
				{
					//LinClip : 8-bit Natural Line Dot Product
					//＊S＝∑A[n]×B[n]
					data_08(_PL_ D08_)(DATA_08 _PL_ A,DATA_08 _PL_ B,ADDRESS N);
					//LinClip : 16-bit Natural Line Dot Product
					//＊S＝∑A[n]×B[n]
					data_16(_PL_ D16_)(DATA_16 _PL_ A,DATA_16 _PL_ B,ADDRESS N);
					//LinClip : 32-bit Natural Line Dot Product
					//＊S＝∑A[n]×B[n]
					data_32(_PL_ D32_)(DATA_32 _PL_ A,DATA_32 _PL_ B,ADDRESS N);
					//LinClip : 64-bit Natural Line Dot Product
					//＊S＝∑A[n]×B[n]
					data_64(_PL_ D64_)(DATA_64 _PL_ A,DATA_64 _PL_ B,ADDRESS N);
				};
			};

			//LinClip : 32-bit Real Line Dot Product
			//＊S＝∑A[n]×B[n]
			real_32(_PL_ R32_)(REAL_32 _PL_ A,REAL_32 _PL_ B,ADDRESS N);
			//LinClip : 64-bit Real Line Dot Product
			//＊S＝∑A[n]×B[n]
			real_64(_PL_ R64_)(REAL_64 _PL_ A,REAL_64 _PL_ B,ADDRESS N);
		}
		Dot_2;

		//LinClip : Maximum Functions
		const struct
		{
			//LinClip : 8-Bit Integer Line Maximum
			//＊n＝argmax{A}
			address(_PL_ I08_)(INTE_08 _PL_ A,ADDRESS N);
			//LinClip : 16-Bit Integer Line Maximum
			//＊n＝argmax{A}
			address(_PL_ I16_)(INTE_16 _PL_ A,ADDRESS N);
			//LinClip : 32-Bit Integer Line Maximum
			//＊n＝argmax{A}
			address(_PL_ I32_)(INTE_32 _PL_ A,ADDRESS N);
			//LinClip : 64-Bit Integer Line Maximum
			//＊n＝argmax{A}
			address(_PL_ I64_)(INTE_64 _PL_ A,ADDRESS N);
			//LinClip : 8-Bit Natural Line Maximum
			//＊n＝argmax{A}
			address(_PL_ D08_)(DATA_08 _PL_ A,ADDRESS N);
			//LinClip : 16-Bit Natural Line Maximum
			//＊n＝argmax{A}
			address(_PL_ D16_)(DATA_16 _PL_ A,ADDRESS N);
			//LinClip : 32-Bit Natural Line Maximum
			//＊n＝argmax{A}
			address(_PL_ D32_)(DATA_32 _PL_ A,ADDRESS N);
			//LinClip : 64-Bit Natural Line Maximum
			//＊n＝argmax{A}
			address(_PL_ D64_)(DATA_64 _PL_ A,ADDRESS N);
			//LinClip : 32-Bit Real Line Maximum
			//＊n＝argmax{A}
			address(_PL_ R32_)(REAL_32 _PL_ A,ADDRESS N);
			//LinClip : 64-Bit Real Line Maximum
			//＊n＝argmax{A}
			address(_PL_ R64_)(REAL_64 _PL_ A,ADDRESS N);
		}
		Max_1;

		//LinClip : Minimum Functions
		const struct
		{
			//LinClip : 8-Bit Integer Line Minimum
			//＊n＝argmin{A}
			address(_PL_ I08_)(INTE_08 _PL_ A,ADDRESS N);
			//LinClip : 16-Bit Integer Line Minimum
			//＊n＝argmin{A}
			address(_PL_ I16_)(INTE_16 _PL_ A,ADDRESS N);
			//LinClip : 32-Bit Integer Line Minimum
			//＊n＝argmin{A}
			address(_PL_ I32_)(INTE_32 _PL_ A,ADDRESS N);
			//LinClip : 64-Bit Integer Line Minimum
			//＊n＝argmin{A}
			address(_PL_ I64_)(INTE_64 _PL_ A,ADDRESS N);
			//LinClip : 8-Bit Natural Line Minimum
			//＊n＝argmin{A}
			address(_PL_ D08_)(DATA_08 _PL_ A,ADDRESS N);
			//LinClip : 16-Bit Natural Line Minimum
			//＊n＝argmin{A}
			address(_PL_ D16_)(DATA_16 _PL_ A,ADDRESS N);
			//LinClip : 32-Bit Natural Line Minimum
			//＊n＝argmin{A}
			address(_PL_ D32_)(DATA_32 _PL_ A,ADDRESS N);
			//LinClip : 64-Bit Natural Line Minimum
			//＊n＝argmin{A}
			address(_PL_ D64_)(DATA_64 _PL_ A,ADDRESS N);
			//LinClip : 32-Bit Real Line Minimum
			//＊n＝argmin{A}
			address(_PL_ R32_)(REAL_32 _PL_ A,ADDRESS N);
			//LinClip : 64-Bit Real Line Minimum
			//＊n＝argmin{A}
			address(_PL_ R64_)(REAL_64 _PL_ A,ADDRESS N);
		}
		Min_1;

		//LinClip : Recursive Radix Sorting Functions
		const struct
		{
			//LinClip : 8-Bit Integer Recursive Radix Sorting
			//＊Required (ValueLine) size is (Length)×1 bytes.
			//　If (IndexLine) is not NULL,
			//　then required (IndexLine) size is (Length)×sizeof(address) bytes,
			//　and required (Buffer) size is (Length)×(sizeof(address)＋1) bytes,
			//　else required (Buffer) size is (Length)×1 bytes.
			//＊Mode 0 : Ascending Order
			//　Mode 1 : Descending Order
			//＊(ValueLine) and (IndexLine) should be initialized before processing.
			general(_PL_ I08_)(inte_08 _PL_ _R_ ValueLine,address _PL_ _R_ IndexLine,general _PL_ _R_ Buffer,ADDRESS Length,LOGICAL Mode);
			//LinClip : 16-Bit Integer Recursive Radix Sorting
			//＊Required (ValueLine) size is (Length)×2 bytes.
			//　If (IndexLine) is not NULL,
			//　then required (IndexLine) size is (Length)×sizeof(address) bytes,
			//　and required (Buffer) size is (Length)×(sizeof(address)＋2) bytes,
			//　else required (Buffer) size is (Length)×2 bytes.
			//＊Mode 0 : Ascending Order
			//　Mode 1 : Descending Order
			//＊(ValueLine) and (IndexLine) should be initialized before processing.
			general(_PL_ I16_)(inte_16 _PL_ _R_ ValueLine,address _PL_ _R_ IndexLine,general _PL_ _R_ Buffer,ADDRESS Length,LOGICAL Mode);
			//LinClip : 32-Bit Integer Recursive Radix Sorting
			//＊Required (ValueLine) size is (Length)×4 bytes.
			//　If (IndexLine) is not NULL,
			//　then required (IndexLine) size is (Length)×sizeof(address) bytes,
			//　and required (Buffer) size is (Length)×(sizeof(address)＋4) bytes,
			//　else required (Buffer) size is (Length)×4 bytes.
			//＊Mode 0 : Ascending Order
			//　Mode 1 : Descending Order
			//＊(ValueLine) and (IndexLine) should be initialized before processing.
			general(_PL_ I32_)(inte_32 _PL_ _R_ ValueLine,address _PL_ _R_ IndexLine,general _PL_ _R_ Buffer,ADDRESS Length,LOGICAL Mode);
			//LinClip : 64-Bit Integer Recursive Radix Sorting
			//＊Required (ValueLine) size is (Length)×8 bytes.
			//　If (IndexLine) is not NULL,
			//　then required (IndexLine) size is (Length)×sizeof(address) bytes,
			//　and required (Buffer) size is (Length)×(sizeof(address)＋8) bytes,
			//　else required (Buffer) size is (Length)×8 bytes.
			//＊Mode 0 : Ascending Order
			//　Mode 1 : Descending Order
			//＊(ValueLine) and (IndexLine) should be initialized before processing.
			general(_PL_ I64_)(inte_64 _PL_ _R_ ValueLine,address _PL_ _R_ IndexLine,general _PL_ _R_ Buffer,ADDRESS Length,LOGICAL Mode);
			//LinClip : 8-Bit Natural Recursive Radix Sorting
			//＊Required (ValueLine) size is (Length)×1 bytes.
			//　If (IndexLine) is not NULL,
			//　then required (IndexLine) size is (Length)×sizeof(address) bytes,
			//　and required (Buffer) size is (Length)×(sizeof(address)＋1) bytes,
			//　else required (Buffer) size is (Length)×1 bytes.
			//＊Mode 0 : Ascending Order
			//　Mode 1 : Descending Order
			//＊(ValueLine) and (IndexLine) should be initialized before processing.
			general(_PL_ D08_)(data_08 _PL_ _R_ ValueLine,address _PL_ _R_ IndexLine,general _PL_ _R_ Buffer,ADDRESS Length,LOGICAL Mode);
			//LinClip : 16-Bit Natural Recursive Radix Sorting
			//＊Required (ValueLine) size is (Length)×2 bytes.
			//　If (IndexLine) is not NULL,
			//　then required (IndexLine) size is (Length)×sizeof(address) bytes,
			//　and required (Buffer) size is (Length)×(sizeof(address)＋2) bytes,
			//　else required (Buffer) size is (Length)×2 bytes.
			//＊Mode 0 : Ascending Order
			//　Mode 1 : Descending Order
			//＊(ValueLine) and (IndexLine) should be initialized before processing.
			general(_PL_ D16_)(data_16 _PL_ _R_ ValueLine,address _PL_ _R_ IndexLine,general _PL_ _R_ Buffer,ADDRESS Length,LOGICAL Mode);
			//LinClip : 32-Bit Natural Recursive Radix Sorting
			//＊Required (ValueLine) size is (Length)×4 bytes.
			//　If (IndexLine) is not NULL,
			//　then required (IndexLine) size is (Length)×sizeof(address) bytes,
			//　and required (Buffer) size is (Length)×(sizeof(address)＋4) bytes,
			//　else required (Buffer) size is (Length)×4 bytes.
			//＊Mode 0 : Ascending Order
			//　Mode 1 : Descending Order
			//＊(ValueLine) and (IndexLine) should be initialized before processing.
			general(_PL_ D32_)(data_32 _PL_ _R_ ValueLine,address _PL_ _R_ IndexLine,general _PL_ _R_ Buffer,ADDRESS Length,LOGICAL Mode);
			//LinClip : 64-Bit Natural Recursive Radix Sorting
			//＊Required (ValueLine) size is (Length)×8 bytes.
			//　If (IndexLine) is not NULL,
			//　then required (IndexLine) size is (Length)×sizeof(address) bytes,
			//　and required (Buffer) size is (Length)×(sizeof(address)＋8) bytes,
			//　else required (Buffer) size is (Length)×8 bytes.
			//＊Mode 0 : Ascending Order
			//　Mode 1 : Descending Order
			//＊(ValueLine) and (IndexLine) should be initialized before processing.
			general(_PL_ D64_)(data_64 _PL_ _R_ ValueLine,address _PL_ _R_ IndexLine,general _PL_ _R_ Buffer,ADDRESS Length,LOGICAL Mode);
			//LinClip : 32-Bit Real Recursive Radix Sorting
			//＊Required (ValueLine) size is (Length)×4 bytes.
			//　If (IndexLine) is not NULL,
			//　then required (IndexLine) size is (Length)×sizeof(address) bytes,
			//　and required (Buffer) size is (Length)×(sizeof(address)＋4) bytes,
			//　else required (Buffer) size is (Length)×4 bytes.
			//＊Mode 0 : Ascending Order
			//　Mode 1 : Descending Order
			//＊(ValueLine) and (IndexLine) should be initialized before processing.
			general(_PL_ R32_)(real_32 _PL_ _R_ ValueLine,address _PL_ _R_ IndexLine,general _PL_ _R_ Buffer,ADDRESS Length,LOGICAL Mode);
			//LinClip : 64-Bit Real Recursive Radix Sorting
			//＊Required (ValueLine) size is (Length)×8 bytes.
			//　If (IndexLine) is not NULL,
			//　then required (IndexLine) size is (Length)×sizeof(address) bytes,
			//　and required (Buffer) size is (Length)×(sizeof(address)＋8) bytes,
			//　else required (Buffer) size is (Length)×8 bytes.
			//＊Mode 0 : Ascending Order
			//　Mode 1 : Descending Order
			//＊(ValueLine) and (IndexLine) should be initialized before processing.
			general(_PL_ R64_)(real_64 _PL_ _R_ ValueLine,address _PL_ _R_ IndexLine,general _PL_ _R_ Buffer,ADDRESS Length,LOGICAL Mode);
		}
		Order;

		//LinClip : Mapping Functions
		const union
		{
			const struct
			{
				//LinClip : 8-Bit Natural Line Mapping
				//＊C[n]＝T[I[n]]
				general(_PL_ D08_)(data_08 _PL_ _R_ C,ADDRESS _PL_ _R_ I,DATA_08 _PL_ T,ADDRESS N);
				//LinClip : 16-Bit Natural Line Mapping
				//＊C[n]＝T[I[n]]
				general(_PL_ D16_)(data_16 _PL_ _R_ C,ADDRESS _PL_ _R_ I,DATA_16 _PL_ T,ADDRESS N);
				//LinClip : 32-Bit Natural Line Mapping
				//＊C[n]＝T[I[n]]
				general(_PL_ D32_)(data_32 _PL_ _R_ C,ADDRESS _PL_ _R_ I,DATA_32 _PL_ T,ADDRESS N);
				//LinClip : 64-Bit Natural Line Mapping
				//＊C[n]＝T[I[n]]
				general(_PL_ D64_)(data_64 _PL_ _R_ C,ADDRESS _PL_ _R_ I,DATA_64 _PL_ T,ADDRESS N);
			};
			const struct
			{
				//LinClip : 8-Bit Integer Line Mapping
				//＊C[n]＝T[I[n]]
				general(_PL_ I08_)(inte_08 _PL_ _R_ C,ADDRESS _PL_ _R_ I,INTE_08 _PL_ T,ADDRESS N);
				//LinClip : 16-Bit Integer Line Mapping
				//＊C[n]＝T[I[n]]
				general(_PL_ I16_)(inte_16 _PL_ _R_ C,ADDRESS _PL_ _R_ I,INTE_16 _PL_ T,ADDRESS N);

				const union
				{
					const struct
					{
						//LinClip : 32-Bit Integer Line Mapping
						//＊C[n]＝T[I[n]]
						general(_PL_ I32_)(inte_32 _PL_ _R_ C,ADDRESS _PL_ _R_ I,INTE_32 _PL_ T,ADDRESS N);
						//LinClip : 64-Bit Integer Line Mapping
						//＊C[n]＝T[I[n]]
						general(_PL_ I64_)(inte_64 _PL_ _R_ C,ADDRESS _PL_ _R_ I,INTE_64 _PL_ T,ADDRESS N);
					};
					const struct
					{
						//LinClip : 32-Bit Real Line Mapping
						//＊C[n]＝T[I[n]]
						general(_PL_ R32_)(real_32 _PL_ _R_ C,ADDRESS _PL_ _R_ I,REAL_32 _PL_ T,ADDRESS N);
						//LinClip : 64-Bit Real Line Mapping
						//＊C[n]＝T[I[n]]
						general(_PL_ R64_)(real_64 _PL_ _R_ C,ADDRESS _PL_ _R_ I,REAL_64 _PL_ T,ADDRESS N);
					};
				};
			};
		}
		Map_1;
	};
}
LINCASE;

//LinClip : Library Case Object
extern LINCASE LinC,*LinC_(general);

#ifdef __OPENCL_H
//LinClip : OpenCL Extension Structure
typedef const struct
{
	//LinClip : Program Build Functions
	//＊The number of binary paths must be same as the number of devices associated with the context.
	//＊(BuildOption) Example : "-I ../../Headers -I ../../Sources -D uBitC_R16_=0 -D uBitC_R64_=1"
	const struct
	{
		//LinClip : Build a program as binary files with narrow string paths.
		//＊(SourcePath) Example : "../../Kernels/linclip.cl"
		//　(BinaryPath) Example : { "../../Device 1/linclip.obj", "../../Device 2/linclip.obj", ... }
		general(_PL_ T08_)(const cl_context Context,TEXT_08 _PL_ _R_ BuildOption,TEXT_08 _PL_ _R_ SourcePath,TEXT_08 _PL_ _PL_ _R_ BinaryPath,FILE _PL_ _R_ LogStream,oclc_ef _PL_ _R_ Error);
		//LinClip : Build a program as binary files with wide string paths.
		//＊(SourcePath) Example : L"../../Kernels/linclip.cl"
		//　(BinaryPath) Example : { L"../../Device 1/linclip.obj", L"../../Device 2/linclip.obj", ... }
		general(_PL_ T16_)(const cl_context Context,TEXT_08 _PL_ _R_ BuildOption,TEXT_16 _PL_ _R_ SourcePath,TEXT_16 _PL_ _PL_ _R_ BinaryPath,FILE _PL_ _R_ LogStream,oclc_ef _PL_ _R_ Error);
	}
	Build;

	//LinClip : Program Creation Functions
	//＊The number of binary paths must be same as the number of devices associated with the context.
	//＊(BuildOption) Example : "-I ../../Headers -I ../../Sources -D uBitC_R16_=0 -D uBitC_R64_=1"
	//＊(BinaryPath) Example : { "../../Device 1/linclip.obj", "../../Device 2/linclip.obj", ... }
	const struct
	{
		//LinClip : Load a program from binary files with narrow string paths.
		//＊(BinaryPath) Example : { "../../Device 1/linclip.obj", "../../Device 2/linclip.obj", ... }
		oclc_pm*(_PL_ T08_)(const cl_context Context,TEXT_08 _PL_ _R_ BuildOption,TEXT_08 _PL_ _PL_ _R_ BinaryPath,FILE _PL_ _R_ LogStream,oclc_ef _PL_ _R_ Error);
		//LinClip : Load a program from binary files with wide string paths.
		//＊(BinaryPath) Example : { L"../../Device 1/linclip.obj", L"../../Device 2/linclip.obj", ... }
		oclc_pm*(_PL_ T16_)(const cl_context Context,TEXT_08 _PL_ _R_ BuildOption,TEXT_16 _PL_ _PL_ _R_ BinaryPath,FILE _PL_ _R_ LogStream,oclc_ef _PL_ _R_ Error);
	}
	Create;

	//LinClip : Preserved for Future Usage
	ADDRESS xPreserved[2];

	const struct
	{
		//LinClip : Increment
		//＊C and A's types should be same and one of BitC.Type.
		//＊Required (Value) size is the type size of those to be calculated.
		general(_PL_ Inc_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Value,oclc_ef _PL_ _R_ Error);

		//LinClip : Amplification
		//＊C and A's types should be same and one of BitC.Type.
		//＊Required (Value) size is the type size of those to be calculated.
		general(_PL_ Amp_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Value,oclc_ef _PL_ _R_ Error);

		//LinClip : Addition
		//＊C, A, and B's types should be same and one of BitC.Type.
		general(_PL_ Add_2_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ _R_ Error);

		//LinClip : Subtraction
		//＊C, A, and B's types should be same and one of BitC.Type.
		general(_PL_ Sub_2_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ _R_ Error);

		//LinClip : Multiplication
		//＊C, A, and B's types should be same and one of BitC.Type.
		general(_PL_ Mul_2_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ _R_ Error);

		//LinClip : Division
		//＊C and A's types should be same and one of BitC.Type.D## or BitC.Type.I##.
		//＊Required (Value) size is the type size of those to be calculated.
		general(_PL_ Div_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Value,oclc_ef _PL_ _R_ Error);

		//LinClip : Inverse
		//＊C and A's types should be same and one of BitC.Type.
		//＊Required (Value) size is the type size of those to be calculated.
		general(_PL_ Inv_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Value,oclc_ef _PL_ _R_ Error);

		//LinClip : Division
		//＊C, A, and B's types should be same and one of BitC.Type.
		general(_PL_ Div_2_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,oclc_ef _PL_ _R_ Error);

		//LinClip : Modulo
		//＊C and A's types should be same and one of BitC.Type.D## or BitC.Type.I##.
		//＊Required (Value) size is the type size of those to be calculated.
		general(_PL_ Mod_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,GENERAL _PL_ Value,oclc_ef _PL_ _R_ Error);

		//LinClip : Summation
		//＊C and A's types should be same and one of BitC.Type.
		general(_PL_ Sum_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,OCLC_PA Axis,oclc_ef _PL_ _R_ Error);

		//LinClip : Dot Product
		//＊C, A, and B's types should be same and one of BitC.Type.
		general(_PL_ Dot_2_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutA,OCLC_MH _PL_ AboutB,OCLC_MP _PL_ AboutN,OCLC_PA Axis,oclc_ef _PL_ _R_ Error);

		//LinClip : Maximum
		//＊I's type size×8 should be same as the device's address bits.
		//＊A's type should be one of BitC.Type.
		general(_PL_ Max_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutI,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,OCLC_PA Axis,oclc_ef _PL_ _R_ Error);

		//LinClip : Minimum
		//＊I's type size×8 should be same as the device's address bits.
		//　A's type should be one of BitC.Type.
		general(_PL_ Min_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutI,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,OCLC_PA Axis,oclc_ef _PL_ _R_ Error);

		//LinClip : Mapping
		//＊I's type size×8 should be same as the device's address bits.
		//　C and A's type sizes should be same.
		general(_PL_ Map_1_)(OCLC_PM _PL_,const cl_command_queue Queue,OCLC_MH _PL_ AboutC,OCLC_MH _PL_ AboutI,OCLC_MH _PL_ AboutA,OCLC_MP _PL_ AboutN,OCLC_PA Axis,oclc_ef _PL_ _R_ Error);
	};
}
LINC_CL;

//LinClip : OpenCL Extension Object
extern LINC_CL LinCL,*LinCL_(general);
#else
//LinClip : Indirect access to the OpenCL extension object.
//＊If the library is not built with OpenCL settings,
//　then the return address will be just NULL.
extern GENERAL *LinCL_(general);
#endif
#endif
#endif
#endif
