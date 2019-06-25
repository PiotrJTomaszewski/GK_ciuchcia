#include "objects/CarObstacle.h"

CarObstacle::CarObstacle(glm::vec3 trans, float scal, float direction)
    : PhysicalObject(trans, scal, direction) {
    nr_mod = rand()%3;
    if(nr_mod==1){
        scale=0.058f;
        translate.y-=1.0f;
    }
    M = glm::translate(glm::mat4(1.0f),translate);
    M = glm::scale(M,glm::vec3(scal,scal,scal));
    model->getHitbox(80);
}

CarObstacle::~CarObstacle() {
}

void CarObstacle::draw(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    M = glm::translate(M,translate);
    M = glm::rotate(M,angle_dr,glm::vec3(0.0f,1.0f,0.0f));
    if(angle_rot!=0)
        M = glm::rotate(M,angle_rot,glm::vec3(0.0f,0.0f,1.0f));
    if(nr_mod==1){
        M = glm::rotate(M,-PI/2,glm::vec3(1.0f,0.0f,0.0f));
    }
    M = glm::scale(M,glm::vec3(scale,scale,scale));

    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
    glUniform1f(sp->u("material_ambient_strength"),0.6f);
    glUniform1f(sp->u("material_diffuse_strength"),0.6f);
    glUniform1f(sp->u("material_specular_strength"),0.15f);
    glUniform1f(sp->u("material_shininess"),0.20f);
    switch(nr_mod) {
    case 0: model->drawSolid(); break;
    case 1: model2->drawSolid(); break;
    case 2: model3->drawSolid(); break;
    }
}

bool CarObstacle::initialize_model() { // Model trzeba zainicjowac w initOpenGLProgram
    model  = new Models::Model("models/911_GT2.obj", 5); // Sciezka modelu, id_tekstury
    model2 = new Models::Model("models/mustang.obj", 6);
    model3 = new Models::Model("models/attack_helicopter.obj", 7);
    return 0;
}

void CarObstacle::destroy_model() { // Model trzeba usunac w freeOpenGLProgram
    delete model;
    delete model2;
    delete model3;
}

// Zwraca wybrany wierzcholek hitboxa
glm::vec4 CarObstacle::get_hitbox(int which) {
    return model->hitbox[which];
}

// Zwraca wybrana normalna hitboxaa
glm::vec4 CarObstacle::get_hitbox_normal(int which) {
    return model->hitbox_normal[which];
}

glm::mat4 CarObstacle::get_M() {
    return M;
}
