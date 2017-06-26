/* automatically created by mc from ../popWorld.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#include <string.h>
#include <limits.h>
typedef struct Points_Point_r Points_Point;

typedef unsigned int deviceIf_Colour;

#   define SYSTEM_BITSPERBYTE 8
typedef struct fract_r fract;

typedef fract *Fractions_Fract;

#   define SYSTEM_BYTESPERWORD 4
typedef struct _T2_r _T2;

typedef _T2 *macroObjects_Macro;

typedef struct _T3_r _T3;

typedef _T3 *Object;

typedef struct macroObjects_pProc_p macroObjects_pProc;

typedef struct macroObjects_cProc_p macroObjects_cProc;

typedef long int libc_time_t;

typedef struct libc_tm_r libc_tm;

typedef libc_tm *libc_ptrToTM;

typedef struct libc_timeb_r libc_timeb;

typedef struct GC_walkP_p GC_walkP;

typedef struct _T5_r _T5;

typedef _T5 *GC_garbage;

typedef struct GC_callP_p GC_callP;

typedef struct stringRecord_r stringRecord;

typedef stringRecord *DynamicStrings_String;

typedef struct Contents_r Contents;

typedef struct _T7_a _T7;

#   define ASCII_nul (char) 000
#   define ASCII_soh (char) 001
#   define ASCII_stx (char) 002
#   define ASCII_etx (char) 003
#   define ASCII_eot (char) 004
#   define ASCII_enq (char) 005
#   define ASCII_ack (char) 006
#   define ASCII_bel (char) 007
#   define ASCII_bs (char) 010
#   define ASCII_ht (char) 011
#   define ASCII_nl (char) 012
#   define ASCII_vt (char) 013
#   define ASCII_np (char) 014
#   define ASCII_cr (char) 015
#   define ASCII_so (char) 016
#   define ASCII_si (char) 017
#   define ASCII_dle (char) 020
#   define ASCII_dc1 (char) 021
#   define ASCII_dc2 (char) 022
#   define ASCII_dc3 (char) 023
#   define ASCII_dc4 (char) 024
#   define ASCII_nak (char) 025
#   define ASCII_syn (char) 026
#   define ASCII_etb (char) 027
#   define ASCII_can (char) 030
#   define ASCII_em (char) 031
#   define ASCII_sub (char) 032
#   define ASCII_esc (char) 033
#   define ASCII_fs (char) 034
#   define ASCII_gs (char) 035
#   define ASCII_rs (char) 036
#   define ASCII_us (char) 037
#   define ASCII_sp (char) 040
#   define ASCII_lf ASCII_nl
#   define ASCII_ff ASCII_np
#   define ASCII_eof ASCII_eot
#   define ASCII_tab ASCII_ht
#   define ASCII_del (char) 0177
#   define ASCII_EOL ASCII_nl
#   define PolyMatrix3D_MaxDimension 3
typedef struct PolyMatrix3D_MatrixValue_a PolyMatrix3D_MatrixValue;

typedef struct _T9_r _T9;

typedef _T9 *PolyMatrix3D_Matrix;

typedef struct { Fractions_Fract array[PolyMatrix3D_MaxDimension-1]; } PolyMatrix3D__T10;

typedef struct {
                   double x;
                   double y;
               } coord_Coord;

typedef struct Indexing_IndexProcedure_p Indexing_IndexProcedure;

typedef struct _T6_r _T6;

typedef _T6 *Indexing_Index;

#   define FPSgroff 80
#   define FPSpy 80
typedef enum {oFract, oAdd, oSub, oMult, oDiv, oNegate, oPower, oSin, oCos, oTan} Operator;

typedef enum {NONE, PI, E, ROOT2, ROOT3, ROOT6, EXPR} Special;

#   define maxPoints 10
typedef enum {tcircle, tpolygon} typeOfObject;

typedef struct Circle_r Circle;

typedef enum {history_corner, history_edge} history_whereHit;

#   define MaxBuf 127
struct Points_Point_r {
                        Fractions_Fract x;
                        Fractions_Fract y;
                      };

typedef void (*macroObjects_cProc_t) (Points_Point, unsigned int, Fractions_Fract, Fractions_Fract, deviceIf_Colour);
struct macroObjects_cProc_p { macroObjects_cProc_t proc; };

struct libc_tm_r {
                   int tm_sec;
                   int tm_min;
                   int tm_hour;
                   int tm_mday;
                   int tm_mon;
                   int tm_year;
                   int tm_wday;
                   int tm_yday;
                   int tm_isdst;
                   long int tm_gmtoff;
                   void *tm_zone;
                 };

struct libc_timeb_r {
                      libc_time_t time;
                      short unsigned int millitm;
                      short unsigned int timezone;
                      short unsigned int dstflag;
                    };

typedef void (*GC_walkP_t) (void *);
struct GC_walkP_p { GC_walkP_t proc; };

typedef void (*GC_callP_t) (void);
struct GC_callP_p { GC_callP_t proc; };

struct _T7_a { char array[(MaxBuf-1)+1]; };
struct PolyMatrix3D_MatrixValue_a { PolyMatrix3D__T10 array[PolyMatrix3D_MaxDimension-1+1]; };
typedef void (*Indexing_IndexProcedure_t) (void *);
struct Indexing_IndexProcedure_p { Indexing_IndexProcedure_t proc; };

struct _T6_r {
               void *ArrayStart;
               unsigned int ArraySize;
               unsigned int Used;
               unsigned int Low;
               unsigned int High;
               unsigned int Debug;
               unsigned int Map;
             };

typedef struct _T1_r _T1;

typedef unsigned int state;

typedef struct _T8_r _T8;

typedef _T8 *callBack;

typedef _T1 *GC_entity;

struct fract_r {
                 unsigned int positive;
                 long unsigned int whole;
                 long unsigned int num;
                 long unsigned int demon;
                 Operator op;
                 Fractions_Fract left;
                 Fractions_Fract right;
                 unsigned int dirty;
                 Special special;
                 GC_entity fentity;
               };

struct _T2_r {
               Object head;
               Points_Point pos;
               GC_entity mentity;
             };

typedef void (*macroObjects_pProc_t) (unsigned int, Points_Point *, unsigned int, unsigned int, Fractions_Fract, deviceIf_Colour);
struct macroObjects_pProc_p { macroObjects_pProc_t proc; };

struct _T1_r {
               void *data;
               unsigned int rIndex;
               state status;
               GC_entity next;
             };

struct _T5_r {
               Indexing_Index roots;
               Indexing_Index allocated;
               unsigned int bytes;
               DynamicStrings_String desc;
               GC_walkP walkp;
               callBack callbacks;
               GC_entity freeList;
               GC_garbage next;
             };

struct _T8_r {
               GC_callP callp;
               callBack next;
             };

struct Contents_r {
                    _T7 buf;
                    unsigned int len;
                    DynamicStrings_String next;
                  };

struct _T9_r {
               PolyMatrix3D_MatrixValue value;
               GC_entity gentity;
             };

struct Circle_r {
                  deviceIf_Colour colour;
                  unsigned int filled;
                  Fractions_Fract thickness;
                  Points_Point center;
                  Fractions_Fract radius;
                };

typedef struct Polygon_r Polygon;

typedef struct _T4_a _T4;

typedef struct descriptor_r descriptor;

typedef descriptor *Descriptor;

typedef enum {inuse, marked, onlist, poisoned} desState;

struct _T4_a { Points_Point array[maxPoints+1]; };
struct descriptor_r {
                      unsigned int charStarUsed;
                      void *charStar;
                      unsigned int charStarSize;
                      unsigned int charStarValid;
                      desState state;
                      DynamicStrings_String garbage;
                    };

typedef struct DebugInfo_r DebugInfo;

struct Polygon_r {
                   deviceIf_Colour colour;
                   unsigned int filled;
                   Fractions_Fract thickness;
                   unsigned int noPoints;
                   _T4 pArray;
                 };

struct DebugInfo_r {
                     DynamicStrings_String next;
                     void *file;
                     unsigned int line;
                     void *proc;
                   };

struct _T3_r {
               typeOfObject type;  /* case tag */
               union {
                       Circle oCircle;
                       Polygon oPolygon;
                     };
               GC_entity oentity;
               Object next;
             };

