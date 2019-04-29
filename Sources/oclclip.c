#include "oclclip.h"

#if(Fold_(Definition:OCLClip Macros))
#define _OCLC_ static
#endif

#if(Fold_(Definition:OCLCrux Macros))
#define _OCLC_TXX_(Type,Bits) Type##Bits
#define OCLC_TXX_(Type,Bits) _OCLC_TXX_(Type,Bits)

#define _OCLC_Type_(Type,Bits) Type##_##Bits
#define OCLC_Type_(Type,Bits) _OCLC_Type_(Type,Bits)

#define _OCLC_Func_(Name,Suffix) Name##Suffix##_
#define OCLC_Func_(Name,Suffix) _OCLC_Func_(Name,Suffix)
#endif

#if(Fold_(Definition:Internal Constants))
static BYTE_08 IdiomVersion[16]="2019.04.26";
static OCLC_MP ConstantZero={.N=0,.Z=0,.Y=0,.X=0};
#endif

#if(Fold_(Part:Environment Manager))
_OCLC_ general OCLC_EM_Delete_(oclc_em *_PL_ EM)
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
				}
				if(PtrP->Context)
					clReleaseContext(PtrP->Context);
			}
		}

		MemC_Deloc_(*EM);
	}
}
_OCLC_ oclc_em *OCLC_EM_Create_(cl_int _PL_ Error)
{
	oclc_em *EM=NULL;

	if(*Error==CL_SUCCESS)
	{
		cl_uint PlatformNums=0;

		*Error=clGetPlatformIDs(0,NULL,&PlatformNums);
		if(*Error==CL_SUCCESS)
		{
			cl_platform_id *PlatformList=MemC.Alloc.Byte_(MemC.Size.Mul_(PlatformNums,sizeof(cl_platform_id)+sizeof(address)+sizeof(cl_uint)));

			if(PlatformList)
			{
				*Error=clGetPlatformIDs(PlatformNums,PlatformList,NULL);
				if(*Error==CL_SUCCESS)
				{
					address _PL_ PlatformLngs=(address*)(PlatformList+PlatformNums);
					cl_uint _PL_ DeviceNums=(cl_uint*)(PlatformLngs+PlatformNums);
					address LengthSums=0;
					cl_uint DeviceSums=0;

					for(cl_uint Idx=0;Idx<PlatformNums;Idx++)
					{
						*Error=clGetPlatformInfo(PlatformList[Idx],CL_PLATFORM_NAME,0,NULL,PlatformLngs+Idx);
						if(*Error==CL_SUCCESS)
						{
							*Error=clGetDeviceIDs(PlatformList[Idx],CL_DEVICE_TYPE_ALL,0,NULL,DeviceNums+Idx);
							if(*Error==CL_SUCCESS)
							{
								LengthSums+=PlatformLngs[Idx];
								DeviceSums+=DeviceNums[Idx];
							}
							else goto ESCAPE_PLATFORM;
						}
						else goto ESCAPE_PLATFORM;
					}
					if(*Error==CL_SUCCESS)
					{
						cl_device_id *DeviceList=MemC.Alloc.Byte_(MemC.Size.Mul_(DeviceSums,sizeof(cl_device_id)+sizeof(address)));

						if(DeviceList)
						{
							for(cl_uint Idx=0,Pin=0;Idx<PlatformNums;Idx++)
							{
								*Error=clGetDeviceIDs(PlatformList[Idx],CL_DEVICE_TYPE_ALL,DeviceNums[Idx],DeviceList+Pin,NULL);
								if(*Error==CL_SUCCESS)
									Pin+=DeviceNums[Idx];
								else goto ESCAPE_DEVICE;
							}
							if(*Error==CL_SUCCESS)
							{
								address _PL_ DeviceLngs=(address*)(DeviceList+DeviceSums);
								cl_uint WorkSums=0;

								for(cl_uint Idx=0,WorkNums;Idx<DeviceSums;Idx++)
								{
									*Error=clGetDeviceInfo(DeviceList[Idx],CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,sizeof(cl_uint),&WorkNums,NULL);
									if(*Error==CL_SUCCESS)
										WorkSums+=WorkNums;
									else goto ESCAPE_DEVICE;

									*Error=clGetDeviceInfo(DeviceList[Idx],CL_DEVICE_NAME,0,NULL,DeviceLngs+Idx);
									if(*Error==CL_SUCCESS)
										LengthSums+=DeviceLngs[Idx];
									else goto ESCAPE_DEVICE;
								}
								{
									address Size;
									address Temp;

									Size=MemC.Size.Add_(LengthSums,sizeof(struct _oclc_em));
									if(!Size) goto ESCAPE_SIZE;

									Temp=MemC.Size.Mul_(PlatformNums,sizeof(struct _oclc_em_platform));
									if(!Temp) goto ESCAPE_SIZE;

									Size=MemC.Size.Add_(Size,Temp);
									if(!Size) goto ESCAPE_SIZE;

									Temp=MemC.Size.Mul_(DeviceSums,sizeof(struct _oclc_em_device));
									if(!Temp) goto ESCAPE_SIZE;

									Size=MemC.Size.Add_(Size,Temp);
									if(!Size) goto ESCAPE_SIZE;

									Temp=MemC.Size.Mul_(WorkSums,sizeof(address));
									if(!Temp) goto ESCAPE_SIZE;

									Size=MemC.Size.Add_(Size,Temp);
									if(!Size) goto ESCAPE_SIZE;

									EM=MemC.Alloc.Byte_(Size);
									if(!EM) goto ESCAPE_SIZE;

									MemC_Clear_Byte_(EM,Size);
								}
								{
									Acs_(address,EM->Platform.Nums)=PlatformNums;
									Acs_(struct _oclc_em_platform*,EM->Platform.List)=(struct _oclc_em_platform*)(EM+1);
								}
								{
									struct _oclc_em_device *DevicePin=(struct _oclc_em_device*)((EM->Platform.List)+(EM->Platform.Nums));
									address *WorkPin=(address*)(DevicePin+DeviceSums);
									byte_08 *NamePin=(byte_08*)(WorkPin+WorkSums);

									for(cl_uint IdxP=0,IdxL=0;IdxP<PlatformNums;IdxP++)
									{
										struct _oclc_em_platform _PL_ PtrP=(struct _oclc_em_platform*)(EM->Platform.List+IdxP);
										oclc_md _PL_ NameP=(oclc_md*)&(PtrP->Name);

										Acs_(cl_platform_id,PtrP->ID)=PlatformList[IdxP];

										NameP->Size=PlatformLngs[IdxP];
										NameP->Data=NamePin;
										*Error=clGetPlatformInfo(PtrP->ID,CL_PLATFORM_NAME,NameP->Size,(byte_08*)(NameP->Data),NULL);
										if(*Error==CL_SUCCESS)
											NamePin+=PlatformLngs[IdxP];
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
											struct _oclc_em_device _PL_ PtrD=(struct _oclc_em_device*)(PtrP->Device.List+IdxD);

											Acs_(cl_device_id,PtrD->ID)=DeviceList[IdxL];
											{
												oclc_md _PL_ NameD=(oclc_md*)&(PtrD->Name);

												NameD->Size=DeviceLngs[IdxL];
												NameD->Data=NamePin;
												*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_NAME,NameD->Size,(byte_08*)(NameD->Data),NULL);
											}

											if(*Error==CL_SUCCESS)
												*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_ADDRESS_BITS,sizeof(cl_uint),(cl_uint*)&(PtrD->Info.AddressBits),NULL);
											else goto ESCAPE_CONTEXT;

											if(*Error==CL_SUCCESS)
												*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_MAX_CLOCK_FREQUENCY,sizeof(cl_uint),(cl_uint*)&(PtrD->Info.MaxClockFrequency),NULL);
											else goto ESCAPE_CONTEXT;

											if(*Error==CL_SUCCESS)
												*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_MAX_COMPUTE_UNITS,sizeof(cl_uint),(cl_uint*)&(PtrD->Info.MaxComputeUnits),NULL);
											else goto ESCAPE_CONTEXT;

											if(*Error==CL_SUCCESS)
												*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,sizeof(cl_uint),(cl_uint*)&(PtrD->Info.MaxWorkItemDimensions),NULL);
											else goto ESCAPE_CONTEXT;

											if(*Error==CL_SUCCESS)
												*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_GLOBAL_MEM_SIZE,sizeof(cl_ulong),(cl_ulong*)&(PtrD->Info.GlobalMemSize),NULL);
											else goto ESCAPE_CONTEXT;

											if(*Error==CL_SUCCESS)
												*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_LOCAL_MEM_SIZE,sizeof(cl_ulong),(cl_ulong*)&(PtrD->Info.LocalMemSize),NULL);
											else goto ESCAPE_CONTEXT;

											if(*Error==CL_SUCCESS)
												*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,sizeof(cl_ulong),(cl_ulong*)&(PtrD->Info.MaxConstantBufferSize),NULL);
											else goto ESCAPE_CONTEXT;

											if(*Error==CL_SUCCESS)
												*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_MAX_MEM_ALLOC_SIZE,sizeof(cl_ulong),(cl_ulong*)&(PtrD->Info.MaxMemAllocSize),NULL);
											else goto ESCAPE_CONTEXT;

											if(*Error==CL_SUCCESS)
												*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_MAX_WORK_GROUP_SIZE,sizeof(address),(address*)&(PtrD->Info.MaxWorkGroupSize),NULL);
											else goto ESCAPE_CONTEXT;

											if(*Error==CL_SUCCESS)
												Acs_(address*,PtrD->Info.MaxWorkItemSizes)=WorkPin;
											else goto ESCAPE_CONTEXT;

											*Error=clGetDeviceInfo(PtrD->ID,CL_DEVICE_MAX_WORK_ITEM_SIZES,MemC_Size_(address,PtrD->Info.MaxWorkItemDimensions),(address*)(PtrD->Info.MaxWorkItemSizes),NULL);
											if(*Error==CL_SUCCESS)
												WorkPin+=PtrD->Info.MaxWorkItemDimensions;
											else goto ESCAPE_CONTEXT;

											Acs_(cl_command_queue,PtrD->Queue)=clCreateCommandQueueWithProperties(PtrP->Context,PtrD->ID,NULL,Error);
											if(*Error==CL_SUCCESS)
												NamePin+=DeviceLngs[IdxL];
											else goto ESCAPE_CONTEXT;
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
						{
ESCAPE_SIZE:
							*Error=CL_OUT_OF_HOST_MEMORY;
						}
