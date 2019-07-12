/*------------------------------------------------------------------*/
/*	BoxClip is a simple data structure library.						*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2019.07.12	*/
/*------------------------------------------------------------------*/

#ifndef _INC_BOXCLIP
#define _INC_BOXCLIP

#if(1)
#include <bitclip.h>
#endif

#if(Fold_(Definition:Types))
//BoxClip : Box Structure
struct _boxclip
{
	general *L;	//BoxClip : External Link
	address I;	//BoxClip : Identifier
};
MemC_Type_Declare_(struct,boxclip,BOXCLIP);	//BoxClip : Box Structure

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

//BoxClip : Key Set Structure
struct _boxc_ks
{
	GENERAL _PL_ Key;	//BoxClip : Internal Key Set
	//BoxClip : Ordering Function
	integer(_PL_ Comp_)(GENERAL _PL_,GENERAL _PL_);
	ADDRESS Number;		//BoxClip : Current Number of Keys
	ADDRESS Capacity;	//BoxClip : Maximum Number of Keys
};
MemC_Type_Declare_(struct,boxc_ks,BOXC_KS);	//BoxClip : Key Set Structure
static_assert((sizeof(boxc_ks)%sizeof(address))==0,"Type Size Misalign");

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

//BoxClip : Switch Structure
struct _boxc_sw
{
	BOXCLIP _PL_ Case;	//BoxClip : Case Mapping
	ADDRESS Number;		//BoxClip : The Number of Cases
};
MemC_Type_Declare_(struct,boxc_sw,BOXC_SW);	//BoxClip : Switch Structure
#endif

#if(Fold_(Library Casing))
//BoxClip : Library Case Structure
struct _boxcase
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
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Reset_All_)(BOXC_SS _PL_ StackSet);
		//BoxClip : Reset the Selected Stack
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Reset_)(BOXC_SS _PL_ StackSet,ADDRESS StackSelect);

		//BoxClip : Push an Object into the Selected Stack
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Push_)(BOXC_SS _PL_ StackSet,ADDRESS StackSelect,general _PL_ Object);
		//BoxClip : Pop an Object from the Selected Stack
		//＊Return value is the stored address.
		general*(_PL_ Pop_)(BOXC_SS _PL_ StackSet,ADDRESS StackSelect);
		//BoxClip : Spread Objects into the Memory Slot
		//＊Return value is the number of popped objects.
		address(_PL_ Spread_)(MEMC_MS _PL_ MemorySlot,BOXC_SS _PL_ StackSet,ADDRESS StackSelect);
#define BoxC_SS_Foreach_(StackSet,StackSelect,type,Each) for(type const(Each)=(MemC_Assert_(sizeof(type)==sizeof(address)),(type)0),_PL_(_Mark##Each)=(StackSet)?(((StackSelect)<((StackSet)->Number))?((general*)(((StackSet)->Count)+(StackSelect))):(NULL)):(NULL),*(_Temp##Each)=(*(address*)(_Mark##Each))?(FULL):(NULL);(_Temp##Each)?((Acs_(general*,Each)=BoxC.SS.Pop_(StackSet,StackSelect)),1):(0);(_Temp##Each)=(*(address*)(_Mark##Each))?(FULL):(NULL))

		//BoxClip : Check the Selected Stack
		//＊Return value is 1 only if the selected stack has no NULL object, otherwise 0.
		logical(_PL_ Check_)(BOXC_SS _PL_ StackSet,ADDRESS StackSelect);
		//BoxClip : Peek an Object in the Seleted Stack without Change
		//＊Return value is the stored address.
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
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Reset_All_)(BOXC_QS _PL_ QueueSet);
		//BoxClip : Reset the Selected Queue
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Reset_)(BOXC_QS _PL_ QueueSet,ADDRESS QueueSelect);

		//BoxClip : Enqueue an Object into the Selected Queue
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Enque_)(BOXC_QS _PL_ QueueSet,ADDRESS QueueSelect,general _PL_ Object);
		//BoxClip : Dequeue an Object from the Selected Queue
		//＊Return value is the stored address.
		general*(_PL_ Deque_)(BOXC_QS _PL_ QueueSet,ADDRESS QueueSelect);
		//BoxClip : Spread Objects into the Memory Slot
		//＊Return value is the number of dequeued objects.
		address(_PL_ Spread_)(MEMC_MS _PL_ MemorySlot,BOXC_QS _PL_ QueueSet,ADDRESS QueueSelect);
