﻿#include "linclip.h"

#if(MemC_Fold_(Definition:Global Constants))
static DATA_08 IdiomVersion[16]="Date:2019.03.22";
static ADDRESS ConstantSize[2]={sizeof(real_32),sizeof(real_64)};

#ifdef __OPENCL_H
static NAME_08 IdiomFileName[40]="ouoclip.cl\0\0linclip.cl\0\0linclip.obj";
static NAME_08 IdiomKernelName[LinCKernels][16]=
{
	"LinC_Ari_0_I08_",	"LinC_Ari_0_I16_",	"LinC_Ari_0_I32_",	"LinC_Ari_0_I64_",
	"",					"LinC_Ari_0_R16_",	"LinC_Ari_0_R32_",	"LinC_Ari_0_R64_",
	"LinC_Geo_0_I08_",	"LinC_Geo_0_I16_",	"LinC_Geo_0_I32_",	"LinC_Geo_0_I64_",
	"",					"LinC_Geo_0_R16_",	"LinC_Geo_0_R32_",	"LinC_Geo_0_R64_",
	"LinC_Inc_1_I08_",	"LinC_Inc_1_I16_",	"LinC_Inc_1_I32_",	"LinC_Inc_1_I64_",
	"",					"LinC_Inc_1_R16_",	"LinC_Inc_1_R32_",	"LinC_Inc_1_R64_",
	"LinC_Amp_1_I08_",	"LinC_Amp_1_I16_",	"LinC_Amp_1_I32_",	"LinC_Amp_1_I64_",
	"",					"LinC_Amp_1_R16_",	"LinC_Amp_1_R32_",	"LinC_Amp_1_R64_",
	"LinC_Add_2_I08_",	"LinC_Add_2_I16_",	"LinC_Add_2_I32_",	"LinC_Add_2_I64_",
	"",					"LinC_Add_2_R16_",	"LinC_Add_2_R32_",	"LinC_Add_2_R64_",
	"LinC_Sub_2_I08_",	"LinC_Sub_2_I16_",	"LinC_Sub_2_I32_",	"LinC_Sub_2_I64_",
	"",					"LinC_Sub_2_R16_",	"LinC_Sub_2_R32_",	"LinC_Sub_2_R64_",
	"LinC_Mul_2_I08_",	"LinC_Mul_2_I16_",	"LinC_Mul_2_I32_",	"LinC_Mul_2_I64_",
	"",					"LinC_Mul_2_R16_",	"LinC_Mul_2_R32_",	"LinC_Mul_2_R64_",
	"LinC_Div_2_I08_",	"LinC_Div_2_I16_",	"LinC_Div_2_I32_",	"LinC_Div_2_I64_",
	"LinC_Div_2_D08_",	"LinC_Div_2_D16_",	"LinC_Div_2_D32_",	"LinC_Div_2_D64_",
	"",					"LinC_Div_2_R16_",	"LinC_Div_2_R32_",	"LinC_Div_2_R64_",
	"LinC_Div_1_I08_",	"LinC_Div_1_I16_",	"LinC_Div_1_I32_",	"LinC_Div_1_I64_",
	"LinC_Div_1_D08_",	"LinC_Div_1_D16_",	"LinC_Div_1_D32_",	"LinC_Div_1_D64_",
	"LinC_Inv_1_I08_",	"LinC_Inv_1_I16_",	"LinC_Inv_1_I32_",	"LinC_Inv_1_I64_",
	"LinC_Inv_1_D08_",	"LinC_Inv_1_D16_",	"LinC_Inv_1_D32_",	"LinC_Inv_1_D64_",
	"",					"LinC_Inv_1_R16_",	"LinC_Inv_1_R32_",	"LinC_Inv_1_R64_",
	"LinC_Sum_1_I08_",	"LinC_Sum_1_I16_",	"LinC_Sum_1_I32_",	"LinC_Sum_1_I64_",
	"",					"LinC_Sum_1_R16_",	"LinC_Sum_1_R32_",	"LinC_Sum_1_R64_",
	"LinC_Dot_2_I08_",	"LinC_Dot_2_I16_",	"LinC_Dot_2_I32_",	"LinC_Dot_2_I64_",
	"",					"LinC_Dot_2_R16_",	"LinC_Dot_2_R32_",	"LinC_Dot_2_R64_",
	"LinC_Max_1_I08_",	"LinC_Max_1_I16_",	"LinC_Max_1_I32_",	"LinC_Max_1_I64_",
	"LinC_Max_1_D08_",	"LinC_Max_1_D16_",	"LinC_Max_1_D32_",	"LinC_Max_1_D64_",
	"",					"LinC_Max_1_R16_",	"LinC_Max_1_R32_",	"LinC_Max_1_R64_",
	"LinC_Min_1_I08_",	"LinC_Min_1_I16_",	"LinC_Min_1_I32_",	"LinC_Min_1_I64_",
	"LinC_Min_1_D08_",	"LinC_Min_1_D16_",	"LinC_Min_1_D32_",	"LinC_Min_1_D64_",
	"",					"LinC_Min_1_R16_",	"LinC_Min_1_R32_",	"LinC_Min_1_R64_",
	"LinC_Map_1_D08_",	"LinC_Map_1_D16_",	"LinC_Map_1_D32_",	"LinC_Map_1_D64_"
};

