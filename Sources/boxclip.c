#include "boxclip.h"

#if(Fold_(Definition:Internal Constants))
static BYTE_08 IdiomVersion[16]="Date:2019.07.12";
#endif

#if(Fold_(Definition:BoxClip Structure Functions))
#define _BOXC_ static

#if(Fold_(Part:BoxC_L2))
MemC_Type_Declare_(struct,boxc_l2,BOXC_L2);
struct _boxc_l2 { boxc_l2 *L[2]; };

static general _BoxC_L2_Assign_(boxc_l2 *_R_ Ptr,BOXC_L2 _PL_ Last)
{
	for(;Ptr<Last;Ptr[-1].L[1]=Ptr)
		Ptr++;

	Ptr[0].L[1]=NULL;
}
static logical _BoxC_L2_Check_(BOXC_L2 *_R_ Ptr)
{
	while(Ptr)
		if(Ptr->L[0])
			Ptr=Ptr->L[1];
		else
			return 0;

	return 1;
}
static general *_BoxC_L2_Peek_(BOXC_L2 *_R_ Ptr,address Index)
{
	while(Index--)
		Ptr=Ptr->L[1];

	return Ptr->L[0];
}
#endif

#if(Fold_(Part:BoxC_VS))
struct _boxc_vs
{
	general *Thing;
	address *Count;
	address Number;
	address Capacity;
};
MemC_Type_Declare_(struct,boxc_vs,BOXC_VS);

static general _BoxC_VS_Delete_(boxc_vs *_PL_ V)
{
	MemC_Deloc_(*V);
}
#endif

#if(Fold_(Part:BoxC_SS))
static general _BoxC_SS_Setup_(BOXC_VS _PL_ S)
{
	boxc_l2 *_PL_ Stack=S->Thing;
	address _PL_ Count=S->Count;

	if(S->Number)
	{
		MemC_Clear_1D_(Stack,S->Number);
		MemC_Clear_1D_(Count,S->Number);
	}
	else;

	Count[-1]=S->Capacity;

	if(S->Capacity)
	{
		Stack[-1]=(boxc_l2*)(Stack+S->Number);
		_BoxC_L2_Assign_(Stack[-1],Stack[-1]+(S->Capacity-1));
	}
	else
		Stack[-1]=NULL;
}
_BOXC_ boxc_vs *BoxC_SS_Create_(ADDRESS Number,ADDRESS Capacity)
{
	boxc_vs *S;

	MemC_Temp_(address,Size=MemC.Size.Mul_(Number+1,sizeof(boxc_l2*)+sizeof(address)))
		if(Size)
			if(Capacity)
			{
				ADDRESS Temp=MemC.Size.Mul_(Capacity,sizeof(boxc_l2));

				if(Temp)
				{
					Size=MemC.Size.Add_(Size,Temp);

					S=(Size)?(MemC.Alloc.Byte_(MemC.Size.Add_(Size,sizeof(boxc_vs)))):(NULL);
				}
				else
					S=NULL;
			}
			else
				S=MemC.Alloc.Byte_(MemC.Size.Add_(Size,sizeof(boxc_vs)));
		else
			S=NULL;

	if(S)
	{
		S->Count=(address*)(S+1)+1;
		S->Thing=(boxc_l2**)(S->Count+Number)+1;

		S->Number=Number;
		S->Capacity=Capacity;

		_BoxC_SS_Setup_(S);
	}
	else;

	return S;
}
_BOXC_ address BoxC_SS_Size_(BOXC_VS _PL_ S)
{
	address Temp;

	if(S)
	{
		Temp=S->Number+1;
		Temp=MemC_Size_(boxc_ss,1)+MemC_Size_(boxc_l2*,Temp)+MemC_Size_(address,Temp)+MemC_Size_(boxc_l2,S->Capacity);
	}
	else
		Temp=0;

	return Temp;
}

