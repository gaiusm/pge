(* Copyright (C) 2010, 2011, 2012
                 Free Software Foundation, Inc. *)
(* This file is part of GNU Modula-2.

GNU Modula-2 is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GNU Modula-2 is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with gm2; see the file COPYING.  If not, write to the Free Software
Foundation, 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA. *)

IMPLEMENTATION MODULE roots ;

FROM libc IMPORT printf ;
FROM libm IMPORT pow, sin, cos, atan2 ;
IMPORT libm ;
IMPORT gdbif ;


CONST
   Epsilon   = 0.000001 ;
   Debugging = FALSE ;

VAR
   tracing: BOOLEAN ;


(*
   roundZero -
*)

PROCEDURE roundZero (r: REAL) : REAL ;
BEGIN
   IF nearZero (r)
   THEN
      RETURN 0.0
   ELSE
      RETURN r
   END
END roundZero ;


(*
   roundRoot -
*)

PROCEDURE roundRoot (r: REAL) : REAL ;
BEGIN
   RETURN roundZero (r)
END roundRoot ;


(*
   roundRoots -
*)

PROCEDURE roundRoots (VAR r: ARRAY OF REAL; n: CARDINAL) ;
VAR
   i: CARDINAL ;
BEGIN
   i := 0 ;
   WHILE i<n DO
      r[i] := roundRoot (r[i]) ;
      INC (i)
   END
END roundRoots ;


(*
   nearZero - returns TRUE if, r, is close to 0.0
*)

PROCEDURE nearZero (r: REAL) : BOOLEAN ;
BEGIN
   IF r>=0.0
   THEN
      RETURN r<Epsilon
   ELSE
      RETURN (-r)<Epsilon
   END
END nearZero ;


(*
   nearSame - returns TRUE if, |a-b| < epsilon
*)

PROCEDURE nearSame (a, b: REAL) : BOOLEAN ;
BEGIN
   RETURN nearZero (a-b)
END nearSame ;


(*
   cnearZero - returns TRUE if the magnitude of, c, is close to 0.
*)

PROCEDURE cnearZero (c: COMPLEX) : BOOLEAN ;
VAR
   r: REAL ;
BEGIN
   r := rsqrt (sqr (RE(c)) + sqr (IM (c))) ;
   RETURN nearZero (r)
END cnearZero ;


(*
   isReal - returns TRUE if the imaginary component of, c, is near zero.
*)

PROCEDURE isReal (c: COMPLEX) : BOOLEAN ;
BEGIN
   RETURN nearZero (IM (c))
END isReal ;


(*
   nearCoord - returns TRUE if position, a, is very close to, b.
*)

PROCEDURE nearCoord (a, b: Coord) : BOOLEAN ;
BEGIN
   RETURN nearSame (a.x, b.x) AND nearSame (a.y, b.y)
END nearCoord ;


(*
   rsqrt - useful for debugging
*)

PROCEDURE rsqrt (r: REAL) : REAL ;
BEGIN
   RETURN libm.sqrt(r)
END rsqrt ;


(*
   sqr - returns r^2
*)

PROCEDURE sqr (r: REAL) : REAL ;
BEGIN
   RETURN r*r
END sqr ;


(*
   cub - returns r^3
*)

PROCEDURE cub (r: REAL) : REAL ;
BEGIN
   RETURN r*r*r
END cub ;


(*
   cubr - returns r^(1/3)
*)

PROCEDURE cubr (r: REAL) : REAL ;
BEGIN
   IF r<0.0
   THEN
      RETURN -pow(-r, 1.0/3.0)
   ELSE
      RETURN pow(r, 1.0/3.0)
   END
END cubr ;


(*
   cpower -
*)

PROCEDURE cpower (c: COMPLEX; r: REAL) : COMPLEX ;
VAR
   radiusr,
   radius ,
   angle  : REAL ;
BEGIN
   (*
    *  use Abraham de Moivre's formula which states that:
    *
    *  (cos(x) + i sin(x))^r = cos(rx) + i sin(rx)
    *)

   radius := rsqrt (RE(c) * RE(c) + IM(c) * IM(c)) ;
   angle := atan2 (IM(c), RE(c)) ;
   radiusr := pow (radius, r) ;

   RETURN CMPLX (radiusr * cos (angle*r),
                 radiusr * sin (angle*r))
END cpower ;


(*
   csqrt - useful for debugging
*)

PROCEDURE csqrt (c: COMPLEX) : COMPLEX ;
BEGIN
   RETURN cpower (c, 1.0/2.0)
END csqrt ;


