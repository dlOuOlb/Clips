#include <CL/opencl.h>
#include <linclip.h>

integer main(general)
{
	FILE _PL_ Stream=NULL;
	penc_sl *StringLender=PenC.SL.Create_(1024);
	oclc_ef _Error={.E=CLSuccess},_PL_ Error=&_Error;
	
	if(StringLender)
	{
		oclc_em *EnvMan=OCLC.EM.Create_(Error);

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

							PenC_SL_Borrow_Format_T08_(StringLender,TempContainer,"../Release/P%d D%d %s.obj",IdxP,IdxD,NameList[IdxN]);
							BinaryPath[IdxD]=TempContainer->String;
						}
						{
							penc_sc *TempContainer=NULL;

							PenC_SL_Borrow_Format_T08_(StringLender,TempContainer,"../../Sources/%s.cl",NameList[IdxN]);
							BitC.CL.Ready.T08_(EnvMan->Platform.List[IdxP].Context,"-I ../../Headers/ -I ../../Sources/ -D _BitC_R16_=0 -D _BitC_R64_=1",TempContainer->String.T08,(text_08**)BinaryPath,Stream,Error);
						}
						if(Error->E==CLSuccess)
							PenC.SL.Reset_(StringLender);
						else
						{
							PenC_Stream_Format_T08_(0,Stream,"Program Build Failure\r\n");
							break;
						}
					}
				}
				continue;
ESCAPE:
				PenC_Stream_Format_T08_(0,Stream,"String Array Allocation Failure\r\n");
				Error->E=CLOutOfHostMemory;
				break;
			}
			OCLC.EM.Delete_(&EnvMan);
		}
		else
			PenC_Stream_Format_T08_(0,Stream,"Environment Manager Creation Failure\r\n");

		PenC.SL.Delete_(&StringLender);
	}
	else
	{
		PenC_Stream_Format_T08_(0,Stream,"String Lender Creation Failure\r\n");
		Error->E=CLOutOfHostMemory;
	}

	return Error->I;
}
_MemC_Default_
