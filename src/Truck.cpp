#include "Truck.h"

Truck::Truck() : PhysicalObject(glm::vec3(0.0f,0.0f,0.0f))
{
    wheel_l = new WheelObject(glm::vec3(1.45f,0.55f,1.1f),-1.0f); // Lewe kola maja ten sam model co prawe, wiec trzeba zrobic odbicie lustrzane
    wheel_r = new WheelObject(glm::vec3(1.45f,0.55f,-1.1f));
    wheels[0] = new WheelObject(glm::vec3(-3.55f,0.55f,1.1f),-1.0f);
    wheels[3] = new WheelObject(glm::vec3(-3.55f,0.55f,-1.1f));
    main_part = new MainObject(glm::vec3(0.0f,1.65f,0.0f));
    back_part = new WheelObject(glm::vec3(0.f,1.65f,0.f),0.f); // Chwilowo tego nie ma, potem mozna dodac np. jakis model przyczepy
//    back_part = new MainObject(glm::vec3(-21.0f,0.0f,0.0f), 10.0f);

    speed = 0.0f;
    acceleration = 0.0f;
    b_acc = false;
    turn_l = turn_r = 0.0f;
}

Truck::~Truck()
{
    //wheel_l->~Object();
    //wheel_r->~Object();
    //main_part->~Object();
    //back_part->~Object();
    delete wheels[0];
    delete wheels[3];
    delete wheel_l;
    delete wheel_r;
    delete main_part;
    delete back_part;
}

void Truck::draw_all(glm::mat4 P, glm::mat4 V){
    M = glm::translate(glm::mat4(1.0f),translate
                       +glm::vec3(wheel_odlegl/2*(cos(angle_dr)-1),0.0f,wheel_odlegl/2*sin(angle_dr)));
    M = glm::rotate(M,angle_dr,glm::vec3(0.0f,1.0f,0.0f));
//    printf("%f, %f, %f, %f\n", translate.x,translate.y, translate.z,angle_dr);
    glUniform1f(sp->u("material_ambient_strength"),0.950f);
    glUniform1f(sp->u("material_diffuse_strength"),1.0f);
    glUniform1f(sp->u("material_specular_strength"),0.025f);
    glUniform1f(sp->u("material_shininess"),0.025f);
    wheel_l->draw(P,V,M);
    wheel_r->draw(P,V,M);
    main_part->draw(P,V,M);
    this->wheels_draw(P,V,M);
    //back_part->draw(P,V,M);
}

void Truck::update(double time){
    wheel_l->angle_dr+=(turn_l-turn_r)*time;
    if(wheel_l->angle_dr>angle_max) wheel_l->angle_dr=angle_max;
    else if(wheel_l->angle_dr<-angle_max) wheel_l->angle_dr = -angle_max;
    wheel_r->angle_dr=wheel_l->angle_dr;

    if(wheel_l->angle_dr!=0){
        ctga = 1/tan(wheel_l->angle_dr);
        R = wheel_odlegl * ctga;
        s = speed*time + (acceleration-this->friction())*time*time/2;
        omega = s/R;
        px = R*sin(omega);
        pz = R*(1-cos(omega));
        delt = omega; //albo omega, albo omega/2

        translate += glm::rotateY(glm::vec3(px,0.0f,-pz),this->angle_dr);

        this->angle_dr += delt;
        if(this->angle_dr>2*PI)this->angle_dr-=2*PI;
        else if(this->angle_dr<-2*PI)this->angle_dr+=2*PI;

        wheel_l->angle_rot += speed*(R+wheel_rozstaw/2)/R*float(time)/wheel_rad;
        if(wheel_l->angle_rot>2*PI)
            wheel_l->angle_rot-=2*PI;
        wheel_r->angle_rot += speed*(R-wheel_rozstaw/2)/R*float(time)/wheel_rad;
        if(wheel_r->angle_rot>2*PI)
            wheel_r->angle_rot-=2*PI;
        this->wheels_round(wheel_l->angle_rot, wheel_r->angle_rot);

    }
    else{
        s = speed*time + (acceleration-this->friction())*time*time/2;

        translate += glm::rotateY(glm::vec3(s,0.0f,0.0f),this->angle_dr);

        wheel_l->angle_rot += speed*float(time)/wheel_rad;
        if(wheel_l->angle_rot>2*PI)
            wheel_l->angle_rot-=2*PI;
        wheel_r->angle_rot = wheel_l->angle_rot;
        this->wheels_round(wheel_l->angle_rot);

    }
    speed += (acceleration-this->friction())*float(time);
    if(speed == vmax)
        speed = vmax;
    //printf("%f, %f\n", speed,time);

}

void Truck::wheels_round(float angle, float op_angle){
    wheels[0]->angle_rot=angle;
    //wheels[3]->angle_rot=PI-op_angle;
    wheels[3]->angle_rot=op_angle;


    //wheels[1]->angle_rot=angle;
    //wheels[2]->angle_rot=angle;
    //wheels[5]->angle_rot=PI-op_angle;
    //wheels[4]->angle_rot=PI-op_angle;

}

void Truck::wheels_round(float angle){
    wheels[0]->angle_rot=angle;
    //wheels[3]->angle_rot=PI-angle;
    wheels[3]->angle_rot=angle;


    //wheels[1]->angle_rot=angle;
    //wheels[2]->angle_rot=angle;
    //wheels[4]->angle_rot=PI-angle;
    //wheels[5]->angle_rot=PI-angle;

}

void Truck::wheels_draw(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    wheels[0]->draw(P,V,M);
    wheels[3]->draw(P,V,M);


    //wheels[1]->draw(P,V,M);
    //wheels[2]->draw(P,V,M);
    //wheels[4]->draw(P,V,M);
    //wheels[5]->draw(P,V,M);

}

//TODO jakies ladne tarcie ogrnac
float Truck::friction(){
    return speed/7.0f;
}

// Zwraca wybrany wierzcholek hitboxa
glm::vec4 Truck::get_hitbox(int which) {
    return main_part->get_hitbox(which);
}

// Zwraca wybrana normalna hitboxaa
glm::vec4 Truck::get_hitbox_normal(int which) {
    return main_part->get_hitbox_normal(which);
}

void Truck::reset_pos() {
    speed = 0.0f;
    acceleration = 0.0f;
    translate = glm::vec3(0.0f,0.0f,0.0f);
    angle_dr = 0.0f;
}
