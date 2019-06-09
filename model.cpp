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
}