(*
   csqr - returns c^2
*)

PROCEDURE csqr (c: COMPLEX) : COMPLEX ;
BEGIN
   RETURN c*c
END csqr ;


(*
   ccub - returns c^3
*)

PROCEDURE ccub (c: COMPLEX) : COMPLEX ;
BEGIN
   RETURN c*c*c
END ccub ;


(*
   ccubr - returns c^(1/3)
*)

PROCEDURE ccubr (c: COMPLEX) : COMPLEX ;
BEGIN
   RETURN cpower (c, 1.0/3.0)
END ccubr ;


PROCEDURE mystop ; BEGIN END mystop ;


(*
   findQuadratic - returns TRUE if scalar values of x can be found
                   for.

                     2
                   ax  +  bx + c == 0
*)

PROCEDURE findQuadratic (a, b, c: REAL; VAR x0, x1: REAL) : BOOLEAN ;
VAR
   q, discriminant: REAL ;
BEGIN
   IF tracing
   THEN
      printf ("entered findQuadratic\n")
   END ;
   IF nearZero(a)
   THEN
      IF tracing
      THEN
         printf ("findQuadratic a == 0\n")
      END ;
      IF nearZero(b)
      THEN
         IF tracing
         THEN
            printf ("findQuadratic a == 0, b == 0   -> false\n")
         END ;
         RETURN FALSE
      ELSE
         x0 := -c/b ;
         x0 := roundRoot (x0) ;
         x1 := x0 ;
         IF tracing
         THEN
            printf ("findQuadratic a == 0, x0 = %g, x1 = %g  -> true\n", x0, x1)
         END ;
         RETURN TRUE
      END
   ELSE
      discriminant := sqr (b) - 4.0*a*c ;
      IF discriminant>0.0
      THEN
         q := rsqrt (discriminant) ;
         x0 := (-b + q) / (2.0 * a) ;
         x1 := (-b - q) / (2.0 * a) ;

         x0 := roundRoot (x0) ;
	 x1 := roundRoot (x1) ;
         IF tracing
         THEN
            printf ("findQuadratic discriminant > 0.0, x0 = %g, x1 = %g  -> true\n", x0, x1) ;
            IF nearSame (x1, 0.388415)
            THEN
               (* gdbif.sleepSpin *)
            END
         END ;
         RETURN TRUE
      ELSIF discriminant=0.0
      THEN
         x0 := -b / (2.0 * a) ;
	 x0 := roundRoot (x0) ;
         x1 := x0 ;

         IF tracing
         THEN
            printf ("findQuadratic discriminant = 0.0, x0 = %g, x1 = %g  -> true\n", x0, x1)
         END ;
         RETURN TRUE
      ELSE
         IF tracing
         THEN
            printf ("findQuadratic discriminant < 0.0  -> false\n")
         END ;
         RETURN FALSE
      END
   END
END findQuadratic ;


(*
   findCubic - returns TRUE if a root can be found for

                 3      2
               ax  +  bx  +  cx  +  d  ==  0

               if returns TRUE if it finds a root >= 0
               and will return the smallest root >= 0
*)

PROCEDURE findCubic (a, b, c, d: REAL; VAR x: REAL) : BOOLEAN ;
VAR
   i, j: CARDINAL ;
   X   : ARRAY [1..2] OF REAL ;
BEGIN
   i := 0 ;
   IF nearZero (a)
   THEN
      IF findQuadratic (b, c, d, X[1], X[2])
      THEN
         i := 2
      END
   ELSE
      i := 1 ;
      X[1] := -b/(3.0*a)
              -1.0/(3.0*a) * cubr((2.0*cub(b)-9.0*a*b*c+27.0*sqr(a)*d+rsqrt(sqr(2.0*cub(b)-9.0*a*b*c+27.0*sqr(a)*d)-4.0*cub(sqr(b)-3.0*a*c))))
              -1.0/(3.0*a) * cubr((2.0*cub(b)-9.0*a*b*c+27.0*sqr(a)*d-rsqrt(sqr(2.0*cub(b)-9.0*a*b*c+27.0*sqr(a)*d)-4.0*cub(sqr(b)-3.0*a*c))))
   END ;
   roundRoots (X, i) ;

   IF tracing
   THEN
      printf ("findCubic found %d roots\n", i) ;
      j := 1 ;
      WHILE j<=i DO
         printf ("  root %d  = %g\n", j, X[j]) ;
         INC (j)
      END
   END ;

   j := 1 ;
   x := -1.0 ;
   WHILE j<=i DO
      IF (X[j]>=0.0) AND ((X[j]<x) OR (x<0.0))
      THEN
         x := X[j]
      END ;
      INC (j)
   END ;
   RETURN x>=0.0
