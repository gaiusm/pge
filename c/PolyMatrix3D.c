/* automatically created by mc from ../git-pge/m2/PolyMatrix3D.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   if !defined (FALSE)
#      define FALSE (1==0)
#   endif

#include <stddef.h>
#define _PolyMatrix3D_H
#define _PolyMatrix3D_C

#   include "GSYSTEM.h"
#   include "Glibc.h"
#   include "GAssertion.h"
#   include "GStrIO.h"
#   include "GASCII.h"
#   include "GDynamicStrings.h"
#   include "GGC.h"
#   include "GFractions.h"

#   define PolyMatrix3D_MaxDimension 3
typedef struct PolyMatrix3D_MatrixValue_a PolyMatrix3D_MatrixValue;

typedef struct PolyMatrix3D__T2_a PolyMatrix3D__T2;

#   define PoisonOn FALSE
#   define DebugOn FALSE
#   define CheckOn FALSE
#   define TraceOn FALSE
typedef struct _T1_r _T1;

typedef _T1 *PolyMatrix3D_Matrix;

struct PolyMatrix3D__T2_a { Fractions_Fract array[PolyMatrix3D_MaxDimension-1+1]; };
struct PolyMatrix3D_MatrixValue_a { PolyMatrix3D__T2 array[PolyMatrix3D_MaxDimension-1+1]; };
struct _T1_r {
               PolyMatrix3D_MatrixValue value;
               GC_entity gentity;
             };

static GC_garbage matrixHeap;

/*
   init - creates an unrooted matrix and returns the matrix object.
*/

PolyMatrix3D_Matrix PolyMatrix3D_init (void);

/*
   mark - marks the matrix as used.
*/

PolyMatrix3D_Matrix PolyMatrix3D_mark (PolyMatrix3D_Matrix m);

/*
   root - grafts matrix into the roots of the garbage tree.
*/

PolyMatrix3D_Matrix PolyMatrix3D_root (PolyMatrix3D_Matrix m);

/*
   kill - removes, m, from the roots of the garbage tree.
*/

PolyMatrix3D_Matrix PolyMatrix3D_kill (PolyMatrix3D_Matrix m);

/*
   set - sets the elements of a Matrix with the values.
*/

PolyMatrix3D_Matrix PolyMatrix3D_set (PolyMatrix3D_Matrix m, PolyMatrix3D_MatrixValue v);

/*
   get - gets the elements of a Matrix into value MatrixValues.
*/

PolyMatrix3D_Matrix PolyMatrix3D_get (PolyMatrix3D_Matrix m, PolyMatrix3D_MatrixValue *v);

/*
   add - adds a and b together and returns the result.
*/

PolyMatrix3D_Matrix PolyMatrix3D_add (PolyMatrix3D_Matrix a, PolyMatrix3D_Matrix b);

/*
   mult - multiplies a and b together and returns the result.
*/

PolyMatrix3D_Matrix PolyMatrix3D_mult (PolyMatrix3D_Matrix a, PolyMatrix3D_Matrix b);

/*
   mult3 - performs a * (b * c) returns the result.
*/

PolyMatrix3D_Matrix PolyMatrix3D_mult3 (PolyMatrix3D_Matrix a, PolyMatrix3D_Matrix b, PolyMatrix3D_Matrix c);

/*
   dup - returns a copy of, m.
*/

PolyMatrix3D_Matrix PolyMatrix3D_dup (PolyMatrix3D_Matrix m);

/*
   eval - returns, m, after all values have been simplified.
*/

PolyMatrix3D_Matrix PolyMatrix3D_eval (PolyMatrix3D_Matrix m);

/*
   walkMatrix - walks the Matrix data structures, marking it as used.
*/

static void walkMatrix (PolyMatrix3D_Matrix m);

/*
   walkMatrixEntity - walks macro, m, associated with entity, e.
*/

static void walkMatrixEntity (GC_entity e);

/*
   Init - 
*/

static void Init (void);


/*
   walkMatrix - walks the Matrix data structures, marking it as used.
*/

static void walkMatrix (PolyMatrix3D_Matrix m)
{
  m = PolyMatrix3D_mark (m);
}


/*
   walkMatrixEntity - walks macro, m, associated with entity, e.
*/

static void walkMatrixEntity (GC_entity e)
{
  walkMatrix ((PolyMatrix3D_Matrix) GC_getData (e));
}


