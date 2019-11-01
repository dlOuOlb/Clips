#ifdef _INC_LINCLIP
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
#endif

#ifdef _LinC_Operation_0_
#ifndef __OPENCL_VERSION__
_LINC_ general LinC_Oper_(LinC_Op_,0,TXX)(type_xx *_R_ Line,TYPE_XX Start,TYPE_XX Step,ADDRESS Length)
{
	if(Length)
	{
		ADDRESS Last=Length-1;
		TYPE_XX *End=Line;

		for(End+=(Last&BitC.Const.Mask.Safe[3]),Line[0]=Start;Line<End;Line+=8)
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
		for(End+=(Last&BitC.Const.Mask.Rest[3]);Line<End;Line++)
			Line[1]=LinC_Op_(Line[0],Step);
	}
	else;

	return;
}
#endif
#endif

#ifdef _LinC_Operation_1_
#ifdef __OPENCL_VERSION__
_K_ LinC_Oper_(LinC_Op_,1,TXX)(_G_ type_xx _PL_ CData,_G_ TYPE_XX _PL_ AData,_P_ OCLCLIP CStart,_P_ OCLCLIP AStart,_P_ OCLCLIP Amount,_P_ OCLCLIP CShape,_P_ OCLCLIP AShape,_P_ TYPE_XX Value)
{
	_P_ OCLCLIP Select=Work_From_(Amount);

	CData[Work_Into_(Select,CStart,CShape)]=LinC_Op_(AData[Work_Into_(Select,AStart,AShape)],Value);

	return;
}
#else
_LINC_ general LinC_Oper_(LinC_Op_,1,TXX)(type_xx *LineC,TYPE_XX *LineA,TYPE_XX Value,ADDRESS Length)
{
	TYPE_XX *End=LineA;

	for(End+=(Length&BitC.Const.Mask.Safe[3]);LineA<End;LineA+=8,LineC+=8)
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
	for(End+=(Length&BitC.Const.Mask.Rest[3]);LineA<End;LineA++,LineC++)
		LineC[0]=LinC_Op_(LineA[0],Value);

	return;
}
#endif
#endif

#ifdef _LinC_Operation_2_
#ifdef __OPENCL_VERSION__
_K_ LinC_Oper_(LinC_Op_,2,TXX)(_G_ type_xx _PL_ CData,_G_ TYPE_XX _PL_ AData,_G_ TYPE_XX _PL_ BData,_P_ OCLCLIP CStart,_P_ OCLCLIP AStart,_P_ OCLCLIP BStart,_P_ OCLCLIP Amount,_P_ OCLCLIP CShape,_P_ OCLCLIP AShape,_P_ OCLCLIP BShape)
{
	_P_ OCLCLIP Select=Work_From_(Amount);

	CData[Work_Into_(Select,CStart,CShape)]=LinC_Op_(AData[Work_Into_(Select,AStart,AShape)],BData[Work_Into_(Select,BStart,BShape)]);

	return;
}
#else
_LINC_ general LinC_Oper_(LinC_Op_,2,TXX)(type_xx *LineC,TYPE_XX *LineA,TYPE_XX *LineB,ADDRESS Length)
{
	TYPE_XX *End=LineA;

	for(End+=(Length&BitC.Const.Mask.Safe[3]);LineA<End;LineA+=8,LineB+=8,LineC+=8)
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
	for(End+=(Length&BitC.Const.Mask.Rest[3]);LineA<End;LineA++,LineB++,LineC++)
		LineC[0]=LinC_Op_(LineA[0],LineB[0]);

	return;
}
#endif
#endif

