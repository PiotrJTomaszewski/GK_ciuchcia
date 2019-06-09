#ifndef LOADOBJECT_H
#define LOADOBJECT_H

#include <glm/glm.hpp>
#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>

bool load_object(const char* file_name, glm::vec4* &vertices, glm::vec2* &tex, glm::vec4* &normals, unsigned *vertex_count);


#endif //LOADOBJECT_H
