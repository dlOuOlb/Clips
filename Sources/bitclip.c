#include "bitclip.h"

#if(MemC_Fold_(Definition:Macros))
#define _BitC_Min_(A,B) (((A)<(B))?(A):(B))
#define _BitC_Max_(A,B) (((A)>(B))?(A):(B))
#define _BitC_Clamp_(Data,Min,Max) (((Data)<(Min))?(Min):(((Data)>(Max))?(Max):(Data)))

#define _BitC_Total_Types 12
#define _BitC_Type_Name_Length 8
#ifdef __OPENCL_H
#define _BitC_Total_Files 2
#define _BitC_File_Name_Length 16

#define _BitC_Total_Kernels 244
#define _BitC_Kernel_Name_Length 24
#endif
#define _BitC_DT_Define_(IType,type,IFlag) MemC_DT_Define_(IdiomVersion,IType,IdiomTypeName[IType],IFlag,NULL,NULL,type)
#define _BitC_DT_Flag_Sign_(Bool) ((Bool)<<2)
#define _BitC_DT_Flag_Real_(Bool) ((Bool)<<3)
#define _BitC_DT_Flag_Bits_(Bits) _BitC_DT_Flag_Bits_##Bits##_
#define _BitC_DT_Flag_Bits_08_ (0)
#define _BitC_DT_Flag_Bits_16_ (1)
#define _BitC_DT_Flag_Bits_32_ (2)
#define _BitC_DT_Flag_Bits_64_ (3)
#endif

#if(MemC_Fold_(Definition:Global Constants))
static DATA_08 IdiomVersion[16]="Date:2018.06.26";

static INTE_64 ConstantInvalid64[4]={0x7FF0000000000000,0xFFF0000000000000,0x7FFFFFFFFFFFFFFF,0xFFFFFFFFFFFFFFFF};
static INTE_64 ConstantPi64[4]={0x400921FB54442D18,0x3FD45F306DC9C883,0x4005BF0A8B145769,0x3FD78B56362CEF38};
static INTE_32 ConstantInvalid32[4]={0x7F800000,0xFF800000,0x7FFFFFFF,0xFFFFFFFF};
static INTE_32 ConstantPi32[4]={0x40490FDB,0x3EA2F983,0x402DF854,0x3EBC5AB2};

static DATA_64 TableShrink64[8]={0x0000000000000001,0x0000000000000002,0x0000000000000004,0x0000000000000008,0x0000000000000010,0x0000000000000020,0x0000000000000040,0x0000000000000080};
static DATA_32 TableShrink32[8]={0x00000001,0x00000002,0x00000004,0x00000008,0x00000010,0x00000020,0x00000040,0x00000080};
static DATA_16 TableShrink16[8]={0x0001,0x0002,0x0004,0x0008,0x0010,0x0020,0x0040,0x0080};
static DATA_08 TableShrink08[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
static BOOLEAN TableBool[4]={!1,!0,BitCNull,BitCFull};

#if(MemC_Fold_(Type Descriptors))
static INTE_08 IdiomTypeName[_BitC_Total_Types][_BitC_Type_Name_Length]=
{
	"data_08","data_16","data_32","data_64",
	"inte_08","inte_16","inte_32","inte_64",
	"real_08","real_16","real_32","real_64",
};
static MEMC_DT TableType[_BitC_Total_Types]=
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
static MEMC_DT _PL_ AddressType[_BitC_Total_Types]=
{
	TableType+BitCTypeD08,TableType+BitCTypeD16,TableType+BitCTypeD32,TableType+BitCTypeD64,
	TableType+BitCTypeI08,TableType+BitCTypeI16,TableType+BitCTypeI32,TableType+BitCTypeI64,
	TableType+BitCTypeR08,TableType+BitCTypeR16,TableType+BitCTypeR32,TableType+BitCTypeR64
};
#endif

#ifdef __OPENCL_H
static NAME_08 IdiomFileName[_BitC_Total_Files][_BitC_File_Name_Length]={"ouoclip.cl","bitclip.cl"};
static NAME_08 IdiomKernelName[_BitC_Total_Kernels][_BitC_Kernel_Name_Length]=
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
	"",						"BitC_RO_L_2_R16_",		"BitC_RO_L_2_R32_",		"BitC_RO_L_2_R64_"
};

static NAME_08 _PL_ AddressFileName[_BitC_Total_Files]={IdiomFileName[0],IdiomFileName[1]};
static NAME_08 _PL_ AddressKernelName[_BitC_Total_Kernels]=
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
	IdiomKernelName[240],IdiomKernelName[241],IdiomKernelName[242],IdiomKernelName[243]
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

