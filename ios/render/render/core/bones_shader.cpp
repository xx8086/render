//
//  bones_shader.cpp
//  render
//
//  Created by liu on 2018/6/27.
//  Copyright © 2018年 redliu. All rights reserved.
//

#include "bones_shader.hpp"

#include "stdio.h"
#include <assert.h>

void BonesShader::bone_uniformlocation(){
    char bone_name[128];
    _vec_bones.resize(_bones_counts);
    for (unsigned int i = 0; i < _bones_counts; i++) {
        memset(bone_name, 0, sizeof(bone_name));
        snprintf(bone_name, sizeof(bone_name), "gBones[%d]", i);
        _vec_bones[i] = getuniformlocation(bone_name);
    }
}

void BonesShader::set_bones_uniformlocation(int index, Mat4f& m){
    assert(index >= 0 && _bones_counts > index);
    setmat4(_vec_bones[index], m, GL_TRUE);
}
