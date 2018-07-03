//
//  bones_mesh.hpp
//  render
//
//  Created by liu on 2018/6/27.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef bones_mesh_hpp
#define bones_mesh_hpp

#include <stdio.h>
#include "texture.hpp"
#include <vector>
#include <map>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "type_render.h"

class BonesMesh{
public:
    BonesMesh();
    ~BonesMesh();
    
    bool load_mesh(const std::string& Filename);
    void render();
    unsigned int num_bones() const{ return _num_bones;}
    void bone_transform(float, std::vector<Mat4f>&);
    
private:
#define NUM_BONES_PER_VEREX 4
    
    struct BoneInfo{
        Mat4f BoneOffset;
        Mat4f FinalTransformation;
        
        BoneInfo(){
            BoneOffset.SetZero();
            FinalTransformation.SetZero();
        }
    };
    
    struct VertexBoneData
    {
        unsigned int ids[NUM_BONES_PER_VEREX];
        float weights[NUM_BONES_PER_VEREX];
        VertexBoneData(){
            reset();
        };
        
        void reset(){
            memset(ids, 0, sizeof(ids));
            memset(weights, 0, sizeof(weights));
        }
        
        void add_bone_data(unsigned int, float);
    };
    
    void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    uint find_scaling(float, const aiNodeAnim*);
    uint find_rotation(float, const aiNodeAnim*);
    uint find_position(float, const aiNodeAnim*);
    const aiNodeAnim* find_node_anim(const aiAnimation*, const std::string);
    void read_node_heirarchy(float, const aiNode*, const Matrix4f&);
    bool load_scene(const aiScene*, const std::string&);
    void load_mesh(unsigned int,
                  const aiMesh*,
                  std::vector<Vec3f>&,
                  std::vector<Vec3f>&,
                  std::vector<Vec2f>&,
                  std::vector<VertexBoneData>&,
                  std::vector<unsigned int>&);
    void load_bones(unsigned int, const aiMesh*, std::vector<VertexBoneData>&);
    bool load_materials(const aiScene*, const std::string&);
    void clear();
    
#define INVALID_MATERIAL 0xFFFFFFFF
    
    enum VB_TYPES {
        INDEX_BUFFER,
        POS_VB,
        NORMAL_VB,
        TEXCOORD_VB,
        BONE_VB,
        NUM_VBs
    };
    
    GLuint _vao;
    GLuint _vbos[NUM_VBs];
    
    struct MeshEntry {
        MeshEntry()
        {
            num_indices    = 0;
            base_vertex    = 0;
            base_index     = 0;
            material_index = INVALID_MATERIAL;
        }
        
        unsigned int num_indices;
        unsigned int base_vertex;
        unsigned int base_index;
        unsigned int material_index;
    };
    
    std::vector<MeshEntry> _entries;
    std::vector<TextureGl*> _textures;
    std::map<std::string,unsigned int> _bone_mapping;
    unsigned int _num_bones;
    std::vector<BoneInfo> _bone_info;
    Mat4f _global_inverse_transform;
    
    const aiScene* _scene;
    Assimp::Importer _importer;
};

#endif /* bones_mesh_hpp */
