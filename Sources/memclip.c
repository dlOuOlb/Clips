#define __STDC_WANT_LIB_EXT1__ (1)
#include "memclip.h"

#include <limits.h>
#include <stdarg.h>
#include <stddef.h>

#if(Fold_(Static Assertions))
static_assert((CHAR_BIT==8),"CHAR_BIT != 8");
static_assert((sizeof(byte_08)==1),"sizeof(byte_08) != 1");

static_assert(((address)(NULL))==((address)(0)),"NULL != 0");
static_assert(((address)(FULL))==(~((address)(0))),"FULL != ~0");
static_assert(((address)(FULL))==(UINTPTR_MAX),"FULL != UINTPTR_MAX");

static_assert((sizeof(address)==sizeof(void*)),"sizeof(address) != sizeof(void*)");
static_assert((sizeof(address)==sizeof(size_t)),"sizeof(address) != sizeof(size_t)");
static_assert((sizeof(address)==sizeof(ptrdiff_t)),"sizeof(address) != sizeof(ptrdiff_t)");
static_assert((sizeof(address)==sizeof(void(*)(void))),"sizeof(address) != sizeof(void(*)(void))");
#endif

#if(Fold_(Internal Constants))
#define xMemC_Dims_ ((address)(8))

static const struct
{
	const struct { MEMC_DT Desc[MemCTypes];BYTE_08 Name[MemCTypes][8]; }Type;
	ADDRESS Zero[xMemC_Dims_];
	BYTE_08 Version[16];
	GENERAL _PL_ Self;
}
Idiom=
{
	.Version=oMEMCLIP_INC_,
	.Self=&(Idiom.Self),
	.Zero={0},
	.Type=
	{
		.Name=
		{
			[MemCTypeNone_00]="none_00",
			[MemCTypeByte_08]="byte_08",
			[MemCTypeInteger]="integer",
			[MemCTypeAddress]="address"
		},
		.Desc=
#define xMemC_DT_Parse_(Enum,Size) {.Scope=&(Idiom.Self),.Index=(Enum),.Flag=0,.SizeType=(Size),.SizeName=sizeof(Idiom.Type.Name[Enum]),.Name=Idiom.Type.Name[Enum],.Link=NULL,.Meta=NULL}
		{
			[MemCTypeNone_00]=xMemC_DT_Parse_(MemCTypeNone_00,0),
			[MemCTypeByte_08]=xMemC_DT_Parse_(MemCTypeByte_08,sizeof(byte_08)),
			[MemCTypeInteger]=xMemC_DT_Parse_(MemCTypeInteger,sizeof(integer)),
			[MemCTypeAddress]=xMemC_DT_Parse_(MemCTypeAddress,sizeof(address))
		}
#undef xMemC_DT_Parse_
	}
};

static memc_te MemC_DT_Enum_(MEMC_DT _PL_ _R_ Desc) { return ((Desc)?((Desc->Scope==Idiom.Self)?((memc_te)(Desc->Index)):(MemCTypeUnknown)):(MemCTypeUnknown)); }
static MEMC_DT *MemC_DT_Desc_(MEMC_TE Enum) { return ((Enum>MemCTypeUnknown)?((Enum<MemCTypes)?(Idiom.Type.Desc+Enum):(NULL)):(NULL)); }
#endif

#if(Fold_(Memory Manipulations))
#if(Fold_(Memory Set Handle))
static address xMemC_Array_Prod_(ADDRESS *_R_ Ptr,ADDRESS Count)
{
	register address Length=1;

	for(ADDRESS _PL_ End=Ptr+Count;Ptr<End;Ptr++)
		Length*=*Ptr;

	return Length;
}
static logical xMemC_Array_Non_Zero_(ADDRESS *_R_ Ptr,ADDRESS Nums)
{
	for(ADDRESS _PL_ End=Ptr+Nums;Ptr<End;Ptr++)
		if(*Ptr);
		else
			return 0;

	return 1;
}
static logical xMemC_Array_All_Zero_(ADDRESS *_R_ Ptr,ADDRESS Nums)
{
	for(ADDRESS _PL_ End=Ptr+Nums;Ptr<End;Ptr++)
		if(*Ptr)
			return 0;
		else;

	return 1;
}
static logical MemC_Check_(GENERAL _PL_ _PL_ _R_ Memory,ADDRESS Sets)
{
	if(Memory)
		return xMemC_Array_Non_Zero_((ADDRESS*)(Memory),Sets);
	else
		return 0;
}
static general MemC_Deloc_Set_(general **_R_ Memory,ADDRESS Sets)
{
	if(Memory)
		for(general _PL_ _PL_ End=Memory+Sets;Memory<End;Memory++)
			MemC_Deloc_(*Memory);
	else;

	return;
}
#endif

#if(Fold_(ND Array Memory Allocation))
static address MemC_Size_Add_(ADDRESS A,ADDRESS B) { ADDRESS C=A+B;return ((C<A)?(0):(C)); }
static address MemC_Size_Sub_(ADDRESS A,ADDRESS B) { return ((A<B)?(0):(A-B)); }
static address MemC_Size_Mul_(ADDRESS A,ADDRESS B) { ADDRESS C=A*B;return (((C/B)==A)?(C):(0)); }
static address MemC_Size_Div_(ADDRESS A,ADDRESS B) { return ((A%B)?(0):(A/B)); }

static address xMemC_Bigger_(ADDRESS Number,ADDRESS Old)
{
	address New=MemC_Size_Add_(Old,sizeof(address));

	if(New)
		New=MemC_Size_Mul_(Number,New);
	else;

	return New;
}
static general **xMemC_Assign_(general **_R_ High,ADDRESS NumberHigh,ADDRESS SizeStep)
{
	general *_PL_ End=High+NumberHigh;
	
	for(byte_08 *Low=(byte_08*)End;High<End;High++,Low+=SizeStep)
		*High=Low;

	return End;
}
static general *xMemC_Assign_Loop_(general **PtrM,ADDRESS *_R_ PtrS,ADDRESS NumberDimension,ADDRESS SizeElement)
{
	address Temp=*PtrS;
	
	for(ADDRESS _PL_ End=(PtrS++)+(NumberDimension-1);PtrS<End;PtrS++)
	{
		PtrM=xMemC_Assign_(PtrM,Temp,MemC_Size_(address,*PtrS));
		Temp*=*PtrS;
	}

	return xMemC_Assign_(PtrM,Temp,(*PtrS)*SizeElement);
}
static address xMemC_Size_Pad_(register address S)
{
	ADDRESS T=sizeof(address);

	S--;
	S+=T;
	S/=T;
	S*=T;

	return S;
}
static general *MemC_Alloc_Byte_(ADDRESS S)
{
	ADDRESS N=xMemC_Size_Pad_(S);

	return ((N)?(uMemC_Malloc_(N)):(NULL));
}

