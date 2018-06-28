//
//  mesh.hpp
//  render
//
//  Created by liu on 2018/6/26.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef mesh_hpp
#define mesh_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "assimp/Importer.hpp"
#include "texture.hpp"

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int VAO;
    
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(unsigned int programid);
    
private:
    void setup_mesh();
private:
    unsigned int VBO, EBO;
};
#endif /* mesh_hpp */
