(* Copyright (C) 2012, 2013 Free Software Foundation, Inc. *)
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

IMPLEMENTATION MODULE Fractions ;

FROM libc IMPORT strlen, strncpy, write, exit, printf ;
FROM StrLib IMPORT StrLen ;
FROM GC IMPORT garbage, entity, initGarbage, markEntity, allocate, rootDeallocate, rootAllocate, rootEntity, getData ;
FROM Assertion IMPORT Assert ;
FROM StringConvert IMPORT LongrealToString ;
FROM DynamicStrings IMPORT String, string, KillString ;
FROM SYSTEM IMPORT ADR, ADDRESS, TSIZE ;
FROM ASCII IMPORT nul, tab, lf ;
FROM DynamicStrings IMPORT InitString ;

CONST
   runRegression = FALSE ;

TYPE
   doProcedure = PROCEDURE (Fract) : BOOLEAN ;

   Special = (NONE, PI, E, ROOT2, ROOT3, ROOT6, EXPR) ;

   Operator = (oFract, oAdd, oSub, oMult, oDiv, oNegate, oPower, oSin, oCos, oTan) ;

   Fract = POINTER TO fract ;
   fract =            RECORD
                         positive: BOOLEAN ;
                         whole   : LONGCARD ;
                         num,
                         demon   : LONGCARD ;
                         op      : Operator ;
                         left,
                         right   : Fract ;    (* operators to, op.                  *)
                         dirty   : BOOLEAN ;  (* has this fraction been simplified? *)
                         special : Special ;
                         fentity : entity ;
                       END ;

CONST
   trigTerm = 5 ;


