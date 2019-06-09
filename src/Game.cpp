#include "Game.h"

Game::Game()
{
    //model = new Models::Cube();
    truck = new Truck();
}

Game::~Game()
{
    //model->~Cube();
    truck->~Truck();
    //delete model;
    delete truck;
}


void Game::draw(){

    /*M = glm::mat4(1.0f);
    M = glm::translate(M,glm::vec3(0.0f,0.0f,-2.0f));

    sp->use();
    glUniformMatrix4fv(sp->u("P"),1,false,glm::value_ptr(P));
    glUniformMatrix4fv(sp->u("V"),1,false,glm::value_ptr(V));
    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
    glUniform4f(sp->u("color"),0.0f,1.0f,1.0f,1.0f);
    glUniform1i(sp->u("pod"),0);
    glUniform4f(sp->u("lightPos"),-1.0f,-5.0f,-25.0f,1.0f);
    glUniform4fv(sp->u("lightPos2"),1,glm::value_ptr(glm::vec4(ob_position,1.0f)));

    model->drawSolid();*/

    truck->draw_all(P,V);

}

void Game::init(GLFWwindow *window){

}

void Game::key_callback(int key, int scancode, int action, int mods){
    if(action == GLFW_PRESS){
        if(key==GLFW_KEY_UP)
            u_r=1;
        if(key==GLFW_KEY_DOWN)
            d_r=1;
        if(key==GLFW_KEY_LEFT)
            l_r=1;
        if(key==GLFW_KEY_RIGHT)
            r_r=1;
        if(key==GLFW_KEY_W){
            truck->acceleration = glm::vec3(1.0f,0.0f,0.0f);
            truck->b_acc = true;
        }
        if(key==GLFW_KEY_A){
            truck->turn_l = 1;
        }
        if(key==GLFW_KEY_D){
            truck->turn_r = 1;
        }
    }
    if(action == GLFW_RELEASE){
        if(key==GLFW_KEY_UP)
            u_r=0;
        if(key==GLFW_KEY_DOWN)
            d_r=0;
        if(key==GLFW_KEY_LEFT)
            l_r=0;
        if(key==GLFW_KEY_RIGHT)
            r_r=0;
        if(key==GLFW_KEY_W){
            truck->acceleration = glm::vec3(0.0f,0.0f,0.0f);
            truck->b_acc = false;
        }
        if(key==GLFW_KEY_A){
            truck->turn_l = 0;
        }
        if(key==GLFW_KEY_D){
            truck->turn_r = 0;
        }
    }
}

void Game::cursor_position_callback(double xpos, double ypos){
    dx = xpos-xcur;
    dy = ypos-ycur;
    xcur = xpos;
    ycur = ypos;

    //printf("%f %f %f\n",lukat.x,lukat.y,lukat.z);
    dx = dx/1500 * PI * 2;
    dy = dy/1500 * PI * 2;
    //printf("%f %f\n",dx,dy);
    plukat = lukat - ob_position;
    pl = glm::vec4(plukat,1.0f);

    pl = glm::rotate(glm::mat4(1.0f),float(dx),-nose)*pl;
    plukat = glm::vec3(pl.x,pl.y,pl.z);
    pl = glm::rotate(glm::mat4(1.0f),float(dy),glm::cross(nose,plukat))*pl;
    glm::vec4 pn = glm::vec4(nose,1.0f);
    pn = glm::rotate(glm::mat4(1.0f),float(dy),glm::cross(nose,plukat))*pn;
    plukat = glm::vec3(pl.x,pl.y,pl.z);
    lukat = plukat + ob_position;
    //lukat = glm::normalize(lukat);
    //nose = glm::vec3(pn.x,pn.y,pn.z);
    //nose = glm::normalize(nose);

    V = glm::lookAt(ob_position,lukat,nose);
}

void Game::update(double time){
    glfwSetTime(0);

    angle_h=(r_r-l_r)*time;
    angle_v=(u_r-d_r)*time;

    pom_sum=glm::vec3(angle_v*(lukat.x - ob_position.x),angle_v*(lukat.y - ob_position.y),0.0f);
    ob_position+=pom_sum;
    lukat+=pom_sum;
    pom_sum=glm::vec3(angle_h*glm::cross(lukat - ob_position,nose).x,
                           angle_h*glm::cross(lukat - ob_position,nose).y,0.0f);
    ob_position+=pom_sum;
    lukat+=pom_sum;
    V=glm::lookAt(ob_position,lukat,nose);

    truck->update(time);
}
