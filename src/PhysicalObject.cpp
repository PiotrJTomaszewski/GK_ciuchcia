#include "PhysicalObject.h"

PhysicalObject::PhysicalObject(glm::vec3 trans, float scal, float direction)
    :Object(trans, scal, direction)
{
    angle_dr = angle_rot = 0;
    translate = glm::vec3(trans);
    scale = scal;
    angle_dr = direction;
}

// Rzutuje na oœ i umieszcza min i max w minimum i maximum
void getMinMax(glm::vec4* verts, glm::vec4 axis, float* minimum, float* maximum) {
    *minimum = glm::dot(axis,verts[0]);
    *maximum = *minimum;
    for (int i=1; i<4; ++i) {
        float p = glm::dot(axis, verts[i]);
        if (p < *minimum)
            *minimum = p;
        else if (p > *maximum)
            *maximum = p;
    }
}

// Returns true if two hitbox rectangles overlap SAT
bool PhysicalObject::is_collision(PhysicalObject *object2) {
    glm::vec4 hitbox_vert[2][4];
    glm::vec4 hitbox_norm[2][4];
    // Wyliczenie aktualnych wspó³rzêdnych hitboxa
    for (int i=0; i<4; ++i) {
        hitbox_vert[0][i] = this->get_M() * this->get_hitbox(i);
        hitbox_vert[1][i] = object2->get_M() * object2->get_hitbox(i);
        hitbox_norm[1][i] = glm::normalize(this->get_M() * this->get_hitbox_normal(i));
        hitbox_norm[1][i] = glm::normalize(object2->get_M() * object2->get_hitbox_normal(i));
    }

    // Wyliczenie rzutowania na osie
    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            float min_p0, max_p0;
            float min_p1, max_p1;
            getMinMax(hitbox_vert[0],hitbox_norm[i][j],&min_p0,&max_p0);
            getMinMax(hitbox_vert[1],hitbox_norm[i][j],&min_p1,&max_p1);

            // Sprawdzenie czy projekcje na siebie nachodza
            if(max_p0 < min_p1 || max_p1 < min_p0)
                return false; // Jesli chociaz jedno rzutowanie sie nie pokrywa, to nie ma kolizji
        }
    }
    return true;
}
