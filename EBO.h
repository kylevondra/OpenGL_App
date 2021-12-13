#pragma once

#include<glad/glad.h>

class EBO {
public:
	// ID reference of the element buffer object
	GLuint ID;

	// Constructor that generates an EBO and links it to the indices
	EBO(GLuint* indices, GLsizeiptr size);

	// Binds the EBO
	void Bind();
	// Unbinds the EBO
	void Unbind();
	// Deletes the EBO
	void Delete();
};