struct stringRecord_r {
                        Contents contents;
                        Descriptor head;
                        DebugInfo debug;
                      };

static unsigned int pFixed;
static Points_Point defaultVelocity;
static Fractions_Fract defaultMass;
static double defaultRotation;
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
void M2RTS_NoException (void * filename, unsigned int line, unsigned int column, void * scope);

/*
   populate - populate the 2D world with the contents of macro, m.
*/

void popWorld_populate (macroObjects_Macro m, unsigned int fixed, unsigned int solid);

/*
   mass - sets the default mass for a movable object.
*/

void popWorld_mass (Fractions_Fract m);

/*
   velocity - sets the default velocity for a movable object.
*/

void popWorld_velocity (Points_Point v);

/*
   rotate - sets the default angular velocity for a movable object.
*/

void popWorld_rotate (Fractions_Fract r);

/*
   init - initialise the 2D world and configure the device to be groff or pygame.
*/

void popWorld_init (unsigned int groff);

/*
   root - grafts fract into the roots of the garbage tree.
*/

Fractions_Fract Fractions_root (Fractions_Fract f);

/*
   unroot - removes, f, from the roots of the garbage tree.
*/

Fractions_Fract Fractions_unroot (Fractions_Fract f);

/*
   pi - returns the approximation of pi as a Fract.
*/

Fractions_Fract Fractions_pi (void);

/*
   zero - returns the fraction, 0.
*/

Fractions_Fract Fractions_zero (void);

/*
   one - returns the fraction, 1/1.
*/

Fractions_Fract Fractions_one (void);

/*
   two - returns the value 2 as a fraction.
*/

Fractions_Fract Fractions_two (void);

/*
   half - returns 1/2.
*/

Fractions_Fract Fractions_half (void);

/*
   quarter - returns 1/4.
*/

Fractions_Fract Fractions_quarter (void);

/*
   oneOverN - returns 1/n.
*/

Fractions_Fract Fractions_oneOverN (long unsigned int n);

/*
   root2 -
*/

Fractions_Fract Fractions_root2 (void);

/*
   root3 - returns 3^.5.
*/

Fractions_Fract Fractions_root3 (void);

/*
   root6 - returns 6^.5.
*/

Fractions_Fract Fractions_root6 (void);

/*
   integer - return, i, as a fraction.
*/

Fractions_Fract Fractions_integer (long int i);

/*
   cardinal - returns a cardinal as a fraction.
*/

Fractions_Fract Fractions_cardinal (long unsigned int i);

/*
   isZero - returns TRUE if the fraction is zero.
*/

unsigned int Fractions_isZero (Fractions_Fract f);

/*
   isOne - returns TRUE if the fraction is one.
*/

unsigned int Fractions_isOne (Fractions_Fract f);

/*
   isEqual - returns TRUE if Fracts, l, and, r, are equal.
*/

unsigned int Fractions_isEqual (Fractions_Fract l, Fractions_Fract r);

/*
   isLess - returns TRUE if l < r.
*/

unsigned int Fractions_isLess (Fractions_Fract l, Fractions_Fract r);

/*
   isGreater - returns TRUE if l > r.
*/

unsigned int Fractions_isGreater (Fractions_Fract l, Fractions_Fract r);

/*
   negate - negate fraction, f.
*/

Fractions_Fract Fractions_negate (Fractions_Fract f);

/*
   power - return l^r.
*/

Fractions_Fract Fractions_power (Fractions_Fract l, Fractions_Fract r);

/*
   mult - return l * r
*/

Fractions_Fract Fractions_mult (Fractions_Fract l, Fractions_Fract r);

/*
   div - return l / r.
*/

Fractions_Fract Fractions_div (Fractions_Fract l, Fractions_Fract r);

/*
   reciprocal - return 1/f.
*/

Fractions_Fract Fractions_reciprocal (Fractions_Fract f);

/*
   sub - returns the expression, l - r.
*/

