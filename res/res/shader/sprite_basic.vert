#version 330 core

layout(location = 0) in vec2 a_pos;
layout(location = 1) in vec2 a_uv;
layout(location = 2) in vec4 a_rect;

uniform vec2 u_screen_size;

out vec2 uv;

void main()
{
    uv = a_uv;

    vec2 pos_pixel = a_rect.xy + a_pos * a_rect.zw;
    vec2 pos_normalized = pos_pixel / u_screen_size;

    gl_Position = vec4(pos_normalized, 0.0, 1.0);
}
