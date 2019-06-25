#include "objects/TruckMainObject.h"

MainObject::MainObject(glm::vec3 trans, float scal)
    : PhysicalObject(trans, scal) {
    M = glm::translate(glm::mat4(1.0f),translate);
    M = glm::scale(M,glm::vec3(scal,scal,scal));
    model->getHitbox(1.2f);
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
    model = new Models::Model("models/mainB.obj", 1); // Sciezka modelu, id_tekstury
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

glm::mat4 MainObject::get_M() {
    return M;
}
