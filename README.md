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

To enable a callback:

```ruby
window.on_resize do |width, height|
  # Process width/height changes
  p [width, height]
end
```

## Documentation

The GLFW API offers a very in-depth and detailed [documentation](http://www.glfw.org/docs/latest/intro_guide.html) that may be used as a subsitute until complete, and as a fantastic stand-alone source of information to understanding the library.

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/ForeverZer0/glfw. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [Contributor Covenant](http://contributor-covenant.org) code of conduct.

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).

[GLFW](http://www.glfw.org) is is licensed under the [zlib/libpng](http://www.glfw.org/license.html) license.

## Code of Conduct

Everyone interacting in the GLFW project’s codebases, issue trackers, chat rooms and mailing lists is expected to follow the [code of conduct](https://github.com/ForeverZer0/glfw/blob/master/CODE_OF_CONDUCT.md).
