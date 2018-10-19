/*------------------------------------------------------------------*/
/*	BoxClip is a simple data structure library.						*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2018.10.19	*/
/*------------------------------------------------------------------*/

#ifndef _INC_BOXCLIP
#define _INC_BOXCLIP

#include <bitclip.h>

#if(MemC_Fold_(Declaration:Global Constants))
//BoxClip : Library Version
extern BYTE_08 _PL_ BoxClip;
#endif

#if(MemC_Fold_(Declaration:BoxClip Structure Functions))
#if(MemC_Fold_(Part:BoxC_SS))
struct _boxc_ss			//BoxClip : Stack Set Structure
{
	GENERAL _PL_ Stack;	//BoxClip : Internal Stack Set
	ADDRESS _PL_ Count;	//BoxClip : Length of Stacks where Count[-1] means Left Capacity
	ADDRESS Number;		//BoxClip : Number of Stacks
	ADDRESS Capacity;	//BoxClip : Maximum Total Stack Length
};
MemC_Type_Declare_(struct,boxc_ss,BOXC_SS);	//BoxClip : Stack Set Structure

//BoxClip : Stack Set Memory Allocation - Deallocate with "BoxC_SS_Delete_"
boxc_ss *BoxC_SS_Create_(ADDRESS StacksNumber,ADDRESS MaximumCapacity);
//BoxClip : Stack Set Memory Deallocation
general BoxC_SS_Delete_(boxc_ss *_PL_ StackSet);
//BoxClip : Stack Set Memory Occupation
address BoxC_SS_Size_(BOXC_SS _PL_ StackSet);

//BoxClip : Reset All Stacks
//＊Return value is ~0 for success, 0 for failure.
boolean BoxC_SS_Reset_All_(BOXC_SS _PL_ StackSet);
//BoxClip : Reset the Selected Stack
//＊Return value is ~0 for success, 0 for failure.
boolean BoxC_SS_Reset_(BOXC_SS _PL_ StackSet,ADDRESS StackSelect);

//BoxClip : Push an Object into the Selected Stack
//＊Return value is ~0 for success, 0 for failure.
boolean BoxC_SS_Push_(BOXC_SS _PL_ StackSet,ADDRESS StackSelect,general *Object);
//BoxClip : Pop an Object from the Selected Stack
//＊Return value is the stored address.
general *BoxC_SS_Pop_(BOXC_SS _PL_ StackSet,ADDRESS StackSelect);

//BoxClip : Check the Selected Stack
//＊Return value is ~0 only if the selected stack has no NULL object, otherwise 0.
boolean BoxC_SS_Check_(BOXC_SS _PL_ StackSet,ADDRESS StackSelect);
//BoxClip : Peek an Object in the Seleted Stack without Change
//＊Return value is the stored address.
general *BoxC_SS_Peek_(BOXC_SS _PL_ StackSet,ADDRESS StackSelect,ADDRESS Depth);
#endif

#if(MemC_Fold_(Part:BoxC_QS))
struct _boxc_qs			//BoxClip : Queue Set Structure
{
	GENERAL _PL_ Queue;	//BoxClip : Internal Queue Set
	ADDRESS _PL_ Count;	//BoxClip : Length of Queues where Count[-1] means Left Capacity
	ADDRESS Number;		//BoxClip : Number of Queues
	ADDRESS Capacity;	//BoxClip : Maximum Total Queue Length
};
MemC_Type_Declare_(struct,boxc_qs,BOXC_QS);	//BoxClip : Queue Set Structure

//BoxClip : Queue Set Memory Allocation - Deallocate with "BoxC_QS_Delete_"
boxc_qs *BoxC_QS_Create_(ADDRESS QueuesNumber,ADDRESS MaximumCapacity);
//BoxClip : Queue Set Memory Deallocation
general BoxC_QS_Delete_(boxc_qs *_PL_ QueueSet);
//BoxClip : Queue Set Memory Occupation
address BoxC_QS_Size_(BOXC_QS _PL_ QueueSet);

