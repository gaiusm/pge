/* automatically created by mc from ../git-pge/m2/macroObjects.mod.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#include <stddef.h>
#   include "Gmcrts.h"
#define _macroObjects_H
#define _macroObjects_C

#   include "GPoints.h"
#   include "GPolyMatrix3D.h"
#   include "GFractions.h"
#   include "GAssertion.h"
#   include "GSTextIO.h"
#   include "GSWholeIO.h"
#   include "GDynamicStrings.h"
#   include "GGC.h"
#   include "GSYSTEM.h"
#   include "GTransform3D.h"

typedef struct macroObjects_pProc_p macroObjects_pProc;

typedef struct macroObjects_cProc_p macroObjects_cProc;

typedef unsigned int deviceIf_Colour;

#   define maxPoints 10
typedef struct Circle_r Circle;

typedef struct Polygon_r Polygon;

typedef struct _T1_r _T1;

typedef struct _T2_r _T2;

typedef _T2 *Object;

typedef struct _T3_a _T3;

typedef enum {tcircle, tpolygon} typeOfObject;

typedef _T1 *macroObjects_Macro;

typedef void (*macroObjects_pProc_t) (unsigned int, Points_Point *, unsigned int, unsigned int, Fractions_Fract, deviceIf_Colour);
struct macroObjects_pProc_p { macroObjects_pProc_t proc; };

typedef void (*macroObjects_cProc_t) (Points_Point, unsigned int, Fractions_Fract, Fractions_Fract, deviceIf_Colour);
struct macroObjects_cProc_p { macroObjects_cProc_t proc; };

struct Circle_r {
                  deviceIf_Colour colour;
                  unsigned int filled;
                  Fractions_Fract thickness;
                  Points_Point center;
                  Fractions_Fract radius;
                };

struct _T1_r {
               Object head;
               Points_Point pos;
               GC_entity mentity;
             };

struct _T3_a { Points_Point array[maxPoints+1]; };
struct Polygon_r {
                   deviceIf_Colour colour;
                   unsigned int filled;
                   Fractions_Fract thickness;
                   unsigned int noPoints;
                   _T3 pArray;
                 };

struct _T2_r {
               typeOfObject type;  /* case tag */
               union {
                       Circle oCircle;
                       Polygon oPolygon;
                     };
               GC_entity oentity;
               Object next;
             };

static GC_garbage objectHeap;
static GC_garbage macroHeap;

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

/*
   dumpFract -
*/

static void dumpFract (Fractions_Fract f);

/*
   dumpPoint - displays point, p.
*/

static void dumpPoint (Points_Point p);

/*
   dp - debug point.
*/

static void dp (Points_Point p);

/*
   dumpColour -
*/

static void dumpColour (deviceIf_Colour c);

/*
   dumpCircle - dumps circle information.
*/

static void dumpCircle (Object o);

/*
   dumpPolygon - dumps the polygon information.
*/

static void dumpPolygon (Object o);

/*
   dumpObject - dump the object, o.
*/

static void dumpObject (Object o);

/*
   dmac - debug macro, m.
*/

static void dmac (macroObjects_Macro m);

/*
   dmat -
*/

static void dmat (PolyMatrix3D_Matrix m);

/*
   dupCircle - return a new circle object based on the values in, o.
               It adds the offset to the object from, p.
*/

static Object dupCircle (Object o, Points_Point p);

/*
   dupPolygon - return a new rectangle object based on the values in, o.
                It adds the offset to the object from, p.
*/

static Object dupPolygon (Object o, Points_Point p);

/*
   dupObject - returns a duplicate object based on the values in, o.
               It adds the offset to the object from, p.
*/

static Object dupObject (Object o, Points_Point p);

/*
   initObject - create and return an uninitialised object.
                The next field is set to NIL.
*/

static Object initObject (void);

/*
   addTo - adds object, o, to macro, m.
*/

