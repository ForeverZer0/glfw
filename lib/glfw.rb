require_relative "glfw/version"
require_relative "glfw/glfw"

module GLFW



  p self.init

  p Vulkan.supported?
  

  Window.new(800, 600, "Hello, World!") do |window|


    window.make_current
    self.swap_interval(1)
    pixels32 = [0, 0, 255, 255].pack('C*') * (32 * 32) 
    pixels16 = [0, 255, 255, 255].pack('C*') * (16 * 16)

    window.set_icon(Image.new(32, 32, pixels32), Image.new(16, 16, pixels16))

    until window.closing?
      self.poll_events
      window.swap_buffers
    end

  end

  self.terminate
end

