#ifndef TRUCK_H
#define TRUCK_H

#include "objects/TruckWheelObject.h"
#include "objects/TruckMainObject.h"
#include <cmath>


class Truck : private Object
{
    public:
        Truck();
        ~Truck();
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
        void wheels_round(float angle);
        void wheels_round(float angle, float op_angle);
        void wheels_draw(glm::mat4 P, glm::mat4 V, glm::mat4 M);
        float wheel_rozstaw=2.2f, wheel_odlegl=5, wheel_rad=0.1f, ctga, px, py, R, omega, delt, s;
        float back_length = 10, back_odlegl=5, back_ang;
        float friction();
        int i;
        // metoda draw w object jest wirtualna, wiec trzeba tu dac deklaracje, mimo ze funkcja nie jest potrzebna
        void draw(glm::mat4 P, glm::mat4 V, glm::mat4 M = glm::mat4(1.0f)){};

};

#endif // TRUCK_H