static macroObjects_Macro addTo (macroObjects_Macro m, Object o);

/*
   scalar - scales all scalars within, m, by, f.
            A new macro is returned.
*/

static macroObjects_Macro scalar (macroObjects_Macro m, Fractions_Fract f);

/*
   setPointValues -
*/

static void setPointValues (PolyMatrix3D_MatrixValue *v, Points_Point p);

/*
   getPointValues - returns a copy of the point values.
*/

static Points_Point getPointValues (PolyMatrix3D_MatrixValue v);

/*
   mp - multiply point, p, by matrix, a, returning a new point.
*/

static Points_Point mp (Points_Point p, PolyMatrix3D_Matrix a);

/*
   foreachObjectScalar - foreach object scale the scalar values, by, s.
*/

static macroObjects_Macro foreachObjectScalar (macroObjects_Macro n, macroObjects_Macro m, Fractions_Fract s);

/*
   objectCircleScalar - scale the radius by, s.
*/

static Object objectCircleScalar (Object o, Fractions_Fract s);

/*
   objectCircleMatrix - return a new circle object after multiplying
                        all points by, a.
*/

static Object objectCircleMatrix (Object o, PolyMatrix3D_Matrix a);
static Object objectPolygonMatrix (Object o, PolyMatrix3D_Matrix a);

/*
   foreachObject - apply matrix, a, to each object in, m, and add it
                   to macro, n.  Macro, n, is returned.
*/

static macroObjects_Macro foreachObject (macroObjects_Macro n, macroObjects_Macro m, PolyMatrix3D_Matrix a);

/*
   addToEnd -
*/

static macroObjects_Macro addToEnd (macroObjects_Macro m, Object o);

/*
   callCircle -
*/

static void callCircle (Object o, macroObjects_cProc c);

/*
   callPolygon -
*/

static void callPolygon (Object o, macroObjects_pProc p);

/*
   markCircle -
*/

static void markCircle (Object o);

/*
   markPolygon -
*/

static void markPolygon (Object o);

/*
   markObject -
*/

static void markObject (Object o);

/*
   markMacroEntity - mark macro as specified by, e.
*/

static void markMacroEntity (GC_entity e);

/*
   markObjectEntity - mark object as specified by, e.
*/

static void markObjectEntity (GC_entity e);

/*
   Init -
*/

static void Init (void);


/*
   dumpFract -
*/

static void dumpFract (Fractions_Fract f)
{
  Fractions_writeFract (f);
}


/*
   dumpPoint - displays point, p.
*/

static void dumpPoint (Points_Point p)
{
  STextIO_WriteString ((char *) " (", 2);
  dumpFract (p.x);
  STextIO_WriteString ((char *) ", ", 2);
  dumpFract (p.y);
  STextIO_WriteString ((char *) ") ", 2);
}


/*
   dp - debug point.
*/

static void dp (Points_Point p)
{
  dumpPoint (p);
  STextIO_WriteLn ();
}


/*
   dumpColour -
*/

static void dumpColour (deviceIf_Colour c)
{
  SWholeIO_WriteCard ((unsigned int) c, 4);
}


/*
   dumpCircle - dumps circle information.
*/

static void dumpCircle (Object o)
{
  STextIO_WriteString ((char *) "circle ", 7);
  if (o->oCircle.filled)
    {
      STextIO_WriteString ((char *) "filled with colour ", 19);
      dumpColour (o->oCircle.colour);
    }
  else
    {
      STextIO_WriteString ((char *) "outlined with colour ", 21);
      dumpColour (o->oCircle.colour);
      STextIO_WriteString ((char *) " with a thickness of ", 21);
      dumpFract (o->oCircle.thickness);
    }
  STextIO_WriteString ((char *) " at ", 4);
  dumpPoint (o->oCircle.center);
  STextIO_WriteString ((char *) " radius ", 8);
  dumpFract (o->oCircle.radius);
  STextIO_WriteLn ();
}