general BitC_Expand_D08_(DATA_08 *MemC_Rst_ DataI,data_08 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	DATA_08 *End=DataO+Safe;
	inte_08 TempA;
	inte_08 TempB;

	for(;DataO<End;DataI++,DataO+=8)
	{
		TempA=(inte_08)(DataI[0]);

		TempB=TempA<<7;
		TempB>>=7;
		DataO[0]=TempB;
		TempB=TempA<<6;
		TempB>>=7;
		DataO[1]=TempB;
		TempB=TempA<<5;
		TempB>>=7;
		DataO[2]=TempB;
		TempB=TempA<<4;
		TempB>>=7;
		DataO[3]=TempB;
		TempB=TempA<<3;
		TempB>>=7;
		DataO[4]=TempB;
		TempB=TempA<<2;
		TempB>>=7;
		DataO[5]=TempB;
		TempB=TempA<<1;
		TempB>>=7;
		DataO[6]=TempB;
		TempB=TempA>>7;
		DataO[7]=TempB;
	}
	if(Rest)
	{
		data_32 Shift=7;

		for(End+=Rest,TempA=(inte_08)(DataI[0]);DataO<End;DataO++,Shift--)
		{
			TempB=TempA<<Shift;
			TempB>>=7;
			DataO[0]=TempB;
		}
	}
}
general BitC_Expand_D16_(DATA_08 *MemC_Rst_ DataI,data_16 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	DATA_16 *End=DataO+Safe;
	inte_16 TempA;
	inte_16 TempB;

	for(;DataO<End;DataI++,DataO+=8)
	{
		TempA=(inte_16)(DataI[0]);

		TempB=TempA<<15;
		TempB>>=15;
		DataO[0]=TempB;
		TempB=TempA<<14;
		TempB>>=15;
		DataO[1]=TempB;
		TempB=TempA<<13;
		TempB>>=15;
		DataO[2]=TempB;
		TempB=TempA<<12;
		TempB>>=15;
		DataO[3]=TempB;
		TempB=TempA<<11;
		TempB>>=15;
		DataO[4]=TempB;
		TempB=TempA<<10;
		TempB>>=15;
		DataO[5]=TempB;
		TempB=TempA<<9;
		TempB>>=15;
		DataO[6]=TempB;
		TempB=TempA<<8;
		TempB>>=15;
		DataO[7]=TempB;
	}
	if(Rest)
	{
		data_32 Shift=15;

		for(End+=Rest,TempA=(inte_16)(DataI[0]);DataO<End;DataO++,Shift--)
		{
			TempB=TempA<<Shift;
			TempB>>=15;
			DataO[0]=TempB;
		}
	}
}
general BitC_Expand_D32_(DATA_08 *MemC_Rst_ DataI,data_32 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	DATA_32 *End=DataO+Safe;
	inte_32 TempA;
	inte_32 TempB;

	for(;DataO<End;DataI++,DataO+=8)
	{
		TempA=(inte_32)(DataI[0]);

		TempB=TempA<<31;
		TempB>>=31;
		DataO[0]=TempB;
		TempB=TempA<<30;
		TempB>>=31;
		DataO[1]=TempB;
		TempB=TempA<<29;
		TempB>>=31;
		DataO[2]=TempB;
		TempB=TempA<<28;
		TempB>>=31;
		DataO[3]=TempB;
		TempB=TempA<<27;
		TempB>>=31;
		DataO[4]=TempB;
		TempB=TempA<<26;
		TempB>>=31;
		DataO[5]=TempB;
		TempB=TempA<<25;
		TempB>>=31;
		DataO[6]=TempB;
		TempB=TempA<<24;
		TempB>>=31;
		DataO[7]=TempB;
	}
	if(Rest)
	{
		data_32 Shift=31;

		for(End+=Rest,TempA=(inte_32)(DataI[0]);DataO<End;DataO++,Shift--)
		{
			TempB=TempA<<Shift;
			TempB>>=31;
			DataO[0]=TempB;
		}
	}
}
general BitC_Expand_D64_(DATA_08 *MemC_Rst_ DataI,data_64 *MemC_Rst_ DataO,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	DATA_64 *End=DataO+Safe;
	inte_64 TempA;
	inte_64 TempB;

	for(;DataO<End;DataI++,DataO+=8)
	{
		TempA=(inte_64)(DataI[0]);

		TempB=TempA<<63;
		TempB>>=63;
		DataO[0]=TempB;
		TempB=TempA<<62;
		TempB>>=63;
		DataO[1]=TempB;
		TempB=TempA<<61;
		TempB>>=63;
		DataO[2]=TempB;
		TempB=TempA<<60;
		TempB>>=63;
		DataO[3]=TempB;
		TempB=TempA<<59;
		TempB>>=63;
		DataO[4]=TempB;
		TempB=TempA<<58;
		TempB>>=63;
		DataO[5]=TempB;
		TempB=TempA<<57;
		TempB>>=63;
		DataO[6]=TempB;
		TempB=TempA<<56;
		TempB>>=63;
		DataO[7]=TempB;
	}
	if(Rest)
	{
		data_32 Shift=63;

		for(End+=Rest,TempA=(inte_64)(DataI[0]);DataO<End;DataO++,Shift--)
		{
			TempB=TempA<<Shift;
			TempB>>=63;
			DataO[0]=TempB;
		}
	}
}

general BitC_Shrink_D08_(DATA_08 *MemC_Rst_ DataI,data_08 *MemC_Rst_ DataO,DATA_32 Length)
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
general BitC_Shrink_D16_(DATA_16 *MemC_Rst_ DataI,data_08 *MemC_Rst_ DataO,DATA_32 Length)
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
general BitC_Shrink_D32_(DATA_32 *MemC_Rst_ DataI,data_08 *MemC_Rst_ DataO,DATA_32 Length)
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
general BitC_Shrink_D64_(DATA_64 *MemC_Rst_ DataI,data_08 *MemC_Rst_ DataO,DATA_32 Length)
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

