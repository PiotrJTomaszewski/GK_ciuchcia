#ifndef PHYSICALOBJECT_H
#define PHYSICALOBJECT_H

#include "Object.h"


class PhysicalObject : public Object
{
    public:
        PhysicalObject(glm::vec3 trans, float scal = 1.0f, float direction = 0);
        virtual ~PhysicalObject(){};
        bool is_collision(PhysicalObject *Object2);
        glm::mat4 get_M();
        virtual glm::vec4 get_hitbox(int which)=0;
        virtual glm::vec4 get_hitbox_normal(int which)=0;
    protected:
    private:
};

#endif // PHYSICALOBJECT_H