static general *xMemC_Alloc_(ADDRESS _PL_ Size,ADDRESS Dims,ADDRESS TypeSize)
{
	if(Size)
		if(Dims*TypeSize)
		{
			ADDRESS Last=Dims-1;
			address Bulk=MemC_Size_Mul_(Size[Last],TypeSize);

			for(ADDRESS *_R_ PtrS=Size+Last;(--PtrS)>=Size;)
				if(Bulk)
					Bulk=xMemC_Bigger_(*PtrS,Bulk);
				else
					return NULL;

			if(Bulk)
			{
				general _PL_ Memory=MemC_Alloc_Byte_(Bulk);

				if(Memory)
					if(Last)
						xMemC_Assign_Loop_(Memory,Size,Dims,TypeSize);
					else;
				else;

				return Memory;
			}
			else;
		}
		else;
	else;

	return NULL;
}
static general *xMemC_Alloc_ND_(ADDRESS TypeSize,ADDRESS Dims,...)
{
	if(Dims>xMemC_Dims_)
		return NULL;
	else
	{
		address Buffer[xMemC_Dims_];
		va_list Arg;

		va_start(Arg,Dims);

		for(address Dim=0;Dim<Dims;Dim++)
			Buffer[Dim]=va_arg(Arg,address);

		va_end(Arg);

		return xMemC_Alloc_(Buffer,Dims,TypeSize);
	}
}
#endif

#if(Fold_(1D Array Trivials))
static address xMemC_Safe_2_(register address Num)
{
	Num|=(Num>>1);
	Num|=(Num>>2);
	Num|=(Num>>4);
#if(UINTPTR_MAX>UINT8_MAX)
	Num|=(Num>>8);
#if(UINTPTR_MAX>UINT16_MAX)
	Num|=(Num>>16);
#if(UINTPTR_MAX>UINT32_MAX)
	Num|=(Num>>32);
#endif
#endif
#endif
	Num++;
	Num>>=1;

	return Num;
}
static logical xMemC_Init_1D_(general _PL_ _R_ Memory,GENERAL _PL_ _R_ Tile,ADDRESS NumberElement,ADDRESS SizeElement)
{
	if(MemC_Size_Mul_(NumberElement,SizeElement))
		if(MemC_Copy_Byte_(Tile,Memory,SizeElement))
		{
			address Safe=xMemC_Safe_2_(NumberElement);
			BYTE_08 _PL_ End=((byte_08*)Memory)+(Safe*SizeElement);
			byte_08 *_R_ Ptr=((byte_08*)Memory)+SizeElement;

			for(address Copy=SizeElement;Ptr<End;Copy<<=1)
				if(MemC_Copy_Byte_(Memory,Ptr,Copy))
					Ptr+=Copy;
				else
					return 0;

			Safe^=NumberElement;
			Safe*=SizeElement;

			if(Safe)
				return MemC_Copy_Byte_(Memory,Ptr,Safe);
			else
				return 1;
		}
		else;
	else;

	return 0;
}
static logical MemC_Copy_Step_(GENERAL _PL_ _R_ Source,general _PL_ _R_ Target,ADDRESS Nums,ADDRESS StepS,ADDRESS StepT,ADDRESS Copy)
{
	BYTE_08 *_R_ PtrS=Source;
	byte_08 *_R_ PtrT=Target;

	for(BYTE_08 _PL_ End=PtrS+(Nums*StepS);PtrS<End;PtrS+=StepS,PtrT+=StepT)
		if(MemC_Copy_Byte_(PtrS,PtrT,Copy));
		else
			return 0;

	return 1;
}
#endif

#if(Fold_(ND Array Data Copy))
static general xMemC_Jump_Offset_(address _PL_ Jump,ADDRESS _PL_ Shape,ADDRESS Dimension,ADDRESS Bytes)
{
	ADDRESS From=Dimension-2;
	ADDRESS *_R_ PtrS=Shape+From;
	address *_R_ PtrJ=Jump+From;

	for(PtrJ[+1]=Bytes;PtrJ>=Jump;PtrS--,PtrJ--)
		PtrJ[0]=PtrS[+1]*PtrJ[+1];

	return;
}
static logical xMemC_Copy_2D_(BYTE_08 _PL_ MemoryS,byte_08 _PL_ MemoryT,ADDRESS _PL_ JumpS,ADDRESS _PL_ JumpT,ADDRESS _PL_ OriginS,ADDRESS _PL_ OriginT,ADDRESS _PL_ Length,ADDRESS Bytes)
{
	ADDRESS Copy=Length[1]*Bytes;
	BYTE_08 *End=MemoryS+((JumpS[0]*OriginS[0])+(JumpS[1]*OriginS[1]));
	BYTE_08 *PointerS=End;
	byte_08 *PointerT=MemoryT+((JumpT[0]*OriginT[0])+(JumpT[1]*OriginT[1]));

	for(End+=(JumpS[0]*Length[0]);PointerS<End;PointerS+=JumpS[0],PointerT+=JumpT[0])
		if(MemC_Copy_Byte_(PointerS,PointerT,Copy));
		else
			return 0;

	return 1;
}
static logical xMemC_Copy_Recursive_(BYTE_08 _PL_ MemoryS,byte_08 _PL_ MemoryT,ADDRESS _PL_ JumpS,ADDRESS _PL_ JumpT,ADDRESS _PL_ OriginS,ADDRESS _PL_ OriginT,ADDRESS _PL_ Length,ADDRESS Dimensions,ADDRESS Bytes)
{
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
			if(xMemC_Copy_Recursive_(PointerS,PointerT,NextJumpS,NextJumpT,NextOriginS,NextOriginT,NextLength,NextDimensions,Bytes));
			else
				return 0;

		return 1;
	}
	else
		return xMemC_Copy_2D_(MemoryS,MemoryT,JumpS,JumpT,OriginS,OriginT,Length,Bytes);
}
static logical xMemC_Copy_Check_Bound_(ADDRESS _PL_ Shape,ADDRESS _PL_ Offset,ADDRESS _PL_ Length,ADDRESS Dimensions)
{
	for(register address Index=0;Index<Dimensions;Index++)
	{
		register ADDRESS Temp=Offset[Index]+Length[Index];

		if(Temp<Offset[Index])
			return 0;
		else if(Temp>Shape[Index])
			return 0;
		else;
	}

	return 1;
}
static logical xMemC_Copy_(GENERAL _PL_ MemoryS,general _PL_ MemoryT,ADDRESS _PL_ OriginS,ADDRESS _PL_ OriginT,ADDRESS _PL_ Length,ADDRESS _PL_ ShapeS,ADDRESS _PL_ ShapeT,ADDRESS Dimensions,ADDRESS Bytes)
{
	ADDRESS _PL_ OffsetS=(OriginS)?(OriginS):(Idiom.Zero);
	ADDRESS _PL_ OffsetT=(OriginT)?(OriginT):(Idiom.Zero);

	if(xMemC_Copy_Check_Bound_(ShapeS,OffsetS,Length,Dimensions)&&xMemC_Copy_Check_Bound_(ShapeT,OffsetT,Length,Dimensions))
		switch(Dimensions)
		{
		case 0:
			return 1;
		case 1:
			{
				ADDRESS Copy=Length[0]*Bytes;

				if(Copy)
					return MemC_Copy_Byte_(((BYTE_08*)MemoryS)+(OffsetS[0]*Bytes),((byte_08*)MemoryT)+(OffsetT[0]*Bytes),Copy);
				else
					return 1;
			}
		default:
			if(Bytes)
				if(xMemC_Array_Non_Zero_(Length,Dimensions))
					if(Dimensions>xMemC_Dims_)
						return 0;
					else
					{
						address JumpS[xMemC_Dims_];
						address JumpT[xMemC_Dims_];

						xMemC_Jump_Offset_(JumpS,(ShapeS)?(ShapeS):(Length),Dimensions,Bytes);
						xMemC_Jump_Offset_(JumpT,(ShapeT)?(ShapeT):(Length),Dimensions,Bytes);

						return xMemC_Copy_Recursive_(MemoryS,MemoryT,JumpS,JumpT,OffsetS,OffsetT,Length,Dimensions,Bytes);
					}
				else
					return 1;
			else
				return 1;
		}
	else
		return 0;
}
#endif

