require_relative "glfw/version"
require_relative "glfw/glfw"

module GLFW

  class Window


  end

  self.init

  window = Window.new(800, 600, "Hello, World!")

  window.make_current
  # window.aspect_ratio(4, 3)
  # window.show

  self.swap_interval(1)

  window.enable_callback(CB_FILE_DROP, true)

  until window.closing?
    self.wait_events
    window.swap_buffers
  end

  window.destroy
  self.terminate
end
