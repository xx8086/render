//
//  bones_mesh.cpp
//  render
//
//  Created by liu on 2018/6/27.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include <OpenGLES/ES3/gl.h>
#include "bones_mesh.hpp"
#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)

#define POSITION_LOCATION    0
#define TEX_COORD_LOCATION   1
#define NORMAL_LOCATION      2
#define BONE_ID_LOCATION     3
#define BONE_WEIGHT_LOCATION 4

void BonesMesh::VertexBonedata::add_bonedata(unsigned int BoneID, float Weight)
{
    for (uint i = 0; i < ARRAY_SIZE_IN_ELEMENTS(ids); i++) {
        if (weights[i] == 0.0) {
            ids[i] = BoneID;
            weights[i] = Weight;
            return;
        }
    }
    
    assert(0);
}

BonesMesh::BonesMesh(){
}


BonesMesh::~BonesMesh(){
    Clear();
}


void BonesMesh::Clear()
{
    //for (uint i = 0; i < _textures.size(); i++) {
    //    SAFE_DELETE(_textures[i]);
    //}
    
    if (_vbos[0] != 0) {
        glDeleteBuffers(ARRAY_SIZE_IN_ELEMENTS(_vbos), _vbos);

    }
    
    if (_vao != 0) {
        glDeleteVertexArrays(1, &_vao);
        _vao = 0;
    }
}


bool BonesMesh::loadmesh(const char* filename)
{
    Clear();
    bool Ret = false;
    
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    glGenBuffers(ARRAY_SIZE_IN_ELEMENTS(_vbos), _vbos);
    _scene = _importer.ReadFile(filename, ASSIMP_LOAD_FLAGS);
    if (_scene) {
        _global_inverse_transform = Mat4f(_scene->mRootNode->mTransformation);
        _global_inverse_transform.Inverse();
        Ret = InitFromScene(_scene, filename);
    }
    else {
        printf("Error parsing '%s': '%s'\n", filename, _importer.GetErrorString());
    }
    
    // Make sure the VAO is not changed from the outside
    glBindVertexArray(0);
    return Ret;
}


