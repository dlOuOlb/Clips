#include "bitclip.h"

#if(MemC_Fold_(Definition:BitClip Macros))
#define _BitC_Min_(A,B) (((A)<(B))?(A):(B))
#define _BitC_Max_(A,B) (((A)>(B))?(A):(B))
#define _BitC_Clamp_(Data,Min,Max) (((Data)<(Min))?(Min):(((Data)>(Max))?(Max):(Data)))

#define _BitC_DT_Define_(IType,type,IFlag) MemC_DT_Define_(IdiomVersion,IType,IdiomTypeName[IType],IFlag,NULL,NULL,type)
#define _BitC_DT_Flag_Sign_(Bool) ((Bool)<<2)
#define _BitC_DT_Flag_Real_(Bool) ((Bool)<<3)
#define _BitC_DT_Flag_Bits_(Bits) _BitC_DT_Flag_Bits_##Bits##_
#define _BitC_DT_Flag_Bits_08_ (0)
#define _BitC_DT_Flag_Bits_16_ (1)
#define _BitC_DT_Flag_Bits_32_ (2)
#define _BitC_DT_Flag_Bits_64_ (3)
#endif

#if(MemC_Fold_(Definition:BitCrux Macros))
#define BitC_XX_(Bits) ((1##Bits)-(1##00))
#define _BitC_TXX_(Type,Bits) Type##Bits
#define BitC_TXX_(Type,Bits) _BitC_TXX_(Type,Bits)

#define _BitC_Type_(Type,Bits) Type##_##Bits
#define BitC_Type_(Type,Bits) _BitC_Type_(Type,Bits)

#define _BitC_Func_(Name,Suffix) general BitC_##Name##_##Suffix##_
#define BitC_Func_(Name,Suffix) _BitC_Func_(Name,Suffix)

#define _BitC_Cast_(Source,Target) general BitC_Caster_##Source##_##Target##_
#define BitC_Cast_(Source,Target) _BitC_Cast_(Source,Target)

#define _BitC_Oper_(Oper,N,TXX) general Oper##N##_##TXX##_
#define BitC_Oper_(Oper,N,TXX) _BitC_Oper_(Oper,N,TXX)

#define _BitC_Wide_(TXX) _BitC_Wide_Mask_##TXX##_
#define BitC_Wide_(TXX) _BitC_Wide_(TXX)

#define BitC_BO_A_(U,V) ((U)&(V))
#define BitC_BO_O_(U,V) ((U)|(V))
#define BitC_BO_X_(U,V) ((U)^(V))

#define BitC_RO_E_(U,V) ((U)==(V))
#define BitC_RO_N_(U,V) ((U)!=(V))
#define BitC_RO_G_(U,V) ((U)>=(V))
#define BitC_RO_L_(U,V) ((U)<(V))
#endif

#if(MemC_Fold_(Definition:Global Constants))
static DATA_08 IdiomVersion[16]="Date:2019.03.08";

static INTE_64 ConstantInvalid64[4]={0x7FF0000000000000,0xFFF0000000000000,0x7FFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF};
static INTE_64 ConstantPi64[4]={0x400921FB54442D18,0x3FD45F306DC9C883,0x4005BF0A8B145769,0x3FD78B56362CEF38};
static INTE_32 ConstantInvalid32[4]={0x7F800000,0xFF800000,0x7FFFFFFF,0xFFFFFFFF};
static INTE_32 ConstantPi32[4]={0x40490FDB,0x3EA2F983,0x402DF854,0x3EBC5AB2};

