/*------------------------------------------------------------------*/
/*	BoxClip is a simple data structure library.						*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2018.09.27	*/
/*------------------------------------------------------------------*/

#ifndef _INC_BOXCLIP
#define _INC_BOXCLIP

#include <memclip.h>

#if(MemC_Fold_(Definition:Types))
struct _boxc_ss			//BoxClip : Stack Set Structure
{
	GENERAL _PL_ Stack;	//BoxClip : Internal Stack Set
	ADDRESS _PL_ Count;	//BoxClip : Length of Stacks where Count[-1] means Left Capacity
	ADDRESS Number;		//BoxClip : Number of Stacks
	ADDRESS Capacity;	//BoxClip : Maximum Total Stack Length
};
MemC_Type_Declare_(struct,boxc_ss,BOXC_SS);	//BoxClip : Stack Set Structure

struct _boxc_qs			//BoxClip : Queue Set Structure
{
	GENERAL _PL_ Queue;	//BoxClip : Internal Queue Set
	ADDRESS _PL_ Count;	//BoxClip : Length of Queues where Count[-1] means Left Capacity
	ADDRESS Number;		//BoxClip : Number of Queues
	ADDRESS Capacity;	//BoxClip : Maximum Total Queue Length
};
MemC_Type_Declare_(struct,boxc_qs,BOXC_QS);	//BoxClip : Queue Set Structure

struct _boxc_rs			//BoxClip : Ring Set Structure
{
	GENERAL _PL_ Ring;	//BoxClip : Internal Ring Set
	ADDRESS _PL_ Count;	//BoxClip : Length of Rings where Count[-1] means Left Capacity
	ADDRESS Number;		//BoxClip : Number of Rings
	ADDRESS Capacity;	//BoxClip : Maximum Total Ring Length
};
MemC_Type_Declare_(struct,boxc_rs,BOXC_RS);	//BoxClip : Ring Set Structure
#endif

#if(MemC_Fold_(Declaration:Global Constants))
//BoxClip : Library Version
extern BYTE_08 _PL_ BoxClip;
#endif

#if(MemC_Fold_(Declaration:BoxClip Structure Functions))
#if(MemC_Fold_(Part:BoxC_SS))
//BoxClip : Stack Set Memory Allocation - Deallocate with "BoxC_SS_Delete_"
boxc_ss *BoxC_SS_Create_(ADDRESS StacksNumber,ADDRESS MaximumCapacity);
//BoxClip : Stack Set Memory Deallocation
general BoxC_SS_Delete_(boxc_ss *_PL_ StackSet);
//BoxClip : Stack Set Memory Occupation
address BoxC_SS_Size_(BOXC_SS _PL_ StackSet);

//BoxClip : Reset All Stacks
//＊Return value is 1 for success, 0 for failure.
integer BoxC_SS_Reset_All_(BOXC_SS _PL_ StackSet);
//BoxClip : Reset the Selected Stack
//＊Return value is 1 for success, 0 for failure.
integer BoxC_SS_Reset_(BOXC_SS _PL_ StackSet,ADDRESS StackSelect);

//BoxClip : Push an Object into the Selected Stack
//＊Return value is 1 for success, 0 for failure.
integer BoxC_SS_Push_(BOXC_SS _PL_ StackSet,ADDRESS StackSelect,general *Object);
//BoxClip : Pop an Object from the Selected Stack
//＊Return value is the stored address.
general *BoxC_SS_Pop_(BOXC_SS _PL_ StackSet,ADDRESS StackSelect);

