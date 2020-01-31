#define __STDC_WANT_LIB_EXT1__ (1)
#ifndef uOCLCLIP_USE_
#define uOCLCLIP_USE_
#endif
#include <linclip.h>

MemC_Default_

extern integer main(general)
{
	PenC_SL_Auto_(StringLender,1024);
	MemC_Unit_(oclc_ef,Error,.E=CLSuccess);
	FILE _PL_ Stream=NULL;
	oclc_em *EnvMan=OCLCL.EM.Create_(Error);

	if(EnvMan)
	{
		for(address IdxP=0;IdxP<EnvMan->Platform.Nums;IdxP++)
		{
			MemC_Temp_ND_(penclip,TempString,goto ESCAPE;,1,EnvMan->Platform.List[IdxP].Device.Nums)
			{
				TEXT_08 NameList[2][8]={"bitclip","linclip"};
				penclip _PL_ BinaryPath=TempString;

				for(address IdxN=0;IdxN<2;IdxN++)
				{
					for(address IdxD=0;IdxD<EnvMan->Platform.List[IdxP].Device.Nums;IdxD++)
					{
						penc_sc *TempContainer=NULL;

						PenC_SL_Borrow_Format_T08_(StringLender,TempContainer,"../Release/P%zu D%zu %s.obj",IdxP,IdxD,NameList[IdxN]);
						BinaryPath[IdxD]=TempContainer->String;
					}
					{
						penc_sc *TempContainer=NULL;

						PenC_SL_Borrow_Format_T08_(StringLender,TempContainer,"../../Sources/%s.cl",NameList[IdxN]);
						BitCL.Build.T08_(EnvMan->Platform.List[IdxP].Context,"-I ../../Headers/ -I ../../Sources/ -D uBitC_R16_=0 -D uBitC_R64_=1",TempContainer->String.T08,(text_08**)(BinaryPath),Stream,Error);
					}
					if(Error->E==CLSuccess)
						PenC.SL.Reset_(StringLender);
					else
					{
						PenC_Stream_Format_T08_(O,Stream,"Program Build Failure\r\n");
						break;
					}
				}
			}
			continue;
ESCAPE:
			PenC_Stream_Format_T08_(O,Stream,"String Array Allocation Failure\r\n");
			Error->E=CLOutOfHostMemory;
			break;
		}
		OCLCL.EM.Delete_(&EnvMan);
	}
	else
		PenC_Stream_Format_T08_(O,Stream,"Environment Manager Creation Failure\r\n");

	return Error->I;
}
