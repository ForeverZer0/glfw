
module GLFW

  ##
  # Provides methods for interacting and querying joystick and gamepad peripherals.
  module Joystick

    ##
    # Retrieves the state of the specified joystick remapped to an Xbox-like gamepad.
    #
    # @param jid [Integer] The joystick index to query.
    #
    # @return [GamepadState?] the gamepad input state of the joystick or `nil` if an error occurred.
    def self.gamepad_state(jid)
    end

    ##
    # Returns the name, encoded as UTF-8, of the specified joystick. 
    #
    # @param jid [Integer] The joystick index to query.
    #
    # @return [String?] the UTF-8 encoded name of the gamepad, or `nil` if the joystick is not present, does not
    #   have a mapping or an error occurred.
    def self.name(jid)
    end

    ##
    # Returns the human-readable name of the gamepad from the gamepad mapping assigned to the specified joystick.
    #
    # @param jid [Integer] The joystick index to query.
    #
    # @return [String?] the UTF-8 encoded name of the gamepad, or `nil` if the joystick is not present, does not
    #   have a mapping or an error occurred.
    def self.gamepad_name(jid)
    end

    ##
    # Returns whether the specified joystick is present.
    #
    # @param jid [Integer] The joystick index to query.
    # @return [Boolean] `true` if joystick is detected, otherwise `false`.
    # @note There is no need to call this function before other functions that accept a joystick ID, as they all check
    #   for presence before performing any other work.
    def self.present?(jid)
    end

    ##
    # Returns whether the specified joystick is both present and has a gamepad mapping.
    #
    # @param jid [Integer] The joystick index to query.
    #
    # @return [Boolean] `true` if joystick is detected and it has gamepad mappings, otherwise `false`
    def self.gamepad?(jid)
    end

    ##
    # Returns the SDL compatible GUID, as a UTF-8 encoded hexadecimal string, of the specified joystick
    # The GUID is what connects a joystick to a gamepad mapping. A connected joystick will always have a
    # GUID even if there is no gamepad mapping assigned to it.
    #
    # @param jid [Integer] The joystick index to query.
    #
    # @return [String?] The UTF-8 encoded GUID of the joystick, or `nil` if the joystick is not present or an error occurred.
    def self.guid(jid)
    end

    ##
    # Returns the state of all buttons of the specified joystick.
    #
    # @param jid [Integer] The joystick index to query.
    #
    # @return [Array<Boolean>] an array where each element represents the joystick button at the same index, whose value
    #   if either `true` (pressed) or `false` (released).
    def self.buttons(jid)
    end

    ##
    # Returns the values of all axes of the specified joystick. Each element in the array is a value between
    # `-1.0` and `1.0`.
    #
    # @param jid [Integer] The joystick index to query.
    #
    # @return [Array<Float>] an array where each element represents the joystick axis at the same index
    def self.axes(jid)
    end

    ##
    # Returns the state of all hats of the specified joystick.
    #
    # @param jid [Integer] The joystick index to query.
    #
    # @return [Array<Boolean>] an array where each element represents the joystick hats at the same index, whose value
    #   if either `true` (pressed) or `false` (released).
    def self.hats(jid)
    end

    ##
    # Parses the specified ASCII encoded string(s) and updates the internal list with any gamepad mappings it finds.
    # This string may contain either a single gamepad mapping or many mappings separated by newlines. 
    #
    # If there is already a gamepad mapping for a given GUID in the internal list, it will be replaced by the one
    # passed to this function. If the library is terminated and re-initialized the internal list will revert to the
    # built-in default.
    #
    # @note The parser supports standard SDL gamepad mappings.
    #
    # @param mapping [String,Array<String>] One or more mappings to update.
    #
    # @return [Integer] the number of mappings that were updated.
    def self.update_mappings(*mapping)
    end

    ##
    # @overload self.on_connection(&block)
    #   When called with a block, sets a callback to be invoked when the connection state of a joystick is changed.
    #   @yieldparam connected [Boolean] `true` if device was connected, otherwise `false` if disconectted.
    #
    # @overload self.on_connection
    #   When called without a block, clears any callback that is set.
    #
    # @return [Proc?] the previous callback that was set, or `nil` if none existed.
    def self.on_connection
    end
  end
end