/*
   Init - 
*/

static void Init (void)
{
  PolyMatrix3D_Matrix m;

  matrixHeap = GC_initGarbage ((GC_walkP) {(GC_walkP_t) walkMatrixEntity}, (unsigned int) sizeof ((*m)), DynamicStrings_InitString ((char *) "matrices", 8));
}


/*
   init - creates an unrooted matrix and returns the matrix object.
*/

PolyMatrix3D_Matrix PolyMatrix3D_init (void)
{
  PolyMatrix3D_Matrix m;
  GC_entity e;
  unsigned int i;
  unsigned int j;

  GC_allocate (matrixHeap, &e, (void **) &m);
  m->gentity = e;
  for (j=1; j<=PolyMatrix3D_MaxDimension; j++)
    for (i=1; i<=PolyMatrix3D_MaxDimension; i++)
      m->value.array[i-1].array[j-1] = NULL;
  return m;
}


/*
   mark - marks the matrix as used.
*/

PolyMatrix3D_Matrix PolyMatrix3D_mark (PolyMatrix3D_Matrix m)
{
  unsigned int i;
  unsigned int j;

  GC_markEntity (m->gentity);
  for (i=1; i<=PolyMatrix3D_MaxDimension; i++)
    for (j=1; j<=PolyMatrix3D_MaxDimension; j++)
      /* and mark all its values  */
      Fractions_mark (m->value.array[i-1].array[j-1]);
  return m;
}


/*
   root - grafts matrix into the roots of the garbage tree.
*/

PolyMatrix3D_Matrix PolyMatrix3D_root (PolyMatrix3D_Matrix m)
{
  GC_rootEntity (matrixHeap, m->gentity, (void *) m);
  return m;
}


/*
   kill - removes, m, from the roots of the garbage tree.
*/

PolyMatrix3D_Matrix PolyMatrix3D_kill (PolyMatrix3D_Matrix m)
{
  GC_rootDeallocate (matrixHeap, &m->gentity, (void **) &m);
  return NULL;
}


/*
   set - sets the elements of a Matrix with the values.
*/

PolyMatrix3D_Matrix PolyMatrix3D_set (PolyMatrix3D_Matrix m, PolyMatrix3D_MatrixValue v)
{
  m->value = v;
  return m;
}


/*
   get - gets the elements of a Matrix into value MatrixValues.
*/

PolyMatrix3D_Matrix PolyMatrix3D_get (PolyMatrix3D_Matrix m, PolyMatrix3D_MatrixValue *v)
{
  (*v) = m->value;
  return m;
}


/*
   add - adds a and b together and returns the result.
*/

PolyMatrix3D_Matrix PolyMatrix3D_add (PolyMatrix3D_Matrix a, PolyMatrix3D_Matrix b)
{
  unsigned int i;
  unsigned int j;
  PolyMatrix3D_Matrix m;

  m = PolyMatrix3D_init ();
  for (i=1; i<=PolyMatrix3D_MaxDimension; i++)
    for (j=1; j<=PolyMatrix3D_MaxDimension; j++)
      m->value.array[i-1].array[j-1] = Fractions_add (a->value.array[i-1].array[j-1], b->value.array[i-1].array[j-1]);
  return m;
}


/*
   mult - multiplies a and b together and returns the result.
*/

