/* automatically created by mc from ../git-pge/m2/rpc.def.  */


#if !defined (_rpc_H)
#   define _rpc_H

#   ifdef __cplusplus
extern "C" {
#   endif
#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   include "GSeqFile.h"

#   if defined (_rpc_C)
#      define EXTERN
#   else
#      define EXTERN extern
#   endif

typedef struct rpc_cc_r rpc_cc;

typedef enum {rpc_ready, rpc_problem} rpc_rpcStatus;

struct rpc_cc_r {
                  unsigned int x;
                  unsigned int y;
                };


/*
   initcc - initialises a, cc, structure.
*/

EXTERN rpc_cc rpc_initcc (unsigned int x, unsigned int y);

/*
   colour - registers a colour with pygame and cid is assigned with the python colour, id.
*/

EXTERN rpc_rpcStatus rpc_colour (SeqFile_ChanId file, unsigned int r, unsigned int g, unsigned int b, unsigned int *cid);

/*
   polygon - writes a filled polygon to the pygame display.
             Polygon to be filled with colour, cid.
*/

EXTERN rpc_rpcStatus rpc_polygon (SeqFile_ChanId file, unsigned int cid, unsigned int n, rpc_cc *p_, unsigned int _p_high);

/*
   circle - writes a filled circle to the pygame display.
            Circle to be filled with colour, cid.
*/

EXTERN rpc_rpcStatus rpc_circle (SeqFile_ChanId file, unsigned int cid, rpc_cc center, unsigned int radius);

/*
   drawLine - draw a line on the pygame screen from p1 to p2 with thickness and colour, id.
*/

EXTERN rpc_rpcStatus rpc_drawLine (SeqFile_ChanId file, unsigned int cid, rpc_cc p1, rpc_cc p2, unsigned int thickness);

/*
   resolution - sets the resolution of Pygame.
*/

EXTERN rpc_rpcStatus rpc_resolution (SeqFile_ChanId file, rpc_cc res);

/*
   flipbuffer - flips the pygame frame buffer.
*/

EXTERN rpc_rpcStatus rpc_flipbuffer (SeqFile_ChanId file);
#   ifdef __cplusplus
}
#   endif

#   undef EXTERN
#endif