bool BonesMesh::InitFromScene(const aiScene* scene, const char* filename)
{
    _entries.resize(scene->mNumMeshes);
    _textures.resize(scene->mNumMaterials);
    
    std::vector<Vec3f> Positions;
    std::vector<Vec3f> Normals;
    std::vector<Vec2f> TexCoords;
    std::vector<VertexBonedata> Bones;
    std::vector<unsigned int> Indices;
    
    unsigned int NumVertices = 0;
    unsigned int NumIndices = 0;
    
    // Count the number of vertices and indices
    for (uint i = 0; i < _entries.size(); i++) {
        _entries[i].material_index = scene->mMeshes[i]->mMaterialIndex;
        _entries[i].num_indices = scene->mMeshes[i]->mNumFaces * 3;
        _entries[i].base_vertex = NumVertices;
        _entries[i].base_index = NumIndices;
        
        NumVertices += scene->mMeshes[i]->mNumVertices;
        NumIndices += _entries[i].num_indices;
    }
    
    // Reserve space in the vectors for the vertex attributes and indices
    Positions.reserve(NumVertices);
    Normals.reserve(NumVertices);
    TexCoords.reserve(NumVertices);
    Bones.resize(NumVertices);
    Indices.reserve(NumIndices);
    
    // Initialize the meshes in the scene one by one
    for (uint i = 0; i < _entries.size(); i++) {
        const aiMesh* paiMesh = scene->mMeshes[i];
        InitMesh(i, paiMesh, Positions, Normals, TexCoords, Bones, Indices);
    }
    
    if (!InitMaterials(scene, filename)) {
        return false;
    }
    
    // Generate and populate the buffers with vertex attributes and the indices
    glBindBuffer(GL_ARRAY_BUFFER, _vbos[POS_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Positions[0]) * Positions.size(), &Positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(POSITION_LOCATION);
    glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, _vbos[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TexCoords[0]) * TexCoords.size(), &TexCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(TEX_COORD_LOCATION);
    glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, _vbos[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Normals[0]) * Normals.size(), &Normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(NORMAL_LOCATION);
    glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, _vbos[BONE_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Bones[0]) * Bones.size(), &Bones[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(BONE_ID_LOCATION);
    glVertexAttribIPointer(BONE_ID_LOCATION, 4, GL_INT, sizeof(VertexBonedata), (const GLvoid*)0);
    glEnableVertexAttribArray(BONE_WEIGHT_LOCATION);
    glVertexAttribPointer(BONE_WEIGHT_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBonedata), (const GLvoid*)16);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbos[INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
    
    return true;//GLCheckError();
}


void BonesMesh::InitMesh(uint MeshIndex,
                         const aiMesh* paiMesh,
                         std::vector<Vec3f>& Positions,
                         std::vector<Vec3f>& Normals,
                         std::vector<Vec2f>& TexCoords,
                         std::vector<VertexBonedata>& Bones,
                         std::vector<unsigned int>& Indices)
{
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
    
    // Populate the vertex attribute vectors
    for (uint i = 0; i < paiMesh->mNumVertices; i++) {
        const aiVector3D* pPos = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
        const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
        
        Positions.emplace_back(Vec3f(pPos->x, pPos->y, pPos->z));
        Normals.emplace_back(Vec3f(pNormal->x, pNormal->y, pNormal->z));
        TexCoords.emplace_back(Vec2f(pTexCoord->x, pTexCoord->y));
    }
    
    LoadBones(MeshIndex, paiMesh, Bones);
    
    // Populate the index buffer
    for (uint i = 0; i < paiMesh->mNumFaces; i++) {
        const aiFace& Face = paiMesh->mFaces[i];
        assert(Face.mNumIndices == 3);
        Indices.push_back(Face.mIndices[0]);
        Indices.push_back(Face.mIndices[1]);
        Indices.push_back(Face.mIndices[2]);
    }
}


void BonesMesh::LoadBones(unsigned int MeshIndex, const aiMesh* pMesh, std::vector<VertexBonedata>& Bones)
{
    for (unsigned int i = 0; i < pMesh->mNumBones; i++) {
        unsigned int BoneIndex = 0;
        std::string BoneName(pMesh->mBones[i]->mName.data);
        
        if (_bones_map.find(BoneName) == _bones_map.end()) {
            // Allocate an index for a new bone
            BoneIndex = _num_bones;
            _num_bones++;
            BoneInfo bi;
            _bones_info.push_back(bi);
            _bones_info[BoneIndex].bone_offset = Mat4f(pMesh->mBones[i]->mOffsetMatrix);
            _bones_map[BoneName] = BoneIndex;
        }
        else {
            BoneIndex = _bones_map[BoneName];
        }
        
        for (uint j = 0; j < pMesh->mBones[i]->mNumWeights; j++) {
            uint VertexID = _entries[MeshIndex].base_vertex + pMesh->mBones[i]->mWeights[j].mVertexId;
            float Weight = pMesh->mBones[i]->mWeights[j].mWeight;
            Bones[VertexID].add_bonedata(BoneIndex, Weight);
        }
    }
}


bool BonesMesh::InitMaterials(const aiScene* pScene, const char* filename)
{
    // Extract the directory part from the file name
    std::string strfilename(filename);
    std::string::size_type SlashIndex = strfilename.find_last_of("/");
    std::string dir;
    
    if (SlashIndex == std::string::npos) {
        dir = ".";
    }
    else if (SlashIndex == 0) {
        dir = "/";
    }
    else {
        dir = strfilename.substr(0, SlashIndex);
    }
    
    bool Ret = true;
    
    // Initialize the materials
    for (uint i = 0; i < pScene->mNumMaterials; i++) {
        const aiMaterial* pMaterial = pScene->mMaterials[i];
        _textures[i] = nullptr;
        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString Path;
            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path,
                                      nullptr, nullptr, nullptr, nullptr, nullptr) == AI_SUCCESS) {
                std::string p(Path.data);
                
                if (p.substr(0, 2) == ".\\") {
                    p = p.substr(2, p.size() - 2);
                }
                
                std::string full_path = dir + "/" + p;
                _textures[i] = new TexureGl;
                
                if (!_textures[i]->load_texture(full_path)) {
                    printf("Error loading texture '%s'\n", full_path.c_str());
                    delete _textures[i];
                    _textures[i] = nullptr;
                    Ret = false;
                }
                else {
                    printf("%d - loaded texture '%s'\n", i, full_path.c_str());
                }
            }
        }
    }
    
    return Ret;
}


void BonesMesh::render()
{
    glBindVertexArray(_vao);
    
    for (uint i = 0; i < _entries.size(); i++) {
        const uint MaterialIndex = _entries[i].material_index;
        
        assert(MaterialIndex < _textures.size());
        
        if (_textures[MaterialIndex]) {
            _textures[MaterialIndex]->bind(GL_TEXTURE0);
        }
        
        /*
         glDrawElementsBaseVertex(GL_TRIANGLES,
         _entries[i].num_indices,
         GL_UNSIGNED_INT,
         (void*)(sizeof(uint) * _entries[i].base_index),
         _entries[i].base_vertex);
         */
        glDrawElementsInstanced(GL_TRIANGLES,
                                 _entries[i].num_indices,
                                 GL_UNSIGNED_INT,
                                 (void*)(sizeof(uint) * _entries[i].base_index),
                                 _entries[i].base_vertex);
    }
    
    glBindVertexArray(0);
}


