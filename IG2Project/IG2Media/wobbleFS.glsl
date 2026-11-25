#version 330 core

in vec2 vUv0;
uniform sampler2D tex0;

out vec4 fFragColor;

void main() {
    vec3 color = vec3(texture(tex0, vUv0));
    
    fFragColor = vec4(color, 1.0);
}