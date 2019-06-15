#include "model.h"

namespace Models {
    Model::Model(const char* file_name, unsigned texture_id) {
        ObjectLoader::load_object(file_name, vertices, texCoords, normals, &vertexCount);
        tex_id = texture_id;
    }

    Model::~Model() {
        delete [] vertices;
        delete [] normals;
        delete [] texCoords;
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

	void Model::getHitbox(glm::vec4* &hitbox_arg) {
        hitbox_arg = new glm::vec4[2];
	    glm::vec2 hitbox[4];
        for(int i=0; i<4; ++i) {
            hitbox[i].x = 0;
            hitbox[i].y = 0; // reprezentuje wspolrzedna z w swiecie
        }
        // Przegladamy wierzcholki i szukamy wierzcholkow czworokata, ktory powstalby gdybysmy "sprasowali" obiekt od gory
        int which_edge=0;
        for(int i=0; i<vertexCount; ++i) {
            if(vertices[i].z>0)
                which_edge = 2;
            else
                which_edge = 0;
            if(vertices[i].x>0)
                ++which_edge;
            if(abs(vertices[i].x)>hitbox[which_edge].x)
                hitbox[which_edge].x = abs(vertices[i].x);
            if(abs(vertices[i].z)>hitbox[which_edge].y)
                hitbox[which_edge].y = abs(vertices[i].z);
        }
        // Sprowadzenie do 2 punktow
        hitbox_arg[0].x = hitbox[0].x>hitbox[2].x ? hitbox[0].x : hitbox[2].x;
        hitbox_arg[0].y = hitbox[0].y>hitbox[1].y ? hitbox[0].y : hitbox[1].y;
        hitbox_arg[1].x = hitbox[1].x>hitbox[3].x ? hitbox[1].x : hitbox[3].x;
        hitbox_arg[1].y = hitbox[3].y>hitbox[2].y ? hitbox[3].y : hitbox[2].y;
        // Przywrocenie znaku wspolrzednym
        hitbox_arg[0].x = -hitbox_arg[0].x;
        hitbox_arg[0].y = -hitbox_arg[0].z;
        // Ustawienie y i w
        hitbox_arg[0].z=0.0f;
        hitbox_arg[1].z=0.0f;
        hitbox_arg[0].w=1.0f;
        hitbox_arg[1].w=1.0f;
	}
}
