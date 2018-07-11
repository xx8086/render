//
//  config_render.h
//  megranate
//
//  Created by liu on 2018/7/9.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef config_render_h
#define config_render_h
namespace megranate {
#define M_PI (3.14159265358979323846264338327950288f)
static const float M_HALF_PI = M_PI * 0.5f;
static const int M_MIN_INT = 0x80000000;
static const int M_MAX_INT = 0x7fffffff;
static const unsigned M_MIN_UNSIGNED = 0x00000000;
static const unsigned M_MAX_UNSIGNED = 0xffffffff;

static const float M_EPSILON = 0.000001f;
static const float M_LARGE_EPSILON = 0.00005f;
static const float M_MIN_NEARCLIP = 0.01f;
static const float M_MAX_FOV = 160.0f;
static const float M_LARGE_VALUE = 100000000.0f;
static const float M_INFINITY = (float)HUGE_VAL;
static const float M_DEGTORAD = M_PI / 180.0f;
static const float M_DEGTORAD_2 = M_PI / 360.0f;    // M_DEGTORAD / 2.f
static const float M_RADTODEG = 1.0f / M_DEGTORAD;

    
static const unsigned int FIRST_REPLICATED_ID = 0x1;
static const unsigned int LAST_REPLICATED_ID = 0xffffff;
static const unsigned int FIRST_LOCAL_ID = 0x01000000;
static const unsigned int LAST_LOCAL_ID = 0xffffffff;
    
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define SAFE_DELETE(ptr) \
if(nullptr != ptr){\
delete ptr;\
ptr = nullptr;\
}
}

inline unsigned float_to_raw_int_bits(float value){
    unsigned u = *((unsigned*)&value);
    return u;
}

inline bool nan(float value){
    unsigned u = float_to_raw_int_bits(value);
    return (u & 0x7fffffff) > 0x7f800000;
}

#endif /* config_render_h */
