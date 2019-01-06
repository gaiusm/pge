/* automatically created by mc from /home/gaius/GM2/graft-8.2.0/gcc-8.2.0/gcc/gm2/gm2-libs/Indexing.def.  */


#if !defined (_Indexing_H)
#   define _Indexing_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_Indexing_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#if !defined (Indexing_Index_D)
#  define Indexing_Index_D
   typedef void *Indexing_Index;
#endif

typedef struct Indexing_IndexProcedure_p Indexing_IndexProcedure;

typedef void (*Indexing_IndexProcedure_t) (void *);
struct Indexing_IndexProcedure_p { Indexing_IndexProcedure_t proc; };


/*
   InitIndex - creates and returns an Index.
*/

EXTERN Indexing_Index Indexing_InitIndex (unsigned int low);

/*
   KillIndex - returns Index to free storage.
*/

EXTERN Indexing_Index Indexing_KillIndex (Indexing_Index i);

/*
   DebugIndex - turns on debugging within an index.
*/

EXTERN Indexing_Index Indexing_DebugIndex (Indexing_Index i);

/*
   InBounds - returns TRUE if indice, n, is within the bounds
              of the dynamic array.
*/

EXTERN unsigned int Indexing_InBounds (Indexing_Index i, unsigned int n);

/*
   HighIndice - returns the last legally accessible indice of this array.
*/

EXTERN unsigned int Indexing_HighIndice (Indexing_Index i);

/*
   LowIndice - returns the first legally accessible indice of this array.
*/

EXTERN unsigned int Indexing_LowIndice (Indexing_Index i);

/*
   PutIndice - places, a, into the dynamic array at position i[n]
*/

EXTERN void Indexing_PutIndice (Indexing_Index i, unsigned int n, void * a);

/*
   GetIndice - retrieves, element i[n] from the dynamic array.
*/

EXTERN void * Indexing_GetIndice (Indexing_Index i, unsigned int n);

/*
   IsIndiceInIndex - returns TRUE if, a, is in the index, i.
*/

EXTERN unsigned int Indexing_IsIndiceInIndex (Indexing_Index i, void * a);

/*
   RemoveIndiceFromIndex - removes, a, from Index, i.
*/

EXTERN void Indexing_RemoveIndiceFromIndex (Indexing_Index i, void * a);

/*
   DeleteIndice - delete i[j] from the array.
*/

EXTERN void Indexing_DeleteIndice (Indexing_Index i, unsigned int j);

/*
   IncludeIndiceIntoIndex - if the indice is not in the index, then
                            add it at the end.
*/

EXTERN void Indexing_IncludeIndiceIntoIndex (Indexing_Index i, void * a);

/*
   ForeachIndiceInIndexDo - for each j indice of i, call procedure p(i[j])
*/

EXTERN void Indexing_ForeachIndiceInIndexDo (Indexing_Index i, Indexing_IndexProcedure p);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
