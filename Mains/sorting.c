#include <penclip.h>
#include <linclip.h>
#include <timclip.h>

_MemC_Default_;
static general _Naive_Rand_(inte_32 *_R_,ADDRESS);
static integer _Naive_Comp_(INTE_32 _PL_,INTE_32 _PL_);

integer main(general)
{
	FILE _PL_ Stream=NULL;
	ADDRESS Length=1<<20;
	INTEGER Trials=256;
	inte_32 *Array=MemC_Alloc_ND_(inte_32,1,Length);
	general *Buffer=MemC.Alloc.Byte_(MemC_Size_(inte_32,Length));
	timc_sw *SW=TimC.SW.Create_(2);
	timc_rg *RG=TimC.RG.Create_(1);
	integer MainFlag=0;

	if(Array&&SW&&RG)
	{
		timc_sf SWState[2];

		PenC_Stream_Format_T08_(0,Stream,"Time Measurement for Random Generation and Sorting\r\n%d integers(32-bit) up to %d : %d tries\r\n",Length,RAND_MAX,Trials);

		PenC_Stream_Format_T08_(0,Stream,"\r\nNaive Approach : rand() and qsort().\r\n");
		{
			PenC_Stream_Format_T08_(0,Stream,"Warming up...\r\n");
			{
				MemC_Clear_1D_(SWState,2);
				TimC.SW.All.Reset_(SW);
				_Naive_Rand_(Array,Length);

				PenC_Stream_Format_T08_(0,Stream,"%d %d %d ... %d %d %d\r\n",Array[0],Array[1],Array[2],Array[Length-3],Array[Length-2],Array[Length-1]);
				qsort(Array,Length,sizeof(*Array),_Naive_Comp_);
				PenC_Stream_Format_T08_(0,Stream,"%d %d %d ... %d %d %d\r\n",Array[0],Array[1],Array[2],Array[Length-3],Array[Length-2],Array[Length-1]);
			}
			for(integer Try=0;Try<Trials;Try++)
			{
				PenC_Stream_Format_T08_(0,Stream,"\rRepetition %4d/%4d",Try,Trials);

				TimC_SW_Tick_Tock_(SW,0,SWState[0])
					_Naive_Rand_(Array,Length);

				TimC_SW_Tick_Tock_(SW,1,SWState[1])
					qsort(Array,Length,sizeof(*Array),_Naive_Comp_);

			}
			if((SWState[0]|SWState[1])==TimCStateStopped)
			{
				PenC_Stream_Format_T08_(0,Stream,"\rRepetition %4d/%4d\r\n",Trials,Trials);
				PenC_Stream_Format_T08_(0,Stream,"average %f ms per try for random generation\r\n",1000.0F*TimC.SW.Read.Mean_(SW,0));
				PenC_Stream_Format_T08_(0,Stream,"average %f ms per try for sorting\r\n",1000.0F*TimC.SW.Read.Mean_(SW,1));
			}
			else
			{
				MainFlag=-2;
				goto KILL;
			}
		}

		PenC_Stream_Format_T08_(0,Stream,"\r\nUnfair Approach : MWC64X and radix-sort.\r\n");
		{
			PenC_Stream_Format_T08_(0,Stream,"Warming up...\r\n");
			{
				MemC_Clear_1D_(SWState,2);
				TimC.SW.All.Reset_(SW);
				TimC.RG.Uni.I32_(RG,0,Array,Length,0,RAND_MAX);

				PenC_Stream_Format_T08_(0,Stream,"%d %d %d ... %d %d %d\r\n",Array[0],Array[1],Array[2],Array[Length-3],Array[Length-2],Array[Length-1]);
				LinC.Order.I32_(Array,NULL,Buffer,Length,BitCNull);
				PenC_Stream_Format_T08_(0,Stream,"%d %d %d ... %d %d %d\r\n",Array[0],Array[1],Array[2],Array[Length-3],Array[Length-2],Array[Length-1]);
			}
			for(integer Try=0;Try<Trials;Try++)
			{
				PenC_Stream_Format_T08_(0,Stream,"\rRepetition %4d/%4d",Try,Trials);

				TimC_SW_Tick_Tock_(SW,0,SWState[0])
					TimC.RG.Uni.I32_(RG,0,Array,Length,0,RAND_MAX);

				TimC_SW_Tick_Tock_(SW,1,SWState[1])
					LinC.Order.I32_(Array,NULL,Buffer,Length,BitCNull);
			}
			if((SWState[0]|SWState[1])==TimCStateStopped)
			{
				PenC_Stream_Format_T08_(0,Stream,"\rRepetition %4d/%4d\r\n",Trials,Trials);
				PenC_Stream_Format_T08_(0,Stream,"average %f ms per try for random generation\r\n",1000.0F*TimC.SW.Read.Mean_(SW,0));
				PenC_Stream_Format_T08_(0,Stream,"average %f ms per try for sorting\r\n",1000.0F*TimC.SW.Read.Mean_(SW,1));
			}
			else
			{
				MainFlag=-2;
				goto KILL;
			}
		}
	}
	else
		MainFlag=-1;
KILL:
	TimC.RG.Delete_(&RG);
	TimC.SW.Delete_(&SW);
	MemC_Deloc_(Buffer);
	MemC_Deloc_(Array);

	switch(MainFlag)
	{
	case 0:
		PenC_Stream_Format_T08_(0,Stream,"\r\nDone\r\n");
		break;
	case-1:
		PenC_Stream_Format_T08_(0,Stream,"\r\nMemory Allocation Failed\r\n");
		break;
	case-2:
		PenC_Stream_Format_T08_(0,Stream,"\r\nStopwatch Overflow Detected\r\n");
		break;
	default:
		PenC_Stream_Format_T08_(0,Stream,"\r\nUnknown Error Occurred\r\n");
	}

	return MainFlag;
}

static general _Naive_Rand_(inte_32 *_R_ Ptr,ADDRESS Length)
{
	for(INTE_32 _PL_ End=Ptr+Length;Ptr<End;Ptr++)
		*Ptr=rand();
}
static integer _Naive_Comp_(INTE_32 _PL_ A,INTE_32 _PL_ B)
{
	return (((*A)>(*B))-((*A)<(*B)));
}