//BoxClip : Check the Selected Stack
//＊Return value is 1 only if the selected stack has no NULL object, otherwise 0.
integer BoxC_SS_Check_(BOXC_SS _PL_ StackSet,ADDRESS StackSelect);
//BoxClip : Peek an Object in the Seleted Stack without Change
//＊Return value is the stored address.
general *BoxC_SS_Peek_(BOXC_SS _PL_ StackSet,ADDRESS StackSelect,ADDRESS Depth);
#endif
#if(MemC_Fold_(Part:BoxC_QS))
//BoxClip : Queue Set Memory Allocation - Deallocate with "BoxC_QS_Delete_"
boxc_qs *BoxC_QS_Create_(ADDRESS QueuesNumber,ADDRESS MaximumCapacity);
//BoxClip : Queue Set Memory Deallocation
general BoxC_QS_Delete_(boxc_qs *_PL_ QueueSet);
//BoxClip : Queue Set Memory Occupation
address BoxC_QS_Size_(BOXC_QS _PL_ QueueSet);

//BoxClip : Reset All Queues
//＊Return value is 1 for success, 0 for failure.
integer BoxC_QS_Reset_All_(BOXC_QS _PL_ QueueSet);
//BoxClip : Reset the Selected Queue
//＊Return value is 1 for success, 0 for failure.
integer BoxC_QS_Reset_(BOXC_QS _PL_ QueueSet,ADDRESS QueueSelect);

//BoxClip : Enqueue an Object into the Selected Queue
//＊Return value is 1 for success, 0 for failure.
integer BoxC_QS_Enque_(BOXC_QS _PL_ QueueSet,ADDRESS QueueSelect,general *Object);
//BoxClip : Dequeue an Object from the Selected Queue
//＊Return value is the stored address.
general *BoxC_QS_Deque_(BOXC_QS _PL_ QueueSet,ADDRESS QueueSelect);

//BoxClip : Check the Selected Queue
//＊Return value is 1 only if the selected queue has no NULL object, otherwise 0.
integer BoxC_QS_Check_(BOXC_QS _PL_ QueueSet,ADDRESS QueueSelect);
//BoxClip : Peek an Object in the Seleted Queue without Change
//＊Return value is the stored address.
general *BoxC_QS_Peek_(BOXC_QS _PL_ QueueSet,ADDRESS QueueSelect,ADDRESS Depth);
#endif
#if(MemC_Fold_(Part:BoxC_RS))
//BoxClip : Ring Set Memory Allocation - Deallocate with "BoxC_RS_Delete_"
boxc_rs *BoxC_RS_Create_(ADDRESS RingsNumber,ADDRESS MaximumCapacity);
//BoxClip : Ring Set Memory Deallocation
general BoxC_RS_Delete_(boxc_rs *_PL_ RingSet);
//BoxClip : Ring Set Memory Occupation
address BoxC_RS_Size_(BOXC_RS _PL_ RingSet);

//BoxClip : Reset All Rings
//＊Return value is 1 for success, 0 for failure.
integer BoxC_RS_Reset_All_(BOXC_RS _PL_ RingSet);
//BoxClip : Reset the Selected Ring
//＊Return value is 1 for success, 0 for failure.
integer BoxC_RS_Reset_(BOXC_RS _PL_ RingSet,ADDRESS RingSelect);

//BoxClip : Insert an Object into the Selected Ring
//＊Return value is 1 for success, 0 for failure.
integer BoxC_RS_Insert_(BOXC_RS _PL_ RingSet,ADDRESS RingSelect,general *Object);
//BoxClip : Desert an Object from the Selected Ring
//＊Return value is the stored address.
general *BoxC_RS_Desert_(BOXC_RS _PL_ RingSet,ADDRESS RingSelect);
//BoxClip : Rotate the Selected Ring
//＊Return value is 1 for success, 0 for failure.
integer BoxC_RS_Rotate_(BOXC_RS _PL_ RingSet,ADDRESS RingSelect,INTEGER Rotation);

//BoxClip : Check the Selected Ring
//＊Return value is 1 only if the selected ring has no NULL object, otherwise 0.
integer BoxC_RS_Check_(BOXC_RS _PL_ RingSet,ADDRESS RingSelect);
//BoxClip : Read an Object in the Selected Ring without Change
//＊Return value is the stored address.
general *BoxC_RS_Read_(BOXC_RS _PL_ RingSet,ADDRESS RingSelect);
#endif
#endif
#endif
