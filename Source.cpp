#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderClass.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// TODO: dive deeper into the depth buffer

const unsigned int width = 800;
const unsigned int height = 800;

// vertex coordinates
GLfloat verticies[] = {
//   vertex coordinates          colors        texture coordinates
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// indicies for verticies order
GLuint indicies[] = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

int main() {
	// initialize glfw
	glfwInit();

	// tell glfw what version of opengl we're using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// tell glfw we're using the core profile so we only support modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// the window itself
	GLFWwindow* window = glfwCreateWindow(width, height, "Kyle's Window", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window!\n";
		glfwTerminate();
		return -1;
	}

	// tell glfw we want to use the window by setting the context to the window
	glfwMakeContextCurrent(window);

	// tell glad to load the configurations for opengl
	gladLoadGL();

	// specify the size of the viewport, where x = 0, y = 0, x = 800, y = 800
	glViewport(0, 0, width, height);

	// generates shader object using the shader files
	Shader shaderProgram("default.vert", "default.frag");

	// creates VAO and binds it
	VAO VAO1;
	VAO1.Bind();

	// creates VBO and links it to the verticies
	VBO VBO1(verticies, sizeof(verticies));

	// creates element buffer object and links it to the indicies
	EBO EBO1(indicies, sizeof(indicies));

	// links VBO to VAO
	VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Unbinds everything to prevent accidental modification
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// gets a reference of the shader's uniform (in this case, in our vertex shader from our shader program) and assigns it to a variable 
	GLuint uniID = glGetUniformLocation(shaderProgram.shaderProgramID, "scale");

	// Texture
	Texture popCat("Textures/pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE, false);
	popCat.texUnit(shaderProgram, "tex0", 0);

	// for rotation of the pyramid
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// enables depth testing to prevent glitches
	glEnable(GL_DEPTH_TEST);
	
	// main loop
	while (!glfwWindowShouldClose(window)) {
		// specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); 

		// clear the back buffer's color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

		// tell OpenGL which shader program to use
		shaderProgram.Activate();

		// timer that gets the current time, checks if the current time - the time from the last loop has been more than 1/60th of a second, 
		// and adds a little to the rotation if so
		double currentTime = glfwGetTime();
		if (currentTime - prevTime >= 1 / 60) {
			rotation += 0.5f;
			prevTime = currentTime;
		}

		// initialize matrices to the identity matrix so when they are multiplied for viewing, a null matrix is not returned
		glm::mat4 model = glm::mat4(1.f);
		glm::mat4 view = glm::mat4(1.f);
		glm::mat4 proj = glm::mat4(1.f);
		
		// assigns transformations to each matrix for 3D viewing
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.f), (float)(width / height), 0.1f, 100.f);

		// sends the matrices to the vertex shader through uniforms
		int modelLocation = glGetUniformLocation(shaderProgram.shaderProgramID, "model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
		int projLocation = glGetUniformLocation(shaderProgram.shaderProgramID, "proj");
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(proj));
		int viewLocation = glGetUniformLocation(shaderProgram.shaderProgramID, "view");
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

		// gives data to the uniform as a float
		glUniform1f(uniID, 0.5f);

		// binds the texture so that it appears in rendering
		popCat.Bind();
		
		// bind the VAO so OpenGL knows which one to use
		VAO1.Bind();

		// draw primitives, number of indicies, data type of the indicies, and the index of the indicies 
		glDrawElements(GL_TRIANGLES, sizeof(indicies)/sizeof(int), GL_UNSIGNED_INT, 0); 

		// swap the back and front buffers
		glfwSwapBuffers(window);

		// tell glfw to process all events (window resize, etc)
		glfwPollEvents();
	}

	// delete all the objects we made and terminate
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	popCat.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
}