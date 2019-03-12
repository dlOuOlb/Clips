#include "bitclip.h"

#if(MemC_Fold_(Definition:Macros))
#ifdef D
#error The macro "D" is already defined.
#else
#define D() (0)
#endif

#ifdef I
#error The macro "I" is already defined.
#else
#define I() (-1)
#endif

#ifdef R
#error The macro "R" is already defined.
#else
#define R() (+1)
#endif

#ifdef S
#ifdef SYPE
#error The macro "SYPE" is already defined.
#else
#ifdef sype
#error The macro "sype" is already defined.
#else
#if(S()==D())
#define SYPE DATA
#define sype data
#elif(S()==I())
#define SYPE INTE
#define sype inte
#elif(S()==R())
#define SYPE REAL
#define sype real
#else
#error The macro "S" is defined out of this context.
#endif
#endif
#endif
#endif

#ifdef T
#ifdef TYPE
#error The macro "TYPE" is already defined.
#else
#ifdef type
#error The macro "type" is already defined.
#else
#if(T()==D())
#define TYPE DATA
#define type data
#elif(T()==I())
#define TYPE INTE
#define type inte
#elif(T()==R())
#define TYPE REAL
#define type real
#else
#error The macro "T" is defined out of this context.
#endif
#endif
#endif
#endif
#endif

#if(MemC_Fold_(Definition:Function Templates))
#ifdef _BitC_Caster_
general BitC_Cast_(BitC_TXX_(S,OO),BitC_TXX_(T,XX))(BitC_Type_(SYPE,OO) *_R_ DataI,BitC_Type_(type,XX) *_R_ DataO,DATA_32 Length)
{
#if(T()==R())
#define BitC_Gate_(Data,Min,Max) (Data)
#else
#if(S()==R())
#define BitC_Gate_(Data,Min,Max) _BitC_Clamp_(Data,Min,Max)
	BitC_Type_(SYPE,OO) Min=(BitC_Type_(SYPE,OO))((BitC_Type_(TYPE,XX))(((BitC_Type_(TYPE,XX))T())<<(BitC_XX_(XX)-1)));
	BitC_Type_(SYPE,OO) Max=(BitC_Type_(SYPE,OO))((BitC_Type_(TYPE,XX))(~(((BitC_Type_(TYPE,XX))T())<<(BitC_XX_(XX)-1))));
#else
#if(T()==I())
#if(S()==I())
#if(BitC_XX_(OO)>BitC_XX_(XX))
#define BitC_Gate_(Data,Min,Max) _BitC_Clamp_(Data,Min,Max)
	BitC_Type_(SYPE,OO) Min=((BitC_Type_(SYPE,OO))T())<<((1-BitC_XX_(XX))*T());
	BitC_Type_(SYPE,OO) Max=(((BitC_Type_(SYPE,OO))(+1))<<(BitC_XX_(XX)+T()))-1;
#else
#define BitC_Gate_(Data,Min,Max) (Data)
#endif
#else
#define BitC_Gate_(Data,Min,Max) _BitC_Min_(Data,Max)
	BitC_Type_(SYPE,OO) Max=(((BitC_Type_(SYPE,OO))(+1))<<(BitC_XX_(XX)+T()))-1;
#endif
#else
#if(S()==I())
#if(BitC_XX_(OO)>BitC_XX_(XX))
#define BitC_Gate_(Data,Min,Max) _BitC_Clamp_(Data,Min,Max)
	BitC_Type_(SYPE,OO) Min=((BitC_Type_(SYPE,OO))T())<<((1-BitC_XX_(XX))*T());
	BitC_Type_(SYPE,OO) Max=(((BitC_Type_(SYPE,OO))(+1))<<(BitC_XX_(XX)+T()))-1;
#else
#define BitC_Gate_(Data,Min,Max) _BitC_Max_(Data,Min)
	BitC_Type_(SYPE,OO) Min=((BitC_Type_(SYPE,OO))T())<<((1-BitC_XX_(XX))*T());
#endif
#else
#if(BitC_XX_(OO)>BitC_XX_(XX))
#define BitC_Gate_(Data,Min,Max) _BitC_Min_(Data,Max)
	BitC_Type_(SYPE,OO) Max=(((BitC_Type_(SYPE,OO))(+1))<<(BitC_XX_(XX)+T()))-1;
#else
#define BitC_Gate_(Data,Min,Max) (Data)
#endif
#endif
#endif
#endif
#endif
	for(BitC_Type_(SYPE,OO) _PL_ End=DataI+Length;DataI<End;DataI++,DataO++)
		DataO[0]=(BitC_Type_(type,XX))BitC_Gate_(DataI[0],Min,Max);
#undef BitC_Gate_
}
#endif

