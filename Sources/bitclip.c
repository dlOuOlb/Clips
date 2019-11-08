﻿#include "bitclip.h"

#include <limits.h>

#if(Fold_(Static Assertions))
static_assert(((inte_08)(-1))==(((inte_08)(-1))>>1),"The bit-shift-right operation of a signed integer must preserve the sign.");
static_assert(((data_08)(-1))!=(((data_08)(-1))>>1),"The bit-shift-right operation of an unsigned integer must not preserve the sign.");
static_assert((~((address)(0)))==((address)((inte_08)(~0))),"Casting from a signed integer to an address value must preserve the sign.");
static_assert(sizeof(sintptr)==sizeof(address),"The signed address type size must be equal to the address type size.");
static_assert(sizeof(uintptr)==sizeof(address),"The unsigned address type size must be equal to the address type size.");
static_assert(((sintptr)(-1))==(((sintptr)(-1))>>1),"The bit-shift-right operation of a signed address must preserve the sign.");
static_assert(((uintptr)(-1))!=(((uintptr)(-1))>>1),"The bit-shift-right operation of an unsigned address must not preserve the sign.");
#endif

#if(Fold_(Definition:Internal Macros))
#define _BITC_ static
#define _BitC_Dims_ ((address)(8))
#include "bitcros.c"
#endif

#if(Fold_(Definition:Internal Constants))
static GENERAL _PL_ BitClip=&BitClip;
_BITC_ BYTE_08 IdiomVersion[16]="Date:2019.11.08";

_BITC_ ADDRESS ConstantMask[16]={~(address)0,~(address)1,~(address)3,~(address)7,~(address)15,~(address)31,~(address)63,~(address)127,(address)0,(address)1,(address)3,(address)7,(address)15,(address)31,(address)63,(address)127};
_BITC_ INTE_64 Constant64[8]={0x400921FB54442D18,0x3FD45F306DC9C883,0x4005BF0A8B145769,0x3FD78B56362CEF38,0x7FF0000000000000,0xFFF0000000000000,0x7FFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF};
_BITC_ INTE_32 Constant32[8]={0x40490FDB,0x3EA2F983,0x402DF854,0x3EBC5AB2,0x7F800000,0xFF800000,0x7FFFFFFF,0xFFFFFFFF};