#if(Fold_(ND Array Data Reformation))
static logical xMemC_Reform_Valid_(ADDRESS *_R_ Map,ADDRESS Dims)
{
	address Table[xMemC_Dims_]={0};

	for(ADDRESS _PL_ End=Map+Dims;Map<End;Map++)
		if((*Map)<Dims)
			Table[*Map]=~Table[*Map];
		else
			return 0;

	return xMemC_Array_Non_Zero_(Table,Dims);
}
static general xMemC_Reform_Short_(ADDRESS _PL_ _R_ Shape,ADDRESS _PL_ _R_ Map,address _PL_ _R_ Dims,address _PL_ _R_ Bytes)
{
	for(register address Temp=*Dims;--Temp;)
		if(Map[Temp]==Temp)
			*Bytes*=Shape[*Dims=Temp];
		else
			break;

	return;
}
static general xMemC_Reform_Merge_(address _PL_ Shape,address _PL_ Map,address _PL_ _R_ Dims)
{
	ADDRESS *End=Map+(*Dims),*Last=End-1;

	for(address *MapA=Map,*ShpA=Shape;MapA<Last;MapA++,ShpA++)
	{
		ADDRESS *MapB,*ShpB;

		for(MapB=MapA,ShpB=ShpA;MapB<Last;MapB++,ShpB++)
			if((MapB[0]+1)==MapB[1])
				ShpA[0]*=ShpB[1];
			else
				break;

		if(MapA<MapB)
		{
			ADDRESS Pull=MapB-MapA;
			address *MapC,*ShpC;

			for(MapC=Map,ShpC=ShpA;MapC<MapA;MapC++)
				if(MapC[0]>MapA[0])
					MapC[0]-=Pull;
				else;

			for(MapB++,MapC++,ShpB++,ShpC++;MapB<End;MapB++,MapC++,ShpB++,ShpC++)
			{
				MapC[0]=(MapA[0]<MapB[0])?(MapB[0]-Pull):(MapB[0]);
				ShpC[0]=ShpB[0];
			}

			End=MapC;
			Last=End-1;
			*Dims=End-Map;
		}
		else;
	}

	return;
}
static logical xMemC_Reform_Order_(BYTE_08 _PL_ _R_ Source,byte_08 _PL_ _R_ Target,ADDRESS _PL_ _R_ Shape,ADDRESS _PL_ _R_ Map,ADDRESS Total,ADDRESS Dims,ADDRESS Bytes)
{
	ADDRESS Last=Dims-1;

	for(address Jump[xMemC_Dims_],IdxT=0;IdxT<Total;IdxT++)
	{
		address IdxJ,IdxS,Prod;

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
		if(MemC_Copy_Byte_(Source+(IdxS*Bytes),Target+(IdxT*Bytes),Bytes));
		else
			return 0;
	}

	return 1;
}
static logical xMemC_Reform_(GENERAL _PL_ _R_ MemoryS,general _PL_ _R_ MemoryT,ADDRESS _PL_ _R_ ShapeS,ADDRESS _PL_ _R_ AxisStoT,address Dimensions,address Bytes)
{
	if(Dimensions)
	{
		xMemC_Reform_Short_(ShapeS,AxisStoT,&Dimensions,&Bytes);
		if(Dimensions>1)
			if(Dimensions>xMemC_Dims_)
				return 0;
			else if(xMemC_Reform_Valid_(AxisStoT,Dimensions))
			{
				ADDRESS Total=xMemC_Array_Prod_(ShapeS,Dimensions);

				if(Total)
				{
					address ShapeSNew[xMemC_Dims_];
					address MapTNew[xMemC_Dims_];

					if(MemC_Copy_1D_(ShapeS,ShapeSNew,Dimensions));
					else
						return 0;

					if(MemC_Copy_1D_(AxisStoT,MapTNew,Dimensions));
					else
						return 0;

					xMemC_Reform_Merge_(ShapeSNew,MapTNew,&Dimensions);

					return xMemC_Reform_Order_(MemoryS,MemoryT,ShapeSNew,MapTNew,Total,Dimensions,Bytes);
				}
				else
					return 1;
			}
			else
				return 0;
		else
			if(AxisStoT[0])
				return 0;
			else
			{
				ADDRESS Copy=ShapeS[0]*Bytes;

				if(Copy)
					return MemC_Copy_Byte_(MemoryS,MemoryT,Copy);
				else
					return 1;
			}
	}
	else
		return 1;
}

