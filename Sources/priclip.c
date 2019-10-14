#include "priclip.h"

#if(Fold_(Definition:PriClip Macros))
#define _PRIC_ static
#endif

#if(Fold_(Definition:PriCrux Macros))
#define PriC_TXX_(Type,Bits) _Conc_(Type,Bits)

#define _PriC_Type_(Type,Bits) Type##_##Bits
#define PriC_Type_(Type,Bits) _PriC_Type_(Type,Bits)

#define _PriC_Func_(Name,Suffix) Name##Suffix##_
#define PriC_Func_(Name,Suffix) _PriC_Func_(Name,Suffix)

#define _PriC_Meta_(Msg) #Msg
#define PriC_Meta_(Msg) _PriC_Meta_(Msg)
#endif

#if(Fold_(Definition:Internal Constants))
_PRIC_ BYTE_08 IdiomVersion[16]="2019.10.14";
static const struct { DATA_64 D64;DATA_32 D32;DATA_16 D16;DATA_08 D08; }
ConstLimit=
{
	.D08=((UINT8_MAX)<(SIZE_MAX))?(UINT8_MAX):(SIZE_MAX),
	.D16=((UINT16_MAX)<(SIZE_MAX))?(UINT16_MAX):(SIZE_MAX),
	.D32=((UINT32_MAX)<(SIZE_MAX))?(UINT32_MAX):(SIZE_MAX),
	.D64=((UINT64_MAX)<(SIZE_MAX))?(UINT64_MAX):(SIZE_MAX)
};
#endif

#if(Fold_(Definition:Prime Table Functions))
_PRIC_ general PriC_Delete_(general *_PL_ _R_ Table) { MemC_Deloc_(*Table);return; }

#include "pricrux.c"
#endif

#if(Fold_(Undefinition:PriCrux Macros))
#undef PriC_Meta_
#undef _PriC_Meta_
#undef PriC_Func_
#undef _PriC_Func_
#undef PriC_Type_
#undef _PriC_Type_
#undef PriC_TXX_
#endif

#if(Fold_(Undefinition:PriClip Macros))
#undef _PRIC_
#endif

#if(Fold_(Library Casing))
PRICASE PriC=
{
	.Version=IdiomVersion,
	.PT=
	{
		.Delete.D08_=MemC_Func_Casting_(general,PriC_Delete_,pric_08 *_PL_ _R_),
		.Create=
		{
			.D08_=PriC_Create_D08_,
			.D16_=PriC_Create_D16_,
			.D32_=PriC_Create_D32_,
			.D64_=PriC_Create_D64_
		},
		.Save=
		{
			.D08_=MemC_Func_Casting_(logical,PriC_Save_D08_,FILE _PL_,PRIC_08 _PL_ _R_),
			.D16_=MemC_Func_Casting_(logical,PriC_Save_D16_,FILE _PL_,PRIC_16 _PL_ _R_),
			.D32_=MemC_Func_Casting_(logical,PriC_Save_D32_,FILE _PL_,PRIC_32 _PL_ _R_),
			.D64_=MemC_Func_Casting_(logical,PriC_Save_D64_,FILE _PL_,PRIC_64 _PL_ _R_)
		},
		.Load=
		{
			.D08_=MemC_Func_Casting_(pric_08*,PriC_Load_D08_,FILE _PL_,general _PL_ _R_),
			.D16_=MemC_Func_Casting_(pric_16*,PriC_Load_D16_,FILE _PL_,general _PL_ _R_),
			.D32_=MemC_Func_Casting_(pric_32*,PriC_Load_D32_,FILE _PL_,general _PL_ _R_),
			.D64_=MemC_Func_Casting_(pric_64*,PriC_Load_D64_,FILE _PL_,general _PL_ _R_)
		},
		.Search=
		{
			.D08_=PriC_Search_D08_,
			.D16_=PriC_Search_D16_,
			.D32_=PriC_Search_D32_,
			.D64_=PriC_Search_D64_
		},
		.Factor=
		{
			.D08_=MemC_Func_Casting_(logical,PriC_Factor_D08_,data_08 _PL_,PRIC_08 _PL_ _R_,DATA_08),
			.D16_=MemC_Func_Casting_(logical,PriC_Factor_D16_,data_16 _PL_,PRIC_16 _PL_ _R_,DATA_16),
			.D32_=MemC_Func_Casting_(logical,PriC_Factor_D32_,data_32 _PL_,PRIC_32 _PL_ _R_,DATA_32),
			.D64_=MemC_Func_Casting_(logical,PriC_Factor_D64_,data_64 _PL_,PRIC_64 _PL_ _R_,DATA_64)
		}
	},
	.Count=
	{
		.D08=0x36,
		.D16=0x198E,
		.D32=0x0C1DCF5D,
		.D64=0x05E83C229654F94F
	}
};
PRICASE *PriC_(general) { return &PriC; }
#endif
