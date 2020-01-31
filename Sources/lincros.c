#ifdef oLINCLIP_INC_

#ifndef xBITCROS_SRC_
#define xBITCROS_SRC_

#define LinC_TXX_(Type,Bits) Conc_(Type,Bits)

#define LinC_Type_(Type,Bits) xLinC_Type_(Type,Bits)
#define xLinC_Type_(Type,Bits) Type##_##Bits

#define LinC_Func_(Name,Suffix) xLinC_Func_(Name,Suffix)
#define xLinC_Func_(Name,Suffix) Name##Suffix##_

#define LinC_Oper_(Oper,N,TXX) xLinC_Oper_(Oper,N,TXX)
#define xLinC_Oper_(Oper,N,TXX) Oper##N##_##TXX##_

#define LinC_Ari_(U,V) ((U)+(V))
#define LinC_Geo_(U,V) ((U)*(V))
#define LinC_Inc_(U,V) ((U)+(V))
#define LinC_Amp_(U,V) ((U)*(V))
#define LinC_Add_(U,V) ((U)+(V))
#define LinC_Sub_(U,V) ((U)-(V))
#define LinC_Mul_(U,V) ((U)*(V))
#define LinC_Div_(U,V) ((U)/(V))
#define LinC_Inv_(U,V) ((V)/(U))
#define LinC_Mod_(U,V) ((U)%(V))
#define LinC_Max_(U,V) ((U)<(V))
#define LinC_Min_(U,V) ((U)>(V))
#endif

#else
#error Do not build this template directly.
#endif