Fractions_Fract Fractions_sub (Fractions_Fract l, Fractions_Fract r);

/*
   add - returns a new fraction of the result, l+r.
*/

Fractions_Fract Fractions_add (Fractions_Fract l, Fractions_Fract r);

/*
   inc - returns, l, after, r, has been added.
*/

Fractions_Fract Fractions_inc (Fractions_Fract l, Fractions_Fract r);

/*
   dec - returns, l, after, r, has been subtracted.
*/

Fractions_Fract Fractions_dec (Fractions_Fract l, Fractions_Fract r);

/*
   simplify - simplify the fraction or expression.
*/

Fractions_Fract Fractions_simplify (Fractions_Fract f);

/*
   initFract - initialise a fraction, which is expressed as:  w + n/d.
*/

Fractions_Fract Fractions_initFract (long unsigned int w, long unsigned int n, long unsigned int d);

/*
   add3 - returns a new fraction which contains the result of a+b+c.
*/

Fractions_Fract Fractions_add3 (Fractions_Fract a, Fractions_Fract b, Fractions_Fract c);

/*
   mult3 - returns a new fraction which contains the result of a * b * c.
*/

Fractions_Fract Fractions_mult3 (Fractions_Fract a, Fractions_Fract b, Fractions_Fract c);

/*
   mark - marks Fract, f, to be saved from garbage collection.
*/

void Fractions_mark (Fractions_Fract f);

/*
   dup - returns a duplicate of Fract, f.
*/

Fractions_Fract Fractions_dup (Fractions_Fract f);

/*
   areEqual - return TRUE if l = r.
*/

unsigned int Fractions_areEqual (Fractions_Fract l, Fractions_Fract r);

/*
   getReal - returns a REAL value of, f.
*/

double Fractions_getReal (Fractions_Fract f);

/*
   getFract - returns the, whole, numerator and demonimator value of, f.
*/

void Fractions_getFract (Fractions_Fract f, long unsigned int *w, long unsigned int *n, long unsigned int *d);

/*
   getLongReal - returns a LONGREAL value of, f.
*/

long double Fractions_getLongReal (Fractions_Fract f);

/*
   putReal - returns a fraction in the range whole number + x/10000
*/

Fractions_Fract Fractions_putReal (double r);

/*
   writeFract - displays fraction, f.
*/

void Fractions_writeFract (Fractions_Fract f);

/*
   isPositive - returns TRUE if, f, is positive.
*/

unsigned int Fractions_isPositive (Fractions_Fract f);

/*
   isNegative - returns TRUE if the value is negative.
*/

unsigned int Fractions_isNegative (Fractions_Fract f);

/*
   sin - return sin of angle, f.
*/

Fractions_Fract Fractions_sin (Fractions_Fract f);

/*
   cos - return cos of angle, f.
*/

Fractions_Fract Fractions_cos (Fractions_Fract f);

/*
   tan - return tan of angle, f.
*/

Fractions_Fract Fractions_tan (Fractions_Fract f);
Points_Point Points_initPoint (Fractions_Fract x, Fractions_Fract y);
Points_Point Points_rootPoint (Points_Point p);
Points_Point Points_unRootPoint (Points_Point p);
Points_Point Points_dupPoint (Points_Point p);
void Points_markPoint (Points_Point p);
Points_Point Points_addPoint (Points_Point a, Points_Point b);
Points_Point Points_subPoint (Points_Point a, Points_Point b);
Points_Point Points_negatePoint (Points_Point p);
Points_Point Points_scalePoint (Points_Point p, Fractions_Fract s);
Points_Point Points_zeroPoint (void);

/*
   initMacro - creates and returns a macro.
*/

macroObjects_Macro macroObjects_initMacro (void);

/*
   moveTo - assign the internal position in macro, m, to, p.
*/

macroObjects_Macro macroObjects_moveTo (macroObjects_Macro m, Points_Point p);

/*
   right - move right relatively by, f, units.
*/

macroObjects_Macro macroObjects_right (macroObjects_Macro m, Fractions_Fract f);

/*
   left - move left relatively by, f, units.
*/

macroObjects_Macro macroObjects_left (macroObjects_Macro m, Fractions_Fract f);

/*
   up - move up relatively by, f, units.
*/

macroObjects_Macro macroObjects_up (macroObjects_Macro m, Fractions_Fract f);

/*
   down - move down relatively by, f, units.
*/

macroObjects_Macro macroObjects_down (macroObjects_Macro m, Fractions_Fract f);

/*
   rectangle - draw a rectangle at current position which is length, height, units, and is
               filled and has colour, c.
*/

macroObjects_Macro macroObjects_rectangle (macroObjects_Macro m, unsigned int fill, Fractions_Fract thick, deviceIf_Colour c, Fractions_Fract length, Fractions_Fract height);

/*
   circle - draw a circle at current position of, colour, and radius.
*/

macroObjects_Macro macroObjects_circle (macroObjects_Macro m, unsigned int fill, Fractions_Fract thick, deviceIf_Colour c, Fractions_Fract rad);

/*
   angledRect - add angled rectangle to macro, m.  The angled rectangle four points are defined
                by the current position, cp, cp+v1, cp+v1+v2, cp+v2.
*/

macroObjects_Macro macroObjects_angledRect (macroObjects_Macro m, unsigned int fill, Fractions_Fract thick, deviceIf_Colour c, Points_Point v1, Points_Point v2);

/*
   triangle - the triangle is defined by the current position:  cp, cp+v1, cp+v2.
*/

macroObjects_Macro macroObjects_triangle (macroObjects_Macro m, unsigned int fill, Fractions_Fract thick, deviceIf_Colour c, Points_Point v1, Points_Point v2);

/*
   append - returns a new macro which is the result of appending, b, onto the end of, a.
*/

macroObjects_Macro macroObjects_append (macroObjects_Macro a, macroObjects_Macro b);

/*
   rotate - rotate macro, m, about point, p, with angle, r.
            It returns a new macro.
*/

macroObjects_Macro macroObjects_rotate (macroObjects_Macro m, Points_Point p, Fractions_Fract r);

