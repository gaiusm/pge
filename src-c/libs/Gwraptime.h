/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/wraptime.def.  */


#if !defined (_wraptime_H)
#   define _wraptime_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSYSTEM.h"

#   if defined (_wraptime_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef void *wraptime_timeval;

typedef void *wraptime_timezone;

typedef void *wraptime_tm;


/*
   InitTimeval - returns a newly created opaque type.
*/

EXTERN wraptime_timeval wraptime_InitTimeval (void);

/*
   KillTimeval - deallocates the memory associated with an
                 opaque type.
*/

EXTERN wraptime_timeval wraptime_KillTimeval (wraptime_timeval tv);

/*
   InitTimezone - returns a newly created opaque type.
*/

EXTERN wraptime_timezone wraptime_InitTimezone (void);

/*
   KillTimezone - deallocates the memory associated with an
                  opaque type.
*/

EXTERN wraptime_timezone wraptime_KillTimezone (wraptime_timezone tv);

/*
   InitTM - returns a newly created opaque type.
*/

EXTERN wraptime_tm wraptime_InitTM (void);

/*
   KillTM - deallocates the memory associated with an
            opaque type.
*/

EXTERN wraptime_tm wraptime_KillTM (wraptime_tm tv);

/*
   gettimeofday - calls gettimeofday(2) with the same parameters, tv,
                  and, tz.  It returns 0 on success.
*/

EXTERN int wraptime_gettimeofday (wraptime_timeval tv, wraptime_timezone tz);

/*
   settimeofday - calls settimeofday(2) with the same parameters, tv,
                  and, tz.  It returns 0 on success.
*/

EXTERN int wraptime_settimeofday (wraptime_timeval tv, wraptime_timezone tz);

/*
   GetFractions - returns the tv_usec field inside the timeval structure
                  as a CARDINAL.
*/

EXTERN unsigned int wraptime_GetFractions (wraptime_timeval tv);

/*
   localtime_r - returns the tm parameter, m, after it has been assigned with
                 appropriate contents determined by, tv.  Notice that
                 this procedure function expects, timeval, as its first
                 parameter and not a time_t (as expected by the posix
                 equivalent).  This avoids having to expose a time_t
                 system dependant definition.
*/

EXTERN wraptime_tm wraptime_localtime_r (wraptime_timeval tv, wraptime_tm m);

/*
   GetYear - returns the year from the structure, m.
*/

EXTERN unsigned int wraptime_GetYear (wraptime_tm m);

/*
   GetMonth - returns the month from the structure, m.
*/

EXTERN unsigned int wraptime_GetMonth (wraptime_tm m);

/*
   GetDay - returns the day of the month from the structure, m.
*/

EXTERN unsigned int wraptime_GetDay (wraptime_tm m);

/*
   GetHour - returns the hour of the day from the structure, m.
*/

EXTERN unsigned int wraptime_GetHour (wraptime_tm m);

/*
   GetMinute - returns the minute within the hour from the structure, m.
*/

EXTERN unsigned int wraptime_GetMinute (wraptime_tm m);

/*
   GetSecond - returns the seconds in the minute from the structure, m.
               The return value will always be in the range 0..59.
               A leap minute of value 60 will be truncated to 59.
*/

EXTERN unsigned int wraptime_GetSecond (wraptime_tm m);

/*
   GetSummerTime - returns a boolean indicating whether summer time is
                   set.
*/

EXTERN unsigned int wraptime_GetSummerTime (wraptime_timezone tz);

/*
   GetDST - returns the number of minutes west of GMT.
*/

EXTERN int wraptime_GetDST (wraptime_timezone tz);

/*
   SetTimeval - sets the fields in timeval, tv, with:
                second, minute, hour, day, month, year, fractions.
*/

EXTERN void wraptime_SetTimeval (wraptime_timeval tv, unsigned int second, unsigned int minute, unsigned int hour, unsigned int day, unsigned int month, unsigned int year, unsigned int yday, unsigned int wday, unsigned int isdst);

/*
   SetTimezone - set the timezone field inside timeval, tv.
*/

EXTERN void wraptime_SetTimezone (wraptime_timeval tv, unsigned int zone, int minuteswest);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
