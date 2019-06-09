#ifndef TRUCKMAINOBJECT_H
#define TRUCKMAINOBJECT_H
#include "Object.h"

class MainObject : public Object {
    public:
        MainObject(glm::vec3 trans, float scal=1.f);
        ~MainObject();
        void draw(glm::mat4 P, glm::mat4 V, glm::mat4 M = glm::mat4(1.0f));
        static bool initialize_model();
        static void destroy_model();

    private:
        static Models::Model *model;
};

#endif //TRUCKMAINOBJECT_H