ESCAPE_DEVICE:
						MemC_Deloc_(DeviceList);
					}
				}
			}
			else
				*Error=CL_OUT_OF_HOST_MEMORY;
ESCAPE_PLATFORM:
			MemC_Deloc_(PlatformList);
		}
	}

	return EM;
}

_OCLC_ cl_context OCLC_EM_Context_(OCLC_EM _PL_ EM,ADDRESS PSelect)
{
	return ((EM)?((PSelect<EM->Platform.Nums)?(EM->Platform.List[PSelect].Context):(NULL)):(NULL));
}
_OCLC_ cl_command_queue OCLC_EM_Queue_(OCLC_EM _PL_ EM,ADDRESS PSelect,ADDRESS DSelect)
{
	return ((EM)?((PSelect<EM->Platform.Nums)?((DSelect<EM->Platform.List[PSelect].Device.Nums)?(EM->Platform.List[PSelect].Device.List[DSelect].Queue):(NULL)):(NULL)):(NULL));
}
#endif

#if(Fold_(Part:Program Manager))
_OCLC_ general OCLC_PM_Delete_(oclc_pm *_PL_ PM)
{
	if(*PM)
	{
		if((*PM)->Program.Kernel.List)
		{
			const struct _oclc_pm_kernel _PL_ EndK=((*PM)->Program.Kernel.List)+((*PM)->Program.Kernel.Nums.Total);

			for(struct _oclc_pm_kernel *_R_ PtrK=(struct _oclc_pm_kernel*)((*PM)->Program.Kernel.List);PtrK<EndK;PtrK++)
				if(PtrK->ID)
					clReleaseKernel(PtrK->ID);
		}
		if((*PM)->Program.ID)
			clReleaseProgram((*PM)->Program.ID);

		MemC_Deloc_(*PM);
	}
}
_OCLC_ oclc_pm *OCLC_PM_Create_(GENERAL _PL_ Origin,OCLC_MD _PL_ KernelList,ADDRESS KernelNums)
{
	oclc_pm *PM=NULL;

	if(KernelNums)
	{
		address Size=MemC.Size.Mul_(KernelNums,sizeof(struct _oclc_pm_kernel));

		if(Size)
		{
			Size=MemC.Size.Add_(Size,sizeof(struct _oclc_pm));
			if(!Size) goto ESCAPE;

			for(address Idx=0;Idx<KernelNums;Idx++)
			{
				Size=MemC.Size.Add_(Size,KernelList[Idx].Size);
				if(!Size) goto ESCAPE;
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

		for(byte_08 *NamePin=(byte_08*)((PM->Program.Kernel.List)+(PM->Program.Kernel.Nums.Total));Idx<PM->Program.Kernel.Nums.Total;Idx++)
		{
			oclc_md _PL_ PtrN=(oclc_md*)&(PM->Program.Kernel.List[Idx].Name);

			PtrN->Size=KernelList[Idx].Size;
			PtrN->Data=NamePin;

			if(MemC_Copy_1D_(KernelList[Idx].Data,(byte_08*)(PtrN->Data),PtrN->Size)==MemCErrZero)
				NamePin+=KernelList[Idx].Size;
			else break;
		}
		if(Idx==KernelNums)
			Acs_(GENERAL*,PM->Origin)=Origin;
		else
			OCLC_PM_Delete_(&PM);
	}
ESCAPE:
	return PM;
}
#define _OCLC_Build_
#include "oclcrux.c"
#undef _OCLC_Build_
_OCLC_ general OCLC_PM_Build_Log_(OCLC_PM _PL_ PM,FILE _PL_ Stream,cl_int _PL_ Error)
{
	if(PM)
	{
		const cl_program Program=PM->Program.ID;
		cl_uint DeviceNums;

		*Error=clGetProgramInfo(Program,CL_PROGRAM_NUM_DEVICES,sizeof(cl_uint),&DeviceNums,NULL);
		if(*Error==CL_SUCCESS)
		{
			MemC_Temp_ND_(cl_device_id,DeviceTemp,ESCAPE_DEVICE,1,DeviceNums)
			{
				cl_device_id _PL_ DeviceList=DeviceTemp;

				*Error=clGetProgramInfo(Program,CL_PROGRAM_DEVICES,MemC_Size_(cl_device_id,DeviceNums),DeviceList,NULL);
				if(*Error==CL_SUCCESS)
				{
					BYTE_08 IdiomNext[2]={'\n','\0'};
					ADDRESS SizeNext=sizeof(IdiomNext);
					address Size;

					for(cl_uint Idx=0;Idx<DeviceNums;Idx++)
					{
						if(*Error==CL_SUCCESS)
							*Error=clGetDeviceInfo(DeviceList[Idx],CL_DEVICE_NAME,0,NULL,&Size);
						else break;

						if(*Error==CL_SUCCESS)
						{
							MemC_Temp_Byte_(NameTemp,Size,ESCAPE_PROGRAM)
							{
								byte_08 _PL_ Name=NameTemp;

								*Error=clGetDeviceInfo(DeviceList[Idx],CL_DEVICE_NAME,Size,Name,NULL);
								if(*Error==CL_SUCCESS)
								{
									PenC.Stream.Buffer.T08_(0,Stream,Name,Size);
									PenC.Stream.Buffer.T08_(0,Stream,(text_08*)IdiomNext,SizeNext);
								}
							}
						}
						else break;

						if(*Error==CL_SUCCESS)
							*Error=clGetProgramBuildInfo(Program,DeviceList[Idx],CL_PROGRAM_BUILD_LOG,0,NULL,&Size);
						else break;

						if(*Error==CL_SUCCESS)
						{
							MemC_Temp_Byte_(LogTemp,Size,ESCAPE_PROGRAM)
							{
								byte_08 _PL_ Log=LogTemp;

								*Error=clGetProgramBuildInfo(Program,DeviceList[Idx],CL_PROGRAM_BUILD_LOG,Size,Log,NULL);
								if(*Error==CL_SUCCESS)
								{
									PenC.Stream.Buffer.T08_(0,Stream,Log,Size);
									PenC.Stream.Buffer.T08_(0,Stream,(text_08*)IdiomNext,SizeNext);
								}
							}
						}
						else break;

						continue;
ESCAPE_PROGRAM:
						*Error=CL_OUT_OF_HOST_MEMORY;
						break;
					}
				}
			}
			return;
ESCAPE_DEVICE:
			*Error=CL_OUT_OF_HOST_MEMORY;
		}
	}
	else
		*Error=CL_INVALID_HOST_PTR;
}

_OCLC_ cl_kernel OCLC_PM_Kernel_(OCLC_PM _PL_ PM,ADDRESS KSelect)
{
	return ((PM)?((KSelect<PM->Program.Kernel.Nums.Total)?(PM->Program.Kernel.List[KSelect].ID):(NULL)):(NULL));
}
#endif

#if(Fold_(Part:Memory Object))
_OCLC_ address OCLC_MO_Info_Size_(const cl_mem Memory,const cl_mem_info Flag,cl_int _PL_ Error)
{
	address Size=0;

	if(*Error==CL_SUCCESS)
		*Error=clGetMemObjectInfo(Memory,Flag,0,NULL,&Size);

	return Size;
}
_OCLC_ general OCLC_MO_Info_What_(const cl_mem Memory,const cl_mem_info Flag,general _PL_ What,ADDRESS Size,cl_int _PL_ Error)
{
	if(*Error==CL_SUCCESS)
		*Error=clGetMemObjectInfo(Memory,Flag,Size,What,NULL);
}

_OCLC_ cl_mem OCLC_MO_Create_Buffer_(const cl_context Context,ADDRESS Size,cl_int _PL_ Error)
{
	return (*Error==CL_SUCCESS)?(clCreateBuffer(Context,CL_MEM_READ_WRITE,Size,NULL,Error)):(NULL);
}
_OCLC_ cl_mem OCLC_MO_Create_Sub_Buffer_(const cl_mem Buffer,ADDRESS Offset,ADDRESS Size,cl_int _PL_ Error)
{
	cl_mem Sub;

	if(*Error==CL_SUCCESS)
	{
		cl_buffer_region Region;

		Region.origin=Offset;
		Region.size=Size;
		
		Sub=clCreateSubBuffer(Buffer,CL_MEM_READ_WRITE,CL_BUFFER_CREATE_TYPE_REGION,&Region,Error);
	}
	else
		Sub=NULL;

	return Sub;
}
_OCLC_ general OCLC_MO_Delete_(cl_mem *Mem)
{
	if(*Mem)
	{
		clReleaseMemObject(*Mem);
		*Mem=NULL;
	}
}

_OCLC_ address OCLC_MO_Size_(const cl_mem Mem,cl_int _PL_ Error)
{
	address Size=0;

	if(*Error==CL_SUCCESS)
		*Error=clGetMemObjectInfo(Mem,CL_MEM_SIZE,sizeof(address),&Size,NULL);

	return Size;
}
_OCLC_ address OCLC_MO_Offset_(const cl_mem Mem,cl_int _PL_ Error)
{
	address Size=0;

	if(*Error==CL_SUCCESS)
		*Error=clGetMemObjectInfo(Mem,CL_MEM_OFFSET,sizeof(address),&Size,NULL);

	return Size;
}
_OCLC_ cl_context OCLC_MO_Context_(const cl_mem Mem,cl_int _PL_ Error)
{
	cl_context Context=NULL;

	if(*Error==CL_SUCCESS)
		*Error=clGetMemObjectInfo(Mem,CL_MEM_CONTEXT,sizeof(cl_context),&Context,NULL);

	return Context;
}
#endif

#if(Fold_(Part:Memory Pin))
static _Bool _OCLC_MP_Invalid_Offset_(OCLC_MP _PL_ Ofs,OCLC_MP _PL_ Shp)
{
	oclc_pa Idx;

	for(Idx=OCLCPinAxisN;Idx<OCLCPinAxes;Idx++)
		if(Ofs->S[Idx]>Shp->S[Idx])
			break;

	return (Idx<OCLCPinAxes);
}
static _Bool _OCLC_MP_Invalid_Length_(OCLC_MP _PL_ Ofs,OCLC_MP _PL_ Lng,OCLC_MP _PL_ Shp)
{
	oclc_pa Idx;

	for(Idx=OCLCPinAxisN;Idx<OCLCPinAxes;Idx++)
		if(Lng->S[Idx])
		{
			ADDRESS Temp=Ofs->S[Idx]+Lng->S[Idx];

			if(Temp<Lng->S[Idx])
				break;
			if(Temp>Shp->S[Idx])
				break;
		}
		else
			break;

	return (Idx<OCLCPinAxes);
}

_OCLC_ oclc_mp OCLC_MP_Length_1D_(ADDRESS LngX)
{
	oclc_mp Pin;

	Pin.N=1;
	Pin.Z=1;
	Pin.Y=1;
	Pin.X=LngX;

	return Pin;
}
_OCLC_ oclc_mp OCLC_MP_Length_2D_(ADDRESS LngY,ADDRESS LngX)
{
	oclc_mp Pin;

	Pin.N=1;
	Pin.Z=1;
	Pin.Y=LngY;
	Pin.X=LngX;

	return Pin;
}
_OCLC_ oclc_mp OCLC_MP_Length_3D_(ADDRESS LngZ,ADDRESS LngY,ADDRESS LngX)
{
	oclc_mp Pin;

	Pin.N=1;
	Pin.Z=LngZ;
	Pin.Y=LngY;
	Pin.X=LngX;

	return Pin;
}
_OCLC_ oclc_mp OCLC_MP_Length_4D_(ADDRESS LngN,ADDRESS LngZ,ADDRESS LngY,ADDRESS LngX)
{
	oclc_mp Pin;

	Pin.N=LngN;
	Pin.Z=LngZ;
	Pin.Y=LngY;
	Pin.X=LngX;

	return Pin;
}

_OCLC_ oclc_mp OCLC_MP_Offset_1D_(ADDRESS OfsX)
{
	oclc_mp Pin;

	Pin.N=0;
	Pin.Z=0;
	Pin.Y=0;
	Pin.X=OfsX;

	return Pin;
}
_OCLC_ oclc_mp OCLC_MP_Offset_2D_(ADDRESS OfsY,ADDRESS OfsX)
{
	oclc_mp Pin;

	Pin.N=0;
	Pin.Z=0;
	Pin.Y=OfsY;
	Pin.X=OfsX;

	return Pin;
}
_OCLC_ oclc_mp OCLC_MP_Offset_3D_(ADDRESS OfsZ,ADDRESS OfsY,ADDRESS OfsX)
{
	oclc_mp Pin;

	Pin.N=0;
	Pin.Z=OfsZ;
	Pin.Y=OfsY;
	Pin.X=OfsX;

	return Pin;
}
_OCLC_ oclc_mp OCLC_MP_Offset_4D_(ADDRESS OfsN,ADDRESS OfsZ,ADDRESS OfsY,ADDRESS OfsX)
{
	oclc_mp Pin;

	Pin.N=OfsN;
	Pin.Z=OfsZ;
	Pin.Y=OfsY;
	Pin.X=OfsX;

	return Pin;
}

_OCLC_ address OCLC_MP_Total_(OCLC_MP _PL_ Pin)
{
	return (Pin->N*Pin->Z*Pin->Y*Pin->X);
}
#endif

#if(Fold_(Part:Memory Holder))
_OCLC_ oclc_mh OCLC_MH_Assign_(general _PL_ Memory,OCLC_MP _PL_ Start,OCLC_MP _PL_ Shape,MEMC_DT _PL_ Type)
{
	oclc_mh Holder;

	Holder.Memory=Memory;
	Holder.Start=Start;
	Holder.Shape=Shape;
	Holder.Type=Type;

	return Holder;
}
#endif

#if(Fold_(Part:Platform ID))
_OCLC_ address OCLC_PI_Info_Size_(const cl_platform_id Platform,const cl_platform_info Flag,cl_int _PL_ Error)
{
	address Size=0;

	if(*Error==CL_SUCCESS)
		*Error=clGetPlatformInfo(Platform,Flag,0,NULL,&Size);

	return Size;
}
_OCLC_ general OCLC_PI_Info_What_(const cl_platform_id Platform,const cl_platform_info Flag,general _PL_ What,ADDRESS Size,cl_int _PL_ Error)
{
	if(*Error==CL_SUCCESS)
		*Error=clGetPlatformInfo(Platform,Flag,Size,What,NULL);
}
#endif

#if(Fold_(Part:Device ID))
_OCLC_ address OCLC_DI_Info_Size_(const cl_device_id Device,const cl_device_info Flag,cl_int _PL_ Error)
{
	address Size=0;

	if(*Error==CL_SUCCESS)
		*Error=clGetDeviceInfo(Device,Flag,0,NULL,&Size);

	return Size;
}
_OCLC_ general OCLC_DI_Info_What_(const cl_device_id Device,const cl_device_info Flag,general _PL_ What,ADDRESS Size,cl_int _PL_ Error)
{
	if(*Error==CL_SUCCESS)
		*Error=clGetDeviceInfo(Device,Flag,Size,What,NULL);
}
#endif

#if(Fold_(Part:Context Object))
_OCLC_ address OCLC_CO_Info_Size_(const cl_context Context,const cl_context_info Flag,cl_int _PL_ Error)
{
	address Size=0;

	if(*Error==CL_SUCCESS)
		*Error=clGetContextInfo(Context,Flag,0,NULL,&Size);

	return Size;
}
_OCLC_ general OCLC_CO_Info_What_(const cl_context Context,const cl_context_info Flag,general _PL_ What,ADDRESS Size,cl_int _PL_ Error)
{
	if(*Error==CL_SUCCESS)
		*Error=clGetContextInfo(Context,Flag,Size,What,NULL);
}
#endif

#if(Fold_(Part:Queue Object))
_OCLC_ address OCLC_QO_Info_Size_(const cl_command_queue Queue,const cl_command_queue_info Flag,cl_int _PL_ Error)
{
	address Size=0;

	if(*Error==CL_SUCCESS)
		*Error=clGetCommandQueueInfo(Queue,Flag,0,NULL,&Size);

	return Size;
}
_OCLC_ general OCLC_QO_Info_What_(const cl_command_queue Queue,const cl_command_queue_info Flag,general _PL_ What,ADDRESS Size,cl_int _PL_ Error)
{
	if(*Error==CL_SUCCESS)
		*Error=clGetCommandQueueInfo(Queue,Flag,Size,What,NULL);
}

static general _OCLC_QO_Merge_(oclc_mp _PL_ SOfs,oclc_mp _PL_ TOfs,oclc_mp _PL_ Lng,oclc_mp _PL_ SShp,oclc_mp _PL_ TShp)
{
	if(((SOfs->Z)|((Lng->Z)^(SShp->Z)))|((TOfs->Z)|((Lng->Z)^(TShp->Z))))
		return;
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
}
static general _OCLC_QO_Pin_Set_(OCLC_MP _PL_ LngPin,OCLC_MP _PL_ OfsPin,address Step[2],address Offset[3],ADDRESS TypeSize)
{
	Step[0]=LngPin->X*TypeSize;
	Step[1]=LngPin->Y*Step[0];

	Offset[0]=OfsPin->X*TypeSize;
	Offset[1]=OfsPin->Y;
	Offset[2]=(OfsPin->N*LngPin->Z)+OfsPin->Z;
}
static general _OCLC_QO_Pin_Length_(OCLC_MP _PL_ LngPin,address Length[3],ADDRESS TypeSize)
{
	Length[0]=LngPin->X*TypeSize;
	Length[1]=LngPin->Y;
	Length[2]=LngPin->Z;
}
static cl_int _OCLC_QO_HtoD_(const cl_command_queue Queue,GENERAL _PL_ SrcMem,OCLC_MP _PL_ SrcOfs,OCLC_MP _PL_ SrcShp,const cl_mem TrgMem,OCLC_MP _PL_ TrgOfs,OCLC_MP _PL_ TrgShp,OCLC_MP _PL_ CpyLng,ADDRESS TypeSize)
{
	address SourceStep[2];
	address TargetStep[2];
	address SourceOffset[3];
	address TargetOffset[3];
	address CopyLength[3];
	cl_int Error=CL_SUCCESS;

	_OCLC_QO_Pin_Set_(SrcShp,SrcOfs,SourceStep,SourceOffset,TypeSize);
	_OCLC_QO_Pin_Set_(TrgShp,TrgOfs,TargetStep,TargetOffset,TypeSize);
	_OCLC_QO_Pin_Length_(CpyLng,CopyLength,TypeSize);

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
static cl_int _OCLC_QO_DtoH_(const cl_command_queue Queue,const cl_mem SrcMem,OCLC_MP _PL_ SrcOfs,OCLC_MP _PL_ SrcShp,general _PL_ TrgMem,OCLC_MP _PL_ TrgOfs,OCLC_MP _PL_ TrgShp,OCLC_MP _PL_ CpyLng,ADDRESS TypeSize)
{
	address SourceStep[2];
	address TargetStep[2];
	address SourceOffset[3];
	address TargetOffset[3];
	address CopyLength[3];
	cl_int Error=CL_SUCCESS;

	_OCLC_QO_Pin_Set_(SrcShp,SrcOfs,SourceStep,SourceOffset,TypeSize);
	_OCLC_QO_Pin_Set_(TrgShp,TrgOfs,TargetStep,TargetOffset,TypeSize);
	_OCLC_QO_Pin_Length_(CpyLng,CopyLength,TypeSize);

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
static cl_int _OCLC_QO_DtoD_(const cl_command_queue Queue,const cl_mem SrcMem,OCLC_MP _PL_ SrcOfs,OCLC_MP _PL_ SrcShp,const cl_mem TrgMem,OCLC_MP _PL_ TrgOfs,OCLC_MP _PL_ TrgShp,OCLC_MP _PL_ CpyLng,ADDRESS TypeSize)
{
	address SourceStep[2];
	address TargetStep[2];
	address SourceOffset[3];
	address TargetOffset[3];
	address CopyLength[3];
	cl_int Error=CL_SUCCESS;

	_OCLC_QO_Pin_Set_(SrcShp,SrcOfs,SourceStep,SourceOffset,TypeSize);
	_OCLC_QO_Pin_Set_(TrgShp,TrgOfs,TargetStep,TargetOffset,TypeSize);
	_OCLC_QO_Pin_Length_(CpyLng,CopyLength,TypeSize);

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
_OCLC_ general OCLC_QO_Copy_(const cl_command_queue Queue,OCLC_CF Mode,OCLC_MH _PL_ Source,OCLC_MH _PL_ Target,OCLC_MP _PL_ CpyLng,cl_int _PL_ Error)
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

			_OCLC_QO_Merge_(&FSrcOfs,&FTrgOfs,&FLng,&FSrcShp,&FTrgShp);

			if(_OCLC_MP_Invalid_Offset_(&FSrcOfs,&FSrcShp))
				goto INVALID_VALUE;
			if(_OCLC_MP_Invalid_Offset_(&FTrgOfs,&FTrgShp))
				goto INVALID_VALUE;
			if(_OCLC_MP_Invalid_Length_(&FSrcOfs,&FLng,&FSrcShp))
				goto INVALID_VALUE;
			if(_OCLC_MP_Invalid_Length_(&FTrgOfs,&FLng,&FTrgShp))
				goto INVALID_VALUE;

			switch(Mode)
			{
			case OCLCopyHtoH:
				if(MemC.Copy.DN_(Source->Memory,Target->Memory,FSrcOfs.S,FTrgOfs.S,FLng.S,FSrcShp.S,FTrgShp.S,4,TypeSize)==MemCErrZero)
					break;
				else
					goto INVALID_VALUE;
			case OCLCopyHtoD:
				*Error=_OCLC_QO_HtoD_(Queue,Source->Memory,&FSrcOfs,&FSrcShp,Target->Memory,&FTrgOfs,&FTrgShp,&FLng,TypeSize);
				break;
			case OCLCopyDtoH:
				*Error=_OCLC_QO_DtoH_(Queue,(cl_mem)(Source->Memory),&FSrcOfs,&FSrcShp,Target->Memory,&FTrgOfs,&FTrgShp,&FLng,TypeSize);
				break;
			case OCLCopyDtoD:
				*Error=_OCLC_QO_DtoD_(Queue,(cl_mem)(Source->Memory),&FSrcOfs,&FSrcShp,Target->Memory,&FTrgOfs,&FTrgShp,&FLng,TypeSize);
				break;
			default:
				goto INVALID_VALUE;
			}
		}
		else
		{
INVALID_VALUE:
			*Error=CL_INVALID_VALUE;
		}
}

static oclc_mp _OCLC_QO_Jump_(OCLC_MP _PL_ Shape,ADDRESS TypeSize)
{
	oclc_mp Jump;

	Jump.X=TypeSize;
	Jump.Y=Shape->X*Jump.X;
	Jump.Z=Shape->Y*Jump.Y;
	Jump.N=Shape->Z*Jump.Z;

	return Jump;
}
static oclc_mp _OCLC_QO_Skip_(OCLC_MP _PL_ Offset,OCLC_MP _PL_ Jump)
{
	oclc_mp Skip;

	Skip.N=Offset->N*Jump->N;
	Skip.Z=Offset->Z*Jump->Z;
	Skip.Y=Offset->Y*Jump->Y;
	Skip.X=Offset->X*Jump->X;

	return Skip;
}
static general _OCLC_QO_Flat_(oclc_mp _PL_ Ofs,oclc_mp _PL_ Lng,oclc_mp _PL_ Shp)
{
	for(oclc_pa Here=OCLCPinAxisZ;Here<OCLCPinAxes;Here++)
		if((Ofs->S[Here])|((Lng->S[Here])^(Shp->S[Here])))
			continue;
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
}
_OCLC_ general OCLC_QO_Fill_(const cl_command_queue Queue,GENERAL _PL_ Source,OCLC_MH _PL_ Target,OCLC_MP _PL_ SetLng,cl_int _PL_ Error)
{
	if(*Error==CL_SUCCESS)
	{
		oclc_mp VOfs=(Target->Start)?(*(Target->Start)):(ConstantZero);
		oclc_mp VLng=*SetLng;
		oclc_mp VShp=(Target->Shape)?(*(Target->Shape)):(VLng);

		_OCLC_QO_Flat_(&VOfs,&VLng,&VShp);

		if(_OCLC_MP_Invalid_Offset_(&VOfs,&VShp))
			goto INVALID_VALUE;
		if(_OCLC_MP_Invalid_Length_(&VOfs,&VLng,&VShp))
		{
INVALID_VALUE:
			*Error=CL_INVALID_VALUE;
			return;
		}
		else
		{
			const cl_mem Memory=Target->Memory;
			ADDRESS Length=VLng.X*Target->Type->SizeType;
			OCLC_MP Jump=_OCLC_QO_Jump_(&VShp,Target->Type->SizeType);
			OCLC_MP Skip=_OCLC_QO_Skip_(&VOfs,&Jump);

			for(address IdxN=0,OfsN=Skip.N;IdxN<VLng.N;IdxN++,OfsN+=Jump.N)
				for(address IdxZ=0,OfsZ=OfsN+Skip.Z;IdxZ<VLng.Z;IdxZ++,OfsZ+=Jump.Z)
					for(address IdxY=0,OfsY=OfsZ+Skip.Y;IdxY<VLng.Y;IdxY++,OfsY+=Jump.Y)
					{
						*Error=clEnqueueFillBuffer(Queue,Memory,Source,Jump.X,OfsY+Skip.X,Length,0,NULL,NULL);
						if(*Error) return;
					}
		}
	}
}

_OCLC_ general OCLC_QO_Wait_(const cl_command_queue Queue,cl_int _PL_ Error)
{
	if(*Error==CL_SUCCESS)
		*Error=clFinish(Queue);
}
#endif

#if(Fold_(Part:Kernel Object))
_OCLC_ address OCLC_KO_Info_Size_(const cl_kernel Kernel,const cl_kernel_info Flag,cl_int _PL_ Error)
{
	address Size=0;

	if(*Error==CL_SUCCESS)
		*Error=clGetKernelInfo(Kernel,Flag,0,NULL,&Size);

	return Size;
}
_OCLC_ general OCLC_KO_Info_What_(const cl_kernel Kernel,const cl_kernel_info Flag,general _PL_ What,ADDRESS Size,cl_int _PL_ Error)
{
	if(*Error==CL_SUCCESS)
		*Error=clGetKernelInfo(Kernel,Flag,Size,What,NULL);
}

_OCLC_ general OCLC_KO_G_(const cl_kernel Kernel,const cl_uint Index,const cl_mem Memory,cl_int _PL_ Error)
{
	if(*Error==CL_SUCCESS)
		*Error=clSetKernelArg(Kernel,Index,sizeof(cl_mem),&Memory);
}
_OCLC_ general OCLC_KO_L_(const cl_kernel Kernel,const cl_uint Index,ADDRESS Size,cl_int _PL_ Error)
{
	if(*Error==CL_SUCCESS)
		*Error=clSetKernelArg(Kernel,Index,Size,NULL);
}
_OCLC_ general OCLC_KO_P_(const cl_kernel Kernel,const cl_uint Index,GENERAL _PL_ Value,ADDRESS ValueSize,cl_int _PL_ Error)
{
	if(*Error==CL_SUCCESS)
		*Error=clSetKernelArg(Kernel,Index,ValueSize,Value);
}
#endif

#if(Fold_(Undefinition:OCLCrux Macros))
#undef OCLC_Func_
#undef _OCLC_Func_
#undef OCLC_Type_
#undef _OCLC_Type_
#undef OCLC_TXX_
#undef _OCLC_TXX_
#endif

#if(Fold_(Undefinition:OCLClip Macros))
#undef _OCLC_
#endif

#if(Fold_(Library Casing))
const struct _oclcase OCLC=
{
	.Version=IdiomVersion,

	.EM.Create_=MemC_Func_Casting_(oclc_em*,OCLC_EM_Create_,oclc_ef _PL_),
	.EM.Delete_=OCLC_EM_Delete_,
	.EM.Select.Context_=OCLC_EM_Context_,
	.EM.Select.Queue_=OCLC_EM_Queue_,

	.PM.Create_=OCLC_PM_Create_,
	.PM.Build.Source.T08_=MemC_Func_Casting_(general,OCLC_PM_Build_T08_,oclc_pm _PL_,oclc_co _PL_,BYTE_08 _PL_,TEXT_08 _PL_ _PL_,const cl_uint,oclc_ef _PL_),
	.PM.Build.Source.T16_=MemC_Func_Casting_(general,OCLC_PM_Build_T16_,oclc_pm _PL_,oclc_co _PL_,BYTE_08 _PL_,TEXT_16 _PL_ _PL_,const cl_uint,oclc_ef _PL_),
	.PM.Build.Binary.T08_=MemC_Func_Casting_(general,OCLC_PM_Load_T08_,oclc_pm _PL_,oclc_co _PL_,BYTE_08 _PL_,TEXT_08 _PL_ _PL_,oclc_ef _PL_),
	.PM.Build.Binary.T16_=MemC_Func_Casting_(general,OCLC_PM_Load_T16_,oclc_pm _PL_,oclc_co _PL_,BYTE_08 _PL_,TEXT_16 _PL_ _PL_,oclc_ef _PL_),
	.PM.Build.Save.T08_=MemC_Func_Casting_(general,OCLC_PM_Save_T08_,OCLC_PM _PL_,TEXT_08 _PL_ _PL_,oclc_ef _PL_),
	.PM.Build.Save.T16_=MemC_Func_Casting_(general,OCLC_PM_Save_T16_,OCLC_PM _PL_,TEXT_16 _PL_ _PL_,oclc_ef _PL_),
	.PM.Build.Log_=MemC_Func_Casting_(general,OCLC_PM_Build_Log_,OCLC_PM _PL_,FILE _PL_,oclc_ef _PL_),
	.PM.Delete_=OCLC_PM_Delete_,
	.PM.Select.Kernel_=OCLC_PM_Kernel_,

	.PI.Info.Size_=MemC_Func_Casting_(address,OCLC_PI_Info_Size_,OCLC_PI _PL_,const cl_platform_info,oclc_ef _PL_),
	.PI.Info.What_=MemC_Func_Casting_(general,OCLC_PI_Info_What_,OCLC_PI _PL_,const cl_platform_info,general _PL_,ADDRESS,oclc_ef _PL_),

	.DI.Info.Size_=MemC_Func_Casting_(address,OCLC_DI_Info_Size_,OCLC_DI _PL_,const cl_device_info,oclc_ef _PL_),
	.DI.Info.What_=MemC_Func_Casting_(general,OCLC_DI_Info_What_,OCLC_DI _PL_,const cl_device_info,general _PL_,ADDRESS,oclc_ef _PL_),

	.CO.Info.Size_=MemC_Func_Casting_(address,OCLC_CO_Info_Size_,OCLC_CO _PL_,const cl_context_info,oclc_ef _PL_),
	.CO.Info.What_=MemC_Func_Casting_(general,OCLC_CO_Info_What_,OCLC_CO _PL_,const cl_context_info,general _PL_,ADDRESS,oclc_ef _PL_),

	.QO.Info.Size_=MemC_Func_Casting_(address,OCLC_QO_Info_Size_,OCLC_QO _PL_,const cl_command_queue_info,oclc_ef _PL_),
	.QO.Info.What_=MemC_Func_Casting_(general,OCLC_QO_Info_What_,OCLC_QO _PL_,const cl_command_queue_info,general _PL_,ADDRESS,oclc_ef _PL_),
	.QO.Fill_=MemC_Func_Casting_(general,OCLC_QO_Fill_,oclc_qo _PL_,GENERAL _PL_,OCLC_MH _PL_,OCLC_MP _PL_,oclc_ef _PL_),
	.QO.Copy_=MemC_Func_Casting_(general,OCLC_QO_Copy_,oclc_qo _PL_,OCLC_CF,OCLC_MH _PL_,OCLC_MH _PL_,OCLC_MP _PL_,oclc_ef _PL_),
	.QO.Wait_=MemC_Func_Casting_(general,OCLC_QO_Wait_,oclc_qo _PL_,oclc_ef _PL_),

	.KO.Info.Size_=MemC_Func_Casting_(address,OCLC_KO_Info_Size_,OCLC_KO _PL_,const cl_kernel_info,oclc_ef _PL_),
	.KO.Info.What_=MemC_Func_Casting_(general,OCLC_KO_Info_What_,OCLC_KO _PL_,const cl_kernel_info,general _PL_,ADDRESS,oclc_ef _PL_),
	.KO.Arg.G_=MemC_Func_Casting_(general,OCLC_KO_G_,oclc_ko _PL_,const cl_uint,OCLC_MO _PL_,oclc_ef _PL_),
	.KO.Arg.L_=MemC_Func_Casting_(general,OCLC_KO_L_,oclc_ko _PL_,const cl_uint,ADDRESS,oclc_ef _PL_),
	.KO.Arg.P_=MemC_Func_Casting_(general,OCLC_KO_P_,oclc_ko _PL_,const cl_uint,GENERAL _PL_,ADDRESS,oclc_ef _PL_),

	.MO.Info.Size_=MemC_Func_Casting_(address,OCLC_MO_Info_Size_,OCLC_MO _PL_,const cl_mem_info,oclc_ef _PL_),
	.MO.Info.What_=MemC_Func_Casting_(general,OCLC_MO_Info_What_,OCLC_MO _PL_,const cl_mem_info,general _PL_,ADDRESS,oclc_ef _PL_),
	.MO.Create.Buffer_=MemC_Func_Casting_(oclc_mo*,OCLC_MO_Create_Buffer_,oclc_co _PL_,ADDRESS,oclc_ef _PL_),
	.MO.Create.Sub_=MemC_Func_Casting_(oclc_mo*,OCLC_MO_Create_Sub_Buffer_,oclc_mo _PL_,ADDRESS,ADDRESS,oclc_ef _PL_),
	.MO.Delete_=OCLC_MO_Delete_,

	.MP.Zero=&ConstantZero,
	.MP.Total_=OCLC_MP_Total_,
	.MP.Length.Invalid_=_OCLC_MP_Invalid_Length_,
	.MP.Offset.Invalid_=_OCLC_MP_Invalid_Offset_,
	.MP.Length.D1_=OCLC_MP_Length_1D_,
	.MP.Length.D2_=OCLC_MP_Length_2D_,
	.MP.Length.D3_=OCLC_MP_Length_3D_,
	.MP.Length.D4_=OCLC_MP_Length_4D_,
	.MP.Offset.D1_=OCLC_MP_Offset_1D_,
	.MP.Offset.D2_=OCLC_MP_Offset_2D_,
	.MP.Offset.D3_=OCLC_MP_Offset_3D_,
	.MP.Offset.D4_=OCLC_MP_Offset_4D_,

	.MH.Assign_=OCLC_MH_Assign_
};
#endif
