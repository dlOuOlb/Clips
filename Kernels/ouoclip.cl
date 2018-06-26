/*------------------------------------------------------------------*/
/*	BitClip's OpenCL Header Parts.									*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2018.06.26	*/
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
#define _Vect_Load_03_(Address) vload3(0,Address)
#define _Vect_Load_04_(Address) vload4(0,Address)
#define _Vect_Load_08_(Address) vload8(0,Address)
#define _Vect_Load_16_(Address) vload16(0,Address)

#define _Vect_Save_02_(Vector,Address) vstore2(Vector,0,Address)
#define _Vect_Save_03_(Vector,Address) vstore3(Vector,0,Address)
#define _Vect_Save_04_(Vector,Address) vstore4(Vector,0,Address)
#define _Vect_Save_08_(Vector,Address) vstore8(Vector,0,Address)
#define _Vect_Save_16_(Vector,Address) vstore16(Vector,0,Address)

#define Type_Rename_(oldtype,newtype,NEWTYPE) typedef oldtype newtype;typedef const oldtype NEWTYPE;
#define Type_Declare_(spec,type,TYPE) typedef spec _##type type;typedef const spec _##type TYPE;
#endif

#if(Fold_(Definition:Scalar and Vector Data Types))
#define _Parse_A_(oldtype,newtype,NEWTYPE) Type_Rename_(oldtype,newtype,NEWTYPE);Type_Rename_(oldtype##2,_02_##newtype,_02_##NEWTYPE);Type_Rename_(oldtype##3,_03_##newtype,_03_##NEWTYPE);Type_Rename_(oldtype##4,_04_##newtype,_04_##NEWTYPE);Type_Rename_(oldtype##8,_08_##newtype,_08_##NEWTYPE);Type_Rename_(oldtype##16,_16_##newtype,_16_##NEWTYPE);

Type_Rename_(void,general,GENERAL)
Type_Rename_(size_t,address,ADDRESS)
Type_Rename_(bool,boolean,BOOLEAN)
Type_Rename_(intptr_t,sintptr,SINTPTR)
Type_Rename_(uintptr_t,uintptr,UINTPTR)

_Parse_A_(uchar,data_08,DATA_08)
_Parse_A_(ushort,data_16,DATA_16)
_Parse_A_(uint,data_32,DATA_32)
#if(_ABLE_I64_)
_Parse_A_(ulong,data_64,DATA_64)
#endif

_Parse_A_(char,inte_08,INTE_08)
_Parse_A_(short,inte_16,INTE_16)
_Parse_A_(int,inte_32,INTE_32)
#if(_ABLE_I64_)
_Parse_A_(long,inte_64,INTE_64)
#endif

#if(_ABLE_R16_)
_Parse_A_(half,real_16,REAL_16)
#endif
_Parse_A_(float,real_32,REAL_32)
#if(_ABLE_R64_)
_Parse_A_(double,real_64,REAL_64)
#endif

#undef _Parse_A_
#endif

#if(Fold_(Definition:Pointer Unions))
#define _Parse_A_(scope,num,type,Name) Vect_(scope,num,type) *_##num##_##Name
#define _Parse_B_(scope,type,Name) _##scope##_ type *Name;_Parse_A_(scope,02,type,Name);_Parse_A_(scope,03,type,Name);_Parse_A_(scope,04,type,Name);_Parse_A_(scope,08,type,Name);_Parse_A_(scope,16,type,Name);

union _point_c
{
	union _c_ptr_v
	{
		_C_ general *G;
		_C_ general **GG;
		_C_ address *AA;

		_Parse_B_(C,data_08,D08)
		_Parse_B_(C,data_16,D16)
		_Parse_B_(C,data_32,D32)
#if(_ABLE_I64_)
		_Parse_B_(C,data_64,D64)
#endif
		_Parse_B_(C,inte_08,I08)
		_Parse_B_(C,inte_16,I16)
		_Parse_B_(C,inte_32,I32)
#if(_ABLE_I64_)
		_Parse_B_(C,inte_64,I64)
#endif
#if(_ABLE_R16_)
		_Parse_B_(C,real_16,R16)
#endif
		_Parse_B_(C,real_32,R32)
#if(_ABLE_R64_)
		_Parse_B_(C,real_64,R64)
#endif
	}
	V;
	union _c_ptr_c
	{
		_C_ GENERAL *G;
		_C_ GENERAL **GG;
		_C_ ADDRESS *AA;

		_Parse_B_(C,DATA_08,D08)
		_Parse_B_(C,DATA_16,D16)
		_Parse_B_(C,DATA_32,D32)
#if(_ABLE_I64_)
		_Parse_B_(C,DATA_64,D64)
#endif
		_Parse_B_(C,INTE_08,I08)
		_Parse_B_(C,INTE_16,I16)
		_Parse_B_(C,INTE_32,I32)
#if(_ABLE_I64_)
		_Parse_B_(C,INTE_64,I64)
#endif
#if(_ABLE_R16_)
		_Parse_B_(C,REAL_16,R16)
#endif
		_Parse_B_(C,REAL_32,R32)
#if(_ABLE_R64_)
		_Parse_B_(C,REAL_64,R64)
#endif
	}
	C;
};
Type_Declare_(union,point_c,POINT_C)

union _point_g
{
	union _g_ptr_v
	{
		_G_ general *G;
		_G_ general **GG;
		_G_ address *AA;

