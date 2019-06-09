#include "Truck.h"

Truck::Truck()
{
    WheelObject::initialize_model();// TODO: Mo¿e to nie jest najlepsze miejsce ale na razie niech zostanie
    wheel_l = new WheelObject(glm::vec3(0.0f,-10.0f,-10.0f));
    wheel_r = new WheelObject(glm::vec3(0.0f,10.0f,-10.0f));
    main_part = new WheelObject(glm::vec3(0.0f,0.0f,0.0f), 10.0f);
    back_part = new WheelObject(glm::vec3(-21.0f,0.0f,0.0f), 10.0f);
    speed = glm::vec3(0.0f);
    acceleration = glm::vec3(0.0f);
    b_acc = false;
    turn_l = turn_r = 0.0f;
    angle_dr = angle_rot = 0;
    translate = glm::vec3(0.f, 0.f, 11.f);
}

Truck::~Truck()
{
    wheel_l->~Object();
    wheel_r->~Object();
    main_part->~Object();
    back_part->~Object();
    delete wheel_l;
    delete wheel_r;
    delete main_part;
    delete back_part;
    WheelObject::destroy_model();// TODO: Mo¿e to nie jest najlepsze miejsce ale na razie niech zostanie
}

void Truck::draw_all(glm::mat4 P, glm::mat4 V){
    M = glm::translate(glm::mat4(1.0f),translate);
    M = glm::rotate(M,angle_dr,glm::vec3(0.0f,0.0f,1.0f));

    wheel_l->draw(P,V,M);
    wheel_r->draw(P,V,M);
    main_part->draw(P,V,M);
    back_part->draw(P,V,M);
}

void Truck::update(double time){

    wheel_l->angle_dr+=(turn_l-turn_r)*time;
    if(wheel_l->angle_dr>angle_max) wheel_l->angle_dr=angle_max;
    else if(wheel_l->angle_dr<-angle_max) wheel_l->angle_dr = -angle_max;
    wheel_r->angle_dr=wheel_l->angle_dr;

    acceleration = glm::rotateZ(acceleration,wheel_l->angle_dr);

    //TODO jakies ladne tarcie ogrnac
    translate += speed*float(time) + (acceleration-speed/7.0f)*float(time)*float(time)/2.0f;
    speed += (acceleration-speed/7.0f)*float(time);
    //printf("%f, %f\n", glm::length(speed),time);

    wheel_l->angle_rot += glm::length(speed)*float(time); //na razie r=1, wiec predkosc katowa=liniowej
    wheel_r->angle_rot = wheel_l->angle_rot;
    if(angle_rot>2*PI)
        angle_rot-=2*PI;

}

