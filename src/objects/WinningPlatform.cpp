#include "objects/WinningPlatform.h"

WinningPlatform::WinningPlatform(glm::vec3 trans, float scal)
    : PhysicalObject(trans, scal) {
    M = glm::translate(glm::mat4(1.0f),translate);
    M = glm::scale(M,glm::vec3(scal,scal,scal));
    model->getHitbox(90);
}

WinningPlatform::~WinningPlatform() {
}

void WinningPlatform::draw(glm::mat4 P, glm::mat4 V, glm::mat4 M_arg){
    M = glm::translate(M_arg,translate);
    M = glm::rotate(M,angle_dr,glm::vec3(0.0f,1.0f,0.0f));
    if(angle_rot!=0)
        M = glm::rotate(M,angle_rot,glm::vec3(0.0f,0.0f,1.0f));
    M = glm::scale(M,glm::vec3(scale,scale,scale));

    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
    glUniform1f(sp->u("material_ambient_strength"),0.4f);
    glUniform1f(sp->u("material_diffuse_strength"),0.4f);
    glUniform1f(sp->u("material_specular_strength"),0.0f);
    glUniform1f(sp->u("material_shininess"),1.0f);
    model->drawSolid();

}

bool WinningPlatform::initialize_model() { // Model trzeba zainicjowac w initOpenGLProgram
    model = new Models::Model("models/winning_platform.obj", 8); // Sciezka modelu, id_tekstury
    return 0;
}

void WinningPlatform::destroy_model() { // Model trzeba usunac w freeOpenGLProgram
    delete model;
}

// Zwraca wybrany wierzcholek hitboxa
glm::vec4 WinningPlatform::get_hitbox(int which) {
    return model->hitbox[which];
}

// Zwraca wybrana normalna hitboxaa
glm::vec4 WinningPlatform::get_hitbox_normal(int which) {
    return model->hitbox_normal[which];
}

glm::mat4 WinningPlatform::get_M() {
    return M;
}

// Zwraca prawde jesli a jest miedzy b i c
bool is_between(float a, float b, float c) {
    if (a>b && a<c)
        return true;
    if (a>c && a<b)
        return true;
    return false;
}

// Sprawdza czy podany obiekt jest wewnatrz tego
bool WinningPlatform::is_inside(PhysicalObject *object2) {
    glm::vec4 hitbox_vert[2][4];
    // Wyliczenie aktualnych wspó³rzêdnych hitboxa
    for (int i=0; i<4; ++i) {
        hitbox_vert[0][i] = get_M() * get_hitbox(i);
        hitbox_vert[1][i] = object2->get_M() * object2->get_hitbox(i);
    }
    if     (is_between(hitbox_vert[1][0].x,hitbox_vert[0][0].x,hitbox_vert[0][2].x)
        && is_between(hitbox_vert[1][2].x,hitbox_vert[0][0].x,hitbox_vert[0][2].x)
        && is_between(hitbox_vert[1][0].z,hitbox_vert[0][0].z,hitbox_vert[0][2].z)
        && is_between(hitbox_vert[1][2].z,hitbox_vert[0][0].z,hitbox_vert[0][2].z)) {
        return true;
    }
    return false;
}
