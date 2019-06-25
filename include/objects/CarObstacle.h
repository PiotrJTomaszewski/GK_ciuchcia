#ifndef CAROBSTACLE_H
#define CAROBSTACLE_H

#include "model.h"
#include "PhysicalObject.h"
#include <cstdlib>

class CarObstacle : public PhysicalObject
{
    public:
        CarObstacle(glm::vec3 trans, float scal=1.f, float direction = 0.0f);
        ~CarObstacle();
        void draw(glm::mat4 P, glm::mat4 V, glm::mat4 M_arg = glm::mat4(1.0f));
        static bool initialize_model();
        static void destroy_model();
        glm::vec4 get_hitbox(int which);
        glm::vec4 get_hitbox_normal(int which);
        glm::mat4 get_M();
    private:
        static Models::Model *model, *model2, *model3;
        int nr_mod;
        glm::mat4 M;
};

#endif // CAROBSTACLE_H
