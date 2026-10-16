#version 330 core

in vec2 uv;

uniform sampler2D u_sprite;
uniform int u_discard;

out vec4 color;

void main()
{
    color = texture(u_sprite, uv);
    if (u_discard > 0 && color.a == 0.0) {
        discard;
    }
}