#ifdef _BitC_BO_S_1_
general BitC_Oper_(BitC_Op_,1,BitC_TXX_(T,XX))(BitC_Type_(type,XX) *DataC,BitC_Type_(TYPE,XX) *DataA,inte_32 Shift,DATA_32 Length)
{
	BitC_Type_(TYPE,XX) *End=DataA+(Length&0xFFFFFFF8);
	
	if(Shift>0)
	{
		for(;DataA<End;DataA+=8,DataC+=8)
		{
			DataC[0]=DataA[0]<<Shift;
			DataC[1]=DataA[1]<<Shift;
			DataC[2]=DataA[2]<<Shift;
			DataC[3]=DataA[3]<<Shift;
			DataC[4]=DataA[4]<<Shift;
			DataC[5]=DataA[5]<<Shift;
			DataC[6]=DataA[6]<<Shift;
			DataC[7]=DataA[7]<<Shift;
		}
		for(End+=(Length&0x00000007);DataA<End;DataA++,DataC++)
			DataC[0]=DataA[0]<<Shift;
	}
	else
	{
		for(Shift=-Shift;DataA<End;DataA+=8,DataC+=8)
		{
			DataC[0]=DataA[0]>>Shift;
			DataC[1]=DataA[1]>>Shift;
			DataC[2]=DataA[2]>>Shift;
			DataC[3]=DataA[3]>>Shift;
			DataC[4]=DataA[4]>>Shift;
			DataC[5]=DataA[5]>>Shift;
			DataC[6]=DataA[6]>>Shift;
			DataC[7]=DataA[7]>>Shift;
		}
		for(End+=(Length&0x00000007);DataA<End;DataA++,DataC++)
			DataC[0]=DataA[0]>>Shift;
	}
}
#endif

