require "rake/extensiontask"

task :build => :compile

Rake::ExtensionTask.new("glfw") do |ext|
  ext.lib_dir = "lib/glfw"
end

task :default => [:clobber, :compile]
