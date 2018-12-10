#include <CL\opencl.h>
#include <linclip.h>

static penc_eu _Main_Build_Option_(cl_device_id const,PENC_SC);

integer main(general)
{
	NAME_08 PathI[16]="..\\..\\Kernels\\";
	NAME_08 PathO[16]="..\\Release\\";
	NAME_08 NameL[24]="..\\Release\\log.txt";
	cl_uint Select[2];
	penc_eu Error=PenC_CL_Identify_(Select+0,Select+1,NULL,NULL);

	if(Error.E==CLSuccess)
	{
		PenC_File_Using_(Log,NameL,PenCOpen[3],Error.I)
		{
			name_08 Buffer[64];
			PENC_SC Option=PenC_SC_Assign_(Buffer);
			
			MemC_Using_(devi_qc,QC,Devi_QC_Create_(Select[0],Select[1]),Devi_QC_Delete_)
			{
				Error=_Main_Build_Option_(QC->Device,Option);
				if(Error.E==CLSuccess)
				{
					Error=BitC_CL_Binary_(QC->Queue,PathI,PathO,Option.String.N08,Log);
					PenC_Stream_Format_N08_(0,Log,"\n\n");
					if(Error.E==CLSuccess)
					{
						Error=LinC_CL_Binary_(QC->Queue,PathI,PathO,Option.String.N08,Log);
						PenC_Stream_Format_N08_(0,Log,"\n\n");
						if(Error.E==CLSuccess)
							PenC_Stream_Format_N08_(0,NULL,"Fine\n");
					}
					else
						PenC_Stream_Format_N08_(0,NULL,"Program Build Failure\n");
				}
				else
					PenC_Stream_Format_N08_(0,NULL,"Error Occurred during Parsing the Build Option\n");
			}
			MemC_Catch_
			{
				PenC_Stream_Format_N08_(0,NULL,"Invalid Platform or Device\n");
				Error.E=CLInvalidCommandQueue;
			}
		}
		if(Error.I)
			PenC_Stream_Format_N08_(0,NULL,"File Open Failure\n");
	}
	else
		PenC_Stream_Format_N08_(0,NULL,"Platform or Device Select Failure\n");

	return Error.I;
}
static penc_eu _Main_Build_Option_(cl_device_id const Device,PENC_SC Option)
{
	address Size;
	penc_eu Error;

	Error.I=Devi_Size_Info_Device_(Device,&Size,CL_DEVICE_EXTENSIONS);
	if(Error.E==CLSuccess)
	{
		name_08 *Buffer=MemC_Alloc_1D_(Size,name_08);

		if(Buffer)
		{
			Error.I=Devi_Info_Device_(Device,Buffer,Size,CL_DEVICE_EXTENSIONS);
			if(Error.E==CLSuccess)
				if(PenC_SC_Format_N08_(0,Option,"-D _ABLE_R16_=%d -D _ABLE_R64_=%d",(PenC_String_Finder_N08_(Buffer,"cl_khr_fp16")!=NULL),(PenC_String_Finder_N08_(Buffer,"cl_khr_fp64")!=NULL))<0)
					Error.E=CLOutOfHostMemory;
		}
		else
			Error.E=CLOutOfHostMemory;

		MemC_Deloc_(Buffer);
	}

	return Error;
}
general *_MemC_Malloc_(ADDRESS Size) { return malloc(Size); }
general _MemC_Free_(general _PL_ Memory) { free(Memory); }
