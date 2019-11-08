﻿#include "timclip.h"

#include <limits.h>
#include <math.h>

#if(Fold_(Static Assertions))
static_assert(((UINT32_MAX)/(UINT32_C(1000)))>(CLOCKS_PER_SEC),"UINT32_MAX < 1000*CLOCKS_PER_SEC");
static_assert(sizeof(timc_tt)==sizeof(data_32),"sizeof(timc_tt) != sizeof(data_32)");
#endif

#if(Fold_(Definition:Internals))
#if defined(__STDC__)&&defined(__STDC_VERSION__)
#if((__STDC__)&&((__STDC_VERSION__)>=(201710L)))
#define _TimC_Generic_
#endif
#endif

#define _TIMC_ static

_TIMC_ BYTE_08 IdiomVersion[16]="Date:2019.11.08";
_TIMC_ REAL_32 ConstClocks[2]={[0]=(real_32)(CLOCKS_PER_SEC),[1]=1.0F/((real_32)(CLOCKS_PER_SEC))};
#endif

#if(Fold_(Definition:Advanced Type Functions))
#if(Fold_(Part:Common))
struct _timc_vc { general *Thing;address Nums; };
MemC_Type_Declare_(struct,timc_vc,TIMC_VC);

_TIMC_ general TimC_Delete_(general *_PL_ _R_ Object) { MemC_Deloc_(*Object);return; }
static logical _TimC_Check_(TIMC_VC _PL_ _R_ VC,ADDRESS Select)
{
	if(VC)
		if(Select<(VC->Nums))
			return 1;
		else;
	else;

	return 0;
}
#endif

#if(Fold_(Part:TimC_SW))
_TIMC_ timc_sw *TimC_SW_Create_(ADDRESS Timers)
{
	timc_sw *_R_ SW;

	if(Timers)
	{
		ADDRESS Temp=MemC.Size.Mul_(Timers,sizeof(timc_te));

		if(Temp)
		{
			SW=MemC.Alloc.Byte_(MemC.Size.Add_(Temp,sizeof(timc_sw)));
			if(SW)
			{
				Acs_(timc_te*,SW->Timer)=MemC_Clear_1D_((timc_te*)(SW+1),Timers);
				Acs_(address,SW->Nums)=Timers;
			}
			else;
		}
		else
			SW=NULL;
	}
	else
	{
		SW=MemC_Alloc_Unit_(timc_sw);
		if(SW)
			MemC_Clear_Unit_(SW);
		else;
	}

	return SW;
}
_TIMC_ address TimC_SW_Size_(TIMC_SW _PL_ _R_ SW)
{
	return ((SW)?(sizeof(timc_sw)+MemC_Size_(timc_te,SW->Nums)):(0));
}

_TIMC_ timc_sf TimC_SW_Reset_All_(TIMC_SW _PL_ _R_ SW)
{
	if(SW)
	{
		if(SW->Nums)
			MemC_Clear_1D_(SW->Timer,SW->Nums);
		else;

		return TimCStateStopped;
	}
	else
		return TimCStateUnknown;
}
_TIMC_ timc_sf TimC_SW_Stop_All_(TIMC_SW _PL_ _R_ SW)
{
	if(SW)
	{
		for(timc_te *_R_ Ptr=SW->Timer,_PL_ End=Ptr+(SW->Nums);Ptr<End;Ptr++)
			switch(Ptr->State)
			{
			default:
				Ptr->Sum=0;
				Ptr->State=TimCStateStopped;
				Ptr->Count=0;
				break;
			case TimCStateRunning:
				Ptr->Sum+=clock()-(Ptr->Mark);
				Ptr->State=TimCStateStopped;
			case TimCStateStopped:;
			}

		return TimCStateStopped;
	}
	else
		return TimCStateUnknown;
}

