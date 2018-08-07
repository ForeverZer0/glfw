#include "glfw.h"

VALUE rb_mGlfw;

void
Init_glfw(void)
{
  rb_mGlfw = rb_define_module("Glfw");
}