static NAME_08 _PL_ AddressFileName[4]={IdiomFileName+0,IdiomFileName+12,IdiomFileName+24,NULL};
static NAME_08 _PL_ AddressKernelName[LinCKernels]=
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
	IdiomKernelName[128],IdiomKernelName[129],IdiomKernelName[130],IdiomKernelName[131]
};
#endif

DATA_08 _PL_ LinClip=IdiomVersion;
#ifdef __OPENCL_H
NAME_08 _PL_ _PL_ LinCFile=AddressFileName;
NAME_08 _PL_ _PL_ LinCKernel=AddressKernelName;
#endif
#endif

#if(MemC_Fold_(Definition:LinCrux Macros))
#define _LinC_TXX_(Type,Bits) Type##Bits
#define LinC_TXX_(Type,Bits) _LinC_TXX_(Type,Bits)

#define _LinC_Type_(Type,Bits) Type##_##Bits
#define LinC_Type_(Type,Bits) _LinC_Type_(Type,Bits)

#define _LinC_Func_(Name,Suffix) Name##Suffix##_
#define LinC_Func_(Name,Suffix) _LinC_Func_(Name,Suffix)

#define _LinC_Oper_(Oper,N,TXX) Oper##N##_##TXX##_
#define LinC_Oper_(Oper,N,TXX) _LinC_Oper_(Oper,N,TXX)

#define LinC_Ari_(U,V) ((U)+(V))
#define LinC_Geo_(U,V) ((U)*(V))
#define LinC_Inc_(U,V) ((U)+(V))
#define LinC_Amp_(U,V) ((U)*(V))
#define LinC_Add_(U,V) ((U)+(V))
#define LinC_Sub_(U,V) ((U)-(V))
#define LinC_Mul_(U,V) ((U)*(V))
#define LinC_Div_(U,V) ((U)/(V))
#define LinC_Inv_(U,V) ((V)/(U))
#define LinC_Mod_(U,V) ((U)%(V))
#define LinC_Max_(U,V) ((U)<(V))
#define LinC_Min_(U,V) ((U)>(V))
#endif

#if(MemC_Fold_(Definition: Arithmetic and Geometric Progression Functions))
#define _LinC_Operation_0_
#define _LinC_Inte_
#define _LinC_Real_
#define LinC_Op_ LinC_Ari_
#include "lincrux.c"
#undef LinC_Op_
#define LinC_Op_ LinC_Geo_
#include "lincrux.c"
#undef LinC_Op_
#undef _LinC_Real_
#undef _LinC_Inte_
#undef _LinC_Operation_0_
#endif

#if(MemC_Fold_(Definition:Increment and Amplification Functions))
#define _LinC_Operation_1_
#define _LinC_Inte_
#define _LinC_Real_
#define LinC_Op_ LinC_Inc_
#include "lincrux.c"
#undef LinC_Op_
#define LinC_Op_ LinC_Amp_
#include "lincrux.c"
#undef LinC_Op_
#undef _LinC_Real_
#undef _LinC_Inte_
#undef _LinC_Operation_1_
#endif

#if(MemC_Fold_(Definition:Addition, Subtraction, and Multiplication Functions))
#define _LinC_Operation_2_
#define _LinC_Inte_
#define _LinC_Real_
#define LinC_Op_ LinC_Add_
#include "lincrux.c"
#undef LinC_Op_
#define LinC_Op_ LinC_Sub_
#include "lincrux.c"
#undef LinC_Op_
#define LinC_Op_ LinC_Mul_
#include "lincrux.c"
#undef LinC_Op_
#undef _LinC_Real_
#undef _LinC_Inte_
#undef _LinC_Operation_2_
#endif

#if(MemC_Fold_(Definition:Division Functions))
#define _LinC_Operation_2_
#define LinC_Op_ LinC_Div_
#define _LinC_Data_
#define _LinC_Inte_
#define _LinC_Real_
#include "lincrux.c"
#undef _LinC_Real_
#undef _LinC_Operation_2_
#define _LinC_Operation_1_
#include "lincrux.c"
#undef LinC_Op_
#define LinC_Op_ LinC_Inv_
#define _LinC_Real_
#include "lincrux.c"
#undef _LinC_Real_
#undef _LinC_Inte_
#undef _LinC_Data_
#undef LinC_Op_
#undef _LinC_Operation_1_
#endif

