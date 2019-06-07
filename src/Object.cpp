#include "Object.h"

Object::Object(glm::vec3 trans, float scal, float direction)
{
    cube = new Models::Cube();
    angle_dr = angle_rot = 0;
    translate = glm::vec3(trans);
    scale = scal;
    angle_dr = direction;
}

Object::~Object()
{
    cube->~Cube();
    delete cube;
}

void Object::draw(glm::mat4 P, glm::mat4 V, glm::mat4 M){

    M = glm::translate(M,translate);
    M = glm::rotate(M,angle_dr,glm::vec3(0.0f,0.0f,1.0f));
    if(angle_rot!=0)
        M = glm::rotate(M,angle_rot,glm::vec3(0.0f,1.0f,0.0f));
    M = glm::scale(M,glm::vec3(scale,scale,scale));

    //sp->use();
    //glUniformMatrix4fv(sp->u("P"),1,false,glm::value_ptr(P));
    //glUniformMatrix4fv(sp->u("V"),1,false,glm::value_ptr(V));
    glUniformMatrix4fv(sp->u("M"),1,false,glm::value_ptr(M));
    glUniform4f(sp->u("color"),0.0f,1.0f,1.0f,1.0f);
    //glUniform1i(sp->u("pod"),0);
    //glUniform4f(sp->u("lightPos"),-1.0f,-5.0f,-25.0f,1.0f);
    //glUniform4fv(sp->u("lightPos2"),1,glm::value_ptr(glm::vec4(M[3][0]-translate.x, M[3][1]-translate.y,
     //                                                          M[3][2]-translate.z, 1.0f)));

    cube->drawSolid();
}