/*
   translate - translates macro, m, along, vector.
               It returns a new macro.
*/

macroObjects_Macro macroObjects_translate (macroObjects_Macro m, Points_Point vector);

/*
   scale - scale macro, m, in the x and y axis.  A new
           macro is returned.
*/

macroObjects_Macro macroObjects_scale (macroObjects_Macro m, Points_Point s);

/*
   dup - duplicates and returns a new macro.
*/

macroObjects_Macro macroObjects_dup (macroObjects_Macro m);

/*
   runCallBacks - for each
                           polygon call p 
                           circle call c
                                         in macro, m.
*/

void macroObjects_runCallBacks (macroObjects_Macro m, macroObjects_pProc p, macroObjects_cProc c);

/*
   rootMacro - register macro, m, with the roots of the garbage collector.
*/

macroObjects_Macro macroObjects_rootMacro (macroObjects_Macro m);

/*
   unRootMacro - unroots macro, m, from the garbage collector.
                 Macro, m, can still be used until the garbage collector is called.
*/

macroObjects_Macro macroObjects_unRootMacro (macroObjects_Macro m);

/*
   markMacro - marks macro, m, and marks everything.
*/

void macroObjects_markMacro (macroObjects_Macro m);
unsigned int deviceIf_white (void);
unsigned int deviceIf_black (void);
unsigned int deviceIf_red (void);
unsigned int deviceIf_green (void);
unsigned int deviceIf_blue (void);
unsigned int deviceIf_yellow (void);
unsigned int deviceIf_purple (void);
void deviceIf_glyphLine (Points_Point start, Points_Point end, Fractions_Fract thick, deviceIf_Colour c);
void deviceIf_glyphPolygon (unsigned int n, Points_Point *p_, unsigned int _p_high, unsigned int fill, Fractions_Fract thick, deviceIf_Colour c);
void deviceIf_glyphCircle (Points_Point pos, unsigned int fill, Fractions_Fract thick, Fractions_Fract rad, deviceIf_Colour c);
void deviceIf_flipBuffer (void);
void deviceIf_frameNote (void);
void deviceIf_emptyCbuffer (void);
void deviceIf_emptyFbuffer (void);
void deviceIf_writeTime (double t);
unsigned int deviceIf_defineColour (Fractions_Fract r, Fractions_Fract g, Fractions_Fract b);
void deviceIf_useGroff (void);
void deviceIf_useBuffer (void);
void deviceIf_useRPC (void);
void deviceIf_finish (void);
void deviceIf_configDevice (Points_Point inMax, Points_Point outMax, unsigned int fps);
void deviceIf_getFrameBuffer (void * *start, unsigned int *length, unsigned int *used);
void deviceIf_getColourBuffer (void * *start, unsigned int *length, unsigned int *used);
int libc_write (int d, void * buf, int nbytes);
int libc_read (int d, void * buf, int nbytes);
int libc_system (void * a);
void libc_abort (void);
void * libc_malloc (unsigned int size);
void libc_free (void * ptr);
void * libc_realloc (void * ptr, unsigned int size);
int libc_isatty (int fd);
void libc_exit (int r);
void * libc_getenv (void * s);
int libc_getpid (void);
int libc_dup (int d);
int libc_close (int d);
int libc_open (void * filename, int oflag, ...);
int libc_creat (void * filename, unsigned int mode);
long int libc_lseek (int fd, long int offset, int whence);
void libc_perror (char *string_, unsigned int _string_high);
int libc_readv (int fd, void * v, int n);
int libc_writev (int fd, void * v, int n);
void * libc_getcwd (void * buf, int size);
int libc_chown (void * filename, int uid, int gid);
int libc_strlen (void * a);
void * libc_strcpy (void * dest, void * src);
void * libc_strncpy (void * dest, void * src, unsigned int n);
int libc_unlink (void * file);
void * libc_memcpy (void * dest, void * src, unsigned int size);
void * libc_memset (void * s, int c, unsigned int size);
void * libc_memmove (void * dest, void * src, unsigned int size);
int libc_printf (char *format_, unsigned int _format_high, ...);
int libc_setenv (void * name, void * value, int overwrite);
void libc_srand (int seed);
int libc_rand (void);
libc_time_t libc_time (void * a);
void * libc_localtime (libc_time_t *t);
int libc_ftime (libc_timeb *t);
int libc_shutdown (int s, int how);
int libc_rename (void * oldpath, void * newpath);
int libc_setjmp (void * env);
void libc_longjmp (void * env, int val);
void libc_atexit (PROC proc);
void * libc_ttyname (int filedes);
unsigned int libc_sleep (unsigned int seconds);
void twoDsim_gravity (double g);
unsigned int twoDsim_box (double x0, double y0, double i, double j, deviceIf_Colour colour);
unsigned int twoDsim_poly3 (double x0, double y0, double x1, double y1, double x2, double y2, deviceIf_Colour colour);
unsigned int twoDsim_poly4 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, deviceIf_Colour colour);
unsigned int twoDsim_poly5 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, deviceIf_Colour colour);
unsigned int twoDsim_poly6 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, deviceIf_Colour colour);
double twoDsim_get_xpos (unsigned int id);
double twoDsim_get_ypos (unsigned int id);
double twoDsim_get_xvel (unsigned int id);
double twoDsim_get_yvel (unsigned int id);
double twoDsim_get_xaccel (unsigned int id);
double twoDsim_get_yaccel (unsigned int id);
void twoDsim_put_xvel (unsigned int id, double r);
void twoDsim_put_yvel (unsigned int id, double r);
void twoDsim_put_xaccel (unsigned int id, double r);
void twoDsim_put_yaccel (unsigned int id, double r);
void twoDsim_apply_impulse (unsigned int id, double x, double y, double m);
unsigned int twoDsim_moving_towards (unsigned int id, double x, double y);
void twoDsim_set_colour (unsigned int id, deviceIf_Colour colour);
unsigned int twoDsim_mass (unsigned int id, double m);
unsigned int twoDsim_fix (unsigned int id);
unsigned int twoDsim_circle (double x0, double y0, double radius, deviceIf_Colour colour);
unsigned int twoDsim_velocity (unsigned int id, double vx, double vy);
unsigned int twoDsim_accel (unsigned int id, double ax, double ay);
unsigned int twoDsim_rotate (unsigned int id, double angle);
unsigned int twoDsim_rvel (unsigned int id, double angle);
void twoDsim_fps (double f);
void twoDsim_replayRate (double f);
void twoDsim_simulateFor (double t);
double twoDsim_getTime (void);
double twoDsim_skipTime (double t);
double twoDsim_timeUntil (void);
void twoDsim_processEvent (void);
unsigned int twoDsim_isCollision (void);
unsigned int twoDsim_isFrame (void);
unsigned int twoDsim_isFunction (void);
void twoDsim_createFunctionEvent (double t, unsigned int id);
unsigned int twoDsim_rm (unsigned int id);
void twoDsim_getEventBuffer (void * *start, unsigned int *length, unsigned int *used);
void twoDsim_buildFrame (void);
void twoDsim_emptyCbuffer (void);
void twoDsim_emptyFbuffer (void);
void twoDsim_useTimeDelay (unsigned int on);
void twoDsim_drawCollisionFrames (unsigned int actual, unsigned int predict);
void twoDsim_setCollisionColour (deviceIf_Colour c);
void twoDsim_dumpWorld (void);
void twoDsim_checkObjects (void);
void StrLib_StrConCat (char *a_, unsigned int _a_high, char *b_, unsigned int _b_high, char *c, unsigned int _c_high);
unsigned int StrLib_StrLess (char *a_, unsigned int _a_high, char *b_, unsigned int _b_high);
unsigned int StrLib_StrEqual (char *a_, unsigned int _a_high, char *b_, unsigned int _b_high);
unsigned int StrLib_StrLen (char *a_, unsigned int _a_high);
void StrLib_StrCopy (char *a_, unsigned int _a_high, char *b, unsigned int _b_high);
unsigned int StrLib_IsSubString (char *a_, unsigned int _a_high, char *b_, unsigned int _b_high);
void StrLib_StrRemoveWhitePrefix (char *a_, unsigned int _a_high, char *b, unsigned int _b_high);

