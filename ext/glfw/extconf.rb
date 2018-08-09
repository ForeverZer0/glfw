require "mkmf"


headers = [RbConfig::CONFIG['includedir'], File.dirname(__FILE__)]
libdirs = [RbConfig::CONFIG['libdir']]

dir = 0.size == 4 ? 'ming32' : 'ming64'
libdirs << File.expand_path(File.join(File.dirname(__FILE__), dir))

case RbConfig::CONFIG['host_os']
when /mingw/
  $LOCAL_LIBS << '-lglfw3 -lgdi32 -lopengl32'
when /darwin/
  $LOCAL_LIBS << '-lglfw3'
when /linux/
  $LOCAL_LIBS << '-lglfw3'
end

dir_config('glfw', headers, libdirs)

create_makefile("glfw/glfw")
