#version 440 core

layout (location = 0) in vec2 vPos;

out vec2 colorPos;

void main() {
	gl_Position = vec4(vPos, 0.0f, 1.0f);
	colorPos = vPos + vec2(0.5f, 0.5f);
}
