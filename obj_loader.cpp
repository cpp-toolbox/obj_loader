#include "obj_loader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

static void parse_face_vertex(const std::string &vertex, Face &f) {
    std::istringstream vss(vertex);
    std::string index;
    int indices[3] = {0, 0, 0};
    int i = 0;

    while (std::getline(vss, index, '/') && i < 3) {
        if (!index.empty()) {
            indices[i] = std::stoi(index) - 1; // OBJ indices are 1-based
        } else {
            indices[i] = -1;
        }
        i++;
    }

    f.vertex_indices.push_back(indices[0]);
    if (indices[1] >= 0)
        f.tex_coord_indices.push_back(indices[1]);
    if (indices[2] >= 0)
        f.normal_indices.push_back(indices[2]);
}

static void process_vertex_line(std::istringstream &iss, Mesh &mesh_data) {
    Vec3 v;
    iss >> v.x >> v.y >> v.z;
    mesh_data.vertices.push_back(v);
}

static void process_tex_coord_line(std::istringstream &iss, Mesh &mesh_data) {
    Vec2 vt;
    iss >> vt.u >> vt.v;
    mesh_data.tex_coords.push_back(vt);
}

static void process_normal_line(std::istringstream &iss, Mesh &mesh_data) {
    Vec3 vn;
    iss >> vn.x >> vn.y >> vn.z;
    mesh_data.normals.push_back(vn);
}

static void process_face_line(std::istringstream &iss, Mesh &mesh_data) {
    Face f;
    std::string vertex_data;

    while (iss >> vertex_data) {
        parse_face_vertex(vertex_data, f);
    }

    mesh_data.faces.push_back(f);
}

bool load_obj(const std::string &filename, Mesh &mesh_data) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            process_vertex_line(iss, mesh_data);
        } else if (prefix == "vt") {
            process_tex_coord_line(iss, mesh_data);
        } else if (prefix == "vn") {
            process_normal_line(iss, mesh_data);
        } else if (prefix == "f") {
            process_face_line(iss, mesh_data);
        }
    }

    file.close();
    print_mesh_info(mesh_data, filename);
    return true;
}

void print_mesh_info(const Mesh &mesh_data, const std::string &filename) {
    std::cout << "Loaded OBJ file: " << filename << std::endl;
    std::cout << "Vertices: " << mesh_data.vertices.size() << std::endl;
    std::cout << "Texture Coords: " << mesh_data.tex_coords.size() << std::endl;
    std::cout << "Normals: " << mesh_data.normals.size() << std::endl;
    std::cout << "Faces: " << mesh_data.faces.size() << std::endl;
}
