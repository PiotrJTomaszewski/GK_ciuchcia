#ifndef TRUCK_H
#define TRUCK_H

#include <objects/WheelObject.h>


class Truck : private Object
{
    public:
        Truck();
        ~Truck();
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
        // metoda draw w object jest wirtualna, wiec trzeba tu dac deklaracje, mimo ze funkcja nie jest potrzebna
        void draw(glm::mat4 P, glm::mat4 V, glm::mat4 M = glm::mat4(1.0f)){};
};

#endif // TRUCK_H
