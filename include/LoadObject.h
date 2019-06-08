#ifndef LOADOBJECT_H
#define LOADOBJECT_H

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

bool load_object(char* file_name, glm::vec3 *vertices, glm::vec2 *tex, glm::vec3 *normals);


#endif LOADOBJECT_H
