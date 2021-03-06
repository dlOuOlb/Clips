﻿#define __STDC_WANT_LIB_EXT1__ (1)
#include "boxclip.h"

#include <stdarg.h>

#if(Fold_(Internal Constants))
static const struct { BYTE_08 Version[16]; }Idiom={.Version=oBOXCLIP_INC_};
#endif

#if(Fold_(Advanced Objects))

#if(Fold_(Trivial))
static address xBoxC_Min_(register ADDRESS A,register ADDRESS B) { return ((A<B)?(A):(B)); }
static GENERAL *BoxC_Just_(GENERAL _PL_ X) { return X; }
static integer BoxC_Comp_T08_(TEXT_08 _PL_ A,TEXT_08 _PL_ B) { return strcmp(A,B); }
static integer BoxC_Comp_T16_(TEXT_16 _PL_ A,TEXT_16 _PL_ B) { return wcscmp(A,B); }
#endif

#if(Fold_(BoxC_L2))
struct _boxc_l2 { struct _boxc_l2 *L[2]; };
MemC_Type_Declare_(struct,boxc_l2,BOXC_L2);
static_assert(sizeof(boxc_l2)==(sizeof(address)<<1),"sizeof(boxc_l2) != 2*sizeof(address)");

static general xBoxC_L2_Assign_(boxc_l2 *_R_ Ptr,BOXC_L2 _PL_ Last)
{
	for(;Ptr<Last;Ptr[-1].L[1]=Ptr)
		Ptr++;

	Ptr[0].L[1]=NULL;

	return;
}
static logical xBoxC_L2_Check_(BOXC_L2 *_R_ Ptr)
{
	while(Ptr)
		if(Ptr->L[0])
			Ptr=Ptr->L[1];
		else
			return 0;

	return 1;
}
static general *xBoxC_L2_Peek_(BOXC_L2 *_R_ Ptr,register address Index) { for(;Index--;Ptr=Ptr->L[1]);return Ptr->L[0]; }
#endif

#if(Fold_(BoxC_VS))
struct _boxc_vs { general *Thing;address *Count,Number,Capacity; };
MemC_Type_Declare_(struct,boxc_vs,BOXC_VS);
static_assert(sizeof(boxc_vs)==(sizeof(address)<<2),"sizeof(boxc_vs) != 4*sizeof(address)");

static general xBoxC_VS_Delete_(boxc_vs *_PL_ _R_ V) { MemC_Deloc_(*V);return; }
static logical xBoxC_VS_Verify_(BOXC_VS _PL_ _R_ V,ADDRESS Select) { return ((V)&&(Select<(V->Number))); }
#endif

#if(Fold_(BoxC_SS))
static_assert(sizeof(boxc_vs)==sizeof(boxc_ss),"sizeof(boxc_vs) != sizeof(boxc_ss)");

static general xBoxC_SS_Setup_A_(boxc_l2 *_PL_ _R_ Stack,address _PL_ _R_ Count,ADDRESS Number,ADDRESS Capacity)
{
	Stack[-1]=NULL;
	Count[-1]=Capacity;

	if(Number)
	{
		MemC_Clear_1D_(Stack,Number);
		MemC_Clear_1D_(Count,Number);
	}
	else;

	return;
}
static general xBoxC_SS_Setup_B_(boxc_l2 *_PL_ _R_ Stack,ADDRESS Number,ADDRESS Capacity)
{
	if(Capacity)
	{
		Stack[-1]=(boxc_l2*)(Stack+Number);
		xBoxC_L2_Assign_(Stack[-1],Stack[-1]+(Capacity-1));
	}
	else;

	return;
}
static general xBoxC_SS_Setup_(BOXC_VS _PL_ _R_ S)
{
	xBoxC_SS_Setup_A_(S->Thing,S->Count,S->Number,S->Capacity);
	xBoxC_SS_Setup_B_(S->Thing,S->Number,S->Capacity);

	return;
}
static boxc_vs *xBoxC_SS_Auto_(boxc_vs _PL_ _R_ S) { xBoxC_SS_Setup_B_(S->Thing,S->Number,S->Capacity);return S; }
static boxc_vs *BoxC_SS_Create_(ADDRESS Number,ADDRESS Capacity)
{
	boxc_vs *_R_ S=NULL;

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

		xBoxC_SS_Setup_(S);
	}
	else;

	return S;
}
static address BoxC_SS_Size_(BOXC_VS _PL_ _R_ S)
{
	register address Temp;

	if(S)
	{
		Temp=S->Number+1;
		Temp=MemC_Size_(boxc_ss,1)+MemC_Size_(boxc_l2*,Temp)+MemC_Size_(address,Temp)+MemC_Size_(boxc_l2,S->Capacity);
	}
	else
		Temp=0;

	return Temp;
}

static general xBoxC_SS_Swap_(boxc_l2 *_PL_ _R_ Source,boxc_l2 *_PL_ _R_ Target,general *_PL_ _R_ Port)
{
	{
		boxc_l2 _PL_ _R_ Temp=*Source;

		*Source=Temp->L[1];
		Temp->L[1]=*Target;
		*Target=Temp;
	}
	{
		general _PL_ Temp=*Port;

		*Port=(*Target)->L[0];
		(*Target)->L[0]=Temp;
	}

	return;
}
static logical BoxC_SS_Push_(BOXC_VS _PL_ _R_ S,ADDRESS Select,general *Contents)
{
	if((xBoxC_VS_Verify_(S,Select))&&(S->Count[-1])&&(Contents))
	{
		boxc_l2 *_PL_ Stack=S->Thing;
		address _PL_ _R_ Count=S->Count;

		xBoxC_SS_Swap_(Stack-1,Stack+Select,&Contents);

		Count[-1]--;
		Count[Select]++;

		return 1;
	}
	else
		return 0;
}
static general *BoxC_SS_Pop_(BOXC_VS _PL_ _R_ S,ADDRESS Select)
{
	if((xBoxC_VS_Verify_(S,Select))&&(S->Count[Select]))
	{
		boxc_l2 *_PL_ Stack=S->Thing;
		address _PL_ _R_ Count=S->Count;
		general *Object;

		xBoxC_SS_Swap_(Stack+Select,Stack-1,&Object);

		Count[-1]++;
		Count[Select]--;

		return Object;
	}
	else
		return NULL;
}
static logical BoxC_SS_Spread_(boxc_li _PL_ _R_ Li,BOXC_VS _PL_ _R_ SS,ADDRESS Select)
{
	if((Li)&&(xBoxC_VS_Verify_(SS,Select)))
	{
		boxc_l2 *_PL_ Stack=SS->Thing;
		address _PL_ _R_ Count=SS->Count;
		ADDRESS Number=Acs_(address,Li->Count)=xBoxC_Min_(Li->Capacity,SS->Count[Select]);

		MemC_Temp_(boxc_l2,*_PL_ From=Stack+Select,*_PL_ Into=Stack-1)
			for(general **Ptr=(general**)(Li->Item),_PL_ _PL_ End=Ptr+Number;Ptr<End;Ptr++)
				xBoxC_SS_Swap_(From,Into,Ptr);

		Count[-1]+=Number;
		Count[Select]-=Number;

		return 1;
	}
	else
		return 0;
}

static general xBoxC_SS_Reset_(boxc_l2 *_PL_ _R_ Source,boxc_l2 *_PL_ _R_ Target)
{
	{
		boxc_l2 *_R_ Temp=*Source;

		for(;Temp->L[1];Temp=Temp->L[1]);

		Temp->L[1]=*Target;
	}
	{
		*Target=*Source;
		*Source=NULL;

		return;
	}
}
static logical BoxC_SS_Reset_(BOXC_VS _PL_ _R_ S,ADDRESS Select)
{
	if(xBoxC_VS_Verify_(S,Select))
	{
		if(S->Count[Select])
		{
			boxc_l2 *_PL_ Stack=S->Thing;
			address _PL_ _R_ Count=S->Count;

			xBoxC_SS_Reset_(Stack+Select,Stack-1);

			Count[-1]+=Count[Select];
			Count[Select]=0;
		}
		else;

		return 1;
	}
	else
		return 0;
}
static logical BoxC_SS_Reset_All_(BOXC_VS _PL_ _R_ S)
{
	if(S)
	{
		xBoxC_SS_Setup_(S);

		return 1;
	}
	else
		return 0;
}

static logical BoxC_SS_Check_(BOXC_VS _PL_ _R_ S,ADDRESS Select) { return ((xBoxC_VS_Verify_(S,Select))&&(xBoxC_L2_Check_(((boxc_l2**)(S->Thing))[Select]))); }
static logical BoxC_SS_Check_All_(BOXC_VS _PL_ _R_ S)
{
	if(S)
	{
		for(BOXC_L2 _PL_ *_R_ Ptr=S->Thing,_PL_ _PL_ End=Ptr+(S->Number);Ptr<End;Ptr++)
			if(xBoxC_L2_Check_(*Ptr));
			else
				return 0;

		return 1;
	}
	else
		return 0;
}
static general *BoxC_SS_Peek_(BOXC_VS _PL_ _R_ S,ADDRESS Select,ADDRESS Index)
{
	if((xBoxC_VS_Verify_(S,Select))&&(Index<S->Count[Select]))
		return xBoxC_L2_Peek_(((boxc_l2**)(S->Thing))[Select],Index);
	else
		return NULL;
}
#endif

#if(Fold_(BoxC_QS))
static_assert(sizeof(boxc_vs)==sizeof(boxc_qs),"sizeof(boxc_vs) != sizeof(boxc_qs)");