#if(MemC_Fold_(Definition:Modulo Functions))
#define _LinC_Operation_1_
#define LinC_Op_ LinC_Mod_
#define _LinC_Data_
#define _LinC_Inte_
#include "lincrux.c"
#undef _LinC_Inte_
#undef _LinC_Data_
#undef LinC_Op_
#undef _LinC_Operation_1_
#endif

#if(MemC_Fold_(Definition:Summation and Dot-Product Functions))
#define _LinC_Summation_
#define _LinC_Inte_
#define _LinC_Real_
#include "lincrux.c"
#undef _LinC_Real_
#undef _LinC_Inte_
#undef _LinC_Summation_
#endif

#if(MemC_Fold_(Definition:Maximum and Minimum Functions))
#define _LinC_Min_Max_
#define _LinC_Data_
#define _LinC_Inte_
#define _LinC_Real_
#define LinC_Op_ LinC_Max_
#include "lincrux.c"
#undef LinC_Op_
#define LinC_Op_ LinC_Min_
#include "lincrux.c"
#undef LinC_Op_
#undef _LinC_Real_
#undef _LinC_Inte_
#undef _LinC_Data_
#undef _LinC_Min_Max_
#endif

#if(MemC_Fold_(Definition:Mapping and Radix Sorting Functions))
static inline general _LinC_Swap_D08_(data_08 _PL_,INTEGER _PL_);
static inline general _LinC_Swap_D16_(data_16 _PL_,INTEGER _PL_);
static inline general _LinC_Swap_D32_(data_32 _PL_,INTEGER _PL_);
static inline general _LinC_Swap_D64_(data_64 _PL_,INTEGER _PL_);

#define _LinC_Sorting_
#define _LinC_Data_
#include "lincrux.c"
#undef _LinC_Data_
#undef _LinC_Sorting_

