
#include "monitor.h"

VALUE rb_cGLFWmonitor;

void Init_glfw_monitor(VALUE module) {
    rb_cGLFWmonitor = rb_define_class_under(module, "Monitor", rb_cObject);

    rb_define_method(rb_cGLFWmonitor, "name", rb_glfw_monitor_name, 0);
    rb_define_method(rb_cGLFWmonitor, "position", rb_glfw_monitor_pos, 0);
    rb_define_method(rb_cGLFWmonitor, "size", rb_glfw_monitor_size, 0);
    rb_define_method(rb_cGLFWmonitor, "x", rb_glfw_monitor_x, 0);
    rb_define_method(rb_cGLFWmonitor, "y", rb_glfw_monitor_y, 0);
    rb_define_method(rb_cGLFWmonitor, "width", rb_glfw_monitor_width, 0);
    rb_define_method(rb_cGLFWmonitor, "height", rb_glfw_monitor_height, 0);
    rb_define_method(rb_cGLFWmonitor, "dimensions", rb_glfw_monitor_dimensions, 0);

    rb_define_method(rb_cGLFWmonitor, "gamma", rb_glfw_monitor_gamma, 1);
    rb_define_method(rb_cGLFWmonitor, "gamma_ramp", rb_glfw_monitor_get_gamma_ramp, 0);
    rb_define_method(rb_cGLFWmonitor, "set_gamma_ramp", rb_glfw_monitor_set_gamma_ramp, -1);

    rb_define_singleton_method(rb_cGLFWmonitor, "primary", rb_glfw_monitor_primary, 0);
    rb_define_const(rb_cGLFWmonitor, "NONE", rb_glfw_monitor_alloc(rb_cGLFWmonitor));
}

static VALUE rb_glfw_monitor_alloc(VALUE klass) {
    GLFWmonitor *monitor = ruby_xmalloc(SIZEOF_INTPTR_T);
    memset(monitor, 0, SIZEOF_INTPTR_T);
    return Data_Wrap_Struct(rb_cGLFWmonitor, NULL, RUBY_DEFAULT_FREE, monitor);
}

VALUE rb_glfw_monitor_name(VALUE self) {
    MONITOR();
    const char *name = glfwGetMonitorName(m);
    return rb_str_new_cstr(name);
}

VALUE rb_glfw_monitor_pos(VALUE self) {
    MONITOR();
    int x, y;
    glfwGetMonitorPos(m, &x, &y);
    VALUE ary = rb_ary_new_capa(2);
    rb_ary_store(ary, 0, INT2NUM(x));
    rb_ary_store(ary, 1, INT2NUM(y));
    return ary;
}

VALUE rb_glfw_monitor_size(VALUE self) {
    MONITOR();
    int width, height;
    glfwGetMonitorPhysicalSize(m, &width, &height);
    VALUE ary = rb_ary_new_capa(2);
    rb_ary_store(ary, 0, INT2NUM(width));
    rb_ary_store(ary, 1, INT2NUM(height));
    return ary;
}

VALUE rb_glfw_monitor_x(VALUE self) {
    MONITOR();
    int x;
    glfwGetMonitorPos(m, &x, NULL);
    return INT2NUM(x);
}

VALUE rb_glfw_monitor_y(VALUE self) {
    MONITOR();
    int y;
    glfwGetMonitorPos(m, NULL, &y);
    return INT2NUM(y);
}

VALUE rb_glfw_monitor_width(VALUE self) {
    MONITOR();
    int width;
    glfwGetMonitorPhysicalSize(m, &width, NULL);
    return INT2NUM(width);
}

VALUE rb_glfw_monitor_height(VALUE self) {
    MONITOR();
    int height;
    glfwGetMonitorPhysicalSize(m, NULL, &height);
    return INT2NUM(height);
}

VALUE rb_glfw_monitor_dimensions(VALUE self) {
    MONITOR();
    int x, y, width, height;
    glfwGetMonitorPos(m, &x, &y);
    glfwGetMonitorPhysicalSize(m, &width, &height);
    VALUE ary = rb_ary_new_capa(4);
    rb_ary_store(ary, 0, INT2NUM(x));
    rb_ary_store(ary, 1, INT2NUM(y));
    rb_ary_store(ary, 2, INT2NUM(width));
    rb_ary_store(ary, 3, INT2NUM(height));
    return ary;
}

VALUE rb_glfw_monitor_get_gamma_ramp(VALUE self) {
    MONITOR();
    const GLFWgammaramp *ramp = glfwGetGammaRamp(m);

    if (ramp == NULL)
        return Qnil;

    int count = ramp->size;
    VALUE hash = rb_hash_new();
    VALUE red = rb_ary_new_capa(count), green = rb_ary_new_capa(count), blue = rb_ary_new_capa(count);

    for (int i = 0; i < count; i++) {
        rb_ary_store(red, i, INT2NUM(ramp->red[i]));
        rb_ary_store(green, i, INT2NUM(ramp->green[i]));
        rb_ary_store(blue, i, INT2NUM(ramp->blue[i]));
    }

    rb_hash_aset(hash, ID2SYM(rb_intern("red")), red);
    rb_hash_aset(hash, ID2SYM(rb_intern("green")), green);
    rb_hash_aset(hash, ID2SYM(rb_intern("blue")), blue);

    return hash;
}

VALUE rb_glfw_monitor_set_gamma_ramp(int argc, VALUE *argv, VALUE self) {
    if (argc != 1 && argc != 3)
    {
        rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 1, 3)", argc);
        return Qnil;
    }

    MONITOR();
    VALUE red, green, blue;

    if (argc == 1)
    {
        Check_Type(argv[0], T_HASH);
        red = rb_hash_aref(argv[0], ID2SYM(rb_intern("red")));
        green = rb_hash_aref(argv[0], ID2SYM(rb_intern("green")));
        blue = rb_hash_aref(argv[0], ID2SYM(rb_intern("blue")));
    }
    else
    {
        red = argv[0];
        green = argv[1];
        blue = argv[2];
    }

    Check_Type(red, T_ARRAY);
    Check_Type(green, T_ARRAY);
    Check_Type(blue, T_ARRAY);

    int size = rb_array_len(red);
    if (rb_array_len(green) != size || rb_array_len(blue) != size)
    {
        rb_raise(rb_eRuntimeError, "red, green, and blue gamma ramps must all be of equal length");
        return Qnil;
    }

    GLFWgammaramp *ramp = malloc(sizeof(GLFWgammaramp));
    ramp->size = size;
    ramp->red = malloc(sizeof(u_short) * size);
    ramp->green = malloc(sizeof(u_short) * size);
    ramp->blue = malloc(sizeof(u_short) * size);

    for (int i = 0; i < size; i++)
    {
        ramp->red[i] = NUM2USHORT(rb_ary_entry(red, i));
        ramp->green[i] = NUM2USHORT(rb_ary_entry(green, i));
        ramp->blue[i] = NUM2USHORT(rb_ary_entry(blue, i));
    }

    glfwSetGammaRamp(m, ramp);

    free(ramp);
    return self;
}

VALUE rb_glfw_monitor_gamma(VALUE self, VALUE exponent) {
    MONITOR();
    float e = (float) NUM2DBL(exponent);
    glfwSetGamma(m, e);
    return exponent;
}

VALUE rb_glfw_monitor_primary(VALUE klass) {
    GLFWmonitor *m = glfwGetPrimaryMonitor();
    return Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, m);
}