END findCubic ;


(*
   findQuartic - returns TRUE if a scalar root can be found for:

                   4      3      2
                 ax  +  bx  +  cx  +  dx +  e  == 0

                 TRUE is only returned if a positive value for
                 x is found and it returns the smallest value for x.
*)

PROCEDURE findQuartic (a, b, c, d, e: REAL; VAR x: REAL) : BOOLEAN ;
VAR
   t    : ARRAY [0..3] OF REAL ;
   i, n : CARDINAL ;
   unset: BOOLEAN ;
BEGIN
   IF a=0.0
   THEN
      RETURN findCubic (b, c, d, e, x)
   ELSE
      IF tracing
      THEN
         printf ("findQuartic finding all roots\n", n)
      END ;
      n := findAllRootsQuartic (a, b, c, d, e, t) ;
      roundRoots (t, n) ;
      IF tracing
      THEN
         printf (" findQuartic found %d roots\n", n) ;
         i := 0 ;
         WHILE i<n DO
            printf ("  root %d  = %g\n", i, t[i]) ;
            INC (i)
         END
      END ;

      unset := TRUE ;
      x := -1.0 ;
      i := 0 ;
      WHILE i<n DO
         IF unset OR ((t[i] >= 0.0) AND (t[i]<x))
         THEN
            unset := FALSE ;
            x := t[i]
         END ;
         INC (i)
      END ;
      IF tracing
      THEN
         printf ("findQuartic x = %g", x) ;
	 IF x >= 0.0
         THEN
            printf (" returning TRUE\n")
         ELSE
            printf (" returning FALSE\n")
         END
      END ;
      RETURN x >= 0.0
   END
END findQuartic ;


(*
   findAllRootsQuartic - returns all the real roots for:

                           4      3      2
                         ax  +  bx  +  cx  +  dx +  e  == 0
*)

PROCEDURE findAllRootsQuartic (a, b, c, d, e: REAL; VAR x: ARRAY OF REAL) : CARDINAL ;
VAR
   i, k                  : CARDINAL ;
   f, p, q,
   alpha, beta, gamma    : REAL ;
   r, u, w, y, z         : COMPLEX ;
   X                     : ARRAY [1..4] OF COMPLEX ;
BEGIN
   alpha := -((3.0 * sqr(b)) / (8.0 * sqr(a))) + c/a ;
   beta  := (cub(b) / (8.0*cub(a))) - ((b * c) / (2.0 * sqr(a))) + d/a ;
   gamma := -(3.0*sqr(b)*sqr(b)) / (256.0 * sqr(a)*sqr(a)) + (c*sqr(b)) / (16.0 * cub(a)) - (b*d)/(4.0*sqr(a)) + e/a ;
   IF beta=0.0
   THEN
      X[1] := CMPLX(-(b / (4.0 * a)), 0.0) + csqrt((CMPLX(-alpha, 0.0) + csqrt(CMPLX(sqr(alpha)-4.0*gamma, 0.0)))/CMPLX(2.0, 0.0)) ;
      X[2] := CMPLX(-(b / (4.0 * a)), 0.0) + csqrt((CMPLX(-alpha, 0.0) - csqrt(CMPLX(sqr(alpha)-4.0*gamma, 0.0)))/CMPLX(2.0, 0.0)) ;
      X[3] := CMPLX(-(b / (4.0 * a)), 0.0) - csqrt((CMPLX(-alpha, 0.0) + csqrt(CMPLX(sqr(alpha)-4.0*gamma, 0.0)))/CMPLX(2.0, 0.0)) ;
      X[4] := CMPLX(-(b / (4.0 * a)), 0.0) - csqrt((CMPLX(-alpha, 0.0) - csqrt(CMPLX(sqr(alpha)-4.0*gamma, 0.0)))/CMPLX(2.0, 0.0))
   ELSE
      p := -sqr(alpha)/12.0 - gamma ;
      q := -(cub(alpha) / 108.0) + (alpha*gamma)/3.0 - sqr(beta)/8.0 ;
      f := sqr(q)/4.0+cub(p)/27.0 ;
      (* as f can be negative we must use complex arithmetic *)
      r := -CMPLX(q/2.0, 0.0) + csqrt(CMPLX(f, 0.0)) ;
      u := ccubr(r) ;
      IF cnearZero(u)
      THEN
         y := -CMPLX((5.0/6.0)*alpha, 0.0) + u - ccubr(CMPLX(q, 0.0))
      ELSE
         y := -CMPLX((5.0/6.0)*alpha, 0.0) + u - CMPLX(p, 0.0)/(CMPLX(3.0, 0.0)*u)
      END ;
      w := csqrt(CMPLX(alpha, 0.0) + CMPLX(+2.0, 0.0) * y) ;

      z := -(CMPLX(3.0 * alpha, 0.0) + CMPLX(2.0, 0.0) * y + (CMPLX(2.0 * beta, 0.0) / w)) ;
      X[1] := -(CMPLX(b/(4.0*a), 0.0)) + (w - csqrt(z)) / CMPLX(2.0, 0.0) ;
      X[2] := -(CMPLX(b/(4.0*a), 0.0)) + (w + csqrt(z)) / CMPLX(2.0, 0.0) ;

      z := -(CMPLX(3.0 * alpha, 0.0) + CMPLX(2.0, 0.0) * y - (CMPLX(2.0 * beta, 0.0) / w)) ;
      X[3] := -(CMPLX(b/(4.0*a), 0.0)) + (-w - csqrt(z)) / CMPLX(2.0, 0.0) ;
      X[4] := -(CMPLX(b/(4.0*a), 0.0)) + (-w + csqrt(z)) / CMPLX(2.0, 0.0) ;
   END ;
   k := 0 ;
   FOR i := 1 TO 4 DO
      IF isReal(X[i])
      THEN
         x[k] := RE(X[i]) ;
         INC(k)
      END
   END ;
   RETURN k
