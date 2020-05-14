
require_relative '../lib/glfw'
require_relative 'gl'
require_relative 'shader'

class MyGame < GLFW::Window

  include GL
  include Fiddle
  include GLFW

  def initialize(width, height, title)

    Window.default_hints
    Window.hint(HINT_CLIENT_API, API_OPENGL)
    Window.hint(HINT_OPENGL_PROFILE, PROFILE_OPENGL_CORE)
    Window.hint(HINT_CONTEXT_VERSION_MAJOR, 3)
    Window.hint(HINT_CONTEXT_VERSION_MINOR, 3)
    Window.hint(HINT_DOUBLEBUFFER, true)
    Window.hint(HINT_OPENGL_FORWARD_COMPAT, true)
    Window.hint(HINT_DECORATED, true)
    Window.hint(HINT_RESIZABLE, true)
    Window.hint(HINT_VISIBLE, false)

    super(width, height, title, vsync: true)

    self.icon = Image.new('../glfw-icon.png')
    setup(width, height)
    set_callbacks
  end

  def set_callbacks
    # Update the viewport when the framebuffer size changes
    on_framebuffer_resize do |width, height|
      glViewport(0, 0, width, height)
    end

    # Cleanup when window is closing
    on_close do
      glDeleteProgram(@shader.id)
      glDeleteVertexArrays(1, [@vao].pack('L'))
      glDeleteBuffers(1, [@vbo].pack('L'))
    end
  end

  def setup(width, height)
    make_current
    GL.import_functions

    create_shader
    create_vertex_array

    glViewport(0, 0, width, height)
    glClearColor(0.1, 0.1, 0.2, 1.0)
  end

  def create_shader

    vertex = <<-EOS
    #version 330 core
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 color;
      
    out vec3 out_color;
    
    void main()
    {
        gl_Position = vec4(position, 1.0);
        out_color = color;
    }
    EOS
    fragment = <<-EOS
    #version 330 core
  
    in vec3 out_color;
    out vec4 fragment;
    
    void main()
    {
        fragment = vec4(out_color, 1.0f);
    } 
    EOS

    @shader = Shader.new(vertex, fragment)
    @shader.use
  end

  def create_vertex_array

    vertices = [
        0.5, -0.5, 0.0,  1.0, 0.0, 0.0,
    -0.5, -0.5, 0.0,  0.0, 1.0, 0.0,
    0.0,  0.5, 0.0,  0.0, 0.0, 1.0
    ]

    ptr = "\0" * SIZEOF_INT
    glGenVertexArrays(1, ptr)
    @vao = ptr.unpack1('L')

    glGenBuffers(1, ptr)
    @vbo = ptr.unpack1('L')

    glBindVertexArray(@vao)

    glBindBuffer(GL_ARRAY_BUFFER, @vbo)
    glBufferData(GL_ARRAY_BUFFER, vertices.size * SIZEOF_FLOAT, vertices.pack('f*'), GL_STATIC_DRAW)
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * SIZEOF_FLOAT, nil)
    glEnableVertexAttribArray(0)

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * SIZEOF_FLOAT, 3 * SIZEOF_FLOAT)
    glEnableVertexAttribArray(1)
  end

  def main

    show
    until closing?
      render
      GLFW.poll_events
    end
  end

  def render
    glClear(GL_COLOR_BUFFER_BIT)

    glBindVertexArray(@vao)
    glDrawArrays(GL_TRIANGLES, 0, 3)


    swap_buffers
  end
end


GLFW.init

game = MyGame.new(1024, 768, 'Hello Triangle!')
game.main

GLFW.terminate