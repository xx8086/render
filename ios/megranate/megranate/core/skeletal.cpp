//
//  skeletal.cpp
//  megranate
//
//  Created by liu on 2018/7/12.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#include <assert.h>
#include <sstream>
#include "skeletal.hpp"
#include "../object/config_render.h"
#include "../math/math_common.hpp"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)
#define POSITION_LOCATION    0
#define TEX_COORD_LOCATION   1
#define NORMAL_LOCATION      2
#define BONE_ID_LOCATION     3
#define BONE_WEIGHT_LOCATION 4

namespace megranate {
    Skeletal::Skeletal(Context* context) : Component(context), _shader(context){
        _vao = 0;
        memset(_vbos, 0, sizeof(_vbos));
        _num_bones = 0;
        _scene = NULL;
    }
    
    Skeletal::~Skeletal(){
        clear();
    }

    
    mg_void update(){
        ;
    }

    mg_void Skeletal::draw(const Mat4f &mat){
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        _shader.use();
        
        std::vector<Mat4f> transform;
        bone_transform(_time.interval_ms()/1000.0f, transform);//_bones_mesh
        for (unsigned int i = 0 ; i < transform.size() ; i++) {
            set_bones_uniformlocation(i, transform[i]);
        }
        
        _shader.setmat4(_shader.getuniformlocation("pvw"), mat, GL_TRUE);
        render();
        _shader.unuse();
    }
    mg_void Skeletal::shutdown(){
        glDeleteProgram (_shader.programid());
    }
    mg_void Skeletal::touch_event(){
        ;
    }
    
    mg_void Skeletal::release(){
        ;
    }
    
    
    void Skeletal::bone_uniformlocation(){
        char bone_name[128];
        _vec_bones.resize(_bones_counts);
        for (unsigned int i = 0; i < _bones_counts; i++) {
            memset(bone_name, 0, sizeof(bone_name));
            snprintf(bone_name, sizeof(bone_name), "gBones[%d]", i);
            _vec_bones[i] = _shader.getuniformlocation(bone_name);
        }
    }
    
    void Skeletal::set_bones_uniformlocation(int index, Mat4f& m){
        assert(index >= 0 && _bones_counts > index);
        _shader.setmat4(_vec_bones[index], m, GL_TRUE);
    }
    
    void Skeletal::VertexBoneData::add_bone_data(unsigned int bone_id, float weight){
        for (uint i = 0 ; i < NUM_BONES_PER_VEREX; i++) {
            if (weights[i] == 0.0) {
                ids[i]     = bone_id;
                weights[i] = weight;
                return;
            }
        }
        
        // should never get here - more bones than we have space for
        assert(0);
    }
    
