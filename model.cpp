#include "model.h"

namespace Models {
    Model::Model(const char* file_name, unsigned texture_id) {
        ObjectLoader::load_object(file_name, vertices, texCoords, normals, &vertexCount);
        tex_id = texture_id;
        hitbox        = new glm::vec4[4];
        hitbox_normal = new glm::vec4[4];
    }

    Model::~Model() {
        delete [] vertices;
        delete [] normals;
        delete [] texCoords;
        delete [] hitbox;
        delete [] hitbox_normal;
    }

    void Model::drawSolid() {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glVertexAttribPointer(0,4,GL_FLOAT,false,0,vertices);
        glVertexAttribPointer(1,4,GL_FLOAT,false,0,normals);
        glVertexAttribPointer(2,2,GL_FLOAT,false,0,texCoords);

        glActiveTexture(GL_TEXTURE0 + tex_id);
        glBindTexture(GL_TEXTURE_2D, Global::tex[tex_id]);
        glUniform1i(sp->u("tex"), tex_id);
        glDrawArrays(GL_TRIANGLES,0,vertexCount);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
    }

	void Model::drawWire() {
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		drawSolid();

		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}

	float abs(float a) {
        if(a>0) return a;
        else return -a;
	}

	// Oblicza hitbox modelu
	void Model::getHitbox(float max_height) {
        for (int i=0; i<4; ++i)
            hitbox[0].x=hitbox[0].z=0;
        // Przegladamy wierzcholki i szukamy wierzcholkow czworokata, ktory powstalby gdybysmy "sprasowali" obiekt od gory
        for(unsigned long i=0; i<vertexCount; ++i) {
            if(vertices[i].y <= max_height) { // Jak model ma wysoko polozone np. lusterka, ktorymi i tak nie zachaczy
                // +x +z
                if(vertices[i].x > 0 && vertices[i].z > 0) {
                    if(vertices[i].x > hitbox[0].x)
                        hitbox[0].x = vertices[i].x;
                    if(vertices[i].z > hitbox[0].z)
                        hitbox[0].z = vertices[i].z;
                }
                // -x +z
                if(vertices[i].x < 0 && vertices[i].z > 0) {
                    if(vertices[i].x < hitbox[1].x)
                        hitbox[1].x = vertices[i].x;
                    if(vertices[i].z > hitbox[1].z)
                        hitbox[1].z = vertices[i].z;
                }
                // -x -z
                if(vertices[i].x < 0 && vertices[i].z < 0) {
                    if(vertices[i].x < hitbox[2].x)
                        hitbox[2].x = vertices[i].x;
                    if(vertices[i].z < hitbox[2].z)
                        hitbox[2].z = vertices[i].z;
                }
                // +x -z
                if(vertices[i].x > 0 && vertices[i].z < 0) {
                    if(vertices[i].x > hitbox[3].x)
                        hitbox[3].x = vertices[i].x;
                    if(vertices[i].z < hitbox[3].z)
                        hitbox[3].z = vertices[i].z;
                }

            }
        }
        //for (int i=0; i<4; ++i)printf("%f,%f\n",hitbox[i].x,hitbox[i].z);
        // Ustawienie y i w
        for (int i=0; i<4; ++i) {
            hitbox[i].y = 0.0f;
            hitbox[i].w = 1.0f;
        }

        // Wyznaczenie wektorów normalnych krawedzi hitboxa
        for (int i=0; i<4; ++i) {
            hitbox_normal[i] = hitbox[i<3 ? i+1 : 0] - hitbox[i];
            // hitbox[i<3 ? i+1 : 0] - Nastepny wierzcholek
            float tmp;
            // Wyznaczenie wektora prostopadlego do krawedzi = wektora normalnego
            tmp = hitbox_normal[i].x;
            hitbox_normal[i].x = hitbox_normal[i].z;
            hitbox_normal[i].z = -tmp;
            hitbox_normal[i].y = 0.0f;
            hitbox_normal[i].w = 1.0f;
            hitbox_normal[i] = glm::normalize(hitbox_normal[i]);
        }
        //for (int i=0; i<4; ++i) printf("%f,%f\n",hitbox_normal[i].x,hitbox_normal[i].z);
	}
}
