#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;


uniform vec4 color=vec4(0.0f,1.0f,1.0f,1.0f);
uniform vec4 lightPos; //w przestrzeni swiata
uniform vec4 lightPos1;

uniform int pod = 1;

//Atrybuty
layout (location=0) in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
layout (location=1) in vec4 normal; //wektor normalny w wierzcholku
layout (location=2) in vec2 aTexCoord; //wspolrzedne teksturowania

//Zmienne interpolowane
out vec4 i_color;
out vec4 lpos0;
out vec4 lpos1;
out vec4 ds; // Wektor do swiatla 0
out vec4 nor; // Wektor normalny
out vec4 dob; // Wektor do obserwatora
out vec4 ds1; // Wektor do swiatla 1
out vec2 texCoord; // Wspolrzedne teksturowania
out vec4 fragPos;


void main(void) {
    gl_Position = P*V*M*vertex;
    fragPos = M*vertex;
    nor = normalize(normal);
    ds  = normalize(V*(lightPos-M*vertex));
    ds1 = normalize(V*(lightPos1-M*vertex));
    //ds1 = normalize(V*M*vertex);

    dob = normalize(vec4(0,0,0,1)-V*M*vertex);

    lpos0 = V*lightPos;
    //lpos1 = V*vec4(0.f,50.f,0.f,1.f);
    lpos1 = V*lightPos1;

    texCoord = aTexCoord;
}
