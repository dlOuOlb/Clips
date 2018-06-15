/*------------------------------------------------------------------*/
/*	BitClip's OpenCL Header Parts.									*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2018.06.15	*/
/*------------------------------------------------------------------*/
/*	OpenCL Support													*/
/*	http://www.khronos.org/opencl/									*/
/*------------------------------------------------------------------*/

#ifndef _INC_OUOCLIP
#define _INC_OUOCLIP

#define Fold_(Comment) (1)

#if(Fold_(OpenCL Extensions))
#define _EMPTY_(X) ((~(~X+0)==0)&&(~(~X+1)==1))

#ifdef _ABLE_I64_
#if(_EMPTY_(_ABLE_I64_))
#undef _ABLE_I64_
#define _ABLE_I64_ (1)
#endif
#else
#define _ABLE_I64_ (0)
#endif

#ifdef _ABLE_R16_
#if(_EMPTY_(_ABLE_R16_))
#undef _ABLE_R16_
#define _ABLE_R16_ (1)
#endif
#else
#define _ABLE_R16_ (0)
#endif

#ifdef _ABLE_R64_
#if(_EMPTY_(_ABLE_R64_))
#undef _ABLE_R64_
#define _ABLE_R64_ (1)
#endif
#else
#define _ABLE_R64_ (0)
#endif

#undef _EMPTY_

#if(_ABLE_I64_)
#pragma OPENCL EXTENSION cl_khr_int64_base_atomics : enable
#pragma OPENCL EXTENSION cl_khr_int64_extended_atomics : enable
#else
#pragma OPENCL EXTENSION cl_khr_int64_base_atomics : disable
#pragma OPENCL EXTENSION cl_khr_int64_extended_atomics : disable
#endif

#if(_ABLE_R16_)
#pragma OPENCL EXTENSION cl_khr_fp16 : enable
#else
#pragma OPENCL EXTENSION cl_khr_fp16 : disable
#endif

#if(_ABLE_R64_)
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#else
#pragma OPENCL EXTENSION cl_khr_fp64 : disable
#endif
#endif

#if(Fold_(Definitions:Macros))
#define _K_ __kernel void
#define _I_ inline static
#define _C_ __constant
#define _G_ __global
#define _L_ __local
#define _P_ __private
#define _R_ restrict

#define Wait_G_ barrier(CLK_GLOBAL_MEM_FENCE)
#define Wait_L_ barrier(CLK_LOCAL_MEM_FENCE)

#define Work_D_ get_work_dim()

#define Work_SGX_ get_global_size(0)
#define Work_SGY_ get_global_size(1)
#define Work_SGZ_ get_global_size(2)

#define Work_SBX_ get_num_groups(0)
#define Work_SBY_ get_num_groups(1)
#define Work_SBZ_ get_num_groups(2)

#define Work_SLX_ get_local_size(0)
#define Work_SLY_ get_local_size(1)
#define Work_SLZ_ get_local_size(2)

#define Work_IGX_ get_global_id(0)
#define Work_IGY_ get_global_id(1)
#define Work_IGZ_ get_global_id(2)

#define Work_IBX_ get_group_id(0)
#define Work_IBY_ get_group_id(1)
#define Work_IBZ_ get_group_id(2)

#define Work_ILX_ get_local_id(0)
#define Work_ILY_ get_local_id(1)
#define Work_ILZ_ get_local_id(2)

#define _PL_ *const
#define Acs_(scope,type,Data) (*((_##scope##_ type*)&(Data)))
#define Vect_(scope,num,type) _##scope##_ _##num##_##type

#define Vect_Load_(num,Address) _Vect_Load_##num##_(Address)
#define Vect_Save_(num,Address,Vector) _Vect_Save_##num##_(Vector,Address)

#define _Vect_Load_02_(Address) vload2(0,Address)
#define _Vect_Load_04_(Address) vload4(0,Address)
#define _Vect_Load_08_(Address) vload8(0,Address)
#define _Vect_Load_16_(Address) vload16(0,Address)

#define _Vect_Save_02_(Vector,Address) vstore2(Vector,0,Address)
#define _Vect_Save_04_(Vector,Address) vstore4(Vector,0,Address)
#define _Vect_Save_08_(Vector,Address) vstore8(Vector,0,Address)
#define _Vect_Save_16_(Vector,Address) vstore16(Vector,0,Address)

#define Type_Declare_(spec,type,TYPE) typedef spec _##type type;typedef const spec _##type TYPE;
#endif

#if(Fold_(Definition:Scalar Types))
typedef unsigned char data_08;
typedef const data_08 DATA_08;

