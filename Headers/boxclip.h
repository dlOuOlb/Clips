#ifndef oBOXCLIP_INC_
#define oBOXCLIP_INC_ "BoxC:2020.01.31"
/*------------------------------------------------------------------+
|	BoxClip provides some simple data structures.					|
|																	|
|	Written by Ranny Clover											|
|	http://github.com/dlOuOlb/Clips/blob/master/Headers/boxclip.h	|
+-------------------------------------------------------------------+
|	Dependency:														|
|																	|
|	MSVClip -- MemClip -- PenClip -- OCLClip -- BitClip -- BoxClip	|
+------------------------------------------------------------------*/

#include <bitclip.h>

#if(Fold_(Plain Types))
//BoxClip : Box Structure
struct _boxclip
{
	general *L;	//BoxClip : External Link
	address I;	//BoxClip : Identifier
};
MemC_Type_Declare_(struct,boxclip,BOXCLIP);	//BoxClip : Box Structure
#endif

#if(Fold_(Advanced Types))
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

//BoxClip : Flag Set Structure
struct _boxc_fs
{
	GENERAL _PL_ Flag;	//BoxClip : Internal Flag Set
	ADDRESS Number;		//BoxClip : Number of Flags
};
MemC_Type_Declare_(struct,boxc_fs,BOXC_FS);	//BoxClip : Flag Set Structure

