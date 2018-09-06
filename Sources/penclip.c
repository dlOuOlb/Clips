#include "penclip.h"

#if(MemC_Fold_(Definition:Global Constants))
static NAME_08 IdiomVersion[16]="Date:2018.09.05";
static NAME_08 IdiomOpen[16]={'r','b','\0','\0','w','b','\0','\0','r','t','\0','\0','w','t','\0','\0'};
static NAME_08 _PL_ AddressOpen[4]={IdiomOpen+0,IdiomOpen+4,IdiomOpen+8,IdiomOpen+12};
#ifdef __OPENCL_H
static NAME_08 IdiomBuild[104]="Build was successful.\n\0Build was not performed.\n\0Build generated an error.\n\0Build was not finished.\n";
static NAME_08 IdiomInfo[104]="Platform\0Device\0Vendor\0Driver\0OpenCL\0Version\0Profile\0Extensions\0cl_khr_icd\0cl_khr_spir\0Built-in Kernels";
static NAME_08 IdiomMessage[72]="No %s\n\0Invalid Selection\n\0%d %s%s:\n\0[%d] %s\n\0*-- %s --*\n\0%s %s: %s\n";
static NAME_08 _PL_ IdiomPlural=IdiomInfo+102;
static NAME_08 _PL_ AddressBuild[4]={IdiomBuild+0,IdiomBuild+23,IdiomBuild+49,IdiomBuild+76};
static NAME_08 _PL_ AddressInfo[12]={IdiomInfo+0,IdiomInfo+9,IdiomInfo+16,IdiomInfo+23,IdiomInfo+30,IdiomInfo+37,IdiomInfo+45,IdiomInfo+53,IdiomInfo+64,IdiomInfo+75,IdiomInfo+87,IdiomInfo+103};
static NAME_08 _PL_ AddressMessage[8]={IdiomMessage+0,IdiomMessage+7,IdiomMessage+26,IdiomMessage+36,IdiomMessage+45,IdiomMessage+57,IdiomMessage+60,IdiomMessage+66};
#endif
static NAME_08 TableNumeric[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
NAME_08 _PL_ PenClip=IdiomVersion;
NAME_08 _PL_ _PL_ PenCOpen=AddressOpen;
#endif

#if(MemC_Fold_(Definition:I/O Functions))
integer _PenC_Reader_1D_(general _PL_ Line,NAME_08 _PL_ Name,ADDRESS Size,ADDRESS Count)
{
	integer Success;

	if(Line)
	{
		FILE *FilePointer=NULL;

		if(PenC_File_Opener_(FilePointer,Name,AddressOpen[0]))
			Success=0;
		else
		{
			ADDRESS Bytes=Count*Size;

			if(Bytes==PenC_File_Reader_(FilePointer,Line,Bytes,name_08))
				Success=1;
			else
				Success=0;
		}
		PenC_File_Closer_(FilePointer);
	}
	else
		Success=0;

	return Success;
}
integer _PenC_Writer_1D_(GENERAL _PL_ Line,NAME_08 _PL_ Name,ADDRESS Size,ADDRESS Count)
{
	integer Success;

	if(Line)
	{
		FILE *FilePointer=NULL;

		if(PenC_File_Opener_(FilePointer,Name,AddressOpen[1]))
			Success=0;
		else
		{
			ADDRESS Bytes=Count*Size;

			if(Bytes==PenC_File_Writer_(FilePointer,Line,Bytes,name_08))
				Success=1;
			else
				Success=0;
		}
		PenC_File_Closer_(FilePointer);
	}
	else
		Success=0;

	return Success;
}

address PenC_File_Length_(NAME_08 _PL_ Name)
{
	FILE *FilePointer=NULL;
	address Length=0;

	if(PenC_File_Opener_(FilePointer,Name,AddressOpen[0]))
		Length=0;
	else
		if(fseek(FilePointer,0,SEEK_END))
			Length=0;
		else
			Length=(address)ftell(FilePointer);

	PenC_File_Closer_(FilePointer);

	return Length;
}

integer PenC_Pipe_Action_(NAME_08 _PL_ Command,FILE _PL_ Stream)
{
	name_08 Buffer[1024];
	PENC_SC SC=PenC_SC_Assign_(Buffer);
	FILE *ProgramPointer=NULL;
	integer Return=-1;
	
	PenC_Pipe_Opener_(ProgramPointer,Command,AddressOpen[0]);
	if(ProgramPointer)
		while(PenC_SC_Stream_N08_(1,SC,ProgramPointer))
		{
			Return=PenC_Stream_Format_N08_(0,Stream,Buffer);
			if(Return<0)
				break;

			Return=PenC_File_Washer_(ProgramPointer);
			if(Return)
				break;
		}
	PenC_Pipe_Closer_(ProgramPointer,Return);
	
	return Return;
}

errno_t PenC_String_Caster_N08_N16_(NAME_08 *StringS,name_16 _PL_ StringT,ADDRESS CapacityS,ADDRESS CapacityT)
{
	mbstate_t State={._Wchar=0,._Byte=0,._State=0};
	size_t Length;

	return mbsrtowcs_s(&Length,StringT,CapacityT,&StringS,CapacityS,&State);
}
errno_t PenC_String_Caster_N16_N08_(NAME_16 *StringS,name_08 _PL_ StringT,ADDRESS CapacityS,ADDRESS CapacityT)
{
	mbstate_t State={._Wchar=0,._Byte=0,._State=0};
	size_t Length;

	return wcsrtombs_s(&Length,StringT,CapacityT,&StringS,CapacityS,&State);
}

general PenC_Name_Deci_(name_08 _PL_ Line,ADDRESS Number,ADDRESS Count)
{
	if(Line)
	{
		name_08 *Pointer=Line+(Count-1);
		address Dividend=Number;

		for(;Pointer>=Line;Pointer--,Dividend/=10)
			(*Pointer)=TableNumeric[Dividend%10];
	}
}
general PenC_Name_Hexa_(name_08 _PL_ Line,ADDRESS Number,ADDRESS Count)
{
	if(Line)
	{
		name_08 *Pointer=Line+(Count-1);
		address Dividend=Number;

		for(;Pointer>=Line;Pointer--,Dividend>>=4)
			(*Pointer)=TableNumeric[Dividend&15];
	}
}

address PenC_Name_Extend_(NAME_08 _PL_ Line,ADDRESS Length)
{
	address Offset=0;

	if(Line)
	{
		NAME_08 *End=Line;
		NAME_08 *Pointer=(name_08*)PenC_Finder_N08_(Line,'\0',Length);

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
penc_sc _PenC_SC_Assign_(GENERAL _PL_ String,ADDRESS Capacity)
{
	penc_sc SC;

	Acs_(address,SC.Capacity)=Capacity;
	Acs_(GENERAL*,SC.String.X)=String;

	return SC;
}

static address _PenC_Overflow_Add_(ADDRESS A,ADDRESS B)
{
	ADDRESS Return=A+B;

	return ((Return<A)?(0):(Return));
}
static address _PenC_Overflow_Mul_(ADDRESS A,ADDRESS B)
{
	ADDRESS Return=A*B;

	return (((Return/B)==A)?(Return):(0));
}
static general _PenC_SC_Bound_(PENC_SC _PL_ SC)
{
	address Temp=SC->Capacity;

	if(Temp)
	{
		SC->String.N08[0]=0x00;
		SC->String.N08[Temp-1]=0x00;
		Temp>>=1;

		if(Temp)
		{
			SC->String.N16[0]=0x0000;
			SC->String.N16[Temp-1]=0x0000;
			Temp>>=1;

			if(Temp)
			{
				SC->String.N32[0]=0x00000000;
				SC->String.N32[Temp-1]=0x00000000;
			}
		}
	}
}
penc_sc *PenC_SC_Create_(ADDRESS Capacity)
{
	penc_sc *SC;
	
	if(Capacity>RSIZE_MAX)
		SC=NULL;
	else
		if(Capacity)
		{
			SC=MemC_Alloc_Byte_(_PenC_Overflow_Add_(Capacity,sizeof(penc_sc)));
			if(SC)
			{
				Acs_(address,SC->Capacity)=Capacity;
				Acs_(name_08*,SC->String.N08)=(name_08*)(SC+1);
				_PenC_SC_Bound_(SC);
			}
		}
		else
		{
			SC=MemC_Alloc_Unit_(penc_sc);
			if(SC)
				MemC_Clear_Unit_(SC,penc_sc);
		}

	return SC;
}
penc_sc *PenC_SC_Create_Sub_(PENC_SC _PL_ Root,ADDRESS Offset,ADDRESS Length)
{
	penc_sc *SC;

	if(Root)
		if(Length)
		{
			ADDRESS Bound=_PenC_Overflow_Add_(Offset,Length);

			if(Bound)
				if(Bound>Root->Capacity)
					SC=NULL;
				else
				{
					SC=MemC_Alloc_Unit_(penc_sc);
					if(SC)
					{
						Acs_(address,SC->Capacity)=Length;
						Acs_(name_08*,SC->String.N08)=Root->String.N08+Offset;
						_PenC_SC_Bound_(SC);
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
				SC=MemC_Alloc_Unit_(penc_sc);
				if(SC)
					MemC_Clear_Unit_(SC,penc_sc);
			}
	else
		SC=NULL;

	return SC;
}
general PenC_SC_Delete_(penc_sc *_PL_ SC)
{
	MemC_Deloc_(*SC);
}

penc_ss *PenC_SS_Create_(ADDRESS Parts,ADDRESS Total)
{
	penc_ss *SS;

	if(Total>RSIZE_MAX)
		SS=NULL;
	else
		if(Parts)
			if(Total)
			{
				address Size=_PenC_Overflow_Mul_(Parts,sizeof(penc_sc));

				if(Size)
				{
					Size=_PenC_Overflow_Add_(Size,sizeof(penc_ss));
					if(Size)
					{
						Size=_PenC_Overflow_Add_(Size,Total);
						SS=MemC_Alloc_Byte_(Size);
						if(SS)
						{
							Acs_(address,SS->Root.Capacity)=Total;
							Acs_(address,SS->Nums)=Parts;
							Acs_(penc_sc*,SS->Part)=MemC_Clear_1D_(SS+1,Parts,penc_sc);
							Acs_(name_08*,SS->Root.String.N08)=(name_08*)(SS->Part+Parts);
							_PenC_SC_Bound_(&(SS->Root));
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
				address Size=_PenC_Overflow_Mul_(Parts,sizeof(penc_sc));

				if(Size)
				{
					Size=_PenC_Overflow_Add_(Size,sizeof(penc_ss));
					SS=MemC_Alloc_Byte_(Size);
					if(SS)
					{
						Acs_(address,SS->Root.Capacity)=0;
						Acs_(name_08*,SS->Root.String.N08)=NULL;
						Acs_(address,SS->Nums)=Parts;
						Acs_(penc_sc*,SS->Part)=MemC_Clear_1D_(SS+1,Parts,penc_sc);
					}
				}
				else
					SS=NULL;
			}
		else
			if(Total)
			{
				SS=MemC_Alloc_Byte_(_PenC_Overflow_Add_(Total,sizeof(penc_ss)));
				if(SS)
				{
					Acs_(address,SS->Root.Capacity)=Total;
					Acs_(name_08*,SS->Root.String.N08)=(name_08*)(SS+1);
					Acs_(address,SS->Nums)=0;
					Acs_(penc_sc*,SS->Part)=NULL;
					_PenC_SC_Bound_(&(SS->Root));
				}
			}
			else
			{
				SS=MemC_Alloc_Unit_(penc_ss);
				if(SS)
					MemC_Clear_Unit_(SS,penc_ss);
			}

	return SS;
}
general PenC_SS_Delete_(penc_ss *_PL_ SS)
{
	MemC_Deloc_(*SS);
}
integer PenC_SS_Assign_(PENC_SS _PL_ SS,ADDRESS Index,ADDRESS Offset,ADDRESS Length)
{
	if(SS)
		if(Index<SS->Nums)
			if(Offset>SS->Root.Capacity)
				goto FAILURE;
			else
				if(Length)
				{
					ADDRESS Bound=_PenC_Overflow_Add_(Offset,Length);

					if(Bound>SS->Root.Capacity)
						goto FAILURE;
					else
					{
						Acs_(address,SS->Part[Index].Capacity)=Length;
						Acs_(name_08*,SS->Part[Index].String.N08)=SS->Root.String.N08+Offset;
						_PenC_SC_Bound_(SS->Part+Index);

						goto SUCCESS;
					}
				}
				else
				{
					Acs_(address,SS->Part[Index].Capacity)=0;
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
static address _PenC_File_Length_S_(address *FileSize,NAME_08 _PL_*FileName,ADDRESS Files)
{
	NAME_08 _PL_ _PL_ End=FileName+Files;
	address Total=0;

	for(;FileName<End;FileName++,FileSize++)
	{
		FileSize[0]=PenC_File_Length_(FileName[0]);
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
static integer _PenC_Line_Reader_S_(name_08 *Line,NAME_08 _PL_ *FileName,ADDRESS *FileSize,ADDRESS Files)
{
	NAME_08 _PL_ _PL_ End=FileName+Files;
	integer Success;

	for(;FileName<End;FileName++,FileSize++)
		if(PenC_Reader_1D_(Line,FileName[0],FileSize[0],name_08))
			Line+=FileSize[0];
		else
			break;

	if(FileName==End)
		Success=1;
	else
		Success=0;

	return Success;
}
static general _PenC_Build_Log_CL_(cl_device_id const Device,cl_program const Program,FILE _PL_ Stream)
{
	{
		cl_build_status Status;

		if(Devi_Info_Build_(Device,Program,&Status,1,cl_build_status,CL_PROGRAM_BUILD_STATUS)==CL_SUCCESS)
			switch(Status)
			{
			case CL_BUILD_SUCCESS:
				PenC_Stream_Format_N08_(0,Stream,AddressBuild[0]);
				break;
			case CL_BUILD_NONE:
				PenC_Stream_Format_N08_(0,Stream,AddressBuild[1]);
				break;
			case CL_BUILD_ERROR:
				PenC_Stream_Format_N08_(0,Stream,AddressBuild[2]);
				break;
			case CL_BUILD_IN_PROGRESS:
				PenC_Stream_Format_N08_(0,Stream,AddressBuild[3]);
				break;
			default:;
			}
	}
	{
		address StringSize;

		if(Devi_Size_Info_Build_(Device,Program,&StringSize,CL_PROGRAM_BUILD_LOG)==CL_SUCCESS)
		{
			name_08 *String=MemC_Alloc_1D_(StringSize,name_08);

			if(String)
				if(Devi_Info_Build_(Device,Program,String,StringSize,name_08,CL_PROGRAM_BUILD_LOG)==CL_SUCCESS)
					PenC_Stream_Format_N08_(0,Stream,String);

			MemC_Deloc_(String);
		}
	}
}
penc_eu PenC_CL_Binary_(cl_command_queue const Queue,NAME_08 _PL_ PathOut,NAME_08 _PL_ _PL_ ListPathIn,NAME_08 _PL_ Option,ADDRESS Files,FILE _PL_ Stream)
{
	cl_device_id Device;
	penc_eu Error;

	Error.I=Devi_Info_Queue_(Queue,&Device,1,cl_device_id,CL_QUEUE_DEVICE);
	if(Error.E==CLSuccess)
	{
		cl_context Context;

		Error.I=Devi_Info_Queue_(Queue,&Context,1,cl_context,CL_QUEUE_CONTEXT);
		if(Error.E==CLSuccess)
		{
			address *FileSize=MemC_Alloc_1D_(Files<<1,address);

			if(FileSize)
			{
				ADDRESS SizeText=_PenC_File_Length_S_(FileSize,ListPathIn,Files);

				if(SizeText)
				{
					name_08 *Text=MemC_Alloc_1D_(SizeText+1,name_08);

					if(Text)
					{
						name_08 **TextSet=(name_08**)(FileSize+Files);

						Text[SizeText]='\0';
						if(_PenC_Line_Reader_S_(Text,ListPathIn,FileSize,Files))
							if(MemC_Assign_1D_N_(TextSet,Text,FileSize,Files,name_08)==SizeText)
							{
								cl_program Program=Devi_Create_Program_Source_(Context,TextSet,FileSize,(cl_uint)Files,&(Error.I));

								if(Error.E==CLSuccess)
								{
									Error.I=Devi_Build_(Program,Option);
									_PenC_Build_Log_CL_(Device,Program,Stream);
									if(Error.E==CLSuccess)
									{
										address SizeBinary;

										Error.I=Devi_Info_Program_(Program,&SizeBinary,1,address,CL_PROGRAM_BINARY_SIZES);
										if(Error.E==CLSuccess)
										{
											name_08 *Binary=MemC_Alloc_1D_(SizeBinary,name_08);

											if(Binary)
											{
												Error.I=Devi_Info_Program_(Program,&Binary,1,name_08*,CL_PROGRAM_BINARIES);
												if(Error.E==CLSuccess)
													if(!PenC_Writer_1D_(Binary,PathOut,SizeBinary,name_08))
														Error.E=CLInvalidValue;
											}
											else
												Error.E=CLOutOfHostMemory;

											MemC_Deloc_(Binary);
										}
									}
								}
								Devi_Delete_Program_(Program);
							}
							else
								Error.E=CLInvalidProgram;
						else
							Error.E=CLInvalidProgram;
					}
					else
						Error.E=CLOutOfHostMemory;

					MemC_Deloc_(Text);
				}
				else
					Error.E=CLOutOfHostMemory;
			}
			else
				Error.E=CLOutOfHostMemory;

			MemC_Deloc_(FileSize);
		}
	}

	return Error;
}
penc_cl *PenC_CL_Create_(cl_command_queue const Queue,NAME_08 _PL_ PathObj,NAME_08 _PL_ _PL_ SetIndicator,NAME_08 _PL_ Option,const cl_uint Kernels,penc_eu _PL_ Error,FILE _PL_ Stream)
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
						ADDRESS SizeBinary=PenC_File_Length_(PathObj);
						name_08 *Binary=MemC_Alloc_1D_(SizeBinary,name_08);

						if(Binary)
							if(PenC_Reader_1D_(Binary,PathObj,SizeBinary,name_08))
							{
								{
									address SizeTemp;

									SizeTemp=_PenC_Overflow_Mul_(Kernels,sizeof(cl_kernel));
									if(SizeTemp)
									{
										SizeTemp=_PenC_Overflow_Add_(SizeTemp,MemC_Size_(address,Dimensions));
										if(SizeTemp)
										{
											SizeTemp=_PenC_Overflow_Add_(SizeTemp,sizeof(penc_cl));
											Helper=MemC_Alloc_Byte_(SizeTemp);
										}
									}
								}
								if(Helper)
								{
									Acs_(address*,Helper->SizeWorker)=(address*)(Helper+1);
									Acs_(cl_kernel*,Helper->SetKernel)=(cl_kernel*)(Helper->SizeWorker+Dimensions);

									Error->I=Devi_Info_Device_(Device,(general*)(Helper->SizeWorker),Dimensions,address,CL_DEVICE_MAX_WORK_ITEM_SIZES);
									if(Error->E==CLSuccess)
									{
										Error->I=Devi_Info_Device_(Device,(general*)&(Helper->Workers),1,address,CL_DEVICE_MAX_WORK_GROUP_SIZE);
										if(Error->E==CLSuccess)
										{
											Error->I=Devi_Info_Device_(Device,(general*)&(Helper->SizeLocal),1,cl_ulong,CL_DEVICE_LOCAL_MEM_SIZE);
											if(Error->E==CLSuccess)
											{
												Acs_(cl_program,Helper->Program)=Devi_Create_Program_Binary_(&Device,Context,(unsigned char**)&Binary,&SizeBinary,1,&(Error->I));
												if(Helper->Program)
												{
													Error->I=Devi_Build_(Helper->Program,Option);
													_PenC_Build_Log_CL_(Device,Helper->Program,Stream);
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
									Error->E=CLOutOfHostMemory;
							}
							else
								Error->E=CLInvalidValue;
						else
							Error->E=CLOutOfHostMemory;

						MemC_Deloc_(Binary);
					}
				}
			}
		}
	}
	else
		Error->E=CLInvalidCommandQueue;

	return Helper;
}
general PenC_CL_Delete_(penc_cl *_PL_ Helper)
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

static cl_uint _PenC_Select_Key_CL_(FILE _PL_ StreamI,FILE _PL_ StreamO)
{
	cl_uint Key;

	PenC_Stream_Format_N08_(0,StreamO,"Select:");
	PenC_Stream_Format_N08_(1,StreamI,"%d",&Key);
	PenC_Stream_Format_N08_(0,StreamO,"\n[%d] is selected.\n",Key);

	return Key;
}
static general _PenC_Show_Platform_CL_(cl_platform_id const Platform,PENC_SC SC,FILE _PL_ Stream)
{
	if(Devi_Info_Platform_(Platform,SC.String.N08,SC.Capacity,name_08,CL_PLATFORM_NAME)==CL_SUCCESS)
		PenC_Stream_Format_N08_(0,Stream,AddressMessage[4],SC.String.N08);
	if(Devi_Info_Platform_(Platform,SC.String.N08,SC.Capacity,name_08,CL_PLATFORM_VENDOR)==CL_SUCCESS)
		PenC_Stream_Format_N08_(0,Stream,AddressMessage[6],AddressInfo[2],SC.String.N08);
	if(Devi_Info_Platform_(Platform,SC.String.N08,SC.Capacity,name_08,CL_PLATFORM_VERSION)==CL_SUCCESS)
		PenC_Stream_Format_N08_(0,Stream,AddressMessage[6],AddressInfo[5],SC.String.N08);
	if(Devi_Info_Platform_(Platform,SC.String.N08,SC.Capacity,name_08,CL_PLATFORM_PROFILE)==CL_SUCCESS)
		PenC_Stream_Format_N08_(0,Stream,AddressMessage[6],AddressInfo[6],SC.String.N08);
	if(Devi_Info_Platform_(Platform,SC.String.N08,SC.Capacity,name_08,CL_PLATFORM_EXTENSIONS)==CL_SUCCESS)
		PenC_Stream_Format_N08_(0,Stream,AddressMessage[6],AddressInfo[7],SC.String.N08);
	if(Devi_Info_Platform_(Platform,SC.String.N08,SC.Capacity,name_08,CL_PLATFORM_ICD_SUFFIX_KHR)==CL_SUCCESS)
		PenC_Stream_Format_N08_(0,Stream,AddressMessage[6],AddressInfo[8],SC.String.N08);
	PenC_Stream_Format_N08_(0,Stream,AddressMessage[7]);
}
static general _PenC_Show_Device_CL_(cl_device_id const Device,PENC_SC SC,FILE _PL_ Stream)
{
	if(Devi_Info_Device_(Device,SC.String.N08,SC.Capacity,name_08,CL_DEVICE_NAME)==CL_SUCCESS)
		PenC_Stream_Format_N08_(0,Stream,AddressMessage[4],SC.String.N08);
	if(Devi_Info_Device_(Device,SC.String.N08,SC.Capacity,name_08,CL_DEVICE_VENDOR)==CL_SUCCESS)
		PenC_Stream_Format_N08_(0,Stream,AddressMessage[6],AddressInfo[2],SC.String.N08);
	if(Devi_Info_Device_(Device,SC.String.N08,SC.Capacity,name_08,CL_DEVICE_VERSION)==CL_SUCCESS)
		PenC_Stream_Format_N08_(0,Stream,AddressMessage[5],AddressInfo[1],AddressInfo[5],SC.String.N08);
	if(Devi_Info_Device_(Device,SC.String.N08,SC.Capacity,name_08,CL_DRIVER_VERSION)==CL_SUCCESS)
		PenC_Stream_Format_N08_(0,Stream,AddressMessage[5],AddressInfo[3],AddressInfo[5],SC.String.N08);
	if(Devi_Info_Device_(Device,SC.String.N08,SC.Capacity,name_08,CL_DEVICE_OPENCL_C_VERSION)==CL_SUCCESS)
		PenC_Stream_Format_N08_(0,Stream,AddressMessage[5],AddressInfo[4],AddressInfo[5],SC.String.N08);
	if(Devi_Info_Device_(Device,SC.String.N08,SC.Capacity,name_08,CL_DEVICE_PROFILE)==CL_SUCCESS)
		PenC_Stream_Format_N08_(0,Stream,AddressMessage[6],AddressInfo[6],SC.String.N08);
	if(Devi_Info_Device_(Device,SC.String.N08,SC.Capacity,name_08,CL_DEVICE_EXTENSIONS)==CL_SUCCESS)
		PenC_Stream_Format_N08_(0,Stream,AddressMessage[6],AddressInfo[7],SC.String.N08);
	if(Devi_Info_Device_(Device,SC.String.N08,SC.Capacity,name_08,CL_DEVICE_SPIR_VERSIONS)==CL_SUCCESS)
		PenC_Stream_Format_N08_(0,Stream,AddressMessage[6],AddressInfo[9],SC.String.N08);
	if(Devi_Info_Device_(Device,SC.String.N08,SC.Capacity,name_08,CL_DEVICE_BUILT_IN_KERNELS)==CL_SUCCESS)
		PenC_Stream_Format_N08_(0,Stream,AddressMessage[6],AddressInfo[10],SC.String.N08);
	PenC_Stream_Format_N08_(0,Stream,AddressMessage[7]);
}
penc_eu PenC_CL_Identify_(cl_uint _PL_ SelectPlatform,cl_uint _PL_ SelectDevice,FILE _PL_ StreamI,FILE _PL_ StreamO)
{
	name_08 Buffer[1024];
	PENC_SC SC=PenC_SC_Assign_(Buffer);
	cl_uint Platforms;
	penc_eu ErrorCode;
	
	ErrorCode.I=Devi_Numb_Platforms_(&Platforms);
	if(ErrorCode.E==CLSuccess)
		if(Platforms)
		{
			cl_platform_id *Platform=MemC_Alloc_1D_(Platforms,cl_platform_id);

			if(Platform)
			{
				ErrorCode.I=Devi_List_Platforms_(Platform,&Platforms,Platforms);
				if(ErrorCode.E==CLSuccess)
					if(Platforms)
					{
						NAME_08 *Plural=(Platforms>1)?(IdiomPlural+0):(IdiomPlural+1);
						cl_uint Index;

						PenC_Stream_Format_N08_(0,StreamO,AddressMessage[2],Platforms,AddressInfo[0],Plural);
						for(Index=0;Index<Platforms;Index++)
						{
							ErrorCode.I=Devi_Info_Platform_(Platform[Index],SC.String.N08,SC.Capacity,name_08,CL_PLATFORM_NAME);
							if(ErrorCode.E==CLSuccess)
								PenC_Stream_Format_N08_(0,StreamO,AddressMessage[3],Index,SC.String.N08);
							else
								break;
						}
						if(ErrorCode.E==CLSuccess)
						{
							Index=_PenC_Select_Key_CL_(StreamI,StreamO);
							if(Index<Platforms)
							{
								cl_uint Devices;

								(*SelectPlatform)=Index;
								_PenC_Show_Platform_CL_(Platform[*SelectPlatform],SC,StreamO);
								ErrorCode.I=Devi_Numb_Devices_(Platform[*SelectPlatform],&Devices);
								if(ErrorCode.E==CLSuccess)
									if(Devices)
									{
										cl_device_id *Device=MemC_Alloc_1D_(Devices,cl_device_id);

										if(Device)
										{
											ErrorCode.I=Devi_List_Devices_(Platform[*SelectPlatform],Device,&Devices,Devices);
											if(ErrorCode.E==CLSuccess)
												if(Devices)
												{
													Plural=(Devices>1)?(IdiomPlural+0):(IdiomPlural+1);
													PenC_Stream_Format_N08_(0,StreamO,AddressMessage[2],Devices,AddressInfo[1],Plural);
													for(Index=0;Index<Devices;Index++)
													{
														ErrorCode.I=Devi_Info_Device_(Device[Index],SC.String.N08,SC.Capacity,name_08,CL_DEVICE_NAME);
														if(ErrorCode.E==CLSuccess)
															PenC_Stream_Format_N08_(0,StreamO,AddressMessage[3],Index,SC.String.N08);
														else
															break;
													}
													if(ErrorCode.E==CLSuccess)
													{
														Index=_PenC_Select_Key_CL_(StreamI,StreamO);
														if(Index<Devices)
														{
															(*SelectDevice)=Index;
															_PenC_Show_Device_CL_(Device[*SelectDevice],SC,StreamO);
														}
														else
														{
															PenC_Stream_Format_N08_(0,StreamO,AddressMessage[1]);
															ErrorCode.E=CLInvalidDevice;
														}
													}
												}
												else
												{
													PenC_Stream_Format_N08_(0,StreamO,AddressMessage[0],AddressInfo[1]);
													ErrorCode.E=CLInvalidDevice;
												}
										}
										else
											ErrorCode.E=CLOutOfHostMemory;

										MemC_Deloc_(Device);
									}
									else
									{
										PenC_Stream_Format_N08_(0,StreamO,AddressMessage[0],AddressInfo[1]);
										ErrorCode.E=CLInvalidDevice;
									}
							}
							else
							{
								PenC_Stream_Format_N08_(0,StreamO,AddressMessage[1]);
								ErrorCode.E=CLInvalidPlatform;
							}
						}
					}
					else
					{
						PenC_Stream_Format_N08_(0,StreamO,AddressMessage[0],AddressInfo[0]);
						ErrorCode.E=CLInvalidPlatform;
					}
			}
			else
				ErrorCode.E=CLOutOfHostMemory;

			MemC_Deloc_(Platform);
		}
		else
		{
			PenC_Stream_Format_N08_(0,StreamO,AddressMessage[0],AddressInfo[0]);
			ErrorCode.E=CLInvalidPlatform;
		}
	
	return ErrorCode;
}
#endif
#endif