general BitC_RO_E_1_D08_(data_08 *MemC_Rst_ DataC,DATA_08 *MemC_Rst_ DataA,DATA_08 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_08 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]==Value);
			Mask.V.D08[1]=(data_08)(DataA[1]==Value);
			Mask.V.D08[2]=(data_08)(DataA[2]==Value);
			Mask.V.D08[3]=(data_08)(DataA[3]==Value);
			Mask.V.D08[4]=(data_08)(DataA[4]==Value);
			Mask.V.D08[5]=(data_08)(DataA[5]==Value);
			Mask.V.D08[6]=(data_08)(DataA[6]==Value);
			Mask.V.D08[7]=(data_08)(DataA[7]==Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]==Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_E_1_D16_(data_08 *MemC_Rst_ DataC,DATA_16 *MemC_Rst_ DataA,DATA_16 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_16 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]==Value);
			Mask.V.D08[1]=(data_08)(DataA[1]==Value);
			Mask.V.D08[2]=(data_08)(DataA[2]==Value);
			Mask.V.D08[3]=(data_08)(DataA[3]==Value);
			Mask.V.D08[4]=(data_08)(DataA[4]==Value);
			Mask.V.D08[5]=(data_08)(DataA[5]==Value);
			Mask.V.D08[6]=(data_08)(DataA[6]==Value);
			Mask.V.D08[7]=(data_08)(DataA[7]==Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]==Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_E_1_D32_(data_08 *MemC_Rst_ DataC,DATA_32 *MemC_Rst_ DataA,DATA_32 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_32 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]==Value);
			Mask.V.D08[1]=(data_08)(DataA[1]==Value);
			Mask.V.D08[2]=(data_08)(DataA[2]==Value);
			Mask.V.D08[3]=(data_08)(DataA[3]==Value);
			Mask.V.D08[4]=(data_08)(DataA[4]==Value);
			Mask.V.D08[5]=(data_08)(DataA[5]==Value);
			Mask.V.D08[6]=(data_08)(DataA[6]==Value);
			Mask.V.D08[7]=(data_08)(DataA[7]==Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]==Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_E_1_D64_(data_08 *MemC_Rst_ DataC,DATA_64 *MemC_Rst_ DataA,DATA_64 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_64 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]==Value);
			Mask.V.D08[1]=(data_08)(DataA[1]==Value);
			Mask.V.D08[2]=(data_08)(DataA[2]==Value);
			Mask.V.D08[3]=(data_08)(DataA[3]==Value);
			Mask.V.D08[4]=(data_08)(DataA[4]==Value);
			Mask.V.D08[5]=(data_08)(DataA[5]==Value);
			Mask.V.D08[6]=(data_08)(DataA[6]==Value);
			Mask.V.D08[7]=(data_08)(DataA[7]==Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]==Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_E_2_D08_(data_08 *MemC_Rst_ DataC,DATA_08 *MemC_Rst_ DataA,DATA_08 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_08 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]==DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]==DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]==DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]==DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]==DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]==DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]==DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]==DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]==DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_E_2_D16_(data_08 *MemC_Rst_ DataC,DATA_16 *MemC_Rst_ DataA,DATA_16 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_16 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]==DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]==DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]==DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]==DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]==DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]==DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]==DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]==DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]==DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_E_2_D32_(data_08 *MemC_Rst_ DataC,DATA_32 *MemC_Rst_ DataA,DATA_32 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_32 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]==DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]==DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]==DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]==DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]==DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]==DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]==DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]==DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]==DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_E_2_D64_(data_08 *MemC_Rst_ DataC,DATA_64 *MemC_Rst_ DataA,DATA_64 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_64 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]==DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]==DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]==DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]==DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]==DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]==DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]==DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]==DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]==DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}

general BitC_RO_N_1_D08_(data_08 *MemC_Rst_ DataC,DATA_08 *MemC_Rst_ DataA,DATA_08 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_08 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]!=Value);
			Mask.V.D08[1]=(data_08)(DataA[1]!=Value);
			Mask.V.D08[2]=(data_08)(DataA[2]!=Value);
			Mask.V.D08[3]=(data_08)(DataA[3]!=Value);
			Mask.V.D08[4]=(data_08)(DataA[4]!=Value);
			Mask.V.D08[5]=(data_08)(DataA[5]!=Value);
			Mask.V.D08[6]=(data_08)(DataA[6]!=Value);
			Mask.V.D08[7]=(data_08)(DataA[7]!=Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]!=Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_N_1_D16_(data_08 *MemC_Rst_ DataC,DATA_16 *MemC_Rst_ DataA,DATA_16 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_16 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]!=Value);
			Mask.V.D08[1]=(data_08)(DataA[1]!=Value);
			Mask.V.D08[2]=(data_08)(DataA[2]!=Value);
			Mask.V.D08[3]=(data_08)(DataA[3]!=Value);
			Mask.V.D08[4]=(data_08)(DataA[4]!=Value);
			Mask.V.D08[5]=(data_08)(DataA[5]!=Value);
			Mask.V.D08[6]=(data_08)(DataA[6]!=Value);
			Mask.V.D08[7]=(data_08)(DataA[7]!=Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]!=Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_N_1_D32_(data_08 *MemC_Rst_ DataC,DATA_32 *MemC_Rst_ DataA,DATA_32 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_32 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]!=Value);
			Mask.V.D08[1]=(data_08)(DataA[1]!=Value);
			Mask.V.D08[2]=(data_08)(DataA[2]!=Value);
			Mask.V.D08[3]=(data_08)(DataA[3]!=Value);
			Mask.V.D08[4]=(data_08)(DataA[4]!=Value);
			Mask.V.D08[5]=(data_08)(DataA[5]!=Value);
			Mask.V.D08[6]=(data_08)(DataA[6]!=Value);
			Mask.V.D08[7]=(data_08)(DataA[7]!=Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]!=Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_N_1_D64_(data_08 *MemC_Rst_ DataC,DATA_64 *MemC_Rst_ DataA,DATA_64 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_64 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]!=Value);
			Mask.V.D08[1]=(data_08)(DataA[1]!=Value);
			Mask.V.D08[2]=(data_08)(DataA[2]!=Value);
			Mask.V.D08[3]=(data_08)(DataA[3]!=Value);
			Mask.V.D08[4]=(data_08)(DataA[4]!=Value);
			Mask.V.D08[5]=(data_08)(DataA[5]!=Value);
			Mask.V.D08[6]=(data_08)(DataA[6]!=Value);
			Mask.V.D08[7]=(data_08)(DataA[7]!=Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]!=Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_N_2_D08_(data_08 *MemC_Rst_ DataC,DATA_08 *MemC_Rst_ DataA,DATA_08 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_08 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]!=DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]!=DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]!=DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]!=DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]!=DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]!=DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]!=DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]!=DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]!=DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_N_2_D16_(data_08 *MemC_Rst_ DataC,DATA_16 *MemC_Rst_ DataA,DATA_16 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_16 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]!=DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]!=DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]!=DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]!=DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]!=DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]!=DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]!=DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]!=DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]!=DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_N_2_D32_(data_08 *MemC_Rst_ DataC,DATA_32 *MemC_Rst_ DataA,DATA_32 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_32 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]!=DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]!=DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]!=DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]!=DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]!=DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]!=DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]!=DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]!=DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]!=DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_N_2_D64_(data_08 *MemC_Rst_ DataC,DATA_64 *MemC_Rst_ DataA,DATA_64 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_64 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]!=DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]!=DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]!=DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]!=DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]!=DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]!=DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]!=DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]!=DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]!=DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}

