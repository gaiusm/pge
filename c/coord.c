/* automatically created by mc from ../git-pge/m2/coord.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   define SYSTEM_BITSPERBYTE 8
#   define SYSTEM_BYTESPERWORD 4
typedef struct coord_Coord_r coord_Coord;

struct coord_Coord_r {
                       double x;
                       double y;
                     };

void SYSTEM_ShiftVal (unsigned int *s, unsigned int _s_high, unsigned int *d, unsigned int _d_high, unsigned int SetSizeInBits, int ShiftCount);
void SYSTEM_ShiftLeft (unsigned int *s, unsigned int _s_high, unsigned int *d, unsigned int _d_high, unsigned int SetSizeInBits, unsigned int ShiftCount);
void SYSTEM_ShiftRight (unsigned int *s, unsigned int _s_high, unsigned int *d, unsigned int _d_high, unsigned int SetSizeInBits, unsigned int ShiftCount);
void SYSTEM_RotateVal (unsigned int *s, unsigned int _s_high, unsigned int *d, unsigned int _d_high, unsigned int SetSizeInBits, int RotateCount);
void SYSTEM_RotateLeft (unsigned int *s, unsigned int _s_high, unsigned int *d, unsigned int _d_high, unsigned int SetSizeInBits, unsigned int RotateCount);
void SYSTEM_RotateRight (unsigned int *s, unsigned int _s_high, unsigned int *d, unsigned int _d_high, unsigned int SetSizeInBits, unsigned int RotateCount);
void M2RTS_ExecuteTerminationProcedures (void);
unsigned int M2RTS_InstallTerminationProcedure (PROC p);
void M2RTS_ExecuteInitialProcedures (void);
unsigned int M2RTS_InstallInitialProcedure (PROC p);
void M2RTS_Terminate (void);
void M2RTS_HALT (int exitcode);
void M2RTS_Halt (char *file_, unsigned int _file_high, unsigned int line, char *function_, unsigned int _function_high, char *description_, unsigned int _description_high);
void M2RTS_ExitOnHalt (int e);
void M2RTS_ErrorMessage (char *message_, unsigned int _message_high, char *file_, unsigned int _file_high, unsigned int line, char *function_, unsigned int _function_high);
unsigned int M2RTS_Length (char *a_, unsigned int _a_high);
void M2RTS_AssignmentException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_ReturnException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_IncException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_DecException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_InclException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_ExclException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_ShiftException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_RotateException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_StaticArraySubscriptException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_DynamicArraySubscriptException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_ForLoopBeginException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_ForLoopToException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_ForLoopEndException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_PointerNilException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_NoReturnException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_CaseException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_WholeNonPosDivException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_WholeNonPosModException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_WholeZeroDivException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_WholeZeroRemException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_WholeValueException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_RealValueException (void * filename, unsigned int line, unsigned int column, void * scope);
void M2RTS_NoException (void * filename, unsigned int line, unsigned int column, void * scope);

/*
   initCoord - initialises a coordinate pair.
*/

coord_Coord coord_initCoord (double x, double y);

/*
   normaliseCoord - return a Coord whose length is 1.
*/

coord_Coord coord_normaliseCoord (coord_Coord c);

/*
   perpendiculars - fill in c1 and c2 which are the two perpendicular values to, c.
*/

void coord_perpendiculars (coord_Coord c, coord_Coord *c1, coord_Coord *c2);

/*
   perpendicular - return the perpendicular of, c.
                   This is the one defined by Hill 1994 where, c, is rotated
                   90 degrees anticlockwise.
*/

coord_Coord coord_perpendicular (coord_Coord c);

/*
   scaleCoord - scale the coord, c, by, s.
*/

coord_Coord coord_scaleCoord (coord_Coord c, double s);

/*
   negateCoord - negates both components of the vector, c.
*/

coord_Coord coord_negateCoord (coord_Coord c);

/*
   subCoord - returns a - b.
*/

coord_Coord coord_subCoord (coord_Coord a, coord_Coord b);

/*
   addCoord - returns a + b.
*/

coord_Coord coord_addCoord (coord_Coord a, coord_Coord b);

/*
   lengthCoord - returns sqrt(c.x*c.x + c.y*c.y)
*/

double coord_lengthCoord (coord_Coord c);

/*
   rotateCoord - rotate point, c, about the origin at theta radians.
*/

coord_Coord coord_rotateCoord (coord_Coord c, double theta);

/*
   dotProd - performs a dot product of, a, and, b.
*/

double coord_dotProd (coord_Coord a, coord_Coord b);

/*
   nearZeroCoord - returns TRUE if, a, is very close to (0, 0)
*/

unsigned int coord_nearZeroCoord (coord_Coord a);

/*
   equalCoord - return true if a == b.  (very closely equal).
*/

unsigned int coord_equalCoord (coord_Coord a, coord_Coord b);

/*
   projectVector - returns the vector, onto, after it has been
                   projected by, project.
*/

