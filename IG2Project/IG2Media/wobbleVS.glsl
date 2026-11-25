#version 330 core

in vec4 vertex;
in vec2 uv0;
in vec3 normal;

out vec2 vUv0;

uniform mat4 modelViewProjectionMatrix;
uniform float time;
uniform float amplitude;
uniform float frequency;

void main() {
    vec3 n = normalize(normal);
    vec3 offset = n * amplitude * sin(frequency * time + dot(vertex.xyz, vec3(1.0, 0.5, 1.2)));

    gl_Position = modelViewProjectionMatrix * (vertex + vec4(offset, 0.0f));
    vUv0 = uv0;
}