/*
   dumpPolygon - dumps the polygon information.
*/

static void dumpPolygon (Object o)
{
  unsigned int i;

  STextIO_WriteString ((char *) "polygon ", 8);
  if (o->oPolygon.filled)
    {
      STextIO_WriteString ((char *) "filled with colour ", 19);
      dumpColour (o->oPolygon.colour);
    }
  else
    {
      STextIO_WriteString ((char *) "outlined with colour ", 21);
      dumpColour (o->oPolygon.colour);
      STextIO_WriteString ((char *) " with a thickness of ", 21);
      dumpFract (o->oPolygon.thickness);
    }
  STextIO_WriteString ((char *) " coordinates ", 13);
  for (i=0; i<=o->oPolygon.noPoints-1; i++)
    dumpPoint ((Points_Point) o->oPolygon.pArray.array[i]);
  STextIO_WriteLn ();
}


/*
   dumpObject - dump the object, o.
*/

static void dumpObject (Object o)
{
  switch (o->type)
    {
      case tcircle:
        dumpCircle (o);
        break;

      case tpolygon:
        dumpPolygon (o);
        break;


      default:
        CaseException ("../git-pge/m2/macroObjects.def", 1, 15);
    }
}


/*
   dmac - debug macro, m.
*/

static void dmac (macroObjects_Macro m)
{
  Object o;

  STextIO_WriteString ((char *) "macro position: ", 16);
  dumpPoint (m->pos);
  STextIO_WriteLn ();
  o = m->head;
  while (o != NULL)
    {
      dumpObject (o);
      o = o->next;
    }
}


/*
   dmat -
*/

static void dmat (PolyMatrix3D_Matrix m)
{
  unsigned int i;
  unsigned int j;
  PolyMatrix3D_MatrixValue v;

  m = PolyMatrix3D_get (m, &v);
  STextIO_WriteString ((char *) "+-", 2);
  STextIO_WriteLn ();
  STextIO_WriteString ((char *) "| ", 2);
  for (i=1; i<=3; i++)
    {
      dumpFract (v.array[1-1].array[i-1]);
      STextIO_WriteString ((char *) "  ", 2);
    }
  STextIO_WriteLn ();
  STextIO_WriteString ((char *) "| ", 2);
  for (i=1; i<=3; i++)
    {
      dumpFract (v.array[2-1].array[i-1]);
      STextIO_WriteString ((char *) "  ", 2);
    }
  STextIO_WriteLn ();
  STextIO_WriteString ((char *) "| ", 2);
  for (i=1; i<=3; i++)
    {
      dumpFract (v.array[3-1].array[i-1]);
      STextIO_WriteString ((char *) "  ", 2);
    }
  STextIO_WriteLn ();
  STextIO_WriteString ((char *) "+-", 2);
  STextIO_WriteString ((char *) " ", 1);
  STextIO_WriteLn ();
}


/*
   dupCircle - return a new circle object based on the values in, o.
               It adds the offset to the object from, p.
*/

static Object dupCircle (Object o, Points_Point p)
{
  Object n;

  n = initObject ();
  n->type = tcircle;
  n->oCircle.colour = o->oCircle.colour;
  n->oCircle.filled = o->oCircle.filled;
  n->oCircle.thickness = Fractions_dup (o->oCircle.thickness);
  n->oCircle.center = Points_addPoint (o->oCircle.center, p);
  n->oCircle.radius = Fractions_dup (o->oCircle.radius);
  return n;
}


/*
   dupPolygon - return a new rectangle object based on the values in, o.
                It adds the offset to the object from, p.
*/

