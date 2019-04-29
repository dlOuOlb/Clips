#ifdef _INC_BITCLIP
#ifdef _SRC_BITCRUX

#ifdef T
#if(T()==D())
#define TYPE DATA
#define type data
#elif(T()==I())
#define TYPE INTE
#define type inte
#elif(T()==R())
#define TYPE REAL
#define type real
#endif
#endif

#ifdef S
#if(S()==D())
#define SYPE DATA
#define sype data
#elif(S()==I())
#define SYPE INTE
#define sype inte
#elif(S()==R())
#define SYPE REAL
#define sype real
#endif
#endif

#ifdef _BitC_Copy_
#ifdef __OPENCL_VERSION__
_K_ BitC_Func_(BitC_Reform_,TXX)(_G_ TYPE_XX _PL_ SData,_G_ type_xx _PL_ TData,_P_ OCLCLIP SStart,_P_ OCLCLIP TStart,OCLCLIP TAmount,_P_ OCLCLIP SShape,_P_ OCLCLIP TShape,_P_ OCLCLIP StoTAxis)
{
	_P_ OCLCLIP Telect=Work_From_(TAmount);
	_P_ oclclip Select;

	Select.N=Telect.S[StoTAxis.N];
	Select.Z=Telect.S[StoTAxis.Z];
	Select.Y=Telect.S[StoTAxis.Y];
	Select.X=Telect.S[StoTAxis.X];

	TData[Work_Into_(Telect,TStart,TShape)]=SData[Work_Into_(Select,SStart,SShape)];
}
#else
_BITC_ general BitC_Func_(BitC_Copy_,TXX)(TYPE_XX *_R_ Source,type_xx *_R_ Target,ADDRESS Length)
{
	MemC_Copy_1D_(Source,Target,Length);
}
#endif
#endif

#ifdef _BitC_Caster_
#if(!(((S()==T())&&(NOO==NXX))||((S()==D())&&(T()==I())&&(NOO<NXX))))
#ifdef __OPENCL_VERSION__
_K_ BitC_Cast_(SOO,TXX)(_G_ SYPE_OO _PL_ IData,_G_ type_xx _PL_ OData,_P_ OCLCLIP IStart,_P_ OCLCLIP OStart,_P_ OCLCLIP Amount,_P_ OCLCLIP IShape,_P_ OCLCLIP OShape)
#else
_BITC_ general BitC_Cast_(SOO,TXX)(SYPE_OO *_R_ DataI,type_xx *_R_ DataO,ADDRESS Length)
#endif
{
#if(T()==R())
#define BitC_Gate_(Data,Min,Max) (Data)
#else
#if(S()==R())
#define BitC_Gate_(Data,Min,Max) _BitC_Clamp_(Data,Min,Max)
	SYPE_OO Min=(sype_oo)((type_xx)(((type_xx)T())<<(NXX-1)));
	SYPE_OO Max=(sype_oo)((type_xx)(~(((type_xx)T())<<(NXX-1))));
#else
#if(T()==I())
#if(S()==I())
#if(NOO>NXX)
#define BitC_Gate_(Data,Min,Max) _BitC_Clamp_(Data,Min,Max)
	SYPE_OO Min=((sype_oo)T())<<((1-NXX)*T());
	SYPE_OO Max=(((sype_oo)(+1))<<(NXX+T()))-1;
#else
#define BitC_Gate_(Data,Min,Max) (Data)
#endif
#else
#define BitC_Gate_(Data,Min,Max) _BitC_Min_(Data,Max)
	SYPE_OO Max=(((sype_oo)(+1))<<(NXX+T()))-1;
#endif
#else
#if(S()==I())
#if(NOO>NXX)
#define BitC_Gate_(Data,Min,Max) _BitC_Clamp_(Data,Min,Max)
	SYPE_OO Min=((sype_oo)T())<<((1-NXX)*T());
	SYPE_OO Max=(((sype_oo)(+1))<<(NXX+T()))-1;
#else
#define BitC_Gate_(Data,Min,Max) _BitC_Max_(Data,Min)
	SYPE_OO Min=((sype_oo)T())<<((1-NXX)*T());
#endif
#else
#if(NOO>NXX)
#define BitC_Gate_(Data,Min,Max) _BitC_Min_(Data,Max)
	SYPE_OO Max=(((sype_oo)(+1))<<(NXX+T()))-1;
#else
#define BitC_Gate_(Data,Min,Max) (Data)
#endif
#endif
#endif
#endif
#endif
#ifdef __OPENCL_VERSION__
	_P_ OCLCLIP Select=Work_From_(Amount);

	OData[Work_Into_(Select,OStart,OShape)]=(type_xx)BitC_Gate_(IData[Work_Into_(Select,IStart,IShape)],Min,Max);
#else
	for(SYPE_OO _PL_ End=DataI+Length;DataI<End;DataI++,DataO++)
		*DataO=(type_xx)BitC_Gate_(*DataI,Min,Max);
#endif
#undef BitC_Gate_
}
#endif
#endif

