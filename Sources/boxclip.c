﻿#include "boxclip.h"

#if(MemC_Fold_(Definition:Global Constants))
static BYTE_08 IdiomVersion[16]="Date:2018.10.19";
BYTE_08 _PL_ BoxClip=IdiomVersion;
#endif

#if(MemC_Fold_(Definition:BoxClip Structure Functions))
#if(MemC_Fold_(Part:BoxC_L2))
MemC_Type_Declare_(struct,boxc_l2,BOXC_L2);
struct _boxc_l2 { boxc_l2 *L[2]; };

static general _BoxC_L2_Assign_(boxc_l2 *_R_ Ptr,BOXC_L2 _PL_ Last)
{
	for(;Ptr<Last;Ptr[-1].L[1]=Ptr)
		Ptr++;

	Ptr[0].L[1]=NULL;
}
static boolean _BoxC_L2_Check_(BOXC_L2 *_R_ Ptr)
{
	while(Ptr)
		if(Ptr->L[0])
			Ptr=Ptr->L[1];
		else
			break;

	return BitCBool[Ptr==NULL];
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
		MemC_Clear_1D_(Stack,S->Number);
		MemC_Clear_1D_(Count,S->Number);
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
boolean BoxC_SS_Push_(BOXC_SS _PL_ S,ADDRESS Select,general *Contents)
{
	if(S)
		if(Select<S->Number)
			if(S->Count[-1])
			{
				boxc_l2 *_PL_ Stack=(boxc_l2**)(S->Stack);
				address _PL_ Count=(address*)(S->Count);

				_BoxC_SS_Swap_(Stack-1,Stack+Select,&Contents);

				Count[-1]--;
				Count[Select]++;

				goto SUCCESS;
			}
			else
				goto FAILURE;
		else
			goto FAILURE;
	else
		goto FAILURE;
FAILURE:
	return BitCNull;
SUCCESS:
	return BitCFull;
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
boolean BoxC_SS_Reset_(BOXC_SS _PL_ S,ADDRESS Select)
{
	if(S)
		if(Select<S->Number)
			if(S->Count[Select])
			{
				boxc_l2 *_PL_ Stack=(boxc_l2**)(S->Stack);
				address _PL_ Count=(address*)(S->Count);

				_BoxC_SS_Reset_(Stack+Select,Stack-1);

				Count[-1]+=Count[Select];
				Count[Select]=0;

				goto SUCCESS;
			}
			else
				goto SUCCESS;
		else
			goto FAILURE;
	else
		goto FAILURE;
FAILURE:
	return BitCNull;
SUCCESS:
	return BitCFull;
}
boolean BoxC_SS_Reset_All_(BOXC_SS _PL_ S)
{
	return (S)?(_BoxC_SS_Setup_(S),BitCFull):(BitCNull);
}

boolean BoxC_SS_Check_(BOXC_SS _PL_ S,ADDRESS Select)
{
	return (S)?((Select<S->Number)?(_BoxC_L2_Check_(((boxc_l2**)(S->Stack))[Select])):(BitCNull)):(BitCNull);
}
general *BoxC_SS_Peek_(BOXC_SS _PL_ S,ADDRESS Select,ADDRESS Index)
{
	return (S)?((Select<S->Number)?((Index<S->Count[Select])?(_BoxC_L2_Peek_(((boxc_l2**)(S->Stack))[Select],Index)):(NULL)):(NULL)):(NULL);
}
#endif

#if(MemC_Fold_(Part:BoxC_QS))
static general _BoxC_QS_Setup_(BOXC_QS _PL_ Q)
{
	boxc_l2 _PL_ Queue=(boxc_l2*)(Q->Queue);
	address _PL_ Count=(address*)(Q->Count);

	if(Q->Number)
	{
		MemC_Clear_1D_(Queue,Q->Number);
		MemC_Clear_1D_(Count,Q->Number);
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
boolean BoxC_QS_Enque_(BOXC_QS _PL_ Q,ADDRESS Select,general *Contents)
{
	if(Q)
		if(Select<Q->Number)
			if(Q->Count[-1])
			{
				boxc_l2 _PL_ Queue=(boxc_l2*)(Q->Queue);
				address _PL_ Count=(address*)(Q->Count);

				_BoxC_QS_Swap_(Queue[-1].L,Queue[Select].L,&Contents);

				Count[-1]--;
				Count[Select]++;

				goto SUCCESS;
			}
			else
				goto FAILURE;
		else
			goto FAILURE;
	else
		goto FAILURE;
FAILURE:
	return BitCNull;
SUCCESS:
	return BitCFull;
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
boolean BoxC_QS_Reset_(BOXC_QS _PL_ Q,ADDRESS Select)
{
	if(Q)
		if(Select<Q->Number)
			if(Q->Count[Select])
			{
				boxc_l2 _PL_ Queue=(boxc_l2*)(Q->Queue);
				address _PL_ Count=(address*)(Q->Count);

				_BoxC_QS_Reset_(Queue[Select].L,Queue[-1].L);

				Count[-1]+=Count[Select];
				Count[Select]=0;

				goto SUCCESS;
			}
			else
				goto SUCCESS;
		else
			goto FAILURE;
	else
		goto FAILURE;
FAILURE:
	return BitCNull;
SUCCESS:
	return BitCFull;
}
boolean BoxC_QS_Reset_All_(BOXC_QS _PL_ Q)
{
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
		goto SUCCESS;
	}
	else
		goto FAILURE;
FAILURE:
	return BitCNull;
SUCCESS:
	return BitCFull;
}

boolean BoxC_QS_Check_(BOXC_QS _PL_ Q,ADDRESS Select)
{
	return (Q)?((Select<Q->Number)?(_BoxC_L2_Check_(((boxc_l2*)(Q->Queue))[Select].L[0])):(BitCNull)):(BitCNull);
}
general *BoxC_QS_Peek_(BOXC_QS _PL_ Q,ADDRESS Select,ADDRESS Index)
{
	return (Q)?((Select<Q->Number)?((Index<Q->Count[Select])?(_BoxC_L2_Peek_(((boxc_l2*)(Q->Queue))[Select].L[0],Index)):(NULL)):(NULL)):(NULL);
}
#endif

#if(MemC_Fold_(Part:BoxC_RS))
#define _BoxC_L2_Twist_(A,B) ((boxc_l2*)(((address)(A))^((address)(B))))

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
		MemC_Clear_1D_(Ring,R->Number);
		MemC_Clear_1D_(Count,R->Number);
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

static general _BoxC_RS_Swap_(boxc_l2 *_PL_ Source,boxc_l2 *_PL_ Target,general *_PL_ Port,INTEGER Posi)
{
	INTEGER Nega=Posi^1;
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
boolean BoxC_RS_Insert_(BOXC_RS _PL_ R,ADDRESS Select,general *Contents,BOOLEAN Mode)
{
	if(R)
		if(Select<R->Number)
			if(R->Count[-1])
			{
				boxc_l2 _PL_ Ring=(boxc_l2*)(R->Ring);
				address _PL_ Count=(address*)(R->Count);

				_BoxC_RS_Swap_(Ring[-1].L,Ring[Select].L,&Contents,Mode&1);

				Count[-1]--;
				Count[Select]++;

				goto SUCCESS;
			}
			else
				goto FAILURE;
		else
			goto FAILURE;
	else
		goto FAILURE;
FAILURE:
	return BitCNull;
SUCCESS:
	return BitCFull;
}
boolean BoxC_RS_Desert_(BOXC_RS _PL_ R,ADDRESS Select,BOOLEAN Mode)
{
	if(R)
		if(Select<R->Number)
			if(R->Count[Select])
			{
				boxc_l2 _PL_ Ring=(boxc_l2*)(R->Ring);
				address _PL_ Count=(address*)(R->Count);
				general *Temp;

				_BoxC_RS_Swap_(Ring[Select].L,Ring[-1].L,&Temp,Mode&1);

				Count[-1]++;
				Count[Select]--;

				goto SUCCESS;
			}
			else
				goto FAILURE;
		else
			goto FAILURE;
	else
		goto FAILURE;
FAILURE:
	return BitCNull;
SUCCESS:
	return BitCFull;
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
boolean BoxC_RS_Rotate_(BOXC_RS _PL_ R,ADDRESS Select,INTEGER Rotation)
{
	if(R)
		if(Select<R->Number)
			if(R->Count[Select])
			{
				_BoxC_RS_Rotate_(((boxc_l2*)(R->Ring))[Select].L,Rotation);

				goto SUCCESS;
			}
			else
				goto SUCCESS;
		else
			goto FAILURE;
	else
		goto FAILURE;
FAILURE:
	return BitCNull;
SUCCESS:
	return BitCFull;
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
boolean BoxC_RS_Reset_(BOXC_RS _PL_ R,ADDRESS Select)
{
	if(R)
		if(Select<R->Number)
			if(R->Count[Select])
			{
				boxc_l2 _PL_ Ring=(boxc_l2*)(R->Ring);
				address _PL_ Count=(address*)(R->Count);

				_BoxC_RS_Reset_(Ring[Select].L,Ring[-1].L);

				Count[-1]+=Count[Select];
				Count[Select]=0;

				goto SUCCESS;
			}
			else
				goto SUCCESS;
		else
			goto FAILURE;
	else
		goto FAILURE;
FAILURE:
	return BitCNull;
SUCCESS:
	return BitCFull;
}
boolean BoxC_RS_Reset_All_(BOXC_RS _PL_ R)
{
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
		goto SUCCESS;
	}
	else
		goto FAILURE;
FAILURE:
	return BitCNull;
SUCCESS:
	return BitCFull;
}

static boolean _BoxC_RS_Check_(BOXC_L2 _PL_ _PL_ Ring)
{
	boolean Return;

	if(Ring[0]==Ring[1])
		Return=BitCBool[Ring[0]->L[0]!=NULL];
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

		Return=BitCBool[Next==Ring[1]];
	}

	return Return;
}
boolean BoxC_RS_Check_(BOXC_RS _PL_ R,ADDRESS Select)
{
	return (R)?((Select<R->Number)?(_BoxC_RS_Check_(((boxc_l2*)(R->Ring))[Select].L)):(BitCNull)):(BitCNull);
}
general *BoxC_RS_Read_(BOXC_RS _PL_ R,ADDRESS Select,BOOLEAN Mode)
{
	return (R)?((Select<R->Number)?((R->Count[Select])?(((boxc_l2*)(R->Ring))[Select].L[Mode&1]->L[0]):(NULL)):(NULL)):(NULL);
}

#undef _BoxC_L2_Twist_
#endif

#if(MemC_Fold_(Part:BoxC_FS))
boxc_fs *BoxC_FS_Create_(ADDRESS Number)
{
	boxc_fs *F;

	{
		ADDRESS Size=_MemC_Size_Add_(Number,7);

		F=(Size)?(MemC_Alloc_Byte_(_MemC_Size_Add_(Size>>3,sizeof(boxc_fs)))):(NULL);
	}
	if(F)
	{
		Acs_(general*,F->Flag)=(Number)?(MemC_Clear_1D_((byte_08*)(F+1),(Number+7)>>3)):(NULL);
		Acs_(address,F->Number)=Number;
	}

	return F;
}
general BoxC_FS_Delete_(boxc_fs *_PL_ F)
{
	if(*F)
		MemC_Deloc_(*F);
}
address BoxC_FS_Size_(BOXC_FS _PL_ F)
{
	return (F)?(((F->Number+7)>>3)+sizeof(boxc_fs)):(0);
}

general BoxC_FS_Writer_(BOXC_FS _PL_ F,ADDRESS Select,BOOLEAN Bool)
{
	if(F)
		if(Select<F->Number)
		{
			byte_08 _PL_ Flag=((byte_08*)(F->Flag))+(Select>>3);
			byte_08 Mask=1<<(Select&7);

			*Flag|=Mask;
			Mask=~Mask;
			Mask|=Bool;
			*Flag&=Mask;
		}
}
boolean BoxC_FS_Reader_(BOXC_FS _PL_ F,ADDRESS Select)
{
	return (F)?((Select<F->Number)?(BitCBool[(((byte_08*)(F->Flag))[Select>>3]>>(Select&7))&1]):(BitCNull)):(BitCNull);
}
general BoxC_FS_Toggle_(BOXC_FS _PL_ F,ADDRESS Select)
{
	if(F)
		if(Select<F->Number)
			((byte_08*)(F->Flag))[Select>>3]^=1<<(Select&7);
}
#endif

#if(MemC_Fold_(Part:BoxC_Tr))
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
boxc_tr *BoxC_Tr_Create_(boxc_tr _PL_ Root,ADDRESS Capacity)
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
		Tree=MemC_Alloc_Byte_(_MemC_Size_Mul_(_MemC_Size_Add_(Capacity,2),sizeof(boxc_tr)));
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
	}

	return Tree;
}
general BoxC_Tr_Delete_(boxc_tr *_PL_ Tree)
{
	if(*Tree)
		if((*Tree)->Root)
		{
			boxc_tr _PL_ Root=(*Tree)->Root;
			boxc_tr *Origin=_BoxC_Tr_Most_Root_(Root);

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
			MemC_Deloc_(*Tree);
		}
}
address BoxC_Tr_Size_(BOXC_TR *Tree)
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
address BoxC_Tr_Used_(BOXC_TR _PL_ Tree)
{
	address Return;

	if(Tree)
	{
		BOXC_TR _PL_ Origin=_BoxC_Tr_Most_Root_((boxc_tr*)Tree);

		Return=(Origin<(boxc_tr*)(Origin->Link))?(MemC_Size_(boxc_tr,Tree->Total+1)):(0);
	}
	else
		Return=0;

	return Return;
}

address BoxC_Tr_Left_(BOXC_TR _PL_ Tree)
{
	address Return;

	if(Tree)
	{
		boxc_tr *Origin=_BoxC_Tr_Most_Root_((boxc_tr*)Tree);

		if(Origin<(boxc_tr*)(Origin->Link))
			Origin=Origin->Link;

		Return=Origin->Total;
	}
	else
		Return=0;

	return Return;
}
boxc_tr *BoxC_Tr_Origin_(boxc_tr _PL_ Tree)
{
	boxc_tr *Return;

	if(Tree)
	{
		Return=_BoxC_Tr_Most_Root_(Tree);
		if(Return>(boxc_tr*)(Return->Link))
			Return=Return->Link;
	}
	else
		Return=NULL;

	return Return;
}
address BoxC_Tr_Height_(BOXC_TR *Tree)
{
	address Return;

	if(Tree)
	{
		for(Return=0;Tree->Root;Tree=Tree->Root,Return++);
		if(Tree>(boxc_tr*)(Tree->Link))
			Return=0;
	}
	else
		Return=0;

	return Return;
}

static boolean _BoxC_Tr_Okay_(BOXC_TR *Source,BOXC_TR *Target)
{
	if(Source)
		if(Target)
		{
			while(Target->Root)
				if(Source==Target)
					goto FAILURE;
				else
					Target=Target->Root;

			if(Source==Target)
				goto FAILURE;

			if(Target>(boxc_tr*)(Target->Link))
				goto FAILURE;

			for(;Source->Root;Source=Source->Root);

			if(Source==Target)
				goto SUCCESS;
			else
				goto FAILURE;
		}
		else
			goto FAILURE;
	else
		goto FAILURE;
FAILURE:
	return BitCNull;
SUCCESS:
	return BitCFull;
}
boolean BoxC_Tr_Move_(boxc_tr _PL_ Tree,boxc_tr _PL_ Root)
{
	if(_BoxC_Tr_Okay_(Tree,Root))
	{
		_BoxC_Tr_Numb_Dec_(Tree);
		_BoxC_Tr_Swap_(Tree,Root);
		_BoxC_Tr_Numb_Inc_(Tree);

		goto SUCCESS;
	}
	else
		goto FAILURE;
FAILURE:
	return BitCNull;
SUCCESS:
	return BitCFull;
}
#endif
#endif
