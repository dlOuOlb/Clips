#include "memclip.h"

#if(MemC_Fold_(Definition:Global Constants))
static const char IdiomVersion[16]="Date:2018.06.08";
static const char IdiomAddress[8]="address";
static const size_t ConstantZero[MemC_Copy_Max_Dimension]={0};
#ifdef __OPENCL_H
static const char ConstantArgType[8]={'G','L','H','F'};
#endif
static MEMC_DT TypeAddress=MemC_DT_Define_(IdiomVersion,0,IdiomAddress,0,NULL,NULL,size_t);
const char _PL_ MemClip=IdiomVersion;
const void _PL_ MemCrux=&MemCrux;
MEMC_DT _PL_ MemCTypeAddress=&TypeAddress;
#endif

#if(MemC_Fold_(Definition:Memory Functions))
static int _MemC_Array_Non_Zero_(const size_t *MemC_Rst_ Ptr,const size_t Nums)
{
	const size_t _PL_ End=Ptr+Nums;

	while(Ptr<End)
		if(*Ptr)
			Ptr++;
		else
			break;

	return (Ptr==End);
}
static int _MemC_Array_All_Zero_(const size_t *MemC_Rst_ Ptr,const size_t Nums)
{
	const size_t _PL_ End=Ptr+Nums;

	while(Ptr<End)
		if(*Ptr)
			break;
		else
			Ptr++;

	return (Ptr==End);
}
static int _MemC_Array_Boundary_(const size_t *MemC_Rst_ Access,const size_t *MemC_Rst_ Bound,const size_t Count)
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
void MemC_Void_(void)
{}
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
	const size_t *MemC_Rst_ PtrS=Size;
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
		if(NumberDimension*SizeElement)
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
					_MemC_Assign_Loop_(Memory,Size,NumberDimension,SizeElement);
			}
		}

	return Memory;
}

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

		ErrorCode=Line_Copy_(Tile,Ptr,Copy,char);
		if(!ErrorCode)
		{
			for(Ptr+=Copy;Ptr<End;Copy<<=1)
			{
				ErrorCode=Line_Copy_(Memory,Ptr,Copy,char);
				if(ErrorCode)
					break;
				else
					Ptr+=Copy;
			}
			if(!ErrorCode)
			{
				Copy=Safe^NumberElement;
				Copy*=SizeElement;
				ErrorCode=Line_Copy_(Memory,Ptr,Copy,char);
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
		ErrorCode=memcpy_s(PtrO,SizeElement,PtrI,SizeElement);
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
		ErrorCode=memcpy_s(PtrO,SizeElement,PtrI,SizeElement);
		if(ErrorCode)
			break;
	}

	return ErrorCode;
}

static void _MemC_Jump_Offset_(size_t _PL_ Jump,const size_t _PL_ Shape,const size_t Dimension,const size_t Bytes)
{
	const size_t *MemC_Rst_ PointerS=Shape+(Dimension-2);
	size_t *MemC_Rst_ PointerJ=Jump+(Dimension-1);

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
		ErrorCode=memcpy_s(PointerT,Copy,PointerS,Copy);
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
			if(Bytes)
			{
				const size_t Copy=Length[0]*Bytes;

				ErrorCode=memcpy_s(((char*)MemoryT)+(OffsetT[0]*Bytes),Copy,((char*)MemoryS)+(OffsetS[0]*Bytes),Copy);
			}
			else
				ErrorCode=0;
			break;
		default:
			if(Bytes)
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
		}
	else
		ErrorCode=EINVAL;

	return ErrorCode;
}

