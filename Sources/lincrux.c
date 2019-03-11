#include "linclip.h"

#ifdef _SRC_LINCRUX

#if(T()==D())
#define TYPE DATA
#define type data
#elif(T()==I())
#define TYPE INTE
#define type inte
#elif(T()==R())
#define TYPE REAL
#define type real
#else
#error The macro "T" is defined out of this context.
#endif

#ifdef _LinC_Operation_0_
general LinC_Oper_(LinC_Op_,0,LinC_TXX_(T,XX))(LinC_Type_(type,XX) *_R_ Line,LinC_Type_(TYPE,XX) Start,LinC_Type_(TYPE,XX) Step,DATA_32 Length)
{
	if(Length)
	{
		DATA_32 Last=Length-1;
		LinC_Type_(TYPE,XX) *End=Line+(Last&0xFFFFFFF8);

		for(Line[0]=Start;Line<End;Line+=8)
		{
			Line[1]=LinC_Op_(Line[0],Step);
			Line[2]=LinC_Op_(Line[1],Step);
			Line[3]=LinC_Op_(Line[2],Step);
			Line[4]=LinC_Op_(Line[3],Step);
			Line[5]=LinC_Op_(Line[4],Step);
			Line[6]=LinC_Op_(Line[5],Step);
			Line[7]=LinC_Op_(Line[6],Step);
			Line[8]=LinC_Op_(Line[7],Step);
		}
		for(End+=(Last&0x00000007);Line<End;Line++)
			Line[1]=LinC_Op_(Line[0],Step);
	}
}
#endif

#ifdef _LinC_Operation_1_
general LinC_Oper_(LinC_Op_,1,LinC_TXX_(T,XX))(LinC_Type_(type,XX) *LineC,LinC_Type_(TYPE,XX) *LineA,LinC_Type_(TYPE,XX) Value,DATA_32 Length)
{
	LinC_Type_(TYPE,XX) *End=LineA+(Length&0xFFFFFFF8);

	for(;LineA<End;LineA+=8,LineC+=8)
	{
		LineC[0]=LinC_Op_(LineA[0],Value);
		LineC[1]=LinC_Op_(LineA[1],Value);
		LineC[2]=LinC_Op_(LineA[2],Value);
		LineC[3]=LinC_Op_(LineA[3],Value);
		LineC[4]=LinC_Op_(LineA[4],Value);
		LineC[5]=LinC_Op_(LineA[5],Value);
		LineC[6]=LinC_Op_(LineA[6],Value);
		LineC[7]=LinC_Op_(LineA[7],Value);
	}
	for(End+=(Length&0x00000007);LineA<End;LineA++,LineC++)
		LineC[0]=LinC_Op_(LineA[0],Value);
}
#endif

#ifdef _LinC_Operation_2_
general LinC_Oper_(LinC_Op_,2,LinC_TXX_(T,XX))(LinC_Type_(type,XX) *LineC,LinC_Type_(TYPE,XX) *LineA,LinC_Type_(TYPE,XX) *LineB,DATA_32 Length)
{
	LinC_Type_(TYPE,XX) *End=LineA+(Length&0xFFFFFFF8);

	for(;LineA<End;LineA+=8,LineB+=8,LineC+=8)
	{
		LineC[0]=LinC_Op_(LineA[0],LineB[0]);
		LineC[1]=LinC_Op_(LineA[1],LineB[1]);
		LineC[2]=LinC_Op_(LineA[2],LineB[2]);
		LineC[3]=LinC_Op_(LineA[3],LineB[3]);
		LineC[4]=LinC_Op_(LineA[4],LineB[4]);
		LineC[5]=LinC_Op_(LineA[5],LineB[5]);
		LineC[6]=LinC_Op_(LineA[6],LineB[6]);
		LineC[7]=LinC_Op_(LineA[7],LineB[7]);
	}
	for(End+=(Length&0x00000007);LineA<End;LineA++,LineB++,LineC++)
		LineC[0]=LinC_Op_(LineA[0],LineB[0]);
}
#endif

