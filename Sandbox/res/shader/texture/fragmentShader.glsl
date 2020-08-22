#version 440 core

in vec2 texturePos;

uniform sampler2D plainTexture;

out vec4 fragColor;

void main() {
	fragColor = texture(plainTexture, texturePos);
}
