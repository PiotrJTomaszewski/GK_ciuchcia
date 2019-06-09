#ifndef TRUCK_H
#define TRUCK_H

#include <Object.h>
#include <cmath>


class Truck : private Object
{
    public:
        Truck();
        virtual ~Truck();
        void draw_all(glm::mat4 P, glm::mat4 V);
        float speed, acceleration;
        bool b_acc;
        void update(double time);
        float turn_l, turn_r;

    protected:

    private:
        //poszczegolne czesci ciezarowki
        Object *wheel_l, *wheel_r, *main_part, *back_part, *wheels[6];
        glm::mat4 M;
        float angle_max = PI/4.0f;
        glm::vec3 acc_dr;
        void wheels_round(float angle);
        void wheels_draw(glm::mat4 P, glm::mat4 V, glm::mat4 M);
        float wheel_rozstaw=10, wheel_odlegl=10, ctga, px, py, R, omega, delt, s;
        float friction();
        int i;
};

#endif // TRUCK_H
