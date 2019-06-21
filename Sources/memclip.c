#include <stdarg.h>
#include "memclip.h"

#if(Fold_(Definition:MemClip Macros))
#define _MEMC_ static
#endif

#if(Fold_(Definition:Internal Constants))
static GENERAL _PL_ MemClip=&MemClip;
static BYTE_08 IdiomVersion[16]="Date:2019.06.21";
static ADDRESS ConstantZero[MemC_Max_Dimension]={0};
#endif

#if(Fold_(Definition:Type Descriptors))
#define _MemC_DT_Parse_(Enum,Size) {.Scope=&MemClip,.Index=(Enum),.Flag=0,.SizeType=(Size),.SizeName=sizeof(IdiomType[Enum]),.Name=IdiomType[Enum],.Link=NULL,.Meta=NULL}

static BYTE_08 IdiomType[MemCTypes][8]={"none_00","byte_08","integer","address"};
static MEMC_DT TableType[MemCTypes]=
{
	_MemC_DT_Parse_(MemCTypeNone_00,0),
	_MemC_DT_Parse_(MemCTypeByte_08,sizeof(byte_08)),
	_MemC_DT_Parse_(MemCTypeInteger,sizeof(integer)),
	_MemC_DT_Parse_(MemCTypeAddress,sizeof(address))
};

_MEMC_ memc_te MemC_DT_Enum_(MEMC_DT _PL_ Desc)
{
	return ((Desc)?((Desc->Scope==MemClip)?((memc_te)(Desc->Index)):(MemCTypeUnknown)):(MemCTypeUnknown));
}
_MEMC_ MEMC_DT *MemC_DT_Desc_(MEMC_TE Enum)
{
	return ((Enum>MemCTypeUnknown)?((Enum<MemCTypes)?(TableType+Enum):(NULL)):(NULL));
}

#undef _MemC_DT_Parse_
#endif

#if(Fold_(Definition:Memory Functions))
#if(Fold_(Part:Memory Set Handle))
static address _MemC_Array_Prod_(ADDRESS *_R_ Ptr,ADDRESS Count)
{
	ADDRESS _PL_ End=Ptr+Count;
	address Length=1;

	for(;Ptr<End;Ptr++)
		Length*=(*Ptr);

	return Length;
}
static integer _MemC_Array_Non_Zero_(ADDRESS *_R_ Ptr,ADDRESS Nums)
{
	for(ADDRESS _PL_ End=Ptr+Nums;Ptr<End;Ptr++)
		if(!(*Ptr))
			return 0;

	return 1;
}
static integer _MemC_Array_All_Zero_(ADDRESS *_R_ Ptr,ADDRESS Nums)
{
	for(ADDRESS _PL_ End=Ptr+Nums;Ptr<End;Ptr++)
		if(*Ptr)
			return 0;

	return 1;
}
_MEMC_ integer MemC_Check_(GENERAL _PL_ _PL_ Memory,ADDRESS Sets)
{
	return ((Memory)?(_MemC_Array_Non_Zero_((ADDRESS*)Memory,Sets)):(0));
}
_MEMC_ general MemC_Deloc_Set_(general **Memory,ADDRESS Sets)
{
	if(Memory)
	{
		GENERAL _PL_ _PL_ End=Memory+Sets;

		for(;Memory<End;Memory++)
			MemC_Deloc_(*Memory);
	}
}
#endif
#if(Fold_(Part:ND Array Memory Allocation))
_MEMC_ address _MemC_Size_Add_(ADDRESS A,ADDRESS B)
{
	volatile ADDRESS Return=A+B;
	
	return ((Return<A)?(0):(Return));
}
_MEMC_ address _MemC_Size_Mul_(ADDRESS A,ADDRESS B)
{
	volatile ADDRESS Return=A*B;

	return (((Return/B)==A)?(Return):(0));
}
static address _MemC_Bigger_(ADDRESS Number,ADDRESS Old)
{
	address New=_MemC_Size_Add_(Old,sizeof(general*));

	if(New)
		New=_MemC_Size_Mul_(Number,New);

	return New;
}
static general **_MemC_Assign_(general **High,ADDRESS NumberHigh,ADDRESS SizeStep)
{
	general **End=High+NumberHigh;
	byte_08 *PtrL=(byte_08*)End;

	for(;High<End;High++,PtrL+=SizeStep)
		(*High)=PtrL;

	return End;
}
static general *_MemC_Assign_Loop_(general **PtrM,ADDRESS _PL_ Size,ADDRESS NumberDimension,ADDRESS SizeElement)
{
	ADDRESS _PL_ End=Size+(NumberDimension-1);
	ADDRESS *_R_ PtrS=Size;
	address Temp=PtrS[0];

	for(PtrS++;PtrS<End;PtrS++)
	{
		PtrM=_MemC_Assign_(PtrM,Temp,(*PtrS)*sizeof(address));
		Temp*=(*PtrS);
	}
	PtrM=_MemC_Assign_(PtrM,Temp,(*PtrS)*SizeElement);

	return PtrM;
}
_MEMC_ general *MemC_Alloc_Byte_(ADDRESS S)
{
	ADDRESS T=sizeof(address);
	ADDRESS N=_MemC_Size_Mul_((S+T-1)/T,T);
	general _PL_ Memory=(N)?(_MemC_Malloc_(N)):(NULL);

	return Memory;
}

