#include "penclip.h"

#if(MemC_Fold_(Definition:Global Constants))
static NAME_08 IdiomVersion[16]="Date:2018.06.27";
static NAME_08 IdiomOpen[16]={'r','b','\0','\0','w','b','\0','\0','r','t','\0','\0','w','t','\0','\0'};
static NAME_08 _PL_ AddressOpen[4]={IdiomOpen+0,IdiomOpen+4,IdiomOpen+8,IdiomOpen+12};
#ifdef __OPENCL_H
static NAME_08 IdiomBuild[104]="Build was successful.\n\0Build was not performed.\n\0Build generated an error.\n\0Build was not finished.\n";
static NAME_08 IdiomInfo[104]="Platform\0Device\0Vendor\0Driver\0OpenCL\0Version\0Profile\0Extensions\0cl_khr_icd\0cl_khr_spir\0Built-in Kernels";
static NAME_08 IdiomMessage[72]="No %s\n\0Invalid Selection\n\0%d %s%s:\n\0[%d] %s\n\0*-- %s --*\n\0%s %s: %s\n";
static NAME_08 _PL_ AddressBuild[4]={IdiomBuild+0,IdiomBuild+23,IdiomBuild+49,IdiomBuild+76};
static NAME_08 _PL_ AddressInfo[12]={IdiomInfo+0,IdiomInfo+9,IdiomInfo+16,IdiomInfo+23,IdiomInfo+30,IdiomInfo+37,IdiomInfo+45,IdiomInfo+53,IdiomInfo+64,IdiomInfo+75,IdiomInfo+87,IdiomInfo+103};
static NAME_08 _PL_ AddressMessage[8]={IdiomMessage+0,IdiomMessage+7,IdiomMessage+26,IdiomMessage+36,IdiomMessage+45,IdiomMessage+57,IdiomMessage+60,IdiomMessage+66};
#endif
static NAME_08 TableNumeric[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
NAME_08 _PL_ PenClip=IdiomVersion;
NAME_08 _PL_ _PL_ PenCOpen=AddressOpen;
#endif

#if(MemC_Fold_(Definition:I/O Functions))
int _Line_Reader_(void _PL_ Line,NAME_08 _PL_ Name,const size_t Size,const size_t Count)
{
	int Success;

	if(Line)
	{
		FILE *FilePointer=NULL;

		if(File_Opener_(FilePointer,Name,AddressOpen[0]))
			Success=0;
		else
			if(Count==File_Reader_(FilePointer,Line,Count*Size,name_08))
				Success=1;
			else
				Success=0;

		File_Closer_(FilePointer);
	}
	else
		Success=0;

	return Success;
}
int _Line_Writer_(const void _PL_ Line,NAME_08 _PL_ Name,const size_t Size,const size_t Count)
{
	int Success;

	if(Line)
	{
		FILE *FilePointer=NULL;

		if(File_Opener_(FilePointer,Name,AddressOpen[1]))
			Success=0;
		else
			if(Count==File_Writer_(FilePointer,Line,Count*Size,name_08))
				Success=1;
			else
				Success=0;

		File_Closer_(FilePointer);
	}
	else
		Success=0;

	return Success;
}

size_t File_Length_(NAME_08 _PL_ Name)
{
	FILE *FilePointer=NULL;
	size_t Length=0;

	if(File_Opener_(FilePointer,Name,AddressOpen[0]))
		Length=0;
	else
		if(fseek(FilePointer,0,SEEK_END))
			Length=0;
		else
			Length=(size_t)ftell(FilePointer);

	File_Closer_(FilePointer);

	return Length;
}

int PenC_Command_(NAME_08 _PL_ Command)
{
	name_08 Buffer[1024];
	FILE *ProgramPointer=NULL;
	int Return=-1;

	Program_Opener_(ProgramPointer,Command,AddressOpen[0]);
	if(ProgramPointer)
		while(Scanner_Text_(Buffer,1024,ProgramPointer))
		{
			Printer_Console_(Buffer);
			File_Washer_(ProgramPointer);
		}
	Program_Closer_(ProgramPointer,Return);

	return Return;
}

void PenC_Deci_(name_08 _PL_ Line,const size_t Number,const size_t Count)
{
	if(Line)
	{
		name_08 *Pointer=Line+(Count-1);
		size_t Dividend=Number;

		for(;Pointer>=Line;Pointer--,Dividend/=10)
			(*Pointer)=TableNumeric[Dividend%10];
	}
}
void PenC_Hexa_(name_08 _PL_ Line,const size_t Number,const size_t Count)
{
	if(Line)
	{
		name_08 *Pointer=Line+(Count-1);
		size_t Dividend=Number;

		for(;Pointer>=Line;Pointer--,Dividend>>=4)
			(*Pointer)=TableNumeric[Dividend&15];
	}
}

void PenC_Date_(name_08 _PL_ Line)
{
	struct tm Clock={0};

	{
		time_t Timer=time(NULL);

		localtime_s(&Clock,&Timer);
	}
	PenC_Deci_(Line,Clock.tm_year+1900,4);
	Line[4]='.';
	PenC_Deci_(Line+5,Clock.tm_mon+1,2);
	Line[7]='.';
	PenC_Deci_(Line+8,Clock.tm_mday,2);
}
void PenC_Time_(name_08 _PL_ Line)
{
	struct tm Clock={0};

	{
		time_t Timer=time(NULL);
		
		localtime_s(&Clock,&Timer);
	}
	PenC_Deci_(Line,Clock.tm_hour,2);
	Line[2]=':';
	PenC_Deci_(Line+3,Clock.tm_min,2);
	Line[5]=':';
	PenC_Deci_(Line+6,Clock.tm_sec,2);
}

size_t PenC_Extend_(NAME_08 _PL_ Line,const size_t Length)
{
	size_t Offset=0;

	if(Line)
	{
		NAME_08 *End=Line;
		NAME_08 *Pointer=(name_08*)Byte_Finder_(Line,'\0',Length);

		for(;Pointer>End;Pointer--)
			if((*Pointer)=='.')
			{
				End=Pointer;
				break;
			}
		Offset=End-Line;
	}

	return Offset;
}
#endif

#if(MemC_Fold_(Definition:PenClip Managed Functions))
static size_t _PenC_Overflow_Add_(const size_t A,const size_t B)
{
	const size_t Return=A+B;

	return ((Return<A)?(0):(Return));
}
static size_t _PenC_Overflow_Mul_(const size_t A,const size_t B)
{
	const size_t Return=A*B;

	return (((Return/B)==A)?(Return):(0));
}
penc_sc *PenC_SC_Create_(const size_t Capacity)
{
	penc_sc *SC;

	if(Capacity)
	{
		SC=Byte_Alloc_(_PenC_Overflow_Add_(Capacity,sizeof(penc_sc)));
		if(SC)
		{
			Acs_(size_t,SC->Capacity)=Capacity;
			Acs_(name_08*,SC->String.N08)=Line_Clear_(SC+1,Capacity,name_08);
		}
	}
	else
	{
		SC=Unit_Alloc_(penc_sc);
		if(SC)
			Unit_Clear_(SC,penc_sc);
	}

	return SC;
}
penc_sc *PenC_SC_Create_Sub_(PENC_SC _PL_ Root,const size_t Offset,const size_t Length)
{
	penc_sc *SC;

	if(Root)
		if(Length)
		{
			const size_t Bound=_PenC_Overflow_Add_(Offset,Length);

			if(Bound)
				if(Bound>Root->Capacity)
					SC=NULL;
				else
				{
					SC=Unit_Alloc_(penc_sc);
					if(SC)
					{
						Acs_(size_t,SC->Capacity)=Length;
						Acs_(name_08*,SC->String.N08)=Root->String.N08+Offset;
					}
				}
			else
				SC=NULL;
		}
		else
			if(Offset>Root->Capacity)
				SC=NULL;
			else
			{
				SC=Unit_Alloc_(penc_sc);
				if(SC)
					Unit_Clear_(SC,penc_sc);
			}
	else
		SC=NULL;

	return SC;
}
void PenC_SC_Delete_(penc_sc *_PL_ SC)
{
	MemC_Deloc_(*SC);
}
int PenC_SC_Init_(PENC_SC _PL_ SC)
{
	if(SC)
	{
		Line_Clear_(SC->String.N08,SC->Capacity,name_08);
		goto SUCCESS;
	}
	else
		goto FAILURE;
FAILURE:
	return 0;
SUCCESS:
	return 1;
}

penc_ss *PenC_SS_Create_(const size_t Parts,const size_t Total)
{
	penc_ss *SS;

	if(Parts)
		if(Total)
		{
			size_t Size=_PenC_Overflow_Mul_(Parts,sizeof(penc_sc));

			if(Size)
			{
				Size=_PenC_Overflow_Add_(Size,sizeof(penc_ss));
				if(Size)
				{
					Size=_PenC_Overflow_Add_(Size,Total);
					SS=Byte_Alloc_(Size);
					if(SS)
					{
						Acs_(size_t,SS->Root.Capacity)=Total;
						Acs_(size_t,SS->Nums)=Parts;
						Acs_(penc_sc*,SS->Part)=Line_Clear_(SS+1,Parts,penc_sc);
						Acs_(name_08*,SS->Root.String.N08)=Line_Clear_((name_08*)(SS->Part+Parts),Total,name_08);
					}
				}
				else
					SS=NULL;
			}
			else
				SS=NULL;
		}
		else
		{
			size_t Size=_PenC_Overflow_Mul_(Parts,sizeof(penc_sc));

			if(Size)
			{
				Size=_PenC_Overflow_Add_(Size,sizeof(penc_ss));
				SS=Byte_Alloc_(Size);
				if(SS)
				{
					Acs_(size_t,SS->Root.Capacity)=0;
					Acs_(name_08*,SS->Root.String.N08)=NULL;
					Acs_(size_t,SS->Nums)=Parts;
					Acs_(penc_sc*,SS->Part)=Line_Clear_(SS+1,Parts,penc_sc);
				}
			}
			else
				SS=NULL;
		}
	else
		if(Total)
		{
			SS=Byte_Alloc_(_PenC_Overflow_Add_(Total,sizeof(penc_ss)));
			if(SS)
			{
				Acs_(size_t,SS->Root.Capacity)=Total;
				Acs_(name_08*,SS->Root.String.N08)=Line_Clear_(SS+1,Total,name_08);
				Acs_(size_t,SS->Nums)=0;
				Acs_(penc_sc*,SS->Part)=NULL;
			}
		}
		else
		{
			SS=Unit_Alloc_(penc_ss);
			if(SS)
				Unit_Clear_(SS,penc_ss);
		}

	return SS;
}
void PenC_SS_Delete_(penc_ss *_PL_ SS)
{
	MemC_Deloc_(*SS);
}
int PenC_SS_Assign_(PENC_SS _PL_ SS,const size_t Index,const size_t Offset,const size_t Length)
{
	if(SS)
		if(Index<SS->Nums)
			if(Offset>SS->Root.Capacity)
				goto FAILURE;
			else
				if(Length)
				{
					const size_t Bound=_PenC_Overflow_Add_(Offset,Length);

					if(Bound>SS->Root.Capacity)
						goto FAILURE;
					else
					{
						Acs_(size_t,SS->Part[Index].Capacity)=Length;
						Acs_(name_08*,SS->Part[Index].String.N08)=SS->Root.String.N08+Offset;

						goto SUCCESS;
					}
				}
				else
				{
					Acs_(size_t,SS->Part[Index].Capacity)=0;
					Acs_(name_08*,SS->Part[Index].String.N08)=NULL;

					goto SUCCESS;
				}
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
static size_t _PenC_File_Length_S_(size_t *FileSize,NAME_08 _PL_*FileName,const size_t Files)
{
	NAME_08 _PL_ _PL_ End=FileName+Files;
	size_t Total=0;

	for(;FileName<End;FileName++,FileSize++)
	{
		FileSize[0]=File_Length_(FileName[0]);
		if(FileSize[0])
			Total+=FileSize[0];
		else
		{
			Total=0;
			break;
		}
	}

	return Total;
}
static int _PenC_Line_Reader_S_(name_08 *Line,NAME_08 _PL_ *FileName,const size_t *FileSize,const size_t Files)
{
	NAME_08 _PL_ _PL_ End=FileName+Files;
	int Success;

	for(;FileName<End;FileName++,FileSize++)
		if(Line_Reader_(Line,FileName[0],FileSize[0],name_08))
			Line+=FileSize[0];
		else
			break;

	if(FileName==End)
		Success=1;
	else
		Success=0;

	return Success;
}
static void _PenC_Build_Log_CL_(cl_device_id const Device,cl_program const Program)
{
	{
		cl_build_status Status;

		if(Devi_Info_Build_(Device,Program,&Status,1,cl_build_status,CL_PROGRAM_BUILD_STATUS)==CL_SUCCESS)
			switch(Status)
			{
			case CL_BUILD_SUCCESS:
				Printer_Console_(AddressBuild[0]);
				break;
			case CL_BUILD_NONE:
				Printer_Console_(AddressBuild[1]);
				break;
			case CL_BUILD_ERROR:
				Printer_Console_(AddressBuild[2]);
				break;
			case CL_BUILD_IN_PROGRESS:
				Printer_Console_(AddressBuild[3]);
				break;
			default:;
			}
	}
	{
		size_t StringSize;

		if(Devi_Size_Info_Build_(Device,Program,&StringSize,CL_PROGRAM_BUILD_LOG)==CL_SUCCESS)
		{
			name_08 *String=Line_Alloc_(StringSize,name_08);

			if(String)
				if(Devi_Info_Build_(Device,Program,String,StringSize,name_08,CL_PROGRAM_BUILD_LOG)==CL_SUCCESS)
					Printer_Console_(String);

			MemC_Deloc_(String);
		}
	}
}
penc_cl *PenC_CL_Create_(cl_command_queue const Queue,NAME_08 _PL_ _PL_ FileName,NAME_08 _PL_ _PL_ SetIndicator,NAME_08 _PL_ Option,const size_t Files,const cl_uint Kernels,penc_eu _PL_ Error)
{
	penc_cl *Helper=NULL;
	
	if(Queue)
	{
		cl_device_id Device;

		Error->I=Devi_Info_Queue_(Queue,&Device,1,cl_device_id,CL_QUEUE_DEVICE);
		if(Error->E==CLSuccess)
		{
			cl_context Context;

			Error->I=Devi_Info_Queue_(Queue,&Context,1,cl_context,CL_QUEUE_CONTEXT);
			if(Error->E==CLSuccess)
			{
				cl_uint Cores;

				Error->I=Devi_Info_Device_(Device,&Cores,1,cl_uint,CL_DEVICE_MAX_COMPUTE_UNITS);
				if(Error->E==CLSuccess)
				{
					cl_uint Dimensions;

					Error->I=Devi_Info_Device_(Device,&Dimensions,1,cl_uint,CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS);
					if(Error->E==CLSuccess)
					{
						size_t *FileSize=Line_Alloc_(Files,size_t);

						if(FileSize)
						{
							const size_t SizeText=_PenC_File_Length_S_(FileSize,FileName,Files);

							if(SizeText)
							{
								name_08 *Text=Line_Alloc_(SizeText+1,name_08);

								if(Text)
								{
									name_08 **TextSet=Line_Alloc_(Files,name_08*);

									Text[SizeText]='\0';
									if(TextSet)
										if(_PenC_Line_Reader_S_(Text,FileName,FileSize,Files))
											if(Line_Assign_N_(TextSet,Text,FileSize,Files,name_08)==SizeText)
											{
												{
													size_t SizeTemp;

													SizeTemp=_PenC_Overflow_Mul_(Kernels,sizeof(cl_kernel));
													if(SizeTemp)
													{
														SizeTemp=_PenC_Overflow_Add_(SizeTemp,MemC_Size_(size_t,Dimensions));
														if(SizeTemp)
														{
															SizeTemp=_PenC_Overflow_Add_(SizeTemp,sizeof(penc_cl));
															Helper=Byte_Alloc_(SizeTemp);
														}
													}
												}
												if(Helper)
												{
													Acs_(size_t*,Helper->SizeWorker)=(size_t*)(Helper+1);
													Acs_(cl_kernel*,Helper->SetKernel)=(cl_kernel*)(Helper->SizeWorker+Dimensions);

													Error->I=Devi_Info_Device_(Device,(void*)(Helper->SizeWorker),Dimensions,size_t,CL_DEVICE_MAX_WORK_ITEM_SIZES);
													if(Error->E==CLSuccess)
													{
														Error->I=Devi_Info_Device_(Device,(void*)&(Helper->Workers),1,size_t,CL_DEVICE_MAX_WORK_GROUP_SIZE);
														if(Error->E==CLSuccess)
														{
															Error->I=Devi_Info_Device_(Device,(void*)&(Helper->SizeLocal),1,cl_ulong,CL_DEVICE_LOCAL_MEM_SIZE);
															if(Error->E==CLSuccess)
															{
																Acs_(cl_program,Helper->Program)=Devi_Create_Program_(Context,TextSet,FileSize,(cl_uint)Files,&(Error->I));
																if(Helper->Program)
																{
																	Error->I=Devi_Build_(Helper->Program,Option);
																	_PenC_Build_Log_CL_(Device,Helper->Program);
																	if(Error->E==CLSuccess)
																	{
																		NAME_08 _PL_ _PL_ End=SetIndicator+Kernels;
																		NAME_08 _PL_ *PointerI=SetIndicator;
																		cl_kernel *PointerK=Helper->SetKernel;

																		for(;PointerI<End;PointerI++,PointerK++)
																		{
																			PointerK[0]=Devi_Create_Kernel_(Helper->Program,PointerI[0],&(Error->I));
																			if(!(PointerK[0]))
																				break;
																		}
																		if(PointerI==End)
																		{
																			Acs_(cl_device_id,Helper->Device)=Device;
																			Acs_(cl_context,Helper->Context)=Context;
																			Acs_(cl_command_queue,Helper->Queue)=Queue;
																			Acs_(cl_uint,Helper->Cores)=Cores;
																			Acs_(cl_uint,Helper->Dimensions)=Dimensions;
																			Acs_(cl_uint,Helper->Kernels)=Kernels;
																		}
																		else
																		{
																			for(PointerK--;PointerK>=Helper->SetKernel;PointerK--)
																				Devi_Delete_Kernel_(PointerK[0]);
																			Devi_Delete_Program_(Acs_(cl_program,Helper->Program));
																			MemC_Deloc_(Helper);
																		}
																	}
																	else
																	{
																		Devi_Delete_Program_(Acs_(cl_program,Helper->Program));
																		MemC_Deloc_(Helper);
																	}
																}
																else
																	MemC_Deloc_(Helper);
															}
															else
																MemC_Deloc_(Helper);
														}
														else
															MemC_Deloc_(Helper);
													}
													else
														MemC_Deloc_(Helper);
												}
												else
													Error->E=CLInvalidHostPtr;
											}
											else
												Error->E=CLInvalidProgram;
										else
											Error->E=CLInvalidProgram;
									else
										Error->E=CLInvalidHostPtr;

									MemC_Deloc_(TextSet);
								}
								else
									Error->E=CLInvalidHostPtr;

								MemC_Deloc_(Text);
							}
						}
						else
							Error->E=CLInvalidHostPtr;

						MemC_Deloc_(FileSize);
					}
				}
			}
		}
	}
	else
		Error->E=CLInvalidCommandQueue;

	return Helper;
}
void PenC_CL_Delete_(penc_cl *_PL_ Helper)
{
	if(*Helper)
	{
		cl_kernel *PointerK=(*Helper)->SetKernel+((*Helper)->Kernels-1);

		for(;PointerK>=(*Helper)->SetKernel;PointerK--)
			Devi_Delete_Kernel_(PointerK[0]);
		Devi_Delete_Program_(Acs_(cl_program,(*Helper)->Program));
		MemC_Deloc_(*Helper);
	}
}

static cl_uint _PenC_Select_Key_CL_(void)
{
	cl_uint Key;

	Printer_Console_("Select: ");
	Scanner_Console_("%d",&Key);
	Printer_Console_("\n");

	return Key;
}
static void _PenC_Show_Platform_CL_(cl_platform_id const Platform,name_08 *Buffer)
{
	if(Devi_Info_Platform_(Platform,Buffer,1024,name_08,CL_PLATFORM_NAME)==CL_SUCCESS)
		Printer_Console_(AddressMessage[4],Buffer);
	if(Devi_Info_Platform_(Platform,Buffer,1024,name_08,CL_PLATFORM_VENDOR)==CL_SUCCESS)
		Printer_Console_(AddressMessage[6],AddressInfo[2],Buffer);
	if(Devi_Info_Platform_(Platform,Buffer,1024,name_08,CL_PLATFORM_VERSION)==CL_SUCCESS)
		Printer_Console_(AddressMessage[6],AddressInfo[5],Buffer);
	if(Devi_Info_Platform_(Platform,Buffer,1024,name_08,CL_PLATFORM_PROFILE)==CL_SUCCESS)
		Printer_Console_(AddressMessage[6],AddressInfo[6],Buffer);
	if(Devi_Info_Platform_(Platform,Buffer,1024,name_08,CL_PLATFORM_EXTENSIONS)==CL_SUCCESS)
		Printer_Console_(AddressMessage[6],AddressInfo[7],Buffer);
	if(Devi_Info_Platform_(Platform,Buffer,1024,name_08,CL_PLATFORM_ICD_SUFFIX_KHR)==CL_SUCCESS)
		Printer_Console_(AddressMessage[6],AddressInfo[8],Buffer);
	Printer_Console_(AddressMessage[7]);
}
static void _PenC_Show_Device_CL_(cl_device_id const Device,name_08 *Buffer)
{
	if(Devi_Info_Device_(Device,Buffer,1024,name_08,CL_DEVICE_NAME)==CL_SUCCESS)
		Printer_Console_(AddressMessage[4],Buffer);
	if(Devi_Info_Device_(Device,Buffer,1024,name_08,CL_DEVICE_VENDOR)==CL_SUCCESS)
		Printer_Console_(AddressMessage[6],AddressInfo[2],Buffer);
	if(Devi_Info_Device_(Device,Buffer,1024,name_08,CL_DEVICE_VERSION)==CL_SUCCESS)
		Printer_Console_(AddressMessage[5],AddressInfo[1],AddressInfo[5],Buffer);
	if(Devi_Info_Device_(Device,Buffer,1024,name_08,CL_DRIVER_VERSION)==CL_SUCCESS)
		Printer_Console_(AddressMessage[5],AddressInfo[3],AddressInfo[5],Buffer);
	if(Devi_Info_Device_(Device,Buffer,1024,name_08,CL_DEVICE_OPENCL_C_VERSION)==CL_SUCCESS)
		Printer_Console_(AddressMessage[5],AddressInfo[4],AddressInfo[5],Buffer);
	if(Devi_Info_Device_(Device,Buffer,1024,name_08,CL_DEVICE_PROFILE)==CL_SUCCESS)
		Printer_Console_(AddressMessage[6],AddressInfo[6],Buffer);
	if(Devi_Info_Device_(Device,Buffer,1024,name_08,CL_DEVICE_EXTENSIONS)==CL_SUCCESS)
		Printer_Console_(AddressMessage[6],AddressInfo[7],Buffer);
	if(Devi_Info_Device_(Device,Buffer,1024,name_08,CL_DEVICE_SPIR_VERSIONS)==CL_SUCCESS)
		Printer_Console_(AddressMessage[6],AddressInfo[9],Buffer);
	if(Devi_Info_Device_(Device,Buffer,1024,name_08,CL_DEVICE_BUILT_IN_KERNELS)==CL_SUCCESS)
		Printer_Console_(AddressMessage[6],AddressInfo[10],Buffer);
	Printer_Console_(AddressMessage[7]);
}
penc_eu PenC_CL_Identify_(cl_uint _PL_ SelectPlatform,cl_uint _PL_ SelectDevice)
{
	name_08 Buffer[1024];
	cl_uint Platforms;
	penc_eu ErrorCode;
	
	ErrorCode.I=Devi_Numb_Platforms_(&Platforms);
	if(ErrorCode.E==CLSuccess)
		if(Platforms)
		{
			cl_platform_id *Platform=Line_Alloc_(Platforms,cl_platform_id);

			if(Platform)
			{
				ErrorCode.I=Devi_List_Platforms_(Platform,&Platforms,Platforms);
				if(ErrorCode.E==CLSuccess)
					if(Platforms)
					{
						NAME_08 *Plural=(Platforms>1)?(IdiomInfo+102):(IdiomInfo+103);
						cl_uint Index;

						Printer_Console_(AddressMessage[2],Platforms,AddressInfo[0],Plural);
						for(Index=0;Index<Platforms;Index++)
						{
							ErrorCode.I=Devi_Info_Platform_(Platform[Index],Buffer,1024,name_08,CL_PLATFORM_NAME);
							if(ErrorCode.E==CLSuccess)
								Printer_Console_(AddressMessage[3],Index,Buffer);
							else
								break;
						}
						if(ErrorCode.E==CLSuccess)
						{
							Index=_PenC_Select_Key_CL_();
							if(Index<Platforms)
							{
								cl_uint Devices;

								(*SelectPlatform)=Index;
								_PenC_Show_Platform_CL_(Platform[*SelectPlatform],Buffer);
								ErrorCode.I=Devi_Numb_Devices_(Platform[*SelectPlatform],&Devices);
								if(ErrorCode.E==CLSuccess)
									if(Devices)
									{
										cl_device_id *Device=Line_Alloc_(Devices,cl_device_id);

										if(Device)
										{
											ErrorCode.I=Devi_List_Devices_(Platform[*SelectPlatform],Device,&Devices,Devices);
											if(ErrorCode.E==CLSuccess)
												if(Devices)
												{
													Plural=(Devices>1)?(IdiomInfo+102):(IdiomInfo+103);
													Printer_Console_(AddressMessage[2],Devices,AddressInfo[1],Plural);
													for(Index=0;Index<Devices;Index++)
													{
														ErrorCode.I=Devi_Info_Device_(Device[Index],Buffer,1024,name_08,CL_DEVICE_NAME);
														if(ErrorCode.E==CLSuccess)
															Printer_Console_(AddressMessage[3],Index,Buffer);
														else
															break;
													}
													if(ErrorCode.E==CLSuccess)
													{
														Index=_PenC_Select_Key_CL_();
														if(Index<Devices)
														{
															(*SelectDevice)=Index;
															_PenC_Show_Device_CL_(Device[*SelectDevice],Buffer);
														}
														else
														{
															Printer_Console_(AddressMessage[1]);
															ErrorCode.E=CLInvalidDevice;
														}
													}
												}
												else
												{
													Printer_Console_(AddressMessage[0],AddressInfo[1]);
													ErrorCode.E=CLInvalidDevice;
												}
										}
										else
											ErrorCode.E=CLOutOfHostMemory;

										MemC_Deloc_(Device);
									}
									else
									{
										Printer_Console_(AddressMessage[0],AddressInfo[1]);
										ErrorCode.E=CLInvalidDevice;
									}
							}
							else
							{
								Printer_Console_(AddressMessage[1]);
								ErrorCode.E=CLInvalidPlatform;
							}
						}
					}
					else
					{
						Printer_Console_(AddressMessage[0],AddressInfo[0]);
						ErrorCode.E=CLInvalidPlatform;
					}
			}
			else
				ErrorCode.E=CLOutOfHostMemory;

			MemC_Deloc_(Platform);
		}
		else
		{
			Printer_Console_(AddressMessage[0],AddressInfo[0]);
			ErrorCode.E=CLInvalidPlatform;
		}
	
	return ErrorCode;
}
#endif
#endif
