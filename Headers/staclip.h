/*------------------------------------------------------------------*/
/*	StaClip is a simple stack structure library.					*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2018.09.20	*/
/*------------------------------------------------------------------*/

#ifndef _INC_STACLIP
#define _INC_STACLIP	//StaClip : Header Declaration

#include <memclip.h>

struct _stac_ss			//StaClip : Stack Set Structure
{
	GENERAL _PL_ Stack;	//StaClip : Internal Stack Set
	ADDRESS _PL_ Count;	//StaClip : Length of Stacks where Count[-1] means Empty Length
	ADDRESS Number;		//StaClip : Number of Stacks
	ADDRESS Capacity;	//StaClip : Maximum Total Stack Length
};
MemC_Type_Declare_(struct,stac_ss,STAC_SS);	//StaClip : Stack Set Structure

//StaClip : Library Version
extern BYTE_08 _PL_ StaClip;

//StaClip : Stack Set Memory Allocation - Deallocate with "StaC_SS_Delete_"
stac_ss *StaC_SS_Create_(ADDRESS StacksNumber,ADDRESS MaximumCapacity);
//StaClip : Stack Set Memory Deallocation
general StaC_SS_Delete_(stac_ss *_PL_ SSet);
//StaClip : Stack Set Memory Occupation
address StaC_SS_Size_(STAC_SS _PL_ SSet);

//StaClip : Reset All Stacks
//＊Return value is 1 for success, 0 for failure.
integer StaC_SS_Reset_All_(STAC_SS _PL_ SSet);
//StaClip : Reset the Selected Stack
//＊Return value is 1 for success, 0 for failure.
integer StaC_SS_Reset_(STAC_SS _PL_ SSet,ADDRESS SSelect);

//StaClip : Push an Object into the Selected Stack
//＊Return value is 1 for success, 0 for failure.
integer StaC_SS_Push_(STAC_SS _PL_ SSet,ADDRESS SSelect,GENERAL *Object);
//StaClip : Pop an Object from the Selected Stack
//＊Return value is the stored address.
general *StaC_SS_Pop_(STAC_SS _PL_ SSet,ADDRESS SSelect);

//StaClip : Check the Selected Stack
//＊Return value is 1 only if the selected stack has no NULL object, otherwise 0.
integer StaC_SS_Check_(STAC_SS _PL_ SSet,ADDRESS SSelect);
//StaClip : Peek an Object in the Seleted Stack without Change
//＊Return value is the stored address.
general *StaC_SS_Peek_(STAC_SS _PL_ SSet,ADDRESS SSelect,ADDRESS Depth);
#endif