static general *_MemC_Alloc_(ADDRESS _PL_ Size,ADDRESS NumberDimension,ADDRESS SizeElement)
{
	general *Memory=NULL;

	if(Size)
		if(NumberDimension)
			if(SizeElement)
			{
				ADDRESS _PL_ End=Size+(NumberDimension-1);
				ADDRESS *PtrS=End;
				address Temporary=_MemC_Size_Mul_(*PtrS,SizeElement);

				for(PtrS--;PtrS>=Size;PtrS--)
					if(Temporary)
						Temporary=_MemC_Bigger_(*PtrS,Temporary);
					else
						break;

				if(Temporary)
				{
					Memory=MemC_Alloc_Byte_(Temporary);
					if(Memory)
						if(NumberDimension>1)
							_MemC_Assign_Loop_(Memory,Size,NumberDimension,SizeElement);
				}
			}

	return Memory;
}
_MEMC_ general *_MemC_Alloc_ND_(ADDRESS TypeSize,ADDRESS Dims,...)
{
	general *Return;

	if(Dims>MemC_Max_Dimension)
		Return=NULL;
	else
	{
		address Buffer[MemC_Max_Dimension];
		va_list Arg;

		va_start(Arg,Dims);

		for(address Dim=0;Dim<Dims;Dim++)
			Buffer[Dim]=va_arg(Arg,address);

		va_end(Arg);

		Return=_MemC_Alloc_(Buffer,Dims,TypeSize);
	}

	return Return;
}
#endif
#if(Fold_(Part:1D Array Trivials))
static address _MemC_Safe_2_(address Num)
{
	Num|=(Num>>1);
	Num|=(Num>>2);
	Num|=(Num>>4);
	Num|=(Num>>8);
	Num|=(Num>>16);
#ifdef MemC_64_
	Num|=(Num>>32);
#endif
	Num++;
	Num>>=1;

	return Num;
}
_MEMC_ errno_t _MemC_Init_1D_(general _PL_ Memory,GENERAL _PL_ Tile,ADDRESS NumberElement,ADDRESS SizeElement)
{
	errno_t ErrorCode;

	if(_MemC_Size_Mul_(NumberElement,SizeElement))
	{
		ADDRESS Safe=_MemC_Safe_2_(NumberElement);
		BYTE_08 _PL_ End=((byte_08*)Memory)+(Safe*SizeElement);
		byte_08 *Ptr=(byte_08*)Memory;
		address Copy=SizeElement;

		ErrorCode=MemC_Copy_Byte_(Tile,Ptr,Copy);
		if(ErrorCode==MemCErrZero)
		{
			for(Ptr+=Copy;Ptr<End;Copy<<=1)
			{
				ErrorCode=MemC_Copy_Byte_(Memory,Ptr,Copy);
				if(ErrorCode==MemCErrZero)
					Ptr+=Copy;
				else
					goto ESCAPE;
			}
			{
				Copy=Safe^NumberElement;
				Copy*=SizeElement;
				ErrorCode=MemC_Copy_Byte_(Memory,Ptr,Copy);
			}
		}
		else
			goto ESCAPE;
	}
	else
		ErrorCode=MemCErrCustom;
ESCAPE:
	return ErrorCode;
}
_MEMC_ errno_t MemC_Copy_Step_(GENERAL _PL_ Source,general _PL_ Target,ADDRESS Nums,ADDRESS StepS,ADDRESS StepT,ADDRESS Copy)
{
	BYTE_08 _PL_ End=(byte_08*)Source+(Nums*StepS);
	BYTE_08 *PtrS;
	byte_08 *PtrT;
	errno_t ErrorCode;

	for(PtrS=Source,PtrT=Target,ErrorCode=MemCErrZero;(ErrorCode==MemCErrZero)&&(PtrS<End);PtrS+=StepS,PtrT+=StepT)
		ErrorCode=MemC_Copy_Byte_(PtrS,PtrT,Copy);

	return ErrorCode;
}
#endif
#if(Fold_(Part:ND Array Data Copy))
static general _MemC_Jump_Offset_(address _PL_ Jump,ADDRESS _PL_ Shape,ADDRESS Dimension,ADDRESS Bytes)
{
	ADDRESS *_R_ PointerS=Shape+(Dimension-2);
	address *_R_ PointerJ=Jump+(Dimension-1);

	PointerJ[0]=Bytes;
	for(PointerJ--;PointerJ>=Jump;PointerS--,PointerJ--)
		PointerJ[0]=PointerS[+1]*PointerJ[+1];
}
static errno_t _MemC_Copy_2D_(BYTE_08 _PL_ MemoryS,byte_08 _PL_ MemoryT,ADDRESS _PL_ JumpS,ADDRESS _PL_ JumpT,ADDRESS _PL_ OriginS,ADDRESS _PL_ OriginT,ADDRESS _PL_ Length,ADDRESS Bytes)
{
	ADDRESS Copy=Length[1]*Bytes;
	BYTE_08 *End=MemoryS+((JumpS[0]*OriginS[0])+(JumpS[1]*OriginS[1]));
	BYTE_08 *PointerS=End;
	byte_08 *PointerT=MemoryT+((JumpT[0]*OriginT[0])+(JumpT[1]*OriginT[1]));
	errno_t ErrorCode;

	for(End+=(JumpS[0]*Length[0]),ErrorCode=MemCErrZero;(ErrorCode==MemCErrZero)&&(PointerS<End);PointerS+=JumpS[0],PointerT+=JumpT[0])
		ErrorCode=MemC_Copy_Byte_(PointerS,PointerT,Copy);

	return ErrorCode;
}
static errno_t _MemC_Copy_Recursive_(BYTE_08 _PL_ MemoryS,byte_08 _PL_ MemoryT,ADDRESS _PL_ JumpS,ADDRESS _PL_ JumpT,ADDRESS _PL_ OriginS,ADDRESS _PL_ OriginT,ADDRESS _PL_ Length,ADDRESS Dimensions,ADDRESS Bytes)
{
	errno_t ErrorCode;

	if(Dimensions>2)
	{
		ADDRESS NextDimensions=Dimensions-1;
		ADDRESS _PL_ NextJumpS=JumpS+1;
		ADDRESS _PL_ NextJumpT=JumpT+1;
		ADDRESS _PL_ NextOriginS=OriginS+1;
		ADDRESS _PL_ NextOriginT=OriginT+1;
		ADDRESS _PL_ NextLength=Length+1;
		BYTE_08 *End=MemoryS+(JumpS[0]*OriginS[0]);
		BYTE_08 *PointerS=End;
		byte_08 *PointerT=MemoryT+(JumpT[0]*OriginT[0]);

		for(End+=(JumpS[0]*Length[0]),ErrorCode=MemCErrZero;(ErrorCode==MemCErrZero)&&(PointerS<End);PointerS+=JumpS[0],PointerT+=JumpT[0])
			ErrorCode=_MemC_Copy_Recursive_(PointerS,PointerT,NextJumpS,NextJumpT,NextOriginS,NextOriginT,NextLength,NextDimensions,Bytes);
	}
	else
		ErrorCode=_MemC_Copy_2D_(MemoryS,MemoryT,JumpS,JumpT,OriginS,OriginT,Length,Bytes);

	return ErrorCode;
}
static integer _MemC_Copy_Check_Bound_(ADDRESS _PL_ Shape,ADDRESS _PL_ Offset,ADDRESS _PL_ Length,ADDRESS Dimensions)
{
	address Index;
	address Temp;

	for(Index=0;Index<Dimensions;Index++)
	{
		Temp=Offset[Index]+Length[Index];
		if(Temp<Offset[Index])
			break;
		if(Temp>Shape[Index])
			break;
	}

	return (Index==Dimensions);
}
_MEMC_ errno_t _MemC_Copy_(GENERAL _PL_ MemoryS,general _PL_ MemoryT,ADDRESS _PL_ OriginS,ADDRESS _PL_ OriginT,ADDRESS _PL_ Length,ADDRESS _PL_ ShapeS,ADDRESS _PL_ ShapeT,ADDRESS Dimensions,ADDRESS Bytes)
{
	ADDRESS _PL_ OffsetS=(OriginS)?(OriginS):(ConstantZero);
	ADDRESS _PL_ OffsetT=(OriginT)?(OriginT):(ConstantZero);
	errno_t ErrorCode;

	if(_MemC_Copy_Check_Bound_(ShapeS,OffsetS,Length,Dimensions)&&_MemC_Copy_Check_Bound_(ShapeT,OffsetT,Length,Dimensions))
		switch(Dimensions)
		{
		case 0:
			ErrorCode=MemCErrZero;
			break;
		case 1:
			{
				ADDRESS Copy=Length[0]*Bytes;
				
				if(Copy)
					ErrorCode=MemC_Copy_Byte_(((BYTE_08*)MemoryS)+(OffsetS[0]*Bytes),((byte_08*)MemoryT)+(OffsetT[0]*Bytes),Copy);
				else
					ErrorCode=MemCErrZero;
			}
			break;
		default:
			if(Bytes)
				if(_MemC_Array_Non_Zero_(Length,Dimensions))
					if(Dimensions>MemC_Max_Dimension)
						ErrorCode=MemCErrCustom;
					else
					{
						address JumpS[MemC_Max_Dimension];
						address JumpT[MemC_Max_Dimension];

						if(ShapeS)
							_MemC_Jump_Offset_(JumpS,ShapeS,Dimensions,Bytes);
						else
							_MemC_Jump_Offset_(JumpS,Length,Dimensions,Bytes);
						if(ShapeT)
							_MemC_Jump_Offset_(JumpT,ShapeT,Dimensions,Bytes);
						else
							_MemC_Jump_Offset_(JumpT,Length,Dimensions,Bytes);

						ErrorCode=_MemC_Copy_Recursive_(MemoryS,MemoryT,JumpS,JumpT,OffsetS,OffsetT,Length,Dimensions,Bytes);
					}
				else
					ErrorCode=MemCErrZero;
			else
				ErrorCode=MemCErrZero;
		}
	else
		ErrorCode=MemCErrCustom;

	return ErrorCode;
}
#endif
#if(Fold_(Part:ND Array Data Reformation))
static integer _MemC_Reform_Valid_(ADDRESS *_R_ Map,ADDRESS Dims)
{
	address Table[MemC_Max_Dimension]={0};
	ADDRESS _PL_ End=Map+Dims;

	while(Map<End)
		if((*Map)<Dims)
		{
			Table[*Map]=(address)FULL;
			Map++;
		}
		else
			break;

	return ((Map==End)?(_MemC_Array_Non_Zero_(Table,Dims)):(0));
}
static general _MemC_Reform_Short_(ADDRESS _PL_ Shape,ADDRESS _PL_ Map,address _PL_ Dims,address _PL_ Bytes)
{
	for(address Temp=(*Dims)-1;Temp;Temp--)
		if(Map[Temp]==Temp)
		{
			(*Bytes)*=Shape[Temp];
			(*Dims)=Temp;
		}
		else
			break;
}
static general _MemC_Reform_Merge_(address _PL_ Shape,address _PL_ Map,address _PL_ Dims)
{
	ADDRESS *End=Map+(*Dims);
	ADDRESS *Last=End-1;
	address *MapA;
	address *MapB;
	address *MapC;
	address *ShpA;
	address *ShpB;
	address *ShpC;
	address Pull;

	for(MapA=Map,ShpA=Shape;MapA<Last;MapA++,ShpA++)
	{
		for(MapB=MapA,ShpB=ShpA;MapB<Last;MapB++,ShpB++)
			if((MapB[0]+1)==MapB[1])
				ShpA[0]*=ShpB[1];
			else
				break;

		if(MapA<MapB)
		{
			for(MapC=Map,Pull=MapB-MapA;MapC<MapA;MapC++)
				if(MapC[0]>MapA[0])
					MapC[0]-=Pull;

			for(MapB++,MapC++,ShpB++,ShpC=ShpA+1;MapB<End;MapB++,MapC++,ShpB++,ShpC++)
			{
				MapC[0]=(MapA[0]<MapB[0])?(MapB[0]-Pull):(MapB[0]);
				ShpC[0]=ShpB[0];
			}

			End=MapC;
			Last=End-1;
			*Dims=End-Map;
		}
	}
}
static errno_t _MemC_Reform_Order_(BYTE_08 _PL_ Source,byte_08 _PL_ Target,ADDRESS _PL_ Shape,ADDRESS _PL_ Map,ADDRESS Total,ADDRESS Dims,ADDRESS Bytes)
{
	address Jump[MemC_Max_Dimension];
	ADDRESS Last=Dims-1;
	address Prod;
	address IdxS;
	address IdxT;
	address IdxJ;
	errno_t ErrorCode;

	for(IdxT=0,ErrorCode=MemCErrZero;(ErrorCode==MemCErrZero)&&(IdxT<Total);IdxT++)
	{
		for(IdxJ=Last,Prod=IdxT/Shape[Map[Last]],Jump[Map[Last]]=IdxT%Shape[Map[Last]];IdxJ;Prod/=Shape[Map[IdxJ]])
		{
			IdxJ--;
			Jump[Map[IdxJ]]=Prod%Shape[Map[IdxJ]];
		}
		for(IdxJ=Last,IdxS=Jump[Last],Prod=Shape[Last];IdxJ;Prod*=Shape[IdxJ])
		{
			IdxJ--;
			IdxS+=Prod*Jump[IdxJ];
		}
		ErrorCode=MemC_Copy_Byte_(Source+(IdxS*Bytes),Target+(IdxT*Bytes),Bytes);
	}

	return ErrorCode;
}
_MEMC_ errno_t _MemC_Reform_(GENERAL _PL_ MemoryS,general _PL_ MemoryT,ADDRESS _PL_ ShapeS,ADDRESS _PL_ AxisStoT,address Dimensions,address Bytes)
{
	errno_t ErrorCode;

	if(Dimensions)
	{
		_MemC_Reform_Short_(ShapeS,AxisStoT,&Dimensions,&Bytes);
		if(Dimensions>1)
			if(Dimensions<MemC_Max_Dimension)
				if(_MemC_Reform_Valid_(AxisStoT,Dimensions))
				{
					ADDRESS Total=_MemC_Array_Prod_(ShapeS,Dimensions);

					if(Total)
					{
						address ShapeSNew[MemC_Max_Dimension];
						address MapTNew[MemC_Max_Dimension];

						ErrorCode=MemC_Copy_1D_(ShapeS,ShapeSNew,Dimensions);
						if(ErrorCode!=MemCErrZero)
							goto ESCAPE;

						ErrorCode=MemC_Copy_1D_(AxisStoT,MapTNew,Dimensions);
						if(ErrorCode!=MemCErrZero)
							goto ESCAPE;

						_MemC_Reform_Merge_(ShapeSNew,MapTNew,&Dimensions);
						ErrorCode=_MemC_Reform_Order_(MemoryS,MemoryT,ShapeSNew,MapTNew,Total,Dimensions,Bytes);
					}
					else
						goto NO_OPERATION;
				}
				else
					goto INVALID;
			else
				goto INVALID;
		else
			if(AxisStoT[0])
			{
INVALID:
				ErrorCode=MemCErrCustom;
			}
			else
			{
				ADDRESS Copy=ShapeS[0]*Bytes;

				if(Copy)
					ErrorCode=MemC_Copy_Byte_(MemoryS,MemoryT,Copy);
				else
					goto NO_OPERATION;
			}
	}
	else
	{
NO_OPERATION:
		ErrorCode=MemCErrZero;
	}
ESCAPE:
	return ErrorCode;
}

