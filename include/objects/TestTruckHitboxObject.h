#ifndef TESTTRUCKHITBOXOBJECT_H
#define TESTTRUCKHITBOXOBJECT_H
#include "Object.h"
#include "model.h"

class TestTruckHitboxObject : public Object {
    public:
        TestTruckHitboxObject(glm::vec3 trans, float scal=1.f);
        ~TestTruckHitboxObject();
        void draw(glm::mat4 P, glm::mat4 V, glm::mat4 M = glm::mat4(1.0f));
        static bool initialize_model();
        static void destroy_model();

    private:
        static Models::Model *model;
};

#endif //TESTTRUCKHITBOXOBJECT_H