general BitC_RO_G_1_D08_(data_08 *MemC_Rst_ DataC,DATA_08 *MemC_Rst_ DataA,DATA_08 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_08 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]>=Value);
			Mask.V.D08[1]=(data_08)(DataA[1]>=Value);
			Mask.V.D08[2]=(data_08)(DataA[2]>=Value);
			Mask.V.D08[3]=(data_08)(DataA[3]>=Value);
			Mask.V.D08[4]=(data_08)(DataA[4]>=Value);
			Mask.V.D08[5]=(data_08)(DataA[5]>=Value);
			Mask.V.D08[6]=(data_08)(DataA[6]>=Value);
			Mask.V.D08[7]=(data_08)(DataA[7]>=Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]>=Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_G_1_D16_(data_08 *MemC_Rst_ DataC,DATA_16 *MemC_Rst_ DataA,DATA_16 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_16 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]>=Value);
			Mask.V.D08[1]=(data_08)(DataA[1]>=Value);
			Mask.V.D08[2]=(data_08)(DataA[2]>=Value);
			Mask.V.D08[3]=(data_08)(DataA[3]>=Value);
			Mask.V.D08[4]=(data_08)(DataA[4]>=Value);
			Mask.V.D08[5]=(data_08)(DataA[5]>=Value);
			Mask.V.D08[6]=(data_08)(DataA[6]>=Value);
			Mask.V.D08[7]=(data_08)(DataA[7]>=Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]>=Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_G_1_D32_(data_08 *MemC_Rst_ DataC,DATA_32 *MemC_Rst_ DataA,DATA_32 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_32 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]>=Value);
			Mask.V.D08[1]=(data_08)(DataA[1]>=Value);
			Mask.V.D08[2]=(data_08)(DataA[2]>=Value);
			Mask.V.D08[3]=(data_08)(DataA[3]>=Value);
			Mask.V.D08[4]=(data_08)(DataA[4]>=Value);
			Mask.V.D08[5]=(data_08)(DataA[5]>=Value);
			Mask.V.D08[6]=(data_08)(DataA[6]>=Value);
			Mask.V.D08[7]=(data_08)(DataA[7]>=Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]>=Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_G_1_D64_(data_08 *MemC_Rst_ DataC,DATA_64 *MemC_Rst_ DataA,DATA_64 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_64 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]>=Value);
			Mask.V.D08[1]=(data_08)(DataA[1]>=Value);
			Mask.V.D08[2]=(data_08)(DataA[2]>=Value);
			Mask.V.D08[3]=(data_08)(DataA[3]>=Value);
			Mask.V.D08[4]=(data_08)(DataA[4]>=Value);
			Mask.V.D08[5]=(data_08)(DataA[5]>=Value);
			Mask.V.D08[6]=(data_08)(DataA[6]>=Value);
			Mask.V.D08[7]=(data_08)(DataA[7]>=Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]>=Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_G_1_I08_(data_08 *MemC_Rst_ DataC,INTE_08 *MemC_Rst_ DataA,INTE_08 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		INTE_08 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]>=Value);
			Mask.V.D08[1]=(data_08)(DataA[1]>=Value);
			Mask.V.D08[2]=(data_08)(DataA[2]>=Value);
			Mask.V.D08[3]=(data_08)(DataA[3]>=Value);
			Mask.V.D08[4]=(data_08)(DataA[4]>=Value);
			Mask.V.D08[5]=(data_08)(DataA[5]>=Value);
			Mask.V.D08[6]=(data_08)(DataA[6]>=Value);
			Mask.V.D08[7]=(data_08)(DataA[7]>=Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]>=Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_G_1_I16_(data_08 *MemC_Rst_ DataC,INTE_16 *MemC_Rst_ DataA,INTE_16 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		INTE_16 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]>=Value);
			Mask.V.D08[1]=(data_08)(DataA[1]>=Value);
			Mask.V.D08[2]=(data_08)(DataA[2]>=Value);
			Mask.V.D08[3]=(data_08)(DataA[3]>=Value);
			Mask.V.D08[4]=(data_08)(DataA[4]>=Value);
			Mask.V.D08[5]=(data_08)(DataA[5]>=Value);
			Mask.V.D08[6]=(data_08)(DataA[6]>=Value);
			Mask.V.D08[7]=(data_08)(DataA[7]>=Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]>=Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_G_1_I32_(data_08 *MemC_Rst_ DataC,INTE_32 *MemC_Rst_ DataA,INTE_32 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		INTE_32 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]>=Value);
			Mask.V.D08[1]=(data_08)(DataA[1]>=Value);
			Mask.V.D08[2]=(data_08)(DataA[2]>=Value);
			Mask.V.D08[3]=(data_08)(DataA[3]>=Value);
			Mask.V.D08[4]=(data_08)(DataA[4]>=Value);
			Mask.V.D08[5]=(data_08)(DataA[5]>=Value);
			Mask.V.D08[6]=(data_08)(DataA[6]>=Value);
			Mask.V.D08[7]=(data_08)(DataA[7]>=Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]>=Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_G_1_I64_(data_08 *MemC_Rst_ DataC,INTE_64 *MemC_Rst_ DataA,INTE_64 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		INTE_64 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]>=Value);
			Mask.V.D08[1]=(data_08)(DataA[1]>=Value);
			Mask.V.D08[2]=(data_08)(DataA[2]>=Value);
			Mask.V.D08[3]=(data_08)(DataA[3]>=Value);
			Mask.V.D08[4]=(data_08)(DataA[4]>=Value);
			Mask.V.D08[5]=(data_08)(DataA[5]>=Value);
			Mask.V.D08[6]=(data_08)(DataA[6]>=Value);
			Mask.V.D08[7]=(data_08)(DataA[7]>=Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]>=Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_G_1_R32_(data_08 *MemC_Rst_ DataC,REAL_32 *MemC_Rst_ DataA,REAL_32 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		REAL_32 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]>=Value);
			Mask.V.D08[1]=(data_08)(DataA[1]>=Value);
			Mask.V.D08[2]=(data_08)(DataA[2]>=Value);
			Mask.V.D08[3]=(data_08)(DataA[3]>=Value);
			Mask.V.D08[4]=(data_08)(DataA[4]>=Value);
			Mask.V.D08[5]=(data_08)(DataA[5]>=Value);
			Mask.V.D08[6]=(data_08)(DataA[6]>=Value);
			Mask.V.D08[7]=(data_08)(DataA[7]>=Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]>=Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_G_1_R64_(data_08 *MemC_Rst_ DataC,REAL_64 *MemC_Rst_ DataA,REAL_64 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		REAL_64 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]>=Value);
			Mask.V.D08[1]=(data_08)(DataA[1]>=Value);
			Mask.V.D08[2]=(data_08)(DataA[2]>=Value);
			Mask.V.D08[3]=(data_08)(DataA[3]>=Value);
			Mask.V.D08[4]=(data_08)(DataA[4]>=Value);
			Mask.V.D08[5]=(data_08)(DataA[5]>=Value);
			Mask.V.D08[6]=(data_08)(DataA[6]>=Value);
			Mask.V.D08[7]=(data_08)(DataA[7]>=Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]>=Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_G_2_D08_(data_08 *MemC_Rst_ DataC,DATA_08 *MemC_Rst_ DataA,DATA_08 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_08 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]>=DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]>=DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]>=DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]>=DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]>=DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]>=DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]>=DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]>=DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]>=DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_G_2_D16_(data_08 *MemC_Rst_ DataC,DATA_16 *MemC_Rst_ DataA,DATA_16 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_16 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]>=DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]>=DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]>=DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]>=DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]>=DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]>=DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]>=DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]>=DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]>=DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_G_2_D32_(data_08 *MemC_Rst_ DataC,DATA_32 *MemC_Rst_ DataA,DATA_32 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_32 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]>=DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]>=DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]>=DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]>=DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]>=DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]>=DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]>=DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]>=DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]>=DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_G_2_D64_(data_08 *MemC_Rst_ DataC,DATA_64 *MemC_Rst_ DataA,DATA_64 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_64 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]>=DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]>=DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]>=DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]>=DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]>=DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]>=DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]>=DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]>=DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]>=DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_G_2_I08_(data_08 *MemC_Rst_ DataC,INTE_08 *MemC_Rst_ DataA,INTE_08 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		INTE_08 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]>=DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]>=DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]>=DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]>=DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]>=DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]>=DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]>=DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]>=DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]>=DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_G_2_I16_(data_08 *MemC_Rst_ DataC,INTE_16 *MemC_Rst_ DataA,INTE_16 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		INTE_16 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]>=DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]>=DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]>=DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]>=DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]>=DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]>=DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]>=DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]>=DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]>=DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_G_2_I32_(data_08 *MemC_Rst_ DataC,INTE_32 *MemC_Rst_ DataA,INTE_32 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		INTE_32 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]>=DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]>=DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]>=DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]>=DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]>=DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]>=DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]>=DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]>=DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]>=DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_G_2_I64_(data_08 *MemC_Rst_ DataC,INTE_64 *MemC_Rst_ DataA,INTE_64 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		INTE_64 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]>=DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]>=DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]>=DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]>=DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]>=DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]>=DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]>=DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]>=DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]>=DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_G_2_R32_(data_08 *MemC_Rst_ DataC,REAL_32 *MemC_Rst_ DataA,REAL_32 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		REAL_32 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]>=DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]>=DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]>=DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]>=DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]>=DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]>=DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]>=DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]>=DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]>=DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_G_2_R64_(data_08 *MemC_Rst_ DataC,REAL_64 *MemC_Rst_ DataA,REAL_64 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		REAL_64 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]>=DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]>=DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]>=DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]>=DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]>=DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]>=DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]>=DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]>=DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]>=DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}

