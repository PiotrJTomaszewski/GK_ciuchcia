#ifndef FLOOROBJECT_H
#define FLOOROBJECT_H
#include "Object.h"
#include "model.h"

class FloorObject : public Object {
    public:
        FloorObject(glm::vec3 trans, float scal=1.f);
        ~FloorObject();
        void draw(glm::mat4 P, glm::mat4 V, glm::mat4 M = glm::mat4(1.0f));
        static bool initialize_model();
        static void destroy_model();

    private:
        static Models::Model *model;
};

#endif //FLOOROBJECT_H
