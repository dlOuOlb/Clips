/*------------------------------------------------------------------*/
/*	BoxClip provides some simple data structures.					*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2019.09.26	*/
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

//BoxClip : List Structure
struct _boxc_li
{
	ADDRESS Capacity;		//BoxClip : Maximum Number of Items
	ADDRESS Count;			//BoxClip : Current Number of Items
	general _PL_ Item[];	//BoxClip : Array of Items
};
MemC_Type_Declare_(struct,boxc_li,BOXC_LI);	//BoxClip : List Structure
#endif

#if(Fold_(Library Casing))
//BoxClip : Library Case Structure
struct _boxcase
{
	//BoxClip : Library Version
	BYTE_08 _PL_ Version;

	//BoxClip : Stack Set Functions
	const struct
	{
		//BoxClip : Stack Set Memory Allocation - Deallocate with "BoxC.SS.Delete_"
		boxc_ss*(_PL_ Create_)(ADDRESS StacksNumber,ADDRESS MaximumCapacity);
		//BoxClip : Stack Set Memory Deallocation
		general(_PL_ Delete_)(boxc_ss *_PL_ _R_ StackSet);
		//BoxClip : Stack Set Memory Occupation
		address(_PL_ Size_)(BOXC_SS _PL_ _R_ StackSet);

		//BoxClip : Functions for All Stacks
		const struct
		{
			//BoxClip : Reset all stacks.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Reset_)(BOXC_SS _PL_ _R_ StackSet);
			//BoxClip : Check all stacks.
			//＊Return value is 1 only if all stacks have no NULL object, otherwise 0.
			logical(_PL_ Check_)(BOXC_SS _PL_ _R_ StackSet);
		}
		All;

		//BoxClip : Reset the selected stack.
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Reset_)(BOXC_SS _PL_ _R_ StackSet,ADDRESS StackSelect);
		//BoxClip : Check the selected stack.
		//＊Return value is 1 only if the selected stack has no NULL object, otherwise 0.
		logical(_PL_ Check_)(BOXC_SS _PL_ _R_ StackSet,ADDRESS StackSelect);