#define BoxC_QS_Foreach_(QueueSet,QueueSelect,type,Each) for(type const(Each)=(MemC_Assert_(sizeof(type)==sizeof(address)),(type)0),_PL_(_Mark##Each)=(QueueSet)?(((QueueSelect)<((QueueSet)->Number))?((general*)(((QueueSet)->Count)+(QueueSelect))):(NULL)):(NULL),*(_Temp##Each)=(*(address*)(_Mark##Each))?(FULL):(NULL);(_Temp##Each)?((Acs_(general*,Each)=BoxC.QS.Deque_(QueueSet,QueueSelect)),1):(0);(_Temp##Each)=(*(address*)(_Mark##Each))?(FULL):(NULL))

		//BoxClip : Check the Selected Queue
		//＊Return value is 1 only if the selected queue has no NULL object, otherwise 0.
		logical(_PL_ Check_)(BOXC_QS _PL_ QueueSet,ADDRESS QueueSelect);
		//BoxClip : Peek an Object in the Seleted Queue without Change
		//＊Return value is the stored address.
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
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Reset_All_)(BOXC_RS _PL_ RingSet);
		//BoxClip : Reset the Selected Ring
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Reset_)(BOXC_RS _PL_ RingSet,ADDRESS RingSelect);

		//BoxClip : Insert an Object into the Selected Ring
		//＊Enqueue left for direction 0, right for direction 1.
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Insert_)(BOXC_RS _PL_ RingSet,ADDRESS RingSelect,general _PL_ Object,LOGICAL Direction);
		//BoxClip : Desert an Object from the Selected Ring
		//＊Dequeue left for direction 0, right for direction 1.
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Desert_)(BOXC_RS _PL_ RingSet,ADDRESS RingSelect,LOGICAL Direction);
		//BoxClip : Rotate the Selected Ring
		//＊Move the pin left for negative rotation, right for positive rotation.
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Rotate_)(BOXC_RS _PL_ RingSet,ADDRESS RingSelect,SINTPTR Rotation);

		//BoxClip : Check the Selected Ring
		//＊Return value is 1 only if the selected ring has no NULL object, otherwise 0.
		logical(_PL_ Check_)(BOXC_RS _PL_ RingSet,ADDRESS RingSelect);
		//BoxClip : Read an Object in the Selected Ring without Change
		//＊Read left for direction 0, right for direction 1.
		//＊Return value is the stored address.
		general*(_PL_ Read_)(BOXC_RS _PL_ RingSet,ADDRESS RingSelect,LOGICAL Direction);
		//BoxClip : Spread Objects into the Memory Slot
		//＊Return value is the number of read objects.
		address(_PL_ Spread_)(MEMC_MS _PL_ MemorySlot,BOXC_RS _PL_ RingSet,ADDRESS RingSelect,SINTPTR Rotation,LOGICAL Mode);
