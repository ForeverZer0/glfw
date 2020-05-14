require "mkmf"


unless find_library('glfw', 'glfwInit')
  abort 'Unable to locate native GLFW library on system'
end

create_makefile("glfw/glfw")
