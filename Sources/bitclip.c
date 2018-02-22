#include "bitclip.h"

#if(MemC_Fold_(Definition:Macros))
#define _BitC_Min_(A,B) (((A)<(B))?(A):(B))
#define _BitC_Max_(A,B) (((A)>(B))?(A):(B))
#define _BitC_Clamp_(Data,Min,Max) (((Data)<(Min))?(Min):(((Data)>(Max))?(Max):(Data)))

#ifdef __OPENCL_H
#define _BitC_Total_Kernels 172
#define _BitC_Kernel_Name_Length 24
#endif
#endif

#if(MemC_Fold_(Definition:Global Constants))
static DATA_08 IdiomVersion[16]="Date:2018.02.22";

#ifdef BitC_64_
static volatile DATA_64 ConstantUnique=0x0000000000000001;
#else
static volatile DATA_32 ConstantUnique=0x00000001;
#endif

static INTE_64 ConstantInvalid64[4]={0x7FF0000000000000,0xFFF0000000000000,0x7FFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF};
static INTE_64 ConstantPi64[4]={0x400921FB54442D18,0x3FD45F306DC9C883,0x4005BF0A8B145769,0x3FD78B56362CEF38};

static INTE_32 ConstantInvalid32[4]={0x7F800000,0xFF800000,0x7FFFFFFF,0xFFFFFFFF};
static INTE_32 ConstantPi32[4]={0x40490FDB,0x3EA2F983,0x402DF854,0x3EBC5AB2};

#ifdef __OPENCL_H
static DATA_08 IdiomKernelNull[_BitC_Kernel_Name_Length]="";
static DATA_08 IdiomKernelName[_BitC_Total_Kernels][_BitC_Kernel_Name_Length]=
{
	"",						"BitC_Endian_D16_",		"BitC_Endian_D32_",		"BitC_Endian_D64_",
	"",						"BitC_Caster_D08_D16_",	"BitC_Caster_D08_D32_",	"BitC_Caster_D08_D64_",
	"BitC_Caster_D08_I08_",	"",						"",						"",
	"",						"BitC_Caster_D08_R16_",	"BitC_Caster_D08_R32_",	"BitC_Caster_D08_R64_",
	"BitC_Caster_D16_D08_",	"",						"BitC_Caster_D16_D32_",	"BitC_Caster_D16_D64_",
	"BitC_Caster_D16_I08_",	"BitC_Caster_D16_I16_",	"",						"",
	"",						"BitC_Caster_D16_R16_",	"BitC_Caster_D16_R32_",	"BitC_Caster_D16_R64_",
	"BitC_Caster_D32_D08_",	"BitC_Caster_D32_D16_",	"",						"BitC_Caster_D32_D64_",
	"BitC_Caster_D32_I08_",	"BitC_Caster_D32_I16_",	"BitC_Caster_D32_I32_",	"",
	"",						"BitC_Caster_D32_R16_",	"BitC_Caster_D32_R32_",	"BitC_Caster_D32_R64_",
	"BitC_Caster_D64_D08_",	"BitC_Caster_D64_D16_",	"BitC_Caster_D64_D32_",	"",
	"BitC_Caster_D64_I08_",	"BitC_Caster_D64_I16_",	"BitC_Caster_D64_I32_",	"BitC_Caster_D64_I64_",
	"",						"BitC_Caster_D64_R16_",	"BitC_Caster_D64_R32_",	"BitC_Caster_D64_R64_",
	"BitC_Caster_I08_D08_",	"BitC_Caster_I08_D16_",	"BitC_Caster_I08_D32_",	"BitC_Caster_I08_D64_",
	"",						"BitC_Caster_I08_I16_",	"BitC_Caster_I08_I32_",	"BitC_Caster_I08_I64_",
	"",						"BitC_Caster_I08_R16_",	"BitC_Caster_I08_R32_",	"BitC_Caster_I08_R64_",
	"BitC_Caster_I16_D08_",	"BitC_Caster_I16_D16_",	"BitC_Caster_I16_D32_",	"BitC_Caster_I16_D64_",
	"BitC_Caster_I16_I08_",	"",						"BitC_Caster_I16_I32_",	"BitC_Caster_I16_I64_",
	"",						"BitC_Caster_I16_R16_",	"BitC_Caster_I16_R32_",	"BitC_Caster_I16_R64_",
	"BitC_Caster_I32_D08_",	"BitC_Caster_I32_D16_",	"BitC_Caster_I32_D32_",	"BitC_Caster_I32_D64_",
	"BitC_Caster_I32_I08_",	"BitC_Caster_I32_I16_",	"",						"BitC_Caster_I32_I64_",
	"",						"BitC_Caster_I32_R16_",	"BitC_Caster_I32_R32_",	"BitC_Caster_I32_R64_",
	"BitC_Caster_I64_D08_",	"BitC_Caster_I64_D16_",	"BitC_Caster_I64_D32_",	"BitC_Caster_I64_D64_",
	"BitC_Caster_I64_I08_",	"BitC_Caster_I64_I16_",	"BitC_Caster_I64_I32_",	"",
	"",						"BitC_Caster_I64_R16_",	"BitC_Caster_I64_R32_",	"BitC_Caster_I64_R64_",
	"",						"",						"",						"",
	"",						"",						"",						"",
	"",						"",						"",						"",
	"BitC_Caster_R16_D08_",	"BitC_Caster_R16_D16_",	"BitC_Caster_R16_D32_",	"BitC_Caster_R16_D64_",
	"BitC_Caster_R16_I08_",	"BitC_Caster_R16_I16_",	"BitC_Caster_R16_I32_",	"BitC_Caster_R16_I64_",
	"",						"",						"BitC_Caster_R16_R32_",	"BitC_Caster_R16_R64_",
	"BitC_Caster_R32_D08_",	"BitC_Caster_R32_D16_",	"BitC_Caster_R32_D32_",	"BitC_Caster_R32_D64_",
	"BitC_Caster_R32_I08_",	"BitC_Caster_R32_I16_",	"BitC_Caster_R32_I32_",	"BitC_Caster_R32_I64_",
	"",						"BitC_Caster_R32_R16_",	"",						"BitC_Caster_R32_R64_",
	"BitC_Caster_R64_D08_",	"BitC_Caster_R64_D16_",	"BitC_Caster_R64_D32_",	"BitC_Caster_R64_D64_",
	"BitC_Caster_R64_I08_",	"BitC_Caster_R64_I16_",	"BitC_Caster_R64_I32_",	"BitC_Caster_R64_I64_",
	"",						"BitC_Caster_R64_R16_",	"BitC_Caster_R64_R32_",	"",
	"BitC_BO_N_1_D08_",		"BitC_BO_A_2_D08_",		"BitC_BO_O_2_D08_",		"BitC_BO_X_2_D08_",
	"BitC_BO_A_1_D08_",		"BitC_BO_A_1_D16_",		"BitC_BO_A_1_D32_",		"BitC_BO_A_1_D64_",
	"BitC_BO_O_1_D08_",		"BitC_BO_O_1_D16_",		"BitC_BO_O_1_D32_",		"BitC_BO_O_1_D64_",
	"BitC_BO_X_1_D08_",		"BitC_BO_X_1_D16_",		"BitC_BO_X_1_D32_",		"BitC_BO_X_1_D64_",
	"BitC_BO_S_1_D08_",		"BitC_BO_S_1_D16_",		"BitC_BO_S_1_D32_",		"BitC_BO_S_1_D64_",
	"BitC_BO_S_1_I08_",		"BitC_BO_S_1_I16_",		"BitC_BO_S_1_I32_",		"BitC_BO_S_1_I64_"
};
static DATA_08 _PL_ AddressKernelName[_BitC_Total_Kernels]=
{
	IdiomKernelName[0],IdiomKernelName[1],IdiomKernelName[2],IdiomKernelName[3],
	IdiomKernelName[4],IdiomKernelName[5],IdiomKernelName[6],IdiomKernelName[7],
	IdiomKernelName[8],IdiomKernelName[9],IdiomKernelName[10],IdiomKernelName[11],
	IdiomKernelName[12],IdiomKernelName[13],IdiomKernelName[14],IdiomKernelName[15],
	IdiomKernelName[16],IdiomKernelName[17],IdiomKernelName[18],IdiomKernelName[19],
	IdiomKernelName[20],IdiomKernelName[21],IdiomKernelName[22],IdiomKernelName[23],
	IdiomKernelName[24],IdiomKernelName[25],IdiomKernelName[26],IdiomKernelName[27],
	IdiomKernelName[28],IdiomKernelName[29],IdiomKernelName[30],IdiomKernelName[31],
	IdiomKernelName[32],IdiomKernelName[33],IdiomKernelName[34],IdiomKernelName[35],
	IdiomKernelName[36],IdiomKernelName[37],IdiomKernelName[38],IdiomKernelName[39],
	IdiomKernelName[40],IdiomKernelName[41],IdiomKernelName[42],IdiomKernelName[43],
	IdiomKernelName[44],IdiomKernelName[45],IdiomKernelName[46],IdiomKernelName[47],
	IdiomKernelName[48],IdiomKernelName[49],IdiomKernelName[50],IdiomKernelName[51],
	IdiomKernelName[52],IdiomKernelName[53],IdiomKernelName[54],IdiomKernelName[55],
	IdiomKernelName[56],IdiomKernelName[57],IdiomKernelName[58],IdiomKernelName[59],
	IdiomKernelName[60],IdiomKernelName[61],IdiomKernelName[62],IdiomKernelName[63],
	IdiomKernelName[64],IdiomKernelName[65],IdiomKernelName[66],IdiomKernelName[67],
	IdiomKernelName[68],IdiomKernelName[69],IdiomKernelName[70],IdiomKernelName[71],
	IdiomKernelName[72],IdiomKernelName[73],IdiomKernelName[74],IdiomKernelName[75],
	IdiomKernelName[76],IdiomKernelName[77],IdiomKernelName[78],IdiomKernelName[79],
	IdiomKernelName[80],IdiomKernelName[81],IdiomKernelName[82],IdiomKernelName[83],
	IdiomKernelName[84],IdiomKernelName[85],IdiomKernelName[86],IdiomKernelName[87],
	IdiomKernelName[88],IdiomKernelName[89],IdiomKernelName[90],IdiomKernelName[91],
	IdiomKernelName[92],IdiomKernelName[93],IdiomKernelName[94],IdiomKernelName[95],
	IdiomKernelName[96],IdiomKernelName[97],IdiomKernelName[98],IdiomKernelName[99],
	IdiomKernelName[100],IdiomKernelName[101],IdiomKernelName[102],IdiomKernelName[103],
	IdiomKernelName[104],IdiomKernelName[105],IdiomKernelName[106],IdiomKernelName[107],
	IdiomKernelName[108],IdiomKernelName[109],IdiomKernelName[110],IdiomKernelName[111],
	IdiomKernelName[112],IdiomKernelName[113],IdiomKernelName[114],IdiomKernelName[115],
	IdiomKernelName[116],IdiomKernelName[117],IdiomKernelName[118],IdiomKernelName[119],
	IdiomKernelName[120],IdiomKernelName[121],IdiomKernelName[122],IdiomKernelName[123],
	IdiomKernelName[124],IdiomKernelName[125],IdiomKernelName[126],IdiomKernelName[127],
	IdiomKernelName[128],IdiomKernelName[129],IdiomKernelName[130],IdiomKernelName[131],
	IdiomKernelName[132],IdiomKernelName[133],IdiomKernelName[134],IdiomKernelName[135],
	IdiomKernelName[136],IdiomKernelName[137],IdiomKernelName[138],IdiomKernelName[139],
	IdiomKernelName[140],IdiomKernelName[141],IdiomKernelName[142],IdiomKernelName[143],
	IdiomKernelName[144],IdiomKernelName[145],IdiomKernelName[146],IdiomKernelName[147],
	IdiomKernelName[148],IdiomKernelName[149],IdiomKernelName[150],IdiomKernelName[151],
	IdiomKernelName[152],IdiomKernelName[153],IdiomKernelName[154],IdiomKernelName[155],
	IdiomKernelName[156],IdiomKernelName[157],IdiomKernelName[158],IdiomKernelName[159],
	IdiomKernelName[160],IdiomKernelName[161],IdiomKernelName[162],IdiomKernelName[163],
	IdiomKernelName[164],IdiomKernelName[165],IdiomKernelName[166],IdiomKernelName[167],
	IdiomKernelName[168],IdiomKernelName[169],IdiomKernelName[170],IdiomKernelName[171]
};
DATA_08 _PL_ _PL_ BitCKernel=AddressKernelName;
#endif