static DATA_64 TableShrink64[8]={0x0000000000000001,0x0000000000000002,0x0000000000000004,0x0000000000000008,0x0000000000000010,0x0000000000000020,0x0000000000000040,0x0000000000000080};
static DATA_32 TableShrink32[8]={0x00000001,0x00000002,0x00000004,0x00000008,0x00000010,0x00000020,0x00000040,0x00000080};
static DATA_16 TableShrink16[8]={0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080};
static DATA_08 TableShrink08[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

static INTEGER TableReform[8]={3,0,1,0,2,0,1,0};
#endif

#if(Fold_(Definition:Type Descriptors))
#define _BitC_DT_Define_(IType,type,IFlag) [IType]=MemC_DT_Define_(&BitClip,IType,IdiomTypeName[IType],IFlag,NULL,NULL,type)

static BYTE_08 IdiomTypeName[BitCTypes][8]=
{
	[BitCTypeData_08]="data_08",
	[BitCTypeData_16]="data_16",
	[BitCTypeData_32]="data_32",
	[BitCTypeData_64]="data_64",
	[BitCTypeInte_08]="inte_08",
	[BitCTypeInte_16]="inte_16",
	[BitCTypeInte_32]="inte_32",
	[BitCTypeInte_64]="inte_64",
	[BitCTypeReal_08]="real_08",
	[BitCTypeReal_16]="real_16",
	[BitCTypeReal_32]="real_32",
	[BitCTypeReal_64]="real_64"
};
static MEMC_DT TableType[BitCTypes]=
{
	_BitC_DT_Define_(BitCTypeData_08,data_08,0x0),
	_BitC_DT_Define_(BitCTypeData_16,data_16,0x1),
	_BitC_DT_Define_(BitCTypeData_32,data_32,0x2),
	_BitC_DT_Define_(BitCTypeData_64,data_64,0x3),
	_BitC_DT_Define_(BitCTypeInte_08,inte_08,0x4),
	_BitC_DT_Define_(BitCTypeInte_16,inte_16,0x5),
	_BitC_DT_Define_(BitCTypeInte_32,inte_32,0x6),
	_BitC_DT_Define_(BitCTypeInte_64,inte_64,0x7),
	_BitC_DT_Define_(BitCTypeReal_08,data_08,0xC),
	_BitC_DT_Define_(BitCTypeReal_16,data_16,0xD),
	_BitC_DT_Define_(BitCTypeReal_32,real_32,0xE),
	_BitC_DT_Define_(BitCTypeReal_64,real_64,0xF)
};

_BITC_ bitc_te BitC_DT_Enum_(MEMC_DT _PL_ Desc)
{
	return ((Desc)?((Desc->Scope==BitClip)?((bitc_te)(Desc->Index)):(BitCTypeUnknown)):(BitCTypeUnknown));
}
_BITC_ MEMC_DT *BitC_DT_Desc_(BITC_TE Enum)
{
	return ((Enum>BitCTypeUnknown)?((Enum<BitCTypes)?(TableType+Enum):(NULL)):(NULL));
}

#undef _BitC_DT_Define_
#endif

#if(Fold_(Domain:Host))

#if(Fold_(Definition:Just Functions))
_BITC_ data_08 BitC_Just_D08_(DATA_08 X) { return X; }
_BITC_ data_16 BitC_Just_D16_(DATA_16 X) { return X; }
_BITC_ data_32 BitC_Just_D32_(DATA_32 X) { return X; }
_BITC_ data_64 BitC_Just_D64_(DATA_64 X) { return X; }
#endif

#if(Fold_(Definition:Endian Functions))
_BITC_ general BitC_Endian_D08_(data_08 _PL_ Data,ADDRESS Length)
{
	Mute_(Data);
	Mute_(Length);

	return;
}
_BITC_ general BitC_Endian_D16_(data_16 _PL_ Data,ADDRESS Length)
{
	DATA_08 *End=(data_08*)(Data+(Length&BitC.Const.Mask.Safe[2]));
	data_08 *_R_ Ptr=(data_08*)Data;
	data_08 Temp;

	for(;Ptr<End;Ptr+=8)
	{
		Temp=Ptr[0];
		Ptr[0]=Ptr[1];
		Ptr[1]=Temp;

		Temp=Ptr[2];
		Ptr[2]=Ptr[3];
		Ptr[3]=Temp;

		Temp=Ptr[4];
		Ptr[4]=Ptr[5];
		Ptr[5]=Temp;

		Temp=Ptr[6];
		Ptr[6]=Ptr[7];
		Ptr[7]=Temp;
	}
	for(End+=((Length&BitC.Const.Mask.Rest[2])<<1);Ptr<End;Ptr+=2)
	{
		Temp=Ptr[0];
		Ptr[0]=Ptr[1];
		Ptr[1]=Temp;
	}

	return;
}
_BITC_ general BitC_Endian_D32_(data_32 _PL_ Data,ADDRESS Length)
{
	DATA_08 *End=(data_08*)(Data+(Length&BitC.Const.Mask.Safe[1]));
	data_08 *_R_ Ptr=(data_08*)Data;
	data_08 Temp;

	for(;Ptr<End;Ptr+=8)
	{
		Temp=Ptr[0];
		Ptr[0]=Ptr[3];
		Ptr[3]=Temp;

		Temp=Ptr[1];
		Ptr[1]=Ptr[2];
		Ptr[2]=Temp;
		
		Temp=Ptr[4];
		Ptr[4]=Ptr[7];
		Ptr[7]=Temp;

		Temp=Ptr[5];
		Ptr[5]=Ptr[6];
		Ptr[6]=Temp;
	}
	for(End+=((Length&BitC.Const.Mask.Rest[1])<<2);Ptr<End;Ptr+=4)
	{
		Temp=Ptr[0];
		Ptr[0]=Ptr[3];
		Ptr[3]=Temp;

		Temp=Ptr[1];
		Ptr[1]=Ptr[2];
		Ptr[2]=Temp;
	}

	return;
}
_BITC_ general BitC_Endian_D64_(data_64 _PL_ Data,ADDRESS Length)
{
	DATA_08 *End=(data_08*)(Data+Length);
	data_08 *_R_ Ptr=(data_08*)Data;
	data_08 Temp;

	for(;Ptr<End;Ptr+=8)
	{
		Temp=Ptr[0];
		Ptr[0]=Ptr[7];
		Ptr[7]=Temp;

		Temp=Ptr[1];
		Ptr[1]=Ptr[6];
		Ptr[6]=Temp;

		Temp=Ptr[2];
		Ptr[2]=Ptr[5];
		Ptr[5]=Temp;

		Temp=Ptr[3];
		Ptr[3]=Ptr[4];
		Ptr[4]=Temp;
	}

	return;
}
#endif

#if(Fold_(Definition:Internal Copy Functions))
#define _BitC_Copy_
#define _BitC_Data_
#include "bitcrux.c"
#undef _BitC_Data_
#undef _BitC_Copy_
#endif

#if(Fold_(Definition:Caster Functions))
#define _BitC_Caster_
#include "bitcrux.c"
#undef _BitC_Caster_
#endif

#if(Fold_(Definition:Bit Operation Functions))
static data_64 _BitC_Wide_Mask_D08_(DATA_08 Mask)
{
	data_64 Wide=(data_64)Mask;

	Wide|=(Wide<<8);
	Wide|=(Wide<<16);
	Wide|=(Wide<<32);

	return Wide;
}
static data_64 _BitC_Wide_Mask_D16_(DATA_16 Mask)
{
	data_64 Wide=(data_64)Mask;

	Wide|=(Wide<<16);
	Wide|=(Wide<<32);

	return Wide;
}
static data_64 _BitC_Wide_Mask_D32_(DATA_32 Mask)
{
	data_64 Wide=(data_64)Mask;

	Wide|=(Wide<<32);

	return Wide;
}
static data_64 _BitC_Wide_Mask_D64_(DATA_64 Mask)
{
	return Mask;
}

#if(Fold_(Part:BitC_BO_N_1_))
#define _BitC_BO_N_1_
#define BitC_Op_ BitC_BO_N_
#define _BitC_Data_
#include "bitcrux.c"
#undef _BitC_Data_
#undef BitC_Op_
#undef _BitC_BO_N_1_
#endif

#if(Fold_(Part:BitC_BO_S_1_))
#define _BitC_BO_S_1_
#define BitC_Op_ BitC_BO_S_
#define _BitC_Data_
#define _BitC_Inte_
#include "bitcrux.c"
#undef _BitC_Inte_
#undef _BitC_Data_
#undef BitC_Op_
#undef _BitC_BO_S_1_
#endif

#if(Fold_(Part:BitC_BO_A_,BitC_BO_O_,BitC_BO_X_))
#define _BitC_BO_Op_
#define _BitC_Data_
#define BitC_Op_ BitC_BO_A_
#include "bitcrux.c"
#undef BitC_Op_
#define BitC_Op_ BitC_BO_O_
#include "bitcrux.c"
#undef BitC_Op_
#define BitC_Op_ BitC_BO_X_
#include "bitcrux.c"
#undef BitC_Op_
#undef _BitC_Data_
#undef _BitC_BO_Op_
#endif
#endif

#if(Fold_(Definition:Relational Operation Functions))
static data_08 _BitC_RO_Loop_A_(BITCLIP M)
{
	M.V.D32[1]<<=4;
	M.V.D32[0]|=M.C.D32[1];

	M.V.D16[1]<<=2;
	M.V.D16[0]|=M.C.D16[1];

	M.V.D08[1]<<=1;
	M.V.D08[0]|=M.C.D08[1];

	return M.C.D08[0];
}
static general _BitC_RO_Loop_B_(BITCLIP M,DATA_08 R)
{
	M.V.D32[0]|=M.C.D32[1];
	M.V.D16[0]|=M.C.D16[1];
	M.V.D08[0]|=M.C.D08[1];

	M.V.D08[1]=0xFF;
	M.V.D08[1]<<=R;

	return;
}

#if(Fold_(Part:BitC_Expand_))
#define _BitC_Expand_
#define _BitC_Data_
#include "bitcrux.c"
#undef _BitC_Data_
#undef _BitC_Expand_
#endif

#if(Fold_(Part:BitC_Shrink_))
_BITC_ general BitC_Shrink_D08_(DATA_08 *_R_ DataI,data_08 *_R_ DataO,ADDRESS Length)
{
	DATA_64 _PL_ Peek=(data_64*)TableShrink08;
	ADDRESS Safe=Length&BitC.Const.Mask.Safe[3];
	ADDRESS Rest=Length&BitC.Const.Mask.Rest[3];
	BITCLIP Mask={.V.D64=&(data_64) { 0 }};

	for(DATA_08 _PL_ End=DataI+Safe;DataI<End;DataI+=8,DataO++)
	{
		Mask.V.D64[0]=(((data_64*)DataI)[0])&(Peek[0]);
		Mask.V.D32[0]|=Mask.C.D32[1];
		Mask.V.D16[0]|=Mask.C.D16[1];
		Mask.V.D08[0]|=Mask.C.D08[1];

		DataO[0]=Mask.C.D08[0];
	}
	if(Rest)
	{
		Mask.V.D64[0]=0;
		for(address Index=0;Index<Rest;Index++)
			Mask.V.D08[Index]=DataI[Index]&TableShrink08[Index];

		_BitC_RO_Loop_B_(Mask,(DATA_08)(Rest));

		DataO[0]&=Mask.C.D08[1];
		DataO[0]|=Mask.C.D08[0];
	}
	else;

	return;
}
_BITC_ general BitC_Shrink_D16_(DATA_16 *_R_ DataI,data_08 *_R_ DataO,ADDRESS Length)
{
	DATA_64 _PL_ Peek=(data_64*)TableShrink16;
	ADDRESS Safe=Length&BitC.Const.Mask.Safe[3];
	ADDRESS Rest=Length&BitC.Const.Mask.Rest[3];
	BITCLIP Mask={.V.D64=(data_64[2]) { 0 }};

	for(DATA_16 _PL_ End=DataI+Safe;DataI<End;DataI+=8,DataO++)
	{
		Mask.V.D64[0]=(((data_64*)DataI)[0])&(Peek[0]);
		Mask.V.D64[1]=(((data_64*)DataI)[1])&(Peek[1]);
		Mask.V.D64[0]|=Mask.C.D64[1];
		Mask.V.D32[0]|=Mask.C.D32[1];
		Mask.V.D16[0]|=Mask.C.D16[1];
		Mask.V.D08[0]|=Mask.C.D08[1];

		DataO[0]=Mask.C.D08[0];
	}
	if(Rest)
	{
		Mask.V.D64[0]=0;
		for(address Index=0;Index<Rest;Index++)
			Mask.V.D16[Index]=DataI[Index]&TableShrink16[Index];

		Mask.V.D64[0]|=Mask.C.D64[1];
		_BitC_RO_Loop_B_(Mask,(DATA_08)(Rest));

		DataO[0]&=Mask.C.D08[1];
		DataO[0]|=Mask.C.D08[0];
	}
	else;

	return;
}
_BITC_ general BitC_Shrink_D32_(DATA_32 *_R_ DataI,data_08 *_R_ DataO,ADDRESS Length)
{
	DATA_64 _PL_ Peek=(data_64*)TableShrink32;
	ADDRESS Safe=Length&BitC.Const.Mask.Safe[3];
	ADDRESS Rest=Length&BitC.Const.Mask.Rest[3];
	BITCLIP Mask={.V.D64=(data_64[4]) { 0 }};

	for(DATA_32 _PL_ End=DataI+Safe;DataI<End;DataI+=8,DataO++)
	{
		Mask.V.D64[0]=(((data_64*)DataI)[0])&(Peek[0]);
		Mask.V.D64[1]=(((data_64*)DataI)[1])&(Peek[1]);
		Mask.V.D64[2]=(((data_64*)DataI)[2])&(Peek[2]);
		Mask.V.D64[3]=(((data_64*)DataI)[3])&(Peek[3]);
		Mask.V.D64[0]|=Mask.C.D64[2];
		Mask.V.D64[1]|=Mask.C.D64[3];
		Mask.V.D64[0]|=Mask.C.D64[1];
		Mask.V.D32[0]|=Mask.C.D32[1];
		Mask.V.D16[0]|=Mask.C.D16[1];
		Mask.V.D08[0]|=Mask.C.D08[1];

		DataO[0]=Mask.C.D08[0];
	}
	if(Rest)
	{
		Mask.V.D64[0]=0;
		for(address Index=0;Index<Rest;Index++)
			Mask.V.D32[Index]=DataI[Index]&TableShrink32[Index];

		Mask.V.D64[0]|=Mask.C.D64[2];
		Mask.V.D64[1]|=Mask.C.D64[3];
		Mask.V.D64[0]|=Mask.C.D64[1];
		_BitC_RO_Loop_B_(Mask,(DATA_08)(Rest));

		DataO[0]&=Mask.C.D08[1];
		DataO[0]|=Mask.C.D08[0];
	}
	else;

	return;
}
_BITC_ general BitC_Shrink_D64_(DATA_64 *_R_ DataI,data_08 *_R_ DataO,ADDRESS Length)
{
	ADDRESS Safe=Length&BitC.Const.Mask.Safe[3];
	ADDRESS Rest=Length&BitC.Const.Mask.Rest[3];
	BITCLIP Mask={.V.D64=(data_64[8]) { 0 }};

	for(DATA_64 _PL_ End=DataI+Safe;DataI<End;DataI+=8,DataO++)
	{
		Mask.V.D64[0]=(DataI[0])&(TableShrink64[0]);
		Mask.V.D64[1]=(DataI[1])&(TableShrink64[1]);
		Mask.V.D64[2]=(DataI[2])&(TableShrink64[2]);
		Mask.V.D64[3]=(DataI[3])&(TableShrink64[3]);
		Mask.V.D64[4]=(DataI[0])&(TableShrink64[0]);
		Mask.V.D64[5]=(DataI[1])&(TableShrink64[1]);
		Mask.V.D64[6]=(DataI[2])&(TableShrink64[2]);
		Mask.V.D64[7]=(DataI[3])&(TableShrink64[3]);
		Mask.V.D64[0]|=Mask.C.D64[4];
		Mask.V.D64[1]|=Mask.C.D64[5];
		Mask.V.D64[2]|=Mask.C.D64[6];
		Mask.V.D64[3]|=Mask.C.D64[7];
		Mask.V.D64[0]|=Mask.C.D64[2];
		Mask.V.D64[1]|=Mask.C.D64[3];
		Mask.V.D64[0]|=Mask.C.D64[1];
		Mask.V.D32[0]|=Mask.C.D32[1];
		Mask.V.D16[0]|=Mask.C.D16[1];
		Mask.V.D08[0]|=Mask.C.D08[1];

		DataO[0]=Mask.C.D08[0];
	}
	if(Rest)
	{
		Mask.V.D64[0]=0;
		for(address Index=0;Index<Rest;Index++)
			Mask.V.D64[Index]=DataI[Index]&TableShrink64[Index];

		Mask.V.D64[0]|=Mask.C.D64[4];
		Mask.V.D64[1]|=Mask.C.D64[5];
		Mask.V.D64[2]|=Mask.C.D64[6];
		Mask.V.D64[3]|=Mask.C.D64[7];
		Mask.V.D64[0]|=Mask.C.D64[2];
		Mask.V.D64[1]|=Mask.C.D64[3];
		Mask.V.D64[0]|=Mask.C.D64[1];
		_BitC_RO_Loop_B_(Mask,(DATA_08)(Rest));

		DataO[0]&=Mask.C.D08[1];
		DataO[0]|=Mask.C.D08[0];
	}
	else;

	return;
}
#endif

#if(Fold_(Part:BitC_RO_E_,BitC_RO_N_))
#define _BitC_RO_Op_
#define _BitC_Data_
#define BitC_Op_ BitC_RO_E_
#include "bitcrux.c"
#undef BitC_Op_
#define BitC_Op_ BitC_RO_N_
#include "bitcrux.c"
#undef BitC_Op_
#undef _BitC_Data_
#undef _BitC_RO_Op_
#endif

#if(Fold_(Part:BitC_RO_G_,BitC_RO_L_))
#define _BitC_RO_Op_
#define _BitC_Data_
#define _BitC_Inte_
#define _BitC_Real_
#define BitC_Op_ BitC_RO_G_
#include "bitcrux.c"
#undef BitC_Op_
#define BitC_Op_ BitC_RO_L_
#include "bitcrux.c"
#undef BitC_Op_
#undef _BitC_Real_
#undef _BitC_Inte_
#undef _BitC_Data_
#undef _BitC_RO_Op_
#endif
#endif

#if(Fold_(Definition:Reformation Functions))
static logical _BitC_Reform_Valid_(ADDRESS *_R_ Map,ADDRESS Dims)
{
	logical Table[_BitC_Dims_]={0};

	for(address Idx=0;Idx<Dims;Idx++)
		if(Map[Idx]<Dims)
			Table[Map[Idx]]=1;
		else
			return 0;

	for(address Idx=0;Idx<Dims;Idx++)
		if(Table[Idx]);
		else
			return 0;

	return 1;
}
static general _BitC_Reform_Short_(ADDRESS _PL_ Shape,ADDRESS _PL_ Map,address _PL_ Dims,address _PL_ Bytes)
{
	for(address Temp=(*Dims)-1;Temp;Temp--)
		if(Map[Temp]==Temp)
		{
			(*Bytes)*=Shape[Temp];
			(*Dims)=Temp;
		}
		else
			break;

	return;
}
static general _BitC_Reform_Merge_(address _PL_ Shape,address _PL_ Map,address _PL_ Dims)
{
	ADDRESS *End=Map+(*Dims);
	ADDRESS *Last=End-1;

	for(address *MapA=Map,*ShpA=Shape;MapA<Last;MapA++,ShpA++)
	{
		ADDRESS *MapB=MapA;
		ADDRESS *ShpB=ShpA;

		for(;MapB<Last;MapB++,ShpB++)
			if((MapB[0]+1)==MapB[1])
				ShpA[0]*=ShpB[1];
			else
				break;

		if(MapA<MapB)
		{
			ADDRESS Pull=MapB-MapA;
			address *MapC=Map;
			address *ShpC=ShpA;

			for(;MapC<MapA;MapC++)
				if(MapC[0]>MapA[0])
					MapC[0]-=Pull;
				else;

			for(MapB++,MapC++,ShpB++,ShpC++;MapB<End;MapB++,MapC++,ShpB++,ShpC++)
			{
				MapC[0]=(MapA[0]<MapB[0])?(MapB[0]-Pull):(MapB[0]);
				ShpC[0]=ShpB[0];
			}

			End=MapC;
			Last=End-1;
			*Dims=End-Map;
		}
		else;
	}

	return;
}
static address _BitC_Reform_Total_(ADDRESS *_R_ Shape,ADDRESS Dims)
{
	address Total=1;

	for(ADDRESS _PL_ End=Shape+Dims;Shape<End;Shape++)
		Total*=*Shape;

	return Total;
}
static general _BitC_Reform_Order_(BITCLIP Source,BITCLIP Target,ADDRESS _PL_ Shape,ADDRESS _PL_ Map,ADDRESS Total,ADDRESS Dims,ADDRESS Bytes)
{
	ADDRESS Switch=Bytes&BitC.Const.Mask.Rest[3];
	ADDRESS Loop=Bytes>>TableReform[Switch];
	ADDRESS Last=Dims-1;
	address Jump[_BitC_Dims_];
	address Prod;
	address IdxS;
	address IdxT;
	address IdxJ;

	switch(Switch)
	{
	default:
		for(IdxT=0;IdxT<Total;IdxT++)
		{
			for(IdxJ=Last,Prod=IdxT/Shape[Map[Last]],Jump[Map[Last]]=IdxT%Shape[Map[Last]];IdxJ;Prod/=Shape[Map[IdxJ]])
			{
				IdxJ--;
				Jump[Map[IdxJ]]=Prod%Shape[Map[IdxJ]];
			}
			for(IdxJ=Last,IdxS=Jump[Last],Prod=Shape[Last];IdxJ;Prod*=Shape[IdxJ])
			{
				IdxJ--;
				IdxS+=Prod*Jump[IdxJ];
			}
			IdxS*=Loop;
			for(Prod=IdxS+Loop,IdxJ=IdxT*Loop;IdxS<Prod;IdxS++,IdxJ++)
				Target.V.D08[IdxJ]=Source.C.D08[IdxS];
		}
		return;
	case 2:case 6:
		for(IdxT=0;IdxT<Total;IdxT++)
		{
			for(IdxJ=Last,Prod=IdxT/Shape[Map[Last]],Jump[Map[Last]]=IdxT%Shape[Map[Last]];IdxJ;Prod/=Shape[Map[IdxJ]])
			{
				IdxJ--;
				Jump[Map[IdxJ]]=Prod%Shape[Map[IdxJ]];
			}
			for(IdxJ=Last,IdxS=Jump[Last],Prod=Shape[Last];IdxJ;Prod*=Shape[IdxJ])
			{
				IdxJ--;
				IdxS+=Prod*Jump[IdxJ];
			}
			IdxS*=Loop;
			for(Prod=IdxS+Loop,IdxJ=IdxT*Loop;IdxS<Prod;IdxS++,IdxJ++)
				Target.V.D16[IdxJ]=Source.C.D16[IdxS];
		}
		return;
	case 4:
		for(IdxT=0;IdxT<Total;IdxT++)
		{
			for(IdxJ=Last,Prod=IdxT/Shape[Map[Last]],Jump[Map[Last]]=IdxT%Shape[Map[Last]];IdxJ;Prod/=Shape[Map[IdxJ]])
			{
				IdxJ--;
				Jump[Map[IdxJ]]=Prod%Shape[Map[IdxJ]];
			}
			for(IdxJ=Last,IdxS=Jump[Last],Prod=Shape[Last];IdxJ;Prod*=Shape[IdxJ])
			{
				IdxJ--;
				IdxS+=Prod*Jump[IdxJ];
			}
			IdxS*=Loop;
			for(Prod=IdxS+Loop,IdxJ=IdxT*Loop;IdxS<Prod;IdxS++,IdxJ++)
				Target.V.D32[IdxJ]=Source.C.D32[IdxS];
		}
		return;
	case 0:
		for(IdxT=0;IdxT<Total;IdxT++)
		{
			for(IdxJ=Last,Prod=IdxT/Shape[Map[Last]],Jump[Map[Last]]=IdxT%Shape[Map[Last]];IdxJ;Prod/=Shape[Map[IdxJ]])
			{
				IdxJ--;
				Jump[Map[IdxJ]]=Prod%Shape[Map[IdxJ]];
			}
			for(IdxJ=Last,IdxS=Jump[Last],Prod=Shape[Last];IdxJ;Prod*=Shape[IdxJ])
			{
				IdxJ--;
				IdxS+=Prod*Jump[IdxJ];
			}
			IdxS*=Loop;
			for(Prod=IdxS+Loop,IdxJ=IdxT*Loop;IdxS<Prod;IdxS++,IdxJ++)
				Target.V.D64[IdxJ]=Source.C.D64[IdxS];
		}
		return;
	}
}
_BITC_ logical _BitC_Reform_(GENERAL _PL_ ArrayS,general _PL_ ArrayT,ADDRESS _PL_ ShapeS,ADDRESS _PL_ AxisStoT,address Dimensions,address Bytes)
{
	if(Dimensions)
	{
		_BitC_Reform_Short_(ShapeS,AxisStoT,&Dimensions,&Bytes);
		if(Dimensions>1)
			if(Dimensions>_BitC_Dims_);
			else if(_BitC_Reform_Valid_(AxisStoT,Dimensions))
			{
				ADDRESS Total=_BitC_Reform_Total_(ShapeS,Dimensions);

				if(Total)
				{
					address ShapeSNew[_BitC_Dims_];
					address MapTNew[_BitC_Dims_];

					if(MemC_Copy_1D_(ShapeS,ShapeSNew,Dimensions));
					else
						return 0;

					if(MemC_Copy_1D_(AxisStoT,MapTNew,Dimensions));
					else
						return 0;

					_BitC_Reform_Merge_(ShapeSNew,MapTNew,&Dimensions);
					_BitC_Reform_Order_(Acs_(BITCLIP,ArrayS),Acs_(BITCLIP,ArrayT),ShapeSNew,MapTNew,Total,Dimensions,Bytes);
				}
				else;

				return 1;
			}
			else;
		else if(AxisStoT[0]);
		else
		{
			ADDRESS Copy=ShapeS[0]*Bytes;

			if(Copy)
				return MemC_Copy_Byte_(ArrayS,ArrayT,Copy);
			else
				return 1;
		}

		return 0;
	}
	else
		return 1;
}
#endif

#if(Fold_(Definition:Bit Pointer Functions))
_BITC_ bitc_bp BitC_BP_Assign_S_(general _PL_ Base,SINTPTR Offset)
{
	bitc_bp BP;

	BP.Base=Base;
	BP.Base+=Offset>>3;
	BP.Offset=Offset&7;

	return BP;
}
_BITC_ bitc_bp BitC_BP_Assign_U_(general _PL_ Base,UINTPTR Offset)
{
	bitc_bp BP;

	BP.Base=Base;
	BP.Base+=Offset>>3;
	BP.Offset=Offset&7;

	return BP;
}
_BITC_ bitc_bp BitC_BP_Jumper_S_(bitc_bp BP,sintptr Move)
{
	Move+=BP.Offset;
	BP.Base+=Move>>3;
	BP.Offset=Move&7;

	return BP;
}
_BITC_ bitc_bp BitC_BP_Jumper_U_(bitc_bp BP,uintptr Move)
{
	Move+=BP.Offset;
	BP.Base+=Move>>3;
	BP.Offset=Move&7;

	return BP;
}
_BITC_ logical BitC_BP_Reader_(BITC_BP BP)
{
	LOGICAL Table[2]={0,1};
	data_08 Temp=*(BP.Base);

	Temp>>=(DATA_08)(BP.Offset);
	Temp&=0x01;

	return Table[Temp];
}
_BITC_ general BitC_BP_Writer_(BITC_BP BP,LOGICAL Bool)
{
	data_08 Mask=((DATA_08)(0x01))<<((DATA_08)(BP.Offset));
	inte_08 Temp=(inte_08)(Bool);

	*(BP.Base)|=Mask;
	Mask=~Mask;
	Temp=-Temp;
	Mask|=Temp;
	*(BP.Base)&=Mask;

	return;
}
#endif

#endif

#if(Fold_(Domain:Device)&&defined(__OPENCL_H))

#if(Fold_(Part:Internal Constants))
#define _BitC_Meta_(Enum) {.Size=sizeof(BitCKernelName[Enum]),.Data=BitCKernelName[Enum]}

enum _bitc_ki
{
	BitCEndianD08,BitCEndianD16,BitCEndianD32,BitCEndianD64,

	BitCReformD08,BitCReformD16,BitCReformD32,BitCReformD64,

	BitCCasterD08D08,BitCCasterD08D16,BitCCasterD08D32,BitCCasterD08D64,BitCCasterD08I08,BitCCasterD08I16,BitCCasterD08I32,BitCCasterD08I64,BitCCasterD08R08,BitCCasterD08R16,BitCCasterD08R32,BitCCasterD08R64,
	BitCCasterD16D08,BitCCasterD16D16,BitCCasterD16D32,BitCCasterD16D64,BitCCasterD16I08,BitCCasterD16I16,BitCCasterD16I32,BitCCasterD16I64,BitCCasterD16R08,BitCCasterD16R16,BitCCasterD16R32,BitCCasterD16R64,
	BitCCasterD32D08,BitCCasterD32D16,BitCCasterD32D32,BitCCasterD32D64,BitCCasterD32I08,BitCCasterD32I16,BitCCasterD32I32,BitCCasterD32I64,BitCCasterD32R08,BitCCasterD32R16,BitCCasterD32R32,BitCCasterD32R64,
	BitCCasterD64D08,BitCCasterD64D16,BitCCasterD64D32,BitCCasterD64D64,BitCCasterD64I08,BitCCasterD64I16,BitCCasterD64I32,BitCCasterD64I64,BitCCasterD64R08,BitCCasterD64R16,BitCCasterD64R32,BitCCasterD64R64,
	BitCCasterI08D08,BitCCasterI08D16,BitCCasterI08D32,BitCCasterI08D64,BitCCasterI08I08,BitCCasterI08I16,BitCCasterI08I32,BitCCasterI08I64,BitCCasterI08R08,BitCCasterI08R16,BitCCasterI08R32,BitCCasterI08R64,
	BitCCasterI16D08,BitCCasterI16D16,BitCCasterI16D32,BitCCasterI16D64,BitCCasterI16I08,BitCCasterI16I16,BitCCasterI16I32,BitCCasterI16I64,BitCCasterI16R08,BitCCasterI16R16,BitCCasterI16R32,BitCCasterI16R64,
	BitCCasterI32D08,BitCCasterI32D16,BitCCasterI32D32,BitCCasterI32D64,BitCCasterI32I08,BitCCasterI32I16,BitCCasterI32I32,BitCCasterI32I64,BitCCasterI32R08,BitCCasterI32R16,BitCCasterI32R32,BitCCasterI32R64,
	BitCCasterI64D08,BitCCasterI64D16,BitCCasterI64D32,BitCCasterI64D64,BitCCasterI64I08,BitCCasterI64I16,BitCCasterI64I32,BitCCasterI64I64,BitCCasterI64R08,BitCCasterI64R16,BitCCasterI64R32,BitCCasterI64R64,
	BitCCasterR08D08,BitCCasterR08D16,BitCCasterR08D32,BitCCasterR08D64,BitCCasterR08I08,BitCCasterR08I16,BitCCasterR08I32,BitCCasterR08I64,BitCCasterR08R08,BitCCasterR08R16,BitCCasterR08R32,BitCCasterR08R64,
	BitCCasterR16D08,BitCCasterR16D16,BitCCasterR16D32,BitCCasterR16D64,BitCCasterR16I08,BitCCasterR16I16,BitCCasterR16I32,BitCCasterR16I64,BitCCasterR16R08,BitCCasterR16R16,BitCCasterR16R32,BitCCasterR16R64,
	BitCCasterR32D08,BitCCasterR32D16,BitCCasterR32D32,BitCCasterR32D64,BitCCasterR32I08,BitCCasterR32I16,BitCCasterR32I32,BitCCasterR32I64,BitCCasterR32R08,BitCCasterR32R16,BitCCasterR32R32,BitCCasterR32R64,
	BitCCasterR64D08,BitCCasterR64D16,BitCCasterR64D32,BitCCasterR64D64,BitCCasterR64I08,BitCCasterR64I16,BitCCasterR64I32,BitCCasterR64I64,BitCCasterR64R08,BitCCasterR64R16,BitCCasterR64R32,BitCCasterR64R64,

	BitCBON1D08,BitCBON1D16,BitCBON1D32,BitCBON1D64,
	BitCBOSLD08,BitCBOSLD16,BitCBOSLD32,BitCBOSLD64,
	BitCBOSRD08,BitCBOSRD16,BitCBOSRD32,BitCBOSRD64,BitCBOSRI08,BitCBOSRI16,BitCBOSRI32,BitCBOSRI64,
	BitCBOA1D08,BitCBOA1D16,BitCBOA1D32,BitCBOA1D64,BitCBOA2D08,BitCBOA2D16,BitCBOA2D32,BitCBOA2D64,
	BitCBOO1D08,BitCBOO1D16,BitCBOO1D32,BitCBOO1D64,BitCBOO2D08,BitCBOO2D16,BitCBOO2D32,BitCBOO2D64,
	BitCBOX1D08,BitCBOX1D16,BitCBOX1D32,BitCBOX1D64,BitCBOX2D08,BitCBOX2D16,BitCBOX2D32,BitCBOX2D64,

	BitCROE1D08,BitCROE1D16,BitCROE1D32,BitCROE1D64,BitCROE2D08,BitCROE2D16,BitCROE2D32,BitCROE2D64,
	BitCRON1D08,BitCRON1D16,BitCRON1D32,BitCRON1D64,BitCRON2D08,BitCRON2D16,BitCRON2D32,BitCRON2D64,
	BitCROG1D08,BitCROG1D16,BitCROG1D32,BitCROG1D64,BitCROG2D08,BitCROG2D16,BitCROG2D32,BitCROG2D64,BitCROG1I08,BitCROG1I16,BitCROG1I32,BitCROG1I64,BitCROG2I08,BitCROG2I16,BitCROG2I32,BitCROG2I64,BitCROG1R08,BitCROG1R16,BitCROG1R32,BitCROG1R64,BitCROG2R08,BitCROG2R16,BitCROG2R32,BitCROG2R64,
	BitCROL1D08,BitCROL1D16,BitCROL1D32,BitCROL1D64,BitCROL2D08,BitCROL2D16,BitCROL2D32,BitCROL2D64,BitCROL1I08,BitCROL1I16,BitCROL1I32,BitCROL1I64,BitCROL2I08,BitCROL2I16,BitCROL2I32,BitCROL2I64,BitCROL1R08,BitCROL1R16,BitCROL1R32,BitCROL1R64,BitCROL2R08,BitCROL2R16,BitCROL2R32,BitCROL2R64,

	BitCKernelNums
};
MemC_Type_Declare_(enum,bitc_ki,BITC_KI);

static BYTE_08 BitCKernelName[BitCKernelNums][32]=
{
	"BitC_Endian_D08_","BitC_Endian_D16_","BitC_Endian_D32_","BitC_Endian_D64_",

	"BitC_Reform_D08_","BitC_Reform_D16_","BitC_Reform_D32_","BitC_Reform_D64_",

	"BitC_Caster_D08_D08_","BitC_Caster_D08_D16_","BitC_Caster_D08_D32_","BitC_Caster_D08_D64_","BitC_Caster_D08_I08_","BitC_Caster_D08_I16_","BitC_Caster_D08_I32_","BitC_Caster_D08_I64_","BitC_Caster_D08_R08_","BitC_Caster_D08_R16_","BitC_Caster_D08_R32_","BitC_Caster_D08_R64_",
	"BitC_Caster_D16_D08_","BitC_Caster_D16_D16_","BitC_Caster_D16_D32_","BitC_Caster_D16_D64_","BitC_Caster_D16_I08_","BitC_Caster_D16_I16_","BitC_Caster_D16_I32_","BitC_Caster_D16_I64_","BitC_Caster_D16_R08_","BitC_Caster_D16_R16_","BitC_Caster_D16_R32_","BitC_Caster_D16_R64_",
	"BitC_Caster_D32_D08_","BitC_Caster_D32_D16_","BitC_Caster_D32_D32_","BitC_Caster_D32_D64_","BitC_Caster_D32_I08_","BitC_Caster_D32_I16_","BitC_Caster_D32_I32_","BitC_Caster_D32_I64_","BitC_Caster_D32_R08_","BitC_Caster_D32_R16_","BitC_Caster_D32_R32_","BitC_Caster_D32_R64_",
	"BitC_Caster_D64_D08_","BitC_Caster_D64_D16_","BitC_Caster_D64_D32_","BitC_Caster_D64_D64_","BitC_Caster_D64_I08_","BitC_Caster_D64_I16_","BitC_Caster_D64_I32_","BitC_Caster_D64_I64_","BitC_Caster_D64_R08_","BitC_Caster_D64_R16_","BitC_Caster_D64_R32_","BitC_Caster_D64_R64_",
	"BitC_Caster_I08_D08_","BitC_Caster_I08_D16_","BitC_Caster_I08_D32_","BitC_Caster_I08_D64_","BitC_Caster_I08_I08_","BitC_Caster_I08_I16_","BitC_Caster_I08_I32_","BitC_Caster_I08_I64_","BitC_Caster_I08_R08_","BitC_Caster_I08_R16_","BitC_Caster_I08_R32_","BitC_Caster_I08_R64_",
	"BitC_Caster_I16_D08_","BitC_Caster_I16_D16_","BitC_Caster_I16_D32_","BitC_Caster_I16_D64_","BitC_Caster_I16_I08_","BitC_Caster_I16_I16_","BitC_Caster_I16_I32_","BitC_Caster_I16_I64_","BitC_Caster_I16_R08_","BitC_Caster_I16_R16_","BitC_Caster_I16_R32_","BitC_Caster_I16_R64_",
	"BitC_Caster_I32_D08_","BitC_Caster_I32_D16_","BitC_Caster_I32_D32_","BitC_Caster_I32_D64_","BitC_Caster_I32_I08_","BitC_Caster_I32_I16_","BitC_Caster_I32_I32_","BitC_Caster_I32_I64_","BitC_Caster_I32_R08_","BitC_Caster_I32_R16_","BitC_Caster_I32_R32_","BitC_Caster_I32_R64_",
	"BitC_Caster_I64_D08_","BitC_Caster_I64_D16_","BitC_Caster_I64_D32_","BitC_Caster_I64_D64_","BitC_Caster_I64_I08_","BitC_Caster_I64_I16_","BitC_Caster_I64_I32_","BitC_Caster_I64_I64_","BitC_Caster_I64_R08_","BitC_Caster_I64_R16_","BitC_Caster_I64_R32_","BitC_Caster_I64_R64_",
	"BitC_Caster_R08_D08_","BitC_Caster_R08_D16_","BitC_Caster_R08_D32_","BitC_Caster_R08_D64_","BitC_Caster_R08_I08_","BitC_Caster_R08_I16_","BitC_Caster_R08_I32_","BitC_Caster_R08_I64_","BitC_Caster_R08_R08_","BitC_Caster_R08_R16_","BitC_Caster_R08_R32_","BitC_Caster_R08_R64_",
	"BitC_Caster_R16_D08_","BitC_Caster_R16_D16_","BitC_Caster_R16_D32_","BitC_Caster_R16_D64_","BitC_Caster_R16_I08_","BitC_Caster_R16_I16_","BitC_Caster_R16_I32_","BitC_Caster_R16_I64_","BitC_Caster_R16_R08_","BitC_Caster_R16_R16_","BitC_Caster_R16_R32_","BitC_Caster_R16_R64_",
	"BitC_Caster_R32_D08_","BitC_Caster_R32_D16_","BitC_Caster_R32_D32_","BitC_Caster_R32_D64_","BitC_Caster_R32_I08_","BitC_Caster_R32_I16_","BitC_Caster_R32_I32_","BitC_Caster_R32_I64_","BitC_Caster_R32_R08_","BitC_Caster_R32_R16_","BitC_Caster_R32_R32_","BitC_Caster_R32_R64_",
	"BitC_Caster_R64_D08_","BitC_Caster_R64_D16_","BitC_Caster_R64_D32_","BitC_Caster_R64_D64_","BitC_Caster_R64_I08_","BitC_Caster_R64_I16_","BitC_Caster_R64_I32_","BitC_Caster_R64_I64_","BitC_Caster_R64_R08_","BitC_Caster_R64_R16_","BitC_Caster_R64_R32_","BitC_Caster_R64_R64_",

	"BitC_BO_N_1_D08_","BitC_BO_N_1_D16_","BitC_BO_N_1_D32_","BitC_BO_N_1_D64_",
	"BitC_BO_S_L_D08_","BitC_BO_S_L_D16_","BitC_BO_S_L_D32_","BitC_BO_S_L_D64_",
	"BitC_BO_S_R_D08_","BitC_BO_S_R_D16_","BitC_BO_S_R_D32_","BitC_BO_S_R_D64_","BitC_BO_S_R_I08_","BitC_BO_S_R_I16_","BitC_BO_S_R_I32_","BitC_BO_S_R_I64_",
	"BitC_BO_A_1_D08_","BitC_BO_A_1_D16_","BitC_BO_A_1_D32_","BitC_BO_A_1_D64_","BitC_BO_A_2_D08_","BitC_BO_A_2_D16_","BitC_BO_A_2_D32_","BitC_BO_A_2_D64_",
	"BitC_BO_O_1_D08_","BitC_BO_O_1_D16_","BitC_BO_O_1_D32_","BitC_BO_O_1_D64_","BitC_BO_O_2_D08_","BitC_BO_O_2_D16_","BitC_BO_O_2_D32_","BitC_BO_O_2_D64_",
	"BitC_BO_X_1_D08_","BitC_BO_X_1_D16_","BitC_BO_X_1_D32_","BitC_BO_X_1_D64_","BitC_BO_X_2_D08_","BitC_BO_X_2_D16_","BitC_BO_X_2_D32_","BitC_BO_X_2_D64_",

	"BitC_RO_E_1_D08_","BitC_RO_E_1_D16_","BitC_RO_E_1_D32_","BitC_RO_E_1_D64_","BitC_RO_E_2_D08_","BitC_RO_E_2_D16_","BitC_RO_E_2_D32_","BitC_RO_E_2_D64_",
	"BitC_RO_N_1_D08_","BitC_RO_N_1_D16_","BitC_RO_N_1_D32_","BitC_RO_N_1_D64_","BitC_RO_N_2_D08_","BitC_RO_N_2_D16_","BitC_RO_N_2_D32_","BitC_RO_N_2_D64_",
	"BitC_RO_G_1_D08_","BitC_RO_G_1_D16_","BitC_RO_G_1_D32_","BitC_RO_G_1_D64_","BitC_RO_G_2_D08_","BitC_RO_G_2_D16_","BitC_RO_G_2_D32_","BitC_RO_G_2_D64_","BitC_RO_G_1_I08_","BitC_RO_G_1_I16_","BitC_RO_G_1_I32_","BitC_RO_G_1_I64_","BitC_RO_G_2_I08_","BitC_RO_G_2_I16_","BitC_RO_G_2_I32_","BitC_RO_G_2_I64_","BitC_RO_G_1_R08_","BitC_RO_G_1_R16_","BitC_RO_G_1_R32_","BitC_RO_G_1_R64_","BitC_RO_G_2_R08_","BitC_RO_G_2_R16_","BitC_RO_G_2_R32_","BitC_RO_G_2_R64_",
	"BitC_RO_L_1_D08_","BitC_RO_L_1_D16_","BitC_RO_L_1_D32_","BitC_RO_L_1_D64_","BitC_RO_L_2_D08_","BitC_RO_L_2_D16_","BitC_RO_L_2_D32_","BitC_RO_L_2_D64_","BitC_RO_L_1_I08_","BitC_RO_L_1_I16_","BitC_RO_L_1_I32_","BitC_RO_L_1_I64_","BitC_RO_L_2_I08_","BitC_RO_L_2_I16_","BitC_RO_L_2_I32_","BitC_RO_L_2_I64_","BitC_RO_L_1_R08_","BitC_RO_L_1_R16_","BitC_RO_L_1_R32_","BitC_RO_L_1_R64_","BitC_RO_L_2_R08_","BitC_RO_L_2_R16_","BitC_RO_L_2_R32_","BitC_RO_L_2_R64_"
};
static OCLC_MD BitCKernelList[BitCKernelNums]=
{
	_BitC_Meta_(BitCEndianD08),_BitC_Meta_(BitCEndianD16),_BitC_Meta_(BitCEndianD32),_BitC_Meta_(BitCEndianD64),

	_BitC_Meta_(BitCReformD08),_BitC_Meta_(BitCReformD16),_BitC_Meta_(BitCReformD32),_BitC_Meta_(BitCReformD64),

	_BitC_Meta_(BitCCasterD08D08),_BitC_Meta_(BitCCasterD08D16),_BitC_Meta_(BitCCasterD08D32),_BitC_Meta_(BitCCasterD08D64),_BitC_Meta_(BitCCasterD08I08),_BitC_Meta_(BitCCasterD08I16),_BitC_Meta_(BitCCasterD08I32),_BitC_Meta_(BitCCasterD08I64),_BitC_Meta_(BitCCasterD08R08),_BitC_Meta_(BitCCasterD08R16),_BitC_Meta_(BitCCasterD08R32),_BitC_Meta_(BitCCasterD08R64),
	_BitC_Meta_(BitCCasterD16D08),_BitC_Meta_(BitCCasterD16D16),_BitC_Meta_(BitCCasterD16D32),_BitC_Meta_(BitCCasterD16D64),_BitC_Meta_(BitCCasterD16I08),_BitC_Meta_(BitCCasterD16I16),_BitC_Meta_(BitCCasterD16I32),_BitC_Meta_(BitCCasterD16I64),_BitC_Meta_(BitCCasterD16R08),_BitC_Meta_(BitCCasterD16R16),_BitC_Meta_(BitCCasterD16R32),_BitC_Meta_(BitCCasterD16R64),
	_BitC_Meta_(BitCCasterD32D08),_BitC_Meta_(BitCCasterD32D16),_BitC_Meta_(BitCCasterD32D32),_BitC_Meta_(BitCCasterD32D64),_BitC_Meta_(BitCCasterD32I08),_BitC_Meta_(BitCCasterD32I16),_BitC_Meta_(BitCCasterD32I32),_BitC_Meta_(BitCCasterD32I64),_BitC_Meta_(BitCCasterD32R08),_BitC_Meta_(BitCCasterD32R16),_BitC_Meta_(BitCCasterD32R32),_BitC_Meta_(BitCCasterD32R64),
	_BitC_Meta_(BitCCasterD64D08),_BitC_Meta_(BitCCasterD64D16),_BitC_Meta_(BitCCasterD64D32),_BitC_Meta_(BitCCasterD64D64),_BitC_Meta_(BitCCasterD64I08),_BitC_Meta_(BitCCasterD64I16),_BitC_Meta_(BitCCasterD64I32),_BitC_Meta_(BitCCasterD64I64),_BitC_Meta_(BitCCasterD64R08),_BitC_Meta_(BitCCasterD64R16),_BitC_Meta_(BitCCasterD64R32),_BitC_Meta_(BitCCasterD64R64),
	_BitC_Meta_(BitCCasterI08D08),_BitC_Meta_(BitCCasterI08D16),_BitC_Meta_(BitCCasterI08D32),_BitC_Meta_(BitCCasterI08D64),_BitC_Meta_(BitCCasterI08I08),_BitC_Meta_(BitCCasterI08I16),_BitC_Meta_(BitCCasterI08I32),_BitC_Meta_(BitCCasterI08I64),_BitC_Meta_(BitCCasterI08R08),_BitC_Meta_(BitCCasterI08R16),_BitC_Meta_(BitCCasterI08R32),_BitC_Meta_(BitCCasterI08R64),
	_BitC_Meta_(BitCCasterI16D08),_BitC_Meta_(BitCCasterI16D16),_BitC_Meta_(BitCCasterI16D32),_BitC_Meta_(BitCCasterI16D64),_BitC_Meta_(BitCCasterI16I08),_BitC_Meta_(BitCCasterI16I16),_BitC_Meta_(BitCCasterI16I32),_BitC_Meta_(BitCCasterI16I64),_BitC_Meta_(BitCCasterI16R08),_BitC_Meta_(BitCCasterI16R16),_BitC_Meta_(BitCCasterI16R32),_BitC_Meta_(BitCCasterI16R64),
	_BitC_Meta_(BitCCasterI32D08),_BitC_Meta_(BitCCasterI32D16),_BitC_Meta_(BitCCasterI32D32),_BitC_Meta_(BitCCasterI32D64),_BitC_Meta_(BitCCasterI32I08),_BitC_Meta_(BitCCasterI32I16),_BitC_Meta_(BitCCasterI32I32),_BitC_Meta_(BitCCasterI32I64),_BitC_Meta_(BitCCasterI32R08),_BitC_Meta_(BitCCasterI32R16),_BitC_Meta_(BitCCasterI32R32),_BitC_Meta_(BitCCasterI32R64),
	_BitC_Meta_(BitCCasterI64D08),_BitC_Meta_(BitCCasterI64D16),_BitC_Meta_(BitCCasterI64D32),_BitC_Meta_(BitCCasterI64D64),_BitC_Meta_(BitCCasterI64I08),_BitC_Meta_(BitCCasterI64I16),_BitC_Meta_(BitCCasterI64I32),_BitC_Meta_(BitCCasterI64I64),_BitC_Meta_(BitCCasterI64R08),_BitC_Meta_(BitCCasterI64R16),_BitC_Meta_(BitCCasterI64R32),_BitC_Meta_(BitCCasterI64R64),
	_BitC_Meta_(BitCCasterR08D08),_BitC_Meta_(BitCCasterR08D16),_BitC_Meta_(BitCCasterR08D32),_BitC_Meta_(BitCCasterR08D64),_BitC_Meta_(BitCCasterR08I08),_BitC_Meta_(BitCCasterR08I16),_BitC_Meta_(BitCCasterR08I32),_BitC_Meta_(BitCCasterR08I64),_BitC_Meta_(BitCCasterR08R08),_BitC_Meta_(BitCCasterR08R16),_BitC_Meta_(BitCCasterR08R32),_BitC_Meta_(BitCCasterR08R64),
	_BitC_Meta_(BitCCasterR16D08),_BitC_Meta_(BitCCasterR16D16),_BitC_Meta_(BitCCasterR16D32),_BitC_Meta_(BitCCasterR16D64),_BitC_Meta_(BitCCasterR16I08),_BitC_Meta_(BitCCasterR16I16),_BitC_Meta_(BitCCasterR16I32),_BitC_Meta_(BitCCasterR16I64),_BitC_Meta_(BitCCasterR16R08),_BitC_Meta_(BitCCasterR16R16),_BitC_Meta_(BitCCasterR16R32),_BitC_Meta_(BitCCasterR16R64),
	_BitC_Meta_(BitCCasterR32D08),_BitC_Meta_(BitCCasterR32D16),_BitC_Meta_(BitCCasterR32D32),_BitC_Meta_(BitCCasterR32D64),_BitC_Meta_(BitCCasterR32I08),_BitC_Meta_(BitCCasterR32I16),_BitC_Meta_(BitCCasterR32I32),_BitC_Meta_(BitCCasterR32I64),_BitC_Meta_(BitCCasterR32R08),_BitC_Meta_(BitCCasterR32R16),_BitC_Meta_(BitCCasterR32R32),_BitC_Meta_(BitCCasterR32R64),
	_BitC_Meta_(BitCCasterR64D08),_BitC_Meta_(BitCCasterR64D16),_BitC_Meta_(BitCCasterR64D32),_BitC_Meta_(BitCCasterR64D64),_BitC_Meta_(BitCCasterR64I08),_BitC_Meta_(BitCCasterR64I16),_BitC_Meta_(BitCCasterR64I32),_BitC_Meta_(BitCCasterR64I64),_BitC_Meta_(BitCCasterR64R08),_BitC_Meta_(BitCCasterR64R16),_BitC_Meta_(BitCCasterR64R32),_BitC_Meta_(BitCCasterR64R64),

	_BitC_Meta_(BitCBON1D08),_BitC_Meta_(BitCBON1D16),_BitC_Meta_(BitCBON1D32),_BitC_Meta_(BitCBON1D64),
	_BitC_Meta_(BitCBOSLD08),_BitC_Meta_(BitCBOSLD16),_BitC_Meta_(BitCBOSLD32),_BitC_Meta_(BitCBOSLD64),
	_BitC_Meta_(BitCBOSRD08),_BitC_Meta_(BitCBOSRD16),_BitC_Meta_(BitCBOSRD32),_BitC_Meta_(BitCBOSRD64),_BitC_Meta_(BitCBOSRI08),_BitC_Meta_(BitCBOSRI16),_BitC_Meta_(BitCBOSRI32),_BitC_Meta_(BitCBOSRI64),
	_BitC_Meta_(BitCBOA1D08),_BitC_Meta_(BitCBOA1D16),_BitC_Meta_(BitCBOA1D32),_BitC_Meta_(BitCBOA1D64),_BitC_Meta_(BitCBOA2D08),_BitC_Meta_(BitCBOA2D16),_BitC_Meta_(BitCBOA2D32),_BitC_Meta_(BitCBOA2D64),
	_BitC_Meta_(BitCBOO1D08),_BitC_Meta_(BitCBOO1D16),_BitC_Meta_(BitCBOO1D32),_BitC_Meta_(BitCBOO1D64),_BitC_Meta_(BitCBOO2D08),_BitC_Meta_(BitCBOO2D16),_BitC_Meta_(BitCBOO2D32),_BitC_Meta_(BitCBOO2D64),
	_BitC_Meta_(BitCBOX1D08),_BitC_Meta_(BitCBOX1D16),_BitC_Meta_(BitCBOX1D32),_BitC_Meta_(BitCBOX1D64),_BitC_Meta_(BitCBOX2D08),_BitC_Meta_(BitCBOX2D16),_BitC_Meta_(BitCBOX2D32),_BitC_Meta_(BitCBOX2D64),

	_BitC_Meta_(BitCROE1D08),_BitC_Meta_(BitCROE1D16),_BitC_Meta_(BitCROE1D32),_BitC_Meta_(BitCROE1D64),_BitC_Meta_(BitCROE2D08),_BitC_Meta_(BitCROE2D16),_BitC_Meta_(BitCROE2D32),_BitC_Meta_(BitCROE2D64),
	_BitC_Meta_(BitCRON1D08),_BitC_Meta_(BitCRON1D16),_BitC_Meta_(BitCRON1D32),_BitC_Meta_(BitCRON1D64),_BitC_Meta_(BitCRON2D08),_BitC_Meta_(BitCRON2D16),_BitC_Meta_(BitCRON2D32),_BitC_Meta_(BitCRON2D64),
	_BitC_Meta_(BitCROG1D08),_BitC_Meta_(BitCROG1D16),_BitC_Meta_(BitCROG1D32),_BitC_Meta_(BitCROG1D64),_BitC_Meta_(BitCROG2D08),_BitC_Meta_(BitCROG2D16),_BitC_Meta_(BitCROG2D32),_BitC_Meta_(BitCROG2D64),_BitC_Meta_(BitCROG1I08),_BitC_Meta_(BitCROG1I16),_BitC_Meta_(BitCROG1I32),_BitC_Meta_(BitCROG1I64),_BitC_Meta_(BitCROG2I08),_BitC_Meta_(BitCROG2I16),_BitC_Meta_(BitCROG2I32),_BitC_Meta_(BitCROG2I64),_BitC_Meta_(BitCROG1R08),_BitC_Meta_(BitCROG1R16),_BitC_Meta_(BitCROG1R32),_BitC_Meta_(BitCROG1R64),_BitC_Meta_(BitCROG2R08),_BitC_Meta_(BitCROG2R16),_BitC_Meta_(BitCROG2R32),_BitC_Meta_(BitCROG2R64),
	_BitC_Meta_(BitCROL1D08),_BitC_Meta_(BitCROL1D16),_BitC_Meta_(BitCROL1D32),_BitC_Meta_(BitCROL1D64),_BitC_Meta_(BitCROL2D08),_BitC_Meta_(BitCROL2D16),_BitC_Meta_(BitCROL2D32),_BitC_Meta_(BitCROL2D64),_BitC_Meta_(BitCROL1I08),_BitC_Meta_(BitCROL1I16),_BitC_Meta_(BitCROL1I32),_BitC_Meta_(BitCROL1I64),_BitC_Meta_(BitCROL2I08),_BitC_Meta_(BitCROL2I16),_BitC_Meta_(BitCROL2I32),_BitC_Meta_(BitCROL2I64),_BitC_Meta_(BitCROL1R08),_BitC_Meta_(BitCROL1R16),_BitC_Meta_(BitCROL1R32),_BitC_Meta_(BitCROL1R64),_BitC_Meta_(BitCROL2R08),_BitC_Meta_(BitCROL2R16),_BitC_Meta_(BitCROL2R32),_BitC_Meta_(BitCROL2R64)
};

#undef _BitC_Meta_
#endif

#if(Fold_(Part:Program Manager))
_BITC_ general BitC_CL_Build_T08_(const cl_context Context,BYTE_08 _PL_ BuildOption,TEXT_08 _PL_ SourcePath,TEXT_08 _PL_ _PL_ BinaryPath,FILE _PL_ Stream,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
	{
		oclc_pm *PM=OCLCL.PM.Create_(BitClip,BitCKernelList,BitCKernelNums);

		if(PM)
		{
			OCLCL.PM.Build.Source.T08_(PM,Context,BuildOption,&SourcePath,1,Error);
			if(Error->E==CLSuccess)
			{
				OCLCL.PM.Build.Log_(PM,Stream,Error);
				if(Error->E==CLSuccess)
					OCLCL.PM.Build.Save.T08_(PM,BinaryPath,Error);
				else;
			}
			else
			{
				oclc_ef Local={0};

				OCLCL.PM.Build.Log_(PM,Stream,&Local);
			}
			OCLCL.PM.Delete_(&PM);
		}
		else
			Error->E=CLOutOfHostMemory;
	}
	else;

	return;
}
_BITC_ general BitC_CL_Build_T16_(const cl_context Context,BYTE_08 _PL_ BuildOption,TEXT_16 _PL_ SourcePath,TEXT_16 _PL_ _PL_ BinaryPath,FILE _PL_ Stream,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
	{
		oclc_pm *PM=OCLCL.PM.Create_(BitClip,BitCKernelList,BitCKernelNums);

		if(PM)
		{
			OCLCL.PM.Build.Source.T16_(PM,Context,BuildOption,&SourcePath,1,Error);
			if(Error->E==CLSuccess)
			{
				OCLCL.PM.Build.Log_(PM,Stream,Error);
				if(Error->E==CLSuccess)
					OCLCL.PM.Build.Save.T16_(PM,BinaryPath,Error);
				else;
			}
			else
			{
				oclc_ef Local={0};

				OCLCL.PM.Build.Log_(PM,Stream,&Local);
			}
			OCLCL.PM.Delete_(&PM);
		}
		else
			Error->E=CLOutOfHostMemory;
	}
	else;

	return;
}

_BITC_ oclc_pm *BitC_CL_Create_T08_(const cl_context Context,BYTE_08 _PL_ BuildOption,TEXT_08 _PL_ _PL_ BinaryPath,FILE _PL_ Stream,oclc_ef _PL_ Error)
{
	oclc_pm *PM;
	
	if(Error->E==CLSuccess)
	{
		PM=OCLCL.PM.Create_(BitClip,BitCKernelList,BitCKernelNums);
		if(PM)
		{
			OCLCL.PM.Build.Binary.T08_(PM,Context,BuildOption,BinaryPath,Error);
			if(Error->E==CLSuccess)
			{
				OCLCL.PM.Build.Log_(PM,Stream,Error);
				if(Error->E!=CLSuccess)
					OCLCL.PM.Delete_(&PM);
				else;
			}
			else
			{
				oclc_ef Local={0};

				OCLCL.PM.Build.Log_(PM,Stream,&Local);
			}
		}
		else
			Error->E=CLOutOfHostMemory;
	}
	else
		PM=NULL;

	return PM;
}
_BITC_ oclc_pm *BitC_CL_Create_T16_(const cl_context Context,BYTE_08 _PL_ BuildOption,TEXT_16 _PL_ _PL_ BinaryPath,FILE _PL_ Stream,oclc_ef _PL_ Error)
{
	oclc_pm *PM;

	if(Error->E==CLSuccess)
	{
		PM=OCLCL.PM.Create_(BitClip,BitCKernelList,BitCKernelNums);
		if(PM)
		{
			OCLCL.PM.Build.Binary.T16_(PM,Context,BuildOption,BinaryPath,Error);
			if(Error->E==CLSuccess)
			{
				OCLCL.PM.Build.Log_(PM,Stream,Error);
				if(Error->E!=CLSuccess)
					OCLCL.PM.Delete_(&PM);
				else;
			}
			else
			{
				oclc_ef Local={0};

				OCLCL.PM.Build.Log_(PM,Stream,&Local);
			}
		}
		else
			Error->E=CLOutOfHostMemory;
	}
	else
		PM=NULL;

	return PM;
}
#endif

#if(Fold_(Part:Internal Functions))
static GENERAL *_BitC_CL_Pin_Cast_(OCLC_MP _PL_ Pin,general _PL_ Buffer,ADDRESS Bits)
{
	bitclip Peek;

	if((sizeof(address)<<3)==Bits)
		Peek.C.AA=Pin->S;
	else
		switch(Bits)
		{
		case 8:
			Peek.C.G=Buffer;
			Peek.V.D08[OCLCPinAxisN]=(data_08)(Pin->S[OCLCPinAxisN]);
			Peek.V.D08[OCLCPinAxisZ]=(data_08)(Pin->S[OCLCPinAxisZ]);
			Peek.V.D08[OCLCPinAxisY]=(data_08)(Pin->S[OCLCPinAxisY]);
			Peek.V.D08[OCLCPinAxisX]=(data_08)(Pin->S[OCLCPinAxisX]);
			break;
		case 16:
			Peek.C.G=Buffer;
			Peek.V.D16[OCLCPinAxisN]=(data_16)(Pin->S[OCLCPinAxisN]);
			Peek.V.D16[OCLCPinAxisZ]=(data_16)(Pin->S[OCLCPinAxisZ]);
			Peek.V.D16[OCLCPinAxisY]=(data_16)(Pin->S[OCLCPinAxisY]);
			Peek.V.D16[OCLCPinAxisX]=(data_16)(Pin->S[OCLCPinAxisX]);
			break;
		case 32:
			Peek.C.G=Buffer;
			Peek.V.D32[OCLCPinAxisN]=(data_32)(Pin->S[OCLCPinAxisN]);
			Peek.V.D32[OCLCPinAxisZ]=(data_32)(Pin->S[OCLCPinAxisZ]);
			Peek.V.D32[OCLCPinAxisY]=(data_32)(Pin->S[OCLCPinAxisY]);
			Peek.V.D32[OCLCPinAxisX]=(data_32)(Pin->S[OCLCPinAxisX]);
			break;
		case 64:
			Peek.C.G=Buffer;
			Peek.V.D64[OCLCPinAxisN]=(data_64)(Pin->S[OCLCPinAxisN]);
			Peek.V.D64[OCLCPinAxisZ]=(data_64)(Pin->S[OCLCPinAxisZ]);
			Peek.V.D64[OCLCPinAxisY]=(data_64)(Pin->S[OCLCPinAxisY]);
			Peek.V.D64[OCLCPinAxisX]=(data_64)(Pin->S[OCLCPinAxisX]);
			break;
		default:
			Peek.C.G=NULL;
		}

	return Peek.V.G;
}
static OCLC_MP *_BitC_CL_Pin_Default_(OCLC_MP _PL_ Pin,OCLC_MP _PL_ Default)
{
	return ((Pin)?(Pin):(Default));
}
static cl_uint _BitC_CL_Address_Bits_(const cl_command_queue Queue,oclc_ef _PL_ Error)
{
	cl_device_id Device;OCLCL_Info_(Queue,Queue,&Device,CL_QUEUE_DEVICE,Error);
	cl_uint Bits;OCLCL_Info_(Device,Device,&Bits,CL_DEVICE_ADDRESS_BITS,Error);

	return Bits;
}
static general _BitC_CL_Set_0_(const cl_command_queue Queue,const cl_kernel Kernel,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ Region,oclc_ef _PL_ Error)
{
	OCLC_MP _PL_ AOfs=_BitC_CL_Pin_Default_(ADesc->Start,OCLCL.MP.Zero);
	OCLC_MP _PL_ AShp=_BitC_CL_Pin_Default_(ADesc->Shape,Region);

	if(OCLCL.MP.Offset.Invalid_(AOfs,AShp))
		Error->E=CLInvalidValue;
	else if(OCLCL.MP.Length.Invalid_(AOfs,Region,AShp))
		Error->E=CLInvalidValue;
	else
	{
		ADDRESS Bits=(address)_BitC_CL_Address_Bits_(Queue,Error);
		ADDRESS PinSize=Bits>>1;
		data_64 Buffer[OCLCPinAxes];

		OCLCL.Kernel.Arg.G_(Kernel,0,ADesc->Memory,Error);
		OCLCL.Kernel.Arg.P_(Kernel,1,_BitC_CL_Pin_Cast_(AOfs,Buffer,Bits),PinSize,Error);
		OCLCL.Kernel.Arg.P_(Kernel,2,_BitC_CL_Pin_Cast_(Region,Buffer,Bits),PinSize,Error);
		OCLCL.Kernel.Arg.P_(Kernel,3,_BitC_CL_Pin_Cast_(AShp,Buffer,Bits),PinSize,Error);
	}

	return;
}
static general _BitC_CL_Set_1_(const cl_command_queue Queue,const cl_kernel Kernel,OCLC_MH _PL_ ADesc,OCLC_MH _PL_ BDesc,OCLC_MP _PL_ Region,oclc_ef _PL_ Error)
{
	OCLC_MP _PL_ AOfs=_BitC_CL_Pin_Default_(ADesc->Start,OCLCL.MP.Zero);
	OCLC_MP _PL_ BOfs=_BitC_CL_Pin_Default_(BDesc->Start,OCLCL.MP.Zero);
	OCLC_MP _PL_ AShp=_BitC_CL_Pin_Default_(ADesc->Shape,Region);
	OCLC_MP _PL_ BShp=_BitC_CL_Pin_Default_(BDesc->Shape,Region);

	if(OCLCL.MP.Offset.Invalid_(AOfs,AShp))
		Error->E=CLInvalidValue;
	else if(OCLCL.MP.Offset.Invalid_(BOfs,BShp))
		Error->E=CLInvalidValue;
	else if(OCLCL.MP.Length.Invalid_(AOfs,Region,AShp))
		Error->E=CLInvalidValue;
	else if(OCLCL.MP.Length.Invalid_(BOfs,Region,BShp))
		Error->E=CLInvalidValue;
	else
	{
		ADDRESS Bits=(address)_BitC_CL_Address_Bits_(Queue,Error);
		ADDRESS PinSize=Bits>>1;
		data_64 Buffer[OCLCPinAxes];

		OCLCL.Kernel.Arg.G_(Kernel,0,ADesc->Memory,Error);
		OCLCL.Kernel.Arg.G_(Kernel,1,BDesc->Memory,Error);
		OCLCL.Kernel.Arg.P_(Kernel,2,_BitC_CL_Pin_Cast_(AOfs,Buffer,Bits),PinSize,Error);
		OCLCL.Kernel.Arg.P_(Kernel,3,_BitC_CL_Pin_Cast_(BOfs,Buffer,Bits),PinSize,Error);
		OCLCL.Kernel.Arg.P_(Kernel,4,_BitC_CL_Pin_Cast_(Region,Buffer,Bits),PinSize,Error);
		OCLCL.Kernel.Arg.P_(Kernel,5,_BitC_CL_Pin_Cast_(AShp,Buffer,Bits),PinSize,Error);
		OCLCL.Kernel.Arg.P_(Kernel,6,_BitC_CL_Pin_Cast_(BShp,Buffer,Bits),PinSize,Error);
	}

	return;
}
static general _BitC_CL_Set_2_(const cl_command_queue Queue,const cl_kernel Kernel,OCLC_MH _PL_ ADesc,OCLC_MH _PL_ BDesc,OCLC_MH _PL_ CDesc,OCLC_MP _PL_ Region,oclc_ef _PL_ Error)
{
	OCLC_MP _PL_ AOfs=_BitC_CL_Pin_Default_(ADesc->Start,OCLCL.MP.Zero);
	OCLC_MP _PL_ BOfs=_BitC_CL_Pin_Default_(BDesc->Start,OCLCL.MP.Zero);
	OCLC_MP _PL_ COfs=_BitC_CL_Pin_Default_(CDesc->Start,OCLCL.MP.Zero);
	OCLC_MP _PL_ AShp=_BitC_CL_Pin_Default_(ADesc->Shape,Region);
	OCLC_MP _PL_ BShp=_BitC_CL_Pin_Default_(BDesc->Shape,Region);
	OCLC_MP _PL_ CShp=_BitC_CL_Pin_Default_(CDesc->Shape,Region);

	if(OCLCL.MP.Offset.Invalid_(AOfs,AShp))
		Error->E=CLInvalidValue;
	else if(OCLCL.MP.Offset.Invalid_(BOfs,BShp))
		Error->E=CLInvalidValue;
	else if(OCLCL.MP.Offset.Invalid_(COfs,CShp))
		Error->E=CLInvalidValue;
	else if(OCLCL.MP.Length.Invalid_(AOfs,Region,AShp))
		Error->E=CLInvalidValue;
	else if(OCLCL.MP.Length.Invalid_(BOfs,Region,BShp))
		Error->E=CLInvalidValue;
	else if(OCLCL.MP.Length.Invalid_(COfs,Region,CShp))
		Error->E=CLInvalidValue;
	else
	{
		ADDRESS Bits=(address)_BitC_CL_Address_Bits_(Queue,Error);
		ADDRESS PinSize=Bits>>1;
		data_64 Buffer[OCLCPinAxes];

		OCLCL.Kernel.Arg.G_(Kernel,0,ADesc->Memory,Error);
		OCLCL.Kernel.Arg.G_(Kernel,1,BDesc->Memory,Error);
		OCLCL.Kernel.Arg.G_(Kernel,2,CDesc->Memory,Error);
		OCLCL.Kernel.Arg.P_(Kernel,3,_BitC_CL_Pin_Cast_(AOfs,Buffer,Bits),PinSize,Error);
		OCLCL.Kernel.Arg.P_(Kernel,4,_BitC_CL_Pin_Cast_(BOfs,Buffer,Bits),PinSize,Error);
		OCLCL.Kernel.Arg.P_(Kernel,5,_BitC_CL_Pin_Cast_(COfs,Buffer,Bits),PinSize,Error);
		OCLCL.Kernel.Arg.P_(Kernel,6,_BitC_CL_Pin_Cast_(Region,Buffer,Bits),PinSize,Error);
		OCLCL.Kernel.Arg.P_(Kernel,7,_BitC_CL_Pin_Cast_(AShp,Buffer,Bits),PinSize,Error);
		OCLCL.Kernel.Arg.P_(Kernel,8,_BitC_CL_Pin_Cast_(BShp,Buffer,Bits),PinSize,Error);
		OCLCL.Kernel.Arg.P_(Kernel,9,_BitC_CL_Pin_Cast_(CShp,Buffer,Bits),PinSize,Error);
	}

	return;
}
static cl_int _BitC_CL_Enqueue_(const cl_command_queue Queue,const cl_kernel Kernel,ADDRESS Total)
{
	return clEnqueueNDRangeKernel(Queue,Kernel,1,NULL,&Total,NULL,0,NULL,NULL);
}
#endif

#if(Fold_(Part:Endian Functions))
static cl_kernel _BitC_CL_Endian_Kernel_(OCLC_PM _PL_ PM,ADDRESS TypeSize,oclc_ef _PL_ Error)
{
	switch(TypeSize)
	{
	default:
		Error->E=CLInvalidValue;
	case 1:
		return NULL;
	case 2:
	case 4:
	case 8:
		return PM->Program.Kernel.List[BitCEndianD16+(TypeSize>>2)].ID;
	}
}
_BITC_ general BitC_CL_Endian_(OCLC_PM _PL_ PM,const cl_command_queue Queue,OCLC_MH _PL_ Desc,OCLC_MP _PL_ Region,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==BitClip)
			{
				const cl_kernel Kernel=_BitC_CL_Endian_Kernel_(PM,Desc->Type->SizeType,Error);

				if(Kernel)
				{
					_BitC_CL_Set_0_(Queue,Kernel,Desc,Region,Error);
					if(Error->E==CLSuccess)
						Error->I=_BitC_CL_Enqueue_(Queue,Kernel,OCLCL.MP.Total_(Region));
					else;
				}
				else;
			}
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
	else;

	return;
}
#endif

