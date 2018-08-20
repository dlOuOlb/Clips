#include "memclip.h"

#if(MemC_Fold_(Definition:Global Constants))
#define _MemC_DT_Parse_(Enum,Size) {.Scope=IdiomVersion,.Index=(Enum),.Flag=0,.SizeType=(Size),.SizeName=sizeof(IdiomType[Enum]),.Name=IdiomType[Enum],.Link=NULL,.Meta=NULL}

static BYTE_08 IdiomVersion[16]="Date:2018.08.20";
static BYTE_08 IdiomType[4][8]={"none_00","byte_08","integer","address"};
static ADDRESS ConstantZero[MemC_Copy_Max_Dimension]={0};

static MEMC_DT TableType[4]=
{
	_MemC_DT_Parse_(MemCTypeNone_00,0),
	_MemC_DT_Parse_(MemCTypeByte_08,sizeof(byte_08)),
	_MemC_DT_Parse_(MemCTypeInteger,sizeof(integer)),
	_MemC_DT_Parse_(MemCTypeAddress,sizeof(address))
};
static MEMC_DT _PL_ AddressType[MemCTypes]={TableType+MemCTypeNone_00,TableType+MemCTypeByte_08,TableType+MemCTypeInteger,TableType+MemCTypeAddress};

BYTE_08 _PL_ MemClip=IdiomVersion;
GENERAL _PL_ MemCrux=&MemCrux;
MEMC_DT _PL_ _PL_ MemCType=AddressType;

#undef _MemC_DT_Parse_
#endif