typedef unsigned short data_16;
typedef const data_16 DATA_16;

typedef unsigned int data_32;
typedef const data_32 DATA_32;

#if(_ABLE_I64_)
typedef unsigned long data_64;
typedef const data_64 DATA_64;
#endif

typedef signed char inte_08;
typedef const inte_08 INTE_08;

typedef signed short inte_16;
typedef const inte_16 INTE_16;

typedef signed int inte_32;
typedef const inte_32 INTE_32;

#if(_ABLE_I64_)
typedef signed long inte_64;
typedef const inte_64 INTE_64;
#endif

#if(_ABLE_R16_)
typedef half real_16;
typedef const real_16 REAL_16;
#endif

typedef float real_32;
typedef const real_32 REAL_32;

#if(_ABLE_R64_)
typedef double real_64;
typedef const real_64 REAL_64;
#endif

typedef void general;
typedef const general GENERAL;

typedef size_t address;
typedef const address ADDRESS;

typedef bool boolean;
typedef const boolean BOOLEAN;

typedef intptr_t sintptr;
typedef const sintptr SINTPTR;

typedef uintptr_t uintptr;
typedef const uintptr UINTPTR;
#endif

#if(Fold_(Definition:Vector Types))
typedef uchar2 _02_data_08;
typedef uchar4 _04_data_08;
typedef uchar8 _08_data_08;
typedef uchar16 _16_data_08;

typedef const _02_data_08 _02_DATA_08;
typedef const _04_data_08 _04_DATA_08;
typedef const _08_data_08 _08_DATA_08;
typedef const _16_data_08 _16_DATA_08;

typedef ushort2 _02_data_16;
typedef ushort4 _04_data_16;
typedef ushort8 _08_data_16;
typedef ushort16 _16_data_16;

typedef const _02_data_16 _02_DATA_16;
typedef const _04_data_16 _04_DATA_16;
typedef const _08_data_16 _08_DATA_16;
typedef const _16_data_16 _16_DATA_16;

typedef uint2 _02_data_32;
typedef uint4 _04_data_32;
typedef uint8 _08_data_32;
typedef uint16 _16_data_32;

typedef const _02_data_32 _02_DATA_32;
typedef const _04_data_32 _04_DATA_32;
typedef const _08_data_32 _08_DATA_32;
typedef const _16_data_32 _16_DATA_32;

#if(_ABLE_I64_)
typedef ulong2 _02_data_64;
typedef ulong4 _04_data_64;
typedef ulong8 _08_data_64;
typedef ulong16 _16_data_64;

typedef const _02_data_64 _02_DATA_64;
typedef const _04_data_64 _04_DATA_64;
typedef const _08_data_64 _08_DATA_64;
typedef const _16_data_64 _16_DATA_64;
#endif

typedef char2 _02_inte_08;
typedef char4 _04_inte_08;
typedef char8 _08_inte_08;
typedef char16 _16_inte_08;

typedef const _02_inte_08 _02_INTE_08;
typedef const _04_inte_08 _04_INTE_08;
typedef const _08_inte_08 _08_INTE_08;
typedef const _16_inte_08 _16_INTE_08;

typedef short2 _02_inte_16;
typedef short4 _04_inte_16;
typedef short8 _08_inte_16;
typedef short16 _16_inte_16;

typedef const _02_inte_16 _02_INTE_16;
typedef const _04_inte_16 _04_INTE_16;
typedef const _08_inte_16 _08_INTE_16;
typedef const _16_inte_16 _16_INTE_16;

typedef int2 _02_inte_32;
typedef int4 _04_inte_32;
typedef int8 _08_inte_32;
typedef int16 _16_inte_32;

typedef const _02_inte_32 _02_INTE_32;
typedef const _04_inte_32 _04_INTE_32;
typedef const _08_inte_32 _08_INTE_32;
typedef const _16_inte_32 _16_INTE_32;

#if(_ABLE_I64_)
typedef long2 _02_inte_64;
typedef long4 _04_inte_64;
typedef long8 _08_inte_64;
typedef long16 _16_inte_64;

typedef const _02_inte_64 _02_INTE_64;
typedef const _04_inte_64 _04_INTE_64;
typedef const _08_inte_64 _08_INTE_64;
typedef const _16_inte_64 _16_INTE_64;
#endif

#if(_ABLE_R16_)
typedef half2 _02_real_16;
typedef half4 _04_real_16;
typedef half8 _08_real_16;
typedef half16 _16_real_16;

