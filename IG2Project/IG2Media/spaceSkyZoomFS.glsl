#version 330 core

out vec4 fFragColor;

in vec2 vUv0;
in vec2 vUv1;
in float vZF;

uniform sampler2D tex0;
uniform sampler2D tex1;

void main(void) {
    vec3 color0 = vec3(texture(tex0, vUv0));
    vec3 color1 = vec3(texture(tex1, vUv1));

    vec3 color = color0 * color1 * vZF;
    
    fFragColor = vec4(color, 1.0);
}