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

	void Model::getHitbox(glm::vec4* &hitbox_arg, float max_height) {
        hitbox_arg = new glm::vec4[2];
	    float x1,x2;
	    float z1,z2;
	    x1=x2=0;
	    z1=z2=0;
        // Przegladamy wierzcholki i szukamy wierzcholkow czworokata, ktory powstalby gdybysmy "sprasowali" obiekt od gory
        // Patrzymy symetrycznie wokol osi x oraz z
        for(int i=0; i<vertexCount; ++i) {
            if(vertices[i].y <= max_height) { // Jak model ma wysoko polozone np. lusterka, ktorymi i tak nie zachaczy
                if(vertices[i].x > x1)
                    x1 = vertices[i].x;
                if(vertices[i].x < x2)
                    x2 = vertices[i].x;
                if(vertices[i].z > z1)
                    z1 = vertices[i].z;
                if(vertices[i].z < z2)
                    z2 = vertices[i].z;
            }
        }
        printf("%f,%f,%f,%f\n",x1,z1,x2,z2);
        // Przywrocenie znaku wierzcholkom
        hitbox_arg[0].x = x1;
        hitbox_arg[0].z = z1;
        hitbox_arg[1].x = x2;
        hitbox_arg[1].z = z2;
        // Ustawienie y i w
        hitbox_arg[0].y=0.0f;
        hitbox_arg[1].y=0.0f;
        hitbox_arg[0].w=1.0f;
        hitbox_arg[1].w=1.0f;
	}
}
