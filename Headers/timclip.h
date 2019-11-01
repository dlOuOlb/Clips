/*------------------------------------------------------------------*/
/*	TimClip is a simple time record library.						*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2019.11.01	*/
/*------------------------------------------------------------------*/

#ifndef _INC_TIMCLIP
#define _INC_TIMCLIP

#if(1)
#include <bitclip.h>

#include <time.h>
#endif

#if(Fold_(Definition:Types))
//TimClip : Time Tag Structure
struct _timc_tt
{
	data_32 Sign:1,Overflow:1,Days:3,Hours:5,Minutes:6,Seconds:6,Milliseconds:10;
};
MemC_Type_Declare_(struct,timc_tt,TIMC_TT);	//TimClip : Time Tag Structure

//TimClip : Timer State Flag Enumeration
enum _timc_sf
{
	TimCStateUnknown=-1,	//TimClip : Unknown State
	TimCStateStopped=0,		//TimClip : Idle State
	TimCStateRunning=+1		//TimClip : Running State
};
MemC_Type_Declare_(enum,timc_sf,TIMC_SF);	//TimClip : Timer State Flag Enumeration

//TimClip : Timer Element Structure
struct _timc_te
{
	clock_t Sum;	//TimClip : Clock Sum
	clock_t Mark;	//TimClip : Start Marker
	timc_sf State;	//TimClip : Timer State
	integer Count;	//TimClip : Run Count
};
MemC_Type_Declare_(struct,timc_te,TIMC_TE);	//TimClip : Timer Element Structure

//TimClip : Stopwatch Structure
struct _timc_sw
{
	timc_te _PL_ Timer;	//TimClip : Internal Timer Set
	ADDRESS Nums;		//TimClip : Number of Timers
};
MemC_Type_Declare_(struct,timc_sw,TIMC_SW);	//TimClip : Stopwatch Structure

//TimClip : Random Generator Structure
struct _timc_rg
{
	data_64 _PL_ State;	//TimClip : Internal State Set
	ADDRESS Nums;		//TimClip : Number of States
};
MemC_Type_Declare_(struct,timc_rg,TIMC_RG);	//TimClip : Random Generator Structure
#endif

#if(Fold_(Library Casing))
//TimClip : Library Case Structure
struct _timcase
{
	//TimClip : Library Version
	BYTE_08 _PL_ Version;

	//TimClip : Timer Clock's Resolution and Frequency
	const struct
	{
		REAL_32 Frequency;	//TimClip : clocks per second
		REAL_32 Resolution;	//TimClip : seconds per clock
	}
	Clock;

	//TimClip : Stopwatch Functions
	const struct
	{
		//TimClip : Automatic Stopwatch
#define TimC_SW_Auto_(Auto,TimersNumber) MemC_Unit_(timc_sw,Auto,.Timer=(timc_te[TimersNumber]){0},.Nums=(TimersNumber))

		//TimClip : Stopwatch Memory Allocation - Deallocate with "TimC.SW.Delete_"
		timc_sw*(_PL_ Create_)(ADDRESS TimersNumber);
		//TimClip : Stopwatch Memory Deallocation
		general(_PL_ Delete_)(timc_sw *_PL_ _R_ Stopwatch);
		//TimClip : Stopwatch Memory Occupation
		address(_PL_ Size_)(TIMC_SW _PL_ _R_ Stopwatch);

		//TimClip : All Timer Control Functions
		const struct
		{
			//TimClip : Initialize all timers in the stopwatch.
			//＊Return value is "TimCStateStopped" for success, "TimCStateUnknown" for failure.
			timc_sf(_PL_ Reset_)(TIMC_SW _PL_ _R_ Stopwatch);
			//TimClip : Stop all timers in the stopwatch.
			//＊Return value is "TimCStateStopped" for success, "TimCStateUnknown" for failure.
			timc_sf(_PL_ Stop_)(TIMC_SW _PL_ _R_ Stopwatch);
		}
		All;

		//TimClip : Initialize the selected timer.
		//＊Return value is "TimCStateStopped" for success, "TimCStateUnknown" for failure.
		timc_sf(_PL_ Reset_)(TIMC_SW _PL_ _R_ Stopwatch,ADDRESS TimerSelect);
		//TimClip : Toggle the selected timer.
		//＊Return value is the timer's state after toggling.
		timc_sf(_PL_ Toggle_)(TIMC_SW _PL_ _R_ Stopwatch,ADDRESS TimerSelect);
#define TimC_SW_Tick_Tock_(Stopwatch,TimerSelect,State) if(TimC.SW.Read.State_(Stopwatch,TimerSelect)){(State)=TimCStateUnknown;}else for((State)=TimC.SW.Toggle_(Stopwatch,TimerSelect);(State)==TimCStateRunning;(State)=TimC.SW.Toggle_(Stopwatch,TimerSelect))

		//TimClip : Timer Read Functions
		const struct
		{
			//TimClip : Read the selected timer's state flag.
			//＊Return value is the timer's current state.
			timc_sf(_PL_ State_)(TIMC_SW _PL_ _R_ Stopwatch,ADDRESS TimerSelect);
			//TimClip : Read the selected timer's running count.
			integer(_PL_ Count_)(TIMC_SW _PL_ _R_ Stopwatch,ADDRESS TimerSelect);

			//TimClip : Total Running Time
			const struct
			{
				//TimClip : Read the selected timer's total running time as 32-bit real.
				real_32(_PL_ R32_)(TIMC_SW _PL_ _R_ Stopwatch,ADDRESS TimerSelect);
				//TimClip : Read the selected timer's total running time as time tag.
				timc_tt(_PL_ Tag_)(TIMC_SW _PL_ _R_ Stopwatch,ADDRESS TimerSelect);
			}
			Sum;

			//TimClip : Average Running Time
			const struct
			{
				//TimClip : Read the selected timer's average running time as 32-bit real.
				real_32(_PL_ R32_)(TIMC_SW _PL_ _R_ Stopwatch,ADDRESS TimerSelect);
				//TimClip : Read the selected timer's average running time as time tag.
				timc_tt(_PL_ Tag_)(TIMC_SW _PL_ _R_ Stopwatch,ADDRESS TimerSelect);
			}
			Mean;
		}
		Read;
	}
	SW;

