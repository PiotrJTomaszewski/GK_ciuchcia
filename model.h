#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "LoadObject.h"
#include "shaderprogram.h"
#include "globals.h"

namespace Models {

	class Model {
		public:
		    Model(const char* file_name, unsigned texture_id);
		    ~Model();
            unsigned vertexCount;
			glm::vec4 *vertices;
			glm::vec4 *normals;
			glm::vec2 *texCoords;
			glm::vec4 *hitbox;
			glm::vec4 *hitbox_normal;
            unsigned tex_id; // Id tekstury
			// Blender eksportuje do obj normalne wierzcholkow i scian razem, wiec zeby wylaczyc wygladzanie trzeba by sie dodatkowo napracowac, co nie ma sensu :)
			void drawSolid();
			void drawWire();
			static ShaderProgram *sp;
			void getHitbox(float max_height);
	};
}

#endif
