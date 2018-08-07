
#include "video_mode.h"

VALUE rb_cGLFWvidmode;

void Init_glfw_vidmode(VALUE module) {
    rb_cGLFWvidmode = rb_define_class_under(module, "VideoMode", rb_cObject);
}