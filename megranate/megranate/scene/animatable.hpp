//
//  animatable.hpp
//  megranate
//
//  Created by liu on 2018/7/9.
//  Copyright © 2018年 hanliu. All rights reserved.
//

#ifndef animatable_hpp
#define animatable_hpp
#include "../object/object.h"

namespace megranate {
    class Animatable : public Object{
        //MEGRANATE_OBJECT(Animatable, Object);
    public:
        Animatable(Context*);
        virtual ~Animatable();
    };
}

#endif /* animatable_hpp */