END findAllRootsQuartic ;


(*
   Assert -
*)

PROCEDURE Assert (b: BOOLEAN) ;
BEGIN
   IF NOT b
   THEN
      printf ("assert failed\n")
   END
END Assert ;


(*
   findOctic - returns TRUE if a root >= 0 exists for the equation:

                 8     7    6    5    4    3    2
               ax  + bx + cx + dx + ex + fx + gx + hx + i = 0
*)

PROCEDURE findOctic (a, b, c, d, e, f, g, h, i: REAL; VAR x0: REAL) : BOOLEAN ;
BEGIN
   RETURN FALSE
END findOctic ;


(*
   setTrace - turns tracing on/off.
*)

PROCEDURE setTrace (on: BOOLEAN) ;
BEGIN
   tracing := on
END setTrace ;


PROCEDURE test ;
VAR
   A, B, C, D, E, t, T: REAL ;
BEGIN
   A := 3.0 ;
   B := 6.0 ;
   C := -123.0 ;
   D := -126.0 ;
   E := 1080.0 ;
   IF findQuartic (A, B, C, D, E, t)
   THEN
      (* 5, 3, -4, -6 *)
      T := A*(sqr(t)*sqr(t))+B*(sqr(t)*t)+C*sqr(t)+D*t+E ;
      IF Debugging
      THEN
         printf ("%gt^4 + %gt^3 +%gt^2 + %gt + %g = %g    (t=%g)\n",
                 A, B, C, D, E, T, t)
      END ;
      Assert (t=3.0)
   ELSE
      printf ("failed to find root\n")
   END ;

   A := 1.0 ;
   B := 0.0 ;
   C := -15.0 ;
   D := 10.0 ;
   E := 24.0 ;
   IF findQuartic (A, B, C, D, E, t)
   THEN
      (* (x-3)(x+4)(x+1)(x-2) *)
      T := A*(sqr(t)*sqr(t))+B*(sqr(t)*t)+C*sqr(t)+D*t+E ;
      IF Debugging
      THEN
         printf ("%gt^4 + %gt^3 +%gt^2 + %gt + %g = %g    (t=%g)\n",
                 A, B, C, D, E, T, t)
      END ;
      Assert (t=2.0)
   ELSE
      printf ("failed to find root\n")
   END ;

   A := 1.0 ;
   B := 0.0 ;
   C := -5.0 ;
   D := 0.0 ;
   E := 4.0 ;
   IF findQuartic (A, B, C, D, E, t)
   THEN
      (* (x-1)(x+1)(x-2)(x+2) *)
      T := A*(sqr(t)*sqr(t))+B*(sqr(t)*t)+C*sqr(t)+D*t+E ;
      IF Debugging
      THEN
         printf ("%gt^4 + %gt^3 +%gt^2 + %gt + %g = %g    (t=%g)\n",
                 A, B, C, D, E, T, t)
      END ;
      Assert (t=1.0)
   ELSE
      printf ("failed to find root\n")
   END
END test ;


BEGIN
   tracing := Debugging
END roots.
