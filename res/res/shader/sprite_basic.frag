#version 330 core

in vec2 uv;

uniform sampler2D u_sprite;

out vec4 color;

void main()
{
    color = texture(u_sprite, uv);
}