#if(Fold_(Part:Caster Functions))
_BITC_ general BitC_CL_Caster_(OCLC_PM _PL_ PM,const cl_command_queue Queue,OCLC_MH _PL_ IDesc,OCLC_MH _PL_ ODesc,OCLC_MP _PL_ Region,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==BitClip)
			{
				BITC_TE IIdx=BitC_DT_Enum_(IDesc->Type);
				BITC_TE OIdx=BitC_DT_Enum_(ODesc->Type);

				if(IIdx==BitCTypeUnknown)
					Error->E=CLInvalidValue;
				else if(OIdx==BitCTypeUnknown)
					Error->E=CLInvalidValue;
				else if(IIdx==OIdx)
					OCLCL.Queue.Copy_(Queue,OCLCopyDtoD,IDesc,ODesc,Region,Error);
				else
				{
					BITC_TE TIdx=OIdx-BitCTypeInte_08;
					const cl_kernel Kernel=PM->Program.Kernel.List[(IIdx*BitCTypes)+(((IIdx<TIdx)&(TIdx<BitCTypeInte_08))?(TIdx):(OIdx))+BitCCasterD08D08].ID;

					_BitC_CL_Set_1_(Queue,Kernel,IDesc,ODesc,Region,Error);
					if(Error->E==CLSuccess)
						Error->I=_BitC_CL_Enqueue_(Queue,Kernel,OCLCL.MP.Total_(Region));
					else;
				}
			}
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
	else;

	return;
}
#endif

