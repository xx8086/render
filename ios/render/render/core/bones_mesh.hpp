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
#include "math.hpp"

class BonesMesh{
public:
    BonesMesh();
    ~BonesMesh();
public:
    bool loadmesh(const char*);
    void render();
    unsigned int num_bones()const{return _num_bones;};
    void bone_transform(float seconds, std::vector<Mat4f>& transforms);
private:
    #define NUM_BONES_PER_VEREX 4
    struct BoneInfo{
        Mat4f bone_offset;
        Mat4f final_transformation;
        BoneInfo(){
            bone_offset.SetZero();
            final_transformation.SetZero();
        }
    };
    struct VertexBonedata{
        unsigned int ids[NUM_BONES_PER_VEREX] = {0};
        float weights[NUM_BONES_PER_VEREX] = {0};
        void add_bonedata(unsigned int, float);
    };
    struct MeshEntry{
        unsigned int num_indices = 0;
        unsigned int base_vertex = 0;
        unsigned int base_index = 0;
        unsigned int material_index = 0;
    };
    enum VB_TYPES {
        INDEX_BUFFER,
        POS_VB,
        NORMAL_VB,
        TEXCOORD_VB,
        BONE_VB,
        NUM_VBs
    };
    
private:
    void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    unsigned int FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
    unsigned int FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
    unsigned int FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
    const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const char* nodename);
    void ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const Mat4f& ParentTransform);
    bool InitFromScene(const aiScene* pScene, const char* filename);
    void InitMesh(uint MeshIndex,
                  const aiMesh* paiMesh,
                  std::vector<Vec3f>& Positions,
                  std::vector<Vec3f>& Normals,
                  std::vector<Vec2f>& TexCoords,
                  std::vector<VertexBonedata>& Bones,
                  std::vector<unsigned int>& Indices);
    void LoadBones(unsigned int MeshIndex, const aiMesh* paiMesh, std::vector<VertexBonedata>& Bones);
    bool InitMaterials(const aiScene* pScene, const char* filename);
    void clear();
private:
    unsigned int _num_bones = 0;
    unsigned int _vao = 0;
    unsigned int _vbos[NUM_VBs] = {0};
    std::vector<MeshEntry> _entries;
    std::vector<TexureGl*> _textures;
    std::map<std::string, unsigned int> _bones_map;
    std::vector<BoneInfo> _bones_info;
    Mat4f _global_inverse_transform;
    Assimp::Importer _importer;
    const aiScene* _scene;
};

#endif /* bones_mesh_hpp */
