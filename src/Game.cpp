#include "Game.h"

Game::Game()
{
    truck = new Truck();
    floor = new FloorObject(glm::vec3(0.0f,0.0f,0.0f));
    barrier_obstacles.push_back(BarrierObstacle(glm::vec3(20.0f, 0.0f, 0.0f)));
    barrier_obstacles.push_back(BarrierObstacle(glm::vec3(20.0f, 0.0f, 20.0f)));
    sky = new Sky(ob_position);
    winning_platform = new WinningPlatform(glm::vec3(40.0f,0.1f,00.0f));
}

Game::~Game()
{
    //truck->~Truck();
    delete truck;
    delete floor;
    delete winning_platform;
}

void Game::draw(){
    truck->draw_all(P,V);
    floor->draw(P,V);
    for (std::vector<BarrierObstacle>::size_type i = 0; i != barrier_obstacles.size(); ++i) {
        barrier_obstacles[i].draw(P,V);
    }
    sky->draw(P,V);
    winning_platform->draw(P,V);
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
            truck->acceleration = 1.0f;
            truck->b_acc = true;
        }
        if(key==GLFW_KEY_S){
            truck->acceleration = -1.0f;
            truck->b_acc = false;
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
            truck->acceleration = 0.0f;
            truck->b_acc = false;
        }
        if(key==GLFW_KEY_S){
            truck->acceleration = 0.0f;
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

void Game::cursor_position_callback(double xpos, double zpos){
    dx = xpos-xcur;
    dz = zpos-zcur;
    xcur = xpos;
    zcur = zpos;

    //printf("%f %f %f\n",lukat.x,lukat.y,lukat.z);
    dx = dx/1500 * PI * 2;
    dz = dz/1500 * PI * 2;
    //printf("%f %f\n",dx,dy);
    plukat = lukat - ob_position;
    pl = glm::vec4(plukat,1.0f);

    pl = glm::rotate(glm::mat4(1.0f),float(dx),-nose)*pl;
    plukat = glm::vec3(pl.x,pl.y,pl.z);
    pl = glm::rotate(glm::mat4(1.0f),float(dz),glm::cross(nose,plukat))*pl;
    glm::vec4 pn = glm::vec4(nose,1.0f);
    pn = glm::rotate(glm::mat4(1.0f),float(dz),glm::cross(nose,plukat))*pn;
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

    pom_sum=glm::vec3(angle_v*(lukat.x - ob_position.x),0.0f,angle_v*(lukat.z - ob_position.z));
    ob_position+=pom_sum;
    lukat+=pom_sum;
    pom_sum=glm::vec3(angle_h*glm::cross(lukat - ob_position,nose).x,0.0f,
                           angle_h*glm::cross(lukat - ob_position,nose).z);
    ob_position+=pom_sum;
    lukat+=pom_sum;
    V=glm::lookAt(ob_position,lukat,nose);
    truck->update(time);

    sky->update(ob_position);

    // Check collisions
    static int i=1;
    bool collision_detected = false;
    for (std::vector<BarrierObstacle>::size_type i = 0; i != barrier_obstacles.size(); ++i) {
        collision_detected |= truck->is_collision(&barrier_obstacles[i]);
    }
    if(collision_detected) {
        printf("Kolizja %d\n",i++);
        truck->reset_pos();
    }
    static int j=1;
    if(winning_platform->is_inside(truck)) {
        printf("Gratulacje po raz %d!\n",j++);
        truck->reset_pos();
    }
}
