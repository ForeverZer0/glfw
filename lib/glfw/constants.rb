
module GLFW

  class Cursor
    ##
    # Standard "arror" cursor shape.
    SHAPE_ARROW           = 0x00036001

    ##
    # I-beam cursor shape, commonly used for text editing.
    SHAPE_IBEAM           = 0x00036002

    ##
    # Cross-hair cursor shape
    SHAPE_CROSSHAIR       = 0x00036003

    ##
    # Hand cursor shape, common for clickable links, move, drag, etc.
    SHAPE_HAND            = 0x00036004

    ##
    # Horizontal-resize cursor shape.
    SHAPE_HRESIZE         = 0x00036005

    ##
    # Vertical-resize cursor shape.
    SHAPE_VRESIZE         = 0x00036006
  end

  class Window

    # @!group Cursor Mode
    
    ##
    # The cursor is visible and behaves normally.
    CURSOR_NORMAL    = 0x00034001

    ##
    # The cursor is invisible when it is over the content area of the window but does not restrict the cursor from leaving.
    CURSOR_HIDDEN    = 0x00034002

    ##
    # The application window hides and grabs the cursor, providing virtual and unlimited cursor movement, useful for implementing 3D camera controls.
    CURSOR_DISABLED  = 0x00034003

  end

  class GamepadState

    # @!group Gamepad Axes
  
      AXIS_LEFT_X         = 0
      AXIS_LEFT_Y         = 1
      AXIS_RIGHT_X        = 2
      AXIS_RIGHT_Y        = 3
      AXIS_LEFT_TRIGGER   = 4
      AXIS_RIGHT_TRIGGER  = 5

  
      # @!group Gamepad Buttons

      BUTTON_A             = 0
      BUTTON_B             = 1
      BUTTON_X             = 2
      BUTTON_Y             = 3
      BUTTON_LEFT_BUMPER   = 4
      BUTTON_RIGHT_BUMPER  = 5
      BUTTON_BACK          = 6
      BUTTON_START         = 7
      BUTTON_GUIDE         = 8
      BUTTON_LEFT_THUMB    = 9
      BUTTON_RIGHT_THUMB   = 10
      BUTTON_DPAD_UP       = 11
      BUTTON_DPAD_RIGHT    = 12
      BUTTON_DPAD_DOWN     = 13
      BUTTON_DPAD_LEFT     = 14
      BUTTON_CROSS         = BUTTON_A
      BUTTON_CIRCLE        = BUTTON_B
      BUTTON_SQUARE        = BUTTON_X
      BUTTON_TRIANGLE      = BUTTON_Y
    end

  # @!group Input States
  
  RELEASE               = 0
  PRESS                 = 1
  REPEAT                = 2
  
  # @!group Printable Keys

  KEY_SPACE              = 32
  KEY_APOSTROPHE         = 39
  KEY_COMMA              = 44
  KEY_MINUS              = 45
  KEY_PERIOD             = 46
  KEY_SLASH              = 47
  KEY_0                  = 48
  KEY_1                  = 49
  KEY_2                  = 50
  KEY_3                  = 51
  KEY_4                  = 52
  KEY_5                  = 53
  KEY_6                  = 54
  KEY_7                  = 55
  KEY_8                  = 56
  KEY_9                  = 57
  KEY_SEMICOLON          = 59
  KEY_EQUAL              = 61
  KEY_A                  = 65
  KEY_B                  = 66
  KEY_C                  = 67
  KEY_D                  = 68
  KEY_E                  = 69
  KEY_F                  = 70
  KEY_G                  = 71
  KEY_H                  = 72
  KEY_I                  = 73
  KEY_J                  = 74
  KEY_K                  = 75
  KEY_L                  = 76
  KEY_M                  = 77
  KEY_N                  = 78
  KEY_O                  = 79
  KEY_P                  = 80
  KEY_Q                  = 81
  KEY_R                  = 82
  KEY_S                  = 83
  KEY_T                  = 84
  KEY_U                  = 85
  KEY_V                  = 86
  KEY_W                  = 87
  KEY_X                  = 88
  KEY_Y                  = 89
  KEY_Z                  = 90
  KEY_LEFT_BRACKET       = 91
  KEY_BACKSLASH          = 92
  KEY_RIGHT_BRACKET      = 93
  KEY_GRAVE_ACCENT       = 96
  KEY_WORLD_1            = 161
  KEY_WORLD_2            = 162

  # @!group Non-printable Keys 

  # An unknown/invalid key
  KEY_UNKNOWN            = -1
  KEY_ESCAPE             = 256
  KEY_ENTER              = 257
  KEY_TAB                = 258
  KEY_BACKSPACE          = 259
  KEY_INSERT             = 260
  KEY_DELETE             = 261
  KEY_RIGHT              = 262
  KEY_LEFT               = 263
  KEY_DOWN               = 264
  KEY_UP                 = 265
  KEY_PAGE_UP            = 266
  KEY_PAGE_DOWN          = 267
  KEY_HOME               = 268
  KEY_END                = 269
  KEY_CAPS_LOCK          = 280
  KEY_SCROLL_LOCK        = 281
  KEY_NUM_LOCK           = 282
  KEY_PRINT_SCREEN       = 283
  KEY_PAUSE              = 284
  KEY_F1                 = 290
  KEY_F2                 = 291
  KEY_F3                 = 292
  KEY_F4                 = 293
  KEY_F5                 = 294
  KEY_F6                 = 295
  KEY_F7                 = 296
  KEY_F8                 = 297
  KEY_F9                 = 298
  KEY_F10                = 299
  KEY_F11                = 300
  KEY_F12                = 301
  KEY_F13                = 302
  KEY_F14                = 303
  KEY_F15                = 304
  KEY_F16                = 305
  KEY_F17                = 306
  KEY_F18                = 307
  KEY_F19                = 308
  KEY_F20                = 309
  KEY_F21                = 310
  KEY_F22                = 311
  KEY_F23                = 312
  KEY_F24                = 313
  KEY_F25                = 314
  KEY_KP_0               = 320
  KEY_KP_1               = 321
  KEY_KP_2               = 322
  KEY_KP_3               = 323
  KEY_KP_4               = 324
  KEY_KP_5               = 325
  KEY_KP_6               = 326
  KEY_KP_7               = 327
  KEY_KP_8               = 328
  KEY_KP_9               = 329
  KEY_KP_DECIMAL         = 330
  KEY_KP_DIVIDE          = 331
  KEY_KP_MULTIPLY        = 332
  KEY_KP_SUBTRACT        = 333
  KEY_KP_ADD             = 334
  KEY_KP_ENTER           = 335
  KEY_KP_EQUAL           = 336
  KEY_LEFT_SHIFT         = 340
  KEY_LEFT_CONTROL       = 341
  KEY_LEFT_ALT           = 342
  KEY_LEFT_SUPER         = 343
  KEY_RIGHT_SHIFT        = 344
  KEY_RIGHT_CONTROL      = 345
  KEY_RIGHT_ALT          = 346
  KEY_RIGHT_SUPER        = 347
  KEY_MENU               = 348

  # @!group Modifier Keys

  MOD_SHIFT               = 0x0001
  MOD_CONTROL             = 0x0002
  MOD_ALT                 = 0x0004
  MOD_SUPER               = 0x0008
  MOD_CAPS_LOCK           = 0x0010
  MOD_NUM_LOCK            = 0x0020

  # @!group Joystick Hats
  
  HAT_CENTERED           = 0
  HAT_UP                 = 1
  HAT_RIGHT              = 2
  HAT_DOWN               = 4
  HAT_LEFT               = 8
  HAT_RIGHT_UP           = (HAT_RIGHT | HAT_UP)
  HAT_RIGHT_DOWN         = (HAT_RIGHT | HAT_DOWN)
  HAT_LEFT_UP            = (HAT_LEFT  | HAT_UP)
  HAT_LEFT_DOWN          = (HAT_LEFT  | HAT_DOWN)
  
  # @!group Mouse Buttons

  MOUSE_BUTTON_1         = 0
  MOUSE_BUTTON_2         = 1
  MOUSE_BUTTON_3         = 2
  MOUSE_BUTTON_4         = 3
  MOUSE_BUTTON_5         = 4
  MOUSE_BUTTON_6         = 5
  MOUSE_BUTTON_7         = 6
  MOUSE_BUTTON_8         = 7
  MOUSE_BUTTON_LAST      = MOUSE_BUTTON_8
  MOUSE_BUTTON_LEFT      = MOUSE_BUTTON_1
  MOUSE_BUTTON_RIGHT     = MOUSE_BUTTON_2
  MOUSE_BUTTON_MIDDLE    = MOUSE_BUTTON_3
  
  # @!group Joystick Identifiers

  JOYSTICK_1            = 0
  JOYSTICK_2            = 1
  JOYSTICK_3            = 2
  JOYSTICK_4            = 3
  JOYSTICK_5            = 4
  JOYSTICK_6            = 5
  JOYSTICK_7            = 6
  JOYSTICK_8            = 7
  JOYSTICK_9            = 8
  JOYSTICK_10           = 9
  JOYSTICK_11           = 10
  JOYSTICK_12           = 11
  JOYSTICK_13           = 12
  JOYSTICK_14           = 13
  JOYSTICK_15           = 14
  JOYSTICK_16           = 15

  # @!group Error Codes

  ERR_NOT_INITIALIZED       = 0x00010001
  ERR_NO_CURRENT_CONTEXT    = 0x00010002
  ERR_INVALID_ENUM          = 0x00010003
  ERR_INVALID_VALUE         = 0x00010004
  ERR_OUT_OF_MEMORY         = 0x00010005
  ERR_API_UNAVAILABLE       = 0x00010006
  ERR_VERSION_UNAVAILABLE   = 0x00010007
  ERR_PLATFORM_ERROR        = 0x00010008
  ERR_FORMAT_UNAVAILABLE    = 0x00010009
  ERR_NO_WINDOW_CONTEXT     = 0x0001000A

  # @!group Window Hints

  HINT_RESIZABLE                = 0x00020003
  HINT_VISIBLE                  = 0x00020004
  HINT_DECORATED                = 0x00020005
  HINT_AUTO_ICONIFY             = 0x00020006
  HINT_FLOATING                 = 0x00020007
  HINT_MAXIMIZED                = 0x00020008
  HINT_CENTER_CURSOR            = 0x00020009
  HINT_TRANSPARENT_FRAMEBUFFER  = 0x0002000A
  HINT_FOCUS_ON_SHOW            = 0x0002000C
  HINT_SCALE_TO_MONITOR         = 0x0002200C
  HINT_RED_BITS                 = 0x00021001
  HINT_GREEN_BITS               = 0x00021002
  HINT_BLUE_BITS                = 0x00021003
  HINT_ALPHA_BITS               = 0x00021004
  HINT_DEPTH_BITS               = 0x00021005
  HINT_STENCIL_BITS             = 0x00021006
  HINT_ACCUM_RED_BITS           = 0x00021007
  HINT_ACCUM_GREEN_BITS         = 0x00021008
  HINT_ACCUM_BLUE_BITS          = 0x00021009
  HINT_ACCUM_ALPHA_BITS         = 0x0002100A
  HINT_AUX_BUFFERS              = 0x0002100B
  HINT_SAMPLES                  = 0x0002100D
  HINT_REFRESH_RATE             = 0x0002100F
  HINT_STEREO                   = 0x0002100C  
  HINT_SRGB_CAPABLE             = 0x0002100E
  HINT_DOUBLEBUFFER             = 0x00021010
  HINT_CLIENT_API               = 0x00022001
  HINT_CONTEXT_VERSION_MAJOR    = 0x00022002
  HINT_CONTEXT_VERSION_MINOR    = 0x00022003
  HINT_CONTEXT_REVISION         = 0x00022004
  HINT_CONTEXT_ROBUSTNESS       = 0x00022005
  HINT_CONTEXT_RELEASE_BEHAVIOR = 0x00022009
  HINT_OPENGL_FORWARD_COMPAT    = 0x00022006
  HINT_OPENGL_DEBUG_CONTEXT     = 0x00022007
  HINT_OPENGL_PROFILE           = 0x00022008
  HINT_COCOA_RETINA_FRAMEBUFFER = 0x00023001
  HINT_COCOA_FRAME_NAME         = 0x00023002
  HINT_COCOA_GRAPHICS_SWITCHING = 0x00023003
  HINT_X11_CLASS_NAME           = 0x00024001
  HINT_X11_INSTANCE_NAME        = 0x00024002
  HINT_CONTEXT_NO_ERROR         = 0x0002200A
  HINT_CONTEXT_CREATION_API     = 0x0002200B

  # @!group Values for HINT_RELEASE_BEHAVIOR

  RELEASE_BEHAVIOR_ANY   =          0
  RELEASE_BEHAVIOR_FLUSH = 0x00035001
  RELEASE_BEHAVIOR_NONE  = 0x00035002
    
  # @!group Values for HINT_CONTEXT_CREATION_API

  CONTEXT_API_NATIVE     = 0x00036001
  CONTEXT_API_EGL        = 0x00036002
  CONTEXT_API_OSMESA     = 0x00036003

  # @!group Values for HINT_CLIENT_API

  API_NONE        =          0
  API_OPENGL      = 0x00030001
  API_OPENGL_ES   = 0x00030002

  # @!group Values for HINT_OPENGL_PROFILE

  PROFILE_OPENGL_ANY     =          0
  PROFILE_OPENGL_CORE    = 0x00032001
  PROFILE_OPENGL_COMPAT  = 0x00032002

  # @!group Value for HINT_CONTEXT_ROBUSTNESS

  ROBUSTNESS_NONE                   =          0
  ROBUSTNESS_NO_RESET_NOTIFICATION  = 0x00031001
  ROBUSTNESS_LOSE_CONTEXT_ON_RESET  = 0x00031002

  # @!group Library initialization hints

  JOYSTICK_HAT_BUTTONS   = 0x00050001
  COCOA_CHDIR_RESOURCES  = 0x00051001
  COCOA_MENUBAR          = 0x00051002
end