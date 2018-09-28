#include "boxclip.h"

#if(MemC_Fold_(Definition:Internal Opaque Types))
MemC_Type_Declare_(struct,boxc_l2,BOXC_L2);
struct _boxc_l2 { boxc_l2 *L[2]; };
#endif

#if(MemC_Fold_(Definition:Internal Macros))
#define _BoxC_L2_Twist_(A,B) ((boxc_l2*)(((address)(A))^((address)(B))))
#endif

#if(MemC_Fold_(Definition:Global Constants))
static BYTE_08 IdiomVersion[16]="Date:2018.09.27";
BYTE_08 _PL_ BoxClip=IdiomVersion;
#endif

#if(MemC_Fold_(Definition:BoxClip Structure Functions))
#if(MemC_Fold_(Part:BoxC_L2))
static general _BoxC_L2_Assign_(boxc_l2 *_R_ Ptr,BOXC_L2 _PL_ Last)
{
	for(;Ptr<Last;Ptr[-1].L[1]=Ptr)
		Ptr++;

	Ptr[0].L[1]=NULL;
}
static integer _BoxC_L2_Check_(BOXC_L2 *_R_ Ptr)
{
	while(Ptr)
		if(Ptr->L[0])
			Ptr=Ptr->L[1];
		else
			break;

	return (Ptr==NULL);
}
static general *_BoxC_L2_Peek_(BOXC_L2 *_R_ Ptr,address Index)
{
	while(Index--)
		Ptr=Ptr->L[1];

	return Ptr->L[0];
}
#endif
#if(MemC_Fold_(Part:BoxC_SS))
static general _BoxC_SS_Setup_(BOXC_SS _PL_ S)
{
	boxc_l2 *_PL_ Stack=(boxc_l2**)(S->Stack);
	address _PL_ Count=(address*)(S->Count);

	if(S->Number)
	{
		MemC_Clear_1D_(Stack,S->Number,boxc_l2*);
		MemC_Clear_1D_(Count,S->Number,address);
	}
	Count[-1]=S->Capacity;

	if(S->Capacity)
	{
		Stack[-1]=(boxc_l2*)(Stack+S->Number);
		_BoxC_L2_Assign_(Stack[-1],Stack[-1]+(S->Capacity-1));
	}
	else
		Stack[-1]=NULL;
}
boxc_ss *BoxC_SS_Create_(ADDRESS Number,ADDRESS Capacity)
{
	boxc_ss *S;

	{
		address Size=_MemC_Size_Mul_(Number+1,sizeof(boxc_l2*)+sizeof(address));

		if(Size)
			if(Capacity)
			{
				ADDRESS Temp=_MemC_Size_Mul_(Capacity,sizeof(boxc_l2));

				if(Temp)
				{
					Size=_MemC_Size_Add_(Size,Temp);

					S=(Size)?(MemC_Alloc_Byte_(_MemC_Size_Add_(Size,sizeof(boxc_ss)))):(NULL);
				}
				else
					S=NULL;
			}
			else
				S=MemC_Alloc_Byte_(_MemC_Size_Add_(Size,sizeof(boxc_ss)));
		else
			S=NULL;
	}
	if(S)
	{
		Acs_(address*,S->Count)=(address*)(S+1)+1;
		Acs_(boxc_l2**,S->Stack)=(boxc_l2**)(S->Count+Number)+1;

		Acs_(address,S->Number)=Number;
		Acs_(address,S->Capacity)=Capacity;

		_BoxC_SS_Setup_(S);
	}

	return S;
}
general BoxC_SS_Delete_(boxc_ss *_PL_ S)
{
	if(*S)
		MemC_Deloc_(*S);
}
address BoxC_SS_Size_(BOXC_SS _PL_ S)
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
integer BoxC_SS_Push_(BOXC_SS _PL_ S,ADDRESS Select,general *Contents)
{
	integer Return;

	if(S)
		if(Select<S->Number)
			if(S->Count[-1])
			{
				boxc_l2 *_PL_ Stack=(boxc_l2**)(S->Stack);
				address _PL_ Count=(address*)(S->Count);

				_BoxC_SS_Swap_(Stack-1,Stack+Select,&Contents);

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
general *BoxC_SS_Pop_(BOXC_SS _PL_ S,ADDRESS Select)
{
	general *Return;

	if(S)
		if(Select<S->Number)
			if(S->Count[Select])
			{
				boxc_l2 *_PL_ Stack=(boxc_l2**)(S->Stack);
				address _PL_ Count=(address*)(S->Count);

				_BoxC_SS_Swap_(Stack+Select,Stack-1,&Return);

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

static general _BoxC_SS_Reset_(boxc_l2 *_PL_ Source,boxc_l2 *_PL_ Target)
{
	boxc_l2 *Temp;

	for(Temp=*Source;Temp->L[1];Temp=Temp->L[1]);
	Temp->L[1]=*Target;

	*Target=*Source;
	*Source=NULL;
}
integer BoxC_SS_Reset_(BOXC_SS _PL_ S,ADDRESS Select)
{
	integer Return;

	if(S)
		if(Select<S->Number)
			if(S->Count[Select])
			{
				boxc_l2 *_PL_ Stack=(boxc_l2**)(S->Stack);
				address _PL_ Count=(address*)(S->Count);

				_BoxC_SS_Reset_(Stack+Select,Stack-1);

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
integer BoxC_SS_Reset_All_(BOXC_SS _PL_ S)
{
	integer Return;

	if(S)
	{
		_BoxC_SS_Setup_(S);

		Return=1;
	}
	else
		Return=0;

	return Return;
}

integer BoxC_SS_Check_(BOXC_SS _PL_ S,ADDRESS Select)
{
	integer Return;

	if(S)
		if(Select<S->Number)
			Return=_BoxC_L2_Check_(((boxc_l2**)(S->Stack))[Select]);
		else
			Return=0;
	else
		Return=0;

	return Return;
}
general *BoxC_SS_Peek_(BOXC_SS _PL_ S,ADDRESS Select,ADDRESS Index)
{
	general *Return;

	if(S)
		if(Select<S->Number)
			if(Index<S->Count[Select])
				Return=_BoxC_L2_Peek_(((boxc_l2**)(S->Stack))[Select],Index);
			else
				Return=NULL;
		else
			Return=NULL;
	else
		Return=NULL;

	return Return;
}
#endif
#if(MemC_Fold_(Part:BoxC_QS))
static general _BoxC_QS_Setup_(BOXC_QS _PL_ Q)
{
	boxc_l2 _PL_ Queue=(boxc_l2*)(Q->Queue);
	address _PL_ Count=(address*)(Q->Count);

	if(Q->Number)
	{
		MemC_Clear_1D_(Queue,Q->Number,boxc_l2);
		MemC_Clear_1D_(Count,Q->Number,address);
	}
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
boxc_qs *BoxC_QS_Create_(ADDRESS Number,ADDRESS Capacity)
{
	boxc_qs *Q;

	{
		address Size=_MemC_Size_Mul_(Number+1,sizeof(boxc_l2)+sizeof(address));

		if(Size)
			if(Capacity)
			{
				ADDRESS Temp=_MemC_Size_Mul_(Capacity,sizeof(boxc_l2));

				if(Temp)
				{
					Size=_MemC_Size_Add_(Size,Temp);

					Q=(Size)?(MemC_Alloc_Byte_(_MemC_Size_Add_(Size,sizeof(boxc_qs)))):(NULL);
				}
				else
					Q=NULL;
			}
			else
				Q=MemC_Alloc_Byte_(_MemC_Size_Add_(Size,sizeof(boxc_qs)));
		else
			Q=NULL;
	}
	if(Q)
	{
		Acs_(address*,Q->Count)=(address*)(Q+1)+1;
		Acs_(boxc_l2*,Q->Queue)=(boxc_l2*)(Q->Count+Number)+1;

		Acs_(address,Q->Number)=Number;
		Acs_(address,Q->Capacity)=Capacity;

		_BoxC_QS_Setup_(Q);
	}

	return Q;
}
general BoxC_QS_Delete_(boxc_qs *_PL_ Q)
{
	if(*Q)
		MemC_Deloc_(*Q);
}
address BoxC_QS_Size_(BOXC_QS _PL_ Q)
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
integer BoxC_QS_Enque_(BOXC_QS _PL_ Q,ADDRESS Select,general *Contents)
{
	integer Return;

	if(Q)
		if(Select<Q->Number)
			if(Q->Count[-1])
			{
				boxc_l2 _PL_ Queue=(boxc_l2*)(Q->Queue);
				address _PL_ Count=(address*)(Q->Count);

				_BoxC_QS_Swap_(Queue[-1].L,Queue[Select].L,&Contents);

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
general *BoxC_QS_Deque_(BOXC_QS _PL_ Q,ADDRESS Select)
{
	general *Return;

	if(Q)
		if(Select<Q->Number)
			if(Q->Count[Select])
			{
				boxc_l2 _PL_ Queue=(boxc_l2*)(Q->Queue);
				address _PL_ Count=(address*)(Q->Count);

				_BoxC_QS_Swap_(Queue[Select].L,Queue[-1].L,&Return);

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
integer BoxC_QS_Reset_(BOXC_QS _PL_ Q,ADDRESS Select)
{
	integer Return;

	if(Q)
		if(Select<Q->Number)
			if(Q->Count[Select])
			{
				boxc_l2 _PL_ Queue=(boxc_l2*)(Q->Queue);
				address _PL_ Count=(address*)(Q->Count);

				_BoxC_QS_Reset_(Queue[Select].L,Queue[-1].L);

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
integer BoxC_QS_Reset_All_(BOXC_QS _PL_ Q)
{
	integer Return;

	if(Q)
	{
		boxc_l2 _PL_ Queue=(boxc_l2*)(Q->Queue);
		address _PL_ Count=(address*)(Q->Count);
		address Select;

		for(Select=0;Select<Q->Number;Select++)
			if(Count[Select])
			{
				_BoxC_QS_Reset_(Queue[Select].L,Queue[-1].L);

				Count[-1]+=Count[Select];
				Count[Select]=0;
			}
		Return=1;
	}
	else
		Return=0;

	return Return;
}

integer BoxC_QS_Check_(BOXC_QS _PL_ Q,ADDRESS Select)
{
	integer Return;

	if(Q)
		if(Select<Q->Number)
			Return=_BoxC_L2_Check_(((boxc_l2*)(Q->Queue))[Select].L[0]);
		else
			Return=0;
	else
		Return=0;

	return Return;
}
general *BoxC_QS_Peek_(BOXC_QS _PL_ Q,ADDRESS Select,ADDRESS Index)
{
	general *Return;

	if(Q)
		if(Select<Q->Number)
			if(Index<Q->Count[Select])
				Return=_BoxC_L2_Peek_(((boxc_l2*)(Q->Queue))[Select].L[0],Index);
			else
				Return=NULL;
		else
			Return=NULL;
	else
		Return=NULL;

	return Return;
}
#endif
#if(MemC_Fold_(Part:BoxC_RS))
static general _BoxC_RS_Assign_(boxc_l2 *_R_ Ptr,BOXC_L2 _PL_ Last)
{
	for(Ptr++;Ptr<Last;Ptr++)
		Ptr->L[1]=_BoxC_L2_Twist_(Ptr-1,Ptr+1);
}
static general _BoxC_RS_Setup_(BOXC_RS _PL_ R)
{
	boxc_l2 _PL_ Ring=(boxc_l2*)(R->Ring);
	address _PL_ Count=(address*)(R->Count);

	if(R->Number)
	{
		MemC_Clear_1D_(Ring,R->Number,boxc_l2);
		MemC_Clear_1D_(Count,R->Number,address);
	}
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
boxc_rs *BoxC_RS_Create_(ADDRESS Number,ADDRESS Capacity)
{
	boxc_rs *R;

	{
		address Size=_MemC_Size_Mul_(Number+1,sizeof(boxc_l2)+sizeof(address));

		if(Size)
			if(Capacity)
			{
				ADDRESS Temp=_MemC_Size_Mul_(Capacity,sizeof(boxc_l2));

				if(Temp)
				{
					Size=_MemC_Size_Add_(Size,Temp);

					R=(Size)?(MemC_Alloc_Byte_(_MemC_Size_Add_(Size,sizeof(boxc_rs)))):(NULL);
				}
				else
					R=NULL;
			}
			else
				R=MemC_Alloc_Byte_(_MemC_Size_Add_(Size,sizeof(boxc_rs)));
		else
			R=NULL;
	}
	if(R)
	{
		Acs_(address*,R->Count)=(address*)(R+1)+1;
		Acs_(boxc_l2*,R->Ring)=(boxc_l2*)(R->Count+Number)+1;

		Acs_(address,R->Number)=Number;
		Acs_(address,R->Capacity)=Capacity;

		_BoxC_RS_Setup_(R);
	}

	return R;
}
general BoxC_RS_Delete_(boxc_rs *_PL_ R)
{
	if(*R)
		MemC_Deloc_(*R);
}
address BoxC_RS_Size_(BOXC_RS _PL_ R)
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

static general _BoxC_RS_Swap_(boxc_l2 *_PL_ Source,boxc_l2 *_PL_ Target,general *_PL_ Port)
{
	boxc_l2 _PL_ Here=Source[1];

	if(Source[0]==Source[1])
	{
		Source[0]=NULL;
		Source[1]=NULL;
	}
	else
	{
		boxc_l2 _PL_ Next=_BoxC_L2_Twist_(Here->L[1],Source[0]);
		boxc_l2 _PL_ Prev=_BoxC_L2_Twist_(Here->L[1],Next);

		Next->L[1]=_BoxC_L2_Twist_(Next->L[1],_BoxC_L2_Twist_(Here,Prev));
		Prev->L[1]=_BoxC_L2_Twist_(Prev->L[1],_BoxC_L2_Twist_(Here,Next));

		Source[1]=Next;
	}
	{
		general _PL_ Temp=*Port;

		*Port=Here->L[0];
		Here->L[0]=Temp;
		Here->L[1]=_BoxC_L2_Twist_(Target[0],Target[1]);
	}
	if(Target[0])
	{
		Target[0]->L[1]=_BoxC_L2_Twist_(Target[0]->L[1],_BoxC_L2_Twist_(Here,Target[1]));
		Target[1]->L[1]=_BoxC_L2_Twist_(Target[1]->L[1],_BoxC_L2_Twist_(Here,Target[0]));
	}
	else
		Target[1]=Here;
	Target[0]=Here;
}
integer BoxC_RS_Insert_(BOXC_RS _PL_ R,ADDRESS Select,general *Contents)
{
	integer Return;

	if(R)
		if(Select<R->Number)
			if(R->Count[-1])
			{
				boxc_l2 _PL_ Ring=(boxc_l2*)(R->Ring);
				address _PL_ Count=(address*)(R->Count);

				_BoxC_RS_Swap_(Ring[-1].L,Ring[Select].L,&Contents);

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
general *BoxC_RS_Desert_(BOXC_RS _PL_ R,ADDRESS Select)
{
	general *Return;

	if(R)
		if(Select<R->Number)
			if(R->Count[Select])
			{
				boxc_l2 _PL_ Ring=(boxc_l2*)(R->Ring);
				address _PL_ Count=(address*)(R->Count);

				_BoxC_RS_Swap_(Ring[Select].L,Ring[-1].L,&Return);

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

static general _BoxC_RS_Rotate_(BOXC_L2 *_PL_ Ring,integer Rotation)
{
	INTEGER Mask=(Rotation>=0);
	INTEGER Nega=Mask^1;
	INTEGER Step=1-(Mask<<1);
	BOXC_L2 *Here=Ring[Mask];
	BOXC_L2 *Prop=_BoxC_L2_Twist_(Ring[Nega],Here->L[1]);
	BOXC_L2 *Temp;

	for(;Rotation;Rotation+=Step)
	{
		Temp=Prop;
		Prop=_BoxC_L2_Twist_(Here,Prop->L[1]);
		Here=Temp;
	}
	{
		Ring[Mask]=Here;
		Ring[Nega]=_BoxC_L2_Twist_(Prop,Here->L[1]);
	}
}
integer BoxC_RS_Rotate_(BOXC_RS _PL_ R,ADDRESS Select,INTEGER Rotation)
{
	integer Return;

	if(R)
		if(Select<R->Number)
			if(R->Count[Select])
			{
				_BoxC_RS_Rotate_(((boxc_l2*)(R->Ring))[Select].L,Rotation);

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
integer BoxC_RS_Reset_(BOXC_RS _PL_ R,ADDRESS Select)
{
	integer Return;

	if(R)
		if(Select<R->Number)
			if(R->Count[Select])
			{
				boxc_l2 _PL_ Ring=(boxc_l2*)(R->Ring);
				address _PL_ Count=(address*)(R->Count);

				_BoxC_RS_Reset_(Ring[Select].L,Ring[-1].L);

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
integer BoxC_RS_Reset_All_(BOXC_RS _PL_ R)
{
	integer Return;

	if(R)
	{
		boxc_l2 _PL_ Ring=(boxc_l2*)(R->Ring);
		address _PL_ Count=(address*)(R->Count);
		address Select;

		for(Select=0;Select<R->Number;Select++)
			if(Count[Select])
			{
				_BoxC_RS_Reset_(Ring[Select].L,Ring[-1].L);

				Count[-1]+=Count[Select];
				Count[Select]=0;
			}
		Return=1;
	}
	else
		Return=0;

	return Return;
}

static integer _BoxC_RS_Check_(BOXC_L2 _PL_ _PL_ Ring)
{
	integer Return;

	if(Ring[0]==Ring[1])
		Return=(Ring[0]->L[0]!=NULL);
	else
	{
		BOXC_L2 *Here=Ring[1];
		BOXC_L2 *Next=_BoxC_L2_Twist_(Ring[0],Here->L[1]);
		BOXC_L2 *Temp;

		while(Next!=Ring[1])
			if(Here->L[0])
			{
				Temp=Next;
				Next=_BoxC_L2_Twist_(Here,Next->L[1]);
				Here=Temp;
			}
			else
				break;

		Return=(Next==Ring[1]);
	}

	return Return;
}
integer BoxC_RS_Check_(BOXC_RS _PL_ R,ADDRESS Select)
{
	integer Return;

	if(R)
		if(Select<R->Number)
			Return=_BoxC_RS_Check_(((boxc_l2*)(R->Ring))[Select].L);
		else
			Return=0;
	else
		Return=0;

	return Return;
}
general *BoxC_RS_Read_(BOXC_RS _PL_ R,ADDRESS Select)
{
	general *Return;

	if(R)
		if(Select<R->Number)
			if(R->Count[Select])
				Return=((boxc_l2*)(R->Ring))[Select].L[1]->L[0];
			else
				Return=NULL;
		else
			Return=NULL;
	else
		Return=NULL;

	return Return;
}
#endif
#endif

