//
//  bones_shader.hpp
//  render
//
//  Created by liu on 2018/6/27.
//  Copyright © 2018年 redliu. All rights reserved.
//

#ifndef bones_shader_hpp
#define bones_shader_hpp


#include "shader.hpp"
#include <vector>

class BonesShader: public CShader{
public:
    void bone_uniformlocation();
    void set_bones_uniformlocation(int index, Mat4f& m);
    void set_bones_counts(GLuint counts){_bones_counts = counts;};
private:
    GLuint _bones_counts = 0;
    std::vector<GLuint> _vec_bones;
};


#endif /* bones_shader_hpp */
