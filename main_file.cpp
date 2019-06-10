#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "Body.h"
#include "Game.h"
#include "Object.h"
#include "globals.h"

// Tekstury
const unsigned number_of_textures=2; // Ile tekstur jest do zaladowania
const char *texture_names[] = {"textures/wheel_tex.png", "textures/main_tex.png"}; // Nazwy plikow tekstur
GLuint Global::tex[number_of_textures]; // Uchwyty na tekstury


glm::mat4 Body::P, Body::M, Body::V;
float r_r=0, l_r=0, u_r=0, d_r=0;
ShaderProgram *sp_podloga, *Body::sp, *Object::sp, *Models::Model::sp;
glm::vec3 Body::lukat, Body::nose, Body::ob_position;
glm::vec4 Body::perspective;
int action;
Body *body;
Game *game;
// Konieczne do dzialania statycznych modeli
Models::Model *WheelObject::model = NULL;
Models::Model *MainObject::model  = NULL;

void readTextures() {
    glGenTextures(number_of_textures, Global::tex); // Zainicjuj uchwyty dla tekstur
    for (int i=0; i<number_of_textures; ++i) {
        std::vector<unsigned char> image;
        unsigned width, height;
        // Wczytaj obrazek
        unsigned error = lodepng::decode(image, width, height, texture_names[i]);
        if (error != 0) { // Jesli obrazka nie uda sie wczytac
        printf("Error while loading texture file %s\n", texture_names[i]);
        exit(EXIT_FAILURE);
        }
        glActiveTexture(GL_TEXTURE0+i); // Zawsze GL_TEXTUREi = GL_TEXTURE0+i
        glBindTexture(GL_TEXTURE_2D, Global::tex[i]); // Uaktywnij pojedynczy uchwyt
        //Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
        glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());
        // Parametry tekstury
        // TODO: Pomyslec jakie sa potrzebne, bo te po prostu skopiowalem z prezentacji i nie chce mi sie myslec co robia xd
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
    body->key_callback(key,scancode,action,mods);
}

double Body::xcur, Body::ycur, Body::xpos, Body::ypos, Body::dx, Body::dy;

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos){
    body->cursor_position_callback(xpos,ypos);
}

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
    // Wczytaj modele
    WheelObject::initialize_model();
    MainObject::initialize_model();
    // Wczytaj tekstury
    readTextures();

    Body::lukat = glm::vec3(0.0f,0.0f,4.0f);
    Body::nose = glm::vec3(0.0f,0.0f,1.0f);
    Body::ob_position = glm::vec3(0.0f,-15.0f,4.0f);
    Body::V = glm::lookAt(Body::ob_position,Body::lukat,Body::nose);
    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    glfwGetCursorPos(window,&Body::xcur,&Body::ycur);
    glfwSetCursorPosCallback(window,cursor_position_callback);

    initShaders();

    glClearColor(1,0,0,1);

    glEnable(GL_DEPTH_TEST);

    Body::P = glm::perspective(PI/3,1.0f,0.5f,140.0f);

    glfwSetKeyCallback(window, key_callback);

    Object::sp = spLambert;
    Body::sp = spLambert;
    Models::Model::sp = spLambert;
    game = new Game();
    body = game;
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    // Zwolnij tekstury
    glDeleteTextures(number_of_textures,Global::tex);
    // Zwolnij modele
    WheelObject::destroy_model();
    MainObject::destroy_model();

    freeShaders();
    //game->~Game();
    delete body;
    //delete game; // Usuniecie body juz usuwa game, ta linia powoduje naruszenie pamieci
}

//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    Body::M=glm::scale(glm::mat4(1.0f),glm::vec3(140.0f,140.0f,0.1f));

    spLambert->use();
    glUniformMatrix4fv(spLambert->u("P"),1,false,glm::value_ptr(Body::P));
    glUniformMatrix4fv(spLambert->u("V"),1,false,glm::value_ptr(Body::V));
    glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(Body::M));
    glUniform4f(spLambert->u("color"),0.0f,1.0f,0.0f,1.0f);
    glUniform1i(spLambert->u("pod"),0);
    glUniform4f(spLambert->u("lightPos"),-1.0f,-5.0f,25.0f,1.0f);
    glUniform4fv(spLambert->u("lightPos2"),1,glm::value_ptr(glm::vec4(Body::ob_position,1.0f)));

    body->draw();

    glfwSwapBuffers(window);
}


int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(1280, 720, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

	//Główna pętla
	glfwSetTime(0);
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{

	    body->update(glfwGetTime());

		drawScene(window); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