#ifdef _BitC_BO_Op_1_
general BitC_Oper_(BitC_Op_,1,BitC_TXX_(D,XX))(BitC_Type_(data,XX) _PL_ DataC,BitC_Type_(DATA,XX) _PL_ DataA,BitC_Type_(DATA,XX) Mask,DATA_32 Length)
{
	DATA_64 Wide=BitC_Func_(_BitC_Wide_Mask_,BitC_TXX_(D,XX))(Mask);
	bitclip End;
	bitclip PtrA;
	bitclip PtrC;

	{
		End.C.G=DataA;
		PtrA.C.G=DataA;
		PtrC.C.G=DataC;
	}
	for(End.C.BitC_TXX_(D,XX)+=(Length&(-512/BitC_XX_(XX)));PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrC.C.D64+=8)
	{
		PtrC.V.D64[0]=BitC_Op_(PtrA.C.D64[0],Wide);
		PtrC.V.D64[1]=BitC_Op_(PtrA.C.D64[1],Wide);
		PtrC.V.D64[2]=BitC_Op_(PtrA.C.D64[2],Wide);
		PtrC.V.D64[3]=BitC_Op_(PtrA.C.D64[3],Wide);
		PtrC.V.D64[4]=BitC_Op_(PtrA.C.D64[4],Wide);
		PtrC.V.D64[5]=BitC_Op_(PtrA.C.D64[5],Wide);
		PtrC.V.D64[6]=BitC_Op_(PtrA.C.D64[6],Wide);
		PtrC.V.D64[7]=BitC_Op_(PtrA.C.D64[7],Wide);
	}
	for(End.C.BitC_TXX_(D,XX)+=(Length&(+448/BitC_XX_(XX)));PtrA.C.G<End.C.G;PtrA.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=BitC_Op_(PtrA.C.D64[0],Wide);
	for(End.C.BitC_TXX_(D,XX)+=(Length&(+56/BitC_XX_(XX)));PtrA.C.G<End.C.G;PtrA.C.BitC_TXX_(D,XX)++,PtrC.C.BitC_TXX_(D,XX)++)
		PtrC.V.BitC_TXX_(D,XX)[0]=BitC_Op_(PtrA.C.BitC_TXX_(D,XX)[0],Mask);
}
#endif

#ifdef _BitC_BO_Op_2_
general BitC_Oper_(BitC_Op_,2,D08)(data_08 _PL_ DataC,DATA_08 _PL_ DataA,DATA_08 _PL_ DataB,DATA_32 Length)
{
	bitclip End;
	bitclip PtrA;
	bitclip PtrB;
	bitclip PtrC;

	{
		End.C.G=DataA;
		PtrA.C.G=DataA;
		PtrB.C.G=DataB;
		PtrC.C.G=DataC;
	}
	for(End.C.D08+=(Length&0xFFFFFFC0);PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrB.C.D64+=8,PtrC.C.D64+=8)
	{
		PtrC.V.D64[0]=BitC_Op_(PtrA.C.D64[0],PtrB.C.D64[0]);
		PtrC.V.D64[1]=BitC_Op_(PtrA.C.D64[1],PtrB.C.D64[1]);
		PtrC.V.D64[2]=BitC_Op_(PtrA.C.D64[2],PtrB.C.D64[2]);
		PtrC.V.D64[3]=BitC_Op_(PtrA.C.D64[3],PtrB.C.D64[3]);
		PtrC.V.D64[4]=BitC_Op_(PtrA.C.D64[4],PtrB.C.D64[4]);
		PtrC.V.D64[5]=BitC_Op_(PtrA.C.D64[5],PtrB.C.D64[5]);
		PtrC.V.D64[6]=BitC_Op_(PtrA.C.D64[6],PtrB.C.D64[6]);
		PtrC.V.D64[7]=BitC_Op_(PtrA.C.D64[7],PtrB.C.D64[7]);
	}
	for(End.C.D08+=(Length&0x00000038);PtrA.C.G<End.C.G;PtrA.C.D64++,PtrB.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=BitC_Op_(PtrA.C.D64[0],PtrB.C.D64[0]);
	for(End.C.D08+=(Length&0x00000007);PtrA.C.G<End.C.G;PtrA.C.D08++,PtrB.C.D08++,PtrC.C.D08++)
		PtrC.V.D08[0]=BitC_Op_(PtrA.C.D08[0],PtrB.C.D08[0]);
}
#endif

#ifdef _BitC_Expand_
general BitC_Func_(BitC_Expand_,BitC_TXX_(D,XX))(DATA_08 *_R_ DataI,BitC_Type_(data,XX) *_R_ DataO,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	INTEGER Masker=BitC_XX_(XX)-1;
	BitC_Type_(DATA,XX) *End=DataO+Safe;
	BitC_Type_(inte,XX) TempA;
	BitC_Type_(inte,XX) TempB;

	for(;DataO<End;DataI++,DataO+=8)
	{
		TempA=(BitC_Type_(inte,XX))(DataI[0]);

		TempB=TempA<<(BitC_XX_(XX)-1);
		TempB>>=Masker;
		DataO[0]=TempB;

		TempB=TempA<<(BitC_XX_(XX)-2);
		TempB>>=Masker;
		DataO[1]=TempB;

		TempB=TempA<<(BitC_XX_(XX)-3);
		TempB>>=Masker;
		DataO[2]=TempB;

		TempB=TempA<<(BitC_XX_(XX)-4);
		TempB>>=Masker;
		DataO[3]=TempB;

		TempB=TempA<<(BitC_XX_(XX)-5);
		TempB>>=Masker;
		DataO[4]=TempB;

		TempB=TempA<<(BitC_XX_(XX)-6);
		TempB>>=Masker;
		DataO[5]=TempB;

		TempB=TempA<<(BitC_XX_(XX)-7);
		TempB>>=Masker;
		DataO[6]=TempB;

		TempB=TempA<<(BitC_XX_(XX)-8);
		TempB>>=Masker;
		DataO[7]=TempB;
	}
	if(Rest)
	{
		integer Shift=Masker;

		for(End+=Rest,TempA=(BitC_Type_(inte,XX))(DataI[0]);DataO<End;DataO++,Shift--)
		{
			TempB=TempA<<Shift;
			TempB>>=Masker;
			DataO[0]=TempB;
		}
	}
}
#endif

#ifdef _BitC_RO_Op_
general BitC_Oper_(BitC_Op_,1,BitC_TXX_(T,XX))(data_08 *_R_ DataC,BitC_Type_(TYPE,XX) *_R_ DataA,BitC_Type_(TYPE,XX) Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;
	
	Mask.C.D64=&Buffer;
	{
		BitC_Type_(TYPE,XX) _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)BitC_Op_(DataA[0],Value);
			Mask.V.D08[1]=(data_08)BitC_Op_(DataA[1],Value);
			Mask.V.D08[2]=(data_08)BitC_Op_(DataA[2],Value);
			Mask.V.D08[3]=(data_08)BitC_Op_(DataA[3],Value);
			Mask.V.D08[4]=(data_08)BitC_Op_(DataA[4],Value);
			Mask.V.D08[5]=(data_08)BitC_Op_(DataA[5],Value);
			Mask.V.D08[6]=(data_08)BitC_Op_(DataA[6],Value);
			Mask.V.D08[7]=(data_08)BitC_Op_(DataA[7],Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)BitC_Op_(DataA[Index],Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_Oper_(BitC_Op_,2,BitC_TXX_(T,XX))(data_08 *_R_ DataC,BitC_Type_(TYPE,XX) *_R_ DataA,BitC_Type_(TYPE,XX) *_R_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;
	
	Mask.C.D64=&Buffer;
	{
		BitC_Type_(TYPE,XX) _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)BitC_Op_(DataA[0],DataB[0]);
			Mask.V.D08[1]=(data_08)BitC_Op_(DataA[1],DataB[1]);
			Mask.V.D08[2]=(data_08)BitC_Op_(DataA[2],DataB[2]);
			Mask.V.D08[3]=(data_08)BitC_Op_(DataA[3],DataB[3]);
			Mask.V.D08[4]=(data_08)BitC_Op_(DataA[4],DataB[4]);
			Mask.V.D08[5]=(data_08)BitC_Op_(DataA[5],DataB[5]);
			Mask.V.D08[6]=(data_08)BitC_Op_(DataA[6],DataB[6]);
			Mask.V.D08[7]=(data_08)BitC_Op_(DataA[7],DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)BitC_Op_(DataA[Index],DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
#endif
#endif

#if(MemC_Fold_(Undefinition:Macros))
#undef type
#undef TYPE
#undef sype
#undef SYPE
#undef R
#undef I
#undef D
#endif
