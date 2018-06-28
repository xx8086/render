//
//  model.hpp
//  render
//
//  Created by liu on 2018/6/26.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef model_hpp
#define model_hpp

#include <stdio.h>
#include "mesh.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"

class Model
{
public:
    Model(std::string const &path, bool gamma = false);
    void Draw(unsigned int);
private:
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
    void loadModel(std::string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
private:
    std::vector<Texture> textures_loaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;
};


#endif /* model_hpp */