DATA_08 _PL_ BitClip=IdiomVersion;
volatile DATA_08 _PL_ BitCEndian=(data_08*)&ConstantUnique;
REAL_32 _PL_ BitCInvalid32=(real_32*)ConstantInvalid32;
REAL_64 _PL_ BitCInvalid64=(real_64*)ConstantInvalid64;
REAL_32 _PL_ BitCPi32=(real_32*)ConstantPi32;
REAL_64 _PL_ BitCPi64=(real_64*)ConstantPi64;
#endif

#if(MemC_Fold_(Definition:KM Functions))
#ifdef __OPENCL_H
static devi_km *_BitC_Create_KM_Endian_(cl_kernel const Kernel)
{
	devi_km *KM=Devi_KM_Create_(Kernel,2,1);

	if(KM)
	{
		Devi_KM_Type_G_(KM,0,cl_mem);
		Devi_KM_Type_G_(KM,1,data_32);
		if(Devi_KM_Init_(KM)!=CL_SUCCESS)
			Devi_KM_Delete_(&KM);
	}

	return KM;
}
static devi_km *_BitC_Create_KM_Caster_(cl_kernel const Kernel)
{
	devi_km *KM=Devi_KM_Create_(Kernel,3,1);

	if(KM)
	{
		Devi_KM_Type_G_(KM,0,cl_mem);
		Devi_KM_Type_G_(KM,1,cl_mem);
		Devi_KM_Type_G_(KM,2,data_32);
		if(Devi_KM_Init_(KM)!=CL_SUCCESS)
			Devi_KM_Delete_(&KM);
	}

	return KM;
}
static devi_km *_BitC_Create_KM_Op_(cl_kernel const Kernel,const size_t TypeSize)
{
	devi_km *KM=Devi_KM_Create_(Kernel,4,1);

	if(KM)
	{
		Devi_KM_Type_G_(KM,0,cl_mem);
		Devi_KM_Type_G_(KM,1,cl_mem);
		_Devi_KM_Type_(KM,2,TypeSize,0);
		Devi_KM_Type_G_(KM,3,data_32);
		if(Devi_KM_Init_(KM)!=CL_SUCCESS)
			Devi_KM_Delete_(&KM);
	}

	return KM;
}
general BitC_Worker_KM_Endian_(PENC_CL _PL_ Helper,devi_km _PL_ KM,cl_mem const Data,DATA_32 Length)
{
	{
		KM->WGroups[0]=Helper->Cores;
		KM->WLocals[0]=Helper->SizeWorker[0];
	}
	{
		Devi_KM_Save_G_(KM,0,&Data);
		Devi_KM_Save_G_(KM,1,&Length);
	}
}
general BitC_Worker_KM_Caster_(PENC_CL _PL_ Helper,devi_km _PL_ KM,cl_mem const Input,cl_mem const Output,DATA_32 Length)
{
	{
		KM->WGroups[0]=Helper->Cores;
		KM->WLocals[0]=Helper->SizeWorker[0];
	}
	{
		Devi_KM_Save_G_(KM,0,&Input);
		Devi_KM_Save_G_(KM,1,&Output);
		Devi_KM_Save_G_(KM,2,&Length);
	}
}
general BitC_Worker_KM_Op_N_1_(PENC_CL _PL_ Helper,devi_km _PL_ KM,cl_mem const DataC,cl_mem const DataA,DATA_32 Length)
{
	{
		KM->WGroups[0]=Helper->Cores;
		KM->WLocals[0]=Helper->SizeWorker[0];
	}
	{
		Devi_KM_Save_G_(KM,0,&DataC);
		Devi_KM_Save_G_(KM,1,&DataA);
		Devi_KM_Save_G_(KM,2,&Length);
	}
}
general BitC_Worker_KM_Op_S_1_(PENC_CL _PL_ Helper,devi_km _PL_ KM,cl_mem const DataC,cl_mem const DataA,INTE_32 Shift,DATA_32 Length)
{
	{
		KM->WGroups[0]=Helper->Cores;
		KM->WLocals[0]=Helper->SizeWorker[0];
	}
	{
		Devi_KM_Save_G_(KM,0,&DataC);
		Devi_KM_Save_G_(KM,1,&DataA);
		Devi_KM_Save_G_(KM,2,&Shift);
		Devi_KM_Save_G_(KM,3,&Length);
	}
}
general BitC_Worker_KM_Op_M_1_(PENC_CL _PL_ Helper,devi_km _PL_ KM,cl_mem const DataC,cl_mem const DataA,GENERAL *Mask,DATA_32 Length)
{
	{
		KM->WGroups[0]=Helper->Cores;
		KM->WLocals[0]=Helper->SizeWorker[0];
	}
	{
		Devi_KM_Save_G_(KM,0,&DataC);
		Devi_KM_Save_G_(KM,1,&DataA);
		Devi_KM_Save_G_(KM,2,Mask);
		Devi_KM_Save_G_(KM,3,&Length);
	}
}
general BitC_Worker_KM_Op_M_2_(PENC_CL _PL_ Helper,devi_km _PL_ KM,cl_mem const DataC,cl_mem const DataA,cl_mem const DataB,DATA_32 Length)
{
	{
		KM->WGroups[0]=Helper->Cores;
		KM->WLocals[0]=Helper->SizeWorker[0];
	}
	{
		Devi_KM_Save_G_(KM,0,&DataC);
		Devi_KM_Save_G_(KM,1,&DataA);
		Devi_KM_Save_G_(KM,2,&DataB);
		Devi_KM_Save_G_(KM,3,&Length);
	}
}
devi_km *BitC_Create_KM_(cl_kernel const Kernel)
{
	data_08 BufferName[_BitC_Kernel_Name_Length];
	devi_km *KM;

	if(Devi_Info_Kernel_(Kernel,BufferName,_BitC_Kernel_Name_Length,data_08,CL_KERNEL_FUNCTION_NAME)==CL_SUCCESS)
	{
		ADDRESS Switch=MemC_Switch_(BufferName,(general**)BitCKernel,NULL,_BitC_Kernel_Name_Length,_BitC_Total_Kernels,data_08);
		
		if(Switch<4)
			KM=_BitC_Create_KM_Endian_(Kernel);
		else if(Switch<148)
			KM=_BitC_Create_KM_Caster_(Kernel);
		else if(Switch<164)
			switch(Switch)
			{
			case 148:
				KM=_BitC_Create_KM_Caster_(Kernel);
				break;
			case 149:
			case 150:
			case 151:
				KM=_BitC_Create_KM_Op_(Kernel,sizeof(cl_mem));
				break;
			case 152:
			case 156:
			case 160:
				KM=_BitC_Create_KM_Op_(Kernel,sizeof(data_08));
				break;
			case 153:
			case 157:
			case 161:
				KM=_BitC_Create_KM_Op_(Kernel,sizeof(data_16));
				break;
			case 154:
			case 158:
			case 162:
				KM=_BitC_Create_KM_Op_(Kernel,sizeof(data_32));
				break;
			case 155:
			case 159:
			case 163:
				KM=_BitC_Create_KM_Op_(Kernel,sizeof(data_64));
				break;
			default:
				KM=NULL;
			}
		else if(Switch<172)
			KM=_BitC_Create_KM_Op_(Kernel,sizeof(inte_32));
		else
			KM=NULL;
	}
	else
		KM=NULL;

	return KM;
}
#endif
#endif

