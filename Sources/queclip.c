#include "queclip.h"

MemC_Type_Declare_(struct,quec_l2,QUEC_L2);
struct _quec_l2 { quec_l2 *L[2]; };

static BYTE_08 IdiomVersion[16]="Date:2018.09.20";
BYTE_08 _PL_ QueClip=IdiomVersion;

static general _QueC_Initialize_(quec_l2 _PL_ Queue,ADDRESS Number,ADDRESS Capacity)
{
	quec_l2 *_R_ Ptr=Queue-1;

	Ptr->L[0]=Queue+Number;
	Ptr->L[1]=Ptr->L[0]+(Capacity-1);

	for(Ptr=Ptr->L[0];Ptr<Queue[-1].L[1];Ptr[-1].L[1]=Ptr)
		Ptr++;

	Ptr[0].L[1]=NULL;
}
static general _QueC_Setup_(QUEC_QS _PL_ Q)
{
	quec_l2 _PL_ Queue=(quec_l2*)(Q->Queue);
	address _PL_ Count=(address*)(Q->Count);

	if(Q->Number)
	{
		MemC_Clear_1D_(Queue,Q->Number,quec_l2);
		MemC_Clear_1D_(Count,Q->Number,address);
	}
	Count[-1]=Q->Capacity;

	if(Q->Capacity)
		_QueC_Initialize_(Queue,Q->Number,Q->Capacity);
	else
	{
		Queue[-1].L[0]=NULL;
		Queue[-1].L[1]=NULL;
	}
}
quec_qs *QueC_QS_Create_(ADDRESS Number,ADDRESS Capacity)
{
	quec_qs *Q;

	{
		address TempA=_MemC_Size_Add_(Number,1);

		TempA=_MemC_Size_Mul_(TempA,sizeof(quec_l2)+sizeof(address));
		if(TempA)
			if(Capacity)
			{
				address TempB=_MemC_Size_Mul_(Capacity,sizeof(quec_l2));

				if(TempB)
				{
					TempA=_MemC_Size_Add_(TempA,TempB);
					if(TempA)
					{
						TempA=_MemC_Size_Add_(TempA,sizeof(quec_qs));
						Q=MemC_Alloc_Byte_(TempA);
					}
					else
						Q=NULL;
				}
				else
					Q=NULL;
			}
			else
			{
				TempA=_MemC_Size_Add_(TempA,sizeof(quec_qs));
				Q=MemC_Alloc_Byte_(TempA);
			}
		else
			Q=NULL;
	}
	if(Q)
	{
		Acs_(address*,Q->Count)=(address*)(Q+1)+1;
		Acs_(quec_l2*,Q->Queue)=(quec_l2*)(Q->Count+Number)+1;

		Acs_(address,Q->Number)=Number;
		Acs_(address,Q->Capacity)=Capacity;

		_QueC_Setup_(Q);
	}

	return Q;
}
general QueC_QS_Delete_(quec_qs *_PL_ Q)
{
	if(*Q)
		MemC_Deloc_(*Q);
}
address QueC_QS_Size_(QUEC_QS _PL_ Q)
{
	address Temp;

	if(Q)
	{
		Temp=Q->Number+1;
		Temp=MemC_Size_(quec_qs,1)+MemC_Size_(quec_l2,Temp)+MemC_Size_(address,Temp)+MemC_Size_(quec_l2,Q->Capacity);
	}
	else
		Temp=0;

	return Temp;
}

static general _QueC_Swap_(quec_l2 *_PL_ Source,quec_l2 *_PL_ Target,general *_PL_ Port)
{
	if(Target[1])
	{
		Target[1]->L[1]=Source[0];
		Target[1]=Target[1]->L[1];
	}
	else
	{
		Target[0]=Source[0];
		Target[1]=Target[0];
	}
	if(Source[0]->L[1])
		Source[0]=Source[0]->L[1];
	else
	{
		Source[0]=NULL;
		Source[1]=NULL;
	}
	{
		general _PL_ Temp=*Port;

		*Port=Target[1]->L[0];
		Target[1]->L[0]=Temp;
		Target[1]->L[1]=NULL;
	}
}
integer QueC_QS_Enque_(QUEC_QS _PL_ Q,ADDRESS Select,GENERAL *Contents)
{
	integer Return;

	if(Q)
		if(Select<Q->Number)
			if(Q->Count[-1])
			{
				quec_l2 _PL_ Queue=(quec_l2*)(Q->Queue);
				address _PL_ Count=(address*)(Q->Count);

				_QueC_Swap_(Queue[-1].L,Queue[Select].L,(general**)(&Contents));

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
general *QueC_QS_Deque_(QUEC_QS _PL_ Q,ADDRESS Select)
{
	general *Return;

	if(Q)
		if(Select<Q->Number)
			if(Q->Count[Select])
			{
				quec_l2 _PL_ Queue=(quec_l2*)(Q->Queue);
				address _PL_ Count=(address*)(Q->Count);

				_QueC_Swap_(Queue[Select].L,Queue[-1].L,&Return);

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

static general _QueC_Reset_(quec_l2 *_PL_ Source,quec_l2 *_PL_ Target)
{
	if(Target[1])
		Target[1]->L[1]=Source[0];
	else
		Target[0]=Source[0];
	{
		Target[1]=Source[1];

		Source[0]=NULL;
		Source[1]=NULL;
	}
}
integer QueC_QS_Reset_(QUEC_QS _PL_ Q,ADDRESS Select)
{
	integer Return;

	if(Q)
		if(Select<Q->Number)
			if(Q->Count[Select])
			{
				quec_l2 _PL_ Queue=(quec_l2*)(Q->Queue);
				address _PL_ Count=(address*)(Q->Count);

				_QueC_Reset_(Queue[Select].L,Queue[-1].L);

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
integer QueC_QS_Reset_All_(QUEC_QS _PL_ Q)
{
	integer Return;

	if(Q)
	{
		quec_l2 _PL_ Queue=(quec_l2*)(Q->Queue);
		address _PL_ Count=(address*)(Q->Count);
		address Select;

		for(Select=0;Select<Q->Number;Select++)
			if(Count[Select])
			{
				_QueC_Reset_(Queue[Select].L,Queue[-1].L);

				Count[-1]+=Count[Select];
				Count[Select]=0;
			}
		Return=1;
	}
	else
		Return=0;

	return Return;
}

static integer _QueC_Check_(QUEC_L2 *_R_ Ptr)
{
	while(Ptr)
		if(Ptr->L[0])
			Ptr=Ptr->L[1];
		else
			break;

	return (Ptr==NULL);
}
integer QueC_QS_Check_(QUEC_QS _PL_ Q,ADDRESS Select)
{
	integer Return;

	if(Q)
		if(Select<Q->Number)
			Return=_QueC_Check_(((quec_l2*)(Q->Queue))[Select].L[0]);
		else
			Return=0;
	else
		Return=0;

	return Return;
}

static general *_QueC_Peek_(QUEC_L2 *_R_ Ptr,address Index)
{
	while(Index--)
		Ptr=Ptr->L[1];

	return Ptr->L[0];
}
general *QueC_QS_Peek_(QUEC_QS _PL_ Q,ADDRESS Select,ADDRESS Index)
{
	general *Return;

	if(Q)
		if(Select<Q->Number)
			if(Index<Q->Count[Select])
				Return=_QueC_Peek_(((quec_l2*)(Q->Queue))[Select].L[0],Index);
			else
				Return=NULL;
		else
			Return=NULL;
	else
		Return=NULL;

	return Return;
}
