#ifdef _INC_PRICLIP
#ifdef _SRC_PRICRUX

static_assert(sizeof(data_xx)==sizeof(pric_xx),"sizeof(" Meta_(data_xx) ") != sizeof(" Meta_(pric_xx) ")");

static logical PriC_Func_(_PriC_Record_,DXX)(FILE _PL_ File,data_08 _PL_ Mask,ADDRESS Bits)
{
	DATA_XX Nums=(data_xx)_PriC_Nums_(Mask,Bits);
	
	if(Nums)
	{
		logical Flag=0;

		MemC_Temp_ND_(data_xx,Space,;,1,Nums)
		{
			data_xx _PL_ _R_ Table=Space;

			Table[0]=2;
			MemC_Temp_(bitc_bp,Ptr=BitC.BP.Assign.U_(Mask,1))
				for(data_xx Num=1,Value=3;Num<Nums;Value+=2,Ptr=BitC.BP.Jumper.U_(Ptr,1))
				{
					Table[Num]=Value;
					Num+=BitC.BP.Reader_(Ptr);
				}

			if(PenC_File_Writer_(File,&Nums,1)==1)
			{
				ADDRESS Cast=(address)Nums;

				Flag=(PenC_File_Writer_(File,Table,Cast)==Cast);
			}
			else
				Flag=0;
		}

		return Flag;
	}
	else
		return (PenC_File_Writer_(File,&Nums,1)==1);
}
_PRIC_ logical PriC_Func_(PriC_Save_,DXX)(FILE _PL_ File,ADDRESS Bits)
{
	fpos_t Back;

	if(PenC.File.Pose.Get_(File,&Back));
	else
	{
		if(Bits>(sizeof(address)<<3));
		else if(Bits>(sizeof(data_xx)<<3));
		else if(Bits>8)
		{
			ADDRESS Bytes=((address)(1))<<(Bits-4);
			logical Flag=0;

			MemC_Temp_ND_(data_08,Space,;,1,Bytes)
			{
				data_08 _PL_ Mask=Space;

				_PriC_Mass_(Mask,Bits);
				Flag=PriC_Func_(_PriC_Record_,DXX)(File,Mask,Bits);
			}
			if(Flag)
				return 1;
			else;
		}
		else
		{
			data_08 Mask[16];

			_PriC_Mass_(Mask,Bits);
			if(PriC_Func_(_PriC_Record_,DXX)(File,Mask,Bits))
				return 1;
			else;
		}

		PenC.File.Pose.Set_(File,Back);
	}

	return 0;
}
_PRIC_ data_xx *PriC_Func_(PriC_Load_,DXX)(FILE _PL_ File,DATA_XX _PL_ _R_ Nums)
{
	fpos_t Back;

	if(PenC.File.Pose.Get_(File,&Back));
	else
	{
		data_xx Temp;

		if(PenC_File_Reader_(File,&Temp,1)==1)
		{
			data_xx Count;

			if(Nums)
				if(Temp<(*Nums))
					goto FAIL;
				else
					Count=*Nums;
			else
				Count=Temp;

			MemC_Temp_(ADDRESS,Cast=(address)Count)
			{
				data_xx *Table=MemC_Alloc_ND_(data_xx,1,Cast+1);

				if(Table)
				{
					*Table=Count;
					if(Count)
						if(PenC_File_Reader_(File,Table+1,Cast)==Cast);
						else
							goto KILL;
					else;

					if(PenC_File_Jumper_(File,(address)(Temp-Count),data_xx))
KILL:					MemC_Deloc_(Table);
					else
						return Table;
				}
				else;
			}
		}
		else;
FAIL:
		PenC.File.Pose.Set_(File,Back);
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
		DATA_XX _PL_ Where=bsearch(&Value,Table->Prime,(address)(Table->Count),sizeof(data_xx),MemC_Func_Casting_(integer,PriC_Func_(_PriC_Comp_,DXX),GENERAL _PL_,GENERAL _PL_));
		
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

_PRIC_ logical PriC_Func_(PriC_Factor_,DXX)(data_xx _PL_ _R_ Factor,PRIC_XX _PL_ _R_ Table,data_xx Value)
{
	if(Factor)
	{
		*Factor=0;

		if(Table)
			if(Table->Count)
				if(Value)
					for(DATA_XX *_R_ Ptr=(Table->Prime),_PL_ End=Ptr+(address)(Table->Count);1;)
						if(Value%(*Ptr))
							if((*Ptr)<(Value/(*Ptr)))
								if((++Ptr)<End);
								else
									break;
							else
							{
								if(Value>1)
									Factor[++(*Factor)]=Value;
								else;

								return 1;
							}
						else
							Value/=Factor[++(*Factor)]=*Ptr;
				else;
			else;
		else;

		Factor[++(*Factor)]=Value;
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
