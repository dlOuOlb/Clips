/*------------------------------------------------------------------*/
/*	BitClip's OpenCL Header and Source Parts.						*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/BitClip/					2018.02.14	*/
/*------------------------------------------------------------------*/
/*	OpenCL Support													*/
/*	http://www.khronos.org/opencl/									*/
/*------------------------------------------------------------------*/

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
#define Acs_(scope,type,Data) (*((scope type*)&(Data)))
#endif

#if(Fold_(Definition:Types))
typedef unsigned char data_08;
typedef unsigned short data_16;
typedef unsigned int data_32;
typedef unsigned long data_64;

typedef const data_08 DATA_08;
typedef const data_16 DATA_16;
typedef const data_32 DATA_32;
typedef const data_64 DATA_64;

typedef signed char inte_08;
typedef signed short inte_16;
typedef signed int inte_32;
typedef signed long inte_64;

typedef const inte_08 INTE_08;
typedef const inte_16 INTE_16;
typedef const inte_32 INTE_32;
typedef const inte_64 INTE_64;

typedef half real_16;
typedef float real_32;
typedef double real_64;

typedef const real_16 REAL_16;
typedef const real_32 REAL_32;
typedef const real_64 REAL_64;

typedef void general;
typedef const general GENERAL;

typedef size_t address;
typedef const address ADDRESS;

typedef bool boolean;
typedef const boolean BOOLEAN;

typedef intptr_t sintptr;
typedef uintptr_t uintptr;

typedef const sintptr SINTPTR;
typedef const uintptr UINTPTR;

union _g_ptr_v
{
	_G_ general *G;
	_G_ general **GG;
	_G_ address *AA;
	_G_ data_08 *D08;
	_G_ data_16 *D16;
	_G_ data_32 *D32;
	_G_ data_64 *D64;
	_G_ inte_08 *I08;
	_G_ inte_16 *I16;
	_G_ inte_32 *I32;
	_G_ inte_64 *I64;
#if(_ABLE_R16_)
	_G_ real_16 *R16;
#endif
	_G_ real_32 *R32;
#if(_ABLE_R64_)
	_G_ real_64 *R64;
#endif
};
typedef union _g_ptr_v g_ptr_v;
typedef const union _g_ptr_v G_PTR_V;

union _g_ptr_c
{
	_G_ GENERAL *G;
	_G_ GENERAL **GG;
	_G_ ADDRESS *AA;
	_G_ DATA_08 *D08;
	_G_ DATA_16 *D16;
	_G_ DATA_32 *D32;
	_G_ DATA_64 *D64;
	_G_ INTE_08 *I08;
	_G_ INTE_16 *I16;
	_G_ INTE_32 *I32;
	_G_ INTE_64 *I64;
#if(_ABLE_R16_)
	_G_ REAL_16 *R16;
#endif
	_G_ REAL_32 *R32;
#if(_ABLE_R64_)
	_G_ REAL_64 *R64;
#endif
};
typedef union _g_ptr_c g_ptr_c;
typedef const union _g_ptr_c G_PTR_C;

union _l_ptr_v
{
	_L_ general *G;
	_L_ general **GG;
	_L_ address *AA;
	_L_ data_08 *D08;
	_L_ data_16 *D16;
	_L_ data_32 *D32;
	_L_ data_64 *D64;
	_L_ inte_08 *I08;
	_L_ inte_16 *I16;
	_L_ inte_32 *I32;
	_L_ inte_64 *I64;
#if(_ABLE_R16_)
	_L_ real_16 *R16;
#endif
	_L_ real_32 *R32;
#if(_ABLE_R64_)
	_L_ real_64 *R64;
#endif
};
typedef union _l_ptr_v l_ptr_v;
typedef const union _l_ptr_v L_PTR_V;

union _l_ptr_c
{
	_L_ GENERAL *G;
	_L_ GENERAL **GG;
	_L_ ADDRESS *AA;
	_L_ DATA_08 *D08;
	_L_ DATA_16 *D16;
	_L_ DATA_32 *D32;
	_L_ DATA_64 *D64;
	_L_ INTE_08 *I08;
	_L_ INTE_16 *I16;
	_L_ INTE_32 *I32;
	_L_ INTE_64 *I64;
#if(_ABLE_R16_)
	_L_ REAL_16 *R16;
#endif
	_L_ REAL_32 *R32;
#if(_ABLE_R64_)
	_L_ REAL_64 *R64;
#endif
};
typedef union _l_ptr_c l_ptr_c;
typedef const union _l_ptr_c L_PTR_C;

union _p_ptr_v
{
	_P_ general *G;
	_P_ general **GG;
	_P_ address *AA;
	_P_ data_08 *D08;
	_P_ data_16 *D16;
	_P_ data_32 *D32;
	_P_ data_64 *D64;
	_P_ inte_08 *I08;
	_P_ inte_16 *I16;
	_P_ inte_32 *I32;
	_P_ inte_64 *I64;
#if(_ABLE_R16_)
	_P_ real_16 *R16;
#endif
	_P_ real_32 *R32;
#if(_ABLE_R64_)
	_P_ real_64 *R64;
#endif
};
typedef union _p_ptr_v p_ptr_v;
typedef const union _p_ptr_v P_PTR_V;

union _p_ptr_c
{
	_P_ GENERAL *G;
	_P_ GENERAL **GG;
	_P_ ADDRESS *AA;
	_P_ DATA_08 *D08;
	_P_ DATA_16 *D16;
	_P_ DATA_32 *D32;
	_P_ DATA_64 *D64;
	_P_ INTE_08 *I08;
	_P_ INTE_16 *I16;
	_P_ INTE_32 *I32;
	_P_ INTE_64 *I64;
#if(_ABLE_R16_)
	_P_ REAL_16 *R16;
#endif
	_P_ REAL_32 *R32;
#if(_ABLE_R64_)
	_P_ REAL_64 *R64;
#endif
};
typedef union _p_ptr_c p_ptr_c;
typedef const union _p_ptr_c P_PTR_C;
#endif
