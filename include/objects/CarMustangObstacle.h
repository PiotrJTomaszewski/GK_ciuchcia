#ifndef CARMUSTANGOBSTACLE_H
#define CARMUSTANGOBSTACLE_H

#include "PhysicalObject.h"

class CarMustangObstacle : public PhysicalObject
{
    public:
        CarMustangObstacle(glm::vec3 trans, float scal=1.f, float direction = 0.0f);
        ~CarMustangObstacle();
        void draw(glm::mat4 P, glm::mat4 V, glm::mat4 M = glm::mat4(1.0f));
        static bool initialize_model();
        static void destroy_model();
        glm::vec4 get_hitbox(int which);
        glm::vec4 get_hitbox_normal(int which);
    private:
        static Models::Model *model;
};

#endif // CARMUSATNGOBSTACLE_H
