#version 130

in vec2 fragmentPosition;
in vec4 fragmentColour;

out vec4 colour;

uniform float time;

void main() {
    colour = vec4(fragmentColour.r * (sin(fragmentPosition.x * 5.0 + time) + 1.0) * 0.5,
                  fragmentColour.g * (sin(fragmentPosition.y * 7.0 + time) + 1.0) * 0.5,
                  fragmentColour.b * (cos(fragmentPosition.x * fragmentPosition.y * 22.0 + time) + 1.0) * 0.5,
                  fragmentColour.a);
}