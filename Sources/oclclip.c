#define __STDC_WANT_LIB_EXT1__ (1)
#include "oclclip.h"

static const struct { BYTE_08 Version[16]; }Idiom={.Version=oOCLCLIP_INC_};

#ifdef __OPENCL_H
static OCLC_MP ConstantZero={0};

#if(Fold_(Static Assertions))
static_assert(OCLCPinAxes==4,"The pin must be 4D.");
static_assert(CLSuccess==0,"CLSuccess != 0");
static_assert((sizeof(struct _oclc_em_device_info)%sizeof(address))==0,"Structure Misalign");
static_assert(sizeof(cl_mem)==sizeof(address),"sizeof(cl_mem) != sizeof(address)");
static_assert(sizeof(cl_int)==sizeof(oclc_ef),"sizeof(cl_int) != sizeof(oclc_ef)");
#endif

#if(Fold_(OCLCrux Macros))
#define OCLC_TXX_(Type,Bits) Conc_(Type,Bits)

#define OCLC_Type_(Type,Bits) xOCLC_Type_(Type,Bits)
#define xOCLC_Type_(Type,Bits) Type##_##Bits

#define OCLC_Func_(Name,Suffix) xOCLC_Func_(Name,Suffix)
#define xOCLC_Func_(Name,Suffix) Name##Suffix##_
#endif

