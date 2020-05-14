require "mkmf"

abort('Unable to locate GLFW library') unless find_library('glfw', 'glfwInit')

create_makefile("glfw/glfw")