_MEMC_ integer MemC_Reform_Shape_(ADDRESS _PL_ ShapeS,ADDRESS _PL_ AxisStoT,address _PL_ ShapeT,ADDRESS Dimensions)
{
	if(Dimensions)
		if(Dimensions<MemC_Max_Dimension)
			if(_MemC_Reform_Valid_(AxisStoT,Dimensions))
			{
				for(address Index=0;Index<Dimensions;Index++)
					ShapeT[AxisStoT[Index]]=ShapeS[Index];

				goto SUCCESS;
			}
			else
				goto FAILURE;
		else
			goto FAILURE;
	else
		goto SUCCESS;
FAILURE:
	return 0;
SUCCESS:
	return 1;
}
#endif
#if(Fold_(Part:Object Sorting))
static address _MemC_Sort_Lng_2_(ADDRESS Length)
{
	address Temp=1;

	Temp=~Temp;
	Temp&=Length;

	return Temp;
}
static general _MemC_Sort_Bound_(address _PL_ Jump,GENERAL _PL_ **Bound)
{
	Bound[2]=Bound[1]+Jump[0];
	if(Bound[2]>Bound[3])
		Bound[2]=Bound[3];

	Jump[1]=Bound[2]-Bound[1];
	Jump[2]=Jump[0]+Jump[1];
	Jump[3]=Jump[1]-1;
}
static general _MemC_Sort_Ord_2_(integer(_PL_ Comp_)(GENERAL _PL_,GENERAL _PL_),GENERAL **Ptr,address *Idx,ADDRESS Length)
{
	GENERAL _PL_ _PL_ End=Ptr+_MemC_Sort_Lng_2_(Length);
	GENERAL *Temp;

	if(Idx)
		for(;Ptr<End;Ptr+=2,Idx+=2)
		{
			if(Comp_(Ptr[0],Ptr[1]))
			{
				Temp=Ptr[0];
				Ptr[0]=Ptr[1];
				Ptr[1]=Temp;

				Temp=(general*)(Idx[0]);
				Idx[0]=Idx[1];
				Idx[1]=(address)Temp;
			}
		}
	else
		for(;Ptr<End;Ptr+=2)
			if(Comp_(Ptr[0],Ptr[1]))
			{
				Temp=Ptr[0];
				Ptr[0]=Ptr[1];
				Ptr[1]=Temp;
			}
}
static general _MemC_Sort_Ord_A_(integer(_PL_ Comp_)(GENERAL _PL_,GENERAL _PL_),address *PtrT,GENERAL _PL_ *PtrA,GENERAL _PL_ _PL_ StartB,GENERAL _PL_ _PL_ EndB)
{
	GENERAL _PL_ *PtrB=StartB;

	for(PtrT[0]=0;PtrB<EndB;PtrB++)
		if(Comp_(PtrA[0],PtrB[0]))
			PtrT[0]++;
		else
		{
			for(PtrA++,PtrT++;PtrA<StartB;PtrA++,PtrT++)
				if(Comp_(PtrA[0],PtrB[0]))
				{
					PtrT[0]=PtrT[-1]+1;
					break;
				}
				else
					PtrT[0]=PtrT[-1];

			if(PtrA==StartB)
				break;
		}
	for(PtrA++,PtrT++;PtrA<StartB;PtrA++,PtrT++)
		PtrT[0]=PtrT[-1];
}
static general _MemC_Sort_Ord_B_(integer(_PL_ Comp_)(GENERAL _PL_,GENERAL _PL_),address *PtrT,GENERAL _PL_ *PtrB,GENERAL _PL_ _PL_ StartA,GENERAL _PL_ _PL_ StartB)
{
	GENERAL _PL_ *PtrA=StartB-1;

	for(PtrT[0]=0;PtrA>=StartA;PtrA--)
		if(Comp_(PtrA[0],PtrB[0]))
			PtrT[0]--;
		else
		{
			for(PtrB--,PtrT--;PtrB>=StartB;PtrB--,PtrT--)
				if(Comp_(PtrA[0],PtrB[0]))
				{
					PtrT[0]=PtrT[+1]-1;
					break;
				}
				else
					PtrT[0]=PtrT[+1];

			if(PtrB<StartB)
				break;
		}
	for(PtrB--,PtrT--;PtrB>=StartB;PtrB--,PtrT--)
		PtrT[0]=PtrT[+1];
}
static errno_t _MemC_Sort_Table_(address *IdxO,address *IdxA,ADDRESS *PtrT,ADDRESS _PL_ MatchB,ADDRESS Copy,ADDRESS Step)
{
	errno_t Error=MemC_Copy_1D_(IdxO,IdxA,Copy);

	if(Error==MemCErrZero)
	{
		for(;IdxO<MatchB;IdxA++,IdxO++,PtrT++)
			IdxO[PtrT[0]]=IdxA[0];
		for(IdxA+=Step,IdxO+=Step,PtrT+=Step;IdxO>=MatchB;IdxA--,IdxO--,PtrT--)
			IdxO[PtrT[0]]=IdxA[0];
	}

	return Error;
}
_MEMC_ errno_t MemC_Sort_(MemC_Func_Declare_C_(integer,Comp_,GENERAL _PL_,GENERAL _PL_),GENERAL *_PL_ Refer,address _PL_ Index,address _PL_ Buffer,ADDRESS Length)
{
	errno_t ErrorCode=MemCErrZero;

	if(Length)
	{
		GENERAL _PL_ *Bound[4];
		address Jump[4];
		address _PL_ Table=Buffer;
		address _PL_ Value=Table+Length;

		_MemC_Sort_Ord_2_(Comp_,Refer,Index,Length);
		if(Index)
		{
			address *Match;

			for(Jump[0]=2,Bound[3]=Refer+Length;Jump[0]<Length;Jump[0]<<=1)
				for(Bound[0]=Refer,Bound[1]=Refer+Jump[0],Match=Index;Bound[1]<Bound[3];Bound[0]=Bound[2],Bound[1]=Bound[2]+Jump[1],Match+=Jump[2])
				{
					_MemC_Sort_Bound_(Jump,Bound);
					_MemC_Sort_Ord_A_(Comp_,Table,Bound[0],Bound[1],Bound[2]);
					_MemC_Sort_Ord_B_(Comp_,Table+(Jump[2]-1),Bound[2]-1,Bound[0],Bound[1]);

					ErrorCode=_MemC_Sort_Table_((address*)(Bound[0]),Value,Table,(address*)(Bound[1]),Jump[2],Jump[3]);
					if(ErrorCode)
						goto ESCAPE;

					ErrorCode=_MemC_Sort_Table_(Match,Value,Table,Match+Jump[0],Jump[2],Jump[3]);
					if(ErrorCode)
						goto ESCAPE;
				}
		}
		else
			for(Jump[0]=2,Bound[3]=Refer+Length;Jump[0]<Length;Jump[0]<<=1)
				for(Bound[0]=Refer,Bound[1]=Refer+Jump[0];Bound[1]<Bound[3];Bound[0]=Bound[2],Bound[1]=Bound[2]+Jump[1])
				{
					_MemC_Sort_Bound_(Jump,Bound);
					_MemC_Sort_Ord_A_(Comp_,Table,Bound[0],Bound[1],Bound[2]);
					_MemC_Sort_Ord_B_(Comp_,Table+(Jump[2]-1),Bound[2]-1,Bound[0],Bound[1]);

					ErrorCode=_MemC_Sort_Table_((address*)(Bound[0]),Value,Table,(address*)(Bound[1]),Jump[2],Jump[3]);
					if(ErrorCode!=MemCErrZero)
						goto ESCAPE;
				}
	}
ESCAPE:
	return ErrorCode;
}
#endif
#if(Fold_(Part:Others))
_MEMC_ general MemC_Void_(general)
{
}
_MEMC_ general MemC_Self_(address *_R_ Table,ADDRESS Length,INTEGER Mode)
{
	if(Mode)
	{
		ADDRESS _PL_ End=Table+Length;

		for(;Table<End;Table++)
			(*Table)=(address)Table;
	}
	else
	{
		address Idx;

		for(Idx=0;Idx<Length;Idx++)
			Table[Idx]=Idx;
	}
}
_MEMC_ address _MemC_Assign_1D_(general _PL_ Indexer,GENERAL _PL_ Indexed,ADDRESS Interval,ADDRESS Indices,ADDRESS TypeSize,INTEGER Mode)
{
	address Sum;

	if(Indices)
	{
		BYTE_08 _PL_ _PL_ End=(byte_08**)Indexer+Indices;
		byte_08 **_R_ PointerO=Indexer;

		{
			PointerO[0]=(byte_08*)Indexed;
			PointerO++;
		}
		if(Mode)
		{
			ADDRESS *_R_ PointerS=(address*)Interval;

			for(;PointerO<End;PointerO++,PointerS++)
				PointerO[0]=PointerO[-1]+(PointerS[0]*TypeSize);

			Sum=(PointerO[-1]-(byte_08*)Indexed)+(PointerS[0]*TypeSize);
		}
		else
		{
			ADDRESS Step=Interval*TypeSize;

			for(;PointerO<End;PointerO++)
				PointerO[0]=PointerO[-1]+Step;

			Sum=Step*Indices;
		}
	}
	else
		Sum=0;

	return Sum;
}
#endif
#endif

