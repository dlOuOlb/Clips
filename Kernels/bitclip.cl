/*------------------------------------------------------------------*/
/*	BitClip's OpenCL Source Parts.									*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2018.07.23	*/
/*------------------------------------------------------------------*/
/*	OpenCL Support													*/
/*	http://www.khronos.org/opencl/									*/
/*------------------------------------------------------------------*/

#if(Fold_(Endian))
_K_ BitC_Endian_D16_(_G_ data_16 *_R_ Data,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Rest=Length%Step;
	_P_ DATA_32 Safe=Length-Rest;
	_G_ DATA_16 _PL_ End=Data+Safe;
	_P_ data_16 Now;
	_P_ data_08 _PL_ Byte=(_P_ data_08*)&Now;
	_P_ data_08 Temp;

	for(Data+=Start;Data<End;Data+=Step)
	{
		Now=Data[0];

		Temp=Byte[0];
		Byte[0]=Byte[1];
		Byte[1]=Temp;

		Wait_L_;
		Data[0]=Now;
	}
	if(Start<Rest)
	{
		Now=Data[0];

		Temp=Byte[0];
		Byte[0]=Byte[1];
		Byte[1]=Temp;

		Wait_L_;
		Data[0]=Now;
	}
	else
		Wait_L_;
}
_K_ BitC_Endian_D32_(_G_ data_32 *_R_ Data,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Rest=Length%Step;
	_P_ DATA_32 Safe=Length-Rest;
	_G_ DATA_32 _PL_ End=Data+Safe;
	_P_ data_32 Now;
	_P_ data_08 _PL_ Byte=(_P_ data_08*)&Now;
	_P_ data_08 Temp;

	for(Data+=Start;Data<End;Data+=Step)
	{
		Now=Data[0];

		Temp=Byte[0];
		Byte[0]=Byte[3];
		Byte[3]=Temp;

		Temp=Byte[1];
		Byte[1]=Byte[2];
		Byte[2]=Temp;

		Wait_L_;
		Data[0]=Now;
	}
	if(Start<Rest)
	{
		Now=Data[0];

		Temp=Byte[0];
		Byte[0]=Byte[3];
		Byte[3]=Temp;

		Temp=Byte[1];
		Byte[1]=Byte[2];
		Byte[2]=Temp;

		Wait_L_;
		Data[0]=Now;
	}
	else
		Wait_L_;
}
_K_ BitC_Endian_D64_(_G_ data_64 *_R_ Data,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Rest=Length%Step;
	_P_ DATA_32 Safe=Length-Rest;
	_G_ DATA_64 _PL_ End=Data+Safe;
	_P_ data_64 Now;
	_P_ data_08 _PL_ Byte=(_P_ data_08*)&Now;
	_P_ data_08 Temp;

	for(Data+=Start;Data<End;Data+=Step)
	{
		Now=Data[0];

		Temp=Byte[0];
		Byte[0]=Byte[7];
		Byte[7]=Temp;

		Temp=Byte[1];
		Byte[1]=Byte[6];
		Byte[6]=Temp;

		Temp=Byte[2];
		Byte[2]=Byte[5];
		Byte[5]=Temp;

		Temp=Byte[3];
		Byte[3]=Byte[4];
		Byte[4]=Temp;

		Wait_L_;
		Data[0]=Now;
	}
	if(Start<Rest)
	{
		Now=Data[0];

		Temp=Byte[0];
		Byte[0]=Byte[7];
		Byte[7]=Temp;

		Temp=Byte[1];
		Byte[1]=Byte[6];
		Byte[6]=Temp;

		Temp=Byte[2];
		Byte[2]=Byte[5];
		Byte[5]=Temp;

		Temp=Byte[3];
		Byte[3]=Byte[4];
		Byte[4]=Temp;

		Wait_L_;
		Data[0]=Now;
	}
	else
		Wait_L_;
}
#endif

