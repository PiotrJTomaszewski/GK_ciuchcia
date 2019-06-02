#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;


uniform vec4 color=vec4(0,1,1,1);
uniform vec4 lightPos=vec4(0,0,-5,1); //w przestrzeni swiata
uniform vec4 lightPos2;

uniform int pod = 1;

//Atrybuty
layout (location=0) in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location=1) in vec4 normal; //wektor normalny w wierzcholku


//Zmienne interpolowane
out vec4 i_color;
out vec4 ds;
out vec4 nor;
out vec4 dob;
out vec4 ds1;

void main(void) {
    vec4 pom = vertex;
    if(pod==1){
        pom.z=0;
    }
    gl_Position=P*V*M*pom;

    /*mat4 G=mat4(inverse(transpose(mat3(M))));
    vec4 n=normalize(V*G*normal);

    float nl=clamp(dot(n,lightDir),0,1);*/

    /*float nl=clamp(dot(M*normal,(-(M*vertex)+lightPos)),0,1);
    nl+=clamp(dot(M*normal,(lightPos2-(M*vertex))),0,0.4);
    nl=clamp(nl,0,1);*/

    i_color=color;

    ds = normalize(V*(lightPos2-M*vertex));
    nor = normalize(V*M*normal);

    ds1 = normalize(V*(lightPos-M*vertex));
    dob = normalize(vec4(0,0,0,1)-V*M*vertex);
}