general BitC_RO_L_1_D08_(data_08 *MemC_Rst_ DataC,DATA_08 *MemC_Rst_ DataA,DATA_08 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_08 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]<Value);
			Mask.V.D08[1]=(data_08)(DataA[1]<Value);
			Mask.V.D08[2]=(data_08)(DataA[2]<Value);
			Mask.V.D08[3]=(data_08)(DataA[3]<Value);
			Mask.V.D08[4]=(data_08)(DataA[4]<Value);
			Mask.V.D08[5]=(data_08)(DataA[5]<Value);
			Mask.V.D08[6]=(data_08)(DataA[6]<Value);
			Mask.V.D08[7]=(data_08)(DataA[7]<Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]<Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_L_1_D16_(data_08 *MemC_Rst_ DataC,DATA_16 *MemC_Rst_ DataA,DATA_16 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_16 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]<Value);
			Mask.V.D08[1]=(data_08)(DataA[1]<Value);
			Mask.V.D08[2]=(data_08)(DataA[2]<Value);
			Mask.V.D08[3]=(data_08)(DataA[3]<Value);
			Mask.V.D08[4]=(data_08)(DataA[4]<Value);
			Mask.V.D08[5]=(data_08)(DataA[5]<Value);
			Mask.V.D08[6]=(data_08)(DataA[6]<Value);
			Mask.V.D08[7]=(data_08)(DataA[7]<Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]<Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_L_1_D32_(data_08 *MemC_Rst_ DataC,DATA_32 *MemC_Rst_ DataA,DATA_32 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_32 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]<Value);
			Mask.V.D08[1]=(data_08)(DataA[1]<Value);
			Mask.V.D08[2]=(data_08)(DataA[2]<Value);
			Mask.V.D08[3]=(data_08)(DataA[3]<Value);
			Mask.V.D08[4]=(data_08)(DataA[4]<Value);
			Mask.V.D08[5]=(data_08)(DataA[5]<Value);
			Mask.V.D08[6]=(data_08)(DataA[6]<Value);
			Mask.V.D08[7]=(data_08)(DataA[7]<Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]<Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_L_1_D64_(data_08 *MemC_Rst_ DataC,DATA_64 *MemC_Rst_ DataA,DATA_64 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_64 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]<Value);
			Mask.V.D08[1]=(data_08)(DataA[1]<Value);
			Mask.V.D08[2]=(data_08)(DataA[2]<Value);
			Mask.V.D08[3]=(data_08)(DataA[3]<Value);
			Mask.V.D08[4]=(data_08)(DataA[4]<Value);
			Mask.V.D08[5]=(data_08)(DataA[5]<Value);
			Mask.V.D08[6]=(data_08)(DataA[6]<Value);
			Mask.V.D08[7]=(data_08)(DataA[7]<Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]<Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_L_1_I08_(data_08 *MemC_Rst_ DataC,INTE_08 *MemC_Rst_ DataA,INTE_08 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		INTE_08 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]<Value);
			Mask.V.D08[1]=(data_08)(DataA[1]<Value);
			Mask.V.D08[2]=(data_08)(DataA[2]<Value);
			Mask.V.D08[3]=(data_08)(DataA[3]<Value);
			Mask.V.D08[4]=(data_08)(DataA[4]<Value);
			Mask.V.D08[5]=(data_08)(DataA[5]<Value);
			Mask.V.D08[6]=(data_08)(DataA[6]<Value);
			Mask.V.D08[7]=(data_08)(DataA[7]<Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]<Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_L_1_I16_(data_08 *MemC_Rst_ DataC,INTE_16 *MemC_Rst_ DataA,INTE_16 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		INTE_16 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]<Value);
			Mask.V.D08[1]=(data_08)(DataA[1]<Value);
			Mask.V.D08[2]=(data_08)(DataA[2]<Value);
			Mask.V.D08[3]=(data_08)(DataA[3]<Value);
			Mask.V.D08[4]=(data_08)(DataA[4]<Value);
			Mask.V.D08[5]=(data_08)(DataA[5]<Value);
			Mask.V.D08[6]=(data_08)(DataA[6]<Value);
			Mask.V.D08[7]=(data_08)(DataA[7]<Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]<Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_L_1_I32_(data_08 *MemC_Rst_ DataC,INTE_32 *MemC_Rst_ DataA,INTE_32 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		INTE_32 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]<Value);
			Mask.V.D08[1]=(data_08)(DataA[1]<Value);
			Mask.V.D08[2]=(data_08)(DataA[2]<Value);
			Mask.V.D08[3]=(data_08)(DataA[3]<Value);
			Mask.V.D08[4]=(data_08)(DataA[4]<Value);
			Mask.V.D08[5]=(data_08)(DataA[5]<Value);
			Mask.V.D08[6]=(data_08)(DataA[6]<Value);
			Mask.V.D08[7]=(data_08)(DataA[7]<Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]<Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_L_1_I64_(data_08 *MemC_Rst_ DataC,INTE_64 *MemC_Rst_ DataA,INTE_64 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		INTE_64 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]<Value);
			Mask.V.D08[1]=(data_08)(DataA[1]<Value);
			Mask.V.D08[2]=(data_08)(DataA[2]<Value);
			Mask.V.D08[3]=(data_08)(DataA[3]<Value);
			Mask.V.D08[4]=(data_08)(DataA[4]<Value);
			Mask.V.D08[5]=(data_08)(DataA[5]<Value);
			Mask.V.D08[6]=(data_08)(DataA[6]<Value);
			Mask.V.D08[7]=(data_08)(DataA[7]<Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]<Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_L_1_R32_(data_08 *MemC_Rst_ DataC,REAL_32 *MemC_Rst_ DataA,REAL_32 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		REAL_32 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]<Value);
			Mask.V.D08[1]=(data_08)(DataA[1]<Value);
			Mask.V.D08[2]=(data_08)(DataA[2]<Value);
			Mask.V.D08[3]=(data_08)(DataA[3]<Value);
			Mask.V.D08[4]=(data_08)(DataA[4]<Value);
			Mask.V.D08[5]=(data_08)(DataA[5]<Value);
			Mask.V.D08[6]=(data_08)(DataA[6]<Value);
			Mask.V.D08[7]=(data_08)(DataA[7]<Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]<Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_L_1_R64_(data_08 *MemC_Rst_ DataC,REAL_64 *MemC_Rst_ DataA,REAL_64 Value,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		REAL_64 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]<Value);
			Mask.V.D08[1]=(data_08)(DataA[1]<Value);
			Mask.V.D08[2]=(data_08)(DataA[2]<Value);
			Mask.V.D08[3]=(data_08)(DataA[3]<Value);
			Mask.V.D08[4]=(data_08)(DataA[4]<Value);
			Mask.V.D08[5]=(data_08)(DataA[5]<Value);
			Mask.V.D08[6]=(data_08)(DataA[6]<Value);
			Mask.V.D08[7]=(data_08)(DataA[7]<Value);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]<Value);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_L_2_D08_(data_08 *MemC_Rst_ DataC,DATA_08 *MemC_Rst_ DataA,DATA_08 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_08 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]<DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]<DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]<DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]<DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]<DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]<DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]<DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]<DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]<DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_L_2_D16_(data_08 *MemC_Rst_ DataC,DATA_16 *MemC_Rst_ DataA,DATA_16 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_16 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]<DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]<DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]<DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]<DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]<DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]<DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]<DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]<DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]<DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_L_2_D32_(data_08 *MemC_Rst_ DataC,DATA_32 *MemC_Rst_ DataA,DATA_32 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_32 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]<DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]<DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]<DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]<DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]<DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]<DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]<DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]<DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]<DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_L_2_D64_(data_08 *MemC_Rst_ DataC,DATA_64 *MemC_Rst_ DataA,DATA_64 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		DATA_64 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]<DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]<DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]<DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]<DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]<DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]<DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]<DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]<DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]<DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_L_2_I08_(data_08 *MemC_Rst_ DataC,INTE_08 *MemC_Rst_ DataA,INTE_08 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		INTE_08 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]<DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]<DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]<DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]<DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]<DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]<DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]<DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]<DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]<DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_L_2_I16_(data_08 *MemC_Rst_ DataC,INTE_16 *MemC_Rst_ DataA,INTE_16 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		INTE_16 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]<DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]<DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]<DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]<DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]<DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]<DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]<DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]<DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]<DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_L_2_I32_(data_08 *MemC_Rst_ DataC,INTE_32 *MemC_Rst_ DataA,INTE_32 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		INTE_32 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]<DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]<DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]<DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]<DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]<DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]<DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]<DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]<DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]<DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_L_2_I64_(data_08 *MemC_Rst_ DataC,INTE_64 *MemC_Rst_ DataA,INTE_64 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		INTE_64 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]<DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]<DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]<DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]<DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]<DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]<DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]<DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]<DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]<DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_L_2_R32_(data_08 *MemC_Rst_ DataC,REAL_32 *MemC_Rst_ DataA,REAL_32 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		REAL_32 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]<DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]<DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]<DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]<DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]<DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]<DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]<DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]<DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]<DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