_TIMC_ timc_sf TimC_SW_Reset_(TIMC_SW _PL_ _R_ SW,ADDRESS Select)
{
	if(_TimC_Check_((TIMC_VC*)SW,Select))
	{
		MemC_Clear_Unit_(SW->Timer+Select);

		return TimCStateStopped;
	}
	else
		return TimCStateUnknown;
}
_TIMC_ timc_sf TimC_SW_Toggle_(TIMC_SW _PL_ _R_ SW,ADDRESS Select)
{
	if(_TimC_Check_((TIMC_VC*)SW,Select))
	{
		timc_te _PL_ _R_ Timer=SW->Timer+Select;

		switch(Timer->State)
		{
		case TimCStateStopped:
			if(Timer->Count<INT_MAX)
			{
				Timer->Count++;
				Timer->State=TimCStateRunning;
				Timer->Mark=clock();
				break;
			}
			else
				goto UNKNOWN;
		case TimCStateRunning:
			Timer->Sum+=clock()-(Timer->Mark);
			if(Timer->Sum<0)
				goto UNKNOWN;
			else
			{
				Timer->State=TimCStateStopped;
				break;
			}
UNKNOWN:
		default:
			Timer->State=TimCStateUnknown;
		}

		return (Timer->State);
	}
	else
		return TimCStateUnknown;
}

_TIMC_ timc_sf TimC_SW_Read_State_(TIMC_SW _PL_ _R_ SW,ADDRESS Select)
{
	if(_TimC_Check_((TIMC_VC*)SW,Select))
		return (SW->Timer[Select].State);
	else
		return TimCStateUnknown;
}
_TIMC_ integer TimC_SW_Read_Count_(TIMC_SW _PL_ _R_ SW,ADDRESS Select)
{
	if(_TimC_Check_((TIMC_VC*)SW,Select))
		return (SW->Timer[Select].Count);
	else
		return -1;
}

static clock_t _TimC_SW_Read_Stop_(TIMC_TE _PL_ _R_ Timer)
{
	return (Timer->Sum);
}
static clock_t _TimC_SW_Read_Run_(TIMC_TE _PL_ _R_ Timer)
{
	return (clock()-(Timer->Mark)+(Timer->Sum));
}

static real_32 _TimC_SW_Cast_R32_(const clock_t Time)
{
	return ((ConstClocks[1])*(real_32)(Time));
}
_TIMC_ real_32 TimC_SW_Read_Sum_R32_(TIMC_SW _PL_ _R_ SW,ADDRESS Select)
{
	if(_TimC_Check_((TIMC_VC*)SW,Select))
	{
		TIMC_TE _PL_ _R_ Timer=SW->Timer+Select;

		switch(Timer->State)
		{
		case TimCStateStopped:
			return _TimC_SW_Cast_R32_(_TimC_SW_Read_Stop_(Timer));
		case TimCStateRunning:
			return _TimC_SW_Cast_R32_(_TimC_SW_Read_Run_(Timer));
		default:;
		}
	}
	else;

	return -1.0F;
}
_TIMC_ real_32 TimC_SW_Read_Mean_R32_(TIMC_SW _PL_ _R_ SW,ADDRESS Select)
{
	if(_TimC_Check_((TIMC_VC*)SW,Select))
	{
		TIMC_TE _PL_ _R_ Timer=SW->Timer+Select;

		switch(Timer->State)
		{
		case TimCStateStopped:
			return ((Timer->Count)?(_TimC_SW_Cast_R32_(_TimC_SW_Read_Stop_(Timer))/((real_32)(Timer->Count))):(0.0F));
		case TimCStateRunning:
			return ((Timer->Count)?(_TimC_SW_Cast_R32_(_TimC_SW_Read_Run_(Timer))/((real_32)(Timer->Count))):(-1.0F));
		default:;
		}
	}
	else;

	return -1.0F;
}

