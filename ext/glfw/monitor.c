#include "glfw.h"

VALUE cb_monitor;
VALUE cMonitor;
VALUE cVideoMode;

static inline VALUE rb_glfw_video_create(const GLFWvidmode *value)
{
    GLFWvidmode *video = ALLOC(GLFWvidmode);
    if (value)
        memcpy(video, value, sizeof(GLFWvidmode));
    else
        memset(video, 0, sizeof(GLFWvidmode));
    return Data_Wrap_Struct(cVideoMode, NULL, RUBY_DEFAULT_FREE, video);
}

static VALUE rb_glfw_video_alloc(VALUE klass)
{
    GLFWvidmode *video = ALLOC(GLFWvidmode);
    memset(video, 0, sizeof(GLFWvidmode));
    return Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, video);
}

static VALUE rb_glfw_video_width(VALUE self)
{   
    return INT2NUM(((GLFWvidmode*) DATA_PTR(self))->width);
}

static VALUE rb_glfw_video_height(VALUE self)
{   
    return INT2NUM(((GLFWvidmode*) DATA_PTR(self))->height);
}

static VALUE rb_glfw_video_r_bits(VALUE self)
{   
    return INT2NUM(((GLFWvidmode*) DATA_PTR(self))->redBits);
}

static VALUE rb_glfw_video_g_bits(VALUE self)
{   
    return INT2NUM(((GLFWvidmode*) DATA_PTR(self))->greenBits);
}

static VALUE rb_glfw_video_b_bits(VALUE self)
{   
    return INT2NUM(((GLFWvidmode*) DATA_PTR(self))->blueBits);
}

static VALUE rb_glfw_video_refresh_rate(VALUE self)
{   
    return INT2NUM(((GLFWvidmode*) DATA_PTR(self))->refreshRate);
}

static VALUE rb_glfw_video_to_s(VALUE self)
{
    GLFWvidmode *v = DATA_PTR(self);
    return rb_sprintf("<%s: width:%d, height:%d, r:%d, g:%d, b:%d, rate:%dhz>", rb_class2name(CLASS_OF(self)), v->width, v->height, v->redBits, v->greenBits, v->blueBits, v->refreshRate);
}

static VALUE rb_glfw_monitor_get_gamma_ramp(VALUE self)
{
    const GLFWgammaramp *ramp = glfwGetGammaRamp(DATA_PTR(self));

    long capa = (long) ramp->size;
    VALUE r = rb_ary_new_capa(capa);
    VALUE g = rb_ary_new_capa(capa);
    VALUE b = rb_ary_new_capa(capa);

    for (long i = 0; i < capa; i++)
    {
        rb_ary_store(r, i, USHORT2NUM(ramp->red[i]));
        rb_ary_store(g, i, USHORT2NUM(ramp->green[i]));
        rb_ary_store(b, i, USHORT2NUM(ramp->blue[i]));
    }
    return rb_ary_new_from_args(3, r, g, b);
}

static VALUE rb_glfw_monitor_set_gamma_ramp(VALUE self, VALUE gamma)
{
    if (!RB_TYPE_P(gamma, T_ARRAY))
        rb_raise(rb_eTypeError, "%s us not an Array", rb_obj_classname(CLASS_OF(gamma)));
    if (rb_array_len(gamma) != 3)
        rb_raise(rb_eArgError, "gamma array must have a length of 3");


    VALUE r = rb_ary_entry(gamma, 0);
    VALUE g = rb_ary_entry(gamma, 1);
    VALUE b = rb_ary_entry(gamma, 2);

    long capa = rb_array_len(g);
    if (rb_array_len(r) != capa || rb_array_len(b) != capa)
        rb_raise(rb_eArgError, "all arrays must be the same length");

    GLFWgammaramp ramp = {0};
    ramp.size = (unsigned int) capa;
    ramp.red = xmalloc(sizeof(short) * capa);
    ramp.green = xmalloc(sizeof(short) * capa);
    ramp.blue = xmalloc(sizeof(short) * capa);

    for (long i = 0; i < capa; i++)
    {
        ramp.red[i] = NUM2USHORT(rb_ary_entry(r, i));
        ramp.green[i] = NUM2USHORT(rb_ary_entry(g, i));
        ramp.blue[i] = NUM2USHORT(rb_ary_entry(b, i));
    }

    glfwSetGammaRamp(DATA_PTR(self), &ramp);

    xfree(ramp.red);
    xfree(ramp.green);
    xfree(ramp.blue);

    return gamma;
}