#if(Fold_(Environment Manager))
static general OCLC_EM_Delete_(oclc_em *_PL_ _R_ EM)
{
	if(*EM)
	{
		if((*EM)->Platform.List)
		{
			const struct _oclc_em_platform _PL_ EndP=((*EM)->Platform.List)+((*EM)->Platform.Nums);

			for(struct _oclc_em_platform *_R_ PtrP=(struct _oclc_em_platform*)((*EM)->Platform.List);PtrP<EndP;PtrP++)
			{
				if(PtrP->Device.List)
				{
					const struct _oclc_em_device _PL_ EndD=(PtrP->Device.List)+(PtrP->Device.Nums);

					for(struct _oclc_em_device *_R_ PtrD=(struct _oclc_em_device*)(PtrP->Device.List);PtrD<EndD;PtrD++)
						if(PtrD->Queue)
						{
							clFinish(PtrD->Queue);
							clReleaseCommandQueue(PtrD->Queue);
						}
						else;
				}
				else;

				if(PtrP->Context)
					clReleaseContext(PtrP->Context);
				else;
			}
		}
		else;

		MemC_Deloc_(*EM);
	}
	else;

	return;
}
static oclc_em *OCLC_EM_Create_(cl_int _PL_ _R_ Error)
{
	oclc_em *EM=NULL;

	if(*Error==CL_SUCCESS)
	{
		cl_uint PlatformNums;

		if((*Error=clGetPlatformIDs(0,NULL,&PlatformNums))==CL_SUCCESS)
		{
			cl_platform_id *_R_ PlatformList=MemC.Alloc.Byte_(MemC.Size.Mul_(PlatformNums,sizeof(cl_platform_id)+sizeof(address)+sizeof(cl_uint)));

			if(PlatformList)
				if((*Error=clGetPlatformIDs(PlatformNums,PlatformList,NULL))==CL_SUCCESS)
				{
					address LengthSums=0,_PL_ _R_ PlatformLngs=(address*)(PlatformList+PlatformNums);
					cl_uint DeviceSums=0,_PL_ _R_ DeviceNums=(cl_uint*)(PlatformLngs+PlatformNums);

					for(cl_uint Idx=0;Idx<PlatformNums;Idx++)
						if((*Error=clGetPlatformInfo(PlatformList[Idx],CL_PLATFORM_NAME,0,NULL,PlatformLngs+Idx))==CL_SUCCESS)
							if((*Error=clGetDeviceIDs(PlatformList[Idx],CL_DEVICE_TYPE_ALL,0,NULL,DeviceNums+Idx))==CL_SUCCESS)
							{
								LengthSums+=PlatformLngs[Idx];
								DeviceSums+=DeviceNums[Idx];
							}
							else goto ESCAPE_PLATFORM;
						else goto ESCAPE_PLATFORM;

					{
						cl_device_id *_R_ DeviceList=MemC.Alloc.Byte_(MemC.Size.Mul_(DeviceSums,sizeof(cl_device_id)+sizeof(address)));

						if(DeviceList)
						{
							for(cl_uint Idx=0,Pin=0;Idx<PlatformNums;Idx++)
								if((*Error=clGetDeviceIDs(PlatformList[Idx],CL_DEVICE_TYPE_ALL,DeviceNums[Idx],DeviceList+Pin,NULL))==CL_SUCCESS)
									Pin+=DeviceNums[Idx];
								else goto ESCAPE_DEVICE;

							{
								address _PL_ _R_ DeviceLngs=(address*)(DeviceList+DeviceSums);
								cl_uint WorkSums=0;

								for(cl_uint Idx=0,WorkNums;Idx<DeviceSums;Idx++)
								{
									if((*Error=clGetDeviceInfo(DeviceList[Idx],CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,sizeof(cl_uint),&WorkNums,NULL))==CL_SUCCESS)
										WorkSums+=WorkNums;
									else goto ESCAPE_DEVICE;

									if((*Error=clGetDeviceInfo(DeviceList[Idx],CL_DEVICE_NAME,0,NULL,DeviceLngs+Idx))==CL_SUCCESS)
										LengthSums+=DeviceLngs[Idx];
									else goto ESCAPE_DEVICE;
								}
								{
									address Size,Temp;

									Size=MemC.Size.Add_(LengthSums,sizeof(struct _oclc_em));
									if(Size);else goto ESCAPE_SIZE;

									Temp=MemC.Size.Mul_(PlatformNums,sizeof(struct _oclc_em_platform));
									if(Temp);else goto ESCAPE_SIZE;

									Size=MemC.Size.Add_(Size,Temp);
									if(Size);else goto ESCAPE_SIZE;

									Temp=MemC.Size.Mul_(DeviceSums,sizeof(struct _oclc_em_device));
									if(Temp);else goto ESCAPE_SIZE;

									Size=MemC.Size.Add_(Size,Temp);
									if(Size);else goto ESCAPE_SIZE;

									Temp=MemC.Size.Mul_(WorkSums,sizeof(address));
									if(Temp);else goto ESCAPE_SIZE;

									Size=MemC.Size.Add_(Size,Temp);
									if(Size);else goto ESCAPE_SIZE;

									EM=MemC.Alloc.Byte_(Size);
									if(EM);else goto ESCAPE_SIZE;

									MemC_Clear_Byte_(EM,Size);
								}
								{
									Acs_(address,EM->Platform.Nums)=PlatformNums;
									Acs_(struct _oclc_em_platform*,EM->Platform.List)=(struct _oclc_em_platform*)(EM+1);
								}
								{
									struct _oclc_em_device *DevicePin=(struct _oclc_em_device*)((EM->Platform.List)+(EM->Platform.Nums));
									address *WorkPin=(address*)(DevicePin+DeviceSums);
									text_08 *NamePin=(text_08*)(WorkPin+WorkSums);

									for(cl_uint IdxP=0,IdxL=0;IdxP<PlatformNums;IdxP++)
									{
										struct _oclc_em_platform _PL_ _R_ PtrP=(struct _oclc_em_platform*)(EM->Platform.List+IdxP);

										if((*Error=clGetPlatformInfo(PlatformList[IdxP],CL_PLATFORM_NAME,PlatformLngs[IdxP],NamePin,NULL))==CL_SUCCESS)
										{
											Acs_(cl_platform_id,PtrP->ID)=PlatformList[IdxP];
											Acs_(address,PtrP->Name.Size)=PlatformLngs[IdxP];
											Acs_(TEXT_08*,PtrP->Name.Data)=NamePin;
											NamePin+=PlatformLngs[IdxP];
										}
										else goto ESCAPE_CONTEXT;

										Acs_(cl_context,PtrP->Context)=clCreateContext(NULL,DeviceNums[IdxP],DeviceList+IdxL,NULL,NULL,Error);
										if(*Error==CL_SUCCESS)
										{
											Acs_(address,PtrP->Device.Nums)=DeviceNums[IdxP];
											Acs_(struct _oclc_em_device*,PtrP->Device.List)=DevicePin;
										}
										else goto ESCAPE_CONTEXT;

										for(cl_uint IdxD=0;IdxD<DeviceNums[IdxP];IdxD++,IdxL++)
										{
											struct _oclc_em_device _PL_ _R_ PtrD=(struct _oclc_em_device*)(PtrP->Device.List+IdxD);

											if((*Error=clGetDeviceInfo(DeviceList[IdxL],CL_DEVICE_NAME,DeviceLngs[IdxL],NamePin,NULL))==CL_SUCCESS)
											{
												Acs_(cl_device_id,PtrD->ID)=DeviceList[IdxL];
												Acs_(address,PtrD->Name.Size)=DeviceLngs[IdxL];
												Acs_(TEXT_08*,PtrD->Name.Data)=NamePin;
												NamePin+=DeviceLngs[IdxL];
											}
											else goto ESCAPE_CONTEXT;

											if((*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_ADDRESS_BITS,sizeof(cl_uint),(cl_uint*)&(PtrD->Info.AddressBits),NULL))==CL_SUCCESS);
											else goto ESCAPE_CONTEXT;

											if((*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_MAX_CLOCK_FREQUENCY,sizeof(cl_uint),(cl_uint*)&(PtrD->Info.MaxClockFrequency),NULL))==CL_SUCCESS);
											else goto ESCAPE_CONTEXT;

											if((*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_MAX_COMPUTE_UNITS,sizeof(cl_uint),(cl_uint*)&(PtrD->Info.MaxComputeUnits),NULL))==CL_SUCCESS);
											else goto ESCAPE_CONTEXT;

											if((*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,sizeof(cl_uint),(cl_uint*)&(PtrD->Info.MaxWorkItemDimensions),NULL))==CL_SUCCESS);
											else goto ESCAPE_CONTEXT;

											if((*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_GLOBAL_MEM_SIZE,sizeof(cl_ulong),(cl_ulong*)&(PtrD->Info.GlobalMemSize),NULL))==CL_SUCCESS);
											else goto ESCAPE_CONTEXT;

											if((*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_LOCAL_MEM_SIZE,sizeof(cl_ulong),(cl_ulong*)&(PtrD->Info.LocalMemSize),NULL))==CL_SUCCESS);
											else goto ESCAPE_CONTEXT;

											if((*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,sizeof(cl_ulong),(cl_ulong*)&(PtrD->Info.MaxConstantBufferSize),NULL))==CL_SUCCESS);
											else goto ESCAPE_CONTEXT;

											if((*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_MAX_MEM_ALLOC_SIZE,sizeof(cl_ulong),(cl_ulong*)&(PtrD->Info.MaxMemAllocSize),NULL))==CL_SUCCESS);
											else goto ESCAPE_CONTEXT;

											if((*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_MAX_WORK_GROUP_SIZE,sizeof(address),(address*)&(PtrD->Info.MaxWorkGroupSize),NULL))==CL_SUCCESS);
											else goto ESCAPE_CONTEXT;

											if((*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_MAX_WORK_ITEM_SIZES,MemC_Size_(address,PtrD->Info.MaxWorkItemDimensions),WorkPin,NULL))==CL_SUCCESS)
											{
												Acs_(address*,PtrD->Info.MaxWorkItemSizes)=WorkPin;
												WorkPin+=PtrD->Info.MaxWorkItemDimensions;
											}
											else goto ESCAPE_CONTEXT;

											Acs_(cl_command_queue,PtrD->Queue)=clCreateCommandQueueWithProperties(PtrP->Context,PtrD->ID,NULL,Error);
											if(*Error==CL_SUCCESS);else goto ESCAPE_CONTEXT;
										}
										DevicePin+=DeviceNums[IdxP];
									}
									goto ESCAPE_DEVICE;
								}
ESCAPE_CONTEXT:
								OCLC_EM_Delete_(&EM);
							}
						}
						else
ESCAPE_SIZE:
							*Error=CL_OUT_OF_HOST_MEMORY;
ESCAPE_DEVICE:
						MemC_Deloc_(DeviceList);
					}
				}
				else;
			else
				*Error=CL_OUT_OF_HOST_MEMORY;
ESCAPE_PLATFORM:
			MemC_Deloc_(PlatformList);
		}
		else;
	}
	else;

	return EM;
}

