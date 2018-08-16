#include "memclip.h"

#if(MemC_Fold_(Definition:Global Constants))
#define _MemC_DT_Parse_(Enum,Size) {.Scope=IdiomVersion,.Index=(Enum),.Flag=0,.SizeType=(Size),.SizeName=sizeof(IdiomType[Enum]),.Name=IdiomType[Enum],.Link=NULL,.Meta=NULL}

static const char IdiomVersion[16]="Date:2018.08.16";
static const char IdiomType[4][8]={"none\0\0\0","byte\0\0\0","integer","address"};
static const size_t ConstantZero[MemC_Copy_Max_Dimension]={0};

static MEMC_DT TableType[4]=
{
	_MemC_DT_Parse_(MemCTypeNone,0),
	_MemC_DT_Parse_(MemCTypeByte,sizeof(char)),
	_MemC_DT_Parse_(MemCTypeInteger,sizeof(int)),
	_MemC_DT_Parse_(MemCTypeAddress,sizeof(size_t))
};
static MEMC_DT _PL_ AddressType[MemCTypes]={TableType+MemCTypeNone,TableType+MemCTypeByte,TableType+MemCTypeInteger,TableType+MemCTypeAddress};

const char _PL_ MemClip=IdiomVersion;
const void _PL_ MemCrux=&MemCrux;
MEMC_DT _PL_ _PL_ MemCType=AddressType;

#undef _MemC_DT_Parse_
#endif