#ifdef _LinC_Summation_
#ifdef __OPENCL_VERSION__
_K_ LinC_Func_(LinC_Sum_1_,TXX)(_G_ type_xx _PL_ CData,_G_ TYPE_XX _PL_ AData,_P_ OCLCLIP CStart,_P_ OCLCLIP AStart,_P_ OCLCLIP Amount,_P_ OCLCLIP CShape,_P_ OCLCLIP AShape,_P_ OCLC_PA Axis,_L_ type_xx _PL_ LData)
{
	_P_ ADDRESS LSize=Work_Size_L_(0);
	_P_ ADDRESS LStart=Work_Here_L_(0);
	_P_ oclclip LSelect=LinC_From_(Amount,Axis);
	_P_ type_xx Value=0;

	{
		_P_ address AJump=LSize;

		for(_P_ oclc_pa Idx=Axis+1;Idx<OCLCPinAxes;Idx++)
			AJump*=AShape.S[Idx];

		LSelect.S[Axis]+=LStart;
		for(_P_ address LIndex=LStart,AIndex=Work_Into_(LSelect,AStart,AShape);LIndex<Amount.S[Axis];LIndex+=LSize,AIndex+=AJump)
			Value+=AData[AIndex];
		LSelect.S[Axis]-=LStart;
	}
	for(_P_ address LJump=LSize>>1;LJump;LJump>>=1)
	{
		Work_Wait_L_();
		LData[LStart]=Value;
		Work_Wait_L_();
		Value=LData[LStart]+LData[LStart^LJump];
	}
	if(LStart);
	else
		CData[Work_Into_(LSelect,CStart,CShape)]=Value;

	return;
}
_K_ LinC_Func_(LinC_Dot_2_,TXX)(_G_ type_xx _PL_ CData,_G_ TYPE_XX _PL_ AData,_G_ TYPE_XX _PL_ BData,_P_ OCLCLIP CStart,_P_ OCLCLIP AStart,_P_ OCLCLIP BStart,_P_ OCLCLIP Amount,_P_ OCLCLIP CShape,_P_ OCLCLIP AShape,_P_ OCLCLIP BShape,_P_ OCLC_PA Axis,_L_ type_xx _PL_ LData)
{
	_P_ ADDRESS LSize=Work_Size_L_(0);
	_P_ ADDRESS LStart=Work_Here_L_(0);
	_P_ oclclip LSelect=LinC_From_(Amount,Axis);
	_P_ type_xx Value=0;

	{
		_P_ address AJump=LSize;
		_P_ address BJump=LSize;

		for(_P_ oclc_pa Idx=Axis+1;Idx<OCLCPinAxes;Idx++)
		{
			AJump*=AShape.S[Idx];
			BJump*=BShape.S[Idx];
		}

		LSelect.S[Axis]+=LStart;
		for(_P_ address LIndex=LStart,AIndex=Work_Into_(LSelect,AStart,AShape),BIndex=Work_Into_(LSelect,BStart,BShape);LIndex<Amount.S[Axis];LIndex+=LSize,AIndex+=AJump,BIndex+=BJump)
			Value+=AData[AIndex]*BData[BIndex];
		LSelect.S[Axis]-=LStart;
	}
	for(_P_ address LJump=LSize>>1;LJump;LJump>>=1)
	{
		Work_Wait_L_();
		LData[LStart]=Value;
		Work_Wait_L_();
		Value=LData[LStart]+LData[LStart^LJump];
	}
	if(LStart);
	else
		CData[Work_Into_(LSelect,CStart,CShape)]=Value;

	return;
}
#else
_LINC_ type_xx LinC_Func_(LinC_Sum_1_,TXX)(TYPE_XX *_R_ Line,ADDRESS Length)
{
	TYPE_XX *End=Line;
	type_xx Temp[8]={0};

	for(End+=(Length&BitC.Const.Mask.Safe[3]);Line<End;Line+=8)
	{
		Temp[0]+=Line[0];
		Temp[1]+=Line[1];
		Temp[2]+=Line[2];
		Temp[3]+=Line[3];
		Temp[4]+=Line[4];
		Temp[5]+=Line[5];
		Temp[6]+=Line[6];
		Temp[7]+=Line[7];
	}
	for(End+=(Length&BitC.Const.Mask.Rest[3]);Line<End;Line++)
		Temp[0]+=Line[0];
	{
		Temp[0]+=Temp[4];
		Temp[1]+=Temp[5];
		Temp[2]+=Temp[6];
		Temp[3]+=Temp[7];

		Temp[0]+=Temp[2];
		Temp[1]+=Temp[3];

		Temp[0]+=Temp[1];
	}

	return Temp[0];
}
_LINC_ type_xx LinC_Func_(LinC_Dot_2_,TXX)(TYPE_XX *LineA,TYPE_XX *LineB,ADDRESS Length)
{
	TYPE_XX *End=LineA;
	type_xx Temp[8]={0};

	for(End+=(Length&BitC.Const.Mask.Safe[3]);LineA<End;LineA+=8,LineB+=8)
	{
		Temp[0]+=(LineA[0]*LineB[0]);
		Temp[1]+=(LineA[1]*LineB[1]);
		Temp[2]+=(LineA[2]*LineB[2]);
		Temp[3]+=(LineA[3]*LineB[3]);
		Temp[4]+=(LineA[4]*LineB[4]);
		Temp[5]+=(LineA[5]*LineB[5]);
		Temp[6]+=(LineA[6]*LineB[6]);
		Temp[7]+=(LineA[7]*LineB[7]);
	}
	for(End+=(Length&BitC.Const.Mask.Rest[3]);LineA<End;LineA++,LineB++)
		Temp[0]+=(LineA[0]*LineB[0]);
	{
		Temp[0]+=Temp[4];
		Temp[1]+=Temp[5];
		Temp[2]+=Temp[6];
		Temp[3]+=Temp[7];

		Temp[0]+=Temp[2];
		Temp[1]+=Temp[3];

		Temp[0]+=Temp[1];
	}

	return Temp[0];
}
#endif
#endif

