#ifndef TRUCK_H
#define TRUCK_H

#include <Object.h>


class Truck : private Object
{
    public:
        Truck();
        virtual ~Truck();
        void draw_all(glm::mat4 P, glm::mat4 V);
        glm::vec3 speed, acceleration;
        bool b_acc;
        void update(double time);
        float turn_l, turn_r;

    protected:

    private:
        //poszczegolne czesci ciezarowki
        Object *wheel_l, *wheel_r, *main_part, *back_part;
        glm::mat4 M;
        float angle_max = PI/4.0f;
};

#endif // TRUCK_H