static Object dupPolygon (Object o, Points_Point p)
{
  Object n;
  unsigned int i;

  n = initObject ();
  n->type = tpolygon;
  n->oPolygon.colour = o->oPolygon.colour;
  n->oPolygon.filled = o->oPolygon.filled;
  n->oPolygon.thickness = Fractions_dup (o->oPolygon.thickness);
  n->oPolygon.noPoints = o->oPolygon.noPoints;
  for (i=0; i<=n->oPolygon.noPoints-1; i++)
    n->oPolygon.pArray.array[i] = Points_addPoint ((Points_Point) o->oPolygon.pArray.array[i], p);
  return n;
}


/*
   dupObject - returns a duplicate object based on the values in, o.
               It adds the offset to the object from, p.
*/

static Object dupObject (Object o, Points_Point p)
{
  switch (o->type)
    {
      case tcircle:
        return dupCircle (o, p);
        break;

      case tpolygon:
        return dupPolygon (o, p);
        break;


      default:
        CaseException ("../git-pge/m2/macroObjects.def", 1, 15);
    }
}


/*
   initObject - create and return an uninitialised object.
                The next field is set to NIL.
*/

static Object initObject (void)
{
  Object o;
  GC_entity e;

  GC_allocate (objectHeap, &e, (void **) &o);
  o->next = NULL;
  o->oentity = e;
  return o;
}


/*
   addTo - adds object, o, to macro, m.
*/

static macroObjects_Macro addTo (macroObjects_Macro m, Object o)
{
  o->next = m->head;
  m->head = o;
  return m;
}


/*
   scalar - scales all scalars within, m, by, f.
            A new macro is returned.
*/

static macroObjects_Macro scalar (macroObjects_Macro m, Fractions_Fract f)
{
  macroObjects_Macro n;

  n = macroObjects_initMacro ();
  return foreachObjectScalar (n, m, f);
}


/*
   setPointValues -
*/

static void setPointValues (PolyMatrix3D_MatrixValue *v, Points_Point p)
{
  (*v).array[1-1].array[1-1] = Fractions_dup (p.x);
  (*v).array[1-1].array[2-1] = Fractions_dup (p.y);
  (*v).array[1-1].array[3-1] = Fractions_one ();
  (*v).array[2-1].array[1-1] = Fractions_zero ();
  (*v).array[2-1].array[2-1] = Fractions_zero ();
  (*v).array[2-1].array[3-1] = Fractions_zero ();
  (*v).array[3-1].array[1-1] = Fractions_zero ();
  (*v).array[3-1].array[2-1] = Fractions_zero ();
  (*v).array[3-1].array[3-1] = Fractions_zero ();
}


/*
   getPointValues - returns a copy of the point values.
*/

static Points_Point getPointValues (PolyMatrix3D_MatrixValue v)
{
  Points_Point p;

  p.x = Fractions_dup (v.array[1-1].array[1-1]);
  p.y = Fractions_dup (v.array[1-1].array[2-1]);
  return p;
}


/*
   mp - multiply point, p, by matrix, a, returning a new point.
*/

static Points_Point mp (Points_Point p, PolyMatrix3D_Matrix a)
{
  PolyMatrix3D_MatrixValue v;
  PolyMatrix3D_Matrix i;
  Points_Point q;

  setPointValues (&v, p);
  i = PolyMatrix3D_set (PolyMatrix3D_init (), v);
  i = PolyMatrix3D_mult (i, a);
  i = PolyMatrix3D_get (i, &v);
  q = getPointValues (v);
  return q;
}


/*
   foreachObjectScalar - foreach object scale the scalar values, by, s.
*/

static macroObjects_Macro foreachObjectScalar (macroObjects_Macro n, macroObjects_Macro m, Fractions_Fract s)
{
  Object o;

  o = m->head;
  while (o != NULL)
    {
      switch (o->type)
        {
          case tcircle:
            n = addToEnd (n, objectCircleScalar (o, s));
            break;


          default:
            break;
        }
      o = o->next;
    }
  return n;
}


/*
   objectCircleScalar - scale the radius by, s.
*/

