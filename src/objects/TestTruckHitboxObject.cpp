#include "objects/TestTruckHitboxObject.h"

TestTruckHitboxObject::TestTruckHitboxObject(glm::vec3 trans, float scal)
    : Object(trans, scal) {

}

TestTruckHitboxObject::~TestTruckHitboxObject() {

}

void TestTruckHitboxObject::draw(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    M = glm::translate(M,translate);
    M = glm::rotate(M,angle_dr,glm::vec3(0.0f,1.0f,0.0f));
    if(angle_rot!=0)
        M = glm::rotate(M,angle_rot,glm::vec3(0.0f,0.0f,1.0f));
    M = glm::scale(M,glm::vec3(scale,scale,scale));

    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
    glUniform4f(sp->u("color"),0.0f,1.0f,1.0f,1.0f);
//    model->drawSolid();

}

bool TestTruckHitboxObject::initialize_model() { // Model trzeba zainicjowac w initOpenGLProgram
//    model = new Models::Model("models/test_truck_hitbox.obj", 3); // Sciezka modelu, id_tekstury
    return 0;
}

void TestTruckHitboxObject::destroy_model() { // Model trzeba usunac w freeOpenGLProgram
//    delete model;
}