#if(MemC_Fold_(Definition:Memory Functions))
#if(MemC_Fold_(Part:Memory Set Handle))
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
	ADDRESS _PL_ End=Ptr+Nums;

	while(Ptr<End)
		if(*Ptr)
			Ptr++;
		else
			break;

	return (Ptr==End);
}
static integer _MemC_Array_All_Zero_(ADDRESS *_R_ Ptr,ADDRESS Nums)
{
	ADDRESS _PL_ End=Ptr+Nums;

	while(Ptr<End)
		if(*Ptr)
			break;
		else
			Ptr++;

	return (Ptr==End);
}
static integer _MemC_Array_Boundary_(ADDRESS *_R_ Access,ADDRESS *_R_ Bound,ADDRESS Count)
{
	ADDRESS _PL_ End=Access+Count;

	while(Access<End)
		if((*Access)<(*Bound))
		{
			Access++;
			Bound++;
		}
		else
			break;

	return (Access==End);
}
integer MemC_Check_(GENERAL _PL_ *Memory,ADDRESS Sets)
{
	integer Success;

	if(Memory)
		Success=_MemC_Array_Non_Zero_((address*)Memory,Sets);
	else
		Success=0;

	return Success;
}
general MemC_Deloc_Set_(general **Memory,ADDRESS Sets)
{
	if(Memory)
	{
		GENERAL _PL_ _PL_ End=Memory+Sets;

		for(;Memory<End;Memory++)
			MemC_Deloc_(*Memory);
	}
}
#endif
#if(MemC_Fold_(Part:ND Array Memory Allocation))
static address _MemC_Origin_(ADDRESS Number,ADDRESS SizeElement)
{
	volatile address New=Number*SizeElement;
	
	if((New/SizeElement)!=Number)
		New=0;

	return New;
}
static address _MemC_Bigger_(ADDRESS Number,ADDRESS Old)
{
	volatile address New=sizeof(general*)+Old;

	if(New>Old)
	{
		volatile address Temporary=Number*New;

		if((Temporary/New)==Number)
			New=Temporary;
		else
			New=0;
	}
	else
		New=0;

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
general *MemC_Alloc_(ADDRESS _PL_ Size,ADDRESS NumberDimension,ADDRESS SizeElement)
{
	general *Memory=NULL;

	if(Size)
		if(NumberDimension)
			if(SizeElement)
			{
				ADDRESS _PL_ End=Size+(NumberDimension-1);
				ADDRESS *PtrS=End;
				address Temporary=_MemC_Origin_(*PtrS,SizeElement);

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
#endif
#if(MemC_Fold_(Part:1D, 2D, 3D, and 4D Array Memory Allocations))
static address _MemC_Overflow_Add_(ADDRESS A,ADDRESS B)
{
	address C=A+B;

	if(C<A)
		C=0;
	else
		if(C<B)
			C=0;

	return C;
}
static address _MemC_Overflow_Mul_(ADDRESS A,ADDRESS B)
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
general *MemC_Alloc_Byte_(ADDRESS S)
{
	ADDRESS T=sizeof(address);
	ADDRESS N=_MemC_Overflow_Mul_((S+T-1)/T,T);
	general _PL_ Memory=(N)?(malloc(N)):(NULL);

	return Memory;
}
general *_MemC_Alloc_1D_(ADDRESS Z,ADDRESS SizeElement)
{
	address BufferSize[1];

	BufferSize[0]=Z;

	return MemC_Alloc_(BufferSize,1,SizeElement);
}
general *_MemC_Alloc_2D_(ADDRESS Y,ADDRESS Z,ADDRESS SizeElement)
{
	address BufferSize[2];

	BufferSize[0]=Y;
	BufferSize[1]=Z;

	return MemC_Alloc_(BufferSize,2,SizeElement);
}
general *_MemC_Alloc_3D_(ADDRESS X,ADDRESS Y,ADDRESS Z,ADDRESS SizeElement)
{
	address BufferSize[3];

	BufferSize[0]=X;
	BufferSize[1]=Y;
	BufferSize[2]=Z;

	return MemC_Alloc_(BufferSize,3,SizeElement);
}
general *_MemC_Alloc_4D_(ADDRESS W,ADDRESS X,ADDRESS Y,ADDRESS Z,ADDRESS SizeElement)
{
	address BufferSize[4];

	BufferSize[0]=W;
	BufferSize[1]=X;
	BufferSize[2]=Y;
	BufferSize[3]=Z;

	return MemC_Alloc_(BufferSize,4,SizeElement);
}
#endif
#if(MemC_Fold_(Part:1D Array Trivials))
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
errno_t _MemC_Init_1D_(general _PL_ Memory,GENERAL _PL_ Tile,ADDRESS NumberElement,ADDRESS SizeElement)
{
	errno_t ErrorCode;

	if(_MemC_Origin_(NumberElement,SizeElement))
	{
		ADDRESS Safe=_MemC_Safe_2_(NumberElement);
		BYTE_08 _PL_ End=((byte_08*)Memory)+(Safe*SizeElement);
		byte_08 *Ptr=(byte_08*)Memory;
		address Copy=SizeElement;

		ErrorCode=MemC_Copy_Byte_(Tile,Ptr,Copy);
		if(!ErrorCode)
		{
			for(Ptr+=Copy;Ptr<End;Copy<<=1)
			{
				ErrorCode=MemC_Copy_Byte_(Memory,Ptr,Copy);
				if(ErrorCode)
					break;
				else
					Ptr+=Copy;
			}
			if(!ErrorCode)
			{
				Copy=Safe^NumberElement;
				Copy*=SizeElement;
				ErrorCode=MemC_Copy_Byte_(Memory,Ptr,Copy);
			}
		}
	}
	else
		ErrorCode=EINVAL;

	return ErrorCode;
}
errno_t _MemC_Pick_1D_(GENERAL _PL_ Input,general _PL_ Output,ADDRESS NumberChannel,ADDRESS NumberElement,ADDRESS SizeElement)
{
	ADDRESS Step=NumberChannel*SizeElement;
	BYTE_08 _PL_ End=((byte_08*)Input)+(Step*NumberElement);
	BYTE_08 *PtrI=(byte_08*)Input;
	byte_08 *PtrO=(byte_08*)Output;
	errno_t ErrorCode=EINVAL;
	
	for(;PtrI<End;PtrI+=Step,PtrO+=SizeElement)
	{
		ErrorCode=MemC_Copy_Byte_(PtrI,PtrO,SizeElement);
		if(ErrorCode)
			break;
	}

	return ErrorCode;
}
errno_t _MemC_Fill_1D_(GENERAL _PL_ Input,general _PL_ Output,ADDRESS NumberChannel,ADDRESS NumberElement,ADDRESS SizeElement)
{
	ADDRESS Step=NumberChannel*SizeElement;
	BYTE_08 _PL_ End=((byte_08*)Input)+(SizeElement*NumberElement);
	BYTE_08 *PtrI=(byte_08*)Input;
	byte_08 *PtrO=(byte_08*)Output;
	errno_t ErrorCode=EINVAL;

	for(;PtrI<End;PtrI+=SizeElement,PtrO+=Step)
	{
		ErrorCode=MemC_Copy_Byte_(PtrI,PtrO,SizeElement);
		if(ErrorCode)
			break;
	}

	return ErrorCode;
}
#endif
#if(MemC_Fold_(Part:ND Array Data Copy))
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
	errno_t ErrorCode=EINVAL;

	for(End+=(JumpS[0]*Length[0]);PointerS<End;PointerS+=JumpS[0],PointerT+=JumpT[0])
	{
		ErrorCode=MemC_Copy_Byte_(PointerS,PointerT,Copy);
		if(ErrorCode)
			break;
	}

	return ErrorCode;
}
static errno_t _MemC_Copy_Recursive_(BYTE_08 _PL_ MemoryS,byte_08 _PL_ MemoryT,ADDRESS _PL_ JumpS,ADDRESS _PL_ JumpT,ADDRESS _PL_ OriginS,ADDRESS _PL_ OriginT,ADDRESS _PL_ Length,ADDRESS Dimensions,ADDRESS Bytes)
{
	errno_t ErrorCode=EINVAL;

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

		for(End+=(JumpS[0]*Length[0]);PointerS<End;PointerS+=JumpS[0],PointerT+=JumpT[0])
		{
			ErrorCode=_MemC_Copy_Recursive_(PointerS,PointerT,NextJumpS,NextJumpT,NextOriginS,NextOriginT,NextLength,NextDimensions,Bytes);
			if(ErrorCode)
				break;
		}
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
errno_t _MemC_Copy_(GENERAL _PL_ MemoryS,general _PL_ MemoryT,ADDRESS _PL_ OriginS,ADDRESS _PL_ OriginT,ADDRESS _PL_ Length,ADDRESS _PL_ ShapeS,ADDRESS _PL_ ShapeT,ADDRESS Dimensions,ADDRESS Bytes)
{
	ADDRESS _PL_ OffsetS=(OriginS)?(OriginS):(ConstantZero);
	ADDRESS _PL_ OffsetT=(OriginT)?(OriginT):(ConstantZero);
	errno_t ErrorCode;

	if(_MemC_Copy_Check_Bound_(ShapeS,OffsetS,Length,Dimensions)&&_MemC_Copy_Check_Bound_(ShapeT,OffsetT,Length,Dimensions))
		switch(Dimensions)
		{
		case 0:
			ErrorCode=0;
			break;
		case 1:
			{
				ADDRESS Copy=Length[0]*Bytes;
				
				if(Copy)
					ErrorCode=MemC_Copy_Byte_(((BYTE_08*)MemoryS)+(OffsetS[0]*Bytes),((byte_08*)MemoryT)+(OffsetT[0]*Bytes),Copy);
				else
					ErrorCode=0;
			}
			break;
		default:
			if(Bytes)
				if(_MemC_Array_Non_Zero_(Length,Dimensions))
					if(Dimensions>MemC_Copy_Max_Dimension)
						ErrorCode=EINVAL;
					else
					{
						address JumpS[MemC_Copy_Max_Dimension];
						address JumpT[MemC_Copy_Max_Dimension];

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
					ErrorCode=0;
			else
				ErrorCode=0;
		}
	else
		ErrorCode=EINVAL;

	return ErrorCode;
}
#endif
#if(MemC_Fold_(Part:ND Array Data Reformation))
static integer _MemC_Reform_Valid_(ADDRESS *_R_ Map,ADDRESS Dims)
{
	address Table[MemC_Copy_Max_Dimension]={0};
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
	address Temp;

	for(Temp=(*Dims)-1;Temp;Temp--)
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
	address Jump[MemC_Copy_Max_Dimension];
	ADDRESS Last=Dims-1;
	address Prod;
	address IdxS;
	address IdxT;
	address IdxJ;
	errno_t ErrorCode=0;

	for(IdxT=0;IdxT<Total;IdxT++)
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
		if(ErrorCode)
			break;
	}

	return ErrorCode;
}
errno_t _MemC_Reform_(GENERAL _PL_ MemoryS,general _PL_ MemoryT,ADDRESS _PL_ ShapeS,ADDRESS _PL_ MapT,address Dimensions,address Bytes)
{
	errno_t ErrorCode;

	if(Dimensions)
	{
		_MemC_Reform_Short_(ShapeS,MapT,&Dimensions,&Bytes);
		if(Dimensions>1)
			if(Dimensions<MemC_Copy_Max_Dimension)
				if(_MemC_Reform_Valid_(MapT,Dimensions))
				{
					ADDRESS Total=_MemC_Array_Prod_(ShapeS,Dimensions);

					if(Total)
					{
						address ShapeSNew[MemC_Copy_Max_Dimension];
						address MapTNew[MemC_Copy_Max_Dimension];

						ErrorCode=MemC_Copy_1D_(ShapeS,ShapeSNew,Dimensions,address);
						if(ErrorCode)
							goto ESCAPE;

						ErrorCode=MemC_Copy_1D_(MapT,MapTNew,Dimensions,address);
						if(ErrorCode)
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
			if(MapT[0])
			{
INVALID:
				ErrorCode=EINVAL;
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
		ErrorCode=0;
	}
ESCAPE:
	return ErrorCode;
}
#endif
#if(MemC_Fold_(Part:Object Sorting))
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
	errno_t Error=MemC_Copy_1D_(IdxO,IdxA,Copy,address);

	if(!Error)
	{
		for(;IdxO<MatchB;IdxA++,IdxO++,PtrT++)
			IdxO[PtrT[0]]=IdxA[0];
		for(IdxA+=Step,IdxO+=Step,PtrT+=Step;IdxO>=MatchB;IdxA--,IdxO--,PtrT--)
			IdxO[PtrT[0]]=IdxA[0];
	}

	return Error;
}
errno_t MemC_Sort_(MemC_Func_Declare_C_(integer,Comp_,GENERAL _PL_,GENERAL _PL_),GENERAL *_PL_ Refer,address _PL_ Index,address _PL_ Buffer,ADDRESS Length)
{
	errno_t ErrorCode=0;

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
					if(ErrorCode)
						goto ESCAPE;
				}
	}
ESCAPE:
	return ErrorCode;
}
#endif
#if(MemC_Fold_(Part:Others))
general MemC_Void_(general)
{
}
general MemC_Self_(address *_R_ Table,ADDRESS Length,INTEGER Mode)
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
address _MemC_Assign_1D_(general _PL_ Indexer,GENERAL _PL_ Indexed,ADDRESS Interval,ADDRESS Indices,ADDRESS TypeSize,INTEGER Mode)
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
address _MemC_Switch_(GENERAL _PL_ Key,GENERAL _PL_ _PL_ ReferTable,ADDRESS *ReferLength,ADDRESS KeyLength,ADDRESS Refers,ADDRESS TypeSize)
{
	ADDRESS ByteSize=KeyLength*TypeSize;
	address Index=0;

	Index=~Index;
	if(ByteSize)
	{
		GENERAL _PL_ _PL_ End=ReferTable+Refers;
		GENERAL _PL_ *PointerT=ReferTable;

		if(ReferLength)
			for(;PointerT<End;PointerT++,ReferLength++)
			{
				if(ReferLength[0]==KeyLength)
					if(!memcmp(Key,PointerT[0],ByteSize))
					{
						Index=PointerT-ReferTable;
						break;
					}
			}
		else
			for(;PointerT<End;PointerT++)
				if(!memcmp(Key,PointerT[0],ByteSize))
				{
					Index=PointerT-ReferTable;
					break;
				}
	}

	return Index;
}
#endif
#endif

#if(MemC_Fold_(Definition:MemClip Structure Functions))
#if(MemC_Fold_(Part:MemC_MS))
memc_ms *MemC_MS_Create_(GENERAL _PL_ ID,ADDRESS Slots)
{
	memc_ms *MS;

	if(Slots)
	{
		address Size=_MemC_Overflow_Mul_(Slots,sizeof(general*));

		if(Size)
		{
			Size=_MemC_Overflow_Add_(Size,sizeof(memc_ms));
			if(Size)
			{
				MS=MemC_Alloc_Byte_(Size);
				if(MS)
				{
					Acs_(GENERAL*,MS->ID)=ID;
					Acs_(MEMC_DT*,MS->Type)=MemCType[MemCTypeAddress];
					Acs_(address,MS->Nums)=Slots;
					Acs_(address*,MS->Slot.V)=MemC_Clear_1D_(MS+1,Slots,address);
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
			Acs_(MEMC_DT*,MS->Type)=MemCType[MemCTypeAddress];
			Acs_(address,MS->Nums)=0;
			Acs_(address*,MS->Slot.V)=NULL;
		}
	}

	return MS;
}
general MemC_MS_Delete_(memc_ms *_PL_ MS)
{
	MemC_Deloc_(*MS);
}

address MemC_MS_Size_(MEMC_MS _PL_ MS)
{
	return (MS)?(sizeof(memc_ms)+MemC_Size_(address,MS->Nums)):(0);
}
integer MemC_MS_Change_(MEMC_MS _PL_ MS,MEMC_DT _PL_ DT)
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
integer MemC_MS_Init_(MEMC_MS _PL_ MS)
{
	if(MS)
	{
		if(MS->Nums)
			MemC_Clear_1D_(MS->Slot.V,MS->Nums,address);
		goto SUCCESS;
	}
	else
		goto FAILURE;
FAILURE:
	return 0;
SUCCESS:
	return 1;
}
integer MemC_MS_Null_(MEMC_MS _PL_ MS,INTEGER Mode)
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

integer MemC_MS_Joke_(MEMC_MS _PL_ MS)
{
	if(MS)
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

			goto SUCCESS;
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
integer MemC_MS_Oops_(MEMC_MS _PL_ MS)
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
							else
								goto SUCCESS;
						else
							Pointer=(*Pointer);
					else
						goto FAILURE;
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
#if(MemC_Fold_(Part:MemC_MC))
static address _MemC_Shape_Overflow_(ADDRESS _PL_ Shape,ADDRESS Dims)
{
	ADDRESS _PL_ End=Shape+Dims;
	ADDRESS *_R_ Ptr=Shape;
	address Total=1;

	for(;Ptr<End;Ptr++)
		Total=_MemC_Overflow_Mul_(Total,*Ptr);

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
			Size[0]=_MemC_Overflow_Mul_(Size[0],*Ptr);
			Size[1]=_MemC_Overflow_Add_(Size[0],Size[1]);
			if(!(Size[1]))
				break;
		}
		if(Ptr==Last)
		{
			Size[0]=_MemC_Overflow_Mul_(Size[0],*Ptr);
			Size[0]=_MemC_Overflow_Mul_(Size[0],SizeType);
			if(Size[0])
			{
				Size[1]=_MemC_Overflow_Mul_(Size[1],sizeof(address));
				if(Size[1])
					Size[1]=_MemC_Overflow_Add_(Size[0],Size[1]);
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
		Size[1]=_MemC_Overflow_Mul_(Shape[0],SizeType);

	return Size[1];
}
memc_mc *MemC_MC_Create_(GENERAL _PL_ ID,MEMC_MS _PL_ MS,MEMC_DT _PL_ DT)
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
								address Size=_MemC_Overflow_Mul_(Dimensions,sizeof(address));

								if(Size)
								{
									Size=_MemC_Overflow_Add_(Size,sizeof(memc_mc));
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
									if(MemC_Copy_1D_(Shape,(address*)(MC->LngND),Dimensions,address))
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
									Size[0]=_MemC_Overflow_Mul_(Dimensions,sizeof(address));
									if(Size[0])
										Size[0]=_MemC_Overflow_Add_(Size[0],sizeof(memc_mc));
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
									Size[0]=_MemC_Overflow_Add_(Size[0],Size[1]);
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
									if(MemC_Copy_1D_(Shape,(address*)(MC->LngND),Dimensions,address))
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
general MemC_MC_Delete_(memc_mc *_PL_ MC)
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
address MemC_MC_Size_(MEMC_MC _PL_ MC)
{
	return (MC)?(sizeof(memc_mc)+((MC->Dims>1)?(MemC_Size_(address,MC->Dims)):(0))+((MC->Acs1D)?(_MemC_Space_Occupied_(MC->LngND,MC->Dims,MC->Unit)):(0))):(0);
}
integer MemC_MC_Form_(MEMC_MC _PL_ MC,MEMC_MS _PL_ MS)
{
	if(MC)
		if(MS)
			if(MC->Dims<MS->Nums)
			{
				MS->Slot.V[0]=MC->Dims;
				if(MC->Dims)
					if(MemC_Copy_1D_(MC->LngND,MS->Slot.V+1,MC->Dims,address))
						goto FAILURE;
					else
						goto SUCCESS;
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
integer MemC_MC_Change_(MEMC_MC _PL_ MC,MEMC_DT _PL_ DT)
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
#endif

#if(MemC_Fold_(Definition:OpenCL Functions))
#ifdef __OPENCL_H
#if(MemC_Fold_(Part:OpenCL Object Handle))
cl_mem _Devi_Create_Buffer_(cl_context const Context,ADDRESS Elements,ADDRESS SizeElement,cl_int _PL_ Error)
{
	ADDRESS Bytes=(SizeElement)?(_MemC_Overflow_Mul_(Elements,SizeElement)):(0);
	cl_mem Return;
	cl_int Local;

	if(Bytes)
		Return=clCreateBuffer(Context,CL_MEM_READ_WRITE,Bytes,NULL,&Local);
	else
	{
		Return=NULL;
		Local=CL_INVALID_BUFFER_SIZE;
	}
	if(Error)
		*Error=Local;

	return Return;
}
cl_mem _Devi_Create_Buffer_GL_(cl_context const Context,const cl_GLuint Root,cl_int _PL_ Error)
{
	return clCreateFromGLBuffer(Context,CL_MEM_READ_WRITE,Root,Error);
}
cl_mem _Devi_Create_Buffer_Sub_(cl_mem const Root,ADDRESS Offset,ADDRESS Elements,ADDRESS SizeElement,cl_int _PL_ Error)
{
	cl_buffer_region Info;
	cl_mem Return;
	cl_int Local;

	if(SizeElement)
		goto OFFSET;
	else
	{
		Return=NULL;
		Local=CL_INVALID_BUFFER_SIZE;
		goto ESCAPE;
	}
OFFSET:
	if(Offset)
	{
		Info.origin=_MemC_Overflow_Mul_(Offset,SizeElement);
		if(Info.origin)
			goto LENGTH;
		else
		{
			Return=NULL;
			Local=CL_INVALID_VALUE;
			goto ESCAPE;
		}
	}
	else
	{
		Info.origin=0;
		goto LENGTH;
	}
LENGTH:
	if(Elements)
	{
		Info.size=_MemC_Overflow_Mul_(Elements,SizeElement);
		if(Info.size)
			Return=clCreateSubBuffer(Root,CL_MEM_READ_WRITE,CL_BUFFER_CREATE_TYPE_REGION,&Info,&Local);
		else
		{
			Return=NULL;
			Local=CL_INVALID_BUFFER_SIZE;
			goto ESCAPE;
		}
	}
	else
	{
		Return=NULL;
		Local=CL_INVALID_BUFFER_SIZE;
		goto ESCAPE;
	}
ESCAPE:
	if(Error)
		*Error=Local;

	return Return;
}

cl_int _Devi_Delete_Event_(cl_event const Event)
{
	cl_int Status=0;
	cl_int Error=Devi_Info_Event_(Event,&Status,1,cl_int,CL_EVENT_COMMAND_EXECUTION_STATUS);

	if(Error==CL_SUCCESS)
		if(Status==CL_COMPLETE)
		{
			Error=Devi_Info_Event_(Event,&Status,1,cl_int,CL_EVENT_REFERENCE_COUNT);
			if(Error==CL_SUCCESS)
				while(Status--)
				{
					Error=Devi_Event_Dec_(Event);
					if(Error!=CL_SUCCESS)
						break;
				}
		}
		else
			Error=Status;

	return Error;
}

static general _Devi_Work_Global_(address *_R_ GlobalWorkers,ADDRESS *_R_ WorkGroups,ADDRESS *_R_ LocalWorkers,const cl_uint Dimensions)
{
	ADDRESS _PL_ End=LocalWorkers+Dimensions;

	for(;LocalWorkers<End;LocalWorkers++,WorkGroups++,GlobalWorkers++)
		GlobalWorkers[0]=LocalWorkers[0]*WorkGroups[0];
}
cl_int Devi_Kenq_(cl_command_queue const Queue,cl_kernel const Kernel,ADDRESS _PL_ WorkGroups,ADDRESS _PL_ LocalWorkers,ADDRESS _PL_ GlobalOffset,const cl_uint Dimensions)
{
	cl_int Error;

	if(Dimensions>Devi_Copy_Max_Dimension)
		Error=CL_INVALID_WORK_DIMENSION;
	else
	{
		address Total[Devi_Copy_Max_Dimension];

		_Devi_Work_Global_(Total,WorkGroups,LocalWorkers,Dimensions);
		Error=clEnqueueNDRangeKernel(Queue,Kernel,Dimensions,GlobalOffset,Total,LocalWorkers,0,NULL,NULL);
	}

	return Error;
}
#endif
#if(MemC_Fold_(Part:ND Array Data Copy))
cl_int _Devi_Copy_1D_(cl_command_queue const Queue,general _PL_ MemoryS,general _PL_ MemoryT,ADDRESS OriginS,ADDRESS OriginT,ADDRESS Length,ADDRESS Bytes,DEVI_CF Mode)
{
	cl_int ErrorCode;

	switch(Mode)
	{
	case DeviCopyHtoD:
		ErrorCode=clEnqueueWriteBuffer(Queue,MemoryT,CL_TRUE,Bytes*OriginT,Bytes*Length,((byte_08*)MemoryS)+(Bytes*OriginS),0,NULL,NULL);
		break;
	case DeviCopyDtoH:
		ErrorCode=clEnqueueReadBuffer(Queue,MemoryS,CL_TRUE,Bytes*OriginS,Bytes*Length,((byte_08*)MemoryT)+(Bytes*OriginT),0,NULL,NULL);
		break;
	case DeviCopyDtoD:
		ErrorCode=clEnqueueCopyBuffer(Queue,MemoryS,MemoryT,Bytes*OriginS,Bytes*OriginT,Bytes*Length,0,NULL,NULL);
		break;
	default:
		ErrorCode=CL_INVALID_VALUE;
	}

	return ErrorCode;
}
cl_int _Devi_Copy_(cl_command_queue const Queue,general _PL_ MemoryS,general _PL_ MemoryT,ADDRESS _PL_ OriginS,ADDRESS _PL_ OriginT,ADDRESS _PL_ Length,ADDRESS _PL_ ShapeS,ADDRESS _PL_ ShapeT,const cl_uint Dimensions,ADDRESS Bytes,DEVI_CF Mode)
{
	ADDRESS _PL_ ShapeSValid=(ShapeS)?(ShapeS):(Length);
	ADDRESS _PL_ ShapeTValid=(ShapeT)?(ShapeT):(Length);
	cl_int ErrorCode=CL_INVALID_VALUE;
	
	switch(Dimensions)
	{
	case 0:
		ErrorCode=CL_SUCCESS;
		break;
	case 1:
		{
			address BufferB[4];

			if(OriginS)
				BufferB[0]=Bytes*OriginS[0];
			else
				BufferB[0]=0;
			if(OriginT)
				BufferB[1]=Bytes*OriginT[0];
			else
				BufferB[1]=0;
			BufferB[2]=Bytes*Length[0];
			
			switch(Mode)
			{
			case DeviCopyHtoD:
				ErrorCode=clEnqueueWriteBuffer(Queue,MemoryT,CL_TRUE,BufferB[1],BufferB[2],((byte_08*)MemoryS)+BufferB[0],0,NULL,NULL);
				break;
			case DeviCopyDtoH:
				ErrorCode=clEnqueueReadBuffer(Queue,MemoryS,CL_TRUE,BufferB[0],BufferB[2],((byte_08*)MemoryT)+BufferB[1],0,NULL,NULL);
				break;
			case DeviCopyDtoD:
				ErrorCode=clEnqueueCopyBuffer(Queue,MemoryS,MemoryT,BufferB[0],BufferB[1],BufferB[2],0,NULL,NULL);
				break;
			default:
				ErrorCode=CL_INVALID_VALUE;
			}
		}
		break;
	case 2:
		{
			address BufferS[4];
			address BufferT[4];
			address Region[4];

			if(OriginS)
			{
				BufferS[0]=OriginS[1]*Bytes;
				BufferS[1]=OriginS[0];
			}
			else
			{
				BufferS[0]=0;
				BufferS[1]=0;
			}
			if(OriginT)
			{
				BufferT[0]=OriginT[1]*Bytes;
				BufferT[1]=OriginT[0];
			}
			else
			{
				BufferT[0]=0;
				BufferT[1]=0;
			}
			{
				BufferS[2]=0;
				BufferS[3]=ShapeSValid[1]*Bytes;

				BufferT[2]=0;
				BufferT[3]=ShapeTValid[1]*Bytes;

				Region[0]=Length[1]*Bytes;
				Region[1]=Length[0];
				Region[2]=1;
			}
			switch(Mode)
			{
			case DeviCopyHtoD:
				ErrorCode=clEnqueueWriteBufferRect(Queue,MemoryT,CL_TRUE,BufferT,BufferS,Region,BufferT[3],ShapeTValid[0]*BufferT[3],BufferS[3],ShapeSValid[0]*BufferS[3],MemoryS,0,NULL,NULL);
				break;
			case DeviCopyDtoH:
				ErrorCode=clEnqueueReadBufferRect(Queue,MemoryS,CL_TRUE,BufferS,BufferT,Region,BufferS[3],ShapeSValid[0]*BufferS[3],BufferT[3],ShapeTValid[0]*BufferT[3],MemoryT,0,NULL,NULL);
				break;
			case DeviCopyDtoD:
				ErrorCode=clEnqueueCopyBufferRect(Queue,MemoryS,MemoryT,BufferS,BufferT,Region,BufferS[3],ShapeSValid[0]*BufferS[3],BufferT[3],ShapeTValid[0]*BufferT[3],0,NULL,NULL);
				break;
			default:
				ErrorCode=CL_INVALID_VALUE;
			}
		}
		break;
	case 3:
		{
			address BufferS[4];
			address BufferT[4];
			address Region[4];

			if(OriginS)
			{
				BufferS[0]=OriginS[2]*Bytes;
				BufferS[1]=OriginS[1];
				BufferS[2]=OriginS[0];
			}
			else
			{
				BufferS[0]=0;
				BufferS[1]=0;
				BufferS[2]=0;
			}
			if(OriginT)
			{
				BufferT[0]=OriginT[2]*Bytes;
				BufferT[1]=OriginT[1];
				BufferT[2]=OriginT[0];
			}
			else
			{
				BufferT[0]=0;
				BufferT[1]=0;
				BufferT[2]=0;
			}
			{
				BufferS[3]=ShapeSValid[2]*Bytes;
				BufferT[3]=ShapeTValid[2]*Bytes;

				Region[0]=Length[2]*Bytes;
				Region[1]=Length[1];
				Region[2]=Length[0];
			}
			switch(Mode)
			{
			case DeviCopyHtoD:
				ErrorCode=clEnqueueWriteBufferRect(Queue,MemoryT,CL_TRUE,BufferT,BufferS,Region,BufferT[3],ShapeTValid[1]*BufferT[3],BufferS[3],ShapeSValid[1]*BufferS[3],MemoryS,0,NULL,NULL);
				break;
			case DeviCopyDtoH:
				ErrorCode=clEnqueueReadBufferRect(Queue,MemoryS,CL_TRUE,BufferS,BufferT,Region,BufferS[3],ShapeSValid[1]*BufferS[3],BufferT[3],ShapeTValid[1]*BufferT[3],MemoryT,0,NULL,NULL);
				break;
			case DeviCopyDtoD:
				ErrorCode=clEnqueueCopyBufferRect(Queue,MemoryS,MemoryT,BufferS,BufferT,Region,BufferS[3],ShapeSValid[1]*BufferS[3],BufferT[3],ShapeTValid[1]*BufferT[3],0,NULL,NULL);
				break;
			default:
				ErrorCode=CL_INVALID_VALUE;
			}
		}
		break;
	default:
		ErrorCode=CL_INVALID_VALUE;
	}

	return ErrorCode;
}
#endif
#if(MemC_Fold_(Part:Devi_QC))
static cl_platform_id *_Devi_QC_Alloc_List_Platform_(cl_uint _PL_ Platforms)
{
	cl_platform_id *List;

	if(Devi_Numb_Platforms_(Platforms)==CL_SUCCESS)
	{
		List=MemC_Alloc_1D_(*Platforms,cl_platform_id);
		if(List)
			if(Devi_List_Platforms_(List,Platforms,*Platforms)!=CL_SUCCESS)
				MemC_Deloc_(List);
	}
	else
		List=NULL;

	return List;
}
static cl_device_id *_Devi_QC_Alloc_List_Device_(cl_platform_id const Platform,cl_uint _PL_ Devices)
{
	cl_device_id *List;

	if(Devi_Numb_Devices_(Platform,Devices)==CL_SUCCESS)
	{
		List=MemC_Alloc_1D_(*Devices,cl_device_id);
		if(List)
			if(Devi_List_Devices_(Platform,List,Devices,*Devices)!=CL_SUCCESS)
				MemC_Deloc_(List);
	}
	else
		List=NULL;

	return List;
}
devi_qc *Devi_QC_Create_(const cl_uint ChoicePlatform,const cl_uint ChoiceDevice)
{
	devi_qc *QC;
	cl_uint Platforms;
	cl_platform_id *ListPlatform=_Devi_QC_Alloc_List_Platform_(&Platforms);

	if(ListPlatform)
		if(ChoicePlatform<Platforms)
		{
			cl_uint Devices;
			cl_device_id *ListDevice=_Devi_QC_Alloc_List_Device_(ListPlatform[ChoicePlatform],&Devices);

			if(ListDevice)
				if(ChoiceDevice<Devices)
				{
					QC=MemC_Alloc_Unit_(devi_qc);
					if(QC)
					{
						cl_int Error=CL_SUCCESS;

						Acs_(cl_context,QC->Context)=Devi_Create_Context_(ListDevice+ChoiceDevice,1,&Error);
						if(QC->Context)
						{
							Acs_(cl_command_queue,QC->Queue)=Devi_Create_Queue_(QC->Context,ListDevice[ChoiceDevice],&Error);
							if(QC->Queue)
							{
								Acs_(cl_platform_id,QC->Platform)=ListPlatform[ChoicePlatform];
								Acs_(cl_device_id,QC->Device)=ListDevice[ChoiceDevice];
							}
							else
							{
								Devi_Delete_Context_(Acs_(cl_context,QC->Context));
								MemC_Deloc_(QC);
							}
						}
						else
							MemC_Deloc_(QC);
					}
				}
				else
					QC=NULL;
			else
				QC=NULL;

			MemC_Deloc_(ListDevice);
		}
		else
			QC=NULL;
	else
		QC=NULL;

	MemC_Deloc_(ListPlatform);

	return QC;
}
general Devi_QC_Delete_(devi_qc *_PL_ QC)
{
	if(*QC)
	{
		Devi_Delete_Queue_(Acs_(cl_command_queue,(*QC)->Queue));
		Devi_Delete_Context_(Acs_(cl_context,(*QC)->Context));
		MemC_Deloc_(*QC);
	}
}
#endif
#if(MemC_Fold_(Part:Devi_KM))
static address _Devi_KM_Arg_Size_Padding_(address Size)
{
	Size+=sizeof(address);
	Size--;
	Size/=sizeof(address);
	Size*=sizeof(address);

	return Size;
}
devi_km *Devi_KM_Create_(GENERAL _PL_ ID,ADDRESS Args,ADDRESS Dims)
{
	devi_km *KM;

	if(Dims>Devi_Copy_Max_Dimension)
	{
ESCAPE:
		KM=NULL;
	}
	else
	{
		address Temp[2];

		Temp[0]=_MemC_Overflow_Mul_(Dims,sizeof(address)<<2);
		if(!(Temp[0]))
			goto ESCAPE;

		Temp[1]=_MemC_Overflow_Mul_(Args,sizeof(address)<<1);
		if(!(Temp[1]))
			goto ESCAPE;

		Temp[0]=_MemC_Overflow_Add_(Temp[0],Temp[1]);
		if(!(Temp[0]))
			goto ESCAPE;

		Temp[1]=_MemC_Overflow_Mul_(Args,sizeof(devi_df));
		if(!(Temp[1]))
			goto ESCAPE;

		Temp[0]=_MemC_Overflow_Add_(Temp[0],Temp[1]);
		if(!(Temp[0]))
			goto ESCAPE;

		Temp[0]=_MemC_Overflow_Add_(Temp[0],sizeof(devi_km));
		KM=MemC_Alloc_Byte_(Temp[0]);
	}
	if(KM)
	{
		Acs_(GENERAL*,KM->ID)=ID;
		Acs_(address,KM->KArgs)=Args;
		Acs_(address,KM->WDims)=Dims;
		Acs_(cl_kernel,KM->Kernel)=NULL;

		Acs_(ADDRESS*,KM->ArgSize)=MemC_Clear_1D_(KM+1,Args<<1,address);
		Acs_(ADDRESS*,KM->ArgAccess.V)=KM->ArgSize+Args;

		Acs_(address*,KM->WLocals)=MemC_Clear_1D_((address*)(KM->ArgAccess.V+Args),Dims<<2,address);
		Acs_(address*,KM->WGroups)=KM->WLocals+Dims;
		Acs_(address*,KM->WOffset)=KM->WGroups+Dims;
		Acs_(address*,KM->WLength)=KM->WOffset+Dims;

		Acs_(devi_df*,KM->ArgFlag)=MemC_Clear_1D_((devi_df*)(KM->WLength+Dims),Args,devi_df);
		Acs_(general*,KM->ArgMemory)=NULL;
	}

	return KM;
}
cl_int _Devi_KM_Type_(DEVI_KM _PL_ KM,ADDRESS Order,ADDRESS ArgSize,DEVI_DF Domain)
{
	cl_int Error;

	if(KM)
		if(KM->ArgMemory)
			Error=CL_INVALID_HOST_PTR;
		else
			if(Order<KM->KArgs)
			{
				switch(Domain)
				{
				case DeviDomainConstant:
				case DeviDomainGlobal:
					((address*)(KM->ArgSize))[Order]=sizeof(cl_mem);
					break;
				case DeviDomainLocal:
				case DeviDomainPrivate:
					((address*)(KM->ArgSize))[Order]=ArgSize;
					break;
				default:
					Error=CL_INVALID_ARG_VALUE;
					goto ESCAPE;
				}
				{
					((devi_df*)(KM->ArgFlag))[Order]=Domain;
					Error=CL_SUCCESS;
				}
			}
			else
				Error=CL_INVALID_ARG_INDEX;
	else
		Error=CL_INVALID_HOST_PTR;
ESCAPE:
	return Error;
}
cl_int Devi_KM_Init_(devi_km _PL_ KM,cl_kernel const Kernel)
{
	cl_int Error;

	if(KM)
		if(KM->ArgMemory)
			Error=CL_INVALID_HOST_PTR;
		else
		{
			cl_uint Args;

			Error=Devi_Info_Kernel_(Kernel,&Args,1,cl_uint,CL_KERNEL_NUM_ARGS);
			if(Error==CL_SUCCESS)
				if(((address)Args)==KM->KArgs)
				{
					DEVI_DF _PL_ End=KM->ArgFlag+KM->KArgs;
					DEVI_DF *_R_ PtrF;
					ADDRESS *_R_ PtrS;
					address Total=0;
					address Temp;

					for(PtrF=KM->ArgFlag,PtrS=KM->ArgSize;PtrF<End;PtrF++,PtrS++)
						switch(*PtrF)
						{
						case DeviDomainConstant:
						case DeviDomainGlobal:
							if((*PtrS)==sizeof(cl_mem))
							{
								Total=_MemC_Overflow_Add_(Total,*PtrS);
								if(Total)
									break;
								else
									goto ESCAPE_INVALID_ARG_SIZE;
							}
							else
								goto ESCAPE_INVALID_ARG_SIZE;
						case DeviDomainLocal:
							if(*PtrS)
								break;
							else
								goto ESCAPE_INVALID_ARG_SIZE;
						case DeviDomainPrivate:
							Temp=_Devi_KM_Arg_Size_Padding_(*PtrS);
							if(Temp)
							{
								Total=_MemC_Overflow_Add_(Total,Temp);
								if(Total)
									break;
								else
									goto ESCAPE_INVALID_ARG_SIZE;
							}
							else
								goto ESCAPE_INVALID_ARG_SIZE;
						default:
							Error=CL_INVALID_KERNEL_DEFINITION;
							goto ESCAPE;
						}

					if(Total)
						Acs_(general*,KM->ArgMemory)=MemC_Alloc_Byte_(Total);
					else
					{
ESCAPE_INVALID_ARG_SIZE:
						Error=CL_INVALID_ARG_SIZE;
						goto ESCAPE;
					}

					if(KM->ArgMemory)
					{
						general **PtrA=(general**)(KM->ArgAccess.P);

						{
							PtrF=KM->ArgFlag;
							PtrS=KM->ArgSize;
							PtrA[0]=MemC_Clear_Byte_((general*)(KM->ArgMemory),Total);
						}
						for(PtrF++,PtrS++,PtrA++;PtrF<End;PtrF++,PtrS++,PtrA++)
							if(PtrF[-1]==DeviDomainLocal)
							{
								PtrA[0]=PtrA[-1];
								PtrA[-1]=NULL;
							}
							else
								PtrA[0]=((byte_08*)(PtrA[-1]))+_Devi_KM_Arg_Size_Padding_(PtrS[-1]);

						if(PtrF[-1]==DeviDomainLocal)
							PtrA[-1]=NULL;

						Acs_(cl_kernel,KM->Kernel)=Kernel;
					}
					else
						Error=CL_OUT_OF_HOST_MEMORY;
				}
				else
					Error=CL_INVALID_KERNEL_ARGS;
		}
	else
		Error=CL_INVALID_HOST_PTR;
ESCAPE:
	return Error;
}
general Devi_KM_Delete_(devi_km *_PL_ KM)
{
	if(*KM)
	{
		MemC_Deloc_(Acs_(general*,(*KM)->ArgMemory));
		MemC_Deloc_(*KM);
	}
}

cl_int Devi_KM_Save_(DEVI_KM _PL_ KM,ADDRESS Order,ADDRESS Thing)
{
	cl_int Error;

	if(KM)
		if(KM->ArgMemory)
			if(Order<KM->KArgs)
				switch(KM->ArgFlag[Order])
				{
				case DeviDomainConstant:
				case DeviDomainGlobal:
					*((general**)(KM->ArgAccess.P[Order]))=*((general**)Thing);

					Error=CL_SUCCESS;
					break;
				case DeviDomainLocal:
					((address*)(KM->ArgAccess.V))[Order]=Thing;

					Error=CL_SUCCESS;
					break;
				case DeviDomainPrivate:
					if(MemC_Copy_Byte_((GENERAL*)Thing,(general*)(KM->ArgAccess.P[Order]),KM->ArgSize[Order]))
						Error=CL_INVALID_ARG_VALUE;
					else
						Error=CL_SUCCESS;
					break;
				default:
					Error=CL_INVALID_ARG_VALUE;
				}
			else
				Error=CL_INVALID_ARG_INDEX;
		else
			Error=CL_INVALID_HOST_PTR;
	else
		Error=CL_INVALID_HOST_PTR;

	return Error;
}
cl_int Devi_KM_Enqueue_(cl_command_queue const Queue,DEVI_KM _PL_ KM)
{
	cl_int Error;

	if(KM)
		if(KM->ArgMemory)
		{
			address Index=0;

			Error=CL_SUCCESS;
			while(Index<KM->KArgs)
			{
				switch(KM->ArgFlag[Index])
				{
				case DeviDomainConstant:
				case DeviDomainGlobal:
					Error=Devi_Karg_(KM->Kernel,(cl_uint)Index,KM->ArgAccess.P[Index],sizeof(cl_mem));
					break;
				case DeviDomainLocal:
					Error=Devi_Karg_(KM->Kernel,(cl_uint)Index,NULL,KM->ArgAccess.V[Index]*KM->ArgSize[Index]);
					break;
				case DeviDomainPrivate:
					Error=Devi_Karg_(KM->Kernel,(cl_uint)Index,KM->ArgAccess.P[Index],KM->ArgSize[Index]);
					break;
				default:
					Error=CL_INVALID_ARG_VALUE;
				}
				if(Error==CL_SUCCESS)
					Index++;
				else
					break;
			}
			if(Error==CL_SUCCESS)
				Error=Devi_Kenq_(Queue,KM->Kernel,KM->WGroups,KM->WLocals,KM->WOffset,(cl_uint)(KM->WDims));
		}
		else
			Error=CL_INVALID_HOST_PTR;
	else
		Error=CL_INVALID_HOST_PTR;

	return Error;
}
#endif
#if(MemC_Fold_(Part:Devi_MC))
static cl_uint _Devi_MC_Align_(cl_context const Context,cl_int *Error)
{
	cl_device_id Device;
	cl_uint Align=0;

	*Error=Devi_Info_Context_(Context,&Device,1,cl_device_id,CL_CONTEXT_DEVICES);
	if((*Error)==CL_SUCCESS)
		*Error=Devi_Info_Device_(Device,&Align,1,cl_uint,CL_DEVICE_MEM_BASE_ADDR_ALIGN);

	return Align;
}
static address _Devi_MC_Length_Padded_(address Length,ADDRESS Align)
{
	Length+=Align;
	Length--;
	Length/=Align;
	Length*=Align;

	return Length;
}
devi_mc *Devi_MC_Create_(GENERAL _PL_ ID,cl_context const Context,ADDRESS Number,ADDRESS Length,MEMC_DT _PL_ DT,cl_int *Error)
{
	devi_mc *MC;

	if(DT)
	{
		ADDRESS Align=(address)_Devi_MC_Align_(Context,Error);

		if((*Error)==CL_SUCCESS)
		{
			{
				address Size;

				if(Number)
				{
					Size=_MemC_Overflow_Mul_(Number,sizeof(cl_mem));
					if(Size)
						Size=_MemC_Overflow_Add_(Size,sizeof(devi_mc));
				}
				else
					Size=sizeof(devi_mc);

				MC=MemC_Alloc_Byte_(Size);
			}
			if(MC)
			{
				Acs_(GENERAL*,MC->ID)=ID;
				Acs_(MEMC_DT*,MC->Type)=DT;
				Acs_(address,MC->Unit)=DT->SizeType;
				Acs_(address,MC->Nums)=Number;
				Acs_(address,MC->LngS)=Length;

				if(DT->SizeType)
					if(Length)
					{
						Acs_(address,MC->AlignS)=_Devi_MC_Length_Padded_(_MemC_Overflow_Mul_(Length,DT->SizeType),Align);
						if(MC->AlignS)
							if(Number)
							{
								ADDRESS Size=_MemC_Overflow_Mul_(Number,MC->AlignS);

								Acs_(cl_mem,MC->BufT)=Devi_Create_Buffer_(Context,Size,byte_08,Error);
								Acs_(cl_mem*,MC->BufS)=(cl_mem*)(MC+1);
								if((*Error)==CL_SUCCESS)
								{
									const cl_mem _PL_ End=MC->BufS+Number;
									cl_mem *Ptr=(cl_mem*)(MC->BufS);
									address Ofs=0;

									while(Ptr<End)
									{
										*Ptr=Devi_Create_Buffer_Sub_(MC->BufT,Ofs,MC->AlignS,byte_08,Error);
										if((*Error)==CL_SUCCESS)
										{
											Ptr++;
											Ofs+=MC->AlignS;
										}
										else
											break;
									}
									if(Ptr<End)
									{
										for(Ptr--;Ptr>=MC->BufS;Ptr--)
											Devi_Delete_Buffer_(*Ptr);
										Devi_Delete_Buffer_(Acs_(cl_mem,MC->BufT));
										MemC_Deloc_(MC);
									}
								}
								else
									MemC_Deloc_(MC);
							}
							else
							{
								Acs_(cl_mem,MC->BufT)=NULL;
								Acs_(cl_mem,MC->BufS)=NULL;
							}
						else
						{
							MemC_Deloc_(MC);
							*Error=CL_INVALID_BUFFER_SIZE;
						}
					}
					else
						goto VACANT;
				else
				{
VACANT:
					Acs_(address,MC->AlignS)=0;
					Acs_(cl_mem,MC->BufT)=NULL;
					Acs_(cl_mem*,MC->BufS)=(Number)?(MemC_Clear_1D_(MC+1,Number,cl_mem)):(NULL);
				}
			}
			else
				*Error=CL_OUT_OF_HOST_MEMORY;
		}
		else
			MC=NULL;
	}
	else
	{
		MC=NULL;
		*Error=CL_INVALID_HOST_PTR;
	}

	return MC;
}
general Devi_MC_Delete_(devi_mc *_PL_ MC)
{
	if(*MC)
	{
		if((*MC)->BufS)
		{
			cl_mem *Ptr=(cl_mem*)((*MC)->BufS+(*MC)->Nums);

			for(Ptr--;Ptr>=(*MC)->BufS;Ptr--)
				Devi_Delete_Buffer_(*Ptr);
			Devi_Delete_Buffer_(Acs_(cl_mem,(*MC)->BufT));
		}
		MemC_Deloc_(*MC);
	}
}

integer Devi_MC_Change_(DEVI_MC _PL_ MC,MEMC_DT _PL_ DT)
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
#endif
#endif

#if(MemC_Fold_(Definition:MemClip Fused Functions))
static general *_MemC_VC_Access_(general *_R_ Jumper,ADDRESS *_R_ Access,ADDRESS Count)
{
	ADDRESS _PL_ End=Access+Count;

	for(;Access<End;Access++)
		Jumper=((general**)Jumper)[*Access];

	return Jumper;
}
memc_vc *MemC_VC_Create_(GENERAL _PL_ ID,MEMC_MC _PL_ MC,MEMC_MS _PL_ MS)
{
	memc_vc *VC;

	if(MC)
		if(MS)
			if(MS->Slot.V)
				if(MS->Slot.V[0]<MS->Nums)
					if(MS->Slot.V[0]>MC->Dims)
						goto ESCAPE;
					else
						if(_MemC_Array_Boundary_(MS->Slot.V+1,MC->LngND,MS->Slot.V[0]))
							VC=MemC_Alloc_Unit_(memc_vc);
						else
							goto ESCAPE;
				else
					goto ESCAPE;
			else
				goto ESCAPE;
		else
			goto ESCAPE;
	else
	{
ESCAPE:
		VC=NULL;
		goto RETURN;
	}
	if(VC)
	{
		Acs_(GENERAL*,VC->ID)=ID;
		Acs_(MEMC_DT*,VC->Type)=MC->Type;
		Acs_(address,VC->Unit)=MC->Unit;
		Acs_(address,VC->Dims)=MC->Dims-MS->Slot.V[0];
		if(VC->Dims)
		{
			if(VC->Dims>1)
			{
				Acs_(ADDRESS*,VC->LngND)=MC->LngND+MS->Slot.V[0];
				Acs_(address,VC->Lng1D)=_MemC_Array_Prod_(VC->LngND,VC->Dims);
			}
			else
			{
				Acs_(address,VC->Lng1D)=MC->LngND[MS->Slot.V[0]];
				Acs_(ADDRESS*,VC->LngND)=&(VC->Lng1D);
			}
			if(MC->AcsND)
				Acs_(general*,VC->Hidden)=_MemC_VC_Access_((general*)(MC->AcsND),MS->Slot.V+1,MS->Slot.V[0]);
			else
				Acs_(general*,VC->Hidden)=NULL;
		}
		else
		{
			Acs_(address,VC->Lng1D)=0;
			Acs_(address*,VC->LngND)=NULL;
			Acs_(general*,VC->Hidden)=NULL;
		}
		Acs_(address,VC->Domain.N)=0;
		Acs_(memc_df,VC->Domain.E)=MemCDomainHost;
	}
	else
		goto RETURN;
RETURN:
	return VC;
}
#ifdef __OPENCL_H
memc_vc *Devi_VC_Create_(GENERAL _PL_ ID,DEVI_MC _PL_ MC,ADDRESS Select,MEMC_MS _PL_ MS)
{
	memc_vc *VC;

	if(MC)
		if(Select<MC->Nums)
			if(MS)
				if(MS->Slot.V)
					if(MS->Slot.V[0]<MS->Nums)
						switch(MS->Slot.V[0])
						{
						default:
							if(MC->Unit)
								if(_MemC_Array_Non_Zero_(MS->Slot.V+1,MS->Slot.V[0]))
									if(_MemC_Overflow_Mul_(_MemC_Shape_Overflow_(MS->Slot.V+1,MS->Slot.V[0]),MC->Unit))
										goto ALLOC_EXTEN;
									else
										goto ESCAPE;
								else
									goto ALLOC_EXTEN;
							else
							{
ALLOC_EXTEN:;
								address Size=_MemC_Overflow_Mul_(MS->Slot.V[0],sizeof(address));

								if(Size)
								{
									Size=_MemC_Overflow_Add_(Size,sizeof(memc_vc));
									VC=MemC_Alloc_Byte_(Size);
									break;
								}
								else
									goto ESCAPE;
							}
						case 1:
							if(MC->Unit)
								if(MS->Slot.V[1])
								{
									ADDRESS Size=_MemC_Overflow_Mul_(MS->Slot.V[1],MC->Unit);

									if(Size)
										if(Size>MC->AlignS)
											goto ESCAPE;
										else
											goto ALLOC_SMALL;
									else
										goto ESCAPE;
								}
								else
									goto ALLOC_SMALL;
							else
								goto ALLOC_SMALL;
ALLOC_SMALL:
						case 0:
							VC=MemC_Alloc_Unit_(memc_vc);
						}
					else
						goto ESCAPE;
				else
					goto ESCAPE;
			else
				goto ESCAPE;
		else
			goto ESCAPE;
	else
	{
ESCAPE:
		VC=NULL;
		goto RETURN;
	}
	if(VC)
	{
		Acs_(GENERAL*,VC->ID)=ID;
		Acs_(MEMC_DT*,VC->Type)=MC->Type;
		Acs_(address,VC->Unit)=MC->Unit;
		Acs_(address,VC->Dims)=MS->Slot.V[0];
		if(VC->Dims)
		{
			if(VC->Dims>1)
			{
				Acs_(address*,VC->LngND)=(address*)(VC+1);
				if(MemC_Copy_1D_(MS->Slot.V+1,(address*)(VC->LngND),MS->Slot.V[0],address))
				{
					MemC_Deloc_(VC);
					goto RETURN;
				}
				else
					Acs_(address,VC->Lng1D)=_MemC_Array_Prod_(VC->LngND,VC->Dims);
			}
			else
			{
				Acs_(address,VC->Lng1D)=MS->Slot.V[1];
				Acs_(ADDRESS*,VC->LngND)=&(VC->Lng1D);
			}
			if(VC->Lng1D)
				Acs_(general*,VC->Hidden)=MC->BufS[Select];
			else
				Acs_(general*,VC->Hidden)=NULL;
		}
		else
		{
			Acs_(address,VC->Lng1D)=0;
			Acs_(address*,VC->LngND)=NULL;
			Acs_(general*,VC->Hidden)=NULL;
		}
		Acs_(address,VC->Domain.N)=0;
		Acs_(memc_df,VC->Domain.E)=MemCDomainDevice;
	}
	else
		goto RETURN;
RETURN:
	return VC;
}
#endif
general MemC_VC_Delete_(memc_vc *_PL_ VC)
{
	MemC_Deloc_(*VC);
}

address MemC_VC_Size_(MEMC_VC _PL_ VC)
{
	address Return;

	if(VC)
		switch(VC->Domain.E)
		{
		case MemCDomainHost:
			Return=sizeof(memc_vc);
			break;
		case MemCDomainDevice:
			Return=sizeof(memc_vc)+((VC->Dims>1)?(VC->Dims*sizeof(address)):(0));
			break;
		default:
			Return=0;
		}
	else
		Return=0;

	return Return;
}
integer MemC_VC_Change_(MEMC_VC _PL_ VC,MEMC_DT _PL_ DT)
{
	if(VC)
		if(DT)
			if(DT->SizeType==VC->Unit)
			{
				Acs_(MEMC_DT*,VC->Type)=DT;
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

static general *_MemC_VC_Direct_(general *Ptr,address Dig)
{
	while(Dig--)
		Ptr=*((general**)Ptr);

	return Ptr;
}
general *MemC_VC_Member_AcsND_(MEMC_VC _PL_ VC)
{
	return ((VC)?((VC->Domain.E==MemCDomainHost)?((general*)(VC->Hidden)):(NULL)):(NULL));
}
general *MemC_VC_Member_Acs1D_(MEMC_VC _PL_ VC)
{
	general *Return;
	
	if(VC)
		if(VC->Domain.E==MemCDomainHost)
			if(VC->Hidden)
				Return=_MemC_VC_Direct_((general*)(VC->Hidden),VC->Dims-1);
			else
				Return=NULL;
		else
			Return=NULL;
	else
		Return=NULL;

	return Return;
}
#ifdef __OPENCL_H
cl_mem Devi_VC_Member_BufS_(MEMC_VC _PL_ VC)
{
	return ((VC)?((VC->Domain.E==MemCDomainDevice)?((cl_mem)(VC->Hidden)):(NULL)):(NULL));
}
#endif

static address _Devi_VC_Offset_(ADDRESS *_R_ Access,ADDRESS *_R_ Length,ADDRESS Dig)
{
	ADDRESS _PL_ End=Access+Dig;
	address Offset=Access[0];

	for(;Access<End;Access++,Length++)
	{
		Offset*=Length[1];
		Offset+=Access[1];
	}

	return Offset;
}
integer MemC_VC_Access_(MEMC_VC _PL_ VC,MEMC_MS _PL_ MS)
{
	if(VC)
		if(MS)
			if(VC->Hidden)
				if(MS->Nums>VC->Dims)
				{
					ADDRESS _PL_ Access=MS->Slot.V+1;

					if(_MemC_Array_Boundary_(Access,VC->LngND,VC->Dims))
					{
						ADDRESS Dig=VC->Dims-1;

						switch(VC->Domain.E)
						{
						case MemCDomainHost:
							MS->Slot.P[0]=_MemC_VC_Access_((general*)(VC->Hidden),Access,Dig);
							MS->Slot.V[0]+=((MS->Slot.V[VC->Dims])*(VC->Unit));
							goto SUCCESS;
#ifdef __OPENCL_H
						case MemCDomainDevice:
							MS->Slot.V[0]=_Devi_VC_Offset_(Access,VC->LngND,Dig);
							goto SUCCESS;
#endif
						default:
							goto FAILURE;
						}
					}
					else
						goto FAILURE;
				}
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

static integer _MemC_VC_Copy_Bound_(ADDRESS *_R_ Copy,ADDRESS *_R_ Offset,ADDRESS *_R_ Bound,ADDRESS Dims)
{
	ADDRESS _PL_ End=Copy+Dims;
	address Temp;

	for(;Copy<End;Copy++,Offset++,Bound++)
	{
		Temp=(*Copy)+(*Offset);
		if(Temp<(*Copy))
			break;
		if(Temp>(*Bound))
			break;
	}

	return (Copy==End);
}
static integer _MemC_VC_Copy_Check_(ADDRESS _PL_ OffsetData,ADDRESS _PL_ LengthData,ADDRESS _PL_ LengthCopy,ADDRESS JumpData,ADDRESS DimsData,ADDRESS DimsCopy)
{
	integer Return;

	if(DimsCopy>DimsData)
		Return=0;
	else
		if(_MemC_Array_Boundary_(OffsetData,LengthData,JumpData))
			if(_MemC_VC_Copy_Bound_(LengthCopy,OffsetData+JumpData,LengthData+JumpData,DimsCopy))
				Return=1;
			else
				Return=0;
		else
			Return=0;

	return Return;
}
static general _MemC_VC_Copy_New_Size_(address _PL_ LengthNew,address _PL_ OffsetNew,ADDRESS *_R_ OffsetData,ADDRESS *_R_ LengthData,ADDRESS JumpData,ADDRESS DimsCopy)
{
	{
		ADDRESS _PL_ End=OffsetData+JumpData;

		{
			LengthNew[0]=LengthData[0];
			OffsetNew[0]=OffsetData[0];
		}
		for(;OffsetData<End;OffsetData++,LengthData++)
		{
			LengthNew[0]*=LengthData[1];
			OffsetNew[0]*=LengthData[1];
			OffsetNew[0]+=OffsetData[1];
		}
	}
	{
		ADDRESS Rest=DimsCopy-1;

		MemC_Copy_1D_(LengthData+1,LengthNew+1,Rest,address);
		MemC_Copy_1D_(OffsetData+1,OffsetNew+1,Rest,address);
	}
}
integer MemC_VC_Init_(general _PL_ Queue,MEMC_VC _PL_ VC)
{
	if(VC)
		if(VC->Hidden)
			switch(VC->Domain.E)
			{
			case MemCDomainHost:
				MemC_Clear_Byte_(_MemC_VC_Direct_((general*)(VC->Hidden),VC->Dims-1),(VC->Lng1D)*(VC->Unit));
				goto SUCCESS;
#ifdef __OPENCL_H
			case MemCDomainDevice:
				if(Devi_Init_(Queue,(cl_mem)(VC->Hidden),ConstantZero,0,(VC->Lng1D)*(VC->Unit),byte_08)==CL_SUCCESS)
					goto SUCCESS;
				else
					goto FAILURE;
#else
				MemC_Mute_(Queue);
#endif
			default:
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
integer MemC_VC_Copy_(general _PL_ Queue,MEMC_VC _PL_ Source,MEMC_VC _PL_ Target,MEMC_MS _PL_ Copy)
{
	if(Source)
		if(Target)
			if(Source->Unit==Target->Unit);
			else
				goto FAILURE;
		else
			goto FAILURE;
	else
		goto FAILURE;

	if(Copy)
		if(Copy->Slot.V)
		{
			ADDRESS DimC=Copy->Slot.V[0];
			ADDRESS _PL_ LngC=Copy->Slot.V+1;
			ADDRESS *OfsS=LngC+DimC;
			ADDRESS *OfsT=OfsS+Source->Dims;

			{
				ADDRESS _PL_ End=Copy->Slot.V+Copy->Nums;
				ADDRESS _PL_ Temp=OfsT+Target->Dims;

				if(LngC<Copy->Slot.V)
					goto FAILURE;
				if(OfsS<LngC)
					goto FAILURE;
				if(OfsT<OfsS)
					goto FAILURE;
				if(Temp<OfsT)
					goto FAILURE;
				if(Temp>End)
					goto FAILURE;
			}
			if(DimC)
			{
				ADDRESS PreS=Source->Dims-DimC;
				ADDRESS PreT=Target->Dims-DimC;
				ADDRESS *LngS=Source->LngND;
				ADDRESS *LngT=Target->LngND;

				if(!_MemC_VC_Copy_Check_(OfsS,LngS,LngC,PreS,Source->Dims,DimC))
					goto FAILURE;
				if(!_MemC_VC_Copy_Check_(OfsT,LngT,LngC,PreT,Target->Dims,DimC))
					goto FAILURE;
				if(!_MemC_Array_Non_Zero_(LngC,DimC))
					goto SUCCESS;
				if(Source->Hidden)
					if(Target->Hidden)
					{
						general *MemS;
						general *MemT;
#ifdef __OPENCL_H
						integer Flag=0x0;
#else
						MemC_Mute_(Queue);
#endif
						switch(Source->Domain.E)
						{
						case MemCDomainHost:
							MemS=_MemC_VC_Access_((general*)(Source->Hidden),OfsS,PreS);
							MemS=_MemC_VC_Direct_(MemS,DimC-1);
							break;
#ifdef __OPENCL_H
						case MemCDomainDevice:
							MemS=(general*)(Source->Hidden);
							Flag|=0x2;
							break;
#endif
						default:
							goto FAILURE;
						}
						switch(Target->Domain.E)
						{
						case MemCDomainHost:
							MemT=_MemC_VC_Access_((general*)(Target->Hidden),OfsT,PreT);
							MemT=_MemC_VC_Direct_(MemT,DimC-1);
							break;
#ifdef __OPENCL_H
						case MemCDomainDevice:
							MemT=(general*)(Target->Hidden);
							Flag|=0x1;
							break;
#endif
						default:
							goto FAILURE;
						}
#ifdef __OPENCL_H
						if(Flag)
							if(DimC>Devi_Copy_Max_Dimension)
								goto FAILURE;
							else
							{
								address SizeNew[Devi_Copy_Max_Dimension<<2];

								if(Flag&0x2)
									if(PreS)
									{
										address _PL_ LngSNew=SizeNew;
										address _PL_ OfsSNew=LngSNew+Devi_Copy_Max_Dimension;

										_MemC_VC_Copy_New_Size_(LngSNew,OfsSNew,OfsS,LngS,PreS,DimC);
										OfsS=OfsSNew;
										LngS=LngSNew;
									}
								if(Flag&0x1)
									if(PreT)
									{
										address _PL_ LngTNew=SizeNew+(Devi_Copy_Max_Dimension<<1);
										address _PL_ OfsTNew=LngTNew+Devi_Copy_Max_Dimension;

										_MemC_VC_Copy_New_Size_(LngTNew,OfsTNew,OfsT,LngT,PreT,DimC);
										OfsT=OfsTNew;
										LngT=LngTNew;
									}
								if(_Devi_Copy_(Queue,MemS,MemT,OfsS,OfsT,LngC,LngS,LngT,(cl_uint)DimC,Source->Unit,(devi_cf)Flag)==CL_SUCCESS)
									goto SUCCESS;
								else
									goto FAILURE;
							}
						else
#endif
						{
							if(_MemC_Copy_(MemS,MemT,OfsS+PreS,OfsT+PreT,LngC,LngS+PreS,LngT+PreT,DimC,Source->Unit))
								goto FAILURE;
							else
								goto SUCCESS;
						}
					}
					else
						goto FAILURE;
				else
					if(Target->Hidden)
						goto FAILURE;
					else
						goto SUCCESS;
			}
			else
				goto SUCCESS;
		}
		else
			goto FAILURE;
	else
		if(Source->Dims==Target->Dims)
			if(Source->Dims)
				if(MemC_Compare_1D_(Source->LngND,Target->LngND,Source->Dims,address))
					goto FAILURE;
				else
					if(Source->Hidden)
						if(Target->Hidden)
						{
							ADDRESS Dig=Source->Dims-1;
							general *MemoryS;
							general *MemoryT;
#ifdef __OPENCL_H
							integer Flag=0x0;
#else
							MemC_Mute_(Queue);
#endif
							switch(Source->Domain.E)
							{
							case MemCDomainHost:
								MemoryS=_MemC_VC_Direct_((general*)(Source->Hidden),Dig);
								break;
#ifdef __OPENCL_H
							case MemCDomainDevice:
								MemoryS=(general*)(Source->Hidden);
								Flag|=0x2;
								break;
#endif
							default:
								goto FAILURE;
							}
							switch(Target->Domain.E)
							{
							case MemCDomainHost:
								MemoryT=_MemC_VC_Direct_((general*)(Target->Hidden),Dig);
								break;
#ifdef __OPENCL_H
							case MemCDomainDevice:
								MemoryT=(general*)(Target->Hidden);
								Flag|=0x1;
								break;
#endif
							default:
								goto FAILURE;
							}
#ifdef __OPENCL_H
							if(Flag)
								if(_Devi_Copy_1D_(Queue,MemoryS,MemoryT,0,0,Source->Lng1D,Source->Unit,(devi_cf)Flag)==CL_SUCCESS)
									goto SUCCESS;
								else
									goto FAILURE;
							else
#endif
							{
								if(MemC_Copy_Byte_(MemoryS,MemoryT,(Source->Lng1D)*(Source->Unit)))
									goto FAILURE;
								else
									goto SUCCESS;
							}
						}
						else
							goto FAILURE;
					else
						if(Target->Hidden)
							goto FAILURE;
						else
							goto SUCCESS;
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
