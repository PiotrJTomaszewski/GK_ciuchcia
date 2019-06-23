#ifndef SKY_H
#define SKY_H

#include <Object.h>


class Sky : public Object
{
    public:
        Sky(glm::vec3 trans, float scal=100.f);
        ~Sky();
        void draw(glm::mat4 P, glm::mat4 V, glm::mat4 M = glm::mat4(1.0f));
        void update(glm::vec3 position);
        static bool initialize_model();
        static void destroy_model();

    protected:

    private:
        static Models::Model *model;
};

#endif // SKY_H
