/*------------------------------------------------------------------*/
/*	LinClip's OpenCL Source Parts.									*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2018.07.20	*/
/*------------------------------------------------------------------*/
/*	OpenCL Support													*/
/*	http://www.khronos.org/opencl/									*/
/*------------------------------------------------------------------*/

#if(Fold_(Definition:Arithmetic Progression Functions))
_K_ LinC_Ari_0_I08_(_G_ inte_08 _PL_ Line,_P_ INTE_08 VStart,_P_ INTE_08 VStep,_P_ DATA_32 Length)
{
	_P_ DATA_32 IStep=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;
	_P_ inte_08 Temp;

	for(;Index<Length;Index+=IStep)
	{
		Temp=(_P_ inte_08)Index;
		Temp*=VStep;
		Temp+=VStart;

		Line[Index]=Temp;
	}
}
_K_ LinC_Ari_0_I16_(_G_ inte_16 _PL_ Line,_P_ INTE_16 VStart,_P_ INTE_16 VStep,_P_ DATA_32 Length)
{
	_P_ DATA_32 IStep=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;
	_P_ inte_16 Temp;

	for(;Index<Length;Index+=IStep)
	{
		Temp=(_P_ inte_16)Index;
		Temp*=VStep;
		Temp+=VStart;

		Line[Index]=Temp;
	}
}
_K_ LinC_Ari_0_I32_(_G_ inte_32 _PL_ Line,_P_ INTE_32 VStart,_P_ INTE_32 VStep,_P_ DATA_32 Length)
{
	_P_ DATA_32 IStep=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;
	_P_ inte_32 Temp;

	for(;Index<Length;Index+=IStep)
	{
		Temp=(_P_ inte_32)Index;
		Temp*=VStep;
		Temp+=VStart;

		Line[Index]=Temp;
	}
}
#if(_ABLE_I64_)
_K_ LinC_Ari_0_I64_(_G_ inte_64 _PL_ Line,_P_ INTE_64 VStart,_P_ INTE_64 VStep,_P_ DATA_32 Length)
{
	_P_ DATA_32 IStep=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;
	_P_ inte_64 Temp;

	for(;Index<Length;Index+=IStep)
	{
		Temp=(_P_ inte_64)Index;
		Temp*=VStep;
		Temp+=VStart;

		Line[Index]=Temp;
	}
}
#endif
#if(_ABLE_R16_)
_K_ LinC_Ari_0_R16_(_G_ real_16 _PL_ Line,_P_ INTE_16 VStart,_P_ INTE_16 VStep,_P_ DATA_32 Length)
{
	_P_ DATA_32 IStep=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;
	_P_ real_16 Temp;

	for(;Index<Length;Index+=IStep)
	{
		Temp=(_P_ real_16)Index;
		Temp*=Acs_(P,real_16,VStep);
		Temp+=Acs_(P,real_16,VStart);

		Line[Index]=Temp;
	}
}
#endif
_K_ LinC_Ari_0_R32_(_G_ real_32 _PL_ Line,_P_ REAL_32 VStart,_P_ REAL_32 VStep,_P_ DATA_32 Length)
{
	_P_ DATA_32 IStep=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;
	_P_ real_32 Temp;

	for(;Index<Length;Index+=IStep)
	{
		Temp=(_P_ real_32)Index;
		Temp*=VStep;
		Temp+=VStart;

		Line[Index]=Temp;
	}
}
#if(_ABLE_R64_)
_K_ LinC_Ari_0_R64_(_G_ real_64 _PL_ Line,_P_ REAL_64 VStart,_P_ REAL_64 VStep,_P_ DATA_32 Length)
{
	_P_ DATA_32 IStep=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;
	_P_ real_64 Temp;

	for(;Index<Length;Index+=IStep)
	{
		Temp=(_P_ real_64)Index;
		Temp*=VStep;
		Temp+=VStart;

		Line[Index]=Temp;
	}
}
#endif
#endif
#if(Fold_(Definition:Geometric Progression Functions))
_I_ _P_ data_32 _LinC_Length_Bits_(_P_ data_32 Temp)
{
	Temp--;
	Temp|=(Temp>>1);
	Temp|=(Temp>>2);
	Temp|=(Temp>>4);
	Temp|=(Temp>>8);
	Temp|=(Temp>>16);
	Temp=popcount(Temp);

	return Temp;
}
_K_ LinC_Geo_0_I08_(_G_ inte_08 _PL_ Line,_P_ INTE_08 VStart,_P_ INTE_08 VStep,_P_ DATA_32 Length)
{
	_P_ DATA_32 IStep=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;
	_P_ inte_08 VTable[32];
	_P_ INTE_08 _PL_ End=VTable+_LinC_Length_Bits_(Length);
	_P_ inte_08 *Ptr;
	_P_ inte_08 Temp[4];
	_P_ data_32 Local;

	for(VTable[0]=VStep,Ptr=VTable+1;Ptr<End;Ptr++)
		Ptr[0]=Ptr[-1]*Ptr[-1];

	for(;Index<Length;Index+=IStep)
	{
		for(Ptr=VTable,Local=Index,Temp[0]=VStart;Ptr<End;Ptr++,Local>>=1)
		{
			Temp[1]=(_P_ inte_08)(Local&0x00000001);

			Temp[2]=-Temp[1];
			Temp[3]=Temp[1]^0x01;

			Temp[1]=Ptr[0]&Temp[2];
			Temp[1]|=Temp[3];

			Temp[0]*=Temp[1];
		}
		Line[Index]=Temp[0];
	}
}
_K_ LinC_Geo_0_I16_(_G_ inte_16 _PL_ Line,_P_ INTE_16 VStart,_P_ INTE_16 VStep,_P_ DATA_32 Length)
{
	_P_ DATA_32 IStep=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;
	_P_ inte_16 VTable[32];
	_P_ INTE_16 _PL_ End=VTable+_LinC_Length_Bits_(Length);
	_P_ inte_16 *Ptr;
	_P_ inte_16 Temp[4];
	_P_ data_32 Local;

	for(VTable[0]=VStep,Ptr=VTable+1;Ptr<End;Ptr++)
		Ptr[0]=Ptr[-1]*Ptr[-1];

	for(;Index<Length;Index+=IStep)
	{
		for(Ptr=VTable,Local=Index,Temp[0]=VStart;Ptr<End;Ptr++,Local>>=1)
		{
			Temp[1]=(_P_ inte_16)(Local&0x00000001);

			Temp[2]=-Temp[1];
			Temp[3]=Temp[1]^0x0001;

			Temp[1]=Ptr[0]&Temp[2];
			Temp[1]|=Temp[3];

			Temp[0]*=Temp[1];
		}
		Line[Index]=Temp[0];
	}
}
_K_ LinC_Geo_0_I32_(_G_ inte_32 _PL_ Line,_P_ INTE_32 VStart,_P_ INTE_32 VStep,_P_ DATA_32 Length)
{
	_P_ DATA_32 IStep=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;
	_P_ inte_32 VTable[32];
	_P_ INTE_32 _PL_ End=VTable+_LinC_Length_Bits_(Length);
	_P_ inte_32 *Ptr;
	_P_ inte_32 Temp[4];
	_P_ data_32 Local;

	for(VTable[0]=VStep,Ptr=VTable+1;Ptr<End;Ptr++)
		Ptr[0]=Ptr[-1]*Ptr[-1];

	for(;Index<Length;Index+=IStep)
	{
		for(Ptr=VTable,Local=Index,Temp[0]=VStart;Ptr<End;Ptr++,Local>>=1)
		{
			Temp[1]=(_P_ inte_32)(Local&0x00000001);

			Temp[2]=-Temp[1];
			Temp[3]=Temp[1]^0x00000001;

			Temp[1]=Ptr[0]&Temp[2];
			Temp[1]|=Temp[3];

			Temp[0]*=Temp[1];
		}
		Line[Index]=Temp[0];
	}
}
#if(_ABLE_I64_)
_K_ LinC_Geo_0_I64_(_G_ inte_64 _PL_ Line,_P_ INTE_64 VStart,_P_ INTE_64 VStep,_P_ DATA_32 Length)
{
	_P_ DATA_32 IStep=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;
	_P_ inte_64 VTable[32];
	_P_ INTE_64 _PL_ End=VTable+_LinC_Length_Bits_(Length);
	_P_ inte_64 *Ptr;
	_P_ inte_64 Temp[4];
	_P_ data_32 Local;

	for(VTable[0]=VStep,Ptr=VTable+1;Ptr<End;Ptr++)
		Ptr[0]=Ptr[-1]*Ptr[-1];

	for(;Index<Length;Index+=IStep)
	{
		for(Ptr=VTable,Local=Index,Temp[0]=VStart;Ptr<End;Ptr++,Local>>=1)
		{
			Temp[1]=(_P_ inte_64)(Local&0x00000001);

			Temp[2]=-Temp[1];
			Temp[3]=Temp[1]^0x0000000000000001;

			Temp[1]=Ptr[0]&Temp[2];
			Temp[1]|=Temp[3];

			Temp[0]*=Temp[1];
		}
		Line[Index]=Temp[0];
	}
}
#endif
#if(_ABLE_R16_)
_K_ LinC_Geo_0_R16_(_G_ real_16 _PL_ Line,_P_ INTE_16 VStart,_P_ INTE_16 VStep,_P_ DATA_32 Length)
{
	_P_ DATA_32 IStep=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=IStep)
		Line[Index]=Acs_(P,real_16,VStart)*pown(Acs_(P,real_16,VStep),Index);
}
#endif
_K_ LinC_Geo_0_R32_(_G_ real_32 _PL_ Line,_P_ REAL_32 VStart,_P_ REAL_32 VStep,_P_ DATA_32 Length)
{
	_P_ DATA_32 IStep=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=IStep)
		Line[Index]=VStart*pown(VStep,Index);
}
#if(_ABLE_R64_)
_K_ LinC_Geo_0_R64_(_G_ real_64 _PL_ Line,_P_ REAL_64 VStart,_P_ REAL_64 VStep,_P_ DATA_32 Length)
{
	_P_ DATA_32 IStep=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=IStep)
		Line[Index]=VStart*pown(VStep,Index);
}
#endif
#endif
#if(Fold_(Definition:Increment Functions))
_K_ LinC_Inc_1_I08_(_G_ inte_08 _PL_ LineC,_G_ INTE_08 _PL_ LineA,_P_ INTE_08 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]+Value;
}
_K_ LinC_Inc_1_I16_(_G_ inte_16 _PL_ LineC,_G_ INTE_16 _PL_ LineA,_P_ INTE_16 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]+Value;
}
_K_ LinC_Inc_1_I32_(_G_ inte_32 _PL_ LineC,_G_ INTE_32 _PL_ LineA,_P_ INTE_32 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]+Value;
}
#if(_ABLE_I64_)
_K_ LinC_Inc_1_I64_(_G_ inte_64 _PL_ LineC,_G_ INTE_64 _PL_ LineA,_P_ INTE_64 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]+Value;
}
#endif
#if(_ABLE_R16_)
_K_ LinC_Inc_1_R16_(_G_ real_16 _PL_ LineC,_G_ REAL_16 _PL_ LineA,_P_ INTE_16 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]+Acs_(P,real_16,Value);
}
#endif
_K_ LinC_Inc_1_R32_(_G_ real_32 _PL_ LineC,_G_ REAL_32 _PL_ LineA,_P_ REAL_32 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]+Value;
}
#if(_ABLE_R64_)
_K_ LinC_Inc_1_R64_(_G_ real_64 _PL_ LineC,_G_ REAL_64 _PL_ LineA,_P_ REAL_64 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]+Value;
}
#endif
#endif
#if(Fold_(Definition:Amplification Functions))
_K_ LinC_Amp_1_I08_(_G_ inte_08 _PL_ LineC,_G_ INTE_08 _PL_ LineA,_P_ INTE_08 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]*Value;
}
_K_ LinC_Amp_1_I16_(_G_ inte_16 _PL_ LineC,_G_ INTE_16 _PL_ LineA,_P_ INTE_16 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]*Value;
}
_K_ LinC_Amp_1_I32_(_G_ inte_32 _PL_ LineC,_G_ INTE_32 _PL_ LineA,_P_ INTE_32 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]*Value;
}
#if(_ABLE_I64_)
_K_ LinC_Amp_1_I64_(_G_ inte_64 _PL_ LineC,_G_ INTE_64 _PL_ LineA,_P_ INTE_64 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]*Value;
}
#endif
#if(_ABLE_R16_)
_K_ LinC_Amp_1_R16_(_G_ real_16 _PL_ LineC,_G_ REAL_16 _PL_ LineA,_P_ INTE_16 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]*Acs_(P,real_16,Value);
}
#endif
_K_ LinC_Amp_1_R32_(_G_ real_32 _PL_ LineC,_G_ REAL_32 _PL_ LineA,_P_ REAL_32 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]*Value;
}
#if(_ABLE_R64_)
_K_ LinC_Amp_1_R64_(_G_ real_64 _PL_ LineC,_G_ REAL_64 _PL_ LineA,_P_ REAL_64 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]*Value;
}
#endif
#endif
#if(Fold_(Definition:Addition Functions))
_K_ LinC_Add_2_I08_(_G_ inte_08 _PL_ LineC,_G_ INTE_08 _PL_ LineA,_G_ INTE_08 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]+LineB[Index];
}
_K_ LinC_Add_2_I16_(_G_ inte_16 _PL_ LineC,_G_ INTE_16 _PL_ LineA,_G_ INTE_16 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]+LineB[Index];
}
_K_ LinC_Add_2_I32_(_G_ inte_32 _PL_ LineC,_G_ INTE_32 _PL_ LineA,_G_ INTE_32 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]+LineB[Index];
}
#if(_ABLE_I64_)
_K_ LinC_Add_2_I64_(_G_ inte_64 _PL_ LineC,_G_ INTE_64 _PL_ LineA,_G_ INTE_64 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]+LineB[Index];
}
#endif
#if(_ABLE_R16_)
_K_ LinC_Add_2_R16_(_G_ real_16 _PL_ LineC,_G_ REAL_16 _PL_ LineA,_G_ REAL_16 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]+LineB[Index];
}
#endif
_K_ LinC_Add_2_R32_(_G_ real_32 _PL_ LineC,_G_ REAL_32 _PL_ LineA,_G_ REAL_32 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]+LineB[Index];
}
#if(_ABLE_R64_)
_K_ LinC_Add_2_R64_(_G_ real_64 _PL_ LineC,_G_ REAL_64 _PL_ LineA,_G_ REAL_64 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]+LineB[Index];
}
#endif
#endif
#if(Fold_(Definition:Subtraction Functions))
_K_ LinC_Sub_2_I08_(_G_ inte_08 _PL_ LineC,_G_ INTE_08 _PL_ LineA,_G_ INTE_08 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]-LineB[Index];
}
_K_ LinC_Sub_2_I16_(_G_ inte_16 _PL_ LineC,_G_ INTE_16 _PL_ LineA,_G_ INTE_16 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]-LineB[Index];
}
_K_ LinC_Sub_2_I32_(_G_ inte_32 _PL_ LineC,_G_ INTE_32 _PL_ LineA,_G_ INTE_32 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]-LineB[Index];
}
#if(_ABLE_I64_)
_K_ LinC_Sub_2_I64_(_G_ inte_64 _PL_ LineC,_G_ INTE_64 _PL_ LineA,_G_ INTE_64 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]-LineB[Index];
}
#endif
#if(_ABLE_R16_)
_K_ LinC_Sub_2_R16_(_G_ real_16 _PL_ LineC,_G_ REAL_16 _PL_ LineA,_G_ REAL_16 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]-LineB[Index];
}
#endif
_K_ LinC_Sub_2_R32_(_G_ real_32 _PL_ LineC,_G_ REAL_32 _PL_ LineA,_G_ REAL_32 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]-LineB[Index];
}
#if(_ABLE_R64_)
_K_ LinC_Sub_2_R64_(_G_ real_64 _PL_ LineC,_G_ REAL_64 _PL_ LineA,_G_ REAL_64 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]-LineB[Index];
}
#endif
#endif
#if(Fold_(Definition:Multiplication Functions))
_K_ LinC_Mul_2_I08_(_G_ inte_08 _PL_ LineC,_G_ INTE_08 _PL_ LineA,_G_ INTE_08 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]*LineB[Index];
}
_K_ LinC_Mul_2_I16_(_G_ inte_16 _PL_ LineC,_G_ INTE_16 _PL_ LineA,_G_ INTE_16 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]*LineB[Index];
}
_K_ LinC_Mul_2_I32_(_G_ inte_32 _PL_ LineC,_G_ INTE_32 _PL_ LineA,_G_ INTE_32 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]*LineB[Index];
}
#if(_ABLE_I64_)
_K_ LinC_Mul_2_I64_(_G_ inte_64 _PL_ LineC,_G_ INTE_64 _PL_ LineA,_G_ INTE_64 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]*LineB[Index];
}
#endif
#if(_ABLE_R16_)
_K_ LinC_Mul_2_R16_(_G_ real_16 _PL_ LineC,_G_ REAL_16 _PL_ LineA,_G_ REAL_16 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]*LineB[Index];
}
#endif
_K_ LinC_Mul_2_R32_(_G_ real_32 _PL_ LineC,_G_ REAL_32 _PL_ LineA,_G_ REAL_32 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]*LineB[Index];
}
#if(_ABLE_R64_)
_K_ LinC_Mul_2_R64_(_G_ real_64 _PL_ LineC,_G_ REAL_64 _PL_ LineA,_G_ REAL_64 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]*LineB[Index];
}
#endif
#endif
#if(Fold_(Definition:Division Functions))
_K_ LinC_Div_2_I08_(_G_ inte_08 _PL_ LineC,_G_ INTE_08 _PL_ LineA,_G_ INTE_08 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]/LineB[Index];
}
_K_ LinC_Div_2_I16_(_G_ inte_16 _PL_ LineC,_G_ INTE_16 _PL_ LineA,_G_ INTE_16 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]/LineB[Index];
}
_K_ LinC_Div_2_I32_(_G_ inte_32 _PL_ LineC,_G_ INTE_32 _PL_ LineA,_G_ INTE_32 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]/LineB[Index];
}
#if(_ABLE_I64_)
_K_ LinC_Div_2_I64_(_G_ inte_64 _PL_ LineC,_G_ INTE_64 _PL_ LineA,_G_ INTE_64 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]/LineB[Index];
}
#endif
_K_ LinC_Div_2_D08_(_G_ data_08 _PL_ LineC,_G_ DATA_08 _PL_ LineA,_G_ DATA_08 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]/LineB[Index];
}
_K_ LinC_Div_2_D16_(_G_ data_16 _PL_ LineC,_G_ DATA_16 _PL_ LineA,_G_ DATA_16 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]/LineB[Index];
}
_K_ LinC_Div_2_D32_(_G_ data_32 _PL_ LineC,_G_ DATA_32 _PL_ LineA,_G_ DATA_32 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]/LineB[Index];
}
#if(_ABLE_I64_)
_K_ LinC_Div_2_D64_(_G_ data_64 _PL_ LineC,_G_ DATA_64 _PL_ LineA,_G_ DATA_64 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]/LineB[Index];
}
#endif
#if(_ABLE_R16_)
_K_ LinC_Div_2_R16_(_G_ real_16 _PL_ LineC,_G_ REAL_16 _PL_ LineA,_G_ REAL_16 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]/LineB[Index];
}
#endif
_K_ LinC_Div_2_R32_(_G_ real_32 _PL_ LineC,_G_ REAL_32 _PL_ LineA,_G_ REAL_32 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]/LineB[Index];
}
#if(_ABLE_R64_)
_K_ LinC_Div_2_R64_(_G_ real_64 _PL_ LineC,_G_ REAL_64 _PL_ LineA,_G_ REAL_64 _PL_ LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]/LineB[Index];
}
#endif

