//
//  skeletal.hpp
//  megranate
//
//  Created by liu on 2018/7/12.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef skeletal_hpp
#define skeletal_hpp

#include "../scene/component.hpp"
#include "../render/shader.hpp"
#include "../object/texture.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "../object/timer.hpp"
#include "../render/materials.hpp"
#include <vector>
#include <map>

namespace megranate {
    class Skeletal : public Component {
        MEGRANATE_OBJECT(Skeletal, Object);
    public:
        Skeletal(Context* context);
        virtual ~Skeletal();
    public:
        virtual mg_bool load_res(const std::string&);
        virtual mg_void update();
        virtual mg_void draw(const Mat4f &project, const Mat4f &view, const Mat4f &world);
        virtual mg_void shutdown();
        virtual mg_void touch_event();
        mg_void release();
        mg_void render();
        
        
    private:
        mg_bool load_mesh(const std::string& Filename);
        mg_uint num_bones() const{ return _num_bones;}
        mg_void bone_transform(float, std::vector<Mat4f>&);
        mg_void bone_uniformlocation();
        mg_void set_bones_uniformlocation(mg_int index, Mat4f& m);
        mg_void set_bones_counts(GLuint counts){_bones_counts = counts;};
    private:
#define NUM_BONES_PER_VEREX 24
        struct BoneInfo{
            Mat4f BoneOffset;
            Mat4f FinalTransformation;
            
            BoneInfo(){
                BoneOffset.set_zero();
                FinalTransformation.set_zero();
            }
        };
        
        struct VertexBoneData{
            mg_uint ids[NUM_BONES_PER_VEREX];
            mg_float weights[NUM_BONES_PER_VEREX];
            VertexBoneData(){
                reset();
            };
            
            mg_void reset(){
                memset(ids, 0, sizeof(ids));
                memset(weights, 0, sizeof(weights));
            }
            
            mg_void add_bone_data(mg_uint, mg_float);
        };
        
        mg_uint find_scaling(mg_float, const aiNodeAnim*);
        mg_uint find_rotation(mg_float, const aiNodeAnim*);
        mg_uint find_position(mg_float, const aiNodeAnim*);
        mg_void calc_interpolated_scaling(aiVector3D& Out, mg_float AnimationTime, const aiNodeAnim* pNodeAnim);
        mg_void calc_interpolated_rotation(aiQuaternion& Out, mg_float AnimationTime, const aiNodeAnim* pNodeAnim);
        mg_void calc_interpolated_position(aiVector3D& Out, mg_float AnimationTime, const aiNodeAnim* pNodeAnim);
        mg_void read_node_heirarchy(mg_float, const aiNode*, const Mat4f&);
        mg_void load_mesh(mg_uint,
                       const aiMesh*,
                       std::vector<Vec3f>&,
                       std::vector<Vec3f>&,
                       std::vector<Vec2f>&,
                       std::vector<VertexBoneData>&,
                       std::vector<mg_uint>&);
        mg_void load_bones(mg_uint, const aiMesh*, std::vector<VertexBoneData>&);
        mg_void clear();
        mg_bool load_materials(const aiScene*, const std::string&);
        mg_bool load_scene(const aiScene*, const std::string&);
        const aiNodeAnim* find_node_anim(const aiAnimation*, const std::string);
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
        std::map<std::string, mg_uint> _bone_mapping;
        std::vector<BoneInfo> _bone_info;
        mg_uint _num_bones;
        Assimp::Importer _importer;
        Materials _materials;
        Mat4f _global_inverse_transform;
        const aiScene* _scene;
    private:
        GLuint _bones_counts = 0;
        std::vector<GLuint> _vec_bones;
        Shader* _shader = nullptr;
        Timer _time;
    };
}

#endif /* skeletal_hpp */