#if(Fold_(Caster))
_K_ BitC_Caster_D08_D16_(_G_ DATA_08 *_R_ DataI,_G_ data_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_08 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_16)(DataI[0]);
}
_K_ BitC_Caster_D08_D32_(_G_ DATA_08 *_R_ DataI,_G_ data_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_08 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_32)(DataI[0]);
}
_K_ BitC_Caster_D08_D64_(_G_ DATA_08 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_08 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_64)(DataI[0]);
}
_K_ BitC_Caster_D08_I08_(_G_ DATA_08 *_R_ DataI,_G_ inte_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_08 Max=0x7FU;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_08 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_08)min(DataI[0],Max);
}
#if(_ABLE_R16_)
_K_ BitC_Caster_D08_R16_(_G_ DATA_08 *_R_ DataI,_G_ real_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_08 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_16)(DataI[0]);
}
#endif
_K_ BitC_Caster_D08_R32_(_G_ DATA_08 *_R_ DataI,_G_ real_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_08 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_32)(DataI[0]);
}
#if(_ABLE_R64_)
_K_ BitC_Caster_D08_R64_(_G_ DATA_08 *_R_ DataI,_G_ real_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_08 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_64)(DataI[0]);
}
#endif
_K_ BitC_Caster_D16_D08_(_G_ DATA_16 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_16 Max=0x00FFU;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_08)min(DataI[0],Max);
}
_K_ BitC_Caster_D16_D32_(_G_ DATA_16 *_R_ DataI,_G_ data_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_32)(DataI[0]);
}
_K_ BitC_Caster_D16_D64_(_G_ DATA_16 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_64)(DataI[0]);
}
_K_ BitC_Caster_D16_I08_(_G_ DATA_16 *_R_ DataI,_G_ inte_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_16 Max=0x007FU;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_08)min(DataI[0],Max);
}
_K_ BitC_Caster_D16_I16_(_G_ DATA_16 *_R_ DataI,_G_ inte_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_16 Max=0x7FFFU;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_16)min(DataI[0],Max);
}
#if(_ABLE_R16_)
_K_ BitC_Caster_D16_R16_(_G_ DATA_16 *_R_ DataI,_G_ real_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_16)(DataI[0]);
}
#endif
_K_ BitC_Caster_D16_R32_(_G_ DATA_16 *_R_ DataI,_G_ real_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_32)(DataI[0]);
}
#if(_ABLE_R64_)
_K_ BitC_Caster_D16_R64_(_G_ DATA_16 *_R_ DataI,_G_ real_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_64)(DataI[0]);
}
#endif
_K_ BitC_Caster_D32_D08_(_G_ DATA_32 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Max=0x000000FFU;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_08)min(DataI[0],Max);
}
_K_ BitC_Caster_D32_D16_(_G_ DATA_32 *_R_ DataI,_G_ data_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Max=0x0000FFFFU;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_16)min(DataI[0],Max);
}
_K_ BitC_Caster_D32_D64_(_G_ DATA_32 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_64)(DataI[0]);
}
_K_ BitC_Caster_D32_I08_(_G_ DATA_32 *_R_ DataI,_G_ inte_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Max=0x0000007FU;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_08)min(DataI[0],Max);
}
_K_ BitC_Caster_D32_I16_(_G_ DATA_32 *_R_ DataI,_G_ inte_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Max=0x00007FFFU;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_16)min(DataI[0],Max);
}
_K_ BitC_Caster_D32_I32_(_G_ DATA_32 *_R_ DataI,_G_ inte_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Max=0x7FFFFFFFU;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_32)min(DataI[0],Max);
}
#if(_ABLE_R16_)
_K_ BitC_Caster_D32_R16_(_G_ DATA_32 *_R_ DataI,_G_ real_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_16)(DataI[0]);
}
#endif
_K_ BitC_Caster_D32_R32_(_G_ DATA_32 *_R_ DataI,_G_ real_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_32)(DataI[0]);
}
#if(_ABLE_R64_)
_K_ BitC_Caster_D32_R64_(_G_ DATA_32 *_R_ DataI,_G_ real_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_64)(DataI[0]);
}
#endif
_K_ BitC_Caster_D64_D08_(_G_ DATA_64 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_64 Max=0x00000000000000FFUL;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_08)min(DataI[0],Max);
}
_K_ BitC_Caster_D64_D16_(_G_ DATA_64 *_R_ DataI,_G_ data_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_64 Max=0x000000000000FFFFUL;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_16)min(DataI[0],Max);
}
_K_ BitC_Caster_D64_D32_(_G_ DATA_64 *_R_ DataI,_G_ data_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_64 Max=0x00000000FFFFFFFFUL;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_32)min(DataI[0],Max);
}
_K_ BitC_Caster_D64_I08_(_G_ DATA_64 *_R_ DataI,_G_ inte_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_64 Max=0x000000000000007FUL;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_08)min(DataI[0],Max);
}
_K_ BitC_Caster_D64_I16_(_G_ DATA_64 *_R_ DataI,_G_ inte_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_64 Max=0x0000000000007FFFUL;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_16)min(DataI[0],Max);
}
_K_ BitC_Caster_D64_I32_(_G_ DATA_64 *_R_ DataI,_G_ inte_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_64 Max=0x000000007FFFFFFFUL;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_32)min(DataI[0],Max);
}
_K_ BitC_Caster_D64_I64_(_G_ DATA_64 *_R_ DataI,_G_ inte_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_64 Max=0x7FFFFFFFFFFFFFFFUL;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_64)min(DataI[0],Max);
}
#if(_ABLE_R16_)
_K_ BitC_Caster_D64_R16_(_G_ DATA_64 *_R_ DataI,_G_ real_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_16)(DataI[0]);
}
#endif
_K_ BitC_Caster_D64_R32_(_G_ DATA_64 *_R_ DataI,_G_ real_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_32)(DataI[0]);
}
#if(_ABLE_R64_)
_K_ BitC_Caster_D64_R64_(_G_ DATA_64 *_R_ DataI,_G_ real_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_64)(DataI[0]);
}
#endif
_K_ BitC_Caster_I08_D08_(_G_ INTE_08 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_08 Min=0x00;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_08 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_08)max(DataI[0],Min);
}
_K_ BitC_Caster_I08_D16_(_G_ INTE_08 *_R_ DataI,_G_ data_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_08 Min=0x00;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_08 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_16)max(DataI[0],Min);
}
_K_ BitC_Caster_I08_D32_(_G_ INTE_08 *_R_ DataI,_G_ data_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_08 Min=0x00;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_08 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_32)max(DataI[0],Min);
}
_K_ BitC_Caster_I08_D64_(_G_ INTE_08 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_08 Min=0x00;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_08 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_64)max(DataI[0],Min);
}
_K_ BitC_Caster_I08_I16_(_G_ INTE_08 *_R_ DataI,_G_ inte_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_08 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_16)(DataI[0]);
}
_K_ BitC_Caster_I08_I32_(_G_ INTE_08 *_R_ DataI,_G_ inte_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_08 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_32)(DataI[0]);
}
_K_ BitC_Caster_I08_I64_(_G_ INTE_08 *_R_ DataI,_G_ inte_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_08 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_64)(DataI[0]);
}
#if(_ABLE_R16_)
_K_ BitC_Caster_I08_R16_(_G_ INTE_08 *_R_ DataI,_G_ real_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_08 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_16)(DataI[0]);
}
#endif
_K_ BitC_Caster_I08_R32_(_G_ INTE_08 *_R_ DataI,_G_ real_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_08 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_32)(DataI[0]);
}
#if(_ABLE_R64_)
_K_ BitC_Caster_I08_R64_(_G_ INTE_08 *_R_ DataI,_G_ real_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_08 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_64)(DataI[0]);
}
#endif
_K_ BitC_Caster_I16_D08_(_G_ INTE_16 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_16 Min=0x0000;
	_P_ INTE_16 Max=0x00FF;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_08)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_I16_D16_(_G_ INTE_16 *_R_ DataI,_G_ data_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_16 Min=0x0000;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_16)max(DataI[0],Min);
}
_K_ BitC_Caster_I16_D32_(_G_ INTE_16 *_R_ DataI,_G_ data_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_16 Min=0x0000;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_32)max(DataI[0],Min);
}
_K_ BitC_Caster_I16_D64_(_G_ INTE_16 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_16 Min=0x0000;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_64)max(DataI[0],Min);
}
_K_ BitC_Caster_I16_I08_(_G_ INTE_16 *_R_ DataI,_G_ inte_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_16 Min=0xFF80;
	_P_ INTE_16 Max=0x007F;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_08)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_I16_I32_(_G_ INTE_16 *_R_ DataI,_G_ inte_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_32)(DataI[0]);
}
_K_ BitC_Caster_I16_I64_(_G_ INTE_16 *_R_ DataI,_G_ inte_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_64)(DataI[0]);
}
#if(_ABLE_R16_)
_K_ BitC_Caster_I16_R16_(_G_ INTE_16 *_R_ DataI,_G_ real_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_16)(DataI[0]);
}
#endif
_K_ BitC_Caster_I16_R32_(_G_ INTE_16 *_R_ DataI,_G_ real_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_32)(DataI[0]);
}
#if(_ABLE_R64_)
_K_ BitC_Caster_I16_R64_(_G_ INTE_16 *_R_ DataI,_G_ real_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_64)(DataI[0]);
}
#endif
_K_ BitC_Caster_I32_D08_(_G_ INTE_32 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_32 Min=0x00000000;
	_P_ INTE_32 Max=0x000000FF;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_08)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_I32_D16_(_G_ INTE_32 *_R_ DataI,_G_ data_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_32 Min=0x00000000;
	_P_ INTE_32 Max=0x0000FFFF;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_16)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_I32_D32_(_G_ INTE_32 *_R_ DataI,_G_ data_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_32 Min=0x00000000;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_32)max(DataI[0],Min);
}
_K_ BitC_Caster_I32_D64_(_G_ INTE_32 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_32 Min=0x00000000;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_64)max(DataI[0],Min);
}
_K_ BitC_Caster_I32_I08_(_G_ INTE_32 *_R_ DataI,_G_ inte_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_32 Min=0xFFFFFF80;
	_P_ INTE_32 Max=0x0000007F;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_08)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_I32_I16_(_G_ INTE_32 *_R_ DataI,_G_ inte_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_32 Min=0xFFFF8000;
	_P_ INTE_32 Max=0x00007FFF;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_16)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_I32_I64_(_G_ INTE_32 *_R_ DataI,_G_ inte_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_64)(DataI[0]);
}
#if(_ABLE_R16_)
_K_ BitC_Caster_I32_R16_(_G_ INTE_32 *_R_ DataI,_G_ real_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_16)(DataI[0]);
}
#endif
_K_ BitC_Caster_I32_R32_(_G_ INTE_32 *_R_ DataI,_G_ real_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_32)(DataI[0]);
}
#if(_ABLE_R64_)
_K_ BitC_Caster_I32_R64_(_G_ INTE_32 *_R_ DataI,_G_ real_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_64)(DataI[0]);
}
#endif
_K_ BitC_Caster_I64_D08_(_G_ INTE_64 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_64 Min=0x0000000000000000L;
	_P_ INTE_64 Max=0x00000000000000FFL;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_08)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_I64_D16_(_G_ INTE_64 *_R_ DataI,_G_ data_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_64 Min=0x0000000000000000L;
	_P_ INTE_64 Max=0x000000000000FFFFL;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_16)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_I64_D32_(_G_ INTE_64 *_R_ DataI,_G_ data_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_64 Min=0x0000000000000000L;
	_P_ INTE_64 Max=0x00000000FFFFFFFFL;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_32)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_I64_D64_(_G_ INTE_64 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_64 Min=0x0000000000000000L;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_64)max(DataI[0],Min);
}
_K_ BitC_Caster_I64_I08_(_G_ INTE_64 *_R_ DataI,_G_ inte_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_64 Min=0xFFFFFFFFFFFFFF80L;
	_P_ INTE_64 Max=0x000000000000007FL;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_08)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_I64_I16_(_G_ INTE_64 *_R_ DataI,_G_ inte_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_64 Min=0xFFFFFFFFFFFF8000L;
	_P_ INTE_64 Max=0x0000000000007FFFL;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_16)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_I64_I32_(_G_ INTE_64 *_R_ DataI,_G_ inte_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_64 Min=0xFFFFFFFF80000000L;
	_P_ INTE_64 Max=0x000000007FFFFFFFL;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_32)clamp(DataI[0],Min,Max);
}
#if(_ABLE_R16_)
_K_ BitC_Caster_I64_R16_(_G_ INTE_64 *_R_ DataI,_G_ real_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_16)(DataI[0]);
}
#endif
_K_ BitC_Caster_I64_R32_(_G_ INTE_64 *_R_ DataI,_G_ real_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_32)(DataI[0]);
}
#if(_ABLE_R64_)
_K_ BitC_Caster_I64_R64_(_G_ INTE_64 *_R_ DataI,_G_ real_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_64)(DataI[0]);
}
#endif
#if(_ABLE_R16_)
_K_ BitC_Caster_R16_D08_(_G_ REAL_16 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_08 Table[2]={0x00U,0xFFU};
	_P_ REAL_16 Min=(real_16)(Table[0]);
	_P_ REAL_16 Max=(real_16)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_08)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R16_D16_(_G_ REAL_16 *_R_ DataI,_G_ data_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_16 Table[2]={0x0000U,0xFFFFU};
	_P_ REAL_16 Min=(real_16)(Table[0]);
	_P_ REAL_16 Max=(real_16)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_16)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R16_D32_(_G_ REAL_16 *_R_ DataI,_G_ data_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Table[2]={0x00000000U,0xFFFFFFFFU};
	_P_ REAL_16 Min=(real_16)(Table[0]);
	_P_ REAL_16 Max=(real_16)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_32)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R16_D64_(_G_ REAL_16 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_64 Table[2]={0x0000000000000000UL,0xFFFFFFFFFFFFFFFFUL};
	_P_ REAL_16 Min=(real_16)(Table[0]);
	_P_ REAL_16 Max=(real_16)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_64)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R16_I08_(_G_ REAL_16 *_R_ DataI,_G_ inte_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_08 Table[2]={0x80,0x7F};
	_P_ REAL_16 Min=(real_16)(Table[0]);
	_P_ REAL_16 Max=(real_16)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_08)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R16_I16_(_G_ REAL_16 *_R_ DataI,_G_ inte_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_16 Table[2]={0x8000,0x7FFF};
	_P_ REAL_16 Min=(real_16)(Table[0]);
	_P_ REAL_16 Max=(real_16)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_16)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R16_I32_(_G_ REAL_16 *_R_ DataI,_G_ inte_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_32 Table[2]={0x80000000,0x7FFFFFFF};
	_P_ REAL_16 Min=(real_16)(Table[0]);
	_P_ REAL_16 Max=(real_16)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_32)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R16_I64_(_G_ REAL_16 *_R_ DataI,_G_ inte_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_64 Table[2]={0x8000000000000000L,0x7FFFFFFFFFFFFFFFL};
	_P_ REAL_16 Min=(real_16)(Table[0]);
	_P_ REAL_16 Max=(real_16)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_64)(DataI[0],Min,Max);
}
_K_ BitC_Caster_R16_R32_(_G_ REAL_16 *_R_ DataI,_G_ real_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_32)(DataI[0]);
}
#if(_ABLE_R64_)
_K_ BitC_Caster_R16_R64_(_G_ REAL_16 *_R_ DataI,_G_ real_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_64)(DataI[0]);
}
#endif
#endif
_K_ BitC_Caster_R32_D08_(_G_ REAL_32 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_08 Table[2]={0x00U,0xFFU};
	_P_ REAL_32 Min=(real_32)(Table[0]);
	_P_ REAL_32 Max=(real_32)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_08)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R32_D16_(_G_ REAL_32 *_R_ DataI,_G_ data_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_16 Table[2]={0x0000U,0xFFFFU};
	_P_ REAL_32 Min=(real_32)(Table[0]);
	_P_ REAL_32 Max=(real_32)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_16)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R32_D32_(_G_ REAL_32 *_R_ DataI,_G_ data_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Table[2]={0x00000000U,0xFFFFFFFFU};
	_P_ REAL_32 Min=(real_32)(Table[0]);
	_P_ REAL_32 Max=(real_32)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_32)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R32_D64_(_G_ REAL_32 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_64 Table[2]={0x0000000000000000UL,0xFFFFFFFFFFFFFFFFUL};
	_P_ REAL_32 Min=(real_32)(Table[0]);
	_P_ REAL_32 Max=(real_32)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_64)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R32_I08_(_G_ REAL_32 *_R_ DataI,_G_ inte_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_08 Table[2]={0x80,0x7F};
	_P_ REAL_32 Min=(real_32)(Table[0]);
	_P_ REAL_32 Max=(real_32)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_08)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R32_I16_(_G_ REAL_32 *_R_ DataI,_G_ inte_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_16 Table[2]={0x8000,0x7FFF};
	_P_ REAL_32 Min=(real_32)(Table[0]);
	_P_ REAL_32 Max=(real_32)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_16)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R32_I32_(_G_ REAL_32 *_R_ DataI,_G_ inte_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_32 Table[2]={0x80000000,0x7FFFFFFF};
	_P_ REAL_32 Min=(real_32)(Table[0]);
	_P_ REAL_32 Max=(real_32)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_32)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R32_I64_(_G_ REAL_32 *_R_ DataI,_G_ inte_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_64 Table[2]={0x8000000000000000L,0x7FFFFFFFFFFFFFFFL};
	_P_ REAL_32 Min=(real_32)(Table[0]);
	_P_ REAL_32 Max=(real_32)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_64)clamp(DataI[0],Min,Max);
}
#if(_ABLE_R16_)
_K_ BitC_Caster_R32_R16_(_G_ REAL_32 *_R_ DataI,_G_ real_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_16)(DataI[0]);
}
#endif
#if(_ABLE_R64_)
_K_ BitC_Caster_R32_R64_(_G_ REAL_32 *_R_ DataI,_G_ real_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_64)(DataI[0]);
}
#endif
#if(_ABLE_R64_)
_K_ BitC_Caster_R64_D08_(_G_ REAL_64 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_08 Table[2]={0x00U,0xFFU};
	_P_ REAL_64 Min=(real_64)(Table[0]);
	_P_ REAL_64 Max=(real_64)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_08)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R64_D16_(_G_ REAL_64 *_R_ DataI,_G_ data_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_16 Table[2]={0x0000U,0xFFFFU};
	_P_ REAL_64 Min=(real_64)(Table[0]);
	_P_ REAL_64 Max=(real_64)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_16)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R64_D32_(_G_ REAL_64 *_R_ DataI,_G_ data_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Table[2]={0x00000000U,0xFFFFFFFFU};
	_P_ REAL_64 Min=(real_64)(Table[0]);
	_P_ REAL_64 Max=(real_64)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_32)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R64_D64_(_G_ REAL_64 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_64 Table[2]={0x0000000000000000UL,0xFFFFFFFFFFFFFFFFUL};
	_P_ REAL_64 Min=(real_64)(Table[0]);
	_P_ REAL_64 Max=(real_64)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_64)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R64_I08_(_G_ REAL_64 *_R_ DataI,_G_ inte_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_08 Table[2]={0x80,0x7F};
	_P_ REAL_64 Min=(real_64)(Table[0]);
	_P_ REAL_64 Max=(real_64)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_08)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R64_I16_(_G_ REAL_64 *_R_ DataI,_G_ inte_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_16 Table[2]={0x8000,0x7FFF};
	_P_ REAL_64 Min=(real_64)(Table[0]);
	_P_ REAL_64 Max=(real_64)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_16)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R64_I32_(_G_ REAL_64 *_R_ DataI,_G_ inte_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_32 Table[2]={0x80000000,0x7FFFFFFF};
	_P_ REAL_64 Min=(real_64)(Table[0]);
	_P_ REAL_64 Max=(real_64)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_32)clamp(DataI[0],Min,Max);
}
_K_ BitC_Caster_R64_I64_(_G_ REAL_64 *_R_ DataI,_G_ inte_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_64 Table[2]={0x8000000000000000L,0x7FFFFFFFFFFFFFFFL};
	_P_ REAL_64 Min=(real_64)(Table[0]);
	_P_ REAL_64 Max=(real_64)(Table[1]);
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_64)clamp(DataI[0],Min,Max);
}
#if(_ABLE_R16_)
_K_ BitC_Caster_R64_R16_(_G_ REAL_64 *_R_ DataI,_G_ real_16 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_16)(DataI[0]);
}
#endif
_K_ BitC_Caster_R64_R32_(_G_ REAL_64 *_R_ DataI,_G_ real_32 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ REAL_64 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(real_32)(DataI[0]);
}
#endif
#endif

