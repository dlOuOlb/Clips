#include "linclip.h"

#if(Fold_(Definition:Internal Macros))
#define _LINC_ static
#include "lincros.c"
#endif

#if(Fold_(Definition:Internal Constants))
static GENERAL _PL_ LinClip=&LinClip;
static BYTE_08 IdiomVersion[16]="Date:2019.04.26";
#endif

#if(Fold_(Domain:Host))

#if(Fold_(Part:Arithmetic and Geometric Progression Functions))
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

#if(Fold_(Part:Increment and Amplification Functions))
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

#if(Fold_(Part:Addition, Subtraction, and Multiplication Functions))
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

#if(Fold_(Part:Division Functions))
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

#if(Fold_(Part:Modulo Functions))
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

#if(Fold_(Part:Summation and Dot-Product Functions))
#define _LinC_Summation_
#define _LinC_Inte_
#define _LinC_Real_
#include "lincrux.c"
#undef _LinC_Real_
#undef _LinC_Inte_
#undef _LinC_Summation_
#endif

#if(Fold_(Part:Maximum and Minimum Functions))
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

#if(Fold_(Part:Mapping and Radix Sorting Functions))
static inline general _LinC_Swap_Address_(address _PL_ A,INTEGER T[2])
{
	ADDRESS Temp=A[T[1]];

	A[0]=A[T[0]];
	A[1]=Temp;
}

#define _LinC_Mapping_
#define _LinC_Data_
#include "lincrux.c"
#undef _LinC_Data_
#undef _LinC_Mapping_

_LINC_ general LinC_Order_D08_(data_08 _PL_ Line,address _PL_ Index,general _PL_ Buffer,ADDRESS Length,BOOLEAN Mode)
{
	if(Length)
	{
		address _PL_ IndexTemp=Buffer;
		data_08 _PL_ ValueTemp=(data_08*)(IndexTemp+Length);

		_LinC_Recur_D08_(Line,Index,ValueTemp,IndexTemp,Length,~BitC.Boolean[Mode&1],7);
	}
}
_LINC_ general LinC_Order_D16_(data_16 _PL_ Line,address _PL_ Index,general _PL_ Buffer,ADDRESS Length,BOOLEAN Mode)
{
	if(Length)
	{
		address _PL_ IndexTemp=Buffer;
		data_16 _PL_ ValueTemp=(data_16*)(IndexTemp+Length);

		_LinC_Recur_D16_(Line,Index,ValueTemp,IndexTemp,Length,~BitC.Boolean[Mode&1],15);
	}
}
_LINC_ general LinC_Order_D32_(data_32 _PL_ Line,address _PL_ Index,general _PL_ Buffer,ADDRESS Length,BOOLEAN Mode)
{
	if(Length)
	{
		address _PL_ IndexTemp=Buffer;
		data_32 _PL_ ValueTemp=(data_32*)(IndexTemp+Length);

		_LinC_Recur_D32_(Line,Index,ValueTemp,IndexTemp,Length,~BitC.Boolean[Mode&1],31);
	}
}
_LINC_ general LinC_Order_D64_(data_64 _PL_ Line,address _PL_ Index,general _PL_ Buffer,ADDRESS Length,BOOLEAN Mode)
{
	if(Length)
	{
		address _PL_ IndexTemp=Buffer;
		data_64 _PL_ ValueTemp=(data_64*)(IndexTemp+Length);

		_LinC_Recur_D64_(Line,Index,ValueTemp,IndexTemp,Length,~BitC.Boolean[Mode&1],63);
	}
}
_LINC_ general LinC_Order_I08_(inte_08 _PL_ Line,address _PL_ Index,general _PL_ Buffer,ADDRESS Length,BOOLEAN Mode)
{
	if(Length)
	{
		address _PL_ IndexTemp=Buffer;
		inte_08 _PL_ ValueTemp=(inte_08*)(IndexTemp+Length);
		ADDRESS Offset=(inte_08*)(_LinC_Radix_D08_((data_08*)ValueTemp,IndexTemp,(data_08*)Line,Index,Length,~BitC.Boolean[Mode&1],0x80))-ValueTemp;

		if(Offset)
			_LinC_Recur_D08_((data_08*)ValueTemp,IndexTemp,(data_08*)Line,Index,Offset,Mode,6);
		if(Offset<Length)
			_LinC_Recur_D08_((data_08*)(ValueTemp+Offset),IndexTemp+Offset,(data_08*)(Line+Offset),Index+Offset,Length-Offset,Mode,6);
	}
}
_LINC_ general LinC_Order_I16_(inte_16 _PL_ Line,address _PL_ Index,general _PL_ Buffer,ADDRESS Length,BOOLEAN Mode)
{
	if(Length)
	{
		address _PL_ IndexTemp=Buffer;
		inte_16 _PL_ ValueTemp=(inte_16*)(IndexTemp+Length);
		ADDRESS Offset=(inte_16*)(_LinC_Radix_D16_((data_16*)ValueTemp,IndexTemp,(data_16*)Line,Index,Length,~BitC.Boolean[Mode&1],0x8000))-ValueTemp;

		if(Offset)
			_LinC_Recur_D16_((data_16*)ValueTemp,IndexTemp,(data_16*)Line,Index,Offset,Mode,14);
		if(Offset<Length)
			_LinC_Recur_D16_((data_16*)(ValueTemp+Offset),IndexTemp+Offset,(data_16*)(Line+Offset),Index+Offset,Length-Offset,Mode,14);
	}
}
_LINC_ general LinC_Order_I32_(inte_32 _PL_ Line,address _PL_ Index,general _PL_ Buffer,ADDRESS Length,BOOLEAN Mode)
{
	if(Length)
	{
		address _PL_ IndexTemp=Buffer;
		inte_32 _PL_ ValueTemp=(inte_32*)(IndexTemp+Length);
		ADDRESS Offset=(inte_32*)(_LinC_Radix_D32_((data_32*)ValueTemp,IndexTemp,(data_32*)Line,Index,Length,~BitC.Boolean[Mode&1],0x80000000U))-ValueTemp;

		if(Offset)
			_LinC_Recur_D32_((data_32*)ValueTemp,IndexTemp,(data_32*)Line,Index,Offset,Mode,30);
		if(Offset<Length)
			_LinC_Recur_D32_((data_32*)(ValueTemp+Offset),IndexTemp+Offset,(data_32*)(Line+Offset),Index+Offset,Length-Offset,Mode,30);
	}
}
_LINC_ general LinC_Order_I64_(inte_64 _PL_ Line,address _PL_ Index,general _PL_ Buffer,ADDRESS Length,BOOLEAN Mode)
{
	if(Length)
	{
		address _PL_ IndexTemp=Buffer;
		inte_64 _PL_ ValueTemp=(inte_64*)(IndexTemp+Length);
		ADDRESS Offset=(inte_64*)(_LinC_Radix_D64_((data_64*)ValueTemp,IndexTemp,(data_64*)Line,Index,Length,~BitC.Boolean[Mode&1],0x8000000000000000UL))-ValueTemp;

		if(Offset)
			_LinC_Recur_D64_((data_64*)ValueTemp,IndexTemp,(data_64*)Line,Index,Offset,Mode,62);
		if(Offset<Length)
			_LinC_Recur_D64_((data_64*)(ValueTemp+Offset),IndexTemp+Offset,(data_64*)(Line+Offset),Index+Offset,Length-Offset,Mode,62);
	}
}
_LINC_ general LinC_Order_R32_(real_32 _PL_ Line,address _PL_ Index,general _PL_ Buffer,ADDRESS Length,BOOLEAN Mode)
{
	if(Length)
	{
		address _PL_ IndexTemp=Buffer;
		real_32 _PL_ ValueTemp=(real_32*)(IndexTemp+Length);
		ADDRESS Offset=(real_32*)(_LinC_Radix_D32_((data_32*)ValueTemp,IndexTemp,(data_32*)Line,Index,Length,~BitC.Boolean[Mode&1],0x80000000U))-ValueTemp;

		if(Offset)
			_LinC_Recur_D32_((data_32*)ValueTemp,IndexTemp,(data_32*)Line,Index,Offset,BitCFull,30);
		if(Offset<Length)
			_LinC_Recur_D32_((data_32*)(ValueTemp+Offset),IndexTemp+Offset,(data_32*)(Line+Offset),Index+Offset,Length-Offset,BitCNull,30);
	}
}
_LINC_ general LinC_Order_R64_(real_64 _PL_ Line,address _PL_ Index,general _PL_ Buffer,ADDRESS Length,BOOLEAN Mode)
{
	if(Length)
	{
		address _PL_ IndexTemp=Buffer;
		real_64 _PL_ ValueTemp=(real_64*)(IndexTemp+Length);
		ADDRESS Offset=(real_64*)(_LinC_Radix_D64_((data_64*)ValueTemp,IndexTemp,(data_64*)Line,Index,Length,~BitC.Boolean[Mode&1],0x8000000000000000UL))-ValueTemp;

		if(Offset)
			_LinC_Recur_D64_((data_64*)ValueTemp,IndexTemp,(data_64*)Line,Index,Offset,BitCFull,62);
		if(Offset<Length)
			_LinC_Recur_D64_((data_64*)(ValueTemp+Offset),IndexTemp+Offset,(data_64*)(Line+Offset),Index+Offset,Length-Offset,BitCNull,62);
	}
}
#endif

#endif

#if(Fold_(Domain:Device)&&defined(__OPENCL_H))

#if(Fold_(Part:Internal Constants))
#define _LinC_Meta_(Enum) {.Size=sizeof(LinCKernelName[Enum]),.Data=LinCKernelName[Enum]}

enum _linc_ki
{
	LinCInc1I08,LinCInc1I16,LinCInc1I32,LinCInc1I64,LinCInc1R08,LinCInc1R16,LinCInc1R32,LinCInc1R64,
	LinCAmp1I08,LinCAmp1I16,LinCAmp1I32,LinCAmp1I64,LinCAmp1R08,LinCAmp1R16,LinCAmp1R32,LinCAmp1R64,