static cl_context OCLC_EM_Context_(OCLC_EM _PL_ _R_ EM,ADDRESS PSelect)
{
	if(EM)
		if(PSelect<EM->Platform.Nums)
			return EM->Platform.List[PSelect].Context;
		else;
	else;

	return NULL;
}
static cl_command_queue OCLC_EM_Queue_(OCLC_EM _PL_ _R_ EM,ADDRESS PSelect,ADDRESS DSelect)
{
	if(EM)
		if(PSelect<EM->Platform.Nums)
			if(DSelect<EM->Platform.List[PSelect].Device.Nums)
				return EM->Platform.List[PSelect].Device.List[DSelect].Queue;
			else;
		else;
	else;

	return NULL;
}
#endif

#if(Fold_(Program Manager))
static general OCLC_PM_Delete_(oclc_pm *_PL_ _R_ PM)
{
	if(*PM)
	{
		if((*PM)->Program.Kernel.List)
		{
			const struct _oclc_pm_kernel _PL_ EndK=((*PM)->Program.Kernel.List)+((*PM)->Program.Kernel.Nums.Total);

			for(struct _oclc_pm_kernel *_R_ PtrK=(struct _oclc_pm_kernel*)((*PM)->Program.Kernel.List);PtrK<EndK;PtrK++)
				if(PtrK->ID)
					clReleaseKernel(PtrK->ID);
				else;
		}
		else;

		if((*PM)->Program.ID)
			clReleaseProgram((*PM)->Program.ID);
		else;

		MemC_Deloc_(*PM);
	}
	else;

	return;
}
static oclc_pm *OCLC_PM_Create_(GENERAL _PL_ Origin,OCLC_MD _PL_ _R_ KernelList,ADDRESS KernelNums)
{
	oclc_pm *PM=NULL;

	if(KernelNums)
	{
		address Size=MemC.Size.Mul_(KernelNums,sizeof(struct _oclc_pm_kernel));

		if(Size)
		{
			Size=MemC.Size.Add_(Size,sizeof(struct _oclc_pm));
			if(Size);else goto ESCAPE;

			for(address Idx=0;Idx<KernelNums;Idx++)
			{
				Size=MemC.Size.Add_(Size,KernelList[Idx].Size);
				if(Size);else goto ESCAPE;
			}

			PM=MemC.Alloc.Byte_(Size);
			if(PM)
				MemC_Clear_Byte_(PM,Size);
			else goto ESCAPE;
		}
		else goto ESCAPE;
	}
	else goto ESCAPE;

	Acs_(address,PM->Program.Kernel.Nums.Total)=KernelNums;
	Acs_(struct _oclc_pm_kernel*,PM->Program.Kernel.List)=(struct _oclc_pm_kernel*)(PM+1);
	{
		address Idx=0;

		for(text_08 *NamePin=(text_08*)((PM->Program.Kernel.List)+(PM->Program.Kernel.Nums.Total));Idx<PM->Program.Kernel.Nums.Total;Idx++)
			if(MemC_Copy_1D_(KernelList[Idx].Data,NamePin,KernelList[Idx].Size))
			{
				oclc_md _PL_ _R_ PtrN=(oclc_md*)&(PM->Program.Kernel.List[Idx].Name);

				PtrN->Size=KernelList[Idx].Size;
				PtrN->Data=NamePin;
				NamePin+=KernelList[Idx].Size;
			}
			else break;

		if(Idx==KernelNums)
			Acs_(GENERAL*,PM->Origin)=Origin;
		else
			OCLC_PM_Delete_(&PM);
	}
ESCAPE:
	return PM;
}
#define xOCLC_Build_
#include "oclcrux.c"
#undef xOCLC_Build_
static general OCLC_PM_Build_Log_(OCLC_PM _PL_ _R_ PM,FILE _PL_ _R_ Stream,cl_int _PL_ _R_ Error)
{
	if(*Error==CL_SUCCESS)
		if(PM)
		{
			const cl_program Program=PM->Program.ID;
			cl_uint DeviceNums;

			if((*Error=clGetProgramInfo(Program,CL_PROGRAM_NUM_DEVICES,sizeof(cl_uint),&DeviceNums,NULL))==CL_SUCCESS)
			{
				MemC_Temp_ND_(cl_device_id,DeviceTemp,*Error=CL_OUT_OF_HOST_MEMORY;,1,DeviceNums)
				{
					cl_device_id _PL_ _R_ DeviceList=DeviceTemp;

					if((*Error=clGetProgramInfo(Program,CL_PROGRAM_DEVICES,MemC_Size_(cl_device_id,DeviceNums),DeviceList,NULL))==CL_SUCCESS)
					{
						MemC_Unit_(PENC_SC,Next,.Capacity=2,.String.T08=(text_08[2]) { '\n','\0' });
						
						for(cl_uint Idx=0;Idx<DeviceNums;Idx++)
						{
							address Size;

							if((*Error=clGetDeviceInfo(DeviceList[Idx],CL_DEVICE_NAME,0,NULL,&Size))==CL_SUCCESS)
							{
								MemC_Temp_Byte_(NameTemp,Size,*Error=CL_OUT_OF_HOST_MEMORY;)
								{
									text_08 _PL_ Name=NameTemp;

									if((*Error=clGetDeviceInfo(DeviceList[Idx],CL_DEVICE_NAME,Size,Name,NULL))==CL_SUCCESS)
										if(PenC.Stream.Buffer.T08_(0,Stream,Size,Name))
											if(PenC.Stream.SC.T08_(0,Stream,Next));
											else
												*Error=CL_INVALID_HOST_PTR;
										else
											*Error=CL_INVALID_HOST_PTR;
									else;
								}

								if(*Error==CL_SUCCESS);else break;
							}
							else break;

							if((*Error=clGetProgramBuildInfo(Program,DeviceList[Idx],CL_PROGRAM_BUILD_LOG,0,NULL,&Size))==CL_SUCCESS)
							{
								MemC_Temp_Byte_(LogTemp,Size,*Error=CL_OUT_OF_HOST_MEMORY;)
								{
									text_08 _PL_ Log=LogTemp;

									if((*Error=clGetProgramBuildInfo(Program,DeviceList[Idx],CL_PROGRAM_BUILD_LOG,Size,Log,NULL))==CL_SUCCESS)
										if(PenC.Stream.Buffer.T08_(0,Stream,Size,Log))
											if(PenC.Stream.SC.T08_(0,Stream,Next));
											else
												*Error=CL_INVALID_HOST_PTR;
										else
											*Error=CL_INVALID_HOST_PTR;
									else;
								}

								if(*Error==CL_SUCCESS);else break;
							}
							else break;
						}
					}
					else;
				}
			}
			else;
		}
		else
			*Error=CL_INVALID_HOST_PTR;
	else;

	return;
}