static general xBoxC_QS_Setup_A_(boxc_l2 _PL_ _R_ Queue,address _PL_ _R_ Count,ADDRESS Number,ADDRESS Capacity)
{
	Queue[-1].L[1]=Queue[-1].L[0]=NULL;
	Count[-1]=Capacity;

	if(Number)
	{
		MemC_Clear_1D_(Queue,Number);
		MemC_Clear_1D_(Count,Number);
	}
	else;

	return;
}
static general xBoxC_QS_Setup_B_(boxc_l2 _PL_ _R_ Queue,ADDRESS Number,ADDRESS Capacity)
{
	if(Capacity)
	{
		Queue[-1].L[1]=(Queue[-1].L[0]=Queue+Number)+(Capacity-1);

		xBoxC_L2_Assign_(Queue[-1].L[0],Queue[-1].L[1]);
	}
	else;

	return;
}
static general xBoxC_QS_Setup_(BOXC_VS _PL_ _R_ Q)
{
	xBoxC_QS_Setup_A_(Q->Thing,Q->Count,Q->Number,Q->Capacity);
	xBoxC_QS_Setup_B_(Q->Thing,Q->Number,Q->Capacity);

	return;
}
static boxc_vs *xBoxC_QS_Auto_(boxc_vs _PL_ _R_ Q) { xBoxC_QS_Setup_B_(Q->Thing,Q->Number,Q->Capacity);return Q; }
static boxc_vs *BoxC_QS_Create_(ADDRESS Number,ADDRESS Capacity)
{
	boxc_vs *_R_ Q=NULL;

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

		xBoxC_QS_Setup_(Q);
	}
	else;

	return Q;
}
static address BoxC_QS_Size_(BOXC_VS _PL_ _R_ Q)
{
	register address Temp;

	if(Q)
	{
		Temp=Q->Number+1;
		Temp=MemC_Size_(boxc_qs,1)+MemC_Size_(boxc_l2,Temp)+MemC_Size_(address,Temp)+MemC_Size_(boxc_l2,Q->Capacity);
	}
	else
		Temp=0;

	return Temp;
}

static general xBoxC_QS_Swap_(boxc_l2 *_PL_ _R_ Source,boxc_l2 *_PL_ _R_ Target,general *_PL_ _R_ Port)
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

	return;
}
static logical BoxC_QS_Enque_(BOXC_VS _PL_ _R_ Q,ADDRESS Select,general *Contents)
{
	if((xBoxC_VS_Verify_(Q,Select))&&(Q->Count[-1])&&(Contents))
	{
		boxc_l2 _PL_ _R_ Queue=Q->Thing;
		address _PL_ _R_ Count=Q->Count;

		xBoxC_QS_Swap_(Queue[-1].L,Queue[Select].L,&Contents);

		Count[-1]--;
		Count[Select]++;

		return 1;
	}
	else
		return 0;
}
static general *BoxC_QS_Deque_(BOXC_VS _PL_ _R_ Q,ADDRESS Select)
{
	if((xBoxC_VS_Verify_(Q,Select))&&(Q->Count[Select]))
	{
		boxc_l2 _PL_ _R_ Queue=Q->Thing;
		address _PL_ _R_ Count=Q->Count;
		general *Object;

		xBoxC_QS_Swap_(Queue[Select].L,Queue[-1].L,&Object);

		Count[-1]++;
		Count[Select]--;

		return Object;
	}
	else
		return NULL;
}
static logical BoxC_QS_Spread_(boxc_li _PL_ _R_ Li,BOXC_VS _PL_ _R_ QS,ADDRESS Select)
{
	if((Li)&&(xBoxC_VS_Verify_(QS,Select)))
	{
		boxc_l2 _PL_ Queue=QS->Thing;
		address _PL_ _R_ Count=QS->Count;
		ADDRESS Number=Acs_(address,Li->Count)=xBoxC_Min_(Li->Capacity,QS->Count[Select]);

		MemC_Temp_(boxc_l2,_PL_ _R_ From=Queue+Select,_PL_ _R_ Into=Queue-1)
			for(general **Ptr=(general**)(Li->Item),_PL_ _PL_ End=Ptr+Number;Ptr<End;Ptr++)
				xBoxC_QS_Swap_(From->L,Into->L,Ptr);

		Count[-1]+=Number;
		Count[Select]-=Number;

		return 1;
	}
	else
		return 0;
}

static general xBoxC_QS_Reset_(boxc_l2 *_PL_ _R_ Source,boxc_l2 *_PL_ _R_ Target)
{
	if(Target[1])
		Target[1]->L[1]=Source[0];
	else
		Target[0]=Source[0];
	{
		Target[1]=Source[1];

		Source[0]=NULL;
		Source[1]=NULL;

		return;
	}
}
static logical BoxC_QS_Reset_(BOXC_VS _PL_ _R_ Q,ADDRESS Select)
{
	if(xBoxC_VS_Verify_(Q,Select))
	{
		if(Q->Count[Select])
		{
			boxc_l2 _PL_ _R_ Queue=Q->Thing;
			address _PL_ _R_ Count=Q->Count;

			xBoxC_QS_Reset_(Queue[Select].L,Queue[-1].L);

			Count[-1]+=Count[Select];
			Count[Select]=0;
		}
		else;

		return 1;
	}
	else
		return 0;
}
static logical BoxC_QS_Reset_All_(BOXC_VS _PL_ _R_ Q)
{
	if(Q)
	{
		boxc_l2 _PL_ _R_ Queue=Q->Thing;
		address _PL_ _R_ Count=Q->Count;

		for(address Select=0;Select<Q->Number;Select++)
			if(Count[Select])
			{
				xBoxC_QS_Reset_(Queue[Select].L,Queue[-1].L);

				Count[-1]+=Count[Select];
				Count[Select]=0;
			}
			else;

		return 1;
	}
	else
		return 0;
}

static logical BoxC_QS_Check_(BOXC_VS _PL_ _R_ Q,ADDRESS Select) { return ((xBoxC_VS_Verify_(Q,Select))&&(xBoxC_L2_Check_(((boxc_l2*)(Q->Thing))[Select].L[0]))); }
static logical BoxC_QS_Check_All_(BOXC_VS _PL_ _R_ Q)
{
	if(Q)
	{
		for(BOXC_L2 *_R_ Ptr=Q->Thing,_PL_ End=Ptr+(Q->Number);Ptr<End;Ptr++)
			if(xBoxC_L2_Check_(Ptr->L[0]));
			else
				return 0;

		return 1;
	}
	else
		return 0;
}
static general *BoxC_QS_Peek_(BOXC_VS _PL_ _R_ Q,ADDRESS Select,ADDRESS Index)
{
	if((xBoxC_VS_Verify_(Q,Select))&&(Index<Q->Count[Select]))
		return xBoxC_L2_Peek_(((boxc_l2*)(Q->Thing))[Select].L[0],Index);
	else
		return NULL;
}
#endif

#if(Fold_(BoxC_RS))
static_assert(sizeof(boxc_vs)==sizeof(boxc_rs),"sizeof(boxc_vs) != sizeof(boxc_rs)");
#define xBoxC_L2_Twist_(A,B) ((boxc_l2*)(((address)(A))^((address)(B))))

static general xBoxC_RS_Assign_(boxc_l2 *_R_ Ptr,BOXC_L2 _PL_ Last)
{
	for(Ptr++;Ptr<Last;Ptr++)
		Ptr->L[1]=xBoxC_L2_Twist_(Ptr-1,Ptr+1);

	return;
}
static general xBoxC_RS_Setup_A_(boxc_l2 _PL_ _R_ Ring,address _PL_ _R_ Count,ADDRESS Number,ADDRESS Capacity)
{
	Ring[-1].L[1]=Ring[-1].L[0]=NULL;
	Count[-1]=Capacity;

	if(Number)
	{
		MemC_Clear_1D_(Ring,Number);
		MemC_Clear_1D_(Count,Number);
	}
	else;

	return;
}
static general xBoxC_RS_Setup_B_(boxc_l2 _PL_ _R_ Ring,ADDRESS Number,ADDRESS Capacity)
{
	if(Capacity)
	{
		Ring[-1].L[0]=(Ring[-1].L[1]=Ring+Number)+(Capacity-1);

		switch(Capacity)
		{
		case 1:
			Ring[-1].L[0]->L[1]=NULL;
		case 2:
			Ring[-1].L[1]->L[1]=NULL;
			break;
		default:
			Ring[-1].L[1]->L[1]=xBoxC_L2_Twist_(Ring[-1].L[0],Ring[-1].L[1]+1);
			xBoxC_RS_Assign_(Ring[-1].L[1],Ring[-1].L[0]);
			Ring[-1].L[0]->L[1]=xBoxC_L2_Twist_(Ring[-1].L[1],Ring[-1].L[0]-1);
		}
	}
	else;

	return;
}
static general xBoxC_RS_Setup_(BOXC_VS _PL_ _R_ R)
{
	xBoxC_RS_Setup_A_(R->Thing,R->Count,R->Number,R->Capacity);
	xBoxC_RS_Setup_B_(R->Thing,R->Number,R->Capacity);

	return;
}
static boxc_vs *xBoxC_RS_Auto_(boxc_vs _PL_ _R_ R) { xBoxC_RS_Setup_B_(R->Thing,R->Number,R->Capacity);return R; }
static boxc_vs *BoxC_RS_Create_(ADDRESS Number,ADDRESS Capacity)
{
	boxc_vs *_R_ R=NULL;

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

		xBoxC_RS_Setup_(R);
	}
	else;

	return R;
}
static address BoxC_RS_Size_(BOXC_VS _PL_ _R_ R)
{
	register address Temp;

	if(R)
	{
		Temp=R->Number+1;
		Temp=MemC_Size_(boxc_rs,1)+MemC_Size_(boxc_l2,Temp)+MemC_Size_(address,Temp)+MemC_Size_(boxc_l2,R->Capacity);
	}
	else
		Temp=0;

	return Temp;
}

