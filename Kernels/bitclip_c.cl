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
#if(_ABLE_I64_)
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
#if(_ABLE_I64_)
_K_ BitC_Caster_D08_D64_(_G_ DATA_08 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_08 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_64)(DataI[0]);
}
#endif
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
#if(_ABLE_I64_)
_K_ BitC_Caster_D16_D64_(_G_ DATA_16 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_64)(DataI[0]);
}
#endif
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
#if(_ABLE_I64_)
_K_ BitC_Caster_D32_D64_(_G_ DATA_32 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_64)(DataI[0]);
}
#endif
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
#if(_ABLE_I64_)
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
#if(_ABLE_I64_)
_K_ BitC_Caster_I08_D64_(_G_ INTE_08 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_08 Min=0x00;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_08 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_64)max(DataI[0],Min);
}
#endif
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
#if(_ABLE_I64_)
_K_ BitC_Caster_I08_I64_(_G_ INTE_08 *_R_ DataI,_G_ inte_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_08 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_64)(DataI[0]);
}
#endif
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
#if(_ABLE_I64_)
_K_ BitC_Caster_I16_D64_(_G_ INTE_16 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_16 Min=0x0000;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_64)max(DataI[0],Min);
}
#endif
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
#if(_ABLE_I64_)
_K_ BitC_Caster_I16_I64_(_G_ INTE_16 *_R_ DataI,_G_ inte_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_16 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_64)(DataI[0]);
}
#endif
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
#if(_ABLE_I64_)
_K_ BitC_Caster_I32_D64_(_G_ INTE_32 *_R_ DataI,_G_ data_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ INTE_32 Min=0x00000000;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(data_64)max(DataI[0],Min);
}
#endif
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
#if(_ABLE_I64_)
_K_ BitC_Caster_I32_I64_(_G_ INTE_32 *_R_ DataI,_G_ inte_64 *_R_ DataO,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ INTE_32 _PL_ End=DataI+Length;

	for(DataI+=Start,DataO+=Start;DataI<End;DataI+=Step,DataO+=Step)
		DataO[0]=(inte_64)(DataI[0]);
}
#endif
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
#if(_ABLE_I64_)
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
#if(_ABLE_I64_)
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
#endif
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
#if(_ABLE_I64_)
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
#endif
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
#if(_ABLE_I64_)
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
#endif
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
#if(_ABLE_I64_)
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
#endif
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
#if(_ABLE_I64_)
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
#endif
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
#if(_ABLE_I64_)
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
#endif
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
	_P_ g_ptr_c End;
	_P_ g_ptr_c PtrA;
	_P_ g_ptr_v PtrC;

	{
		RestOld=Length;
		RestNew=Length%(Step<<2);
		End.D08=DataA+(RestOld-RestNew);
	}
	for(PtrA.D08=DataA,PtrC.D08=DataC;PtrA.G<End.G;PtrA.D32+=Step,PtrC.D32+=Step)
		PtrC.D32[Start]=~(PtrA.D32[Start]);
	{
		RestOld=RestNew;
		RestNew%=(Step<<1);
	}
	if(RestNew<RestOld)
	{
		PtrC.D16[Start]=~(PtrA.D16[Start]);

		PtrA.D16+=Step;
		PtrC.D16+=Step;
	}
	{
		RestOld=RestNew;
		RestNew%=Step;
	}
	if(RestNew<RestOld)
	{
		PtrC.D08[Start]=~(PtrA.D08[Start]);

		PtrA.D08+=Step;
		PtrC.D08+=Step;
	}
	if(Start<RestNew)
		PtrC.D08[Start]=~(PtrA.D08[Start]);
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
#if(_ABLE_I64_)
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
#endif
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
#if(_ABLE_I64_)
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
#endif

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
#if(_ABLE_I64_)
_K_ BitC_BO_A_1_D64_(_G_ data_64* DataC,_G_ DATA_64* DataA,_P_ DATA_64 Mask,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_64 _PL_ End=DataA+Length;

	for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
		DataC[0]=DataA[0]&Mask;
}
#endif
_K_ BitC_BO_A_2_D08_(_G_ data_08 _PL_ DataC,_G_ DATA_08 _PL_ DataA,_G_ DATA_08 _PL_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 RestOld;
	_P_ data_32 RestNew;
	_P_ g_ptr_c End;
	_P_ g_ptr_c PtrA;
	_P_ g_ptr_c PtrB;
	_P_ g_ptr_v PtrC;

	{
		RestOld=Length;
		RestNew=Length%(Step<<2);
		End.D08=DataA+(RestOld-RestNew);
	}
	for(PtrA.D08=DataA,PtrB.D08=DataB,PtrC.D08=DataC;PtrA.G<End.G;PtrA.D32+=Step,PtrB.D32+=Step,PtrC.D32+=Step)
		PtrC.D32[Start]=PtrA.D32[Start]&PtrB.D32[Start];
	{
		RestOld=RestNew;
		RestNew%=(Step<<1);
	}
	if(RestNew<RestOld)
	{
		PtrC.D16[Start]=PtrA.D16[Start]&PtrB.D16[Start];

		PtrA.D16+=Step;
		PtrB.D16+=Step;
		PtrC.D16+=Step;
	}
	{
		RestOld=RestNew;
		RestNew%=Step;
	}
	if(RestNew<RestOld)
	{
		PtrC.D08[Start]=PtrA.D08[Start]&PtrB.D08[Start];

		PtrA.D08+=Step;
		PtrB.D08+=Step;
		PtrC.D08+=Step;
	}
	if(Start<RestNew)
		PtrC.D08[Start]=PtrA.D08[Start]&PtrB.D08[Start];
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
#if(_ABLE_I64_)
_K_ BitC_BO_O_1_D64_(_G_ data_64* DataC,_G_ DATA_64* DataA,_P_ DATA_64 Mask,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_64 _PL_ End=DataA+Length;

	for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
		DataC[0]=DataA[0]|Mask;
}
#endif
_K_ BitC_BO_O_2_D08_(_G_ data_08 _PL_ DataC,_G_ DATA_08 _PL_ DataA,_G_ DATA_08 _PL_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 RestOld;
	_P_ data_32 RestNew;
	_P_ g_ptr_c End;
	_P_ g_ptr_c PtrA;
	_P_ g_ptr_c PtrB;
	_P_ g_ptr_v PtrC;

	{
		RestOld=Length;
		RestNew=Length%(Step<<2);
		End.D08=DataA+(RestOld-RestNew);
	}
	for(PtrA.D08=DataA,PtrB.D08=DataB,PtrC.D08=DataC;PtrA.G<End.G;PtrA.D32+=Step,PtrB.D32+=Step,PtrC.D32+=Step)
		PtrC.D32[Start]=PtrA.D32[Start]|PtrB.D32[Start];
	{
		RestOld=RestNew;
		RestNew%=(Step<<1);
	}
	if(RestNew<RestOld)
	{
		PtrC.D16[Start]=PtrA.D16[Start]|PtrB.D16[Start];

		PtrA.D16+=Step;
		PtrB.D16+=Step;
		PtrC.D16+=Step;
	}
	{
		RestOld=RestNew;
		RestNew%=Step;
	}
	if(RestNew<RestOld)
	{
		PtrC.D08[Start]=PtrA.D08[Start]|PtrB.D08[Start];

		PtrA.D08+=Step;
		PtrB.D08+=Step;
		PtrC.D08+=Step;
	}
	if(Start<RestNew)
		PtrC.D08[Start]=PtrA.D08[Start]|PtrB.D08[Start];
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
#if(_ABLE_I64_)
_K_ BitC_BO_X_1_D64_(_G_ data_64* DataC,_G_ DATA_64* DataA,_P_ DATA_64 Mask,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_G_ DATA_64 _PL_ End=DataA+Length;

	for(DataA+=Start,DataC+=Start;DataA<End;DataA+=Step,DataC+=Step)
		DataC[0]=DataA[0]^Mask;
}
#endif
_K_ BitC_BO_X_2_D08_(_G_ data_08 _PL_ DataC,_G_ DATA_08 _PL_ DataA,_G_ DATA_08 _PL_ DataB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 RestOld;
	_P_ data_32 RestNew;
	_P_ g_ptr_c End;
	_P_ g_ptr_c PtrA;
	_P_ g_ptr_c PtrB;
	_P_ g_ptr_v PtrC;

	{
		RestOld=Length;
		RestNew=Length%(Step<<2);
		End.D08=DataA+(RestOld-RestNew);
	}
	for(PtrA.D08=DataA,PtrB.D08=DataB,PtrC.D08=DataC;PtrA.G<End.G;PtrA.D32+=Step,PtrB.D32+=Step,PtrC.D32+=Step)
		PtrC.D32[Start]=PtrA.D32[Start]^PtrB.D32[Start];
	{
		RestOld=RestNew;
		RestNew%=(Step<<1);
	}
	if(RestNew<RestOld)
	{
		PtrC.D16[Start]=PtrA.D16[Start]^PtrB.D16[Start];

		PtrA.D16+=Step;
		PtrB.D16+=Step;
		PtrC.D16+=Step;
	}
	{
		RestOld=RestNew;
		RestNew%=Step;
	}
	if(RestNew<RestOld)
	{
		PtrC.D08[Start]=PtrA.D08[Start]^PtrB.D08[Start];

		PtrA.D08+=Step;
		PtrB.D08+=Step;
		PtrC.D08+=Step;
	}
	if(Start<RestNew)
		PtrC.D08[Start]=PtrA.D08[Start]^PtrB.D08[Start];
}
#endif
