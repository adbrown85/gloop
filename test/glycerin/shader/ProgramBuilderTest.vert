#version 330

/* Uniforms */
uniform mat4 MVPMatrix = mat4(1.0);

/* Inputs */
in vec4 MCVertex;


/** Transforms the incoming vertex. */
void main() {
    gl_Position = MVPMatrix * MCVertex;
}
