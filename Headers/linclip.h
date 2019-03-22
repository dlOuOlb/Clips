/*------------------------------------------------------------------*/
/*	LinClip provides some elementary arithmetic operations.			*/
/*																	*/
/*	Written by Ranny Clover								Date		*/
/*	http://github.com/dlOuOlb/Clips/					2019.03.22	*/
/*------------------------------------------------------------------*/
/*	OpenCL Support													*/
/*	http://www.khronos.org/opencl/									*/
/*------------------------------------------------------------------*/

#ifndef _INC_LINCLIP
#define _INC_LINCLIP	//LinClip : Header Declaration

#ifdef _CL
#include <CL\opencl.h>
#endif
#include <bitclip.h>

#if(MemC_Fold_(Definition:Types))
#ifdef __OPENCL_H
enum _linc_ki			//LinC_CL : LinCKernel Indicator Enumeration
{
	LinCAri0I08=0,		//LinC_CL : LinC_Ari_0_I08_(_G_ inte_08 _PL_ Line,_P_ INTE_08 VStart,_P_ INTE_08 VStep,_P_ DATA_32 Length)
	LinCAri0I16=1,		//LinC_CL : LinC_Ari_0_I16_(_G_ inte_16 _PL_ Line,_P_ INTE_16 VStart,_P_ INTE_16 VStep,_P_ DATA_32 Length)
	LinCAri0I32=2,		//LinC_CL : LinC_Ari_0_I32_(_G_ inte_32 _PL_ Line,_P_ INTE_32 VStart,_P_ INTE_32 VStep,_P_ DATA_32 Length)
	LinCAri0I64=3,		//LinC_CL : LinC_Ari_0_I64_(_G_ inte_64 _PL_ Line,_P_ INTE_64 VStart,_P_ INTE_64 VStep,_P_ DATA_32 Length)
	LinCAri0R16=5,		//LinC_CL : LinC_Ari_0_R16_(_G_ real_16 _PL_ Line,_P_ INTE_16 VStart,_P_ INTE_16 VStep,_P_ DATA_32 Length)
	LinCAri0R32=6,		//LinC_CL : LinC_Ari_0_R32_(_G_ real_32 _PL_ Line,_P_ REAL_32 VStart,_P_ REAL_32 VStep,_P_ DATA_32 Length)
	LinCAri0R64=7,		//LinC_CL : LinC_Ari_0_R64_(_G_ real_64 _PL_ Line,_P_ REAL_64 VStart,_P_ REAL_64 VStep,_P_ DATA_32 Length)
	LinCGeo0I08=8,		//LinC_CL : LinC_Geo_0_I08_(_G_ inte_08 _PL_ Line,_P_ INTE_08 VStart,_P_ INTE_08 VStep,_P_ DATA_32 Length)
	LinCGeo0I16=9,		//LinC_CL : LinC_Geo_0_I16_(_G_ inte_16 _PL_ Line,_P_ INTE_16 VStart,_P_ INTE_16 VStep,_P_ DATA_32 Length)
	LinCGeo0I32=10,		//LinC_CL : LinC_Geo_0_I32_(_G_ inte_32 _PL_ Line,_P_ INTE_32 VStart,_P_ INTE_32 VStep,_P_ DATA_32 Length)
	LinCGeo0I64=11,		//LinC_CL : LinC_Geo_0_I64_(_G_ inte_64 _PL_ Line,_P_ INTE_64 VStart,_P_ INTE_64 VStep,_P_ DATA_32 Length)
	LinCGeo0R16=13,		//LinC_CL : LinC_Geo_0_R16_(_G_ real_16 _PL_ Line,_P_ INTE_16 VStart,_P_ INTE_16 VStep,_P_ DATA_32 Length)
	LinCGeo0R32=14,		//LinC_CL : LinC_Geo_0_R32_(_G_ real_32 _PL_ Line,_P_ REAL_32 VStart,_P_ REAL_32 VStep,_P_ DATA_32 Length)
	LinCGeo0R64=15,		//LinC_CL : LinC_Geo_0_R64_(_G_ real_64 _PL_ Line,_P_ REAL_64 VStart,_P_ REAL_64 VStep,_P_ DATA_32 Length)
	LinCInc1I08=16,		//LinC_CL : LinC_Inc_1_I08_(_G_ inte_08 _PL_ LineC,_G_ INTE_08 _PL_ LineA,_P_ INTE_08 Value,_P_ DATA_32 Length)
	LinCInc1I16=17,		//LinC_CL : LinC_Inc_1_I16_(_G_ inte_16 _PL_ LineC,_G_ INTE_16 _PL_ LineA,_P_ INTE_16 Value,_P_ DATA_32 Length)
	LinCInc1I32=18,		//LinC_CL : LinC_Inc_1_I32_(_G_ inte_32 _PL_ LineC,_G_ INTE_32 _PL_ LineA,_P_ INTE_32 Value,_P_ DATA_32 Length)
	LinCInc1I64=19,		//LinC_CL : LinC_Inc_1_I64_(_G_ inte_64 _PL_ LineC,_G_ INTE_64 _PL_ LineA,_P_ INTE_64 Value,_P_ DATA_32 Length)
	LinCInc1R16=21,		//LinC_CL : LinC_Inc_1_R16_(_G_ real_16 _PL_ LineC,_G_ REAL_16 _PL_ LineA,_P_ INTE_16 Value,_P_ DATA_32 Length)
	LinCInc1R32=22,		//LinC_CL : LinC_Inc_1_R32_(_G_ real_32 _PL_ LineC,_G_ REAL_32 _PL_ LineA,_P_ REAL_32 Value,_P_ DATA_32 Length)
	LinCInc1R64=23,		//LinC_CL : LinC_Inc_1_R64_(_G_ real_64 _PL_ LineC,_G_ REAL_64 _PL_ LineA,_P_ REAL_64 Value,_P_ DATA_32 Length)
	LinCAmp1I08=24,		//LinC_CL : LinC_Amp_1_I08_(_G_ inte_08 _PL_ LineC,_G_ INTE_08 _PL_ LineA,_P_ INTE_08 Value,_P_ DATA_32 Length)
	LinCAmp1I16=25,		//LinC_CL : LinC_Amp_1_I16_(_G_ inte_16 _PL_ LineC,_G_ INTE_16 _PL_ LineA,_P_ INTE_16 Value,_P_ DATA_32 Length)
	LinCAmp1I32=26,		//LinC_CL : LinC_Amp_1_I32_(_G_ inte_32 _PL_ LineC,_G_ INTE_32 _PL_ LineA,_P_ INTE_32 Value,_P_ DATA_32 Length)
	LinCAmp1I64=27,		//LinC_CL : LinC_Amp_1_I64_(_G_ inte_64 _PL_ LineC,_G_ INTE_64 _PL_ LineA,_P_ INTE_64 Value,_P_ DATA_32 Length)
	LinCAmp1R16=29,		//LinC_CL : LinC_Amp_1_R16_(_G_ real_16 _PL_ LineC,_G_ REAL_16 _PL_ LineA,_P_ INTE_16 Value,_P_ DATA_32 Length)
	LinCAmp1R32=30,		//LinC_CL : LinC_Amp_1_R32_(_G_ real_32 _PL_ LineC,_G_ REAL_32 _PL_ LineA,_P_ REAL_32 Value,_P_ DATA_32 Length)
	LinCAmp1R64=31,		//LinC_CL : LinC_Amp_1_R64_(_G_ real_64 _PL_ LineC,_G_ REAL_64 _PL_ LineA,_P_ REAL_64 Value,_P_ DATA_32 Length)
	LinCAdd2I08=32,		//LinC_CL : LinC_Add_2_I08_(_G_ inte_08 _PL_ LineC,_G_ INTE_08 _PL_ LineA,_G_ INTE_08 _PL_ LineB,_P_ DATA_32 Length)
	LinCAdd2I16=33,		//LinC_CL : LinC_Add_2_I16_(_G_ inte_16 _PL_ LineC,_G_ INTE_16 _PL_ LineA,_G_ INTE_16 _PL_ LineB,_P_ DATA_32 Length)
	LinCAdd2I32=34,		//LinC_CL : LinC_Add_2_I32_(_G_ inte_32 _PL_ LineC,_G_ INTE_32 _PL_ LineA,_G_ INTE_32 _PL_ LineB,_P_ DATA_32 Length)
	LinCAdd2I64=35,		//LinC_CL : LinC_Add_2_I64_(_G_ inte_64 _PL_ LineC,_G_ INTE_64 _PL_ LineA,_G_ INTE_64 _PL_ LineB,_P_ DATA_32 Length)
	LinCAdd2R16=37,		//LinC_CL : LinC_Add_2_R16_(_G_ real_16 _PL_ LineC,_G_ REAL_16 _PL_ LineA,_G_ REAL_16 _PL_ LineB,_P_ DATA_32 Length)
	LinCAdd2R32=38,		//LinC_CL : LinC_Add_2_R32_(_G_ real_32 _PL_ LineC,_G_ REAL_32 _PL_ LineA,_G_ REAL_32 _PL_ LineB,_P_ DATA_32 Length)
	LinCAdd2R64=39,		//LinC_CL : LinC_Add_2_R64_(_G_ real_64 _PL_ LineC,_G_ REAL_64 _PL_ LineA,_G_ REAL_64 _PL_ LineB,_P_ DATA_32 Length)
	LinCSub2I08=40,		//LinC_CL : LinC_Sub_2_I08_(_G_ inte_08 _PL_ LineC,_G_ INTE_08 _PL_ LineA,_G_ INTE_08 _PL_ LineB,_P_ DATA_32 Length)
	LinCSub2I16=41,		//LinC_CL : LinC_Sub_2_I16_(_G_ inte_16 _PL_ LineC,_G_ INTE_16 _PL_ LineA,_G_ INTE_16 _PL_ LineB,_P_ DATA_32 Length)
	LinCSub2I32=42,		//LinC_CL : LinC_Sub_2_I32_(_G_ inte_32 _PL_ LineC,_G_ INTE_32 _PL_ LineA,_G_ INTE_32 _PL_ LineB,_P_ DATA_32 Length)
	LinCSub2I64=43,		//LinC_CL : LinC_Sub_2_I64_(_G_ inte_64 _PL_ LineC,_G_ INTE_64 _PL_ LineA,_G_ INTE_64 _PL_ LineB,_P_ DATA_32 Length)
	LinCSub2R16=45,		//LinC_CL : LinC_Sub_2_R16_(_G_ real_16 _PL_ LineC,_G_ REAL_16 _PL_ LineA,_G_ REAL_16 _PL_ LineB,_P_ DATA_32 Length)
	LinCSub2R32=46,		//LinC_CL : LinC_Sub_2_R32_(_G_ real_32 _PL_ LineC,_G_ REAL_32 _PL_ LineA,_G_ REAL_32 _PL_ LineB,_P_ DATA_32 Length)
	LinCSub2R64=47,		//LinC_CL : LinC_Sub_2_R64_(_G_ real_64 _PL_ LineC,_G_ REAL_64 _PL_ LineA,_G_ REAL_64 _PL_ LineB,_P_ DATA_32 Length)
	LinCMul2I08=48,		//LinC_CL : LinC_Mul_2_I08_(_G_ inte_08 _PL_ LineC,_G_ INTE_08 _PL_ LineA,_G_ INTE_08 _PL_ LineB,_P_ DATA_32 Length)
	LinCMul2I16=49,		//LinC_CL : LinC_Mul_2_I16_(_G_ inte_16 _PL_ LineC,_G_ INTE_16 _PL_ LineA,_G_ INTE_16 _PL_ LineB,_P_ DATA_32 Length)
	LinCMul2I32=50,		//LinC_CL : LinC_Mul_2_I32_(_G_ inte_32 _PL_ LineC,_G_ INTE_32 _PL_ LineA,_G_ INTE_32 _PL_ LineB,_P_ DATA_32 Length)
	LinCMul2I64=51,		//LinC_CL : LinC_Mul_2_I64_(_G_ inte_64 _PL_ LineC,_G_ INTE_64 _PL_ LineA,_G_ INTE_64 _PL_ LineB,_P_ DATA_32 Length)
	LinCMul2R16=53,		//LinC_CL : LinC_Mul_2_R16_(_G_ real_16 _PL_ LineC,_G_ REAL_16 _PL_ LineA,_G_ REAL_16 _PL_ LineB,_P_ DATA_32 Length)
	LinCMul2R32=54,		//LinC_CL : LinC_Mul_2_R32_(_G_ real_32 _PL_ LineC,_G_ REAL_32 _PL_ LineA,_G_ REAL_32 _PL_ LineB,_P_ DATA_32 Length)
	LinCMul2R64=55,		//LinC_CL : LinC_Mul_2_R64_(_G_ real_64 _PL_ LineC,_G_ REAL_64 _PL_ LineA,_G_ REAL_64 _PL_ LineB,_P_ DATA_32 Length)
	LinCDiv2I08=56,		//LinC_CL : LinC_Div_2_I08_(_G_ inte_08 _PL_ LineC,_G_ INTE_08 _PL_ LineA,_G_ INTE_08 _PL_ LineB,_P_ DATA_32 Length)
	LinCDiv2I16=57,		//LinC_CL : LinC_Div_2_I16_(_G_ inte_16 _PL_ LineC,_G_ INTE_16 _PL_ LineA,_G_ INTE_16 _PL_ LineB,_P_ DATA_32 Length)
	LinCDiv2I32=58,		//LinC_CL : LinC_Div_2_I32_(_G_ inte_32 _PL_ LineC,_G_ INTE_32 _PL_ LineA,_G_ INTE_32 _PL_ LineB,_P_ DATA_32 Length)
	LinCDiv2I64=59,		//LinC_CL : LinC_Div_2_I64_(_G_ inte_64 _PL_ LineC,_G_ INTE_64 _PL_ LineA,_G_ INTE_64 _PL_ LineB,_P_ DATA_32 Length)
	LinCDiv2D08=60,		//LinC_CL : LinC_Div_2_D08_(_G_ data_08 _PL_ LineC,_G_ DATA_08 _PL_ LineA,_G_ DATA_08 _PL_ LineB,_P_ DATA_32 Length)
	LinCDiv2D16=61,		//LinC_CL : LinC_Div_2_D16_(_G_ data_16 _PL_ LineC,_G_ DATA_16 _PL_ LineA,_G_ DATA_16 _PL_ LineB,_P_ DATA_32 Length)
	LinCDiv2D32=62,		//LinC_CL : LinC_Div_2_D32_(_G_ data_32 _PL_ LineC,_G_ DATA_32 _PL_ LineA,_G_ DATA_32 _PL_ LineB,_P_ DATA_32 Length)
	LinCDiv2D64=63,		//LinC_CL : LinC_Div_2_D64_(_G_ data_64 _PL_ LineC,_G_ DATA_64 _PL_ LineA,_G_ DATA_64 _PL_ LineB,_P_ DATA_32 Length)
	LinCDiv2R16=65,		//LinC_CL : LinC_Div_2_R16_(_G_ real_16 _PL_ LineC,_G_ REAL_16 _PL_ LineA,_G_ REAL_16 _PL_ LineB,_P_ DATA_32 Length)
	LinCDiv2R32=66,		//LinC_CL : LinC_Div_2_R32_(_G_ real_32 _PL_ LineC,_G_ REAL_32 _PL_ LineA,_G_ REAL_32 _PL_ LineB,_P_ DATA_32 Length)
	LinCDiv2R64=67,		//LinC_CL : LinC_Div_2_R64_(_G_ real_64 _PL_ LineC,_G_ REAL_64 _PL_ LineA,_G_ REAL_64 _PL_ LineB,_P_ DATA_32 Length)
	LinCDiv1I08=68,		//LinC_CL : LinC_Div_1_I08_(_G_ inte_08 _PL_ LineC,_G_ INTE_08 _PL_ LineA,_P_ INTE_08 Value,_P_ DATA_32 Length)
	LinCDiv1I16=69,		//LinC_CL : LinC_Div_1_I16_(_G_ inte_16 _PL_ LineC,_G_ INTE_16 _PL_ LineA,_P_ INTE_16 Value,_P_ DATA_32 Length)
	LinCDiv1I32=70,		//LinC_CL : LinC_Div_1_I32_(_G_ inte_32 _PL_ LineC,_G_ INTE_32 _PL_ LineA,_P_ INTE_32 Value,_P_ DATA_32 Length)
	LinCDiv1I64=71,		//LinC_CL : LinC_Div_1_I64_(_G_ inte_64 _PL_ LineC,_G_ INTE_64 _PL_ LineA,_P_ INTE_64 Value,_P_ DATA_32 Length)
	LinCDiv1D08=72,		//LinC_CL : LinC_Div_1_D08_(_G_ data_08 _PL_ LineC,_G_ DATA_08 _PL_ LineA,_P_ DATA_08 Value,_P_ DATA_32 Length)
	LinCDiv1D16=73,		//LinC_CL : LinC_Div_1_D16_(_G_ data_16 _PL_ LineC,_G_ DATA_16 _PL_ LineA,_P_ DATA_16 Value,_P_ DATA_32 Length)
	LinCDiv1D32=74,		//LinC_CL : LinC_Div_1_D32_(_G_ data_32 _PL_ LineC,_G_ DATA_32 _PL_ LineA,_P_ DATA_32 Value,_P_ DATA_32 Length)
	LinCDiv1D64=75,		//LinC_CL : LinC_Div_1_D64_(_G_ data_64 _PL_ LineC,_G_ DATA_64 _PL_ LineA,_P_ DATA_64 Value,_P_ DATA_32 Length)
	LinCInv1I08=76,		//LinC_CL : LinC_Inv_1_I08_(_G_ inte_08 _PL_ LineC,_G_ INTE_08 _PL_ LineA,_P_ INTE_08 Value,_P_ DATA_32 Length)
	LinCInv1I16=77,		//LinC_CL : LinC_Inv_1_I16_(_G_ inte_16 _PL_ LineC,_G_ INTE_16 _PL_ LineA,_P_ INTE_16 Value,_P_ DATA_32 Length)
	LinCInv1I32=78,		//LinC_CL : LinC_Inv_1_I32_(_G_ inte_32 _PL_ LineC,_G_ INTE_32 _PL_ LineA,_P_ INTE_32 Value,_P_ DATA_32 Length)
	LinCInv1I64=79,		//LinC_CL : LinC_Inv_1_I64_(_G_ inte_64 _PL_ LineC,_G_ INTE_64 _PL_ LineA,_P_ INTE_64 Value,_P_ DATA_32 Length)
	LinCInv1D08=80,		//LinC_CL : LinC_Inv_1_D08_(_G_ data_08 _PL_ LineC,_G_ DATA_08 _PL_ LineA,_P_ DATA_08 Value,_P_ DATA_32 Length)
	LinCInv1D16=81,		//LinC_CL : LinC_Inv_1_D16_(_G_ data_16 _PL_ LineC,_G_ DATA_16 _PL_ LineA,_P_ DATA_16 Value,_P_ DATA_32 Length)
	LinCInv1D32=82,		//LinC_CL : LinC_Inv_1_D32_(_G_ data_32 _PL_ LineC,_G_ DATA_32 _PL_ LineA,_P_ DATA_32 Value,_P_ DATA_32 Length)
	LinCInv1D64=83,		//LinC_CL : LinC_Inv_1_D64_(_G_ data_64 _PL_ LineC,_G_ DATA_64 _PL_ LineA,_P_ DATA_64 Value,_P_ DATA_32 Length)
	LinCInv1R16=85,		//LinC_CL : LinC_Inv_1_R16_(_G_ real_16 _PL_ LineC,_G_ REAL_16 _PL_ LineA,_P_ REAL_16 Value,_P_ DATA_32 Length)
	LinCInv1R32=86,		//LinC_CL : LinC_Inv_1_R32_(_G_ real_32 _PL_ LineC,_G_ REAL_32 _PL_ LineA,_P_ REAL_32 Value,_P_ DATA_32 Length)
	LinCInv1R64=87,		//LinC_CL : LinC_Inv_1_R64_(_G_ real_64 _PL_ LineC,_G_ REAL_64 _PL_ LineA,_P_ REAL_64 Value,_P_ DATA_32 Length)