    void Skeletal::clear(){
        for (uint i = 0 ; i < _textures.size() ; i++) {
            SAFE_DELETE(_textures[i]);
        }
        
        if (_vbos[0] != 0) {
            glDeleteBuffers(ARRAY_SIZE_IN_ELEMENTS(_vbos), _vbos);
        }
        
        if (_vao != 0) {
            glDeleteVertexArrays(1, &_vao);
            _vao = 0;
        }
    }
    
    
    bool Skeletal::load_mesh(const std::string& strfile){
        clear();
        
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
        glGenBuffers(ARRAY_SIZE_IN_ELEMENTS(_vbos), _vbos);
        bool ret = false;
        _scene = _importer.ReadFile(strfile.c_str(), ASSIMP_LOAD_FLAGS);
        if (_scene) {
            aiMatrix4x4& aimt4 = _scene->mRootNode->mTransformation;
            _global_inverse_transform = Mat4f(aimt4.a1, aimt4.a2, aimt4.a3, aimt4.a4,
                                              aimt4.b1, aimt4.b2, aimt4.b3, aimt4.b4,
                                              aimt4.c1, aimt4.c2, aimt4.c3, aimt4.c4,
                                              aimt4.d1, aimt4.d2, aimt4.d3, aimt4.d4);
            //_global_inverse_transform.inverse();
            inverse(_global_inverse_transform);
            ret = load_scene(_scene, strfile);
        }
        else {
            printf("Error parsing '%s': '%s'\n", strfile.c_str(), _importer.GetErrorString());
        }
        
        glBindVertexArray(0);
        return ret;
    }
    
    
    bool Skeletal::load_scene(const aiScene* pScene, const std::string& strfile)
    {
        _entries.resize(pScene->mNumMeshes);
        _textures.resize(pScene->mNumMaterials);
        
        std::vector<Vec3f> positions;
        std::vector<Vec3f> normals;
        std::vector<Vec2f> tex_coords;
        std::vector<VertexBoneData> bones;
        std::vector<unsigned int> indices;
        unsigned int num_vertices = 0;
        unsigned int num_indices = 0;
        
        for (int i = 0 ; i < _entries.size() ; i++) {
            _entries[i].material_index = pScene->mMeshes[i]->mMaterialIndex;
            _entries[i].num_indices    = pScene->mMeshes[i]->mNumFaces * 3;
            _entries[i].base_vertex    = num_vertices;
            _entries[i].base_index     = num_indices;
            
            num_vertices += pScene->mMeshes[i]->mNumVertices;
            num_indices  += _entries[i].num_indices;
        }
        
        // Reserve space in the vectors for the vertex attributes and indices
        positions.reserve(num_vertices);
        normals.reserve(num_vertices);
        tex_coords.reserve(num_vertices);
        bones.resize(num_vertices);
        indices.reserve(num_indices);
        
        // Initialize the meshes in the scene one by one
        for (int i = 0 ; i < _entries.size() ; i++) {
            const aiMesh* paiMesh = pScene->mMeshes[i];
            load_mesh(i, paiMesh, positions, normals, tex_coords, bones, indices);
        }
        
        if (!load_materials(pScene, strfile)) {
            return false;
        }
        
        // Generate and populate the buffers with vertex attributes and the indices
        glBindBuffer(GL_ARRAY_BUFFER, _vbos[POS_VB]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions[0]) * positions.size(), &positions[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(POSITION_LOCATION);
        glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, _vbos[TEXCOORD_VB]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(tex_coords[0]) * tex_coords.size(), &tex_coords[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(TEX_COORD_LOCATION);
        glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, _vbos[NORMAL_VB]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0]) * normals.size(), &normals[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(NORMAL_LOCATION);
        glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, _vbos[BONE_VB]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(bones[0]) * bones.size(), &bones[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(BONE_ID_LOCATION);
        glVertexAttribIPointer(BONE_ID_LOCATION, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);
        glEnableVertexAttribArray(BONE_WEIGHT_LOCATION);
        glVertexAttribPointer(BONE_WEIGHT_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (const GLvoid*)(sizeof(unsigned int)*NUM_BONES_PER_VEREX) );
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbos[INDEX_BUFFER]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);
        
        return 1;
    }
    
    
    void Skeletal::load_mesh(unsigned int mesh_index,
                              const aiMesh* mesh,
                              std::vector<Vec3f>& positions,
                              std::vector<Vec3f>& normals,
                              std::vector<Vec2f>& tex_coords,
                              std::vector<VertexBoneData>& bones,
                              std::vector<unsigned int>& indices){
        const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
        for (uint i = 0 ; i < mesh->mNumVertices ; i++) {
            const aiVector3D* pos      = &(mesh->mVertices[i]);
            const aiVector3D* normal   = &(mesh->mNormals[i]);
            const aiVector3D* texcoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero3D;
            
            positions.push_back(Vec3f(pos->x, pos->y, pos->z));
            normals.push_back(Vec3f(normal->x, normal->y, normal->z));
            tex_coords.push_back(Vec2f(texcoord->x, texcoord->y));
        }
        
        load_bones(mesh_index, mesh, bones);
        unsigned int basevexter = _entries[mesh_index].base_vertex;
        for (uint i = 0 ; i < mesh->mNumFaces ; i++) {
            const aiFace& Face = mesh->mFaces[i];
            assert(Face.mNumIndices == 3);
            indices.push_back(Face.mIndices[0] + basevexter);
            indices.push_back(Face.mIndices[1] + basevexter);
            indices.push_back(Face.mIndices[2] + basevexter);
        }
    }
    
    
    void Skeletal::load_bones(unsigned int mesh_index, const aiMesh* mesh, std::vector<VertexBoneData>& bones)
    {
        for (int i = 0 ; i < mesh->mNumBones ; i++) {
            unsigned int bone_index = 0;
            std::string bone_name(mesh->mBones[i]->mName.data);
            
            if (_bone_mapping.find(bone_name) == _bone_mapping.end()) {
                bone_index = _num_bones;
                _num_bones++;
                BoneInfo bi;
                _bone_info.push_back(bi);
                
                aiMatrix4x4& aimt4 = mesh->mBones[i]->mOffsetMatrix;
                _bone_info[bone_index].BoneOffset = Mat4f(aimt4.a1, aimt4.a2, aimt4.a3, aimt4.a4,
                                                          aimt4.b1, aimt4.b2, aimt4.b3, aimt4.b4,
                                                          aimt4.c1, aimt4.c2, aimt4.c3, aimt4.c4,
                                                          aimt4.d1, aimt4.d2, aimt4.d3, aimt4.d4);
                _bone_mapping[bone_name] = bone_index;
            }
            else {
                bone_index = _bone_mapping[bone_name];
            }
            
            for (int j = 0 ; j < mesh->mBones[i]->mNumWeights ; j++) {
                unsigned int vertex_id = _entries[mesh_index].base_vertex + mesh->mBones[i]->mWeights[j].mVertexId;
                bones[vertex_id].add_bone_data(bone_index, mesh->mBones[i]->mWeights[j].mWeight);
            }
        }
    }
    
    
    bool Skeletal::load_materials(const aiScene* pScene, const std::string& strfile){
        std::string::size_type slash_index = strfile.find_last_of("/");
        std::string std_dir;
        if (slash_index == std::string::npos) {
            std_dir = ".";
        }
        else if (slash_index == 0) {
            std_dir = "/";
        }
        else {
            std_dir = strfile.substr(0, slash_index);
        }
        
        bool ret = true;
        for (int i = 0 ; i < pScene->mNumMaterials ; i++) {
            const aiMaterial* material = pScene->mMaterials[i];
            _textures[i] = NULL;
            if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
                aiString path;
                if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
                    std::string p(path.data);
                    if (p.substr(0, 2) == ".\\") {
                        p = p.substr(2, p.size() - 2);
                    }
                    
                    std::string full_path = std_dir + "/" + p;
                    _textures[i] = new TextureGl();
                    if (!_textures[i]->load_texture(full_path)) {
                        printf("Error loading texture '%s'\n", full_path.c_str());
                        delete _textures[i];
                        _textures[i] = NULL;
                        ret = false;
                    }
                    else {
                        printf("%d - loaded texture '%s'\n", i, full_path.c_str());
                    }
                }
            }
        }
        
