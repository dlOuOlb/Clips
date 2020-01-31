#define __STDC_WANT_LIB_EXT1__ (1)
#include <timclip.h>
#include <priclip.h>

#include <stdbool.h>
#include <inttypes.h>

#if(Fold_(Type Selection))

#if(UINTPTR_MAX==UINT8_MAX)
#define Main_Bits_ 08
#define Main_Form_ PRIu8
#elif(UINTPTR_MAX==UINT16_MAX)
#define Main_Bits_ 16
#define Main_Form_ PRIu16
#elif(UINTPTR_MAX==UINT32_MAX)
#define Main_Bits_ 32
#define Main_Form_ PRIu32
#elif(UINTPTR_MAX==UINT64_MAX)
#define Main_Bits_ 64
#define Main_Form_ PRIu64
#else
#error Not supported address size.
#endif

#define Main_DXX_ Conc_(Conc_(D,Main_Bits_),_)
MemC_Type_Rename_(Conc_(Conc_(data,_),Main_Bits_),main_nn,MAIN_NN);//natural number redefinition
MemC_Type_Rename_(Conc_(Conc_(pric,_),Main_Bits_),main_pt,MAIN_PT);//prime table redefinition

#endif

MemC_Default_;

//load a prime table from the disk
static main_pt *Main_Table_Load_(TEXT_08 _PL_ _R_ FileName);
//save a prime table into the disk
static logical Main_Table_Save_(TEXT_08 _PL_ _R_ FileName);
//factorize and display a number
static logical Main_Table_Find_(MAIN_PT _PL_ _R_ Table);

extern integer main(general)
{
	TEXT_08 FileName[24]="prime table "Meta_(Main_Bits_)"-bit.dat";//file path of the prime table to be stored
	main_pt *Table=Main_Table_Load_(FileName);//prime table

	if(Table)
		goto ACTIVE;
	else
	{
		text_08 Key=-1;

		PenC_Stream_Format_T08_(O,NULL,"Failed to load. Wanna create one?\r\nMay take several hours. [Y/N]: ");
		PenC_Stream_Format_T08_(I,NULL,"%1c",&Key,1);
		switch(Key)
		{
		case 'Y':
		case 'y':
			if(Main_Table_Save_(FileName))
				Table=Main_Table_Load_(FileName);
			else
				break;
			if(Table)
ACTIVE:			while(Main_Table_Find_(Table));
			else
				break;
		default:;
		}
		PenC_Stream_Format_T08_(O,NULL,"Good bye!\r\n");
	}

	PriC.PT.Delete.Main_DXX_(&Table);

	return 0;
}

static main_pt *Main_Table_Load_(TEXT_08 _PL_ _R_ FileName)
{
	PenC_Stream_Format_T08_(O,NULL,"Try to load the prime table.\r\n");

	return PenC.Object.Load.T08_(FileName,PriC.PT.Load.Main_DXX_,NULL,false);
}
static logical Main_Table_Save_(TEXT_08 _PL_ _R_ FileName)
{
	TimC_SW_Auto_(SW,1);//stopwatch
	MEMCLIP Bits={.V=sizeof(address)<<2};//first small prime numbers
	logical Flag=false;//file save flag

	PenC_Stream_Format_T08_(O,NULL,"Try to record the prime table.\r\n");
	TimC_SW_Tick_Tock_(SW,0)
		Flag=PenC.Object.Save.T08_(FileName,MemC_Func_Casting_(logical,PriC.PT.Save.Main_DXX_,FILE _PL_ _R_,GENERAL _PL_ _R_),Bits.P,false);

	if(Flag)
	{
		TIMC_TT Time=TimC.SW.Read.Sum.Tag_(SW,0);//time tag

		if(Time.Overflow)
			PenC_Stream_Format_T08_(O,NULL,"Failed to measure the time consumed.\r\n");
		else
			PenC_Stream_Format_T08_(O,NULL,"Consumed %01d %02d:%02d:%02d.%03d\r\n",Time.Days,Time.Hours,Time.Minutes,Time.Seconds,Time.Milliseconds);
	}
	else
		PenC_Stream_Format_T08_(O,NULL,"Sorry but failed to create it. Maybe a memory issue.\r\n");

	return Flag;
}
static logical Main_Table_Find_(MAIN_PT _PL_ _R_ Table)
{
	main_nn Number;//number to be factorized

	PenC_Stream_Format_T08_(O,NULL,"Give me a natural number : ");
	if(PenC_Stream_Format_T08_(I,NULL,"%"Main_Form_,&Number)>0)
	{
		main_nn Factor[sizeof(address)<<3];//factorized sequence

		if(PriC.PT.Factor.Main_DXX_(Factor,Table,Number))
		{
			PenC_Stream_Format_T08_(O,NULL,"Factorization :\r\n");
			for(main_nn Index=1;Index<=(*Factor);Index++)
				PenC_Stream_Format_T08_(O,NULL,"%"Main_Form_" ",Factor[Index]);
			PenC_Stream_Format_T08_(O,NULL,"\r\n");

			return true;
		}
		else;
	}
	else;

	return false;
}