static DATA_32 TableReform[8]={3,0,1,0,2,0,1,0};
static DATA_64 TableShrink64[8]={0x0000000000000001,0x0000000000000002,0x0000000000000004,0x0000000000000008,0x0000000000000010,0x0000000000000020,0x0000000000000040,0x0000000000000080};
static DATA_32 TableShrink32[8]={0x00000001,0x00000002,0x00000004,0x00000008,0x00000010,0x00000020,0x00000040,0x00000080};
static DATA_16 TableShrink16[8]={0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080};
static DATA_08 TableShrink08[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
static BOOLEAN TableBool[4]={!1,!0,BitCNull,BitCFull};
#ifdef __OPENCL_H
static INTE_08 TableSwitch[BitCKernels]={0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5,5,5,5};
#endif

#if(MemC_Fold_(Type Descriptors))
static INTE_08 IdiomTypeName[BitCTypes][8]=
{
	"data_08","data_16","data_32","data_64",
	"inte_08","inte_16","inte_32","inte_64",
	"real_08","real_16","real_32","real_64",
};
static MEMC_DT TableType[BitCTypes]=
{
	_BitC_DT_Define_(BitCTypeD08,data_08,_BitC_DT_Flag_Bits_(08)|_BitC_DT_Flag_Real_(0)|_BitC_DT_Flag_Sign_(0)),
	_BitC_DT_Define_(BitCTypeD16,data_16,_BitC_DT_Flag_Bits_(16)|_BitC_DT_Flag_Real_(0)|_BitC_DT_Flag_Sign_(0)),
	_BitC_DT_Define_(BitCTypeD32,data_32,_BitC_DT_Flag_Bits_(32)|_BitC_DT_Flag_Real_(0)|_BitC_DT_Flag_Sign_(0)),
	_BitC_DT_Define_(BitCTypeD64,data_64,_BitC_DT_Flag_Bits_(64)|_BitC_DT_Flag_Real_(0)|_BitC_DT_Flag_Sign_(0)),
	_BitC_DT_Define_(BitCTypeI08,inte_08,_BitC_DT_Flag_Bits_(08)|_BitC_DT_Flag_Real_(0)|_BitC_DT_Flag_Sign_(1)),
	_BitC_DT_Define_(BitCTypeI16,inte_16,_BitC_DT_Flag_Bits_(16)|_BitC_DT_Flag_Real_(0)|_BitC_DT_Flag_Sign_(1)),
	_BitC_DT_Define_(BitCTypeI32,inte_32,_BitC_DT_Flag_Bits_(32)|_BitC_DT_Flag_Real_(0)|_BitC_DT_Flag_Sign_(1)),
	_BitC_DT_Define_(BitCTypeI64,inte_64,_BitC_DT_Flag_Bits_(64)|_BitC_DT_Flag_Real_(0)|_BitC_DT_Flag_Sign_(1)),
	_BitC_DT_Define_(BitCTypeR08,data_08,_BitC_DT_Flag_Bits_(08)|_BitC_DT_Flag_Real_(1)|_BitC_DT_Flag_Sign_(1)),
	_BitC_DT_Define_(BitCTypeR16,data_16,_BitC_DT_Flag_Bits_(16)|_BitC_DT_Flag_Real_(1)|_BitC_DT_Flag_Sign_(1)),
	_BitC_DT_Define_(BitCTypeR32,real_32,_BitC_DT_Flag_Bits_(32)|_BitC_DT_Flag_Real_(1)|_BitC_DT_Flag_Sign_(1)),
	_BitC_DT_Define_(BitCTypeR64,real_64,_BitC_DT_Flag_Bits_(64)|_BitC_DT_Flag_Real_(1)|_BitC_DT_Flag_Sign_(1))
};
static MEMC_DT _PL_ AddressType[BitCTypes]=
{
	TableType+BitCTypeD08,TableType+BitCTypeD16,TableType+BitCTypeD32,TableType+BitCTypeD64,
	TableType+BitCTypeI08,TableType+BitCTypeI16,TableType+BitCTypeI32,TableType+BitCTypeI64,
	TableType+BitCTypeR08,TableType+BitCTypeR16,TableType+BitCTypeR32,TableType+BitCTypeR64
};
#endif

#ifdef __OPENCL_H
static NAME_08 IdiomFileName[40]="ouoclip.cl\0\0bitclip.cl\0\0bitclip.obj";
static NAME_08 IdiomKernelName[BitCKernels][24]=
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
	"BitC_BO_S_1_I08_",		"BitC_BO_S_1_I16_",		"BitC_BO_S_1_I32_",		"BitC_BO_S_1_I64_",
	"BitC_Expand_D08_",		"BitC_Expand_D16_",		"BitC_Expand_D32_",		"BitC_Expand_D64_",
	"BitC_Shrink_D08_",		"BitC_Shrink_D16_",		"BitC_Shrink_D32_",		"BitC_Shrink_D64_",
	"BitC_RO_E_1_D08_",		"BitC_RO_E_1_D16_",		"BitC_RO_E_1_D32_",		"BitC_RO_E_1_D64_",
	"BitC_RO_N_1_D08_",		"BitC_RO_N_1_D16_",		"BitC_RO_N_1_D32_",		"BitC_RO_N_1_D64_",
	"BitC_RO_G_1_D08_",		"BitC_RO_G_1_D16_",		"BitC_RO_G_1_D32_",		"BitC_RO_G_1_D64_",
	"BitC_RO_G_1_I08_",		"BitC_RO_G_1_I16_",		"BitC_RO_G_1_I32_",		"BitC_RO_G_1_I64_",
	"",						"BitC_RO_G_1_R16_",		"BitC_RO_G_1_R32_",		"BitC_RO_G_1_R64_",
	"BitC_RO_L_1_D08_",		"BitC_RO_L_1_D16_",		"BitC_RO_L_1_D32_",		"BitC_RO_L_1_D64_",
	"BitC_RO_L_1_I08_",		"BitC_RO_L_1_I16_",		"BitC_RO_L_1_I32_",		"BitC_RO_L_1_I64_",
	"",						"BitC_RO_L_1_R16_",		"BitC_RO_L_1_R32_",		"BitC_RO_L_1_R64_",
	"BitC_RO_E_2_D08_",		"BitC_RO_E_2_D16_",		"BitC_RO_E_2_D32_",		"BitC_RO_E_2_D64_",
	"BitC_RO_N_2_D08_",		"BitC_RO_N_2_D16_",		"BitC_RO_N_2_D32_",		"BitC_RO_N_2_D64_",
	"BitC_RO_G_2_D08_",		"BitC_RO_G_2_D16_",		"BitC_RO_G_2_D32_",		"BitC_RO_G_2_D64_",
	"BitC_RO_G_2_I08_",		"BitC_RO_G_2_I16_",		"BitC_RO_G_2_I32_",		"BitC_RO_G_2_I64_",
	"",						"BitC_RO_G_2_R16_",		"BitC_RO_G_2_R32_",		"BitC_RO_G_2_R64_",
	"BitC_RO_L_2_D08_",		"BitC_RO_L_2_D16_",		"BitC_RO_L_2_D32_",		"BitC_RO_L_2_D64_",
	"BitC_RO_L_2_I08_",		"BitC_RO_L_2_I16_",		"BitC_RO_L_2_I32_",		"BitC_RO_L_2_I64_",
	"",						"BitC_RO_L_2_R16_",		"BitC_RO_L_2_R32_",		"BitC_RO_L_2_R64_",
	"BitC_Reform_D08_",		"BitC_Reform_D16_",		"BitC_Reform_D32_",		"BitC_Reform_D64_"
};

