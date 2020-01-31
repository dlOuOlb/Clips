#ifdef oBITCLIP_INC_

#ifndef xBITCROS_SRC_
#define xBITCROS_SRC_

#define BitC_XX_(Bits) ((Conc_(1,Bits))-(Conc_(1,00)))
#define BitC_TXX_(Type,Bits) Conc_(Type,Bits)

#define BitC_Type_(Type,Bits) xBitC_Type_(Type,Bits)
#define xBitC_Type_(Type,Bits) Type##_##Bits

#define BitC_Func_(Name,Suffix) xBitC_Func_(Name,Suffix)
#define xBitC_Func_(Name,Suffix) Name##Suffix##_

#define BitC_Cast_(Source,Target) xBitC_Cast_(Source,Target)
#define xBitC_Cast_(Source,Target) BitC_Caster_##Source##_##Target##_

#define BitC_Oper_(Oper,N,TXX) xBitC_Oper_(Oper,N,TXX)
#define xBitC_Oper_(Oper,N,TXX) Oper##N##_##TXX##_

#define BitC_BO_N_(U) (~(U))
#define BitC_BO_A_(U,V) ((U)&(V))
#define BitC_BO_O_(U,V) ((U)|(V))
#define BitC_BO_X_(U,V) ((U)^(V))

#define BitC_RO_E_(U,V) ((U)==(V))
#define BitC_RO_N_(U,V) ((U)!=(V))
#define BitC_RO_G_(U,V) ((U)>=(V))
#define BitC_RO_L_(U,V) ((U)<(V))
#endif

#else
#error Do not build this template directly.
#endif
