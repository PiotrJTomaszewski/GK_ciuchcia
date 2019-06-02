#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "cube.h"
#include "shaderprogram.h"
#include "constants.h"


class Object
{
    public:
        Object(glm::vec3 trans, float scal = 1.0f);
        virtual ~Object();
        void draw(glm::mat4 P, glm::mat4 V, glm::mat4 M = glm::mat4(1.0f));
        float angle_dr, angle_rot;
        static ShaderProgram *sp;

    protected:
        glm::vec3 translate;
        float scale;

    private:
        //jakies wierzcholki, tekstury
        // chwilowo
        Models::Cube *cube;
};

#endif // OBJECT_H