PolyMatrix3D_Matrix PolyMatrix3D_mult (PolyMatrix3D_Matrix a, PolyMatrix3D_Matrix b)
{
  unsigned int i;
  unsigned int j;
  PolyMatrix3D_Matrix m;

  m = PolyMatrix3D_init ();
  /* 1st row  */
  m->value.array[1-1].array[1-1] = Fractions_add3 (Fractions_mult (a->value.array[1-1].array[1-1], b->value.array[1-1].array[1-1]), Fractions_mult (a->value.array[1-1].array[2-1], b->value.array[2-1].array[1-1]), Fractions_mult (a->value.array[1-1].array[3-1], b->value.array[3-1].array[1-1]));
  m->value.array[1-1].array[2-1] = Fractions_add3 (Fractions_mult (a->value.array[1-1].array[1-1], b->value.array[1-1].array[2-1]), Fractions_mult (a->value.array[1-1].array[2-1], b->value.array[2-1].array[2-1]), Fractions_mult (a->value.array[1-1].array[3-1], b->value.array[3-1].array[2-1]));
  m->value.array[1-1].array[3-1] = Fractions_add3 (Fractions_mult (a->value.array[1-1].array[1-1], b->value.array[1-1].array[3-1]), Fractions_mult (a->value.array[1-1].array[2-1], b->value.array[2-1].array[3-1]), Fractions_mult (a->value.array[1-1].array[3-1], b->value.array[3-1].array[3-1]));
  /* 2nd row  */
  m->value.array[2-1].array[1-1] = Fractions_add3 (Fractions_mult (a->value.array[2-1].array[1-1], b->value.array[1-1].array[1-1]), Fractions_mult (a->value.array[2-1].array[2-1], b->value.array[2-1].array[1-1]), Fractions_mult (a->value.array[2-1].array[3-1], b->value.array[3-1].array[1-1]));
  m->value.array[2-1].array[2-1] = Fractions_add3 (Fractions_mult (a->value.array[2-1].array[1-1], b->value.array[1-1].array[2-1]), Fractions_mult (a->value.array[2-1].array[2-1], b->value.array[2-1].array[2-1]), Fractions_mult (a->value.array[2-1].array[3-1], b->value.array[3-1].array[2-1]));
  m->value.array[2-1].array[3-1] = Fractions_add3 (Fractions_mult (a->value.array[2-1].array[1-1], b->value.array[1-1].array[3-1]), Fractions_mult (a->value.array[2-1].array[2-1], b->value.array[2-1].array[3-1]), Fractions_mult (a->value.array[2-1].array[3-1], b->value.array[3-1].array[3-1]));
  /* 3rd row  */
  m->value.array[3-1].array[1-1] = Fractions_add3 (Fractions_mult (a->value.array[3-1].array[1-1], b->value.array[1-1].array[1-1]), Fractions_mult (a->value.array[3-1].array[2-1], b->value.array[2-1].array[1-1]), Fractions_mult (a->value.array[3-1].array[3-1], b->value.array[3-1].array[1-1]));
  m->value.array[3-1].array[2-1] = Fractions_add3 (Fractions_mult (a->value.array[3-1].array[1-1], b->value.array[1-1].array[2-1]), Fractions_mult (a->value.array[3-1].array[2-1], b->value.array[2-1].array[2-1]), Fractions_mult (a->value.array[3-1].array[3-1], b->value.array[3-1].array[2-1]));
  m->value.array[3-1].array[3-1] = Fractions_add3 (Fractions_mult (a->value.array[3-1].array[1-1], b->value.array[1-1].array[3-1]), Fractions_mult (a->value.array[3-1].array[2-1], b->value.array[2-1].array[3-1]), Fractions_mult (a->value.array[3-1].array[3-1], b->value.array[3-1].array[3-1]));
  return m;
}


/*
   mult3 - performs a * (b * c) returns the result.
*/

PolyMatrix3D_Matrix PolyMatrix3D_mult3 (PolyMatrix3D_Matrix a, PolyMatrix3D_Matrix b, PolyMatrix3D_Matrix c)
{
  return PolyMatrix3D_mult (a, PolyMatrix3D_mult (b, c));
}


/*
   dup - returns a copy of, m.
*/

PolyMatrix3D_Matrix PolyMatrix3D_dup (PolyMatrix3D_Matrix m)
{
  PolyMatrix3D_Matrix n;
  unsigned int i;
  unsigned int j;

  n = PolyMatrix3D_init ();
  for (i=1; i<=PolyMatrix3D_MaxDimension; i++)
    for (j=1; j<=PolyMatrix3D_MaxDimension; j++)
      n->value.array[i-1].array[j-1] = Fractions_dup (m->value.array[i-1].array[j-1]);
  return n;
}


/*
   eval - returns, m, after all values have been simplified.
*/

PolyMatrix3D_Matrix PolyMatrix3D_eval (PolyMatrix3D_Matrix m)
{
  unsigned int i;
  unsigned int j;

  for (i=1; i<=PolyMatrix3D_MaxDimension; i++)
    for (j=1; j<=PolyMatrix3D_MaxDimension; j++)
      m->value.array[i-1].array[j-1] = Fractions_simplify (m->value.array[i-1].array[j-1]);
  return m;
}

void _M2_PolyMatrix3D_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  Init ();
}

void _M2_PolyMatrix3D_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
