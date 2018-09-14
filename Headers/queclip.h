/*------------------------------------------------------------------*/
/*	QueClip is a simple queue structure library.					*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2018.09.14	*/
/*------------------------------------------------------------------*/

#ifndef _INC_QUECLIP
#define _INC_QUECLIP	//QueClip : Header Declaration

#include <memclip.h>

struct _quec_qs			//QueClip : Queue Set Structure
{
	GENERAL _PL_ Queue;	//QueClip : Internal Queue Set
	ADDRESS _PL_ Count;	//QueClip : Length of Queues where Count[-1] means Empty Length
	ADDRESS Number;		//QueClip : Number of Queues
	ADDRESS Capacity;	//QueClip : Maximum Total Queue Length
};
MemC_Type_Declare_(struct,quec_qs,QUEC_QS);	//QueClip : Queue Set Structure

//QueClip : Library Version
extern BYTE_08 _PL_ QueClip;

//QueClip : Queue Set Memory Allocation - Deallocate with "QueC_QS_Delete_"
quec_qs *QueC_QS_Create_(ADDRESS QueuesNumber,ADDRESS MaximumCapacity);
//QueClip : Queue Set Memory Deallocation
general QueC_QS_Delete_(quec_qs *_PL_ QSet);
//QueClip : Queue Set Memory Occupation
address QueC_QS_Size_(QUEC_QS _PL_ QSet);

//QueClip : Reset All Queues
//＊Return value is 1 for success, 0 for failure.
integer QueC_QS_Reset_All_(QUEC_QS _PL_ QSet);
//QueClip : Reset the Selected Queue
//＊Return value is 1 for success, 0 for failure.
integer QueC_QS_Reset_(QUEC_QS _PL_ QSet,ADDRESS QSelect);

//QueClip : Enqueue an Object into the Selected Queue
//＊Return value is 1 for success, 0 for failure.
integer QueC_QS_Enque_(QUEC_QS _PL_ QSet,ADDRESS QSelect,GENERAL *Object);
//QueClip : Dequeue an Object from the Selected Queue
//＊Return value is the stored address.
general *QueC_QS_Deque_(QUEC_QS _PL_ QSet,ADDRESS QSelect);

//QueClip : Check the Selected Queue
//＊Return value is 1 only if the selected queue has no NULL object, otherwise 0.
integer QueC_QS_Check_(QUEC_QS _PL_ QSet,ADDRESS QSelect);
//QueClip : Peek an Object in the Seleted Queue without Change
//＊Return value is the stored address.
general *QueC_QS_Peek_(QUEC_QS _PL_ QSet,ADDRESS QSelect,ADDRESS Depth);
#endif