static logical MemC_Reform_Shape_(ADDRESS _PL_ _R_ ShapeS,ADDRESS _PL_ _R_ AxisStoT,address _PL_ _R_ ShapeT,ADDRESS Dimensions)
{
	if(Dimensions)
		if(Dimensions>xMemC_Dims_)
			return 0;
		else if(xMemC_Reform_Valid_(AxisStoT,Dimensions))
			for(register address Index=0;Index<Dimensions;Index++)
				ShapeT[AxisStoT[Index]]=ShapeS[Index];
		else
			return 0;
	else;

	return 1;
}
#endif

#if(Fold_(Object Sorting))
static address xMemC_Sort_Lng_2_(ADDRESS Length)
{
	register address Temp=1;

	Temp=~Temp;
	Temp&=Length;

	return Temp;
}
static general xMemC_Sort_Bound_(address _PL_ _R_ Jump,GENERAL _PL_ *_PL_ _R_ Bound)
{
	Bound[2]=Bound[1]+Jump[0];
	if(Bound[2]>Bound[3])
		Bound[2]=Bound[3];
	else;
	Jump[1]=Bound[2]-Bound[1];
	Jump[2]=Jump[0]+Jump[1];
	Jump[3]=Jump[1]-1;

	return;
}
static general xMemC_Sort_Ord_2_(logical(_PL_ Comp_)(GENERAL _PL_,GENERAL _PL_),GENERAL **_R_ Ptr,address *_R_ Idx,ADDRESS Length)
{
	if(Idx)
		for(GENERAL _PL_ _PL_ End=Ptr+xMemC_Sort_Lng_2_(Length);Ptr<End;Ptr+=2,Idx+=2)
		{
			ADDRESS Cast=Comp_(Ptr[0],Ptr[1]),X=Cast&1,Y=X^1;
			union { GENERAL*P;address V; }Temp;

			Temp.P=Ptr[Y];
			Ptr[0]=Ptr[X];
			Ptr[1]=Temp.P;

			Temp.V=Idx[Y];
			Idx[0]=Idx[X];
			Idx[1]=Temp.V;
		}
	else
		for(GENERAL _PL_ _PL_ End=Ptr+xMemC_Sort_Lng_2_(Length);Ptr<End;Ptr+=2)
		{
			address Cast=Comp_(Ptr[0],Ptr[1]);
			GENERAL _PL_ Temp=Ptr[Cast&=1];

			Ptr[1]=Ptr[Cast^=1];
			Ptr[0]=Temp;
		}

	return;
}
static general xMemC_Sort_Ord_A_(logical(_PL_ Comp_)(GENERAL _PL_,GENERAL _PL_),address *_R_ PtrT,GENERAL _PL_ *_R_ PtrA,GENERAL _PL_ _PL_ StartB,GENERAL _PL_ _PL_ EndB)
{
	PtrT[0]=0;

	for(GENERAL _PL_ *_R_ PtrB=StartB;PtrB<EndB;PtrB++)
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
			else;
		}

	for(PtrA++,PtrT++;PtrA<StartB;PtrA++,PtrT++)
		PtrT[0]=PtrT[-1];

	return;
}
static general xMemC_Sort_Ord_B_(logical(_PL_ Comp_)(GENERAL _PL_,GENERAL _PL_),address *_R_ PtrT,GENERAL _PL_ *_R_ PtrB,GENERAL _PL_ _PL_ StartA,GENERAL _PL_ _PL_ StartB)
{
	PtrT[0]=0;

	for(GENERAL _PL_ *_R_ PtrA=StartB-1;PtrA>=StartA;PtrA--)
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
			else;
		}

	for(PtrB--,PtrT--;PtrB>=StartB;PtrB--,PtrT--)
		PtrT[0]=PtrT[+1];

	return;
}
static logical xMemC_Sort_Table_(address *_R_ IdxO,address *_R_ IdxA,ADDRESS *_R_ PtrT,ADDRESS _PL_ MatchB,ADDRESS Copy,ADDRESS Step)
{
	if(MemC_Copy_1D_(IdxO,IdxA,Copy))
	{
		for(;IdxO<MatchB;IdxA++,IdxO++,PtrT++)
			IdxO[PtrT[0]]=IdxA[0];
		for(IdxA+=Step,IdxO+=Step,PtrT+=Step;IdxO>=MatchB;IdxA--,IdxO--,PtrT--)
			IdxO[PtrT[0]]=IdxA[0];

		return 1;
	}
	else
		return 0;
}
static logical MemC_Sort_(logical(_PL_ Comp_)(GENERAL _PL_,GENERAL _PL_),GENERAL *_PL_ _R_ Refer,address _PL_ _R_ Index,address _PL_ _R_ Buffer,ADDRESS Length)
{
	if(Length)
	{
		GENERAL _PL_ *Bound[4];
		address Jump[4];
		address _PL_ Table=Buffer;
		address _PL_ Value=Table+Length;

		xMemC_Sort_Ord_2_(Comp_,Refer,Index,Length);
		if(Index)
		{
			address *Match;

			for(Jump[0]=2,Bound[3]=Refer+Length;Jump[0]<Length;Jump[0]<<=1)
				for(Bound[0]=Refer,Bound[1]=Refer+Jump[0],Match=Index;Bound[1]<Bound[3];Bound[0]=Bound[2],Bound[1]=Bound[2]+Jump[1],Match+=Jump[2])
				{
					xMemC_Sort_Bound_(Jump,Bound);
					xMemC_Sort_Ord_A_(Comp_,Table,Bound[0],Bound[1],Bound[2]);
					xMemC_Sort_Ord_B_(Comp_,Table+(Jump[2]-1),Bound[2]-1,Bound[0],Bound[1]);

					if(xMemC_Sort_Table_((address*)(Bound[0]),Value,Table,(address*)(Bound[1]),Jump[2],Jump[3]));
					else
						return 0;

					if(xMemC_Sort_Table_(Match,Value,Table,Match+Jump[0],Jump[2],Jump[3]));
					else
						return 0;
				}
		}
		else
			for(Jump[0]=2,Bound[3]=Refer+Length;Jump[0]<Length;Jump[0]<<=1)
				for(Bound[0]=Refer,Bound[1]=Refer+Jump[0];Bound[1]<Bound[3];Bound[0]=Bound[2],Bound[1]=Bound[2]+Jump[1])
				{
					xMemC_Sort_Bound_(Jump,Bound);
					xMemC_Sort_Ord_A_(Comp_,Table,Bound[0],Bound[1],Bound[2]);
					xMemC_Sort_Ord_B_(Comp_,Table+(Jump[2]-1),Bound[2]-1,Bound[0],Bound[1]);

					if(xMemC_Sort_Table_((address*)(Bound[0]),Value,Table,(address*)(Bound[1]),Jump[2],Jump[3]));
					else
						return 0;
				}
	}
	else;

	return 1;
}
#endif