coord_Coord coord_projectVector (coord_Coord project, coord_Coord onto);
double libm_sin (double x);
long double libm_sinl (long double x);
float libm_sinf (float x);
double libm_cos (double x);
long double libm_cosl (long double x);
float libm_cosf (float x);
double libm_tan (double x);
long double libm_tanl (long double x);
float libm_tanf (float x);
double libm_sqrt (double x);
long double libm_sqrtl (long double x);
float libm_sqrtf (float x);
double libm_asin (double x);
long double libm_asinl (long double x);
float libm_asinf (float x);
double libm_acos (double x);
long double libm_acosl (long double x);
float libm_acosf (float x);
double libm_atan (double x);
long double libm_atanl (long double x);
float libm_atanf (float x);
double libm_atan2 (double x, double y);
long double libm_atan2l (long double x, long double y);
float libm_atan2f (float x, float y);
double libm_exp (double x);
long double libm_expl (long double x);
float libm_expf (float x);
double libm_log (double x);
long double libm_logl (long double x);
float libm_logf (float x);
double libm_exp10 (double x);
long double libm_exp10l (long double x);
float libm_exp10f (float x);
double libm_pow (double x, double y);
long double libm_powl (long double x, long double y);
float libm_powf (float x, float y);
double libm_floor (double x);
long double libm_floorl (long double x);
float libm_floorf (float x);
double libm_ceil (double x);
long double libm_ceill (long double x);
float libm_ceilf (float x);
unsigned int roots_findOctic (double a, double b, double c, double d, double e, double f, double g, double h, double i, double *x0);
unsigned int roots_findQuadratic (double a, double b, double c, double *x0, double *x1);
unsigned int roots_findQuadraticRoots (double a, double b, double c, double *x, unsigned int _x_high);
unsigned int roots_findQuartic (double a, double b, double c, double d, double e, double *x);
unsigned int roots_findQuarticRoots (double a, double b, double c, double d, double e, double *x, unsigned int _x_high);
unsigned int roots_findAllRootsQuartic (double a, double b, double c, double d, double e, double *x, unsigned int _x_high);
unsigned int roots_nearZero (double r);
unsigned int roots_nearSame (double a, double b);
unsigned int roots_nearCoord (coord_Coord a, coord_Coord b);
void roots_setTrace (unsigned int on);


/*
   initCoord - initialises a coordinate pair.
*/

coord_Coord coord_initCoord (double x, double y)
{
  coord_Coord c;

  c.x = x;
  c.y = y;
  return c;
}


/*
   normaliseCoord - return a Coord whose length is 1.
*/

coord_Coord coord_normaliseCoord (coord_Coord c)
{
  double h;

  h = coord_lengthCoord (c);
  if (roots_nearZero (h))
    h = 1.0;
  c.x = c.x/h;
  c.y = c.y/h;
  return c;
}


/*
   perpendiculars - fill in c1 and c2 which are the two perpendicular values to, c.
*/

void coord_perpendiculars (coord_Coord c, coord_Coord *c1, coord_Coord *c2)
{
  (*c1) = coord_initCoord (-c.y, c.x);
  (*c2) = coord_initCoord (c.y, -c.x);
}


/*
   perpendicular - return the perpendicular of, c.
                   This is the one defined by Hill 1994 where, c, is rotated
                   90 degrees anticlockwise.
*/

coord_Coord coord_perpendicular (coord_Coord c)
{
  return coord_initCoord (-c.y, c.x);
}


/*
   scaleCoord - scale the coord, c, by, s.
*/

coord_Coord coord_scaleCoord (coord_Coord c, double s)
{
  c.x = c.x*s;
  c.y = c.y*s;
  return c;
}


/*
   negateCoord - negates both components of the vector, c.
*/

coord_Coord coord_negateCoord (coord_Coord c)
{
  return coord_initCoord (-c.x, -c.y);
}


/*
   subCoord - returns a - b.
*/

coord_Coord coord_subCoord (coord_Coord a, coord_Coord b)
{
  return coord_initCoord (a.x-b.x, a.y-b.y);
}


/*
   addCoord - returns a + b.
*/

coord_Coord coord_addCoord (coord_Coord a, coord_Coord b)
{
  return coord_initCoord (a.x+b.x, a.y+b.y);
}


/*
   lengthCoord - returns sqrt(c.x*c.x + c.y*c.y)
*/

double coord_lengthCoord (coord_Coord c)
{
  return libm_sqrt ((c.x*c.x)+(c.y*c.y));
}


/*
   rotateCoord - rotate point, c, about the origin at theta radians.
*/

coord_Coord coord_rotateCoord (coord_Coord c, double theta)
{
  return coord_initCoord ((c.x*(libm_cos (theta)))-(c.y*(libm_sin (theta))), (c.x*(libm_sin (theta)))+(c.y*(libm_cos (theta))));
}


/*
   dotProd - performs a dot product of, a, and, b.
*/

double coord_dotProd (coord_Coord a, coord_Coord b)
{
  return (a.x*b.x)+(a.y*b.y);
}


/*
   nearZeroCoord - returns TRUE if, a, is very close to (0, 0)
*/

unsigned int coord_nearZeroCoord (coord_Coord a)
{
  return (roots_nearZero (a.x)) && (roots_nearZero (a.y));
}


/*
   equalCoord - return true if a == b.  (very closely equal).
*/

unsigned int coord_equalCoord (coord_Coord a, coord_Coord b)
{
  return coord_nearZeroCoord (coord_subCoord (a, b));
}


/*
   projectVector - returns the vector, onto, after it has been
                   projected by, project.
*/

coord_Coord coord_projectVector (coord_Coord project, coord_Coord onto)
{
  double dp;
  double d;

  d = coord_dotProd (onto, onto);
  /* if angle of onto is < 90 degrees.  */
  if (d > 0.0)
    {
      dp = coord_dotProd (project, onto);
      return coord_scaleCoord (onto, dp/d);
    }
  return onto;
}

void _M2_coord_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_coord_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