_K_ LinC_Div_1_I08_(_G_ inte_08 _PL_ LineC,_G_ INTE_08 _PL_ LineA,_P_ INTE_08 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]/Value;
}
_K_ LinC_Div_1_I16_(_G_ inte_16 _PL_ LineC,_G_ INTE_16 _PL_ LineA,_P_ INTE_16 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]/Value;
}
_K_ LinC_Div_1_I32_(_G_ inte_32 _PL_ LineC,_G_ INTE_32 _PL_ LineA,_P_ INTE_32 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]/Value;
}
#if(_ABLE_I64_)
_K_ LinC_Div_1_I64_(_G_ inte_64 _PL_ LineC,_G_ INTE_64 _PL_ LineA,_P_ INTE_64 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]/Value;
}
#endif
_K_ LinC_Div_1_D08_(_G_ data_08 _PL_ LineC,_G_ DATA_08 _PL_ LineA,_P_ DATA_08 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]/Value;
}
_K_ LinC_Div_1_D16_(_G_ data_16 _PL_ LineC,_G_ DATA_16 _PL_ LineA,_P_ DATA_16 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]/Value;
}
_K_ LinC_Div_1_D32_(_G_ data_32 _PL_ LineC,_G_ DATA_32 _PL_ LineA,_P_ DATA_32 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]/Value;
}
#if(_ABLE_I64_)
_K_ LinC_Div_1_D64_(_G_ data_64 _PL_ LineC,_G_ DATA_64 _PL_ LineA,_P_ DATA_64 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=LineA[Index]/Value;
}
#endif

