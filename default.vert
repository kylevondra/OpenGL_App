// vertex shader source
#version 330 core

// positions of the verticies
layout (location = 0) in vec3 aPos;

// colors of the verticies
layout (location = 1) in vec3 aColor;

// texture coordinates
layout (location = 2) in vec2 aTex;


// outputs the color for the fragment shader
out vec3 color;

// outputs the texture coordinates to the frag shader
out vec2 texCoord;

// controls the verticies scale
uniform float scale;

// inputs matrices needed for perspective 3D viewing
uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

void main() {
    // outputs the position of all the verticies
    gl_Position = proj * view * model * vec4(aPos, 1.0);

    // assigns the color from the vertext data to "color"
    color = aColor;

    // assigns the texture coordinates from the vertex data to "texCoord"
    texCoord = aTex;
}
