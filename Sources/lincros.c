#ifdef _INC_LINCLIP
#ifdef _SRC_BITCROS

#undef LinC_Min_
#undef LinC_Max_
#undef LinC_Mod_
#undef LinC_Inv_
#undef LinC_Div_
#undef LinC_Mul_
#undef LinC_Sub_
#undef LinC_Add_
#undef LinC_Amp_
#undef LinC_Inc_
#undef LinC_Geo_
#undef LinC_Ari_

#undef LinC_Oper_
#undef _LinC_Oper_

#undef LinC_Func_
#undef _LinC_Func_

#undef LinC_Type_
#undef _LinC_Type_

#undef LinC_TXX_

#undef _SRC_BITCROS

#else

#define _SRC_BITCROS

#define LinC_TXX_(Type,Bits) _Conc_(Type,Bits)

#define _LinC_Type_(Type,Bits) Type##_##Bits
#define LinC_Type_(Type,Bits) _LinC_Type_(Type,Bits)

#define _LinC_Func_(Name,Suffix) Name##Suffix##_
#define LinC_Func_(Name,Suffix) _LinC_Func_(Name,Suffix)

#define _LinC_Oper_(Oper,N,TXX) Oper##N##_##TXX##_
#define LinC_Oper_(Oper,N,TXX) _LinC_Oper_(Oper,N,TXX)

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
#ifdef __OPENCL_VERSION__
#error This template cannot be built directly.
#else
static void _LinC_Void_(void) { (void)(_LinC_Void_);return; }
#endif
#endif
