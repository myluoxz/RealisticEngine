#include "RealisticEngine/Renderer/Asset.h"
#include "RealisticEngine/Renderer/GPURenderer.h"


using namespace RealisticEngine::Renderer;







UniformVariable::UniformVariable(std::string name, UniformType type, GLsizei count)
{
  mType = type;
  mName = name;
  mCount = count;
}


void UniformVariable::Setup(std::string name, UniformType type, GLsizei count)
{
  mName = name;
  mType = type;
  mCount = count;
}

void UniformVariable::Bind()
{
  GLint loc = glGetUniformLocation(mRenderer->GetActiveShader()->GetProgramID(), mName.data());
  if(loc < 0)
  {
    return;
  }


  switch(mType)
  {
    case INT:
    {
      GLint* data = (GLint*)mData;
      glUniform1i(loc, data[0]);
      break;
    }
    case INTARY:
    {
      GLint* data = (GLint*)mData;
      glUniform1iv(loc, mCount, data);
      break;
    }
    case VEC2I:
    {
      GLint* data = (GLint*)mData;
      glUniform2i(loc, data[0], data[1]);
      break;
    }
    case VEC2IARY:
    {
      GLint* data = (GLint*)mData;
      glUniform2iv(loc, mCount, data);
      break;
    }
    case VEC3I:
    {
      GLint* data = (GLint*)mData;
      glUniform3i(loc, data[0], data[1], data[2]);
      break;
    }
    case VEC3IARY:
    {
      GLint* data = (GLint*)mData;
      glUniform3iv(loc, mCount, data);
      break;
    }
    case VEC4I:
    {
      GLint* data = (GLint*)mData;
      glUniform4i(loc, data[0], data[1], data[2], data[3]);
      break;
    }
    case VEC4IARY:
    {
      GLint* data = (GLint*)mData;
      glUniform4iv(loc, mCount, data);
      break;
    }
    case FLOAT:
    {
      GLfloat* data = (GLfloat*)mData;
      glUniform1f(loc, data[0]);
      break;
    }
    case FLOATARY:
    {
      GLfloat* data = (GLfloat*)mData;
      glUniform1fv(loc, mCount, data);
      break;
    }
    case VEC2F:
    {
      GLfloat* data = (GLfloat*)mData;
      glUniform2f(loc, data[0], data[1]);
      break;
    }
    case VEC2FARY:
    {
      GLfloat* data = (GLfloat*)mData;
      glUniform2fv(loc, mCount, data);
      break;
    }
    case VEC3F:
    {
      GLfloat* data = (GLfloat*)mData;
      glUniform3f(loc, data[0], data[1], data[2]);
      break;
    }
    case VEC3FARY:
    {
      GLfloat* data = (GLfloat*)mData;
      glUniform3fv(loc, mCount, data);
      break;
    }
    case VEC4F:
    {
      GLfloat* data = (GLfloat*)mData;
      glUniform4f(loc, data[0], data[1], data[2], data[3]);
      break;
    }
    case VEC4FARY:
    {
      GLfloat* data = (GLfloat*)mData;
      glUniform4fv(loc, mCount, data);
      break;
    }
    case MAT2F:
    {
      GLfloat* data = (GLfloat*)mData;
      glUniformMatrix2fv(loc, mCount, false, data);
      break;
    }
    case MAT3F:
    {
      GLfloat* data = (GLfloat*)mData;
      glUniformMatrix3fv(loc, mCount, false, data);
      break;
    }
    case MAT4F:
    {
      GLfloat* data = (GLfloat*)mData;
      glUniformMatrix4fv(loc, mCount, false, data);
      break;
    }

    default:
      break;
  }
}

void UniformVariable::BindData(void* data)
{
  mData = data;
}

void UniformVariable::BindActiveShader(GPURenderer *renderer)
{
  mRenderer = renderer;
}

void Texture::Setup(void *data, GLuint width, GLuint height, GLenum texunit, GLenum format, GLenum pixletype)
{
  mData = data;
  mWidth = width;
  mHeight = height;
  mTexUnit = texunit;
  mFormat = format;
  mPixleType = pixletype;
}

void Texture::Load()
{
  glGenTextures(1, &mTexid);
  glBindTexture(GL_TEXTURE_2D,mTexid);
  glTexImage2D(GL_TEXTURE_2D, 0, mFormat, mWidth,mHeight, 0, mFormat, mPixleType, mData);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind()
{
  glActiveTexture(mTexUnit);

  glBindTexture(GL_TEXTURE_2D, mTexid);

}

void Texture::UnBind()
{
  glBindTexture(GL_TEXTURE_2D, 0);
}