#if(Fold_(Others))
static general MemC_Void_(general) { return; }
static address MemC_Just_(ADDRESS X) { return X; }
static general MemC_Self_(address *_R_ Table,ADDRESS Length,LOGICAL Mode)
{
	if(Mode)
		for(ADDRESS _PL_ End=Table+Length;Table<End;Table++)
			*Table=(address)(Table);
	else
		for(address Idx=0;Idx<Length;Idx++)
			Table[Idx]=Idx;

	return;
}
static address xMemC_Assign_1D_(general _PL_ _R_ Indexer,GENERAL _PL_ _R_ Indexed,ADDRESS Interval,ADDRESS Indices,ADDRESS TypeSize,LOGICAL Mode)
{
	if(Indices)
	{
		BYTE_08 **_R_ PtrO=Indexer;
		BYTE_08 _PL_ _PL_ End=PtrO+Indices;

		*(PtrO++)=Indexed;
		if(Mode)
		{
			ADDRESS *_R_ PtrS=Acs_(ADDRESS*,Interval);

			for(;PtrO<End;PtrO++,PtrS++)
				PtrO[0]=PtrO[-1]+(PtrS[0]*TypeSize);

			return ((PtrO[-1]-(BYTE_08*)(Indexed))+(PtrS[0]*TypeSize));
		}
		else
		{
			ADDRESS Step=Interval*TypeSize;

			for(;PtrO<End;PtrO++)
				PtrO[0]=PtrO[-1]+Step;

			return (Step*Indices);
		}
	}
	else
		return 0;
}
#endif
#endif

#if(Fold_(Advanced Objects))
static general MemC_Delete_(general *_PL_ _R_ Object) { MemC_Deloc_(*Object);return; }

#if(Fold_(MemC_MS))
static memc_ms *MemC_MS_Create_(ADDRESS Nums)
{
	memc_ms *MS=NULL;

	if(Nums)
	{
		MemC_Temp_(ADDRESS,Size=MemC_Size_Mul_(Nums,sizeof(address)))
			MS=MemC_Alloc_Byte_(MemC_Size_Add_(Size,sizeof(memc_ms)));

		if(MS)
		{
			Acs_(address,MS->Nums)=Nums;
			Acs_(address*,MS->Slot.V)=MemC_Clear_1D_((address*)(MS+1),Nums);
		}
		else;
	}
	else
	{
		MS=MemC_Alloc_Unit_(memc_ms);
		if(MS)
		{
			Acs_(address,MS->Nums)=0;
			Acs_(address*,MS->Slot.V)=NULL;
		}
		else;
	}

	return MS;
}
static address MemC_MS_Size_(MEMC_MS _PL_ _R_ MS)
{
	return (MS)?(sizeof(memc_ms)+MemC_Size_(address,MS->Nums)):(0);
}

static logical MemC_MS_Init_(MEMC_MS _PL_ _R_ MS)
{
	if(MS)
	{
		if(MS->Nums)
			MemC_Clear_1D_(MS->Slot.V,MS->Nums);
		else;

		return 1;
	}
	else
		return 0;
}
static logical MemC_MS_Null_(MEMC_MS _PL_ _R_ MS,LOGICAL Mode)
{
	if(MS)
		if(MS->Slot.V)
			if(MS->Slot.V[0]<MS->Nums)
				return (((Mode)?(xMemC_Array_Non_Zero_):(xMemC_Array_All_Zero_))(MS->Slot.V+1,MS->Slot.V[0]));
			else;
		else;
	else;

	return 0;
}

static logical MemC_MS_Dims_(MEMC_MS _PL_ _R_ MS,ADDRESS Dims,...)
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

			return 1;
		}
		else;
	else;

	return 0;
}
#endif

#if(Fold_(MemC_MC))
static address xMemC_Shape_Overflow_(ADDRESS *_R_ Ptr,ADDRESS Dims)
{
	address Total=1;

	for(ADDRESS _PL_ End=Ptr+Dims;Ptr<End;Ptr++)
		Total=MemC_Size_Mul_(Total,*Ptr);

	return Total;
}
static address xMemC_Space_Required_(ADDRESS *_R_ Ptr,ADDRESS Dims,ADDRESS SizeType)
{
	if(Dims>1)
	{
		address Size[2]={1,0};

		for(ADDRESS _PL_ Last=Ptr+(Dims-1);Ptr<Last;)
		{
			Size[0]=MemC_Size_Mul_(Size[0],*Ptr);

			if(Size[0])
				Size[1]=MemC_Size_Add_(Size[0],Size[1]);
			else
				return 0;

			if(Size[1])
				Ptr++;
			else
				return 0;
		}

		Size[0]=MemC_Size_Mul_(Size[0],*Ptr);
		Size[0]=MemC_Size_Mul_(Size[0],SizeType);

		if(Size[0])
			Size[1]=MemC_Size_Mul_(Size[1],sizeof(address));
		else
			return 0;

		if(Size[1])
			return MemC_Size_Add_(Size[0],Size[1]);
		else
			return 0;
	}
	else
		return MemC_Size_Mul_(*Ptr,SizeType);
}
static memc_mc *MemC_MC_Create_(GENERAL _PL_ ID,MEMC_MS _PL_ MS,MEMC_DT _PL_ DT)
{
	if(DT)
		if(MS)
			if(MS->Slot.V)
				if(MS->Slot.V[0]<MS->Nums)
					if(MS->Slot.V[0])
					{
						ADDRESS Dimensions=MS->Slot.V[0],_PL_ Shape=MS->Slot.V+1;
						address Lng1D;
						integer Flag=(DT->SizeType)?(0x1):(0x0);

						if(xMemC_Array_Non_Zero_(Shape,Dimensions))
						{
							Lng1D=xMemC_Shape_Overflow_(Shape,Dimensions);
							Flag|=(Lng1D)?(0x6):(0x2);
						}
						else
							Lng1D=0;

						switch(Flag)
						{
							memc_mc *MC;

						case 0x0:
						case 0x1:
						case 0x6:
							if(Dimensions>1)
							{
								ADDRESS Size=MemC_Size_Mul_(Dimensions,sizeof(address));

								if(Size)
									MC=MemC_Alloc_Byte_(MemC_Size_Add_(Size,sizeof(memc_mc)));
								else
									break;
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
									if(MemC_Copy_1D_(Shape,Acs_(address*,MC->LngND)=(address*)(MC+1),Dimensions));
									else
										MemC_Deloc_(MC);
								else
									Acs_(ADDRESS*,MC->LngND)=&(MC->Lng1D);

								return MC;
							}
							else
								break;

						case 0x7:
							{
								address Size[2];

								if(Dimensions>1)
								{
									Size[0]=MemC_Size_Mul_(Dimensions,sizeof(address));
									if(Size[0]);else break;

									Size[0]=MemC_Size_Add_(Size[0],sizeof(memc_mc));
									if(Size[0]);else break;
								}
								else
									Size[0]=sizeof(memc_mc);

								Size[1]=xMemC_Space_Required_(Shape,Dimensions,DT->SizeType);
								if(Size[1]);else break;

								MC=MemC_Alloc_Byte_(MemC_Size_Add_(Size[0],Size[1]));
							}

							if(MC)
							{
								Acs_(GENERAL*,MC->ID)=ID;
								Acs_(MEMC_DT*,MC->Type)=DT;
								Acs_(address,MC->Dims)=Dimensions;
								Acs_(address,MC->Unit)=DT->SizeType;
								Acs_(address,MC->Lng1D)=Lng1D;

								if(Dimensions>1)
									if(MemC_Copy_1D_(Shape,Acs_(address*,MC->LngND)=(address*)(MC+1),Dimensions))
										Acs_(general*,MC->Acs1D)=xMemC_Assign_Loop_(Acs_(general*,MC->AcsND)=(general*)(MC->LngND+Dimensions),Shape,Dimensions,DT->SizeType);
									else
										MemC_Deloc_(MC);
								else
								{
									Acs_(ADDRESS*,MC->LngND)=&(MC->Lng1D);
									Acs_(general*,MC->AcsND)=(general*)(MC+1);
									Acs_(general*,MC->Acs1D)=(general*)(MC->AcsND);
								}

								return MC;
							}
							else
								break;

						default:;
						}
					}
					else
					{
						memc_mc _PL_ MC=MemC_Alloc_Unit_(memc_mc);

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

							return MC;
						}
						else;
					}
				else;
			else;
		else;
	else;

	return NULL;
}