	LinCAdd2I08,LinCAdd2I16,LinCAdd2I32,LinCAdd2I64,LinCAdd2R08,LinCAdd2R16,LinCAdd2R32,LinCAdd2R64,
	LinCSub2I08,LinCSub2I16,LinCSub2I32,LinCSub2I64,LinCSub2R08,LinCSub2R16,LinCSub2R32,LinCSub2R64,
	LinCMul2I08,LinCMul2I16,LinCMul2I32,LinCMul2I64,LinCMul2R08,LinCMul2R16,LinCMul2R32,LinCMul2R64,

	LinCDiv2D08,LinCDiv2D16,LinCDiv2D32,LinCDiv2D64,LinCDiv2I08,LinCDiv2I16,LinCDiv2I32,LinCDiv2I64,LinCDiv2R08,LinCDiv2R16,LinCDiv2R32,LinCDiv2R64,
	LinCDiv1D08,LinCDiv1D16,LinCDiv1D32,LinCDiv1D64,LinCDiv1I08,LinCDiv1I16,LinCDiv1I32,LinCDiv1I64,
	LinCInv1D08,LinCInv1D16,LinCInv1D32,LinCInv1D64,LinCInv1I08,LinCInv1I16,LinCInv1I32,LinCInv1I64,LinCInv1R08,LinCInv1R16,LinCInv1R32,LinCInv1R64,

	LinCMod1D08,LinCMod1D16,LinCMod1D32,LinCMod1D64,LinCMod1I08,LinCMod1I16,LinCMod1I32,LinCMod1I64,

	LinCSum1I08,LinCSum1I16,LinCSum1I32,LinCSum1I64,LinCSum1R08,LinCSum1R16,LinCSum1R32,LinCSum1R64,
	LinCDot2I08,LinCDot2I16,LinCDot2I32,LinCDot2I64,LinCDot2R08,LinCDot2R16,LinCDot2R32,LinCDot2R64,

	LinCMax1D08,LinCMax1D16,LinCMax1D32,LinCMax1D64,LinCMax1I08,LinCMax1I16,LinCMax1I32,LinCMax1I64,LinCMax1R08,LinCMax1R16,LinCMax1R32,LinCMax1R64,
	LinCMin1D08,LinCMin1D16,LinCMin1D32,LinCMin1D64,LinCMin1I08,LinCMin1I16,LinCMin1I32,LinCMin1I64,LinCMin1R08,LinCMin1R16,LinCMin1R32,LinCMin1R64,

	LinCMap1D08,LinCMap1D16,LinCMap1D32,LinCMap1D64,

	LinCXXXNT08,LinCXXXNT16,LinCXXXNT32,LinCXXXNT64,

	LinCKernelNums
};
MemC_Type_Declare_(enum,linc_ki,LINC_KI);

static BYTE_08 LinCKernelName[LinCKernelNums][16]=
{
	"LinC_Inc_1_I08_","LinC_Inc_1_I16_","LinC_Inc_1_I32_","LinC_Inc_1_I64_","LinC_Inc_1_R08_","LinC_Inc_1_R16_","LinC_Inc_1_R32_","LinC_Inc_1_R64_",
	"LinC_Amp_1_I08_","LinC_Amp_1_I16_","LinC_Amp_1_I32_","LinC_Amp_1_I64_","LinC_Amp_1_R08_","LinC_Amp_1_R16_","LinC_Amp_1_R32_","LinC_Amp_1_R64_",

	"LinC_Add_2_I08_","LinC_Add_2_I16_","LinC_Add_2_I32_","LinC_Add_2_I64_","LinC_Add_2_R08_","LinC_Add_2_R16_","LinC_Add_2_R32_","LinC_Add_2_R64_",
	"LinC_Sub_2_I08_","LinC_Sub_2_I16_","LinC_Sub_2_I32_","LinC_Sub_2_I64_","LinC_Sub_2_R08_","LinC_Sub_2_R16_","LinC_Sub_2_R32_","LinC_Sub_2_R64_",
	"LinC_Mul_2_I08_","LinC_Mul_2_I16_","LinC_Mul_2_I32_","LinC_Mul_2_I64_","LinC_Mul_2_R08_","LinC_Mul_2_R16_","LinC_Mul_2_R32_","LinC_Mul_2_R64_",

	"LinC_Div_2_D08_","LinC_Div_2_D16_","LinC_Div_2_D32_","LinC_Div_2_D64_","LinC_Div_2_I08_","LinC_Div_2_I16_","LinC_Div_2_I32_","LinC_Div_2_I64_","LinC_Div_2_R08_","LinC_Div_2_R16_","LinC_Div_2_R32_","LinC_Div_2_R64_",
	"LinC_Div_1_D08_","LinC_Div_1_D16_","LinC_Div_1_D32_","LinC_Div_1_D64_","LinC_Div_1_I08_","LinC_Div_1_I16_","LinC_Div_1_I32_","LinC_Div_1_I64_",
	"LinC_Inv_1_D08_","LinC_Inv_1_D16_","LinC_Inv_1_D32_","LinC_Inv_1_D64_","LinC_Inv_1_I08_","LinC_Inv_1_I16_","LinC_Inv_1_I32_","LinC_Inv_1_I64_","LinC_Inv_1_R08_","LinC_Inv_1_R16_","LinC_Inv_1_R32_","LinC_Inv_1_R64_",

	"LinC_Mod_1_D08_","LinC_Mod_1_D16_","LinC_Mod_1_D32_","LinC_Mod_1_D64_","LinC_Mod_1_I08_","LinC_Mod_1_I16_","LinC_Mod_1_I32_","LinC_Mod_1_I64_",

	"LinC_Sum_1_I08_","LinC_Sum_1_I16_","LinC_Sum_1_I32_","LinC_Sum_1_I64_","LinC_Sum_1_R08_","LinC_Sum_1_R16_","LinC_Sum_1_R32_","LinC_Sum_1_R64_",
	"LinC_Dot_2_I08_","LinC_Dot_2_I16_","LinC_Dot_2_I32_","LinC_Dot_2_I64_","LinC_Dot_2_R08_","LinC_Dot_2_R16_","LinC_Dot_2_R32_","LinC_Dot_2_R64_",

	"LinC_Max_1_D08_","LinC_Max_1_D16_","LinC_Max_1_D32_","LinC_Max_1_D64_","LinC_Max_1_I08_","LinC_Max_1_I16_","LinC_Max_1_I32_","LinC_Max_1_I64_","LinC_Max_1_R08_","LinC_Max_1_R16_","LinC_Max_1_R32_","LinC_Max_1_R64_",
	"LinC_Min_1_D08_","LinC_Min_1_D16_","LinC_Min_1_D32_","LinC_Min_1_D64_","LinC_Min_1_I08_","LinC_Min_1_I16_","LinC_Min_1_I32_","LinC_Min_1_I64_","LinC_Min_1_R08_","LinC_Min_1_R16_","LinC_Min_1_R32_","LinC_Min_1_R64_",

	"LinC_Map_1_D08_","LinC_Map_1_D16_","LinC_Map_1_D32_","LinC_Map_1_D64_",

	"LinC_XXX_N_T08_","LinC_XXX_N_T16_","LinC_XXX_N_T32_","LinC_XXX_N_T64_"
};
static OCLC_MD LinCKernelList[LinCKernelNums]=
{
	_LinC_Meta_(LinCInc1I08),_LinC_Meta_(LinCInc1I16),_LinC_Meta_(LinCInc1I32),_LinC_Meta_(LinCInc1I64),_LinC_Meta_(LinCInc1R08),_LinC_Meta_(LinCInc1R16),_LinC_Meta_(LinCInc1R32),_LinC_Meta_(LinCInc1R64),
	_LinC_Meta_(LinCAmp1I08),_LinC_Meta_(LinCAmp1I16),_LinC_Meta_(LinCAmp1I32),_LinC_Meta_(LinCAmp1I64),_LinC_Meta_(LinCAmp1R08),_LinC_Meta_(LinCAmp1R16),_LinC_Meta_(LinCAmp1R32),_LinC_Meta_(LinCAmp1R64),

	_LinC_Meta_(LinCAdd2I08),_LinC_Meta_(LinCAdd2I16),_LinC_Meta_(LinCAdd2I32),_LinC_Meta_(LinCAdd2I64),_LinC_Meta_(LinCAdd2R08),_LinC_Meta_(LinCAdd2R16),_LinC_Meta_(LinCAdd2R32),_LinC_Meta_(LinCAdd2R64),
	_LinC_Meta_(LinCSub2I08),_LinC_Meta_(LinCSub2I16),_LinC_Meta_(LinCSub2I32),_LinC_Meta_(LinCSub2I64),_LinC_Meta_(LinCSub2R08),_LinC_Meta_(LinCSub2R16),_LinC_Meta_(LinCSub2R32),_LinC_Meta_(LinCSub2R64),
	_LinC_Meta_(LinCMul2I08),_LinC_Meta_(LinCMul2I16),_LinC_Meta_(LinCMul2I32),_LinC_Meta_(LinCMul2I64),_LinC_Meta_(LinCMul2R08),_LinC_Meta_(LinCMul2R16),_LinC_Meta_(LinCMul2R32),_LinC_Meta_(LinCMul2R64),

	_LinC_Meta_(LinCDiv2D08),_LinC_Meta_(LinCDiv2D16),_LinC_Meta_(LinCDiv2D32),_LinC_Meta_(LinCDiv2D64),_LinC_Meta_(LinCDiv2I08),_LinC_Meta_(LinCDiv2I16),_LinC_Meta_(LinCDiv2I32),_LinC_Meta_(LinCDiv2I64),_LinC_Meta_(LinCDiv2R08),_LinC_Meta_(LinCDiv2R16),_LinC_Meta_(LinCDiv2R32),_LinC_Meta_(LinCDiv2R64),
	_LinC_Meta_(LinCDiv1D08),_LinC_Meta_(LinCDiv1D16),_LinC_Meta_(LinCDiv1D32),_LinC_Meta_(LinCDiv1D64),_LinC_Meta_(LinCDiv1I08),_LinC_Meta_(LinCDiv1I16),_LinC_Meta_(LinCDiv1I32),_LinC_Meta_(LinCDiv1I64),
	_LinC_Meta_(LinCInv1D08),_LinC_Meta_(LinCInv1D16),_LinC_Meta_(LinCInv1D32),_LinC_Meta_(LinCInv1D64),_LinC_Meta_(LinCInv1I08),_LinC_Meta_(LinCInv1I16),_LinC_Meta_(LinCInv1I32),_LinC_Meta_(LinCInv1I64),_LinC_Meta_(LinCInv1R08),_LinC_Meta_(LinCInv1R16),_LinC_Meta_(LinCInv1R32),_LinC_Meta_(LinCInv1R64),

	_LinC_Meta_(LinCMod1D08),_LinC_Meta_(LinCMod1D16),_LinC_Meta_(LinCMod1D32),_LinC_Meta_(LinCMod1D64),_LinC_Meta_(LinCMod1I08),_LinC_Meta_(LinCMod1I16),_LinC_Meta_(LinCMod1I32),_LinC_Meta_(LinCMod1I64),

	_LinC_Meta_(LinCSum1I08),_LinC_Meta_(LinCSum1I16),_LinC_Meta_(LinCSum1I32),_LinC_Meta_(LinCSum1I64),_LinC_Meta_(LinCSum1R08),_LinC_Meta_(LinCSum1R16),_LinC_Meta_(LinCSum1R32),_LinC_Meta_(LinCSum1R64),
	_LinC_Meta_(LinCDot2I08),_LinC_Meta_(LinCDot2I16),_LinC_Meta_(LinCDot2I32),_LinC_Meta_(LinCDot2I64),_LinC_Meta_(LinCDot2R08),_LinC_Meta_(LinCDot2R16),_LinC_Meta_(LinCDot2R32),_LinC_Meta_(LinCDot2R64),

	_LinC_Meta_(LinCMax1D08),_LinC_Meta_(LinCMax1D16),_LinC_Meta_(LinCMax1D32),_LinC_Meta_(LinCMax1D64),_LinC_Meta_(LinCMax1I08),_LinC_Meta_(LinCMax1I16),_LinC_Meta_(LinCMax1I32),_LinC_Meta_(LinCMax1I64),_LinC_Meta_(LinCMax1R08),_LinC_Meta_(LinCMax1R16),_LinC_Meta_(LinCMax1R32),_LinC_Meta_(LinCMax1R64),
	_LinC_Meta_(LinCMin1D08),_LinC_Meta_(LinCMin1D16),_LinC_Meta_(LinCMin1D32),_LinC_Meta_(LinCMin1D64),_LinC_Meta_(LinCMin1I08),_LinC_Meta_(LinCMin1I16),_LinC_Meta_(LinCMin1I32),_LinC_Meta_(LinCMin1I64),_LinC_Meta_(LinCMin1R08),_LinC_Meta_(LinCMin1R16),_LinC_Meta_(LinCMin1R32),_LinC_Meta_(LinCMin1R64),

	_LinC_Meta_(LinCMap1D08),_LinC_Meta_(LinCMap1D16),_LinC_Meta_(LinCMap1D32),_LinC_Meta_(LinCMap1D64),

	_LinC_Meta_(LinCXXXNT08),_LinC_Meta_(LinCXXXNT16),_LinC_Meta_(LinCXXXNT32),_LinC_Meta_(LinCXXXNT64)
};