	//TimClip : Random Generator Functions
	const struct
	{
		//TimClip : Automatic Random Generator
#define TimC_RG_Auto_(Auto,StatesNumber,...) timc_rg _PL_(Auto)=&(timc_rg){.State=(data_64[StatesNumber]){__VA_ARGS__},.Nums=(StatesNumber)}

		//TimClip : Random Generator Memory Allocation - Deallocate with "TimC.RG.Delete_"
		//＊RandomGenerator -> State[idx]＝time(NULL)＋idx;
		timc_rg*(_PL_ Create_)(ADDRESS StatesNumber);
		//TimClip : Random Generator Memory Deallocation
		general(_PL_ Delete_)(timc_rg *_PL_ _R_ RandomGenerator);
		//TimClip : Random Generator Memory Occupation
		address(_PL_ Size_)(TIMC_RG _PL_ _R_ RandomGenerator);

		//TimClip : Random Generator State Reset
		//＊RandomGenerator -> State[idx]＝time(NULL)＋idx;
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Reset_)(TIMC_RG _PL_ _R_ RandomGenerator);

		//TimClip : Random Generation Functions
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//TimClip : Random Generation for Specified Bytes
			//＊MWC64X algorithm is used.
			logical(_PL_ Byte_)(TIMC_RG _PL_ _R_ RandomGenerator,ADDRESS StateSelect,general _PL_ _R_ ArrayData,ADDRESS ArraySize);
			//TimClip : Random Permutation
			//＊Knuth shuffles algorithm is used.
			//＊An array whose length exceeds ((2^64)-1) is not allowed.
			logical(_PL_ Perm_)(TIMC_RG _PL_ _R_ RandomGenerator,ADDRESS StateSelect,address _PL_ _R_ Array,ADDRESS Length);
		}
		Rand;

		//TimClip : Functions for Uniform Distribution U[L, H]
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//TimClip : 32-bit Random Integer Array
			logical(_PL_ I32_)(TIMC_RG _PL_ _R_ RandomGenerator,ADDRESS StateSelect,inte_32 _PL_ _R_ Array,ADDRESS Length,INTE_32 Low,INTE_32 High);

			//TimClip : 32-bit Random Real Array
			logical(_PL_ R32_)(TIMC_RG _PL_ _R_ RandomGenerator,ADDRESS StateSelect,real_32 _PL_ _R_ Array,ADDRESS Length,REAL_32 Low,REAL_32 High);
			//TimClip : 64-bit Random Real Array
			logical(_PL_ R64_)(TIMC_RG _PL_ _R_ RandomGenerator,ADDRESS StateSelect,real_64 _PL_ _R_ Array,ADDRESS Length,REAL_64 Low,REAL_64 High);
		}
		Uni;

		//TimClip : Functions for Gaussian Distribution N(μ, σ²)
		//＊Box-Muller transform is used.
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//TimClip : 32-bit Random Real Array
			logical(_PL_ R32_)(TIMC_RG _PL_ _R_ RandomGenerator,ADDRESS StateSelect,real_32 _PL_ _R_ Array,ADDRESS Length,REAL_32 Mean,REAL_32 Deviation);
			//TimClip : 64-bit Random Real Array
			logical(_PL_ R64_)(TIMC_RG _PL_ _R_ RandomGenerator,ADDRESS StateSelect,real_64 _PL_ _R_ Array,ADDRESS Length,REAL_64 Mean,REAL_64 Deviation);
		}
		Gau;
	}
	RG;
};
MemC_Type_Declare_(struct,timcase,TIMCASE);	//TimClip : Library Case Structure

//TimClip : Library Case Object
extern TIMCASE TimC;
//TimClip : Indirect access to the library case object.
extern TIMCASE *TimC_(general);
#endif
#endif
