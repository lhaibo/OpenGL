#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 6) in vec3 aColor;
layout(location = 7) in vec2 aTexCoord;
out vec4 vertexColor;
out vec2 TexCoord;

uniform mat4 trans;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;


void main(){
	//
	gl_Position = projMat * viewMat * modelMat * trans * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	vertexColor= vec4(aColor.x,aColor.y,aColor.z,1.0);
	TexCoord= aTexCoord;
}