#undef _LinC_Meta_
#endif

#if(Fold_(Part:Program Manager))
_LINC_ general LinC_CL_Build_T08_(oclc_co _PL_ Context,BYTE_08 _PL_ BuildOption,TEXT_08 _PL_ SourcePath,TEXT_08 _PL_ _PL_ BinaryPath,FILE _PL_ Stream,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
	{
		oclc_pm *PM=OCLC.PM.Create_(LinClip,LinCKernelList,LinCKernelNums);

		if(PM)
		{
			OCLC.PM.Build.Source.T08_(PM,Context,BuildOption,&SourcePath,1,Error);
			if(Error->E==CLSuccess)
			{
				OCLC.PM.Build.Log_(PM,Stream,Error);
				if(Error->E==CLSuccess)
					OCLC.PM.Build.Save.T08_(PM,BinaryPath,Error);
			}
			else
			{
				oclc_ef Local={0};

				OCLC.PM.Build.Log_(PM,Stream,&Local);
			}
			OCLC.PM.Delete_(&PM);
		}
		else
			Error->E=CLOutOfHostMemory;
	}
}
_LINC_ general LinC_CL_Build_T16_(oclc_co _PL_ Context,BYTE_08 _PL_ BuildOption,TEXT_16 _PL_ SourcePath,TEXT_16 _PL_ _PL_ BinaryPath,FILE _PL_ Stream,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
	{
		oclc_pm *PM=OCLC.PM.Create_(LinClip,LinCKernelList,LinCKernelNums);

		if(PM)
		{
			OCLC.PM.Build.Source.T16_(PM,Context,BuildOption,&SourcePath,1,Error);
			if(Error->E==CLSuccess)
			{
				OCLC.PM.Build.Log_(PM,Stream,Error);
				if(Error->E==CLSuccess)
					OCLC.PM.Build.Save.T16_(PM,BinaryPath,Error);
			}
			else
			{
				oclc_ef Local={0};

				OCLC.PM.Build.Log_(PM,Stream,&Local);
			}
			OCLC.PM.Delete_(&PM);
		}
		else
			Error->E=CLOutOfHostMemory;
	}
}

_LINC_ oclc_pm *LinC_CL_Create_T08_(oclc_co _PL_ Context,BYTE_08 _PL_ BuildOption,TEXT_08 _PL_ _PL_ BinaryPath,FILE _PL_ Stream,oclc_ef _PL_ Error)
{
	oclc_pm *PM;

	if(Error->E==CLSuccess)
	{
		PM=OCLC.PM.Create_(LinClip,LinCKernelList,LinCKernelNums);
		if(PM)
		{
			OCLC.PM.Build.Binary.T08_(PM,Context,BuildOption,BinaryPath,Error);
			if(Error->E==CLSuccess)
			{
				OCLC.PM.Build.Log_(PM,Stream,Error);
				if(Error->E!=CLSuccess)
					OCLC.PM.Delete_(&PM);
			}
			else
			{
				oclc_ef Local={0};

				OCLC.PM.Build.Log_(PM,Stream,&Local);
			}
		}
		else
			Error->E=CLOutOfHostMemory;
	}
	else
		PM=NULL;

	return PM;
}
_LINC_ oclc_pm *LinC_CL_Create_T16_(oclc_co _PL_ Context,BYTE_08 _PL_ BuildOption,TEXT_16 _PL_ _PL_ BinaryPath,FILE _PL_ Stream,oclc_ef _PL_ Error)
{
	oclc_pm *PM;

	if(Error->E==CLSuccess)
	{
		PM=OCLC.PM.Create_(LinClip,LinCKernelList,LinCKernelNums);
		if(PM)
		{
			OCLC.PM.Build.Binary.T16_(PM,Context,BuildOption,BinaryPath,Error);
			if(Error->E==CLSuccess)
			{
				OCLC.PM.Build.Log_(PM,Stream,Error);
				if(Error->E!=CLSuccess)
					OCLC.PM.Delete_(&PM);
			}
			else
			{
				oclc_ef Local={0};

				OCLC.PM.Build.Log_(PM,Stream,&Local);
			}
		}
		else
			Error->E=CLOutOfHostMemory;
	}
	else
		PM=NULL;

	return PM;
}
#endif

