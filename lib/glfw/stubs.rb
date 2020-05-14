
require_relative 'stubs/window'
require_relative 'stubs/image'
require_relative 'stubs/gamepad_state'
require_relative 'stubs/cursor'
require_relative 'stubs/joystick'
require_relative 'stubs/monitor'
require_relative 'stubs/video_mode'

module GLFW

  class << self

    ##
    # Initializes the GLFW library. This method must be called before attempting to use any other feature, or
    # after a call to {terminate} was made.
    # 
    # @overload init
    #   When called without a block, returns a value indicating if library initialized successfully.
    #   @return [Boolean] `true` if library initialized successfully, otherwise `false`.
    #   @note Calling this method while library is already initialized is a no-op and returns `true` immediately.
    # @overload init(&block)
    #   When called with a block, yields and automatically calls {terminate} when the block exits.
    #   @return [void]
    #   
    # @see terminate
    # @see 
    def init
    end

    ##
    # Destroys the all windows, their contexts, cursors, etc., restoring the library to an uninitialized state.
    #
    # @return [void]
    # @see init
    def terminate
    end

    ##
    # Sets hints that affect how the library behaves until termination.
    #
    # @param hint [Integer] A value indicating the hint to change.
    # @param value [Integer,Boolean,String] The desired value to set for this hint.  
    #
    # @return [void]
    # @see JOYSTICK_HAT_BUTTONS
    # @see COCOA_CHDIR_RESOURCES
    # @see COCOA_MENUBAR
    def init_hint(hint, value)
    end

    ##
    # Returns whether the specified API extension is supported by the current OpenGL or OpenGL ES context. It searches
    # both for client API extension and context creation API extensions.
    #
    # A context must be current on the calling thread.
    #
    # @param extenion_name [String] The name of an extension to query.
    # @return [Boolean] `true` if extension is supported, otherwise `false`.
    def supported?(extension_name)
    end
    
    ##
    # This function sets the swap interval for the current OpenGL or OpenGL ES context, i.e. the number of
    # screen updates to wait from the time {Window.swap_buffers} was called before swapping the buffers and
    # returning. This is sometimes called vertical synchronization, vertical retrace synchronization or just vsync.
    #
    # @param interval [Integer] The minimum number of screen updates to wait for until the buffers are swapped by {Window.swap_buffers}
    #
    # @return [void] 
    def swap_interval(interval)
    end

    ##
    # Processes only those events that are already in the event queue and then returns immediately.
    # Processing events will cause the window and input callbacks associated with those events to be called.
    # @return [void]
    def poll_events
    end

    ##
    # puts the calling thread to sleep until at least one event is available in the event queue. 
    # Once one or more events are available, it behaves exactly like {poll_events}.
    # @return [void]
    def wait_events
    end

    ##
    # Posts an empty event from the current thread to the event queue, causing {Wait_vents} or {events_timeout} to return.
    # @return [void]
    def post_empty_event
    end

    ##
    # Puts the calling thread to sleep until at least one event is available in the event queue, or until the specified
    # timeout is reached. If one or more events are available, it behaves exactly like {poll_events}.
    # @return [void]
    def event_timeout(timeout)
    end

    ##
    # Returns a function pointer for the specified OpenGL function, as a [Fiddle::Pointer](https://ruby-doc.org/stdlib-2.5.3/libdoc/fiddle/rdoc/Fiddle/Pointer.html).
    #
    # @param name [String] The name of an OpenGL function.
    #
    # @return [Fiddle::Pointer] a function pointer.
    def proc_address(name)
    end

    ##
    # Convenience method for importing OpenGL functions using Fiddle (standard library since Ruby 1.9)
    #
    # @param name [String] The name of an OpenGL function.
    # @param args [Array<Integer>] An array describing the argument prototypes, same as when creating a [Fiddle::Function](https://ruby-doc.org/stdlib-2.5.3/libdoc/fiddle/rdoc/Fiddle/Function.html#method-c-new).
    # @param return_type [Integer] A value describing the argument prototypes, same as when creating a [Fiddle::Function](https://ruby-doc.org/stdlib-2.5.3/libdoc/fiddle/rdoc/Fiddle/Function.html#method-c-new).
    #
    # @return [Fiddle::Function]
    # @see https://ruby-doc.org/stdlib-2.5.3/libdoc/fiddle/rdoc/Fiddle/Function.html
    def import(name, args, return_type)
    end

    ##
    # Returns the name of the specified printable key, encoded as UTF-8. This is typically the character that key
    # would produce without any modifier keys, intended for displaying key bindings to the user. For dead keys, it
    # is typically the diacritic it would add to a character.
    #
    # @param key [Integer] The key to query.
    # @param scancode [Integer] The scancode of the key to query.
    #
    # @note When `scancode` is specified, the `key` argument is ignored.
    #
    # @return [String?] The UTF-8 encoded, layout-specific name of the key, or `nil`.
    def key_name(key, scancode = 0)
    end

    ##
    # returns the platform-specific scancode of the specified key.
    #
    # @param key [Integer] The key to query.
    #
    # @return [Integer] the platform-specific scancode for the key, or `-1` if an error occurred.
    def scancode(key)
    end

    ##
    # @return [String] the version of the native GLFW library, in "MAJOR.MINOR.REVISION" format.
    attr_reader :version

    ##
    # @return [String] a version string, including information such as driver version, etc.
    attr_reader :version_str

    ##
    # @return [Integer] the current value of the raw timer, measured in 1 / {timer_frequency) seconds. 
    attr_reader :timer_value

    ##
    # @return [Integer] the frequency, in Hz, of the raw timer.
    attr_reader :timer_frequency

    ##
    # The current time measured by GLFW, in seconds. 
    # Unless the time has been set using glfwSetTime it measures time elapsed since GLFW was initialized.
    # 
    # The resolution of the timer is system dependent, but is usually on the order of a few micro- or nanoseconds.
    # It uses the highest-resolution monotonic time source on each supported platform.
    #
    # @return [Float] the current GLFW time, in seconds.
    attr_accessor :time
  end


  ##
  # Descibes the location of an object in 2D space.
  class Point

    ##
    # @return [Integer] the position on the x-axis.
    attr_accessor :x

    ##
    # @return [Integer] the position on the y-axis.
    attr_accessor :y

    ##
    # Creates a new instance of the {Point} class.
    # @param x [Integer] The position on the x-axis.
    # @param y [Integer] The position on the y-axis.
    def initialize(x, y)
    end
  end

  ##
  # Describes the dimensions of an object in 2D space.
  class Size

    ##
    # @return [Integer] the dimension on the x-axis.
    attr_accessor :width

    ##
    # @return [Integer] the dimension on the y-axis.
    attr_accessor :height

    ##
    # Creates a new instance of the {Size} class.
    # @param width [Integer] The dimension on the x-axis.
    # @param height [Integer] The dimension on the y-axis.
    def initialize(width, height)
    end
  end
end