static Object objectCircleScalar (Object o, Fractions_Fract s)
{
  Object p;

  p = initObject ();
  p->type = tcircle;
  p->oCircle.colour = o->oCircle.colour;
  p->oCircle.filled = o->oCircle.filled;
  p->oCircle.thickness = Fractions_dup (o->oCircle.thickness);
  p->oCircle.center = o->oCircle.center;
  p->oCircle.radius = Fractions_mult (o->oCircle.radius, s);
  return p;
}


/*
   objectCircleMatrix - return a new circle object after multiplying
                        all points by, a.
*/

static Object objectCircleMatrix (Object o, PolyMatrix3D_Matrix a)
{
  Object p;

  p = initObject ();
  p->type = tcircle;
  p->oCircle.colour = o->oCircle.colour;
  p->oCircle.filled = o->oCircle.filled;
  p->oCircle.thickness = Fractions_dup (o->oCircle.thickness);
  p->oCircle.center = mp (o->oCircle.center, a);
  p->oCircle.radius = Fractions_dup (o->oCircle.radius);
  return p;
}

static Object objectPolygonMatrix (Object o, PolyMatrix3D_Matrix a)
{
  Object p;
  unsigned int i;

  /* 
   objectPolgonMatrix - return a new polygon object after multiplying
                        all points in, o, by, a.
  */
  p = initObject ();
  p->type = tpolygon;
  p->oPolygon.colour = o->oPolygon.colour;
  p->oPolygon.filled = o->oPolygon.filled;
  p->oPolygon.thickness = Fractions_dup (o->oPolygon.thickness);
  p->oPolygon.noPoints = o->oPolygon.noPoints;
  for (i=0; i<=p->oPolygon.noPoints-1; i++)
    p->oPolygon.pArray.array[i] = mp ((Points_Point) o->oPolygon.pArray.array[i], a);
  return p;
}


/*
   foreachObject - apply matrix, a, to each object in, m, and add it
                   to macro, n.  Macro, n, is returned.
*/

static macroObjects_Macro foreachObject (macroObjects_Macro n, macroObjects_Macro m, PolyMatrix3D_Matrix a)
{
  Object o;

  o = m->head;
  while (o != NULL)
    {
      switch (o->type)
        {
          case tcircle:
            n = addToEnd (n, objectCircleMatrix (o, a));
            break;

          case tpolygon:
            n = addToEnd (n, objectPolygonMatrix (o, a));
            break;


          default:
            CaseException ("../git-pge/m2/macroObjects.def", 1, 15);
        }
      o = o->next;
    }
  return n;
}


/*
   addToEnd -
*/

static macroObjects_Macro addToEnd (macroObjects_Macro m, Object o)
{
  Object n;

  if (m->head == NULL)
    m->head = o;
  else
    {
      n = m->head;
      while (n->next != NULL)
        n = n->next;
      n->next = o;
    }
  o->next = NULL;
  return m;
}


/*
   callCircle -
*/

static void callCircle (Object o, macroObjects_cProc c)
{
  (*c.proc) (o->oCircle.center, o->oCircle.filled, o->oCircle.thickness, o->oCircle.radius, o->oCircle.colour);
}


/*
   callPolygon -
*/

static void callPolygon (Object o, macroObjects_pProc p)
{
  (*p.proc) (o->oPolygon.noPoints, (Points_Point *) &o->oPolygon.pArray.array[0], maxPoints, o->oPolygon.filled, o->oPolygon.thickness, o->oPolygon.colour);
}


/*
   markCircle -
*/

static void markCircle (Object o)
{
  Fractions_mark (o->oCircle.thickness);
  Points_markPoint (o->oCircle.center);
  Fractions_mark (o->oCircle.radius);
}


/*
   markPolygon -
*/

static void markPolygon (Object o)
{
  unsigned int i;

  Fractions_mark (o->oPolygon.thickness);
  i = 0;
  while (i < o->oPolygon.noPoints)
    {
      Points_markPoint ((Points_Point) o->oPolygon.pArray.array[i]);
      i += 1;
    }
}


