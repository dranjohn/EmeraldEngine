#version 440 core

in vec2 texPos;

out vec4 fragColor;

uniform sampler2D frame;

void main() {
	fragColor = vec4(vec3(1.0f) - texture(frame, texPos).xyz, 1.0f);
	//fragColor = vec4(texPos, 0.0f, 1.0f);
}
