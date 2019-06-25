#ifndef WINNINGPLATFORM_H
#define WINNINGPLATFORM_H
#include "PhysicalObject.h"
#include "model.h"

class WinningPlatform: public PhysicalObject {
    public:
        WinningPlatform(glm::vec3 trans, float scal=1.f);
        ~WinningPlatform();
        void draw(glm::mat4 P, glm::mat4 V, glm::mat4 M_arg = glm::mat4(1.0f));
        static bool initialize_model();
        static void destroy_model();
        glm::vec4 get_hitbox(int which);
        glm::vec4 get_hitbox_normal(int which);
        bool is_inside(PhysicalObject *object2); // Sprawdza czy podany obiekt jest wewnatrz tego
        glm::mat4 get_M();
    private:
        static Models::Model *model;
        glm::mat4 M;
};

#endif // WINNINGPLATFORM_H
