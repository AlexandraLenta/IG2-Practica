#version 330 core

in vec4 vertex;
in vec2 uv0;

out vec2 vUv0;
out vec2 vUv1;
out float vZF;

uniform mat4 modelViewProjectionMatrix;
uniform float timeZoom;

void main() {
    vZF = timeZoom * 0.25 + 0.75;
    vUv0 = uv0;
    vUv1.s = (uv0.s - 0.5) * (vZF) + 0.5;
    vUv1.t = (uv0.t - 0.5) * (vZF) + 0.5;

    gl_Position = modelViewProjectionMatrix * vertex;
}