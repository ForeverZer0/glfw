
require_relative 'stubs/window'
require_relative 'stubs/image'
require_relative 'stubs/gamepad_state'
require_relative 'stubs/cursor'

module GLFW

  class << self

    ##
    # Initializes the GLFW library. This method must be called before attempting to use any other feature, or
    # after a call to {terminate} was made.
    # 
    # @note Calling this method while library is already initialized is a no-op and returns `true` immediately.
    # @return [Boolean] `true` if library initialized successfully, otherwise `false`.
    # @see terminate
    def init
    end

    ##
    # Destroys the all windows, their contexts, cursors, etc., restoring the library to an uninitialized state.
    #
    # @return [void]
    # @see init
    def terminate
    end

    def init_hint(hint, value)
    end

    def supported?(extension_name)
    end
    
    def swap_interval(interval)
    end

    def poll_events
    end

    def wait_events
    end

    def post_empty_event
    end

    def event_timeout(timeout)
    end

    def proc_address(name)
    end

    def import(name, args, return_type)
    end

    def key_name(key, scancode = 0)
    end

    def scancode(key)
    end

    attr_reader :version
    attr_reader :version_str
    attr_reader :timer_value
    attr_reader :timer_frequency

  
    attr_accessor :time
  end



  ##
  # Provides methods for interacting and querying joystick and gamepad peripherals.
  module Joystick

    def self.gamepad_state(jid)
    end

    def self.name(jid)
    end

    def self.gamepad_name(jid)
    end

    def self.present?(jid)
    end

    def self.gamepad?(jid)
    end

    def self.guid(jid)
    end

    def self.buttons(jid)
    end

    def self.axes(jid)
    end

    def self.hats(jid)
    end

    def self.update_mappings(*mapping)
    end

    ##
    # @overload self.on_connection(&block)
    #
    # @overload self.on_connection
    #
    #
    def self.on_connection
    end

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