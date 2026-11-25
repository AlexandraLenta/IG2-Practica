#version 330 core

uniform sampler2D texCoor;
uniform sampler2D texInside;
uniform float flipping;
uniform vec3 lightDir;

in vec2 vUv0;
in vec2 vUv1;
in vec3 nFinal;

out vec4 fFragColor;

void main() {
    bool frontFacing = (flipping > -1)? gl_FrontFacing : !gl_FrontFacing;

    vec3 S = normalize(-lightDir);

    vec3 colorOutside = vec3(texture(texCoor, vUv0));
    vec3 colorInside = vec3(texture(texInside, vUv1));

    if (colorOutside.x > 0.8) {
        discard;
    }

    vec3 N = normalize(nFinal);
    vec3 color;

    if (frontFacing) {
        color = colorOutside;
    }
    else {
        color = colorInside;
        N = -N;
    }

    float diff = max(0.0, dot(N, S));

    fFragColor = vec4(color * diff, 1.0);
}