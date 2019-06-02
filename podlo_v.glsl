#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

uniform vec4 color=vec4(0,1,1,1);

in vec4 vertex;

out vec4 i_color;

void main(void){
    vec4 pom = P*V*M*vertex;
    gl_Position = vec4(pom.xy,0,pom.w);

    i_color = color;
}
