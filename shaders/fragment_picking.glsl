#version 330 core

in vec3 PickingColor;

out vec4 color;

void main(){

	color = vec4(PickingColor,1.0);
}