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

out vec4 position_M; // Polozenie wierzcholka w przestrzeni swiata
out vec4 normal_V; // Wektor normalny w przestrzeni widoku
out vec4 eye_dir_V; // Wektor do obserwatora w przestrzeni widoku
out vec4 light_dir_one_V; // Wektor do swiatla 1 w przestrzeni widoku
out vec4 light_dir_two_V; // Wektor do swiatla 1 w przestrzeni widoku
out vec4 light_pos_one_M;
out vec4 light_pos_two_M;
out vec2 tex_coord; // Wspolrzedne teksturowania


void main(void) {
    gl_Position = P*V*M*vertex;
    position_M = M*vertex;

    normal_V = V*M*normal;
    eye_dir_V = vec4(0.0f,0.0f,0.0f,1.0f)-V*M*vertex; // Obserwator jest w pkt. 0,0,0
    light_dir_one_V = V*lightPos+ eye_dir_V;
    light_dir_two_V = V*lightPos1+ eye_dir_V;
    light_pos_one_M = lightPos;
    light_pos_two_M = lightPos1;
    tex_coord = aTexCoord;
}
