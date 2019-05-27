/*------------------------------------------------------------------*/
/*	TimClip is a simple time record library.						*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2019.05.27	*/
/*------------------------------------------------------------------*/

#ifndef _INC_TIMCLIP
#define _INC_TIMCLIP

#if(1)
#include <time.h>
#include <limits.h>
#include <bitclip.h>
#endif

#if(Fold_(Definition:Types))
//TimClip : Timer State Flag Enumeration
enum _timc_sf
{
	TimCStateUnknown=-1,	//TimClip : Unknown State
	TimCStateStopped=0,		//TimClip : Idle State
	TimCStateRunning=+1		//TimClip : Running State
};
MemC_Type_Declare_(enum,timc_sf,TIMC_SF);	//TimClip : Timer State Flag Enumeration

//TimClip : Stopwatch Structure
struct _timc_sw
{
	GENERAL _PL_ Timer;	//TimClip : Internal Timer Set
	ADDRESS Nums;		//TimClip : Number of Timers
};
MemC_Type_Declare_(struct,timc_sw,TIMC_SW);	//TimClip : Stopwatch Structure
#endif

#if(Fold_(Library Casing))
//TimClip : Library Case
extern const struct _timcase
{
	//TimClip : Library Version
	BYTE_08 _PL_ Version;

	//TimClip : Stopwatch Functions
	const struct
	{
		//TimClip : Stopwatch Memory Allocation - Deallocate with "TimC.SW.Delete_"
		timc_sw*(_PL_ Create_)(ADDRESS TimersNumber);
		//TimClip : Stopwatch Memory Deallocation
		general(_PL_ Delete_)(timc_sw *_PL_ Stopwatch);
		//TimClip : Temporarily allocate and deallocate a stopwatch.
#define TimC_SW_Temp_(Temp,Nums,FAIL) for(timc_sw _PL_(Temp)=TimC.SW.Create_(Nums),*(_##Temp)=FULL;_##Temp;TimC.SW.Delete_((timc_sw**)&(Temp)),(_##Temp)=NULL)if(!(Temp)){FAIL}else

		//TimClip : Stopwatch Memory Occupation
		address(_PL_ Size_)(TIMC_SW _PL_ Stopwatch);

		//TimClip : All Timer Control Functions
		const struct
		{
			//TimClip : Initialize All Timers in the Stopwatch
			//£ªReturn value is "TimCStateStopped" for success, "TimCStateUnknown" for failure.
			timc_sf(_PL_ Reset_)(TIMC_SW _PL_ Stopwatch);
			//TimClip : Turn off All Timers in the Stopwatch
			//£ªReturn value is "TimCStateStopped" for success, "TimCStateUnknown" for failure.
			timc_sf(_PL_ Stop_)(TIMC_SW _PL_ Stopwatch);
		}
		All;

		//TimClip : Initialize the Selected Timer
		//£ªReturn value is "TimCStateStopped" for success, "TimCStateUnknown" for failure.
		timc_sf(_PL_ Reset_)(TIMC_SW _PL_ Stopwatch,ADDRESS TimerSelect);
		//TimClip : Toggle the Selected Timer
		//£ªReturn value is the timer's state after toggling.
		timc_sf(_PL_ Toggle_)(TIMC_SW _PL_ Stopwatch,ADDRESS TimerSelect);
#define TimC_SW_Tick_Tock_(Stopwatch,TimerSelect,State) if(TimC.SW.Read.State_(Stopwatch,TimerSelect)){(State)=TimCStateUnknown;}else for((State)=TimC.SW.Toggle_(Stopwatch,TimerSelect);(State)==TimCStateRunning;(State)=TimC.SW.Toggle_(Stopwatch,TimerSelect))

		//TimClip : Timer Read Functions
		const struct
		{
			//TimClip : Read the Selected Timer's State Flag
			//£ªReturn value is the timer's current state.
			timc_sf(_PL_ State_)(TIMC_SW _PL_ Stopwatch,ADDRESS TimerSelect);
			//TimClip : Read the Selected Timer's Running Count
			integer(_PL_ Count_)(TIMC_SW _PL_ Stopwatch,ADDRESS TimerSelect);

			//TimClip : Read the Selected Timer's Total Running Time
			real_32(_PL_ Sum_)(TIMC_SW _PL_ Stopwatch,ADDRESS TimerSelect);
			//TimClip : Read the Selected Timer's Average Running Time
			real_32(_PL_ Mean_)(TIMC_SW _PL_ Stopwatch,ADDRESS TimerSelect);
		}
		Read;
	}
	SW;

	//TimClip : Timer Clock's Resolution and Frequency
	const struct
	{
		REAL_32 Resolution;	//TimClip : clocks per second
		REAL_32 Frequency;	//TimClip : seconds per clock
	}
	Clock;
}
TimC;
#endif
#endif