static VALUE rb_glfw_monitor_gamma(VALUE self, VALUE gamma)
{
    glfwSetGamma(DATA_PTR(self), NUM2FLT(gamma));
    return Qnil;
}

static VALUE rb_glfw_monitor_content_scale(VALUE self)
{
    float x, y;
    glfwGetMonitorContentScale(DATA_PTR(self), &x, &y);
    return rb_glfw_vec2_create(cVec2, x, y);
}

static VALUE rb_glfw_monitor_video_mode(VALUE self)
{
    const GLFWvidmode *mode = glfwGetVideoMode(DATA_PTR(self));
    return rb_glfw_video_create(mode);
}

static VALUE rb_glfw_monitor_video_modes(VALUE self)
{
    int count;
    const GLFWvidmode *modes = glfwGetVideoModes(DATA_PTR(self), &count);

    VALUE ary = rb_ary_new_capa(count);
    for (int i = 0; i < count; i++)
    {
        VALUE video = rb_glfw_video_create(&modes[i]);
        rb_ary_store(ary, i, video);
    }
    return ary;
}

static VALUE rb_glfw_monitor_work_area_location(VALUE self)
{
    int x, y;
    glfwGetMonitorWorkarea(DATA_PTR(self), &x, &y, NULL, NULL);
    return rb_glfw_ivec2_create(cPoint, x, y);
}

static VALUE rb_glfw_monitor_work_area_size(VALUE self)
{
    int w, h;
    glfwGetMonitorWorkarea(DATA_PTR(self), NULL, NULL, &w, &h);
    return rb_glfw_ivec2_create(cSize, w, h);
}

static VALUE rb_glfw_monitor_size(VALUE self)
{
    const GLFWvidmode *vid = glfwGetVideoMode(DATA_PTR(self));
    return rb_glfw_ivec2_create(cSize, vid->width, vid->height);
}

static VALUE rb_glfw_monitor_physical_size(VALUE self)
{
    int w, h;
    glfwGetMonitorPhysicalSize(DATA_PTR(self), &w, &h);
    return rb_glfw_ivec2_create(cSize, w, h);
}

static VALUE rb_glfw_monitor_position(VALUE self)
{
    int x, y;
    glfwGetMonitorPos(DATA_PTR(self), &x, &y);
    return rb_glfw_ivec2_create(cPoint, x, y);
}

static VALUE rb_glfw_monitor_available(VALUE klass)
{
    int count;
    GLFWmonitor **monitors = glfwGetMonitors(&count);
    VALUE ary = rb_ary_new_capa(count);

    for (int i = 0; i < count; i++)
    {
        VALUE monitor = Data_Wrap_Struct(klass, NULL, NULL, monitors[i]);
        rb_ary_store(ary, i, monitor);
    }

    return ary;
}

static VALUE rb_glfw_monitor_name(VALUE self)
{
    return rb_str_new_cstr(glfwGetMonitorName(DATA_PTR(self)));
}

static VALUE rb_glfw_monitor_eql(VALUE self, VALUE other)
{

    if (CLASS_OF(self) != CLASS_OF(other))
        return Qfalse;

    return RB_BOOL(DATA_PTR(self) == DATA_PTR(other));
}

static VALUE rb_glfw_monitor_primary(VALUE klass)
{
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    return monitor ? Data_Wrap_Struct(klass, NULL, NULL, monitor) : Qnil;
}

