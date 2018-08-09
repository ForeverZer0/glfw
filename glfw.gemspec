
lib = File.expand_path("../lib", __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require "glfw/version"

Gem::Specification.new do |spec|
  spec.name          = "glfw"
  spec.version       = GLFW::VERSION
  spec.authors       = ["Eric Freed"]
  spec.email         = ["efreed09@gmail.com"]

  spec.summary       = %q{GLFW is an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan development on the desktop. It provides a simple API for creating windows, contexts and surfaces, receiving input and events.}
  spec.description   = %q{This is a Ruby C-extension that for the excellent GLFW library. Unlike other bindings, this gem goes beyond just providing a 1:1 wrapper of the functions, and has been organized to be used in a more object-oriented, Ruby way. Being statically linked with the included object file during compilation alleviates any headaches with regards to versioning or dependencies, as none are required for this gem}
  spec.homepage      = "https://github.com/ForeverZer0/glfw"
  spec.license       = "MIT"

  spec.files         = Dir.chdir(File.expand_path('..', __FILE__)) do
    `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  end
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]
  spec.extensions    = ["ext/glfw/extconf.rb"]

  spec.add_development_dependency "bundler", "~> 1.16"
  spec.add_development_dependency "rake", "~> 10.0"
  spec.add_development_dependency "rake-compiler", '~> 0'
  spec.add_development_dependency "minitest", "~> 5.0"
end
