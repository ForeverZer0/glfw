
module GLFW

  ##
  # Describes the video settings for a {Monitor}.
  class VideoMode

    ##
    # @return [Integer] the width, in screen coordinates, of the video mode.
    attr_reader :width

    ##
    # @return [Integer] the height, in screen coordinates, of the video mode.
    attr_reader :height

    ##
    # @return [Integer] the bit depth of the red channel of the video mode.
    attr_reader :red_bits

    ##
    # @return [Integer] the bit depth of the green channel of the video mode.
    attr_reader :green_bits

    ##
    # @return [Integer] the bit depth of the blue channel of the video mode.
    attr_reader :blue_bits

    ##
    # @return [Integer] the refresh rate, in Hz, of the video mode.
    attr_reader :refresh_rate
  end
end