(* %%%FORWARD%%%
PROCEDURE writeDesc (f: Fract) ; FORWARD ;
PROCEDURE writeNspace (n: CARDINAL) ; FORWARD ;
PROCEDURE Capture (f: Fract) : CARDINAL ; FORWARD ;
PROCEDURE isSpecial (f: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE isConst (f: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE isSpecialConst (f: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE isExpr (f: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE checkPoisoned (f: Fract) : Fract ; FORWARD ;
PROCEDURE writeString (a: ARRAY OF CHAR) ; FORWARD ;
PROCEDURE writeCstring (a: ADDRESS) ; FORWARD ;
PROCEDURE writeLongcard (c: LONGCARD) ; FORWARD ;
PROCEDURE writeLongint (i: LONGINT) ; FORWARD ;
PROCEDURE writeLn ; FORWARD ;
PROCEDURE AssignDebug (f: Fract; file: ARRAY OF CHAR; line: CARDINAL; proc: ARRAY OF CHAR) : Fract ; FORWARD ;
PROCEDURE dirty (f: Fract) : Fract ; FORWARD ;
PROCEDURE clean (f: Fract) : Fract ; FORWARD ;
PROCEDURE pi () : Fract ; FORWARD ;
PROCEDURE zero () : Fract ; FORWARD ;
PROCEDURE one () : Fract ; FORWARD ;
PROCEDURE two () : Fract ; FORWARD ;
PROCEDURE half () : Fract ; FORWARD ;
PROCEDURE quarter () : Fract ; FORWARD ;
PROCEDURE oneOverN (n: LONGCARD) : Fract ; FORWARD ;
PROCEDURE root2 () : Fract ; FORWARD ;
PROCEDURE root3 () : Fract ; FORWARD ;
PROCEDURE root6 () : Fract ; FORWARD ;
PROCEDURE integer (i: LONGINT) : Fract ; FORWARD ;
PROCEDURE cardinal (i: LONGCARD) : Fract ; FORWARD ;
PROCEDURE isZero (f: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE isEqual (l, r: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE isLess (l, r: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE negatec (f: Fract) : Fract ; FORWARD ;
PROCEDURE negates (f: Fract) : Fract ; FORWARD ;
PROCEDURE negate (f: Fract) : Fract ; FORWARD ;
PROCEDURE equalDemon (l, r: Fract) ; FORWARD ;
PROCEDURE addND (l, r: Fract) ; FORWARD ;
PROCEDURE inc (l, r: Fract) : Fract ; FORWARD ;
PROCEDURE subND (l, r: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE dec (l, r: Fract) : Fract ; FORWARD ;
PROCEDURE addc (l, r: Fract) : Fract ; FORWARD ;
PROCEDURE buildUnary (operator: Operator; l: Fract) : Fract ; FORWARD ;
PROCEDURE buildBinary (operator: Operator; l, r: Fract) : Fract ; FORWARD ;
PROCEDURE adds (l, r: Fract) : Fract ; FORWARD ;
PROCEDURE add (l, r: Fract) : Fract ; FORWARD ;
PROCEDURE powers (l, r: Fract) : Fract ; FORWARD ;
PROCEDURE powerc (l, r: Fract) : Fract ; FORWARD ;
PROCEDURE power (l, r: Fract) : Fract ; FORWARD ;
PROCEDURE mults (l, r: Fract) : Fract ; FORWARD ;
PROCEDURE mult (l, r: Fract) : Fract ; FORWARD ;
PROCEDURE multc (l, r: Fract) : Fract ; FORWARD ;
PROCEDURE divc (l, r: Fract) : Fract ; FORWARD ;
PROCEDURE divs (l, r: Fract) : Fract ; FORWARD ;
PROCEDURE div (l, r: Fract) : Fract ; FORWARD ;
PROCEDURE reciprocal (f: Fract) : Fract ; FORWARD ;
PROCEDURE reciprocals (f: Fract) : Fract ; FORWARD ;
PROCEDURE reciprocalc (f: Fract) : Fract ; FORWARD ;
PROCEDURE subc (l, r: Fract) : Fract ; FORWARD ;
PROCEDURE subs (l, r: Fract) : Fract ; FORWARD ;
PROCEDURE sub (l, r: Fract) : Fract ; FORWARD ;
PROCEDURE simplifyc (f: Fract) : Fract ; FORWARD ;
PROCEDURE simplify (f: Fract) : Fract ; FORWARD ;
PROCEDURE walkExpr (f: Fract; p: doProcedure) : BOOLEAN ; FORWARD ;
PROCEDURE simplifys (f: Fract) : Fract ; FORWARD ;
PROCEDURE doFract (f: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE doRules (f: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE areEqual (l, r: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE doSub (f: Fract; l, r: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE doAdd (f: Fract; l, r: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE doMult (f: Fract; l, r: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE doPower (f: Fract; l, r: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE doNegate (f: Fract; l: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE doDiv (f: Fract; l, r: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE angleIs (a, v, f, r: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE doSin (f: Fract; l: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE doCos (f: Fract; l: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE doTan (f: Fract; l: Fract) : BOOLEAN ; FORWARD ;
PROCEDURE gcd (x, y: LONGCARD) : LONGCARD ; FORWARD ;
PROCEDURE newFract () : Fract ; FORWARD ;
PROCEDURE initFract (w: LONGINT; n, d: LONGCARD) : Fract ; FORWARD ;
PROCEDURE killFract (f: Fract) : Fract ; FORWARD ;
PROCEDURE makeSpecial (f: Fract; s: Special) : Fract ; FORWARD ;
PROCEDURE pf (f: Fract) ; FORWARD ;
PROCEDURE writeMath (o: ARRAY OF CHAR; l: Fract) ; FORWARD ;
PROCEDURE writeUnary (o: ARRAY OF CHAR; l: Fract) ; FORWARD ;
PROCEDURE writeBinary (o: ARRAY OF CHAR; l, r: Fract) ; FORWARD ;
PROCEDURE writeOp (f: Fract) ; FORWARD ;
PROCEDURE writeFracts (f: Fract) ; FORWARD ;
PROCEDURE writeFractc (f: Fract) ; FORWARD ;
PROCEDURE writeFract (f: Fract) ; FORWARD ;
PROCEDURE pd (f: Fract) ; FORWARD ;
PROCEDURE log10 (l: LONGCARD) : CARDINAL ; FORWARD ;
PROCEDURE writeDecimal (f: Fract) ; FORWARD ;
PROCEDURE mark (f: Fract) ; FORWARD ;
PROCEDURE dup (f: Fract) : Fract ; FORWARD ;
PROCEDURE addToGarbage (f, g: Fract) : Fract ; FORWARD ;
PROCEDURE sinc (x: Fract) : Fract ; FORWARD ;
PROCEDURE sin (f: Fract) : Fract ; FORWARD ;
PROCEDURE tanc (f: Fract) : Fract ; FORWARD ;
PROCEDURE tan (f: Fract) : Fract ; FORWARD ;
PROCEDURE init ; FORWARD ;
PROCEDURE regressionTest ; FORWARD ;
   %%%FORWARD%%% *)

VAR
   Initialized: BOOLEAN ;
   fractHeap  : garbage ;
   captured   : Fract ;


(*
   writeCard -
*)

PROCEDURE writeCard (c: CARDINAL) ;
VAR
   ch: CHAR ;
   i : INTEGER ;
BEGIN
   IF c>9
   THEN
      writeCard(c DIV 10) ;
      writeCard(c MOD 10)
   ELSE
      ch := CHR(ORD('0')+c) ;
      i := write(1, ADR(ch), 1)
   END
END writeCard ;


(*
   writeAddress -
*)

PROCEDURE writeAddress (a: ADDRESS) ;
BEGIN
   writeLongcard(VAL(LONGCARD, a))
END writeAddress ;


(*
   writeNspace -
*)

PROCEDURE writeNspace (n: CARDINAL) ;
BEGIN
   WHILE n>0 DO
      writeString(' ') ;
      DEC(n)
   END
END writeNspace ;



PROCEDURE capture (f: Fract) : CARDINAL ;
BEGIN
   captured := f ;
   RETURN 1;
END capture ;


(*
   isSpecial - return TRUE if, f, is a special.
*)

PROCEDURE isSpecial (f: Fract) : BOOLEAN ;
BEGIN
   RETURN f^.special#NONE
END isSpecial ;


(*
   isConst - returns if, f, is a fractional constant.
*)

PROCEDURE isConst (f: Fract) : BOOLEAN ;
BEGIN
   RETURN f^.special=NONE
END isConst ;


(*
   isSpecialConst -
*)

PROCEDURE isSpecialConst (f: Fract) : BOOLEAN ;
BEGIN
   WITH f^ DO
      RETURN (special=PI) OR (special=E) OR (special=ROOT2) OR (special=ROOT3) OR (special=ROOT6)
   END
END isSpecialConst ;


(*
   isExpr - return TRUE if, f, is an expression.
*)

PROCEDURE isExpr (f: Fract) : BOOLEAN ;
BEGIN
   RETURN f^.special=EXPR
END isExpr ;


(*
   writeString - writes a string to stdout.
*)

PROCEDURE writeString (a: ARRAY OF CHAR) ;
VAR
   i: INTEGER ;
BEGIN
   i := write(1, ADR(a), StrLen(a))
END writeString ;


(*
   writeCstring - writes a C string to stdout.
*)

PROCEDURE writeCstring (a: ADDRESS) ;
VAR
   i: INTEGER ;
BEGIN
   IF a=NIL
   THEN
      writeString('(null)')
   ELSE
      i := write(1, a, strlen(a))
   END
END writeCstring ;


(*
   writeLongcard -
*)

PROCEDURE writeLongcard (c: LONGCARD) ;
VAR
   ch: CHAR ;
   i : INTEGER ;
BEGIN
   IF c>9
   THEN
      writeLongcard(c DIV 10) ;
      writeLongcard(c MOD 10)
   ELSE
      ch := CHR(ORD('0')+VAL(CARDINAL, c)) ;
      i := write(1, ADR(ch), 1)
   END
END writeLongcard ;


(*
   writeLongint -
*)

PROCEDURE writeLongint (i: LONGINT) ;
VAR
   ch: CHAR ;
   j : INTEGER ;
BEGIN
   IF i<0
   THEN
      writeString("-") ;
      writeLongint(-i)
   ELSIF i>=10
   THEN
      writeLongint(i DIV 10) ;
      writeLongint(i MOD 10)
   ELSIF i<10
   THEN
      ch := CHR(ORD('0')+VAL(CARDINAL, i)) ;
      j := write(1, ADR(ch), 1)
   END
END writeLongint ;


(*
   writeLn - writes a newline.
*)

PROCEDURE writeLn ;
VAR
   ch: CHAR ;
   i : INTEGER ;
BEGIN
   ch := lf ;
   i := write(1, ADR(ch), 1)
END writeLn ;


(*
   dirty - sets Fract, f, to dirty.
*)

PROCEDURE dirty (f: Fract) : Fract ;
BEGIN
   f^.dirty := TRUE ;
   RETURN f
END dirty ;


(*
   clean - sets Fract, f, to clean.
*)

PROCEDURE clean (f: Fract) : Fract ;
BEGIN
   f^.dirty := FALSE ;
   RETURN f
END clean ;


(*
   pi - returns the approximation of pi as a Fract.
*)

PROCEDURE pi () : Fract ;
BEGIN
   RETURN makeSpecial(initFract(3, 1, 7), PI)
(*
   RETURN initFract(3, 14, 100)
*)
(*
   RETURN initFract(3, 141592653589, 1000000000000)
*)
(*
   RETURN initFract(3, 1, 7)
*)
END pi ;


(*
   zero - returns the fraction, 0.
*)

PROCEDURE zero () : Fract ;
BEGIN
   RETURN initFract(0, 0, 0)
END zero ;


(*
   one - returns the fraction, 1/1.
*)

PROCEDURE one () : Fract ;
BEGIN
   RETURN initFract(1, 0, 0)
END one ;


(*
   two - returns the value 2 as a fraction.
*)

PROCEDURE two () : Fract ;
BEGIN
   RETURN initFract(2, 0, 0)
END two ;


(*
   half - returns 1/2.
*)

PROCEDURE half () : Fract ;
BEGIN
   RETURN oneOverN(2)
END half ;


(*
   quarter - returns 1/4.
*)

PROCEDURE quarter () : Fract ;
BEGIN
   RETURN oneOverN(4)
END quarter ;


(*
   oneOverN - returns 1/n.
*)

PROCEDURE oneOverN (n: LONGCARD) : Fract ;
BEGIN
   RETURN initFract(0, 1, n)
END oneOverN ;


(*
   root2 -
*)

PROCEDURE root2 () : Fract ;
BEGIN
   RETURN makeSpecial(initFract(0, 707, 1000), ROOT2)
END root2 ;


(*
   root3 - returns 3^.5.
*)

PROCEDURE root3 () : Fract ;
BEGIN
   RETURN makeSpecial(initFract(1, 732, 1000), ROOT3)
END root3 ;


(*
   root6 - returns 6^.5.
*)

PROCEDURE root6 () : Fract ;
BEGIN
   RETURN makeSpecial(initFract(2, 449, 1000), ROOT6)
END root6 ;


(*
   integer - return, i, as a fraction.
*)

PROCEDURE integer (i: LONGINT) : Fract ;
BEGIN
   IF i>=0
   THEN
      RETURN initFract(VAL(LONGCARD, i), 0, 0)
   ELSE
      RETURN negate(initFract(VAL(LONGCARD, -i), 0, 0))
   END
END integer ;


(*
   cardinal - returns a cardinal as a fraction.
*)

PROCEDURE cardinal (i: LONGCARD) : Fract ;
BEGIN
   RETURN initFract(i, 0, 0)
END cardinal ;


(*
   isZero - returns TRUE if the fraction is zero.
*)

PROCEDURE isZero (f: Fract) : BOOLEAN ;
BEGIN
   f := simplify(f) ;
   WITH f^ DO
      RETURN (whole=0) AND (num=0)
   END
END isZero ;


(*
   isOne - returns TRUE if the fraction is one.
*)

PROCEDURE isOne (f: Fract) : BOOLEAN ;
BEGIN
   f := simplify(f) ;
   WITH f^ DO
      RETURN (whole=1) AND (num=0)
   END
END isOne ;


(*
   isEqual - returns TRUE if Fracts, l, and, r, are equal.
*)

PROCEDURE isEqual (l, r: Fract) : BOOLEAN ;
BEGIN
   l := simplify(l) ;
   r := simplify(r) ;
   RETURN (l^.positive = r^.positive) AND (l^.whole = r^.whole) AND (l^.num = r^.num) AND (l^.demon = r^.demon)
END isEqual ;


(*
   isLess - returns TRUE if l < r.
*)

PROCEDURE isLess (l, r: Fract) : BOOLEAN ;
VAR
   tl, tr: Fract ;
BEGIN
   (* handle different signs first *)
   IF l^.positive#r^.positive
   THEN
      RETURN r^.positive
   END ;
   (* now check whole numbers *)
   IF l^.positive
   THEN
      IF l^.whole<r^.whole
      THEN
         RETURN TRUE
      ELSIF l^.whole>r^.whole
      THEN
         RETURN FALSE
      END ;
      l := simplify(l) ;
      r := simplify(r) ;
      tl := dup(l) ;
      tr := dup(r) ;
      equalDemon(tl, tr) ;
      RETURN tl^.num<tr^.num
   ELSE
      IF l^.whole>r^.whole
      THEN
         RETURN TRUE
      ELSIF l^.whole<r^.whole
      THEN
         RETURN FALSE
      END ;
      l := simplify(l) ;
      r := simplify(r) ;
      tl := dup(l) ;
      tr := dup(r) ;
      equalDemon(tl, tr) ;
      RETURN tl^.num>tr^.num
   END
END isLess ;


(*
   isGreater - returns TRUE if l > r.
*)

PROCEDURE isGreater (l, r: Fract) : BOOLEAN ;
VAR
   tl, tr: Fract ;
BEGIN
   (* handle different signs first *)
   IF l^.positive#r^.positive
   THEN
      RETURN l^.positive
   END ;
   (* now check whole numbers *)
   IF l^.positive
   THEN
      IF l^.whole>r^.whole
      THEN
         RETURN TRUE
      ELSIF l^.whole<r^.whole
      THEN
         RETURN FALSE
      END ;
      l := simplify(l) ;
      r := simplify(r) ;
      tl := dup(l) ;
      tr := dup(r) ;
      equalDemon(tl, tr) ;
      RETURN tl^.num>tr^.num
   ELSE
      IF l^.whole<r^.whole
      THEN
         RETURN TRUE
      ELSIF l^.whole>r^.whole
      THEN
         RETURN FALSE
      END ;
      l := simplify(l) ;
      r := simplify(r) ;
      tl := dup(l) ;
      tr := dup(r) ;
      equalDemon(tl, tr) ;
      RETURN tl^.num<tr^.num
   END
END isGreater ;


(*
   negatec - negates constant, -f.
*)

PROCEDURE negatec (f: Fract) : Fract ;
BEGIN
   IF NOT isZero(f)
   THEN
      f^.positive := NOT f^.positive
   END ;
   RETURN f
END negatec ;


(*
   negates - negate special.
*)

PROCEDURE negates (f: Fract) : Fract ;
BEGIN
   RETURN buildUnary(oNegate, f)
END negates ;


(*
   negate - negate fraction, f.
*)

PROCEDURE negate (f: Fract) : Fract ;
BEGIN
   f := dup(f) ;
   IF isSpecial(f)
   THEN
      RETURN negates(f)
   ELSE
      RETURN negatec(f)
   END
END negate ;


(*
   equalDemon - converts both fractions to have equal demoninators.
*)

PROCEDURE equalDemon (l, r: Fract) ;
VAR
   g, lg, rg: LONGCARD ;
BEGIN
   IF (l^.num=0) AND (r^.num=0)
   THEN
      l^.demon := 0 ;
      r^.demon := 0
   ELSIF l^.num=0
   THEN
      l^.demon := r^.demon
   ELSIF r^.num=0
   THEN
      r^.demon := l^.demon
   ELSE
      (* need to convert them *)
      g := gcd(l^.demon, r^.demon) ;
      lg := r^.demon DIV g ;
      rg := l^.demon DIV g ;
      l^.num := (l^.num * lg) ;
      l^.demon := l^.demon * lg ;
      r^.num :=  r^.num * rg ;
      r^.demon := l^.demon * rg
   END
END equalDemon ;


(*
   addND - add the numerator/demonimator pairs of, l, and, r.
           It propagates the carry into whole.
           l := l+r  is performed.
*)

PROCEDURE addND (l, r: Fract) ;
VAR
   g, lg, rg: LONGCARD ;
BEGIN
   IF l^.num=0
   THEN
      l^.num := r^.num ;
      l^.demon := r^.demon
   ELSIF r^.num=0
   THEN
      (* nothing to do *)
   ELSE
      g := gcd(l^.demon, r^.demon) ;
      lg := r^.demon DIV g ;
      rg := l^.demon DIV g ;

      l^.num := (l^.num * lg) + (r^.num * rg) ;
      l^.demon := l^.demon * lg ;
      l := simplify(l)   (* handles carry *)
   END
END addND ;


(*
   inc - returns, l, after, r, has been added.
*)

PROCEDURE inc (l, r: Fract) : Fract ;
VAR
   n: BOOLEAN ;
BEGIN
   l := simplify(l) ;
   r := simplify(r) ;
   IF isZero(r)
   THEN
      RETURN l
   ELSIF isZero(l)
   THEN
      l^.positive := r^.positive ;
      l^.whole := r^.whole ;
      l^.num := r^.num ;
      l^.demon := r^.demon ;
      RETURN dirty(l)
   END ;
   IF r=l
   THEN
      r := dup(l)
   END ;
   IF l^.positive=r^.positive
   THEN
      l := dirty(l) ;
      l^.whole := l^.whole+r^.whole ;
      addND(l, r)
   ELSIF l^.positive AND (NOT r^.positive)
   THEN
      l := dec(l, negate(r))
   ELSIF (NOT l^.positive) AND r^.positive
   THEN
      l := negate(dec(negate(l), r))
   ELSE
      HALT
   END ;
   RETURN l
END inc ;


(*
   subND - sub the numerator/demonimator pairs of, l, and, r.
           It returns TRUE if it needs to borrow.
           l := l-r  is performed.
*)

PROCEDURE subND (l, r: Fract) : BOOLEAN ;
VAR
   g, lg, rg: LONGCARD ;
BEGIN
   IF l^.num=0
   THEN
      l^.num := r^.demon-r^.num ;
      l^.demon := r^.demon ;
      l := dirty(l) ;
      RETURN r^.num#0
   ELSIF r^.num=0
   THEN
      (* nothing to do *)
      RETURN FALSE
   ELSE
      l := dirty(l) ;
      g := gcd(l^.demon, r^.demon) ;
      lg := r^.demon DIV g ;
      rg := l^.demon DIV g ;

      IF (l^.num * lg) >= (r^.num * rg)
      THEN
         (* no need to borrow *)
         l^.num := (l^.num * lg) - (r^.num * rg) ;
         l^.demon := l^.demon * lg ;
         RETURN FALSE
      ELSE
         (* need to borrow *)
         l^.demon := l^.demon * lg ;
         l^.num := (r^.num * rg) - (l^.num * lg) ;
         RETURN TRUE
      END
   END
END subND ;


(*
   dec - returns, l, after, r, has been subtracted.
*)

PROCEDURE dec (l, r: Fract) : Fract ;
VAR
   n   : BOOLEAN ;
   t, s: Fract ;
BEGIN
   l := simplify(l) ;
   r := simplify(r) ;
   IF isZero(r)
   THEN
      RETURN l
   ELSIF isZero(l)
   THEN
      IF isZero(r)
      THEN
         l^.positive := TRUE
      ELSE
         l^.positive := NOT r^.positive
      END ;
      l^.whole := r^.whole ;
      l^.num := r^.num ;
      l^.demon := r^.demon ;
      RETURN dirty(l)
   END ;
   IF r=l
   THEN
      r := dup(l)
   END ;
   IF l^.positive AND r^.positive
   THEN
      l := dirty(l) ;
      IF r^.whole<=l^.whole
      THEN
         (* positive whole result *)
         l^.whole := l^.whole-r^.whole ;
         IF isZero(l)
         THEN
            l^.num := r^.num ;
            l^.demon := r^.demon ;
            IF (l^.whole=0) AND (l^.num=0)
            THEN
               l^.positive := TRUE
            ELSE
               l^.positive := FALSE
            END
         ELSIF subND(l, r)
         THEN
            IF l^.whole>=1
            THEN
               DEC(l^.whole)
            ELSE
               l^.positive := FALSE
            END
         END
      ELSE
         (* negative whole result, therefore flip the operands and subtract *)
         l^.whole := r^.whole-l^.whole ;
         l^.positive := FALSE ;
         s := initFract(0, l^.num, l^.demon) ;
         t := initFract(0, r^.num, r^.demon) ;
         IF subND(t, s)
         THEN
            DEC(l^.whole)
         END ;
         l^.num := t^.num ;
         l^.demon := t^.demon
      END
   ELSIF (NOT l^.positive) AND (NOT r^.positive)
   THEN
      l := inc(l, negate(r))
   ELSIF l^.positive AND (NOT r^.positive)
   THEN
      l := inc(l, negate(r))
   ELSIF (NOT l^.positive) AND r^.positive
   THEN
      RETURN negate(inc(negate(l), r))
   ELSE
      HALT
   END ;
   RETURN simplify(l)
END dec ;


(*
   addc - add constant fractions.
*)

PROCEDURE addc (l, r: Fract) : Fract ;
VAR
   f: Fract ;
BEGIN
   f := simplify(dup(l)) ;
   r := simplify(r) ;
   f := simplify(inc(f, r)) ;
   RETURN f
END addc ;


(*
   buildUnary - returns (operator, l).
*)

PROCEDURE buildUnary (operator: Operator; l: Fract) : Fract ;
BEGIN
   RETURN buildBinary(operator, l, NIL)
END buildUnary ;


(*
   buildBinary - returns (operator, l, r).
*)

PROCEDURE buildBinary (operator: Operator; l, r: Fract) : Fract ;
VAR
   f: Fract ;
BEGIN
   f := initFract(0, 0, 0) ;
   WITH f^ DO
      op := operator ;
      special := EXPR ;
      left := l ;
      right := r
   END ;
   RETURN f
END buildBinary ;


(*
   adds - returns expression l + r.
*)

PROCEDURE adds (l, r: Fract) : Fract ;
BEGIN
   RETURN buildBinary(oAdd, l, r)
END adds ;


(*
   add - returns a new fraction of the result, l+r.
*)

PROCEDURE add (l, r: Fract) : Fract ;
BEGIN
   IF isSpecial(l) OR isSpecial(r)
   THEN
      RETURN adds(l, r)
   ELSE
      RETURN addc(l, r)
   END
END add ;


(*
   add3 - returns a new fraction which contains the result of a+b+c.
*)

PROCEDURE add3 (a, b, c: Fract) : Fract ;
BEGIN
   RETURN add(a, add(b, c))
END add3 ;


(*
   mult3 - returns a new fraction which contains the result of a * b * c.
*)

PROCEDURE mult3 (a, b, c: Fract) : Fract ;
BEGIN
   RETURN mult(a, mult(b, c))
END mult3 ;


(*
   powers - return an expression l^r.
*)

PROCEDURE powers (l, r: Fract) : Fract ;
BEGIN
   RETURN buildBinary(oPower, l, r)
END powers ;


(*
   powerc - compute constant, l^r
*)

PROCEDURE powerc (l, r: Fract) : Fract ;
BEGIN
   RETURN powers(l, r)   (* --fixme-- improve this, maybe *)
END powerc ;


(*
   power - return l^r.
*)

PROCEDURE power (l, r: Fract) : Fract ;
BEGIN
   IF isSpecial(l) OR isSpecial(r)
   THEN
      RETURN powers(l, r)
   ELSE
      RETURN powerc(l, r)
   END
END power ;


(*
   mults - returns expression l * r.
*)

PROCEDURE mults (l, r: Fract) : Fract ;
BEGIN
   RETURN buildBinary(oMult, l, r)
END mults ;


(*
   mult - return l * r
*)

PROCEDURE mult (l, r: Fract) : Fract ;
BEGIN
   IF isSpecial(l) OR isSpecial(r)
   THEN
      RETURN mults(l, r)
   ELSE
      RETURN multc(l, r)
   END
END mult ;


(*
   multc - calculate l * r from constants.
*)

PROCEDURE multc (l, r: Fract) : Fract ;
VAR
   f: Fract ;
   n: BOOLEAN ;
BEGIN
   l := simplify(l) ;
   IF l=r
   THEN
      r := dup(l)
   ELSE
      r := simplify(r)
   END ;
   IF l^.positive AND r^.positive
   THEN
      f := inc(inc(cardinal(l^.whole*r^.whole),
                   inc(initFract(0, l^.whole * r^.num, r^.demon),
                       initFract(0, r^.whole * l^.num, l^.demon))),
               initFract(0, l^.num*r^.num, l^.demon*r^.demon))
   ELSIF l^.positive
   THEN
      Assert(NOT r^.positive) ;
      r := negate(r) ;
      f := inc(inc(negate(cardinal(l^.whole*r^.whole)),
                   inc(negate(initFract(0, l^.whole * r^.num, r^.demon)),
                       negate(initFract(0, r^.whole * l^.num, l^.demon)))),
               negate(initFract(0, l^.num*r^.num, l^.demon*r^.demon)))
   ELSIF r^.positive
   THEN
      Assert(NOT l^.positive) ;
      l := negate(l) ;
      f := inc(inc(negate(cardinal(l^.whole*r^.whole)),
                   inc(negate(initFract(0, l^.whole * r^.num, r^.demon)),
                       negate(initFract(0, r^.whole * l^.num, l^.demon)))),
               negate(initFract(0, l^.num*r^.num, l^.demon*r^.demon)))
   ELSE
      Assert((NOT l^.positive) AND (NOT r^.positive)) ;
      l := negate(l) ;
      r := negate(r) ;
      f := inc(inc(cardinal(l^.whole*r^.whole),
                   inc(initFract(0, l^.whole * r^.num, r^.demon),
                       initFract(0, r^.whole * l^.num, l^.demon))),
               initFract(0, l^.num*r^.num, l^.demon*r^.demon))
   END ;
   RETURN simplify(f)
END multc ;


(*
   divc - calculate l / r from constants.
*)

PROCEDURE divc (l, r: Fract) : Fract ;
BEGIN
   l := simplify(l) ;
   r := simplify(r) ;
   IF isZero(r)
   THEN
      HALT
   END ;
   IF isEqual(l, r)
   THEN
      RETURN one()
   ELSE
      RETURN mult(l, reciprocal(r))
   END
END divc ;


(*
   divs - calculate l / r from one or more specials.
*)

PROCEDURE divs (l, r: Fract) : Fract ;
BEGIN
   RETURN buildBinary(oDiv, l, r)
END divs ;


(*
   div - return l / r.
*)

PROCEDURE div (l, r: Fract) : Fract ;
BEGIN
   IF isSpecial(l) OR isSpecial(r)
   THEN
      RETURN divs(l, r)
   ELSE
      RETURN divc(l, r)
   END
END div ;


(*
   reciprocal - return 1/f.
*)

PROCEDURE reciprocal (f: Fract) : Fract ;
BEGIN
   IF isSpecial(f)
   THEN
      RETURN reciprocals(f)
   ELSE
      RETURN reciprocalc(f)
   END
END reciprocal ;


(*
   reciprocals - return 1/f from a special.
*)

PROCEDURE reciprocals (f: Fract) : Fract ;
BEGIN
   RETURN buildBinary(oDiv, one(), f)
END reciprocals ;


(*
   reciprocalc - return 1/f from a constant.
*)

PROCEDURE reciprocalc (f: Fract) : Fract ;
VAR
   r: Fract ;
BEGIN
   WITH f^ DO
      IF (num=0) AND (whole=0)
      THEN
         r := initFract(0, 0, 0)
      ELSIF num=0
      THEN
         (* only a whole number *)
         r := initFract(0, 1, whole)
      ELSE
         r := initFract(0, demon, whole*demon+num)
      END ;
      IF NOT positive
      THEN
         r := negate(r)
      END
   END ;
   RETURN simplify(r)
END reciprocalc ;


(*
   subc - returns a constant from, l - r.
*)

PROCEDURE subc (l, r: Fract) : Fract ;
VAR
   f: Fract ;
BEGIN
   f := simplify(dup(l)) ;
   f := simplify(dec(f, r)) ;
   RETURN f
END subc ;


(*
   subs - returns the expression, l - r.
*)

PROCEDURE subs (l, r: Fract) : Fract ;
BEGIN
   RETURN buildBinary(oSub, l, r)
END subs ;


(*
   sub - returns the expression, l - r.
*)

PROCEDURE sub (l, r: Fract) : Fract ;
BEGIN
   IF isSpecial(l) OR isSpecial(r)
   THEN
      RETURN subs(l, r)
   ELSE
      RETURN subc(l, r)
   END
END sub ;


(*
   stop - debugging hook.
*)

PROCEDURE stop ; BEGIN END stop ;


(*
   simplifyc - returns a simplified fraction, f.
*)

PROCEDURE simplifyc (f: Fract) : Fract ;
VAR
   d: LONGCARD ;
BEGIN
   WITH f^ DO
      IF NOT dirty
      THEN
         RETURN f
      END ;
      IF (num#0) AND (demon#0)
      THEN
         IF num>demon
         THEN
            d := num/demon ;
            IF whole>=0
            THEN
               INC(whole, d)
            ELSE
               DEC(whole, d)
            END ;
            num := num MOD demon
         END ;
         IF (num#0) AND (demon#0)
         THEN
            d := gcd(num, demon) ;
            IF d>1
            THEN
               num := num DIV d ;
               demon := demon DIV d
            END
         END ;
         IF num=demon
         THEN
            Assert(num=1) ;
            num := 0 ;
            demon := 0 ;
            INC(whole)
         END
      END ;
      IF num=0
      THEN
         demon := 0
      END
   END ;
   RETURN clean(f)
END simplifyc ;


(*
   simplify - simplify the fraction or expression.
*)

PROCEDURE simplify (f: Fract) : Fract ;
BEGIN
   IF isSpecial(f)
   THEN
      RETURN simplifys(f)
   ELSE
      RETURN simplifyc(f)
   END
END simplify ;


(*
   specialToConst - returns TRUE if, f, was changed to a const.
*)

PROCEDURE specialToConst (f: Fract) : BOOLEAN ;
BEGIN
   IF isSpecialConst(f)
   THEN
      WITH f^ DO
         op := oFract ;
         special := NONE
      END ;
      RETURN TRUE
   END ;
   RETURN FALSE
END specialToConst ;


(*
   walkFract - walks fract, f, and marks each node.
*)

PROCEDURE walkFract (f: Fract) ;
BEGIN
   mark(f) ;
   WITH f^ DO
      CASE special OF

      NONE,
      PI,
      E,
      ROOT2,
      ROOT3,
      ROOT6: |
      EXPR : CASE op OF

             oFract:  |
             oAdd,
             oSub,
             oMult,
             oDiv,
             oPower:  walkFract(left) ;
                      walkFract(right) |
             oNegate,
             oSin,
             oCos,
             oTan   : walkFract(left)

             ELSE
                HALT
             END
      ELSE
         HALT
      END
   END
END walkFract ;


(*
   walkExpr -
*)

PROCEDURE walkExpr (f: Fract; p: doProcedure) : BOOLEAN ;
VAR
   changed: BOOLEAN ;
BEGIN
   WITH f^ DO
      CASE special OF

      NONE,
      PI,
      E,
      ROOT2,
      ROOT3,
      ROOT6: changed := p(f) |
      EXPR : CASE op OF

             oFract:  changed := p(f) |
             oAdd,
             oSub,
             oMult,
             oDiv,
             oPower:  changed := walkExpr(left, p) ;
                      IF walkExpr(right, p) AND (NOT changed)
                      THEN
                         changed := TRUE
                      END |
             oNegate,
             oSin,
             oCos,
             oTan   : changed := walkExpr(left, p)

             ELSE
                HALT
             END
      ELSE
         HALT
      END
   END ;
   RETURN changed
END walkExpr ;


(*
   simplifys - simplify the expression until it cannot be simplified any further.
*)

PROCEDURE simplifys (f: Fract) : Fract ;
BEGIN
   WHILE doRules(f) DO
      (* pf(f) *)
   END ;
   RETURN f
END simplifys ;


(*
   doFract - returns TRUE if fract, f, was simplified.
*)

PROCEDURE doFract (f: Fract) : BOOLEAN ;
BEGIN
   IF f^.dirty
   THEN
      f := simplifyc(f) ;
      RETURN TRUE
   END ;
   RETURN FALSE
END doFract ;


(*
   doRules - returns TRUE if, f, is altered dues to a simplifcation rule being applied.
*)

PROCEDURE doRules (f: Fract) : BOOLEAN ;
BEGIN
   WITH f^ DO
      CASE special OF

      NONE : RETURN doFract(f) |
      PI,
      E,
      ROOT2,
      ROOT3,
      ROOT6: |
      EXPR : CASE op OF

             oFract :  RETURN doFract(f) |
             oAdd   :  RETURN doAdd(f, left, right) |
             oSub   :  RETURN doSub(f, left, right) |
             oMult  :  RETURN doMult(f, left, right) |
             oDiv   :  RETURN doDiv(f, left, right) |
             oNegate:  RETURN doNegate(f, left) |
             oPower :  RETURN doPower(f, left, right) |
             oSin   :  RETURN doSin(f, left) |
             oCos   :  RETURN doCos(f, left) |
             oTan   :  RETURN doTan(f, left) |

             ELSE
                HALT
             END
      ELSE
         HALT
      END
   END ;
   RETURN FALSE
END doRules ;


(*
   areEqual - return TRUE if l = r.
*)

PROCEDURE areEqual (l, r: Fract) : BOOLEAN ;
BEGIN
   IF l=r
   THEN
      RETURN TRUE
   ELSIF (NOT isSpecial(l)) AND (NOT isSpecial(r))
   THEN
      RETURN isEqual(l, r)
   ELSIF isSpecialConst(l) AND isSpecialConst(r)
   THEN
      RETURN l^.special=r^.special
   ELSIF isSpecialConst(l) OR isSpecialConst(r)
   THEN
      RETURN FALSE
   ELSIF isExpr(l) AND isExpr(r)
   THEN
      IF l^.op=r^.op
      THEN
         CASE l^.op OF

         oAdd,
         oMult  :  RETURN (areEqual(l^.left, r^.left) AND areEqual(l^.right, r^.right)) OR
                          (areEqual(l^.left, r^.right) AND areEqual(l^.right, r^.left)) |
         oSub,
         oDiv,
         oPower :  RETURN areEqual(l^.left, r^.left) AND areEqual(l^.right, r^.right) |
         oSin,
         oCos,
         oTan,
         oNegate:  RETURN areEqual(l^.left, r^.left)

         ELSE
            HALT
         END
      END
   END ;
   RETURN FALSE
END areEqual ;


(*
   assignValue - performs des^ := expr^ of the values (avoiding any housekeeping fields).
*)

PROCEDURE assignValue (des, expr: Fract) ;
BEGIN
   des^.positive := expr^.positive ;
   des^.whole := expr^.whole ;
   des^.num := expr^.num ;  (* was whole *)
   des^.demon := expr^.demon ;
   des^.op := expr^.op ;
   des^.dirty := expr^.dirty ;
   des^.special := expr^.special ;
   des^.left := expr^.left ;
   des^.right := expr^.right ;
END assignValue ;


(*
   doSub - if, l, and, r, are equal then alter, f, to zero.
*)

PROCEDURE doSub (f: Fract; l, r: Fract) : BOOLEAN ;
VAR
   modified: BOOLEAN ;
BEGIN
   modified := doRules(l) ;
   IF doRules(r)
   THEN
      modified := TRUE
   END ;

   IF areEqual(r, zero())
   THEN
      assignValue(f, l) ;
      RETURN TRUE
   END ;
   IF areEqual(l, zero())
   THEN
      assignValue(f, negate(r)) ;
      RETURN TRUE
   END ;

   IF areEqual(l, r)
   THEN
      assignValue(f, zero()) ;
      RETURN TRUE
   END ;
   IF isConst(l) AND isConst(r)
   THEN
      assignValue(f, sub(l, r)) ;
      RETURN TRUE
   END ;
   RETURN modified
END doSub ;


(*
   doAdd - simplify the addition of two fractions.
*)

PROCEDURE doAdd (f: Fract; l, r: Fract) : BOOLEAN ;
VAR
   modified: BOOLEAN ;
BEGIN
   modified := doRules(l) ;
   IF doRules(r)
   THEN
      modified := TRUE
   END ;

   IF areEqual(l, zero())
   THEN
      assignValue(f, r) ;
      RETURN TRUE
   END ;
   IF areEqual(r, zero())
   THEN
      assignValue(f, l) ;
      RETURN TRUE
   END ;

   IF areEqual(l, r)
   THEN
      f^.op := oMult ;
      assignValue(l, cardinal(2)) ;
      RETURN TRUE
   END ;
   IF isConst(l) AND isConst(r)
   THEN
      assignValue(f, add(l, r)) ;
      RETURN TRUE
   END ;
   RETURN modified
END doAdd ;


(*
   doMult - simplify the multiplication. of two fractions.
*)

PROCEDURE doMult (f: Fract; l, r: Fract) : BOOLEAN ;
VAR
   modified: BOOLEAN ;
BEGIN
   modified := doRules(l) ;
   IF doRules(r)
   THEN
      modified := TRUE
   END ;

   IF areEqual(r, zero())
   THEN
      assignValue(f, zero()) ;
      RETURN TRUE
   END ;
   IF areEqual(l, zero())
   THEN
      assignValue(f, zero()) ;
      RETURN TRUE
   END ;

   IF areEqual(l, r)
   THEN
      IF isSpecialConst(l) AND (l^.special=ROOT2)
      THEN
         assignValue(f, cardinal(2)) ;
         modified := TRUE
      ELSIF isSpecialConst(l) AND (l^.special=ROOT3)
      THEN
         assignValue(f, cardinal(3)) ;
         modified := TRUE
      ELSIF isSpecialConst(l) AND (l^.special=ROOT6)
      THEN
         assignValue(f, cardinal(6)) ;
         modified := TRUE
      ELSE
         f^.op := oPower ;
         f^.right := cardinal(2) ;
         modified := TRUE
      END
   ELSIF isConst(l) AND isConst(r)
   THEN
      assignValue(f, mult(l, r)) ;
      RETURN TRUE
   END ;
   RETURN modified
END doMult ;


(*
   doPower - simplify the expression l^r.
*)

PROCEDURE doPower (f: Fract; l, r: Fract) : BOOLEAN ;
VAR
   modified: BOOLEAN ;
BEGIN
   modified := doRules(l) ;
   IF doRules(r)
   THEN
      modified := TRUE
   END ;

   IF areEqual(l, one())
   THEN
      assignValue(f, cardinal(1)) ;
      RETURN TRUE
   ELSIF isSpecialConst(l) AND isEqual(r, two()) AND (l^.special=ROOT2)
   THEN
      assignValue(f, cardinal(2)) ;
      RETURN TRUE
   ELSIF isSpecialConst(l) AND isEqual(r, two()) AND (l^.special=ROOT3)
   THEN
      assignValue(f, cardinal(3)) ;
      RETURN TRUE
   ELSIF isSpecialConst(l) AND isEqual(r, two()) AND (l^.special=ROOT6)
   THEN
      assignValue(f, cardinal(6)) ;
      RETURN TRUE
   ELSIF isEqual(r, two()) AND isExpr(l) AND (l^.op=oDiv)
   THEN
      (* fractions multiplied *)
      assignValue(f, div(mult(l^.left, l^.left), mult(l^.right, l^.right))) ;
      RETURN TRUE
   END ;
   RETURN modified
END doPower ;


(*
   doNegate - simplify negate.
*)

PROCEDURE doNegate (f: Fract; l: Fract) : BOOLEAN ;
VAR
   result  : Fract ;
   modified: BOOLEAN ;
BEGIN
   modified := doRules(l) ;
   IF l^.op=oNegate
   THEN
      f^.left := l^.left ;
      RETURN TRUE
   ELSIF isConst(l)
   THEN
      assignValue(f, negate(l)) ;
      RETURN TRUE
   END ;
   RETURN modified
END doNegate ;


(*
   doDiv - simplify divide.
*)

PROCEDURE doDiv (f: Fract; l, r: Fract) : BOOLEAN ;
VAR
   modified: BOOLEAN ;
BEGIN
   modified := doRules(l) ;
   IF doRules(r)
   THEN
      modified := TRUE
   END ;

   IF areEqual(l, r)
   THEN
      assignValue(f, cardinal(1)) ;
      RETURN TRUE
   END ;
   IF areEqual(r, cardinal(1))
   THEN
      assignValue(f, l) ;
      RETURN TRUE
   END ;
   IF isConst(l) AND isConst(r)
   THEN
      assignValue(f, div(l, r)) ;
      RETURN TRUE
   END ;
   RETURN modified
END doDiv ;


(*
   angleIs - if angle a = angle v
             then
                f := r
             fi
*)

PROCEDURE angleIs (a, v, f, r: Fract) : BOOLEAN ;
BEGIN
   IF areEqual(a, v)
   THEN
      assignValue(f, r) ;
      RETURN TRUE
   END ;
   RETURN FALSE
END angleIs ;


(*
   doSin - lookup the sin of angle, l, and if it is known replace, f, with the result.
*)

PROCEDURE doSin (f: Fract; l: Fract) : BOOLEAN ;
VAR
   modified: BOOLEAN ;
BEGIN
   modified := doRules(l) ;

   IF angleIs(l, cardinal(0), f, cardinal(0))
   THEN
      RETURN TRUE
   END ;
   IF angleIs(l, div(pi(), two()), f, one())
   THEN
      RETURN TRUE
   END ;
   IF angleIs(l, div(pi(), cardinal(3)), f, div(root3(), two()))
   THEN
      RETURN TRUE
   END ;
   IF angleIs(l, div(pi(), cardinal(4)), f, div(root2(), two()))
   THEN
      RETURN TRUE
   END ;
   IF angleIs(l, div(pi(), cardinal(6)), f, half())
   THEN
      RETURN TRUE
   END ;
   IF angleIs(l, div(pi(), cardinal(12)), f, div(sub(root6(), root2()), cardinal(4)))
   THEN
      RETURN TRUE
   END ;

   RETURN modified
END doSin ;


(*
   doCos - lookup the cos of angle, l, and if it is known replace, f, with the result.
*)

PROCEDURE doCos (f: Fract; l: Fract) : BOOLEAN ;
VAR
   modified: BOOLEAN ;
BEGIN
   modified := doRules(l) ;

   IF angleIs(l, cardinal(0), f, one())
   THEN
      RETURN TRUE
   END ;
   IF angleIs(l, div(pi(), two()), f, zero())
   THEN
      RETURN TRUE
   END ;
   IF angleIs(l, div(pi(), cardinal(3)), f, half())
   THEN
      RETURN TRUE
   END ;
   IF angleIs(l, div(pi(), cardinal(4)), f, div(root2(), two()))
   THEN
      RETURN TRUE
   END ;
   IF angleIs(l, div(pi(), cardinal(6)), f, div(root3(), two()))
   THEN
      RETURN TRUE
   END ;

   RETURN modified
END doCos ;


(*
   doTan - lookup the tan of angle, l, and if it is known replace, f, with the result.
*)

PROCEDURE doTan (f: Fract; l: Fract) : BOOLEAN ;
VAR
   modified: BOOLEAN ;
BEGIN
   modified := doRules(l) ;

   IF angleIs(l, cardinal(0), f, zero())
   THEN
      RETURN TRUE
   END ;
   IF angleIs(l, div(pi(), cardinal(3)), f, root3())
   THEN
      RETURN TRUE
   END ;
   IF angleIs(l, div(pi(), cardinal(4)), f, one())
   THEN
      RETURN TRUE
   END ;
   IF angleIs(l, div(pi(), cardinal(6)), f, div(root3(), cardinal(3)))
   THEN
      RETURN TRUE
   END ;
   IF angleIs(l, div(pi(), cardinal(12)), f, sub(two(), root3()))
   THEN
      RETURN TRUE
   END ;
   IF angleIs(l, div(mult(pi(), cardinal(5)), cardinal(12)), f, add(two(), root3()))
   THEN
      RETURN TRUE
   END ;
   IF angleIs(l, mult(div(pi(), cardinal(12)), cardinal(5)), f, add(two(), root3()))
   THEN
      RETURN TRUE
   END ;

   RETURN modified
END doTan ;


(*
   gcd - return the greatest demoninator of, x, and, y.
*)

PROCEDURE gcd (x, y: LONGCARD) : LONGCARD ;
BEGIN
   WHILE x#y DO
      IF x>y
      THEN
         DEC(x, y)
      ELSE
         DEC(y, x)
      END
   END ;
   RETURN x
END gcd ;


(*
   newFract - return a new fraction.
*)

PROCEDURE newFract () : Fract ;
VAR
   f: Fract ;
   e: entity ;
BEGIN
   allocate(fractHeap, e, f) ;
   f^.fentity := e ;
   RETURN f
END newFract ;


(*
   initFract - initialise a fraction, which is expressed as:  w + n/d.
*)

PROCEDURE initFract (w: LONGCARD; n, d: LONGCARD) : Fract ;
VAR
   f: Fract ;
BEGIN
   f := newFract() ;
   WITH f^ DO
      positive := TRUE ;
      whole := w ;
      num := n ;
      demon := d ;
      op := oFract ;
      left := NIL ;
      right := NIL ;
      dirty := TRUE ;
      special := NONE
   END ;
   RETURN f
END initFract ;


(*
   root - grafts fract into the roots of the garbage tree.
*)

PROCEDURE root (f: Fract) : Fract ;
BEGIN
   rootEntity(fractHeap, f^.fentity, f) ;
   RETURN f
END root ;


(*
   unroot - removes, f, from the roots of the garbage tree.
*)

PROCEDURE unroot (f: Fract) : Fract ;
BEGIN
   rootDeallocate(fractHeap, f^.fentity, f) ;
   RETURN( NIL )
END unroot ;


(*
   makeSpecial - return a special fraction containing the value, special.
*)

PROCEDURE makeSpecial (f: Fract; s: Special) : Fract ;
BEGIN
   f^.special := s ;
   RETURN f
END makeSpecial ;


(*
   pf - short cut to print out a Fract, useful for interactive debugging via gdb.
*)

PROCEDURE pf (f: Fract) ;
BEGIN
   writeFract(f) ; writeLn
END pf ;


(*
   writeMath - write out the string, o, and the fraction, l.
*)

PROCEDURE writeMath (o: ARRAY OF CHAR; l: Fract) ;
BEGIN
   writeString(o) ;
   writeString('(') ;
   writeOp(l) ;
   writeString(')')
END writeMath ;


(*
   writeUnary - write the unary operator and fraction, l, as:  (o l)
*)

PROCEDURE writeUnary (o: ARRAY OF CHAR; l: Fract) ;
BEGIN
   writeString('(') ;
   writeString(o) ;
   writeOp(l) ;
   writeString(')')
END writeUnary ;


(*
   writeBinary - write out:  (l o r)
*)

PROCEDURE writeBinary (o: ARRAY OF CHAR; l, r: Fract) ;
BEGIN
   writeString('(') ;
   writeOp(l) ;
   writeString(o) ;
   writeOp(r) ;
   writeString(')')
END writeBinary ;


(*
   writeOp - write operator, f.
*)

PROCEDURE writeOp (f: Fract) ;
BEGIN
   WITH f^ DO
      CASE op OF

      oFract :  writeFract(f) |
      oAdd   :  writeBinary('+', left, right) |
      oSub   :  writeBinary('-', left, right) |
      oMult  :  writeBinary('*', left, right) |
      oDiv   :  writeBinary('/', left, right) |
      oNegate:  writeUnary('-', left) |
      oPower :  writeBinary('^', left, right) |
      oSin   :  writeMath('sin', left) |
      oCos   :  writeMath('cos', left) |
      oTan   :  writeMath('tan', left)

      ELSE
         HALT
      END
   END
END writeOp ;


(*
   writeFracts - write the special in, f.
*)

PROCEDURE writeFracts (f: Fract) ;
BEGIN
   WITH f^ DO
      CASE special OF

      NONE :  writeFract(f) |
      PI   :  writeString('pi') |
      E    :  writeString('e') |
      ROOT2:  writeString('root2') |
      ROOT3:  writeString('root3') |
      ROOT6:  writeString('root6') |
      EXPR :  writeOp(f)

      ELSE
         HALT
      END
   END
END writeFracts ;


(*
   writeFractc - write out the constant, f.
*)

PROCEDURE writeFractc (f: Fract) ;
BEGIN
   WITH f^ DO
      IF NOT positive
      THEN
         writeString('-')
      END ;
      IF whole#0
      THEN
         writeLongcard(whole)
      END ;
      IF (demon#1) AND (num#0)
      THEN
         writeString('.') ;
         writeLongcard(num) ;
         writeString('/') ;
         writeLongcard(demon)
      ELSIF whole=0
      THEN
         writeString('0') ;
      END
   END
END writeFractc ;


(*
   writeFract - displays fraction, f.
*)

PROCEDURE writeFract (f: Fract) ;
BEGIN
   IF isSpecial(f)
   THEN
      writeFracts(f)
   ELSE
      writeFractc(f)
   END
END writeFract ;


(*
   pd - writes out the Fract, f, as a decimal.
*)

PROCEDURE pd (f: Fract) ;
BEGIN
   writeDecimal(f) ; writeLn
END pd ;


(*
   log10 - return the log10 of, l.
*)

PROCEDURE log10 (l: LONGCARD) : CARDINAL ;
VAR
   c: LONGCARD ;
   i: CARDINAL ;
BEGIN
   i := 0 ;
   c := 1 ;
   WHILE c<l DO
      INC(i) ;
      c := c*10
   END ;
   RETURN i
END log10 ;


(*
   writeDecimal - write out, f, as a decimal.
*)

PROCEDURE writeDecimal (f: Fract) ;
VAR
   d: CARDINAL ;
   l: LONGREAL ;
   s: String ;
   a: ADDRESS ;
   i: INTEGER ;
BEGIN
   IF isZero(f)
   THEN
      writeString('0.0')
   ELSE
      WITH f^ DO
         d := log10(whole) ;
         l := VAL(LONGREAL, whole) + VAL(LONGREAL, num)/VAL(LONGREAL, demon) ;
         IF NOT positive
         THEN
            writeString('-')
         END ;
         s := LongrealToString(l, 20, 20-d) ;
         a := string(s) ;
         i := write(1, a, strlen(a)) ;
         s := KillString(s)
      END
   END
END writeDecimal ;


(*
   flush -
*)

PROCEDURE flush (f: Fract) : Fract ;
BEGIN
   IF isConst(f)
   THEN
      RETURN f
   ELSE
      f := simplifys(f) ;
      IF isConst(f)
      THEN
         RETURN f
      ELSE
         HALT
      END
   END
END flush ;


(*
   mark - marks Fract, f, to be saved from garbage collection.
*)

PROCEDURE mark (f: Fract) ;
BEGIN
   markEntity(f^.fentity)
END mark ;


(*
   dup - returns a duplicate of Fract, f.
*)

PROCEDURE dup (f: Fract) : Fract ;
BEGIN
   f := simplify(f) ;
   IF isConst(f) OR isSpecialConst(f)
   THEN
      RETURN dupc(f)
   ELSE
      RETURN dups(f)
   END
END dup ;


(*
   dupc -
*)

PROCEDURE dupc (f: Fract) : Fract ;
VAR
   d: Fract ;
BEGIN
   WITH f^ DO
      d := initFract(whole, num, demon) ;
      IF NOT positive
      THEN
         d := negate(d)
      END ;
      d^.dirty := dirty ;
      d^.special := special ;
      d^.op := op
   END ;
   RETURN d
END dupc ;


(*
   dups -
*)

PROCEDURE dups (f: Fract) : Fract ;
BEGIN
   WITH f^ DO
      CASE special OF

      NONE,
      PI,
      E,
      ROOT2,
      ROOT3,
      ROOT6: RETURN dupc(f) |
      EXPR : RETURN dupExpr(f)

      ELSE
         HALT
      END
   END
END dups ;


(*
   dupExpr - duplicate an entire expression.
*)

PROCEDURE dupExpr (f: Fract) : Fract ;
VAR
   g: Fract ;
BEGIN
   g := newFract() ;
   assignValue(g, f) ;
   g^.left := NIL ;
   g^.right := NIL ;

   WITH f^ DO
      CASE op OF

      oFract:  RETURN g |
      oAdd,
      oSub,
      oMult,
      oDiv,
      oPower:  g^.left := dup(left) ;
               g^.right := dup(right) |
      oNegate,
      oSin,
      oCos,
      oTan   : g^.left := dup(left)

      ELSE
         HALT
      END
   END ;
   RETURN g
END dupExpr ;


(*
   sinc -
*)

PROCEDURE sinc (x: Fract) : Fract ;
BEGIN
   HALT ;   (* this needs a lookup table --fixme-- *)
   RETURN x
END sinc ;


(*
   sin - return sin of angle, f.
*)

PROCEDURE sin (f: Fract) : Fract ;
BEGIN
   IF isSpecial(f)
   THEN
      RETURN buildUnary(oSin, f)
   ELSE
      RETURN sinc(f)
   END
END sin ;


(*
   tanc -
*)

PROCEDURE tanc (f: Fract) : Fract ;
BEGIN
   HALT ;   (* this needs a lookup table --fixme-- *)
   RETURN f
END tanc ;


(*
   tan - return tan of angle, f.
*)

PROCEDURE tan (f: Fract) : Fract ;
BEGIN
   IF isSpecial(f)
   THEN
      RETURN buildUnary(oTan, f)
   ELSE
      RETURN tanc(f)
   END
END tan ;


(*
   cos - return cos of angle, f.
*)

PROCEDURE cos (f: Fract) : Fract ;
BEGIN
   IF isSpecial(f)
   THEN
      RETURN buildUnary(oCos, f)
   ELSE
      RETURN cosc(f)
   END
END cos ;


(*
   cosc - return cos of angle, f.
*)

PROCEDURE cosc (f: Fract) : Fract ;
BEGIN
   HALT ;   (* this needs a lookup table --fixme-- *)
   RETURN f
END cosc ;


(*
   toConst - returns the same fraction, f, which has been converted into a constant.
*)

PROCEDURE toConst (f: Fract) : Fract ;
BEGIN
   f := simplify(f) ;
   IF walkExpr(f, specialToConst)
   THEN
      f := simplify(f)
   END ;

   IF isConst(f)
   THEN
      RETURN f
   ELSE
      HALT  (* something went wrong - the expression should be resolved *)
   END
END toConst ;


(*
   isNegative - returns TRUE if the value is negative.
*)

PROCEDURE isNegative (f: Fract) : BOOLEAN ;
BEGIN
   RETURN NOT isPositive(f)
END isNegative ;


(*
   isPositive - returns TRUE if, f, is positive.
*)

PROCEDURE isPositive (f: Fract) : BOOLEAN ;
BEGIN
   IF isConst(f)
   THEN
      RETURN f^.positive
   ELSIF isSpecialConst(f)
   THEN
      RETURN TRUE
   ELSIF isExpr(f)
   THEN
      RETURN isPositive(toConst(f))
   END
END isPositive ;


(*
   getReal - returns a REAL value of, f.
*)

PROCEDURE getReal (f: Fract) : REAL ;
VAR
   r: REAL ;
BEGIN
   f := toConst(f) ;
   IF isZero(f)
   THEN
      RETURN 0.0
   ELSE
      WITH f^ DO
         r := VAL(REAL, whole) ;
         IF (num#0) AND (demon#0)
         THEN
            r := r + VAL(REAL, num)/VAL(REAL, demon)
         END ;
         IF positive
         THEN
            RETURN r
         ELSE
            RETURN -r
         END
      END
   END
END getReal ;


(*
   getLongReal - returns a LONGREAL value of, f.
*)

PROCEDURE getLongReal (f: Fract) : LONGREAL ;
VAR
   r: LONGREAL ;
BEGIN
   f := toConst(f) ;
   IF isZero(f)
   THEN
      RETURN 0.0
   ELSE
      WITH f^ DO
         r := VAL(LONGREAL, whole) ;
         IF (num#0) AND (demon#0)
         THEN
            r := r + VAL(LONGREAL, num)/VAL(LONGREAL, demon)
         END ;
         IF positive
         THEN
            RETURN r
         ELSE
            RETURN -r
         END
      END
   END
END getLongReal ;


(*
   getFract - returns the, whole, numerator and demonimator value of, f.
*)

PROCEDURE getFract (f: Fract; VAR w, n, d: LONGCARD) ;
BEGIN
   f := toConst(f) ;
   WITH f^ DO
      w := whole ;
      n := num ;
      d := demon
   END
END getFract ;


(*
   putReal - returns a fraction in the range whole number + x/10000
*)

PROCEDURE putReal (r: REAL) : Fract ;
VAR
   w, n: CARDINAL ;
BEGIN
   IF r>=0.0
   THEN
      w := TRUNC(r) ;
      n := TRUNC((r-VAL(REAL, w))*10000.0) ;
      RETURN initFract(w, n, 10000)
   ELSE
      r := -r ;
      w := TRUNC(r) ;
      n := TRUNC((r-VAL(REAL, w))*10000.0) ;
      RETURN negate(initFract(w, n, 10000))
   END
END putReal ;


(*
   walkFractEntity -
*)

PROCEDURE walkFractEntity (e: entity) ;
VAR
   f: Fract ;
BEGIN
   f := getData(e) ;
   walkFract(f)
END walkFractEntity ;


(*
   init - initialise the global data structures.
*)

PROCEDURE init ;
VAR
   f: Fract ;
BEGIN
   fractHeap := initGarbage(walkFractEntity, TSIZE(f^), InitString('fractions'))
END init ;


(*
   regressionTest - perform some simple sanity regression tests.
*)

PROCEDURE regressionTest ;
BEGIN
   Assert(isEqual(sub(half(), initFract(1, 1, 2)), negate(one()))) ;
   Assert(isEqual(sub(initFract(1, 1, 2), half()), one())) ;
   Assert(isEqual(sub(initFract(1, 1, 2), negate(half())), two())) ;
   Assert(isEqual(sub(negate(two()), negate(half())), negate(initFract(1, 1, 2)))) ;
   Assert(isEqual(add(negate(one()), negate(half())), negate(initFract(1, 1, 2)))) ;
   Assert(isEqual(add(negate(half()), negate(half())), integer(-1))) ;
   Assert(isEqual(add(initFract(0, 1, 4), initFract(0, 1, 5)), initFract(0, 9, 20))) ;
   Assert(isEqual(add(initFract(0, 9, 4), initFract(0, 1, 5)), initFract(2, 9, 20))) ;
   Assert(isEqual(reciprocal(initFract(0, 1, 9)), cardinal(9))) ;
   Assert(isEqual(reciprocal(initFract(0, 3, 10)), initFract(0, 10, 3))) ;
   Assert(isEqual(reciprocal(one()), one())) ;
   Assert(isEqual(mult(reciprocal(cardinal(2)), reciprocal(cardinal(3))), initFract(0, 1, 6))) ;
   Assert(isEqual(inc(reciprocal(cardinal(50)), reciprocal(cardinal(100))), initFract(0, 3, 100))) ;
   Assert(isEqual(mult(initFract(0, 22, 7), initFract(0, 22, 7)), initFract(9, 43, 49))) ;
   Assert(isEqual(dec(initFract(0, 1, 4), initFract(0, 1, 2)), negate(initFract(0, 1, 4)))) ;
   Assert(isEqual(dec(initFract(0, 1, 2), initFract(0, 1, 4)), initFract(0, 1, 4))) ;
   Assert(isEqual(dec(initFract(3, 0, 0), initFract(3, 1, 4)), negate(initFract(0, 1, 4)))) ;
   Assert(isEqual(mult(integer(-1), one()), integer(-1))) ;
   Assert(isEqual(integer(-1), mult(integer(-1), one()))) ;
   Assert(isEqual(mult(integer(-2), one()), integer(-2))) ;
   Assert(isEqual(integer(-2), mult(integer(-2), one()))) ;
   Assert(isEqual(integer(2), mult(integer(-2), integer(-1)))) ;
   Assert(isEqual(mult(integer(-2), integer(-1)), integer(2))) ;
   Assert(isEqual(mult(integer(-2), integer(1)), integer(-2))) ;
   Assert(isEqual(mult(integer(2), integer(-1)), integer(-2))) ;
   Assert(isEqual(add(integer(-1), integer(-1)), integer(-2))) ;
   Assert(isEqual(integer(-2), add(integer(-1), integer(-1)))) ;
   Assert(isEqual(add(integer(-1), integer(1)), integer(0))) ;
   Assert(isEqual(add(integer(1), integer(-1)), integer(0))) ;
   Assert(isEqual(sub(integer(-1), integer(-1)), integer(0))) ;
   Assert(isEqual(integer(0), sub(integer(-1), integer(-1)))) ;
   Assert(isEqual(sub(integer(-1), integer(1)), integer(-2))) ;
   Assert(isEqual(sub(integer(1), integer(-1)), integer(2))) ;
   writeFract(pi()) ; writeLn ;
   pf(simplify(sin(pi()))) ; writeLn ;
   pf(simplify(sin(div(pi(), cardinal(6))))) ; writeLn ;
   pf(simplify(sin(div(pi(), cardinal(4))))) ; writeLn ;
   pf(simplify(mult(sin(div(pi(), cardinal(4))), sin(div(pi(), cardinal(4)))))) ; writeLn ;
   pf(simplify(tan(mult(cardinal(5), div(pi(), cardinal(12)))))) ; writeLn ;
   pf(simplify(sin(div(pi(), cardinal(12))))) ; writeLn ;
   pf(simplify(power(sub(root6(), root2()), two()))) ; writeLn ;
   pf(simplify(mult(sin(div(pi(), cardinal(12))), sin(div(pi(), cardinal(12)))))) ; writeLn ;
   pf(simplify(div(mult(sin(div(pi(), cardinal(12))), sin(div(pi(), cardinal(12)))),
                   mult(sin(div(pi(), cardinal(12))), sin(div(pi(), cardinal(12))))))) ; writeLn
END regressionTest ;


BEGIN
   init ;
   IF runRegression
   THEN
      regressionTest
   END
END Fractions.
