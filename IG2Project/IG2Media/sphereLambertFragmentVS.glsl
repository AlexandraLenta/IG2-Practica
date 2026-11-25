#version 330 core

in vec4 vertex;
in vec2 uv0;
in vec3 normal;

out vec2 vUv0;
out vec2 vUv1;
out vec3 nFinal;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main() {
    nFinal = normalize(normalMatrix * normal);
    
    gl_Position = modelViewProjectionMatrix * vertex;

    vUv0 = uv0;
    vUv1 = uv0;
}