#ifdef _LinC_Summation_
LinC_Type_(type,XX) LinC_Func_(LinC_Sum_1_,LinC_TXX_(T,XX))(LinC_Type_(TYPE,XX) *_R_ Line,DATA_32 Length)
{
	LinC_Type_(TYPE,XX) *End=Line+(Length&0xFFFFFFF8);
	LinC_Type_(type,XX) Sum;

	for(Acs_(LinC_Type_(data,XX),Sum)=0;Line<End;Line+=8)
	{
		Sum+=Line[0];
		Sum+=Line[1];
		Sum+=Line[2];
		Sum+=Line[3];
		Sum+=Line[4];
		Sum+=Line[5];
		Sum+=Line[6];
		Sum+=Line[7];
	}
	for(End+=(Length&0x00000007);Line<End;Line++)
		Sum+=Line[0];

	return Sum;
}
LinC_Type_(type,XX) LinC_Func_(LinC_Dot_2_,LinC_TXX_(T,XX))(LinC_Type_(TYPE,XX) *LineA,LinC_Type_(TYPE,XX) *LineB,DATA_32 Length)
{
	LinC_Type_(TYPE,XX) *End=LineA+(Length&0xFFFFFFF8);
	LinC_Type_(type,XX) Sum;

	for(Acs_(LinC_Type_(data,XX),Sum)=0;LineA<End;LineA+=8,LineB+=8)
	{
		Sum+=(LineA[0]*LineB[0]);
		Sum+=(LineA[1]*LineB[1]);
		Sum+=(LineA[2]*LineB[2]);
		Sum+=(LineA[3]*LineB[3]);
		Sum+=(LineA[4]*LineB[4]);
		Sum+=(LineA[5]*LineB[5]);
		Sum+=(LineA[6]*LineB[6]);
		Sum+=(LineA[7]*LineB[7]);
	}
	for(End+=(Length&0x00000007);LineA<End;LineA++,LineB++)
		Sum+=(LineA[0]*LineB[0]);

	return Sum;
}
#endif

#ifdef _LinC_Min_Max_
data_32 LinC_Oper_(LinC_Op_,1,LinC_TXX_(T,XX))(LinC_Type_(TYPE,XX) _PL_ Line,DATA_32 Length)
{
	data_32 Index;

	if(Length)
	{
		LinC_Type_(TYPE,XX) _PL_ End=Line+Length;
		LinC_Type_(TYPE,XX) *_R_ Ptr=Line;
		LinC_Type_(TYPE,XX) *Here=Ptr;
		LinC_Type_(type,XX) Value=*Ptr;

		for(Ptr++;Ptr<End;Ptr++)
			if(LinC_Op_(Value,*Ptr))
			{
				Value=*Ptr;
				Here=Ptr;
			}
		Index=(data_32)(Here-Line);
	}
	else
		Index=0;

	return Index;
}
#endif

#ifdef _LinC_Sorting_
general LinC_Func_(LinC_Map_1_,LinC_TXX_(T,XX))(LinC_Type_(type,XX) *_R_ Line,DATA_32 *_R_ Index,LinC_Type_(TYPE,XX) _PL_ Table,DATA_32 Length)
{
	DATA_32 *End=Index+(Length&0xFFFFFFF8);

	for(;Index<End;Index+=8,Line+=8)
	{
		Line[0]=Table[Index[0]];
		Line[1]=Table[Index[1]];
		Line[2]=Table[Index[2]];
		Line[3]=Table[Index[3]];
		Line[4]=Table[Index[4]];
		Line[5]=Table[Index[5]];
		Line[6]=Table[Index[6]];
		Line[7]=Table[Index[7]];
	}
	for(End+=(Length&0x00000007);Index<End;Index++,Line++)
		Line[0]=Table[Index[0]];
}