/*
   markObject -
*/

static void markObject (Object o)
{
  GC_markEntity (o->oentity);
  switch (o->type)
    {
      case tcircle:
        markCircle (o);
        break;

      case tpolygon:
        markPolygon (o);
        break;


      default:
        CaseException ("../git-pge/m2/macroObjects.def", 1, 15);
    }
}


/*
   markMacroEntity - mark macro as specified by, e.
*/

static void markMacroEntity (GC_entity e)
{
  macroObjects_markMacro ((macroObjects_Macro) GC_getData (e));
}


/*
   markObjectEntity - mark object as specified by, e.
*/

static void markObjectEntity (GC_entity e)
{
  markObject ((Object) GC_getData (e));
}


/*
   Init -
*/

static void Init (void)
{
  macroObjects_Macro m;
  Object o;

  macroHeap = GC_initGarbage ((GC_walkP) {(GC_walkP_t) markMacroEntity}, (unsigned int) sizeof ((*m)), DynamicStrings_InitString ((char *) "macro", 5));
  objectHeap = GC_initGarbage ((GC_walkP) {(GC_walkP_t) markObjectEntity}, (unsigned int) sizeof ((*o)), DynamicStrings_InitString ((char *) "objects", 7));
}


/*
   initMacro - creates and returns a macro.
*/

macroObjects_Macro macroObjects_initMacro (void)
{
  macroObjects_Macro m;
  GC_entity e;

  GC_allocate (macroHeap, &e, (void **) &m);
  m->head = NULL;
  m->pos = Points_initPoint (Fractions_zero (), Fractions_zero ());
  m->mentity = e;
  return m;
}


/*
   moveTo - assign the internal position in macro, m, to, p.
*/

macroObjects_Macro macroObjects_moveTo (macroObjects_Macro m, Points_Point p)
{
  m->pos = Points_dupPoint (p);
  return m;
}


/*
   right - move right relatively by, f, units.
*/

macroObjects_Macro macroObjects_right (macroObjects_Macro m, Fractions_Fract f)
{
  m->pos.x = Fractions_inc (m->pos.x, f);
  return m;
}


/*
   left - move left relatively by, f, units.
*/

macroObjects_Macro macroObjects_left (macroObjects_Macro m, Fractions_Fract f)
{
  m->pos.x = Fractions_dec (m->pos.x, f);
  return m;
}


/*
   up - move up relatively by, f, units.
*/

macroObjects_Macro macroObjects_up (macroObjects_Macro m, Fractions_Fract f)
{
  m->pos.y = Fractions_inc (m->pos.y, f);
  return m;
}


/*
   down - move down relatively by, f, units.
*/

macroObjects_Macro macroObjects_down (macroObjects_Macro m, Fractions_Fract f)
{
  m->pos.y = Fractions_dec (m->pos.y, f);
  return m;
}


/*
   rectangle - draw a rectangle at current position which is length, height, units, and is
               filled and has colour, c.
*/

macroObjects_Macro macroObjects_rectangle (macroObjects_Macro m, unsigned int fill, Fractions_Fract thick, deviceIf_Colour c, Fractions_Fract length, Fractions_Fract height)
{
  Object o;

  o = initObject ();
  o->type = tpolygon;
  switch (o->type)
    {
      case tpolygon:
        o->oPolygon.filled = fill;
        o->oPolygon.thickness = thick;
        o->oPolygon.colour = c;
        o->oPolygon.noPoints = 4;
        o->oPolygon.pArray.array[0] = Points_dupPoint (m->pos);
        o->oPolygon.pArray.array[1].x = Fractions_add (m->pos.x, length);
        o->oPolygon.pArray.array[1].y = Fractions_dup (m->pos.y);
        o->oPolygon.pArray.array[2].x = Fractions_add (m->pos.x, length);
        o->oPolygon.pArray.array[2].y = Fractions_add (m->pos.y, height);
        o->oPolygon.pArray.array[3].x = Fractions_dup (m->pos.x);
        o->oPolygon.pArray.array[3].y = Fractions_add (m->pos.y, height);
        break;


      default:
        CaseException ("../git-pge/m2/macroObjects.def", 1, 15);
    }
  return addTo (m, o);
}


