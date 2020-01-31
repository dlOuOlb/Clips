#ifdef oOCLCLIP_INC_
#ifdef oOCLCLIP_SRC_

#ifdef xOCLC_Build_
static general OCLC_Func_(OCLC_PM_Build_,TXX)(oclc_pm _PL_ _R_ PM,const cl_context Context,TEXT_08 _PL_ _R_ Option,TEXT_XX _PL_ _PL_ _R_ SrcPath,ADDRESS SrcNums,cl_int _PL_ _R_ Error)
{
	if(*Error==CL_SUCCESS)
		if(PM)
			if(PM->Program.ID)
				*Error=CL_INVALID_HOST_PTR;
			else
				if(SrcPath)
				{
					cl_uint DeviceNums;

					if((*Error=clGetContextInfo(Context,CL_CONTEXT_NUM_DEVICES,sizeof(cl_uint),&DeviceNums,NULL))==CL_SUCCESS)
					{
						MemC_Temp_ND_(cl_device_id,DeviceTemp,*Error=CL_OUT_OF_HOST_MEMORY;,1,DeviceNums)
						{
							cl_device_id _PL_ DeviceList=DeviceTemp;

							if((*Error=clGetContextInfo(Context,CL_CONTEXT_DEVICES,MemC_Size_(cl_device_id,DeviceNums),DeviceList,NULL))==CL_SUCCESS)
							{
								MemC_Temp_ND_(address,SrcTemp,*Error=CL_OUT_OF_HOST_MEMORY;,1,SrcNums<<1)
								{
									address _PL_ _R_ SrcLngs=SrcTemp,SrcSums,Idx;

									for(Idx=0,SrcSums=0;Idx<SrcNums;Idx++)
									{
										SrcLngs[Idx]=PenC_File_Length_(SrcPath[Idx]);
										if(SrcLngs[Idx])
											SrcSums+=SrcLngs[Idx];
										else break;
									}
									if(Idx<SrcNums)
										*Error=CL_INVALID_HOST_PTR;
									else
									{
										MemC_Temp_Byte_(Space,SrcSums,*Error=CL_OUT_OF_HOST_MEMORY;)
										{
											text_08 _PL_ Source=Space,**_R_ SrcList=(text_08**)(SrcLngs+SrcNums);

											MemC_Assign_1D_N_(SrcList,Source,SrcLngs,SrcNums);
											for(Idx=0;Idx<SrcNums;Idx++)
												if(PenC_Buffer_Reader_(SrcList[Idx],SrcPath[Idx],SrcLngs[Idx]));
												else break;

											if(Idx<SrcNums)
												*Error=CL_INVALID_HOST_PTR;
											else
											{
												Acs_(cl_program,PM->Program.ID)=clCreateProgramWithSource(Context,(cl_uint)SrcNums,(const char**)SrcList,SrcLngs,Error);
												if(*Error==CL_SUCCESS)
													if((*Error=clBuildProgram(PM->Program.ID,DeviceNums,DeviceList,Option,NULL,NULL))==CL_SUCCESS)
														for(Idx=0;Idx<PM->Program.Kernel.Nums.Total;Idx++)
														{
															struct _oclc_pm_kernel _PL_ _R_ PtrK=(struct _oclc_pm_kernel*)(PM->Program.Kernel.List+Idx);

															Acs_(cl_kernel,PtrK->ID)=clCreateKernel(PM->Program.ID,PtrK->Name.Data,Error);
															switch(*Error)
															{
															case CL_SUCCESS:
																Acs_(address,PM->Program.Kernel.Nums.Valid)++;
																break;
															case CL_INVALID_KERNEL_NAME:
																*Error=CL_SUCCESS;
																break;
															default:goto ESCAPE;
															}
														}
													else;
												else;
											}
ESCAPE:;
										}
									}
								}
							}
							else;
						}
					}
					else;
				}
				else
					*Error=CL_INVALID_HOST_PTR;
		else
			*Error=CL_INVALID_HOST_PTR;
	else;

	return;
}
static general OCLC_Func_(OCLC_PM_Load_,TXX)(oclc_pm _PL_ _R_ PM,const cl_context Context,TEXT_08 _PL_ _R_ Option,TEXT_XX _PL_ _PL_ _R_ NameList,cl_int _PL_ _R_ Error)
{
	if(*Error==CL_SUCCESS)
		if(PM)
			if(PM->Program.ID)
				*Error=CL_INVALID_HOST_PTR;
			else
			{
				cl_uint Devices;

				if((*Error=clGetContextInfo(Context,CL_CONTEXT_NUM_DEVICES,sizeof(cl_uint),&Devices,NULL))==CL_SUCCESS)
				{
					MemC_Temp_ND_(address,Space,*Error=CL_OUT_OF_HOST_MEMORY;,1,Devices*3)
					{
						address _PL_ _R_ SizeList=Space,SizeSums=0;

						for(cl_uint Idx=0;Idx<Devices;Idx++)
							if(NameList[Idx])
							{
								SizeList[Idx]=PenC_File_Length_(NameList[Idx]);
								if(SizeList[Idx])
									SizeSums+=SizeList[Idx];
								else goto INVALID_VALUE;
							}
							else
							{
INVALID_VALUE:					*Error=CL_INVALID_VALUE;
								break;
							}

						if(*Error==CL_SUCCESS)
						{
							text_08 *_PL_ _R_ BinaryList=(text_08**)(SizeList+Devices);

							MemC_Temp_Byte_(Temp,SizeSums,*Error=CL_OUT_OF_HOST_MEMORY;)
							{
								text_08 *Binary=Temp;

								for(cl_uint Idx=0;Idx<Devices;Idx++)
								{
									BinaryList[Idx]=Binary;
									if(PenC_Buffer_Reader_(BinaryList[Idx],NameList[Idx],SizeList[Idx]))
										Binary+=SizeList[Idx];
									else
									{
										*Error=CL_INVALID_HOST_PTR;
										break;
									}
								}

								if(*Error==CL_SUCCESS)
								{
									cl_device_id _PL_ DeviceList=(cl_device_id*)(BinaryList+Devices);

									if((*Error=clGetContextInfo(Context,CL_CONTEXT_DEVICES,MemC_Size_(cl_device_id,Devices),DeviceList,NULL))==CL_SUCCESS)
									{
										Acs_(cl_program,PM->Program.ID)=clCreateProgramWithBinary(Context,Devices,DeviceList,SizeList,(const unsigned char**)BinaryList,NULL,Error);
										if(*Error==CL_SUCCESS)
											if((*Error=clBuildProgram(PM->Program.ID,Devices,DeviceList,Option,NULL,NULL))==CL_SUCCESS)
												for(address Idx=0;Idx<PM->Program.Kernel.Nums.Total;Idx++)
												{
													struct _oclc_pm_kernel _PL_ _R_ PtrK=(struct _oclc_pm_kernel*)(PM->Program.Kernel.List+Idx);

													Acs_(cl_kernel,PtrK->ID)=clCreateKernel(PM->Program.ID,PtrK->Name.Data,Error);
													switch(*Error)
													{
													case CL_SUCCESS:
														Acs_(address,PM->Program.Kernel.Nums.Valid)++;
														break;
													case CL_INVALID_KERNEL_NAME:
														*Error=CL_SUCCESS;
														break;
													default:goto WRONG;
													}
												}
											else;
										else;
									}
									else;
								}
								else;
WRONG:;
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
static general OCLC_Func_(OCLC_PM_Save_,TXX)(OCLC_PM _PL_ _R_ PM,TEXT_XX _PL_ _PL_ _R_ NameList,cl_int _PL_ _R_ Error)
{
	if(*Error==CL_SUCCESS)
		if(PM)
		{
			const cl_program Program=PM->Program.ID;
			cl_uint Devices;

			if((*Error=clGetProgramInfo(Program,CL_PROGRAM_NUM_DEVICES,sizeof(cl_uint),&Devices,NULL))==CL_SUCCESS)
			{
				MemC_Temp_ND_(address,Space,*Error=CL_OUT_OF_HOST_MEMORY;,1,Devices<<1)
				{
					address _PL_ _R_ SizeList=Space;

					if((*Error=clGetProgramInfo(Program,CL_PROGRAM_BINARY_SIZES,MemC_Size_(address,Devices),SizeList,NULL))==CL_SUCCESS)
					{
						address SizeSums=0;

						for(cl_uint Idx=0;Idx<Devices;Idx++)
							if(NameList[Idx])
								if(SizeList[Idx])
									SizeSums+=SizeList[Idx];
								else
								{
									*Error=CL_INVALID_BINARY;
									break;
								}
							else;

						if(*Error==CL_SUCCESS)
							if(SizeSums)
							{
								MemC_Temp_Byte_(Temp,SizeSums,*Error=CL_OUT_OF_HOST_MEMORY;)
								{
									text_08 *_PL_ _R_ BinaryList=(text_08**)(SizeList+Devices),*Binary=Temp;

									for(cl_uint Idx=0;Idx<Devices;Idx++)
										if(NameList[Idx])
										{
											BinaryList[Idx]=Binary;
											Binary+=SizeList[Idx];
										}
										else
											BinaryList[Idx]=NULL;

									if((*Error=clGetProgramInfo(Program,CL_PROGRAM_BINARIES,MemC_Size_(text_08*,Devices),BinaryList,NULL))==CL_SUCCESS)
										for(cl_uint Idx=0;Idx<Devices;Idx++)
											if(NameList[Idx])
												if(PenC_Buffer_Writer_(BinaryList[Idx],NameList[Idx],SizeList[Idx]));
												else
												{
													*Error=CL_INVALID_VALUE;
													break;
												}
											else;
									else;
								}
							}
							else;
						else;
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
#endif

#else

#ifdef XX
#error The macro "XX" is already defined.
#else

#ifdef TXX
#error The macro "TXX" is already defined.
#else
#define TXX OCLC_TXX_(T,XX)
#endif

#ifdef TEXT_XX
#error The macro "TEXT_XX" is already defined.
#else
#define TEXT_XX OCLC_Type_(TEXT,XX)
#endif

#define oOCLCLIP_SRC_

#define XX 08
#include "oclcrux.c"
#undef XX
#define XX 16
#include "oclcrux.c"
#undef XX

#undef oOCLCLIP_SRC_

#undef TEXT_XX
#undef TXX
#endif
#endif

#else
#error Do not build this template directly.
#endif