	//LinC_CL : LinC_Sum_1_I08_(_G_ inte_08 _PL_ Result,_L_ inte_08 _PL_ Work,_G_ INTE_08 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCSum1I08=88,
	//LinC_CL : LinC_Sum_1_I16_(_G_ inte_16 _PL_ Result,_L_ inte_16 _PL_ Work,_G_ INTE_16 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCSum1I16=89,
	//LinC_CL : LinC_Sum_1_I32_(_G_ inte_32 _PL_ Result,_L_ inte_32 _PL_ Work,_G_ INTE_32 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCSum1I32=90,
	//LinC_CL : LinC_Sum_1_I64_(_G_ inte_64 _PL_ Result,_L_ inte_64 _PL_ Work,_G_ INTE_64 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCSum1I64=91,
	//LinC_CL : LinC_Sum_1_R16_(_G_ real_16 _PL_ Result,_L_ real_16 _PL_ Work,_G_ REAL_16 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCSum1R16=93,
	//LinC_CL : LinC_Sum_1_R32_(_G_ real_32 _PL_ Result,_L_ real_32 _PL_ Work,_G_ REAL_32 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCSum1R32=94,
	//LinC_CL : LinC_Sum_1_R64_(_G_ real_64 _PL_ Result,_L_ real_64 _PL_ Work,_G_ REAL_64 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCSum1R64=95,