#ifdef _LinC_Min_Max_
#ifdef __OPENCL_VERSION__
_K_ LinC_Oper_(LinC_Op_,1,TXX)(_G_ address _PL_ IData,_G_ TYPE_XX _PL_ AData,_P_ OCLCLIP IStart,_P_ OCLCLIP AStart,_P_ OCLCLIP Amount,_P_ OCLCLIP IShape,_P_ OCLCLIP AShape,_P_ OCLC_PA Axis,_L_ general _PL_ LData)
{
	_P_ ADDRESS LSize=Work_Size_L_(0);
	_P_ ADDRESS LStart=Work_Here_L_(0);
	_P_ oclclip LSelect=LinC_From_(Amount,Axis);
	_P_ type_xx Value=AData[Work_Into_(LSelect,AStart,AShape)];
	_P_ address Index=0;

	{
		_P_ address AJump=LSize;

		for(_P_ oclc_pa Idx=Axis+1;Idx<OCLCPinAxes;Idx++)
			AJump*=AShape.S[Idx];

		LSelect.S[Axis]+=LStart;
		for(_P_ address Idx=LStart,AIndex=Work_Into_(LSelect,AStart,AShape);Idx<Amount.S[Axis];Idx+=LSize,AIndex+=AJump)
		{
			_P_ TYPE_XX Thing=AData[AIndex];

			if(LinC_Op_(Value,Thing))
			{
				Value=Thing;
				Index=Idx;
			}
			else;
		}
		LSelect.S[Axis]-=LStart;
	}
	{
		_L_ address _PL_ LIndex=LData;
		_L_ type_xx _PL_ LValue=(_L_ type_xx*)(LIndex+LSize);
		_P_ address LThere;
		_P_ type_xx LThing;

		for(_P_ address LJump=LSize>>1;LJump;LJump>>=1)
		{
			LValue[LStart]=Value;
			LIndex[LStart]=Index;
			Work_Wait_L_();

			LThere=LStart^LJump;
			LThing=LValue[LThere];
			LThere=LIndex[LThere];

			if(LinC_Op_(Value,LThing))
			{
				Value=LThing;
				Index=LThere;
			}
			else;
			Work_Wait_L_();
		}
	}
	if(LStart);
	else
		IData[Work_Into_(LSelect,IStart,IShape)]=Index;

	return;
}
#else
_LINC_ address LinC_Oper_(LinC_Op_,1,TXX)(TYPE_XX _PL_ Line,ADDRESS Length)
{
	address Index;

	if(Length)
	{
		TYPE_XX _PL_ End=Line+Length;
		TYPE_XX *_R_ Ptr=Line;
		TYPE_XX *Here=Ptr;
		type_xx Value=*Ptr;

		for(Ptr++;Ptr<End;Ptr++)
			if(LinC_Op_(Value,*Ptr))
			{
				Value=*Ptr;
				Here=Ptr;
			}
			else;
		Index=Here-Line;
	}
	else
		Index=0;

	return Index;
}
#endif
#endif

