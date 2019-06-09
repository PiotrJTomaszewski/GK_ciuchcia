#ifndef WHEELOBJECT_H
#define WHEELOBJECT_H
#include "Object.h"

class WheelObject : public Object {
    public:
        WheelObject(glm::vec3 trans, float scal=1.f);
        ~WheelObject();
        void draw(glm::mat4 P, glm::mat4 V, glm::mat4 M = glm::mat4(1.0f));
        static bool initialize_model();
        static void destroy_model();

    private:
        static Models::Model *model;
};

#endif //WHEELOBJECT_H