general BitC_RO_L_2_R64_(data_08 *MemC_Rst_ DataC,REAL_64 *MemC_Rst_ DataA,REAL_64 *MemC_Rst_ DataB,DATA_32 Length)
{
	DATA_32 Safe=Length&0xFFFFFFF8;
	DATA_32 Rest=Length&0x00000007;
	data_64 Buffer;
	bitclip Mask;

	Mask.C.D64=&Buffer;
	{
		REAL_64 _PL_ End=DataA+Safe;

		for(;DataA<End;DataA+=8,DataB+=8,DataC++)
		{
			Mask.V.D08[0]=(data_08)(DataA[0]<DataB[0]);
			Mask.V.D08[1]=(data_08)(DataA[1]<DataB[1]);
			Mask.V.D08[2]=(data_08)(DataA[2]<DataB[2]);
			Mask.V.D08[3]=(data_08)(DataA[3]<DataB[3]);
			Mask.V.D08[4]=(data_08)(DataA[4]<DataB[4]);
			Mask.V.D08[5]=(data_08)(DataA[5]<DataB[5]);
			Mask.V.D08[6]=(data_08)(DataA[6]<DataB[6]);
			Mask.V.D08[7]=(data_08)(DataA[7]<DataB[7]);

			DataC[0]=_BitC_RO_Loop_A_(Mask);
		}
	}
	if(Rest)
	{
		data_32 Index=0;

		for(Mask.V.D64[0]=0;Index<Rest;Index++)
		{
			Mask.V.D08[Index]=(data_08)(DataA[Index]<DataB[Index]);
			Mask.V.D08[Index]<<=Index;
		}
		{
			_BitC_RO_Loop_B_(Mask,Rest);

			DataC[0]&=Mask.C.D08[1];
			DataC[0]|=Mask.C.D08[0];
		}
	}
}
#endif

