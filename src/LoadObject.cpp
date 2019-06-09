#include "LoadObject.h"

//TODO: Przerobiæ na wspó³rzêdne homogeniczne
bool load_object(const char* file_name, glm::vec4* &vertices, glm::vec2* &tex, glm::vec4* &normals, unsigned *vertex_count) {
    std::vector<glm::vec3> tmp_vertices;
    std::vector<glm::vec2> tmp_tex;
    std::vector<glm::vec3> tmp_normal;
    std::vector<unsigned>  vert_id, tex_id, norm_id;
    int tex_count, norm_count;
    std::fstream model_file (file_name, std::ios::in);
    std::string line;
    std::stringstream ss;
    char a; // first char (or 2) in line is a letter and we don't need it
    if (model_file.is_open()) {
        // Reading data
        while(getline(model_file,line)) { // while not EOF
            if (line[0] == 'v') {
                if (line[1] == 't') {
                    // vt -  texture coordinate of one vertex
                    glm::vec2 tex;
                    ss << line;
                    ss >> a >> a >> tex.x >> tex.y;
                    tmp_tex.push_back(tex);
                    ss.clear();

                }
                else if (line[1] == 'n') {
                    // vn - normal of one vertex
                    glm::vec3 normal;
                    ss << line;
                    ss >> a >> a >> normal.x >> normal.y >> normal.z;
                    tmp_normal.push_back(normal);
                    ss.clear();
                }
                else {
                    // v - vertex
                    glm::vec3 vertex;
                    ss << line;
                    ss >> a >> vertex.x >> vertex.y >> vertex.z;
                    ss.clear();
                    tmp_vertices.push_back(vertex);
                }
            }
            else if (line[0] == 'f') {
                // f - face
                unsigned tmp_vert_id[3], tmp_tex_id[3], tmp_norm_id[3];
                ss << line;
                ss >> a >> tmp_vert_id[0] >> a >> tmp_tex_id[0] >> a >> tmp_norm_id[0] >> tmp_vert_id[1] >> a >> tmp_tex_id[1] >> a >> tmp_norm_id[1] >> tmp_vert_id[2] >> a >> tmp_tex_id[2] >> a >> tmp_norm_id[2];
                //for(int i=0; i<3; ++i)std::cout << tmp_vert_id[i] << " " << tmp_tex_id[i] << " " << tmp_norm_id[i] << std::endl;
                ss.clear();
                for (int i=0; i<3; ++i) {
                    vert_id.push_back(tmp_vert_id[i]-1); // in .obj indexes start from 1
                    tex_id.push_back(tmp_tex_id[i]-1);
                    norm_id.push_back(tmp_norm_id[i]-1);
                }
            }
        }
        model_file.close();

        // Interpreting data
        // Vertices
        *vertex_count = vert_id.size();
        vertices = new glm::vec4[*vertex_count];
        int j=0;
        for (auto &index : vert_id) {
            //std::cout << index << " " << tmp_vertices[index].x<< std::endl;
            vertices[j].x = tmp_vertices[index].x;
            vertices[j].y = tmp_vertices[index].y;
            vertices[j].z = tmp_vertices[index].z;
            vertices[j].w = 1.f;
            ++j;
        }
        // Texture coords
        tex_count = tex_id.size();
        tex = new glm::vec2[tex_count];
        j=0;
        for (auto &index : tex_id) {
            tex[j].x = tmp_tex[index].x;
            tex[j].y = tmp_tex[index].y;
            ++j;
        }
        // Vertex normals
        norm_count = norm_id.size();
        normals = new glm::vec4[norm_count];
        j=0;
        for (auto &index : norm_id) {
            normals[j].x = tmp_normal[index].x;
            normals[j].y = tmp_normal[index].y;
            normals[j].z = tmp_normal[index].z;
            normals[j].w = 0.f;
        }
    }
    else {
        perror("Error while opening model file");

        return -1;
    }
    return 0;
}