#if(MemC_Fold_(Definition:Endian Functions))
general BitC_Endian_D16_(data_16 _PL_ Data,DATA_32 Length)
{
	DATA_08 *End=(data_08*)(Data+(Length&0xFFFFFFFC));
	data_08 *MemC_Rst_ Ptr=(data_08*)Data;
	data_08 Temp;

	for(;Ptr<End;Ptr+=8)
	{
		Temp=Ptr[0];
		Ptr[0]=Ptr[1];
		Ptr[1]=Temp;

		Temp=Ptr[2];
		Ptr[2]=Ptr[3];
		Ptr[3]=Temp;

		Temp=Ptr[4];
		Ptr[4]=Ptr[5];
		Ptr[5]=Temp;

		Temp=Ptr[6];
		Ptr[6]=Ptr[7];
		Ptr[7]=Temp;
	}
	for(End+=((Length&0x00000003)<<1);Ptr<End;Ptr+=2)
	{
		Temp=Ptr[0];
		Ptr[0]=Ptr[1];
		Ptr[1]=Temp;
	}
}
general BitC_Endian_D32_(data_32 _PL_ Data,DATA_32 Length)
{
	DATA_08 *End=(data_08*)(Data+(Length&0xFFFFFFFE));
	data_08 *MemC_Rst_ Ptr=(data_08*)Data;
	data_08 Temp;

	for(;Ptr<End;Ptr+=8)
	{
		Temp=Ptr[0];
		Ptr[0]=Ptr[3];
		Ptr[3]=Temp;
		Temp=Ptr[1];
		Ptr[1]=Ptr[2];
		Ptr[2]=Temp;
		
		Temp=Ptr[4];
		Ptr[4]=Ptr[7];
		Ptr[7]=Temp;
		Temp=Ptr[5];
		Ptr[5]=Ptr[6];
		Ptr[6]=Temp;
	}
	for(End+=((Length&0x00000001)<<2);Ptr<End;Ptr+=4)
	{
		Temp=Ptr[0];
		Ptr[0]=Ptr[3];
		Ptr[3]=Temp;
		Temp=Ptr[1];
		Ptr[1]=Ptr[2];
		Ptr[2]=Temp;
	}
}
general BitC_Endian_D64_(data_64 _PL_ Data,DATA_32 Length)
{
	DATA_08 *End=(data_08*)(Data+Length);
	data_08 *MemC_Rst_ Ptr=(data_08*)Data;
	data_08 Temp;

	for(;Ptr<End;Ptr+=8)
	{
		Temp=Ptr[0];
		Ptr[0]=Ptr[7];
		Ptr[7]=Temp;
		Temp=Ptr[1];
		Ptr[1]=Ptr[6];
		Ptr[6]=Temp;
		Temp=Ptr[2];
		Ptr[2]=Ptr[5];
		Ptr[5]=Temp;
		Temp=Ptr[3];
		Ptr[3]=Ptr[4];
		Ptr[4]=Temp;
	}
}
#endif

