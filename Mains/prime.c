#include <penclip.h>
#include <priclip.h>
#include <timclip.h>

_MemC_Default_

static pric_32 *_Table_Load_(TEXT_08 _PL_ _R_ FileName);
static logical _Table_Save_(TEXT_08 _PL_ _R_ FileName);
static logical _Table_Find_(PRIC_32 _PL_ _R_ Table);

integer main(general)
{
	TEXT_08 FileName[24]="prime table 32-bit.dat";
	pric_32 *Table=_Table_Load_(FileName);

	if(Table)
		goto ACTIVE;
	else
	{
		text_08 Key=-1;

		PenC_Stream_Format_T08_(0,NULL,"Failed to load. Wanna create one?\r\nMay take several hours. [Y/N]: ");
		PenC_Stream_Format_T08_(1,NULL,"%1c",&Key,sizeof(Key));
		switch(Key)
		{
		case 'Y':
		case 'y':
			if(_Table_Save_(FileName))
				Table=_Table_Load_(FileName);
			else
				break;
			if(Table)
ACTIVE:			while(_Table_Find_(Table));
			else
				break;
		default:;
		}
		PenC_Stream_Format_T08_(0,NULL,"Good bye!\r\n");
	}

	PriC.PT.Delete.D32_(&Table);

	return 0;
}

static pric_32 *_Table_Load_(TEXT_08 _PL_ _R_ FileName)
{
	PenC_Stream_Format_T08_(0,NULL,"Try to load the prime table.\r\n");

	return PenC.Object.Load.T08_(FileName,PriC.PT.Load.D32_,NULL,0);
}
static logical _Table_Save_(TEXT_08 _PL_ _R_ FileName)
{
	timc_sw *Watch=TimC.SW.Create_(1);
	timc_sf State;
	logical Flag=0;

	if(Watch)
	{
		MEMCLIP Bits={.V=32};

		PenC_Stream_Format_T08_(0,NULL,"Try to record the prime table.\r\n");
		TimC_SW_Tick_Tock_(Watch,0,State)
			Flag=PenC.Object.Save.T08_(FileName,MemC_Func_Casting_(logical,PriC.PT.Save.D32_,FILE _PL_,GENERAL _PL_ _R_),Bits.P,0);

		if(Flag)
		{
			TIMC_TT Time=TimC.SW.Read.Sum.Tag_(Watch,0);

			if(Time.Overflow)
				PenC_Stream_Format_T08_(0,NULL,"Failed to measure the time consumed.\r\n");
			else
				PenC_Stream_Format_T08_(0,NULL,"Consumed %01d %02d:%02d:%02d.%03d\r\n",Time.Days,Time.Hours,Time.Minutes,Time.Seconds,Time.Milliseconds);
		}
		else
			goto MEMORY;
	}
	else
MEMORY:	PenC_Stream_Format_T08_(0,NULL,"Sorry but failed to create it. Maybe a memory issue.\r\n");

	TimC.SW.Delete_(&Watch);

	return Flag;
}
static logical _Table_Find_(PRIC_32 _PL_ _R_ Table)
{
	data_32 Number;

	PenC_Stream_Format_T08_(0,NULL,"Give me a natural number : ");
	if(PenC_Stream_Format_T08_(1,NULL,"%u",&Number)>0)
	{
		data_32 Factor[32];

		if(PriC.PT.Factor.D32_(Factor,Table,Number))
		{
			PenC_Stream_Format_T08_(0,NULL,"Factorization :\r\n");
			for(data_32 Index=1;Index<=(*Factor);Index++)
				PenC_Stream_Format_T08_(0,NULL,"%u ",Factor[Index]);
			PenC_Stream_Format_T08_(0,NULL,"\r\n");

			return 1;
		}
		else;
	}
	else;

	return 0;
}
