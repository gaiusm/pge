/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/ConvTypes.def.  */


#if !defined (_ConvTypes_H)
#   define _ConvTypes_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_ConvTypes_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef struct ConvTypes_ScanState_p ConvTypes_ScanState;

typedef enum {ConvTypes_strAllRight, ConvTypes_strOutOfRange, ConvTypes_strWrongFormat, ConvTypes_strEmpty} ConvTypes_ConvResults;

typedef enum {ConvTypes_padding, ConvTypes_valid, ConvTypes_invalid, ConvTypes_terminator} ConvTypes_ScanClass;

typedef void (*ConvTypes_ScanState_t) (char, ConvTypes_ScanClass *, ConvTypes_ScanState *);
struct ConvTypes_ScanState_p { ConvTypes_ScanState_t proc; };

#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
