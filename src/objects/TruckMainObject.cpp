#include "objects/TruckMainObject.h"

MainObject::MainObject(glm::vec3 trans, float scal)
    : Object(trans, scal) {
}

MainObject::~MainObject() {
}

void MainObject::draw(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    M = glm::translate(M,translate);
    M = glm::rotate(M,angle_dr,glm::vec3(0.0f,1.0f,0.0f));
    if(angle_rot!=0)
        M = glm::rotate(M,angle_rot,glm::vec3(0.0f,0.0f,1.0f));
    M = glm::scale(M,glm::vec3(scale,scale,scale));

    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
    model->drawSolid();

}

bool MainObject::initialize_model() { // Model trzeba zainicjowac w initOpenGLProgram
    model = new Models::Model("models/main.obj", 1); // Sciezka modelu, id_tekstury
    model->getHitbox(3);
    return 0;
}

void MainObject::destroy_model() { // Model trzeba usunac w freeOpenGLProgram
    delete model;
}

// Zwraca wybrany wierzcholek hitboxa
glm::vec4 MainObject::get_hitbox(int which) {
    return model->hitbox[which];
}

// Zwraca wybrana normalna hitboxaa
glm::vec4 MainObject::get_hitbox_normal(int which) {
    return model->hitbox_normal[which];
}
