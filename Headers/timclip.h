/*------------------------------------------------------------------*/
/*	TimClip is a simple time record library.						*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2019.06.21	*/
/*------------------------------------------------------------------*/

#ifndef _INC_TIMCLIP
#define _INC_TIMCLIP

#if(1)
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
		REAL_32 Resolution;	//TimClip : clocks per second
		REAL_32 Frequency;	//TimClip : seconds per clock
	}
	Clock;

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
			//＊Return value is "TimCStateStopped" for success, "TimCStateUnknown" for failure.
			timc_sf(_PL_ Reset_)(TIMC_SW _PL_ Stopwatch);
			//TimClip : Turn off All Timers in the Stopwatch
			//＊Return value is "TimCStateStopped" for success, "TimCStateUnknown" for failure.
			timc_sf(_PL_ Stop_)(TIMC_SW _PL_ Stopwatch);
		}
		All;

		//TimClip : Initialize the Selected Timer
		//＊Return value is "TimCStateStopped" for success, "TimCStateUnknown" for failure.
		timc_sf(_PL_ Reset_)(TIMC_SW _PL_ Stopwatch,ADDRESS TimerSelect);
		//TimClip : Toggle the Selected Timer
		//＊Return value is the timer's state after toggling.
		timc_sf(_PL_ Toggle_)(TIMC_SW _PL_ Stopwatch,ADDRESS TimerSelect);
#define TimC_SW_Tick_Tock_(Stopwatch,TimerSelect,State) if(TimC.SW.Read.State_(Stopwatch,TimerSelect)){(State)=TimCStateUnknown;}else for((State)=TimC.SW.Toggle_(Stopwatch,TimerSelect);(State)==TimCStateRunning;(State)=TimC.SW.Toggle_(Stopwatch,TimerSelect))

		//TimClip : Timer Read Functions
		const struct
		{
			//TimClip : Read the Selected Timer's State Flag
			//＊Return value is the timer's current state.
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

	//TimClip : Random Generator Functions
	const struct
	{
		//TimClip : Random Generator Memory Allocation - Deallocate with "TimC.RG.Delete_"
		timc_rg*(_PL_ Create_)(ADDRESS StatesNumber);
		//TimClip : Random Generator Memory Deallocation
		general(_PL_ Delete_)(timc_rg *_PL_ RandomGenerator);

		//TimClip : Random Generator Memory Occupation
		address(_PL_ Size_)(TIMC_RG _PL_ RandomGenerator);

		//TimClip : Random Generator State Reset
		//＊RandomGenerator -> State[idx]＝time(NULL)＋idx;
		//＊Return value is ~0 for success, 0 for failure.
		boolean(_PL_ Reset_)(TIMC_RG _PL_ RandomGenerator);

		//TimClip : Random Generation Functions
		const struct
		{
			//TimClip : Random Generation for Specified Bytes
			//＊MWC64X algorithm is used.
			//＊Return value is ~0 for success, 0 for failure.
			boolean(_PL_ Byte_)(TIMC_RG _PL_ RandomGenerator,ADDRESS StateSelect,general _PL_ _R_ ArrayData,ADDRESS ArraySize);
			//TimClip : Random Permutation
			//＊Knuth shuffles algorithm is used.
			//＊An array whose length exceeds ((2^64)-1) is not allowed.
			//＊Return value is ~0 for success, 0 for failure.
			boolean(_PL_ Perm_)(TIMC_RG _PL_ RandomGenerator,ADDRESS StateSelect,address _PL_ _R_ Array,ADDRESS Length);
		}
		Rand;

		//TimClip : Random Uniform Functions
		const struct
		{
			//TimClip : 32-bit Integer Array of Uniform Distribution U[L, H]
			//＊Return value is ~0 for success, 0 for failure.
			boolean(_PL_ I32_)(TIMC_RG _PL_ RandomGenerator,ADDRESS StateSelect,inte_32 _PL_ _R_ Array,ADDRESS Length,INTE_32 Low,INTE_32 High);

			//TimClip : 32-bit Real Array of Uniform Distribution U[L, H)
			//＊Return value is ~0 for success, 0 for failure.
			boolean(_PL_ R32_)(TIMC_RG _PL_ RandomGenerator,ADDRESS StateSelect,real_32 _PL_ _R_ Array,ADDRESS Length,REAL_32 Low,REAL_32 High);
			//TimClip : 64-bit Real Array of Uniform Distribution U[L, H)
			//＊Return value is ~0 for success, 0 for failure.
			boolean(_PL_ R64_)(TIMC_RG _PL_ RandomGenerator,ADDRESS StateSelect,real_64 _PL_ _R_ Array,ADDRESS Length,REAL_64 Low,REAL_64 High);
		}
		Uni;

		//TimClip : Random Gaussian Functions
		const struct
		{
			//TimClip : 32-bit Real Array of Gaussian Distribution N(μ, σ²)
			//＊Box-Muller transform is used.
			//＊Return value is ~0 for success, 0 for failure.
			boolean(_PL_ R32_)(TIMC_RG _PL_ RandomGenerator,ADDRESS StateSelect,real_32 _PL_ _R_ Array,ADDRESS Length,REAL_32 Mean,REAL_32 Deviation);
			//TimClip : 64-bit Real Array of Gaussian Distribution N(μ, σ²)
			//＊Box-Muller transform is used.
			//＊Return value is ~0 for success, 0 for failure.
			boolean(_PL_ R64_)(TIMC_RG _PL_ RandomGenerator,ADDRESS StateSelect,real_64 _PL_ _R_ Array,ADDRESS Length,REAL_64 Mean,REAL_64 Deviation);
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