/*
   initGarbage - initialises a garbage heap which manages a dynamically
                 allocated data type of noOfBytes length.  It must be
                 the same data structure which is walked by, walkP.
*/

GC_garbage GC_initGarbage (GC_walkP p, unsigned int noOfBytes, DynamicStrings_String typeName);

/*
   collect - collect all used entities and place them onto the free list.
*/

void GC_collect (GC_garbage g);

/*
   markEntity - sets the status of entity, e, to marked.
*/

void GC_markEntity (GC_entity e);

/*
   allocate - returns allocated memory from, a.  It also
              returns entity, e, which is associated with, a.
*/

void GC_allocate (GC_garbage g, GC_entity *e, void * *a);

/*
   rootAllocate - returns allocated memory from, a, with length, bytes.  It also
                  returns entity, e, which is associated with, a.

                  It registers this entity in the root of the garbage collection.
*/

void GC_rootAllocate (GC_garbage g, GC_entity *e, void * *a);

/*
   rootDeallocate - deallocates memory from, a, with length, bytes.
                    It also unregisters entity, e, from the root.
*/

void GC_rootDeallocate (GC_garbage g, GC_entity *e, void * *a);

/*
   rootEntity - records data, a, to be part of the roots in heap, g.
                Useful if an entity was created using, allocate,
                and now needs to be remembered.
*/

void GC_rootEntity (GC_garbage g, GC_entity e, void * a);

/*
   getData - returns the address associated with entity, e.
*/

void * GC_getData (GC_entity e);

/*
   registerCallback - call procedure, p, when the garbage collector is marking used entities.
*/

void GC_registerCallback (GC_garbage g, GC_callP p);

/*
   collectAll - run the garbage collection on all heaps.
*/

void GC_collectAll (void);
void Assertion_Assert (unsigned int Condition);
DynamicStrings_String StringConvert_IntegerToString (int i, unsigned int width, char padding, unsigned int sign, unsigned int base, unsigned int lower);
DynamicStrings_String StringConvert_CardinalToString (unsigned int c, unsigned int width, char padding, unsigned int base, unsigned int lower);
int StringConvert_StringToInteger (DynamicStrings_String s, unsigned int base, unsigned int *found);
unsigned int StringConvert_StringToCardinal (DynamicStrings_String s, unsigned int base, unsigned int *found);
DynamicStrings_String StringConvert_LongIntegerToString (long int i, unsigned int width, char padding, unsigned int sign, unsigned int base, unsigned int lower);
long int StringConvert_StringToLongInteger (DynamicStrings_String s, unsigned int base, unsigned int *found);
DynamicStrings_String StringConvert_LongCardinalToString (long unsigned int c, unsigned int width, char padding, unsigned int base, unsigned int lower);
long unsigned int StringConvert_StringToLongCardinal (DynamicStrings_String s, unsigned int base, unsigned int *found);
DynamicStrings_String StringConvert_ShortCardinalToString (short unsigned int c, unsigned int width, char padding, unsigned int base, unsigned int lower);
short unsigned int StringConvert_StringToShortCardinal (DynamicStrings_String s, unsigned int base, unsigned int *found);
int StringConvert_stoi (DynamicStrings_String s);
DynamicStrings_String StringConvert_itos (int i, unsigned int width, char padding, unsigned int sign);
DynamicStrings_String StringConvert_ctos (unsigned int c, unsigned int width, char padding);
unsigned int StringConvert_stoc (DynamicStrings_String s);
int StringConvert_hstoi (DynamicStrings_String s);
int StringConvert_ostoi (DynamicStrings_String s);
int StringConvert_bstoi (DynamicStrings_String s);
unsigned int StringConvert_hstoc (DynamicStrings_String s);
unsigned int StringConvert_ostoc (DynamicStrings_String s);
unsigned int StringConvert_bstoc (DynamicStrings_String s);
long double StringConvert_StringToLongreal (DynamicStrings_String s, unsigned int *found);
DynamicStrings_String StringConvert_LongrealToString (long double x, unsigned int TotalWidth, unsigned int FractionWidth);
double StringConvert_stor (DynamicStrings_String s);
long double StringConvert_stolr (DynamicStrings_String s);
DynamicStrings_String StringConvert_ToSigFig (DynamicStrings_String s, unsigned int n);
DynamicStrings_String StringConvert_ToDecimalPlaces (DynamicStrings_String s, unsigned int n);