#if(MemC_Fold_(Definition:BitClip Managed Functions))
#ifdef __OPENCL_H
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
static devi_km *_BitC_Create_KM_(cl_kernel const Kernel,BITC_KI Switch)
{
	devi_km *KM;

	if(Switch<0)
		KM=NULL;
	else if(Switch<4)
		KM=_BitC_Create_KM_Endian_(Kernel,BitCKernel[Switch]);
	else if(Switch<=148)
		KM=_BitC_Create_KM_Caster_(Kernel,BitCKernel[Switch]);
	else if(Switch<152)
		KM=_BitC_Create_KM_Op_(Kernel,BitCKernel[Switch],sizeof(cl_mem));
	else if(Switch<164)
		KM=_BitC_Create_KM_Op_(Kernel,BitCKernel[Switch],(address)(1<<(Switch&3)));
	else if(Switch<172)
		KM=_BitC_Create_KM_Op_(Kernel,BitCKernel[Switch],sizeof(inte_32));
	else if(Switch<180)
		KM=_BitC_Create_KM_Caster_(Kernel,BitCKernel[Switch]);
	else if(Switch<212)
		KM=_BitC_Create_KM_Op_(Kernel,BitCKernel[Switch],(address)(1<<(Switch&3)));
	else if(Switch<244)
		KM=_BitC_Create_KM_Op_(Kernel,BitCKernel[Switch],sizeof(cl_mem));
	else
		KM=NULL;

	return KM;
}

