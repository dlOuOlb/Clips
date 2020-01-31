#include "bitclip.h"
#include "bitcros.c"

#if(Fold_(Endian Functions))
_K_ BitC_Endian_D16_(_G_ data_16 _PL_ Data,_P_ OCLCLIP Start,_P_ OCLCLIP Amount,_P_ OCLCLIP Shape)
{
	_P_ ADDRESS Index=Work_Into_(Work_From_(Amount),Start,Shape);
	_P_ data_08 Buffer[4];
	_P_ bitc_pp Peek;Peek.C.D08=Buffer;
	
	Peek.V.D16[0]=Data[Index];
	Peek.V.D08[2]=Peek.C.D08[1];
	Peek.V.D08[3]=Peek.C.D08[0];
	Data[Index]=Peek.C.D16[1];

	return;
}
_K_ BitC_Endian_D32_(_G_ data_32 _PL_ Data,_P_ OCLCLIP Start,_P_ OCLCLIP Amount,_P_ OCLCLIP Shape)
{
	_P_ ADDRESS Index=Work_Into_(Work_From_(Amount),Start,Shape);
	_P_ data_08 Buffer[8];
	_P_ bitc_pp Peek;Peek.C.D08=Buffer;
	
	Peek.V.D32[0]=Data[Index];
	Peek.V.D08[4]=Peek.C.D08[3];
	Peek.V.D08[5]=Peek.C.D08[2];
	Peek.V.D08[6]=Peek.C.D08[1];
	Peek.V.D08[7]=Peek.C.D08[0];
	Data[Index]=Peek.C.D32[1];

	return;
}
_K_ BitC_Endian_D64_(_G_ data_32 _PL_ Data,_P_ OCLCLIP Start,_P_ OCLCLIP Amount,_P_ OCLCLIP Shape)
{
	_P_ ADDRESS Index=Work_Into_(Work_From_(Amount),Start,Shape);
	_P_ data_08 Buffer[16];
	_P_ bitc_pp Peek;Peek.C.D08=Buffer;

	Peek.V.D64[0]=Data[Index];
	Peek.V.D08[8]=Peek.C.D08[7];
	Peek.V.D08[9]=Peek.C.D08[6];
	Peek.V.D08[10]=Peek.C.D08[5];
	Peek.V.D08[11]=Peek.C.D08[4];
	Peek.V.D08[12]=Peek.C.D08[3];
	Peek.V.D08[13]=Peek.C.D08[2];
	Peek.V.D08[14]=Peek.C.D08[1];
	Peek.V.D08[15]=Peek.C.D08[0];
	Data[Index]=Peek.C.D64[1];

	return;
}
#endif

#if(Fold_(Reformation Functions))
#define xBitC_Copy_
#define xBitC_Data_
#include "bitcrux.c"
#undef xBitC_Data_
#undef xBitC_Copy_
#endif

#if(Fold_(Caster Functions))
#define xBitC_Caster_
#include "bitcrux.c"
#undef xBitC_Caster_
#endif

#if(Fold_(Bit Operation Functions))
#if(Fold_(BitC_BO_N_1_))
#define xBitC_BO_N_1_
#define BitC_Op_ BitC_BO_N_
#define xBitC_Data_
#include "bitcrux.c"
#undef xBitC_Data_
#undef BitC_Op_
#undef xBitC_BO_N_1_
#endif

#if(Fold_(BitC_BO_S_1_))
#define xBitC_BO_S_1_
#define BitC_Op_ BitC_BO_S_
#define xBitC_Data_
#define xBitC_Inte_
#include "bitcrux.c"
#undef xBitC_Inte_
#undef xBitC_Data_
#undef BitC_Op_
#undef xBitC_BO_S_1_
#endif

#if(Fold_(BitC_BO_A_ O_ X_))
#define xBitC_BO_Op_
#define xBitC_Data_
#define BitC_Op_ BitC_BO_A_
#include "bitcrux.c"
#undef BitC_Op_
#define BitC_Op_ BitC_BO_O_
#include "bitcrux.c"
#undef BitC_Op_
#define BitC_Op_ BitC_BO_X_
#include "bitcrux.c"
#undef BitC_Op_
#undef xBitC_Data_
#undef xBitC_BO_Op_
#endif
#endif

#if(Fold_(Relational Operation Functions))
#if(Fold_(BitC_RO_E_ N_))
#define xBitC_RO_Op_
#define xBitC_Data_
#define BitC_Op_ BitC_RO_E_
#include "bitcrux.c"
#undef BitC_Op_
#define BitC_Op_ BitC_RO_N_
#include "bitcrux.c"
#undef BitC_Op_
#undef xBitC_Data_
#undef xBitC_RO_Op_
#endif

#if(Fold_(BitC_RO_G_ L_))
#define xBitC_RO_Op_
#define xBitC_Data_
#define xBitC_Inte_
#define xBitC_Real_
#define BitC_Op_ BitC_RO_G_
#include "bitcrux.c"
#undef BitC_Op_
#define BitC_Op_ BitC_RO_L_
#include "bitcrux.c"
#undef BitC_Op_
#undef xBitC_Real_
#undef xBitC_Inte_
#undef xBitC_Data_
#undef xBitC_RO_Op_
#endif
#endif
