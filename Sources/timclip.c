#include <limits.h>
#include <math.h>
#include <time.h>
#include "timclip.h"

#if(Fold_(Definition:Opaque Types))
struct _timc_te { clock_t Sum;clock_t Mark;timc_sf State;integer Count; };
MemC_Type_Declare_(struct,timc_te,TIMC_TE);
#endif

#if(Fold_(Definition:Internal Constants))
static BYTE_08 IdiomVersion[16]="Date:2019.07.12";
#endif

#if(Fold_(Definition:Functions))
#define _TIMC_ static

#if(Fold_(Part:Common))
_TIMC_ general TimC_Delete_(general *_PL_ Object)
{
	MemC_Deloc_(*Object);
}
#endif

#if(Fold_(Part:TimC_SW))
_TIMC_ timc_sw *TimC_SW_Create_(ADDRESS Timers)
{
	timc_sw *SW;

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
_TIMC_ address TimC_SW_Size_(TIMC_SW _PL_ SW)
{
	return ((SW)?(sizeof(timc_sw)+MemC_Size_(timc_te,SW->Nums)):(0));
}

_TIMC_ timc_sf TimC_SW_Reset_All_(TIMC_SW _PL_ SW)
{
	if(SW)
	{
		if(SW->Nums)
			MemC_Clear_1D_((timc_te*)(SW->Timer),SW->Nums);
		else;

		return TimCStateStopped;
	}
	else
		return TimCStateUnknown;
}
_TIMC_ timc_sf TimC_SW_Stop_All_(TIMC_SW _PL_ SW)
{
	if(SW)
	{
		for(timc_te *_R_ Ptr=(timc_te*)(SW->Timer),_PL_ End=Ptr+(SW->Nums);Ptr<End;Ptr++)
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

_TIMC_ timc_sf TimC_SW_Reset_(TIMC_SW _PL_ SW,ADDRESS Select)
{
	if(SW)
		if(Select<SW->Nums)
		{
			MemC_Clear_Unit_((timc_te*)(SW->Timer)+Select);

			return TimCStateStopped;
		}
		else;
	else;

	return TimCStateUnknown;
}
_TIMC_ timc_sf TimC_SW_Toggle_(TIMC_SW _PL_ SW,ADDRESS Select)
{
	if(SW)
		if(Select<SW->Nums)
		{
			timc_te _PL_ _R_ Timer=(timc_te*)(SW->Timer)+Select;

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
		else;
	else;

	return TimCStateUnknown;
}

_TIMC_ timc_sf TimC_SW_Read_State_(TIMC_SW _PL_ SW,ADDRESS Select)
{
	if(SW)
		if(Select<SW->Nums)
			return (((timc_te*)(SW->Timer))[Select].State);
		else;
	else;

	return TimCStateUnknown;
}
_TIMC_ integer TimC_SW_Read_Count_(TIMC_SW _PL_ SW,ADDRESS Select)
{
	if(SW)
		if(Select<SW->Nums)
			return (((timc_te*)(SW->Timer))[Select].Count);
		else;
	else;

	return -1;
}

_TIMC_ real_32 TimC_SW_Read_Sum_(TIMC_SW _PL_ SW,ADDRESS Select)
{
	if(SW)
		if(Select<SW->Nums)
		{
			TIMC_TE _PL_ _R_ Timer=(timc_te*)(SW->Timer)+Select;

			switch(Timer->State)
			{
			case TimCStateStopped:
				return (TimC.Clock.Frequency*(real_32)(Timer->Sum));
			case TimCStateRunning:
				return (TimC.Clock.Frequency*(real_32)(clock()-(Timer->Mark)+(Timer->Sum)));
			default:;
			}
		}
		else;
	else;

	return -1.0F;
}
_TIMC_ real_32 TimC_SW_Read_Mean_(TIMC_SW _PL_ SW,ADDRESS Select)
{
	if(SW)
		if(Select<SW->Nums)
		{
			TIMC_TE _PL_ _R_ Timer=(timc_te*)(SW->Timer)+Select;

			switch(Timer->State)
			{
			case TimCStateStopped:
				return ((Timer->Count)?((TimC.Clock.Frequency*(real_32)(Timer->Sum))/((real_32)(Timer->Count))):(0.0F));
			case TimCStateRunning:
				return ((TimC.Clock.Frequency*(real_32)(clock()-(Timer->Mark)+(Timer->Sum)))/((real_32)(Timer->Count)));
			default:;
			}
		}
		else;
	else;

	return -1.0F;
}
#endif

#if(Fold_(Part:TimC_RG))
static general _TimC_RG_Setup_(data_64 *_R_ Ptr,ADDRESS Nums)
{
	data_64 Temp=(data_64)time(NULL);
	
	for(DATA_64 _PL_ End=Ptr+Nums;Ptr<End;Ptr++,Temp++)
		*Ptr=Temp;
}
_TIMC_ timc_rg *TimC_RG_Create_(ADDRESS States)
{
	timc_rg *RG;

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
_TIMC_ address TimC_RG_Size_(TIMC_RG _PL_ RG)
{
	return ((RG)?(sizeof(timc_rg)+MemC_Size_(data_64,RG->Nums)):(0));
}
_TIMC_ logical TimC_RG_Reset_(TIMC_RG _PL_ RG)
{
	if(RG)
	{
		_TimC_RG_Setup_(RG->State,RG->Nums);

		return 1;
	}
	else
		return 0;
}

static data_32 _TimC_RG_Rand_(bitclip State)
{
	DATA_64 Temp=(State.C.D64[0])>>32;

	State.V.D64[0]&=0x00000000FFFFFFFF;
	State.V.D64[0]*=0x00000000FFFEB81B;
	State.V.D64[0]+=Temp;

	return ((State.C.D32[0])^(State.C.D32[1]));
}
_TIMC_ logical TimC_RG_Byte_(TIMC_RG _PL_ RG,ADDRESS Select,general _PL_ _R_ Array,ADDRESS Length)
{
	if(RG)
		if(Select<RG->Nums)
		{
			ADDRESS Batch=Length>>2;
			DATA_32 *End=Array;
			data_32 *_R_ Ptr=Array;
			bitclip State;State.C.G=RG->State+Select;

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
		else;
	else;

	return 0;
}
static data_32 _TimC_RG_Cage_I32_(data_64 Value,DATA_64 Add,DATA_64 Mul)
{
	Value*=Mul;
	Value+=Add;
	Value>>=32;

	return ((data_32)Value);
}
_TIMC_ logical TimC_RG_Uni_I32_(TIMC_RG _PL_ RG,ADDRESS Select,data_32 _PL_ _R_ Array,ADDRESS Length,INTE_32 Min,INTE_32 Max)
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
_TIMC_ logical TimC_RG_Uni_R32_(TIMC_RG _PL_ RG,ADDRESS Select,real_32 _PL_ _R_ Array,ADDRESS Length,REAL_32 Min,REAL_32 Max)
{
	if(TimC_RG_Byte_(RG,Select,Array,MemC_Size_(real_32,Length)))
	{
		DATA_32 Ref=0x2F800000;
		REAL_32 Scale=Acs_(real_32,Ref)*(Max-Min);
		bitclip End;End.C.G=Array;
		bitclip Ptr;Ptr.C.G=Array;

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
_TIMC_ logical TimC_RG_Uni_R64_(TIMC_RG _PL_ RG,ADDRESS Select,real_64 _PL_ _R_ Array,ADDRESS Length,REAL_64 Min,REAL_64 Max)
{
	if(TimC_RG_Byte_(RG,Select,Array,MemC_Size_(real_64,Length)))
	{
		DATA_64 Ref=0x3BF0000000000000;
		REAL_64 Scale=Acs_(real_64,Ref)*(Max-Min);
		bitclip End;End.C.G=Array;
		bitclip Ptr;Ptr.C.G=Array;

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

_TIMC_ logical TimC_RG_Gau_R32_(TIMC_RG _PL_ RG,ADDRESS Select,real_32 _PL_ _R_ Array,ADDRESS Length,REAL_32 Mean,REAL_32 Deviation)
{
	if(TimC_RG_Byte_(RG,Select,Array,MemC_Size_(real_32,Length)))
	{
		DATA_32 Ref=0x2F800000;
		REAL_32 ScaleU=Acs_(real_32,Ref);
		REAL_32 ScaleV=2.0F*(BitC.Const.Pi.R32[0])*ScaleU;
		REAL_32 ScaleW=-2.0F*Deviation*Deviation;
		data_32 Space[2];
		bitclip End;End.C.G=Array;
		bitclip Ptr;Ptr.C.G=Array;
		bitclip Temp;Temp.C.G=Space;

		for(End.C.R32+=(Length&(BitC.Const.Mask.Safe[1]));Ptr.C.R32<End.C.R32;Ptr.C.R32+=2)
		{
			Temp.V.D32[0]=0x00000001|Ptr.C.D32[0];
			Temp.V.D32[1]=0xFFFFFFFE&Ptr.C.D32[1];

			Temp.V.R32[0]=ScaleU*((real_32)(Temp.C.D32[0]));
			Temp.V.R32[1]=ScaleV*((real_32)(Temp.C.D32[1]));

			Temp.V.R32[0]=logf(Temp.C.R32[0]);
			Temp.V.R32[0]*=ScaleW;
			Temp.V.R32[0]=sqrtf(Temp.C.R32[0]);

			Ptr.V.R32[0]=Temp.C.R32[0]*cosf(Temp.C.R32[1]);
			Ptr.V.R32[1]=Temp.C.R32[0]*sinf(Temp.C.R32[1]);

			Ptr.V.R32[0]+=Mean;
			Ptr.V.R32[1]+=Mean;
		}
		if(Length&(BitC.Const.Mask.Rest[1]))
		{
			bitclip State;State.C.G=RG->State+Select;

			Temp.V.D32[0]=0x00000001|Ptr.C.D32[0];
			Temp.V.D32[1]=0xFFFFFFFE&_TimC_RG_Rand_(State);

			Temp.V.R32[0]=ScaleU*((real_32)(Temp.C.D32[0]));
			Temp.V.R32[1]=ScaleV*((real_32)(Temp.C.D32[1]));

			Temp.V.R32[0]=logf(Temp.C.R32[0]);
			Temp.V.R32[0]*=ScaleW;
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
_TIMC_ logical TimC_RG_Gau_R64_(TIMC_RG _PL_ RG,ADDRESS Select,real_64 _PL_ _R_ Array,ADDRESS Length,REAL_64 Mean,REAL_64 Deviation)
{
	if(TimC_RG_Byte_(RG,Select,Array,MemC_Size_(real_64,Length)))
	{
		DATA_64 Ref=0x3BF0000000000000;
		REAL_64 ScaleU=Acs_(real_64,Ref);
		REAL_64 ScaleV=2.0*(BitC.Const.Pi.R64[0])*ScaleU;
		REAL_64 ScaleW=-2.0*Deviation*Deviation;
		data_64 Space[2];
		bitclip End;End.C.G=Array;
		bitclip Ptr;Ptr.C.G=Array;
		bitclip Temp;Temp.C.G=Space;

		for(End.C.R64+=(Length&(BitC.Const.Mask.Safe[1]));Ptr.C.R64<End.C.R64;Ptr.C.R64+=2)
		{
			Temp.V.D64[0]=0x0000000000000001|Ptr.C.D64[0];
			Temp.V.D64[1]=0xFFFFFFFFFFFFFFFE&Ptr.C.D64[1];

			Temp.V.R64[0]=ScaleU*((real_64)(Temp.C.D64[0]));
			Temp.V.R64[1]=ScaleV*((real_64)(Temp.C.D64[1]));

			Temp.V.R64[0]=log(Temp.C.R64[0]);
			Temp.V.R64[0]*=ScaleW;
			Temp.V.R64[0]=sqrt(Temp.C.R64[0]);

			Ptr.V.R64[0]=Temp.C.R64[0]*cos(Temp.C.R64[1]);
			Ptr.V.R64[1]=Temp.C.R64[0]*sin(Temp.C.R64[1]);

			Ptr.V.R64[0]+=Mean;
			Ptr.V.R64[1]+=Mean;
		}
		if(Length&(BitC.Const.Mask.Rest[1]))
		{
			bitclip State;State.C.G=RG->State+Select;

			Temp.V.D64[0]=0x0000000000000001|Ptr.C.D64[0];
			Temp.V.D64[1]=0xFFFFFFFFFFFFFFFE&_TimC_RG_Rand_(State);

			Temp.V.R64[0]=ScaleU*((real_64)(Temp.C.D64[0]));
			Temp.V.R64[1]=ScaleV*((real_64)(Temp.C.D64[1]));

			Temp.V.R64[0]=log(Temp.C.R64[0]);
			Temp.V.R64[0]*=ScaleW;
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
}
_TIMC_ logical TimC_RG_Perm_(TIMC_RG _PL_ RG,ADDRESS Select,address _PL_ _R_ Array,ADDRESS Length)
{
	if(RG)
		if(Select<RG->Nums)
			if(Length)
			{
				data_64 Mul=(data_64)Length;

				if(Length>((address)Mul));
				else
				{
					ADDRESS *End=Array;
					address *_R_ Ptr=Array;
					bitclip State;State.C.G=RG->State+Select;

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
			}
			else
				return 1;
		else;
	else;

	return 0;
}
#endif

#undef _TIMC_
#endif

#if(Fold_(Library Casing))
TIMCASE TimC=
{
	.Version=IdiomVersion,
	.Clock=
	{
		.Resolution=(real_32)(CLOCKS_PER_SEC),
		.Frequency=1.0F/((real_32)(CLOCKS_PER_SEC))
	},
	.SW=
	{
		.Create_=TimC_SW_Create_,
		.Delete_=MemC_Func_Casting_(general,TimC_Delete_,timc_sw *_PL_),
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
			.Sum_=TimC_SW_Read_Sum_,
			.Mean_=TimC_SW_Read_Mean_
		}
	},
	.RG=
	{
		.Create_=TimC_RG_Create_,
		.Delete_=MemC_Func_Casting_(general,TimC_Delete_,timc_rg *_PL_),
		.Size_=TimC_RG_Size_,
		.Reset_=TimC_RG_Reset_,
		.Rand=
		{
			.Byte_=TimC_RG_Byte_,
			.Perm_=TimC_RG_Perm_
		},
		.Uni=
		{
			.I32_=MemC_Func_Casting_(logical,TimC_RG_Uni_I32_,TIMC_RG _PL_,ADDRESS,inte_32 _PL_ _R_,ADDRESS,INTE_32,INTE_32),
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
