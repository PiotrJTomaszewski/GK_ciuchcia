#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "LoadObject.h"


namespace Models {

	class Model {
		public:
		    Model(const char* file_name);
		    ~Model();
            unsigned vertexCount;
			glm::vec4 *vertices;
			glm::vec4 *normals;
			glm::vec2 *texCoords;
			// Blender eksportuje do obj normalne wierzcholkow i scian razem, wiec zeby wylaczyc wygladzanie trzeba by sie dodatkowo napracowac, co nie ma sensu :)
			void drawSolid();
			void drawWire();
	};
}

#endif