/*
   circle - draw a circle at current position of, colour, and radius.
*/

macroObjects_Macro macroObjects_circle (macroObjects_Macro m, unsigned int fill, Fractions_Fract thick, deviceIf_Colour c, Fractions_Fract rad)
{
  Object o;

  o = initObject ();
  o->type = tcircle;
  switch (o->type)
    {
      case tcircle:
        o->oCircle.filled = fill;
        o->oCircle.thickness = thick;
        o->oCircle.colour = c;
        o->oCircle.radius = rad;
        o->oCircle.center.x = Fractions_dup (m->pos.x);
        o->oCircle.center.y = Fractions_dup (m->pos.y);
        break;


      default:
        CaseException ("../git-pge/m2/macroObjects.def", 1, 15);
    }
  return addTo (m, o);
}


/*
   angledRect - add angled rectangle to macro, m.  The angled rectangle four points are defined
                by the current position, cp, cp+v1, cp+v1+v2, cp+v2.
*/

macroObjects_Macro macroObjects_angledRect (macroObjects_Macro m, unsigned int fill, Fractions_Fract thick, deviceIf_Colour c, Points_Point v1, Points_Point v2)
{
  Object o;

  o = initObject ();
  o->type = tpolygon;
  switch (o->type)
    {
      case tpolygon:
        o->oPolygon.filled = fill;
        o->oPolygon.thickness = thick;
        o->oPolygon.colour = c;
        o->oPolygon.noPoints = 4;
        o->oPolygon.pArray.array[0] = Points_dupPoint (m->pos);
        o->oPolygon.pArray.array[1] = Points_addPoint (m->pos, v1);
        o->oPolygon.pArray.array[2] = Points_addPoint (m->pos, Points_addPoint (v1, v2));
        o->oPolygon.pArray.array[3] = Points_addPoint (m->pos, v2);
        break;


      default:
        CaseException ("../git-pge/m2/macroObjects.def", 1, 15);
    }
  return addTo (m, o);
}


/*
   triangle - the triangle is defined by the current position:  cp, cp+v1, cp+v2.
*/

macroObjects_Macro macroObjects_triangle (macroObjects_Macro m, unsigned int fill, Fractions_Fract thick, deviceIf_Colour c, Points_Point v1, Points_Point v2)
{
  Object o;

  o = initObject ();
  o->type = tpolygon;
  switch (o->type)
    {
      case tpolygon:
        o->oPolygon.filled = fill;
        o->oPolygon.thickness = thick;
        o->oPolygon.colour = c;
        o->oPolygon.noPoints = 3;
        o->oPolygon.pArray.array[0] = Points_dupPoint (m->pos);
        o->oPolygon.pArray.array[1] = Points_addPoint (Points_dupPoint (m->pos), v1);
        o->oPolygon.pArray.array[2] = Points_addPoint (Points_addPoint (Points_dupPoint (m->pos), v1), v2);
        break;


      default:
        CaseException ("../git-pge/m2/macroObjects.def", 1, 15);
    }
  return addTo (m, o);
}


/*
   append - returns a new macro which is the result of appending, b, onto the end of, a.
*/

macroObjects_Macro macroObjects_append (macroObjects_Macro a, macroObjects_Macro b)
{
  macroObjects_Macro c;
  Object o;

  c = macroObjects_dup (a);
  o = b->head;
  while (o != NULL)
    {
      c = addToEnd (c, dupObject (o, a->pos));
      o = o->next;
    }
  return c;
}


