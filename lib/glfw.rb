require_relative "glfw/version"
require_relative "glfw/glfw"

module GLFW

  class Window


  end

  self.init

  window = Window.new(800, 600, "Hello, World!")

  pixels32 = [0, 0, 255, 255].pack('C*') * (32 * 32) 
  pixels16 = [0, 255, 255, 255].pack('C*') * (16 * 16)

  window.set_icon(Image.new(32, 32, pixels32), Image.new(16, 16, pixels16))


  window.make_current

  self.swap_interval(1)

  window.enable_callback(CB_FILE_DROP, true)

  until window.closing?
    self.wait_events
    window.swap_buffers
  end

  window.destroy
  self.terminate
end
