/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/Debug.def.  */


#if !defined (_Debug_H)
#   define _Debug_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_Debug_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif


/*
   Halt - writes a message in the format:
          Module:Line:Message

          It then terminates by calling HALT.
*/

EXTERN void Debug_Halt (char *Message_, unsigned int _Message_high, unsigned int LineNo, char *Module_, unsigned int _Module_high);

/*
   DebugString - writes a string to the debugging device (Scn.Write).
                 It interprets 
 as carriage return, linefeed.
*/

EXTERN void Debug_DebugString (char *a_, unsigned int _a_high);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
