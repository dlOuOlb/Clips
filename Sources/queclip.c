#include "queclip.h"

struct _quec_l2 { quec_l2 *L[2]; };

static BYTE_08 IdiomVersion[16]="Date:2018.09.12";
BYTE_08 _PL_ QueClip=IdiomVersion;

static address _QueC_Overflow_Add_(ADDRESS A,ADDRESS B)
{
	address C=A+B;

	if(C<A)
		C=0;
	else
		if(C<B)
			C=0;

	return C;
}
static address _QueC_Overflow_Mul_(ADDRESS A,ADDRESS B)
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
static general _QueC_Initialize_(quec_l2 _PL_ Queue,ADDRESS Nums,ADDRESS Caps)
{
	quec_l2 *_R_ Ptr=Queue-1;

	Ptr->L[0]=Queue+Nums;
	Ptr->L[1]=Ptr->L[0]+(Caps-1);

	for(Ptr=Ptr->L[0];Ptr<Queue[-1].L[1];Ptr[-1].L[1]=Ptr)
		Ptr++;

	Ptr[0].L[1]=NULL;
}
static general _QueC_Setup_(QUEC_QS _PL_ Q)
{
	if(Q->Nums)
	{
		MemC_Clear_1D_(Q->Queue,Q->Nums,quec_l2);
		MemC_Clear_1D_((address*)(Q->Lngs),Q->Nums,address);
	}
	((address*)(Q->Lngs))[-1]=Q->Caps;

	if(Q->Caps)
		_QueC_Initialize_(Q->Queue,Q->Nums,Q->Caps);
	else
	{
		Q->Queue[-1].L[0]=NULL;
		Q->Queue[-1].L[1]=NULL;
	}
}
quec_qs *QueC_QS_Create_(ADDRESS Nums,ADDRESS Caps)
{
	quec_qs *Q;

	{
		address TempA=_QueC_Overflow_Add_(Nums,1);

		TempA=_QueC_Overflow_Mul_(TempA,sizeof(quec_l2)+sizeof(address));
		if(TempA)
			if(Caps)
			{
				address TempB=_QueC_Overflow_Mul_(Caps,sizeof(quec_l2));

				if(TempB)
				{
					TempA=_QueC_Overflow_Add_(TempA,TempB);
					if(TempA)
					{
						TempA=_QueC_Overflow_Add_(TempA,sizeof(quec_qs));
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
				TempA=_QueC_Overflow_Add_(TempA,sizeof(quec_qs));
				Q=MemC_Alloc_Byte_(TempA);
			}
		else
			Q=NULL;
	}
	if(Q)
	{
		Acs_(address*,Q->Lngs)=(address*)(Q+1)+1;
		Acs_(quec_l2*,Q->Queue)=(quec_l2*)(Q->Lngs+Nums)+1;

		Acs_(address,Q->Nums)=Nums;
		Acs_(address,Q->Caps)=Caps;

		_QueC_Setup_(Q);
	}

	return Q;
}
general QueC_QS_Delete_(quec_qs *_PL_ Q)
{
	if(*Q)
	{
		MemC_Deloc_(*Q);
	}
}
address QueC_QS_Size_(QUEC_QS _PL_ Q)
{
	address Temp;

	if(Q)
	{
		Temp=Q->Nums+1;
		Temp=MemC_Size_(quec_qs,1)+MemC_Size_(quec_l2,Temp)+MemC_Size_(address,Temp)+MemC_Size_(quec_l2,Q->Caps);
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
		if(Select<Q->Nums)
			if(Q->Lngs[-1])
			{
				_QueC_Swap_(Q->Queue[-1].L,Q->Queue[Select].L,(general**)(&Contents));

				((address*)(Q->Lngs))[-1]--;
				((address*)(Q->Lngs))[Select]++;

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
		if(Select<Q->Nums)
			if(Q->Lngs[Select])
			{
				_QueC_Swap_(Q->Queue[Select].L,Q->Queue[-1].L,&Return);

				((address*)(Q->Lngs))[-1]++;
				((address*)(Q->Lngs))[Select]--;
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
		if(Select<Q->Nums)
			if(Q->Lngs[Select])
			{
				_QueC_Reset_(Q->Queue[Select].L,Q->Queue[-1].L);

				((address*)(Q->Lngs))[-1]+=Q->Lngs[Select];
				((address*)(Q->Lngs))[Select]=0;

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
		address Select;

		for(Select=0;Select<Q->Nums;Select++)
			if(Q->Lngs[Select])
			{
				_QueC_Reset_(Q->Queue[Select].L,Q->Queue[-1].L);

				((address*)(Q->Lngs))[-1]+=Q->Lngs[Select];
				((address*)(Q->Lngs))[Select]=0;
			}
		Return=1;
	}
	else
		Return=0;

	return Return;
}
