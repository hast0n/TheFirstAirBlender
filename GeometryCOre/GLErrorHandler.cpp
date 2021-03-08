#include "GLErrorHandler.h"

// specific to MSVC
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLErrorHandler::ClearErrors();\
	x;\
	ASSERT(GLErrorHandler::CheckErrors())

void GLErrorHandler::ClearErrors()
{
	while(glGetError() != GL_NO_ERROR);
}
//
//void GLErrorHandler::CheckErrors( GLenum source,
//                 GLenum type,
//                 GLuint id,
//                 GLenum severity,
//                 GLsizei length,
//                 const GLchar* message,
//                 const void* userParam )
//{
//	fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
//           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
//            type, severity, message );
//}