static general xBoxC_RS_Swap_(boxc_l2 *_PL_ _R_ Source,boxc_l2 *_PL_ _R_ Target,general *_PL_ _R_ Port,LOGICAL Mode)
{
	LOGICAL Nega=!Mode,Posi=!Nega;
	boxc_l2 _PL_ _R_ Here=Source[Posi];

	if(Source[0]==Source[1])
	{
		Source[0]=NULL;
		Source[1]=NULL;
	}
	else
	{
		boxc_l2 _PL_ _R_ NearA=xBoxC_L2_Twist_(Here->L[1],Source[Nega]);
		boxc_l2 _PL_ _R_ NearB=xBoxC_L2_Twist_(Here->L[1],NearA);

		NearA->L[1]=xBoxC_L2_Twist_(NearA->L[1],xBoxC_L2_Twist_(Here,NearB));
		NearB->L[1]=xBoxC_L2_Twist_(NearB->L[1],xBoxC_L2_Twist_(Here,NearA));

		Source[Posi]=NearA;
	}
	{
		general _PL_ Temp=*Port;

		*Port=Here->L[0];
		Here->L[0]=Temp;
		Here->L[1]=xBoxC_L2_Twist_(Target[0],Target[1]);
	}
	if(Target[Nega])
	{
		Target[Nega]->L[1]=xBoxC_L2_Twist_(Target[Nega]->L[1],xBoxC_L2_Twist_(Here,Target[Posi]));
		Target[Posi]->L[1]=xBoxC_L2_Twist_(Target[Posi]->L[1],xBoxC_L2_Twist_(Here,Target[Nega]));
	}
	else
		Target[Posi]=Here;
	Target[Nega]=Here;

	return;
}
static logical BoxC_RS_Insert_(BOXC_VS _PL_ _R_ R,ADDRESS Select,general *Contents,LOGICAL Mode)
{
	if((xBoxC_VS_Verify_(R,Select))&&(R->Count[-1])&&(Contents))
	{
		boxc_l2 _PL_ _R_ Ring=R->Thing;
		address _PL_ _R_ Count=R->Count;

		xBoxC_RS_Swap_(Ring[-1].L,Ring[Select].L,&Contents,Mode);

		Count[-1]--;
		Count[Select]++;

		return 1;
	}
	else
		return 0;
}
static logical BoxC_RS_Desert_(BOXC_VS _PL_ _R_ R,ADDRESS Select,LOGICAL Mode)
{
	if((xBoxC_VS_Verify_(R,Select))&&(R->Count[Select]))
	{
		boxc_l2 _PL_ _R_ Ring=R->Thing;
		address _PL_ _R_ Count=R->Count;
		general *Temp;

		xBoxC_RS_Swap_(Ring[Select].L,Ring[-1].L,&Temp,Mode);

		Count[-1]++;
		Count[Select]--;

		return 1;
	}
	else
		return 0;
}

static general xBoxC_RS_Rotate_(BOXC_L2 *_PL_ _R_ Ring,sintptr Rotation)
{
	SINTPTR Mask=(Rotation>0);
	SINTPTR Nega=Mask^1;
	BOXC_L2 *_R_ Here=Ring[Mask];
	BOXC_L2 *_R_ Prop=xBoxC_L2_Twist_(Ring[Nega],Here->L[1]);

	for(SINTPTR Step=1-(Mask<<1);Rotation;Rotation+=Step)
	{
		BOXC_L2 _PL_ Temp=Prop;

		Prop=xBoxC_L2_Twist_(Here,Prop->L[1]);
		Here=Temp;
	}
	{
		Ring[Mask]=Here;
		Ring[Nega]=xBoxC_L2_Twist_(Prop,Here->L[1]);
	}

	return;
}
static logical BoxC_RS_Rotate_(BOXC_VS _PL_ _R_ R,ADDRESS Select,SINTPTR Rotation)
{
	if(xBoxC_VS_Verify_(R,Select))
	{
		ADDRESS Count=R->Count[Select];

		if(Count)
			xBoxC_RS_Rotate_((BOXC_L2**)(((boxc_l2*)(R->Thing))[Select].L),Rotation%Acs_(sintptr,Count));
		else;

		return 1;
	}
	else
		return 0;
}
static logical BoxC_RS_Flip_(BOXC_VS _PL_ _R_ R,ADDRESS Select)
{
	if(xBoxC_VS_Verify_(R,Select))
	{
		boxc_l2 _PL_ _R_ Ring=R->Thing;
		boxc_l2 _PL_ Temp=Ring[Select].L[0];

		Ring[Select].L[0]=Ring[Select].L[1];
		Ring[Select].L[1]=Temp;

		return 1;
	}
	else
		return 0;
}

static general xBoxC_RS_Reset_(boxc_l2 *_PL_ _R_ Source,boxc_l2 *_PL_ _R_ Target)
{
	if(Target[0])
	{
		BOXC_L2 *Twist;

		Twist=xBoxC_L2_Twist_(Source[0],Target[0]);
		Target[1]->L[1]=xBoxC_L2_Twist_(Target[1]->L[1],Twist);
		Source[1]->L[1]=xBoxC_L2_Twist_(Source[1]->L[1],Twist);

		Twist=xBoxC_L2_Twist_(Source[1],Target[1]);
		Source[0]->L[1]=xBoxC_L2_Twist_(Source[0]->L[1],Twist);
		Target[0]->L[1]=xBoxC_L2_Twist_(Target[0]->L[1],Twist);
	}
	else
		Target[1]=Source[1];
	{
		Target[0]=Source[0];

		Source[0]=NULL;
		Source[1]=NULL;

		return;
	}
}
static logical BoxC_RS_Reset_(BOXC_VS _PL_ _R_ R,ADDRESS Select)
{
	if(xBoxC_VS_Verify_(R,Select))
	{
		if(R->Count[Select])
		{
			boxc_l2 _PL_ _R_ Ring=R->Thing;
			address _PL_ _R_ Count=R->Count;

			xBoxC_RS_Reset_(Ring[Select].L,Ring[-1].L);

			Count[-1]+=Count[Select];
			Count[Select]=0;
		}
		else;

		return 1;
	}
	else
		return 0;
}
static logical BoxC_RS_Reset_All_(BOXC_VS _PL_ _R_ R)
{
	if(R)
	{
		boxc_l2 _PL_ _R_ Ring=R->Thing;
		address _PL_ _R_ Count=R->Count;
		address Select;

		for(Select=0;Select<R->Number;Select++)
			if(Count[Select])
			{
				xBoxC_RS_Reset_(Ring[Select].L,Ring[-1].L);

				Count[-1]+=Count[Select];
				Count[Select]=0;
			}
			else;

		return 1;
	}
	else
		return 0;
}

static logical xBoxC_RS_Check_(BOXC_L2 _PL_ _PL_ _R_ Ring)
{
	if(Ring[0]==Ring[1])
		return (Ring[0]->L[0]!=NULL);
	else
	{
		BOXC_L2 *_R_ Here=Ring[1];
		BOXC_L2 *_R_ Next=xBoxC_L2_Twist_(Ring[0],Here->L[1]);

		while(Next!=Ring[1])
			if(Here->L[0])
			{
				BOXC_L2 _PL_ Temp=Next;

				Next=xBoxC_L2_Twist_(Here,Next->L[1]);
				Here=Temp;
			}
			else
				return 0;

		return 1;
	}
}
static logical BoxC_RS_Check_(BOXC_VS _PL_ _R_ R,ADDRESS Select) { return ((xBoxC_VS_Verify_(R,Select))&&(xBoxC_RS_Check_((BOXC_L2**)(((boxc_l2*)(R->Thing))[Select].L)))); }
static logical BoxC_RS_Check_All_(BOXC_VS _PL_ _R_ R)
{
	if(R)
	{
		for(BOXC_L2 *_R_ Ptr=R->Thing,_PL_ End=Ptr+(R->Number);Ptr<End;Ptr++)
			if(xBoxC_RS_Check_((BOXC_L2**)(Ptr->L)));
			else
				return 0;

		return 1;
	}
	else
		return 0;
}
static general *BoxC_RS_Read_(BOXC_VS _PL_ _R_ R,ADDRESS Select,LOGICAL Mode)
{
	if((xBoxC_VS_Verify_(R,Select))&&(R->Count[Select]))
		return (((boxc_l2*)(R->Thing))[Select].L[Mode&1]->L[0]);
	else
		return NULL;
}