static NAME_08 _PL_ AddressFileName[4]={IdiomFileName+0,IdiomFileName+12,IdiomFileName+24,NULL};
static NAME_08 _PL_ AddressKernelName[BitCKernels]=
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
	IdiomKernelName[168],IdiomKernelName[169],IdiomKernelName[170],IdiomKernelName[171],
	IdiomKernelName[172],IdiomKernelName[173],IdiomKernelName[174],IdiomKernelName[175],
	IdiomKernelName[176],IdiomKernelName[177],IdiomKernelName[178],IdiomKernelName[179],
	IdiomKernelName[180],IdiomKernelName[181],IdiomKernelName[182],IdiomKernelName[183],
	IdiomKernelName[184],IdiomKernelName[185],IdiomKernelName[186],IdiomKernelName[187],
	IdiomKernelName[188],IdiomKernelName[189],IdiomKernelName[190],IdiomKernelName[191],
	IdiomKernelName[192],IdiomKernelName[193],IdiomKernelName[194],IdiomKernelName[195],
	IdiomKernelName[196],IdiomKernelName[197],IdiomKernelName[198],IdiomKernelName[199],
	IdiomKernelName[200],IdiomKernelName[201],IdiomKernelName[202],IdiomKernelName[203],
	IdiomKernelName[204],IdiomKernelName[205],IdiomKernelName[206],IdiomKernelName[207],
	IdiomKernelName[208],IdiomKernelName[209],IdiomKernelName[210],IdiomKernelName[211],
	IdiomKernelName[212],IdiomKernelName[213],IdiomKernelName[214],IdiomKernelName[215],
	IdiomKernelName[216],IdiomKernelName[217],IdiomKernelName[218],IdiomKernelName[219],
	IdiomKernelName[220],IdiomKernelName[221],IdiomKernelName[222],IdiomKernelName[223],
	IdiomKernelName[224],IdiomKernelName[225],IdiomKernelName[226],IdiomKernelName[227],
	IdiomKernelName[228],IdiomKernelName[229],IdiomKernelName[230],IdiomKernelName[231],
	IdiomKernelName[232],IdiomKernelName[233],IdiomKernelName[234],IdiomKernelName[235],
	IdiomKernelName[236],IdiomKernelName[237],IdiomKernelName[238],IdiomKernelName[239],
	IdiomKernelName[240],IdiomKernelName[241],IdiomKernelName[242],IdiomKernelName[243],
	IdiomKernelName[244],IdiomKernelName[245],IdiomKernelName[246],IdiomKernelName[247]
};
#endif
static ADDRESS ConstantUnique=1;

DATA_08 _PL_ BitClip=IdiomVersion;
DATA_08 _PL_ BitCEndian=(data_08*)&ConstantUnique;
REAL_32 _PL_ BitCInvalid32=(real_32*)ConstantInvalid32;
REAL_64 _PL_ BitCInvalid64=(real_64*)ConstantInvalid64;
REAL_32 _PL_ BitCPi32=(real_32*)ConstantPi32;
REAL_64 _PL_ BitCPi64=(real_64*)ConstantPi64;
BOOLEAN _PL_ BitCBool=TableBool+2;
MEMC_DT _PL_ _PL_ BitCType=AddressType;
#ifdef __OPENCL_H
NAME_08 _PL_ _PL_ BitCFile=AddressFileName;
NAME_08 _PL_ _PL_ BitCKernel=AddressKernelName;
#endif
#endif

#if(MemC_Fold_(Definition:Endian Functions))
general BitC_Endian_D16_(data_16 _PL_ Data,DATA_32 Length)
{
	DATA_08 *End=(data_08*)(Data+(Length&0xFFFFFFFC));
	data_08 *_R_ Ptr=(data_08*)Data;
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
	data_08 *_R_ Ptr=(data_08*)Data;
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
	data_08 *_R_ Ptr=(data_08*)Data;
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
#define _BitC_Caster_

#if(MemC_Fold_(Part:BitC_Caster_D08_))
#define S D
#define OO 08
#define T D
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#define T I
#define XX 08
#include "bitcrux.c"
#undef XX
#undef T
#define T R
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#undef OO
#undef S
#endif

#if(MemC_Fold_(Part:BitC_Caster_D16_))
#define S D
#define OO 16
#define T D
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#define T I
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#undef T
#define T R
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#undef OO
#undef S
#endif

#if(MemC_Fold_(Part:BitC_Caster_D32_))
#define S D
#define OO 32
#define T D
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#define T I
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#undef T
#define T R
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#undef OO
#undef S
#endif

#if(MemC_Fold_(Part:BitC_Caster_D64_))
#define S D
#define OO 64
#define T D
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#undef T
#define T I
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#define T R
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#undef OO
#undef S
#endif

#if(MemC_Fold_(Part:BitC_Caster_I08_))
#define S I
#define OO 08
#define T D
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#define T I
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#define T R
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#undef OO
#undef S
#endif

#if(MemC_Fold_(Part:BitC_Caster_I16_))
#define S I
#define OO 16
#define T D
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#define T I
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#define T R
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#undef OO
#undef S
#endif

#if(MemC_Fold_(Part:BitC_Caster_I32_))
#define S I
#define OO 32
#define T D
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#define T I
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#define T R
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#undef OO
#undef S
#endif

#if(MemC_Fold_(Part:BitC_Caster_I64_))
#define S I
#define OO 64
#define T D
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#define T I
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#undef T
#define T R
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#undef OO
#undef S
#endif

#if(MemC_Fold_(Part:BitC_Caster_R32_))
#define S R
#define OO 32
#define T D
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#define T I
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#define T R
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#undef OO
#undef S
#endif

#if(MemC_Fold_(Part:BitC_Caster_R64_))
#define S R
#define OO 64
#define T D
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#define T I
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#define T R
#define XX 32
#include "bitcrux.c"
#undef XX
#undef T
#undef OO
#undef S
#endif

#undef _BitC_Caster_
#endif

#if(MemC_Fold_(Definition:Bit Operation Functions))
__inline static data_64 _BitC_Wide_Mask_D08_(DATA_08 Mask)
{
	data_64 Wide=(data_64)Mask;

	Wide|=(Wide<<8);
	Wide|=(Wide<<16);
	Wide|=(Wide<<32);

	return Wide;
}
__inline static data_64 _BitC_Wide_Mask_D16_(DATA_16 Mask)
{
	data_64 Wide=(data_64)Mask;

	Wide|=(Wide<<16);
	Wide|=(Wide<<32);

	return Wide;
}
__inline static data_64 _BitC_Wide_Mask_D32_(DATA_32 Mask)
{
	data_64 Wide=(data_64)Mask;

	Wide|=(Wide<<32);

	return Wide;
}
__inline static data_64 _BitC_Wide_Mask_D64_(DATA_64 Mask)
{
	return Mask;
}

#if(MemC_Fold_(Part:BitC_BO_N_1_))
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
#endif

#if(MemC_Fold_(Part:BitC_BO_S_1_))
#define BitC_Op_ BitC_BO_S_
#define _BitC_BO_S_1_
#define T D
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#define T I
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#undef _BitC_BO_S_1_
#undef BitC_Op_
#endif

#if(MemC_Fold_(Part:BitC_BO_A_))
#define BitC_Op_ BitC_BO_A_
#define _BitC_BO_Op_1_
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef _BitC_BO_Op_1_
#define _BitC_BO_Op_2_
#include "bitcrux.c"
#undef _BitC_BO_Op_2_
#undef BitC_Op_
#endif

#if(MemC_Fold_(Part:BitC_BO_O_))
#define BitC_Op_ BitC_BO_O_
#define _BitC_BO_Op_1_
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef _BitC_BO_Op_1_
#define _BitC_BO_Op_2_
#include "bitcrux.c"
#undef _BitC_BO_Op_2_
#undef BitC_Op_
#endif

#if(MemC_Fold_(Part:BitC_BO_X_))
#define BitC_Op_ BitC_BO_X_
#define _BitC_BO_Op_1_
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef _BitC_BO_Op_1_
#define _BitC_BO_Op_2_
#include "bitcrux.c"
#undef _BitC_BO_Op_2_
#undef BitC_Op_
#endif
#endif

#if(MemC_Fold_(Definition:Relational Operation Functions))
__inline static data_08 _BitC_RO_Loop_A_(bitclip M)
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

	return M.C.D08[0];
}
__inline static general _BitC_RO_Loop_B_(bitclip M,DATA_32 R)
{
	M.V.D32[0]|=M.C.D32[1];
	M.V.D16[0]|=M.C.D16[1];
	M.V.D08[0]|=M.C.D08[1];

	M.V.D08[1]=0xFF;
	M.V.D08[1]<<=R;
}