static timc_tt _TimC_SW_Cast_Tag_(clock_t Time)
{
	timc_tt Tag={0};

	{
		const clock_t Zero=0;
#ifdef _TimC_Generic_
		BITCLIP Peek={.C.G=&Time},Mask={.C.G=&(inte_64) { 0 }};

		_Generic
		(
			Time,
			data_08:(Tag.Sign=0),
			data_16:(Tag.Sign=0),
			data_32:(Tag.Sign=0),
			data_64:(Tag.Sign=0),
			inte_08:((Mask.V.I08[0]=Peek.C.I08[0]>>7),(Peek.V.I08[0]+=Mask.C.I08[0]),(Peek.V.I08[0]^=Mask.C.I08[0]),(Tag.Sign=(data_32)(Mask.C.I08[0]))),
			inte_16:((Mask.V.I16[0]=Peek.C.I16[0]>>15),(Peek.V.I16[0]+=Mask.C.I16[0]),(Peek.V.I16[0]^=Mask.C.I16[0]),(Tag.Sign=(data_32)(Mask.C.I16[0]))),
			inte_32:((Mask.V.I32[0]=Peek.C.I32[0]>>31),(Peek.V.I32[0]+=Mask.C.I32[0]),(Peek.V.I32[0]^=Mask.C.I32[0]),(Tag.Sign=(data_32)(Mask.C.I32[0]))),
			inte_64:((Mask.V.I64[0]=Peek.C.I64[0]>>63),(Peek.V.I64[0]+=Mask.C.I64[0]),(Peek.V.I64[0]^=Mask.C.I64[0]),(Tag.Sign=(data_32)(Mask.C.I64[0]))),
			real_32:(Tag.Sign=(data_32)(Peek.C.D32[0]>>31),Peek.V.D32[0]&=0x7FFFFFFF),
			real_64:(Tag.Sign=(data_32)(Peek.C.D64[0]>>63),Peek.V.D64[0]&=0x7FFFFFFFFFFFFFFF),
			default:
#endif
				((Time<Zero)?((Time=Zero-Time),(Tag.Sign=1)):((Time=Zero+Time),(Tag.Sign=0)))
#ifdef _TimC_Generic_
		)
#endif
			;
	}
	{
		DATA_32 Days=7,Hours=24,Minutes=60,Seconds=60,Milliseconds=1000,Clocks=(DATA_32)(CLOCKS_PER_SEC);
		data_32 Cast=(data_32)(Time);

		Tag.Milliseconds=(Milliseconds*(Cast%Clocks))/Clocks;
		Tag.Seconds=(Cast/=Clocks)%Seconds;
		Tag.Minutes=(Cast/=Seconds)%Minutes;
		Tag.Hours=(Cast/=Minutes)%Hours;
		Tag.Days=(Cast/=Hours)%Days;
		Tag.Overflow=(Cast=0-Cast)>>31;
	}

	return Tag;
}
_TIMC_ timc_tt TimC_SW_Read_Sum_Tag_(TIMC_SW _PL_ _R_ SW,ADDRESS Select)
{
	DATA_32 Fail=0xFFFFFFFF;

	if(_TimC_Check_((TIMC_VC*)SW,Select))
	{
		TIMC_TE _PL_ _R_ Timer=SW->Timer+Select;

		switch(Timer->State)
		{
		case TimCStateStopped:
			return _TimC_SW_Cast_Tag_(_TimC_SW_Read_Stop_(Timer));
		case TimCStateRunning:
			return _TimC_SW_Cast_Tag_(_TimC_SW_Read_Run_(Timer));
		default:;
		}
	}
	else;

	return Acs_(TIMC_TT,Fail);
}
_TIMC_ timc_tt TimC_SW_Read_Mean_Tag_(TIMC_SW _PL_ _R_ SW,ADDRESS Select)
{
	DATA_32 Fail=0xFFFFFFFF;

	if(_TimC_Check_((TIMC_VC*)SW,Select))
	{
		TIMC_TE _PL_ _R_ Timer=SW->Timer+Select;
		DATA_32 Zero=0x00000000;

		switch(Timer->State)
		{
		case TimCStateStopped:
			return ((Timer->Count)?(_TimC_SW_Cast_Tag_(_TimC_SW_Read_Stop_(Timer)/(Timer->Count))):(Acs_(TIMC_TT,Zero)));
		case TimCStateRunning:
			return ((Timer->Count)?(_TimC_SW_Cast_Tag_(_TimC_SW_Read_Run_(Timer)/(Timer->Count))):(Acs_(TIMC_TT,Fail)));
		default:;
		}
	}
	else;

	return Acs_(TIMC_TT,Fail);
}
#endif