static address xMemC_Space_Occupied_(ADDRESS *_R_ Ptr,ADDRESS Dims,ADDRESS SizeType)
{
	address Size[2]={1,0};

	for(ADDRESS _PL_ Last=Ptr+(Dims-1);Ptr<Last;Ptr++)
		Size[1]+=(Size[0]*=*Ptr);
	{
		Size[0]*=*Ptr;
		Size[0]*=SizeType;
		Size[1]*=sizeof(address);
		Size[1]+=Size[0];
	}

	return Size[1];
}
static address MemC_MC_Size_(MEMC_MC _PL_ _R_ MC)
{
	return ((MC)?(sizeof(memc_mc)+(((MC->LngND)==&(MC->Lng1D))?(0):(MemC_Size_(address,MC->Dims)))+((MC->Acs1D)?(xMemC_Space_Occupied_(MC->LngND,MC->Dims,MC->Unit)):(0))):(0));
}
static logical MemC_MC_Fill_(MEMC_MC _PL_ _R_ MC,GENERAL _PL_ _R_ Value)
{
	if(MC)
	{
		if(MC->Unit)
			if(MC->Lng1D)
				return xMemC_Init_1D_(MC->Acs1D,Value,MC->Lng1D,MC->Unit);
			else;
		else;

		return 1;
	}
	else
		return 0;
}

static logical MemC_MC_Form_(MEMC_MC _PL_ _R_ MC,MEMC_MS _PL_ _R_ MS)
{
	if(MC)
		if(MS)
			if(MC->Dims<MS->Nums)
			{
				MS->Slot.V[0]=MC->Dims;
				if(MC->Dims)
					if(MemC_Copy_1D_(MC->LngND,MS->Slot.V+1,MC->Dims))
						return 1;
					else;
				else
					return 1;
			}
			else;
		else;
	else;

	return 0;
}
static logical MemC_MC_Change_(memc_mc _PL_ _R_ MC,MEMC_DT _PL_ DT)
{
	if(MC)
		if(DT)
			if(DT->SizeType==MC->Unit)
			{
				Acs_(MEMC_DT*,MC->Type)=DT;

				return 1;
			}
			else;
		else;
	else;

	return 0;
}
#endif

#if(Fold_(MemC_ML))
#define xMemC_ML_Malloc_(Chunks) ((MemC_Size_Mul_(Chunks,sizeof(memc_mn)))?(malloc(MemC_Size_(memc_mn,Chunks))):(NULL))
#define xMemC_ML_Free_(Memory) __dl{free(Memory);(Memory)=NULL;}lb__

struct _memc_l2 { general *L[2]; };
MemC_Type_Declare_(struct,memc_l2,MEMC_L2);

struct _memc_mn { memc_ml *Home;struct _memc_mn *Prev,*Next;address Size; };
MemC_Type_Declare_(struct,memc_mn,MEMC_MN);

static_assert(sizeof(memc_l2)==(sizeof(address)<<1),"sizeof(memc_l2) != 2*sizeof(address)");
static_assert(sizeof(memc_mn)==(sizeof(address)<<2),"sizeof(memc_mn) != 4*sizeof(address)");
static_assert(sizeof(memc_ml)==(sizeof(address)<<3),"sizeof(memc_ml) != 8*sizeof(address)");

