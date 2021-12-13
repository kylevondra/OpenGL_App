#include"EBO.h"

// Constructor that generates an element buffer object and links it to the indices
EBO::EBO(GLuint* indices, GLsizeiptr size) {
	glGenBuffers(1, &ID); // generates a buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); // binds it to the context
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW); // gives the buffer its data
}

// Binds the EBO
void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbinds the EBO
void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO
void EBO::Delete() {
	glDeleteBuffers(1, &ID);
}