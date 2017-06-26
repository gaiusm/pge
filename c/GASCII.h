/* automatically created by mc from /home/gaius/GM2/graft-5.2.0/gcc-5.2.0/gcc/gm2/gm2-libs/ASCII.def.  */


#if !defined (_ASCII_H)
#   define _ASCII_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif


#   if defined (_ASCII_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

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
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
