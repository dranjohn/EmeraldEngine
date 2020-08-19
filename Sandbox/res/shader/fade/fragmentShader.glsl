#version 440 core

in vec2 colorPos;

out vec4 fragColor;

void main() {
	fragColor = vec4(colorPos.x, 0.5f, colorPos.y, 1.0f);
}