general LinC_Order_D08_(data_08 _PL_ Line,data_32 _PL_ Index,general _PL_ Buffer,DATA_32 Length,BOOLEAN Mode)
{
	if(Length)
	{
		data_32 _PL_ IndexTemp=(data_32*)Buffer;
		data_08 _PL_ ValueTemp=(data_08*)(IndexTemp+Length);

		_LinC_Recur_D08_(Line,Index,ValueTemp,IndexTemp,Length,~BitCBool[Mode&1],7);
	}
}
general LinC_Order_D16_(data_16 _PL_ Line,data_32 _PL_ Index,general _PL_ Buffer,DATA_32 Length,BOOLEAN Mode)
{
	if(Length)
	{
		data_32 _PL_ IndexTemp=(data_32*)Buffer;
		data_16 _PL_ ValueTemp=(data_16*)(IndexTemp+Length);

		_LinC_Recur_D16_(Line,Index,ValueTemp,IndexTemp,Length,~BitCBool[Mode&1],15);
	}
}
general LinC_Order_D32_(data_32 _PL_ Line,data_32 _PL_ Index,general _PL_ Buffer,DATA_32 Length,BOOLEAN Mode)
{
	if(Length)
	{
		data_32 _PL_ IndexTemp=(data_32*)Buffer;
		data_32 _PL_ ValueTemp=(data_32*)(IndexTemp+Length);

		_LinC_Recur_D32_(Line,Index,ValueTemp,IndexTemp,Length,~BitCBool[Mode&1],31);
	}
}
general LinC_Order_D64_(data_64 _PL_ Line,data_32 _PL_ Index,general _PL_ Buffer,DATA_32 Length,BOOLEAN Mode)
{
	if(Length)
	{
		data_32 _PL_ IndexTemp=(data_32*)Buffer;
		data_64 _PL_ ValueTemp=(data_64*)(IndexTemp+Length);

		_LinC_Recur_D64_(Line,Index,ValueTemp,IndexTemp,Length,~BitCBool[Mode&1],63);
	}
}
general LinC_Order_I08_(inte_08 _PL_ Line,data_32 _PL_ Index,general _PL_ Buffer,DATA_32 Length,BOOLEAN Mode)
{
	if(Length)
	{
		data_32 _PL_ IndexTemp=(data_32*)Buffer;
		inte_08 _PL_ ValueTemp=(inte_08*)(IndexTemp+Length);
		data_32 Offset;

		Offset=(data_32)((inte_08*)_LinC_Radix_D08_((data_08*)ValueTemp,IndexTemp,(data_08*)Line,Index,Length,~BitCBool[Mode&1],0x80)-ValueTemp);
		if(Offset)
			_LinC_Recur_D08_((data_08*)ValueTemp,IndexTemp,(data_08*)Line,Index,Offset,Mode,6);
		if(Offset<Length)
			_LinC_Recur_D08_((data_08*)(ValueTemp+Offset),IndexTemp+Offset,(data_08*)(Line+Offset),Index+Offset,Length-Offset,Mode,6);
	}
}
general LinC_Order_I16_(inte_16 _PL_ Line,data_32 _PL_ Index,general _PL_ Buffer,DATA_32 Length,BOOLEAN Mode)
{
	if(Length)
	{
		data_32 _PL_ IndexTemp=(data_32*)Buffer;
		inte_16 _PL_ ValueTemp=(inte_16*)(IndexTemp+Length);
		data_32 Offset;

		Offset=(data_32)((inte_16*)_LinC_Radix_D16_((data_16*)ValueTemp,IndexTemp,(data_16*)Line,Index,Length,~BitCBool[Mode&1],0x8000)-ValueTemp);
		if(Offset)
			_LinC_Recur_D16_((data_16*)ValueTemp,IndexTemp,(data_16*)Line,Index,Offset,Mode,14);
		if(Offset<Length)
			_LinC_Recur_D16_((data_16*)(ValueTemp+Offset),IndexTemp+Offset,(data_16*)(Line+Offset),Index+Offset,Length-Offset,Mode,14);
	}
}
general LinC_Order_I32_(inte_32 _PL_ Line,data_32 _PL_ Index,general _PL_ Buffer,DATA_32 Length,BOOLEAN Mode)
{
	if(Length)
	{
		data_32 _PL_ IndexTemp=(data_32*)Buffer;
		inte_32 _PL_ ValueTemp=(inte_32*)(IndexTemp+Length);
		data_32 Offset;

		Offset=(data_32)((inte_32*)_LinC_Radix_D32_((data_32*)ValueTemp,IndexTemp,(data_32*)Line,Index,Length,~BitCBool[Mode&1],0x80000000U)-ValueTemp);
		if(Offset)
			_LinC_Recur_D32_((data_32*)ValueTemp,IndexTemp,(data_32*)Line,Index,Offset,Mode,30);
		if(Offset<Length)
			_LinC_Recur_D32_((data_32*)(ValueTemp+Offset),IndexTemp+Offset,(data_32*)(Line+Offset),Index+Offset,Length-Offset,Mode,30);
	}
}
general LinC_Order_I64_(inte_64 _PL_ Line,data_32 _PL_ Index,general _PL_ Buffer,DATA_32 Length,BOOLEAN Mode)
{
	if(Length)
	{
		data_32 _PL_ IndexTemp=(data_32*)Buffer;
		inte_64 _PL_ ValueTemp=(inte_64*)(IndexTemp+Length);
		data_32 Offset;

		Offset=(data_32)((inte_64*)_LinC_Radix_D64_((data_64*)ValueTemp,IndexTemp,(data_64*)Line,Index,Length,~BitCBool[Mode&1],0x8000000000000000UL)-ValueTemp);
		if(Offset)
			_LinC_Recur_D64_((data_64*)ValueTemp,IndexTemp,(data_64*)Line,Index,Offset,Mode,62);
		if(Offset<Length)
			_LinC_Recur_D64_((data_64*)(ValueTemp+Offset),IndexTemp+Offset,(data_64*)(Line+Offset),Index+Offset,Length-Offset,Mode,62);
	}
}
general LinC_Order_R32_(real_32 _PL_ Line,data_32 _PL_ Index,general _PL_ Buffer,DATA_32 Length,BOOLEAN Mode)
{
	if(Length)
	{
		data_32 _PL_ IndexTemp=(data_32*)Buffer;
		real_32 _PL_ ValueTemp=(real_32*)(IndexTemp+Length);
		data_32 Offset;

		Offset=(data_32)((real_32*)_LinC_Radix_D32_((data_32*)ValueTemp,IndexTemp,(data_32*)Line,Index,Length,~BitCBool[Mode&1],0x80000000U)-ValueTemp);
		if(Offset)
			_LinC_Recur_D32_((data_32*)ValueTemp,IndexTemp,(data_32*)Line,Index,Offset,BitCFull,30);
		if(Offset<Length)
			_LinC_Recur_D32_((data_32*)(ValueTemp+Offset),IndexTemp+Offset,(data_32*)(Line+Offset),Index+Offset,Length-Offset,BitCNull,30);
	}
}
general LinC_Order_R64_(real_64 _PL_ Line,data_32 _PL_ Index,general _PL_ Buffer,DATA_32 Length,BOOLEAN Mode)
{
	if(Length)
	{
		data_32 _PL_ IndexTemp=(data_32*)Buffer;
		real_64 _PL_ ValueTemp=(real_64*)(IndexTemp+Length);
		data_32 Offset;
		
		Offset=(data_32)((real_64*)_LinC_Radix_D64_((data_64*)ValueTemp,IndexTemp,(data_64*)Line,Index,Length,~BitCBool[Mode&1],0x8000000000000000UL)-ValueTemp);
		if(Offset)
			_LinC_Recur_D64_((data_64*)ValueTemp,IndexTemp,(data_64*)Line,Index,Offset,BitCFull,62);
		if(Offset<Length)
			_LinC_Recur_D64_((data_64*)(ValueTemp+Offset),IndexTemp+Offset,(data_64*)(Line+Offset),Index+Offset,Length-Offset,BitCNull,62);
	}
}
#endif

