﻿#include "priclip.h"

#if(Fold_(Template Macros))
#define PriC_TXX_(Type,Bits) Conc_(Type,Bits)

#define PriC_Type_(Type,Bits) xPriC_Type_(Type,Bits)
#define xPriC_Type_(Type,Bits) Type##_##Bits

#define PriC_Func_(Name,Suffix) xPriC_Func_(Name,Suffix)
#define xPriC_Func_(Name,Suffix) Name##Suffix##_
#endif

#if(Fold_(Internal Constants))
static const struct
{
	const struct { DATA_32 Break[64];DATA_08 Count[256]; }Cheat;
	BYTE_08 Version[16];
	const struct { DATA_64 D64;DATA_32 D32;DATA_16 D16;DATA_08 D08,Pad; }Count;
}
Idiom=
{
	.Version=oPRICLIP_INC_,
	.Count=
	{
		.D08=UINT8_C(0x36),
		.D16=UINT16_C(0x198E),
		.D32=UINT32_C(0x0C1DCF5D),
		.D64=UINT64_C(0x05E83C229654F94F)
	},
	.Cheat=
	{
		.Break=
		{
			0x00000001,0x00000001,0x00000002,0x00000002,0x00000003,0x00000004,0x00000006,0x00000008,
			0x0000000C,0x00000010,0x00000017,0x00000020,0x0000002E,0x00000040,0x0000005B,0x00000080,
			0x000000B6,0x00000100,0x0000016B,0x00000200,0x000002D5,0x00000400,0x000005A9,0x00000800,
			0x00000B51,0x00001000,0x000016A1,0x00002000,0x00002D42,0x00004000,0x00005A83,0x00008000,
			0x0000B505,0x00010000,0x00016A0A,0x00020000,0x0002D414,0x00040000,0x0005A828,0x00080000,
			0x000B5050,0x00100000,0x0016A09F,0x00200000,0x002D413D,0x00400000,0x005A827A,0x00800000,
			0x00B504F4,0x01000000,0x016A09E7,0x02000000,0x02D413CD,0x04000000,0x05A8279A,0x08000000,
			0x0B504F34,0x10000000,0x16A09E67,0x20000000,0x2D413CCD,0x40000000,0x5A82799A,0x80000000
		},
		.Count=
		{
			0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,
			1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
			1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
			2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
			1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
			2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
			2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
			3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
			1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
			2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
			2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
			3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
			2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
			3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
			3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
			4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
		}
	}
};
static_assert((sizeof(*(PriC.Count))<=sizeof(Idiom.Count))&&(sizeof(Idiom.Count)==16),"structure size mismatch");
#endif

#if(Fold_(Prime Table Functions))
static general PriC_Delete_(general *_PL_ _R_ Table) { MemC_Deloc_(*Table);return; }

static general xPriC_Mass_(data_08 _PL_ Mask,ADDRESS Bits)
{
	if(Bits<4)
	{
		DATA_08 Table[4]={0x00,0x00,0x02,0x0E};

		*Mask=Table[Bits];
	}
	else
	{
		ADDRESS Bytes=((address)(1))<<(Bits-4),Break=(address)(Idiom.Cheat.Break[Bits-1]);
		DATA_08 _PL_ Bound=(data_08*)memset(Mask,0xFF,Bytes)+Bytes;

		*Mask=0xFE;
		for(address Sub=1;1;Sub++)
		{
			for(bitc_bp Ptr=BitC.BP.Assign.U_(Mask,Sub);1;)
				if(BitC.BP.Reader_(Ptr))
				{
					Sub=(Ptr.Base)-Mask;
					Sub<<=3;
					Sub|=Ptr.Offset;
					break;
				}
				else
					Ptr=BitC.BP.Jumper.U_(Ptr,1);

			if(Sub<Break)
			{
				ADDRESS Mod=(Sub<<1)|1;

				for(bitc_bp Ptr=BitC.BP.Assign.U_(Mask,(Mod*Mod)>>1);(Ptr.Base)<Bound;Ptr=BitC.BP.Jumper.U_(Ptr,Mod))
					BitC.BP.Writer_(Ptr,0);
			}
			else
				break;
		}
	}

	return;
}
static address xPriC_Nums_(DATA_08 *_R_ Mask,ADDRESS Bits)
{
	if(Bits)
	{
		register address Count=1;

		if(Bits<4)
			Count+=Idiom.Cheat.Count[*Mask];
		else
		{
			ADDRESS Bytes=((address)(1))<<(Bits-4);

			for(DATA_08 _PL_ Bound=Mask+Bytes;Mask<Bound;Mask++)
				Count+=Idiom.Cheat.Count[*Mask];
		}

		return Count;
	}
	else
		return 0;
}

#include "pricrux.c"
#endif

#if(Fold_(Library Casing))
static_assert(sizeof(PRICASE)==sizeof(ADDRESS)*24,"sizeof(PRICASE) != 24*sizeof(ADDRESS)");
extern PRICASE PriC=
{
	.Version=Idiom.Version,
	.Count=(GENERAL*)&(Idiom.Count),
	.PT=
	{
		.Delete.D08_=MemC_Func_Casting_(general,PriC_Delete_,pric_08 *_PL_ _R_),
		.Save=
		{
			.D08_=PriC_Save_D08_,
			.D16_=PriC_Save_D16_,
			.D32_=PriC_Save_D32_,
			.D64_=PriC_Save_D64_
		},
		.Load=
		{
			.D08_=MemC_Func_Casting_(pric_08*,PriC_Load_D08_,FILE _PL_ _R_,DATA_08 _PL_ _R_),
			.D16_=MemC_Func_Casting_(pric_16*,PriC_Load_D16_,FILE _PL_ _R_,DATA_16 _PL_ _R_),
			.D32_=MemC_Func_Casting_(pric_32*,PriC_Load_D32_,FILE _PL_ _R_,DATA_32 _PL_ _R_),
			.D64_=MemC_Func_Casting_(pric_64*,PriC_Load_D64_,FILE _PL_ _R_,DATA_64 _PL_ _R_)
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
			.D08_=PriC_Factor_D08_,
			.D16_=PriC_Factor_D16_,
			.D32_=PriC_Factor_D32_,
			.D64_=PriC_Factor_D64_
		}
	}
};
extern PRICASE *PriC_(general) { return &PriC; }
#endif