#ifdef _BitC_BO_N_1_
#ifdef __OPENCL_VERSION__
_K_ BitC_Oper_(BitC_Op_,1,TXX)(_G_ type_xx _PL_ CData,_G_ TYPE_XX _PL_ AData,_P_ OCLCLIP CStart,_P_ OCLCLIP AStart,_P_ OCLCLIP Amount,_P_ OCLCLIP CShape,_P_ OCLCLIP AShape)
{
	_P_ OCLCLIP Select=Work_From_(Amount);

	CData[Work_Into_(Select,CStart,CShape)]=BitC_Op_(AData[Work_Into_(Select,AStart,AShape)]);
}
#else
_BITC_ general BitC_Oper_(BitC_Op_,1,TXX)(type_xx _PL_ DataC,TYPE_XX _PL_ DataA,ADDRESS Length)
{
#if(NXX>8)
	BitC_Oper_(BitC_Op_,1,D08)((data_08*)DataC,(data_08*)DataA,Length*(NXX>>3));
#else
	bitclip End;End.C.G=DataA;
	bitclip PtrA;PtrA.C.G=DataA;
	bitclip PtrC;PtrC.C.G=DataC;

	for(End.C.D08+=(Length&ConstantSafe[6]);PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrC.C.D64+=8)
	{
		PtrC.V.D64[0]=BitC_Op_(PtrA.C.D64[0]);
		PtrC.V.D64[1]=BitC_Op_(PtrA.C.D64[1]);
		PtrC.V.D64[2]=BitC_Op_(PtrA.C.D64[2]);
		PtrC.V.D64[3]=BitC_Op_(PtrA.C.D64[3]);
		PtrC.V.D64[4]=BitC_Op_(PtrA.C.D64[4]);
		PtrC.V.D64[5]=BitC_Op_(PtrA.C.D64[5]);
		PtrC.V.D64[6]=BitC_Op_(PtrA.C.D64[6]);
		PtrC.V.D64[7]=BitC_Op_(PtrA.C.D64[7]);
	}
	for(End.C.D08+=(Length&(ConstantRest[6]^ConstantRest[3]));PtrA.C.G<End.C.G;PtrA.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=BitC_Op_(PtrA.C.D64[0]);
	for(End.C.D08+=(Length&ConstantRest[3]);PtrA.C.G<End.C.G;PtrA.C.D08++,PtrC.C.D08++)
		PtrC.V.D08[0]=BitC_Op_(PtrA.C.D08[0]);
#endif
}
#endif
#endif

#ifdef _BitC_BO_S_1_
#ifdef __OPENCL_VERSION__
#if(T()==D())
_K_ BitC_Oper_(BitC_Op_,L,TXX)(_G_ type_xx _PL_ CData,_G_ TYPE_XX _PL_ AData,_P_ OCLCLIP CStart,_P_ OCLCLIP AStart,_P_ OCLCLIP Amount,_P_ OCLCLIP CShape,_P_ OCLCLIP AShape,INTEGER Shift)
{
	_P_ OCLCLIP Select=Work_From_(Amount);

	CData[Work_Into_(Select,CStart,CShape)]=AData[Work_Into_(Select,AStart,AShape)]<<Shift;
}
#endif
_K_ BitC_Oper_(BitC_Op_,R,TXX)(_G_ type_xx _PL_ CData,_G_ TYPE_XX _PL_ AData,_P_ OCLCLIP CStart,_P_ OCLCLIP AStart,_P_ OCLCLIP Amount,_P_ OCLCLIP CShape,_P_ OCLCLIP AShape,INTEGER Shift)
{
	_P_ OCLCLIP Select=Work_From_(Amount);

	CData[Work_Into_(Select,CStart,CShape)]=AData[Work_Into_(Select,AStart,AShape)]>>Shift;
}
#else
_BITC_ general BitC_Oper_(BitC_Op_,1,TXX)(type_xx *DataC,TYPE_XX *DataA,integer Shift,ADDRESS Length)
{
	TYPE_XX *End=DataA+(Length&ConstantSafe[3]);

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
		for(End+=(Length&ConstantRest[3]);DataA<End;DataA++,DataC++)
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
		for(End+=(Length&ConstantRest[3]);DataA<End;DataA++,DataC++)
			DataC[0]=DataA[0]>>Shift;
	}
}
#endif
#endif