static cl_kernel OCLC_PM_Kernel_(OCLC_PM _PL_ _R_ PM,ADDRESS KSelect)
{
	if(PM)
		if(KSelect<PM->Program.Kernel.Nums.Total)
			return PM->Program.Kernel.List[KSelect].ID;
		else;
	else;

	return NULL;
}
#endif

#if(Fold_(Memory Object))
static address OCLC_MO_Info_Size_(const cl_mem Memory,const cl_mem_info Flag,cl_int _PL_ _R_ Error)
{
	address Size=0;

	if(*Error==CL_SUCCESS)
		*Error=clGetMemObjectInfo(Memory,Flag,0,NULL,&Size);
	else;

	return Size;
}
static general OCLC_MO_Info_What_(const cl_mem Memory,const cl_mem_info Flag,general _PL_ What,ADDRESS Size,cl_int _PL_ _R_ Error)
{
	if(*Error==CL_SUCCESS)
		*Error=clGetMemObjectInfo(Memory,Flag,Size,What,NULL);
	else;

	return;
}

static cl_mem OCLC_MO_Create_Buffer_(const cl_context Context,ADDRESS Size,cl_int _PL_ _R_ Error)
{
	return ((*Error==CL_SUCCESS)?(clCreateBuffer(Context,CL_MEM_READ_WRITE,Size,NULL,Error)):(NULL));
}
static cl_mem OCLC_MO_Create_Sub_Buffer_(const cl_mem Buffer,ADDRESS Offset,ADDRESS Size,cl_int _PL_ _R_ Error)
{
	if(*Error==CL_SUCCESS)
	{
		const cl_buffer_region Region={.origin=Offset,.size=Size};

		return clCreateSubBuffer(Buffer,CL_MEM_READ_WRITE,CL_BUFFER_CREATE_TYPE_REGION,&Region,Error);
	}
	else
		return NULL;
}
static general OCLC_MO_Delete_(cl_mem _PL_ _R_ Mem)
{
	if(*Mem)
	{
		clReleaseMemObject(*Mem);
		*Mem=NULL;
	}
	else;

	return;
}
#endif

#if(Fold_(Memory Pin))
static logical OCLC_MP_Invalid_Offset_(OCLC_MP _PL_ Ofs,OCLC_MP _PL_ Shp)
{
	for(oclc_pa Idx=OCLCPinAxisN;Idx<OCLCPinAxes;Idx++)
		if(Ofs->S[Idx]>Shp->S[Idx])
			return 1;
		else;

	return 0;
}
static logical OCLC_MP_Invalid_Length_(OCLC_MP _PL_ Ofs,OCLC_MP _PL_ Lng,OCLC_MP _PL_ Shp)
{
	for(oclc_pa Idx=OCLCPinAxisN;Idx<OCLCPinAxes;Idx++)
		if(Lng->S[Idx])
		{
			ADDRESS Temp=Ofs->S[Idx]+Lng->S[Idx];

			if(Temp<Lng->S[Idx])
				return 1;
			else if(Temp>Shp->S[Idx])
				return 1;
			else;
		}
		else
			return 1;

	return 0;
}

static oclc_mp OCLC_MP_Length_1D_(ADDRESS LngX)
{
	oclc_mp Pin;

	Pin.N=1;
	Pin.Z=1;
	Pin.Y=1;
	Pin.X=LngX;

	return Pin;
}
static oclc_mp OCLC_MP_Length_2D_(ADDRESS LngY,ADDRESS LngX)
{
	oclc_mp Pin;

	Pin.N=1;
	Pin.Z=1;
	Pin.Y=LngY;
	Pin.X=LngX;

	return Pin;
}
static oclc_mp OCLC_MP_Length_3D_(ADDRESS LngZ,ADDRESS LngY,ADDRESS LngX)
{
	oclc_mp Pin;

	Pin.N=1;
	Pin.Z=LngZ;
	Pin.Y=LngY;
	Pin.X=LngX;

	return Pin;
}
static oclc_mp OCLC_MP_Length_4D_(ADDRESS LngN,ADDRESS LngZ,ADDRESS LngY,ADDRESS LngX)
{
	oclc_mp Pin;

	Pin.N=LngN;
	Pin.Z=LngZ;
	Pin.Y=LngY;
	Pin.X=LngX;

	return Pin;
}

static oclc_mp OCLC_MP_Offset_1D_(ADDRESS OfsX)
{
	oclc_mp Pin;

	Pin.N=0;
	Pin.Z=0;
	Pin.Y=0;
	Pin.X=OfsX;

	return Pin;
}
static oclc_mp OCLC_MP_Offset_2D_(ADDRESS OfsY,ADDRESS OfsX)
{
	oclc_mp Pin;

	Pin.N=0;
	Pin.Z=0;
	Pin.Y=OfsY;
	Pin.X=OfsX;

	return Pin;
}
static oclc_mp OCLC_MP_Offset_3D_(ADDRESS OfsZ,ADDRESS OfsY,ADDRESS OfsX)
{
	oclc_mp Pin;

	Pin.N=0;
	Pin.Z=OfsZ;
	Pin.Y=OfsY;
	Pin.X=OfsX;

	return Pin;
}
static oclc_mp OCLC_MP_Offset_4D_(ADDRESS OfsN,ADDRESS OfsZ,ADDRESS OfsY,ADDRESS OfsX)
{
	oclc_mp Pin;

	Pin.N=OfsN;
	Pin.Z=OfsZ;
	Pin.Y=OfsY;
	Pin.X=OfsX;

	return Pin;
}

static address OCLC_MP_Total_(OCLC_MP _PL_ _R_ Pin) { return (Pin->N*Pin->Z*Pin->Y*Pin->X); }
#endif