//BoxClip : Tree Structure
struct _boxc_tr
{
	struct _boxc_tr _PL_ Root;	//BoxClip : Root Node
	struct _boxc_tr _PL_ Leaf;	//BoxClip : Leaf Node
	struct _boxc_tr _PL_ Prev;	//BoxClip : Previous Node
	struct _boxc_tr _PL_ Next;	//BoxClip : Next Node
	ADDRESS Count;				//BoxClip : Number of Current Leaves
	ADDRESS Total;				//BoxClip : Number of All Leaves
	general _PL_ Link;			//BoxClip : Internal Linking
	general *Object;			//BoxClip : User Object
};
MemC_Type_Declare_(struct,boxc_tr,BOXC_TR);	//BoxClip : Tree Structure

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
typedef const struct
{
	//BoxClip : Some Trivials
	const struct
	{
		//BoxClip : Library Version - "BoxC:yyyy.mm.dd"
		BYTE_08 _PL_ _R_ Version;

		//BoxClip : Just return the input.
		GENERAL*(_PL_ Just_)(GENERAL _PL_);
	};

	//BoxClip : String Comparators
	const struct
	{
		//BoxClip : Compare null-terminated narrow strings.
		integer(_PL_ T08_)(TEXT_08 _PL_ A,TEXT_08 _PL_ B);
		//BoxClip : Compare null-terminated wide strings.
		integer(_PL_ T16_)(TEXT_16 _PL_ A,TEXT_16 _PL_ B);
	}
	Comp;

	//BoxClip : Stack Set Functions
	const struct
	{
		//BoxClip : Creation and Deletion
		const struct
		{
			//BoxClip : Stack Set Memory Allocation - Deallocate with "BoxC.SS.Delete_"
			boxc_ss*(_PL_ Create_)(ADDRESS StacksNumber,ADDRESS MaximumCapacity);
			//BoxClip : Stack Set Memory Deallocation
			general(_PL_ Delete_)(boxc_ss *_PL_ _R_);
			//BoxClip : Stack Set Memory Occupation
			address(_PL_ Size_)(BOXC_SS _PL_ _R_ StackSet);

			//BoxClip : Automatic Stack Set - Use "BoxC_SS_Auto_"
			boxc_ss*(_PL_ Auto_)(boxc_ss _PL_ _R_);
#if(Fold_(Auto))
#define BoxC_SS_Auto_(Auto,StacksNumber,MaximumCapacity)\
			auto boxc_ss _PL_(Auto)=BoxC.SS.Auto_\
			(\
				&(boxc_ss)\
				{\
					.Stack=1+((address[1+(StacksNumber)+((MaximumCapacity)<<1)]){0}),\
					.Count=1+((address[1+(StacksNumber)]){MaximumCapacity}),\
					.Number=(StacksNumber),\
					.Capacity=(MaximumCapacity)\
				}\
			)
#endif
		};

		//BoxClip : Functions for All Stacks
		const struct
		{
			//BoxClip : Reset all stacks.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Reset_)(BOXC_SS _PL_ _R_ StackSet);
			//BoxClip : Check all stacks.
			//＊Return value is 1 only if all stacks have no null object, otherwise 0.
			logical(_PL_ Check_)(BOXC_SS _PL_ _R_ StackSet);
		}
		All;

		//BoxClip : Reset and Check
		const struct
		{
			//BoxClip : Reset the selected stack.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Reset_)(BOXC_SS _PL_ _R_ StackSet,ADDRESS StackSelect);
			//BoxClip : Check the selected stack.
			//＊Return value is 1 only if the selected stack has no null object, otherwise 0.
			logical(_PL_ Check_)(BOXC_SS _PL_ _R_ StackSet,ADDRESS StackSelect);
		};

		//BoxClip : Stack Operations
		const struct
		{
			//BoxClip : Push an object into the selected stack.
			//＊Null object is not allowed.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Push_)(BOXC_SS _PL_ _R_ StackSet,ADDRESS StackSelect,general _PL_ Object);
			//BoxClip : Pop an object from the selected stack.
			//＊Return value is the stored address for success, null for failure.
			general*(_PL_ Pop_)(BOXC_SS _PL_ _R_ StackSet,ADDRESS StackSelect);
			//BoxClip : Peek an object in the seleted stack without change.
			//＊Return value is the stored address.
			general*(_PL_ Peek_)(BOXC_SS _PL_ _R_ StackSet,ADDRESS StackSelect,ADDRESS Depth);
			//BoxClip : Pop and spread objects into the list.
			//＊Popping will be stopped when the list's count reaches its capacity.
			//＊Original items in the list will be just over-written.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Spread_)(boxc_li _PL_ _R_ List,BOXC_SS _PL_ _R_ StackSet,ADDRESS StackSelect);

#if(Fold_(Generic))
#define BoxC_SS_Generic_($tag,type)\
			xBoxC_Check_(type);\
			typedef union{boxc_ss*Core;const struct{ADDRESS Hidden,_PL_ Count,Number,Capacity;}_PL_ Wrap;}boxc_ss$##$tag;\
			typedef const boxc_ss$##$tag BOXC_SS$##$tag;\
			const struct\
			{\
				logical(_PL_ Push_)(BOXC_SS$##$tag,ADDRESS Sel,type const Obj);\
				type\
					(_PL_ Pop_)(BOXC_SS$##$tag,ADDRESS Sel),\
					(_PL_ Peek_)(BOXC_SS$##$tag,ADDRESS Sel,ADDRESS Depth);\
				logical(_PL_ Spread_)(BOXC_LI$##$tag,BOXC_SS$##$tag,ADDRESS Sel);\
			}\
			_PL_ _R_(SS$##$tag)=(GENERAL*)&(BoxC.SS.Push_)
#endif
		};

#if(Fold_(Foreach: Pop for each object.))
#define BoxC_SS_Foreach_(StackSet,StackSelect,type,Each)\
		for\
		(\
			ADDRESS*Conc_(xBoxCMark,__LINE__)=\
			(\
				MemC_Assert_(sizeof(address)==sizeof(type)),\
				assert((StackSet)&&((StackSelect)<((StackSet)->Number))),\
				(((StackSet)->Count)+(StackSelect))\
			);\
			Conc_(xBoxCMark,__LINE__);\
			Conc_(xBoxCMark,__LINE__)=NULL\
		)\
		while(*Conc_(xBoxCMark,__LINE__))\
		MemC_Temp_(type,const(Each)=BoxC.SS.Pop_(StackSet,StackSelect))
#endif
	}
	SS;

	//BoxClip : Queue Set Functions
	const struct
	{
		//BoxClip : Creation and Deletion
		const struct
		{
			//BoxClip : Queue Set Memory Allocation - Deallocate with "BoxC.QS.Delete_"
			boxc_qs*(_PL_ Create_)(ADDRESS QueuesNumber,ADDRESS MaximumCapacity);
			//BoxClip : Queue Set Memory Deallocation
			general(_PL_ Delete_)(boxc_qs *_PL_ _R_);
			//BoxClip : Queue Set Memory Occupation
			address(_PL_ Size_)(BOXC_QS _PL_ _R_ QueueSet);

			//BoxClip : Automatic Queue Set - Use "BoxC_QS_Auto_"
			boxc_qs*(_PL_ Auto_)(boxc_qs _PL_ _R_);
#if(Fold_(Auto))
#define BoxC_QS_Auto_(Auto,QueuesNumber,MaximumCapacity)\
			auto boxc_qs _PL_(Auto)=BoxC.QS.Auto_\
			(\
				&(boxc_qs)\
				{\
					.Queue=2+((address[(1+(QueuesNumber)+(MaximumCapacity))<<1]){0}),\
					.Count=1+((address[1+(QueuesNumber)]){MaximumCapacity}),\
					.Number=(QueuesNumber),\
					.Capacity=(MaximumCapacity)\
				}\
			)
#endif
		};

		//BoxClip : Functions for All Queues
		const struct
		{
			//BoxClip : Reset all queues.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Reset_)(BOXC_QS _PL_ _R_ QueueSet);
			//BoxClip : Check all queues.
			//＊Return value is 1 only if all queues have no null object, otherwise 0.
			logical(_PL_ Check_)(BOXC_QS _PL_ _R_ QueueSet);
		}
		All;

		//BoxClip : Reset and Check
		const struct
		{
			//BoxClip : Reset the selected queue.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Reset_)(BOXC_QS _PL_ _R_ QueueSet,ADDRESS QueueSelect);
			//BoxClip : Check the selected queue.
			//＊Return value is 1 only if the selected queue has no null object, otherwise 0.
			logical(_PL_ Check_)(BOXC_QS _PL_ _R_ QueueSet,ADDRESS QueueSelect);
		};

		//BoxClip : Queue Operations
		const struct
		{
			//BoxClip : Enqueue an object into the selected queue.
			//＊Null object is not allowed.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Enque_)(BOXC_QS _PL_ _R_ QueueSet,ADDRESS QueueSelect,general _PL_ Object);
			//BoxClip : Dequeue an object from the selected queue.
			//＊Return value is the stored address for success, null for failure.
			general*(_PL_ Deque_)(BOXC_QS _PL_ _R_ QueueSet,ADDRESS QueueSelect);
			//BoxClip : Peek an object in the seleted queue without change.
			//＊Return value is the stored address.
			general*(_PL_ Peek_)(BOXC_QS _PL_ _R_ QueueSet,ADDRESS QueueSelect,ADDRESS Depth);
			//BoxClip : Dequeue and spread objects into the list.
			//＊Dequeueing will be stopped when the list's count reaches its capacity.
			//＊Original items in the list will be just over-written.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Spread_)(boxc_li _PL_ _R_ List,BOXC_QS _PL_ _R_ QueueSet,ADDRESS QueueSelect);

#if(Fold_(Generic))
#define BoxC_QS_Generic_($tag,type)\
			xBoxC_Check_(type);\
			typedef union{boxc_qs*Core;const struct{ADDRESS Hidden,_PL_ Count,Number,Capacity;}_PL_ Wrap;}boxc_qs$##$tag;\
			typedef const boxc_qs$##$tag BOXC_QS$##$tag;\
			const struct\
			{\
				logical(_PL_ Enque_)(BOXC_QS$##$tag,ADDRESS Sel,type const Obj);\
				type\
					(_PL_ Deque_)(BOXC_QS$##$tag,ADDRESS Sel),\
					(_PL_ Peek_)(BOXC_QS$##$tag,ADDRESS Sel,ADDRESS Depth);\
				logical(_PL_ Spread_)(BOXC_LI$##$tag,BOXC_QS$##$tag,ADDRESS Sel);\
			}\
			_PL_ _R_(QS$##$tag)=(GENERAL*)&(BoxC.QS.Enque_)
#endif
		};

#if(Fold_(Foreach: Dequeue for each object.))
#define BoxC_QS_Foreach_(QueueSet,QueueSelect,type,Each)\
		for\
		(\
			ADDRESS*Conc_(xBoxCMark,__LINE__)=\
			(\
				MemC_Assert_(sizeof(address)==sizeof(type)),\
				assert((QueueSet)&&((QueueSelect)<((QueueSet)->Number))),\
				(((QueueSet)->Count)+(QueueSelect))\
			);\
			Conc_(xBoxCMark,__LINE__);\
			Conc_(xBoxCMark,__LINE__)=NULL\
		)\
		while(*Conc_(xBoxCMark,__LINE__))\
		MemC_Temp_(type,const(Each)=BoxC.QS.Deque_(QueueSet,QueueSelect))
#endif
	}
	QS;

	//BoxClip : Ring Set Functions
	const struct
	{
		//BoxClip : Creation and Deletion
		const struct
		{
			//BoxClip : Ring Set Memory Allocation - Deallocate with "BoxC.RS.Delete_"
			boxc_rs*(_PL_ Create_)(ADDRESS RingsNumber,ADDRESS MaximumCapacity);
			//BoxClip : Ring Set Memory Deallocation
			general(_PL_ Delete_)(boxc_rs *_PL_ _R_);
			//BoxClip : Ring Set Memory Occupation
			address(_PL_ Size_)(BOXC_RS _PL_ _R_ RingSet);

			//BoxClip : Automatic Ring Set - Use "BoxC_RS_Auto_"
			boxc_rs*(_PL_ Auto_)(boxc_rs _PL_ _R_);
#if(Fold_(Auto))
#define BoxC_RS_Auto_(Auto,RingsNumber,MaximumCapacity)\
			auto boxc_rs _PL_(Auto)=BoxC.RS.Auto_\
			(\
				&(boxc_rs)\
				{\
					.Ring=2+((address[(1+(RingsNumber)+(MaximumCapacity))<<1]){0}),\
					.Count=1+((address[1+(RingsNumber)]){MaximumCapacity}),\
					.Number=(RingsNumber),\
					.Capacity=(MaximumCapacity)\
				}\
			)
#endif
		};

		//BoxClip : Functions for All Rings
		const struct
		{
			//BoxClip : Reset all rings.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Reset_)(BOXC_RS _PL_ _R_ RingSet);
			//BoxClip : Check all rings.
			//＊Return value is 1 only if all rings have no null object, otherwise 0.
			logical(_PL_ Check_)(BOXC_RS _PL_ _R_ RingSet);
		}
		All;

		//BoxClip : Reset and Check
		const struct
		{
			//BoxClip : Reset the selected ring.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Reset_)(BOXC_RS _PL_ _R_ RingSet,ADDRESS RingSelect);
			//BoxClip : Check the selected ring.
			//＊Return value is 1 only if the selected ring has no null object, otherwise 0.
			logical(_PL_ Check_)(BOXC_RS _PL_ _R_ RingSet,ADDRESS RingSelect);
		};

		//BoxClip : Ring Operations
		const struct
		{
			//BoxClip : Insert an object into the selected ring.
			//＊Enqueue left for direction 0, right for direction 1.
			//＊Null object is not allowed.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Insert_)(BOXC_RS _PL_ _R_ RingSet,ADDRESS RingSelect,general _PL_ Object,LOGICAL Direction);
			//BoxClip : Desert an object from the selected ring.
			//＊Dequeue left for direction 0, right for direction 1.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Desert_)(BOXC_RS _PL_ _R_ RingSet,ADDRESS RingSelect,LOGICAL Direction);
			//BoxClip : Read an object in the selected ring without change.
			//＊Read left for direction 0, right for direction 1.
			//＊Return value is the stored address.
			general*(_PL_ Read_)(BOXC_RS _PL_ _R_ RingSet,ADDRESS RingSelect,LOGICAL Direction);
			//BoxClip : Read and spread objects into the list.
			//＊The list's capacity should not be less than the number of objects to be read.
			//＊Original items in the list will be just over-written.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Spread_)(boxc_li _PL_ _R_ List,BOXC_RS _PL_ _R_ RingSet,ADDRESS RingSelect,SINTPTR Rotation,LOGICAL Mode);

#if(Fold_(Generic))
#define BoxC_RS_Generic_($tag,type)\
			xBoxC_Check_(type);\
			typedef union{boxc_rs*Core;const struct{ADDRESS Hidden,_PL_ Count,Number,Capacity;}_PL_ Wrap;}boxc_rs$##$tag;\
			typedef const boxc_rs$##$tag BOXC_RS$##$tag;\
			const struct\
			{\
				logical\
					(_PL_ Insert_)(BOXC_RS$##$tag,ADDRESS Sel,type const Obj,LOGICAL Dir),\
					(_PL_ Desert_)(BOXC_RS$##$tag,ADDRESS Sel,LOGICAL Dir);\
				type(_PL_ Read_)(BOXC_RS$##$tag,ADDRESS Sel,LOGICAL Dir);\
				logical(_PL_ Spread_)(BOXC_LI$##$tag,BOXC_RS$##$tag,ADDRESS Sel,SINTPTR Rot,LOGICAL Mode);\
			}\
			_PL_ _R_(RS$##$tag)=(GENERAL*)&(BoxC.RS.Insert_)
#endif
		};

		//BoxClip : Rotate and Flip
		const struct
		{
			//BoxClip : Rotate the selected ring.
			//＊Move the pin left for negative rotation, right for positive rotation.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Rotate_)(BOXC_RS _PL_ _R_ RingSet,ADDRESS RingSelect,SINTPTR Rotation);
			//BoxClip : Flip the direction of the selected ring.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Flip_)(BOXC_RS _PL_ _R_ RingSet,ADDRESS RingSelect);
		};

		//BoxClip : Preserved for Future Usage
		ADDRESS xPreserved[2];

#if(Fold_(Foreach: Read for each object.))
#define BoxC_RS_Foreach_(RingSet,RingSelect,Rotation,Direction,type,Each)\
		for\
		(\
			GENERAL\
				_PL_ _PL_ Conc_(xBoxCMark,__LINE__)=\
				(\
					MemC_Assert_(sizeof(address)==sizeof(type)),\
					assert((RingSet)&&((RingSelect)<((RingSet)->Number))),\
					(((GENERAL**)((RingSet)->Ring))+((RingSelect)<<1))\
				),\
				_PL_ Conc_(xBoxCStop,__LINE__)=*Conc_(xBoxCMark,__LINE__),\
				*Conc_(xBoxCBool,__LINE__)=((RingSet)->Count[RingSelect])?(FULL):(NULL);\
			Conc_(xBoxCBool,__LINE__);\
			Conc_(xBoxCBool,__LINE__)=\
				(BoxC.RS.Rotate_(RingSet,RingSelect,Rotation))?\
				((Conc_(xBoxCStop,__LINE__)==*Conc_(xBoxCMark,__LINE__))?(NULL):(FULL)):\
				(NULL)\
		)\
		for\
		(\
			type const(Each)=BoxC.RS.Read_(RingSet,RingSelect,Direction);\
			Conc_(xBoxCBool,__LINE__);\
			Conc_(xBoxCBool,__LINE__)=NULL\
		)
#endif
	}
	RS;

	//BoxClip : Key Set Functions
	const struct
	{
		//BoxClip : Creation and Deletion
		const struct
		{
			//BoxClip : Key Set Memory Allocation - Deallocate with "BoxC.KS.Delete_"
			boxc_ks*(_PL_ Create_)(integer(_PL_ Compare_)(GENERAL _PL_ KeyA,GENERAL _PL_ KeyB),ADDRESS Capacity);
			//BoxClip : Key Set Memory Deallocation
			general(_PL_ Delete_)(boxc_ks *_PL_ _R_);
			//BoxClip : Key Set Memory Occupation
			address(_PL_ Size_)(BOXC_KS _PL_ _R_ KeySet);

			//BoxClip : Automatic Key Set - Use "BoxC_KS_Auto_"
			boxc_ks*(_PL_ Auto_)(boxc_ks _PL_ _R_);
#if(Fold_(Auto))
#define BoxC_KS_Auto_(Auto,Comparator_,MaximumCapacity)\
			auto boxc_ks _PL_(Auto)=BoxC.KS.Auto_\
			(\
				&(boxc_ks)\
				{\
					.Key=(address[2+(6*(MaximumCapacity))]){0},\
					.Comp_=(Comparator_),\
					.Capacity=(MaximumCapacity)\
				}\
			)
#endif
		};

		//BoxClip : Key and Value Operations
		const struct
		{
			//BoxClip : Key Functions
			const struct
			{
				//BoxClip : Enroll a key into the key set.
				//＊Null key is not allowed.
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

#if(Fold_(Foreach: Take for each key.))
#define BoxC_KS_Foreach_(KeySet,type_key,Each)\
				for\
				(\
					address Conc_(xBoxCTrip,__LINE__)=\
					(\
						MemC_Assert_(sizeof(address)==sizeof(type_key)),\
						assert((KeySet)&&(1)),\
						(0)\
					);\
					Conc_(xBoxCTrip,__LINE__)<((KeySet)->Number);\
					Conc_(xBoxCTrip,__LINE__)++\
				)\
				MemC_Temp_(type_key,const(Each)=BoxC.KS.Index.Search_(KeySet,Conc_(xBoxCTrip,__LINE__)))
#endif
			}
			Key;

			//BoxClip : Value Functions
			const struct
			{
				//BoxClip : Give a value to the key.
				//＊Null value is not allowed.
				//＊Return value is 1 for success, 0 for failure.
				logical(_PL_ Writer_)(BOXC_KS _PL_ _R_ KeySet,GENERAL _PL_ Key,general _PL_ Value);
				//BoxClip : Take a value from the key.
				//＊Return value is the stored value for success, null for failure.
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

#if(Fold_(Generic))
#define BoxC_KS_Generic_($tag,type_key,type_value)\
			xBoxC_Check_(type_key);\
			xBoxC_Check_(type_value);\
			typedef union{boxc_ks*Core;const struct{ADDRESS Hidden;integer(_PL_ Comp_)(type_key const,type_key const);ADDRESS Number,Capacity;}_PL_ Wrap;}boxc_ks$##$tag;\
			typedef const boxc_ks$##$tag BOXC_KS$##$tag;\
			const struct\
			{\
				const struct\
				{\
					logical\
						(_PL_ Enroll_)(BOXC_KS$##$tag,type_key const Key),\
						(_PL_ Remove_)(BOXC_KS$##$tag,type_key const Key),\
						(_PL_ Verify_)(BOXC_KS$##$tag,type_key const Key),\
						(_PL_ Spread_)(BOXC_LI$##$tag,BOXC_KS$##$tag);\
				}\
				Key;\
				const struct\
				{\
					logical(_PL_ Writer_)(BOXC_KS$##$tag,type_key const Key,type_value const Value);\
					type_value(_PL_ Reader_)(BOXC_KS$##$tag,type_key const Key);\
				}\
				Value;\
				const struct\
				{\
					type_key(_PL_ Search_)(BOXC_KS$##$tag,ADDRESS Index);\
					address(_PL_ Locate_)(BOXC_KS$##$tag,type_key const Key);\
				}\
				Index;\
			}\
			_PL_ _R_(KS$##$tag)=(GENERAL*)&(BoxC.KS.Key.Enroll_)
#endif
		};

		//BoxClip : Some Functions
		const struct
		{
			//BoxClip : Remove all keys.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Reset_)(boxc_ks _PL_ _R_ KeySet);
			//BoxClip : Get the current height of the internal search tree.
			address(_PL_ Height_)(BOXC_KS _PL_ _R_ KeySet);

			//BoxClip : Preserved for Future Usage
			ADDRESS xPreserved[2];
		};
	}
	KS;

	//BoxClip : Flag Set Functions
	const struct
	{
		//BoxClip : Creation and Deletion
		const struct
		{
			//BoxClip : Flag Set Memory Allocation - Deallocate with "BoxC.FS.Delete_"
			boxc_fs*(_PL_ Create_)(ADDRESS FlagsNumber);
			//BoxClip : Flag Set Memory Deallocation
			general(_PL_ Delete_)(boxc_fs *_PL_ _R_);
			//BoxClip : Flag Set Memory Occupation
			address(_PL_ Size_)(BOXC_FS _PL_ _R_ FlagSet);
			//BoxClip : Toggle a boolean of the selected flag.
			general(_PL_ Toggle_)(BOXC_FS _PL_ _R_ FlagSet,ADDRESS FlagSelect);

#if(Fold_(Auto))
#define BoxC_FS_Auto_(Auto,FlagsNumber)\
			auto MemC_Unit_\
			(\
				boxc_fs,Auto,\
					.Flag=(byte_08[((FlagsNumber)+7)>>3]){0},\
					.Number=(FlagsNumber)\
			)
#endif
		};

		//BoxClip : Functions for All Flags
		const struct
		{
			//BoxClip : Reset all flags to a value.
			//＊X value should be 0 or 1.
			general(_PL_ Reset_)(BOXC_FS _PL_ _R_ FlagSet,LOGICAL X);
			//BoxClip : Check all flags.
			//＊If all flags equal to the X value, then return 1, else return 0.
			logical(_PL_ Check_)(BOXC_FS _PL_ _R_ FlagSet,LOGICAL X);
		}
		All;

		//BoxClip : Read and Write
		const struct
		{
			//BoxClip : Write a state into the selected flag.
			//＊X value should be 0 or 1.
			general(_PL_ Writer_)(BOXC_FS _PL_ _R_ FlagSet,ADDRESS FlagSelect,LOGICAL X);
			//BoxClip : Read a boolean from the selected flag.
			//＊Return value is the stored boolean value.
			logical(_PL_ Reader_)(BOXC_FS _PL_ _R_ FlagSet,ADDRESS FlagSelect);
		};
	}
	FS;

	//BoxClip : Tree Functions
	const struct
	{
		//BoxClip : Creation and Deletion
		const struct
		{
			//BoxClip : Tree Creation - Delete with "BoxC.Tr.Delete_"
			//＊If the root is null, then required memory space will be allocated, else the capacity should be 0.
			boxc_tr*(_PL_ Create_)(boxc_tr _PL_ _R_ Root,ADDRESS Capacity);
			//BoxClip : Tree Deletion
			//＊If the tree is the deepest root, then the memory space will be deallocated, else the tree will point its root.
			general(_PL_ Delete_)(boxc_tr *_PL_ _R_);
			//BoxClip : Tree Memory Occupation of All Nodes
			address(_PL_ Size_)(BOXC_TR _PL_ _R_ Tree);
			//BoxClip : Tree Memory Occupation of the Current Node and its All Leaves
			address(_PL_ Used_)(BOXC_TR _PL_ _R_ Tree);
		};

		//BoxClip : Some Functions
		const struct
		{
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
		};

#if(Fold_(Generic))
#define BoxC_Tr_Generic_($tag,type)\
		xBoxC_Check_(type);\
		typedef union{boxc_tr*Core;struct{boxc_tr _PL_ Root,_PL_ Leaf,_PL_ Prev,_PL_ Next;ADDRESS Count,Total,Hidden;type Object;}_PL_ Wrap;}boxc_tr$##$tag;\
		typedef const boxc_tr$##$tag BOXC_TR$##$tag;\
		GENERAL _PL_ _R_(Tr$##$tag)=&(Tr$##$tag)
#endif
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
		general(_PL_ Delete_)(boxc_sw *_PL_ _R_);
		//BoxClip : Switch Memory Occupation
		address(_PL_ Size_)(BOXC_SW _PL_ _R_ Switch);

		//BoxClip : Switch Operations
		const struct
		{
			//BoxClip : Case Finding
			//＊Mode 0 : Naive Search
			//　Mode 1 : Binary Search
			//＊Return value is a corresponding index of the found case, or ~0 for the unknown case.
			address(_PL_ Find_)(BOXC_SW _PL_ _R_ Switch,GENERAL _PL_ Case,LOGICAL SearchMode);

#if(Fold_(Generic))
#define BoxC_Sw_Generic_($tag,type)\
			xBoxC_Check_(type);\
			typedef union{boxc_sw*Core;const struct{const struct{type const Item;ADDRESS Index;}_PL_ Case;ADDRESS Number;}_PL_ Wrap;}boxc_sw$##$tag;\
			typedef const boxc_sw$##$tag BOXC_SW$##$tag;\
			const struct{address(_PL_ Find_)(BOXC_SW$##$tag,type const Case,LOGICAL Mode);}_PL_ _R_(Sw$##$tag)=(GENERAL*)&(BoxC.Sw.Find_)
#endif
		};
	}
	Sw;

	//BoxClip : List Functions
	const struct
	{
		//BoxClip : Creation and Deletion
		const struct
		{
			//BoxClip : List Creation - Delete with "BoxC.Li.Delete_"
			boxc_li*(_PL_ Create_)(ADDRESS Capacity);
			//BoxClip : List Deletion
			general(_PL_ Delete_)(boxc_li *_PL_ _R_);
			//BoxClip : List Memory Occupation
			address(_PL_ Size_)(BOXC_LI _PL_ _R_ List);
			//BoxClip : Reverse the order of all items.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Reverse_)(BOXC_LI _PL_ _R_ List);

#if(Fold_(Auto))
#define BoxC_Li_Auto_(Auto,Capacity)\
			auto boxc_li _PL_(Auto)=(boxc_li*)((address[(Capacity)+2]){Capacity})
#endif
		};

		//BoxClip : Reset and Check
		const struct
		{
			//BoxClip : Desert all items.
			//＊Return value is 1 for success, 0 for failure.
			logical(_PL_ Reset_)(boxc_li _PL_ _R_ List);
			//BoxClip : Check the list.
			//＊Return value is 1 only if the list has no null object, otherwise 0.
			logical(_PL_ Check_)(BOXC_LI _PL_ _R_ List);

			//BoxClip : Preserved for Future Usage
			ADDRESS xPreserved[2];
		};

		//BoxClip : List Operations
		const struct
		{
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

			//BoxClip : Functions for List Operations
			//＊Return value is 1 for success, 0 for failure.
			const struct
			{
				//BoxClip : Copy some items.
				logical(_PL_ Copy_)(boxc_li _PL_ _R_ TargetList,BOXC_LI _PL_ _R_ SourceList,ADDRESS TargetOffset,ADDRESS SourceOffset,ADDRESS CopyNumber);
				//BoxClip : Filter all items.
				//＊The target list's capacity should not be less than the source list's count.
				//＊Original items in the target list will be just over-written.
				logical(_PL_ Filter_)(boxc_li _PL_ _R_ TargetList,BOXC_LI _PL_ _R_ SourceList,logical(_PL_ Filter_)(GENERAL _PL_ _R_ SourceItem,general _PL_ _R_ Option),general _PL_ _R_ Option);
			}
			Do;

#if(Fold_(Generic))
#define BoxC_Li_Generic_($tag,type)\
			xBoxC_Check_(type);\
			typedef union{boxc_li*Core;const struct{ADDRESS Capacity,Count;type Item[];}_PL_ Wrap;}boxc_li$##$tag;\
			typedef const boxc_li$##$tag BOXC_LI$##$tag;\
			const struct\
			{\
				const struct\
				{\
					logical\
						(_PL_ Insert_)(BOXC_LI$##$tag,type const Item),\
						(_PL_ Desert_)(BOXC_LI$##$tag);\
				}\
				Tip;\
				const struct\
				{\
					logical\
						(_PL_ Insert_)(BOXC_LI$##$tag,ADDRESS Ofs,type const Item),\
						(_PL_ Desert_)(BOXC_LI$##$tag,ADDRESS Ofs);\
				}\
				One;\
				const struct\
				{\
					logical\
						(_PL_ Insert_)(BOXC_LI$##$tag,ADDRESS Ofs,ADDRESS Num,...),\
						(_PL_ Desert_)(BOXC_LI$##$tag,ADDRESS Ofs,ADDRESS Num);\
				}\
				Lot;\
				const struct\
				{\
					logical\
						(_PL_ Copy_)(BOXC_LI$##$tag TList,BOXC_LI$##$tag SList,ADDRESS TOfs,ADDRESS SOfs,ADDRESS Num),\
						(_PL_ Filter_)(BOXC_LI$##$tag TList,BOXC_LI$##$tag SList,logical(_PL_ Filt_)(GENERAL _PL_ _R_ Item,general _PL_ _R_ Opt),general _PL_ _R_ Opt);\
				}\
				Do;\
			}\
			_PL_ _R_(Li$##$tag)=(GENERAL*)&(BoxC.Li.Tip.Insert_)
#endif
		};

#if(Fold_(Foreach: Iterate for each object.))
#define BoxC_Li_Foreach_(List,type,Each)\
		for\
		(\
			address Conc_(xBoxCTrip,__LINE__)=\
			(\
				MemC_Assert_(sizeof(address)==sizeof(type)),\
				assert((List)&&(1)),\
				(0)\
			);\
			Conc_(xBoxCTrip,__LINE__)<((List)->Count);\
			Conc_(xBoxCTrip,__LINE__)++\
		)\
		MemC_Temp_(type,const(Each)=(List)->Item[Conc_(xBoxCTrip,__LINE__)])
#endif
	}
	Li;

#if(Fold_(Generic Type Checker))
#define xBoxC_Check_(type)\
	static_assert\
	(\
		(sizeof(type)==sizeof(address))&&\
		((address)((type)(FULL))==(address)(FULL)),\
		"invalid type error (" Meta_(type) ")"\
	)
#endif
}
BOXCASE;

//BoxClip : Library Case Object
extern BOXCASE BoxC,*BoxC_(general);
#endif
#endif