#if(Fold_(Part:Bit Operation Functions))
static cl_kernel _BitC_CL_BO_Kernel_(OCLC_PM _PL_ PM,BITC_KI Base,ADDRESS TypeSize)
{
	switch(TypeSize)
	{
	case 1:
		return PM->Program.Kernel.List[Base+BitCTypeData_08].ID;
	case 2:
		return PM->Program.Kernel.List[Base+BitCTypeData_16].ID;
	case 4:
		return PM->Program.Kernel.List[Base+BitCTypeData_32].ID;
	case 8:
		return PM->Program.Kernel.List[Base+BitCTypeData_64].ID;
	default:
		return NULL;
	}
}
_BITC_ general BitC_CL_BO_N_1_(OCLC_PM _PL_ PM,const cl_command_queue Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ Region,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==BitClip)
				if(CDesc->Type->SizeType==ADesc->Type->SizeType)
				{
					const cl_kernel Kernel=_BitC_CL_BO_Kernel_(PM,BitCBON1D08,CDesc->Type->SizeType);

					if(Kernel)
					{
						_BitC_CL_Set_1_(Queue,Kernel,CDesc,ADesc,Region,Error);
						if(Error->E==CLSuccess)
							Error->I=_BitC_CL_Enqueue_(Queue,Kernel,OCLCL.MP.Total_(Region));
						else;
					}
					else
						Error->E=CLInvalidValue;
				}
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
	else;

	return;
}
_BITC_ general BitC_CL_BO_S_1_(OCLC_PM _PL_ PM,const cl_command_queue Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ Region,integer Shift,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==BitClip)
				if(CDesc->Type==ADesc->Type)
				{
					BITC_TE Type=BitC_DT_Enum_(CDesc->Type);

					if(Type<BitCTypeData_08)
						Error->E=CLInvalidValue;
					else if(Type>BitCTypeInte_64)
						Error->E=CLInvalidValue;
					else
					{
						cl_kernel Kernel;

						if(Shift>0)
							Kernel=PM->Program.Kernel.List[BitCBOSLD08+(Type&3)].ID;
						else
						{
							Shift=-Shift;
							Kernel=PM->Program.Kernel.List[BitCBOSRD08+Type].ID;
						}

						_BitC_CL_Set_1_(Queue,Kernel,CDesc,ADesc,Region,Error);
						OCLCL.Kernel.Arg.P_(Kernel,7,&Shift,sizeof(integer),Error);
						if(Error->E==CLSuccess)
							Error->I=_BitC_CL_Enqueue_(Queue,Kernel,OCLCL.MP.Total_(Region));
						else;
					}
				}
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
	else;

	return;
}
_BITC_ general BitC_CL_BO_A_1_(OCLC_PM _PL_ PM,const cl_command_queue Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ Region,GENERAL _PL_ Mask,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==BitClip)
				if(CDesc->Type->SizeType==ADesc->Type->SizeType)
				{
					const cl_kernel Kernel=_BitC_CL_BO_Kernel_(PM,BitCBOA1D08,CDesc->Type->SizeType);

					if(Kernel)
					{
						_BitC_CL_Set_1_(Queue,Kernel,CDesc,ADesc,Region,Error);
						OCLCL.Kernel.Arg.P_(Kernel,7,Mask,CDesc->Type->SizeType,Error);
						if(Error->E==CLSuccess)
							Error->I=_BitC_CL_Enqueue_(Queue,Kernel,OCLCL.MP.Total_(Region));
						else;
					}
					else
						Error->E=CLInvalidValue;
				}
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
	else;

	return;
}
_BITC_ general BitC_CL_BO_A_2_(OCLC_PM _PL_ PM,const cl_command_queue Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MH _PL_ BDesc,OCLC_MP _PL_ Region,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==BitClip)
				if(CDesc->Type->SizeType==ADesc->Type->SizeType)
					if(CDesc->Type->SizeType==BDesc->Type->SizeType)
					{
						const cl_kernel Kernel=_BitC_CL_BO_Kernel_(PM,BitCBOA2D08,CDesc->Type->SizeType);

						if(Kernel)
						{
							_BitC_CL_Set_2_(Queue,Kernel,CDesc,ADesc,BDesc,Region,Error);
							if(Error->E==CLSuccess)
								Error->I=_BitC_CL_Enqueue_(Queue,Kernel,OCLCL.MP.Total_(Region));
							else;
						}
						else
							Error->E=CLInvalidValue;
					}
					else
						Error->E=CLInvalidValue;
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
	else;

	return;
}
_BITC_ general BitC_CL_BO_O_1_(OCLC_PM _PL_ PM,const cl_command_queue Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ Region,GENERAL _PL_ Mask,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==BitClip)
				if(CDesc->Type->SizeType==ADesc->Type->SizeType)
				{
					const cl_kernel Kernel=_BitC_CL_BO_Kernel_(PM,BitCBOO1D08,CDesc->Type->SizeType);

					if(Kernel)
					{
						_BitC_CL_Set_1_(Queue,Kernel,CDesc,ADesc,Region,Error);
						OCLCL.Kernel.Arg.P_(Kernel,7,Mask,CDesc->Type->SizeType,Error);
						if(Error->E==CLSuccess)
							Error->I=_BitC_CL_Enqueue_(Queue,Kernel,OCLCL.MP.Total_(Region));
						else;
					}
					else
						Error->E=CLInvalidValue;
				}
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
	else;

	return;
}
_BITC_ general BitC_CL_BO_O_2_(OCLC_PM _PL_ PM,const cl_command_queue Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MH _PL_ BDesc,OCLC_MP _PL_ Region,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==BitClip)
				if(CDesc->Type->SizeType==ADesc->Type->SizeType)
					if(CDesc->Type->SizeType==BDesc->Type->SizeType)
					{
						const cl_kernel Kernel=_BitC_CL_BO_Kernel_(PM,BitCBOO2D08,CDesc->Type->SizeType);

						if(Kernel)
						{
							_BitC_CL_Set_2_(Queue,Kernel,CDesc,ADesc,BDesc,Region,Error);
							if(Error->E==CLSuccess)
								Error->I=_BitC_CL_Enqueue_(Queue,Kernel,OCLCL.MP.Total_(Region));
							else;
						}
						else
							Error->E=CLInvalidValue;
					}
					else
						Error->E=CLInvalidValue;
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
	else;

	return;
}
_BITC_ general BitC_CL_BO_X_1_(OCLC_PM _PL_ PM,const cl_command_queue Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ Region,GENERAL _PL_ Mask,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==BitClip)
				if(CDesc->Type->SizeType==ADesc->Type->SizeType)
				{
					const cl_kernel Kernel=_BitC_CL_BO_Kernel_(PM,BitCBOX1D08,CDesc->Type->SizeType);

					if(Kernel)
					{
						_BitC_CL_Set_1_(Queue,Kernel,CDesc,ADesc,Region,Error);
						OCLCL.Kernel.Arg.P_(Kernel,7,Mask,CDesc->Type->SizeType,Error);
						if(Error->E==CLSuccess)
							Error->I=_BitC_CL_Enqueue_(Queue,Kernel,OCLCL.MP.Total_(Region));
						else;
					}
					else
						Error->E=CLInvalidValue;
				}
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
	else;

	return;
}
_BITC_ general BitC_CL_BO_X_2_(OCLC_PM _PL_ PM,const cl_command_queue Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MH _PL_ BDesc,OCLC_MP _PL_ Region,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==BitClip)
				if(CDesc->Type->SizeType==ADesc->Type->SizeType)
					if(CDesc->Type->SizeType==BDesc->Type->SizeType)
					{
						const cl_kernel Kernel=_BitC_CL_BO_Kernel_(PM,BitCBOX2D08,CDesc->Type->SizeType);

						if(Kernel)
						{
							_BitC_CL_Set_2_(Queue,Kernel,CDesc,ADesc,BDesc,Region,Error);
							if(Error->E==CLSuccess)
								Error->I=_BitC_CL_Enqueue_(Queue,Kernel,OCLCL.MP.Total_(Region));
							else;
						}
						else
							Error->E=CLInvalidValue;
					}
					else
						Error->E=CLInvalidValue;
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
	else;

	return;
}
#endif