typedef const _02_real_16 _02_REAL_16;
typedef const _04_real_16 _04_REAL_16;
typedef const _08_real_16 _08_REAL_16;
typedef const _16_real_16 _16_REAL_16;
#endif

typedef float2 _02_real_32;
typedef float4 _04_real_32;
typedef float8 _08_real_32;
typedef float16 _16_real_32;

typedef const _02_real_32 _02_REAL_32;
typedef const _04_real_32 _04_REAL_32;
typedef const _08_real_32 _08_REAL_32;
typedef const _16_real_32 _16_REAL_32;

#if(_ABLE_R64_)
typedef double2 _02_real_64;
typedef double4 _04_real_64;
typedef double8 _08_real_64;
typedef double16 _16_real_64;

typedef const _02_real_64 _02_REAL_64;
typedef const _04_real_64 _04_REAL_64;
typedef const _08_real_64 _08_REAL_64;
typedef const _16_real_64 _16_REAL_64;
#endif
#endif

#if(Fold_(Definition:Pointer Unions))
union _point_c
{
	union _c_ptr_v
	{
		_C_ general *G;
		_C_ general **GG;
		_C_ address *AA;
		_C_ data_08 *D08;
		_C_ data_16 *D16;
		_C_ data_32 *D32;
#if(_ABLE_I64_)
		_C_ data_64 *D64;
#endif
		_C_ inte_08 *I08;
		_C_ inte_16 *I16;
		_C_ inte_32 *I32;
#if(_ABLE_I64_)
		_C_ inte_64 *I64;
#endif
#if(_ABLE_R16_)
		_C_ real_16 *R16;
#endif
		_C_ real_32 *R32;
#if(_ABLE_R64_)
		_C_ real_64 *R64;
#endif
		_C_ _02_data_08 *_02_D08;
		_C_ _04_data_08 *_04_D08;
		_C_ _08_data_08 *_08_D08;
		_C_ _16_data_08 *_16_D08;
		_C_ _02_data_16 *_02_D16;
		_C_ _04_data_16 *_04_D16;
		_C_ _08_data_16 *_08_D16;
		_C_ _16_data_16 *_16_D16;
		_C_ _02_data_32 *_02_D32;
		_C_ _04_data_32 *_04_D32;
		_C_ _08_data_32 *_08_D32;
		_C_ _16_data_32 *_16_D32;
#if(_ABLE_I64_)
		_C_ _02_data_64 *_02_D64;
		_C_ _04_data_64 *_04_D64;
		_C_ _08_data_64 *_08_D64;
		_C_ _16_data_64 *_16_D64;
#endif
		_C_ _02_inte_08 *_02_I08;
		_C_ _04_inte_08 *_04_I08;
		_C_ _08_inte_08 *_08_I08;
		_C_ _16_inte_08 *_16_I08;
		_C_ _02_inte_16 *_02_I16;
		_C_ _04_inte_16 *_04_I16;
		_C_ _08_inte_16 *_08_I16;
		_C_ _16_inte_16 *_16_I16;
		_C_ _02_inte_32 *_02_I32;
		_C_ _04_inte_32 *_04_I32;
		_C_ _08_inte_32 *_08_I32;
		_C_ _16_inte_32 *_16_I32;
#if(_ABLE_I64_)
		_C_ _02_inte_64 *_02_I64;
		_C_ _04_inte_64 *_04_I64;
		_C_ _08_inte_64 *_08_I64;
		_C_ _16_inte_64 *_16_I64;
#endif
#if(_ABLE_R16_)
		_C_ _02_real_16 *_02_R16;
		_C_ _04_real_16 *_04_R16;
		_C_ _08_real_16 *_08_R16;
		_C_ _16_real_16 *_16_R16;
#endif
		_C_ _02_real_32 *_02_R32;
		_C_ _04_real_32 *_04_R32;
		_C_ _08_real_32 *_08_R32;
		_C_ _16_real_32 *_16_R32;
#if(_ABLE_R64_)
		_C_ _02_real_64 *_02_R64;
		_C_ _04_real_64 *_04_R64;
		_C_ _08_real_64 *_08_R64;
		_C_ _16_real_64 *_16_R64;
#endif
	}
	V;
	union _c_ptr_c
	{
		_C_ GENERAL *G;
		_C_ GENERAL **GG;
		_C_ ADDRESS *AA;
		_C_ DATA_08 *D08;
		_C_ DATA_16 *D16;
		_C_ DATA_32 *D32;
#if(_ABLE_I64_)
		_C_ DATA_64 *D64;
#endif
		_C_ INTE_08 *I08;
		_C_ INTE_16 *I16;
		_C_ INTE_32 *I32;
#if(_ABLE_I64_)
		_C_ INTE_64 *I64;
#endif
#if(_ABLE_R16_)
		_C_ REAL_16 *R16;
#endif
		_C_ REAL_32 *R32;
#if(_ABLE_R64_)
		_C_ REAL_64 *R64;
#endif
		_C_ _02_DATA_08 *_02_D08;
		_C_ _04_DATA_08 *_04_D08;
		_C_ _08_DATA_08 *_08_D08;
		_C_ _16_DATA_08 *_16_D08;
		_C_ _02_DATA_16 *_02_D16;
		_C_ _04_DATA_16 *_04_D16;
		_C_ _08_DATA_16 *_08_D16;
		_C_ _16_DATA_16 *_16_D16;
		_C_ _02_DATA_32 *_02_D32;
		_C_ _04_DATA_32 *_04_D32;
		_C_ _08_DATA_32 *_08_D32;
		_C_ _16_DATA_32 *_16_D32;
#if(_ABLE_I64_)
		_C_ _02_DATA_64 *_02_D64;
		_C_ _04_DATA_64 *_04_D64;
		_C_ _08_DATA_64 *_08_D64;
		_C_ _16_DATA_64 *_16_D64;
#endif
		_C_ _02_INTE_08 *_02_I08;
		_C_ _04_INTE_08 *_04_I08;
		_C_ _08_INTE_08 *_08_I08;
		_C_ _16_INTE_08 *_16_I08;
		_C_ _02_INTE_16 *_02_I16;
		_C_ _04_INTE_16 *_04_I16;
		_C_ _08_INTE_16 *_08_I16;
		_C_ _16_INTE_16 *_16_I16;
		_C_ _02_INTE_32 *_02_I32;
		_C_ _04_INTE_32 *_04_I32;
		_C_ _08_INTE_32 *_08_I32;
		_C_ _16_INTE_32 *_16_I32;
#if(_ABLE_I64_)
		_C_ _02_INTE_64 *_02_I64;
		_C_ _04_INTE_64 *_04_I64;
		_C_ _08_INTE_64 *_08_I64;
		_C_ _16_INTE_64 *_16_I64;
#endif
#if(_ABLE_R16_)
		_C_ _02_REAL_16 *_02_R16;
		_C_ _04_REAL_16 *_04_R16;
		_C_ _08_REAL_16 *_08_R16;
		_C_ _16_REAL_16 *_16_R16;
#endif
		_C_ _02_REAL_32 *_02_R32;
		_C_ _04_REAL_32 *_04_R32;
		_C_ _08_REAL_32 *_08_R32;
		_C_ _16_REAL_32 *_16_R32;
#if(_ABLE_R64_)
		_C_ _02_REAL_64 *_02_R64;
		_C_ _04_REAL_64 *_04_R64;
		_C_ _08_REAL_64 *_08_R64;
		_C_ _16_REAL_64 *_16_R64;
#endif
	}
	C;
};
Type_Declare_(union,point_c,POINT_C);