#if(Fold_(Definition:MemClip Structure Functions))
#if(Fold_(Part:MemC_MS))
_MEMC_ memc_ms *MemC_MS_Create_(GENERAL _PL_ ID,ADDRESS Slots)
{
	memc_ms *MS;

	if(Slots)
	{
		address Size=_MemC_Size_Mul_(Slots,sizeof(general*));

		if(Size)
		{
			Size=_MemC_Size_Add_(Size,sizeof(memc_ms));
			if(Size)
			{
				MS=MemC_Alloc_Byte_(Size);
				if(MS)
				{
					Acs_(GENERAL*,MS->ID)=ID;
					Acs_(MEMC_DT*,MS->Type)=MemC.Type.Add;
					Acs_(address,MS->Nums)=Slots;
					Acs_(address*,MS->Slot.V)=MemC_Clear_1D_((address*)(MS+1),Slots);
				}
			}
			else
				MS=NULL;
		}
		else
			MS=NULL;
	}
	else
	{
		MS=MemC_Alloc_Unit_(memc_ms);
		if(MS)
		{
			Acs_(GENERAL*,MS->ID)=ID;
			Acs_(MEMC_DT*,MS->Type)=MemC.Type.Add;
			Acs_(address,MS->Nums)=0;
			Acs_(address*,MS->Slot.V)=NULL;
		}
	}

	return MS;
}
_MEMC_ general MemC_MS_Delete_(memc_ms *_PL_ MS)
{
	MemC_Deloc_(*MS);
}

_MEMC_ address MemC_MS_Size_(MEMC_MS _PL_ MS)
{
	return (MS)?(sizeof(memc_ms)+MemC_Size_(address,MS->Nums)):(0);
}
_MEMC_ integer MemC_MS_Change_(MEMC_MS _PL_ MS,MEMC_DT _PL_ DT)
{
	if(MS)
		if(DT)
			if(DT->SizeType==sizeof(address))
			{
				Acs_(MEMC_DT*,MS->Type)=DT;
				goto SUCCESS;
			}
			else
				goto FAILURE;
		else
			goto FAILURE;
	else
		goto FAILURE;
FAILURE:
	return 0;
SUCCESS:
	return 1;
}

_MEMC_ integer MemC_MS_Init_(MEMC_MS _PL_ MS)
{
	if(MS)
	{
		if(MS->Nums)
			MemC_Clear_1D_(MS->Slot.V,MS->Nums);
		goto SUCCESS;
	}
	else
		goto FAILURE;
FAILURE:
	return 0;
SUCCESS:
	return 1;
}
_MEMC_ integer MemC_MS_Null_(MEMC_MS _PL_ MS,INTEGER Mode)
{
	if(MS)
		if(MS->Slot.V)
			if(MS->Slot.V[0]<MS->Nums)
				if(Mode)
					if(_MemC_Array_Non_Zero_(MS->Slot.V+1,MS->Slot.V[0]))
						goto SUCCESS;
					else
						goto FAILURE;
				else
					if(_MemC_Array_All_Zero_(MS->Slot.V+1,MS->Slot.V[0]))
						goto SUCCESS;
					else
						goto FAILURE;
			else
				goto FAILURE;
		else
			goto FAILURE;
	else
		goto FAILURE;
FAILURE:
	return 0;
SUCCESS:
	return 1;
}