#if(Fold_(Part:Relational Operation Functions))
static cl_kernel _BitC_CL_RO_Kernel_(OCLC_PM _PL_ PM,BITC_KI Base,INTEGER Mask,MEMC_DT _PL_ CType,MEMC_DT _PL_ AType)
{
	bitc_te Enum=BitC_DT_Enum_(CType);

	if(Enum<BitCTypeInte_08);
	else if(Enum>BitCTypeInte_64);
	else if((Enum=BitC_DT_Enum_(AType))==BitCTypeUnknown);
	else
		return PM->Program.Kernel.List[Base+(Enum&Mask)].ID;

	return NULL;
}
_BITC_ general BitC_CL_RO_E_1_(OCLC_PM _PL_ PM,const cl_command_queue Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ Region,GENERAL _PL_ Value,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==BitClip)
				if(CDesc->Type->SizeType==ADesc->Type->SizeType)
				{
					const cl_kernel Kernel=_BitC_CL_RO_Kernel_(PM,BitCROE1D08,3,CDesc->Type,ADesc->Type);

					if(Kernel)
					{
						_BitC_CL_Set_1_(Queue,Kernel,CDesc,ADesc,Region,Error);
						OCLCL.Kernel.Arg.P_(Kernel,7,Value,CDesc->Type->SizeType,Error);
						if(Error->E==CLSuccess)
							Error->I=_BitC_CL_Enqueue_(Queue,Kernel,OCLCL.MP.Total_(Region));
						else;
					}
					else
						Error->E=CLInvalidValue;
				}
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
	else;

	return;
}
_BITC_ general BitC_CL_RO_E_2_(OCLC_PM _PL_ PM,const cl_command_queue Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MH _PL_ BDesc,OCLC_MP _PL_ Region,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==BitClip)
				if(CDesc->Type->SizeType==ADesc->Type->SizeType)
					if(ADesc->Type==BDesc->Type)
					{
						const cl_kernel Kernel=_BitC_CL_RO_Kernel_(PM,BitCROE2D08,3,CDesc->Type,ADesc->Type);

						if(Kernel)
						{
							_BitC_CL_Set_2_(Queue,Kernel,CDesc,ADesc,BDesc,Region,Error);
							if(Error->E==CLSuccess)
								Error->I=_BitC_CL_Enqueue_(Queue,Kernel,OCLCL.MP.Total_(Region));
							else;
						}
						else
							Error->E=CLInvalidValue;
					}
					else
						Error->E=CLInvalidValue;
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
	else;

	return;
}
_BITC_ general BitC_CL_RO_N_1_(OCLC_PM _PL_ PM,const cl_command_queue Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ Region,GENERAL _PL_ Value,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==BitClip)
				if(CDesc->Type->SizeType==ADesc->Type->SizeType)
				{
					const cl_kernel Kernel=_BitC_CL_RO_Kernel_(PM,BitCRON1D08,3,CDesc->Type,ADesc->Type);
					
					if(Kernel)
					{
						_BitC_CL_Set_1_(Queue,Kernel,CDesc,ADesc,Region,Error);
						OCLCL.Kernel.Arg.P_(Kernel,7,Value,CDesc->Type->SizeType,Error);
						if(Error->E==CLSuccess)
							Error->I=_BitC_CL_Enqueue_(Queue,Kernel,OCLCL.MP.Total_(Region));
						else;
					}
					else
						Error->E=CLInvalidValue;
				}
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
	else;

	return;
}
_BITC_ general BitC_CL_RO_N_2_(OCLC_PM _PL_ PM,const cl_command_queue Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MH _PL_ BDesc,OCLC_MP _PL_ Region,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==BitClip)
				if(CDesc->Type->SizeType==ADesc->Type->SizeType)
					if(ADesc->Type==BDesc->Type)
					{
						const cl_kernel Kernel=_BitC_CL_RO_Kernel_(PM,BitCRON2D08,3,CDesc->Type,ADesc->Type);

						if(Kernel)
						{
							_BitC_CL_Set_2_(Queue,Kernel,CDesc,ADesc,BDesc,Region,Error);
							if(Error->E==CLSuccess)
								Error->I=_BitC_CL_Enqueue_(Queue,Kernel,OCLCL.MP.Total_(Region));
							else;
						}
						else
							Error->E=CLInvalidValue;
					}
					else
						Error->E=CLInvalidValue;
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
	else;

	return;
}
_BITC_ general BitC_CL_RO_G_1_(OCLC_PM _PL_ PM,const cl_command_queue Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ Region,GENERAL _PL_ Value,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==BitClip)
				if(CDesc->Type->SizeType==ADesc->Type->SizeType)
				{
					const cl_kernel Kernel=_BitC_CL_RO_Kernel_(PM,BitCROG1D08,-1,CDesc->Type,ADesc->Type);

					if(Kernel)
					{
						_BitC_CL_Set_1_(Queue,Kernel,CDesc,ADesc,Region,Error);
						OCLCL.Kernel.Arg.P_(Kernel,7,Value,CDesc->Type->SizeType,Error);
						if(Error->E==CLSuccess)
							Error->I=_BitC_CL_Enqueue_(Queue,Kernel,OCLCL.MP.Total_(Region));
						else;
					}
					else
						Error->E=CLInvalidValue;
				}
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
	else;

	return;
}
_BITC_ general BitC_CL_RO_G_2_(OCLC_PM _PL_ PM,const cl_command_queue Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MH _PL_ BDesc,OCLC_MP _PL_ Region,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==BitClip)
				if(CDesc->Type->SizeType==ADesc->Type->SizeType)
					if(ADesc->Type==BDesc->Type)
					{
						const cl_kernel Kernel=_BitC_CL_RO_Kernel_(PM,BitCROG2D08,-1,CDesc->Type,ADesc->Type);

						if(Kernel)
						{
							_BitC_CL_Set_2_(Queue,Kernel,CDesc,ADesc,BDesc,Region,Error);
							if(Error->E==CLSuccess)
								Error->I=_BitC_CL_Enqueue_(Queue,Kernel,OCLCL.MP.Total_(Region));
							else;
						}
						else
							Error->E=CLInvalidValue;
					}
					else
						Error->E=CLInvalidValue;
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
	else;

	return;
}
_BITC_ general BitC_CL_RO_L_1_(OCLC_PM _PL_ PM,const cl_command_queue Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ Region,GENERAL _PL_ Value,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==BitClip)
				if(CDesc->Type->SizeType==ADesc->Type->SizeType)
				{
					const cl_kernel Kernel=_BitC_CL_RO_Kernel_(PM,BitCROL1D08,-1,CDesc->Type,ADesc->Type);

					if(Kernel)
					{
						_BitC_CL_Set_1_(Queue,Kernel,CDesc,ADesc,Region,Error);
						OCLCL.Kernel.Arg.P_(Kernel,7,Value,CDesc->Type->SizeType,Error);
						if(Error->E==CLSuccess)
							Error->I=_BitC_CL_Enqueue_(Queue,Kernel,OCLCL.MP.Total_(Region));
						else;
					}
					else
						Error->E=CLInvalidValue;
				}
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
	else;

	return;
}
_BITC_ general BitC_CL_RO_L_2_(OCLC_PM _PL_ PM,const cl_command_queue Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MH _PL_ BDesc,OCLC_MP _PL_ Region,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==BitClip)
				if(CDesc->Type->SizeType==ADesc->Type->SizeType)
					if(ADesc->Type==BDesc->Type)
					{
						const cl_kernel Kernel=_BitC_CL_RO_Kernel_(PM,BitCROL2D08,-1,CDesc->Type,ADesc->Type);

						if(Kernel)
						{
							_BitC_CL_Set_2_(Queue,Kernel,CDesc,ADesc,BDesc,Region,Error);
							if(Error->E==CLSuccess)
								Error->I=_BitC_CL_Enqueue_(Queue,Kernel,OCLCL.MP.Total_(Region));
							else;
						}
						else
							Error->E=CLInvalidValue;
					}
					else
						Error->E=CLInvalidValue;
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
	else;

	return;
}
#endif