#define BoxC_RS_Foreach_(RingSet,RingSelect,Rotation,Direction,type,Each) for(type const(Each)=(MemC_Assert_(sizeof(type)==sizeof(address)),(type)0),_PL_ _PL_(_Mark##Each)=(RingSet)?(((RingSelect)<((RingSet)->Number))?((general*)(((address*)((RingSet)->Ring))+((RingSelect)<<1))):(NULL)):(NULL),_PL_(_Stop##Each)=*(_Mark##Each),*(_Temp##Each)=FULL;(_Temp##Each)?((Acs_(general*,Each)=BoxC.RS.Read_(RingSet,RingSelect,Direction)),1):(0);(_Temp##Each)=(BoxC.RS.Rotate_(RingSet,RingSelect,Rotation))?(((_Stop##Each)==*(_Mark##Each))?(NULL):(FULL)):(NULL))
	}
	RS;

	//BoxClip : Map Functions
	const struct
	{
		//BoxClip : Key Set Memory Allocation - Deallocate with "BoxC.KS.Delete_"
		boxc_ks*(_PL_ Create_)(integer(_PL_ Compare_)(GENERAL _PL_ KeyA,GENERAL _PL_ KeyB),ADDRESS Capacity);
		//BoxClip : Key Set Memory Deallocation
		general(_PL_ Delete_)(boxc_ks *_PL_ KeySet);
		//BoxClip : Key Set Memory Occupation
		address(_PL_ Size_)(BOXC_KS _PL_ KeySet);
		//BoxClip : Remove All Keys
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Reset_)(boxc_ks _PL_ KeySet);

		//BoxClip : Key Functions
		const struct
		{
			//BoxClip : Enroll a Key into the Key Set
			logical(_PL_ Enroll_)(boxc_ks _PL_ KeySet,general _PL_ Key);
			//BoxClip : Remove a Key from the Key Set
			logical(_PL_ Remove_)(boxc_ks _PL_ KeySet,GENERAL _PL_ Key);
			//BoxClip : Verify a Key's Existence
			logical(_PL_ Verify_)(BOXC_KS _PL_ KeySet,GENERAL _PL_ Key);
			//BoxClip : Spread Keys into the Memory Slot
			//＊Return value is the number of copied keys.
			address(_PL_ Spread_)(MEMC_MS _PL_ MemorySlot,BOXC_KS _PL_ KeySet);
#define BoxC_KS_Foreach_(KeySet,type,Each) for(type const(Each)=(MemC_Assert_(sizeof(type)==sizeof(address)),(type)0),_PL_(_Num##Each)=Acs_(general*,(KeySet)->Number),*(_Idx##Each)=NULL;(Acs_(address,_Idx##Each)<Acs_(address,_Num##Each))?((Acs_(type,Each)=BoxC.KS.Index.Search_(KeySet,Acs_(address,_Idx##Each))),1):(0);Acs_(address,_Idx##Each)++)
		}
		Key;

		//BoxClip : Value Functions
		const struct
		{
			//BoxClip : Write a Value at the Key
			logical(_PL_ Writer_)(BOXC_KS _PL_ KeySet,GENERAL _PL_ Key,general _PL_ Value);
			//BoxClip : Read a Value at the Key
			general*(_PL_ Reader_)(BOXC_KS _PL_ KeySet,GENERAL _PL_ Key);
		}
		Value;

		//BoxClip : Index Functions
		const struct
		{
			//BoxClip : Convert from an Index to a Key
			general*(_PL_ Search_)(BOXC_KS _PL_ KeySet,ADDRESS Index);
			//BoxClip : Convert from a key to an Index
			//＊Return value is 1 for failure.
			address(_PL_ Locate_)(BOXC_KS _PL_ KeySet,GENERAL _PL_ Key);
		}
		Index;
	}
	KS;

	//BoxClip : Flag Functions
	const struct
	{
		//BoxClip : Flag Set Memory Allocation - Deallocate with "BoxC.FS.Delete_"
		boxc_fs*(_PL_ Create_)(ADDRESS FlagsNumber);
		//BoxClip : Flag Set Memory Deallocation
		general(_PL_ Delete_)(boxc_fs *_PL_ FlagSet);
		//BoxClip : Flag Set Memory Occupation
		address(_PL_ Size_)(BOXC_FS _PL_ FlagSet);
		//BoxClip : Reset All Flags
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Reset_All_)(BOXC_FS _PL_ FlagSet);

		//BoxClip : Write a Boolean into the Selected Flag
		//＊Boolean value should be 0 or 1.
		general(_PL_ Writer_)(BOXC_FS _PL_ FlagSet,ADDRESS FlagSelect,LOGICAL Boolean);
		//BoxClip : Read a Boolean from the Selected Flag
		//＊Return Value is the stored logical.
		logical(_PL_ Reader_)(BOXC_FS _PL_ FlagSet,ADDRESS FlagSelect);
		//BoxClip : Toggle a Boolean of the Selected Flag
		general(_PL_ Toggle_)(BOXC_FS _PL_ FlagSet,ADDRESS FlagSelect);
	}
	FS;

	//BoxClip : Tree Functions
	const struct
	{
		//BoxClip : Tree Creation - Delete with "BoxC.Tr.Delete_"
		//＊If the root is null, then a new memory space will be allocated, else the capacity should be 0.
		boxc_tr*(_PL_ Create_)(boxc_tr _PL_ Root,ADDRESS Capacity);
		//BoxClip : Tree Deletion
		//＊If the tree is the deepest root, then the memory space will be deallocated, else the tree will point its root.
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
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Move_)(boxc_tr _PL_ Tree,boxc_tr _PL_ NewRoot);
	}
	Tr;

	//BoxClip : Switch Functions
	const struct
	{
		//BoxClip : Switch Creation - Delete with "BoxC.Sw.Delete_"
		//＊Number = CaseList -> Slot.V[0]
		//　Case[idx].L = CaseList -> Slot.P[Case[idx].I]
		//＊All NULL cases will be mapped to 0, and duplicated non-NULL cases are not allowed.
		boxc_sw*(_PL_ Create_)(MEMC_MS _PL_ CaseList);
		//BoxClip : Switch Deletion
		general(_PL_ Delete_)(boxc_sw *_PL_ Switch);
		//BoxClip : Switch Memory Occupation
		address(_PL_ Size_)(BOXC_SW _PL_ Switch);

		//BoxClip : Case Finding
		//＊Mode 0 : Naive Search
		//　Mode 1 : Binary Search
		//＊Return value is a corresponding index of the found case, 0 for NULL, or 1 for the unknown.
		address(_PL_ Find_)(BOXC_SW _PL_ Switch,GENERAL _PL_ Case,LOGICAL SearchMode);
	}
	Sw;
};
MemC_Type_Declare_(struct,boxcase,BOXCASE);	//BoxClip : Library Case Structure

//BoxClip : Library Case Object
extern BOXCASE BoxC;
//BoxClip : Indirect access to the library case object.
extern BOXCASE *BoxC_(general);
#endif
#endif