bitc_cl *BitC_CL_Create_(general)
{
	bitc_cl *Manager=Byte_Alloc_(sizeof(bitc_cl)+MemC_Size_(devi_km*,_BitC_Total_Kernels));

	if(Manager)
	{
		MemC_Acs_(GENERAL*,Manager->Helper)=NULL;
		MemC_Acs_(devi_km**,Manager->KMSet)=Line_Clear_(Manager+1,_BitC_Total_Kernels,devi_km*);
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
penc_eu BitC_CL_Launch_(cl_command_queue const Queue,BITC_CL _PL_ Manager,NAME_08 _PL_ Option)
{
	penc_eu Error;

	if(Manager)
		if(Manager->Helper)
			Error.E=CLInvalidHostPtr;
		else
		{
			GENERAL *Slot[_BitC_Total_Kernels];
			bitc_ki Link[_BitC_Total_Kernels];
			cl_uint Count=0;

			{
				bitc_ki Index;

				for(Index=0;Index<_BitC_Total_Kernels;Index++)
					if(Manager->KMSet[Index])
					{
						Slot[Count]=BitCKernel[Index];
						Link[Count]=Index;
						Count++;
					}
			}
			if(Count)
			{
				penc_cl *Helper=PenC_CL_Create_(Queue,BitCFile,(name_08**)Slot,Option,_BitC_Total_Files,Count,&Error);

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

						MemC_Acs_(penc_cl*,Manager->Helper)=Helper;
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
		if((*Manager)->Helper!=MemCrux)
		{
			devi_km **Ptr=(devi_km**)((*Manager)->KMSet+_BitC_Total_Kernels);

			for(Ptr--;Ptr>=(*Manager)->KMSet;Ptr--)
				Devi_KM_Delete_(Ptr);
			PenC_CL_Delete_((penc_cl**)&((*Manager)->Helper));
		}
		MemC_Deloc_(*Manager);
	}
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
					if(Indicator<_BitC_Total_Kernels)
						if(Manager->KMSet[Indicator])
							if((Argument->Nums)<((address)(Manager->KMSet[Indicator]->KArgs)))
								Error.E=CLInvalidKernelArgs;
							else
							{
								DEVI_KM _PL_ KM=Manager->KMSet[Indicator];

								{
									cl_uint Index=0;

									Error.E=CLSuccess;
									while(Index<KM->KArgs)
									{
										Error.I=Devi_KM_Save_(KM,Index,Argument->Slot.V[Index]);
										if(Error.E==CLSuccess)
											Index++;
										else
											break;
									}
								}
								if(Error.E==CLSuccess)
								{
									KM->WGroups[0]=Manager->Helper->Cores;
									KM->WLocals[0]=Manager->Helper->SizeWorker[0];
									Error.I=Devi_KM_Enqueue_(Manager->Helper->Queue,KM);
								}
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

#if(MemC_Fold_(Undefinition:Macros))
#undef _BitC_DT_Flag_Bits_64_
#undef _BitC_DT_Flag_Bits_32_
#undef _BitC_DT_Flag_Bits_16_
#undef _BitC_DT_Flag_Bits_08_
#undef _BitC_DT_Flag_Bits_
#undef _BitC_DT_Flag_Sign_
#undef _BitC_DT_Flag_Real_
#undef _BitC_DT_Define_
#ifdef __OPENCL_H
#undef _BitC_Kernel_Name_Length
#undef _BitC_Total_Kernels
#undef _BitC_File_Name_Length
#undef _BitC_Total_Files
#endif
#undef _BitC_Total_Types
#undef _BitC_Type_Name_Length
#undef _BitC_Clamp_
#undef _BitC_Max_
#undef _BitC_Min_
#endif