#ifdef _LinC_Mapping_
#ifdef __OPENCL_VERSION__
_K_ LinC_Func_(LinC_Map_1_,TXX)(_G_ type_xx _PL_ CData,_G_ ADDRESS _PL_ IData,_G_ TYPE_XX _PL_ AData,_P_ OCLCLIP CStart,_P_ OCLCLIP IStart,_P_ OCLCLIP AStart,_P_ oclclip Amount,_P_ OCLCLIP CShape,_P_ OCLCLIP IShape,_P_ OCLCLIP AShape,_P_ OCLC_PA Axis)
{
	_P_ ADDRESS Length=Amount.S[Axis];Amount.S[Axis]=1;
	_P_ oclclip Select=Work_From_(Amount);
	_P_ ADDRESS Index=IData[Work_Into_(Select,IStart,IShape)];Select.S[Axis]+=Index;
	_P_ TYPE_XX Value=(Index<Length)?(AData[Work_Into_(Select,AStart,AShape)]):(~0);Select.S[Axis]-=Index;

	CData[Work_Into_(Select,CStart,CShape)]=Value;

	return;
}
#else
_LINC_ general LinC_Func_(LinC_Map_1_,TXX)(type_xx *_R_ Line,ADDRESS *_R_ Index,TYPE_XX _PL_ Table,ADDRESS Length)
{
	ADDRESS *End=Index;

	for(End+=(Length&BitC.Const.Mask.Safe[3]);Index<End;Index+=8,Line+=8)
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
	for(End+=(Length&BitC.Const.Mask.Rest[3]);Index<End;Index++,Line++)
		Line[0]=Table[Index[0]];

	return;
}