#if(MemC_Fold_(Definition:Caster Functions))
general BitC_Caster_D08_D16_(DATA_08 *MemC_Rst_ DataI,data_16 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_08 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_16)(DataI[0]);
}
general BitC_Caster_D08_D32_(DATA_08 *MemC_Rst_ DataI,data_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_08 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_32)(DataI[0]);
}
general BitC_Caster_D08_D64_(DATA_08 *MemC_Rst_ DataI,data_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_08 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_64)(DataI[0]);
}
general BitC_Caster_D08_I08_(DATA_08 *MemC_Rst_ DataI,inte_08 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_08 Max=0x7FU;
	DATA_08 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_08)_BitC_Min_(DataI[0],Max);
}
general BitC_Caster_D08_R32_(DATA_08 *MemC_Rst_ DataI,real_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_08 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(real_32)(DataI[0]);
}
general BitC_Caster_D08_R64_(DATA_08 *MemC_Rst_ DataI,real_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_08 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(real_64)(DataI[0]);
}
general BitC_Caster_D16_D08_(DATA_16 *MemC_Rst_ DataI,data_08 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_16 Max=0x00FFU;
	DATA_16 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_08)_BitC_Min_(DataI[0],Max);
}
general BitC_Caster_D16_D32_(DATA_16 *MemC_Rst_ DataI,data_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_16 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_32)(DataI[0]);
}
general BitC_Caster_D16_D64_(DATA_16 *MemC_Rst_ DataI,data_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_16 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_64)(DataI[0]);
}
general BitC_Caster_D16_I08_(DATA_16 *MemC_Rst_ DataI,inte_08 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_16 Max=0x007FU;
	DATA_16 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_08)_BitC_Min_(DataI[0],Max);
}
general BitC_Caster_D16_I16_(DATA_16 *MemC_Rst_ DataI,inte_16 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_16 Max=0x7FFFU;
	DATA_16 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_16)_BitC_Min_(DataI[0],Max);
}
general BitC_Caster_D16_R32_(DATA_16 *MemC_Rst_ DataI,real_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_16 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(real_32)(DataI[0]);
}
general BitC_Caster_D16_R64_(DATA_16 *MemC_Rst_ DataI,real_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_16 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(real_64)(DataI[0]);
}
general BitC_Caster_D32_D08_(DATA_32 *MemC_Rst_ DataI,data_08 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_32 Max=0x000000FFU;
	DATA_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_08)_BitC_Min_(DataI[0],Max);
}
general BitC_Caster_D32_D16_(DATA_32 *MemC_Rst_ DataI,data_16 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_32 Max=0x0000FFFFU;
	DATA_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_16)_BitC_Min_(DataI[0],Max);
}
general BitC_Caster_D32_D64_(DATA_32 *MemC_Rst_ DataI,data_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_64)(DataI[0]);
}
general BitC_Caster_D32_I08_(DATA_32 *MemC_Rst_ DataI,inte_08 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_32 Max=0x0000007FU;
	DATA_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_08)_BitC_Min_(DataI[0],Max);
}
general BitC_Caster_D32_I16_(DATA_32 *MemC_Rst_ DataI,inte_16 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_32 Max=0x00007FFFU;
	DATA_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_16)_BitC_Min_(DataI[0],Max);
}
general BitC_Caster_D32_I32_(DATA_32 *MemC_Rst_ DataI,inte_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_32 Max=0x7FFFFFFFU;
	DATA_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_32)_BitC_Min_(DataI[0],Max);
}
general BitC_Caster_D32_R32_(DATA_32 *MemC_Rst_ DataI,real_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(real_32)(DataI[0]);
}
general BitC_Caster_D32_R64_(DATA_32 *MemC_Rst_ DataI,real_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(real_64)(DataI[0]);
}
general BitC_Caster_D64_D08_(DATA_64 *MemC_Rst_ DataI,data_08 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_64 Max=0x00000000000000FFUL;
	DATA_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_08)_BitC_Min_(DataI[0],Max);
}
general BitC_Caster_D64_D16_(DATA_64 *MemC_Rst_ DataI,data_16 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_64 Max=0x000000000000FFFFUL;
	DATA_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_16)_BitC_Min_(DataI[0],Max);
}
general BitC_Caster_D64_D32_(DATA_64 *MemC_Rst_ DataI,data_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_64 Max=0x00000000FFFFFFFFUL;
	DATA_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_32)_BitC_Min_(DataI[0],Max);
}
general BitC_Caster_D64_I08_(DATA_64 *MemC_Rst_ DataI,inte_08 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_64 Max=0x000000000000007FUL;
	DATA_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_08)_BitC_Min_(DataI[0],Max);
}
general BitC_Caster_D64_I16_(DATA_64 *MemC_Rst_ DataI,inte_16 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_64 Max=0x0000000000007FFFUL;
	DATA_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_16)_BitC_Min_(DataI[0],Max);
}
general BitC_Caster_D64_I32_(DATA_64 *MemC_Rst_ DataI,inte_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_64 Max=0x000000007FFFFFFFUL;
	DATA_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_32)_BitC_Min_(DataI[0],Max);
}
general BitC_Caster_D64_I64_(DATA_64 *MemC_Rst_ DataI,inte_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_64 Max=0x7FFFFFFFFFFFFFFFUL;
	DATA_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_64)_BitC_Min_(DataI[0],Max);
}
general BitC_Caster_D64_R32_(DATA_64 *MemC_Rst_ DataI,real_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(real_32)(DataI[0]);
}
general BitC_Caster_D64_R64_(DATA_64 *MemC_Rst_ DataI,real_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(real_64)(DataI[0]);
}
general BitC_Caster_I08_D08_(INTE_08 *MemC_Rst_ DataI,data_08 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_08 Min=0x00;
	INTE_08 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_08)_BitC_Max_(DataI[0],Min);
}
general BitC_Caster_I08_D16_(INTE_08 *MemC_Rst_ DataI,data_16 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_08 Min=0x00;
	INTE_08 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_16)_BitC_Max_(DataI[0],Min);
}
general BitC_Caster_I08_D32_(INTE_08 *MemC_Rst_ DataI,data_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_08 Min=0x00;
	INTE_08 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_32)_BitC_Max_(DataI[0],Min);
}
general BitC_Caster_I08_D64_(INTE_08 *MemC_Rst_ DataI,data_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_08 Min=0x00;
	INTE_08 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_64)_BitC_Max_(DataI[0],Min);
}
general BitC_Caster_I08_I16_(INTE_08 *MemC_Rst_ DataI,inte_16 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_08 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_16)(DataI[0]);
}
general BitC_Caster_I08_I32_(INTE_08 *MemC_Rst_ DataI,inte_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_08 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_32)(DataI[0]);
}
general BitC_Caster_I08_I64_(INTE_08 *MemC_Rst_ DataI,inte_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_08 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_64)(DataI[0]);
}
general BitC_Caster_I08_R32_(INTE_08 *MemC_Rst_ DataI,real_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_08 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(real_32)(DataI[0]);
}
general BitC_Caster_I08_R64_(INTE_08 *MemC_Rst_ DataI,real_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_08 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(real_64)(DataI[0]);
}
general BitC_Caster_I16_D08_(INTE_16 *MemC_Rst_ DataI,data_08 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_16 Min=0x0000;
	INTE_16 Max=0x00FF;
	INTE_16 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_08)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_I16_D16_(INTE_16 *MemC_Rst_ DataI,data_16 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_16 Min=0x0000;
	INTE_16 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_16)_BitC_Max_(DataI[0],Min);
}
general BitC_Caster_I16_D32_(INTE_16 *MemC_Rst_ DataI,data_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_16 Min=0x0000;
	INTE_16 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_32)_BitC_Max_(DataI[0],Min);
}
general BitC_Caster_I16_D64_(INTE_16 *MemC_Rst_ DataI,data_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_16 Min=0x0000;
	INTE_16 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_64)_BitC_Max_(DataI[0],Min);
}
general BitC_Caster_I16_I08_(INTE_16 *MemC_Rst_ DataI,inte_08 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_16 Min=0xFF80;
	INTE_16 Max=0x007F;
	INTE_16 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_08)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_I16_I32_(INTE_16 *MemC_Rst_ DataI,inte_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_16 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_32)(DataI[0]);
}
general BitC_Caster_I16_I64_(INTE_16 *MemC_Rst_ DataI,inte_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_16 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_64)(DataI[0]);
}
general BitC_Caster_I16_R32_(INTE_16 *MemC_Rst_ DataI,real_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_16 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(real_32)(DataI[0]);
}
general BitC_Caster_I16_R64_(INTE_16 *MemC_Rst_ DataI,real_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_16 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(real_64)(DataI[0]);
}
general BitC_Caster_I32_D08_(INTE_32 *MemC_Rst_ DataI,data_08 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_32 Min=0x00000000;
	INTE_32 Max=0x000000FF;
	INTE_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_08)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_I32_D16_(INTE_32 *MemC_Rst_ DataI,data_16 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_32 Min=0x00000000;
	INTE_32 Max=0x0000FFFF;
	INTE_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_16)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_I32_D32_(INTE_32 *MemC_Rst_ DataI,data_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_32 Min=0x00000000;
	INTE_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_32)_BitC_Max_(DataI[0],Min);
}
general BitC_Caster_I32_D64_(INTE_32 *MemC_Rst_ DataI,data_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_32 Min=0x00000000;
	INTE_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_64)_BitC_Max_(DataI[0],Min);
}
general BitC_Caster_I32_I08_(INTE_32 *MemC_Rst_ DataI,inte_08 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_32 Min=0xFFFFFF80;
	INTE_32 Max=0x0000007F;
	INTE_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_08)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_I32_I16_(INTE_32 *MemC_Rst_ DataI,inte_16 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_32 Min=0xFFFF8000;
	INTE_32 Max=0x00007FFF;
	INTE_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_16)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_I32_I64_(INTE_32 *MemC_Rst_ DataI,inte_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_64)(DataI[0]);
}
general BitC_Caster_I32_R32_(INTE_32 *MemC_Rst_ DataI,real_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(real_32)(DataI[0]);
}
general BitC_Caster_I32_R64_(INTE_32 *MemC_Rst_ DataI,real_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(real_64)(DataI[0]);
}
general BitC_Caster_I64_D08_(INTE_64 *MemC_Rst_ DataI,data_08 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_64 Min=0x0000000000000000L;
	INTE_64 Max=0x00000000000000FFL;
	INTE_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_08)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_I64_D16_(INTE_64 *MemC_Rst_ DataI,data_16 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_64 Min=0x0000000000000000L;
	INTE_64 Max=0x000000000000FFFFL;
	INTE_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_16)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_I64_D32_(INTE_64 *MemC_Rst_ DataI,data_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_64 Min=0x0000000000000000L;
	INTE_64 Max=0x00000000FFFFFFFFL;
	INTE_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_32)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_I64_D64_(INTE_64 *MemC_Rst_ DataI,data_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_64 Min=0x0000000000000000L;
	INTE_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_64)_BitC_Max_(DataI[0],Min);
}
general BitC_Caster_I64_I08_(INTE_64 *MemC_Rst_ DataI,inte_08 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_64 Min=0xFFFFFFFFFFFFFF80L;
	INTE_64 Max=0x000000000000007FL;
	INTE_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_08)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_I64_I16_(INTE_64 *MemC_Rst_ DataI,inte_16 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_64 Min=0xFFFFFFFFFFFF8000L;
	INTE_64 Max=0x0000000000007FFFL;
	INTE_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_16)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_I64_I32_(INTE_64 *MemC_Rst_ DataI,inte_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_64 Min=0xFFFFFFFF80000000L;
	INTE_64 Max=0x000000007FFFFFFFL;
	INTE_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_32)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_I64_R32_(INTE_64 *MemC_Rst_ DataI,real_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(real_32)(DataI[0]);
}
general BitC_Caster_I64_R64_(INTE_64 *MemC_Rst_ DataI,real_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(real_64)(DataI[0]);
}
general BitC_Caster_R32_D08_(REAL_32 *MemC_Rst_ DataI,data_08 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_08 Table[2]={0x00U,0xFFU};
	REAL_32 Min=(real_32)(Table[0]);
	REAL_32 Max=(real_32)(Table[1]);
	REAL_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_08)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_R32_D16_(REAL_32 *MemC_Rst_ DataI,data_16 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_16 Table[2]={0x0000U,0xFFFFU};
	REAL_32 Min=(real_32)(Table[0]);
	REAL_32 Max=(real_32)(Table[1]);
	REAL_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_16)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_R32_D32_(REAL_32 *MemC_Rst_ DataI,data_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_32 Table[2]={0x00000000U,0xFFFFFFFFU};
	REAL_32 Min=(real_32)(Table[0]);
	REAL_32 Max=(real_32)(Table[1]);
	REAL_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_32)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_R32_D64_(REAL_32 *MemC_Rst_ DataI,data_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_64 Table[2]={0x0000000000000000UL,0xFFFFFFFFFFFFFFFFUL};
	REAL_32 Min=(real_32)(Table[0]);
	REAL_32 Max=(real_32)(Table[1]);
	REAL_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_64)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_R32_I08_(REAL_32 *MemC_Rst_ DataI,inte_08 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_08 Table[2]={0x80,0x7F};
	REAL_32 Min=(real_32)(Table[0]);
	REAL_32 Max=(real_32)(Table[1]);
	REAL_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_08)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_R32_I16_(REAL_32 *MemC_Rst_ DataI,inte_16 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_16 Table[2]={0x8000,0x7FFF};
	REAL_32 Min=(real_32)(Table[0]);
	REAL_32 Max=(real_32)(Table[1]);
	REAL_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_16)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_R32_I32_(REAL_32 *MemC_Rst_ DataI,inte_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_32 Table[2]={0x80000000,0x7FFFFFFF};
	REAL_32 Min=(real_32)(Table[0]);
	REAL_32 Max=(real_32)(Table[1]);
	REAL_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_32)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_R32_I64_(REAL_32 *MemC_Rst_ DataI,inte_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_64 Table[2]={0x8000000000000000L,0x7FFFFFFFFFFFFFFFL};
	REAL_32 Min=(real_32)(Table[0]);
	REAL_32 Max=(real_32)(Table[1]);
	REAL_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_64)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_R32_R64_(REAL_32 *MemC_Rst_ DataI,real_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	REAL_32 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(real_64)(DataI[0]);
}
general BitC_Caster_R64_D08_(REAL_64 *MemC_Rst_ DataI,data_08 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_08 Table[2]={0x00U,0xFFU};
	REAL_64 Min=(real_64)(Table[0]);
	REAL_64 Max=(real_64)(Table[1]);
	REAL_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_08)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_R64_D16_(REAL_64 *MemC_Rst_ DataI,data_16 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_16 Table[2]={0x0000U,0xFFFFU};
	REAL_64 Min=(real_64)(Table[0]);
	REAL_64 Max=(real_64)(Table[1]);
	REAL_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_16)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_R64_D32_(REAL_64 *MemC_Rst_ DataI,data_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_32 Table[2]={0x00000000U,0xFFFFFFFFU};
	REAL_64 Min=(real_64)(Table[0]);
	REAL_64 Max=(real_64)(Table[1]);
	REAL_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_32)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_R64_D64_(REAL_64 *MemC_Rst_ DataI,data_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_64 Table[2]={0x0000000000000000UL,0xFFFFFFFFFFFFFFFFUL};
	REAL_64 Min=(real_64)(Table[0]);
	REAL_64 Max=(real_64)(Table[1]);
	REAL_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(data_64)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_R64_I08_(REAL_64 *MemC_Rst_ DataI,inte_08 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_08 Table[2]={0x80,0x7F};
	REAL_64 Min=(real_64)(Table[0]);
	REAL_64 Max=(real_64)(Table[1]);
	REAL_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_08)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_R64_I16_(REAL_64 *MemC_Rst_ DataI,inte_16 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_16 Table[2]={0x8000,0x7FFF};
	REAL_64 Min=(real_64)(Table[0]);
	REAL_64 Max=(real_64)(Table[1]);
	REAL_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_16)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_R64_I32_(REAL_64 *MemC_Rst_ DataI,inte_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_32 Table[2]={0x80000000,0x7FFFFFFF};
	REAL_64 Min=(real_64)(Table[0]);
	REAL_64 Max=(real_64)(Table[1]);
	REAL_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_32)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_R64_I64_(REAL_64 *MemC_Rst_ DataI,inte_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	INTE_64 Table[2]={0x8000000000000000L,0x7FFFFFFFFFFFFFFFL};
	REAL_64 Min=(real_64)(Table[0]);
	REAL_64 Max=(real_64)(Table[1]);
	REAL_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(inte_64)_BitC_Clamp_(DataI[0],Min,Max);
}
general BitC_Caster_R64_R32_(REAL_64 *MemC_Rst_ DataI,real_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	REAL_64 _PL_ End=DataI+Length;

	for(;DataI<End;DataI++,DataO++)
		DataO[0]=(real_32)(DataI[0]);
}
#endif

#if(MemC_Fold_(Definition:Bit Operation Functions))
static data_64 _BitC_Wide_Mask_D08_(DATA_08 Mask)
{
	data_64 Wide=(data_64)Mask;

	Wide|=(Wide<<8);
	Wide|=(Wide<<16);
	Wide|=(Wide<<32);

	return Wide;
}
static data_64 _BitC_Wide_Mask_D16_(DATA_16 Mask)
{
	data_64 Wide=(data_64)Mask;

	Wide|=(Wide<<16);
	Wide|=(Wide<<32);

	return Wide;
}
static data_64 _BitC_Wide_Mask_D32_(DATA_32 Mask)
{
	data_64 Wide=(data_64)Mask;

	Wide|=(Wide<<32);

	return Wide;
}

general BitC_BO_N_1_D08_(data_08 _PL_ DataC,DATA_08 _PL_ DataA,DATA_32 Length)
{
	bitclip End;
	bitclip PtrA;
	bitclip PtrC;

	{
		End.C.G=DataA;
		PtrA.C.G=DataA;
		PtrC.C.G=DataC;
	}
	for(End.C.D08+=(Length&0xFFFFFFC0);PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrC.C.D64+=8)
	{
		PtrC.V.D64[0]=~(PtrA.C.D64[0]);
		PtrC.V.D64[1]=~(PtrA.C.D64[1]);
		PtrC.V.D64[2]=~(PtrA.C.D64[2]);
		PtrC.V.D64[3]=~(PtrA.C.D64[3]);
		PtrC.V.D64[4]=~(PtrA.C.D64[4]);
		PtrC.V.D64[5]=~(PtrA.C.D64[5]);
		PtrC.V.D64[6]=~(PtrA.C.D64[6]);
		PtrC.V.D64[7]=~(PtrA.C.D64[7]);
	}
	for(End.C.D08+=(Length&0x00000038);PtrA.C.G<End.C.G;PtrA.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=~(PtrA.C.D64[0]);
	for(End.C.D08+=(Length&0x00000007);PtrA.C.G<End.C.G;PtrA.C.D08++,PtrC.C.D08++)
		PtrC.V.D08[0]=~(PtrA.C.D08[0]);
}

general BitC_BO_S_1_D08_(data_08 *DataC,DATA_08 *DataA,inte_32 Shift,DATA_32 Length)
{
	DATA_08 *End=DataA+(Length&0xFFFFFFF8);

	if(Shift>0)
	{
		for(;DataA<End;DataA+=8,DataC+=8)
		{
			DataC[0]=DataA[0]<<Shift;
			DataC[1]=DataA[1]<<Shift;
			DataC[2]=DataA[2]<<Shift;
			DataC[3]=DataA[3]<<Shift;
			DataC[4]=DataA[4]<<Shift;
			DataC[5]=DataA[5]<<Shift;
			DataC[6]=DataA[6]<<Shift;
			DataC[7]=DataA[7]<<Shift;
		}
		for(End+=(Length&0x00000007);DataA<End;DataA++,DataC++)
			DataC[0]=DataA[0]<<Shift;
	}
	else
	{
		for(Shift=-Shift;DataA<End;DataA+=8,DataC+=8)
		{
			DataC[0]=DataA[0]>>Shift;
			DataC[1]=DataA[1]>>Shift;
			DataC[2]=DataA[2]>>Shift;
			DataC[3]=DataA[3]>>Shift;
			DataC[4]=DataA[4]>>Shift;
			DataC[5]=DataA[5]>>Shift;
			DataC[6]=DataA[6]>>Shift;
			DataC[7]=DataA[7]>>Shift;
		}
		for(End+=(Length&0x00000007);DataA<End;DataA++,DataC++)
			DataC[0]=DataA[0]>>Shift;
	}
}
general BitC_BO_S_1_D16_(data_16 *DataC,DATA_16 *DataA,inte_32 Shift,DATA_32 Length)
{
	DATA_16 *End=DataA+(Length&0xFFFFFFF8);

	if(Shift>0)
	{
		for(;DataA<End;DataA+=8,DataC+=8)
		{
			DataC[0]=DataA[0]<<Shift;
			DataC[1]=DataA[1]<<Shift;
			DataC[2]=DataA[2]<<Shift;
			DataC[3]=DataA[3]<<Shift;
			DataC[4]=DataA[4]<<Shift;
			DataC[5]=DataA[5]<<Shift;
			DataC[6]=DataA[6]<<Shift;
			DataC[7]=DataA[7]<<Shift;
		}
		for(End+=(Length&0x00000007);DataA<End;DataA++,DataC++)
			DataC[0]=DataA[0]<<Shift;
	}
	else
	{
		for(Shift=-Shift;DataA<End;DataA+=8,DataC+=8)
		{
			DataC[0]=DataA[0]>>Shift;
			DataC[1]=DataA[1]>>Shift;
			DataC[2]=DataA[2]>>Shift;
			DataC[3]=DataA[3]>>Shift;
			DataC[4]=DataA[4]>>Shift;
			DataC[5]=DataA[5]>>Shift;
			DataC[6]=DataA[6]>>Shift;
			DataC[7]=DataA[7]>>Shift;
		}
		for(End+=(Length&0x00000007);DataA<End;DataA++,DataC++)
			DataC[0]=DataA[0]>>Shift;
	}
}
general BitC_BO_S_1_D32_(data_32 *DataC,DATA_32 *DataA,inte_32 Shift,DATA_32 Length)
{
	DATA_32 *End=DataA+(Length&0xFFFFFFF8);

	if(Shift>0)
	{
		for(;DataA<End;DataA+=8,DataC+=8)
		{
			DataC[0]=DataA[0]<<Shift;
			DataC[1]=DataA[1]<<Shift;
			DataC[2]=DataA[2]<<Shift;
			DataC[3]=DataA[3]<<Shift;
			DataC[4]=DataA[4]<<Shift;
			DataC[5]=DataA[5]<<Shift;
			DataC[6]=DataA[6]<<Shift;
			DataC[7]=DataA[7]<<Shift;
		}
		for(End+=(Length&0x00000007);DataA<End;DataA++,DataC++)
			DataC[0]=DataA[0]<<Shift;
	}
	else
	{
		for(Shift=-Shift;DataA<End;DataA+=8,DataC+=8)
		{
			DataC[0]=DataA[0]>>Shift;
			DataC[1]=DataA[1]>>Shift;
			DataC[2]=DataA[2]>>Shift;
			DataC[3]=DataA[3]>>Shift;
			DataC[4]=DataA[4]>>Shift;
			DataC[5]=DataA[5]>>Shift;
			DataC[6]=DataA[6]>>Shift;
			DataC[7]=DataA[7]>>Shift;
		}
		for(End+=(Length&0x00000007);DataA<End;DataA++,DataC++)
			DataC[0]=DataA[0]>>Shift;
	}
}
general BitC_BO_S_1_D64_(data_64 *DataC,DATA_64 *DataA,inte_32 Shift,DATA_32 Length)
{
	DATA_64 *End=DataA+(Length&0xFFFFFFF8);

	if(Shift>0)
	{
		for(;DataA<End;DataA+=8,DataC+=8)
		{
			DataC[0]=DataA[0]<<Shift;
			DataC[1]=DataA[1]<<Shift;
			DataC[2]=DataA[2]<<Shift;
			DataC[3]=DataA[3]<<Shift;
			DataC[4]=DataA[4]<<Shift;
			DataC[5]=DataA[5]<<Shift;
			DataC[6]=DataA[6]<<Shift;
			DataC[7]=DataA[7]<<Shift;
		}
		for(End+=(Length&0x00000007);DataA<End;DataA++,DataC++)
			DataC[0]=DataA[0]<<Shift;
	}
	else
	{
		for(Shift=-Shift;DataA<End;DataA+=8,DataC+=8)
		{
			DataC[0]=DataA[0]>>Shift;
			DataC[1]=DataA[1]>>Shift;
			DataC[2]=DataA[2]>>Shift;
			DataC[3]=DataA[3]>>Shift;
			DataC[4]=DataA[4]>>Shift;
			DataC[5]=DataA[5]>>Shift;
			DataC[6]=DataA[6]>>Shift;
			DataC[7]=DataA[7]>>Shift;
		}
		for(End+=(Length&0x00000007);DataA<End;DataA++,DataC++)
			DataC[0]=DataA[0]>>Shift;
	}
}
general BitC_BO_S_1_I08_(inte_08 *DataC,INTE_08 *DataA,inte_32 Shift,DATA_32 Length)
{
	INTE_08 *End=DataA+(Length&0xFFFFFFF8);

	if(Shift>0)
	{
		for(;DataA<End;DataA+=8,DataC+=8)
		{
			DataC[0]=DataA[0]<<Shift;
			DataC[1]=DataA[1]<<Shift;
			DataC[2]=DataA[2]<<Shift;
			DataC[3]=DataA[3]<<Shift;
			DataC[4]=DataA[4]<<Shift;
			DataC[5]=DataA[5]<<Shift;
			DataC[6]=DataA[6]<<Shift;
			DataC[7]=DataA[7]<<Shift;
		}
		for(End+=(Length&0x00000007);DataA<End;DataA++,DataC++)
			DataC[0]=DataA[0]<<Shift;
	}
	else
	{
		for(Shift=-Shift;DataA<End;DataA+=8,DataC+=8)
		{
			DataC[0]=DataA[0]>>Shift;
			DataC[1]=DataA[1]>>Shift;
			DataC[2]=DataA[2]>>Shift;
			DataC[3]=DataA[3]>>Shift;
			DataC[4]=DataA[4]>>Shift;
			DataC[5]=DataA[5]>>Shift;
			DataC[6]=DataA[6]>>Shift;
			DataC[7]=DataA[7]>>Shift;
		}
		for(End+=(Length&0x00000007);DataA<End;DataA++,DataC++)
			DataC[0]=DataA[0]>>Shift;
	}
}
general BitC_BO_S_1_I16_(inte_16 *DataC,INTE_16 *DataA,inte_32 Shift,DATA_32 Length)
{
	INTE_16 *End=DataA+(Length&0xFFFFFFF8);

	if(Shift>0)
	{
		for(;DataA<End;DataA+=8,DataC+=8)
		{
			DataC[0]=DataA[0]<<Shift;
			DataC[1]=DataA[1]<<Shift;
			DataC[2]=DataA[2]<<Shift;
			DataC[3]=DataA[3]<<Shift;
			DataC[4]=DataA[4]<<Shift;
			DataC[5]=DataA[5]<<Shift;
			DataC[6]=DataA[6]<<Shift;
			DataC[7]=DataA[7]<<Shift;
		}
		for(End+=(Length&0x00000007);DataA<End;DataA++,DataC++)
			DataC[0]=DataA[0]<<Shift;
	}
	else
	{
		for(Shift=-Shift;DataA<End;DataA+=8,DataC+=8)
		{
			DataC[0]=DataA[0]>>Shift;
			DataC[1]=DataA[1]>>Shift;
			DataC[2]=DataA[2]>>Shift;
			DataC[3]=DataA[3]>>Shift;
			DataC[4]=DataA[4]>>Shift;
			DataC[5]=DataA[5]>>Shift;
			DataC[6]=DataA[6]>>Shift;
			DataC[7]=DataA[7]>>Shift;
		}
		for(End+=(Length&0x00000007);DataA<End;DataA++,DataC++)
			DataC[0]=DataA[0]>>Shift;
	}
}
general BitC_BO_S_1_I32_(inte_32 *DataC,INTE_32 *DataA,inte_32 Shift,DATA_32 Length)
{
	INTE_32 *End=DataA+(Length&0xFFFFFFF8);

	if(Shift>0)
	{
		for(;DataA<End;DataA+=8,DataC+=8)
		{
			DataC[0]=DataA[0]<<Shift;
			DataC[1]=DataA[1]<<Shift;
			DataC[2]=DataA[2]<<Shift;
			DataC[3]=DataA[3]<<Shift;
			DataC[4]=DataA[4]<<Shift;
			DataC[5]=DataA[5]<<Shift;
			DataC[6]=DataA[6]<<Shift;
			DataC[7]=DataA[7]<<Shift;
		}
		for(End+=(Length&0x00000007);DataA<End;DataA++,DataC++)
			DataC[0]=DataA[0]<<Shift;
	}
	else
	{
		for(Shift=-Shift;DataA<End;DataA+=8,DataC+=8)
		{
			DataC[0]=DataA[0]>>Shift;
			DataC[1]=DataA[1]>>Shift;
			DataC[2]=DataA[2]>>Shift;
			DataC[3]=DataA[3]>>Shift;
			DataC[4]=DataA[4]>>Shift;
			DataC[5]=DataA[5]>>Shift;
			DataC[6]=DataA[6]>>Shift;
			DataC[7]=DataA[7]>>Shift;
		}
		for(End+=(Length&0x00000007);DataA<End;DataA++,DataC++)
			DataC[0]=DataA[0]>>Shift;
	}
}
general BitC_BO_S_1_I64_(inte_64 *DataC,INTE_64 *DataA,inte_32 Shift,DATA_32 Length)
{
	INTE_64 *End=DataA+(Length&0xFFFFFFF8);

	if(Shift>0)
	{
		for(;DataA<End;DataA+=8,DataC+=8)
		{
			DataC[0]=DataA[0]<<Shift;
			DataC[1]=DataA[1]<<Shift;
			DataC[2]=DataA[2]<<Shift;
			DataC[3]=DataA[3]<<Shift;
			DataC[4]=DataA[4]<<Shift;
			DataC[5]=DataA[5]<<Shift;
			DataC[6]=DataA[6]<<Shift;
			DataC[7]=DataA[7]<<Shift;
		}
		for(End+=(Length&0x00000007);DataA<End;DataA++,DataC++)
			DataC[0]=DataA[0]<<Shift;
	}
	else
	{
		for(Shift=-Shift;DataA<End;DataA+=8,DataC+=8)
		{
			DataC[0]=DataA[0]>>Shift;
			DataC[1]=DataA[1]>>Shift;
			DataC[2]=DataA[2]>>Shift;
			DataC[3]=DataA[3]>>Shift;
			DataC[4]=DataA[4]>>Shift;
			DataC[5]=DataA[5]>>Shift;
			DataC[6]=DataA[6]>>Shift;
			DataC[7]=DataA[7]>>Shift;
		}
		for(End+=(Length&0x00000007);DataA<End;DataA++,DataC++)
			DataC[0]=DataA[0]>>Shift;
	}
}

general BitC_BO_A_1_D08_(data_08 _PL_ DataC,DATA_08 _PL_ DataA,DATA_08 Mask,DATA_32 Length)
{
	DATA_64 Wide=_BitC_Wide_Mask_D08_(Mask);
	bitclip End;
	bitclip PtrA;
	bitclip PtrC;

	{
		End.C.G=DataA;
		PtrA.C.G=DataA;
		PtrC.C.G=DataC;
	}
	for(End.C.D08+=(Length&0xFFFFFFC0);PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrC.C.D64+=8)
	{
		PtrC.V.D64[0]=PtrA.C.D64[0]&Wide;
		PtrC.V.D64[1]=PtrA.C.D64[1]&Wide;
		PtrC.V.D64[2]=PtrA.C.D64[2]&Wide;
		PtrC.V.D64[3]=PtrA.C.D64[3]&Wide;
		PtrC.V.D64[4]=PtrA.C.D64[4]&Wide;
		PtrC.V.D64[5]=PtrA.C.D64[5]&Wide;
		PtrC.V.D64[6]=PtrA.C.D64[6]&Wide;
		PtrC.V.D64[7]=PtrA.C.D64[7]&Wide;
	}
	for(End.C.D08+=(Length&0x00000038);PtrA.C.G<End.C.G;PtrA.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=PtrA.C.D64[0]&Wide;
	for(End.C.D08+=(Length&0x00000007);PtrA.C.G<End.C.G;PtrA.C.D08++,PtrC.C.D08++)
		PtrC.V.D08[0]=PtrA.C.D08[0]&Mask;
}
general BitC_BO_A_1_D16_(data_16 _PL_ DataC,DATA_16 _PL_ DataA,DATA_16 Mask,DATA_32 Length)
{
	DATA_64 Wide=_BitC_Wide_Mask_D16_(Mask);
	bitclip End;
	bitclip PtrA;
	bitclip PtrC;

	{
		End.C.G=DataA;
		PtrA.C.G=DataA;
		PtrC.C.G=DataC;
	}
	for(End.C.D16+=(Length&0xFFFFFFE0);PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrC.C.D64+=8)
	{
		PtrC.V.D64[0]=PtrA.C.D64[0]&Wide;
		PtrC.V.D64[1]=PtrA.C.D64[1]&Wide;
		PtrC.V.D64[2]=PtrA.C.D64[2]&Wide;
		PtrC.V.D64[3]=PtrA.C.D64[3]&Wide;
		PtrC.V.D64[4]=PtrA.C.D64[4]&Wide;
		PtrC.V.D64[5]=PtrA.C.D64[5]&Wide;
		PtrC.V.D64[6]=PtrA.C.D64[6]&Wide;
		PtrC.V.D64[7]=PtrA.C.D64[7]&Wide;
	}
	for(End.C.D16+=(Length&0x0000001C);PtrA.C.G<End.C.G;PtrA.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=PtrA.C.D64[0]&Wide;
	for(End.C.D16+=(Length&0x00000003);PtrA.C.G<End.C.G;PtrA.C.D16++,PtrC.C.D16++)
		PtrC.V.D16[0]=PtrA.C.D16[0]&Mask;
}
general BitC_BO_A_1_D32_(data_32 _PL_ DataC,DATA_32 _PL_ DataA,DATA_32 Mask,DATA_32 Length)
{
	DATA_64 Wide=_BitC_Wide_Mask_D32_(Mask);
	bitclip End;
	bitclip PtrA;
	bitclip PtrC;

	{
		End.C.G=DataA;
		PtrA.C.G=DataA;
		PtrC.C.G=DataC;
	}
	for(End.C.D32+=(Length&0xFFFFFFF0);PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrC.C.D64+=8)
	{
		PtrC.V.D64[0]=PtrA.C.D64[0]&Wide;
		PtrC.V.D64[1]=PtrA.C.D64[1]&Wide;
		PtrC.V.D64[2]=PtrA.C.D64[2]&Wide;
		PtrC.V.D64[3]=PtrA.C.D64[3]&Wide;
		PtrC.V.D64[4]=PtrA.C.D64[4]&Wide;
		PtrC.V.D64[5]=PtrA.C.D64[5]&Wide;
		PtrC.V.D64[6]=PtrA.C.D64[6]&Wide;
		PtrC.V.D64[7]=PtrA.C.D64[7]&Wide;
	}
	for(End.C.D32+=(Length&0x0000000E);PtrA.C.G<End.C.G;PtrA.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=PtrA.C.D64[0]&Wide;
	for(End.C.D32+=(Length&0x00000001);PtrA.C.G<End.C.G;PtrA.C.D32++,PtrC.C.D32++)
		PtrC.V.D32[0]=PtrA.C.D32[0]&Mask;
}
general BitC_BO_A_1_D64_(data_32 _PL_ DataC,DATA_32 _PL_ DataA,DATA_64 Mask,DATA_32 Length)
{
	bitclip End;
	bitclip PtrA;
	bitclip PtrC;

	{
		End.C.G=DataA;
		PtrA.C.G=DataA;
		PtrC.C.G=DataC;
	}
	for(End.C.D64+=(Length&0xFFFFFFF8);PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrC.C.D64+=8)
	{
		PtrC.V.D64[0]=PtrA.C.D64[0]&Mask;
		PtrC.V.D64[1]=PtrA.C.D64[1]&Mask;
		PtrC.V.D64[2]=PtrA.C.D64[2]&Mask;
		PtrC.V.D64[3]=PtrA.C.D64[3]&Mask;
		PtrC.V.D64[4]=PtrA.C.D64[4]&Mask;
		PtrC.V.D64[5]=PtrA.C.D64[5]&Mask;
		PtrC.V.D64[6]=PtrA.C.D64[6]&Mask;
		PtrC.V.D64[7]=PtrA.C.D64[7]&Mask;
	}
	for(End.C.D64+=(Length&0x00000007);PtrA.C.G<End.C.G;PtrA.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=PtrA.C.D64[0]&Mask;
}
general BitC_BO_A_2_D08_(data_08 _PL_ DataC,DATA_08 _PL_ DataA,DATA_08 _PL_ DataB,DATA_32 Length)
{
	bitclip End;
	bitclip PtrA;
	bitclip PtrB;
	bitclip PtrC;

	{
		End.C.G=DataA;
		PtrA.C.G=DataA;
		PtrB.C.G=DataB;
		PtrC.C.G=DataC;
	}
	for(End.C.D08+=(Length&0xFFFFFFC0);PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrB.C.D64+=8,PtrC.C.D64+=8)
	{
		PtrC.V.D64[0]=PtrA.C.D64[0]&PtrB.C.D64[0];
		PtrC.V.D64[1]=PtrA.C.D64[1]&PtrB.C.D64[1];
		PtrC.V.D64[2]=PtrA.C.D64[2]&PtrB.C.D64[2];
		PtrC.V.D64[3]=PtrA.C.D64[3]&PtrB.C.D64[3];
		PtrC.V.D64[4]=PtrA.C.D64[4]&PtrB.C.D64[4];
		PtrC.V.D64[5]=PtrA.C.D64[5]&PtrB.C.D64[5];
		PtrC.V.D64[6]=PtrA.C.D64[6]&PtrB.C.D64[6];
		PtrC.V.D64[7]=PtrA.C.D64[7]&PtrB.C.D64[7];
	}
	for(End.C.D08+=(Length&0x00000038);PtrA.C.G<End.C.G;PtrA.C.D64++,PtrB.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=PtrA.C.D64[0]&PtrB.C.D64[0];
	for(End.C.D08+=(Length&0x00000007);PtrA.C.G<End.C.G;PtrA.C.D08++,PtrB.C.D08++,PtrC.C.D08++)
		PtrC.V.D08[0]=PtrA.C.D08[0]&PtrB.C.D08[0];
}

general BitC_BO_O_1_D08_(data_08 _PL_ DataC,DATA_08 _PL_ DataA,DATA_08 Mask,DATA_32 Length)
{
	DATA_64 Wide=_BitC_Wide_Mask_D08_(Mask);
	bitclip End;
	bitclip PtrA;
	bitclip PtrC;

	{
		End.C.G=DataA;
		PtrA.C.G=DataA;
		PtrC.C.G=DataC;
	}
	for(End.C.D08+=(Length&0xFFFFFFC0);PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrC.C.D64+=8)
	{
		PtrC.V.D64[0]=PtrA.C.D64[0]|Wide;
		PtrC.V.D64[1]=PtrA.C.D64[1]|Wide;
		PtrC.V.D64[2]=PtrA.C.D64[2]|Wide;
		PtrC.V.D64[3]=PtrA.C.D64[3]|Wide;
		PtrC.V.D64[4]=PtrA.C.D64[4]|Wide;
		PtrC.V.D64[5]=PtrA.C.D64[5]|Wide;
		PtrC.V.D64[6]=PtrA.C.D64[6]|Wide;
		PtrC.V.D64[7]=PtrA.C.D64[7]|Wide;
	}
	for(End.C.D08+=(Length&0x00000038);PtrA.C.G<End.C.G;PtrA.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=PtrA.C.D64[0]|Wide;
	for(End.C.D08+=(Length&0x00000007);PtrA.C.G<End.C.G;PtrA.C.D08++,PtrC.C.D08++)
		PtrC.V.D08[0]=PtrA.C.D08[0]|Mask;
}
general BitC_BO_O_1_D16_(data_16 _PL_ DataC,DATA_16 _PL_ DataA,DATA_16 Mask,DATA_32 Length)
{
	DATA_64 Wide=_BitC_Wide_Mask_D16_(Mask);
	bitclip End;
	bitclip PtrA;
	bitclip PtrC;

	{
		End.C.G=DataA;
		PtrA.C.G=DataA;
		PtrC.C.G=DataC;
	}
	for(End.C.D16+=(Length&0xFFFFFFE0);PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrC.C.D64+=8)
	{
		PtrC.V.D64[0]=PtrA.C.D64[0]|Wide;
		PtrC.V.D64[1]=PtrA.C.D64[1]|Wide;
		PtrC.V.D64[2]=PtrA.C.D64[2]|Wide;
		PtrC.V.D64[3]=PtrA.C.D64[3]|Wide;
		PtrC.V.D64[4]=PtrA.C.D64[4]|Wide;
		PtrC.V.D64[5]=PtrA.C.D64[5]|Wide;
		PtrC.V.D64[6]=PtrA.C.D64[6]|Wide;
		PtrC.V.D64[7]=PtrA.C.D64[7]|Wide;
	}
	for(End.C.D16+=(Length&0x0000001C);PtrA.C.G<End.C.G;PtrA.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=PtrA.C.D64[0]|Wide;
	for(End.C.D16+=(Length&0x00000003);PtrA.C.G<End.C.G;PtrA.C.D16++,PtrC.C.D16++)
		PtrC.V.D16[0]=PtrA.C.D16[0]|Mask;
}
general BitC_BO_O_1_D32_(data_32 _PL_ DataC,DATA_32 _PL_ DataA,DATA_32 Mask,DATA_32 Length)
{
	DATA_64 Wide=_BitC_Wide_Mask_D32_(Mask);
	bitclip End;
	bitclip PtrA;
	bitclip PtrC;

	{
		End.C.G=DataA;
		PtrA.C.G=DataA;
		PtrC.C.G=DataC;
	}
	for(End.C.D32+=(Length&0xFFFFFFF0);PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrC.C.D64+=8)
	{
		PtrC.V.D64[0]=PtrA.C.D64[0]|Wide;
		PtrC.V.D64[1]=PtrA.C.D64[1]|Wide;
		PtrC.V.D64[2]=PtrA.C.D64[2]|Wide;
		PtrC.V.D64[3]=PtrA.C.D64[3]|Wide;
		PtrC.V.D64[4]=PtrA.C.D64[4]|Wide;
		PtrC.V.D64[5]=PtrA.C.D64[5]|Wide;
		PtrC.V.D64[6]=PtrA.C.D64[6]|Wide;
		PtrC.V.D64[7]=PtrA.C.D64[7]|Wide;
	}
	for(End.C.D32+=(Length&0x0000000E);PtrA.C.G<End.C.G;PtrA.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=PtrA.C.D64[0]|Wide;
	for(End.C.D32+=(Length&0x00000001);PtrA.C.G<End.C.G;PtrA.C.D32++,PtrC.C.D32++)
		PtrC.V.D32[0]=PtrA.C.D32[0]|Mask;
}
general BitC_BO_O_1_D64_(data_32 _PL_ DataC,DATA_32 _PL_ DataA,DATA_64 Mask,DATA_32 Length)
{
	bitclip End;
	bitclip PtrA;
	bitclip PtrC;

	{
		End.C.G=DataA;
		PtrA.C.G=DataA;
		PtrC.C.G=DataC;
	}
	for(End.C.D64+=(Length&0xFFFFFFF8);PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrC.C.D64+=8)
	{
		PtrC.V.D64[0]=PtrA.C.D64[0]|Mask;
		PtrC.V.D64[1]=PtrA.C.D64[1]|Mask;
		PtrC.V.D64[2]=PtrA.C.D64[2]|Mask;
		PtrC.V.D64[3]=PtrA.C.D64[3]|Mask;
		PtrC.V.D64[4]=PtrA.C.D64[4]|Mask;
		PtrC.V.D64[5]=PtrA.C.D64[5]|Mask;
		PtrC.V.D64[6]=PtrA.C.D64[6]|Mask;
		PtrC.V.D64[7]=PtrA.C.D64[7]|Mask;
	}
	for(End.C.D64+=(Length&0x00000007);PtrA.C.G<End.C.G;PtrA.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=PtrA.C.D64[0]|Mask;
}
general BitC_BO_O_2_D08_(data_08 _PL_ DataC,DATA_08 _PL_ DataA,DATA_08 _PL_ DataB,DATA_32 Length)
{
	bitclip End;
	bitclip PtrA;
	bitclip PtrB;
	bitclip PtrC;

	{
		End.C.G=DataA;
		PtrA.C.G=DataA;
		PtrB.C.G=DataB;
		PtrC.C.G=DataC;
	}
	for(End.C.D08+=(Length&0xFFFFFFC0);PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrB.C.D64+=8,PtrC.C.D64+=8)
	{
		PtrC.V.D64[0]=PtrA.C.D64[0]|PtrB.C.D64[0];
		PtrC.V.D64[1]=PtrA.C.D64[1]|PtrB.C.D64[1];
		PtrC.V.D64[2]=PtrA.C.D64[2]|PtrB.C.D64[2];
		PtrC.V.D64[3]=PtrA.C.D64[3]|PtrB.C.D64[3];
		PtrC.V.D64[4]=PtrA.C.D64[4]|PtrB.C.D64[4];
		PtrC.V.D64[5]=PtrA.C.D64[5]|PtrB.C.D64[5];
		PtrC.V.D64[6]=PtrA.C.D64[6]|PtrB.C.D64[6];
		PtrC.V.D64[7]=PtrA.C.D64[7]|PtrB.C.D64[7];
	}
	for(End.C.D08+=(Length&0x00000038);PtrA.C.G<End.C.G;PtrA.C.D64++,PtrB.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=PtrA.C.D64[0]|PtrB.C.D64[0];
	for(End.C.D08+=(Length&0x00000007);PtrA.C.G<End.C.G;PtrA.C.D08++,PtrB.C.D08++,PtrC.C.D08++)
		PtrC.V.D08[0]=PtrA.C.D08[0]|PtrB.C.D08[0];
}

general BitC_BO_X_1_D08_(data_08 _PL_ DataC,DATA_08 _PL_ DataA,DATA_08 Mask,DATA_32 Length)
{
	DATA_64 Wide=_BitC_Wide_Mask_D08_(Mask);
	bitclip End;
	bitclip PtrA;
	bitclip PtrC;

	{
		End.C.G=DataA;
		PtrA.C.G=DataA;
		PtrC.C.G=DataC;
	}
	for(End.C.D08+=(Length&0xFFFFFFC0);PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrC.C.D64+=8)
	{
		PtrC.V.D64[0]=PtrA.C.D64[0]^Wide;
		PtrC.V.D64[1]=PtrA.C.D64[1]^Wide;
		PtrC.V.D64[2]=PtrA.C.D64[2]^Wide;
		PtrC.V.D64[3]=PtrA.C.D64[3]^Wide;
		PtrC.V.D64[4]=PtrA.C.D64[4]^Wide;
		PtrC.V.D64[5]=PtrA.C.D64[5]^Wide;
		PtrC.V.D64[6]=PtrA.C.D64[6]^Wide;
		PtrC.V.D64[7]=PtrA.C.D64[7]^Wide;
	}
	for(End.C.D08+=(Length&0x00000038);PtrA.C.G<End.C.G;PtrA.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=PtrA.C.D64[0]^Wide;
	for(End.C.D08+=(Length&0x00000007);PtrA.C.G<End.C.G;PtrA.C.D08++,PtrC.C.D08++)
		PtrC.V.D08[0]=PtrA.C.D08[0]^Mask;
}
general BitC_BO_X_1_D16_(data_16 _PL_ DataC,DATA_16 _PL_ DataA,DATA_16 Mask,DATA_32 Length)
{
	DATA_64 Wide=_BitC_Wide_Mask_D16_(Mask);
	bitclip End;
	bitclip PtrA;
	bitclip PtrC;

	{
		End.C.G=DataA;
		PtrA.C.G=DataA;
		PtrC.C.G=DataC;
	}
	for(End.C.D16+=(Length&0xFFFFFFE0);PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrC.C.D64+=8)
	{
		PtrC.V.D64[0]=PtrA.C.D64[0]^Wide;
		PtrC.V.D64[1]=PtrA.C.D64[1]^Wide;
		PtrC.V.D64[2]=PtrA.C.D64[2]^Wide;
		PtrC.V.D64[3]=PtrA.C.D64[3]^Wide;
		PtrC.V.D64[4]=PtrA.C.D64[4]^Wide;
		PtrC.V.D64[5]=PtrA.C.D64[5]^Wide;
		PtrC.V.D64[6]=PtrA.C.D64[6]^Wide;
		PtrC.V.D64[7]=PtrA.C.D64[7]^Wide;
	}
	for(End.C.D16+=(Length&0x0000001C);PtrA.C.G<End.C.G;PtrA.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=PtrA.C.D64[0]^Wide;
	for(End.C.D16+=(Length&0x00000003);PtrA.C.G<End.C.G;PtrA.C.D16++,PtrC.C.D16++)
		PtrC.V.D16[0]=PtrA.C.D16[0]^Mask;
}
general BitC_BO_X_1_D32_(data_32 _PL_ DataC,DATA_32 _PL_ DataA,DATA_32 Mask,DATA_32 Length)
{
	DATA_64 Wide=_BitC_Wide_Mask_D32_(Mask);
	bitclip End;
	bitclip PtrA;
	bitclip PtrC;

	{
		End.C.G=DataA;
		PtrA.C.G=DataA;
		PtrC.C.G=DataC;
	}
	for(End.C.D32+=(Length&0xFFFFFFF0);PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrC.C.D64+=8)
	{
		PtrC.V.D64[0]=PtrA.C.D64[0]^Wide;
		PtrC.V.D64[1]=PtrA.C.D64[1]^Wide;
		PtrC.V.D64[2]=PtrA.C.D64[2]^Wide;
		PtrC.V.D64[3]=PtrA.C.D64[3]^Wide;
		PtrC.V.D64[4]=PtrA.C.D64[4]^Wide;
		PtrC.V.D64[5]=PtrA.C.D64[5]^Wide;
		PtrC.V.D64[6]=PtrA.C.D64[6]^Wide;
		PtrC.V.D64[7]=PtrA.C.D64[7]^Wide;
	}
	for(End.C.D32+=(Length&0x0000000E);PtrA.C.G<End.C.G;PtrA.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=PtrA.C.D64[0]^Wide;
	for(End.C.D32+=(Length&0x00000001);PtrA.C.G<End.C.G;PtrA.C.D32++,PtrC.C.D32++)
		PtrC.V.D32[0]=PtrA.C.D32[0]^Mask;
}
general BitC_BO_X_1_D64_(data_32 _PL_ DataC,DATA_32 _PL_ DataA,DATA_64 Mask,DATA_32 Length)
{
	bitclip End;
	bitclip PtrA;
	bitclip PtrC;

	{
		End.C.G=DataA;
		PtrA.C.G=DataA;
		PtrC.C.G=DataC;
	}
	for(End.C.D64+=(Length&0xFFFFFFF8);PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrC.C.D64+=8)
	{
		PtrC.V.D64[0]=PtrA.C.D64[0]^Mask;
		PtrC.V.D64[1]=PtrA.C.D64[1]^Mask;
		PtrC.V.D64[2]=PtrA.C.D64[2]^Mask;
		PtrC.V.D64[3]=PtrA.C.D64[3]^Mask;
		PtrC.V.D64[4]=PtrA.C.D64[4]^Mask;
		PtrC.V.D64[5]=PtrA.C.D64[5]^Mask;
		PtrC.V.D64[6]=PtrA.C.D64[6]^Mask;
		PtrC.V.D64[7]=PtrA.C.D64[7]^Mask;
	}
	for(End.C.D64+=(Length&0x00000007);PtrA.C.G<End.C.G;PtrA.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=PtrA.C.D64[0]^Mask;
}
general BitC_BO_X_2_D08_(data_08 _PL_ DataC,DATA_08 _PL_ DataA,DATA_08 _PL_ DataB,DATA_32 Length)
{
	bitclip End;
	bitclip PtrA;
	bitclip PtrB;
	bitclip PtrC;

	{
		End.C.G=DataA;
		PtrA.C.G=DataA;
		PtrB.C.G=DataB;
		PtrC.C.G=DataC;
	}
	for(End.C.D08+=(Length&0xFFFFFFC0);PtrA.C.G<End.C.G;PtrA.C.D64+=8,PtrB.C.D64+=8,PtrC.C.D64+=8)
	{
		PtrC.V.D64[0]=PtrA.C.D64[0]^PtrB.C.D64[0];
		PtrC.V.D64[1]=PtrA.C.D64[1]^PtrB.C.D64[1];
		PtrC.V.D64[2]=PtrA.C.D64[2]^PtrB.C.D64[2];
		PtrC.V.D64[3]=PtrA.C.D64[3]^PtrB.C.D64[3];
		PtrC.V.D64[4]=PtrA.C.D64[4]^PtrB.C.D64[4];
		PtrC.V.D64[5]=PtrA.C.D64[5]^PtrB.C.D64[5];
		PtrC.V.D64[6]=PtrA.C.D64[6]^PtrB.C.D64[6];
		PtrC.V.D64[7]=PtrA.C.D64[7]^PtrB.C.D64[7];
	}
	for(End.C.D08+=(Length&0x00000038);PtrA.C.G<End.C.G;PtrA.C.D64++,PtrB.C.D64++,PtrC.C.D64++)
		PtrC.V.D64[0]=PtrA.C.D64[0]^PtrB.C.D64[0];
	for(End.C.D08+=(Length&0x00000007);PtrA.C.G<End.C.G;PtrA.C.D08++,PtrB.C.D08++,PtrC.C.D08++)
		PtrC.V.D08[0]=PtrA.C.D08[0]^PtrB.C.D08[0];
}
#endif

#if(MemC_Fold_(Undefinition:Macros))
#undef _BitC_Total_Kernels
#undef _BitC_Kernel_Name_Length
#undef _BitC_Clamp_
#undef _BitC_Max_
#undef _BitC_Min_
#endif