size_t _Line_Assign_(void _PL_ Indexer,const void _PL_ Indexed,const size_t Interval,const size_t Indices,const size_t TypeSize,const int Mode)
{
	size_t Sum;

	if(Indices)
	{
		const char _PL_ _PL_ End=(char**)Indexer+Indices;
		char **MemC_Rst_ PointerO=Indexer;

		{
			PointerO[0]=(char*)Indexed;
			PointerO++;
		}
		if(Mode)
		{
			const size_t *MemC_Rst_ PointerS=(size_t*)Interval;

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

#if(MemC_Fold_(Definition:MemClip Structure Functions))
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
					MemC_Acs_(const void*,MS->ID)=ID;
					MemC_Acs_(MEMC_DT*,MS->Type)=MemCTypeAddress;
					MemC_Acs_(size_t,MS->Nums)=Slots;
					MemC_Acs_(size_t*,MS->Slot.V)=Line_Clear_(MS+1,Slots,size_t);
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
			MemC_Acs_(const void*,MS->ID)=ID;
			MemC_Acs_(MEMC_DT*,MS->Type)=MemCTypeAddress;
			MemC_Acs_(size_t,MS->Nums)=0;
			MemC_Acs_(size_t*,MS->Slot.V)=NULL;
		}
	}

	return MS;
}
void MemC_MS_Delete_(memc_ms *_PL_ MS)
{
	MemC_Deloc_(*MS);
}
int MemC_MS_Change_(MEMC_MS _PL_ MS,MEMC_DT _PL_ DT)
{
	if(MS)
		if(DT)
			if(DT->SizeType==sizeof(size_t))
			{
				MemC_Acs_(MEMC_DT*,MS->Type)=DT;
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

static size_t _MemC_Shape_Overflow_(const size_t _PL_ Shape,const size_t Dims)
{
	const size_t _PL_ End=Shape+Dims;
	const size_t *MemC_Rst_ Ptr=Shape;
	size_t Total=1;

	for(;Ptr<End;Ptr++)
		Total=_MemC_Overflow_Mul_(Total,*Ptr);

	return Total;
}
static size_t _MemC_Space_Required_(const size_t _PL_ Shape,const size_t Dims,const size_t SizeType)
{
	size_t Size[2];
	const size_t _PL_ Last=Shape+(Dims-1);
	const size_t *MemC_Rst_ Ptr=Shape;

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
							{
								size_t Size=_MemC_Overflow_Mul_(Dimensions,sizeof(size_t));

								if(Size)
								{
									Size=_MemC_Overflow_Add_(Size,sizeof(memc_mc));
									MC=Byte_Alloc_(Size);
									if(MC)
									{
										MemC_Acs_(const void*,MC->ID)=ID;
										MemC_Acs_(MEMC_DT*,MC->Type)=DT;
										MemC_Acs_(size_t,MC->Dims)=Dimensions;
										MemC_Acs_(size_t,MC->Unit)=DT->SizeType;
										MemC_Acs_(size_t*,MC->LngND)=(size_t*)(MC+1);
										MemC_Acs_(size_t,MC->Lng1D)=Lng1D;
										MemC_Acs_(void*,MC->AcsND)=NULL;
										MemC_Acs_(void*,MC->Acs1D)=NULL;

										if(Line_Copy_(Shape,(size_t*)(MC->LngND),Dimensions,size_t))
											MemC_Deloc_(MC);
									}
								}
								else
									goto ESCAPE;
							}
							break;
						case 0x7:
							{
								size_t Size[2];

								Size[0]=_MemC_Overflow_Mul_(Dimensions,sizeof(size_t));
								if(!(Size[0]))
									goto ESCAPE;

								Size[0]=_MemC_Overflow_Add_(Size[0],sizeof(memc_mc));
								if(!(Size[0]))
									goto ESCAPE;

								Size[1]=_MemC_Space_Required_(Shape,Dimensions,DT->SizeType);
								if(!(Size[1]))
									goto ESCAPE;

								Size[0]=_MemC_Overflow_Add_(Size[0],Size[1]);
								MC=Byte_Alloc_(Size[0]);
								if(MC)
								{
									MemC_Acs_(const void*,MC->ID)=ID;
									MemC_Acs_(MEMC_DT*,MC->Type)=DT;
									MemC_Acs_(size_t,MC->Dims)=Dimensions;
									MemC_Acs_(size_t,MC->Unit)=DT->SizeType;
									MemC_Acs_(size_t*,MC->LngND)=(size_t*)(MC+1);
									MemC_Acs_(size_t,MC->Lng1D)=Lng1D;
									MemC_Acs_(void*,MC->AcsND)=(void*)(MC->LngND+Dimensions);
									MemC_Acs_(void*,MC->Acs1D)=_MemC_Assign_Loop_((void**)(MC->AcsND),Shape,Dimensions,DT->SizeType);

									if(Line_Copy_(Shape,(size_t*)(MC->LngND),Dimensions,size_t))
										MemC_Deloc_(MC);
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
							MemC_Acs_(const void*,MC->ID)=ID;
							MemC_Acs_(MEMC_DT*,MC->Type)=DT;
							MemC_Acs_(size_t,MC->Dims)=0;
							MemC_Acs_(size_t,MC->Unit)=DT->SizeType;
							MemC_Acs_(size_t*,MC->LngND)=NULL;
							MemC_Acs_(size_t,MC->Lng1D)=0;
							MemC_Acs_(void*,MC->AcsND)=NULL;
							MemC_Acs_(void*,MC->Acs1D)=NULL;
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
int MemC_MC_Change_(MEMC_MC _PL_ MC,MEMC_DT _PL_ DT)
{
	if(MC)
		if(DT)
			if(DT->SizeType==MC->Unit)
			{
				MemC_Acs_(MEMC_DT*,MC->Type)=DT;
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

#if(MemC_Fold_(Definition:OpenCL Functions))
#ifdef __OPENCL_H
cl_mem _Devi_Create_Buffer_(cl_context const Context,const size_t Elements,const size_t SizeElement)
{
	return clCreateBuffer(Context,CL_MEM_READ_WRITE,Elements*SizeElement,NULL,NULL);
}
cl_mem _Devi_Create_Buffer_Sub_(cl_mem const Root,const size_t Offset,const size_t Elements,const size_t SizeElement)
{
	cl_buffer_region Info;

	{
		Info.origin=Offset*SizeElement;
		Info.size=Elements*SizeElement;
	}

	return clCreateSubBuffer(Root,CL_MEM_READ_WRITE,CL_BUFFER_CREATE_TYPE_REGION,&Info,NULL);
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

static void _Devi_Work_Global_(size_t *MemC_Rst_ GlobalWorkers,const size_t *MemC_Rst_ WorkGroups,const size_t *MemC_Rst_ LocalWorkers,const cl_uint Dimensions)
{
	const size_t _PL_ End=LocalWorkers+Dimensions;

	for(;LocalWorkers<End;LocalWorkers++,WorkGroups++,GlobalWorkers++)
		GlobalWorkers[0]=LocalWorkers[0]*WorkGroups[0];
}
cl_int Devi_Kenq_(cl_command_queue const Queue,cl_kernel const Kernel,const size_t _PL_ WorkGroups,const size_t _PL_ LocalWorkers,const size_t _PL_ GlobalOffset,const cl_uint Dimensions)
{
	cl_int ErrorCode=CL_INVALID_WORK_DIMENSION;

	if(Dimensions<=Devi_Copy_Max_Dimension)
	{
		size_t Total[Devi_Copy_Max_Dimension];

		_Devi_Work_Global_(Total,WorkGroups,LocalWorkers,Dimensions);
		ErrorCode=clEnqueueNDRangeKernel(Queue,Kernel,Dimensions,GlobalOffset,Total,LocalWorkers,0,NULL,NULL);
	}

	return ErrorCode;
}

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

						MemC_Acs_(cl_context,QC->Context)=Devi_Create_Context_(ListDevice+ChoiceDevice,1,&Error);
						if(QC->Context)
						{
							MemC_Acs_(cl_command_queue,QC->Queue)=Devi_Create_Queue_(QC->Context,ListDevice[ChoiceDevice],&Error);
							if(QC->Queue)
							{
								MemC_Acs_(cl_platform_id,QC->Platform)=ListPlatform[ChoicePlatform];
								MemC_Acs_(cl_device_id,QC->Device)=ListDevice[ChoiceDevice];
							}
							else
							{
								Devi_Delete_Context_(MemC_Acs_(cl_context,QC->Context));
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
		Devi_Delete_Queue_(MemC_Acs_(cl_command_queue,(*QC)->Queue));
		Devi_Delete_Context_(MemC_Acs_(cl_context,(*QC)->Context));
		MemC_Deloc_(*QC);
	}
}

devi_km *Devi_KM_Create_(cl_kernel const Kernel,const cl_uint Args,const cl_uint Dims)
{
	devi_km *KM;

	if(Dims)
		if(Dims<=Devi_Copy_Max_Dimension)
		{
			cl_uint Number;

			if(Devi_Info_Kernel_(Kernel,&Number,1,cl_uint,CL_KERNEL_NUM_ARGS)==CL_SUCCESS)
				if(Number==Args)
				{
					KM=Unit_Alloc_(devi_km);
					if(KM)
						if(Args)
						{
							const size_t StringLength=Args+1;

							MemC_Acs_(char*,KM->Flag)=Line_Alloc_(StringLength,char);
							if(KM->Flag)
							{
								const size_t Bulk=(Args+Dims)<<2;

								MemC_Acs_(size_t*,KM->WLocals)=Line_Alloc_(Bulk,size_t);
								if(KM->WLocals)
								{
									MemC_Acs_(cl_kernel,KM->Kernel)=Kernel;
									Line_Clear_((char*)(KM->Flag),StringLength,char);
									MemC_Acs_(void*,KM->Memory)=NULL;

									MemC_Acs_(size_t*,KM->WGroups)=Line_Clear_(KM->WLocals,Bulk,size_t)+Dims;
									MemC_Acs_(size_t*,KM->WOffset)=KM->WGroups+Dims;
									MemC_Acs_(size_t*,KM->WLength)=KM->WOffset+Dims;

									MemC_Acs_(size_t*,KM->TypeSize)=KM->WLength+Dims;
									MemC_Acs_(size_t*,KM->Elements)=(size_t*)(KM->TypeSize+Args);
									MemC_Acs_(size_t*,KM->ArgSize)=(size_t*)(KM->Elements+Args);
									MemC_Acs_(void**,KM->ArgAddress)=(void**)(KM->ArgSize+Args);

									MemC_Acs_(cl_uint,KM->KArgs)=Args;
									MemC_Acs_(cl_uint,KM->WDims)=Dims;
								}
								else
								{
									MemC_Deloc_(MemC_Acs_(char*,KM->Flag));
									MemC_Deloc_(KM);
								}
							}
							else
								MemC_Deloc_(KM);
						}
						else
						{
							const size_t Bulk=Dims<<2;

							MemC_Acs_(size_t*,KM->WLocals)=Line_Alloc_(Bulk,size_t);
							if(KM->WLocals)
							{
								MemC_Acs_(cl_kernel,KM->Kernel)=Kernel;
								MemC_Acs_(char*,KM->Flag)=(char*)&(KM->KArgs);
								MemC_Acs_(void*,KM->Memory)=NULL;

								MemC_Acs_(size_t*,KM->WGroups)=Line_Clear_(KM->WLocals,Bulk,size_t)+Dims;
								MemC_Acs_(size_t*,KM->WOffset)=KM->WGroups+Dims;
								MemC_Acs_(size_t*,KM->WLength)=KM->WOffset+Dims;

								MemC_Acs_(size_t*,KM->TypeSize)=NULL;
								MemC_Acs_(size_t*,KM->Elements)=NULL;
								MemC_Acs_(size_t*,KM->ArgSize)=NULL;
								MemC_Acs_(void**,KM->ArgAddress)=NULL;

								MemC_Acs_(cl_uint,KM->KArgs)=0;
								MemC_Acs_(cl_uint,KM->WDims)=Dims;
							}
							else
								MemC_Deloc_(KM);
						}
				}
				else
					KM=NULL;
			else
				KM=NULL;
		}
		else
			KM=NULL;
	else
		KM=NULL;

	return KM;
}
void Devi_KM_Delete_(devi_km *_PL_ KM)
{
	if(*KM)
	{
		if((*KM)->KArgs)
		{
			MemC_Deloc_(MemC_Acs_(void*,(*KM)->Memory));
			MemC_Deloc_(MemC_Acs_(char*,(*KM)->Flag));
		}
		{
			MemC_Deloc_(MemC_Acs_(size_t*,(*KM)->WLocals));
			MemC_Deloc_(*KM);
		}
	}
}

cl_int _Devi_KM_Type_(DEVI_KM _PL_ KM,const cl_uint Order,const size_t TypeSize,const int Mode)
{
	cl_int ErrorCode;

	if(KM)
		if(KM->Memory)
			ErrorCode=CL_INVALID_HOST_PTR;
		else
			if(Order<KM->KArgs)
			{
				((char*)(KM->Flag))[Order]=ConstantArgType[Mode&1];
				((size_t*)(KM->TypeSize))[Order]=TypeSize;

				ErrorCode=CL_SUCCESS;
			}
			else
				ErrorCode=CL_INVALID_ARG_INDEX;
	else
		ErrorCode=CL_INVALID_HOST_PTR;

	return ErrorCode;
}
cl_int Devi_KM_Init_(devi_km _PL_ KM)
{
	cl_int ErrorCode;

	if(KM)
		if(KM->KArgs)
			if(KM->Memory)
				ErrorCode=CL_INVALID_HOST_PTR;
			else
			{
				const char *PointerF=KM->Flag;
				const size_t *PointerS=KM->TypeSize;
				size_t SizeTotal=0;

				{
					const char _PL_ End=KM->Flag+KM->KArgs;

					for(ErrorCode=CL_SUCCESS;PointerF<End;PointerF++,PointerS++)
						switch(PointerF[0])
						{
						case 'G':
							SizeTotal+=PointerS[0];
							break;
						case 'L':
							break;
						default:
							ErrorCode=CL_INVALID_VALUE;
							goto ESCAPE;
						}
				}
ESCAPE:
				if(ErrorCode==CL_SUCCESS)
				{
					MemC_Acs_(void*,KM->Memory)=Byte_Alloc_(SizeTotal);
					if(KM->Memory)
					{
						const void _PL_ _PL_ End=KM->ArgAddress+(KM->KArgs-1);
						const void **PointerA=(void**)(KM->ArgAddress);

						for(PointerA[0]=Line_Clear_((void*)(KM->Memory),SizeTotal,char),PointerS=KM->TypeSize,PointerF=KM->Flag;PointerA<End;PointerA++,PointerS++,PointerF++)
							if(PointerF[0]==ConstantArgType[0])
								PointerA[1]=((char**)PointerA)[0]+PointerS[0];
							else
							{
								PointerA[1]=PointerA[0];
								PointerA[0]=NULL;
							}
						if(PointerF[0]==ConstantArgType[1])
							PointerA[0]=NULL;
					}
					else
						ErrorCode=CL_OUT_OF_HOST_MEMORY;
				}
			}
		else
			ErrorCode=CL_SUCCESS;
	else
		ErrorCode=CL_INVALID_HOST_PTR;

	return ErrorCode;
}

cl_int Devi_KM_Save_G_(DEVI_KM _PL_ KM,const cl_uint Order,const void _PL_ Value)
{
	cl_int ErrorCode;

	if(KM)
		if(KM->Memory)
			if(Order<KM->KArgs)
			{
				((size_t*)(KM->ArgSize))[Order]=KM->TypeSize[Order];
				Line_Copy_(Value,((void**)(KM->ArgAddress))[Order],KM->TypeSize[Order],char);

				ErrorCode=CL_SUCCESS;
			}
			else
				ErrorCode=CL_INVALID_VALUE;
		else
			ErrorCode=CL_INVALID_HOST_PTR;
	else
		ErrorCode=CL_INVALID_HOST_PTR;

	return ErrorCode;
}
cl_int Devi_KM_Save_L_(DEVI_KM _PL_ KM,const cl_uint Order,const size_t Elements)
{
	cl_int ErrorCode;

	if(KM)
		if(KM->Memory)
			if(Order<KM->KArgs)
			{
				((size_t*)(KM->ArgSize))[Order]=KM->TypeSize[Order]*Elements;
				MemC_Acs_(void**,KM->ArgAddress)[Order]=NULL;

				ErrorCode=CL_SUCCESS;
			}
			else
				ErrorCode=CL_INVALID_VALUE;
		else
			ErrorCode=CL_INVALID_HOST_PTR;
	else
		ErrorCode=CL_INVALID_HOST_PTR;

	return ErrorCode;
}
cl_int Devi_KM_Enqueue_(cl_command_queue const Queue,DEVI_KM _PL_ KM)
{
	cl_int ErrorCode;

	if(KM)
		if(KM->KArgs)
			if(KM->Memory)
			{
				cl_uint Index=0;

				for(ErrorCode=CL_SUCCESS;Index<KM->KArgs;Index++)
				{
					ErrorCode=Devi_Karg_(KM->Kernel,Index,KM->ArgAddress[Index],KM->ArgSize[Index]);
					if(ErrorCode!=CL_SUCCESS)
						break;
				}
				if(ErrorCode==CL_SUCCESS)
					ErrorCode=Devi_Kenq_(Queue,KM->Kernel,KM->WGroups,KM->WLocals,KM->WOffset,KM->WDims);
			}
			else
				ErrorCode=CL_INVALID_HOST_PTR;
		else
			ErrorCode=Devi_Kenq_(Queue,KM->Kernel,KM->WGroups,KM->WLocals,KM->WOffset,KM->WDims);
	else
		ErrorCode=CL_INVALID_HOST_PTR;

	return ErrorCode;
}

static size_t _Devi_BC_Length_Total_(const size_t *MemC_Rst_ Lng,const size_t Nums)
{
	const size_t _PL_ End=Lng+Nums;
	size_t Return=1;

	while(Lng<End)
	{
		Return=_MemC_Overflow_Add_(Return,*Lng);
		if(Return)
			Lng++;
		else
			goto ESCAPE;
	}
	Return--;
ESCAPE:
	return Return;
}
devi_bc *Devi_BC_Create_(const void _PL_ ID,const cl_context Context,MEMC_MS _PL_ MS,MEMC_DT _PL_ DT,const int Mode)
{
	devi_bc *BC;

	if(Context&&MS&&DT)
		if(MS->Slot.V)
		{
			int Flag;

			if(Mode)
				if(MS->Slot.V[0]<MS->Nums)
					if(_MemC_Array_All_Zero_(MS->Slot.V+1,MS->Slot.V[0]))
						Flag=0x1;
					else
						Flag=0x9;
				else
					goto ESCAPE;
			else
				if(MS->Nums<2)
					goto ESCAPE;
				else
					if(MS->Slot.V[1])
						Flag=0x8;
					else
						Flag=0x0;
			if(DT->SizeType)
				Flag|=0x2;
			if(MS->Slot.V[0])
				Flag|=0x4;

			switch(Flag)
			{
			case 0x0:
			case 0x1:
			case 0x2:
			case 0x3:
			case 0x8:
			case 0x9:
			case 0xA:
			case 0xB:
				BC=Unit_Alloc_(devi_bc);
				if(BC)
				{
					MemC_Acs_(const void*,BC->ID)=ID;
					MemC_Acs_(MEMC_DT*,BC->Type)=DT;
					MemC_Acs_(size_t,BC->Unit)=DT->SizeType;
					MemC_Acs_(size_t,BC->LngT)=0;
					MemC_Acs_(cl_mem,BC->BufT)=NULL;
					MemC_Acs_(size_t,BC->Nums)=0;
					MemC_Acs_(size_t*,BC->LngS)=NULL;
					MemC_Acs_(cl_mem*,BC->BufS)=NULL;
				}
				break;
			case 0x4:
			case 0x5:
			case 0x6:
			case 0x7:
			case 0xC:
			case 0xD:
				{
					size_t Total[2];

					if(Flag&0x8)
					{
						if(Flag&0x1)
							Total[0]=_Devi_BC_Length_Total_(MS->Slot.V+1,MS->Slot.V[0]);
						else
							Total[0]=_MemC_Overflow_Mul_(MS->Slot.V[1],MS->Slot.V[0]);
						if(!(Total[0]))
							goto ESCAPE;
					}
					else
						Total[0]=0;

					Total[1]=_MemC_Overflow_Mul_(MS->Slot.V[0],sizeof(size_t)<<1);
					if(Total[1])
					{
						Total[1]=_MemC_Overflow_Add_(Total[1],sizeof(devi_bc));
						BC=Byte_Alloc_(Total[1]);
						if(BC)
						{
							MemC_Acs_(const void*,BC->ID)=ID;
							MemC_Acs_(MEMC_DT*,BC->Type)=DT;
							MemC_Acs_(size_t,BC->Unit)=DT->SizeType;
							MemC_Acs_(size_t,BC->LngT)=Total[0];
							MemC_Acs_(cl_mem,BC->BufT)=NULL;
							MemC_Acs_(size_t,BC->Nums)=MS->Slot.V[0];
							MemC_Acs_(size_t*,BC->LngS)=(size_t*)(BC+1);
							MemC_Acs_(cl_mem*,BC->BufS)=Line_Clear_((cl_mem*)(BC->LngS+BC->Nums),BC->Nums,cl_mem);
							if(Flag&0x1)
							{
								if(Line_Copy_(MS->Slot.V+1,(size_t*)(BC->LngS),BC->Nums,size_t))
									MemC_Deloc_(BC);
							}
							else
								for(Total[1]=0;Total[1]<BC->Nums;Total[1]++)
									((size_t*)(BC->LngS))[Total[1]]=MS->Slot.V[1];
						}
					}
					else
						goto ESCAPE;
				}
				break;
			case 0xE:
			case 0xF:
				{
					const size_t Total=(Flag&0x1)?_Devi_BC_Length_Total_(MS->Slot.V+1,MS->Slot.V[0]):_MemC_Overflow_Mul_(MS->Slot.V[1],MS->Slot.V[0]);

					if(Total)
					{
						size_t Temp=_MemC_Overflow_Mul_(MS->Slot.V[0],sizeof(size_t)<<1);
						
						if(Temp)
						{
							Temp=_MemC_Overflow_Add_(Temp,sizeof(devi_bc));
							BC=Byte_Alloc_(Temp);
							if(BC)
							{
								{
									MemC_Acs_(size_t*,BC->LngS)=(size_t*)(BC+1);
									MemC_Acs_(cl_mem*,BC->BufS)=(cl_mem*)(BC->LngS+MS->Slot.V[0]);
									MemC_Acs_(cl_mem,BC->BufT)=_Devi_Create_Buffer_(Context,Total,DT->SizeType);
								}
								if(BC->BufT)
								{
									const cl_mem _PL_ End=BC->BufS+MS->Slot.V[0];
									cl_mem *MemC_Rst_ Ptr=(cl_mem*)(BC->BufS);
									size_t *MemC_Rst_ Lng=(size_t*)(BC->LngS);

									if(Flag&0x1)
									{
										if(!Line_Copy_(MS->Slot.V+1,Lng,MS->Slot.V[0],size_t))
											for(Temp=0;Ptr<End;Ptr++,Lng++)
												if(*Lng)
												{
													(*Ptr)=_Devi_Create_Buffer_Sub_(BC->BufT,Temp,*Lng,DT->SizeType);
													if(*Ptr)
														Temp+=(*Lng);
													else
														break;
												}
												else
													(*Ptr)=NULL;
									}
									else
										for(Temp=0;Ptr<End;Ptr++,Lng++,Temp+=MS->Slot.V[1])
										{
											(*Ptr)=_Devi_Create_Buffer_Sub_(BC->BufT,Temp,MS->Slot.V[1],DT->SizeType);
											if(*Ptr)
												(*Lng)=MS->Slot.V[1];
											else
												break;
										}
									if(Ptr==End)
									{
										MemC_Acs_(const void*,BC->ID)=ID;
										MemC_Acs_(MEMC_DT*,BC->Type)=DT;
										MemC_Acs_(size_t,BC->Unit)=DT->SizeType;
										MemC_Acs_(size_t,BC->LngT)=Total;
										MemC_Acs_(size_t,BC->Nums)=MS->Slot.V[0];
									}
									else
									{
										for(Ptr--;Ptr>=BC->BufS;Ptr--)
											Devi_Delete_Buffer_(*Ptr);
										Devi_Delete_Buffer_(MemC_Acs_(cl_mem,BC->BufT));
										MemC_Deloc_(BC);
									}
								}
								else
									MemC_Deloc_(BC);
							}
						}
						else
							goto ESCAPE;
					}
					else
						goto ESCAPE;
				}
				break;
			default:
				goto ESCAPE;
			}
		}
		else
			goto ESCAPE;
	else
	{
ESCAPE:
		BC=NULL;
	}

	return BC;
}
void Devi_BC_Delete_(devi_bc *_PL_ BC)
{
	if(*BC)
	{
		if((*BC)->BufT)
		{
			cl_mem *Ptr=(cl_mem*)((*BC)->BufS+(*BC)->Nums);

			for(Ptr--;Ptr>=(*BC)->BufS;Ptr--)
				Devi_Delete_Buffer_(*Ptr);
			Devi_Delete_Buffer_(MemC_Acs_(cl_mem,(*BC)->BufT));
		}
		MemC_Deloc_(*BC);
	}
}
#endif
#endif

#if(MemC_Fold_(Definition:MemClip Fused Functions))
static size_t _MemC_VC_Total_Length_(const size_t *MemC_Rst_ Ptr,const size_t Count)
{
	const size_t _PL_ End=Ptr+Count;
	size_t Length=1;

	for(;Ptr<End;Ptr++)
		Length*=(*Ptr);

	return Length;
}
static void *_MemC_VC_Access_(void *MemC_Rst_ Jumper,const size_t *MemC_Rst_ Access,const size_t Count)
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
	{
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

		if(VC)
		{
			MemC_Acs_(const void*,VC->ID)=ID;
			MemC_Acs_(MEMC_DT*,VC->Type)=MC->Type;
			MemC_Acs_(size_t,VC->Unit)=MC->Unit;
			MemC_Acs_(size_t,VC->Dims)=MC->Dims-MS->Slot.V[0];
			if(VC->Dims)
			{
				MemC_Acs_(const size_t*,VC->LngND)=MC->LngND+MS->Slot.V[0];
				MemC_Acs_(size_t,VC->Lng1D)=_MemC_VC_Total_Length_(VC->LngND,VC->Dims);
				if(MC->AcsND)
					MemC_Acs_(void*,VC->Hidden)=_MemC_VC_Access_((void*)(MC->AcsND),MS->Slot.V+1,MS->Slot.V[0]);
				else
					MemC_Acs_(void*,VC->Hidden)=NULL;
			}
			else
			{
				MemC_Acs_(size_t,VC->Lng1D)=0;
				MemC_Acs_(size_t*,VC->LngND)=NULL;
				MemC_Acs_(void*,VC->Hidden)=NULL;
			}
			MemC_Acs_(memc_df,VC->Domain.E)=MemCDomainHost;
		}
	}
	else
	{
ESCAPE:
		VC=NULL;
	}

	return VC;
}
#ifdef __OPENCL_H
memc_vc *Devi_VC_Create_(const void _PL_ ID,DEVI_BC _PL_ BC,MEMC_MS _PL_ MS)
{
	memc_vc *VC;

	if(BC)
	{
		if(MS)
			if(MS->Nums<2)
				goto ESCAPE;
			else
			{
				const size_t Index=MS->Slot.V[0];
				const size_t Dims=MS->Slot.V[1];
				const size_t _PL_ Shape=(MS->Nums>2)?(MS->Slot.V+2):(NULL);
				const void *Buffer;
				int Flag;

				if(Index<BC->Nums)
				{
					const size_t Temp=Dims+1;

					if(Temp<Dims)
						goto ESCAPE;
					else
						if(Temp<MS->Nums)
							Buffer=BC->BufS[Index];
						else
							goto ESCAPE;
				}
				else
					goto ESCAPE;

				if(Dims)
					if(BC->LngS[Index])
						if(_MemC_Array_Non_Zero_(Shape,Dims))
							if(_MemC_Shape_Overflow_(Shape,Dims)==BC->LngS[Index])
								Flag=0x2;
							else
								goto ESCAPE;
						else
							goto ESCAPE;
					else
						if(_MemC_Array_Non_Zero_(Shape,Dims))
							goto ESCAPE;
						else
							Flag=0x0;
				else
					if(BC->LngS[Index])
						goto ESCAPE;
					else
						Flag=0x0;

				if(BC->Unit)
					Flag|=0x1;

				switch(Flag)
				{
				case 0x0:
				case 0x1:
				case 0x2:
					if(Buffer)
						goto ESCAPE;
					else
						if(Dims)
						{
							size_t Temp=_MemC_Overflow_Mul_(Dims,sizeof(size_t));

							if(Temp)
							{
								Temp=_MemC_Overflow_Add_(Temp,sizeof(memc_vc));
								VC=Byte_Alloc_(Temp);
							}
							else
								goto ESCAPE;
						}
						else
							VC=Unit_Alloc_(memc_vc);
					if(VC)
					{
						MemC_Acs_(const void*,VC->ID)=ID;
						MemC_Acs_(MEMC_DT*,VC->Type)=BC->Type;
						MemC_Acs_(size_t,VC->Unit)=BC->Unit;
						MemC_Acs_(size_t,VC->Dims)=Dims;
						MemC_Acs_(size_t,VC->Lng1D)=BC->LngS[Index];
						MemC_Acs_(memc_df,VC->Domain.E)=MemCDomainDevice;
						MemC_Acs_(void*,VC->Hidden)=NULL;
						if(Dims)
						{
							MemC_Acs_(size_t*,VC->LngND)=(size_t*)(VC+1);
							if(Line_Copy_(Shape,(size_t*)(VC->LngND),Dims,size_t))
								MemC_Deloc_(VC);
						}
						else
							MemC_Acs_(size_t*,VC->LngND)=NULL;
					}
					break;
				case 0x3:
					if(Buffer)
					{
						size_t Temp=_MemC_Overflow_Mul_(Dims,sizeof(size_t));

						if(Temp)
						{
							Temp=_MemC_Overflow_Add_(Temp,sizeof(memc_vc));
							VC=Byte_Alloc_(Temp);
						}
						else
							goto ESCAPE;
					}
					else
						goto ESCAPE;
					if(VC)
					{
						MemC_Acs_(const void*,VC->ID)=ID;
						MemC_Acs_(MEMC_DT*,VC->Type)=BC->Type;
						MemC_Acs_(size_t,VC->Unit)=BC->Unit;
						MemC_Acs_(size_t,VC->Dims)=Dims;
						MemC_Acs_(size_t,VC->Lng1D)=BC->LngS[Index];
						MemC_Acs_(size_t*,VC->LngND)=(size_t*)(VC+1);
						MemC_Acs_(memc_df,VC->Domain.E)=MemCDomainDevice;
						MemC_Acs_(const void*,VC->Hidden)=Buffer;
						if(Line_Copy_(Shape,(size_t*)(VC->LngND),Dims,size_t))
							MemC_Deloc_(VC);
					}
					break;
				default:
					goto ESCAPE;
				}
			}
		else
			goto ESCAPE;
	}
	else
	{
ESCAPE:
		VC=NULL;
	}

	return VC;
}
#endif
void MemC_VC_Delete_(memc_vc *_PL_ VC)
{
	MemC_Deloc_(*VC);
}
int MemC_VC_Change_(MEMC_VC _PL_ VC,MEMC_DT _PL_ DT)
{
	if(VC)
		if(DT)
			if(DT->SizeType==VC->Unit)
			{
				MemC_Acs_(MEMC_DT*,VC->Type)=DT;
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
cl_mem Devi_VC_Member_Buf_(MEMC_VC _PL_ VC)
{
	return ((VC)?((VC->Domain.E==MemCDomainDevice)?((cl_mem)(VC->Hidden)):(NULL)):(NULL));
}
#endif

static size_t _Devi_VC_Offset_(const size_t *MemC_Rst_ Access,const size_t *MemC_Rst_ Length,const size_t Dig)
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

static int _MemC_VC_Copy_Bound_(const size_t *MemC_Rst_ Copy,const size_t *MemC_Rst_ Offset,const size_t *MemC_Rst_ Bound,const size_t Dims)
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
static void _MemC_VC_Copy_New_Size_(size_t _PL_ LengthNew,size_t _PL_ OffsetNew,const size_t *MemC_Rst_ OffsetData,const size_t *MemC_Rst_ LengthData,const size_t JumpData,const size_t DimsCopy)
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
				Line_Clear_(_MemC_VC_Direct_((void*)(VC->Hidden),VC->Dims-1),(VC->Lng1D)*(VC->Unit),char);
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
								const size_t Bytes=(Source->Lng1D)*(Source->Unit);

								if(Line_Copy_(MemoryS,MemoryT,Bytes,char))
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
