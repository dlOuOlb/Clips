/*------------------------------------------------------------------*/
/*	BoxClip is a simple data structure library.						*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2019.04.26	*/
/*------------------------------------------------------------------*/

#ifndef _INC_BOXCLIP
#define _INC_BOXCLIP

#if(1)
#include <bitclip.h>
#endif

#if(Fold_(Definition:Types))
//BoxClip : Stack Set Structure
struct _boxc_ss
{
	GENERAL _PL_ Stack;	//BoxClip : Internal Stack Set
	ADDRESS _PL_ Count;	//BoxClip : Length of Stacks where Count[-1] means Left Capacity
	ADDRESS Number;		//BoxClip : Number of Stacks
	ADDRESS Capacity;	//BoxClip : Maximum Total Stack Length
};
MemC_Type_Declare_(struct,boxc_ss,BOXC_SS);	//BoxClip : Stack Set Structure

//BoxClip : Queue Set Structure
struct _boxc_qs
{
	GENERAL _PL_ Queue;	//BoxClip : Internal Queue Set
	ADDRESS _PL_ Count;	//BoxClip : Length of Queues where Count[-1] means Left Capacity
	ADDRESS Number;		//BoxClip : Number of Queues
	ADDRESS Capacity;	//BoxClip : Maximum Total Queue Length
};
MemC_Type_Declare_(struct,boxc_qs,BOXC_QS);	//BoxClip : Queue Set Structure

//BoxClip : Ring Set Structure
struct _boxc_rs
{
	GENERAL _PL_ Ring;	//BoxClip : Internal Ring Set
	ADDRESS _PL_ Count;	//BoxClip : Length of Rings where Count[-1] means Left Capacity
	ADDRESS Number;		//BoxClip : Number of Rings
	ADDRESS Capacity;	//BoxClip : Maximum Total Ring Length
};
MemC_Type_Declare_(struct,boxc_rs,BOXC_RS);	//BoxClip : Ring Set Structure

//BoxClip : Flag Set Structure
struct _boxc_fs
{
	GENERAL _PL_ Flag;	//BoxClip : Internal Flag Set
	ADDRESS Number;		//BoxClip : Number of Flags
};
MemC_Type_Declare_(struct,boxc_fs,BOXC_FS);	//BoxClip : Flag Set Structure

MemC_Type_Declare_(struct,boxc_tr,BOXC_TR);	//BoxClip : Tree Structure
//BoxClip : Tree Structure
struct _boxc_tr
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
#endif

