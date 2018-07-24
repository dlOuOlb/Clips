#include <CL\opencl.h>
#include <linclip.h>

static penc_eu _Main_Build_Option_(cl_device_id const,name_08*,address);

integer main(general)
{
	static NAME_08 PathI[16]="..\\..\\Kernels\\";
	static NAME_08 PathO[16]="..\\Release\\";
	static name_08 Buffer[40];
	penc_sc Option=PenC_SC_Define_(Buffer);
	cl_uint Select[2];
	penc_eu Error=PenC_CL_Identify_(Select+0,Select+1);

	if(Error.E==CLSuccess)
	{
		devi_qc *QC=Devi_QC_Create_(Select[0],Select[1]);

		if(QC)
		{
			Error=_Main_Build_Option_(QC->Device,Option.String.N08,Option.Capacity);
			if(Error.E==CLSuccess)
			{
				Error=BitC_CL_Binary_(QC->Queue,PathI,PathO,Option.String.N08);
				Printer_Console_("\n");
				if(Error.E==CLSuccess)
				{
					Error=LinC_CL_Binary_(QC->Queue,PathI,PathO,Option.String.N08);
					Printer_Console_("\n");
				}
			}
			else
				Printer_Console_("Error Occurred during Parsing the Build Option\n");
		}
		else
		{
			Printer_Console_("Invalid Platform or Device\n");
			Error.E=CLInvalidCommandQueue;
		}
		Devi_QC_Delete_(&QC);
	}

	return Error.I;
}
static penc_eu _Main_Build_Option_(cl_device_id const Device,name_08 *Option,address Count)
{
	penc_eu Error;

	if(Count>33)
	{
		address Size;

		Error.I=Devi_Size_Info_Device_(Device,&Size,CL_DEVICE_EXTENSIONS);
		if(Error.E==CLSuccess)
		{
			name_08 *Buffer=Line_Alloc_(Size,name_08);

			if(Buffer)
			{
				Error.I=Devi_Info_Device_(Device,Buffer,Size,name_08,CL_DEVICE_EXTENSIONS);
				if(Error.E==CLSuccess)
				{
					{
						Printer_Buffer_(Option,Count,"-D _ABLE_R16_=%d ",(Word_Finder_(Buffer,"cl_khr_fp16")!=NULL));
						Option+=16;
						Count-=16;
					}
					{
						Printer_Buffer_(Option,Count,"-D _ABLE_R64_=%d ",(Word_Finder_(Buffer,"cl_khr_fp64")!=NULL));
						Option+=16;
						Count-=16;
					}
					(*Option)='\0';
				}
			}
			else
				Error.E=CLOutOfHostMemory;

			MemC_Deloc_(Buffer);
		}
	}
	else
		Error.E=CLOutOfHostMemory;

	return Error;
}
