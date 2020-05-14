
module GLFW

  ##
  # Object describing a raw image with uncompressed pixel data, with 32-bytes per pixel in RGBA byte order. 
  class Image

    ##
    # @return [Integer] the width of the image, in pixel units.
    attr_reader :width

    ##
    # @return [Integer] the height of the image, in pixel units.
    attr_reader :height

    ##
    # @overload initialize(width, height, pixels = nil)
    #
    # @overload initialize(filename)
    #
    def initialize(width, height, pixels)
    end

    ##
    # Gets the pixel data as a binary blob.
    # @return [String] the pixel data.
    def pixels
    end

    alias_method :columns, :width
    alias_method :rows, :height
    alias_method :to_blob, :pixels
  end

end