		_Parse_B_(G,data_08,D08)
		_Parse_B_(G,data_16,D16)
		_Parse_B_(G,data_32,D32)
#if(_ABLE_I64_)
		_Parse_B_(G,data_64,D64)
#endif
		_Parse_B_(G,inte_08,I08)
		_Parse_B_(G,inte_16,I16)
		_Parse_B_(G,inte_32,I32)
#if(_ABLE_I64_)
		_Parse_B_(G,inte_64,I64)
#endif
#if(_ABLE_R16_)
		_Parse_B_(G,real_16,R16)
#endif
		_Parse_B_(G,real_32,R32)
#if(_ABLE_R64_)
		_Parse_B_(G,real_64,R64)
#endif
	}
	V;
	union _g_ptr_c
	{
		_G_ GENERAL *G;
		_G_ GENERAL **GG;
		_G_ ADDRESS *AA;

		_Parse_B_(G,DATA_08,D08)
		_Parse_B_(G,DATA_16,D16)
		_Parse_B_(G,DATA_32,D32)
#if(_ABLE_I64_)
		_Parse_B_(G,DATA_64,D64)
#endif
		_Parse_B_(G,INTE_08,I08)
		_Parse_B_(G,INTE_16,I16)
		_Parse_B_(G,INTE_32,I32)
#if(_ABLE_I64_)
		_Parse_B_(G,INTE_64,I64)
#endif
#if(_ABLE_R16_)
		_Parse_B_(G,REAL_16,R16)
#endif
		_Parse_B_(G,REAL_32,R32)
#if(_ABLE_R64_)
		_Parse_B_(G,REAL_64,R64)
#endif
	}
	C;
};
Type_Declare_(union,point_g,POINT_G)

union _point_l
{
	union _l_ptr_v
	{
		_L_ general *G;
		_L_ general **GG;
		_L_ address *AA;

		_Parse_B_(L,data_08,D08)
		_Parse_B_(L,data_16,D16)
		_Parse_B_(L,data_32,D32)
#if(_ABLE_I64_)
		_Parse_B_(L,data_64,D64)
#endif
		_Parse_B_(L,inte_08,I08)
		_Parse_B_(L,inte_16,I16)
		_Parse_B_(L,inte_32,I32)
#if(_ABLE_I64_)
		_Parse_B_(L,inte_64,I64)
#endif
#if(_ABLE_R16_)
		_Parse_B_(L,real_16,R16)
#endif
		_Parse_B_(L,real_32,R32)
#if(_ABLE_R64_)
		_Parse_B_(L,real_64,R64)
#endif
	}
	V;
	union _l_ptr_c
	{
		_L_ GENERAL *G;
		_L_ GENERAL **GG;
		_L_ ADDRESS *AA;

		_Parse_B_(L,DATA_08,D08)
		_Parse_B_(L,DATA_16,D16)
		_Parse_B_(L,DATA_32,D32)
#if(_ABLE_I64_)
		_Parse_B_(L,DATA_64,D64)
#endif
		_Parse_B_(L,INTE_08,I08)
		_Parse_B_(L,INTE_16,I16)
		_Parse_B_(L,INTE_32,I32)
#if(_ABLE_I64_)
		_Parse_B_(L,INTE_64,I64)
#endif
#if(_ABLE_R16_)
		_Parse_B_(L,REAL_16,R16)
#endif
		_Parse_B_(L,REAL_32,R32)
#if(_ABLE_R64_)
		_Parse_B_(L,REAL_64,R64)
#endif
	}
	C;
};
Type_Declare_(union,point_l,POINT_L)

union _point_p
{
	union _p_ptr_v
	{
		_P_ general *G;
		_P_ general **GG;
		_P_ address *AA;

		_Parse_B_(P,data_08,D08)
		_Parse_B_(P,data_16,D16)
		_Parse_B_(P,data_32,D32)
#if(_ABLE_I64_)
		_Parse_B_(P,data_64,D64)
#endif
		_Parse_B_(P,inte_08,I08)
		_Parse_B_(P,inte_16,I16)
		_Parse_B_(P,inte_32,I32)
#if(_ABLE_I64_)
		_Parse_B_(P,inte_64,I64)
#endif
#if(_ABLE_R16_)
		_Parse_B_(P,real_16,R16)
#endif
		_Parse_B_(P,real_32,R32)
#if(_ABLE_R64_)
		_Parse_B_(P,real_64,R64)
#endif
	}
	V;
	union _p_ptr_c
	{
		_P_ GENERAL *G;
		_P_ GENERAL **GG;
		_P_ ADDRESS *AA;

		_Parse_B_(P,DATA_08,D08)
		_Parse_B_(P,DATA_16,D16)
		_Parse_B_(P,DATA_32,D32)
#if(_ABLE_I64_)
		_Parse_B_(P,DATA_64,D64)
#endif
		_Parse_B_(P,INTE_08,I08)
		_Parse_B_(P,INTE_16,I16)
		_Parse_B_(P,INTE_32,I32)
#if(_ABLE_I64_)
		_Parse_B_(P,INTE_64,I64)
#endif
#if(_ABLE_R16_)
		_Parse_B_(P,REAL_16,R16)
#endif
		_Parse_B_(P,REAL_32,R32)
#if(_ABLE_R64_)
		_Parse_B_(P,REAL_64,R64)
#endif
	}
	C;
};
Type_Declare_(union,point_p,POINT_P)

#undef _Parse_B_
#undef _Parse_A_
#endif
#endif