#if(Fold_(Platform ID))
static address OCLC_PI_Info_Size_(const cl_platform_id Platform,const cl_platform_info Flag,cl_int _PL_ _R_ Error)
{
	address Size=0;

	if(*Error==CL_SUCCESS)
		*Error=clGetPlatformInfo(Platform,Flag,0,NULL,&Size);
	else;

	return Size;
}
static general OCLC_PI_Info_What_(const cl_platform_id Platform,const cl_platform_info Flag,general _PL_ What,ADDRESS Size,cl_int _PL_ _R_ Error)
{
	if(*Error==CL_SUCCESS)
		*Error=clGetPlatformInfo(Platform,Flag,Size,What,NULL);
	else;

	return;
}
#endif

#if(Fold_(Device ID))
static address OCLC_DI_Info_Size_(const cl_device_id Device,const cl_device_info Flag,cl_int _PL_ _R_ Error)
{
	address Size=0;

	if(*Error==CL_SUCCESS)
		*Error=clGetDeviceInfo(Device,Flag,0,NULL,&Size);
	else;

	return Size;
}
static general OCLC_DI_Info_What_(const cl_device_id Device,const cl_device_info Flag,general _PL_ What,ADDRESS Size,cl_int _PL_ _R_ Error)
{
	if(*Error==CL_SUCCESS)
		*Error=clGetDeviceInfo(Device,Flag,Size,What,NULL);
	else;

	return;
}
#endif

#if(Fold_(Context Object))
static address OCLC_CO_Info_Size_(const cl_context Context,const cl_context_info Flag,cl_int _PL_ _R_ Error)
{
	address Size=0;

	if(*Error==CL_SUCCESS)
		*Error=clGetContextInfo(Context,Flag,0,NULL,&Size);
	else;

	return Size;
}
static general OCLC_CO_Info_What_(const cl_context Context,const cl_context_info Flag,general _PL_ What,ADDRESS Size,cl_int _PL_ _R_ Error)
{
	if(*Error==CL_SUCCESS)
		*Error=clGetContextInfo(Context,Flag,Size,What,NULL);
	else;

	return;
}
#endif

#if(Fold_(Queue Object))
static address OCLC_QO_Info_Size_(const cl_command_queue Queue,const cl_command_queue_info Flag,cl_int _PL_ _R_ Error)
{
	address Size=0;

	if(*Error==CL_SUCCESS)
		*Error=clGetCommandQueueInfo(Queue,Flag,0,NULL,&Size);
	else;

	return Size;
}
static general OCLC_QO_Info_What_(const cl_command_queue Queue,const cl_command_queue_info Flag,general _PL_ What,ADDRESS Size,cl_int _PL_ _R_ Error)
{
	if(*Error==CL_SUCCESS)
		*Error=clGetCommandQueueInfo(Queue,Flag,Size,What,NULL);
	else;

	return;
}

