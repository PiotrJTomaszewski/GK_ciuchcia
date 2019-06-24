#include "Object.h"

Object::Object(glm::vec3 trans, float scal, float direction)
{
    angle_dr = angle_rot = 0;
    translate = glm::vec3(trans);
    scale = scal;
    angle_dr = direction;
}

glm::mat4 Object::get_M() {
    return this->M;
}
