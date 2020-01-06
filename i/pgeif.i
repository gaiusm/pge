/* this needs to be maintained */
%module pgeif

%include exception.i

%exception {
  try {
     $action
  } catch (int i) {
     return NULL;
  }
}

%include cstring.i
%cstring_output_allocate_size(char **s, int *slen, );

%{
#define SWIG_PYTHON_STRICT_BYTE_CHAR

extern "C" void get_cbuf (char **s, int *slen);
extern "C" void get_ebuf (char **s, int *slen);
extern "C" void get_fbuf (char **s, int *slen);

extern "C" void empty_cbuffer (void);
extern "C" void empty_fbuffer (void);

extern "C" void batch (void);
extern "C" void use_buffer (void);
extern "C" void use_time_delay (unsigned int on) ;
extern "C" void draw_collision (unsigned int actual, unsigned int predict);
extern "C" void set_collision_colour (unsigned int c);

extern "C" void dump_world (void);
extern "C" unsigned int check_objects (void);
extern "C" unsigned int rm (unsigned int id);
extern "C" double get_time (void);
extern "C" double time_until (void);
extern "C" unsigned int is_frame (void);
extern "C" unsigned int is_collision (void);
extern "C" unsigned int is_function (void);
extern "C" unsigned int is_spring (void);
extern "C" void create_function_event (double t, unsigned int id, unsigned int param);

extern "C" void process_event (void);
extern "C" unsigned int rotate (unsigned int id, double angle);
extern "C" unsigned int accel (unsigned int id, double ax, double ay);
extern "C" unsigned int velocity (unsigned int id, double vx, double vy);
extern "C" unsigned int spring (unsigned int id1, unsigned int id2, double k, double d, double l);
extern "C" unsigned int circle (double x0, double y0, double radius, unsigned int c);
extern "C" unsigned int fix (unsigned int id);
extern "C" unsigned int unfix (unsigned int id);
extern "C" unsigned int is_fixed (unsigned int id);
extern "C" unsigned int mass (unsigned int id, double m);
extern "C" double get_mass (unsigned int id);
extern "C" double get_gravity (unsigned int id);
extern "C" double set_gravity (unsigned int id, double g);

extern "C" unsigned int poly6 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, unsigned int c);
extern "C" unsigned int poly5 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, unsigned int c);
extern "C" unsigned int poly4 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, unsigned int c);
extern "C" unsigned int poly3 (double x0, double y0, double x1, double y1, double x2, double y2, unsigned int c);
extern "C" unsigned int box (double x0, double y0, double i, double j, unsigned int c);

extern "C" double get_xpos (unsigned int id);
extern "C" double get_ypos (unsigned int id);
extern "C" double get_xvel (unsigned int id);
extern "C" double get_yvel (unsigned int id);
extern "C" double get_xaccel (unsigned int id);
extern "C" double get_yaccel (unsigned int id);

extern "C" void apply_impulse (unsigned int id, double x, double y, double m);
extern "C" int moving_towards (unsigned int id, double x, double y);
extern "C" void put_xvel (unsigned int id, double d);
extern "C" void put_yvel (unsigned int id, double d);
extern "C" void put_xaccel (unsigned int id, double d);
extern "C" void put_yaccel (unsigned int id, double d);
extern "C" void set_colour (unsigned int id, unsigned int c);
extern "C" void draw_spring (unsigned int id, unsigned int c, double w);
extern "C" void end_spring (unsigned int id, unsigned int c);
extern "C" void mid_spring (unsigned int id, unsigned int c);
extern "C" void when_spring (unsigned int id, double length, unsigned int func);

extern "C" void gravity (double g);

extern "C" unsigned int purple (void);
extern "C" unsigned int blue (void);
extern "C" unsigned int green (void);
extern "C" unsigned int red (void);
extern "C" unsigned int black (void);
extern "C" unsigned int white (void);
extern "C" unsigned int rgb (double r, double g, double b);