static inline general LinC_Func_(_LinC_Swap_,LinC_TXX_(T,XX))(LinC_Type_(type,XX) _PL_ A,INTEGER _PL_ T)
{
	LinC_Type_(TYPE,XX) Temp=A[T[1]];

	A[0]=A[T[0]];
	A[1]=Temp;
}
static LinC_Type_(type,XX) *LinC_Func_(_LinC_Radix_,LinC_TXX_(T,XX))(LinC_Type_(type,XX) *_R_ ValueFirst,data_32 *_R_ IndexFirst,LinC_Type_(TYPE,XX) *_R_ ValueMess,DATA_32 *_R_ IndexMess,DATA_32 Length,BOOLEAN Mode,LinC_Type_(TYPE,XX) Scan)
{
	LinC_Type_(type,XX) *_R_ ValueLast=ValueFirst+Length;
	data_32 *_R_ IndexLast=IndexFirst+Length;

	if(Mode)
		for(;ValueFirst<ValueLast;ValueMess++,IndexMess++)
			if((*ValueMess)&Scan)
			{
				(*ValueFirst)=(*ValueMess);
				ValueFirst++;

				(*IndexFirst)=(*IndexMess);
				IndexFirst++;
			}
			else
			{
				ValueLast--;
				(*ValueLast)=(*ValueMess);

				IndexLast--;
				(*IndexLast)=(*IndexMess);
			}
	else
		for(;ValueFirst<ValueLast;ValueMess++,IndexMess++)
			if((*ValueMess)&Scan)
			{
				ValueLast--;
				(*ValueLast)=(*ValueMess);

				IndexLast--;
				(*IndexLast)=(*IndexMess);
			}
			else
			{
				(*ValueFirst)=(*ValueMess);
				ValueFirst++;

				(*IndexFirst)=(*IndexMess);
				IndexFirst++;
			}

	return ValueFirst;
}
static general LinC_Func_(_LinC_Sort_2_Here_,LinC_TXX_(T,XX))(LinC_Type_(type,XX) _PL_ ValueA,data_32 _PL_ IndexA,BOOLEAN Mode)
{
	integer T[2];

	if(ValueA[0]<ValueA[1])
	{
		T[0]=Mode&1;
		T[1]=T[0]^1;
	}
	else
	{
		T[1]=Mode&1;
		T[0]=T[1]^1;
	}
	{
		LinC_Func_(_LinC_Swap_,LinC_TXX_(T,XX))(ValueA,T);
		_LinC_Swap_D32_(IndexA,T);
	}
}
static general LinC_Func_(_LinC_Sort_2_Move_,LinC_TXX_(T,XX))(LinC_Type_(type,XX) _PL_ ValueA,LinC_Type_(type,XX) _PL_ ValueB,data_32 _PL_ IndexA,data_32 _PL_ IndexB,BOOLEAN Mode)
{
	integer T[2];

	if(ValueA[0]<ValueA[1])
	{
		T[0]=Mode&1;
		T[1]=T[0]^1;
	}
	else
	{
		T[1]=Mode&1;
		T[0]=T[1]^1;
	}
	{
		ValueB[0]=ValueA[T[0]];
		ValueB[1]=ValueA[T[1]];

		IndexB[0]=IndexA[T[0]];
		IndexB[1]=IndexA[T[1]];
	}
}
static general LinC_Func_(_LinC_Recur_,LinC_TXX_(T,XX))(LinC_Type_(type,XX) *ValueSource,data_32 *IndexSource,LinC_Type_(type,XX) *ValueTarget,data_32 *IndexTarget,DATA_32 Length,BOOLEAN Mode,integer Bits)
{
	data_32 Offset=(data_32)(LinC_Func_(_LinC_Radix_,LinC_TXX_(T,XX))(ValueTarget,IndexTarget,ValueSource,IndexSource,Length,Mode,((LinC_Type_(type,XX))1)<<((LinC_Type_(type,XX))Bits))-ValueTarget);

	if(Bits)
	{
		Bits--;
		if(Bits&1)
			switch(Offset)
			{
			default:
				LinC_Func_(_LinC_Recur_,LinC_TXX_(T,XX))(ValueTarget,IndexTarget,ValueSource,IndexSource,Offset,Mode,Bits);
				goto JUMP_A;
			case 2:
				LinC_Func_(_LinC_Sort_2_Here_,LinC_TXX_(T,XX))(ValueTarget,IndexTarget,Mode);
			case 1:
JUMP_A:
				ValueSource+=Offset;
				IndexSource+=Offset;
				ValueTarget+=Offset;
				IndexTarget+=Offset;
			case 0:
				Offset=Length-Offset;
				switch(Offset)
				{
				default:
					LinC_Func_(_LinC_Recur_,LinC_TXX_(T,XX))(ValueTarget,IndexTarget,ValueSource,IndexSource,Offset,Mode,Bits);
					break;
				case 2:
					LinC_Func_(_LinC_Sort_2_Here_,LinC_TXX_(T,XX))(ValueTarget,IndexTarget,Mode);
					break;
				case 1:
				case 0:;
				}
			}
		else
			switch(Offset)
			{
			default:
				LinC_Func_(_LinC_Recur_,LinC_TXX_(T,XX))(ValueTarget,IndexTarget,ValueSource,IndexSource,Offset,Mode,Bits);
				goto JUMP_B;
			case 2:
				LinC_Func_(_LinC_Sort_2_Move_,LinC_TXX_(T,XX))(ValueTarget,ValueSource,IndexTarget,IndexSource,Mode);
				goto JUMP_B;
			case 1:
				ValueSource[0]=ValueTarget[0];
				IndexSource[0]=IndexTarget[0];
JUMP_B:
				ValueSource+=Offset;
				IndexSource+=Offset;
				ValueTarget+=Offset;
				IndexTarget+=Offset;
			case 0:
				Offset=Length-Offset;
				switch(Offset)
				{
				default:
					LinC_Func_(_LinC_Recur_,LinC_TXX_(T,XX))(ValueTarget,IndexTarget,ValueSource,IndexSource,Offset,Mode,Bits);
					break;
				case 2:
					LinC_Func_(_LinC_Sort_2_Move_,LinC_TXX_(T,XX))(ValueTarget,ValueSource,IndexTarget,IndexSource,Mode);
					break;
				case 1:
					ValueSource[0]=ValueTarget[0];
					IndexSource[0]=IndexTarget[0];
				case 0:;
				}
			}
	}
}
#endif

