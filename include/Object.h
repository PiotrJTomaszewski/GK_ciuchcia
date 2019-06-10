#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "model.h"
#include "shaderprogram.h"
#include "constants.h"


class Object
{
    public:
        Object(glm::vec3 trans, float scal = 1.0f, float direction = 0);
        virtual ~Object(){};
        virtual void draw(glm::mat4 P, glm::mat4 V, glm::mat4 M = glm::mat4(1.0f))=0;
        float angle_dr, angle_rot;
        static ShaderProgram *sp;

    protected:
        glm::vec3 translate;
        float scale;

    private:
};

#endif // OBJECT_H