#if(Fold_(Part:TimC_RG))
static general _TimC_RG_Setup_(data_64 *_R_ Ptr,ADDRESS Nums)
{
	for(data_64 Temp=(data_64)time(NULL),_PL_ End=Ptr+Nums;Ptr<End;Ptr++,Temp++)
		*Ptr=Temp;

	return;
}
_TIMC_ timc_rg *TimC_RG_Create_(ADDRESS States)
{
	timc_rg *_R_ RG=NULL;

	if(States)
	{
		MemC_Temp_(ADDRESS,Size=MemC.Size.Mul_(States,sizeof(data_64)))
			RG=(Size)?(MemC.Alloc.Byte_(MemC.Size.Add_(Size,sizeof(timc_rg)))):(NULL);

		if(RG)
		{
			Acs_(address,RG->Nums)=States;
			Acs_(data_64*,RG->State)=(data_64*)(RG+1);

			_TimC_RG_Setup_(RG->State,States);
		}
		else;
	}
	else
	{
		RG=MemC_Alloc_Unit_(timc_rg);
		if(RG)
			MemC_Clear_Unit_(RG);
		else;
	}

	return RG;
}
_TIMC_ address TimC_RG_Size_(TIMC_RG _PL_ _R_ RG)
{
	return ((RG)?(sizeof(timc_rg)+MemC_Size_(data_64,RG->Nums)):(0));
}
_TIMC_ logical TimC_RG_Reset_(TIMC_RG _PL_ _R_ RG)
{
	return ((RG)?(_TimC_RG_Setup_(RG->State,RG->Nums),1):(0));
}

static data_32 _TimC_RG_Rand_(BITCLIP State)
{
	DATA_64 Temp=(State.C.D64[0])>>32;

	State.V.D64[0]&=0x00000000FFFFFFFF;
	State.V.D64[0]*=0x00000000FFFEB81B;
	State.V.D64[0]+=Temp;

	return ((State.C.D32[0])^(State.C.D32[1]));
}
_TIMC_ logical TimC_RG_Byte_(TIMC_RG _PL_ _R_ RG,ADDRESS Select,general _PL_ _R_ Array,ADDRESS Length)
{
	if(_TimC_Check_((TIMC_VC*)RG,Select))
	{
		ADDRESS Batch=Length>>2;
		BITCLIP State={.V.D64=RG->State+Select};
		DATA_32 *End=Array;
		data_32 *_R_ Ptr=Array;

		for(End+=(Batch&(BitC.Const.Mask.Safe[3]));Ptr<End;Ptr+=8)
		{
			Ptr[0]=_TimC_RG_Rand_(State);
			Ptr[1]=_TimC_RG_Rand_(State);
			Ptr[2]=_TimC_RG_Rand_(State);
			Ptr[3]=_TimC_RG_Rand_(State);
			Ptr[4]=_TimC_RG_Rand_(State);
			Ptr[5]=_TimC_RG_Rand_(State);
			Ptr[6]=_TimC_RG_Rand_(State);
			Ptr[7]=_TimC_RG_Rand_(State);
		}
		for(End+=(Batch&(BitC.Const.Mask.Rest[3]));Ptr<End;Ptr++)
			Ptr[0]=_TimC_RG_Rand_(State);

		MemC_Temp_(ADDRESS,Rest=Length&(BitC.Const.Mask.Rest[2]))
			if(Rest)
			{
				DATA_32 Last=_TimC_RG_Rand_(State);

				if(MemC_Copy_Byte_(&Last,Ptr,Rest));
				else
					return 0;
			}
			else;

		return 1;
	}
	else
		return 0;
}
static data_32 _TimC_RG_Cage_I32_(data_64 Value,DATA_64 Add,DATA_64 Mul)
{
	Value*=Mul;
	Value+=Add;
	Value>>=32;

	return ((data_32)Value);
}
_TIMC_ logical TimC_RG_Uni_I32_(TIMC_RG _PL_ _R_ RG,ADDRESS Select,data_32 _PL_ _R_ Array,ADDRESS Length,INTE_32 Min,INTE_32 Max)
{
	if(TimC_RG_Byte_(RG,Select,Array,MemC_Size_(data_32,Length)))
	{
		inte_64 Add,Mul;
		DATA_32 *End=Array;
		data_32 *_R_ Ptr=Array;

		if(Min<Max)
		{
			Add=(inte_64)Min;
			Mul=(inte_64)Max;
		}
		else
		{
			Add=(inte_64)Max;
			Mul=(inte_64)Min;
		}
		{
			Mul-=Add;
			Mul++;
			Add<<=32;
		}
		for(End+=(Length&(BitC.Const.Mask.Safe[3]));Ptr<End;Ptr+=8)
		{
			Ptr[0]=_TimC_RG_Cage_I32_((data_64)(Ptr[0]),Add,Mul);
			Ptr[1]=_TimC_RG_Cage_I32_((data_64)(Ptr[1]),Add,Mul);
			Ptr[2]=_TimC_RG_Cage_I32_((data_64)(Ptr[2]),Add,Mul);
			Ptr[3]=_TimC_RG_Cage_I32_((data_64)(Ptr[3]),Add,Mul);
			Ptr[4]=_TimC_RG_Cage_I32_((data_64)(Ptr[4]),Add,Mul);
			Ptr[5]=_TimC_RG_Cage_I32_((data_64)(Ptr[5]),Add,Mul);
			Ptr[6]=_TimC_RG_Cage_I32_((data_64)(Ptr[6]),Add,Mul);
			Ptr[7]=_TimC_RG_Cage_I32_((data_64)(Ptr[7]),Add,Mul);
		}
		for(End+=(Length&(BitC.Const.Mask.Rest[3]));Ptr<End;Ptr++)
			Ptr[0]=_TimC_RG_Cage_I32_((data_64)(Ptr[0]),Add,Mul);

		return 1;
	}
	else
		return 0;
}

