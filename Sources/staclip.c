#include "staclip.h"

struct _stac_l2 { stac_l2 *L[2]; };

static BYTE_08 IdiomVersion[16]="Date:2018.09.13";
BYTE_08 _PL_ StaClip=IdiomVersion;

static address _StaC_Overflow_Add_(ADDRESS A,ADDRESS B)
{
	address C=A+B;

	if(C<A)
		C=0;
	else
		if(C<B)
			C=0;

	return C;
}
static address _StaC_Overflow_Mul_(ADDRESS A,ADDRESS B)
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
static general _StaC_Initialize_(stac_l2 *_R_ Ptr,STAC_L2 _PL_ Last)
{
	for(;Ptr<Last;Ptr[-1].L[1]=Ptr)
		Ptr++;

	Ptr[0].L[1]=NULL;
}
static general _StaC_Setup_(STAC_SS _PL_ S)
{
	if(S->Nums)
	{
		MemC_Clear_1D_(S->Stack,S->Nums,stac_l2*);
		MemC_Clear_1D_((address*)(S->Lngs),S->Nums,address);
	}
	((address*)(S->Lngs))[-1]=S->Caps;

	if(S->Caps)
	{
		S->Stack[-1]=(stac_l2*)(S->Stack+S->Nums);
		_StaC_Initialize_(S->Stack[-1],S->Stack[-1]+(S->Caps-1));
	}
	else
		S->Stack[-1]=NULL;
}
stac_ss *StaC_SS_Create_(ADDRESS Nums,ADDRESS Caps)
{
	stac_ss *S;

	{
		address TempA=_StaC_Overflow_Add_(Nums,1);

		TempA=_StaC_Overflow_Mul_(TempA,sizeof(stac_l2*)+sizeof(address));
		if(TempA)
			if(Caps)
			{
				address TempB=_StaC_Overflow_Mul_(Caps,sizeof(stac_l2));

				if(TempB)
				{
					TempA=_StaC_Overflow_Add_(TempA,TempB);
					if(TempA)
					{
						TempA=_StaC_Overflow_Add_(TempA,sizeof(stac_ss));
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
				TempA=_StaC_Overflow_Add_(TempA,sizeof(stac_ss));
				S=MemC_Alloc_Byte_(TempA);
			}
		else
			S=NULL;
	}
	if(S)
	{
		Acs_(address*,S->Lngs)=(address*)(S+1)+1;
		Acs_(stac_l2**,S->Stack)=(stac_l2**)(S->Lngs+Nums)+1;

		Acs_(address,S->Nums)=Nums;
		Acs_(address,S->Caps)=Caps;

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
		Temp=S->Nums+1;
		Temp=MemC_Size_(stac_ss,1)+MemC_Size_(stac_l2*,Temp)+MemC_Size_(address,Temp)+MemC_Size_(stac_l2,S->Caps);
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
		if(Select<S->Nums)
			if(S->Lngs[-1])
			{
				_StaC_Swap_(S->Stack-1,S->Stack+Select,(general**)(&Contents));

				((address*)(S->Lngs))[-1]--;
				((address*)(S->Lngs))[Select]++;

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
		if(Select<S->Nums)
			if(S->Lngs[Select])
			{
				_StaC_Swap_(S->Stack+Select,S->Stack-1,&Return);

				((address*)(S->Lngs))[-1]++;
				((address*)(S->Lngs))[Select]--;
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
		if(Select<S->Nums)
			if(S->Lngs[Select])
			{
				_StaC_Reset_(S->Stack+Select,S->Stack-1);

				((address*)(S->Lngs))[-1]+=S->Lngs[Select];
				((address*)(S->Lngs))[Select]=0;

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
