#include "Game.h"

Game::Game()
{
    srand(time(0));
    truck = new Truck();
    floor = new FloorObject(glm::vec3(0.0f,0.0f,0.0f));
    genarate_barriers();
    sky = new Sky(ob_position);
    for(j = -2; j<3; ++j){
        for(l = -3; l < 2; ++l){
            genarate_cars(glm::vec3(-3.5f,1.0f,22.8f)+glm::vec3(j*31.9f,0.0f,l*31.9f));
        }
    }
}

void Game::genarate_cars(glm::vec3 origin){
    for(k = 0; k< 5; ++k){
        if(!platform_generated && rand()%5) {
            // Jesli jeszcze nie ma, to umiesc platforme koncowa
            winning_platform = new WinningPlatform(glm::vec4(origin.x,0.01f,origin.z,1.0f),1.0f);
            platform_generated = true;
        }
        else {
            if(rand()%6==0){
                obstacles.push_back(CarObstacle(origin,1.3f,-PI/2));
            }
            if(rand()%6==0){
                obstacles.push_back(CarObstacle(origin+glm::vec3(7.5f,0.0f,0.0f),1.3f,PI/2));
            }
            origin+=glm::vec3(0.0f,0.0f,4.76f);
        }
    }
}

void Game::genarate_barriers() { // Umieszcza na skrzyzowaniach barierki
    for (int row=-3; row<3; ++row) {
        for (int col=-3; col<3; ++col) {
            if(rand()%3==0) {
                float direction = 1.0f/(rand()%20)*2.0f*PI; // Jakis losowy obrot
                barrier_obstacles.push_back(BarrierObstacle(glm::vec3(row*32.0f+16.0f, 0.0f, col*32.0f+16.0f), 1.0f, direction));
            }
        }
    }
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
    for(std::vector<Object>::size_type i = 0; i != obstacles.size(); ++i){
        obstacles[i].draw(P,V);
    }
    winning_platform->draw(P,V);
}

void Game::init(GLFWwindow *window){

}

void Game::key_callback(int key, int scancode, int action, int mods){
    if(action == GLFW_PRESS){
        if(!camera_static){
            if(key==GLFW_KEY_UP)
                u_r=1;
            if(key==GLFW_KEY_DOWN)
                d_r=1;
            if(key==GLFW_KEY_LEFT)
                l_r=1;
            if(key==GLFW_KEY_RIGHT)
                r_r=1;
        }
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
        if(key==GLFW_KEY_U){
            ob_position.y+=1.0f;
            lukat.y+=1.0f;
        }
        if(key==GLFW_KEY_Y){
            ob_position.y-=1.0f;
            lukat.y-=1.0f;
        }
        if(key==GLFW_KEY_P)
            camera_static = !camera_static;
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

void Game::update(double time, bool *nan_detected){
    glfwSetTime(0);

    if(!camera_static){
        angle_h=(r_r-l_r)*time;
        angle_v=(u_r-d_r)*time;

        pom_sum=glm::vec3(angle_v*(lukat.x - ob_position.x),0.0f,angle_v*(lukat.z - ob_position.z));
        ob_position+=pom_sum;
        lukat+=pom_sum;
        pom_sum=glm::vec3(angle_h*glm::cross(lukat - ob_position,nose).x,0.0f,
                               angle_h*glm::cross(lukat - ob_position,nose).z);
        ob_position+=pom_sum;
        lukat+=pom_sum;
    }
    else{
        ob_position = truck->translate + glm::vec3(0.0f,5.0f,0.0f);
        lukat = ob_position + glm::rotateY(glm::vec3(5.0f,0.0f,0.0f),truck->angle_dr);
    }
    V=glm::lookAt(ob_position,lukat,nose);
    truck->update(time);

    sky->update(ob_position);

    // Check collisions
    static int i=1;
    bool collision_detected = false;
    for (std::vector<BarrierObstacle>::size_type i = 0; i != barrier_obstacles.size(); ++i) {
        collision_detected |= truck->is_collision(&barrier_obstacles[i], nan_detected);
    }
    for(std::vector<CarObstacle>::size_type i = 0; i != obstacles.size(); ++i){
        collision_detected |= truck->is_collision(&obstacles[i], nan_detected);
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