	//LinC_CL : LinC_Dot_2_I08_(_G_ inte_08 _PL_ Result,_L_ inte_08 _PL_ Work,_G_ INTE_08 *LineA,_G_ INTE_08 *LineB,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSetA), &(cl_mem)(InputSetB), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCDot2I08=96,
	//LinC_CL : LinC_Dot_2_I16_(_G_ inte_16 _PL_ Result,_L_ inte_16 _PL_ Work,_G_ INTE_16 *LineA,_G_ INTE_16 *LineB,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSetA), &(cl_mem)(InputSetB), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCDot2I16=97,
	//LinC_CL : LinC_Dot_2_I32_(_G_ inte_32 _PL_ Result,_L_ inte_32 _PL_ Work,_G_ INTE_32 *LineA,_G_ INTE_32 *LineB,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSetA), &(cl_mem)(InputSetB), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCDot2I32=98,
	//LinC_CL : LinC_Dot_2_I64_(_G_ inte_64 _PL_ Result,_L_ inte_64 _PL_ Work,_G_ INTE_64 *LineA,_G_ INTE_64 *LineB,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSetA), &(cl_mem)(InputSetB), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCDot2I64=99,
	//LinC_CL : LinC_Dot_2_R16_(_G_ real_16 _PL_ Result,_L_ real_16 _PL_ Work,_G_ REAL_16 *LineA,_G_ REAL_16 *LineB,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSetA), &(cl_mem)(InputSetB), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCDot2R16=101,
	//LinC_CL : LinC_Dot_2_R32_(_G_ real_32 _PL_ Result,_L_ real_32 _PL_ Work,_G_ REAL_32 *LineA,_G_ REAL_32 *LineB,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSetA), &(cl_mem)(InputSetB), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCDot2R32=102,
	//LinC_CL : LinC_Dot_2_R64_(_G_ real_64 _PL_ Result,_L_ real_64 _PL_ Work,_G_ REAL_64 *LineA,_G_ REAL_64 *LineB,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSetA), &(cl_mem)(InputSetB), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCDot2R64=103,

