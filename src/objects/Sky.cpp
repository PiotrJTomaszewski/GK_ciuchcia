#include "objects/Sky.h"

Sky::Sky(glm::vec3 trans, float scal) :
    Object(trans,scal){

}

Sky::~Sky()
{
    //dtor
}

void Sky::update(glm::vec3 position){
    this->translate = position;
}

void Sky::draw(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    M = glm::translate(M,translate);
    M = glm::rotate(M,PI/2,glm::vec3(1.0f,0.0f,0.0f));
    if(angle_rot!=0)
        M = glm::rotate(M,angle_rot,glm::vec3(0.0f,0.0f,1.0f));
    M = glm::scale(M,glm::vec3(scale,scale,scale));

    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
    glUniform1f(sp->u("material_ambient_strength"),1.0f);
    glUniform1f(sp->u("material_diffuse_strength"),0.0f);
    glUniform1f(sp->u("material_specular_strength"),0.0f);
    glUniform1f(sp->u("material_shininess"),1.0f);
    model->drawSolid();

}

bool Sky::initialize_model() { // Model trzeba zainicjowac w initOpenGLProgram
    model = new Models::Model("models/test2.obj", 2); // Sciezka modelu, id_tekstury
    return 0;
}

void Sky::destroy_model() { // Model trzeba usunac w freeOpenGLProgram
    delete model;
}

