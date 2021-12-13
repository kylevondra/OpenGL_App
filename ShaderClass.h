#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader {
public:
	// reference to a shader program as an int (because pointers/references are just ints to a memory location)
	GLuint shaderProgramID;
	Shader(const char* vertexFile, const char* fragmentFile);
	
	void Activate();
	void Delete();

private:
	// checks if the shaders have compiled correctly
	void compileErrors(unsigned int shader, const char* type);
};