static general xOCLC_QO_Merge_(oclc_mp _PL_ _R_ SOfs,oclc_mp _PL_ _R_ TOfs,oclc_mp _PL_ _R_ Lng,oclc_mp _PL_ _R_ SShp,oclc_mp _PL_ _R_ TShp)
{
	if(((SOfs->Z)|((Lng->Z)^(SShp->Z)))|((TOfs->Z)|((Lng->Z)^(TShp->Z))));
	else
	{
		SOfs->Z=SOfs->N*SShp->Z;
		SOfs->N=0;

		TOfs->Z=TOfs->N*TShp->Z;
		TOfs->N=0;

		Lng->Z*=Lng->N;
		Lng->N=1;

		SShp->Z*=SShp->N;
		SShp->N=1;

		TShp->Z*=TShp->N;
		TShp->N=1;
	}

	return;
}
static general xOCLC_QO_Pin_Set_(OCLC_MP _PL_ _R_ LngPin,OCLC_MP _PL_ _R_ OfsPin,address _PL_ _R_ Step,address _PL_ _R_ Offset,ADDRESS TypeSize)
{
	Step[0]=LngPin->X*TypeSize;
	Step[1]=LngPin->Y*Step[0];

	Offset[0]=OfsPin->X*TypeSize;
	Offset[1]=OfsPin->Y;
	Offset[2]=(OfsPin->N*LngPin->Z)+OfsPin->Z;

	return;
}
static general xOCLC_QO_Pin_Length_(OCLC_MP _PL_ _R_ LngPin,address _PL_ _R_ Length,ADDRESS TypeSize)
{
	Length[0]=LngPin->X*TypeSize;
	Length[1]=LngPin->Y;
	Length[2]=LngPin->Z;

	return;
}
static cl_int xOCLC_QO_HtoD_(const cl_command_queue Queue,GENERAL _PL_ SrcMem,OCLC_MP _PL_ SrcOfs,OCLC_MP _PL_ SrcShp,const cl_mem TrgMem,OCLC_MP _PL_ TrgOfs,OCLC_MP _PL_ TrgShp,OCLC_MP _PL_ CpyLng,ADDRESS TypeSize)
{
	address SourceStep[2];
	address TargetStep[2];
	address SourceOffset[3];
	address TargetOffset[3];
	address CopyLength[3];
	cl_int Error=CL_SUCCESS;

	xOCLC_QO_Pin_Set_(SrcShp,SrcOfs,SourceStep,SourceOffset,TypeSize);
	xOCLC_QO_Pin_Set_(TrgShp,TrgOfs,TargetStep,TargetOffset,TypeSize);
	xOCLC_QO_Pin_Length_(CpyLng,CopyLength,TypeSize);

	for(address Idx=0;Idx<CpyLng->N;Idx++)
	{
		Error=clEnqueueWriteBufferRect(Queue,TrgMem,CL_NON_BLOCKING,TargetOffset,SourceOffset,CopyLength,TargetStep[0],TargetStep[1],SourceStep[0],SourceStep[1],SrcMem,0,NULL,NULL);
		if(Error==CL_SUCCESS)
		{
			SourceOffset[2]+=SrcShp->Z;
			TargetOffset[2]+=TrgShp->Z;
		}
		else break;
	}

	return Error;
}
static cl_int xOCLC_QO_DtoH_(const cl_command_queue Queue,const cl_mem SrcMem,OCLC_MP _PL_ SrcOfs,OCLC_MP _PL_ SrcShp,general _PL_ TrgMem,OCLC_MP _PL_ TrgOfs,OCLC_MP _PL_ TrgShp,OCLC_MP _PL_ CpyLng,ADDRESS TypeSize)
{
	address SourceStep[2];
	address TargetStep[2];
	address SourceOffset[3];
	address TargetOffset[3];
	address CopyLength[3];
	cl_int Error=CL_SUCCESS;

	xOCLC_QO_Pin_Set_(SrcShp,SrcOfs,SourceStep,SourceOffset,TypeSize);
	xOCLC_QO_Pin_Set_(TrgShp,TrgOfs,TargetStep,TargetOffset,TypeSize);
	xOCLC_QO_Pin_Length_(CpyLng,CopyLength,TypeSize);

	for(address Idx=0;Idx<CpyLng->N;Idx++)
	{
		Error=clEnqueueReadBufferRect(Queue,SrcMem,CL_NON_BLOCKING,SourceOffset,TargetOffset,CopyLength,SourceStep[0],SourceStep[1],TargetStep[0],TargetStep[1],TrgMem,0,NULL,NULL);
		if(Error==CL_SUCCESS)
		{
			SourceOffset[2]+=SrcShp->Z;
			TargetOffset[2]+=TrgShp->Z;
		}
		else break;
	}

	return Error;
}
static cl_int xOCLC_QO_DtoD_(const cl_command_queue Queue,const cl_mem SrcMem,OCLC_MP _PL_ SrcOfs,OCLC_MP _PL_ SrcShp,const cl_mem TrgMem,OCLC_MP _PL_ TrgOfs,OCLC_MP _PL_ TrgShp,OCLC_MP _PL_ CpyLng,ADDRESS TypeSize)
{
	address SourceStep[2];
	address TargetStep[2];
	address SourceOffset[3];
	address TargetOffset[3];
	address CopyLength[3];
	cl_int Error=CL_SUCCESS;

	xOCLC_QO_Pin_Set_(SrcShp,SrcOfs,SourceStep,SourceOffset,TypeSize);
	xOCLC_QO_Pin_Set_(TrgShp,TrgOfs,TargetStep,TargetOffset,TypeSize);
	xOCLC_QO_Pin_Length_(CpyLng,CopyLength,TypeSize);

	for(address Idx=0;Idx<CpyLng->N;Idx++)
	{
		Error=clEnqueueCopyBufferRect(Queue,SrcMem,TrgMem,SourceOffset,TargetOffset,CopyLength,SourceStep[0],SourceStep[1],TargetStep[0],TargetStep[1],0,NULL,NULL);
		if(Error==CL_SUCCESS)
		{
			SourceOffset[2]+=SrcShp->Z;
			TargetOffset[2]+=TrgShp->Z;
		}
		else break;
	}

	return Error;
}
static general OCLC_QO_Copy_(const cl_command_queue Queue,OCLC_CF Mode,OCLC_MH _PL_ _R_ Source,OCLC_MH _PL_ _R_ Target,OCLC_MP _PL_ _R_ CpyLng,cl_int _PL_ _R_ Error)
{
	if(*Error==CL_SUCCESS)
		if(Source->Type->SizeType==Target->Type->SizeType)
		{
			ADDRESS TypeSize=Source->Type->SizeType;
			oclc_mp FSrcOfs=(Source->Start)?(*(Source->Start)):(ConstantZero);
			oclc_mp FTrgOfs=(Target->Start)?(*(Target->Start)):(ConstantZero);
			oclc_mp FLng=*CpyLng;
			oclc_mp FSrcShp=(Source->Shape)?(*(Source->Shape)):(FLng);
			oclc_mp FTrgShp=(Target->Shape)?(*(Target->Shape)):(FLng);

			xOCLC_QO_Merge_(&FSrcOfs,&FTrgOfs,&FLng,&FSrcShp,&FTrgShp);

			if(OCLC_MP_Invalid_Offset_(&FSrcOfs,&FSrcShp))
				goto INVALID_VALUE;
			else if(OCLC_MP_Invalid_Offset_(&FTrgOfs,&FTrgShp))
				goto INVALID_VALUE;
			else if(OCLC_MP_Invalid_Length_(&FSrcOfs,&FLng,&FSrcShp))
				goto INVALID_VALUE;
			else if(OCLC_MP_Invalid_Length_(&FTrgOfs,&FLng,&FTrgShp))
				goto INVALID_VALUE;
			else switch(Mode)
			{
			case OCLCopyHtoH:
				if(MemC.Copy.DN_(Source->Memory,Target->Memory,FSrcOfs.S,FTrgOfs.S,FLng.S,FSrcShp.S,FTrgShp.S,4,TypeSize))
					break;
				else
					goto INVALID_VALUE;
			case OCLCopyHtoD:
				*Error=xOCLC_QO_HtoD_(Queue,Source->Memory,&FSrcOfs,&FSrcShp,Target->Memory,&FTrgOfs,&FTrgShp,&FLng,TypeSize);
				break;
			case OCLCopyDtoH:
				*Error=xOCLC_QO_DtoH_(Queue,(cl_mem)(Source->Memory),&FSrcOfs,&FSrcShp,Target->Memory,&FTrgOfs,&FTrgShp,&FLng,TypeSize);
				break;
			case OCLCopyDtoD:
				*Error=xOCLC_QO_DtoD_(Queue,(cl_mem)(Source->Memory),&FSrcOfs,&FSrcShp,Target->Memory,&FTrgOfs,&FTrgShp,&FLng,TypeSize);
				break;
			default:
				goto INVALID_VALUE;
			}
		}
		else
INVALID_VALUE:
			*Error=CL_INVALID_VALUE;
	else;

	return;
}