extern "C" unsigned int l2h (unsigned int id);
extern "C" unsigned int h2l (unsigned int id);
extern "C" double skip_until (double t);
extern "C" void fps (double t);
%}

extern "C" void empty_cbuffer (void);
extern "C" void empty_fbuffer (void);

extern "C" void batch (void);
extern "C" void use_buffer (void);
extern "C" void use_time_delay (unsigned int on) ;
extern "C" void draw_collision (unsigned int actual, unsigned int predict);
extern "C" void set_collision_colour (unsigned int c);

extern "C" void dump_world (void);
extern "C" unsigned int check_objects (void);
extern "C" unsigned int rm (unsigned int id);
extern "C" double get_time (void);
extern "C" double time_until (void);
extern "C" unsigned int is_frame (void);
extern "C" unsigned int is_collision (void);
extern "C" unsigned int is_function (void);
extern "C" unsigned int is_spring (void);
extern "C" void create_function_event (double t, unsigned int id, unsigned int param);

extern "C" void process_event (void);
extern "C" unsigned int rotate (unsigned int id, double angle);
extern "C" unsigned int accel (unsigned int id, double ax, double ay);
extern "C" unsigned int velocity (unsigned int id, double vx, double vy);
extern "C" unsigned int spring (unsigned int id1, unsigned int id2, double k, double d, double l);
extern "C" unsigned int circle (double x0, double y0, double radius, unsigned int c);
extern "C" unsigned int fix (unsigned int id);
extern "C" unsigned int unfix (unsigned int id);
extern "C" unsigned int is_fixed (unsigned int id);
extern "C" unsigned int mass (unsigned int id, double m);
extern "C" double get_mass (unsigned int id);
extern "C" double get_gravity (unsigned int id);
extern "C" double set_gravity (unsigned int id, double g);

extern "C" unsigned int poly6 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, unsigned int c);
extern "C" unsigned int poly5 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, unsigned int c);
extern "C" unsigned int poly4 (double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3, unsigned int c);
extern "C" unsigned int poly3 (double x0, double y0, double x1, double y1, double x2, double y2, unsigned int c);
extern "C" unsigned int box (double x0, double y0, double i, double j, unsigned int c);

extern "C" double get_xpos (unsigned int id);
extern "C" double get_ypos (unsigned int id);
extern "C" double get_xvel (unsigned int id);
extern "C" double get_yvel (unsigned int id);
extern "C" double get_xaccel (unsigned int id);
extern "C" double get_yaccel (unsigned int id);

extern "C" void apply_impulse (unsigned int id, double x, double y, double m);
extern "C" int moving_towards (unsigned int id, double x, double y);
extern "C" void put_xvel (unsigned int id, double d);
extern "C" void put_yvel (unsigned int id, double d);
extern "C" void put_xaccel (unsigned int id, double d);
extern "C" void put_yaccel (unsigned int id, double d);

extern "C" void set_colour (unsigned int id, unsigned int c);
extern "C" void draw_spring (unsigned int id, unsigned int c, double w);
extern "C" void end_spring (unsigned int id, unsigned int c);
extern "C" void mid_spring (unsigned int id, unsigned int c);
extern "C" void when_spring (unsigned int id, double length, unsigned int func);

extern "C" void gravity (double g);
extern "C" unsigned int purple (void);
extern "C" unsigned int blue (void);
extern "C" unsigned int green (void);
extern "C" unsigned int red (void);
extern "C" unsigned int black (void);
extern "C" unsigned int white (void);
extern "C" unsigned int rgb (double r, double g, double b);

extern "C" unsigned int l2h (unsigned int id);
extern "C" unsigned int h2l (unsigned int id);

extern "C" double skip_until (double t);

extern "C" void get_cbuf (char **s, int *slen);
extern "C" void get_ebuf (char **s, int *slen);
extern "C" void get_fbuf (char **s, int *slen);
extern "C" void fps (double t);
