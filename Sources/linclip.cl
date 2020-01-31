#include "linclip.h"
#include "lincros.c"

#if(Fold_(Internal Functions))
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

#if(Fold_(Increment and Amplification Functions))
#define xLinC_Operation_1_
#define xLinC_Inte_
#define xLinC_Real_
#define LinC_Op_ LinC_Inc_
#include "lincrux.c"
#undef LinC_Op_
#define LinC_Op_ LinC_Amp_
#include "lincrux.c"
#undef LinC_Op_
#undef xLinC_Real_
#undef xLinC_Inte_
#undef xLinC_Operation_1_
#endif

#if(Fold_(Addition and Subtraction and Multiplication Functions))
#define xLinC_Operation_2_
#define xLinC_Inte_
#define xLinC_Real_
#define LinC_Op_ LinC_Add_
#include "lincrux.c"
#undef LinC_Op_
#define LinC_Op_ LinC_Sub_
#include "lincrux.c"
#undef LinC_Op_
#define LinC_Op_ LinC_Mul_
#include "lincrux.c"
#undef LinC_Op_
#undef xLinC_Real_
#undef xLinC_Inte_
#undef xLinC_Operation_2_
#endif

#if(Fold_(Division Functions))
#define xLinC_Operation_2_
#define LinC_Op_ LinC_Div_
#define xLinC_Data_
#define xLinC_Inte_
#define xLinC_Real_
#include "lincrux.c"
#undef xLinC_Real_
#undef xLinC_Operation_2_
#define xLinC_Operation_1_
#include "lincrux.c"
#undef LinC_Op_
#define LinC_Op_ LinC_Inv_
#define xLinC_Real_
#include "lincrux.c"
#undef xLinC_Real_
#undef xLinC_Inte_
#undef xLinC_Data_
#undef LinC_Op_
#undef xLinC_Operation_1_
#endif

#if(Fold_(Modulo Functions))
#define xLinC_Operation_1_
#define LinC_Op_ LinC_Mod_
#define xLinC_Data_
#define xLinC_Inte_
#include "lincrux.c"
#undef xLinC_Inte_
#undef xLinC_Data_
#undef LinC_Op_
#undef xLinC_Operation_1_
#endif

#if(Fold_(Summation and Dot-Product Functions))
#define xLinC_Summation_
#define xLinC_Inte_
#define xLinC_Real_
#include "lincrux.c"
#undef xLinC_Real_
#undef xLinC_Inte_
#undef xLinC_Summation_
#endif

#if(Fold_(Maximum and Minimum Functions))
#define xLinC_Min_Max_
#define xLinC_Data_
#define xLinC_Inte_
#define xLinC_Real_
#define LinC_Op_ LinC_Max_
#include "lincrux.c"
#undef LinC_Op_
#define LinC_Op_ LinC_Min_
#include "lincrux.c"
#undef LinC_Op_
#undef xLinC_Real_
#undef xLinC_Inte_
#undef xLinC_Data_
#undef xLinC_Min_Max_
#endif

#if(Fold_(Mapping Functions))
#define xLinC_Mapping_
#define xLinC_Data_
#include "lincrux.c"
#undef xLinC_Data_
#undef xLinC_Mapping_
#endif