#ifdef _BitC_BO_Op_
#ifdef __OPENCL_VERSION__
_K_ BitC_Oper_(BitC_Op_,1,TXX)(_G_ type_xx _PL_ CData,_G_ TYPE_XX _PL_ AData,_P_ OCLCLIP CStart,_P_ OCLCLIP AStart,_P_ OCLCLIP Amount,_P_ OCLCLIP CShape,_P_ OCLCLIP AShape,_P_ TYPE_XX Mask)
{
	_P_ OCLCLIP Select=Work_From_(Amount);

	CData[Work_Into_(Select,CStart,CShape)]=BitC_Op_(AData[Work_Into_(Select,AStart,AShape)],Mask);
}
_K_ BitC_Oper_(BitC_Op_,2,TXX)(_G_ type_xx _PL_ CData,_G_ TYPE_XX _PL_ AData,_G_ TYPE_XX _PL_ BData,_P_ OCLCLIP CStart,_P_ OCLCLIP AStart,_P_ OCLCLIP BStart,_P_ OCLCLIP Amount,_P_ OCLCLIP CShape,_P_ OCLCLIP AShape,_P_ OCLCLIP BShape)
{
	_P_ OCLCLIP Select=Work_From_(Amount);

	CData[Work_Into_(Select,CStart,CShape)]=BitC_Op_(AData[Work_Into_(Select,AStart,AShape)],BData[Work_Into_(Select,BStart,BShape)]);
}
#else
_BITC_ general BitC_Oper_(BitC_Op_,1,TXX)(type_xx _PL_ DataC,TYPE_XX _PL_ DataA,TYPE_XX Mask,ADDRESS Length)
{
	DATA_64 Wide=BitC_Func_(_BitC_Wide_Mask_,TXX)(Mask);
	bitclip End;End.C.G=DataA;
	bitclip PtrA;PtrA.C.G=DataA;
	bitclip PtrC;PtrC.C.G=DataC;

	for(End.C.TXX+=(Length&(-512/NXX));PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrC.C.D64+=8)
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
	for(End.C.TXX+=(Length&(+448/NXX));PtrA.C.G<End.C.G;PtrA.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=BitC_Op_(PtrA.C.D64[0],Wide);
	for(End.C.TXX+=(Length&(+56/NXX));PtrA.C.G<End.C.G;PtrA.C.TXX++,PtrC.C.TXX++)
		PtrC.V.TXX[0]=BitC_Op_(PtrA.C.TXX[0],Mask);
}
_BITC_ general BitC_Oper_(BitC_Op_,2,TXX)(type_xx _PL_ DataC,TYPE_XX _PL_ DataA,TYPE_XX _PL_ DataB,ADDRESS Length)
{
#if(NXX>8)
	BitC_Oper_(BitC_Op_,2,D08)((data_08*)DataC,(data_08*)DataA,(data_08*)DataB,Length*(NXX>>3));
#else
	bitclip End;End.C.G=DataA;
	bitclip PtrA;PtrA.C.G=DataA;
	bitclip PtrB;PtrB.C.G=DataB;
	bitclip PtrC;PtrC.C.G=DataC;

	for(End.C.D08+=(Length&ConstantSafe[6]);PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrB.C.D64+=8,PtrC.C.D64+=8)
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
	for(End.C.D08+=(Length&(ConstantRest[6]^ConstantRest[3]));PtrA.C.G<End.C.G;PtrA.C.D64++,PtrB.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=BitC_Op_(PtrA.C.D64[0],PtrB.C.D64[0]);
	for(End.C.D08+=(Length&ConstantRest[3]);PtrA.C.G<End.C.G;PtrA.C.D08++,PtrB.C.D08++,PtrC.C.D08++)
		PtrC.V.D08[0]=BitC_Op_(PtrA.C.D08[0],PtrB.C.D08[0]);
#endif
}
#endif
#endif

#ifdef _BitC_Expand_
#ifndef __OPENCL_VERSION__
_BITC_ general BitC_Func_(BitC_Expand_,TXX)(DATA_08 *_R_ DataI,type_xx *_R_ DataO,ADDRESS Length)
{
	ADDRESS Safe=Length&ConstantSafe[3];
	ADDRESS Rest=Length&ConstantRest[3];
	INTEGER Masker=NXX-1;
	TYPE_XX *End=DataO+Safe;
	BitC_Type_(inte,XX) TempA;
	BitC_Type_(inte,XX) TempB;

	for(;DataO<End;DataI++,DataO+=8)
	{
		TempA=(BitC_Type_(inte,XX))(DataI[0]);

		TempB=TempA<<(NXX-1);
		TempB>>=Masker;
		DataO[0]=TempB;

		TempB=TempA<<(NXX-2);
		TempB>>=Masker;
		DataO[1]=TempB;

		TempB=TempA<<(NXX-3);
		TempB>>=Masker;
		DataO[2]=TempB;

		TempB=TempA<<(NXX-4);
		TempB>>=Masker;
		DataO[3]=TempB;

		TempB=TempA<<(NXX-5);
		TempB>>=Masker;
		DataO[4]=TempB;

		TempB=TempA<<(NXX-6);
		TempB>>=Masker;
		DataO[5]=TempB;

		TempB=TempA<<(NXX-7);
		TempB>>=Masker;
		DataO[6]=TempB;

		TempB=TempA<<(NXX-8);
		TempB>>=Masker;
		DataO[7]=TempB;
	}
	if(Rest)
	{
		End+=Rest;
		TempA=(BitC_Type_(inte,XX))(DataI[0]);
		for(integer Shift=Masker;DataO<End;DataO++,Shift--)
		{
			TempB=TempA<<Shift;
			TempB>>=Masker;
			DataO[0]=TempB;
		}
	}
}
#endif
#endif

#ifdef _BitC_RO_Op_
#ifdef __OPENCL_VERSION__
_K_ BitC_Oper_(BitC_Op_,1,TXX)(_G_ BitC_Type_(inte,XX) _PL_ CData,_G_ TYPE_XX _PL_ AData,_P_ OCLCLIP CStart,_P_ OCLCLIP AStart,_P_ OCLCLIP Amount,_P_ OCLCLIP CShape,_P_ OCLCLIP AShape,_P_ TYPE_XX Value)
{
	_P_ OCLCLIP Select=Work_From_(Amount);
	_P_ BitC_Type_(INTE,XX) Temp=BitC_Op_(AData[Work_Into_(Select,AStart,AShape)],Value);

	CData[Work_Into_(Select,CStart,CShape)]=-Temp;
}
_K_ BitC_Oper_(BitC_Op_,2,TXX)(_G_ BitC_Type_(inte,XX) _PL_ CData,_G_ TYPE_XX _PL_ AData,_G_ TYPE_XX _PL_ BData,_P_ OCLCLIP CStart,_P_ OCLCLIP AStart,_P_ OCLCLIP BStart,_P_ OCLCLIP Amount,_P_ OCLCLIP CShape,_P_ OCLCLIP AShape,_P_ OCLCLIP BShape)
{
	_P_ OCLCLIP Select=Work_From_(Amount);
	_P_ BitC_Type_(INTE,XX) Temp=BitC_Op_(AData[Work_Into_(Select,AStart,AShape)],BData[Work_Into_(Select,BStart,BShape)]);

	CData[Work_Into_(Select,CStart,CShape)]=-Temp;
}
#else
_BITC_ general BitC_Oper_(BitC_Op_,1,TXX)(data_08 *_R_ DataC,TYPE_XX *_R_ DataA,TYPE_XX Value,ADDRESS Length)
{
	ADDRESS Safe=Length&ConstantSafe[3];
	ADDRESS Rest=Length&ConstantRest[3];
	data_64 Buffer;
	bitclip Mask;Mask.C.D64=&Buffer;

	for(TYPE_XX _PL_ End=DataA+Safe;DataA<End;DataA+=8,DataC++)
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
	if(Rest)
	{
		Mask.V.D64[0]=0;
		for(address Index=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)BitC_Op_(DataA[Index],Value);
			Mask.V.D08[Index]<<=Index;
		}
		_BitC_RO_Loop_B_(Mask,Rest);

		DataC[0]&=Mask.C.D08[1];
		DataC[0]|=Mask.C.D08[0];
	}
}
_BITC_ general BitC_Oper_(BitC_Op_,2,TXX)(data_08 *_R_ DataC,TYPE_XX *_R_ DataA,TYPE_XX *_R_ DataB,ADDRESS Length)
{
	ADDRESS Safe=Length&ConstantSafe[3];
	ADDRESS Rest=Length&ConstantRest[3];
	data_64 Buffer;
	bitclip Mask;Mask.C.D64=&Buffer;

	for(TYPE_XX _PL_ End=DataA+Safe;DataA<End;DataA+=8,DataB+=8,DataC++)
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
	if(Rest)
	{
		Mask.V.D64[0]=0;
		for(address Index=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)BitC_Op_(DataA[Index],DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		_BitC_RO_Loop_B_(Mask,Rest);

		DataC[0]&=Mask.C.D08[1];
		DataC[0]|=Mask.C.D08[0];
	}
}
#endif
#endif

#undef sype
#undef SYPE
#undef type
#undef TYPE

#else

#if defined(_BitC_Caster_)&&!defined(_SRC_CASTING)

#define NOO BitC_XX_(OO)
#define SOO BitC_TXX_(S,OO)
#define SYPE_OO BitC_Type_(SYPE,OO)
#define sype_oo BitC_Type_(sype,OO)

#define _SRC_CASTING

#define _BitC_Min_(A,B) (((A)<(B))?(A):(B))
#define _BitC_Max_(A,B) (((A)>(B))?(A):(B))
#define _BitC_Clamp_(Data,Min,Max) (((Data)<(Min))?(Min):(((Data)>(Max))?(Max):(Data)))

#define _BitC_Data_
#define _BitC_Inte_
#define _BitC_Real_

#define S D
#define OO 08
#include "bitcrux.c"
#undef OO
#define OO 16
#include "bitcrux.c"
#undef OO
#define OO 32
#include "bitcrux.c"
#undef OO
#define OO 64
#include "bitcrux.c"
#undef OO
#undef S

#define S I
#define OO 08
#include "bitcrux.c"
#undef OO
#define OO 16
#include "bitcrux.c"
#undef OO
#define OO 32
#include "bitcrux.c"
#undef OO
#define OO 64
#include "bitcrux.c"
#undef OO
#undef S

#define S R
#ifdef __OPENCL_VERSION__
#if(_BitC_R16_)
#define OO 16
#include "bitcrux.c"
#undef OO
#endif
#define OO 32
#include "bitcrux.c"
#undef OO
#if(_BitC_R64_)
#define OO 64
#include "bitcrux.c"
#undef OO
#endif
#else
#define OO 32
#include "bitcrux.c"
#undef OO
#define OO 64
#include "bitcrux.c"
#undef OO
#endif
#undef S

#undef _BitC_Real_
#undef _BitC_Inte_
#undef _BitC_Data_

#undef _BitC_Clamp_
#undef _BitC_Max_
#undef _BitC_Min_

#undef _SRC_CASTING

#undef sype_oo
#undef SYPE_OO
#undef SOO
#undef NOO

#else

#define NXX BitC_XX_(XX)
#define TXX BitC_TXX_(T,XX)
#define TYPE_XX BitC_Type_(TYPE,XX)
#define type_xx BitC_Type_(type,XX)

#define D() (0)
#define I() (-1)
#define R() (+1)

#define _SRC_BITCRUX

#ifdef _BitC_Data_
#define T D
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#endif

#ifdef _BitC_Inte_
#define T I
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#endif

#ifdef _BitC_Real_
#define T R
#ifdef __OPENCL_VERSION__
#if(_BitC_R16_)
#define XX 16
#include "bitcrux.c"
#undef XX
#endif
#define XX 32
#include "bitcrux.c"
#undef XX
#if(_BitC_R64_)
#define XX 64
#include "bitcrux.c"
#undef XX
#endif
#else
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#endif
#undef T
#endif

#undef _SRC_BITCRUX

#undef R
#undef I
#undef D
#undef type_xx
#undef TYPE_XX
#undef TXX
#undef NXX
#endif
#endif

#else
#ifdef __OPENCL_VERSION__
#error This template cannot be built directly.
#else
static void _BitC_Void_(void) {}
#endif
#endif