_MEMC_ integer MemC_MS_Dims_(MEMC_MS _PL_ MS,ADDRESS Dims,...)
{
	if(MS)
		if(MS->Nums>Dims)
		{
			va_list Arg;

			va_start(Arg,Dims);

			MemC_Temp_(address,Dim=0)
				for(MS->Slot.V[Dim++]=Dims;Dim<=Dims;Dim++)
					MS->Slot.V[Dim]=va_arg(Arg,address);

			va_end(Arg);
		}
		else goto FAILURE;
	else goto FAILURE;

	return 1;
FAILURE:
	return 0;
}

_MEMC_ integer MemC_MS_Joke_(MEMC_MS _PL_ MS)
{
	if(MS)
	{
		if(MS->Nums)
		{
			address Table[8]={1,2,3,4,5,6,7,8};
			address Temp[2];
			address *Mover=Table-7;
			general **Pointer=MS->Slot.P;
			address Count=MS->Nums;

			for(Count--,Temp[0]=(address)Pointer/sizeof(address);Count>7;Count--,Pointer=(*Pointer))
			{
				{
					Temp[1]=Temp[0]>>1;
					Temp[0]*=3;
					Temp[0]++;
					Temp[0]=Temp[Temp[0]&1];

					Temp[1]=Temp[0]&7;
					(*Pointer)=MS->Slot.P+Table[Temp[1]];
				}
				switch(Temp[1])
				{
				case 0:
					Table[0]=Table[1];
				case 1:
					Table[1]=Table[2];
				case 2:
					Table[2]=Table[3];
				case 3:
					Table[3]=Table[4];
				case 4:
					Table[4]=Table[5];
				case 5:
					Table[5]=Table[6];
				case 6:
					Table[6]=Table[7];
				default:
					Table[7]++;
				}
			}
			for(Mover+=Count;Count;Count--,Pointer=(*Pointer))
			{
				{
					Temp[1]=Temp[0]>>1;
					Temp[0]*=3;
					Temp[0]++;
					Temp[0]=Temp[Temp[0]&1];

					Temp[1]=Temp[0]%Count;
					(*Pointer)=MS->Slot.P+Table[Temp[1]];

					Temp[1]+=7;
					Temp[1]-=Count;
				}
				switch(Temp[1])
				{
				case 0:
					Mover[0]=Mover[1];
				case 1:
					Mover[1]=Mover[2];
				case 2:
					Mover[2]=Mover[3];
				case 3:
					Mover[3]=Mover[4];
				case 4:
					Mover[4]=Mover[5];
				case 5:
					Mover[5]=Mover[6];
				default:
					Mover--;
				}
			}
			(*Pointer)=MS->Slot.P;
		}
	}
	else goto FAILURE;

	return 1;
FAILURE:
	return 0;
}
_MEMC_ integer MemC_MS_Oops_(MEMC_MS _PL_ MS)
{
	if(MS)
		if(MS->Nums)
		{
			GENERAL _PL_ Start=MS->Slot.P;
			GENERAL _PL_ End=MS->Slot.P+MS->Nums;
			GENERAL _PL_ *Pointer=MS->Slot.P;
			address Count=MS->Nums;

			while(Count--)
				if((*Pointer)<Start)
					goto FAILURE;
				else
					if((*Pointer)<End)
						if((*Pointer)==Start)
							if(Count)
								goto FAILURE;
							else goto SUCCESS;
						else
							Pointer=(*Pointer);
					else goto FAILURE;
			goto FAILURE;
		}
		else
			goto SUCCESS;
	else
		goto FAILURE;
FAILURE:
	return 0;
SUCCESS:
	return 1;
}
#endif
#if(Fold_(Part:MemC_MC))
static address _MemC_Shape_Overflow_(ADDRESS _PL_ Shape,ADDRESS Dims)
{
	ADDRESS _PL_ End=Shape+Dims;
	ADDRESS *_R_ Ptr=Shape;
	address Total=1;

	for(;Ptr<End;Ptr++)
		Total=_MemC_Size_Mul_(Total,*Ptr);

	return Total;
}
static address _MemC_Space_Required_(ADDRESS _PL_ Shape,ADDRESS Dims,ADDRESS SizeType)
{
	address Size[2];

	if(Dims>1)
	{
		ADDRESS _PL_ Last=Shape+(Dims-1);
		ADDRESS *_R_ Ptr=Shape;

		for(Size[0]=1,Size[1]=0;Ptr<Last;Ptr++)
		{
			Size[0]=_MemC_Size_Mul_(Size[0],*Ptr);
			Size[1]=_MemC_Size_Add_(Size[0],Size[1]);
			if(!(Size[1]))
				break;
		}
		if(Ptr==Last)
		{
			Size[0]=_MemC_Size_Mul_(Size[0],*Ptr);
			Size[0]=_MemC_Size_Mul_(Size[0],SizeType);
			if(Size[0])
			{
				Size[1]=_MemC_Size_Mul_(Size[1],sizeof(address));
				if(Size[1])
					Size[1]=_MemC_Size_Add_(Size[0],Size[1]);
				else
					Size[1]=0;
			}
			else
				Size[1]=0;
		}
		else
			Size[1]=0;
	}
	else
		Size[1]=_MemC_Size_Mul_(Shape[0],SizeType);

	return Size[1];
}
_MEMC_ memc_mc *MemC_MC_Create_(GENERAL _PL_ ID,MEMC_MS _PL_ MS,MEMC_DT _PL_ DT)
{
	memc_mc *MC;
	
	if(DT)
		if(MS)
			if(MS->Slot.V)
				if(MS->Slot.V[0]<MS->Nums)
					if(MS->Slot.V[0])
					{
						ADDRESS Dimensions=MS->Slot.V[0];
						ADDRESS _PL_ Shape=MS->Slot.V+1;
						address Lng1D;
						integer Flag=(DT->SizeType)?(0x1):(0x0);

						if(_MemC_Array_Non_Zero_(Shape,Dimensions))
						{
							Lng1D=_MemC_Shape_Overflow_(Shape,Dimensions);
							if(Lng1D)
								Flag|=0x6;
							else
								Flag|=0x2;
						}
						else
							Lng1D=0;

						switch(Flag)
						{
						case 0x0:
						case 0x1:
						case 0x6:
							if(Dimensions>1)
							{
								address Size=_MemC_Size_Mul_(Dimensions,sizeof(address));

								if(Size)
								{
									Size=_MemC_Size_Add_(Size,sizeof(memc_mc));
									MC=MemC_Alloc_Byte_(Size);
								}
								else
									goto ESCAPE;
							}
							else
								MC=MemC_Alloc_Unit_(memc_mc);

							if(MC)
							{
								Acs_(GENERAL*,MC->ID)=ID;
								Acs_(MEMC_DT*,MC->Type)=DT;
								Acs_(address,MC->Dims)=Dimensions;
								Acs_(address,MC->Unit)=DT->SizeType;
								Acs_(address,MC->Lng1D)=Lng1D;
								Acs_(general*,MC->AcsND)=NULL;
								Acs_(general*,MC->Acs1D)=NULL;
								if(Dimensions>1)
								{
									Acs_(address*,MC->LngND)=(address*)(MC+1);
									if(MemC_Copy_1D_(Shape,(address*)(MC->LngND),Dimensions)!=MemCErrZero)
										MemC_Deloc_(MC);
								}
								else
									Acs_(ADDRESS*,MC->LngND)=&(MC->Lng1D);
							}
							break;
						case 0x7:
							{
								address Size[2];

								if(Dimensions>1)
								{
									Size[0]=_MemC_Size_Mul_(Dimensions,sizeof(address));
									if(Size[0])
										Size[0]=_MemC_Size_Add_(Size[0],sizeof(memc_mc));
									else
										goto ESCAPE;
									if(Size[0])
										goto INVADE;
									else
										goto ESCAPE;
								}
								else
								{
									Size[0]=sizeof(memc_mc);
INVADE:
									Size[1]=_MemC_Space_Required_(Shape,Dimensions,DT->SizeType);
								}
								if(Size[1])
									Size[0]=_MemC_Size_Add_(Size[0],Size[1]);
								else
									goto ESCAPE;

								MC=MemC_Alloc_Byte_(Size[0]);
							}
							if(MC)
							{
								Acs_(GENERAL*,MC->ID)=ID;
								Acs_(MEMC_DT*,MC->Type)=DT;
								Acs_(address,MC->Dims)=Dimensions;
								Acs_(address,MC->Unit)=DT->SizeType;
								Acs_(address,MC->Lng1D)=Lng1D;
								if(Dimensions>1)
								{
									Acs_(address*,MC->LngND)=(address*)(MC+1);
									Acs_(general*,MC->AcsND)=(general*)(MC->LngND+Dimensions);
									Acs_(general*,MC->Acs1D)=_MemC_Assign_Loop_((general**)(MC->AcsND),Shape,Dimensions,DT->SizeType);
									if(MemC_Copy_1D_(Shape,(address*)(MC->LngND),Dimensions)!=MemCErrZero)
										MemC_Deloc_(MC);
								}
								else
								{
									Acs_(ADDRESS*,MC->LngND)=&(MC->Lng1D);
									Acs_(general*,MC->AcsND)=(general*)(MC+1);
									Acs_(general*,MC->Acs1D)=(general*)(MC->AcsND);
								}
							}
							break;
						default:
							goto ESCAPE;
						}
					}
					else
					{
						MC=MemC_Alloc_Unit_(memc_mc);
						if(MC)
						{
							Acs_(GENERAL*,MC->ID)=ID;
							Acs_(MEMC_DT*,MC->Type)=DT;
							Acs_(address,MC->Dims)=0;
							Acs_(address,MC->Unit)=DT->SizeType;
							Acs_(address*,MC->LngND)=NULL;
							Acs_(address,MC->Lng1D)=0;
							Acs_(general*,MC->AcsND)=NULL;
							Acs_(general*,MC->Acs1D)=NULL;
						}
					}
				else
					goto ESCAPE;
			else
				goto ESCAPE;
		else
			goto ESCAPE;
	else
	{
ESCAPE:
		MC=NULL;
	}

	return MC;
}
_MEMC_ general MemC_MC_Delete_(memc_mc *_PL_ MC)
{
	MemC_Deloc_(*MC);
}

