#version 330

/* Uniforms */
uniform vec4 Color = vec4(1.0);

/* Outputs */
out vec4 FragColor;


/** Colors the fragment. */
void main() {
    FragColor = Color;
}