#if(Fold_(Bit Operation))
_K_ BitC_BO_N_1_D08_(_G_ data_08 _PL_ DataC,_G_ DATA_08 _PL_ DataA,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 RestOld;
	_P_ data_32 RestNew;
	_P_ point_g End;
	_P_ point_g PtrA;
	_P_ point_g PtrC;

	{
		RestOld=Length;
		RestNew=Length%(Step<<2);
		End.C.D08=DataA+(RestOld-RestNew);
	}
	for(PtrA.C.D08=DataA,PtrC.C.D08=DataC;PtrA.C.G<End.C.G;PtrA.C.D32+=Step,PtrC.C.D32+=Step)
		PtrC.V.D32[Start]=~(PtrA.C.D32[Start]);
	{
		RestOld=RestNew;
		RestNew%=(Step<<1);
	}
	if(RestNew<RestOld)
	{
		PtrC.V.D16[Start]=~(PtrA.C.D16[Start]);

		PtrA.C.D16+=Step;
		PtrC.C.D16+=Step;
	}
	{
		RestOld=RestNew;
		RestNew%=Step;
	}
	if(RestNew<RestOld)
	{
		PtrC.V.D08[Start]=~(PtrA.C.D08[Start]);

		PtrA.C.D08+=Step;
		PtrC.C.D08+=Step;
	}
	if(Start<RestNew)
		PtrC.V.D08[Start]=~(PtrA.C.D08[Start]);
}

