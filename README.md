# ![icon](./glfw-icon.png) GLFW

This is a Ruby C-extension for the excellent [GLFW](https://github.com/glfw/glfw) library. Unlike other bindings, this gem goes beyond just providing a 1:1 wrapper of the functions, and has been organized to be used in a more object-oriented, Ruby way.

## Installation

For Windows users, you can download the pre-built binaries [here](https://www.glfw.org/download.html) for your target architecture, or both. Place these within the their respective folders withing the `ext/glfw/` directory.

For Unix users, simply have GLFW installed globally, and it will be found and linked against during the build process.


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
GLFW.load_default_hints

# Window will be NOT be decorated (title, border, close widget, etc)
GLFW.hint(GLFW::HINT_DECORATED, false)

# Specify MINIMUM required OpenGL version
GLFW.hint(GLFW::HINT_CONTEXT_VERSION_MAJOR, 3)
GLFW.hint(GLFW::HINT_CONTEXT_VERSION_MAJOR, 0)
```

All constants for creation hints are prefixed with `HINT`.

### Callbacks

GLFW offers a high-level of control of the application window, including callbacks for nearly every relevant system event that effects the window (see documentation for what all callbacks are available). By default, most of these callbacks are disabled, and need to be enabled with a method call to have them fired. This is for performance reasons, as it is inefficient to have them all being invoked if they are not going to be used.

To enable a callback:

```ruby
window.enable_callback(GLFW::CB_RESIZED, true)
```

You then have two options; to either alias the `GLFW::Window` class for the relevant callback, or more commonly to create your own class that inherits from `GLFW::Window`.

```ruby
class MyGame < GLFW::Window

  def initialize
    super(800, 600, "My Awesome Game Title", fullscreen: true)
    enable_callback(GLFW::CB_RESIZED, true)
  end

  # This method will be invoked when the window is resized.
  def resized(width, hight)
    # Your code goes here.
    # The "width/height" arguments passed are the new size
  end
end
```

All constants for callbacks are prefixed with `CB`.

## Documentation

The documentation is a work-in-progress.

The GLFW API offers a very in-depth and detailed [documentation](http://www.glfw.org/docs/latest/intro_guide.html) that may be used as a subsitute until complete, and as a fantastic stand-alone source of information to understanding the linrary.

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/ForeverZer0/glfw. This project is intended to be a safe, welcoming space for collaboration, and contributors are expected to adhere to the [Contributor Covenant](http://contributor-covenant.org) code of conduct.

## License

The gem is available as open source under the terms of the [MIT License](https://opensource.org/licenses/MIT).

The [GLFW API](http://www.glfw.org) is is licensed under the [zlib/libpng](http://www.glfw.org/license.html) license.

## Code of Conduct

Everyone interacting in the GLFW project’s codebases, issue trackers, chat rooms and mailing lists is expected to follow the [code of conduct](https://github.com/ForeverZer0/glfw/blob/master/CODE_OF_CONDUCT.md).