static memc_ml *MemC_ML_Create_(memc_ml _PL_ Root,ADDRESS Chunks)
{
	memc_ml *ML;

	if(Chunks>2)
		if(Root)
			if(Root==Root->Link.Self)
			{
				ML=xMemC_ML_Malloc_(Chunks);
				if(ML)
				{
					Acs_(memc_ml*,ML->Link.Self)=ML;
					Acs_(memc_ml*,ML->Link.Prev)=Root;
					Acs_(MEMC_ML*,ML->Link.Next)=Root->Link.Next;

					Acs_(memc_ml*,Root->Link.Next->Link.Prev)=ML;
					Acs_(memc_ml*,Root->Link.Next)=ML;

					goto JUMP;
				}
				else;
			}
			else
				ML=NULL;
		else
		{
			ML=xMemC_ML_Malloc_(Chunks);
			if(ML)
			{
				{
					Acs_(memc_ml*,ML->Link.Self)=ML;
					Acs_(memc_ml*,ML->Link.Prev)=ML;
					Acs_(memc_ml*,ML->Link.Next)=ML;
				}
JUMP:
				MemC_Temp_(memc_mn,_PL_ MN=(memc_mn*)(ML+1))
				{
					MN->Home=NULL;
					MN->Prev=NULL;
					MN->Next=NULL;
					MN->Size=MemC_Size_(memc_mn,Chunks-3);

					Acs_(address,ML->Size.Able)=MN->Size;
					Acs_(address,ML->Size.Idle)=MN->Size;
					Acs_(address,ML->Size.Used)=0;
					Acs_(address,ML->Nums.Idle)=1;
					Acs_(address,ML->Nums.Used)=0;
				}
			}
			else;
		}
	else
		ML=NULL;

	return ML;
}
static memc_ml *MemC_ML_Delete_(memc_ml *_PL_ _R_ ML)
{
	memc_ml *Return;

	if(*ML)
		if((*ML)==(*ML)->Link.Self)
		{
			if((*ML)==(*ML)->Link.Prev)
				Return=NULL;
			else
			{
				Return=(*ML)->Link.Prev;

				Acs_(memc_ml*,(*ML)->Link.Prev->Link.Next)=(*ML)->Link.Next;
				Acs_(memc_ml*,(*ML)->Link.Next->Link.Prev)=(*ML)->Link.Prev;
			}
			xMemC_ML_Free_(*ML);
		}
		else
			Return=NULL;
	else
		Return=NULL;

	return Return;
}
static address MemC_ML_Size_(MEMC_ML _PL_ _R_ ML)
{
	return ((ML)?(MemC_Size_(memc_ml,1)+MemC_Size_(memc_mn,ML->Nums.Idle+ML->Nums.Used)+(ML->Size.Idle+ML->Size.Used)):(0));
}

static address xMemC_MN_Margin_(register address S)
{
	ADDRESS T=sizeof(memc_mn);

	S--;
	S+=T;
	S/=T;
	S*=T;

	return S;
}
static logical xMemC_MN_Scan_(memc_mn *_R_ Ptr)
{
	__dlOuOlb__
		if(Ptr->Next)
			if(Ptr==Ptr->Next->Prev)
				Ptr=Ptr->Next;
			else
				return 0;
		else
			return 1;
}
static memc_mn *xMemC_MN_Search_Space_(memc_mn *_R_ Ptr,ADDRESS Demand)
{
	memc_mn *Here=NULL;

	for(address Size=UINTPTR_MAX;Ptr;Ptr=Ptr->Next)
		if(Ptr->Home);
		else if(Demand>Ptr->Size);
		else if(Size>Ptr->Size)
			Size=(Here=Ptr)->Size;
		else;

	return Here;
}
static address xMemC_MN_Search_Size_(memc_mn *_R_ Ptr)
{
	address Temp;

	for(Temp=0;Ptr;Ptr=Ptr->Next)
		if(Ptr->Home);
		else if(Temp<Ptr->Size)
			Temp=Ptr->Size;
		else;

	return Temp;
}
static memc_mn *xMemC_MN_Search_Node_(memc_mn *_R_ Node)
{
	if(Node--)
		if(Node->Home)
			if(Node->Home==Node->Home->Link.Self)
				return Node;
			else;
		else;
	else;

	return NULL;
}
static logical xMemC_MN_Borrow_(memc_mn _PL_ Node,ADDRESS Demand)
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

		return 1;
	}
	else
		return 0;
}
static general xMemC_MN_Attach_(memc_mn _PL_ Node)
{
	Node->Size+=sizeof(memc_mn);
	Node->Size+=Node->Next->Size;

	Node->Next=Node->Next->Next;
	if(Node->Next)
		Node->Next->Prev=Node;
	else;

	return;
}
static address xMemC_MN_Return_(memc_mn *_PL_ Node)
{
	address Return=0;

	if((*Node)->Prev)
		if((*Node)->Prev->Home);
		else
		{
			xMemC_MN_Attach_(*Node=(*Node)->Prev);
			Return++;
		}
	else;

	if((*Node)->Next)
		if((*Node)->Next->Home);
		else
		{
			xMemC_MN_Attach_(*Node);
			Return++;
		}
	else;

	(*Node)->Home=NULL;

	return Return;
}
static memc_l2 xMemC_ML_Search_Home_(memc_ml _PL_ ML,ADDRESS Demand)
{
	memc_ml *_R_ Here=ML;
	address Size=UINTPTR_MAX;
	memc_l2 Return={NULL,NULL};

	do
		if(Demand>Here->Size.Able)
			Here=Here->Link.Next;
		else
		{
			memc_mn _PL_ Node=(memc_mn*)(Here+1);

			if(xMemC_MN_Scan_(Node))
			{
				memc_mn _PL_ Temp=xMemC_MN_Search_Space_(Node,Demand);

				if(Temp)
					if(Size>Temp->Size)
					{
						Size=Temp->Size;
						Return.L[0]=Here;
						Return.L[1]=Temp;
					}
					else;
				else;

				Here=Here->Link.Next;
			}
			else
			{
				Return.L[1]=Return.L[0]=NULL;
				break;
			}
		}
	while(Here!=ML);

	return Return;
}
static general *xMemC_MN_Give_(memc_mn _PL_ _R_ Node,ADDRESS Demand)
{
	ADDRESS Margin=Node->Size;
	byte_08 _PL_ Return=memset(Node+1,0x6F,Margin);

	if(Demand<Margin)
		memset(Return+Demand,0x78,Margin-Demand);
	else;

	return Return;
}
static general xMemC_MN_Take_(memc_mn _PL_ _R_ Node) { memset(Node+1,0x58,Node->Size);return; }
static general *MemC_ML_Borrow_(memc_ml _PL_ _R_ ML,ADDRESS Demand)
{
	if(ML)
	{
		ADDRESS Margin=xMemC_MN_Margin_(Demand);

		if(Margin)
		{
			MEMC_L2 Select=xMemC_ML_Search_Home_(ML,Margin);

			if(Select.L[0])
			{
				memc_ml _PL_ Home=Select.L[0];
				memc_mn _PL_ Node=Select.L[1];
				ADDRESS Size=Node->Size;

				Node->Home=Home;

				if(xMemC_MN_Borrow_(Node,Margin))
					Acs_(address,Home->Size.Idle)-=sizeof(memc_mn);
				else
					Acs_(address,Home->Nums.Idle)--;

				if(Size==Home->Size.Able)
					Acs_(address,Home->Size.Able)=xMemC_MN_Search_Size_(Node);
				else;

				{
					Acs_(address,Home->Nums.Used)++;
					Acs_(address,Home->Size.Idle)-=Margin;
					Acs_(address,Home->Size.Used)+=Margin;
				}

				return xMemC_MN_Give_(Node,Demand);
			}
			else;
		}
		else;
	}
	else;

	return NULL;
}
static logical xMemC_ML_Return_(general _PL_ Memory)
{
	memc_mn *Node=xMemC_MN_Search_Node_(Memory);

	if(Node)
	{
		memc_ml _PL_ _R_ Home=Node->Home;
		ADDRESS Size=Node->Size;
		ADDRESS Mode=xMemC_MN_Return_(&Node);

		Acs_(address,Home->Size.Idle)+=MemC_Size_(memc_mn,Mode);
		Acs_(address,Home->Size.Idle)+=Size;
		Acs_(address,Home->Size.Used)-=Size;

		Acs_(address,Home->Nums.Idle)-=Mode;
		Acs_(address,Home->Nums.Idle)++;
		Acs_(address,Home->Nums.Used)--;

		if(Home->Size.Able<Node->Size)
			Acs_(address,Home->Size.Able)=Node->Size;
		else;

		xMemC_MN_Take_(Node);

		return 1;
	}
	else
		return 0;
}
static logical MemC_ML_Kill_(memc_ml _PL_ ML)
{
	if(ML)
	{
		memc_ml *_R_ PtrML=ML;

		do
		{
			if(PtrML->Nums.Used)
			{
				memc_mn _PL_ _R_ PtrMN=(memc_mn*)(PtrML+1);

				PtrMN->Home=NULL;
				PtrMN->Prev=NULL;
				PtrMN->Next=NULL;
				PtrMN->Size=MemC_Size_(memc_mn,PtrML->Nums.Idle+PtrML->Nums.Used-1)+(PtrML->Size.Idle+PtrML->Size.Used);

				xMemC_MN_Take_(PtrMN);

				Acs_(address,PtrML->Size.Able)=PtrMN->Size;
				Acs_(address,PtrML->Size.Idle)=PtrMN->Size;
				Acs_(address,PtrML->Size.Used)=0;
				Acs_(address,PtrML->Nums.Idle)=1;
				Acs_(address,PtrML->Nums.Used)=0;
			}
			else;

			PtrML=PtrML->Link.Next;
		}
		while(PtrML!=ML);

		return 1;
	}
	else
		return 0;
}