#if(MemC_Fold_(Definition:LinClip Managed Functions))
#ifdef __OPENCL_H
static NAME_08 *_LinC_Path_(name_08 _PL_ Buffer,NAME_08 _PL_ Prefix,NAME_08 _PL_ Name,ADDRESS Capacity)
{
	NAME_08 *Return;

	if(Prefix)
		if(PenC_String_Copier_N08_(Buffer,Prefix,Capacity))
			Return=NULL;
		else
			if(PenC_String_Concat_N08_(Buffer,Name,Capacity))
				Return=NULL;
			else
				Return=Buffer;
	else
		Return=Name;

	return Return;
}
penc_eu LinC_CL_Binary_(cl_command_queue const Queue,NAME_08 _PL_ DirSrc,NAME_08 _PL_ DirBin,NAME_08 _PL_ Option,FILE _PL_ Stream)
{
	ADDRESS Length=1024;
	name_08 _PL_ _PL_ Buffer=MemC_Alloc_2D_(3,Length,name_08);
	penc_eu Error;

	if(Buffer)
	{
		NAME_08 *Name[3];

		Name[0]=_LinC_Path_(Buffer[0],DirSrc,LinCFile[0],Length);
		Name[1]=_LinC_Path_(Buffer[1],DirSrc,LinCFile[1],Length);
		Name[2]=_LinC_Path_(Buffer[2],DirBin,LinCFile[2],Length);
		if(MemC_Check_(Name,3))
			Error=PenC_CL_Binary_(Queue,Name[2],Name,Option,2,Stream);
		else
			Error.E=CLOutOfHostMemory;
	}
	else
		Error.E=CLOutOfHostMemory;

	MemC_Deloc_(Acs_(name_08**,Buffer));

	return Error;
}

