require "mkmf"
require 'rbconfig'

def libname
  host = RbConfig::CONFIG['host_os']
  return 'glfw3' if /mswin|msys|mingw|cygwin|bccwin|wince|emc/.match?(host)
  'glfw'
end

abort('Unable to locate GLFW library') unless find_library(libname, 'glfwInit')
create_makefile("glfw/glfw")