union _point_g
{
	union _g_ptr_v
	{
		_G_ general *G;
		_G_ general **GG;
		_G_ address *AA;
		_G_ data_08 *D08;
		_G_ data_16 *D16;
		_G_ data_32 *D32;
#if(_ABLE_I64_)
		_G_ data_64 *D64;
#endif
		_G_ inte_08 *I08;
		_G_ inte_16 *I16;
		_G_ inte_32 *I32;
#if(_ABLE_I64_)
		_G_ inte_64 *I64;
#endif
#if(_ABLE_R16_)
		_G_ real_16 *R16;
#endif
		_G_ real_32 *R32;
#if(_ABLE_R64_)
		_G_ real_64 *R64;
#endif
		_G_ _02_data_08 *_02_D08;
		_G_ _04_data_08 *_04_D08;
		_G_ _08_data_08 *_08_D08;
		_G_ _16_data_08 *_16_D08;
		_G_ _02_data_16 *_02_D16;
		_G_ _04_data_16 *_04_D16;
		_G_ _08_data_16 *_08_D16;
		_G_ _16_data_16 *_16_D16;
		_G_ _02_data_32 *_02_D32;
		_G_ _04_data_32 *_04_D32;
		_G_ _08_data_32 *_08_D32;
		_G_ _16_data_32 *_16_D32;
#if(_ABLE_I64_)
		_G_ _02_data_64 *_02_D64;
		_G_ _04_data_64 *_04_D64;
		_G_ _08_data_64 *_08_D64;
		_G_ _16_data_64 *_16_D64;
#endif
		_G_ _02_inte_08 *_02_I08;
		_G_ _04_inte_08 *_04_I08;
		_G_ _08_inte_08 *_08_I08;
		_G_ _16_inte_08 *_16_I08;
		_G_ _02_inte_16 *_02_I16;
		_G_ _04_inte_16 *_04_I16;
		_G_ _08_inte_16 *_08_I16;
		_G_ _16_inte_16 *_16_I16;
		_G_ _02_inte_32 *_02_I32;
		_G_ _04_inte_32 *_04_I32;
		_G_ _08_inte_32 *_08_I32;
		_G_ _16_inte_32 *_16_I32;
#if(_ABLE_I64_)
		_G_ _02_inte_64 *_02_I64;
		_G_ _04_inte_64 *_04_I64;
		_G_ _08_inte_64 *_08_I64;
		_G_ _16_inte_64 *_16_I64;
#endif
#if(_ABLE_R16_)
		_G_ _02_real_16 *_02_R16;
		_G_ _04_real_16 *_04_R16;
		_G_ _08_real_16 *_08_R16;
		_G_ _16_real_16 *_16_R16;
#endif
		_G_ _02_real_32 *_02_R32;
		_G_ _04_real_32 *_04_R32;
		_G_ _08_real_32 *_08_R32;
		_G_ _16_real_32 *_16_R32;
#if(_ABLE_R64_)
		_G_ _02_real_64 *_02_R64;
		_G_ _04_real_64 *_04_R64;
		_G_ _08_real_64 *_08_R64;
		_G_ _16_real_64 *_16_R64;
#endif
	}
	V;
	union _g_ptr_c
	{
		_G_ GENERAL *G;
		_G_ GENERAL **GG;
		_G_ ADDRESS *AA;
		_G_ DATA_08 *D08;
		_G_ DATA_16 *D16;
		_G_ DATA_32 *D32;
#if(_ABLE_I64_)
		_G_ DATA_64 *D64;
#endif
		_G_ INTE_08 *I08;
		_G_ INTE_16 *I16;
		_G_ INTE_32 *I32;
#if(_ABLE_I64_)
		_G_ INTE_64 *I64;
#endif
#if(_ABLE_R16_)
		_G_ REAL_16 *R16;
#endif
		_G_ REAL_32 *R32;
#if(_ABLE_R64_)
		_G_ REAL_64 *R64;
#endif
		_G_ _02_DATA_08 *_02_D08;
		_G_ _04_DATA_08 *_04_D08;
		_G_ _08_DATA_08 *_08_D08;
		_G_ _16_DATA_08 *_16_D08;
		_G_ _02_DATA_16 *_02_D16;
		_G_ _04_DATA_16 *_04_D16;
		_G_ _08_DATA_16 *_08_D16;
		_G_ _16_DATA_16 *_16_D16;
		_G_ _02_DATA_32 *_02_D32;
		_G_ _04_DATA_32 *_04_D32;
		_G_ _08_DATA_32 *_08_D32;
		_G_ _16_DATA_32 *_16_D32;
#if(_ABLE_I64_)
		_G_ _02_DATA_64 *_02_D64;
		_G_ _04_DATA_64 *_04_D64;
		_G_ _08_DATA_64 *_08_D64;
		_G_ _16_DATA_64 *_16_D64;
#endif
		_G_ _02_INTE_08 *_02_I08;
		_G_ _04_INTE_08 *_04_I08;
		_G_ _08_INTE_08 *_08_I08;
		_G_ _16_INTE_08 *_16_I08;
		_G_ _02_INTE_16 *_02_I16;
		_G_ _04_INTE_16 *_04_I16;
		_G_ _08_INTE_16 *_08_I16;
		_G_ _16_INTE_16 *_16_I16;
		_G_ _02_INTE_32 *_02_I32;
		_G_ _04_INTE_32 *_04_I32;
		_G_ _08_INTE_32 *_08_I32;
		_G_ _16_INTE_32 *_16_I32;
#if(_ABLE_I64_)
		_G_ _02_INTE_64 *_02_I64;
		_G_ _04_INTE_64 *_04_I64;
		_G_ _08_INTE_64 *_08_I64;
		_G_ _16_INTE_64 *_16_I64;
#endif
#if(_ABLE_R16_)
		_G_ _02_REAL_16 *_02_R16;
		_G_ _04_REAL_16 *_04_R16;
		_G_ _08_REAL_16 *_08_R16;
		_G_ _16_REAL_16 *_16_R16;
#endif
		_G_ _02_REAL_32 *_02_R32;
		_G_ _04_REAL_32 *_04_R32;
		_G_ _08_REAL_32 *_08_R32;
		_G_ _16_REAL_32 *_16_R32;
#if(_ABLE_R64_)
		_G_ _02_REAL_64 *_02_R64;
		_G_ _04_REAL_64 *_04_R64;
		_G_ _08_REAL_64 *_08_R64;
		_G_ _16_REAL_64 *_16_R64;
#endif
	}
	C;
};
Type_Declare_(union,point_g,POINT_G);