static devi_km *_LinC_Create_KM_GPPP_(cl_kernel const Kernel,GENERAL _PL_ ID,ADDRESS TypeSize)
{
	devi_km *KM=Devi_KM_Create_(ID,4,1);

	if(KM)
	{
		penc_eu Error={.E=CLSuccess};

		Error.I|=Devi_KM_Type_G_(KM,0);
		Error.I|=_Devi_KM_Type_(KM,1,TypeSize,DeviDomainPrivate);
		Error.I|=_Devi_KM_Type_(KM,2,TypeSize,DeviDomainPrivate);
		Error.I|=Devi_KM_Type_P_(KM,3,data_32);
		Error.I|=Devi_KM_Init_(KM,Kernel);
		if(Error.E!=CLSuccess)
			Devi_KM_Delete_(&KM);
	}

	return KM;
}
static devi_km *_LinC_Create_KM_GGPP_(cl_kernel const Kernel,GENERAL _PL_ ID,ADDRESS TypeSize)
{
	devi_km *KM=Devi_KM_Create_(ID,4,1);

	if(KM)
	{
		penc_eu Error={.E=CLSuccess};

		Error.I|=Devi_KM_Type_G_(KM,0);
		Error.I|=Devi_KM_Type_G_(KM,1);
		Error.I|=_Devi_KM_Type_(KM,2,TypeSize,DeviDomainPrivate);
		Error.I|=Devi_KM_Type_P_(KM,3,data_32);
		Error.I|=Devi_KM_Init_(KM,Kernel);
		if(Error.E!=CLSuccess)
			Devi_KM_Delete_(&KM);
	}

	return KM;
}
static devi_km *_LinC_Create_KM_GGGP_(cl_kernel const Kernel,GENERAL _PL_ ID)
{
	devi_km *KM=Devi_KM_Create_(ID,4,1);

	if(KM)
	{
		penc_eu Error={.E=CLSuccess};

		Error.I|=Devi_KM_Type_G_(KM,0);
		Error.I|=Devi_KM_Type_G_(KM,1);
		Error.I|=Devi_KM_Type_G_(KM,2);
		Error.I|=Devi_KM_Type_P_(KM,3,data_32);
		Error.I|=Devi_KM_Init_(KM,Kernel);
		if(Error.E!=CLSuccess)
			Devi_KM_Delete_(&KM);
	}

	return KM;
}
static devi_km *_LinC_Create_KM_GLGP_(cl_kernel const Kernel,GENERAL _PL_ ID,ADDRESS TypeSize)
{
	devi_km *KM=Devi_KM_Create_(ID,4,1);

	if(KM)
	{
		penc_eu Error={.E=CLSuccess};

		Error.I|=Devi_KM_Type_G_(KM,0);
		Error.I|=_Devi_KM_Type_(KM,1,TypeSize,DeviDomainLocal);
		Error.I|=Devi_KM_Type_G_(KM,2);
		Error.I|=Devi_KM_Type_P_(KM,3,data_32);
		Error.I|=Devi_KM_Init_(KM,Kernel);
		if(Error.E!=CLSuccess)
			Devi_KM_Delete_(&KM);
	}

	return KM;
}
static devi_km *_LinC_Create_KM_GLGGP_(cl_kernel const Kernel,GENERAL _PL_ ID,ADDRESS TypeSize)
{
	devi_km *KM=Devi_KM_Create_(ID,5,1);

	if(KM)
	{
		penc_eu Error={.E=CLSuccess};

		Error.I|=Devi_KM_Type_G_(KM,0);
		Error.I|=_Devi_KM_Type_(KM,1,TypeSize,DeviDomainLocal);
		Error.I|=Devi_KM_Type_G_(KM,2);
		Error.I|=Devi_KM_Type_G_(KM,3);
		Error.I|=Devi_KM_Type_P_(KM,4,data_32);
		Error.I|=Devi_KM_Init_(KM,Kernel);
		if(Error.E!=CLSuccess)
			Devi_KM_Delete_(&KM);
	}

	return KM;
}
static devi_km *_LinC_Create_KM_GGGPP_(cl_kernel const Kernel,GENERAL _PL_ ID)
{
	devi_km *KM=Devi_KM_Create_(ID,5,1);

	if(KM)
	{
		penc_eu Error={.E=CLSuccess};

		Error.I|=Devi_KM_Type_G_(KM,0);
		Error.I|=Devi_KM_Type_G_(KM,1);
		Error.I|=Devi_KM_Type_G_(KM,2);
		Error.I|=Devi_KM_Type_P_(KM,3,data_32);
		Error.I|=Devi_KM_Type_P_(KM,4,data_32);
		Error.I|=Devi_KM_Init_(KM,Kernel);
		if(Error.E!=CLSuccess)
			Devi_KM_Delete_(&KM);
	}

	return KM;
}
static devi_km *_LinC_Create_KM_(cl_kernel const Kernel,LINC_KI Switch)
{
	ADDRESS TypeSize=(address)(1<<(Switch&3));
	devi_km *KM;

	switch(Switch>>2)
	{
	case 0:case 1:case 2:case 3:
		KM=_LinC_Create_KM_GPPP_(Kernel,LinCKernel[Switch],TypeSize);
		break;
	case 4:case 5:case 6:case 7:
	case 17:case 18:case 19:case 20:case 21:
		KM=_LinC_Create_KM_GGPP_(Kernel,LinCKernel[Switch],TypeSize);
		break;
	case 8:case 9:case 10:case 11:case 12:case 13:case 14:case 15:case 16:
		KM=_LinC_Create_KM_GGGP_(Kernel,LinCKernel[Switch]);
		break;
	case 22:case 23:
		KM=_LinC_Create_KM_GLGP_(Kernel,LinCKernel[Switch],TypeSize);
		break;
	case 26:case 27:case 28:case 29:case 30:case 31:
		KM=_LinC_Create_KM_GLGP_(Kernel,LinCKernel[Switch],sizeof(data_32)+TypeSize);
		break;
	case 24:case 25:
		KM=_LinC_Create_KM_GLGGP_(Kernel,LinCKernel[Switch],TypeSize);
		break;
	case 32:
		KM=_LinC_Create_KM_GGGPP_(Kernel,LinCKernel[Switch]);
		break;
	default:
		KM=NULL;
	}

	return KM;
}
linc_cl *LinC_CL_Create_(general)
{
	linc_cl *Manager=MemC_Alloc_Byte_(sizeof(linc_cl)+MemC_Size_(devi_km*,LinCKernels));

	if(Manager)
	{
		Acs_(GENERAL*,Manager->Helper)=NULL;
		Acs_(devi_km**,Manager->KMSet)=MemC_Clear_1D_((devi_km**)(Manager+1),LinCKernels);
	}

	return Manager;
}
address *LinC_CL_Choice_(LINC_CL _PL_ Manager)
{
	address *Table;

	if(Manager)
		if(Manager->Helper)
			Table=NULL;
		else
			Table=(address*)(Manager->KMSet);
	else
		Table=NULL;

	return Table;
}
penc_eu LinC_CL_Launch_(cl_command_queue const Queue,LINC_CL _PL_ Manager,NAME_08 _PL_ DirBin,NAME_08 _PL_ Option,FILE _PL_ Stream)
{
	penc_eu Error;

	if(Manager)
		if(Manager->Helper)
			Error.E=CLInvalidHostPtr;
		else
		{
			GENERAL *Slot[LinCKernels];
			linc_ki Link[LinCKernels];
			cl_uint Count=0;

			{
				bitc_ki Index;

				for(Index=0;Index<LinCKernels;Index++)
					if(Manager->KMSet[Index])
					{
						Slot[Count]=LinCKernel[Index];
						Link[Count]=Index;
						Count++;
					}
			}
			if(Count)
			{
				ADDRESS Length=1024;
				name_08 *Buffer=MemC_Alloc_1D_(Length,name_08);

				if(Buffer)
				{
					NAME_08 *Name=_LinC_Path_(Buffer,DirBin,LinCFile[2],Length);

					if(Name)
					{
						penc_cl *Helper=PenC_CL_Create_(Queue,Name,(name_08**)Slot,Option,Count,&Error,Stream);

						if(Helper)
						{
							cl_uint Index=0;

							while(Index<Count)
							{
								Slot[Index]=_LinC_Create_KM_(Helper->SetKernel[Index],Link[Index]);
								if(Slot[Index])
									Index++;
								else
									break;
							}
							if(Index==Count)
							{
								for(Index=0;Index<Count;Index++)
									((DEVI_KM**)(Manager->KMSet))[Link[Index]]=Slot[Index];

								Acs_(penc_cl*,Manager->Helper)=Helper;
							}
							else
							{
								cl_int Down;

								for(Down=Index-1;Down>=0;Down--)
									Devi_KM_Delete_((devi_km**)(Slot+Down));
								PenC_CL_Delete_(&Helper);

								Error.E=CLBuildProgramFailure;
							}
						}
					}
					else
						Error.E=CLOutOfHostMemory;
				}
				else
					Error.E=CLOutOfHostMemory;

				MemC_Deloc_(Buffer);
			}
			else
				Error.E=CLInvalidValue;
		}
	else
		Error.E=CLInvalidHostPtr;

	return Error;
}
general LinC_CL_Delete_(linc_cl *_PL_ Manager)
{
	if(*Manager)
	{
		if((*Manager)->Helper)
		{
			devi_km **Ptr=(devi_km**)((*Manager)->KMSet+LinCKernels);

			for(Ptr--;Ptr>=(*Manager)->KMSet;Ptr--)
				Devi_KM_Delete_(Ptr);
			PenC_CL_Delete_((penc_cl**)&((*Manager)->Helper));
		}
		MemC_Deloc_(*Manager);
	}
}