static real_32 _TimC_RG_Cage_R32_(real_32 Value,REAL_32 Add,REAL_32 Mul)
{
	Value*=Mul;
	Value+=Add;

	return Value;
}
_TIMC_ logical TimC_RG_Uni_R32_(TIMC_RG _PL_ _R_ RG,ADDRESS Select,real_32 _PL_ _R_ Array,ADDRESS Length,REAL_32 Min,REAL_32 Max)
{
	if(TimC_RG_Byte_(RG,Select,Array,MemC_Size_(real_32,Length)))
	{
		DATA_32 Ref=0x2F800000;
		REAL_32 Scale=Acs_(real_32,Ref)*(Max-Min);
		bitclip Ptr={.V.R32=Array},End=Ptr;

		for(End.C.R32+=(Length&(BitC.Const.Mask.Safe[3]));Ptr.C.R32<End.C.R32;Ptr.C.R32+=8)
		{
			Ptr.V.R32[0]=_TimC_RG_Cage_R32_((real_32)(Ptr.C.D32[0]),Min,Scale);
			Ptr.V.R32[1]=_TimC_RG_Cage_R32_((real_32)(Ptr.C.D32[1]),Min,Scale);
			Ptr.V.R32[2]=_TimC_RG_Cage_R32_((real_32)(Ptr.C.D32[2]),Min,Scale);
			Ptr.V.R32[3]=_TimC_RG_Cage_R32_((real_32)(Ptr.C.D32[3]),Min,Scale);
			Ptr.V.R32[4]=_TimC_RG_Cage_R32_((real_32)(Ptr.C.D32[4]),Min,Scale);
			Ptr.V.R32[5]=_TimC_RG_Cage_R32_((real_32)(Ptr.C.D32[5]),Min,Scale);
			Ptr.V.R32[6]=_TimC_RG_Cage_R32_((real_32)(Ptr.C.D32[6]),Min,Scale);
			Ptr.V.R32[7]=_TimC_RG_Cage_R32_((real_32)(Ptr.C.D32[7]),Min,Scale);
		}
		for(End.C.R32+=(Length&(BitC.Const.Mask.Rest[3]));Ptr.C.R32<End.C.R32;Ptr.C.R32++)
			Ptr.V.R32[0]=_TimC_RG_Cage_R32_((real_32)(Ptr.C.D32[0]),Min,Scale);

		return 1;
	}
	else
		return 0;
}
static real_64 _TimC_RG_Cage_R64_(real_64 Value,REAL_64 Add,REAL_64 Mul)
{
	Value*=Mul;
	Value+=Add;

	return Value;
}
_TIMC_ logical TimC_RG_Uni_R64_(TIMC_RG _PL_ _R_ RG,ADDRESS Select,real_64 _PL_ _R_ Array,ADDRESS Length,REAL_64 Min,REAL_64 Max)
{
	if(TimC_RG_Byte_(RG,Select,Array,MemC_Size_(real_64,Length)))
	{
		DATA_64 Ref=0x3BF0000000000000;
		REAL_64 Scale=Acs_(real_64,Ref)*(Max-Min);
		bitclip Ptr={.V.R64=Array},End=Ptr;

		for(End.C.R64+=(Length&(BitC.Const.Mask.Safe[3]));Ptr.C.R64<End.C.R64;Ptr.C.R64+=8)
		{
			Ptr.V.R64[0]=_TimC_RG_Cage_R64_((real_64)(Ptr.C.D64[0]),Min,Scale);
			Ptr.V.R64[1]=_TimC_RG_Cage_R64_((real_64)(Ptr.C.D64[1]),Min,Scale);
			Ptr.V.R64[2]=_TimC_RG_Cage_R64_((real_64)(Ptr.C.D64[2]),Min,Scale);
			Ptr.V.R64[3]=_TimC_RG_Cage_R64_((real_64)(Ptr.C.D64[3]),Min,Scale);
			Ptr.V.R64[4]=_TimC_RG_Cage_R64_((real_64)(Ptr.C.D64[4]),Min,Scale);
			Ptr.V.R64[5]=_TimC_RG_Cage_R64_((real_64)(Ptr.C.D64[5]),Min,Scale);
			Ptr.V.R64[6]=_TimC_RG_Cage_R64_((real_64)(Ptr.C.D64[6]),Min,Scale);
			Ptr.V.R64[7]=_TimC_RG_Cage_R64_((real_64)(Ptr.C.D64[7]),Min,Scale);
		}
		for(End.C.R64+=(Length&(BitC.Const.Mask.Rest[3]));Ptr.C.R64<End.C.R64;Ptr.C.R64++)
			Ptr.V.R64[0]=_TimC_RG_Cage_R64_((real_64)(Ptr.C.D64[0]),Min,Scale);

		return 1;
	}
	else
		return 0;
}

