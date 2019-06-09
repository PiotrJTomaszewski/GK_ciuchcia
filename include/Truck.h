#ifndef TRUCK_H
#define TRUCK_H

#include <objects/WheelObject.h>


class Truck
{
    public:
        Truck();
        ~Truck();
        void draw_all(glm::mat4 P, glm::mat4 V);
        glm::vec3 speed, acceleration;
        bool b_acc;
        void update(double time);
        float turn_l, turn_r;
        float angle_dr, angle_rot;
        glm::vec3 translate;
    protected:

    private:
        //poszczegolne czesci ciezarowki
        Object *wheel_l, *wheel_r, *main_part, *back_part;
        glm::mat4 M;
        float angle_max = PI/4.0f;
};

#endif // TRUCK_H
