#ifndef TRUCK_H
#define TRUCK_H

#include "Object.h"
#include "objects/TruckWheelObject.h"
#include "objects/TruckMainObject.h"
#include <cmath>


class Truck : public Object
{
    public:
        Truck();
        ~Truck();
        void draw_all(glm::mat4 P, glm::mat4 V);
        float speed, acceleration;
        bool b_acc;
        void update(double time);
        float turn_l, turn_r;
        glm::vec4 get_hitbox(int which);
        glm::vec4 get_hitbox_normal(int which);
        void reset_pos();
    protected:

    private:
        //poszczegolne czesci ciezarowki
        Object *wheel_l, *wheel_r, *main_part, *back_part, *wheels[6];
        const float angle_max = PI/6.0f; // Maksymalny skret kola
        void wheels_round(float angle);
        void wheels_round(float angle, float op_angle);
        void wheels_draw(glm::mat4 P, glm::mat4 V, glm::mat4 M);
        float wheel_rozstaw=2.2f, wheel_odlegl=5, wheel_rad=0.3f, ctga, px, pz, R, omega, delt, s;
        const float vmax = 1.0f;
        float back_length = 10, back_odlegl=5, back_ang;
        float friction();
        int i;
        // metoda draw w object jest wirtualna, wiec trzeba tu dac deklaracje, mimo ze funkcja nie jest potrzebna
        void draw(glm::mat4 P, glm::mat4 V, glm::mat4 M = glm::mat4(1.0f)){};

};

#endif // TRUCK_H
