#ifndef CAROBSTACLE_H
#define CAROBSTACLE_H

#include <Object.h>
#include "model.h"

class CarObstacle : public Object
{
    public:
        CarObstacle(glm::vec3 trans, float scal=1.f, float direction = 0.0f);
        ~CarObstacle();
        void draw(glm::mat4 P, glm::mat4 V, glm::mat4 M = glm::mat4(1.0f));
        static bool initialize_model();
        static void destroy_model();
        glm::vec4 get_hitbox(int which);
        glm::vec4 get_hitbox_normal(int which);
    private:
        static Models::Model *model;
};

#endif // CAROBSTACLE_H
