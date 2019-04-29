#include "timclip.h"

#if(Fold_(Definition:Opaque Types))
struct _timc_te { clock_t Sum;clock_t Mark;timc_sf State;integer Count; };
MemC_Type_Declare_(struct,timc_te,TIMC_TE);
#endif

#if(Fold_(Definition:Internal Constants))
static BYTE_08 IdiomVersion[16]="Date:2019.04.26";
#endif

#if(Fold_(Definition:Functions))
#define _TIMC_ static

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
		}
		else
			SW=NULL;
	}
	else
	{
		SW=MemC_Alloc_Unit_(timc_sw);
		if(SW)
			MemC_Clear_Unit_(SW);
	}

	return SW;
}
_TIMC_ general TimC_SW_Delete_(timc_sw *_PL_ SW)
{
	MemC_Deloc_(*SW);
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

		goto SUCCESS;
	}
	else
		goto FAILURE;
FAILURE:
	return TimCStateUnknown;
SUCCESS:
	return TimCStateStopped;
}
_TIMC_ timc_sf TimC_SW_Stop_All_(TIMC_SW _PL_ SW)
{
	if(SW)
	{
		TIMC_TE _PL_ End=(timc_te*)(SW->Timer)+SW->Nums;

		for(timc_te *_R_ Ptr=(timc_te*)(SW->Timer);Ptr<End;Ptr++)
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

_TIMC_ timc_sf TimC_SW_Reset_(TIMC_SW _PL_ SW,ADDRESS Select)
{
	if(SW)
		if(Select<SW->Nums)
		{
			MemC_Clear_Unit_((timc_te*)(SW->Timer)+Select);

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
_TIMC_ timc_sf TimC_SW_Toggle_(TIMC_SW _PL_ SW,ADDRESS Select)
{
	timc_sf Flag;

	if(SW)
		if(Select<SW->Nums)
		{
			timc_te _PL_ Timer=(timc_te*)(SW->Timer)+Select;

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

_TIMC_ timc_sf TimC_SW_Read_State_(TIMC_SW _PL_ SW,ADDRESS Select)
{
	timc_sf Flag;

	if(SW)
		if(Select<SW->Nums)
			Flag=((timc_te*)(SW->Timer))[Select].State;
		else
			Flag=TimCStateUnknown;
	else
		Flag=TimCStateUnknown;

	return Flag;
}
_TIMC_ integer TimC_SW_Read_Count_(TIMC_SW _PL_ SW,ADDRESS Select)
{
	integer Count;

	if(SW)
		if(Select<SW->Nums)
			Count=((timc_te*)(SW->Timer))[Select].Count;
		else
			Count=-1;
	else
		Count=-1;

	return Count;
}

_TIMC_ real_32 TimC_SW_Read_Sum_(TIMC_SW _PL_ SW,ADDRESS Select)
{
	real_32 Time;

	if(SW)
		if(Select<SW->Nums)
		{
			TIMC_TE _PL_ Timer=(timc_te*)(SW->Timer)+Select;

			switch(Timer->State)
			{
			case TimCStateStopped:
				Time=TimC.Clock.Frequency*(real_32)(Timer->Sum);
				break;
			case TimCStateRunning:
				Time=TimC.Clock.Frequency*(real_32)(clock()-(Timer->Mark)+(Timer->Sum));
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
_TIMC_ real_32 TimC_SW_Read_Mean_(TIMC_SW _PL_ SW,ADDRESS Select)
{
	real_32 Time;

	if(SW)
		if(Select<SW->Nums)
		{
			TIMC_TE _PL_ Timer=(timc_te*)(SW->Timer)+Select;

			switch(Timer->State)
			{
			case TimCStateStopped:
				Time=(Timer->Count)?((TimC.Clock.Frequency*(real_32)(Timer->Sum))/((real_32)(Timer->Count))):(0.0F);
				break;
			case TimCStateRunning:
				Time=(TimC.Clock.Frequency*(real_32)(clock()-(Timer->Mark)+(Timer->Sum)))/((real_32)(Timer->Count));
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

#undef _TIMC_
#endif

#if(Fold_(Library Casing))
const struct _timcase TimC=
{
	.Version=IdiomVersion,
	.Clock.Resolution=(real_32)(CLOCKS_PER_SEC),
	.Clock.Frequency=1.0F/((real_32)(CLOCKS_PER_SEC)),

	.SW.Create_=TimC_SW_Create_,
	.SW.Delete_=TimC_SW_Delete_,
	.SW.Size_=TimC_SW_Size_,
	.SW.All.Reset_=TimC_SW_Reset_All_,
	.SW.All.Stop_=TimC_SW_Stop_All_,
	.SW.Reset_=TimC_SW_Reset_,
	.SW.Toggle_=TimC_SW_Toggle_,
	.SW.State_=TimC_SW_Read_State_,
	.SW.Count_=TimC_SW_Read_Count_,
	.SW.Sum_=TimC_SW_Read_Sum_,
	.SW.Mean_=TimC_SW_Read_Mean_
};
#endif