static void rb_glfw_monitor_cb_connected(GLFWmonitor *monitor, int connected)
{
    if (RTEST(cb_monitor))
    {
        VALUE mon = Data_Wrap_Struct(cMonitor, NULL, NULL, monitor);
        VALUE state = RB_BOOL(connected == GLFW_CONNECTED);
        rb_proc_call(cb_monitor, rb_ary_new_from_args(2, mon, state));
    }
}

static VALUE rb_glfw_monitor_on_connection(VALUE klass)
{
    VALUE current = cb_monitor;
    if (rb_block_given_p())
    {
        cb_monitor = rb_block_proc();
        glfwSetMonitorCallback(rb_glfw_monitor_cb_connected);
        rb_iv_set(cMonitor, "@connection_proc", cb_monitor);
    }
    else
    {
        cb_monitor = Qnil;
        glfwSetMonitorCallback(NULL);
        rb_iv_set(cMonitor, "@connection_proc", Qnil);
    }
    return current;
}

static VALUE rb_glfw_monitor_to_s(VALUE self) {
    return rb_str_new_cstr(glfwGetMonitorName(DATA_PTR(self)));
}

void rb_glfw_monitor_init(void)
{

    cVideoMode = rb_define_class_under(mGLFW, "VideoMode", rb_cObject);
    rb_define_alloc_func(cVideoMode, rb_glfw_video_alloc);
    rb_define_method(cVideoMode, "width", rb_glfw_video_width, 0);
    rb_define_method(cVideoMode, "height", rb_glfw_video_height, 0);
    rb_define_method(cVideoMode, "red_bits", rb_glfw_video_r_bits, 0);
    rb_define_method(cVideoMode, "green_bits", rb_glfw_video_g_bits, 0);
    rb_define_method(cVideoMode, "blue_bits", rb_glfw_video_b_bits, 0);
    rb_define_method(cVideoMode, "refresh_rate", rb_glfw_video_refresh_rate, 0);
    rb_define_method(cVideoMode, "to_s", rb_glfw_video_to_s, 0);

    cMonitor = rb_define_class_under(mGLFW, "Monitor", rb_cObject);
    rb_define_singleton_method(cMonitor, "available", rb_glfw_monitor_available, 0);
    rb_define_singleton_method(cMonitor, "primary", rb_glfw_monitor_primary, 0);
    rb_define_singleton_method(cMonitor, "on_connection", rb_glfw_monitor_on_connection, 0);

    rb_define_method(cMonitor, "name", rb_glfw_monitor_name, 0);
    rb_define_method(cMonitor, "position", rb_glfw_monitor_position, 0);
    rb_define_method(cMonitor, "physical_size", rb_glfw_monitor_physical_size, 0);
    rb_define_method(cMonitor, "size", rb_glfw_monitor_size, 0);
    rb_define_method(cMonitor, "client_position", rb_glfw_monitor_work_area_location, 0);
    rb_define_method(cMonitor, "client_size", rb_glfw_monitor_work_area_size, 0);
    rb_define_method(cMonitor, "video_mode", rb_glfw_monitor_video_mode, 0);
    rb_define_method(cMonitor, "video_modes", rb_glfw_monitor_video_modes, 0);
    rb_define_method(cMonitor, "content_scale", rb_glfw_monitor_content_scale, 0);
    rb_define_method(cMonitor, "gamma", rb_glfw_monitor_gamma, 1);
    rb_define_method(cMonitor, "gamma_ramp", rb_glfw_monitor_get_gamma_ramp, 0);
    rb_define_method(cMonitor, "gamma_ramp=", rb_glfw_monitor_set_gamma_ramp, 1);
    rb_define_method(cMonitor, "==", rb_glfw_monitor_eql, 1);
    rb_define_method(cMonitor, "eql?", rb_glfw_monitor_eql, 1);
    rb_define_method(cMonitor, "to_s", rb_glfw_monitor_to_s, 0);

    cb_monitor = Qnil;
}