static address _MemC_Space_Occupied_(ADDRESS _PL_ Shape,ADDRESS Dims,ADDRESS SizeType)
{
	ADDRESS _PL_ Last=Shape+(Dims-1);
	ADDRESS *_R_ Ptr=Shape;
	address Size[2]={1,0};

	for(;Ptr<Last;Ptr++)
	{
		Size[0]*=*Ptr;
		Size[1]+=Size[0];
	}
	{
		Size[0]*=*Ptr;
		Size[0]*=SizeType;
		Size[1]*=sizeof(address);
		Size[1]+=Size[0];
	}

	return Size[1];
}
_MEMC_ address MemC_MC_Size_(MEMC_MC _PL_ MC)
{
	return (MC)?(sizeof(memc_mc)+((MC->Dims>1)?(MemC_Size_(address,MC->Dims)):(0))+((MC->Acs1D)?(_MemC_Space_Occupied_(MC->LngND,MC->Dims,MC->Unit)):(0))):(0);
}
_MEMC_ integer MemC_MC_Form_(MEMC_MC _PL_ MC,MEMC_MS _PL_ MS)
{
	if(MC)
		if(MS)
			if(MC->Dims<MS->Nums)
			{
				MS->Slot.V[0]=MC->Dims;
				if(MC->Dims)
					if(MemC_Copy_1D_(MC->LngND,MS->Slot.V+1,MC->Dims)==MemCErrZero)
						goto SUCCESS;
					else
						goto FAILURE;
				else
					goto SUCCESS;
			}
			else
				goto FAILURE;
		else
			goto FAILURE;
	else
		goto FAILURE;
FAILURE:
	return 0;
SUCCESS:
	return 1;
}
_MEMC_ integer MemC_MC_Change_(MEMC_MC _PL_ MC,MEMC_DT _PL_ DT)
{
	if(MC)
		if(DT)
			if(DT->SizeType==MC->Unit)
			{
				Acs_(MEMC_DT*,MC->Type)=DT;
				goto SUCCESS;
			}
			else
				goto FAILURE;
		else
			goto FAILURE;
	else
		goto FAILURE;
FAILURE:
	return 0;
SUCCESS:
	return 1;
}
#endif
#if(Fold_(Part:MemC_ML))
#define _MemC_ML_Malloc_(Chunks) ((_MemC_Size_Mul_(Chunks,sizeof(memc_mn)))?(malloc(MemC_Size_(memc_mn,Chunks))):(NULL))
#define _MemC_ML_Free_(Memory) __dl{free(Memory);(Memory)=NULL;}lb__

struct _memc_l2 { general *L[2]; };
MemC_Type_Declare_(struct,memc_l2,MEMC_L2);

MemC_Type_Declare_(struct,memc_mn,MEMC_MN);
struct _memc_mn
{
	memc_ml *Home;
	memc_mn *Prev;
	memc_mn *Next;
	address Size;
};

_MEMC_ memc_ml *MemC_ML_Create_(memc_ml _PL_ Root,ADDRESS Chunks)
{
	memc_ml *ML;

	if(Chunks>2)
		if(Root)
			if(Root==Root->LinkSelf)
			{
				ML=_MemC_ML_Malloc_(Chunks);
				if(ML)
				{
					Acs_(memc_ml*,ML->LinkSelf)=ML;
					Acs_(memc_ml*,ML->LinkPrev)=Root;
					Acs_(MEMC_ML*,ML->LinkNext)=Root->LinkNext;

					Acs_(memc_ml*,Root->LinkNext->LinkPrev)=ML;
					Acs_(memc_ml*,Root->LinkNext)=ML;

					goto JUMP;
				}
			}
			else
				ML=NULL;
		else
		{
			ML=_MemC_ML_Malloc_(Chunks);
			if(ML)
			{
				{
					Acs_(memc_ml*,ML->LinkSelf)=ML;
					Acs_(memc_ml*,ML->LinkPrev)=ML;
					Acs_(memc_ml*,ML->LinkNext)=ML;
				}
JUMP:
				MemC_Temp_(memc_mn,_PL_ MN=(memc_mn*)(ML+1))
				{
					MN->Home=NULL;
					MN->Prev=NULL;
					MN->Next=NULL;
					MN->Size=MemC_Size_(memc_mn,Chunks-3);

					Acs_(address,ML->SizeAble)=MN->Size;
					Acs_(address,ML->SizeIdle)=MN->Size;
					Acs_(address,ML->SizeUsed)=0;
					Acs_(address,ML->NumsIdle)=1;
					Acs_(address,ML->NumsUsed)=0;
				}
			}
		}
	else
		ML=NULL;

	return ML;
}
_MEMC_ memc_ml *MemC_ML_Delete_(memc_ml *_PL_ ML)
{
	memc_ml *Return;

	if(*ML)
		if((*ML)==(*ML)->LinkSelf)
		{
			if((*ML)==(*ML)->LinkPrev)
				Return=NULL;
			else
			{
				Return=(*ML)->LinkPrev;

				Acs_(memc_ml*,(*ML)->LinkPrev->LinkNext)=(*ML)->LinkNext;
				Acs_(memc_ml*,(*ML)->LinkNext->LinkPrev)=(*ML)->LinkPrev;
			}
			_MemC_ML_Free_(*ML);
		}
		else
			Return=NULL;
	else
		Return=NULL;

	return Return;
}
_MEMC_ address MemC_ML_Size_(MEMC_ML _PL_ ML)
{
	return ((ML)?(MemC_Size_(memc_ml,1)+MemC_Size_(memc_mn,ML->NumsIdle+ML->NumsUsed)+(ML->SizeIdle+ML->SizeUsed)):(0));
}