_TIMC_ logical TimC_RG_Gau_R32_(TIMC_RG _PL_ _R_ RG,ADDRESS Select,real_32 _PL_ _R_ Array,ADDRESS Length,REAL_32 Mean,REAL_32 Deviation)
{
	if(TimC_RG_Byte_(RG,Select,Array,MemC_Size_(real_32,Length)))
	{
		const union { DATA_32 Ref;REAL_32 U; }Range={.Ref=0x2F800000};
		const struct { REAL_32 V,W; }Scale={.V=(+2.0F)*(BitC.Const.Pi.R32[0])*(Range.U),.W=(-2.0F)*(Deviation*Deviation)};
		BITCLIP Temp={.V.D32=(data_32[2]) { 0 }};
		bitclip Ptr={.V.R32=Array},End=Ptr;

		for(End.C.R32+=(Length&(BitC.Const.Mask.Safe[1]));Ptr.C.R32<End.C.R32;Ptr.C.R32+=2)
		{
			Temp.V.D32[0]=0x00000001|Ptr.C.D32[0];
			Temp.V.D32[1]=0xFFFFFFFE&Ptr.C.D32[1];

			Temp.V.R32[0]=Range.U*((real_32)(Temp.C.D32[0]));
			Temp.V.R32[1]=Scale.V*((real_32)(Temp.C.D32[1]));

			Temp.V.R32[0]=logf(Temp.C.R32[0]);
			Temp.V.R32[0]*=Scale.W;
			Temp.V.R32[0]=sqrtf(Temp.C.R32[0]);

			Ptr.V.R32[0]=Temp.C.R32[0]*cosf(Temp.C.R32[1]);
			Ptr.V.R32[1]=Temp.C.R32[0]*sinf(Temp.C.R32[1]);

			Ptr.V.R32[0]+=Mean;
			Ptr.V.R32[1]+=Mean;
		}
		if(Length&(BitC.Const.Mask.Rest[1]))
		{
			BITCLIP State={.V.G=RG->State+Select};

			Temp.V.D32[0]=0x00000001|Ptr.C.D32[0];
			Temp.V.D32[1]=0xFFFFFFFE&_TimC_RG_Rand_(State);

			Temp.V.R32[0]=Range.U*((real_32)(Temp.C.D32[0]));
			Temp.V.R32[1]=Scale.V*((real_32)(Temp.C.D32[1]));

			Temp.V.R32[0]=logf(Temp.C.R32[0]);
			Temp.V.R32[0]*=Scale.W;
			Temp.V.R32[0]=sqrtf(Temp.C.R32[0]);

			Ptr.V.R32[0]=Temp.C.R32[0]*cosf(Temp.C.R32[1]);

			Ptr.V.R32[0]+=Mean;
		}
		else;

		return 1;
	}
	else
		return 0;
}
_TIMC_ logical TimC_RG_Gau_R64_(TIMC_RG _PL_ _R_ RG,ADDRESS Select,real_64 _PL_ _R_ Array,ADDRESS Length,REAL_64 Mean,REAL_64 Deviation)
{
	if(TimC_RG_Byte_(RG,Select,Array,MemC_Size_(real_64,Length)))
	{
		const union { DATA_64 Ref;REAL_64 U; }Range={.Ref=0x3BF0000000000000};
		const struct { REAL_64 V,W; }Scale={.V=(+2.0)*(BitC.Const.Pi.R64[0])*(Range.U),.W=(-2.0)*(Deviation*Deviation)};
		BITCLIP Temp={.V.D64=(data_64[2]) { 0 }};
		bitclip Ptr={.V.R64=Array},End=Ptr;

		for(End.C.R64+=(Length&(BitC.Const.Mask.Safe[1]));Ptr.C.R64<End.C.R64;Ptr.C.R64+=2)
		{
			Temp.V.D64[0]=0x0000000000000001|Ptr.C.D64[0];
			Temp.V.D64[1]=0xFFFFFFFFFFFFFFFE&Ptr.C.D64[1];

			Temp.V.R64[0]=Range.U*((real_64)(Temp.C.D64[0]));
			Temp.V.R64[1]=Scale.V*((real_64)(Temp.C.D64[1]));

			Temp.V.R64[0]=log(Temp.C.R64[0]);
			Temp.V.R64[0]*=Scale.W;
			Temp.V.R64[0]=sqrt(Temp.C.R64[0]);

			Ptr.V.R64[0]=Temp.C.R64[0]*cos(Temp.C.R64[1]);
			Ptr.V.R64[1]=Temp.C.R64[0]*sin(Temp.C.R64[1]);

			Ptr.V.R64[0]+=Mean;
			Ptr.V.R64[1]+=Mean;
		}
		if(Length&(BitC.Const.Mask.Rest[1]))
		{
			BITCLIP State={.V.G=RG->State+Select};

			Temp.V.D64[0]=0x0000000000000001|Ptr.C.D64[0];
			Temp.V.D64[1]=0xFFFFFFFFFFFFFFFE&_TimC_RG_Rand_(State);

			Temp.V.R64[0]=Range.U*((real_64)(Temp.C.D64[0]));
			Temp.V.R64[1]=Scale.V*((real_64)(Temp.C.D64[1]));

			Temp.V.R64[0]=log(Temp.C.R64[0]);
			Temp.V.R64[0]*=Scale.W;
			Temp.V.R64[0]=sqrt(Temp.C.R64[0]);

			Ptr.V.R64[0]=Temp.C.R64[0]*cos(Temp.C.R64[1]);

			Ptr.V.R64[0]+=Mean;
		}
		else;

		return 1;
	}
	else
		return 0;
}