/*
   rotate - rotate macro, m, about point, p, with angle, r.
            It returns a new macro.
*/

macroObjects_Macro macroObjects_rotate (macroObjects_Macro m, Points_Point p, Fractions_Fract r)
{
  PolyMatrix3D_Matrix a;
  PolyMatrix3D_Matrix b;
  PolyMatrix3D_Matrix c;
  PolyMatrix3D_Matrix d;
  macroObjects_Macro n;

  /* a: translate point, p, to the origin.  */
  a = Transform3D_translate (Points_negatePoint (Points_dupPoint (p)));
  b = Transform3D_rotate (r);  /* b: rotate, r, radians.  */
  c = Transform3D_translate (p);  /* c: translate from origin to point, p.  */
  d = PolyMatrix3D_mult3 (a, b, c);  /* d: combine a, b and c transforms.  */
  n = macroObjects_initMacro ();  /* d: combine a, b and c transforms.  */
  n = foreachObject (n, m, d);  /* n: for every object in, m, transform using, d.  */
  return n;  /* n: for every object in, m, transform using, d.  */
}


/*
   translate - translates macro, m, along, vector.
               It returns a new macro.
*/

macroObjects_Macro macroObjects_translate (macroObjects_Macro m, Points_Point vector)
{
  PolyMatrix3D_Matrix a;
  macroObjects_Macro n;

  a = Transform3D_translate (vector);
  n = macroObjects_initMacro ();
  return foreachObject (n, m, a);
}


/*
   scale - scale macro, m, in the x and y axis.  A new
           macro is returned.
*/

macroObjects_Macro macroObjects_scale (macroObjects_Macro m, Points_Point s)
{
  PolyMatrix3D_Matrix a;
  macroObjects_Macro n;

  a = Transform3D_scale (s);
  n = macroObjects_initMacro ();
  return foreachObject (n, m, a);
}


/*
   dup - duplicates and returns a new macro.
*/

macroObjects_Macro macroObjects_dup (macroObjects_Macro m)
{
  macroObjects_Macro n;
  Object o;

  n = macroObjects_initMacro ();
  n->pos = Points_dupPoint (m->pos);
  o = m->head;
  while (o != NULL)
    {
      n = addToEnd (n, dupObject (o, Points_zeroPoint ()));
      o = o->next;
    }
  return n;
}


/*
   runCallBacks - for each
                           polygon call p
                           circle call c
                                         in macro, m.
*/

void macroObjects_runCallBacks (macroObjects_Macro m, macroObjects_pProc p, macroObjects_cProc c)
{
  Object o;

  o = m->head;
  while (o != NULL)
    {
      switch (o->type)
        {
          case tcircle:
            callCircle (o, c);
            break;

          case tpolygon:
            callPolygon (o, p);
            break;


          default:
            CaseException ("../git-pge/m2/macroObjects.def", 1, 15);
        }
      o = o->next;
    }
}


/*
   rootMacro - register macro, m, with the roots of the garbage collector.
*/

macroObjects_Macro macroObjects_rootMacro (macroObjects_Macro m)
{
  GC_rootEntity (macroHeap, m->mentity, (void *) m);
  return m;
}


/*
   unRootMacro - unroots macro, m, from the garbage collector.
                 Macro, m, can still be used until the garbage collector is called.
*/

macroObjects_Macro macroObjects_unRootMacro (macroObjects_Macro m)
{
  GC_rootDeallocate (macroHeap, &m->mentity, (void **) &m);
  return m;
}


/*
   markMacro - marks macro, m, and marks everything.
*/

void macroObjects_markMacro (macroObjects_Macro m)
{
  Object o;

  GC_markEntity (m->mentity);
  Points_markPoint (m->pos);
  o = m->head;
  while (o != NULL)
    {
      markObject (o);
      o = o->next;
    }
}

void _M2_macroObjects_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  Init ();
}

void _M2_macroObjects_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
