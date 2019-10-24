#ifdef _INC_BITCLIP
#ifdef _SRC_BITCROS

#undef BitC_RO_L_
#undef BitC_RO_G_
#undef BitC_RO_N_
#undef BitC_RO_E_

#undef BitC_BO_X_
#undef BitC_BO_O_
#undef BitC_BO_A_
#undef BitC_BO_N_

#undef BitC_Oper_
#undef _BitC_Oper_

#undef BitC_Cast_
#undef _BitC_Cast_

#undef BitC_Func_
#undef _BitC_Func_

#undef BitC_Type_
#undef _BitC_Type_

#undef BitC_TXX_
#undef BitC_XX_

#undef _SRC_BITCROS

#else

#define _SRC_BITCROS

#define BitC_XX_(Bits) ((_Conc_(1,Bits))-(_Conc_(1,00)))
#define BitC_TXX_(Type,Bits) _Conc_(Type,Bits)

#define _BitC_Type_(Type,Bits) Type##_##Bits
#define BitC_Type_(Type,Bits) _BitC_Type_(Type,Bits)

#define _BitC_Func_(Name,Suffix) Name##Suffix##_
#define BitC_Func_(Name,Suffix) _BitC_Func_(Name,Suffix)

#define _BitC_Cast_(Source,Target) BitC_Caster_##Source##_##Target##_
#define BitC_Cast_(Source,Target) _BitC_Cast_(Source,Target)

#define _BitC_Oper_(Oper,N,TXX) Oper##N##_##TXX##_
#define BitC_Oper_(Oper,N,TXX) _BitC_Oper_(Oper,N,TXX)

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
#ifdef __OPENCL_VERSION__
#error This template cannot be built directly.
#else
static void _BitC_Void_(void) { (void)(_BitC_Void_);return; }
#endif
#endif
