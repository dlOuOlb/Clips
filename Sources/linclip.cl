#include "linclip.h"

#if(Fold_(Definition:LinCrux Macros))
#include "lincros.c"
#endif

#if(Fold_(Definition:Internal Functions))
_F_ oclclip LinC_From_(_P_ oclclip Amount,_P_ OCLC_PA Axis)
{
	_P_ oclclip Where;

	Amount.S[Axis]=1;

	Where.X=Work_Here_B_(0);
	Where.Y=Where.X/Amount.X;
	Where.Z=Where.Y/Amount.Y;
	Where.N=Where.Z/Amount.Z;
	Where.Z%=Amount.Z;
	Where.Y%=Amount.Y;
	Where.X%=Amount.X;

	return Where;
}
#endif

#if(Fold_(Definition:Increment and Amplification Functions))
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

#if(Fold_(Definition:Addition and Subtraction and Multiplication Functions))
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

#if(Fold_(Definition:Division Functions))
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

#if(Fold_(Definition:Modulo Functions))
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

#if(Fold_(Definition:Summation and Dot-Product Functions))
#define _LinC_Summation_
#define _LinC_Inte_
#define _LinC_Real_
#include "lincrux.c"
#undef _LinC_Real_
#undef _LinC_Inte_
#undef _LinC_Summation_
#endif

#if(Fold_(Definition:Maximum and Minimum Functions))
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

#if(Fold_(Definition:Mapping Functions))
#define _LinC_Mapping_
#define _LinC_Data_
#include "lincrux.c"
#undef _LinC_Data_
#undef _LinC_Mapping_
#endif

#if(Fold_(Undefinition:LinCrux Macros))
#include "lincros.c"
#endif
