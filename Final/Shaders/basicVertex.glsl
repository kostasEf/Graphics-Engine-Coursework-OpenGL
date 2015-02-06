#version 150 core

in vec3 position ;
in vec4 colour1 ;

out Vertex  { 	 vec4 colour ; } OUT ;

//out vec4 colour2;

void main ( void ) 
{
	gl_Position = vec4 ( position , 1.00);
	OUT.colour = colour1 ;
}