static address _MemC_MN_Margin_(address Size)
{
	Size+=sizeof(memc_mn);
	Size--;
	Size/=sizeof(memc_mn);
	Size*=sizeof(memc_mn);

	return Size;
}
static integer _MemC_MN_Scan_(memc_mn *_R_ Ptr)
{
	__dlOuOlb__
		if(Ptr->Next)
			if(Ptr==Ptr->Next->Prev)
				Ptr=Ptr->Next;
			else return 0;
		else return 1;
}
static memc_mn *_MemC_MN_Search_Space_(memc_mn *_R_ Ptr,ADDRESS Demand)
{
	memc_mn *Here=NULL;

	for(address Size=(address)FULL;Ptr;Ptr=Ptr->Next)
		if(!(Ptr->Home))
			if(Demand<=Ptr->Size)
				if(Size>Ptr->Size)
				{
					Size=Ptr->Size;
					Here=Ptr;
				}

	return Here;
}
static address _MemC_MN_Search_Size_(memc_mn *_R_ Ptr)
{
	address Temp;

	for(Temp=0;Ptr;Ptr=Ptr->Next)
		if(!(Ptr->Home))
			if(Temp<Ptr->Size)
				Temp=Ptr->Size;

	return Temp;
}
static memc_mn *_MemC_MN_Search_Node_(memc_mn *Node)
{
	if(Node)
	{
		Node--;
		if(Node->Home)
		{
			if(Node->Home!=Node->Home->LinkSelf)
				Node=NULL;
		}
		else
			Node=NULL;
	}

	return Node;
}
static integer _MemC_MN_Borrow_(memc_mn _PL_ Node,ADDRESS Demand)
{
	if(Demand<Node->Size)
	{
		if(Node->Next)
		{
			Node->Next->Prev=(memc_mn*)((address)(Node+1)+Demand);
			Node->Next->Prev->Next=Node->Next;
			Node->Next=Node->Next->Prev;
		}
		else
		{
			Node->Next=(memc_mn*)((address)(Node+1)+Demand);
			Node->Next->Next=NULL;
		}
		{
			Node->Next->Prev=Node;

			Node->Next->Size=Node->Size-Demand-sizeof(memc_mn);
			Node->Next->Home=NULL;

			Node->Size=Demand;
		}
	}
	else goto FAILURE;

	return 1;
FAILURE:
	return 0;
}
static general _MemC_MN_Attach_(memc_mn _PL_ Node)
{
	Node->Size+=sizeof(memc_mn);
	Node->Size+=Node->Next->Size;

	Node->Next=Node->Next->Next;
	if(Node->Next)
		Node->Next->Prev=Node;
}
static address _MemC_MN_Return_(memc_mn *_PL_ Node)
{
	address Return=0;

	if((*Node)->Prev)
		if(!((*Node)->Prev->Home))
		{
			*Node=(*Node)->Prev;
			_MemC_MN_Attach_(*Node);
			Return++;
		}
	if((*Node)->Next)
		if(!((*Node)->Next->Home))
		{
			_MemC_MN_Attach_(*Node);
			Return++;
		}
	(*Node)->Home=NULL;

	return Return;
}
static memc_l2 _MemC_ML_Search_Home_(memc_ml _PL_ ML,ADDRESS Demand)
{
	memc_ml *Here=ML;
	memc_mn *Node;
	address Size=(address)FULL;
	memc_l2 Return={NULL,NULL};

	do
		if(Demand>Here->SizeAble)
			Here=Here->LinkNext;
		else
		{
			Node=(memc_mn*)(Here+1);
			if(_MemC_MN_Scan_(Node))
			{
				memc_mn *Temp=_MemC_MN_Search_Space_(Node,Demand);

				if(Temp)
					if(Size>Temp->Size)
					{
						Size=Temp->Size;
						Return.L[0]=Here;
						Return.L[1]=Temp;
					}
				Here=Here->LinkNext;
			}
			else
			{
				Return.L[0]=NULL;
				Return.L[1]=NULL;
				break;
			}
		}
	while(Here!=ML);

	return Return;
}
static inline general *_MemC_MN_Give_(memc_mn _PL_ Node,ADDRESS Demand)
{
	ADDRESS Margin=Node->Size;
	byte_08 _PL_ Return=memset(Node+1,0x6F,Margin);

	if(Demand<Margin)
		memset(Return+Demand,0x78,Margin-Demand);

	return Return;
}
static inline general _MemC_MN_Take_(memc_mn _PL_ Node)
{
	memset(Node+1,0x58,Node->Size);
}
_MEMC_ general *MemC_ML_Borrow_(memc_ml _PL_ ML,ADDRESS Demand)
{
	general *Memory;

	if(ML)
	{
		ADDRESS Margin=_MemC_MN_Margin_(Demand);

		if(Margin)
		{
			MEMC_L2 Select=_MemC_ML_Search_Home_(ML,Margin);

			if(Select.L[0])
			{
				memc_ml _PL_ Home=Select.L[0];
				memc_mn _PL_ Node=Select.L[1];
				ADDRESS Size=Node->Size;

				Node->Home=Home;
				if(_MemC_MN_Borrow_(Node,Margin))
					Acs_(address,Home->SizeIdle)-=sizeof(memc_mn);
				else
					Acs_(address,Home->NumsIdle)--;
				if(Size==Home->SizeAble)
					Acs_(address,Home->SizeAble)=_MemC_MN_Search_Size_(Node);
				{
					Acs_(address,Home->NumsUsed)++;
					Acs_(address,Home->SizeIdle)-=Margin;
					Acs_(address,Home->SizeUsed)+=Margin;
				}
				Memory=_MemC_MN_Give_(Node,Demand);
			}
			else
				Memory=NULL;
		}
		else
			Memory=NULL;
	}
	else
		Memory=NULL;

	return Memory;
}
_MEMC_ integer _MemC_ML_Return_(general _PL_ Memory)
{
	memc_mn *Node=_MemC_MN_Search_Node_(Memory);

	if(Node)
	{
		memc_ml _PL_ Home=Node->Home;
		ADDRESS Size=Node->Size;
		ADDRESS Mode=_MemC_MN_Return_(&Node);

		Acs_(address,Home->SizeIdle)+=MemC_Size_(memc_mn,Mode);
		Acs_(address,Home->SizeIdle)+=Size;
		Acs_(address,Home->SizeUsed)-=Size;

		Acs_(address,Home->NumsIdle)-=Mode;
		Acs_(address,Home->NumsIdle)++;
		Acs_(address,Home->NumsUsed)--;

		if(Home->SizeAble<Node->Size)
			Acs_(address,Home->SizeAble)=Node->Size;

		_MemC_MN_Take_(Node);
	}
	else
		goto FAILURE;

	return 1;
FAILURE:
	return 0;
}
_MEMC_ integer MemC_ML_Kill_(memc_ml _PL_ ML)
{
	if(ML)
	{
		memc_ml *PtrML=ML;

		do
		{
			if(PtrML->NumsUsed)
			{
				memc_mn _PL_ PtrMN=(memc_mn*)(PtrML+1);

				PtrMN->Home=NULL;
				PtrMN->Prev=NULL;
				PtrMN->Next=NULL;
				PtrMN->Size=MemC_Size_(memc_mn,PtrML->NumsIdle+PtrML->NumsUsed-1)+(PtrML->SizeIdle+PtrML->SizeUsed);
				_MemC_MN_Take_(PtrMN);

				Acs_(address,PtrML->SizeAble)=PtrMN->Size;
				Acs_(address,PtrML->SizeIdle)=PtrMN->Size;
				Acs_(address,PtrML->SizeUsed)=0;
				Acs_(address,PtrML->NumsIdle)=1;
				Acs_(address,PtrML->NumsUsed)=0;
			}
			PtrML=PtrML->LinkNext;
		}
		while(PtrML!=ML);
	}
	else
		goto FAILURE;

	return 1;
FAILURE:
	return 0;
}

_MEMC_ memc_ml *MemC_ML_Master_(GENERAL _PL_ Memory)
{
	memc_ml *Root;

	if(Memory)
	{
		MEMC_MN *Node=Memory;

		Node--;
		Root=(Node->Home)?((Node->Home==Node->Home->LinkSelf)?(Node->Home):(NULL)):(NULL);
	}
	else
		Root=NULL;

	return Root;
}
_MEMC_ address MemC_ML_Usable_(GENERAL _PL_ Memory)
{
	address Size;

	if(Memory)
	{
		MEMC_MN *Node=Memory;

		Node--;
		Size=(Node->Home)?((Node->Home==Node->Home->LinkSelf)?(Node->Size):(0)):(0);
	}
	else
		Size=0;

	return Size;
}

