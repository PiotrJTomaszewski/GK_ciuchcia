#ifndef TRUCKWHEELOBJECT_H
#define TRUCKWHEELOBJECT_H
#include "PhysicalObject.h"
#include "model.h"

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

#endif //TRUCKWHEELOBJECT_H
