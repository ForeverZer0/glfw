
module GLFW

  ##
  # Represents a handle to a physical monitor.
  class Monitor

    ##
    # Retrieves an array of all connected monitors.
    # @return [Array<Monitor>] an array of monitors.
    # @see primary
    def self.available
    end

    ##
    # @return [Monitor] the primary or "default" monitor.
    # @see available
    def self.primary
    end

    ##
    # @overload self.on_connection(&block)
    #   When called with a block, sets a callback to be invoked when the connection
    #   state of a monitor is changed.
    #   @yieldparam connected [Boolean] `true` if device was connected, otherwise `false` if disconectted.
    #
    # @overload self.on_connection
    #   When called without a block, clears any callback that is set.
    #
    # @return [Proc?] the previous callback that was set, or `nil` if none existed.
    def self.on_connection
    end

    ##
    # Generates an appropriately sized gamma ramp from the specified exponent and
    # then sets the {gamme_ramp} with it. The value must be a finite number greater
    # than zero.
    #
    # The software controlled gamma ramp is applied in addition to the hardware gamma
    # correction, which today is usually an approximation of sRGB gamma. This means
    # that setting a perfectly linear ramp, or gamma 1.0, will produce the default
    # (usually sRGB-like) behavior.
    #
    # @param [Float] the desired exponent value, must be greater than `0.0` and finite.
    #
    # @return [void]
    def gamma(exponent)
    end

    ##
    # Sets teh gamma ramp of the monitor. The ramp is an array of 3 equally sized
    # arrays of integers that range from `0` to `65535`. Each child array represents
    # the ramp for a single color component, in RGB order.
    #
    # @note It is strongly recommended to use {gamma} instead of this method.
    # @note On Windows, the maximum size of a gamma ramp is 256.
    #
    # @return [Array<Array<Integer>, Array<Integer> Array<Integer>>] the gamma ramp.
    attr_accessor :gamma_ramp

    ##
    # The human-readable name of the specified monitor. The name typically reflects
    # the make and model of the monitor and is not guaranteed to be unique among the
    # connected monitors.
    # @return [String] the monitor name.
    attr_reader :name

    ##
    # @return [Size] the physical dimensions of the monitor, in millimeter units.
    attr_reader :physical_size

    ##
    # @return [Size] the dimensions of the monitor, in screen coordinates.
    attr_reader :size

    ##
    # The position, in screen coordinates, of the upper-left corner of the work area.
    # The work area is defined as the area of the monitor not occluded by the operating
    # system task bar where present. If no task bar exists then the work area is the
    # monitor resolution in screen coordinates.
    # @return [Point] the location of the monitor's work area.
    attr_reader :client_position

    ##
    # The size of the "non-system" area of the monitor, in screen coordinates.
    # The work area is defined as the area of the monitor not occluded by the operating
    # system task bar where present. If no task bar exists then the work area is the
    # monitor resolution in screen coordinates.
    # @return [Size] the size of the monitor's work area.
    attr_reader :client_size

    ##
    # @return [VideoMode] the current video mode for the monitor.
    attr_reader :video_mode

    ##
    # @return [Array<VideoMode>] an array of all video modes available to the monitor.
    attr_reader :video_modes

    ##
    # etrieves the content scale for the specified monitor. The content scale is the ratio
    # between the current DPI and the platform's default DPI. This is especially important
    # for text and any UI elements. If the pixel dimensions of your UI scaled by this look
    # appropriate on your machine then it should appear at a reasonable size on other machines
    # regardless of their DPI and scaling settings. This relies on the system DPI and scaling
    # settings being somewhat correct.
    #
    # The content scale may depend on both the monitor resolution and pixel density and on user
    # settings. It may be very different from the raw DPI calculated from the physical size and
    # current resolution.
    #
    # @return [Vector2] the current content scale of the monitor.
    attr_reader :content_scale
  end
end