static memc_ml *MemC_ML_Master_(MEMC_MN *_R_ Node)
{
	if(Node--)
	{
		memc_ml _PL_ _R_ Home=Node->Home;

		if(Home)
			if(Home==Home->Link.Self)
				return Home;
			else;
		else;
	}
	else;

	return NULL;
}
static address MemC_ML_Usable_(MEMC_MN *_R_ Node)
{
	if(Node--)
	{
		MEMC_ML _PL_ _R_ Home=Node->Home;

		if(Home)
			if(Home==Home->Link.Self)
				return Node->Size;
			else;
		else;
	}
	else;

	return 0;
}

#undef xMemC_ML_Free_
#undef xMemC_ML_Malloc_
#endif
#endif

#if(Fold_(Library Casing))
static_assert(sizeof(MEMCASE)==(sizeof(ADDRESS)<<6),"sizeof(MEMCASE) != 64*sizeof(ADDRESS)");
extern MEMCASE MemC=
{
	{
		.Version=Idiom.Version,
		.MaxDims=xMemC_Dims_,
		.Null.V=0,
		.Full.V=UINTPTR_MAX
	},
	{
		.Void_=MemC_Void_,
		.Just_=MemC_Just_
	},
	.Type=
	{
		{
			.N00=Idiom.Type.Desc+MemCTypeNone_00,
			.B08=Idiom.Type.Desc+MemCTypeByte_08,
			.Int=Idiom.Type.Desc+MemCTypeInteger,
			.Add=Idiom.Type.Desc+MemCTypeAddress
		},
		{
			.Enum_=MemC_DT_Enum_,
			.Desc_=MemC_DT_Desc_
		}
	},
	.Size=
	{
		.Add_=MemC_Size_Add_,
		.Sub_=MemC_Size_Sub_,
		.Mul_=MemC_Size_Mul_,
		.Div_=MemC_Size_Div_
	},
	{
		.Alloc=
		{
			.Byte_=MemC_Alloc_Byte_,
			.DN_=xMemC_Alloc_ND_
		},
		.Set=
		{
			.Check_=MemC_Check_,
			.Deloc_=MemC_Deloc_Set_
		}
	},
	{
		.Copy=
		{
			.DN_=xMemC_Copy_,
			.Step_=MemC_Copy_Step_
		},
		.Reform=
		{
			.DN_=xMemC_Reform_,
			.Shape_=MemC_Reform_Shape_
		},
		.Sort=
		{
			.Index_=MemC_Self_,
			.Do_=MemC_Sort_
		},
		.Preset.D1_=xMemC_Init_1D_,
		.Assign.D1_=xMemC_Assign_1D_
	},
	.MS=
	{
		{
			.Create_=MemC_MS_Create_,
			.Delete_=MemC_Func_Casting_(general,MemC_Delete_,memc_ms *_PL_ _R_),
			.Size_=MemC_MS_Size_,
			.Init_=MemC_MS_Init_
		},
		{
			.Null_=MemC_MS_Null_,
			.Dims_=MemC_MS_Dims_
		}
	},
	.MC=
	{
		{
			.Create_=MemC_MC_Create_,
			.Delete_=MemC_Func_Casting_(general,MemC_Delete_,memc_mc *_PL_ _R_),
			.Size_=MemC_MC_Size_,
			.Fill_=MemC_MC_Fill_
		},
		{
			.Change_=MemC_MC_Change_,
			.Form_=MemC_MC_Form_
		}
	},
	.ML=
	{
		{
			.Create_=MemC_ML_Create_,
			.Delete_=MemC_ML_Delete_,
			.Size_=MemC_ML_Size_,
			.Kill_=MemC_ML_Kill_
		},
		{
			.Borrow_=MemC_ML_Borrow_,
			.Return_=xMemC_ML_Return_
		},
		{
			.Master_=MemC_Func_Casting_(memc_ml*,MemC_ML_Master_,GENERAL _PL_),
			.Usable_=MemC_Func_Casting_(address,MemC_ML_Usable_,GENERAL _PL_)
		}
	}
};
extern MEMCASE *MemC_(general) { return &MemC; }
#endif