	//LinC_CL : LinC_Max_1_I08_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ INTE_08 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMax1I08=104,
	//LinC_CL : LinC_Max_1_I16_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ INTE_16 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMax1I16=105,
	//LinC_CL : LinC_Max_1_I32_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ INTE_32 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMax1I32=106,
	//LinC_CL : LinC_Max_1_I64_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ INTE_64 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMax1I64=107,
	//LinC_CL : LinC_Max_1_D08_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ DATA_08 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMax1D08=108,
	//LinC_CL : LinC_Max_1_D16_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ DATA_16 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMax1D16=109,
	//LinC_CL : LinC_Max_1_D32_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ DATA_32 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMax1D32=110,
	//LinC_CL : LinC_Max_1_D64_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ DATA_64 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMax1D64=111,
	//LinC_CL : LinC_Max_1_R16_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ REAL_16 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMax1R16=113,
	//LinC_CL : LinC_Max_1_R32_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ REAL_32 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMax1R32=114,
	//LinC_CL : LinC_Max_1_R64_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ REAL_64 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMax1R64=115,

	//LinC_CL : LinC_Min_1_I08_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ INTE_08 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMin1I08=116,
	//LinC_CL : LinC_Min_1_I16_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ INTE_16 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMin1I16=117,
	//LinC_CL : LinC_Min_1_I32_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ INTE_32 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMin1I32=118,
	//LinC_CL : LinC_Min_1_I64_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ INTE_64 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMin1I64=119,
	//LinC_CL : LinC_Min_1_D08_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ DATA_08 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMin1D08=120,
	//LinC_CL : LinC_Min_1_D16_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ DATA_16 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMin1D16=121,
	//LinC_CL : LinC_Min_1_D32_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ DATA_32 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMin1D32=122,
	//LinC_CL : LinC_Min_1_D64_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ DATA_64 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMin1D64=123,
	//LinC_CL : LinC_Min_1_R16_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ REAL_16 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMin1R16=125,
	//LinC_CL : LinC_Min_1_R32_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ REAL_32 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMin1R32=126,
	//LinC_CL : LinC_Min_1_R64_(_G_ data_32 _PL_ Result,_L_ general _PL_ Work,_G_ REAL_64 *Line,_P_ DATA_32 Length)
	//＊Pass arguments as
	//　{ &(cl_mem)(OutputSet), &(cl_mem)(InputSet), &(data_32)(LineNumber), &(data_32)(LineLength) }
	LinCMin1R64=127,

	LinCMap1D08=128,	//LinC_CL : LinC_Map_1_D08_(_G_ data_08 *Line,_G_ DATA_32 *Match,_G_ DATA_08 *Table,_P_ DATA_32 Number,_P_ DATA_32 Length)
	LinCMap1D16=129,	//LinC_CL : LinC_Map_1_D16_(_G_ data_16 *Line,_G_ DATA_32 *Match,_G_ DATA_16 *Table,_P_ DATA_32 Number,_P_ DATA_32 Length)
	LinCMap1D32=130,	//LinC_CL : LinC_Map_1_D32_(_G_ data_32 *Line,_G_ DATA_32 *Match,_G_ DATA_32 *Table,_P_ DATA_32 Number,_P_ DATA_32 Length)
	LinCMap1D64=131,	//LinC_CL : LinC_Map_1_D64_(_G_ data_64 *Line,_G_ DATA_32 *Match,_G_ DATA_64 *Table,_P_ DATA_32 Number,_P_ DATA_32 Length)
	
	LinCKernels=132		//LinC_CL : The Number of Kernels
};
MemC_Type_Declare_(enum,linc_ki,LINC_KI);	//LinC_CL : LinCKernel Indicator Enumeration

struct _linc_cl					//LinC_CL : Kernel Manager Set Structure
{
	PENC_CL _PL_ Helper;		//LinC_CL : Program Resource
	DEVI_KM _PL_ _PL_ KMSet;	//LinC_CL : Kernel Manager Set
};
MemC_Type_Declare_(struct,linc_cl,LINC_CL);	//LinC_CL : Kernel Manager Set Structure
#endif
#endif

#if(MemC_Fold_(Declaration:Global Constants))
//LinClip : Library Version
extern DATA_08 _PL_ LinClip;

#ifdef __OPENCL_H
//LinC_CL :
extern NAME_08 _PL_ _PL_ LinCFile;
//LinC_CL : Kernel Indicator Set
extern NAME_08 _PL_ _PL_ LinCKernel;
#endif
#endif

#if(MemC_Fold_(Declaration:Arithmetic Progression Functions))
//LinClip : 8-bit Integer Line Arithmetic Progression
//＊C[n]＝S＋(n×K)
general LinC_Ari_0_I08_(inte_08 *_R_ C,INTE_08 S,INTE_08 K,DATA_32 N);
//LinClip : 16-bit Integer Line Arithmetic Progression
//＊C[n]＝S＋(n×K)
general LinC_Ari_0_I16_(inte_16 *_R_ C,INTE_16 S,INTE_16 K,DATA_32 N);
//LinClip : 32-bit Integer Line Arithmetic Progression
//＊C[n]＝S＋(n×K)
general LinC_Ari_0_I32_(inte_32 *_R_ C,INTE_32 S,INTE_32 K,DATA_32 N);
//LinClip : 64-bit Integer Line Arithmetic Progression
//＊C[n]＝S＋(n×K)
general LinC_Ari_0_I64_(inte_64 *_R_ C,INTE_64 S,INTE_64 K,DATA_32 N);
//LinClip : 32-bit Real Line Arithmetic Progression
//＊C[n]＝S＋(n×K)
general LinC_Ari_0_R32_(real_32 *_R_ C,REAL_32 S,REAL_32 K,DATA_32 N);
//LinClip : 64-bit Real Line Arithmetic Progression
//＊C[n]＝S＋(n×K)
general LinC_Ari_0_R64_(real_64 *_R_ C,REAL_64 S,REAL_64 K,DATA_32 N);
#endif

#if(MemC_Fold_(Declaration:Geometric Progression Functions))
//LinClip : 8-bit Integer Line Geometric Progression
//＊C[n]＝S×Kⁿ
general LinC_Geo_0_I08_(inte_08 *_R_ C,INTE_08 S,INTE_08 K,DATA_32 N);
//LinClip : 16-bit Integer Line Geometric Progression
//＊C[n]＝S×Kⁿ
general LinC_Geo_0_I16_(inte_16 *_R_ C,INTE_16 S,INTE_16 K,DATA_32 N);
//LinClip : 32-bit Integer Line Geometric Progression
//＊C[n]＝S×Kⁿ
general LinC_Geo_0_I32_(inte_32 *_R_ C,INTE_32 S,INTE_32 K,DATA_32 N);
//LinClip : 64-bit Integer Line Geometric Progression
//＊C[n]＝S×Kⁿ
general LinC_Geo_0_I64_(inte_64 *_R_ C,INTE_64 S,INTE_64 K,DATA_32 N);
//LinClip : 32-bit Real Line Geometric Progression
//＊C[n]＝S×Kⁿ
general LinC_Geo_0_R32_(real_32 *_R_ C,REAL_32 S,REAL_32 K,DATA_32 N);
//LinClip : 64-bit Real Line Geometric Progression
//＊C[n]＝S×Kⁿ
general LinC_Geo_0_R64_(real_64 *_R_ C,REAL_64 S,REAL_64 K,DATA_32 N);
#endif