uint BonesMesh::FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    for (uint i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) {
        if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
            return i;
        }
    }
    
    assert(0);
    
    return 0;
}


uint BonesMesh::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    assert(pNodeAnim->mNumRotationKeys > 0);
    
    for (uint i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) {
        if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
            return i;
        }
    }
    
    assert(0);
    
    return 0;
}


uint BonesMesh::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    assert(pNodeAnim->mNumScalingKeys > 0);
    
    for (uint i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) {
        if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
            return i;
        }
    }
    
    assert(0);
    
    return 0;
}


void BonesMesh::CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    if (pNodeAnim->mNumPositionKeys == 1) {
        Out = pNodeAnim->mPositionKeys[0].mValue;
        return;
    }
    
    uint PositionIndex = FindPosition(AnimationTime, pNodeAnim);
    uint NextPositionIndex = (PositionIndex + 1);
    assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
    float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
    float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
    const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
    aiVector3D Delta = End - Start;
    Out = Start + Factor * Delta;
}


void BonesMesh::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    // we need at least two values to interpolate...
    if (pNodeAnim->mNumRotationKeys == 1) {
        Out = pNodeAnim->mRotationKeys[0].mValue;
        return;
    }
    
    uint RotationIndex = FindRotation(AnimationTime, pNodeAnim);
    uint NextRotationIndex = (RotationIndex + 1);
    assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
    float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
    float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
    const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
    aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
    Out = Out.Normalize();
}


void BonesMesh::CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    if (pNodeAnim->mNumScalingKeys == 1) {
        Out = pNodeAnim->mScalingKeys[0].mValue;
        return;
    }
    
    uint ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
    uint NextScalingIndex = (ScalingIndex + 1);
    assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
    float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
    float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
    const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
    aiVector3D Delta = End - Start;
    Out = Start + Factor * Delta;
}


void BonesMesh::ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const Mat4f& ParentTransform)
{
    std::string NodeName(pNode->mName.data);
    const aiAnimation* pAnimation = _scene->mAnimations[0];
    Mat4f NodeTransformation = pNode->mTransformation;
    const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName.c_str());
    
    if (pNodeAnim) {
        // Interpolate scaling and generate scaling transformation matrix
        aiVector3D Scaling;
        CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
        Mat4f ScalingM;
        ScalingM.InitScaleTransform(Scaling.x, Scaling.y, Scaling.z);
        
        // Interpolate rotation and generate rotation transformation matrix
        aiQuaternion RotationQ;
        CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
        Matrix4f RotationM = Matrix4f(RotationQ.GetMatrix());
        
        // Interpolate translation and generate translation transformation matrix
        aiVector3D Translation;
        CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
        Matrix4f TranslationM;
        TranslationM.InitTranslationTransform(Translation.x, Translation.y, Translation.z);
        
        // Combine the above transformations
        NodeTransformation = TranslationM * RotationM * ScalingM;
    }
    
    Matrix4f GlobalTransformation = ParentTransform * NodeTransformation;
    if (_bones_map.find(NodeName) != _bones_map.end()) {
        unsigned int BoneIndex = _bones_map[NodeName];
        _bones_info[BoneIndex].final_transformation =
        _global_inverse_transform * GlobalTransformation * _bones_info[BoneIndex].bone_offset;
    }
    
    for (uint i = 0; i < pNode->mNumChildren; i++) {
        ReadNodeHeirarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
    }
}


void BonesMesh::bone_transform(float seconds, std::vector<Mat4f>& transforms)
{
    Mat4f Identity;
    Identity.InitIdentity();
    
    float TicksPerSecond = (float)(_scene->mAnimations[0]->mTicksPerSecond != 0 ? _scene->mAnimations[0]->mTicksPerSecond : 25.0f);
    float TimeInTicks = seconds * TicksPerSecond;
    float AnimationTime = fmod(TimeInTicks, (float)_scene->mAnimations[0]->mDuration);
    
    ReadNodeHeirarchy(AnimationTime, _scene->mRootNode, Identity);
    
    transforms.resize(_num_bones);
    
    for (uint i = 0; i < _num_bones; i++) {
        transforms[i] = _bones_info[i].final_transformation;
    }
}


const aiNodeAnim* BonesMesh::FindNodeAnim(const aiAnimation* pAnimation, const char* NodeName)
{
    for (uint i = 0; i < pAnimation->mNumChannels; i++) {
        const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];
        if(strcmp(pNodeAnim->mNodeName.data, NodeName)){
            return pNodeAnim;
        }
    }
    
    return nullptr;
}