union _point_l
{
	union _l_ptr_v
	{
		_L_ general *G;
		_L_ general **GG;
		_L_ address *AA;
		_L_ data_08 *D08;
		_L_ data_16 *D16;
		_L_ data_32 *D32;
#if(_ABLE_I64_)
		_L_ data_64 *D64;
#endif
		_L_ inte_08 *I08;
		_L_ inte_16 *I16;
		_L_ inte_32 *I32;
#if(_ABLE_I64_)
		_L_ inte_64 *I64;
#endif
#if(_ABLE_R16_)
		_L_ real_16 *R16;
#endif
		_L_ real_32 *R32;
#if(_ABLE_R64_)
		_L_ real_64 *R64;
#endif
		_L_ _02_data_08 *_02_D08;
		_L_ _04_data_08 *_04_D08;
		_L_ _08_data_08 *_08_D08;
		_L_ _16_data_08 *_16_D08;
		_L_ _02_data_16 *_02_D16;
		_L_ _04_data_16 *_04_D16;
		_L_ _08_data_16 *_08_D16;
		_L_ _16_data_16 *_16_D16;
		_L_ _02_data_32 *_02_D32;
		_L_ _04_data_32 *_04_D32;
		_L_ _08_data_32 *_08_D32;
		_L_ _16_data_32 *_16_D32;
#if(_ABLE_I64_)
		_L_ _02_data_64 *_02_D64;
		_L_ _04_data_64 *_04_D64;
		_L_ _08_data_64 *_08_D64;
		_L_ _16_data_64 *_16_D64;
#endif
		_L_ _02_inte_08 *_02_I08;
		_L_ _04_inte_08 *_04_I08;
		_L_ _08_inte_08 *_08_I08;
		_L_ _16_inte_08 *_16_I08;
		_L_ _02_inte_16 *_02_I16;
		_L_ _04_inte_16 *_04_I16;
		_L_ _08_inte_16 *_08_I16;
		_L_ _16_inte_16 *_16_I16;
		_L_ _02_inte_32 *_02_I32;
		_L_ _04_inte_32 *_04_I32;
		_L_ _08_inte_32 *_08_I32;
		_L_ _16_inte_32 *_16_I32;
#if(_ABLE_I64_)
		_L_ _02_inte_64 *_02_I64;
		_L_ _04_inte_64 *_04_I64;
		_L_ _08_inte_64 *_08_I64;
		_L_ _16_inte_64 *_16_I64;
#endif
#if(_ABLE_R16_)
		_L_ _02_real_16 *_02_R16;
		_L_ _04_real_16 *_04_R16;
		_L_ _08_real_16 *_08_R16;
		_L_ _16_real_16 *_16_R16;
#endif
		_L_ _02_real_32 *_02_R32;
		_L_ _04_real_32 *_04_R32;
		_L_ _08_real_32 *_08_R32;
		_L_ _16_real_32 *_16_R32;
#if(_ABLE_R64_)
		_L_ _02_real_64 *_02_R64;
		_L_ _04_real_64 *_04_R64;
		_L_ _08_real_64 *_08_R64;
		_L_ _16_real_64 *_16_R64;
#endif
	}
	V;
	union _l_ptr_c
	{
		_L_ GENERAL *G;
		_L_ GENERAL **GG;
		_L_ ADDRESS *AA;
		_L_ DATA_08 *D08;
		_L_ DATA_16 *D16;
		_L_ DATA_32 *D32;
#if(_ABLE_I64_)
		_L_ DATA_64 *D64;
#endif
		_L_ INTE_08 *I08;
		_L_ INTE_16 *I16;
		_L_ INTE_32 *I32;
#if(_ABLE_I64_)
		_L_ INTE_64 *I64;
#endif
#if(_ABLE_R16_)
		_L_ REAL_16 *R16;
#endif
		_L_ REAL_32 *R32;
#if(_ABLE_R64_)
		_L_ REAL_64 *R64;
#endif
		_L_ _02_DATA_08 *_02_D08;
		_L_ _04_DATA_08 *_04_D08;
		_L_ _08_DATA_08 *_08_D08;
		_L_ _16_DATA_08 *_16_D08;
		_L_ _02_DATA_16 *_02_D16;
		_L_ _04_DATA_16 *_04_D16;
		_L_ _08_DATA_16 *_08_D16;
		_L_ _16_DATA_16 *_16_D16;
		_L_ _02_DATA_32 *_02_D32;
		_L_ _04_DATA_32 *_04_D32;
		_L_ _08_DATA_32 *_08_D32;
		_L_ _16_DATA_32 *_16_D32;
#if(_ABLE_I64_)
		_L_ _02_DATA_64 *_02_D64;
		_L_ _04_DATA_64 *_04_D64;
		_L_ _08_DATA_64 *_08_D64;
		_L_ _16_DATA_64 *_16_D64;
#endif
		_L_ _02_INTE_08 *_02_I08;
		_L_ _04_INTE_08 *_04_I08;
		_L_ _08_INTE_08 *_08_I08;
		_L_ _16_INTE_08 *_16_I08;
		_L_ _02_INTE_16 *_02_I16;
		_L_ _04_INTE_16 *_04_I16;
		_L_ _08_INTE_16 *_08_I16;
		_L_ _16_INTE_16 *_16_I16;
		_L_ _02_INTE_32 *_02_I32;
		_L_ _04_INTE_32 *_04_I32;
		_L_ _08_INTE_32 *_08_I32;
		_L_ _16_INTE_32 *_16_I32;
#if(_ABLE_I64_)
		_L_ _02_INTE_64 *_02_I64;
		_L_ _04_INTE_64 *_04_I64;
		_L_ _08_INTE_64 *_08_I64;
		_L_ _16_INTE_64 *_16_I64;
#endif
#if(_ABLE_R16_)
		_L_ _02_REAL_16 *_02_R16;
		_L_ _04_REAL_16 *_04_R16;
		_L_ _08_REAL_16 *_08_R16;
		_L_ _16_REAL_16 *_16_R16;
#endif
		_L_ _02_REAL_32 *_02_R32;
		_L_ _04_REAL_32 *_04_R32;
		_L_ _08_REAL_32 *_08_R32;
		_L_ _16_REAL_32 *_16_R32;
#if(_ABLE_R64_)
		_L_ _02_REAL_64 *_02_R64;
		_L_ _04_REAL_64 *_04_R64;
		_L_ _08_REAL_64 *_08_R64;
		_L_ _16_REAL_64 *_16_R64;
#endif
	}
	C;
};
Type_Declare_(union,point_l,POINT_L);

