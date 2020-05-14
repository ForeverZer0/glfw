#include "glfw.h"

VALUE cPoint;
VALUE cSize;
VALUE cVec2;

static VALUE rb_glfw_ivec_alloc(VALUE klass)
{
    RBivec2 *ivec = ALLOC(RBivec2);
    memset(ivec, 0, sizeof(RBivec2));
    return Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, ivec);
}

static VALUE rb_glfw_vec_alloc(VALUE klass)
{
    RBvec2 *vec = ALLOC(RBvec2);
    memset(vec, 0, sizeof(RBvec2));
    return Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, vec);
}

static VALUE rb_glfw_ivec_get_x(VALUE self)
{
    return INT2NUM(((RBivec2*) DATA_PTR(self))->x);
}

static VALUE rb_glfw_ivec_get_y(VALUE self)
{
    return INT2NUM(((RBivec2*) DATA_PTR(self))->y);
}

static VALUE rb_glfw_ivec_set_x(VALUE self, VALUE value)
{
    RBivec2 *ivec = DATA_PTR(self);
    ivec->x = NUM2INT(value);
    return value;
}

static VALUE rb_glfw_ivec_set_y(VALUE self, VALUE value)
{
    RBivec2 *ivec = DATA_PTR(self);
    ivec->y = NUM2INT(value);
    return value;
}


static VALUE rb_glfw_vec_get_x(VALUE self)
{
    return DBL2NUM(((RBvec2*) DATA_PTR(self))->x);
}

static VALUE rb_glfw_vec_get_y(VALUE self)
{
    return DBL2NUM(((RBvec2*) DATA_PTR(self))->y);
}

static VALUE rb_glfw_vec_set_x(VALUE self, VALUE value)
{
    RBvec2 *vec = DATA_PTR(self);
    vec->x = NUM2DBL(value);
    return value;
}

static VALUE rb_glfw_vec_set_y(VALUE self, VALUE value)
{
    RBvec2 *vec = DATA_PTR(self);
    vec->y = NUM2DBL(value);
    return value;
}

static VALUE rb_glfw_vec_initialize(VALUE self, VALUE x, VALUE y)
{
    RBvec2 *vec = DATA_PTR(self);
    vec->x = NUM2DBL(x);
    vec->y = NUM2DBL(y);
    return Qnil;
}

static VALUE rb_glfw_ivec_initialize(VALUE self, VALUE x, VALUE y)
{
    RBivec2 *ivec = DATA_PTR(self);
    ivec->x = NUM2INT(x);
    ivec->y = NUM2INT(y);
    return Qnil;
}

static VALUE rb_glfw_ivec_equal(VALUE self, VALUE other)
{
    if (CLASS_OF(self) != CLASS_OF(other))
        return Qfalse;

    RBivec2 *v1 = DATA_PTR(self), *v2 = DATA_PTR(other);
    return RB_BOOL(v1->x == v2->x && v1->y == v2->y);
}

static VALUE rb_glfw_ivec_inspect(VALUE self)
{   
    RBivec2 *v = DATA_PTR(self);
    return rb_sprintf("<%d, %d>", v->x, v->y);
}

static VALUE rb_glfw_vec_inspect(VALUE self)
{   
    RBvec2 *v = DATA_PTR(self);
    return rb_sprintf("<%f, %f>", v->x, v->y);
}

VALUE rb_glfw_ivec2_create(VALUE klass, int x, int y)
{
    RBivec2 *ivec = ALLOC(RBivec2);
    ivec->x = x;
    ivec->y = y;
    return Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, ivec);
}

VALUE rb_glfw_vec2_create(VALUE klass, double x, double y)
{
    RBvec2 *vec = ALLOC(RBvec2);
    vec->x = x;
    vec->y = y;
    return Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, vec);
}

void rb_glfw_common_init(void)
{
    cPoint = rb_define_class_under(mGLFW, "Point", rb_cObject);
    cSize = rb_define_class_under(mGLFW, "Size", rb_cObject);
    cVec2 = rb_define_class_under(mGLFW, "Vec2", rb_cObject);

    rb_define_alloc_func(cPoint, rb_glfw_ivec_alloc);
    rb_define_alloc_func(cSize, rb_glfw_ivec_alloc);
    rb_define_alloc_func(cSize, rb_glfw_vec_alloc);

    rb_define_method(cPoint, "x", rb_glfw_ivec_get_x, 0);
    rb_define_method(cPoint, "y", rb_glfw_ivec_get_y, 0);
    rb_define_method(cPoint, "x=", rb_glfw_ivec_set_x, 1);
    rb_define_method(cPoint, "y=", rb_glfw_ivec_set_y, 1);

    rb_define_method(cSize, "width", rb_glfw_ivec_get_x, 0);
    rb_define_method(cSize, "height", rb_glfw_ivec_get_y, 0);
    rb_define_method(cSize, "width=", rb_glfw_ivec_set_x, 1);
    rb_define_method(cSize, "height=", rb_glfw_ivec_set_y, 1);

    rb_define_method(cVec2, "x", rb_glfw_vec_get_x, 0);
    rb_define_method(cVec2, "y", rb_glfw_vec_get_y, 0);
    rb_define_method(cVec2, "x=", rb_glfw_vec_set_x, 1);
    rb_define_method(cVec2, "y=", rb_glfw_vec_set_y, 1);

    rb_define_method(cPoint, "==", rb_glfw_ivec_equal, 1);
    rb_define_method(cPoint, "eql?", rb_glfw_ivec_equal, 1);
    rb_define_method(cSize, "==", rb_glfw_ivec_equal, 1);
    rb_define_method(cSize, "eql?", rb_glfw_ivec_equal, 1);
    rb_define_method(cPoint, "inspect", rb_glfw_ivec_inspect, 0);
    rb_define_method(cSize, "inspect", rb_glfw_ivec_inspect, 0);
    rb_define_method(cVec2, "inspect", rb_glfw_vec_inspect, 0);

    rb_define_method(cPoint, "initialize", rb_glfw_ivec_initialize, 2);
    rb_define_method(cSize, "initialize", rb_glfw_ivec_initialize, 2);
    rb_define_method(cVec2, "initialize", rb_glfw_vec_initialize, 2);
}