

#if !defined (_IOConsts_H)
#   define _IOConsts_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_IOConsts_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef enum {IOConsts_notKnown, IOConsts_allRight, IOConsts_outOfRange, IOConsts_wrongFormat, IOConsts_endOfLine, IOConsts_endOfInput} IOConsts_ReadResults;

#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
