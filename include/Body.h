#ifndef BODY_H
#define BODY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaderprogram.h"

class Body
{
    public:
        virtual void draw() = 0;
        virtual void init(GLFWwindow *window) = 0;
        virtual void update(double time, bool *nan_detected) = 0;
        virtual void key_callback(int key, int scancode, int action, int mods) = 0;
        virtual void cursor_position_callback(double xpos, double ypos) = 0;
        static ShaderProgram *sp;
        static glm::mat4 P, M, V;
        static glm::vec3 lukat, nose, ob_position;
        static glm::vec4 perspective;
        static double xcur, xpos, zcur, zpos, dx, dz;

    protected:

    private:

};

#endif // BODY_H
