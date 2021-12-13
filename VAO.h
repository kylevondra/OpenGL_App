#include <glad/glad.h>
#include "VBO.h"

class VAO {
public:
	// reference to the VAO
	GLuint VAOReferenceID;
	VAO();

	/// <summary>
	/// Tells OpenGL information about each vertex array object so the info can be passed through the rendering pipeline to the shader
	/// </summary>
	/// <param name="VBO">- The VBO it is bound to</param>
	/// <param name="layout">- Tells OpenGL which layout "block" to start at for the attribute</param>
	/// <param name="numComponents">- the number of components per block</param>
	/// <param name="type">- the data type of the block</param>
	/// <param name="stride">- how far OpenGL must travel to get to the next vertex</param>
	/// <param name="offset">- the offset from the beginning of the block OpenGL must go to find this attribute</param>
	void linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

	void Bind();
	void Unbind();
	void Delete();
};