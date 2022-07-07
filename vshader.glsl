#version 410

in vec4 vPosition;
in vec4 vColor;
out vec4 color;

uniform mat4 ModelView;
uniform mat4 Projection;
uniform mat4 GeneralModelView;

void main()
{
    gl_Position =  Projection * GeneralModelView * ModelView * vPosition;
    color = vColor;
}
