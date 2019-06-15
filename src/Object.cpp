#include "Object.h"

Object::Object(glm::vec3 trans, float scal, float direction)
{
    angle_dr = angle_rot = 0;
    translate = glm::vec3(trans);
    scale = scal;
    angle_dr = direction;
}

// Returns true if two hitbox rectangles overlap
bool Object::is_collision(Object *object2) {
    glm::vec4 m_hbox11 = this->get_M() * this->hitbox[0];
    glm::vec4 m_hbox12 = this->get_M() * this->hitbox[1];
    glm::mat4 M2 = object2->get_M();
    glm::vec4 m_hbox21 = object2->get_hitbox(0);
    glm::vec4 m_hbox22 = object2->get_hitbox(1);
    //printf("%f,%f %f,%f\n",m_hbox2_l.x,m_hbox2_l.z,m_hbox2_r.x,m_hbox2_r.z);
    m_hbox21 = M2 * m_hbox21;
    m_hbox22 = M2 * m_hbox22;

    //printf("truck:(%f,%f)(%f,%f)\tobstacle:(%f,%f)(%f,%f)\n",m_hbox11.x,m_hbox11.y,m_hbox12.x,m_hbox12.y,m_hbox21.x,m_hbox21.y,m_hbox22.x,m_hbox22.y);

    if(m_hbox11.x > m_hbox22.x || m_hbox21.x > m_hbox12.x)
        return false;
    if(m_hbox11.y > m_hbox22.z || m_hbox21.y > m_hbox12.z)
        return false;
    return true;
}

glm::vec4 Object::get_hitbox(int which) {
    return hitbox[which];
}

glm::mat4 Object::get_M() {
    return this->M;
}