_K_ BitC_BO_S_1_D08_(_G_ data_08 *DataC,_G_ DATA_08 *DataA,_P_ inte_32 Shift,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_08 _PL_ End=DataA+Length;

	if(Shift>0)
		for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
			DataC[0]=DataA[0]<<Shift;
	else
		for(Shift=-Shift,DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
			DataC[0]=DataA[0]>>Shift;
}
_K_ BitC_BO_S_1_D16_(_G_ data_16 *DataC,_G_ DATA_16 *DataA,_P_ inte_32 Shift,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_16 _PL_ End=DataA+Length;

	if(Shift>0)
		for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
			DataC[0]=DataA[0]<<Shift;
	else
		for(Shift=-Shift,DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
			DataC[0]=DataA[0]>>Shift;
}
_K_ BitC_BO_S_1_D32_(_G_ data_32 *DataC,_G_ DATA_32 *DataA,_P_ inte_32 Shift,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_32 _PL_ End=DataA+Length;

	if(Shift>0)
		for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
			DataC[0]=DataA[0]<<Shift;
	else
		for(Shift=-Shift,DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
			DataC[0]=DataA[0]>>Shift;
}
_K_ BitC_BO_S_1_D64_(_G_ data_64 *DataC,_G_ DATA_64 *DataA,_P_ inte_32 Shift,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_64 _PL_ End=DataA+Length;

	if(Shift>0)
		for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
			DataC[0]=DataA[0]<<Shift;
	else
		for(Shift=-Shift,DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
			DataC[0]=DataA[0]>>Shift;
}
_K_ BitC_BO_S_1_I08_(_G_ inte_08 *DataC,_G_ INTE_08 *DataA,_P_ inte_32 Shift,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_08 _PL_ End=DataA+Length;

	if(Shift>0)
		for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
			DataC[0]=DataA[0]<<Shift;
	else
		for(Shift=-Shift,DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
			DataC[0]=DataA[0]>>Shift;
}
_K_ BitC_BO_S_1_I16_(_G_ inte_16 *DataC,_G_ INTE_16 *DataA,_P_ inte_32 Shift,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_16 _PL_ End=DataA+Length;

	if(Shift>0)
		for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
			DataC[0]=DataA[0]<<Shift;
	else
		for(Shift=-Shift,DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
			DataC[0]=DataA[0]>>Shift;
}
_K_ BitC_BO_S_1_I32_(_G_ inte_32 *DataC,_G_ INTE_32 *DataA,_P_ inte_32 Shift,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_32 _PL_ End=DataA+Length;

	if(Shift>0)
		for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
			DataC[0]=DataA[0]<<Shift;
	else
		for(Shift=-Shift,DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
			DataC[0]=DataA[0]>>Shift;
}
_K_ BitC_BO_S_1_I64_(_G_ inte_64 *DataC,_G_ INTE_64 *DataA,_P_ inte_32 Shift,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_64 _PL_ End=DataA+Length;

	if(Shift>0)
		for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
			DataC[0]=DataA[0]<<Shift;
	else
		for(Shift=-Shift,DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
			DataC[0]=DataA[0]>>Shift;
}

_K_ BitC_BO_A_1_D08_(_G_ data_08* DataC,_G_ DATA_08* DataA,_P_ DATA_08 Mask,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_08 _PL_ End=DataA+Length;

	for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
		DataC[0]=DataA[0]&Mask;
}
_K_ BitC_BO_A_1_D16_(_G_ data_16* DataC,_G_ DATA_16* DataA,_P_ DATA_16 Mask,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_16 _PL_ End=DataA+Length;

	for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
		DataC[0]=DataA[0]&Mask;
}
_K_ BitC_BO_A_1_D32_(_G_ data_32* DataC,_G_ DATA_32* DataA,_P_ DATA_32 Mask,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_32 _PL_ End=DataA+Length;

	for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
		DataC[0]=DataA[0]&Mask;
}
_K_ BitC_BO_A_1_D64_(_G_ data_64* DataC,_G_ DATA_64* DataA,_P_ DATA_64 Mask,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_64 _PL_ End=DataA+Length;

	for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
		DataC[0]=DataA[0]&Mask;
}
_K_ BitC_BO_A_2_D08_(_G_ data_08 _PL_ DataC,_G_ DATA_08 _PL_ DataA,_G_ DATA_08 _PL_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 RestOld;
	_P_ data_32 RestNew;
	_P_ point_g End;
	_P_ point_g PtrA;
	_P_ point_g PtrB;
	_P_ point_g PtrC;

	{
		RestOld=Length;
		RestNew=Length%(Step<<2);
		End.C.D08=DataA+(RestOld-RestNew);
	}
	for(PtrA.C.D08=DataA,PtrB.C.D08=DataB,PtrC.C.D08=DataC;PtrA.C.G<End.C.G;PtrA.C.D32+=Step,PtrB.C.D32+=Step,PtrC.C.D32+=Step)
		PtrC.V.D32[Start]=PtrA.C.D32[Start]&PtrB.C.D32[Start];
	{
		RestOld=RestNew;
		RestNew%=(Step<<1);
	}
	if(RestNew<RestOld)
	{
		PtrC.V.D16[Start]=PtrA.C.D16[Start]&PtrB.C.D16[Start];

		PtrA.C.D16+=Step;
		PtrB.C.D16+=Step;
		PtrC.C.D16+=Step;
	}
	{
		RestOld=RestNew;
		RestNew%=Step;
	}
	if(RestNew<RestOld)
	{
		PtrC.V.D08[Start]=PtrA.C.D08[Start]&PtrB.C.D08[Start];

		PtrA.C.D08+=Step;
		PtrB.C.D08+=Step;
		PtrC.C.D08+=Step;
	}
	if(Start<RestNew)
		PtrC.V.D08[Start]=PtrA.C.D08[Start]&PtrB.C.D08[Start];
}

_K_ BitC_BO_O_1_D08_(_G_ data_08* DataC,_G_ DATA_08* DataA,_P_ DATA_08 Mask,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_08 _PL_ End=DataA+Length;

	for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
		DataC[0]=DataA[0]|Mask;
}
_K_ BitC_BO_O_1_D16_(_G_ data_16* DataC,_G_ DATA_16* DataA,_P_ DATA_16 Mask,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_16 _PL_ End=DataA+Length;

	for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
		DataC[0]=DataA[0]|Mask;
}
_K_ BitC_BO_O_1_D32_(_G_ data_32* DataC,_G_ DATA_32* DataA,_P_ DATA_32 Mask,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_32 _PL_ End=DataA+Length;

	for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
		DataC[0]=DataA[0]|Mask;
}
_K_ BitC_BO_O_1_D64_(_G_ data_64* DataC,_G_ DATA_64* DataA,_P_ DATA_64 Mask,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_64 _PL_ End=DataA+Length;

	for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
		DataC[0]=DataA[0]|Mask;
}
_K_ BitC_BO_O_2_D08_(_G_ data_08 _PL_ DataC,_G_ DATA_08 _PL_ DataA,_G_ DATA_08 _PL_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 RestOld;
	_P_ data_32 RestNew;
	_P_ point_g End;
	_P_ point_g PtrA;
	_P_ point_g PtrB;
	_P_ point_g PtrC;

	{
		RestOld=Length;
		RestNew=Length%(Step<<2);
		End.C.D08=DataA+(RestOld-RestNew);
	}
	for(PtrA.C.D08=DataA,PtrB.C.D08=DataB,PtrC.C.D08=DataC;PtrA.C.G<End.C.G;PtrA.C.D32+=Step,PtrB.C.D32+=Step,PtrC.C.D32+=Step)
		PtrC.V.D32[Start]=PtrA.C.D32[Start]|PtrB.C.D32[Start];
	{
		RestOld=RestNew;
		RestNew%=(Step<<1);
	}
	if(RestNew<RestOld)
	{
		PtrC.V.D16[Start]=PtrA.C.D16[Start]|PtrB.C.D16[Start];

		PtrA.C.D16+=Step;
		PtrB.C.D16+=Step;
		PtrC.C.D16+=Step;
	}
	{
		RestOld=RestNew;
		RestNew%=Step;
	}
	if(RestNew<RestOld)
	{
		PtrC.V.D08[Start]=PtrA.C.D08[Start]|PtrB.C.D08[Start];

		PtrA.C.D08+=Step;
		PtrB.C.D08+=Step;
		PtrC.C.D08+=Step;
	}
	if(Start<RestNew)
		PtrC.V.D08[Start]=PtrA.C.D08[Start]|PtrB.C.D08[Start];
}

_K_ BitC_BO_X_1_D08_(_G_ data_08* DataC,_G_ DATA_08* DataA,_P_ DATA_08 Mask,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_08 _PL_ End=DataA+Length;

	for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
		DataC[0]=DataA[0]^Mask;
}
_K_ BitC_BO_X_1_D16_(_G_ data_16* DataC,_G_ DATA_16* DataA,_P_ DATA_16 Mask,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_16 _PL_ End=DataA+Length;

	for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
		DataC[0]=DataA[0]^Mask;
}
_K_ BitC_BO_X_1_D32_(_G_ data_32* DataC,_G_ DATA_32* DataA,_P_ DATA_32 Mask,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_32 _PL_ End=DataA+Length;

	for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
		DataC[0]=DataA[0]^Mask;
}
_K_ BitC_BO_X_1_D64_(_G_ data_64* DataC,_G_ DATA_64* DataA,_P_ DATA_64 Mask,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_64 _PL_ End=DataA+Length;

	for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
		DataC[0]=DataA[0]^Mask;
}
_K_ BitC_BO_X_2_D08_(_G_ data_08 _PL_ DataC,_G_ DATA_08 _PL_ DataA,_G_ DATA_08 _PL_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 RestOld;
	_P_ data_32 RestNew;
	_P_ point_g End;
	_P_ point_g PtrA;
	_P_ point_g PtrB;
	_P_ point_g PtrC;

	{
		RestOld=Length;
		RestNew=Length%(Step<<2);
		End.C.D08=DataA+(RestOld-RestNew);
	}
	for(PtrA.C.D08=DataA,PtrB.C.D08=DataB,PtrC.C.D08=DataC;PtrA.C.G<End.C.G;PtrA.C.D32+=Step,PtrB.C.D32+=Step,PtrC.C.D32+=Step)
		PtrC.V.D32[Start]=PtrA.C.D32[Start]^PtrB.C.D32[Start];
	{
		RestOld=RestNew;
		RestNew%=(Step<<1);
	}
	if(RestNew<RestOld)
	{
		PtrC.V.D16[Start]=PtrA.C.D16[Start]^PtrB.C.D16[Start];

		PtrA.C.D16+=Step;
		PtrB.C.D16+=Step;
		PtrC.C.D16+=Step;
	}
	{
		RestOld=RestNew;
		RestNew%=Step;
	}
	if(RestNew<RestOld)
	{
		PtrC.V.D08[Start]=PtrA.C.D08[Start]^PtrB.C.D08[Start];

		PtrA.C.D08+=Step;
		PtrB.C.D08+=Step;
		PtrC.C.D08+=Step;
	}
	if(Start<RestNew)
		PtrC.V.D08[Start]=PtrA.C.D08[Start]^PtrB.C.D08[Start];
}
#endif

#if(Fold_(Relational Operation))
_I_ general _BitC_Taking_D08_(_P_ data_08 _PL_ _R_ T,_G_ DATA_08 _PL_ _R_ S,_P_ INTE_32 L)
{
	inte_32 I=0;

	switch(L)
	{
	case 0x00000007:
		T[I]=S[I];
		I++;
	case 0x00000006:
		T[I]=S[I];
		I++;
	case 0x00000005:
		T[I]=S[I];
		I++;
	case 0x00000004:
		T[I]=S[I];
		I++;
	case 0x00000003:
		T[I]=S[I];
		I++;
	case 0x00000002:
		T[I]=S[I];
		I++;
	case 0x00000001:
		T[I]=S[I];
	default:;
	}
}
_I_ general _BitC_Taking_D16_(_P_ data_16 _PL_ _R_ T,_G_ DATA_16 _PL_ _R_ S,_P_ INTE_32 L)
{
	inte_32 I=0;

	switch(L)
	{
	case 0x00000007:
		T[I]=S[I];
		I++;
	case 0x00000006:
		T[I]=S[I];
		I++;
	case 0x00000005:
		T[I]=S[I];
		I++;
	case 0x00000004:
		T[I]=S[I];
		I++;
	case 0x00000003:
		T[I]=S[I];
		I++;
	case 0x00000002:
		T[I]=S[I];
		I++;
	case 0x00000001:
		T[I]=S[I];
	default:;
	}
}
_I_ general _BitC_Taking_D32_(_P_ data_32 _PL_ _R_ T,_G_ DATA_32 _PL_ _R_ S,_P_ INTE_32 L)
{
	inte_32 I=0;

	switch(L)
	{
	case 0x00000007:
		T[I]=S[I];
		I++;
	case 0x00000006:
		T[I]=S[I];
		I++;
	case 0x00000005:
		T[I]=S[I];
		I++;
	case 0x00000004:
		T[I]=S[I];
		I++;
	case 0x00000003:
		T[I]=S[I];
		I++;
	case 0x00000002:
		T[I]=S[I];
		I++;
	case 0x00000001:
		T[I]=S[I];
	default:;
	}
}
_I_ general _BitC_Taking_D64_(_P_ data_64 _PL_ _R_ T,_G_ DATA_64 _PL_ _R_ S,_P_ INTE_32 L)
{
	inte_32 I=0;

	switch(L)
	{
	case 0x00000007:
		T[I]=S[I];
		I++;
	case 0x00000006:
		T[I]=S[I];
		I++;
	case 0x00000005:
		T[I]=S[I];
		I++;
	case 0x00000004:
		T[I]=S[I];
		I++;
	case 0x00000003:
		T[I]=S[I];
		I++;
	case 0x00000002:
		T[I]=S[I];
		I++;
	case 0x00000001:
		T[I]=S[I];
	default:;
	}
}

_I_ general _BitC_Choose_D08_(_P_ point_p M,_P_ POINT_P P)
{
	M.V._02_D32[0]&=P.C._02_D32[0];
	M.V.D32[0]|=M.C.D32[1];
	M.V.D16[0]|=M.C.D16[1];
	M.V.D08[0]|=M.C.D08[1];
}
_I_ general _BitC_Choose_D16_(_P_ point_p M,_P_ POINT_P P)
{
	M.V._04_D32[0]&=P.C._04_D32[0];
	M.V._02_D32[0]|=M.C._02_D32[1];
	M.V.D32[0]|=M.C.D32[1];
	M.V.D16[0]|=M.C.D16[1];
}
_I_ general _BitC_Choose_D32_(_P_ point_p M,_P_ POINT_P P)
{
	M.V._08_D32[0]&=P.C._08_D32[0];
	M.V._04_D32[0]|=M.C._04_D32[1];
	M.V._02_D32[0]|=M.C._02_D32[1];
	M.V.D32[0]|=M.C.D32[1];
}
_I_ general _BitC_Choose_D64_(_P_ point_p M,_P_ POINT_P P)
{
	M.V._08_D64[0]&=P.C._08_D64[0];
	M.V._04_D64[0]|=M.C._04_D64[1];
	M.V._02_D64[0]|=M.C._02_D64[1];
	M.V.D64[0]|=M.C.D64[1];
}

_I_ general _BitC_RO_S_M_D08_(_P_ point_p M)
{
	M.V.D08[1]<<=1;
	M.V.D08[2]<<=2;
	M.V.D08[3]<<=3;
	M.V.D08[4]<<=4;
	M.V.D08[5]<<=5;
	M.V.D08[6]<<=6;
	M.V.D08[7]<<=7;

	M.V.D32[0]|=M.C.D32[1];
	M.V.D16[0]|=M.C.D16[1];
	M.V.D08[0]|=M.C.D08[1];
}
_I_ general _BitC_RO_S_M_D16_(_P_ point_p M)
{
	M.V.D16[1]<<=1;
	M.V.D16[2]<<=2;
	M.V.D16[3]<<=3;
	M.V.D16[4]<<=4;
	M.V.D16[5]<<=5;
	M.V.D16[6]<<=6;
	M.V.D16[7]<<=7;

	M.V._02_D32[0]|=M.C._02_D32[1];
	M.V.D32[0]|=M.C.D32[1];
	M.V.D16[0]|=M.C.D16[1];
}
_I_ general _BitC_RO_S_M_D32_(_P_ point_p M)
{
	M.V.D32[1]<<=1;
	M.V.D32[2]<<=2;
	M.V.D32[3]<<=3;
	M.V.D32[4]<<=4;
	M.V.D32[5]<<=5;
	M.V.D32[6]<<=6;
	M.V.D32[7]<<=7;

	M.V._04_D32[0]|=M.C._04_D32[1];
	M.V._02_D32[0]|=M.C._02_D32[1];
	M.V.D32[0]|=M.C.D32[1];
}
_I_ general _BitC_RO_S_M_D64_(_P_ point_p M)
{
	M.V.D64[1]<<=1;
	M.V.D64[2]<<=2;
	M.V.D64[3]<<=3;
	M.V.D64[4]<<=4;
	M.V.D64[5]<<=5;
	M.V.D64[6]<<=6;
	M.V.D64[7]<<=7;

	M.V._04_D64[0]|=M.C._04_D64[1];
	M.V._02_D64[0]|=M.C._02_D64[1];
	M.V.D64[0]|=M.C.D64[1];
}

_I_ general _BitC_RO_Rem_D08_(_P_ data_08 _PL_ _R_ M,_P_ INTE_32 S,_P_ DATA_08 C)
{
	M[1]=0xFFU;
	M[1]<<=S;
	M[1]&=C;
	M[0]|=M[1];
}
_I_ general _BitC_RO_Rem_D16_(_P_ data_16 _PL_ _R_ M,_P_ INTE_32 S,_P_ DATA_16 C)
{
	M[1]=0xFFFFU;
	M[1]<<=S;
	M[1]&=C;
	M[0]|=M[1];
}
_I_ general _BitC_RO_Rem_D32_(_P_ data_32 _PL_ _R_ M,_P_ INTE_32 S,_P_ DATA_32 C)
{
	M[1]=0xFFFFFFFFU;
	M[1]<<=S;
	M[1]&=C;
	M[0]|=M[1];
}
_I_ general _BitC_RO_Rem_D64_(_P_ data_64 _PL_ _R_ M,_P_ INTE_32 S,_P_ DATA_64 C)
{
	M[1]=0xFFFFFFFFFFFFFFFFUL;
	M[1]<<=S;
	M[1]&=C;
	M[0]|=M[1];
}

_K_ BitC_Expand_D08_(_G_ DATA_08 _PL_ _R_ DataI,_G_ data_08 _PL_ _R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index;
	_P_ data_32 Shift;
	_P_ inte_08 Temp;

	for(Index=Start;Index<Length;Index+=Step)
	{
		Shift=Index>>3;
		Temp=(inte_08)(DataI[Shift]);
		Shift=Index&0x00000007;
		Shift^=0x00000007;
		Temp<<=Shift;
		Temp>>=7;
		DataO[Index]=Temp;
	}
}
_K_ BitC_Expand_D16_(_G_ DATA_08 _PL_ _R_ DataI,_G_ data_16 _PL_ _R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index;
	_P_ data_32 Shift;
	_P_ inte_16 Temp;

	for(Index=Start;Index<Length;Index+=Step)
	{
		Shift=Index>>3;
		Temp=(inte_16)(DataI[Shift]);
		Shift=Index&0x00000007;
		Shift^=0x0000000F;
		Temp<<=Shift;
		Temp>>=15;
		DataO[Index]=Temp;
	}
}
_K_ BitC_Expand_D32_(_G_ DATA_08 _PL_ _R_ DataI,_G_ data_32 _PL_ _R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index;
	_P_ data_32 Shift;
	_P_ inte_32 Temp;

	for(Index=Start;Index<Length;Index+=Step)
	{
		Shift=Index>>3;
		Temp=(inte_32)(DataI[Shift]);
		Shift=Index&0x00000007;
		Shift^=0x0000001F;
		Temp<<=Shift;
		Temp>>=31;
		DataO[Index]=Temp;
	}
}
_K_ BitC_Expand_D64_(_G_ DATA_08 _PL_ _R_ DataI,_G_ data_64 _PL_ _R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index;
	_P_ data_32 Shift;
	_P_ inte_64 Temp;

	for(Index=Start;Index<Length;Index+=Step)
	{
		Shift=Index>>3;
		Temp=(inte_64)(DataI[Shift]);
		Shift=Index&0x00000007;
		Shift^=0x0000003F;
		Temp<<=Shift;
		Temp>>=63;
		DataO[Index]=Temp;
	}
}

_K_ BitC_Shrink_D08_(_G_ DATA_08 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_08 Table[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_08 Buff[8];
	_P_ point_p Peek;
	_P_ point_p Mask;

	{
		Peek.C.D08=Table;
		Mask.C.D08=Buff;
	}
	{
		_G_ DATA_08 _PL_ End=DataI+Safe;

		for(DataI+=Start8,DataO+=Start;DataI<End;DataI+=Step8,DataO+=Step)
		{
			Wait_L_;
			Mask.V._08_D08[0]=Vect_Load_(08,DataI);
			
			Wait_L_;
			_BitC_Choose_D08_(Mask,Peek);

			Wait_L_;
			DataO[0]=Mask.C.D08[0];
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D08_(Mask.V.D08,DataI,Margin);

			Wait_L_;
			_BitC_Choose_D08_(Mask,Peek);
			_BitC_RO_Rem_D08_(Mask.V.D08,Margin,(data_08)(DataO[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D08[0]=Vect_Load_(08,DataI);
			
			Wait_L_;
			_BitC_Choose_D08_(Mask,Peek);
		}
		{
			Wait_L_;
			DataO[0]=Mask.C.D08[0];
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_Shrink_D16_(_G_ DATA_16 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_16 Table[8]={0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080};
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_16 Buff[8];
	_P_ point_p Peek;
	_P_ point_p Mask;

	{
		Peek.C.D16=Table;
		Mask.C.D16=Buff;
	}
	{
		_G_ DATA_16 _PL_ End=DataI+Safe;

		for(DataI+=Start8,DataO+=Start;DataI<End;DataI+=Step8,DataO+=Step)
		{
			Wait_L_;
			Mask.V._08_D16[0]=Vect_Load_(08,DataI);
			
			Wait_L_;
			_BitC_Choose_D16_(Mask,Peek);

			Wait_L_;
			DataO[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D16_(Mask.V.D16,DataI,Margin);

			Wait_L_;
			_BitC_Choose_D16_(Mask,Peek);
			_BitC_RO_Rem_D16_(Mask.V.D16,Margin,(data_16)(DataO[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D16[0]=Vect_Load_(08,DataI);

			Wait_L_;
			_BitC_Choose_D16_(Mask,Peek);
		}
		{
			Wait_L_;
			DataO[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_Shrink_D32_(_G_ DATA_32 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Table[8]={0x00000001,0x00000002,0x00000004,0x00000008,0x00000010,0x00000020,0x00000040,0x00000080};
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_32 Buff[8];
	_P_ point_p Peek;
	_P_ point_p Mask;

	{
		Peek.C.D32=Table;
		Mask.C.D32=Buff;
	}
	{
		_G_ DATA_32 _PL_ End=DataI+Safe;

		for(DataI+=Start8,DataO+=Start;DataI<End;DataI+=Step8,DataO+=Step)
		{
			Wait_L_;
			Mask.V._08_D32[0]=Vect_Load_(08,DataI);

			Wait_L_;
			_BitC_Choose_D32_(Mask,Peek);

			Wait_L_;
			DataO[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			inte_32 Index;

			Wait_L_;
			_BitC_Taking_D32_(Mask.V.D32,DataI,Margin);

			Wait_L_;
			_BitC_Choose_D32_(Mask,Peek);
			_BitC_RO_Rem_D32_(Mask.V.D32,Margin,(data_32)(DataO[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D32[0]=Vect_Load_(08,DataI);

			Wait_L_;
			_BitC_Choose_D32_(Mask,Peek);
		}
		{
			Wait_L_;
			DataO[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_Shrink_D64_(_G_ DATA_64 *_R_ DataI,_G_ data_08 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_64 Table[8]={0x0000000000000001,0x0000000000000002,0x0000000000000004,0x0000000000000008,0x0000000000000010,0x0000000000000020,0x0000000000000040,0x0000000000000080};
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_64 Buff[8];
	_P_ point_p Peek;
	_P_ point_p Mask;

	{
		Peek.C.D64=Table;
		Mask.C.D64=Buff;
	}
	{
		_G_ DATA_64 _PL_ End=DataI+Safe;

		for(DataI+=Start8,DataO+=Start;DataI<End;DataI+=Step8,DataO+=Step)
		{
			Wait_L_;
			Mask.V._08_D64[0]=Vect_Load_(08,DataI);

			Wait_L_;
			_BitC_Choose_D64_(Mask,Peek);

			Wait_L_;
			DataO[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			inte_32 Index;

			Wait_L_;
			_BitC_Taking_D64_(Mask.V.D64,DataI,Margin);
			for(Index=0;Index<Margin;Index++)
				Mask.V.D64[Index]=DataI[Index];

			Wait_L_;
			_BitC_Choose_D64_(Mask,Peek);
			_BitC_RO_Rem_D64_(Mask.V.D64,Margin,(data_64)(DataO[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D64[0]=Vect_Load_(08,DataI);

			Wait_L_;
			_BitC_Choose_D64_(Mask,Peek);
		}
		{
			Wait_L_;
			DataO[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}

_K_ BitC_RO_E_1_D08_(_G_ data_08 *_R_ DataC,_G_ DATA_08 *_R_ DataA,_P_ DATA_08 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_08 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D08=Buff;
	}
	{
		_G_ DATA_08 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D08[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]==Value);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);

			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D08_(Mask.V.D08,DataA,Margin);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]==Value);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
			_BitC_RO_Rem_D08_(Mask.V.D08,Margin,(data_08)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D08[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]==Value);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_E_1_D16_(_G_ data_08 *_R_ DataC,_G_ DATA_16 *_R_ DataA,_P_ DATA_16 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_16 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D16=Buff;
	}
	{
		_G_ DATA_16 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D16[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]==Value);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D16_(Mask.V.D16,DataA,Margin);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]==Value);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
			_BitC_RO_Rem_D16_(Mask.V.D16,Margin,(data_16)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D16[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]==Value);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_E_1_D32_(_G_ data_08 *_R_ DataC,_G_ DATA_32 *_R_ DataA,_P_ DATA_32 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_32 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D32=Buff;
	}
	{
		_G_ DATA_32 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D32[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]==Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D32_(Mask.V.D32,DataA,Margin);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]==Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
			_BitC_RO_Rem_D32_(Mask.V.D32,Margin,(data_32)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D32[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]==Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_E_1_D64_(_G_ data_08 *_R_ DataC,_G_ DATA_64 *_R_ DataA,_P_ DATA_64 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_64 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D64=Buff;
	}
	{
		_G_ DATA_64 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D64[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]==Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D64_(Mask.V.D64,DataA,Margin);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]==Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
			_BitC_RO_Rem_D64_(Mask.V.D64,Margin,(data_64)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D64[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]==Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}

_K_ BitC_RO_E_2_D08_(_G_ data_08 *_R_ DataC,_G_ DATA_08 *_R_ DataA,_G_ DATA_08 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_08 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D08=Buff;
	}
	{
		_G_ DATA_08 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D08[0]=Vect_Load_(08,DataA);
			Mask.V._08_D08[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]==Mask.C._08_D08[1]);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);

			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D08_(Mask.V.D08+0,DataA,Margin);
			_BitC_Taking_D08_(Mask.V.D08+8,DataB,Margin);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]==Mask.C._08_D08[1]);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
			_BitC_RO_Rem_D08_(Mask.V.D08,Margin,(data_08)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D08[0]=Vect_Load_(08,DataA);
			Mask.V._08_D08[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]==Mask.C._08_D08[1]);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_E_2_D16_(_G_ data_08 *_R_ DataC,_G_ DATA_16 *_R_ DataA,_G_ DATA_16 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_16 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D16=Buff;
	}
	{
		_G_ DATA_16 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D16[0]=Vect_Load_(08,DataA);
			Mask.V._08_D16[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]==Mask.C._08_D16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D16_(Mask.V.D16+0,DataA,Margin);
			_BitC_Taking_D16_(Mask.V.D16+8,DataB,Margin);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]==Mask.C._08_D16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
			_BitC_RO_Rem_D16_(Mask.V.D16,Margin,(data_16)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D16[0]=Vect_Load_(08,DataA);
			Mask.V._08_D16[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]==Mask.C._08_D16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_E_2_D32_(_G_ data_08 *_R_ DataC,_G_ DATA_32 *_R_ DataA,_G_ DATA_32 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_32 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D32=Buff;
	}
	{
		_G_ DATA_32 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D32[0]=Vect_Load_(08,DataA);
			Mask.V._08_D32[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]==Mask.C._08_D32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D32_(Mask.V.D32+0,DataA,Margin);
			_BitC_Taking_D32_(Mask.V.D32+8,DataB,Margin);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]==Mask.C._08_D32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
			_BitC_RO_Rem_D32_(Mask.V.D32,Margin,(data_32)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D32[0]=Vect_Load_(08,DataA);
			Mask.V._08_D32[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]==Mask.C._08_D32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_E_2_D64_(_G_ data_08 *_R_ DataC,_G_ DATA_64 *_R_ DataA,_G_ DATA_64 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_64 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D64=Buff;
	}
	{
		_G_ DATA_64 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D64[0]=Vect_Load_(08,DataA);
			Mask.V._08_D64[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]==Mask.C._08_D64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D64_(Mask.V.D64+0,DataA,Margin);
			_BitC_Taking_D64_(Mask.V.D64+8,DataB,Margin);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]==Mask.C._08_D64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
			_BitC_RO_Rem_D64_(Mask.V.D64,Margin,(data_64)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D64[0]=Vect_Load_(08,DataA);
			Mask.V._08_D64[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]==Mask.C._08_D64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}

_K_ BitC_RO_N_1_D08_(_G_ data_08 *_R_ DataC,_G_ DATA_08 *_R_ DataA,_P_ DATA_08 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_08 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D08=Buff;
	}
	{
		_G_ DATA_08 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D08[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]!=Value);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);

			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D08_(Mask.V.D08,DataA,Margin);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]!=Value);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
			_BitC_RO_Rem_D08_(Mask.V.D08,Margin,(data_08)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D08[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]!=Value);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_N_1_D16_(_G_ data_08 *_R_ DataC,_G_ DATA_16 *_R_ DataA,_P_ DATA_16 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_16 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D16=Buff;
	}
	{
		_G_ DATA_16 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D16[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]!=Value);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D16_(Mask.V.D16,DataA,Margin);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]!=Value);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
			_BitC_RO_Rem_D16_(Mask.V.D16,Margin,(data_16)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D16[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]!=Value);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_N_1_D32_(_G_ data_08 *_R_ DataC,_G_ DATA_32 *_R_ DataA,_P_ DATA_32 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_32 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D32=Buff;
	}
	{
		_G_ DATA_32 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D32[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]!=Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D32_(Mask.V.D32,DataA,Margin);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]!=Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
			_BitC_RO_Rem_D32_(Mask.V.D32,Margin,(data_32)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D32[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]!=Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_N_1_D64_(_G_ data_08 *_R_ DataC,_G_ DATA_64 *_R_ DataA,_P_ DATA_64 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_64 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D64=Buff;
	}
	{
		_G_ DATA_64 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D64[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]!=Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D64_(Mask.V.D64,DataA,Margin);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]!=Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
			_BitC_RO_Rem_D64_(Mask.V.D64,Margin,(data_64)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D64[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]!=Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}

_K_ BitC_RO_N_2_D08_(_G_ data_08 *_R_ DataC,_G_ DATA_08 *_R_ DataA,_G_ DATA_08 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_08 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D08=Buff;
	}
	{
		_G_ DATA_08 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D08[0]=Vect_Load_(08,DataA);
			Mask.V._08_D08[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]!=Mask.C._08_D08[1]);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);

			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D08_(Mask.V.D08+0,DataA,Margin);
			_BitC_Taking_D08_(Mask.V.D08+8,DataB,Margin);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]!=Mask.C._08_D08[1]);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
			_BitC_RO_Rem_D08_(Mask.V.D08,Margin,(data_08)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D08[0]=Vect_Load_(08,DataA);
			Mask.V._08_D08[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]!=Mask.C._08_D08[1]);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_N_2_D16_(_G_ data_08 *_R_ DataC,_G_ DATA_16 *_R_ DataA,_G_ DATA_16 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_16 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D16=Buff;
	}
	{
		_G_ DATA_16 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D16[0]=Vect_Load_(08,DataA);
			Mask.V._08_D16[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]!=Mask.C._08_D16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D16_(Mask.V.D16+0,DataA,Margin);
			_BitC_Taking_D16_(Mask.V.D16+8,DataB,Margin);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]!=Mask.C._08_D16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
			_BitC_RO_Rem_D16_(Mask.V.D16,Margin,(data_16)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D16[0]=Vect_Load_(08,DataA);
			Mask.V._08_D16[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]!=Mask.C._08_D16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_N_2_D32_(_G_ data_08 *_R_ DataC,_G_ DATA_32 *_R_ DataA,_G_ DATA_32 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_32 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D32=Buff;
	}
	{
		_G_ DATA_32 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D32[0]=Vect_Load_(08,DataA);
			Mask.V._08_D32[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]!=Mask.C._08_D32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D32_(Mask.V.D32+0,DataA,Margin);
			_BitC_Taking_D32_(Mask.V.D32+8,DataB,Margin);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]!=Mask.C._08_D32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
			_BitC_RO_Rem_D32_(Mask.V.D32,Margin,(data_32)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D32[0]=Vect_Load_(08,DataA);
			Mask.V._08_D32[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]!=Mask.C._08_D32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_N_2_D64_(_G_ data_08 *_R_ DataC,_G_ DATA_64 *_R_ DataA,_G_ DATA_64 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_64 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D64=Buff;
	}
	{
		_G_ DATA_64 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D64[0]=Vect_Load_(08,DataA);
			Mask.V._08_D64[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]!=Mask.C._08_D64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D64_(Mask.V.D64+0,DataA,Margin);
			_BitC_Taking_D64_(Mask.V.D64+8,DataB,Margin);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]!=Mask.C._08_D64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
			_BitC_RO_Rem_D64_(Mask.V.D64,Margin,(data_64)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D64[0]=Vect_Load_(08,DataA);
			Mask.V._08_D64[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]!=Mask.C._08_D64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}

_K_ BitC_RO_G_1_D08_(_G_ data_08 *_R_ DataC,_G_ DATA_08 *_R_ DataA,_P_ DATA_08 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_08 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D08=Buff;
	}
	{
		_G_ DATA_08 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D08[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);

			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D08_(Mask.V.D08,DataA,Margin);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
			_BitC_RO_Rem_D08_(Mask.V.D08,Margin,(data_08)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D08[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_G_1_D16_(_G_ data_08 *_R_ DataC,_G_ DATA_16 *_R_ DataA,_P_ DATA_16 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_16 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D16=Buff;
	}
	{
		_G_ DATA_16 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D16[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D16_(Mask.V.D16,DataA,Margin);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
			_BitC_RO_Rem_D16_(Mask.V.D16,Margin,(data_16)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D16[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_G_1_D32_(_G_ data_08 *_R_ DataC,_G_ DATA_32 *_R_ DataA,_P_ DATA_32 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_32 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D32=Buff;
	}
	{
		_G_ DATA_32 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D32[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D32_(Mask.V.D32,DataA,Margin);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
			_BitC_RO_Rem_D32_(Mask.V.D32,Margin,(data_32)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D32[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_G_1_D64_(_G_ data_08 *_R_ DataC,_G_ DATA_64 *_R_ DataA,_P_ DATA_64 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_64 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D64=Buff;
	}
	{
		_G_ DATA_64 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D64[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D64_(Mask.V.D64,DataA,Margin);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
			_BitC_RO_Rem_D64_(Mask.V.D64,Margin,(data_64)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D64[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_G_1_I08_(_G_ data_08 *_R_ DataC,_G_ INTE_08 *_R_ DataA,_P_ INTE_08 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_08 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D08=Buff;
	}
	{
		_G_ INTE_08 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			//Mask.V._08_I08[0]=Vect_Load_(08,DataA);//Maybe a bug?
			Mask.V._08_D08[0]=Vect_Load_(08,(_G_ data_08*)DataA);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_I08[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);

			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D08_(Mask.V.D08,(_G_ data_08*)DataA,Margin);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_I08[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
			_BitC_RO_Rem_D08_(Mask.V.D08,Margin,(data_08)(DataC[0]));
		}
		else
		{
			Wait_L_;
			//Mask.V._08_I08[0]=Vect_Load_(08,DataA);//Maybe a bug?
			Mask.V._08_D08[0]=Vect_Load_(08,(_G_ data_08*)DataA);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_I08[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_G_1_I16_(_G_ data_08 *_R_ DataC,_G_ INTE_16 *_R_ DataA,_P_ INTE_16 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_16 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D16=Buff;
	}
	{
		_G_ INTE_16 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_I16[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_I16[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D16_(Mask.V.D16,(_G_ data_16*)DataA,Margin);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_I16[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
			_BitC_RO_Rem_D16_(Mask.V.D16,Margin,(data_16)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_I16[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_I16[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_G_1_I32_(_G_ data_08 *_R_ DataC,_G_ INTE_32 *_R_ DataA,_P_ INTE_32 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_32 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D32=Buff;
	}
	{
		_G_ INTE_32 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_I32[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_I32[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D32_(Mask.V.D32,(_G_ data_32*)DataA,Margin);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_I32[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
			_BitC_RO_Rem_D32_(Mask.V.D32,Margin,(data_32)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_I32[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_I32[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_G_1_I64_(_G_ data_08 *_R_ DataC,_G_ INTE_64 *_R_ DataA,_P_ INTE_64 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_64 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D64=Buff;
	}
	{
		_G_ INTE_64 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_I64[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_I64[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D64_(Mask.V.D64,(_G_ data_64*)DataA,Margin);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_I64[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
			_BitC_RO_Rem_D64_(Mask.V.D64,Margin,(data_64)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_I64[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_I64[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
#if(_ABLE_R16_)
_K_ BitC_RO_G_1_R16_(_G_ data_08 *_R_ DataC,_G_ REAL_16 *_R_ DataA,_P_ DATA_16 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_16 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D16=Buff;
	}
	{
		_G_ REAL_16 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_R16[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_R16[0]>=Acs_(P,real_16,Value));

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D16_(Mask.V.D16,(_G_ data_16*)DataA,Margin);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_R16[0]>=Acs_(P,real_16,Value));

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
			_BitC_RO_Rem_D16_(Mask.V.D16,Margin,(data_16)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_R16[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_R16[0]>=Acs_(P,real_16,Value));

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
#endif
_K_ BitC_RO_G_1_R32_(_G_ data_08 *_R_ DataC,_G_ REAL_32 *_R_ DataA,_P_ REAL_32 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_32 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D32=Buff;
	}
	{
		_G_ REAL_32 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_R32[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_R32[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D32_(Mask.V.D32,(_G_ data_32*)DataA,Margin);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_R32[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
			_BitC_RO_Rem_D32_(Mask.V.D32,Margin,(data_32)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_R32[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_R32[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
#if(_ABLE_R64_)
_K_ BitC_RO_G_1_R64_(_G_ data_08 *_R_ DataC,_G_ REAL_64 *_R_ DataA,_P_ REAL_64 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_64 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D64=Buff;
	}
	{
		_G_ REAL_64 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_R64[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_R64[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D64_(Mask.V.D64,(_G_ data_64*)DataA,Margin);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_R64[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
			_BitC_RO_Rem_D64_(Mask.V.D64,Margin,(data_64)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_R64[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_R64[0]>=Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
#endif

_K_ BitC_RO_G_2_D08_(_G_ data_08 *_R_ DataC,_G_ DATA_08 *_R_ DataA,_G_ DATA_08 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_08 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D08=Buff;
	}
	{
		_G_ DATA_08 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D08[0]=Vect_Load_(08,DataA);
			Mask.V._08_D08[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]>=Mask.C._08_D08[1]);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);

			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D08_(Mask.V.D08+0,DataA,Margin);
			_BitC_Taking_D08_(Mask.V.D08+8,DataB,Margin);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]>=Mask.C._08_D08[1]);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
			_BitC_RO_Rem_D08_(Mask.V.D08,Margin,(data_08)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D08[0]=Vect_Load_(08,DataA);
			Mask.V._08_D08[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]>=Mask.C._08_D08[1]);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_G_2_D16_(_G_ data_08 *_R_ DataC,_G_ DATA_16 *_R_ DataA,_G_ DATA_16 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_16 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D16=Buff;
	}
	{
		_G_ DATA_16 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D16[0]=Vect_Load_(08,DataA);
			Mask.V._08_D16[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]>=Mask.C._08_D16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D16_(Mask.V.D16+0,DataA,Margin);
			_BitC_Taking_D16_(Mask.V.D16+8,DataB,Margin);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]>=Mask.C._08_D16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
			_BitC_RO_Rem_D16_(Mask.V.D16,Margin,(data_16)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D16[0]=Vect_Load_(08,DataA);
			Mask.V._08_D16[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]>=Mask.C._08_D16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_G_2_D32_(_G_ data_08 *_R_ DataC,_G_ DATA_32 *_R_ DataA,_G_ DATA_32 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_32 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D32=Buff;
	}
	{
		_G_ DATA_32 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D32[0]=Vect_Load_(08,DataA);
			Mask.V._08_D32[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]>=Mask.C._08_D32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D32_(Mask.V.D32+0,DataA,Margin);
			_BitC_Taking_D32_(Mask.V.D32+8,DataB,Margin);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]>=Mask.C._08_D32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
			_BitC_RO_Rem_D32_(Mask.V.D32,Margin,(data_32)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D32[0]=Vect_Load_(08,DataA);
			Mask.V._08_D32[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]>=Mask.C._08_D32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_G_2_D64_(_G_ data_08 *_R_ DataC,_G_ DATA_64 *_R_ DataA,_G_ DATA_64 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_64 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D64=Buff;
	}
	{
		_G_ DATA_64 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D64[0]=Vect_Load_(08,DataA);
			Mask.V._08_D64[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]>=Mask.C._08_D64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D64_(Mask.V.D64+0,DataA,Margin);
			_BitC_Taking_D64_(Mask.V.D64+8,DataB,Margin);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]>=Mask.C._08_D64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
			_BitC_RO_Rem_D64_(Mask.V.D64,Margin,(data_64)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D64[0]=Vect_Load_(08,DataA);
			Mask.V._08_D64[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]>=Mask.C._08_D64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_G_2_I08_(_G_ data_08 *_R_ DataC,_G_ INTE_08 *_R_ DataA,_G_ INTE_08 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_08 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D08=Buff;
	}
	{
		_G_ INTE_08 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			//Mask.V._08_I08[0]=Vect_Load_(08,DataA);//Maybe a bug?
			//Mask.V._08_I08[1]=Vect_Load_(08,DataB);//Maybe a bug?
			Mask.V._08_D08[0]=Vect_Load_(08,(_G_ data_08*)DataA);
			Mask.V._08_D08[1]=Vect_Load_(08,(_G_ data_08*)DataB);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_I08[0]>=Mask.C._08_I08[1]);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);

			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D08_(Mask.V.D08+0,(_G_ data_08*)DataA,Margin);
			_BitC_Taking_D08_(Mask.V.D08+8,(_G_ data_08*)DataB,Margin);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_I08[0]>=Mask.C._08_I08[1]);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
			_BitC_RO_Rem_D08_(Mask.V.D08,Margin,(data_08)(DataC[0]));
		}
		else
		{
			Wait_L_;
			//Mask.V._08_I08[0]=Vect_Load_(08,DataA);//Maybe a bug?
			//Mask.V._08_I08[1]=Vect_Load_(08,DataB);//Maybe a bug?
			Mask.V._08_D08[0]=Vect_Load_(08,(_G_ data_08*)DataA);
			Mask.V._08_D08[1]=Vect_Load_(08,(_G_ data_08*)DataB);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_I08[0]>=Mask.C._08_I08[1]);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_G_2_I16_(_G_ data_08 *_R_ DataC,_G_ INTE_16 *_R_ DataA,_G_ INTE_16 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_16 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D16=Buff;
	}
	{
		_G_ INTE_16 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_I16[0]=Vect_Load_(08,DataA);
			Mask.V._08_I16[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_I16[0]>=Mask.C._08_I16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D16_(Mask.V.D16+0,(_G_ data_16*)DataA,Margin);
			_BitC_Taking_D16_(Mask.V.D16+8,(_G_ data_16*)DataB,Margin);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_I16[0]>=Mask.C._08_I16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
			_BitC_RO_Rem_D16_(Mask.V.D16,Margin,(data_16)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_I16[0]=Vect_Load_(08,DataA);
			Mask.V._08_I16[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_I16[0]>=Mask.C._08_I16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_G_2_I32_(_G_ data_08 *_R_ DataC,_G_ INTE_32 *_R_ DataA,_G_ INTE_32 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_32 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D32=Buff;
	}
	{
		_G_ INTE_32 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_I32[0]=Vect_Load_(08,DataA);
			Mask.V._08_I32[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_I32[0]>=Mask.C._08_I32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D32_(Mask.V.D32+0,(_G_ data_32*)DataA,Margin);
			_BitC_Taking_D32_(Mask.V.D32+8,(_G_ data_32*)DataB,Margin);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_I32[0]>=Mask.C._08_I32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
			_BitC_RO_Rem_D32_(Mask.V.D32,Margin,(data_32)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_I32[0]=Vect_Load_(08,DataA);
			Mask.V._08_I32[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_I32[0]>=Mask.C._08_I32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_G_2_I64_(_G_ data_08 *_R_ DataC,_G_ INTE_64 *_R_ DataA,_G_ INTE_64 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_64 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D64=Buff;
	}
	{
		_G_ INTE_64 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_I64[0]=Vect_Load_(08,DataA);
			Mask.V._08_I64[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_I64[0]>=Mask.C._08_I64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D64_(Mask.V.D64+0,(_G_ data_64*)DataA,Margin);
			_BitC_Taking_D64_(Mask.V.D64+8,(_G_ data_64*)DataB,Margin);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_I64[0]>=Mask.C._08_I64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
			_BitC_RO_Rem_D64_(Mask.V.D64,Margin,(data_64)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_I64[0]=Vect_Load_(08,DataA);
			Mask.V._08_I64[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_I64[0]>=Mask.C._08_I64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
#if(_ABLE_R16_)
_K_ BitC_RO_G_2_R16_(_G_ data_08 *_R_ DataC,_G_ REAL_16 *_R_ DataA,_G_ REAL_16 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_16 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D16=Buff;
	}
	{
		_G_ REAL_16 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_R16[0]=Vect_Load_(08,DataA);
			Mask.V._08_R16[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_R16[0]>=Mask.C._08_R16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D16_(Mask.V.D16+0,(_G_ data_16*)DataA,Margin);
			_BitC_Taking_D16_(Mask.V.D16+8,(_G_ data_16*)DataB,Margin);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_R16[0]>=Mask.C._08_R16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
			_BitC_RO_Rem_D16_(Mask.V.D16,Margin,(data_16)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_R16[0]=Vect_Load_(08,DataA);
			Mask.V._08_R16[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_R16[0]>=Mask.C._08_R16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
#endif
_K_ BitC_RO_G_2_R32_(_G_ data_08 *_R_ DataC,_G_ REAL_32 *_R_ DataA,_G_ REAL_32 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_32 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D32=Buff;
	}
	{
		_G_ REAL_32 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_R32[0]=Vect_Load_(08,DataA);
			Mask.V._08_R32[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_R32[0]>=Mask.C._08_R32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D32_(Mask.V.D32+0,(_G_ data_32*)DataA,Margin);
			_BitC_Taking_D32_(Mask.V.D32+8,(_G_ data_32*)DataB,Margin);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_R32[0]>=Mask.C._08_R32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
			_BitC_RO_Rem_D32_(Mask.V.D32,Margin,(data_32)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_R32[0]=Vect_Load_(08,DataA);
			Mask.V._08_R32[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_R32[0]>=Mask.C._08_R32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
#if(_ABLE_R64_)
_K_ BitC_RO_G_2_R64_(_G_ data_08 *_R_ DataC,_G_ REAL_64 *_R_ DataA,_G_ REAL_64 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_64 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D64=Buff;
	}
	{
		_G_ REAL_64 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_R64[0]=Vect_Load_(08,DataA);
			Mask.V._08_R64[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_R64[0]>=Mask.C._08_R64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D64_(Mask.V.D64+0,(_G_ data_64*)DataA,Margin);
			_BitC_Taking_D64_(Mask.V.D64+8,(_G_ data_64*)DataB,Margin);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_R64[0]>=Mask.C._08_R64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
			_BitC_RO_Rem_D64_(Mask.V.D64,Margin,(data_64)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_R64[0]=Vect_Load_(08,DataA);
			Mask.V._08_R64[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_R64[0]>=Mask.C._08_R64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
#endif

_K_ BitC_RO_L_1_D08_(_G_ data_08 *_R_ DataC,_G_ DATA_08 *_R_ DataA,_P_ DATA_08 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_08 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D08=Buff;
	}
	{
		_G_ DATA_08 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D08[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);

			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D08_(Mask.V.D08,DataA,Margin);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
			_BitC_RO_Rem_D08_(Mask.V.D08,Margin,(data_08)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D08[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_L_1_D16_(_G_ data_08 *_R_ DataC,_G_ DATA_16 *_R_ DataA,_P_ DATA_16 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_16 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D16=Buff;
	}
	{
		_G_ DATA_16 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D16[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D16_(Mask.V.D16,DataA,Margin);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
			_BitC_RO_Rem_D16_(Mask.V.D16,Margin,(data_16)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D16[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_L_1_D32_(_G_ data_08 *_R_ DataC,_G_ DATA_32 *_R_ DataA,_P_ DATA_32 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_32 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D32=Buff;
	}
	{
		_G_ DATA_32 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D32[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D32_(Mask.V.D32,DataA,Margin);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
			_BitC_RO_Rem_D32_(Mask.V.D32,Margin,(data_32)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D32[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_L_1_D64_(_G_ data_08 *_R_ DataC,_G_ DATA_64 *_R_ DataA,_P_ DATA_64 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_64 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D64=Buff;
	}
	{
		_G_ DATA_64 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D64[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D64_(Mask.V.D64,DataA,Margin);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
			_BitC_RO_Rem_D64_(Mask.V.D64,Margin,(data_64)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D64[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_L_1_I08_(_G_ data_08 *_R_ DataC,_G_ INTE_08 *_R_ DataA,_P_ INTE_08 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_08 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D08=Buff;
	}
	{
		_G_ INTE_08 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			//Mask.V._08_I08[0]=Vect_Load_(08,DataA);//Maybe a bug?
			Mask.V._08_D08[0]=Vect_Load_(08,(_G_ data_08*)DataA);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_I08[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);

			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D08_(Mask.V.D08,(_G_ data_08*)DataA,Margin);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_I08[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
			_BitC_RO_Rem_D08_(Mask.V.D08,Margin,(data_08)(DataC[0]));
		}
		else
		{
			Wait_L_;
			//Mask.V._08_I08[0]=Vect_Load_(08,DataA);//Maybe a bug?
			Mask.V._08_D08[0]=Vect_Load_(08,(_G_ data_08*)DataA);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_I08[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_L_1_I16_(_G_ data_08 *_R_ DataC,_G_ INTE_16 *_R_ DataA,_P_ INTE_16 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_16 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D16=Buff;
	}
	{
		_G_ INTE_16 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_I16[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_I16[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D16_(Mask.V.D16,(_G_ data_16*)DataA,Margin);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_I16[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
			_BitC_RO_Rem_D16_(Mask.V.D16,Margin,(data_16)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_I16[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_I16[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_L_1_I32_(_G_ data_08 *_R_ DataC,_G_ INTE_32 *_R_ DataA,_P_ INTE_32 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_32 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D32=Buff;
	}
	{
		_G_ INTE_32 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_I32[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_I32[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D32_(Mask.V.D32,(_G_ data_32*)DataA,Margin);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_I32[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
			_BitC_RO_Rem_D32_(Mask.V.D32,Margin,(data_32)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_I32[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_I32[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_L_1_I64_(_G_ data_08 *_R_ DataC,_G_ INTE_64 *_R_ DataA,_P_ INTE_64 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_64 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D64=Buff;
	}
	{
		_G_ INTE_64 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_I64[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_I64[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D64_(Mask.V.D64,(_G_ data_64*)DataA,Margin);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_I64[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
			_BitC_RO_Rem_D64_(Mask.V.D64,Margin,(data_64)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_I64[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_I64[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
#if(_ABLE_R16_)
_K_ BitC_RO_L_1_R16_(_G_ data_08 *_R_ DataC,_G_ REAL_16 *_R_ DataA,_P_ DATA_16 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_16 Buff[8];
	_P_ p_ptr_v Mask;

	{
		Mask.C.D16=Buff;
	}
	{
		_G_ REAL_16 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_R16[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_R16[0]<Acs_(P,real_16,Value));

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D16_(Mask.V.D16,(_G_ data_16*)DataA,Margin);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_R16[0]<Acs_(P,real_16,Value));

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
			_BitC_RO_Rem_D16_(Mask.V.D16,Margin,(data_16)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_R16[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_R16[0]<Acs_(P,real_16,Value));

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
#endif
_K_ BitC_RO_L_1_R32_(_G_ data_08 *_R_ DataC,_G_ REAL_32 *_R_ DataA,_P_ REAL_32 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_32 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D32=Buff;
	}
	{
		_G_ REAL_32 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_R32[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_R32[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D32_(Mask.V.D32,(_G_ data_32*)DataA,Margin);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_R32[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
			_BitC_RO_Rem_D32_(Mask.V.D32,Margin,(data_32)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_R32[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_R32[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
#if(_ABLE_R64_)
_K_ BitC_RO_L_1_R64_(_G_ data_08 *_R_ DataC,_G_ REAL_64 *_R_ DataA,_P_ REAL_64 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_64 Buff[8];
	_P_ point_p Mask;

	{
		Mask.C.D64=Buff;
	}
	{
		_G_ REAL_64 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_R64[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_R64[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D64_(Mask.V.D64,(_G_ data_64*)DataA,Margin);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_R64[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
			_BitC_RO_Rem_D64_(Mask.V.D64,Margin,(data_64)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_R64[0]=Vect_Load_(08,DataA);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_R64[0]<Value);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
#endif

_K_ BitC_RO_L_2_D08_(_G_ data_08 *_R_ DataC,_G_ DATA_08 *_R_ DataA,_G_ DATA_08 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_08 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D08=Buff;
	}
	{
		_G_ DATA_08 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			//Mask.V._08_D08[0]=Vect_Load_(08,DataA);//Maybe a bug?
			//Mask.V._08_D08[1]=Vect_Load_(08,DataB);//Maybe a bug?
			Mask.V._08_D08[0]=Vect_Load_(08,(_G_ data_08*)DataA);
			Mask.V._08_D08[1]=Vect_Load_(08,(_G_ data_08*)DataB);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]<Mask.C._08_D08[1]);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);

			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D08_(Mask.V.D08+0,DataA,Margin);
			_BitC_Taking_D08_(Mask.V.D08+8,DataB,Margin);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]<Mask.C._08_D08[1]);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
			_BitC_RO_Rem_D08_(Mask.V.D08,Margin,(data_08)(DataC[0]));
		}
		else
		{
			Wait_L_;
			//Mask.V._08_D08[0]=Vect_Load_(08,DataA);//Maybe a bug?
			//Mask.V._08_D08[1]=Vect_Load_(08,DataB);//Maybe a bug?
			Mask.V._08_D08[0]=Vect_Load_(08,(_G_ data_08*)DataA);
			Mask.V._08_D08[1]=Vect_Load_(08,(_G_ data_08*)DataB);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_D08[0]<Mask.C._08_D08[1]);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_L_2_D16_(_G_ data_08 *_R_ DataC,_G_ DATA_16 *_R_ DataA,_G_ DATA_16 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_16 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D16=Buff;
	}
	{
		_G_ DATA_16 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D16[0]=Vect_Load_(08,DataA);
			Mask.V._08_D16[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]<Mask.C._08_D16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D16_(Mask.V.D16+0,DataA,Margin);
			_BitC_Taking_D16_(Mask.V.D16+8,DataB,Margin);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]<Mask.C._08_D16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
			_BitC_RO_Rem_D16_(Mask.V.D16,Margin,(data_16)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D16[0]=Vect_Load_(08,DataA);
			Mask.V._08_D16[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_D16[0]<Mask.C._08_D16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_L_2_D32_(_G_ data_08 *_R_ DataC,_G_ DATA_32 *_R_ DataA,_G_ DATA_32 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_32 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D32=Buff;
	}
	{
		_G_ DATA_32 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D32[0]=Vect_Load_(08,DataA);
			Mask.V._08_D32[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]<Mask.C._08_D32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D32_(Mask.V.D32+0,DataA,Margin);
			_BitC_Taking_D32_(Mask.V.D32+8,DataB,Margin);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]<Mask.C._08_D32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
			_BitC_RO_Rem_D32_(Mask.V.D32,Margin,(data_32)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D32[0]=Vect_Load_(08,DataA);
			Mask.V._08_D32[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_D32[0]<Mask.C._08_D32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_L_2_D64_(_G_ data_08 *_R_ DataC,_G_ DATA_64 *_R_ DataA,_G_ DATA_64 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_64 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D64=Buff;
	}
	{
		_G_ DATA_64 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_D64[0]=Vect_Load_(08,DataA);
			Mask.V._08_D64[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]<Mask.C._08_D64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D64_(Mask.V.D64+0,DataA,Margin);
			_BitC_Taking_D64_(Mask.V.D64+8,DataB,Margin);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]<Mask.C._08_D64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
			_BitC_RO_Rem_D64_(Mask.V.D64,Margin,(data_64)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_D64[0]=Vect_Load_(08,DataA);
			Mask.V._08_D64[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_D64[0]<Mask.C._08_D64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_L_2_I08_(_G_ data_08 *_R_ DataC,_G_ INTE_08 *_R_ DataA,_G_ INTE_08 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_08 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D08=Buff;
	}
	{
		_G_ INTE_08 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			//Mask.V._08_I08[0]=Vect_Load_(08,DataA);//Maybe a bug?
			//Mask.V._08_I08[1]=Vect_Load_(08,DataB);//Maybe a bug?
			Mask.V._08_D08[0]=Vect_Load_(08,(_G_ data_08*)DataA);
			Mask.V._08_D08[1]=Vect_Load_(08,(_G_ data_08*)DataB);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_I08[0]<Mask.C._08_I08[1]);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);

			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D08_(Mask.V.D08+0,(_G_ data_08*)DataA,Margin);
			_BitC_Taking_D08_(Mask.V.D08+8,(_G_ data_08*)DataB,Margin);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_I08[0]<Mask.C._08_I08[1]);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
			_BitC_RO_Rem_D08_(Mask.V.D08,Margin,(data_08)(DataC[0]));
		}
		else
		{
			Wait_L_;
			//Mask.V._08_I08[0]=Vect_Load_(08,DataA);//Maybe a bug?
			//Mask.V._08_I08[1]=Vect_Load_(08,DataB);//Maybe a bug?
			Mask.V._08_D08[0]=Vect_Load_(08,(_G_ data_08*)DataA);
			Mask.V._08_D08[1]=Vect_Load_(08,(_G_ data_08*)DataB);

			Wait_L_;
			Mask.V._08_I08[0]=(Mask.C._08_I08[0]<Mask.C._08_I08[1]);

			Wait_L_;
			_BitC_RO_S_M_D08_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=Mask.C.D08[0];
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_L_2_I16_(_G_ data_08 *_R_ DataC,_G_ INTE_16 *_R_ DataA,_G_ INTE_16 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_16 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D16=Buff;
	}
	{
		_G_ INTE_16 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_I16[0]=Vect_Load_(08,DataA);
			Mask.V._08_I16[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_I16[0]<Mask.C._08_I16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D16_(Mask.V.D16+0,(_G_ data_16*)DataA,Margin);
			_BitC_Taking_D16_(Mask.V.D16+8,(_G_ data_16*)DataB,Margin);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_I16[0]<Mask.C._08_I16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
			_BitC_RO_Rem_D16_(Mask.V.D16,Margin,(data_16)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_I16[0]=Vect_Load_(08,DataA);
			Mask.V._08_I16[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_I16[0]<Mask.C._08_I16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_L_2_I32_(_G_ data_08 *_R_ DataC,_G_ INTE_32 *_R_ DataA,_G_ INTE_32 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_32 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D32=Buff;
	}
	{
		_G_ INTE_32 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_I32[0]=Vect_Load_(08,DataA);
			Mask.V._08_I32[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_I32[0]<Mask.C._08_I32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D32_(Mask.V.D32+0,(_G_ data_32*)DataA,Margin);
			_BitC_Taking_D32_(Mask.V.D32+8,(_G_ data_32*)DataB,Margin);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_I32[0]<Mask.C._08_I32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
			_BitC_RO_Rem_D32_(Mask.V.D32,Margin,(data_32)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_I32[0]=Vect_Load_(08,DataA);
			Mask.V._08_I32[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_I32[0]<Mask.C._08_I32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
_K_ BitC_RO_L_2_I64_(_G_ data_08 *_R_ DataC,_G_ INTE_64 *_R_ DataA,_G_ INTE_64 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_64 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D64=Buff;
	}
	{
		_G_ INTE_64 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_I64[0]=Vect_Load_(08,DataA);
			Mask.V._08_I64[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_I64[0]<Mask.C._08_I64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D64_(Mask.V.D64+0,(_G_ data_64*)DataA,Margin);
			_BitC_Taking_D64_(Mask.V.D64+8,(_G_ data_64*)DataB,Margin);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_I64[0]<Mask.C._08_I64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
			_BitC_RO_Rem_D64_(Mask.V.D64,Margin,(data_64)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_I64[0]=Vect_Load_(08,DataA);
			Mask.V._08_I64[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_I64[0]<Mask.C._08_I64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
#if(_ABLE_R16_)
_K_ BitC_RO_L_2_R16_(_G_ data_08 *_R_ DataC,_G_ REAL_16 *_R_ DataA,_G_ REAL_16 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_16 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D16=Buff;
	}
	{
		_G_ REAL_16 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_R16[0]=Vect_Load_(08,DataA);
			Mask.V._08_R16[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_R16[0]<Mask.C._08_R16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D16_(Mask.D16+0,(_G_ data_16*)DataA,Margin);
			_BitC_Taking_D16_(Mask.D16+8,(_G_ data_16*)DataB,Margin);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_R16[0]<Mask.C._08_R16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
			_BitC_RO_Rem_D16_(Mask.V.D16,Margin,(data_16)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_R16[0]=Vect_Load_(08,DataA);
			Mask.V._08_R16[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I16[0]=(Mask.C._08_R16[0]<Mask.C._08_R16[1]);

			Wait_L_;
			_BitC_RO_S_M_D16_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D16[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
#endif
_K_ BitC_RO_L_2_R32_(_G_ data_08 *_R_ DataC,_G_ REAL_32 *_R_ DataA,_G_ REAL_32 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_32 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D32=Buff;
	}
	{
		_G_ REAL_32 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_R32[0]=Vect_Load_(08,DataA);
			Mask.V._08_R32[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_R32[0]<Mask.C._08_R32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D32_(Mask.V.D32+0,(_G_ data_32*)DataA,Margin);
			_BitC_Taking_D32_(Mask.V.D32+8,(_G_ data_32*)DataB,Margin);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_R32[0]<Mask.C._08_R32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
			_BitC_RO_Rem_D32_(Mask.V.D32,Margin,(data_32)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_R32[0]=Vect_Load_(08,DataA);
			Mask.V._08_R32[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I32[0]=(Mask.C._08_R32[0]<Mask.C._08_R32[1]);

			Wait_L_;
			_BitC_RO_S_M_D32_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D32[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
#if(_ABLE_R64_)
_K_ BitC_RO_L_2_R64_(_G_ data_08 *_R_ DataC,_G_ REAL_64 *_R_ DataA,_G_ REAL_64 *_R_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start8=Start<<3;
	_P_ DATA_32 Step8=Step<<3;
	_P_ DATA_32 Rest=Length%Step8;
	_P_ DATA_32 Safe=Length-Rest;
	_P_ data_64 Buff[16];
	_P_ point_p Mask;

	{
		Mask.C.D64=Buff;
	}
	{
		_G_ REAL_64 _PL_ End=DataA+Safe;

		for(DataA+=Start8,DataB+=Start8,DataC+=Start;DataA<End;DataA+=Step8,DataB+=Step8,DataC+=Step)
		{
			Wait_L_;
			Mask.V._08_R64[0]=Vect_Load_(08,DataA);
			Mask.V._08_R64[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_R64[0]<Mask.C._08_R64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);

			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	if(Start8<Rest)
	{
		INTE_32 Margin=Rest-Start8;

		if(Margin<8)
		{
			Wait_L_;
			_BitC_Taking_D64_(Mask.V.D64+0,(_G_ data_64*)DataA,Margin);
			_BitC_Taking_D64_(Mask.V.D64+8,(_G_ data_64*)DataB,Margin);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_R64[0]<Mask.C._08_R64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
			_BitC_RO_Rem_D64_(Mask.V.D64,Margin,(data_64)(DataC[0]));
		}
		else
		{
			Wait_L_;
			Mask.V._08_R64[0]=Vect_Load_(08,DataA);
			Mask.V._08_R64[1]=Vect_Load_(08,DataB);

			Wait_L_;
			Mask.V._08_I64[0]=(Mask.C._08_R64[0]<Mask.C._08_R64[1]);

			Wait_L_;
			_BitC_RO_S_M_D64_(Mask);
		}
		{
			Wait_L_;
			DataC[0]=(data_08)(Mask.C.D64[0]);
		}
	}
	else
	{
		Wait_L_;
		Wait_L_;
		Wait_L_;
		Wait_L_;
	}
}
#endif
#endif