union _point_p
{
	union _p_ptr_v
	{
		_P_ general *G;
		_P_ general **GG;
		_P_ address *AA;
		_P_ data_08 *D08;
		_P_ data_16 *D16;
		_P_ data_32 *D32;
#if(_ABLE_I64_)
		_P_ data_64 *D64;
#endif
		_P_ inte_08 *I08;
		_P_ inte_16 *I16;
		_P_ inte_32 *I32;
#if(_ABLE_I64_)
		_P_ inte_64 *I64;
#endif
#if(_ABLE_R16_)
		_P_ real_16 *R16;
#endif
		_P_ real_32 *R32;
#if(_ABLE_R64_)
		_P_ real_64 *R64;
#endif
		_P_ _02_data_08 *_02_D08;
		_P_ _04_data_08 *_04_D08;
		_P_ _08_data_08 *_08_D08;
		_P_ _16_data_08 *_16_D08;
		_P_ _02_data_16 *_02_D16;
		_P_ _04_data_16 *_04_D16;
		_P_ _08_data_16 *_08_D16;
		_P_ _16_data_16 *_16_D16;
		_P_ _02_data_32 *_02_D32;
		_P_ _04_data_32 *_04_D32;
		_P_ _08_data_32 *_08_D32;
		_P_ _16_data_32 *_16_D32;
#if(_ABLE_I64_)
		_P_ _02_data_64 *_02_D64;
		_P_ _04_data_64 *_04_D64;
		_P_ _08_data_64 *_08_D64;
		_P_ _16_data_64 *_16_D64;
#endif
		_P_ _02_inte_08 *_02_I08;
		_P_ _04_inte_08 *_04_I08;
		_P_ _08_inte_08 *_08_I08;
		_P_ _16_inte_08 *_16_I08;
		_P_ _02_inte_16 *_02_I16;
		_P_ _04_inte_16 *_04_I16;
		_P_ _08_inte_16 *_08_I16;
		_P_ _16_inte_16 *_16_I16;
		_P_ _02_inte_32 *_02_I32;
		_P_ _04_inte_32 *_04_I32;
		_P_ _08_inte_32 *_08_I32;
		_P_ _16_inte_32 *_16_I32;
#if(_ABLE_I64_)
		_P_ _02_inte_64 *_02_I64;
		_P_ _04_inte_64 *_04_I64;
		_P_ _08_inte_64 *_08_I64;
		_P_ _16_inte_64 *_16_I64;
#endif
#if(_ABLE_R16_)
		_P_ _02_real_16 *_02_R16;
		_P_ _04_real_16 *_04_R16;
		_P_ _08_real_16 *_08_R16;
		_P_ _16_real_16 *_16_R16;
#endif
		_P_ _02_real_32 *_02_R32;
		_P_ _04_real_32 *_04_R32;
		_P_ _08_real_32 *_08_R32;
		_P_ _16_real_32 *_16_R32;
#if(_ABLE_R64_)
		_P_ _02_real_64 *_02_R64;
		_P_ _04_real_64 *_04_R64;
		_P_ _08_real_64 *_08_R64;
		_P_ _16_real_64 *_16_R64;
#endif
	}
	V;
	union _p_ptr_c
	{
		_P_ GENERAL *G;
		_P_ GENERAL **GG;
		_P_ ADDRESS *AA;
		_P_ DATA_08 *D08;
		_P_ DATA_16 *D16;
		_P_ DATA_32 *D32;
#if(_ABLE_I64_)
		_P_ DATA_64 *D64;
#endif
		_P_ INTE_08 *I08;
		_P_ INTE_16 *I16;
		_P_ INTE_32 *I32;
#if(_ABLE_I64_)
		_P_ INTE_64 *I64;
#endif
#if(_ABLE_R16_)
		_P_ REAL_16 *R16;
#endif
		_P_ REAL_32 *R32;
#if(_ABLE_R64_)
		_P_ REAL_64 *R64;
#endif
		_P_ _02_DATA_08 *_02_D08;
		_P_ _04_DATA_08 *_04_D08;
		_P_ _08_DATA_08 *_08_D08;
		_P_ _16_DATA_08 *_16_D08;
		_P_ _02_DATA_16 *_02_D16;
		_P_ _04_DATA_16 *_04_D16;
		_P_ _08_DATA_16 *_08_D16;
		_P_ _16_DATA_16 *_16_D16;
		_P_ _02_DATA_32 *_02_D32;
		_P_ _04_DATA_32 *_04_D32;
		_P_ _08_DATA_32 *_08_D32;
		_P_ _16_DATA_32 *_16_D32;
#if(_ABLE_I64_)
		_P_ _02_DATA_64 *_02_D64;
		_P_ _04_DATA_64 *_04_D64;
		_P_ _08_DATA_64 *_08_D64;
		_P_ _16_DATA_64 *_16_D64;
#endif
		_P_ _02_INTE_08 *_02_I08;
		_P_ _04_INTE_08 *_04_I08;
		_P_ _08_INTE_08 *_08_I08;
		_P_ _16_INTE_08 *_16_I08;
		_P_ _02_INTE_16 *_02_I16;
		_P_ _04_INTE_16 *_04_I16;
		_P_ _08_INTE_16 *_08_I16;
		_P_ _16_INTE_16 *_16_I16;
		_P_ _02_INTE_32 *_02_I32;
		_P_ _04_INTE_32 *_04_I32;
		_P_ _08_INTE_32 *_08_I32;
		_P_ _16_INTE_32 *_16_I32;
#if(_ABLE_I64_)
		_P_ _02_INTE_64 *_02_I64;
		_P_ _04_INTE_64 *_04_I64;
		_P_ _08_INTE_64 *_08_I64;
		_P_ _16_INTE_64 *_16_I64;
#endif
#if(_ABLE_R16_)
		_P_ _02_REAL_16 *_02_R16;
		_P_ _04_REAL_16 *_04_R16;
		_P_ _08_REAL_16 *_08_R16;
		_P_ _16_REAL_16 *_16_R16;
#endif
		_P_ _02_REAL_32 *_02_R32;
		_P_ _04_REAL_32 *_04_R32;
		_P_ _08_REAL_32 *_08_R32;
		_P_ _16_REAL_32 *_16_R32;
#if(_ABLE_R64_)
		_P_ _02_REAL_64 *_02_R64;
		_P_ _04_REAL_64 *_04_R64;
		_P_ _08_REAL_64 *_08_R64;
		_P_ _16_REAL_64 *_16_R64;
#endif
	}
	C;
};
Type_Declare_(union,point_p,POINT_P);
#endif
#endif
