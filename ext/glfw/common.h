

#ifndef GLFW_RB_COMMON_H
#define GLFW_RB_COMMON_H 1

#include "glfw3.h"
#include "ruby.h"

#define STR2SYM(str) ID2SYM(rb_intern(str))

#define INT2BOOL(i) (i ? Qtrue : Qfalse)

#define WINDOW()   \
    GLFWwindow *w; \
    Data_Get_Struct(self, GLFWwindow, w)

enum GLFW_RB_CALLBACK_TYPE {
    GLFW_RB_MOVED,
    GLFW_RB_RESIZED,
    GLFW_RB_FRAMEBUFFER_RESIZED,
    GLFW_RB_CLOSING,
    GLFW_RB_REFRESHED,
    GLFW_RB_FOCUS_CHANGED,
    GLFW_RB_MINIMIZE_CHANGED,
    GLFW_RB_MOUSE_MOVE,
    GLFW_RB_MOUSE_SCROLL,
    GLFW_RB_MOUSE_BUTTON,
    GLFW_RB_MOUSE_ENTER,
    GLFW_RB_KEY,
    GLFW_RB_CHAR,
    GLFW_RB_CHAR_MODS,
    GLFW_RB_FILE_DROP,
    GLFW_RB_MONITOR,
    GLFW_RB_JOYSTICK
} GLFW_RB_CALLBACK_TYPE;

extern VALUE rb_mGLFW;
extern VALUE rb_eGLFWError;
extern VALUE rb_cGLFWwindow;
extern VALUE rb_cGLFWmonitor;
extern VALUE rb_cGLFWvidmode;
extern VALUE rb_cGLFWimage;
extern VALUE rb_cGLFWcursor;

#endif /* GLFW_RB_COMMON_H */