/*
   InitString - creates and returns a String type object.
                Initial contents are, a.
*/

DynamicStrings_String DynamicStrings_InitString (char *a_, unsigned int _a_high);

/*
   KillString - frees String, s, and its contents.
                NIL is returned.
*/

DynamicStrings_String DynamicStrings_KillString (DynamicStrings_String s);

/*
   Fin - finishes with a string, it calls KillString with, s.
         The purpose of the procedure is to provide a short cut
         to calling KillString and then testing the return result.
*/

void DynamicStrings_Fin (DynamicStrings_String s);

/*
   InitStringCharStar - initializes and returns a String to contain the C string.
*/

DynamicStrings_String DynamicStrings_InitStringCharStar (void * a);

/*
   InitStringChar - initializes and returns a String to contain the single character, ch.
*/

DynamicStrings_String DynamicStrings_InitStringChar (char ch);

/*
   Mark - marks String, s, ready for garbage collection.
*/

DynamicStrings_String DynamicStrings_Mark (DynamicStrings_String s);

/*
   Length - returns the length of the String, s.
*/

unsigned int DynamicStrings_Length (DynamicStrings_String s);

/*
   ConCat - returns String, a, after the contents of, b, have been appended.
*/

DynamicStrings_String DynamicStrings_ConCat (DynamicStrings_String a, DynamicStrings_String b);

/*
   ConCatChar - returns String, a, after character, ch, has been appended.
*/

DynamicStrings_String DynamicStrings_ConCatChar (DynamicStrings_String a, char ch);

/*
   Assign - assigns the contents of, b, into, a.
            String, a, is returned.
*/

DynamicStrings_String DynamicStrings_Assign (DynamicStrings_String a, DynamicStrings_String b);

/*
   Dup - duplicate a String, s, returning the copy of s.
*/

DynamicStrings_String DynamicStrings_Dup (DynamicStrings_String s);

/*
   Add - returns a new String which contains the contents of a and b.
*/

DynamicStrings_String DynamicStrings_Add (DynamicStrings_String a, DynamicStrings_String b);

/*
   Equal - returns TRUE if String, a, and, b, are equal.
*/

unsigned int DynamicStrings_Equal (DynamicStrings_String a, DynamicStrings_String b);

/*
   EqualCharStar - returns TRUE if contents of String, s, is the same as the
                   string, a.
*/

unsigned int DynamicStrings_EqualCharStar (DynamicStrings_String s, void * a);

/*
   EqualArray - returns TRUE if contents of String, s, is the same as the
                string, a.
*/

unsigned int DynamicStrings_EqualArray (DynamicStrings_String s, char *a_, unsigned int _a_high);

/*
   Mult - returns a new string which is n concatenations of String, s.
*/

DynamicStrings_String DynamicStrings_Mult (DynamicStrings_String s, unsigned int n);

/*
   Slice - returns a new string which contains the elements
           low..high-1

           strings start at element 0
           Slice(s, 0, 2)  will return elements 0, 1 but not 2
           Slice(s, 1, 3)  will return elements 1, 2 but not 3
           Slice(s, 2, 0)  will return elements 2..max
           Slice(s, 3, -1) will return elements 3..max-1
           Slice(s, 4, -2) will return elements 4..max-2
*/

DynamicStrings_String DynamicStrings_Slice (DynamicStrings_String s, int low, int high);

/*
   Index - returns the indice of the first occurance of, ch, in
           String, s. -1 is returned if, ch, does not exist.
           The search starts at position, o.
*/

int DynamicStrings_Index (DynamicStrings_String s, char ch, unsigned int o);

/*
   RIndex - returns the indice of the last occurance of, ch,
            in String, s. The search starts at position, o.
            -1 is returned if, ch, is not found.
*/

int DynamicStrings_RIndex (DynamicStrings_String s, char ch, unsigned int o);

/*
   RemoveComment - assuming that, comment, is a comment delimiter
                   which indicates anything to its right is a comment
                   then strip off the comment and also any white space
                   on the remaining right hand side.
                   It leaves any white space on the left hand side alone.
*/

DynamicStrings_String DynamicStrings_RemoveComment (DynamicStrings_String s, char comment);

/*
   RemoveWhitePrefix - removes any leading white space from String, s.
                       A new string is returned.
*/

DynamicStrings_String DynamicStrings_RemoveWhitePrefix (DynamicStrings_String s);

/*
   RemoveWhitePostfix - removes any leading white space from String, s.
                        A new string is returned.
*/

DynamicStrings_String DynamicStrings_RemoveWhitePostfix (DynamicStrings_String s);

/*
   ToUpper - returns string, s, after it has had its lower case characters
             replaced by upper case characters.
             The string, s, is not duplicated.
*/

DynamicStrings_String DynamicStrings_ToUpper (DynamicStrings_String s);

/*
   ToLower - returns string, s, after it has had its upper case characters
             replaced by lower case characters.
             The string, s, is not duplicated.
*/

DynamicStrings_String DynamicStrings_ToLower (DynamicStrings_String s);

/*
   CopyOut - copies string, s, to a.
*/

void DynamicStrings_CopyOut (char *a, unsigned int _a_high, DynamicStrings_String s);

/*
   char - returns the character, ch, at position, i, in String, s.
*/

char DynamicStrings_char (DynamicStrings_String s, int i);

/*
   string - returns the C style char * of String, s.
*/

void * DynamicStrings_string (DynamicStrings_String s);

/*
   InitStringDB - the debug version of InitString.
*/

DynamicStrings_String DynamicStrings_InitStringDB (char *a_, unsigned int _a_high, char *file_, unsigned int _file_high, unsigned int line);

