# ![icon](./glfw-icon.png) GLFW

This is a Ruby C-extension for the excellent [GLFW](https://github.com/glfw/glfw) library. Unlike other bindings, this gem goes beyond just providing a 1:1 wrapper of the functions, and has been organized to be used in a more object-oriented, Ruby way.

## Installation

For Windows users, the dependencies will automatically be fetched and installed into Ruby's environment using the built-in functionality of MSYS2. 

For Unix-like systems, simply have GLFW installed globally, and it will be found and linked against during the build process.


### From [RubyGems.org](https://rubygems.org/gems/glfw)

    $ gem install glfw

### From Source

Open a terminal/command prompt in the base directory:

    $ gem build glfw.gemspec
    $ gem install glfw-[VERSION].gem

## Features

* Implemented in C for higher performance than FFI-based bindings can achieve, very desirable for game/graphics applications
* Covers the entire GLFW API (exception of creating a Vulkan surface, possible support in future if in-demand)
* Built-in image-loader supporting most common image formats (can also be used for OpenGL texture loading)
* Intuitive API, implemented using common Ruby idioms, while also staying true to the base API
* Convenience methods for importing and returning OpenGL functions as `Fiddle::Function` instances
* Stubs and documentation for all C functions so that linters can detect signatures and offer code completion, inline documentation, etc.
* Painless cross-platform support, uses natively installed libraries on Unix-like systems, and automatically retrieves native dependencies using MSYS on Windows (meaning it "just works" and you need no special deployment process or dependency handling for Windows systems)

## Usage

### Window Creation

At its simplest, to create a platform-specific window with an OpenGL context requires very little code.

```ruby
GLFW::Window.new(800, 600, "Hello, World!") do |window|

  until window.closing?
    GLFW.poll_events
    window.swap_buffers
    # Your rendering code goes here
  end
end
```

You will likely want to fine-tune the created context to what your application requires. GLFW exposes these as "hints", which can be set **before** a window is created.

```ruby
# Initialize GLFW core
GLFW.init

# Load default window hints. This will reset any previous hints given
GLFW::Window.default_hints

# Window will be NOT be decorated (title, border, close widget, etc)
GLFW::Window.hint(GLFW::HINT_DECORATED, false)

# Specify MINIMUM required OpenGL version
GLFW::Window.hint(GLFW::HINT_CONTEXT_VERSION_MAJOR, 3)
GLFW::Window.hint(GLFW::HINT_CONTEXT_VERSION_MAJOR, 3)
```

All constants for creation hints are prefixed with `HINT`.

### Callbacks

GLFW offers a high-level of control of the application window, including callbacks for nearly every relevant system event that effects the window (see documentation for what all callbacks are available). Callbacks are implemented by using Ruby blocks to create a closure that will be invoked the callback fires. 

All callbacks in the libaray follow the same idioms:

```ruby
window.on_framebuffer_resize do |width, height|
  # Block will be called when framebuffer size changes (change projection matrix, viewport, etc.)
end

window.on_key do |key, scancode, action, mods|
  # Block called when keyboard input changes (process keystroke)
end

# Use method without block to unsubscribe from callback
window.on_key
```

#### Breaking Changes

Prior versions of the gem used a method of enabling all callbacks via a single method, which would then invoke a
pre-defined method that had to be overridden/aliased. Starting with version 3.3.2, this functiionality has been
removed in favor of using Ruby blocks, which is more familiar and Ruby-like, as well as being more flexible.

## Documentation

The gem documention can be found [here](https://www.rubydoc.info/gems/glfw/3.3.2.0), providing coverage of the entire API surface.

For more in depth explanation of some features, the native GLFW library offers a very in-depth and detailed [documentation](http://www.glfw.org/docs/latest/intro_guide.html) that may be used to augment it, or even as a stand-alone source of information to understanding the library. While not all features will match up
with a 1:1 ratio, the naming conventions and idioms are the same and self-explanatory to use the C documentation for the Ruby gem.

Feel free to open an [issue](https://github.com/ForeverZer0/glfw/issues) for any additional questions that may not be covered, I would be happy to offer any help that I can.

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/ForeverZer0/glfw. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [Contributor Covenant](http://contributor-covenant.org) code of conduct.

Pull requests are always welcome.

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).

[GLFW](http://www.glfw.org) is is licensed under the [zlib/libpng](http://www.glfw.org/license.html) license.

## Code of Conduct

Everyone interacting in the GLFW project’s codebases, issue trackers, chat rooms and mailing lists is expected to follow the [code of conduct](https://github.com/ForeverZer0/glfw/blob/master/CODE_OF_CONDUCT.md).
