/*
 *  swig interface file defining how Python can grab
 *  a copy of the event buffer.
 */

%module pgeif

%cstring_output_allocate_size(char **start, int *used);

%{
extern "C" void pgeif_gete (char **start, int *used);
%}

extern "C" void pgeif_gete (char **start, int *used);