static address _LinC_Worker_Local_(ADDRESS MaxWorker,ADDRESS MaxMemory,ADDRESS Length)
{
	address Workers=(MaxWorker<MaxMemory)?((MaxWorker<Length)?(MaxWorker):(Length)):((MaxMemory<Length)?(MaxMemory):(Length));

	Workers--;
	Workers|=(Workers>>1);
	Workers|=(Workers>>2);
	Workers|=(Workers>>4);
	Workers|=(Workers>>8);
	Workers|=(Workers>>16);
#ifdef MemC_64_
	Workers|=(Workers>>32);
#endif
	Workers++;

	return Workers;
}
static penc_eu _LinC_Worker_KM_GPPP_(PENC_CL _PL_ Helper,DEVI_KM _PL_ KM,ADDRESS _PL_ Token)
{
	penc_eu Error={.E=CLSuccess};

	Error.I|=Devi_KM_Save_(KM,0,Token[0]);
	Error.I|=Devi_KM_Save_(KM,1,Token[1]);
	Error.I|=Devi_KM_Save_(KM,2,Token[2]);
	Error.I|=Devi_KM_Save_(KM,3,Token[3]);
	if(Error.E==CLSuccess)
	{
		KM->WGroups[0]=Helper->Cores;
		KM->WLocals[0]=Helper->SizeWorker[0];
	}

	return Error;
}
static penc_eu _LinC_Worker_KM_GLGP_(PENC_CL _PL_ Helper,DEVI_KM _PL_ KM,ADDRESS _PL_ Token)
{
	ADDRESS NumL=(address)(*((data_32*)(Token[2])));
	ADDRESS LngL=(address)(*((data_32*)(Token[3])));
	ADDRESS Workers=_LinC_Worker_Local_(Helper->SizeWorker[0],((address)(Helper->SizeLocal))/(KM->ArgSize[1]),LngL);
	penc_eu Error={.E=CLSuccess};

	Error.I|=Devi_KM_Save_(KM,0,Token[0]);
	Error.I|=Devi_KM_Save_(KM,1,Workers);
	Error.I|=Devi_KM_Save_(KM,2,Token[1]);
	Error.I|=Devi_KM_Save_(KM,3,Token[3]);
	if(Error.E==CLSuccess)
	{
		KM->WGroups[0]=NumL;
		KM->WLocals[0]=Workers;
	}
	
	return Error;
}
static penc_eu _LinC_Worker_KM_GLGGP_(PENC_CL _PL_ Helper,DEVI_KM _PL_ KM,ADDRESS _PL_ Token)
{
	ADDRESS NumL=(address)(*((data_32*)(Token[3])));
	ADDRESS LngL=(address)(*((data_32*)(Token[4])));
	ADDRESS Workers=_LinC_Worker_Local_(Helper->SizeWorker[0],((address)(Helper->SizeLocal))/(KM->ArgSize[1]),LngL);
	penc_eu Error={.E=CLSuccess};
	
	Error.I|=Devi_KM_Save_(KM,0,Token[0]);
	Error.I|=Devi_KM_Save_(KM,1,Workers);
	Error.I|=Devi_KM_Save_(KM,2,Token[1]);
	Error.I|=Devi_KM_Save_(KM,3,Token[2]);
	Error.I|=Devi_KM_Save_(KM,4,Token[4]);
	if(Error.E==CLSuccess)
	{
		KM->WGroups[0]=NumL;
		KM->WLocals[0]=Workers;
	}

	return Error;
}
static penc_eu _LinC_Worker_KM_GGGPP_(PENC_CL _PL_ Helper,DEVI_KM _PL_ KM,ADDRESS _PL_ Token)
{
	penc_eu Error={.E=CLSuccess};

	Error.I|=Devi_KM_Save_(KM,0,Token[0]);
	Error.I|=Devi_KM_Save_(KM,1,Token[1]);
	Error.I|=Devi_KM_Save_(KM,2,Token[2]);
	Error.I|=Devi_KM_Save_(KM,3,Token[3]);
	Error.I|=Devi_KM_Save_(KM,4,Token[4]);
	if(Error.E==CLSuccess)
	{
		KM->WGroups[0]=Helper->Cores;
		KM->WLocals[0]=Helper->SizeWorker[0];
	}

	return Error;
}
static penc_eu _LinC_Worker_KM_(PENC_CL _PL_ Helper,DEVI_KM _PL_ KM,ADDRESS _PL_ Token,LINC_KI Switch)
{
	penc_eu Error;

	switch(Switch>>2)
	{
	case 0:case 1:case 2:case 3:
	case 4:case 5:case 6:case 7:
	case 8:case 9:case 10:case 11:case 12:case 13:case 14:case 15:case 16:
	case 17:case 18:case 19:case 20:case 21:
		Error=_LinC_Worker_KM_GPPP_(Helper,KM,Token);
		break;
	case 26:case 27:case 28:case 29:case 30:case 31:
		if(*((data_32*)(Token[3])))
		{
	case 22:case 23:
		Error=_LinC_Worker_KM_GLGP_(Helper,KM,Token);
		}
		else
			Error.E=CLInvalidArgValue;
		break;
	case 24:case 25:
		Error=_LinC_Worker_KM_GLGGP_(Helper,KM,Token);
		break;
	case 32:
		Error=_LinC_Worker_KM_GGGPP_(Helper,KM,Token);
		break;
	default:
		Error.E=CLInvalidValue;
	}

	return Error;
}
penc_eu LinC_CL_Action_(LINC_CL _PL_ Manager,MEMC_MS _PL_ Argument,LINC_KI Indicator)
{
	penc_eu Error;

	if(Manager)
		if(Argument)
			if(Manager->Helper)
				if(Indicator<0)
					Error.E=CLInvalidKernelName;
				else
					if(Indicator<LinCKernels)
						if(Manager->KMSet[Indicator])
							if((Argument->Nums)<((address)(Manager->KMSet[Indicator]->KArgs)))
								Error.E=CLInvalidKernelArgs;
							else
							{
								Error=_LinC_Worker_KM_(Manager->Helper,Manager->KMSet[Indicator],Argument->Slot.V,Indicator);
								if(Error.E==CLSuccess)
									Error.I=Devi_KM_Enqueue_(Manager->Helper->Queue,Manager->KMSet[Indicator]);
							}
						else
							Error.E=CLInvalidKernelName;
					else
						Error.E=CLInvalidKernelName;
			else
				Error.E=CLInvalidHostPtr;
		else
			Error.E=CLInvalidHostPtr;
	else
		Error.E=CLInvalidHostPtr;

	return Error;
}
#endif
#endif

#if(MemC_Fold_(Undefinition:LinCrux Macros))
#undef LinC_Min_
#undef LinC_Max_
#undef LinC_Mod_
#undef LinC_Inv_
#undef LinC_Div_
#undef LinC_Mul_
#undef LinC_Sub_
#undef LinC_Add_
#undef LinC_Amp_
#undef LinC_Inc_
#undef LinC_Geo_
#undef LinC_Ari_
#undef LinC_Oper_
#undef _LinC_Oper_
#undef LinC_Func_
#undef _LinC_Func_
#undef LinC_Type_
#undef _LinC_Type_
#undef LinC_TXX_
#undef _LinC_TXX_
#endif
