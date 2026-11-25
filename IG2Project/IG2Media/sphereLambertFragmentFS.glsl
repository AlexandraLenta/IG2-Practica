#version 330 core

uniform sampler2D texCoor;
uniform sampler2D texInside;
uniform float flipping;

out vec4 fFragColor;

void main() {
    vec3 color;

    vec3 colorOutside = vec3(texture(texCoor, vUv0));
}