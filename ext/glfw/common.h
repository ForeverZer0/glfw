

#ifndef GLFW_RB_COMMON_H
#define GLFW_RB_COMMON_H 1

#include "glfw3.h"
#include "ruby.h"

#define STR2SYM(str) ID2SYM(rb_intern(str))

#define WINDOW()   \
    GLFWwindow *w; \
    Data_Get_Struct(self, GLFWwindow, w)

#define WRAP_WINDOW(w) Data_Wrap_Struct(rb_cGLFWwindow, NULL, RUBY_DEFAULT_FREE, w)

#define RETURN_WRAP_WINDOW(w)                \
    void *ptr = glfwGetWindowUserPointer(w); \
    return (ptr != NULL) ? (VALUE)ptr : Data_Wrap_Struct(rb_cGLFWwindow, NULL, RUBY_DEFAULT_FREE, w)


extern VALUE rb_mGLFW;
extern VALUE rb_eGLFWError;

extern VALUE rb_cGLFWwindow;
extern VALUE rb_cGLFWmonitor;
extern VALUE rb_cGLFWvidmode;
extern VALUE rb_cGLFWimage;

#endif /* GLFW_RB_COMMON_H */