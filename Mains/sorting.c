#define __STDC_WANT_LIB_EXT1__ (1)
#include <linclip.h>
#include <timclip.h>

#include <stdbool.h>

MemC_Default_;

static general Main_Naive_Rand_(inte_32 *_R_ Ptr,ADDRESS Lng) { for(INTE_32 _PL_ End=Ptr+Lng;Ptr<End;*(Ptr++)=rand());return; }
static integer Main_Naive_Comp_(INTE_32 _PL_ _R_ A,INTE_32 _PL_ _R_ B) { return(((*A)>(*B))-((*A)<(*B))); }
static real_64 Main_Time_Cast_(REAL_32 Time) { return (1000.0*((real_64)(Time))); }
extern integer main(general)
{
	TimC_SW_Auto_(SW,2);//a stopwatch
	TimC_RG_Auto_(RG,1,(data_64)time(NULL));//a random generator
	FILE _PL_ Stream=NULL;//the stream to print outputs
	ADDRESS Length=1<<20;//the number of random integers
	INTEGER Trials=256;//the number of trials
	inte_32 *Array=MemC_Alloc_ND_(inte_32,1,Length);//an array for random integers
	general *Buffer=MemC.Alloc.Byte_(MemC_Size_(inte_32,Length));//a calculation buffer
	integer MainFlag=0;//an error flag

	if(Array)
	{
		PenC_Stream_Format_T08_(O,Stream,"Time Measurement for Random Generation and Sorting\r\n%zu integers(32-bit) up to %d : %d tries\r\n",Length,RAND_MAX,Trials);

		PenC_Stream_Format_T08_(O,Stream,"\r\nNaive Approach : rand() and qsort().\r\n");
		{
			PenC_Stream_Format_T08_(O,Stream,"Warming up...\r\n");
			{
				TimC.SW.All.Reset_(SW);
				Main_Naive_Rand_(Array,Length);

				PenC_Stream_Format_T08_(O,Stream,"%d %d %d ... %d %d %d\r\n",Array[0],Array[1],Array[2],Array[Length-3],Array[Length-2],Array[Length-1]);
				qsort(Array,Length,sizeof(*Array),Main_Naive_Comp_);
				PenC_Stream_Format_T08_(O,Stream,"%d %d %d ... %d %d %d\r\n",Array[0],Array[1],Array[2],Array[Length-3],Array[Length-2],Array[Length-1]);
			}
			for(integer Try=0;Try<Trials;Try++)
			{
				PenC_Stream_Format_T08_(O,Stream,"\rRepetition %4d/%4d",Try,Trials);

				TimC_SW_Tick_Tock_(SW,0)
					Main_Naive_Rand_(Array,Length);

				if(TimC.SW.Read.State_(SW,0)==TimCStateStopped);else break;

				TimC_SW_Tick_Tock_(SW,1)
					qsort(Array,Length,sizeof(*Array),Main_Naive_Comp_);

				if(TimC.SW.Read.State_(SW,1)==TimCStateStopped);else break;
			}
			if((TimC.SW.Read.State_(SW,0)==TimCStateStopped)&&(TimC.SW.Read.State_(SW,1)==TimCStateStopped))
			{
				PenC_Stream_Format_T08_(O,Stream,"\rRepetition %4d/%4d\r\n",Trials,Trials);
				PenC_Stream_Format_T08_(O,Stream,"average %.3f ms per try for random generation\r\n",Main_Time_Cast_(TimC.SW.Read.Mean.R32_(SW,0)));
				PenC_Stream_Format_T08_(O,Stream,"average %.3f ms per try for sorting\r\n",Main_Time_Cast_(TimC.SW.Read.Mean.R32_(SW,1)));
			}
			else
			{
				MainFlag=-2;
				goto KILL;
			}
		}

		PenC_Stream_Format_T08_(O,Stream,"\r\nUnfair Approach : MWC64X, radix-sort, and additional memory.\r\n");
		{
			PenC_Stream_Format_T08_(O,Stream,"Warming up...\r\n");
			{
				TimC.SW.All.Reset_(SW);
				TimC.RG.Uni.I32_(RG,0,Array,Length,0,RAND_MAX);

				PenC_Stream_Format_T08_(O,Stream,"%d %d %d ... %d %d %d\r\n",Array[0],Array[1],Array[2],Array[Length-3],Array[Length-2],Array[Length-1]);
				LinC.Order.I32_(Array,NULL,Buffer,Length,false);
				PenC_Stream_Format_T08_(O,Stream,"%d %d %d ... %d %d %d\r\n",Array[0],Array[1],Array[2],Array[Length-3],Array[Length-2],Array[Length-1]);
			}
			for(integer Try=0;Try<Trials;Try++)
			{
				PenC_Stream_Format_T08_(O,Stream,"\rRepetition %4d/%4d",Try,Trials);

				TimC_SW_Tick_Tock_(SW,0)
					TimC.RG.Uni.I32_(RG,0,Array,Length,0,RAND_MAX);

				if(TimC.SW.Read.State_(SW,0)==TimCStateStopped);else break;

				TimC_SW_Tick_Tock_(SW,1)
					LinC.Order.I32_(Array,NULL,Buffer,Length,false);

				if(TimC.SW.Read.State_(SW,1)==TimCStateStopped);else break;
			}
			if((TimC.SW.Read.State_(SW,0)==TimCStateStopped)&&(TimC.SW.Read.State_(SW,1)==TimCStateStopped))
			{
				PenC_Stream_Format_T08_(O,Stream,"\rRepetition %4d/%4d\r\n",Trials,Trials);
				PenC_Stream_Format_T08_(O,Stream,"average %.3f ms per try for random generation\r\n",Main_Time_Cast_(TimC.SW.Read.Mean.R32_(SW,0)));
				PenC_Stream_Format_T08_(O,Stream,"average %.3f ms per try for sorting\r\n",Main_Time_Cast_(TimC.SW.Read.Mean.R32_(SW,1)));
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
	MemC_Deloc_(Buffer);
	MemC_Deloc_(Array);

	switch(MainFlag)
	{
	case 0:
		PenC_Stream_Format_T08_(O,Stream,"\r\nDone\r\n");
		break;
	case-1:
		PenC_Stream_Format_T08_(O,Stream,"\r\nMemory Allocation Failed\r\n");
		break;
	case-2:
		PenC_Stream_Format_T08_(O,Stream,"\r\nStopwatch Overflow Detected\r\n");
		break;
	default:
		PenC_Stream_Format_T08_(O,Stream,"\r\nUnknown Error Occurred\r\n");
	}

	return MainFlag;
}
