#ifndef BARRIEROBSTACLE_H
#define BARRIEROBSTACLE_H
#include "PhysicalObject.h"
#include "model.h"

class BarrierObstacle: public PhysicalObject {
    public:
        BarrierObstacle(glm::vec3 trans, float scal=1.f, float direction=1.0f);
        ~BarrierObstacle();
        void draw(glm::mat4 P, glm::mat4 V, glm::mat4 M_arg = glm::mat4(1.0f));
        static bool initialize_model();
        static void destroy_model();
        glm::vec4 get_hitbox(int which);
        glm::vec4 get_hitbox_normal(int which);
        glm::mat4 get_M();
    private:
        static Models::Model *model;
        glm::mat4 M;
};

#endif // BARRIEROBSTACLE_H
