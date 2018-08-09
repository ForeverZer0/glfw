require_relative "glfw/version"
require_relative "glfw/glfw"

module GLFW

  require "mkmf"

  os = RbConfig::CONFIG['host_os']

  puts os

  Window.new(800, 600, "Foobar") do |window|

    window.make_current

    until window.closing?
      GLFW.poll_events
      window.swap_buffers

    end
  end

    terminate
end

