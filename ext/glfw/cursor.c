
#include "cursor.h"

VALUE rb_cGLFWcursor;

void Init_glfw_cursor(VALUE module) {
    rb_cGLFWcursor = rb_define_class_under(module, "Cursor", rb_cObject);
    
}