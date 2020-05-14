
module GLFW

  ##
  # Describes the application's mouse cursor object and how it appears for the window.
  class Cursor

    ##
    # @overload initialize(shape)
    #   Creates a new cursor using a standard shape defined by the operating system.
    #   @param shape [Integer] An integer representing the shape of the cursor to create.
    #
    # @overload initialize(image, xhot = 0, yhot = 0)
    #   Creates a new cursor using the specified image.
    #   @param image [Image] A source image to use for the cursor's appearance.
    #   @param xhot [Integer] The "hot-point" of the cursor on the x-axis, where 0 is the left edge of the image.
    #   @param yhot [Integer] The "hot-point" of the cursor on the y-axis, where 0 is the top edge of the image.
    def initialize(*argv)
    end
  end
end