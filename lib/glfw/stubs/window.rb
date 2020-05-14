
module GLFW

  ##
  # Represents an application window and OpenGL context.
  class Window

    ##
    # Resets all window hints that have been applied back to the "default" configuration.
    # @return [void]
    def self.default_hints
    end

    ##
    # Sets a hint for the next window creation. Once set, the value will persist until changed with this function
    # or the library is terminated.
    #
    # @param hint [Integer] A value indicating the hint to change. See the GLFW constants prefixed with `HINT`
    #   for valid values for this parameter.
    # @param value [Integer,Boolean,String] The desired value to set for this hint.  
    # 
    # @return [void]
    def self.hint(hint, value)
    end

    ##
    # @return [Window?] the {Window} whose context is current on the calling thread, or `nil` if none is found.
    def self.current
    end

    ##
    # Creates a new instance of the {Window} class.
    #
    # @param width [Integer] The desired width of the window, in screen coordinates.
    # @param height [Integer] The desired height of the window, in screen coordinates.
    # @param title [String?] The caption to display in the system menubar, window titlebar, etc.
    # @param opts [Hash] The options hash.
    # 
    # @option opts [Boolean] :center (true) `true` to have window initially centered on screen.
    # @option opts [Boolean] :vsync (true) `true` to enable vertical syncronization with the monitor refresh.
    # @option opts [Monitor] :monitor (nil) Specifies a monitor to create the window on.
    # @option opts [Window] :shared (nil) Specified another window instance to share context resources with.
    # @option opts [Boolean] :full_window (false) Initializes window as "borderless fullscreen", which allows faster context switching.
    # @option opts [Boolean] :fullscreen (false) Initializes window as fullscreen.
    #
    # @note The OpenGL coontext will automatically be made current on the thread for the new window.
    def initialize(width, height, title = nil, **opts)
    end

    ##
    # Destroys the window, reclaiming any resources it is using and invalidating it for further use.
    # @return [void]
    def destroy
    end

    alias_method :dispose, :destroy

    ##
    # Sets the OpenGL context of the window as current on the calling thread.
    # @return [self]
    # @see current?
    def make_current
    end

    ##
    # Returns value indicating if the OpenGL context of this window is current on the calling thread.
    # @return [Boolean] `true` if context is current, otherwise `false`.
    # @see make_current
    def current?
    end

    ##
    # Returns value indicating if the window currently contains the operating system input focus.
    # @return [Boolean] `true` if window has input focus, otherwise `false`.
    def focused?
    end

    ##
    # Returns value indicating if window is currently minimized to the system toolbar.
    # @return [Boolean] `true` if window is minimized, otherwsie `false`.
    def minimized?
    end

    ##
    # Returns value indicated if window is currently maximized to fill the work area of the monitor.
    # @return [Boolean] `true` if window is maximized, otherwise `false`.
    def maximized?
    end

    ##
    # Returns value indicating if the mouse cursor is currently over thw window's client area.
    # @return [Boolean] `true` if cursor is over the window, otherwise `false`.
    def hovered?
    end

    ##
    # Returns value indicating if window is currently in fullscreen mode on the monitor.
    # @return [Boolean] `true` if window is fullscreen, otherwise `false`.
    def fullscreen?
    end

    ##
    # Modifies the behavior when a user resizes the window to stay locked to the specified aspect ratio.
    #
    # @param numerator [Integer] The numerator component of the aspect ratio.
    # @param denominator [Integer] The denominator component of the aspect ratio.
    #
    # @return [void]
    def aspect_ratio(numerator, denominator)
    end

    ##
    # Sets the minimum and maximum sizes that a user can resize the window to.
    #
    # @param min [Size] The minimum size of the window's client area the user can resize to, in screen coordinates.
    # @param max [Size] The maximum size of the window's client area the user can resize to, in screen coordinates.
    #
    # @return [void]
    def size_limits(min, max)
    end

    ##
    # Retrieves the size, in screen coordinates, of each edge of the frame of the specified window. This size includes the title bar, 
    # if the window has one.
    #
    # @return [Array<Integer>] a 4-element array in the order of left, top, right, bottom, where each value is the size, in
    #   screen coordinates, of the window's frame.
    #
    # @note Values will always be greater than or equal to `0`.
    def frame_size
    end

    ##
    # Moves the mouse cursor to the specified coordinates.
    #
    # @param x [Float] The location to move the cursor to on the x-axis in screen coordinates, relative to the window's client area.
    # @param y [Float] The location to move the cursor to on the y-axis in screen coordinates, relative to the window's client area.
    #
    # @return [void]
    def move_cursor(x, y)
    end

    ##
    # Centers a window on the screen. Has no effect on fullscreen windows.
    # @return [self]
    def center
    end

    ##
    # Sets the closing state of the window.
    # 
    # @param flag [Boolean] `true` to set window state to close, otherwise `false` to cancel a close action that is in progress.
    #
    # @return [self]
    #
    # @see closing?
    # @see on_close
    def close(flag = true)
    end

    ##
    # Retrieves value indicating if window is currently set to close.
    #
    # return [Boolean] `true` if window is set to close, otherwise `false`.
    #
    # @see close
    # @see on_close
    def closing?
    end

    ##
    # Typically called each frame, swaps the front and back buffers used for rendering, presenting the current back buffer to the
    # user, while staging the current front buffer to be overwritten.
    #
    # @return [void]
    def swap_buffers
    end

    ##
    #  Makes the window visible if it was previously hidden.
    #  If the window is already visible or is in full screen mode, this method does nothing.
    #
    # @return [self]
    # @see hide
    def show
    end

    ##
    # Hides the window if it was previously visible.
    # If the window is already hidden or is in full screen mode, this method does nothing.
    #
    # @return [self]
    # @see show
    def hide
    end

    ##
    # Brings the specified window to front and sets input focus. The window should already be visible and not minimized.
    # @return [self]
    def focus
    end

    ##
    # Mminimizes the window if it was previously restored. If the window is already iconified, this function does nothing.
    # If the window is fullscreen, the original monitor resolution is restored until the window is restored.
    #
    # @return [self]
    # @see maximize
    # @see restore
    def minimize
    end

    ##
    # Maximizes the window if it was previously not maximized. If the window is already maximized, this function does nothing.
    # If the window is fullscreen, this function does nothing.
    #
    # @return [self]
    # @see minimize
    # @see restore
    def maximize
    end

    ##
    # Restores the window if it was previously minimized or maximized. If the window is already restored, this function does nothing.
    # If the window is fullscreen, the resolution chosen for the window is restored on the selected monitor.
    #
    # @return [self]
    # @see minimize
    # @see maximize
    def restore
    end

    ##
    # Requests user attention to the window. On platforms where this is not supported, attention is requested to the application as a whole.
    # Once the user has given attention, usually by focusing the window or application, the system will end the request automatically.
    #
    # @return [self]
    def request_attention
    end

    ##
    # Returns the last state reported for the specified key to the window.
    #
    # @param key [Integer] The key to query.
    #
    # @return [Boolean] `true` if key is depressed, otherwise `false`.
    # @see button?
    # @see on_key
    def key?(key)
    end

    ##
    # Returns the last state reported for the specified mouse button to the window.
    #
    # @param key [Integer] The mouse button to query.
    #
    # @return [Boolean] `true` if mouse button is depressed, otherwise `false`.
    # @see key?
    # @see on_mouse_button
    def button?(button)
    end

    ##
    # Ssets the monitor that the window uses for full screen mode or, if the monitor is `nil`,
    # makes it windowed mode.
    #
    # When setting a monitor, this function updates the width, height and refresh rate of the
    # desired video mode and switches to the video mode closest to it. The window position is
    # ignored when setting a monitor.
    #
    # When the monitor is `nil`, the position, width and height are used to place the window
    # content area. The refresh rate is ignored when no monitor is specified.
    #
    # When a window transitions from full screen to windowed mode, this function restores any previous
    # window settings such as whether it is decorated, floating, resizable, has size or aspect
    # ratio limits, etc.
    #
    # @param monitor [Monitor?] The desired monitor, or `nil` to set windowed mode.
    # @param position [Point] The desired location of the upper-left corner of the content area.
    # @param size [Size] The desired size in screen coordinates of the content area or video mode.
    # @param hz [Integer] The desired refresh rate, in Hz, of the video mode, or `-1` to ignore.
    #
    # @return [void]
    def change_monitor(monitor, position, size, hz = -1)
    end

    ##
    # @return [String?] the window caption displayed in the system menubar, window titlebar, etc.
    attr_accessor :title

    ##
    # @return [Boolean] the visibility state of the window.
    attr_accessor :visible

    ##
    # @return [Boolean] `true` if window is floating (always-on-top) of other application windows, otherwise `false`.
    attr_accessor :topmost

    ##
    # The icon(s) to be displayed as a window decoration, on systems that support this functionality.
    # @return [Image, Array<Image>] an image or array of possible images.
    attr_accessor :icon

    ##
    # @return [Point] the position of the top-left corner of the window's client area, in screen coordinates.
    attr_accessor :position

    ##
    # @return [Size] the size of the window's client area, in screen coordinates.
    attr_accessor :size

    ##
    # @return [Cursor?] the mouse cursor the window uses, or `nil` if not specified.
    attr_accessor :cursor

    ##
    # @return [Vector2] the location of the mouse cursor.
    attr_accessor :cursor_pos

    ##
    # @return [Float] a value determining the visibility of the window (including frame), where `0.0` is invisible and `1.0` is fully opaque.
    attr_accessor :opacity

    ##
    # @return [Boolean] a value indicating if the window will be decoarted with a frame, close widget, etc.
    attr_accessor :decorated

    ##
    # @return [Boolean] a value indicating if window is resizable by the user.
    attr_accessor :resizable

    ##
    # @return [String?] a string for the clipboard associated with the window.
    attr_accessor :clipboard

    ##
    # @return [Boolean] a value indicating if window will automatically focus when being restored from minimized state, etc.
    attr_accessor :auto_focus

    ##
    # @return [Integer] a value indicating the behavior of the mouse cursor.
    # @see CURSOR_NORMAL
    # @see CURSOR_HIDDEN
    # @see CURSOR_DISABLED
    attr_accessor :cursor_mode

    ##
    # @return [Boolean] a value indicating if input states for keys will persist until queried with {key?}.
    attr_accessor :sticky_keys

    ##
    # @return [Boolean] a value indicating if input states for mouse buttons will persist until queried with {button?}.
    attr_accessor :sticky_buttons

    ##
    # @return [Boolean] a value indicating if modifier bits for input callback functions will include {MOD_CAPS_LOCK}, {MOD_NUM_LOCK}, etc.
    attr_accessor :lock_modifiers

    ##
    # When the cursor is disabled, raw (unscaled and unaccelerated) mouse motion can be enabled if available.
    #
    # Raw mouse motion is closer to the actual motion of the mouse across a surface. It is not affected by the
    # scaling and acceleration applied to the motion of the desktop cursor. That processing is suitable for a
    # cursor while raw motion is better for controlling for example a 3D camera. Because of this, raw mouse
    # motion is only provided when the cursor is disabled.
    #
    # @return [Boolean] `true` if raw mouse motion is enabled, otherwise `false`.
    attr_accessor :raw_mouse_motion

    ##
    # @return [Monitor?] the monitor the window is displayed on, or `nil` if not a fullscreen window. 
    attr_reader :monitor

    ##
    # @return [Vector2] the current content scale of the window.
    attr_reader :content_scale

    ##
    # @return [Size] the dimensions of the window's primary framebuffer, in pixel coordinates.
    attr_reader :framebuffer_size

    # @!group Callback Functions

    ##
    # @overload on_framebuffer_resize(&block)
    #   When called with a block, sets a callback to be invoked when the window's framebuffer size changes.
    #   @yieldparam width [Integer] The new width of the framebuffer, in pixel units.
    #   @yieldparam height [Integer] The new height of the framebuffer, in pixel units.
    #
    # @overload on_framebuffer_resize
    #   When called without a block, clears any callback that is set.
    #
    # @return [Proc?] the previous callback that was set, or `nil` if none existed.
    # @see framebuffer_size
    def on_framebuffer_resize
    end

    ##
    # @overload on_resize(&block)
    #   When called with a block, sets a callback to be invoked when the window size changes.
    #   @yieldparam width [Integer] The new width of the window's client area, in screen coordinates.
    #   @yieldparam height [Integer] The new height of the window's client area, in screen coordinates.
    #
    # @overload on_resize
    #   When called without a block, clears any callback that is set.
    #
    # @return [Proc?] the previous callback that was set, or `nil` if none existed.
    # @see size
    def on_resize
    end

    ##
    # @overload on_move(&block)
    #   When called with a block, sets a callback to be invoked when the window's position is changed.
    #   @yieldparam x [Integer] The new position of the window on the x-axis, in screen coordinates.
    #   @yieldparam y [Integer] The new position of the window on the y-axis, in screen coordinates.
    #
    # @overload on_move
    #   When called without a block, clears any callback that is set.
    #
    # @return [Proc?] the previous callback that was set, or `nil` if none existed.
    # @see position
    def on_move
    end

    ##
    # @overload on_focus(&block)
    #   When called with a block, sets a callback to be invoked when the window gains or loses input focus.
    #   @yieldparam focused [Boolean] `true` if window has gained focus, otherwise `false` if it was lost.
    #
    # @overload on_focus
    #   When called without a block, clears any callback that is set.
    #
    # @return [Proc?] the previous callback that was set, or `nil` if none existed.
    # @see focus
    # @see focused?
    def on_focus
    end

    ##
    # @overload on_refresh(&block)
    #   When called with a block, sets a callback to be invoked when the content area of the window needs
    #   to be redrawn, for example if the window has been exposed after having been covered by another window.
    #   @yield No arguments are yielded to the block.
    #
    # @overload on_refresh
    #   When called without a block, clears any callback that is set.
    #
    # @note On compositing window systems such as Aero, Compiz, Aqua or Wayland, where the window contents
    #   are saved off-screen, this callback may be called only very infrequently or never at all.
    #
    # @return [Proc?] the previous callback that was set, or `nil` if none existed.
    def on_refresh
    end

    ##
    # @overload on_close(&block)
    #   When called with a block, sets a callback to be invoked when the window is flagged to close.
    #   @yield No arguments are yielded to the block.
    #
    # @overload on_close
    #   When called without a block, clears any callback that is set.
    #
    # @return [Proc?] the previous callback that was set, or `nil` if none existed.
    # @see close
    # @see closing?
    def on_close
    end

    ##
    # @overload on_minimize(&block)
    #   When called with a block, sets a callback to be invoked when the window minimized or restored.
    #   @yieldparam minimized [Boolean] `true` if window has been minimized, otherwise `false` if being restored.
    #
    # @overload on_minimize
    #   When called without a block, clears any callback that is set.
    #
    # @return [Proc?] the previous callback that was set, or `nil` if none existed.
    # @see minimize
    # @see minimized?
    def on_minimize
    end

    ##
    # @overload on_maximize(&block)
    #   When called with a block, sets a callback to be invoked when the window maximized or restored.
    #   @yieldparam maximized [Boolean] `true` if window has been maximized, otherwise `false` if being restored.
    #
    # @overload on_maximize
    #   When called without a block, clears any callback that is set.
    #
    # @return [Proc?] the previous callback that was set, or `nil` if none existed.
    # @see maximize
    # @see maximized?
    def on_maximize
    end

    ##
    # @overload on_file_drop(&block)
    #   When called with a block, sets a callback to be invoked when a files/folders are drag-dropped onto
    #   the windows client area.
    #   @yieldparam paths [Array<String>] An array of the absolite paths of the filepaths that were dropped.
    #
    # @overload on_file_drop
    #   When called without a block, clears any callback that is set.
    #
    # @return [Proc?] the previous callback that was set, or `nil` if none existed.
    def on_file_drop
    end

    ##
    # @overload on_cursor_move(&block)
    #   When called with a block, sets a callback to be invoked when the mouse cursor moves.
    #   @yieldparam x [Float] The new cursor position on the x-axis, in screen coordinates and 
    #     relative to the top-left corner of the window's client area. 
    #   @yieldparam y [Float] The new cursor position on the y-axis, in screen coordinates and
    #     relative to the top-left corner of the window's client area.
    #
    # @overload on_cursor_move
    #   When called without a block, clears any callback that is set.
    #
    # @return [Proc?] the previous callback that was set, or `nil` if none existed.
    # @see cursor_pos
    # @see move_cursor
    def on_cursor_move
    end

    ##
    # @overload on_scroll(&block)
    #   When called with a block, sets a callback to be invoked when the mouse wheel is scrolled.
    #   @yieldparam x [Float] The scroll amount on the x-axis, or `0.0` when not supported.
    #   @yieldparam y [Float] The scroll amount on the y-axis. 
    # 
    # @overload on_scroll
    #   When called without a block, clears any callback that is set.
    #
    # @return [Proc?] the previous callback that was set, or `nil` if none existed.
    def on_scroll
    end

    ##
    # @overload on_key(&block)
    #   When called with a block, sets a callback to be invoked when a key state changes.
    #   @yieldparam key [Integer] The keyboard key that was pressed or released.
    #   @yieldparam scancode [Integer] The system-specific scancode of the key.
    #   @yieldparam action [Integer] A value indicating the state of the key
    #   @yieldparam modifiers [Integer] A bitfield value of modifier keys that were present during the action.
    #   
    # @overload on_key
    #   When called without a block, clears any callback that is set.
    #
    # @return [Proc?] the previous callback that was set, or `nil` if none existed.
    # @see key?
    # @see RELEASE
    # @see PRESS
    # @see REPEAT
    def on_key
    end

    ##
    # @overload on_mouse_button(&block)
    #   When called with a block, sets a callback to be invoked when a mouse button state changes.
    #   @yieldparam button [Integer] The mouse button that was pressed or released.
    #   @yieldparam action [Integer] A value indicating the state of the button.
    #   @yieldparam modifiers [Integer] A bitfield value of modifier keys that were present during the action.
    #
    # @overload on_mouse_button
    #   When called without a block, clears any callback that is set.
    #
    # @return [Proc?] the previous callback that was set, or `nil` if none existed.
    # @see button?
    # @see RELEASE
    # @see PRESS
    # @see REPEAT
    def on_mouse_button
    end

    ##
    # @overload on_cursor_enter(&block)
    #   When called with a block, sets a callback to be invoked when the mouse cursor enters or leaves
    #   the content area of the window.
    #   @yieldparam entered [Booleab] `true` if cursor is entering the window, otherwise `false` when leaving.
    #
    # @overload on_cursor_enter
    #   When called without a block, clears any callback that is set.
    #
    # @return [Proc?] the previous callback that was set, or `nil` if none existed.
    def on_cursor_enter
    end

    ##
    # The character callback is intended for Unicode text input. As it deals with characters, it is keyboard
    # layout dependent, whereas the key callback is not. Characters do not map 1:1 to physical keys, as a key
    # may produce zero, one or more characters. If you want to know whether a specific physical key was pressed
    # or released, see the key callback instead.
    #
    # The character callback behaves as system text input normally does and will not be called if modifier keys
    # are held down that would prevent normal text input on that platform, for example a Super (Command) key on
    # macOS or Alt key on Windows.
    #
    # @overload on_char(&block)
    #   When called with a block, sets a callback to be invoked when a Unicode character is input.
    #   @yieldparam codepoint [Integer] A Unicode codepoint.
    #
    # @overload on_char
    #   When called without a block, clears any callback that is set.
    #
    # @return [Proc?] the previous callback that was set, or `nil` if none existed.
    def on_char
    end

    ##
    # @overload on_scale(&block)
    #   When called with a block, sets a callback to be invoked when the window's content scale is changed.
    #   @yieldparam x [Float] The new content scaling factor on the x-axis.
    #   @yieldparam y [Float] The new content scaling factor on the y-axis.
    #
    # @overload on_scale
    #   When called without a block, clears any callback that is set.
    #
    # @return [Proc?] the previous callback that was set, or `nil` if none existed.
    # @see content_scale
    def on_scale
    end
  end
end