static address xBoxC_RS_Zeros_(register address T) { register address C=0;for(T^=T-1;T>>=1;C++);return C; }
static address xBoxC_RS_GCD_(address M,address N)
{
	ADDRESS S=xBoxC_RS_Zeros_(M|N);

	M>>=S;
	N>>=S;
	M>>=xBoxC_RS_Zeros_(M);

	__dlOuOlb__
	{
		N>>=xBoxC_RS_Zeros_(N);
		if(M>N)
		{
			register ADDRESS T=M-N;

			M=N;
			N=T;
		}
		else if(M<N)
			N-=M;
		else
			return (M<<S);
	}
}
static general xBoxC_RS_Spread_(general **_R_ Slot,BOXC_L2 *_PL_ _R_ Ring,ADDRESS Count,SINTPTR Rotation,LOGICAL Mode)
{
	SINTPTR Mask=(Rotation>0);
	SINTPTR Nega=Mask^1;
	SINTPTR Step=1-(Mask<<1);
	BOXC_L2 *_R_ Here=Ring[Mask];
	BOXC_L2 *_R_ Prop=xBoxC_L2_Twist_(Ring[Nega],Here->L[1]);
	
	for(general *_PL_ End=Slot+Count;Slot<End;Slot++)
	{
		MemC_Temp_(boxc_l2,Temp)
		{
			Temp.L[Mask]=(boxc_l2*)Here;
			Temp.L[Nega]=xBoxC_L2_Twist_(Prop,Here->L[1]);

			*Slot=Temp.L[Mode]->L[0];
		}
		for(sintptr Iter=Rotation;Iter;Iter+=Step)
		{
			BOXC_L2 _PL_ Temp=Prop;

			Prop=xBoxC_L2_Twist_(Here,Prop->L[1]);
			Here=Temp;
		}
	}

	return;
}
static logical BoxC_RS_Spread_(boxc_li _PL_ _R_ Li,BOXC_VS _PL_ _R_ RS,ADDRESS Select,sintptr Rotation,LOGICAL Mode)
{
	if((Li)&&(xBoxC_VS_Verify_(RS,Select)))
		if(RS->Count[Select])
		{
			address Number;

			if(Rotation)
			{
				ADDRESS Count=RS->Count[Select];

				Rotation%=Acs_(sintptr,Count);
				Number=(Rotation<0)?(-Rotation):(+Rotation);
				Number=xBoxC_RS_GCD_(Count,Number);
				Number=Count/Number;
			}
			else
				Number=1;

			if((Li->Capacity)<Number);
			else
			{
				Acs_(address,Li->Count)=Number;
				xBoxC_RS_Spread_((general**)(Li->Item),(BOXC_L2**)(((boxc_l2*)(RS->Thing))[Select].L),Number,Rotation,Mode);

				return 1;
			}
		}
		else
		{
			Acs_(address,Li->Count)=0;

			return 1;
		}
	else;

	return 0;
}

#undef xBoxC_L2_Twist_
#endif

#if(Fold_(BoxC_KS))
struct _boxc_kn { general *Key,*Value;address Height,Weight;struct _boxc_kn *Leaf[2]; };
MemC_Type_Declare_(struct,boxc_kn,BOXC_KN);
MemC_Func_Declare_(integer,boxc_c_,BOXC_C_,GENERAL _PL_,GENERAL _PL_);
static_assert(sizeof(boxc_ks)==(sizeof(address)<<2),"sizeof(boxc_ks) != 4*sizeof(address)");
static_assert(sizeof(boxc_kn)==(sizeof(boxc_ks)+sizeof(boxc_l2)),"sizeof(boxc_kn) != 6*sizeof(address)");