#if(Fold_(Library Casing))
//BoxClip : Library Case
extern const struct _boxcase
{
	//BoxClip : Library Version
	BYTE_08 _PL_ Version;

	//BoxClip : Stack Functions
	const struct
	{
		//BoxClip : Stack Set Memory Allocation - Deallocate with "BoxC.SS.Delete_"
		boxc_ss*(_PL_ Create_)(ADDRESS StacksNumber,ADDRESS MaximumCapacity);
		//BoxClip : Stack Set Memory Deallocation
		general(_PL_ Delete_)(boxc_ss *_PL_ StackSet);
		//BoxClip : Stack Set Memory Occupation
		address(_PL_ Size_)(BOXC_SS _PL_ StackSet);

		//BoxClip : Reset All Stacks
		//£ªReturn value is ~0 for success, 0 for failure.
		boolean(_PL_ Reset_All_)(BOXC_SS _PL_ StackSet);
		//BoxClip : Reset the Selected Stack
		//£ªReturn value is ~0 for success, 0 for failure.
		boolean(_PL_ Reset_)(BOXC_SS _PL_ StackSet,ADDRESS StackSelect);

		//BoxClip : Push an Object into the Selected Stack
		//£ªReturn value is ~0 for success, 0 for failure.
		boolean(_PL_ Push_)(BOXC_SS _PL_ StackSet,ADDRESS StackSelect,general _PL_ Object);
		//BoxClip : Pop an Object from the Selected Stack
		//£ªReturn value is the stored address.
		general*(_PL_ Pop_)(BOXC_SS _PL_ StackSet,ADDRESS StackSelect);

		//BoxClip : Check the Selected Stack
		//£ªReturn value is ~0 only if the selected stack has no NULL object, otherwise 0.
		boolean(_PL_ Check_)(BOXC_SS _PL_ StackSet,ADDRESS StackSelect);
		//BoxClip : Peek an Object in the Seleted Stack without Change
		//£ªReturn value is the stored address.
		general*(_PL_ Peek_)(BOXC_SS _PL_ StackSet,ADDRESS StackSelect,ADDRESS Depth);
	}
	SS;

	//BoxClip : Queue Functions
	const struct
	{
		//BoxClip : Queue Set Memory Allocation - Deallocate with "BoxC.QS.Delete_"
		boxc_qs*(_PL_ Create_)(ADDRESS QueuesNumber,ADDRESS MaximumCapacity);
		//BoxClip : Queue Set Memory Deallocation
		general(_PL_ Delete_)(boxc_qs *_PL_ QueueSet);
		//BoxClip : Queue Set Memory Occupation
		address(_PL_ Size_)(BOXC_QS _PL_ QueueSet);

		//BoxClip : Reset All Queues
		//£ªReturn value is ~0 for success, 0 for failure.
		boolean(_PL_ Reset_All_)(BOXC_QS _PL_ QueueSet);
		//BoxClip : Reset the Selected Queue
		//£ªReturn value is ~0 for success, 0 for failure.
		boolean(_PL_ Reset_)(BOXC_QS _PL_ QueueSet,ADDRESS QueueSelect);

		//BoxClip : Enqueue an Object into the Selected Queue
		//£ªReturn value is ~0 for success, 0 for failure.
		boolean(_PL_ Enque_)(BOXC_QS _PL_ QueueSet,ADDRESS QueueSelect,general _PL_ Object);
		//BoxClip : Dequeue an Object from the Selected Queue
		//£ªReturn value is the stored address.
		general*(_PL_ Deque_)(BOXC_QS _PL_ QueueSet,ADDRESS QueueSelect);

		//BoxClip : Check the Selected Queue
		//£ªReturn value is ~0 only if the selected queue has no NULL object, otherwise 0.
		boolean(_PL_ Check_)(BOXC_QS _PL_ QueueSet,ADDRESS QueueSelect);
		//BoxClip : Peek an Object in the Seleted Queue without Change
		//£ªReturn value is the stored address.
		general*(_PL_ Peek_)(BOXC_QS _PL_ QueueSet,ADDRESS QueueSelect,ADDRESS Depth);
	}
	QS;

	//BoxClip : Ring Functions
	const struct
	{
		//BoxClip : Ring Set Memory Allocation - Deallocate with "BoxC.RS.Delete_"
		boxc_rs*(_PL_ Create_)(ADDRESS RingsNumber,ADDRESS MaximumCapacity);
		//BoxClip : Ring Set Memory Deallocation
		general(_PL_ Delete_)(boxc_rs *_PL_ RingSet);
		//BoxClip : Ring Set Memory Occupation
		address(_PL_ Size_)(BOXC_RS _PL_ RingSet);

		//BoxClip : Reset All Rings
		//£ªReturn value is ~0 for success, 0 for failure.
		boolean(_PL_ Reset_All_)(BOXC_RS _PL_ RingSet);
		//BoxClip : Reset the Selected Ring
		//£ªReturn value is ~0 for success, 0 for failure.
		boolean(_PL_ Reset_)(BOXC_RS _PL_ RingSet,ADDRESS RingSelect);

		//BoxClip : Insert an Object into the Selected Ring
		//£ªEnqueue left for direction 0, right for direction ~0.
		//£ªReturn value is ~0 for success, 0 for failure.
		boolean(_PL_ Insert_)(BOXC_RS _PL_ RingSet,ADDRESS RingSelect,general _PL_ Object,BOOLEAN Direction);
		//BoxClip : Desert an Object from the Selected Ring
		//£ªDequeue left for direction 0, right for direction ~0.
		//£ªReturn value is ~0 for success, 0 for failure.
		boolean(_PL_ Desert_)(BOXC_RS _PL_ RingSet,ADDRESS RingSelect,BOOLEAN Direction);
		//BoxClip : Rotate the Selected Ring
		//£ªMove the pin left for negative rotation, right for positive rotation.
		//£ªReturn value is ~0 for success, 0 for failure.
		boolean(_PL_ Rotate_)(BOXC_RS _PL_ RingSet,ADDRESS RingSelect,INTEGER Rotation);

		//BoxClip : Check the Selected Ring
		//£ªReturn value is ~0 only if the selected ring has no NULL object, otherwise 0.
		boolean(_PL_ Check_)(BOXC_RS _PL_ RingSet,ADDRESS RingSelect);
		//BoxClip : Read an Object in the Selected Ring without Change
		//£ªRead left for direction 0, right for direction ~0.
		//£ªReturn value is the stored address.
		general*(_PL_ Read_)(BOXC_RS _PL_ RingSet,ADDRESS RingSelect,BOOLEAN Direction);
	}
	RS;

	//BoxClip : Flag Functions
	const struct
	{
		//BoxClip : Flag Set Memory Allocation - Deallocate with "BoxC.FS.Delete_"
		boxc_fs*(_PL_ Create_)(ADDRESS FlagsNumber);
		//BoxClip : Flag Set Memory Deallocation
		general(_PL_ Delete_)(boxc_fs *_PL_ FlagSet);
		//BoxClip : Flag Set Memory Occupation
		address(_PL_ Size_)(BOXC_FS _PL_ FlagSet);

		//BoxClip : Write a Boolean into the Selected Flag
		//£ªBoolean value should be 0 or ~0.
		general(_PL_ Writer_)(BOXC_FS _PL_ FlagSet,ADDRESS FlagSelect,BOOLEAN Boolean);
		//BoxClip : Read a Boolean from the Selected Flag
		//£ªReturn Value is the stored boolean.
		boolean(_PL_ Reader_)(BOXC_FS _PL_ FlagSet,ADDRESS FlagSelect);
		//BoxClip : Toggle a Boolean of the Selected Flag
		general(_PL_ Toggle_)(BOXC_FS _PL_ FlagSet,ADDRESS FlagSelect);
	}
	FS;

	//BoxClip : Tree Functions
	const struct
	{
		//BoxClip : Tree Creation - Delete with "BoxC.Tr.Delete_"
		//£ªIf the root is null, then a new memory space will be allocated, else the capacity should be 0.
		boxc_tr*(_PL_ Create_)(boxc_tr _PL_ Root,ADDRESS Capacity);
		//BoxClip : Tree Deletion
		//£ªIf the tree is the deepest root, then the memory space will be deallocated, else the tree will point its root.
		general(_PL_ Delete_)(boxc_tr *_PL_ Tree);
		//BoxClip : Tree Memory Occupation of All Nodes
		address(_PL_ Size_)(BOXC_TR _PL_ Tree);
		//BoxClip : Tree Memory Occupation of the Current Node and its All Leaves
		address(_PL_ Used_)(BOXC_TR _PL_ Tree);

		//BoxClip : Tree's Left Capacity
		address(_PL_ Left_)(BOXC_TR _PL_ Tree);
		//BoxClip : Tree's Deepest Root
		boxc_tr*(_PL_ Origin_)(boxc_tr _PL_ Tree);
		//BoxClip : Current Node's Height
		address(_PL_ Height_)(BOXC_TR _PL_ Tree);

		//BoxClip : Move the Tree on the New Root
		//£ªReturn value is ~0 for success, 0 for failure.
		boolean(_PL_ Move_)(boxc_tr _PL_ Tree,boxc_tr _PL_ NewRoot);
	}
	Tr;
}
BoxC;
#endif
#endif
