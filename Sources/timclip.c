#include "timclip.h"

#if(MemC_Fold_(Definition:Opaque Types))
struct _timc_te
{
	clock_t Sum;
	clock_t Mark;
	timc_sf State;
	integer Count;
};
#endif

#if(MemC_Fold_(Definition:Global Constants))
static BYTE_08 IdiomVersion[16]="Date:2018.09.06";
static REAL_32 ConstantClocks[2]={(real_32)(CLOCKS_PER_SEC),1.0F/(real_32)(CLOCKS_PER_SEC)};

BYTE_08 _PL_ TimClip=IdiomVersion;
REAL_32 _PL_ TimClocks=ConstantClocks;
#endif

#if(MemC_Fold_(Definition:Functions))
static address _TimC_Overflow_Add_(ADDRESS A,ADDRESS B)
{
	address C=A+B;

	if(C<A)
		C=0;
	else
		if(C<B)
			C=0;

	return C;
}
static address _TimC_Overflow_Mul_(ADDRESS A,ADDRESS B)
{
	address C[2];

	C[0]=A*B;
	if(C[0])
	{
		C[1]=C[0]/B;
		if(C[1]!=A)
			C[0]=0;
	}

	return C[0];
}
timc_sw *TimC_SW_Create_(ADDRESS Timers)
{
	timc_sw *SW;

	if(Timers)
	{
		address Size=_TimC_Overflow_Mul_(Timers,sizeof(timc_te));

		if(Size)
		{
			Size=_TimC_Overflow_Add_(Size,sizeof(timc_sw));
			if(Size)
			{
				SW=MemC_Alloc_Byte_(Size);
				if(SW)
				{
					Acs_(address,SW->Nums)=Timers;
					Acs_(timc_te*,SW->Timer)=(timc_te*)(SW+1);
				}
			}
			else
				SW=NULL;
		}
		else
			SW=NULL;
	}
	else
	{
		SW=MemC_Alloc_Unit_(timc_sw);
		if(SW)
			MemC_Clear_Unit_(SW,timc_sw);
	}

	return SW;
}
general TimC_SW_Delete_(timc_sw *_PL_ SW)
{
	MemC_Deloc_(*SW);
}

address TimC_SW_Size_(TIMC_SW _PL_ SW)
{
	return ((SW)?(sizeof(timc_sw)+MemC_Size_(timc_te,SW->Nums)):(0));
}

timc_sf TimC_SW_Reset_All_(TIMC_SW _PL_ SW)
{
	if(SW)
	{
		if(SW->Nums)
			MemC_Clear_1D_(SW->Timer,SW->Nums,timc_te);

		goto SUCCESS;
	}
	else
		goto FAILURE;
FAILURE:
	return TimCStateUnknown;
SUCCESS:
	return TimCStateStopped;
}
timc_sf TimC_SW_Stop_All_(TIMC_SW _PL_ SW)
{
	if(SW)
	{
		TIMC_TE _PL_ End=SW->Timer+SW->Nums;
		timc_te *_R_ Ptr;

		for(Ptr=SW->Timer;Ptr<End;Ptr++)
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
		goto SUCCESS;
	}
	else
		goto FAILURE;
FAILURE:
	return TimCStateUnknown;
SUCCESS:
	return TimCStateStopped;
}

timc_sf TimC_SW_Reset_(TIMC_SW _PL_ SW,ADDRESS Select)
{
	if(SW)
		if(Select<SW->Nums)
		{
			MemC_Clear_Unit_(SW->Timer+Select,timc_te);

			goto SUCCESS;
		}
		else
			goto FAILURE;
	else
		goto FAILURE;
FAILURE:
	return TimCStateUnknown;
SUCCESS:
	return TimCStateStopped;
}
timc_sf TimC_SW_Toggle_(TIMC_SW _PL_ SW,ADDRESS Select)
{
	timc_sf Flag;

	if(SW)
		if(Select<SW->Nums)
		{
			timc_te _PL_ Timer=SW->Timer+Select;

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
			Flag=Timer->State;
		}
		else
			Flag=TimCStateUnknown;
	else
		Flag=TimCStateUnknown;

	return Flag;
}

timc_sf TimC_SW_Read_State_(TIMC_SW _PL_ SW,ADDRESS Select)
{
	timc_sf Flag;

	if(SW)
		if(Select<SW->Nums)
			Flag=SW->Timer[Select].State;
		else
			Flag=TimCStateUnknown;
	else
		Flag=TimCStateUnknown;

	return Flag;
}
integer TimC_SW_Read_Count_(TIMC_SW _PL_ SW,ADDRESS Select)
{
	integer Count;

	if(SW)
		if(Select<SW->Nums)
			Count=SW->Timer[Select].Count;
		else
			Count=-1;
	else
		Count=-1;

	return Count;
}

real_32 TimC_SW_Read_Sum_(TIMC_SW _PL_ SW,ADDRESS Select)
{
	real_32 Time;

	if(SW)
		if(Select<SW->Nums)
		{
			TIMC_TE _PL_ Timer=SW->Timer+Select;

			switch(Timer->State)
			{
			case TimCStateStopped:
				Time=TimClocks[1]*(real_32)(Timer->Sum);
				break;
			case TimCStateRunning:
				Time=TimClocks[1]*(real_32)(clock()-(Timer->Mark)+(Timer->Sum));
				break;
			default:
				Time=-1.0F;
			}
		}
		else
			Time=-1.0F;
	else
		Time=-1.0F;

	return Time;
}
real_32 TimC_SW_Read_Mean_(TIMC_SW _PL_ SW,ADDRESS Select)
{
	real_32 Time;

	if(SW)
		if(Select<SW->Nums)
		{
			TIMC_TE _PL_ Timer=SW->Timer+Select;

			switch(Timer->State)
			{
			case TimCStateStopped:
				Time=(Timer->Count)?((TimClocks[1]*(real_32)(Timer->Sum))/((real_32)(Timer->Count))):(0.0F);
				break;
			case TimCStateRunning:
				Time=(TimClocks[1]*(real_32)(clock()-(Timer->Mark)+(Timer->Sum)))/((real_32)(Timer->Count));
				break;
			default:
				Time=-1.0F;
			}
		}
		else
			Time=-1.0F;
	else
		Time=-1.0F;

	return Time;
}
#endif