#if(Fold_(Part:Reformation Functions))
static OCLC_MP *_BitC_CL_Reform_Region_(OCLC_MP _PL_ _R_ SRegion,oclc_mp _PL_ _R_ TRegion,OCLC_MP _PL_ _R_ StoTAxis)
{
	TRegion->S[StoTAxis->N]=SRegion->N;
	TRegion->S[StoTAxis->Z]=SRegion->Z;
	TRegion->S[StoTAxis->Y]=SRegion->Y;
	TRegion->S[StoTAxis->X]=SRegion->X;

	return TRegion;
}
static general _BitC_CL_Reform_Set_(const cl_command_queue Queue,const cl_kernel Kernel,OCLC_MH _PL_ SDesc,OCLC_MH _PL_ TDesc,OCLC_MP _PL_ SRegion,OCLC_MP _PL_ StoTAxis,oclc_ef _PL_ Error)
{
	oclc_mp TRegion;
	OCLC_MP _PL_ SOfs=_BitC_CL_Pin_Default_(SDesc->Start,OCLCL.MP.Zero);
	OCLC_MP _PL_ TOfs=_BitC_CL_Pin_Default_(TDesc->Start,OCLCL.MP.Zero);
	OCLC_MP _PL_ SShp=_BitC_CL_Pin_Default_(SDesc->Shape,SRegion);
	OCLC_MP _PL_ TShp=_BitC_CL_Pin_Default_(TDesc->Shape,_BitC_CL_Reform_Region_(SRegion,&TRegion,StoTAxis));

	if(OCLCL.MP.Offset.Invalid_(SOfs,SShp))
		Error->E=CLInvalidValue;
	else if(OCLCL.MP.Offset.Invalid_(TOfs,TShp))
		Error->E=CLInvalidValue;
	else if(OCLCL.MP.Length.Invalid_(SOfs,SRegion,SShp))
		Error->E=CLInvalidValue;
	else if(OCLCL.MP.Length.Invalid_(TOfs,&TRegion,TShp))
		Error->E=CLInvalidValue;
	else
	{
		ADDRESS Bits=(address)_BitC_CL_Address_Bits_(Queue,Error);
		ADDRESS PinSize=Bits>>1;
		data_64 Buffer[OCLCPinAxes];

		OCLCL.Kernel.Arg.G_(Kernel,0,SDesc->Memory,Error);
		OCLCL.Kernel.Arg.G_(Kernel,1,TDesc->Memory,Error);
		OCLCL.Kernel.Arg.P_(Kernel,2,_BitC_CL_Pin_Cast_(SOfs,Buffer,Bits),PinSize,Error);
		OCLCL.Kernel.Arg.P_(Kernel,3,_BitC_CL_Pin_Cast_(TOfs,Buffer,Bits),PinSize,Error);
		OCLCL.Kernel.Arg.P_(Kernel,4,_BitC_CL_Pin_Cast_(&TRegion,Buffer,Bits),PinSize,Error);
		OCLCL.Kernel.Arg.P_(Kernel,5,_BitC_CL_Pin_Cast_(SShp,Buffer,Bits),PinSize,Error);
		OCLCL.Kernel.Arg.P_(Kernel,6,_BitC_CL_Pin_Cast_(TShp,Buffer,Bits),PinSize,Error);
		OCLCL.Kernel.Arg.P_(Kernel,7,_BitC_CL_Pin_Cast_(StoTAxis,Buffer,Bits),PinSize,Error);
	}

	return;
}
_BITC_ general BitC_CL_Reform_(OCLC_PM _PL_ PM,const cl_command_queue Queue,OCLC_MH _PL_ SDesc,OCLC_MH _PL_ TDesc,OCLC_MP _PL_ SRegion,OCLC_MP _PL_ StoTAxis,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==BitClip)
				if(SDesc->Type->SizeType==TDesc->Type->SizeType)
					if(_BitC_Reform_Valid_(StoTAxis->S,OCLCPinAxes))
					{
						const cl_kernel Kernel=_BitC_CL_BO_Kernel_(PM,BitCReformD08,SDesc->Type->SizeType);

						if(Kernel)
						{
							_BitC_CL_Reform_Set_(Queue,Kernel,SDesc,TDesc,SRegion,StoTAxis,Error);
							if(Error->E==CLSuccess)
								Error->I=_BitC_CL_Enqueue_(Queue,Kernel,OCLCL.MP.Total_(SRegion));
							else;
						}
						else
							Error->E=CLInvalidValue;
					}
					else
						Error->E=CLInvalidValue;
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
	else;

	return;
}
#endif

