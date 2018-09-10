/*------------------------------------------------------------------*/
/*	TimClip is a simple time record library.						*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2018.09.06	*/
/*------------------------------------------------------------------*/

#ifndef _INC_TIMCLIP
#define _INC_TIMCLIP	//TimClip : Header Declaration

#include <time.h>
#include <limits.h>
#include <bitclip.h>

#if(MemC_Fold_(Definition:Types))
enum _timc_sf				//TimClip : Timer State Flag Enumeration
{
	TimCStateUnknown=-1,	//TimClip : Unknown State
	TimCStateStopped=0,		//TimClip : Idle State
	TimCStateRunning=+1		//TimClip : Running State
};
MemC_Type_Declare_(enum,timc_sf,TIMC_SF);	//TimClip : Timer State Flag Enumeration
MemC_Type_Declare_(struct,timc_te,TIMC_TE);	//TimClip : Opaque Timer Structure

struct _timc_sw			//TimClip : Stopwatch Structure
{
	ADDRESS Nums;		//TimClip : Number of Timers
	timc_te _PL_ Timer;	//TimClip : Internal Timer Set
};
MemC_Type_Declare_(struct,timc_sw,TIMC_SW);	//TimClip : Stopwatch Structure
#endif

#if(MemC_Fold_(Declaration:Global Constants))
//TimClip : Library Version
extern BYTE_08 _PL_ TimClip;
//TimClip : Timer Clock's Resolution and Frequency
//＊[0] : clocks per second
//　[1] : seconds per clock
extern REAL_32 _PL_ TimClocks;
#endif

#if(MemC_Fold_(Declaration:TimC_SW Functions))
//TimClip : Stopwatch Memory Allocation - Deallocate with "TimC_SW_Delete_"
timc_sw *TimC_SW_Create_(ADDRESS TimersNumber);
//TimClip : Stopwatch Memory Deallocation
general TimC_SW_Delete_(timc_sw *_PL_ Stopwatch);

//TimClip : Stopwatch Memory Occupation
address TimC_SW_Size_(TIMC_SW _PL_ Stopwatch);

//TimClip : Initialize All Timers in the Stopwatch
//＊Return value is "TimCStateStopped" for success, "TimCStateUnknown" for failure.
timc_sf TimC_SW_Reset_All_(TIMC_SW _PL_ Stopwatch);
//TimClip : Turn off All Timers in the Stopwatch
//＊Return value is "TimCStateStopped" for success, "TimCStateUnknown" for failure.
timc_sf TimC_SW_Stop_All_(TIMC_SW _PL_ Stopwatch);

//TimClip : Initialize the Selected Timer
//＊Return value is "TimCStateStopped" for success, "TimCStateUnknown" for failure.
timc_sf TimC_SW_Reset_(TIMC_SW _PL_ Stopwatch,ADDRESS TimerSelect);
//TimClip : Toggle the Selected Timer
//＊Return value is the timer's state after toggling.
timc_sf TimC_SW_Toggle_(TIMC_SW _PL_ Stopwatch,ADDRESS TimerSelect);
#define TimC_SW_Tick_Tock_(Stopwatch,TimerSelect,State) for((State)=TimC_SW_Toggle_(Stopwatch,TimerSelect);(State)==TimCStateRunning;(State)=TimC_SW_Toggle_(Stopwatch,TimerSelect))

//TimClip : Read the Selected Timer's State Flag
//＊Return value is the timer's current state.
timc_sf TimC_SW_Read_State_(TIMC_SW _PL_ Stopwatch,ADDRESS TimerSelect);
//TimClip : Read the Selected Timer's Running Count
integer TimC_SW_Read_Count_(TIMC_SW _PL_ Stopwatch,ADDRESS TimerSelect);

//TimClip : Read the Selected Timer's Total Running Time
real_32 TimC_SW_Read_Sum_(TIMC_SW _PL_ Stopwatch,ADDRESS TimerSelect);
//TimClip : Read the Selected Timer's Average Running Time
real_32 TimC_SW_Read_Mean_(TIMC_SW _PL_ Stopwatch,ADDRESS TimerSelect);
#endif
#endif