static address _TimC_RG_Perm_(data_64 Value,DATA_64 Mul)
{
	Value*=Mul;
	Value>>=32;

	return ((address)Value);
}
static general _TimC_RG_Swap_(address _PL_ _R_ Ptr,ADDRESS S)
{
	ADDRESS Temp=Ptr[0];

	Ptr[0]=Ptr[S];
	Ptr[S]=Temp;

	return;
}
_TIMC_ logical TimC_RG_Perm_(TIMC_RG _PL_ _R_ RG,ADDRESS Select,address _PL_ _R_ Array,ADDRESS Length)
{
	if(_TimC_Check_((TIMC_VC*)RG,Select))
		if(Length)
			if(Length>UINT64_MAX)
				return 0;
			else
			{
				BITCLIP State={.V.D64=RG->State+Select};
				ADDRESS *End=Array;
				address *_R_ Ptr=Array;
				data_64 Mul=(data_64)Length;

				MemC.Sort.Index_(Array,Length,0);

				for(End+=(Length&(BitC.Const.Mask.Safe[2]));Ptr<End;)
				{
					_TimC_RG_Swap_(Ptr++,_TimC_RG_Perm_((data_64)_TimC_RG_Rand_(State),Mul--));
					_TimC_RG_Swap_(Ptr++,_TimC_RG_Perm_((data_64)_TimC_RG_Rand_(State),Mul--));
					_TimC_RG_Swap_(Ptr++,_TimC_RG_Perm_((data_64)_TimC_RG_Rand_(State),Mul--));
					_TimC_RG_Swap_(Ptr++,_TimC_RG_Perm_((data_64)_TimC_RG_Rand_(State),Mul--));
				}
				for(End+=(Length&(BitC.Const.Mask.Rest[2]));Ptr<End;)
					_TimC_RG_Swap_(Ptr++,_TimC_RG_Perm_((data_64)_TimC_RG_Rand_(State),Mul--));

				return 1;
			}
		else
			return 1;
	else
		return 0;
}
#endif
#endif

