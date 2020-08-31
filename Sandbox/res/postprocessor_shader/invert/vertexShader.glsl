#version 440 core

layout (location = 0) in vec2 vPos;

out vec2 texPos;

void main() {
	gl_Position = vec4(vPos, 0.0f, 1.0f);
	texPos = (vPos + vec2(1.0f, 1.0f)) / 2;
}
