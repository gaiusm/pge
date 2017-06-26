/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/CmdArgs.def.  */


#if !defined (_CmdArgs_H)
#   define _CmdArgs_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_CmdArgs_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   GetArg - returns the nth argument from the command line, CmdLine
            the success of the operation is returned.
*/

EXTERN unsigned int CmdArgs_GetArg (char *CmdLine_, unsigned int _CmdLine_high, unsigned int n, char *Argi, unsigned int _Argi_high);

/*
   Narg - returns the number of arguments available from
          command line, CmdLine.
*/

EXTERN unsigned int CmdArgs_Narg (char *CmdLine_, unsigned int _CmdLine_high);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
