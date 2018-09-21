#include "staclip.h"

MemC_Type_Declare_(struct,stac_l2,STAC_L2);
struct _stac_l2 { stac_l2 *L[2]; };

static BYTE_08 IdiomVersion[16]="Date:2018.09.20";
BYTE_08 _PL_ StaClip=IdiomVersion;

static general _StaC_Initialize_(stac_l2 *_R_ Ptr,STAC_L2 _PL_ Last)
{
	for(;Ptr<Last;Ptr[-1].L[1]=Ptr)
		Ptr++;

	Ptr[0].L[1]=NULL;
}
static general _StaC_Setup_(STAC_SS _PL_ S)
{
	stac_l2 *_PL_ Stack=(stac_l2**)(S->Stack);
	address _PL_ Count=(address*)(S->Count);

	if(S->Number)
	{
		MemC_Clear_1D_(Stack,S->Number,stac_l2*);
		MemC_Clear_1D_(Count,S->Number,address);
	}
	Count[-1]=S->Capacity;

	if(S->Capacity)
	{
		Stack[-1]=(stac_l2*)(Stack+S->Number);
		_StaC_Initialize_(Stack[-1],Stack[-1]+(S->Capacity-1));
	}
	else
		Stack[-1]=NULL;
}
stac_ss *StaC_SS_Create_(ADDRESS Number,ADDRESS Capacity)
{
	stac_ss *S;

	{
		address TempA=_MemC_Size_Add_(Number,1);

		TempA=_MemC_Size_Mul_(TempA,sizeof(stac_l2*)+sizeof(address));
		if(TempA)
			if(Capacity)
			{
				address TempB=_MemC_Size_Mul_(Capacity,sizeof(stac_l2));

				if(TempB)
				{
					TempA=_MemC_Size_Add_(TempA,TempB);
					if(TempA)
					{
						TempA=_MemC_Size_Add_(TempA,sizeof(stac_ss));
						S=MemC_Alloc_Byte_(TempA);
					}
					else
						S=NULL;
				}
				else
					S=NULL;
			}
			else
			{
				TempA=_MemC_Size_Add_(TempA,sizeof(stac_ss));
				S=MemC_Alloc_Byte_(TempA);
			}
		else
			S=NULL;
	}
	if(S)
	{
		Acs_(address*,S->Count)=(address*)(S+1)+1;
		Acs_(stac_l2**,S->Stack)=(stac_l2**)(S->Count+Number)+1;

		Acs_(address,S->Number)=Number;
		Acs_(address,S->Capacity)=Capacity;

		_StaC_Setup_(S);
	}

	return S;
}
general StaC_SS_Delete_(stac_ss *_PL_ S)
{
	if(*S)
		MemC_Deloc_(*S);
}
address StaC_SS_Size_(STAC_SS _PL_ S)
{
	address Temp;

	if(S)
	{
		Temp=S->Number+1;
		Temp=MemC_Size_(stac_ss,1)+MemC_Size_(stac_l2*,Temp)+MemC_Size_(address,Temp)+MemC_Size_(stac_l2,S->Capacity);
	}
	else
		Temp=0;

	return Temp;
}

static general _StaC_Swap_(stac_l2 *_PL_ Source,stac_l2 *_PL_ Target,general *_PL_ Port)
{
	{
		stac_l2 _PL_ Temp=*Source;

		*Source=Temp->L[1];
		Temp->L[1]=*Target;
		*Target=Temp;
	}
	{
		general _PL_ Temp=*Port;

		*Port=(*Target)->L[0];
		(*Target)->L[0]=Temp;
	}
}
integer StaC_SS_Push_(STAC_SS _PL_ S,ADDRESS Select,GENERAL *Contents)
{
	integer Return;

	if(S)
		if(Select<S->Number)
			if(S->Count[-1])
			{
				stac_l2 *_PL_ Stack=(stac_l2**)(S->Stack);
				address _PL_ Count=(address*)(S->Count);

				_StaC_Swap_(Stack-1,Stack+Select,(general**)(&Contents));

				Count[-1]--;
				Count[Select]++;

				Return=1;
			}
			else
				Return=0;
		else
			Return=0;
	else
		Return=0;

	return Return;
}
general *StaC_SS_Pop_(STAC_SS _PL_ S,ADDRESS Select)
{
	general *Return;

	if(S)
		if(Select<S->Number)
			if(S->Count[Select])
			{
				stac_l2 *_PL_ Stack=(stac_l2**)(S->Stack);
				address _PL_ Count=(address*)(S->Count);

				_StaC_Swap_(Stack+Select,Stack-1,&Return);

				Count[-1]++;
				Count[Select]--;
			}
			else
				Return=NULL;
		else
			Return=NULL;
	else
		Return=NULL;

	return Return;
}

static general _StaC_Reset_(stac_l2 *_PL_ Source,stac_l2 *_PL_ Target)
{
	stac_l2 *Temp;

	for(Temp=*Source;Temp->L[1];Temp=Temp->L[1]);
	Temp->L[1]=*Target;

	*Target=*Source;
	*Source=NULL;
}
integer StaC_SS_Reset_(STAC_SS _PL_ S,ADDRESS Select)
{
	integer Return;

	if(S)
		if(Select<S->Number)
			if(S->Count[Select])
			{
				stac_l2 *_PL_ Stack=(stac_l2**)(S->Stack);
				address _PL_ Count=(address*)(S->Count);

				_StaC_Reset_(Stack+Select,Stack-1);

				Count[-1]+=Count[Select];
				Count[Select]=0;

				Return=1;
			}
			else
				Return=1;
		else
			Return=0;
	else
		Return=0;

	return Return;
}
integer StaC_SS_Reset_All_(STAC_SS _PL_ S)
{
	integer Return;

	if(S)
	{
		_StaC_Setup_(S);

		Return=1;
	}
	else
		Return=0;

	return Return;
}

static integer _StaC_Check_(STAC_L2 *_R_ Ptr)
{
	while(Ptr)
		if(Ptr->L[0])
			Ptr=Ptr->L[1];
		else
			break;

	return (Ptr==NULL);
}
integer StaC_SS_Check_(STAC_SS _PL_ S,ADDRESS Select)
{
	integer Return;

	if(S)
		if(Select<S->Number)
			Return=_StaC_Check_(((stac_l2**)(S->Stack))[Select]);
		else
			Return=0;
	else
		Return=0;

	return Return;
}

static general *_StaC_Peek_(STAC_L2 *_R_ Ptr,address Index)
{
	while(Index--)
		Ptr=Ptr->L[1];

	return Ptr->L[0];
}
general *StaC_SS_Peek_(STAC_SS _PL_ S,ADDRESS Select,ADDRESS Index)
{
	general *Return;

	if(S)
		if(Select<S->Number)
			if(Index<S->Count[Select])
				Return=_StaC_Peek_(((stac_l2**)(S->Stack))[Select],Index);
			else
				Return=NULL;
		else
			Return=NULL;
	else
		Return=NULL;

	return Return;
}