#if(MemC_Fold_(Part:BitC_Expand_))
#define _BitC_Expand_
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef _BitC_Expand_
#endif

#if(MemC_Fold_(Part:BitC_Shrink_))
general BitC_Shrink_D08_(DATA_08 *_R_ DataI,data_08 *_R_ DataO,DATA_32 Length)
{
	DATA_08 _PL_ Table=TableShrink08;
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_64 _PL_ Peek=(data_64*)Table;
		DATA_08 _PL_ End=DataI+Safe;

		for(;DataI<End;DataI+=8,DataO++)
		{
			Mask.V.D64[0]=(((data_64*)DataI)[0])&(Peek[0]);
			Mask.V.D32[0]|=Mask.C.D32[1];
			Mask.V.D16[0]|=Mask.C.D16[1];
			Mask.V.D08[0]|=Mask.C.D08[1];

			DataO[0]=Mask.C.D08[0];
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
			Mask.V.D08[Index]=DataI[Index]&Table[Index];
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataO[0]&=Mask.C.D08[1];
			DataO[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_Shrink_D16_(DATA_16 *_R_ DataI,data_08 *_R_ DataO,DATA_32 Length)
{
	DATA_16 _PL_ Table=TableShrink16;
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer[2];
	bitclip Mask;

	Mask.C.D64=Buffer;
	{
		DATA_64 _PL_ Peek=(data_64*)Table;
		DATA_16 _PL_ End=DataI+Safe;

		for(;DataI<End;DataI+=8,DataO++)
		{
			Mask.V.D64[0]=(((data_64*)DataI)[0])&(Peek[0]);
			Mask.V.D64[1]=(((data_64*)DataI)[1])&(Peek[1]);
			Mask.V.D64[0]|=Mask.C.D64[1];
			Mask.V.D32[0]|=Mask.C.D32[1];
			Mask.V.D16[0]|=Mask.C.D16[1];
			Mask.V.D08[0]|=Mask.C.D08[1];

			DataO[0]=Mask.C.D08[0];
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
			Mask.V.D16[Index]=DataI[Index]&Table[Index];
		{
			Mask.V.D64[0]|=Mask.C.D64[1];
			_BitC_RO_Loop_B_(Mask,Rest);

			DataO[0]&=Mask.C.D08[1];
			DataO[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_Shrink_D32_(DATA_32 *_R_ DataI,data_08 *_R_ DataO,DATA_32 Length)
{
	DATA_32 _PL_ Table=TableShrink32;
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer[4];
	bitclip Mask;

	Mask.C.D64=Buffer;
	{
		DATA_64 _PL_ Peek=(data_64*)Table;
		DATA_32 _PL_ End=DataI+Safe;

		for(;DataI<End;DataI+=8,DataO++)
		{
			Mask.V.D64[0]=(((data_64*)DataI)[0])&(Peek[0]);
			Mask.V.D64[1]=(((data_64*)DataI)[1])&(Peek[1]);
			Mask.V.D64[2]=(((data_64*)DataI)[2])&(Peek[2]);
			Mask.V.D64[3]=(((data_64*)DataI)[3])&(Peek[3]);
			Mask.V.D64[0]|=Mask.C.D64[2];
			Mask.V.D64[1]|=Mask.C.D64[3];
			Mask.V.D64[0]|=Mask.C.D64[1];
			Mask.V.D32[0]|=Mask.C.D32[1];
			Mask.V.D16[0]|=Mask.C.D16[1];
			Mask.V.D08[0]|=Mask.C.D08[1];

			DataO[0]=Mask.C.D08[0];
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
			Mask.V.D32[Index]=DataI[Index]&Table[Index];
		{
			Mask.V.D64[0]|=Mask.C.D64[2];
			Mask.V.D64[1]|=Mask.C.D64[3];
			Mask.V.D64[0]|=Mask.C.D64[1];
			_BitC_RO_Loop_B_(Mask,Rest);

			DataO[0]&=Mask.C.D08[1];
			DataO[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_Shrink_D64_(DATA_64 *_R_ DataI,data_08 *_R_ DataO,DATA_32 Length)
{
	DATA_64 _PL_ Table=TableShrink64;
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer[8];
	bitclip Mask;

	Mask.C.D64=Buffer;
	{
		DATA_64 _PL_ End=DataI+Safe;

		for(;DataI<End;DataI+=8,DataO++)
		{
			Mask.V.D64[0]=(DataI[0])&(Table[0]);
			Mask.V.D64[1]=(DataI[1])&(Table[1]);
			Mask.V.D64[2]=(DataI[2])&(Table[2]);
			Mask.V.D64[3]=(DataI[3])&(Table[3]);
			Mask.V.D64[4]=(DataI[0])&(Table[0]);
			Mask.V.D64[5]=(DataI[1])&(Table[1]);
			Mask.V.D64[6]=(DataI[2])&(Table[2]);
			Mask.V.D64[7]=(DataI[3])&(Table[3]);
			Mask.V.D64[0]|=Mask.C.D64[4];
			Mask.V.D64[1]|=Mask.C.D64[5];
			Mask.V.D64[2]|=Mask.C.D64[6];
			Mask.V.D64[3]|=Mask.C.D64[7];
			Mask.V.D64[0]|=Mask.C.D64[2];
			Mask.V.D64[1]|=Mask.C.D64[3];
			Mask.V.D64[0]|=Mask.C.D64[1];
			Mask.V.D32[0]|=Mask.C.D32[1];
			Mask.V.D16[0]|=Mask.C.D16[1];
			Mask.V.D08[0]|=Mask.C.D08[1];

			DataO[0]=Mask.C.D08[0];
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
			Mask.V.D64[Index]=DataI[Index]&Table[Index];
		{
			Mask.V.D64[0]|=Mask.C.D64[4];
			Mask.V.D64[1]|=Mask.C.D64[5];
			Mask.V.D64[2]|=Mask.C.D64[6];
			Mask.V.D64[3]|=Mask.C.D64[7];
			Mask.V.D64[0]|=Mask.C.D64[2];
			Mask.V.D64[1]|=Mask.C.D64[3];
			Mask.V.D64[0]|=Mask.C.D64[1];
			_BitC_RO_Loop_B_(Mask,Rest);

			DataO[0]&=Mask.C.D08[1];
			DataO[0]|=Mask.C.D08[0];
		}
	}
}
#endif

#if(MemC_Fold_(Part:BitC_RO_E_))
#define _BitC_RO_Op_
#define BitC_Op_ BitC_RO_E_
#define T D
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#undef BitC_Op_
#undef _BitC_RO_Op_
#endif

#if(MemC_Fold_(Part:BitC_RO_N_))
#define _BitC_RO_Op_
#define BitC_Op_ BitC_RO_N_
#define T D
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#undef BitC_Op_
#undef _BitC_RO_Op_
#endif

#if(MemC_Fold_(Part:BitC_RO_G_))
#define _BitC_RO_Op_
#define BitC_Op_ BitC_RO_G_
#define T D
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#define T I
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#define T R
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#undef BitC_Op_
#undef _BitC_RO_Op_
#endif

#if(MemC_Fold_(Part:BitC_RO_L_))
#define _BitC_RO_Op_
#define BitC_Op_ BitC_RO_L_
#define T D
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#define T I
#define XX 08
#include "bitcrux.c"
#undef XX
#define XX 16
#include "bitcrux.c"
#undef XX
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#define T R
#define XX 32
#include "bitcrux.c"
#undef XX
#define XX 64
#include "bitcrux.c"
#undef XX
#undef T
#undef BitC_Op_
#undef _BitC_RO_Op_
#endif
#endif

#if(MemC_Fold_(Definition:Reformation Functions))
static boolean _BitC_Reform_Valid_(DATA_32 *_R_ Map,DATA_32 Dims)
{
	boolean Table[MemC_Copy_Max_Dimension]={BitCNull};
	boolean Flag;
	data_32 Idx;

	for(Idx=0;Idx<Dims;Idx++)
		if(Map[Idx]<Dims)
			Table[Map[Idx]]=BitCFull;
		else
		{
			Flag=BitCNull;
			goto ESCAPE;
		}
	for(Idx=0,Flag=BitCFull;Idx<Dims;Idx++)
		Flag&=Table[Idx];
ESCAPE:
	return Flag;
}
static general _BitC_Reform_Short_(DATA_32 _PL_ Shape,DATA_32 _PL_ Map,data_32 _PL_ Dims,data_32 _PL_ Bytes)
{
	data_32 Temp;

	for(Temp=(*Dims)-1;Temp;Temp--)
		if(Map[Temp]==Temp)
		{
			(*Bytes)*=Shape[Temp];
			(*Dims)=Temp;
		}
		else
			break;
}
static general _BitC_Reform_Merge_(data_32 _PL_ Shape,data_32 _PL_ Map,data_32 _PL_ Dims)
{
	DATA_32 *End=Map+(*Dims);
	DATA_32 *Last=End-1;
	data_32 *MapA;
	data_32 *MapB;
	data_32 *MapC;
	data_32 *ShpA;
	data_32 *ShpB;
	data_32 *ShpC;
	data_32 Pull;

	for(MapA=Map,ShpA=Shape;MapA<Last;MapA++,ShpA++)
	{
		for(MapB=MapA,ShpB=ShpA;MapB<Last;MapB++,ShpB++)
			if((MapB[0]+1)==MapB[1])
				ShpA[0]*=ShpB[1];
			else
				break;

		if(MapA<MapB)
		{
			for(MapC=Map,Pull=(data_32)(MapB-MapA);MapC<MapA;MapC++)
				if(MapC[0]>MapA[0])
					MapC[0]-=Pull;

			for(MapB++,MapC++,ShpB++,ShpC=ShpA+1;MapB<End;MapB++,MapC++,ShpB++,ShpC++)
			{
				MapC[0]=(MapA[0]<MapB[0])?(MapB[0]-Pull):(MapB[0]);
				ShpC[0]=ShpB[0];
			}

			End=MapC;
			Last=End-1;
			*Dims=(data_32)(End-Map);
		}
	}
}
static data_32 _BitC_Reform_Total_(DATA_32 *_R_ Shape,DATA_32 Dims)
{
	DATA_32 _PL_ End=Shape+Dims;
	data_32 Total;

	for(Total=1;Shape<End;Shape++)
		Total*=*Shape;

	return Total;
}
static general _BitC_Reform_Order_(BITCLIP Source,BITCLIP Target,DATA_32 _PL_ Shape,DATA_32 _PL_ Map,DATA_32 Total,DATA_32 Dims,DATA_32 Bytes)
{
	DATA_32 Switch=Bytes&0x00000007;
	DATA_32 Loop=Bytes>>TableReform[Switch];
	DATA_32 Last=Dims-1;
	data_32 Jump[MemC_Copy_Max_Dimension];
	data_32 Prod;
	data_32 IdxS;
	data_32 IdxT;
	data_32 IdxJ;

	switch(Switch)
	{
	default:
		for(IdxT=0;IdxT<Total;IdxT++)
		{
			for(IdxJ=Last,Prod=IdxT/Shape[Map[Last]],Jump[Map[Last]]=IdxT%Shape[Map[Last]];IdxJ;Prod/=Shape[Map[IdxJ]])
			{
				IdxJ--;
				Jump[Map[IdxJ]]=Prod%Shape[Map[IdxJ]];
			}
			for(IdxJ=Last,IdxS=Jump[Last],Prod=Shape[Last];IdxJ;Prod*=Shape[IdxJ])
			{
				IdxJ--;
				IdxS+=Prod*Jump[IdxJ];
			}
			IdxS*=Loop;
			for(Prod=IdxS+Loop,IdxJ=IdxT*Loop;IdxS<Prod;IdxS++,IdxJ++)
				Target.V.D08[IdxJ]=Source.C.D08[IdxS];
		}
		break;
	case 2:case 6:
		for(IdxT=0;IdxT<Total;IdxT++)
		{
			for(IdxJ=Last,Prod=IdxT/Shape[Map[Last]],Jump[Map[Last]]=IdxT%Shape[Map[Last]];IdxJ;Prod/=Shape[Map[IdxJ]])
			{
				IdxJ--;
				Jump[Map[IdxJ]]=Prod%Shape[Map[IdxJ]];
			}
			for(IdxJ=Last,IdxS=Jump[Last],Prod=Shape[Last];IdxJ;Prod*=Shape[IdxJ])
			{
				IdxJ--;
				IdxS+=Prod*Jump[IdxJ];
			}
			IdxS*=Loop;
			for(Prod=IdxS+Loop,IdxJ=IdxT*Loop;IdxS<Prod;IdxS++,IdxJ++)
				Target.V.D16[IdxJ]=Source.C.D16[IdxS];
		}
		break;
	case 4:
		for(IdxT=0;IdxT<Total;IdxT++)
		{
			for(IdxJ=Last,Prod=IdxT/Shape[Map[Last]],Jump[Map[Last]]=IdxT%Shape[Map[Last]];IdxJ;Prod/=Shape[Map[IdxJ]])
			{
				IdxJ--;
				Jump[Map[IdxJ]]=Prod%Shape[Map[IdxJ]];
			}
			for(IdxJ=Last,IdxS=Jump[Last],Prod=Shape[Last];IdxJ;Prod*=Shape[IdxJ])
			{
				IdxJ--;
				IdxS+=Prod*Jump[IdxJ];
			}
			IdxS*=Loop;
			for(Prod=IdxS+Loop,IdxJ=IdxT*Loop;IdxS<Prod;IdxS++,IdxJ++)
				Target.V.D32[IdxJ]=Source.C.D32[IdxS];
		}
		break;
	case 0:
		for(IdxT=0;IdxT<Total;IdxT++)
		{
			for(IdxJ=Last,Prod=IdxT/Shape[Map[Last]],Jump[Map[Last]]=IdxT%Shape[Map[Last]];IdxJ;Prod/=Shape[Map[IdxJ]])
			{
				IdxJ--;
				Jump[Map[IdxJ]]=Prod%Shape[Map[IdxJ]];
			}
			for(IdxJ=Last,IdxS=Jump[Last],Prod=Shape[Last];IdxJ;Prod*=Shape[IdxJ])
			{
				IdxJ--;
				IdxS+=Prod*Jump[IdxJ];
			}
			IdxS*=Loop;
			for(Prod=IdxS+Loop,IdxJ=IdxT*Loop;IdxS<Prod;IdxS++,IdxJ++)
				Target.V.D64[IdxJ]=Source.C.D64[IdxS];
		}
	}
}
boolean _BitC_Reform_(GENERAL _PL_ ArrayS,general _PL_ ArrayT,DATA_32 _PL_ ShapeS,DATA_32 _PL_ AxisStoT,data_32 Dimensions,data_32 Bytes)
{
	if(Dimensions)
	{
		_BitC_Reform_Short_(ShapeS,AxisStoT,&Dimensions,&Bytes);
		if(Dimensions>1)
			if(Dimensions<MemC_Copy_Max_Dimension)
				if(_BitC_Reform_Valid_(AxisStoT,Dimensions))
				{
					data_32 Total=_BitC_Reform_Total_(ShapeS,Dimensions);

					if(Total)
					{
						data_32 ShapeSNew[MemC_Copy_Max_Dimension];
						data_32 MapTNew[MemC_Copy_Max_Dimension];

						if(MemC_Copy_1D_(ShapeS,ShapeSNew,Dimensions)!=MemC_Errno_0)
							goto FAILURE;

						if(MemC_Copy_1D_(AxisStoT,MapTNew,Dimensions)!=MemC_Errno_0)
							goto FAILURE;

						_BitC_Reform_Merge_(ShapeSNew,MapTNew,&Dimensions);
						_BitC_Reform_Order_(Acs_(bitclip,ArrayS),Acs_(bitclip,ArrayT),ShapeSNew,MapTNew,Total,Dimensions,Bytes);

						goto SUCCESS;
					}
					else
						goto SUCCESS;
				}
				else
					goto FAILURE;
			else
				goto FAILURE;
		else
			if(AxisStoT[0])
				goto FAILURE;
			else
			{
				const size_t Copy=ShapeS[0]*Bytes;

				if(Copy)
					if(MemC_Copy_Byte_(ArrayS,ArrayT,Copy)==MemC_Errno_0)
						goto SUCCESS;
					else
						goto FAILURE;
				else
					goto SUCCESS;
			}
	}
	else
		goto SUCCESS;
FAILURE:
	return BitCNull;
SUCCESS:
	return BitCFull;
}
#endif

#if(MemC_Fold_(Definition:Boolean Pointer Functions))
bitc_bp BitC_BP_Assign_(general _PL_ Base,SINTPTR Offset)
{
	bitc_bp BP;

	BP.Base=Base;
	BP.Base+=Offset>>3;
	BP.Offset=Offset&7;

	return BP;
}
#endif

#if(MemC_Fold_(Definition:BitClip Managed Functions))
#ifdef __OPENCL_H
static NAME_08 *_BitC_Path_(name_08 _PL_ Buffer,NAME_08 _PL_ Prefix,NAME_08 _PL_ Name,ADDRESS Capacity)
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
penc_eu BitC_CL_Binary_(cl_command_queue const Queue,NAME_08 _PL_ DirSrc,NAME_08 _PL_ DirBin,NAME_08 _PL_ Option,FILE _PL_ Stream)
{
	ADDRESS Length=1024;
	name_08 _PL_ _PL_ Buffer=MemC_Alloc_2D_(3,Length,name_08);
	penc_eu Error;

	if(Buffer)
	{
		NAME_08 *Name[3];

		Name[0]=_BitC_Path_(Buffer[0],DirSrc,BitCFile[0],Length);
		Name[1]=_BitC_Path_(Buffer[1],DirSrc,BitCFile[1],Length);
		Name[2]=_BitC_Path_(Buffer[2],DirBin,BitCFile[2],Length);
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

static devi_km *_BitC_Create_KM_Endian_(cl_kernel const Kernel,GENERAL _PL_ ID)
{
	devi_km *KM=Devi_KM_Create_(ID,2,1);
	
	if(KM)
	{
		penc_eu Error={.E=CLSuccess};

		Error.I|=Devi_KM_Type_G_(KM,0);
		Error.I|=Devi_KM_Type_P_(KM,1,data_32);
		Error.I|=Devi_KM_Init_(KM,Kernel);
		if(Error.E!=CLSuccess)
			Devi_KM_Delete_(&KM);
	}

	return KM;
}
static devi_km *_BitC_Create_KM_Caster_(cl_kernel const Kernel,GENERAL _PL_ ID)
{
	devi_km *KM=Devi_KM_Create_(ID,3,1);

	if(KM)
	{
		penc_eu Error={.E=CLSuccess};

		Error.I|=Devi_KM_Type_G_(KM,0);
		Error.I|=Devi_KM_Type_G_(KM,1);
		Error.I|=Devi_KM_Type_P_(KM,2,data_32);
		Error.I|=Devi_KM_Init_(KM,Kernel);
		if(Error.E!=CLSuccess)
			Devi_KM_Delete_(&KM);
	}

	return KM;
}
static devi_km *_BitC_Create_KM_Op_(cl_kernel const Kernel,GENERAL _PL_ ID,ADDRESS TypeSize)
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
static devi_km *_BitC_Create_KM_Reform_(cl_kernel const Kernel,GENERAL _PL_ ID)
{
	devi_km *KM=Devi_KM_Create_(ID,3,1);

	if(KM)
	{
		penc_eu Error={.E=CLSuccess};

		Error.I|=Devi_KM_Type_G_(KM,0);
		Error.I|=Devi_KM_Type_G_(KM,1);
		Error.I|=Devi_KM_Type_C_(KM,2);
		Error.I|=Devi_KM_Init_(KM,Kernel);
		if(Error.E!=CLSuccess)
			Devi_KM_Delete_(&KM);
	}

	return KM;
}
static devi_km *_BitC_Create_KM_(cl_kernel const Kernel,BITC_KI Switch)
{
	devi_km *KM;

	switch(TableSwitch[Switch])
	{
	case 0:
		KM=_BitC_Create_KM_Endian_(Kernel,BitCKernel[Switch]);
		break;
	case 1:
		KM=_BitC_Create_KM_Caster_(Kernel,BitCKernel[Switch]);
		break;
	case 2:
		KM=_BitC_Create_KM_Op_(Kernel,BitCKernel[Switch],sizeof(cl_mem));
		break;
	case 3:
		KM=_BitC_Create_KM_Op_(Kernel,BitCKernel[Switch],(address)(1<<(Switch&3)));
		break;
	case 4:
		KM=_BitC_Create_KM_Op_(Kernel,BitCKernel[Switch],sizeof(inte_32));
		break;
	case 5:
		KM=_BitC_Create_KM_Reform_(Kernel,BitCKernel[Switch]);
		break;
	default:
		KM=NULL;
	}

	return KM;
}

bitc_cl *BitC_CL_Create_(general)
{
	bitc_cl *Manager=MemC_Alloc_Byte_(sizeof(bitc_cl)+MemC_Size_(devi_km*,BitCKernels));

	if(Manager)
	{
		Acs_(GENERAL*,Manager->Helper)=NULL;
		Acs_(devi_km**,Manager->KMSet)=MemC_Clear_1D_((devi_km**)(Manager+1),BitCKernels);
	}

	return Manager;
}
address *BitC_CL_Choice_(BITC_CL _PL_ Manager)
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
penc_eu BitC_CL_Launch_(cl_command_queue const Queue,BITC_CL _PL_ Manager,NAME_08 _PL_ DirBin,NAME_08 _PL_ Option,FILE _PL_ Stream)
{
	penc_eu Error;

	if(Manager)
		if(Manager->Helper)
			Error.E=CLInvalidHostPtr;
		else
		{
			GENERAL *Slot[BitCKernels];
			bitc_ki Link[BitCKernels];
			cl_uint Count=0;

			{
				bitc_ki Index;

				for(Index=0;Index<BitCKernels;Index++)
					if(Manager->KMSet[Index])
					{
						Slot[Count]=BitCKernel[Index];
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
					NAME_08 *Name=_BitC_Path_(Buffer,DirBin,BitCFile[2],Length);

					if(Name)
					{
						penc_cl *Helper=PenC_CL_Create_(Queue,Name,(name_08**)Slot,Option,Count,&Error,Stream);

						if(Helper)
						{
							cl_uint Index=0;

							while(Index<Count)
							{
								Slot[Index]=_BitC_Create_KM_(Helper->SetKernel[Index],Link[Index]);
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
general BitC_CL_Delete_(bitc_cl *_PL_ Manager)
{
	if(*Manager)
	{
		if((*Manager)->Helper)
		{
			devi_km **Ptr=(devi_km**)((*Manager)->KMSet+BitCKernels);

			for(Ptr--;Ptr>=(*Manager)->KMSet;Ptr--)
				Devi_KM_Delete_(Ptr);
			PenC_CL_Delete_((penc_cl**)&((*Manager)->Helper));
		}
		MemC_Deloc_(*Manager);
	}
}

static penc_eu _BitC_Worker_KM_Default_(PENC_CL _PL_ Helper,DEVI_KM _PL_ KM,ADDRESS _PL_ Token)
{
	penc_eu Error={.E=CLSuccess};
	address Index;

	for(Index=0;Index<KM->KArgs;Index++)
		Error.I|=Devi_KM_Save_(KM,Index,Token[Index]);

	if(Error.E==CLSuccess)
	{
		KM->WGroups[0]=Helper->Cores;
		KM->WLocals[0]=Helper->SizeWorker[0];
	}

	return Error;
}
static penc_eu _BitC_Worker_KM_Reform_(PENC_CL _PL_ Helper,DEVI_KM _PL_ KM,ADDRESS _PL_ Token)
{
	data_32 ParamHost[2+(Devi_Copy_Max_Dimension<<1)];
	cl_mem const ArrayS=*((cl_mem*)(Token[0]));
	cl_mem const ArrayT=*((cl_mem*)(Token[1]));
	cl_mem const ParamDevice=*((cl_mem*)(Token[2]));
	DATA_32 _PL_ ShapeS=*((data_32**)(Token[3]));
	DATA_32 _PL_ AxisStoT=*((data_32**)(Token[4]));
	data_32 Dimensions=*((data_32*)(Token[5]));
	penc_eu Error;

	ParamHost[0]=Dimensions;
	ParamHost[1]=_BitC_Reform_Total_(ShapeS,Dimensions);
	if(MemC_Copy_1D_(ShapeS,ParamHost+2,Dimensions)==MemC_Errno_0)
		if(MemC_Copy_1D_(AxisStoT,ParamHost+(2+Devi_Copy_Max_Dimension),Dimensions)==MemC_Errno_0)
		{
			Error.I=Devi_Copy_1D_(Helper->Queue,ParamHost,ParamDevice,0,0,2+(Devi_Copy_Max_Dimension<<1),data_32,DeviCopyHtoD);
			Error.I|=Devi_KM_Save_(KM,0,(address)(&ArrayS));
			Error.I|=Devi_KM_Save_(KM,1,(address)(&ArrayT));
			Error.I|=Devi_KM_Save_(KM,2,(address)(&ParamDevice));
			if(Error.E==CLSuccess)
			{
				KM->WGroups[0]=Helper->Cores;
				KM->WLocals[0]=Helper->SizeWorker[0];
			}
		}
		else
			Error.E=CLInvalidArgValue;
	else
		Error.E=CLInvalidArgValue;

	return Error;
}
static penc_eu _BitC_Worker_KM_(PENC_CL _PL_ Helper,DEVI_KM _PL_ KM,ADDRESS _PL_ Token,BITC_KI Switch)
{
	penc_eu Error;

	switch(TableSwitch[Switch])
	{
	case 5:
		Error=_BitC_Worker_KM_Reform_(Helper,KM,Token);
		break;
	default:
		Error=_BitC_Worker_KM_Default_(Helper,KM,Token);
	}

	return Error;
}
penc_eu BitC_CL_Action_(BITC_CL _PL_ Manager,MEMC_MS _PL_ Argument,BITC_KI Indicator)
{
	penc_eu Error;

	if(Manager)
		if(Argument)
			if(Manager->Helper)
				if(Indicator<0)
					Error.E=CLInvalidKernelName;
				else
					if(Indicator<BitCKernels)
						if(Manager->KMSet[Indicator])
							if((Argument->Nums)<((address)(Manager->KMSet[Indicator]->KArgs)))
								Error.E=CLInvalidKernelArgs;
							else
							{
								Error=_BitC_Worker_KM_(Manager->Helper,Manager->KMSet[Indicator],Argument->Slot.V,Indicator);
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

#if(MemC_Fold_(Undefinition:BitCrux Macros))
#undef BitC_RO_L_
#undef BitC_RO_G_
#undef BitC_RO_N_
#undef BitC_RO_E_
#undef BitC_BO_X_
#undef BitC_BO_O_
#undef BitC_BO_A_
#undef BitC_Wide_
#undef _BitC_Wide_
#undef BitC_Oper_
#undef _BitC_Oper_
#undef BitC_Cast_
#undef _BitC_Cast_
#undef BitC_Func_
#undef _BitC_Func_
#undef BitC_Type_
#undef _BitC_Type_
#undef BitC_TXX_
#undef _BitC_TXX_
#undef BitC_XX_
#endif

#if(MemC_Fold_(Undefinition:BitClip Macros))
#undef _BitC_DT_Flag_Bits_64_
#undef _BitC_DT_Flag_Bits_32_
#undef _BitC_DT_Flag_Bits_16_
#undef _BitC_DT_Flag_Bits_08_
#undef _BitC_DT_Flag_Bits_
#undef _BitC_DT_Flag_Sign_
#undef _BitC_DT_Flag_Real_
#undef _BitC_DT_Define_
#undef _BitC_Clamp_
#undef _BitC_Max_
#undef _BitC_Min_
#endif
