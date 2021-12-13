#include "ShaderClass.h"

// honestly no clue how this works, kinda just grabbed from google. 
// TODO: Go back and either rewrite a new file reading function or figure it out later
std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		return (contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// converts to c string
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // create vertex shader object and get reference
	glShaderSource(vertexShader, 1, &vertexSource, NULL); // attach vertex shader source to vertex shader object
	glCompileShader(vertexShader); // compile vertex shader to machine code
	compileErrors(vertexShader, "VERTEX");

	// fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // create frag shader object and get ref
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL); // attach shader source to frag shader obj
	glCompileShader(fragmentShader); // compile shader 
	compileErrors(fragmentShader, "FRAG");

	// shader program
	shaderProgramID = glCreateProgram(); // create shader program object and get its reference
	glAttachShader(shaderProgramID, vertexShader); // attach vertex and frag shader to shader program
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID); // link all shaders together into the shader program
	compileErrors(shaderProgramID, "PROGRAM");

	// delete the shader objects now that they've been compiled
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate() {
	glUseProgram(shaderProgramID);
}

void Shader::Delete() {
	glDeleteProgram(shaderProgramID);
}

// Checks if the different Shaders have compiled properly. 
// TODO: I got this function from an outside source, go back and go through it in depth or rewrite it
void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}