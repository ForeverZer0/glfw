require_relative 'gl'

module GL

  #noinspection SpellCheckingInspection
  class Shader

    class CompileError < GL::Error
    end

    class LinkError < GL::Error
    end

    include GL
    include Fiddle

    attr_reader :id

    def initialize(vertex, fragment, geometry = nil)

      raise ArgumentError, 'vertex source cannot be nil' unless vertex
      raise ArgumentError, 'fragment source cannot be nil' unless fragment

      @id = glCreateProgram
      v = compile_and_attach(@id, vertex, GL_VERTEX_SHADER)
      f = compile_and_attach(@id, fragment, GL_FRAGMENT_SHADER)
      g = compile_and_attach(@id, geometry, GL_GEOMETRY_SHADER)

      glLinkProgram(@id)

      detach_and_delete(@id, v)
      detach_and_delete(@id, f)
      detach_and_delete(@id, g)

      check_link_status
    end

    def use
      glUseProgram(@id)
    end

    private

    def check_link_status

      int = "\0" * SIZEOF_INT
      glGetProgramiv(id, GL_LINK_STATUS, int)

      if int.unpack1('L') != GL_TRUE

        glGetProgramiv(id, GL_INFO_LOG_LENGTH, int)
        len = int.unpack1('L')
        buffer = "\0" * len
        glGetProgramInfoLog(id, len, int, buffer)
        raise LinkError, buffer
      end
    end

    def compile_and_attach(program, src, type)
      return 0 if program.zero? || src.nil?

      id = glCreateShader(type)

      len = [src.bytesize].pack('L')
      ptr = Pointer.to_ptr(src)
      glShaderSource(id, 1, ptr.ref, len)
      glCompileShader(id)

      int = "\0" * SIZEOF_INT
      glGetShaderiv(id, GL_COMPILE_STATUS, int)

      if int.unpack1('L') != GL_TRUE
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, int)
        len = int.unpack1('L')
        buffer = "\0" * len
        glGetShaderInfoLog(id, len, int, buffer)
        raise CompileError, buffer
      end

      glAttachShader(program, id)
      id
    end

    def detach_and_delete(program, shader)
      return if program.zero? || shader.zero?

      glDetachShader(program, shader)
      glDeleteShader(shader)
    end
  end

end