/* automatically created by mc from ../PolyMath.def.  */


#if !defined (_PolyMath_H)
#   define _PolyMath_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_PolyMath_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#if !defined (PolyMath_Poly_D)
#  define PolyMath_Poly_D
   typedef void *PolyMath_Poly;
#endif

#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
