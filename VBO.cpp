#include "VBO.h"

// constructor generates a VBO and links it to the verticies
VBO::VBO(GLfloat* verticies, GLsizeiptr size) {
	glGenBuffers(1, &VBOReferenceID); // generates a buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBOReferenceID); // binds it to the current context
	glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW); // gives it its data
}

void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, VBOReferenceID);
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
}

void VBO::Delete() {
	glDeleteBuffers(1, &VBOReferenceID);
}