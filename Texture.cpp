#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum textureUnitSlot, GLenum format, GLenum pixelType, bool clampToBorder) {
	
	// assigns the type of the texture to the texture object
	type = texType;

	// stores the width, height, and the number of color channels of the image
	int widthImag, heightImg, numberOfColorChannels;

	// flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);

	// reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(image, &widthImag, &heightImg, &numberOfColorChannels, 0);


	// generates an opengl texture object
	glGenTextures(1, &textureReferenceID);

	// assigns the texture to a texture unit
	glActiveTexture(textureUnitSlot);
	glBindTexture(texType, textureReferenceID);

	// configures the type of algorithm thats used to make the image smaller or bigger
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// configures the way the texture repeats (if at all)
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // for the S axis
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT); // for the T axis

	// clamps to border
	if (clampToBorder) {
		float flatColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);
	}

	// assigns the image to the opengl texture object
	glTexImage2D(texType, 0, GL_RGBA, widthImag, heightImg, 0, format, pixelType, bytes);
	
	// generates mipmaps
	glGenerateMipmap(texType);

	// deletes the image data since it's now in the opengl texture object
	stbi_image_free(bytes);

	// unbinds the opengl texture object so that it can't be accidentally modified
	glBindTexture(texType, 0);

}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
	// gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.shaderProgramID, uniform);

	// shader needs to be activated before changing the value of the uniform
	shader.Activate();

	// sets the uniform value
	glUniform1f(texUni, unit);
}

void Texture::Bind() {
	glBindTexture(type, textureReferenceID);
}

void Texture::Unbind() {
	glBindTexture(type, 0);
}

void Texture::Delete() {
	glDeleteTextures(1, &textureReferenceID);
}