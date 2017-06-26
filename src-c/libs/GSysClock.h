/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs-iso/SysClock.def.  */


#if !defined (_SysClock_H)
#   define _SysClock_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_SysClock_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

#   define SysClock_maxSecondParts 1000000
typedef unsigned int SysClock_Month;

typedef struct SysClock_DateTime_r SysClock_DateTime;

typedef unsigned int SysClock_Sec;

typedef unsigned int SysClock_Fraction;

typedef unsigned int SysClock_Day;

typedef unsigned int SysClock_Hour;

typedef unsigned int SysClock_Min;

typedef unsigned int SysClock_UTCDiff;

struct SysClock_DateTime_r {
                             unsigned int year;
                             SysClock_Month month;
                             SysClock_Day day;
                             SysClock_Hour hour;
                             SysClock_Min minute;
                             SysClock_Sec second;
                             SysClock_Fraction fractions;
                             SysClock_UTCDiff zone;
                             unsigned int summerTimeFlag;
                           };

EXTERN unsigned int SysClock_CanGetClock (void);
EXTERN unsigned int SysClock_CanSetClock (void);
EXTERN unsigned int SysClock_IsValidDateTime (SysClock_DateTime userData);
EXTERN void SysClock_GetClock (SysClock_DateTime *userData);
EXTERN void SysClock_SetClock (SysClock_DateTime userData);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
