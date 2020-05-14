
module GLFW

  ##
  # Object describing a raw image with uncompressed pixel data, with 32-bytes per pixel in RGBA byte order. 
  #
  # This class may also be used for creating textures with OpenGL, simply use `GL_RGBA` as the pixel format
  # and pass the value of the {pixels} method.
  class Image

    ##
    # @return [Integer] the width of the image, in pixel units.
    attr_reader :width

    ##
    # @return [Integer] the height of the image, in pixel units.
    attr_reader :height

    ##
    # @overload initialize(width, height, pixels = nil)
    #   Creates a new image of the specified size.
    #   @param width [Integer] The width of the image, in pixel units.
    #   @param height [Integer] The height of the image, in pixel units.
    #   @param pixels [String?] A string buffer containing the uncompressed pixel data.
    # @overload initialize(filename)
    #   Creates a new image from the specified file.
    #   @param filename [String] The path to an image file to load.
    def initialize(*args)
    end

    ##
    # Gets the pixel data as a binary blob.
    #
    # @return [String] the pixel data.
    def pixels
    end

    alias_method :columns, :width
    alias_method :rows, :height
    alias_method :to_blob, :pixels
  end

end