#pragma once

#include<glad/glad.h>
#include<stb/stb_image.h>

#include "ShaderClass.h"

class Texture {
public:
	GLuint textureReferenceID;
	GLenum type;
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType, bool clampToBorder);

	// assign a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);

	// binds a texture
	void Bind();

	// unbinds texture
	void Unbind();

	// deletes texture
	void Delete();

};