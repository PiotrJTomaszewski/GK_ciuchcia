#include "Object.h"

Object::Object(glm::vec3 trans, float scal)
{
    angle_dr = angle_rot = 0;
    translate = glm::vec3(trans);
    scale = scal;
}
