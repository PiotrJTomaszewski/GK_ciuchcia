#include "objects/BarrierObstacle.h"

BarrierObstacle::BarrierObstacle(glm::vec3 trans, float scal, float direction)
    : PhysicalObject(trans, scal, direction) {
    M = glm::translate(glm::mat4(1.0f),translate);
    M = glm::scale(M,glm::vec3(scal,scal,scal));
    M = glm::rotate(M,direction,glm::vec3(0.0f,1.0f,0.0f));
    model->getHitbox(90);
}

BarrierObstacle::~BarrierObstacle() {
}

void BarrierObstacle::draw(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    M = glm::translate(M,translate);
    M = glm::rotate(M,angle_dr,glm::vec3(0.0f,1.0f,0.0f));
    if(angle_rot!=0)
        M = glm::rotate(M,angle_rot,glm::vec3(0.0f,0.0f,1.0f));
    M = glm::scale(M,glm::vec3(scale,scale,scale));

    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
    glUniform1f(sp->u("material_ambient_strength"),0.950f);
    glUniform1f(sp->u("material_diffuse_strength"),1.0f);
    glUniform1f(sp->u("material_specular_strength"),0.025f);
    glUniform1f(sp->u("material_shininess"),0.025f);
    model->drawSolid();

}

bool BarrierObstacle::initialize_model() { // Model trzeba zainicjowac w initOpenGLProgram
    model = new Models::Model("models/barrier.obj", 4); // Sciezka modelu, id_tekstury
    return 0;
}

void BarrierObstacle::destroy_model() { // Model trzeba usunac w freeOpenGLProgram
    delete model;
}

 // Zwraca wybrany wierzcholek hitboxa
glm::vec4 BarrierObstacle::get_hitbox(int which) {
    return model->hitbox[which];
}

// Zwraca wybrana normalna hitboxaa
glm::vec4 BarrierObstacle::get_hitbox_normal(int which) {
    return model->hitbox_normal[which];
}

glm::mat4 BarrierObstacle::get_M() {
    return M;
}