_K_ LinC_Inv_1_I08_(_G_ inte_08 _PL_ LineC,_G_ INTE_08 _PL_ LineA,_P_ INTE_08 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=Value/LineA[Index];
}
_K_ LinC_Inv_1_I16_(_G_ inte_16 _PL_ LineC,_G_ INTE_16 _PL_ LineA,_P_ INTE_16 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=Value/LineA[Index];
}
_K_ LinC_Inv_1_I32_(_G_ inte_32 _PL_ LineC,_G_ INTE_32 _PL_ LineA,_P_ INTE_32 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=Value/LineA[Index];
}
#if(_ABLE_I64_)
_K_ LinC_Inv_1_I64_(_G_ inte_64 _PL_ LineC,_G_ INTE_64 _PL_ LineA,_P_ INTE_64 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=Value/LineA[Index];
}
#endif
_K_ LinC_Inv_1_D08_(_G_ data_08 _PL_ LineC,_G_ DATA_08 _PL_ LineA,_P_ DATA_08 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=Value/LineA[Index];
}
_K_ LinC_Inv_1_D16_(_G_ data_16 _PL_ LineC,_G_ DATA_16 _PL_ LineA,_P_ DATA_16 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=Value/LineA[Index];
}
_K_ LinC_Inv_1_D32_(_G_ data_32 _PL_ LineC,_G_ DATA_32 _PL_ LineA,_P_ DATA_32 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=Value/LineA[Index];
}
#if(_ABLE_I64_)
_K_ LinC_Inv_1_D64_(_G_ data_64 _PL_ LineC,_G_ DATA_64 _PL_ LineA,_P_ DATA_64 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=Value/LineA[Index];
}
#endif
#if(_ABLE_R16_)
_K_ LinC_Inv_1_R16_(_G_ real_16 _PL_ LineC,_G_ REAL_16 _PL_ LineA,_P_ REAL_16 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=Value/LineA[Index];
}
#endif
_K_ LinC_Inv_1_R32_(_G_ real_32 _PL_ LineC,_G_ REAL_32 _PL_ LineA,_P_ REAL_32 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=Value/LineA[Index];
}
#if(_ABLE_R64_)
_K_ LinC_Inv_1_R64_(_G_ real_64 _PL_ LineC,_G_ REAL_64 _PL_ LineA,_P_ REAL_64 Value,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ data_32 Index=Work_IGX_;

	for(;Index<Length;Index+=Step)
		LineC[Index]=Value/LineA[Index];
}
#endif
#endif
#if(Fold_(Definition:Summation Functions))
_K_ LinC_Sum_1_I08_(_G_ inte_08 _PL_ Result,_L_ inte_08 _PL_ Work,_G_ INTE_08 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ DATA_32 Step=Work_SLX_;
	_P_ data_32 Index;
	_P_ inte_08 Temp;

	for(Index=Start,Line+=(Group*Length),Temp=0;Index<Length;Index+=Step)
		Temp+=Line[Index];

	for(Index=Step>>1;Index;Index>>=1)
	{
		Wait_L_;
		Work[Start]=Temp;
		Wait_L_;
		Temp=Work[Start]+Work[Start^Index];
	}
	if(!Start)
		Result[Group]=Temp;
}
_K_ LinC_Sum_1_I16_(_G_ inte_16 _PL_ Result,_L_ inte_16 _PL_ Work,_G_ INTE_16 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ DATA_32 Step=Work_SLX_;
	_P_ data_32 Index;
	_P_ inte_16 Temp;

	for(Index=Start,Line+=(Group*Length),Temp=0;Index<Length;Index+=Step)
		Temp+=Line[Index];

	for(Index=Step>>1;Index;Index>>=1)
	{
		Wait_L_;
		Work[Start]=Temp;
		Wait_L_;
		Temp=Work[Start]+Work[Start^Index];
	}
	if(!Start)
		Result[Group]=Temp;
}
_K_ LinC_Sum_1_I32_(_G_ inte_32 _PL_ Result,_L_ inte_32 _PL_ Work,_G_ INTE_32 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ DATA_32 Step=Work_SLX_;
	_P_ data_32 Index;
	_P_ inte_32 Temp;

	for(Index=Start,Line+=(Group*Length),Temp=0;Index<Length;Index+=Step)
		Temp+=Line[Index];

	for(Index=Step>>1;Index;Index>>=1)
	{
		Wait_L_;
		Work[Start]=Temp;
		Wait_L_;
		Temp=Work[Start]+Work[Start^Index];
	}
	if(!Start)
		Result[Group]=Temp;
}
#if(_ABLE_I64_)
_K_ LinC_Sum_1_I64_(_G_ inte_64 _PL_ Result,_L_ inte_64 _PL_ Work,_G_ INTE_64 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ DATA_32 Step=Work_SLX_;
	_P_ data_32 Index;
	_P_ inte_64 Temp;

	for(Index=Start,Line+=(Group*Length),Temp=0;Index<Length;Index+=Step)
		Temp+=Line[Index];

	for(Index=Step>>1;Index;Index>>=1)
	{
		Wait_L_;
		Work[Start]=Temp;
		Wait_L_;
		Temp=Work[Start]+Work[Start^Index];
	}
	if(!Start)
		Result[Group]=Temp;
}
#endif
#if(_ABLE_R16_)
_K_ LinC_Sum_1_R16_(_G_ real_16 _PL_ Result,_L_ real_16 _PL_ Work,_G_ REAL_16 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ DATA_32 Step=Work_SLX_;
	_P_ data_32 Index;
	_P_ real_16 Temp;

	for(Index=Start,Line+=(Group*Length),Temp=0.0H;Index<Length;Index+=Step)
		Temp+=Line[Index];

	for(Index=Step>>1;Index;Index>>=1)
	{
		Wait_L_;
		Work[Start]=Temp;
		Wait_L_;
		Temp=Work[Start]+Work[Start^Index];
	}
	if(!Start)
		Result[Group]=Temp;
}
#endif
_K_ LinC_Sum_1_R32_(_G_ real_32 _PL_ Result,_L_ real_32 _PL_ Work,_G_ REAL_32 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ DATA_32 Step=Work_SLX_;
	_P_ data_32 Index;
	_P_ real_32 Temp;

	for(Index=Start,Line+=(Group*Length),Temp=0.0F;Index<Length;Index+=Step)
		Temp+=Line[Index];

	for(Index=Step>>1;Index;Index>>=1)
	{
		Wait_L_;
		Work[Start]=Temp;
		Wait_L_;
		Temp=Work[Start]+Work[Start^Index];
	}
	if(!Start)
		Result[Group]=Temp;
}
#if(_ABLE_R64_)
_K_ LinC_Sum_1_R64_(_G_ real_64 _PL_ Result,_L_ real_64 _PL_ Work,_G_ REAL_64 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ DATA_32 Step=Work_SLX_;
	_P_ data_32 Index;
	_P_ real_64 Temp;

	for(Index=Start,Line+=(Group*Length),Temp=0.0;Index<Length;Index+=Step)
		Temp+=Line[Index];

	for(Index=Step>>1;Index;Index>>=1)
	{
		Wait_L_;
		Work[Start]=Temp;
		Wait_L_;
		Temp=Work[Start]+Work[Start^Index];
	}
	if(!Start)
		Result[Group]=Temp;
}
#endif
#endif
#if(Fold_(Definition:Dot-Product Functions))
_K_ LinC_Dot_2_I08_(_G_ inte_08 _PL_ Result,_L_ inte_08 _PL_ Work,_G_ INTE_08 *LineA,_G_ INTE_08 *LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ DATA_32 Step=Work_SLX_;
	_P_ DATA_32 Offset=Group*Length;
	_P_ data_32 Index;
	_P_ inte_08 Temp;

	for(Index=Start,LineA+=Offset,LineB+=Offset,Temp=0;Index<Length;Index+=Step)
		Temp+=(LineA[Index]*LineB[Index]);

	for(Index=Step>>1;Index;Index>>=1)
	{
		Wait_L_;
		Work[Start]=Temp;
		Wait_L_;
		Temp=Work[Start]+Work[Start^Index];
	}
	if(!Start)
		Result[Group]=Temp;
}
_K_ LinC_Dot_2_I16_(_G_ inte_16 _PL_ Result,_L_ inte_16 _PL_ Work,_G_ INTE_16 *LineA,_G_ INTE_16 *LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ DATA_32 Step=Work_SLX_;
	_P_ DATA_32 Offset=Group*Length;
	_P_ data_32 Index;
	_P_ inte_16 Temp;

	for(Index=Start,LineA+=Offset,LineB+=Offset,Temp=0;Index<Length;Index+=Step)
		Temp+=(LineA[Index]*LineB[Index]);

	for(Index=Step>>1;Index;Index>>=1)
	{
		Wait_L_;
		Work[Start]=Temp;
		Wait_L_;
		Temp=Work[Start]+Work[Start^Index];
	}
	if(!Start)
		Result[Group]=Temp;
}
_K_ LinC_Dot_2_I32_(_G_ inte_32 _PL_ Result,_L_ inte_32 _PL_ Work,_G_ INTE_32 *LineA,_G_ INTE_32 *LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ DATA_32 Step=Work_SLX_;
	_P_ DATA_32 Offset=Group*Length;
	_P_ data_32 Index;
	_P_ inte_32 Temp;

	for(Index=Start,LineA+=Offset,LineB+=Offset,Temp=0;Index<Length;Index+=Step)
		Temp+=(LineA[Index]*LineB[Index]);

	for(Index=Step>>1;Index;Index>>=1)
	{
		Wait_L_;
		Work[Start]=Temp;
		Wait_L_;
		Temp=Work[Start]+Work[Start^Index];
	}
	if(!Start)
		Result[Group]=Temp;
}
#if(_ABLE_I64_)
_K_ LinC_Dot_2_I64_(_G_ inte_64 _PL_ Result,_L_ inte_64 _PL_ Work,_G_ INTE_64 *LineA,_G_ INTE_64 *LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ DATA_32 Step=Work_SLX_;
	_P_ DATA_32 Offset=Group*Length;
	_P_ data_32 Index;
	_P_ inte_64 Temp;

	for(Index=Start,LineA+=Offset,LineB+=Offset,Temp=0;Index<Length;Index+=Step)
		Temp+=(LineA[Index]*LineB[Index]);

	for(Index=Step>>1;Index;Index>>=1)
	{
		Wait_L_;
		Work[Start]=Temp;
		Wait_L_;
		Temp=Work[Start]+Work[Start^Index];
	}
	if(!Start)
		Result[Group]=Temp;
}
#endif
#if(_ABLE_R16_)
_K_ LinC_Dot_2_R16_(_G_ real_16 _PL_ Result,_L_ real_16 _PL_ Work,_G_ REAL_16 *LineA,_G_ REAL_16 *LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ DATA_32 Step=Work_SLX_;
	_P_ DATA_32 Offset=Group*Length;
	_P_ data_32 Index;
	_P_ real_16 Temp;

	for(Index=Start,LineA+=Offset,LineB+=Offset,Temp=0.0H;Index<Length;Index+=Step)
		Temp+=(LineA[Index]*LineB[Index]);

	for(Index=Step>>1;Index;Index>>=1)
	{
		Wait_L_;
		Work[Start]=Temp;
		Wait_L_;
		Temp=Work[Start]+Work[Start^Index];
	}
	if(!Start)
		Result[Group]=Temp;
}
#endif
_K_ LinC_Dot_2_R32_(_G_ real_32 _PL_ Result,_L_ real_32 _PL_ Work,_G_ REAL_32 *LineA,_G_ REAL_32 *LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ DATA_32 Step=Work_SLX_;
	_P_ DATA_32 Offset=Group*Length;
	_P_ data_32 Index;
	_P_ real_32 Temp;

	for(Index=Start,LineA+=Offset,LineB+=Offset,Temp=0.0F;Index<Length;Index+=Step)
		Temp+=(LineA[Index]*LineB[Index]);

	for(Index=Step>>1;Index;Index>>=1)
	{
		Wait_L_;
		Work[Start]=Temp;
		Wait_L_;
		Temp=Work[Start]+Work[Start^Index];
	}
	if(!Start)
		Result[Group]=Temp;
}
#if(_ABLE_R64_)
_K_ LinC_Dot_2_R64_(_G_ real_64 _PL_ Result,_L_ real_64 _PL_ Work,_G_ REAL_64 *LineA,_G_ REAL_64 *LineB,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ DATA_32 Step=Work_SLX_;
	_P_ DATA_32 Offset=Group*Length;
	_P_ data_32 Index;
	_P_ real_64 Temp;

	for(Index=Start,LineA+=Offset,LineB+=Offset,Temp=0.0;Index<Length;Index+=Step)
		Temp+=(LineA[Index]*LineB[Index]);

	for(Index=Step>>1;Index;Index>>=1)
	{
		Wait_L_;
		Work[Start]=Temp;
		Wait_L_;
		Temp=Work[Start]+Work[Start^Index];
	}
	if(!Start)
		Result[Group]=Temp;
}
#endif
#endif
#if(Fold_(Definition:Maximum Functions))
_K_ LinC_Max_1_I08_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ INTE_08 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ inte_08 _PL_ BuffM=(_L_ inte_08*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ inte_08 Max;
	_P_ inte_08 Now;

	{
		Line+=(Group*Length);
		Max=0x80;
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Max<Now)
		{
			Max=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Max;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Max<Now)
		{
			Max=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
_K_ LinC_Max_1_I16_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ INTE_16 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ inte_16 _PL_ BuffM=(_L_ inte_16*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ inte_16 Max;
	_P_ inte_16 Now;

	{
		Line+=(Group*Length);
		Max=0x8000;
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Max<Now)
		{
			Max=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Max;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Max<Now)
		{
			Max=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
_K_ LinC_Max_1_I32_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ INTE_32 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ inte_32 _PL_ BuffM=(_L_ inte_32*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ inte_32 Max;
	_P_ inte_32 Now;

	{
		Line+=(Group*Length);
		Max=0x80000000;
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Max<Now)
		{
			Max=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Max;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Max<Now)
		{
			Max=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
#if(_ABLE_I64_)
_K_ LinC_Max_1_I64_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ INTE_64 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ inte_64 _PL_ BuffM=(_L_ inte_64*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ inte_64 Max;
	_P_ inte_64 Now;

	{
		Line+=(Group*Length);
		Max=0x8000000000000000L;
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Max<Now)
		{
			Max=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Max;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Max<Now)
		{
			Max=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
#endif
_K_ LinC_Max_1_D08_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ DATA_08 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ data_08 _PL_ BuffM=(_L_ data_08*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ data_08 Max;
	_P_ data_08 Now;

	{
		Line+=(Group*Length);
		Max=0x00;
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Max<Now)
		{
			Max=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Max;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Max<Now)
		{
			Max=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
_K_ LinC_Max_1_D16_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ DATA_16 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ data_16 _PL_ BuffM=(_L_ data_16*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ data_16 Max;
	_P_ data_16 Now;

	{
		Line+=(Group*Length);
		Max=0x0000;
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Max<Now)
		{
			Max=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Max;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Max<Now)
		{
			Max=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
_K_ LinC_Max_1_D32_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ DATA_32 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ data_32 _PL_ BuffM=(_L_ data_32*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ data_32 Max;
	_P_ data_32 Now;

	{
		Line+=(Group*Length);
		Max=0x00000000;
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Max<Now)
		{
			Max=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Max;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Max<Now)
		{
			Max=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
#if(_ABLE_I64_)
_K_ LinC_Max_1_D64_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ DATA_64 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ data_64 _PL_ BuffM=(_L_ data_64*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ data_64 Max;
	_P_ data_64 Now;

	{
		Line+=(Group*Length);
		Max=0x0000000000000000UL;
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Max<Now)
		{
			Max=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Max;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Max<Now)
		{
			Max=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
#endif
#if(_ABLE_R16_)
_K_ LinC_Max_1_R16_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ REAL_16 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ real_16 _PL_ BuffM=(_L_ real_16*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ real_16 Max;
	_P_ real_16 Now;

	{
		Line+=(Group*Length);
		Max=Line[0];
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Max<Now)
		{
			Max=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Max;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Max<Now)
		{
			Max=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
#endif
_K_ LinC_Max_1_R32_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ REAL_32 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ real_32 _PL_ BuffM=(_L_ real_32*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ real_32 Max;
	_P_ real_32 Now;

	{
		Line+=(Group*Length);
		Max=Line[0];
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Max<Now)
		{
			Max=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Max;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Max<Now)
		{
			Max=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
#if(_ABLE_R64_)
_K_ LinC_Max_1_R64_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ REAL_64 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ real_64 _PL_ BuffM=(_L_ real_64*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ real_64 Max;
	_P_ real_64 Now;

	{
		Line+=(Group*Length);
		Max=Line[0];
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Max<Now)
		{
			Max=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Max;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Max<Now)
		{
			Max=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
#endif
#endif
#if(Fold_(Definition:Minimum Functions))
_K_ LinC_Min_1_I08_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ INTE_08 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ inte_08 _PL_ BuffM=(_L_ inte_08*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ inte_08 Min;
	_P_ inte_08 Now;

	{
		Line+=(Group*Length);
		Min=0x7F;
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Min>Now)
		{
			Min=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Min;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Min>Now)
		{
			Min=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
_K_ LinC_Min_1_I16_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ INTE_16 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ inte_16 _PL_ BuffM=(_L_ inte_16*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ inte_16 Min;
	_P_ inte_16 Now;

	{
		Line+=(Group*Length);
		Min=0x7FFF;
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Min>Now)
		{
			Min=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Min;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Min>Now)
		{
			Min=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
_K_ LinC_Min_1_I32_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ INTE_32 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ inte_32 _PL_ BuffM=(_L_ inte_32*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ inte_32 Min;
	_P_ inte_32 Now;

	{
		Line+=(Group*Length);
		Min=0x7FFFFFFF;
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Min>Now)
		{
			Min=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Min;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Min>Now)
		{
			Min=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
#if(_ABLE_I64_)
_K_ LinC_Min_1_I64_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ INTE_64 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ inte_64 _PL_ BuffM=(_L_ inte_64*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ inte_64 Min;
	_P_ inte_64 Now;

	{
		Line+=(Group*Length);
		Min=0x7FFFFFFFFFFFFFFFL;
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Min>Now)
		{
			Min=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Min;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Min>Now)
		{
			Min=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
#endif
_K_ LinC_Min_1_D08_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ DATA_08 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ data_08 _PL_ BuffM=(_L_ data_08*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ data_08 Min;
	_P_ data_08 Now;

	{
		Line+=(Group*Length);
		Min=0xFF;
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Min>Now)
		{
			Min=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Min;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Min>Now)
		{
			Min=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
_K_ LinC_Min_1_D16_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ DATA_16 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ data_16 _PL_ BuffM=(_L_ data_16*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ data_16 Min;
	_P_ data_16 Now;

	{
		Line+=(Group*Length);
		Min=0xFFFF;
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Min>Now)
		{
			Min=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Min;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Min>Now)
		{
			Min=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
_K_ LinC_Min_1_D32_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ DATA_32 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ data_32 _PL_ BuffM=(_L_ data_32*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ data_32 Min;
	_P_ data_32 Now;

	{
		Line+=(Group*Length);
		Min=0xFFFFFFFF;
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Min>Now)
		{
			Min=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Min;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Min>Now)
		{
			Min=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
#if(_ABLE_I64_)
_K_ LinC_Min_1_D64_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ DATA_64 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ data_64 _PL_ BuffM=(_L_ data_64*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ data_64 Min;
	_P_ data_64 Now;

	{
		Line+=(Group*Length);
		Min=0xFFFFFFFFFFFFFFFFUL;
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Min>Now)
		{
			Min=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Min;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Min>Now)
		{
			Min=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
#endif
#if(_ABLE_R16_)
_K_ LinC_Min_1_R16_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ REAL_16 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ real_16 _PL_ BuffM=(_L_ real_16*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ real_16 Min;
	_P_ real_16 Now;

	{
		Line+=(Group*Length);
		Min=Line[0];
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Min>Now)
		{
			Min=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Min;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Min>Now)
		{
			Min=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
#endif
_K_ LinC_Min_1_R32_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ REAL_32 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ real_32 _PL_ BuffM=(_L_ real_32*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ real_32 Min;
	_P_ real_32 Now;

	{
		Line+=(Group*Length);
		Min=Line[0];
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Min>Now)
		{
			Min=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Min;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Min>Now)
		{
			Min=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
#if(_ABLE_R64_)
_K_ LinC_Min_1_R64_(_G_ data_32 _PL_ Result,_L_ data_32 _PL_ Work,_G_ REAL_64 *Line,_P_ DATA_32 Length)
{
	_P_ DATA_32 Group=Work_IBX_;
	_P_ DATA_32 Start=Work_ILX_;
	_P_ data_32 Step=Work_SLX_;
	_L_ data_32 _PL_ BuffA=(_L_ data_32*)Work;
	_L_ real_64 _PL_ BuffM=(_L_ real_64*)(BuffA+Step);
	_P_ data_32 Index;
	_P_ data_32 Arg;
	_P_ real_64 Min;
	_P_ real_64 Now;

	{
		Line+=(Group*Length);
		Min=Line[0];
		Arg=0;
	}
	for(Index=Start;Index<Length;Index+=Step)
	{
		Now=Line[Index];
		if(Min>Now)
		{
			Min=Now;
			Arg=Index;
		}
	}

	for(Step>>=1;Step;Step>>=1)
	{
		Wait_L_;
		BuffA[Start]=Arg;
		BuffM[Start]=Min;

		Wait_L_;
		Index=Start^Step;
		Now=BuffM[Index];

		Wait_L_;
		if(Min>Now)
		{
			Min=Now;
			Arg=BuffA[Index];
		}
	}
	if(!Start)
		Result[Group]=Arg;
}
#endif
#endif
#if(Fold_(Definition:Mapping Functions))
_K_ LinC_Map_1_D08_(_G_ data_08 *Line,_G_ DATA_32 *Match,_G_ DATA_08 *Table,_P_ DATA_32 Number,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 StepT=Step*Length;
	_G_ DATA_08 _PL_ End=Table+(Number*Length);

	for(Table+=(Start*Length);Table<End;Line+=Step,Match+=Step,Table+=StepT)
		Line[Start]=Table[Match[Start]];
}
_K_ LinC_Map_1_D16_(_G_ data_16 *Line,_G_ DATA_32 *Match,_G_ DATA_16 *Table,_P_ DATA_32 Number,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 StepT=Step*Length;
	_G_ DATA_16 _PL_ End=Table+(Number*Length);

	for(Table+=(Start*Length);Table<End;Line+=Step,Match+=Step,Table+=StepT)
		Line[Start]=Table[Match[Start]];
}
_K_ LinC_Map_1_D32_(_G_ data_32 *Line,_G_ DATA_32 *Match,_G_ DATA_32 *Table,_P_ DATA_32 Number,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 StepT=Step*Length;
	_G_ DATA_32 _PL_ End=Table+(Number*Length);

	for(Table+=(Start*Length);Table<End;Line+=Step,Match+=Step,Table+=StepT)
		Line[Start]=Table[Match[Start]];
}
#if(_ABLE_I64_)
_K_ LinC_Map_1_D64_(_G_ data_64 *Line,_G_ DATA_32 *Match,_G_ DATA_64 *Table,_P_ DATA_32 Number,_P_ DATA_32 Length)
{
	_P_ DATA_32 Step=Work_SGX_;
	_P_ DATA_32 Start=Work_IGX_;
	_P_ DATA_32 StepT=Step*Length;
	_G_ DATA_64 _PL_ End=Table+(Number*Length);

	for(Table+=(Start*Length);Table<End;Line+=Step,Match+=Step,Table+=StepT)
		Line[Start]=Table[Match[Start]];
}
#endif
#endif
