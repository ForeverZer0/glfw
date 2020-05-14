#ifndef RB_GLFW_H
#define RB_GLFW_H 1

#include "ruby.h"
#include "GLFW/glfw3.h"

#define GLFW_IMAGE_LOADER 1

extern VALUE mGLFW;
extern VALUE eGLFWError;
extern VALUE cWindow;
extern VALUE cMonitor;
extern VALUE cImage;
extern VALUE cCursor;
extern VALUE cVideoMode;
extern VALUE mJoystick;
extern VALUE cGamepadState;
extern VALUE cPoint;
extern VALUE cSize;
extern VALUE cVec2;

#define RB_BOOL(exp) ((exp) ? Qtrue : Qfalse)
#define NUM2FLT(v) ((float) NUM2DBL(v))
#define STR2SYM(str) (ID2SYM(rb_intern(str)))

void rb_glfw_window_init(void);
void rb_glfw_monitor_init(void);
void rb_glfw_image_init(void);
void rb_glfw_cursor_init(void);
void rb_glfw_common_init(void);
void rb_glfw_joystick_init(void);

typedef struct {
    int x;
    int y;
} RBivec2;

typedef struct {
    double x;
    double y;
} RBvec2;

VALUE rb_glfw_ivec2_create(VALUE klass, int x, int y);
VALUE rb_glfw_vec2_create(VALUE klass, double x, double y);

#endif /* RB_GLFW_H */