static general LinC_Func_(_LinC_Swap_,TXX)(type_xx _PL_ _R_ A)
{
	TYPE_XX Temp=A[0];

	A[0]=A[1];
	A[1]=Temp;

	return;
}
static type_xx *LinC_Func_(_LinC_Radix_M0_,TXX)(type_xx *_R_ ValueFirst,address *_R_ IndexFirst,TYPE_XX *_R_ ValueMess,ADDRESS *_R_ IndexMess,ADDRESS Length,TYPE_XX Scan)
{
	type_xx *_R_ ValueLast=ValueFirst+Length;
	address *_R_ IndexLast=IndexFirst+Length;

	for(;ValueFirst<ValueLast;ValueMess++,IndexMess++)
		if((*ValueMess)&Scan)
		{
			*(--ValueLast)=*ValueMess;
			*(--IndexLast)=*IndexMess;
		}
		else
		{
			*(ValueFirst++)=*ValueMess;
			*(IndexFirst++)=*IndexMess;
		}

	return ValueFirst;
}
static type_xx *LinC_Func_(_LinC_Radix_M1_,TXX)(type_xx *_R_ ValueFirst,address *_R_ IndexFirst,TYPE_XX *_R_ ValueMess,ADDRESS *_R_ IndexMess,ADDRESS Length,TYPE_XX Scan)
{
	type_xx *_R_ ValueLast=ValueFirst+Length;
	address *_R_ IndexLast=IndexFirst+Length;

	for(;ValueFirst<ValueLast;ValueMess++,IndexMess++)
		if((*ValueMess)&Scan)
		{
			*(ValueFirst++)=*ValueMess;
			*(IndexFirst++)=*IndexMess;
		}
		else
		{
			*(--ValueLast)=*ValueMess;
			*(--IndexLast)=*IndexMess;
		}

	return ValueFirst;
}
static type_xx *LinC_Func_(_LinC_Radix_Lite_M0_,TXX)(type_xx *_R_ ValueFirst,TYPE_XX *_R_ ValueMess,ADDRESS Length,TYPE_XX Scan)
{
	type_xx *_R_ ValueLast=ValueFirst+Length;

	for(;ValueFirst<ValueLast;ValueMess++)
		if((*ValueMess)&Scan)
			*(--ValueLast)=*ValueMess;
		else
			*(ValueFirst++)=*ValueMess;

	return ValueFirst;
}
static type_xx *LinC_Func_(_LinC_Radix_Lite_M1_,TXX)(type_xx *_R_ ValueFirst,TYPE_XX *_R_ ValueMess,ADDRESS Length,TYPE_XX Scan)
{
	type_xx *_R_ ValueLast=ValueFirst+Length;

	for(;ValueFirst<ValueLast;ValueMess++)
		if((*ValueMess)&Scan)
			*(ValueFirst++)=*ValueMess;
		else
			*(--ValueLast)=*ValueMess;

	return ValueFirst;
}
static general LinC_Func_(_LinC_Sort_2_Here_M0_,TXX)(type_xx _PL_ _R_ ValueA,address _PL_ _R_ IndexA)
{
	if(ValueA[0]<ValueA[1]);
	else
	{
		LinC_Func_(_LinC_Swap_,TXX)(ValueA);
		_LinC_Swap_Address_(IndexA);
	}

	return;
}
static general LinC_Func_(_LinC_Sort_2_Here_M1_,TXX)(type_xx _PL_ _R_ ValueA,address _PL_ _R_ IndexA)
{
	if(ValueA[0]<ValueA[1])
	{
		LinC_Func_(_LinC_Swap_,TXX)(ValueA);
		_LinC_Swap_Address_(IndexA);
	}
	else;

	return;
}
static general LinC_Func_(_LinC_Sort_2_Here_Lite_M0_,TXX)(type_xx _PL_ _R_ ValueA)
{
	if(ValueA[0]<ValueA[1]);
	else
		LinC_Func_(_LinC_Swap_,TXX)(ValueA);

	return;
}
static general LinC_Func_(_LinC_Sort_2_Here_Lite_M1_,TXX)(type_xx _PL_ _R_ ValueA)
{
	if(ValueA[0]<ValueA[1])
		LinC_Func_(_LinC_Swap_,TXX)(ValueA);
	else;

	return;
}
static general LinC_Func_(_LinC_Sort_2_Move_M0_,TXX)(type_xx _PL_ _R_ ValueA,type_xx _PL_ _R_ ValueB,address _PL_ _R_ IndexA,address _PL_ _R_ IndexB)
{
	if(ValueA[0]<ValueA[1])
	{
		ValueB[0]=ValueA[0];
		ValueB[1]=ValueA[1];

		IndexB[0]=IndexA[0];
		IndexB[1]=IndexA[1];
	}
	else
	{
		ValueB[0]=ValueA[1];
		ValueB[1]=ValueA[0];

		IndexB[0]=IndexA[1];
		IndexB[1]=IndexA[0];
	}

	return;
}
static general LinC_Func_(_LinC_Sort_2_Move_M1_,TXX)(type_xx _PL_ _R_ ValueA,type_xx _PL_ _R_ ValueB,address _PL_ _R_ IndexA,address _PL_ _R_ IndexB)
{
	if(ValueA[0]<ValueA[1])
	{
		ValueB[0]=ValueA[1];
		ValueB[1]=ValueA[0];

		IndexB[0]=IndexA[1];
		IndexB[1]=IndexA[0];
	}
	else
	{
		ValueB[0]=ValueA[0];
		ValueB[1]=ValueA[1];

		IndexB[0]=IndexA[0];
		IndexB[1]=IndexA[1];
	}

	return;
}
static general LinC_Func_(_LinC_Sort_2_Move_Lite_M0_,TXX)(type_xx _PL_ _R_ ValueA,type_xx _PL_ _R_ ValueB)
{
	if(ValueA[0]<ValueA[1])
	{
		ValueB[0]=ValueA[0];
		ValueB[1]=ValueA[1];
	}
	else
	{
		ValueB[0]=ValueA[1];
		ValueB[1]=ValueA[0];
	}

	return;
}
static general LinC_Func_(_LinC_Sort_2_Move_Lite_M1_,TXX)(type_xx _PL_ _R_ ValueA,type_xx _PL_ _R_ ValueB)
{
	if(ValueA[0]<ValueA[1])
	{
		ValueB[0]=ValueA[1];
		ValueB[1]=ValueA[0];
	}
	else
	{
		ValueB[0]=ValueA[0];
		ValueB[1]=ValueA[1];
	}

	return;
}
static general LinC_Func_(_LinC_Recur_M0_,TXX)(type_xx *_R_ ValueSource,address *_R_ IndexSource,type_xx *_R_ ValueTarget,address *_R_ IndexTarget,ADDRESS Length,integer Bits)
{
	address Offset=LinC_Func_(_LinC_Radix_M0_,TXX)(ValueTarget,IndexTarget,ValueSource,IndexSource,Length,((type_xx)1)<<((type_xx)Bits))-ValueTarget;

	if(Bits--)
		if(Bits&1)
			switch(Offset)
			{
			default:
				LinC_Func_(_LinC_Recur_M0_,TXX)(ValueTarget,IndexTarget,ValueSource,IndexSource,Offset,Bits);
				goto JUMP_A;
			case 2:
				LinC_Func_(_LinC_Sort_2_Here_M0_,TXX)(ValueTarget,IndexTarget);
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
					LinC_Func_(_LinC_Recur_M0_,TXX)(ValueTarget,IndexTarget,ValueSource,IndexSource,Offset,Bits);
					break;
				case 2:
					LinC_Func_(_LinC_Sort_2_Here_M0_,TXX)(ValueTarget,IndexTarget);
				case 1:
				case 0:;
				}
			}
		else
			switch(Offset)
			{
			default:
				LinC_Func_(_LinC_Recur_M0_,TXX)(ValueTarget,IndexTarget,ValueSource,IndexSource,Offset,Bits);
				goto JUMP_B;
			case 2:
				LinC_Func_(_LinC_Sort_2_Move_M0_,TXX)(ValueTarget,ValueSource,IndexTarget,IndexSource);
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
					LinC_Func_(_LinC_Recur_M0_,TXX)(ValueTarget,IndexTarget,ValueSource,IndexSource,Offset,Bits);
					break;
				case 2:
					LinC_Func_(_LinC_Sort_2_Move_M0_,TXX)(ValueTarget,ValueSource,IndexTarget,IndexSource);
					break;
				case 1:
					ValueSource[0]=ValueTarget[0];
					IndexSource[0]=IndexTarget[0];
				case 0:;
				}
			}
	else;

	return;
}
static general LinC_Func_(_LinC_Recur_M1_,TXX)(type_xx *_R_ ValueSource,address *_R_ IndexSource,type_xx *_R_ ValueTarget,address *_R_ IndexTarget,ADDRESS Length,integer Bits)
{
	address Offset=LinC_Func_(_LinC_Radix_M1_,TXX)(ValueTarget,IndexTarget,ValueSource,IndexSource,Length,((type_xx)1)<<((type_xx)Bits))-ValueTarget;

	if(Bits--)
		if(Bits&1)
			switch(Offset)
			{
			default:
				LinC_Func_(_LinC_Recur_M1_,TXX)(ValueTarget,IndexTarget,ValueSource,IndexSource,Offset,Bits);
				goto JUMP_A;
			case 2:
				LinC_Func_(_LinC_Sort_2_Here_M1_,TXX)(ValueTarget,IndexTarget);
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
					LinC_Func_(_LinC_Recur_M1_,TXX)(ValueTarget,IndexTarget,ValueSource,IndexSource,Offset,Bits);
					break;
				case 2:
					LinC_Func_(_LinC_Sort_2_Here_M1_,TXX)(ValueTarget,IndexTarget);
				case 1:
				case 0:;
				}
			}
		else
			switch(Offset)
			{
			default:
				LinC_Func_(_LinC_Recur_M1_,TXX)(ValueTarget,IndexTarget,ValueSource,IndexSource,Offset,Bits);
				goto JUMP_B;
			case 2:
				LinC_Func_(_LinC_Sort_2_Move_M1_,TXX)(ValueTarget,ValueSource,IndexTarget,IndexSource);
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
					LinC_Func_(_LinC_Recur_M1_,TXX)(ValueTarget,IndexTarget,ValueSource,IndexSource,Offset,Bits);
					break;
				case 2:
					LinC_Func_(_LinC_Sort_2_Move_M1_,TXX)(ValueTarget,ValueSource,IndexTarget,IndexSource);
					break;
				case 1:
					ValueSource[0]=ValueTarget[0];
					IndexSource[0]=IndexTarget[0];
				case 0:;
				}
			}
	else;

	return;
}
static general LinC_Func_(_LinC_Recur_Lite_M0_,TXX)(type_xx *_R_ ValueSource,type_xx *_R_ ValueTarget,ADDRESS Length,integer Bits)
{
	address Offset=LinC_Func_(_LinC_Radix_Lite_M0_,TXX)(ValueTarget,ValueSource,Length,((type_xx)1)<<((type_xx)Bits))-ValueTarget;

	if(Bits--)
		if(Bits&1)
			switch(Offset)
			{
			default:
				LinC_Func_(_LinC_Recur_Lite_M0_,TXX)(ValueTarget,ValueSource,Offset,Bits);
				goto JUMP_A;
			case 2:
				LinC_Func_(_LinC_Sort_2_Here_Lite_M0_,TXX)(ValueTarget);
			case 1:
JUMP_A:
				ValueSource+=Offset;
				ValueTarget+=Offset;
			case 0:
				Offset=Length-Offset;
				switch(Offset)
				{
				default:
					LinC_Func_(_LinC_Recur_Lite_M0_,TXX)(ValueTarget,ValueSource,Offset,Bits);
					break;
				case 2:
					LinC_Func_(_LinC_Sort_2_Here_Lite_M0_,TXX)(ValueTarget);
				case 1:
				case 0:;
				}
			}
		else
			switch(Offset)
			{
			default:
				LinC_Func_(_LinC_Recur_Lite_M0_,TXX)(ValueTarget,ValueSource,Offset,Bits);
				goto JUMP_B;
			case 2:
				LinC_Func_(_LinC_Sort_2_Move_Lite_M0_,TXX)(ValueTarget,ValueSource);
				goto JUMP_B;
			case 1:
				ValueSource[0]=ValueTarget[0];
JUMP_B:
				ValueSource+=Offset;
				ValueTarget+=Offset;
			case 0:
				Offset=Length-Offset;
				switch(Offset)
				{
				default:
					LinC_Func_(_LinC_Recur_Lite_M0_,TXX)(ValueTarget,ValueSource,Offset,Bits);
					break;
				case 2:
					LinC_Func_(_LinC_Sort_2_Move_Lite_M0_,TXX)(ValueTarget,ValueSource);
					break;
				case 1:
					ValueSource[0]=ValueTarget[0];
				case 0:;
				}
			}
	else;

	return;
}
static general LinC_Func_(_LinC_Recur_Lite_M1_,TXX)(type_xx *_R_ ValueSource,type_xx *_R_ ValueTarget,ADDRESS Length,integer Bits)
{
	address Offset=LinC_Func_(_LinC_Radix_Lite_M1_,TXX)(ValueTarget,ValueSource,Length,((type_xx)1)<<((type_xx)Bits))-ValueTarget;

	if(Bits--)
		if(Bits&1)
			switch(Offset)
			{
			default:
				LinC_Func_(_LinC_Recur_Lite_M1_,TXX)(ValueTarget,ValueSource,Offset,Bits);
				goto JUMP_A;
			case 2:
				LinC_Func_(_LinC_Sort_2_Here_Lite_M1_,TXX)(ValueTarget);
			case 1:
JUMP_A:
				ValueSource+=Offset;
				ValueTarget+=Offset;
			case 0:
				Offset=Length-Offset;
				switch(Offset)
				{
				default:
					LinC_Func_(_LinC_Recur_Lite_M1_,TXX)(ValueTarget,ValueSource,Offset,Bits);
					break;
				case 2:
					LinC_Func_(_LinC_Sort_2_Here_Lite_M1_,TXX)(ValueTarget);
				case 1:
				case 0:;
				}
			}
		else
			switch(Offset)
			{
			default:
				LinC_Func_(_LinC_Recur_Lite_M1_,TXX)(ValueTarget,ValueSource,Offset,Bits);
				goto JUMP_B;
			case 2:
				LinC_Func_(_LinC_Sort_2_Move_Lite_M1_,TXX)(ValueTarget,ValueSource);
				goto JUMP_B;
			case 1:
				ValueSource[0]=ValueTarget[0];
JUMP_B:
				ValueSource+=Offset;
				ValueTarget+=Offset;
			case 0:
				Offset=Length-Offset;
				switch(Offset)
				{
				default:
					LinC_Func_(_LinC_Recur_Lite_M1_,TXX)(ValueTarget,ValueSource,Offset,Bits);
					break;
				case 2:
					LinC_Func_(_LinC_Sort_2_Move_Lite_M1_,TXX)(ValueTarget,ValueSource);
					break;
				case 1:
					ValueSource[0]=ValueTarget[0];
				case 0:;
				}
			}
	else;

	return;
}
#endif
#endif

#undef type
#undef TYPE

#else

#define TXX LinC_TXX_(T,XX)
#define TYPE_XX LinC_Type_(TYPE,XX)
#define type_xx LinC_Type_(type,XX)

#define D() (0)
#define I() (-1)
#define R() (+1)

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
#ifdef __OPENCL_VERSION__
#if(_BitC_R16_)
#define XX 16
#include "lincrux.c"
#undef XX
#endif
#define XX 32
#include "lincrux.c"
#undef XX
#if(_BitC_R64_)
#define XX 64
#include "lincrux.c"
#undef XX
#endif
#else
#define XX 32
#include "lincrux.c"
#undef XX
#define XX 64
#include "lincrux.c"
#undef XX
#endif
#undef T
#endif

#undef _SRC_LINCRUX

#undef R
#undef I
#undef D
#undef type_xx
#undef TYPE_XX
#undef TXX
#endif

#else
#ifdef __OPENCL_VERSION__
#error This template cannot be built directly.
#else
static void _LinC_Void_(void) { (void)(_LinC_Void_);return; }
#endif
#endif
