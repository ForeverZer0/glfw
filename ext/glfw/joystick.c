
#include "glfw.h"

VALUE mJoystick;
VALUE cGamepadState;
VALUE cb_joystick;

static VALUE rb_glfw_gamepad_state_alloc(VALUE klass)
{
    GLFWgamepadstate *state = ALLOC(GLFWgamepadstate);
    memset(state, 0, sizeof(GLFWgamepadstate));
    return Data_Wrap_Struct(klass, NULL, RUBY_DEFAULT_FREE, state);
}

static VALUE rb_glfw_gamepad_axis(VALUE self, VALUE axis)
{
    int index = NUM2INT(axis);
    if (index >= 0 && index <= GLFW_GAMEPAD_AXIS_LAST)
        return DBL2NUM(((GLFWgamepadstate*) DATA_PTR(self))->axes[index]);
    return DBL2NUM(0.0);
}

static VALUE rb_glfw_gamepad_button(VALUE self, VALUE button)
{
    int index = NUM2INT(button);
    if (index >= 0 && index <= GLFW_GAMEPAD_BUTTON_LAST)
        return RB_BOOL(((GLFWgamepadstate*) DATA_PTR(self))->buttons[index]);
    return Qfalse;
}

static VALUE rb_glfw_joystick_is_present(VALUE module, VALUE jid)
{
    return RB_BOOL(glfwJoystickPresent(NUM2INT(jid)));
}

static VALUE rb_glfw_joystick_is_gamepad(VALUE module, VALUE jid)
{
    return RB_BOOL(glfwJoystickIsGamepad(NUM2INT(jid)));
}

static VALUE rb_glfw_joystick_name(VALUE module, VALUE jid)
{
    const char *name = glfwGetJoystickName(NUM2INT(jid));
    return name ? rb_str_new_cstr(name) : Qnil;
}

static VALUE rb_glfw_joystick_gamepad_name(VALUE module, VALUE jid)
{
    const char *name = glfwGetGamepadName(NUM2INT(jid));
    return name ? rb_str_new_cstr(name) : Qnil;
}

static VALUE rb_glfw_joystick_guid(VALUE module, VALUE jid)
{
    const char *guid = glfwGetJoystickGUID(NUM2INT(jid));
    return guid ? rb_str_new_cstr(guid) : Qnil;
}

static void rb_glfw_joystick_cb_connection(int jid, int event)
{
    if (RTEST(cb_joystick))
    {
        VALUE args = rb_ary_new_from_args(2, INT2NUM(jid), RB_BOOL(event == GLFW_CONNECTED));
        rb_proc_call(cb_joystick, args);
    }
}

static VALUE rb_glfw_joystick_on_connection(VALUE module)
{
    VALUE current = cb_joystick;
    if (rb_block_given_p())
    {
        cb_joystick = rb_block_proc();
        rb_iv_set(mJoystick, "@connection_proc", cb_joystick);
        glfwSetJoystickCallback(rb_glfw_joystick_cb_connection);
    }
    else
    {
        cb_joystick = Qnil;
        rb_iv_set(mJoystick, "@connection_proc", Qnil);
        glfwSetJoystickCallback(NULL);
    }
    return current;
}

static VALUE rb_glfw_joystick_update_mappings(int argc, VALUE *argv, VALUE module)
{
    int count = 0;
    for (int i = 0; i < argc; i++)
    {
        const char *str = StringValueCStr(argv[i]);
        count += glfwUpdateGamepadMappings(str);
    }
    return INT2NUM(count);
}

static VALUE rb_glfw_joystick_gamepad_state(VALUE module, VALUE jid)
{
    GLFWgamepadstate *state = ALLOC(GLFWgamepadstate);
    if (glfwGetGamepadState(NUM2INT(jid), state))
        return Data_Wrap_Struct(cGamepadState, NULL, RUBY_DEFAULT_FREE, state);
    xfree(state);
    return Qnil;
}

static VALUE rb_glfw_joystick_buttons(VALUE module, VALUE jid)
{
    int count;
    const unsigned char* buttons = glfwGetJoystickButtons(NUM2INT(jid), &count);
    if (count > 0)
    {
        VALUE ary = rb_ary_new_capa(count);
        for (int i = 0; i < count; i++)
            rb_ary_store(ary, i, RB_BOOL(buttons[i]));
        return ary;
    }
    return Qnil;
}

static VALUE rb_glfw_joystick_axes(VALUE module, VALUE jid)
{
    int count;
    const float* axes = glfwGetJoystickAxes(NUM2INT(jid), &count);
    if (count > 0)
    {
        VALUE ary = rb_ary_new_capa(count);
        for (int i = 0; i < count; i++)
            rb_ary_store(ary, i, DBL2NUM(axes[i]));
        return ary;
    }
    return Qnil;
}

static VALUE rb_glfw_joystick_hats(VALUE module, VALUE jid)
{
    int count;
    const unsigned char* hats = glfwGetJoystickHats(NUM2INT(jid), &count);
    if (count > 0)
    {
        VALUE ary = rb_ary_new_capa(count);
        for (int i = 0; i < count; i++)
            rb_ary_store(ary, i, RB_BOOL(hats[i]));
        return ary;
    }
    return Qnil;
}

void rb_glfw_joystick_init(void)
{
    cGamepadState = rb_define_class_under(mGLFW, "GamepadState", rb_cObject);
    rb_define_alloc_func(cGamepadState, rb_glfw_gamepad_state_alloc);
    rb_define_method(cGamepadState, "axis", rb_glfw_gamepad_axis, 1);
    rb_define_method(cGamepadState, "button", rb_glfw_gamepad_button, 1);

    mJoystick = rb_define_module_under(mGLFW, "Joystick");
    rb_define_singleton_method(mJoystick, "gamepad_state", rb_glfw_joystick_gamepad_state, 1);
    rb_define_singleton_method(mJoystick, "name", rb_glfw_joystick_name, 1);
    rb_define_singleton_method(mJoystick, "gamepad_name", rb_glfw_joystick_gamepad_name, 1);
    rb_define_singleton_method(mJoystick, "present?", rb_glfw_joystick_is_present, 1);
    rb_define_singleton_method(mJoystick, "gamepad?", rb_glfw_joystick_is_gamepad, 1);
    rb_define_singleton_method(mJoystick, "guid", rb_glfw_joystick_guid, 1);
    rb_define_singleton_method(mJoystick, "buttons", rb_glfw_joystick_buttons, 1);
    rb_define_singleton_method(mJoystick, "axes", rb_glfw_joystick_axes, 1);
    rb_define_singleton_method(mJoystick, "hats", rb_glfw_joystick_hats, 1);
    rb_define_singleton_method(mJoystick, "update_mappings", rb_glfw_joystick_update_mappings, -1);
    rb_define_singleton_method(mJoystick, "on_connection", rb_glfw_joystick_on_connection, 0);

    cb_joystick = Qnil;
}
