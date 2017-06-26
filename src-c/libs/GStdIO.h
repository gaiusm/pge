/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/StdIO.def.  */


#if !defined (_StdIO_H)
#   define _StdIO_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_StdIO_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef struct StdIO_ProcWrite_p StdIO_ProcWrite;

typedef struct StdIO_ProcRead_p StdIO_ProcRead;

typedef void (*StdIO_ProcWrite_t) (char);
struct StdIO_ProcWrite_p { StdIO_ProcWrite_t proc; };

typedef void (*StdIO_ProcRead_t) (char *);
struct StdIO_ProcRead_p { StdIO_ProcRead_t proc; };


/*
   Read - is the generic procedure that all higher application layers
          should use to receive a character.
*/

EXTERN void StdIO_Read (char *ch);

/*
   Write - is the generic procedure that all higher application layers
           should use to emit a character.
*/

EXTERN void StdIO_Write (char ch);

/*
   PushOutput - pushes the current Write procedure onto a stack,
                any future references to Write will actually invoke
                procedure, p.
*/

EXTERN void StdIO_PushOutput (StdIO_ProcWrite p);

/*
   PopOutput - restores Write to use the previous output procedure.
*/

EXTERN void StdIO_PopOutput (void);

/*
   GetCurrentOutput - returns the current output procedure.
*/

EXTERN StdIO_ProcWrite StdIO_GetCurrentOutput (void);

/*
   PushInput - pushes the current Read procedure onto a stack,
               any future references to Read will actually invoke
               procedure, p.
*/

EXTERN void StdIO_PushInput (StdIO_ProcRead p);

/*
   PopInput - restores Write to use the previous output procedure.
*/

EXTERN void StdIO_PopInput (void);

/*
   GetCurrentInput - returns the current input procedure.
*/

EXTERN StdIO_ProcRead StdIO_GetCurrentInput (void);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
