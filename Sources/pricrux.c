#ifdef _INC_PRICLIP
#ifdef _SRC_PRICRUX

static_assert(sizeof(data_xx)==sizeof(pric_xx),"sizeof(" PriC_Meta_(data_xx) ") != sizeof(" PriC_Meta_(pric_xx) ")");

static logical PriC_Func_(_PriC_Seed_,DXX)(pric_xx _PL_ _R_ Table)
{
	DATA_XX Count=Table->Count;
	data_xx _PL_ _R_ Prime=(data_xx*)(Table->Prime);

	Prime[0]=2;
	if(Count>1)
	{
		Prime[1]=3;
		return (Count>2);
	}
	else
		return 0;
}
static general PriC_Func_(_PriC_Fill_,DXX)(pric_xx _PL_ _R_ Table)
{
	ADDRESS Count=(address)(Table->Count);
	data_xx _PL_ _R_ Prime=(data_xx*)(Table->Prime);
	data_xx Num=5;

	for(address Cnt=2,Max=1,Idx;1;Max++,Num+=2)
		for(DATA_XX Bnd=Prime[Max],Squ=Bnd*Bnd;Num!=Squ;Num+=2)
			for(data_xx Mod=Prime[Idx=1];1;Mod=Prime[++Idx])
				if(Mod<Bnd)
					if(Num%Mod);
					else
						break;
				else
				{
					Prime[Cnt++]=Num;
					if(Cnt<Count)
						break;
					else
						return;
				}
}
_PRIC_ pric_xx *PriC_Func_(PriC_Create_,DXX)(DATA_XX Count)
{
	if(Count>ConstLimit.DXX);
	else if(Count>PriC.Count.DXX);
	else
	{
		pric_xx *Table;

		if(Count)
		{
			MemC_Temp_(ADDRESS,Temp=MemC.Size.Mul_((address)Count,sizeof(data_xx)))
				Table=(Temp)?(MemC.Alloc.Byte_(MemC.Size.Add_(sizeof(pric_xx),Temp))):(NULL);

			if(Table)
			{
				Acs_(data_xx,Table->Count)=Count;
				if(PriC_Func_(_PriC_Seed_,DXX)(Table))
					PriC_Func_(_PriC_Fill_,DXX)(Table);
				else;
			}
			else;
		}
		else
		{
			Table=MemC_Alloc_Unit_(pric_xx);
			if(Table)
				MemC_Clear_Unit_(Table);
			else;
		}
		
		return Table;
	}

	return NULL;
}

_PRIC_ logical PriC_Func_(PriC_Save_,DXX)(FILE _PL_ File,DATA_XX _PL_ _R_ Table)
{
	if(Table)
	{
		fpos_t Back;

		if(fgetpos(File,&Back));
		else
		{
			ADDRESS Length=(address)((*Table)+1);

			if(PenC_File_Writer_(File,Table,Length)==Length)
				return 1;
			else
				fsetpos(File,&Back);
		}
	}
	else;

	return 0;
}
_PRIC_ data_xx *PriC_Func_(PriC_Load_,DXX)(FILE _PL_ File,general _PL_ _R_ Nope)
{
	Mute_(Nope);
	fpos_t Back;

	if(fgetpos(File,&Back));
	else
	{
		data_xx Count;

		if(PenC_File_Reader_(File,&Count,1)==1)
		{
			ADDRESS Cast=(address)Count;
			data_xx *Table=MemC_Alloc_ND_(data_xx,1,Cast+1);

			if(Table)
			{
				*Table=Count;
				if(Count)
					if(PenC_File_Reader_(File,Table+1,Cast)==Cast)
						return Table;
					else
						MemC_Deloc_(Table);
				else
					return Table;
			}
			else;
		}
		else;

		fsetpos(File,&Back);
	}

	return NULL;
}

static integer PriC_Func_(_PriC_Comp_,DXX)(DATA_XX _PL_ _R_ A,DATA_XX _PL_ _R_ B)
{
	return (((*A)>(*B))-((*A)<(*B)));
}
_PRIC_ data_xx PriC_Func_(PriC_Search_,DXX)(PRIC_XX _PL_ _R_ Table,DATA_XX Value)
{
	DATA_XX Fail=0;

	if(Table)
	{
		DATA_XX _PL_ Where=bsearch(&Value,Table->Prime,(address)(Table->Count),sizeof(data_xx),PriC_Func_(_PriC_Comp_,DXX));
		
		if(Where)
		{
			ADDRESS Offset=Where-(Table->Prime);

			return ((data_xx)Offset);
		}
		else;
	}
	else;

	return (~Fail);
}

_PRIC_ data_xx PriC_Func_(PriC_Factor_First_,DXX)(PRIC_XX _PL_ _R_ Table,DATA_XX Value)
{
	if(Table)
		if(Value>1)
		{
			DATA_XX _PL_ End=(Table->Prime)+(address)(Table->Count);
			DATA_XX *_R_ Ptr=(Table->Prime);

			while(Ptr<End)
				if(Value%(*Ptr))
					if((*Ptr)<(Value/(*Ptr)))
						Ptr++;
					else
						break;
				else
					return (*Ptr);
		}
		else;
	else;

	return Value;
}
_PRIC_ address PriC_Func_(PriC_Factor_Count_,DXX)(PRIC_XX _PL_ _R_ Table,data_xx Value,LOGICAL Mode)
{
	if(Table)
	{
		DATA_XX _PL_ End=(Table->Prime)+(address)(Table->Count);
		DATA_XX *_R_ Ptr=(Table->Prime);
		address Count=0;

		if(Mode)
			for(;(Value>1)&&(Ptr<End);Ptr++)
				if(Value%(*Ptr))
					if((*Ptr)<(Value/(*Ptr)));
					else
					{
						Count++;
						break;
					}
				else
					do
					{
						Count++;
						Value/=*Ptr;
					}
					while(!(Value%(*Ptr)));
		else
			for(;(Value>1)&&(Ptr<End);Ptr++)
				if(Value%(*Ptr))
					if((*Ptr)<(Value/(*Ptr)));
					else
					{
						Count++;
						break;
					}
				else
				{
					Count++;
					do
						Value/=*Ptr;
					while(!(Value%(*Ptr)));
				}

		return Count;
	}
	else;

	return 0;
}

#else

#ifdef XX
#error The macro "XX" is already defined.
#else

#ifdef DXX
#error The macro "DXX" is already defined.
#else
#define DXX PriC_TXX_(D,XX)
#endif

#ifdef data_xx
#error The macro "data_xx" is already defined.
#else
#define data_xx PriC_Type_(data,XX)
#endif

#ifdef DATA_XX
#error The macro "DATA_XX" is already defined.
#else
#define DATA_XX PriC_Type_(DATA,XX)
#endif

#ifdef pric_xx
#error The macro "pric_xx" is already defined.
#else
#define pric_xx PriC_Type_(pric,XX)
#endif

#ifdef PRIC_XX
#error The macro "PRIC_XX" is already defined.
#else
#define PRIC_XX PriC_Type_(PRIC,XX)
#endif

#define _SRC_PRICRUX

#define XX 08
#include "pricrux.c"
#undef XX
#define XX 16
#include "pricrux.c"
#undef XX
#define XX 32
#include "pricrux.c"
#undef XX
#define XX 64
#include "pricrux.c"
#undef XX

#undef _SRC_PRICRUX

#undef PRIC_XX
#undef pric_xx
#undef DATA_XX
#undef data_xx
#undef DXX
#endif
#endif

#else
static void _PriC_Void_(void) { (void)(_PriC_Void_);return; }
#endif
