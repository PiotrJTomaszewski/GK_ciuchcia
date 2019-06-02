/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

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
#include "allmodels.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include <Body.h>
#include <Game.h>
#include <Object.h>

Models::Cube *mcube;
glm::mat4 Body::P, Body::M, Body::V;
float r_r=0, l_r=0, u_r=0, d_r=0;
ShaderProgram *sp_podloga, *Body::sp, *Object::sp;
glm::vec3 Body::lukat, Body::nose, Body::ob_position;
glm::vec4 Body::perspective;
int action;
Body *body;
Game *game;
/*float podloga[] = {
    1.0f,-1.0f,0.0f,1.0f,
    -1.0f, 1.0f,0.0f,1.0f,
	-1.0f,-1.0f,0.0f,1.0f,

	1.0f,-1.0f,0.0f,1.0f,
	1.0f, 1.0f,0.0f,1.0f,
	-1.0f, 1.0f,0.0f,1.0f,
};
float podloga_norm[] = {
    0.0f,0.0f,1.0f,1.0f,   0.0f,0.0f,1.0f,1.0f,   0.0f,0.0f,1.0f,1.0f,
    0.0f,0.0f,-1.0f,1.0f,   0.0f,0.0f,-1.0f,1.0f,   0.0f,0.0f,-1.0f,1.0f
};*/

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
    Body::lukat = glm::vec3(0.0f,0.0f,4.0f);
    Body::nose = glm::vec3(0.0f,0.0f,1.0f);
    Body::ob_position = glm::vec3(0.0f,-15.0f,4.0f);
    Body::V = glm::lookAt(Body::ob_position,Body::lukat,Body::nose);
    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    glfwGetCursorPos(window,&Body::xcur,&Body::ycur);
    glfwSetCursorPosCallback(window,cursor_position_callback);

    initShaders();
    //sp_podloga = new ShaderProgram("podlo_v.glsl",NULL,"podlo_f.glsl");

    glClearColor(1,0,0,1);

    glEnable(GL_DEPTH_TEST);

    Body::P = glm::perspective(PI/3,1.0f,0.5f,140.0f);

    mcube = new Models::Cube();

    glfwSetKeyCallback(window, key_callback);

    Object::sp = spLambert;
    Body::sp = spLambert;
    game = new Game();
    body = game;
    //body->init(window);
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
}


//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
    freeShaders();
    //sp_podloga->~ShaderProgram();
    mcube->~Cube();
    game->~Game();
    delete mcube;
    delete body;
    delete game;
    //************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************
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

    mcube->drawSolid();

    /*glEnableVertexAttribArray(spLambert->a("vertex"));
    glVertexAttribPointer(spLambert->a("vertex"),4,GL_FLOAT,false,0,podloga);

    glEnableVertexAttribArray(spLambert->a("normal"));
    glVertexAttribPointer(spLambert->a("normal"),4,GL_FLOAT,false,0,podloga_norm);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(spLambert->a("vertex"));
    glDisableVertexAttribArray(spLambert->a("normal"));*/


    /*M=glm::mat4(1.0f);
    M=glm::translate(M,glm::vec3(0.0f,0.0f,-2.0f));
    /*M=glm::rotate(M,angle_h,glm::vec3(0.0f,1.0f,0.0f));
    M=glm::rotate(M,angle_v,glm::vec3(1.0f,0.0f,0.0f));*/

    /*spLambert -> use();
    glUniformMatrix4fv(spLambert->u("P"),1,false,glm::value_ptr(P));
    glUniformMatrix4fv(spLambert->u("V"),1,false,glm::value_ptr(V));
    glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
    glUniform4f(spLambert->u("color"),0.0f,1.0f,1.0f,1.0f);
    glUniform1i(spLambert->u("pod"),0);
    glUniform4f(spLambert->u("lightPos"),-1.0f,-5.0f,-25.0f,1.0f);
    glUniform4fv(spLambert->u("lightPos2"),1,glm::value_ptr(glm::vec4(ob_position,1.0f)));

    mcube->drawSolid();*/

    body->draw();

    glfwSwapBuffers(window);
	//************Tutaj umieszczaj kod rysujący obraz******************l
}


int main(void)
{
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(900, 900, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

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
	    //keybord(window);
	    //mouse(window);

	    body->update(glfwGetTime());

		drawScene(window); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