#if(MemC_Fold_(Declaration:Increment Functions))
//LinClip : 8-bit Integer Line Increment
//＊C[n]＝A[n]＋K
general LinC_Inc_1_I08_(inte_08 *C,INTE_08 *A,INTE_08 K,DATA_32 N);
//LinClip : 16-bit Integer Line Increment
//＊C[n]＝A[n]＋K
general LinC_Inc_1_I16_(inte_16 *C,INTE_16 *A,INTE_16 K,DATA_32 N);
//LinClip : 32-bit Integer Line Increment
//＊C[n]＝A[n]＋K
general LinC_Inc_1_I32_(inte_32 *C,INTE_32 *A,INTE_32 K,DATA_32 N);
//LinClip : 64-bit Integer Line Increment
//＊C[n]＝A[n]＋K
general LinC_Inc_1_I64_(inte_64 *C,INTE_64 *A,INTE_64 K,DATA_32 N);
//LinClip : 32-bit Real Line Increment
//＊C[n]＝A[n]＋K
general LinC_Inc_1_R32_(real_32 *C,REAL_32 *A,REAL_32 K,DATA_32 N);
//LinClip : 64-bit Real Line Increment
//＊C[n]＝A[n]＋K
general LinC_Inc_1_R64_(real_64 *C,REAL_64 *A,REAL_64 K,DATA_32 N);
#endif

#if(MemC_Fold_(Declaration:Amplification Functions))
//LinClip : 8-bit Integer Line Amplification
//＊C[n]＝K×A[n]
general LinC_Amp_1_I08_(inte_08 *C,INTE_08 *A,INTE_08 K,DATA_32 N);
//LinClip : 16-bit Integer Line Amplification
//＊C[n]＝K×A[n]
general LinC_Amp_1_I16_(inte_16 *C,INTE_16 *A,INTE_16 K,DATA_32 N);
//LinClip : 32-bit Integer Line Amplification
//＊C[n]＝K×A[n]
general LinC_Amp_1_I32_(inte_32 *C,INTE_32 *A,INTE_32 K,DATA_32 N);
//LinClip : 64-bit Integer Line Amplification
//＊C[n]＝K×A[n]
general LinC_Amp_1_I64_(inte_64 *C,INTE_64 *A,INTE_64 K,DATA_32 N);
//LinClip : 32-bit Real Line Amplification
//＊C[n]＝K×A[n]
general LinC_Amp_1_R32_(real_32 *C,REAL_32 *A,REAL_32 K,DATA_32 N);
//LinClip : 64-bit Real Line Amplification
//＊C[n]＝K×A[n]
general LinC_Amp_1_R64_(real_64 *C,REAL_64 *A,REAL_64 K,DATA_32 N);
#endif

#if(MemC_Fold_(Declaration:Addition Functions))
//LinClip : 8-bit Integer Line Addition
//＊C[n]＝A[n]＋B[n]
general LinC_Add_2_I08_(inte_08 *C,INTE_08 *A,INTE_08 *B,DATA_32 N);
//LinClip : 16-bit Integer Line Addition
//＊C[n]＝A[n]＋B[n]
general LinC_Add_2_I16_(inte_16 *C,INTE_16 *A,INTE_16 *B,DATA_32 N);
//LinClip : 32-bit Integer Line Addition
//＊C[n]＝A[n]＋B[n]
general LinC_Add_2_I32_(inte_32 *C,INTE_32 *A,INTE_32 *B,DATA_32 N);
//LinClip : 64-bit Integer Line Addition
//＊C[n]＝A[n]＋B[n]
general LinC_Add_2_I64_(inte_64 *C,INTE_64 *A,INTE_64 *B,DATA_32 N);
//LinClip : 32-bit Real Line Addition
//＊C[n]＝A[n]＋B[n]
general LinC_Add_2_R32_(real_32 *C,REAL_32 *A,REAL_32 *B,DATA_32 N);
//LinClip : 64-bit Real Line Addition
//＊C[n]＝A[n]＋B[n]
general LinC_Add_2_R64_(real_64 *C,REAL_64 *A,REAL_64 *B,DATA_32 N);
#endif

#if(MemC_Fold_(Declaration:Subtraction Functions))
//LinClip : 8-bit Integer Line Subtraction
//＊C[n]＝A[n]－B[n]
general LinC_Sub_2_I08_(inte_08 *C,INTE_08 *A,INTE_08 *B,DATA_32 N);
//LinClip : 16-bit Integer Line Subtraction
//＊C[n]＝A[n]－B[n]
general LinC_Sub_2_I16_(inte_16 *C,INTE_16 *A,INTE_16 *B,DATA_32 N);
//LinClip : 32-bit Integer Line Subtraction
//＊C[n]＝A[n]－B[n]
general LinC_Sub_2_I32_(inte_32 *C,INTE_32 *A,INTE_32 *B,DATA_32 N);
//LinClip : 64-bit Integer Line Subtraction
//＊C[n]＝A[n]－B[n]
general LinC_Sub_2_I64_(inte_64 *C,INTE_64 *A,INTE_64 *B,DATA_32 N);
//LinClip : 32-bit Real Line Subtraction
//＊C[n]＝A[n]－B[n]
general LinC_Sub_2_R32_(real_32 *C,REAL_32 *A,REAL_32 *B,DATA_32 N);
//LinClip : 64-bit Real Line Subtraction
//＊C[n]＝A[n]－B[n]
general LinC_Sub_2_R64_(real_64 *C,REAL_64 *A,REAL_64 *B,DATA_32 N);
#endif

#if(MemC_Fold_(Declaration:Multiplication Functions))
//LinClip : 8-bit Integer Line Multiplication
//＊C[n]＝A[n]×B[n]
general LinC_Mul_2_I08_(inte_08 *C,INTE_08 *A,INTE_08 *B,DATA_32 N);
//LinClip : 16-bit Integer Line Multiplication
//＊C[n]＝A[n]×B[n]
general LinC_Mul_2_I16_(inte_16 *C,INTE_16 *A,INTE_16 *B,DATA_32 N);
//LinClip : 32-bit Integer Line Multiplication
//＊C[n]＝A[n]×B[n]
general LinC_Mul_2_I32_(inte_32 *C,INTE_32 *A,INTE_32 *B,DATA_32 N);
//LinClip : 64-bit Integer Line Multiplication
//＊C[n]＝A[n]×B[n]
general LinC_Mul_2_I64_(inte_64 *C,INTE_64 *A,INTE_64 *B,DATA_32 N);
//LinClip : 32-bit Real Line Multiplication
//＊C[n]＝A[n]×B[n]
general LinC_Mul_2_R32_(real_32 *C,REAL_32 *A,REAL_32 *B,DATA_32 N);
//LinClip : 64-bit Real Line Multiplication
//＊C[n]＝A[n]×B[n]
general LinC_Mul_2_R64_(real_64 *C,REAL_64 *A,REAL_64 *B,DATA_32 N);
#endif