//BoxClip : Reset All Queues
//＊Return value is ~0 for success, 0 for failure.
boolean BoxC_QS_Reset_All_(BOXC_QS _PL_ QueueSet);
//BoxClip : Reset the Selected Queue
//＊Return value is ~0 for success, 0 for failure.
boolean BoxC_QS_Reset_(BOXC_QS _PL_ QueueSet,ADDRESS QueueSelect);

//BoxClip : Enqueue an Object into the Selected Queue
//＊Return value is ~0 for success, 0 for failure.
boolean BoxC_QS_Enque_(BOXC_QS _PL_ QueueSet,ADDRESS QueueSelect,general *Object);
//BoxClip : Dequeue an Object from the Selected Queue
//＊Return value is the stored address.
general *BoxC_QS_Deque_(BOXC_QS _PL_ QueueSet,ADDRESS QueueSelect);

//BoxClip : Check the Selected Queue
//＊Return value is ~0 only if the selected queue has no NULL object, otherwise 0.
boolean BoxC_QS_Check_(BOXC_QS _PL_ QueueSet,ADDRESS QueueSelect);
//BoxClip : Peek an Object in the Seleted Queue without Change
//＊Return value is the stored address.
general *BoxC_QS_Peek_(BOXC_QS _PL_ QueueSet,ADDRESS QueueSelect,ADDRESS Depth);
#endif

#if(MemC_Fold_(Part:BoxC_RS))
struct _boxc_rs			//BoxClip : Ring Set Structure
{
	GENERAL _PL_ Ring;	//BoxClip : Internal Ring Set
	ADDRESS _PL_ Count;	//BoxClip : Length of Rings where Count[-1] means Left Capacity
	ADDRESS Number;		//BoxClip : Number of Rings
	ADDRESS Capacity;	//BoxClip : Maximum Total Ring Length
};
MemC_Type_Declare_(struct,boxc_rs,BOXC_RS);	//BoxClip : Ring Set Structure

//BoxClip : Ring Set Memory Allocation - Deallocate with "BoxC_RS_Delete_"
boxc_rs *BoxC_RS_Create_(ADDRESS RingsNumber,ADDRESS MaximumCapacity);
//BoxClip : Ring Set Memory Deallocation
general BoxC_RS_Delete_(boxc_rs *_PL_ RingSet);
//BoxClip : Ring Set Memory Occupation
address BoxC_RS_Size_(BOXC_RS _PL_ RingSet);

//BoxClip : Reset All Rings
//＊Return value is ~0 for success, 0 for failure.
boolean BoxC_RS_Reset_All_(BOXC_RS _PL_ RingSet);
//BoxClip : Reset the Selected Ring
//＊Return value is ~0 for success, 0 for failure.
boolean BoxC_RS_Reset_(BOXC_RS _PL_ RingSet,ADDRESS RingSelect);

//BoxClip : Insert an Object into the Selected Ring
//＊Enqueue left for direction 0, right for direction ~0.
//＊Return value is ~0 for success, 0 for failure.
boolean BoxC_RS_Insert_(BOXC_RS _PL_ RingSet,ADDRESS RingSelect,general *Object,BOOLEAN Direction);
//BoxClip : Desert an Object from the Selected Ring
//＊Dequeue left for direction 0, right for direction ~0.
//＊Return value is ~0 for success, 0 for failure.
boolean BoxC_RS_Desert_(BOXC_RS _PL_ RingSet,ADDRESS RingSelect,BOOLEAN Direction);
//BoxClip : Rotate the Selected Ring
//＊Move the pin left for negative rotation, right for positive rotation.
//＊Return value is ~0 for success, 0 for failure.
boolean BoxC_RS_Rotate_(BOXC_RS _PL_ RingSet,ADDRESS RingSelect,INTEGER Rotation);