static oclc_mp xOCLC_QO_Jump_(OCLC_MP _PL_ _R_ Shape,ADDRESS TypeSize)
{
	oclc_mp Jump;

	Jump.X=TypeSize;
	Jump.Y=Shape->X*Jump.X;
	Jump.Z=Shape->Y*Jump.Y;
	Jump.N=Shape->Z*Jump.Z;

	return Jump;
}
static oclc_mp xOCLC_QO_Skip_(OCLC_MP _PL_ _R_ Offset,OCLC_MP _PL_ _R_ Jump)
{
	OCLC_MP Skip={.N=Offset->N*Jump->N,.Z=Offset->Z*Jump->Z,.Y=Offset->Y*Jump->Y,.X=Offset->X*Jump->X};

	return Skip;
}
static general xOCLC_QO_Flat_(oclc_mp _PL_ _R_ Ofs,oclc_mp _PL_ _R_ Lng,oclc_mp _PL_ _R_ Shp)
{
	for(oclc_pa Here=OCLCPinAxisZ;Here<OCLCPinAxes;Here++)
		if((Ofs->S[Here])|((Lng->S[Here])^(Shp->S[Here])));
		else
		{
			OCLC_PA Prev=Here-1;

			Ofs->S[Here]=Ofs->S[Prev]*Shp->S[Here];
			Ofs->S[Prev]=0;

			Lng->S[Here]*=Lng->S[Prev];
			Lng->S[Prev]=1;

			Shp->S[Here]*=Shp->S[Prev];
			Shp->S[Prev]=1;
		}

	return;
}
static general OCLC_QO_Fill_(const cl_command_queue Queue,GENERAL _PL_ Source,OCLC_MH _PL_ _R_ Target,OCLC_MP _PL_ _R_ SetLng,cl_int _PL_ _R_ Error)
{
	if(*Error==CL_SUCCESS)
	{
		oclc_mp VOfs=(Target->Start)?(*(Target->Start)):(ConstantZero);
		oclc_mp VLng=*SetLng;
		oclc_mp VShp=(Target->Shape)?(*(Target->Shape)):(VLng);

		xOCLC_QO_Flat_(&VOfs,&VLng,&VShp);

		if(OCLC_MP_Invalid_Offset_(&VOfs,&VShp))
			*Error=CL_INVALID_VALUE;
		else if(OCLC_MP_Invalid_Length_(&VOfs,&VLng,&VShp))
			*Error=CL_INVALID_VALUE;
		else
		{
			const cl_mem Memory=Target->Memory;
			ADDRESS Length=VLng.X*Target->Type->SizeType;
			OCLC_MP Jump=xOCLC_QO_Jump_(&VShp,Target->Type->SizeType);
			OCLC_MP Skip=xOCLC_QO_Skip_(&VOfs,&Jump);

			for(address IdxN=0,OfsN=Skip.N;IdxN<VLng.N;IdxN++,OfsN+=Jump.N)
				for(address IdxZ=0,OfsZ=OfsN+Skip.Z;IdxZ<VLng.Z;IdxZ++,OfsZ+=Jump.Z)
					for(address IdxY=0,OfsY=OfsZ+Skip.Y;IdxY<VLng.Y;IdxY++,OfsY+=Jump.Y)
					{
						*Error=clEnqueueFillBuffer(Queue,Memory,Source,Jump.X,OfsY+Skip.X,Length,0,NULL,NULL);
						if(*Error==CL_SUCCESS);else return;
					}
		}
	}
	else;

	return;
}

static general OCLC_QO_Wait_(const cl_command_queue Queue,cl_int _PL_ _R_ Error)
{
	if(*Error==CL_SUCCESS)
		*Error=clFinish(Queue);
	else;

	return;
}
#endif

#if(Fold_(Kernel Object))
static address OCLC_KO_Info_Size_(const cl_kernel Kernel,const cl_kernel_info Flag,cl_int _PL_ _R_ Error)
{
	address Size=0;

	if(*Error==CL_SUCCESS)
		*Error=clGetKernelInfo(Kernel,Flag,0,NULL,&Size);
	else;

	return Size;
}
static general OCLC_KO_Info_What_(const cl_kernel Kernel,const cl_kernel_info Flag,general _PL_ What,ADDRESS Size,cl_int _PL_ _R_ Error)
{
	if(*Error==CL_SUCCESS)
		*Error=clGetKernelInfo(Kernel,Flag,Size,What,NULL);
	else;

	return;
}

static general OCLC_KO_G_(const cl_kernel Kernel,const cl_uint Index,const cl_mem Memory,cl_int _PL_ _R_ Error)
{
	if(*Error==CL_SUCCESS)
		*Error=clSetKernelArg(Kernel,Index,sizeof(cl_mem),&Memory);
	else;

	return;
}
static general OCLC_KO_L_(const cl_kernel Kernel,const cl_uint Index,ADDRESS Size,cl_int _PL_ _R_ Error)
{
	if(*Error==CL_SUCCESS)
		*Error=clSetKernelArg(Kernel,Index,Size,NULL);
	else;

	return;
}
static general OCLC_KO_P_(const cl_kernel Kernel,const cl_uint Index,GENERAL _PL_ Value,ADDRESS ValueSize,cl_int _PL_ _R_ Error)
{
	if(*Error==CL_SUCCESS)
		*Error=clSetKernelArg(Kernel,Index,ValueSize,Value);
	else;

	return;
}
#endif
#endif