#if(MemC_Fold_(Definition:Memory Functions))
#if(MemC_Fold_(Part:Memory Set Handle))
static size_t _MemC_Array_Prod_(const size_t *_R_ Ptr,const size_t Count)
{
	const size_t _PL_ End=Ptr+Count;
	size_t Length=1;

	for(;Ptr<End;Ptr++)
		Length*=(*Ptr);

	return Length;
}
static int _MemC_Array_Non_Zero_(const size_t *_R_ Ptr,const size_t Nums)
{
	const size_t _PL_ End=Ptr+Nums;

	while(Ptr<End)
		if(*Ptr)
			Ptr++;
		else
			break;

	return (Ptr==End);
}
static int _MemC_Array_All_Zero_(const size_t *_R_ Ptr,const size_t Nums)
{
	const size_t _PL_ End=Ptr+Nums;

	while(Ptr<End)
		if(*Ptr)
			break;
		else
			Ptr++;

	return (Ptr==End);
}
static int _MemC_Array_Boundary_(const size_t *_R_ Access,const size_t *_R_ Bound,const size_t Count)
{
	const size_t _PL_ End=Access+Count;

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
int MemC_Check_(const void _PL_ *Memory,const size_t Sets)
{
	int Success;

	if(Memory)
		Success=_MemC_Array_Non_Zero_((size_t*)Memory,Sets);
	else
		Success=0;

	return Success;
}
void MemC_Deloc_Set_(void **Memory,const size_t Sets)
{
	if(Memory)
	{
		const void _PL_ _PL_ End=Memory+Sets;

		for(;Memory<End;Memory++)
			MemC_Deloc_(*Memory);
	}
}
#endif
#if(MemC_Fold_(Part:ND Array Memory Allocation))
static size_t _MemC_Origin_(const size_t Number,const size_t SizeElement)
{
	volatile size_t New=Number*SizeElement;
	
	if((New/SizeElement)!=Number)
		New=0;

	return New;
}
static size_t _MemC_Bigger_(const size_t Number,const size_t Old)
{
	volatile size_t New=sizeof(void*)+Old;

	if(New>Old)
	{
		volatile size_t Temporary=Number*New;

		if((Temporary/New)==Number)
			New=Temporary;
		else
			New=0;
	}
	else
		New=0;

	return New;
}
static void **_MemC_Assign_(void **High,const size_t NumberHigh,const size_t SizeStep)
{
	void **End=High+NumberHigh;
	char *PtrL=(char*)End;

	for(;High<End;High++,PtrL+=SizeStep)
		(*High)=PtrL;

	return End;
}
static void *_MemC_Assign_Loop_(void **PtrM,const size_t _PL_ Size,const size_t NumberDimension,const size_t SizeElement)
{
	const size_t _PL_ End=Size+(NumberDimension-1);
	const size_t *_R_ PtrS=Size;
	size_t Temp=PtrS[0];

	for(PtrS++;PtrS<End;PtrS++)
	{
		PtrM=_MemC_Assign_(PtrM,Temp,(*PtrS)*sizeof(size_t));
		Temp*=(*PtrS);
	}
	PtrM=_MemC_Assign_(PtrM,Temp,(*PtrS)*SizeElement);

	return PtrM;
}
void *MemC_Alloc_(const size_t _PL_ Size,const size_t NumberDimension,const size_t SizeElement)
{
	void *Memory=NULL;

	if(Size)
		if(NumberDimension)
			if(SizeElement)
			{
				const size_t _PL_ End=Size+(NumberDimension-1);
				const size_t *PtrS=End;
				size_t Temporary=_MemC_Origin_(*PtrS,SizeElement);

				for(PtrS--;PtrS>=Size;PtrS--)
					if(Temporary)
						Temporary=_MemC_Bigger_(*PtrS,Temporary);
					else
						break;

				if(Temporary)
				{
					Memory=Byte_Alloc_(Temporary);
					if(Memory)
						if(NumberDimension>1)
							_MemC_Assign_Loop_(Memory,Size,NumberDimension,SizeElement);
				}
			}

	return Memory;
}
#endif
#if(MemC_Fold_(Part:1D, 2D, 3D, and 4D Array Memory Allocations))
static size_t _MemC_Overflow_Add_(const size_t A,const size_t B)
{
	size_t C=A+B;

	if(C<A)
		C=0;
	else
		if(C<B)
			C=0;

	return C;
}
static size_t _MemC_Overflow_Mul_(const size_t A,const size_t B)
{
	size_t C[2];

	C[0]=A*B;
	if(C[0])
	{
		C[1]=C[0]/B;
		if(C[1]!=A)
			C[0]=0;
	}

	return C[0];
}
void *Byte_Alloc_(const size_t S)
{
	const size_t T=sizeof(size_t);
	const size_t N=_MemC_Overflow_Mul_((S+T-1)/T,T);
	void _PL_ Memory=(N)?(malloc(N)):(NULL);

	return Memory;
}
void *_Line_Alloc_(const size_t Z,const size_t SizeElement)
{
	size_t BufferSize[1];

	BufferSize[0]=Z;

	return MemC_Alloc_(BufferSize,1,SizeElement);
}
void *_Rect_Alloc_(const size_t Y,const size_t Z,const size_t SizeElement)
{
	size_t BufferSize[2];

	BufferSize[0]=Y;
	BufferSize[1]=Z;

	return MemC_Alloc_(BufferSize,2,SizeElement);
}
void *_Cube_Alloc_(const size_t X,const size_t Y,const size_t Z,const size_t SizeElement)
{
	size_t BufferSize[3];

	BufferSize[0]=X;
	BufferSize[1]=Y;
	BufferSize[2]=Z;

	return MemC_Alloc_(BufferSize,3,SizeElement);
}
void *_Tess_Alloc_(const size_t W,const size_t X,const size_t Y,const size_t Z,const size_t SizeElement)
{
	size_t BufferSize[4];

	BufferSize[0]=W;
	BufferSize[1]=X;
	BufferSize[2]=Y;
	BufferSize[3]=Z;

	return MemC_Alloc_(BufferSize,4,SizeElement);
}
#endif
#if(MemC_Fold_(Part:1D Array Trivials))
static size_t _MemC_Safe_2_(size_t Num)
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
errno_t _Line_Init_(void _PL_ Memory,const void _PL_ Tile,const size_t NumberElement,const size_t SizeElement)
{
	errno_t ErrorCode;

	if(_MemC_Origin_(NumberElement,SizeElement))
	{
		const size_t Safe=_MemC_Safe_2_(NumberElement);
		const char _PL_ End=((char*)Memory)+(Safe*SizeElement);
		char *Ptr=(char*)Memory;
		size_t Copy=SizeElement;

		ErrorCode=Byte_Copy_(Tile,Ptr,Copy);
		if(!ErrorCode)
		{
			for(Ptr+=Copy;Ptr<End;Copy<<=1)
			{
				ErrorCode=Byte_Copy_(Memory,Ptr,Copy);
				if(ErrorCode)
					break;
				else
					Ptr+=Copy;
			}
			if(!ErrorCode)
			{
				Copy=Safe^NumberElement;
				Copy*=SizeElement;
				ErrorCode=Byte_Copy_(Memory,Ptr,Copy);
			}
		}
	}
	else
		ErrorCode=EINVAL;

	return ErrorCode;
}
errno_t _Line_Pick_(const void _PL_ Input,void _PL_ Output,const size_t NumberChannel,const size_t NumberElement,const size_t SizeElement)
{
	const size_t Step=NumberChannel*SizeElement;
	const char _PL_ End=((char*)Input)+(Step*NumberElement);
	const char *PtrI=(char*)Input;
	char *PtrO=(char*)Output;
	errno_t ErrorCode=EINVAL;
	
	for(;PtrI<End;PtrI+=Step,PtrO+=SizeElement)
	{
		ErrorCode=Byte_Copy_(PtrI,PtrO,SizeElement);
		if(ErrorCode)
			break;
	}

	return ErrorCode;
}
errno_t _Line_Fill_(const void _PL_ Input,void _PL_ Output,const size_t NumberChannel,const size_t NumberElement,const size_t SizeElement)
{
	const size_t Step=NumberChannel*SizeElement;
	const char _PL_ End=((char*)Input)+(SizeElement*NumberElement);
	const char *PtrI=(char*)Input;
	char *PtrO=(char*)Output;
	errno_t ErrorCode=EINVAL;

	for(;PtrI<End;PtrI+=SizeElement,PtrO+=Step)
	{
		ErrorCode=Byte_Copy_(PtrI,PtrO,SizeElement);
		if(ErrorCode)
			break;
	}

	return ErrorCode;
}
#endif
#if(MemC_Fold_(Part:ND Array Data Copy))
static void _MemC_Jump_Offset_(size_t _PL_ Jump,const size_t _PL_ Shape,const size_t Dimension,const size_t Bytes)
{
	const size_t *_R_ PointerS=Shape+(Dimension-2);
	size_t *_R_ PointerJ=Jump+(Dimension-1);

	PointerJ[0]=Bytes;
	for(PointerJ--;PointerJ>=Jump;PointerS--,PointerJ--)
		PointerJ[0]=PointerS[+1]*PointerJ[+1];
}
static errno_t _MemC_Copy_2D_(const char _PL_ MemoryS,char _PL_ MemoryT,const size_t _PL_ JumpS,const size_t _PL_ JumpT,const size_t _PL_ OriginS,const size_t _PL_ OriginT,const size_t _PL_ Length,const size_t Bytes)
{
	const size_t Copy=Length[1]*Bytes;
	const char *End=MemoryS+((JumpS[0]*OriginS[0])+(JumpS[1]*OriginS[1]));
	const char *PointerS=End;
	char *PointerT=MemoryT+((JumpT[0]*OriginT[0])+(JumpT[1]*OriginT[1]));
	errno_t ErrorCode=EINVAL;

	for(End+=(JumpS[0]*Length[0]);PointerS<End;PointerS+=JumpS[0],PointerT+=JumpT[0])
	{
		ErrorCode=Byte_Copy_(PointerS,PointerT,Copy);
		if(ErrorCode)
			break;
	}

	return ErrorCode;
}
static errno_t _MemC_Copy_Recursive_(const char _PL_ MemoryS,char _PL_ MemoryT,const size_t _PL_ JumpS,const size_t _PL_ JumpT,const size_t _PL_ OriginS,const size_t _PL_ OriginT,const size_t _PL_ Length,const size_t Dimensions,const size_t Bytes)
{
	errno_t ErrorCode=EINVAL;

	if(Dimensions>2)
	{
		const size_t NextDimensions=Dimensions-1;
		const size_t _PL_ NextJumpS=JumpS+1;
		const size_t _PL_ NextJumpT=JumpT+1;
		const size_t _PL_ NextOriginS=OriginS+1;
		const size_t _PL_ NextOriginT=OriginT+1;
		const size_t _PL_ NextLength=Length+1;
		const char *End=MemoryS+(JumpS[0]*OriginS[0]);
		const char *PointerS=End;
		char *PointerT=MemoryT+(JumpT[0]*OriginT[0]);

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
static int _MemC_Copy_Check_Bound_(const size_t _PL_ Shape,const size_t _PL_ Offset,const size_t _PL_ Length,const size_t Dimensions)
{
	size_t Index;
	size_t Temp;

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
errno_t _MemC_Copy_(const void _PL_ MemoryS,void _PL_ MemoryT,const size_t _PL_ OriginS,const size_t _PL_ OriginT,const size_t _PL_ Length,const size_t _PL_ ShapeS,const size_t _PL_ ShapeT,const size_t Dimensions,const size_t Bytes)
{
	const size_t _PL_ OffsetS=(OriginS)?(OriginS):(ConstantZero);
	const size_t _PL_ OffsetT=(OriginT)?(OriginT):(ConstantZero);
	errno_t ErrorCode;

	if(_MemC_Copy_Check_Bound_(ShapeS,OffsetS,Length,Dimensions)&&_MemC_Copy_Check_Bound_(ShapeT,OffsetT,Length,Dimensions))
		switch(Dimensions)
		{
		case 0:
			ErrorCode=0;
			break;
		case 1:
			{
				const size_t Copy=Length[0]*Bytes;
				
				if(Copy)
					ErrorCode=Byte_Copy_(((const char*)MemoryS)+(OffsetS[0]*Bytes),((char*)MemoryT)+(OffsetT[0]*Bytes),Copy);
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
						size_t JumpS[MemC_Copy_Max_Dimension];
						size_t JumpT[MemC_Copy_Max_Dimension];

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
static int _MemC_Reform_Valid_(const size_t *_R_ Map,const size_t Dims)
{
	size_t Table[MemC_Copy_Max_Dimension]={0};
	const size_t _PL_ End=Map+Dims;

	while(Map<End)
		if((*Map)<Dims)
		{
			Table[*Map]=(size_t)FULL;
			Map++;
		}
		else
			break;

	return ((Map==End)?(_MemC_Array_Non_Zero_(Table,Dims)):(0));
}
static void _MemC_Reform_Short_(const size_t _PL_ Shape,const size_t _PL_ Map,size_t _PL_ Dims,size_t _PL_ Bytes)
{
	size_t Temp;

	for(Temp=(*Dims)-1;Temp;Temp--)
		if(Map[Temp]==Temp)
		{
			(*Bytes)*=Shape[Temp];
			(*Dims)=Temp;
		}
		else
			break;
}
static void _MemC_Reform_Merge_(size_t _PL_ Shape,size_t _PL_ Map,size_t _PL_ Dims)
{
	const size_t *End=Map+(*Dims);
	const size_t *Last=End-1;
	size_t *MapA;
	size_t *MapB;
	size_t *MapC;
	size_t *ShpA;
	size_t *ShpB;
	size_t *ShpC;
	size_t Pull;

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
static errno_t _MemC_Reform_Order_(const char _PL_ Source,char _PL_ Target,const size_t _PL_ Shape,const size_t _PL_ Map,const size_t Total,const size_t Dims,const size_t Bytes)
{
	size_t Jump[MemC_Copy_Max_Dimension];
	const size_t Last=Dims-1;
	size_t Prod;
	size_t IdxS;
	size_t IdxT;
	size_t IdxJ;
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
		ErrorCode=Byte_Copy_(Source+(IdxS*Bytes),Target+(IdxT*Bytes),Bytes);
		if(ErrorCode)
			break;
	}

	return ErrorCode;
}
errno_t _MemC_Reform_(const void _PL_ MemoryS,void _PL_ MemoryT,const size_t _PL_ ShapeS,const size_t _PL_ MapT,size_t Dimensions,size_t Bytes)
{
	errno_t ErrorCode;

	if(Dimensions)
	{
		_MemC_Reform_Short_(ShapeS,MapT,&Dimensions,&Bytes);
		if(Dimensions>1)
			if(Dimensions<MemC_Copy_Max_Dimension)
				if(_MemC_Reform_Valid_(MapT,Dimensions))
				{
					const size_t Total=_MemC_Array_Prod_(ShapeS,Dimensions);

					if(Total)
					{
						size_t ShapeSNew[MemC_Copy_Max_Dimension];
						size_t MapTNew[MemC_Copy_Max_Dimension];

						ErrorCode=Line_Copy_(ShapeS,ShapeSNew,Dimensions,size_t);
						if(ErrorCode)
							goto ESCAPE;

						ErrorCode=Line_Copy_(MapT,MapTNew,Dimensions,size_t);
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
				const size_t Copy=ShapeS[0]*Bytes;

				if(Copy)
					ErrorCode=Byte_Copy_(MemoryS,MemoryT,Copy);
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
static size_t _MemC_Sort_Lng_2_(const size_t Length)
{
	size_t Temp=1;

	Temp=~Temp;
	Temp&=Length;

	return Temp;
}
static void _MemC_Sort_Bound_(size_t _PL_ Jump,const void _PL_ **Bound)
{
	Bound[2]=Bound[1]+Jump[0];
	if(Bound[2]>Bound[3])
		Bound[2]=Bound[3];

	Jump[1]=Bound[2]-Bound[1];
	Jump[2]=Jump[0]+Jump[1];
	Jump[3]=Jump[1]-1;
}
static void _MemC_Sort_Ord_2_(int(_PL_ Comp_)(const void _PL_,const void _PL_),const void **Ptr,size_t *Idx,const size_t Length)
{
	const void _PL_ _PL_ End=Ptr+_MemC_Sort_Lng_2_(Length);
	const void *Temp;

	if(Idx)
		for(;Ptr<End;Ptr+=2,Idx+=2)
		{
			if(Comp_(Ptr[0],Ptr[1]))
			{
				Temp=Ptr[0];
				Ptr[0]=Ptr[1];
				Ptr[1]=Temp;

				Temp=(void*)(Idx[0]);
				Idx[0]=Idx[1];
				Idx[1]=(size_t)Temp;
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
static void _MemC_Sort_Ord_A_(int(_PL_ Comp_)(const void _PL_,const void _PL_),size_t *PtrT,const void _PL_ *PtrA,const void _PL_ _PL_ StartB,const void _PL_ _PL_ EndB)
{
	const void _PL_ *PtrB=StartB;

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
static void _MemC_Sort_Ord_B_(int(_PL_ Comp_)(const void _PL_,const void _PL_),size_t *PtrT,const void _PL_ *PtrB,const void _PL_ _PL_ StartA,const void _PL_ _PL_ StartB)
{
	const void _PL_ *PtrA=StartB-1;

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
static errno_t _MemC_Sort_Table_(size_t *IdxO,size_t *IdxA,const size_t *PtrT,const size_t _PL_ MatchB,const size_t Copy,const size_t Step)
{
	errno_t Error=Line_Copy_(IdxO,IdxA,Copy,size_t);

	if(!Error)
	{
		for(;IdxO<MatchB;IdxA++,IdxO++,PtrT++)
			IdxO[PtrT[0]]=IdxA[0];
		for(IdxA+=Step,IdxO+=Step,PtrT+=Step;IdxO>=MatchB;IdxA--,IdxO--,PtrT--)
			IdxO[PtrT[0]]=IdxA[0];
	}

	return Error;
}
errno_t MemC_Sort_(int(_PL_ Comp_)(const void _PL_,const void _PL_),const void *_PL_ Refer,size_t _PL_ Index,size_t _PL_ Buffer,const size_t Length)
{
	errno_t ErrorCode=0;

	if(Length)
	{
		const void _PL_ *Bound[4];
		size_t Jump[4];
		size_t _PL_ Table=Buffer;
		size_t _PL_ Value=Table+Length;

		_MemC_Sort_Ord_2_(Comp_,Refer,Index,Length);
		if(Index)
		{
			size_t *Match;

			for(Jump[0]=2,Bound[3]=Refer+Length;Jump[0]<Length;Jump[0]<<=1)
				for(Bound[0]=Refer,Bound[1]=Refer+Jump[0],Match=Index;Bound[1]<Bound[3];Bound[0]=Bound[2],Bound[1]=Bound[2]+Jump[1],Match+=Jump[2])
				{
					_MemC_Sort_Bound_(Jump,Bound);
					_MemC_Sort_Ord_A_(Comp_,Table,Bound[0],Bound[1],Bound[2]);
					_MemC_Sort_Ord_B_(Comp_,Table+(Jump[2]-1),Bound[2]-1,Bound[0],Bound[1]);

					ErrorCode=_MemC_Sort_Table_((size_t*)(Bound[0]),Value,Table,(size_t*)(Bound[1]),Jump[2],Jump[3]);
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

					ErrorCode=_MemC_Sort_Table_((size_t*)(Bound[0]),Value,Table,(size_t*)(Bound[1]),Jump[2],Jump[3]);
					if(ErrorCode)
						goto ESCAPE;
				}
	}
ESCAPE:
	return ErrorCode;
}
#endif
#if(MemC_Fold_(Part:Others))
void MemC_Void_(void)
{
}
void MemC_Self_(size_t *_R_ Table,const size_t Length,const int Mode)
{
	if(Mode)
	{
		const size_t _PL_ End=Table+Length;

		for(;Table<End;Table++)
			(*Table)=(size_t)Table;
	}
	else
	{
		size_t Idx;

		for(Idx=0;Idx<Length;Idx++)
			Table[Idx]=Idx;
	}
}
size_t _Line_Assign_(void _PL_ Indexer,const void _PL_ Indexed,const size_t Interval,const size_t Indices,const size_t TypeSize,const int Mode)
{
	size_t Sum;

	if(Indices)
	{
		const char _PL_ _PL_ End=(char**)Indexer+Indices;
		char **_R_ PointerO=Indexer;

		{
			PointerO[0]=(char*)Indexed;
			PointerO++;
		}
		if(Mode)
		{
			const size_t *_R_ PointerS=(size_t*)Interval;

			for(;PointerO<End;PointerO++,PointerS++)
				PointerO[0]=PointerO[-1]+(PointerS[0]*TypeSize);

			Sum=(PointerO[-1]-(char*)Indexed)+(PointerS[0]*TypeSize);
		}
		else
		{
			const size_t Step=Interval*TypeSize;

			for(;PointerO<End;PointerO++)
				PointerO[0]=PointerO[-1]+Step;

			Sum=Step*Indices;
		}
	}
	else
		Sum=0;

	return Sum;
}
size_t _MemC_Switch_(const void _PL_ Key,const void _PL_ _PL_ ReferTable,const size_t *ReferLength,const size_t KeyLength,const size_t Refers,const size_t TypeSize)
{
	const size_t ByteSize=KeyLength*TypeSize;
	size_t Index=0;

	Index=~Index;
	if(ByteSize)
	{
		const void _PL_ _PL_ End=ReferTable+Refers;
		const void _PL_ *PointerT=ReferTable;

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
memc_ms *MemC_MS_Create_(const void _PL_ ID,const size_t Slots)
{
	memc_ms *MS;

	if(Slots)
	{
		size_t Size=_MemC_Overflow_Mul_(Slots,sizeof(void*));

		if(Size)
		{
			Size=_MemC_Overflow_Add_(Size,sizeof(memc_ms));
			if(Size)
			{
				MS=Byte_Alloc_(Size);
				if(MS)
				{
					Acs_(const void*,MS->ID)=ID;
					Acs_(MEMC_DT*,MS->Type)=MemCType[MemCTypeAddress];
					Acs_(size_t,MS->Nums)=Slots;
					Acs_(size_t*,MS->Slot.V)=Line_Clear_(MS+1,Slots,size_t);
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
		MS=Unit_Alloc_(memc_ms);
		if(MS)
		{
			Acs_(const void*,MS->ID)=ID;
			Acs_(MEMC_DT*,MS->Type)=MemCType[MemCTypeAddress];
			Acs_(size_t,MS->Nums)=0;
			Acs_(size_t*,MS->Slot.V)=NULL;
		}
	}

	return MS;
}
void MemC_MS_Delete_(memc_ms *_PL_ MS)
{
	MemC_Deloc_(*MS);
}

size_t MemC_MS_Size_(MEMC_MS _PL_ MS)
{
	return (MS)?(sizeof(memc_ms)+MemC_Size_(size_t,MS->Nums)):(0);
}
int MemC_MS_Change_(MEMC_MS _PL_ MS,MEMC_DT _PL_ DT)
{
	if(MS)
		if(DT)
			if(DT->SizeType==sizeof(size_t))
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
int MemC_MS_Init_(MEMC_MS _PL_ MS)
{
	if(MS)
	{
		if(MS->Nums)
			Line_Clear_(MS->Slot.V,MS->Nums,size_t);
		goto SUCCESS;
	}
	else
		goto FAILURE;
FAILURE:
	return 0;
SUCCESS:
	return 1;
}
int MemC_MS_Null_(MEMC_MS _PL_ MS,const int Mode)
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

int MemC_MS_Joke_(MEMC_MS _PL_ MS)
{
	if(MS)
		if(MS->Nums)
		{
			size_t Table[8]={1,2,3,4,5,6,7,8};
			size_t Temp[2];
			size_t *Mover=Table-7;
			void **Pointer=MS->Slot.P;
			size_t Count=MS->Nums;

			for(Count--,Temp[0]=(size_t)Pointer/sizeof(size_t);Count>7;Count--,Pointer=(*Pointer))
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
int MemC_MS_Oops_(MEMC_MS _PL_ MS)
{
	if(MS)
		if(MS->Nums)
		{
			const void _PL_ Start=MS->Slot.P;
			const void _PL_ End=MS->Slot.P+MS->Nums;
			const void _PL_ *Pointer=MS->Slot.P;
			size_t Count=MS->Nums;

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
static size_t _MemC_Shape_Overflow_(const size_t _PL_ Shape,const size_t Dims)
{
	const size_t _PL_ End=Shape+Dims;
	const size_t *_R_ Ptr=Shape;
	size_t Total=1;

	for(;Ptr<End;Ptr++)
		Total=_MemC_Overflow_Mul_(Total,*Ptr);

	return Total;
}
static size_t _MemC_Space_Required_(const size_t _PL_ Shape,const size_t Dims,const size_t SizeType)
{
	size_t Size[2];

	if(Dims>1)
	{
		const size_t _PL_ Last=Shape+(Dims-1);
		const size_t *_R_ Ptr=Shape;

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
				Size[1]=_MemC_Overflow_Mul_(Size[1],sizeof(size_t));
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
memc_mc *MemC_MC_Create_(const void _PL_ ID,MEMC_MS _PL_ MS,MEMC_DT _PL_ DT)
{
	memc_mc *MC;
	
	if(DT)
		if(MS)
			if(MS->Slot.V)
				if(MS->Slot.V[0]<MS->Nums)
					if(MS->Slot.V[0])
					{
						const size_t Dimensions=MS->Slot.V[0];
						const size_t _PL_ Shape=MS->Slot.V+1;
						size_t Lng1D;
						int Flag=(DT->SizeType)?(0x1):(0x0);

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
								size_t Size=_MemC_Overflow_Mul_(Dimensions,sizeof(size_t));

								if(Size)
								{
									Size=_MemC_Overflow_Add_(Size,sizeof(memc_mc));
									MC=Byte_Alloc_(Size);
								}
								else
									goto ESCAPE;
							}
							else
								MC=Unit_Alloc_(memc_mc);

							if(MC)
							{
								Acs_(const void*,MC->ID)=ID;
								Acs_(MEMC_DT*,MC->Type)=DT;
								Acs_(size_t,MC->Dims)=Dimensions;
								Acs_(size_t,MC->Unit)=DT->SizeType;
								Acs_(size_t,MC->Lng1D)=Lng1D;
								Acs_(void*,MC->AcsND)=NULL;
								Acs_(void*,MC->Acs1D)=NULL;
								if(Dimensions>1)
								{
									Acs_(size_t*,MC->LngND)=(size_t*)(MC+1);
									if(Line_Copy_(Shape,(size_t*)(MC->LngND),Dimensions,size_t))
										MemC_Deloc_(MC);
								}
								else
									Acs_(const size_t*,MC->LngND)=&(MC->Lng1D);
							}
							break;
						case 0x7:
							{
								size_t Size[2];

								if(Dimensions>1)
								{
									Size[0]=_MemC_Overflow_Mul_(Dimensions,sizeof(size_t));
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

								MC=Byte_Alloc_(Size[0]);
							}
							if(MC)
							{
								Acs_(const void*,MC->ID)=ID;
								Acs_(MEMC_DT*,MC->Type)=DT;
								Acs_(size_t,MC->Dims)=Dimensions;
								Acs_(size_t,MC->Unit)=DT->SizeType;
								Acs_(size_t,MC->Lng1D)=Lng1D;
								if(Dimensions>1)
								{
									Acs_(size_t*,MC->LngND)=(size_t*)(MC+1);
									Acs_(void*,MC->AcsND)=(void*)(MC->LngND+Dimensions);
									Acs_(void*,MC->Acs1D)=_MemC_Assign_Loop_((void**)(MC->AcsND),Shape,Dimensions,DT->SizeType);
									if(Line_Copy_(Shape,(size_t*)(MC->LngND),Dimensions,size_t))
										MemC_Deloc_(MC);
								}
								else
								{
									Acs_(const size_t*,MC->LngND)=&(MC->Lng1D);
									Acs_(void*,MC->AcsND)=(void*)(MC+1);
									Acs_(void*,MC->Acs1D)=(void*)(MC->AcsND);
								}
							}
							break;
						default:
							goto ESCAPE;
						}
					}
					else
					{
						MC=Unit_Alloc_(memc_mc);
						if(MC)
						{
							Acs_(const void*,MC->ID)=ID;
							Acs_(MEMC_DT*,MC->Type)=DT;
							Acs_(size_t,MC->Dims)=0;
							Acs_(size_t,MC->Unit)=DT->SizeType;
							Acs_(size_t*,MC->LngND)=NULL;
							Acs_(size_t,MC->Lng1D)=0;
							Acs_(void*,MC->AcsND)=NULL;
							Acs_(void*,MC->Acs1D)=NULL;
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
void MemC_MC_Delete_(memc_mc *_PL_ MC)
{
	MemC_Deloc_(*MC);
}

static size_t _MemC_Space_Occupied_(const size_t _PL_ Shape,const size_t Dims,const size_t SizeType)
{
	const size_t _PL_ Last=Shape+(Dims-1);
	const size_t *_R_ Ptr=Shape;
	size_t Size[2]={1,0};

	for(;Ptr<Last;Ptr++)
	{
		Size[0]*=*Ptr;
		Size[1]+=Size[0];
	}
	{
		Size[0]*=*Ptr;
		Size[0]*=SizeType;
		Size[1]*=sizeof(size_t);
		Size[1]+=Size[0];
	}

	return Size[1];
}
size_t MemC_MC_Size_(MEMC_MC _PL_ MC)
{
	return (MC)?(sizeof(memc_mc)+((MC->Dims>1)?(MemC_Size_(size_t,MC->Dims)):(0))+((MC->Acs1D)?(_MemC_Space_Occupied_(MC->LngND,MC->Dims,MC->Unit)):(0))):(0);
}
int MemC_MC_Form_(MEMC_MC _PL_ MC,MEMC_MS _PL_ MS)
{
	if(MC)
		if(MS)
			if(MC->Dims<MS->Nums)
			{
				MS->Slot.V[0]=MC->Dims;
				if(MC->Dims)
					if(Line_Copy_(MC->LngND,MS->Slot.V+1,MC->Dims,size_t))
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
int MemC_MC_Change_(MEMC_MC _PL_ MC,MEMC_DT _PL_ DT)
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
cl_mem _Devi_Create_Buffer_(cl_context const Context,const size_t Elements,const size_t SizeElement,cl_int _PL_ Error)
{
	const size_t Bytes=(SizeElement)?(_MemC_Overflow_Mul_(Elements,SizeElement)):(0);
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
cl_mem _Devi_Create_Buffer_Sub_(cl_mem const Root,const size_t Offset,const size_t Elements,const size_t SizeElement,cl_int _PL_ Error)
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

static void _Devi_Work_Global_(size_t *_R_ GlobalWorkers,const size_t *_R_ WorkGroups,const size_t *_R_ LocalWorkers,const cl_uint Dimensions)
{
	const size_t _PL_ End=LocalWorkers+Dimensions;

	for(;LocalWorkers<End;LocalWorkers++,WorkGroups++,GlobalWorkers++)
		GlobalWorkers[0]=LocalWorkers[0]*WorkGroups[0];
}
cl_int Devi_Kenq_(cl_command_queue const Queue,cl_kernel const Kernel,const size_t _PL_ WorkGroups,const size_t _PL_ LocalWorkers,const size_t _PL_ GlobalOffset,const cl_uint Dimensions)
{
	cl_int Error;

	if(Dimensions>Devi_Copy_Max_Dimension)
		Error=CL_INVALID_WORK_DIMENSION;
	else
	{
		size_t Total[Devi_Copy_Max_Dimension];

		_Devi_Work_Global_(Total,WorkGroups,LocalWorkers,Dimensions);
		Error=clEnqueueNDRangeKernel(Queue,Kernel,Dimensions,GlobalOffset,Total,LocalWorkers,0,NULL,NULL);
	}

	return Error;
}
#endif
#if(MemC_Fold_(Part:ND Array Data Copy))
cl_int _Devi_Copy_1D_(cl_command_queue const Queue,void _PL_ MemoryS,void _PL_ MemoryT,const size_t OriginS,const size_t OriginT,const size_t Length,const size_t Bytes,DEVI_CF Mode)
{
	cl_int ErrorCode;

	switch(Mode)
	{
	case DeviCopyHtoD:
		ErrorCode=clEnqueueWriteBuffer(Queue,MemoryT,CL_TRUE,Bytes*OriginT,Bytes*Length,((char*)MemoryS)+(Bytes*OriginS),0,NULL,NULL);
		break;
	case DeviCopyDtoH:
		ErrorCode=clEnqueueReadBuffer(Queue,MemoryS,CL_TRUE,Bytes*OriginS,Bytes*Length,((char*)MemoryT)+(Bytes*OriginT),0,NULL,NULL);
		break;
	case DeviCopyDtoD:
		ErrorCode=clEnqueueCopyBuffer(Queue,MemoryS,MemoryT,Bytes*OriginS,Bytes*OriginT,Bytes*Length,0,NULL,NULL);
		break;
	default:
		ErrorCode=CL_INVALID_VALUE;
	}

	return ErrorCode;
}
cl_int _Devi_Copy_(cl_command_queue const Queue,void _PL_ MemoryS,void _PL_ MemoryT,const size_t _PL_ OriginS,const size_t _PL_ OriginT,const size_t _PL_ Length,const size_t _PL_ ShapeS,const size_t _PL_ ShapeT,const cl_uint Dimensions,const size_t Bytes,DEVI_CF Mode)
{
	const size_t _PL_ ShapeSValid=(ShapeS)?(ShapeS):(Length);
	const size_t _PL_ ShapeTValid=(ShapeT)?(ShapeT):(Length);
	cl_int ErrorCode=CL_INVALID_VALUE;
	
	switch(Dimensions)
	{
	case 0:
		ErrorCode=CL_SUCCESS;
		break;
	case 1:
		{
			size_t BufferB[4];

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
				ErrorCode=clEnqueueWriteBuffer(Queue,MemoryT,CL_TRUE,BufferB[1],BufferB[2],((char*)MemoryS)+BufferB[0],0,NULL,NULL);
				break;
			case DeviCopyDtoH:
				ErrorCode=clEnqueueReadBuffer(Queue,MemoryS,CL_TRUE,BufferB[0],BufferB[2],((char*)MemoryT)+BufferB[1],0,NULL,NULL);
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
			size_t BufferS[4];
			size_t BufferT[4];
			size_t Region[4];

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
			size_t BufferS[4];
			size_t BufferT[4];
			size_t Region[4];

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
		List=Line_Alloc_(*Platforms,cl_platform_id);
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
		List=Line_Alloc_(*Devices,cl_device_id);
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
					QC=Unit_Alloc_(devi_qc);
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
void Devi_QC_Delete_(devi_qc *_PL_ QC)
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
static size_t _Devi_KM_Arg_Size_Padding_(size_t Size)
{
	Size+=sizeof(size_t);
	Size--;
	Size/=sizeof(size_t);
	Size*=sizeof(size_t);

	return Size;
}
devi_km *Devi_KM_Create_(const void _PL_ ID,const size_t Args,const size_t Dims)
{
	devi_km *KM;

	if(Dims>Devi_Copy_Max_Dimension)
	{
ESCAPE:
		KM=NULL;
	}
	else
	{
		size_t Temp[2];

		Temp[0]=_MemC_Overflow_Mul_(Dims,sizeof(size_t)<<2);
		if(!(Temp[0]))
			goto ESCAPE;

		Temp[1]=_MemC_Overflow_Mul_(Args,sizeof(size_t)<<1);
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
		KM=Byte_Alloc_(Temp[0]);
	}
	if(KM)
	{
		Acs_(const void*,KM->ID)=ID;
		Acs_(size_t,KM->KArgs)=Args;
		Acs_(size_t,KM->WDims)=Dims;
		Acs_(cl_kernel,KM->Kernel)=NULL;

		Acs_(const size_t*,KM->ArgSize)=Line_Clear_(KM+1,Args<<1,size_t);
		Acs_(const size_t*,KM->ArgAccess.V)=KM->ArgSize+Args;

		Acs_(size_t*,KM->WLocals)=Line_Clear_((size_t*)(KM->ArgAccess.V+Args),Dims<<2,size_t);
		Acs_(size_t*,KM->WGroups)=KM->WLocals+Dims;
		Acs_(size_t*,KM->WOffset)=KM->WGroups+Dims;
		Acs_(size_t*,KM->WLength)=KM->WOffset+Dims;

		Acs_(devi_df*,KM->ArgFlag)=Line_Clear_((devi_df*)(KM->WLength+Dims),Args,devi_df);
		Acs_(void*,KM->ArgMemory)=NULL;
	}

	return KM;
}
cl_int _Devi_KM_Type_(DEVI_KM _PL_ KM,const size_t Order,const size_t ArgSize,DEVI_DF Domain)
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
					((size_t*)(KM->ArgSize))[Order]=sizeof(cl_mem);
					break;
				case DeviDomainLocal:
				case DeviDomainPrivate:
					((size_t*)(KM->ArgSize))[Order]=ArgSize;
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
				if(((size_t)Args)==KM->KArgs)
				{
					DEVI_DF _PL_ End=KM->ArgFlag+KM->KArgs;
					DEVI_DF *_R_ PtrF;
					const size_t *_R_ PtrS;
					size_t Total=0;
					size_t Temp;

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
						Acs_(void*,KM->ArgMemory)=Byte_Alloc_(Total);
					else
					{
ESCAPE_INVALID_ARG_SIZE:
						Error=CL_INVALID_ARG_SIZE;
						goto ESCAPE;
					}

					if(KM->ArgMemory)
					{
						void **PtrA=(void**)(KM->ArgAccess.P);

						{
							PtrF=KM->ArgFlag;
							PtrS=KM->ArgSize;
							PtrA[0]=Byte_Clear_((void*)(KM->ArgMemory),Total);
						}
						for(PtrF++,PtrS++,PtrA++;PtrF<End;PtrF++,PtrS++,PtrA++)
							if(PtrF[-1]==DeviDomainLocal)
							{
								PtrA[0]=PtrA[-1];
								PtrA[-1]=NULL;
							}
							else
								PtrA[0]=((char*)(PtrA[-1]))+_Devi_KM_Arg_Size_Padding_(PtrS[-1]);

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
void Devi_KM_Delete_(devi_km *_PL_ KM)
{
	if(*KM)
	{
		MemC_Deloc_(Acs_(void*,(*KM)->ArgMemory));
		MemC_Deloc_(*KM);
	}
}

cl_int Devi_KM_Save_(DEVI_KM _PL_ KM,const size_t Order,const size_t Thing)
{
	cl_int Error;

	if(KM)
		if(KM->ArgMemory)
			if(Order<KM->KArgs)
				switch(KM->ArgFlag[Order])
				{
				case DeviDomainConstant:
				case DeviDomainGlobal:
					*((void**)(KM->ArgAccess.P[Order]))=*((void**)Thing);

					Error=CL_SUCCESS;
					break;
				case DeviDomainLocal:
					((size_t*)(KM->ArgAccess.V))[Order]=Thing;

					Error=CL_SUCCESS;
					break;
				case DeviDomainPrivate:
					if(Byte_Copy_((const void*)Thing,(void*)(KM->ArgAccess.P[Order]),KM->ArgSize[Order]))
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
			size_t Index=0;

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
static size_t _Devi_MC_Length_Padded_(size_t Length,const size_t Align)
{
	Length+=Align;
	Length--;
	Length/=Align;
	Length*=Align;

	return Length;
}
devi_mc *Devi_MC_Create_(const void _PL_ ID,cl_context const Context,const size_t Number,const size_t Length,MEMC_DT _PL_ DT,cl_int *Error)
{
	devi_mc *MC;

	if(DT)
	{
		const size_t Align=(size_t)_Devi_MC_Align_(Context,Error);

		if((*Error)==CL_SUCCESS)
		{
			{
				size_t Size;

				if(Number)
				{
					Size=_MemC_Overflow_Mul_(Number,sizeof(cl_mem));
					if(Size)
						Size=_MemC_Overflow_Add_(Size,sizeof(devi_mc));
				}
				else
					Size=sizeof(devi_mc);

				MC=Byte_Alloc_(Size);
			}
			if(MC)
			{
				Acs_(const void*,MC->ID)=ID;
				Acs_(MEMC_DT*,MC->Type)=DT;
				Acs_(size_t,MC->Unit)=DT->SizeType;
				Acs_(size_t,MC->Nums)=Number;
				Acs_(size_t,MC->LngS)=Length;

				if(DT->SizeType)
					if(Length)
					{
						Acs_(size_t,MC->AlignS)=_Devi_MC_Length_Padded_(_MemC_Overflow_Mul_(Length,DT->SizeType),Align);
						if(MC->AlignS)
							if(Number)
							{
								const size_t Size=_MemC_Overflow_Mul_(Number,MC->AlignS);

								Acs_(cl_mem,MC->BufT)=Devi_Create_Buffer_(Context,Size,char,Error);
								Acs_(cl_mem*,MC->BufS)=(cl_mem*)(MC+1);
								if((*Error)==CL_SUCCESS)
								{
									const cl_mem _PL_ End=MC->BufS+Number;
									cl_mem *Ptr=(cl_mem*)(MC->BufS);
									size_t Ofs=0;

									while(Ptr<End)
									{
										*Ptr=Devi_Create_Buffer_Sub_(MC->BufT,Ofs,MC->AlignS,char,Error);
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
					Acs_(size_t,MC->AlignS)=0;
					Acs_(cl_mem,MC->BufT)=NULL;
					Acs_(cl_mem*,MC->BufS)=(Number)?(Line_Clear_(MC+1,Number,cl_mem)):(NULL);
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
void Devi_MC_Delete_(devi_mc *_PL_ MC)
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

int Devi_MC_Change_(DEVI_MC _PL_ MC,MEMC_DT _PL_ DT)
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
static void *_MemC_VC_Access_(void *_R_ Jumper,const size_t *_R_ Access,const size_t Count)
{
	const size_t _PL_ End=Access+Count;

	for(;Access<End;Access++)
		Jumper=((void**)Jumper)[*Access];

	return Jumper;
}
memc_vc *MemC_VC_Create_(const void _PL_ ID,MEMC_MC _PL_ MC,MEMC_MS _PL_ MS)
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
							VC=Unit_Alloc_(memc_vc);
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
		Acs_(const void*,VC->ID)=ID;
		Acs_(MEMC_DT*,VC->Type)=MC->Type;
		Acs_(size_t,VC->Unit)=MC->Unit;
		Acs_(size_t,VC->Dims)=MC->Dims-MS->Slot.V[0];
		if(VC->Dims)
		{
			if(VC->Dims>1)
			{
				Acs_(const size_t*,VC->LngND)=MC->LngND+MS->Slot.V[0];
				Acs_(size_t,VC->Lng1D)=_MemC_Array_Prod_(VC->LngND,VC->Dims);
			}
			else
			{
				Acs_(size_t,VC->Lng1D)=MC->LngND[MS->Slot.V[0]];
				Acs_(const size_t*,VC->LngND)=&(VC->Lng1D);
			}
			if(MC->AcsND)
				Acs_(void*,VC->Hidden)=_MemC_VC_Access_((void*)(MC->AcsND),MS->Slot.V+1,MS->Slot.V[0]);
			else
				Acs_(void*,VC->Hidden)=NULL;
		}
		else
		{
			Acs_(size_t,VC->Lng1D)=0;
			Acs_(size_t*,VC->LngND)=NULL;
			Acs_(void*,VC->Hidden)=NULL;
		}
		Acs_(size_t,VC->Domain.N)=0;
		Acs_(memc_df,VC->Domain.E)=MemCDomainHost;
	}
	else
		goto RETURN;
RETURN:
	return VC;
}
#ifdef __OPENCL_H
memc_vc *Devi_VC_Create_(const void _PL_ ID,DEVI_MC _PL_ MC,const size_t Select,MEMC_MS _PL_ MS)
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
								size_t Size=_MemC_Overflow_Mul_(MS->Slot.V[0],sizeof(size_t));

								if(Size)
								{
									Size=_MemC_Overflow_Add_(Size,sizeof(memc_vc));
									VC=Byte_Alloc_(Size);
									break;
								}
								else
									goto ESCAPE;
							}
						case 1:
							if(MC->Unit)
								if(MS->Slot.V[1])
								{
									const size_t Size=_MemC_Overflow_Mul_(MS->Slot.V[1],MC->Unit);

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
							VC=Unit_Alloc_(memc_vc);
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
		Acs_(const void*,VC->ID)=ID;
		Acs_(MEMC_DT*,VC->Type)=MC->Type;
		Acs_(size_t,VC->Unit)=MC->Unit;
		Acs_(size_t,VC->Dims)=MS->Slot.V[0];
		if(VC->Dims)
		{
			if(VC->Dims>1)
			{
				Acs_(size_t*,VC->LngND)=(size_t*)(VC+1);
				if(Line_Copy_(MS->Slot.V+1,(size_t*)(VC->LngND),MS->Slot.V[0],size_t))
				{
					MemC_Deloc_(VC);
					goto RETURN;
				}
				else
					Acs_(size_t,VC->Lng1D)=_MemC_Array_Prod_(VC->LngND,VC->Dims);
			}
			else
			{
				Acs_(size_t,VC->Lng1D)=MS->Slot.V[1];
				Acs_(const size_t*,VC->LngND)=&(VC->Lng1D);
			}
			if(VC->Lng1D)
				Acs_(void*,VC->Hidden)=MC->BufS[Select];
			else
				Acs_(void*,VC->Hidden)=NULL;
		}
		else
		{
			Acs_(size_t,VC->Lng1D)=0;
			Acs_(size_t*,VC->LngND)=NULL;
			Acs_(void*,VC->Hidden)=NULL;
		}
		Acs_(size_t,VC->Domain.N)=0;
		Acs_(memc_df,VC->Domain.E)=MemCDomainDevice;
	}
	else
		goto RETURN;
RETURN:
	return VC;
}
#endif
void MemC_VC_Delete_(memc_vc *_PL_ VC)
{
	MemC_Deloc_(*VC);
}

size_t MemC_VC_Size_(MEMC_VC _PL_ VC)
{
	size_t Return;

	if(VC)
		switch(VC->Domain.E)
		{
		case MemCDomainHost:
			Return=sizeof(memc_vc);
			break;
		case MemCDomainDevice:
			Return=sizeof(memc_vc)+((VC->Dims>1)?(VC->Dims*sizeof(size_t)):(0));
			break;
		default:
			Return=0;
		}
	else
		Return=0;

	return Return;
}
int MemC_VC_Change_(MEMC_VC _PL_ VC,MEMC_DT _PL_ DT)
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

static void *_MemC_VC_Direct_(void *Ptr,size_t Dig)
{
	while(Dig--)
		Ptr=*((void**)Ptr);

	return Ptr;
}
void *MemC_VC_Member_AcsND_(MEMC_VC _PL_ VC)
{
	return ((VC)?((VC->Domain.E==MemCDomainHost)?((void*)(VC->Hidden)):(NULL)):(NULL));
}
void *MemC_VC_Member_Acs1D_(MEMC_VC _PL_ VC)
{
	void *Return;
	
	if(VC)
		if(VC->Domain.E==MemCDomainHost)
			if(VC->Hidden)
				Return=_MemC_VC_Direct_((void*)(VC->Hidden),VC->Dims-1);
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

static size_t _Devi_VC_Offset_(const size_t *_R_ Access,const size_t *_R_ Length,const size_t Dig)
{
	const size_t _PL_ End=Access+Dig;
	size_t Offset=Access[0];

	for(;Access<End;Access++,Length++)
	{
		Offset*=Length[1];
		Offset+=Access[1];
	}

	return Offset;
}
int MemC_VC_Access_(MEMC_VC _PL_ VC,MEMC_MS _PL_ MS)
{
	if(VC)
		if(MS)
			if(VC->Hidden)
				if(MS->Nums>VC->Dims)
				{
					const size_t _PL_ Access=MS->Slot.V+1;

					if(_MemC_Array_Boundary_(Access,VC->LngND,VC->Dims))
					{
						const size_t Dig=VC->Dims-1;

						switch(VC->Domain.E)
						{
						case MemCDomainHost:
							MS->Slot.P[0]=_MemC_VC_Access_((void*)(VC->Hidden),Access,Dig);
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

static int _MemC_VC_Copy_Bound_(const size_t *_R_ Copy,const size_t *_R_ Offset,const size_t *_R_ Bound,const size_t Dims)
{
	const size_t _PL_ End=Copy+Dims;
	size_t Temp;

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
static int _MemC_VC_Copy_Check_(const size_t _PL_ OffsetData,const size_t _PL_ LengthData,const size_t _PL_ LengthCopy,const size_t JumpData,const size_t DimsData,const size_t DimsCopy)
{
	int Return;

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
static void _MemC_VC_Copy_New_Size_(size_t _PL_ LengthNew,size_t _PL_ OffsetNew,const size_t *_R_ OffsetData,const size_t *_R_ LengthData,const size_t JumpData,const size_t DimsCopy)
{
	{
		const size_t _PL_ End=OffsetData+JumpData;

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
		const size_t Rest=DimsCopy-1;

		Line_Copy_(LengthData+1,LengthNew+1,Rest,size_t);
		Line_Copy_(OffsetData+1,OffsetNew+1,Rest,size_t);
	}
}
int MemC_VC_Init_(void _PL_ Queue,MEMC_VC _PL_ VC)
{
	if(VC)
		if(VC->Hidden)
			switch(VC->Domain.E)
			{
			case MemCDomainHost:
				Byte_Clear_(_MemC_VC_Direct_((void*)(VC->Hidden),VC->Dims-1),(VC->Lng1D)*(VC->Unit));
				goto SUCCESS;
#ifdef __OPENCL_H
			case MemCDomainDevice:
				if(Devi_Init_(Queue,(cl_mem)(VC->Hidden),ConstantZero,0,(VC->Lng1D)*(VC->Unit),char)==CL_SUCCESS)
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
int MemC_VC_Copy_(void _PL_ Queue,MEMC_VC _PL_ Source,MEMC_VC _PL_ Target,MEMC_MS _PL_ Copy)
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
			const size_t DimC=Copy->Slot.V[0];
			const size_t _PL_ LngC=Copy->Slot.V+1;
			const size_t *OfsS=LngC+DimC;
			const size_t *OfsT=OfsS+Source->Dims;

			{
				const size_t _PL_ End=Copy->Slot.V+Copy->Nums;
				const size_t _PL_ Temp=OfsT+Target->Dims;

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
				const size_t PreS=Source->Dims-DimC;
				const size_t PreT=Target->Dims-DimC;
				const size_t *LngS=Source->LngND;
				const size_t *LngT=Target->LngND;

				if(!_MemC_VC_Copy_Check_(OfsS,LngS,LngC,PreS,Source->Dims,DimC))
					goto FAILURE;
				if(!_MemC_VC_Copy_Check_(OfsT,LngT,LngC,PreT,Target->Dims,DimC))
					goto FAILURE;
				if(!_MemC_Array_Non_Zero_(LngC,DimC))
					goto SUCCESS;
				if(Source->Hidden)
					if(Target->Hidden)
					{
						void *MemS;
						void *MemT;
#ifdef __OPENCL_H
						int Flag=0x0;
#else
						MemC_Mute_(Queue);
#endif
						switch(Source->Domain.E)
						{
						case MemCDomainHost:
							MemS=_MemC_VC_Access_((void*)(Source->Hidden),OfsS,PreS);
							MemS=_MemC_VC_Direct_(MemS,DimC-1);
							break;
#ifdef __OPENCL_H
						case MemCDomainDevice:
							MemS=(void*)(Source->Hidden);
							Flag|=0x2;
							break;
#endif
						default:
							goto FAILURE;
						}
						switch(Target->Domain.E)
						{
						case MemCDomainHost:
							MemT=_MemC_VC_Access_((void*)(Target->Hidden),OfsT,PreT);
							MemT=_MemC_VC_Direct_(MemT,DimC-1);
							break;
#ifdef __OPENCL_H
						case MemCDomainDevice:
							MemT=(void*)(Target->Hidden);
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
								size_t SizeNew[Devi_Copy_Max_Dimension<<2];

								if(Flag&0x2)
									if(PreS)
									{
										size_t _PL_ LngSNew=SizeNew;
										size_t _PL_ OfsSNew=LngSNew+Devi_Copy_Max_Dimension;

										_MemC_VC_Copy_New_Size_(LngSNew,OfsSNew,OfsS,LngS,PreS,DimC);
										OfsS=OfsSNew;
										LngS=LngSNew;
									}
								if(Flag&0x1)
									if(PreT)
									{
										size_t _PL_ LngTNew=SizeNew+(Devi_Copy_Max_Dimension<<1);
										size_t _PL_ OfsTNew=LngTNew+Devi_Copy_Max_Dimension;

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
				if(Line_Compare_(Source->LngND,Target->LngND,Source->Dims,size_t))
					goto FAILURE;
				else
					if(Source->Hidden)
						if(Target->Hidden)
						{
							const size_t Dig=Source->Dims-1;
							void *MemoryS;
							void *MemoryT;
#ifdef __OPENCL_H
							int Flag=0x0;
#else
							MemC_Mute_(Queue);
#endif
							switch(Source->Domain.E)
							{
							case MemCDomainHost:
								MemoryS=_MemC_VC_Direct_((void*)(Source->Hidden),Dig);
								break;
#ifdef __OPENCL_H
							case MemCDomainDevice:
								MemoryS=(void*)(Source->Hidden);
								Flag|=0x2;
								break;
#endif
							default:
								goto FAILURE;
							}
							switch(Target->Domain.E)
							{
							case MemCDomainHost:
								MemoryT=_MemC_VC_Direct_((void*)(Target->Hidden),Dig);
								break;
#ifdef __OPENCL_H
							case MemCDomainDevice:
								MemoryT=(void*)(Target->Hidden);
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
								if(Byte_Copy_(MemoryS,MemoryT,(Source->Lng1D)*(Source->Unit)))
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
