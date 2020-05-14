
module GLFW

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