#if(Fold_(Undefinition:Internals))
#undef _TIMC_
#undef _TimC_Generic_
#endif

#if(Fold_(Library Casing))
TIMCASE TimC=
{
	.Version=IdiomVersion,
	.Clocks=ConstClocks,
	.SW=
	{
		.Create_=TimC_SW_Create_,
		.Delete_=MemC_Func_Casting_(general,TimC_Delete_,timc_sw *_PL_ _R_),
		.Size_=TimC_SW_Size_,
		.All=
		{
			.Reset_=TimC_SW_Reset_All_,
			.Stop_=TimC_SW_Stop_All_
		},
		.Reset_=TimC_SW_Reset_,
		.Toggle_=TimC_SW_Toggle_,
		.Read=
		{
			.State_=TimC_SW_Read_State_,
			.Count_=TimC_SW_Read_Count_,
			.Sum=
			{
				.R32_=TimC_SW_Read_Sum_R32_,
				.Tag_=TimC_SW_Read_Sum_Tag_
			},
			.Mean=
			{
				.R32_=TimC_SW_Read_Mean_R32_,
				.Tag_=TimC_SW_Read_Mean_Tag_
			}
		}
	},
	.RG=
	{
		.Create_=TimC_RG_Create_,
		.Delete_=MemC_Func_Casting_(general,TimC_Delete_,timc_rg *_PL_ _R_),
		.Size_=TimC_RG_Size_,
		.Reset_=TimC_RG_Reset_,
		.Rand=
		{
			.Byte_=TimC_RG_Byte_,
			.Perm_=TimC_RG_Perm_
		},
		.Uni=
		{
			.I32_=MemC_Func_Casting_(logical,TimC_RG_Uni_I32_,TIMC_RG _PL_ _R_,ADDRESS,inte_32 _PL_ _R_,ADDRESS,INTE_32,INTE_32),
			.R32_=TimC_RG_Uni_R32_,
			.R64_=TimC_RG_Uni_R64_
		},
		.Gau=
		{
			.R32_=TimC_RG_Gau_R32_,
			.R64_=TimC_RG_Gau_R64_
		}
	}
};
TIMCASE *TimC_(general) { return &TimC; }
#endif
