#include "GLErrorHandler.h"

void GLErrorHandler::ClearErrors()
{
	while(glGetError() != GL_NO_ERROR);
}

bool GLErrorHandler::CheckErrors()
{
	auto err = glGetError();
	const bool result = err == GL_NO_ERROR;
	
	while(err != GL_NO_ERROR)
	{
		std::cout << err << std::endl;
		err = glGetError();
	}
	
	return result;
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