static integer xBoxC_KN_Comp_(GENERAL _PL_ A,GENERAL _PL_ B) { return ((A>B)-(A<B)); }
static address xBoxC_KN_Height_Old_(BOXC_KN _PL_ _R_ Node) { return ((Node)?(Node->Height):(0)); }
static general xBoxC_KN_Height_New_(boxc_kn _PL_ _R_ Node)
{
	ADDRESS H0=xBoxC_KN_Height_Old_(Node->Leaf[0]);
	ADDRESS H1=xBoxC_KN_Height_Old_(Node->Leaf[1]);

	Node->Height=(H0>H1)?(H0):(H1);
	Node->Height++;

	return;
}
static sintptr xBoxC_KN_Height_Bal_(BOXC_KN _PL_ _R_ Node) { return ((Node)?(xBoxC_KN_Height_Old_(Node->Leaf[0])-xBoxC_KN_Height_Old_(Node->Leaf[1])):(0)); }
static address xBoxC_KN_Weight_Old_(BOXC_KN _PL_ _R_ Node) { return ((Node)?(Node->Weight):(0)); }
static general xBoxC_KN_Weight_New_(boxc_kn _PL_ _R_ Node)
{
	ADDRESS W0=xBoxC_KN_Weight_Old_(Node->Leaf[0]);
	ADDRESS W1=xBoxC_KN_Weight_Old_(Node->Leaf[1]);

	Node->Weight=W0+W1;
	Node->Weight++;

	return;
}
static boxc_kn *xBoxC_KN_Deeper_(boxc_kn *_R_ Node)
{
	while(Node->Height>1)
		Node=Node->Leaf[xBoxC_KN_Height_Old_(Node->Leaf[0])<xBoxC_KN_Height_Old_(Node->Leaf[1])];

	return Node;
}
static boxc_kn *xBoxC_KN_Diving_(boxc_kn *_R_ Node) { for(;Node->Leaf[0];Node=Node->Leaf[0]);return Node; }
static boxc_kn *xBoxC_KN_Verify_(BOXC_C_ Comp_,boxc_kn *_R_ Node,GENERAL _PL_ Key)
{
	while(Node)
	{
		register INTEGER Comp=Comp_(Key,Node->Key);

		if(Comp)
			Node=Node->Leaf[Comp>0];
		else
			break;
	}

	return Node;
}
static boxc_kn *xBoxC_KN_Search_(boxc_kn *_R_ Node,ADDRESS Index)
{
	for(address Offset=0;1;)
	{
		register ADDRESS Temp=Offset+xBoxC_KN_Weight_Old_(Node->Leaf[0]);

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
static address xBoxC_KN_Locate_(BOXC_C_ Comp_,boxc_kn *_R_ Node,GENERAL _PL_ Key)
{
	for(address Index=0;1;)
	{
		register INTEGER Comp=Comp_(Key,Node->Key);

		if(Comp<0)
			if(Node->Leaf[0])
				Node=Node->Leaf[0];
			else
				return MemC.Full.V;
		else if(Comp>0)
			if(Node->Leaf[1])
			{
				if(Node->Leaf[0])
					Index+=Node->Leaf[0]->Weight;
				else;

				Index++;
				Node=Node->Leaf[1];
			}
			else
				return MemC.Full.V;
		else
			return Index;
	}
}
static general xBoxC_KN_Travel_(BOXC_KN _PL_ _R_ Node,memclip *_R_ List)
{
	if(Node->Leaf[0])
	{
		xBoxC_KN_Travel_(Node->Leaf[0],List);
		List+=Node->Leaf[0]->Weight;
	}
	else;

	List->P=Node->Key;

	if(Node->Leaf[1])
		xBoxC_KN_Travel_(Node->Leaf[1],List+1);
	else;

	return;
}
static boxc_kn *xBoxC_KN_Rotate_(boxc_kn _PL_ _R_ Node,LOGICAL Mode)
{
	LOGICAL Togg=!Mode;
	boxc_kn _PL_ _R_ Leaf=Node->Leaf[Togg];
	boxc_kn _PL_ _R_ Temp=Leaf->Leaf[Mode];

	Leaf->Leaf[Mode]=Node;
	Node->Leaf[Togg]=Temp;

	xBoxC_KN_Height_New_(Node);
	xBoxC_KN_Weight_New_(Node);

	xBoxC_KN_Height_New_(Leaf);
	xBoxC_KN_Weight_New_(Leaf);

	return Leaf;
}

static boxc_kn *xBoxC_KN_Insert_(boxc_kn _PL_,BOXC_C_,boxc_kn*_R_,general _PL_);
static boxc_kn *xBoxC_KN_Desert_(boxc_kn _PL_,BOXC_C_,boxc_kn*_R_,GENERAL _PL_);
static boxc_kn *xBoxC_KN_Create_(boxc_kn _PL_ Pair,general _PL_ Key)
{
	boxc_kn *_R_ Node;

	if(Pair)
	{
		Node=xBoxC_KN_Deeper_(Pair);
		xBoxC_KN_Desert_(NULL,xBoxC_KN_Comp_,Pair,Node);

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
static general xBoxC_KN_Delete_(boxc_kn _PL_ Pair,boxc_kn _PL_ Node) { if(Pair)xBoxC_KN_Insert_(NULL,xBoxC_KN_Comp_,Pair,Node);else;return; }
static boxc_kn *xBoxC_KN_Insert_(boxc_kn _PL_ Pair,BOXC_C_ Comp_,boxc_kn *_R_ Node,general _PL_ Key)
{
	if(Node)
	{
		integer Comp=Comp_(Key,Node->Key);
		logical Mode=(Comp>0);

		Node->Leaf[Mode]=xBoxC_KN_Insert_(Pair,Comp_,Node->Leaf[Mode],Key);

		xBoxC_KN_Height_New_(Node);
		xBoxC_KN_Weight_New_(Node);
		{
			SINTPTR Balance=xBoxC_KN_Height_Bal_(Node);

			switch(Balance)
			{
			default:
				Mode=(Balance<0)?((Comp=+Comp_(Key,Node->Leaf[1]->Key)),1):((Comp=-Comp_(Key,Node->Leaf[0]->Key)),0);
				if(Comp)
				{
					if(Comp<0)
						Node->Leaf[Mode]=xBoxC_KN_Rotate_(Node->Leaf[Mode],Mode);
					else;

					Node=xBoxC_KN_Rotate_(Node,!Mode);
				}
				else
			case-1:case 0:case+1:;
			}
		}
	}
	else
		Node=xBoxC_KN_Create_(Pair,Key);

	return Node;
}
static boxc_kn *xBoxC_KN_Desert_(boxc_kn _PL_ Pair,BOXC_C_ Comp_,boxc_kn *_R_ Node,GENERAL _PL_ Key)
{
	if(Node)
	{
		integer Comp=Comp_(Key,Node->Key);

		if(Comp)
		{
			LOGICAL Mode=(Comp>0);

			Node->Leaf[Mode]=xBoxC_KN_Desert_(Pair,Comp_,Node->Leaf[Mode],Key);
		}
		else
		{
			INTEGER Mode=((Node->Leaf[0])?(1):(0))|((Node->Leaf[1])?(2):(0));

			switch(Mode)
			{
			case 0:
				xBoxC_KN_Delete_(Pair,Node);

				return NULL;
			case 1:
			case 2:
				{
					boxc_kn _PL_ Leaf=Node->Leaf[Mode>>1];

					*Node=*Leaf;
					xBoxC_KN_Delete_(Pair,Leaf);
				}
				break;
			default:
				{
					boxc_kn _PL_ Leaf=xBoxC_KN_Diving_(Node->Leaf[1]);

					Node->Key=Leaf->Key;
					Node->Leaf[1]=xBoxC_KN_Desert_(Pair,Comp_,Node->Leaf[1],Leaf->Key);
				}
			}
		}
		xBoxC_KN_Height_New_(Node);
		xBoxC_KN_Weight_New_(Node);
		{
			sintptr Balance=xBoxC_KN_Height_Bal_(Node);

			switch(Balance)
			{
			default:
				{
					LOGICAL Mode=(Balance<0)?((Balance=+xBoxC_KN_Height_Bal_(Node->Leaf[1])),1):((Balance=-xBoxC_KN_Height_Bal_(Node->Leaf[0])),0);

					if(Balance>0)
						Node->Leaf[Mode]=xBoxC_KN_Rotate_(Node->Leaf[Mode],Mode);
					else;

					Node=xBoxC_KN_Rotate_(Node,!Mode);
				}
			case-1:case 0:case+1:;
			}
		}
	}
	else;

	return Node;
}

static general xBoxC_KS_Setup_A_(boxc_kn *_PL_ _R_ Root) { Root[1]=Root[0]=NULL;return; }
static general xBoxC_KS_Setup_B_(boxc_kn *_PL_ _R_ Root,ADDRESS Capacity)
{
	for(boxc_kn *Ptr=(boxc_kn*)(Root+2),_PL_ End=Ptr+Capacity;Ptr<End;Ptr++)
		Root[0]=xBoxC_KN_Insert_(NULL,xBoxC_KN_Comp_,Root[0],Ptr);

	return;
}
static general xBoxC_KS_Setup_(BOXC_KS _PL_ _R_ Head)
{
	boxc_kn *_PL_ _R_ Root=(boxc_kn**)(((boxc_l2*)(Head->Key))->L);

	xBoxC_KS_Setup_A_(Root);
	xBoxC_KS_Setup_B_(Root,Head->Capacity);

	return;
}
static boxc_ks *xBoxC_KS_Auto_(boxc_ks _PL_ _R_ Head)
{
	boxc_kn *_PL_ _R_ Root=(boxc_kn**)(((boxc_l2*)(Head->Key))->L);

	Acs_(boxc_c_,Head->Comp_)=(Head->Comp_)?(Head->Comp_):(xBoxC_KN_Comp_);
	xBoxC_KS_Setup_B_(Root,Head->Capacity);

	return Head;
}
static boxc_ks *BoxC_KS_Create_(BOXC_C_ Comp_,ADDRESS Capacity)
{
	boxc_ks _PL_ _R_ Head=MemC.Alloc.Byte_(MemC.Size.Mul_(Capacity+1,sizeof(boxc_kn)));

	if(Head)
	{
		Acs_(boxc_l2*,Head->Key)=(boxc_l2*)(Head+1);
		Acs_(boxc_c_,Head->Comp_)=(Comp_)?(Comp_):(xBoxC_KN_Comp_);
		Acs_(address,Head->Number)=0;
		Acs_(address,Head->Capacity)=Capacity;

		xBoxC_KS_Setup_(Head);
	}
	else;

	return Head;
}
static address BoxC_KS_Size_(BOXC_KS _PL_ _R_ Head) { return ((Head)?(MemC_Size_(boxc_kn,(Head->Capacity)+1)):(0)); }
static logical BoxC_KS_Reset_(boxc_ks _PL_ _R_ Head)
{
	if(Head)
	{
		Acs_(address,Head->Number)=0;

		xBoxC_KS_Setup_(Head);

		return 1;
	}
	else
		return 0;
}
static address BoxC_KS_Height_(BOXC_KS _PL_ _R_ Head)
{
	if((Head)&&(Head->Number))
	{
		boxc_kn _PL_ _PL_ _R_ Root=(boxc_kn**)(((boxc_l2*)(Head->Key))->L);

		return (Root[1]->Height);
	}
	else
		return 0;
}

static logical BoxC_KS_Insert_(boxc_ks _PL_ _R_ Head,general _PL_ Key)
{
	if((Head)&&((Head->Number)<(Head->Capacity))&&(Key))
	{
		boxc_kn *_PL_ _R_ Root=(boxc_kn**)(((boxc_l2*)(Head->Key))->L);

		if(xBoxC_KN_Verify_(Head->Comp_,Root[1],Key));
		else
		{
			Root[1]=xBoxC_KN_Insert_(Root[0],Head->Comp_,Root[1],Key);
			Acs_(address,Head->Number)++;

			return 1;
		}
	}
	else;

	return 0;
}
static logical BoxC_KS_Desert_(boxc_ks _PL_ _R_ Head,GENERAL _PL_ Key)
{
	if(Head)
	{
		boxc_kn *_PL_ _R_ Root=(boxc_kn**)(((boxc_l2*)(Head->Key))->L);

		if(xBoxC_KN_Verify_(Head->Comp_,Root[1],Key))
		{
			Root[1]=xBoxC_KN_Desert_(Root[0],Head->Comp_,Root[1],Key);
			Acs_(address,Head->Number)--;

			return 1;
		}
		else;
	}
	else;

	return 0;
}
static logical BoxC_KS_Verify_(BOXC_KS _PL_ _R_ Head,GENERAL _PL_ Key)
{
	if(Head)
	{
		boxc_kn _PL_ _PL_ _R_ Root=(boxc_kn**)(((boxc_l2*)(Head->Key))->L);

		if(xBoxC_KN_Verify_(Head->Comp_,Root[1],Key))
			return 1;
		else;
	}
	else;

	return 0;
}

static logical BoxC_KS_Writer_(BOXC_KS _PL_ _R_ Head,GENERAL _PL_ Key,general _PL_ Value)
{
	if((Head)&&(Key)&&(Value))
	{
		boxc_kn _PL_ _PL_ _R_ Root=(boxc_kn**)(((boxc_l2*)(Head->Key))->L);
		boxc_kn _PL_ _R_ Node=xBoxC_KN_Verify_(Head->Comp_,Root[1],Key);

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
static general *BoxC_KS_Reader_(BOXC_KS _PL_ _R_ Head,GENERAL _PL_ Key)
{
	if((Head)&&(Key))
	{
		boxc_kn _PL_ _PL_ _R_ Root=(boxc_kn**)(((boxc_l2*)(Head->Key))->L);
		boxc_kn _PL_ _R_ Node=xBoxC_KN_Verify_(Head->Comp_,Root[1],Key);

		if(Node)
			return (Node->Value);
		else;
	}
	else;

	return NULL;
}

static general *BoxC_KS_Search_(BOXC_KS _PL_ _R_ Head,ADDRESS Index)
{
	if((Head)&&(Index<Head->Number))
	{
		boxc_kn _PL_ _PL_ _R_ Root=(boxc_kn**)(((boxc_l2*)(Head->Key))->L);

		return (xBoxC_KN_Search_(Root[1],Index)->Key);
	}
	else
		return NULL;
}
static address BoxC_KS_Locate_(BOXC_KS _PL_ _R_ Head,GENERAL _PL_ Key)
{
	if((Head)&&(Head->Number))
	{
		boxc_kn _PL_ _PL_ _R_ Root=(boxc_kn**)(((boxc_l2*)(Head->Key))->L);

		return xBoxC_KN_Locate_(Head->Comp_,Root[1],Key);
	}
	else
		return MemC.Full.V;
}

static logical BoxC_KS_Spread_(boxc_li _PL_ _R_ Li,BOXC_KS _PL_ _R_ KS)
{
	if((Li)&&(KS))
		if((Li->Capacity)<(KS->Number));
		else
		{
			BOXC_KN _PL_ _PL_ _R_ Root=(BOXC_KN**)(((boxc_l2*)(KS->Key))->L);

			Acs_(address,Li->Count)=Root[1]->Weight;
			xBoxC_KN_Travel_(Root[1],(memclip*)(Li->Item));

			return 1;
		}
	else;

	return 0;
}
#endif

#if(Fold_(BoxC_FS))
static boxc_fs *BoxC_FS_Create_(ADDRESS Number)
{
	boxc_fs *_R_ F=NULL;

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
static address BoxC_FS_Size_(BOXC_FS _PL_ _R_ F) { return ((F)?(((F->Number+7)>>3)+sizeof(boxc_fs)):(0)); }
static general BoxC_FS_Reset_All_(BOXC_FS _PL_ _R_ F,LOGICAL X) { if((F)&&(F->Number))memset((general*)(F->Flag),(X)?(0xFF):(0x00),(F->Number+7)>>3);else;return; }
static logical BoxC_FS_Check_All_(BOXC_FS _PL_ _R_ F,LOGICAL X)
{
	if(F)
		if(F->Number)
		{
			ADDRESS Safe=F->Number>>3;
			BYTE_08 *_R_ Ptr=F->Flag,_PL_ End=Ptr+Safe;
			register byte_08 Rest=(byte_08)(F->Number&7);
			register byte_08 Mask;

			if(X)
			{
				for(Mask=0xFF;Ptr<End;Ptr++)
					Mask&=*Ptr;

				Rest=0xFF<<Rest;
				Rest|=*Ptr;
				Mask&=Rest;

				return (Mask==0xFF);
			}
			else
			{
				for(Mask=0x00;Ptr<End;Ptr++)
					Mask|=*Ptr;

				Rest=0xFF<<Rest;
				Rest=~Rest;
				Rest&=*Ptr;
				Mask|=Rest;

				return (Mask==0x00);
			}
		}
		else
			return 1;
	else
		return 0;
}

static logical xBoxC_FS_Verify_(BOXC_FS _PL_ _R_ F,ADDRESS Select) { return ((F)&&(Select<(F->Number))); }
static general BoxC_FS_Writer_(BOXC_FS _PL_ _R_ F,ADDRESS Select,LOGICAL Mode)
{
	if(xBoxC_FS_Verify_(F,Select))
	{
		byte_08 _PL_ _R_ Flag=((byte_08*)(F->Flag))+(Select>>3);
		register byte_08 Mask=(byte_08)(1<<(Select&7));
		register byte_08 Temp=(byte_08)(Mode);

		*Flag|=Mask;
		Mask=~Mask;
		Temp=-Temp;
		Mask|=Temp;
		*Flag&=Mask;
	}
	else;

	return;
}
static logical BoxC_FS_Reader_(BOXC_FS _PL_ _R_ F,ADDRESS Select)
{
	if(xBoxC_FS_Verify_(F,Select))
	{
		LOGICAL Table[2]={0,1};
		register byte_08 Temp=(byte_08)(Select&7);

		Temp=((BYTE_08*)(F->Flag))[Select>>3]>>Temp;
		Temp&=0x01;

		return Table[Temp];
	}
	else
		return 0;
}
static general BoxC_FS_Toggle_(BOXC_FS _PL_ _R_ F,ADDRESS Select)
{
	if(xBoxC_FS_Verify_(F,Select))
	{
		register byte_08 Temp=(byte_08)(1<<(Select&7));

		((byte_08*)(F->Flag))[Select>>3]^=Temp;
	}
	else;

	return;
}
#endif

#if(Fold_(BoxC_Tr))
static general xBoxC_Tr_Init_(boxc_tr _PL_ _R_ Root,ADDRESS Chunks)
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

	return;
}
static boxc_tr *xBoxC_Tr_Most_Root_(boxc_tr *_R_ Ptr) { for(;Ptr->Root;Ptr=Ptr->Root);return Ptr; }
static boxc_tr *xBoxC_Tr_Most_Leaf_(boxc_tr *_R_ Ptr)
{
	for(;Ptr->Leaf;Ptr=Ptr->Leaf);
	Ptr->Object=Acs_(general*,Ptr->Link)=NULL;
	
	return Ptr;
}
static general xBoxC_Tr_Swap_(boxc_tr _PL_ _R_ This,boxc_tr _PL_ _R_ Root)
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

	return;
}
static general xBoxC_Tr_Numb_Inc_(boxc_tr *_R_ Ptr)
{
	ADDRESS Increment=Ptr->Total+1;

	Ptr=Ptr->Root;
	for(Acs_(address,Ptr->Count)++;Ptr;Ptr=Ptr->Root)
		Acs_(address,Ptr->Total)+=Increment;

	return;
}
static general xBoxC_Tr_Numb_Dec_(boxc_tr *_R_ Ptr)
{
	ADDRESS Decrement=Ptr->Total+1;

	Ptr=Ptr->Root;
	for(Acs_(address,Ptr->Count)--;Ptr;Ptr=Ptr->Root)
		Acs_(address,Ptr->Total)-=Decrement;

	return;
}
static boxc_tr *BoxC_Tr_Create_(boxc_tr _PL_ _R_ Root,ADDRESS Capacity)
{
	boxc_tr *_R_ Tree;

	if(Root)
		if(Capacity)
			Tree=NULL;
		else
		{
			boxc_tr *_R_ Origin=xBoxC_Tr_Most_Root_(Root);

			if(Origin<(boxc_tr*)(Origin->Link))
			{
				Origin=Origin->Link;
				if(Origin->Count)
				{
					Tree=xBoxC_Tr_Most_Leaf_(Origin);

					xBoxC_Tr_Numb_Dec_(Tree);
					xBoxC_Tr_Swap_(Tree,Root);
					xBoxC_Tr_Numb_Inc_(Tree);
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
				xBoxC_Tr_Init_(Tree+1,Capacity);
			}
			else
				Acs_(boxc_tr*,Tree[1].Leaf)=NULL;
		}
		else;
	}

	return Tree;
}
static general BoxC_Tr_Delete_(boxc_tr *_PL_ _R_ Tree)
{
	if(*Tree)
		if((*Tree)->Root)
		{
			boxc_tr _PL_ Root=(*Tree)->Root;
			boxc_tr _PL_ _R_ Origin=xBoxC_Tr_Most_Root_(Root);

			if(Origin<(boxc_tr*)(Origin->Link))
			{
				xBoxC_Tr_Numb_Dec_(*Tree);
				xBoxC_Tr_Swap_(*Tree,Origin->Link);
				xBoxC_Tr_Numb_Inc_(*Tree);

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

	return;
}
static address BoxC_Tr_Size_(BOXC_TR *_R_ Tree)
{
	if(Tree)
	{
		Tree=xBoxC_Tr_Most_Root_((boxc_tr*)(Tree));

		return MemC_Size_(boxc_tr,Tree->Total+((boxc_tr*)(Tree->Link))->Total+2);
	}
	else
		return 0;
}
static address BoxC_Tr_Used_(BOXC_TR _PL_ _R_ Tree)
{
	if(Tree)
	{
		BOXC_TR _PL_ _R_ Origin=xBoxC_Tr_Most_Root_((boxc_tr*)Tree);

		if(Origin<(boxc_tr*)(Origin->Link))
			return MemC_Size_(boxc_tr,Tree->Total+1);
		else;
	}
	else;

	return 0;
}

static address BoxC_Tr_Left_(BOXC_TR _PL_ _R_ Tree)
{
	if(Tree)
	{
		BOXC_TR *_R_ Origin=xBoxC_Tr_Most_Root_((boxc_tr*)Tree);

		if(Origin<(BOXC_TR*)(Origin->Link))
			Origin=Origin->Link;
		else;

		return Origin->Total;
	}
	else
		return 0;
}
static boxc_tr *BoxC_Tr_Origin_(boxc_tr _PL_ _R_ Tree)
{
	boxc_tr *_R_ Return;

	if(Tree)
	{
		Return=xBoxC_Tr_Most_Root_(Tree);
		if(Return>(boxc_tr*)(Return->Link))
			Return=Return->Link;
		else;
	}
	else
		Return=NULL;

	return Return;
}
static address BoxC_Tr_Height_(BOXC_TR *_R_ Tree)
{
	if(Tree)
	{
		register address Height;

		for(Height=0;Tree->Root;Tree=Tree->Root,Height++);
		if(Tree>(BOXC_TR*)(Tree->Link));
		else
			return Height;
	}
	else;

	return 0;
}

static logical xBoxC_Tr_Okay_(BOXC_TR *Source,BOXC_TR *Target)
{
	if((Source)&&(Target))
	{
		while(Target->Root)
			if(Source==Target)
				return 0;
			else
				Target=Target->Root;

		if(Source==Target)
			return 0;
		else if(Target>(BOXC_TR*)(Target->Link))
			return 0;
		else
			for(;Source->Root;Source=Source->Root);

		return (Source==Target);
	}
	else
		return 0;
}
static logical BoxC_Tr_Move_(boxc_tr _PL_ Tree,boxc_tr _PL_ Root)
{
	if(xBoxC_Tr_Okay_(Tree,Root))
	{
		xBoxC_Tr_Numb_Dec_(Tree);
		xBoxC_Tr_Swap_(Tree,Root);
		xBoxC_Tr_Numb_Inc_(Tree);

		return 1;
	}
	else
		return 0;
}
#endif

#if(Fold_(BoxC_Sw))
static logical xBoxC_Sw_Comp_(register GENERAL _PL_ A,register GENERAL _PL_ B) { return (A>B); }
static general xBoxC_Sw_Take_(general _PL_ *_R_ PtrL,ADDRESS *_R_ PtrI,boxclip *_R_ PtrC,ADDRESS Nums)
{
	for(BOXCLIP _PL_ End=PtrC+Nums;PtrC<End;PtrL++,PtrI++,PtrC++)
	{
		PtrC->L=*PtrL;
		PtrC->I=*PtrI;
	}

	return;
}
static logical xBoxC_Sw_Unique_(GENERAL _PL_ *_R_ Ptr,ADDRESS Sub)
{
	for(GENERAL _PL_ _PL_ End=Ptr+Sub;Ptr<End;Ptr++)
		if(Ptr[0]==Ptr[1])
			return 0;
		else;

	return 1;
}
static boxc_sw *BoxC_Sw_Create_(BOXC_LI _PL_ _R_ Li)
{
	if(Li)
	{
		ADDRESS Number=Li->Count;
		boxc_sw *_R_ Switch;

		if(Number)
		{
			MemC_Temp_(ADDRESS,Temp=MemC.Size.Mul_(Number,sizeof(boxclip)))
				Switch=(Temp)?(MemC.Alloc.Byte_(MemC.Size.Add_(Temp,sizeof(boxc_sw)))):(NULL);

			if(Switch)
			{
				boxclip _PL_ Case=(boxclip*)(Switch+1);

				Acs_(boxclip*,Switch->Case)=Case;
				Acs_(address,Switch->Number)=Number;
				MemC_Temp_ND_(general*,Space,KILL:xBoxC_VS_Delete_((boxc_vs**)(&Switch));,1,Number<<1)
				{
					general *_PL_ TableL=Space;
					address _PL_ TableI=(address*)(TableL+Number);

					if(MemC_Copy_1D_(Li->Item,TableL,Li->Count))
						MemC.Sort.Index_(TableI,Li->Count,0);
					else
						goto KILL;

					if(MemC.Sort.Do_(xBoxC_Sw_Comp_,(GENERAL**)(TableL),TableI,(address*)Case,Number))
						if(xBoxC_Sw_Unique_((GENERAL**)(TableL),Number-1))
							xBoxC_Sw_Take_(TableL,TableI,Case,Number);
						else
							goto KILL;
					else
						goto KILL;
				}
			}
			else;
		}
		else
		{
			Switch=MemC_Alloc_Unit_(boxc_sw);
			if(Switch)
				MemC_Clear_Unit_(Switch);
			else;
		}

		return Switch;
	}
	else;

	return NULL;
}
static address BoxC_Sw_Size_(BOXC_SW _PL_ _R_ Switch) { return ((Switch)?(sizeof(boxc_sw)+MemC_Size_(boxclip,Switch->Number)):(0)); }
static address BoxC_Sw_Find_(BOXC_SW _PL_ _R_ Switch,GENERAL _PL_ Key,LOGICAL Mode)
{
	if((Switch)&&(Switch->Case))
		if(Mode)
		{
			boxclip Scope=*((BOXCLIP*)(Switch));

			__dlOuOlb__
			{
				register ADDRESS Pick=Scope.I>>1;
				BOXCLIP _PL_ _R_ Case=((boxclip*)(Scope.L))+Pick;

				if(Pick)
					if(Key<(Case->L))
						Scope.I=Pick;
					else if(Key>(Case->L))
					{
						register ADDRESS Offset=Pick+1;

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

	return MemC.Full.V;
}
#endif

#if(Fold_(BoxC_Li))
static boxc_li *BoxC_Li_Create_(ADDRESS Caps)
{
	boxc_li *_R_ List=NULL;

	if(Caps)
	{
		MemC_Temp_(ADDRESS,Temp=MemC.Size.Mul_(Caps,sizeof(general*)))
			List=(Temp)?(MemC.Alloc.Byte_(MemC.Size.Add_(Temp,sizeof(boxc_li)))):(NULL);

		if(List)
		{
			Acs_(address,List->Capacity)=Caps;
			Acs_(address,List->Count)=0;
		}
		else;
	}
	else
	{
		List=MemC_Alloc_Unit_(boxc_li);
		if(List)
			MemC_Clear_Unit_(List);
		else;
	}

	return List;
}
static address BoxC_Li_Size_(BOXC_LI _PL_ _R_ List) { return ((List)?(sizeof(boxc_li)+MemC_Size_(general*,List->Capacity)):(0)); }
static logical BoxC_Li_Reset_(boxc_li _PL_ _R_ List)
{
	if(List)
	{
		Acs_(address,List->Count)=0;

		return 1;
	}
	else
		return 0;
}
static logical BoxC_Li_Check_(BOXC_LI _PL_ _R_ List) { return ((List)&&(MemC.Set.Check_((GENERAL**)(List->Item),List->Count))); }

static logical BoxC_Li_Tip_Append_(boxc_li _PL_ _R_ List,general _PL_ Tip)
{
	if((List)&&((List->Count)<(List->Capacity)))
	{
		((general**)(List->Item))[List->Count]=Tip;
		Acs_(address,List->Count)++;

		return 1;
	}
	else
		return 0;
}
static logical BoxC_Li_Tip_Remove_(boxc_li _PL_ _R_ List)
{
	if((List)&&(List->Count))
	{
		Acs_(address,List->Count)--;

		return 1;
	}
	else
		return 0;
}

static logical BoxC_Li_One_Insert_(boxc_li _PL_ _R_ List,ADDRESS Offset,general _PL_ One)
{
	if((List)&&(Offset<=(List->Count))&&((List->Count)<(List->Capacity)))
	{
		ADDRESS Move=MemC_Size_(general*,(List->Count)-Offset);
		general *_PL_ _R_ Here=(general**)(List->Item)+Offset;

		if((Move)&&(memmove_s(Here+1,Move,Here,Move)));
		else
		{
			*Here=One;
			Acs_(address,List->Count)++;

			return 1;
		}
	}
	else;

	return 0;
}
static logical BoxC_Li_One_Desert_(boxc_li _PL_ _R_ List,ADDRESS Offset)
{
	if((List)&&(Offset<(List->Count)))
	{
		ADDRESS After=(List->Count)-1;
		ADDRESS Move=MemC_Size_(general*,After-Offset);
		general *_PL_ _R_ Here=(general**)(List->Item)+Offset;

		if((Move)&&(memmove_s(Here,Move,Here+1,Move)));
		else
		{
			Acs_(address,List->Count)=After;

			return 1;
		}
	}
	else;

	return 0;
}

static logical BoxC_Li_Lot_Insert_(boxc_li _PL_ _R_ List,ADDRESS Offset,ADDRESS Length,...)
{
	if(List)
		if(Offset>(List->Count));
		else
		{
			ADDRESS After=(List->Count)+Length;

			if((After<(List->Count))||((List->Capacity)<After));
			else if(Length)
			{
				ADDRESS Move=MemC_Size_(general*,(List->Count)-Offset);
				general **_R_ Here=(general**)(List->Item)+Offset;
				general *_PL_ There=Here+Length;

				if((Move)&&(memmove_s(There,Move,Here,Move)));
				else
				{
					Acs_(address,List->Count)=After;

					MemC_Temp_(va_list,Arg)
					{
						va_start(Arg,Length);

						while(Here<There)
							*(Here++)=va_arg(Arg,general*);

						va_end(Arg);
					}

					return 1;
				}
			}
			else
				return 1;
		}
	else;

	return 0;
}
static logical BoxC_Li_Lot_Desert_(boxc_li _PL_ _R_ List,ADDRESS Offset,ADDRESS Length)
{
	if(List)
	{
		ADDRESS Bound=Offset+Length;

		if((Bound<Offset)||((List->Count)<Bound));
		else if(Length)
		{
			ADDRESS After=(List->Count)-Length;
			ADDRESS Move=MemC_Size_(general*,After-Offset);
			general *_PL_ Here=(general**)(List->Item)+Offset;

			if((Move)&&(memmove_s(Here,Move,Here+Length,Move)));
			else
			{
				Acs_(address,List->Count)=After;

				return 1;
			}
		}
		else
			return 1;
	}
	else;

	return 0;
}

static logical BoxC_Li_Copy_(boxc_li _PL_ _R_ TList,BOXC_LI _PL_ _R_ SList,ADDRESS TOfs,ADDRESS SOfs,ADDRESS Nums)
{
	if((TList)&&(SList))
		if((TList==SList)||((TList->Count)<TOfs));
		else
		{
			ADDRESS SBnd=SOfs+Nums;

			if((SBnd<SOfs)||((SList->Count)<SBnd));
			else if(Nums)
			{
				ADDRESS TCnt=(TList->Count)+Nums;

				if((TCnt<(TList->Count))||((TList->Capacity)<TCnt));
				else
				{
					general _PL_ _PL_ SHere=(general**)(SList->Item)+SOfs;
					general *_PL_ THere=(general**)(TList->Item)+TOfs;
					ADDRESS Move=MemC_Size_(general*,(TList->Count)-TOfs);

					if((Move)&&(memmove_s(THere+Nums,Move,THere,Move)));
					else if(MemC_Copy_1D_(SHere,THere,Nums))
					{
						Acs_(address,TList->Count)=TCnt;

						return 1;
					}
					else;
				}
			}
			else
				return 1;
		}
	else;

	return 0;
}
static logical BoxC_Li_Filter_(boxc_li _PL_ _R_ TList,BOXC_LI _PL_ _R_ SList,logical(_PL_ Filt_)(GENERAL _PL_ _R_,general _PL_ _R_),general _PL_ _R_ Opt)
{
	if((TList)&&(SList)&&(Filt_))
		if((TList==SList)||((TList->Capacity)<(SList->Count)));
		else
		{
			general **_R_ PtrT=(general**)(TList->Item);

			for(general _PL_ *_R_ PtrS=SList->Item,_PL_ _PL_ End=PtrS+(SList->Count);PtrS<End;PtrS++)
				if(Filt_(*PtrS,Opt))
					*(PtrT++)=*PtrS;
				else;

			Acs_(address,TList->Count)=PtrT-(TList->Item);

			return 1;
		}
	else;

	return 0;
}
static logical BoxC_Li_Reverse_(BOXC_LI _PL_ _R_ List)
{
	if(List)
	{
		for(address *_R_ PtrA=(address*)(List->Item),*_R_ PtrZ=PtrA+(List->Count);PtrA<(--PtrZ);PtrA++)
		{
			register ADDRESS Temp=*PtrA;

			*PtrA=*PtrZ;
			*PtrZ=Temp;
		}

		return 1;
	}
	else
		return 0;
}
#endif

#endif

#if(Fold_(Library Casing))
static_assert(sizeof(BOXCASE)==(sizeof(ADDRESS)*96),"sizeof(BOXCASE) != 96*sizeof(ADDRESS)");
extern BOXCASE BoxC=
{
	{
		.Version=Idiom.Version,
		.Just_=BoxC_Just_
	},
	.Comp=
	{
		.T08_=BoxC_Comp_T08_,
		.T16_=BoxC_Comp_T16_
	},
	.SS=
	{
		{
			.Create_=MemC_Func_Casting_(boxc_ss*,BoxC_SS_Create_,ADDRESS,ADDRESS),
			.Delete_=MemC_Func_Casting_(general,xBoxC_VS_Delete_,boxc_ss *_PL_ _R_),
			.Size_=MemC_Func_Casting_(address,BoxC_SS_Size_,BOXC_SS _PL_ _R_),
			.Auto_=MemC_Func_Casting_(boxc_ss*,xBoxC_SS_Auto_,boxc_ss _PL_ _R_)
		},
		.All=
		{
			.Reset_=MemC_Func_Casting_(logical,BoxC_SS_Reset_All_,BOXC_SS _PL_ _R_),
			.Check_=MemC_Func_Casting_(logical,BoxC_SS_Check_All_,BOXC_SS _PL_ _R_)
		},
		{
			.Reset_=MemC_Func_Casting_(logical,BoxC_SS_Reset_,BOXC_SS _PL_ _R_,ADDRESS),
			.Check_=MemC_Func_Casting_(logical,BoxC_SS_Check_,BOXC_SS _PL_ _R_,ADDRESS)
		},
		{
			.Push_=MemC_Func_Casting_(logical,BoxC_SS_Push_,BOXC_SS _PL_ _R_,ADDRESS,general _PL_),
			.Pop_=MemC_Func_Casting_(general*,BoxC_SS_Pop_,BOXC_SS _PL_ _R_,ADDRESS),
			.Peek_=MemC_Func_Casting_(general*,BoxC_SS_Peek_,BOXC_SS _PL_ _R_,ADDRESS,ADDRESS),
			.Spread_=MemC_Func_Casting_(logical,BoxC_SS_Spread_,boxc_li _PL_ _R_,BOXC_SS _PL_ _R_,ADDRESS)
		}
	},
	.QS=
	{
		{
			.Create_=MemC_Func_Casting_(boxc_qs*,BoxC_QS_Create_,ADDRESS,ADDRESS),
			.Delete_=MemC_Func_Casting_(general,xBoxC_VS_Delete_,boxc_qs *_PL_ _R_),
			.Size_=MemC_Func_Casting_(address,BoxC_QS_Size_,BOXC_QS _PL_ _R_),
			.Auto_=MemC_Func_Casting_(boxc_qs*,xBoxC_QS_Auto_,boxc_qs _PL_ _R_)
		},
		.All=
		{
			.Reset_=MemC_Func_Casting_(logical,BoxC_QS_Reset_All_,BOXC_QS _PL_ _R_),
			.Check_=MemC_Func_Casting_(logical,BoxC_QS_Check_All_,BOXC_QS _PL_ _R_)
		},
		{
			.Reset_=MemC_Func_Casting_(logical,BoxC_QS_Reset_,BOXC_QS _PL_ _R_,ADDRESS),
			.Check_=MemC_Func_Casting_(logical,BoxC_QS_Check_,BOXC_QS _PL_ _R_,ADDRESS)
		},
		{
			.Enque_=MemC_Func_Casting_(logical,BoxC_QS_Enque_,BOXC_QS _PL_ _R_,ADDRESS,general _PL_),
			.Deque_=MemC_Func_Casting_(general*,BoxC_QS_Deque_,BOXC_QS _PL_ _R_,ADDRESS),
			.Peek_=MemC_Func_Casting_(general*,BoxC_QS_Peek_,BOXC_QS _PL_ _R_,ADDRESS,ADDRESS),
			.Spread_=MemC_Func_Casting_(logical,BoxC_QS_Spread_,boxc_li _PL_ _R_,BOXC_QS _PL_ _R_,ADDRESS)
		}
	},
	.RS=
	{
		{
			.Create_=MemC_Func_Casting_(boxc_rs*,BoxC_RS_Create_,ADDRESS,ADDRESS),
			.Delete_=MemC_Func_Casting_(general,xBoxC_VS_Delete_,boxc_rs *_PL_ _R_),
			.Size_=MemC_Func_Casting_(address,BoxC_RS_Size_,BOXC_RS _PL_ _R_),
			.Auto_=MemC_Func_Casting_(boxc_rs*,xBoxC_RS_Auto_,boxc_rs _PL_ _R_)
		},
		.All=
		{
			.Reset_=MemC_Func_Casting_(logical,BoxC_RS_Reset_All_,BOXC_RS _PL_ _R_),
			.Check_=MemC_Func_Casting_(logical,BoxC_RS_Check_All_,BOXC_RS _PL_ _R_)
		},
		{
			.Reset_=MemC_Func_Casting_(logical,BoxC_RS_Reset_,BOXC_RS _PL_ _R_,ADDRESS),
			.Check_=MemC_Func_Casting_(logical,BoxC_RS_Check_,BOXC_RS _PL_ _R_,ADDRESS)
		},
		{
			.Insert_=MemC_Func_Casting_(logical,BoxC_RS_Insert_,BOXC_RS _PL_ _R_,ADDRESS,general _PL_,LOGICAL),
			.Desert_=MemC_Func_Casting_(logical,BoxC_RS_Desert_,BOXC_RS _PL_ _R_,ADDRESS,LOGICAL),
			.Read_=MemC_Func_Casting_(general*,BoxC_RS_Read_,BOXC_RS _PL_ _R_,ADDRESS,LOGICAL),
			.Spread_=MemC_Func_Casting_(logical,BoxC_RS_Spread_,boxc_li _PL_ _R_,BOXC_RS _PL_ _R_,ADDRESS,SINTPTR,LOGICAL)
		},
		{
			.Rotate_=MemC_Func_Casting_(logical,BoxC_RS_Rotate_,BOXC_RS _PL_ _R_,ADDRESS,SINTPTR),
			.Flip_=MemC_Func_Casting_(logical,BoxC_RS_Flip_,BOXC_RS _PL_ _R_,ADDRESS)
		}
	},
	.KS=
	{
		{
			.Create_=BoxC_KS_Create_,
			.Delete_=MemC_Func_Casting_(general,xBoxC_VS_Delete_,boxc_ks *_PL_ _R_),
			.Size_=BoxC_KS_Size_,
			.Auto_=xBoxC_KS_Auto_
		},
		{
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
		{
			.Reset_=BoxC_KS_Reset_,
			.Height_=BoxC_KS_Height_
		}
	},
	.FS=
	{
		{
			.Create_=BoxC_FS_Create_,
			.Delete_=MemC_Func_Casting_(general,xBoxC_VS_Delete_,boxc_fs *_PL_ _R_),
			.Size_=BoxC_FS_Size_,
			.Toggle_=BoxC_FS_Toggle_
		},
		.All=
		{
			.Reset_=BoxC_FS_Reset_All_,
			.Check_=BoxC_FS_Check_All_
		},
		{
			.Writer_=BoxC_FS_Writer_,
			.Reader_=BoxC_FS_Reader_
		}
	},
	.Tr=
	{
		{
			.Create_=BoxC_Tr_Create_,
			.Delete_=BoxC_Tr_Delete_,
			.Size_=BoxC_Tr_Size_,
			.Used_=BoxC_Tr_Used_
		},
		{
			.Left_=BoxC_Tr_Left_,
			.Origin_=BoxC_Tr_Origin_,
			.Height_=BoxC_Tr_Height_,
			.Move_=BoxC_Tr_Move_
		}
	},
	.Sw=
	{
		.Create_=BoxC_Sw_Create_,
		.Delete_=MemC_Func_Casting_(general,xBoxC_VS_Delete_,boxc_sw *_PL_ _R_),
		.Size_=BoxC_Sw_Size_,
		.Find_=BoxC_Sw_Find_
	},
	.Li=
	{
		{
			.Create_=BoxC_Li_Create_,
			.Delete_=MemC_Func_Casting_(general,xBoxC_VS_Delete_,boxc_li *_PL_ _R_),
			.Size_=BoxC_Li_Size_,
			.Reverse_=BoxC_Li_Reverse_
		},
		{
			.Reset_=BoxC_Li_Reset_,
			.Check_=BoxC_Li_Check_
		},
		{
			.Tip=
			{
				.Insert_=BoxC_Li_Tip_Append_,
				.Desert_=BoxC_Li_Tip_Remove_
			},
			.One=
			{
				.Insert_=BoxC_Li_One_Insert_,
				.Desert_=BoxC_Li_One_Desert_
			},
			.Lot=
			{
				.Insert_=BoxC_Li_Lot_Insert_,
				.Desert_=BoxC_Li_Lot_Desert_
			},
			.Do=
			{
				.Copy_=BoxC_Li_Copy_,
				.Filter_=BoxC_Li_Filter_
			}
		}
	}
};
extern BOXCASE *BoxC_(general) { return &BoxC; }
#endif