#if(Fold_(Library Casing))
static_assert(sizeof(OCLCASE)==sizeof(ADDRESS),"sizeof(OCLCASE) != sizeof(ADDRESS)");
extern OCLCASE OCLC={.Version=Idiom.Version};
extern OCLCASE *OCLC_(general) { return &OCLC; }
#ifdef __OPENCL_H
static_assert(sizeof(OCLC_CL)==(sizeof(ADDRESS)*50),"sizeof(OCLC_CL) != 50*sizeof(ADDRESS)");
extern OCLC_CL OCLCL=
{
	.EM=
	{
		.Create_=MemC_Func_Casting_(oclc_em*,OCLC_EM_Create_,oclc_ef _PL_ _R_),
		.Delete_=OCLC_EM_Delete_,
		.Select=
		{
			.Context_=OCLC_EM_Context_,
			.Queue_=OCLC_EM_Queue_
		}
	},
	.PM=
	{
		.Create_=OCLC_PM_Create_,
		.Build=
		{
			.Source=
			{
				.T08_=MemC_Func_Casting_(general,OCLC_PM_Build_T08_,oclc_pm _PL_ _R_,const cl_context,TEXT_08 _PL_ _R_,TEXT_08 _PL_ _PL_ _R_,const cl_uint,oclc_ef _PL_ _R_),
				.T16_=MemC_Func_Casting_(general,OCLC_PM_Build_T16_,oclc_pm _PL_ _R_,const cl_context,TEXT_08 _PL_ _R_,TEXT_16 _PL_ _PL_ _R_,const cl_uint,oclc_ef _PL_ _R_)
			},
			.Binary=
			{
				.T08_=MemC_Func_Casting_(general,OCLC_PM_Load_T08_,oclc_pm _PL_ _R_,const cl_context,TEXT_08 _PL_ _R_,TEXT_08 _PL_ _PL_ _R_,oclc_ef _PL_ _R_),
				.T16_=MemC_Func_Casting_(general,OCLC_PM_Load_T16_,oclc_pm _PL_ _R_,const cl_context,TEXT_08 _PL_ _R_,TEXT_16 _PL_ _PL_ _R_,oclc_ef _PL_ _R_)
			},
			.Save=
			{
				.T08_=MemC_Func_Casting_(general,OCLC_PM_Save_T08_,OCLC_PM _PL_ _R_,TEXT_08 _PL_ _PL_ _R_,oclc_ef _PL_ _R_),
				.T16_=MemC_Func_Casting_(general,OCLC_PM_Save_T16_,OCLC_PM _PL_ _R_,TEXT_16 _PL_ _PL_ _R_,oclc_ef _PL_ _R_)
			},
			.Log_=MemC_Func_Casting_(general,OCLC_PM_Build_Log_,OCLC_PM _PL_ _R_,FILE _PL_ _R_,oclc_ef _PL_ _R_)
		},
		.Delete_=OCLC_PM_Delete_,
		.Select.Kernel_=OCLC_PM_Kernel_
	},
	.Platform.Info=
	{
		.Size_=MemC_Func_Casting_(address,OCLC_PI_Info_Size_,const cl_platform_id,const cl_platform_info,oclc_ef _PL_ _R_),
		.What_=MemC_Func_Casting_(general,OCLC_PI_Info_What_,const cl_platform_id,const cl_platform_info,general _PL_,ADDRESS,oclc_ef _PL_ _R_)
	},
	.Device.Info=
	{
		.Size_=MemC_Func_Casting_(address,OCLC_DI_Info_Size_,const cl_device_id,const cl_device_info,oclc_ef _PL_ _R_),
		.What_=MemC_Func_Casting_(general,OCLC_DI_Info_What_,const cl_device_id,const cl_device_info,general _PL_,ADDRESS,oclc_ef _PL_ _R_)
	},
	.Context.Info=
	{
		.Size_=MemC_Func_Casting_(address,OCLC_CO_Info_Size_,const cl_context,const cl_context_info,oclc_ef _PL_ _R_),
		.What_=MemC_Func_Casting_(general,OCLC_CO_Info_What_,const cl_context,const cl_context_info,general _PL_,ADDRESS,oclc_ef _PL_ _R_)
	},
	.Queue=
	{
		.Info=
		{
			.Size_=MemC_Func_Casting_(address,OCLC_QO_Info_Size_,const cl_command_queue,const cl_command_queue_info,oclc_ef _PL_ _R_),
			.What_=MemC_Func_Casting_(general,OCLC_QO_Info_What_,const cl_command_queue,const cl_command_queue_info,general _PL_,ADDRESS,oclc_ef _PL_ _R_)
		},
		.Fill_=MemC_Func_Casting_(general,OCLC_QO_Fill_,const cl_command_queue,GENERAL _PL_,OCLC_MH _PL_ _R_,OCLC_MP _PL_ _R_,oclc_ef _PL_ _R_),
		.Copy_=MemC_Func_Casting_(general,OCLC_QO_Copy_,const cl_command_queue,OCLC_CF,OCLC_MH _PL_ _R_,OCLC_MH _PL_ _R_,OCLC_MP _PL_ _R_,oclc_ef _PL_ _R_),
		.Wait_=MemC_Func_Casting_(general,OCLC_QO_Wait_,const cl_command_queue,oclc_ef _PL_ _R_)
	},
	.Kernel=
	{
		.Info=
		{
			.Size_=MemC_Func_Casting_(address,OCLC_KO_Info_Size_,const cl_kernel,const cl_kernel_info,oclc_ef _PL_ _R_),
			.What_=MemC_Func_Casting_(general,OCLC_KO_Info_What_,const cl_kernel,const cl_kernel_info,general _PL_,ADDRESS,oclc_ef _PL_ _R_)
		},
		.Arg=
		{
			.G_=MemC_Func_Casting_(general,OCLC_KO_G_,const cl_kernel,const cl_uint,const cl_mem,oclc_ef _PL_ _R_),
			.L_=MemC_Func_Casting_(general,OCLC_KO_L_,const cl_kernel,const cl_uint,ADDRESS,oclc_ef _PL_ _R_),
			.P_=MemC_Func_Casting_(general,OCLC_KO_P_,const cl_kernel,const cl_uint,GENERAL _PL_,ADDRESS,oclc_ef _PL_ _R_)
		}
	},
	.Memory=
	{
		.Info=
		{
			.Size_=MemC_Func_Casting_(address,OCLC_MO_Info_Size_,const cl_mem,const cl_mem_info,oclc_ef _PL_ _R_),
			.What_=MemC_Func_Casting_(general,OCLC_MO_Info_What_,const cl_mem,const cl_mem_info,general _PL_,ADDRESS,oclc_ef _PL_ _R_)
		},
		.Create=
		{
			.Buffer_=MemC_Func_Casting_(cl_mem,OCLC_MO_Create_Buffer_,const cl_context,ADDRESS,oclc_ef _PL_ _R_),
			.Sub_=MemC_Func_Casting_(cl_mem,OCLC_MO_Create_Sub_Buffer_,const cl_mem,ADDRESS,ADDRESS,oclc_ef _PL_ _R_)
		},
		.Delete_=OCLC_MO_Delete_
	},
	.MP=
	{
		.Length=
		{
			.D1_=OCLC_MP_Length_1D_,
			.D2_=OCLC_MP_Length_2D_,
			.D3_=OCLC_MP_Length_3D_,
			.D4_=OCLC_MP_Length_4D_
		},
		.Offset=
		{
			.D1_=OCLC_MP_Offset_1D_,
			.D2_=OCLC_MP_Offset_2D_,
			.D3_=OCLC_MP_Offset_3D_,
			.D4_=OCLC_MP_Offset_4D_
		},
		{
			.Zero=&(ConstantZero),
			.Total_=OCLC_MP_Total_,
			.Invalid=
			{
				.Length_=OCLC_MP_Invalid_Length_,
				.Offset_=OCLC_MP_Invalid_Offset_
			}
		}
	}
};
extern OCLC_CL *OCLCL_(general) { return &OCLCL; }
#else
extern GENERAL *OCLCL_(general) { return NULL; }
#endif
#endif
