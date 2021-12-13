#pragma once

#include <glad/glad.h>

class VBO {
public:
	// reference to the VBO
	GLuint VBOReferenceID;

	// constructor that takes a VBO and links it to the verticies
	VBO(GLfloat* verticies, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};