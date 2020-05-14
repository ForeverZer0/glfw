
module GLFW

    ##
  # Describes the captured state of a gamepad.
  class GamepadState

    ##
    # Queries the value of the axis at the specified index.
    # 
    # @param index [Integer] The desired index of the axis to query.
    #
    # @return [Float] The current axis value, or `0.0` if out of range.
    # @note It is recommended to use the return value rounded to a specific precision, or "dead zone", as many devices
    #   will report miniscule values even when stationary.
    # @note Use the class constants prefixed with `AXIS` for strongly typed index values if desired.
    def axis(index)
    end

    ##
    # Queries the button state at the specified index.
    #
    # @param index [Integer] The desired index of the button to query.
    #
    # @return [Float] `true` if button is depressed, otherwise `false` if no input is detected or if index is out of range.
    # @note Use the class constants prefixed with `BUTTON` for strongly typed index values if desired.
    def button(index)
    end
  end

end