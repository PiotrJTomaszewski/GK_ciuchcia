#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;


uniform vec4 lightPos; //w przestrzeni swiata
uniform vec4 lightPos1;

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
out vec4 light_pos_one_M; // Polozenie zrodla swiatla w przestrzeni swiata
out vec4 light_pos_two_M; // Polozenie zrodla swiatla w przestrzeni swiata
out vec2 tex_coord; // Wspolrzedne teksturowania


void main(void) {
    gl_Position = P*V*M*vertex;
    position_M = M*vertex;

    normal_V = V*M*normal;
    eye_dir_V = -V*M*vertex; // Obserwator jest w pkt. 0,0,0
    light_dir_one_V = V*vec4(0,-1,0,0);
    light_dir_two_V = V*lightPos1 + eye_dir_V; // V*lightPos1 - V*M*vertex
    // Normalizacja wektorow
    normal_V = normalize(normal_V);
    eye_dir_V = normalize(eye_dir_V);
    light_dir_one_V = normalize(light_dir_one_V);
    light_dir_two_V = normalize(light_dir_two_V);

    light_pos_one_M = position_M+vec4(0,0,1,0); //lightPos;
    light_pos_two_M = lightPos1;
    tex_coord = aTexCoord;
}