static general _BoxC_SS_Swap_(boxc_l2 *_PL_ Source,boxc_l2 *_PL_ Target,general *_PL_ Port)
{
	{
		boxc_l2 _PL_ Temp=*Source;

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
_BOXC_ logical BoxC_SS_Push_(BOXC_VS _PL_ S,ADDRESS Select,general *Contents)
{
	if(S)
		if(Select<S->Number)
			if(S->Count[-1])
			{
				boxc_l2 *_PL_ Stack=S->Thing;
				address _PL_ Count=S->Count;

				_BoxC_SS_Swap_(Stack-1,Stack+Select,&Contents);

				Count[-1]--;
				Count[Select]++;

				return 1;
			}
			else;
		else;
	else;

	return 0;
}
_BOXC_ general *BoxC_SS_Pop_(BOXC_VS _PL_ S,ADDRESS Select)
{
	if(S)
		if(Select<S->Number)
			if(S->Count[Select])
			{
				boxc_l2 *_PL_ Stack=S->Thing;
				address _PL_ Count=S->Count;
				general *Object;

				_BoxC_SS_Swap_(Stack+Select,Stack-1,&Object);

				Count[-1]++;
				Count[Select]--;

				return Object;
			}
			else;
		else;
	else;

	return NULL;
}
_BOXC_ address BoxC_SS_Spread_(MEMC_MS _PL_ MS,BOXC_VS _PL_ SS,ADDRESS Select)
{
	if(MS)
		if(SS)
			if(Select<SS->Number)
			{
				boxc_l2 *_PL_ Stack=SS->Thing;
				address _PL_ Count=SS->Count;
				ADDRESS Number=((MS->Nums)<(SS->Count[Select]))?(MS->Nums):(SS->Count[Select]);

				MemC_Temp_(boxc_l2,*_PL_ From=Stack+Select,*_PL_ Into=Stack-1)
					for(general **Ptr=MS->Slot.P,_PL_ _PL_ End=Ptr+Number;Ptr<End;Ptr++)
						_BoxC_SS_Swap_(From,Into,Ptr);

				Count[-1]+=Number;
				Count[Select]-=Number;

				return Number;
			}
			else;
		else;
	else;

	return 0;
}

static general _BoxC_SS_Reset_(boxc_l2 *_PL_ Source,boxc_l2 *_PL_ Target)
{
	boxc_l2 *Temp;

	for(Temp=*Source;Temp->L[1];Temp=Temp->L[1]);
	Temp->L[1]=*Target;

	*Target=*Source;
	*Source=NULL;
}
_BOXC_ logical BoxC_SS_Reset_(BOXC_VS _PL_ S,ADDRESS Select)
{
	if(S)
		if(Select<S->Number)
		{
			if(S->Count[Select])
			{
				boxc_l2 *_PL_ Stack=S->Thing;
				address _PL_ Count=S->Count;

				_BoxC_SS_Reset_(Stack+Select,Stack-1);

				Count[-1]+=Count[Select];
				Count[Select]=0;
			}
			else;

			return 1;
		}
		else;
	else;

	return 0;
}
_BOXC_ logical BoxC_SS_Reset_All_(BOXC_VS _PL_ S)
{
	if(S)
	{
		_BoxC_SS_Setup_(S);

		return 1;
	}
	else
		return 0;
}

_BOXC_ logical BoxC_SS_Check_(BOXC_VS _PL_ S,ADDRESS Select)
{
	if(S)
		if(Select<S->Number)
			return _BoxC_L2_Check_(((boxc_l2**)(S->Thing))[Select]);
		else;
	else;

	return 0;
}
_BOXC_ general *BoxC_SS_Peek_(BOXC_VS _PL_ S,ADDRESS Select,ADDRESS Index)
{
	if(S)
		if(Select<S->Number)
			if(Index<S->Count[Select])
				return _BoxC_L2_Peek_(((boxc_l2**)(S->Thing))[Select],Index);
			else;
		else;
	else;

	return NULL;
}
#endif

#if(Fold_(Part:BoxC_QS))
static general _BoxC_QS_Setup_(BOXC_VS _PL_ Q)
{
	boxc_l2 _PL_ Queue=Q->Thing;
	address _PL_ Count=Q->Count;

	if(Q->Number)
	{
		MemC_Clear_1D_(Queue,Q->Number);
		MemC_Clear_1D_(Count,Q->Number);
	}
	else;

	Count[-1]=Q->Capacity;

	if(Q->Capacity)
	{
		Queue[-1].L[0]=Queue+Q->Number;
		Queue[-1].L[1]=Queue[-1].L[0]+(Q->Capacity-1);

		_BoxC_L2_Assign_(Queue[-1].L[0],Queue[-1].L[1]);
	}
	else
	{
		Queue[-1].L[0]=NULL;
		Queue[-1].L[1]=NULL;
	}
}
_BOXC_ boxc_vs *BoxC_QS_Create_(ADDRESS Number,ADDRESS Capacity)
{
	boxc_vs *Q;

	MemC_Temp_(address,Size=MemC.Size.Mul_(Number+1,sizeof(boxc_l2)+sizeof(address)))
		if(Size)
			if(Capacity)
			{
				ADDRESS Temp=MemC.Size.Mul_(Capacity,sizeof(boxc_l2));

				if(Temp)
				{
					Size=MemC.Size.Add_(Size,Temp);

					Q=(Size)?(MemC.Alloc.Byte_(MemC.Size.Add_(Size,sizeof(boxc_vs)))):(NULL);
				}
				else
					Q=NULL;
			}
			else
				Q=MemC.Alloc.Byte_(MemC.Size.Add_(Size,sizeof(boxc_vs)));
		else
			Q=NULL;

	if(Q)
	{
		Q->Count=(address*)(Q+1)+1;
		Q->Thing=(boxc_l2*)(Q->Count+Number)+1;

		Q->Number=Number;
		Q->Capacity=Capacity;

		_BoxC_QS_Setup_(Q);
	}
	else;

	return Q;
}
_BOXC_ address BoxC_QS_Size_(BOXC_VS _PL_ Q)
{
	address Temp;

	if(Q)
	{
		Temp=Q->Number+1;
		Temp=MemC_Size_(boxc_qs,1)+MemC_Size_(boxc_l2,Temp)+MemC_Size_(address,Temp)+MemC_Size_(boxc_l2,Q->Capacity);
	}
	else
		Temp=0;

	return Temp;
}

static general _BoxC_QS_Swap_(boxc_l2 *_PL_ Source,boxc_l2 *_PL_ Target,general *_PL_ Port)
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
_BOXC_ logical BoxC_QS_Enque_(BOXC_VS _PL_ Q,ADDRESS Select,general *Contents)
{
	if(Q)
		if(Select<Q->Number)
			if(Q->Count[-1])
			{
				boxc_l2 _PL_ Queue=Q->Thing;
				address _PL_ Count=Q->Count;

				_BoxC_QS_Swap_(Queue[-1].L,Queue[Select].L,&Contents);

				Count[-1]--;
				Count[Select]++;

				return 1;
			}
			else;
		else;
	else;

	return 0;
}
_BOXC_ general *BoxC_QS_Deque_(BOXC_VS _PL_ Q,ADDRESS Select)
{
	if(Q)
		if(Select<Q->Number)
			if(Q->Count[Select])
			{
				boxc_l2 _PL_ Queue=Q->Thing;
				address _PL_ Count=Q->Count;
				general *Object;

				_BoxC_QS_Swap_(Queue[Select].L,Queue[-1].L,&Object);

				Count[-1]++;
				Count[Select]--;

				return Object;
			}
			else;
		else;
	else;

	return NULL;
}
_BOXC_ address BoxC_QS_Spread_(MEMC_MS _PL_ MS,BOXC_VS _PL_ QS,ADDRESS Select)
{
	if(MS)
		if(QS)
			if(Select<QS->Number)
			{
				boxc_l2 _PL_ Queue=QS->Thing;
				address _PL_ Count=QS->Count;
				ADDRESS Number=((MS->Nums)<(QS->Count[Select]))?(MS->Nums):(QS->Count[Select]);

				MemC_Temp_(boxc_l2,_PL_ From=Queue+Select,_PL_ Into=Queue-1)
					for(general **Ptr=MS->Slot.P,_PL_ _PL_ End=Ptr+Number;Ptr<End;Ptr++)
						_BoxC_QS_Swap_(From->L,Into->L,Ptr);

				Count[-1]+=Number;
				Count[Select]-=Number;

				return Number;
			}
			else;
		else;
	else;

	return 0;
}

static general _BoxC_QS_Reset_(boxc_l2 *_PL_ Source,boxc_l2 *_PL_ Target)
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
_BOXC_ logical BoxC_QS_Reset_(BOXC_VS _PL_ Q,ADDRESS Select)
{
	if(Q)
		if(Select<Q->Number)
		{
			if(Q->Count[Select])
			{
				boxc_l2 _PL_ Queue=Q->Thing;
				address _PL_ Count=Q->Count;

				_BoxC_QS_Reset_(Queue[Select].L,Queue[-1].L);

				Count[-1]+=Count[Select];
				Count[Select]=0;
			}
			else;

			return 1;
		}
		else;
	else;

	return 0;
}
_BOXC_ logical BoxC_QS_Reset_All_(BOXC_VS _PL_ Q)
{
	if(Q)
	{
		boxc_l2 _PL_ Queue=Q->Thing;
		address _PL_ Count=Q->Count;

		for(address Select=0;Select<Q->Number;Select++)
			if(Count[Select])
			{
				_BoxC_QS_Reset_(Queue[Select].L,Queue[-1].L);

				Count[-1]+=Count[Select];
				Count[Select]=0;
			}
			else;

		return 1;
	}
	else
		return 0;
}

_BOXC_ logical BoxC_QS_Check_(BOXC_VS _PL_ Q,ADDRESS Select)
{
	if(Q)
		if(Select<Q->Number)
			return _BoxC_L2_Check_(((boxc_l2*)(Q->Thing))[Select].L[0]);
		else;
	else;

	return 0;
}
_BOXC_ general *BoxC_QS_Peek_(BOXC_VS _PL_ Q,ADDRESS Select,ADDRESS Index)
{
	if(Q)
		if(Select<Q->Number)
			if(Index<Q->Count[Select])
				return _BoxC_L2_Peek_(((boxc_l2*)(Q->Thing))[Select].L[0],Index);
			else;
		else;
	else;

	return NULL;
}
#endif

#if(Fold_(Part:BoxC_RS))
#define _BoxC_L2_Twist_(A,B) ((boxc_l2*)(((address)(A))^((address)(B))))

static general _BoxC_RS_Assign_(boxc_l2 *_R_ Ptr,BOXC_L2 _PL_ Last)
{
	for(Ptr++;Ptr<Last;Ptr++)
		Ptr->L[1]=_BoxC_L2_Twist_(Ptr-1,Ptr+1);
}
static general _BoxC_RS_Setup_(BOXC_VS _PL_ R)
{
	boxc_l2 _PL_ Ring=R->Thing;
	address _PL_ Count=R->Count;

	if(R->Number)
	{
		MemC_Clear_1D_(Ring,R->Number);
		MemC_Clear_1D_(Count,R->Number);
	}
	else;

	Count[-1]=R->Capacity;

	if(R->Capacity)
	{
		Ring[-1].L[1]=Ring+R->Number;
		Ring[-1].L[0]=Ring[-1].L[1]+(R->Capacity-1);

		switch(R->Capacity)
		{
		case 1:
			Ring[-1].L[0]->L[1]=NULL;
		case 2:
			Ring[-1].L[1]->L[1]=NULL;
			break;
		default:
			Ring[-1].L[1]->L[1]=_BoxC_L2_Twist_(Ring[-1].L[0],Ring[-1].L[1]+1);
			_BoxC_RS_Assign_(Ring[-1].L[1],Ring[-1].L[0]);
			Ring[-1].L[0]->L[1]=_BoxC_L2_Twist_(Ring[-1].L[1],Ring[-1].L[0]-1);
		}
	}
	else
	{
		Ring[-1].L[0]=NULL;
		Ring[-1].L[1]=NULL;
	}
}
_BOXC_ boxc_vs *BoxC_RS_Create_(ADDRESS Number,ADDRESS Capacity)
{
	boxc_vs *R;

	MemC_Temp_(address,Size=MemC.Size.Mul_(Number+1,sizeof(boxc_l2)+sizeof(address)))
		if(Size)
			if(Capacity)
			{
				ADDRESS Temp=MemC.Size.Mul_(Capacity,sizeof(boxc_l2));

				if(Temp)
				{
					Size=MemC.Size.Add_(Size,Temp);

					R=(Size)?(MemC.Alloc.Byte_(MemC.Size.Add_(Size,sizeof(boxc_vs)))):(NULL);
				}
				else
					R=NULL;
			}
			else
				R=MemC.Alloc.Byte_(MemC.Size.Add_(Size,sizeof(boxc_vs)));
		else
			R=NULL;

	if(R)
	{
		R->Count=(address*)(R+1)+1;
		R->Thing=(boxc_l2*)(R->Count+Number)+1;

		R->Number=Number;
		R->Capacity=Capacity;

		_BoxC_RS_Setup_(R);
	}
	else;

	return R;
}
_BOXC_ address BoxC_RS_Size_(BOXC_VS _PL_ R)
{
	address Temp;

	if(R)
	{
		Temp=R->Number+1;
		Temp=MemC_Size_(boxc_rs,1)+MemC_Size_(boxc_l2,Temp)+MemC_Size_(address,Temp)+MemC_Size_(boxc_l2,R->Capacity);
	}
	else
		Temp=0;

	return Temp;
}

static general _BoxC_RS_Swap_(boxc_l2 *_PL_ Source,boxc_l2 *_PL_ Target,general *_PL_ Port,LOGICAL Posi)
{
	LOGICAL Nega=Posi^1;
	boxc_l2 _PL_ Here=Source[Posi];

	if(Source[0]==Source[1])
	{
		Source[0]=NULL;
		Source[1]=NULL;
	}
	else
	{
		boxc_l2 _PL_ NearA=_BoxC_L2_Twist_(Here->L[1],Source[Nega]);
		boxc_l2 _PL_ NearB=_BoxC_L2_Twist_(Here->L[1],NearA);

		NearA->L[1]=_BoxC_L2_Twist_(NearA->L[1],_BoxC_L2_Twist_(Here,NearB));
		NearB->L[1]=_BoxC_L2_Twist_(NearB->L[1],_BoxC_L2_Twist_(Here,NearA));

		Source[Posi]=NearA;
	}
	{
		general _PL_ Temp=*Port;

		*Port=Here->L[0];
		Here->L[0]=Temp;
		Here->L[1]=_BoxC_L2_Twist_(Target[0],Target[1]);
	}
	if(Target[Nega])
	{
		Target[Nega]->L[1]=_BoxC_L2_Twist_(Target[Nega]->L[1],_BoxC_L2_Twist_(Here,Target[Posi]));
		Target[Posi]->L[1]=_BoxC_L2_Twist_(Target[Posi]->L[1],_BoxC_L2_Twist_(Here,Target[Nega]));
	}
	else
		Target[Posi]=Here;
	Target[Nega]=Here;
}
_BOXC_ logical BoxC_RS_Insert_(BOXC_VS _PL_ R,ADDRESS Select,general *Contents,LOGICAL Mode)
{
	if(R)
		if(Select<R->Number)
			if(R->Count[-1])
			{
				boxc_l2 _PL_ Ring=R->Thing;
				address _PL_ Count=R->Count;

				_BoxC_RS_Swap_(Ring[-1].L,Ring[Select].L,&Contents,Mode);

				Count[-1]--;
				Count[Select]++;

				return 1;
			}
			else;
		else;
	else;

	return 0;
}
_BOXC_ logical BoxC_RS_Desert_(BOXC_VS _PL_ R,ADDRESS Select,LOGICAL Mode)
{
	if(R)
		if(Select<R->Number)
			if(R->Count[Select])
			{
				boxc_l2 _PL_ Ring=R->Thing;
				address _PL_ Count=R->Count;
				general *Temp;

				_BoxC_RS_Swap_(Ring[Select].L,Ring[-1].L,&Temp,Mode&1);

				Count[-1]++;
				Count[Select]--;

				return 1;
			}
			else;
		else;
	else;

	return 0;
}

static general _BoxC_RS_Rotate_(BOXC_L2 *_PL_ Ring,sintptr Rotation)
{
	SINTPTR Mask=(Rotation>0);
	SINTPTR Nega=Mask^1;
	BOXC_L2 *Here=Ring[Mask];
	BOXC_L2 *Prop=_BoxC_L2_Twist_(Ring[Nega],Here->L[1]);

	for(SINTPTR Step=1-(Mask<<1);Rotation;Rotation+=Step)
	{
		BOXC_L2 _PL_ Temp=Prop;

		Prop=_BoxC_L2_Twist_(Here,Prop->L[1]);
		Here=Temp;
	}
	{
		Ring[Mask]=Here;
		Ring[Nega]=_BoxC_L2_Twist_(Prop,Here->L[1]);
	}
}
_BOXC_ logical BoxC_RS_Rotate_(BOXC_VS _PL_ R,ADDRESS Select,SINTPTR Rotation)
{
	if(R)
		if(Select<R->Number)
		{
			ADDRESS Count=R->Count[Select];

			if(Count)
				_BoxC_RS_Rotate_(((boxc_l2*)(R->Thing))[Select].L,Rotation%Acs_(sintptr,Count));
			else;

			return 1;
		}
		else;
	else;

	return 0;
}

static general _BoxC_RS_Reset_(boxc_l2 *_PL_ Source,boxc_l2 *_PL_ Target)
{
	if(Target[0])
	{
		BOXC_L2 *Twist;

		Twist=_BoxC_L2_Twist_(Source[0],Target[0]);
		Target[1]->L[1]=_BoxC_L2_Twist_(Target[1]->L[1],Twist);
		Source[1]->L[1]=_BoxC_L2_Twist_(Source[1]->L[1],Twist);

		Twist=_BoxC_L2_Twist_(Source[1],Target[1]);
		Source[0]->L[1]=_BoxC_L2_Twist_(Source[0]->L[1],Twist);
		Target[0]->L[1]=_BoxC_L2_Twist_(Target[0]->L[1],Twist);
	}
	else
		Target[1]=Source[1];
	{
		Target[0]=Source[0];

		Source[0]=NULL;
		Source[1]=NULL;
	}
}
_BOXC_ logical BoxC_RS_Reset_(BOXC_VS _PL_ R,ADDRESS Select)
{
	if(R)
		if(Select<R->Number)
		{
			if(R->Count[Select])
			{
				boxc_l2 _PL_ Ring=R->Thing;
				address _PL_ Count=R->Count;

				_BoxC_RS_Reset_(Ring[Select].L,Ring[-1].L);

				Count[-1]+=Count[Select];
				Count[Select]=0;
			}
			else;

			return 1;
		}
		else;
	else;

	return 0;
}
_BOXC_ logical BoxC_RS_Reset_All_(BOXC_VS _PL_ R)
{
	if(R)
	{
		boxc_l2 _PL_ Ring=R->Thing;
		address _PL_ Count=R->Count;
		address Select;

		for(Select=0;Select<R->Number;Select++)
			if(Count[Select])
			{
				_BoxC_RS_Reset_(Ring[Select].L,Ring[-1].L);

				Count[-1]+=Count[Select];
				Count[Select]=0;
			}
			else;

		return 1;
	}
	else
		return 0;
}

static logical _BoxC_RS_Check_(BOXC_L2 _PL_ _PL_ Ring)
{
	if(Ring[0]==Ring[1])
		return (Ring[0]->L[0]!=NULL);
	else
	{
		BOXC_L2 *Here=Ring[1];
		BOXC_L2 *Next=_BoxC_L2_Twist_(Ring[0],Here->L[1]);

		while(Next!=Ring[1])
			if(Here->L[0])
			{
				BOXC_L2 _PL_ Temp=Next;

				Next=_BoxC_L2_Twist_(Here,Next->L[1]);
				Here=Temp;
			}
			else
				break;

		return (Next==Ring[1]);
	}
}
_BOXC_ logical BoxC_RS_Check_(BOXC_VS _PL_ R,ADDRESS Select)
{
	if(R)
		if(Select<R->Number)
			return _BoxC_RS_Check_(((boxc_l2*)(R->Thing))[Select].L);
		else;
	else;

	return 0;
}
_BOXC_ general *BoxC_RS_Read_(BOXC_VS _PL_ R,ADDRESS Select,LOGICAL Mode)
{
	if(R)
		if(Select<R->Number)
			if(R->Count[Select])
				return (((boxc_l2*)(R->Thing))[Select].L[Mode&1]->L[0]);
			else;
		else;
	else;

	return NULL;
}

static address _BoxC_RS_Zeros_(address T)
{
	address C=0;

	for(T^=T-1,T>>=1;T;T>>=1,C++);

	return C;
}
static address _BoxC_RS_GCD_(address M,address N)
{
	ADDRESS S=_BoxC_RS_Zeros_(M|N);

	M>>=S;
	N>>=S;
	M>>=_BoxC_RS_Zeros_(M);

	__dlOuOlb__
	{
		N>>=_BoxC_RS_Zeros_(N);
		if(M>N)
		{
			ADDRESS T=M-N;

			M=N;
			N=T;
		}
		else if(M<N)
			N-=M;
		else
			return (M<<S);
	}
}
static general _BoxC_RS_Spread_(general **Slot,BOXC_L2 *_PL_ Ring,ADDRESS Count,SINTPTR Rotation,LOGICAL Mode)
{
	SINTPTR Mask=(Rotation>0);
	SINTPTR Nega=Mask^1;
	SINTPTR Step=1-(Mask<<1);
	BOXC_L2 *Here=Ring[Mask];
	BOXC_L2 *Prop=_BoxC_L2_Twist_(Ring[Nega],Here->L[1]);
	
	for(GENERAL _PL_ _PL_ End=Slot+Count;Slot<End;Slot++)
	{
		MemC_Temp_(boxc_l2,Temp)
		{
			Temp.L[Mask]=(boxc_l2*)Here;
			Temp.L[Nega]=_BoxC_L2_Twist_(Prop,Here->L[1]);

			*Slot=Temp.L[Mode]->L[0];
		}
		for(sintptr Iter=Rotation;Iter;Iter+=Step)
		{
			BOXC_L2 _PL_ Temp=Prop;

			Prop=_BoxC_L2_Twist_(Here,Prop->L[1]);
			Here=Temp;
		}
	}
}
_BOXC_ address BoxC_RS_Spread_(MEMC_MS _PL_ MS,BOXC_VS _PL_ RS,ADDRESS Select,sintptr Rotation,LOGICAL Mode)
{
	if(MS)
		if(RS)
			if(Select<RS->Number)
				if(RS->Count[Select])
				{
					address Return;

					if(Rotation)
					{
						ADDRESS Count=RS->Count[Select];

						Rotation%=Acs_(sintptr,Count);
						Return=(Rotation<0)?(-Rotation):(+Rotation);
						Return=_BoxC_RS_GCD_(Count,Return);
						Return=Count/Return;
					}
					else
						Return=1;

					if(Return>MS->Nums)
						Return=0;
					else
						_BoxC_RS_Spread_(MS->Slot.P,((boxc_l2*)(RS->Thing))[Select].L,Return,Rotation,Mode);

					return Return;
				}
				else;
			else;
		else;
	else;

	return 0;
}

#undef _BoxC_L2_Twist_
#endif

#if(Fold_(Part:BoxC_KS))
MemC_Func_Declare_(integer,boxc_c_,BOXC_C_,GENERAL _PL_,GENERAL _PL_);
MemC_Type_Declare_(struct,boxc_kn,BOXC_KN);
struct _boxc_kn
{
	general *Key;
	general *Value;
	address Height;
	address Weight;
	boxc_kn *Leaf[2];
};

static inline integer _BoxC_KN_Comp_(GENERAL _PL_ A,GENERAL _PL_ B)
{
	return ((A>B)-(A<B));
}
static inline address _BoxC_KN_Height_Old_(BOXC_KN _PL_ Node)
{
	return ((Node)?(Node->Height):(0));
}
static inline general _BoxC_KN_Height_New_(boxc_kn _PL_ Node)
{
	ADDRESS H0=_BoxC_KN_Height_Old_(Node->Leaf[0]);
	ADDRESS H1=_BoxC_KN_Height_Old_(Node->Leaf[1]);

	Node->Height=(H0>H1)?(H0):(H1);
	Node->Height++;
}
static inline sintptr _BoxC_KN_Height_Bal_(BOXC_KN _PL_ Node)
{
	return ((Node)?(_BoxC_KN_Height_Old_(Node->Leaf[0])-_BoxC_KN_Height_Old_(Node->Leaf[1])):(0));
}
static inline address _BoxC_KN_Weight_Old_(BOXC_KN _PL_ Node)
{
	return ((Node)?(Node->Weight):(0));
}
static inline general _BoxC_KN_Weight_New_(boxc_kn _PL_ Node)
{
	ADDRESS W0=_BoxC_KN_Weight_Old_(Node->Leaf[0]);
	ADDRESS W1=_BoxC_KN_Weight_Old_(Node->Leaf[1]);

	Node->Weight=W0+W1;
	Node->Weight++;
}
static boxc_kn *_BoxC_KN_Deeper_(boxc_kn *Node)
{
	while(Node->Height>1)
		Node=Node->Leaf[_BoxC_KN_Height_Old_(Node->Leaf[0])<_BoxC_KN_Height_Old_(Node->Leaf[1])];

	return Node;
}
static boxc_kn *_BoxC_KN_Diving_(boxc_kn *Node)
{
	while(Node->Leaf[0])
		Node=Node->Leaf[0];

	return Node;
}
static boxc_kn *_BoxC_KN_Verify_(BOXC_C_ Comp_,boxc_kn *Node,GENERAL _PL_ Key)
{
	while(Node)
	{
		INTEGER Comp=Comp_(Key,Node->Key);

		if(Comp)
			Node=Node->Leaf[Comp>0];
		else
			break;
	}

	return Node;
}
static boxc_kn *_BoxC_KN_Search_(boxc_kn *Node,ADDRESS Index)
{
	for(address Offset=0;1;)
	{
		ADDRESS Temp=Offset+_BoxC_KN_Weight_Old_(Node->Leaf[0]);

		if(Index<Temp)
			Node=Node->Leaf[0];
		else if(Index>Temp)
		{
			Node=Node->Leaf[1];
			Offset=Temp+1;
		}
		else
			return Node;
	}
}
static memclip _BoxC_KN_Locate_(BOXC_C_ Comp_,boxc_kn *Node,GENERAL _PL_ Key)
{
	memclip Index={.V=0};

	__dlOuOlb__
	{
		INTEGER Comp=Comp_(Key,Node->Key);

		if(Comp<0)
			if(Node->Leaf[0])
				Node=Node->Leaf[0];
			else
				goto WRONG;
		else if(Comp>0)
			if(Node->Leaf[1])
			{
				if(Node->Leaf[0])
					Index.V+=Node->Leaf[0]->Weight;
				else;

				Index.V++;
				Node=Node->Leaf[1];
			}
			else
			{
WRONG:
				Index.P=FULL;
				break;
			}
		else
			break;
	}
	
	return Index;
}
static general _BoxC_KN_Travel_(BOXC_KN _PL_ Node,memclip *List)
{
	if(Node->Leaf[0])
	{
		_BoxC_KN_Travel_(Node->Leaf[0],List);
		List+=Node->Leaf[0]->Weight;
	}
	else;

	List->P=Node->Key;

	if(Node->Leaf[1])
		_BoxC_KN_Travel_(Node->Leaf[1],List+1);
	else;
}
static boxc_kn *_BoxC_KN_Rotate_(boxc_kn _PL_ Node,LOGICAL Mode)
{
	INTEGER Togg=Mode^1;
	boxc_kn _PL_ Leaf=Node->Leaf[Togg];
	boxc_kn _PL_ Temp=Leaf->Leaf[Mode];

	Leaf->Leaf[Mode]=Node;
	Node->Leaf[Togg]=Temp;

	_BoxC_KN_Height_New_(Node);
	_BoxC_KN_Weight_New_(Node);

	_BoxC_KN_Height_New_(Leaf);
	_BoxC_KN_Weight_New_(Leaf);

	return Leaf;
}

static boxc_kn *_BoxC_KN_Insert_(boxc_kn _PL_,BOXC_C_,boxc_kn*,general _PL_);
static boxc_kn *_BoxC_KN_Desert_(boxc_kn _PL_,BOXC_C_,boxc_kn*,GENERAL _PL_);
static boxc_kn *_BoxC_KN_Create_(boxc_kn _PL_ Pair,general _PL_ Key)
{
	boxc_kn *Node;

	if(Pair)
	{
		Node=_BoxC_KN_Deeper_(Pair);
		_BoxC_KN_Desert_(NULL,_BoxC_KN_Comp_,Pair,Node);

		Node->Key=Key;
		Node->Value=NULL;
	}
	else
	{
		Node=Key;

		Node->Key=Key;
		Node->Height=1;
		Node->Weight=1;
		Node->Leaf[0]=NULL;
		Node->Leaf[1]=NULL;
	}

	return Node;
}
static general _BoxC_KN_Delete_(boxc_kn _PL_ Pair,boxc_kn _PL_ Node)
{
	if(Pair)
		_BoxC_KN_Insert_(NULL,_BoxC_KN_Comp_,Pair,Node);
	else;
}
static boxc_kn *_BoxC_KN_Insert_(boxc_kn _PL_ Pair,BOXC_C_ Comp_,boxc_kn *Node,general _PL_ Key)
{
	if(Node)
	{
		integer Comp=Comp_(Key,Node->Key);
		logical Mode=(Comp>0);

		Node->Leaf[Mode]=_BoxC_KN_Insert_(Pair,Comp_,Node->Leaf[Mode],Key);

		_BoxC_KN_Height_New_(Node);
		_BoxC_KN_Weight_New_(Node);
		{
			SINTPTR Balance=_BoxC_KN_Height_Bal_(Node);

			switch(Balance)
			{
			default:
				Mode=(Balance<0)?((Comp=+Comp_(Key,Node->Leaf[1]->Key)),1):((Comp=-Comp_(Key,Node->Leaf[0]->Key)),0);
				if(Comp)
				{
					if(Comp<0)
						Node->Leaf[Mode]=_BoxC_KN_Rotate_(Node->Leaf[Mode],Mode);
					else;

					Node=_BoxC_KN_Rotate_(Node,Mode^1);
				}
				else
			case-1:case 0:case+1:;
			}
		}
	}
	else
		Node=_BoxC_KN_Create_(Pair,Key);

	return Node;
}
static boxc_kn *_BoxC_KN_Desert_(boxc_kn _PL_ Pair,BOXC_C_ Comp_,boxc_kn *Node,GENERAL _PL_ Key)
{
	if(Node)
	{
		integer Comp=Comp_(Key,Node->Key);

		if(Comp)
		{
			LOGICAL Mode=(Comp>0);

			Node->Leaf[Mode]=_BoxC_KN_Desert_(Pair,Comp_,Node->Leaf[Mode],Key);
		}
		else
		{
			INTEGER Mode=((Node->Leaf[0])?(1):(0))|((Node->Leaf[1])?(2):(0));

			switch(Mode)
			{
			case 0:
				_BoxC_KN_Delete_(Pair,Node);

				return NULL;
			case 1:
			case 2:
				{
					boxc_kn _PL_ Leaf=Node->Leaf[Mode>>1];

					*Node=*Leaf;
					_BoxC_KN_Delete_(Pair,Leaf);
				}
				break;
			default:
				{
					boxc_kn _PL_ Leaf=_BoxC_KN_Diving_(Node->Leaf[1]);

					Node->Key=Leaf->Key;
					Node->Leaf[1]=_BoxC_KN_Desert_(Pair,Comp_,Node->Leaf[1],Leaf->Key);
				}
			}
		}
		_BoxC_KN_Height_New_(Node);
		_BoxC_KN_Weight_New_(Node);
		{
			sintptr Balance=_BoxC_KN_Height_Bal_(Node);

			switch(Balance)
			{
			default:
				{
					LOGICAL Mode=(Balance<0)?((Balance=+_BoxC_KN_Height_Bal_(Node->Leaf[1])),1):((Balance=-_BoxC_KN_Height_Bal_(Node->Leaf[0])),0);

					if(Balance>0)
						Node->Leaf[Mode]=_BoxC_KN_Rotate_(Node->Leaf[Mode],Mode);
					else;

					Node=_BoxC_KN_Rotate_(Node,Mode^1);
				}
			case-1:case 0:case+1:;
			}
		}
	}
	else;

	return Node;
}

static general _BoxC_KS_Setup_(BOXC_KS _PL_ Head)
{
	boxc_kn *_PL_ Root=(boxc_kn**)(((boxc_l2*)(Head->Key))->L);

	Root[0]=NULL;
	Root[1]=NULL;

	for(boxc_kn *Ptr=(boxc_kn*)(Root+2),_PL_ End=Ptr+(Head->Capacity);Ptr<End;Ptr++)
		Root[0]=_BoxC_KN_Insert_(NULL,_BoxC_KN_Comp_,Root[0],Ptr);
}
_BOXC_ boxc_ks *BoxC_KS_Create_(BOXC_C_ Comp_,ADDRESS Capacity)
{
	boxc_ks *Head;

	if(Capacity)
	{
		ADDRESS Temp=MemC.Size.Mul_(Capacity,sizeof(boxc_kn));

		Head=(Temp)?(MemC.Alloc.Byte_(MemC.Size.Add_(Temp,sizeof(boxc_ks)+sizeof(boxc_l2)))):(NULL);
	}
	else
		Head=MemC.Alloc.Byte_(sizeof(boxc_ks)+sizeof(boxc_l2));

	if(Head)
	{
		Acs_(boxc_l2*,Head->Key)=(boxc_l2*)(Head+1);
		Acs_(boxc_c_,Head->Comp_)=(Comp_)?(Comp_):(_BoxC_KN_Comp_);
		Acs_(address,Head->Number)=0;
		Acs_(address,Head->Capacity)=Capacity;

		_BoxC_KS_Setup_(Head);
	}
	else;

	return Head;
}
_BOXC_ address BoxC_KS_Size_(BOXC_KS _PL_ Head)
{
	return ((Head)?(sizeof(boxc_ks)+sizeof(boxc_l2)+MemC_Size_(boxc_kn,Head->Capacity)):(0));
}
_BOXC_ logical BoxC_KS_Reset_(boxc_ks _PL_ Head)
{
	if(Head)
	{
		Acs_(address,Head->Number)=0;

		_BoxC_KS_Setup_(Head);

		return 1;
	}
	else
		return 0;
}

_BOXC_ logical BoxC_KS_Insert_(boxc_ks _PL_ Head,general _PL_ Key)
{
	if(Head)
		if((Head->Number)<(Head->Capacity))
		{
			boxc_kn *_PL_ Root=(boxc_kn**)(((boxc_l2*)(Head->Key))->L);

			if(_BoxC_KN_Verify_(Head->Comp_,Root[1],Key));
			else
			{
				Root[1]=_BoxC_KN_Insert_(Root[0],Head->Comp_,Root[1],Key);
				Acs_(address,Head->Number)++;

				return 1;
			}
		}
		else;
	else;

	return 0;
}
_BOXC_ logical BoxC_KS_Desert_(boxc_ks _PL_ Head,GENERAL _PL_ Key)
{
	if(Head)
	{
		boxc_kn *_PL_ Root=(boxc_kn**)(((boxc_l2*)(Head->Key))->L);

		if(_BoxC_KN_Verify_(Head->Comp_,Root[1],Key))
		{
			Root[1]=_BoxC_KN_Desert_(Root[0],Head->Comp_,Root[1],Key);
			Acs_(address,Head->Number)--;

			return 1;
		}
		else;
	}
	else;

	return 0;
}
_BOXC_ logical BoxC_KS_Verify_(BOXC_KS _PL_ Head,GENERAL _PL_ Key)
{
	if(Head)
	{
		boxc_kn _PL_ _PL_ Root=(boxc_kn**)(((boxc_l2*)(Head->Key))->L);

		if(_BoxC_KN_Verify_(Head->Comp_,Root[1],Key))
			return 1;
		else;
	}
	else;

	return 0;
}

_BOXC_ logical BoxC_KS_Writer_(BOXC_KS _PL_ Head,GENERAL _PL_ Key,general _PL_ Value)
{
	if(Head)
	{
		boxc_kn _PL_ _PL_ Root=(boxc_kn**)(((boxc_l2*)(Head->Key))->L);
		boxc_kn _PL_ Node=_BoxC_KN_Verify_(Head->Comp_,Root[1],Key);

		if(Node)
		{
			Node->Value=Value;

			return 1;
		}
		else;
	}
	else;

	return 0;
}
_BOXC_ general *BoxC_KS_Reader_(BOXC_KS _PL_ Head,GENERAL _PL_ Key)
{
	if(Head)
	{
		boxc_kn _PL_ _PL_ Root=(boxc_kn**)(((boxc_l2*)(Head->Key))->L);
		boxc_kn _PL_ Node=_BoxC_KN_Verify_(Head->Comp_,Root[1],Key);

		if(Node)
			return Node->Value;
		else;
	}
	else;

	return NULL;
}

_BOXC_ general *BoxC_KS_Search_(BOXC_KS _PL_ Head,ADDRESS Index)
{
	if(Head)
		if(Index<Head->Number)
		{
			boxc_kn _PL_ _PL_ Root=(boxc_kn**)(((boxc_l2*)(Head->Key))->L);

			return (_BoxC_KN_Search_(Root[1],Index)->Key);
		}
		else;
	else;

	return NULL;
}
_BOXC_ address BoxC_KS_Locate_(BOXC_KS _PL_ Head,GENERAL _PL_ Key)
{
	memclip Return;

	if(Head)
	{
		boxc_kn _PL_ _PL_ Root=(boxc_kn**)(((boxc_l2*)(Head->Key))->L);

		Return=_BoxC_KN_Locate_(Head->Comp_,Root[1],Key);
	}
	else
		Return.P=FULL;

	return Return.V;
}

_BOXC_ address BoxC_KS_Spread_(MEMC_MS _PL_ MS,BOXC_KS _PL_ KS)
{
	if(MS)
		if(KS)
			if((MS->Nums)<(KS->Number));
			else
			{
				BOXC_KN _PL_ _PL_ Root=(boxc_kn**)(((boxc_l2*)(KS->Key))->L);

				_BoxC_KN_Travel_(Root[1],MS->Cell);

				return (Root[1]->Weight);
			}
		else;
	else;

	return 0;
}
#endif

#if(Fold_(Part:BoxC_FS))
_BOXC_ boxc_fs *BoxC_FS_Create_(ADDRESS Number)
{
	boxc_fs *F;

	MemC_Temp_(ADDRESS,Size=MemC.Size.Add_(Number,7))
		F=(Size)?(MemC.Alloc.Byte_(MemC.Size.Add_(Size>>3,sizeof(boxc_fs)))):(NULL);

	if(F)
	{
		Acs_(general*,F->Flag)=(Number)?(MemC_Clear_1D_((byte_08*)(F+1),(Number+7)>>3)):(NULL);
		Acs_(address,F->Number)=Number;
	}
	else;

	return F;
}
_BOXC_ address BoxC_FS_Size_(BOXC_FS _PL_ F)
{
	return (F)?(((F->Number+7)>>3)+sizeof(boxc_fs)):(0);
}
_BOXC_ logical BoxC_FS_Reset_All_(BOXC_FS _PL_ F)
{
	if(F)
	{
		if(F->Number)
			MemC_Clear_1D_((byte_08*)(F->Flag),(F->Number+7)>>3);
		else;

		return 1;
	}
	else
		return 0;
}

_BOXC_ general BoxC_FS_Writer_(BOXC_FS _PL_ F,ADDRESS Select,LOGICAL Mode)
{
	if(F)
		if(Select<F->Number)
		{
			byte_08 _PL_ Flag=((byte_08*)(F->Flag))+(Select>>3);
			byte_08 Mask=1<<(Select&7);
			byte_08 Temp=(byte_08)Mode;

			*Flag|=Mask;
			Mask=~Mask;
			Temp=-Temp;
			Mask|=Temp;
			*Flag&=Mask;
		}
		else;
	else;
}
_BOXC_ logical BoxC_FS_Reader_(BOXC_FS _PL_ F,ADDRESS Select)
{
	if(F)
		if(Select<F->Number)
			return (logical)((((byte_08*)(F->Flag))[Select>>3]>>(Select&7))&1);
		else;
	else;

	return 0;
}
_BOXC_ general BoxC_FS_Toggle_(BOXC_FS _PL_ F,ADDRESS Select)
{
	if(F)
		if(Select<F->Number)
			((byte_08*)(F->Flag))[Select>>3]^=1<<(Select&7);
		else;
	else;
}
#endif

#if(Fold_(Part:BoxC_Tr))
static general _BoxC_Tr_Init_(boxc_tr _PL_ Root,ADDRESS Chunks)
{
	boxc_tr *_R_ Ptr=Root->Leaf;

	if(Chunks>1)
	{
		boxc_tr _PL_ First=Ptr;
		boxc_tr _PL_ Last=Ptr+(Chunks-1);

		{
			Acs_(boxc_tr*,Ptr->Root)=Root;
			Acs_(boxc_tr*,Ptr->Leaf)=NULL;
			Acs_(boxc_tr*,Ptr->Prev)=Last;
			Acs_(boxc_tr*,Ptr->Next)=Ptr+1;
			Acs_(address,Ptr->Count)=0;
			Acs_(address,Ptr->Total)=0;
		}
		for(Ptr=Ptr->Next;Ptr<Last;Ptr=Ptr->Next)
		{
			Acs_(boxc_tr*,Ptr->Root)=Root;
			Acs_(boxc_tr*,Ptr->Leaf)=NULL;
			Acs_(boxc_tr*,Ptr->Prev)=Ptr-1;
			Acs_(boxc_tr*,Ptr->Next)=Ptr+1;
			Acs_(address,Ptr->Count)=0;
			Acs_(address,Ptr->Total)=0;
		}
		{
			Acs_(boxc_tr*,Ptr->Root)=Root;
			Acs_(boxc_tr*,Ptr->Leaf)=NULL;
			Acs_(boxc_tr*,Ptr->Prev)=Ptr-1;
			Acs_(boxc_tr*,Ptr->Next)=First;
			Acs_(address,Ptr->Count)=0;
			Acs_(address,Ptr->Total)=0;
		}
	}
	else
	{
		Acs_(boxc_tr*,Ptr->Root)=Root;
		Acs_(boxc_tr*,Ptr->Leaf)=NULL;
		Acs_(boxc_tr*,Ptr->Prev)=Ptr;
		Acs_(boxc_tr*,Ptr->Next)=Ptr;
		Acs_(address,Ptr->Count)=0;
		Acs_(address,Ptr->Total)=0;
	}
}
static boxc_tr *_BoxC_Tr_Most_Root_(boxc_tr *_R_ Ptr)
{
	for(;Ptr->Root;Ptr=Ptr->Root);

	return Ptr;
}
static boxc_tr *_BoxC_Tr_Most_Leaf_(boxc_tr *_R_ Ptr)
{
	for(;Ptr->Leaf;Ptr=Ptr->Leaf);
	Acs_(general*,Ptr->Link)=NULL;
	Ptr->Object=NULL;

	return Ptr;
}
static general _BoxC_Tr_Swap_(boxc_tr _PL_ This,boxc_tr _PL_ Root)
{
	if(This==This->Next)
		Acs_(boxc_tr*,This->Root->Leaf)=NULL;
	else
	{
		Acs_(boxc_tr*,This->Root->Leaf)=This->Next;
		Acs_(boxc_tr*,This->Prev->Next)=This->Next;
		Acs_(boxc_tr*,This->Next->Prev)=This->Prev;
	}
	if(Root->Leaf)
	{
		Acs_(boxc_tr*,This->Prev)=Root->Leaf->Prev;
		Acs_(boxc_tr*,This->Next)=Root->Leaf;

		Acs_(boxc_tr*,This->Prev->Next)=This;
		Acs_(boxc_tr*,This->Next->Prev)=This;
	}
	else
	{
		Acs_(boxc_tr*,This->Prev)=This;
		Acs_(boxc_tr*,This->Next)=This;
	}
	{
		Acs_(boxc_tr*,This->Root)=Root;
		Acs_(boxc_tr*,Root->Leaf)=This;
	}
}
static general _BoxC_Tr_Numb_Inc_(boxc_tr *_R_ Ptr)
{
	ADDRESS Increment=Ptr->Total+1;

	Ptr=Ptr->Root;
	for(Acs_(address,Ptr->Count)++;Ptr;Ptr=Ptr->Root)
		Acs_(address,Ptr->Total)+=Increment;
}
static general _BoxC_Tr_Numb_Dec_(boxc_tr *_R_ Ptr)
{
	ADDRESS Decrement=Ptr->Total+1;

	Ptr=Ptr->Root;
	for(Acs_(address,Ptr->Count)--;Ptr;Ptr=Ptr->Root)
		Acs_(address,Ptr->Total)-=Decrement;
}
_BOXC_ boxc_tr *BoxC_Tr_Create_(boxc_tr _PL_ Root,ADDRESS Capacity)
{
	boxc_tr *Tree;

	if(Root)
		if(Capacity)
			Tree=NULL;
		else
		{
			boxc_tr *Origin=_BoxC_Tr_Most_Root_(Root);

			if(Origin<(boxc_tr*)(Origin->Link))
			{
				Origin=Origin->Link;
				if(Origin->Count)
				{
					Tree=_BoxC_Tr_Most_Leaf_(Origin);

					_BoxC_Tr_Numb_Dec_(Tree);
					_BoxC_Tr_Swap_(Tree,Root);
					_BoxC_Tr_Numb_Inc_(Tree);
				}
				else
					Tree=NULL;
			}
			else
				Tree=NULL;
		}
	else
	{
		Tree=MemC.Alloc.Byte_(MemC.Size.Mul_(MemC.Size.Add_(Capacity,2),sizeof(boxc_tr)));
		if(Tree)
		{
			{
				Acs_(boxc_tr*,Tree[0].Root)=NULL;
				Acs_(boxc_tr*,Tree[0].Leaf)=NULL;
				Acs_(boxc_tr*,Tree[0].Prev)=Tree;
				Acs_(boxc_tr*,Tree[0].Next)=Tree;
				Acs_(general*,Tree[0].Link)=Tree+1;
				Tree[0].Object=NULL;
				Acs_(address,Tree[0].Count)=0;
				Acs_(address,Tree[0].Total)=0;
			}
			{
				Acs_(boxc_tr*,Tree[1].Root)=NULL;
				Acs_(BOXC_TR*,Tree[1].Prev)=Tree[0].Link;
				Acs_(BOXC_TR*,Tree[1].Next)=Tree[0].Link;
				Acs_(general*,Tree[1].Link)=Tree;
				Tree[1].Object=NULL;
				Acs_(address,Tree[1].Count)=Capacity;
				Acs_(address,Tree[1].Total)=Capacity;
			}
			if(Capacity)
			{
				Acs_(boxc_tr*,Tree[1].Leaf)=Tree+2;
				_BoxC_Tr_Init_(Tree+1,Capacity);
			}
			else
				Acs_(boxc_tr*,Tree[1].Leaf)=NULL;
		}
		else;
	}

	return Tree;
}
_BOXC_ general BoxC_Tr_Delete_(boxc_tr *_PL_ Tree)
{
	if(*Tree)
		if((*Tree)->Root)
		{
			boxc_tr _PL_ Root=(*Tree)->Root;
			boxc_tr _PL_ Origin=_BoxC_Tr_Most_Root_(Root);

			if(Origin<(boxc_tr*)(Origin->Link))
			{
				_BoxC_Tr_Numb_Dec_(*Tree);
				_BoxC_Tr_Swap_(*Tree,Origin->Link);
				_BoxC_Tr_Numb_Inc_(*Tree);

				(*Tree)=Root;
			}
			else
				(*Tree)=Origin->Link;
		}
		else
		{
			if((*Tree)>(boxc_tr*)((*Tree)->Link))
				*Tree=(*Tree)->Link;
			else;

			MemC_Deloc_(*Tree);
		}
	else;
}
_BOXC_ address BoxC_Tr_Size_(BOXC_TR *Tree)
{
	address Return;

	if(Tree)
	{
		Tree=_BoxC_Tr_Most_Root_((boxc_tr*)Tree);
		Return=MemC_Size_(boxc_tr,Tree->Total+((boxc_tr*)(Tree->Link))->Total+2);
	}
	else
		Return=0;

	return Return;
}
_BOXC_ address BoxC_Tr_Used_(BOXC_TR _PL_ Tree)
{
	if(Tree)
	{
		BOXC_TR _PL_ Origin=_BoxC_Tr_Most_Root_((boxc_tr*)Tree);

		if(Origin<(boxc_tr*)(Origin->Link))
			return MemC_Size_(boxc_tr,Tree->Total+1);
		else;
	}
	else;

	return 0;
}

_BOXC_ address BoxC_Tr_Left_(BOXC_TR _PL_ Tree)
{
	if(Tree)
	{
		boxc_tr *Origin=_BoxC_Tr_Most_Root_((boxc_tr*)Tree);

		if(Origin<(boxc_tr*)(Origin->Link))
			Origin=Origin->Link;
		else;

		return Origin->Total;
	}
	else
		return 0;
}
_BOXC_ boxc_tr *BoxC_Tr_Origin_(boxc_tr _PL_ Tree)
{
	boxc_tr *Return;

	if(Tree)
	{
		Return=_BoxC_Tr_Most_Root_(Tree);
		if(Return>(boxc_tr*)(Return->Link))
			Return=Return->Link;
		else;
	}
	else
		Return=NULL;

	return Return;
}
_BOXC_ address BoxC_Tr_Height_(BOXC_TR *Tree)
{
	if(Tree)
	{
		address Height;

		for(Height=0;Tree->Root;Tree=Tree->Root,Height++);
		if(Tree>(boxc_tr*)(Tree->Link));
		else
			return Height;
	}
	else;

	return 0;
}

static logical _BoxC_Tr_Okay_(BOXC_TR *Source,BOXC_TR *Target)
{
	if(Source)
		if(Target)
		{
			while(Target->Root)
				if(Source==Target)
					return 0;
				else
					Target=Target->Root;

			if(Source==Target)
				return 0;
			else;

			if(Target>(boxc_tr*)(Target->Link))
				return 0;
			else;

			for(;Source->Root;Source=Source->Root);

			return (Source==Target);
		}
		else;
	else;

	return 0;
}
_BOXC_ logical BoxC_Tr_Move_(boxc_tr _PL_ Tree,boxc_tr _PL_ Root)
{
	if(_BoxC_Tr_Okay_(Tree,Root))
	{
		_BoxC_Tr_Numb_Dec_(Tree);
		_BoxC_Tr_Swap_(Tree,Root);
		_BoxC_Tr_Numb_Inc_(Tree);

		return 1;
	}
	else
		return 0;
}
#endif

#if(Fold_(Part:BoxC_Sw))
static logical _BoxC_Sw_Comp_(GENERAL _PL_ A,GENERAL _PL_ B)
{
	return (A>B);
}
static address _BoxC_Sw_Count_(ADDRESS _PL_ Slot)
{
	address Count=0;

	for(ADDRESS *_R_ Ptr=Slot+1,_PL_ End=Ptr+(*Slot);Ptr<End;Ptr++)
		if(*Ptr)
			Count++;
		else;

	return Count;
}
static general _BoxC_Sw_Compact_(ADDRESS _PL_ Slot,address *_R_ PtrL,address *_R_ PtrI)
{
	*(PtrL++)=0;
	*(PtrI++)=0;
	for(ADDRESS *_R_ PtrS=Slot+1,_PL_ End=PtrS+(*Slot);PtrS<End;PtrS++)
		if(*PtrS)
		{
			*(PtrL++)=*PtrS;
			*(PtrI++)=PtrS-Slot;
		}
		else;
}
static general _BoxC_Sw_Take_(general _PL_ *_R_ PtrL,ADDRESS *_R_ PtrI,boxclip *_R_ PtrC,ADDRESS Nums)
{
	for(BOXCLIP _PL_ End=PtrC+Nums;PtrC<End;PtrL++,PtrI++,PtrC++)
	{
		PtrC->L=*PtrL;
		PtrC->I=*PtrI;
	}
}
static logical _BoxC_Sw_Unique_(GENERAL _PL_ *_R_ Ptr,ADDRESS Valid)
{
	for(GENERAL _PL_ _PL_ End=Ptr+Valid;Ptr<End;Ptr++)
		if(Ptr[0]==Ptr[1])
			return 0;
		else;

	return 1;
}
_BOXC_ boxc_sw *BoxC_Sw_Create_(MEMC_MS _PL_ MS)
{
	boxc_sw *Switch;

	if(MS)
		if(MS->Nums)
			if((MS->Slot.V[0])<(MS->Nums))
			{
				ADDRESS Valid=_BoxC_Sw_Count_(MS->Slot.V);
				ADDRESS Number=Valid+1;

				MemC_Temp_(ADDRESS,Temp=MemC.Size.Mul_(Number,sizeof(boxclip)))
					Switch=(Temp)?(MemC.Alloc.Byte_(MemC.Size.Add_(Temp,sizeof(boxc_sw)))):(NULL);

				if(Switch)
				{
					boxclip _PL_ Case=(boxclip*)(Switch+1);

					Acs_(boxclip*,Switch->Case)=Case;
					Acs_(address,Switch->Number)=Number;
					MemC_Temp_ND_(general*,Space,KILL:_BoxC_VS_Delete_((boxc_vs**)(&Switch));,1,Number<<1)
					{
						general *_PL_ TableL=Space;
						address _PL_ TableI=(address*)(TableL+Number);

						_BoxC_Sw_Compact_(MS->Slot.V,(address*)TableL,TableI);

						if(MemC.Sort.Do_(_BoxC_Sw_Comp_,TableL,TableI,(address*)Case,Number))
							if(_BoxC_Sw_Unique_(TableL,Valid))
								_BoxC_Sw_Take_(TableL,TableI,Case,Number);
							else
								goto KILL;
						else
							goto KILL;
					}
				}
				else;
			}
			else
				Switch=NULL;
		else
			Switch=NULL;
	else
		Switch=NULL;

	return Switch;
}
_BOXC_ address BoxC_Sw_Size_(BOXC_SW _PL_ Switch)
{
	return ((Switch)?(sizeof(boxc_sw)+MemC_Size_(boxclip,Switch->Number)):(0));
}

_BOXC_ address BoxC_Sw_Find_(BOXC_SW _PL_ Switch,GENERAL _PL_ Key,LOGICAL Mode)
{
	if(Switch)
		if(Mode)
		{
			boxclip Scope=*((BOXCLIP*)Switch);

			__dlOuOlb__
			{
				ADDRESS Pick=Scope.I>>1;
				BOXCLIP _PL_ Case=((boxclip*)(Scope.L))+Pick;

				if(Pick)
					if(Key<(Case->L))
						Scope.I=Pick;
					else if(Key>(Case->L))
					{
						ADDRESS Offset=Pick+1;

						Acs_(boxclip*,Scope.L)+=Offset;
						Scope.I-=Offset;
					}
					else
						return (Case->I);
				else if(Key==(Case->L))
					return (Case->I);
				else
					break;
			}
		}
		else
			for(BOXCLIP *_R_ Case=Switch->Case,_PL_ End=Case+(Switch->Number);Case<End;Case++)
				if(Key==(Case->L))
					return (Case->I);
				else;
	else;

	return (address)FULL;
}
#endif

#undef _BOXC_
#endif

#if(Fold_(Library Casing))
BOXCASE BoxC=
{
	.Version=IdiomVersion,
	.SS=
	{
		.Create_=MemC_Func_Casting_(boxc_ss*,BoxC_SS_Create_,ADDRESS,ADDRESS),
		.Delete_=MemC_Func_Casting_(general,_BoxC_VS_Delete_,boxc_ss *_PL_),
		.Size_=MemC_Func_Casting_(address,BoxC_SS_Size_,BOXC_SS _PL_),
		.Reset_All_=MemC_Func_Casting_(logical,BoxC_SS_Reset_All_,BOXC_SS _PL_),
		.Reset_=MemC_Func_Casting_(logical,BoxC_SS_Reset_,BOXC_SS _PL_,ADDRESS),
		.Push_=MemC_Func_Casting_(logical,BoxC_SS_Push_,BOXC_SS _PL_,ADDRESS,general _PL_),
		.Pop_=MemC_Func_Casting_(general*,BoxC_SS_Pop_,BOXC_SS _PL_,ADDRESS),
		.Spread_=MemC_Func_Casting_(address,BoxC_SS_Spread_,MEMC_MS _PL_,BOXC_SS _PL_,ADDRESS),
		.Check_=MemC_Func_Casting_(logical,BoxC_SS_Check_,BOXC_SS _PL_,ADDRESS),
		.Peek_=MemC_Func_Casting_(general*,BoxC_SS_Peek_,BOXC_SS _PL_,ADDRESS,ADDRESS)
	},
	.QS=
	{
		.Create_=MemC_Func_Casting_(boxc_qs*,BoxC_QS_Create_,ADDRESS,ADDRESS),
		.Delete_=MemC_Func_Casting_(general,_BoxC_VS_Delete_,boxc_qs *_PL_),
		.Size_=MemC_Func_Casting_(address,BoxC_QS_Size_,BOXC_QS _PL_),
		.Reset_All_=MemC_Func_Casting_(logical,BoxC_QS_Reset_All_,BOXC_QS _PL_),
		.Reset_=MemC_Func_Casting_(logical,BoxC_QS_Reset_,BOXC_QS _PL_,ADDRESS),
		.Enque_=MemC_Func_Casting_(logical,BoxC_QS_Enque_,BOXC_QS _PL_,ADDRESS,general _PL_),
		.Deque_=MemC_Func_Casting_(general*,BoxC_QS_Deque_,BOXC_QS _PL_,ADDRESS),
		.Spread_=MemC_Func_Casting_(address,BoxC_QS_Spread_,MEMC_MS _PL_,BOXC_QS _PL_,ADDRESS),
		.Check_=MemC_Func_Casting_(logical,BoxC_QS_Check_,BOXC_QS _PL_,ADDRESS),
		.Peek_=MemC_Func_Casting_(general*,BoxC_QS_Peek_,BOXC_QS _PL_,ADDRESS,ADDRESS)
	},
	.RS=
	{
		.Create_=MemC_Func_Casting_(boxc_rs*,BoxC_RS_Create_,ADDRESS,ADDRESS),
		.Delete_=MemC_Func_Casting_(general,_BoxC_VS_Delete_,boxc_rs *_PL_),
		.Size_=MemC_Func_Casting_(address,BoxC_RS_Size_,BOXC_RS _PL_),
		.Reset_All_=MemC_Func_Casting_(logical,BoxC_RS_Reset_All_,BOXC_RS _PL_),
		.Reset_=MemC_Func_Casting_(logical,BoxC_RS_Reset_,BOXC_RS _PL_,ADDRESS),
		.Insert_=MemC_Func_Casting_(logical,BoxC_RS_Insert_,BOXC_RS _PL_,ADDRESS,general _PL_,LOGICAL),
		.Desert_=MemC_Func_Casting_(logical,BoxC_RS_Desert_,BOXC_RS _PL_,ADDRESS,LOGICAL),
		.Rotate_=MemC_Func_Casting_(logical,BoxC_RS_Rotate_,BOXC_RS _PL_,ADDRESS,SINTPTR),
		.Check_=MemC_Func_Casting_(logical,BoxC_RS_Check_,BOXC_RS _PL_,ADDRESS),
		.Read_=MemC_Func_Casting_(general*,BoxC_RS_Read_,BOXC_RS _PL_,ADDRESS,LOGICAL),
		.Spread_=MemC_Func_Casting_(address,BoxC_RS_Spread_,MEMC_MS _PL_,BOXC_RS _PL_,ADDRESS,SINTPTR,LOGICAL)
	},
	.KS=
	{
		.Create_=BoxC_KS_Create_,
		.Delete_=MemC_Func_Casting_(general,_BoxC_VS_Delete_,boxc_ks *_PL_),
		.Size_=BoxC_KS_Size_,
		.Reset_=BoxC_KS_Reset_,
		.Key=
		{
			.Enroll_=BoxC_KS_Insert_,
			.Remove_=BoxC_KS_Desert_,
			.Verify_=BoxC_KS_Verify_,
			.Spread_=BoxC_KS_Spread_
		},
		.Value=
		{
			.Writer_=BoxC_KS_Writer_,
			.Reader_=BoxC_KS_Reader_
		},
		.Index=
		{
			.Search_=BoxC_KS_Search_,
			.Locate_=BoxC_KS_Locate_
		}
	},
	.FS=
	{
		.Create_=BoxC_FS_Create_,
		.Delete_=MemC_Func_Casting_(general,_BoxC_VS_Delete_,boxc_fs *_PL_),
		.Size_=BoxC_FS_Size_,
		.Reset_All_=BoxC_FS_Reset_All_,
		.Writer_=BoxC_FS_Writer_,
		.Reader_=BoxC_FS_Reader_,
		.Toggle_=BoxC_FS_Toggle_
	},
	.Tr=
	{
		.Create_=BoxC_Tr_Create_,
		.Delete_=BoxC_Tr_Delete_,
		.Size_=BoxC_Tr_Size_,
		.Used_=BoxC_Tr_Used_,
		.Left_=BoxC_Tr_Left_,
		.Origin_=BoxC_Tr_Origin_,
		.Height_=BoxC_Tr_Height_,
		.Move_=BoxC_Tr_Move_
	},
	.Sw=
	{
		.Create_=BoxC_Sw_Create_,
		.Delete_=MemC_Func_Casting_(general,_BoxC_VS_Delete_,boxc_sw *_PL_),
		.Size_=BoxC_Sw_Size_,
		.Find_=BoxC_Sw_Find_
	}
};
BOXCASE *BoxC_(general) { return &BoxC; }
#endif
