#ifndef LOADOBJECT_H
#define LOADOBJECT_H

#include <glm/glm.hpp>
#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>

namespace ObjectLoader {
    bool load_object(const char* file_name, glm::vec4* &vertices, glm::vec2* &tex, glm::vec4* &vert_normals, unsigned long *vertex_count);
};
#endif //LOADOBJECT_H