#endif

#if(Fold_(Undefinition:Internal Macros))
#include "bitcros.c"
#undef _BITC_
#endif

#if(Fold_(Library Casing))
BITCASE BitC=
{
	.Version=IdiomVersion,
	.Endianness=(data_08*)(ConstantMask+9),
	.MaxDims=_BitC_Dims_,
	.Reform_=_BitC_Reform_,
	.Type=
	{
		.D08=TableType+BitCTypeData_08,
		.D16=TableType+BitCTypeData_16,
		.D32=TableType+BitCTypeData_32,
		.D64=TableType+BitCTypeData_64,
		.I08=TableType+BitCTypeInte_08,
		.I16=TableType+BitCTypeInte_16,
		.I32=TableType+BitCTypeInte_32,
		.I64=TableType+BitCTypeInte_64,
		.R08=TableType+BitCTypeReal_08,
		.R16=TableType+BitCTypeReal_16,
		.R32=TableType+BitCTypeReal_32,
		.R64=TableType+BitCTypeReal_64,
		.Enum_=BitC_DT_Enum_,
		.Desc_=BitC_DT_Desc_
	},
	.Const=
	{
		.Pi=
		{
			.R32=(real_32*)(Constant32+0),
			.R64=(real_64*)(Constant64+0)
		},
		.Euler=
		{
			.R32=(real_32*)(Constant32+2),
			.R64=(real_64*)(Constant64+2)
		},
		.Inf=
		{
			.R32=(real_32*)(Constant32+4),
			.R64=(real_64*)(Constant64+4)
		},
		.NaN=
		{
			.R32=(real_32*)(Constant32+6),
			.R64=(real_64*)(Constant64+6)
		},
		.Mask=
		{
			.Safe=ConstantMask+0,
			.Rest=ConstantMask+8
		}
	},
	.Just=
	{
		.D08_=BitC_Just_D08_,
		.D16_=BitC_Just_D16_,
		.D32_=BitC_Just_D32_,
		.D64_=BitC_Just_D64_
	},
	.Endian=
	{
		.D08_=BitC_Endian_D08_,
		.D16_=BitC_Endian_D16_,
		.D32_=BitC_Endian_D32_,
		.D64_=BitC_Endian_D64_
	},
	.Caster=
	{
		.D08=
		{
			.D08_=MemC_Func_Casting_(general,BitC_Copy_D08_,DATA_08 *_R_,data_08 *_R_,ADDRESS),
			.D16_=BitC_Caster_D08_D16_,
			.D32_=BitC_Caster_D08_D32_,
			.D64_=BitC_Caster_D08_D64_,
			.I08_=BitC_Caster_D08_I08_,
			.I16_=MemC_Func_Casting_(general,BitC_Caster_D08_D16_,DATA_08 *_R_,inte_16 *_R_,ADDRESS),
			.I32_=MemC_Func_Casting_(general,BitC_Caster_D08_D32_,DATA_08 *_R_,inte_32 *_R_,ADDRESS),
			.I64_=MemC_Func_Casting_(general,BitC_Caster_D08_D64_,DATA_08 *_R_,inte_64 *_R_,ADDRESS),
			.R32_=BitC_Caster_D08_R32_,
			.R64_=BitC_Caster_D08_R64_
		},
		.D16=
		{
			.D08_=BitC_Caster_D16_D08_,
			.D16_=MemC_Func_Casting_(general,BitC_Copy_D16_,DATA_16 *_R_,data_16 *_R_,ADDRESS),
			.D32_=BitC_Caster_D16_D32_,
			.D64_=BitC_Caster_D16_D64_,
			.I08_=BitC_Caster_D16_I08_,
			.I16_=BitC_Caster_D16_I16_,
			.I32_=MemC_Func_Casting_(general,BitC_Caster_D16_D32_,DATA_16 *_R_,inte_32 *_R_,ADDRESS),
			.I64_=MemC_Func_Casting_(general,BitC_Caster_D16_D64_,DATA_16 *_R_,inte_64 *_R_,ADDRESS),
			.R32_=BitC_Caster_D16_R32_,
			.R64_=BitC_Caster_D16_R64_
		},
		.D32=
		{
			.D08_=BitC_Caster_D32_D08_,
			.D16_=BitC_Caster_D32_D16_,
			.D32_=MemC_Func_Casting_(general,BitC_Copy_D32_,DATA_32 *_R_,data_32 *_R_,ADDRESS),
			.D64_=BitC_Caster_D32_D64_,
			.I08_=BitC_Caster_D32_I08_,
			.I16_=BitC_Caster_D32_I16_,
			.I32_=BitC_Caster_D32_I32_,
			.I64_=MemC_Func_Casting_(general,BitC_Caster_D32_D64_,DATA_32 *_R_,inte_64 *_R_,ADDRESS),
			.R32_=BitC_Caster_D32_R32_,
			.R64_=BitC_Caster_D32_R64_
		},
		.D64=
		{
			.D08_=BitC_Caster_D64_D08_,
			.D16_=BitC_Caster_D64_D16_,
			.D32_=BitC_Caster_D64_D32_,
			.D64_=MemC_Func_Casting_(general,BitC_Copy_D64_,DATA_64 *_R_,data_64 *_R_,ADDRESS),
			.I08_=BitC_Caster_D64_I08_,
			.I16_=BitC_Caster_D64_I16_,
			.I32_=BitC_Caster_D64_I32_,
			.I64_=BitC_Caster_D64_I64_,
			.R32_=BitC_Caster_D64_R32_,
			.R64_=BitC_Caster_D64_R64_
		},
		.I08=
		{
			.D08_=BitC_Caster_I08_D08_,
			.D16_=BitC_Caster_I08_D16_,
			.D32_=BitC_Caster_I08_D32_,
			.D64_=BitC_Caster_I08_D64_,
			.I08_=MemC_Func_Casting_(general,BitC_Copy_D08_,INTE_08 *_R_,inte_08 *_R_,ADDRESS),
			.I16_=BitC_Caster_I08_I16_,
			.I32_=BitC_Caster_I08_I32_,
			.I64_=BitC_Caster_I08_I64_,
			.R32_=BitC_Caster_I08_R32_,
			.R64_=BitC_Caster_I08_R64_
		},
		.I16=
		{
			.D08_=BitC_Caster_I16_D08_,
			.D16_=BitC_Caster_I16_D16_,
			.D32_=BitC_Caster_I16_D32_,
			.D64_=BitC_Caster_I16_D64_,
			.I08_=BitC_Caster_I16_I08_,
			.I16_=MemC_Func_Casting_(general,BitC_Copy_D16_,INTE_16 *_R_,inte_16 *_R_,ADDRESS),
			.I32_=BitC_Caster_I16_I32_,
			.I64_=BitC_Caster_I16_I64_,
			.R32_=BitC_Caster_I16_R32_,
			.R64_=BitC_Caster_I16_R64_
		},
		.I32=
		{
			.D08_=BitC_Caster_I32_D08_,
			.D16_=BitC_Caster_I32_D16_,
			.D32_=BitC_Caster_I32_D32_,
			.D64_=BitC_Caster_I32_D64_,
			.I08_=BitC_Caster_I32_I08_,
			.I16_=BitC_Caster_I32_I16_,
			.I32_=MemC_Func_Casting_(general,BitC_Copy_D32_,INTE_32 *_R_,inte_32 *_R_,ADDRESS),
			.I64_=BitC_Caster_I32_I64_,
			.R32_=BitC_Caster_I32_R32_,
			.R64_=BitC_Caster_I32_R64_
		},
		.I64=
		{
			.D08_=BitC_Caster_I64_D08_,
			.D16_=BitC_Caster_I64_D16_,
			.D32_=BitC_Caster_I64_D32_,
			.D64_=BitC_Caster_I64_D64_,
			.I08_=BitC_Caster_I64_I08_,
			.I16_=BitC_Caster_I64_I16_,
			.I32_=BitC_Caster_I64_I32_,
			.I64_=MemC_Func_Casting_(general,BitC_Copy_D64_,INTE_64 *_R_,inte_64 *_R_,ADDRESS),
			.R32_=BitC_Caster_I64_R32_,
			.R64_=BitC_Caster_I64_R64_
		},
		.R32=
		{
			.D08_=BitC_Caster_R32_D08_,
			.D16_=BitC_Caster_R32_D16_,
			.D32_=BitC_Caster_R32_D32_,
			.D64_=BitC_Caster_R32_D64_,
			.I08_=BitC_Caster_R32_I08_,
			.I16_=BitC_Caster_R32_I16_,
			.I32_=BitC_Caster_R32_I32_,
			.I64_=BitC_Caster_R32_I64_,
			.R32_=MemC_Func_Casting_(general,BitC_Copy_D32_,REAL_32 *_R_,real_32 *_R_,ADDRESS),
			.R64_=BitC_Caster_R32_R64_
		},
		.R64=
		{
			.D08_=BitC_Caster_R64_D08_,
			.D16_=BitC_Caster_R64_D16_,
			.D32_=BitC_Caster_R64_D32_,
			.D64_=BitC_Caster_R64_D64_,
			.I08_=BitC_Caster_R64_I08_,
			.I16_=BitC_Caster_R64_I16_,
			.I32_=BitC_Caster_R64_I32_,
			.I64_=BitC_Caster_R64_I64_,
			.R32_=BitC_Caster_R64_R32_,
			.R64_=MemC_Func_Casting_(general,BitC_Copy_D64_,REAL_64 *_R_,real_64 *_R_,ADDRESS)
		}
	},
	.BO=
	{
		.N_1=
		{
			.D08_=BitC_BO_N_1_D08_,
			.D16_=BitC_BO_N_1_D16_,
			.D32_=BitC_BO_N_1_D32_,
			.D64_=BitC_BO_N_1_D64_
		},
		.S_1=
		{
			.D08_=BitC_BO_S_1_D08_,
			.D16_=BitC_BO_S_1_D16_,
			.D32_=BitC_BO_S_1_D32_,
			.D64_=BitC_BO_S_1_D64_,
			.I08_=BitC_BO_S_1_I08_,
			.I16_=BitC_BO_S_1_I16_,
			.I32_=BitC_BO_S_1_I32_,
			.I64_=BitC_BO_S_1_I64_
		},
		.A_1=
		{
			.D08_=BitC_BO_A_1_D08_,
			.D16_=BitC_BO_A_1_D16_,
			.D32_=BitC_BO_A_1_D32_,
			.D64_=BitC_BO_A_1_D64_
		},
		.A_2=
		{
			.D08_=BitC_BO_A_2_D08_,
			.D16_=BitC_BO_A_2_D16_,
			.D32_=BitC_BO_A_2_D32_,
			.D64_=BitC_BO_A_2_D64_
		},
		.O_1=
		{
			.D08_=BitC_BO_O_1_D08_,
			.D16_=BitC_BO_O_1_D16_,
			.D32_=BitC_BO_O_1_D32_,
			.D64_=BitC_BO_O_1_D64_
		},
		.O_2=
		{
			.D08_=BitC_BO_O_2_D08_,
			.D16_=BitC_BO_O_2_D16_,
			.D32_=BitC_BO_O_2_D32_,
			.D64_=BitC_BO_O_2_D64_
		},
		.X_1=
		{
			.D08_=BitC_BO_X_1_D08_,
			.D16_=BitC_BO_X_1_D16_,
			.D32_=BitC_BO_X_1_D32_,
			.D64_=BitC_BO_X_1_D64_
		},
		.X_2=
		{
			.D08_=BitC_BO_X_2_D08_,
			.D16_=BitC_BO_X_2_D16_,
			.D32_=BitC_BO_X_2_D32_,
			.D64_=BitC_BO_X_2_D64_
		}
	},
	.RO=
	{
		.Expand=
		{
			.D08_=BitC_Expand_D08_,
			.D16_=BitC_Expand_D16_,
			.D32_=BitC_Expand_D32_,
			.D64_=BitC_Expand_D64_
		},
		.Shrink=
		{
			.D08_=BitC_Shrink_D08_,
			.D16_=BitC_Shrink_D16_,
			.D32_=BitC_Shrink_D32_,
			.D64_=BitC_Shrink_D64_
		},
		.E_1=
		{
			.D08_=BitC_RO_E_1_D08_,
			.D16_=BitC_RO_E_1_D16_,
			.D32_=BitC_RO_E_1_D32_,
			.D64_=BitC_RO_E_1_D64_
		},
		.E_2=
		{
			.D08_=BitC_RO_E_2_D08_,
			.D16_=BitC_RO_E_2_D16_,
			.D32_=BitC_RO_E_2_D32_,
			.D64_=BitC_RO_E_2_D64_
		},
		.N_1=
		{
			.D08_=BitC_RO_N_1_D08_,
			.D16_=BitC_RO_N_1_D16_,
			.D32_=BitC_RO_N_1_D32_,
			.D64_=BitC_RO_N_1_D64_
		},
		.N_2=
		{
			.D08_=BitC_RO_N_2_D08_,
			.D16_=BitC_RO_N_2_D16_,
			.D32_=BitC_RO_N_2_D32_,
			.D64_=BitC_RO_N_2_D64_
		},
		.G_1=
		{
			.D08_=BitC_RO_G_1_D08_,
			.D16_=BitC_RO_G_1_D16_,
			.D32_=BitC_RO_G_1_D32_,
			.D64_=BitC_RO_G_1_D64_,
			.I08_=BitC_RO_G_1_I08_,
			.I16_=BitC_RO_G_1_I16_,
			.I32_=BitC_RO_G_1_I32_,
			.I64_=BitC_RO_G_1_I64_,
			.R32_=BitC_RO_G_1_R32_,
			.R64_=BitC_RO_G_1_R64_
		},
		.G_2=
		{
			.D08_=BitC_RO_G_2_D08_,
			.D16_=BitC_RO_G_2_D16_,
			.D32_=BitC_RO_G_2_D32_,
			.D64_=BitC_RO_G_2_D64_,
			.I08_=BitC_RO_G_2_I08_,
			.I16_=BitC_RO_G_2_I16_,
			.I32_=BitC_RO_G_2_I32_,
			.I64_=BitC_RO_G_2_I64_,
			.R32_=BitC_RO_G_2_R32_,
			.R64_=BitC_RO_G_2_R64_
		},
		.L_1=
		{
			.D08_=BitC_RO_L_1_D08_,
			.D16_=BitC_RO_L_1_D16_,
			.D32_=BitC_RO_L_1_D32_,
			.D64_=BitC_RO_L_1_D64_,
			.I08_=BitC_RO_L_1_I08_,
			.I16_=BitC_RO_L_1_I16_,
			.I32_=BitC_RO_L_1_I32_,
			.I64_=BitC_RO_L_1_I64_,
			.R32_=BitC_RO_L_1_R32_,
			.R64_=BitC_RO_L_1_R64_
		},
		.L_2=
		{
			.D08_=BitC_RO_L_2_D08_,
			.D16_=BitC_RO_L_2_D16_,
			.D32_=BitC_RO_L_2_D32_,
			.D64_=BitC_RO_L_2_D64_,
			.I08_=BitC_RO_L_2_I08_,
			.I16_=BitC_RO_L_2_I16_,
			.I32_=BitC_RO_L_2_I32_,
			.I64_=BitC_RO_L_2_I64_,
			.R64_=BitC_RO_L_2_R64_,
			.R32_=BitC_RO_L_2_R32_
		}
	},
	.BP=
	{
		.Assign=
		{
			.S_=BitC_BP_Assign_S_,
			.U_=BitC_BP_Assign_U_
		},
		.Jumper=
		{
			.S_=BitC_BP_Jumper_S_,
			.U_=BitC_BP_Jumper_U_
		},
		.Reader_=BitC_BP_Reader_,
		.Writer_=BitC_BP_Writer_
	}
};
BITCASE *BitC_(general) { return &BitC; }
#ifdef __OPENCL_H
BITC_CL BitCL=
{
	.Ready=
	{
		.T08_=BitC_CL_Build_T08_,
		.T16_=BitC_CL_Build_T16_
	},
	.Create=
	{
		.T08_=BitC_CL_Create_T08_,
		.T16_=BitC_CL_Create_T16_
	},
	.Pin_=_BitC_CL_Pin_Cast_,
	.Endian_=BitC_CL_Endian_,
	.Reform_=BitC_CL_Reform_,
	.Caster_=BitC_CL_Caster_,
	.BO=
	{
		.N_1_=BitC_CL_BO_N_1_,
		.S_1_=BitC_CL_BO_S_1_,
		.A_1_=BitC_CL_BO_A_1_,
		.A_2_=BitC_CL_BO_A_2_,
		.O_1_=BitC_CL_BO_O_1_,
		.O_2_=BitC_CL_BO_O_2_,
		.X_1_=BitC_CL_BO_X_1_,
		.X_2_=BitC_CL_BO_X_2_
	},
	.RO=
	{
		.E_1_=BitC_CL_RO_E_1_,
		.E_2_=BitC_CL_RO_E_2_,
		.N_1_=BitC_CL_RO_N_1_,
		.N_2_=BitC_CL_RO_N_2_,
		.G_1_=BitC_CL_RO_G_1_,
		.G_2_=BitC_CL_RO_G_2_,
		.L_1_=BitC_CL_RO_L_1_,
		.L_2_=BitC_CL_RO_L_2_
	}
};
BITC_CL *BitCL_(general) { return &BitCL; }
#else
GENERAL *BitCL_(general) { return NULL; }
#endif
#endif
