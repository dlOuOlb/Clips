#include <priclip.h>
#include <timclip.h>
#include <stdbool.h>

_MemC_Default_

static pric_32 *_Table_Load_(TEXT_08 _PL_ _R_ FileName);
static logical _Table_Save_(TEXT_08 _PL_ _R_ FileName);
static logical _Table_Find_(PRIC_32 _PL_ _R_ Table);

integer main(general)
{
	TEXT_08 FileName[24]="prime table 32-bit.dat";//file path of the prime table to be stored
	pric_32 *Table=_Table_Load_(FileName);//32-bit prime table

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

	return PenC.Object.Load.T08_(FileName,PriC.PT.Load.D32_,NULL,false);
}
static logical _Table_Save_(TEXT_08 _PL_ _R_ FileName)
{
	TimC_SW_Auto_(SW,1);//stopwatch
	MEMCLIP Bits={.V=32};//all 32-bit prime numbers
	timc_sf State;//timer state
	logical Flag=false;//file save flag

	PenC_Stream_Format_T08_(0,NULL,"Try to record the prime table.\r\n");
	TimC_SW_Tick_Tock_(SW,0,State)
		Flag=PenC.Object.Save.T08_(FileName,MemC_Func_Casting_(logical,PriC.PT.Save.D32_,FILE _PL_,GENERAL _PL_ _R_),Bits.P,false);

	if(Flag)
	{
		TIMC_TT Time=TimC.SW.Read.Sum.Tag_(SW,0);//time tag

		if(Time.Overflow)
			PenC_Stream_Format_T08_(0,NULL,"Failed to measure the time consumed.\r\n");
		else
			PenC_Stream_Format_T08_(0,NULL,"Consumed %01d %02d:%02d:%02d.%03d\r\n",Time.Days,Time.Hours,Time.Minutes,Time.Seconds,Time.Milliseconds);
	}
	else
		PenC_Stream_Format_T08_(0,NULL,"Sorry but failed to create it. Maybe a memory issue.\r\n");

	return Flag;
}
static logical _Table_Find_(PRIC_32 _PL_ _R_ Table)
{
	data_32 Number;//number to be factorized

	PenC_Stream_Format_T08_(0,NULL,"Give me a natural number : ");
	if(PenC_Stream_Format_T08_(1,NULL,"%u",&Number)>0)
	{
		data_32 Factor[32];//factorized sequence

		if(PriC.PT.Factor.D32_(Factor,Table,Number))
		{
			PenC_Stream_Format_T08_(0,NULL,"Factorization :\r\n");
			for(data_32 Index=1;Index<=(*Factor);Index++)
				PenC_Stream_Format_T08_(0,NULL,"%u ",Factor[Index]);
			PenC_Stream_Format_T08_(0,NULL,"\r\n");

			return true;
		}
		else;
	}
	else;

	return false;
}