#if(Fold_(Part:Internal Functions))
static inline address _LinC_CL_Min_(ADDRESS A,ADDRESS B,ADDRESS C)
{
	return ((A<B)?((A<C)?(A):(C)):((B<C)?(B):(C)));
}
static cl_uint _LinC_CL_Address_Bits_(OCLC_DI _PL_ Device,oclc_ef _PL_ Error)
{
	cl_uint Bits;OCLC_Info_(DI,Device,&Bits,CL_DEVICE_ADDRESS_BITS,Error);

	return Bits;
}
static OCLC_DI *_LinC_CL_Device_(OCLC_QO _PL_ Queue,oclc_ef _PL_ Error)
{
	oclc_di *Device;OCLC_Info_(QO,Queue,&Device,CL_QUEUE_DEVICE,Error);

	return Device;
}
static address _LinC_CL_Work_Safe_(address Works)
{
	for(address Shift=sizeof(address)<<2;Shift;Shift>>=1)
		Works|=Works>>Shift;

	Works++;
	Works>>=1;

	return Works;
}
static address _LinC_CL_Work_Nums_(OCLC_DI _PL_ Device,ADDRESS Length,ADDRESS Unit,oclc_ef _PL_ Error)
{
	address MaxWorkGroupSize;OCLC_Info_(DI,Device,&MaxWorkGroupSize,CL_DEVICE_MAX_WORK_GROUP_SIZE,Error);
	cl_ulong LocalMemSize;OCLC_Info_(DI,Device,&LocalMemSize,CL_DEVICE_LOCAL_MEM_SIZE,Error);

	return _LinC_CL_Work_Safe_(_LinC_CL_Min_(Length,(address)MaxWorkGroupSize,((address)LocalMemSize)/Unit));
}
static inline OCLC_MP *_LinC_CL_Pin_Default_(OCLC_MP _PL_ Pin,OCLC_MP _PL_ Default)
{
	return ((Pin)?(Pin):(Default));
}
static general _LinC_CL_Set_1_(oclc_qo _PL_ Queue,oclc_ko _PL_ Kernel,OCLC_MH _PL_ ADesc,OCLC_MH _PL_ BDesc,OCLC_MP _PL_ Region,oclc_ef _PL_ Error)
{
	OCLC_MP _PL_ AOfs=_LinC_CL_Pin_Default_(ADesc->Start,OCLC.MP.Zero);
	OCLC_MP _PL_ BOfs=_LinC_CL_Pin_Default_(BDesc->Start,OCLC.MP.Zero);
	OCLC_MP _PL_ AShp=_LinC_CL_Pin_Default_(ADesc->Shape,Region);
	OCLC_MP _PL_ BShp=_LinC_CL_Pin_Default_(BDesc->Shape,Region);

	if(OCLC.MP.Offset.Invalid_(AOfs,AShp))
		Error->E=CLInvalidValue;
	else if(OCLC.MP.Offset.Invalid_(BOfs,BShp))
		Error->E=CLInvalidValue;
	else if(OCLC.MP.Length.Invalid_(AOfs,Region,AShp))
		Error->E=CLInvalidValue;
	else if(OCLC.MP.Length.Invalid_(BOfs,Region,BShp))
		Error->E=CLInvalidValue;
	else
	{
		ADDRESS Bits=(address)_LinC_CL_Address_Bits_(_LinC_CL_Device_(Queue,Error),Error);
		ADDRESS PinSize=Bits>>1;
		data_64 Buffer[OCLCPinAxes];

		OCLC.KO.Arg.G_(Kernel,0,ADesc->Memory,Error);
		OCLC.KO.Arg.G_(Kernel,1,BDesc->Memory,Error);
		OCLC.KO.Arg.P_(Kernel,2,BitC.CL.Pin_(AOfs,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,3,BitC.CL.Pin_(BOfs,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,4,BitC.CL.Pin_(Region,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,5,BitC.CL.Pin_(AShp,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,6,BitC.CL.Pin_(BShp,Buffer,Bits),PinSize,Error);
	}
}
static general _LinC_CL_Set_2_(oclc_qo _PL_ Queue,oclc_ko _PL_ Kernel,OCLC_MH _PL_ ADesc,OCLC_MH _PL_ BDesc,OCLC_MH _PL_ CDesc,OCLC_MP _PL_ Region,oclc_ef _PL_ Error)
{
	OCLC_MP _PL_ AOfs=_LinC_CL_Pin_Default_(ADesc->Start,OCLC.MP.Zero);
	OCLC_MP _PL_ BOfs=_LinC_CL_Pin_Default_(BDesc->Start,OCLC.MP.Zero);
	OCLC_MP _PL_ COfs=_LinC_CL_Pin_Default_(CDesc->Start,OCLC.MP.Zero);
	OCLC_MP _PL_ AShp=_LinC_CL_Pin_Default_(ADesc->Shape,Region);
	OCLC_MP _PL_ BShp=_LinC_CL_Pin_Default_(BDesc->Shape,Region);
	OCLC_MP _PL_ CShp=_LinC_CL_Pin_Default_(CDesc->Shape,Region);

	if(OCLC.MP.Offset.Invalid_(AOfs,AShp))
		Error->E=CLInvalidValue;
	else if(OCLC.MP.Offset.Invalid_(BOfs,BShp))
		Error->E=CLInvalidValue;
	else if(OCLC.MP.Offset.Invalid_(COfs,CShp))
		Error->E=CLInvalidValue;
	else if(OCLC.MP.Length.Invalid_(AOfs,Region,AShp))
		Error->E=CLInvalidValue;
	else if(OCLC.MP.Length.Invalid_(BOfs,Region,BShp))
		Error->E=CLInvalidValue;
	else if(OCLC.MP.Length.Invalid_(COfs,Region,CShp))
		Error->E=CLInvalidValue;
	else
	{
		ADDRESS Bits=(address)_LinC_CL_Address_Bits_(_LinC_CL_Device_(Queue,Error),Error);
		ADDRESS PinSize=Bits>>1;
		data_64 Buffer[OCLCPinAxes];

		OCLC.KO.Arg.G_(Kernel,0,ADesc->Memory,Error);
		OCLC.KO.Arg.G_(Kernel,1,BDesc->Memory,Error);
		OCLC.KO.Arg.G_(Kernel,2,CDesc->Memory,Error);
		OCLC.KO.Arg.P_(Kernel,3,BitC.CL.Pin_(AOfs,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,4,BitC.CL.Pin_(BOfs,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,5,BitC.CL.Pin_(COfs,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,6,BitC.CL.Pin_(Region,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,7,BitC.CL.Pin_(AShp,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,8,BitC.CL.Pin_(BShp,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,9,BitC.CL.Pin_(CShp,Buffer,Bits),PinSize,Error);
	}
}
static inline cl_int _LinC_CL_Enqueue_(oclc_qo _PL_ Queue,oclc_ko _PL_ Kernel,ADDRESS Total)
{
	return clEnqueueNDRangeKernel(Queue,Kernel,1,NULL,&Total,NULL,0,NULL,NULL);
}
static inline cl_int _LinC_CL_Enqueue_Local_(oclc_qo _PL_ Queue,oclc_ko _PL_ Kernel,ADDRESS Local,ADDRESS Total)
{
	return clEnqueueNDRangeKernel(Queue,Kernel,1,NULL,&Total,&Local,0,NULL,NULL);
}
#endif

#if(Fold_(Part:Increment and Amplification Functions))
_LINC_ general LinC_CL_Inc_1_(OCLC_PM _PL_ PM,oclc_qo _PL_ Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ Region,BITCLIP Value,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==LinClip)
				if(CDesc->Type==ADesc->Type)
				{
					BITC_TE Type=BitC.Type.Enum_(CDesc->Type);

					if(Type==BitCTypeUnknown)
						Error->E=CLInvalidValue;
					else
					{
						oclc_ko _PL_ Kernel=PM->Program.Kernel.List[LinCInc1I08+((Type<BitCTypeInte_08)?(Type):(Type-BitCTypeInte_08))].ID;

						_LinC_CL_Set_1_(Queue,Kernel,CDesc,ADesc,Region,Error);
						OCLC.KO.Arg.P_(Kernel,7,Value.C.G,CDesc->Type->SizeType,Error);
						if(Error->E==CLSuccess)
							Error->I=_LinC_CL_Enqueue_(Queue,Kernel,OCLC.MP.Total_(Region));
					}
				}
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
}
_LINC_ general LinC_CL_Amp_1_(OCLC_PM _PL_ PM,oclc_qo _PL_ Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ Region,BITCLIP Value,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==LinClip)
				if(CDesc->Type==ADesc->Type)
				{
					BITC_TE Type=BitC.Type.Enum_(CDesc->Type);
					
					if(Type==BitCTypeUnknown)
						Error->E=CLInvalidValue;
					else
					{
						oclc_ko _PL_ Kernel=PM->Program.Kernel.List[LinCAmp1I08+((Type<BitCTypeInte_08)?(Type):(Type-BitCTypeInte_08))].ID;

						_LinC_CL_Set_1_(Queue,Kernel,CDesc,ADesc,Region,Error);
						OCLC.KO.Arg.P_(Kernel,7,Value.C.G,CDesc->Type->SizeType,Error);
						if(Error->E==CLSuccess)
							Error->I=_LinC_CL_Enqueue_(Queue,Kernel,OCLC.MP.Total_(Region));
					}
				}
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
}
#endif

#if(Fold_(Part:Addition, Subtraction, and Multiplication Functions))
_LINC_ general LinC_CL_Add_2_(OCLC_PM _PL_ PM,oclc_qo _PL_ Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MH _PL_ BDesc,OCLC_MP _PL_ Region,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==LinClip)
				if(CDesc->Type==ADesc->Type)
					if(CDesc->Type==BDesc->Type)
					{
						BITC_TE Type=BitC.Type.Enum_(CDesc->Type);

						if(Type==BitCTypeUnknown)
							Error->E=CLInvalidValue;
						else
						{
							oclc_ko _PL_ Kernel=PM->Program.Kernel.List[LinCAdd2I08+((Type<BitCTypeInte_08)?(Type):(Type-BitCTypeInte_08))].ID;

							_LinC_CL_Set_2_(Queue,Kernel,CDesc,ADesc,BDesc,Region,Error);
							if(Error->E==CLSuccess)
								Error->I=_LinC_CL_Enqueue_(Queue,Kernel,OCLC.MP.Total_(Region));
						}
					}
					else
						Error->E=CLInvalidValue;
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
}
_LINC_ general LinC_CL_Sub_2_(OCLC_PM _PL_ PM,oclc_qo _PL_ Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MH _PL_ BDesc,OCLC_MP _PL_ Region,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==LinClip)
				if(CDesc->Type==ADesc->Type)
					if(CDesc->Type==BDesc->Type)
					{
						BITC_TE Type=BitC.Type.Enum_(CDesc->Type);

						if(Type==BitCTypeUnknown)
							Error->E=CLInvalidValue;
						else
						{
							oclc_ko _PL_ Kernel=PM->Program.Kernel.List[LinCSub2I08+((Type<BitCTypeInte_08)?(Type):(Type-BitCTypeInte_08))].ID;

							_LinC_CL_Set_2_(Queue,Kernel,CDesc,ADesc,BDesc,Region,Error);
							if(Error->E==CLSuccess)
								Error->I=_LinC_CL_Enqueue_(Queue,Kernel,OCLC.MP.Total_(Region));
						}
					}
					else
						Error->E=CLInvalidValue;
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
}
_LINC_ general LinC_CL_Mul_2_(OCLC_PM _PL_ PM,oclc_qo _PL_ Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MH _PL_ BDesc,OCLC_MP _PL_ Region,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==LinClip)
				if(CDesc->Type==ADesc->Type)
					if(CDesc->Type==BDesc->Type)
					{
						BITC_TE Type=BitC.Type.Enum_(CDesc->Type);

						if(Type==BitCTypeUnknown)
							Error->E=CLInvalidValue;
						else
						{
							oclc_ko _PL_ Kernel=PM->Program.Kernel.List[LinCMul2I08+((Type<BitCTypeInte_08)?(Type):(Type-BitCTypeInte_08))].ID;

							_LinC_CL_Set_2_(Queue,Kernel,CDesc,ADesc,BDesc,Region,Error);
							if(Error->E==CLSuccess)
								Error->I=_LinC_CL_Enqueue_(Queue,Kernel,OCLC.MP.Total_(Region));
						}
					}
					else
						Error->E=CLInvalidValue;
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
}
#endif

#if(Fold_(Part:Division Functions))
_LINC_ general LinC_CL_Div_2_(OCLC_PM _PL_ PM,oclc_qo _PL_ Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MH _PL_ BDesc,OCLC_MP _PL_ Region,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==LinClip)
				if(CDesc->Type==ADesc->Type)
					if(CDesc->Type==BDesc->Type)
					{
						BITC_TE Type=BitC.Type.Enum_(CDesc->Type);

						if(Type==BitCTypeUnknown)
							Error->E=CLInvalidValue;
						else
						{
							oclc_ko _PL_ Kernel=PM->Program.Kernel.List[LinCDiv2D08+Type].ID;

							_LinC_CL_Set_2_(Queue,Kernel,CDesc,ADesc,BDesc,Region,Error);
							if(Error->E==CLSuccess)
								Error->I=_LinC_CL_Enqueue_(Queue,Kernel,OCLC.MP.Total_(Region));
						}
					}
					else
						Error->E=CLInvalidValue;
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
}
_LINC_ general LinC_CL_Div_1_(OCLC_PM _PL_ PM,oclc_qo _PL_ Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ Region,BITCLIP Value,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==LinClip)
				if(CDesc->Type==ADesc->Type)
				{
					BITC_TE Type=BitC.Type.Enum_(CDesc->Type);

					if(Type<BitCTypeData_08)
						Error->E=CLInvalidValue;
					else if(Type>BitCTypeInte_64)
						Error->E=CLInvalidValue;
					else
					{
						oclc_ko _PL_ Kernel=PM->Program.Kernel.List[LinCDiv1D08+Type].ID;

						_LinC_CL_Set_1_(Queue,Kernel,CDesc,ADesc,Region,Error);
						OCLC.KO.Arg.P_(Kernel,7,Value.C.G,CDesc->Type->SizeType,Error);
						if(Error->E==CLSuccess)
							Error->I=_LinC_CL_Enqueue_(Queue,Kernel,OCLC.MP.Total_(Region));
					}
				}
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
}
_LINC_ general LinC_CL_Inv_1_(OCLC_PM _PL_ PM,oclc_qo _PL_ Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ Region,BITCLIP Value,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==LinClip)
				if(CDesc->Type==ADesc->Type)
				{
					BITC_TE Type=BitC.Type.Enum_(CDesc->Type);

					if(Type==BitCTypeUnknown)
						Error->E=CLInvalidValue;
					else
					{
						oclc_ko _PL_ Kernel=PM->Program.Kernel.List[LinCInv1D08+Type].ID;

						_LinC_CL_Set_1_(Queue,Kernel,CDesc,ADesc,Region,Error);
						OCLC.KO.Arg.P_(Kernel,7,Value.C.G,CDesc->Type->SizeType,Error);
						if(Error->E==CLSuccess)
							Error->I=_LinC_CL_Enqueue_(Queue,Kernel,OCLC.MP.Total_(Region));
					}
				}
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
}
#endif

#if(Fold_(Part:Modulo Functions))
_LINC_ general LinC_CL_Mod_1_(OCLC_PM _PL_ PM,oclc_qo _PL_ Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ Region,BITCLIP Value,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==LinClip)
				if(CDesc->Type==ADesc->Type)
				{
					BITC_TE Type=BitC.Type.Enum_(CDesc->Type);

					if(Type<BitCTypeData_08)
						Error->E=CLInvalidValue;
					else if(Type>BitCTypeInte_64)
						Error->E=CLInvalidValue;
					else
					{
						oclc_ko _PL_ Kernel=PM->Program.Kernel.List[LinCMod1D08+Type].ID;

						_LinC_CL_Set_1_(Queue,Kernel,CDesc,ADesc,Region,Error);
						OCLC.KO.Arg.P_(Kernel,7,Value.C.G,CDesc->Type->SizeType,Error);
						if(Error->E==CLSuccess)
							Error->I=_LinC_CL_Enqueue_(Queue,Kernel,OCLC.MP.Total_(Region));
					}
				}
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
}
#endif

#if(Fold_(Part:Summation and Dot-Product Functions))
static general _LinC_CL_Set_Enq_Sum_1_(oclc_qo _PL_ Queue,oclc_ko _PL_ Kernel,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ ARegion,OCLC_PA Axis,oclc_ef _PL_ Error)
{
	oclc_mp CRegion=*ARegion;CRegion.S[Axis]=1;
	OCLC_MP _PL_ COfs=_LinC_CL_Pin_Default_(CDesc->Start,OCLC.MP.Zero);
	OCLC_MP _PL_ AOfs=_LinC_CL_Pin_Default_(ADesc->Start,OCLC.MP.Zero);
	OCLC_MP _PL_ CShp=_LinC_CL_Pin_Default_(CDesc->Shape,&CRegion);
	OCLC_MP _PL_ AShp=_LinC_CL_Pin_Default_(ADesc->Shape,ARegion);

	if(OCLC.MP.Offset.Invalid_(COfs,CShp))
		Error->E=CLInvalidValue;
	else if(OCLC.MP.Offset.Invalid_(AOfs,AShp))
		Error->E=CLInvalidValue;
	else if(OCLC.MP.Length.Invalid_(COfs,&CRegion,CShp))
		Error->E=CLInvalidValue;
	else if(OCLC.MP.Length.Invalid_(AOfs,ARegion,AShp))
		Error->E=CLInvalidValue;
	else
	{
		OCLC_DI _PL_ Device=_LinC_CL_Device_(Queue,Error);
		ADDRESS Bits=_LinC_CL_Address_Bits_(Device,Error);
		ADDRESS PinSize=Bits>>1;
		ADDRESS Unit=CDesc->Type->SizeType;
		ADDRESS Length=ARegion->S[Axis];
		ADDRESS Work=_LinC_CL_Work_Nums_(Device,Length,Unit,Error);
		data_64 Buffer[OCLCPinAxes];

		OCLC.KO.Arg.G_(Kernel,0,CDesc->Memory,Error);
		OCLC.KO.Arg.G_(Kernel,1,ADesc->Memory,Error);
		OCLC.KO.Arg.P_(Kernel,2,BitC.CL.Pin_(COfs,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,3,BitC.CL.Pin_(AOfs,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,4,BitC.CL.Pin_(ARegion,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,5,BitC.CL.Pin_(CShp,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,6,BitC.CL.Pin_(AShp,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,7,&Axis,sizeof(oclc_pa),Error);
		OCLC.KO.Arg.L_(Kernel,8,Work*Unit,Error);
		if(Error->E==CLSuccess)
			Error->I=_LinC_CL_Enqueue_Local_(Queue,Kernel,Work,Work*(OCLC.MP.Total_(ARegion)/Length));
	}
}
_LINC_ general LinC_CL_Sum_1_(OCLC_PM _PL_ PM,oclc_qo _PL_ Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ Region,OCLC_PA Axis,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==LinClip)
				if(CDesc->Type==ADesc->Type)
					if(Axis<OCLCPinAxisN)
						Error->E=CLInvalidValue;
					else if(Axis>OCLCPinAxisX)
						Error->E=CLInvalidValue;
					else
					{
						BITC_TE Type=BitC.Type.Enum_(CDesc->Type);

						if(Type==BitCTypeUnknown)
							Error->E=CLInvalidValue;
						else
						{
							oclc_ko _PL_ Kernel=PM->Program.Kernel.List[LinCSum1I08+((Type<BitCTypeInte_08)?(Type):(Type-BitCTypeInte_08))].ID;

							_LinC_CL_Set_Enq_Sum_1_(Queue,Kernel,CDesc,ADesc,Region,Axis,Error);
						}
					}
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
}

static general _LinC_CL_Set_Enq_Dot_2_(oclc_qo _PL_ Queue,oclc_ko _PL_ Kernel,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MH _PL_ BDesc,OCLC_MP _PL_ ARegion,OCLC_PA Axis,oclc_ef _PL_ Error)
{
	oclc_mp CRegion=*ARegion;CRegion.S[Axis]=1;
	OCLC_MP _PL_ COfs=_LinC_CL_Pin_Default_(CDesc->Start,OCLC.MP.Zero);
	OCLC_MP _PL_ AOfs=_LinC_CL_Pin_Default_(ADesc->Start,OCLC.MP.Zero);
	OCLC_MP _PL_ BOfs=_LinC_CL_Pin_Default_(BDesc->Start,OCLC.MP.Zero);
	OCLC_MP _PL_ CShp=_LinC_CL_Pin_Default_(CDesc->Shape,&CRegion);
	OCLC_MP _PL_ AShp=_LinC_CL_Pin_Default_(ADesc->Shape,ARegion);
	OCLC_MP _PL_ BShp=_LinC_CL_Pin_Default_(BDesc->Shape,ARegion);

	if(OCLC.MP.Offset.Invalid_(COfs,CShp))
		Error->E=CLInvalidValue;
	else if(OCLC.MP.Offset.Invalid_(AOfs,AShp))
		Error->E=CLInvalidValue;
	else if(OCLC.MP.Offset.Invalid_(BOfs,BShp))
		Error->E=CLInvalidValue;
	else if(OCLC.MP.Length.Invalid_(COfs,&CRegion,CShp))
		Error->E=CLInvalidValue;
	else if(OCLC.MP.Length.Invalid_(AOfs,ARegion,AShp))
		Error->E=CLInvalidValue;
	else if(OCLC.MP.Length.Invalid_(BOfs,ARegion,BShp))
		Error->E=CLInvalidValue;
	else
	{
		OCLC_DI _PL_ Device=_LinC_CL_Device_(Queue,Error);
		ADDRESS Bits=_LinC_CL_Address_Bits_(Device,Error);
		ADDRESS PinSize=Bits>>1;
		ADDRESS Unit=CDesc->Type->SizeType;
		ADDRESS Length=ARegion->S[Axis];
		ADDRESS Work=_LinC_CL_Work_Nums_(Device,Length,Unit,Error);
		data_64 Buffer[OCLCPinAxes];

		OCLC.KO.Arg.G_(Kernel,0,CDesc->Memory,Error);
		OCLC.KO.Arg.G_(Kernel,1,ADesc->Memory,Error);
		OCLC.KO.Arg.G_(Kernel,2,BDesc->Memory,Error);
		OCLC.KO.Arg.P_(Kernel,3,BitC.CL.Pin_(COfs,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,4,BitC.CL.Pin_(AOfs,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,5,BitC.CL.Pin_(BOfs,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,6,BitC.CL.Pin_(ARegion,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,7,BitC.CL.Pin_(CShp,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,8,BitC.CL.Pin_(AShp,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,9,BitC.CL.Pin_(BShp,Buffer,Bits),PinSize,Error);
		OCLC.KO.Arg.P_(Kernel,10,&Axis,sizeof(oclc_pa),Error);
		OCLC.KO.Arg.L_(Kernel,11,Work*Unit,Error);
		if(Error->E==CLSuccess)
			Error->I=_LinC_CL_Enqueue_Local_(Queue,Kernel,Work,Work*(OCLC.MP.Total_(ARegion)/Length));
	}
}
_LINC_ general LinC_CL_Dot_2_(OCLC_PM _PL_ PM,oclc_qo _PL_ Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ ADesc,OCLC_MH _PL_ BDesc,OCLC_MP _PL_ Region,OCLC_PA Axis,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==LinClip)
				if(CDesc->Type==ADesc->Type)
					if(CDesc->Type==BDesc->Type)
						if(Axis<OCLCPinAxisN)
							Error->E=CLInvalidValue;
						else if(Axis>OCLCPinAxisX)
							Error->E=CLInvalidValue;
						else
						{
							BITC_TE Type=BitC.Type.Enum_(CDesc->Type);

							if(Type==BitCTypeUnknown)
								Error->E=CLInvalidValue;
							else
							{
								oclc_ko _PL_ Kernel=PM->Program.Kernel.List[LinCDot2I08+((Type<BitCTypeInte_08)?(Type):(Type-BitCTypeInte_08))].ID;

								_LinC_CL_Set_Enq_Dot_2_(Queue,Kernel,CDesc,ADesc,BDesc,Region,Axis,Error);
							}
						}
					else
						Error->E=CLInvalidValue;
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
}
#endif

#if(Fold_(Part:Maximum and Minimum Functions))
static general _LinC_CL_Set_Enq_M_M_1_(oclc_qo _PL_ Queue,oclc_ko _PL_ Kernel,OCLC_MH _PL_ IDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ ARegion,OCLC_PA Axis,oclc_ef _PL_ Error)
{
	OCLC_DI _PL_ Device=_LinC_CL_Device_(Queue,Error);
	ADDRESS Bits=_LinC_CL_Address_Bits_(Device,Error);

	if(Error->E==CLSuccess)
		if(Bits==(IDesc->Type->SizeType<<3))
		{
			oclc_mp IRegion=*ARegion;IRegion.S[Axis]=1;
			OCLC_MP _PL_ IOfs=_LinC_CL_Pin_Default_(IDesc->Start,OCLC.MP.Zero);
			OCLC_MP _PL_ AOfs=_LinC_CL_Pin_Default_(ADesc->Start,OCLC.MP.Zero);
			OCLC_MP _PL_ IShp=_LinC_CL_Pin_Default_(IDesc->Shape,&IRegion);
			OCLC_MP _PL_ AShp=_LinC_CL_Pin_Default_(ADesc->Shape,ARegion);

			if(OCLC.MP.Offset.Invalid_(IOfs,IShp))
				Error->E=CLInvalidValue;
			else if(OCLC.MP.Offset.Invalid_(AOfs,AShp))
				Error->E=CLInvalidValue;
			else if(OCLC.MP.Length.Invalid_(IOfs,&IRegion,IShp))
				Error->E=CLInvalidValue;
			else if(OCLC.MP.Length.Invalid_(AOfs,ARegion,AShp))
				Error->E=CLInvalidValue;
			else
			{
				ADDRESS PinSize=Bits>>1;
				ADDRESS Unit=(IDesc->Type->SizeType)+(ADesc->Type->SizeType);
				ADDRESS Length=ARegion->S[Axis];
				ADDRESS Work=_LinC_CL_Work_Nums_(Device,Length,Unit,Error);
				data_64 Buffer[OCLCPinAxes];

				OCLC.KO.Arg.G_(Kernel,0,IDesc->Memory,Error);
				OCLC.KO.Arg.G_(Kernel,1,ADesc->Memory,Error);
				OCLC.KO.Arg.P_(Kernel,2,BitC.CL.Pin_(IOfs,Buffer,Bits),PinSize,Error);
				OCLC.KO.Arg.P_(Kernel,3,BitC.CL.Pin_(AOfs,Buffer,Bits),PinSize,Error);
				OCLC.KO.Arg.P_(Kernel,4,BitC.CL.Pin_(ARegion,Buffer,Bits),PinSize,Error);
				OCLC.KO.Arg.P_(Kernel,5,BitC.CL.Pin_(IShp,Buffer,Bits),PinSize,Error);
				OCLC.KO.Arg.P_(Kernel,6,BitC.CL.Pin_(AShp,Buffer,Bits),PinSize,Error);
				OCLC.KO.Arg.P_(Kernel,7,&Axis,sizeof(oclc_pa),Error);
				OCLC.KO.Arg.L_(Kernel,8,Work*Unit,Error);
				if(Error->E==CLSuccess)
					Error->I=_LinC_CL_Enqueue_Local_(Queue,Kernel,Work,Work*(OCLC.MP.Total_(ARegion)/Length));
			}
		}
		else
			Error->E=CLInvalidValue;
}
_LINC_ general LinC_CL_Max_1_(OCLC_PM _PL_ PM,oclc_qo _PL_ Queue,OCLC_MH _PL_ IDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ Region,OCLC_PA Axis,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==LinClip)
				if(Axis<OCLCPinAxisN)
					Error->E=CLInvalidValue;
				else if(Axis>OCLCPinAxisX)
					Error->E=CLInvalidValue;
				else
				{
					BITC_TE Type=BitC.Type.Enum_(ADesc->Type);

					if(Type==BitCTypeUnknown)
						Error->E=CLInvalidValue;
					else
					{
						oclc_ko _PL_ Kernel=PM->Program.Kernel.List[LinCMax1D08+Type].ID;

						_LinC_CL_Set_Enq_M_M_1_(Queue,Kernel,IDesc,ADesc,Region,Axis,Error);
					}
				}
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
}
_LINC_ general LinC_CL_Min_1_(OCLC_PM _PL_ PM,oclc_qo _PL_ Queue,OCLC_MH _PL_ IDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ Region,OCLC_PA Axis,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==LinClip)
				if(Axis<OCLCPinAxisN)
					Error->E=CLInvalidValue;
				else if(Axis>OCLCPinAxisX)
					Error->E=CLInvalidValue;
				else
				{
					BITC_TE Type=BitC.Type.Enum_(ADesc->Type);

					if(Type==BitCTypeUnknown)
						Error->E=CLInvalidValue;
					else
					{
						oclc_ko _PL_ Kernel=PM->Program.Kernel.List[LinCMin1D08+Type].ID;

						_LinC_CL_Set_Enq_M_M_1_(Queue,Kernel,IDesc,ADesc,Region,Axis,Error);
					}
				}
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
}
#endif

#if(Fold_(Part:Mapping Functions))
static oclc_ko *_LinC_CL_Map_1_Kernel_(OCLC_PM _PL_ PM,ADDRESS TypeSize)
{
	oclc_ko *Kernel;

	switch(TypeSize)
	{
	case 1:
		Kernel=PM->Program.Kernel.List[LinCMap1D08].ID;
		break;
	case 2:
		Kernel=PM->Program.Kernel.List[LinCMap1D16].ID;
		break;
	case 4:
		Kernel=PM->Program.Kernel.List[LinCMap1D32].ID;
		break;
	case 8:
		Kernel=PM->Program.Kernel.List[LinCMap1D64].ID;
		break;
	default:
		Kernel=NULL;
	}

	return Kernel;
}
static general _LinC_CL_Set_Enq_Map_1_(oclc_qo _PL_ Queue,oclc_ko _PL_ Kernel,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ IDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ ARegion,OCLC_PA Axis,oclc_ef _PL_ Error)
{
	OCLC_DI _PL_ Device=_LinC_CL_Device_(Queue,Error);
	ADDRESS Bits=_LinC_CL_Address_Bits_(Device,Error);

	if(Error->E==CLSuccess)
		if(Bits==(IDesc->Type->SizeType<<3))
		{
			oclc_mp IRegion=*ARegion;IRegion.S[Axis]=1;
			OCLC_MP _PL_ COfs=_LinC_CL_Pin_Default_(CDesc->Start,OCLC.MP.Zero);
			OCLC_MP _PL_ IOfs=_LinC_CL_Pin_Default_(IDesc->Start,OCLC.MP.Zero);
			OCLC_MP _PL_ AOfs=_LinC_CL_Pin_Default_(ADesc->Start,OCLC.MP.Zero);
			OCLC_MP _PL_ CShp=_LinC_CL_Pin_Default_(CDesc->Shape,&IRegion);
			OCLC_MP _PL_ IShp=_LinC_CL_Pin_Default_(IDesc->Shape,&IRegion);
			OCLC_MP _PL_ AShp=_LinC_CL_Pin_Default_(ADesc->Shape,ARegion);

			if(OCLC.MP.Offset.Invalid_(COfs,CShp))
				Error->E=CLInvalidValue;
			else if(OCLC.MP.Offset.Invalid_(IOfs,IShp))
				Error->E=CLInvalidValue;
			else if(OCLC.MP.Offset.Invalid_(AOfs,AShp))
				Error->E=CLInvalidValue;
			else if(OCLC.MP.Length.Invalid_(COfs,&IRegion,CShp))
				Error->E=CLInvalidValue;
			else if(OCLC.MP.Length.Invalid_(IOfs,&IRegion,IShp))
				Error->E=CLInvalidValue;
			else if(OCLC.MP.Length.Invalid_(AOfs,ARegion,AShp))
				Error->E=CLInvalidValue;
			else
			{
				ADDRESS PinSize=Bits>>1;
				ADDRESS Length=ARegion->S[Axis];
				data_64 Buffer[OCLCPinAxes];

				OCLC.KO.Arg.G_(Kernel,0,CDesc->Memory,Error);
				OCLC.KO.Arg.G_(Kernel,1,IDesc->Memory,Error);
				OCLC.KO.Arg.G_(Kernel,2,ADesc->Memory,Error);
				OCLC.KO.Arg.P_(Kernel,3,BitC.CL.Pin_(COfs,Buffer,Bits),PinSize,Error);
				OCLC.KO.Arg.P_(Kernel,4,BitC.CL.Pin_(IOfs,Buffer,Bits),PinSize,Error);
				OCLC.KO.Arg.P_(Kernel,5,BitC.CL.Pin_(AOfs,Buffer,Bits),PinSize,Error);
				OCLC.KO.Arg.P_(Kernel,6,BitC.CL.Pin_(ARegion,Buffer,Bits),PinSize,Error);
				OCLC.KO.Arg.P_(Kernel,7,BitC.CL.Pin_(CShp,Buffer,Bits),PinSize,Error);
				OCLC.KO.Arg.P_(Kernel,8,BitC.CL.Pin_(IShp,Buffer,Bits),PinSize,Error);
				OCLC.KO.Arg.P_(Kernel,9,BitC.CL.Pin_(AShp,Buffer,Bits),PinSize,Error);
				OCLC.KO.Arg.P_(Kernel,10,&Axis,sizeof(oclc_pa),Error);
				if(Error->E==CLSuccess)
					Error->I=_LinC_CL_Enqueue_(Queue,Kernel,OCLC.MP.Total_(ARegion)/Length);
			}
		}
		else
			Error->E=CLInvalidValue;
}
_LINC_ general LinC_CL_Map_1_(OCLC_PM _PL_ PM,oclc_qo _PL_ Queue,OCLC_MH _PL_ CDesc,OCLC_MH _PL_ IDesc,OCLC_MH _PL_ ADesc,OCLC_MP _PL_ Region,OCLC_PA Axis,oclc_ef _PL_ Error)
{
	if(Error->E==CLSuccess)
		if(PM)
			if(PM->Origin==LinClip)
				if(CDesc->Type==ADesc->Type)
					if(Axis<OCLCPinAxisN)
						Error->E=CLInvalidValue;
					else if(Axis>OCLCPinAxisX)
						Error->E=CLInvalidValue;
					else
					{
						oclc_ko _PL_ Kernel=_LinC_CL_Map_1_Kernel_(PM,CDesc->Type->SizeType);

						_LinC_CL_Set_Enq_Map_1_(Queue,Kernel,CDesc,IDesc,ADesc,Region,Axis,Error);
					}
				else
					Error->E=CLInvalidValue;
			else
				Error->E=CLInvalidHostPtr;
		else
			Error->E=CLInvalidHostPtr;
}
#endif

#endif

#if(Fold_(Undefinition:Internal Macros))
#include "lincros.c"
#undef _LINC_
#endif

#if(Fold_(Library Casing))
const struct _lincase LinC=
{
	.Version=IdiomVersion,

#if(Fold_(Domain:Device)&&defined(__OPENCL_H))
	.CL.Ready.T08_=LinC_CL_Build_T08_,
	.CL.Ready.T16_=LinC_CL_Build_T16_,
	.CL.Create.T08_=LinC_CL_Create_T08_,
	.CL.Create.T16_=LinC_CL_Create_T16_,
	.CL.Inc_1_=MemC_Func_Casting_(general,LinC_CL_Inc_1_,OCLC_PM _PL_,oclc_qo _PL_,OCLC_MH _PL_,OCLC_MH _PL_,OCLC_MP _PL_,GENERAL _PL_,oclc_ef _PL_),
	.CL.Amp_1_=MemC_Func_Casting_(general,LinC_CL_Inc_1_,OCLC_PM _PL_,oclc_qo _PL_,OCLC_MH _PL_,OCLC_MH _PL_,OCLC_MP _PL_,GENERAL _PL_,oclc_ef _PL_),
	.CL.Add_2_=LinC_CL_Add_2_,
	.CL.Sub_2_=LinC_CL_Sub_2_,
	.CL.Mul_2_=LinC_CL_Mul_2_,
	.CL.Div_1_=MemC_Func_Casting_(general,LinC_CL_Div_1_,OCLC_PM _PL_,oclc_qo _PL_,OCLC_MH _PL_,OCLC_MH _PL_,OCLC_MP _PL_,GENERAL _PL_,oclc_ef _PL_),
	.CL.Inv_1_=MemC_Func_Casting_(general,LinC_CL_Inv_1_,OCLC_PM _PL_,oclc_qo _PL_,OCLC_MH _PL_,OCLC_MH _PL_,OCLC_MP _PL_,GENERAL _PL_,oclc_ef _PL_),
	.CL.Div_2_=LinC_CL_Div_2_,
	.CL.Mod_1_=MemC_Func_Casting_(general,LinC_CL_Mod_1_,OCLC_PM _PL_,oclc_qo _PL_,OCLC_MH _PL_,OCLC_MH _PL_,OCLC_MP _PL_,GENERAL _PL_,oclc_ef _PL_),
	.CL.Sum_1_=LinC_CL_Sum_1_,
	.CL.Dot_2_=LinC_CL_Dot_2_,
	.CL.Max_1_=LinC_CL_Max_1_,
	.CL.Min_1_=LinC_CL_Min_1_,
	.CL.Map_1_=LinC_CL_Map_1_,
#endif

#if(Fold_(Domain:Host))
#if(Fold_(Part:Arithmetic Progression))
	.Ari_0.I08_=LinC_Ari_0_I08_,
	.Ari_0.I16_=LinC_Ari_0_I16_,
	.Ari_0.I32_=LinC_Ari_0_I32_,
	.Ari_0.I64_=LinC_Ari_0_I64_,
	.Ari_0.D08_=MemC_Func_Casting_(general,LinC_Ari_0_I08_,data_08 *_R_,DATA_08,DATA_08,ADDRESS),
	.Ari_0.D16_=MemC_Func_Casting_(general,LinC_Ari_0_I16_,data_16 *_R_,DATA_16,DATA_16,ADDRESS),
	.Ari_0.D32_=MemC_Func_Casting_(general,LinC_Ari_0_I32_,data_32 *_R_,DATA_32,DATA_32,ADDRESS),
	.Ari_0.D64_=MemC_Func_Casting_(general,LinC_Ari_0_I64_,data_64 *_R_,DATA_64,DATA_64,ADDRESS),
	.Ari_0.R32_=LinC_Ari_0_R32_,
	.Ari_0.R64_=LinC_Ari_0_R64_,
#endif

#if(Fold_(Part:Geometric Progression))
	.Geo_0.I08_=LinC_Geo_0_I08_,
	.Geo_0.I16_=LinC_Geo_0_I16_,
	.Geo_0.I32_=LinC_Geo_0_I32_,
	.Geo_0.I64_=LinC_Geo_0_I64_,
	.Geo_0.D08_=MemC_Func_Casting_(general,LinC_Geo_0_I08_,data_08 *_R_,DATA_08,DATA_08,ADDRESS),
	.Geo_0.D16_=MemC_Func_Casting_(general,LinC_Geo_0_I16_,data_16 *_R_,DATA_16,DATA_16,ADDRESS),
	.Geo_0.D32_=MemC_Func_Casting_(general,LinC_Geo_0_I32_,data_32 *_R_,DATA_32,DATA_32,ADDRESS),
	.Geo_0.D64_=MemC_Func_Casting_(general,LinC_Geo_0_I64_,data_64 *_R_,DATA_64,DATA_64,ADDRESS),
	.Geo_0.R32_=LinC_Geo_0_R32_,
	.Geo_0.R64_=LinC_Geo_0_R64_,
#endif

#if(Fold_(Part:Increment))
	.Inc_1.I08_=LinC_Inc_1_I08_,
	.Inc_1.I16_=LinC_Inc_1_I16_,
	.Inc_1.I32_=LinC_Inc_1_I32_,
	.Inc_1.I64_=LinC_Inc_1_I64_,
	.Inc_1.D08_=MemC_Func_Casting_(general,LinC_Inc_1_I08_,data_08*,DATA_08*,DATA_08,ADDRESS),
	.Inc_1.D16_=MemC_Func_Casting_(general,LinC_Inc_1_I16_,data_16*,DATA_16*,DATA_16,ADDRESS),
	.Inc_1.D32_=MemC_Func_Casting_(general,LinC_Inc_1_I32_,data_32*,DATA_32*,DATA_32,ADDRESS),
	.Inc_1.D64_=MemC_Func_Casting_(general,LinC_Inc_1_I64_,data_64*,DATA_64*,DATA_64,ADDRESS),
	.Inc_1.R32_=LinC_Inc_1_R32_,
	.Inc_1.R64_=LinC_Inc_1_R64_,
#endif

#if(Fold_(Part:Amplification))
	.Amp_1.I08_=LinC_Amp_1_I08_,
	.Amp_1.I16_=LinC_Amp_1_I16_,
	.Amp_1.I32_=LinC_Amp_1_I32_,
	.Amp_1.I64_=LinC_Amp_1_I64_,
	.Amp_1.D08_=MemC_Func_Casting_(general,LinC_Amp_1_I08_,data_08*,DATA_08*,DATA_08,ADDRESS),
	.Amp_1.D16_=MemC_Func_Casting_(general,LinC_Amp_1_I16_,data_16*,DATA_16*,DATA_16,ADDRESS),
	.Amp_1.D32_=MemC_Func_Casting_(general,LinC_Amp_1_I32_,data_32*,DATA_32*,DATA_32,ADDRESS),
	.Amp_1.D64_=MemC_Func_Casting_(general,LinC_Amp_1_I64_,data_64*,DATA_64*,DATA_64,ADDRESS),
	.Amp_1.R32_=LinC_Amp_1_R32_,
	.Amp_1.R64_=LinC_Amp_1_R64_,
#endif

#if(Fold_(Part:Addition))
	.Add_2.I08_=LinC_Add_2_I08_,
	.Add_2.I16_=LinC_Add_2_I16_,
	.Add_2.I32_=LinC_Add_2_I32_,
	.Add_2.I64_=LinC_Add_2_I64_,
	.Add_2.D08_=MemC_Func_Casting_(general,LinC_Add_2_I08_,data_08*,DATA_08*,DATA_08*,ADDRESS),
	.Add_2.D16_=MemC_Func_Casting_(general,LinC_Add_2_I16_,data_16*,DATA_16*,DATA_16*,ADDRESS),
	.Add_2.D32_=MemC_Func_Casting_(general,LinC_Add_2_I32_,data_32*,DATA_32*,DATA_32*,ADDRESS),
	.Add_2.D64_=MemC_Func_Casting_(general,LinC_Add_2_I64_,data_64*,DATA_64*,DATA_64*,ADDRESS),
	.Add_2.R32_=LinC_Add_2_R32_,
	.Add_2.R64_=LinC_Add_2_R64_,
#endif

#if(Fold_(Part:Subtraction))
	.Sub_2.I08_=LinC_Sub_2_I08_,
	.Sub_2.I16_=LinC_Sub_2_I16_,
	.Sub_2.I32_=LinC_Sub_2_I32_,
	.Sub_2.I64_=LinC_Sub_2_I64_,
	.Sub_2.D08_=MemC_Func_Casting_(general,LinC_Sub_2_I08_,data_08*,DATA_08*,DATA_08*,ADDRESS),
	.Sub_2.D16_=MemC_Func_Casting_(general,LinC_Sub_2_I16_,data_16*,DATA_16*,DATA_16*,ADDRESS),
	.Sub_2.D32_=MemC_Func_Casting_(general,LinC_Sub_2_I32_,data_32*,DATA_32*,DATA_32*,ADDRESS),
	.Sub_2.D64_=MemC_Func_Casting_(general,LinC_Sub_2_I64_,data_64*,DATA_64*,DATA_64*,ADDRESS),
	.Sub_2.R32_=LinC_Sub_2_R32_,
	.Sub_2.R64_=LinC_Sub_2_R64_,
#endif

#if(Fold_(Part:Multiplication))
	.Mul_2.I08_=LinC_Mul_2_I08_,
	.Mul_2.I16_=LinC_Mul_2_I16_,
	.Mul_2.I32_=LinC_Mul_2_I32_,
	.Mul_2.I64_=LinC_Mul_2_I64_,
	.Mul_2.D08_=MemC_Func_Casting_(general,LinC_Mul_2_I08_,data_08*,DATA_08*,DATA_08*,ADDRESS),
	.Mul_2.D16_=MemC_Func_Casting_(general,LinC_Mul_2_I16_,data_16*,DATA_16*,DATA_16*,ADDRESS),
	.Mul_2.D32_=MemC_Func_Casting_(general,LinC_Mul_2_I32_,data_32*,DATA_32*,DATA_32*,ADDRESS),
	.Mul_2.D64_=MemC_Func_Casting_(general,LinC_Mul_2_I64_,data_64*,DATA_64*,DATA_64*,ADDRESS),
	.Mul_2.R32_=LinC_Mul_2_R32_,
	.Mul_2.R64_=LinC_Mul_2_R64_,
#endif

#if(Fold_(Part:Division))
	.Div_1.I08_=LinC_Div_1_I08_,
	.Div_1.I16_=LinC_Div_1_I16_,
	.Div_1.I32_=LinC_Div_1_I32_,
	.Div_1.I64_=LinC_Div_1_I64_,
	.Div_1.D08_=LinC_Div_1_D08_,
	.Div_1.D16_=LinC_Div_1_D16_,
	.Div_1.D32_=LinC_Div_1_D32_,
	.Div_1.D64_=LinC_Div_1_D64_,

	.Inv_1.I08_=LinC_Inv_1_I08_,
	.Inv_1.I16_=LinC_Inv_1_I16_,
	.Inv_1.I32_=LinC_Inv_1_I32_,
	.Inv_1.I64_=LinC_Inv_1_I64_,
	.Inv_1.D08_=LinC_Inv_1_D08_,
	.Inv_1.D16_=LinC_Inv_1_D16_,
	.Inv_1.D32_=LinC_Inv_1_D32_,
	.Inv_1.D64_=LinC_Inv_1_D64_,
	.Inv_1.R32_=LinC_Inv_1_R32_,
	.Inv_1.R64_=LinC_Inv_1_R64_,

	.Div_2.I08_=LinC_Div_2_I08_,
	.Div_2.I16_=LinC_Div_2_I16_,
	.Div_2.I32_=LinC_Div_2_I32_,
	.Div_2.I64_=LinC_Div_2_I64_,
	.Div_2.D08_=LinC_Div_2_D08_,
	.Div_2.D16_=LinC_Div_2_D16_,
	.Div_2.D32_=LinC_Div_2_D32_,
	.Div_2.D64_=LinC_Div_2_D64_,
	.Div_2.R32_=LinC_Div_2_R32_,
	.Div_2.R64_=LinC_Div_2_R64_,
#endif

#if(Fold_(Part:Modulo))
	.Mod_1.I08_=LinC_Mod_1_I08_,
	.Mod_1.I16_=LinC_Mod_1_I16_,
	.Mod_1.I32_=LinC_Mod_1_I32_,
	.Mod_1.I64_=LinC_Mod_1_I64_,
	.Mod_1.D08_=LinC_Mod_1_D08_,
	.Mod_1.D16_=LinC_Mod_1_D16_,
	.Mod_1.D32_=LinC_Mod_1_D32_,
	.Mod_1.D64_=LinC_Mod_1_D64_,
#endif

#if(Fold_(Part:Summation))
	.Sum_1.I08_=LinC_Sum_1_I08_,
	.Sum_1.I16_=LinC_Sum_1_I16_,
	.Sum_1.I32_=LinC_Sum_1_I32_,
	.Sum_1.I64_=LinC_Sum_1_I64_,
	.Sum_1.D08_=MemC_Func_Casting_(data_08,LinC_Sum_1_I08_,DATA_08 *_R_,ADDRESS),
	.Sum_1.D16_=MemC_Func_Casting_(data_16,LinC_Sum_1_I16_,DATA_16 *_R_,ADDRESS),
	.Sum_1.D32_=MemC_Func_Casting_(data_32,LinC_Sum_1_I32_,DATA_32 *_R_,ADDRESS),
	.Sum_1.D64_=MemC_Func_Casting_(data_64,LinC_Sum_1_I64_,DATA_64 *_R_,ADDRESS),
	.Sum_1.R32_=LinC_Sum_1_R32_,
	.Sum_1.R64_=LinC_Sum_1_R64_,
#endif

#if(Fold_(Part:Dot-Product))
	.Dot_2.I08_=LinC_Dot_2_I08_,
	.Dot_2.I16_=LinC_Dot_2_I16_,
	.Dot_2.I32_=LinC_Dot_2_I32_,
	.Dot_2.I64_=LinC_Dot_2_I64_,
	.Dot_2.D08_=MemC_Func_Casting_(data_08,LinC_Dot_2_I08_,DATA_08*,DATA_08*,ADDRESS),
	.Dot_2.D16_=MemC_Func_Casting_(data_16,LinC_Dot_2_I16_,DATA_16*,DATA_16*,ADDRESS),
	.Dot_2.D32_=MemC_Func_Casting_(data_32,LinC_Dot_2_I32_,DATA_32*,DATA_32*,ADDRESS),
	.Dot_2.D64_=MemC_Func_Casting_(data_64,LinC_Dot_2_I64_,DATA_64*,DATA_64*,ADDRESS),
	.Dot_2.R32_=LinC_Dot_2_R32_,
	.Dot_2.R64_=LinC_Dot_2_R64_,
#endif

#if(Fold_(Part:Maximum))
	.Max_1.I08_=LinC_Max_1_I08_,
	.Max_1.I16_=LinC_Max_1_I16_,
	.Max_1.I32_=LinC_Max_1_I32_,
	.Max_1.I64_=LinC_Max_1_I64_,
	.Max_1.D08_=LinC_Max_1_D08_,
	.Max_1.D16_=LinC_Max_1_D16_,
	.Max_1.D32_=LinC_Max_1_D32_,
	.Max_1.D64_=LinC_Max_1_D64_,
	.Max_1.R32_=LinC_Max_1_R32_,
	.Max_1.R64_=LinC_Max_1_R64_,
#endif

#if(Fold_(Part:Minimum))
	.Min_1.I08_=LinC_Min_1_I08_,
	.Min_1.I16_=LinC_Min_1_I16_,
	.Min_1.I32_=LinC_Min_1_I32_,
	.Min_1.I64_=LinC_Min_1_I64_,
	.Min_1.D08_=LinC_Min_1_D08_,
	.Min_1.D16_=LinC_Min_1_D16_,
	.Min_1.D32_=LinC_Min_1_D32_,
	.Min_1.D64_=LinC_Min_1_D64_,
	.Min_1.R32_=LinC_Min_1_R32_,
	.Min_1.R64_=LinC_Min_1_R64_,
#endif

#if(Fold_(Part:Radix Sorting))
	.Order.I08_=LinC_Order_I08_,
	.Order.I16_=LinC_Order_I16_,
	.Order.I32_=LinC_Order_I32_,
	.Order.I64_=LinC_Order_I64_,
	.Order.D08_=LinC_Order_D08_,
	.Order.D16_=LinC_Order_D16_,
	.Order.D32_=LinC_Order_D32_,
	.Order.D64_=LinC_Order_D64_,
	.Order.R32_=LinC_Order_R32_,
	.Order.R64_=LinC_Order_R64_,
#endif

#if(Fold_(Part:Mapping))
	.Map_1.I08_=MemC_Func_Casting_(general,LinC_Map_1_D08_,inte_08 *_R_,ADDRESS *_R_,INTE_08 _PL_,ADDRESS),
	.Map_1.I16_=MemC_Func_Casting_(general,LinC_Map_1_D16_,inte_16 *_R_,ADDRESS *_R_,INTE_16 _PL_,ADDRESS),
	.Map_1.I32_=MemC_Func_Casting_(general,LinC_Map_1_D32_,inte_32 *_R_,ADDRESS *_R_,INTE_32 _PL_,ADDRESS),
	.Map_1.I64_=MemC_Func_Casting_(general,LinC_Map_1_D64_,inte_64 *_R_,ADDRESS *_R_,INTE_64 _PL_,ADDRESS),
	.Map_1.D08_=LinC_Map_1_D08_,
	.Map_1.D16_=LinC_Map_1_D16_,
	.Map_1.D32_=LinC_Map_1_D32_,
	.Map_1.D64_=LinC_Map_1_D64_,
	.Map_1.R32_=MemC_Func_Casting_(general,LinC_Map_1_D32_,real_32 *_R_,ADDRESS *_R_,REAL_32 _PL_,ADDRESS),
	.Map_1.R64_=MemC_Func_Casting_(general,LinC_Map_1_D64_,real_64 *_R_,ADDRESS *_R_,REAL_64 _PL_,ADDRESS)
#endif
#endif
};
#endif