        return ret;
    }
    
    
    void Skeletal::render(){
        glBindVertexArray(_vao);
        int entries_size = _entries.size() - 1;
        for (int i = 0 ; i < _entries.size() ; i++) {
            const uint MaterialIndex = _entries[i].material_index;
            assert(MaterialIndex < _textures.size());
            if (_textures[MaterialIndex]) {
                _textures[MaterialIndex]->bind(GL_TEXTURE0);
            }
            
            glDrawElements(GL_TRIANGLES,
                           _entries[i].num_indices,
                           GL_UNSIGNED_INT,
                           (void*)(sizeof(uint) * _entries[i].base_index));
        }
        
        glBindVertexArray(0);
    }
    
    
    uint Skeletal::find_position(float animation_time, const aiNodeAnim* node_anim)
    {
        for (uint i = 0 ; i < node_anim->mNumPositionKeys - 1 ; i++) {
            if (animation_time < (float)node_anim->mPositionKeys[i + 1].mTime) {
                return i;
            }
        }
        
        assert(0);
        return 0;
    }
    
    
    uint Skeletal::find_rotation(float animation_time, const aiNodeAnim* node_anim){
        assert(node_anim->mNumRotationKeys > 0);
        for (uint i = 0 ; i < node_anim->mNumRotationKeys - 1 ; i++) {
            if (animation_time < (float)node_anim->mRotationKeys[i + 1].mTime) {
                return i;
            }
        }
        
        assert(0);
        return 0;
    }
    
    
    uint Skeletal::find_scaling(float animation_time, const aiNodeAnim* node_anim){
        assert(node_anim->mNumScalingKeys > 0);
        for (uint i = 0 ; i < node_anim->mNumScalingKeys - 1 ; i++) {
            if (animation_time < (float)node_anim->mScalingKeys[i + 1].mTime) {
                return i;
            }
        }
        
        assert(0);
        
        return 0;
    }
    
    
    void Skeletal::CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim){
        if (pNodeAnim->mNumPositionKeys == 1) {
            Out = pNodeAnim->mPositionKeys[0].mValue;
            return;
        }
        
        uint PositionIndex = find_position(AnimationTime, pNodeAnim);
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
    
    
    void Skeletal::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim){
        // we need at least two values to interpolate...
        if (pNodeAnim->mNumRotationKeys == 1) {
            Out = pNodeAnim->mRotationKeys[0].mValue;
            return;
        }
        
        uint RotationIndex = find_rotation(AnimationTime, pNodeAnim);
        uint NextRotationIndex = (RotationIndex + 1);
        assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
        float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
        float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
        assert(Factor >= 0.0f && Factor <= 1.0f);
        const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
        const aiQuaternion& EndRotationQ   = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
        aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
        Out = Out.Normalize();
    }
    
    
    void Skeletal::CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim){
        if (pNodeAnim->mNumScalingKeys == 1) {
            Out = pNodeAnim->mScalingKeys[0].mValue;
            return;
        }
        
        uint ScalingIndex = find_scaling(AnimationTime, pNodeAnim);
        uint NextScalingIndex = (ScalingIndex + 1);
        assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
        float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
        float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
        assert(Factor >= 0.0f && Factor <= 1.0f);
        const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
        const aiVector3D& End   = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
        aiVector3D Delta = End - Start;
        Out = Start + Factor * Delta;
    }
    
    
    void Skeletal::read_node_heirarchy(float animation_time, const aiNode* node, const Mat4f& parent_transform){
        std::string node_name(node->mName.data);
        const aiAnimation* animation = _scene->mAnimations[0];
        const aiMatrix4x4& aimt4 = node->mTransformation;
        Mat4f node_transformation(aimt4.a1, aimt4.a2, aimt4.a3, aimt4.a4,
                                  aimt4.b1, aimt4.b2, aimt4.b3, aimt4.b4,
                                  aimt4.c1, aimt4.c2, aimt4.c3, aimt4.c4,
                                  aimt4.d1, aimt4.d2, aimt4.d3, aimt4.d4);
        const aiNodeAnim* node_anim = find_node_anim(animation, node_name);
        
        if (node_anim) {
            aiVector3D scaling;
            CalcInterpolatedScaling(scaling, animation_time, node_anim);
            Mat4f scaling_mat;
            init_mat_scale(scaling_mat, scaling.x, scaling.y, scaling.z);
            
            aiQuaternion rotation_quate;
            CalcInterpolatedRotation(rotation_quate, animation_time, node_anim);
            const aiMatrix3x3& aimt3 = rotation_quate.GetMatrix();
            Mat4f rotation_mat = Mat4f(aimt3.a1, aimt3.a2, aimt3.a3, 0.0f,
                                       aimt3.b1, aimt3.b2, aimt3.b3, 0.0f,
                                       aimt3.c1, aimt3.c2, aimt3.c3, 0.0f,
                                       0.0f,     0.0f,     0.0f,     1.0f);
            
            aiVector3D translation;
            CalcInterpolatedPosition(translation, animation_time, node_anim);
            Mat4f translation_mat;
            init_mat_translation(translation_mat, translation.x, translation.y, translation.z);
            node_transformation = translation_mat * rotation_mat * scaling_mat;
        }
        
        Mat4f global_transformation = parent_transform * node_transformation;
        if (_bone_mapping.find(node_name) != _bone_mapping.end()) {
            uint bone_index = _bone_mapping[node_name];
            _bone_info[bone_index].FinalTransformation = _global_inverse_transform * global_transformation * _bone_info[bone_index].BoneOffset;
        }
        
        for (uint i = 0 ; i < node->mNumChildren ; i++) {
            read_node_heirarchy(animation_time, node->mChildren[i], global_transformation);
        }
    }
    
    
    void Skeletal::bone_transform(float seconds, std::vector<Mat4f>& transforms){
        Mat4f indentity;
        indentity.identity();
        float ticks_per_second = (float)(_scene->mAnimations[0]->mTicksPerSecond != 0 ? _scene->mAnimations[0]->mTicksPerSecond : 25.0f);
        float time_ticks = seconds * ticks_per_second;
        float animation_time = fmod(time_ticks, (float)_scene->mAnimations[0]->mDuration);
        read_node_heirarchy(animation_time, _scene->mRootNode, indentity);
        transforms.resize(_num_bones);
        for (uint i = 0 ; i < _num_bones ; i++) {
            transforms[i] = _bone_info[i].FinalTransformation;
        }
    }
    
    
    const aiNodeAnim* Skeletal::find_node_anim(const aiAnimation* animation, const std::string node_name){
        for (uint i = 0 ; i < animation->mNumChannels ; i++) {
            const aiNodeAnim* node_anim = animation->mChannels[i];
            if (std::string(node_anim->mNodeName.data) == node_name) {
                return node_anim;
            }
        }
        
        return NULL;
    }

}