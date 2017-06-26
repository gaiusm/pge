/* automatically created by mc from ../PolyMatrix3D.def.  */


#if !defined (_PolyMatrix3D_H)
#   define _PolyMatrix3D_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GFractions.h"

#   if defined (_PolyMatrix3D_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#   define PolyMatrix3D_MaxDimension 3
#if !defined (PolyMatrix3D_Matrix_D)
#  define PolyMatrix3D_Matrix_D
   typedef void *PolyMatrix3D_Matrix;
#endif

typedef struct PolyMatrix3D_MatrixValue_a PolyMatrix3D_MatrixValue;

typedef struct PolyMatrix3D__T1_a PolyMatrix3D__T1;

struct PolyMatrix3D__T1_a { Fractions_Fract array[PolyMatrix3D_MaxDimension-1+1]; };
struct PolyMatrix3D_MatrixValue_a { PolyMatrix3D__T1 array[PolyMatrix3D_MaxDimension-1+1]; };

/*
   init - creates a matrix and returns the matrix object.
*/

EXTERN PolyMatrix3D_Matrix PolyMatrix3D_init (void);

/*
   mark - marks the matrix as used.
*/

EXTERN PolyMatrix3D_Matrix PolyMatrix3D_mark (PolyMatrix3D_Matrix m);

/*
   root - grafts matrix into the roots of the garbage tree.
*/

EXTERN PolyMatrix3D_Matrix PolyMatrix3D_root (PolyMatrix3D_Matrix m);

/*
   kill - removes, m, from the roots of the garbage tree.
*/

EXTERN PolyMatrix3D_Matrix PolyMatrix3D_kill (PolyMatrix3D_Matrix m);

/*
   set - sets the elements of a Matrix with the values.
*/

EXTERN PolyMatrix3D_Matrix PolyMatrix3D_set (PolyMatrix3D_Matrix m, PolyMatrix3D_MatrixValue v);

/*
   get - gets the elements of a Matrix into value MatrixValues.
*/

EXTERN PolyMatrix3D_Matrix PolyMatrix3D_get (PolyMatrix3D_Matrix m, PolyMatrix3D_MatrixValue *v);

/*
   add - adds a and b together and returns the result in a new
         Matrix.  a and b will be garbage collected if they
         are marked.
*/

EXTERN PolyMatrix3D_Matrix PolyMatrix3D_add (PolyMatrix3D_Matrix a, PolyMatrix3D_Matrix b);

/*
   mult - multiplies a and b together and returns the result
          in a new Matrix.
          a and b will be garbage collected if they are marked.
*/

EXTERN PolyMatrix3D_Matrix PolyMatrix3D_mult (PolyMatrix3D_Matrix a, PolyMatrix3D_Matrix b);

/*
   mult3 - performs a * (b * c) returns the result.
*/

EXTERN PolyMatrix3D_Matrix PolyMatrix3D_mult3 (PolyMatrix3D_Matrix a, PolyMatrix3D_Matrix b, PolyMatrix3D_Matrix c);

/*
   dup - returns another copy of matrix, m.
*/

EXTERN PolyMatrix3D_Matrix PolyMatrix3D_dup (PolyMatrix3D_Matrix m);

/*
   eval - returns, m, after all values have been simplified.
*/

EXTERN PolyMatrix3D_Matrix PolyMatrix3D_eval (PolyMatrix3D_Matrix m);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