//BoxClip : Check the Selected Ring
//＊Return value is ~0 only if the selected ring has no NULL object, otherwise 0.
boolean BoxC_RS_Check_(BOXC_RS _PL_ RingSet,ADDRESS RingSelect);
//BoxClip : Read an Object in the Selected Ring without Change
//＊Read left for direction 0, right for direction ~0.
//＊Return value is the stored address.
general *BoxC_RS_Read_(BOXC_RS _PL_ RingSet,ADDRESS RingSelect,BOOLEAN Direction);
#endif

#if(MemC_Fold_(Part:BoxC_FS))
struct _boxc_fs			//BoxClip : Flag Set Structure
{
	GENERAL _PL_ Flag;	//BoxClip : Internal Flag Set
	ADDRESS Number;		//BoxClip : Number of Flags
};
MemC_Type_Declare_(struct,boxc_fs,BOXC_FS);	//BoxClip : Flag Set Structure

//BoxClip : Flag Set Memory Allocation - Deallocate with "BoxC_FS_Delete_"
boxc_fs *BoxC_FS_Create_(ADDRESS FlagsNumber);
//BoxClip : Flag Set Memory Deallocation
general BoxC_FS_Delete_(boxc_fs *_PL_ FlagSet);
//BoxClip : Flag Set Memory Occupation
address BoxC_FS_Size_(BOXC_FS _PL_ FlagSet);

//BoxClip : Write a Boolean into the Selected Flag
//＊Boolean value should be 0 or ~0.
general BoxC_FS_Writer_(BOXC_FS _PL_ FlagSet,ADDRESS FlagSelect,BOOLEAN Boolean);
//BoxClip : Read a Boolean from the Selected Flag
//＊Return Value is the stored boolean.
boolean BoxC_FS_Reader_(BOXC_FS _PL_ FlagSet,ADDRESS FlagSelect);
//BoxClip : Toggle a Boolean of the Selected Flag
general BoxC_FS_Toggle_(BOXC_FS _PL_ FlagSet,ADDRESS FlagSelect);
#endif

#if(MemC_Fold_(Part:BoxC_Tr))
MemC_Type_Declare_(struct,boxc_tr,BOXC_TR);	//BoxClip : Tree Structure
struct _boxc_tr			//BoxClip : Tree Structure
{
	boxc_tr _PL_ Root;	//BoxClip : Root Node
	boxc_tr _PL_ Leaf;	//BoxClip : Leaf Node
	boxc_tr _PL_ Prev;	//BoxClip : Previous Node
	boxc_tr _PL_ Next;	//BoxClip : Next Node
	ADDRESS Count;		//BoxClip : Number of Current Leaves
	ADDRESS Total;		//BoxClip : Number of All Leaves
	general _PL_ Link;	//BoxClip : Internal Linking
	general *Object;	//BoxClip : User Object
};

//BoxClip : Tree Creation - Delete with "BoxC_Tr_Create_"
//＊If the root is null, then a new memory space will be allocated, else the capacity should be 0.
boxc_tr *BoxC_Tr_Create_(boxc_tr _PL_ Root,ADDRESS Capacity);
//BoxClip : Tree Deletion
//＊If the tree is the deepest root, then the memory space will be deallocated, else the tree will point its root.
general BoxC_Tr_Delete_(boxc_tr *_PL_ Tree);
//BoxClip : Tree Memory Occupation of All Nodes
address BoxC_Tr_Size_(BOXC_TR *Tree);
//BoxClip : Tree Memory Occupation of the Current Node and its All Leaves
address BoxC_Tr_Used_(BOXC_TR _PL_ Tree);

//BoxClip : Tree's Left Capacity
address BoxC_Tr_Left_(BOXC_TR _PL_ Tree);
//BoxClip : Tree's Deepest Root
boxc_tr *BoxC_Tr_Origin_(boxc_tr _PL_ Tree);
//BoxClip : Current Node's Height
address BoxC_Tr_Height_(BOXC_TR *Tree);

//BoxClip : Move the Tree on the New Root
//＊Return value is ~0 for success, 0 for failure.
boolean BoxC_Tr_Move_(boxc_tr _PL_ Tree,boxc_tr _PL_ NewRoot);
#endif
#endif
#endif
