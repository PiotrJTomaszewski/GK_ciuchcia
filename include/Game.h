#ifndef GAME_H
#define GAME_H

#include "Body.h"
#include "Truck.h"
#include "objects/Floor.h"
#include "objects/TestObstacle.h"
#include "shaderprogram.h"

class Game : public Body
{
    public:
        Game();
        virtual ~Game();
        void draw();
        void init(GLFWwindow *window);
        void update(double time);
        void key_callback(int key, int scancode, int action, int mods);
        void cursor_position_callback(double xpos, double ypos);
    protected:

    private:
        float r_r=0, l_r=0, u_r=0, d_r=0;
        glm::vec3 plukat;
        glm::vec4 pl;
        glm::vec3 pom_sum;
        float angle_h = 0, angle_v = 0;
        Truck *truck;
        FloorObject *floor;
        TestObstacle *test_obstacle;
};

#endif // GAME_H