#if(MemC_Fold_(Declaration:Division Functions))
//LinClip : 8-bit Integer Line Division
//＊C[n]＝A[n]÷K
general LinC_Div_1_I08_(inte_08 *C,INTE_08 *A,INTE_08 K,DATA_32 N);
//LinClip : 16-bit Integer Line Division
//＊C[n]＝A[n]÷K
general LinC_Div_1_I16_(inte_16 *C,INTE_16 *A,INTE_16 K,DATA_32 N);
//LinClip : 32-bit Integer Line Division
//＊C[n]＝A[n]÷K
general LinC_Div_1_I32_(inte_32 *C,INTE_32 *A,INTE_32 K,DATA_32 N);
//LinClip : 64-bit Integer Line Division
//＊C[n]＝A[n]÷K
general LinC_Div_1_I64_(inte_64 *C,INTE_64 *A,INTE_64 K,DATA_32 N);
//LinClip : 8-bit Natural Line Division
//＊C[n]＝A[n]÷K
general LinC_Div_1_D08_(data_08 *C,DATA_08 *A,DATA_08 K,DATA_32 N);
//LinClip : 16-bit Natural Line Division
//＊C[n]＝A[n]÷K
general LinC_Div_1_D16_(data_16 *C,DATA_16 *A,DATA_16 K,DATA_32 N);
//LinClip : 32-bit Natural Line Division
//＊C[n]＝A[n]÷K
general LinC_Div_1_D32_(data_32 *C,DATA_32 *A,DATA_32 K,DATA_32 N);
//LinClip : 64-bit Natural Line Division
//＊C[n]＝A[n]÷K
general LinC_Div_1_D64_(data_64 *C,DATA_64 *A,DATA_64 K,DATA_32 N);

//LinClip : 8-bit Integer Line Division
//＊C[n]＝K÷A[n]
general LinC_Inv_1_I08_(inte_08 *C,INTE_08 *A,INTE_08 K,DATA_32 N);
//LinClip : 16-bit Integer Line Division
//＊C[n]＝K÷A[n]
general LinC_Inv_1_I16_(inte_16 *C,INTE_16 *A,INTE_16 K,DATA_32 N);
//LinClip : 32-bit Integer Line Division
//＊C[n]＝K÷A[n]
general LinC_Inv_1_I32_(inte_32 *C,INTE_32 *A,INTE_32 K,DATA_32 N);
//LinClip : 64-bit Integer Line Division
//＊C[n]＝K÷A[n]
general LinC_Inv_1_I64_(inte_64 *C,INTE_64 *A,INTE_64 K,DATA_32 N);
//LinClip : 8-bit Natural Line Division
//＊C[n]＝K÷A[n]
general LinC_Inv_1_D08_(data_08 *C,DATA_08 *A,DATA_08 K,DATA_32 N);
//LinClip : 16-bit Natural Line Division
//＊C[n]＝K÷A[n]
general LinC_Inv_1_D16_(data_16 *C,DATA_16 *A,DATA_16 K,DATA_32 N);
//LinClip : 32-bit Natural Line Division
//＊C[n]＝K÷A[n]
general LinC_Inv_1_D32_(data_32 *C,DATA_32 *A,DATA_32 K,DATA_32 N);
//LinClip : 64-bit Natural Line Division
//＊C[n]＝K÷A[n]
general LinC_Inv_1_D64_(data_64 *C,DATA_64 *A,DATA_64 K,DATA_32 N);
//LinClip : 32-bit Real Line Division
//＊C[n]＝K÷A[n]
general LinC_Inv_1_R32_(real_32 *C,REAL_32 *A,REAL_32 K,DATA_32 N);
//LinClip : 64-bit Real Line Division
//＊C[n]＝K÷A[n]
general LinC_Inv_1_R64_(real_64 *C,REAL_64 *A,REAL_64 K,DATA_32 N);

//LinClip : 8-bit Integer Line Division
//＊C[n]＝A[n]÷B[n]
general LinC_Div_2_I08_(inte_08 *C,INTE_08 *A,INTE_08 *B,DATA_32 N);
//LinClip : 16-bit Integer Line Division
//＊C[n]＝A[n]÷B[n]
general LinC_Div_2_I16_(inte_16 *C,INTE_16 *A,INTE_16 *B,DATA_32 N);
//LinClip : 32-bit Integer Line Division
//＊C[n]＝A[n]÷B[n]
general LinC_Div_2_I32_(inte_32 *C,INTE_32 *A,INTE_32 *B,DATA_32 N);
//LinClip : 64-bit Integer Line Division
//＊C[n]＝A[n]÷B[n]
general LinC_Div_2_I64_(inte_64 *C,INTE_64 *A,INTE_64 *B,DATA_32 N);
//LinClip : 8-bit Natural Line Division
//＊C[n]＝A[n]÷B[n]
general LinC_Div_2_D08_(data_08 *C,DATA_08 *A,DATA_08 *B,DATA_32 N);
//LinClip : 16-bit Natural Line Division
//＊C[n]＝A[n]÷B[n]
general LinC_Div_2_D16_(data_16 *C,DATA_16 *A,DATA_16 *B,DATA_32 N);
//LinClip : 32-bit Natural Line Division
//＊C[n]＝A[n]÷B[n]
general LinC_Div_2_D32_(data_32 *C,DATA_32 *A,DATA_32 *B,DATA_32 N);
//LinClip : 64-bit Natural Line Division
//＊C[n]＝A[n]÷B[n]
general LinC_Div_2_D64_(data_64 *C,DATA_64 *A,DATA_64 *B,DATA_32 N);
//LinClip : 32-bit Real Line Division
//＊C[n]＝A[n]÷B[n]
general LinC_Div_2_R32_(real_32 *C,REAL_32 *A,REAL_32 *B,DATA_32 N);
//LinClip : 64-bit Real Line Division
//＊C[n]＝A[n]÷B[n]
general LinC_Div_2_R64_(real_64 *C,REAL_64 *A,REAL_64 *B,DATA_32 N);
#endif

#if(MemC_Fold_(Declaration:Modulo Functions))
//LinClip : 8-bit Natural Line Modulo
//＊C[n]＝A[n]％K
general LinC_Mod_1_D08_(data_08 *C,DATA_08 *A,DATA_08 K,DATA_32 N);
//LinClip : 16-bit Natural Line Modulo
//＊C[n]＝A[n]％K
general LinC_Mod_1_D16_(data_16 *C,DATA_16 *A,DATA_16 K,DATA_32 N);
//LinClip : 32-bit Natural Line Modulo
//＊C[n]＝A[n]％K
general LinC_Mod_1_D32_(data_32 *C,DATA_32 *A,DATA_32 K,DATA_32 N);
//LinClip : 64-bit Natural Line Modulo
//＊C[n]＝A[n]％K
general LinC_Mod_1_D64_(data_64 *C,DATA_64 *A,DATA_64 K,DATA_32 N);
//LinClip : 8-bit Integer Line Modulo
//＊C[n]＝A[n]％K
general LinC_Mod_1_I08_(inte_08 *C,INTE_08 *A,INTE_08 K,DATA_32 N);
//LinClip : 16-bit Integer Line Modulo
//＊C[n]＝A[n]％K
general LinC_Mod_1_I16_(inte_16 *C,INTE_16 *A,INTE_16 K,DATA_32 N);
//LinClip : 32-bit Integer Line Modulo
//＊C[n]＝A[n]％K
general LinC_Mod_1_I32_(inte_32 *C,INTE_32 *A,INTE_32 K,DATA_32 N);
//LinClip : 64-bit Integer Line Modulo
//＊C[n]＝A[n]％K
general LinC_Mod_1_I64_(inte_64 *C,INTE_64 *A,INTE_64 K,DATA_32 N);
#endif

#if(MemC_Fold_(Declaration:Summation Functions))
//LinClip : 8-bit Integer Line Summation
//＊S＝∑A[n]
inte_08 LinC_Sum_1_I08_(INTE_08 *_R_ A,DATA_32 N);
//LinClip : 16-bit Integer Line Summation
//＊S＝∑A[n]
inte_16 LinC_Sum_1_I16_(INTE_16 *_R_ A,DATA_32 N);
//LinClip : 32-bit Integer Line Summation
//＊S＝∑A[n]
inte_32 LinC_Sum_1_I32_(INTE_32 *_R_ A,DATA_32 N);
//LinClip : 64-bit Integer Line Summation
//＊S＝∑A[n]
inte_64 LinC_Sum_1_I64_(INTE_64 *_R_ A,DATA_32 N);
//LinClip : 32-bit Real Line Summation
//＊S＝∑A[n]
real_32 LinC_Sum_1_R32_(REAL_32 *_R_ A,DATA_32 N);
//LinClip : 64-bit Real Line Summation
//＊S＝∑A[n]
real_64 LinC_Sum_1_R64_(REAL_64 *_R_ A,DATA_32 N);
#endif