#undef type
#undef TYPE

#else

#ifdef T
#error The macro "T" is already defined.
#else

#ifdef XX
#error The macro "XX" is already defined.
#else

#ifdef TYPE
#error The macro "TYPE" is already defined.
#else

#ifdef type
#error The macro "type" is already defined.
#else

#ifdef D
#error The macro "D" is already defined.
#else
#define D() (0)
#endif

#ifdef I
#error The macro "I" is already defined.
#else
#define I() (-1)
#endif

#ifdef R
#error The macro "R" is already defined.
#else
#define R() (+1)
#endif

#define _SRC_LINCRUX

#ifdef _LinC_Data_
#define T D
#define XX 08
#include "lincrux.c"
#undef XX
#define XX 16
#include "lincrux.c"
#undef XX
#define XX 32
#include "lincrux.c"
#undef XX
#define XX 64
#include "lincrux.c"
#undef XX
#undef T
#endif

#ifdef _LinC_Inte_
#define T I
#define XX 08
#include "lincrux.c"
#undef XX
#define XX 16
#include "lincrux.c"
#undef XX
#define XX 32
#include "lincrux.c"
#undef XX
#define XX 64
#include "lincrux.c"
#undef XX
#undef T
#endif

#ifdef _LinC_Real_
#define T R
#define XX 32
#include "lincrux.c"
#undef XX
#define XX 64
#include "lincrux.c"
#undef XX
#undef T
#endif

#undef _SRC_LINCRUX

#undef R
#undef I
#undef D
#endif
#endif
#endif
#endif
#endif
