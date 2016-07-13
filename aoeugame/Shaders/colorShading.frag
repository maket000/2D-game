#version 130

in vec2 fragmentPosition;
in vec4 fragmentColour;
in vec2 fragmentUV;

out vec4 colour;

uniform float time;
uniform sampler2D samplerTexture;

void main() {
    vec4 textureColour = texture(samplerTexture, fragmentUV);
    colour = vec4(fragmentColour.r * (sin(fragmentPosition.x * 5.0 + time/1000.0) + 1.0) * 0.5,
                  fragmentColour.g * (sin(fragmentPosition.y * 2.0 + time/1000.0) + 1.0) * 0.5,
                  fragmentColour.b * (cos(fragmentPosition.x / fragmentPosition.y * 3.0 + time/1000.0) + 1.0) * 0.5,
                  fragmentColour.a) * textureColour;
}