#if(MemC_Fold_(Declaration:Dot-Product Functions))
//LinClip : 8-bit Integer Line Dot Product
//＊S＝∑A[n]×B[n]
inte_08 LinC_Dot_2_I08_(INTE_08 *A,INTE_08 *B,DATA_32 N);
//LinClip : 16-bit Integer Line Dot Product
//＊S＝∑A[n]×B[n]
inte_16 LinC_Dot_2_I16_(INTE_16 *A,INTE_16 *B,DATA_32 N);
//LinClip : 16-bit Integer Line Dot Product
//＊S＝∑A[n]×B[n]
inte_32 LinC_Dot_2_I32_(INTE_32 *A,INTE_32 *B,DATA_32 N);
//LinClip : 16-bit Integer Line Dot Product
//＊S＝∑A[n]×B[n]
inte_64 LinC_Dot_2_I64_(INTE_64 *A,INTE_64 *B,DATA_32 N);
//LinClip : 32-bit Real Line Dot Product
//＊S＝∑A[n]×B[n]
real_32 LinC_Dot_2_R32_(REAL_32 *A,REAL_32 *B,DATA_32 N);
//LinClip : 64-bit Real Line Dot Product
//＊S＝∑A[n]×B[n]
real_64 LinC_Dot_2_R64_(REAL_64 *A,REAL_64 *B,DATA_32 N);
#endif

#if(MemC_Fold_(Declaration:Maximum Functions))
//LinClip : 8-Bit Integer Line Maximum
//＊n＝argmax{A}
data_32 LinC_Max_1_I08_(INTE_08 _PL_ A,DATA_32 N);
//LinClip : 16-Bit Integer Line Maximum
//＊n＝argmax{A}
data_32 LinC_Max_1_I16_(INTE_16 _PL_ A,DATA_32 N);
//LinClip : 32-Bit Integer Line Maximum
//＊n＝argmax{A}
data_32 LinC_Max_1_I32_(INTE_32 _PL_ A,DATA_32 N);
//LinClip : 64-Bit Integer Line Maximum
//＊n＝argmax{A}
data_32 LinC_Max_1_I64_(INTE_64 _PL_ A,DATA_32 N);
//LinClip : 8-Bit Natural Line Maximum
//＊n＝argmax{A}
data_32 LinC_Max_1_D08_(DATA_08 _PL_ A,DATA_32 N);
//LinClip : 16-Bit Natural Line Maximum
//＊n＝argmax{A}
data_32 LinC_Max_1_D16_(DATA_16 _PL_ A,DATA_32 N);
//LinClip : 32-Bit Natural Line Maximum
//＊n＝argmax{A}
data_32 LinC_Max_1_D32_(DATA_32 _PL_ A,DATA_32 N);
//LinClip : 64-Bit Natural Line Maximum
//＊n＝argmax{A}
data_32 LinC_Max_1_D64_(DATA_64 _PL_ A,DATA_32 N);
//LinClip : 32-Bit Real Line Maximum
//＊n＝argmax{A}
data_32 LinC_Max_1_R32_(REAL_32 _PL_ A,DATA_32 N);
//LinClip : 64-Bit Real Line Maximum
//＊n＝argmax{A}
data_32 LinC_Max_1_R64_(REAL_64 _PL_ A,DATA_32 N);
#endif

#if(MemC_Fold_(Declaration:Minimum Functions))
//LinClip : 8-Bit Integer Line Minimum
//＊n＝argmin{A}
data_32 LinC_Min_1_I08_(INTE_08 _PL_ A,DATA_32 N);
//LinClip : 16-Bit Integer Line Minimum
//＊n＝argmin{A}
data_32 LinC_Min_1_I16_(INTE_16 _PL_ A,DATA_32 N);
//LinClip : 32-Bit Integer Line Minimum
//＊n＝argmin{A}
data_32 LinC_Min_1_I32_(INTE_32 _PL_ A,DATA_32 N);
//LinClip : 64-Bit Integer Line Minimum
//＊n＝argmin{A}
data_32 LinC_Min_1_I64_(INTE_64 _PL_ A,DATA_32 N);
//LinClip : 8-Bit Natural Line Minimum
//＊n＝argmin{A}
data_32 LinC_Min_1_D08_(DATA_08 _PL_ A,DATA_32 N);
//LinClip : 16-Bit Natural Line Minimum
//＊n＝argmin{A}
data_32 LinC_Min_1_D16_(DATA_16 _PL_ A,DATA_32 N);
//LinClip : 32-Bit Natural Line Minimum
//＊n＝argmin{A}
data_32 LinC_Min_1_D32_(DATA_32 _PL_ A,DATA_32 N);
//LinClip : 64-Bit Natural Line Minimum
//＊n＝argmin{A}
data_32 LinC_Min_1_D64_(DATA_64 _PL_ A,DATA_32 N);
//LinClip : 32-Bit Real Line Minimum
//＊n＝argmin{A}
data_32 LinC_Min_1_R32_(REAL_32 _PL_ A,DATA_32 N);
//LinClip : 64-Bit Real Line Minimum
//＊n＝argmin{A}
data_32 LinC_Min_1_R64_(REAL_64 _PL_ A,DATA_32 N);
#endif

