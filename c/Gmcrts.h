#if !defined(MCRTS_H)
#  define MCRTS_H

#ifdef __cplusplus
extern "C" {
#endif

void CaseException (const char *s, unsigned int high, unsigned int lineno);
void ReturnException (const char *s, unsigned int high, unsigned int lineno);
/* void throw (int n); */

#ifdef __cplusplus
}
#endif


#endif
