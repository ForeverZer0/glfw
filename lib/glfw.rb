require_relative 'glfw/version'
require_relative 'glfw/stubs'
require_relative 'glfw/constants'
require_relative 'glfw/glfw'

# module GLFW


#   GLFW.init

#   GL_CLEAR_BUFFER_BIT = 0x4000
#   include Fiddle

#   Window.new(800, 600, "GLFW") do |window|

#     window.make_current


#     glClear = GLFW.import('glClear', [-TYPE_INT], TYPE_VOID)
#     glClearColor = GLFW.import('glClearColor', [TYPE_FLOAT, TYPE_FLOAT, TYPE_FLOAT, TYPE_FLOAT], TYPE_VOID)

#     glClearColor.call(0.2, 0.3, 0.4, 1.0)

#     until window.closing?
  
#       glClear.call(GL_CLEAR_BUFFER_BIT)
#       window.swap_buffers
#       GLFW.poll_events
#     end

#   end

#   GLFW.terminate
# end