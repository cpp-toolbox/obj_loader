#ifndef OBJ_LOADER_HPP
#define OBJ_LOADER_HPP

#include <vector>
#include <string>

struct Vec3 {
    float x, y, z;
};

struct Vec2 {
    float u, v;
};

struct Face {
    std::vector<int> vertex_indices;
    std::vector<int> tex_coord_indices;
    std::vector<int> normal_indices;
};

struct Mesh {
    std::vector<Vec3> vertices;
    std::vector<Vec2> tex_coords;
    std::vector<Vec3> normals;
    std::vector<Face> faces;
};

bool load_obj(const std::string &filename, Mesh &mesh_data);
void print_mesh_info(const Mesh &mesh_data, const std::string &filename);

#endif // OBJ_LOADER_HPP
