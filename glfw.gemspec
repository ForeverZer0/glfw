
require_relative 'lib/glfw/version'

Gem::Specification.new do |spec|
  spec.name          = "glfw"
  spec.version       = GLFW::VERSION
  spec.authors       = ["Eric Freed"]
  spec.email         = ["efreed09@gmail.com"]

  spec.summary       = %q{GLFW is an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan development on the desktop. It provides a simple API for creating windows, contexts and surfaces, receiving input and events.}
  spec.description   = %q{This is a high-performance Ruby C-extension for the excellent GLFW3 library.}
  spec.homepage      = 'https://github.com/ForeverZer0/glfw'
  spec.license       = 'MIT'

  spec.files         = Dir.chdir(File.expand_path('..', __FILE__)) do
    `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  end

  spec.require_paths = ["lib"]
  spec.extensions    = ["ext/glfw/extconf.rb"]

  spec.required_ruby_version = '>= 2.0.0'

  spec.add_development_dependency 'rake", "~> 13.0'
  spec.add_development_dependency 'rake-compiler', '~> 0'
end
