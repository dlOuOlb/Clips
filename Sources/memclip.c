#include "memclip.h"

#if(MemC_Fold_(Definition:Global Constants))
static const char IdiomVersion[16]="Date:2018.03.13";
static const size_t ConstantZero[MemC_Copy_Max_Dimension]={0};
#ifdef __OPENCL_H
static const char ConstantArgType[8]={'G','L','H','F'};
#endif
const char _PL_ MemClip=IdiomVersion;
const void _PL_ MemCrux=&MemCrux;
#endif

#if(MemC_Fold_(Definition:Memory Functions))
int MemC_Check_(const void _PL_ *Memory,const size_t Sets)
{
	int Success;

	if(Memory)
	{
		const void _PL_ _PL_ End=Memory+Sets;

		for(;Memory<End;Memory++)
			if(!(*Memory))
				break;

		if(Memory==End)
			Success=1;
		else
			Success=0;
	}
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
static const void **_MemC_Assign_(const void **High,const size_t NumberHigh,const size_t SizeStep)
{
	const void **End=High+NumberHigh;
	const char *PtrL=(char*)End;

	for(;High<End;High++,PtrL+=SizeStep)
		(*High)=PtrL;

	return End;
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
				{
					const void **PointerM=Memory;

					Temporary=Size[0];
					for(PtrS=Size+1;PtrS<End;PtrS++)
					{
						PointerM=_MemC_Assign_(PointerM,Temporary,(*PtrS)*sizeof(void*));
						Temporary*=(*PtrS);
					}
					if(PtrS==End)
						PointerM=_MemC_Assign_(PointerM,Temporary,(*PtrS)*SizeElement);
				}
			}
		}

	return Memory;
}

void *Byte_Alloc_(const size_t S)
{
	const size_t T=sizeof(size_t);
	const size_t N=(S+T-1)/T;

	return malloc(N*T);
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
errno_t _MemC_Copy_(const void _PL_ MemoryS,void _PL_ MemoryT,const size_t _PL_ OriginS,const size_t _PL_ OriginT,const size_t _PL_ Length,const size_t _PL_ ShapeS,const size_t _PL_ ShapeT,const size_t Dimensions,const size_t Bytes)
{
	const size_t _PL_ OffsetS=(OriginS)?(OriginS):(ConstantZero);
	const size_t _PL_ OffsetT=(OriginT)?(OriginT):(ConstantZero);
	errno_t ErrorCode=EINVAL;

	switch(Dimensions)
	{
	case 0:
		break;
	case 1:
		{
			const size_t Copy=Length[0]*Bytes;

			ErrorCode=memcpy_s(((char*)MemoryT)+(OffsetT[0]*Bytes),Copy,((char*)MemoryS)+(OffsetS[0]*Bytes),Copy);
		}
		break;
	default:
		if(Dimensions<=MemC_Copy_Max_Dimension)
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
	}

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

cl_int _Devi_Copy_1D_(cl_command_queue const Queue,void _PL_ MemoryS,void _PL_ MemoryT,const size_t OriginS,const size_t OriginT,const size_t Length,const size_t Bytes,DEVI_CP Mode)
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
		ErrorCode=CL_INVALID_VALUE;;
	}

	return ErrorCode;
}
cl_int _Devi_Copy_(cl_command_queue const Queue,void _PL_ MemoryS,void _PL_ MemoryT,const size_t _PL_ OriginS,const size_t _PL_ OriginT,const size_t _PL_ Length,const size_t _PL_ ShapeS,const size_t _PL_ ShapeT,const cl_uint Dimensions,const size_t Bytes,DEVI_CP Mode)
{
	const size_t _PL_ ShapeSValid=(ShapeS)?(ShapeS):(Length);
	const size_t _PL_ ShapeTValid=(ShapeT)?(ShapeT):(Length);
	cl_int ErrorCode=CL_INVALID_VALUE;
	
	switch(Dimensions)
	{
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
#endif
#endif