/*
   InitStringCharStarDB - the debug version of InitStringCharStar.
*/

DynamicStrings_String DynamicStrings_InitStringCharStarDB (void * a, char *file_, unsigned int _file_high, unsigned int line);

/*
   InitStringCharDB - the debug version of InitStringChar.
*/

DynamicStrings_String DynamicStrings_InitStringCharDB (char ch, char *file_, unsigned int _file_high, unsigned int line);

/*
   MultDB - the debug version of MultDB.
*/

DynamicStrings_String DynamicStrings_MultDB (DynamicStrings_String s, unsigned int n, char *file_, unsigned int _file_high, unsigned int line);

/*
   DupDB - the debug version of Dup.
*/

DynamicStrings_String DynamicStrings_DupDB (DynamicStrings_String s, char *file_, unsigned int _file_high, unsigned int line);

/*
   SliceDB - debug version of Slice.
*/

DynamicStrings_String DynamicStrings_SliceDB (DynamicStrings_String s, int low, int high, char *file_, unsigned int _file_high, unsigned int line);

/*
   PushAllocation - pushes the current allocation/deallocation lists.
*/

void DynamicStrings_PushAllocation (void);

/*
   PopAllocation - test to see that all strings are deallocated since
                   the last push.  Then it pops to the previous
                   allocation/deallocation lists.

                   If halt is true then the application terminates
                   with an exit code of 1.
*/

void DynamicStrings_PopAllocation (unsigned int halt);

/*
   PopAllocationExemption - test to see that all strings are deallocated, except
                            string, e, since the last push.
                            Then it pops to the previous allocation/deallocation
                            lists.

                            If halt is true then the application terminates
                            with an exit code of 1.
*/

DynamicStrings_String DynamicStrings_PopAllocationExemption (unsigned int halt, DynamicStrings_String e);

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
void STextIO_ReadChar (char *ch);
void STextIO_ReadRestLine (char *s, unsigned int _s_high);
void STextIO_ReadString (char *s, unsigned int _s_high);
void STextIO_ReadToken (char *s, unsigned int _s_high);
void STextIO_SkipLine (void);
void STextIO_WriteChar (char ch);
void STextIO_WriteLn (void);
void STextIO_WriteString (char *s_, unsigned int _s_high);
void SWholeIO_ReadInt (int *int_);
void SWholeIO_WriteInt (int int_, unsigned int width);
void SWholeIO_ReadCard (unsigned int *card);
void SWholeIO_WriteCard (unsigned int card, unsigned int width);
PolyMatrix3D_Matrix Transform3D_reflect (Fractions_Fract m, Fractions_Fract x, Fractions_Fract c);
PolyMatrix3D_Matrix Transform3D_rotate (Fractions_Fract r);
PolyMatrix3D_Matrix Transform3D_scale (Points_Point p);
PolyMatrix3D_Matrix Transform3D_translate (Points_Point p);
unsigned int history_isDuplicate (double currentTime, double relTime, unsigned int id1, unsigned int id2, history_whereHit w1, history_whereHit w2, coord_Coord cp);
void history_forgetFuture (void);
void history_occurred (double currentTime, unsigned int id1, unsigned int id2, coord_Coord cp);
void history_anticipate (double aTime, unsigned int id1, unsigned int id2, coord_Coord cp);
unsigned int history_isPair (unsigned int a, unsigned int b, unsigned int x, unsigned int y);

/*
   InitIndex - creates and returns an Index.
*/

Indexing_Index Indexing_InitIndex (unsigned int low);

/*
   KillIndex - returns Index to free storage.
*/

Indexing_Index Indexing_KillIndex (Indexing_Index i);

/*
   DebugIndex - turns on debugging within an index.
*/

Indexing_Index Indexing_DebugIndex (Indexing_Index i);

/*
   InBounds - returns TRUE if indice, n, is within the bounds
              of the dynamic array.
*/

unsigned int Indexing_InBounds (Indexing_Index i, unsigned int n);

/*
   HighIndice - returns the last legally accessible indice of this array.
*/

unsigned int Indexing_HighIndice (Indexing_Index i);

/*
   LowIndice - returns the first legally accessible indice of this array.
*/

unsigned int Indexing_LowIndice (Indexing_Index i);

/*
   PutIndice - places, a, into the dynamic array at position i[n]
*/

void Indexing_PutIndice (Indexing_Index i, unsigned int n, void * a);

/*
   GetIndice - retrieves, element i[n] from the dynamic array.
*/

void * Indexing_GetIndice (Indexing_Index i, unsigned int n);

/*
   IsIndiceInIndex - returns TRUE if, a, is in the index, i.
*/

unsigned int Indexing_IsIndiceInIndex (Indexing_Index i, void * a);

/*
   RemoveIndiceFromIndex - removes, a, from Index, i.
*/

void Indexing_RemoveIndiceFromIndex (Indexing_Index i, void * a);

/*
   DeleteIndice - delete i[j] from the array.
*/

void Indexing_DeleteIndice (Indexing_Index i, unsigned int j);

/*
   IncludeIndiceIntoIndex - if the indice is not in the index, then
                            add it at the end.
*/

void Indexing_IncludeIndiceIntoIndex (Indexing_Index i, void * a);

/*
   ForeachIndiceInIndexDo - for each j indice of i, call procedure p(i[j])
*/

void Indexing_ForeachIndiceInIndexDo (Indexing_Index i, Indexing_IndexProcedure p);
void Storage_ALLOCATE (void * *a, unsigned int Size);
void Storage_DEALLOCATE (void * *a, unsigned int Size);
void Storage_REALLOCATE (void * *a, unsigned int Size);
unsigned int Storage_Available (unsigned int Size);
void gdbif_finishSpin (void);
void gdbif_sleepSpin (void);
void gdbif_connectSpin (void);
void StrIO_WriteLn (void);
void StrIO_ReadString (char *a, unsigned int _a_high);
void StrIO_WriteString (char *a_, unsigned int _a_high);
coord_Coord coord_initCoord (double x, double y);
coord_Coord coord_normaliseCoord (coord_Coord c);
void coord_perpendiculars (coord_Coord c, coord_Coord *c1, coord_Coord *c2);
coord_Coord coord_perpendicular (coord_Coord c);
coord_Coord coord_scaleCoord (coord_Coord c, double s);
coord_Coord coord_subCoord (coord_Coord a, coord_Coord b);
coord_Coord coord_addCoord (coord_Coord a, coord_Coord b);
double coord_lengthCoord (coord_Coord c);
coord_Coord coord_rotateCoord (coord_Coord c, double theta);
double coord_dotProd (coord_Coord a, coord_Coord b);