#if(MemC_Fold_(Declaration:Sorting Functions))
//LinClip : 8-Bit Integer Recursive Radix Sorting
//＊Required (ValueLine) size is (Length)×1 bytes.
//　Required (IndexLine) size is (Length)×4 bytes.
//　Required (Buffer) size is (Length)×5 bytes.
//＊Mode Null : Ascending Order
//　Mode Full : Descending Order
//＊(ValueLine) and (IndexLine) should be initialized before processing.
general LinC_Order_I08_(inte_08 _PL_ ValueLine,data_32 _PL_ IndexLine,general _PL_ Buffer,DATA_32 Length,BOOLEAN Mode);
//LinClip : 16-Bit Integer Recursive Radix Sorting
//＊Required (ValueLine) size is (Length)×2 bytes.
//　Required (IndexLine) size is (Length)×4 bytes.
//　Required (Buffer) size is (Length)×6 bytes.
//＊Mode Null : Ascending Order
//　Mode Full : Descending Order
//＊(ValueLine) and (IndexLine) should be initialized before processing.
general LinC_Order_I16_(inte_16 _PL_ ValueLine,data_32 _PL_ IndexLine,general _PL_ Buffer,DATA_32 Length,BOOLEAN Mode);
//LinClip : 32-Bit Integer Recursive Radix Sorting
//＊Required (ValueLine) size is (Length)×4 bytes.
//　Required (IndexLine) size is (Length)×4 bytes.
//　Required (Buffer) size is (Length)×8 bytes.
//＊Mode Null : Ascending Order
//　Mode Full : Descending Order
//＊(ValueLine) and (IndexLine) should be initialized before processing.
general LinC_Order_I32_(inte_32 _PL_ ValueLine,data_32 _PL_ IndexLine,general _PL_ Buffer,DATA_32 Length,BOOLEAN Mode);
//LinClip : 64-Bit Integer Recursive Radix Sorting
//＊Required (ValueLine) size is (Length)×8 bytes.
//　Required (IndexLine) size is (Length)×4 bytes.
//　Required (Buffer) size is (Length)×12 bytes.
//＊Mode Null : Ascending Order
//　Mode Full : Descending Order
//＊(ValueLine) and (IndexLine) should be initialized before processing.
general LinC_Order_I64_(inte_64 _PL_ ValueLine,data_32 _PL_ IndexLine,general _PL_ Buffer,DATA_32 Length,BOOLEAN Mode);
//LinClip : 8-Bit Natural Recursive Radix Sorting
//＊Required (ValueLine) size is (Length)×1 bytes.
//　Required (IndexLine) size is (Length)×4 bytes.
//　Required (Buffer) size is (Length)×5 bytes.
//＊Mode Null : Ascending Order
//　Mode Full : Descending Order
//＊(ValueLine) and (IndexLine) should be initialized before processing.
general LinC_Order_D08_(data_08 _PL_ ValueLine,data_32 _PL_ IndexLine,general _PL_ Buffer,DATA_32 Length,BOOLEAN Mode);
//LinClip : 16-Bit Natural Recursive Radix Sorting
//＊Required (ValueLine) size is (Length)×2 bytes.
//　Required (IndexLine) size is (Length)×4 bytes.
//　Required (Buffer) size is (Length)×6 bytes.
//＊Mode Null : Ascending Order
//　Mode Full : Descending Order
//＊(ValueLine) and (IndexLine) should be initialized before processing.
general LinC_Order_D16_(data_16 _PL_ ValueLine,data_32 _PL_ IndexLine,general _PL_ Buffer,DATA_32 Length,BOOLEAN Mode);
//LinClip : 32-Bit Natural Recursive Radix Sorting
//＊Required (ValueLine) size is (Length)×4 bytes.
//　Required (IndexLine) size is (Length)×4 bytes.
//　Required (Buffer) size is (Length)×8 bytes.
//＊Mode Null : Ascending Order
//　Mode Full : Descending Order
//＊(ValueLine) and (IndexLine) should be initialized before processing.
general LinC_Order_D32_(data_32 _PL_ ValueLine,data_32 _PL_ IndexLine,general _PL_ Buffer,DATA_32 Length,BOOLEAN Mode);
//LinClip : 64-Bit Natural Recursive Radix Sorting
//＊Required (ValueLine) size is (Length)×8 bytes.
//　Required (IndexLine) size is (Length)×4 bytes.
//　Required (Buffer) size is (Length)×12 bytes.
//＊Mode Null : Ascending Order
//　Mode Full : Descending Order
//＊(ValueLine) and (IndexLine) should be initialized before processing.
general LinC_Order_D64_(data_64 _PL_ ValueLine,data_32 _PL_ IndexLine,general _PL_ Buffer,DATA_32 Length,BOOLEAN Mode);
//LinClip : 32-Bit Real Recursive Radix Sorting
//＊Required (ValueLine) size is (Length)×4 bytes.
//　Required (IndexLine) size is (Length)×4 bytes.
//　Required (Buffer) size is (Length)×8 bytes.
//＊Mode Null : Ascending Order
//　Mode Full : Descending Order
//＊(ValueLine) and (IndexLine) should be initialized before processing.
general LinC_Order_R32_(real_32 _PL_ ValueLine,data_32 _PL_ IndexLine,general _PL_ Buffer,DATA_32 Length,BOOLEAN Mode);
//LinClip : 64-Bit Real Recursive Radix Sorting
//＊Required (ValueLine) size is (Length)×8 bytes.
//　Required (IndexLine) size is (Length)×4 bytes.
//　Required (Buffer) size is (Length)×12 bytes.
//＊Mode Null : Ascending Order
//　Mode Full : Descending Order
//＊(ValueLine) and (IndexLine) should be initialized before processing.
general LinC_Order_R64_(real_64 _PL_ ValueLine,data_32 _PL_ IndexLine,general _PL_ Buffer,DATA_32 Length,BOOLEAN Mode);
#endif

#if(MemC_Fold_(Declaration:Mapping Functions))
//LinClip : 8-Bit Natural Line Mapping
//＊C[n]＝T[I[n]]
general LinC_Map_1_D08_(data_08 *_R_ C,DATA_32 *_R_ I,DATA_08 _PL_ T,DATA_32 N);
//LinClip : 16-Bit Natural Line Mapping
//＊C[n]＝T[I[n]]
general LinC_Map_1_D16_(data_16 *_R_ C,DATA_32 *_R_ I,DATA_16 _PL_ T,DATA_32 N);
//LinClip : 32-Bit Natural Line Mapping
//＊C[n]＝T[I[n]]
general LinC_Map_1_D32_(data_32 *_R_ C,DATA_32 *_R_ I,DATA_32 _PL_ T,DATA_32 N);
//LinClip : 64-Bit Natural Line Mapping
//＊C[n]＝T[I[n]]
general LinC_Map_1_D64_(data_64 *_R_ C,DATA_32 *_R_ I,DATA_64 _PL_ T,DATA_32 N);
//LinClip : Redefined Natural Line Mapping
//＊C[n]＝T[I[n]]
#define LinC_Map_1_(C,I,T,N) __dl{switch(sizeof(*(T))){case 1:LinC_Map_1_D08_((data_08*)(C),I,(data_08*)(T),N);break;case 2:LinC_Map_1_D16_((data_16*)(C),I,(data_16*)(T),N);break;case 4:LinC_Map_1_D32_((data_32*)(C),I,(data_32*)(T),N);break;case 8:LinC_Map_1_D64_((data_64*)(C),I,(data_64*)(T),N);break;default:;static_assert((sizeof(*(C))==sizeof(*(T))),"Type Size Error");}}lb__
#endif

#if(MemC_Fold_(Definition:LinClip Kernel Manager Functions))
#ifdef __OPENCL_H
//LinC_CL : Program Build
//＊Return value is an error code.
penc_eu LinC_CL_Binary_(cl_command_queue const Queue,NAME_08 _PL_ SourceDirectory,NAME_08 _PL_ ObjectDirectory,NAME_08 _PL_ BuildOption,FILE _PL_ MessageStream);

//LinC_CL : Kernel Manager Set Memory Allocation - Deallocate with "LinC_CL_Delete_"
linc_cl *LinC_CL_Create_(general);
//LinC_CL : Kernel Activation Check Table
//＊Example of checking the kernel "LinC_Amp_1_R32_" :
//　LinC_CL_Choice_( KernelManager ) [ LinCAmp1R32 ] = 1;
//＊Do not access the returned table after "LinC_CL_Launch_"
address *LinC_CL_Choice_(LINC_CL _PL_ KernelManager);
//LinC_CL : OpenCL Program Build with Specified Kernels
//＊Execute only one time.
//＊Return value is an error code.
penc_eu LinC_CL_Launch_(cl_command_queue const Queue,LINC_CL _PL_ KernelManager,NAME_08 _PL_ ObjectDirectory,NAME_08 _PL_ BuildOption,FILE _PL_ MessageStream);
//LinC_CL : Kernel Manager Set Memory Deallocation
general LinC_CL_Delete_(linc_cl *_PL_ KernelManager);

//LinC_CL : Kernel Manager Task Enqueueing
//＊Default Example for KernelIndicator : LinCAmp1R32
//　KernelArgument -> Slot.P = { &(cl_mem)(LineC), &(cl_mem)(LineA), &(real_32)(Scale), &(data_32)(Length) }
//＊For the cases of passing a local memory argument,
//　namely LinCSum1T##, LinCDot2T##, LinCMax1T##, and LinCMin1T##,
//　follow the commented protocol of the corressponding kernel indicator enumeration.
//＊Return value is an error code.
penc_eu LinC_CL_Action_(LINC_CL _PL_ KernelManager,MEMC_MS _PL_ KernelArgument,LINC_KI KernelIndicator);
#endif
#endif
#endif
