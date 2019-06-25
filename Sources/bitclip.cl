#include "bitclip.h"

#if(Fold_(Definition:BitCrux Macros))
#include "bitcros.c"
#endif

#if(Fold_(Definition:Endian Functions))
_K_ BitC_Endian_D16_(_G_ data_16 _PL_ Data,_P_ OCLCLIP Start,_P_ OCLCLIP Amount,_P_ OCLCLIP Shape)
{
	_P_ ADDRESS Index=Work_Into_(Work_From_(Amount),Start,Shape);
	_P_ data_08 Buffer[4];
	_P_ bitc_pp Peek;Peek.C.D08=Buffer;
	
	Peek.V.D16[0]=Data[Index];
	Peek.V.D08[2]=Peek.C.D08[1];
	Peek.V.D08[3]=Peek.C.D08[0];
	Data[Index]=Peek.C.D16[1];
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
}
#endif

#if(Fold_(Definition:Reformation Functions))
#define _BitC_Copy_
#define _BitC_Data_
#include "bitcrux.c"
#undef _BitC_Data_
#undef _BitC_Copy_
#endif

#if(Fold_(Definition:Caster Functions))
#define _BitC_Caster_
#include "bitcrux.c"
#undef _BitC_Caster_
#endif

#if(Fold_(Definition:Bit Operation Functions))
#if(Fold_(Part:BitC_BO_N_1_))
#define _BitC_BO_N_1_
#define BitC_Op_ BitC_BO_N_
#define _BitC_Data_
#include "bitcrux.c"
#undef _BitC_Data_
#undef BitC_Op_
#undef _BitC_BO_N_1_
#endif

#if(Fold_(Part:BitC_BO_S_1_))
#define _BitC_BO_S_1_
#define BitC_Op_ BitC_BO_S_
#define _BitC_Data_
#define _BitC_Inte_
#include "bitcrux.c"
#undef _BitC_Inte_
#undef _BitC_Data_
#undef BitC_Op_
#undef _BitC_BO_S_1_
#endif

#if(Fold_(Part:BitC_BO_A_ O_ X_))
#define _BitC_BO_Op_
#define _BitC_Data_
#define BitC_Op_ BitC_BO_A_
#include "bitcrux.c"
#undef BitC_Op_
#define BitC_Op_ BitC_BO_O_
#include "bitcrux.c"
#undef BitC_Op_
#define BitC_Op_ BitC_BO_X_
#include "bitcrux.c"
#undef BitC_Op_
#undef _BitC_Data_
#undef _BitC_BO_Op_
#endif
#endif

#if(Fold_(Definition:Relational Operation Functions))
#if(Fold_(Part:BitC_RO_E_ N_))
#define _BitC_RO_Op_
#define _BitC_Data_
#define BitC_Op_ BitC_RO_E_
#include "bitcrux.c"
#undef BitC_Op_
#define BitC_Op_ BitC_RO_N_
#include "bitcrux.c"
#undef BitC_Op_
#undef _BitC_Data_
#undef _BitC_RO_Op_
#endif

#if(Fold_(Part:BitC_RO_G_ L_))
#define _BitC_RO_Op_
#define _BitC_Data_
#define _BitC_Inte_
#define _BitC_Real_
#define BitC_Op_ BitC_RO_G_
#include "bitcrux.c"
#undef BitC_Op_
#define BitC_Op_ BitC_RO_L_
#include "bitcrux.c"
#undef BitC_Op_
#undef _BitC_Real_
#undef _BitC_Inte_
#undef _BitC_Data_
#undef _BitC_RO_Op_
#endif
#endif

#if(Fold_(Undefinition:BitCrux Macros))
#include "bitcros.c"
#endif