		//BoxClip : Push an object into the selected stack.
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Push_)(BOXC_SS _PL_ _R_ StackSet,ADDRESS StackSelect,general _PL_ Object);
		//BoxClip : Pop an object from the selected stack.
		//＊Return value is the stored address.
		general*(_PL_ Pop_)(BOXC_SS _PL_ _R_ StackSet,ADDRESS StackSelect);
		//BoxClip : Pop and spread objects into the list.
		//＊Popping will be stopped when the list's count reaches its capacity.
		//＊Original items in the list will be just over-written.
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Spread_)(boxc_li _PL_ _R_ List,BOXC_SS _PL_ _R_ StackSet,ADDRESS StackSelect);
#define BoxC_SS_Foreach_(StackSet,StackSelect,type,Each) for(type const(Each)=(MemC_Assert_(sizeof(type)==sizeof(address)),(type)0),_PL_(_Mark##Each)=(StackSet)?(((StackSelect)<((StackSet)->Number))?((general*)(((StackSet)->Count)+(StackSelect))):(NULL)):(NULL),*(_Temp##Each)=(*(address*)(_Mark##Each))?(FULL):(NULL);(_Temp##Each)?((Acs_(general*,Each)=BoxC.SS.Pop_(StackSet,StackSelect)),1):(0);(_Temp##Each)=(*(address*)(_Mark##Each))?(FULL):(NULL))

		//BoxClip : Peek an object in the seleted stack without change.
		//＊Return value is the stored address.
		general*(_PL_ Peek_)(BOXC_SS _PL_ _R_ StackSet,ADDRESS StackSelect,ADDRESS Depth);
	}
	SS;

	//BoxClip : Queue Set Functions
	const struct
	{
		//BoxClip : Queue Set Memory Allocation - Deallocate with "BoxC.QS.Delete_"
		boxc_qs*(_PL_ Create_)(ADDRESS QueuesNumber,ADDRESS MaximumCapacity);
		//BoxClip : Queue Set Memory Deallocation
		general(_PL_ Delete_)(boxc_qs *_PL_ _R_ QueueSet);
		//BoxClip : Queue Set Memory Occupation
		address(_PL_ Size_)(BOXC_QS _PL_ _R_ QueueSet);

		//BoxClip : Functions for All Queues
		const struct
		{
			//BoxClip : Reset all queues.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Reset_)(BOXC_QS _PL_ _R_ QueueSet);
			//BoxClip : Check all queues.
			//＊Return value is 1 only if all queues have no NULL object, otherwise 0.
			logical(_PL_ Check_)(BOXC_QS _PL_ _R_ QueueSet);
		}
		All;

		//BoxClip : Reset the selected queue.
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Reset_)(BOXC_QS _PL_ _R_ QueueSet,ADDRESS QueueSelect);
		//BoxClip : Check the selected queue.
		//＊Return value is 1 only if the selected queue has no NULL object, otherwise 0.
		logical(_PL_ Check_)(BOXC_QS _PL_ _R_ QueueSet,ADDRESS QueueSelect);

		//BoxClip : Enqueue an object into the selected queue.
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Enque_)(BOXC_QS _PL_ _R_ QueueSet,ADDRESS QueueSelect,general _PL_ Object);
		//BoxClip : Dequeue an object from the selected queue.
		//＊Return value is the stored address.
		general*(_PL_ Deque_)(BOXC_QS _PL_ _R_ QueueSet,ADDRESS QueueSelect);
		//BoxClip : Dequeue and spread objects into the list.
		//＊Dequeueing will be stopped when the list's count reaches its capacity.
		//＊Original items in the list will be just over-written.
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Spread_)(boxc_li _PL_ _R_ List,BOXC_QS _PL_ _R_ QueueSet,ADDRESS QueueSelect);
#define BoxC_QS_Foreach_(QueueSet,QueueSelect,type,Each) for(type const(Each)=(MemC_Assert_(sizeof(type)==sizeof(address)),(type)0),_PL_(_Mark##Each)=(QueueSet)?(((QueueSelect)<((QueueSet)->Number))?((general*)(((QueueSet)->Count)+(QueueSelect))):(NULL)):(NULL),*(_Temp##Each)=(*(address*)(_Mark##Each))?(FULL):(NULL);(_Temp##Each)?((Acs_(general*,Each)=BoxC.QS.Deque_(QueueSet,QueueSelect)),1):(0);(_Temp##Each)=(*(address*)(_Mark##Each))?(FULL):(NULL))

		//BoxClip : Peek an object in the seleted queue without change.
		//＊Return value is the stored address.
		general*(_PL_ Peek_)(BOXC_QS _PL_ _R_ QueueSet,ADDRESS QueueSelect,ADDRESS Depth);
	}
	QS;

	//BoxClip : Ring Set Functions
	const struct
	{
		//BoxClip : Ring Set Memory Allocation - Deallocate with "BoxC.RS.Delete_"
		boxc_rs*(_PL_ Create_)(ADDRESS RingsNumber,ADDRESS MaximumCapacity);
		//BoxClip : Ring Set Memory Deallocation
		general(_PL_ Delete_)(boxc_rs *_PL_ _R_ RingSet);
		//BoxClip : Ring Set Memory Occupation
		address(_PL_ Size_)(BOXC_RS _PL_ _R_ RingSet);

		//BoxClip : Functions for All Rings
		const struct
		{
			//BoxClip : Reset all rings.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Reset_)(BOXC_RS _PL_ _R_ RingSet);
			//BoxClip : Check all rings.
			//＊Return value is 1 only if all rings have no NULL object, otherwise 0.
			logical(_PL_ Check_)(BOXC_RS _PL_ _R_ RingSet);
		}
		All;

		//BoxClip : Reset the selected ring.
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Reset_)(BOXC_RS _PL_ _R_ RingSet,ADDRESS RingSelect);
		//BoxClip : Check the selected ring.
		//＊Return value is 1 only if the selected ring has no NULL object, otherwise 0.
		logical(_PL_ Check_)(BOXC_RS _PL_ _R_ RingSet,ADDRESS RingSelect);

		//BoxClip : Insert an object into the selected ring.
		//＊Enqueue left for direction 0, right for direction 1.
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Insert_)(BOXC_RS _PL_ _R_ RingSet,ADDRESS RingSelect,general _PL_ Object,LOGICAL Direction);
		//BoxClip : Desert an object from the selected ring.
		//＊Dequeue left for direction 0, right for direction 1.
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Desert_)(BOXC_RS _PL_ _R_ RingSet,ADDRESS RingSelect,LOGICAL Direction);
		//BoxClip : Rotate the selected ring.
		//＊Move the pin left for negative rotation, right for positive rotation.
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Rotate_)(BOXC_RS _PL_ _R_ RingSet,ADDRESS RingSelect,SINTPTR Rotation);

		//BoxClip : Read an object in the selected ring without change.
		//＊Read left for direction 0, right for direction 1.
		//＊Return value is the stored address.
		general*(_PL_ Read_)(BOXC_RS _PL_ _R_ RingSet,ADDRESS RingSelect,LOGICAL Direction);
		//BoxClip : Read and spread objects into the list.
		//＊The list's capacity should not be less than the number of objects to be read.
		//＊Original items in the list will be just over-written.
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Spread_)(boxc_li _PL_ _R_ List,BOXC_RS _PL_ _R_ RingSet,ADDRESS RingSelect,SINTPTR Rotation,LOGICAL Mode);
#define BoxC_RS_Foreach_(RingSet,RingSelect,Rotation,Direction,type,Each) for(type const(Each)=(MemC_Assert_(sizeof(type)==sizeof(address)),(type)0),_PL_ _PL_(_Mark##Each)=(RingSet)?(((RingSelect)<((RingSet)->Number))?((general*)(((address*)((RingSet)->Ring))+((RingSelect)<<1))):(NULL)):(NULL),_PL_(_Stop##Each)=*(_Mark##Each),*(_Temp##Each)=FULL;(_Temp##Each)?((Acs_(general*,Each)=BoxC.RS.Read_(RingSet,RingSelect,Direction)),1):(0);(_Temp##Each)=(BoxC.RS.Rotate_(RingSet,RingSelect,Rotation))?(((_Stop##Each)==*(_Mark##Each))?(NULL):(FULL)):(NULL))
	}
	RS;

	//BoxClip : Key Set Functions
	const struct
	{
		//BoxClip : Key Set Memory Allocation - Deallocate with "BoxC.KS.Delete_"
		boxc_ks*(_PL_ Create_)(integer(_PL_ Compare_)(GENERAL _PL_ KeyA,GENERAL _PL_ KeyB),ADDRESS Capacity);
		//BoxClip : Key Set Memory Deallocation
		general(_PL_ Delete_)(boxc_ks *_PL_ _R_ KeySet);
		//BoxClip : Key Set Memory Occupation
		address(_PL_ Size_)(BOXC_KS _PL_ _R_ KeySet);

		//BoxClip : Remove all keys.
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Reset_)(boxc_ks _PL_ _R_ KeySet);

		//BoxClip : Key Functions
		const struct
		{
			//BoxClip : Enroll a key into the key set.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Enroll_)(boxc_ks _PL_ _R_ KeySet,general _PL_ Key);
			//BoxClip : Remove a key from the key set.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Remove_)(boxc_ks _PL_ _R_ KeySet,GENERAL _PL_ Key);
			//BoxClip : Verify whether a key exists or not.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Verify_)(BOXC_KS _PL_ _R_ KeySet,GENERAL _PL_ Key);
			//BoxClip : Spread keys into the list.
			//＊The list's capacity should not be less than the number of keys.
			//＊Original items in the list will be just over-written.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Spread_)(boxc_li _PL_ _R_ List,BOXC_KS _PL_ _R_ KeySet);
#define BoxC_KS_Foreach_(KeySet,type,Each) for(type const(Each)=(MemC_Assert_(sizeof(type)==sizeof(address)),(type)0),_PL_(_Num##Each)=Acs_(general*,(KeySet)->Number),*(_Idx##Each)=NULL;(Acs_(address,_Idx##Each)<Acs_(address,_Num##Each))?((Acs_(type,Each)=BoxC.KS.Index.Search_(KeySet,Acs_(address,_Idx##Each))),1):(0);Acs_(address,_Idx##Each)++)
		}
		Key;

		//BoxClip : Value Functions
		const struct
		{
			//BoxClip : Give a value to the key.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Writer_)(BOXC_KS _PL_ _R_ KeySet,GENERAL _PL_ Key,general _PL_ Value);
			//BoxClip : Take a value from the key.
			general*(_PL_ Reader_)(BOXC_KS _PL_ _R_ KeySet,GENERAL _PL_ Key);
		}
		Value;

		//BoxClip : Index Functions
		const struct
		{
			//BoxClip : Convert from an index to a key.
			//＊Return value is NULL for failure.
			general*(_PL_ Search_)(BOXC_KS _PL_ _R_ KeySet,ADDRESS Index);
			//BoxClip : Convert from a key to an index.
			//＊Return value is ~0 for failure.
			address(_PL_ Locate_)(BOXC_KS _PL_ _R_ KeySet,GENERAL _PL_ Key);
		}
		Index;
	}
	KS;

	//BoxClip : Flag Set Functions
	const struct
	{
		//BoxClip : Flag Set Memory Allocation - Deallocate with "BoxC.FS.Delete_"
		boxc_fs*(_PL_ Create_)(ADDRESS FlagsNumber);
		//BoxClip : Flag Set Memory Deallocation
		general(_PL_ Delete_)(boxc_fs *_PL_ _R_ FlagSet);
		//BoxClip : Flag Set Memory Occupation
		address(_PL_ Size_)(BOXC_FS _PL_ _R_ FlagSet);

		//BoxClip : Functions for All Flags
		const struct
		{
			//BoxClip : Reset all flags.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Reset_)(BOXC_FS _PL_ _R_ FlagSet);
		}
		All;

		//BoxClip : Write a boolean into the selected flag.
		//＊Boolean value should be 0 or 1.
		general(_PL_ Writer_)(BOXC_FS _PL_ _R_ FlagSet,ADDRESS FlagSelect,LOGICAL Boolean);
		//BoxClip : Read a boolean from the selected flag.
		//＊Return Value is the stored boolean value.
		logical(_PL_ Reader_)(BOXC_FS _PL_ _R_ FlagSet,ADDRESS FlagSelect);
		//BoxClip : Toggle a boolean of the selected flag.
		general(_PL_ Toggle_)(BOXC_FS _PL_ _R_ FlagSet,ADDRESS FlagSelect);
	}
	FS;

	//BoxClip : Tree Functions
	const struct
	{
		//BoxClip : Tree Creation - Delete with "BoxC.Tr.Delete_"
		//＊If the root is null, then a new memory space will be allocated, else the capacity should be 0.
		boxc_tr*(_PL_ Create_)(boxc_tr _PL_ _R_ Root,ADDRESS Capacity);
		//BoxClip : Tree Deletion
		//＊If the tree is the deepest root, then the memory space will be deallocated, else the tree will point its root.
		general(_PL_ Delete_)(boxc_tr *_PL_ _R_ Tree);
		//BoxClip : Tree Memory Occupation of All Nodes
		address(_PL_ Size_)(BOXC_TR _PL_ _R_ Tree);
		//BoxClip : Tree Memory Occupation of the Current Node and its All Leaves
		address(_PL_ Used_)(BOXC_TR _PL_ _R_ Tree);

		//BoxClip : Tree's Left Capacity
		address(_PL_ Left_)(BOXC_TR _PL_ _R_ Tree);
		//BoxClip : Tree's Deepest Root
		boxc_tr*(_PL_ Origin_)(boxc_tr _PL_ _R_ Tree);
		//BoxClip : Current Node's Height
		address(_PL_ Height_)(BOXC_TR _PL_ _R_ Tree);

		//BoxClip : Move the tree to the new root
		//＊Both trees should share the same origin.
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Move_)(boxc_tr _PL_ Tree,boxc_tr _PL_ NewRoot);
	}
	Tr;

	//BoxClip : Switch Functions
	const struct
	{
		//BoxClip : Switch Creation - Delete with "BoxC.Sw.Delete_"
		//＊Number = List -> Count
		//　Switch -> Case[idx].L = List -> Item[Switch -> Case[idx].I]
		//＊Duplicated cases are not allowed.
		boxc_sw*(_PL_ Create_)(BOXC_LI _PL_ _R_ List);
		//BoxClip : Switch Deletion
		general(_PL_ Delete_)(boxc_sw *_PL_ _R_ Switch);
		//BoxClip : Switch Memory Occupation
		address(_PL_ Size_)(BOXC_SW _PL_ _R_ Switch);

		//BoxClip : Case Finding
		//＊Mode 0 : Naive Search
		//　Mode 1 : Binary Search
		//＊Return value is a corresponding index of the found case, or FULL for the unknown case.
		address(_PL_ Find_)(BOXC_SW _PL_ _R_ Switch,GENERAL _PL_ Case,LOGICAL SearchMode);
	}
	Sw;

	//BoxClip : List Functions
	const struct
	{
		//BoxClip : Automatic List
#define BoxC_Li_Auto_(List,Capacity) address(_##List)[(Capacity)+2]={[0]=(Capacity),[1]=0};boxc_li _PL_(List)=(boxc_li*)(_##List);

		//BoxClip : List Creation - Delete with "BoxC.Li.Delete_"
		boxc_li*(_PL_ Create_)(ADDRESS Capacity);
		//BoxClip : List Deletion
		general(_PL_ Delete_)(boxc_li *_PL_ _R_ List);
		//BoxClip : List Memory Occupation
		address(_PL_ Size_)(BOXC_LI _PL_ _R_ List);

		//BoxClip : Desert all items.
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Reset_)(boxc_li _PL_ _R_ List);
		//BoxClip : Check the list.
		//＊Return value is 1 only if the list has no NULL object, otherwise 0.
		logical(_PL_ Check_)(BOXC_LI _PL_ _R_ List);
		
		//BoxClip : Functions for the Last Item
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//BoxClip : Append an item.
			//＊Equivalent to BoxC.Li.One.Insert_( List, List -> Count, Item ).
			logical(_PL_ Insert_)(boxc_li _PL_ _R_ List,general _PL_ Item);
			//BoxClip : Remove an item.
			//＊Equivalent to BoxC.Li.One.Desert_( List, List -> Count - 1 ).
			logical(_PL_ Desert_)(boxc_li _PL_ _R_ List);
		}
		Tip;

		//BoxClip : Functions for One Item
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//BoxClip : Insert an item.
			logical(_PL_ Insert_)(boxc_li _PL_ _R_ List,ADDRESS Offset,general _PL_ Item);
			//BoxClip : Desert an item.
			logical(_PL_ Desert_)(boxc_li _PL_ _R_ List,ADDRESS Offset);
		}
		One;

		//BoxClip : Functions for Lots of Items
		//＊Return value is 1 for success, 0 for failure.
		const struct
		{
			//BoxClip : Insert items.
			//＊(Number) and the number of variadic arguments must be equal!
			logical(_PL_ Insert_)(boxc_li _PL_ _R_ List,ADDRESS Offset,ADDRESS Number,...);
			//BoxClip : Desert items.
			logical(_PL_ Desert_)(boxc_li _PL_ _R_ List,ADDRESS Offset,ADDRESS Number);
		}
		Lot;

		//BoxClip : Copy some items.
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Copy_)(boxc_li _PL_ _R_ TargetList,BOXC_LI _PL_ _R_ SourceList,ADDRESS TargetOffset,ADDRESS SourceOffset,ADDRESS CopyNumber);
		//BoxClip : Filter all items.
		//＊The target list's capacity should not be less than the source list's count.
		//＊Original items in the target list will be just over-written.
		//＊Return value is 1 for success, 0 for failure.
		logical(_PL_ Filter_)(boxc_li _PL_ _R_ TargetList,BOXC_LI _PL_ _R_ SourceList,logical(_PL_ ItemFilter_)(general _PL_ _R_ SourceItem));

#define BoxC_Li_Foreach_(List,type,Each) for(type const(Each)=(MemC_Assert_(sizeof(type)==sizeof(address)),(type)0),*(_Ptr##Each)=(general*)((List)->Item),_PL_(_End##Each)=(general*)(((List)->Item)+((List)->Count));(((address)(_Ptr##Each))<((address)(_End##Each)))?((Acs_(address,Each)=*(address*)(_Ptr##Each)),1):(0);Acs_(address*,(_Ptr##Each))++)
	}
	Li;
};
MemC_Type_Declare_(struct,boxcase,BOXCASE);	//BoxClip : Library Case Structure

//BoxClip : Library Case Object
extern BOXCASE BoxC;
//BoxClip : Indirect access to the library case object.
extern BOXCASE *BoxC_(general);
#endif
#endif