/*
   ppolygon - 
*/

static void ppolygon (unsigned int n, Points_Point *p_, unsigned int _p_high, unsigned int fill, Fractions_Fract thick, deviceIf_Colour c);

/*
   pcircle - 
*/

static void pcircle (Points_Point pos, unsigned int fill, Fractions_Fract thick, Fractions_Fract rad, deviceIf_Colour c);


/*
   ppolygon - 
*/

static void ppolygon (unsigned int n, Points_Point *p_, unsigned int _p_high, unsigned int fill, Fractions_Fract thick, deviceIf_Colour c)
{
  unsigned int o;
  Points_Point p[_p_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (p, p_, (_p_high+1) * sizeof (Points_Point));

  switch (n)
    {
      case 3:
        o = twoDsim_poly3 (Fractions_getReal (p[0].x), Fractions_getReal (p[0].y), Fractions_getReal (p[1].x), Fractions_getReal (p[1].y), Fractions_getReal (p[2].x), Fractions_getReal (p[2].y), c);
        break;

      case 4:
        o = twoDsim_poly4 (Fractions_getReal (p[0].x), Fractions_getReal (p[0].y), Fractions_getReal (p[1].x), Fractions_getReal (p[1].y), Fractions_getReal (p[2].x), Fractions_getReal (p[2].y), Fractions_getReal (p[3].x), Fractions_getReal (p[3].y), c);
        break;

      case 5:
        o = twoDsim_poly5 (Fractions_getReal (p[0].x), Fractions_getReal (p[0].y), Fractions_getReal (p[1].x), Fractions_getReal (p[1].y), Fractions_getReal (p[2].x), Fractions_getReal (p[2].y), Fractions_getReal (p[3].x), Fractions_getReal (p[3].y), Fractions_getReal (p[4].x), Fractions_getReal (p[4].y), c);
        break;

      case 6:
        o = twoDsim_poly6 (Fractions_getReal (p[0].x), Fractions_getReal (p[0].y), Fractions_getReal (p[1].x), Fractions_getReal (p[1].y), Fractions_getReal (p[2].x), Fractions_getReal (p[2].y), Fractions_getReal (p[3].x), Fractions_getReal (p[3].y), Fractions_getReal (p[4].x), Fractions_getReal (p[4].y), Fractions_getReal (p[5].x), Fractions_getReal (p[5].y), c);
        break;


      default:
        libc_printf ((char *) "too many sides to the polygon, max 6 allowed\\n", 46);
        M2RTS_HALT (0);
        break;
    }
  if (pFixed)
    o = twoDsim_fix (o);
  else
    {
      o = twoDsim_mass (o, Fractions_getReal (defaultMass));
      o = twoDsim_velocity (o, Fractions_getReal (defaultVelocity.x), Fractions_getReal (defaultVelocity.y));
      o = twoDsim_rotate (o, defaultRotation);
    }
}


/*
   pcircle - 
*/

static void pcircle (Points_Point pos, unsigned int fill, Fractions_Fract thick, Fractions_Fract rad, deviceIf_Colour c)
{
  unsigned int o;

  o = twoDsim_circle (Fractions_getReal (pos.x), Fractions_getReal (pos.y), Fractions_getReal (rad), c);
  if (pFixed)
    o = twoDsim_fix (o);
  else
    {
      o = twoDsim_mass (o, Fractions_getReal (defaultMass));
      o = twoDsim_velocity (o, Fractions_getReal (defaultVelocity.x), Fractions_getReal (defaultVelocity.y));
      o = twoDsim_rotate (o, defaultRotation);
    }
}


/*
   populate - populate the 2D world with the contents of macro, m.
*/

void popWorld_populate (macroObjects_Macro m, unsigned int fixed, unsigned int solid)
{
  pFixed = fixed;
  macroObjects_runCallBacks (m, (macroObjects_pProc) {(macroObjects_pProc_t) ppolygon}, (macroObjects_cProc) {(macroObjects_cProc_t) pcircle});
}


/*
   mass - sets the default mass for a movable object.
*/

void popWorld_mass (Fractions_Fract m)
{
  defaultMass = Fractions_unroot (defaultMass);
  defaultMass = Fractions_root (m);
}


/*
   velocity - sets the default velocity for a movable object.
*/

void popWorld_velocity (Points_Point v)
{
  defaultVelocity = Points_unRootPoint (defaultVelocity);
  defaultVelocity = Points_rootPoint (v);
}


/*
   rotate - sets the default angular velocity for a movable object.
*/

void popWorld_rotate (Fractions_Fract r)
{
  defaultRotation = Fractions_getReal (r);
}


/*
   init - initialise the 2D world and configure the device to be groff or pygame.
*/

void popWorld_init (unsigned int groff)
{
  defaultMass = Fractions_root (Fractions_one ());
  defaultVelocity = Points_rootPoint (Points_initPoint (Fractions_zero (), Fractions_zero ()));
  if (groff)
    {
      deviceIf_useGroff ();
      deviceIf_configDevice (Points_initPoint (Fractions_one (), Fractions_one ()), Points_initPoint (Fractions_cardinal (5), Fractions_cardinal (5)), FPSgroff);
      twoDsim_fps ((double) (FPSgroff));
    }
  else
    {
      deviceIf_useRPC ();
      deviceIf_configDevice (Points_initPoint (Fractions_one (), Fractions_one ()), Points_initPoint (Fractions_cardinal (1000), Fractions_cardinal (1000)), FPSpy);
      twoDsim_fps ((double) (FPSpy));
    }
}

void _M2_popWorld_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_popWorld_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