static address _MemC_ML_Link_Count_(MEMC_ML _PL_ ML)
{
	MEMC_ML *_R_ Ptr=ML;
	address Count=0;

	do
	{
		Count++;
		Ptr=Ptr->LinkNext;
	}
	while(Ptr!=ML);

	return Count;
}
static address _MemC_ML_Used_Count_(MEMC_ML _PL_ ML)
{
	MEMC_ML *_R_ Ptr=ML;
	address Count=0;

	do
	{
		Count+=Ptr->NumsUsed;
		Ptr=Ptr->LinkNext;
	}
	while(Ptr!=ML);

	return Count;
}
static general _MemC_ML_Used_Array_(MEMC_ML _PL_ ML,address *_R_ Array)
{
	MEMC_ML *_R_ Ptr=ML;

	do
	{
		*Array=Ptr->SizeUsed+MemC_Size_(memc_mn,Ptr->NumsUsed);
		Array++;
		Ptr=Ptr->LinkNext;
	}
	while(Ptr!=ML);
}
static general _MemC_ML_Able_Array_(MEMC_ML _PL_ ML,address *_R_ Array)
{
	MEMC_ML *_R_ Ptr=ML;

	do
	{
		*Array=Ptr->SizeAble;
		Array++;
		Ptr=Ptr->LinkNext;
	}
	while(Ptr!=ML);
}
static integer _MemC_ML_Able_Check_(ADDRESS *_R_ PtrU,address _PL_ Able,ADDRESS _PL_ EndA)
{
	address *PtrA;
	address *Mark;
	address Size;

	for(;PtrU<Able;PtrU++)
		if(*PtrU)
		{
			for(PtrA=Able,Mark=NULL,Size=(address)FULL;PtrA<EndA;PtrA++)
				if((*PtrU)<=(*PtrA))
					if(Size>(*PtrA))
					{
						Size=*PtrA;
						Mark=PtrA;
					}

			if(Mark)
				(*Mark)-=(*PtrU);
			else
				break;
		}

	return (PtrU==Able);
}
static general _MemC_ML_Head_Array_(MEMC_ML _PL_ ML,MEMC_MN **_R_ Array)
{
	MEMC_ML *_R_ PtrML=ML;
	MEMC_MN *PtrMN;

	do
	{
		if(PtrML->NumsUsed)
			for(PtrMN=(memc_mn*)(PtrML+1);PtrMN;PtrMN=PtrMN->Next)
				if(PtrMN->Home)
				{
					*Array=PtrMN;
					Array++;
				}
		PtrML=PtrML->LinkNext;
	}
	while(PtrML!=ML);
}
static integer _MemC_MN_Comp_Size_(MEMC_MN _PL_ A,MEMC_MN _PL_ B)
{
	return (A->Size<B->Size);
}
static integer _MemC_ML_Twin_Alloc_(memc_ml _PL_ ML,MEMC_MN _PL_ *_R_ Old,MEMC_MN _PL_ _PL_ End)
{
	general **New;

	for(New=(general**)End;Old<End;Old++,New++)
	{
		*New=MemC_ML_Borrow_(ML,(*Old)->Size);
		if(New)
			if(MemC_Copy_1D_((byte_08*)((*Old)+1),(byte_08*)(*New),(*Old)->Size)==MemCErrZero);
			else
			{
				MemC_ML_Return_(*New);
				break;
			}
		else
			break;
	}
	if(Old==End)
		goto SUCCESS;
	else
	{
		for(New--;New>=End;New--)
			MemC_ML_Return_(*New);

		goto FAILURE;
	}
FAILURE:
	return 0;
SUCCESS:
	return 1;
}
static general _MemC_ML_Over_Write_(MEMC_MN _PL_ *_R_ Old,MEMC_MN _PL_ _PL_ End)
{
	for(GENERAL _PL_ *_R_ New=(general**)End,_PL_ *Bound,**_R_ Ptr;Old<End;Old++,New++)
	{
		{
			Ptr=(general**)((*Old)+1);
			Bound=(general**)((address)Ptr+(*Old)->Size);
		}
		{
			Ptr[0]=*New;
			Ptr[1]=(general**)(Ptr[0])+1;
			Ptr[2]=(general**)(Ptr[1])+1;
			Ptr[3]=(general**)(Ptr[2])+1;
		}
		for(Ptr+=4;Ptr<Bound;Ptr+=4)
		{
			Ptr[0]=(general**)(Ptr[-1])+1;
			Ptr[1]=(general**)(Ptr[0])+1;
			Ptr[2]=(general**)(Ptr[1])+1;
			Ptr[3]=(general**)(Ptr[2])+1;
		}
	}
}
_MEMC_ integer MemC_ML_Move_(memc_ml _PL_ Source,memc_ml _PL_ Target,memc_ms _PL_ Buffer)
{
	if(Source)
		if(Target)
		{
			ADDRESS Sources=_MemC_ML_Link_Count_(Source);
			ADDRESS Targets=_MemC_ML_Link_Count_(Target);

			if(Buffer->Nums<(Sources+Targets))
				goto FAILURE;
			else
			{
				ADDRESS Useds=_MemC_ML_Used_Count_(Source);
				
				if((Buffer->Nums)<(3*Useds))
					goto FAILURE;
				else
				{
					address _PL_ Used=Buffer->Slot.V;
					address _PL_ Able=Used+Sources;

					_MemC_ML_Used_Array_(Source,Used);
					_MemC_ML_Able_Array_(Target,Able);
					if(_MemC_ML_Able_Check_(Used,Able,Able+Targets))
					{
						MEMC_MN *_PL_ Head=(memc_mn**)(Buffer->Slot.P);
						address _PL_ Temp=(address*)(Head+Useds);

						_MemC_ML_Head_Array_(Source,Head);
						if(MemC_Sort_(_MemC_MN_Comp_Size_,Head,NULL,Temp,Useds)==MemCErrZero)
							if(_MemC_ML_Twin_Alloc_(Target,Head,(memc_mn**)Temp))
								_MemC_ML_Over_Write_(Head,(memc_mn**)Temp);
							else
								goto FAILURE;
						else
							goto FAILURE;
					}
					else
						goto FAILURE;
				}
			}
		}
		else
			goto FAILURE;
	else
		goto FAILURE;

	return 1;
FAILURE:
	return 0;
}

#undef _MemC_ML_Free_
#undef _MemC_ML_Malloc_
#endif
#endif

#if(Fold_(Undefinition:MemClip Macros))
#undef _MEMC_
#endif

#if(Fold_(Library Casing))
MEMCASE MemC=
{
	.Version=IdiomVersion,
	.Void_=MemC_Void_,
	.Type=
	{
		.N00=TableType+MemCTypeNone_00,
		.B08=TableType+MemCTypeByte_08,
		.Int=TableType+MemCTypeInteger,
		.Add=TableType+MemCTypeAddress,
		.Enum_=MemC_DT_Enum_,
		.Desc_=MemC_DT_Desc_
	},
	.Alloc=
	{
		.Byte_=MemC_Alloc_Byte_,
		.DN_=_MemC_Alloc_ND_
	},
	.Set=
	{
		.Check_=MemC_Check_,
		.Deloc_=MemC_Deloc_Set_
	},
	.Copy=
	{
		.DN_=_MemC_Copy_,
		.Step_=MemC_Copy_Step_
	},
	.Preset.D1_=_MemC_Init_1D_,
	.Reform=
	{
		.DN_=_MemC_Reform_,
		.Shape_=MemC_Reform_Shape_
	},
	.Assign.D1_=_MemC_Assign_1D_,
	.Sort=
	{
		.Index_=MemC_Self_,
		.Do_=MemC_Sort_
	},
	.Size=
	{
		.Add_=_MemC_Size_Add_,
		.Mul_=_MemC_Size_Mul_
	},
	.MS=
	{
		.Create_=MemC_MS_Create_,
		.Delete_=MemC_MS_Delete_,
		.Size_=MemC_MS_Size_,
		.Change_=MemC_MS_Change_,
		.Init_=MemC_MS_Init_,
		.Null_=MemC_MS_Null_,
		.Dims_=MemC_MS_Dims_,
		.Joke_=MemC_MS_Joke_,
		.Oops_=MemC_MS_Oops_
	},
	.MC=
	{
		.Create_=MemC_MC_Create_,
		.Delete_=MemC_MC_Delete_,
		.Size_=MemC_MC_Size_,
		.Form_=MemC_MC_Form_,
		.Change_=MemC_MC_Change_
	},
	.ML=
	{
		.Create_=MemC_ML_Create_,
		.Delete_=MemC_ML_Delete_,
		.Size_=MemC_ML_Size_,
		.Kill_=MemC_ML_Kill_,
		.Move_=MemC_ML_Move_,
		.Borrow_=MemC_ML_Borrow_,
		.Return_=_MemC_ML_Return_,
		.Master_=MemC_ML_Master_,
		.Usable_=MemC_ML_Usable_
	}
};
MEMCASE *MemC_(general) { return &MemC; }
#endif
